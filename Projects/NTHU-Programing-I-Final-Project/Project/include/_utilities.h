//
// Created by root on 2021/1/15.
//

#ifndef PROJECT_UTILITIES_H
#define PROJECT_UTILITIES_H

#endif //PROJECT_UTILITIES_H


#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))


/* Constants. */

// Frame rate (frame per second)
const int FPS = 60;
// Display (screen) width.
const int SCREEN_W = 800;
// Display (screen) height.
const int SCREEN_H = 600;
// At most 10 audios can be played at a time.
const int RESERVE_SAMPLES = 10;
// Same as:
// const int SCENE_MENU = 1;
// const int SCENE_START = 2;
enum {
    SCENE_MENU = 1,
    SCENE_START = 2,
    // [HACKATHON 3-7]
    // TODO: Declare a new scene id.
    SCENE_SETTINGS = 3,
    SCENE_WIN = 4
};

/* Input states */

// The active scene id.
int active_scene;
// Keyboard state, whether the key is down or not.
bool key_state[ALLEGRO_KEY_MAX];
// Mouse state, whether the key is down or not.
// 1 is for left, 2 is for right, 3 is for middle.
bool *mouse_state;
// Mouse position.
int mouse_x, mouse_y;
// TODO: More variables to store input states such as joysticks, ...

/* Variables for allegro basic routines. */

ALLEGRO_DISPLAY* game_display;
ALLEGRO_EVENT_QUEUE* game_event_queue;
ALLEGRO_TIMER* game_update_timer;

/* Shared resources*/

ALLEGRO_FONT* font_pirulen_32;
ALLEGRO_FONT* font_pirulen_24;
// TODO: More shared resources or data that needed to be accessed
// across different scenes.

/* Menu Scene resources*/
ALLEGRO_BITMAP* main_img_background;
// [HACKATHON 3-1]
// TODO: Declare 2 variables for storing settings images.
// Uncomment and fill in the code below.
ALLEGRO_BITMAP* img_settings;
ALLEGRO_BITMAP* img_settings2;

/* Start Scene resources*/
ALLEGRO_BITMAP* start_img_background;
ALLEGRO_BITMAP* start_img_plane;
ALLEGRO_BITMAP* start_img_enemy;

ALLEGRO_BITMAP* winning_background;
// [HACKATHON 2-1]
// TODO: Declare a variable to store your bullet's image.
// Uncomment and fill in the code below.
ALLEGRO_BITMAP* img_bullet;

typedef struct {
    // The center coordinate of the image.
    float x, y;
    // The width and height of the object.
    float w, h;
    // The velocity in x, y axes.
    float vx, vy;
    // Should we draw this object on the screen.
    bool hidden;
    // The pointer to the object’s image.
    ALLEGRO_BITMAP* img;
    // The health of the plane
    int health;
} MovableObject;
#define MAX_ENEMY_BULLET 30
MovableObject enemy_bullet[MAX_ENEMY_BULLET];

void draw_movable_object(MovableObject obj);
#define MAX_ENEMY 10
// [HACKATHON 2-2]
// TODO: Declare the max bullet count that will show on screen.
// You can try max 4 bullets here and see if you needed more.
// Uncomment and fill in the code below.
#define MAX_BULLET 4
MovableObject plane;
MovableObject enemies[MAX_ENEMY];
// [HACKATHON 2-3]
// TODO: Declare an array to store bullets with size of max bullet count.
// Uncomment and fill in the code below.
MovableObject bullets[MAX_BULLET];
// [HACKATHON 2-4]
// TODO: Set up bullet shooting cool-down variables.
// 1) Declare your shooting cool-down time as constant. (0.2f will be nice)
// 2) Declare your last shoot timestamp.
// Uncomment and fill in the code below.
const float MAX_COOLDOWN = 0.2;
double last_shoot_timestamp;

MovableObject boss;


float time_coefficient = 1;
int score;
int history_high_score;

#define MAX_BOSS_BULLETS 100
MovableObject boss_bullets[MAX_BOSS_BULLETS];



bool allow_spawn_enemy = true;
const int spawn_enemy_interval = 100;
int spawn_enemy_runned_frames = 0;

const int enemy_trajectory_update_interval = 10;
int enemy_trajectory_runned_frames = 0;



const int move_boss_shoot_bullet = 100;
int runned_boss_shoot_bullet = 0;

const int move_boss_interval = 30;
int runned_move_boss_interval = 0;


bool pnt_in_rect(int px, int py, int x, int y, int w, int h) {
    return x <= px && px <= x + w && y <= py && py <= y + h;
}

int random_uniform(int l, int r) { return rand() % (r - l + 1) - ((r - l + 1) / 2); }

ALLEGRO_BITMAP *load_bitmap_resized(const char *filename, int w, int h) {
    ALLEGRO_BITMAP* loaded_bmp = al_load_bitmap(filename);
    if (!loaded_bmp)
        game_abort("failed to load image: %s", filename);
    ALLEGRO_BITMAP *resized_bmp = al_create_bitmap(w, h);
    ALLEGRO_BITMAP *prev_target = al_get_target_bitmap();

    if (!resized_bmp)
        game_abort("failed to create bitmap when creating resized image: %s", filename);
    al_set_target_bitmap(resized_bmp);
    al_draw_scaled_bitmap(loaded_bmp, 0, 0,
                          al_get_bitmap_width(loaded_bmp),
                          al_get_bitmap_height(loaded_bmp),
                          0, 0, w, h, 0);
    al_set_target_bitmap(prev_target);
    al_destroy_bitmap(loaded_bmp);

    game_log("resized image: %s", filename);

    return resized_bmp;
}