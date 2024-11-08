/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:06:14 by akastler          #+#    #+#             */
/*   Updated: 2024/04/09 13:19:58 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "includes.hpp"

class bot;

class channel
{
public:
    channel(std::string channelName);
    ~channel();
    std::string getChannelName();
    int joinChannel(client *client);
    int leaveChannel(client *client, std::string reason);
    std::vector<client *> getChannelClients();
    void changeTopic(std::string newTopic, std::string author);
    bool isOperator(std::string user);
    void addOperator(client *author, std::string user);
    void removeOperator(client *author, std::string user);
    std::string getTopic();
    std::string getMdp();
    bool isMdp();
    void setMdp(std::string mdp, std::string author);
    void deletemdp(std::string author);
    void setLimit(int limit, std::string author);
    void deleteLimit(std::string author);
    void setWeCanChangeTopic(bool weCanChangeTopic, std::string author);
    bool isFull();
    void modeInvitationList(std::string author);
    void removeModeInvitationList(std::string author);
    std::string getMode();
    bool isInviteMode();
    void addInvitation(std::string user);
    void removeInvitation(std::string user);
    std::vector<std::string> getInvitationList();
    std::time_t getCreation();
    
    void setBot(std::string botName);
    void useBotJokeStory(std::string type);
    void useBotInsult(std::string message, client *author, int z);
    void useBotHelp();

    bool thisUserIsInChannel(std::string user);
    void useBotBhee();
    void useBotHell();

    void useHurtClient(client *author, std::string user);
    void useBotFirework();
    void useBotHeal(client *author, int yesOrNo);
    void useSeePv(client *author);

    void inviteInGame(client *author, std::string user, std::string game);
    void acceptInGame(client *author, std::string user, std::string game);

    void launchRussianRoulette(client *author);
    
    void playMorpion(client *author, int nb);
    void morpionWithBot(client *author);

private:
    std::string _channelName;
    std::vector<client *> _channelClients;
    std::vector<std::string> _operator;
    std::vector<std::string> _invitationList;
    std::string _topic;
    std::string _mdp;
    bool _thereIsMdp;
    int _limit;
    std::time_t _creationTime;
    bool _weCanChangeTopic;
    bool _inviteMode;
    bot *_bot;
    
};