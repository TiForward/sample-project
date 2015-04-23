/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_DETAIL_JSEXPORTCALLBACKS_HPP_
#define _HAL_DETAIL_JSEXPORTCALLBACKS_HPP_

#include "HAL/JSValue.hpp"

#include <vector>

namespace HAL {
  class JSString;
  class JSObject;
  class JSPropertyNameAccumulator;
}


namespace HAL { namespace detail {
  
  /*!
   @typedef GetNamedValuePropertyCallback
   
   @abstract The callback to invoke when getting a property's value
   from your JavaScript object.
   
   @discussion For example, given this class definition:
   
   class Foo {
   JSValue GetBar() const;
   };
   
   You would define the callback like this:
   
   GetNamedValuePropertyCallback callback(&Foo::GetBar);
   
   @param 1 A const reference to the C++ object that implements your
   JavaScript object.
   
   @result Return the named property's value.
   */
  template<typename T>
  using GetNamedValuePropertyCallback = std::function<JSValue(const T&)>;
  
  /*!
   @typedef SetNamedValuePropertyCallback
   
   @abstract The callback to invoke when setting a property's value on
   your JavaScript object.
   
   @discussion For example, given this class definition:
   
   class Foo {
   bool SetBar(JSObject object, const JSValue& value);
   };
   
   You would define the callback like this:
   
   SetNamedValuePropertyCallback callback(&Foo::SetBar);
   
   @param 1 A non-const reference to the C++ object that implements
   your JavaScript object.
   
   @param 2 A const rvalue reference to the property's value.
   
   @result Return true to indicate that the property was set.
   */
  template<typename T>
  using SetNamedValuePropertyCallback = std::function<bool(T&, const JSValue&)>;
  
  /*!
   @typedef CallNamedFunctionCallback
   
   @abstract The callback to invoke when your JavaScript object is
   called as a function.
   
   @discussion For example, given this class definition:
   
   class Foo {
   JSValue Hello(const std::vector<JSValue>& arguments);
   };
   
   You would define the callback like this:
   
   CallNamedFunctionCallback callback(&Foo::Hello);
   
   In the JavaScript expression 'myObject.myFunction()', then
   'myFunction' is the instance of Foo being called, and this_object
   would be set to 'myObject'.
   
   @param 1 A non-const reference to the C++ object that implements
   your JavaScript object.
   
   @param 2 A const rvalue reference to the JSValue array of arguments
   to pass to the function.
   
   @param 3 An non-const rvalue reference to the 'this' JavaScript
   object.
   
   @result Return the function's value.
   */
  template<typename T>
  using CallNamedFunctionCallback = std::function<JSValue(T&, const std::vector<JSValue>&, JSObject&)>;
  
  /*!
   @typedef HasPropertyCallback
   
   @abstract The callback to invoke when determining whether your
   JavaScript object has a property. If this callback does not exist
   then your JavaScript object will forward the request to the
   GetPropertyCallback.
   
   @discussion The HasPropertyCallback enables optimization in cases
   where only a property's existence needs to be known, not its value,
   and computing its value is expensive. If this callback does not
   exist then your JavaScript object will forward the request to the
   GetPropertyCallback.
   
   If this callback returns false then the reqeust forwards to your
   JavaScript object's set of GetNamedValuePropertyCallback and
   CallNamedFunctionCallback callbacks (if any), then properties
   vended by your class' parent class chain, then properties belonging
   to your JavaScript object's prototype chain.
   
   For example, given this class definition:
   
   class Foo {
   bool HasProperty(const JSString& property_name) const;
   };
   
   You would define the callback like this:
   
   HasPropertyCallback callback(&Foo::HasProperty);
   
   @param 1 A const reference to the C++ object that implements your
   JavaScript object.
   
   @param 2 A const rvalue reference to the property's name.
   
   @result Return true if your JavaScript object has a property with
   the name in parameter 2. Return false to forward the reqeust to
   your JavaScript object's set of GetNamedValuePropertyCallback and
   CallNamedFunctionCallback callbacks (if any), then properties
   vended by your class' parent class chain, then properties belonging
   to your JavaScript object's prototype chain.
   */
  template<typename T>
  using HasPropertyCallback = std::function<bool(const T&, const JSString&)>;
  
