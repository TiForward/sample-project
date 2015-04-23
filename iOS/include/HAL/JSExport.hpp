/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_JSEXPORT_HPP_
#define _HAL_JSEXPORT_HPP_

#include "HAL/detail/JSBase.hpp"
#include "HAL/detail/JSExportClassDefinitionBuilder.hpp"

#include <string>
#include <memory>
#include <mutex>

namespace HAL {
  
  /*!
   @class
   
   @abstract This is a CRTP (i.e. Curiously Recurring Template
   Pattern) base class that allows any C++ class derived from it to be
   seamlessly integrated into JavaScriptCore. For example, to expose
   the following C++ Widget class to JavaScriptCore you would define
   Widget like this:
   
   class Widget : public JSExport<Widget> {
   
   // Mandatory constructor.
   Widget::Widget(const JSContext& js_context)
   }
   
   // Add additional C++ methods to implement any or all of the
   // following characteristics that define a JavaScript object (all
   // described in detail in the documentation that follows):
   //
   // 1. JavaScript named value properties (i.e. getters and/or
   //    setters) with full support for all JavaScript property
   //    attributes (i.e.  'None', 'ReadOnly', 'DontEnum' and
   //    'DontDelete').
   //
   // 2. JavaScript named function properties with full support for
   //    all JavaScript property attributes (i.e.  'None',
   //    'ReadOnly', 'DontEnum' and 'DontDelete').
   //
   // 3. Calling Widget as a function property on another JavaScript
   //    object.
   //
   // 4. Calling Widget as a constructor in a JavaScript 'new'
   //    expression.
   //
   // 5. Definig how a Widget behaves when it is the target of a
   //    JavaScript 'instanceof' expression.
   //
   // 6. Definig how a Widget converts to a JavaScript string or
   //    number.
   
   // Implementing this static function is how your C++ class
   // seamlessly integrates into JavaScriptCore.
   static void JSExportInitialize() {
   // All of the characteristics are optional, but here are some
   // examples:
   SetClassVersion(1);
   AddValueProperty("name"       , std::mem_fn(&Widget::get_name)  , std::mem_fn(&Widget::set_name));
   AddValueProperty("number"     , std::mem_fn(&Widget::get_number), std::mem_fn(&Widget::set_number));
   AddValueProperty("pi"         , std::mem_fn(&Widget::pi));
   AddFunctionProperty("sayHello", std::mem_fn(&Widget::sayHello));
   }
   };
   
   @discussion All properties are optional. By default the 'class
   version numner' is initialized to 0, the 'parent' JavaScriptCore
   class is initialized to the default JavaScript object class, and
   the JavaScriptCore 'class attribute' defaults to
   'AutomaticPrototype' (more on this below).
   
   Using the AddValueProperty and AddFunctionProperty static methods
   in your JSExportInitialize are the simplest and most efficient
   means for vending custom JavaScript properties since they
   autmatically service requests like GetProperty, SetProperty and
   GetPropertyNames. The other property access callbacks are required
   only to implement unusual properties, like array indexes, whose
   names are not known at compile-time.
   
   Standard JavaScript practice calls for storing JavaScript function
   objects in prototypes so that they can be shared with JavaScript
   objects having that prototype. By default all derived classes of
   JSExport follow this idiom whereby JavaScriptCore instantiates your
   JavaScript objects with a shared, automatically generated prototype
   containing the JavaScript function properties you have (optionally)
   defined.
   
   To override this behavior call the SetClassAttribute method with
   the argument 'NoAutomaticPrototype', which specifies that
   JavaScriptCore should not automatically generate such a
   prototype. JavaScriptCore will then instantiate your JavaScript
   objects with the default JavaScript object prototype, and give each
   JavaScript object its own copy of the the JavaScript function
   properties you have (optionally) defined.
   
   Setting any callback to nullptr specifies that the default object
   callback should substitute, except in the case of HasProperty,
   where it specifies that GetProperty should substitute.
   */
  template<typename T>
  class JSExport HAL_PERFORMANCE_COUNTER1(JSExport<T>) {
    
