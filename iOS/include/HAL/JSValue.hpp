/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_JSVALUE_HPP_
#define _HAL_JSVALUE_HPP_

#include "HAL/detail/JSBase.hpp"
#include "HAL/JSContext.hpp"

#include <vector>
#include <ostream>

namespace HAL {
  class JSString;
  class JSValue;
  class JSBoolean;
  class JSNumber;
  class JSObject;
  class JSFunction;
  class JSArray;
  class JSDate;
  class JSError;
  class JSRegExp;
  
  namespace detail {
    template<typename T>
    class JSExportClass;
    
    HAL_EXPORT std::vector<JSValue>    to_vector(const JSContext&, size_t, const JSValueRef[]);
    HAL_EXPORT std::vector<JSValueRef> to_vector(const std::vector<JSValue>&);
  }}

namespace HAL {
  
  /*!
   @class
   
   @discussion A JSValue is an RAII wrapper around a JSValueRef, the
   JavaScriptCore C API representation of a JavaScript value. This is
   the base class for all JavaScript values. These are the direct
   descendants of JSValue:
   
   JSUndefined
   JSNull
   JSBoolean
   JSNumber
   
   The only way to create a JSValue is by using the
   JSContext::CreateXXX member functions.
   */
  class HAL_EXPORT JSValue HAL_PERFORMANCE_COUNTER1(JSValue) {
    
  public:
    
    /*!
     @enum Type
     @abstract An enum identifying the type of a JSValue.
     @constant Undefined  The unique undefined value.
     @constant Null       The unique null value.
     @constant Boolean    A primitive boolean value, one of true or false.
     @constant Number     A primitive number value.
     @constant String     A primitive string value.
     @constant Object     An object value (meaning that this JSValue is a JSObject).
     */
    enum class Type {
      Undefined,
      Null,
      Boolean,
      Number,
      String,
      Object
    };
    
    /*!
     @method
     
     @abstract Return a JSString containing the JSON serialized
     representation of this JavaScript value.
     
     @param indent The number of spaces to indent when nesting. If 0
     (the default), the resulting JSON will not contain newlines. The
     size of the indent is clamped to 10 spaces.
     
     @result A JSString containing the JSON serialized representation
     of this JavaScript value.
     */
    virtual JSString ToJSONString(unsigned indent = 0) final;
    
    /*!
     @method
     
     @abstract Convert this JSValue to a JSString.
     
     @result A JSString with the result of conversion.
     */
    explicit operator JSString() const;
    
    /*!
     @method
     
     @abstract Convert this JSValue to a std::string.
     
     @result A std::string with the result of conversion.
     */
    explicit operator std::string() const;
    
    /*!
     @method
     
     @abstract Convert a JSValue to a boolean.
     
     @result The boolean result of conversion.
     */
    explicit operator bool() const HAL_NOEXCEPT;
    
    /*!
     @method
     
     @abstract Convert a JSValue to a double.
     
     @result The double result of conversion.
     */
    explicit operator double() const;
    
    /*!
     @method
     
     @abstract Convert a JSValue to an int32_t according to the rules
     specified by the JavaScript language.
     
     @result The int32_t result of conversion.
     */
    explicit operator int32_t() const;
    
    /*!
     @method
     
     @abstract Convert a JSValue to an uint32_t according to the rules
     specified by the JavaScript language.
     
     @discussion The JSValue is converted to an uint32_t according to
     the rules specified by the JavaScript language (implements
     ToUInt32, defined in ECMA-262 9.6).
     
     @result The uint32_t result of the conversion.
     */
    explicit operator uint32_t() const{
      // As commented in the spec, the operation of ToInt32 and
      // ToUint32 only differ in how the result is interpreted; see
      // NOTEs in sections 9.5 and 9.6.
      return operator int32_t();
    }
    
    /*!
     @method
     
     @abstract Convert this JSValue to a JSObject.
     
     @result A JSObject with the result of conversion.
     
     @throws std::runtime_error if this JSValue could not be converted
     to a JSObject.
     */
    explicit operator JSObject() const;
    
