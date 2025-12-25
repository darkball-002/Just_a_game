#include <glad/glad.h>
#include <cglm/types.h>
#include <cglm/mat4.h>
#include <cglm/cam.h>

#include "client/object/camera.h"

#include "core/value.h"
#include "core/extra.h"

// cos: x / r
// sin: y / r
// tan: y / x

void camera_create(Camera* camera, double x, double y, double z, double yaw, double pitch, int uniform) {
    camera->uniform_location = uniform;
    camera->pitch_deg = pitch;
    camera->yaw_deg = yaw + 90.0;

    value_triple_set(float, camera->antigravityDirection, 0.0f, 1.0f, 0.0f);

    value_yaw_pitch_ptr(camera->orientation, &camera->yaw_deg, &camera->pitch_deg);

    value_triple_set(float, camera->position, x, y, z);
}

void camera_lookat(Camera* camera, double* fov, double ratio, double* closer, double* faraway) {
    mat4 view, projection, pmv;
    vec3 center;

    glm_mat4_identity(view);
	glm_mat4_identity(projection);

    glm_vec3_add(camera->position, camera->orientation, center);

    glm_lookat(camera->position, center, camera->antigravityDirection, view);

    glm_perspective(
        value_rad(*fov = value_clamp(*fov, 10.0, 120.0)), 
        ratio, 
        (*closer = value_clamp(*closer, 0.01, *faraway)), 
        (*faraway = value_clamp(*faraway, *closer, 10000.0)), 
        projection
    );

    glm_mat4_mul(projection, view, pmv);

    glUniformMatrix4fv(camera->uniform_location, 1, false, &pmv[0][0]);
}
