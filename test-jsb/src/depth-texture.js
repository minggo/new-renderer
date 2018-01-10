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
        uniform float near;
        uniform float far;

        void main() {
          float z = texture2D(texture, uv).x;
          float viewZ = (near * far) / ((far - near) * z - far);
          float depth = (viewZ + near) / (near - far);

          gl_FragColor.rgb = vec3(depth);
				  gl_FragColor.a = 1.0;
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

      void main () {
        vec4 pos = projection * view * model * vec4(a_position, 1);
        gl_Position = pos;
      }
    `,
      frag: `
      #ifdef GL_ES
      precision highp float;
      #endif
      uniform vec4 color;

      void main () {
        gl_FragColor = vec4(1, 1, 1, 1);
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

  let depthTexture = new gfx.Texture2D(device, {
    width: canvas.width,
    height: canvas.height,
    format: gfx.TEXTURE_FMT_D16,
    // format: gfx.TEXTURE_FMT_D32,
    wrapS: gfx.WRAP_CLAMP,
    wrapT: gfx.WRAP_CLAMP,
  });

  let frameBuffer = new gfx.FrameBuffer(device, canvas.width, canvas.height, {
    depth: depthTexture
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
      0.1,
      100
    );

    device.setViewport(0, 0, canvas.width, canvas.height);

    if (bunny) {
      device.setFrameBuffer(frameBuffer);
      device.setViewport(0, 0, canvas.width, canvas.height);
      device.clear({
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
      device.setUniform('color', new Float32Array([0.5, 0.5, 0.5, 1]));
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
      device.setUniform('color', new Float32Array([0.5, 0.5, 0.5, 1]));
      device.setProgram(bunny.program);
      device.draw(0, bunny.ib.count);

      // draw bg
      device.setFrameBuffer(null);
      device.setViewport(0, 0, canvas.width, canvas.height);
      device.clear({
        color: [0.1, 0.1, 0.1, 1],
        depth: 1
      });
      device.setTexture('texture', depthTexture, 0);
      device.setUniform('near', 0.1);
      device.setUniform('far', 100.0);
      device.setVertexBuffer(0, bg.vb);
      device.setProgram(bg.program);
      device.draw(0, bg.vb.count);
    }
  };
})();