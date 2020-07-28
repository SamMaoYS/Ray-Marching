#include <iostream>

#include "window.h"
#include "interactor.h"
#include <boost/any.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

#define SETVEC3 static_cast<void(Shader:: *) (const std::string &str, const glm::vec3 &value) const>

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

    Camera* camera = new Camera(glm::vec3(0, 0, 7));

    Shader light_shader("../shaders/light.vs", "../shaders/light.frag");
    Shader cube_shader("../shaders/model.vs", "../shaders/model.frag");

    PolyData cube;
    cube.genCube();

    Light light;
    light.pos = glm::vec3(0.0f, 1.0f, 1.0f);
    light.color = glm::vec3(1.0);

    std::string diffuse_tex_path = "../data/container.png";
    std::string specular_tex_path = "../data/container_specular.png";

    Actor cube_actor;
    cube_actor.setPolyData(&cube);
    cube_actor.setShader(&cube_shader);
    cube_actor.setLight(light);
    glm::mat4 model = glm::mat4(1.0f);
    cube_actor.setModelMatrix(model);
    cube_actor.setDrawParams(GL_TRIANGLES, 0, 36);
    cube_actor.loadDiffuseTexture(diffuse_tex_path);
    cube_actor.loadSpecularTexture(specular_tex_path);

    Actor light_actor;
    light_actor.setPolyData(&cube);
    light_actor.setShader(&light_shader);
    light_actor.setLight(light);
    model = glm::mat4(1.0f);
    model = glm::translate(model, light.pos);
    model = glm::scale(model, glm::vec3(0.2f));
    light_actor.setModelMatrix(model);
    light_actor.setDrawParams(GL_TRIANGLES, 0, 36);

    Interactor* interactor = new Interactor(window, camera);
    interactor->addActor(&cube_actor);
    interactor->addActor(&light_actor);
    interactor->render();

    delete interactor;
    delete window;
    delete camera;
    return EXIT_SUCCESS;
}
