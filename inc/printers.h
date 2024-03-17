#ifndef PRINTER_H
#define PRINTER_H

#include "backend.h"

void print_all_users(const std::unordered_map<unsigned, User> &);
void print_all_groups(const std::unordered_map<unsigned, Group> &);
void print_user_groups(unsigned, const std::unordered_map<unsigned, User> &, const std::unordered_map<unsigned, Group> &);
void print_expenses(unsigned group_id, const std::unordered_map<unsigned, User> &user_umap, const std::unordered_map<unsigned, Group> &group_umap);

#endif