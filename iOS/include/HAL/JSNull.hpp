/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_JSNULL_HPP_
#define _HAL_JSNULL_HPP_

#include "HAL/JSValue.hpp"

namespace HAL {

/*!
  @class
  
  @discussion A JavaScript value of the null type.

  The only way to create a JSNull is by using the
  JSContext::CreateNull member function.
*/
class HAL_EXPORT JSNull final : public JSValue HAL_PERFORMANCE_COUNTER2(JSNull) {
	
private:

	// Only a JSContext can create a JSNull.
	friend JSContext;
	
	explicit JSNull(const JSContext& js_context)
			: JSValue(js_context, JSValueMakeNull(static_cast<JSContextRef>(js_context))) {
	}
};

} // namespace HAL {

#endif // _HAL_JSNULL_HPP_
