//
//  ViewController.m
//  Test-ios
//
//  Created by James Chen on 12/29/17.
//  Copyright © 2017 cocos. All rights reserved.
//

#import "RootViewController.h"
#import "platform/ios/CCEAGLView-ios.h"
#import "platform/ios/CCDirectorCaller-ios.h"

#include <chrono>
#include "TestBase.h"
#include "defines.h"

#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "cocos/scripting/js-bindings/auto/jsb_gfx_auto.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_global.h"
#include "cocos/scripting/js-bindings/manual/jsb_classtype.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_gfx_manual.hpp"


@interface RootViewController ()

@end

@implementation RootViewController

se::Value tickVal;

- (void) tick: (id) sender {
     // FIXME:
    float dt = 0.016f;
    se::ValueArray args;
    args.push_back(se::Value(dt));
    tickVal.toObject()->call(args, nullptr);

    [((CCEAGLView*)self.view) swapBuffers];
}

// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
    CGRect rect = [UIScreen mainScreen].bounds;
    // Initialize the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: rect
                                         pixelFormat: kEAGLColorFormatRGB565
                                         depthFormat: GL_DEPTH_COMPONENT24_OES
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: NO
                                     numberOfSamples: 0 ];

    float scale = [[UIScreen mainScreen] scale];
    utils::WINDOW_WIDTH = rect.size.width * scale;
    utils::WINDOW_HEIGHT = rect.size.height * scale;

    // Enable or disable multiple touches
    [eaglView setMultipleTouchEnabled:YES];

    // Set EAGLView as view of RootViewController
    self.view = eaglView;

    auto se = se::ScriptEngine::getInstance();
    se->addRegisterCallback(jsb_register_global_variables);
    se->addRegisterCallback(register_all_gfx);
    se->addRegisterCallback(jsb_register_gfx_manual);

    se->enableDebugger("0.0.0.0", 5678);

    se->addBeforeInitHook([](){
        JSBClassType::init();
    });

    jsb_init_file_operation_delegate();

    se->start();

    se::AutoHandleScope hs;

    char commandBuf[200] = {0};
    sprintf(commandBuf, "window.canvas = { width: %d, height: %d };", utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    se->evalString(commandBuf);
    se->runScript("src/gfx.js");

//    se->runScript("src/depth-texture.js", &tickVal);
    se->runScript("src/gui-projection.js", &tickVal);

    se->addAfterCleanupHook([](){
        JSBClassType::destroy();
    });

    [[CCDirectorCaller sharedDirectorCaller] startMainLoop:self selector: @selector(tick:)];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6.0 and higher, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations
{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}


@end
