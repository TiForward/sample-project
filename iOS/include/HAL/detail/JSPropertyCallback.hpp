/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_DETAIL_JSPROPERTYCALLBACK_HPP_
#define _HAL_DETAIL_JSPROPERTYCALLBACK_HPP_

#include "HAL/detail/JSBase.hpp"
#include "HAL/JSPropertyAttribute.hpp"

#include <string>
#include <unordered_set>

namespace HAL { namespace detail {
  
  /*!
   @class
   
   @discussion JSPropertyCallback is the base class for JSStaticValue,
   JSStaticFunction, JSExportValuePropertyCallback and
   JSExportFunctionPropertyCallback.
   */
  class HAL_EXPORT JSPropertyCallback HAL_PERFORMANCE_COUNTER1(JSPropertyCallback) {
    
  public:
    
    /*!
     @method
     
     @abstract Set the name and property attributes of a callback.
     
     @param name The property's name.
     
     @param attributes The set of JSPropertyAttributes to give to
     the property.
     
     @result An object which describes the name and property
     attributes a JavaScript property.
     
     @throws std::invalid_argument if property_name is empty.
     */
    JSPropertyCallback(const std::string& name, const std::unordered_set<JSPropertyAttribute, std::hash<JSPropertyAttribute>>& attributes);
    
    virtual std::string get_name() const HAL_NOEXCEPT final {
      return name__;
    }
    
    virtual std::unordered_set<JSPropertyAttribute> get_attributes() const HAL_NOEXCEPT final {
      return attributes__;
    }
    
    virtual ~JSPropertyCallback()                            = default;
    JSPropertyCallback(const JSPropertyCallback&)            HAL_NOEXCEPT;
    JSPropertyCallback(JSPropertyCallback&&)                 HAL_NOEXCEPT;
    JSPropertyCallback& operator=(const JSPropertyCallback&) HAL_NOEXCEPT;
    JSPropertyCallback& operator=(JSPropertyCallback&&)      HAL_NOEXCEPT;
    void swap(JSPropertyCallback&)                           HAL_NOEXCEPT;
    
  private:
    
    friend bool operator==(const JSPropertyCallback& lhs, const JSPropertyCallback& rhs) HAL_NOEXCEPT;
    
    // Silence 4251 on Windows since private member variables do not
    // need to be exported from a DLL.
#pragma warning(push)
#pragma warning(disable: 4251)
    std::string name__;
#pragma warning(pop)
    
  protected:
    
    // Silence 4251 on Windows since private member variables do not
    // need to be exported from a DLL.
#pragma warning(push)
#pragma warning(disable: 4251)
    std::unordered_set<JSPropertyAttribute> attributes__;
#pragma warning(pop)
    
#undef HAL_DETAIL_JSPROPERTYCALLBACK_LOCK_GUARD
#ifdef HAL_THREAD_SAFE
    std::recursive_mutex             mutex__;
#define HAL_DETAIL_JSPROPERTYCALLBACK_LOCK_GUARD std::lock_guard<std::recursive_mutex> lock_guard(mutex__)
#else
#define HAL_DETAIL_JSPROPERTYCALLBACK_LOCK_GUARD
#endif  // HAL_THREAD_SAFE
  };
  
  inline
  void swap(JSPropertyCallback& first, JSPropertyCallback& second) HAL_NOEXCEPT {
    first.swap(second);
  }

  // Return true if the two JSPropertyCallbacks are equal.
  inline
  bool operator==(const JSPropertyCallback& lhs, const JSPropertyCallback& rhs) HAL_NOEXCEPT {
    return (lhs.name__ != rhs.name__) && (lhs.attributes__ == rhs.attributes__);
  }
  
  // Return true if the two JSPropertyCallback are not equal.
  inline
  bool operator!=(const JSPropertyCallback& lhs, const JSPropertyCallback& rhs) HAL_NOEXCEPT {
    return ! (lhs == rhs);
  }
  
}} // HAL { namespace detail {

#endif // _HAL_DETAIL_JSPROPERTYCALLBACK_HPP_
