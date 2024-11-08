/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:37:26 by akastler          #+#    #+#             */
/*   Updated: 2024/04/11 12:05:57 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void server::leaveChannel(std::istringstream &iss, client *author)
{
    std::string channelName;

    iss >> channelName;
    std::cout << "\033[38;2;255;165;0m" << author->getNick() <<" \033[1;32mtry to leave channel \033[38;2;255;165;0m" << channelName << "\033[0m" << std::endl;
    
    std::string reason;
    iss >> reason;
    std::string temp;
    std::getline(iss, temp);
    reason += temp;
    if (reason[0] == ':')
        reason.erase(0, 1);
    if (reason.size() <= 0)
        reason = "go make some tea";
    if (channelName[0] != '#')
    {
        sendMessage(ERR_NOSUCHCHANNEL(author->getNick(), channelName), author->getFd());
        return;
    }
    for (unsigned int i = 0; i < _channels.size(); i++)
    {
        if (_channels[i]->getChannelName() == channelName)
        {
            std::vector<client *> authors = _channels[i]->getChannelClients();
            int IsInChannel = 0;
            for (unsigned int j = 0; j < authors.size(); j++)
            {
                if (authors[j] == author)
                    {IsInChannel = 1; break;}
            }
            if (IsInChannel == 0)
            {
                sendMessage(ERR_NOTONCHANNEL(author->getNick(), channelName), author->getFd());
                return;
            }
            _channels[i]->leaveChannel(author, reason);
            if (_channels[i]->getChannelClients().size() == 0 && _channels[i]->getChannelName() != "#jail")
            {
                delete _channels[i];
                _channels.erase(_channels.begin() + i);
            }
            return;
        }
    }
    sendMessage(ERR_NOSUCHCHANNEL(author->getNick(), channelName), author->getFd());
}