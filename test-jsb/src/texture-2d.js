(() => {
  let gfx = window.gfx;
  let device = window.device;
  let canvas = window.canvas;
  // let resl = window.resl;
  let { quat, vec3, mat4 } = window.vmath;
  let texture = null;

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

  // let canvasElement = document.createElement('canvas');
  // canvasElement.width = 512;
  // canvasElement.height = 512;
  // let ctx = canvasElement.getContext('2d');
  // ctx.fillStyle = 'rgb(199,237,204)';
  // ctx.fillRect(0, 0, 512, 512);
  // ctx.fillStyle = 'rgb(0,0,0)';
  // ctx.fillText('use canvas element as texture, filled by rgb(199,237,204)', 90, 256);

  let textTextureInfo = getTextTextureInfo("use canvas element as texture, filled by rgb(199,237,204)", {
      fontSize: 32,
      textAlign: TextHAlignment.CENTER,
      verticalAlign: TextVAlignment.CENTER,
      boundingWidth: 512,
      boundingHeight: 512
  }, DeviceTextAlign.CENTER);

  let canvasTexture;

  canvasTexture = new gfx.Texture2D(device, {
    width: 512,
    height: 512,
    images: [textTextureInfo.data] //[canvasElement]
  });

  // resl({
  //   manifest: {
  //     image: {
  //       type: 'image',
  //       src: './assets/uv_checker_01.jpg'
  //     },
  //   },
  //   onDone (assets) {
      let image = getImageInfo("assets/uv_checker_01.jpg"); //assets.image;
      texture = new gfx.Texture2D(device, {
        width : image.width,
        height : image.height,
        format: gfx.TEXTURE_FMT_RGB8,
        images : [image.data]
      });
  //   }
  // });
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
  let transform1 = mat4.create();
  mat4.fromRTS(transform0, quat.create(), vec3.new(-0.5, 0, 0), vec3.new(0.5, 0.5, 0.5));
  mat4.fromRTS(transform1, quat.create(), vec3.new(0.5, 0, 0), vec3.new(0.5, 0.5, 0.5));
  // tick
  return function tick() {
    device.setViewport(0, 0, canvas.width, canvas.height);
    device.clear({
      color: [0.1, 0.1, 0.1, 1],
      depth: 1
    });

    if (canvasTexture) {
      device.setVertexBuffer(0, vertexBuffer);
      device.setUniform('color', new Float32Array([1, 0, 0, 1]));
      device.setTexture('texture', canvasTexture, 0);
      device.setUniform('transform', mat4.array(new Float32Array(16), transform0));
      device.setProgram(program);
      device.draw(0, vertexBuffer.count);
    }
    if (texture) {
      device.setVertexBuffer(0, vertexBuffer);
      device.setUniform('color', new Float32Array([1, 0, 0, 1]));
      device.setTexture('texture', texture, 0);
      device.setUniform('transform', mat4.array(new Float32Array(16), transform1));
      device.setProgram(program);
      device.draw(0, vertexBuffer.count);
    }
  };
})();
