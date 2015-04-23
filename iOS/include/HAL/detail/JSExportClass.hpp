/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_DETAIL_JSEXPORTCLASS_HPP_
#define _HAL_DETAIL_JSEXPORTCLASS_HPP_

#include "HAL/detail/JSBase.hpp"
#include "HAL/JSClass.hpp"
#include "HAL/detail/JSExportClassDefinition.hpp"

#include "HAL/JSString.hpp"
#include "HAL/JSValue.hpp"
#include "HAL/JSObject.hpp"
#include "HAL/JSNumber.hpp"
#include "HAL/JSError.hpp"
#include "HAL/JSArray.hpp"

#include "HAL/detail/JSPropertyNameAccumulator.hpp"
#include "HAL/detail/JSUtil.hpp"
#include "HAL/detail/JSValueUtil.hpp"

#include <string>
#include <regex>
#include <cstdint>
#include <vector>
#include <memory>
#include <utility>
#include <typeinfo>
#include <typeindex>

namespace HAL {
  template<typename T>
  class JSExport;
}

namespace HAL { namespace detail {
  
  
  template<typename T>
  class JSExportClassDefinitionBuilder;
  
  template<typename T>
  class JSExportClassDefinition;
  
  /*!
   @class
   
   @discussion A JSExportClass is an RAII wrapper around a JSClassRef,
   the JavaScriptCore C API representation of a JavaScript class. A
   JSExportClass defines JavaScript objects implemented by a C++
   class.
   
   This class is thread-safe and lock-free by design.
   */
  template<typename T>
  class JSExportClass final : public JSClass HAL_PERFORMANCE_COUNTER2(JSExportClass<T>) {
    
  public:
    
    JSExportClass(const JSExportClassDefinition<T>& js_export_class_definition) HAL_NOEXCEPT;
    
    JSExportClass()                                HAL_NOEXCEPT;//= default;
    ~JSExportClass()                               HAL_NOEXCEPT;//= default;
    JSExportClass(const JSExportClass&)            = default;
    JSExportClass& operator=(const JSExportClass&) = default;
    
#ifdef HAL_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    JSExportClass(JSExportClass&&)                 = default;
    JSExportClass& operator=(JSExportClass&&)      = default;
#endif

  private:
    
    void Print() const;
    
    // JSExportClassDefinitionBuilder needs access in order to take
    // the address of our non-static functions that implement the
    // JSExport callbacks.
    template<typename U>
    friend class JSExportClassDefinition;
    
    // JSExportClassDefinitionBuilder needs access in order to take
    // the address of our static functions that implement the
    // JavaScriptCore C API callbacks.
    template<typename U>
    friend class JSExportClassDefinitionBuilder;
    
    // Support for JSStaticValue
    static JSValueRef  GetNamedValuePropertyCallback(JSContextRef context_ref, JSObjectRef object_ref, JSStringRef property_name_ref, JSValueRef* exception);
    static bool        SetNamedValuePropertyCallback(JSContextRef context_ref, JSObjectRef object_ref, JSStringRef property_name_ref, JSValueRef value_ref, JSValueRef* exception);
    
    // Support for JSStaticFunction
    static JSValueRef  CallNamedFunctionCallback(JSContextRef context_ref, JSObjectRef function_ref, JSObjectRef this_object_ref, size_t argument_count, const JSValueRef arguments_array[], JSValueRef* exception);
    
