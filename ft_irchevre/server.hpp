/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:41:04 by akastler          #+#    #+#             */
/*   Updated: 2024/04/02 16:54:49 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "includes.hpp"

class server
{
    private:
        int _port;
        std::string _password;
        int _socketServer;
        struct sockaddr_in _serverAddr;
        int _epollFd;
        std::vector<client *> _clients;
        std::vector<channel *> _channels;
        unsigned int _nbCo;
        std::string _ip;

        void acceptClient();
        void registerClient(client *client);
        void tryCommands(std::string command, client *client);
        void cmdForRegisteredUser(std::istringstream &iss, std::string word, client *client);
        void otherCmd(std::istringstream &iss, std::string word, client *client, bool regist);
        void cmdInJail(std::istringstream &iss,std::string word, client *client);
        void clientTryToEscape(client *sender);

        void sendMessage(std::string message, int fd);

        void changeNick(std::string nick, client *client);
        void privateMsg(std::istringstream &iss, client *client);
        void whoCommand(std::istringstream &iss, client *client);
        void topic(std::istringstream &iss, client *client);
        void mode(std::istringstream &iss, client *sender);
        void kickYourAssOfMyChannel(std::istringstream &iss, client *sender);
        void joinCmd(std::istringstream &iss, client *client);
        void leaveChannel(std::istringstream &iss, client *client);
        void inviteTheDevil(std::istringstream &iss, client *sender);

        void botCommand(std::string message, client *author, channel *chan);
        
        void sendGoatOfTheDay(client *client);

        void killClient(client *client);
        bool handleUnknownCommand(std::string command, client *client);

        std::string getNumberInString(int number);
        std::string getNumberInString(unsigned int number);
        std::string getNumberInString(size_t number);
        std::vector<std::string> split(std::string str, char separator);

        void sendJailMessage(client *client);

    public:
        server(int port, std::string password);
        ~server();
        void run();
        void stop();
};