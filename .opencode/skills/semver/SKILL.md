---
name: semver
description: Enforce Semantic Versioning with tbump.toml — bump, validate, tag, and document releases consistently for this repo.
license: MIT
compatibility: opencode
metadata:
  audience: maintainers
  workflow: release
  tool: tbump
---

## What I do

- Drive a correct `tbump` release for this repo (SemVer `MAJOR.MINOR.PATCH`).
- Enforce the repo's `tbump.toml` contract: file patches, ChangeLog gate, commit/tag templates, and tag push.
- Prevent common mistakes: dirty tree, missing ChangeLog entry, manual version edits, or wrong bump type.

## When to use me

Use this when you are:
- Preparing a tagged release or pre-release bump on `develop`/`main`.
- Asked to "bump version", "cut a release", "patch/minor/major", or to update `ChangeLog.md` and version strings.
- Fixing a failed `tbump` run (e.g. `before_commit` hook `grep -q {new_version} ChangeLog.md` failing).

Ask clarifying questions if the bump type (major/minor/patch) or target version is unclear. Do not guess.

## Repo contract (source of truth: `tbump.toml:1`)

```toml
github_url = "https://github.com/emrainey/embedded-superloop/"

[version]
current = "0.3.0"
regex = '''
  (?P<major>\d+)
  \.
  (?P<minor>\d+)
  \.
  (?P<patch>\d+)
  '''

[git]
message_template = "Bump to {new_version}"
tag_template = "v{new_version}"

[[file]]
src = "CMakeLists.txt"                                          # project(VERSION 0.3.0) at CMakeLists.txt:4

[[file]]
src = "build-support/share/cmake/embedded-superloop/embedded-superloop.cmake"  # project(VERSION 0.3.0) at embedded-superloop.cmake:5

[[before_commit]]
name = "check changelog"
cmd = "grep -q {new_version} ChangeLog.md"
```

Additional facts:
- `include/cmake.hpp.in:34` is **generated** via `configure_file` from `CMakeLists.txt` (`@PROJECT_VERSION_MAJOR@` etc.) — never patch it by hand. `tbump` patches the two `CMakeLists.txt`/`embedded-superloop.cmake` files and CMake regenerates the header.
- Submodule `third-party/libhypha/tbump.toml:1` is a **separate** tbump project. Do not run the root `tbump` for libhypha, and vice versa.
- `tbump` is installed via `pipx` at `~/.local/bin/tbump` (`tbump 6.11.0`) — invoke as `tbump`, not `venv/bin/tbump`.

## SemVer quick reference (https://semver.org/)

- `MAJOR` — incompatible API/behavior change. `0.y.z` is initial development: breaking changes MAY be minor.
- `MINOR` — backward-compatible feature.
- `PATCH` — backward-compatible bug fix.
- Precedence: `1.0.0 < 2.0.0 < 2.1.0 < 2.1.1`. No `v` prefix in `tbump.toml` current; tag adds `v` via `tag_template`.

Current repo is `0.3.0` (`ChangeLog.md:3` — `## v0.3.0 Unit Tests for I2C/SPI`). Most bumps today are `0.3.x` (patch) or `0.4.0` (minor) unless breaking.

## Preconditions

Check before any bump:

```bash
tbump current-version
git status --porcelain        # must be empty (tbump refuses to run on dirty tree)
git branch --show-current     # expected: issue-xxx tracking develop, or develop/main for release
git log --oneline -5
git tag --list | sort -V | tail -20
cat tbump.toml
cat ChangeLog.md | head -n 40
```

If `git status` is dirty, stash/commit first. If on a feature branch, confirm the bump should land there vs `develop`.

## Workflow

### 1 — Determine target version

Ask the user unless unambiguous:

- `patch`: `0.3.0` → `0.3.1`
- `minor`: `0.3.0` → `0.4.0` (reset patch to 0)
- `major`: `0.3.0` → `1.0.0` (or `0.3.0` → `0.4.0` counts as breaking in `0.y.z`)

Validate with the regex in `tbump.toml:10` — must be `^\d+\.\d+\.\d+$` (no `v` prefix, no suffix). Compute `NEW_VERSION` and confirm with user.

### 2 — Update ChangeLog.md FIRST

`tbump`'s `before_commit` hook runs `grep -q {new_version} ChangeLog.md` (`tbump.toml:34`). If this fails, tbump aborts after patching files but before commit.

Edit `ChangeLog.md` before invoking tbump:

```markdown
# Versions

## v0.4.0 <short title>

* Bullet per user-facing change (imperative mood)
* ...

## v0.3.0 Unit Tests for I2C/SPI
...
```

Rules:
- Header must be `## v{new_version} <title>` so `grep -q 0.4.0 ChangeLog.md` succeeds.
- Keep newest at top, preserve existing entries.
- One bullet per PR/issue; link issue if helpful.

### 3 — Dry-run

```bash
tbump --dry-run {new_version}
```

Inspect diff output for the two patched files. Expect:

- `CMakeLists.txt:4`  `VERSION 0.3.0` → `VERSION {new_version}`
- `build-support/share/cmake/embedded-superloop/embedded-superloop.cmake:5` same

If dry-run shows extra files or no diff, stop and investigate `tbump.toml` regex / file list.

### 4 — Bump

Interactive (default — prompts for confirmation):

```bash
tbump {new_version}
```

