#include<iostream>
using namespace std;

void f(int x,int y) {
	cout <<  "f(" << x << "," << y << ") = " << 2*x+y << endl;

}

int main(void) {
	f(1, 2);
	f(182, 144);

	return 0;
}