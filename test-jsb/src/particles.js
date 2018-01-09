(() => {
  let gfx = window.gfx;
  let device = window.device;
  let canvas = window.canvas;
  let { vec3, mat4, randomRange } = window.vmath;

  // init resources
  let program = new gfx.Program(device, {
    vert: `
    #ifdef GL_ES
      precision highp float;
    #endif
      uniform mat4 model, view, projection;

      attribute vec2 a_quad;
      attribute vec3 a_position;
      attribute vec4 a_color;

      varying vec4 color;
      varying vec2 uv;

      void main() {
        // billboard
        vec4 pos = view * model * vec4(a_position, 1);
        pos.xy += a_quad.xy;
        pos = projection * pos;

        uv = vec2(a_quad * -0.5 + 0.5);

        gl_Position = pos;
        gl_PointSize = 2.0;
        color = a_color;
      }
    `,
    frag: `
    #ifdef GL_ES
      precision highp float;
    #endif
      uniform sampler2D u_texture;

      varying vec4 color;
      varying vec2 uv;

      void main () {
        gl_FragColor = color * texture2D( u_texture, uv );
      }
    `,
  });
  program.link();

  function fillRectWithColor(buf, totalWidth, totalHeight, x, y, width, height, r, g, b)
  {
      console.assert(x + width <= totalWidth);
      console.assert(y + height <=  totalHeight);

      var y0 = totalHeight - (y + height);
      var y1 = totalHeight - y;

      for (var offsetY = y0; offsetY < y1; ++offsetY)
      {
          for (var offsetX = x; offsetX < (x + width); ++offsetX)
          {
              var index = (totalWidth * offsetY + offsetX) * 3;
              buf[index] = r;
              buf[index + 1] = g;
              buf[index + 2] = b;
          }
      }
  }

  const BUFFER_SIZE = 128 * 128 * 3;
  var data = new Uint8Array(BUFFER_SIZE);

  const lineWidth = 128;
  const lineHeight = 128;
  fillRectWithColor(data, lineWidth, lineHeight, 0, 0, 128, 128, 0xD0, 0xD0, 0xD0);
  fillRectWithColor(data, lineWidth, lineHeight, 0, 0, 64, 64, 0x50, 0x50, 0x50);
  fillRectWithColor(data, lineWidth, lineHeight, 32, 32, 32, 32, 0xFF, 0x00, 0x00);
  fillRectWithColor(data, lineWidth, lineHeight, 64, 64, 64, 64, 0x00, 0xFF, 0x00);
  fillRectWithColor(data, lineWidth, lineHeight, 96, 96, 32, 32, 0x00, 0x00, 0xFF);

  // create texture
  // let img = document.createElement('canvas');
  // let imgC = img.getContext('2d');
  // img.width = img.height = 128;
  // imgC.fillStyle = '#ddd';
  // imgC.fillRect(0, 0, 128, 128);
  // imgC.fillStyle = '#555';
  // imgC.fillRect(0, 0, 64, 64);
  // imgC.fillStyle = '#FF0000';
  // imgC.fillRect(32, 32, 32, 32);
  // imgC.fillStyle = '#00FF00';
  // imgC.fillRect(64, 64, 64, 64);
  // imgC.fillStyle = '#0000FF';
  // imgC.fillRect(96, 96, 32, 32);

  let texture = new gfx.Texture2D(device, {
    images: [data],//[img],
    width: 128,
    height: 128,
    wrapS: gfx.WRAP_REPEAT,
    wrapT: gfx.WRAP_REPEAT,
    format: gfx.TEXTURE_FMT_RGB8,
    mipmap: true,
  });

  // variables
  let quadVerts = [
    [-1, -1],
    [1, -1],
    [1, 1],
    [-1, 1]
  ];
  let maxCount = 1024;
  let vertStride = 9;
  let t = 0;
  let model = mat4.create();
  let view = mat4.create();
  let projection = mat4.create();
  let eye = vec3.create();
  let center = vec3.create();
  let up = vec3.create();

  // vb
  let vbufferArray = new Float32Array(maxCount * vertStride * 4);
  let vertexFmt = new gfx.VertexFormat([
    { name: 'a_quad', type: gfx.ATTR_TYPE_FLOAT32, num: 2 },
    { name: gfx.ATTR_POSITION, type: gfx.ATTR_TYPE_FLOAT32, num: 3 },
    { name: gfx.ATTR_COLOR, type: gfx.ATTR_TYPE_FLOAT32, num: 4 },
  ]);
  let vertexBuffer = new gfx.VertexBuffer(
    device,
    vertexFmt,
    gfx.USAGE_DYNAMIC,
    vbufferArray,
    maxCount * 4
  );

  // ib
  let ibufferArray = new Uint16Array(maxCount * 6);
  let dst = 0;
  for (let i = 0; i < maxCount; ++i) {
    let baseIndex = i * 4;
    ibufferArray[dst++] = baseIndex;
    ibufferArray[dst++] = baseIndex + 1;
    ibufferArray[dst++] = baseIndex + 2;
    ibufferArray[dst++] = baseIndex;
    ibufferArray[dst++] = baseIndex + 2;
    ibufferArray[dst++] = baseIndex + 3;
  }
  let indexBuffer = new gfx.IndexBuffer(
    device,
    gfx.INDEX_FMT_UINT16,
    gfx.USAGE_STATIC,
    ibufferArray,
    maxCount * 6
  );

  let particles = new Array(100);
  let particleCount = 100;
  for (let i = 0; i < particleCount; ++i) {
    particles[i] = {
      position: vec3.create(),
      velocity: vec3.random(vec3.create(), randomRange(0.1, 10)),
      age: 0,
      life: randomRange(1,10),
    };
  }

  // tick
  return function tick(dt) {
    t += dt;

    // update particles
    for (let i = 0; i < particleCount; ++i) {
      let p = particles[i];
      vec3.scaleAndAdd(p.position, p.position, p.velocity, dt);
      p.age += dt;

      if (p.age >= p.life) {
        p.age = 0;
        vec3.set(p.position, 0, 0, 0);
      }
    }

    // update vertex-buffer
    for (let i = 0; i < particleCount; ++i) {
      let p = particles[i];
      for (let v = 0; v < 4; ++v) {
        let offset = vertStride * (4 * i + v);

        // quad
        vbufferArray[offset + 0] = quadVerts[v][0];
        vbufferArray[offset + 1] = quadVerts[v][1];

        // pos
        vbufferArray[offset + 2] = p.position.x;
        vbufferArray[offset + 3] = p.position.y;
        vbufferArray[offset + 4] = p.position.z;

        // color
        vbufferArray[offset + 5] = 1;
        vbufferArray[offset + 6] = 1;
        vbufferArray[offset + 7] = 1;
        vbufferArray[offset + 8] = 1.0 - p.age / p.life;
      }
    }
    vertexBuffer.update(0, vbufferArray);

    //
    mat4.lookAt(view,
      vec3.set(eye, 30, 20, 30),
      vec3.set(center, 0, 2.5, 0),
      vec3.set(up, 0, 1, 0)
    );

    mat4.perspective(projection,
      Math.PI / 4,
      canvas.width / canvas.height,
      0.1,
      100
    );

    device.setViewport(0, 0, canvas.width, canvas.height);
    device.clear({
      color: [0.1, 0.1, 0.1, 1],
      depth: 1
    });

    device.enableBlend();
    device.setBlendFuncSep(gfx.BLEND_SRC_ALPHA, gfx.BLEND_ONE_MINUS_SRC_ALPHA, gfx.BLEND_ONE, gfx.BLEND_ONE);
    device.setBlendEqSep(gfx.BLEND_FUNC_ADD, gfx.BLEND_FUNC_ADD);

    device.setVertexBuffer(0, vertexBuffer);
    device.setIndexBuffer(indexBuffer);

    device.setUniform('model', mat4.array(new Float32Array(16), model));
    device.setUniform('view', mat4.array(new Float32Array(16), view));
    device.setUniform('projection', mat4.array(new Float32Array(16), projection));
    device.setTexture('u_texture', texture, 0);
    device.setProgram(program);

    device.draw(0, particleCount * 6);
  };
})();