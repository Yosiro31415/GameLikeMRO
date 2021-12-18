#include "../include/Scene.hpp"

void SceneSample::initScene(GameManager* in_gmanager, D3DManager* in_dmanager) {
    gmanager = in_gmanager;
    model.init(in_dmanager);
    in_dmanager->createCamera(WindowSize::width, WindowSize::height, &camera);
    camera.posZ = -20.f;
    ObjectSample* sikaku = new ObjectSample();
    addObject(sikaku);
    sikaku->scl.setVec(100, 100, 1);
    sikaku->col.setCol(0.0, 0.0, 0.5, 1);
    sikaku->pos.addVec(0, 0, -2);
    ObjectPlayer* obj = new ObjectPlayer();
    addObject(obj);
    ObjectSample* BG = new ObjectSample();
    addObject(BG);
    BG->scl.setVec(10000, 10000, 1);
    BG->col.setCol(1, 1., 1, 0.5);
    BG->pos.addVec(0, 0, 100);
}

void SceneSample::SceneMain() {
    checkKey();
    if (listObject.size() != 0) {
        camera.posY = listObject.at(0)->pos.y;
        camera.posX = listObject.at(0)->pos.x;
    }
    for (int i = 0; i < listObject.size(); i++) {
        listObject.at(i)->ObjectMain();
    }
    gmanager->applyCamera(&camera);
}

void SceneSample::checkKey() {
    if (gmanager->imanager->getKey(KEY::Z)) {
        for (int i = 0; i < 1; i++) {
            static int NUMBER = 0;
            ObjectBullet* obj = new ObjectBullet();
            addObject(obj);
            obj->scl.setVec(1000, 1000, 1);
            obj->speed.addVec(-1, -1, 0);
            obj->pos.addVec(0, 0, 0); // 1. * (float)NUMBER / 100000000.);
            if (NUMBER == INT_MAX / 2) {
                NUMBER = 0;
            }
            NUMBER++;
        }
    }
    if (gmanager->imanager->getKey(KEY::C)) {
        SceneSample* newSample = new SceneSample();
        std::cout << "change current " << std::endl;
        gmanager->changeCurrent(newSample);
        return;
    }
    if (gmanager->imanager->getKey(KEY::DOWN)) {
        if (listObject.size() != 0) {
            ObjectGame* objPtr = listObject.at(0);
            deleteObject(objPtr);
        }
    }
    if (gmanager->imanager->getKey(KEY::UP)) {
    }
}