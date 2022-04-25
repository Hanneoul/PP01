#include <vector> 
#include <iostream>

using namespace std;
template <typename T, typename C>
C sum(T a, T b)
{
	return a + b;
}

template <typename T>
T sum(T a, T b)
{
	return a + b;
}

int main()
{
	vector<int> a;

	cout << sum<double, int>(5.0, 3.434)<<endl;

	a.push_back(1);
	a.push_back(2);
	cout << a.size() << endl;

	a.push_back(4);
	a.push_back(8);
	a.push_back(16);
	cout << a.size() << endl;

	cout << a[4] << endl;

	return 0;
}