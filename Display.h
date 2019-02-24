//
// Created by florian on 24/02/19.
//

#ifndef CLIPPING_DISPLAY_H
#define CLIPPING_DISPLAY_H


#include "Polygon.h"

namespace Clipping {
    class Display {
    public:
        static void render();

    private:
        static void displayPolygon(const Polygon &polygon, unsigned int color);
    };
}


#endif //CLIPPING_DISPLAY_H
