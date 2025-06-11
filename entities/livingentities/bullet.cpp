//
// Created by nick on 6/7/25.
//
#include <cmath>
#include <iostream>
#include <utility>

#include "../entities.h"

Bullet::Bullet(Vector3 pos, float spd, float yaw, std::string uuid) {
    this->position = pos;
    this->speed = spd;
    this->yaw = yaw + (PI/2);
    this->color = RED;
    this->life_time = 0;
    this->damage = 50.0f;
    this->shooter_uuid = std::move(uuid); // I'm really not sure why it recommended to move this.
}

void Bullet::onInteract(Entity *other) {

}


void Bullet::update(const Camera& camera, float &deltaTime) {
    float dx = sinf(yaw) * speed * deltaTime;
    float dz = cosf(yaw) * speed * deltaTime;
    position.x += dx;
    position.z += dz;
    life_time += 1;
    if (life_time >= 300) {
        markForDeletion();
    }
}

void Bullet::draw() const {
    DrawSphere(position, 0.1f, color);
}
