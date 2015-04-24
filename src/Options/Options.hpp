#ifndef OPTIONS_HPP
#define OPTIONS_HPP
 
#include <SFML/Graphics.hpp>
 
class Options {
    public:
	   Options();
    
	   void run();
	   int getGridSize();
	   int getRounds();
    
    private:
	   sf::RenderWindow window;
	   sf::Font font;
	   int selection;
	   unsigned int gridsize;
	   int rounds;
	   unsigned int mingridsize;
	   unsigned int maxgridsize;
	   int minrounds;
	   int maxrounds;
	   
	   void resetMinMax();
};
 
#endif
