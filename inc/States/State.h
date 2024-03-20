#ifndef STATE_H
#define STATE_H

#include <unordered_map>
#include "../User.h"
#include "../Group.h"

enum class StateName
{
    INIT,

    START,
    CHOOSE_USER,
    CREATE_USER,

    USER_HOME,
    CREATE_GROUP,
    CHOOSE_GROUP,
    JOIN_GROUP,

    GROUP_HOME,
    GROUP_MEMBER,
    ADD_EXPENSE,
    CHECK_EXPENSE,
    SETTLEMENT,
    LEAVE_GROUP,
    EDIT_EXPENSE,
    BALANCE,

    AUTO_GEN, // Autogenerated mode

    EXIT
};

class State
{

protected:
    StateName _name;

    virtual void _entry() = 0;

    virtual void _during() = 0;

    // virtual void exit();

    static inline unsigned _user_id;
    static inline unsigned _group_id;

    static inline std::unordered_map<unsigned, User> _user_umap;
    static inline std::unordered_map<unsigned, Group> _group_umap;

public:
    State(StateName name);

    void enter();

    StateName run();

    virtual StateName transitions();

    StateName name();
};

#endif