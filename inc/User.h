#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include "Group.h"

class Group;

class User
{

private:
    std::string _name;
    unsigned _id;
    std::unordered_map<unsigned, int> _balance;
    std::vector<unsigned> _group_ids;

    // static class member: shared across all class objects
    // inline: so we can initialize it here.
    static inline unsigned counter = 0;

public:
    User(std::string name = "");
    std::string name() const;
    unsigned id() const;
    std::vector<unsigned> group_ids() const;
    void join_group(unsigned group_id);
    void leave_group(unsigned group_id);
    void update_balance(unsigned group_id, unsigned balance);
    std::unordered_map<unsigned, int> balance();
    void show_balance(unsigned group_id);
    void print_user_groups(const std::unordered_map<unsigned, Group> &);
    void print_unjoined_groups(const std::unordered_map<unsigned, Group> &);
};

#endif