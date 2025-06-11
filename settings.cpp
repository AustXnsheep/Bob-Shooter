//
// Created by nick on 6/8/25.
//

#include "settings.h"

namespace Settings {
    float zoom_sensitivity = 0.25f;
    float current_zoom = 1.0f;
    float min_zoom_distance = 0.25f;
    float max_zoom_distance = 2.5f;

    void loadDefaults() {
        zoom_sensitivity = 0.25f;
        min_zoom_distance = 1.0f;
        current_zoom = 1.0f;
        max_zoom_distance = 5.0f;
    }
} // Settings