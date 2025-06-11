#include <memory>

#include "raylib.h"
#include "raymath.h"
#include "settings.h"
#include "entities/entities.h"
#include "world.h"

// This is temporary and is bad.
void spawnBob() {
    float x = -20 + static_cast<float>(rand()) / RAND_MAX * (20 - -20);
    float z = -20 + static_cast<float>(rand()) / RAND_MAX * (20 - -20);
    std::unique_ptr<Entity> bob(new Bob(Vector3{x, 0.0f, z}, 20.0f, RED));
    World::addEntity(std::move(bob));
}

void updateCamera(Camera3D &camera, Vector3 &offset) {
    float wheel_move = GetMouseWheelMove();
    float zoom_amount = wheel_move * Settings::zoom_sensitivity;

    Settings::current_zoom -= zoom_amount;

    if (Settings::current_zoom < Settings::min_zoom_distance) {
        Settings::current_zoom = Settings::min_zoom_distance;
    } else if (Settings::current_zoom > Settings::max_zoom_distance) {
        Settings::current_zoom = Settings::max_zoom_distance;
    }

    camera.position = Vector3Add(World::player->position, Vector3Scale(offset, Settings::current_zoom));
}

int main() {
    InitWindow(800, 600, "BlockyStuff");
    SetTargetFPS(144);

    Vector3 cam_offset {0.0F, 10.0F, -15.0F};

    Camera3D camera = { 0 };
    camera.position = { 4.0f, 4.0f, 4.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;

    World::player = std::unique_ptr<Player>(new Player(Vector3{0, 0.0f, 0}, 5.0f, BLUE));

    double lastSpawnTime = 0.0;
    const double spawnInterval = 0.5;

    while (!WindowShouldClose()) {
        float delta_time = GetFrameTime();
        double currentTime = GetTime();

        if (currentTime - lastSpawnTime >= spawnInterval) {
            spawnBob();
            lastSpawnTime = currentTime;
        }

        World::updateEntities(camera, delta_time);
        camera.target = World::player->position;
        updateCamera(camera, cam_offset);


        //  Collision logic
        for (auto& a : World::entities) {
            auto* interactor = dynamic_cast<Interactable*>(a.get());
            if (!interactor) continue;

            for (auto& b : World::entities) {
                if (a == b) continue;

                float distance = Vector3Distance(a->position, b->position);
                float range = a->interactionRange + b->interactionRange;
                if (distance <= range) {
                    interactor->onInteract(b.get());
                }
            }
        }



        BeginDrawing();
        ClearBackground(RAYWHITE);


        BeginMode3D(camera);
        DrawGrid(50, 1.0f);
        World::drawEntities();
        EndMode3D();


        DrawText("Use WASD to move the cube", 10, 10, 20, DARKGRAY);
        DrawText("Left click to shoot", 10, 25, 20, DARKGRAY);
        DrawText("Scroll wheel to zoom in and out", 10, 40, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}