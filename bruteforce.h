using namespace std;

//In a brute-force approach for convex hull problems, every possible subset of points is checked to determine whether it forms the boundary of the convex hull.

set<pair<int, int>> convexHull; // Stores the unique points that form the convex hull

// Brute-force function to find convex hull points
void BruteForce(int length, int X[], int Y[]) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            // Ensure we're checking two distinct points
            if (X[i] != X[j] || Y[i] != Y[j]) {
                // Equation of the line: ax + by = c
                int a = Y[j] - Y[i];       // Difference in Y coordinates
                int b = X[i] - X[j];       // Negative difference in X coordinates
                int c = (X[i] * Y[j]) - (X[j] * Y[i]); // Determinant (constant term in line equation)

                int side = 0;             // Will store direction of the first point w.r.t. the line
                bool allOneSide = true;  // Flag to check if all other points lie on one side

                // Check position of all other points relative to the line
                for (int p = 0; p < length; p++) {
                    if ((p != i) && (p != j)) { // Skip the points forming the line
                        int eq = a * X[p] + b * Y[p] - c; // Substitute point into line equation

                        if (eq != 0) { // Point is not on the line
                            if (side == 0)
                                side = (eq > 0) ? 1 : -1; // First non-zero side is taken as reference
                            else if ((eq > 0 && side == -1) || (eq < 0 && side == 1)) {
                                // Found a point on the opposite side
                                allOneSide = false;
                                break; // No need to check further
                            }
                        }
                    }
                }

                // If all points lie on one side of the line, then the line segment (i,j) is on the convex hull
                if (allOneSide) {
                    convexHull.insert({X[i], Y[i]});
                    convexHull.insert({X[j], Y[j]});
                }
            }
        }
    }
}

// Function to export input points to a CSV file
void exportInputToCSV(const string& filename, int length, int X[], int Y[]) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "X,Y\n"; // CSV header
        for (int i = 0; i < length; i++) {
            file << X[i] << "," << Y[i] << "\n"; // Write each point
        }
        file.close(); // Close the file after writing
    } else {
        cerr << "Unable to open file for writing: " << filename << endl;
    }
}

// Function to export convex hull points to a CSV file
void exportOutputToCSV(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "X,Y\n"; // CSV header
        for (const auto& p : convexHull) {
            file << p.first << "," << p.second << "\n"; // Write each convex hull point
        }
        file.close(); // Close the file
    } else {
        cerr << "Unable to open file for writing: " << filename << endl;
    }
}