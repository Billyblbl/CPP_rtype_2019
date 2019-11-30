/*
** EPITECH PROJECT, 2019
** babel
** File description:
** protocol message definition
*/

#include <string>
#include "Protocol.hpp"

REngineTCP::Message::Message(const std::vector<std::byte> &data):
	_header(*reinterpret_cast<const MessageHeader *>(data.data()))
{
	auto	begin = data.begin() + sizeof(MessageHeader);
	auto	end = data.begin() + _header.size;
	switch (_header.payload) {
	case TEXT: {
		std::string	text(std::distance(begin, end), '?');
		std::transform(data.begin() + sizeof(MessageHeader), data.end(), text.begin(), [](auto byte){
			return std::to_integer<char>(byte);
		});
		_payload.emplace<std::string>(text);
		break;
	}
	case ID: _payload.emplace<uint32_t>(*reinterpret_cast<const uint32_t *>(data.data() + sizeof(MessageHeader)));
		// std::cerr << "ID\n";
		break;
	case RAW: /* default: */ _payload.emplace<std::vector<std::byte>>(std::vector<std::byte>(next(data.begin(), sizeof(MessageHeader)), data.end()));
		// std::cerr << "RAW\n";
		break;
	default:
		throw std::runtime_error(std::string(__func__) + " : Unknown payload type : " + std::to_string(_header.payload));
	}
}

size_t						REngineTCP::Message::getSize() const
{
	return _header.size;
}

REngineTCP::MessageType			REngineTCP::Message::getType() const
{
	return _header.type;
}

const REngineTCP::MessagePayload	&REngineTCP::Message::getPayload() const
{
	return _payload;
}

REngineTCP::PayloadType				REngineTCP::Message::getPayloadType() const
{
	return _header.payload;
}
