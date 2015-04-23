/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_DETAIL_JSLOGGERPOLICYFILE_HPP_
#define _HAL_DETAIL_JSLOGGERPOLICYFILE_HPP_

#include "HAL/detail/JSLoggerPolicyInterface.hpp"
#include <fstream>

namespace HAL { namespace detail {
  
  class HAL_EXPORT JSLoggerPolicyFile final : public JSLoggerPolicyInterface {
  public:
    
    JSLoggerPolicyFile(const std::string& name) {
      ofstream__.open(name, std::ios_base::binary | std::ios_base::out);
      if(!ofstream__.is_open() ) {
        throw(std::runtime_error("JSLoggerPolicyFile: Unable to open an output stream"));
      }
    }
    
    ~JSLoggerPolicyFile() {
      ofstream__.close();
    }
    
    JSLoggerPolicyFile()                                     = delete;
    JSLoggerPolicyFile(const JSLoggerPolicyFile&)            = default;
    JSLoggerPolicyFile& operator=(const JSLoggerPolicyFile&) = default;
    
#ifdef HAL_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    JSLoggerPolicyFile(JSLoggerPolicyFile&&)                 = default;
    JSLoggerPolicyFile& operator=(JSLoggerPolicyFile&&)      = default;
#endif
    
    virtual void Write(const std::string& log_message) override final {
      ofstream__ << log_message << std::endl;
      }
      
    private:
      
    // Silence 4251 on Windows since private member variables do not
    // need to be exported from a DLL.
#pragma warning(push)
#pragma warning(disable: 4251)
      std::ofstream ofstream__;
#pragma warning(pop)
  };
      
}} // namespace HAL { namespace detail {
      
#endif // _HAL_DETAIL_JSLOGGERPOLICYFILE_HPP_
