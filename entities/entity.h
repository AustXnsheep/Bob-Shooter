//
// Created by nick on 6/7/25.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>
#include <string>

#include "../uuid/uuid.h"

/*
 * This class for now is defined for entities exclusively.
 * Once I add static objects I'll need to make come changes.
 */

class Entity {
protected:
    bool markedForDeletion = false;

public:
    Vector3 position{};
    float speed{};
    float yaw{};
    Color color{};
    std::string uuid;
    bool is_dead = false;
    float interactionRange = 0.5f;

    Entity() {
        uuid =  UUID::generateSimpleUUID();
    }

    virtual ~Entity() = default;

    virtual void update(const Camera& camera, float &deltaTime) = 0;

    virtual void draw() const = 0;

    void clearDeletionFlag() {
        markedForDeletion = false;
    }

    void markForDeletion() {
        markedForDeletion = true;
    }

    bool isMarkedForDeletion() const {
        return markedForDeletion;
    }
};

#endif //ENTITY_H
