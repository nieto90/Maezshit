#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Utils/Constants.hpp"
#include "Mazegame.hpp"
#include "Map.hpp"
#include <iostream>
using namespace std;

Mazegame::Mazegame(){
    
}

void Mazegame::init(unsigned int gridsize, int rounds){
    map = Map(gridsize);
}



void Mazegame::print(){
    sf::RectangleShape a(sf::Vector2f(500.0,500.0));
    a.setPosition(0,0);
    a.setFillColor(sf::Color::Red);
    window.draw(a);
}



void Mazegame::run(){
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Maezshit", sf::Style::Fullscreen);
    map.initmap();
    
    while (window.isOpen()){
	   
	   time = clock.restart();
	   
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) )
                window.close();
        }
        
	   window.clear();
	   print();
	   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) map.print(&window);
	   window.display();
	   
	   
    }
}

