/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_DETAIL_JSPROPERTYNAMEACCUMULATOR_HPP_
#define _HAL_DETAIL_JSPROPERTYNAMEACCUMULATOR_HPP_

#include "HAL/detail/JSBase.hpp"
#include "HAL/JSString.hpp"
#include <iostream>
#include <cassert>

namespace HAL {
  
  class JSObject;
  
  namespace detail {
    template<typename T>
    class JSExportClass;
  }}

namespace HAL {
  
  /*!
   @class
   
   @discussion A JSPropertyNameAccumulator is an RAII wrapper around a
   JSPropertyNameAccumulatorRef, the JavaScriptCore C API
   representation of a JavaScript property name accumulator which is
   an ordered set used to collect the names of a JavaScript object's
   properties
   */
  class JSPropertyNameAccumulator HAL_PERFORMANCE_COUNTER2(JSPropertyNameAccumulator) {
      
    public:
      
      JSPropertyNameAccumulator()                                            = delete;
      ~JSPropertyNameAccumulator()                                           = default;
      JSPropertyNameAccumulator(const JSPropertyNameAccumulator&)            = delete;
      JSPropertyNameAccumulator(JSPropertyNameAccumulator&&)                 = delete;
      JSPropertyNameAccumulator& operator=(const JSPropertyNameAccumulator&) = delete;
      JSPropertyNameAccumulator& operator=(JSPropertyNameAccumulator&&)      = delete;
      
      
      /*!
       @method
       
       @abstract Adds a property name to a JavaScript property name
       accumulator.
       
       @param property_name The property name to add.
       */
      void AddName(const JSString& property_name) const {
        JSPropertyNameAccumulatorAddName(js_property_name_accumulator_ref__, static_cast<JSStringRef>(property_name));
      }
      
    private:
      
      // Only a JSObject and a JSExportClass can create a
      // JSPropertyNameAccumulator.
      friend class JSObject;
      
      template<typename T>
      friend class detail::JSExportClass;
      
      // For interoperability with the JavaScriptCore C API.
      explicit JSPropertyNameAccumulator(const JSPropertyNameAccumulatorRef& js_property_name_accumulator_ref)
      : js_property_name_accumulator_ref__(js_property_name_accumulator_ref) {
        assert(js_property_name_accumulator_ref__);
      }
      
      // For interoperability with the JavaScriptCore C API.
      operator JSPropertyNameAccumulatorRef() const {
        return js_property_name_accumulator_ref__;
      }
      
      JSPropertyNameAccumulatorRef js_property_name_accumulator_ref__;
    };
    
  } // namespace HAL {
  
#endif // _HAL_DETAIL_JSPROPERTYNAMEACCUMULATOR_HPP_
