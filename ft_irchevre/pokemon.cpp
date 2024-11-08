/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pokemon.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:57:55 by qdenizar          #+#    #+#             */
/*   Updated: 2024/04/09 14:37:10 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pokemon.hpp"

pokemon::pokemon(std::string name)
{
    _name = name;
    setStat(name);
}

pokemon::~pokemon()
{
}

void pokemon::attackP(int dg, std::string attack, pokemon *target, bot *bot)
{
    if (attack == _attack1)
        takeDamage(dg, _deg1, _attack1, bot, target);
    else if (attack == _attack2)
        takeDamage(dg, _deg2, _attack2, bot, target);
}  

#include <sstream>

void pokemon::takeDamage(int multi, int damage, std::string attackName, bot *bot, pokemon *who)
{
    std::stringstream ss;
    ss << damage * multi;
    std::string nb = ss.str();
    std::string msg = who->getName() + " took " + nb + " damage from " + _name + " with " + attackName + "!";
    bot->sendMessage(msg);
    int trudmg = damage * multi;
    who->_hp -= trudmg;
}

std::string pokemon::getName()
{
    return _name;
}

void pokemon::setStat(std::string name)
{
    if (name == "Bulbasaur")
    {
        _hp = 85;
        _attack = 45;
        _defense = 49;
        _speed = 45;
        _deg1 = 40;
        _deg2 = 30;
        _attack1 = "Vine Whip";
        _attack2 = "Tackle";
    }
    else if (name == "Charmander")
    {
        _hp = 69;
        _attack = 52;
        _defense = 43;
        _speed = 65;
        _deg1 = 40;
        _deg2 = 30;
        _attack1 = "Ember";
        _attack2 = "Scratch";
    }
    else if (name == "Squirtle")
    {
        _hp = 72;
        _attack = 48;
        _defense = 65;
        _speed = 43;
        _deg1 = 40;
        _deg2 = 30;
        _attack1 = "Water Gun";
        _attack2 = "Tackle";
    }
}

int pokemon::getPv()
{
    return _hp;
}

void pokemon::getDeg(pokemon *adv, bot *bot)
{
    std::string attack;
    std::string attackName;
    int _degat = 1;
    rand() % 2 == 0 ? attack = _attack1 : attack = _attack2;
    if (attack == _attack1)
    {
        if (_name == "Bulbasaur")
        {
            if (adv->getName() == "Squirtle")
                _degat = 2;
        }
        else if (_name == "Charmander")
        {
            if (adv->getName() == "Bulbasaur")
                _degat = 2;
        }
        else if (_name == "Squirtle")
        {
            if (adv->getName() == "Charmander")
                _degat = 2;
        }
    }
    attackP(_degat, attack, adv, bot);
}

void pokemon::decreasePv(int degat)
{
    _hp -= degat;
}
