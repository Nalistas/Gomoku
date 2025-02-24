/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** ManagerConnection
*/

#include <iostream>
#include <sstream>
#include <map>
#include <list>
#include "ManagerConnection.hpp"
#include "Board.hpp"

ManagerConnection::ManagerConnection(std::string const &output, std::string const &name, std::string const &version, std::string const &author, std::string const &country) :
    _output(output, std::ios::out),
    _name(name),
    _version(version),
    _author(author),
    _country(country)
{
    this->add_action("INFO", [this](std::string const &command) {this->handle_info(command); return 0;});
    this->add_action("ABOUT", [this](std::string const &command) {this->handle_about(command); return 0;});
}


ManagerConnection::~ManagerConnection(void)
{
}

void ManagerConnection::log(std::string const &command)
{
    this->_output << "-- " << command << std::endl;
}

std::string ManagerConnection::get(void)
{
    std::string command;

    std::getline(std::cin, command);
    // if (std::cin.eof()) {
    //     this->log("end of file");
    //     return ("END");
    // }
    this->_output << ">> \"" << command.substr(0, command.find('\n')) << "\"" << std::endl;
    return command;
}

/*************  ✨ Codeium Command ⭐  *************/
/// \brief Send a command to the manager and log it
///
/// \param command The command to send
///
/// This function writes the command to the manager's output stream and
/// logs it in the log file.
/******  90e05122-a845-4563-84a5-2da8e2d835ba  *******/void ManagerConnection::put(std::string const &command)
{
    this->_output << "<< \"" << command << "\"" << std::endl;
    std::cout << command << std::endl;
}

void ManagerConnection::add_action(std::string const &name, std::function<int(std::string const &)> function)
{
    this->_functions[name] = function;
}

void ManagerConnection::handle_info(std::string const &command)
{
    std::stringstream ss(command);
    std::string name;
    int value;

    ss >> name;
    ss >> value;
    this->_infos[name] = value;
}

int ManagerConnection::get_infos(std::string const &command)
{
    if (this->_infos.find(command) != this->_infos.end())
        return this->_infos[command];
    return 0;
}

void ManagerConnection::handle_about(std::string const &command __attribute__((unused)))
{
    this->put("name=\"" + this->_name + "\", version=\"" + this->_version + "\", author=\"" + this->_author + "\", country=\"" + this->_country + "\"");
}

int ManagerConnection::exec(std::string const &command, std::string const &params)
{
    if (this->_functions.find(command) != this->_functions.end())
        return this->_functions[command](params);
    else {
        this->log("command not found :");
        this->log(command);
    }
    return 0;
}

std::ostream &ManagerConnection::get_log(void)
{
    return (this->_output);
}
/*
BOARD
10,10,2
10,11,2
10,12,2
10,13,2
10,14,2
DONE
*/
