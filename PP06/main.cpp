#include <vector>
#include <iostream>

using namespace std;

template<typename T>
T sum(T a, T b)
{
	return a + b;
}


int main()
{
	vector<int> a;

	cout << sum<double>(3.9, 4.9) << endl;

	cout << a.size() <<endl;

	a.push_back(1);
	a.push_back(2);
	a.push_back(4);

	cout << a.size() << endl;
	cout << "°ª :"<< a[0] << endl;

	return 0;
}