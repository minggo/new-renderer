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

gfx.VertexFormat = VertexFormat;
Object.assign(gfx, enums);