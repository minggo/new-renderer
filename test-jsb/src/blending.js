(() => {
  let gfx = window.gfx;
  let device = window.device;
  let canvas = window.canvas;
  // let resl = window.resl;
  let { quat, vec3, mat4 } = window.vmath;

  function _quad(device) {
    let program = new gfx.Program(device, {
      vert: `
      #ifdef GL_ES
        precision highp float;
      #endif
        attribute vec2 a_position;
        attribute vec2 a_uv;
        varying vec2 uv;
        uniform mat4 model, projection;

        void main() {
          uv = a_uv;
          gl_Position = projection * model * vec4(a_position, 0, 1);
        }
      `,
      frag: `
      #ifdef GL_ES
        precision highp float;
      #endif
        varying vec2 uv;
        uniform sampler2D texture;

        void main() {
          gl_FragColor = texture2D(texture, uv);
        }
      `,
    });
    program.link();

    let vertexFmt = new gfx.VertexFormat([
      { name: gfx.ATTR_POSITION, type: gfx.ATTR_TYPE_FLOAT32, num: 2 },
      { name: gfx.ATTR_UV, type: gfx.ATTR_TYPE_FLOAT32, num: 2 },
    ]);
    let vb = new gfx.VertexBuffer(
      device,
      vertexFmt,
      gfx.USAGE_STATIC,
      new Float32Array([
        -0.5, -0.5, 0, 0,
        -0.5,  0.5, 0, 1,
         0.5,  0.5, 1, 1,
         0.5, -0.5, 1, 0,
      ]),
      4
    );
    let ib = new gfx.IndexBuffer(
      device,
      gfx.INDEX_FMT_UINT8,
      gfx.USAGE_STATIC,
      new Uint8Array([ 0, 3, 1, 1, 3, 2]),
      6
    );

    return {
      vb,
      ib,
      program,
    };
  }

  function _bigTriangle(device) {
    let program = new gfx.Program(device, {
      vert: `
      #ifdef GL_ES
        precision highp float;
      #endif
        attribute vec2 a_position;
        varying vec2 uv;

        void main() {
          uv = (a_position + 1.0) * 0.5;
          gl_Position = vec4(a_position, 0, 1);
        }
      `,
      frag: `
      #ifdef GL_ES
        precision highp float;
      #endif
        varying vec2 uv;
        uniform sampler2D texture;
        uniform float time;

        void main() {
          vec2 offset = vec2(time * -0.01);
          gl_FragColor = texture2D(texture, 20.0 * (uv + offset));
        }
      `,
    });
    program.link();

    let vertexFmt = new gfx.VertexFormat([
      { name: gfx.ATTR_POSITION, type: gfx.ATTR_TYPE_FLOAT32, num: 2 },
    ]);
    let vb = new gfx.VertexBuffer(
      device,
      vertexFmt,
      gfx.USAGE_STATIC,
      new Float32Array([-1, 4, -1, -1, 4, -1]),
      3
    );

    return {
      vb,
      program,
    };
  }

  // create background texture
  // let img = document.createElement('canvas');
  // let imgC = img.getContext('2d');
  // img.width = img.height = 128;
  // imgC.fillStyle = '#ddd';
  // imgC.fillRect(0, 0, 128, 128);
  // imgC.fillStyle = '#555';
  // imgC.fillRect(0, 0, 64, 64);
  // imgC.fillStyle = '#999';
  // imgC.fillRect(32, 32, 32, 32);
  // imgC.fillStyle = '#555';
  // imgC.fillRect(64, 64, 64, 64);
  // imgC.fillStyle = '#777';
  // imgC.fillRect(96, 96, 32, 32);

  let bgImgInfo = getImageInfo("assets/background.png");
  let textureBG = new gfx.Texture2D(device, {
    images: [bgImgInfo.data],
    width: bgImgInfo.width,
    height: bgImgInfo.height,
    wrapS: gfx.WRAP_REPEAT,
    wrapT: gfx.WRAP_REPEAT,
    format: gfx.TEXTURE_FMT_RGB8,
    mipmap: true,
  });

  let model = mat4.create();
  let projection = mat4.create();
  let bg = _bigTriangle(device);
  let quad = _quad(device);

  let sprite0;

  // resl({
  //   manifest: {
  //     sprite0: {
  //       type: 'image',
  //       src: './assets/sprite0.png'
  //     },
  //   },
  //   onDone (assets) {

    var spriteImgInfo = getImageInfo("assets/sprite0.png");
      sprite0 = new gfx.Texture2D(device, {
        width : spriteImgInfo.width,//assets.sprite0.width,
        height : spriteImgInfo.height,//assets.sprite0.height,
        images : [spriteImgInfo.data],//[assets.sprite0],
        flipY: false,
        format: gfx.TEXTURE_FMT_RGBA8,
        // premultiplyAlpha: true,
      });
  //   }
  // });

  let t = 0;

  // tick
  return function tick(dt) {
    t += dt;

    // let hw = canvas.width * 0.5;
    // let hh = canvas.height * 0.5;
    // mat4.ortho(projection, -hw, hw, -hh, hh, -1, 1);
    mat4.ortho(projection, 0, canvas.width, canvas.height, 0, 0.0, 1000.0);
    // mat4.set(projection,
    //   2 / canvas.width, 0,                  0,    0,
    //   0,                -2 / canvas.height, 0,    0,
    //   0,                0,                  0,    0,
    //   -1,               1,                  0,    1
    // );

    device.setViewport(0, 0, canvas.width, canvas.height);
    device.clear({
      color: [0.1, 0.1, 0.1, 1],
      depth: 1
    });

    // shared uniforms
    device.setUniform('time', t);
    device.setUniform('projection', mat4.array(new Float32Array(16), projection));

    // background
    device.setTexture('texture', textureBG, 0);
    device.setVertexBuffer(0, bg.vb);
    device.setProgram(bg.program);
    device.draw(0, bg.vb.count);

    // sprites
    if (sprite0) {
      let size = Math.min(canvas.width, canvas.height) * 0.15;
      let hsize = size * 0.5;

      // no-blending
      let offsetX = 5 + hsize;
      let offsetY = 5 + hsize;
      device.enableBlend();
      device.setBlendFuncSep(gfx.BLEND_ONE, gfx.BLEND_ZERO, gfx.BLEND_ONE, gfx.BLEND_ONE);
      device.setBlendEqSep(gfx.BLEND_FUNC_ADD, gfx.BLEND_FUNC_ADD);

      device.setCullMode(gfx.CULL_NONE);
      mat4.fromRTS(model, quat.create(), vec3.new(offsetX, offsetY, 0), vec3.new(size, size, 0));
      device.setUniform('model', mat4.array(new Float32Array(16), model));
      device.setTexture('texture', sprite0, 0);
      device.setVertexBuffer(0, quad.vb);
      device.setIndexBuffer(quad.ib);
      device.setProgram(quad.program);
      device.draw(0, quad.ib.count);

      // normal
      offsetY = offsetY + 5 + size;
      device.enableBlend();
      device.setBlendFuncSep(gfx.BLEND_SRC_ALPHA, gfx.BLEND_ONE_MINUS_SRC_ALPHA, gfx.BLEND_ONE, gfx.BLEND_ONE);
      device.setBlendEqSep(gfx.BLEND_FUNC_ADD, gfx.BLEND_FUNC_ADD);

      device.setCullMode(gfx.CULL_NONE);
      mat4.fromRTS(model, quat.create(), vec3.new(offsetX, offsetY, 0), vec3.new(size, size, 0));
      device.setUniform('model', mat4.array(new Float32Array(16), model));
      device.setTexture('texture', sprite0, 0);
      device.setVertexBuffer(0, quad.vb);
      device.setIndexBuffer(quad.ib);
      device.setProgram(quad.program);
      device.draw(0, quad.ib.count);

      // additive
      offsetY = offsetY + 5 + size;
      device.enableBlend();
      device.setBlendFuncSep(gfx.BLEND_SRC_ALPHA, gfx.BLEND_ONE, gfx.BLEND_ONE, gfx.BLEND_ONE);
      device.setBlendEqSep(gfx.BLEND_FUNC_ADD, gfx.BLEND_FUNC_ADD);

      device.setCullMode(gfx.CULL_NONE);
      mat4.fromRTS(model, quat.create(), vec3.new(offsetX, offsetY, 0), vec3.new(size, size, 0));
      device.setUniform('model', mat4.array(new Float32Array(16), model));
      device.setTexture('texture', sprite0, 0);
      device.setVertexBuffer(0, quad.vb);
      device.setIndexBuffer(quad.ib);
      device.setProgram(quad.program);
      device.draw(0, quad.ib.count);

      // substract
      offsetY = offsetY + 5 + size;
      device.enableBlend();
      device.setBlendFuncSep(gfx.BLEND_ZERO, gfx.BLEND_ONE_MINUS_SRC_COLOR, gfx.BLEND_ONE, gfx.BLEND_ONE);
      device.setBlendEqSep(gfx.BLEND_FUNC_ADD, gfx.BLEND_FUNC_ADD);

      device.setCullMode(gfx.CULL_NONE);
      mat4.fromRTS(model, quat.create(), vec3.new(offsetX, offsetY, 0), vec3.new(size, size, 0));
      device.setUniform('model', mat4.array(new Float32Array(16), model));
      device.setTexture('texture', sprite0, 0);
      device.setVertexBuffer(0, quad.vb);
      device.setIndexBuffer(quad.ib);
      device.setProgram(quad.program);
      device.draw(0, quad.ib.count);

      // multiply
      offsetY = offsetY + 5 + size;
      device.enableBlend();
      device.setBlendFuncSep(gfx.BLEND_ZERO, gfx.BLEND_SRC_COLOR, gfx.BLEND_ONE, gfx.BLEND_ONE);
      device.setBlendEqSep(gfx.BLEND_FUNC_ADD, gfx.BLEND_FUNC_ADD);

      device.setCullMode(gfx.CULL_NONE);
      mat4.fromRTS(model, quat.create(), vec3.new(offsetX, offsetY, 0), vec3.new(size, size, 0));
      device.setUniform('model', mat4.array(new Float32Array(16), model));
      device.setTexture('texture', sprite0, 0);
      device.setVertexBuffer(0, quad.vb);
      device.setIndexBuffer(quad.ib);
      device.setProgram(quad.program);
      device.draw(0, quad.ib.count);
    }
  };
})();