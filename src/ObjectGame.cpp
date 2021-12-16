#include "../include/ObjectGame.hpp"
#include "../include/Scene.hpp"
#include "../include/resource.hpp"
void VecObject::addVec(float in_x, float in_y, float in_z) {
    x += in_x;
    y += in_y;
    z += in_z;
}

void VecObject::setVec(float in_x, float in_y, float in_z) {
    x = in_x;
    y = in_y;
    z = in_z;
}

void VecObject::addVec(VecObject* in_vec) {
    x += in_vec->x;
    y += in_vec->y;
    z += in_vec->z;
}

void VecObject::setVec(VecObject* in_vec) {
    x = in_vec->x;
    y = in_vec->y;
    z = in_vec->z;
}

void ColObject::addCol(float in_red, float in_green, float in_blue, float in_alpha) {
    x += in_red;
    y += in_green;
    z += in_blue;
    a += in_alpha;
}

void ColObject::setCol(float in_red, float in_green, float in_blue, float in_alpha) {
    x = in_red;
    y = in_green;
    z = in_blue;
    a = in_alpha;
}

void ColObject::addCol(ColObject* in_vec) {
    x += in_vec->x;
    y += in_vec->y;
    z += in_vec->z;
    a += in_vec->a;
}

void ColObject::setCol(ColObject* in_vec) {
    x = in_vec->x;
    y = in_vec->y;
    z = in_vec->z;
    a = in_vec->a;
}

int ObjectGame::numObj() {
    static int number = 0;
    number++;
    return number;
}

void ObjectSample::initObject(Scene* in_scene) {
    scene = in_scene;
    numTexture = 100;
    pos.setVec(0, 0, 0);
    scl.setVec(1, 1, 1);
    deg.setVec(0, 0, 0);
    col.setCol(1, 1, 1, 1);
}

void ObjectSample::ObjectMain() {
    scene->drawObject(this);
    return;
}

void ObjectBullet::initObject(Scene* in_scene) {
    scene = in_scene;
    int numObjTemp = numObj();
    if (numObjTemp % 3 == 1) {
        numTexture = CIRCLE;
    } else if (numObjTemp % 3 == 0) {
        numTexture = CIRCLE;
    } else {
        numTexture = CIRCLE;
    }
    pos.setVec(0, 0, 0);
    scl.setVec(20, 20, 0.5);
    deg.setVec(0, 0, 0);
    col.setCol(1, 0, 0, 1);
    VecObject ran;
    ran.setVec(0.1 * Random::Num(1, -1), 0.1 * Random::Num(1, -1), 0);
    speed.setVec(20 * std::cos(numObjTemp), 20 * std::sin(numObjTemp), 0);
    speed.addVec(&ran);
}

void ObjectBullet::ObjectMain() {
    pos.addVec(&speed);
    scene->drawObject(this);
    time++;
    if (time > 100000) {
        scene->deleteObject(this);
    }
    return;
}