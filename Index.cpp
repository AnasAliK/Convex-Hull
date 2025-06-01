#include <bits/stdc++.h>
#include <chrono>
#include "quickhull.h"
#include "bruteforce.h"
using namespace std;
using namespace std::chrono;

//add additional commands "-static-libgcc  -Wl,--stack=20000000" for Lenght equal or above 100000

//input generator
void random_list(Point points[],int length, int X[], int Y[], int seed = 0, int start = 0, int end = INT_MAX) {
    srand(seed); 
    for (int i = 0; i < length; ++i) {
        X[i] = start + rand() % (end - start + 1);
        points[i].x = X[i];
        Y[i] = start + rand() % (end - start + 1);
        points[i].y = Y[i];
    }
}



int main(){
	cout<<"Convex Hull\n";
	int n,s,e;
	cout<<"Enter No. of Points : ";
	cin>>n;
	cout<<"Enter Distance Range of the Points : ";
	cin>>s>>e;
	const int length = n;
    int X[length];
    int Y[length];
    int seed = time(0);
    int start = s;
    int end = e;
    Point points[length];
    random_list(points,length, X, Y, seed, start, end);


	cout<<"Generated Input\n";
	for(int i=0;i<length;i++){
	cout << "(" << X[i] << ", " << Y[i] << ")" << endl;
	}
	
  cout<<endl<<"Quick Hull : \n"; 
    Point hull[length];
    int hullSize = 0;
    auto strt = high_resolution_clock::now();
    quickHull(points, length, hull, hullSize);
    auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - strt);
    cout << "Convex Hull Points:\n";
    for (int i = 0; i < hullSize; i++) {
        cout << "(" << hull[i].x << ", " << hull[i].y << ")\n";
    }
    cout<<"\nTotal Time Taken By Quick Hull :" <<duration.count() << " microseconds\n";
  
	exportInputToCSV("inputPoints.csv", length, points);
    exportOutputToCSV("hullPoints.csv", hullSize, hull);
	
	cout<<endl<<"Brute Force : \n";
	
	strt = high_resolution_clock::now();
	BruteForce(length,X,Y);
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - strt);
	
	cout << "Points in the convex hull:\n";
	for (auto p : convexHull) {
		cout << "(" << p.first << ", " << p.second << ")\n";
	}
	
	cout<<"\nTotal Time Taken By Brute Force :" <<duration.count() << " microseconds\n";	

	exportInputToCSV("input_points.csv", length, X, Y);
    exportOutputToCSV("convex_hull_points.csv");
    
	return 0;
}