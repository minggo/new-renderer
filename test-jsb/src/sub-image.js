(() => {
  let gfx = window.gfx;
  let device = window.device;
  let canvas = window.canvas;
  let { mat4, randomRangeInt } = window.vmath;

  // init resources
  let program = new gfx.Program(device, {
    vert: `
    #ifdef GL_ES
      precision highp float;
    #endif
      uniform mat4 transform;
      attribute vec2 a_position;
      varying vec2 v_texcoord;
      void main () {
        gl_Position = transform * vec4(a_position, 0, 1);
        v_texcoord = a_position * 0.5 + 0.5;
      }
    `,
    frag: `
    #ifdef GL_ES
      precision highp float;
    #endif
      uniform sampler2D texture;
      uniform vec4 color;
      varying vec2 v_texcoord;
      void main () {
        gl_FragColor = texture2D(texture, v_texcoord);
      }
    `,
  });
  program.link();

  // create texture
  let texture = new gfx.Texture2D(device, {
    width: 128,
    height: 128,
    wrapS: gfx.WRAP_CLAMP,
    wrapT: gfx.WRAP_CLAMP,
    minFilter: gfx.FILTER_NEAREST,
    magFilter: gfx.FILTER_NEAREST,
    format: gfx.TEXTURE_FMT_RGB8,
    mipmap: false,
    flipY: false
  });

  let vertexFmt = new gfx.VertexFormat([
    { name: gfx.ATTR_POSITION, type: gfx.ATTR_TYPE_FLOAT32, num: 2 },
  ]);
  let vertexBuffer = new gfx.VertexBuffer(
    device,
    vertexFmt,
    gfx.USAGE_STATIC,
    new Float32Array([-1, -1, 1, -1, 1, 1, 1, 1, -1, 1, -1, -1]),
    6
  );
  let transform0 = mat4.create();

  let data = new Uint8Array(texture._width * texture._height * 3);
  let size = 0;

  // tick
  return function tick() {
    device.setViewport(0, 0, canvas.width, canvas.height);
    device.clear({
      color: [0.1, 0.1, 0.1, 1],
      depth: 1
    });

    for (let i = 0; i < size; ++i) {
      data[3 * i] = randomRangeInt(0,255);
      data[3 * i + 1] = randomRangeInt(0,255);
      data[3 * i + 2] = randomRangeInt(0,255);
    }
    let opts = {
      x: 0,
      y: 0,
      width: texture._width,
      height: texture._height,
      level: 0,
      image: data,
      flipY: false
    };
    texture.updateSubImage(opts);

    device.setVertexBuffer(0, vertexBuffer);
    device.setUniform('color', new Float32Array([1, 0, 0, 1]));
    device.setTexture('texture', texture, 0);
    device.setUniform('transform', mat4.array(new Float32Array(16), transform0));
    device.setProgram(program);
    device.draw(0, vertexBuffer.count);

    if (size < texture._width * texture._height ) {
      size += 1;
    }
  };
})();
