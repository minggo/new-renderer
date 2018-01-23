/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2015 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

/**
 * !#en
 * A cc.SpriteFrame has:<br/>
 *  - texture: A cc.Texture2D that will be used by the _ccsg.Sprite<br/>
 *  - rectangle: A rectangle of the texture
 *
 * !#zh
 * 一个 SpriteFrame 包含：<br/>
 *  - 纹理：会被 Sprite 使用的 Texture2D 对象。<br/>
 *  - 矩形：在纹理中的矩形区域。
 *
 * @class SpriteFrame
 * @extends Asset
 * @uses EventTarget
 * @example
 * // load a cc.SpriteFrame with image path (Recommend)
 * var self = this;
 * var url = "test assets/PurpleMonster";
 * cc.loader.loadRes(url, cc.SpriteFrame, function (err, spriteFrame) {
 *  var node = new cc.Node("New Sprite");
 *  var sprite = node.addComponent(cc.Sprite);
 *  sprite.spriteFrame = spriteFrame;
 *  node.parent = self.node
 * });
 */
class SpriteFrame {

    constructor (rect, rotated, offset, originalSize) {
        // the location of the sprite on rendering texture
        this._rect = null;

        // for trimming
        this._offset = null;

        // for trimming
        this._originalSize = null;

        this._rotated = false;

        /**
         * !#en Top border of the sprite
         * !#zh sprite 的顶部边框
         * @property insetTop
         * @type {Number}
         * @default 0
         */
        this.insetTop = 0;

        /**
         * !#en Bottom border of the sprite
         * !#zh sprite 的底部边框
         * @property insetBottom
         * @type {Number}
         * @default 0
         */
        this.insetBottom = 0;

        /**
         * !#en Left border of the sprite
         * !#zh sprite 的左边边框
         * @property insetLeft
         * @type {Number}
         * @default 0
         */
        this.insetLeft = 0;

        /**
         * !#en Right border of the sprite
         * !#zh sprite 的左边边框
         * @property insetRight
         * @type {Number}
         * @default 0
         */
        this.insetRight = 0;

        this.init(rect, rotated, offset, originalSize);
    }

    init (rect, rotated, offset, originalSize) {
        if (rect) {
            this.setRect(rect);
        }
        else {
            this._rect = null;
        }

        if (offset) {
            this.setOffset(offset);
        }
        else {
            this._offset = null;
        }

        if (originalSize) {
            this.setOriginalSize(originalSize);
        }
        else {
            this._originalSize = null;
        }

        this._rotated = rotated || false;
    }

    /**
     * !#en Returns whether the sprite frame is rotated in the texture.
     * !#zh 获取 SpriteFrame 是否旋转
     * @method isRotated
     * @return {Boolean}
     */
    isRotated () {
        return this._rotated;
    }

    /**
     * !#en Set whether the sprite frame is rotated in the texture.
     * !#zh 设置 SpriteFrame 是否旋转
     * @method setRotated
     * @param {Boolean} bRotated
     */
    setRotated (rotated) {
        this._rotated = rotated;
    }

    /**
     * !#en Returns the rect of the sprite frame in the texture.
     * !#zh 获取 SpriteFrame 的纹理矩形区域
     * @method getRect
     * @return {Rect}
     */
    getRect () {
        return {x: this._rect.x, y: this._rect.y, width: this._rect.width, height: this._rect.height};
    }

    /**
     * !#en Sets the rect of the sprite frame in the texture.
     * !#zh 设置 SpriteFrame 的纹理矩形区域
     * @method setRect
     * @param {Rect} rect
     */
    setRect (rect) {
        this._rect = {x: rect.x, y: rect.y, width: rect.width, height: rect.height};
    }

    /**
     * !#en Returns the original size of the trimmed image.
     * !#zh 获取修剪前的原始大小
     * @method getOriginalSize
     * @return {Size}
     */
    getOriginalSize () {
        return {width: this._originalSize.width, height: this._originalSize.height};
    }

    /**
     * !#en Sets the original size of the trimmed image.
     * !#zh 设置修剪前的原始大小
     * @method setOriginalSize
     * @param {Size} size
     */
    setOriginalSize (size) {
        if (!this._originalSize) {
            this._originalSize = {width: size.width, height: size.height};
        } else {
            this._originalSize.width = size.width;
            this._originalSize.height = size.height;
        }
    }

    /**
     * !#en Returns the offset of the frame in the texture.
     * !#zh 获取偏移量
     * @method getOffset
     * @return {Vec2}
     */
    getOffset () {
        return {x: this._offset.x, y: this._offset.y};
    }

    /**
     * !#en Sets the offset of the frame in the texture.
     * !#zh 设置偏移量
     * @method setOffset
     * @param {Vec2} offsets
     */
    setOffset (offset) {
        this._offset = {x: offset.x, y: offset.y};
    }

    /**
     * !#en Clone the sprite frame.
     * !#zh 克隆 SpriteFrame
     * @method clone
     * @return {SpriteFrame}
     */
    clone () {
        var rect = {x: this._rect.x, y: this._rect.y, width: this._rect.width, height: this._rect.height};
        var offset = {x: this._offset.x, y: this._offset.y};
        var originalSize = {width: this._originalSize.width, height: this._originalSize.height};
        return new cc.SpriteFrame(rect, this._rotated, offset, originalSize);
    }
}