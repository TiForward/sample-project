/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_JSARRAY_HPP_
#define _HAL_JSARRAY_HPP_

#include "HAL/JSObject.hpp"
#include "HAL/JSValue.hpp"
#include "HAL/JSString.hpp"
#include <vector>

namespace HAL {

/*!
  @class
  
  @discussion A JavaScript object of the Array type.
  
  The only way to create a JSArray is by using the
  JSContext::CreateArray member function.
*/
class HAL_EXPORT JSArray final : public JSObject HAL_PERFORMANCE_COUNTER2(JSArray) {

public:
    /*!
     @method
     
     @abstract Convert this JSArray to a std::vector<JSValue>
     
     @result An array of JSValue with the result of conversion.
     */
    virtual operator std::vector<JSValue>() const final;
	
    /*!
     @method
     
     @abstract Return length of this JSArray
     
     @result Length of this JSArray
     */
    virtual uint32_t GetLength() const HAL_NOEXCEPT final;

    /*!
     @method
     
     @abstract Return an array of std::shared_ptr<T> to this object's private data.
     
     @result An array of std::shared_ptr<T> to this object's private data if the
     object has private data of type T*, otherwise nullptr.
     */
    template<typename T>
    std::vector<std::shared_ptr<T>> GetPrivateItems() const HAL_NOEXCEPT;

private:

	// Only JSContext and JSObject can create a JSArray.
	friend JSContext;
	friend JSObject;
	
	JSArray(const JSContext& js_context, const std::vector<JSValue>& arguments = {});

	static JSObjectRef MakeArray(const JSContext& js_context, const std::vector<JSValue>& arguments);

	// For interoperability with the JavaScriptCore C API.
	JSArray(const JSContext& js_context, JSObjectRef js_object_ref);
};

template<typename T>
std::vector<std::shared_ptr<T>> JSArray::GetPrivateItems() const HAL_NOEXCEPT {
	const uint32_t length = static_cast<uint32_t>(GetProperty("length"));
	std::vector<std::shared_ptr<T>> items(length);
	for (uint32_t i = 0; i < length; i++) {
		const JSValue js_item_prop = GetProperty(i);
		if (js_item_prop.IsObject()) {
			const JSObject js_item = static_cast<JSObject>(js_item_prop);
			items.at(i) = js_item.GetPrivate<T>();
		} else {
			items.at(i) = nullptr;
		}
	}
	return items;
}

} // namespace HAL {

#endif // _HAL_JSARRAY_HPP_
