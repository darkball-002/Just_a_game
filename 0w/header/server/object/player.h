#if (defined Camera_CLASS && defined Keyboard_CLASS)

#define Player_CLASS

#include "core/value.h"

typedef struct Player__ *Player;

int player_create(Player* player, void* window, Camera camera, double fov_deg, double closer_std_max, double faraway_std_min, double sensitivity);

void player_lookAround(Player player, double passedTime, int window_width, int window_height);

void player_control_special(Player player, int state);

void player_control_move(Player player, float* speed, float* direction, double passedTime);

void player_control_rotate(Player player, double rotation_x, double rotation_y);

void player_pause(Player player, bool really);


bool player_boolean_distractionning(Player player);

double player_get_sensitivity(Player player);

Camera player_get_camera(Player player);

#endif
