//
//  main.m
//  testapp
//
//  Created by Matt Apperson on 4/21/15.
//  Copyright (c) 2015 Community. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "HAL/HAL.hpp"

int main(int argc, char * argv[]) {
    @autoreleasepool {
        HAL::JSContextGroup js_context_group;
        
        HAL::JSContext js_context = js_context_group.CreateContext();
        auto js_result       = js_context.JSEvaluateScript("1 + 2");
        NSString* result     = [NSString stringWithCString:static_cast<std::string>(js_result).c_str() encoding:[NSString defaultCStringEncoding]];
        
        NSLog(@"%@", result);
        
        return 0;
    }
}
