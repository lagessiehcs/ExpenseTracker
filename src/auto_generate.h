#ifndef AUTOGENERATED_H
#define AUTOGENERATED_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "User.h"
#include "backend.h"

void import_data(std::ifstream&, std::vector<User>&, std::vector<Group>&);
void auto_run(std::vector<User>& user_list, std::vector<Group>& group_list);

#endif