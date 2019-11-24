/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** JSONValue
*/

#ifndef JSONVALUE_HPP_
#define JSONVALUE_HPP_

#include <vector>
#include <string>
#include <unordered_map>
#include <variant>
#include <memory>

class JSONValue {
	public:

		using String = std::string;
		using Numberi = long;
		using Numberf = double;
		using Array = std::vector<JSONValue>;

		using ObjectImpl = std::unordered_map<std::string, std::unique_ptr<JSONValue>>;
		using Object = std::unique_ptr<ObjectImpl>;
		using Bool = bool;
		struct Null {};

		using Value = std::variant<Null, String, Numberi, Numberf, Array, Object, Bool>;

		JSONValue() = default;
		JSONValue(JSONValue &&) = default;
		JSONValue(const JSONValue &) = default;

		template<typename Variant>
		JSONValue(const Variant &val):
			_val(std::forward<Variant>(val))
		{}

		template<typename Variant>
		JSONValue(Variant &&val):
			_val(std::forward<Variant>(val))
		{}

		JSONValue		&operator=(const JSONValue &) = default;
		JSONValue		&operator=(JSONValue &&) = default;

		JSONValue		&operator[](size_t idx);
		const JSONValue	&operator[](size_t idx) const;

		JSONValue		&operator[](const std::string &key);
		const JSONValue	&operator[](const std::string &key) const;

		template<typename Variant>
		Variant			&get()
		{
			return std::get<Variant>(_val);
		}

		template<typename Variant>
		const Variant	&get() const
		{
			return std::get<Variant>(_val);
		}

		template<typename Variant>
		bool			isType()
		{
			return std::get_if<Variant>(&_val) != nullptr;
		}

		bool			isNull() const;

		Value			&getVal();
		const Value		&getVal() const;

		static JSONValue	parseJSON(const std::string &input);

	protected:
	private:
		Value	_val;
};

#endif /* !JSONVALUE_HPP_ */
