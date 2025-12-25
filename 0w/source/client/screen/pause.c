#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <cglm/cglm.h>

#include "core/value.h"
#include "core/extra.h"
#include "core/heap.h"

#include "client/core/keyboard.h"
#include "client/core/shader.h"
#include "client/object/camera.h"

#include "server/object/player.h"
#include "server/object/block.h"

#include "client/screen/pause.h"

struct Screen_Pause__ {
    Player player;
    Block block;
    void* window;
}; 

int screen_pause_create(Screen_Pause* turnback, void* window) {
    return 0; 
}

void screen_pause_frame(Screen_Pause screen) {

}

void screen_pause_destroy(Screen_Pause* screen) {
   
}
