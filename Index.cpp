#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

//input generator
void random_list(int length, int X[], int Y[], int seed = 0, int start = 0, int end = INT_MAX) {
    srand(seed); 
    for (int i = 0; i < length; ++i) {
        X[i] = start + rand() % (end - start + 1);
        Y[i] = start + rand() % (end - start + 1);
    }
}


set<pair<int, int>> convexHull;
	
//Brute Force
void BruteForce(int length,int X[], int Y[]){
		for(int i=0;i<length;i++){
		for(int j=0;j<length;j++){
			if(X[i]!=X[j] || Y[i]!=Y[j]){
				int a=Y[j]-Y[i];
				int b=X[i]-X[j];
				int c=(X[i]*Y[j])-(X[j]*Y[i]);
			
				int side = 0;
				bool allOneSide = true;
			
				for(int p=0;p<length;p++){
					if((p!=i) && (p!=j)){
						int eq=a*X[p] + b*Y[p]-c;
						if(eq!=0){
							
					if (eq != 0) {
                        if (side == 0)
                       side = (eq > 0) ? 1 : -1;
                       else if ((eq > 0 && side == -1) || (eq < 0 && side == 1)) {
						allOneSide = false;
                            break;
                        }
                    }
						
						}
					}
				}
			
				if (allOneSide) {
                    convexHull.insert({X[i], Y[i]});
                    convexHull.insert({X[j], Y[j]});
                }
			}
		}
	}
}

//export input points to CSV
void exportInputToCSV(const string& filename, int length, int X[], int Y[]) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "X,Y\n"; //CSV header
        for (int i = 0; i < length; i++) {
            file << X[i] << "," << Y[i] << "\n";
        }
        file.close();
    } else {
        cerr<<"Unable to open file for writing: "<<filename<<endl;
    }
}
//export output points to CSV
void exportOutputToCSV(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "X,Y\n"; // CSV header
        for (const auto& p : convexHull) {
            file << p.first << "," << p.second << "\n";
        }
        file.close();
    } else {
        cerr << "Unable to open file for writing: " << filename << endl;

}
}
int main(){
	
	const int length = 10;
    int X[length];
    int Y[length];
    int seed = time(0);
    int start = 0;
    int end = 10;
    random_list(length, X, Y, seed, start, end);

	cout<<"Generated Input\n";
	for(int i=0;i<length;i++){
	cout << "(" << X[i] << ", " << Y[i] << ")" << endl;
	}
auto strt = high_resolution_clock::now();
	BruteForce(length,X,Y);
auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop - strt);
	
cout << "Points in the convex hull:\n";
	for (auto p : convexHull) {
		cout << "(" << p.first << ", " << p.second << ")\n";
	}
	
cout<<"\nTotal Time Taken By Algorithm :" <<duration.count() << " microseconds\n";	

	exportInputToCSV("input_points.csv", length, X, Y);
    exportOutputToCSV("convex_hull_points.csv");
    
	return 0;
}