#ifndef _HEADER_SCENE_
#define _HEADER_SCENE_

#include "../include/HeaderApp.hpp"
#include "../include/ObjectGame.hpp"
#include "../include/GameManager.hpp"
class GameManager;
class ObjectGame;
class MapGame;
class Scene {
protected:
    Scene();
    Camera camera;
    ModelSquare model;
    std::map<int, Texture*> listTexture = {};
    std::vector<ObjectGame*> listObject = {};
    inline void setModel(ObjectGame* obj) {
        model.colR = obj->col.x;
        model.colG = obj->col.y;
        model.colB = obj->col.z;
        model.colA = obj->col.a;
        model.degX = obj->deg.x;
        model.sclX = obj->scl.x;
        model.posX = obj->pos.x;
        model.degY = obj->deg.y;
        model.sclY = obj->scl.y;
        model.posY = obj->pos.y;
        model.degZ = obj->deg.z;
        model.sclZ = obj->scl.z;
        model.posZ = obj->pos.z;
    };

public:
    virtual ~Scene();
    virtual void addObject(ObjectGame* obj);
    virtual void deleteObject(ObjectGame* obj);
    GameManager* gmanager;
    void addTexture(ObjectGame* obj);
    void drawObject(ObjectGame* obj);
    virtual void initScene(GameManager* in_gmanager, D3DManager* in_dmanager) = 0;
    virtual void SceneMain() = 0;
    virtual void checkKey() = 0;
};

class DummyScene : public Scene {
public:
    void initScene(GameManager* in_gmanager, D3DManager* in_dmanager);
    void SceneMain();
    void checkKey();
};

class SceneSample : public Scene {

public:
    void initScene(GameManager* in_gmanager, D3DManager* in_dmanager);
    void SceneMain();
    void checkKey();
};

class SceneStageSelect : public Scene {
    ObjectGame* chara;
    ObjectGame* BG;

public:
    ~SceneStageSelect();
    void initScene(GameManager* in_gmanager, D3DManager* in_dmanager);
    void SceneMain();
    void checkKey();
    int current = 0;
};

class SceneTitle : public Scene {
public:
    void initScene(GameManager* in_gmanager, D3DManager* in_dmanager);
    void SceneMain();
    void checkKey();
    int currentTab = 0;
};

class SceneStage : public Scene {

private:
    const static int mapHeight = 20;
    ObjectGame* putStageObj(std::string nameObj);
    const std::string pathCSV = "../res/test.csv";

public:
    virtual ~SceneStage();
    ObjectGame* charaPlayer;
    ObjectGame* BG;
    std::vector<std::vector<ObjectGame*>> tileObject;
    std::vector<ObjectGame*> listEntitiy = {};
    virtual void initScene(GameManager* in_gmanager, D3DManager* in_dmanager);
    virtual void SceneMain();
    void checkKey();
    void addEntity(ObjectGame* obj);
    void deleteEntity(ObjectGame* obj);
};

class SceneStageSample : public SceneStage {
private:
    const static int mapHeight = 20;
    ObjectGame* putStageObj(std::string nameObj);
    std::string pathCSV = "../src/stageSample";

public:
};

#endif