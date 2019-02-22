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
    std::vector<int> temp {x,y};
    Pile.push(temp);
    std::array<int,3> CP  = {0,0,0};
    std::array<int,3> CPd = {0,0,0};
    std::array<int,3> CPg = {0,0,0};
    std::cout<<"Start "<<x<<";"<<y<<std::endl;
    int Xd,Xg;
    while (!Pile.empty()){
        std::vector<int> temp2 (Pile.top());
        Pile.pop();
        // CP = couleur(temp2)
        x= temp2[0];
        y= temp2[1];
        std::cout<<"La pile n'est pas vide. x: " << x <<std::endl;
        Xd = x+1;
        CP = getPixelColor(Xd,y);
        //std::cout<<"CC :"<<CC[0]<<","<<CC[1]<<","<<CC[2]<<std::endl;
        CPd = CP;
        while(CPd != CC && Xd<640){
            Xd = Xd+1;
            //CPd = couleur de (Xd,y)
            CPd = getPixelColor(Xd,y);
            //std::cout<<"Points Cpd: "<<Xd<<";"<<y<<std::endl;
        }
        std::cout<<"Xd: "<<Xd<<";"<<y<<std::endl;
        Xg = x-1;
        CPg= CP;
        while(CPg != CC && Xg>0){
            Xg = Xg-1;
            //CPg = couleur de (Xg,y)
            CPg = getPixelColor(Xg,y);
            //std::cout<<"Points CPg: "<<Xg<<";"<<y<<std::endl;
        }
        std::cout<<"Xg: "<<Xg<<";"<<y<<std::endl;
        //if(Xd>=639){
        //    break;
        //}
        //if(Xg<=0){
        //    break;
        //}
        Xg = Xg+1;
        Xd = Xd-1;
        //On affiche la ligne (Xg,y) (Xd,y)
        drawLine(Xg,y,Xd,CR);
        std::cout<<"Drawn line from "<<Xg<<";"<<y<<" to "<<Xd<<";"<<y<<std::endl;

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
                std::vector<int> temp3 {x,y+1};
                std::cout << "Add " << x << "; " << y-1 << " to stack." << std::endl;
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
                std::vector<int> temp3 {x,y-1};
                std::cout << "Add " << x << "; " << y-1 << " to stack." << std::endl;
                Pile.push(temp3);
            }
            while (CP!=CC && x>=Xg){
                x=x-1;
                //CP = couleur de (x,y-1)
                CP = getPixelColor(x,y-1);
            }
        }

    }
}

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

void Clipping::Filler::drawLine(int x1,int y1,int x2 ,std::array<int,3> C){
    glBegin(GL_POINTS);
    glColor3f(C[0],C[1],C[2]);
    for (int i = x1; i < x2; ++i) {
        glVertex2f(i, y1);
    }
    glEnd();
}
