#include "media.h"
#include "page.h"
#include "input/input.h"
#include <string.h>
#include <stdlib.h>
#include <glib/gstdio.h>

// === Checkbox/Radio ===

void page_check(WebKitWebView *web_view, const char *selector) {
    if (!web_view || !selector) return;
    char *selector_js = page_js_quote(selector);
    char *js = g_strdup_printf(
        "(function(){"
        "  var el = document.querySelector(%s);"
        "  if(!el) return false;"
        "  el.checked = true;"
        "  el.dispatchEvent(new Event('change', {bubbles: true}));"
        "  return true;"
        "})()", selector_js);
    char *res = page_eval_js(web_view, js);
    g_free(res);
    g_free(js);
    g_free(selector_js);
}

void page_uncheck(WebKitWebView *web_view, const char *selector) {
    if (!web_view || !selector) return;
    char *selector_js = page_js_quote(selector);
    char *js = g_strdup_printf(
        "(function(){"
        "  var el = document.querySelector(%s);"
        "  if(!el) return false;"
        "  el.checked = false;"
        "  el.dispatchEvent(new Event('change', {bubbles: true}));"
        "  return true;"
        "})()", selector_js);
    char *res = page_eval_js(web_view, js);
    g_free(res);
    g_free(js);
    g_free(selector_js);
}

bool page_is_checked(WebKitWebView *web_view, const char *selector) {
    if (!web_view || !selector) return false;
    char *selector_js = page_js_quote(selector);
    char *js = g_strdup_printf(
        "(function(){ var el = document.querySelector(%s); return el ? el.checked : false; })()",
        selector_js);
    char *res = page_eval_js(web_view, js);
    bool checked = (res && strstr(res, "true"));
    g_free(res);
    g_free(js);
    g_free(selector_js);
    return checked;
}

// === File Upload ===

bool page_upload_file(BrowserState *state, const char *selector, const char *filepath) {
    if (!state || !state->web_view || !selector || !filepath) return false;
    if (!g_file_test(filepath, G_FILE_TEST_EXISTS)) return false;

    gchar *file_bytes = NULL;
    gsize file_size = 0;
    GError *error = NULL;
    if (!g_file_get_contents(filepath, &file_bytes, &file_size, &error)) {
        if (error) {
            fprintf(stderr, "AxonSurf: upload failed (%s)\n", error->message);
            g_error_free(error);
        }
        return false;
    }

    gchar *base64 = g_base64_encode((const guchar *)file_bytes, file_size);
    g_free(file_bytes);

    char *selector_js = page_js_quote(selector);
    char *basename = g_path_get_basename(filepath);
    char *name_js = page_js_quote(basename);
    char *base64_js = page_js_quote(base64);
    g_free(base64);

    char *js = g_strdup_printf(
        "(function(){"
        "  var el = document.querySelector(%s);"
        "  if(!el || el.type !== 'file') return false;"
        "  function b64ToBytes(b64) {"
        "    var bin = atob(b64);"
        "    var bytes = new Uint8Array(bin.length);"
        "    for (var i = 0; i < bin.length; i++) bytes[i] = bin.charCodeAt(i);"
        "    return bytes;"
        "  }"
        "  var file = new File([b64ToBytes(%s)], %s);"
        "  var dt = new DataTransfer();"
        "  dt.items.add(file);"
        "  var proto = Object.getPrototypeOf(el);"
        "  var desc = null;"
        "  while(proto && !desc) {"
        "    desc = Object.getOwnPropertyDescriptor(proto, 'files');"
        "    proto = Object.getPrototypeOf(proto);"
        "  }"
        "  if(desc && desc.set) desc.set.call(el, dt.files);"
        "  else el.files = dt.files;"
        "  el.dispatchEvent(new Event('input', {bubbles: true}));"
        "  el.dispatchEvent(new Event('change', {bubbles: true}));"
        "  return el.files && el.files.length > 0;"
        "})()",
        selector_js, base64_js, name_js);

    char *result = page_eval_js(state->web_view, js);
    bool ok = false;
    if (result) {
        if (strstr(result, "true")) {
            ok = true;
        } else if (strstr(result, "\"true\"")) {
            ok = true;
        } else if (strstr(result, "1")) {
            ok = true;
        }
    }
    g_free(result);
    g_free(js);
    g_free(selector_js);
    g_free(name_js);
    g_free(base64_js);

    if (!ok) {
        return false;
    }

    g_free(basename);
    return true;
}

// === Drag and Drop Simulation ===

void page_drag(WebKitWebView *web_view, int sx, int sy, int ex, int ey) {
    if (!web_view) return;

    // Simulate drag via mouse events at source, move, then target
    input_mouse_down(web_view, sx, sy);
    g_usleep(100000); // 100ms hold

    // Move in steps
    int steps = 20;
    for (int i = 1; i <= steps; i++) {
        int x = sx + (ex - sx) * i / steps;
        int y = sy + (ey - sy) * i / steps;
        input_mouse_move(web_view, x, y);
        g_usleep(20000); // 20ms per step
    }

    g_usleep(100000); // 100ms pause at target
    input_mouse_up(web_view, ex, ey);
}

// === PDF Export ===

bool page_export_pdf(WebKitWebView *web_view, const char *filepath) {
    if (!web_view || !filepath) return false;

    // Save via JS: create a blob and trigger download
    char *js = g_strdup_printf(
        "(function(){"
        "  var printWindow = window.open('', '_blank');"
        "  printWindow.document.write(document.documentElement.outerHTML);"
        "  printWindow.document.close();"
        "  printWindow.print();"
        "  return 'print_dialog_opened';"
        "})()");
    char *res = page_eval_js(web_view, js);
    g_free(res);
    g_free(js);

    // Also save the page HTML to a .html file as fallback
    char *html = page_get_content(web_view, true);
    if (html) {
        FILE *f = fopen(filepath, "w");
        if (f) {
            fprintf(f, "%s", html);
            fclose(f);
            g_free(html);
            return true;
        }
        g_free(html);
    }
    return false;
}
