#pragma once

#ifndef KDTree_H
#define KDTree_H
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits> 

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

struct Point {
    double x; // Latitude
    double y; // Longitude
};

struct City {
    string name;
    Point point;
};

struct Node {

    City city; // Point includes lat and lng
    Node* left, * right;

};

Node* createNewNode(string city, double lat, double lng);

Node* insertRec(Node* root, string city, double lat, double lng, unsigned depth);
Node* insert(Node* root, string city, double lat, double lng);

bool searchRec(Node* root, double lat, double lng, unsigned depth);
bool search(Node* root, double lat, double lng);
void readFileToKDTree(string fileName, Node*& root);
void printTree(Node* root, int depth = 0);
double haversine(double lat1, double lon1, double lat2, double lon2);
bool isPointInRectangle(Point point, Point bottomLeft, Point topRight);
vector<City> rangeSearch(Node* root, Point bottomLeft, Point topRight);
double calculateTotalDistance(Node* root, vector<Point>& points);
void findBestCityRec(Node* root, vector<Point>& points, City& nearestCity, double& minTotalDistance, unsigned depth);
City nearestNeighborSearch(Node* root, vector<Point> coordinates);
void deleteTree(Node* root);

