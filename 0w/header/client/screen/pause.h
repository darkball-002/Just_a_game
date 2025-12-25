#if (defined Shader_CLASS && defined Keyboard_CLASS)

typedef struct Screen_Pause__ *Screen_Pause;

int screen_pause_create(Screen_Pause* turnback, void* window);

void screen_pause_frame(Screen_Pause pause);

void screen_pause_destroy(Screen_Pause* screen);


#endif