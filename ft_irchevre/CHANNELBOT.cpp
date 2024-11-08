/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CHANNELBOT.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:58:24 by qdenizar          #+#    #+#             */
/*   Updated: 2024/04/09 14:37:04 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"


void channel::useBotInsult(std::string message, client *author, int z)
{
    if (_bot->thisIsInsult(message) == true)
    {
        if (z == 1)
        {
            author->addNbInsults();
            z++;
        }
        if (author->getNbInsults() == 1)
        {
            std::string msgI = "Hey, pas d'insultes ici ! [" + message + "] est un mot interdit";
            std::string msg = PRIVMSG(_bot->getBotName(), _channelName, msgI);
            for (size_t i = 0; i < _channelClients.size(); i++)
            {
                send(_channelClients[i]->getFd(), msg.c_str(), msg.size(), 0);
            }
        }
        if (author->getNbInsults() == 2)
        {
            std::string msgI = "La prochaine fois tu vas le regretter.. [" + message + "] est un mot interdit";
            std::string msg = PRIVMSG(_bot->getBotName(), _channelName, msgI);
            for (size_t i = 0; i < _channelClients.size(); i++)
            {
                send(_channelClients[i]->getFd(), msg.c_str(), msg.size(), 0);
            }
        }
        if (author->getNbInsults() == 3)
        {
            std::string msgI = "This is not a democraty anymore ! GET OUT";
            std::string msg = PRIVMSG(_bot->getBotName(), _channelName, msgI);
            std::string msg2 = PRIVMSG(_bot->getBotName(), _channelName, "and take it for what it's worth ! *slap*");
            for (size_t i = 0; i < _channelClients.size(); i++)
            {
                send(_channelClients[i]->getFd(), msg.c_str(), msg.size(), 0);
                send(_channelClients[i]->getFd(), msg2.c_str(), msg2.size(), 0);
            }
            author->decreasePV(1);
            leaveChannel(author, "3 insults");

        }
    }
}

void channel::useBotBhee()
{
    _bot->botBhee();
}

void channel::useBotJokeStory(std::string type)
{
    _bot->upJokeOrStory(type);
}

void channel::setBot(std::string botName)
{
    
    _bot = new bot(botName, this);
}

void channel::useBotHelp()
{
    _bot->dispenseHelp();
}

void channel::useHurtClient(client *author, std::string user)
{
    int res =0;

    res = _bot->hurtClient(user, author);
    return;
   
}

void channel::useBotFirework()
{
    _bot->firework();
}

void channel::useBotHeal(client *author, int yesOrNo)
{
    _bot->botHeal(author, yesOrNo);
    return;
}

void channel::useBotHell()
{
    _bot->botHell();
    return;
}

void channel::useSeePv(client *author)
{
    _bot->seePv(author);
    return;
}

