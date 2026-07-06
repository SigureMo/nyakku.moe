import type { SatteriAstroData, SatteriProcessorOptions } from '@astrojs/markdown-satteri'
import type { Element, ElementContent, Nodes as HastNode } from 'hast'
import katex from 'katex'
import getReadingTime from 'reading-time'
import type { Nodes as MdastNode } from 'mdast'
import { AdmonitionComponent, type AdmonitionType } from './rehype-component-admonition.ts'
import { GithubCardComponent } from './rehype-component-github-card.ts'

type MdastPluginDefinition = NonNullable<SatteriProcessorOptions['mdastPlugins']>[number]
type HastPluginDefinition = NonNullable<SatteriProcessorOptions['hastPlugins']>[number]
type MdastVisitor = NonNullable<MdastPluginDefinition['text']>
type MdastVisitorContext = Parameters<MdastVisitor>[1]
type ContainerDirectiveNode = Parameters<
  NonNullable<MdastPluginDefinition['containerDirective']>
>[0]
type LeafDirectiveNode = Parameters<NonNullable<MdastPluginDefinition['leafDirective']>>[0]
type TextDirectiveNode = Parameters<NonNullable<MdastPluginDefinition['textDirective']>>[0]
type DirectiveNode = ContainerDirectiveNode | LeafDirectiveNode | TextDirectiveNode

const admonitionTypes = [
  'note',
  'tip',
  'important',
  'caution',
  'warning',
] as const satisfies readonly AdmonitionType[]
const admonitionTypeSet = new Set<string>(admonitionTypes)

function isAdmonitionType(value: string): value is AdmonitionType {
  return admonitionTypeSet.has(value)
}

function setFrontmatter(ctx: MdastVisitorContext, key: string, value: unknown): void {
  const frontmatter = (ctx.data.astro as SatteriAstroData | undefined)?.frontmatter
  if (frontmatter) frontmatter[key] = value
}

function getClassList(node: Readonly<Element>): string[] {
  const className = node.properties?.className ?? node.properties?.class
  if (Array.isArray(className))
    return className.filter((item): item is string => typeof item === 'string')
  if (typeof className === 'string') return className.split(/\s+/).filter(Boolean)
  return []
}

function isElementWithTag(node: ElementContent, tagName: string): node is Element {
  return node.type === 'element' && node.tagName === tagName
}

function cloneHastNode(node: Readonly<HastNode>): HastNode {
  return structuredClone(node) as HastNode
}

function getHastText(node: Readonly<HastNode> | undefined): string {
  if (!node) return ''
  if ('value' in node && typeof node.value === 'string') return node.value
  if ('children' in node) return [...(node.children ?? [])].map(getHastText).join('')
  return ''
}

function escapeHtml(value: unknown): string {
  return String(value)
    .replaceAll('&', '&amp;')
    .replaceAll('<', '&lt;')
    .replaceAll('>', '&gt;')
    .replaceAll('"', '&quot;')
}

function renderKatex(value: string, displayMode: boolean): string {
  try {
    return katex.renderToString(value, { displayMode, throwOnError: true })
  } catch (error) {
    try {
      return katex.renderToString(value, {
        displayMode,
        strict: 'ignore',
        throwOnError: false,
      })
    } catch {
      const message = escapeHtml(error)
      return `<span class="katex-error" style="color:#cc0000" title="${message}">${escapeHtml(value)}</span>`
    }
  }
}

function getMdastRoot(node: Readonly<MdastNode>, ctx: MdastVisitorContext): Readonly<MdastNode> {
  let current = node
  let parent = ctx.parent(current)

  while (parent) {
    current = parent
    parent = ctx.parent(current)
  }

  return current
}

export function satteriReadingTime(): MdastPluginDefinition {
  let computed = false

  function compute(node: Readonly<MdastNode>, ctx: MdastVisitorContext): void {
    if (computed) return

    const textOnPage = ctx.textContent(getMdastRoot(node, ctx), { includeImageAlt: true })
    const readingTime = getReadingTime(textOnPage)
    setFrontmatter(ctx, 'minutes', Math.max(1, Math.round(readingTime.minutes)))
    setFrontmatter(ctx, 'words', readingTime.words)
    computed = true
  }

  return {
    name: 'nyakku-reading-time',
    text: compute,
    inlineCode: compute,
    code: compute,
    image: compute,
  }
}

export function satteriExcerpt(): MdastPluginDefinition {
  let captured = false

  return {
    name: 'nyakku-excerpt',
    paragraph(node, ctx) {
      if (captured || ctx.parent(node)?.type !== 'root') return

      setFrontmatter(ctx, 'excerpt', ctx.textContent(node, { includeImageAlt: true }))
      captured = true
    },
  }
}

function visitDirective(node: DirectiveNode, ctx: MdastVisitorContext): void {
  const attributes: Record<string, unknown> = { ...node.attributes }
  const firstChild = node.children?.[0]
  const firstChildData = firstChild?.data as { directiveLabel?: unknown } | undefined

  if (firstChildData?.directiveLabel) {
    attributes['has-directive-label'] = true
  }

  ctx.setProperty(node, 'data', {
    ...node.data,
    hName: node.name,
    hProperties: attributes,
  })
}

export function satteriDirectiveToHast(): MdastPluginDefinition {
  return {
    name: 'nyakku-directive-to-hast',
    containerDirective: visitDirective,
    leafDirective: visitDirective,
    textDirective: visitDirective,
  }
}

