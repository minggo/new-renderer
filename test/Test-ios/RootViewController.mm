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
#include "gfx/Basic.h"
#include "gfx/Bunny.h"
#include "gfx/Blending.h"
#include "gfx/MultiTextures.h"
#include "gfx/Particle.h"
#include "gfx/Stencil.h"
#include "gfx/PostProcess.h"
#include "gfx/DepthTexture.h"
#include "gfx/GuiProjection.h"

namespace {

    int nextIndex = 0;
    using createFunc = TestBaseI* (*)();
    std::vector<createFunc> tests;
    TestBaseI* test = nullptr;

    void initTests()
    {
        tests = {
//            Basic::create,
//            Bunny::create,
//            Blending::create,
//            MultiTextures::create,
//            Particle::create,
//            Stencil::create,
//            PostProcess::create,
//            DepthTexture::create,
            GuiProjection::create,
        };

        test = tests[0]();
    }
}

@interface RootViewController ()

@end

@implementation RootViewController

- (void) tick: (id) sender {
    test->tick(0.016f); // FIXME:
    [((CCEAGLView*)self.view) swapBuffers];
}

// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
    // Initialize the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [UIScreen mainScreen].bounds
                                         pixelFormat: kEAGLColorFormatRGB565
                                         depthFormat: GL_DEPTH_COMPONENT24_OES
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: NO
                                     numberOfSamples: 0 ];

    // Enable or disable multiple touches
    [eaglView setMultipleTouchEnabled:YES];

    // Set EAGLView as view of RootViewController
    self.view = eaglView;

    initTests();

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
