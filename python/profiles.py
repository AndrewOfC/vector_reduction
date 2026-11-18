# MIT License
# 
# Copyright (c) 2026 Andrew Ellis Page
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# 
# SPDX short identifier: MIT

from ctypes import sizeof, c_double, c_float, c_byte, c_int8, c_int16, c_int32, c_int64


class VectorProfile(object):

    INIT = "0"

    def __init__(self, name, n_registers=32):
        self.name = name
        self._n_registers = n_registers

    
    n_registers = property(lambda self: self._n_registers)
    
    def preamble(self):
        return f"    {self.vtype} vaccumulate = {self.INIT} ;\n"
    def _vtype(self):
        return self.VTYPE
    vtype = property(_vtype)

class NEONProfileDouble(VectorProfile):
    INIT = "vdupq_n_f64(0.0)"

    def __init__(self, n_registers):
        super().__init__("NEON", n_registers=n_registers)
        self.VTYPE = "float64x2_t"
        self.LOAD = (lambda params: f"vld1q_f64({params})")
        self.ADD =  lambda params: f"vaddq_f64({params})"
        self.EXTRACT = "vgetq_lane_f64"
        self.STRIDE = 128//(sizeof(c_double)*8)

class NEONProfileFloat(VectorProfile):
    INIT = "vdupq_n_f32(0.0)"

    def __init__(self, n_registers):
        super().__init__("NEON", n_registers=n_registers)
        self.VTYPE = "float32x4_t"
        self.LOAD =  lambda params: f"vld1q_f32({params})"
        self.ADD =  lambda params: f"vaddq_f32({params})"
        self.EXTRACT = "vgetq_lane_f32"
        self.STRIDE = 128//(sizeof(c_float)*8)

class NEONProfileInt32(VectorProfile):
    INIT = "vdupq_n_s32(0.0)"
    def __init__(self, n_registers):
        super().__init__("NEON", n_registers=n_registers)
        self.VTYPE = "int32x4_t"
        self.LOAD =  lambda params: f"vld1q_s32({params})"
        self.ADD =  lambda params: f"vaddq_s32({params})"
        self.EXTRACT = "vgetq_lane_s32"
        self.STRIDE = 128//(sizeof(c_int32)*8)


class NEONProfileInt64(VectorProfile):

    INIT = "vdupq_n_s64(0.0)" ;

    def __init__(self, n_registers):
        super().__init__("NEON", n_registers=n_registers)
        self.VTYPE = "int64x2_t"
        self.DTYPE = "int64_t"
        self.LOAD =  lambda params: f"vld1q_s64({params})"
        self.ADD =  lambda params: f"vaddq_s64({params})"
        self.EXTRACT = "vgetq_lane_s64"
        self.STRIDE = 128 // (sizeof(c_int64) * 8)
        self.filename = "vector_reduce_int64.c"

class SVEBase(VectorProfile):
    def __init__(self, name, n_registers):
        super().__init__(name, n_registers)
        self.STRIDE = "lanes"

    def preamble(self):
        return super().preamble() + f"""    {self.DTYPE} final[32] ;
    svbool_t pg = svptrue_b64();
    uint64_t lanes = svcntd();"""

class SVEProfileDouble(SVEBase):

    INIT= "svdup_f64(0.0)"

    def __init__(self, n_registers):
        super().__init__("SVE", n_registers)
        self.VTYPE = "svfloat64_t"
        self.DTYPE = "double"
        self.LOAD =  lambda params: f"svld1_f64(pg, {params})"
        self.ADD =  lambda params: f"svadd_f64_x(pg, {params})"
        self.EXTRACT = "svst1_f64"
        self.PREAMBLE = self.preamble() + """    double final[32] ;
    svbool_t pg = svptrue_b64();
    uint64_t lanes = svcntd();"""
        self.STRIDE = "lanes"



class SVEProfileFloat(SVEBase):
    INIT = "svdup_f32(0.0)"
    def __init__(self, n_registers):
        super().__init__("SVE", n_registers)
        self.VTYPE = "svfloat32_t"
        self.DTYPE = "float"
        self.LOAD =  lambda params: f"svld1_f32(pg, {params})"
        self.ADD =  lambda params: f"svadd_f32_x(pg, {params})"
        self.EXTRACT = "svst1_f32"
        self.PREAMBLE = self.preamble() + """    float final[32] ;
    svbool_t pg = svptrue_b64();
    uint64_t lanes = svcntd();"""

