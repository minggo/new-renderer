(() => {
  // let resl = window.resl;
  let gfx = window.gfx;
  let device = window.device;
  let canvas = window.canvas;
  let { vec3, mat4 } = window.vmath;

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

        float angle = 1.57;
        float scale = 2.0;
        vec2 center = vec2(0.5, 0.5);
        vec2 size = vec2(256, 256);

        float pattern() {
          float s = sin(angle);
          float c = cos(angle);
          vec2 tex = uv * size - center;
          vec2 point = vec2(c * tex.x - s * tex.y, s * tex.x + c * tex.y) * scale;

          return (sin(point.x) * sin(point.y)) * 4.0;
        }

        void main() {
          vec4 color = texture2D(texture, uv);
          float p = pattern();

          // color.rgb = color.rgb * 5.0 - vec3(5.0 + p);
          // gl_FragColor = color;

          float average = (color.r + color.g + color.b) / 3.0;
          gl_FragColor = vec4( vec3( average * 10.0 - 5.0 + p ), color.a );
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

  function _bunny(device, callback) {
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
        position = a_position;

        gl_Position = pos;
      }
    `,
      frag: `
      #ifdef GL_ES
      precision highp float;
      #endif
      varying vec3 position;

      uniform vec4 color;

      void main () {
        gl_FragColor = color * vec4(position, 1);
      }
    `,
    });
    program.link();

    // resl({
    //   manifest: {
    //     js: {
    //       type: 'text',
    //       src: './assets/bunny.js'
    //     },
    //   },

    //   onDone(assets) {
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

        let vertexFmt = new gfx.VertexFormat([
          { name: gfx.ATTR_POSITION, type: gfx.ATTR_TYPE_FLOAT32, num: 3 },
        ]);

        let vb = new gfx.VertexBuffer(
          device,
          vertexFmt,
          gfx.USAGE_STATIC,
          new Float32Array(verts),
          bunny.positions.length
        );

        let ib = new gfx.IndexBuffer(
          device,
          gfx.INDEX_FMT_UINT16,
          gfx.USAGE_STATIC,
          new Uint16Array(indices),
          indices.length
        );

        callback ({
          program, vb, ib
        });
    //   }
    // });
  }

  let bunny = null;
  _bunny(device, result => {
    bunny = result;
  });

  let bg = _bigTriangle(device);

  let depthBuffer = new gfx.RenderBuffer(device,
    gfx.RB_FMT_D16,
    canvas.width,
    canvas.height
  );
  let colorTexture = new gfx.Texture2D(device, {
    width: canvas.width,
    height: canvas.height,
    format: gfx.TEXTURE_FMT_RGBA8,
    wrapS: gfx.WRAP_CLAMP,
    wrapT: gfx.WRAP_CLAMP,
  });
  let frameBuffer = new gfx.FrameBuffer(device, canvas.width, canvas.height, {
    colors: [colorTexture],
    depth: depthBuffer,
  });

  let model = mat4.create();
  let view = mat4.create();
  let projection = mat4.create();
  let eye = vec3.create();
  let center = vec3.create();
  let up = vec3.create();
  let pos = vec3.create();

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

    // device.setViewport(0, 0, canvas.width, canvas.height);

    if (bunny) {
      device.setFrameBuffer(frameBuffer);
      device.setViewport(0, 0, canvas.width, canvas.height);
      device.clear({
        color: [0.1, 0.1, 0.1, 1],
        depth: 1
      });

      // draw bunny1
      mat4.fromTranslation(model, vec3.set(pos, 5, 0, 0));
      device.enableDepthTest();
      device.enableDepthWrite();
      device.setVertexBuffer(0, bunny.vb);
      device.setIndexBuffer(bunny.ib);
      device.setUniform('model', mat4.array(new Float32Array(16), model));
      device.setUniform('view', mat4.array(new Float32Array(16), view));
      device.setUniform('projection', mat4.array(new Float32Array(16), projection));
      device.setUniform('color', new Float32Array([0.1, 0.1, 0.1, 1]));
      device.setProgram(bunny.program);
      device.draw(0, bunny.ib.count);

      // draw bunny2
      mat4.fromTranslation(model, vec3.set(pos, -5, 0, 0));
      device.enableDepthTest();
      device.enableDepthWrite();
      device.setVertexBuffer(0, bunny.vb);
      device.setIndexBuffer(bunny.ib);
      device.setUniform('model', mat4.array(new Float32Array(16), model));
      device.setUniform('view', mat4.array(new Float32Array(16), view));
      device.setUniform('projection', mat4.array(new Float32Array(16), projection));
      device.setUniform('color', new Float32Array([0.3, 0.3, 0.3, 1]));
      device.setProgram(bunny.program);
      device.draw(0, bunny.ib.count);

      // draw bg
      device.setFrameBuffer(null);
      device.setViewport(0, 0, canvas.width, canvas.height);
      device.clear({
        color: [0.1, 0.1, 0.1, 1],
        depth: 1
      });
      device.setTexture('texture', colorTexture, 0);
      device.setVertexBuffer(0, bg.vb);
      device.setProgram(bg.program);
      device.draw(0, bg.vb.count);
    }
  };
})();