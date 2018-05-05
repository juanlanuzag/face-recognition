#include <bits/stdc++.h>

using namespace std;

int main(){
	set<vector<double> > s;

	vector<double> v1(3, 0);
	vector<double> v2(3, 0);
	vector<double> v3(3, 0);
	
	v1[1] = 1; v1[2] = 2;
	v2[1] = 1; v2[2] = 3;
	v3[0] = -1; v3[1] = 4; v3[2] = 5;
	
	s.insert(v1); s.insert(v2); s.insert(v3);

	for(auto v : s){
		for(auto i : v){
			cout << i << " ";
		}
		cout << endl;
	}
	return 0;
}
