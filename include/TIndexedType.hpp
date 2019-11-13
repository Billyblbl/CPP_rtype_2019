/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** indexed type template
*/

#ifndef TINDEXEDTYPE_HPP_
#define TINDEXEDTYPE_HPP_

#include "TypeIndexer.hpp"

///
///@brief Index type template
///
///@warning intended for CRTP usage
///
template<typename T>
class TIndexedType {
	public:
		virtual ~TIndexedType();

		static TypeIndex	getID()
		{
			static TypeIndex	index = TypeIndexer::attributeIndex();
			return index;
		}

};

#endif /* !TINDEXEDTYPE_HPP_ */
