#ifndef MAP_HPP
#define MAP_HPP
 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
 
class Map {
    public:
    	Map();
		Map(unsigned int gridsize);
		void initmap();
		void print(sf::RenderWindow* window);
    
    private:
		sf::Clock clock;
		sf::Time time;
		float squaresize;
		float minisquaresize;
		int size;
		int rsize;
		std::vector< std::vector<char> > maze;
		std::vector< std::vector<int> > mazei;
		int minp;
		int dx, dy;
		int t;

		void refill();
		bool cango(int x, int y);
		bool genshit(int pd, int x, int y, int d);
		void minpath();
		bool genpath(int pd, int x, int y, int d, int cuts);
		void setextras();
void setup();

};
 
#endif