#include <glfw/glfw3.h>

#include "client/core/keyboard.h"
#include "core/value.h"

void keyboard_getKey(void* window, KeyState turnback) {
    turnback[Keyboard_T] = glfwGetKey(window, GLFW_KEY_T);
    turnback[Keyboard_W] = glfwGetKey(window, GLFW_KEY_W);
    turnback[Keyboard_A] = glfwGetKey(window, GLFW_KEY_A);
    turnback[Keyboard_S] = glfwGetKey(window, GLFW_KEY_S);
    turnback[Keyboard_D] = glfwGetKey(window, GLFW_KEY_D);
    turnback[Keyboard_Space] = glfwGetKey(window, GLFW_KEY_SPACE);
    turnback[Keyboard_Shift] = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
}

void keyboard_getMouseKey(void* window, double feedback[2]) {
    glfwGetCursorPos(window, &feedback[0], &feedback[1]);
}