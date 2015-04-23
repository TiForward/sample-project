/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_DETAIL_JSSTATICVALUE_HPP_
#define _HAL_DETAIL_JSSTATICVALUE_HPP_

#include "HAL/detail/JSBase.hpp"
#include "HAL/detail/JSPropertyCallback.hpp"

namespace HAL { namespace detail {
  
  /*!
   @class
   
   @discussion A JSStaticValue is an RAII wrapper around the
   JavaScriptCore C API JSStaticValue, which describes a value property
   of a JavaScript object.
   */
  class HAL_EXPORT JSStaticValue final : public JSPropertyCallback HAL_PERFORMANCE_COUNTER2(JSStaticValue) {
    
  public:
    
    JSStaticValue(const ::JSStaticValue& js_static_value);
    
    JSObjectGetPropertyCallback get_callback() const HAL_NOEXCEPT {
      return get_callback__;
    }
    
    JSObjectSetPropertyCallback set_callback() const HAL_NOEXCEPT {
      return set_callback__;
    }
    
    ~JSStaticValue()                               = default;
    JSStaticValue(const JSStaticValue&)            HAL_NOEXCEPT;
    JSStaticValue(JSStaticValue&&)                 HAL_NOEXCEPT;
    JSStaticValue& operator=(const JSStaticValue&) HAL_NOEXCEPT;
    JSStaticValue& operator=(JSStaticValue&&)      HAL_NOEXCEPT;
    void swap(JSStaticValue&)                      HAL_NOEXCEPT;
    
  private:
    
    friend bool operator==(const JSStaticValue& lhs, const JSStaticValue& rhs) HAL_NOEXCEPT;
    
    JSObjectGetPropertyCallback get_callback__ { nullptr };
    JSObjectSetPropertyCallback set_callback__ { nullptr };
  };
  
  inline
  void swap(JSStaticValue& first, JSStaticValue& second) HAL_NOEXCEPT {
    first.swap(second);
  }
  
  // Return true if the two JSStaticValues are equal.
  bool operator==(const JSStaticValue& lhs, const JSStaticValue& rhs) HAL_NOEXCEPT;
  
  // Return true if the two JSStaticValue are not equal.
  inline
  bool operator!=(const JSStaticValue& lhs, const JSStaticValue& rhs) HAL_NOEXCEPT {
    return ! (lhs == rhs);
  }
  
}} // namespace HAL { namespace detail {

#endif // _HAL_DETAIL_JSSTATICVALUE_HPP_
