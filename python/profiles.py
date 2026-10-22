
from ctypes import sizeof, c_double, c_float, c_byte, c_int8, c_int16, c_int32, c_int64


class VectorProfile(object):
    def __init__(self, name, n_registers=32):
        self.name = name
        self._n_registers = n_registers
    n_registers = property(lambda self: self._n_registers)


class NEONProfileDouble(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("NEON", n_registers=n_registers)
        self.VTYPE = "float64x2_t"
        self.LOAD = "vld1q_f64"
        self.ADD = "vaddq_f64"
        self.EXTRACT = "vgetq_lane_f64"
        self.STRIDE = 128//(sizeof(c_double)*8)

class NEONProfileFloat(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("NEON", n_registers=n_registers)
        self.VTYPE = "float32x4_t"
        self.LOAD = "vld1q_f32"
        self.ADD = "vaddq_f32"
        self.EXTRACT = "vgetq_lane_f32"
        self.STRIDE = 128//(sizeof(c_float)*8)

class NEONProfileInt32(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("NEON", n_registers=n_registers)
        self.VTYPE = "int32x4_t"
        self.LOAD = "vld1q_s32"
        self.ADD = "vaddq_s32"
        self.EXTRACT = "vgetq_lane_s32"
        self.STRIDE = 128//(sizeof(c_int32)*8)


class NEONProfileInt64(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("NEON", n_registers=n_registers)
        self.VTYPE = "int64x2_t"
        self.DTYPE = "int64_t"
        self.LOAD = "vld1q_s64"
        self.ADD = "vaddq_s64"
        self.EXTRACT = "vgetq_lane_s64"
        self.STRIDE = 128 // (sizeof(c_int64) * 8)
        self.filename = "vector_reduce_int64.c"


class AVX512ProfileDouble(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("AVX512 Double", n_registers=n_registers)
        self.VTYPE = "__m512d"
        self.LOAD = "_mm512_loadu_pd"
        self.ADD = "_mm512_add_pd"
        self.REDUCE = "_mm512_reduce_add_pd"
        self.STRIDE = 512//(sizeof(c_double)*8)


class AVX512ProfileFloat(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("AVX512 Double", n_registers=n_registers)
        self.VTYPE = "__m512"
        self.LOAD = "_mm512_loadu_ps"
        self.ADD = "_mm512_add_ps"
        self.REDUCE = "_mm512_reduce_add_ps"
        self.STRIDE = 512//(sizeof(c_float)*8)


class AVX512ProfileInt8(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("AVX512 Double", n_registers=n_registers)
        self.VTYPE = "__m512i"
        self.LOAD = "_mm512_loadu_epi8"
        self.ADD = "_mm512_add_epi8"
        self.REDUCE = "_mm512_reduce_add_epi8"
        self.STRIDE = 512 // (sizeof(c_int8) * 8)

class AVX512ProfileInt16(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("AVX512 Double", n_registers=n_registers)
        self.VTYPE = "__m512i"
        self.LOAD = "_mm512_loadu_epi16"
        self.ADD = "_mm512_add_epi16"
        self.REDUCE = "_mm512_reduce_add_epi16"
        self.STRIDE = 512 // (sizeof(c_int16) * 8)

class AVX512ProfileInt32(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("AVX512 Double", n_registers=n_registers)
        self.VTYPE = "__m512i"
        self.LOAD = "_mm512_loadu_epi32"
        self.ADD = "_mm512_add_epi32"
        self.REDUCE = "_mm512_reduce_add_epi32"
        self.STRIDE = 512 // (sizeof(c_int32) * 8)

class AVX512ProfileInt64(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("AVX512 Double", n_registers=n_registers)
        self.VTYPE = "__m512i"
        self.LOAD = "_mm512_loadu_epi64"
        self.ADD = "_mm512_add_epi64"
        self.REDUCE = "_mm512_reduce_add_epi64"
        self.STRIDE = 512 // (sizeof(c_int64) * 8)

NEONTypes = {
    "double": NEONProfileDouble,
    "float": NEONProfileFloat,
   "int32_t": NEONProfileInt32,
    "int64_t": NEONProfileInt64,
}

AVX512Types = {
    "double": AVX512ProfileDouble,
    "float": AVX512ProfileFloat,
    # "int8_t": AVX512ProfileInt8,
    # "int16_t": AVX512ProfileInt16,
    "int32_t": AVX512ProfileInt32,
    "int64_t": AVX512ProfileInt64,
}

RenderTypes = ["double", "float", "int32_t", "int64_t"]