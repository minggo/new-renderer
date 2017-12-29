//
//  AppDelegate.h
//  Test-ios
//
//  Created by James Chen on 12/29/17.
//  Copyright © 2017 cocos. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RootViewController.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
@property(nonatomic, readonly) RootViewController* viewController;

@end