  public:
    
    /*!
     @method
     
     @abstract Return the JSClass for the C++ class T.
     */
    static detail::JSExportClass<T> Class();
    
    virtual ~JSExport() HAL_NOEXCEPT {
    }
    
  protected:
    
    /*!
     @method
     
     @abstract Set the version of your JSClass.
     */
    static void SetClassVersion(std::uint32_t class_version);
    
    /*!
     @method
     
     @abstract Set the JSClassAttribute of your JSClass.
     
     @discussion Standard JavaScript practice calls for storing
     JavaScript function objects in prototypes so that they can be
     shared with JavaScript objects with that prototype. By default
     your JSClass follows this idiom, instantiating your JavaScript
     object with a shared, automatically generated prototype
     containing your JSClass's JavaScript function objects.
     
     To override this behavior set the JSClassAttribute to
     'NoAutomaticPrototype', which specifies that your JSClass should
     not automatically generate such a prototype. The resulting
     JSClass will then instantiate your JavaScript objects with the
     default JavaScript object prototype, and give each JavaScript
     object its own copy of your JSClass's JavaScript function
     objects.
     */
    static void SetClassAttribute(JSClassAttribute class_attribute);
    
    /*!
     @method
     
     @abstract Set the parent of your JSClass. By default your JSClass
     will have the default JavaScript object class.
     */
    static void SetParent(const JSClass& parent);
    
    /*!
     @method
     
     @abstract Add callbacks to invoke when getting and/or setting a
     value property on your JavaScript object. The property will
     always have the 'DontDelete' attribute. If a setter callback is
     not provided then the property will also have the 'ReadOnly'
     attribute. By default the property is enumerable unless you
     specify otherwise.
     
     @discussion For example, given this class definition:
     
     class Foo {
     JSValue GetName() const;
     bool SetName(JSValue& value);
     };
     
     You would call AddValueProperty like this:
     
     AddValueProperty("name", &Foo::GetName, &Foo::SetName);
     
     If you wanted the property ReadOnly, then you would call
     AddValueProperty like this:
     
     AddValueProperty("name", &Foo::GetName);
     
     @param property_name A JSString containing your property's name.
     
     @param get_callback The callback to invoke when getting your
     property's value.
     
     @param set_callback The callback to invoke when setting your
     property's value. This may be nullptr, in which case the
     'ReadOnly' attribute for your property is automatically set. If
     this callback returns false, then this indicates that the value
     was not set.
     
     @param enumerable An optional property attribute that specifies
     whether your property is enumerable. The default value is true,
     which means the property is enumerable.
     
     @throws std::invalid_argument exception under these
     preconditions:
     
     1. If property_name is empty.
     
     2. If both get_callback and set_callback are missing.
     
     3. You have already added a property with the same property_name.
     */
    static void AddValueProperty(const JSString& property_name,
                                 detail::GetNamedValuePropertyCallback<T> get_callback,
                                 detail::SetNamedValuePropertyCallback<T> set_callback = nullptr,
                                 bool enumerable = true);
    
    /*!
     @method
     
     @abstract Add a function property to your JavaScript object with
     the 'DontDelete' and 'ReadOnly' attributes. By default the
     property is enumerable unless you specify otherwise.
     
     @discussion For example, given this class definition:
     
     class Foo {
     JSValue Hello(std::vector<JSValue>&& arguments, JSObject&& this_object);
     };
     
     You would call AddFunctionProperty like this:
     
     AddFunctionProperty("hello", &Foo::Hello);
     
     @param function_name A JSString containing your function's name.
     
     @param function_callback The callback to invoke when calling your
     JavaScript object as a function.
     
     @param enumerable An optional property attribute that specifies
     whether your property is enumerable. The default value is true,
     which means the property is enumerable.
     
     @throws std::invalid_argument exception under these
     preconditions:
     
     1. If function_name is empty.
     
     2. If function_callback is not provided.
     
     3. You have already added a property with the same property_name.
     */
    static void AddFunctionProperty(const JSString& function_name, detail::CallNamedFunctionCallback<T> function_callback, bool enumerable = true);
    
