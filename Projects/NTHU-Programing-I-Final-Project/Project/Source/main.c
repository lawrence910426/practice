// [main.c]
// this template is provided for the 2D shooter game.
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/mouse.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

// If defined, logs will be shown on console and written to file.
// If commented out, logs will not be shown nor be saved.
#define LOG_ENABLED

extern volatile int mouse_b;

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
    SCENE_START = 2
    // [HACKATHON 3-7]
    // TODO: Declare a new scene id.
    , SCENE_SETTINGS = 3
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
ALLEGRO_SAMPLE* main_bgm;
ALLEGRO_SAMPLE_ID main_bgm_id;

/* Start Scene resources*/
ALLEGRO_BITMAP* start_img_background;
ALLEGRO_BITMAP* start_img_plane;
ALLEGRO_BITMAP* start_img_enemy;
ALLEGRO_SAMPLE* start_bgm;
ALLEGRO_SAMPLE_ID start_bgm_id;
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

/* Declare function prototypes. */

// Initialize allegro5 library
void allegro5_init(void);
// Initialize variables and resources.
// Allows the game to perform any initialization it needs before
// starting to run.
void game_init(void);
// Process events inside the event queue using an infinity loop.
void game_start_event_loop(void);
// Run game logic such as updating the world, checking for collision,
// switching scenes and so on.
// This is called when the game should update its logic.
void game_update(void);
// Draw to display.
// This is called when the game should draw itself.
void game_draw(void);
// Release resources.
// Free the pointers we allocated.
void game_destroy(void);
// Function to change from one scene to another.
void game_change_scene(int next_scene);
// Load resized bitmap and check if failed.
ALLEGRO_BITMAP *load_bitmap_resized(const char *filename, int w, int h);
// [HACKATHON 3-2]
// TODO: Declare a function.
// Determines whether the point (px, py) is in rect (x, y, w, h).
// Uncomment the code below.
bool pnt_in_rect(int px, int py, int x, int y, int w, int h);

/* Event callbacks. */
void on_key_down(int keycode);
void on_mouse_down(int btn, int x, int y);

/* Declare function prototypes for debugging. */

// Display error message and exit the program, used like 'printf'.
// Write formatted output to stdout and file from the format string.
// If the program crashes unexpectedly, you can inspect "log.txt" for
// further information.
void game_abort(const char* format, ...);
// Log events for later debugging, used like 'printf'.
// Write formatted output to stdout and file from the format string.
// You can inspect "log.txt" for logs in the last run.
void game_log(const char* format, ...);
// Log using va_list.
void game_vlog(const char* format, va_list arg);
void game_update_calls();
void main_scene_start();
void score_board();


int main(int argc, char** argv) {
    // Set random seed for better random outcome.
    srand(time(NULL));
    allegro5_init();
    game_log("Allegro5 initialized");
    game_log("Game begin");
    // Initialize game variables.
    game_init();
    game_log("Game initialized");
    // Draw the first frame.
    game_draw();
    game_log("Game start event loop");
    // This call blocks until the game is finished.
    game_start_event_loop();
    game_log("Game end");
    game_destroy();
    return 0;
}

