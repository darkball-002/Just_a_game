#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <cglm/cglm.h>

#include "core/function.h"
#include "core/value.h"
#include "core/extra.h"
#include "core/heap.h"

#include "client/core/keyboard.h"
#include "client/core/shader.h"
#include "client/object/camera.h"

#include "server/object/player.h"
#include "server/object/block.h"

#include "client/screen/pause.h"
#include "client/core/world.h"

static int width = 800, height = 800, errorcode = Value_Error_Fine;

static void resize(GLFWwindow* window, int w, int h) {
	width = w;
	height = h;
    
	glViewport(0, 0, w, h);
}

static void runs(GLFWwindow* window) {
	if (value_error_valid(errorcode, Value_Error_Died, window)) { } else return;

	World world;
	KeyState keys;

	double lastTime = glfwGetTime(), passedTime = 0.0, worldTime = 0.0;

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, resize);
	gladLoadGL();

	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

    value_print_log_setup();

	if (value_error_state(errorcode, world_create(&world, window))) {
		value_openGL_clearAndPaintColor(value_openGL_color_RGBA(30, 30, 30, 255));
		glfwSwapBuffers(window);
	} else goto leave;

	while (!glfwWindowShouldClose(window)) {
		worldTime = glfwGetTime();
		passedTime = worldTime - lastTime;
		
		if (passedTime < 1.0 / 120.0) {
			glfwPollEvents();

			glfwWaitEventsTimeout(1.0 / 120.0 - passedTime);

			continue;
		}

		if (!glfwGetWindowAttrib(window, GLFW_VISIBLE) || !glfwGetWindowAttrib(window, GLFW_FOCUSED)) {
			player_pause(world_get_player(world), true);

			glfwPollEvents();

			glfwWaitEvents();

			lastTime = glfwGetTime();

    		continue;
		}

		glfwPollEvents();
		keyboard_getKey(window, keys);

		player_control_special(world_get_player(world), keys[Keyboard_T]);

		if (!player_boolean_distractionning(world_get_player(world))) {
			world_frame(world, keys, passedTime, width, height);

			lastTime = worldTime;
			continue;
		}
	}

	world_destroy(world);

	leave: {
		glfwDestroyWindow(window);
	}
}

int main() {
	value_window_setup();
	
	runs(glfwCreateWindow(width, height, "Hello", NULL, NULL));

	value_window_shutDown();
	
    return errorcode;
}
