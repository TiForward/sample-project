/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_DETAIL_JSLOGGERPOLICYINTERFACE_HPP_
#define _HAL_DETAIL_JSLOGGERPOLICYINTERFACE_HPP_

#include "HAL_EXPORT.h"

namespace HAL { namespace detail {
  
  class HAL_EXPORT JSLoggerPolicyInterface {
  public:
    
    JSLoggerPolicyInterface()                                          = default;
    virtual ~JSLoggerPolicyInterface()                                 = default;
    JSLoggerPolicyInterface(const JSLoggerPolicyInterface&)            = default;
    JSLoggerPolicyInterface& operator=(const JSLoggerPolicyInterface&) = default;
    
#ifdef HAL_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    JSLoggerPolicyInterface(JSLoggerPolicyInterface&&)                 = default;
    JSLoggerPolicyInterface& operator=(JSLoggerPolicyInterface&&)      = default;
#endif
    
    virtual void Write(const std::string& log_message) = 0;
  };
  
}} // namespace HAL { namespace detail {

#endif // _HAL_DETAIL_JSLOGGERPOLICYINTERFACE_HPP_