void allegro5_init(void) {
    if (!al_init())
        game_abort("failed to initialize allegro");

    // Initialize add-ons.
    if (!al_init_primitives_addon())
        game_abort("failed to initialize primitives add-on");
    if (!al_init_font_addon())
        game_abort("failed to initialize font add-on");
    if (!al_init_ttf_addon())
        game_abort("failed to initialize ttf add-on");
    if (!al_init_image_addon())
        game_abort("failed to initialize image add-on");
#ifdef audio
    if (!al_install_audio())
       game_abort("failed to initialize audio add-on");
    if (!al_init_acodec_addon())
        game_abort("failed to initialize audio codec add-on");
    if (!al_reserve_samples(RESERVE_SAMPLES))
        game_abort("failed to reserve samples");
#endif
    if (!al_install_keyboard())
        game_abort("failed to install keyboard");
    if (!al_install_mouse())
        game_abort("failed to install mouse");
    // TODO: Initialize other addons such as video, ...

    // Setup game display.
    game_display = al_create_display(SCREEN_W, SCREEN_H);
    if (!game_display)
        game_abort("failed to create display");
    al_set_window_title(game_display, "I2P(I)_2020 Final Project <student_id>");

    // Setup update timer.
    game_update_timer = al_create_timer(1.0f / FPS);
    if (!game_update_timer)
        game_abort("failed to create timer");

    // Setup event queue.
    game_event_queue = al_create_event_queue();
    if (!game_event_queue)
        game_abort("failed to create event queue");

    // Malloc mouse buttons state according to button counts.
    const unsigned m_buttons = al_get_mouse_num_buttons();
    game_log("There are total %u supported mouse buttons", m_buttons);
    // mouse_state[0] will not be used.
    mouse_state = malloc((m_buttons + 1) * sizeof(bool));
    memset(mouse_state, false, (m_buttons + 1) * sizeof(bool));

    // Register display, timer, keyboard, mouse events to the event queue.
    al_register_event_source(game_event_queue, al_get_display_event_source(game_display));
    al_register_event_source(game_event_queue, al_get_timer_event_source(game_update_timer));
    al_register_event_source(game_event_queue, al_get_keyboard_event_source());
    al_register_event_source(game_event_queue, al_get_mouse_event_source());
    // TODO: Register other event sources such as timer, video, ...

    // Start the timer to update and draw the game.
    al_start_timer(game_update_timer);
}

void game_init(void) {
    srand(0);
    /* Shared resources*/
    font_pirulen_32 = al_load_font("pirulen.ttf", 32, 0);
    if (!font_pirulen_32)
        game_abort("failed to load font: pirulen.ttf with size 32");

    font_pirulen_24 = al_load_font("pirulen.ttf", 24, 0);
    if (!font_pirulen_24)
        game_abort("failed to load font: pirulen.ttf with size 24");

    /* Menu Scene resources*/
    main_img_background = load_bitmap_resized("main-bg.jpg", SCREEN_W, SCREEN_H);


#ifdef audio
    main_bgm = al_load_sample("S31-Night Prowler.ogg");
    if (!main_bgm)
        game_abort("failed to load audio: S31-Night Prowler.ogg");
#endif

    // [HACKATHON 3-4]
    // TODO: Load settings images.
    // Don't forget to check their return values.
    // Uncomment and fill in the code below.
    img_settings = al_load_bitmap("settings.png");
    if (!img_settings)
        game_abort("failed to load image: settings.png");
    img_settings2 = al_load_bitmap("settings2.png");
    if (!img_settings2)
        game_abort("failed to load image: settings2.png");

    /* Start Scene resources*/
    start_img_background = load_bitmap_resized("start-bg.jpg", SCREEN_W, SCREEN_H);

    start_img_plane = al_load_bitmap("plane.png");
    if (!start_img_plane)
        game_abort("failed to load image: plane.png");

    start_img_enemy = al_load_bitmap("smallfighter0006.png");
    if (!start_img_enemy)
        game_abort("failed to load image: smallfighter0006.png");

#ifdef audio
    start_bgm = al_load_sample("mythica.ogg");
    if (!start_bgm)
        game_abort("failed to load audio: mythica.ogg");
#endif

    // [HACKATHON 2-5]
    // TODO: Initialize bullets.
    // 1) Search for a bullet image online and put it in your project.
    //    You can use the image we provided.
    // 2) Load it in by 'al_load_bitmap' or 'load_bitmap_resized'.
    // 3) If you use 'al_load_bitmap', don't forget to check its return value.
    // Uncomment and fill in the code below.
    img_bullet = al_load_bitmap("image12.png");
    if (!img_bullet)
        game_abort("failed to load image: image12.png");

    // Change to first scene.
    game_change_scene(SCENE_MENU);
}