  /*!
   @typedef GetPropertyCallback
   
   @abstract The callback to invoke when getting a property's value
   from your JavaScript object.
   
   @discussion If this callback returns native null value (context.CreateNativeNull())
   then get request forwards to your JavaScript object's set of
   GetNamedValuePropertyCallback and CallNamedFunctionCallback
   callbacks (if any), then properties vended by your class' parent
   class chain, then properties belonging to your JavaScript object's
   prototype chain.
   
   For example, given this class definition:
   
   class Foo {
   JSValue GetProperty(const JSString& property_name) const;
   };
   
   You would define the callback like this:
   
   GetPropertyCallback callback(&Foo::GetProperty);
   
   @param 1 A const reference to the C++ object that implements your
   JavaScript object.
   
   @param 2 A const rvalue reference to the property's name.
   
   @result The property's value with the name given in parameter 2 if
   it exists. If the property does not exist then return native null value (context.CreateNativeNull())
   to forward the request to your JavaScript object's set of
   GetNamedValuePropertyCallback and CallNamedFunctionCallback
   callbacks (if any), then properties vended by your class' parent
   class chain, then properties belonging to your JavaScript object's
   prototype chain.
   */
  template<typename T>
  using GetPropertyCallback = std::function<JSValue(const T&, const JSString&)>;
  
  /*!
   @typedef SetPropertyCallback
   
   @abstract Set the callback to invoke when setting a property's
   value on your JavaScript object.
   
   @discussion If this callback returns false then the reqeust
   forwards to your JavaScript object's set of
   SetNamedValuePropertyCallback callbacks (if any), then properties
   vended by your class' parent class chain, then properties belonging
   to your JavaScript object's prototype chain.
   
   For example, given this class definition:
   
   class Foo {
   bool SetProperty(const JSString& property_name, const JSValue& value);
   };
   
   You would define the callback like this:
   
   SetPropertyCallback callback(&Foo::SetProperty);
   
   @param 1 A non-const reference to the C++ object that implements
   your JavaScript object.
   
   @param 2 A const rvalue reference to the property's name.
   
   @param 3 A const rvalue reference to the property's value.
   
   @result Return true if the property with the name in parameter 2
   and value in parameter 2 was set on your JavaScript object. Return
   false to forward the reqeust to your JavaScript object's set of
   SetNamedValuePropertyCallback callbacks (if any), then properties
   vended by your class' parent class chain, then properties belonging
   to your JavaScript object's prototype chain.
   */
  template<typename T>
  using SetPropertyCallback = std::function<bool(T&, const JSString&, const JSValue&)>;
  
  /*!
   @typedef DeletePropertyCallback
   
   @abstract Set the callback to invoke when deleting a property from
   your JavaScript object.
   
   @discussion If this callback returns false then the reqeust
   forwards to your JavaScript object's set of
   GetNamedValuePropertyCallback and CallNamedFunctionCallback
   callbacks (if any), then properties vended by your class' parent
   class chain, then properties belonging to your JavaScript object's
   prototype chain.
   
   For example, given this class definition:
   
   class Foo {
   bool DeleteProperty(const JSString& property_name);
   };
   
   You would define the callback like this:
   
   DeletePropertyCallback callback(&Foo::DeleteProperty);
   
   @param 1 A non-const reference to the C++ object that implements
   your JavaScript object.
   
   @param 2 A const rvalue reference to the property's name.
   
   @result Return true if the property with the name in parameter 2
   was deleted from your JavaScript object. Return false to forward
   the reqeust to your JavaScript object's set of
   GetNamedValuePropertyCallback and CallAsFunctionCallback callbacks
   (if any), then properties vended by your class' parent class chain,
   then properties belonging to your JavaScript object's prototype
   chain.
   */
  template<typename T>
  using DeletePropertyCallback = std::function<bool(T&, const JSString&)>;
  
