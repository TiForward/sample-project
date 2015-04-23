/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_DETAIL_JSLOGGERPIMPL_HPP_
#define _HAL_DETAIL_JSLOGGERPIMPL_HPP_

#include "HAL_EXPORT.h"
#include <string>
#include <cstdint>

namespace HAL {
  template<typename JSLoggerPolicy>
  class JSLogger;
}

namespace HAL { namespace detail {
  
  class HAL_EXPORT JSLoggerPimpl final {
    
  public:
    
    JSLoggerPimpl()                                = delete;
    ~JSLoggerPimpl()                               = delete;
    JSLoggerPimpl(const JSLoggerPimpl&)            = delete;
    JSLoggerPimpl(JSLoggerPimpl&&)                 = delete;
    JSLoggerPimpl& operator=(const JSLoggerPimpl&) = delete;
    JSLoggerPimpl& operator=(JSLoggerPimpl&&)      = delete;
    
    static std::string GetLoglineHeader(uint32_t log_line_number);
  };
  
}} // namespace HAL { namespace detail

#endif // _HAL_DETAIL_JSLOGGERPIMPL_HPP_

