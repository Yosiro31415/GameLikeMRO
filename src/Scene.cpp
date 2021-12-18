#include "../include/Scene.hpp"

Scene::Scene() {
    return;
}

void Scene::addObject(ObjectGame* obj) {
    obj->initObject(this);
    listObject.push_back(obj);
    if (listTexture.count(obj->numTexture) == 0) {
        Texture* text = new Texture();
        listTexture.insert(std::make_pair(obj->numTexture, text));
        gmanager->createTexture(obj->numTexture, listTexture.at(obj->numTexture));
    }
}

void Scene::addTexture(ObjectGame* obj) {
    Texture* text = new Texture();
    listTexture.insert(std::make_pair(obj->numTexture, text));
    gmanager->createTexture(obj->numTexture, listTexture.at(obj->numTexture));
};

void Scene::deleteObject(ObjectGame* obj) {
    auto it = remove(listObject.begin(), listObject.end(), obj);
    listObject.erase(it, listObject.end());
    delete obj;
}

Scene::~Scene() {
    while (listObject.size() != 0) {
        deleteObject(listObject.at(0));
        std::cout << "deleted object " << listObject.size() << " objects are still there" << std::endl;
    }
    std::cout << "Size of Texture " << listTexture.size() << std::endl;
    for (auto i = listTexture.begin(); i != listTexture.end(); i++) {
        delete i->second;
    }
    listTexture.clear();
    std::cout << "Size of Texture " << listTexture.size() << std::endl;
}

void Scene::drawObject(ObjectGame* obj) {
    // static Texture* tex = new Texture();
    // gmanager->dmanager->createTexture(101, tex);
    // setModel(obj);
    // gmanager->dmanager->applyTexture(tex);
    // Deb::cout("hige");
    // gmanager->dmanager->drawModel(&model);
    setModel(obj);
    gmanager->setIdea(&model, listTexture.at(obj->numTexture));
    gmanager->drawIdea();
}
