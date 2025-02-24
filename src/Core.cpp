/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** Core
*/

#include "Core.hpp"
#include "ManagerConnection.hpp"
#include "Player.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <thread>
#include <sstream>

Core::Core()
{
}

Core::~Core()
{}

int Core::run(std::string const &name)
{
    std::string command, str_got;
    std::string log_name("zlog_");
    ManagerConnection con(log_name + name.substr(2, name.size() - 6) + ".txt", name);
    Board board(20);
    Player player(con, board);

    con.log("stating the main loop");
    str_got = con.get();
    if (str_got == "END") {
        return 0;
    }
    std::cerr << "str_got outside: " << str_got << std::endl;
    while (str_got != "END") {
        std::istringstream ss(str_got);
        ss >> command;
        std::getline(ss, str_got);
        con.exec(command, str_got);
        str_got = con.get();
        std::cerr << "str_got in loop: " << str_got << std::endl;
        if (str_got == "END") {
            std::cerr << "END !!!" << std::endl;
            return 0;
        }
    }
    return 0;
}