void game_start_event_loop(void) {
    bool done = false;
    ALLEGRO_EVENT event;
    int redraws = 0;
    while (!done) {
        al_wait_for_event(game_event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            // Event for clicking the window close button.
            game_log("Window close button clicked");
            done = true;
        } else if (event.type == ALLEGRO_EVENT_TIMER) {
            // Event for redrawing the display.
            if (event.timer.source == game_update_timer)
                // The redraw timer has ticked.
                redraws++;
        } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            // Event for keyboard key down.
            game_log("Key with keycode %d down", event.keyboard.keycode);
            key_state[event.keyboard.keycode] = true;
            on_key_down(event.keyboard.keycode);
        } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            // Event for keyboard key up.
            game_log("Key with keycode %d up", event.keyboard.keycode);
            key_state[event.keyboard.keycode] = false;
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            // Event for mouse key down.
            game_log("Mouse button %d down at (%d, %d)", event.mouse.button, event.mouse.x, event.mouse.y);
            mouse_state[event.mouse.button] = true;
            on_mouse_down(event.mouse.button, event.mouse.x, event.mouse.y);
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            // Event for mouse key up.
            game_log("Mouse button %d up at (%d, %d)", event.mouse.button, event.mouse.x, event.mouse.y);
            mouse_state[event.mouse.button] = false;
        } else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            if (event.mouse.dx != 0 || event.mouse.dy != 0) {
                // Event for mouse move.
                // game_log("Mouse move to (%d, %d)", event.mouse.x, event.mouse.y);
                mouse_x = event.mouse.x;
                mouse_y = event.mouse.y;
            } else if (event.mouse.dz != 0) {
                // Event for mouse scroll.
                game_log("Mouse scroll at (%d, %d) with delta %d", event.mouse.x, event.mouse.y, event.mouse.dz);
            }
        }
        // TODO: Process more events and call callbacks by adding more
        // entries inside Scene.

        // Redraw
        if (redraws > 0 && al_is_event_queue_empty(game_event_queue)) {
            // if (redraws > 1)
            //     game_log("%d frame(s) dropped", redraws - 1);
            // Update and draw the next frame.
            game_update();
            game_draw();
            redraws = 0;
        }
    }
}

void game_update(void) {
    if (active_scene == SCENE_START) {
        plane.vx = plane.vy = 0;
        if (key_state[ALLEGRO_KEY_UP] || key_state[ALLEGRO_KEY_W])
            plane.vy -= 1;
        if (key_state[ALLEGRO_KEY_DOWN] || key_state[ALLEGRO_KEY_S])
            plane.vy += 1;
        if (key_state[ALLEGRO_KEY_LEFT] || key_state[ALLEGRO_KEY_A])
            plane.vx -= 1;
        if (key_state[ALLEGRO_KEY_RIGHT] || key_state[ALLEGRO_KEY_D])
            plane.vx += 1;
        // 0.71 is (1/sqrt(2)).
        plane.y += plane.vy * 10 * (plane.vx ? 0.71f : 1);
        plane.x += plane.vx * 10 * (plane.vy ? 0.71f : 1);
        // [HACKATHON 1-1]
        // TODO: Limit the plane's collision box inside the frame.
        //       (x, y axes can be separated.)
        // Uncomment and fill in the code below.
        if (plane.x - plane.w / 2 < 0)
            plane.x = plane.w / 2;
        else if (plane.x + plane.w / 2 > SCREEN_W)
            plane.x = SCREEN_W - plane.w / 2;
        if (plane.y - plane.h / 2 < 0)
            plane.y = plane.h / 2;
        else if (plane.y + plane.h / 2 > SCREEN_H)
            plane.y = SCREEN_H - plane.h / 2;

        // [HACKATHON 2-8]
        // TODO: Shoot if key is down and cool-down is over.
        // 1) Get the time now using 'al_get_time'.
        // 2) If Space key is down in 'key_state' and the time
        //    between now and last shoot is not less that cool
        //    down time.
        // 3) Loop through the bullet array and find one that is hidden.
        //    (This part can be optimized.)
        // 4) The bullet will be found if your array is large enough.
        // 5) Set the last shoot time to now.
        // 6) Set hidden to false (recycle the bullet) and set its x, y to the
        //    front part of your plane.
        // Uncomment and fill in the code below.
        ALLEGRO_MOUSE_STATE state;
        al_get_mouse_state(&state);

        double now = al_get_time();
        if ((key_state[ALLEGRO_KEY_SPACE] || (state.buttons & 1)) && now - last_shoot_timestamp >= MAX_COOLDOWN) {
            int i;
            for (i = 0; i < MAX_BULLET; i++) {
                if (bullets[i].hidden) {
                    last_shoot_timestamp = now;
                    bullets[i].hidden = false;
                    bullets[i].x = plane.x;
                    bullets[i].y = plane.y;
                    break;
                }
            }
        }
        game_update_calls();
    }
}

