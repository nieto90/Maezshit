#include <SFML/Graphics.hpp>
#include "../Utils/Constants.hpp"
#include "Options.hpp"
using namespace std;

Options::Options(){
    font.loadFromFile("fonts/MontereyFLF.ttf");
    gridsize = 10;
    rounds = 50;
    mingridsize = 4;
    maxgridsize = 25;
}

void Options::resetMinMax(){
    minrounds = gridsize;
    maxrounds = gridsize*gridsize;
    if(rounds < minrounds) rounds = minrounds;
    if(rounds > maxrounds) rounds = maxrounds;
}

int Options::getGridSize(){
    return gridsize;
}

int Options::getRounds(){
    return rounds;
}

void Options::run(){
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Gaemshit", sf::Style::Fullscreen);
    
    selection = 0;
    
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setCharacterSize(HEIGHT/7);
    titleText.setColor(sf::Color::Blue);
    titleText.setString("Options");
    titleText.setPosition(sf::Vector2f((WIDTH-titleText.getLocalBounds().width)/2,HEIGHT/7));
    
    sf::Text sizeText;
    sizeText.setFont(font);
    sizeText.setCharacterSize(HEIGHT/12);
    sizeText.setColor(sf::Color::White);
    
    sf::Text turnsText;
    turnsText.setFont(font);
    turnsText.setCharacterSize(HEIGHT/12);
    turnsText.setColor(sf::Color::White);
    
    sf::Text backText;
    backText.setFont(font);
    backText.setCharacterSize(HEIGHT/12);
    backText.setColor(sf::Color::White);
    backText.setString("Back");
    backText.setPosition(sf::Vector2f((WIDTH-backText.getLocalBounds().width)/2,HEIGHT/1.3));
    
    sf::Text sizeTextSelection;
    sizeTextSelection.setFont(font);
    sizeTextSelection.setCharacterSize(HEIGHT/10);
    sizeTextSelection.setColor(sf::Color::Green);
    
    sf::Text turnsTextSelection;
    turnsTextSelection.setFont(font);
    turnsTextSelection.setCharacterSize(HEIGHT/10);
    turnsTextSelection.setColor(sf::Color::Green);
    
    sf::Text backTextSelection;
    backTextSelection.setFont(font);
    backTextSelection.setCharacterSize(HEIGHT/10);
    backTextSelection.setColor(sf::Color::Green);
    backTextSelection.setString("Back");
    backTextSelection.setPosition(sf::Vector2f((WIDTH-backTextSelection.getLocalBounds().width)/2,HEIGHT/1.33));
    
    while (window.isOpen()){
	   
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
			 selection = ((selection-1)+3)%3;
		  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
			 selection = (selection+1)%3;
		  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
			 if(selection == 0){
				if(gridsize > mingridsize) {
				    gridsize--;
				    resetMinMax();
				}
			 } else if(selection == 1){
				if(rounds > minrounds) rounds--;
			 }
		  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
			 if(selection == 0){
				if(gridsize < maxgridsize) {
				    gridsize++;
				    resetMinMax();
				}
			 } else if(selection == 1){
				if(rounds < maxrounds) rounds++;
			 }
		  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && selection == 2){
			 window.close();
		  }
		  
        }
        
        sizeText.setString("Size " + std::to_string(gridsize));
	   sizeText.setPosition(sf::Vector2f((WIDTH-sizeText.getLocalBounds().width)/2,HEIGHT/2));
	   
	   turnsText.setString("Turns " + std::to_string(rounds));
	   turnsText.setPosition(sf::Vector2f((WIDTH-turnsText.getLocalBounds().width)/2,HEIGHT/1.6));
	   
	   sizeTextSelection.setString("Size " + std::to_string(gridsize));
	   sizeTextSelection.setPosition(sf::Vector2f((WIDTH-sizeTextSelection.getLocalBounds().width)/2,HEIGHT/2.09));
	   
	   turnsTextSelection.setString("Turns " + std::to_string(rounds));
	   turnsTextSelection.setPosition(sf::Vector2f((WIDTH-turnsTextSelection.getLocalBounds().width)/2,HEIGHT/1.65));
        
	   window.clear();
	   window.draw(titleText);
	   if(selection == 0) window.draw(sizeTextSelection);
	   else if(selection == 1)window.draw(turnsTextSelection);
	   else if(selection == 2)window.draw(backTextSelection);
	   window.draw(sizeText);
	   window.draw(turnsText);
	   window.draw(backText);
        window.display();
	   
	   
    }
}