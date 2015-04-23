/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_DETAIL_JSUTIL_HPP_
#define _HAL_DETAIL_JSUTIL_HPP_

#include "HAL/detail/JSBase.hpp"
#include "HAL/JSPropertyAttribute.hpp"
#include "HAL/JSClassAttribute.hpp"
#include "HAL/JSValue.hpp"

#include <string>
#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_set>

#include <JavaScriptCore/JavaScript.h>

namespace HAL {
  class JSString;
  class JSContext;
  class JSError;
}

namespace HAL { namespace detail {
  
  template<typename T, typename... Ts>
  std::unique_ptr<T> make_unique(Ts&&... params) {
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
  }

  class js_runtime_error : public std::runtime_error {
  public:
    js_runtime_error() HAL_NOEXCEPT = default;
    js_runtime_error(const JSError& js_error);
    virtual ~js_runtime_error() = default;

    std::string js_name() const {
      return js_name__;
    }
    std::string js_message() const {
      return js_message__;
    }
    std::string js_filename() const {
      return js_filename__;
    }
    std::uint32_t js_linenumber() const {
      return js_linenumber__;
    }
    std::vector<JSValue> js_stack() const {
      return js_stack__;
    }
  private:
    std::string js_name__;
    std::string js_message__;
    std::string js_filename__;
    std::uint32_t js_linenumber__;
    std::vector<JSValue> js_stack__;
  };

  HAL_EXPORT void    ThrowRuntimeError(const std::string& internal_component_name, const std::string& message);
  HAL_EXPORT void    ThrowRuntimeError(const std::string& internal_component_name, const JSValue&     exception, const std::string& source_url = "", int line_number = 0);
  HAL_EXPORT void ThrowInvalidArgument(const std::string& internal_component_name, const std::string& message  );
  
  // For interoperability with the JavaScriptCore C API.
  HAL_EXPORT std::vector<JSValue>     to_vector(const JSContext&, size_t count, const JSValueRef[]);
  HAL_EXPORT std::vector<JSValue>     to_vector(const JSContext&, const std::vector<JSString>&);
  HAL_EXPORT std::vector<JSValueRef>  to_vector(const std::vector<JSValue>&);
  HAL_EXPORT std::vector<JSStringRef> to_vector(const std::vector<JSString>&);
  
  // For interoperability with the JavaScriptCore C API.
  
  // typedef unsigned JSPropertyAttributes
  HAL_EXPORT unsigned ToJSPropertyAttributes(const std::unordered_set<JSPropertyAttribute>& attributes)          HAL_NOEXCEPT;
  HAL_EXPORT std::unordered_set<JSPropertyAttribute> FromJSPropertyAttributes(::JSPropertyAttributes attributes) HAL_NOEXCEPT;
  HAL_EXPORT std::string to_string(JSPropertyAttribute)                                                          HAL_NOEXCEPT;
  HAL_EXPORT std::string to_string(const std::unordered_set<JSPropertyAttribute>& attributes)                    HAL_NOEXCEPT;
  HAL_EXPORT std::string to_string_JSPropertyAttributes(::JSPropertyAttributes attributes)                       HAL_NOEXCEPT;
  
  HAL_EXPORT unsigned ToJSClassAttribute(JSClassAttribute attribute)                                             HAL_NOEXCEPT;
  HAL_EXPORT std::unordered_set<JSClassAttribute> FromJSClassAttributes(::JSClassAttributes attributes)          HAL_NOEXCEPT;
  HAL_EXPORT std::string to_string(JSClassAttribute)                                                             HAL_NOEXCEPT;
  HAL_EXPORT std::string to_string(const std::unordered_set<JSClassAttribute>& attributes)                       HAL_NOEXCEPT;
  HAL_EXPORT std::string to_string_JSClassAttributes(::JSClassAttributes attributes)                             HAL_NOEXCEPT;

  // This in the ToInt32 operation as defined in section 9.5 of the
  // ECMA-262 spec. Note that this operation is identical to ToUInt32
  // other than to interpretation of the resulting bit-pattern (as
  // such this method is also called to implement ToUInt32).
  //
  // The operation can be descibed as round towards zero, then select
  // the 32 least bits of the resulting value in 2s-complement
  // representation.
  HAL_EXPORT int32_t to_int32_t(double number);
  
}} // namespace HAL { namespace detail {

#endif // _HAL_DETAIL_JSUTIL_HPP_
