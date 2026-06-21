# AxonSurf

AxonSurf is a browser automation tool built on WebKitGTK. It drives pages through native-style browser and input operations, exposes a persistent command socket, and supports headless execution through Xvfb.

## Highlights

- WebKitGTK-based browser automation in C
- Persistent Unix socket command interface
- Headless mode with automatic Xvfb startup when needed
- Navigation, DOM querying, input, screenshots, tabs, storage, monitoring, and extensions
- Scriptable extension loading and injection
- Profile, cookie, proxy, and user-agent support

## Build

### Dependencies

On Ubuntu or Debian:

```bash
sudo apt-get install -y \
  build-essential \
  cmake \
  pkg-config \
  libgtk-3-dev \
  libwebkit2gtk-4.1-dev \
  libjson-glib-dev \
  libcurl4-openssl-dev \
  xvfb \
  openbox \
  socat
```

### Compile

```bash
cmake -S . -B build
cmake --build build -j"$(nproc)"
```

The main binary is produced at:

```bash
./build/axonsurf
```

## Quick Start

### Windowed mode

```bash
./build/axonsurf https://example.com
```

### Headless mode

```bash
./build/axonsurf --headless https://example.com
```

In headless mode:

- AxonSurf starts Xvfb automatically if no usable display is available.
- If `--socket` is not provided, it defaults to `/tmp/axonsurf.sock`.

### Send commands

```bash
printf 'url\n' | socat - UNIX-CONNECT:/tmp/axonsurf.sock
printf 'title\n' | socat - UNIX-CONNECT:/tmp/axonsurf.sock
printf 'screenshot /tmp/page.png\n' | socat - UNIX-CONNECT:/tmp/axonsurf.sock
```

To use a custom socket:

```bash
./build/axonsurf --headless --socket /tmp/my.sock https://example.com
printf 'url\n' | socat - UNIX-CONNECT:/tmp/my.sock
```

## Common Commands

### Navigation

- `goto <url>`
- `back`
- `forward`
- `url`
- `title`
- `text`
- `content`
- `history`
- `history-goto <index>`

### Input

- `click <x> <y>`
- `click <selector>`
- `doubleclick <x> <y>`
- `rightclick <x> <y>`
- `type <text>`
- `typeinto <selector> <text>`
- `key <key>`
- `hover <selector>`
- `scroll <x> <y>`
- `scrollto <selector>`

### Elements

- `find <selector>`
- `elements`
- `count <selector>`
- `read <selector>`
- `role-find <role>`
- `role-click <role>`
- `role-type <role> <text>`
- `inspect`
- `a11y-audit`

### Media and Files

- `screenshot <file>`
- `screenshot viewport <file>`
- `screenshot element <selector> <file>`
- `pdf <file>`
- `upload <selector> <file>`
- `record-video start <file> [fps]`
- `record-video status`
- `record-video stop`

### Storage and Tabs

- `ls-set <key> <value>`
- `ls-get <key>`
- `ls-all`
- `ss-set <key> <value>`
- `ss-get <key>`
- `tabs`
- `newtab [url]`
- `tab <index>`
- `closetab <index>`

### Monitoring

- `net-log`
- `net-requests`
- `net-stop`
- `perf-timing`
- `perf-memory`
- `ssl`

### Utilities

- `resize <w> <h>`
- `viewport <w> <h>`
- `eval <js>`
- `waitfor <selector> <timeout_ms>`
- `waitload <timeout_ms>`
- `dismiss`
- `clipboard read`
- `clipboard write <text>`
- `help`

## Extensions

AxonSurf can load JavaScript extensions from a directory and inject them into matching pages.

Example workflow:

```bash
printf 'extension-load /path/to/extensions\n' | socat - UNIX-CONNECT:/tmp/axonsurf.sock
printf 'extension-list\n' | socat - UNIX-CONNECT:/tmp/axonsurf.sock
printf 'extension-inject\n' | socat - UNIX-CONNECT:/tmp/axonsurf.sock
```

Example metadata header:

```javascript
// ==GES==
// @name        Example Extension
// @version     1.0.0
// @match       https://*/*
// @run-at      document-end
// ==/GES==

(function () {
  console.log("AxonSurf extension loaded");
})();
```

## Testing

The repository includes an end-to-end shell test suite that builds the binary, starts a headless instance, and exercises the socket interface.

Run it with:

```bash
bash tests/run_tests.sh
```

The suite currently uses:

- `Xvfb`
- `openbox`
- `socat`

## Repository Layout

```text
src/core/         application startup, browser state, command server
src/page.c        shared page helpers and JS execution
src/navigation/   history and viewport helpers
src/elements/     selector and accessibility helpers
src/input/        mouse, keyboard, and humanization
src/media/        screenshots, file input, video helpers
src/storage/      profiles, cookies, proxy support
src/extensions/   extension loading and injection
src/headless/     Xvfb management
src/monitor/      performance, network, and audit helpers
tests/            shell-based end-to-end test suite
```

## Notes

- Headless mode prefers a working existing `DISPLAY` and falls back to a private Xvfb instance when necessary.
- The command interface is line-oriented over a Unix domain socket.
- Some warnings from Xvfb/XKB can appear during automated runs; the current test suite treats them as non-fatal.

## License

MIT