    // JavaScriptCore C API callback interface.
    static void        JSObjectInitializeCallback(JSContextRef context_ref, JSObjectRef object_ref);
    static void        JSObjectFinalizeCallback(JSObjectRef object_ref);
    static bool        JSObjectHasPropertyCallback(JSContextRef context_ref, JSObjectRef object_ref, JSStringRef property_name_ref);
    static JSValueRef  JSObjectGetPropertyCallback(JSContextRef context_ref, JSObjectRef object_ref, JSStringRef property_name_ref, JSValueRef* exception);
    static bool        JSObjectSetPropertyCallback(JSContextRef context_ref, JSObjectRef object_ref, JSStringRef property_name_ref, JSValueRef value_ref, JSValueRef* exception);
    static bool        JSObjectDeletePropertyCallback(JSContextRef context_ref, JSObjectRef object_ref, JSStringRef property_name_ref, JSValueRef* exception);
    static void        JSObjectGetPropertyNamesCallback(JSContextRef context_ref, JSObjectRef object_ref, JSPropertyNameAccumulatorRef property_names);
    static JSValueRef  JSObjectCallAsFunctionCallback(JSContextRef context_ref, JSObjectRef function_ref, JSObjectRef this_object_ref, size_t argument_count, const JSValueRef arguments_array[], JSValueRef* exception);
    static JSObjectRef JSObjectCallAsConstructorCallback(JSContextRef context_ref, JSObjectRef constructor_ref, size_t argument_count, const JSValueRef arguments_array[], JSValueRef* exception);
    static bool        JSObjectHasInstanceCallback(JSContextRef context_ref, JSObjectRef constructor_ref, JSValueRef possible_instance_ref, JSValueRef* exception);
    static JSValueRef  JSObjectConvertToTypeCallback(JSContextRef context_ref, JSObjectRef object_ref, JSType type, JSValueRef* exception);
    
    // Helper functions.
    static JSValue CreateJSError(const std::string& function_name, const std::string& location, JSObject js_object, const js_runtime_error& e);
    static JSValue CreateJSError(const std::string& function_name, JSObject js_object, const std::exception& e);
    static JSValue CreateJSError(const std::string& function_name, JSObject js_object, const std::string& what);
    static std::string GetJSExportComponentName(const std::string& function_name, const std::string& location = "");
    
    static JSExportClassDefinition<T> js_export_class_definition__;
    
#undef HAL_DETAIL_JSEXPORTCLASS_LOCK_GUARD_STATIC
#ifdef HAL_THREAD_SAFE
    static std::recursive_mutex mutex_static__;
#define HAL_DETAIL_JSEXPORTCLASS_LOCK_GUARD_STATIC std::lock_guard<std::recursive_mutex> lock_static(JSExportClass::mutex_static__)
#else
#define HAL_DETAIL_JSEXPORTCLASS_LOCK_GUARD_STATIC
#endif  // HAL_THREAD_SAFE
  };

#ifdef HAL_THREAD_SAFE
  template<typename T>
  std::recursive_mutex JSExportClass<T>::mutex_static__;
#endif
  
  template<typename T>
  JSExportClassDefinition<T> JSExportClass<T>::js_export_class_definition__;
  
  template<typename T>
  JSExportClass<T>::JSExportClass() HAL_NOEXCEPT {
    HAL_LOG_TRACE("JSExportClass<", typeid(T).name(), ">:: ctor 1 ", this);
  }

  template<typename T>
  JSExportClass<T>::JSExportClass(const JSExportClassDefinition<T>& js_export_class_definition) HAL_NOEXCEPT
  : JSClass(js_export_class_definition) {
    HAL_DETAIL_JSEXPORTCLASS_LOCK_GUARD_STATIC;
    HAL_LOG_TRACE("JSExportClass<", typeid(T).name(), ">:: ctor 2 ", this);
    js_export_class_definition__ = js_export_class_definition;
    //js_export_class_definition__.Print();
  }
  
  template<typename T>
  JSExportClass<T>::~JSExportClass() HAL_NOEXCEPT {
    HAL_LOG_TRACE("JSExportClass<", typeid(T).name(), ">:: dtor ", this);
  }
  