class SVEProfileInt64(SVEBase):
    INIT = "svdup_s64(0.0)"

    def __init__(self, n_registers):
        super().__init__("SVE", n_registers)
        self.VTYPE = "svint64_t"
        self.DTYPE = "int64_t"
        self.LOAD =  lambda params: f"svld1_s64(pg, {params})"
        self.ADD =  lambda params: f"svadd_s64_x(pg, {params})"
        self.EXTRACT = "svst1_s64" ;


class SVEProfileInt32(SVEBase):
    INIT = "svdup_s32(0.0)"

    def __init__(self, n_registers):
        super().__init__("SVE", n_registers)
        self.VTYPE = "svint32_t"
        self.DTYPE = "int32_t"
        self.LOAD =  lambda params: f"svld1_s32(pg, {params})"
        self.ADD =  lambda params: f"svadd_s32_x(pg, {params})"
        self.EXTRACT = "svst1_s32"
        self.PREAMBLE = self.preamble() + """    int32_t final[32] ;
    svbool_t pg = svptrue_b64();
    uint64_t lanes = svcntd();"""
        self.STRIDE = "lanes"

class AVX512ProfileDouble(VectorProfile):

    INIT = "_mm512_setzero_pd()"

    def __init__(self, n_registers):
        super().__init__("AVX512 Double", n_registers=n_registers)
        self.VTYPE = "__m512d"
        self.LOAD =  lambda params: f"_mm512_load_pd({params})"
        self.ADD =  lambda params: f"_mm512_add_pd({params})"
        self.REDUCE = "_mm512_reduce_add_pd"
        self.STRIDE = 512//(sizeof(c_double)*8)

class AVX512ProfileFloat(VectorProfile):

    INIT = "_mm512_setzero_ps()"

    def __init__(self, n_registers):
        super().__init__("AVX512 fLOAT", n_registers=n_registers)
        self.VTYPE = "__m512"
        self.LOAD =  lambda params: f"_mm512_load_ps({params})"
        self.ADD =  lambda params: f"_mm512_add_ps({params})"
        self.REDUCE = "_mm512_reduce_add_ps"
        self.STRIDE = 512//(sizeof(c_float)*8)

class AVX512ProfileInt8(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("AVX512 Double", n_registers=n_registers)
        self.VTYPE = "__m512i"
        self.LOAD =  lambda params: f"_mm512_load_epi8({params})"
        self.ADD =  lambda params: f"_mm512_add_epi8({params})"
        self.REDUCE = "_mm512_reduce_add_epi8"
        self.STRIDE = 512 // (sizeof(c_int8) * 8)

class AVX512ProfileInt16(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("AVX512 Double", n_registers=n_registers)
        self.VTYPE = "__m512i"
        self.LOAD =  lambda params: f"_mm512_load_epi16({params})"
        self.ADD =  lambda params: f"_mm512_add_epi16({params})"
        self.REDUCE = "_mm512_reduce_add_epi16"
        self.STRIDE = 512 // (sizeof(c_int16) * 8)

class AVX512ProfileInt32(VectorProfile):
    INIT = "_mm512_setzero_si512()"

    def __init__(self, n_registers):
        super().__init__("AVX512 Double", n_registers=n_registers)
        self.VTYPE = "__m512i"
        self.LOAD =  lambda params: f"_mm512_load_epi32({params})"
        self.ADD =  lambda params: f"_mm512_add_epi32({params})"
        self.REDUCE = "_mm512_reduce_add_epi32"
        self.STRIDE = 512 // (sizeof(c_int32) * 8)

class AVX512ProfileInt64(VectorProfile):
    INIT = "_mm512_setzero_si512()"
    def __init__(self, n_registers):
        super().__init__("AVX512 Double", n_registers=n_registers)
        self.VTYPE = "__m512i"
        self.LOAD =  lambda params: f"_mm512_load_epi64({params})"
        self.ADD =  lambda params: f"_mm512_add_epi64({params})"
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

SVETypes = {
    "double": SVEProfileDouble,
    "float": SVEProfileFloat,
   "int32_t": SVEProfileInt32,
    "int64_t": SVEProfileInt64,
}




RenderTypes = ["double", "float", "int32_t", "int64_t"]