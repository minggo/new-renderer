/**
 * @module gfx
 */
var gfx = gfx || {};

/**
 * @class GraphicsHandle
 */
gfx.GraphicsHandle = {

/**
 * @method getHandle
 * @return {unsigned int}
 */
getHandle : function (
)
{
    return 0;
},

/**
 * @method GraphicsHandle
 * @constructor
 */
GraphicsHandle : function (
)
{
},

};

/**
 * @class IndexBuffer
 */
gfx.IndexBuffer = {

/**
 * @method getCount
 * @return {unsigned int}
 */
getCount : function (
)
{
    return 0;
},

/**
 * @method IndexBuffer
 * @constructor
 */
IndexBuffer : function (
)
{
},

};

/**
 * @class VertexBuffer
 */
gfx.VertexBuffer = {

/**
 * @method getCount
 * @return {unsigned int}
 */
getCount : function (
)
{
    return 0;
},

/**
 * @method VertexBuffer
 * @constructor
 */
VertexBuffer : function (
)
{
},

};

/**
 * @class DeviceGraphics
 */
gfx.Device = {

/**
 * @method setTexture
 * @param {String} arg0
 * @param {cc.gfx::Texture} arg1
 * @param {int} arg2
 */
setTexture : function (
str, 
texture, 
int 
)
{
},

/**
 * @method setBlendFuncSeparate
 * @param {cc.gfx::BlendFactor} arg0
 * @param {cc.gfx::BlendFactor} arg1
 * @param {cc.gfx::BlendFactor} arg2
 * @param {cc.gfx::BlendFactor} arg3
 */
setBlendFuncSeparate : function (
blendfactor, 
blendfactor, 
blendfactor, 
blendfactor 
)
{
},

/**
 * @method enableBlend
 */
enableBlend : function (
)
{
},

/**
 * @method setPrimitiveType
 * @param {cc.gfx::PrimitiveType} arg0
 */
setPrimitiveType : function (
primitivetype 
)
{
},

/**
 * @method setBlendEquationSeparate
 * @param {cc.gfx::BlendOp} arg0
 * @param {cc.gfx::BlendOp} arg1
 */
setBlendEquationSeparate : function (
blendop, 
blendop 
)
{
},

/**
 * @method setIndexBuffer
 * @param {cc.gfx::IndexBuffer} arg0
 */
setIndexBuffer : function (
indexbuffer 
)
{
},

/**
 * @method setProgram
 * @param {cc.gfx::Program} arg0
 */
setProgram : function (
program 
)
{
},

/**
 * @method setFrameBuffer
 * @param {cc.gfx::FrameBuffer} arg0
 */
setFrameBuffer : function (
framebuffer 
)
{
},

/**
 * @method setStencilFunc
 * @param {cc.gfx::ComparisonFunc} arg0
 * @param {int} arg1
 * @param {unsigned int} arg2
 */
setStencilFunc : function (
comparisonfunc, 
int, 
int 
)
{
},

/**
 * @method setBlendColor
* @param {unsigned char|unsigned int} char
* @param {unsigned char} char
* @param {unsigned char} char
* @param {unsigned char} char
*/
setBlendColor : function(
char,
char,
char,
char 
)
{
},

/**
 * @method setScissor
 * @param {int} arg0
 * @param {int} arg1
 * @param {int} arg2
 * @param {int} arg3
 */
setScissor : function (
int, 
int, 
int, 
int 
)
{
},

/**
 * @method setVertexBuffer
 * @param {int} arg0
 * @param {cc.gfx::VertexBuffer} arg1
 * @param {int} arg2
 */
setVertexBuffer : function (
int, 
vertexbuffer, 
int 
)
{
},

/**
 * @method enableDepthWrite
 */
enableDepthWrite : function (
)
{
},

/**
 * @method setTextureArray
 * @param {String} arg0
 * @param {Array} arg1
 * @param {Array} arg2
 */
setTextureArray : function (
str, 
array, 
array 
)
{
},

/**
 * @method setStencilOpBack
 * @param {cc.gfx::StencilOp} arg0
 * @param {cc.gfx::StencilOp} arg1
 * @param {cc.gfx::StencilOp} arg2
 * @param {unsigned int} arg3
 */
setStencilOpBack : function (
stencilop, 
stencilop, 
stencilop, 
int 
)
{
},

/**
 * @method setViewport
 * @param {int} arg0
 * @param {int} arg1
 * @param {int} arg2
 * @param {int} arg3
 */
setViewport : function (
int, 
int, 
int, 
int 
)
{
},

/**
 * @method draw
 * @param {unsigned int} arg0
 * @param {int} arg1
 */
draw : function (
int, 
int 
)
{
},

/**
 * @method setDepthFunc
 * @param {cc.gfx::ComparisonFunc} arg0
 */
setDepthFunc : function (
comparisonfunc 
)
{
},

/**
 * @method enableDepthTest
 */
enableDepthTest : function (
)
{
},

/**
 * @method setBlendEquation
 * @param {cc.gfx::BlendOp} arg0
 */
setBlendEquation : function (
blendop 
)
{
},

/**
 * @method setStencilFuncFront
 * @param {cc.gfx::ComparisonFunc} arg0
 * @param {int} arg1
 * @param {unsigned int} arg2
 */
setStencilFuncFront : function (
comparisonfunc, 
int, 
int 
)
{
},

/**
 * @method setStencilOpFront
 * @param {cc.gfx::StencilOp} arg0
 * @param {cc.gfx::StencilOp} arg1
 * @param {cc.gfx::StencilOp} arg2
 * @param {unsigned int} arg3
 */
setStencilOpFront : function (
stencilop, 
stencilop, 
stencilop, 
int 
)
{
},

/**
 * @method setStencilFuncBack
 * @param {cc.gfx::ComparisonFunc} arg0
 * @param {int} arg1
 * @param {unsigned int} arg2
 */
setStencilFuncBack : function (
comparisonfunc, 
int, 
int 
)
{
},

/**
 * @method setBlendFunc
 * @param {cc.gfx::BlendFactor} arg0
 * @param {cc.gfx::BlendFactor} arg1
 */
setBlendFunc : function (
blendfactor, 
blendfactor 
)
{
},

/**
 * @method setCullMode
 * @param {cc.gfx::CullMode} arg0
 */
setCullMode : function (
cullmode 
)
{
},

/**
 * @method supportGLExtension
 * @param {String} arg0
 * @return {bool}
 */
supportGLExtension : function (
str 
)
{
    return false;
},

/**
 * @method setStencilOp
 * @param {cc.gfx::StencilOp} arg0
 * @param {cc.gfx::StencilOp} arg1
 * @param {cc.gfx::StencilOp} arg2
 * @param {unsigned int} arg3
 */
setStencilOp : function (
stencilop, 
stencilop, 
stencilop, 
int 
)
{
},

/**
 * @method enableStencilTest
 */
enableStencilTest : function (
)
{
},

/**
 * @method getInstance
 * @return {cc.gfx::DeviceGraphics}
 */
getInstance : function (
)
{
    return cc.gfx::DeviceGraphics;
},

};