  template<typename T>
  void JSExportClass<T>::Print() const {
    HAL_JSCLASS_LOCK_GUARD;
    for (const auto& entry : js_export_class_definition__.named_value_property_callback_map__) {
      const auto& name       = entry.first;
      const auto& attributes = entry.second.get_attributes();
      HAL_LOG_DEBUG("JSExportClass: has value property callback ", name, " with attributes ", to_string(attributes));
    }
    
    for (const auto& entry : js_export_class_definition__.named_function_property_callback_map__) {
      const auto& name       = entry.first;
      const auto& attributes = entry.second.get_attributes();
      HAL_LOG_DEBUG("JSExportClass: has function property callback ", name, " with attributes ", to_string(attributes));
    }
  }
  
  // The static functions that implement the JavaScriptCore C API
  // callbacks begin here.
  
  template<typename T>
  void JSExportClass<T>::JSObjectInitializeCallback(JSContextRef context_ref, JSObjectRef object_ref) {
    
    JSObject js_object(JSContext(context_ref), object_ref);
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::Initialize: JSContextRef = ", context_ref, ", JSObjectRef = ", object_ref);

    const auto previous_native_object_ptr = static_cast<JSExport<T>*>(js_object.GetPrivate());
    const auto native_object_ptr          = new T(js_object.get_context());
    
    if (previous_native_object_ptr != nullptr) {
      HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::Initialize: replace ", previous_native_object_ptr, " with ", native_object_ptr, " for ", object_ref);
      delete previous_native_object_ptr;
    }
    
    const bool result = js_object.SetPrivate(native_object_ptr);
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::Initialize: private data set to ", js_object.GetPrivate(), " for ", object_ref);
    
    native_object_ptr->postInitialize(js_object);
    
    assert(result);
  }
  
  template<typename T>
  void JSExportClass<T>::JSObjectFinalizeCallback(JSObjectRef object_ref) {
    HAL_DETAIL_JSEXPORTCLASS_LOCK_GUARD_STATIC;
    
    auto native_object_ptr = static_cast<JSExport<T>*>(JSObjectGetPrivate(object_ref));
    
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::Finalize: delete native object ", native_object_ptr, " for ", object_ref);
    if (native_object_ptr) {
      //delete reinterpret_cast<T*>(native_object_ptr);
      delete native_object_ptr;
      JSObjectSetPrivate(object_ref, nullptr);
    }
  }
  
