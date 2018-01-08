(() => {
  let gfx = window.gfx;
  let device = window.device;
  let canvas = window.canvas;

  // init resources
  let program = new gfx.Program(device, {
    vert: `
    #ifdef GL_ES
      precision highp float;
    #endif
      attribute vec2 a_position;
      void main () {
        gl_Position = vec4(a_position, 0, 1);
      }
    `,
    frag: `
    #ifdef GL_ES
      precision highp float;
    #endif
      uniform vec4 color;
      void main () {
        gl_FragColor = color;
      }
    `,
  });
  program.link();

  let vertexFmt = new gfx.VertexFormat([
    { name: gfx.ATTR_POSITION, type: gfx.ATTR_TYPE_FLOAT32, num: 2 },
  ]);
  let vertexBuffer = new gfx.VertexBuffer(
    device,
    vertexFmt,
    gfx.USAGE_STATIC,
    new Float32Array([-1, 0, 0, -1, 1, 1]),
    3
  );

  let time = 0;

  // tick
  return function tick(dt) {
    time += dt;

    device.setViewport(0, 0, canvas.width, canvas.height);
    device.clear({
      color: [0.1, 0.1, 0.1, 1],
      depth: 1
    });
    device.setVertexBuffer(0, vertexBuffer);
    device.setUniform('color', new Float32Array([1, Math.abs(Math.sin(time)), 0, 1]));
    device.setProgram(program);
    device.draw(0, vertexBuffer.count);
  };
})();