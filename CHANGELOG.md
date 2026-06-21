# Changelog

All notable changes to AxonSurf will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).

## [Unreleased]

### Changed

- Updated the build and packaging flow to use WebKitGTK 4.1 on current Ubuntu releases
- Improved headless startup so AxonSurf verifies display usability before relying on `DISPLAY`
- Defaulted headless launches without `--socket` to `/tmp/axonsurf.sock`
- Reworked the test setup to include both native C tests and the end-to-end shell suite
- Updated CI to run `ctest` and the current shell-based integration checks

### Fixed

- Fixed `history-goto` index handling
- Fixed `elements` command execution
- Fixed `wait ... --state ...` command handling
- Fixed extension injection to use the loaded extension set rather than a hard-coded path
- Hardened command and page helper paths that previously embedded unescaped values into JavaScript
- Stabilized the test harness server launch and socket client behavior

### Added

- Added compiled native tests under `tests/`, wired into CMake/CTest

## [1.0.0] — 2025-06-18

### Added

**Core**
- Native-input browser automation via WebKitGTK
- Persistent Unix socket for command execution
- Headless mode with auto-Xvfb
- 59 commands across 12 categories

**Navigation**
- `goto`, `back`, `forward`, `reload`
- `url`, `title`, `text`, `content`
- `scroll`, `scrollto`
- `history`, `history-goto`

**Input**
- `click`, `doubleclick`, `rightclick`
- `type`, `typeinto`, `key`
- `hover`, `drag`

**Elements**
- `find`, `elements`, `count`
- `read`, `find-text`, `find-count`
- `role-click`, `role-type`, `role-find`
- `inspect`, `a11y-audit`

**Screenshots & Media**
- `screenshot` (full page and viewport)
- `pdf` export
- `upload` file upload
- `check` / `uncheck` checkboxes
- `record` video recording

**Tabs**
- `tabs`, `newtab`, `tab`, `closetab`

**Storage**
- `ls-set`, `ls-get`, `ls-all` (localStorage)
- `ss-set`, `ss-get` (sessionStorage)

**Extensions**
- GES (General Extension Standard) support
- `extension-load`, `extension-inject`, `extension-list`
- Content scripts with `==GES==` headers
- 8 example extensions included

**Monitoring**
- Network request logging (`net-log`, `net-requests`)
- Performance timing (`perf-timing`, `perf-memory`)
- SSL info (`ssl`)
- Download tracking (`downloads`)

**Window**
- `resize`, `viewport`
- `maximize`, `minimize`, `fullscreen`
- `center`

**Other**
- `eval` — execute JavaScript
- `wait`, `waitload`, `waitfor`
- `clipboard read/write`
- `dismiss` — auto-dismiss overlays
- `humanize` — human-like text input
- `help` — command reference

**CLI**
- `axonsurf` bash CLI tool
- Auto-start headless mode
- Environment variables (`AXON_SOCK`, `AXON_PROXY`, `AXON_UA`)

**GUI**
- GTK window with navigation bar (back/forward/reload)
- URL entry field
- Tab bar

**Build**
- CMake build system
- WebKitGTK, GTK3, json-glib, libcurl dependencies
