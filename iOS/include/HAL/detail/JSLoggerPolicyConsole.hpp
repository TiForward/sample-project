/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_DETAIL_JSLOGGERPOLICYCONSOLE_HPP_
#define _HAL_DETAIL_JSLOGGERPOLICYCONSOLE_HPP_

#include "HAL/detail/JSLoggerPolicyInterface.hpp"
#include <iostream>

namespace HAL { namespace detail {
  
  class HAL_EXPORT JSLoggerPolicyConsole final : public JSLoggerPolicyInterface {
  public:
    
    JSLoggerPolicyConsole(const std::string& name) {
    }
    
    JSLoggerPolicyConsole()                                        = delete;
    ~JSLoggerPolicyConsole()                                       = default;
    JSLoggerPolicyConsole(const JSLoggerPolicyConsole&)            = default;
    JSLoggerPolicyConsole& operator=(const JSLoggerPolicyConsole&) = default;
    
#ifdef HAL_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    JSLoggerPolicyConsole(JSLoggerPolicyConsole&&)                 = default;
    JSLoggerPolicyConsole& operator=(JSLoggerPolicyConsole&&)      = default;
#endif
    
    virtual void Write(const std::string& log_message) override final {
      std::clog << log_message << std::endl;
      }
  };
      
}} // namespace HAL { namespace detail {
      
#endif // _HAL_DETAIL_JSLOGGERPOLICYCONSOLE_HPP_
