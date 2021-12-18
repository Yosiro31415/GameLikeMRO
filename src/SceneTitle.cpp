#include "../include/Scene.hpp"
#include "../include/ObjectGame.hpp"
#include "../include/resource.hpp"

void SceneTitle::initScene(GameManager* in_gmanager, D3DManager* in_dmanager) {
    gmanager = in_gmanager;
    model.init(in_dmanager);
    in_dmanager->createCamera(WindowSize::width, WindowSize::height, &camera);
    camera.posZ = -20.f;
    ObjectTab* BG = new ObjectTab();
    BG->pos.setVec(0, 0, 0);
    for (int i = 0; i < 2; i++) {
        ObjectTab* obj = new ObjectTab();
        obj->numThis = obj->numObj();
        obj->scl.setVec(1000, 200, 10);
        obj->deg.setVec(0, 0, 0);
        obj->col.setCol(0.6, 0.6, 0.6, 1);
        if (obj->numThis == 1) {
            obj->numTexture = BOLD;
            obj->pos.setVec(-600, 150, 0);
        } else if (obj->numThis == 2) {
            obj->numTexture = BOLD;
            obj->pos.setVec(600, 150, 0);
        }
        obj->pos.addVec(0, -600, 0);
        addObject(obj);
    }
    listObject.at(0)->col.setVec(1,1,1);
    BG->numTexture = BOLD;
    addObject(BG);
    BG->scl.setVec(10000, 10000, 100);
    BG->col.setCol(0.9, 0.9, 0.9,1);
}

void SceneTitle::SceneMain() {
    checkKey();
    gmanager->applyCamera(&camera);
    for (int i = 0; i < listObject.size(); i++) {
        listObject.at(i)->ObjectMain();
    }
}
void SceneTitle::checkKey() {
    static bool consecutive = false;
    if (gmanager->imanager->getKey(KEY::LEFT) && !consecutive) {
        listObject.at(currentTab)->col.setVec(0.6, 0.6, 0.6);
        currentTab = 0;
        listObject.at(currentTab)->col.setVec(1, 1, 1);
        std::cout << currentTab << std::endl;
        consecutive = true;
    } else if (gmanager->imanager->getKey(KEY::RIGHT) && !consecutive) {
        listObject.at(currentTab)->col.setVec(0.6, 0.6, 0.6);
        currentTab = 1;
        listObject.at(currentTab)->col.setVec(1, 1, 1);
        std::cout << currentTab << std::endl;
        consecutive = true;
    } else if (gmanager->imanager->getKey(KEY::Z) && !consecutive) {
        if (currentTab == 0) {
            SceneStageSelect* sceneNext = new SceneStageSelect();
            gmanager->changeCurrent(sceneNext);
            consecutive = true;
        } else if (currentTab == 1) {
            PostQuitMessage(0);
            consecutive = true;
        } else {
            consecutive = false;
        }
    } else {
        consecutive = false;
        return;
    }
    return;
}