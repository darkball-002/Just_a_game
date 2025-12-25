#define Camera_CLASS

typedef struct Camera__ {
    double yaw_deg;
    double pitch_deg;
    float position[3];
    float orientation[3];
    float antigravityDirection[3];
    int uniform_location;
} Camera;

/**
 * @param yaw_deg always add 90.0, for redirect to south
 */
void camera_create(Camera* camera, double position_x, double position_y, double position_z, double yaw_deg, double pitch_deg, int gl_uniform_location);

void camera_lookat(Camera* camera, double* fov_deg, double windowRatio, double* closer_std_max, double* faraway_std_min);