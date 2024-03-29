
#include "../inc/printers.h"

void print_all_users(const std::unordered_map<unsigned, User> &user_umap)
{

    if (user_umap.empty())
    {
        std::cout << "| No users yet! Go back and create a user!         |\n";
    }
    else
    {
        std::cout << "| Users:                                           |\n";
        for (const auto &[id, user] : user_umap)
        {
            std::string string = " (" + std::to_string(id + 1) + ") " + user.name();
            std::string spaces(50 - string.length(), ' ');
            std::cout << "|" << string << spaces << "|\n";
        }
    }
    std::cout << "|                                                  |\n";
    std::cout << "| (0) Back                                         |\n";
    std::cout << "*--------------------------------------------------*\n";
    return;
}

void print_all_groups(const std::unordered_map<unsigned, Group> &group_umap)
{

    if (group_umap.empty())
    {
        std::cout << "| No groups yet! Go back and create a group!       |\n";
    }
    else
    {
        std::cout << "| Groups:                                          |\n";
        for (const auto &[id, group] : group_umap)
        {
            std::string string = " (" + std::to_string(id + 1) + ") " + group.name();
            std::string spaces(50 - string.length(), ' ');
            std::cout << "|" << string << spaces << "|\n";
        }
    }
    std::cout << "|                                                  |\n";
    std::cout << "| (0) Back                                         |\n";
    std::cout << "*--------------------------------------------------*\n";
    return;
}

void print_expenses(unsigned group_id, const std::unordered_map<unsigned, User> &user_umap, const std::unordered_map<unsigned, Group> &group_umap)
{
    const auto &expenses = group_umap.find(group_id)->second.expenses(); // Find() instead of [], because group_umap is const, but operator[] not
    if (expenses.empty())
    {
        std::cout << "| No expenses yet!                                 |\n";
        std::cout << "|                                                  |\n";
    }
    else
    {
        for (const auto &expense : expenses)
        {
            std::string string = " (" + std::to_string(expense.id() + 1) + ") " + user_umap.find(expense.payer_id())->second.name() + " paid " + std::to_string((int)(expense.amount() * 0.01)) + " Euro for: ";
            std::string spaces1(50 - string.length(), ' ');
            std::cout << "|" << string << spaces1 << "|\n";

            string = "     ";
            for (auto id : expense.payee_ids())
            {
                string += user_umap.find(id)->second.name();
                if (id != expense.payee_ids().back())
                {
                    string += ", ";
                }
                else
                {
                    string += ".";
                }
            }
            std::string spaces2(50 - string.length(), ' ');
            std::cout << "|" << string << spaces2 << "|\n";
            std::cout << "|                                                  |\n";
        }
    }
    if (not expenses.empty())
    {
        std::cout << "| (Input the number before each expense to edit)   |\n";
        std::cout << "|                                                  |\n";
    }

    std::cout << "| (0) Back                                         |\n";
    std::cout << "*--------------------------------------------------*\n";
}