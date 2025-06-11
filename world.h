//
// Created by nick on 6/7/25.
//

#pragma once
#include <memory>
#include <vector>
#include "entities/entities.h"

/*
 * This class will contain any information about
 * the world that I need to access anywhere in the code.
 * I might eventually make these thread safe when I add
 * multiplayer support, but for now this works fine as is.
 */

namespace World {
    extern std::vector<std::unique_ptr<Entity>>  entities;
    extern std::unique_ptr<Player> player;

    void addEntity(std::unique_ptr<Entity> entity);
    void updateEntities(const Camera& camera, float &deltaTIme);
    void drawEntities();
    void cleanupEntities();
    Entity* getEntity(std::string id);
}
