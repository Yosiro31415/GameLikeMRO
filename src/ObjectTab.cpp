#include "../include/ObjectGame.hpp"
#include "../include/Scene.hpp"
#include "../include/resource.hpp"
/**
struct ObjectTab : public ObjectGame {
    void initObject(Scene * in_scene);
    void ObjectMain();
};
**/

void ObjectTab::initObject(Scene * in_scene) {
    scene = in_scene;
    std::cout << numThis << std::endl;
}
void ObjectTab::ObjectMain() {
    scene->drawObject(this);
}