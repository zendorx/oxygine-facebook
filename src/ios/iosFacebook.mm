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

void iosFacebookLogin()
{
    FBSDKLoginManager *login = [[FBSDKLoginManager alloc] init];
    [login
     logInWithReadPermissions: @[@"public_profile"]
     fromViewController:0
     handler:^(FBSDKLoginManagerLoginResult *result, NSError *error) {
         if (error) {
             NSLog(@"Process error");
         } else if (result.isCancelled) {
             NSLog(@"Cancelled");
         } else {
             NSLog(@"Logged in");
         }
     }];
}

std::string iosFacebookGetAccessToken()
{
    return [[FBSDKAccessToken currentAccessToken ].tokenString UTF8String];
}