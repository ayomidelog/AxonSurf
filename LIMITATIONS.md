# Limitations

AxonSurf is a focused browser automation tool, and some tradeoffs are intentional. The constraints below describe the current implementation rather than long-term product direction.

## Display and Runtime

- **Requires an X11-compatible display path** — either a real X11 display or a virtual framebuffer such as Xvfb
- **Headless mode depends on Xvfb** — AxonSurf can start it automatically, but it still needs to be installed on the system
- **Wayland is not a first-class target** — current automation assumptions are built around X11-style display handling

## Browser Engine

- **WebKitGTK only** — this is not a Chromium- or Firefox-based automation stack, so rendering and compatibility will differ on some sites
- **Engine behavior follows the platform WebKitGTK package** — site behavior can vary with distribution package versions
- **Single application instance per process** — a crash still terminates the active browser instance

## Input Simulation

- **Visibility still matters** — coordinate-based interaction assumes the target is rendered and reachable
- **Cross-origin iframe support is limited**
- **Complex SPA event models can still be inconsistent** even with the current input and DOM event bridging

## Networking

- **No request interception layer yet** — requests cannot currently be rewritten or blocked in-flight
- **Proxy support is basic** — authentication and protocol coverage are not on par with dedicated interception proxies

## Extensions

- **GES-only extension model** — this is a project-specific format, not a Chrome or Firefox extension runtime
- **No popup or browser-action UI**
- **No background process model** — extensions execute in page context
- **Shared runtime assumptions** — extension isolation is limited

## Platform Support

- **Linux only**
- **x86_64 and ARM64 are the primary targets**
- **Debian/Ubuntu are the best-supported environments today**

## Performance

- **Command handling is sequential**
- **Memory use can grow quickly on large or long-lived pages**
- **Startup and rendering costs are tied to WebKitGTK and the local display stack**

## Security

- **No extension sandboxing**
- **The command socket is local only and does not add an authentication layer**
- **Injected extension code has broad page access**

## Non-Goals

- Not a general-purpose browser for daily use
- Not a replacement for Chrome/Firefox
- Not a full browser testing framework by itself, even though it can be used in testing pipelines
- Not designed for video streaming or complex web apps

## Known Issues

- Some SPA navigation patterns may still require explicit waits
- Cookie handling does not provide access to `HttpOnly` cookies through page JavaScript
- Video recording frame rate can vary under load
- Accessibility output is best-effort and may be incomplete on complex pages
