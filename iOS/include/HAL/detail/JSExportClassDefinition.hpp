/**
 * Javascriptcorecpp
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_DETAIL_JSEXPORTCLASSDEFINITION_HPP_
#define _HAL_DETAIL_JSEXPORTCLASSDEFINITION_HPP_

#include "HAL/detail/JSBase.hpp"
#include "HAL/JSClassDefinition.hpp"
#include "HAL/JSClassAttribute.hpp"

#include "HAL/detail/JSExportNamedValuePropertyCallback.hpp"
#include "HAL/detail/JSExportNamedFunctionPropertyCallback.hpp"
#include "HAL/detail/JSExportCallbacks.hpp"

#include <string>
#include <unordered_map>

namespace HAL { namespace detail {
  
  template<typename T>
  using JSExportNamedValuePropertyCallbackMap_t    = std::unordered_map<std::string, JSExportNamedValuePropertyCallback<T>>;
  
  template<typename T>
  using JSExportNamedFunctionPropertyCallbackMap_t = std::unordered_map<std::string, JSExportNamedFunctionPropertyCallback<T>>;
  
  template<typename T>
  class JSExportClassDefinitionBuilder;
  
  template<typename T>
  class JSExportClass;

  /*!
   @class
   
   @discussion A JSExportClassDefinition defines the properties and
   callbacks of a JavaScript object implemented by a C++ classed
   derived from JSExport.
   
   The only way to create a JSExportClassDefinition is by using a
   JSExportClassDefinitionBuilder.
   
   This class is thread safe and immutable by design.
   */
  template<typename T>
  class JSExportClassDefinition final : public JSClassDefinition HAL_PERFORMANCE_COUNTER2(JSExportClassDefinition<T>) {
  public:
    
    JSExportClassDefinition(const JSExportClassDefinitionBuilder<T>& builder);
    JSExportClassDefinition()                                          = default;
    ~JSExportClassDefinition()                                         = default;
    JSExportClassDefinition(const JSExportClassDefinition&)            HAL_NOEXCEPT;
    JSExportClassDefinition(JSExportClassDefinition&&)                 HAL_NOEXCEPT;
    JSExportClassDefinition& operator=(const JSExportClassDefinition&) HAL_NOEXCEPT;
    JSExportClassDefinition& operator=(JSExportClassDefinition&&)      HAL_NOEXCEPT;
    void swap(JSExportClassDefinition&)                                HAL_NOEXCEPT;
    
  private:
    
    void InitializeNamedPropertyCallbacks() HAL_NOEXCEPT;

    // Only JSExportClass can access our private member variables.
    template<typename U>
    friend class JSExportClass;
    
    JSExportNamedValuePropertyCallbackMap_t<T>    named_value_property_callback_map__;
    JSExportNamedFunctionPropertyCallbackMap_t<T> named_function_property_callback_map__;
    HasPropertyCallback<T>                        has_property_callback__        { nullptr };
    GetPropertyCallback<T>                        get_property_callback__        { nullptr };
    SetPropertyCallback<T>                        set_property_callback__        { nullptr };
    DeletePropertyCallback<T>                     delete_property_callback__     { nullptr };
    GetPropertyNamesCallback<T>                   get_property_names_callback__  { nullptr };
    CallAsFunctionCallback<T>                     call_as_function_callback__    { nullptr };
    ConvertToTypeCallback<T>                      convert_to_type_callback__     { nullptr };
  };
  
  template<typename T>
  JSExportClassDefinition<T>::JSExportClassDefinition(const JSExportClassDefinition<T>& rhs) HAL_NOEXCEPT
  : JSClassDefinition(rhs)
  , named_value_property_callback_map__(rhs.named_value_property_callback_map__)
  , named_function_property_callback_map__(rhs.named_function_property_callback_map__)
  , has_property_callback__(rhs.has_property_callback__)
  , get_property_callback__(rhs.get_property_callback__)
  , set_property_callback__(rhs.set_property_callback__)
  , delete_property_callback__(rhs.delete_property_callback__)
  , get_property_names_callback__(rhs.get_property_names_callback__)
  , call_as_function_callback__(rhs.call_as_function_callback__)
  , convert_to_type_callback__(rhs.convert_to_type_callback__) {
    InitializeNamedPropertyCallbacks();
    
//    std::clog << "MDL: copy ctor" << std::endl;
//    Print();
  }
  
  template<typename T>
  JSExportClassDefinition<T>::JSExportClassDefinition(JSExportClassDefinition<T>&& rhs) HAL_NOEXCEPT
  : JSClassDefinition(rhs)
  , named_value_property_callback_map__(std::move(rhs.named_value_property_callback_map__))
  , named_function_property_callback_map__(std::move(rhs.named_function_property_callback_map__))
  , has_property_callback__(std::move(rhs.has_property_callback__))
  , get_property_callback__(std::move(rhs.get_property_callback__))
  , set_property_callback__(std::move(rhs.set_property_callback__))
  , delete_property_callback__(std::move(rhs.delete_property_callback__))
  , get_property_names_callback__(std::move(rhs.get_property_names_callback__))
  , call_as_function_callback__(std::move(rhs.call_as_function_callback__))
  , convert_to_type_callback__(std::move(rhs.convert_to_type_callback__)) {
    InitializeNamedPropertyCallbacks();
    
//    std::clog << "MDL: move ctor" << std::endl;
//    Print();
  }
  
  template<typename T>
  JSExportClassDefinition<T>& JSExportClassDefinition<T>::operator=(const JSExportClassDefinition<T>& rhs) HAL_NOEXCEPT {
    HAL_JSCLASSDEFINITION_LOCK_GUARD;
    JSClassDefinition::operator=(rhs);
    named_value_property_callback_map__    = rhs.named_value_property_callback_map__;
    named_function_property_callback_map__ = rhs.named_function_property_callback_map__;
    has_property_callback__                = rhs.has_property_callback__;
    get_property_callback__                = rhs.get_property_callback__;
    set_property_callback__                = rhs.set_property_callback__;
    delete_property_callback__             = rhs.delete_property_callback__;
    get_property_names_callback__          = rhs.get_property_names_callback__;
    call_as_function_callback__            = rhs.call_as_function_callback__;
    convert_to_type_callback__             = rhs.convert_to_type_callback__;
    InitializeNamedPropertyCallbacks();
    
//    std::clog << "MDL: copy assignment" << std::endl;
//    Print();
    
    return *this;
    }
    
    template<typename T>
    JSExportClassDefinition<T>& JSExportClassDefinition<T>::operator=(JSExportClassDefinition<T>&& rhs) HAL_NOEXCEPT {
      HAL_JSCLASSDEFINITION_LOCK_GUARD;
      swap(rhs);
      InitializeNamedPropertyCallbacks();
      
//      std::clog << "MDL: move assignment" << std::endl;
//      Print();
      
      return *this;
    }
    
    template<typename T>
    void JSExportClassDefinition<T>::swap(JSExportClassDefinition<T>& other) HAL_NOEXCEPT {
      HAL_JSCLASSDEFINITION_LOCK_GUARD;
      JSClassDefinition::swap(other);
      using std::swap;
      
      // By swapping the members of two classes, the two classes are
      // effectively swapped.
      swap(named_value_property_callback_map__   , other.named_value_property_callback_map__);
      swap(named_function_property_callback_map__, other.named_function_property_callback_map__);
      swap(has_property_callback__               , other.has_property_callback__);
      swap(get_property_callback__               , other.get_property_callback__);
      swap(set_property_callback__               , other.set_property_callback__);
      swap(delete_property_callback__            , other.delete_property_callback__);
      swap(get_property_names_callback__         , other.get_property_names_callback__);
      swap(call_as_function_callback__           , other.call_as_function_callback__);
      swap(convert_to_type_callback__            , other.convert_to_type_callback__);
    }
    
    template<typename T>
    void swap(JSExportClassDefinition<T>& first, JSExportClassDefinition<T>& second) HAL_NOEXCEPT {
      first.swap(second);
    }
    
    template<typename T>
    void JSExportClassDefinition<T>::InitializeNamedPropertyCallbacks() HAL_NOEXCEPT {
      
      // Initialize staticValues.
      static_values__.clear();
      js_class_definition__.staticValues = nullptr;
      if (!named_value_property_callback_map__.empty()) {
        for (const auto& entry : named_value_property_callback_map__) {
          const auto& property_name       = entry.first;
          const auto& property_attributes = entry.second.get_attributes();
          ::JSStaticValue static_value;
          static_value.name        = property_name.c_str();
          static_value.getProperty = JSExportClass<T>::GetNamedValuePropertyCallback;
          static_value.setProperty = JSExportClass<T>::SetNamedValuePropertyCallback;
          static_value.attributes  = ToJSPropertyAttributes(property_attributes);
          static_values__.push_back(static_value);
          // HAL_LOG_DEBUG("JSExportClassDefinition<", name__, "> added value property ", static_values__.back().name);
        }
        static_values__.push_back({nullptr, nullptr, nullptr, kJSPropertyAttributeNone});
        js_class_definition__.staticValues = &static_values__[0];
      }
      
      // Initialize staticFunctions.
      static_functions__.clear();
      js_class_definition__.staticFunctions = nullptr;
      if (!named_function_property_callback_map__.empty()) {
        for (const auto& entry : named_function_property_callback_map__) {
          const auto& function_name = entry.first;
          const auto& property_attributes = entry.second.get_attributes();
          ::JSStaticFunction static_function;
          static_function.name           = function_name.c_str();
          static_function.callAsFunction = JSExportClass<T>::CallNamedFunctionCallback;
          static_function.attributes     = ToJSPropertyAttributes(property_attributes);
          static_functions__.push_back(static_function);
          // HAL_LOG_DEBUG("JSExportClassDefinition<", name__, "> added function property ", static_functions__.back().name);
        }
        static_functions__.push_back({nullptr, nullptr, kJSPropertyAttributeNone});
        js_class_definition__.staticFunctions = &static_functions__[0];
      }
    }
    
    }} // namespace HAL { namespace detail {
    
#endif // _HAL_DETAIL_JSEXPORTCLASSDEFINITION_HPP_
