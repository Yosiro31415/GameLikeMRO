#include "../include/Scene.hpp"
#include "../include/ObjectGame.hpp"
#include "../include/resource.hpp"
void ObjectPlayer::initObject(Scene* in_scene) {
    scene = in_scene;
    numTexture = BOLD;
    col.setCol(1, 1, 1, 1);
    pos.setVec(0, 0, -5);
}
void ObjectPlayer::ObjectMain() {
    AttenuateSpeed();
    applyGravity();
    applyAccel();
    applySpeed();
    checkKey();
    scene->drawObject(this);
}

void ObjectPlayer::checkKey() {
    static int numPush = 0;
    bool isJumped = false;
    if (scene->gmanager->imanager->getKey(KEY::LEFT)) {
        pos.addVec(-10, 0, 0);
    }
    if (scene->gmanager->imanager->getKey(KEY::RIGHT)) {
        pos.addVec(10, 0, 0);
    }
    if (scene->gmanager->imanager->getKey(KEY::Z)) {
        if (numPush < 1) {
            VecObject jump;
            jump.setVec(0, 15, 0);
            speed.addVec(&jump);
            isJumped = true;
        }
    }
    if (isJumped) {
        numPush++;
    } else {
        numPush = 0;
    }
}