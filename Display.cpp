//
// Created by florian on 24/02/19.
//

#include <GL/glew.h>
#include <iostream>
#include "Display.h"
#include "Scene.h"
#include "Filler.h"

void Clipping::Display::render() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!Clipping::scene.pts.empty()) {
        int mode = Clipping::scene.mode;
        glColor3f(Clipping::scene.colorPalette[Clipping::scene.colors[mode]][0],
                  Clipping::scene.colorPalette[Clipping::scene.colors[mode]][1],
                  Clipping::scene.colorPalette[Clipping::scene.colors[mode]][2]);
        glBegin(GL_LINE_STRIP);
        for (auto &pt : Clipping::scene.pts)
            glVertex2f((float) pt[0], (float) pt[1]);
        auto &endPt = (Clipping::scene.closed ? Clipping::scene.pts.front()
                                              : Clipping::scene.currentPt);
        glVertex2f((float) endPt[0], (float) endPt[1]);
        glEnd();
    }

    for(const Clipping::Polygon &polygon : Clipping::scene.polygons) {
        displayPolygon(polygon, 0);
    }

    for (const auto &point : Clipping::scene.fillStartPoints) {
        int x = point[0];
        int y = point[1];
        std::cout << "Filling starting at " << x << ";" << y << std::endl;
        std::array<float, 3> fillColor = Clipping::scene.colorPalette[Clipping::scene.colors[3]];
        std::array<int, 3> intFillColor = {static_cast<int>(fillColor[0] * 255),
                                           static_cast<int>(fillColor[1] * 255),
                                           static_cast<int>(fillColor[2] * 255)};
        Clipping::Filler::RemplissageLigne(x, y, {255, 0, 0}, intFillColor);
    }

    for(const Clipping::Polygon &window : Clipping::scene.windows) {
        displayPolygon(window, 1);
    }

    for(const Clipping::Polygon &polygon : Clipping::scene.clippedPolygons) {
        displayPolygon(polygon, 2);
    }

    glutSwapBuffers();
}

void Clipping::Display::displayPolygon(const Clipping::Polygon &polygon, unsigned int color) {
    std::vector<std::array<int, 2>> pts = polygon.points;
    const auto &endPt = pts.front();

    glColor3f(Clipping::scene.colorPalette[Clipping::scene.colors[color]][0],
              Clipping::scene.colorPalette[Clipping::scene.colors[color]][1],
              Clipping::scene.colorPalette[Clipping::scene.colors[color]][2]);

    glBegin(GL_LINE_STRIP);
    for (auto &pt : pts) {
        glVertex2f((float) pt[0], (float) pt[1]);
    }
    glVertex2f((float) endPt[0], (float) endPt[1]);
    glEnd();
}
