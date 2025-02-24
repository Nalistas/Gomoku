/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** ManagerConnection
*/

#include <string>
#include <fstream>
#include <map>
#include <functional>
#include "Board.hpp"

#ifndef MANAGERCONNECTION_HPP_
    #define MANAGERCONNECTION_HPP_

class ManagerConnection {
    public:
        ManagerConnection(std::string const &output = "output.txt", std::string const &name = "Anonymous", std::string const &version = "0.0.0", std::string const &author = "Nymand", std::string const &country = "USA");
        ~ManagerConnection();

        void add_action(std::string const &name, std::function<int(std::string const &)> function);
        int exec(std::string const &command, std::string const &params);

        std::string get(void);
        void put(std::string const &command);
        void log(std::string const &command);
        std::ostream &get_log(void);

        void handle_info(std::string const &params);
        int get_infos(std::string const &command);

    protected:
        void handle_about(std::string const &params);

        std::fstream _output;
        std::string const _name;
        std::string const _version;
        std::string const _author;
        std::string const _country;
        std::map<std::string, int> _infos;
        std::map<std::string, std::function<int(std::string const &)>> _functions;
};

#endif /* !MANAGERCONNECTION_HPP_ */
