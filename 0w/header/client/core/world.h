#if (defined Shader_CLASS && defined Keyboard_CLASS)

typedef struct World__ *World;

int world_create(World* pTurnback, void* window);

void world_frame(World world, KeyState keys, double passedTime, int width, int height);

void world_destroy(World pWorld);

Player world_get_player(World world);

#endif