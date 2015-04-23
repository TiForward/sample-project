/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_JSFUNCTION_HPP_
#define _HAL_JSFUNCTION_HPP_

#include "HAL/JSObject.hpp"

namespace HAL {

/*!
  @class
  
  @discussion A JavaScript object of the Function type whose body is
  given as a string of JavaScript code. Use this class when you want
  to execute a script repeatedly to avoid the cost of re-parsing the
  script before each execution.

  The only way to create a JSFunction is by using the
  JSContext::CreateFunction member function.
*/
class HAL_EXPORT JSFunction final : public JSObject HAL_PERFORMANCE_COUNTER2(JSFunction) {
	
 private:
	
	// Only a JSContext can create a JSFunction.
	friend JSContext;
	
	JSFunction(const JSContext& js_context, const JSString& body, const std::vector<JSString>& parameter_names, const JSString& function_name, const JSString& source_url, int starting_line_number);

	static JSObjectRef MakeFunction(const JSContext& js_context, const JSString& body, const std::vector<JSString>& parameter_names, const JSString& function_name, const JSString& source_url, int starting_line_number);
};

} // namespace HAL {

#endif // _HAL_JSFUNCTION_HPP_
