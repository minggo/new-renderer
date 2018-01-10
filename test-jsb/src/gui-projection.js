(() => {
  let gfx = window.gfx;
  let device = window.device;
  let canvas = window.canvas;
  // let resl = window.resl;
  let { vec2, mat23, mat4, toRadian } = window.vmath;

  let texture = null;
  // resl({
  //   manifest: {
  //     image: {
  //       type: 'image',
  //       src: './assets/uv_checker_02.jpg'
  //     },
  //   },
  //   onDone (assets) {
      let image = getImageInfo("assets/uv_checker_02.jpg"); //assets.image;
      texture = new gfx.Texture2D(device, {
        width : image.width,
        height : image.height,
        images : [image.data],
        format: gfx.TEXTURE_FMT_RGB8,
      });
  //   }
  // });

  // init resources
  let program = new gfx.Program(device, {
    vert: `
    #ifdef GL_ES
      precision highp float;
    #endif
      uniform mat4 projection;
      uniform mat4 transform;
      attribute vec2 a_position;
      attribute vec2 a_uv;
      varying vec2 v_uv;

      void main () {
        gl_Position = projection * transform * vec4(a_position, 0, 1);
        v_uv = a_uv;
      }
    `,
    frag: `
    #ifdef GL_ES
      precision highp float;
    #endif
      uniform sampler2D texture;
      uniform vec4 color;
      varying vec2 v_uv;

      void main () {
        gl_FragColor = color * texture2D(texture, v_uv);
      }
    `,
  });
  program.link();

  let vertexFmt = new gfx.VertexFormat([
    { name: gfx.ATTR_POSITION, type: gfx.ATTR_TYPE_FLOAT32, num: 2 },
    { name: gfx.ATTR_UV, type: gfx.ATTR_TYPE_FLOAT32, num: 2 },
  ]);
  let spriteWidth = 128;
  let spriteHeight = 128;
  let vertexBuffer = new gfx.VertexBuffer(
    device,
    vertexFmt,
    gfx.USAGE_STATIC,
    new Float32Array([
      0, 0,                       0, 0,
      0, spriteHeight,            0, 1,
      spriteWidth, spriteHeight,  1, 1,
      0, 0,                       0, 0,
      spriteWidth, spriteHeight,  1, 1,
      spriteWidth, 0,             1, 0
    ]),
    6
  );
  let projection = mat4.create();
  let affineTranslation = mat23.create();
  let affineRotation = mat23.create();
  let affineScale = mat23.create();

  /**
   * coordinates
   * ^ y
   * |
   * |
   * |
   * |
   * .-----------> x
   */

  // tick
  return function tick() {
    mat4.ortho(projection, 0, canvas.width, 0, canvas.height, -100, 100);

    mat23.fromTranslation(affineTranslation, vec2.new(10, (canvas.height - spriteHeight) / 2));

    mat23.fromTranslation(affineRotation, vec2.new(10 + spriteWidth * 2, (canvas.height - spriteHeight) / 2));
    mat23.rotate(affineRotation, affineRotation, toRadian(15));

    mat23.fromTranslation(affineScale, vec2.new(10 + spriteWidth * 4, (canvas.height - spriteHeight) / 2));
    mat23.scale(affineScale, affineScale, vec2.new(1.2, 0.5));

    device.setViewport(0, 0, canvas.width, canvas.height);
    device.clear({
      color: [0.1, 0.1, 0.1, 1],
      depth: 1
    });

    if (texture) {
      device.setTexture('texture', texture, 0);

      // translation
      device.setCullMode(gfx.CULL_NONE);
      device.setVertexBuffer(0, vertexBuffer);
      device.setUniform('color', new Float32Array([1, 0, 0, 1]));
      device.setUniform('projection', mat4.array(new Float32Array(16), projection));
      device.setUniform('transform', mat23.array4x4(new Float32Array(16), affineTranslation));
      device.setProgram(program);
      device.draw(0, vertexBuffer.count);

      // rotation
      device.setCullMode(gfx.CULL_NONE);
      device.setVertexBuffer(0, vertexBuffer);
      device.setUniform('color', new Float32Array([0, 1, 0, 1]));
      device.setUniform('projection', mat4.array(new Float32Array(16), projection));
      device.setUniform('transform', mat23.array4x4(new Float32Array(16), affineRotation));
      device.setProgram(program);
      device.draw(0, vertexBuffer.count);

      // scale
      device.setCullMode(gfx.CULL_NONE);
      device.setVertexBuffer(0, vertexBuffer);
      device.setUniform('color', new Float32Array([0, 0, 1, 1]));
      device.setUniform('projection', mat4.array(new Float32Array(16), projection));
      device.setUniform('transform', mat23.array4x4(new Float32Array(16), affineScale));
      device.setProgram(program);
      device.draw(0, vertexBuffer.count);
    }
  };
})();