Non-interactive (scripts/CI, matches `tbump --help`):

```bash
tbump --non-interactive {new_version}
```

Useful variants:

```bash
tbump --dry-run {new_version}        # preview only, no git changes
tbump --only-patch {new_version}     # patch files only, skip git commit/tag/hooks
tbump --no-push {new_version}        # commit + tag locally, do not push
tbump --no-tag {new_version}         # commit only, skip tag creation
tbump --no-tag-push {new_version}    # create tag but do not push it
tbump -C <path> {new_version}        # run with different cwd
tbump -c <path.toml> {new_version}   # alternate config (e.g. third-party/libhypha)
```

Default success path (no flags) does: patch files → run `before_commit` hooks → `git commit -m "Bump to {new_version}"` → `git tag v{new_version}` → `git push` + `git push --tags`.

### 5 — Verify

```bash
tbump current-version                # should print {new_version}
grep -n "VERSION" CMakeLists.txt build-support/share/cmake/embedded-superloop/embedded-superloop.cmake
git log --oneline -3
git show --stat HEAD
git tag --list | grep "v{new_version}"
grep -q "{new_version}" ChangeLog.md && echo "changelog ok"
```

Optional but recommended before PR (per `AGENTS.md`):

```bash
cmake --workflow --preset on-host-native-llvm
cmake --workflow --preset on-host-native-clang
cmake --workflow --preset on-target-cortex-m4-gcc-arm-none-eabi-ci
cmake --workflow --preset on-target-cortex-m7-gcc-arm-none-eabi-ci
# or
python3 scripts/build-all-presets.py
```

### 6 — Push / PR

- If bump used `--no-push`, push explicitly when ready:

  ```bash
  git push
  git push --tags
  ```

- For `develop` workflow (AGENTS.md): branch `issue-<num>` tracking `develop`, PR against `develop`, run `scripts/build-all-presets.py` (or `build-all-presets.sh` if present) before pushing PR, delete branch after merge.
- Commit message must be `Bump to {new_version}` (from `message_template`). When appending human/AI attribution (per AGENTS.md "Before Committing"), keep the first line as the template and add `Co-authored-by:` / attribution in the body if needed.

## Commands reference

| Intent | Command |
|---|---|
| Show current | `tbump current-version` |
| Preview | `tbump --dry-run 0.4.0` |
| Bump patch | `tbump 0.3.1` |
| Bump minor | `tbump 0.4.0` |
| Bump major | `tbump 1.0.0` |
| CI / no prompt | `tbump --non-interactive 0.4.0` |
| Patch files only | `tbump --only-patch 0.4.0` |
| Local only | `tbump --no-push 0.4.0` |
| Init new tbump.toml | `tbump init 0.1.0` |

Full help: `tbump --help` (see `tbump --version` for 6.11.0).

## Changelog format

`ChangeLog.md` is the release notes source of truth. Keep it as:

```markdown
# Versions

## v0.4.0 Title

* Change one
* Change two

## v0.3.0 Unit Tests for I2C/SPI
...
```

`tbump` only checks `grep -q {new_version} ChangeLog.md` — any occurrence passes, but keep the `## vX.Y.Z` convention for consistency and tag linkage.

## Verification checklist

- [ ] `tbump current-version` matches `CMakeLists.txt:4` and `embedded-superloop.cmake:5`
- [ ] `ChangeLog.md` contains `v{new_version}` entry at top
- [ ] `tbump --dry-run {new_version}` diff looks correct (only two files)
- [ ] `git status` clean before bump
- [ ] After bump: `git log` shows `Bump to {new_version}`, `git tag` shows `v{new_version}`
- [ ] Cross presets still configure (at least `on-host-native-llvm` + one `on-target-*`)

## Troubleshooting

- **`before_commit` hook `grep -q {new_version} ChangeLog.md` failed** — you edited ChangeLog after tbump. Revert tbump's patches (`git checkout -- CMakeLists.txt build-support/.../embedded-superloop.cmake tbump.toml`), update ChangeLog first, then re-run `tbump`.
- **`tbump` says working tree dirty** — `git status --porcelain` must be empty. Commit or stash first; tbump never patches on dirty tree.
- **`Current version X does not match regex`** — `tbump.toml:current` drifted from file contents. Run `tbump current-version` and manually align the two CMake files to that version before retrying.
- **Tag already exists** — `git tag --list` shows `v{new_version}`. Delete locally (`git tag -d vX.Y.Z`) and remotely (`git push --delete origin vX.Y.Z`) only if the previous bump was not pushed to shared history; otherwise pick next version.
- **`tbump` not found** — install via `pipx install tbump` (repo uses `~/.local/bin/tbump`, not `venv/` or `.venv/`).
- **Submodule libhypha** — its `third-party/libhypha/tbump.toml` is independent. To bump libhypha: `tbump -C third-party/libhypha current-version` and `tbump -C third-party/libhypha {new_version}` — do not run from repo root with default config.

## References

- `tbump.toml` — version, regex, file list, hooks, tag/message templates
- `CMakeLists.txt:4` and `build-support/share/cmake/embedded-superloop/embedded-superloop.cmake:5` — patched files
- `ChangeLog.md` — release notes (must contain new_version)
- `AGENTS.md` — branch `issue-<num>` tracking `develop`, PR against `develop`, `scripts/build-all-presets.py`, commit attribution rules
- https://semver.org/ and `tbump --help`
