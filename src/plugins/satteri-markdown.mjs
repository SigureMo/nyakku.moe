import katex from 'katex'
import getReadingTime from 'reading-time'
import { AdmonitionComponent } from './rehype-component-admonition.mjs'
import { GithubCardComponent } from './rehype-component-github-card.mjs'

function setFrontmatter(ctx, key, value) {
  const frontmatter = ctx.data.astro?.frontmatter
  if (frontmatter) frontmatter[key] = value
}

function getClassList(node) {
  const className = node.properties?.className ?? node.properties?.class
  if (Array.isArray(className)) return className
  if (typeof className === 'string') return className.split(/\s+/).filter(Boolean)
  return []
}

function cloneHastNode(node) {
  if (!node || typeof node !== 'object') return node

  const cloned = { type: node.type }
  if ('tagName' in node) cloned.tagName = node.tagName
  if ('properties' in node) cloned.properties = { ...node.properties }
  if ('value' in node) cloned.value = node.value
  if ('children' in node) cloned.children = [...(node.children ?? [])].map(cloneHastNode)
  if ('data' in node && node.data) cloned.data = { ...node.data }

  return cloned
}

function getHastText(node) {
  if (!node || typeof node !== 'object') return ''
  if ('value' in node && typeof node.value === 'string') return node.value
  if ('children' in node) return [...(node.children ?? [])].map(getHastText).join('')
  return ''
}

function escapeHtml(value) {
  return String(value)
    .replaceAll('&', '&amp;')
    .replaceAll('<', '&lt;')
    .replaceAll('>', '&gt;')
    .replaceAll('"', '&quot;')
}

function renderKatex(value, displayMode) {
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

function getMdastRoot(node, ctx) {
  let current = node
  let parent = ctx.parent(current)

  while (parent) {
    current = parent
    parent = ctx.parent(current)
  }

  return current
}

export function satteriReadingTime() {
  let computed = false

  function compute(node, ctx) {
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

export function satteriExcerpt() {
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

export function satteriDirectiveToHast() {
  function visitDirective(node, ctx) {
    const attributes = { ...node.attributes }
    const firstChild = node.children?.[0]

    if (firstChild?.data?.directiveLabel) {
      attributes['has-directive-label'] = true
    }

    ctx.setProperty(node, 'data', {
      ...node.data,
      hName: node.name,
      hProperties: attributes,
    })
  }

  return {
    name: 'nyakku-directive-to-hast',
    containerDirective: visitDirective,
    leafDirective: visitDirective,
    textDirective: visitDirective,
  }
}

export function satteriKatexDisplay() {
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

export function satteriKatexInline() {
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

function cloneHastChildren(node) {
  return [...(node.children ?? [])].map(cloneHastNode)
}

function getGithubAdmonitionType(node) {
  if (node.tagName !== 'blockquote') return undefined

  const paragraph = node.children?.find(
    (child) => child.type === 'element' && child.tagName === 'p'
  )
  const firstChild = paragraph?.children?.[0]
  const match =
    firstChild?.type === 'text' &&
    firstChild.value.match(/^\[!(NOTE|TIP|IMPORTANT|CAUTION|WARNING)\]\n?/i)

  return match ? { marker: match[0], type: match[1].toLowerCase() } : undefined
}

export function satteriDirectiveComponents() {
  const admonitionTypes = new Set(['note', 'tip', 'important', 'caution', 'warning'])

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
          const paragraph = children.find(
            (child) => child.type === 'element' && child.tagName === 'p'
          )
          const firstChild = paragraph?.children?.[0]

          if (firstChild?.type === 'text') {
            firstChild.value = firstChild.value.slice(githubAdmonition.marker.length)
          }

          return AdmonitionComponent({}, children, githubAdmonition.type)
        }

        if (admonitionTypes.has(node.tagName)) {
          return AdmonitionComponent({ ...node.properties }, cloneHastChildren(node), node.tagName)
        }
      },
    },
  }
}

export function satteriExternalLinks() {
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

function headingDepth(node) {
  if (node?.type !== 'element' || !/^h[1-6]$/.test(node.tagName)) return undefined
  return Number(node.tagName.slice(1))
}

function satteriSectionizeDepth(depth) {
  return {
    name: `nyakku-sectionize-h${depth}`,
    element: {
      filter: [`h${depth}`],
      visit(node, ctx) {
        const parent = ctx.parent(node)
        const startIndex = ctx.indexOf(node)
        if (!parent || startIndex === undefined || !Array.isArray(parent.children)) return

        const sectionChildren = []
        for (let index = startIndex; index < parent.children.length; index += 1) {
          const child = parent.children[index]
          const childDepth = headingDepth(child)

          if (index !== startIndex && childDepth !== undefined && childDepth <= depth) break
          sectionChildren.push(child)
        }

        if (sectionChildren.length === 0) return

        ctx.replaceNode(node, {
          type: 'element',
          tagName: 'section',
          properties: {},
          children: sectionChildren.map(cloneHastNode),
        })

        for (const child of sectionChildren.slice(1)) {
          ctx.removeNode(child)
        }
      },
    },
  }
}

export function satteriSectionize() {
  return [6, 5, 4, 3, 2, 1].map(satteriSectionizeDepth)
}

export function satteriAutolinkHeadings() {
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
