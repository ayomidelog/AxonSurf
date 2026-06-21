#include <glib.h>

#include "test_harness.h"
#include "../src/storage/profile.h"

void test_profile_paths(void) {
    const char *home = g_get_home_dir();
    char *expected_default = g_strdup_printf("%s/.local/share/axonsurf/default", home);
    char *expected_named = g_strdup_printf("%s/.local/share/axonsurf/test-profile", home);
    char *default_path = profile_get_default_path();
    char *named_path = profile_get_path("test-profile");
    char *fallback_path = profile_get_path(NULL);

    ASSERT_STR_EQ(default_path, expected_default, "default profile path should use HOME");
    ASSERT_STR_EQ(named_path, expected_named, "named profile path should append profile name");
    ASSERT_STR_EQ(fallback_path, expected_default, "NULL profile should fall back to default path");

    g_free(expected_default);
    g_free(expected_named);
    g_free(default_path);
    g_free(named_path);
    g_free(fallback_path);
}
