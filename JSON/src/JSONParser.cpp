/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** JSONParser
*/

#include <fstream>
#include <regex>
#include <array>
#include "JSONParser.hpp"

//debug
#include <iostream>

static const std::pair<std::regex, JSONParser::TokenType>	Entries[] = {
	{std::regex("^\"[^\"]*\""), 		JSONParser::STRING},
	{std::regex("^-?[0-9]+\\.[0-9]+"),	JSONParser::FLOAT},
	{std::regex("^-?[0-9]+"),			JSONParser::INTEGER},
	{std::regex("^null"),				JSONParser::JNULL},
	{std::regex("^true|false"),			JSONParser::BOOL},
	{std::regex("^\\{"),				JSONParser::OPENOBJ},
	{std::regex("^}"),					JSONParser::CLOSEOBJ},
	{std::regex("^\\["),				JSONParser::OPENARR},
	{std::regex("^]"),					JSONParser::CLOSEARR},
	{std::regex("^,"), 					JSONParser::COMA},
	{std::regex("^:"), 					JSONParser::PAIRING},
	{std::regex("\\s+"),				JSONParser::WHITESPACE}
};

JSONValue				JSONParser::load(const std::string &path)
{
	using namespace std::string_literals;
	// std::cout << __func__ << std::endl;
	try {
		std::ifstream	file(path);
		if (!file.is_open())
			throw std::runtime_error(__func__ + " : unable to open file : "s + path);
		std::string		content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		return parse(content);
	} catch(const std::exception& e) {
		for (auto &token : _tokens)
			std::cerr << token.second;
		std::cerr << '\n';
		throw;
	}
}

JSONValue				JSONParser::parse(const std::string &input)
{
	// std::cout << __func__ << std::endl;
	try {
		tokenise(input.begin(), input.end());
		return parseValue(_tokens.begin(), _tokens.end());
	} catch(const std::exception& e) {
		std::cerr << __func__ << ' ' << e.what() << '\n';
		throw;
	}
}

JSONValue	JSONParser::parseValue(titerator begin, titerator end)
{
	// std::cout << __func__ << std::endl;
	if (begin == end) throw std::runtime_error(std::string(__func__) + " : Empty value");
	switch (begin->first) {
	case STRING: return parseString(begin);
		break;
	case INTEGER: return parseInteger(begin);
		break;
	case FLOAT: return parseFloat(begin);
		break;
	case BOOL: return parseBool(begin);
		break;
	case OPENOBJ: return parseObject(begin, end);
		break;
	case OPENARR: return parseArray(begin, end);
		break;
	case JNULL: return parseNull(begin);
		break;
	default: throw std::runtime_error(std::string(__func__) + " : Unexpected token " + begin->second);
		break;
	}
}

void	JSONParser::tokenise(siterator begin, siterator end)
{
	// std::cout << __func__ << std::endl;
	std::smatch	match;
	for (auto it = begin; it < end; it += match.str().size()) {
		// std::cout << "remaining :" << std::endl;
		// std::cout << std::string(begin, end) << std::endl;
		for (auto &entry : Entries) {
			if (std::regex_search(it, end, match, entry.first)) {
				if (entry.second != JSONParser::WHITESPACE)
					_tokens.emplace_back(entry.second, match.str());
				break;
			}
		}
		if (match.empty())
			throw std::runtime_error(std::string(__func__) + " : JSON syntax error");
	}
	// std::cout << '/' << __func__ << std::endl;
}

JSONValue	JSONParser::parseString(titerator begin)
{
	// std::cout << __func__ << std::endl;
	auto		&[_, value] = *begin;
	std::string	unquoted(value.begin() + 1, value.end() - 1);
	_tokens.erase(begin);
	return unquoted;
}

JSONValue	JSONParser::parseInteger(titerator begin)
{
	// std::cout << __func__ << std::endl;
	auto		&[_, value] = *begin;
	auto		val = std::stol(value);
	_tokens.erase(begin);
	return val;
}

JSONValue	JSONParser::parseFloat(titerator begin)
{
	// std::cout << __func__ << std::endl;
	auto		&[_, value] = *begin;
	auto		val = std::stod(value);
	_tokens.erase(begin);
	return val;
}

JSONValue	JSONParser::parseBool(titerator begin)
{
	// std::cout << __func__ << std::endl;
	auto &[_, value] = *begin;
	auto		val = (value == "value");
	_tokens.erase(begin);
	return val;
}

JSONValue	JSONParser::parseObject(titerator begin, titerator end)
{
	// std::cout << __func__ << std::endl;
	JSONValue::Object	obj = std::make_unique<JSONValue::ObjectImpl>();
	while (std::next(begin)->first != JSONParser::CLOSEOBJ) {
		auto	&&pairing = parsePairing(std::next(begin), std::prev(end));
		obj->emplace(pairing.first, std::move(pairing.second));
		if (std::next(begin)->first != JSONParser::CLOSEOBJ && std::next(begin)->first != JSONParser::COMA)
			throw std::runtime_error(std::string(__func__) + " : Missing ',' in object");
		else if (std::next(begin)->first == JSONParser::COMA)
			_tokens.erase(std::next(begin));
	}
	_tokens.erase(begin, std::next(begin, 2));
	return std::move(obj);
}

JSONValue	JSONParser::parseArray(titerator begin, titerator end)
{
	// std::cout << __func__ << std::endl;
	JSONValue::Array	arr;
	while (std::next(begin)->first != JSONParser::CLOSEARR) {
		arr.emplace_back(parseValue(std::next(begin), std::prev(end)));
		if (std::next(begin)->first != JSONParser::CLOSEARR && std::next(begin)->first != JSONParser::COMA)
			throw std::runtime_error(std::string(__func__) + " : Missing ',' in array");
		else if (std::next(begin)->first == JSONParser::COMA)
			_tokens.erase(std::next(begin));
	}
	_tokens.erase(begin, std::next(begin, 2));
	return arr;
}

JSONValue	JSONParser::parseNull(titerator begin)
{
	// std::cout << __func__ << std::endl;
	_tokens.erase(begin);
	return JSONValue::Null{};
}

JSONParser::Pairing	JSONParser::parsePairing(titerator begin, titerator end)
{
	// std::cout << __func__ << std::endl;
	auto pairer = std::next(begin);
	if (std::distance(begin, end) < 3)
		throw std::runtime_error(std::string(__func__) + " : Syntax error : " + end->second);
	if (pairer->first != JSONParser::PAIRING)
		throw std::runtime_error(std::string(__func__) + " : Syntax error : " + pairer->second);
	auto	key = parseString(begin);
	auto	value = std::make_unique<JSONValue>(parseValue(std::next(pairer), end));
	_tokens.erase(pairer);
	return {key.get<JSONValue::String>(), std::move(value)};
}