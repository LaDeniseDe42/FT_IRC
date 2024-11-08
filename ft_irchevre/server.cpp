#include "server.hpp"

server::server(int port, std::string password) : _port(port), _password(password), _nbCo(0)
{
    if (password.size() <= 0)
        std::exit(1);
    _socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (_socketServer < 0)
    {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        std::exit(1);
    }
    int opt = 1;
    if (setsockopt(_socketServer, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        std::exit(1);
    }
    bzero((char *)&_serverAddr, sizeof(_serverAddr));
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_addr.s_addr = INADDR_ANY;
    _serverAddr.sin_port = htons(_port);
    if (bind(_socketServer, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr)) < 0)
    {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        std::exit(1);
    }
    if (listen(_socketServer, 0) < 0)
    {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        std::exit(1);
    }
    _epollFd = epoll_create(1);
    if (_epollFd < 0)
    {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        std::exit(1);
    }
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = _socketServer;
    if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, _socketServer, &ev) < 0)
    {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        std::exit(1);
    }
}

server::~server()
{
    std::cout << "\033[1;31mThrow and destroyed server on mountain of destiny\033[0m" << std::endl;
}

void server::acceptClient()
{
    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(_socketServer, (struct sockaddr *)&clientAddr, &clientAddrSize);
    if (clientSocket < 0)
    {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        std::exit(1);
    }
    struct epoll_event ev;
    ev.events = EPOLLIN;
    client *newClient = new client(clientSocket);
    _clients.push_back(newClient);
    ev.data.ptr = newClient;
    std::cout << "\033[0;36m=== New client connected ===" << std::endl;
    std::cout << "\033[0;35mIP: \033[0;33m" << inet_ntoa(clientAddr.sin_addr) << std::endl;
    std::cout << "\033[0;35mSocket: \033[0;33m" << clientSocket << std::endl;
    std::cout << "\033[0;36m============================\033[0m" << std::endl
              << std::endl;
    if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, clientSocket, &ev) < 0)
        std::cerr << "Error epoll ctl add: " << strerror(errno) << std::endl;
    _nbCo++;
}

void server::sendGoatOfTheDay(client *client)
{
    sendMessage(RPL_MOTDSTART(client->getNick()), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), GOAT1), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), GOAT2), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), GOAT3), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), GOAT4), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), GOAT5), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), GOAT6), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), GOAT7), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), GOAT8), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), GOAT9), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), GOAT10), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), GOAT11), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), GOAT12), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), GOAT13), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), GOAT14), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), PROMPT1), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), PROMPT2), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), PROMPT3), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), PROMPT4), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), PROMPT5), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), PROMPT6), client->getFd());
    sendMessage(RPL_MOTD(client->getNick(), PROMPT7), client->getFd());
    sendMessage(RPL_ENDOFMOTD(client->getNick()), client->getFd());
}

void server::registerClient(client *client)
{
    std::time_t temp = std::time(NULL);
    std::string time = std::asctime(std::localtime(&temp));
    time.erase(time.size() - 1, 1);
    sendMessage(RPL_WELCOME(client->getNick(), client->getUser()), client->getFd());
    sendMessage(RPL_YOURHOST(client->getNick()), client->getFd());
    sendMessage(RPL_CREATED(client->getNick(), time), client->getFd());
    sendMessage(RPL_MYINFO(client->getNick()), client->getFd());
    sendMessage(RPL_ISUPPORT(client->getNick()), client->getFd());
    sendMessage(RPL_ISUPPORT2(client->getNick()), client->getFd());
    sendMessage(RPL_LUSERCLIENT(client->getNick(), getNumberInString(_clients.size()), "0", "1"), client->getFd());
    sendMessage(RPL_LUSEROP(client->getNick(), "0"), client->getFd());
    sendMessage(RPL_LUSERCHANNELS(client->getNick(), getNumberInString(_channels.size())), client->getFd());
    sendMessage(RPL_LUSERME(client->getNick(), getNumberInString(_clients.size()), "0"), client->getFd());
    sendMessage(RPL_LOCALUSERS(client->getNick(), getNumberInString(_clients.size()), getNumberInString(_nbCo)), client->getFd());
    sendMessage(RPL_GLOBALUSERS(client->getNick(), getNumberInString(_clients.size()), getNumberInString(_nbCo)), client->getFd());
    sendGoatOfTheDay(client);
    client->sendRegister = false;
    std::cout << "\033[1;32mclient \033[38;2;255;165;0m" << client->getNick() << " \033[1;32mregistered\033[0m" << std::endl;
}

