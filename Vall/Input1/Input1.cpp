#include<iostream>
using namespace std;

int main() {
	int a;

	cout << "なにか入れてね > ";
	cin >> a;

	cout << "その数を3で割った余りは"
		<< a % 3 << "です。" << endl;

	return 0;
}