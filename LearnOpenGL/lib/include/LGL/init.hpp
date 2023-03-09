#pragma once

#include <GLFW/glfw3.h>
#include <functional>

constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HEIGHT = 600;

using RenderFunc = std::function<void(void)>;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

GLFWwindow *init_window();

int init_glad();

void run_loop(GLFWwindow *window, RenderFunc render_func);

void processInput(GLFWwindow *window);