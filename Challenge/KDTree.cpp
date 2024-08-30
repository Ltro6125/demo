#include "KDTree.h"

Node* createNewNode(string city, double lat, double lng) {
    Node* temp = new Node;

    temp->city.name = city;
    temp->city.point.x = lat;
    temp->city.point.y = lng;

    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

Node* insertRec(Node* root, string city, double lat, double lng, unsigned depth) {
    if (root == NULL) {
        return createNewNode(city, lat, lng);
    }

    unsigned cd = depth % 2; // Since we're dealing with 2D (latitude and longitude)

    if (cd == 0) { // Compare x (latitude)
        if (lat < root->city.point.x) {
            root->left = insertRec(root->left, city, lat, lng, depth + 1);
        }
        else {
            root->right = insertRec(root->right, city, lat, lng, depth + 1);
        }
    }
    else { // Compare y (longitude)
        if (lng < root->city.point.y) {
            root->left = insertRec(root->left, city, lat, lng, depth + 1);
        }
        else {
            root->right = insertRec(root->right, city, lat, lng, depth + 1);
        }
    }

    return root;
}

Node* insert(Node* root, string city, double lat, double lng) {
    return insertRec(root, city, lat, lng, 0);
}

bool searchRec(Node* root, double lat, double lng, unsigned depth) {
    if (root == NULL)
        return false;
    if (root->city.point.x == lat && root->city.point.y == lng)
        return true;

    unsigned cd = depth % 2;

    if (cd == 0) {
        if (lat < root->city.point.x) {
            return searchRec(root->left, lat, lng, depth + 1);
        }
        else {
            return searchRec(root->right, lat, lng, depth + 1);
        }
    }
    else {
        if (lng < root->city.point.y) {
            return searchRec(root->left, lat, lng, depth + 1);
        }
        else {
            return searchRec(root->right, lat, lng, depth + 1);
        }
    }
}

bool search(Node* root, double lat, double lng) {
    return searchRec(root, lat, lng, 0);
}

void readFileToKDTree(string fileName, Node*& root) {
    ifstream ifs(fileName);

    if (!ifs) {
        cout << "Khong doc duoc file " << fileName;
        return;
    }

    string ignore_line;
    getline(ifs, ignore_line, '\n');

    string line;
    string city, lat, lng;


    while (getline(ifs, line, '\n')) {
        stringstream ss(line);

        getline(ss, city, ',');
        getline(ss, lat, ',');
        getline(ss, lng, ',');

        root = insert(root, city, stof(lat), stof(lng));

    }

    ifs.close();
}

void printTree(Node* root, int depth ) {
    if (root == NULL) {
        return;
    }

    cout << "City: " << root->city.name << ", Latitude: " << root->city.point.x << ", Longitude: " << root->city.point.y << endl;

    printTree(root->left, depth + 1);
    printTree(root->right, depth + 1);
}


double haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    lat1 = lat1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371; // Earth radius in kilometers
    double c = 2 * asin(sqrt(a));
    return rad * c;
}


bool isPointInRectangle(Point point, Point bottomLeft, Point topRight) {
    return (point.x >= bottomLeft.x && point.x <= topRight.x && point.y >= bottomLeft.y && point.y <= topRight.y);
}

void rangeSearchRec(Node* root, Point bottomLeft, Point topRight, vector<City>& result, unsigned depth) {
    if (root == NULL)
        return;

    if (isPointInRectangle(root->city.point, bottomLeft, topRight)) {
        result.push_back(root->city);
    }

    unsigned cd = depth % 2;

    if (cd == 0) { // Compare latitude (x)
        if (root->city.point.x >= bottomLeft.x) {
            rangeSearchRec(root->left, bottomLeft, topRight, result, depth + 1);
        }
        if (root->city.point.x <= topRight.x) {
            rangeSearchRec(root->right, bottomLeft, topRight, result, depth + 1);
        }
    }
    else { // Compare longitude (y)
        if (root->city.point.y >= bottomLeft.y) {
            rangeSearchRec(root->left, bottomLeft, topRight, result, depth + 1);
        }
        if (root->city.point.y <= topRight.y) {
            rangeSearchRec(root->right, bottomLeft, topRight, result, depth + 1);
        }
    }
}


vector<City> rangeSearch(Node* root, Point bottomLeft, Point topRight) {
    vector<City> result;

    rangeSearchRec(root, bottomLeft, topRight, result, 0);

    return result;
}

double calculateTotalDistance(Node* root, vector<Point>& points) {
    double totalDistance = 0.0;

    for (int i = 0; i < points.size(); i++) {
        totalDistance += haversine(root->city.point.x, root->city.point.y, points[i].x, points[i].y);
    }
    return totalDistance;
}

void findBestCityRec(Node* root, vector<Point>& points, City& nearestCity, double& minTotalDistance, unsigned depth) {
    if (root == NULL)
        return;

    double totalDistance = calculateTotalDistance(root, points);
    if (totalDistance < minTotalDistance) {
        minTotalDistance = totalDistance;
        nearestCity = root->city;
    }

    unsigned cd = depth % 2;

    if (cd == 0) {

        if (root->city.point.x - minTotalDistance < root->city.point.x) {
            findBestCityRec(root->left, points, nearestCity, minTotalDistance, depth + 1);
        }

        if (root->city.point.x + minTotalDistance > root->city.point.x) {
            findBestCityRec(root->right, points, nearestCity, minTotalDistance, depth + 1);
        }
    }
    else {

        if (root->city.point.y - minTotalDistance < root->city.point.y) {
            findBestCityRec(root->left, points, nearestCity, minTotalDistance, depth + 1);
        }

        if (root->city.point.y + minTotalDistance > root->city.point.y) {
            findBestCityRec(root->right, points, nearestCity, minTotalDistance, depth + 1);
        }
    }
}

City nearestNeighborSearch(Node* root, vector<Point> coordinates) {
    if (root == NULL) {
        cout << "The KD-Tree is empty" << endl;
        return City{ "", {0, 0} };
    }

    City nearestCity;

    double minTotalDistance = numeric_limits<double>::max();

    findBestCityRec(root, coordinates, nearestCity, minTotalDistance, 0);

    return nearestCity;
}

void deleteTree(Node* root) {
    if (root == NULL) {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
    root = NULL;
}