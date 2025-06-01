using namespace std;

// In the QuickHull algorithm, collinear points are generally ignored when forming the convex hull.

struct Point {
    int x, y; // Structure to represent a 2D point
};

// Utility function to compute the cross product (area) — used to determine orientation and distance from line
int crossProduct(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

// Recursive function to find points on the hull on one side of line segment ab
void findHull(Point points[], int n, Point a, Point b, Point hull[], int &hullSize) {
    if (n == 0) return; // No points to process

    // Find the point farthest from line segment ab (max distance via cross product)
    int maxDist = -1;
    int farthestIdx = -1;
    for (int i = 0; i < n; i++) {
        int dist = crossProduct(a, b, points[i]);
        if (dist > maxDist) {
            maxDist = dist;
            farthestIdx = i;
        }
    }

    // If no point is found, then all points are collinear or below the line - no further hull points here
    if (farthestIdx == -1) return;

    Point c = points[farthestIdx]; // Farthest point from ab

    // Find a in hull to insert point c after it
    int insertPos = -1;
    for (int i = 0; i < hullSize; i++) {
        if (hull[i].x == a.x && hull[i].y == a.y) {
            insertPos = i;
            break;
        }
    }
    if (insertPos == -1) {
        // a should be in hull, if not found, just append at end
        insertPos = hullSize - 1;
    }

    // Shift hull elements right to insert c at insertPos+1
    // Use memmove for safe memory move
    memmove(&hull[insertPos + 2], &hull[insertPos + 1], sizeof(Point)*(hullSize - insertPos -1));
    hull[insertPos + 1] = c;
    hullSize++;

    // Prepare arrays for points on left side of ac and cb lines respectively
    // Allocate maximum needed size for temporary arrays
    Point *leftSetAC = new Point[n];
    Point *leftSetCB = new Point[n];
    int leftSetACSize = 0, leftSetCBSize = 0;

    for (int i = 0; i < n; i++) {
        if (i == farthestIdx) continue;

        int side1 = crossProduct(a, c, points[i]); // Left side of line ac?
        int side2 = crossProduct(c, b, points[i]); // Left side of line cb?

        // Only consider points strictly on the left to omit collinear points (side == 0)
        if (side1 > 0) {
            leftSetAC[leftSetACSize++] = points[i];
        }
        else if (side2 > 0) {
            leftSetCB[leftSetCBSize++] = points[i];
        }
    }

    // Recursively find hull points on both subsets
    findHull(leftSetAC, leftSetACSize, a, c, hull, hullSize);
    findHull(leftSetCB, leftSetCBSize, c, b, hull, hullSize);

    delete[] leftSetAC;
    delete[] leftSetCB;
}

// Main QuickHull function to compute convex hull points for a given set of points
void quickHull(Point points[], int n, Point hull[], int &hullSize) {
    hullSize = 0;
    if (n < 3) {
        // If less than 3 points, hull is just the points themselves
        for (int i = 0; i < n; i++) {
            hull[hullSize++] = points[i];
        }
        return;
    }

    // Find points with minimum and maximum x coordinates - guaranteed hull vertices
    int minX = 0, maxX = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[minX].x)
            minX = i;
        if (points[i].x > points[maxX].x)
            maxX = i;
    }

    // Initialize hull with these two extreme points
    hull[0] = points[minX];
    hull[1] = points[maxX];
    hullSize = 2;

    // Prepare arrays for points on left and right side of baseline minX-maxX
    Point *leftSet = new Point[n];
    Point *rightSet = new Point[n];
    int leftSize = 0, rightSize = 0;

    for (int i = 0; i < n; i++) {
        if (i == minX || i == maxX) continue;
        int side = crossProduct(hull[0], hull[1], points[i]);
        if (side > 0) leftSet[leftSize++] = points[i];    // Left side of base line
        else if (side < 0) rightSet[rightSize++] = points[i]; // Right side of base line
        // Points with side == 0 are collinear and ignored as per QuickHull convention
    }

    // Recursively find hull points on left and right subsets
    findHull(leftSet, leftSize, hull[0], hull[1], hull, hullSize);
    findHull(rightSet, rightSize, hull[1], hull[0], hull, hullSize);

    delete[] leftSet;
    delete[] rightSet;
}

// Function to export input points to a CSV file
void exportInputToCSV(const string &filename, int length, Point p[]) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "X,Y\n";
        for (int i = 0; i < length; i++) {
            file << p[i].x << "," << p[i].y << "\n";
        }
        file.close();
    }
    else {
        cerr << "Unable to open file for writing: " << filename << endl;
    }
}

// Function to export convex hull points to CSV file
void exportOutputToCSV(const string &filename, int n, Point convexHull[]) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "X,Y\n";
        for (int i = 0; i < n; i++) {
            file << convexHull[i].x << "," << convexHull[i].y << "\n";
        }
        file.close();
    }
    else {
        cerr << "Unable to open file for writing: " << filename << endl;
    }
}