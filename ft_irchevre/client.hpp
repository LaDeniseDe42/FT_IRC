/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:09:57 by akastler          #+#    #+#             */
/*   Updated: 2024/04/09 14:33:22 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "includes.hpp"

class client
{
private:
    int _fd;
    std::string _nick;
    std::string _user;
    std::string _realName;
    std::string _buffer;
    bool _registered;
    bool _nickSet;
    bool _userSet;
    bool _passwordSet;
    std::vector<std::string> _channels;
    std::vector<std::string> _invitations;
    int _nb_insults;
    int _pv;
    bool _havePokemon;
    std::string _pokemonName;
    pokemon *_pokemon;
    bool _isInJail;
    
public:
    client(int fd);
    ~client();

    void clearBuffer();
    std::string readBuffer();
    void writeBuffer(std::string str);
    void setNick(std::string nick);
    void setUser(std::string user);
    void setRealName(std::string realName);
    void setPassword();
    bool getPasswordSet();
    bool Registered();
    std::string const & getNick();
    std::string const & getUser();
    std::string const & getRealName();
    int const & getFd();
    std::vector<std::string> getChannels();
    void addChannel(std::string channel);
    void removeChannel(std::string channel);
    bool sendRegister;
    bool disconnect;
    std::string reasonDisconnect;
    void addInvitation(std::string channelWhoInvite);
    void removeNbInsults();
    void addNbInsults();
    int const & getNbInsults();

    void setIsInJail(bool isInJail);
    bool const & getIsInJail();
    void decreasePV(int pv);
    void increasePV(int pv);
    int const & getPv();
    void setPv(int pv);

    void catchPokemon(std::string channelName);
    std::string const & getPokemonName();
    bool havePokemon();
    pokemon *getPokemon();
    void clearPokemon();
};