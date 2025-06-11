//
// Created by nick on 6/7/25.
//
#include "world.h"

#include <algorithm>
#include <memory>
#include <vector>

#include "entities/entities.h"

namespace World {
    std::vector<std::unique_ptr<Entity>> entities;
    std::unique_ptr<Player> player = nullptr;

    void addEntity(std::unique_ptr<Entity> entity) {
        entities.push_back(std::move(entity));
    }

    void updateEntities(const Camera& camera, float &deltaTIme) {
        cleanupEntities();
        player->update(camera, deltaTIme);
        for (auto& e : entities) {
            e->update(camera, deltaTIme);
        }
    }

    void drawEntities() {
        player->draw();
        for (auto& e : entities) {
            e->draw();
        }
    }

    Entity* getEntity(std::string id) {
        for (auto& e : entities) {
            if (e->uuid == id) {
                return e.get();
            }
        }
        return nullptr;
    }
    void cleanupEntities() {
        entities.erase(
            std::remove_if(entities.begin(), entities.end(),
                [](const std::unique_ptr<Entity>& e) {
                    return e->isMarkedForDeletion();
                }),
            entities.end());
    }
}
