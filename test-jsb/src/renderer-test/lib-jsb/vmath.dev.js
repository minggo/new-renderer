
/*
 * vmath v1.4.7
 * (c) 2017 @Johnny Wu
 * Released under the MIT License.
 */

(function (exports) {
'use strict';

const _d2r = Math.PI / 180.0;
const _r2d = 180.0 / Math.PI;

/**
 * @property {number} EPSILON
 */
const EPSILON = 0.000001;

/**
 * Tests whether or not the arguments have approximately the same value, within an absolute
 * or relative tolerance of glMatrix.EPSILON (an absolute tolerance is used for values less
 * than or equal to 1.0, and a relative tolerance is used for larger values)
 *
 * @param {Number} a The first number to test.
 * @param {Number} b The second number to test.
 * @returns {Boolean} True if the numbers are approximately equal, false otherwise.
 */
function equals(a, b) {
  return Math.abs(a - b) <= EPSILON * Math.max(1.0, Math.abs(a), Math.abs(b));
}

/**
 * Tests whether or not the arguments have approximately the same value by given maxDiff
 *
 * @param {Number} a The first number to test.
 * @param {Number} b The second number to test.
 * @param {Number} maxDiff Maximum difference.
 * @returns {Boolean} True if the numbers are approximately equal, false otherwise.
 */
function approx(a, b, maxDiff) {
  maxDiff = maxDiff || EPSILON;
  return Math.abs(a - b) <= maxDiff;
}

/**
 * Clamps a value between a minimum float and maximum float value.
 *
 * @method clamp
 * @param {number} val
 * @param {number} min
 * @param {number} max
 * @return {number}
 */
function clamp(val, min, max) {
  return val < min ? min : val > max ? max : val;
}

/**
 * Clamps a value between 0 and 1.
 *
 * @method clamp01
 * @param {number} val
 * @return {number}
 */
function clamp01(val) {
  return val < 0 ? 0 : val > 1 ? 1 : val;
}

/**
 * @method lerp
 * @param {number} from
 * @param {number} to
 * @param {number} ratio - the interpolation coefficient
 * @return {number}
 */
function lerp(from, to, ratio) {
  return from + (to - from) * ratio;
}

/**
* Convert Degree To Radian
*
* @param {Number} a Angle in Degrees
*/
function toRadian(a) {
  return a * _d2r;
}

/**
* Convert Radian To Degree
*
* @param {Number} a Angle in Radian
*/
function toDegree(a) {
  return a * _r2d;
}

/**
* @method random
*/
const random = Math.random;

/**
 * Returns a floating-point random number between min (inclusive) and max (exclusive).
 *
 * @method randomRange
 * @param {number} min
 * @param {number} max
 * @return {number} the random number
 */
function randomRange(min, max) {
  return Math.random() * (max - min) + min;
}

/**
 * Returns a random integer between min (inclusive) and max (exclusive).
 *
 * @method randomRangeInt
 * @param {number} min
 * @param {number} max
 * @return {number} the random integer
 */
function randomRangeInt(min, max) {
  return Math.floor(randomRange(min, max));
}

/**
 * Returns the next power of two for the value
 *
 * @method nextPow2
 * @param {number} val
 * @return {number} the the next power of two
 */
function nextPow2(val) {
  --val;
  val = (val >> 1) | val;
  val = (val >> 2) | val;
  val = (val >> 4) | val;
  val = (val >> 8) | val;
  val = (val >> 16) | val;
  ++val;

  return val;
}

/**
 * Bit twiddling hacks for JavaScript.
 *
 * Author: Mikola Lysenko
 *
 * Ported from Stanford bit twiddling hack library:
 *    http://graphics.stanford.edu/~seander/bithacks.html
 */

// Number of bits in an integer
const INT_BITS = 32;
const INT_MAX =  0x7fffffff;
const INT_MIN = -1<<(INT_BITS-1);

/**
 * Returns -1, 0, +1 depending on sign of x
 *
 * @param {number} v
 * @returns {number}
 */
function sign(v) {
  return (v > 0) - (v < 0);
}

/**
 * Computes absolute value of integer
 *
 * @param {number} v
 * @returns {number}
 */
function abs(v) {
  let mask = v >> (INT_BITS-1);
  return (v ^ mask) - mask;
}

/**
 * Computes minimum of integers x and y
 *
 * @param {number} x
 * @param {number} y
 * @returns {number}
 */
function min(x, y) {
  return y ^ ((x ^ y) & -(x < y));
}

/**
 * Computes maximum of integers x and y
 *
 * @param {number} x
 * @param {number} y
 * @returns {number}
 */
function max(x, y) {
  return x ^ ((x ^ y) & -(x < y));
}

/**
 * Checks if a number is a power of two
 *
 * @param {number} v
 * @returns {boolean}
 */
function isPow2(v) {
  return !(v & (v-1)) && (!!v);
}

/**
 * Computes log base 2 of v
 *
 * @param {number} v
 * @returns {number}
 */
function log2(v) {
  let r, shift;
  r =     (v > 0xFFFF) << 4; v >>>= r;
  shift = (v > 0xFF  ) << 3; v >>>= shift; r |= shift;
  shift = (v > 0xF   ) << 2; v >>>= shift; r |= shift;
  shift = (v > 0x3   ) << 1; v >>>= shift; r |= shift;
  return r | (v >> 1);
}

/**
 * Computes log base 10 of v
 *
 * @param {number} v
 * @returns {number}
 */
function log10(v) {
  return  (v >= 1000000000) ? 9 : (v >= 100000000) ? 8 : (v >= 10000000) ? 7 :
          (v >= 1000000) ? 6 : (v >= 100000) ? 5 : (v >= 10000) ? 4 :
          (v >= 1000) ? 3 : (v >= 100) ? 2 : (v >= 10) ? 1 : 0;
}

/**
 * Counts number of bits
 *
 * @param {number} v
 * @returns {number}
 */
function popCount(v) {
  v = v - ((v >>> 1) & 0x55555555);
  v = (v & 0x33333333) + ((v >>> 2) & 0x33333333);
  return ((v + (v >>> 4) & 0xF0F0F0F) * 0x1010101) >>> 24;
}

/**
 * Counts number of trailing zeros
 *
 * @param {number} v
 * @returns {number}
 */
function countTrailingZeros(v) {
  let c = 32;
  v &= -v;
  if (v) c--;
  if (v & 0x0000FFFF) c -= 16;
  if (v & 0x00FF00FF) c -= 8;
  if (v & 0x0F0F0F0F) c -= 4;
  if (v & 0x33333333) c -= 2;
  if (v & 0x55555555) c -= 1;
  return c;
}

/**
 * Rounds to next power of 2
 *
 * @param {number} v
 * @returns {number}
 */
function nextPow2$1(v) {
  v += v === 0;
  --v;
  v |= v >>> 1;
  v |= v >>> 2;
  v |= v >>> 4;
  v |= v >>> 8;
  v |= v >>> 16;
  return v + 1;
}

/**
 * Rounds down to previous power of 2
 *
 * @param {number} v
 * @returns {number}
 */
function prevPow2(v) {
  v |= v >>> 1;
  v |= v >>> 2;
  v |= v >>> 4;
  v |= v >>> 8;
  v |= v >>> 16;
  return v - (v>>>1);
}

/**
 * Computes parity of word
 *
 * @param {number} v
 * @returns {number}
 */
function parity(v) {
  v ^= v >>> 16;
  v ^= v >>> 8;
  v ^= v >>> 4;
  v &= 0xf;
  return (0x6996 >>> v) & 1;
}

const REVERSE_TABLE = new Array(256);

(function(tab) {
  for(let i=0; i<256; ++i) {
    let v = i, r = i, s = 7;
    for (v >>>= 1; v; v >>>= 1) {
      r <<= 1;
      r |= v & 1;
      --s;
    }
    tab[i] = (r << s) & 0xff;
  }
})(REVERSE_TABLE);

/**
 * Reverse bits in a 32 bit word
 *
 * @param {number} v
 * @returns {number}
 */
function reverse(v) {
  return (REVERSE_TABLE[v & 0xff] << 24) |
         (REVERSE_TABLE[(v >>> 8) & 0xff] << 16) |
         (REVERSE_TABLE[(v >>> 16) & 0xff] << 8) |
         REVERSE_TABLE[(v >>> 24) & 0xff];
}

/**
 * Interleave bits of 2 coordinates with 16 bits. Useful for fast quadtree codes
 *
 * @param {number} x
 * @param {number} y
 * @returns {number}
 */
function interleave2(x, y) {
  x &= 0xFFFF;
  x = (x | (x << 8)) & 0x00FF00FF;
  x = (x | (x << 4)) & 0x0F0F0F0F;
  x = (x | (x << 2)) & 0x33333333;
  x = (x | (x << 1)) & 0x55555555;

  y &= 0xFFFF;
  y = (y | (y << 8)) & 0x00FF00FF;
  y = (y | (y << 4)) & 0x0F0F0F0F;
  y = (y | (y << 2)) & 0x33333333;
  y = (y | (y << 1)) & 0x55555555;

  return x | (y << 1);
}

/**
 * Extracts the nth interleaved component
 *
 * @param {number} v
 * @param {number} n
 * @returns {number}
 */
function deinterleave2(v, n) {
  v = (v >>> n) & 0x55555555;
  v = (v | (v >>> 1))  & 0x33333333;
  v = (v | (v >>> 2))  & 0x0F0F0F0F;
  v = (v | (v >>> 4))  & 0x00FF00FF;
  v = (v | (v >>> 16)) & 0x000FFFF;
  return (v << 16) >> 16;
}

/**
 * Interleave bits of 3 coordinates, each with 10 bits.  Useful for fast octree codes
 *
 * @param {number} x
 * @param {number} y
 * @param {number} z
 * @returns {number}
 */
function interleave3(x, y, z) {
  x &= 0x3FF;
  x  = (x | (x<<16)) & 4278190335;
  x  = (x | (x<<8))  & 251719695;
  x  = (x | (x<<4))  & 3272356035;
  x  = (x | (x<<2))  & 1227133513;

  y &= 0x3FF;
  y  = (y | (y<<16)) & 4278190335;
  y  = (y | (y<<8))  & 251719695;
  y  = (y | (y<<4))  & 3272356035;
  y  = (y | (y<<2))  & 1227133513;
  x |= (y << 1);

  z &= 0x3FF;
  z  = (z | (z<<16)) & 4278190335;
  z  = (z | (z<<8))  & 251719695;
  z  = (z | (z<<4))  & 3272356035;
  z  = (z | (z<<2))  & 1227133513;

  return x | (z << 2);
}

/**
 * Extracts nth interleaved component of a 3-tuple
 *
 * @param {number} v
 * @param {number} n
 * @returns {number}
 */
function deinterleave3(v, n) {
  v = (v >>> n)       & 1227133513;
  v = (v | (v>>>2))   & 3272356035;
  v = (v | (v>>>4))   & 251719695;
  v = (v | (v>>>8))   & 4278190335;
  v = (v | (v>>>16))  & 0x3FF;
  return (v<<22)>>22;
}

/**
 * Computes next combination in colexicographic order (this is mistakenly called nextPermutation on the bit twiddling hacks page)
 *
 * @param {number} v
 * @returns {number}
 */
function nextCombination(v) {
  let t = v | (v - 1);
  return (t + 1) | (((~t & -~t) - 1) >>> (countTrailingZeros(v) + 1));
}

var bits_ = Object.freeze({
	INT_BITS: INT_BITS,
	INT_MAX: INT_MAX,
	INT_MIN: INT_MIN,
	sign: sign,
	abs: abs,
	min: min,
	max: max,
	isPow2: isPow2,
	log2: log2,
	log10: log10,
	popCount: popCount,
	countTrailingZeros: countTrailingZeros,
	nextPow2: nextPow2$1,
	prevPow2: prevPow2,
	parity: parity,
	reverse: reverse,
	interleave2: interleave2,
	deinterleave2: deinterleave2,
	interleave3: interleave3,
	deinterleave3: deinterleave3,
	nextCombination: nextCombination
});

let _tmp = new Array(2);

class _vec2 {
  constructor(x, y) {
    this.x = x;
    this.y = y;
  }

  toJSON() {
    _tmp[0] = this.x;
    _tmp[1] = this.y;

    return _tmp;
  }
}

/**
 * @class 2 Dimensional Vector
 * @name vec2
 */
let vec2 = {};

/**
 * Creates a new, empty vec2
 *
 * @returns {vec2} a new 2D vector
 */
vec2.create = function () {
  return new _vec2(0, 0);
};

/**
 * Creates a new vec2 initialized with the given values
 *
 * @param {Number} x X component
 * @param {Number} y Y component
 * @returns {vec2} a new 2D vector
 */
vec2.new = function (x, y) {
  return new _vec2(x, y);
};

/**
 * Creates a new vec2 initialized with values from an existing vector
 *
 * @param {vec2} a vector to clone
 * @returns {vec2} a new 2D vector
 */
vec2.clone = function (a) {
  return new _vec2(a.x, a.y);
};

/**
 * Copy the values from one vec2 to another
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a the source vector
 * @returns {vec2} out
 */
vec2.copy = function (out, a) {
  out.x = a.x;
  out.y = a.y;
  return out;
};

/**
 * Set the components of a vec2 to the given values
 *
 * @param {vec2} out the receiving vector
 * @param {Number} x X component
 * @param {Number} y Y component
 * @returns {vec2} out
 */
vec2.set = function (out, x, y) {
  out.x = x;
  out.y = y;
  return out;
};

/**
 * Adds two vec2's
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a the first operand
 * @param {vec2} b the second operand
 * @returns {vec2} out
 */
vec2.add = function (out, a, b) {
  out.x = a.x + b.x;
  out.y = a.y + b.y;
  return out;
};

/**
 * Subtracts vector b from vector a
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a the first operand
 * @param {vec2} b the second operand
 * @returns {vec2} out
 */
vec2.subtract = function (out, a, b) {
  out.x = a.x - b.x;
  out.y = a.y - b.y;
  return out;
};

/**
 * Alias for {@link vec2.subtract}
 * @function
 */
vec2.sub = vec2.subtract;

/**
 * Multiplies two vec2's
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a the first operand
 * @param {vec2} b the second operand
 * @returns {vec2} out
 */
vec2.multiply = function (out, a, b) {
  out.x = a.x * b.x;
  out.y = a.y * b.y;
  return out;
};

/**
 * Alias for {@link vec2.multiply}
 * @function
 */
vec2.mul = vec2.multiply;

/**
 * Divides two vec2's
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a the first operand
 * @param {vec2} b the second operand
 * @returns {vec2} out
 */
vec2.divide = function (out, a, b) {
  out.x = a.x / b.x;
  out.y = a.y / b.y;
  return out;
};

/**
 * Alias for {@link vec2.divide}
 * @function
 */
vec2.div = vec2.divide;

/**
 * Math.ceil the components of a vec2
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a vector to ceil
 * @returns {vec2} out
 */
vec2.ceil = function (out, a) {
  out.x = Math.ceil(a.x);
  out.y = Math.ceil(a.y);
  return out;
};

/**
 * Math.floor the components of a vec2
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a vector to floor
 * @returns {vec2} out
 */
vec2.floor = function (out, a) {
  out.x = Math.floor(a.x);
  out.y = Math.floor(a.y);
  return out;
};

/**
 * Returns the minimum of two vec2's
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a the first operand
 * @param {vec2} b the second operand
 * @returns {vec2} out
 */
vec2.min = function (out, a, b) {
  out.x = Math.min(a.x, b.x);
  out.y = Math.min(a.y, b.y);
  return out;
};

/**
 * Returns the maximum of two vec2's
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a the first operand
 * @param {vec2} b the second operand
 * @returns {vec2} out
 */
vec2.max = function (out, a, b) {
  out.x = Math.max(a.x, b.x);
  out.y = Math.max(a.y, b.y);
  return out;
};

/**
 * Math.round the components of a vec2
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a vector to round
 * @returns {vec2} out
 */
vec2.round = function (out, a) {
  out.x = Math.round(a.x);
  out.y = Math.round(a.y);
  return out;
};

/**
 * Scales a vec2 by a scalar number
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a the vector to scale
 * @param {Number} b amount to scale the vector by
 * @returns {vec2} out
 */
vec2.scale = function (out, a, b) {
  out.x = a.x * b;
  out.y = a.y * b;
  return out;
};

/**
 * Adds two vec2's after scaling the second operand by a scalar value
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a the first operand
 * @param {vec2} b the second operand
 * @param {Number} scale the amount to scale b by before adding
 * @returns {vec2} out
 */
vec2.scaleAndAdd = function (out, a, b, scale) {
  out.x = a.x + (b.x * scale);
  out.y = a.y + (b.y * scale);
  return out;
};

/**
 * Calculates the euclidian distance between two vec2's
 *
 * @param {vec2} a the first operand
 * @param {vec2} b the second operand
 * @returns {Number} distance between a and b
 */
vec2.distance = function (a, b) {
  let x = b.x - a.x,
      y = b.y - a.y;
  return Math.sqrt(x * x + y * y);
};

/**
 * Alias for {@link vec2.distance}
 * @function
 */
vec2.dist = vec2.distance;

/**
 * Calculates the squared euclidian distance between two vec2's
 *
 * @param {vec2} a the first operand
 * @param {vec2} b the second operand
 * @returns {Number} squared distance between a and b
 */
vec2.squaredDistance = function (a, b) {
  let x = b.x - a.x,
      y = b.y - a.y;
  return x * x + y * y;
};

/**
 * Alias for {@link vec2.squaredDistance}
 * @function
 */
vec2.sqrDist = vec2.squaredDistance;

/**
 * Calculates the length of a vec2
 *
 * @param {vec2} a vector to calculate length of
 * @returns {Number} length of a
 */
vec2.length = function (a) {
  let x = a.x,
      y = a.y;
  return Math.sqrt(x * x + y * y);
};

/**
 * Alias for {@link vec2.length}
 * @function
 */
vec2.len = vec2.length;

/**
 * Calculates the squared length of a vec2
 *
 * @param {vec2} a vector to calculate squared length of
 * @returns {Number} squared length of a
 */
vec2.squaredLength = function (a) {
  let x = a.x,
      y = a.y;
  return x * x + y * y;
};

/**
 * Alias for {@link vec2.squaredLength}
 * @function
 */
vec2.sqrLen = vec2.squaredLength;

/**
 * Negates the components of a vec2
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a vector to negate
 * @returns {vec2} out
 */
vec2.negate = function (out, a) {
  out.x = -a.x;
  out.y = -a.y;
  return out;
};

/**
 * Returns the inverse of the components of a vec2
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a vector to invert
 * @returns {vec2} out
 */
vec2.inverse = function (out, a) {
  out.x = 1.0 / a.x;
  out.y = 1.0 / a.y;
  return out;
};

/**
 * Returns the inverse of the components of a vec2 safely
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a vector to invert
 * @returns {vec2} out
 */
vec2.inverseSafe = function (out, a) {
  let x = a.x,
      y = a.y;

  if (Math.abs(x) < EPSILON) {
    out.x = 0;
  } else {
    out.x = 1.0 / x;
  }

  if (Math.abs(y) < EPSILON) {
    out.y = 0;
  } else {
    out.y = 1.0 / a.y;
  }

  return out;
};

/**
 * Normalize a vec2
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a vector to normalize
 * @returns {vec2} out
 */
vec2.normalize = function (out, a) {
  let x = a.x,
      y = a.y;
  let len = x * x + y * y;
  if (len > 0) {
    //TODO: evaluate use of glm_invsqrt here?
    len = 1 / Math.sqrt(len);
    out.x = a.x * len;
    out.y = a.y * len;
  }
  return out;
};

/**
 * Calculates the dot product of two vec2's
 *
 * @param {vec2} a the first operand
 * @param {vec2} b the second operand
 * @returns {Number} dot product of a and b
 */
vec2.dot = function (a, b) {
  return a.x * b.x + a.y * b.y;
};

/**
 * Computes the cross product of two vec2's
 * Note that the cross product must by definition produce a 3D vector
 *
 * @param {vec3} out the receiving vector
 * @param {vec2} a the first operand
 * @param {vec2} b the second operand
 * @returns {vec3} out
 */
vec2.cross = function (out, a, b) {
  let z = a.x * b.y - a.y * b.x;
  out.x = out.y = 0;
  out.z = z;
  return out;
};

/**
 * Performs a linear interpolation between two vec2's
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a the first operand
 * @param {vec2} b the second operand
 * @param {Number} t interpolation amount between the two inputs
 * @returns {vec2} out
 */
vec2.lerp = function (out, a, b, t) {
  let ax = a.x,
      ay = a.y;
  out.x = ax + t * (b.x - ax);
  out.y = ay + t * (b.y - ay);
  return out;
};

/**
 * Generates a random vector with the given scale
 *
 * @param {vec2} out the receiving vector
 * @param {Number} [scale] Length of the resulting vector. If ommitted, a unit vector will be returned
 * @returns {vec2} out
 */
vec2.random = function (out, scale) {
  scale = scale || 1.0;
  let r = random() * 2.0 * Math.PI;
  out.x = Math.cos(r) * scale;
  out.y = Math.sin(r) * scale;
  return out;
};

/**
 * Transforms the vec2 with a mat2
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a the vector to transform
 * @param {mat2} m matrix to transform with
 * @returns {vec2} out
 */
vec2.transformMat2 = function (out, a, m) {
  let x = a.x,
      y = a.y;
  out.x = m.m00 * x + m.m02 * y;
  out.y = m.m01 * x + m.m03 * y;
  return out;
};

/**
 * Transforms the vec2 with a mat23
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a the vector to transform
 * @param {mat23} m matrix to transform with
 * @returns {vec2} out
 */
vec2.transformMat23 = function (out, a, m) {
  let x = a.x,
      y = a.y;
  out.x = m.m00 * x + m.m02 * y + m.m04;
  out.y = m.m01 * x + m.m03 * y + m.m05;
  return out;
};

/**
 * Transforms the vec2 with a mat3
 * 3rd vector component is implicitly '1'
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a the vector to transform
 * @param {mat3} m matrix to transform with
 * @returns {vec2} out
 */
vec2.transformMat3 = function (out, a, m) {
  let x = a.x,
      y = a.y;
  out.x = m.m00 * x + m.m03 * y + m.m06;
  out.y = m.m01 * x + m.m04 * y + m.m07;
  return out;
};

/**
 * Transforms the vec2 with a mat4
 * 3rd vector component is implicitly '0'
 * 4th vector component is implicitly '1'
 *
 * @param {vec2} out the receiving vector
 * @param {vec2} a the vector to transform
 * @param {mat4} m matrix to transform with
 * @returns {vec2} out
 */
vec2.transformMat4 = function (out, a, m) {
  let x = a.x,
      y = a.y;
  out.x = m.m00 * x + m.m04 * y + m.m12;
  out.y = m.m01 * x + m.m05 * y + m.m13;
  return out;
};

/**
 * Perform some operation over an array of vec2s.
 *
 * @param {Array} a the array of vectors to iterate over
 * @param {Number} stride Number of elements between the start of each vec2. If 0 assumes tightly packed
 * @param {Number} offset Number of elements to skip at the beginning of the array
 * @param {Number} count Number of vec2s to iterate over. If 0 iterates over entire array
 * @param {Function} fn Function to call for each vector in the array
 * @param {Object} [arg] additional argument to pass to fn
 * @returns {Array} a
 * @function
 */
vec2.forEach = (function () {
  let vec = vec2.create();

  return function (a, stride, offset, count, fn, arg) {
    let i, l;
    if (!stride) {
      stride = 2;
    }

    if (!offset) {
      offset = 0;
    }

    if (count) {
      l = Math.min((count * stride) + offset, a.length);
    } else {
      l = a.length;
    }

    for (i = offset; i < l; i += stride) {
      vec.x = a[i]; vec.y = a[i + 1];
      fn(vec, vec, arg);
      a[i] = vec.x; a[i + 1] = vec.y;
    }

    return a;
  };
})();

/**
 * Returns a string representation of a vector
 *
 * @param {vec2} a vector to represent as a string
 * @returns {String} string representation of the vector
 */
vec2.str = function (a) {
  return `vec2(${a.x}, ${a.y})`;
};

/**
 * Returns typed array
 *
 * @param {array} out
 * @param {vec2} v
 * @returns {array}
 */
vec2.array = function (out, v) {
  out[0] = v.x;
  out[1] = v.y;

  return out;
};

/**
 * Returns whether or not the vectors exactly have the same elements in the same position (when compared with ===)
 *
 * @param {vec2} a The first vector.
 * @param {vec2} b The second vector.
 * @returns {Boolean} True if the vectors are equal, false otherwise.
 */
vec2.exactEquals = function (a, b) {
  return a.x === b.x && a.y === b.y;
};

/**
 * Returns whether or not the vectors have approximately the same elements in the same position.
 *
 * @param {vec2} a The first vector.
 * @param {vec2} b The second vector.
 * @returns {Boolean} True if the vectors are equal, false otherwise.
 */
vec2.equals = function (a, b) {
  let a0 = a.x, a1 = a.y;
  let b0 = b.x, b1 = b.y;
  return (Math.abs(a0 - b0) <= EPSILON * Math.max(1.0, Math.abs(a0), Math.abs(b0)) &&
    Math.abs(a1 - b1) <= EPSILON * Math.max(1.0, Math.abs(a1), Math.abs(b1)));
};

let _tmp$1 = new Array(3);

class _vec3 {
  constructor(x, y, z) {
    this.x = x;
    this.y = y;
    this.z = z;
  }

  toJSON() {
    _tmp$1[0] = this.x;
    _tmp$1[1] = this.y;
    _tmp$1[2] = this.z;

    return _tmp$1;
  }
}

/**
 * @class 3 Dimensional Vector
 * @name vec3
 */
let vec3 = {};

/**
 * Creates a new, empty vec3
 *
 * @returns {vec3} a new 3D vector
 */
vec3.create = function () {
  return new _vec3(0, 0, 0);
};

/**
 * Creates a new vec3 initialized with the given values
 *
 * @param {Number} x X component
 * @param {Number} y Y component
 * @param {Number} z Z component
 * @returns {vec3} a new 3D vector
 */
vec3.new = function (x, y, z) {
  return new _vec3(x, y, z);
};

/**
 * Creates a new vec3 initialized with values from an existing vector
 *
 * @param {vec3} a vector to clone
 * @returns {vec3} a new 3D vector
 */
vec3.clone = function (a) {
  return new _vec3(a.x, a.y, a.z);
};

/**
 * Copy the values from one vec3 to another
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the source vector
 * @returns {vec3} out
 */
vec3.copy = function (out, a) {
  out.x = a.x;
  out.y = a.y;
  out.z = a.z;
  return out;
};

/**
 * Set the components of a vec3 to the given values
 *
 * @param {vec3} out the receiving vector
 * @param {Number} x X component
 * @param {Number} y Y component
 * @param {Number} z Z component
 * @returns {vec3} out
 */
vec3.set = function (out, x, y, z) {
  out.x = x;
  out.y = y;
  out.z = z;
  return out;
};

/**
 * Adds two vec3's
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @returns {vec3} out
 */
vec3.add = function (out, a, b) {
  out.x = a.x + b.x;
  out.y = a.y + b.y;
  out.z = a.z + b.z;
  return out;
};

/**
 * Subtracts vector b from vector a
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @returns {vec3} out
 */
vec3.subtract = function (out, a, b) {
  out.x = a.x - b.x;
  out.y = a.y - b.y;
  out.z = a.z - b.z;
  return out;
};

/**
 * Alias for {@link vec3.subtract}
 * @function
 */
vec3.sub = vec3.subtract;

/**
 * Multiplies two vec3's
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @returns {vec3} out
 */
vec3.multiply = function (out, a, b) {
  out.x = a.x * b.x;
  out.y = a.y * b.y;
  out.z = a.z * b.z;
  return out;
};

/**
 * Alias for {@link vec3.multiply}
 * @function
 */
vec3.mul = vec3.multiply;

/**
 * Divides two vec3's
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @returns {vec3} out
 */
vec3.divide = function (out, a, b) {
  out.x = a.x / b.x;
  out.y = a.y / b.y;
  out.z = a.z / b.z;
  return out;
};

/**
 * Alias for {@link vec3.divide}
 * @function
 */
vec3.div = vec3.divide;

/**
 * Math.ceil the components of a vec3
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a vector to ceil
 * @returns {vec3} out
 */
vec3.ceil = function (out, a) {
  out.x = Math.ceil(a.x);
  out.y = Math.ceil(a.y);
  out.z = Math.ceil(a.z);
  return out;
};

/**
 * Math.floor the components of a vec3
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a vector to floor
 * @returns {vec3} out
 */
vec3.floor = function (out, a) {
  out.x = Math.floor(a.x);
  out.y = Math.floor(a.y);
  out.z = Math.floor(a.z);
  return out;
};

/**
 * Returns the minimum of two vec3's
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @returns {vec3} out
 */
vec3.min = function (out, a, b) {
  out.x = Math.min(a.x, b.x);
  out.y = Math.min(a.y, b.y);
  out.z = Math.min(a.z, b.z);
  return out;
};

/**
 * Returns the maximum of two vec3's
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @returns {vec3} out
 */
vec3.max = function (out, a, b) {
  out.x = Math.max(a.x, b.x);
  out.y = Math.max(a.y, b.y);
  out.z = Math.max(a.z, b.z);
  return out;
};

/**
 * Math.round the components of a vec3
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a vector to round
 * @returns {vec3} out
 */
vec3.round = function (out, a) {
  out.x = Math.round(a.x);
  out.y = Math.round(a.y);
  out.z = Math.round(a.z);
  return out;
};

/**
 * Scales a vec3 by a scalar number
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the vector to scale
 * @param {Number} b amount to scale the vector by
 * @returns {vec3} out
 */
vec3.scale = function (out, a, b) {
  out.x = a.x * b;
  out.y = a.y * b;
  out.z = a.z * b;
  return out;
};

/**
 * Adds two vec3's after scaling the second operand by a scalar value
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @param {Number} scale the amount to scale b by before adding
 * @returns {vec3} out
 */
vec3.scaleAndAdd = function (out, a, b, scale) {
  out.x = a.x + (b.x * scale);
  out.y = a.y + (b.y * scale);
  out.z = a.z + (b.z * scale);
  return out;
};

/**
 * Calculates the euclidian distance between two vec3's
 *
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @returns {Number} distance between a and b
 */
vec3.distance = function (a, b) {
  let x = b.x - a.x,
    y = b.y - a.y,
    z = b.z - a.z;
  return Math.sqrt(x * x + y * y + z * z);
};

/**
 * Alias for {@link vec3.distance}
 * @function
 */
vec3.dist = vec3.distance;

/**
 * Calculates the squared euclidian distance between two vec3's
 *
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @returns {Number} squared distance between a and b
 */
vec3.squaredDistance = function (a, b) {
  let x = b.x - a.x,
      y = b.y - a.y,
      z = b.z - a.z;
  return x * x + y * y + z * z;
};

/**
 * Alias for {@link vec3.squaredDistance}
 * @function
 */
vec3.sqrDist = vec3.squaredDistance;

/**
 * Calculates the length of a vec3
 *
 * @param {vec3} a vector to calculate length of
 * @returns {Number} length of a
 */
vec3.length = function (a) {
  let x = a.x,
      y = a.y,
      z = a.z;
  return Math.sqrt(x * x + y * y + z * z);
};

/**
 * Alias for {@link vec3.length}
 * @function
 */
vec3.len = vec3.length;

/**
 * Calculates the squared length of a vec3
 *
 * @param {vec3} a vector to calculate squared length of
 * @returns {Number} squared length of a
 */
vec3.squaredLength = function (a) {
  let x = a.x,
      y = a.y,
      z = a.z;
  return x * x + y * y + z * z;
};

/**
 * Alias for {@link vec3.squaredLength}
 * @function
 */
vec3.sqrLen = vec3.squaredLength;

/**
 * Negates the components of a vec3
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a vector to negate
 * @returns {vec3} out
 */
vec3.negate = function (out, a) {
  out.x = -a.x;
  out.y = -a.y;
  out.z = -a.z;
  return out;
};

/**
 * Returns the inverse of the components of a vec3
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a vector to invert
 * @returns {vec3} out
 */
vec3.inverse = function (out, a) {
  out.x = 1.0 / a.x;
  out.y = 1.0 / a.y;
  out.z = 1.0 / a.z;
  return out;
};

/**
 * Returns the inverse of the components of a vec3 safely
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a vector to invert
 * @returns {vec3} out
 */
vec3.inverseSafe = function (out, a) {
  let x = a.x,
      y = a.y,
      z = a.z;

  if (Math.abs(x) < EPSILON) {
    out.x = 0;
  } else {
    out.x = 1.0 / x;
  }

  if (Math.abs(y) < EPSILON) {
    out.y = 0;
  } else {
    out.y = 1.0 / y;
  }

  if (Math.abs(z) < EPSILON) {
    out.z = 0;
  } else {
    out.z = 1.0 / z;
  }

  return out;
};

/**
 * Normalize a vec3
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a vector to normalize
 * @returns {vec3} out
 */
vec3.normalize = function (out, a) {
  let x = a.x,
      y = a.y,
      z = a.z;

  let len = x * x + y * y + z * z;
  if (len > 0) {
    //TODO: evaluate use of glm_invsqrt here?
    len = 1 / Math.sqrt(len);
    out.x = x * len;
    out.y = y * len;
    out.z = z * len;
  }
  return out;
};

/**
 * Calculates the dot product of two vec3's
 *
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @returns {Number} dot product of a and b
 */
vec3.dot = function (a, b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
};

/**
 * Computes the cross product of two vec3's
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @returns {vec3} out
 */
vec3.cross = function (out, a, b) {
  let ax = a.x, ay = a.y, az = a.z,
      bx = b.x, by = b.y, bz = b.z;

  out.x = ay * bz - az * by;
  out.y = az * bx - ax * bz;
  out.z = ax * by - ay * bx;
  return out;
};

/**
 * Performs a linear interpolation between two vec3's
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @param {Number} t interpolation amount between the two inputs
 * @returns {vec3} out
 */
vec3.lerp = function (out, a, b, t) {
  let ax = a.x,
      ay = a.y,
      az = a.z;
  out.x = ax + t * (b.x - ax);
  out.y = ay + t * (b.y - ay);
  out.z = az + t * (b.z - az);
  return out;
};

/**
 * Performs a hermite interpolation with two control points
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @param {vec3} c the third operand
 * @param {vec3} d the fourth operand
 * @param {Number} t interpolation amount between the two inputs
 * @returns {vec3} out
 */
vec3.hermite = function (out, a, b, c, d, t) {
  let factorTimes2 = t * t,
      factor1 = factorTimes2 * (2 * t - 3) + 1,
      factor2 = factorTimes2 * (t - 2) + t,
      factor3 = factorTimes2 * (t - 1),
      factor4 = factorTimes2 * (3 - 2 * t);

  out.x = a.x * factor1 + b.x * factor2 + c.x * factor3 + d.x * factor4;
  out.y = a.y * factor1 + b.y * factor2 + c.y * factor3 + d.y * factor4;
  out.z = a.z * factor1 + b.z * factor2 + c.z * factor3 + d.z * factor4;

  return out;
};

/**
 * Performs a bezier interpolation with two control points
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the first operand
 * @param {vec3} b the second operand
 * @param {vec3} c the third operand
 * @param {vec3} d the fourth operand
 * @param {Number} t interpolation amount between the two inputs
 * @returns {vec3} out
 */
vec3.bezier = function (out, a, b, c, d, t) {
  let inverseFactor = 1 - t,
      inverseFactorTimesTwo = inverseFactor * inverseFactor,
      factorTimes2 = t * t,
      factor1 = inverseFactorTimesTwo * inverseFactor,
      factor2 = 3 * t * inverseFactorTimesTwo,
      factor3 = 3 * factorTimes2 * inverseFactor,
      factor4 = factorTimes2 * t;

  out.x = a.x * factor1 + b.x * factor2 + c.x * factor3 + d.x * factor4;
  out.y = a.y * factor1 + b.y * factor2 + c.y * factor3 + d.y * factor4;
  out.z = a.z * factor1 + b.z * factor2 + c.z * factor3 + d.z * factor4;

  return out;
};

/**
 * Generates a random vector with the given scale
 *
 * @param {vec3} out the receiving vector
 * @param {Number} [scale] Length of the resulting vector. If ommitted, a unit vector will be returned
 * @returns {vec3} out
 */
vec3.random = function (out, scale) {
  scale = scale || 1.0;

  let r = random() * 2.0 * Math.PI;
  let z = (random() * 2.0) - 1.0;
  let zScale = Math.sqrt(1.0 - z * z) * scale;

  out.x = Math.cos(r) * zScale;
  out.y = Math.sin(r) * zScale;
  out.z = z * scale;
  return out;
};

/**
 * Transforms the vec3 with a mat4.
 * 4th vector component is implicitly '1'
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the vector to transform
 * @param {mat4} m matrix to transform with
 * @returns {vec3} out
 */
vec3.transformMat4 = function (out, a, m) {
  let x = a.x, y = a.y, z = a.z,
      w = m.m03 * x + m.m07 * y + m.m11 * z + m.m15;
  w = w || 1.0;
  out.x = (m.m00 * x + m.m04 * y + m.m08 * z + m.m12) / w;
  out.y = (m.m01 * x + m.m05 * y + m.m09 * z + m.m13) / w;
  out.z = (m.m02 * x + m.m06 * y + m.m10 * z + m.m14) / w;
  return out;
};

/**
 * Transforms the vec3 with a mat3.
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the vector to transform
 * @param {mat4} m the 3x3 matrix to transform with
 * @returns {vec3} out
 */
vec3.transformMat3 = function (out, a, m) {
  let x = a.x, y = a.y, z = a.z;
  out.x = x * m.m00 + y * m.m03 + z * m.m06;
  out.y = x * m.m01 + y * m.m04 + z * m.m07;
  out.z = x * m.m02 + y * m.m05 + z * m.m08;
  return out;
};

/**
 * Transforms the vec3 with a quat
 *
 * @param {vec3} out the receiving vector
 * @param {vec3} a the vector to transform
 * @param {quat} q quaternion to transform with
 * @returns {vec3} out
 */
vec3.transformQuat = function (out, a, q) {
  // benchmarks: http://jsperf.com/quaternion-transform-vec3-implementations

  let x = a.x, y = a.y, z = a.z;
  let qx = q.x, qy = q.y, qz = q.z, qw = q.w;

  // calculate quat * vec
  let ix = qw * x + qy * z - qz * y;
  let iy = qw * y + qz * x - qx * z;
  let iz = qw * z + qx * y - qy * x;
  let iw = -qx * x - qy * y - qz * z;

  // calculate result * inverse quat
  out.x = ix * qw + iw * -qx + iy * -qz - iz * -qy;
  out.y = iy * qw + iw * -qy + iz * -qx - ix * -qz;
  out.z = iz * qw + iw * -qz + ix * -qy - iy * -qx;
  return out;
};

/**
 * Rotate a 3D vector around the x-axis
 * @param {vec3} out The receiving vec3
 * @param {vec3} a The vec3 point to rotate
 * @param {vec3} b The origin of the rotation
 * @param {Number} c The angle of rotation
 * @returns {vec3} out
 */
vec3.rotateX = function (out, a, b, c) {
  let p = [], r = [];
  // Translate point to the origin
  p.x = a.x - b.x;
  p.y = a.y - b.y;
  p.z = a.z - b.z;

  //perform rotation
  r.x = p.x;
  r.y = p.y * Math.cos(c) - p.z * Math.sin(c);
  r.z = p.y * Math.sin(c) + p.z * Math.cos(c);

  //translate to correct position
  out.x = r.x + b.x;
  out.y = r.y + b.y;
  out.z = r.z + b.z;

  return out;
};

/**
 * Rotate a 3D vector around the y-axis
 * @param {vec3} out The receiving vec3
 * @param {vec3} a The vec3 point to rotate
 * @param {vec3} b The origin of the rotation
 * @param {Number} c The angle of rotation
 * @returns {vec3} out
 */
vec3.rotateY = function (out, a, b, c) {
  let p = [], r = [];
  //Translate point to the origin
  p.x = a.x - b.x;
  p.y = a.y - b.y;
  p.z = a.z - b.z;

  //perform rotation
  r.x = p.z * Math.sin(c) + p.x * Math.cos(c);
  r.y = p.y;
  r.z = p.z * Math.cos(c) - p.x * Math.sin(c);

  //translate to correct position
  out.x = r.x + b.x;
  out.y = r.y + b.y;
  out.z = r.z + b.z;

  return out;
};

/**
 * Rotate a 3D vector around the z-axis
 * @param {vec3} out The receiving vec3
 * @param {vec3} a The vec3 point to rotate
 * @param {vec3} b The origin of the rotation
 * @param {Number} c The angle of rotation
 * @returns {vec3} out
 */
vec3.rotateZ = function (out, a, b, c) {
  let p = [], r = [];
  //Translate point to the origin
  p.x = a.x - b.x;
  p.y = a.y - b.y;
  p.z = a.z - b.z;

  //perform rotation
  r.x = p.x * Math.cos(c) - p.y * Math.sin(c);
  r.y = p.x * Math.sin(c) + p.y * Math.cos(c);
  r.z = p.z;

  //translate to correct position
  out.x = r.x + b.x;
  out.y = r.y + b.y;
  out.z = r.z + b.z;

  return out;
};

/**
 * Perform some operation over an array of vec3s.
 *
 * @param {Array} a the array of vectors to iterate over
 * @param {Number} stride Number of elements between the start of each vec3. If 0 assumes tightly packed
 * @param {Number} offset Number of elements to skip at the beginning of the array
 * @param {Number} count Number of vec3s to iterate over. If 0 iterates over entire array
 * @param {Function} fn Function to call for each vector in the array
 * @param {Object} [arg] additional argument to pass to fn
 * @returns {Array} a
 * @function
 */
vec3.forEach = (function () {
  let vec = vec3.create();

  return function (a, stride, offset, count, fn, arg) {
    let i, l;
    if (!stride) {
      stride = 3;
    }

    if (!offset) {
      offset = 0;
    }

    if (count) {
      l = Math.min((count * stride) + offset, a.length);
    } else {
      l = a.length;
    }

    for (i = offset; i < l; i += stride) {
      vec.x = a[i]; vec.y = a[i + 1]; vec.z = a[i + 2];
      fn(vec, vec, arg);
      a[i] = vec.x; a[i + 1] = vec.y; a[i + 2] = vec.z;
    }

    return a;
  };
})();

/**
 * Get the angle between two 3D vectors
 * @param {vec3} a The first operand
 * @param {vec3} b The second operand
 * @returns {Number} The angle in radians
 */
vec3.angle = (function () {
  let tempA = vec3.create();
  let tempB = vec3.create();

  return function (a, b) {
    vec3.copy(tempA, a);
    vec3.copy(tempB, b);

    vec3.normalize(tempA, tempA);
    vec3.normalize(tempB, tempB);

    let cosine = vec3.dot(tempA, tempB);

    if (cosine > 1.0) {
      return 0;
    }

    if (cosine < -1.0) {
      return Math.PI;
    }

    return Math.acos(cosine);
  };
})();

/**
 * Returns a string representation of a vector
 *
 * @param {vec3} a vector to represent as a string
 * @returns {String} string representation of the vector
 */
vec3.str = function (a) {
  return `vec3(${a.x}, ${a.y}, ${a.z})`;
};

/**
 * Returns typed array
 *
 * @param {array} out
 * @param {vec3} v
 * @returns {array}
 */
vec3.array = function (out, v) {
  out[0] = v.x;
  out[1] = v.y;
  out[2] = v.z;

  return out;
};

/**
 * Returns whether or not the vectors have exactly the same elements in the same position (when compared with ===)
 *
 * @param {vec3} a The first vector.
 * @param {vec3} b The second vector.
 * @returns {Boolean} True if the vectors are equal, false otherwise.
 */
vec3.exactEquals = function (a, b) {
  return a.x === b.x && a.y === b.y && a.z === b.z;
};

/**
 * Returns whether or not the vectors have approximately the same elements in the same position.
 *
 * @param {vec3} a The first vector.
 * @param {vec3} b The second vector.
 * @returns {Boolean} True if the vectors are equal, false otherwise.
 */
vec3.equals = function (a, b) {
  let a0 = a.x, a1 = a.y, a2 = a.z;
  let b0 = b.x, b1 = b.y, b2 = b.z;
  return (Math.abs(a0 - b0) <= EPSILON * Math.max(1.0, Math.abs(a0), Math.abs(b0)) &&
    Math.abs(a1 - b1) <= EPSILON * Math.max(1.0, Math.abs(a1), Math.abs(b1)) &&
    Math.abs(a2 - b2) <= EPSILON * Math.max(1.0, Math.abs(a2), Math.abs(b2)));
};

let _tmp$2 = new Array(4);

class _vec4 {
  constructor(x, y, z, w) {
    this.x = x;
    this.y = y;
    this.z = z;
    this.w = w;
  }

  toJSON() {
    _tmp$2[0] = this.x;
    _tmp$2[1] = this.y;
    _tmp$2[2] = this.z;
    _tmp$2[3] = this.w;

    return _tmp$2;
  }
}

/**
 * @class 4 Dimensional Vector
 * @name vec4
 */
let vec4 = {};

/**
 * Creates a new, empty vec4
 *
 * @returns {vec4} a new 4D vector
 */
vec4.create = function () {
  return new _vec4(0, 0, 0, 0);
};

/**
 * Creates a new vec4 initialized with the given values
 *
 * @param {Number} x X component
 * @param {Number} y Y component
 * @param {Number} z Z component
 * @param {Number} w W component
 * @returns {vec4} a new 4D vector
 */
vec4.new = function (x, y, z, w) {
  return new _vec4(x, y, z, w);
};

/**
 * Creates a new vec4 initialized with values from an existing vector
 *
 * @param {vec4} a vector to clone
 * @returns {vec4} a new 4D vector
 */
vec4.clone = function (a) {
  return new _vec4(a.x, a.y, a.z, a.w);
};

/**
 * Copy the values from one vec4 to another
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a the source vector
 * @returns {vec4} out
 */
vec4.copy = function (out, a) {
  out.x = a.x;
  out.y = a.y;
  out.z = a.z;
  out.w = a.w;
  return out;
};

/**
 * Set the components of a vec4 to the given values
 *
 * @param {vec4} out the receiving vector
 * @param {Number} x X component
 * @param {Number} y Y component
 * @param {Number} z Z component
 * @param {Number} w W component
 * @returns {vec4} out
 */
vec4.set = function (out, x, y, z, w) {
  out.x = x;
  out.y = y;
  out.z = z;
  out.w = w;
  return out;
};

/**
 * Adds two vec4's
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a the first operand
 * @param {vec4} b the second operand
 * @returns {vec4} out
 */
vec4.add = function (out, a, b) {
  out.x = a.x + b.x;
  out.y = a.y + b.y;
  out.z = a.z + b.z;
  out.w = a.w + b.w;
  return out;
};

/**
 * Subtracts vector b from vector a
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a the first operand
 * @param {vec4} b the second operand
 * @returns {vec4} out
 */
vec4.subtract = function (out, a, b) {
  out.x = a.x - b.x;
  out.y = a.y - b.y;
  out.z = a.z - b.z;
  out.w = a.w - b.w;
  return out;
};

/**
 * Alias for {@link vec4.subtract}
 * @function
 */
vec4.sub = vec4.subtract;

/**
 * Multiplies two vec4's
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a the first operand
 * @param {vec4} b the second operand
 * @returns {vec4} out
 */
vec4.multiply = function (out, a, b) {
  out.x = a.x * b.x;
  out.y = a.y * b.y;
  out.z = a.z * b.z;
  out.w = a.w * b.w;
  return out;
};

/**
 * Alias for {@link vec4.multiply}
 * @function
 */
vec4.mul = vec4.multiply;

/**
 * Divides two vec4's
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a the first operand
 * @param {vec4} b the second operand
 * @returns {vec4} out
 */
vec4.divide = function (out, a, b) {
  out.x = a.x / b.x;
  out.y = a.y / b.y;
  out.z = a.z / b.z;
  out.w = a.w / b.w;
  return out;
};

/**
 * Alias for {@link vec4.divide}
 * @function
 */
vec4.div = vec4.divide;

/**
 * Math.ceil the components of a vec4
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a vector to ceil
 * @returns {vec4} out
 */
vec4.ceil = function (out, a) {
  out.x = Math.ceil(a.x);
  out.y = Math.ceil(a.y);
  out.z = Math.ceil(a.z);
  out.w = Math.ceil(a.w);
  return out;
};

/**
 * Math.floor the components of a vec4
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a vector to floor
 * @returns {vec4} out
 */
vec4.floor = function (out, a) {
  out.x = Math.floor(a.x);
  out.y = Math.floor(a.y);
  out.z = Math.floor(a.z);
  out.w = Math.floor(a.w);
  return out;
};

/**
 * Returns the minimum of two vec4's
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a the first operand
 * @param {vec4} b the second operand
 * @returns {vec4} out
 */
vec4.min = function (out, a, b) {
  out.x = Math.min(a.x, b.x);
  out.y = Math.min(a.y, b.y);
  out.z = Math.min(a.z, b.z);
  out.w = Math.min(a.w, b.w);
  return out;
};

/**
 * Returns the maximum of two vec4's
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a the first operand
 * @param {vec4} b the second operand
 * @returns {vec4} out
 */
vec4.max = function (out, a, b) {
  out.x = Math.max(a.x, b.x);
  out.y = Math.max(a.y, b.y);
  out.z = Math.max(a.z, b.z);
  out.w = Math.max(a.w, b.w);
  return out;
};

/**
 * Math.round the components of a vec4
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a vector to round
 * @returns {vec4} out
 */
vec4.round = function (out, a) {
  out.x = Math.round(a.x);
  out.y = Math.round(a.y);
  out.z = Math.round(a.z);
  out.w = Math.round(a.w);
  return out;
};

/**
 * Scales a vec4 by a scalar number
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a the vector to scale
 * @param {Number} b amount to scale the vector by
 * @returns {vec4} out
 */
vec4.scale = function (out, a, b) {
  out.x = a.x * b;
  out.y = a.y * b;
  out.z = a.z * b;
  out.w = a.w * b;
  return out;
};

/**
 * Adds two vec4's after scaling the second operand by a scalar value
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a the first operand
 * @param {vec4} b the second operand
 * @param {Number} scale the amount to scale b by before adding
 * @returns {vec4} out
 */
vec4.scaleAndAdd = function (out, a, b, scale) {
  out.x = a.x + (b.x * scale);
  out.y = a.y + (b.y * scale);
  out.z = a.z + (b.z * scale);
  out.w = a.w + (b.w * scale);
  return out;
};

/**
 * Calculates the euclidian distance between two vec4's
 *
 * @param {vec4} a the first operand
 * @param {vec4} b the second operand
 * @returns {Number} distance between a and b
 */
vec4.distance = function (a, b) {
  let x = b.x - a.x,
    y = b.y - a.y,
    z = b.z - a.z,
    w = b.w - a.w;
  return Math.sqrt(x * x + y * y + z * z + w * w);
};

/**
 * Alias for {@link vec4.distance}
 * @function
 */
vec4.dist = vec4.distance;

/**
 * Calculates the squared euclidian distance between two vec4's
 *
 * @param {vec4} a the first operand
 * @param {vec4} b the second operand
 * @returns {Number} squared distance between a and b
 */
vec4.squaredDistance = function (a, b) {
  let x = b.x - a.x,
      y = b.y - a.y,
      z = b.z - a.z,
      w = b.w - a.w;
  return x * x + y * y + z * z + w * w;
};

/**
 * Alias for {@link vec4.squaredDistance}
 * @function
 */
vec4.sqrDist = vec4.squaredDistance;

/**
 * Calculates the length of a vec4
 *
 * @param {vec4} a vector to calculate length of
 * @returns {Number} length of a
 */
vec4.length = function (a) {
  let x = a.x,
      y = a.y,
      z = a.z,
      w = a.w;
  return Math.sqrt(x * x + y * y + z * z + w * w);
};

/**
 * Alias for {@link vec4.length}
 * @function
 */
vec4.len = vec4.length;

/**
 * Calculates the squared length of a vec4
 *
 * @param {vec4} a vector to calculate squared length of
 * @returns {Number} squared length of a
 */
vec4.squaredLength = function (a) {
  let x = a.x,
      y = a.y,
      z = a.z,
      w = a.w;
  return x * x + y * y + z * z + w * w;
};

/**
 * Alias for {@link vec4.squaredLength}
 * @function
 */
vec4.sqrLen = vec4.squaredLength;

/**
 * Negates the components of a vec4
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a vector to negate
 * @returns {vec4} out
 */
vec4.negate = function (out, a) {
  out.x = -a.x;
  out.y = -a.y;
  out.z = -a.z;
  out.w = -a.w;
  return out;
};

/**
 * Returns the inverse of the components of a vec4
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a vector to invert
 * @returns {vec4} out
 */
vec4.inverse = function (out, a) {
  out.x = 1.0 / a.x;
  out.y = 1.0 / a.y;
  out.z = 1.0 / a.z;
  out.w = 1.0 / a.w;
  return out;
};

/**
 * Returns the inverse of the components of a vec4 safely
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a vector to invert
 * @returns {vec4} out
 */
vec4.inverseSafe = function (out, a) {
  let x = a.x,
      y = a.y,
      z = a.z,
      w = a.w;

  if (Math.abs(x) < EPSILON) {
    out.x = 0;
  } else {
    out.x = 1.0 / x;
  }

  if (Math.abs(y) < EPSILON) {
    out.y = 0;
  } else {
    out.y = 1.0 / y;
  }

  if (Math.abs(z) < EPSILON) {
    out.z = 0;
  } else {
    out.z = 1.0 / z;
  }

  if (Math.abs(w) < EPSILON) {
    out.w = 0;
  } else {
    out.w = 1.0 / w;
  }

  return out;
};

/**
 * Normalize a vec4
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a vector to normalize
 * @returns {vec4} out
 */
vec4.normalize = function (out, a) {
  let x = a.x,
      y = a.y,
      z = a.z,
      w = a.w;
  let len = x * x + y * y + z * z + w * w;
  if (len > 0) {
    len = 1 / Math.sqrt(len);
    out.x = x * len;
    out.y = y * len;
    out.z = z * len;
    out.w = w * len;
  }
  return out;
};

/**
 * Calculates the dot product of two vec4's
 *
 * @param {vec4} a the first operand
 * @param {vec4} b the second operand
 * @returns {Number} dot product of a and b
 */
vec4.dot = function (a, b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
};

/**
 * Performs a linear interpolation between two vec4's
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a the first operand
 * @param {vec4} b the second operand
 * @param {Number} t interpolation amount between the two inputs
 * @returns {vec4} out
 */
vec4.lerp = function (out, a, b, t) {
  let ax = a.x,
      ay = a.y,
      az = a.z,
      aw = a.w;
  out.x = ax + t * (b.x - ax);
  out.y = ay + t * (b.y - ay);
  out.z = az + t * (b.z - az);
  out.w = aw + t * (b.w - aw);
  return out;
};

/**
 * Generates a random vector with the given scale
 *
 * @param {vec4} out the receiving vector
 * @param {Number} [scale] Length of the resulting vector. If ommitted, a unit vector will be returned
 * @returns {vec4} out
 */
vec4.random = function (out, scale) {
  scale = scale || 1.0;

  //TODO: This is a pretty awful way of doing this. Find something better.
  out.x = random();
  out.y = random();
  out.z = random();
  out.w = random();
  vec4.normalize(out, out);
  vec4.scale(out, out, scale);
  return out;
};

/**
 * Transforms the vec4 with a mat4.
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a the vector to transform
 * @param {mat4} m matrix to transform with
 * @returns {vec4} out
 */
vec4.transformMat4 = function (out, a, m) {
  let x = a.x, y = a.y, z = a.z, w = a.w;
  out.x = m.m00 * x + m.m04 * y + m.m08 * z + m.m12 * w;
  out.y = m.m01 * x + m.m05 * y + m.m09 * z + m.m13 * w;
  out.z = m.m02 * x + m.m06 * y + m.m10 * z + m.m14 * w;
  out.w = m.m03 * x + m.m07 * y + m.m11 * z + m.m15 * w;
  return out;
};

/**
 * Transforms the vec4 with a quat
 *
 * @param {vec4} out the receiving vector
 * @param {vec4} a the vector to transform
 * @param {quat} q quaternion to transform with
 * @returns {vec4} out
 */
vec4.transformQuat = function (out, a, q) {
  let x = a.x, y = a.y, z = a.z;
  let qx = q.x, qy = q.y, qz = q.z, qw = q.w;

  // calculate quat * vec
  let ix = qw * x + qy * z - qz * y;
  let iy = qw * y + qz * x - qx * z;
  let iz = qw * z + qx * y - qy * x;
  let iw = -qx * x - qy * y - qz * z;

  // calculate result * inverse quat
  out.x = ix * qw + iw * -qx + iy * -qz - iz * -qy;
  out.y = iy * qw + iw * -qy + iz * -qx - ix * -qz;
  out.z = iz * qw + iw * -qz + ix * -qy - iy * -qx;
  out.w = a.w;
  return out;
};

/**
 * Perform some operation over an array of vec4s.
 *
 * @param {Array} a the array of vectors to iterate over
 * @param {Number} stride Number of elements between the start of each vec4. If 0 assumes tightly packed
 * @param {Number} offset Number of elements to skip at the beginning of the array
 * @param {Number} count Number of vec4s to iterate over. If 0 iterates over entire array
 * @param {Function} fn Function to call for each vector in the array
 * @param {Object} [arg] additional argument to pass to fn
 * @returns {Array} a
 * @function
 */
vec4.forEach = (function () {
  let vec = vec4.create();

  return function (a, stride, offset, count, fn, arg) {
    let i, l;
    if (!stride) {
      stride = 4;
    }

    if (!offset) {
      offset = 0;
    }

    if (count) {
      l = Math.min((count * stride) + offset, a.length);
    } else {
      l = a.length;
    }

    for (i = offset; i < l; i += stride) {
      vec.x = a[i]; vec.y = a[i + 1]; vec.z = a[i + 2]; vec.w = a[i + 3];
      fn(vec, vec, arg);
      a[i] = vec.x; a[i + 1] = vec.y; a[i + 2] = vec.z; a[i + 3] = vec.w;
    }

    return a;
  };
})();

/**
 * Returns a string representation of a vector
 *
 * @param {vec4} a vector to represent as a string
 * @returns {String} string representation of the vector
 */
vec4.str = function (a) {
  return `vec4(${a.x}, ${a.y}, ${a.z}, ${a.w})`;
};

/**
 * Returns typed array
 *
 * @param {array} out
 * @param {vec4} v
 * @returns {array}
 */
vec4.array = function (out, v) {
  out[0] = v.x;
  out[1] = v.y;
  out[2] = v.z;
  out[3] = v.w;

  return out;
};

/**
 * Returns whether or not the vectors have exactly the same elements in the same position (when compared with ===)
 *
 * @param {vec4} a The first vector.
 * @param {vec4} b The second vector.
 * @returns {Boolean} True if the vectors are equal, false otherwise.
 */
vec4.exactEquals = function (a, b) {
  return a.x === b.x && a.y === b.y && a.z === b.z && a.w === b.w;
};

/**
 * Returns whether or not the vectors have approximately the same elements in the same position.
 *
 * @param {vec4} a The first vector.
 * @param {vec4} b The second vector.
 * @returns {Boolean} True if the vectors are equal, false otherwise.
 */
vec4.equals = function (a, b) {
  let a0 = a.x, a1 = a.y, a2 = a.z, a3 = a.w;
  let b0 = b.x, b1 = b.y, b2 = b.z, b3 = b.w;
  return (Math.abs(a0 - b0) <= EPSILON * Math.max(1.0, Math.abs(a0), Math.abs(b0)) &&
    Math.abs(a1 - b1) <= EPSILON * Math.max(1.0, Math.abs(a1), Math.abs(b1)) &&
    Math.abs(a2 - b2) <= EPSILON * Math.max(1.0, Math.abs(a2), Math.abs(b2)) &&
    Math.abs(a3 - b3) <= EPSILON * Math.max(1.0, Math.abs(a3), Math.abs(b3)));
};

let _tmp$4 = new Array(9);

class _mat3 {
  constructor(m00, m01, m02, m03, m04, m05, m06, m07, m08) {
    this.m00 = m00;
    this.m01 = m01;
    this.m02 = m02;
    this.m03 = m03;
    this.m04 = m04;
    this.m05 = m05;
    this.m06 = m06;
    this.m07 = m07;
    this.m08 = m08;
  }

  toJSON() {
    _tmp$4[0] = this.m00;
    _tmp$4[1] = this.m01;
    _tmp$4[2] = this.m02;
    _tmp$4[3] = this.m03;
    _tmp$4[4] = this.m04;
    _tmp$4[5] = this.m05;
    _tmp$4[6] = this.m06;
    _tmp$4[7] = this.m07;
    _tmp$4[8] = this.m08;

    return _tmp$4;
  }
}

/**
 * @class 3x3 Matrix
 * @name mat3
 *
 * NOTE: we use column-major matrix for all matrix calculation.
 *
 * This may lead to some confusion when referencing OpenGL documentation,
 * however, which represents out all matricies in column-major format.
 * This means that while in code a matrix may be typed out as:
 *
 * [1, 0, 0, 0,
 *  0, 1, 0, 0,
 *  0, 0, 1, 0,
 *  x, y, z, 0]
 *
 * The same matrix in the [OpenGL documentation](https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glTranslate.xml)
 * is written as:
 *
 *  1 0 0 x
 *  0 1 0 y
 *  0 0 1 z
 *  0 0 0 0
 *
 * Please rest assured, however, that they are the same thing!
 * This is not unique to glMatrix, either, as OpenGL developers have long been confused by the
 * apparent lack of consistency between the memory layout and the documentation.
 */
let mat3 = {};

/**
 * Creates a new identity mat3
 *
 * @returns {mat3} a new 3x3 matrix
 */
mat3.create = function () {
  return new _mat3(
    1, 0, 0,
    0, 1, 0,
    0, 0, 1
  );
};

/**
 * Create a new mat3 with the given values
 *
 * @param {Number} m00 Component in column 0, row 0 position (index 0)
 * @param {Number} m01 Component in column 0, row 1 position (index 1)
 * @param {Number} m02 Component in column 0, row 2 position (index 2)
 * @param {Number} m10 Component in column 1, row 0 position (index 3)
 * @param {Number} m11 Component in column 1, row 1 position (index 4)
 * @param {Number} m12 Component in column 1, row 2 position (index 5)
 * @param {Number} m20 Component in column 2, row 0 position (index 6)
 * @param {Number} m21 Component in column 2, row 1 position (index 7)
 * @param {Number} m22 Component in column 2, row 2 position (index 8)
 * @returns {mat3} A new mat3
 */
mat3.new = function (m00, m01, m02, m10, m11, m12, m20, m21, m22) {
  return new _mat3(
    m00, m01, m02,
    m10, m11, m12,
    m20, m21, m22
  );
};

/**
 * Creates a new mat3 initialized with values from an existing matrix
 *
 * @param {mat3} a matrix to clone
 * @returns {mat3} a new 3x3 matrix
 */
mat3.clone = function (a) {
  return new _mat3(
    a.m00, a.m01, a.m02,
    a.m03, a.m04, a.m05,
    a.m06, a.m07, a.m08
  );
};

/**
 * Copy the values from one mat3 to another
 *
 * @param {mat3} out the receiving matrix
 * @param {mat3} a the source matrix
 * @returns {mat3} out
 */
mat3.copy = function (out, a) {
  out.m00 = a.m00;
  out.m01 = a.m01;
  out.m02 = a.m02;
  out.m03 = a.m03;
  out.m04 = a.m04;
  out.m05 = a.m05;
  out.m06 = a.m06;
  out.m07 = a.m07;
  out.m08 = a.m08;
  return out;
};

/**
 * Set the components of a mat3 to the given values
 *
 * @param {mat3} out the receiving matrix
 * @param {Number} m00 Component in column 0, row 0 position (index 0)
 * @param {Number} m01 Component in column 0, row 1 position (index 1)
 * @param {Number} m02 Component in column 0, row 2 position (index 2)
 * @param {Number} m10 Component in column 1, row 0 position (index 3)
 * @param {Number} m11 Component in column 1, row 1 position (index 4)
 * @param {Number} m12 Component in column 1, row 2 position (index 5)
 * @param {Number} m20 Component in column 2, row 0 position (index 6)
 * @param {Number} m21 Component in column 2, row 1 position (index 7)
 * @param {Number} m22 Component in column 2, row 2 position (index 8)
 * @returns {mat3} out
 */
mat3.set = function (out, m00, m01, m02, m10, m11, m12, m20, m21, m22) {
  out.m00 = m00;
  out.m01 = m01;
  out.m02 = m02;
  out.m03 = m10;
  out.m04 = m11;
  out.m05 = m12;
  out.m06 = m20;
  out.m07 = m21;
  out.m08 = m22;
  return out;
};

/**
 * Set a mat3 to the identity matrix
 *
 * @param {mat3} out the receiving matrix
 * @returns {mat3} out
 */
mat3.identity = function (out) {
  out.m00 = 1;
  out.m01 = 0;
  out.m02 = 0;
  out.m03 = 0;
  out.m04 = 1;
  out.m05 = 0;
  out.m06 = 0;
  out.m07 = 0;
  out.m08 = 1;
  return out;
};

/**
 * Transpose the values of a mat3
 *
 * @param {mat3} out the receiving matrix
 * @param {mat3} a the source matrix
 * @returns {mat3} out
 */
mat3.transpose = function (out, a) {
  // If we are transposing ourselves we can skip a few steps but have to cache some values
  if (out === a) {
    let a01 = a.m01, a02 = a.m02, a12 = a.m05;
    out.m01 = a.m03;
    out.m02 = a.m06;
    out.m03 = a01;
    out.m05 = a.m07;
    out.m06 = a02;
    out.m07 = a12;
  } else {
    out.m00 = a.m00;
    out.m01 = a.m03;
    out.m02 = a.m06;
    out.m03 = a.m01;
    out.m04 = a.m04;
    out.m05 = a.m07;
    out.m06 = a.m02;
    out.m07 = a.m05;
    out.m08 = a.m08;
  }

  return out;
};

/**
 * Inverts a mat3
 *
 * @param {mat3} out the receiving matrix
 * @param {mat3} a the source matrix
 * @returns {mat3} out
 */
mat3.invert = function (out, a) {
  let a00 = a.m00, a01 = a.m01, a02 = a.m02,
      a10 = a.m03, a11 = a.m04, a12 = a.m05,
      a20 = a.m06, a21 = a.m07, a22 = a.m08;

  let b01 = a22 * a11 - a12 * a21;
  let b11 = -a22 * a10 + a12 * a20;
  let b21 = a21 * a10 - a11 * a20;

  // Calculate the determinant
  let det = a00 * b01 + a01 * b11 + a02 * b21;

  if (!det) {
    return null;
  }
  det = 1.0 / det;

  out.m00 = b01 * det;
  out.m01 = (-a22 * a01 + a02 * a21) * det;
  out.m02 = (a12 * a01 - a02 * a11) * det;
  out.m03 = b11 * det;
  out.m04 = (a22 * a00 - a02 * a20) * det;
  out.m05 = (-a12 * a00 + a02 * a10) * det;
  out.m06 = b21 * det;
  out.m07 = (-a21 * a00 + a01 * a20) * det;
  out.m08 = (a11 * a00 - a01 * a10) * det;
  return out;
};

/**
 * Calculates the adjugate of a mat3
 *
 * @param {mat3} out the receiving matrix
 * @param {mat3} a the source matrix
 * @returns {mat3} out
 */
mat3.adjoint = function (out, a) {
  let a00 = a.m00, a01 = a.m01, a02 = a.m02,
      a10 = a.m03, a11 = a.m04, a12 = a.m05,
      a20 = a.m06, a21 = a.m07, a22 = a.m08;

  out.m00 = (a11 * a22 - a12 * a21);
  out.m01 = (a02 * a21 - a01 * a22);
  out.m02 = (a01 * a12 - a02 * a11);
  out.m03 = (a12 * a20 - a10 * a22);
  out.m04 = (a00 * a22 - a02 * a20);
  out.m05 = (a02 * a10 - a00 * a12);
  out.m06 = (a10 * a21 - a11 * a20);
  out.m07 = (a01 * a20 - a00 * a21);
  out.m08 = (a00 * a11 - a01 * a10);
  return out;
};

/**
 * Calculates the determinant of a mat3
 *
 * @param {mat3} a the source matrix
 * @returns {Number} determinant of a
 */
mat3.determinant = function (a) {
  let a00 = a.m00, a01 = a.m01, a02 = a.m02,
      a10 = a.m03, a11 = a.m04, a12 = a.m05,
      a20 = a.m06, a21 = a.m07, a22 = a.m08;

  return a00 * (a22 * a11 - a12 * a21) + a01 * (-a22 * a10 + a12 * a20) + a02 * (a21 * a10 - a11 * a20);
};

/**
 * Multiplies two mat3's
 *
 * @param {mat3} out the receiving matrix
 * @param {mat3} a the first operand
 * @param {mat3} b the second operand
 * @returns {mat3} out
 */
mat3.multiply = function (out, a, b) {
  let a00 = a.m00, a01 = a.m01, a02 = a.m02,
      a10 = a.m03, a11 = a.m04, a12 = a.m05,
      a20 = a.m06, a21 = a.m07, a22 = a.m08;

  let b00 = b.m00, b01 = b.m01, b02 = b.m02;
  let b10 = b.m03, b11 = b.m04, b12 = b.m05;
  let b20 = b.m06, b21 = b.m07, b22 = b.m08;

  out.m00 = b00 * a00 + b01 * a10 + b02 * a20;
  out.m01 = b00 * a01 + b01 * a11 + b02 * a21;
  out.m02 = b00 * a02 + b01 * a12 + b02 * a22;

  out.m03 = b10 * a00 + b11 * a10 + b12 * a20;
  out.m04 = b10 * a01 + b11 * a11 + b12 * a21;
  out.m05 = b10 * a02 + b11 * a12 + b12 * a22;

  out.m06 = b20 * a00 + b21 * a10 + b22 * a20;
  out.m07 = b20 * a01 + b21 * a11 + b22 * a21;
  out.m08 = b20 * a02 + b21 * a12 + b22 * a22;
  return out;
};

/**
 * Alias for {@link mat3.multiply}
 * @function
 */
mat3.mul = mat3.multiply;

/**
 * Translate a mat3 by the given vector
 *
 * @param {mat3} out the receiving matrix
 * @param {mat3} a the matrix to translate
 * @param {vec2} v vector to translate by
 * @returns {mat3} out
 */
mat3.translate = function (out, a, v) {
  let a00 = a.m00, a01 = a.m01, a02 = a.m02,
      a10 = a.m03, a11 = a.m04, a12 = a.m05,
      a20 = a.m06, a21 = a.m07, a22 = a.m08;
  let x = v.x, y = v.y;

  out.m00 = a00;
  out.m01 = a01;
  out.m02 = a02;

  out.m03 = a10;
  out.m04 = a11;
  out.m05 = a12;

  out.m06 = x * a00 + y * a10 + a20;
  out.m07 = x * a01 + y * a11 + a21;
  out.m08 = x * a02 + y * a12 + a22;
  return out;
};

/**
 * Rotates a mat3 by the given angle
 *
 * @param {mat3} out the receiving matrix
 * @param {mat3} a the matrix to rotate
 * @param {Number} rad the angle to rotate the matrix by
 * @returns {mat3} out
 */
mat3.rotate = function (out, a, rad) {
  let a00 = a.m00, a01 = a.m01, a02 = a.m02,
      a10 = a.m03, a11 = a.m04, a12 = a.m05,
      a20 = a.m06, a21 = a.m07, a22 = a.m08;

  let s = Math.sin(rad);
  let c = Math.cos(rad);

  out.m00 = c * a00 + s * a10;
  out.m01 = c * a01 + s * a11;
  out.m02 = c * a02 + s * a12;

  out.m03 = c * a10 - s * a00;
  out.m04 = c * a11 - s * a01;
  out.m05 = c * a12 - s * a02;

  out.m06 = a20;
  out.m07 = a21;
  out.m08 = a22;
  return out;
};

/**
 * Scales the mat3 by the dimensions in the given vec2
 *
 * @param {mat3} out the receiving matrix
 * @param {mat3} a the matrix to rotate
 * @param {vec2} v the vec2 to scale the matrix by
 * @returns {mat3} out
 **/
mat3.scale = function (out, a, v) {
  let x = v.x, y = v.y;

  out.m00 = x * a.m00;
  out.m01 = x * a.m01;
  out.m02 = x * a.m02;

  out.m03 = y * a.m03;
  out.m04 = y * a.m04;
  out.m05 = y * a.m05;

  out.m06 = a.m06;
  out.m07 = a.m07;
  out.m08 = a.m08;
  return out;
};

/**
 * Copies the upper-left 3x3 values into the given mat3.
 *
 * @param {mat3} out the receiving 3x3 matrix
 * @param {mat4} a   the source 4x4 matrix
 * @returns {mat3} out
 */
mat3.fromMat4 = function (out, a) {
  out.m00 = a.m00;
  out.m01 = a.m01;
  out.m02 = a.m02;
  out.m03 = a.m04;
  out.m04 = a.m05;
  out.m05 = a.m06;
  out.m06 = a.m08;
  out.m07 = a.m09;
  out.m08 = a.m10;
  return out;
};

/**
 * Creates a matrix from a vector translation
 * This is equivalent to (but much faster than):
 *
 *     mat3.identity(dest);
 *     mat3.translate(dest, dest, vec);
 *
 * @param {mat3} out mat3 receiving operation result
 * @param {vec2} v Translation vector
 * @returns {mat3} out
 */
mat3.fromTranslation = function (out, v) {
  out.m00 = 1;
  out.m01 = 0;
  out.m02 = 0;
  out.m03 = 0;
  out.m04 = 1;
  out.m05 = 0;
  out.m06 = v.x;
  out.m07 = v.y;
  out.m08 = 1;
  return out;
};

/**
 * Creates a matrix from a given angle
 * This is equivalent to (but much faster than):
 *
 *     mat3.identity(dest);
 *     mat3.rotate(dest, dest, rad);
 *
 * @param {mat3} out mat3 receiving operation result
 * @param {Number} rad the angle to rotate the matrix by
 * @returns {mat3} out
 */
mat3.fromRotation = function (out, rad) {
  let s = Math.sin(rad), c = Math.cos(rad);

  out.m00 = c;
  out.m01 = s;
  out.m02 = 0;

  out.m03 = -s;
  out.m04 = c;
  out.m05 = 0;

  out.m06 = 0;
  out.m07 = 0;
  out.m08 = 1;
  return out;
};

/**
 * Creates a matrix from a vector scaling
 * This is equivalent to (but much faster than):
 *
 *     mat3.identity(dest);
 *     mat3.scale(dest, dest, vec);
 *
 * @param {mat3} out mat3 receiving operation result
 * @param {vec2} v Scaling vector
 * @returns {mat3} out
 */
mat3.fromScaling = function (out, v) {
  out.m00 = v.x;
  out.m01 = 0;
  out.m02 = 0;

  out.m03 = 0;
  out.m04 = v.y;
  out.m05 = 0;

  out.m06 = 0;
  out.m07 = 0;
  out.m08 = 1;
  return out;
};

/**
 * Copies the values from a mat2d into a mat3
 *
 * @param {mat3} out the receiving matrix
 * @param {mat2d} a the matrix to copy
 * @returns {mat3} out
 **/
mat3.fromMat2d = function (out, a) {
  out.m00 = a.m00;
  out.m01 = a.m01;
  out.m02 = 0;

  out.m03 = a.m02;
  out.m04 = a.m03;
  out.m05 = 0;

  out.m06 = a.m04;
  out.m07 = a.m05;
  out.m08 = 1;
  return out;
};

/**
* Calculates a 3x3 matrix from the given quaternion
*
* @param {mat3} out mat3 receiving operation result
* @param {quat} q Quaternion to create matrix from
*
* @returns {mat3} out
*/
mat3.fromQuat = function (out, q) {
  let x = q.x, y = q.y, z = q.z, w = q.w;
  let x2 = x + x;
  let y2 = y + y;
  let z2 = z + z;

  let xx = x * x2;
  let yx = y * x2;
  let yy = y * y2;
  let zx = z * x2;
  let zy = z * y2;
  let zz = z * z2;
  let wx = w * x2;
  let wy = w * y2;
  let wz = w * z2;

  out.m00 = 1 - yy - zz;
  out.m03 = yx - wz;
  out.m06 = zx + wy;

  out.m01 = yx + wz;
  out.m04 = 1 - xx - zz;
  out.m07 = zy - wx;

  out.m02 = zx - wy;
  out.m05 = zy + wx;
  out.m08 = 1 - xx - yy;

  return out;
};

/**
* Calculates a 3x3 matrix from view direction and up direction
*
* @param {mat3} out mat3 receiving operation result
* @param {vec3} view view direction (must be normalized)
* @param {vec3} [up] up direction, default is (0,1,0) (must be normalized)
*
* @returns {mat3} out
*/
mat3.fromViewUp = (function () {
  let default_up = vec3.new(0, 1, 0);
  let x = vec3.create();
  let y = vec3.create();

  return function (out, view, up) {
    if (vec3.sqrLen(view) < EPSILON * EPSILON) {
      mat3.identity(out);
      return out;
    }

    up = up || default_up;
    vec3.cross(x, up, view);

    if (vec3.sqrLen(x) < EPSILON * EPSILON) {
      mat3.identity(out);
      return out;
    }

    vec3.cross(y, view, x);
    mat3.set(out,
      x.x, x.y, x.z,
      y.x, y.y, y.z,
      view.x, view.y, view.z
    );

    return out;
  };
})();

/**
* Calculates a 3x3 normal matrix (transpose inverse) from the 4x4 matrix
*
* @param {mat3} out mat3 receiving operation result
* @param {mat4} a Mat4 to derive the normal matrix from
*
* @returns {mat3} out
*/
mat3.normalFromMat4 = function (out, a) {
  let a00 = a.m00, a01 = a.m01, a02 = a.m02, a03 = a.m03,
      a10 = a.m04, a11 = a.m05, a12 = a.m06, a13 = a.m07,
      a20 = a.m08, a21 = a.m09, a22 = a.m10, a23 = a.m11,
      a30 = a.m12, a31 = a.m13, a32 = a.m14, a33 = a.m15;

  let b00 = a00 * a11 - a01 * a10;
  let b01 = a00 * a12 - a02 * a10;
  let b02 = a00 * a13 - a03 * a10;
  let b03 = a01 * a12 - a02 * a11;
  let b04 = a01 * a13 - a03 * a11;
  let b05 = a02 * a13 - a03 * a12;
  let b06 = a20 * a31 - a21 * a30;
  let b07 = a20 * a32 - a22 * a30;
  let b08 = a20 * a33 - a23 * a30;
  let b09 = a21 * a32 - a22 * a31;
  let b10 = a21 * a33 - a23 * a31;
  let b11 = a22 * a33 - a23 * a32;

  // Calculate the determinant
  let det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;

  if (!det) {
    return null;
  }
  det = 1.0 / det;

  out.m00 = (a11 * b11 - a12 * b10 + a13 * b09) * det;
  out.m01 = (a12 * b08 - a10 * b11 - a13 * b07) * det;
  out.m02 = (a10 * b10 - a11 * b08 + a13 * b06) * det;

  out.m03 = (a02 * b10 - a01 * b11 - a03 * b09) * det;
  out.m04 = (a00 * b11 - a02 * b08 + a03 * b07) * det;
  out.m05 = (a01 * b08 - a00 * b10 - a03 * b06) * det;

  out.m06 = (a31 * b05 - a32 * b04 + a33 * b03) * det;
  out.m07 = (a32 * b02 - a30 * b05 - a33 * b01) * det;
  out.m08 = (a30 * b04 - a31 * b02 + a33 * b00) * det;

  return out;
};

/**
 * Returns a string representation of a mat3
 *
 * @param {mat3} a matrix to represent as a string
 * @returns {String} string representation of the matrix
 */
mat3.str = function (a) {
  return `mat3(${a.m00}, ${a.m01}, ${a.m02}, ${a.m03}, ${a.m04}, ${a.m05}, ${a.m06}, ${a.m07}, ${a.m08})`;
};

/**
 * Returns typed array
 *
 * @param {array} out
 * @param {mat3} m
 * @returns {array}
 */
mat3.array = function (out, m) {
  out[0] = m.m00;
  out[1] = m.m01;
  out[2] = m.m02;
  out[3] = m.m03;
  out[4] = m.m04;
  out[5] = m.m05;
  out[6] = m.m06;
  out[7] = m.m07;
  out[8] = m.m08;

  return out;
};

/**
 * Returns Frobenius norm of a mat3
 *
 * @param {mat3} a the matrix to calculate Frobenius norm of
 * @returns {Number} Frobenius norm
 */
mat3.frob = function (a) {
  return (Math.sqrt(Math.pow(a.m00, 2) + Math.pow(a.m01, 2) + Math.pow(a.m02, 2) + Math.pow(a.m03, 2) + Math.pow(a.m04, 2) + Math.pow(a.m05, 2) + Math.pow(a.m06, 2) + Math.pow(a.m07, 2) + Math.pow(a.m08, 2)));
};

/**
 * Adds two mat3's
 *
 * @param {mat3} out the receiving matrix
 * @param {mat3} a the first operand
 * @param {mat3} b the second operand
 * @returns {mat3} out
 */
mat3.add = function (out, a, b) {
  out.m00 = a.m00 + b.m00;
  out.m01 = a.m01 + b.m01;
  out.m02 = a.m02 + b.m02;
  out.m03 = a.m03 + b.m03;
  out.m04 = a.m04 + b.m04;
  out.m05 = a.m05 + b.m05;
  out.m06 = a.m06 + b.m06;
  out.m07 = a.m07 + b.m07;
  out.m08 = a.m08 + b.m08;
  return out;
};

/**
 * Subtracts matrix b from matrix a
 *
 * @param {mat3} out the receiving matrix
 * @param {mat3} a the first operand
 * @param {mat3} b the second operand
 * @returns {mat3} out
 */
mat3.subtract = function (out, a, b) {
  out.m00 = a.m00 - b.m00;
  out.m01 = a.m01 - b.m01;
  out.m02 = a.m02 - b.m02;
  out.m03 = a.m03 - b.m03;
  out.m04 = a.m04 - b.m04;
  out.m05 = a.m05 - b.m05;
  out.m06 = a.m06 - b.m06;
  out.m07 = a.m07 - b.m07;
  out.m08 = a.m08 - b.m08;
  return out;
};

/**
 * Alias for {@link mat3.subtract}
 * @function
 */
mat3.sub = mat3.subtract;

/**
 * Multiply each element of the matrix by a scalar.
 *
 * @param {mat3} out the receiving matrix
 * @param {mat3} a the matrix to scale
 * @param {Number} b amount to scale the matrix's elements by
 * @returns {mat3} out
 */
mat3.multiplyScalar = function (out, a, b) {
  out.m00 = a.m00 * b;
  out.m01 = a.m01 * b;
  out.m02 = a.m02 * b;
  out.m03 = a.m03 * b;
  out.m04 = a.m04 * b;
  out.m05 = a.m05 * b;
  out.m06 = a.m06 * b;
  out.m07 = a.m07 * b;
  out.m08 = a.m08 * b;
  return out;
};

/**
 * Adds two mat3's after multiplying each element of the second operand by a scalar value.
 *
 * @param {mat3} out the receiving vector
 * @param {mat3} a the first operand
 * @param {mat3} b the second operand
 * @param {Number} scale the amount to scale b's elements by before adding
 * @returns {mat3} out
 */
mat3.multiplyScalarAndAdd = function (out, a, b, scale) {
  out.m00 = a.m00 + (b.m00 * scale);
  out.m01 = a.m01 + (b.m01 * scale);
  out.m02 = a.m02 + (b.m02 * scale);
  out.m03 = a.m03 + (b.m03 * scale);
  out.m04 = a.m04 + (b.m04 * scale);
  out.m05 = a.m05 + (b.m05 * scale);
  out.m06 = a.m06 + (b.m06 * scale);
  out.m07 = a.m07 + (b.m07 * scale);
  out.m08 = a.m08 + (b.m08 * scale);
  return out;
};

/**
 * Returns whether or not the matrices have exactly the same elements in the same position (when compared with ===)
 *
 * @param {mat3} a The first matrix.
 * @param {mat3} b The second matrix.
 * @returns {Boolean} True if the matrices are equal, false otherwise.
 */
mat3.exactEquals = function (a, b) {
  return a.m00 === b.m00 && a.m01 === b.m01 && a.m02 === b.m02 &&
    a.m03 === b.m03 && a.m04 === b.m04 && a.m05 === b.m05 &&
    a.m06 === b.m06 && a.m07 === b.m07 && a.m08 === b.m08;
};

/**
 * Returns whether or not the matrices have approximately the same elements in the same position.
 *
 * @param {mat3} a The first matrix.
 * @param {mat3} b The second matrix.
 * @returns {Boolean} True if the matrices are equal, false otherwise.
 */
mat3.equals = function (a, b) {
  let a0 = a.m00, a1 = a.m01, a2 = a.m02, a3 = a.m03, a4 = a.m04, a5 = a.m05, a6 = a.m06, a7 = a.m07, a8 = a.m08;
  let b0 = b.m00, b1 = b.m01, b2 = b.m02, b3 = b.m03, b4 = b.m04, b5 = b.m05, b6 = b.m06, b7 = b.m07, b8 = b.m08;
  return (
    Math.abs(a0 - b0) <= EPSILON * Math.max(1.0, Math.abs(a0), Math.abs(b0)) &&
    Math.abs(a1 - b1) <= EPSILON * Math.max(1.0, Math.abs(a1), Math.abs(b1)) &&
    Math.abs(a2 - b2) <= EPSILON * Math.max(1.0, Math.abs(a2), Math.abs(b2)) &&
    Math.abs(a3 - b3) <= EPSILON * Math.max(1.0, Math.abs(a3), Math.abs(b3)) &&
    Math.abs(a4 - b4) <= EPSILON * Math.max(1.0, Math.abs(a4), Math.abs(b4)) &&
    Math.abs(a5 - b5) <= EPSILON * Math.max(1.0, Math.abs(a5), Math.abs(b5)) &&
    Math.abs(a6 - b6) <= EPSILON * Math.max(1.0, Math.abs(a6), Math.abs(b6)) &&
    Math.abs(a7 - b7) <= EPSILON * Math.max(1.0, Math.abs(a7), Math.abs(b7)) &&
    Math.abs(a8 - b8) <= EPSILON * Math.max(1.0, Math.abs(a8), Math.abs(b8))
  );
};

let _tmp$3 = new Array(4);

class _quat {
  constructor(x, y, z, w) {
    this.x = x;
    this.y = y;
    this.z = z;
    this.w = w;
  }

  toJSON() {
    _tmp$3[0] = this.x;
    _tmp$3[1] = this.y;
    _tmp$3[2] = this.z;
    _tmp$3[3] = this.w;

    return _tmp$3;
  }
}

/**
 * @class Quaternion
 * @name quat
 */
let quat = {};

/**
 * Creates a new identity quat
 *
 * @returns {quat} a new quaternion
 */
quat.create = function () {
  return new _quat(0, 0, 0, 1);
};

/**
 * Creates a new quat initialized with the given values
 *
 * @param {Number} x X component
 * @param {Number} y Y component
 * @param {Number} z Z component
 * @param {Number} w W component
 * @returns {quat} a new quaternion
 * @function
 */
quat.new = function (x, y, z, w) {
  return new _quat(x, y, z, w);
};

/**
 * Creates a new quat initialized with values from an existing quaternion
 *
 * @param {quat} a quaternion to clone
 * @returns {quat} a new quaternion
 * @function
 */
quat.clone = function (a) {
  return new _quat(a.x, a.y, a.z, a.w);
};

/**
 * Copy the values from one quat to another
 *
 * @param {quat} out the receiving quaternion
 * @param {quat} a the source quaternion
 * @returns {quat} out
 * @function
 */
quat.copy = vec4.copy;

/**
 * Set the components of a quat to the given values
 *
 * @param {quat} out the receiving quaternion
 * @param {Number} x X component
 * @param {Number} y Y component
 * @param {Number} z Z component
 * @param {Number} w W component
 * @returns {quat} out
 * @function
 */
quat.set = vec4.set;

/**
 * Set a quat to the identity quaternion
 *
 * @param {quat} out the receiving quaternion
 * @returns {quat} out
 */
quat.identity = function (out) {
  out.x = 0;
  out.y = 0;
  out.z = 0;
  out.w = 1;
  return out;
};

/**
 * Sets a quaternion to represent the shortest rotation from one
 * vector to another.
 *
 * Both vectors are assumed to be unit length.
 *
 * @param {quat} out the receiving quaternion.
 * @param {vec3} a the initial vector
 * @param {vec3} b the destination vector
 * @returns {quat} out
 */
quat.rotationTo = (function () {
  let tmpvec3 = vec3.create();
  let xUnitVec3 = vec3.new(1, 0, 0);
  let yUnitVec3 = vec3.new(0, 1, 0);

  return function (out, a, b) {
    let dot = vec3.dot(a, b);
    if (dot < -0.999999) {
      vec3.cross(tmpvec3, xUnitVec3, a);
      if (vec3.length(tmpvec3) < 0.000001) {
        vec3.cross(tmpvec3, yUnitVec3, a);
      }
      vec3.normalize(tmpvec3, tmpvec3);
      quat.fromAxisAngle(out, tmpvec3, Math.PI);
      return out;
    } else if (dot > 0.999999) {
      out.x = 0;
      out.y = 0;
      out.z = 0;
      out.w = 1;
      return out;
    } else {
      vec3.cross(tmpvec3, a, b);
      out.x = tmpvec3.x;
      out.y = tmpvec3.y;
      out.z = tmpvec3.z;
      out.w = 1 + dot;
      return quat.normalize(out, out);
    }
  };
})();

/**
 * Gets the rotation axis and angle for a given
 *  quaternion. If a quaternion is created with
 *  fromAxisAngle, this method will return the same
 *  values as providied in the original parameter list
 *  OR functionally equivalent values.
 * Example: The quaternion formed by axis [0, 0, 1] and
 *  angle -90 is the same as the quaternion formed by
 *  [0, 0, 1] and 270. This method favors the latter.
 * @param  {vec3} out_axis  Vector receiving the axis of rotation
 * @param  {quat} q     Quaternion to be decomposed
 * @return {Number}     Angle, in radians, of the rotation
 */
quat.getAxisAngle = function (out_axis, q) {
  let rad = Math.acos(q.w) * 2.0;
  let s = Math.sin(rad / 2.0);
  if (s != 0.0) {
    out_axis.x = q.x / s;
    out_axis.y = q.y / s;
    out_axis.z = q.z / s;
  } else {
    // If s is zero, return any axis (no rotation - axis does not matter)
    out_axis.x = 1;
    out_axis.y = 0;
    out_axis.z = 0;
  }
  return rad;
};

/**
 * Multiplies two quat's
 *
 * @param {quat} out the receiving quaternion
 * @param {quat} a the first operand
 * @param {quat} b the second operand
 * @returns {quat} out
 */
quat.multiply = function (out, a, b) {
  let ax = a.x, ay = a.y, az = a.z, aw = a.w,
      bx = b.x, by = b.y, bz = b.z, bw = b.w;

  out.x = ax * bw + aw * bx + ay * bz - az * by;
  out.y = ay * bw + aw * by + az * bx - ax * bz;
  out.z = az * bw + aw * bz + ax * by - ay * bx;
  out.w = aw * bw - ax * bx - ay * by - az * bz;
  return out;
};

/**
 * Alias for {@link quat.multiply}
 * @function
 */
quat.mul = quat.multiply;

/**
 * Scales a quat by a scalar number
 *
 * @param {quat} out the receiving vector
 * @param {quat} a the vector to scale
 * @param {Number} b amount to scale the vector by
 * @returns {quat} out
 * @function
 */
quat.scale = vec4.scale;

/**
 * Rotates a quaternion by the given angle about the X axis
 *
 * @param {quat} out quat receiving operation result
 * @param {quat} a quat to rotate
 * @param {number} rad angle (in radians) to rotate
 * @returns {quat} out
 */
quat.rotateX = function (out, a, rad) {
  rad *= 0.5;

  let ax = a.x, ay = a.y, az = a.z, aw = a.w,
      bx = Math.sin(rad), bw = Math.cos(rad);

  out.x = ax * bw + aw * bx;
  out.y = ay * bw + az * bx;
  out.z = az * bw - ay * bx;
  out.w = aw * bw - ax * bx;
  return out;
};

/**
 * Rotates a quaternion by the given angle about the Y axis
 *
 * @param {quat} out quat receiving operation result
 * @param {quat} a quat to rotate
 * @param {number} rad angle (in radians) to rotate
 * @returns {quat} out
 */
quat.rotateY = function (out, a, rad) {
  rad *= 0.5;

  let ax = a.x, ay = a.y, az = a.z, aw = a.w,
      by = Math.sin(rad), bw = Math.cos(rad);

  out.x = ax * bw - az * by;
  out.y = ay * bw + aw * by;
  out.z = az * bw + ax * by;
  out.w = aw * bw - ay * by;
  return out;
};

/**
 * Rotates a quaternion by the given angle about the Z axis
 *
 * @param {quat} out quat receiving operation result
 * @param {quat} a quat to rotate
 * @param {number} rad angle (in radians) to rotate
 * @returns {quat} out
 */
quat.rotateZ = function (out, a, rad) {
  rad *= 0.5;

  let ax = a.x, ay = a.y, az = a.z, aw = a.w,
      bz = Math.sin(rad), bw = Math.cos(rad);

  out.x = ax * bw + ay * bz;
  out.y = ay * bw - ax * bz;
  out.z = az * bw + aw * bz;
  out.w = aw * bw - az * bz;
  return out;
};

/**
 * Rotates a quaternion by the given angle about the axis in world space
 *
 * @param {quat} out quat receiving operation result
 * @param {quat} rot quat to rotate
 * @param {vec3} axis the axis around which to rotate in world space
 * @param {number} rad angle (in radians) to rotate
 * @returns {quat} out
 */
quat.rotateAround = (function () {
  let v3_tmp = vec3.create();
  let q_tmp = quat.create();

  return function (out, rot, axis, rad) {
    // get inv-axis (local to rot)
    quat.invert(q_tmp, rot);
    vec3.transformQuat(v3_tmp, axis, q_tmp);
    // rotate by inv-axis
    quat.fromAxisAngle(q_tmp, v3_tmp, rad);
    quat.mul(out, rot, q_tmp);

    return out;
  };
})();

/**
 * Rotates a quaternion by the given angle about the axis in local space
 *
 * @param {quat} out quat receiving operation result
 * @param {quat} rot quat to rotate
 * @param {vec3} axis the axis around which to rotate in local space
 * @param {number} rad angle (in radians) to rotate
 * @returns {quat} out
 */
quat.rotateAroundLocal = (function () {
  let q_tmp = quat.create();

  return function (out, rot, axis, rad) {
    quat.fromAxisAngle(q_tmp, axis, rad);
    quat.mul(out, rot, q_tmp);

    return out;
  };
})();

/**
 * Calculates the W component of a quat from the X, Y, and Z components.
 * Assumes that quaternion is 1 unit in length.
 * Any existing W component will be ignored.
 *
 * @param {quat} out the receiving quaternion
 * @param {quat} a quat to calculate W component of
 * @returns {quat} out
 */
quat.calculateW = function (out, a) {
  let x = a.x, y = a.y, z = a.z;

  out.x = x;
  out.y = y;
  out.z = z;
  out.w = Math.sqrt(Math.abs(1.0 - x * x - y * y - z * z));
  return out;
};

/**
 * Calculates the dot product of two quat's
 *
 * @param {quat} a the first operand
 * @param {quat} b the second operand
 * @returns {Number} dot product of a and b
 * @function
 */
quat.dot = vec4.dot;

/**
 * Performs a linear interpolation between two quat's
 *
 * @param {quat} out the receiving quaternion
 * @param {quat} a the first operand
 * @param {quat} b the second operand
 * @param {Number} t interpolation amount between the two inputs
 * @returns {quat} out
 * @function
 */
quat.lerp = vec4.lerp;

/**
 * Performs a spherical linear interpolation between two quat
 *
 * @param {quat} out the receiving quaternion
 * @param {quat} a the first operand
 * @param {quat} b the second operand
 * @param {Number} t interpolation amount between the two inputs
 * @returns {quat} out
 */
quat.slerp = function (out, a, b, t) {
  // benchmarks:
  //    http://jsperf.com/quaternion-slerp-implementations

  let ax = a.x, ay = a.y, az = a.z, aw = a.w,
      bx = b.x, by = b.y, bz = b.z, bw = b.w;

  let omega, cosom, sinom, scale0, scale1;

  // calc cosine
  cosom = ax * bx + ay * by + az * bz + aw * bw;
  // adjust signs (if necessary)
  if (cosom < 0.0) {
    cosom = -cosom;
    bx = - bx;
    by = - by;
    bz = - bz;
    bw = - bw;
  }
  // calculate coefficients
  if ((1.0 - cosom) > 0.000001) {
    // standard case (slerp)
    omega = Math.acos(cosom);
    sinom = Math.sin(omega);
    scale0 = Math.sin((1.0 - t) * omega) / sinom;
    scale1 = Math.sin(t * omega) / sinom;
  } else {
    // "from" and "to" quaternions are very close
    //  ... so we can do a linear interpolation
    scale0 = 1.0 - t;
    scale1 = t;
  }
  // calculate final values
  out.x = scale0 * ax + scale1 * bx;
  out.y = scale0 * ay + scale1 * by;
  out.z = scale0 * az + scale1 * bz;
  out.w = scale0 * aw + scale1 * bw;

  return out;
};

/**
 * Performs a spherical linear interpolation with two control points
 *
 * @param {quat} out the receiving quaternion
 * @param {quat} a the first operand
 * @param {quat} b the second operand
 * @param {quat} c the third operand
 * @param {quat} d the fourth operand
 * @param {Number} t interpolation amount
 * @returns {quat} out
 */
quat.sqlerp = (function () {
  let temp1 = quat.create();
  let temp2 = quat.create();

  return function (out, a, b, c, d, t) {
    quat.slerp(temp1, a, d, t);
    quat.slerp(temp2, b, c, t);
    quat.slerp(out, temp1, temp2, 2 * t * (1 - t));

    return out;
  };
}());

/**
 * Calculates the inverse of a quat
 *
 * @param {quat} out the receiving quaternion
 * @param {quat} a quat to calculate inverse of
 * @returns {quat} out
 */
quat.invert = function (out, a) {
  let a0 = a.x, a1 = a.y, a2 = a.z, a3 = a.w;
  let dot = a0 * a0 + a1 * a1 + a2 * a2 + a3 * a3;
  let invDot = dot ? 1.0 / dot : 0;

  // TODO: Would be faster to return [0,0,0,0] immediately if dot == 0

  out.x = -a0 * invDot;
  out.y = -a1 * invDot;
  out.z = -a2 * invDot;
  out.w = a3 * invDot;
  return out;
};

/**
 * Calculates the conjugate of a quat
 * If the quaternion is normalized, this function is faster than quat.inverse and produces the same result.
 *
 * @param {quat} out the receiving quaternion
 * @param {quat} a quat to calculate conjugate of
 * @returns {quat} out
 */
quat.conjugate = function (out, a) {
  out.x = -a.x;
  out.y = -a.y;
  out.z = -a.z;
  out.w = a.w;
  return out;
};

/**
 * Calculates the length of a quat
 *
 * @param {quat} a vector to calculate length of
 * @returns {Number} length of a
 * @function
 */
quat.length = vec4.length;

/**
 * Alias for {@link quat.length}
 * @function
 */
quat.len = quat.length;

/**
 * Calculates the squared length of a quat
 *
 * @param {quat} a vector to calculate squared length of
 * @returns {Number} squared length of a
 * @function
 */
quat.squaredLength = vec4.squaredLength;

/**
 * Alias for {@link quat.squaredLength}
 * @function
 */
quat.sqrLen = quat.squaredLength;

/**
 * Normalize a quat
 *
 * @param {quat} out the receiving quaternion
 * @param {quat} a quaternion to normalize
 * @returns {quat} out
 * @function
 */
quat.normalize = vec4.normalize;

/**
 * Sets the specified quaternion with values corresponding to the given
 * axes. Each axis is a vec3 and is expected to be unit length and
 * perpendicular to all other specified axes.
 *
 * @param {vec3} xAxis the vector representing the local "right" direction
 * @param {vec3} yAxis the vector representing the local "up" direction
 * @param {vec3} zAxis the vector representing the viewing direction
 * @returns {quat} out
 */
quat.fromAxes = (function () {
  let matr = mat3.create();

  return function (out, xAxis, yAxis, zAxis) {
    mat3.set(
      matr,
      xAxis.x, xAxis.y, xAxis.z,
      yAxis.x, yAxis.y, yAxis.z,
      zAxis.x, zAxis.y, zAxis.z
    );
    return quat.normalize(out, quat.fromMat3(out, matr));
  };
})();

/**
* Calculates a quaternion from view direction and up direction
*
* @param {quat} out mat3 receiving operation result
* @param {vec3} view view direction (must be normalized)
* @param {vec3} [up] up direction, default is (0,1,0) (must be normalized)
*
* @returns {quat} out
*/
quat.fromViewUp = (function () {
  let matr = mat3.create();

  return function (out, view, up) {
    mat3.fromViewUp(matr, view, up);
    if (!matr) {
      return null;
    }

    return quat.normalize(out, quat.fromMat3(out, matr));
  };
})();

/**
 * Sets a quat from the given angle and rotation axis,
 * then returns it.
 *
 * @param {quat} out the receiving quaternion
 * @param {vec3} axis the axis around which to rotate
 * @param {Number} rad the angle in radians
 * @returns {quat} out
 **/
quat.fromAxisAngle = function (out, axis, rad) {
  rad = rad * 0.5;
  let s = Math.sin(rad);
  out.x = s * axis.x;
  out.y = s * axis.y;
  out.z = s * axis.z;
  out.w = Math.cos(rad);
  return out;
};

/**
 * Creates a quaternion from the given 3x3 rotation matrix.
 *
 * NOTE: The resultant quaternion is not normalized, so you should be sure
 * to renormalize the quaternion yourself where necessary.
 *
 * @param {quat} out the receiving quaternion
 * @param {mat3} m rotation matrix
 * @returns {quat} out
 * @function
 */
quat.fromMat3 = function (out, m) {
  // http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm

  let m00 = m.m00, m01 = m.m03, m02 = m.m06,
      m10 = m.m01, m11 = m.m04, m12 = m.m07,
      m20 = m.m02, m21 = m.m05, m22 = m.m08;

  let trace = m00 + m11 + m22;

  if (trace > 0) {
    let s = 0.5 / Math.sqrt(trace + 1.0);

    out.w = 0.25 / s;
    out.x = (m21 - m12) * s;
    out.y = (m02 - m20) * s;
    out.z = (m10 - m01) * s;

  } else if ((m00 > m11) && (m00 > m22)) {
    let s = 2.0 * Math.sqrt(1.0 + m00 - m11 - m22);

    out.w = (m21 - m12) / s;
    out.x = 0.25 * s;
    out.y = (m01 + m10) / s;
    out.z = (m02 + m20) / s;

  } else if (m11 > m22) {
    let s = 2.0 * Math.sqrt(1.0 + m11 - m00 - m22);

    out.w = (m02 - m20) / s;
    out.x = (m01 + m10) / s;
    out.y = 0.25 * s;
    out.z = (m12 + m21) / s;

  } else {
    let s = 2.0 * Math.sqrt(1.0 + m22 - m00 - m11);

    out.w = (m10 - m01) / s;
    out.x = (m02 + m20) / s;
    out.y = (m12 + m21) / s;
    out.z = 0.25 * s;
  }

  return out;
};

/**
 * Creates a quaternion from the given euler angle x, y, z.
 *
 * @param {quat} out the receiving quaternion
 * @param {x} Angle to rotate around X axis in degrees.
 * @param {y} Angle to rotate around Y axis in degrees.
 * @param {z} Angle to rotate around Z axis in degrees.
 * @returns {quat} out
 * @function
 */
quat.fromEuler = function (out, x, y, z) {
  let halfToRad = 0.5 * Math.PI / 180.0;
  x *= halfToRad;
  y *= halfToRad;
  z *= halfToRad;

  let sx = Math.sin(x);
  let cx = Math.cos(x);
  let sy = Math.sin(y);
  let cy = Math.cos(y);
  let sz = Math.sin(z);
  let cz = Math.cos(z);

  out.x = sx * cy * cz - cx * sy * sz;
  out.y = cx * sy * cz + sx * cy * sz;
  out.z = cx * cy * sz - sx * sy * cz;
  out.w = cx * cy * cz + sx * sy * sz;

  return out;
};

/**
 * Returns a string representation of a quatenion
 *
 * @param {quat} a vector to represent as a string
 * @returns {String} string representation of the vector
 */
quat.str = function (a) {
  return `quat(${a.x}, ${a.y}, ${a.z}, ${a.w})`;
};

/**
 * Returns typed array
 *
 * @param {array} out
 * @param {quat} q
 * @returns {array}
 */
quat.array = function (out, q) {
  out[0] = q.x;
  out[1] = q.y;
  out[2] = q.z;
  out[3] = q.w;

  return out;
};

/**
 * Returns whether or not the quaternions have exactly the same elements in the same position (when compared with ===)
 *
 * @param {quat} a The first quaternion.
 * @param {quat} b The second quaternion.
 * @returns {Boolean} True if the vectors are equal, false otherwise.
 */
quat.exactEquals = vec4.exactEquals;

/**
 * Returns whether or not the quaternions have approximately the same elements in the same position.
 *
 * @param {quat} a The first vector.
 * @param {quat} b The second vector.
 * @returns {Boolean} True if the vectors are equal, false otherwise.
 */
quat.equals = vec4.equals;

let _tmp$5 = new Array(4);

class _mat2 {
  constructor(m00, m01, m02, m03) {
    this.m00 = m00;
    this.m01 = m01;
    this.m02 = m02;
    this.m03 = m03;
  }

  toJSON() {
    _tmp$5[0] = this.m00;
    _tmp$5[1] = this.m01;
    _tmp$5[2] = this.m02;
    _tmp$5[3] = this.m03;

    return _tmp$5;
  }
}

/**
 * @class 2x2 Matrix
 * @name mat2
 */
let mat2 = {};

/**
 * Creates a new identity mat2
 *
 * @returns {mat2} a new 2x2 matrix
 */
mat2.create = function() {
  return new _mat2(1, 0, 0, 1);
};

/**
 * Create a new mat2 with the given values
 *
 * @param {Number} m00 Component in column 0, row 0 position (index 0)
 * @param {Number} m01 Component in column 0, row 1 position (index 1)
 * @param {Number} m10 Component in column 1, row 0 position (index 2)
 * @param {Number} m11 Component in column 1, row 1 position (index 3)
 * @returns {mat2} out A new 2x2 matrix
 */
mat2.new = function (m00, m01, m10, m11) {
  return new _mat2(m00, m01, m10, m11);
};

/**
 * Creates a new mat2 initialized with values from an existing matrix
 *
 * @param {mat2} a matrix to clone
 * @returns {mat2} a new 2x2 matrix
 */
mat2.clone = function (a) {
  return new _mat2(a.m00, a.m01, a.m02, a.m03);
};

/**
 * Copy the values from one mat2 to another
 *
 * @param {mat2} out the receiving matrix
 * @param {mat2} a the source matrix
 * @returns {mat2} out
 */
mat2.copy = function (out, a) {
  out.m00 = a.m00;
  out.m01 = a.m01;
  out.m02 = a.m02;
  out.m03 = a.m03;
  return out;
};

/**
 * Set a mat2 to the identity matrix
 *
 * @param {mat2} out the receiving matrix
 * @returns {mat2} out
 */
mat2.identity = function (out) {
  out.m00 = 1;
  out.m01 = 0;
  out.m02 = 0;
  out.m03 = 1;
  return out;
};

/**
 * Set the components of a mat2 to the given values
 *
 * @param {mat2} out the receiving matrix
 * @param {Number} m00 Component in column 0, row 0 position (index 0)
 * @param {Number} m01 Component in column 0, row 1 position (index 1)
 * @param {Number} m10 Component in column 1, row 0 position (index 2)
 * @param {Number} m11 Component in column 1, row 1 position (index 3)
 * @returns {mat2} out
 */
mat2.set = function (out, m00, m01, m10, m11) {
  out.m00 = m00;
  out.m01 = m01;
  out.m02 = m10;
  out.m03 = m11;
  return out;
};


/**
 * Transpose the values of a mat2
 *
 * @param {mat2} out the receiving matrix
 * @param {mat2} a the source matrix
 * @returns {mat2} out
 */
mat2.transpose = function (out, a) {
  // If we are transposing ourselves we can skip a few steps but have to cache some values
  if (out === a) {
    let a1 = a.m01;
    out.m01 = a.m02;
    out.m02 = a1;
  } else {
    out.m00 = a.m00;
    out.m01 = a.m02;
    out.m02 = a.m01;
    out.m03 = a.m03;
  }

  return out;
};

/**
 * Inverts a mat2
 *
 * @param {mat2} out the receiving matrix
 * @param {mat2} a the source matrix
 * @returns {mat2} out
 */
mat2.invert = function (out, a) {
  let a0 = a.m00, a1 = a.m01, a2 = a.m02, a3 = a.m03;

  // Calculate the determinant
  let det = a0 * a3 - a2 * a1;

  if (!det) {
    return null;
  }
  det = 1.0 / det;

  out.m00 = a3 * det;
  out.m01 = -a1 * det;
  out.m02 = -a2 * det;
  out.m03 = a0 * det;

  return out;
};

/**
 * Calculates the adjugate of a mat2
 *
 * @param {mat2} out the receiving matrix
 * @param {mat2} a the source matrix
 * @returns {mat2} out
 */
mat2.adjoint = function (out, a) {
  // Caching this value is nessecary if out == a
  let a0 = a.m00;
  out.m00 = a.m03;
  out.m01 = -a.m01;
  out.m02 = -a.m02;
  out.m03 = a0;

  return out;
};

/**
 * Calculates the determinant of a mat2
 *
 * @param {mat2} a the source matrix
 * @returns {Number} determinant of a
 */
mat2.determinant = function (a) {
  return a.m00 * a.m03 - a.m02 * a.m01;
};

/**
 * Multiplies two mat2's
 *
 * @param {mat2} out the receiving matrix
 * @param {mat2} a the first operand
 * @param {mat2} b the second operand
 * @returns {mat2} out
 */
mat2.multiply = function (out, a, b) {
  let a0 = a.m00, a1 = a.m01, a2 = a.m02, a3 = a.m03;
  let b0 = b.m00, b1 = b.m01, b2 = b.m02, b3 = b.m03;
  out.m00 = a0 * b0 + a2 * b1;
  out.m01 = a1 * b0 + a3 * b1;
  out.m02 = a0 * b2 + a2 * b3;
  out.m03 = a1 * b2 + a3 * b3;
  return out;
};

/**
 * Alias for {@link mat2.multiply}
 * @function
 */
mat2.mul = mat2.multiply;

/**
 * Rotates a mat2 by the given angle
 *
 * @param {mat2} out the receiving matrix
 * @param {mat2} a the matrix to rotate
 * @param {Number} rad the angle to rotate the matrix by
 * @returns {mat2} out
 */
mat2.rotate = function (out, a, rad) {
  let a0 = a.m00, a1 = a.m01, a2 = a.m02, a3 = a.m03,
      s = Math.sin(rad),
      c = Math.cos(rad);
  out.m00 = a0 * c + a2 * s;
  out.m01 = a1 * c + a3 * s;
  out.m02 = a0 * -s + a2 * c;
  out.m03 = a1 * -s + a3 * c;
  return out;
};

/**
 * Scales the mat2 by the dimensions in the given vec2
 *
 * @param {mat2} out the receiving matrix
 * @param {mat2} a the matrix to rotate
 * @param {vec2} v the vec2 to scale the matrix by
 * @returns {mat2} out
 **/
mat2.scale = function (out, a, v) {
  let a0 = a.m00, a1 = a.m01, a2 = a.m02, a3 = a.m03,
      v0 = v.x, v1 = v.y;
  out.m00 = a0 * v0;
  out.m01 = a1 * v0;
  out.m02 = a2 * v1;
  out.m03 = a3 * v1;
  return out;
};

/**
 * Creates a matrix from a given angle
 * This is equivalent to (but much faster than):
 *
 *     mat2.identity(dest);
 *     mat2.rotate(dest, dest, rad);
 *
 * @param {mat2} out mat2 receiving operation result
 * @param {Number} rad the angle to rotate the matrix by
 * @returns {mat2} out
 */
mat2.fromRotation = function (out, rad) {
  let s = Math.sin(rad),
      c = Math.cos(rad);
  out.m00 = c;
  out.m01 = s;
  out.m02 = -s;
  out.m03 = c;
  return out;
};

/**
 * Creates a matrix from a vector scaling
 * This is equivalent to (but much faster than):
 *
 *     mat2.identity(dest);
 *     mat2.scale(dest, dest, vec);
 *
 * @param {mat2} out mat2 receiving operation result
 * @param {vec2} v Scaling vector
 * @returns {mat2} out
 */
mat2.fromScaling = function (out, v) {
  out.m00 = v.x;
  out.m01 = 0;
  out.m02 = 0;
  out.m03 = v.y;
  return out;
};

/**
 * Returns a string representation of a mat2
 *
 * @param {mat2} a matrix to represent as a string
 * @returns {String} string representation of the matrix
 */
mat2.str = function (a) {
  return `mat2(${a.m00}, ${a.m01}, ${a.m02}, ${a.m03})`;
};

/**
 * Returns typed array
 *
 * @param {array} out
 * @param {mat2} m
 * @returns {array}
 */
mat2.array = function (out, m) {
  out[0] = m.m00;
  out[1] = m.m01;
  out[2] = m.m02;
  out[3] = m.m03;

  return out;
};

/**
 * Returns Frobenius norm of a mat2
 *
 * @param {mat2} a the matrix to calculate Frobenius norm of
 * @returns {Number} Frobenius norm
 */
mat2.frob = function (a) {
  return (Math.sqrt(Math.pow(a.m00, 2) + Math.pow(a.m01, 2) + Math.pow(a.m02, 2) + Math.pow(a.m03, 2)));
};

/**
 * Returns L, D and U matrices (Lower triangular, Diagonal and Upper triangular) by factorizing the input matrix
 * @param {mat2} L the lower triangular matrix
 * @param {mat2} D the diagonal matrix
 * @param {mat2} U the upper triangular matrix
 * @param {mat2} a the input matrix to factorize
 */

mat2.LDU = function (L, D, U, a) {
  L.m02 = a.m02 / a.m00;
  U.m00 = a.m00;
  U.m01 = a.m01;
  U.m03 = a.m03 - L.m02 * U.m01;
};

/**
 * Adds two mat2's
 *
 * @param {mat2} out the receiving matrix
 * @param {mat2} a the first operand
 * @param {mat2} b the second operand
 * @returns {mat2} out
 */
mat2.add = function (out, a, b) {
  out.m00 = a.m00 + b.m00;
  out.m01 = a.m01 + b.m01;
  out.m02 = a.m02 + b.m02;
  out.m03 = a.m03 + b.m03;
  return out;
};

/**
 * Subtracts matrix b from matrix a
 *
 * @param {mat2} out the receiving matrix
 * @param {mat2} a the first operand
 * @param {mat2} b the second operand
 * @returns {mat2} out
 */
mat2.subtract = function (out, a, b) {
  out.m00 = a.m00 - b.m00;
  out.m01 = a.m01 - b.m01;
  out.m02 = a.m02 - b.m02;
  out.m03 = a.m03 - b.m03;
  return out;
};

/**
 * Alias for {@link mat2.subtract}
 * @function
 */
mat2.sub = mat2.subtract;

/**
 * Returns whether or not the matrices have exactly the same elements in the same position (when compared with ===)
 *
 * @param {mat2} a The first matrix.
 * @param {mat2} b The second matrix.
 * @returns {Boolean} True if the matrices are equal, false otherwise.
 */
mat2.exactEquals = function (a, b) {
  return a.m00 === b.m00 && a.m01 === b.m01 && a.m02 === b.m02 && a.m03 === b.m03;
};

/**
 * Returns whether or not the matrices have approximately the same elements in the same position.
 *
 * @param {mat2} a The first matrix.
 * @param {mat2} b The second matrix.
 * @returns {Boolean} True if the matrices are equal, false otherwise.
 */
mat2.equals = function (a, b) {
  let a0 = a.m00, a1 = a.m01, a2 = a.m02, a3 = a.m03;
  let b0 = b.m00, b1 = b.m01, b2 = b.m02, b3 = b.m03;
  return (
    Math.abs(a0 - b0) <= EPSILON * Math.max(1.0, Math.abs(a0), Math.abs(b0)) &&
    Math.abs(a1 - b1) <= EPSILON * Math.max(1.0, Math.abs(a1), Math.abs(b1)) &&
    Math.abs(a2 - b2) <= EPSILON * Math.max(1.0, Math.abs(a2), Math.abs(b2)) &&
    Math.abs(a3 - b3) <= EPSILON * Math.max(1.0, Math.abs(a3), Math.abs(b3))
  );
};

/**
 * Multiply each element of the matrix by a scalar.
 *
 * @param {mat2} out the receiving matrix
 * @param {mat2} a the matrix to scale
 * @param {Number} b amount to scale the matrix's elements by
 * @returns {mat2} out
 */
mat2.multiplyScalar = function (out, a, b) {
  out.m00 = a.m00 * b;
  out.m01 = a.m01 * b;
  out.m02 = a.m02 * b;
  out.m03 = a.m03 * b;
  return out;
};

/**
 * Adds two mat2's after multiplying each element of the second operand by a scalar value.
 *
 * @param {mat2} out the receiving vector
 * @param {mat2} a the first operand
 * @param {mat2} b the second operand
 * @param {Number} scale the amount to scale b's elements by before adding
 * @returns {mat2} out
 */
mat2.multiplyScalarAndAdd = function (out, a, b, scale) {
  out.m00 = a.m00 + (b.m00 * scale);
  out.m01 = a.m01 + (b.m01 * scale);
  out.m02 = a.m02 + (b.m02 * scale);
  out.m03 = a.m03 + (b.m03 * scale);
  return out;
};

let _tmp$6 = new Array(6);

class _mat23 {
  constructor(m00, m01, m02, m03, m04, m05) {
    this.m00 = m00;
    this.m01 = m01;
    this.m02 = m02;
    this.m03 = m03;
    this.m04 = m04;
    this.m05 = m05;
  }

  toJSON() {
    _tmp$6[0] = this.m00;
    _tmp$6[1] = this.m01;
    _tmp$6[2] = this.m02;
    _tmp$6[3] = this.m03;
    _tmp$6[4] = this.m04;
    _tmp$6[5] = this.m05;

    return _tmp$6;
  }
}

/**
 * @class 2x3 Matrix
 * @name mat23
 *
 * @description
 * A mat23 contains six elements defined as:
 * <pre>
 * [a, c, tx,
 *  b, d, ty]
 * </pre>
 * This is a short form for the 3x3 matrix:
 * <pre>
 * [a, c, tx,
 *  b, d, ty,
 *  0, 0, 1]
 * </pre>
 * The last row is ignored so the array is shorter and operations are faster.
 */
let mat23 = {};

/**
 * Creates a new identity mat23
 *
 * @returns {mat23} a new 2x3 matrix
 */
mat23.create = function () {
  return new _mat23(
    1, 0,
    0, 1,
    0, 0
  );
};

/**
 * Create a new mat23 with the given values
 *
 * @param {Number} a Component A (index 0)
 * @param {Number} b Component B (index 1)
 * @param {Number} c Component C (index 2)
 * @param {Number} d Component D (index 3)
 * @param {Number} tx Component TX (index 4)
 * @param {Number} ty Component TY (index 5)
 * @returns {mat23} A new mat23
 */
mat23.new = function (a, b, c, d, tx, ty) {
  return new _mat23(
    a, b,
    c, d,
    tx, ty
  );
};

/**
 * Creates a new mat23 initialized with values from an existing matrix
 *
 * @param {mat23} a matrix to clone
 * @returns {mat23} a new 2x3 matrix
 */
mat23.clone = function (a) {
  return new _mat23(
    a.m00, a.m01,
    a.m02, a.m03,
    a.m04, a.m05
  );
};

/**
 * Copy the values from one mat23 to another
 *
 * @param {mat23} out the receiving matrix
 * @param {mat23} a the source matrix
 * @returns {mat23} out
 */
mat23.copy = function (out, a) {
  out.m00 = a.m00;
  out.m01 = a.m01;
  out.m02 = a.m02;
  out.m03 = a.m03;
  out.m04 = a.m04;
  out.m05 = a.m05;
  return out;
};

/**
 * Set a mat23 to the identity matrix
 *
 * @param {mat23} out the receiving matrix
 * @returns {mat23} out
 */
mat23.identity = function (out) {
  out.m00 = 1;
  out.m01 = 0;
  out.m02 = 0;
  out.m03 = 1;
  out.m04 = 0;
  out.m05 = 0;
  return out;
};

/**
 * Set the components of a mat23 to the given values
 *
 * @param {mat23} out the receiving matrix
 * @param {Number} a Component A (index 0)
 * @param {Number} b Component B (index 1)
 * @param {Number} c Component C (index 2)
 * @param {Number} d Component D (index 3)
 * @param {Number} tx Component TX (index 4)
 * @param {Number} ty Component TY (index 5)
 * @returns {mat23} out
 */
mat23.set = function (out, a, b, c, d, tx, ty) {
  out.m00 = a;
  out.m01 = b;
  out.m02 = c;
  out.m03 = d;
  out.m04 = tx;
  out.m05 = ty;
  return out;
};

/**
 * Inverts a mat23
 *
 * @param {mat23} out the receiving matrix
 * @param {mat23} a the source matrix
 * @returns {mat23} out
 */
mat23.invert = function (out, a) {
  let aa = a.m00, ab = a.m01, ac = a.m02, ad = a.m03,
    atx = a.m04, aty = a.m05;

  let det = aa * ad - ab * ac;
  if (!det) {
    return null;
  }
  det = 1.0 / det;

  out.m00 = ad * det;
  out.m01 = -ab * det;
  out.m02 = -ac * det;
  out.m03 = aa * det;
  out.m04 = (ac * aty - ad * atx) * det;
  out.m05 = (ab * atx - aa * aty) * det;
  return out;
};

/**
 * Calculates the determinant of a mat23
 *
 * @param {mat23} a the source matrix
 * @returns {Number} determinant of a
 */
mat23.determinant = function (a) {
  return a.m00 * a.m03 - a.m01 * a.m02;
};

/**
 * Multiplies two mat23's
 *
 * @param {mat23} out the receiving matrix
 * @param {mat23} a the first operand
 * @param {mat23} b the second operand
 * @returns {mat23} out
 */
mat23.multiply = function (out, a, b) {
  let a0 = a.m00, a1 = a.m01, a2 = a.m02, a3 = a.m03, a4 = a.m04, a5 = a.m05,
    b0 = b.m00, b1 = b.m01, b2 = b.m02, b3 = b.m03, b4 = b.m04, b5 = b.m05;
  out.m00 = a0 * b0 + a2 * b1;
  out.m01 = a1 * b0 + a3 * b1;
  out.m02 = a0 * b2 + a2 * b3;
  out.m03 = a1 * b2 + a3 * b3;
  out.m04 = a0 * b4 + a2 * b5 + a4;
  out.m05 = a1 * b4 + a3 * b5 + a5;
  return out;
};

/**
 * Alias for {@link mat23.multiply}
 * @function
 */
mat23.mul = mat23.multiply;

/**
 * Rotates a mat23 by the given angle
 *
 * @param {mat23} out the receiving matrix
 * @param {mat23} a the matrix to rotate
 * @param {Number} rad the angle to rotate the matrix by
 * @returns {mat23} out
 */
mat23.rotate = function (out, a, rad) {
  let a0 = a.m00, a1 = a.m01, a2 = a.m02, a3 = a.m03, a4 = a.m04, a5 = a.m05,
    s = Math.sin(rad),
    c = Math.cos(rad);
  out.m00 = a0 * c + a2 * s;
  out.m01 = a1 * c + a3 * s;
  out.m02 = a0 * -s + a2 * c;
  out.m03 = a1 * -s + a3 * c;
  out.m04 = a4;
  out.m05 = a5;
  return out;
};

/**
 * Scales the mat23 by the dimensions in the given vec2
 *
 * @param {mat23} out the receiving matrix
 * @param {mat23} a the matrix to translate
 * @param {vec2} v the vec2 to scale the matrix by
 * @returns {mat23} out
 **/
mat23.scale = function (out, a, v) {
  let a0 = a.m00, a1 = a.m01, a2 = a.m02, a3 = a.m03, a4 = a.m04, a5 = a.m05,
    v0 = v.x, v1 = v.y;
  out.m00 = a0 * v0;
  out.m01 = a1 * v0;
  out.m02 = a2 * v1;
  out.m03 = a3 * v1;
  out.m04 = a4;
  out.m05 = a5;
  return out;
};

/**
 * Translates the mat23 by the dimensions in the given vec2
 *
 * @param {mat23} out the receiving matrix
 * @param {mat23} a the matrix to translate
 * @param {vec2} v the vec2 to translate the matrix by
 * @returns {mat23} out
 **/
mat23.translate = function (out, a, v) {
  let a0 = a.m00, a1 = a.m01, a2 = a.m02, a3 = a.m03, a4 = a.m04, a5 = a.m05,
    v0 = v.x, v1 = v.y;
  out.m00 = a0;
  out.m01 = a1;
  out.m02 = a2;
  out.m03 = a3;
  out.m04 = a0 * v0 + a2 * v1 + a4;
  out.m05 = a1 * v0 + a3 * v1 + a5;
  return out;
};

/**
 * Creates a matrix from a given angle
 * This is equivalent to (but much faster than):
 *
 *     mat23.identity(dest);
 *     mat23.rotate(dest, dest, rad);
 *
 * @param {mat23} out mat23 receiving operation result
 * @param {Number} rad the angle to rotate the matrix by
 * @returns {mat23} out
 */
mat23.fromRotation = function (out, rad) {
  let s = Math.sin(rad), c = Math.cos(rad);
  out.m00 = c;
  out.m01 = s;
  out.m02 = -s;
  out.m03 = c;
  out.m04 = 0;
  out.m05 = 0;
  return out;
};

/**
 * Creates a matrix from a vector scaling
 * This is equivalent to (but much faster than):
 *
 *     mat23.identity(dest);
 *     mat23.scale(dest, dest, vec);
 *
 * @param {mat23} out mat23 receiving operation result
 * @param {vec2} v Scaling vector
 * @returns {mat23} out
 */
mat23.fromScaling = function (out, v) {
  out.m00 = v.m00;
  out.m01 = 0;
  out.m02 = 0;
  out.m03 = v.m01;
  out.m04 = 0;
  out.m05 = 0;
  return out;
};

/**
 * Creates a matrix from a vector translation
 * This is equivalent to (but much faster than):
 *
 *     mat23.identity(dest);
 *     mat23.translate(dest, dest, vec);
 *
 * @param {mat23} out mat23 receiving operation result
 * @param {vec2} v Translation vector
 * @returns {mat23} out
 */
mat23.fromTranslation = function (out, v) {
  out.m00 = 1;
  out.m01 = 0;
  out.m02 = 0;
  out.m03 = 1;
  out.m04 = v.x;
  out.m05 = v.y;
  return out;
};

/**
 * Returns a string representation of a mat23
 *
 * @param {mat23} a matrix to represent as a string
 * @returns {String} string representation of the matrix
 */
mat23.str = function (a) {
  return `mat23(${a.m00}, ${a.m01}, ${a.m02}, ${a.m03}, ${a.m04}, ${a.m05})`;
};

/**
 * Returns typed array
 *
 * @param {array} out
 * @param {mat23} m
 * @returns {array}
 */
mat23.array = function (out, m) {
  out[0] = m.m00;
  out[1] = m.m01;
  out[2] = m.m02;
  out[3] = m.m03;
  out[4] = m.m04;
  out[5] = m.m05;

  return out;
};

/**
 * Returns typed array to 16 float array
 *
 * @param {array} out
 * @param {mat23} m
 * @returns {array}
 */
mat23.array4x4 = function (out, m) {
  out[0] = m.m00;
  out[1] = m.m01;
  out[2] = 0;
  out[3] = 0;
  out[4] = m.m02;
  out[5] = m.m03;
  out[6] = 0;
  out[7] = 0;
  out[8] = 0;
  out[9] = 0;
  out[10] = 1;
  out[11] = 0;
  out[12] = m.m04;
  out[13] = m.m05;
  out[14] = 0;
  out[15] = 1;

  return out;
};

/**
 * Returns Frobenius norm of a mat23
 *
 * @param {mat23} a the matrix to calculate Frobenius norm of
 * @returns {Number} Frobenius norm
 */
mat23.frob = function (a) {
  return (Math.sqrt(Math.pow(a.m00, 2) + Math.pow(a.m01, 2) + Math.pow(a.m02, 2) + Math.pow(a.m03, 2) + Math.pow(a.m04, 2) + Math.pow(a.m05, 2) + 1));
};

/**
 * Adds two mat23's
 *
 * @param {mat23} out the receiving matrix
 * @param {mat23} a the first operand
 * @param {mat23} b the second operand
 * @returns {mat23} out
 */
mat23.add = function (out, a, b) {
  out.m00 = a.m00 + b.m00;
  out.m01 = a.m01 + b.m01;
  out.m02 = a.m02 + b.m02;
  out.m03 = a.m03 + b.m03;
  out.m04 = a.m04 + b.m04;
  out.m05 = a.m05 + b.m05;
  return out;
};

/**
 * Subtracts matrix b from matrix a
 *
 * @param {mat23} out the receiving matrix
 * @param {mat23} a the first operand
 * @param {mat23} b the second operand
 * @returns {mat23} out
 */
mat23.subtract = function (out, a, b) {
  out.m00 = a.m00 - b.m00;
  out.m01 = a.m01 - b.m01;
  out.m02 = a.m02 - b.m02;
  out.m03 = a.m03 - b.m03;
  out.m04 = a.m04 - b.m04;
  out.m05 = a.m05 - b.m05;
  return out;
};

/**
 * Alias for {@link mat23.subtract}
 * @function
 */
mat23.sub = mat23.subtract;

/**
 * Multiply each element of the matrix by a scalar.
 *
 * @param {mat23} out the receiving matrix
 * @param {mat23} a the matrix to scale
 * @param {Number} b amount to scale the matrix's elements by
 * @returns {mat23} out
 */
mat23.multiplyScalar = function (out, a, b) {
  out.m00 = a.m00 * b;
  out.m01 = a.m01 * b;
  out.m02 = a.m02 * b;
  out.m03 = a.m03 * b;
  out.m04 = a.m04 * b;
  out.m05 = a.m05 * b;
  return out;
};

/**
 * Adds two mat23's after multiplying each element of the second operand by a scalar value.
 *
 * @param {mat23} out the receiving vector
 * @param {mat23} a the first operand
 * @param {mat23} b the second operand
 * @param {Number} scale the amount to scale b's elements by before adding
 * @returns {mat23} out
 */
mat23.multiplyScalarAndAdd = function (out, a, b, scale) {
  out.m00 = a.m00 + (b.m00 * scale);
  out.m01 = a.m01 + (b.m01 * scale);
  out.m02 = a.m02 + (b.m02 * scale);
  out.m03 = a.m03 + (b.m03 * scale);
  out.m04 = a.m04 + (b.m04 * scale);
  out.m05 = a.m05 + (b.m05 * scale);
  return out;
};

/**
 * Returns whether or not the matrices have exactly the same elements in the same position (when compared with ===)
 *
 * @param {mat23} a The first matrix.
 * @param {mat23} b The second matrix.
 * @returns {Boolean} True if the matrices are equal, false otherwise.
 */
mat23.exactEquals = function (a, b) {
  return a.m00 === b.m00 && a.m01 === b.m01 && a.m02 === b.m02 && a.m03 === b.m03 && a.m04 === b.m04 && a.m05 === b.m05;
};

/**
 * Returns whether or not the matrices have approximately the same elements in the same position.
 *
 * @param {mat23} a The first matrix.
 * @param {mat23} b The second matrix.
 * @returns {Boolean} True if the matrices are equal, false otherwise.
 */
mat23.equals = function (a, b) {
  let a0 = a.m00, a1 = a.m01, a2 = a.m02, a3 = a.m03, a4 = a.m04, a5 = a.m05;
  let b0 = b.m00, b1 = b.m01, b2 = b.m02, b3 = b.m03, b4 = b.m04, b5 = b.m05;
  return (
    Math.abs(a0 - b0) <= EPSILON * Math.max(1.0, Math.abs(a0), Math.abs(b0)) &&
    Math.abs(a1 - b1) <= EPSILON * Math.max(1.0, Math.abs(a1), Math.abs(b1)) &&
    Math.abs(a2 - b2) <= EPSILON * Math.max(1.0, Math.abs(a2), Math.abs(b2)) &&
    Math.abs(a3 - b3) <= EPSILON * Math.max(1.0, Math.abs(a3), Math.abs(b3)) &&
    Math.abs(a4 - b4) <= EPSILON * Math.max(1.0, Math.abs(a4), Math.abs(b4)) &&
    Math.abs(a5 - b5) <= EPSILON * Math.max(1.0, Math.abs(a5), Math.abs(b5))
  );
};

let _tmp$7 = new Array(16);

class _mat4 {
  constructor(
    m00, m01, m02, m03,
    m04, m05, m06, m07,
    m08, m09, m10, m11,
    m12, m13, m14, m15
  ) {
    this.m00 = m00;
    this.m01 = m01;
    this.m02 = m02;
    this.m03 = m03;
    this.m04 = m04;
    this.m05 = m05;
    this.m06 = m06;
    this.m07 = m07;
    this.m08 = m08;
    this.m09 = m09;
    this.m10 = m10;
    this.m11 = m11;
    this.m12 = m12;
    this.m13 = m13;
    this.m14 = m14;
    this.m15 = m15;
  }

  toJSON() {
    _tmp$7[0] = this.m00;
    _tmp$7[1] = this.m01;
    _tmp$7[2] = this.m02;
    _tmp$7[3] = this.m03;
    _tmp$7[4] = this.m04;
    _tmp$7[5] = this.m05;
    _tmp$7[6] = this.m06;
    _tmp$7[7] = this.m07;
    _tmp$7[8] = this.m08;
    _tmp$7[9] = this.m09;
    _tmp$7[10] = this.m10;
    _tmp$7[11] = this.m11;
    _tmp$7[12] = this.m12;
    _tmp$7[13] = this.m13;
    _tmp$7[14] = this.m14;
    _tmp$7[15] = this.m15;

    return _tmp$7;
  }
}

/**
 * @class 4x4 Matrix
 * @name mat4
 *
 * NOTE: we use column-major matrix for all matrix calculation.
 *
 * This may lead to some confusion when referencing OpenGL documentation,
 * however, which represents out all matricies in column-major format.
 * This means that while in code a matrix may be typed out as:
 *
 * [1, 0, 0, 0,
 *  0, 1, 0, 0,
 *  0, 0, 1, 0,
 *  x, y, z, 0]
 *
 * The same matrix in the [OpenGL documentation](https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glTranslate.xml)
 * is written as:
 *
 *  1 0 0 x
 *  0 1 0 y
 *  0 0 1 z
 *  0 0 0 0
 *
 * Please rest assured, however, that they are the same thing!
 * This is not unique to glMatrix, either, as OpenGL developers have long been confused by the
 * apparent lack of consistency between the memory layout and the documentation.
 */
let mat4 = {};

/**
 * Creates a new identity mat4
 *
 * @returns {mat4} a new 4x4 matrix
 */
mat4.create = function () {
  return new _mat4(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  );
};

/**
 * Create a new mat4 with the given values
 *
 * @param {Number} m00 Component in column 0, row 0 position (index 0)
 * @param {Number} m01 Component in column 0, row 1 position (index 1)
 * @param {Number} m02 Component in column 0, row 2 position (index 2)
 * @param {Number} m03 Component in column 0, row 3 position (index 3)
 * @param {Number} m10 Component in column 1, row 0 position (index 4)
 * @param {Number} m11 Component in column 1, row 1 position (index 5)
 * @param {Number} m12 Component in column 1, row 2 position (index 6)
 * @param {Number} m13 Component in column 1, row 3 position (index 7)
 * @param {Number} m20 Component in column 2, row 0 position (index 8)
 * @param {Number} m21 Component in column 2, row 1 position (index 9)
 * @param {Number} m22 Component in column 2, row 2 position (index 10)
 * @param {Number} m23 Component in column 2, row 3 position (index 11)
 * @param {Number} m30 Component in column 3, row 0 position (index 12)
 * @param {Number} m31 Component in column 3, row 1 position (index 13)
 * @param {Number} m32 Component in column 3, row 2 position (index 14)
 * @param {Number} m33 Component in column 3, row 3 position (index 15)
 * @returns {mat4} A new mat4
 */
mat4.new = function (m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33) {
  return new _mat4(
    m00, m01, m02, m03,
    m10, m11, m12, m13,
    m20, m21, m22, m23,
    m30, m31, m32, m33
  );
};

/**
 * Creates a new mat4 initialized with values from an existing matrix
 *
 * @param {mat4} a matrix to clone
 * @returns {mat4} a new 4x4 matrix
 */
mat4.clone = function (a) {
  return new _mat4(
    a.m00, a.m01, a.m02, a.m03,
    a.m04, a.m05, a.m06, a.m07,
    a.m08, a.m09, a.m10, a.m11,
    a.m12, a.m13, a.m14, a.m15
  );
};

/**
 * Copy the values from one mat4 to another
 *
 * @param {mat4} out the receiving matrix
 * @param {mat4} a the source matrix
 * @returns {mat4} out
 */
mat4.copy = function (out, a) {
  out.m00 = a.m00;
  out.m01 = a.m01;
  out.m02 = a.m02;
  out.m03 = a.m03;
  out.m04 = a.m04;
  out.m05 = a.m05;
  out.m06 = a.m06;
  out.m07 = a.m07;
  out.m08 = a.m08;
  out.m09 = a.m09;
  out.m10 = a.m10;
  out.m11 = a.m11;
  out.m12 = a.m12;
  out.m13 = a.m13;
  out.m14 = a.m14;
  out.m15 = a.m15;
  return out;
};

/**
 * Set the components of a mat4 to the given values
 *
 * @param {mat4} out the receiving matrix
 * @param {Number} m00 Component in column 0, row 0 position (index 0)
 * @param {Number} m01 Component in column 0, row 1 position (index 1)
 * @param {Number} m02 Component in column 0, row 2 position (index 2)
 * @param {Number} m03 Component in column 0, row 3 position (index 3)
 * @param {Number} m10 Component in column 1, row 0 position (index 4)
 * @param {Number} m11 Component in column 1, row 1 position (index 5)
 * @param {Number} m12 Component in column 1, row 2 position (index 6)
 * @param {Number} m13 Component in column 1, row 3 position (index 7)
 * @param {Number} m20 Component in column 2, row 0 position (index 8)
 * @param {Number} m21 Component in column 2, row 1 position (index 9)
 * @param {Number} m22 Component in column 2, row 2 position (index 10)
 * @param {Number} m23 Component in column 2, row 3 position (index 11)
 * @param {Number} m30 Component in column 3, row 0 position (index 12)
 * @param {Number} m31 Component in column 3, row 1 position (index 13)
 * @param {Number} m32 Component in column 3, row 2 position (index 14)
 * @param {Number} m33 Component in column 3, row 3 position (index 15)
 * @returns {mat4} out
 */
mat4.set = function (out, m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33) {
  out.m00 = m00;
  out.m01 = m01;
  out.m02 = m02;
  out.m03 = m03;
  out.m04 = m10;
  out.m05 = m11;
  out.m06 = m12;
  out.m07 = m13;
  out.m08 = m20;
  out.m09 = m21;
  out.m10 = m22;
  out.m11 = m23;
  out.m12 = m30;
  out.m13 = m31;
  out.m14 = m32;
  out.m15 = m33;
  return out;
};


/**
 * Set a mat4 to the identity matrix
 *
 * @param {mat4} out the receiving matrix
 * @returns {mat4} out
 */
mat4.identity = function (out) {
  out.m00 = 1;
  out.m01 = 0;
  out.m02 = 0;
  out.m03 = 0;
  out.m04 = 0;
  out.m05 = 1;
  out.m06 = 0;
  out.m07 = 0;
  out.m08 = 0;
  out.m09 = 0;
  out.m10 = 1;
  out.m11 = 0;
  out.m12 = 0;
  out.m13 = 0;
  out.m14 = 0;
  out.m15 = 1;
  return out;
};

/**
 * Transpose the values of a mat4
 *
 * @param {mat4} out the receiving matrix
 * @param {mat4} a the source matrix
 * @returns {mat4} out
 */
mat4.transpose = function (out, a) {
  // If we are transposing ourselves we can skip a few steps but have to cache some values
  if (out === a) {
    let a01 = a.m01, a02 = a.m02, a03 = a.m03,
        a12 = a.m06, a13 = a.m07,
        a23 = a.m11;

    out.m01 = a.m04;
    out.m02 = a.m08;
    out.m03 = a.m12;
    out.m04 = a01;
    out.m06 = a.m09;
    out.m07 = a.m13;
    out.m08 = a02;
    out.m09 = a12;
    out.m11 = a.m14;
    out.m12 = a03;
    out.m13 = a13;
    out.m14 = a23;
  } else {
    out.m00 = a.m00;
    out.m01 = a.m04;
    out.m02 = a.m08;
    out.m03 = a.m12;
    out.m04 = a.m01;
    out.m05 = a.m05;
    out.m06 = a.m09;
    out.m07 = a.m13;
    out.m08 = a.m02;
    out.m09 = a.m06;
    out.m10 = a.m10;
    out.m11 = a.m14;
    out.m12 = a.m03;
    out.m13 = a.m07;
    out.m14 = a.m11;
    out.m15 = a.m15;
  }

  return out;
};

/**
 * Inverts a mat4
 *
 * @param {mat4} out the receiving matrix
 * @param {mat4} a the source matrix
 * @returns {mat4} out
 */
mat4.invert = function (out, a) {
  let a00 = a.m00, a01 = a.m01, a02 = a.m02, a03 = a.m03,
      a10 = a.m04, a11 = a.m05, a12 = a.m06, a13 = a.m07,
      a20 = a.m08, a21 = a.m09, a22 = a.m10, a23 = a.m11,
      a30 = a.m12, a31 = a.m13, a32 = a.m14, a33 = a.m15;

  let b00 = a00 * a11 - a01 * a10;
  let b01 = a00 * a12 - a02 * a10;
  let b02 = a00 * a13 - a03 * a10;
  let b03 = a01 * a12 - a02 * a11;
  let b04 = a01 * a13 - a03 * a11;
  let b05 = a02 * a13 - a03 * a12;
  let b06 = a20 * a31 - a21 * a30;
  let b07 = a20 * a32 - a22 * a30;
  let b08 = a20 * a33 - a23 * a30;
  let b09 = a21 * a32 - a22 * a31;
  let b10 = a21 * a33 - a23 * a31;
  let b11 = a22 * a33 - a23 * a32;

  // Calculate the determinant
  let det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;

  if (!det) {
    return null;
  }
  det = 1.0 / det;

  out.m00 = (a11 * b11 - a12 * b10 + a13 * b09) * det;
  out.m01 = (a02 * b10 - a01 * b11 - a03 * b09) * det;
  out.m02 = (a31 * b05 - a32 * b04 + a33 * b03) * det;
  out.m03 = (a22 * b04 - a21 * b05 - a23 * b03) * det;
  out.m04 = (a12 * b08 - a10 * b11 - a13 * b07) * det;
  out.m05 = (a00 * b11 - a02 * b08 + a03 * b07) * det;
  out.m06 = (a32 * b02 - a30 * b05 - a33 * b01) * det;
  out.m07 = (a20 * b05 - a22 * b02 + a23 * b01) * det;
  out.m08 = (a10 * b10 - a11 * b08 + a13 * b06) * det;
  out.m09 = (a01 * b08 - a00 * b10 - a03 * b06) * det;
  out.m10 = (a30 * b04 - a31 * b02 + a33 * b00) * det;
  out.m11 = (a21 * b02 - a20 * b04 - a23 * b00) * det;
  out.m12 = (a11 * b07 - a10 * b09 - a12 * b06) * det;
  out.m13 = (a00 * b09 - a01 * b07 + a02 * b06) * det;
  out.m14 = (a31 * b01 - a30 * b03 - a32 * b00) * det;
  out.m15 = (a20 * b03 - a21 * b01 + a22 * b00) * det;

  return out;
};

/**
 * Calculates the adjugate of a mat4
 *
 * @param {mat4} out the receiving matrix
 * @param {mat4} a the source matrix
 * @returns {mat4} out
 */
mat4.adjoint = function (out, a) {
  let a00 = a.m00, a01 = a.m01, a02 = a.m02, a03 = a.m03,
      a10 = a.m04, a11 = a.m05, a12 = a.m06, a13 = a.m07,
      a20 = a.m08, a21 = a.m09, a22 = a.m10, a23 = a.m11,
      a30 = a.m12, a31 = a.m13, a32 = a.m14, a33 = a.m15;

  out.m00 = (a11 * (a22 * a33 - a23 * a32) - a21 * (a12 * a33 - a13 * a32) + a31 * (a12 * a23 - a13 * a22));
  out.m01 = -(a01 * (a22 * a33 - a23 * a32) - a21 * (a02 * a33 - a03 * a32) + a31 * (a02 * a23 - a03 * a22));
  out.m02 = (a01 * (a12 * a33 - a13 * a32) - a11 * (a02 * a33 - a03 * a32) + a31 * (a02 * a13 - a03 * a12));
  out.m03 = -(a01 * (a12 * a23 - a13 * a22) - a11 * (a02 * a23 - a03 * a22) + a21 * (a02 * a13 - a03 * a12));
  out.m04 = -(a10 * (a22 * a33 - a23 * a32) - a20 * (a12 * a33 - a13 * a32) + a30 * (a12 * a23 - a13 * a22));
  out.m05 = (a00 * (a22 * a33 - a23 * a32) - a20 * (a02 * a33 - a03 * a32) + a30 * (a02 * a23 - a03 * a22));
  out.m06 = -(a00 * (a12 * a33 - a13 * a32) - a10 * (a02 * a33 - a03 * a32) + a30 * (a02 * a13 - a03 * a12));
  out.m07 = (a00 * (a12 * a23 - a13 * a22) - a10 * (a02 * a23 - a03 * a22) + a20 * (a02 * a13 - a03 * a12));
  out.m08 = (a10 * (a21 * a33 - a23 * a31) - a20 * (a11 * a33 - a13 * a31) + a30 * (a11 * a23 - a13 * a21));
  out.m09 = -(a00 * (a21 * a33 - a23 * a31) - a20 * (a01 * a33 - a03 * a31) + a30 * (a01 * a23 - a03 * a21));
  out.m10 = (a00 * (a11 * a33 - a13 * a31) - a10 * (a01 * a33 - a03 * a31) + a30 * (a01 * a13 - a03 * a11));
  out.m11 = -(a00 * (a11 * a23 - a13 * a21) - a10 * (a01 * a23 - a03 * a21) + a20 * (a01 * a13 - a03 * a11));
  out.m12 = -(a10 * (a21 * a32 - a22 * a31) - a20 * (a11 * a32 - a12 * a31) + a30 * (a11 * a22 - a12 * a21));
  out.m13 = (a00 * (a21 * a32 - a22 * a31) - a20 * (a01 * a32 - a02 * a31) + a30 * (a01 * a22 - a02 * a21));
  out.m14 = -(a00 * (a11 * a32 - a12 * a31) - a10 * (a01 * a32 - a02 * a31) + a30 * (a01 * a12 - a02 * a11));
  out.m15 = (a00 * (a11 * a22 - a12 * a21) - a10 * (a01 * a22 - a02 * a21) + a20 * (a01 * a12 - a02 * a11));
  return out;
};

/**
 * Calculates the determinant of a mat4
 *
 * @param {mat4} a the source matrix
 * @returns {Number} determinant of a
 */
mat4.determinant = function (a) {
  let a00 = a.m00, a01 = a.m01, a02 = a.m02, a03 = a.m03,
      a10 = a.m04, a11 = a.m05, a12 = a.m06, a13 = a.m07,
      a20 = a.m08, a21 = a.m09, a22 = a.m10, a23 = a.m11,
      a30 = a.m12, a31 = a.m13, a32 = a.m14, a33 = a.m15;

  let b00 = a00 * a11 - a01 * a10;
  let b01 = a00 * a12 - a02 * a10;
  let b02 = a00 * a13 - a03 * a10;
  let b03 = a01 * a12 - a02 * a11;
  let b04 = a01 * a13 - a03 * a11;
  let b05 = a02 * a13 - a03 * a12;
  let b06 = a20 * a31 - a21 * a30;
  let b07 = a20 * a32 - a22 * a30;
  let b08 = a20 * a33 - a23 * a30;
  let b09 = a21 * a32 - a22 * a31;
  let b10 = a21 * a33 - a23 * a31;
  let b11 = a22 * a33 - a23 * a32;

  // Calculate the determinant
  return b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;
};

/**
 * Multiplies two mat4's explicitly
 *
 * @param {mat4} out the receiving matrix
 * @param {mat4} a the first operand
 * @param {mat4} b the second operand
 * @returns {mat4} out
 */
mat4.multiply = function (out, a, b) {
  let a00 = a.m00, a01 = a.m01, a02 = a.m02, a03 = a.m03,
      a10 = a.m04, a11 = a.m05, a12 = a.m06, a13 = a.m07,
      a20 = a.m08, a21 = a.m09, a22 = a.m10, a23 = a.m11,
      a30 = a.m12, a31 = a.m13, a32 = a.m14, a33 = a.m15;

  // Cache only the current line of the second matrix
  let b0 = b.m00, b1 = b.m01, b2 = b.m02, b3 = b.m03;
  out.m00 = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
  out.m01 = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
  out.m02 = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
  out.m03 = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;

  b0 = b.m04; b1 = b.m05; b2 = b.m06; b3 = b.m07;
  out.m04 = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
  out.m05 = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
  out.m06 = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
  out.m07 = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;

  b0 = b.m08; b1 = b.m09; b2 = b.m10; b3 = b.m11;
  out.m08 = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
  out.m09 = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
  out.m10 = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
  out.m11 = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;

  b0 = b.m12; b1 = b.m13; b2 = b.m14; b3 = b.m15;
  out.m12 = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
  out.m13 = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
  out.m14 = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
  out.m15 = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;
  return out;
};

/**
 * Alias for {@link mat4.multiply}
 * @function
 */
mat4.mul = mat4.multiply;

/**
 * Translate a mat4 by the given vector
 *
 * @param {mat4} out the receiving matrix
 * @param {mat4} a the matrix to translate
 * @param {vec3} v vector to translate by
 * @returns {mat4} out
 */
mat4.translate = function (out, a, v) {
  let x = v.x, y = v.y, z = v.z,
      a00, a01, a02, a03,
      a10, a11, a12, a13,
      a20, a21, a22, a23;

  if (a === out) {
    out.m12 = a.m00 * x + a.m04 * y + a.m08 * z + a.m12;
    out.m13 = a.m01 * x + a.m05 * y + a.m09 * z + a.m13;
    out.m14 = a.m02 * x + a.m06 * y + a.m10 * z + a.m14;
    out.m15 = a.m03 * x + a.m07 * y + a.m11 * z + a.m15;
  } else {
    a00 = a.m00; a01 = a.m01; a02 = a.m02; a03 = a.m03;
    a10 = a.m04; a11 = a.m05; a12 = a.m06; a13 = a.m07;
    a20 = a.m08; a21 = a.m09; a22 = a.m10; a23 = a.m11;

    out.m00 = a00; out.m01 = a01; out.m02 = a02; out.m03 = a03;
    out.m04 = a10; out.m05 = a11; out.m06 = a12; out.m07 = a13;
    out.m08 = a20; out.m09 = a21; out.m10 = a22; out.m11 = a23;

    out.m12 = a00 * x + a10 * y + a20 * z + a.m12;
    out.m13 = a01 * x + a11 * y + a21 * z + a.m13;
    out.m14 = a02 * x + a12 * y + a22 * z + a.m14;
    out.m15 = a03 * x + a13 * y + a23 * z + a.m15;
  }

  return out;
};

/**
 * Scales the mat4 by the dimensions in the given vec3
 *
 * @param {mat4} out the receiving matrix
 * @param {mat4} a the matrix to scale
 * @param {vec3} v the vec3 to scale the matrix by
 * @returns {mat4} out
 **/
mat4.scale = function (out, a, v) {
  let x = v.x, y = v.y, z = v.z;

  out.m00 = a.m00 * x;
  out.m01 = a.m01 * x;
  out.m02 = a.m02 * x;
  out.m03 = a.m03 * x;
  out.m04 = a.m04 * y;
  out.m05 = a.m05 * y;
  out.m06 = a.m06 * y;
  out.m07 = a.m07 * y;
  out.m08 = a.m08 * z;
  out.m09 = a.m09 * z;
  out.m10 = a.m10 * z;
  out.m11 = a.m11 * z;
  out.m12 = a.m12;
  out.m13 = a.m13;
  out.m14 = a.m14;
  out.m15 = a.m15;
  return out;
};

/**
 * Rotates a mat4 by the given angle around the given axis
 *
 * @param {mat4} out the receiving matrix
 * @param {mat4} a the matrix to rotate
 * @param {Number} rad the angle to rotate the matrix by
 * @param {vec3} axis the axis to rotate around
 * @returns {mat4} out
 */
mat4.rotate = function (out, a, rad, axis) {
  let x = axis.x, y = axis.y, z = axis.z;
  let s, c, t,
      a00, a01, a02, a03,
      a10, a11, a12, a13,
      a20, a21, a22, a23,
      b00, b01, b02,
      b10, b11, b12,
      b20, b21, b22;

  let len = Math.sqrt(x * x + y * y + z * z);

  if (Math.abs(len) < EPSILON) {
    return null;
  }

  len = 1 / len;
  x *= len;
  y *= len;
  z *= len;

  s = Math.sin(rad);
  c = Math.cos(rad);
  t = 1 - c;

  a00 = a.m00; a01 = a.m01; a02 = a.m02; a03 = a.m03;
  a10 = a.m04; a11 = a.m05; a12 = a.m06; a13 = a.m07;
  a20 = a.m08; a21 = a.m09; a22 = a.m10; a23 = a.m11;

  // Construct the elements of the rotation matrix
  b00 = x * x * t + c; b01 = y * x * t + z * s; b02 = z * x * t - y * s;
  b10 = x * y * t - z * s; b11 = y * y * t + c; b12 = z * y * t + x * s;
  b20 = x * z * t + y * s; b21 = y * z * t - x * s; b22 = z * z * t + c;

  // Perform rotation-specific matrix multiplication
  out.m00 = a00 * b00 + a10 * b01 + a20 * b02;
  out.m01 = a01 * b00 + a11 * b01 + a21 * b02;
  out.m02 = a02 * b00 + a12 * b01 + a22 * b02;
  out.m03 = a03 * b00 + a13 * b01 + a23 * b02;
  out.m04 = a00 * b10 + a10 * b11 + a20 * b12;
  out.m05 = a01 * b10 + a11 * b11 + a21 * b12;
  out.m06 = a02 * b10 + a12 * b11 + a22 * b12;
  out.m07 = a03 * b10 + a13 * b11 + a23 * b12;
  out.m08 = a00 * b20 + a10 * b21 + a20 * b22;
  out.m09 = a01 * b20 + a11 * b21 + a21 * b22;
  out.m10 = a02 * b20 + a12 * b21 + a22 * b22;
  out.m11 = a03 * b20 + a13 * b21 + a23 * b22;

  // If the source and destination differ, copy the unchanged last row
  if (a !== out) {
    out.m12 = a.m12;
    out.m13 = a.m13;
    out.m14 = a.m14;
    out.m15 = a.m15;
  }

  return out;
};

/**
 * Rotates a matrix by the given angle around the X axis
 *
 * @param {mat4} out the receiving matrix
 * @param {mat4} a the matrix to rotate
 * @param {Number} rad the angle to rotate the matrix by
 * @returns {mat4} out
 */
mat4.rotateX = function (out, a, rad) {
  let s = Math.sin(rad),
      c = Math.cos(rad),
      a10 = a.m04,
      a11 = a.m05,
      a12 = a.m06,
      a13 = a.m07,
      a20 = a.m08,
      a21 = a.m09,
      a22 = a.m10,
      a23 = a.m11;

  if (a !== out) { // If the source and destination differ, copy the unchanged rows
    out.m00 = a.m00;
    out.m01 = a.m01;
    out.m02 = a.m02;
    out.m03 = a.m03;
    out.m12 = a.m12;
    out.m13 = a.m13;
    out.m14 = a.m14;
    out.m15 = a.m15;
  }

  // Perform axis-specific matrix multiplication
  out.m04 = a10 * c + a20 * s;
  out.m05 = a11 * c + a21 * s;
  out.m06 = a12 * c + a22 * s;
  out.m07 = a13 * c + a23 * s;
  out.m08 = a20 * c - a10 * s;
  out.m09 = a21 * c - a11 * s;
  out.m10 = a22 * c - a12 * s;
  out.m11 = a23 * c - a13 * s;

  return out;
};

/**
 * Rotates a matrix by the given angle around the Y axis
 *
 * @param {mat4} out the receiving matrix
 * @param {mat4} a the matrix to rotate
 * @param {Number} rad the angle to rotate the matrix by
 * @returns {mat4} out
 */
mat4.rotateY = function (out, a, rad) {
  let s = Math.sin(rad),
      c = Math.cos(rad),
      a00 = a.m00,
      a01 = a.m01,
      a02 = a.m02,
      a03 = a.m03,
      a20 = a.m08,
      a21 = a.m09,
      a22 = a.m10,
      a23 = a.m11;

  if (a !== out) { // If the source and destination differ, copy the unchanged rows
    out.m04 = a.m04;
    out.m05 = a.m05;
    out.m06 = a.m06;
    out.m07 = a.m07;
    out.m12 = a.m12;
    out.m13 = a.m13;
    out.m14 = a.m14;
    out.m15 = a.m15;
  }

  // Perform axis-specific matrix multiplication
  out.m00 = a00 * c - a20 * s;
  out.m01 = a01 * c - a21 * s;
  out.m02 = a02 * c - a22 * s;
  out.m03 = a03 * c - a23 * s;
  out.m08 = a00 * s + a20 * c;
  out.m09 = a01 * s + a21 * c;
  out.m10 = a02 * s + a22 * c;
  out.m11 = a03 * s + a23 * c;

  return out;
};

/**
 * Rotates a matrix by the given angle around the Z axis
 *
 * @param {mat4} out the receiving matrix
 * @param {mat4} a the matrix to rotate
 * @param {Number} rad the angle to rotate the matrix by
 * @returns {mat4} out
 */
mat4.rotateZ = function (out, a, rad) {
  let s = Math.sin(rad),
      c = Math.cos(rad),
      a00 = a.m00,
      a01 = a.m01,
      a02 = a.m02,
      a03 = a.m03,
      a10 = a.m04,
      a11 = a.m05,
      a12 = a.m06,
      a13 = a.m07;

  // If the source and destination differ, copy the unchanged last row
  if (a !== out) {
    out.m08 = a.m08;
    out.m09 = a.m09;
    out.m10 = a.m10;
    out.m11 = a.m11;
    out.m12 = a.m12;
    out.m13 = a.m13;
    out.m14 = a.m14;
    out.m15 = a.m15;
  }

  // Perform axis-specific matrix multiplication
  out.m00 = a00 * c + a10 * s;
  out.m01 = a01 * c + a11 * s;
  out.m02 = a02 * c + a12 * s;
  out.m03 = a03 * c + a13 * s;
  out.m04 = a10 * c - a00 * s;
  out.m05 = a11 * c - a01 * s;
  out.m06 = a12 * c - a02 * s;
  out.m07 = a13 * c - a03 * s;

  return out;
};

/**
 * Creates a matrix from a vector translation
 * This is equivalent to (but much faster than):
 *
 *     mat4.identity(dest);
 *     mat4.translate(dest, dest, vec);
 *
 * @param {mat4} out mat4 receiving operation result
 * @param {vec3} v Translation vector
 * @returns {mat4} out
 */
mat4.fromTranslation = function (out, v) {
  out.m00 = 1;
  out.m01 = 0;
  out.m02 = 0;
  out.m03 = 0;
  out.m04 = 0;
  out.m05 = 1;
  out.m06 = 0;
  out.m07 = 0;
  out.m08 = 0;
  out.m09 = 0;
  out.m10 = 1;
  out.m11 = 0;
  out.m12 = v.x;
  out.m13 = v.y;
  out.m14 = v.z;
  out.m15 = 1;
  return out;
};

/**
 * Creates a matrix from a vector scaling
 * This is equivalent to (but much faster than):
 *
 *     mat4.identity(dest);
 *     mat4.scale(dest, dest, vec);
 *
 * @param {mat4} out mat4 receiving operation result
 * @param {vec3} v Scaling vector
 * @returns {mat4} out
 */
mat4.fromScaling = function (out, v) {
  out.m00 = v.x;
  out.m01 = 0;
  out.m02 = 0;
  out.m03 = 0;
  out.m04 = 0;
  out.m05 = v.y;
  out.m06 = 0;
  out.m07 = 0;
  out.m08 = 0;
  out.m09 = 0;
  out.m10 = v.z;
  out.m11 = 0;
  out.m12 = 0;
  out.m13 = 0;
  out.m14 = 0;
  out.m15 = 1;
  return out;
};

/**
 * Creates a matrix from a given angle around a given axis
 * This is equivalent to (but much faster than):
 *
 *     mat4.identity(dest);
 *     mat4.rotate(dest, dest, rad, axis);
 *
 * @param {mat4} out mat4 receiving operation result
 * @param {Number} rad the angle to rotate the matrix by
 * @param {vec3} axis the axis to rotate around
 * @returns {mat4} out
 */
mat4.fromRotation = function (out, rad, axis) {
  let x = axis.x, y = axis.y, z = axis.z;
  let len = Math.sqrt(x * x + y * y + z * z);
  let s, c, t;

  if (Math.abs(len) < EPSILON) {
    return null;
  }

  len = 1 / len;
  x *= len;
  y *= len;
  z *= len;

  s = Math.sin(rad);
  c = Math.cos(rad);
  t = 1 - c;

  // Perform rotation-specific matrix multiplication
  out.m00 = x * x * t + c;
  out.m01 = y * x * t + z * s;
  out.m02 = z * x * t - y * s;
  out.m03 = 0;
  out.m04 = x * y * t - z * s;
  out.m05 = y * y * t + c;
  out.m06 = z * y * t + x * s;
  out.m07 = 0;
  out.m08 = x * z * t + y * s;
  out.m09 = y * z * t - x * s;
  out.m10 = z * z * t + c;
  out.m11 = 0;
  out.m12 = 0;
  out.m13 = 0;
  out.m14 = 0;
  out.m15 = 1;
  return out;
};

/**
 * Creates a matrix from the given angle around the X axis
 * This is equivalent to (but much faster than):
 *
 *     mat4.identity(dest);
 *     mat4.rotateX(dest, dest, rad);
 *
 * @param {mat4} out mat4 receiving operation result
 * @param {Number} rad the angle to rotate the matrix by
 * @returns {mat4} out
 */
mat4.fromXRotation = function (out, rad) {
  let s = Math.sin(rad),
      c = Math.cos(rad);

  // Perform axis-specific matrix multiplication
  out.m00 = 1;
  out.m01 = 0;
  out.m02 = 0;
  out.m03 = 0;
  out.m04 = 0;
  out.m05 = c;
  out.m06 = s;
  out.m07 = 0;
  out.m08 = 0;
  out.m09 = -s;
  out.m10 = c;
  out.m11 = 0;
  out.m12 = 0;
  out.m13 = 0;
  out.m14 = 0;
  out.m15 = 1;
  return out;
};

/**
 * Creates a matrix from the given angle around the Y axis
 * This is equivalent to (but much faster than):
 *
 *     mat4.identity(dest);
 *     mat4.rotateY(dest, dest, rad);
 *
 * @param {mat4} out mat4 receiving operation result
 * @param {Number} rad the angle to rotate the matrix by
 * @returns {mat4} out
 */
mat4.fromYRotation = function (out, rad) {
  let s = Math.sin(rad),
      c = Math.cos(rad);

  // Perform axis-specific matrix multiplication
  out.m00 = c;
  out.m01 = 0;
  out.m02 = -s;
  out.m03 = 0;
  out.m04 = 0;
  out.m05 = 1;
  out.m06 = 0;
  out.m07 = 0;
  out.m08 = s;
  out.m09 = 0;
  out.m10 = c;
  out.m11 = 0;
  out.m12 = 0;
  out.m13 = 0;
  out.m14 = 0;
  out.m15 = 1;
  return out;
};

/**
 * Creates a matrix from the given angle around the Z axis
 * This is equivalent to (but much faster than):
 *
 *     mat4.identity(dest);
 *     mat4.rotateZ(dest, dest, rad);
 *
 * @param {mat4} out mat4 receiving operation result
 * @param {Number} rad the angle to rotate the matrix by
 * @returns {mat4} out
 */
mat4.fromZRotation = function (out, rad) {
  let s = Math.sin(rad),
      c = Math.cos(rad);

  // Perform axis-specific matrix multiplication
  out.m00 = c;
  out.m01 = s;
  out.m02 = 0;
  out.m03 = 0;
  out.m04 = -s;
  out.m05 = c;
  out.m06 = 0;
  out.m07 = 0;
  out.m08 = 0;
  out.m09 = 0;
  out.m10 = 1;
  out.m11 = 0;
  out.m12 = 0;
  out.m13 = 0;
  out.m14 = 0;
  out.m15 = 1;
  return out;
};

/**
 * Creates a matrix from a quaternion rotation and vector translation
 * This is equivalent to (but much faster than):
 *
 *     mat4.identity(dest);
 *     mat4.translate(dest, vec);
 *     let quatMat = mat4.create();
 *     quat.toMat4(quat, quatMat);
 *     mat4.multiply(dest, quatMat);
 *
 * @param {mat4} out mat4 receiving operation result
 * @param {quat} q Rotation quaternion
 * @param {vec3} v Translation vector
 * @returns {mat4} out
 */
mat4.fromRT = function (out, q, v) {
  // Quaternion math
  let x = q.x, y = q.y, z = q.z, w = q.w;
  let x2 = x + x;
  let y2 = y + y;
  let z2 = z + z;

  let xx = x * x2;
  let xy = x * y2;
  let xz = x * z2;
  let yy = y * y2;
  let yz = y * z2;
  let zz = z * z2;
  let wx = w * x2;
  let wy = w * y2;
  let wz = w * z2;

  out.m00 = 1 - (yy + zz);
  out.m01 = xy + wz;
  out.m02 = xz - wy;
  out.m03 = 0;
  out.m04 = xy - wz;
  out.m05 = 1 - (xx + zz);
  out.m06 = yz + wx;
  out.m07 = 0;
  out.m08 = xz + wy;
  out.m09 = yz - wx;
  out.m10 = 1 - (xx + yy);
  out.m11 = 0;
  out.m12 = v.x;
  out.m13 = v.y;
  out.m14 = v.z;
  out.m15 = 1;

  return out;
};

/**
 * Returns the translation vector component of a transformation
 *  matrix. If a matrix is built with fromRT,
 *  the returned vector will be the same as the translation vector
 *  originally supplied.
 * @param  {vec3} out Vector to receive translation component
 * @param  {mat4} mat Matrix to be decomposed (input)
 * @return {vec3} out
 */
mat4.getTranslation = function (out, mat) {
  out.x = mat.m12;
  out.y = mat.m13;
  out.z = mat.m14;

  return out;
};

/**
 * Returns the scaling factor component of a transformation
 *  matrix. If a matrix is built with fromRTS
 *  with a normalized Quaternion paramter, the returned vector will be
 *  the same as the scaling vector
 *  originally supplied.
 * @param  {vec3} out Vector to receive scaling factor component
 * @param  {mat4} mat Matrix to be decomposed (input)
 * @return {vec3} out
 */
mat4.getScaling = function (out, mat) {
  let m11 = mat.m00,
      m12 = mat.m01,
      m13 = mat.m02,
      m21 = mat.m04,
      m22 = mat.m05,
      m23 = mat.m06,
      m31 = mat.m08,
      m32 = mat.m09,
      m33 = mat.m10;

  out.x = Math.sqrt(m11 * m11 + m12 * m12 + m13 * m13);
  out.y = Math.sqrt(m21 * m21 + m22 * m22 + m23 * m23);
  out.z = Math.sqrt(m31 * m31 + m32 * m32 + m33 * m33);

  return out;
};

/**
 * Returns a quaternion representing the rotational component
 *  of a transformation matrix. If a matrix is built with
 *  fromRT, the returned quaternion will be the
 *  same as the quaternion originally supplied.
 * @param {quat} out Quaternion to receive the rotation component
 * @param {mat4} mat Matrix to be decomposed (input)
 * @return {quat} out
 */
mat4.getRotation = function (out, mat) {
  // Algorithm taken from http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
  let trace = mat.m00 + mat.m05 + mat.m10;
  let S = 0;

  if (trace > 0) {
    S = Math.sqrt(trace + 1.0) * 2;
    out.w = 0.25 * S;
    out.x = (mat.m06 - mat.m09) / S;
    out.y = (mat.m08 - mat.m02) / S;
    out.z = (mat.m01 - mat.m04) / S;
  } else if ((mat.m00 > mat.m05) & (mat.m00 > mat.m10)) {
    S = Math.sqrt(1.0 + mat.m00 - mat.m05 - mat.m10) * 2;
    out.w = (mat.m06 - mat.m09) / S;
    out.x = 0.25 * S;
    out.y = (mat.m01 + mat.m04) / S;
    out.z = (mat.m08 + mat.m02) / S;
  } else if (mat.m05 > mat.m10) {
    S = Math.sqrt(1.0 + mat.m05 - mat.m00 - mat.m10) * 2;
    out.w = (mat.m08 - mat.m02) / S;
    out.x = (mat.m01 + mat.m04) / S;
    out.y = 0.25 * S;
    out.z = (mat.m06 + mat.m09) / S;
  } else {
    S = Math.sqrt(1.0 + mat.m10 - mat.m00 - mat.m05) * 2;
    out.w = (mat.m01 - mat.m04) / S;
    out.x = (mat.m08 + mat.m02) / S;
    out.y = (mat.m06 + mat.m09) / S;
    out.z = 0.25 * S;
  }

  return out;
};

/**
 * Creates a matrix from a quaternion rotation, vector translation and vector scale
 * This is equivalent to (but much faster than):
 *
 *     mat4.identity(dest);
 *     mat4.translate(dest, vec);
 *     let quatMat = mat4.create();
 *     quat.toMat4(quat, quatMat);
 *     mat4.multiply(dest, quatMat);
 *     mat4.scale(dest, scale)
 *
 * @param {mat4} out mat4 receiving operation result
 * @param {quat} q Rotation quaternion
 * @param {vec3} v Translation vector
 * @param {vec3} s Scaling vector
 * @returns {mat4} out
 */
mat4.fromRTS = function (out, q, v, s) {
  // Quaternion math
  let x = q.x, y = q.y, z = q.z, w = q.w;
  let x2 = x + x;
  let y2 = y + y;
  let z2 = z + z;

  let xx = x * x2;
  let xy = x * y2;
  let xz = x * z2;
  let yy = y * y2;
  let yz = y * z2;
  let zz = z * z2;
  let wx = w * x2;
  let wy = w * y2;
  let wz = w * z2;
  let sx = s.x;
  let sy = s.y;
  let sz = s.z;

  out.m00 = (1 - (yy + zz)) * sx;
  out.m01 = (xy + wz) * sx;
  out.m02 = (xz - wy) * sx;
  out.m03 = 0;
  out.m04 = (xy - wz) * sy;
  out.m05 = (1 - (xx + zz)) * sy;
  out.m06 = (yz + wx) * sy;
  out.m07 = 0;
  out.m08 = (xz + wy) * sz;
  out.m09 = (yz - wx) * sz;
  out.m10 = (1 - (xx + yy)) * sz;
  out.m11 = 0;
  out.m12 = v.x;
  out.m13 = v.y;
  out.m14 = v.z;
  out.m15 = 1;

  return out;
};

/**
 * Creates a matrix from a quaternion rotation, vector translation and vector scale, rotating and scaling around the given origin
 * This is equivalent to (but much faster than):
 *
 *     mat4.identity(dest);
 *     mat4.translate(dest, vec);
 *     mat4.translate(dest, origin);
 *     let quatMat = mat4.create();
 *     quat.toMat4(quat, quatMat);
 *     mat4.multiply(dest, quatMat);
 *     mat4.scale(dest, scale)
 *     mat4.translate(dest, negativeOrigin);
 *
 * @param {mat4} out mat4 receiving operation result
 * @param {quat} q Rotation quaternion
 * @param {vec3} v Translation vector
 * @param {vec3} s Scaling vector
 * @param {vec3} o The origin vector around which to scale and rotate
 * @returns {mat4} out
 */
mat4.fromRTSOrigin = function (out, q, v, s, o) {
  // Quaternion math
  let x = q.x, y = q.y, z = q.z, w = q.w;
  let x2 = x + x;
  let y2 = y + y;
  let z2 = z + z;

  let xx = x * x2;
  let xy = x * y2;
  let xz = x * z2;
  let yy = y * y2;
  let yz = y * z2;
  let zz = z * z2;
  let wx = w * x2;
  let wy = w * y2;
  let wz = w * z2;

  let sx = s.x;
  let sy = s.y;
  let sz = s.z;

  let ox = o.x;
  let oy = o.y;
  let oz = o.z;

  out.m00 = (1 - (yy + zz)) * sx;
  out.m01 = (xy + wz) * sx;
  out.m02 = (xz - wy) * sx;
  out.m03 = 0;
  out.m04 = (xy - wz) * sy;
  out.m05 = (1 - (xx + zz)) * sy;
  out.m06 = (yz + wx) * sy;
  out.m07 = 0;
  out.m08 = (xz + wy) * sz;
  out.m09 = (yz - wx) * sz;
  out.m10 = (1 - (xx + yy)) * sz;
  out.m11 = 0;
  out.m12 = v.x + ox - (out.m00 * ox + out.m04 * oy + out.m08 * oz);
  out.m13 = v.y + oy - (out.m01 * ox + out.m05 * oy + out.m09 * oz);
  out.m14 = v.z + oz - (out.m02 * ox + out.m06 * oy + out.m10 * oz);
  out.m15 = 1;

  return out;
};

/**
 * Calculates a 4x4 matrix from the given quaternion
 *
 * @param {mat4} out mat4 receiving operation result
 * @param {quat} q Quaternion to create matrix from
 *
 * @returns {mat4} out
 */
mat4.fromQuat = function (out, q) {
  let x = q.x, y = q.y, z = q.z, w = q.w;
  let x2 = x + x;
  let y2 = y + y;
  let z2 = z + z;

  let xx = x * x2;
  let yx = y * x2;
  let yy = y * y2;
  let zx = z * x2;
  let zy = z * y2;
  let zz = z * z2;
  let wx = w * x2;
  let wy = w * y2;
  let wz = w * z2;

  out.m00 = 1 - yy - zz;
  out.m01 = yx + wz;
  out.m02 = zx - wy;
  out.m03 = 0;

  out.m04 = yx - wz;
  out.m05 = 1 - xx - zz;
  out.m06 = zy + wx;
  out.m07 = 0;

  out.m08 = zx + wy;
  out.m09 = zy - wx;
  out.m10 = 1 - xx - yy;
  out.m11 = 0;

  out.m12 = 0;
  out.m13 = 0;
  out.m14 = 0;
  out.m15 = 1;

  return out;
};

/**
 * Generates a frustum matrix with the given bounds
 *
 * @param {mat4} out mat4 frustum matrix will be written into
 * @param {Number} left Left bound of the frustum
 * @param {Number} right Right bound of the frustum
 * @param {Number} bottom Bottom bound of the frustum
 * @param {Number} top Top bound of the frustum
 * @param {Number} near Near bound of the frustum
 * @param {Number} far Far bound of the frustum
 * @returns {mat4} out
 */
mat4.frustum = function (out, left, right, bottom, top, near, far) {
  let rl = 1 / (right - left);
  let tb = 1 / (top - bottom);
  let nf = 1 / (near - far);

  out.m00 = (near * 2) * rl;
  out.m01 = 0;
  out.m02 = 0;
  out.m03 = 0;
  out.m04 = 0;
  out.m05 = (near * 2) * tb;
  out.m06 = 0;
  out.m07 = 0;
  out.m08 = (right + left) * rl;
  out.m09 = (top + bottom) * tb;
  out.m10 = (far + near) * nf;
  out.m11 = -1;
  out.m12 = 0;
  out.m13 = 0;
  out.m14 = (far * near * 2) * nf;
  out.m15 = 0;
  return out;
};

/**
 * Generates a perspective projection matrix with the given bounds
 *
 * @param {mat4} out mat4 frustum matrix will be written into
 * @param {number} fovy Vertical field of view in radians
 * @param {number} aspect Aspect ratio. typically viewport width/height
 * @param {number} near Near bound of the frustum
 * @param {number} far Far bound of the frustum
 * @returns {mat4} out
 */
mat4.perspective = function (out, fovy, aspect, near, far) {
  let f = 1.0 / Math.tan(fovy / 2);
  let nf = 1 / (near - far);

  out.m00 = f / aspect;
  out.m01 = 0;
  out.m02 = 0;
  out.m03 = 0;
  out.m04 = 0;
  out.m05 = f;
  out.m06 = 0;
  out.m07 = 0;
  out.m08 = 0;
  out.m09 = 0;
  out.m10 = (far + near) * nf;
  out.m11 = -1;
  out.m12 = 0;
  out.m13 = 0;
  out.m14 = (2 * far * near) * nf;
  out.m15 = 0;
  return out;
};

/**
 * Generates a perspective projection matrix with the given field of view.
 * This is primarily useful for generating projection matrices to be used
 * with the still experiemental WebVR API.
 *
 * @param {mat4} out mat4 frustum matrix will be written into
 * @param {Object} fov Object containing the following values: upDegrees, downDegrees, leftDegrees, rightDegrees
 * @param {number} near Near bound of the frustum
 * @param {number} far Far bound of the frustum
 * @returns {mat4} out
 */
mat4.perspectiveFromFieldOfView = function (out, fov, near, far) {
  let upTan = Math.tan(fov.upDegrees * Math.PI / 180.0);
  let downTan = Math.tan(fov.downDegrees * Math.PI / 180.0);
  let leftTan = Math.tan(fov.leftDegrees * Math.PI / 180.0);
  let rightTan = Math.tan(fov.rightDegrees * Math.PI / 180.0);
  let xScale = 2.0 / (leftTan + rightTan);
  let yScale = 2.0 / (upTan + downTan);

  out.m00 = xScale;
  out.m01 = 0.0;
  out.m02 = 0.0;
  out.m03 = 0.0;
  out.m04 = 0.0;
  out.m05 = yScale;
  out.m06 = 0.0;
  out.m07 = 0.0;
  out.m08 = -((leftTan - rightTan) * xScale * 0.5);
  out.m09 = ((upTan - downTan) * yScale * 0.5);
  out.m10 = far / (near - far);
  out.m11 = -1.0;
  out.m12 = 0.0;
  out.m13 = 0.0;
  out.m14 = (far * near) / (near - far);
  out.m15 = 0.0;
  return out;
};

/**
 * Generates a orthogonal projection matrix with the given bounds
 *
 * @param {mat4} out mat4 frustum matrix will be written into
 * @param {number} left Left bound of the frustum
 * @param {number} right Right bound of the frustum
 * @param {number} bottom Bottom bound of the frustum
 * @param {number} top Top bound of the frustum
 * @param {number} near Near bound of the frustum
 * @param {number} far Far bound of the frustum
 * @returns {mat4} out
 */
mat4.ortho = function (out, left, right, bottom, top, near, far) {
  let lr = 1 / (left - right);
  let bt = 1 / (bottom - top);
  let nf = 1 / (near - far);
  out.m00 = -2 * lr;
  out.m01 = 0;
  out.m02 = 0;
  out.m03 = 0;
  out.m04 = 0;
  out.m05 = -2 * bt;
  out.m06 = 0;
  out.m07 = 0;
  out.m08 = 0;
  out.m09 = 0;
  out.m10 = 2 * nf;
  out.m11 = 0;
  out.m12 = (left + right) * lr;
  out.m13 = (top + bottom) * bt;
  out.m14 = (far + near) * nf;
  out.m15 = 1;
  return out;
};

/**
 * Generates a look-at matrix with the given eye position, focal point, and up axis
 *
 * @param {mat4} out mat4 frustum matrix will be written into
 * @param {vec3} eye Position of the viewer
 * @param {vec3} center Point the viewer is looking at
 * @param {vec3} up vec3 pointing up
 * @returns {mat4} out
 */
mat4.lookAt = function (out, eye, center, up) {
  let x0, x1, x2, y0, y1, y2, z0, z1, z2, len;
  let eyex = eye.x;
  let eyey = eye.y;
  let eyez = eye.z;
  let upx = up.x;
  let upy = up.y;
  let upz = up.z;
  let centerx = center.x;
  let centery = center.y;
  let centerz = center.z;

  if (
    Math.abs(eyex - centerx) < EPSILON &&
    Math.abs(eyey - centery) < EPSILON &&
    Math.abs(eyez - centerz) < EPSILON
  ) {
    return mat4.identity(out);
  }

  z0 = eyex - centerx;
  z1 = eyey - centery;
  z2 = eyez - centerz;

  len = 1 / Math.sqrt(z0 * z0 + z1 * z1 + z2 * z2);
  z0 *= len;
  z1 *= len;
  z2 *= len;

  x0 = upy * z2 - upz * z1;
  x1 = upz * z0 - upx * z2;
  x2 = upx * z1 - upy * z0;
  len = Math.sqrt(x0 * x0 + x1 * x1 + x2 * x2);
  if (!len) {
    x0 = 0;
    x1 = 0;
    x2 = 0;
  } else {
    len = 1 / len;
    x0 *= len;
    x1 *= len;
    x2 *= len;
  }

  y0 = z1 * x2 - z2 * x1;
  y1 = z2 * x0 - z0 * x2;
  y2 = z0 * x1 - z1 * x0;

  len = Math.sqrt(y0 * y0 + y1 * y1 + y2 * y2);
  if (!len) {
    y0 = 0;
    y1 = 0;
    y2 = 0;
  } else {
    len = 1 / len;
    y0 *= len;
    y1 *= len;
    y2 *= len;
  }

  out.m00 = x0;
  out.m01 = y0;
  out.m02 = z0;
  out.m03 = 0;
  out.m04 = x1;
  out.m05 = y1;
  out.m06 = z1;
  out.m07 = 0;
  out.m08 = x2;
  out.m09 = y2;
  out.m10 = z2;
  out.m11 = 0;
  out.m12 = -(x0 * eyex + x1 * eyey + x2 * eyez);
  out.m13 = -(y0 * eyex + y1 * eyey + y2 * eyez);
  out.m14 = -(z0 * eyex + z1 * eyey + z2 * eyez);
  out.m15 = 1;

  return out;
};

/**
 * Returns a string representation of a mat4
 *
 * @param {mat4} a matrix to represent as a string
 * @returns {String} string representation of the matrix
 */
mat4.str = function (a) {
  return `mat4(${a.m00}, ${a.m01}, ${a.m02}, ${a.m03}, ${a.m04}, ${a.m05}, ${a.m06}, ${a.m07}, ${a.m08}, ${a.m09}, ${a.m10}, ${a.m11}, ${a.m12}, ${a.m13}, ${a.m14}, ${a.m15})`;
};

/**
 * Returns typed array
 *
 * @param {array} out
 * @param {mat4} m
 * @returns {array}
 */
mat4.array = function (out, m) {
  out[0]  = m.m00;
  out[1]  = m.m01;
  out[2]  = m.m02;
  out[3]  = m.m03;
  out[4]  = m.m04;
  out[5]  = m.m05;
  out[6]  = m.m06;
  out[7]  = m.m07;
  out[8]  = m.m08;
  out[9]  = m.m09;
  out[10] = m.m10;
  out[11] = m.m11;
  out[12] = m.m12;
  out[13] = m.m13;
  out[14] = m.m14;
  out[15] = m.m15;

  return out;
};

/**
 * Returns Frobenius norm of a mat4
 *
 * @param {mat4} a the matrix to calculate Frobenius norm of
 * @returns {Number} Frobenius norm
 */
mat4.frob = function (a) {
  return (Math.sqrt(Math.pow(a.m00, 2) + Math.pow(a.m01, 2) + Math.pow(a.m02, 2) + Math.pow(a.m03, 2) + Math.pow(a.m04, 2) + Math.pow(a.m05, 2) + Math.pow(a.m06, 2) + Math.pow(a.m07, 2) + Math.pow(a.m08, 2) + Math.pow(a.m09, 2) + Math.pow(a.m10, 2) + Math.pow(a.m11, 2) + Math.pow(a.m12, 2) + Math.pow(a.m13, 2) + Math.pow(a.m14, 2) + Math.pow(a.m15, 2)))
};

/**
 * Adds two mat4's
 *
 * @param {mat4} out the receiving matrix
 * @param {mat4} a the first operand
 * @param {mat4} b the second operand
 * @returns {mat4} out
 */
mat4.add = function (out, a, b) {
  out.m00 = a.m00 + b.m00;
  out.m01 = a.m01 + b.m01;
  out.m02 = a.m02 + b.m02;
  out.m03 = a.m03 + b.m03;
  out.m04 = a.m04 + b.m04;
  out.m05 = a.m05 + b.m05;
  out.m06 = a.m06 + b.m06;
  out.m07 = a.m07 + b.m07;
  out.m08 = a.m08 + b.m08;
  out.m09 = a.m09 + b.m09;
  out.m10 = a.m10 + b.m10;
  out.m11 = a.m11 + b.m11;
  out.m12 = a.m12 + b.m12;
  out.m13 = a.m13 + b.m13;
  out.m14 = a.m14 + b.m14;
  out.m15 = a.m15 + b.m15;
  return out;
};

/**
 * Subtracts matrix b from matrix a
 *
 * @param {mat4} out the receiving matrix
 * @param {mat4} a the first operand
 * @param {mat4} b the second operand
 * @returns {mat4} out
 */
mat4.subtract = function (out, a, b) {
  out.m00 = a.m00 - b.m00;
  out.m01 = a.m01 - b.m01;
  out.m02 = a.m02 - b.m02;
  out.m03 = a.m03 - b.m03;
  out.m04 = a.m04 - b.m04;
  out.m05 = a.m05 - b.m05;
  out.m06 = a.m06 - b.m06;
  out.m07 = a.m07 - b.m07;
  out.m08 = a.m08 - b.m08;
  out.m09 = a.m09 - b.m09;
  out.m10 = a.m10 - b.m10;
  out.m11 = a.m11 - b.m11;
  out.m12 = a.m12 - b.m12;
  out.m13 = a.m13 - b.m13;
  out.m14 = a.m14 - b.m14;
  out.m15 = a.m15 - b.m15;
  return out;
};

/**
 * Alias for {@link mat4.subtract}
 * @function
 */
mat4.sub = mat4.subtract;

/**
 * Multiply each element of the matrix by a scalar.
 *
 * @param {mat4} out the receiving matrix
 * @param {mat4} a the matrix to scale
 * @param {Number} b amount to scale the matrix's elements by
 * @returns {mat4} out
 */
mat4.multiplyScalar = function (out, a, b) {
  out.m00 = a.m00 * b;
  out.m01 = a.m01 * b;
  out.m02 = a.m02 * b;
  out.m03 = a.m03 * b;
  out.m04 = a.m04 * b;
  out.m05 = a.m05 * b;
  out.m06 = a.m06 * b;
  out.m07 = a.m07 * b;
  out.m08 = a.m08 * b;
  out.m09 = a.m09 * b;
  out.m10 = a.m10 * b;
  out.m11 = a.m11 * b;
  out.m12 = a.m12 * b;
  out.m13 = a.m13 * b;
  out.m14 = a.m14 * b;
  out.m15 = a.m15 * b;
  return out;
};

/**
 * Adds two mat4's after multiplying each element of the second operand by a scalar value.
 *
 * @param {mat4} out the receiving vector
 * @param {mat4} a the first operand
 * @param {mat4} b the second operand
 * @param {Number} scale the amount to scale b's elements by before adding
 * @returns {mat4} out
 */
mat4.multiplyScalarAndAdd = function (out, a, b, scale) {
  out.m00 = a.m00 + (b.m00 * scale);
  out.m01 = a.m01 + (b.m01 * scale);
  out.m02 = a.m02 + (b.m02 * scale);
  out.m03 = a.m03 + (b.m03 * scale);
  out.m04 = a.m04 + (b.m04 * scale);
  out.m05 = a.m05 + (b.m05 * scale);
  out.m06 = a.m06 + (b.m06 * scale);
  out.m07 = a.m07 + (b.m07 * scale);
  out.m08 = a.m08 + (b.m08 * scale);
  out.m09 = a.m09 + (b.m09 * scale);
  out.m10 = a.m10 + (b.m10 * scale);
  out.m11 = a.m11 + (b.m11 * scale);
  out.m12 = a.m12 + (b.m12 * scale);
  out.m13 = a.m13 + (b.m13 * scale);
  out.m14 = a.m14 + (b.m14 * scale);
  out.m15 = a.m15 + (b.m15 * scale);
  return out;
};

/**
 * Returns whether or not the matrices have exactly the same elements in the same position (when compared with ===)
 *
 * @param {mat4} a The first matrix.
 * @param {mat4} b The second matrix.
 * @returns {Boolean} True if the matrices are equal, false otherwise.
 */
mat4.exactEquals = function (a, b) {
  return a.m00 === b.m00 && a.m01 === b.m01 && a.m02 === b.m02 && a.m03 === b.m03 &&
    a.m04 === b.m04 && a.m05 === b.m05 && a.m06 === b.m06 && a.m07 === b.m07 &&
    a.m08 === b.m08 && a.m09 === b.m09 && a.m10 === b.m10 && a.m11 === b.m11 &&
    a.m12 === b.m12 && a.m13 === b.m13 && a.m14 === b.m14 && a.m15 === b.m15;
};

/**
 * Returns whether or not the matrices have approximately the same elements in the same position.
 *
 * @param {mat4} a The first matrix.
 * @param {mat4} b The second matrix.
 * @returns {Boolean} True if the matrices are equal, false otherwise.
 */
mat4.equals = function (a, b) {
  let a0 = a.m00, a1 = a.m01, a2 = a.m02, a3 = a.m03,
      a4 = a.m04, a5 = a.m05, a6 = a.m06, a7 = a.m07,
      a8 = a.m08, a9 = a.m09, a10 = a.m10, a11 = a.m11,
      a12 = a.m12, a13 = a.m13, a14 = a.m14, a15 = a.m15;

  let b0 = b.m00, b1 = b.m01, b2 = b.m02, b3 = b.m03,
      b4 = b.m04, b5 = b.m05, b6 = b.m06, b7 = b.m07,
      b8 = b.m08, b9 = b.m09, b10 = b.m10, b11 = b.m11,
      b12 = b.m12, b13 = b.m13, b14 = b.m14, b15 = b.m15;

  return (
    Math.abs(a0 - b0) <= EPSILON * Math.max(1.0, Math.abs(a0), Math.abs(b0)) &&
    Math.abs(a1 - b1) <= EPSILON * Math.max(1.0, Math.abs(a1), Math.abs(b1)) &&
    Math.abs(a2 - b2) <= EPSILON * Math.max(1.0, Math.abs(a2), Math.abs(b2)) &&
    Math.abs(a3 - b3) <= EPSILON * Math.max(1.0, Math.abs(a3), Math.abs(b3)) &&
    Math.abs(a4 - b4) <= EPSILON * Math.max(1.0, Math.abs(a4), Math.abs(b4)) &&
    Math.abs(a5 - b5) <= EPSILON * Math.max(1.0, Math.abs(a5), Math.abs(b5)) &&
    Math.abs(a6 - b6) <= EPSILON * Math.max(1.0, Math.abs(a6), Math.abs(b6)) &&
    Math.abs(a7 - b7) <= EPSILON * Math.max(1.0, Math.abs(a7), Math.abs(b7)) &&
    Math.abs(a8 - b8) <= EPSILON * Math.max(1.0, Math.abs(a8), Math.abs(b8)) &&
    Math.abs(a9 - b9) <= EPSILON * Math.max(1.0, Math.abs(a9), Math.abs(b9)) &&
    Math.abs(a10 - b10) <= EPSILON * Math.max(1.0, Math.abs(a10), Math.abs(b10)) &&
    Math.abs(a11 - b11) <= EPSILON * Math.max(1.0, Math.abs(a11), Math.abs(b11)) &&
    Math.abs(a12 - b12) <= EPSILON * Math.max(1.0, Math.abs(a12), Math.abs(b12)) &&
    Math.abs(a13 - b13) <= EPSILON * Math.max(1.0, Math.abs(a13), Math.abs(b13)) &&
    Math.abs(a14 - b14) <= EPSILON * Math.max(1.0, Math.abs(a14), Math.abs(b14)) &&
    Math.abs(a15 - b15) <= EPSILON * Math.max(1.0, Math.abs(a15), Math.abs(b15))
  );
};

let _tmp$8 = new Array(3);

class _color3 {
  constructor(r, g, b) {
    this.r = r;
    this.g = g;
    this.b = b;
  }

  toJSON() {
    _tmp$8[0] = this.r;
    _tmp$8[1] = this.g;
    _tmp$8[2] = this.b;

    return _tmp$8;
  }
}

/**
 * @class Color
 * @name color3
 */
let color3 = {};

/**
 * Creates a new color
 *
 * @returns {color3} a new color
 */
color3.create = function () {
  return new _color3(1, 1, 1);
};

/**
 * Creates a new color initialized with the given values
 *
 * @param {Number} r red component
 * @param {Number} g green component
 * @param {Number} b blue component
 * @returns {color3} a new color
 * @function
 */
color3.new = function (r, g, b) {
  return new _color3(r, g, b);
};

/**
 * Creates a new color initialized with values from an existing quaternion
 *
 * @param {color3} a color to clone
 * @returns {color3} a new color
 * @function
 */
color3.clone = function (a) {
  return new _color3(a.r, a.g, a.b, a.a);
};

/**
 * Copy the values from one color to another
 *
 * @param {color3} out the receiving color
 * @param {color3} a the source color
 * @returns {color3} out
 * @function
 */
color3.copy = function (out, a) {
  out.r = a.r;
  out.g = a.g;
  out.b = a.b;
  return out;
};

/**
 * Set the components of a color to the given values
 *
 * @param {color3} out the receiving color
 * @param {Number} r red component
 * @param {Number} g green component
 * @param {Number} b blue component
 * @returns {color3} out
 * @function
 */
color3.set = function (out, r, g, b) {
  out.r = r;
  out.g = g;
  out.b = b;
  return out;
};

/**
 * Set from hex
 *
 * @param {color3} out the receiving color
 * @param {Number} hex
 * @returns {color3} out
 * @function
 */
color3.fromHex = function (out, hex) {
  let r = ((hex >> 16)) / 255.0;
  let g = ((hex >> 8) & 0xff) / 255.0;
  let b = ((hex) & 0xff) / 255.0;

  out.r = r;
  out.g = g;
  out.b = b;
  return out;
};

/**
 * Adds two color's
 *
 * @param {color3} out the receiving color
 * @param {color3} a the first operand
 * @param {color3} b the second operand
 * @returns {color3} out
 * @function
 */
color3.add = function (out, a, b) {
  out.r = a.r + b.r;
  out.g = a.g + b.g;
  out.b = a.b + b.b;
  return out;
};

/**
 * Subtracts color b from color a
 *
 * @param {color3} out the receiving color
 * @param {color3} a the first operand
 * @param {color3} b the second operand
 * @returns {color3} out
 */
color3.subtract = function (out, a, b) {
  out.r = a.r - b.r;
  out.g = a.g - b.g;
  out.b = a.b - b.b;
  return out;
};

/**
 * Alias for {@link color3.subtract}
 * @function
 */
color3.sub = color3.subtract;

/**
 * Multiplies two color's
 *
 * @param {color3} out the receiving color
 * @param {color3} a the first operand
 * @param {color3} b the second operand
 * @returns {color3} out
 * @function
 */
color3.multiply = function (out, a, b) {
  out.r = a.r * b.r;
  out.g = a.g * b.g;
  out.b = a.b * b.b;
  return out;
};

/**
 * Alias for {@link color3.multiply}
 * @function
 */
color3.mul = color3.multiply;

/**
 * Divides two color's
 *
 * @param {color3} out the receiving vector
 * @param {color3} a the first operand
 * @param {color3} b the second operand
 * @returns {color3} out
 */
color3.divide = function (out, a, b) {
  out.r = a.r / b.r;
  out.g = a.g / b.g;
  out.b = a.b / b.b;
  return out;
};

/**
 * Alias for {@link color3.divide}
 * @function
 */
color3.div = color3.divide;


/**
 * Scales a color by a scalar number
 *
 * @param {color3} out the receiving vector
 * @param {color3} a the vector to scale
 * @param {Number} b amount to scale the vector by
 * @returns {color3} out
 * @function
 */
color3.scale = function (out, a, b) {
  out.r = a.r * b;
  out.g = a.g * b;
  out.b = a.b * b;
  return out;
};

/**
 * Performs a linear interpolation between two color's
 *
 * @param {color3} out the receiving color
 * @param {color3} a the first operand
 * @param {color3} b the second operand
 * @param {Number} t interpolation amount between the two inputs
 * @returns {color3} out
 * @function
 */
color3.lerp = function (out, a, b, t) {
  let ar = a.r,
      ag = a.g,
      ab = a.b;
  out.r = ar + t * (b.r - ar);
  out.g = ag + t * (b.g - ag);
  out.b = ab + t * (b.b - ab);
  return out;
};

/**
 * Returns a string representation of a color
 *
 * @param {color3} a vector to represent as a string
 * @returns {String} string representation of the vector
 */
color3.str = function (a) {
  return `color3(${a.r}, ${a.g}, ${a.b})`;
};

/**
 * Returns typed array
 *
 * @param {array} out
 * @param {color3} a
 * @returns {array}
 */
color3.array = function (out, a) {
  out[0] = a.r;
  out[1] = a.g;
  out[2] = a.b;

  return out;
};

/**
 * Returns whether or not the color have exactly the same elements in the same position (when compared with ===)
 *
 * @param {color3} a The first color3.
 * @param {color3} b The second color3.
 * @returns {Boolean} True if the colors are equal, false otherwise.
 */
color3.exactEquals = function (a, b) {
  return a.r === b.r && a.g === b.g && a.b === b.b;
};

/**
 * Returns whether or not the colors have approximately the same elements in the same position.
 *
 * @param {color3} a The first color3.
 * @param {color3} b The second color3.
 * @returns {Boolean} True if the colors are equal, false otherwise.
 */
color3.equals = function (a, b) {
  let a0 = a.r, a1 = a.g, a2 = a.b;
  let b0 = b.r, b1 = b.g, b2 = b.b;
  return (Math.abs(a0 - b0) <= EPSILON * Math.max(1.0, Math.abs(a0), Math.abs(b0)) &&
    Math.abs(a1 - b1) <= EPSILON * Math.max(1.0, Math.abs(a1), Math.abs(b1)) &&
    Math.abs(a2 - b2) <= EPSILON * Math.max(1.0, Math.abs(a2), Math.abs(b2)));
};

/**
 * Returns the hex value
 *
 * @param {color3} a The color
 * @returns {Number}
 */
color3.hex = function (a) {
  return (a.r * 255) << 16 | (a.g * 255) << 8 | (a.b * 255);
};

let _tmp$9 = new Array(4);

class _color4 {
  constructor(r, g, b, a) {
    this.r = r;
    this.g = g;
    this.b = b;
    this.a = a;
  }

  toJSON() {
    _tmp$9[0] = this.r;
    _tmp$9[1] = this.g;
    _tmp$9[2] = this.b;
    _tmp$9[3] = this.a;

    return _tmp$9;
  }
}

/**
 * @class Color
 * @name color4
 */
let color4 = {};

/**
 * Creates a new color
 *
 * @returns {color4} a new color
 */
color4.create = function () {
  return new _color4(1, 1, 1, 1);
};

/**
 * Creates a new color initialized with the given values
 *
 * @param {Number} r red component
 * @param {Number} g green component
 * @param {Number} b blue component
 * @param {Number} a alpha component
 * @returns {color4} a new color
 * @function
 */
color4.new = function (r, g, b, a) {
  return new _color4(r, g, b, a);
};

/**
 * Creates a new color initialized with values from an existing quaternion
 *
 * @param {color4} a color to clone
 * @returns {color4} a new color
 * @function
 */
color4.clone = function (a) {
  return new _color4(a.r, a.g, a.b, a.a);
};

/**
 * Copy the values from one color to another
 *
 * @param {color4} out the receiving color
 * @param {color4} a the source color
 * @returns {color4} out
 * @function
 */
color4.copy = function (out, a) {
  out.r = a.r;
  out.g = a.g;
  out.b = a.b;
  out.a = a.a;
  return out;
};

/**
 * Set the components of a color to the given values
 *
 * @param {color4} out the receiving color
 * @param {Number} r red component
 * @param {Number} g green component
 * @param {Number} b blue component
 * @param {Number} a alpha component
 * @returns {color4} out
 * @function
 */
color4.set = function (out, r, g, b, a) {
  out.r = r;
  out.g = g;
  out.b = b;
  out.a = a;
  return out;
};

/**
 * Set from hex
 *
 * @param {color4} out the receiving color
 * @param {Number} hex
 * @returns {color4} out
 * @function
 */
color4.fromHex = function (out, hex) {
  let r = ((hex >> 24)) / 255.0;
  let g = ((hex >> 16) & 0xff) / 255.0;
  let b = ((hex >> 8) & 0xff) / 255.0;
  let a = ((hex) & 0xff) / 255.0;

  out.r = r;
  out.g = g;
  out.b = b;
  out.a = a;
  return out;
};

/**
 * Adds two color's
 *
 * @param {color4} out the receiving color
 * @param {color4} a the first operand
 * @param {color4} b the second operand
 * @returns {color4} out
 * @function
 */
color4.add = function (out, a, b) {
  out.r = a.r + b.r;
  out.g = a.g + b.g;
  out.b = a.b + b.b;
  out.a = a.a + b.a;
  return out;
};

/**
 * Subtracts color b from color a
 *
 * @param {color4} out the receiving color
 * @param {color4} a the first operand
 * @param {color4} b the second operand
 * @returns {color4} out
 */
color4.subtract = function (out, a, b) {
  out.r = a.r - b.r;
  out.g = a.g - b.g;
  out.b = a.b - b.b;
  out.a = a.a - b.a;
  return out;
};

/**
 * Alias for {@link color4.subtract}
 * @function
 */
color4.sub = color4.subtract;

/**
 * Multiplies two color's
 *
 * @param {color4} out the receiving color
 * @param {color4} a the first operand
 * @param {color4} b the second operand
 * @returns {color4} out
 * @function
 */
color4.multiply = function (out, a, b) {
  out.r = a.r * b.r;
  out.g = a.g * b.g;
  out.b = a.b * b.b;
  out.a = a.a * b.a;
  return out;
};

/**
 * Alias for {@link color4.multiply}
 * @function
 */
color4.mul = color4.multiply;

/**
 * Divides two color's
 *
 * @param {color4} out the receiving vector
 * @param {color4} a the first operand
 * @param {color4} b the second operand
 * @returns {color4} out
 */
color4.divide = function (out, a, b) {
  out.r = a.r / b.r;
  out.g = a.g / b.g;
  out.b = a.b / b.b;
  out.a = a.a / b.a;
  return out;
};

/**
 * Alias for {@link color4.divide}
 * @function
 */
color4.div = color4.divide;


/**
 * Scales a color by a scalar number
 *
 * @param {color4} out the receiving vector
 * @param {color4} a the vector to scale
 * @param {Number} b amount to scale the vector by
 * @returns {color4} out
 * @function
 */
color4.scale = function (out, a, b) {
  out.r = a.r * b;
  out.g = a.g * b;
  out.b = a.b * b;
  out.a = a.a * b;
  return out;
};

/**
 * Performs a linear interpolation between two color's
 *
 * @param {color4} out the receiving color
 * @param {color4} a the first operand
 * @param {color4} b the second operand
 * @param {Number} t interpolation amount between the two inputs
 * @returns {color4} out
 * @function
 */
color4.lerp = function (out, a, b, t) {
  let ar = a.r,
      ag = a.g,
      ab = a.b,
      aa = a.a;
  out.r = ar + t * (b.r - ar);
  out.g = ag + t * (b.g - ag);
  out.b = ab + t * (b.b - ab);
  out.a = aa + t * (b.a - aa);
  return out;
};

/**
 * Returns a string representation of a color
 *
 * @param {color4} a vector to represent as a string
 * @returns {String} string representation of the vector
 */
color4.str = function (a) {
  return `color4(${a.r}, ${a.g}, ${a.b}, ${a.a})`;
};

/**
 * Returns typed array
 *
 * @param {array} out
 * @param {color4} a
 * @returns {array}
 */
color4.array = function (out, a) {
  out[0] = a.r;
  out[1] = a.g;
  out[2] = a.b;
  out[3] = a.a;

  return out;
};

/**
 * Returns whether or not the color have exactly the same elements in the same position (when compared with ===)
 *
 * @param {color4} a The first color4.
 * @param {color4} b The second color4.
 * @returns {Boolean} True if the colors are equal, false otherwise.
 */
color4.exactEquals = function (a, b) {
  return a.r === b.r && a.g === b.g && a.b === b.b && a.a === b.a;
};

/**
 * Returns whether or not the colors have approximately the same elements in the same position.
 *
 * @param {color4} a The first color4.
 * @param {color4} b The second color4.
 * @returns {Boolean} True if the colors are equal, false otherwise.
 */
color4.equals = function (a, b) {
  let a0 = a.r, a1 = a.g, a2 = a.b, a3 = a.a;
  let b0 = b.r, b1 = b.g, b2 = b.b, b3 = b.a;
  return (Math.abs(a0 - b0) <= EPSILON * Math.max(1.0, Math.abs(a0), Math.abs(b0)) &&
    Math.abs(a1 - b1) <= EPSILON * Math.max(1.0, Math.abs(a1), Math.abs(b1)) &&
    Math.abs(a2 - b2) <= EPSILON * Math.max(1.0, Math.abs(a2), Math.abs(b2)) &&
    Math.abs(a3 - b3) <= EPSILON * Math.max(1.0, Math.abs(a3), Math.abs(b3)));
};

/**
 * Returns the hex value
 *
 * @param {color4} a The color
 * @returns {Number}
 */
color4.hex = function (a) {
  return ((a.r * 255) << 24 | (a.g * 255) << 16 | (a.b * 255) << 8 | a.a * 255) >>> 0;
};

// NOTE: there is no syntax for: export {* as bits} from './lib/bits';
let bits = bits_;

exports.bits = bits;
exports.vec2 = vec2;
exports.vec3 = vec3;
exports.vec4 = vec4;
exports.quat = quat;
exports.mat2 = mat2;
exports.mat23 = mat23;
exports.mat3 = mat3;
exports.mat4 = mat4;
exports.color3 = color3;
exports.color4 = color4;
exports.EPSILON = EPSILON;
exports.equals = equals;
exports.approx = approx;
exports.clamp = clamp;
exports.clamp01 = clamp01;
exports.lerp = lerp;
exports.toRadian = toRadian;
exports.toDegree = toDegree;
exports.random = random;
exports.randomRange = randomRange;
exports.randomRangeInt = randomRangeInt;
exports.nextPow2 = nextPow2;

}((this.vmath = this.vmath || {})));
//# sourceMappingURL=vmath.dev.js.map
