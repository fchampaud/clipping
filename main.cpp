#include <GL/glew.h>

#ifdef FREEGLUT
#include <GL/freeglut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <array>
#include <iostream>

#include "GUI.h"
#include "Scene.h"
#include "Business.h"
#include "Filler.h"
#include "Display.h"

void handle_mouse_button(int button, int state, int x, int y)
{
    Clipping::scene.currentPt = std::array<int, 2>{x, Clipping::vp_height-y};

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if ( Clipping::scene.closed ) {
            Clipping::scene.pts.clear(); // restart if last action was close
            Clipping::scene.closed = false;
        }

        if (Clipping::scene.mode == 2) {
            Clipping::scene.fillStartPoints.push_back({x, Clipping::vp_height - y});
            glutPostRedisplay();
        } else {
            Clipping::scene.pts.push_back(Clipping::scene.currentPt);
        }
    }
    if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN
                                        && Clipping::scene.pts.size() >= 3) {
        Clipping::scene.closed = true;
        if (Clipping::scene.mode == 0) {
            Clipping::scene.polygons.push_back(Clipping::Polygon{Clipping::scene.pts});
        } else if (Clipping::scene.mode == 1) {
            Clipping::scene.windows.push_back(Clipping::Polygon{Clipping::scene.pts});
        }
        Clipping::scene.pts.clear();
        glutPostRedisplay();
    }
}

void mouse_move(int x, int y)
{
    Clipping::scene.currentPt = std::array<int, 2>{x, Clipping::vp_height-y};
    auto color = Clipping::Filler::getPixelColor(x, Clipping::vp_height - y);
    if (Clipping::scene.mode != 3) {
        glutPostRedisplay();
    }
}

int main(int argc, char** argv)
{
    Clipping::scene.colorPalette = {
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1},
            {1, 1, 0}
    };

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(Clipping::vp_width, Clipping::vp_height);
    glutInitWindowPosition((1920 - Clipping::vp_width) / 2, 0);
    glutCreateWindow("OpenGL clipping");

    glutDisplayFunc(Clipping::Display::render);
    glutPassiveMotionFunc(mouse_move);
    glutMouseFunc(handle_mouse_button);

    glMatrixMode( GL_PROJECTION );
    glOrtho(0.0f, (float)Clipping::vp_width, 0.0f, (float)Clipping::vp_height,
            -1.0, 1.0);

    Clipping::GUI::registerGUI();

    glutMainLoop();

    return 0;
}
