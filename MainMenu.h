#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"
#define Max_main_menu 3
using namespace sf;
using namespace std;
class MainMenu {
private:
    int MainMenuSelected;
    Font font;
    Text mainMenu[Max_main_menu];
    Text Title;

public:
    // public means that it can be accessed outside the class.
    MainMenu(unsigned int width, unsigned int height);

    void draw(RenderWindow& window);
    void MoveUp();
    void MoveDown();

    int MainMenuPressed() { 
        return MainMenuSelected;
    }

    //~MainMenu();

};