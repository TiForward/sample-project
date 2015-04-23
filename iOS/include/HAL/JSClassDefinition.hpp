/**
 * Javascriptcorecpp
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_JSCLASSDEFINITION_HPP_
#define _HAL_JSCLASSDEFINITION_HPP_

#include "HAL/detail/JSBase.hpp"
#include "HAL/detail/JSStaticValue.hpp"
#include "HAL/detail/JSStaticFunction.hpp"

#include <string>
#include <vector>
#include <memory>

namespace HAL { namespace detail {
  template<typename T>
  class JSExportClass;
}}

namespace HAL {
  
  /*!
   @class
   
   @discussion A JSClassDefinition is an RAII wrapper around the
   JavaScriptCore C API struct of the same name (only in a different
   namespace). It defines the properties and callbacks that define a
   type of JavaScript object.
   
   This class is thread safe and immutable by design.
   */
  class HAL_EXPORT JSClassDefinition HAL_PERFORMANCE_COUNTER1(JSClassDefinition) {
  public:
    
    JSClassDefinition() HAL_NOEXCEPT;
    
    explicit JSClassDefinition(const ::JSClassDefinition& js_class_definition);
    
    /*!
     @method
     
     @abstract Return the name of this JSClassDefinition.
     
     @result The name of this JSClassDefinition.
     */
    virtual std::string get_name() const HAL_NOEXCEPT final;
    
    /*!
     @method
     
     @abstract Return the version number of this JSClassDefinition.
     
     @result The version number of this JSClassDefinition.
     */
    virtual std::uint32_t get_version() const HAL_NOEXCEPT final;
    
    virtual ~JSClassDefinition()                           HAL_NOEXCEPT;
    JSClassDefinition(const JSClassDefinition&)            HAL_NOEXCEPT;
    JSClassDefinition(JSClassDefinition&&)                 HAL_NOEXCEPT;
    JSClassDefinition& operator=(const JSClassDefinition&) HAL_NOEXCEPT;
    JSClassDefinition& operator=(JSClassDefinition&&)      HAL_NOEXCEPT;
    void swap(JSClassDefinition&)                          HAL_NOEXCEPT;
    
    virtual void Print() HAL_NOEXCEPT final;
    static  void Print(const ::JSClassDefinition& js_class_definition) HAL_NOEXCEPT;
    
  private:
    
    virtual void Initialize(const ::JSClassDefinition& other) HAL_NOEXCEPT final;
    virtual void InitializePropertyCallbacks() HAL_NOEXCEPT final;

    // Silence 4251 on Windows since private member variables do not
    // need to be exported from a DLL.
#pragma warning(push)
#pragma warning(disable: 4251)
    std::vector<detail::JSStaticValue>    js_value_properties__;
    std::vector<detail::JSStaticFunction> js_function_properties__;
#pragma warning(pop)
    
  protected:
    
    // JSClass and JSExportClass need access to js_class_definition__.
    friend class JSClass;
    
    template<typename T>
    friend class detail::JSExportClass;
    
    // Silence 4251 on Windows since private member variables do not
    // need to be exported from a DLL.
#pragma warning(push)
#pragma warning(disable: 4251)
    std::string                           name__;
    std::vector<::JSStaticValue>          static_values__;
    std::vector<::JSStaticFunction>       static_functions__;
    ::JSClassDefinition                   js_class_definition__;
#pragma warning(pop)
    
#undef  HAL_JSCLASSDEFINITION_LOCK_GUARD
#ifdef  HAL_THREAD_SAFE
    std::recursive_mutex mutex__;
#define HAL_JSCLASSDEFINITION_LOCK_GUARD std::lock_guard<std::recursive_mutex> lock(mutex__)
#else
#define HAL_JSCLASSDEFINITION_LOCK_GUARD
#endif  // HAL_THREAD_SAFE
  };
  
  inline
  void swap(JSClassDefinition& first, JSClassDefinition& second) HAL_NOEXCEPT {
    first.swap(second);
  }
  
} // namespace HAL {

#endif // _HAL_JSCLASSDEFINITION_HPP_
