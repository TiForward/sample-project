/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_JSREGEXP_HPP_
#define _HAL_JSREGEXP_HPP_

#include "HAL/JSObject.hpp"

namespace HAL {

/*!
  @class
  
  @discussion A JavaScript object of the RegExp type.

  The only way to create a JSRegExp is by using the
  JSContext::CreateRegExp member function.
*/
class HAL_EXPORT JSRegExp final : public JSObject HAL_PERFORMANCE_COUNTER2(JSRegExp) {
	
 private:
	
	// Only a JSContext can create a JSRegExp.
	friend JSContext;

	JSRegExp(const JSContext& js_context, const std::vector<JSValue>& arguments = {});

	static JSObjectRef MakeRegExp(const JSContext& js_context, const std::vector<JSValue>& arguments);
};

} // namespace HAL {

#endif // _HAL_JSREGEXP_HPP_
