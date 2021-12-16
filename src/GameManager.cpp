#include "../include/HeaderApp.hpp"
#include "../include/GameManager.hpp"
#include "../include/Scene.hpp"
D3DManager* D3DManager::getPtrD3DManager() {
    static D3DManager dmanager = D3DManager();
    return &dmanager;
}

InputManager* InputManager::getPtrImanager() {
    static InputManager imanager = InputManager();
    return &imanager;
}

void GameManager::updateScene() {
    currentScene->SceneMain();
}

void GameManager::initManager(D3DManager* in_dmanager, InputManager* in_imanager) {
    dmanager = in_dmanager;
    imanager = in_imanager;
}

void GameManager::changeCurrent(Scene* in_scene) {
    static bool flagFirst = true;
    if (flagFirst) {
        currentScene = in_scene;
    } else {
        delete currentScene;
        std::cout << "Scene deleted" << std::endl;
        in_scene->initScene(this, dmanager);
        currentScene = in_scene;
    }
    flagFirst = false;
}

void GameManager::drawIdea() {
    dmanager->drawModel(&idea);
}

void GameManager::setIdea(Model* model, Texture* text) {
    idea.pIBuffer = model->pIBuffer;
    idea.pVBuffer = model->pVBuffer;
    idea.colR = model->colR;
    idea.colG = model->colG;
    idea.colB = model->colB;
    idea.colA = model->colA;
    idea.degX = model->degX;
    idea.sclX = model->sclX;
    idea.posX = model->posX;
    idea.degY = model->degY;
    idea.sclY = model->sclY;
    idea.posY = model->posY;
    idea.degZ = model->degZ;
    idea.sclZ = model->sclZ;
    idea.posZ = model->posZ;
    idea.numIdx = model->numIdx;
    dmanager->applyTexture(text);
}

void GameManager::applyCamera(Camera* in_camera) {
    dmanager->applyCamera(in_camera);
}

void GameManager::createTexture(int numTexture, Texture* texture) {
    dmanager->createTexture(numTexture, texture);
}

void GameManager::gameQuit() {
    PostQuitMessage(0);
    std::cout << "quit called" << std::endl;
}