/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:31:46 by qdenizar          #+#    #+#             */
/*   Updated: 2024/04/09 14:24:24 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "includes.hpp"


class bot
{
    private:
        std::string _botName;
        channel *_channel;
        int _nbJoke;
        int _nbStory;
        std::vector<std::string> _insults;
        std::map<std::string, std::map<std::string, std::vector<std::string> > > _invites;
        std::vector<morpion *> _morpions;
        std::vector<client *> _clientPlayingMorpion; 

    public:
        bot(std::string botName, channel *channel);
        ~bot();
        void setBot(std::string botName);
        std::string getBotName();
        void sendMessage(std::string message);
        void joke(int nb);
        void story(int nb);
        void upJokeOrStory(std::string type);
        void setInsults();
        bool thisIsInsult(std::string msg);
        void dispenseHelp();
        void russianRoulette(client *launcher, client *secondPlayer);

        void morpionGame(client *author, int nb);
        void createMorpion(client *author, client *invited);
        int hurtClient(std::string nick, client *author);
        void firework();
        void botHeal(client *author, int yesOrNo);
        void botBhee();
        void botHell();
        void seePv(client *author);
        std::vector<client *> getClientPlayMoprion();
        void sendAscii(std::string what);
        void addNewInvitation(client *author, std::string user, std::string game);
        bool inviteChecker(client *author, client *invited, std::string game);
        void acceptInvitation(client *author, std::string user, std::string game);
        void pokeduel(client *author, client *inviter);
        void battleStart(client *author, client *target);
};