    /*!
     @method
     
     @abstract Set the callback to invoke when determining whether
     your JavaScript object has a property. If this callback is
     missing then your JavaScript object will delegate to it's
     GetPropertyCallback.
     
     @discussion The HasPropertyCallback enables optimization in cases
     where only a property's existence needs to be known, not its
     value, and computing its value is expensive. If the
     HasPropertyCallback doesn't exist, then the GetPropertyCallback
     will be used instead.
     
     If this callback returns false then the reqeust forwards to
     properties added by the AddValueProperty and AddFunctionProperty
     methods (if any), then properties vended by your class' parent
     class chain, then properties belonging to your JavaScript
     object's prototype chain.
     
     For example, given this class definition:
     
     class Foo {
     bool HasProperty(const JSString& property_name) const;
     };
     
     You would call AddHasPropertyCallback like this:
     
     AddHasPropertyCallback(&Foo::HasProperty);
     
     @param has_property_callback The callback to invoke when
     determining whether your JavaScript object has a property.
     
     @result Your callback should return true if your JavaScript
     object has a property with the given name. Your callback should
     return false to forward the reqeust to properties added by the
     AddValueProperty and AddFunctionProperty methods (if any), then
     properties vended by your class' parent class chain, then
     properties belonging to your JavaScript object's prototype chain.
     */
    static void AddHasPropertyCallback(const detail::HasPropertyCallback<T>& has_property_callback);
    
    /*!
     @method
     
     @abstract Set the callback to invoke when getting a property's
     value from your JavaScript object.
     
     @discussion If this callback returns JSUndefined then the get
     request forwards to properties added by the AddValueProperty and
     AddFunctionProperty methods (if any), then properties vended by
     your class' parent class chain, then properties belonging to your
     JavaScript object's prototype chain.
     
     For example, given this class definition:
     
     class Foo {
     JSValue GetProperty(const JSString& property_name) const;
     };
     
     You would call AddGetPropertyCallback like this:
     
     AddGetPropertyCallback(&Foo::GetProperty);
     
     @param get_property_callback The callback to invoke when getting
     a property's value from your JavaScript object.
     
     @result Your callback should return the property's value with the
     name given name if it exists. If the property does not exist then
     return JSUndefined to forward the request to properties added by
     the AddValueProperty and AddFunctionProperty methods (if any),
     then properties vended by your class' parent class chain, then
     properties belonging to your JavaScript object's prototype chain.
     */
    static void AddGetPropertyCallback(const detail::GetPropertyCallback<T>& get_property_callback);
    
    /*!
     @method
     
     @abstract Set the callback to invoke when setting a property's
     value on your JavaScript object.
     
     @discussion If this callback returns false then the request
     forwards to properties added by the AddValueProperty method (if
     any), then properties vended by your class' parent class chain,
     then properties belonging to your JavaScript object's prototype
     chain.
     
     For example, given this class definition:
     
     class Foo {
     bool SetProperty(const JSString& property_name, const JSValue& value);
     };
     
     You would call AddSetPropertyCallback like this:
     
     AddSetPropertyCallback(&Foo::SetProperty);
     
     @param set_property_callback The callback to invoke when setting
     a property's value on your JavaScript object.
     
     @result Your callback should return true if the property with the
     given name and value was set on your JavaScript object. Your
     callback should return false to forward the reqeust to properties
     added by the AddValueProperty and AddFunctionProperty methods (if
     any), then properties vended by your class' parent class chain,
     then properties belonging to your JavaScript object's prototype
     chain.
     */
    static void AddSetPropertyCallback(const detail::SetPropertyCallback<T>& set_property_callback);
    
