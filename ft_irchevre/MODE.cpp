/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:13:25 by qdenizar          #+#    #+#             */
/*   Updated: 2024/04/11 12:07:50 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

long strToLong(const std::string &str)
{
    std::stringstream ss(str);
    long result;
    ss >> result;

    if (ss.fail() || !ss.eof())
        return (-1);

    return result;
}

void server::mode(std::istringstream &iss, client *sender)
{
    std::string channelOrUser;
    iss >> channelOrUser;
    if (channelOrUser == "#jail")
        return;
    if (channelOrUser.size() <= 0)
    {
        sendMessage(ERR_NEEDMOREPARAMS(sender->getNick(), "MODE"), sender->getFd());
        return;
    }
    else if (channelOrUser[0] != '#' && channelOrUser[0])
    {
        sendMessage(ERR_NOSUCHCHANNEL(sender->getNick(), channelOrUser), sender->getFd());
        return;
    }
    std::string mode;
    iss >> mode;
    if (mode.size() <= 0)
    {
        if (channelOrUser[0] == '#')
        {
            std::string mode;
            if (_channels.size() == 0)
            {
                sendMessage(RPL_UMODEIS(sender->getNick(), ""), sender->getFd());
                return;
            }
            for (size_t i = 0; i < _channels.size(); i++)
            {
                if (_channels[i]->getChannelName() == channelOrUser)
                {
                    mode = _channels[i]->getMode();
                    std::stringstream ss;
                    ss << _channels[i]->getCreation();
                    sendMessage(RPL_CHANNELMODEIS(sender->getNick(), channelOrUser, mode), sender->getFd());
                    sendMessage(RPL_CREATIONTIME(sender->getNick(), channelOrUser, ss.str()), sender->getFd());
                    return;
                }
            }
            sendMessage(ERR_NOSUCHCHANNEL(sender->getNick(), channelOrUser), sender->getFd());
        }
    }
    std::string info;
    iss >> info;
    std::string temp;
    std::getline(iss, temp);
    info += temp;
    if (channelOrUser[0] == '#')
    {
        if (mode != "+o" && mode != "-o"
            && mode != "+k" && mode != "-k"
            && mode != "+t" && mode != "-t"
            && mode != "+l" && mode != "-l"
            && mode != "+i" && mode != "-i")
        {
            if (mode != "b")
                sendMessage(ERR_UNKNOWNMODE(sender->getNick(), mode), sender->getFd());
            return;
        }
        for (size_t i = 0; i < _channels.size(); i++)
        {
            if (_channels[i]->getChannelName() == channelOrUser)
            {
                if (_channels[i]->isOperator(sender->getUser()) == false)
                    sendMessage(ERR_CHANOPRIVSNEEDED(sender->getNick(), channelOrUser), sender->getFd());
                else if (mode == "+o")
                    _channels[i]->addOperator(sender, info);
                else if (mode == "-o")
                    _channels[i]->removeOperator(sender, info);
                else if (mode == "+k")
                    _channels[i]->setMdp(info, sender->getNick());
                else if (mode == "-k")
                    _channels[i]->deletemdp(sender->getNick());
                else if (mode == "+t")
                    _channels[i]->setWeCanChangeTopic(true, sender->getNick());
                else if (mode == "-t")
                    _channels[i]->setWeCanChangeTopic(false, sender->getNick());
                else if (mode == "+l")
                {
                    long value = strToLong(info);
                    if (value < 0 || value > INT_MAX)
                    {
                        sendMessage(ERR_NEEDOTHERPARAMS(sender->getNick()), sender->getFd());
                        return;
                    }
                    else
                        _channels[i]->setLimit(static_cast<int>(value), sender->getNick());
                    return;
                }
                else if (mode == "-l")
                    _channels[i]->deleteLimit(sender->getNick());
                else if (mode == "+i")
                    _channels[i]->modeInvitationList(sender->getNick());
                else if (mode == "-i")
                    _channels[i]->removeModeInvitationList(sender->getNick());
            }
        }
    }
}