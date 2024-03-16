#include "../inc/auto_generate.h"
#include "../inc/printers.h"

void import_data(std::ifstream &file, std::vector<User> &user_list, std::vector<Group> &group_list)
{
    std::string line;
    // Read the file line by line until reaching the "Groups" line
    while (std::getline(file, line) && line.find("Groups") == std::string::npos)
    {
        // Skip the "Users" line
        if (line.find("Users") != std::string::npos)
        {
            continue;
        }

        // Skip empty lines
        if (line.empty())
        {
            continue;
        }

        line.erase(std::remove_if(line.begin(), line.end(),
                                  [](char c)
                                  { return c == '\r'; }),
                   line.end());

        line.erase(std::remove_if(line.begin(), line.end(),
                                  [](char c)
                                  { return c == '\n'; }),
                   line.end());

        // add user with the name stored in line
        add_user(line, user_list);
    }

    // Read the lines under "Groups" until reaching the "Expenses" line
    while (std::getline(file, line) && line.find("Expenses") == std::string::npos)
    {
        // Skip the "Groups" line
        if (line.find("Groups") != std::string::npos)
        {
            continue;
        }

        // Skip empty lines
        if (line.empty())
        {
            continue;
        }

        // Split the line into group_name and members
        std::istringstream iss(line);
        std::string group_name, members;
        std::getline(iss, group_name, ',');
        std::getline(iss, members);

        // Remove quotes from members using std::remove_if and erase idiom
        members.erase(std::remove_if(members.begin(), members.end(),
                                     [](char c)
                                     { return c == '\"'; }),
                      members.end());

        members.erase(std::remove_if(members.begin(), members.end(),
                                     [](char c)
                                     { return c == '\r'; }),
                      members.end());

        members.erase(std::remove_if(members.begin(), members.end(),
                                     [](char c)
                                     { return c == '\n'; }),
                      members.end());

        // Split members into vector
        std::vector<std::string> membersVector;
        std::istringstream membersStream(members);
        std::string member;

        // store group in the vector
        add_group(group_name, group_list);

        // Add all group users
        while (std::getline(membersStream, member, ','))
        {

            for (auto &user : user_list)
            {
                if (user.name().compare(member) == 0)
                {
                    add_user_to_group(user, group_list.back());
                    break;
                }
            }
        }
    }

    // Read the lines under "Expenses"
    while (std::getline(file, line))
    {
        // Skip the "Expenses" line
        if (line.find("Expenses") != std::string::npos)
        {
            continue;
        }

        // Skip empty lines
        if (line.empty())
        {
            continue;
        }

        // Split the line into parts
        std::istringstream iss(line);
        std::string groupName, payer_name, payee_names, amountStr;
        std::getline(iss, groupName, ',');
        std::getline(iss, payer_name, ',');

        // Check if the string for payee has '\"' to be used as delimeter, if not use ',' instead
        if (iss.peek() == '\"')
        {
            // Ignore \"
            iss.ignore();

            std::getline(iss, payee_names, '\"');
            if (iss.peek() == ',')
            {
                // Ignore the comma
                iss.ignore();
            }
        }
        else
        {
            std::getline(iss, payee_names, ',');
        }

        std::getline(iss, amountStr);

        amountStr.erase(std::remove_if(amountStr.begin(), amountStr.end(),
                                       [](char c)
                                       { return c == '\r'; }),
                        amountStr.end());

        amountStr.erase(std::remove_if(amountStr.begin(), amountStr.end(),
                                       [](char c)
                                       { return c == '\n'; }),
                        amountStr.end());

        // Convert amount to float
        float amount = std::stof(amountStr);

        // Remove quotes from payee using std::remove_if and erase idiom
        payee_names.erase(std::remove_if(payee_names.begin(), payee_names.end(),
                                         [](char c)
                                         { return c == '\"'; }),
                          payee_names.end());

        // Split payee into vector
        std::vector<std::string> payeeVector;
        std::istringstream payeeStream(payee_names);
        std::string payee_name;

        // Find payee_ids
        std::vector<int> payee_ids{};
        while (std::getline(payeeStream, payee_name, ','))
        {
            for (const auto &user : user_list)
            {
                if (user.name().compare(payee_name) == 0)
                {
                    payee_ids.push_back(user.id());
                    break;
                }
            }
        }

        // Find payer_id
        int payer_id{};
        for (const auto &user : user_list)
        {
            if (user.name().compare(payer_name) == 0)
            {
                payer_id = user.id();
                break;
            }
        }

        // Find the corresponding group and add the expense
        for (auto &group : group_list)
        {
            if (group.name().compare(groupName) == 0)
            {
                add_expense_to_group(amount * 100, payer_id, payee_ids, group, user_list);
            }
        }
    }
}

void auto_run(std::vector<User> &user_list, std::vector<Group> &group_list)
{
    // Print all users
    std::cout << "_________________________\n";
    std::cout << "Users list:" << std::endl;
    std::cout << "_________________________\n";
    print_all_users(user_list);

    // Print all Groups
    std::cout << "_________________________\n";
    std::cout << "Groups list:" << std::endl;
    std::cout << "_________________________\n";
    print_all_groups(group_list);

    // Print all group members
    std::cout << std::endl;
    for (auto &group : group_list)
    {
        std::cout << "_________________________\n";
        std::cout << group.name() << "'s information" << std::endl;
        std::cout << "_________________________\n";
        std::cout << std::endl;
        // Print all group members
        group.print_group_members(user_list, group_list);
        std::cout << std::endl;
        // Print all group expenses
        std::cout << "Groups expenses:" << std::endl;
        print_expenses(group.id(), user_list, group_list);
        std::cout << std::endl;
        // Create and print all group settlements
        std::cout << "Groups settlements:" << std::endl;
        group.create_settlement(user_list);
        std::cout << std::endl;
    }
};
