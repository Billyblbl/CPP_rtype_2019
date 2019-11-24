/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** JSONParser
*/

#ifndef JSONPARSER_HPP_
#define JSONPARSER_HPP_

#include <list>
#include "JSONValue.hpp"

class JSONParser {
	public:

		enum TokenType {
			STRING,
			INTEGER,
			FLOAT,
			BOOL,
			OPENOBJ,
			CLOSEOBJ,
			OPENARR,
			CLOSEARR,
			COMA,
			PAIRING,
			WHITESPACE,
			JNULL
		};

		using TokenList = std::list<std::pair<TokenType, std::string>>;

		using titerator = TokenList::const_iterator;
		using siterator = std::string::const_iterator;

		JSONValue	load(const std::string &path);
		JSONValue	parse(const std::string &input);

		JSONValue	parseValue(titerator begin, titerator end);

		JSONValue	parseString(titerator begin);
		JSONValue	parseInteger(titerator begin);
		JSONValue	parseFloat(titerator begin);
		JSONValue	parseBool(titerator begin);
		JSONValue	parseObject(titerator begin, titerator end);
		JSONValue	parseArray(titerator begin, titerator end);
		JSONValue	parseNull(titerator begin);

		using Pairing = std::pair<std::string, std::unique_ptr<JSONValue>>;

		Pairing		parsePairing(titerator begin, titerator end);
		// JSONValue	parse(std::string &&consumableInput);



		void	tokenise(siterator begin, siterator end);

	private:


		TokenList	_tokens;
};

#endif /* !JSONPARSER_HPP_ */