void game_draw(void) {
    if (active_scene == SCENE_MENU) {
        al_draw_bitmap(main_img_background, 0, 0, 0);
        al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 255), SCREEN_W / 2, 30, ALLEGRO_ALIGN_CENTER, "Space Shooter");
        al_draw_text(font_pirulen_24, al_map_rgb(255, 255, 255), 20, SCREEN_H - 50, 0, "Press enter key to start");
        // [HACKATHON 3-5]
        // TODO: Draw settings images.
        // The settings icon should be located at (x, y, w, h) =
        // (SCREEN_W - 48, 10, 38, 38).
        // Change its image according to your mouse position.
        // Uncomment and fill in the code below.
        if (pnt_in_rect(mouse_x, mouse_y, SCREEN_W - 48, 10, 38, 38))
            al_draw_bitmap(img_settings2, SCREEN_W - 48, 10, 0);
        else
            al_draw_bitmap(img_settings, SCREEN_W - 48, 10, 0);
    } else if (active_scene == SCENE_START) {
        int i;
        al_draw_bitmap(start_img_background, 0, 0, 0);
        // [HACKATHON 2-9]
        // TODO: Draw all bullets in your bullet array.
        // Uncomment and fill in the code below.
        for (i = 0;i < MAX_BULLET; i++)
            if(!bullets[i].hidden)
                al_draw_bitmap(bullets[i].img, bullets[i].x, bullets[i].y, 0);

        draw_movable_object(plane);
        for (i = 0; i < MAX_ENEMY; i++)
            draw_movable_object(enemies[i]);

        for (i = 0; i < MAX_ENEMY_BULLET; i++)
            if(!enemy_bullet[i].hidden)
                draw_movable_object(enemy_bullet[i]);

        score_board();
    }
    // [HACKATHON 3-9]
    // TODO: If active_scene is SCENE_SETTINGS.
    // Draw anything you want, or simply clear the display.
    else if (active_scene == SCENE_SETTINGS) {
        al_clear_to_color(al_map_rgb(0, 0, 0));
    }
    al_flip_display();
}

void game_destroy(void) {
    // Destroy everything you have created.
    // Free the memories allocated by malloc or allegro functions.
    // Destroy shared resources.
    al_destroy_font(font_pirulen_32);
    al_destroy_font(font_pirulen_24);

    /* Menu Scene resources*/
    al_destroy_bitmap(main_img_background);
    al_destroy_sample(main_bgm);
    // [HACKATHON 3-6]
    // TODO: Destroy the 2 settings images.
    // Uncomment and fill in the code below.
    al_destroy_bitmap(img_settings);
    al_destroy_bitmap(img_settings2);

    /* Start Scene resources*/
    al_destroy_bitmap(start_img_background);
    al_destroy_bitmap(start_img_plane);
    al_destroy_bitmap(start_img_enemy);
    al_destroy_sample(start_bgm);
    // [HACKATHON 2-10]
    // TODO: Destroy your bullet image.
    // Uncomment and fill in the code below.
    al_destroy_bitmap(img_bullet);

    al_destroy_timer(game_update_timer);
    al_destroy_event_queue(game_event_queue);
    al_destroy_display(game_display);
    free(mouse_state);
}

void game_change_scene(int next_scene) {
    game_log("Change scene from %d to %d", active_scene, next_scene);
    // TODO: Destroy resources initialized when creating scene.
    if (active_scene == SCENE_MENU) {
#ifdef audio
        al_stop_sample(&main_bgm_id);
        game_log("stop audio (bgm)");
#endif
        main_scene_start();
    } else if (active_scene == SCENE_START) {
#ifdef audio
        al_stop_sample(&start_bgm_id);
        game_log("stop audio (bgm)");
#endif
    }
    active_scene = next_scene;
    // TODO: Allocate resources before entering scene.
    if (active_scene == SCENE_MENU) {
#ifdef audio
        if (!al_play_sample(main_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &main_bgm_id))
            game_abort("failed to play audio (bgm)");
#endif
    } else if (active_scene == SCENE_START) {

#ifdef audio
        if (!al_play_sample(start_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &start_bgm_id))
            game_abort("failed to play audio (bgm)");
#endif
    }
}

