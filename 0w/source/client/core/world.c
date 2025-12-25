#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <cglm/cglm.h>
#include <math.h>

#include "core/function.h"
#include "core/value.h"
#include "core/extra.h"
#include "core/heap.h"
#include "core/io.h"

#include "client/core/keyboard.h"
#include "client/core/shader.h"
#include "client/object/camera.h"

#include "server/object/player.h"
#include "server/object/block.h"

#include "client/core/world.h"

enum {
    World_Broken_Player, World_Broken_WindowClosed
};

struct World__ {
    Shader shader;
    Player player;
    Block block;
    void* window;
}; 

static void player_control_normal(World world, KeyState key, double passedTime) {
    static vec3 walkspeed = { 1.7f, 1.7f, 1.7f };
    static vec3 spd_negate = { -1.7f, -1.7f, -1.7f };

    vec3 main = { 0 };
    vec3 side = { 0 };

    value_cos_sin_float(value_rad(player_get_camera(world->player).yaw_deg), &main[0], &main[2]);
    
    glm_vec3_cross(player_get_camera(world->player).antigravityDirection, main, side);

    glm_vec3_normalize(main);
    glm_vec3_normalize(side);

    if (key[Keyboard_W] == Keyboard_Pressed) player_control_move(world->player, walkspeed, main, passedTime);
    if (key[Keyboard_A] == Keyboard_Pressed) player_control_move(world->player, walkspeed, side, passedTime);
    if (key[Keyboard_S] == Keyboard_Pressed) player_control_move(world->player, spd_negate, main, passedTime);
    if (key[Keyboard_D] == Keyboard_Pressed) player_control_move(world->player, spd_negate, side, passedTime);
    
    if (key[Keyboard_Space] == Keyboard_Pressed) {
        player_control_move(world->player, walkspeed, player_get_camera(world->player).antigravityDirection, passedTime);
    } else if (key[Keyboard_Shift] == Keyboard_Pressed) player_control_move(world->player, spd_negate, player_get_camera(world->player).antigravityDirection, passedTime);
}

static void player_control_cursor(World world, double passedTime, int width, int height) {
    double cursor_x = 0.0, cursor_y = 0.0;

    glfwGetCursorPos(world->window, &cursor_x, &cursor_y);
    glfwSetCursorPos(world->window, 0.0, 0.0);

    if (fabs(cursor_x) > 1 || fabs(cursor_y) > 1) {
        const double multiple = 11520.0;

        cursor_x = cursor_x / width * multiple * player_get_sensitivity(world->player) * passedTime;
        cursor_y = -cursor_y / height * multiple * player_get_sensitivity(world->player) * passedTime;

        if (fabs(cursor_x) > 0.01 || fabs(cursor_y) > 0.01) {
            player_control_rotate(world->player, cursor_x, cursor_y);
        }
    }
}

static void player_control(World world, KeyState key, double passedTime, int width, int height) {
    if (player_boolean_distractionning(world->player)) return;

    player_control_cursor(world, passedTime, width, height);
    player_control_normal(world, key, passedTime);
}


static void vertices_create(World world) {
    float* pVBO = shader_get_vertex_buffer(world->shader);
	unsigned int* pEBO = shader_get_order_buffer(world->shader);

    block_create(&world->block, &pVBO[0], &pEBO[0], 0, 1.25, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

    block_create(&world->block, &pVBO[block_getSize(false, 1)], &pEBO[block_getSize(true, 1)], 8,-1.25, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0); 

    block_create(&world->block, &pVBO[block_getSize(false, 2)], &pEBO[block_getSize(true, 2)], 16, 0.0, 3.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
}


// free resources when something was wrong or just player leave the game.
static void world_broken(World world, int level) {
    if (level > World_Broken_Player) {
        value_heap_release(world->player);
        shader_unbind(world->shader);
        shader_destroy(world->shader);
    }

    char* formated;

    value_string_format(&formated, "world loop breaked with level %d", level);
    value_print_log(formated);
    value_heap_release(formated);

    value_heap_release(world);
}


// create an new world for player
int world_create(World* turnback, void* window) {
    World world;
    int errorcode;

    if (value_error_state(errorcode, value_heap_calloc(&world, sizeof(struct World__), 1))) {
        world->window = window;
    } else return errorcode;


    if (value_error_state(errorcode, shader_create(&world->shader, shader_vertex_file(vertices), shader_fragment_file(vertices)))) {
        block_bufferSizeNeed(shader_get_vertex_count(world->shader), shader_get_order_count(world->shader), 3);
    } else {
        world_broken(world, 0);
        return shader_error_check(errorcode);
    }

    if (value_error_state(errorcode, shader_setup_buffer(world->shader))) {
        vertices_create(world);
        shader_setup_bind(world->shader);
    } else {
        world_broken(world, 0);
        return shader_error_check(errorcode);
    }

    Camera camera;

    camera_create(&camera, 0.0, 0.65, 0.0, 0.0, 0.0, glGetUniformLocation(shader_get_globj(world->shader, ShaderProgram), "pcamera"));

    if (value_error_state(errorcode, player_create(&world->player, window, camera, 90.0, 0.1, 100.0, 1.0))) {} else {
        world_broken(world, World_Broken_Player);
        return errorcode;
    }
   
    *turnback = world;

    return errorcode;
}


// render the world object
void world_image(World world) {
    value_openGL_clearAndPaintColor(value_openGL_color_RGBA(30, 30, 30, 255));
    glUseProgram(shader_get_globj(world->shader, ShaderProgram));
	glBindVertexArray(shader_get_globj(world->shader, VAO));
	glDrawElements(GL_TRIANGLES, *shader_get_order_count(world->shader), GL_UNSIGNED_INT, 0);
}

// running in every single frame
void world_frame(World world, KeyState keys, double passedTime, int width, int height) {
    player_control(world, keys, passedTime, width, height);
    player_lookAround(world->player, passedTime, width, height);

    world_image(world);

    glfwSwapBuffers(world->window);
}

// destroy the world
void world_destroy(World world) {
    if (!world) return;

    world_broken(world, World_Broken_WindowClosed);
}




Player world_get_player(World world) {
    return world->player;
}
