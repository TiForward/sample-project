/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_JSCLASSATTRIBUTE_HPP_
#define _HAL_JSCLASSATTRIBUTE_HPP_

#include <cstddef>
#include <functional>

namespace HAL {

/*!
  @enum
  
  @constant None Specifies that a JSClass has no special attributes.
  
  @constant NoAutomaticPrototype Specifies that a JSClass should not
  automatically generate a shared prototype for its instance
  objects. Use NoAutomaticPrototype in combination with
  JSObject::SetPrototype to manage prototypes manually.
*/
enum class HAL_EXPORT JSClassAttribute : std::uint32_t /* typedef unsigned JSClassAttributes */ {
	None,
	NoAutomaticPrototype
};

} // HAL

// Provide a hash function so that a JSClassAttributes can be stored
// in an unordered container.
namespace std {

using HAL::JSClassAttribute;

template<>
struct hash<JSClassAttribute> {
	using argument_type   = JSClassAttribute;
	using result_type     = std::size_t;
	using underlying_type = std::underlying_type<argument_type>::type;
	std::hash<underlying_type> hash_function = std::hash<underlying_type>();
	
	result_type operator()(const argument_type& class_attribute) const {
		return hash_function(static_cast<underlying_type>(class_attribute));
	}
};

}  // namespace std {

#endif // _HAL_JSCLASSATTRIBUTE_HPP_
