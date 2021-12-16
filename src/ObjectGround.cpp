#include "../include/Scene.hpp"
#include "../include/ObjectGame.hpp"

void ObjectGround::initObject(Scene* in_scene) {
    scene = in_scene;
}

void ObjectGround::ObjectMain() {
    scene->drawObject(this);
}
