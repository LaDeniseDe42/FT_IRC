/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:52:05 by akastler          #+#    #+#             */
/*   Updated: 2024/04/11 12:23:26 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

std::string stringToLower(std::string str)
{
    std::string newStr = "";
    for (size_t i = 0; i < str.size(); i++)
        newStr += std::tolower(str[i]);
    return newStr;
}

void server::changeNick(std::string nick, client *client)
{
    if (nick.size() <= 0)
    {
        sendMessage(ERR_NONICKNAMEGIVEN(client->getNick()), client->getFd());
        return;
    }
    for (size_t i = 0; i < _clients.size(); i++)
    {
        if (stringToLower(_clients[i]->getNick()) == stringToLower(nick))
        {
            sendMessage(ERR_NICKNAMEINUSE(client->getNick(), nick), client->getFd());
            return;
        }
    }
    if (nick.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\|{}") != std::string::npos || nick.size() > 32)
    {
        sendMessage(ERR_ERRONEUSNICKNAME(client->getNick()), client->getFd());
        return;
    }
    if (client->Registered() == true)
        sendMessage(NICK(client->getNick(), nick), client->getFd());
    std::cout << "\033[1;32mclient try to change his old nick: \033[38;2;255;165;0m" << client->getNick() << "\033[1;32m with a new nick, \033[38;2;255;165;0m" << nick << " \033[0m!" << std::endl;
    if (nick == "GOD" || nick == "DIEU")
        client->setPv(1000000000);
    client->setNick(nick);
}