void server::run()
{
    char ip[100];
    gethostname(ip, sizeof(ip));
    std::string IP = inet_ntoa(*((struct in_addr *)(gethostbyname(ip))->h_addr_list[0]));
    _ip = IP;
    std::time_t start = std::time(NULL);
    std::string time = std::asctime(std::localtime(&start));
    time.erase(time.size() - 1, 1);
    std::cout << "\033[0;34mServer initialisation..\nStarting at " << time << "...\nSend your personal data on Mother-Russia on IP : " << IP << " and port " << _port << " PLEASE WAIT...\nServer running..\033[0m\n"
              << std::endl;
    while (1)
    {
        for (size_t i = 0; i < _clients.size(); i++)
        {
            if (_clients[i]->disconnect == true)
                killClient(_clients[i]);
        }
        struct epoll_event events[1];
        int nfds = epoll_wait(_epollFd, events, 1, -1);

        for (int i = 0; i < nfds; i++)
        {
            if (events[i].data.fd == _socketServer)
                acceptClient();
            else
            {
                client *sender = (client *)(events[i].data.ptr);
                char buffer[1025] = {0};
                int nbBytesReceived = recv(sender->getFd(), buffer, 1024, 0);
                if (nbBytesReceived <= 0)
                    sender->disconnect = true;
                else
                {
                    sender->writeBuffer(buffer);
                    std::string message;
                    while ((message = sender->readBuffer()).size() > 0)
                    {
                        if (message[message.size() - 1] == '\n')
                            message = message.substr(0, message.size() - 1);
                        if (message[message.size() - 1] == '\r')
                            message = message.substr(0, message.size() - 1);
                        std::cout << "\033[0;36m********************************************" << std::endl;
                        std::cout << "\033[0;35mNew request by: \033[0;33m" << sender->getNick() << "\n\033[0;35mWith client socket: \033[0;33m" << sender->getFd() << "\n\033[0;35mNew Message is: \033[0;33m" << message.substr(0, message.size()) << "\033[0m" << std::endl;
                        std::cout << "\033[0;36m********************************************\033[0m\n"
                                  << std::endl;
                        tryCommands(message, sender);
                        if (sender->disconnect == true)
                            break;
                    }
                }
            }
        }
    }
}

void server::stop()
{
    close(_socketServer);
    close(_epollFd);
    for (size_t i = 0; i < _clients.size(); i++)
        delete _clients[i];
    _clients.clear();
    for (size_t i = 0; i < _channels.size(); i++)
        delete _channels[i];
    _channels.clear();
    std::cout << "\033[1;31mServer is correctly stopped\033[0m" << std::endl;
}

void server::sendMessage(std::string message, int fd)
{
    send(fd, message.c_str(), message.size(), 0);
}

void server::clientTryToEscape(client *sender)
{
    srand(time(NULL));
    int random = rand() % 100;
    if (random > 50)
    {
        if (random >= 85)
        {
            sender->removeNbInsults();
            sender->setIsInJail(false);
            std::istringstream isss("#jail");
            leaveChannel(isss, sender);
            std::string msg = "You are free now. Don't do it again.\r\n";
            sendMessage(msg, sender->getFd());
            sender->setPv(10);
            msg = "During your escape, you found a guard's armor, and now your HP is doubled. \r\n";
            sendMessage(msg, sender->getFd());
        }
        else
        {
            sender->removeNbInsults();
            sender->setIsInJail(false);
            std::istringstream isss("#jail");
            leaveChannel(isss, sender);
            std::string msg = "You are free now. Don't do it again.\r\n";
            sendMessage(msg, sender->getFd());
        }
    }
    else
    {
        std::string msg = "You wake up all gards and they hurt you when they see you out of your jail \r\n";
        std::string msg2 = PRIVMSG(sender->getNick(), "#jail", msg);
        sender->decreasePV(1);
        sendMessage(msg2, sender->getFd());
    }
}

