/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:00:23 by qdenizar          #+#    #+#             */
/*   Updated: 2024/04/11 12:06:25 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void server::topic(std::istringstream &iss, client *sender)
{
    
        std::cout << "\033[1;32mclient try to change the topic of a channel" << std::endl;
        std::string channelName;
        std::string topic;
        iss >> channelName;
        std::string temp;
        iss >> topic;
        std::getline(iss, temp);
        topic += temp;
        if (topic[0] == ':')
            topic.erase(0, 1);
        if (topic.size() <= 0)
        {
            sendMessage(ERR_NEEDMOREPARAMS(sender->getNick(), "TOPIC"), sender->getFd());
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
                std::vector<client *> listOfClients = _channels[i]->getChannelClients();
                int clientIsInChannel = 0;
                for (unsigned int j = 0; j < listOfClients.size(); j++)
                {
                    if (listOfClients[j] == sender)
                    {
                        clientIsInChannel = 1;
                        break;
                    }
                }
                if (clientIsInChannel == 0)
                {
                    sendMessage(ERR_NOTONCHANNEL(sender->getNick(), channelName), sender->getFd());
                    return;
                }
                _channels[i]->changeTopic(topic , sender->getNick());
                return;
            }
        }
        sendMessage(ERR_NOSUCHCHANNEL(sender->getNick(), channelName), sender->getFd());
}