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

int vp_width = 640;
int vp_height = 480;

std::array<int, 2> currentPt;
std::vector<std::array<int, 2>> pts;
bool closed = false;

void draw_polygon(int button, int state, int x, int y)
{
    currentPt = std::array<int, 2>{x, vp_height-y};

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if ( closed )
            pts.clear(); // restart if last action was close
        closed = false;
        if (Clipping::scene.doFilling) {
            std::cout << "Adding point " << x << ';' << y << " to fill start points" << std::endl;
            Clipping::scene.fillStartPoints.push_back({x, vp_height - y});
        }
        else {
            pts.push_back(currentPt);
        }
    }
    if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && pts.size() >= 3) {
        closed = true;
        if (Clipping::scene.mode == 0) {
            Clipping::scene.polygons.push_back(Clipping::Polygon{pts});
        } else if (Clipping::scene.mode == 1) {
            Clipping::scene.windows.push_back(Clipping::Polygon{pts});
        }
        pts.clear();
        glutPostRedisplay();
    }
}


void mouse_move(int x, int y)
{
    currentPt = std::array<int, 2>{x, vp_height-y};
    auto color = Clipping::Filler::getPixelColor(x, vp_height - y);
    if (!Clipping::scene.doFilling) {
        glutPostRedisplay();
    }
}

std::vector<std::array<float, 3>> colors = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 0}
};

void display(void)
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!pts.empty()) {
        int mode = Clipping::scene.mode;
        glColor3f(colors[Clipping::scene.colors[mode]][0],
                  colors[Clipping::scene.colors[mode]][1],
                  colors[Clipping::scene.colors[mode]][2]);

        glBegin(GL_LINE_STRIP);
        for (auto &pt : pts)
            glVertex2f((float) pt[0], (float) pt[1]);
        auto &endPt = closed ? pts.front() : currentPt;
        glVertex2f((float) endPt[0], (float) endPt[1]);
        glEnd();
    }

    for(const Clipping::Polygon &polygon : Clipping::scene.polygons) {
        std::vector<std::array<int, 2>> pts = polygon.points;
        glColor3f(colors[Clipping::scene.colors[0]][0],
                  colors[Clipping::scene.colors[0]][1],
                  colors[Clipping::scene.colors[0]][2]);
        glBegin(GL_LINE_STRIP);
        for (auto &pt : pts)
            glVertex2f((float) pt[0], (float) pt[1]);
        auto &endPt = pts.front();
        glVertex2f((float) endPt[0], (float) endPt[1]);
        glEnd();
    }

    for (const auto &point : Clipping::scene.fillStartPoints) {
        int x = point[0];
        int y = point[1];
        std::cout << "Filling starting at " << x << ";" << y << std::endl;
        Clipping::Filler::RemplissageLigne(x, y, {255, 0, 0}, {1, 0, 0});
    }

    for(const Clipping::Polygon &window : Clipping::scene.windows) {
        std::vector<std::array<int, 2>> pts = window.points;
        glColor3f(colors[Clipping::scene.colors[1]][0],
                  colors[Clipping::scene.colors[1]][1],
                  colors[Clipping::scene.colors[1]][2]);
        glBegin(GL_LINE_STRIP);
        for (auto &pt : pts)
            glVertex2f((float) pt[0], (float) pt[1]);
        auto &endPt = pts.front();
        glVertex2f((float) endPt[0], (float) endPt[1]);
        glEnd();
    }

    //glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(640, 480);
    glutInitWindowPosition((1920 - 640) / 2, 0);
    glutCreateWindow("OpenGL clipping");

    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouse_move);
    glutMouseFunc(draw_polygon);

    glMatrixMode( GL_PROJECTION );
    glOrtho(0.0f, (float)vp_width, 0.0f, (float)vp_height, -1.0, 1.0);

    Clipping::GUI::registerGUI();

    glutMainLoop();

    return 0;
}
