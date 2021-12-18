
#ifndef _HEADER_OBJECTGAME_
#define _HEADER_OBJECTGAME_

#include "../include/HeaderApp.hpp"
class Scene;
struct VecObject {
    float x, y, z;
    virtual void addVec(float in_x, float in_y, float in_z);
    virtual void setVec(float in_x, float in_y, float in_z);
    virtual void addVec(VecObject* in_vec);
    virtual void setVec(VecObject* in_vec);
};

struct ColObject : public VecObject {
    float a;
    void addCol(float in_red, float in_green, float in_blue, float in_alpha);
    void setCol(float in_red, float in_green, float in_blue, float in_alpha);
    void addCol(ColObject* in_col);
    void setCol(ColObject* in_col);
};

struct ObjectGame {
    VecObject pos;
    VecObject scl;
    VecObject deg;
    ColObject col;
    int numThis;
    Scene* scene;
    static int numObj();
    int numTexture;
    virtual void initObject(Scene* in_scene) = 0;
    virtual void ObjectMain() = 0;
};

struct ObjectSample : public ObjectGame {
public:
    void initObject(Scene* in_scene);
    void ObjectMain();
};

struct ObjectBullet : public ObjectGame {
public:
    void initObject(Scene* in_scene);
    void ObjectMain();
    int time = 0;
    VecObject speed;
};

struct ObjectTab : public ObjectGame {
    void initObject(Scene* in_scene);
    void ObjectMain();
};

struct ObjectBlock : public ObjectGame {
    ObjectBlock() {
        col.setCol(1, 1, 1, 1);
        deg.setVec(0, 0, 0);
        scl.setVec(100, 100, 100);
        pos.setVec(0, 0, 0);
    }
    virtual void initObject(Scene* in_scene);
    virtual void ObjectMain();
    bool isTouchable();

protected:
    const bool touchable = true;
};

struct ObjectGround : public ObjectBlock {
    void initObject(Scene* in_scene);
    void ObjectMain();

protected:
    const bool touchable = true;
};

struct ObjectEntitity : public ObjectGame {
protected:
    ObjectEntitity() {
        col.setCol(1, 1, 1, 1);
        deg.setVec(0, 0, 0);
        scl.setVec(100, 100, 100);
        pos.setVec(0, 0, 0);
        speed.setVec(0, 0, 0);
        accel.setVec(0, 0, 0);
    }
    virtual void initObject(Scene* in_scene) = 0;
    virtual void ObjectMain() = 0;
    void applyGravity() {
        accel.addVec(0, -1, 0);
    }
    void applyAccel() {
        speed.addVec(&accel);
    }
    void applySpeed() {
        pos.addVec(&speed);
        if (pos.y < 0) {
            pos.y = 0;
            accel.y = 0;
            speed.y = 0;
        }
    }
    bool isTouchable() {
        return touchable;
    }
    void AttenuateSpeed() {
        if (std::abs(speed.x) > 100) {
            speed.addVec(-speed.x / 10, 0, 0);
        }
    }
    const bool touchable = true;
    VecObject speed;
    VecObject accel;
};

struct ObjectPlayer : public ObjectEntitity {

    virtual void initObject(Scene* in_scene);
    virtual void ObjectMain();
    void checkKey();

protected:
    const bool touchable = true;
};

#endif