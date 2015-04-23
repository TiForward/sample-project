/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_JSSTRING_HPP_
#define _HAL_JSSTRING_HPP_

#include "HAL/detail/JSBase.hpp"

#include <string>
#include <locale>
#include <codecvt>
#include <cstddef>
#include <vector>
#include <utility>
#include <mutex>

namespace HAL {
  class JSString;
}

namespace HAL { namespace detail {
  template<typename T>
  class JSExportClass;
  
  HAL_EXPORT std::vector<JSStringRef> to_vector(const std::vector<JSString>&);
}}

namespace HAL {
  
  /*!
   @class
   
   @discussion A JSString is an RAII wrapper around a JSStringRef, the
   JavaScriptCore C API representation of a JavaScript string.
   
   A JSString satisfies satisfies all the requirements for use in all
   STL containers. For example, a JSString can be used as a key in a
   std::unordered_map.
   
   Specifically, a JSString is comparable with an equivalence relation,
   provides a strict weak ordering, and provides a custom hash
   function.
   */
    class HAL_EXPORT JSString final HAL_PERFORMANCE_COUNTER1(JSString) {
      
    public:
      
      /*!
       @method
       
       @abstract Create an empty JavaScript string with a length of zero.
       
       @result An empty JavaScript string with a length of zero.
       */
      JSString() HAL_NOEXCEPT;
      
      /*!
       @method
       
       @abstract Create a JavaScript string from a null-terminated UTF8
       string.
       
       @param string The null-terminated UTF8 string to copy into the new
       JSString.
       
       @result A JSString containing string.
       */
      JSString(const char* string) HAL_NOEXCEPT;
      
      /*!
       @method
       
       @abstract Create a JavaScript string from a null-terminated UTF8
       string.
       
       @param string The null-terminated UTF8 string to copy into the new
       JSString.
       
       @result A JSString containing string.
       */
      JSString(const std::string& string) HAL_NOEXCEPT;
      
      /*!
       @method
       
       @abstract Return the number of Unicode characters in this
       JavaScript string.
       
       @result The number of Unicode characters in this JavaScript
       string.
       */
      const std::size_t length() const HAL_NOEXCEPT;
      
      /*!
       @method
       
       @abstract Return the number of Unicode characters in this
       JavaScript string.
       
       @result The number of Unicode characters in this JavaScript
       string.
       */
      const std::size_t size() const HAL_NOEXCEPT;
      
      /*!
       @method
       
       @abstract Return true if this JavaScript string has a length of
       zero.
       
       @result true if this JavaScript string has a length of zero.
       */
      const bool empty() const HAL_NOEXCEPT;
      
      /*!
       @method
       
       @abstract Convert this JavaScript string to a UTF-8 encoded
       std::string.
       
       @result This JavaScript string converted to a UTF-8 encoded
       std::string.
       */
      operator std::string() const HAL_NOEXCEPT;
      
      /*!
       @method
       
       @abstract Convert this JavaScript string to a UTF-16 encoded
       std::u16string.
       
       @result This JavaScript string converted to a UTF-16 encoded
       std::u16string.
       */
      operator std::u16string() const HAL_NOEXCEPT;
      
      std::size_t hash_value() const;
      
      ~JSString()                   HAL_NOEXCEPT;
      JSString(const JSString&)     HAL_NOEXCEPT;
      JSString(JSString&&)          HAL_NOEXCEPT;
      JSString& operator=(JSString) HAL_NOEXCEPT;
      void swap(JSString&)          HAL_NOEXCEPT;

    private:
      
      // These classes and functions need access to operator
      // JSStringRef().
      friend class JSContext;                 // JSEvaluateScript and JSCheckScriptSyntax
      friend class JSObject;                  // HasProperty
      friend class JSPropertyNameArray;       // GetNameAtIndex
      friend class JSPropertyNameAccumulator; // AddName
      friend class JSFunction;
      
      friend std::vector<JSStringRef> detail::to_vector(const std::vector<JSString>&);
      
      // For interoperability with the JavaScriptCore C API.
      explicit operator JSStringRef() const {
        return js_string_ref__;
      }
      
      // Only the following classes and functions can create a JSString.
      friend class JSValue;
      
      template<typename T>
      friend class detail::JSExportClass; // static functions
      
      // For interoperability with the JavaScriptCore C API.
      explicit JSString(JSStringRef js_string_ref) HAL_NOEXCEPT;
      
      // Prevent heap based objects.
      static void * operator new(std::size_t);     // #1: To prevent allocation of scalar objects
      static void * operator new [] (std::size_t); // #2: To prevent allocation of array of objects
      
      friend void swap(JSString& first, JSString& second) HAL_NOEXCEPT;
      HAL_EXPORT friend bool operator==(const JSString& lhs, const JSString& rhs);
      
    // Silence 4251 on Windows since private member variables do not
    // need to be exported from a DLL.
#pragma warning(push)
#pragma warning(disable: 4251)
      JSStringRef    js_string_ref__ { nullptr };
      std::string    string__;
      std::u16string u16string__;
      std::size_t    hash_value__;
#pragma warning(pop)
      
#undef HAL_JSSTRING_LOCK_GUARD
#ifdef  HAL_THREAD_SAFE
      std::recursive_mutex mutex__;
#define HAL_JSSTRING_LOCK_GUARD std::lock_guard<std::recursive_mutex> lock(mutex__)
#else
#define HAL_JSSTRING_LOCK_GUARD
#endif  // HAL_THREAD_SAFE
    };
    
    inline
    std::string to_string(const JSString& js_string) {
      return static_cast<std::string>(js_string);
    }
    
    // Return true if the two JSStrings are equal.
    HAL_EXPORT bool operator==(const JSString& lhs, const JSString& rhs);
    
    // Return true if the two JSStrings are not equal.
    inline
    HAL_EXPORT bool operator!=(const JSString& lhs, const JSString& rhs) {
      return ! (lhs == rhs);
    }
    
    // Define a strict weak ordering for two JSStrings.
    inline
    bool operator<(const JSString& lhs, const JSString& rhs) {
      return to_string(lhs) < to_string(rhs);
    }
    
    inline
    bool operator>(const JSString& lhs, const JSString& rhs) {
      return rhs < lhs;
    }
    
    inline
    bool operator<=(const JSString& lhs, const JSString& rhs) {
      return !(lhs > rhs);
    }
    
    inline
    bool operator>=(const JSString& lhs, const JSString& rhs) {
      return !(lhs < rhs);
    }
    
    inline
    std::ostream& operator << (std::ostream& ostream, const JSString& js_string) {
      ostream << to_string(js_string);
      return ostream;
    }
    
    inline
    void swap(JSString& first, JSString& second) HAL_NOEXCEPT {
      first.swap(second);
    }
    
  } // namespace HAL {
  
  namespace std {
    
    using HAL::JSString;
    
    template<>
    struct hash<JSString> {
      using argument_type = JSString;
      using result_type   = std::size_t;
      
      result_type operator()(const argument_type& js_string) const {
        return js_string.hash_value();
      }
    };
    
  }  // namespace std
  
#endif // _HAL_JSSTRING_HPP_
