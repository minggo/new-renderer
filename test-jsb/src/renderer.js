(() => {

var _p;

_p = renderer.ForwardRenderer.prototype;
_p._ctor = function(device, builtin) {
    console.log("ForwardRenderer _ctor...");
    this.init(device, builtin.programTemplates, canvas.width, canvas.height);
};

_p = renderer.InputAssembler.prototype;
_p._ctor = function(vb, ib, pt = gfx.PT_TRIANGLES) {
    console.log("InputAssembler _ctor...");
    this.init(vb, ib, pt);
};

cc.defineGetterSetter(_p, "_vertexBuffer", _p.getVertexBuffer, _p.setVertexBuffer);
cc.defineGetterSetter(_p, "_indexBuffer", _p.getIndexBuffer, _p.setIndexBuffer);
cc.defineGetterSetter(_p, "_primitiveType", _p.getPrimitiveType, _p.setPrimitiveType);
cc.defineGetterSetter(_p, "_start", _p.getStart, _p.setStart);
cc.defineGetterSetter(_p, "_count", _p.getCount, _p.setCount);

})();