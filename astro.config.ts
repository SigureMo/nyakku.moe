import { satteri, satteriHeadingIdsPlugin } from '@astrojs/markdown-satteri'
import sitemap from '@astrojs/sitemap'
import svelte from '@astrojs/svelte'
import tailwindcss from '@tailwindcss/vite'
import { pluginCollapsibleSections } from '@expressive-code/plugin-collapsible-sections'
import { pluginLineNumbers } from '@expressive-code/plugin-line-numbers'
import swup from '@swup/astro'
import { defineConfig } from 'astro/config'
import expressiveCode from 'astro-expressive-code'
import icon from 'astro-icon'
import { expressiveCodeConfig } from './src/config.ts'
import { pluginCustomCopyButton } from './src/plugins/expressive-code/custom-copy-button.ts'
import { pluginLanguageBadge } from './src/plugins/expressive-code/language-badge.ts'
import {
  satteriAutolinkHeadings,
  satteriDirectiveComponents,
  satteriDirectiveToHast,
  satteriExcerpt,
  satteriExternalLinks,
  satteriKatexDisplay,
  satteriKatexInline,
  satteriReadingTime,
  satteriSectionize,
} from './src/plugins/satteri-markdown.ts'

// https://astro.build/config
export default defineConfig({
  site: 'https://nyakku.moe/',
  base: '/',
  trailingSlash: 'always',
  integrations: [
    swup({
      theme: false,
      animationClass: 'transition-swup-', // see https://swup.js.org/options/#animationselector
      // the default value `transition-` cause transition delay
      // when the Tailwind class `transition-all` is used
      containers: ['main', '#toc'],
      smoothScrolling: true,
      cache: true,
      preload: true,
      accessibility: true,
      updateHead: import.meta.env.PROD,
      updateBodyClass: false,
      globalInstance: true,
    }),
    icon({
      include: {
        'material-symbols': ['*'],
        'fa6-brands': ['*'],
        'fa6-regular': ['*'],
        'fa6-solid': ['*'],
      },
    }),
    expressiveCode({
      themes: [expressiveCodeConfig.theme, expressiveCodeConfig.theme],
      plugins: [
        pluginCollapsibleSections(),
        pluginLineNumbers(),
        pluginLanguageBadge(),
        pluginCustomCopyButton(),
      ],
      defaultProps: {
        wrap: true,
        overridesByLang: {
          shellsession: {
            showLineNumbers: false,
          },
        },
      },
      styleOverrides: {
        codeBackground: 'var(--codeblock-bg)',
        borderRadius: '0.75rem',
        borderColor: 'none',
        codeFontSize: '0.875rem',
        codeFontFamily:
          "'JetBrains Mono Variable', ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, 'Liberation Mono', 'Courier New', monospace",
        codeLineHeight: '1.5rem',
        frames: {
          editorBackground: 'var(--codeblock-bg)',
          terminalBackground: 'var(--codeblock-bg)',
          terminalTitlebarBackground: 'var(--codeblock-topbar-bg)',
          editorTabBarBackground: 'var(--codeblock-topbar-bg)',
          editorActiveTabBackground: 'none',
          editorActiveTabIndicatorBottomColor: 'var(--primary)',
          editorActiveTabIndicatorTopColor: 'none',
          editorTabBarBorderBottomColor: 'var(--codeblock-topbar-bg)',
          terminalTitlebarBorderBottomColor: 'none',
        },
        textMarkers: {
          delHue: '0',
          insHue: '180',
          markHue: '250',
        },
      },
      frames: {
        showCopyToClipboardButton: false,
      },
    }),
    svelte(),
    sitemap(),
  ],
  markdown: {
    processor: satteri({
      features: {
        directive: true,
        math: true,
      },
      mdastPlugins: [satteriDirectiveToHast, satteriReadingTime, satteriExcerpt],
      hastPlugins: [
        satteriKatexDisplay,
        satteriKatexInline,
        satteriDirectiveComponents,
        satteriExternalLinks,
        ...satteriSectionize(),
        satteriHeadingIdsPlugin,
        satteriAutolinkHeadings,
      ],
    }),
  },
  vite: {
    plugins: [tailwindcss()],
    build: {
      rollupOptions: {
        onwarn(warning, warn) {
          // temporarily suppress this warning
          if (
            warning.message.includes('is dynamically imported by') &&
            warning.message.includes('but also statically imported by')
          ) {
            return
          }
          warn(warning)
        },
      },
    },
  },
})
