#import "RootViewController.h"
#import "platform/ios/CCEAGLView-ios.h"
#import "platform/ios/CCDirectorCaller-ios.h"

#include <chrono>
#include "TestBase.h"
#include "defines.h"

#include "backend/BasicBackend.h"
#include "backend/Texture2DBackend.h"
#include "backend/BunnyBackend.h"
#include "backend/DepthTextureBackend.h"
#include "backend/BlendingBackend.h"
#include "backend/MultiTexturesBackend.h"
#include "backend/StencilBackend.h"
#include "backend/PostProcessBackend.h"
#include "backend/SubImageBackend.h"

#include "../Tests/Utils.h"

namespace
{
    int nextIndex = 0;
    using createFunc = TestBaseI* (*)();
    std::vector<createFunc> tests;
    TestBaseI* test = nullptr;

    void initTests()
    {
        tests = {
            SubImageBackend::create,
            PostProcessBackend::create,
            StencilBackend::create,
            MultiTexturesBackend::create,
            BlendingBackend::create,
            BasicBackend::create,
            BunnyBackend::create,
            Texture2DBackendTest::create,
            DepthTextureBackend::create,
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
    CGRect rect = [UIScreen mainScreen].bounds;
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: rect
                                         pixelFormat: kEAGLColorFormatRGB565
                                         depthFormat: GL_DEPTH24_STENCIL8_OES
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

    eaglView.touchCallback = ^(TouchEventType type, NSSet* touches, UIEvent* event) {
        if (type == TouchEventType::ENDED || type == TouchEventType::CANCELLED)
        {
            UITouch* touch = [touches anyObject];
            float x = [touch locationInView: [touch view]].x * scale;
//            float y = [touch locationInView: [touch view]].y * scale;

            if (x >= utils::WINDOW_WIDTH / 2)
                nextIndex = (++nextIndex) % tests.size();
            else
                nextIndex = int((--nextIndex + tests.size()) % tests.size());

            delete test;
            test = tests[nextIndex]();
        }
    };

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
