#include "../include/Scene.hpp"
#include "../include/ObjectGame.hpp"

void ObjectBlock::initObject(Scene* in_scene) {
    scene = in_scene;
}

void ObjectBlock::ObjectMain() {
    scene->drawObject(this);
}

bool ObjectBlock::isTouchable(){
    return touchable;
}