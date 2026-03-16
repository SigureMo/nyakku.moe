import { defineConfig } from 'vite-plus'

export default defineConfig({
  staged: {
    '*': 'vp check --fix',
  },
  fmt: {
    printWidth: 100,
    tabWidth: 2,
    singleQuote: true,
    trailingComma: 'es5',
    semi: false,
    arrowParens: 'always',
    sortTailwindcss: {},
    sortPackageJson: false,
    ignorePatterns: ['*.html', 'dist/', 'node_modules/', '*.min.js', 'pnpm-lock.yaml'],
  },
})
