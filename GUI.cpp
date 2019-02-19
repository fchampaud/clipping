//
// Created by florian on 29/01/19.
//

#include <GL/glut.h>
#include "GUI.h"
#include "Scene.h"
#include "Business.h"

void Clipping::GUI::registerGUI() {
    int polygonColorMenu = glutCreateMenu(Clipping::GUI::handlePolygonColorMenu);
    glutAddMenuEntry("red", 1);
    glutAddMenuEntry("green", 2);
    glutAddMenuEntry("blue", 3);
    glutAddMenuEntry("yellow", 4);
    int windowColorMenu = glutCreateMenu(Clipping::GUI::handleWindowColorMenu);
    glutAddMenuEntry("red", 1);
    glutAddMenuEntry("green", 2);
    glutAddMenuEntry("blue", 3);
    glutAddMenuEntry("yellow", 4);
    int clippedColorMenu = glutCreateMenu(Clipping::GUI::handleClippedColorMenu);
    glutAddMenuEntry("red", 1);
    glutAddMenuEntry("green", 2);
    glutAddMenuEntry("blue", 3);
    glutAddMenuEntry("yellow", 4);
    int fillColorMenu = glutCreateMenu(Clipping::GUI::handleFillColorMenu);
    glutAddMenuEntry("red", 1);
    glutAddMenuEntry("green", 2);
    glutAddMenuEntry("blue", 3);
    glutAddMenuEntry("yellow", 4);

    int colorMenu = glutCreateMenu(Clipping::GUI::handleColorMenu);
    glutAddSubMenu("polygon color", polygonColorMenu);
    glutAddSubMenu("window color", windowColorMenu);
    glutAddSubMenu("clipped polygon color", clippedColorMenu);
    glutAddSubMenu("fill color", fillColorMenu);

    int menu = glutCreateMenu(Clipping::GUI::handleMainMenu);
    glutAddSubMenu("colors", colorMenu);
    glutAddMenuEntry("draw polygon to clip", 1);
    glutAddMenuEntry("draw clipping window", 2);
    glutAddMenuEntry("do the clipping", 3);
    glutAddMenuEntry("do the filling", 4);
    glutAddMenuEntry("clear everything", 5);

    glutAttachMenu(GLUT_MIDDLE_BUTTON);
}

void Clipping::GUI::handleMainMenu(int entry) {
    if (entry == 1 or entry == 2) {
        Clipping::scene.mode = entry - 1;
    } else if (entry == 3) { // Clipping
        Clipping::Business::doTheClipping();
    } else if (entry == 4) { // Filling
        Clipping::Business::doTheFilling();
    } else if (entry == 5) { // Clear
        Clipping::scene.polygons.clear();
        Clipping::scene.clippedPolygons.clear();
        Clipping::scene.windows.clear();
    }
    glutPostRedisplay();
}

void Clipping::GUI::handlePolygonColorMenu(int entry) {
    Clipping::scene.colors[0] = entry - 1;
    glutPostRedisplay();
}

void Clipping::GUI::handleWindowColorMenu(int entry) {
    Clipping::scene.colors[1] = entry - 1;
    glutPostRedisplay();
}

void Clipping::GUI::handleClippedColorMenu(int entry) {
    Clipping::scene.colors[2] = entry - 1;
    glutPostRedisplay();
}

void Clipping::GUI::handleFillColorMenu(int entry) {
    Clipping::scene.colors[3] = entry - 1;
    glutPostRedisplay();
}

void Clipping::GUI::handleColorMenu(int entry) {
    // Does nothing, useless but needed as function pointer
}
