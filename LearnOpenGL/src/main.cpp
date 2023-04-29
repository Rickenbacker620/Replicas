// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <LGL/base_components/EBO.hpp>
#include <LGL/base_components/VAO.hpp>
#include <LGL/base_components/VBO.hpp>
#include <LGL/base_components/shader.hpp>
#include <LGL/init.hpp>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

int main()
{
    GLFWwindow *window = init_window();

    if (window == NULL)
    {
        return -1;
    }

    init_glad();
    std::string shaderRoot = "/home/shiro/Projects/Replicas/LearnOpenGL/shaders/";

    auto s = new Shader(shaderRoot + "vertexShader.glsl", shaderRoot + "fragmentShader.glsl");

    auto shaderProgram = s->getProgram();

    float vertices[] = {
        0.5f,  0.5f,  0.0f, // top right
        0.5f,  -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f  // top left
    };

    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first Triangle
        1, 2, 3  // second Triangle
    };

    auto vao = new VAO();
    auto vbo = new VBO(vertices, sizeof(vertices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    auto ebo = new EBO(indices, sizeof(indices));

    run_loop(window, [&]() {
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        vao->bind();
        // do so to keep things a bit more organized
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time
    });

    glfwTerminate();
    return 0;
}
