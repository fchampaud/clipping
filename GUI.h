//
// Created by florian on 29/01/19.
//

#ifndef CLIPPING_GUI_H
#define CLIPPING_GUI_H


namespace Clipping {
    class GUI {
    public:
        static void registerGUI();

    private:
        static void handleMainMenu(int entry);
        static void handleColorMenu(int entry);
        static void handleWindowColorMenu(int entry);
        static void handlePolygonColorMenu(int entry);
        static void handleClippedColorMenu(int entry);
        static void handleFillColorMenu(int entry);
    };
}


#endif //CLIPPING_GUI_H
