require("src/enums.js");
require("src/vertex-format.js");
require("src/vmath.js");

/**
 * Common getter setter configuration function
 * @function
 * @param {Object}   proto      A class prototype or an object to config
 * @param {String}   prop       Property name
 * @param {function} getter     Getter function for the property
 * @param {function} setter     Setter function for the property
 */
cc.defineGetterSetter = function (proto, prop, getter, setter){
    var desc = { enumerable: false, configurable: true };
    getter && (desc.get = getter);
    setter && (desc.set = setter);
    Object.defineProperty(proto, prop, desc);
};


window.device = gfx.Device.getInstance();
window.canvas = { width: 1334, height: 750 };

_p = gfx.Program.prototype;
_p._ctor = function(device, options) {
    this.init(device, options.vert, options.frag);
};

_p = gfx.VertexBuffer.prototype;
_p._ctor = function(device, format, usage, data, numVertices) {
    this.init(device, format, usage, data, numVertices);
};
cc.defineGetterSetter(_p, "count", _p.getCount);

_p = gfx.IndexBuffer.prototype;
_p._ctor = function(device, format, usage, data, numIndices) {
    this.init(device, format, usage, data, numIndices);
};
cc.defineGetterSetter(_p, "count", _p.getCount);

gfx.VertexFormat = VertexFormat;
Object.assign(gfx, enums);

_p = gfx.Texture2D.prototype;
_p._ctor = function(device, options) {
    this.init(device, options);
};
cc.defineGetterSetter(_p, "_width", _p.getWidth);
cc.defineGetterSetter(_p, "_height", _p.getHeight);

_p = gfx.FrameBuffer.prototype;
_p._ctor = function(device, width, height, options) {
    this.init(device, width, height, options);
};

var TextHAlignment = {
    LEFT : 0,
    CENTER : 1,
    RIGHT : 2
};

var TextVAlignment = {
    TOP : 0,
    CENTER : 1,
    BOTTOM : 2
};

var DeviceTextAlign = {
    CENTER        : 0x33, /** Horizontal center and vertical center. */
    TOP           : 0x13, /** Horizontal center and vertical top. */
    TOP_RIGHT     : 0x12, /** Horizontal right and vertical top. */
    RIGHT         : 0x32, /** Horizontal right and vertical center. */
    BOTTOM_RIGHT  : 0x22, /** Horizontal right and vertical bottom. */
    BOTTOM        : 0x23, /** Horizontal center and vertical bottom. */
    BOTTOM_LEFT   : 0x21, /** Horizontal left and vertical bottom. */
    LEFT          : 0x31, /** Horizontal left and vertical center. */
    TOP_LEFT      : 0x11 /** Horizontal left and vertical top. */
}

gfx.RB_FMT_D16 = 0x81A5; // GL_DEPTH_COMPONENT16 hack for JSB
