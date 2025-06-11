//
// Created by nick on 6/7/25.
//

#include "../../world.h"
#include "../entities.h"
#include <cmath>
#include <memory>
#include "raymath.h"
#include "rlgl.h"

bool GetMouseRayHitOnPlaneY0(Vector2 mousePos, const Camera &camera, Vector3 *hitPoint) {
    Ray ray = GetMouseRay(mousePos, camera);

    Vector3 planePoint = { 0.0f, 0.0f, 0.0f };
    Vector3 planeNormal = { 0.0f, 1.0f, 0.0f };

    float denom = Vector3DotProduct(ray.direction, planeNormal);

    if (fabs(denom) > 0.0001f) {
        Vector3 diff = Vector3Subtract(planePoint, ray.position);
        float t = Vector3DotProduct(diff, planeNormal) / denom;

        if (t >= 0) {
            *hitPoint = Vector3Add(ray.position, Vector3Scale(ray.direction, t));
            return true;
        }
    }
    return false;
}

Player::Player(Vector3 pos, float spd, Color col) {
    this->position = pos;
    this->speed = spd;
    this->color = col;
    this->is_dead = false;
}

void Player::onInteract(Entity* other) {

}

void Player::update(const Camera& camera, float &deltaTime) {
    Vector3 mouseWorldPos3D;
    if (GetMouseRayHitOnPlaneY0(GetMousePosition(), camera, &mouseWorldPos3D)) {
        float dx = mouseWorldPos3D.x - position.x;
        float dz = mouseWorldPos3D.z - position.z;
        yaw = -atan2f(dz, dx);
    }

    float moveSpeed = speed * deltaTime;

    if (IsKeyDown(KEY_W)) position.z += moveSpeed;
    if (IsKeyDown(KEY_S)) position.z -= moveSpeed;
    if (IsKeyDown(KEY_D)) position.x -= moveSpeed;
    if (IsKeyDown(KEY_A)) position.x += moveSpeed;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        std::unique_ptr<Entity> bullet(new Bullet(position, 50.0f, yaw, uuid));
        World::addEntity(std::move(bullet));
    }
}



void Player::draw() const {
    Matrix rotation = MatrixRotateY(yaw);
    Matrix translation = MatrixTranslate(position.x, position.y, position.z);

    // Apply rotation first, then translation:
    Matrix transform = MatrixMultiply(rotation, translation);

    rlPushMatrix();
    rlMultMatrixf(MatrixToFloat(transform));
    DrawCube((Vector3){0, 0.5f, 0}, 1.0f, 1.0f, 1.0f, color);
    DrawCubeWires((Vector3){0, 0.5f, 0}, 1.0f, 1.0f, 1.0f, BLACK);
    rlPopMatrix();
}

