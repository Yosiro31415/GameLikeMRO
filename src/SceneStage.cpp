#include "../include/Scene.hpp"
#include "../include/ObjectGame.hpp"
#include "../include/resource.hpp"

SceneStage::~SceneStage() {
    delete charaPlayer;
    delete BG;
    for (int i = 0; i < tileObject.size(); i++) {
        for (int j = 0; j < mapHeight; j++) {
            delete tileObject.at(i).at(j);
        }
    }
    for (int i = 0; i < listEntitiy.size(); i++) {
        delete listEntitiy.at(i);
    }
}

void SceneStage::initScene(GameManager* in_gmanager, D3DManager* in_dmanager) {
    gmanager = in_gmanager;
    model.init(in_dmanager);
    in_dmanager->createCamera(WindowSize::width, WindowSize::height, &camera);
    camera.posZ = -20.f;

    ObjectTab* player = new ObjectTab();
    charaPlayer = player;
    charaPlayer->initObject(this);
    charaPlayer->numTexture = CIRCLE;
    addTexture(charaPlayer);
    charaPlayer->col.setCol(0.5, 0.5, 0.5, 1);
    charaPlayer->deg.setVec(0, 0, 0);
    charaPlayer->scl.setVec(100, 100, 1);
    charaPlayer->pos.setVec(1, 1, 1);

    ObjectTab* BackGround = new ObjectTab();
    BG = BackGround;
    BackGround->numTexture = BOLD;
    BackGround->initObject(this);
    addTexture(BackGround);
    BackGround->col.setCol(0.5, 0.5, 0.5, 1);
    BackGround->deg.setVec(0, 0, 0);
    BackGround->pos.setVec(0, 0, 10);
    BackGround->scl.setVec(10000, 10000, 1);

    std::fstream test("../res/test.csv");
    std::string strBuff;
    int numColum = 0;
    int numLine = 0;
    bool isEOF = false;

    while ((std::getline(test, strBuff))) {
        std::istringstream iStream(strBuff);
        std::string strConmaBuff;
        Deb::cout(strBuff);
        numColum = 0;
        std::vector<ObjectGame*> objLine = {};
        while (getline(iStream, strConmaBuff, ',')) {
            Deb::cout(strConmaBuff);
            if (strConmaBuff != "[EOF]") {
                objLine.push_back(putStageObj(strConmaBuff));
                Deb::cout(std::to_string(isEOF));
            } else {
                return;
            }
            numColum++;
        }
        numLine++;
        tileObject.push_back(objLine);
    }
}

void SceneStage::SceneMain() {
    // std::cout << "SceneMain called " << std::endl;
    getKey();
    for (int i = 0; i < listObject.size(); i++) {
        // listObject.at(i)->ObjectMain();
    }
    Deb::cout(std::to_string(tileObject.size()));
    for (int i = 0; i < tileObject.size(); i++) {
        // Deb::cout(std::to_string(tileObject.at(i).size()));
    }
    // for (int i = 0; i < tileObject.size(); i++) {
    //     // Deb::cout(i);
    //     for (int j = 0; j < tileObject.at(i).size(); j++) {
    //         Deb::cout(j);
    //         if (tileObject.at(i).at(j) != nullptr) {
    //             Deb::cout("objectmain called");
    //             tileObject.at(i).at(j)->ObjectMain();
    //         }
    //     }
    // }
    for (int i = 0; i < listEntitiy.size(); i++) {
        // listEntitiy.at(i)->ObjectMain();
    }
    charaPlayer->ObjectMain();
    BG->ObjectMain();
    Deb::cout("now");
}

void SceneStage::getKey() {
    if (gmanager->imanager->getKey(KEY::UP)) {
        charaPlayer->scl.addVec(1, 1, 0);
    }
    if (gmanager->imanager->getKey(KEY::DOWN)) {
        charaPlayer->scl.addVec(-1, -1, 0);
    }
}

void SceneStage::addEntity(ObjectGame* obj) {
    listEntitiy.push_back(obj);
    if (listTexture.count(obj->numTexture) == 0) {
        Texture* text = new Texture();
        listTexture.insert(std::make_pair(obj->numTexture, text));
        gmanager->createTexture(obj->numTexture, listTexture.at(obj->numTexture));
    }
}

void SceneStage::deleteEntity(ObjectGame* obj) {
    auto it = remove(listEntitiy.begin(), listEntitiy.end(), obj);
    listEntitiy.erase(it, listEntitiy.end());
    delete obj;
}

ObjectGame* SceneStage::putStageObj(std::string nameObj) {
    if ("" == nameObj)
        return nullptr;
    else if ("0" == nameObj) {
        Deb::cout("nameObj created");
        ObjectGround* obj = new ObjectGround();
        obj->initObject(this);
        return obj;
    } else if (false /* template*/)
        return nullptr;
    else
        return nullptr;
}