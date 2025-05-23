using namespace std;

struct Point {
    int x, y;
};

void findHull(Point points[], int n, Point a, Point b, Point hull[], int& hullSize) {
    if (n == 0) return;

    int maxDist = -1, farthestIdx = -1;
    for (int i = 0; i < n; i++) {
        int dist = (b.x - a.x) * (points[i].y - a.y) - (b.y - a.y) * (points[i].x - a.x);
        if (dist > maxDist) {
            maxDist = dist;
            farthestIdx = i;
        }
    }

    if (farthestIdx == -1) return;

    Point c = points[farthestIdx];
    
    int insertPos = 0;
    for (int i = 0; i < hullSize; i++) {
        if (hull[i].x == a.x && hull[i].y == a.y) {
            insertPos = i;
            break;
        }
    }
    
    for (int i = hullSize; i > insertPos + 1; i--){
        hull[i] = hull[i-1];
    }
    hull[insertPos+1] = c;
    hullSize++;

    Point A[n], B[n];
    int A_size = 0, B_size = 0;
    
    for (int i = 0; i < n; i++) {
        if (i == farthestIdx) continue;
        
        int side1 = (c.x - a.x) * (points[i].y - a.y) - (c.y - a.y) * (points[i].x - a.x);
        int side2 = (b.x - c.x) * (points[i].y - c.y) - (b.y - c.y) * (points[i].x - c.x);
        
        if (side1 > 0)
            A[A_size++] = points[i];
        else if (side2 > 0)
            B[B_size++] = points[i];
    }

    findHull(A, A_size, a, c, hull, hullSize);
    findHull(B, B_size, c, b, hull, hullSize);
}

void quickHull(Point points[], int n, Point hull[], int& hullSize) {
    if (n < 3) {
        for (int i = 0; i < n; i++) hull[i] = points[i];
        hullSize = n;
        return;
    }

    int minX = 0, maxX = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[minX].x) {
            minX = i;
        }
        if (points[i].x > points[maxX].x) { 
            maxX = i;
        }
    }

    hull[0] = points[minX];
    hull[1] = points[maxX];
    hullSize = 2;

    Point a[n], b[n];
    int a_size = 0, b_size = 0;
    
    for (int i = 0; i < n; i++) {
        if (i == minX || i == maxX) continue;
        
        int side = (hull[1].x - hull[0].x) * (points[i].y - hull[0].y) - (hull[1].y - hull[0].y) * (points[i].x - hull[0].x);
        
        if (side > 0)
            a[a_size++] = points[i];
        else if (side < 0)
            b[b_size++] = points[i];
    }

    findHull(a, a_size, hull[0], hull[1], hull, hullSize);
    findHull(b, b_size, hull[1], hull[0], hull, hullSize);
}


void exportInputToCSV(const string& filename, int length, Point p[]) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "X,Y\n"; 
        for (int i = 0; i < length; i++) {
            file << p[i].x << "," << p[i].y << "\n";
        }
        file.close();
    } else {
        cerr<<"Unable to open file for writing: "<<filename<<endl;
    }
}

void exportOutputToCSV(const string& filename, int n, Point convexHull[]) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "X,Y\n";
        for (int i = 0; i < n; i++) {
            file << convexHull[i].x << "," << convexHull[i].y << "\n";
        }
        file.close();
    } else {
        cerr << "Unable to open file for writing: " << filename << endl;
    }
}