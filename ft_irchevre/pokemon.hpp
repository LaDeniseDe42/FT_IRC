/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pokemon.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:57:44 by qdenizar          #+#    #+#             */
/*   Updated: 2024/04/09 14:46:49 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "includes.hpp"

class bot;

class pokemon
{
    private:
        std::string _name;
        int _hp;
        int _attack;
        int _defense;
        int _speed;
        int _deg1;
        int _deg2;
        std::string _attack1;
        std::string _attack2;

    public:
        pokemon(std::string name);
        ~pokemon();
        void attackP(int dg, std::string attack, pokemon *target, bot *bot);
        void setStat(std::string name);
        void takeDamage(int dg, int damage, std::string attackName, bot *bot, pokemon *who);
        std::string getName();
        int getPv();
        void getDeg(pokemon *adv, bot *bot);
        void decreasePv(int degat);
};
