/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_JSBOOLEAN_HPP_
#define _HAL_JSBOOLEAN_HPP_

#include "HAL/JSValue.hpp"

namespace HAL {

/*!
  @class
  
  @discussion A JavaScript value of the boolean type.

  The only way to create a JSBoolean is by using the
  JSContext::CreateBoolean member function.
*/
class HAL_EXPORT JSBoolean final : public JSValue HAL_PERFORMANCE_COUNTER2(JSBoolean) {
	
 public:
	
	/*!
    @method
    
    @abstract Assign the given boolean value to the JSBoolean.
    
    @param boolean The bool to assign to the JSBoolean
    
    @result The JSBoolean with the new value of the given boolean.
  */
	JSBoolean& operator=(bool boolean) {
		JSValue::operator=(JSBoolean(get_context(), boolean));
		return *this;
	}

 private:

	// Only JSContext can create a JSBoolean.
	friend JSContext;
	
	JSBoolean(const JSContext& js_context, bool boolean)
			: JSValue(js_context, JSValueMakeBoolean(static_cast<JSContextRef>(js_context), boolean)) {
	}
};

} // namespace HAL {

#endif // _HAL_JSBOOLEAN_HPP_
