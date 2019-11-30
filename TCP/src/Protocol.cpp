/*
** EPITECH PROJECT, 2019
** babl
** File description:
** babal protocol
*/

#include "Protocol.hpp"

bool				REngineTCP::hasValidMessage(const std::vector<std::byte> &data)
{
	if (data.size() < sizeof(MessageHeader))
		return false;
	const MessageHeader	*header = reinterpret_cast<const MessageHeader *>(data.data());
	return (data.size() >= header->size);
}

REngineTCP::Message	REngineTCP::extractMessage(std::vector<std::byte> &data)
{
	Message	msg(data);
	data.erase(data.begin(), data.begin() + msg.getSize() + sizeof(MessageHeader));
	return msg;
}

void				REngineTCP::writeMessage(std::vector<std::byte> &data, const Message &msg)
{
	Converter<MessageHeader>	header;
	header.asObject.size = msg.getSize();
	header.asObject.type = msg.getType();
	header.asObject.payload = msg.getPayloadType();
	data.insert(data.end(), std::begin(header.asData), std::end(header.asData));
	switch (msg.getPayloadType()) {
	case TEXT: {
			auto	&payloadData = msg.getPayloadAs<std::string>();
			auto	begin = payloadData.begin();
			auto	end = payloadData.end();
			data.resize(data.size() + std::distance(begin, end));
			std::transform(begin, end, data.end() - std::distance(begin, end), [](auto c){
				return std::byte(c);
			});
			break;
		}
	case ID: {
			Converter<uint64_t>	payload(msg.getPayloadAs<uint64_t>());
			data.insert(data.end(), std::begin(payload.asData), std::end(payload.asData));
			break;
		}
	case RAW: default: {
			auto	&payloadData = msg.getPayloadAs<std::vector<std::byte>>();
			data.insert(data.end(), payloadData.begin(), payloadData.end());
			break;
		}
	}
}
