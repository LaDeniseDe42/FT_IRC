/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:54:43 by qdenizar          #+#    #+#             */
/*   Updated: 2024/04/11 12:02:27 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void server::kickYourAssOfMyChannel(std::istringstream &iss, client *sender)
{
    if (sender->Registered() == false)
    {
        sendMessage(ERR_NOTREGISTERED(sender->getNick()), sender->getFd());
        return;
    }
    std::string channelName;
    std::string target;
    
    std::string reason;
    iss >> channelName;
    if (channelName == "#jail")
        return;
    iss >> target;
    std::string temp;
    iss >> reason;
    std::getline(iss, temp);
    reason += temp;
    reason.erase(0, 1);
    if (reason.size() == 0)
        reason = "Kicked by " + sender->getNick();
    if (channelName.size() <= 0 || target.size() <= 0 || reason.size() <= 0)
    {
        sendMessage(ERR_NEEDMOREPARAMS(sender->getNick(), "KICK"), sender->getFd());
        return;
    }
    if (channelName[0] != '#')
    {
        sendMessage(ERR_NOSUCHCHANNEL(sender->getNick(), channelName), sender->getFd());
        return;
    }
    for (size_t i = 0; i < _channels.size(); i++)
    {
        if (_channels[i]->getChannelName() == channelName)
        {
            if (_channels[i]->isOperator(sender->getUser()) == false)
            {
                sendMessage(ERR_CHANOPRIVSNEEDED(sender->getNick(), channelName), sender->getFd());
                return;
            }
            std::vector<client *> clients = _channels[i]->getChannelClients();
            for (size_t j = 0; j < clients.size(); j++)
            {
                if (clients[j]->getNick() == target)
                {
                    if (_channels[i]->isOperator(clients[j]->getUser()) == true)
                    {
                        return;
                    }
                    sendMessage(KICK(sender->getNick(), channelName, target, reason), sender->getFd());
                    _channels[i]->leaveChannel(clients[j], reason);
                    return;
                }
            }
            sendMessage(ERR_USERNOTINCHANNEL(sender->getNick(), target, channelName), sender->getFd());
            return;
        }
    }
    sendMessage(ERR_NOSUCHCHANNEL(sender->getNick(), channelName), sender->getFd());
}