void server::cmdInJail(std::istringstream &iss, std::string word, client *sender)
{
    bool regist = sender->Registered();
    std::string word2;
    iss >> word2;
    std::string word3;
    iss >> word3;
    if (word == "QUIT")
    {
        std::cout << "\033[1;32mclient fight in prison and need to go far away at hospital\033[0m" << std::endl;
        sender->disconnect = true;
    }
    else if (word == "PING" && regist == true)
    {
        std::string ping;
        iss >> ping;
        sendMessage("PONG " + _ip + " " + ping + "\r\n", sender->getFd());
    }
    if (word == "PRIVMSG" && word2 == "#jail" && word3 == ":!FREE")
        clientTryToEscape(sender);
    else
    {
        std::string msg = "You are in jail and cannot execute this command.\r\n";
        std::string msg2 = PRIVMSG(sender->getNick(), "#jail", msg);
        sendMessage(msg2, sender->getFd());
    }
}

void server::cmdForRegisteredUser(std::istringstream &iss, std::string word, client *sender)
{
    if (word == "PRIVMSG")
        privateMsg(iss, sender);
    else if (word == "WHO")
        whoCommand(iss, sender);
    else if (word == "JOIN")
    {
        unsigned int y = 0;
        std::string channels;
        std::string passwords;
        iss >> channels;
        iss >> passwords;
        std::vector<std::string> VChan = split(channels, ',');
        std::vector<std::string> VPass = split(passwords, ',');
        std::string isss2;
        for (size_t i = 0; i < VChan.size(); i++)
        {

            if (VChan[i].size() <= 0)
            {
                sendMessage(ERR_NEEDMOREPARAMS(sender->getNick(), "JOIN"), sender->getFd());
                return;
            }
            if (VPass.size() == 0)
                isss2 = VChan[i];
            else
                isss2 = VChan[i] + " " + VPass[y++];
            std::istringstream isss(isss2);
            if (VChan[i].size() > 1)
                joinCmd(isss, sender);
            else
                sendMessage(ERR_BADCHANMASK(sender->getNick(), VChan[i]), sender->getFd());
        }
    }
    else if (word == "PART")
    {
        std::string channels;
        std::string reason;
        iss >> channels;
        iss >> reason;
        std::vector<std::string> VChan = split(channels, ',');
        for (size_t i = 0; i < VChan.size(); i++)
        {
            std::istringstream isss(VChan[i] + " " + reason);
            leaveChannel(isss, sender);
        }
    }
    else if (word == "MODE")
        mode(iss, sender);
    else if (word == "TOPIC")
        topic(iss, sender);
    else if (word == "KICK")
        kickYourAssOfMyChannel(iss, sender);
    else if (word == "INVITE")
        inviteTheDevil(iss, sender);
}

