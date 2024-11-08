/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:32:39 by qdenizar          #+#    #+#             */
/*   Updated: 2024/04/12 10:12:46 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

bot::bot(std::string botName, channel *channel)
{
    _botName = botName;
    _channel = channel;
    _nbJoke = 0;
    _nbStory = 0;
    
    setInsults();
}

bot::~bot()
{
    for (unsigned int i = 0; i < _morpions.size(); i++)
        delete (_morpions[i]);
    _morpions.clear();
}

void bot::setBot(std::string botName)
{
    _botName = botName;
}

std::string bot::getBotName()
{
    return (_botName);
}

void bot::sendMessage(std::string message)
{
    std::string msg = PRIVMSG(getBotName(), _channel->getChannelName(), message);
    for (size_t i = 0; i < _channel->getChannelClients().size(); i++)
    {
        send(_channel->getChannelClients()[i]->getFd(), msg.c_str(), msg.size(), 0);
    }
}
void bot::botBhee()
{
    sendMessage(MG0);
    sendMessage(MG1);
    sendMessage(MG2);
    sendMessage(MG3);
    sendMessage(MG4);
    sendMessage(MG5);
    sendMessage(MG6);
    sendMessage(MG7);
    sendMessage(MG8);
    sendMessage(MG9);
    sendMessage(MG10);
    sendMessage(MG11);
    sendMessage(MG12);
    sendMessage(MG13);
    sendMessage(MG14);
}

void bot::setInsults()
{
    std::ifstream file("juron_conf.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
            _insults.push_back(line);
        file.close();
    }
    else
        std::cerr << "Error: juron_conf.txt not found" << std::endl;
}

bool bot::thisIsInsult(std::string msg)
{
    for (size_t i = 0; i < _insults.size(); i++)
    {
        if (msg == _insults[i])
            return (true);
    }
    return (false);
}

void bot::upJokeOrStory(std::string type)
{
    if (type == "joke")
    {
        if (_nbJoke >= 4)
        {
            _nbJoke = 0;
            joke(_nbJoke);
            return;
        }
        _nbJoke++;
        joke(_nbJoke);
    }
    else if (type == "story")
    {
        if (_nbStory >= 4)
        {
            _nbStory = 0;
            story(_nbStory);
            return;
        }
        _nbStory++;
        story(_nbStory);
    }
}

void bot::dispenseHelp()
{
        std::string help = "How irssi works:";
        sendMessage(help);
        help = "    0. you must be operator for execute some commands";
        sendMessage(help);
        help = "    1. You can join a channel by typing /join #channelname,#channelname2,...";
        sendMessage(help);
        help = "    2. You can leave a channel by typing /part #channelname,#channelname2,...";
        sendMessage(help);
        help = "    3. You can send a private message by typing /msg nickname message";
        sendMessage(help);
        help = "    4. You can change your nickname by typing /nick newNick";
        sendMessage(help);
        help = "    5. You can change the topic of a channel by typing /topic #channelname newtopic";
        sendMessage(help);  
        help = "    6. You can invite someone to a channel by typing /invite nickname #channelname";
        sendMessage(help);
        help = "    7. You can kick someone from a channel by typing /kick #channelname nickname reason";
        sendMessage(help);
        help = "    8. you can exchange files:";
        sendMessage(help);
        help = "        ->Send files by typing /dcc send <nick> <path/to/file(start at /home)>";
        sendMessage(help);
        help = "        ->Get files by tiping /dcc get <nick> -> basic get in /home (changebasic path with /set dcc_download_path /path/to/were/you/want)";
        sendMessage(help);
        help = "";
        sendMessage(help);
        help = "How bot works:";
        sendMessage(help);
        help = "    1. You can show this message by typing !help";
        sendMessage(help);
        help = "    2. You can ask for a joke by typing !joke";
        sendMessage(help);
        help = "    3. You can ask for a story by typing !story";
        sendMessage(help);
        help = "    4. Take care about your langage";
        sendMessage(help);
        help = "    5. You can hurt someone by typing !hurt nickname";
        sendMessage(help);
        help = "    5. You can trigger a firework by typing !firework";
        sendMessage(help);
        help = "    4. You can play morpion with the bot by typing !playMorpion";
        sendMessage(help);
        help = "    5. You can play morpion with someone by typing !playMorpion nickname";
        sendMessage(help);
        help = "    6. You can play russian roulette with the bot by typing !launchRR";
        sendMessage(help);
        help = "    7. You can play russian roulette with someone by typing !launchRR nickname";
        sendMessage(help);
        help = "    8. You can heal yourself by typing !heal";
        sendMessage(help);
        help = "    9. You can see your pv by typing !pv";
        sendMessage(help);
        help = "    10. You can catch a pokemon by typing !catch";
        sendMessage(help);
        help = "    11. You can play pokeduel with someone by typing !pokeduel nickname";
        sendMessage(help);
        help = "    bis. There exists much commands but you have to discover them by yourself !";
        sendMessage(help);
        
}

void bot::joke(int nb)
{
    if (nb == 0)
    {
        std::string joke = "Why do programmers prefer dark mode?";
        sendMessage(joke);
        joke = "Because light attracts bugs!";
        sendMessage(joke);
    }
    else if (nb == 1)
    {
        std::string joke = "I told my wife she was drawing her eyebrows too high. She looked surprised.";
        sendMessage(joke);
    }
    else if (nb == 2)
    {
        std::string joke = "I'm reading a book on anti-gravity. It's impossible to put down!";
        sendMessage(joke);
    }
    else if (nb == 3)
    {
        std::string joke = "Why was the programmer cold?";
        sendMessage(joke);
        joke = "Because he left his Windows open!";
        sendMessage(joke);
    }
    else if (nb == 4)
    {
        std::string joke = "Why did the math book look sad?";
        sendMessage(joke);
        joke = "Because it had too many problems!";
        sendMessage(joke);
    }
}

void bot::story(int nb)
{
    if (nb == 0)
    {
        std::string story = "Ada Lovelace, born in 1815, is often considered the world's first computer programmer.";
        sendMessage(story);
        story = "She wrote the first algorithm intended to be processed by a machine, for Charles Babbage's Analytical Engine.";
        sendMessage(story);
    }
    else if (nb == 1)
    {
        std::string story = "In the 1950s, assembly languages were developed, allowing programmers to write instructions using mnemonic codes rather than binary machine code. " ;
        sendMessage(story);
        story = "This made programming more accessible and efficient.";
        sendMessage(story);
    }
    else if (nb == 2)
    {
        std::string story = "In the 1970s, Vinton Cerf and Robert Kahn developed the TCP/IP protocol suite, laying the foundation for the modern internet. ";
        sendMessage(story);
        story = " TCP/IP standardized the way data is transmitted across networks and enabled the creation of the global network we use today.";
        sendMessage(story);
    }
    else if (nb == 3)
    {
        std::string story = "The introduction of the Microsoft Disk Operating System (MS-DOS) in the early 1980s played a significant role in popularizing personal computers.";
        sendMessage(story);
        story = "MS-DOS provided a command-line interface for interacting with the computer and paved the way for the development of the Windows operating system.";
        sendMessage(story);
    }
    else if (nb == 4)
    {
        std::string story = "Once upon a time, in a faraway land, there was a bot who told stories.";
        sendMessage(story);
    }
}

void bot::addNewInvitation(client *author, std::string user, std::string game)
{
    client *invited = NULL;
    for (size_t i = 0; i < _channel->getChannelClients().size(); i++)
    {
        if (_channel->getChannelClients()[i]->getNick() == user)
        {
            invited = _channel->getChannelClients()[i];
            break;
        }
    }
    if (game != "RR" && game != "morpion" && game != "pokeduel")
    {
        std::string msg = PRIVMSG(_botName, _channel->getChannelName(), "This game does not exist !");
        send(author->getFd(), msg.c_str(), msg.size(), 0);
        return;
    }
    else if (game == "morpion")
    {
        for (size_t i = 0; i < _clientPlayingMorpion.size(); i++)
        {
            if (_clientPlayingMorpion[i]->getUser() == author->getUser())
            {
                std::string msg = PRIVMSG(_botName, _channel->getChannelName(), "You are already playing morpion !");
                send(author->getFd(), msg.c_str(), msg.size(), 0);
                return;
            }
        }
    }
    if (invited)
    {
        user = invited->getUser();
        if (inviteChecker(author, invited, game) == true)
            return;
        std::string msg = PRIVMSG(_botName, _channel->getChannelName(), ("Hey " + invited->getNick() + ", " + author->getNick() + " wants to play " + game + " with you !"));
        send(invited->getFd(), msg.c_str(), msg.size(), 0);
        if (_invites.find(user) == _invites.end())
        {
            std::map<std::string, std::vector<std::string> > newMap;
            std::vector<std::string> newVector;
            newVector.push_back(author->getUser());
            newMap[game] = newVector;
            _invites[user] = newMap;
        }
        else
        {
            if (_invites[user].find(game) == _invites[user].end())
            {
                std::vector<std::string> newVector;
                newVector.push_back(author->getUser());
                _invites[user][game] = newVector;
            }
            else
                _invites[user][game].push_back(author->getUser());
        }
    }
    else
    {
        std::string msg = PRIVMSG(_botName, _channel->getChannelName(), "This user is not in the channel !");
        send(author->getFd(), msg.c_str(), msg.size(), 0);
    }
}

bool bot::inviteChecker(client *author, client *invited, std::string game)
{
    std::string user = invited->getUser();
    if (_invites.find(user) != _invites.end())
    {
        if (_invites[user].find(game) != _invites[user].end())
        {
            for (size_t i = 0; i < _invites[user][game].size(); i++)
            {
                if (_invites[user][game][i] == author->getUser())
                {
                    std::string msg = PRIVMSG(_botName, _channel->getChannelName(), ("You have already invited " + invited->getNick() + " to play " + game + " !"));
                    send(author->getFd(), msg.c_str(), msg.size(), 0);
                    return (true);
                }
            }
        }
    }
    //check if the author received an invitation from the invited
    if (_invites.find(author->getUser()) != _invites.end())
    {
        if (_invites[author->getUser()].find(game) != _invites[author->getUser()].end())
        {
            for (size_t i = 0; i < _invites[author->getUser()][game].size(); i++)
            {
                if (_invites[author->getUser()][game][i] == user)
                {
                    std::string msg = PRIVMSG(_botName, _channel->getChannelName(), ("You have already received an invitation from " + invited->getNick() + " to play " + game + " !"));
                    send(author->getFd(), msg.c_str(), msg.size(), 0);
                    return (true);
                }
            }
        }
    }
    return (false);
}

void bot::acceptInvitation(client *author, std::string user, std::string game)
{
    if (game == "morpion")
    {
        for (size_t i = 0; i < _clientPlayingMorpion.size(); i++)
        {
            if (_clientPlayingMorpion[i]->getUser() == author->getUser())
            {
                std::string msg = PRIVMSG(_botName, _channel->getChannelName(), "You are already playing morpion !");
                send(author->getFd(), msg.c_str(), msg.size(), 0);
                return;
            }
        }
    }
    if (_invites.find(author->getUser()) != _invites.end())
    {
        if (_invites[author->getUser()].find(game) != _invites[author->getUser()].end())
        {
            for (size_t i = 0; i < _invites[author->getUser()][game].size(); i++)
            {
                if (_invites[author->getUser()][game][i] == user)
                {
                    _invites[author->getUser()][game].erase(_invites[author->getUser()][game].begin() + i);
                    client *invited = NULL;
                    for (size_t j = 0; j < _channel->getChannelClients().size(); j++)
                    {
                        if (_channel->getChannelClients()[j]->getUser() == user)
                        {
                            invited = _channel->getChannelClients()[j];
                            break;
                        }
                    }
                    if (invited)
                    {
                        std::string msg = PRIVMSG(_botName, _channel->getChannelName(), (author->getNick() + " has accepted the invitation from " + user + " to play " + game + " !"));
                        send(author->getFd(), msg.c_str(), msg.size(), 0);
                        msg = PRIVMSG(_botName, _channel->getChannelName(), (author->getNick() + " has accepted your invitation to play " + game + " !"));
                        send(invited->getFd(), msg.c_str(), msg.size(), 0);
                        if (game == "RR")
                            russianRoulette(author, invited);
                        else if (game == "morpion")
                            createMorpion(author, invited);
                        else if (game == "pokeduel")
                            pokeduel(author, invited);
                    }
                    else
                    {
                        std::string msg = PRIVMSG(_botName, _channel->getChannelName(), "This user is not in the channel !");
                        send(author->getFd(), msg.c_str(), msg.size(), 0);
                    }
                    return ;
                }
            }
        }
    }

    std::string msg = PRIVMSG(_botName, _channel->getChannelName(), "You have not received an invitation from this user to play this game !");
    send(author->getFd(), msg.c_str(), msg.size(), 0);
}

void bot::morpionGame(client *author, int nb)
{
    for (size_t i = 0; i < _morpions.size(); i++)
    {
        if (_morpions[i]->getUser1() == author->getUser() || _morpions[i]->getUser2() == author->getUser())
        {
            _morpions[i]->playGame(author, nb);
            if (_morpions[i]->gameFinished)
            {
                for (size_t j = 0; j < _clientPlayingMorpion.size(); j++)
                {
                    if (_morpions[i]->getUser1() == _clientPlayingMorpion[j]->getUser() || _morpions[i]->getUser2() == _clientPlayingMorpion[j]->getUser())
                    {
                        _clientPlayingMorpion.erase(_clientPlayingMorpion.begin() + j);
                        j = j - 1;
                    }
                }
                delete _morpions[i];
                _morpions.erase(_morpions.begin() + i);
            }
            return;
        }
    }
    std::string msg = PRIVMSG(_botName, _channel->getChannelName(), "You have not started a game of morpion !");
    send(author->getFd(), msg.c_str(), msg.size(), 0);
}

void bot::pokeduel(client *author, client *inviter)
{
    if (author->getPokemon() == NULL || inviter->getPokemon() == NULL)
    {
        std::string msg = PRIVMSG(_botName, _channel->getChannelName(), "You or the person you want to duel with does not have a pokemon !");
        send(author->getFd(), msg.c_str(), msg.size(), 0);
        send(inviter->getFd(), msg.c_str(), msg.size(), 0);
        return;
    }
    else if (author->getPokemon()->getPv() <= 0 || inviter->getPokemon()->getPv() <= 0)
    {
        std::string msg = PRIVMSG(_botName, _channel->getChannelName(), "You or the person you want to duel with has a pokemon with 0 pv !");
        send(author->getFd(), msg.c_str(), msg.size(), 0);
        send(inviter->getFd(), msg.c_str(), msg.size(), 0);
        return;
    }
    sendMessage("Duel between " + author->getPokemonName() + " and " + inviter->getPokemonName() + " !");
    sendAscii(author->getPokemonName());
    sendAscii("VS");
    sendAscii(inviter->getPokemonName());
    battleStart(author, inviter);
    
    
}

void bot::battleStart(client *author, client *target)
{
    
    std::string msg = "Let's fight !";
    sendMessage(msg);
    std::srand(std::time(NULL));
    int random = std::rand() % 2;
    while (author->getPokemon()->getPv() > 0 && target->getPokemon()->getPv() > 0)
    {
        if (random == 0)
        {
            std::string msg = B + author->getNick() + W + " attack " + R +target->getNick() + W + " with " + B + author->getPokemon()->getName() + W;
            sendMessage(msg);
            author->getPokemon()->getDeg(target->getPokemon(), this);
            random = 1;
        }
        else
        {
            std::string msg = R + target->getNick() + W + " attack " + B + author->getNick() +  W + " with " + R + target->getPokemon()->getName() + W;
            sendMessage(msg);
            target->getPokemon()->getDeg(author->getPokemon(), this);
            random = 0;
        }
    }
    if (author->getPokemon()->getPv() <= 0)
    {
        std::string msg = B + author->getNick() + " " + author->getPokemonName() + W + " die and lost the fight";
        author->clearPokemon();
        sendMessage(msg);
    }
    else if (target->getPokemon()->getPv() <= 0)
    {
        std::string msg = R + target->getNick() + " " + target->getPokemonName() + W + " die and lost the fight";
        target->clearPokemon();
        sendMessage(msg);
    }
    
}

void bot::createMorpion(client *author, client *invited)
{
    _morpions.push_back(new morpion(_channel, this, author, invited));
    _clientPlayingMorpion.push_back(author);
    if (invited)
        _clientPlayingMorpion.push_back(invited);
}


void bot::russianRoulette(client *launcher, client *secondPlayer)
{
    std::srand(std::time(0));
    if (secondPlayer)
    {
        int rdm = std::rand() % 2;
        bool chamber[6] = {false, false, false, false, false, false};
        int random =  std::rand() % 6;
        chamber[random] = true;
        client *players[2] = {launcher, secondPlayer};
        for (int actualChamber = 0; actualChamber < 6; actualChamber++)
        {
            if (chamber[actualChamber] == true)
            {
                std::string msg = players[rdm]->getNick() + " try to play russian roulette, but the bullet was in the chamber";
                sendMessage(msg);
                players[rdm]->decreasePV(INT_MAX);
                return;   
            }
            else
            {
                std::string msg = players[rdm]->getNick() + " try to play russian roulette, but the chamber was empty";
                sendMessage(msg);
                if(rdm == 0)
                    rdm = 1;
                else
                    rdm = 0;
            }
            
        }
    }
    else
    {
        int random =  std::rand() % 6;
        if (random == 0)
        {
            launcher->decreasePV(INT_MAX);
            std::string msg = launcher->getNick() + " try to play russian roulette, but the bullet was in the chamber";
            sendMessage(msg);
            return;
        }
        else
        {
            std::string msg = launcher->getNick() + " try to play russian roulette, but the chamber was empty";
            sendMessage(msg);
            return;
        }
    }
}


int bot::hurtClient(std::string nick, client *author)
{   
    std::srand(std::time(0));
    int random =  std::rand() % 3;
    if (random == 0)
    {
        author->decreasePV(1);
        std::string msg = author->getNick() + " try to punch " + nick + " in the face, but you miss and you hurt yourself";
        sendMessage(msg);
        return 2;
    }        
    for (size_t i = 0; i < _channel->getChannelClients().size(); i++)
    {
        if (_channel->getChannelClients()[i]->getNick() == nick)
        {
            if (random == 1)
            {
                _channel->getChannelClients()[i]->decreasePV(1);
                std::string msg = author->getNick() + " punch " + nick + " in the face in front of everyone";
                sendMessage(msg);
                std::string msg1 = getBotName() + " t " + author->getNick() + " and say : You are a bad person ! Dont do it again or...";
                author->addNbInsults();
                return 0;
                break;
            }
            else if (random == 2)
            {
                _channel->getChannelClients()[i]->decreasePV(2);
                std::string msg1 = author->getNick() + " punch " + nick + " in the face when " + getBotName() + " look away";
                sendMessage(msg1);
                return 0;
                break;
            }
        }
    }
    return 1;
}

void bot::firework()
{
    std::srand(std::time(0));
    int random =  std::rand() % 10;
    int random2 =  std::rand() % _channel->getChannelClients().size();
    if (random == 1)
    {
        std::string msg = "Unlucky, firework triggers a huge fire and " + _channel->getChannelClients()[random2]->getNick() + " is burned alive with all his family";
        sendMessage(msg);
        _channel->getChannelClients()[random2]->decreasePV(5);
    }
    if (random == 2 || random == 3)
    {
        std::string msg = "Unfortunatly, " + _channel->getChannelClients()[random2]->getNick() + " tryed to play with fireworks and one of them exploded in his right hand";
        sendMessage(msg);
        _channel->getChannelClients()[random2]->decreasePV(2);
    }
    else
    {
        sendMessage(FIREWORK1);
        sendMessage(FIREWORK2);
        sendMessage(FIREWORK3);
        sendMessage(FIREWORK4);
        sendMessage(FIREWORK5);
        sendMessage(FIREWORK6);
        sendMessage(FIREWORK7);
        sendMessage(FIREWORK8);
        sendMessage(FIREWORK9);
        sendMessage(FIREWORK10);
        sendMessage(FIREWORK11);
        sendMessage(FIREWORK12);
        sendMessage(FIREWORK13);
    }
}

void bot::sendAscii(std::string what)
{
    if (what == "NURSE")
    {
        sendMessage(NURSE1);
        sendMessage(NURSE2);
        sendMessage(NURSE3);
        sendMessage(NURSE4);
        sendMessage(NURSE5);
        sendMessage(NURSE6);
        sendMessage(NURSE7);
        sendMessage(NURSE8);
        sendMessage(NURSE9);
        sendMessage(NURSE10);
        sendMessage(NURSE11);
        sendMessage(NURSE12);
        sendMessage(NURSE13);
        sendMessage(NURSE14);
        sendMessage(NURSE15);
    }
    else if (what == "SATAG")
    {
        sendMessage(SATAG1);
        sendMessage(SATAG2);
        sendMessage(SATAG3);
        sendMessage(SATAG4);
        sendMessage(SATAG5);
        sendMessage(SATAG6);
        sendMessage(SATAG7);
        sendMessage(SATAG8);
        sendMessage(SATAG9);
        sendMessage(SATAG10);
        sendMessage(SATAG11);
        sendMessage(SATAG12);
        sendMessage(SATAG13);
        sendMessage(SATAG14);
        sendMessage(SATAG15);
        sendMessage(SATAG16);
        sendMessage(SATAG17);
        sendMessage(SATAG18);
        sendMessage(SATAG19);
        sendMessage(SATAG20);
        sendMessage(SATAG21);
        sendMessage(SATAG22);
        sendMessage(SATAG23);
        sendMessage(SATAG24);
        sendMessage(SATAG25);
        sendMessage(SATAG26);
        sendMessage(SATAG27);
        sendMessage(SATAG28);
        sendMessage(SATAG29);
        sendMessage(SATAG30);
    }
    else if (what == "CARA" || what == "Squirtle")
    {
        sendMessage(CARA1);
        sendMessage(CARA2);
        sendMessage(CARA3);
        sendMessage(CARA4);
        sendMessage(CARA5);
        sendMessage(CARA6);
        sendMessage(CARA7);
        sendMessage(CARA8);
        sendMessage(CARA9);
        sendMessage(CARA10);
        sendMessage(CARA11);
        sendMessage(CARA12);
        sendMessage(CARA13);
        sendMessage(CARA14);
        sendMessage(CARA15);
        sendMessage(CARA16);
        sendMessage(CARA17);
        sendMessage(CARA18);
        sendMessage(CARA19);
        sendMessage(CARA20);
        sendMessage(CARA21);
        sendMessage(CARA22);
        sendMessage(CARA23);
        sendMessage(CARA24);
    }
    else if (what == "BULB" || what == "Bulbasaur")
    {
        sendMessage(BULB1);
        sendMessage(BULB2);
        sendMessage(BULB3);
        sendMessage(BULB4);
        sendMessage(BULB5);
        sendMessage(BULB6);
        sendMessage(BULB7);
        sendMessage(BULB8);
        sendMessage(BULB9);
        sendMessage(BULB10);
        sendMessage(BULB11);
        sendMessage(BULB12);
        sendMessage(BULB13);
        sendMessage(BULB14);
        sendMessage(BULB15);
        sendMessage(BULB16);
        sendMessage(BULB17);
        sendMessage(BULB18);
        sendMessage(BULB19);
        sendMessage(BULB20);
    }
    else if (what == "CHAR" || what == "Charmander")
    {
        sendMessage(CHAR1);
        sendMessage(CHAR2);
        sendMessage(CHAR3);
        sendMessage(CHAR4);
        sendMessage(CHAR5);
        sendMessage(CHAR6);
        sendMessage(CHAR7);
        sendMessage(CHAR8);
        sendMessage(CHAR9);
        sendMessage(CHAR10);
        sendMessage(CHAR11);
        sendMessage(CHAR12);
        sendMessage(CHAR13);
        sendMessage(CHAR14);
        sendMessage(CHAR15);
        sendMessage(CHAR16);
        sendMessage(CHAR17);
        sendMessage(CHAR18);
        sendMessage(CHAR19);
        sendMessage(CHAR20);
        sendMessage(CHAR21);
        sendMessage(CHAR22);
        sendMessage(CHAR23);
        sendMessage(CHAR24);   
    }
    else if (what == "VS")
    {
        sendMessage(VS1);
        sendMessage(VS2);
        sendMessage(VS3);
        sendMessage(VS4);
        sendMessage(VS5);
        sendMessage(VS6);
    }
    
}

void bot::botHell()
{
    sendAscii("SATAG");
}

void bot::botHeal(client *author, int yesOrNo)
{
    if (yesOrNo == 1)
    {
        if (author->getPv() >= 5)
        {
            std::string msg = "You are already full life";
            sendMessage(msg);
            return;
        }
        author->increasePV(1);
        std::string msg = getBotName() + " heal you <3";
        sendMessage(msg);
        sendAscii("NURSE");
    }
    else
    {
        std::string msg = "You cannot be heal here. Go to find a doctor";
        sendMessage(msg);
    }
}


void bot::seePv(client *author)
{
    int nbpv = author->getPv();
    std::stringstream ss;
    ss << nbpv;
    std::string nbPv = ss.str();
    std::string msg = author->getNick() + " have " + nbPv + " pv";
    sendMessage(msg);
}

std::vector<client *> bot::getClientPlayMoprion()
{
    return(_clientPlayingMorpion);
}
