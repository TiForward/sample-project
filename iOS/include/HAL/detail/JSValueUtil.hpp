/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_DETAIL_JSVALUEUTIL_HPP_
#define _HAL_DETAIL_JSVALUEUTIL_HPP_

#include "HAL/detail/JSBase.hpp"
#include "HAL/JSValue.hpp"
#include <string>
#include <JavaScriptCore/JavaScript.h>

namespace HAL { namespace detail {
  
  HAL_EXPORT JSValue::Type ToJSValueType(JSType type) HAL_NOEXCEPT;
  
}} // namespace HAL { namespace detail {

#endif // _HAL_DETAIL_JSVALUEUTIL_HPP_
