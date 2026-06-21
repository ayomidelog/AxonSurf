# Roadmap

This roadmap reflects likely next areas of work. It is intended as a planning guide, not a release guarantee.

## v1.1 — Polish & Stability

- [ ] Fix extension injection race condition (currently requires explicit `extension-inject`)
- [ ] Add `--proxy` support to extension-level proxy switching
- [ ] Improve error messages (JSON error codes instead of raw strings)
- [ ] Fix `record-video` frame rate consistency
- [ ] Add `screenshot` quality/compression options
- [ ] Add `upload` drag-and-drop support

## v1.2 — Tabs & Multi-Page

- [ ] Strengthen tab lifecycle handling and isolation
- [ ] Multi-page support (each tab has its own context)
- [ ] Tab persistence across session restarts
- [ ] `tabs` returns full page info (title, URL, favicon)
- [ ] `tab-focus <index>` to switch active tab

## v1.3 — Advanced Input

- [ ] `scrollto <selector>` — smooth scroll to element
- [ ] `drag <selector-from> <selector-to>` — drag between elements
- [ ] `select <selector> <value>` — select dropdown option
- [ ] Improve file upload handling for real browser workflows
- [ ] `key <combo>` — modifier keys (Ctrl+C, Alt+Tab, etc.)
- [ ] `typeinto` with `--delay` for human-like typing

## v1.4 — Network & Monitoring

- [ ] Request interception (block/modify requests)
- [ ] Response body capture in net-log
- [ ] HAR export (network log → HAR file)
- [ ] WebSocket monitoring
- [ ] Console log capture (page console → file)
- [ ] `perf-timeline` — full performance timeline

## v1.5 — Extension System v2

- [ ] GES manifest v2 (permissions, background scripts, storage API)
- [ ] Extension popup UI (mini HTML overlay)
- [ ] Extension storage API (per-extension persistent storage)
- [ ] `extension-enable` / `extension-disable` without full reload
- [ ] Chrome Web Store compatibility layer (basic)

## v2.0 — Multi-Platform

- [ ] macOS support (via XQuartz or native WebKit)
- [ ] Windows support (via WSL2 or native WebView2)
- [ ] Docker image (`ghcr.io/axonsurf/axonsurf`)
- [ ] Flatpak / Snap packages
- [ ] Nix package

## v2.1 — AI Integration

- [ ] `ai-act <instruction>` — LLM-powered automation
- [ ] `ai-find <description>` — natural language element finding
- [ ] `ai-extract <schema>` — structured data extraction
- [ ] `ai-test <scenario>` — auto-generate and run test scenarios

## v2.2 — Distributed

- [ ] Multi-browser orchestration (run multiple instances)
- [ ] Cloud deployment (AWS/GCP/Azure)
- [ ] Session sharing between instances
- [ ] Load balancing across browser instances

## Non-Goals

These are explicitly **not** planned:

- ❌ Chromium/Firefox engine support (too complex, defeats purpose)
- ❌ GUI automation beyond browser (desktop automation is a different project)
- ❌ Commercial licensing (stays MIT)
- ❌ Mobile browser support (use Appium for that)
