cmake_minimum_required(VERSION 3.10)
project(axonsurf VERSION 1.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()

# Pass version to C code
add_definitions(-DAXONSURF_VERSION="${PROJECT_VERSION}")

# Find required packages
find_package(PkgConfig REQUIRED)
find_package(X11 REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(WEBKIT REQUIRED webkit2gtk-4.1)
pkg_check_modules(JSONGLIB REQUIRED json-glib-1.0)
pkg_check_modules(CLIB REQUIRED libcurl)

# Source files — new directory structure
set(SOURCES
    # Core (browser init, command dispatch)
    src/core/main.c
    src/core/browser.c
    src/core/command.c

    # Page / UI core (eval, DOM, dialogs, storage ops, find-in-page)
    src/page.c

    # Commands (command handlers)

    # Feature implementations
    src/navigation/navigation.c
    src/elements/elements.c
    src/input/input.c
    src/input/humanize.c
    src/monitor/monitoring.c
    src/media/media.c
    src/media/screenshot.c
    src/media/video.c
    src/storage/profile.c
    src/extensions/extensions.c
    src/headless/headless.c
)

# Build
add_executable(axonsurf ${SOURCES})

set(TEST_SOURCES
    tests/test_runner.c
    tests/test_cmd_utils.c
    tests/test_profile.c
    tests/test_humanize.c
    tests/test_video.c
    src/page.c
    src/storage/profile.c
    src/input/input.c
    src/input/humanize.c
    src/media/video.c
)

add_executable(axonsurf_tests ${TEST_SOURCES})

target_include_directories(axonsurf PRIVATE
    ${GTK3_INCLUDE_DIRS}
    ${WEBKIT_INCLUDE_DIRS}
    ${JSONGLIB_INCLUDE_DIRS}
    ${CLIB_INCLUDE_DIRS}
    src
)

target_link_libraries(axonsurf PRIVATE
    ${GTK3_LIBRARIES}
    ${WEBKIT_LIBRARIES}
    ${JSONGLIB_LIBRARIES}
    ${CLIB_LIBRARIES}
    ${X11_LIBRARIES}
    m
)

target_include_directories(axonsurf_tests PRIVATE
    ${GTK3_INCLUDE_DIRS}
    ${WEBKIT_INCLUDE_DIRS}
    ${JSONGLIB_INCLUDE_DIRS}
    ${CLIB_INCLUDE_DIRS}
    src
)

target_link_libraries(axonsurf_tests PRIVATE
    ${GTK3_LIBRARIES}
    ${WEBKIT_LIBRARIES}
    ${JSONGLIB_LIBRARIES}
    ${CLIB_LIBRARIES}
    ${X11_LIBRARIES}
    m
)

target_compile_options(axonsurf PRIVATE
    ${GTK3_CFLAGS_OTHER}
    ${WEBKIT_CFLAGS_OTHER}
    ${JSONGLIB_CFLAGS_OTHER}
)

target_compile_options(axonsurf_tests PRIVATE
    ${GTK3_CFLAGS_OTHER}
    ${WEBKIT_CFLAGS_OTHER}
    ${JSONGLIB_CFLAGS_OTHER}
)

# Install
install(TARGETS axonsurf DESTINATION bin)

add_test(NAME native-tests COMMAND axonsurf_tests)
