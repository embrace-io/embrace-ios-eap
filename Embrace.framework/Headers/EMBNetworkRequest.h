//
//  EMBNetworkRequest.h
//  Embrace
//
//  Created by Fredric Newberg on 7/5/19.
//  Copyright © 2019 embrace.io. All rights reserved.
//

/**
 This class is used to create manually-recorded network requests.
 */

#ifndef EMBNetworkRequest_h
#define EMBNetworkRequest_h

#import <Foundation/Foundation.h>

@interface EMBNetworkRequest : NSObject

@property (nonatomic, strong, readonly, nonnull) NSURL *url;
@property (nonatomic, strong, readonly, nonnull) NSString *method;
@property (nonatomic, strong, readonly, nonnull) NSDate *startTime;
@property (nonatomic, strong, nullable) NSDate *endTime;
@property (nonatomic, assign) NSInteger bytesIn;
@property (nonatomic, assign) NSInteger bytesOut;
@property (nonatomic, assign) NSInteger responseCode;
@property (nonatomic, strong, nullable) NSError *error;
@property (nonatomic, strong, nullable) NSString *traceId;

@property (nonatomic, assign, readonly) NSTimeInterval startEpoch;
@property (nonatomic, assign, readonly) NSTimeInterval endEpoch;

/**
 Creates an EMBNetwork Request with the URL, method, and start time set

 @param urlString The request's URL. Must start with http:// or https://
 @param method The request's method. Must be one of the following: GET, PUT, POST, DELETE, PATCH.
 @param startTime The time the request started.

 @return An EMBNetworkRequest object
 */
+ (nullable instancetype)initWithURLString:(nonnull NSString *)urlString method:(nonnull NSString *)method startTime:(nonnull NSDate *)startTime DEPRECATED_MSG_ATTRIBUTE("Please replace calls to initialize network requests with methods of the form networkRequestWithURLString:method:startTime:");
+ (nullable instancetype)networkRequestWithURLString:(nonnull NSString *)urlString method:(nonnull NSString *)method startTime:(nonnull NSDate *)startTime;

/**
 Creates an EMBNetwork Request with the URL, method, start time, end time, bytes sent, bytes received, response code, error, and traceId set.

 @param urlString The request's URL. Must start with http:// or https://
 @param method The request's method. Must be one of the following: GET, PUT, POST, DELETE, PATCH.
 @param startTime The time the request started.
 @param endTime The time the request ended. Must be greater than the startTime.
 @param bytesIn The number of bytes received.
 @param bytesOut The number of bytes received.
 @param responseCode The response status of the request. Must be in the range 100 to 599.
 @param error NSError that describes a non-HTTP error, e.g. a connection error.
 @param traceId Optional trace ID that can be used to trace a particular request. Max length is 64 characters.

 @return An EMBNetworkRequest object
 */
+ (nullable instancetype)initWithURLString:(nonnull NSString *)urlString method:(nonnull NSString *)method startTime:(nonnull NSDate *)startTime endTime:(nullable NSDate *)endTime bytesIn:(NSInteger)bytesIn bytesOut:(NSInteger)bytesOut responseCode:(NSInteger)responseCode error:(nullable NSError *)error traceId:(nullable NSString *)traceId DEPRECATED_MSG_ATTRIBUTE("Please replace calls to initialize network requests with methods of the form networkRequestWithURLString:method:startTime:endTime:bytesIn:bytesOut:responseCode:error:traceId:");
+ (nullable instancetype)networkRequestWithURLString:(nonnull NSString *)urlString method:(nonnull NSString *)method startTime:(nonnull NSDate *)startTime endTime:(nullable NSDate *)endTime bytesIn:(NSInteger)bytesIn bytesOut:(NSInteger)bytesOut responseCode:(NSInteger)responseCode error:(nullable NSError *)error traceId:(nullable NSString *)traceId;

/**
 Creates an EMBNetwork Request with the URL, method, and start time set

 @param url The request's NSURL. Must start with http:// or https://
 @param method The request's method. Must be one of the following: GET, PUT, POST, DELETE, PATCH.
 @param startTime The time the request started.

 @return An EMBNetworkRequest object
 */
+ (nullable instancetype)initWithURL:(nonnull NSURL *)url method:(nonnull NSString *)method startTime:(nonnull NSDate *)startTime DEPRECATED_MSG_ATTRIBUTE("Please replace calls to initialize network requests with methods of the form networkRequestWithURL:method:startTime:");
+ (nullable instancetype)networkRequestWithURL:(nonnull NSURL *)url method:(nonnull NSString *)method startTime:(nonnull NSDate *)startTime;

/**
 Creates an EMBNetwork Request with the URL, method, start time, end time, bytes sent, bytes received, response code, error, and traceId set.

 @param url The request's NSURL. Must start with http:// or https://
 @param method The request's method. Must be one of the following: GET, PUT, POST, DELETE, PATCH.
 @param startTime The time the request started.
 @param endTime The time the request ended. Must be greater than the startTime.
 @param bytesIn The number of bytes received.
 @param bytesOut The number of bytes received.
 @param responseCode The response status of the request. Must be in the range 100 to 599.
 @param error NSError that describes a non-HTTP error, e.g. a connection error.
 @param traceId Optional trace ID that can be used to trace a particular request. Max length is 64 characters.

 @return An EMBNetworkRequest object
 */
+ (nullable instancetype)initWithURL:(nonnull NSURL *)url method:(nonnull NSString *)method startTime:(nonnull NSDate *)startTime endTime:(nullable NSDate *)endTime bytesIn:(NSInteger)bytesIn bytesOut:(NSInteger)bytesOut responseCode:(NSInteger)responseCode error:(nullable NSError *)error traceId:(nullable NSString *)traceId DEPRECATED_MSG_ATTRIBUTE("Please replace calls to initialize network requests with methods of the form networkRequestWithURL:method:startTime:endTime:bytesIn:bytesOut:responseCode:error:traceId:");
+ (nullable instancetype)networkRequestWithURL:(nonnull NSURL *)url method:(nonnull NSString *)method startTime:(nonnull NSDate *)startTime endTime:(nullable NSDate *)endTime bytesIn:(NSInteger)bytesIn bytesOut:(NSInteger)bytesOut responseCode:(NSInteger)responseCode error:(nullable NSError *)error traceId:(nullable NSString *)traceId;

@end

#endif /* EMBNetworkRequest_h */
