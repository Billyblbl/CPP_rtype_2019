/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** TypeIndexer for indexed types
*/

#ifndef TYPEINDEXER_HPP_
#define TYPEINDEXER_HPP_

#include <cinttypes>

using TypeIndex = uint64_t;

///
///@brief singleton class to attribute indexes for indexed types
///
/// This mecanism is here to replace RTTI as standard typeid's can't be safe
/// accross dynamic library bounds
///
class TypeIndexer {
	public:

	///
	///@brief type index attributor
	///
	///
	static TypeIndex	attributeIndex();

	private:

	static TypeIndex	nextIndex;
};

#endif /* !TYPEINDEXER_HPP_ */
