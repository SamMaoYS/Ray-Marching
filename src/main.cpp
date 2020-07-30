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
        window->setBackGroundColor(0, 0, 0, 1);
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

    // positions all cubes
    std::vector<glm::vec3> cube_positions = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // positions of the point lights
    std::vector<glm::vec3> light_positions = {
            glm::vec3( 0.7f,  0.2f,  2.0f),
            glm::vec3( 2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f,  2.0f, -12.0f),
            glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    Actor cube_sample;
    cube_sample.setPolyData(&cube);
    cube_sample.setShader(&cube_shader);
    cube_sample.setLight(light);
    cube_sample.setModelMatrix(glm::mat4(1.0f));
    cube_sample.setDrawParams(GL_TRIANGLES, 0, 36);
    cube_sample.loadDiffuseTexture(diffuse_tex_path);
    cube_sample.loadSpecularTexture(specular_tex_path);

    Actor light_sample;
    light_sample.setPolyData(&cube);
    light_sample.setShader(&light_shader);
    light_sample.setLight(light);
    light_sample.setModelMatrix(glm::mat4(1.0f));
    light_sample.setDrawParams(GL_TRIANGLES, 0, 36);

    glm::mat4 model = glm::mat4(1.0f);

    Interactor* interactor = new Interactor(window, camera);

    std::vector<Actor> cube_actors(cube_positions.size(), cube_sample);
    for (int i = 0; i < cube_actors.size(); ++i) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, cube_positions[i]);
        cube_actors[i].setModelMatrix(model);
        interactor->addActor(&cube_actors[i]);
    }

    std::vector<Actor> light_actors(light_positions.size(), light_sample);
    for (int i = 0; i < light_actors.size(); ++i) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, light_positions[i]);
        light_actors[i].setModelMatrix(model);
        interactor->addActor(&light_actors[i]);
    }
    interactor->render();

    cube_actors.clear();
    light_actors.clear();
    delete interactor;
    delete window;
    delete camera;
    return EXIT_SUCCESS;
}
