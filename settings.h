//
// Created by nick on 6/8/25.
//

#ifndef SETTINGS_H
#define SETTINGS_H

/*
 * This class is going to be more useful later on.
 * Right now it's only used to store zoom data that I
 * didn't want adding length to the main class.
 */

namespace Settings {
    extern float zoom_sensitivity;
    extern float min_zoom_distance;
    extern float current_zoom;
    extern float max_zoom_distance;

    void loadDefaults();

} // Settings

#endif //SETTINGS_H
