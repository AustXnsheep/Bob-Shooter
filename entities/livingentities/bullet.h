//
// Created by nick on 6/7/25.
//

#ifndef BULLET_H
#define BULLET_H
#include "raylib.h"
#include "../typemarkers.h"


class Bullet final : public Entity, public Interactable, public Attacker {
public:
    std::string shooter_uuid;
    int life_time;
    Bullet(Vector3 pos, float spd, float yaw, std::string uuid);

    void onInteract(Entity* other) override;
    void update(const Camera &camera, float &deltaTime) override;
    void draw() const override;
};



#endif //BULLET_H
