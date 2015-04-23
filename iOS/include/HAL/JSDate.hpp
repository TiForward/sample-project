/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_JSDATE_HPP_
#define _HAL_JSDATE_HPP_

#include "HAL/JSObject.hpp"

namespace HAL {

/*!
  @class
  
  @discussion A JavaScript object of the Date type.

  The only way to create a JSDate is by using the
  JSContext::CreateDate member function.
*/
class HAL_EXPORT JSDate final : public JSObject HAL_PERFORMANCE_COUNTER2(JSDate) {
	
 private:
	
	// Only a JSContext can create a JSDate.
	friend JSContext;
	
	JSDate(const JSContext& js_context, const std::vector<JSValue>& arguments = {});

	static JSObjectRef MakeDate(const JSContext& js_context, const std::vector<JSValue>& arguments);
};

} // namespace HAL {

#endif // _HAL_JSDATE_HPP_
