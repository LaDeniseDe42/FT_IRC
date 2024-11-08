/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:27:30 by akastler          #+#    #+#             */
/*   Updated: 2024/04/12 09:53:53 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void server::joinCmd(std::istringstream &iss, client *author)
{
    if (author->Registered() == false)
        {sendMessage(ERR_NOTREGISTERED(author->getNick()), author->getFd()); return;}
    std::string channelName;
    std::string mdp;
    iss >> channelName;
    iss >> mdp;
    std::cout << "\033[38;2;255;165;0m" << author->getNick() << " \033[1;32mtry to join channel\033[38;2;255;165;0m [" << channelName.c_str() << "]\033[0m" << std::endl;
    if (channelName.size() <= 0)
        {sendMessage(ERR_NEEDMOREPARAMS(author->getNick(), "JOIN"), author->getFd()); return;}
    if (channelName[0] != '#')
        {sendMessage(ERR_NOSUCHCHANNEL(author->getNick(), channelName), author->getFd()); return;}
    if (channelName.size() < 2)
        {sendMessage(ERR_BADCHANMASK(author->getNick(), channelName), author->getFd()); return;}
    for (unsigned int i = 0; i < channelName.size(); i++)
        channelName[i] = std::tolower(channelName[i]);
    if (mdp.size() > 0 && mdp == "x")
        mdp = "";
    for (size_t i = 0; i < _channels.size(); i++)
    {
        if (_channels[i]->getChannelName() == channelName)
        {
            if (_channels[i]->isInviteMode() == true)
            {
                for (size_t j = 0; j < _channels[i]->getInvitationList().size(); j++)
                {
                    if (_channels[i]->getInvitationList()[j] == author->getNick())
                    {
                        if (_channels[i]->isFull() == true)
                        {
                            sendMessage(ERR_CHANNELISFULL(author->getNick(), _channels[i]->getChannelName()), author->getFd());
                            
                            return;
                        }
                        _channels[i]->joinChannel(author);
                        author->addChannel(channelName);
                        _channels[i]->removeInvitation(author->getNick());
                        return;
                    }
                }
                sendMessage(ERR_INVITEONLYCHAN(author->getNick(), _channels[i]->getChannelName()), author->getFd());
                return;
            }
            else if (_channels[i]->isMdp() == true)
            {
                if (mdp.size() <= 0)
                {
                    sendMessage(ERR_NEEDMOREPARAMS(author->getNick(), "JOIN"), author->getFd());
                    sendMessage(ERR_BADCHANNELKEY(author->getNick(), _channels[i]->getChannelName()), author->getFd());
                    return;
                }
                else if (mdp != _channels[i]->getMdp())
                    {sendMessage(ERR_BADCHANNELKEY(author->getNick(), _channels[i]->getChannelName()), author->getFd()); return;}
                if (_channels[i]->isFull() == true)
                    {sendMessage(ERR_CHANNELISFULL(author->getNick(), _channels[i]->getChannelName()), author->getFd()); return;}
                else
                {
                    _channels[i]->joinChannel(author);
                    author->addChannel(channelName);
                    return;
                }
            }
            else
            {
                if (_channels[i]->isFull() == true)
                    {sendMessage(ERR_CHANNELISFULL(author->getNick(), _channels[i]->getChannelName()), author->getFd()); return;}
                _channels[i]->joinChannel(author);
                author->addChannel(channelName);
                return;
            }
        }
    }
    channel *newChannel = new channel(channelName);
    newChannel->changeTopic("Welcome to " + channelName, author->getNick());
    std::string botName = "Bot";
    botName += channelName;
    newChannel->setBot(botName);
    newChannel->joinChannel(author);
    newChannel->addOperator(author, author->getNick());
    if (mdp.size() > 0)
        newChannel->setMdp(mdp, author->getNick());
    _channels.push_back(newChannel);
    author->addChannel(channelName);
    return;
}