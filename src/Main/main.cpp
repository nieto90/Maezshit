#include "../Game/Mazegame.hpp"
#include "../Options/Options.hpp"
#include "Menu.hpp"

int main(){
    
    Menu menu;
    Mazegame game;
    Options options;
    int op = menu.run();
    
    while(op != 2){
	   switch(op){
		  case 0:
			 game.init(options.getGridSize(),options.getRounds());
			 game.run();
			 break;
		  case 1:
			 options.run();
			 break;
		  default:
			 break;
	   }
	   
	   op = menu.run();
	   
    }
    
    return 0;
}