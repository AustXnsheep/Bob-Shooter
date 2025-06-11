//
// Created by nick on 6/9/25.
//

#include "bob.h"
#include "../../world.h"
#include "../../entities/entities.h"
#include "raymath.h"
#include <cmath>
#include <memory>

#include "rlgl.h"

Bob::Bob(Vector3 pos, float spd, Color col) {
    this->position = pos;
    this->speed = spd;
    this->color = col;
    this->health = 100.0f;
}

Bob::~Bob() = default;

void Bob::onInteract(Entity* other) {
    const auto* attacker = dynamic_cast<Attacker*>(other);
    if (attacker) {
        float damage = attacker->damage;
        applyDamage(damage);
    }
}

void Bob::applyDamage(float &damage) {
    health -= damage;
    if (health <= 0) {
        markForDeletion();
    }
}


void Bob::update(const Camera &camera, float &deltaTime) {
    if (!World::player) return;

    Vector3 dir = Vector3Subtract(World::player->position, position);
    dir.y = 0.0f;

    float distance = Vector3Length(dir);
    if (distance > 0.1f) {
        dir = Vector3Normalize(dir);
        Vector3 movement = Vector3Scale(dir, speed * deltaTime);
        position = Vector3Add(position, movement);

        yaw = -atan2f(dir.z, dir.x);
    }
}

void Bob::draw() const {
    Matrix rotation = MatrixRotateY(yaw);
    Matrix translation = MatrixTranslate(position.x, position.y, position.z);
    Matrix transform = MatrixMultiply(rotation, translation);

    rlPushMatrix();
    rlMultMatrixf(MatrixToFloat(transform));
    DrawCube((Vector3){0, 0.5f, 0}, 1.0f, 1.0f, 1.0f, color);
    DrawCubeWires((Vector3){0, 0.5f, 0}, 1.0f, 1.0f, 1.0f, BLACK);
    rlPopMatrix();
}
