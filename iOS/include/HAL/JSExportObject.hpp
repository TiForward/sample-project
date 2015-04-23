/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_JSEXPORTOBJECT_HPP_
#define _HAL_JSEXPORTOBJECT_HPP_

#include "HAL/JSExport.hpp"
#include "HAL/JSContext.hpp"
#include "HAL/JSString.hpp"
#include "HAL/JSValue.hpp"

#include <vector>
#include <unordered_set>

namespace HAL { namespace detail {
  template<typename T>
  class JSExportClass;
}}

namespace HAL {
  
  /*!
   @class
   
   @discussion A JSExportObject is a convenience base class for
   integrating your own C++ classes into JavaScriptCore.
   */
  class HAL_EXPORT JSExportObject : public JSExport<JSExportObject> HAL_PERFORMANCE_COUNTER2(JSExportObject) {
    
  public:
    

    /*!
     @method
     
     @abstract Return the execution context of this JavaScript value.
     
     @result The the execution context of this JavaScript value.
     */
    virtual JSContext get_context() const HAL_NOEXCEPT final;
    
    /*!
     @method
     
     @abstract Return the JSObject of this JavaScript value.
     
     @result The JSObject of this JavaScript value.
     */
    virtual JSObject get_object() HAL_NOEXCEPT final;
    
    JSExportObject(const JSContext& js_context) HAL_NOEXCEPT;
    
    virtual ~JSExportObject() HAL_NOEXCEPT;
    JSExportObject(const JSExportObject&)            = default;
    JSExportObject& operator=(const JSExportObject&) = default;
#ifdef HAL_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    JSExportObject(JSExportObject&&)                 = default;
    JSExportObject& operator=(JSExportObject&&)      = default;
#endif

    void swap(JSExportObject&) HAL_NOEXCEPT;
    
    static void JSExportInitialize();
		
    /*!
     @method
     
     @abstract constructor callback which is invoked when your
     JavaScript object is created

     @param js_object The JavaScript object which is being created
     */
    virtual void postInitialize(JSObject& js_object);

    /*!
     @method

     @abstract constructor callback which is invoked when your
     JavaScript object is created as the result of being called in a
     JavaScript 'new' expression.

     @param js_context The JSContext in which your JavaScript object
     is created.
	
     @param arguments An optional list of JSValues to initialize your
     JavaScript object with as the result of being called in a
     JavaScript 'new' expression.
    */
    virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments);
		
  private:
    
    JSContext js_context__;
    
#undef  HAL_JSEXPORTOBJECT_LOCK_GUARD
#ifdef  HAL_THREAD_SAFE
    std::recursive_mutex mutex__;
#define HAL_JSEXPORTOBJECT_LOCK_GUARD std::lock_guard<std::recursive_mutex> lock(mutex__)
#else
#define HAL_JSEXPORTOBJECT_LOCK_GUARD
#endif  // HAL_THREAD_SAFE
  };
  
  inline
  void swap(JSExportObject& first, JSExportObject& second) HAL_NOEXCEPT {
    first.swap(second);
  }
  
} // namespace HAL {

#endif // _HAL_JSEXPORTOBJECT_HPP_
