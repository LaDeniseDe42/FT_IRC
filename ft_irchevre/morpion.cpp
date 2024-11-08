/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   morpion.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:05:18 by akastler          #+#    #+#             */
/*   Updated: 2024/04/12 10:20:24 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "morpion.hpp"

morpion::morpion(channel *chan, bot *bote, client *player1, client *player2)
{
    _chan = chan;
    _bot = bote;
    _player1 = player1;
    _player2 = player2;
    if (_player2 == NULL)
        _bot->sendMessage(_player1->getNick() + " : You play against the bot ! (to play use !morpion <1-9>, for example !morpion 4)");
    else
        _bot->sendMessage(_player1->getNick() + " vs " + _player2->getNick() + " : Let's play Tic Tac Toe ! (to play use !morpion <1-9>, for example !morpion 5)");
    if (rand() % 2 || _player2 == NULL) // if turn is 1, player1 starts // player 2 as replace by bot on single player // if player2 is NULL, it's a single player game (vs bot)
    {
        _bot->sendMessage(_player1->getNick() + " : You start !");
        _turn = true;
    }
    else
    {
        if (_player2 != NULL)
            _bot->sendMessage(_player2->getNick() + " : You start !");
        _turn = false;
    }
    gameFinished = false;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            _board[i][j] = '1' + i * 3 + j;
    displayBoard(false);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            _board[i][j] = ' ';
}

morpion::~morpion()
{
    if (_player2 == NULL)
        displayBoard(false);
}

void morpion::playGame(client *player, int caseNb)
{
    if (gameFinished == true)
        return;
    if (_turn == true)
    {
        if (player == _player1)
        {
            if (_board[(caseNb - 1) / 3][(caseNb - 1) % 3] == ' ')
            {
                _board[(caseNb - 1) / 3][(caseNb - 1) % 3] = 'X';
                if (_player2 == NULL)
                    checkWin();
                else
                    displayBoard(true);
                _turn = false;
                if (gameFinished == true)
                    return;
                if (_player2 == NULL)
                    botTurn();
                else
                    sendToPlayers(_player2->getNick() + " : It's your turn !");
            }
            else
                sendToPlayers(player->getNick() + " : This case is already taken !");
        }
        else
        {
            std::string msg = PRIVMSG(_bot->getBotName(), _chan->getChannelName(), player->getNick() + " : It's not your turn !");
            send(player->getFd(), msg.c_str(), msg.size(), 0);
        }
    }
    else
    {
        if (player == _player2)
        {
            if (_board[(caseNb - 1) / 3][(caseNb - 1) % 3] == ' ')
            {
                _board[(caseNb - 1) / 3][(caseNb - 1) % 3] = 'O';
                displayBoard(true);
                _turn = true;
                if (gameFinished == true)
                    return;
                sendToPlayers(_player1->getNick() + " : It's your turn !");
            }
            else
                sendToPlayers(player->getNick() + " : This case is already taken !");
        }
        else
        {
            std::string msg = PRIVMSG(_bot->getBotName(), _chan->getChannelName(), player->getNick() + " : It's not your turn !");
            send(player->getFd(), msg.c_str(), msg.size(), 0);
        }
    }
}

void morpion::botTurn()
{
    botPlay();
    if (gameFinished == false)
    {
        _turn = true;
        sendToPlayers(_player1->getNick() + " : It's your turn !");
    }
}

void morpion::playRandom()
{
    int nb = rand() % 9 + 1;
    if (nb == 1 && _board[0][0] == ' ')
        _board[0][0] = 'O';
    else if (nb == 2 && _board[0][1] == ' ')
        _board[0][1] = 'O';
    else if (nb == 3 && _board[0][2] == ' ')
        _board[0][2] = 'O';
    else if (nb == 4 && _board[1][0] == ' ')
        _board[1][0] = 'O';
    else if (nb == 5 && _board[1][1] == ' ')
        _board[1][1] = 'O';
    else if (nb == 6 && _board[1][2] == ' ')
        _board[1][2] = 'O';
    else if (nb == 7 && _board[2][0] == ' ')
        _board[2][0] = 'O';
    else if (nb == 8 && _board[2][1] == ' ')
        _board[2][1] = 'O';
    else if (nb == 9 && _board[2][2] == ' ')
        _board[2][2] = 'O';
    else
        playRandom();
    displayBoard(true);
}

int morpion::test_hor(char c)
{
    for (int i = 0; i <= 2; i++)
    {
        if ((_board[i][0] == c && _board[i][1] == c && _board[i][2] == ' ') || (_board[i][0] == c && _board[i][2] == c) || (_board[i][1] == c && _board[i][2] == c))
        {
            for (int k = 0; k <= 2; k++)
            {
                if (_board[i][k] == ' ')
                {
                    _board[i][k] = 'O';
                    displayBoard(true);
                    return (1);
                }
            }
        }
    }
    return (0);
}

int morpion::test_ver(char c)
{
    for (int j = 0; j <= 2; j++)
    {
        if ((_board[0][j] == c && _board[1][j] == c && _board[2][j] == ' ') || (_board[0][j] == c && _board[2][j] == c) || (_board[1][j] == c && _board[2][j] == c))
        {
            for (int k = 0; k <= 2; k++)
            {
                if (_board[k][j] == ' ')
                {
                    _board[k][j] = 'O';
                    displayBoard(true);
                    return (1);
                }
            }
        }
    }
    return 0;
}

int morpion::test_diag(char c)
{
    if (_board[0][0] == c && _board[1][1] == ' ' && _board[2][2] == c)
    {
        _board[1][1] = 'O';
        displayBoard(true);
        return (1);
    }
    else if (_board[0][0] == ' ' && _board[1][1] == c && _board[2][2] == c)
    {
        _board[0][0] = 'O';
        displayBoard(true);
        return (1);
    }
    else if (_board[0][0] == c && _board[1][1] == c && _board[2][2] == ' ')
    {
        _board[2][2] = 'O';
        displayBoard(true);
        return (1);
    }
    else if (_board[0][2] == c && _board[1][1] == ' ' && _board[2][0] == c)
    {
        _board[1][1] = 'O';
        displayBoard(true);
        return (1);
    }
    else if (_board[0][2] == ' ' && _board[1][1] == c && _board[2][0] == c)
    {
        _board[0][2] = 'O';
        displayBoard(true);
        return (1);
    }
    else if (_board[0][2] == c && _board[1][1] == c && _board[2][0] == ' ')
    {
        _board[2][0] = 'O';
        displayBoard(true);
        return (1);
    }
    return 0;
}

void morpion::botPlay()
{
    if (gameFinished == true)
        return;
    sendToPlayers("IA MORPI play");
    if (test_hor('O') == 1)
        return;
    else if (test_ver('O') == 1)
        return;
    else if (test_diag('O') == 1)
        return;
    else
    {
        if (test_hor('X') == 1)
            return;
        else if (test_ver('X') == 1)
            return;
        else if (test_diag('X') == 1)
            return;

        if (_board[1][1] == ' ')
        {
            _board[1][1] = 'O';
            displayBoard(true);
            return;
        }
        playRandom();
    }
}

void morpion::checkWin()
{
    if ((_board[0][0] == _board[0][1] && _board[0][1] == _board[0][2] && _board[0][0] != ' ') // check horizontal
        || (_board[1][0] == _board[1][1] && _board[1][1] == _board[1][2] && _board[1][0] != ' ')
        || (_board[2][0] == _board[2][1] && _board[2][1] == _board[2][2] && _board[2][0] != ' ')
        || (_board[0][0] == _board[1][1] && _board[1][1] == _board[2][2] && _board[0][0] != ' ') // check diagonal
        || (_board[2][0] == _board[1][1] && _board[1][1] == _board[0][2] && _board[2][0] != ' ')
        || (_board[0][0] == _board[1][0] && _board[1][0] == _board[2][0] && _board[0][0] != ' ') // check vertical
        || (_board[0][1] == _board[1][1] && _board[1][1] == _board[2][1] && _board[0][1] != ' ')
        || (_board[0][2] == _board[1][2] && _board[1][2] == _board[2][2] && _board[0][2] != ' '))
    {
        gameFinished = true;
        if (_turn == true)
        {
            _bot->sendMessage(_player1->getNick() + " : You win !");
            if (_player2 != NULL)
                _bot->sendMessage(_player2->getNick() + " : You lose !");
        }
        else
        {
            _bot->sendMessage(_player1->getNick() + " : You lose !");
            if (_player2 != NULL)
                _bot->sendMessage(_player2->getNick() + " : You win !");
        }
    }
    else
    {
        int i = 0;
        int j = 0;
        while (i < 3)
        {
            j = 0;
            while (j < 3)
            {
                if (_board[i][j] == ' ')
                    return;
                j++;
            }
            i++;
        }
        _bot->sendMessage("It's a draw !");
        gameFinished = true;
    }
}

void morpion::sendToPlayers(std::string msg)
{
    msg = PRIVMSG(_bot->getBotName(), _chan->getChannelName(), msg);
    send(_player1->getFd(), msg.c_str(), msg.size(), 0);
    if (_player2 != NULL)
        send(_player2->getFd(), msg.c_str(), msg.size(), 0);
}

void morpion::displayBoard(bool checkWinOrNot)
{
    std::string board = " " + std::string(1, _board[0][0]) + " | " + std::string(1, _board[0][1]) + " | " + std::string(1, _board[0][2]);
    sendToPlayers(board);
    board = "---+---+---";
    sendToPlayers(board);
    board = " " + std::string(1, _board[1][0]) + " | " + std::string(1, _board[1][1]) + " | " + std::string(1, _board[1][2]);
    sendToPlayers(board);
    board = "---+---+---";
    sendToPlayers(board);
    board = " " + std::string(1, _board[2][0]) + " | " + std::string(1, _board[2][1]) + " | " + std::string(1, _board[2][2]);
    sendToPlayers(board);
    sendToPlayers("\n");
    if (checkWinOrNot)
        checkWin();
}

const std::string morpion::getUser1()
{
    return (_player1->getUser());
}

const std::string morpion::getUser2()
{
    if (_player2 == NULL)
        return ("");
    return (_player2->getUser());
}