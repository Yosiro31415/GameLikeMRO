#include "../include/Scene.hpp"
#include "../include/ObjectGame.hpp"
#include "../include/resource.hpp"

SceneStageSelect::~SceneStageSelect() {
    delete chara;
    delete BG;
};

void SceneStageSelect::initScene(GameManager* in_gmanager, D3DManager* in_dmanager) {
    gmanager = in_gmanager;
    model.init(in_dmanager);
    in_dmanager->createCamera(WindowSize::width, WindowSize::height, &camera);
    camera.posZ = -20.f;
    for (int i = 0; i < STAGE::getStage()->numStage; i++) {
        ObjectTab* stage = new ObjectTab();
        stage->numTexture = BOLD;
        addObject(stage);
        stage->numThis = stage->numObj();
        stage->scl.setVec(150, 150, 50);
        stage->deg.setVec(0, 0, 0);
        stage->col.setCol(1, 1, 1, 1);
        stage->pos.setVec(WindowSize::width * (2 + i) / 7 - WindowSize::width / 2, 0, 5);
    }

    ObjectTab* firstChara = new ObjectTab();
    firstChara->numTexture = STAR;
    firstChara->initObject(this);
    addTexture(firstChara);
    chara = firstChara;
    firstChara->scl.setVec(100, 100, 50);
    firstChara->deg.setVec(0, 0, 0);
    firstChara->col.setCol(1, 0, 0, 1);
    firstChara->pos.setVec(WindowSize::width * (2 + 0) / 7 - WindowSize::width / 2, 100, 0);

    ObjectTab* BackGround = new ObjectTab();
    BackGround->numTexture = BOLD;
    BackGround->initObject(this);
    BG = BackGround;
    BackGround->col.setCol(0.5, 0.5, 0.5, 1);
    BackGround->deg.setVec(0, 0, 0);
    BackGround->pos.setVec(0, 0, 10);
    BackGround->scl.setVec(10000, 10000, 1);
}

void SceneStageSelect::SceneMain() {
    checkKey();
    for (int i = 0; i < listObject.size(); i++) {
        if (current == i) {
        }
        listObject.at(i)->ObjectMain();
    }
    BG->ObjectMain();
    chara->pos.setVec(WindowSize::width * (2 + current) / 7 - WindowSize::width / 2, 150, 0);
    chara->ObjectMain();
}
void SceneStageSelect::checkKey() {
    static bool conse = false;
    if (gmanager->imanager->getKey(KEY::LEFT)) {
        if (!conse && current != 0) {
            if (current > 0) {
                current--;
                conse = true;
            }
        }
    } else if (gmanager->imanager->getKey(KEY::RIGHT)) {
        if (!conse && current != 4) {
            if (STAGE::getStage()->clearFlag[current] && current + 1 < STAGE::getStage()->numStage) {
                current++;
                conse = true;
            }
        }
    } else {
        conse = false;
    }
    return;
}