  template<typename T>
  JSValueRef JSExportClass<T>::GetNamedValuePropertyCallback(JSContextRef context_ref, JSObjectRef object_ref, JSStringRef property_name_ref, JSValueRef* exception) try {
    
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    
    const std::string property_name = JSString(property_name_ref);
    
    const auto callback_position = js_export_class_definition__.named_value_property_callback_map__.find(property_name);
    const bool callback_found    = callback_position != js_export_class_definition__.named_value_property_callback_map__.end();
    
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::GetNamedProperty: callback found = ", callback_found, " for ", to_string(js_object), ".", property_name);
    
    // precondition
    assert(callback_found);
    
    try {
      const auto native_object_ptr = static_cast<const T*>(js_object.GetPrivate());
      const auto callback          = (callback_position -> second).get_callback();
      const auto result            = callback(*native_object_ptr);
      
      HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::GetNamedProperty: result = ", to_string(result), " for ", to_string(js_object), ".", property_name);
      
      return static_cast<JSValueRef>(result);

    } catch (const js_runtime_error& e) {
      JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
      *exception = static_cast<JSValueRef>(CreateJSError("GetNamedProperty", property_name, js_object, e));
      return nullptr;
    }

  } catch (const std::exception& e) {
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("GetNamedProperty", js_object, e));
    return nullptr;
  } catch (...) {
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("GetNamedProperty", js_object, "unknown exception"));
    return nullptr;
  }
  
  template<typename T>
  bool JSExportClass<T>::SetNamedValuePropertyCallback(JSContextRef context_ref, JSObjectRef object_ref, JSStringRef property_name_ref, JSValueRef value_ref, JSValueRef* exception) try {
    
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    JSValue  js_value(js_object.get_context(), value_ref);
    
    const std::string property_name = JSString(property_name_ref);
    
    const auto callback_position = js_export_class_definition__.named_value_property_callback_map__.find(property_name);
    const bool callback_found    = callback_position != js_export_class_definition__.named_value_property_callback_map__.end();
    
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::SetNamedProperty: callback found = ", callback_found, " for ", to_string(js_object), ".", property_name);
    
    // precondition
    assert(callback_found);
    
    try {
      auto native_object_ptr = static_cast<T*>(js_object.GetPrivate());
      const auto callback    = (callback_position -> second).set_callback();
      const auto result      = callback(*native_object_ptr, js_value);
      
      HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::SetNamedProperty: result = ", result, " for ", to_string(js_object), ".", property_name);
      
      return result;

    } catch (const js_runtime_error& e) {
      JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
      *exception = static_cast<JSValueRef>(CreateJSError("SetNamedProperty", property_name, js_object, e));
      return false;
    }
    
  } catch (const std::exception& e) {
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("SetNamedProperty", js_object, e));
    return false;
  } catch (...) {
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("SetNamedProperty", js_object, "unknown exception"));
    return false;
  }
  
  template<typename T>
  JSValueRef JSExportClass<T>::CallNamedFunctionCallback(JSContextRef context_ref, JSObjectRef function_ref, JSObjectRef this_object_ref, size_t argument_count, const JSValueRef arguments_array[], JSValueRef* exception) try {
    // to_string(js_object) produces this text:
    //
    // function sayHello() {
    //     [native code]
    // }
    //
    // So this is the regular expression we use to determing the
    // function's name for lookup.
    static std::regex regex("^function\\s+([^(]+)\\(\\)(.|\\n)*$");
    
    JSObject          js_object(JSObject::FindJSObject(context_ref, function_ref));
    JSObject          this_object(JSObject::FindJSObject(context_ref, this_object_ref));
    const std::string js_object_string = to_string(js_object);
    std::smatch       match_results;
    const bool        found = std::regex_match(js_object_string, match_results, regex);

    static_cast<void>(found);
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::CallNamedFunction: function name found = ", found, ", match_results.size() = ", match_results.size(), ", input = ", js_object_string);
    
    // precondition
    // The size of the match results should be 3:
    // match_results[0] == the whole string.
    // match_results[1] == The function's name
    // match_results[2] == Everything after the function's name.
    assert(match_results.size() == 3);
    const std::string function_name = match_results[1];
    
    // precondition
    assert(js_object.IsFunction());
    
    const auto callback_position = js_export_class_definition__.named_function_property_callback_map__.find(function_name);
    const bool callback_found    = callback_position != js_export_class_definition__.named_function_property_callback_map__.end();
    const auto native_object_ptr = static_cast<T*>(js_object.GetPrivate());
    const auto native_this_ptr   = static_cast<T*>(this_object.GetPrivate());

    static_cast<void>(native_object_ptr);
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::CallNamedFunction: callback found = ", callback_found, " for this[", native_this_ptr, "].", function_name, "(...)");
    
    // precondition
    assert(callback_found);

    try {
      const auto callback = (callback_position -> second).function_callback();
      const auto result   = callback(*native_this_ptr, to_vector(this_object.get_context(), argument_count, arguments_array), this_object);
      
#ifdef HAL_LOGGING_ENABLE
      std::string js_value_str;
      if (result.IsObject()) {
        JSObject js_object = static_cast<JSObject>(result);
        const auto native_object_ptr = reinterpret_cast<std::intptr_t>(js_object.GetPrivate());
        js_value_str = std::to_string(native_object_ptr);
      }
      else {
        js_value_str = to_string(result);
      }
      
      HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::CallNamedFunction: result = ", js_value_str, " for this[", native_this_ptr, "].", function_name, "(...)");
#endif
      
      return static_cast<JSValueRef>(result);

    } catch (const js_runtime_error& e) {
      JSObject js_object(JSObject::FindJSObject(context_ref, function_ref));
      *exception = static_cast<JSValueRef>(CreateJSError("CallNamedFunction", function_name, js_object, e));
      return nullptr;
    }

  } catch (const std::exception& e) {
    JSObject js_object(JSObject::FindJSObject(context_ref, function_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("CallNamedFunction", js_object, e));
    return nullptr;
  } catch (...) {
    JSObject js_object(JSObject::FindJSObject(context_ref, function_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("CallNamedFunction", js_object, "unknown exception"));
    return nullptr;
  }

  template<typename T>
  JSValue JSExportClass<T>::CreateJSError(const std::string& function_name, const std::string& location, JSObject js_source, const js_runtime_error& e) {
    const auto js_context = js_source.get_context();
    const auto name = GetJSExportComponentName(function_name, location);

    HAL_LOG_ERROR(name, ": ", e.what());

    std::vector<JSValue> js_stack = e.js_stack();
    js_stack.push_back(js_context.CreateString(name));

    auto js_error = js_context.CreateError();
    js_error.SetProperty("message",    js_context.CreateString(e.js_message()));
    js_error.SetProperty("name",       js_context.CreateString(e.js_name()));
    js_error.SetProperty("fileName",   js_context.CreateString(e.js_filename()));
    js_error.SetProperty("native_stack",      js_context.CreateArray(js_stack));
    js_error.SetProperty("lineNumber", js_context.CreateNumber(e.js_linenumber()));
    return js_error;
  }

  template<typename T>
  JSValue JSExportClass<T>::CreateJSError(const std::string& function_name, JSObject js_source, const std::exception& e) {
    return CreateJSError(function_name, js_source, e.what());
  }

  template<typename T>
  JSValue JSExportClass<T>::CreateJSError(const std::string& function_name, JSObject js_source, const std::string& what) {
    const auto js_context = js_source.get_context();
    const auto name = GetJSExportComponentName(function_name);

    HAL_LOG_ERROR(name, ": ", what);

    auto js_error = js_context.CreateError();
    js_error.SetProperty("message",    js_context.CreateString(what));
    js_error.SetProperty("native_stack",      js_context.CreateArray({ js_context.CreateString(name) }));
    return js_error;
  }
  
  template<typename T>
  bool JSExportClass<T>::JSObjectHasPropertyCallback(JSContextRef context_ref, JSObjectRef object_ref, JSStringRef property_name_ref) try {
    
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    JSString property_name(property_name_ref);
    
    auto       callback       = js_export_class_definition__.has_property_callback__;
    const bool callback_found = callback != nullptr;

    const auto native_object_ptr = static_cast<const T*>(js_object.GetPrivate());
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::HasProperty: callback found = ", callback_found, " for this[", native_object_ptr, "].", static_cast<std::string>(property_name));
    
    // precondition
    assert(callback_found);
    
    const bool result = callback(*native_object_ptr, property_name);
    
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::HasProperty: result = ", result, " for this[", native_object_ptr, "].", static_cast<std::string>(property_name));
    
    return result;
    
  } catch (const std::exception& e) {
    HAL_LOG_ERROR(GetJSExportComponentName("HasProperty"), ": ", e.what());
    return false;
  } catch (...) {
    HAL_LOG_ERROR(GetJSExportComponentName("HasProperty"), ": unknown exception");
    return false;
  }
  
  template<typename T>
  JSValueRef JSExportClass<T>::JSObjectGetPropertyCallback(JSContextRef context_ref, JSObjectRef object_ref, JSStringRef property_name_ref, JSValueRef* exception) try {
    
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    JSString property_name(property_name_ref);
    
    auto       callback       = js_export_class_definition__.get_property_callback__;
    const bool callback_found = callback != nullptr;
    
    const auto native_object_ptr = static_cast<const T*>(js_object.GetPrivate());
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::GetProperty: callback found = ", callback_found, " for this[", native_object_ptr, "].", static_cast<std::string>(property_name));
    
    // precondition
    assert(callback_found);
    
    try {
      const auto result = callback(*native_object_ptr, property_name);
      
#ifdef HAL_LOGGING_ENABLE
      std::string js_value_str;
      if (result.IsObject()) {
        JSObject js_object = static_cast<JSObject>(result);
        const auto native_object_ptr = reinterpret_cast<std::intptr_t>(js_object.GetPrivate());
        js_value_str = std::to_string(native_object_ptr);
      }
      else {
        js_value_str = to_string(result);
      }
      HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::GetProperty: result = ", js_value_str, " for this[", native_object_ptr, "].", static_cast<std::string>(property_name));
#endif
      
      return static_cast<JSValueRef>(result);
    } catch (const js_runtime_error& e) {
      JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
      *exception = static_cast<JSValueRef>(CreateJSError("GetProperty", property_name, js_object, e));
      return nullptr;
    }

  } catch (const std::exception& e) {
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("GetProperty", js_object, e));
    return nullptr;
  } catch (...) {
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("GetProperty", js_object, "unknown exception"));
    return nullptr;
  }
  
  template<typename T>
  bool JSExportClass<T>::JSObjectSetPropertyCallback(JSContextRef context_ref, JSObjectRef object_ref, JSStringRef property_name_ref, JSValueRef value_ref, JSValueRef* exception) try {
    
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    JSString property_name(property_name_ref);
    
    auto       callback       = js_export_class_definition__.set_property_callback__;
    const bool callback_found = callback != nullptr;
    
    auto native_object_ptr = static_cast<T*>(js_object.GetPrivate());
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::SetProperty: callback found = ", callback_found, " for this[", native_object_ptr, "].", static_cast<std::string>(property_name));
    
    // precondition
    assert(callback_found);
    
    try {
      const auto result = callback(*native_object_ptr, property_name, JSValue(js_object.get_context(), value_ref));
      HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::SetProperty: result = ", result, " for this[", native_object_ptr, "].", static_cast<std::string>(property_name));
      return result;
    } catch (const js_runtime_error& e) {
      JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
      *exception = static_cast<JSValueRef>(CreateJSError("SetProperty", property_name, js_object, e));
      return false;
    }

  } catch (const std::exception& e) {
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("SetProperty", js_object, e));
    return false;
  } catch (...) {
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("SetProperty", js_object, "unknown exception"));
    return false;
  }
  
  template<typename T>
  bool JSExportClass<T>::JSObjectDeletePropertyCallback(JSContextRef context_ref, JSObjectRef object_ref, JSStringRef property_name_ref, JSValueRef* exception) try {
    
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    JSString property_name(property_name_ref);
    
    auto       callback       = js_export_class_definition__.delete_property_callback__;
    const bool callback_found = callback != nullptr;
    
    auto native_object_ptr = static_cast<T*>(js_object.GetPrivate());
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::DeleteProperty: callback found = ", callback_found, " for this[", native_object_ptr, "].", static_cast<std::string>(property_name));
    
    // precondition
    assert(callback_found);
    
    try {
      const auto result = callback(*native_object_ptr, property_name);
      HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::DeleteProperty: result = ", result, " for this[", native_object_ptr, "].", static_cast<std::string>(property_name));
      return result;
    } catch (const js_runtime_error& e) {
      JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
      *exception = static_cast<JSValueRef>(CreateJSError("DeleteProperty", property_name, js_object, e));
      return false;
    }
    
  } catch (const std::exception& e) {
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("DeleteProperty", js_object, e));
    return false;
  } catch (...) {
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("DeleteProperty", js_object, "unknown exception"));
    return false;
  }
  
  template<typename T>
  void JSExportClass<T>::JSObjectGetPropertyNamesCallback(JSContextRef context_ref, JSObjectRef object_ref, JSPropertyNameAccumulatorRef property_names) try {
    
    JSObject                  js_object(JSObject::FindJSObject(context_ref, object_ref));
    JSPropertyNameAccumulator js_property_name_accumulator(property_names);
    
    auto       callback       = js_export_class_definition__.get_property_names_callback__;
    const bool callback_found = callback != nullptr;
    
    auto native_object_ptr = static_cast<T*>(js_object.GetPrivate());
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::GetPropertyNames: callback found = ", callback_found, " for this[", native_object_ptr, "]");
    
    // precondition
    assert(callback_found);
    
    callback(*native_object_ptr, js_property_name_accumulator);

  } catch (const std::exception& e) {
    HAL_LOG_ERROR(GetJSExportComponentName("GetPropertyNames"), ": ", e.what());
  } catch (...) {
    HAL_LOG_ERROR(GetJSExportComponentName("GetPropertyNames"), ": unknown exception");
  }
  
  template<typename T>
  JSValueRef JSExportClass<T>::JSObjectCallAsFunctionCallback(JSContextRef context_ref, JSObjectRef function_ref, JSObjectRef this_object_ref, size_t argument_count, const JSValueRef arguments_array[], JSValueRef* exception) try {
    
    JSObject js_object(JSObject::FindJSObject(context_ref, function_ref));
    JSObject this_object(JSObject::FindJSObject(context_ref, this_object_ref));
    
    // precondition
    assert(js_object.IsFunction());
    
    auto       callback       = js_export_class_definition__.call_as_function_callback__;
    const bool callback_found = callback != nullptr;
    
    auto native_object_ptr = static_cast<T*>(js_object.GetPrivate());
    auto native_this_ptr   = static_cast<T*>(this_object.GetPrivate());
    static_cast<void>(native_this_ptr);
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::CallAsFunction: callback found = ", callback_found, " for this[", native_this_ptr, "].this[", native_object_ptr, "](...)");
    
    // precondition
    assert(callback_found);
    
    const auto result = callback(*native_object_ptr, to_vector(this_object.get_context(), argument_count, arguments_array), this_object);
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::CallAsFunction: result = ", to_string(result), " for this[", native_this_ptr, "].this[", native_object_ptr, "](...)");
    return static_cast<JSValueRef>(result);

  } catch (const js_runtime_error& e) {
    JSObject js_object(JSObject::FindJSObject(context_ref, function_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("CallAsFunction", "", js_object, e));
    return nullptr;
  } catch (const std::exception& e) {
    JSObject js_object(JSObject::FindJSObject(context_ref, function_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("CallAsFunction", js_object, e));
    return nullptr;
  } catch (...) {
    JSObject js_object(JSObject::FindJSObject(context_ref, function_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("CallAsFunction", js_object, "unknown exception"));
    return nullptr;
  }
  
  template<typename T>
  JSObjectRef JSExportClass<T>::JSObjectCallAsConstructorCallback(JSContextRef context_ref, JSObjectRef constructor_ref, size_t argument_count, const JSValueRef arguments_array[], JSValueRef* exception) try {
    
    JSObject  js_object(JSObject::FindJSObject(context_ref, constructor_ref));
    JSContext js_context = js_object.get_context();

    auto new_object = js_context.CreateObject(JSExport<T>::Class());
    const auto native_object_ptr = static_cast<T*>(new_object.GetPrivate());
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::CallAsConstructor: for this[", native_object_ptr, "]");

    native_object_ptr->postCallAsConstructor(js_context, to_vector(js_context, argument_count, arguments_array));

    return static_cast<JSObjectRef>(new_object);
    
  } catch (const js_runtime_error& e) {
    JSObject js_object(JSObject::FindJSObject(context_ref, constructor_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("JSObjectCallAsConstructorCallback", "", js_object, e));
    return nullptr;
  } catch (const std::exception& e) {
    JSObject js_object(JSObject::FindJSObject(context_ref, constructor_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("JSObjectCallAsConstructorCallback", js_object, e));
    return nullptr;
  } catch (...) {
    JSObject js_object(JSObject::FindJSObject(context_ref, constructor_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("JSObjectCallAsConstructorCallback", js_object, "unknown exception"));
    return nullptr;
  }
  
  template<typename T>
  bool JSExportClass<T>::JSObjectHasInstanceCallback(JSContextRef context_ref, JSObjectRef constructor_ref, JSValueRef possible_instance_ref, JSValueRef* exception) try {
    JSObject js_object(JSObject::FindJSObject(context_ref, constructor_ref));
    JSValue  possible_instance(js_object.get_context(), possible_instance_ref);

    bool result = false;
    if (possible_instance.IsObject()) {
      JSObject possible_object = static_cast<JSObject>(possible_instance);
      if (possible_object.GetPrivate() != nullptr) {
        auto possible_js_export_ptr     = static_cast<JSExport<T>*>(possible_object.GetPrivate());
        auto possible_native_object_ptr = dynamic_cast<T*>(possible_js_export_ptr);
        if (possible_native_object_ptr != nullptr) {
          result = true;
        }
      }
    }
    
    auto native_object_ptr = static_cast<T*>(js_object.GetPrivate());
    static_cast<void>(native_object_ptr);
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::HasInstance: result = ", result, " for ", to_string(possible_instance), " instanceof this[", native_object_ptr, "]");
    return result;
    
  } catch (const js_runtime_error& e) {
    JSObject js_object(JSObject::FindJSObject(context_ref, constructor_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("JSObjectHasInstanceCallback", "", js_object, e));
    return false;
  } catch (const std::exception& e) {
    JSObject js_object(JSObject::FindJSObject(context_ref, constructor_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("JSObjectHasInstanceCallback", js_object, e));
    return false;
  } catch (...) {
    JSObject js_object(JSObject::FindJSObject(context_ref, constructor_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("JSObjectHasInstanceCallback", js_object, "unknown exception"));
    return false;
  }
  
  template<typename T>
  JSValueRef JSExportClass<T>::JSObjectConvertToTypeCallback(JSContextRef context_ref, JSObjectRef object_ref, JSType type, JSValueRef* exception) try {
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    JSValue::Type js_value_type = ToJSValueType(type);
    
    auto       callback       = js_export_class_definition__.convert_to_type_callback__;
    const bool callback_found = callback != nullptr;
    
    const auto native_object_ptr = static_cast<const T*>(js_object.GetPrivate());
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::ConvertToType: callback found = ", callback_found, " for this[", native_object_ptr, "]");
    
    // precondition
    assert(callback_found);
    
    const auto result = callback(*native_object_ptr, js_value_type);
    
    HAL_LOG_DEBUG("JSExportClass<", typeid(T).name(), ">::ConvertToType: result = ", to_string(result), " for converting this[", native_object_ptr, "] to ", to_string(js_value_type));
    
    return static_cast<JSValueRef>(result);
    
  } catch (const js_runtime_error& e) {
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("JSObjectConvertToTypeCallback", "", js_object, e));
    return nullptr;
  } catch (const std::exception& e) {
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("JSObjectConvertToTypeCallback", js_object, e));
    return nullptr;
  } catch (...) {
    JSObject js_object(JSObject::FindJSObject(context_ref, object_ref));
    *exception = static_cast<JSValueRef>(CreateJSError("JSObjectConvertToTypeCallback", js_object, "unknown exception"));
    return nullptr;
  }
  
  template<typename T>
  std::string JSExportClass<T>::GetJSExportComponentName(const std::string& function_name, const std::string& location) {
    std::ostringstream os;
    os << "JSExportClass<" << typeid(T).name() << ">::" << function_name;
    if (location.size() > 0) {
      os << " (" << location << ")";
    }
    return os.str();
  }

}} // namespace HAL { namespace detail {

#endif // _HAL_DETAIL_JSEXPORTCLASS_HPP_
