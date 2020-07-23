#include <iostream>

#include "window.h"
#include "interactor.h"

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
    return EXIT_SUCCESS;
}