    /*!
     @method
     
     @abstract Set the callback to invoke when deleting a property
     from your JavaScript object.
     
     @discussion If this callback returns false then the request
     forwards to properties added by the AddValueProperty and
     AddFunctionProperty methods (if any), then properties vended by
     your class' parent class chain, then properties belonging to your
     JavaScript object's prototype chain.
     
     For example, given this class definition:
     
     class Foo {
     bool DeleteProperty(const JSString& property_name);
     };
     
     You would call AddDeletePropertyCallback like this:
     
     AddDeletePropertyCallback(&Foo::DeleteProperty);
     
     @param delete_property_callback The callback to invoke when
     deleting a property from your JavaScript object.
     
     @result Your callback should return true if the property with the
     given name was deleted from your JavaScript object. Your callback
     should return false to forward the reqeust to properties added by
     the AddValueProperty and AddFunctionProperty methods (if any),
     then properties vended by your class' parent class chain, then
     properties belonging to your JavaScript object's prototype chain.
     */
    static void AddDeletePropertyCallback(const detail::DeletePropertyCallback<T>& delete_property_callback);
    
    /*!
     @method
     
     @abstract Set the callback to invoke when collecting the names of
     your JavaScript object's properties provided by the GetProperty
     and SetProperty methods. This callback is part of a chain of
     callbacks that are automatically invoked when your JavaScript
     object is used in a JavaScript for...in loop.
     
     @discussion The GetPropertyNamesCallback only needs to provide
     the property names provided by the GetProperty and SetProperty
     methods. Other property names are automatically added from
     properties provided by the AddValueProperty and
     AddFunctionProperty methods (if any), then properties vended by
     your class' parent class chain, then properties belonging to your
     JavaScript object's prototype chain.
     
     For example, given this class definition:
     
     class Foo {
     void GetPropertyNames(JSPropertyNameAccumulator& accumulator) const;
     };
     
     You would call AddGetPropertyNamesCallback like this:
     
     AddGetPropertyNamesCallback(&Foo::GetPropertyNames);
     
     @param get_property_names_callback The callback to invoke when
     collecting the names of your JavaScript object's properties
     provided by the GetProperty and SetProperty methods. This
     callback is part of a chain of callbacks that are automatically
     invoked when your JavaScript object is used in a JavaScript
     for...in loop.
     */
    static void AddGetPropertyNamesCallback(const detail::GetPropertyNamesCallback<T>& get_property_names_callback);
    
    /*!
     @method
     
     @abstract Set the callback to invoke when your JavaScript object
     is called as a function.
     
     @discussion If this callback does not exist, then calling your
     JavaScript object as a function will throw a JavaScript
     exception.
     
     For example, given this class definition:
     
     class Foo {
     JSValue DoSomething(const std::vector<JSValue>& arguments, JSObject& this_object);
     };
     
     You would call AddCallAsFunctionCallback like this:
     
     AddCallAsFunctionCallback(&Foo::DoSomething);
     
     In the JavaScript expression 'myObject.myFunction()', then
     'myFunction' is the instance of Foo being called, and 'myObject'
     is the context of the function call (i.e. the 'this' JavaScript
     object).
     
     @param call_as_function_callback The callback to invoke when your
     JavaScript object is called as a function.
     
     @result Your callback should return the value produced by calling
     your JavaScript object as a function.
     */
    static void AddCallAsFunctionCallback(const detail::CallAsFunctionCallback<T>& call_as_function_callback);
    
