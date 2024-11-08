/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   morpion.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:55:07 by akastler          #+#    #+#             */
/*   Updated: 2024/04/08 16:17:46 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "includes.hpp"

class morpion
{
private:
    channel *_chan;
    bot *_bot;
    client *_player1;
    client *_player2;
    char _board[3][3];
    bool _turn;
public:
    morpion(channel *chan, bot *bot, client *player1, client *player2);
    ~morpion();
    void playGame(client *player, int nb);
    void displayBoard(bool checkWinOrNot);
    void checkWin();
    bool gameFinished;
    const std::string getUser1();
    const std::string getUser2();
    void botTurn();
    void botPlay();
    int test_hor(char c);
    int test_ver(char c);
    int test_diag(char c);
    void playRandom();
    void sendToPlayers(std::string msg);
};