/*
** EPITECH PROJECT, 2019
** babel
** File description:
** protocol message definition
*/

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
		_payload = text;
		break;
	}
	case ID: _payload = *reinterpret_cast<const uint64_t *>(data.data() + sizeof(MessageHeader));
		break;
	case RAW: default: _payload = std::vector<std::byte>(next(data.begin(), sizeof(MessageHeader)), data.end());
		break;
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
