(() => {
  'use strict';
  const device = window.device;
  const canvas = window.canvas;
  const engine = window.engine;
  const resl = window.resl;
  const walker = window.walker;

  const { gfx, RenderData } = engine;
  const { Scene, Camera, SpriteMaterial, Texture2D } = engine;
  const { vec3, quat, randomRange } = engine.math;
  const builtins = window.builtins;
  const Node = window.sgraph.Node;

  // Case related

  let frames = [
    new SpriteFrame({x: 2, y: 2, width: 26, height: 37}),
    new SpriteFrame({x: 2, y: 47, width: 26, height: 37}),
    new SpriteFrame({x: 2, y: 86, width: 26, height: 37}),
    new SpriteFrame({x: 2, y: 125, width: 26, height: 37}),
    new SpriteFrame({x: 2, y: 164, width: 26, height: 37}),
  ];

  // Sliced sprite frames
  for (let i = 0; i < frames.length; i++) {
    let frame = frames[i];
    frame.insetTop = 10;
    frame.insetBottom = 10;
    frame.insetLeft = 5;
    frame.insetRight = 5;
  }

  // create material
  let material = new SpriteMaterial();

  // scene
  let scene = new Scene();
  let nodes = [];

  let number = {};
  // // Add number notification
  // let number = document.createElement('div');
  // number.style.position = 'absolute';
  // number.style.left = '0px';
  // number.style.width = '100%';
  // number.style.top = '50%';
  // number.style.textAlign = 'center';
  // number.style.color = 'rgb(0, 0, 0)';
  // number.style.font = 'bold 50px Helvetica, Arial';
  // document.body.appendChild(number);

  // Add events
  let canvasElt = canvas;
  let isAdding = false;
  function startSpawn () {
    isAdding = true;
  }
  function endSpawn () {
    isAdding = false;
  }
  // canvasElt.addEventListener('mousedown', startSpawn);
  // canvasElt.addEventListener('touchstart', startSpawn);
  // canvasElt.addEventListener('mouseup', endSpawn);
  // canvasElt.addEventListener('mouseleave', endSpawn);
  // canvasElt.addEventListener('touchend', endSpawn);
  // canvasElt.addEventListener('touchcancel', endSpawn);

  var TOUCH_BEGAN = 0;
  var TOUCH_MOVED = 1;
  var TOUCH_ENDED = 2;
  var TOUCH_CANCELLED = 3;

  window.onTouchEvent = (type, x, y) => {
      if (type == TOUCH_BEGAN) {
          startSpawn();
      } else if (type == TOUCH_ENDED || type == TOUCH_CANCELLED) {
          endSpawn();
      }
  };

  var KEY_CODE_RIGHT = 262;
  var KEY_CODE_LEFT = 263;

  window.onKeyUp = (code) => {
    console.log("onKeyUp: " + code);
    if (code == KEY_CODE_RIGHT) {
      endSpawn();
    }
  };

  window.onKeyDown = (code) => {
    console.log("onKeyDown: " + code);
    if (code == KEY_CODE_RIGHT) {
      startSpawn();
    }
  };

  // Node and models
  function spawnNode () {
    let node = new Node('node_' + nodes.length);
    node.width = 54;
    node.height = 70;
    node.speedX = Math.random() * 10;
    node.speedY = (Math.random() * 10) - 5;
    node.anchorPoint = {x: 0.5, y: 0.5};

    vec3.set(node.lpos,
      randomRange(0, canvasElt.width),
      randomRange(0, canvasElt.height),
      0
    );
    quat.fromEuler(node.lrot, 0, 0, randomRange(0, 360));
    vec3.set(node.lscale, 0.5, 0.5, 1);

    let frameId = Math.floor(Math.random() * 5);
    node.frame = frames[frameId];
    let renderData = RenderData.alloc();
    renderData.dataLength = 4;
    renderData.vertexCount = 4;
    renderData.indiceCount = 6;
    renderData.effect = material._effect;
    node.renderData = renderData;
    nodes.push(node);
  }

  // Settings
  let gravity = 0.5;
  let amount = 100;
  let maxX = canvasElt.width;
  let minX = 0;
  let maxY = canvasElt.height;
  let minY = 0;

  // Update
  var updateBunnies = function () {
    var bunny, i;
    if (isAdding) {
        if (nodes.length < 100000) {
            for (i = 0; i < amount; i++) {
              spawnNode();
            }
            number.innerText = nodes.length;
            console.log("==> number: " + number.innerText);
            __setBunnyCount(number.innerText);
        }
    }

    for (i = 0; i < nodes.length; i++) 
    {
        bunny = nodes[i];
        
        var x = (bunny.lpos.x += bunny.speedX);
        var y = (bunny.lpos.y -= bunny.speedY);
        bunny.speedY += gravity;
        
        if (x > maxX)
        {
            bunny.speedX *= -1;
            bunny.lpos.x = maxX;
        }
        else if (x < minX)
        {
            bunny.speedX *= -1;
            bunny.lpos.x = minX;
        }
        
        if (y < minY)
        {
            bunny.speedY *= -0.85;
            bunny.lpos.y = minY;
            if (Math.random() > 0.5)
            {
                bunny.speedY -= Math.random() * 6;
            }
        } 
        else if (y > maxY)
        {
            bunny.speedY = 0;
            bunny.lpos.y = maxY;
        }

        bunny.renderData.vertDirty = true;
    }
  }

  // resl({
    // manifest: {
    //   image: {
    //     type: 'image',
    //     src: './assets/bunnys.png'
    //   },
    // },
    // onDone (assets) {
      let image = getImageInfo("assets/bunnys.png"); //assets.image;
      let texture = new Texture2D(device, {
        width : image.width,
        height: image.height,
        wrapS: gfx.WRAP_CLAMP,
        wrapT: gfx.WRAP_CLAMP,
        mipmap: false,
        flipY: false,
        images : [image.data],
        format: gfx.TEXTURE_FMT_RGBA8
      });
      material.texture = texture;

      for (let i = 0; i < 20; ++i) {
        spawnNode();
      }
    // }
  // });

  walker.init(device, builtins);

  // add camera
  let camera = new Camera({
    x: 0, y: 0, w: canvas.width, h: canvas.height
  });
  camera.setStages([
    'transparent'
  ]);
  scene.addCamera(camera);

  let time = 0;

  return function tick(dt) {
    time += dt;
    updateBunnies();

    walker.renderScene(scene, nodes);
  };
})();