export function satteriKatexDisplay(): HastPluginDefinition {
  return {
    name: 'nyakku-katex-display',
    element: {
      filter: ['pre'],
      visit(node) {
        const code = node.children?.[0]
        if (!code || code.type !== 'element' || code.tagName !== 'code') return

        const classes = getClassList(code)
        if (!classes.includes('language-math') && !classes.includes('math-display')) return

        return {
          type: 'raw',
          value: renderKatex(getHastText(code), true),
        }
      },
    },
  }
}

export function satteriKatexInline(): HastPluginDefinition {
  return {
    name: 'nyakku-katex-inline',
    element: {
      filter: ['code'],
      visit(node, ctx) {
        const parent = ctx.parent(node)
        if (parent?.type === 'element' && parent.tagName === 'pre') return

        const classes = getClassList(node)
        if (!classes.includes('math-inline')) return

        return {
          type: 'raw',
          value: renderKatex(getHastText(node), false),
        }
      },
    },
  }
}

function cloneHastChildren(node: Readonly<Element>): ElementContent[] {
  return [...(node.children ?? [])].map(
    (child) => cloneHastNode(child as HastNode) as ElementContent
  )
}

function getGithubAdmonitionType(
  node: Readonly<Element>
): { marker: string; type: AdmonitionType } | undefined {
  if (node.tagName !== 'blockquote') return undefined

  const paragraph = node.children?.find((child) => isElementWithTag(child, 'p'))
  const firstChild = paragraph?.children?.[0]
  const match =
    firstChild?.type === 'text' &&
    firstChild.value.match(/^\[!(NOTE|TIP|IMPORTANT|CAUTION|WARNING)\]\n?/i)

  if (!match) return undefined

  const type = match[1].toLowerCase()
  return isAdmonitionType(type) ? { marker: match[0], type } : undefined
}

export function satteriDirectiveComponents(): HastPluginDefinition {
  return {
    name: 'nyakku-directive-components',
    element: {
      filter: ['github', 'blockquote', ...admonitionTypes],
      visit(node) {
        if (node.tagName === 'github') {
          return GithubCardComponent({ ...node.properties }, cloneHastChildren(node))
        }

        const githubAdmonition = getGithubAdmonitionType(node)
        if (githubAdmonition) {
          const children = cloneHastChildren(node)
          const paragraph = children.find((child) => isElementWithTag(child, 'p'))
          const firstChild = paragraph?.children?.[0]

          if (firstChild?.type === 'text') {
            firstChild.value = firstChild.value.slice(githubAdmonition.marker.length)
          }

          return AdmonitionComponent({}, children, githubAdmonition.type)
        }

        if (isAdmonitionType(node.tagName)) {
          return AdmonitionComponent({ ...node.properties }, cloneHastChildren(node), node.tagName)
        }
      },
    },
  }
}

export function satteriExternalLinks(): HastPluginDefinition {
  return {
    name: 'nyakku-external-links',
    element: {
      filter: ['a'],
      visit(node, ctx) {
        const href = node.properties?.href
        if (typeof href !== 'string' || !/^(https?:)?\/\//.test(href)) return

        ctx.setProperty(node, 'target', '_blank')
        ctx.setProperty(node, 'rel', 'noopener noreferrer')
      },
    },
  }
}

function headingDepth(node: Readonly<HastNode> | undefined): number | undefined {
  if (node?.type !== 'element' || !/^h[1-6]$/.test(node.tagName)) return undefined
  return Number(node.tagName.slice(1))
}

function satteriSectionizeDepth(depth: number): HastPluginDefinition {
  return {
    name: `nyakku-sectionize-h${depth}`,
    element: {
      filter: [`h${depth}`],
      visit(node, ctx) {
        const parent = ctx.parent(node)
        const startIndex = ctx.indexOf(node)
        if (!parent || startIndex === undefined || !Array.isArray(parent.children)) return

        const sectionChildren: Readonly<HastNode>[] = []
        for (let index = startIndex; index < parent.children.length; index += 1) {
          const child = parent.children[index]
          const childDepth = headingDepth(child)

          if (index !== startIndex && childDepth !== undefined && childDepth <= depth) break
          sectionChildren.push(child as HastNode)
        }

        if (sectionChildren.length === 0) return

        ctx.replaceNode(node, {
          type: 'element',
          tagName: 'section',
          properties: {},
          children: sectionChildren.map((child) => cloneHastNode(child) as ElementContent),
        })

        for (const child of sectionChildren.slice(1)) {
          ctx.removeNode(child)
        }
      },
    },
  }
}

export function satteriSectionize(): HastPluginDefinition[] {
  return [6, 5, 4, 3, 2, 1].map(satteriSectionizeDepth)
}

export function satteriAutolinkHeadings(): HastPluginDefinition {
  return {
    name: 'nyakku-autolink-headings',
    element: {
      filter: ['h1', 'h2', 'h3', 'h4', 'h5', 'h6'],
      visit(node, ctx) {
        const id = node.properties?.id
        if (typeof id !== 'string' || id.length === 0) return

        ctx.appendChild(node, {
          type: 'element',
          tagName: 'a',
          properties: {
            ariaHidden: 'true',
            className: ['anchor'],
            href: `#${id}`,
            tabIndex: -1,
          },
          children: [
            {
              type: 'element',
              tagName: 'span',
              properties: {
                className: ['anchor-icon'],
                'data-pagefind-ignore': true,
              },
              children: [],
            },
          ],
        })
      },
    },
  }
}