    /*!
     @method
     
     @abstract Set the callback to invoke when converting your
     JavaScript object to another JavaScript type. This callback is
     only invoked when converting your object to a number or a
     string. An object converted to boolean is 'true.' An object
     converted to object is itself.
     
     @discussion If this callback returns JSUndefined then the
     conversion request forwards to your your class' parent class
     chain, then your JavaScript object's prototype chain.
     
     For example, given this class definition:
     
     class Foo {
     JSValue ConvertToType(JSValue::Type type) const;
     };
     
     You would call AddHasInstanceCallback like this:
     
     AddHasInstanceCallback(&Foo::HasInstance);
     
     @param convert_to_type_callback The callback to invoke when
     converting your JavaScript object to another JavaScript
     type. This callback is only invoked when converting your object
     to a number or a string. An object converted to boolean is
     'true.' An object converted to object is itself.
     
     @result Return the objects's converted value. Return JSUndefined
     to forward the reqeust to your class' parent class chain, then
     your JavaScript object's prototype chain.
     */
    static void AddConvertToTypeCallback(const detail::ConvertToTypeCallback<T>& convert_to_type_callback);
    
  private:
    
    static detail::JSExportClassDefinitionBuilder<T> builder__;
  };
  
  template<typename T>
  void JSExport<T>::SetClassVersion(uint32_t class_version) {
    builder__.Version(class_version);
  }
  
  template<typename T>
  void JSExport<T>::SetClassAttribute(JSClassAttribute class_attribute) {
    builder__.ClassAttribute(class_attribute);
  }
  
  template<typename T>
  void JSExport<T>::SetParent(const JSClass& parent) {
    builder__.Parent(parent);
  }
  
  template<typename T>
  void JSExport<T>::AddValueProperty(const JSString& property_name, detail::GetNamedValuePropertyCallback<T> get_callback, detail::SetNamedValuePropertyCallback<T> set_callback, bool enumerable) {
    builder__.AddValueProperty(property_name, get_callback, set_callback);
  }
  
  template<typename T>
  void JSExport<T>::AddFunctionProperty(const JSString& function_name, detail::CallNamedFunctionCallback<T> function_callback, bool enumerable) {
    builder__.AddFunctionProperty(function_name, function_callback, enumerable);
  }
  
  template<typename T>
  void JSExport<T>::AddHasPropertyCallback(const detail::HasPropertyCallback<T>& has_property_callback) {
    builder__.HasProperty(has_property_callback);
  }
  
  template<typename T>
  void JSExport<T>::AddGetPropertyCallback(const detail::GetPropertyCallback<T>& get_property_callback) {
    builder__.GetProperty(get_property_callback);
  }
  
  template<typename T>
  void JSExport<T>::AddSetPropertyCallback(const detail::SetPropertyCallback<T>& set_property_callback) {
    builder__.SetProperty(set_property_callback);
  }
  
  template<typename T>
  void JSExport<T>::AddDeletePropertyCallback(const detail::DeletePropertyCallback<T>& delete_property_callback) {
    builder__.DeleteProperty(delete_property_callback);
  }
  
  template<typename T>
  void JSExport<T>::AddGetPropertyNamesCallback(const detail::GetPropertyNamesCallback<T>& get_property_names_callback) {
    builder__.GetPropertyNames(get_property_names_callback);
  }
  
  template<typename T>
  void JSExport<T>::AddCallAsFunctionCallback(const detail::CallAsFunctionCallback<T>& call_as_function_callback) {
    builder__.CallAsFunction(call_as_function_callback);
  }
  
  template<typename T>
  void JSExport<T>::AddConvertToTypeCallback(const detail::ConvertToTypeCallback<T>& convert_to_type_callback) {
    builder__.ConvertToType(convert_to_type_callback);
  }
  
  template<typename T>
  detail::JSExportClassDefinitionBuilder<T> JSExport<T>::builder__ = detail::JSExportClassDefinitionBuilder<T>(typeid(T).name());
  
  template<typename T>
  detail::JSExportClass<T> JSExport<T>::Class() {
    static detail::JSExportClassDefinition<T> js_export_class_definition;
    static detail::JSExportClass<T>           js_export_class;
    static std::once_flag                     of;
    std::call_once(of, []() {
      T::JSExportInitialize();
      js_export_class_definition = builder__.build();
      js_export_class            = detail::JSExportClass<T>(js_export_class_definition);
    });
    
    return js_export_class;
  }
  
} // namespace HAL {

#endif // _HAL_JSEXPORT_HPP_
