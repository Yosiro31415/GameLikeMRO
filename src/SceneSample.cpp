#include "../include/Scene.hpp"

void SceneSample::initScene(GameManager* in_gmanager, D3DManager* in_dmanager) {
    gmanager = in_gmanager;
    model.init(in_dmanager);
    in_dmanager->createCamera(WindowSize::width, WindowSize::height, &camera);
    camera.posZ = -20.f;
    ObjectSample* obj = new ObjectSample();
    addObject(obj);
    ObjectSample* BG = new ObjectSample();
    addObject(BG);
    BG->scl.setVec(10000, 10000, 1);
    BG->col.setCol(0.0, 0.0, 0.5,1);
    BG->pos.addVec(0, 0, 100);
}

void SceneSample::SceneMain() {
    getKey();
    if (listObject.size() != 0) {
        camera.posY = listObject.at(0)->pos.y;
        camera.posX = listObject.at(0)->pos.x;
    }
    gmanager->applyCamera(&camera);
    for (int i = 0; i < listObject.size(); i++) {
        listObject.at(i)->ObjectMain();
    }
}

void SceneSample::getKey() {
    if (gmanager->imanager->getKey(KEY::Z)) {
        for (int i = 0; i < 1; i++) {
            ObjectBullet* obj = new ObjectBullet();
            addObject(obj);
            obj->scl.setVec(1000, 1000, 1);
            obj->speed.addVec(-1, -1, 0);
        }
    }
    if (gmanager->imanager->getKey(KEY::C)) {
        SceneSample* newSample = new SceneSample();
        std::cout << "change current " << std::endl;
        gmanager->changeCurrent(newSample);
        return;
    }
    if (gmanager->imanager->getKey(KEY::UP)) {
        if (listObject.size() != 0) {
            ObjectGame* objPtr = listObject.at(0);
            delete listObject.at(0);
            deleteObject(objPtr);
        }
    }
    if (gmanager->imanager->getKey(KEY::DOWN)) {
    }
}