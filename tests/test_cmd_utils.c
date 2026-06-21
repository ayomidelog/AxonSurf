#include <glib.h>

#include "test_harness.h"
#include "../src/commands/cmd_utils.h"

void test_cmd_json_helpers(void) {
    char *ok = cmd_json_ok();
    char *err = cmd_json_error("boom");

    ASSERT_STR_EQ(ok, "{\"ok\":\"true\"}", "cmd_json_ok should return expected JSON");
    ASSERT_STR_EQ(err, "{\"error\":\"boom\"}", "cmd_json_error should return expected JSON");

    g_free(ok);
    g_free(err);
}

void test_cmd_clean_eval_result(void) {
    char *quoted = g_strdup("\"Example Domain\"");
    char *plain = g_strdup("true");
    char *cleaned_quoted = cmd_clean_eval_result(quoted);
    char *cleaned_plain = cmd_clean_eval_result(plain);

    ASSERT_STR_EQ(cleaned_quoted, "Example Domain", "quoted eval result should unwrap");
    ASSERT_STR_EQ(cleaned_plain, "true", "plain eval result should remain unchanged");

    g_free(cleaned_quoted);
    g_free(cleaned_plain);
}

void test_cmd_coord_detection(void) {
    ASSERT_TRUE(cmd_is_coord("123"), "positive integer should be detected as coordinate");
    ASSERT_TRUE(cmd_is_coord("-45"), "negative integer should be detected as coordinate");
    ASSERT_TRUE(!cmd_is_coord("abc"), "text should not be detected as coordinate");
    ASSERT_TRUE(!cmd_is_coord("-x"), "invalid negative token should not be detected as coordinate");
}

void test_cmd_parse_element_center(void) {
    int x = 0;
    int y = 0;
    char *valid = g_strdup("{\"x\":42,\"y\":99}");
    char *invalid = g_strdup("{\"error\":\"not_found\"}");

    ASSERT_TRUE(cmd_parse_element_center(valid, &x, &y) == 1,
                "valid element JSON should parse");
    ASSERT_INT_EQ(x, 42, "parsed x coordinate should match");
    ASSERT_INT_EQ(y, 99, "parsed y coordinate should match");

    ASSERT_TRUE(cmd_parse_element_center(invalid, &x, &y) == 0,
                "error element JSON should fail to parse");
}
