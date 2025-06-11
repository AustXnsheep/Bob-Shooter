//
// Created by nick on 6/7/25.
//

#ifndef UUID_H
#define UUID_H

#include <string>

/*
 * This might seem pointless but I didn't like the idea of
 * getting an entire library just so I can make UUIDs.
 * It's probably unsafe the way I've made it, but
 * whatever for now.
 */

namespace UUID {
    std::string generateSimpleUUID();
} // UUID

#endif //UUID_H
