((global) => {
    'use strict';
    const engine = window.engine;
  
    const { gfx, renderMode, RecyclePool, InputAssembler, ForwardRenderer } = engine;
    const { Scene, Camera, Model, SpriteMaterial } = engine;
    const { mat4 } = engine.math;

    let _node = new window.sgraph.Node();
    let _color = ((255<<24) >>> 0) + (255<<16) + (255<<8) + 255;
    let _matrix = mat4.create();

    let _vfmt = new gfx.VertexFormat([
        { name: gfx.ATTR_POSITION, type: gfx.ATTR_TYPE_FLOAT32, num: 3 },
        { name: gfx.ATTR_COLOR, type: gfx.ATTR_TYPE_UINT8, num: 4, normalize: true },
        { name: gfx.ATTR_UV0, type: gfx.ATTR_TYPE_FLOAT32, num: 2 }
    ]);

    const FLOATS_PER_VERT = _vfmt._bytes / 4;
    const MAX_VERTEX = 20000;
    const MAX_INDICE = 30000;
  
    // Renderer walker

    let walker = {
        init (device, builtins) {
            this.forwardRenderer = new ForwardRenderer(device, builtins);
            // Buffers
            let verts = new Float32Array(MAX_VERTEX * FLOATS_PER_VERT);
            this._bufs = [{
                verts: verts,
                uintVerts: new Uint32Array(verts.buffer),
                indices: new Uint16Array(MAX_INDICE)
            }];
            this._nextBuf = 0;
            this._switchBuffer();

            this._vbPool = new RecyclePool(function () {
                let vb = new gfx.VertexBuffer(
                    device,
                    _vfmt,
                    gfx.USAGE_DYNAMIC,
                    null,
                    0
                );
                vb._data = null;
                return vb;
            }, 16);
            this._ibPool = new RecyclePool(function () {
                var ib = new gfx.IndexBuffer(
                    device,
                    gfx.INDEX_FMT_UINT16,
                    gfx.USAGE_STATIC,
                    null,
                    0
                );
                ib._data = null;
                return ib;
            }, 16);
            this._iaPool = new RecyclePool(function () {
                return new InputAssembler();
            }, 16);

            this._modelPool = new RecyclePool(() => {
                return new Model();
            }, 16);

            this._scene = null;
            this._batchedModels = [];
            this._sortKey = 0;
        },

        reset() {
            // Reset pools
            this._iaPool.reset();
            this._vbPool.reset();
            this._ibPool.reset();

            // Reset scene
            let scene = this._scene;
            let models = this._batchedModels;
            for (let i = 0; i < models.length; ++i) {
                // remove from scene
                models[i].clearInputAssemblers();
                models[i].clearEffects();
                scene.removeModel(models[i]);
            }
            this._modelPool.reset();
            models.length = 0;
            this._sortKey = 0;
            this._scene = null;

            // Reset buffer
            this._nextBuf = 0;
            this._switchBuffer();
        },
    
        _switchBuffer () {
            if (this._nextBuf === this._bufs.length) {
                let verts = new Float32Array(MAX_VERTEX * FLOATS_PER_VERT);
                this._bufs.push({
                    verts: verts,
                    uintVerts: new Uint32Array(verts.buffer),
                    indices: new Uint16Array(MAX_INDICE)
                });
            }
            let buf = this._bufs[this._nextBuf];
            this._verts = buf.verts;
            this._uintVerts = buf.uintVerts;
            this._indices = buf.indices;
            this._vOffset = 0;
            this._iOffset = 0;
            this._nextBuf++;
        },

        updateUV (node) {
            let renderData = node.renderData;
            if (renderData && renderData.effect) {
                let effect = renderData.effect;
                let data = renderData._data;
                let texture = effect.getProperty('texture');
                let texw = texture._width,
                    texh = texture._height;
                let frame = node.frame;
                let rect = frame._rect;
                let l = texw === 0 ? 0 : rect.x / texw;
                let r = texw === 0 ? 0 : (rect.x + rect.width) / texw;
                let b = texh === 0 ? 0 : (rect.y + rect.height) / texh;
                let t = texh === 0 ? 0 : rect.y / texh;
                
                data[0].u = l;
                data[0].v = b;
                data[1].u = r;
                data[1].v = b;
                data[2].u = l;
                data[2].v = t;
                data[3].u = r;
                data[3].v = t;

                renderData.uvDirty = false;
            }
        },

        updateVerts (node) {
            let renderData = node.renderData,
                data = renderData._data,
                cw = node.width,
                ch = node.height,
                appx = node.anchorPoint.x * cw,
                appy = node.anchorPoint.y * ch;
            let l = -appx;
            let b = -appy;
            let r = cw - appx;
            let t = ch - appy;
            
            data[0].x = l;
            data[0].y = b;
            data[1].x = r;
            data[1].y = b;
            data[2].x = l;
            data[2].y = t;
            data[3].x = r;
            data[3].y = t;
    
            renderData.vertDirty = false;
        },

        fillBuffers (node, vertexOffset, indiceOffset, vertexId, vbuf, uintbuf, ibuf) {
            let index = vertexOffset * _vfmt._bytes / 4;
            let renderData = node.renderData;
            let data = renderData._data;
            
            node.getWorldMatrix(_matrix);
            let a = _matrix.m00,
                b = _matrix.m01,
                c = _matrix.m04,
                d = _matrix.m05,
                tx = _matrix.m12,
                ty = _matrix.m13;
        
            let vert;
            let length = renderData.dataLength;
            for (let i = 0; i < length; i++) {
                vert = data[i];
                vbuf[index + 0] = vert.x * a + vert.y * c + tx;
                vbuf[index + 1] = vert.x * b + vert.y * d + ty;
                vbuf[index + 2] = node.lpos.z;
                vbuf[index + 4] = vert.u;
                vbuf[index + 5] = vert.v;
                uintbuf[index + 3] = _color;
                index += 6;
            }

            ibuf[indiceOffset + 0] = vertexId;
            ibuf[indiceOffset + 1] = vertexId + 1;
            ibuf[indiceOffset + 2] = vertexId + 2;
            ibuf[indiceOffset + 3] = vertexId + 1;
            ibuf[indiceOffset + 4] = vertexId + 3;
            ibuf[indiceOffset + 5] = vertexId + 2;
        },

        _flush (vertexFormat, effect, lastByte, vertexCount, indiceCount) {
            let vertexByte = vertexCount * vertexFormat._bytes,
                byteOffset = lastByte - vertexByte,
                vertexsData = null,
                indicesData = null;
                
            // Prepare data view for vb ib
            if (vertexCount > 0 && indiceCount > 0) {
                vertexsData = new Float32Array(this._verts.buffer, byteOffset, vertexByte / 4);
                byteOffset = 2 * this._iOffset;
                indicesData = new Uint16Array(this._indices.buffer, byteOffset, indiceCount);
            }
    
            // Generate vb, ib, ia
            let vb = this._vbPool.add();
            device._stats.vb -= vb._bytes;
            vb._format = vertexFormat;
            vb._numVertices = vertexCount;
            vb._bytes = vertexByte;
            vb._data = vertexsData;
            device._stats.vb += vb._bytes;
        
            let ib = this._ibPool.add();
            device._stats.ib -= ib._bytes;
            ib._numIndices = indiceCount;
            ib._bytes = 2 * indiceCount;
            ib._data = indicesData;
            device._stats.ib += ib._bytes;
        
            let ia = this._iaPool.add();
            ia._vertexBuffer = vb;
            ia._indexBuffer = ib;
            ia._start = 0;
            ia._count = indiceCount;
            
            // Generate model
            let model = this._modelPool.add();
            this._batchedModels.push(model);
            model.sortKey = this._sortKey++;
            model._viewID = -1;
            model.setNode(_node);
            model.addEffect(effect);
            model.addInputAssembler(ia);
            
            this._scene.addModel(model);
        },

        _checkBatchBroken (effect, vertexOffset, indiceOffset, needNewBuf) {
            let vertexCount = vertexOffset - this._vOffset,
                indiceCount = indiceOffset - this._iOffset;
            if (effect && vertexCount > 0 && indiceCount > 0) {
                this._flush(_vfmt, effect, vertexOffset * _vfmt._bytes, vertexCount, indiceCount);
                if (needNewBuf) {
                    this._switchBuffer();
                }
                else {
                    // update buffer
                    this._vOffset = vertexOffset;
                    this._iOffset = indiceOffset;
                }
            }
        },

        renderScene (scene, nodes) {
            let node, renderData, effect, needNewBuf;
            let vertexId = 0,
                vertexOffset = 0,
                indiceOffset = 0,
                currEffect = null;
            this.reset();
            this._scene = scene;
            for (let i = 0; i < nodes.length; i++) 
            {
                node = nodes[i];
                renderData = node.renderData;
                if (renderData.uvDirty) {
                    this.updateUV(node);
                }
                if (renderData.vertDirty) {
                    this.updateVerts(node);
                }

                effect = renderData.effect;
                if (!effect) {
                    continue;
                }

                // breaking batch
                needNewBuf = (vertexOffset + renderData.vertexCount > MAX_VERTEX) || (indiceOffset + renderData.indiceCount > MAX_INDICE);
                if (currEffect && (currEffect != effect || needNewBuf)) {
                    this._checkBatchBroken(currEffect, vertexOffset, indiceOffset, needNewBuf);
                    currEffect = effect;
                }
                // Init effect
                else if (!currEffect) {
                    currEffect = effect;
                }

                if (needNewBuf) {
                    vertexOffset = 0;
                    indiceOffset = 0;
                }

                let vertexId = vertexOffset - this._vOffset;
                this.fillBuffers(node, vertexOffset, indiceOffset, vertexId, this._verts, this._uintVerts, this._indices);

                vertexOffset += renderData.vertexCount;
                indiceOffset += renderData.indiceCount;
            }

            // last batch
            this._checkBatchBroken(currEffect, vertexOffset, indiceOffset, false);

            // draw
            this.forwardRenderer.render(scene);
        }
    };

    global.walker = walker;
})(window);