void on_key_down(int keycode) {
    if (active_scene == SCENE_MENU) {
        if (keycode == ALLEGRO_KEY_ENTER)
            game_change_scene(SCENE_START);
    }
    // [HACKATHON 3-10]
    // TODO: If active_scene is SCENE_SETTINGS and Backspace is pressed,
    // return to SCENE_MENU.
    else if (active_scene == SCENE_SETTINGS) {
        if (keycode == ALLEGRO_KEY_Q)
            game_change_scene(SCENE_MENU);
    }
}

void on_mouse_down(int btn, int x, int y) {
    // [HACKATHON 3-8]
    // TODO: When settings clicked, switch to settings scene.
    // Uncomment and fill in the code below.
    if (active_scene == SCENE_MENU) {
        if (btn == 1) {
            if (pnt_in_rect(x, y, SCREEN_W - 48, 10, 38, 38))
                game_change_scene(SCENE_SETTINGS);
        }
    }
}

void draw_movable_object(MovableObject obj) {
    if (obj.hidden)
        return;
    al_draw_bitmap(obj.img, round(obj.x - obj.w / 2), round(obj.y - obj.h / 2), 0);
}

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

// [HACKATHON 3-3]
// TODO: Define bool pnt_in_rect(int px, int py, int x, int y, int w, int h)
// Uncomment and fill in the code below.
bool pnt_in_rect(int px, int py, int x, int y, int w, int h) {
    return x <= px && px <= x + w && y <= py && py <= y + h;
}


// +=================================================================+
// | Code below is for debugging purpose, it's fine to remove it.    |
// | Deleting the code below and removing all calls to the functions |
// | doesn't affect the game.                                        |
// +=================================================================+

void game_abort(const char* format, ...) {
    va_list arg;
    va_start(arg, format);
    game_vlog(format, arg);
    va_end(arg);
    fprintf(stderr, "error occured, exiting after 2 secs");
    // Wait 2 secs before exiting.
    al_rest(2);
    // Force exit program.
    exit(1);
}

void game_log(const char* format, ...) {
#ifdef LOG_ENABLED
    va_list arg;
    va_start(arg, format);
    game_vlog(format, arg);
    va_end(arg);
#endif
}

void game_vlog(const char* format, va_list arg) {
#ifdef LOG_ENABLED
    static bool clear_file = true;
    // Write log to file for later debugging.
    FILE* pFile = fopen("log.txt", clear_file ? "w" : "a");
    if (pFile) {
        va_list arg2;
        va_copy(arg2, arg);
        vfprintf(pFile, format, arg2);
        va_end(arg2);
        fprintf(pFile, "\n");
        fclose(pFile);
    }
    vprintf(format, arg);
    printf("\n");
    clear_file = false;
#endif
}



int score;

void enemy_trajectory();
void kill_enemy(); // Kill the enemy which is touched by bullets.
bool spawn_enemy(); // Spawn the enemy randomly.
void kill_plane(); // Kill the plane when touched by enemies
void physics_engine();
void enemy_attack();

void game_update_calls() {
    enemy_trajectory();
    spawn_enemy();
    kill_enemy();
    kill_plane();
    physics_engine();
    enemy_attack();
    kill_bullets();
}

const int enemy_trajectory_update_interval = 10, enemy_trajectory_speed = 11;
int enemy_trajectory_runned_frames = 0;
void enemy_trajectory() {
    if(enemy_trajectory_runned_frames++ % enemy_trajectory_update_interval != 0) return;
    int i;
    int master_vy = rand() % enemy_trajectory_speed - enemy_trajectory_speed / 2;
    for(i = 0;i < MAX_ENEMY;i++) {
        enemies[i].vx = sin(enemy_trajectory_runned_frames + i);
        enemies[i].vy = 1;
    }
}

