//
// Created by florian on 29/01/19.
//

#include <GL/glut.h>
#include "GUI.h"

void Clipping::GUI::handleMainMenu(int entry) {
}

void Clipping::GUI::handleColorMenu(int entry) {
}

void Clipping::GUI::registerGUI() {
    int windowColorMenu = glutCreateMenu(Clipping::GUI::handleWindowColorMenu);
    glutAddMenuEntry("red", 1);
    glutAddMenuEntry("green", 2);
    glutAddMenuEntry("blue", 3);
    glutAddMenuEntry("yellow", 4);
    int polygonColorMenu = glutCreateMenu(Clipping::GUI::handlePolygonColorMenu);
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
    glutAddSubMenu("window color", windowColorMenu);
    glutAddSubMenu("polygon color", polygonColorMenu);
    glutAddSubMenu("clipped polygon color", clippedColorMenu);
    glutAddSubMenu("fill color", fillColorMenu);

    int menu = glutCreateMenu(Clipping::GUI::handleMainMenu);
    glutAddSubMenu("colors", colorMenu);

    glutAttachMenu(GLUT_MIDDLE_BUTTON);
}

void Clipping::GUI::handleWindowColorMenu(int entry) {

}

void Clipping::GUI::handlePolygonColorMenu(int entry) {

}

void Clipping::GUI::handleClippedColorMenu(int entry) {

}

void Clipping::GUI::handleFillColorMenu(int entry) {

}
