#ifndef TEST_HARNESS_H
#define TEST_HARNESS_H

#include <stdio.h>
#include <glib.h>

extern int g_failures;

#define ASSERT_TRUE(cond, msg) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, "FAIL: %s\n", msg); \
            g_failures++; \
        } \
    } while (0)

#define ASSERT_INT_EQ(actual, expected, msg) \
    do { \
        if ((actual) != (expected)) { \
            fprintf(stderr, "FAIL: %s (actual=%d expected=%d)\n", \
                    msg, (actual), (expected)); \
            g_failures++; \
        } \
    } while (0)

#define ASSERT_STR_EQ(actual, expected, msg) \
    do { \
        if (g_strcmp0((actual), (expected)) != 0) { \
            fprintf(stderr, "FAIL: %s (actual=%s expected=%s)\n", \
                    msg, (actual) ? (actual) : "(null)", \
                    (expected) ? (expected) : "(null)"); \
            g_failures++; \
        } \
    } while (0)

#endif
