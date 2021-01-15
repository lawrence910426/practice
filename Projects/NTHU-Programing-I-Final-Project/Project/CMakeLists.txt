cmake_minimum_required(VERSION 3.17)
project(Project C)

set(CMAKE_C_STANDARD 99)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Assets)
add_executable(Project Source/main.c include/physics_engine.h include/bullet_collision.h include/_utilities.h include/enemy.h include/boss.h include/render.h include/init.h include/plane.h include/scoring.h include/ultimate.h)

target_link_libraries(Project
        m
        allegro_acodec
        allegro_audio
        allegro_color
        allegro_dialog
        allegro_font
        allegro_image
        allegro_main
        allegro_memfile
        allegro_physfs
        allegro_primitives
        allegro
        allegro_ttf
        allegro_video
)

