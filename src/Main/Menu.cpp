#include <SFML/Graphics.hpp>
#include "../Utils/Constants.hpp"
#include "Menu.hpp"
using namespace std;

Menu::Menu(){
    font.loadFromFile("fonts/MontereyFLF.ttf");
}

int Menu::run(){
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Gaemshit", sf::Style::Fullscreen);
    
    selection = 0;
    
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setCharacterSize(HEIGHT/5);
    titleText.setColor(sf::Color::Red);
    titleText.setString("GaemShit");
    titleText.setPosition(sf::Vector2f((WIDTH-titleText.getLocalBounds().width)/2,HEIGHT/7));
    
    sf::Text playText;
    playText.setFont(font);
    playText.setCharacterSize(HEIGHT/12);
    playText.setColor(sf::Color::White);
    playText.setString("Play");
    playText.setPosition(sf::Vector2f((WIDTH-playText.getLocalBounds().width)/2,HEIGHT/2));
    
    sf::Text optionText;
    optionText.setFont(font);
    optionText.setCharacterSize(HEIGHT/12);
    optionText.setColor(sf::Color::White);
    optionText.setString("Options");
    optionText.setPosition(sf::Vector2f((WIDTH-optionText.getLocalBounds().width)/2,HEIGHT/1.6));
    
    sf::Text exitText;
    exitText.setFont(font);
    exitText.setCharacterSize(HEIGHT/12);
    exitText.setColor(sf::Color::White);
    exitText.setString("Exit");
    exitText.setPosition(sf::Vector2f((WIDTH-exitText.getLocalBounds().width)/2,HEIGHT/1.3));
    
    sf::Text playTextSelection;
    playTextSelection.setFont(font);
    playTextSelection.setCharacterSize(HEIGHT/10);
    playTextSelection.setColor(sf::Color::Green);
    playTextSelection.setString("Play");
    playTextSelection.setPosition(sf::Vector2f((WIDTH-playTextSelection.getLocalBounds().width)/2,HEIGHT/2.09));
    
    sf::Text optionTextSelection;
    optionTextSelection.setFont(font);
    optionTextSelection.setCharacterSize(HEIGHT/10);
    optionTextSelection.setColor(sf::Color::Green);
    optionTextSelection.setString("Options");
    optionTextSelection.setPosition(sf::Vector2f((WIDTH-optionTextSelection.getLocalBounds().width)/2,HEIGHT/1.65));
    
    sf::Text exitTextSelection;
    exitTextSelection.setFont(font);
    exitTextSelection.setCharacterSize(HEIGHT/10);
    exitTextSelection.setColor(sf::Color::Green);
    exitTextSelection.setString("Exit");
    exitTextSelection.setPosition(sf::Vector2f((WIDTH-exitTextSelection.getLocalBounds().width)/2,HEIGHT/1.33));
    
    while (window.isOpen()){
	   
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
			 selection = ((selection-1)+3)%3;
		  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
			 selection = (selection+1)%3;
		  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return){
			 window.close();
			 return selection;
		  }
		  
        }
        
	   window.clear();
	   window.draw(titleText);
	   if(selection == 0) window.draw(playTextSelection);
	   else if(selection == 1)window.draw(optionTextSelection);
	   else if(selection == 2)window.draw(exitTextSelection);
	   window.draw(playText);
	   window.draw(optionText);
	   window.draw(exitText);
        window.display();
	   
	   
    }
}