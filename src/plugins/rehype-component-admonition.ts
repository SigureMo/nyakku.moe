import type { Element, ElementContent, Properties } from 'hast'
import { h } from 'hastscript'

export type AdmonitionType = 'tip' | 'note' | 'important' | 'caution' | 'warning'

type AdmonitionProperties = Properties & {
  'has-directive-label'?: unknown
  title?: string
}

/**
 * Creates an admonition component.
 */
export function AdmonitionComponent(
  properties: Readonly<AdmonitionProperties>,
  children: ElementContent[],
  type: AdmonitionType
): Element {
  if (!Array.isArray(children) || children.length === 0)
    return h(
      'div',
      { class: 'hidden' },
      'Invalid admonition directive. (Admonition directives must be of block type ":::note{name="name"} <content> :::")'
    )

  let label: ElementContent | undefined
  if (properties['has-directive-label']) {
    label = children[0]
    children = children.slice(1)
    if (label?.type === 'element') label.tagName = 'div' // Change the tag <p> to <div>
  }

  return h('blockquote', { class: `admonition bdm-${type}` }, [
    h('span', { class: 'bdm-title' }, label ?? type.toUpperCase()),
    ...children,
  ])
}
