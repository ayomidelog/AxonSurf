#include <stdio.h>
#include <stdlib.h>

int g_failures = 0;

void test_cmd_json_helpers(void);
void test_cmd_clean_eval_result(void);
void test_cmd_coord_detection(void);
void test_cmd_parse_element_center(void);
void test_profile_paths(void);
void test_humanize_config_bounds(void);
void test_video_default_state(void);

int main(void) {
    test_cmd_json_helpers();
    test_cmd_clean_eval_result();
    test_cmd_coord_detection();
    test_cmd_parse_element_center();
    test_profile_paths();
    test_humanize_config_bounds();
    test_video_default_state();

    if (g_failures > 0) {
        fprintf(stderr, "%d test(s) failed\n", g_failures);
        return EXIT_FAILURE;
    }

    printf("All native tests passed\n");
    return EXIT_SUCCESS;
}
