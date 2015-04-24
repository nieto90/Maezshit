#ifndef MENU_HPP
#define MENU_HPP
 
#include <SFML/Graphics.hpp>
 
class Menu {
    public:
	   Menu();
    
	   int run();
    
    private:
	   sf::RenderWindow window;
	   sf::Font font;
	   int selection;
};
 
#endif