/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:36:42 by akastler          #+#    #+#             */
/*   Updated: 2024/04/08 15:13:27 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class pokemon;
class client;
class server;
class channel;
class morpion;
class bot;

//includes for std
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <cstdio>
#include <stdexcept>
#include <ctime>
#include <cctype>
#include <fstream>
#include <algorithm>


//includes for signals
#include <csignal>

//includes for epoll and socket
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>

//includes for server
#include "pokemon.hpp"
#include "messages.hpp"
#include "server.hpp"
#include "morpion.hpp"
#include "bot.hpp"
#include "client.hpp"
#include "channel.hpp"