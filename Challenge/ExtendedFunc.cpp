#include "KDTree.h"

void serializeNode(Node* root, ofstream& ofs) {
    if (root == NULL) {
        /*char nullMarker = -1;
        ofs.write(&nullMarker, sizeof(nullMarker));*/
        return;
    }

    /* char nonNullMarker = 1;
     ofs.write(&nonNullMarker, sizeof(nonNullMarker));*/


    int nameLength = root->city.name.size();

    ofs.write((char*)(&nameLength), sizeof(nameLength));
    ofs.write(root->city.name.c_str(), nameLength);

    ofs.write((char*)(&root->city.point.x), sizeof(root->city.point.x));
    ofs.write((char*)(&root->city.point.y), sizeof(root->city.point.y));

    serializeNode(root->left, ofs);
    serializeNode(root->right, ofs);
}

void serialize(Node* root, string fileName) {

    ofstream ofs(fileName, ios::binary);

    if (!ofs) {
        cout << "Can not open the file " << fileName << endl;
        return;
    }


    serializeNode(root, ofs);

    ofs.close();

}

Node* deserialize(string fileName) {
    ifstream ifs(fileName, ios::binary);

    if (!ifs) {
        cout << "Can not open the file " << fileName << endl;
        return NULL;
    }

    Node* root = NULL;

    while (!ifs.eof()) {
        City temp;
        int nameLength;

        ifs.read((char*)&nameLength, sizeof(nameLength));
        if (!ifs) break;
        char* cityName = new char[nameLength + 1];
        cityName[nameLength] = '\0';
        ifs.read(cityName, nameLength);

        temp.name = cityName;


        ifs.read((char*)&temp.point.x, sizeof(temp.point.x));
        ifs.read((char*)&temp.point.y, sizeof(temp.point.y));

        root = insert(root, temp.name, temp.point.x, temp.point.y);

        delete[] cityName;
    }

    ifs.close();

    return root;
}

