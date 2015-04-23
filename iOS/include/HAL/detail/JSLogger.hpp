/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_DETAIL_JSLOGGER_HPP_
#define _HAL_DETAIL_JSLOGGER_HPP_

#include "HAL/detail/JSLoggerPimpl.hpp"
#include "HAL/detail/JSLoggerPolicyConsole.hpp"
#include "HAL/detail/JSLoggerPolicyFile.hpp"
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <mutex>
#include <memory>

namespace HAL { namespace detail {
  
  // The JSLogger infrastructure was inspired by this Dr. Dobbs article:
  //
  // A Lightweight Logger for C++
  // By Filip Janiszewski, January 31, 2013
  // http://www.drdobbs.com/cpp/a-lightweight-logger-for-c/240147505
  
  /*!
   @class
   
   @abstract The logging infrastructure used by the HAL
   library.
   
   @discussion Here is an example of how to use the HAL
   logging facility:
   
   HAL_LOG_DEBUG("Before loop.");
   for (short i = 0 ; i < 3 ; ++i) {
     HAL_LOG_DEBUG("The value of 'i' is ", i , ". " , 3 - i - 1 , " more iterations left ");
   }
   HAL_LOG_WARN("After loop.");
   HAL_LOG_ERROR("All good things come to an end.");
   */
  
  enum class HAL_EXPORT JSLoggerSeverityType {
    JS_TRACE,
    JS_DEBUG,
    JS_INFO,
    JS_WARN,
    JS_ERROR
  };
  
  template<typename JSLoggerPolicy>
  class JSLogger final {
    
  public:
    
    static std::shared_ptr<JSLogger<JSLoggerPolicy>> Instance();
    
    JSLogger()                           = delete;
    JSLogger(const JSLogger&)            = delete;
    JSLogger& operator=(const JSLogger&) = delete;
    
#ifdef HAL_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    JSLogger(JSLogger&&)                 = delete;
    JSLogger& operator=(JSLogger&&)      = delete;
#endif
    
    template<JSLoggerSeverityType severity, typename...Args>
    void Print(Args...args);
    
  private:
    
    JSLogger(const std::string& name);
    ~JSLogger() = default;
    
    // Core printing functionality.
    void PrintImpl();
    
    template<typename First, typename...Rest>
    void PrintImpl(First first_parameter, Rest...rest);
    
    // This struct only exists so that a custom deleter can be passed to
    // std::shared_ptr<JSLogger<T>> while keeping the JSLogger<T> destructor
    // private.
    struct deleter {
      void operator()(JSLogger* ptr) {
        delete ptr;
      }
    };

    JSLoggerPolicy       js_log_policy__;
    uint32_t             log_line_number__ { 0 };
    std::ostringstream   log_stream__;
    std::mutex           js_logger_mutex__;
    //std::recursive_mutex js_logger_mutex__;
  };
  
  template<typename JSLoggerPolicy>
  JSLogger<JSLoggerPolicy>::JSLogger(const std::string& name)
  : js_log_policy__(name) {
  }
  
  template<typename JSLoggerPolicy>
  std::shared_ptr<JSLogger<JSLoggerPolicy>> JSLogger<JSLoggerPolicy>::Instance() {
    static std::shared_ptr<JSLogger<JSLoggerPolicy>> instance;
    static std::once_flag of;
    std::call_once(of, [] {
      instance = std::shared_ptr<JSLogger<JSLoggerPolicy>>(new JSLogger<JSLoggerPolicy>("HAL.log"), deleter{});
    });
    
    return instance;
  }

  template<typename JSLoggerPolicy>
  template<JSLoggerSeverityType severity, typename...Args>
  void JSLogger<JSLoggerPolicy>::Print(Args...args)  {
    std::lock_guard<std::mutex> lock(js_logger_mutex__);
    
    // The Debug and Error severity strings (i.e. "DEBUG" and "ERROR")
    // are the longest of the three severity strings, and each is 5
    // characters long. Since we want all of the severity types to have
    // the same width on output, we set it to 5.
    log_stream__ << std::setw(5) << std::left;
    
    switch(severity) {
      case JSLoggerSeverityType::JS_TRACE:
        log_stream__ << "TRACE: ";
        break;
      case JSLoggerSeverityType::JS_DEBUG:
        log_stream__ << "DEBUG: ";
        break;
      case JSLoggerSeverityType::JS_INFO:
        log_stream__ << "INFO: ";
        break;
      case JSLoggerSeverityType::JS_WARN:
        log_stream__ << "WARN: ";
        break;
      case JSLoggerSeverityType::JS_ERROR:
        log_stream__ << "ERROR: ";
        break;
    };
    
    PrintImpl(args...);
  }
  
  template<typename JSLoggerPolicy>
  void JSLogger<JSLoggerPolicy>::PrintImpl() {
    js_log_policy__.Write(JSLoggerPimpl::GetLoglineHeader(log_line_number__++) + log_stream__.str() + ".");
    log_stream__.str("");
  }
  
  template<typename JSLoggerPolicy>
  template<typename First, typename...Rest >
  void JSLogger<JSLoggerPolicy>::PrintImpl(First first_parameter, Rest...rest) {
    log_stream__ << first_parameter;
    PrintImpl(rest...);
  }
  
// TODO: Add a more flexible way to specify the logging policy.
//using JSLogger_t = JSLogger<JSLoggerPolicyFile>;
using JSLogger_t = JSLogger<JSLoggerPolicyConsole>;

#ifdef HAL_LOGGING_ENABLE_TRACE
#define HAL_LOG_TRACE HAL::detail::JSLogger_t::Instance() -> Print<HAL::detail::JSLoggerSeverityType::JS_TRACE>
#else
#define HAL_LOG_TRACE(...)
#endif

#ifdef HAL_LOGGING_ENABLE_DEBUG
#define HAL_LOG_DEBUG HAL::detail::JSLogger_t::Instance() -> Print<HAL::detail::JSLoggerSeverityType::JS_DEBUG>
#else
#define HAL_LOG_DEBUG(...)
#endif

#ifdef HAL_LOGGING_ENABLE_INFO
#define HAL_LOG_INFO  HAL::detail::JSLogger_t::Instance() -> Print<HAL::detail::JSLoggerSeverityType::JS_INFO>
#else
#define HAL_LOG_INFO(...)
#endif

#ifdef HAL_LOGGING_ENABLE_WARN
#define HAL_LOG_WARN  HAL::detail::JSLogger_t::Instance() -> Print<HAL::detail::JSLoggerSeverityType::JS_WARN>
#else
#define HAL_LOG_WARN(...)
#endif

#ifdef HAL_LOGGING_ENABLE_ERROR
#define HAL_LOG_ERROR HAL::detail::JSLogger_t::Instance() -> Print<HAL::detail::JSLoggerSeverityType::JS_ERROR>
#else
#define HAL_LOG_ERROR(...)
#endif

}} // namespace HAL { namespace detail {

#endif // _HAL_DETAIL_JSLOGGER_HPP_
