#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Utils/Constants.hpp"
#include "Map.hpp"
#include <iostream>
using namespace std;

Map::Map(){}

Map::Map(unsigned int gridsize){
    rsize = gridsize;
    size = rsize*2 + 1;
    minisquaresize = HEIGHT/(2*size);
}


void Map::initmap(){
    bool repeat = true;

	//cout << "Generating maze" << endl;
	//cout << "Searching paths... " << endl;
	while(repeat){
		repeat = false;
		setup();
		minpath();
		t = std::time(NULL);
		if(cango(1,1) && cango(1,size-2) && cango(size-2,1) && cango(size-2,size-2)){
			if(!repeat && !genpath(-1,1,1,0,0)) repeat = true;
			if(!repeat && !genpath(-1,1,size-2,0,0)) repeat = true;
			if(!repeat && !genpath(-1,size-2,1,0,0)) repeat = true;
			if(!repeat && !genpath(-1,size-2,size-2,0,0)) repeat = true;
		} else repeat = true;
	}

	vector< vector<char> > mazecopy = maze;
	//cout << "Fulfilling maze..."<< endl;

	refill();

	while(maze != mazecopy) {
		mazecopy = maze;
		refill();
	}

	setextras();

	for(int i = 0; i < size; ++i){
		maze[0][i] = '#';
		maze[size-1][i] = '#';
		maze[i][0] = '#';
		maze[i][size-1] = '#';
	}
}

void Map::print(sf::RenderWindow* window){
	int posx = 0;
	int posy = 0;
	float sizex = minisquaresize;
	float sizey = minisquaresize;
	sf::Shader shader;
	if (!shader.loadFromFile("src/Shaders/minimap.frag", sf::Shader::Fragment))
	{
	    cout << "ERROR" << endl;
	}
	for(int i = 0; i < maze.size(); ++i){
    	for(int j = 0; j < maze[i].size(); ++j){
    		sf::RectangleShape a;
    		/*if(maze[i][j] == '#'){
	    		if(i%2==0) {
	    			sizex = miniwallsize;
	    		}
	    		else {
	    			sizey = miniwallsize;
	    		}
	    	}*/
	    	a = sf::RectangleShape(sf::Vector2f(sizex,sizey));
			sf::Color c;
			if(maze[i][j] == '#') c = sf::Color::Black;
			else if(maze[i][j] == ' ') c = sf::Color::White;
			else if(maze[i][j] == 'D') c = sf::Color::Green;
			else if(maze[i][j] >= 'a' && maze[i][j] <= 'c') c = sf::Color::Magenta;
			else if(maze[i][j] >= '1' && maze[i][j] <= '4') c = sf::Color::Red;
			else c = sf::Color::Yellow;
			a.setFillColor(c);
			a.setPosition(posx,posy);
			window->draw(a,&shader);
			posx += sizex;
		}
		posx = 0;
		posy += sizey;
	}
}


void Map::setup(){
	maze = vector< vector<char> >(size, vector<char>(size,'#'));
	mazei = vector< vector<int> >(size, vector<int>(size,0));
	for(int i = 0; i < size; ++i){
		maze[0][i] = '@';
		maze[size-1][i] = '@';
		maze[i][0] = '@';
		maze[i][size-1] = '@';
	}
	maze[1][1] = '1';
	maze[1][size-2] = '2';
	maze[size-2][1] = '3';
	maze[size-2][size-2] = '4';
}

void Map::setextras(){
	int x = 0;
	int y = 0;
	int cont = 0;
	while(cont < 4){
		while(maze[x][y] != ' '){
			x = 2*(rand()%rsize) + 1;
			y = 2*(rand()%rsize) + 1;
		}
		maze[x][y] = 'p'+cont;
		++cont;
	}
	cont = 0;
	while(cont < 4){
		while(maze[x][y] != ' '){
			x = 2*(rand()%rsize) + 1;
			y = 2*(rand()%rsize) + 1;
		}
		maze[x][y] = 'P'+cont;
		++cont;
	}
	cont = 0;
	while(cont < 3){
		while(maze[x][y] != ' '){
			x = 2*(rand()%rsize) + 1;
			y = 2*(rand()%rsize) + 1;
		}
		maze[x][y] = 'a'+cont;
		++cont;
	}
	

}

void Map::minpath(){
	int x = 0;
	int y = 0;
	int minx;
	int miny;
	while(maze[x][y] != '#' && !(maze[x][y] >= '1' && maze[x][y] <= '4')){
		x = rand()%rsize;
		y = rand()%rsize;
		minx = (rsize-x > x? rsize-x:x);
		miny = (rsize-y > y? rsize-y:y);
		dx = 1 + 2*x;
		dy = 1 + 2*y;
	}
	maze[dy][dx] = 'D';
	minp = minx+miny;

}

