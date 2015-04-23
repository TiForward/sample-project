/**
 * Javascriptcorecpp
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_JSCLASS_HPP_
#define _HAL_JSCLASS_HPP_

#include "HAL/detail/JSBase.hpp"
#include "HAL/JSClassDefinition.hpp"

#include <string>
#include <vector>
#include <cstdint>
#include <memory>


namespace HAL { namespace detail {
  template<typename T>
  class JSExportClassDefinition;
  
  template<typename T>
  class JSExportClassDefinitionBuilder;
}}

namespace HAL {
  
  /*!
   @class
   
   @discussion A JSClass is an RAII wrapper around a JSClassRef, the
   JavaScriptCore C API representation of a JavaScript class that
   defines JavaScript objects implemented in C.
   
   A JSClass wraps a C++ class and seamlessly integrates it into the
   JavaScriptCore runtime.  The only way to create a JSClass is
   through the use of a JSClassBuilder, so please see that class for
   more details.
   
   An instance of JSClass may be passed to the JSContextGroup
   constructor to create a custom JavaScript global object for all
   contexts in that group.
   */
  class HAL_EXPORT JSClass HAL_PERFORMANCE_COUNTER1(JSClass) {
  public:
    
    /*!
     @method
     
     @abstract Return an empty JSClass.
     
     @result An empty JSClass.
     */
    JSClass() HAL_NOEXCEPT;
    
    /*!
     @method
     
     @abstract Return a JSClass defined by the given JSClassDefinition.
     
     @result A JSClass defined by the given JSClassDefinition.
     */
    JSClass(const JSClassDefinition& js_class_definition) HAL_NOEXCEPT;
    
    /*!
     @method
     
     @abstract Return the name of this JSClass.
     
     @result The name of this JSClass.
     */
    virtual std::string get_name() const HAL_NOEXCEPT final {
      return name__;
    }
    
    virtual ~JSClass()          HAL_NOEXCEPT;
    JSClass(const JSClass&)     HAL_NOEXCEPT;
    JSClass(JSClass&&)          HAL_NOEXCEPT;
    JSClass& operator=(JSClass) HAL_NOEXCEPT;
    void swap(JSClass&)         HAL_NOEXCEPT;
    
  private:
    
    // These five classes need access to operator JSClassRef().
    friend class JSContext; // for constructor
    friend class JSValue;   // for IsObjectOfClass
    friend class JSObject;  // for constructor
    
    // For setting JSClassDefinition.parentClass
    template<typename T>
    friend class detail::JSExportClassDefinition;
    
    // For setting JSClassDefinition.parentClass
    template<typename T>
    friend class detail::JSExportClassDefinitionBuilder;
    
    explicit operator JSClassRef() const HAL_NOEXCEPT {
      return js_class_ref__;
    }
    
    // Silence 4251 on Windows since private member variables do not
    // need to be exported from a DLL.
#pragma warning(push)
#pragma warning(disable: 4251)
    std::string name__;
    JSClassRef  js_class_ref__ { nullptr };
#pragma warning(pop)
    
  protected:
    
#undef  HAL_JSCLASS_LOCK_GUARD
#ifdef  HAL_THREAD_SAFE
    std::recursive_mutex mutex__;
#define HAL_JSCLASS_LOCK_GUARD std::lock_guard<std::recursive_mutex> lock(mutex__)
#else
#define HAL_JSCLASS_LOCK_GUARD
#endif  // HAL_THREAD_SAFE
  };
  
  inline
  void swap(JSClass& first, JSClass& second) HAL_NOEXCEPT {
    first.swap(second);
  }
  
} // namespace HAL {

#endif // _HAL_JSCLASS_HPP_
