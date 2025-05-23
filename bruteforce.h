using namespace std;


set<pair<int, int>> convexHull;


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