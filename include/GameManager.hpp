
#ifndef _HEADER_GAMEMANAGER
#define _HEADER_GAMEMANAGER
#include "../include/HeaderApp.hpp"
class Scene;
class GameManager {
    Scene* currentScene;
    ModelInf idea;


public:
    D3DManager* dmanager;
    InputManager* imanager;
    void initManager(D3DManager* in_dmanager, InputManager* in_imanager);
    void changeCurrent(Scene* in_scene);
    void drawIdea();
    void setIdea(Model* model, Texture* text);
    void createTexture(int numTexture, Texture* texture);
    void updateScene();
    void applyCamera(Camera* in_camera);
    void gameQuit();
};

struct STAGE {
private:
    STAGE() {
        for (int i = 0; i < numStage - 1; i++) {
            clearFlag[i] = true;
        }
        clearFlag[3] = false;
        clearFlag[4] = false;
    }

public:
    static STAGE* getStage() {
        static STAGE* stage = new STAGE();
        return stage;
    }
    const static int numStage = 5;
    bool clearFlag[numStage];
};

#endif