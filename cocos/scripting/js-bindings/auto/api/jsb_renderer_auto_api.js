/**
 * @module renderer
 */
var renderer = renderer || {};

/**
 * @class ProgramLib
 */
renderer.ProgramLib = {

/**
 * @method getProgram
 * @param {String} arg0
 * @param {map_object} arg1
 * @return {cc.gfx::Program}
 */
getProgram : function (
str, 
map 
)
{
    return cc.gfx::Program;
},

/**
 * @method define
 * @param {String} arg0
 * @param {String} arg1
 * @param {String} arg2
 * @param {Array} arg3
 */
define : function (
str, 
str, 
str, 
array 
)
{
},

/**
 * @method getKey
 * @param {String} arg0
 * @param {map_object} arg1
 * @return {unsigned int}
 */
getKey : function (
str, 
map 
)
{
    return 0;
},

/**
 * @method ProgramLib
 * @constructor
 * @param {Array} arg0
 */
ProgramLib : function (
array 
)
{
},

};

/**
 * @class Model
 */
renderer.Model = {

/**
 * @method getInputAssemblerCount
 * @return {unsigned int}
 */
getInputAssemblerCount : function (
)
{
    return 0;
},

/**
 * @method getDrawItemCount
 * @return {unsigned int}
 */
getDrawItemCount : function (
)
{
    return 0;
},

/**
 * @method setViewId
 * @param {int} arg0
 */
setViewId : function (
int 
)
{
},

/**
 * @method isDynamicIA
 * @return {bool}
 */
isDynamicIA : function (
)
{
    return false;
},

/**
 * @method addEffect
 * @param {cc.gfx::Effect} arg0
 */
addEffect : function (
effect 
)
{
},

/**
 * @method setWorldMatix
 * @param {mat4_object} arg0
 */
setWorldMatix : function (
mat4 
)
{
},

/**
 * @method clearEffects
 */
clearEffects : function (
)
{
},

/**
 * @method setDynamicIA
 * @param {bool} arg0
 */
setDynamicIA : function (
bool 
)
{
},

/**
 * @method getViewId
 * @return {int}
 */
getViewId : function (
)
{
    return 0;
},

/**
 * @method clearInputAssemblers
 */
clearInputAssemblers : function (
)
{
},

/**
 * @method addInputAssembler
 * @param {cc.gfx::InputAssembler} arg0
 */
addInputAssembler : function (
inputassembler 
)
{
},

/**
 * @method Model
 * @constructor
 */
Model : function (
)
{
},

};

/**
 * @class BaseRenderer
 */
renderer.Base = {

/**
 * @method init
* @param {cc.gfx::DeviceGraphics|cc.gfx::DeviceGraphics} devicegraphics
* @param {Array|Array} array
* @param {cc.gfx::Texture2D} texture2d
* @return {bool|bool}
*/
init : function(
devicegraphics,
array,
texture2d 
)
{
    return false;
},

/**
 * @method BaseRenderer
 * @constructor
 */
BaseRenderer : function (
)
{
},

};

/**
 * @class ForwardRenderer
 */
renderer.ForwardRenderer = {

/**
 * @method init
 * @param {cc.gfx::DeviceGraphics} arg0
 * @param {Array} arg1
 * @param {int} arg2
 * @param {int} arg3
 * @return {bool}
 */
init : function (
devicegraphics, 
array, 
int, 
int 
)
{
    return false;
},

/**
 * @method render
 * @param {cc.gfx::Scene} arg0
 */
render : function (
scene 
)
{
},

/**
 * @method ForwardRenderer
 * @constructor
 */
ForwardRenderer : function (
)
{
},

};

/**
 * @class View
 */
renderer.View = {

/**
 * @method View
 * @constructor
 */
View : function (
)
{
},

};

/**
 * @class Camera
 */
