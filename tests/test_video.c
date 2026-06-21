#include "../src/media/video.h"
#include "test_harness.h"

void test_video_default_state(void) {
    ASSERT_TRUE(!video_is_recording(), "recording should be inactive by default");
    ASSERT_TRUE(video_get_output() == NULL, "output path should be NULL before recording starts");
}
