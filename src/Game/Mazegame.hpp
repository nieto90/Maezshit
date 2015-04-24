#ifndef MAZEGAME_HPP
#define MAZEGAME_HPP
 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Map.hpp"
 
class Mazegame {
    public:
	   Mazegame();
    
	   void run();
	   void init(unsigned int gridsize, int rounds);
    
    private:
	   sf::RenderWindow window;
	   sf::Sprite background;
	   sf::Clock clock;
	   sf::Time time;
	   Map map;
	   
	   void print();
};
 
#endif