#include <webkit2/webkit-web-extension.h>
#include <webkitdom/webkitdom.h>
#include <glib.h>

static gboolean on_page_message_received(WebKitWebPage *page,
                                          WebKitUserMessage *message,
                                          gpointer user_data) {
    (void)user_data;

    const char *name = webkit_user_message_get_name(message);
    fprintf(stderr, "AxonSurf webext: received message %s\n", name ? name : "(null)");
    if (!g_strcmp0(name, "axonsurf-upload")) {
        GVariant *params = webkit_user_message_get_parameters(message);
        if (!params) {
            webkit_user_message_send_reply(
                message,
                webkit_user_message_new("axonsurf-upload-reply",
                                        g_variant_new("(bs)", FALSE, "missing_params")));
            return TRUE;
        }

        const gchar *selector = NULL;
        const gchar *filepath = NULL;
        g_variant_get(params, "(&s&s)", &selector, &filepath);
        if (!selector || !filepath) {
            webkit_user_message_send_reply(
                message,
                webkit_user_message_new("axonsurf-upload-reply",
                                        g_variant_new("(bs)", FALSE, "invalid_params")));
            return TRUE;
        }

        WebKitDOMDocument *document = webkit_web_page_get_dom_document(page);
        if (!document) {
            webkit_user_message_send_reply(
                message,
                webkit_user_message_new("axonsurf-upload-reply",
                                        g_variant_new("(bs)", FALSE, "no_document")));
            return TRUE;
        }

        GError *error = NULL;
        WebKitDOMElement *element = webkit_dom_document_query_selector(document, selector, &error);
        if (error || !element) {
            if (error) g_error_free(error);
            webkit_user_message_send_reply(
                message,
                webkit_user_message_new("axonsurf-upload-reply",
                                        g_variant_new("(bs)", FALSE, "selector_not_found")));
            return TRUE;
        }

        if (!WEBKIT_DOM_IS_HTML_INPUT_ELEMENT(element)) {
            webkit_user_message_send_reply(
                message,
                webkit_user_message_new("axonsurf-upload-reply",
                                        g_variant_new("(bs)", FALSE, "not_input_element")));
            return TRUE;
        }

        WebKitDOMHTMLInputElement *input = WEBKIT_DOM_HTML_INPUT_ELEMENT(element);
        gchar *input_type = webkit_dom_html_input_element_get_input_type(input);
        if (!input_type || g_ascii_strcasecmp(input_type, "file") != 0) {
            g_free(input_type);
            webkit_user_message_send_reply(
                message,
                webkit_user_message_new("axonsurf-upload-reply",
                                        g_variant_new("(bs)", FALSE, "not_file_input")));
            return TRUE;
        }
        g_free(input_type);

        // The legacy DOM API does not expose a way to construct a FileList from
        // arbitrary local files in the extension process. Report the current
        // limitation explicitly instead of pretending success.
        webkit_user_message_send_reply(
            message,
            webkit_user_message_new("axonsurf-upload-reply",
                                    g_variant_new("(bs)", FALSE, "filelist_assignment_unavailable")));
        return TRUE;
    }

    return FALSE;
}

static void on_page_created(WebKitWebExtension *extension,
                             WebKitWebPage *page,
                             gpointer user_data) {
    (void)extension;
    (void)user_data;
    fprintf(stderr, "AxonSurf webext: page created %" G_GUINT64_FORMAT "\n",
            webkit_web_page_get_id(page));
    g_signal_connect(page, "user-message-received",
                     G_CALLBACK(on_page_message_received), NULL);
}

G_MODULE_EXPORT void webkit_web_extension_initialize(WebKitWebExtension *extension) {
    fprintf(stderr, "AxonSurf webext: initialized\n");
    g_signal_connect(extension, "page-created",
                     G_CALLBACK(on_page_created), NULL);
}
