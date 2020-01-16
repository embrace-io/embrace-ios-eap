//
//  Embrace+ReactNative.h
//  Embrace
//
//  Created by Juan Pablo on 01/10/2019.
//  Copyright © 2019 embrace.io. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RNEmbrace: NSObject

/**
 Returns the shared `RNEmbrace` singleton object.
 */
+ (instancetype)sharedInstance;

/**
 
 */
- (void)logUnhandledJSException:(NSString *)name
                        message:(NSString *)message
                           type:(NSString *)type
                     stackTrace:(NSString *)stackTrace;

/**

 */
- (void)setReactNativeVersion:(NSString *)version;

/**
 
 */
- (void)setJavaScriptPatchNumber:(NSString *)number;

/**
 
 */
- (void)setJavaScriptBundleURL:(NSString *)url;

/**

*/
- (void)logMessage:(NSString *)name
      withSeverity:(EMBSeverity)severity
        properties:(NSDictionary *)properties
    takeScreenshot:(BOOL)takeScreenshot
      jsStackTrace:(NSString *)jsStackTrace;

@end