    /*!
     @method
     
     @abstract Return this JavaScript value's type.
     
     @result A value of type JSValue::Type that identifies this
     JavaScript value's type.
     */
    virtual Type GetType() const HAL_NOEXCEPT final;
    
    /*!
     @method
     
     @abstract Determine whether this JavaScript value's type is the
     undefined type.
     
     @result true if this JavaScript value's type is the undefined
     type.
     */
    virtual bool IsUndefined() const HAL_NOEXCEPT final;
    
    /*!
     @method
     
     @abstract Determine whether this JavaScript value's type is the
     null type.
     
     @result true if this JavaScript value's type is the null type.
     */
    virtual bool IsNull() const HAL_NOEXCEPT final;
		
    /*!
     @method
     
     @abstract Determine whether this JavaScript value's type is the
     null type.
     
     @result true if this JavaScript value's type is the null type.
     */
    virtual bool IsNativeNull() const HAL_NOEXCEPT final;
		
    /*!
     @method
     
     @abstract Determine whether this JavaScript value's type is the
     boolean type.
     
     @result true if this JavaScript value's type is the boolean type.
     */
    virtual bool IsBoolean() const HAL_NOEXCEPT final;

    /*!
     @method
     
     @abstract Determine whether this JavaScript value's type is the
     number type.
     
     @result true if this JavaScript value's type is the number type.
     */
    virtual bool IsNumber() const HAL_NOEXCEPT final;
    
    /*!
     @method
     
     @abstract Determine whether this JavaScript value's type is the
     string type.
     
     @result true if this JavaScript value's type is the string type.
     */
    virtual bool IsString() const HAL_NOEXCEPT final;
    
    /*!
     @method
     
     @abstract Determine whether this JavaScript value's type is the
     object type.
     
     @result true if this JavaScript value's type is the object type.
     */
    virtual bool IsObject() const HAL_NOEXCEPT final;
    
    /*!
     @method
     
     @abstract Determine whether this JavaScript's value is an object
     with a given class in its class chain.
     
     @param jsClass The JSClass to test against.
     
     @result true if this JavaScript value is an object with a given
     class in its class chain.
     */
    virtual bool IsObjectOfClass(const JSClass& js_class) const HAL_NOEXCEPT final;
    
    /*!
     @method
     
     @abstract Determine whether this JavaScript value was constructed
     by the given constructor, as compared by the JavaScript
     'instanceof' operator.
     
     @param constructor The constructor to test against.
     
     @result true if this JavaScript value was constructed by the
     given constructor as compared by the JavaScript 'instanceof'
     operator.
     */
    virtual bool IsInstanceOfConstructor(const JSObject& constructor) const final;
    
    /*!
     @method
     
     @abstract Determine whether this JavaScript value is equal to
     another JavaScript by usong the JavaScript == operator.
     
     @param js_value The JavaScript value to test.
     
     @result true this JavaScript value is equal to another JavaScript
     by usong the JavaScript == operator.
     */
    virtual bool IsEqualWithTypeCoercion(const JSValue& js_value) const final;
    
    /*!
     @method
     
     @abstract Return the execution context of this JavaScript value.
     
     @result The the execution context of this JavaScript value.
     */
    virtual JSContext get_context() const HAL_NOEXCEPT final {
      return js_context__;
    }

    /*!
     @method
 
     @abstract Mark this value as native nullptr. 
               For interoperability with the JavaScriptCore C API.
     */
    virtual void MarkAsNativeNull() HAL_NOEXCEPT final {
      is_native_nullptr__ = true;
    }
    
    virtual ~JSValue()           HAL_NOEXCEPT;
    JSValue(const JSValue&)      HAL_NOEXCEPT;
    JSValue(JSValue&&)           HAL_NOEXCEPT;
    JSValue& operator=(JSValue);
    void swap(JSValue&)          HAL_NOEXCEPT;
    
  protected:
    
    // A JSContext can create a JSValue.
    friend class JSContext;
    
