/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:26:23 by qdenizar          #+#    #+#             */
/*   Updated: 2024/04/12 09:53:55 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void server::inviteTheDevil(std::istringstream &iss, client *sender)
{
    if (sender->Registered() == false)
    {
        sendMessage(ERR_NOTREGISTERED(sender->getNick()), sender->getFd());
        return;
    }
    std::string who;
    std::string where;
    iss >> who;
    iss >> where;
    if (who.size() <= 0 || where.size() <= 0)
    {
        sendMessage(ERR_NEEDMOREPARAMS(sender->getNick(), "INVITE"), sender->getFd());
        return;
    }
    if (where[0] != '#')
    {
        sendMessage(ERR_NOSUCHCHANNEL(sender->getNick(), where), sender->getFd());
        return;
    }
    std::vector<client *> channelClients;
    bool channelExist = false;
    int channelIndex = 0;
    for (size_t i = 0; i < _channels.size(); i++)
    {
        if (_channels[i]->getChannelName() == where)
        {
            channelExist = true;
            channelIndex = i;
            channelClients = _channels[i]->getChannelClients();
            break;
        }
    }
    if (channelExist == false)
    {
        sendMessage(ERR_NOSUCHCHANNEL(sender->getNick(), where), sender->getFd());
        return;
    }
    bool clientExist = false;
    for (size_t i = 0; i < channelClients.size(); i++)
    {
        if (channelClients[i]->getNick() == sender->getNick())
        {
            clientExist = true;
            break;
        }
    }
    if (clientExist == false)
    {
        sendMessage(ERR_NOTONCHANNEL(sender->getNick(), where), sender->getFd());
        return;
    }
    for (size_t i = 0; i < channelClients.size(); i++)
    {
        if (channelClients[i]->getNick() == who)
        {
            sendMessage(ERR_USERONCHANNEL(who, where), sender->getFd());
            return;
        }
    }
    if (clientExist == true && channelExist == true)
    {
        for (size_t i = 0; i < _clients.size(); i++)
        {
            if (_clients[i]->getNick() == who)
            {
                sendMessage(RPL_INVITING(sender->getNick(), who, where), _clients[i]->getFd());
                sendMessage(RPL_INVITING(sender->getNick(), who, where), sender->getFd());
                _clients[i]->addInvitation(where);
                _channels[channelIndex]->addInvitation(who);
                int clientIndex = 0;
                for (size_t j = 0; j < _clients.size(); j++)
                {
                    if (_clients[j]->getNick() == who)
                    {
                        clientIndex = j;
                        break;
                    }
                }
                // if (_channels[channelIndex]->isMdp() == true)
                // {
                //     std::string mdp;
                //     mdp = _channels[channelIndex]->getMdp();
                //     std::string mdpMessage = "Invitation for you <3 Use the command /JOIN " + where + " " + mdp ;
                //     sendMessage(PRIVMSG(sender->getNick(), who, mdpMessage + "" + " " + where), _clients[clientIndex]->getFd());

                // }
                // else
                //     sendMessage(PRIVMSG(sender->getNick(), who, "INVITATION FOR YOU <3 " + who + " " + where), _clients[clientIndex]->getFd());
                return;
            }
        }
        sendMessage(ERR_NOSUCHNICK(sender->getNick(), who), sender->getFd());
    }

}