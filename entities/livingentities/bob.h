//
// Created by nick on 6/9/25.
//

#ifndef BOB_H
#define BOB_H
#include "../entity.h"
#include "../typemarkers.h"


class Bob final : public Entity, public Interactable, public Damageable {
public:
    Bob(Vector3 pos, float spd, Color col);
    ~Bob() override;

    void applyDamage(float &damage) override;
    void onInteract(Entity* other) override;
    void update(const Camera &camera, float &deltaTime) override;
    void draw() const override;
};



#endif //BOB_H
