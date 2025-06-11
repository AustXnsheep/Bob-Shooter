//
// Created by nick on 6/10/25.
//

#ifndef TYPEMARKERS_H
#define TYPEMARKERS_H

/*
 * A class can extend all 3 of these at once.
 * Using the onInteract method you'll be able
 * effectively do anything
 */

class Interactable {
public:
    virtual ~Interactable() = default;
    virtual void onInteract(Entity* other) = 0;
};

class Attacker {
public:
    float damage = 0.0f;
    virtual ~Attacker() = default;
};

class Damageable {
public:
    float health{};
    virtual ~Damageable() = default;
    virtual void applyDamage(float &damage) = 0;
};



#endif //TYPEMARKERS_H
