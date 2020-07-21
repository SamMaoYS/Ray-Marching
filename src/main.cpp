#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include "window.h"
#include "interactor.h"

void keyInteractor(GLFWwindow *window);

int main(int argc, char **argv) {
    Window *window = nullptr;
    try {
        window = new Window();
        window->setBackGroundColor(0, 1, 0, 1);
    }
    catch (const std::invalid_argument &e) {
        glfwTerminate();
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    Camera* camera = new Camera();

    Interactor* interactor = new Interactor(window, camera);
    interactor->render();

    delete interactor;
    delete window;
    delete camera;
    glfwTerminate();
    return EXIT_SUCCESS;
}

void keyInteractor(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}