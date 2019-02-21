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

void Clipping::Filler::RemplissageLigne(int x, int y, std::array<int,3> CC,  std::array<int,3> CR){
    std::stack<std::vector<int>> Pile;
    std::vector<int> temp (x,y);
    Pile.push(temp);
    std::array<int,3> CP  = {0,0,0};
    std::array<int,3> CPd = {0,0,0};
    std::array<int,3> CPg = {0,0,0};
    std::cout<<"Start "<<x<<";"<<y<<std::endl;
    int Xd,Xg;
    while (!Pile.empty()){
        std::cout<<"La pile est pleine"<<std::endl;
        std::vector<int> temp2 (Pile.top());
        Pile.pop();
        // CP = couleur(temp2)
        CP = getPixelColor(temp2[0],temp2[1]);
        std::cout<<"CC :"<<CC[0]<<","<<CC[1]<<","<<CC[2]<<std::endl;
        Xd = x+1;
        CPd = CP;
        while(CPd != CC && Xd<640){
            Xd = Xd+1;
            //CPd = couleur de (Xd,y)
            CPd = getPixelColor(Xd,y);
            std::cout<<"Points Cpd: "<<Xd<<";"<<y<<std::endl;
        }

        Xd = Xd-1;
        Xg = x-1;
        CPg= CP;
        while(CPg != CC && Xg>0){
            Xg = Xg-1;
            //CPg = couleur de (Xg,y)
            CPg = getPixelColor(Xg,y);
            std::cout<<"Points CPg: "<<Xg<<";"<<y<<std::endl;
        }

        Xg = Xg+1;
        //On affiche la ligne (Xg,y) (Xd,y)
        drawLine(Xg,y,Xd,CR);
        std::cout<<"Drawn from "<<Xg<<";"<<y<<" and "<<Xd<<";"<<y<<std::endl;
        /*
        x = Xd;
        //Cp = Couleur (x,y+1)
        CP = getPixelColor(x,y+1);

        while(x>=Xg){
            while((CP==CC || CP==CR) && x>=Xg){
                x=x-1;
                //CP = couleur de (x,y+1)
                CP = getPixelColor(x,y+1);
            }
            if(x>Xg && CP!=CC && CP!=CR){
                std::vector<int> temp3 (x,y+1);
                Pile.push(temp3);
            }
            while (CP!=CC && x>=Xg){
                x=x-1;
                //CP = couleur de (x,y+1)
                CP = getPixelColor(x,y+1);
            }
        }
        x=Xd;
        //Cp = couleur de (x,y-1)
        while(x>=Xg){
            while((CP==CC || CP==CR) && x>=Xg){
                x=x-1;
                //CP = couleur (x,y-1)
                CP = getPixelColor(x,y-1);
            }
            if(x>Xg && CP!=CC && CP!=CR){
                std::vector<int> temp3 (x,y-1);
                Pile.push(temp3);
            }
            while (CP!=CC && x>=Xg){
                x=x-1;
                //CP = couleur de (x,y-1)
                CP = getPixelColor(x,y+1);
            }
        }
         */
    }
}

std::array<int,3> Clipping::Filler::getPixelColor(int x,int y){

    unsigned char pixel[4];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    std::cout << "x: " << x << "y: " << y;
    std::cout << " R: " << (int)pixel[0];
    std::cout << " G: " << (int)pixel[1];
    std::cout << " B: " << (int)pixel[2] << std::endl;
    //std::cout << std::endl;
    return {(int)pixel[0],(int)pixel[1],(int)pixel[2]};
}

void Clipping::Filler::drawLine(int x1,int y1,int x2 ,std::array<int,3> C){
    glBegin(GL_POINTS);
    glColor3f(C[0],C[1],C[2]);
    for (int i = x1; i < x2; ++i) {
        glVertex2f(i, y1);
    }
    glEnd();
}