    JSValue(const JSContext& js_context, const JSString& js_string, bool parse_as_json = false);
    
    
    // These classes create a JSValue using the following constructor.
    // friend class JSUndefined;
    // friend class JSNull;
    // friend class JSBoolean;
    // friend class JSNumber;
    friend class JSArray;    // for generating error messages
    friend class JSDate;     // for generating error messages
    friend class JSFunction; // for generating error messages
    friend class JSRegExp;   // for generating error messages
    friend class JSError;    // for generating error messages
    
    template<typename T>
    friend class detail::JSExportClass;
    
    // JSObject needs access to the JSValue constructor for
    // GetPrototype() and for generating error messages, as well as
    // operator JSValueRef() for SetPrototype().
    friend class JSObject;
    
    // For interoperability with the JavaScriptCore C API.
    JSValue(const JSContext& js_context, JSValueRef js_value_ref) HAL_NOEXCEPT;
    
    // For interoperability with the JavaScriptCore C API.
    explicit operator JSValueRef() const HAL_NOEXCEPT {
      if (is_native_nullptr__) {
        return nullptr;
      }
      return js_value_ref__;
    }
    
    // These classes and functions need access to operator
    // JSValueRef().
    HAL_EXPORT friend bool operator==(const JSValue& lhs, const JSValue& rhs) HAL_NOEXCEPT;
    
    HAL_EXPORT friend std::vector<JSValue>    detail::to_vector(const JSContext&, size_t, const JSValueRef[]);
    HAL_EXPORT friend std::vector<JSValueRef> detail::to_vector(const std::vector<JSValue>&);
    
  private:
    
    // Prevent heap based objects.
    static void * operator new(std::size_t);     // #1: To prevent allocation of scalar objects
    static void * operator new [] (std::size_t); // #2: To prevent allocation of array of objects
    
    JSContext  js_context__;
		
    bool is_native_nullptr__{false};

    // Silence 4251 on Windows since private member variables do not
    // need to be exported from a DLL.
#pragma warning(push)
#pragma warning(disable: 4251)
    JSValueRef js_value_ref__ { nullptr };
#pragma warning(pop)
    
#undef  HAL_JSVALUE_LOCK_GUARD
#ifdef  HAL_THREAD_SAFE
    std::recursive_mutex mutex__;
#define HAL_JSVALUE_LOCK_GUARD std::lock_guard<std::recursive_mutex> lock(mutex__)
#else
#define HAL_JSVALUE_LOCK_GUARD
#endif  // HAL_THREAD_SAFE
  };
  
  inline
  void swap(JSValue& first, JSValue& second) HAL_NOEXCEPT {
    first.swap(second);
  }
  
  inline
  std::string to_string(const JSValue& js_value) {
    return static_cast<std::string>(js_value);
  }
  
  HAL_EXPORT std::string to_string(const JSValue::Type& js_value_type) HAL_NOEXCEPT;
  
  /*!
   @function
   
   @abstract Determine whether two JavaScript values are strict equal,
   as compared by the JS === operator.
   
   @param lhs The first value to test.
   
   @param rhs The second value to test.
   
   @result true if the two values are equal, false if they are not
   equal.
   */
  HAL_EXPORT bool operator==(const JSValue& lhs, const JSValue& rhs) HAL_NOEXCEPT;
  
  // Return true if the two JSValues are not strict equal, as compared by the JS === operator.
  inline
  bool operator!=(const JSValue& lhs, const JSValue& rhs) HAL_NOEXCEPT {
    return ! (lhs == rhs);
  }
  
  /*!
   @function
   
   @abstract Determine whether two JavaScript values are equal, as
   compared by the JS == operator.
   
   @param lhs The first value to test.
   
   @param rhs The second value to test.
   
   @result true if the two values are equal, false if they are not
   equal.
   */
  HAL_EXPORT bool IsEqualWithTypeCoercion(const JSValue& lhs, const JSValue& rhs);
  
  inline
  std::ostream& operator << (std::ostream& ostream, const JSValue& js_value) {
    ostream << to_string(js_value);
    return ostream;
  }
  
  inline
  std::ostream& operator << (std::ostream& ostream, const JSValue::Type& js_value_type) {
    ostream << to_string(js_value_type);
    return ostream;
  }
  
} // namespace HAL {

#endif // _HAL_JSVALUE_HPP_
