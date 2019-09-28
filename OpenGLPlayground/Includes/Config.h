#ifndef CONFIG_H
#define CONFIG_H
#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/vec3.hpp>
const int WINDOW_WIDTH  = 600, WINDOW_HEIGHT = 600;
const glm::vec3 LOOKAT_CENTER = glm::vec3(.0f, 1.0f, .0f);
const glm::vec3 DEFAULT_LIGHT_POS = glm::vec3(-1.5f, 3.0f, -1.0f);
const float LIGHT_NEAR_PLANE = 1.0f, LIGHT_FAR_PLANE = 7.5f;
const unsigned int SHADOW_WIDTH = 600, SHADOW_HEIGHT = 600;
const bool RENDER_FROM_LIGHTSPACE = false;
const bool DRAW_DEBUG_QUAD = false;

#endif
