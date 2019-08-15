//
//  EmbraceConfig.h
//  Embrace
//
//  Created by Juan Pablo on 23/10/2018.
//  Copyright © 2018 embrace.io. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface EmbraceConfig : NSObject

/**
 Returns the default config. The first time this is called it synchronously reads
 Embrace-Info.plist from disk.
 Returns nil if a valid plist file is not find at default path.
 */
- (nullable instancetype)initWithDefaultConfig;

/**
 Initializes a customized instance of EmbraceConfig from the file at the given plist file path. This
 will read the file synchronously from disk.
 Returns nil if a valid plist file is not find at path.
 */
- (nullable instancetype)initWithContentsOfFile:(NSString *)path;

/**
 Initializes a customized instance of EmbraceConfig with required fields.
 Returns nil if an invalid app ID is specified.
 */
- (nullable instancetype)initWithAPIKey:(NSString *)apiKey;

@property(atomic, strong, readonly, nonnull) NSString *APIKey;
@property(atomic, strong, readonly, nullable) NSNumber *maxSessionSeconds;
@property(atomic, strong, readonly, nullable) NSDictionary<NSString *, NSNumber *> *networkCaptureDomains;
@property(atomic, strong, readonly, nullable) NSString *configBaseURL;
@property(atomic, strong, readonly, nullable) NSString *baseURL;
@property(atomic, strong, readonly, nullable) NSString *devBaseURL;
@property(atomic, strong, readonly, nullable) NSString *imagesBaseURL;
@property(atomic, assign, readonly) BOOL crashReportEnabled;
@property(atomic, assign, readonly) NSInteger networkCaptureLimit;
@property(atomic, assign, readonly) BOOL nsurlconnectionProxyEnable;
@property(atomic, assign, readonly) BOOL startupScreenshotEnabled;
@property(atomic, assign, readonly) BOOL webviewStripQueryparams;
@property(atomic, assign, readonly) BOOL webviewEnable;
@property(atomic, assign, readonly) BOOL backgroundFetchCaptureEnable;
@property(atomic, assign, readonly) BOOL collectNetworkRequestMetrics;
@property(atomic, assign, readonly) NSUInteger startupAutoendSeconds;
@property(atomic, strong, readonly) NSString *traceIdHeader;

@end

NS_ASSUME_NONNULL_END
