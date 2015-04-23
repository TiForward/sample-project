/**
 * HAL
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _HAL_DETAIL_JSPERFORMANCECOUNTERPRINTER_HPP_
#define _HAL_DETAIL_JSPERFORMANCECOUNTERPRINTER_HPP_

#ifdef HAL_PERFORMANCE_COUNTER_ENABLE

#include "HAL.hpp"
#include <iostream>

namespace HAL { namespace detail {
  
  class HAL_EXPORT JSPerformanceCounterPrinter {
  public:
    
    JSPerformanceCounterPrinter()                                              = default;
    JSPerformanceCounterPrinter(const JSPerformanceCounterPrinter&)            = delete;
    JSPerformanceCounterPrinter(JSPerformanceCounterPrinter&&)                 = delete;
    JSPerformanceCounterPrinter& operator=(const JSPerformanceCounterPrinter&) = delete;
    JSPerformanceCounterPrinter& operator=(JSPerformanceCounterPrinter&&)      = delete;
    
    ~JSPerformanceCounterPrinter() {
      static const std::string log_prefix { "MDL: JSPerformanceCounterPrinter: " };
      std::clog << log_prefix << std::endl;
      
      std::clog << std::endl;
      std::clog << "JSContextGroup:            objects_alive            = " << JSPerformanceCounter<JSContextGroup>::get_objects_alive()            << std::endl;
      std::clog << "JSContextGroup:            objects_created          = " << JSPerformanceCounter<JSContextGroup>::get_objects_created()          << std::endl;
      std::clog << "JSContextGroup:            objects_destroyed        = " << JSPerformanceCounter<JSContextGroup>::get_objects_destroyed()        << std::endl;
      std::clog << "JSContextGroup:            objects_copy_constructed = " << JSPerformanceCounter<JSContextGroup>::get_objects_copy_constructed() << std::endl;
      std::clog << "JSContextGroup:            objects_move_constructed = " << JSPerformanceCounter<JSContextGroup>::get_objects_move_constructed() << std::endl;
      std::clog << "JSContextGroup:            objects_copy_assigned    = " << JSPerformanceCounter<JSContextGroup>::get_objects_copy_assigned()    << std::endl;
      std::clog << "JSContextGroup:            objects_move_assigned    = " << JSPerformanceCounter<JSContextGroup>::get_objects_move_assigned()    << std::endl;
      
      std::clog << std::endl;
      std::clog << "JSContext:                 objects_alive            = " << JSPerformanceCounter<JSContext>::get_objects_alive()            << std::endl;
      std::clog << "JSContext:                 objects_created          = " << JSPerformanceCounter<JSContext>::get_objects_created()          << std::endl;
      std::clog << "JSContext:                 objects_destroyed        = " << JSPerformanceCounter<JSContext>::get_objects_destroyed()        << std::endl;
      std::clog << "JSContext:                 objects_copy_constructed = " << JSPerformanceCounter<JSContext>::get_objects_copy_constructed() << std::endl;
      std::clog << "JSContext:                 objects_move_constructed = " << JSPerformanceCounter<JSContext>::get_objects_move_constructed() << std::endl;
      std::clog << "JSContext:                 objects_copy_assigned    = " << JSPerformanceCounter<JSContext>::get_objects_copy_assigned()    << std::endl;
      std::clog << "JSContext:                 objects_move_assigned    = " << JSPerformanceCounter<JSContext>::get_objects_move_assigned()    << std::endl;
      
      std::clog << std::endl;
      std::clog << "JSString:                  objects_alive            = " << JSPerformanceCounter<JSString>::get_objects_alive()            << std::endl;
      std::clog << "JSString:                  objects_created          = " << JSPerformanceCounter<JSString>::get_objects_created()          << std::endl;
      std::clog << "JSString:                  objects_destroyed        = " << JSPerformanceCounter<JSString>::get_objects_destroyed()        << std::endl;
      std::clog << "JSString:                  objects_copy_constructed = " << JSPerformanceCounter<JSString>::get_objects_copy_constructed() << std::endl;
      std::clog << "JSString:                  objects_move_constructed = " << JSPerformanceCounter<JSString>::get_objects_move_constructed() << std::endl;
      std::clog << "JSString:                  objects_copy_assigned    = " << JSPerformanceCounter<JSString>::get_objects_copy_assigned()    << std::endl;
      std::clog << "JSString:                  objects_move_assigned    = " << JSPerformanceCounter<JSString>::get_objects_move_assigned()    << std::endl;
      
      std::clog << std::endl;
      std::clog << "JSValue:                   objects_alive            = " << JSPerformanceCounter<JSValue>::get_objects_alive()            << std::endl;
      std::clog << "JSValue:                   objects_created          = " << JSPerformanceCounter<JSValue>::get_objects_created()          << std::endl;
      std::clog << "JSValue:                   objects_destroyed        = " << JSPerformanceCounter<JSValue>::get_objects_destroyed()        << std::endl;
      std::clog << "JSValue:                   objects_copy_constructed = " << JSPerformanceCounter<JSValue>::get_objects_copy_constructed() << std::endl;
      std::clog << "JSValue:                   objects_move_constructed = " << JSPerformanceCounter<JSValue>::get_objects_move_constructed() << std::endl;
      std::clog << "JSValue:                   objects_copy_assigned    = " << JSPerformanceCounter<JSValue>::get_objects_copy_assigned()    << std::endl;
      std::clog << "JSValue:                   objects_move_assigned    = " << JSPerformanceCounter<JSValue>::get_objects_move_assigned()    << std::endl;
      
      std::clog << std::endl;
      std::clog << "JSUndefined:               objects_alive            = " << JSPerformanceCounter<JSUndefined>::get_objects_alive()            << std::endl;
      std::clog << "JSUndefined:               objects_alive            = " << JSPerformanceCounter<JSUndefined>::get_objects_alive()            << std::endl;
      std::clog << "JSUndefined:               objects_created          = " << JSPerformanceCounter<JSUndefined>::get_objects_created()          << std::endl;
      std::clog << "JSUndefined:               objects_destroyed        = " << JSPerformanceCounter<JSUndefined>::get_objects_destroyed()        << std::endl;
      std::clog << "JSUndefined:               objects_copy_constructed = " << JSPerformanceCounter<JSUndefined>::get_objects_copy_constructed() << std::endl;
      std::clog << "JSUndefined:               objects_move_constructed = " << JSPerformanceCounter<JSUndefined>::get_objects_move_constructed() << std::endl;
      std::clog << "JSUndefined:               objects_copy_assigned    = " << JSPerformanceCounter<JSUndefined>::get_objects_copy_assigned()    << std::endl;
      std::clog << "JSUndefined:               objects_move_assigned    = " << JSPerformanceCounter<JSUndefined>::get_objects_move_assigned()    << std::endl;
      
      std::clog << std::endl;
      std::clog << "JSNull:                    objects_alive            = " << JSPerformanceCounter<JSNull>::get_objects_alive()            << std::endl;
      std::clog << "JSNull:                    objects_created          = " << JSPerformanceCounter<JSNull>::get_objects_created()          << std::endl;
      std::clog << "JSNull:                    objects_destroyed        = " << JSPerformanceCounter<JSNull>::get_objects_destroyed()        << std::endl;
      std::clog << "JSNull:                    objects_copy_constructed = " << JSPerformanceCounter<JSNull>::get_objects_copy_constructed() << std::endl;
      std::clog << "JSNull:                    objects_move_constructed = " << JSPerformanceCounter<JSNull>::get_objects_move_constructed() << std::endl;
      std::clog << "JSNull:                    objects_copy_assigned    = " << JSPerformanceCounter<JSNull>::get_objects_copy_assigned()    << std::endl;
      std::clog << "JSNull:                    objects_move_assigned    = " << JSPerformanceCounter<JSNull>::get_objects_move_assigned()    << std::endl;
      
      std::clog << std::endl;
      std::clog << "JSBoolean:                 objects_alive            = " << JSPerformanceCounter<JSBoolean>::get_objects_alive()            << std::endl;
      std::clog << "JSBoolean:                 objects_created          = " << JSPerformanceCounter<JSBoolean>::get_objects_created()          << std::endl;
      std::clog << "JSBoolean:                 objects_destroyed        = " << JSPerformanceCounter<JSBoolean>::get_objects_destroyed()        << std::endl;
      std::clog << "JSBoolean:                 objects_copy_constructed = " << JSPerformanceCounter<JSBoolean>::get_objects_copy_constructed() << std::endl;
      std::clog << "JSBoolean:                 objects_move_constructed = " << JSPerformanceCounter<JSBoolean>::get_objects_move_constructed() << std::endl;
      std::clog << "JSBoolean:                 objects_copy_assigned    = " << JSPerformanceCounter<JSBoolean>::get_objects_copy_assigned()    << std::endl;
      std::clog << "JSBoolean:                 objects_move_assigned    = " << JSPerformanceCounter<JSBoolean>::get_objects_move_assigned()    << std::endl;
      
      std::clog << std::endl;
      std::clog << "JSNumber:                  objects_alive            = " << JSPerformanceCounter<JSNumber>::get_objects_alive()            << std::endl;
      std::clog << "JSNumber:                  objects_created          = " << JSPerformanceCounter<JSNumber>::get_objects_created()          << std::endl;
      std::clog << "JSNumber:                  objects_destroyed        = " << JSPerformanceCounter<JSNumber>::get_objects_destroyed()        << std::endl;
      std::clog << "JSNumber:                  objects_copy_constructed = " << JSPerformanceCounter<JSNumber>::get_objects_copy_constructed() << std::endl;
      std::clog << "JSNumber:                  objects_move_constructed = " << JSPerformanceCounter<JSNumber>::get_objects_move_constructed() << std::endl;
      std::clog << "JSNumber:                  objects_copy_assigned    = " << JSPerformanceCounter<JSNumber>::get_objects_copy_assigned()    << std::endl;
      std::clog << "JSNumber:                  objects_move_assigned    = " << JSPerformanceCounter<JSNumber>::get_objects_move_assigned()    << std::endl;
      
      std::clog << std::endl;
      std::clog << "JSObject:                  objects_alive            = " << JSPerformanceCounter<JSObject>::get_objects_alive()            << std::endl;
      std::clog << "JSObject:                  objects_created          = " << JSPerformanceCounter<JSObject>::get_objects_created()          << std::endl;
      std::clog << "JSObject:                  objects_destroyed        = " << JSPerformanceCounter<JSObject>::get_objects_destroyed()        << std::endl;
      std::clog << "JSObject:                  objects_copy_constructed = " << JSPerformanceCounter<JSObject>::get_objects_copy_constructed() << std::endl;
      std::clog << "JSObject:                  objects_move_constructed = " << JSPerformanceCounter<JSObject>::get_objects_move_constructed() << std::endl;
      std::clog << "JSObject:                  objects_copy_assigned    = " << JSPerformanceCounter<JSObject>::get_objects_copy_assigned()    << std::endl;
      std::clog << "JSObject:                  objects_move_assigned    = " << JSPerformanceCounter<JSObject>::get_objects_move_assigned()    << std::endl;
      
      std::clog << std::endl;
      std::clog << "JSArray:                   objects_alive            = " << JSPerformanceCounter<JSArray>::get_objects_alive()            << std::endl;
      std::clog << "JSArray:                   objects_created          = " << JSPerformanceCounter<JSArray>::get_objects_created()          << std::endl;
      std::clog << "JSArray:                   objects_destroyed        = " << JSPerformanceCounter<JSArray>::get_objects_destroyed()        << std::endl;
      std::clog << "JSArray:                   objects_copy_constructed = " << JSPerformanceCounter<JSArray>::get_objects_copy_constructed() << std::endl;
      std::clog << "JSArray:                   objects_move_constructed = " << JSPerformanceCounter<JSArray>::get_objects_move_constructed() << std::endl;
      std::clog << "JSArray:                   objects_copy_assigned    = " << JSPerformanceCounter<JSArray>::get_objects_copy_assigned()    << std::endl;
      std::clog << "JSArray:                   objects_move_assigned    = " << JSPerformanceCounter<JSArray>::get_objects_move_assigned()    << std::endl;
      
      std::clog << std::endl;
      std::clog << "JSDate:                    objects_alive            = " << JSPerformanceCounter<JSDate>::get_objects_alive()            << std::endl;
      std::clog << "JSDate:                    objects_created          = " << JSPerformanceCounter<JSDate>::get_objects_created()          << std::endl;
      std::clog << "JSDate:                    objects_destroyed        = " << JSPerformanceCounter<JSDate>::get_objects_destroyed()        << std::endl;
      std::clog << "JSDate:                    objects_copy_constructed = " << JSPerformanceCounter<JSDate>::get_objects_copy_constructed() << std::endl;
      std::clog << "JSDate:                    objects_move_constructed = " << JSPerformanceCounter<JSDate>::get_objects_move_constructed() << std::endl;
      std::clog << "JSDate:                    objects_copy_assigned    = " << JSPerformanceCounter<JSDate>::get_objects_copy_assigned()    << std::endl;
      std::clog << "JSDate:                    objects_move_assigned    = " << JSPerformanceCounter<JSDate>::get_objects_move_assigned()    << std::endl;
      
      std::clog << std::endl;
      std::clog << "JSError:                   objects_alive            = " << JSPerformanceCounter<JSError>::get_objects_alive()            << std::endl;
      std::clog << "JSError:                   objects_created          = " << JSPerformanceCounter<JSError>::get_objects_created()          << std::endl;
      std::clog << "JSError:                   objects_destroyed        = " << JSPerformanceCounter<JSError>::get_objects_destroyed()        << std::endl;
      std::clog << "JSError:                   objects_copy_constructed = " << JSPerformanceCounter<JSError>::get_objects_copy_constructed() << std::endl;
      std::clog << "JSError:                   objects_move_constructed = " << JSPerformanceCounter<JSError>::get_objects_move_constructed() << std::endl;
      std::clog << "JSError:                   objects_copy_assigned    = " << JSPerformanceCounter<JSError>::get_objects_copy_assigned()    << std::endl;
      std::clog << "JSError:                   objects_move_assigned    = " << JSPerformanceCounter<JSError>::get_objects_move_assigned()    << std::endl;
      
      std::clog << std::endl;
      std::clog << "JSFunction:                objects_alive            = " << JSPerformanceCounter<JSFunction>::get_objects_alive()            << std::endl;
      std::clog << "JSFunction:                objects_created          = " << JSPerformanceCounter<JSFunction>::get_objects_created()          << std::endl;
      std::clog << "JSFunction:                objects_destroyed        = " << JSPerformanceCounter<JSFunction>::get_objects_destroyed()        << std::endl;
      std::clog << "JSFunction:                objects_copy_constructed = " << JSPerformanceCounter<JSFunction>::get_objects_copy_constructed() << std::endl;
      std::clog << "JSFunction:                objects_move_constructed = " << JSPerformanceCounter<JSFunction>::get_objects_move_constructed() << std::endl;
      std::clog << "JSFunction:                objects_copy_assigned    = " << JSPerformanceCounter<JSFunction>::get_objects_copy_assigned()    << std::endl;
      std::clog << "JSFunction:                objects_move_assigned    = " << JSPerformanceCounter<JSFunction>::get_objects_move_assigned()    << std::endl;
      
      std::clog << std::endl;
      std::clog << "JSRegExp:                  objects_alive            = " << JSPerformanceCounter<JSRegExp>::get_objects_alive()            << std::endl;
      std::clog << "JSRegExp:                  objects_created          = " << JSPerformanceCounter<JSRegExp>::get_objects_created()          << std::endl;
      std::clog << "JSRegExp:                  objects_destroyed        = " << JSPerformanceCounter<JSRegExp>::get_objects_destroyed()        << std::endl;
      std::clog << "JSRegExp:                  objects_copy_constructed = " << JSPerformanceCounter<JSRegExp>::get_objects_copy_constructed() << std::endl;
      std::clog << "JSRegExp:                  objects_move_constructed = " << JSPerformanceCounter<JSRegExp>::get_objects_move_constructed() << std::endl;
      std::clog << "JSRegExp:                  objects_copy_assigned    = " << JSPerformanceCounter<JSRegExp>::get_objects_copy_assigned()    << std::endl;
      std::clog << "JSRegExp:                  objects_move_assigned    = " << JSPerformanceCounter<JSRegExp>::get_objects_move_assigned()    << std::endl;
      
      std::clog << std::endl;
      std::clog << "JSClass:                   objects_alive            = " << JSPerformanceCounter<JSClass>::get_objects_alive()            << std::endl;
      std::clog << "JSClass:                   objects_created          = " << JSPerformanceCounter<JSClass>::get_objects_created()          << std::endl;
      std::clog << "JSClass:                   objects_destroyed        = " << JSPerformanceCounter<JSClass>::get_objects_destroyed()        << std::endl;
      std::clog << "JSClass:                   objects_copy_constructed = " << JSPerformanceCounter<JSClass>::get_objects_copy_constructed() << std::endl;
      std::clog << "JSClass:                   objects_move_constructed = " << JSPerformanceCounter<JSClass>::get_objects_move_constructed() << std::endl;
      std::clog << "JSClass:                   objects_copy_assigned    = " << JSPerformanceCounter<JSClass>::get_objects_copy_assigned()    << std::endl;
      std::clog << "JSClass:                   objects_move_assigned    = " << JSPerformanceCounter<JSClass>::get_objects_move_assigned()    << std::endl;
      
      std::clog << std::endl;
      std::clog << "JSPropertyNameAccumulator: objects_alive            = " << JSPerformanceCounter<JSPropertyNameAccumulator>::get_objects_alive()            << std::endl;
      std::clog << "JSPropertyNameAccumulator: objects_created          = " << JSPerformanceCounter<JSPropertyNameAccumulator>::get_objects_created()          << std::endl;
      std::clog << "JSPropertyNameAccumulator: objects_destroyed        = " << JSPerformanceCounter<JSPropertyNameAccumulator>::get_objects_destroyed()        << std::endl;
      std::clog << "JSPropertyNameAccumulator: objects_copy_constructed = " << JSPerformanceCounter<JSPropertyNameAccumulator>::get_objects_copy_constructed() << std::endl;
      std::clog << "JSPropertyNameAccumulator: objects_move_constructed = " << JSPerformanceCounter<JSPropertyNameAccumulator>::get_objects_move_constructed() << std::endl;
      std::clog << "JSPropertyNameAccumulator: objects_copy_assigned    = " << JSPerformanceCounter<JSPropertyNameAccumulator>::get_objects_copy_assigned()    << std::endl;
      std::clog << "JSPropertyNameAccumulator: objects_move_assigned    = " << JSPerformanceCounter<JSPropertyNameAccumulator>::get_objects_move_assigned()    << std::endl;
    }
  };
  
}} // namespace HAL { namespace detail {

#endif  // HAL_PERFORMANCE_COUNTER_ENABLE

#endif // _HAL_DETAIL_JSPERFORMANCECOUNTERPRINTER_HPP_

