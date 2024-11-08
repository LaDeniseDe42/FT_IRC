/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:39:37 by akastler          #+#    #+#             */
/*   Updated: 2024/03/26 15:47:00 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

void signal_hand(int signum)
{
    (void)signum;
    throw std::logic_error(" \033[1;31m\nNeed to stop server\033[0m");
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "\033[38;2;255;165;0mUsage: ./irc [port] [password]\033[0m" << std::endl;
        return 1;
    }
    int port = std::atoi(argv[1]);
    std::string password = argv[2];
    server irc(port, password);
    try
    {
        signal(SIGINT, signal_hand);
        irc.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        irc.stop();
    }
    return 0;
}