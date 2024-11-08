/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:18:53 by akastler          #+#    #+#             */
/*   Updated: 2024/04/09 14:31:17 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

client::client(int fd) : _fd(fd)
{
    _nick = "unknown";
    _user = "unknown";
    _realName = "unknown";
    _buffer = "";
    _nb_insults = 0;
    _registered = false;
    _nickSet = false;
    _userSet = false;
    _passwordSet = false;
    sendRegister = false;
    disconnect = false;
    reasonDisconnect = "";
    _isInJail = false;
    _pv = 5;
    _havePokemon = false;
    _pokemonName = "";
    
}

client::~client()
{
    std::cout << "\033[1;31mClient \033[38;2;255;165;0m" << _nick << " \033[1;31mdisconnected\033[0m" << std::endl;
    
    close(_fd);
    if (_havePokemon == true)
        delete _pokemon;
}

void client::clearBuffer()
{
    _buffer.clear();
}

void client::addInvitation(std::string channelWhoInvite)
{
    _invitations.push_back(channelWhoInvite);
}

void client::removeNbInsults()
{
    _nb_insults = 0;
}

void client::addNbInsults()
{
    _nb_insults++;
}

int const & client::getNbInsults()
{
    return _nb_insults;
}

void client::setIsInJail(bool isInJail)
{
    _isInJail = isInJail;
}

bool const & client::getIsInJail()
{
    return _isInJail;
}

void client::decreasePV(int pv)
{
    _pv -=  pv;
    if (_pv <= 0)
        disconnect = true;
}

void client::increasePV(int pv)
{
    _pv += pv;
}

int const & client::getPv()
{
    return _pv;
}

void client::setPv(int pv)
{
    _pv = pv;
}

std::string client::readBuffer()
{
    if (_buffer.find("\n") != std::string::npos)
    {
        std::string str = _buffer.substr(0, _buffer.find("\n") + 1);
        _buffer = _buffer.substr(_buffer.find("\n") + 1);
        return str;
    }
    return "";
}

void client::writeBuffer(std::string str)
{
    _buffer += str;
}

void client::setNick(std::string nick)
{
    _nick = nick;
    _nickSet = true;
}

void client::setUser(std::string user)
{
    _user = user;
    _userSet = true;
}

void client::setRealName(std::string realName)
{
    _realName = realName;
}

std::string const & client::getNick()
{
    return _nick;
}

std::string const &client::getUser()
{
    return _user;
}

std::string const &client::getRealName()
{
    return _realName;
}

int const & client::getFd()
{
    return _fd;
}

bool client::Registered()
{
    if (_nickSet == true && _userSet == true && _passwordSet == true)
    {
        _registered = true;
        sendRegister = true;
    }
    return _registered;
}

void client::setPassword()
{
    _passwordSet = true;
}

std::vector<std::string> client::getChannels()
{
    return _channels;
}

void client::addChannel(std::string channel)
{
    _channels.push_back(channel);
}

void client::removeChannel(std::string channel)
{
    for (unsigned int i = 0; i < _channels.size(); i++)
    {
        if (_channels[i] == channel)
        {
            _channels.erase(_channels.begin() + i);
            return;
        }
    }
}


bool client::getPasswordSet()
{
    return _passwordSet;
}

void client::catchPokemon(std::string channelName)
{
    if (_havePokemon == true)
    {
        std::string msg = PRIVMSG(("Bot" + channelName), channelName, ("Sorry, " + getNick() + " you already have a pokemon"));
        send(getFd(), msg.c_str(), msg.size(), 0);
        return;
    }
    if (channelName == "#fire")
    {
        _pokemonName = "Charmander";
        _pokemon = new pokemon(_pokemonName);
        _havePokemon = true;
    }
    else if (channelName == "#water")
    {
        _pokemonName = "Squirtle";
        _pokemon = new pokemon(_pokemonName);
        _havePokemon = true;
    }
    else if (channelName == "#grass")
    {
        _pokemonName = "Bulbasaur";
        _pokemon = new pokemon(_pokemonName);
        _havePokemon = true;
    }
    std::string caught = PRIVMSG(("Bot" + channelName), channelName, ("Congratulations " + getNick() + " you caught a " + _pokemonName + "!"));
    send(getFd(), caught.c_str(), caught.size(), 0);
}

std::string const & client::getPokemonName()
{
    return _pokemonName;
}

bool client::havePokemon()
{
    return _havePokemon;
}

pokemon *client::getPokemon()
{
    return (_pokemon);
}

void client::clearPokemon()
{
    delete _pokemon;
    _pokemon = NULL;
    _havePokemon = false;
    _pokemonName = "";
}