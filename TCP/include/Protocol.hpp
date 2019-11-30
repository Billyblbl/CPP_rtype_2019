/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** rtype voip
*/

#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

#include <string>
#include <variant>
#include <vector>
#include <cstdint>
#include <any>
#include <boost/system/error_code.hpp>

#include <iostream>
class REngineTCP {
	public:

		///
		///@brief message type codes
		///
		/// Defines the nature of the message, and how to interpret its payload
		///
		///@sa MessageHeaser, MessagePayload
		///
		enum MessageType : uint16_t {
			ERROR = 0,
			MAKEINSTANCE = 1,	//request a new instance to the server, arg = file of level, answer = instanceID
			KILLINSTANCE = 2,	//request destruction of an instance, arg = instanceID, no answer needed
			JOININSTANCE = 3,	//request join of an instance, arg = instanceID, answer = playerID
			QUITINSTANCE = 4,	//request quit of an instance, arg = instanceID, no answer needed
			LISTINSTANCE = 5	//request a list of instances, no arg needed, answer = all current instances' IDs
		};

		enum PayloadType : uint16_t {
			EMPTY = 0,
			TEXT = EMPTY + 1,
			ID = TEXT + 1,
			RAW = ID + 1,
		};

		///
		///@brief message header definition
		///
		/// |Message----------------------------------------------------------|
		/// |Message Header|Message payload-----------------------------------|
		/// |Size  |Type   |Message payload-----------------------------------|
		///    |		   +--------------------------------------------------+
		///    |								   ^
		///    |								   |
		///    +-----------------------------------+
		///
		///@sa MessageTYpe, MessagePayload
		///
		struct MessageHeader {
			int32_t		size;	///<- Message payload size (header excluded)
			MessageType	type;	///<- cf MessageType
			PayloadType	payload;
			MessageHeader() = default;
			MessageHeader(const MessageHeader &) = default;
			MessageHeader(MessageHeader &&) = default;
			MessageHeader(int32_t _size, MessageType _type, PayloadType _payload):
				size(_size),
				type(_type),
				payload(_payload)
			{}
		};

		using MessagePayload = std::any;

		struct Error {
			public:
				Error(boost::system::error_code _er): er(_er){};
				boost::system::error_code	er;
				inline size_t	size() const {return sizeof(Error);}
		};

		///
		///@brief Data convertion tool template
		///
		///@tparam T type to be converted to raw data
		///
		template<typename T>
		union Converter {
			T			asObject;
			std::byte	asData[sizeof(T)];
			Converter() = default;
			Converter(const T &obj): asObject(obj) {};
			Converter( T &&obj): asObject(obj) {};
		};

		///
		///@brief Protocol message type object
		///
		///
		class Message {
			public:

				///
				///@brief Construct a new Message object from raw data
				///
				///@param data raw data
				///
				Message(const std::vector<std::byte> &data);

				///
				///@brief Construct a new Message object with payload
				///
				///@tparam PayloadType variant used for the payload
				///@param type message type
				///@param payload message payload
				///
				template<typename Payload>
				Message(MessageType type, PayloadType ptype, const Payload &payload, size_t size):
					_header(size + sizeof(MessageHeader), type, ptype),
					_payload(payload)
				{}

				///
				///@brief Construct a new Message object from without payload
				///
				///@param type message type
				///
				Message(MessageType type):
					_header(0, type, EMPTY)
				{}

				///
				///@brief Move constructor
				///
				///
				Message(Message &&) = default;

				///
				///@brief Copy constructor
				///
				///
				Message(const Message &) = default;

				///
				///@brief Get the Size
				///
				///
				size_t					getSize() const;

				///
				///@brief Get the Message Type
				///
				///
				MessageType				getType() const;

				///
				///@brief Get the Payload object
				///
				///
				const MessagePayload	&getPayload() const;

				PayloadType				getPayloadType() const;

				///
				///@brief Get the Payload object as T
				///
				///@tparam T type to interpret payload
				///
				template<typename T>
				const T					&getPayloadAs() const
				{
					if (!_payload.has_value())
						throw std::runtime_error(std::string(__func__) + " : No payload");
					// std::cerr << "payload type = " << _payload.type().name() << '\n';
					// std::cerr << "requested type = " << typeid(T).name() << '\n';
					// std::cerr << "payload type enum " << _header.payload << '\n';
					// std::cerr << "message type" << _header.type << '\n';
					return std::any_cast<const T &>(_payload);
				}

			private:

				MessageHeader	_header;
				MessagePayload	_payload;
		};

		///
		///@brief Protocol message validator
		///
		///@param data buffer to check for message
		///
		static bool		hasValidMessage(const std::vector<std::byte> &data);

		///
		///@brief Protocol message extractor
		///
		///@param data buffer to extract message from
		///@return Message extracted Message
		///
		static Message	extractMessage(std::vector<std::byte> &data);

		///
		///@brief Protocol message writer
		///
		///@param data buffer to write message into
		///@param msg Message to be writen in data
		///
		static void		writeMessage(std::vector<std::byte> &data, const Message &msg);

};

#endif /* !PROTOCOL_HPP_ */
