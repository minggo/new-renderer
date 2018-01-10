(() => {
  let resl = window.resl;
  let gfx = window.gfx;
  let device = window.device;
  let canvas = window.canvas;
  let { vec3, mat4 } = window.vmath;

  // init resources
  let program = new gfx.Program(device, {
    vert: `
    #ifdef GL_ES
      precision highp float;
    #endif
      attribute vec3 a_position;
      uniform mat4 model, view, projection;
      varying vec3 position;

      void main () {
        vec4 pos = projection * view * model * vec4(a_position, 1);
        position = a_position.xyz;
        gl_Position = pos;
      }
    `,
    frag: `
    #ifdef GL_ES
      precision highp float;
    #endif
      uniform vec4 color;
      varying vec3 position;

      void main () {
        gl_FragColor = color * vec4(position, 1);
      }
    `,
  });
  program.link();

  let vertexBuffer, indexBuffer;

  let vertexFmt = new gfx.VertexFormat([
    { name: gfx.ATTR_POSITION, type: gfx.ATTR_TYPE_FLOAT32, num: 3 },
  ]);

  let bunnyLoaded = false;

  // resl({
  //   manifest: {
  //     js: {
  //       type: 'text',
  //       src: './assets/bunny.js'
  //     },
  //   },

  //   onDone (assets) {
      let bunny = eval(getStringFromFile("assets/bunny.js"));
      let verts = new Array(bunny.positions.length * 3);
      let indices = new Array(bunny.cells.length * 3);

      for (let i = 0; i < bunny.positions.length; ++i) {
        let pos = bunny.positions[i];
        verts[3 * i] = pos[0];
        verts[3 * i + 1] = pos[1];
        verts[3 * i + 2] = pos[2];
      }

      for (let i = 0; i < bunny.cells.length; ++i) {
        let cell = bunny.cells[i];
        indices[3 * i] = cell[0];
        indices[3 * i + 1] = cell[1];
        indices[3 * i + 2] = cell[2];
      }

      vertexBuffer = new gfx.VertexBuffer(
        device,
        vertexFmt,
        gfx.USAGE_STATIC,
        new Float32Array(verts),
        bunny.positions.length
      );

      indexBuffer = new gfx.IndexBuffer(
        device,
        gfx.INDEX_FMT_UINT16,
        gfx.USAGE_STATIC,
        new Uint16Array(indices),
        indices.length
      );

      bunnyLoaded = true;
  //   }
  // });

  let model = mat4.create();
  let view = mat4.create();
  let projection = mat4.create();
  let eye = vec3.create();
  let center = vec3.create();
  let up = vec3.create();

  let t = 0;

  // tick
  return function tick(dt) {
    t += dt;

    mat4.lookAt(view,
      vec3.set(eye, 30 * Math.cos(t), 20, 30 * Math.sin(t)),
      vec3.set(center, 0, 2.5, 0),
      vec3.set(up, 0, 1, 0)
    );

    mat4.perspective(projection,
      Math.PI / 4,
      canvas.width / canvas.height,
      0.01,
      1000
    );

    device.setViewport(0, 0, canvas.width, canvas.height);
    device.clear({
      color: [0.1, 0.1, 0.1, 1],
      depth: 1
    });

    if (bunnyLoaded) {
      device.enableDepthTest();
      device.enableDepthWrite();
      device.setVertexBuffer(0, vertexBuffer);
      device.setIndexBuffer(indexBuffer);
      device.setUniform('model', mat4.array(new Float32Array(16), model));
      device.setUniform('view', mat4.array(new Float32Array(16), view));
      device.setUniform('projection', mat4.array(new Float32Array(16), projection));
      device.setUniform('color', new Float32Array([0.5, 0.5, 0.5, 1]));
      device.setProgram(program);
      device.draw(0, indexBuffer.count);
    }
  };
})();