/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_JSUNDEFINED_HPP_
#define _HAL_JSUNDEFINED_HPP_

#include "HAL/JSValue.hpp"

namespace HAL {

/*!
  @class
  
  @discussion A JavaScript value of the undefined type.

  The only way to create a JSUndefined is by using the
  JSContext::CreateUndefined member function.
*/
class HAL_EXPORT JSUndefined final : public JSValue HAL_PERFORMANCE_COUNTER2(JSUndefined) {
	
private:

	// Only a JSContext can create a JSUndefined.
	friend JSContext;
	
	explicit JSUndefined(const JSContext& js_context)
			: JSValue(js_context, JSValueMakeUndefined(static_cast<JSContextRef>(js_context))) {
	}
};

} // namespace HAL {

#endif // _HAL_JSUNDEFINED_HPP_
