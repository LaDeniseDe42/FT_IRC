/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:33:28 by akastler          #+#    #+#             */
/*   Updated: 2024/04/12 10:06:59 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

channel::channel(std::string channelName)
{
    _channelName = channelName;
    _topic = "";
    _thereIsMdp = false;
    _mdp = "";
    _limit = 0;
    _weCanChangeTopic = true;
    _inviteMode = false;
    _creationTime = std::time(NULL);
}


channel::~channel()
{
    delete _bot;
}

std::string channel::getChannelName()
{
    return _channelName;
}

std::string channel::getTopic()
{
    return _topic;
}

std::string channel::getMdp()
{
    return _mdp;
}

bool channel::isMdp()
{
    return _thereIsMdp;
}

void channel::modeInvitationList(std::string author)
{
    _inviteMode = true;
    std::string message = MODE(author, _channelName, "+i", "");
    for (unsigned int i = 0; i < _channelClients.size(); i++)
        send(_channelClients[i]->getFd(), message.c_str(), message.size(), 0);
}

void channel::removeModeInvitationList(std::string author)
{
    _inviteMode = false;
    std::string message = MODE(author, _channelName, "-i", "");
    for (unsigned int i = 0; i < _channelClients.size(); i++)
        send(_channelClients[i]->getFd(), message.c_str(), message.size(), 0);
}

void channel::setWeCanChangeTopic(bool weCanChangeTopic, std::string author)
{
    _weCanChangeTopic = weCanChangeTopic;
    if (_weCanChangeTopic == true)
    {
        std::string message = MODE(author, _channelName, "+t", "");
        for (unsigned int i = 0; i < _channelClients.size(); i++)
            send(_channelClients[i]->getFd(), message.c_str(), message.size(), 0);
    }
    else
    {
        std::string message = MODE(author, _channelName, "-t", "");
        for (unsigned int i = 0; i < _channelClients.size(); i++)
            send(_channelClients[i]->getFd(), message.c_str(), message.size(), 0);
    }
}

void channel::setMdp(std::string mdp, std::string author)
{
    if (mdp.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") != std::string::npos)
    {
        for (unsigned int i = 0; i < _channelClients.size(); i++)
        {
            if (_channelClients[i]->getNick() == author)
            {
                std::string message = ERR_INVALIDKEY(author, _channelName);
                send(_channelClients[i]->getFd(), message.c_str(), message.size(), 0);
                return;
            }
        }
    }
    if (mdp.size() < 2 || mdp.size() > 32)
    {
        for (unsigned int i = 0; i < _channelClients.size(); i++)
        {
            if (_channelClients[i]->getNick() == author)
            {
                std::string message = ERR_INVALIDKEY2(author, _channelName);
                send(_channelClients[i]->getFd(), message.c_str(), message.size(), 0);
                return;
            }
        }
    }
    _mdp = mdp;
    _thereIsMdp = true;
    std::string message = MODE(author, _channelName, "+k", "******");
    for (unsigned int i = 0; i < _channelClients.size(); i++)
        send(_channelClients[i]->getFd(), message.c_str(), message.size(), 0);
}

void channel::deletemdp(std::string author)
{
    _mdp = "";
    _thereIsMdp = false;
    std::string message = MODE(author, _channelName, "-k", _mdp);
    for (unsigned int i = 0; i < _channelClients.size(); i++)
        send(_channelClients[i]->getFd(), message.c_str(), message.size(), 0);
}

std::string channel::getMode()
{
    std::string mode = "";
    if (_thereIsMdp == true)
        mode += "k";
    if (_weCanChangeTopic == true)
        mode += "t";
    if (_inviteMode == true)
        mode += "i";
    if (_limit != 0)
        mode += "l";
    return mode;
}

void channel::setLimit(int limit, std::string author)
{

    _limit = limit;
    std::stringstream ss;
    ss << limit;
    std::string newLimit = ss.str();
    std::string message = MODE(author, _channelName, "+l", newLimit);
    for (unsigned int i = 0; i < _channelClients.size(); i++)
        send(_channelClients[i]->getFd(), message.c_str(), message.size(), 0);
    

}

bool channel::isFull()
{
    if (_limit == 0)
        return false;
    if (_channelClients.size() >= (unsigned int)_limit)
        return true;
    return false;
}

void channel::deleteLimit(std::string author)
{
    _limit = 0;
    std::string message = MODE(author, _channelName, "-l", "0");
    for (unsigned int i = 0; i < _channelClients.size(); i++)
        send(_channelClients[i]->getFd(), message.c_str(), message.size(), 0);
}

bool channel::isOperator(std::string user)
{
    for (size_t i = 0; i < _operator.size(); i++)
    {
        if (_operator[i] == user)
            return true;
    }
    return false;
}

void channel::addOperator(client *author, std::string user)
{
    if (_operator.size() == 0)
    {
        _operator.push_back(author->getUser());
        std::string localhost = "localhost";
        std::string ok = MODE(localhost, _channelName, "+o", author->getNick());
        for (unsigned int i = 0; i < _channelClients.size(); i++)
            send(_channelClients[i]->getFd(), ok.c_str(), ok.size(), 0);
    }
    if (isOperator(author->getUser()) == false && _channelClients.size() > 1)
    {
        std::string message = ERR_CHANOPRIVSNEEDED(author->getNick(), _channelName);
        send(author->getFd(), message.c_str(), message.size(), 0);
        return;
    }
    else
    {
        client *Operatortoadd = NULL;
        for (size_t i = 0; i < _channelClients.size(); i++)
        {
            if (_channelClients[i]->getNick() == user)
            {
                Operatortoadd = _channelClients[i];
                break;
            }
        }
        if (Operatortoadd == NULL)
        {
            std::string message = ERR_NOSUCHNICK(author->getNick(), user);
            send(author->getFd(), message.c_str(), message.size(), 0);
            return;
        }
        for (size_t i = 0; i < _operator.size(); i++)
        {
            if (_operator[i] == Operatortoadd->getUser())
                return;
        }  
        _operator.push_back(Operatortoadd->getUser());
        std::string message = MODE(author->getNick(), _channelName, "+o", Operatortoadd->getNick());
        for (unsigned int i = 0; i < _channelClients.size(); i++)
            send(_channelClients[i]->getFd(), message.c_str(), message.size(), 0);
    }
}

void channel::removeOperator(client *author, std::string user)
{
    if (isOperator(author->getUser()) == false && _channelClients.size() > 1)
    {
        std::string message = ERR_CHANOPRIVSNEEDED(author->getNick(), _channelName);
        send(author->getFd(), message.c_str(), message.size(), 0);
        return;
    }
    if (_operator.size() == 1 && _operator[0] == author->getUser() && _channelClients.size() == 1)
        return;
    for (size_t i = 0; i < _channelClients.size(); i++)
    {
        if (_channelClients[i]->getNick() == user)
        {
            user = _channelClients[i]->getUser();
            break;
        }
    }
    for (size_t i = 0; i < _operator.size(); i++)
    {
        if (_operator[i] == user)
        {
            _operator.erase(_operator.begin() + i);
            std::string message = MODE(author->getNick(), _channelName, "-o", user);
            for (unsigned int i = 0; i < _channelClients.size(); i++)
                send(_channelClients[i]->getFd(), message.c_str(), message.size(), 0);
            return;
        }
    }
}

int channel::joinChannel(client *client)
{
    _channelClients.push_back(client);
    std::string message = JOIN(client->getNick(), client->getUser(), _channelName);
    std::string topic;
    if (_topic.size() > 0)
        topic = RPL_TOPIC(client->getNick(), _channelName, _topic);
    else
        topic = RPL_NOTOPIC(client->getNick(), _channelName);
    for (unsigned int j = 0; j < _channelClients.size(); j++)
        send(_channelClients[j]->getFd(), message.c_str(), message.size(), 0);
    send(client->getFd(), topic.c_str(), topic.size(), 0);

    std::string names = ":localhost 353 " + client->getNick() + " = " + _channelName + " :";
    names += "@Bot" + _channelName + " ";
    for (unsigned int j = 0; j < _channelClients.size(); j++)
    {
        std::string username = _channelClients[j]->getUser();

        for (unsigned int i = 0; i < _operator.size(); i++)
        {
            if (_operator[i] == username)
                username = "";
        }
        if (username == "" || _channelClients.size() == 1)
            names += "@";
        names += _channelClients[j]->getNick() + " ";

    }
    names += "\r\n";
    send(client->getFd(), names.c_str(), names.size(), 0);

    std::string endOfNames = ":localhost 366 " + client->getNick() + " " + _channelName + " :End of /NAMES list.\r\n";
    send(client->getFd(), endOfNames.c_str(), endOfNames.size(), 0);
    if (_channelName == "#fire")
        _bot->sendAscii("CHAR");
    else if (_channelName == "#water")
        _bot->sendAscii("CARA");
    else if (_channelName == "#grass")
        _bot->sendAscii("BULB");
    return 1;
}

int channel::leaveChannel(client *client, std::string reason)
{
    for (size_t i = 0; i < _channelClients.size(); i++)
    {
        if (_channelClients[i] == client)
        {
            std::string message = PART(client->getNick(), client->getUser(), _channelName, reason);
            client->removeChannel(_channelName);
            for (unsigned int j = 0; j < _channelClients.size(); j++)
                send(_channelClients[j]->getFd(), message.c_str(), message.size(), 0);
            if (isOperator(client->getUser()) == true)
                removeOperator(client, client->getNick());
            _channelClients.erase(_channelClients.begin() + i);
            if (_operator.size() == 0 && _channelClients.size() > 0)
            {
                addOperator(_channelClients[0], _channelClients[0]->getNick());
            }
            return 1;
        }
    }
    return 0;
}

std::vector<client *> channel::getChannelClients()
{
    return _channelClients;
}

bool channel::isInviteMode()
{
    return _inviteMode;
}

void channel::addInvitation(std::string user)
{
    _invitationList.push_back(user);
}

void channel::removeInvitation(std::string user)
{
    for (size_t i = 0; i < _invitationList.size(); i++)
    {
        if (_invitationList[i] == user)
        {
            _invitationList.erase(_invitationList.begin() + i);
            return;
        }
    }
}

std::vector<std::string> channel::getInvitationList()
{
    return _invitationList;
}

std::time_t channel::getCreation() 
{
    return _creationTime;
}

void channel::changeTopic(std::string newTopic, std::string author)
{
    if (_weCanChangeTopic == false)
    {
        std::string message = ERR_CHANOPRIVSNEEDEDD(author, _channelName);
        for (unsigned int j = 0; j < _channelClients.size(); j++)
            send(_channelClients[j]->getFd(), message.c_str(), message.size(), 0);
        return;
    }
    _topic = newTopic;
    std::string message = RPL_TOPIC(author, _channelName, newTopic);
    for (unsigned int j = 0; j < _channelClients.size(); j++)
        send(_channelClients[j]->getFd(), message.c_str(), message.size(), 0);
}

void channel::inviteInGame(client *author, std::string user, std::string game)
{
    _bot->addNewInvitation(author, user, game);
}

void channel::acceptInGame(client *author, std::string user, std::string game)
{
    std::string userName = "";
    for (unsigned int i = 0; i < _channelClients.size(); i++)
    {
        if (user == _channelClients[i]->getNick())
            userName = _channelClients[i]->getUser();
    }
    _bot->acceptInvitation(author, userName, game);
}

void channel::launchRussianRoulette(client *author)
{
    _bot->russianRoulette(author, NULL);
}

void channel::playMorpion(client *author, int nb)
{
    std::vector<client*> isPlaying = _bot->getClientPlayMoprion();
    for (size_t i = 0; i < isPlaying.size(); i++)
    {
        if (isPlaying[i] == author)
        {
            _bot->morpionGame(author, nb);
            return;
        }
    }
    _bot->sendMessage("You are not playing morpion");
}

void channel::morpionWithBot(client *author)
{
    std::vector<client *> clients = _bot->getClientPlayMoprion();
    for (size_t i = 0; i < clients.size(); i++)
    {
        if (clients[i] == author)
        {
            _bot->sendMessage("You are already playing with someone");
            return;
        }
    }
    _bot->createMorpion(author, NULL);
}