const int spawn_enemy_interval = 100;
int spawn_enemy_runned_frames = 0;
bool spawn_enemy() {
    if(spawn_enemy_runned_frames++ != spawn_enemy_interval) return;
    spawn_enemy_runned_frames = 0;
    int i;
    for(i = 0;i < MAX_ENEMY;i++) {
        if(enemies[i].hidden) {
            enemies[i].hidden = false;
            enemies[i].x = rand() % SCREEN_W;
            enemies[i].y = 0;
            enemies[i].health = 3;
            break;
        }
    }
    return i != MAX_ENEMY;
}

void kill_enemy() {
    int i, j;
    for(i = 0;i < MAX_ENEMY;i++){
        if(!enemies[i].hidden) {
            bool collision = false;
            int x, y;
            for(x = enemies[i].x;x <= enemies[i].x + enemies[i].w;x++)
                for(y = enemies[i].y;y <= enemies[i].y + enemies[i].h;y++)
                    for(j = 0;j < MAX_BULLET;j++) {
                        collision |= pnt_in_rect(x, y, bullets[j].x, bullets[j].y, bullets[j].w, bullets[j].h) && !bullets[j].hidden;
                        if(pnt_in_rect(x, y, bullets[j].x, bullets[j].y, bullets[j].w, bullets[j].h) && !bullets[j].hidden)
                            bullets[j].hidden = true;
                    }

            if(collision) enemies[i].health -= 1;
            if(enemies[i].health < 0) {
                enemies[i].hidden = true;
                score += 5;
            }
        }
    }
}

void kill_plane() {
    int i;
    for(i = 0;i < MAX_ENEMY;i++){
        if(!enemies[i].hidden) {
            bool collision = false;
            int x, y;
            for(x = enemies[i].x;x <= enemies[i].x + enemies[i].w;x++)
                for(y = enemies[i].y;y <= enemies[i].y + enemies[i].h;y++)
                    collision |= pnt_in_rect(x, y, plane.x, plane.y, plane.w, plane.h);
            if(collision) game_change_scene(SCENE_MENU);
        }
    }

    for(i = 0;i < MAX_ENEMY_BULLET;i++){
        if(!enemy_bullet[i].hidden) {
            bool collision = false;
            int x, y;
            for(x = enemy_bullet[i].x;x <= enemy_bullet[i].x + enemy_bullet[i].w;x++)
                for(y = enemy_bullet[i].y;y <= enemy_bullet[i].y + enemy_bullet[i].h;y++)
                    collision |= pnt_in_rect(x, y, plane.x, plane.y, plane.w, plane.h);
            if(collision) game_change_scene(SCENE_MENU);
        }
    }
}

void kill_bullets() {
    int i, j, x, y;
    for(i = 0;i < MAX_BULLET;i++) for(j = 0;j < MAX_ENEMY_BULLET;j++) {
        bool collision = false;
        for(x = bullets[i].x; x <= bullets[i].x + bullets[i].w; x++) for(y = bullets[i].y; y <= bullets[i].y + bullets[i].h; y++)
            collision |= pnt_in_rect(x, y, enemy_bullet[j].x, enemy_bullet[j].y, enemy_bullet[j].w, enemy_bullet[j].h) && !bullets[i].hidden && !enemy_bullet[j].hidden;
        if(collision) {
            bullets[i].hidden = true;
            enemy_bullet[j].hidden = true;
            score += 1;
        }
    }
}

void enemy_shoot_bullet();
const int attack_interval = 10;
int attack_frames = 0;
void enemy_attack() {
    if(attack_frames++ % attack_interval != 0) return;
    int i;
    for(i = 0;i < MAX_ENEMY;i++) {
        if(!enemies[i].hidden) {
            enemy_shoot_bullet(i);
            break;
        }
    }
}

void enemy_shoot_bullet(int enemy_id) {
    int i;
    for(i = 0;i < MAX_ENEMY_BULLET;i++) {
        if(enemy_bullet[i].hidden) {
            enemy_bullet[i].hidden = false;
            enemy_bullet[i].img = al_load_bitmap("rocket-1.png");
            enemy_bullet[i].x = enemies[enemy_id].x;
            enemy_bullet[i].y = enemies[enemy_id].y;
            break;
        }
    }
}