renderer.Camera = {

/**
 * @method getDepth
 * @return {float}
 */
getDepth : function (
)
{
    return 0;
},

/**
 * @method setFov
 * @param {float} arg0
 */
setFov : function (
float 
)
{
},

/**
 * @method getFrameBuffer
 * @return {cc.gfx::FrameBuffer}
 */
getFrameBuffer : function (
)
{
    return cc.gfx::FrameBuffer;
},

/**
 * @method setStencil
 * @param {int} arg0
 */
setStencil : function (
int 
)
{
},

/**
 * @method getOrthoHeight
 * @return {float}
 */
getOrthoHeight : function (
)
{
    return 0;
},

/**
 * @method getStencil
 * @return {int}
 */
getStencil : function (
)
{
    return 0;
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
 * @method setFar
 * @param {float} arg0
 */
setFar : function (
float 
)
{
},

/**
 * @method setRect
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @param {float} arg3
 */
setRect : function (
float, 
float, 
float, 
float 
)
{
},

/**
 * @method setClearFlags
 * @param {unsigned char} arg0
 */
setClearFlags : function (
char 
)
{
},

/**
 * @method getFar
 * @return {float}
 */
getFar : function (
)
{
    return 0;
},

/**
 * @method getType
 * @return {cc.gfx::ProjectionType}
 */
getType : function (
)
{
    return 0;
},

/**
 * @method setNear
 * @param {float} arg0
 */
setNear : function (
float 
)
{
},

/**
 * @method setStages
 * @param {Array} arg0
 */
setStages : function (
array 
)
{
},

/**
 * @method setOrthoHeight
 * @param {float} arg0
 */
setOrthoHeight : function (
float 
)
{
},

/**
 * @method setDepth
 * @param {float} arg0
 */
setDepth : function (
float 
)
{
},

/**
 * @method getStages
 * @return {Array}
 */
getStages : function (
)
{
    return new Array();
},

/**
 * @method getFov
 * @return {float}
 */
getFov : function (
)
{
    return 0;
},

/**
 * @method setColor
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @param {float} arg3
 */
setColor : function (
float, 
float, 
float, 
float 
)
{
},

/**
 * @method setWorldMatrix
 * @param {mat4_object} arg0
 */
setWorldMatrix : function (
mat4 
)
{
},

/**
 * @method getNear
 * @return {float}
 */
getNear : function (
)
{
    return 0;
},

/**
 * @method getClearFlags
 * @return {unsigned char}
 */
getClearFlags : function (
)
{
    return 0;
},

/**
 * @method Camera
 * @constructor
 */
Camera : function (
)
{
},

};

/**
 * @class Technique
 */
renderer.Technique = {

/**
 * @method getPasses
 * @return {Array}
 */
getPasses : function (
)
{
    return new Array();
},

/**
 * @method getStageIDs
 * @return {unsigned int}
 */
getStageIDs : function (
)
{
    return 0;
},

/**
 * @method setStages
 * @param {Array} arg0
 */
setStages : function (
array 
)
{
},

/**
 * @method getParameters
 * @return {Array}
 */
getParameters : function (
)
{
    return new Array();
},

/**
 * @method Technique
 * @constructor
 * @param {Array} arg0
 * @param {Array} arg1
 * @param {Array} arg2
 * @param {int} arg3
 */
Technique : function (
array, 
array, 
array, 
int 
)
{
},

};

/**
 * @class Effect
 */
renderer.Effect = {

/**
 * @method getDefineValue
 * @param {String} arg0
 * @return {cc.Value}
 */
getDefineValue : function (
str 
)
{
    return cc.Value;
},

/**
 * @method getProperty
 * @param {String} arg0
 * @return {cc.gfx::Technique::Parameter}
 */
getProperty : function (
str 
)
{
    return cc.gfx::Technique::Parameter;
},

/**
 * @method clear
 */
clear : function (
)
{
},

/**
 * @method setDefineValue
 * @param {String} arg0
 * @param {cc.Value} arg1
 */
setDefineValue : function (
str, 
value 
)
{
},

/**
 * @method setProperty
 * @param {String} arg0
 * @param {cc.gfx::Technique::Parameter} arg1
 */
setProperty : function (
str, 
parameter 
)
{
},

/**
 * @method getTechnique
 * @param {String} arg0
 * @return {cc.gfx::Technique}
 */
getTechnique : function (
str 
)
{
    return cc.gfx::Technique;
},

/**
 * @method Effect
 * @constructor
 * @param {Array} arg0
 * @param {map_object} arg1
 * @param {Array} arg2
 */
Effect : function (
array, 
map, 
map 
)
{
},

};

/**
 * @class InputAssembler
 */
renderer.InputAssembler = {

/**
 * @method setVertexBuffer
 * @param {cc.gfx::VertexBuffer} arg0
 */
setVertexBuffer : function (
vertexbuffer 
)
{
},

/**
 * @method getStart
 * @return {int}
 */
getStart : function (
)
{
    return 0;
},

/**
 * @method setStart
 * @param {int} arg0
 */
setStart : function (
int 
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
 * @method getPrimitiveCount
 * @return {unsigned int}
 */
getPrimitiveCount : function (
)
{
    return 0;
},

/**
 * @method setCount
 * @param {int} arg0
 */
setCount : function (
int 
)
{
},

/**
 * @method init
 * @param {cc.gfx::VertexBuffer} arg0
 * @param {cc.gfx::IndexBuffer} arg1
 * @param {cc.gfx::PrimitiveType} arg2
 * @return {bool}
 */
init : function (
vertexbuffer, 
indexbuffer, 
primitivetype 
)
{
    return false;
},

/**
 * @method getVertexBuffer
 * @return {cc.gfx::VertexBuffer}
 */
getVertexBuffer : function (
)
{
    return cc.gfx::VertexBuffer;
},

/**
 * @method getIndexBuffer
 * @return {cc.gfx::IndexBuffer}
 */
getIndexBuffer : function (
)
{
    return cc.gfx::IndexBuffer;
},

/**
 * @method getCount
 * @return {int}
 */
getCount : function (
)
{
    return 0;
},

/**
 * @method getPrimitiveType
 * @return {cc.gfx::PrimitiveType}
 */
getPrimitiveType : function (
)
{
    return 0;
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
 * @method InputAssembler
 * @constructor
 */
InputAssembler : function (
)
{
},

};

/**
 * @class Light
 */
renderer.Light = {

/**
 * @method getShadowScale
 * @return {float}
 */
getShadowScale : function (
)
{
    return 0;
},

/**
 * @method getRange
 * @return {float}
 */
getRange : function (
)
{
    return 0;
},

/**
 * @method setShadowResolution
 * @param {unsigned int} arg0
 */
setShadowResolution : function (
int 
)
{
},

/**
 * @method getFrustumEdgeFalloff
 * @return {unsigned int}
 */
getFrustumEdgeFalloff : function (
)
{
    return 0;
},

/**
 * @method setSpotExp
 * @param {float} arg0
 */
setSpotExp : function (
float 
)
{
},

/**
 * @method setShadowType
 * @param {cc.gfx::Light::ShadowType} arg0
 */
setShadowType : function (
shadowtype 
)
{
},

/**
 * @method setType
 * @param {cc.gfx::Light::LightType} arg0
 */
setType : function (
lighttype 
)
{
},

/**
 * @method getViewProjMatrix
 * @return {mat4_object}
 */
getViewProjMatrix : function (
)
{
    return cc.Mat4;
},

/**
 * @method getShadowBias
 * @return {float}
 */
getShadowBias : function (
)
{
    return 0;
},

/**
 * @method getShadowDarkness
 * @return {unsigned int}
 */
getShadowDarkness : function (
)
{
    return 0;
},

/**
 * @method getSpotAngle
 * @return {float}
 */
getSpotAngle : function (
)
{
    return 0;
},

/**
 * @method getSpotExp
 * @return {float}
 */
getSpotExp : function (
)
{
    return 0;
},

/**
 * @method getViewPorjMatrix
 * @return {mat4_object}
 */
getViewPorjMatrix : function (
)
{
    return cc.Mat4;
},

/**
 * @method getType
 * @return {cc.gfx::Light::LightType}
 */
getType : function (
)
{
    return 0;
},

/**
 * @method getIntensity
 * @return {float}
 */
getIntensity : function (
)
{
    return 0;
},

/**
 * @method getShadowMaxDepth
 * @return {float}
 */
getShadowMaxDepth : function (
)
{
    return 0;
},

/**
 * @method getShadowMap
 * @return {cc.gfx::Texture2D}
 */
getShadowMap : function (
)
{
    return cc.gfx::Texture2D;
},

/**
 * @method getColor
 * @return {cc.Color3F}
 */
getColor : function (
)
{
    return cc.Color3F;
},

/**
 * @method setIntensity
 * @param {float} arg0
 */
setIntensity : function (
float 
)
{
},

/**
 * @method getShadowMinDepth
 * @return {float}
 */
getShadowMinDepth : function (
)
{
    return 0;
},

/**
 * @method setShadowMinDepth
 * @param {float} arg0
 */
setShadowMinDepth : function (
float 
)
{
},

/**
 * @method update
 * @param {cc.gfx::DeviceGraphics} arg0
 */
update : function (
devicegraphics 
)
{
},

/**
 * @method setShadowDarkness
 * @param {unsigned int} arg0
 */
setShadowDarkness : function (
int 
)
{
},

/**
 * @method setSpotAngle
 * @param {float} arg0
 */
setSpotAngle : function (
float 
)
{
},

/**
 * @method setRange
 * @param {float} arg0
 */
setRange : function (
float 
)
{
},

/**
 * @method setShadowScale
 * @param {float} arg0
 */
setShadowScale : function (
float 
)
{
},

/**
 * @method setColor
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 */
setColor : function (
float, 
float, 
float 
)
{
},

/**
 * @method setShadowMaxDepth
 * @param {float} arg0
 */
setShadowMaxDepth : function (
float 
)
{
},

/**
 * @method setFrustumEdgeFalloff
 * @param {unsigned int} arg0
 */
setFrustumEdgeFalloff : function (
int 
)
{
},

/**
 * @method getShadowType
 * @return {cc.gfx::Light::ShadowType}
 */
getShadowType : function (
)
{
    return 0;
},

/**
 * @method getShadowResolution
 * @return {unsigned int}
 */
getShadowResolution : function (
)
{
    return 0;
},

/**
 * @method setShadowBias
 * @param {float} arg0
 */
setShadowBias : function (
float 
)
{
},

/**
 * @method Light
 * @constructor
 */
Light : function (
)
{
},

};

/**
 * @class Pass
 */
renderer.Pass = {

/**
 * @method setStencilBack
 */
setStencilBack : function (
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
 * @method setBlend
 */
setBlend : function (
)
{
},

/**
 * @method setStencilFront
 */
setStencilFront : function (
)
{
},

/**
 * @method setDepth
 */
setDepth : function (
)
{
},

/**
 * @method Pass
 * @constructor
 * @param {String} arg0
 */
Pass : function (
str 
)
{
},

};

/**
 * @class Scene
 */
renderer.Scene = {

/**
 * @method reset
 */
reset : function (
)
{
},

/**
 * @method getCameraCount
 * @return {unsigned int}
 */
getCameraCount : function (
)
{
    return 0;
},

/**
 * @method addCamera
 * @param {cc.gfx::Camera} arg0
 */
addCamera : function (
camera 
)
{
},

/**
 * @method removeCamera
 * @param {cc.gfx::Camera} arg0
 */
removeCamera : function (
camera 
)
{
},

/**
 * @method getLightCount
 * @return {unsigned int}
 */
getLightCount : function (
)
{
    return 0;
},

/**
 * @method getModel
 * @param {unsigned int} arg0
 * @return {cc.gfx::Model}
 */
getModel : function (
int 
)
{
    return cc.gfx::Model;
},

/**
 * @method removeModel
 * @param {cc.gfx::Model} arg0
 */
removeModel : function (
model 
)
{
},

/**
 * @method getModelCount
 * @return {unsigned int}
 */
getModelCount : function (
)
{
    return 0;
},

/**
 * @method getCamera
 * @param {unsigned int} arg0
 * @return {cc.gfx::Camera}
 */
getCamera : function (
int 
)
{
    return cc.gfx::Camera;
},

/**
 * @method getLight
 * @param {unsigned int} arg0
 * @return {cc.gfx::Light}
 */
getLight : function (
int 
)
{
    return cc.gfx::Light;
},

/**
 * @method getCameras
 * @return {Array}
 */
getCameras : function (
)
{
    return new Array();
},

/**
 * @method getModels
 * @return {Array}
 */
getModels : function (
)
{
    return new Array();
},

/**
 * @method addView
 * @param {cc.gfx::View} arg0
 */
addView : function (
view 
)
{
},

/**
 * @method setDebugCamera
 * @param {cc.gfx::Camera} arg0
 */
setDebugCamera : function (
camera 
)
{
},

/**
 * @method addModel
 * @param {cc.gfx::Model} arg0
 */
addModel : function (
model 
)
{
},

/**
 * @method removeView
 * @param {cc.gfx::View} arg0
 */
removeView : function (
view 
)
{
},

/**
 * @method addLight
 * @param {cc.gfx::Light} arg0
 */
addLight : function (
light 
)
{
},

/**
 * @method removeLight
 * @param {cc.gfx::Light} arg0
 */
removeLight : function (
light 
)
{
},

/**
 * @method Scene
 * @constructor
 */
Scene : function (
)
{
},

};
