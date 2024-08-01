#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "MainMenu.h"
#include <cstdlib>
#include <ctime>
#include <memory>

int main()
{
    int alto = 25 * 32;
    int ancho = 23 * 32;
    std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(sf::VideoMode(ancho, alto), "Space Pac-man"); //estos std solucionan problemas de memoria podes verlo y rehacerlo mas tarde
    std::unique_ptr<MainMenu> mainMenu = std::make_unique<MainMenu>(
        static_cast<float>(window->getSize().x),
        static_cast<float>(window->getSize().y)
    );
    window->setFramerateLimit(60);
    std::unique_ptr<Scene> scene = std::make_unique<Scene>();

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up) {
                    mainMenu->MoveUp();
                }
                if (event.key.code == sf::Keyboard::Down) {
                    mainMenu->MoveDown();
                }
                if (event.key.code == sf::Keyboard::Return) {
                    std::unique_ptr<sf::RenderWindow> Play = std::make_unique<sf::RenderWindow>(sf::VideoMode(ancho, alto), "Pac Man");
                    std::unique_ptr<sf::RenderWindow> Settings = std::make_unique<sf::RenderWindow>(sf::VideoMode(ancho, alto), "Settings");

                    int x = mainMenu->MainMenuPressed();

                    if (x == 0) {
                        while (Play->isOpen() && scene->getIsPlaying()) {
                            sf::Event aevent;
                            Play->setFramerateLimit(60);
                            while (Play->pollEvent(aevent)) {
                                if (aevent.type == sf::Event::Closed) {
                                    Play->close();
                                }
                                if (aevent.type == sf::Event::KeyPressed) {
                                    if (aevent.key.code == sf::Keyboard::Escape) {
                                        Play->close();
                                    }
                                }
                            }
                            scene->update();
                            Settings->close();
                            Play->clear();
                            Play->draw(*scene);
                            Play->display();
                        }
                        scene->ResetAll();
                        scene->setIsPlaying();
                    }
                    if (x == 1) {
                        while (Settings->isOpen()) {
                            sf::Event aevent;
                            while (Settings->pollEvent(aevent)) {
                                if (aevent.type == sf::Event::Closed) {
                                    Settings->close();
                                }
                                if (aevent.type == sf::Event::KeyPressed) {
                                    if (aevent.key.code == sf::Keyboard::Escape) {
                                        Settings->close();
                                    }
                                }
                            }
                            Play->close();
                            Settings->clear();
                            Settings->display();
                        }
                    }
                    if (x == 2)
                        window->close();
                    break;
                }
            }
        }

        window->clear();
        mainMenu->draw(*window);
        window->display();
    }
    return 0;
}