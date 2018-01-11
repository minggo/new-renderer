(() => {

var testcases = [
    "basic.js",
    "bunny.js",
    "blending.js",
    "multiple-textures.js",
    "particles.js",
    "stencil.js",
    "post-process.js",
    "depth-texture.js",
    "sub-image.js",
    "texture-2d.js",
    "gui-projection.js"
];

var index = 0;
var testcase_tick = null;

function runTest() {
    testcase_tick = require("src/" + testcases[index]);
}

function runLeftTest() {
    --index;
    if (index < 0) {
        index = testcases.length - 1;
    }
    runTest();
}

function runRightTest() {
    ++index;
    if (index >= testcases.length) {
        index = 0;
    }
    runTest();
}

var TOUCH_BEGAN = 0;
var TOUCH_MOVED = 1;
var TOUCH_ENDED = 2;
var TOUCH_CANCELLED = 3;

window.onTouchEvent = (type, x, y) => {
    if (type == TOUCH_ENDED || type == TOUCH_CANCELLED) {
        console.log("onTouchUp: " + type + ", {" + x + "," + y + "}");
        if (x < canvas.width / 2) {
            runLeftTest();
        } else {
            runRightTest();
        }
    }
};

var KEY_CODE_RIGHT = 262;
var KEY_CODE_LEFT = 263;

window.onKeyUp = (code) => {
    console.log("onKeyUp: " + code);
    if (code == KEY_CODE_RIGHT) {
        runRightTest();
    } else if (code == KEY_CODE_LEFT) {
        runLeftTest();
    }
};

runTest();

return function tick(dt) {
    testcase_tick(dt);
}

})();
