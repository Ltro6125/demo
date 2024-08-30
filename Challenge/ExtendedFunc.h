#pragma once

#ifndef ExtendedFunc_H
#define ExtendedFunc_H
#endif

#include "KDTree.h"
#include <cstring>

void serializeNode(Node* root, ofstream& ofs);
void serialize(Node* root, string fileName);
Node* deserialize(string fileName);

