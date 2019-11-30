/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Server
*/

#include <iostream>
#include <string>
#include "Server.hpp"

Server::Server(int port, io_service &service, InstanceList &instance):
	TServer(port, service),
	_instances(instance)
{}

void	Server::onMessage(Session &session, const REngineTCP::Message &message)
{
	switch (message.getType()) {
	case REngineTCP::ERROR: onEngineErr(session, message.getPayloadAs<std::string>());
		break;
	case REngineTCP::MAKEINSTANCE:
		session.Send(REngineTCP::Message(
			REngineTCP::MAKEINSTANCE,
			REngineTCP::ID,
			makeInstance(message.getPayloadAs<std::string>()),
			sizeof(REngineTCP::MessageHeader) + sizeof(REngineTCP::ID)
		));
		break;
	case REngineTCP::KILLINSTANCE: killInstance(message.getPayloadAs<Instance::ID>());
		break;
	case REngineTCP::JOININSTANCE: joinInstance(session, message.getPayloadAs<Instance::ID>());
		break;
	case REngineTCP::QUITINSTANCE: quitInstance(session, message.getPayloadAs<Instance::ID>());
		break;
	case REngineTCP::LISTINSTANCE: //answer with all intance ids
		break;
	default: std::cerr << "Unimplemented request " << message.getType() << '\n';
		break;
	}
}

void	Server::onError(Session &session, const boost::system::error_code &er)
{
	// session.Send(REngineTCP::Message(REngineTCP::ERROR, REngineTCP::Error(er)));
}

void	Server::onEngineErr(Session &session, const std::string &reason)
{
	_connections.erase(std::find_if(_connections.begin(), _connections.end(), [&](auto sess){
		return sess->getMetadata().id == session.getMetadata().id;
	}));
}

Instance::ID	Server::makeInstance(const std::string &/* file */)
{
	return _instances.emplace_back(std::make_unique<Instance>(/* file */))->getID();
}

void			Server::killInstance(Instance::ID id)
{
	_instances.erase(std::find_if(_instances.begin(), _instances.end(), [&](auto &instance){
		return instance->getID() == id;
	}));
}

void			Server::joinInstance(Session &session, Instance::ID id)
{
	auto	it = std::find_if(_instances.begin(), _instances.end(), [&](auto &instance){
		return instance->getID() == id;
	});
	if (it == _instances.end()) {
		std::string_view	err("Instance not found");
		session.Send(REngineTCP::Message(REngineTCP::ERROR, REngineTCP::TEXT, err, sizeof(REngineTCP::MessageHeader) + err.size()));
	} else {
		// auto plID = it->"addPlayer(session?)"
		// session.Send(REngineTCP::Message(REngineTCP::JOININSTANCE, REngineTCP::ID, plID));
	}
}

void			Server::quitInstance(Session &session, Instance::ID id)
{
	auto	it = std::find_if(_instances.begin(), _instances.end(), [&](auto &instance){
		return instance->getID() == id;
	});
	if (it == _instances.end()) {
		std::string_view	err("Instance not found");
		session.Send(REngineTCP::Message(REngineTCP::ERROR, REngineTCP::TEXT, err, sizeof(REngineTCP::MessageHeader) + err.size()));
	} else {
		// it->"removePlayer(session)"
	}
}
