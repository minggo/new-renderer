
/*
 * scene-graph v1.3.5
 * (c) 2017 @Johnny Wu
 * Released under the MIT License.
 */

(function (exports,vmath) {
'use strict';

// REFERENCE: https://gist.github.com/jed/982883

function b(a) {
  return a           // if the placeholder was passed, return
    ? (              // a random number from 0 to 15
      a ^            // unless b is 8,
      Math.random()  // in which case
      * 16           // a random number from
      >> a / 4       // 8 to 11
    ).toString(16)   // in hexadecimal
    : (              // or otherwise a concatenated string:
      [1e7] +        // 10000000 +
      -1e3 +         // -1000 +
      -4e3 +         // -4000 +
      -8e3 +         // -80000000 +
      -1e11          // -100000000000,
    ).replace(       // replacing
      /[018]/g,      // zeroes, ones, and eights with
      b              // random hex digits
      );
}

let v3_a = vmath.vec3.create();
let q_a = vmath.quat.create();
let m3_a = vmath.mat3.create();
let m3_b = vmath.mat3.create();
let m4_a = vmath.mat4.create();

class Node {
  static mixin (cls) {
    Object.getOwnPropertyNames(Node.prototype).forEach(function (name) {
      if (cls.prototype.hasOwnProperty(name) === false) {
        Object.defineProperty(
          cls.prototype,
          name,
          Object.getOwnPropertyDescriptor(Node.prototype, name)
        );
      }
    });
    cls.prototype.__initNode = function () {
      this._id = b();
      this._enabled = true;
      this._parent = null;
      this._children = [];

      this.name = '';
      this.lpos = vmath.vec3.new(0, 0, 0);
      this.lscale = vmath.vec3.new(1, 1, 1);
      this.lrot = vmath.quat.new(0, 0, 0, 1);
    };
  }

  constructor(name) {
    this._id = b();
    this._enabled = true;
    this._parent = null;
    this._children = [];

    this.name = name || '';
    this.lpos = vmath.vec3.new(0, 0, 0);
    this.lscale = vmath.vec3.new(1, 1, 1);
    this.lrot = vmath.quat.new(0, 0, 0, 1);
  }

  /**
   * @property {boolean} enabled
   * NOTE: This property will invoke `_onEnableChanged` if it exists.
   */
  get enabled() {
    return this._enabled;
  }
  set enabled(val) {
    if (this._enabled === val) {
      return;
    }

    this._enabled = val;

    if (this._onEnableChanged) {
      this._onEnableChanged();
    }
  }

  /**
   * @property {number} id
   * @readonly
   */
  get id() {
    return this._id;
  }

  /**
   * @property parent
   * @readonly
   *
   * get parent
   */
  get parent() {
    return this._parent;
  }

  /**
   * @property children
   *
   * get children
   */
  get children() {
    return this._children;
  }

  // ===============================
  // hierarchy
  // ===============================

  /**
   * @method setParent
   * @param {Node} newParent
   * @return {boolean}
   *
   * NOTE: This function will invoke `_onParentChanged` if it exists.
   */
  setParent(newParent) {
    let oldParent = this._parent;

    // newParent is the current parent of this
    if (oldParent === newParent) {
      return false;
    }

    // make sure the newParent is not a child of this
    let cur = newParent;
    while (cur) {
      if (cur === this) {
        // console.warn(`Failed to set parent for ${this.name}: the new parent ${newParent.name} is its child.`);
        return false;
      }

      cur = cur._parent;
    }

    // remove this from its old parent (if it has)
    if (oldParent) {
      let len = oldParent._children.length;
      for (let i = 0; i < len; ++i) {
        if (oldParent._children[i] === this) {
          oldParent._children.splice(i, 1);
          break;
        }
      }
    }

    // append it to the new parent
    this._parent = newParent;
    if (newParent) {
      newParent._children.push(this);
    }

    // invoke _onParentChanged
    if (this._onParentChanged) {
      this._onParentChanged(oldParent, newParent);
    }

    return true;
  }

  /**
   * @method insertAt
   * @param {Node} node
   * @param {number} idx
   *
   * Insert `node` before the `idx` of children.
   * NOTE: This function will invoke `_onParentChanged` if it exists.
   */
  insertAt(idx, node) {
    if (!node) {
      return false;
    }

    // make sure the node is not the parent of this
    let cur = this;
    while (cur) {
      if (cur === node) {
        // console.warn(`Failed to append ${node.name}: it is the ancient of current node.`);
        return false;
      }

      cur = cur._parent;
    }

    let oldParent = node._parent;

    // 0 <= idx <= len
    let len = this._children.length;
    idx = idx < 0 ? 0 : idx > len ? len : idx;

    // remove node from its current parent
    if (oldParent) {
      len = oldParent._children.length;
      for (let i = 0; i < len; ++i) {
        if (oldParent._children[i] === node) {
          // if we already have the child
          if (oldParent === this) {
            // if its insert position didn't changed, don't do anything.
            if (i === idx || i === idx - 1) {
              return false;
            }

            if (i < idx - 1) {
              idx = idx - 1;
            }
          }

          oldParent._children.splice(i, 1);
          break;
        }
      }
    }

    // append the new node
    node._parent = this;
    this._children.splice(idx, 0, node);

    // invoke _onParentChanged
    if (node._onParentChanged && node._parent !== this) {
      node._onParentChanged(oldParent, this);
    }

    return true;
  }

  /**
   * @method append
   * @param {Node} node
   * @return {boolean}
   *
   * Append `node` at the end of children.
   * NOTE: This function will invoke `_onParentChanged` if it exists.
   */
  append(node) {
    if (!node) {
      return false;
    }

    // make sure the node is not the parent of this
    let cur = this;
    while (cur) {
      if (cur === node) {
        // console.warn(`Failed to append ${node.name}: it is the ancient of current node.`);
        return false;
      }

      cur = cur._parent;
    }

    let oldParent = node._parent;

    // remove node from its current parent
    if (oldParent) {
      let len = oldParent._children.length;
      for (let i = 0; i < len; ++i) {
        if (oldParent._children[i] === node) {
          // if we already have the child and its insert position didn't changed, don't do anything.
          if (oldParent === this && i === len - 1) {
            return false;
          }

          oldParent._children.splice(i, 1);
          break;
        }
      }
    }

    // append the new node
    node._parent = this;
    this._children.push(node);

    // invoke _onParentChanged
    if (node._onParentChanged && node._parent !== this) {
      node._onParentChanged(oldParent, this);
    }

    return true;
  }

  /**
   * @method remove
   *
   * Remove self from parent
   * NOTE: This function will invoke `_onParentChanged` if it exists.
   */
  remove() {
    if (this._parent) {
      this._parent.removeChild(this);
    }
  }

  /**
   * @method removeChild
   * @param {Node} node
   *
   * Remove child
   * NOTE: This function will invoke `_onParentChanged` if it exists.
   */
  removeChild(node) {
    let len = this._children.length;

    for (let i = 0; i < len; ++i) {
      if (this._children[i] === node) {
        this._children.splice(i, 1);
        node._parent = null;

        // invoke _onParentChanged
        if (node._onParentChanged) {
          node._onParentChanged(this, null);
        }

        return true;
      }
    }

    // console.warn(`Failed to remove node ${node.name}, can not find it.`);
    return false;
  }

  // ===============================
  // transform helper
  // ===============================

  /**
   * @method getWorldPos
   * @param {vec3} pos
   * @param {vec3} [up] - default is (0,1,0)
   * @return {vec3}
   *
   * Set rotation by lookAt target point
   */
  lookAt(pos, up) {
    this.getWorldPos(v3_a);
    vmath.vec3.sub(v3_a, v3_a, pos); // NOTE: we use -z for view-dir
    vmath.vec3.normalize(v3_a, v3_a);
    vmath.quat.fromViewUp(q_a, v3_a, up);

    this.setWorldRot(q_a);
  }

  // ===============================
  // transform
  // ===============================

  /**
   * @method getWorldPos
   * @param {vec3} out
   * @return {vec3}
   *
   * Calculate and return world position
   */
  getWorldPos(out) {
    vmath.vec3.copy(out, this.lpos);

    let cur = this._parent;
    while (cur) {
      // out = parent_lscale * lpos
      vmath.vec3.mul(out, out, cur.lscale);

      // out = parent_lrot * out
      vmath.vec3.transformQuat(out, out, cur.lrot);

      // out = out + lpos
      vmath.vec3.add(out, out, cur.lpos);

      cur = cur._parent;
    }

    return out;
  }

  /**
   * @method setWorldPos
   * @param {vec3} pos
   *
   * Set world position
   */
  setWorldPos(pos) {
    // NOTE: this is faster than invert world matrix and transform the point

    if (this._parent) {
      this._parent.invTransformPoint(this.lpos, pos);
      return;
    }

    vmath.vec3.copy(this.lpos, pos);
  }

  /**
   * @method getWorldRot
   * @param {quat} out
   * @return {quat}
   *
   * Calculate and return world rotation
   */
  getWorldRot(out) {
    vmath.quat.copy(out, this.lrot);

    // result = ... * parent.parent.lrot * parent.lrot * lrot
    let cur = this._parent;
    while (cur) {
      vmath.quat.mul(out, cur.lrot, out);

      cur = cur._parent;
    }

    return out;
  }

  /**
   * @method setWorldRot
   * @param {quat} rot
   *
   * Set world position
   */
  setWorldRot(rot) {
    // lrot = rot * inv(prarent.wrot);
    if (this._parent) {
      this._parent.getWorldRot(this.lrot);
      vmath.quat.conjugate(this.lrot, this.lrot);
      vmath.quat.mul(this.lrot, this.lrot, rot);

      return;
    }

    vmath.quat.copy(this.lrot, rot);
  }

  /**
   * @method getWorldScale
   * @param {quat} out
   * @return {quat}
   *
   * Calculate and return world rotation
   */
  getWorldScale(out) {
    // invRot = inv(world_rot)
    this.getWorldRot(q_a);
    vmath.quat.conjugate(q_a, q_a);
    vmath.mat3.fromQuat(out, q_a);

    // worldRotScale
    this.getWorldRS(m3_a);

    // invRot * worldRotScale
    vmath.mat3.mul(out, out, m3_a);

    return out;
  }

  /**
   * @method invTransformPoint
   * @param {vec3} out
   * @param {vec3} vec3
   *
   * Transforms position from world space to local space.
   */
  invTransformPoint(out, pos) {
    if (this._parent) {
      this._parent.invTransformPoint(out, pos);
    } else {
      vmath.vec3.copy(out, pos);
    }

    // out = parent_inv_pos - lpos
    vmath.vec3.sub(out, out, this.lpos);

    // out = inv(lrot) * out
    vmath.quat.conjugate(q_a, this.lrot);
    vmath.vec3.transformQuat(out, out, q_a);

    // out = (1/scale) * out
    vmath.vec3.inverseSafe(v3_a, this.lscale);
    vmath.vec3.mul(out, out, v3_a);

    return out;
  }

  /**
   * @method getLocalMatrix
   * @param {mat4} out
   * @return {mat4}
   *
   * Calculate and return local transform
   */
  getLocalMatrix(out) {
    vmath.mat4.fromRTS(out, this.lrot, this.lpos, this.lscale);
    return out;
  }

  /**
   * @method getWorldMatrix
   * @param {mat4} out
   * @return {mat4}
   *
   * Calculate and return world transform
   */
  getWorldMatrix(out) {
    // out = ... * parent.parent.local * parent.local * local;
    this.getLocalMatrix(out);

    let cur = this._parent;
    while (cur) {
      cur.getLocalMatrix(m4_a);
      vmath.mat4.mul(out, m4_a, out);

      cur = cur._parent;
    }

    return out;
  }

  /**
   * @method getWorldRT
   * @param {mat4} out
   * @return {mat4}
   *
   * Calculate and return world transform without scale
   */
  getWorldRT(out) {
    this._getWorldPosAndRot(v3_a, q_a);
    vmath.mat4.fromRT(out, q_a, v3_a);

    return out;
  }

  /**
   * @method getWorldRS
   * @param {mat3} out
   *
   * Calculate and return world rotation and scale matrix
   */
  getWorldRS(out) {
    vmath.mat3.set(m3_a,
      this.lscale.x, 0, 0,
      0, this.lscale.y, 0,
      0, 0, this.lscale.z
    );
    vmath.mat3.fromQuat(m3_b, this.lrot);

    if (this._parent) {
      // parent_RS * rot * scale
      this._parent.getWorldRS(out);
      vmath.mat3.mul(out, out, m3_b);
      vmath.mat3.mul(out, out, m3_a);
    } else {
      // rot * scale
      vmath.mat3.mul(out, m3_b, m3_a);
    }

    return out;
  }

  /**
   * @method _getWorldPosAndRot
   * @param {vec3} opos
   * @param {vec3} orot
   *
   * Calculate and return world position
   */
  _getWorldPosAndRot(opos, orot) {
    vmath.vec3.copy(opos, this.lpos);
    vmath.quat.copy(orot, this.lrot);

    let cur = this._parent;
    while (cur) {
      // opos = parent_lscale * lpos
      vmath.vec3.mul(opos, opos, cur.lscale);

      // opos = parent_lrot * opos
      vmath.vec3.transformQuat(opos, opos, cur.lrot);

      // opos = opos + lpos
      vmath.vec3.add(opos, opos, cur.lpos);

      // orot = lrot * orot
      vmath.quat.mul(orot, cur.lrot, orot);

      cur = cur._parent;
    }
  }
}

/**
 * @method walk
 * @param {Node} node
 * @param {function} fn
 * @param {Node} fn.node
 * @param {Node} fn.parent
 * @param {number} fn.level
 */
function walk(node, fn, level = 0) {
  level += 1;
  let len = node.children.length;

  for (let i = 0; i < len; ++i) {
    let child = node.children[i];
    let continueWalk = fn(child, node, level);

    if (continueWalk !== false) {
      walk(child, fn, level);
    }
  }
}

/**
 * @method flat
 * @param {Node} node
 */
function flat(node) {
  let out = [];

  out.push(node);
  walk(node, function (iter) {
    out.push(iter);
  });

  return out;
}

/**
 * @method replace
 * @param {Node} oldNode
 * @param {Node} newNode
 */
function replace(oldNode, newNode) {
  newNode.remove();

  let parent = oldNode._parent;
  if (!parent) {
    return;
  }

  oldNode._parent = null;
  newNode._parent = parent;

  let len = parent._children.length;
  for (let i = 0; i < len; ++i) {
    if (parent._children[i] === oldNode) {
      parent._children[i] = newNode;
      return;
    }
  }
}

/**
 * @method enable
 * @param {Node} node
 * @param {boolean} val
 * @param {function} fn
 */
function enable(node, val, fn) {
  if (node._enabled !== val) {
    node._enabled = val;

    if (fn) {
      fn(node, val);

      walk(node, function (n) {
        if (n._enabled) {
          fn(n, val);
          return true;
        }

        return false;
      });
    }
  }
}

/**
 * @method clone
 * @param {Node} node
 * @param {function} ctor
 * @param {function} fn
 * @return {Node}
 */
function clone(node, ctor = Node, fn = null) {
  let newNode = new ctor();
  newNode.name = node.name;
  vmath.vec3.copy(newNode.lpos, node.lpos);
  vmath.vec3.copy(newNode.lscale, node.lscale);
  vmath.quat.copy(newNode.lrot, node.lrot);

  // do user custom clone function
  if (fn) {
    fn(newNode, node);
  }

  return newNode;
}

/**
 * @method deepClone
 * @param {Node} node
 * @param {function} ctor
 * @param {function} fn
 * @return {Node}
 */
function deepClone(node, ctor = Node, fn = null) {
  let newNode = clone(node, ctor, fn);

  newNode._children = new Array(node._children.length);
  for (let i = 0; i < node._children.length; ++i) {
    let child = node._children[i];
    let newChild = deepClone(child, ctor, fn);
    newNode._children[i] = newChild;
    newChild._parent = newNode;
  }

  return newNode;
}

/**
 * @method enabledInHierarchy
 * @param {Node} node
 * @param {boolean} includeSelf
 */
function enabledInHierarchy(node, includeSelf = true) {
  if (includeSelf && !node._enabled) {
    return false;
  }

  let cur = node._parent;
  while (cur) {
    if (!cur._enabled) {
      return false;
    }

    cur = cur._parent;
  }

  return true;
}

/**
 * @method find
 * @param {Node} root
 * @param {string} path
 */
function find(root, path) {
  let names = path.split('/');

  function _recurse(node, level) {
    let len = node.children.length;
    let name = names[level];

    for (let i = 0; i < len; ++i) {
      let child = node.children[i];

      if (child.name !== name) {
        continue;
      }

      if (level === names.length - 1) {
        return child;
      } else {
        return _recurse(child, level + 1);
      }
    }

    return null;
  }

  return _recurse(root, 0);
}

let utils = {
  walk,
  flat,
  replace,
  enable,
  clone,
  deepClone,
  enabledInHierarchy,
  find,
};

exports.Node = Node;
exports.utils = utils;

}((this.sgraph = this.sgraph || {}),window.vmath));
//# sourceMappingURL=scene-graph.dev.js.map
