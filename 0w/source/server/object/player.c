#include <glfw/glfw3.h>
#include <cglm/vec3.h>

#include "client/core/keyboard.h"

#include "client/object/camera.h"

#include "server/object/player.h"

#include "core/value.h"
#include "core/extra.h"
#include "core/heap.h"

struct Player__ {
    ptr_t window;
    Camera camera;
    bool distractionning;
    bool TisPressing;
    double fov;
    double closer;
    double faraway;
    double sensitivity;
};

int player_create(Player* turnback, void* window, Camera camera, double fov, double closer, double faraway, double sensitivity) {
    Player player;

    value_if (value_heap_calloc(&player, sizeof(struct Player__), 1)) {
        player->window = window;
        player->camera = camera;
        player->faraway = faraway;
        player->closer = closer;
        player->fov = fov;
        player->sensitivity = sensitivity;
        player->TisPressing = false;

        *turnback = player;
        player_pause(player, true);

        return Value_Error_Fine;
    }
    
    return Value_Error_Memory;
}

void player_lookAround(Player player, double passedTime, int window_width, int window_height) {
    if (player->distractionning) return;

    camera_lookat(&player->camera, &player->fov, (double) window_width / (double) window_height, &player->closer, &player->faraway);
}


void player_control_special(Player player, int state) {
    if (!player->TisPressing && state == Keyboard_Pressed) {
        player->TisPressing = true;

        player_pause(player, !player->distractionning);
    }

    if (state == Keyboard_Released) player->TisPressing = false;
}

void player_control_move(Player player, vec3 speed, vec3 direction, double passedTime) {
    vec3 spd = { 0 };

    glm_vec3_scale(speed, passedTime, spd);

    glm_vec3_muladd(spd, direction, player->camera.position);
}

void player_control_rotate(Player player, double rotation_x, double rotation_y) {
    player->camera.yaw_deg += rotation_x;
    player->camera.pitch_deg += rotation_y;

    value_yaw_pitch_ptr(player->camera.orientation, &player->camera.yaw_deg, &player->camera.pitch_deg);
}


void player_pause(Player player, bool really) {
    int width, height;

    player->distractionning = really;

    glfwGetWindowSize(player->window, &width, &height);
    glfwSetCursorPos(player->window, (double) width / 2.0, (double) height / 2.0);

    if (really) {
        glfwSetInputMode(player->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    } else {
        glfwSetInputMode(player->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

void player_destroy(Player handle) {
    value_heap_redirect(&handle, null);
}


bool player_boolean_distractionning(Player player) {
    return player->distractionning;
}


double player_get_sensitivity(Player player) {
    return player->sensitivity;
}

Camera player_get_camera(Player player) {
    return player->camera;
}