void physics_engine() {
    // [HACKATHON 2-7]
    // TODO: Update bullet coordinates.
    // 1) For each bullets, if it's not hidden, update x, y
    // according to vx, vy.
    // 2) If the bullet is out of the screen, hide it.
    // Uncomment and fill in the code below.
    int i;
    for (i = 0;i < MAX_BULLET;i++) {
        if (bullets[i].hidden)
            continue;
        bullets[i].y += bullets[i].vy;
        bullets[i].x += bullets[i].vx;
        if (bullets[i].y < 0)
            bullets[i].hidden = true;
    }

    for (i = 0;i < MAX_ENEMY;i++) {
        if (enemies[i].hidden)
            continue;
        enemies[i].y += enemies[i].vy;
        enemies[i].x += enemies[i].vx;
        if(enemies[i].y > SCREEN_W)
            enemies[i].hidden = true;
        //enemies[i].y = max(0, min(SCREEN_H, enemies[i].y));
        enemies[i].x = max(0, min(SCREEN_W, enemies[i].x));
    }

    const float enemy_bullet_speed = 1;
    for(i = 0;i < MAX_ENEMY_BULLET;i++) {
        if (enemy_bullet[i].hidden)
            continue;
        int x = plane.x - enemy_bullet[i].x, y = plane.y - enemy_bullet[i].y;
        enemy_bullet[i].vx = (float)x / sqrt(x * x + y * y) * enemy_bullet_speed;
        enemy_bullet[i].vy = (float)y / sqrt(x * x + y * y) * enemy_bullet_speed + 2;
        enemy_bullet[i].y += enemy_bullet[i].vy;
        enemy_bullet[i].x += enemy_bullet[i].vx;
        if (bullets[i].y > SCREEN_W)
            bullets[i].hidden = true;
    }
}

void main_scene_start() {
    score = 0;
    int i;
    plane.img = start_img_plane;
    plane.x = 400;
    plane.y = 500;
    plane.w = al_get_bitmap_width(plane.img);
    plane.h = al_get_bitmap_height(plane.img);
    plane.health = 3;

    for (i = 0; i < MAX_ENEMY; i++) {
        enemies[i].img = start_img_enemy;
        enemies[i].w = al_get_bitmap_width(start_img_enemy);
        enemies[i].h = al_get_bitmap_height(start_img_enemy);
        enemies[i].x = 30;
        enemies[i].y = i * 20;
    }
    // [HACKATHON 2-6]
    // TODO: Initialize bullets.
    // For each bullets in array, set their w and h to the size of
    // the image, and set their img to bullet image, hidden to true,
    // (vx, vy) to (0, -3).
    // Uncomment and fill in the code below.
    for (i = 0; i < MAX_BULLET; i++) {
        bullets[i].w = al_get_bitmap_width(img_bullet);
        bullets[i].h = al_get_bitmap_height(img_bullet);
        bullets[i].img = img_bullet;
        bullets[i].vx = 0;
        bullets[i].vy = -10;
        bullets[i].hidden = true;
    }

    for(i = 0;i < MAX_ENEMY;i++) enemies[i].health = 3;
    for(i = 0;i < MAX_ENEMY;i++) enemies[i].x = 30;
    for(i = 0;i < MAX_ENEMY;i++) enemies[i].y = i * 10;
    for(i = 0;i < MAX_ENEMY;i++) enemies[i].hidden = false;
    for(i = 0;i < MAX_ENEMY_BULLET;i++) enemy_bullet[i].hidden = true;
    for(i = 0;i < MAX_ENEMY_BULLET;i++) {
        enemy_bullet[i].img = al_load_bitmap("rocket-1.png");
        enemy_bullet[i].h = al_get_bitmap_height(enemy_bullet[i].img);
        enemy_bullet[i].w = al_get_bitmap_width(enemy_bullet[i].img);
    }
}

void score_board() {
    al_draw_textf(font_pirulen_32, al_map_rgb(0, 0, 0), SCREEN_W, 0, ALLEGRO_ALIGN_RIGHT , "SCORE: %d", score);
    al_draw_textf(font_pirulen_32, al_map_rgb(0, 0, 0), SCREEN_W, SCREEN_H - 32, ALLEGRO_ALIGN_RIGHT , "REMAINING LIVES: %d", plane.health);
}