/**
 * @class FrameBuffer
 */
gfx.FrameBuffer = {

/**
 * @method FrameBuffer
 * @constructor
 */
FrameBuffer : function (
)
{
},

};

/**
 * @class RenderTarget
 */
gfx.RenderTarget = {

};

/**
 * @class RenderBuffer
 */
gfx.RenderBuffer = {

/**
 * @method init
 * @param {cc.gfx::DeviceGraphics} arg0
 * @param {cc.gfx::RenderBuffer::Format} arg1
 * @param {unsigned short} arg2
 * @param {unsigned short} arg3
 * @return {bool}
 */
init : function (
devicegraphics, 
format, 
short, 
short 
)
{
    return false;
},

/**
 * @method create
 * @param {cc.gfx::DeviceGraphics} arg0
 * @param {cc.gfx::RenderBuffer::Format} arg1
 * @param {unsigned short} arg2
 * @param {unsigned short} arg3
 * @return {cc.gfx::RenderBuffer}
 */
create : function (
devicegraphics, 
format, 
short, 
short 
)
{
    return cc.gfx::RenderBuffer;
},

/**
 * @method RenderBuffer
 * @constructor
 */
RenderBuffer : function (
)
{
},

};

/**
 * @class Texture
 */
gfx.Texture = {

/**
 * @method getWidth
 * @return {unsigned short}
 */
getWidth : function (
)
{
    return 0;
},

/**
 * @method getHeight
 * @return {unsigned short}
 */
getHeight : function (
)
{
    return 0;
},

/**
 * @method getTarget
 * @return {unsigned int}
 */
getTarget : function (
)
{
    return 0;
},

};

/**
 * @class Texture2D
 */
gfx.Texture2D = {

/**
 * @method updateImage
 * @param {cc.gfx::Texture::ImageOption} arg0
 */
updateImage : function (
imageoption 
)
{
},

/**
 * @method init
 * @param {cc.gfx::DeviceGraphics} arg0
 * @param {cc.gfx::Texture::Options} arg1
 * @return {bool}
 */
init : function (
devicegraphics, 
options 
)
{
    return false;
},

/**
 * @method updateSubImage
 * @param {cc.gfx::Texture::SubImageOption} arg0
 */
updateSubImage : function (
subimageoption 
)
{
},

/**
 * @method update
 * @param {cc.gfx::Texture::Options} arg0
 */
update : function (
options 
)
{
},

/**
 * @method create
 * @param {cc.gfx::DeviceGraphics} arg0
 * @param {cc.gfx::Texture::Options} arg1
 * @return {cc.gfx::Texture2D}
 */
create : function (
devicegraphics, 
options 
)
{
    return cc.gfx::Texture2D;
},

/**
 * @method Texture2D
 * @constructor
 */
Texture2D : function (
)
{
},

};

/**
 * @class Program
 */
gfx.Program = {

/**
 * @method getID
 * @return {unsigned int}
 */
getID : function (
)
{
    return 0;
},

/**
 * @method init
 * @param {cc.gfx::DeviceGraphics} arg0
 * @param {char} arg1
 * @param {char} arg2
 * @return {bool}
 */
init : function (
devicegraphics, 
char, 
char 
)
{
    return false;
},

/**
 * @method link
 */
link : function (
)
{
},

/**
 * @method Program
 * @constructor
 */
Program : function (
)
{
},

};