void server::otherCmd(std::istringstream &iss, std::string word, client *sender, bool regist)
{
    if (word == "QUIT")
    {
        std::cout << "\033[1;32mclient try to quit\033[0m" << std::endl;
        sender->disconnect = true;
        iss >> sender->reasonDisconnect;
        if (sender->reasonDisconnect.size() > 0 && sender->reasonDisconnect[0] == ':')
            sender->reasonDisconnect.erase(0, 1);
    }
    else if (word == "PING")
    {
        std::string ping;
        iss >> ping;
        sendMessage("PONG " + _ip + " " + ping + "\r\n", sender->getFd());
    }
    else if (word == "NICK")
    {
        if (sender->getPasswordSet() == false)
        {
            sendMessage(NEEDPASS, sender->getFd());
            return;
        }
        std::string temp;
        iss >> temp;
        changeNick(temp, sender);
    }
    else if (word == "USER")
    {
        if (sender->getPasswordSet() == false)
        {
            sendMessage(NEEDPASS, sender->getFd());
            return;
        }
        if (regist == true)
        {
            sendMessage(ERR_ALREADYREGISTRED(sender->getNick()), sender->getFd());
            return;
        }
        std::string user;
        iss >> user;
        std::string hostname;
        iss >> hostname;
        std::string afterHostname;
        iss >> afterHostname;
        std::string afterAfter;
        iss >> afterAfter;
        std::string temp;
        std::getline(iss, temp);
        afterAfter += temp;
        if (!(user.size() > 0 && hostname.size() > 0 && afterHostname.size() > 0 && afterAfter.size() >= 2 && afterAfter[0] == ':'))
        {
            sendMessage(ERR_NEEDMOREPARAMS(sender->getNick(), "USER"), sender->getFd());
            return;
        }
        if (user.size() > 0)
        {
            for (size_t i = 0; i < _clients.size(); i++)
            {
                if (_clients[i]->getUser() == user)
                {
                    sendMessage(ERR_ALREADYREGISTRED(sender->getUser()), sender->getFd());
                    return;
                }
            }
            sender->setUser(user);
            sender->setRealName(afterAfter.substr(1, afterAfter.size() - 1));
        }
        else if (user.size() <= 0)
            sendMessage(ERR_NEEDMOREPARAMS(sender->getNick(), "PRIVMSG"), sender->getFd());
    }
    else if (word == "PASS")
    {
        if (regist == true)
        {
            sendMessage(ERR_ALREADYREGISTRED(sender->getNick()), sender->getFd());
            return;
        }
        std::string pass;
        iss >> pass;
        if (pass.size() > 0 && pass == _password)
            sender->setPassword();
        else if (pass.size() <= 0)
            sendMessage(ERR_NEEDMOREPARAMS(sender->getNick(), "PASS"), sender->getFd());
        else
        {
            sendMessage(ERR_PASSWDMISMATCH(sender->getNick()), sender->getFd());
            sender->disconnect = true;
        }
    }
    else if (word == "CAP")
    {
        std::string cap;
        iss >> cap;
        if (cap == "LS")
            sendMessage(CAP_LS, sender->getFd());
    }
    else if (word.size() > 0 && regist == false)
        sendMessage(ERR_NOTREGISTERED(sender->getNick()), sender->getFd());
    if (regist == false)
    {
        sender->Registered();
        if (sender->sendRegister == true)
            registerClient(sender);
    }
}

bool server::handleUnknownCommand(std::string word, client *sender)
{
    if (word == "PRIVMSG" || word == "JOIN" || word == "PART" || word == "MODE" || word == "TOPIC" || word == "KICK" || word == "INVITE" || word == "WHO")
        return false;
    else if (word == "QUIT" || word == "PING" || word == "NICK" || word == "USER" || word == "PASS" || word == "CAP")
        return false;
    sendMessage(ERR_UNKNOWNCOMMAND(sender->getNick(), word), sender->getFd());
    return true;
}

void server::whoCommand(std::istringstream &iss, client *author)
{
    std::string channel;
    iss >> channel;
    if (channel.size() <= 0)
    {
        sendMessage(ERR_NEEDMOREPARAMS(author->getNick(), "WHO"), author->getFd());
        return;
    }
    if (channel[0] != '#')
    {
        sendMessage(ERR_NOSUCHCHANNEL(author->getNick(), channel), author->getFd());
        return;
    }
    for (size_t i = 0; i < _channels.size(); i++)
    {
        if (_channels[i]->getChannelName() == channel)
        {
            std::vector<client *> clients = _channels[i]->getChannelClients();
            for (size_t j = 0; j < clients.size(); j++)
                sendMessage(RPL_WHOREPLY(author->getNick(), channel, clients[j]->getNick(), clients[j]->getUser(), clients[j]->getRealName()), author->getFd());
            sendMessage(RPL_ENDOFWHO(author->getNick(), channel), author->getFd());
            return;
        }
    }
    sendMessage(ERR_NOSUCHNICK(author->getNick(), channel), author->getFd());
}

