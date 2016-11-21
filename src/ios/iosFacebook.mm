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

void iosFacebookLogin()
{
    FBSDKLoginManager *login = [[FBSDKLoginManager alloc] init];
    [login
     logInWithReadPermissions: @[@"public_profile"]
     fromViewController:0
     handler:^(FBSDKLoginManagerLoginResult *result, NSError *error) {
         facebook::internal::loginResult(error == 0);
         if (error) {
             NSLog(@"Process error");
         } else if (result.isCancelled) {
             NSLog(@"Cancelled");
         } else {
             NSLog(@"Logged in");
         }
     }];
}

void iosFacebookLogout()
{
    
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
