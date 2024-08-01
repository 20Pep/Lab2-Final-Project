#include "MainMenu.h"

MainMenu::MainMenu(unsigned int width, unsigned int heightt)
{
	if (!font.loadFromFile("Recursos/images/font.ttf")) {
		// Handle error
		std::cerr << "Error loading font\n";
	}

	Title.setFont(font);
	Title.setFillColor(Color::Yellow);
	Title.setString("PAC MAN");
	Title.setCharacterSize(200);
	Title.setPosition(200, 200);

	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(Color::White);
	mainMenu[0].setString("PLAY");
	mainMenu[0].setCharacterSize(70);
	mainMenu[0].setPosition(275, 200);

	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color::White);
	mainMenu[1].setString("OPTIONS");
	mainMenu[1].setCharacterSize(70);
	mainMenu[1].setPosition(275, 300);

	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(Color::White);
	mainMenu[2].setString("EXIT");
	mainMenu[2].setCharacterSize(70);
	mainMenu[2].setPosition(275, 400);

	MainMenuSelected = -1;
}

void MainMenu::draw(RenderWindow& window) {
	for (int i = 0; i < Max_main_menu; ++i) {
		window.draw(mainMenu[i]);
	}
}

void MainMenu::MoveUp() {
	if (MainMenuSelected - 1 >= 0) {
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected--;
		if (MainMenuSelected == -1) {
			MainMenuSelected = 2;
		}
		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
}

void MainMenu::MoveDown() {
	if (MainMenuSelected + 1 <= Max_main_menu) {
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected++;
		if (MainMenuSelected == 3) {
			MainMenuSelected = 0;
		}
		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
}
