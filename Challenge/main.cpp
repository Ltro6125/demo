#include "KDTree.h"
#include "ExtendedFunc.h"

int main() {
    Node* root = NULL;

    string fileName = "worldcities-20210313-population-50000+.csv";
    readFileToKDTree(fileName, root);

    //printTree(root);
    //deleteTree(root);

    double lat = 35.6897;
    double lng = 139.6922;

    /*if (search(root, lat, lng)) {
        cout << "Found city with coordinates: (" << lat << ", " << lng << ")\n";
    }
    else {
        cout << "City with coordinates: (" << lat << ", " << lng << ") not found\n";
    }*/

    /*cout << "KD Tree structure:" << endl;
    printTree(root);*/

    /*Point bottomLeft = { 10.0, 10.0 };
    Point topRight = { 40.0, 150.0 };
    
    vector<City> citiesInRange = rangeSearch(root, bottomLeft, topRight);

  
    cout << "Cities in the specified range:" << endl;
    for (const City& city : citiesInRange) {
        cout << city.name << " " << city.point.x << " " << city.point.y << endl;
    }*/

    /*vector<Point> coordinates = { {37, 39}, {38, 40} };
    City nearestCity = nearestNeighborSearch(root, coordinates);
    cout << nearestCity.name << " " << nearestCity.point.x << " " << nearestCity.point.y << endl;*/

    //cout << "First" << endl;
    ////printTree(root);

    serialize(root, "input.bin");
    /*printTree(root);*/
    deleteTree(root);

    root = NULL;
    root = deserialize("input.bin");
    cout << "Second" << endl;
    printTree(root);

    deleteTree(root);
    //printTree(root);

	return 0;

}