#include <iostream>
using namespace std;

int main(){
	char c = 'a';

	for(int i = 0; i < 25*25; ++i){
		cout << c << " = " << int(c) << endl;
		c = c + 1;
	}
}