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

#include "Utils.h"

static std::chrono::steady_clock::time_point prevTime;
static float dtSum = 0.0f;
static float dt = 0.0f;
static int dtCounter = 0;
static se::Value tickVal;
static UITextView* __bunnyCoutTextView = nil;

static bool setBunnyCount(se::State& s)
{
    const auto& args = s.args();
    assert(args.size() > 0);
    [__bunnyCoutTextView setText:[NSString stringWithFormat:@"Bunny: %d", args[0].toInt32()]];
    return true;
}
SE_BIND_FUNC(setBunnyCount)

@interface RootViewController ()

@end

@implementation RootViewController

@synthesize fpsTextView = _fpsTextView;

- (void) tick: (id) sender {

    se::AutoHandleScope hs;
    se::ValueArray args;
    args.push_back(se::Value(dt));
    tickVal.toObject()->call(args, nullptr);
    [((CCEAGLView*)self.view) swapBuffers];

    dt = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - prevTime).count() / 1000000.f;

    dtSum += dt;
    ++dtCounter;
    if (dtSum > 1.0f)
    {
        int fps = (int)std::ceil(1.0f / (dtSum / dtCounter));
        [self.fpsTextView setText:[NSString stringWithFormat:@"FPS: %d", fps]];
        dtCounter = 0;
        dtSum = 0.0f;
    }

    prevTime = std::chrono::steady_clock::now();
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

    self.fpsTextView = [[UITextView alloc] initWithFrame:CGRectMake(0, 0, 60, 30)];
    [self.fpsTextView setTextAlignment:NSTextAlignmentLeft];
    [eaglView addSubview: self.fpsTextView];

    __bunnyCoutTextView = [[UITextView alloc] initWithFrame:CGRectMake(0, 40, 100, 30)];
    [__bunnyCoutTextView setTextAlignment:NSTextAlignmentLeft];
    [__bunnyCoutTextView setText:@"Bunny: 20"];
    [eaglView addSubview: __bunnyCoutTextView];

    eaglView.touchCallback = ^(TouchEventType type, NSSet* touches, UIEvent* event) {
//        NSLog(@"type: %d", (int)type);
        auto se = se::ScriptEngine::getInstance();
        se->clearException();
        se::AutoHandleScope hs;

        auto global = se->getGlobalObject();
        se::Value touchUpFuncVal;
        if (global->getProperty("onTouchEvent", &touchUpFuncVal))
        {
            UITouch* touch = [touches anyObject];
            float x = [touch locationInView: [touch view]].x * scale;
            float y = [touch locationInView: [touch view]].y * scale;

            se::ValueArray args;
            args.push_back(se::Value((int)type));
            args.push_back(se::Value(x));
            args.push_back(se::Value(y));
            touchUpFuncVal.toObject()->call(args, nullptr);
        }
    };

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

    se->getGlobalObject()->defineFunction("__setBunnyCount", _SE(setBunnyCount));

    se::AutoHandleScope hs;

    char commandBuf[200] = {0};
    sprintf(commandBuf, "window.canvas = { width: %d, height: %d };", utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    se->evalString(commandBuf);
    se->runScript("src/gfx.js");
    se->runScript("src/renderer-test/main-jsb.js");
    se->runScript("src/renderer-test/src/basic.js", &tickVal);

    se->addAfterCleanupHook([](){
        JSBClassType::destroy();
    });

    [[CCDirectorCaller sharedDirectorCaller] startMainLoop:self selector: @selector(tick:)];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

-(void) dealloc {
    self.fpsTextView = nil;
    [__bunnyCoutTextView release];
    __bunnyCoutTextView = nil;
    [super dealloc];
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
