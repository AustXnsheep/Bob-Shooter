//
// Created by nick on 6/7/25.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

bool GetMouseRayHitOnPlaneY0(Vector2 mousePos, Camera camera, Vector2 *hit2D);

class Player final : public Entity, public Interactable {
public:
    Player(Vector3 pos, float spd, Color col);

    void onInteract(Entity* other) override;
    void update(const Camera &camera, float &deltaTime) override;
    void draw() const override;
};

#endif //PLAYER_H
