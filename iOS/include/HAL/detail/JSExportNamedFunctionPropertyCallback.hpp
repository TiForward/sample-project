/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_DETAIL_JSEXPORTNAMEDFUNCTIONPROPERTYCALLBACK_HPP_
#define _HAL_DETAIL_JSEXPORTNAMEDFUNCTIONPROPERTYCALLBACK_HPP_

#include "HAL/detail/JSBase.hpp"
#include "HAL/detail/JSPropertyCallback.hpp"
#include "HAL/detail/JSExportCallbacks.hpp"
#include "HAL/detail/JSUtil.hpp"

#ifdef HAL_PERFORMANCE_COUNTER_ENABLE
#include "HAL/detail/JSPerformanceCounter.hpp"
#endif

namespace HAL { namespace detail {
  
  /*!
   @class
   
   @discussion A JSExportNamedFunctionPropertyCallback is an RAII
   wrapper around the JavaScriptCore C API JSStaticFunction, which
   describes a function property of a JavaScript object.
   */
  template<typename T>
  class JSExportNamedFunctionPropertyCallback final : public JSPropertyCallback HAL_PERFORMANCE_COUNTER2(JSExportNamedFunctionPropertyCallback<T>) {
    
  public:
    
    /*!
     @method
     
     @abstract Create a callback to invoke when a JavaScript object
     is called as a function.
     
     @discussion If this callback does not exist, then calling your
     object as a function will throw an exception.
     
     For example, given this class definition:
     
     class Foo {
     JSValue sayHello(const std::vector<JSValue>& arguments, JSObject& this_object);
     };
     
     You would define the callback like this:
     
     CallNamedFunctionCallback callback(&Foo::sayHello);
     
     @param name The function property's name.
     
     @param function_callback The callback to invoke when calling
     the JavaScript object as a function.
     
     @param attributes The set of JSPropertyAttributes to give to
     the function property.
     
     @result The callback to invoke when a JavaScript object is
     called as a function.
     
     @throws std::invalid_argument exception under these
     preconditions:
     
     1. If function_name is empty.
     
     2. If the function_callback is not provided.
     */
    JSExportNamedFunctionPropertyCallback(const std::string& function_name,
                                          CallNamedFunctionCallback<T> function_callback,
                                          const std::unordered_set<JSPropertyAttribute>& attributes);
    
    CallNamedFunctionCallback<T> function_callback() const {
      return function_callback__;
    }
    
    ~JSExportNamedFunctionPropertyCallback()                                                       = default;
    JSExportNamedFunctionPropertyCallback(const JSExportNamedFunctionPropertyCallback&)            HAL_NOEXCEPT;
    JSExportNamedFunctionPropertyCallback(JSExportNamedFunctionPropertyCallback&&)                 HAL_NOEXCEPT;
    JSExportNamedFunctionPropertyCallback& operator=(const JSExportNamedFunctionPropertyCallback&) HAL_NOEXCEPT;
    JSExportNamedFunctionPropertyCallback& operator=(JSExportNamedFunctionPropertyCallback&&)      HAL_NOEXCEPT;
    void swap(JSExportNamedFunctionPropertyCallback&)                                              HAL_NOEXCEPT;
    
  private:
    
    template<typename U>
    friend bool operator==(const JSExportNamedFunctionPropertyCallback<U>& lhs, const JSExportNamedFunctionPropertyCallback<U>& rhs) HAL_NOEXCEPT;
    
    CallNamedFunctionCallback<T> function_callback__ { nullptr };
  };
  
  template<typename T>
  JSExportNamedFunctionPropertyCallback<T>::JSExportNamedFunctionPropertyCallback(
                                                                                  const std::string& function_name,
                                                                                  CallNamedFunctionCallback<T> function_callback,
                                                                                  const std::unordered_set<JSPropertyAttribute>& attributes)
  : JSPropertyCallback(function_name, attributes)
  , function_callback__(function_callback) {
    
    if (!function_callback) {
      ThrowInvalidArgument("JSExportNamedFunctionPropertyCallback", "function_callback is missing");
    }
  }
  
  template<typename T>
  JSExportNamedFunctionPropertyCallback<T>::JSExportNamedFunctionPropertyCallback(const JSExportNamedFunctionPropertyCallback& rhs) HAL_NOEXCEPT
  : JSPropertyCallback(rhs)
  , function_callback__(rhs.function_callback__) {
  }
  
  template<typename T>
  JSExportNamedFunctionPropertyCallback<T>::JSExportNamedFunctionPropertyCallback(JSExportNamedFunctionPropertyCallback&& rhs) HAL_NOEXCEPT
  : JSPropertyCallback(rhs)
  , function_callback__(std::move(rhs.function_callback__)) {
  }
  
  template<typename T>
  JSExportNamedFunctionPropertyCallback<T>& JSExportNamedFunctionPropertyCallback<T>::operator=(const JSExportNamedFunctionPropertyCallback<T>& rhs) HAL_NOEXCEPT {
    HAL_DETAIL_JSPROPERTYCALLBACK_LOCK_GUARD;
    JSPropertyCallback::operator=(rhs);
    function_callback__ = rhs.function_callback__;
    return *this;
  }
  
  template<typename T>
  JSExportNamedFunctionPropertyCallback<T>& JSExportNamedFunctionPropertyCallback<T>::operator=(JSExportNamedFunctionPropertyCallback<T>&& rhs) HAL_NOEXCEPT {
    HAL_DETAIL_JSPROPERTYCALLBACK_LOCK_GUARD;
    swap(rhs);
    return *this;
  }
  
  template<typename T>
  void JSExportNamedFunctionPropertyCallback<T>::swap(JSExportNamedFunctionPropertyCallback<T>& other) HAL_NOEXCEPT {
    HAL_DETAIL_JSPROPERTYCALLBACK_LOCK_GUARD;
    JSPropertyCallback::swap(other);
    using std::swap;
    
    // By swapping the members of two classes, the two classes are
    // effectively swapped.
    swap(function_callback__, other.function_callback__);
  }
  
  template<typename T>
  void swap(JSExportNamedFunctionPropertyCallback<T>& first, JSExportNamedFunctionPropertyCallback<T>& second) HAL_NOEXCEPT {
    first.swap(second);
  }
  
  // Return true if the two JSExportNamedFunctionPropertyCallbacks
  // are equal.
  template<typename T>
  bool operator==(const JSExportNamedFunctionPropertyCallback<T>& lhs, const JSExportNamedFunctionPropertyCallback<T>& rhs) HAL_NOEXCEPT {
    if (lhs.function_callback__ && !rhs.function_callback__) {
      return false;
    }
    
    if (!lhs.function_callback__ && rhs.function_callback__) {
      return false;
    }
    
    return static_cast<JSPropertyCallback>(lhs) == static_cast<JSPropertyCallback>(rhs);
  }
  
  // Return true if the two JSExportNamedFunctionPropertyCallbacks
  // are not equal.
  template<typename T>
  bool operator!=(const JSExportNamedFunctionPropertyCallback<T>& lhs, const JSExportNamedFunctionPropertyCallback<T>& rhs) HAL_NOEXCEPT {
    return ! (lhs == rhs);
  }
  
}} // namespace HAL { namespace detail

#endif // _HAL_DETAIL_JSEXPORTNAMEDFUNCTIONPROPERTYCALLBACK_HPP_