void server::sendJailMessage(client *sender)
{
    sendMessage(PRIVMSG(sender->getNick(), "#jail", JAIL1), sender->getFd());
    sendMessage(PRIVMSG(sender->getNick(), "#jail", JAIL2), sender->getFd());
    sendMessage(PRIVMSG(sender->getNick(), "#jail", JAIL3), sender->getFd());
    sendMessage(PRIVMSG(sender->getNick(), "#jail", JAIL4), sender->getFd());
    sendMessage(PRIVMSG(sender->getNick(), "#jail", JAIL5), sender->getFd());
    sendMessage(PRIVMSG(sender->getNick(), "#jail", JAIL6), sender->getFd());
    sendMessage(PRIVMSG(sender->getNick(), "#jail", JAIL7), sender->getFd());
    sendMessage(PRIVMSG(sender->getNick(), "#jail", JAIL8), sender->getFd());
    sendMessage(PRIVMSG(sender->getNick(), "#jail", JAIL9), sender->getFd());
    sendMessage(PRIVMSG(sender->getNick(), "#jail", JAIL10), sender->getFd());
    sendMessage(PRIVMSG(sender->getNick(), "#jail", JAIL11), sender->getFd());
    sendMessage(PRIVMSG(sender->getNick(), "#jail", JAIL12), sender->getFd());
    sendMessage(PRIVMSG(sender->getNick(), "#jail", JAIL13), sender->getFd());
    sendMessage(PRIVMSG(sender->getNick(), "#jail", JAIL14), sender->getFd());
}

void server::tryCommands(std::string command, client *sender)
{
    if (command.size() <= 0 || sender->disconnect == true)
        return;
    std::istringstream iss(command);
    std::string word;
    iss >> word;
    bool regist = sender->Registered();
    if (sender->getIsInJail())
    {
        cmdInJail(iss, word, sender);
        return;
    }
    if (handleUnknownCommand(word, sender) == true)
        return;
    if (sender->getIsInJail() == false && regist == true)
        cmdForRegisteredUser(iss, word, sender);
    otherCmd(iss, word, sender, regist);
    if (sender->getNbInsults() >= 3 && regist == true && sender->getIsInJail() == false)
    {
        sender->setIsInJail(true);
        std::istringstream isss("#jail");
        std::string msg = "So here you are. Time to go to jail\r\n";
        sendMessage(msg, sender->getFd());
        std::vector<std::string> channels = sender->getChannels();
        for (unsigned int i = 0; i < channels.size(); i++)
        {
            std::istringstream gotojail(channels[i] + " :going to jail");
            leaveChannel(gotojail, sender);
        }
        joinCmd(isss, sender);
        sendJailMessage(sender);
        return;
    }
}

void server::killClient(client *client)
{
    epoll_ctl(_epollFd, EPOLL_CTL_DEL, client->getFd(), NULL);
    std::vector<std::string> channels = client->getChannels();
    for (unsigned int i = 0; i < channels.size(); i++)
    {
        if (client->getPv() <= 0)
        {
            std::istringstream iss(channels[i] + " :user was murdered and is now dead");
            leaveChannel(iss, client);
        }
        else
        {
            if (client->reasonDisconnect.size() > 0)
            {
                std::istringstream iss(channels[i] + " :" + client->reasonDisconnect);
                leaveChannel(iss, client);
            }
            else
            {
                std::istringstream iss(channels[i] + " :go make some tea");
                leaveChannel(iss, client);
            }
        }
    }
    sendMessage("ERROR :Goodbye " + client->getNick() + "\r\n", client->getFd());
    for (size_t i = 0; i < _clients.size(); i++)
    {
        if (_clients[i]->getFd() == client->getFd())
        {
            std::cout << "\033[0;101m=== Client disconnected ===\033[0m" << std::endl;
            delete _clients[i];
            _clients.erase(_clients.begin() + i);
            break;
        }
    }
}

std::string server::getNumberInString(int number)
{
    std::stringstream ss;
    ss << number;
    return ss.str();
}

std::string server::getNumberInString(unsigned int number)
{
    std::stringstream ss;
    ss << number;
    return ss.str();
}

std::string server::getNumberInString(size_t number)
{
    std::stringstream ss;
    ss << number;
    return ss.str();
}

std::vector<std::string> server::split(std::string str, char separator)
{
    std::vector<std::string> result;
    if (str.size() <= 0)
        return result;
    std::string temp = "";
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == separator)
        {
            result.push_back(temp);
            temp = "";
        }
        else
            temp += str[i];
    }
    result.push_back(temp);
    return result;
}