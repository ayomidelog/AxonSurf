#include "../src/input/humanize.h"
#include "test_harness.h"

void test_humanize_config_bounds(void) {
    humanize_init();

    humanize_set_level(-10);
    HumanizeConfig *config = humanize_get_config();
    ASSERT_INT_EQ(config->level, 0, "humanize level should clamp low values to 0");

    humanize_set_level(150);
    ASSERT_INT_EQ(config->level, 100, "humanize level should clamp high values to 100");

    humanize_set_level(50);
    ASSERT_INT_EQ(config->level, 50, "humanize level should keep mid-range values");
    ASSERT_TRUE(config->mouse_movement, "mid-range level should enable mouse movement");
    ASSERT_TRUE(config->typing_jitter, "mid-range level should enable typing jitter");
}