  /*!
   @method
   
   @abstract Set the callback to invoke when collecting the names of
   your JavaScript object's properties provided by the
   GetPropertyCallback and SetPropertyCallback callbacks. This
   callback is part of a chain of callbacks that are automatically
   invoked when your JavaScript object is used in a JavaScript
   for...in loop.
   
   @discussion The GetPropertyNamesCallback only needs to provide the
   property names provided by the GetPropertyCallback and
   SetPropertyCallback callbacks. Other property names are
   automatically added from the GetNamedValuePropertyCallback,
   SetNamedValuePropertyCallback and CallNamedFunctionCallback
   callbacks (if any), then properties vended by your class' parent
   class chain, then properties belonging to your JavaScript object's
   prototype chain.
   
   For example, given this class definition:
   
   class Foo {
   void GetPropertyNames(JSPropertyNameAccumulator& accumulator) const;
   };
   
   You would define the callback like this:
   
   GetPropertyNamesCallback callback(&Foo::GetPropertyNames);
   
   @param 1 A const reference to the C++ object that implements your
   JavaScript object.
   
   @param 2 A non-const rvalue reference to a
   JSPropertyNameAccumulator.
   
   @result void
   */
  template<typename T>
  using GetPropertyNamesCallback = std::function<void(const T&, JSPropertyNameAccumulator&)>;
  
  /*!
   @typedef CallAsFunctionCallback
   
   @abstract The callback to invoke when your JavaScript object is
   called as a function. If this callback does not exist, then calling
   your JavaScript object as a function will throw a JavaScript
   exception.
   
   @discussion For example, given this class definition:
   
   class Foo {
   JSValue CallAsFunction(const std::vector<JSValue>& arguments, JSObject& this_object) const;
   };
   
   You would define the callback like this:
   
   CallAsFunctionCallback callback(&Foo::CallAsFunction);
   
   In the JavaScript expression 'myObject.myFunction()', then
   'myFunction' is the instance of Foo being called, and 'myObject' is
   the context of the function call (i.e. the 'this' JavaScript
   object).
   
   @param 1 A const reference to the C++ object that implements your
   JavaScript object.
   
   @param 2 A const rvalue reference to the JSValue array of arguments
   to pass to the function.
   
   @param 3 An non-const rvalue reference to the 'this' JavaScript
   object.
   
   @result Return the value produced by calling your JavaScript object
   as a function.
   */
  template<typename T>
  using CallAsFunctionCallback = std::function<JSValue(T&, const std::vector<JSValue>&, JSObject&)>;
  
  /*!
   @typedef ConvertToTypeCallback
   
   @abstract The callback to invoke when converting your JavaScript
   object to another JavaScript type. This function is only invoked
   when converting your JavaScript object to a number or a string. A
   JavaScript object converted to boolean is 'true.' A JavaScript
   object converted to a JavaScript object is itself.
   
   @discussion For example, given this class definition:
   
   class Foo {
   JSValue ConvertToType(JSValue::Type type) const;
   };
   
   You would define the callback like this:
   
   ConvertToTypeCallback callback(&Foo::ConvertToType);
   
   @param 1 A const reference to the C++ object that implements your
   JavaScript object.
   
   @param 2 A JSValue::Type specifying the JavaScript type to convert
   to.
   
   @result Return the objects's converted value. Return native null value (context.CreateNativeNull())
   forward the reqeust to your class' parent class chain, then your
   JavaScript object's prototype chain.
   */
  template<typename T>
  using ConvertToTypeCallback = std::function<JSValue(const T&, ::HAL::JSValue::Type&)>;
  
}} // namespace HAL { namespace detail {

#endif // _HAL_DETAIL_JSEXPORTCALLBACKS_HPP_
