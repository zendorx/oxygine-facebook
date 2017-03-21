//
//  iosFacebook.m
//  HelloWorldFacebook_ios
//
//  Created by Denis on 17/03/16.
//  Copyright © 2016 Mac. All rights reserved.
//
#include "iosFacebook.h"
#import <Foundation/Foundation.h>
#import <FBSDKCoreKit/FBSDKCoreKit.h>
#import <FBSDKLoginKit/FBSDKLoginKit.h>
#include "facebook.h"

UIViewController * getViewcontrollerForFB(void)
{
    @try {
        UIWindow *window = [[UIApplication sharedApplication] keyWindow];
        if ( window == nullptr )
            return nullptr;
    
        UIView* view = [window.subviews objectAtIndex:0];
        if(!view)
            return nullptr;
        id nextResponder = [view nextResponder];
        if(!nextResponder)
            return nullptr;
        if( [nextResponder isKindOfClass:[UIViewController class]] )
            return (UIViewController *)nextResponder;
    }
    @catch(NSException *e) {
    }
    return nullptr;
}

void iosFacebookLogin()
{
    FBSDKLoginManager *login = [[FBSDKLoginManager alloc] init];
    [login
     logInWithReadPermissions: @[@"public_profile"]
     fromViewController: getViewcontrollerForFB()
     handler:^(FBSDKLoginManagerLoginResult *result, NSError *error) {
         
         if (error) {
             facebook::internal::loginResult(false);
         } else if (result.isCancelled) {
             facebook::internal::loginResult(false);
         } else {
             NSLog(@"Logged in");
             facebook::internal::loginResult(true);
         }
     }];
}

void iosFacebookLogout()
{
    FBSDKLoginManager *loginManager = [[FBSDKLoginManager alloc] init];
    [loginManager logOut];
}

std::string iosFacebookGetAccessToken()
{
    if ([FBSDKAccessToken currentAccessToken])
        return [[FBSDKAccessToken currentAccessToken ].tokenString UTF8String];
    return "";
}

std::string iosFacebookGetUserID()
{
    if ([FBSDKAccessToken currentAccessToken])
        return [[FBSDKAccessToken currentAccessToken].userID UTF8String];
    return "";
}

std::string iosFacebookGetAppID()
{
    return [[FBSDKSettings appID] UTF8String];
}
