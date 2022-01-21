import type { UserConfig } from '@commitlint/types'

const Configuration: UserConfig = {
  extends: ['gitmoji'],
  rules: {
    'type-enum': [
      2,
      'always',
      [
        'feat',
        'fix',
        'docs',
        'dx',
        'refactor',
        'perf',
        'test',
        'workflow',
        'build',
        'ci',
        'chore',
        'types',
        'wip',
        'release',
        'deps',
      ],
    ],
  },
}

export default Configuration
