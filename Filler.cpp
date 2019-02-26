//
// Created by esteban on 20/02/2019.
//

#include <array>
#include "stack"
#include <vector>
#include "Filler.h"
#include "Scene.h"
#include "clipper.h"
#include <GL/gl.h>
#include <iostream>

/**
 * Fills starting at point {x;y}, using passed border color and fill color
 * @param x The x point at which filling will start
 * @param y The y point at which filling will start
 * @param CC The R,G,B components of the border color
 * @param CR The R,G,B components of the fill color
 */
void Clipping::Filler::fill(int x, int y, std::array<int, 3> CC, std::array<int, 3> CR){
    std::stack<std::vector<int>> Pile;
    std::vector<int> temp {x,y};
    Pile.push(temp);
    std::array<int,3> CP  = {0,0,0};
    std::array<int,3> CPd = {0,0,0};
    std::array<int,3> CPg = {0,0,0};
    int Xd,Xg;
    while (!Pile.empty()){
        std::vector<int> temp2 (Pile.top());
        Pile.pop();
        x= temp2[0];
        y= temp2[1];
        Xd = x+1;
        CP = getPixelColor(Xd,y);
        CPd = CP;
        while(CPd != CC && Xd<Clipping::vp_width){
            Xd = Xd+1;
            CPd = getPixelColor(Xd,y);
        }
        Xg = x-1;
        CP = getPixelColor(Xg,y);
        CPg= CP;
        while(CPg != CC && Xg>0){
            Xg = Xg-1;
            CPg = getPixelColor(Xg,y);
        }
        Xg = Xg+1;
        Xd = Xd-1;
        drawLine(Xg,y,Xd+1,CR);

        x = Xd;
        CP = getPixelColor(x,y+1);

        while(x>=Xg){
            while((CP==CC || CP==CR) && x>=Xg){
                x=x-1;
                CP = getPixelColor(x,y+1);
            }
            if(x>Xg && CP!=CC && CP!=CR && y+1 < Clipping::vp_height){
                std::vector<int> temp3 {x,y+1};
                Pile.push(temp3);
            }
            while (CP!=CC && x>=Xg){
                x=x-1;
                CP = getPixelColor(x,y+1);
            }
        }
        x=Xd;
        CP = getPixelColor(x,y-1);
        while(x>=Xg){
            while((CP==CC || CP==CR) && x>=Xg){
                x=x-1;
                CP = getPixelColor(x,y-1);
            }
            if(x>Xg && CP!=CC && CP!=CR && y > 0){
                std::vector<int> temp3 {x,y-1};
                Pile.push(temp3);
            }
            while (CP!=CC && x>=Xg){
                x=x-1;
                CP = getPixelColor(x,y-1);
            }
        }

    }
}

/**
 * Returns the pixel color at passed position
 * @param x The x position of the pixel to retrieve
 * @param y The y position of the pixel to retrieve
 * @return An array containing the R,G,B components of the pixel's color
 */
std::array<int,3> Clipping::Filler::getPixelColor(int x,int y){

    unsigned char pixel[4];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    //std::cout << "x: " << x << "y: " << y;
    //std::cout << " R: " << (int)pixel[0];
    //std::cout << " G: " << (int)pixel[1];
    //std::cout << " B: " << (int)pixel[2] << std::endl;
    //std::cout << std::endl;
    return {(int)pixel[0],(int)pixel[1],(int)pixel[2]};
}

/**
 * Draws a line between two points on the same y position
 * @param x1 The first x position, where drawing starts
 * @param y1 The second x position, where drawing ends
 * @param x2 The y position at which drawing takes place
 * @param C The R,G,B components of the color to use for drawing
 */
void Clipping::Filler::drawLine(int x1,int y1,int x2 ,std::array<int,3> C){
    glBegin(GL_POINTS);
    glColor3f(C[0],C[1],C[2]);
    for (int i = x1; i < x2; ++i) {
        glVertex2f(i, y1);
    }
    glEnd();
}
