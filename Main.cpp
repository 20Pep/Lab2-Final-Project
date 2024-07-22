#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "MainMenu.h"
#include <cstdlib>
#include <ctime>


int main()
{ 
    int alto = 25 * 32;
    int ancho = 23 * 32;

    sf::RenderWindow window(sf::VideoMode(ancho, alto), "Space Pac-man");
    MainMenu mainMenu(window.getSize().x, window.getSize().y);
    window.setFramerateLimit(15);


    Scene scene;



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == Event::KeyReleased) {
                
                if (event.key.code == Keyboard::Up) {
                    mainMenu.MoveUp();
                }
                if (event.key.code == Keyboard::Down) {
                    mainMenu.MoveDown();
                }
                if (event.key.code == Keyboard::Return) {
                    sf::RenderWindow Play(VideoMode(ancho,alto), "Pac Man");
                    sf::RenderWindow Settings(VideoMode(ancho, alto), "Settings");
             
                
                    int x = mainMenu.MainMenuPressed();
                   

                    if (x == 0) {
                        while (Play.isOpen() && scene.getIsPlaying()) {
                            Event aevent;
                            while (Play.pollEvent(aevent)) {
                                if (aevent.type == Event::Closed) {
                                    Play.close();
                                }
                                if (aevent.type == Event::KeyPressed) {
                                    if (aevent.key.code == Keyboard::Escape) {
                                        Play.close();
                                    }
                                }
                            }
                            scene.update();
                            Settings.close();
                            Play.clear();
                            Play.draw(scene);
                            Play.display();
                            
                        }
                        scene.ResetAll();
                        scene.setIsPlaying();
                    }
                    if (x == 1) {
                        while (Settings.isOpen()) {
                            sf::Event aevent;
                            while (Settings.pollEvent(aevent)) {
                                if (aevent.type == Event::Closed) {
                                       Settings.close();
                                }
                                if (aevent.type == Event::KeyPressed) {
                                    if (aevent.key.code == Keyboard::Escape) {
                                        Settings.close();
                                    }
                                }
                            }
                            Play.close();
                            Settings.clear();
                            Settings.display();

                        }
                    }
                    if (x == 2) 
                        window.close();
                    break;
                }
            }
            
        }

       

        
        window.clear();
        mainMenu.draw(window);

        window.display();
    }

    return 0;

}
