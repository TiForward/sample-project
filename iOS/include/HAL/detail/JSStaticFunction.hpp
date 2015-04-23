/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_DETAIL_JSSTATICFUNCTION_HPP_
#define _HAL_DETAIL_JSSTATICFUNCTION_HPP_

#include "HAL/detail/JSBase.hpp"
#include "HAL/detail/JSPropertyCallback.hpp"

namespace HAL { namespace detail {
  
  /*!
   @class
   
   @discussion A JSStaticFunction is an RAII wrapper around the
   JavaScriptCore C API JSStaticFunction, which describes a function
   property of a JavaScript object.
   */
  
  class HAL_EXPORT JSStaticFunction final : public JSPropertyCallback HAL_PERFORMANCE_COUNTER2(JSStaticFunction) {
      
    public:
      
      JSStaticFunction(const ::JSStaticFunction& js_static_function);
      
      JSObjectCallAsFunctionCallback function_callback() const HAL_NOEXCEPT {
        return function_callback__;
      }
      
      ~JSStaticFunction() = default;
      JSStaticFunction(const JSStaticFunction&)            HAL_NOEXCEPT;
      JSStaticFunction(JSStaticFunction&&)                 HAL_NOEXCEPT;
      JSStaticFunction& operator=(const JSStaticFunction&) HAL_NOEXCEPT;
      JSStaticFunction& operator=(JSStaticFunction&&)      HAL_NOEXCEPT;
      void swap(JSStaticFunction&)                         HAL_NOEXCEPT;
      
    private:
      
      friend bool operator==(const JSStaticFunction& lhs, const JSStaticFunction& rhs) HAL_NOEXCEPT;
      
      JSObjectCallAsFunctionCallback function_callback__ { nullptr };
    };
    
    
    inline
    void swap(JSStaticFunction& first, JSStaticFunction& second) HAL_NOEXCEPT {
      first.swap(second);
    }
    
    // Return true if the two JSStaticFunctions are equal.
    bool operator==(const JSStaticFunction& lhs, const JSStaticFunction& rhs) HAL_NOEXCEPT;
    
    // Return true if the two JSStaticFunctions are not equal.
    inline
    bool operator!=(const JSStaticFunction& lhs, const JSStaticFunction& rhs) HAL_NOEXCEPT {
      return ! (lhs == rhs);
    }
    
  }} // namespace HAL { namespace detail

#endif // _HAL_DETAIL_JSSTATICFUNCTION_HPP_
