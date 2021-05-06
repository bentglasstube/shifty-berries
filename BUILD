package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "shifty-berries",
    data = ["//content"],
    linkopts = [
        "-lSDL2",
        "-lSDL2_image",
        "-lSDL2_mixer",
        "-lnoise",
    ],
    srcs = ["main.cc"],
    deps = [
        ":game",
        ":screens",
    ],
)

# Basic framework objects

cc_library(
    name = "audio",
    srcs = ["audio.cc"],
    hdrs = ["audio.h"],
)

cc_library(
    name = "graphics",
    srcs = ["graphics.cc"],
    hdrs = ["graphics.h"],
)

cc_library(
    name = "input",
    srcs = ["input.cc"],
    hdrs = ["input.h"],
)

cc_library(
    name = "screen",
    srcs = ["screen.cc"],
    hdrs = ["screen.h"],
    deps = [
        ":audio",
        ":graphics",
        ":input",
    ]
)

cc_library(
    name = "game",
    srcs = ["game.cc"],
    hdrs = ["game.h"],
    deps = [
        ":audio",
        ":graphics",
        ":input",
        ":screen",
        ":screens",
        ":text",
    ],
)

# Graphical objects

cc_library(
    name = "animated_sprite",
    srcs = ["animated_sprite.cc"],
    hdrs = ["animated_sprite.h"],
    deps = [":sprite"],
)

cc_library(
    name = "backdrop",
    srcs = ["backdrop.cc"],
    hdrs = ["backdrop.h"],
    deps = [":graphics"],
)

cc_library(
    name = "box",
    srcs = ["box.cc"],
    hdrs = ["box.h"],
    deps = [":graphics"],
)

cc_library(
    name = "floating_text",
    srcs = ["floating_text.cc"],
    hdrs = ["floating_text.h"],
    deps = [
        ":text",
        ":objects",
    ],
)

cc_library(
    name = "parallax_backdrop",
    srcs = ["parallax_backdrop.cc"],
    hdrs = ["parallax_backdrop.h"],
    deps = [":graphics"],
)

cc_library(
    name = "sprite",
    srcs = ["sprite.cc"],
    hdrs = ["sprite.h"],
    deps = [":graphics"],
)

cc_library(
    name = "spritemap",
    srcs = ["spritemap.cc"],
    hdrs = ["spritemap.h"],
    deps = [":graphics"],
)

cc_library(
    name = "text",
    srcs = ["text.cc"],
    hdrs = ["text.h"],
    deps = [":graphics"],
)

cc_library(
    name = "screens",
    srcs = [
        "finish_screen.cc",
        "game_screen.cc",
        "title_screen.cc",
    ],
    hdrs = [
        "finish_screen.h",
        "game_screen.h",
        "title_screen.h",
    ],
    deps = [
        ":animals",
        ":animated_sprite",
        ":audio",
        ":backdrop",
        ":camera",
        ":map",
        ":parallax_backdrop",
        ":screen",
        ":text",
    ],
)

cc_library(
    name = "accelerators",
    srcs = ["accelerators.cc"],
    hdrs = ["accelerators.h"],
)

cc_library(
    name = "animals",
    srcs = [
        "bird.cc",
        "goat.cc",
        "human.cc",
    ],
    hdrs = [
        "bird.h",
        "goat.h",
        "human.h",
    ],
    deps = [
        ":animated_sprite",
        ":player",
    ],
)

cc_library(
    name = "camera",
    srcs = ["camera.cc"],
    hdrs = ["camera.h"],
    deps = [
        ":graphics",
        ":map",
        ":player",
    ],
)

cc_library(
    name = "map",
    srcs = ["map.cc"],
    hdrs = ["map.h"],
    deps = [
        ":graphics",
        ":rect",
        ":sign",
        ":spritemap",
    ],
)

cc_library(
    name = "player",
    srcs = ["player.cc"],
    hdrs = ["player.h"],
    deps = [
        ":accelerators",
        ":audio",
        ":map",
        ":sprite",
    ],
)

cc_library(
    name = "rect",
    hdrs = ["rect.h"],
)

cc_library(
    name = "sign",
    hdrs = ["sign.h"],
    srcs = ["sign.cc"],
    deps = [
        ":rect",
        ":text",
    ],
)
