#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>

using namespace std;

vector< vector<char> > maze;
vector< vector<int> > mazei;
int minp;
int dx, dy;
int t;

const int RSIZE = 51;
const int SIZE = RSIZE*2 +1;

void setup(){
	maze = vector< vector<char> >(SIZE, vector<char>(SIZE,'#'));
	mazei = vector< vector<int> >(SIZE, vector<int>(SIZE,0));
	for(int i = 0; i < SIZE; ++i){
		maze[0][i] = '@';
		maze[SIZE-1][i] = '@';
		maze[i][0] = '@';
		maze[i][SIZE-1] = '@';
	}
	maze[1][1] = '1';
	maze[1][SIZE-2] = '2';
	maze[SIZE-2][1] = '3';
	maze[SIZE-2][SIZE-2] = '4';
}

void print(){
	for(int i = 0; i < SIZE; ++i){
		for(int j = 0; j < SIZE; ++j){
			//if(maze[i][j] >= 'a') maze[i][j] = ' ';
			cout << maze[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void clean(){
	for(int i = 1; i < SIZE-1; ++i)
		for(int j = 1; j < SIZE-1; ++j)
			if(maze[i][j] != '#') maze[i][j] = ' ';
	maze[dy][dx] = 'D';
}

void setextras(){
	int x = 0;
	int y = 0;
	int cont = 0;
	while(cont < 4){
		while(maze[x][y] != ' '){
			x = 2*(rand()%RSIZE) + 1;
			y = 2*(rand()%RSIZE) + 1;
		}
		maze[x][y] = 'p'+cont;
		++cont;
	}
	cont = 0;
	while(cont < 4){
		while(maze[x][y] != ' '){
			x = 2*(rand()%RSIZE) + 1;
			y = 2*(rand()%RSIZE) + 1;
		}
		maze[x][y] = 'P'+cont;
		++cont;
	}
	cont = 0;
	while(cont < 3){
		while(maze[x][y] != ' '){
			x = 2*(rand()%RSIZE) + 1;
			y = 2*(rand()%RSIZE) + 1;
		}
		maze[x][y] = 'a'+cont;
		++cont;
	}
	

}

void minpath(){
	int x = 0;
	int y = 0;
	int minx = RSIZE;
	int miny = RSIZE;
	while(maze[x][y] != '#' && !(maze[x][y] >= '1' && maze[x][y] <= '4')){
		x = 2;
		y = 2;
		minx = (RSIZE-x > x? RSIZE-x:x);
		miny = (RSIZE-y > y? RSIZE-y:y);
		x = 2*x+1;
		y = 2*y+1;
		dx = x;
		dy = y;
	}
	maze[dy][dx] = 'D';
	minp = minx+miny+2;
	//minp = RSIZE*2;
}

bool genpath(int pd, int x, int y, int d, int cuts){
	if(time(NULL) - t > 10) return false;
	if(x < 0 || y < 0 || x > SIZE-1 || y > SIZE-1) return false;
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

	/*if(curd == d && ++cuts == 3) {
		
	cout << cuts << endl;
		return true;
	}*/
	if(d == minp && curc == 'D') return true;

	int dir;

	if(d + (abs(dx-x) + abs(dy-y))/2 == minp && ++cuts == RSIZE){
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

/*
bool genshit(int pd, int x, int y){
	if(x < 0 || y < 0 || x > SIZE-1 || y > SIZE-1) return false;
	if(pd != -1 && (maze[x][y] == ' ' || maze[x][y] == 'D')) return false;
	if(maze[x][y] == 'a') return true;
	vector< vector<char> > mazecopy = maze;

	if(maze[x][y] == '#') maze[x][y] = 'a';

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

	for(int i = 0; i < 3; ++i){
		dir = (dir+1)%4;
		if(dir != fd){
			vector< vector<char> > mazecopy2 = maze;
			if(dir == 0){								//UP
				if(genshit(dir,x-2,y)) return true;
			} else if(dir == 1){						//DOWN
				if(genshit(dir,x+2,y)) return true;
			} else if(dir == 2){						//LEFT
				if(genshit(dir,x,y-2)) return true;
			} else if(dir == 3){						//RIGHT
				if(genshit(dir,x,y+2)) return true;
			}
			maze = mazecopy2;
		}
	}

	maze = mazecopy;

	return false;

}*/
bool genshit(int pd, int x, int y, char d){
	if(x < 0 || y < 0 || x > SIZE-1 || y > SIZE-1) return true;

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

void refill(){
	for(int i = 1; i < SIZE-1; i+=2)
		for(int j = 1; j < SIZE-1; j+=2)
			if(maze[i][j] == ' '){
				genshit(-1,i,j,mazei[i][j]);
			}
}

bool cango(int x, int y){
	int remainpath = minp - (abs(dx-x) + abs(dy-y))/2;
	return (remainpath%2 == 0);
}

int main(){
	srand(time(NULL));
	bool repeat = true;

	cout << "Generating maze" << endl;
	int k = 1;
	while(repeat){
		cout << "Searching paths... " << k++ << endl;
		repeat = false;
		setup();
		minpath();
		t = time(NULL);

		if(cango(1,1) && cango(1,SIZE-2) && cango(SIZE-2,1) && cango(SIZE-2,SIZE-2)){
			if(!repeat) cout << "PATH 1"<< endl;
			if(!repeat && !genpath(-1,1,1,0,0)) repeat = true;
			t = time(NULL);
			if(!repeat) cout << "PATH 2"<< endl;
			if(!repeat && !genpath(-1,1,SIZE-2,0,0)) repeat = true;
			t = time(NULL);
			if(!repeat) cout << "PATH 3"<< endl;
			if(!repeat && !genpath(-1,SIZE-2,1,0,0)) repeat = true;
			t = time(NULL);
			if(!repeat) cout << "PATH 4"<< endl;
			if(!repeat && !genpath(-1,SIZE-2,SIZE-2,0,0)) repeat = true;
		} else {
			repeat = true;
		}

		
	}
	print();
	vector< vector<char> > mazecopy = maze;
	k = 1;
	cout << "Fulfilling maze... " << k++ << endl;

	
	refill();

	while(maze != mazecopy){
		cout << "Fulfilling maze... " << k++ << endl;
		mazecopy = maze;
		refill();
	}

	//setextras();

	print();

}