bool Map::genpath(int pd, int x, int y, int d, int cuts){
	if(std::time(NULL) - t > rsize/2) return false;
	if(x < 0 || y < 0 || x > size-1 || y > size-1) return false;
	if(d + (abs(dx-x) + abs(dy-y))/2 > minp) return false;

	char curc = maze[x][y];
	int curd = mazei[x][y];


	if(pd != -1 && curc >= '1' && curc <= '4') return false;
	if(curc == 'D' && d != minp) return false;
	if(curc == ' ' && curd != d) return false;

	if(curc == '#') {
		mazei[x][y] = d;
		maze[x][y] = ' ';
	}

	int fd;

	if(pd == 0){							//UP
		maze[x+1][y] = ' ';
		fd = 1;
	} else if(pd == 1){						//DOWN
		maze[x-1][y] = ' ';
		fd = 0;
	} else if(pd == 2){						//LEFT
		maze[x][y+1] = ' ';
		fd = 3;
	} else if(pd == 3){						//RIGHT
		maze[x][y-1] = ' ';
		fd = 2;
	}

	if(d == minp && curc == 'D') return true;

	int dir;

	if(d + (abs(dx-x) + abs(dy-y))/2 == minp && ++cuts == rsize){
		if((dx-x)/2 > 0 && fd != 1){
			dir = 1;
			if(genpath(dir,x+2,y,d+1,cuts)) return true;
		} else if((dx-x)/2 < 0 && fd != 0){
			dir = 0;
			if(genpath(dir,x-2,y,d+1,cuts)) return true;
		} else if((dy-y)/2 > 0 && fd != 3){
			dir = 3;
			if(genpath(dir,x,y+2,d+1,cuts)) return true;
		} else if((dy-y)/2 < 0 && fd != 2){
			dir = 2;
			if(genpath(dir,x,y-2,d+1,cuts)) return true;
		}
	} else {

		dir = rand()%4;

		for(int i = 0; i < 4; ++i){
			dir = (dir+1)%4;
			if(dir != fd){
				if(dir == 0){								//UP
					if(genpath(dir,x-2,y,d+1,cuts)) return true;
				} else if(dir == 1){						//DOWN
					if(genpath(dir,x+2,y,d+1,cuts)) return true;
				} else if(dir == 2){						//LEFT
					if(genpath(dir,x,y-2,d+1,cuts)) return true;
				} else if(dir == 3){						//RIGHT
					if(genpath(dir,x,y+2,d+1,cuts)) return true;
				}
			}
		}
	}
	maze[x][y] = curc;
	mazei[x][y] = curd;

	if(pd == 0){							//UP
		maze[x+1][y] = '#';
	} else if(pd == 1){						//DOWN
		maze[x-1][y] = '#';
	} else if(pd == 2){						//LEFT
		maze[x][y+1] = '#';
	} else if(pd == 3){						//RIGHT
		maze[x][y-1] = '#';
	}
	return false;
}

bool Map::genshit(int pd, int x, int y, int d){
	if(x < 0 || y < 0 || x > size-1 || y > size-1) return true;

	char curc = maze[x][y];

	if(curc >= '1' && curc <= '4') return true;
	if(curc == 'D') return true;
	if(pd != -1 && curc == ' ') return true;

	if(curc == '#') {
		maze[x][y] = ' ';
	}

	int fd;

	if(pd == 0){							//UP
		maze[x+1][y] = ' ';
		fd = 1;
	} else if(pd == 1){						//DOWN
		maze[x-1][y] = ' ';
		fd = 0;
	} else if(pd == 2){						//LEFT
		maze[x][y+1] = ' ';
		fd = 3;
	} else if(pd == 3){						//RIGHT
		maze[x][y-1] = ' ';
		fd = 2;
	}

	int dir = rand()%4;

	for(int i = 0; i < 4; ++i){
		dir = (dir+1)%4;
		if(dir != fd){
			if(dir == 0){								//UP
				if(genshit(dir,x-2,y,d+1)) return true;
			} else if(dir == 1){						//DOWN
				if(genshit(dir,x+2,y,d+1)) return true;
			} else if(dir == 2){						//LEFT
				if(genshit(dir,x,y-2,d+1)) return true;
			} else if(dir == 3){						//RIGHT
				if(genshit(dir,x,y+2,d+1)) return true;
			}
		}
	}
	maze[x][y] = curc;

	if(pd == 0){							//UP
		maze[x+1][y] = '#';
	} else if(pd == 1){						//DOWN
		maze[x-1][y] = '#';
	} else if(pd == 2){						//LEFT
		maze[x][y+1] = '#';
	} else if(pd == 3){						//RIGHT
		maze[x][y-1] = '#';
	}
	return false;

}
bool Map::cango(int x, int y){
	int remainpath = minp - (abs(dx-x) + abs(dy-y))/2;
	return (remainpath%2 == 0);
}
void Map::refill(){
	for(int i = 1; i < size-1; i+=2)
		for(int j = 1; j < size-1; j+=2)
			if(maze[i][j] == ' '){
				genshit(-1,i,j,mazei[i][j]);
			}
}