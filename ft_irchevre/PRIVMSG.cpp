/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:56:00 by akastler          #+#    #+#             */
/*   Updated: 2024/04/11 11:51:09 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void server::privateMsg(std::istringstream &iss, client *author)
{
    std::string target;
    std::string message;
    iss >> target;
    std::string temp;
    iss >> message;
    std::getline(iss, temp);
    message += temp;
    if (author->Registered() == false)
    {
        sendMessage(ERR_NOTREGISTERED(author->getNick()), author->getFd());
        return;
    }
    if (target.size() <= 0 || message.size() <= 0 || target[0] == ':')
    {
        sendMessage(ERR_NORECIPIENT(author->getNick()), author->getFd());
        return;
    }
    if (message[0] == ':')
        message.erase(0, 1);
    if (target[0] == '#')
    {
        for (size_t i = 0; i < _channels.size(); i++)
        {
            std::string chanName = _channels[i]->getChannelName();
            if (chanName == target)
            {
                std::vector<client *> clients = _channels[i]->getChannelClients();
                int ok = 0;
                for (unsigned int i = 0; i < clients.size(); i++)
                {
                    if (clients[i]->getNick() == author->getNick())
                    {
                        ok = 1;
                        break;
                    }
                }
                if (ok == 0)
                {
                    sendMessage(ERR_CANNOTSENDTOCHAN(author->getNick(), chanName), author->getFd());
                    return;
                }
                std::string word;
                std::istringstream iss(message);
                while (iss >> word)
                    _channels[i]->useBotInsult(word, author, 1);
                for (size_t j = 0; j < _channels[i]->getChannelClients().size(); j++)
                {
                    if (clients[j]->getNick() == author->getNick())
                        continue;
                    sendMessage(PRIVMSG(author->getNick(), chanName, message), clients[j]->getFd());
                }
                if (message[0] == '!')
                    botCommand(message, author, _channels[i]);
            }
        }
        return;
    }
    else
    {
        for (size_t i = 0; i < _clients.size(); i++)
        {
            if (_clients[i]->getNick() == target)
            {
                sendMessage(PRIVMSG(author->getNick(), _clients[i]->getNick(), message), _clients[i]->getFd());
                return;
            }
        }
        sendMessage(ERR_NOSUCHNICK(author->getNick(), target), author->getFd());
        sendMessage(PART(author->getNick(), author->getUser(), target, "nothing"), author->getFd());
    }
}

void server::botCommand(std::string message, client *author, channel *chan)
{
    std::istringstream iss(message);
    std::string command;
    iss >> command;
    if (command != "!help" && command != "!joke" && command != "!story" && command != "!heal" && command != "!pv"
        && command != "!BHEE" && command != "!hell" && command != "!HELL" && command != "!firework" && command != "!hurt"
        && command != "!playMorpion" && command != "!morpion" && command != "!accept" && command != "!launchRR"
        && command != "!catch" && command != "!pokeduel")
    {
        sendMessage(PRIVMSG(("Bot" + chan->getChannelName()), chan->getChannelName(), "the command you entered does not exist"), author->getFd());
        return;
    }
    if (command == "!help")
        chan->useBotHelp();
    else if (command == "!catch")
    {
        if (chan->getChannelName() == "#fire" || chan->getChannelName() == "#water" || chan->getChannelName() == "#grass")
            author->catchPokemon(chan->getChannelName());
        else
            sendMessage(PRIVMSG(("Bot" + chan->getChannelName()), chan->getChannelName(), "You can't catch pokemon in this channel, try to find good the place"), author->getFd());
    }
    else if (command == "!pokeduel")
    {
        std::string nickToInvite;
        iss >> nickToInvite;
        if (nickToInvite.size() <= 0)
        {
            sendMessage(PRIVMSG(("Bot" + chan->getChannelName()), chan->getChannelName(), "You must enter a nickname"), author->getFd());
            return;
        }
        chan->inviteInGame(author, nickToInvite, "pokeduel");
    }
    else if (command == "!joke")
        chan->useBotJokeStory("joke");
    else if (command == "!story")
        chan->useBotJokeStory("story");
    else if (command == "!pv")
        chan->useSeePv(author);
    else if (command == "!heal")
    {
        if (chan->getChannelName() == "#doctor")
            chan->useBotHeal(author, 1);
        else
            chan->useBotHeal(author, 0);
    }
    else if (command == "!hell" || command == "!HELL")
        chan->useBotHell();
    else if (command == "!BHEE")
        chan->useBotBhee();
    else if (command == "!firework")
        chan->useBotFirework();
    else if (command == "!hurt")
    {
        std::string user;
        iss >> user;
        chan->useHurtClient(author, user);
    }
    else if (command == "!playMorpion")
    {
        std::string playingWith;
        iss >> playingWith;
        if (playingWith.size() > 0)
            chan->inviteInGame(author, playingWith, "morpion");
        else
            chan->morpionWithBot(author);
    }
    else if (command == "!morpion")
    {
        std::string nb;
        iss >> nb;
        if (nb.size() == 1 && std::isdigit(nb[0]) && nb[0] != '0')
        {
            int number = nb[0] - '0';
            chan->playMorpion(author, number);
        }
        else
            sendMessage(PRIVMSG(("Bot" + chan->getChannelName()), chan->getChannelName(), "You must enter a number between 1 and 9"), author->getFd());
    }
    else if (command == "!launchRR")
    {
        std::string playingWith;
        iss >> playingWith;
        if (playingWith.size() > 0)
            chan->inviteInGame(author, playingWith, "RR");
        else
            chan->launchRussianRoulette(author);
    }
    else if (command == "!accept")
    {
        std::string game;
        iss >> game;
        std::string user;
        iss >> user;
        if (game.size() <= 0 || user.size() <= 0)
        {
            std::string msg = PRIVMSG(author->getNick(), chan->getChannelName(), "You must enter a game and a user");
            send(author->getFd(), msg.c_str(), msg.size(), 0);
            return;
        }
        chan->acceptInGame(author, user, game);
    }
}