/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:20:19 by akastler          #+#    #+#             */
/*   Updated: 2024/04/12 08:48:16 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "messages_ascii.hpp"

#define CAP_LS "CAP * LS :none\r\n"
#define INT_MAX 2147483647

#define NETWORK "ft_irchevre"
#define VERSION "0.1.8.45.666"

#define NEEDPASS "Need password to connect\r\n"

#define PRIVMSG(user, target, message)                      (":" + user + " PRIVMSG " + target + " :" + message + "\r\n")
#define JOIN(nick, user, channel)                           (":" + nick + "!~" + user + "@localhost JOIN " + channel + "\r\n")
#define KICK(sender, target, channel, reason)               (":" + sender + " KICK " + channel + " " + target + " :" + reason + "\r\n")
#define PART(nick, user, channel, reason)                   (":" + nick + "!~" + user + "@localhost PART " + channel + " :" + reason + "\r\n")
#define MODE(sender, target, mode, arg)                     (":" + sender + "@localhost MODE " + target + " " + mode + " " + arg + "\r\n")
#define NICK(user, nick)                                    (":" + user + " NICK :" + nick + "\r\n")

#define RPL_WELCOME(user, name)                             (":localhost 001 " + user + " :Welcome to the " + NETWORK + ", " + user + "[!" + name + "@localhost]\r\n")
#define RPL_YOURHOST(user)                                  (":localhost 002 " + user + " :you server are in localhost, running version " + VERSION + "\r\n")
#define RPL_CREATED(user, time)                             (":localhost 003 " + user + " :This server was create: " + time + "\r\n")
#define RPL_MYINFO(user)                                    (":localhost 004 " + user + " " + NETWORK + " " + VERSION + " no user mode , channel modes:,,kl,it \r\n")

#define RPL_LUSERCLIENT(user, u, i, s)                      (":localhost 251 " + user + " :There are " + u + " users and " + i + " invisible on " + s + " servers\r\n")
#define RPL_LUSEROP(user, ops)                              (":localhost 252 " + user + " " + ops + " :operator(s) online\r\n")
#define RPL_LUSERCHANNELS(user, ch)                         (":localhost 254 " + user + " " + ch + " :channels formed\r\n")
#define RPL_LUSERME(user, c, s)                             (":localhost 255 " + user + " :I have " + c + " clients and " + s + " servers\r\n")
#define RPL_LOCALUSERS(user, u, m)                          (":localhost 265 " + user + " [" + u + " " + m + "] :Current local users " + u + ", max " + m + "\r\n")
#define RPL_GLOBALUSERS(user, u, m)                         (":localhost 266 " + user + " [" + u + " " + m + "] :Current global users " + u + ", max " + m + "\r\n")
#define RPL_MOTDSTART(user)                                 (":localhost 375 " + user + ": - ft_irchevre Message of the day - \r\n")
#define RPL_MOTD(user, BHEE)                                (":localhost 372 " + user + " :" + BHEE + "\r\n")
#define RPL_ENDOFMOTD(user)                                 (":localhost 376 " + user + " :End of /MOTD command.\r\n")

#define RPL_UMODEIS(user, mode)                             (":localhost 221 " + user + " " + mode + "\r\n")
#define RPL_CHANNELMODEIS(user, channel, limit)             (":localhost 324 " + user + " " + channel + " " + limit + "\r\n")
#define RPL_CREATIONTIME(user, channel, time)               (":localhost 329 " + user + " " + channel + " " + time + "\r\n")
#define RPL_NOTOPIC(user, channel)                          (":localhost 331 " + user + " " + channel + " :" + topic + "\r\n")
#define RPL_TOPIC(user, channel, topic)                     (":localhost 332 " + user + " " + channel + " :" + topic + "\r\n")
#define RPL_INVITING(user, target, channel)                 (":localhost 341 " + user + " " + target + " " + channel + "\r\n")
#define RPL_WHOREPLY(client, chan, user, nick, realname)    (":localhost 352 " + client + " " + chan + " " + user + " localhost FT_IRC " + nick + " H :0 " + realname + "\r\n")
#define RPL_ENDOFWHO(client, chan)                          (":localhost 315 " + client + " " + chan + " :End of /WHO list\r\n")

#define ERR_NOSUCHNICK(user, information)                   (":localhost 401 " + user + " " + information + " :No such nick/channel\r\n")
#define ERR_NOSUCHCHANNEL(user, information)                (":localhost 403 " + user + " " + information + " :No such channel\r\n")
#define ERR_CANNOTSENDTOCHAN(user, channel)                 (":localhost 404 " + user + " " + channel + " :Cannot send to channel\r\n")
#define ERR_NORECIPIENT(user)                               (":localhost 411 " + user + " :No recipient given (PRIVMSG)\r\n")
#define ERR_UNKNOWNCOMMAND(user, command)                   (":localhost 421 " + user + " " + command + " :Unknown command\r\n")
#define ERR_NONICKNAMEGIVEN(user)                           (":localhost 431 " + user + " :No nickname given\r\n")
#define ERR_ERRONEUSNICKNAME(user)                          (":localhost 432 " + user + " :Erroneus nickname\r\n")
#define ERR_NICKNAMEINUSE(user, nick)                       (":localhost 433 " + user + " " + nick + " :Nickname is already in use\r\n")
#define ERR_NICKCOLLISION(user)                             (":localhost 436 " + user + " :Nickname collision KILL\r\n")
#define ERR_USERNOTINCHANNEL(user, target, channel)         (":localhost 441 " + user + " " + target + " " + channel + " :They aren't on that channel\r\n")
#define ERR_NOTONCHANNEL(user, channel)                     (":localhost 442 " + user + " " + channel + " :You're not on that channel\r\n")
#define ERR_USERONCHANNEL(user, channel)                    (":localhost 443 " + user + " " + channel + " :User is already on channel\r\n")
#define ERR_NOTREGISTERED(user)                             (":localhost 451 " + user + " :You have not registered\r\n")
#define ERR_NEEDMOREPARAMS(user, command)                   (":localhost 461 " + user + " " + command + " :Not enough parameters\r\n")
#define ERR_NEEDOTHERPARAMS(user)                           (":localhost 461 " + user + " :Dont try to fuck with me and give me a good number\r\n")
#define ERR_ALREADYREGISTRED(user)                          (":localhost 462 " + user + " :You may not reregister\r\n")
#define ERR_PASSWDMISMATCH(user)                            (":localhost 464 " + user + " :Password incorrect\r\n")
#define ERR_CHANNELISFULL(user, channel)                    (":localhost 471 " + user + " " + channel + " :Cannot join channel, is full (+l)\r\n")
#define ERR_UNKNOWNMODE(nick, modechar)                     (":localhost 472 " + nick + " " + modechar + " :Unknown mode\r\n")
#define ERR_INVITEONLYCHAN(user, channel)                   (":localhost 473 " + user + " " + channel + " :Cannot join channel (+i)\r\n")
#define ERR_BADCHANNELKEY(user, channel)                    (":localhost 475 " + user + " " + channel + " :Cannot join channel, bad mdp (+k)\r\n")
#define ERR_BADCHANMASK(user, channel)                      (":localhost 476 " + user + " " + channel + " :Channel name is not valid\r\n")
#define ERR_CHANOPRIVSNEEDED(user, channel)                 (":localhost 482 " + user + " " + channel + " :You're not channel operator\r\n")
#define ERR_CHANOPRIVSNEEDEDD(user, channel)                (":localhost 482 " + user + " " + channel + " :Operator is not allow to do this\r\n")
#define ERR_INVALIDKEY(user, channel)                       (":localhost 525 " + user + " " + channel + " :Invalid key (please use alpha-num chara) \r\n")
#define ERR_INVALIDKEY2(user, channel)                      (":localhost 525 " + user + " " + channel + " :Invalid key (min 2 characters, max 32) \r\n")

#define RPL_ISUPPORT(client)                                (":localhost 005 " + client + " CASEMAPPING=rfc7613 CHANLIMIT=#: CHANMODES=,,kl,it CHANNELLEN=32 CHANTYPES=# ELIST= HOSTLEN=512 KICKLEN=512 MAXTARGETS=1 MODES=1 NETWORK=ft_irchevre NICKLEN=32 PREFIX=(o)@ :Are supported by this server\r\n")
#define RPL_ISUPPORT2(client)                               (":localhost 005 " + client + " STATUSMSG=@ TARGMAX=PRIVMSG:1,JOIN:,NAMES:,WHO:1,KICK:1 TOPICLEN=512 USERLEN=32 :Are supported by this server\r\n")

#define M "\033[0;33m"
#define C "\033[0;36m"
#define R "\033[0;31m"
#define G "\033[0;32m"
#define Y "\033[0;33m"
#define B "\033[0;34m"
#define P "\033[0;35m"
#define W "\033[0m"
