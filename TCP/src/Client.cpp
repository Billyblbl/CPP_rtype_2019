/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Client
*/

#include <iostream>
#include "Client.hpp"

Client::Client(io_service &service, Instance &local):
	TConnection(service),
	_local(local)
{}

void	Client::onConnect()
{
	// makeInstance()
}

void	Client::onMessage(const REngineTCP::Message &message)
{
	switch (message.getType()) {
	case REngineTCP::ERROR: onEngineErr(message.getPayloadAs<std::string>());
		break;
	case REngineTCP::MAKEINSTANCE:
		_lobby = message.getPayloadAs<Instance::ID>();
		joinInstance(_lobby);
		break;
	case REngineTCP::KILLINSTANCE: _lobby = 0;
		break;
	case REngineTCP::JOININSTANCE: getMetadata().playerID = message.getPayloadAs<uint32_t>();
		break;
	case REngineTCP::QUITINSTANCE: _lobby = 0;
		break;
	case REngineTCP::LISTINSTANCE: std::cout << message.getPayloadAs<std::string>() << std::endl;
		break;
	default: std::cerr << "Unimplemented request " << message.getType() << '\n';
		break;
	}
}

void	Client::onError(const boost::system::error_code &)
{}

void	Client::onEngineErr(const std::string &reason)
{
	std::cerr << "Engine error : " << reason << '\n';
}

void	Client::makeInstance(const std::string &file)
{
	Send(REngineTCP::Message(REngineTCP::MAKEINSTANCE, REngineTCP::TEXT, file, file.size()));
}

void	Client::joinInstance(Instance::ID id)
{
	Send(REngineTCP::Message(REngineTCP::JOININSTANCE, REngineTCP::ID, id, sizeof(Instance::ID)));
}

void	Client::quitInstance(Instance::ID id)
{
	Send(REngineTCP::Message(REngineTCP::QUITINSTANCE, REngineTCP::ID, id, sizeof(Instance::ID)));
}