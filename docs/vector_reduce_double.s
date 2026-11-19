   1              		.file	"vector_reduce_double.c"
   2              	# GNU C23 (Ubuntu 16-20260315-1ubuntu1~24~ppa1) version 16.0.1 20260315 (experimental) [trunk r16-8
   3              	#	compiled by GNU C version 16.0.1 20260315 (experimental) [trunk r16-8100-g3aca3bae8ee], GMP versi
   4              	
   5              	# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
   6              	# options passed: -D_FORTIFY_SOURCE=3 -march=tigerlake -mmmx -mpopcnt -msse -msse2 -msse3 -mssse3 -
   7              		.text
   8              		.p2align 4
   9              		.globl	vector_reduce_double
  11              	vector_reduce_double:
  12              	.LFB7302:
  13              		.cfi_startproc
  14 0000 F30F1EFA 		endbr64	
  15 0004 C5D9EFE4 		vpxor	%xmm4, %xmm4, %xmm4	# tmp377
  16              	# /home/andrew/black/vector_reduction/lib/vector_reduce_double.c:41: {
  17 0008 4889FA   		movq	%rdi, %rdx	# src, src
  18 000b C5F928F0 		vmovapd	%xmm0, %xmm6	# initial, initial
  19              	# /home/andrew/black/vector_reduction/lib/vector_reduce_double.c:48:     while( len >= 32 * 8 ) {
  20 000f 4881FEFF 		cmpq	$255, %rsi	#, len
  20      000000
  21 0016 0F868C03 		jbe	.L11	#,
  21      0000
  22 001c 4889F1   		movq	%rsi, %rcx	# len, len
  23 001f 90       		.p2align 4,,10
  24              		.p2align 3
  25              	.L3:
  26              	# /usr/lib/gcc/x86_64-linux-gnu/16/include/avx512fintrin.h:13688:   return (__m512d) ((__v8df)__A +
  27 0020 62F1FD48 		vmovapd	704(%rdi), %zmm0	# MEM[(__m512d * {ref-all})src_18 + 704B], MEM[(__m512d * {ref-all})src_1
  27      28470B
  28 0027 62F1FD48 		vmovapd	1216(%rdi), %zmm1	# MEM[(__m512d * {ref-all})src_18 + 1216B], MEM[(__m512d * {ref-all})src
  28      284F13
  29              	# vector_reduce_double.c:118:         len -= 32 * 8 ;
  30 002e 4881E900 		subq	$256, %rcx	#, len
  30      010000
  31              	# vector_reduce_double.c:119:         src += 32 * 8  ;
  32 0035 4881C700 		addq	$2048, %rdi	#, src
  32      080000
  33              	# /usr/lib/gcc/x86_64-linux-gnu/16/include/avx512fintrin.h:13688:   return (__m512d) ((__v8df)__A +
  34 003c 62F1FD48 		vmovapd	-1600(%rdi), %zmm7	# MEM[(__m512d * {ref-all})src_18 + 448B], MEM[(__m512d * {ref-all})src
  34      287FE7
  35 0043 6271FD48 		vmovapd	-1088(%rdi), %zmm9	# MEM[(__m512d * {ref-all})src_18 + 960B], MEM[(__m512d * {ref-all})src
  35      284FEF
  36 004a 62F1FD48 		vaddpd	-320(%rdi), %zmm0, %zmm2	# MEM[(__m512d * {ref-all})src_18 + 1728B], MEM[(__m512d * {ref-al
  36      5857FB
  37 0051 62F1F548 		vaddpd	-1856(%rdi), %zmm1, %zmm3	# MEM[(__m512d * {ref-all})src_18 + 192B], MEM[(__m512d * {ref-al
  37      585FE3
  38 0058 6271C548 		vaddpd	-576(%rdi), %zmm7, %zmm8	# MEM[(__m512d * {ref-all})src_18 + 1472B], MEM[(__m512d * {ref-al
  38      5847F7
  39 005f 6271B548 		vaddpd	-64(%rdi), %zmm9, %zmm10	# MEM[(__m512d * {ref-all})src_18 + 1984B], MEM[(__m512d * {ref-al
  39      5857FF
  40 0066 6271FD48 		vmovapd	-1728(%rdi), %zmm13	# MEM[(__m512d * {ref-all})src_18 + 320B], MEM[(__m512d * {ref-all})sr
  40      286FE5
  41 006d 6271FD48 		vmovapd	-1216(%rdi), %zmm15	# MEM[(__m512d * {ref-all})src_18 + 832B], MEM[(__m512d * {ref-all})sr
  41      287FED
  42 0074 62F1ED48 		vaddpd	%zmm3, %zmm2, %zmm5	# _101, _60, _43
  42      58EB
  43 007a 62F1FD48 		vmovapd	-1472(%rdi), %zmm2	# MEM[(__m512d * {ref-all})src_18 + 576B], MEM[(__m512d * {ref-all})src
  43      2857E9
  44 0081 62F1FD48 		vmovapd	-960(%rdi), %zmm3	# MEM[(__m512d * {ref-all})src_18 + 1088B], MEM[(__m512d * {ref-all})src
  44      285FF1
  45 0088 6251BD48 		vaddpd	%zmm10, %zmm8, %zmm11	# _64, _56, _47
  45      58DA
  46 008e 62719548 		vaddpd	-704(%rdi), %zmm13, %zmm14	# MEM[(__m512d * {ref-all})src_18 + 1344B], MEM[(__m512d * {ref-
  46      5877F5
  47 0095 6271FD48 		vmovapd	-1152(%rdi), %zmm13	# MEM[(__m512d * {ref-all})src_18 + 896B], MEM[(__m512d * {ref-all})sr
  47      286FEE
  48 009c 62F18548 		vaddpd	-192(%rdi), %zmm15, %zmm0	# MEM[(__m512d * {ref-all})src_18 + 1856B], MEM[(__m512d * {ref-a
  48      5847FD
  49 00a3 62F1E548 		vaddpd	-1984(%rdi), %zmm3, %zmm7	# MEM[(__m512d * {ref-all})src_18 + 64B], MEM[(__m512d * {ref-all
  49      587FE1
  50 00aa 6251D548 		vaddpd	%zmm11, %zmm5, %zmm12	# _47, _43, _38
  50      58E3
  51 00b0 62F1ED48 		vaddpd	-448(%rdi), %zmm2, %zmm5	# MEM[(__m512d * {ref-all})src_18 + 1600B], MEM[(__m512d * {ref-al
  51      586FF9
  52 00b7 6271FD48 		vmovapd	-1664(%rdi), %zmm11	# MEM[(__m512d * {ref-all})src_18 + 384B], MEM[(__m512d * {ref-all})sr
  52      285FE6
  53 00be 62F18D48 		vaddpd	%zmm0, %zmm14, %zmm1	# _62, _54, _45
  53      58C8
  54 00c4 62F1FD48 		vmovapd	-896(%rdi), %zmm2	# MEM[(__m512d * {ref-all})src_18 + 1152B], MEM[(__m512d * {ref-all})src
  54      2857F2
  55 00cb 62F1FD48 		vmovapd	-1408(%rdi), %zmm0	# MEM[(__m512d * {ref-all})src_18 + 640B], MEM[(__m512d * {ref-all})src
  55      2847EA
  56 00d2 62719548 		vaddpd	-128(%rdi), %zmm13, %zmm14	# MEM[(__m512d * {ref-all})src_18 + 1920B], MEM[(__m512d * {ref-
  56      5877FE
  57 00d9 6271D548 		vaddpd	%zmm7, %zmm5, %zmm8	# _99, _58, _66
  57      58C7
  58 00df 62F1ED48 		vaddpd	-1920(%rdi), %zmm2, %zmm5	# MEM[(__m512d * {ref-all})src_18 + 128B], MEM[(__m512d * {ref-al
  58      586FE2
  59 00e6 6251F548 		vaddpd	%zmm8, %zmm1, %zmm9	# _66, _45, _49
  59      58C8
  60 00ec 62F1FD48 		vaddpd	-384(%rdi), %zmm0, %zmm1	# MEM[(__m512d * {ref-all})src_18 + 1664B], MEM[(__m512d * {ref-al
  60      584FFA
  61 00f3 6271FD48 		vmovapd	-768(%rdi), %zmm8	# MEM[(__m512d * {ref-all})src_18 + 1280B], MEM[(__m512d * {ref-all})src
  61      2847F4
  62 00fa 62F1FD48 		vmovapd	-1024(%rdi), %zmm0	# MEM[(__m512d * {ref-all})src_18 + 1024B], MEM[(__m512d * {ref-all})sr
  62      2847F0
  63 0101 62519D48 		vaddpd	%zmm9, %zmm12, %zmm10	# _49, _38, _33
  63      58D1
  64 0107 6271A548 		vaddpd	-640(%rdi), %zmm11, %zmm12	# MEM[(__m512d * {ref-all})src_18 + 1408B], MEM[(__m512d * {ref-
  64      5867F6
  65 010e 6271FD48 		vmovapd	-1280(%rdi), %zmm11	# MEM[(__m512d * {ref-all})src_18 + 768B], MEM[(__m512d * {ref-all})sr
  65      285FEC
  66 0115 62F1F548 		vaddpd	%zmm5, %zmm1, %zmm3	# _100, _59, _67
  66      58DD
  67 011b 6271BD48 		vaddpd	-1792(%rdi), %zmm8, %zmm9	# MEM[(__m512d * {ref-all})src_18 + 256B], MEM[(__m512d * {ref-al
  67      584FE4
  68 0122 62F1FD48 		vaddpd	-2048(%rdi), %zmm0, %zmm1	# MEM[(__m512d * {ref-all})src_18], MEM[(__m512d * {ref-all})src_
  68      584FE0
  69 0129 62519D48 		vaddpd	%zmm14, %zmm12, %zmm15	# _63, _55, _46
  69      58FE
  70 012f 6271FD48 		vmovapd	-1536(%rdi), %zmm14	# MEM[(__m512d * {ref-all})src_18 + 512B], MEM[(__m512d * {ref-all})sr
  70      2877E8
  71 0136 6271A548 		vaddpd	-256(%rdi), %zmm11, %zmm12	# MEM[(__m512d * {ref-all})src_18 + 1792B], MEM[(__m512d * {ref-
  71      5867FC
  72 013d 62F18548 		vaddpd	%zmm3, %zmm15, %zmm7	# _67, _46, _37
  72      58FB
  73 0143 62718D48 		vaddpd	-512(%rdi), %zmm14, %zmm15	# MEM[(__m512d * {ref-all})src_18 + 1536B], MEM[(__m512d * {ref-
  73      587FF8
  74 014a 6251B548 		vaddpd	%zmm12, %zmm9, %zmm13	# _61, _53, _44
  74      58EC
  75 0150 62F18548 		vaddpd	%zmm1, %zmm15, %zmm2	# _98, _57, _65
  75      58D1
  76 0156 62F19548 		vaddpd	%zmm2, %zmm13, %zmm5	# _65, _44, _48
  76      58EA
  77 015c 62F1C548 		vaddpd	%zmm5, %zmm7, %zmm3	# _48, _37, _39
  77      58DD
  78 0162 6271AD48 		vaddpd	%zmm3, %zmm10, %zmm10	# _39, _33, _27
  78      58D3
  79              	# vector_reduce_double.c:117:         vaccumulate += r000 ;
  80 0168 62D1DD48 		vaddpd	%zmm10, %zmm4, %zmm4	# _27, vaccumulate, vaccumulate
  80      58E2
  81              	# vector_reduce_double.c:48:     while( len >= 32 * 8 ) {
  82 016e 4881F9FF 		cmpq	$255, %rcx	#, len
  82      000000
  83 0175 0F87A5FE 		ja	.L3	#,
  83      FFFF
  84 017b 400FB6C6 		movzbl	%sil, %eax	# len, len
  85 017f 48C1EE08 		shrq	$8, %rsi	#, _389
  86 0183 48C1E60B 		salq	$11, %rsi	#, _412
  87 0187 4801F2   		addq	%rsi, %rdx	# _412, src
  88              	.L2:
  89              	# vector_reduce_double.c:124:     while( len >= 16 * 8 ) {
  90 018a 4883F87F 		cmpq	$127, %rax	#, len
  91 018e 0F86AA00 		jbe	.L4	#,
  91      0000
  92              	# /usr/lib/gcc/x86_64-linux-gnu/16/include/avx512fintrin.h:13688:   return (__m512d) ((__v8df)__A +
  93 0194 62F1FD48 		vmovapd	(%rdx), %zmm7	# MEM[(__m512d * {ref-all})src_11], MEM[(__m512d * {ref-all})src_11]
  93      283A
  94 019a 6271FD48 		vmovapd	256(%rdx), %zmm9	# MEM[(__m512d * {ref-all})src_11 + 256B], MEM[(__m512d * {ref-all})src_1
  94      284A04
  95              	# vector_reduce_double.c:161:         len -= 16 * 8 ;
  96 01a1 4883C080 		addq	$-128, %rax	#, len
  97              	# vector_reduce_double.c:162:         src += 16 * 8  ;
  98 01a5 4881C200 		addq	$1024, %rdx	#, src
  98      040000
  99              	# /usr/lib/gcc/x86_64-linux-gnu/16/include/avx512fintrin.h:13688:   return (__m512d) ((__v8df)__A +
 100 01ac 6271FD48 		vmovapd	-896(%rdx), %zmm13	# MEM[(__m512d * {ref-all})src_11 + 128B], MEM[(__m512d * {ref-all})src
 100      286AF2
 101 01b3 6271FD48 		vmovapd	-640(%rdx), %zmm15	# MEM[(__m512d * {ref-all})src_11 + 384B], MEM[(__m512d * {ref-all})src
 101      287AF6
 102 01ba 6271C548 		vaddpd	-512(%rdx), %zmm7, %zmm8	# MEM[(__m512d * {ref-all})src_11 + 512B], MEM[(__m512d * {ref-all
 102      5842F8
 103 01c1 6271B548 		vaddpd	-256(%rdx), %zmm9, %zmm11	# MEM[(__m512d * {ref-all})src_11 + 768B], MEM[(__m512d * {ref-al
 103      585AFC
 104 01c8 62719548 		vaddpd	-384(%rdx), %zmm13, %zmm14	# MEM[(__m512d * {ref-all})src_11 + 640B], MEM[(__m512d * {ref-a
 104      5872FA
 105 01cf 62F18548 		vaddpd	-128(%rdx), %zmm15, %zmm0	# MEM[(__m512d * {ref-all})src_11 + 896B], MEM[(__m512d * {ref-al
 105      5842FE
 106 01d6 62F1FD48 		vmovapd	-960(%rdx), %zmm2	# MEM[(__m512d * {ref-all})src_11 + 64B], MEM[(__m512d * {ref-all})src_1
 106      2852F1
 107 01dd 6271FD48 		vmovapd	-704(%rdx), %zmm10	# MEM[(__m512d * {ref-all})src_11 + 320B], MEM[(__m512d * {ref-all})src
 107      2852F5
 108 01e4 6251BD48 		vaddpd	%zmm11, %zmm8, %zmm12	# _253, _249, _257
 108      58E3
 109 01ea 6271FD48 		vmovapd	-832(%rdx), %zmm9	# MEM[(__m512d * {ref-all})src_11 + 192B], MEM[(__m512d * {ref-all})src_
 109      284AF3
 110 01f1 62F18D48 		vaddpd	%zmm0, %zmm14, %zmm1	# _255, _251, _259
 110      58C8
 111 01f7 62F1ED48 		vaddpd	-448(%rdx), %zmm2, %zmm3	# MEM[(__m512d * {ref-all})src_11 + 576B], MEM[(__m512d * {ref-all
 111      585AF9
 112 01fe 62F1AD48 		vaddpd	-192(%rdx), %zmm10, %zmm7	# MEM[(__m512d * {ref-all})src_11 + 832B], MEM[(__m512d * {ref-al
 112      587AFD
 113 0205 6271B548 		vaddpd	-320(%rdx), %zmm9, %zmm11	# MEM[(__m512d * {ref-all})src_11 + 704B], MEM[(__m512d * {ref-al
 113      585AFB
 114 020c 62F19D48 		vaddpd	%zmm1, %zmm12, %zmm5	# _259, _257, _261
 114      58E9
 115 0212 6271FD48 		vmovapd	-576(%rdx), %zmm12	# MEM[(__m512d * {ref-all})src_11 + 448B], MEM[(__m512d * {ref-all})src
 115      2862F7
 116 0219 6271E548 		vaddpd	%zmm7, %zmm3, %zmm8	# _254, _250, _258
 116      58C7
 117 021f 62719D48 		vaddpd	-64(%rdx), %zmm12, %zmm13	# MEM[(__m512d * {ref-all})src_11 + 960B], MEM[(__m512d * {ref-al
 117      586AFF
 118 0226 6251A548 		vaddpd	%zmm13, %zmm11, %zmm14	# _256, _252, _260
 118      58F5
 119 022c 6251BD48 		vaddpd	%zmm14, %zmm8, %zmm15	# _260, _258, _262
 119      58FE
 120 0232 62D1D548 		vaddpd	%zmm15, %zmm5, %zmm0	# _262, _261, _263
 120      58C7
 121              	# vector_reduce_double.c:160:         vaccumulate += r000 ;
 122 0238 62F1DD48 		vaddpd	%zmm0, %zmm4, %zmm4	# _263, vaccumulate, vaccumulate
 122      58E0
 123              	.L4:
 124              	# vector_reduce_double.c:167:     while( len >= 8 * 8 ) {
 125 023e 4883F83F 		cmpq	$63, %rax	#, len
 126 0242 765A     		jbe	.L5	#,
 127              	# /usr/lib/gcc/x86_64-linux-gnu/16/include/avx512fintrin.h:13688:   return (__m512d) ((__v8df)__A +
 128 0244 62F1FD48 		vmovapd	(%rdx), %zmm1	# MEM[(__m512d * {ref-all})src_209], MEM[(__m512d * {ref-all})src_209]
 128      280A
 129 024a 62F1FD48 		vmovapd	128(%rdx), %zmm2	# MEM[(__m512d * {ref-all})src_209 + 128B], MEM[(__m512d * {ref-all})src_
 129      285202
 130              	# vector_reduce_double.c:187:         len -= 8 * 8 ;
 131 0251 4883E840 		subq	$64, %rax	#, len
 132              	# vector_reduce_double.c:188:         src += 8 * 8  ;
 133 0255 4881C200 		addq	$512, %rdx	#, src
 133      020000
 134              	# /usr/lib/gcc/x86_64-linux-gnu/16/include/avx512fintrin.h:13688:   return (__m512d) ((__v8df)__A +
 135 025c 62F1FD48 		vmovapd	-448(%rdx), %zmm7	# MEM[(__m512d * {ref-all})src_209 + 64B], MEM[(__m512d * {ref-all})src_
 135      287AF9
 136 0263 6271FD48 		vmovapd	-320(%rdx), %zmm9	# MEM[(__m512d * {ref-all})src_209 + 192B], MEM[(__m512d * {ref-all})src
 136      284AFB
 137 026a 62F1F548 		vaddpd	-256(%rdx), %zmm1, %zmm5	# MEM[(__m512d * {ref-all})src_209 + 256B], MEM[(__m512d * {ref-al
 137      586AFC
 138 0271 62F1ED48 		vaddpd	-128(%rdx), %zmm2, %zmm3	# MEM[(__m512d * {ref-all})src_209 + 384B], MEM[(__m512d * {ref-al
 138      585AFE
 139 0278 6271C548 		vaddpd	-192(%rdx), %zmm7, %zmm8	# MEM[(__m512d * {ref-all})src_209 + 320B], MEM[(__m512d * {ref-al
 139      5842FD
 140 027f 6271B548 		vaddpd	-64(%rdx), %zmm9, %zmm11	# MEM[(__m512d * {ref-all})src_209 + 448B], MEM[(__m512d * {ref-al
 140      585AFF
 141 0286 6271D548 		vaddpd	%zmm3, %zmm5, %zmm10	# _222, _220, _224
 141      58D3
 142 028c 6251BD48 		vaddpd	%zmm11, %zmm8, %zmm12	# _223, _221, _225
 142      58E3
 143 0292 6251AD48 		vaddpd	%zmm12, %zmm10, %zmm13	# _225, _224, _226
 143      58EC
 144              	# vector_reduce_double.c:186:         vaccumulate += r000 ;
 145 0298 62D1DD48 		vaddpd	%zmm13, %zmm4, %zmm4	# _226, vaccumulate, vaccumulate
 145      58E5
 146              	.L5:
 147              	# vector_reduce_double.c:193:     while( len >= 4 * 8 ) {
 148 029e 4883F81F 		cmpq	$31, %rax	#, len
 149 02a2 7632     		jbe	.L6	#,
 150              	# /usr/lib/gcc/x86_64-linux-gnu/16/include/avx512fintrin.h:13688:   return (__m512d) ((__v8df)__A +
 151 02a4 6271FD48 		vmovapd	(%rdx), %zmm14	# MEM[(__m512d * {ref-all})src_196], MEM[(__m512d * {ref-all})src_196]
 151      2832
 152 02aa 62F1FD48 		vmovapd	64(%rdx), %zmm0	# MEM[(__m512d * {ref-all})src_196 + 64B], MEM[(__m512d * {ref-all})src_19
 152      284201
 153              	# vector_reduce_double.c:204:         len -= 4 * 8 ;
 154 02b1 4883E820 		subq	$32, %rax	#, len
 155              	# vector_reduce_double.c:205:         src += 4 * 8  ;
 156 02b5 4881C200 		addq	$256, %rdx	#, src
 156      010000
 157              	# /usr/lib/gcc/x86_64-linux-gnu/16/include/avx512fintrin.h:13688:   return (__m512d) ((__v8df)__A +
 158 02bc 62718D48 		vaddpd	-128(%rdx), %zmm14, %zmm15	# MEM[(__m512d * {ref-all})src_196 + 128B], MEM[(__m512d * {ref-
 158      587AFE
 159 02c3 62F1FD48 		vaddpd	-64(%rdx), %zmm0, %zmm1	# MEM[(__m512d * {ref-all})src_196 + 192B], MEM[(__m512d * {ref-all
 159      584AFF
 160 02ca 62F18548 		vaddpd	%zmm1, %zmm15, %zmm5	# _204, _203, _205
 160      58E9
 161              	# vector_reduce_double.c:203:         vaccumulate += r000 ;
 162 02d0 62F1DD48 		vaddpd	%zmm5, %zmm4, %zmm4	# _205, vaccumulate, vaccumulate
 162      58E5
 163              	.L6:
 164              	# vector_reduce_double.c:210:     while( len >= 2 * 8 ) {
 165 02d6 4883F80F 		cmpq	$15, %rax	#, len
 166 02da 761B     		jbe	.L7	#,
 167              	# /usr/lib/gcc/x86_64-linux-gnu/16/include/avx512fintrin.h:13688:   return (__m512d) ((__v8df)__A +
 168 02dc 62F1FD48 		vmovapd	(%rdx), %zmm2	# MEM[(__m512d * {ref-all})src_187], MEM[(__m512d * {ref-all})src_187]
 168      2812
 169              	# vector_reduce_double.c:216:         len -= 2 * 8 ;
 170 02e2 4883E810 		subq	$16, %rax	#, len
 171              	# vector_reduce_double.c:217:         src += 2 * 8  ;
 172 02e6 4883EA80 		subq	$-128, %rdx	#, src
 173              	# /usr/lib/gcc/x86_64-linux-gnu/16/include/avx512fintrin.h:13688:   return (__m512d) ((__v8df)__A +
 174 02ea 62F1ED48 		vaddpd	-64(%rdx), %zmm2, %zmm3	# MEM[(__m512d * {ref-all})src_187 + 64B], MEM[(__m512d * {ref-all}
 174      585AFF
 175              	# vector_reduce_double.c:215:         vaccumulate += r000 ;
 176 02f1 62F1DD48 		vaddpd	%zmm3, %zmm4, %zmm4	# _192, vaccumulate, vaccumulate
 176      58E3
 177              	.L7:
 178              	# vector_reduce_double.c:222:     while( len >= 1 * 8 ) {
 179 02f7 4883F807 		cmpq	$7, %rax	#, len
 180 02fb 760E     		jbe	.L8	#,
 181              	# vector_reduce_double.c:224:         vaccumulate += r000 ;
 182 02fd 62F1DD48 		vaddpd	(%rdx), %zmm4, %zmm4	# MEM[(__m512d * {ref-all})src_180], vaccumulate, vaccumulate
 182      5822
 183              	# vector_reduce_double.c:225:         len -= 1 * 8 ;
 184 0303 4883E808 		subq	$8, %rax	#, len
 185              	# vector_reduce_double.c:226:         src += 1 * 8  ;
 186 0307 4883C240 		addq	$64, %rdx	#, src
 187              	.L8:
 188              	# /usr/lib/gcc/x86_64-linux-gnu/16/include/avx512fintrin.h:8979:   return (__m256d) __builtin_ia32_
 189 030b 62D3FD48 		vextractf64x4	$0x1, %zmm4, %ymm10	# vaccumulate, tmp352
 189      1BE201
 190              	# /usr/lib/gcc/x86_64-linux-gnu/16/include/avx512fintrin.h:16532:   __MM512_REDUCE_OP (+);
 191 0312 C5AD58FC 		vaddpd	%ymm4, %ymm10, %ymm7	# tmp354, tmp352, __T3
 192              	# /usr/lib/gcc/x86_64-linux-gnu/16/include/avxintrin.h:464:   return (__m128d) __builtin_ia32_vextr
 193 0316 62D3FD28 		vextractf64x2	$0x1, %ymm7, %xmm8	# __T3, tmp356
 193      19F801
 194              	# /usr/lib/gcc/x86_64-linux-gnu/16/include/avx512fintrin.h:16532:   __MM512_REDUCE_OP (+);
 195 031d C53958CF 		vaddpd	%xmm7, %xmm8, %xmm9	# tmp357, tmp356, _176
 196 0321 C4413115 		vunpckhpd	%xmm9, %xmm9, %xmm12	# _176, _178
 196      E1
 197 0326 C4413358 		vaddsd	%xmm12, %xmm9, %xmm13	# _178, _177, _179
 197      EC
 198              	# vector_reduce_double.c:228:     initial += _mm512_reduce_
 199 032b C59358C6 		vaddsd	%xmm6, %xmm13, %xmm0	# initial, _179, <retval>
 200              	# vector_reduce_double.c:233:     for( size_t i = 0 ; i < l
 201 032f 4885C0   		testq	%rax, %rax	# len
 202 0332 746A     		je	.L1	#,
 203 0334 488D70FF 		leaq	-1(%rax), %rsi	#, _398
 204 0338 4883FE02 		cmpq	$2, %rsi	#, _398
 205 033c 7672     		jbe	.L12	#,
 206 033e C5FB5832 		vaddsd	(%rdx), %xmm0, %xmm6	# BIT_FIELD_REF <MEM <const vector(4) double> [(const double *)src_271
 207 0342 C54B5872 		vaddsd	8(%rdx), %xmm6, %xmm14	# BIT_FIELD_REF <MEM <const vector(4) double> [(const double *)src_2
 207      08
 208              	# vector_reduce_double.c:234:         initial += *src ;
 209 0347 C50B587A 		vaddsd	16(%rdx), %xmm14, %xmm15	# BIT_FIELD_REF <MEM <const vector(4) double> [(const double *)src
 209      10
 210 034c C5835842 		vaddsd	24(%rdx), %xmm15, %xmm0	# BIT_FIELD_REF <MEM <const vector(4) double> [(const double *)src_
 210      18
 211 0351 4883F804 		cmpq	$4, %rax	#, len
 212 0355 7447     		je	.L1	#,
 213 0357 4883C220 		addq	$32, %rdx	#, src
 214              	# vector_reduce_double.c:233:     for( size_t i = 0 ; i < l
 215 035b 41B80400 		movl	$4, %r8d	#, i
 215      0000
 216              	.L10:
 217 0361 49C1E802 		shrq	$2, %r8	#, tmp363
 218              	# vector_reduce_double.c:234:         initial += *src ;
 219 0365 C5FB5802 		vaddsd	(%rdx), %xmm0, %xmm0	# *src_21, <retval>, <retval>
 220 0369 4183F001 		xorl	$1, %r8d	#, _403
 221              	# vector_reduce_double.c:233:     for( size_t i = 0 ; i < l
 222 036d 4180F801 		cmpb	$1, %r8b	#, _403
 223 0371 4D19C9   		sbbq	%r9, %r9	# i_399
 224 0374 4183E104 		andl	$4, %r9d	#, i_399
 225 0378 49FFC1   		incq	%r9	# i_399
 226              	# vector_reduce_double.c:233:     for( size_t i = 0 ; i < l
 227 037b 4939C1   		cmpq	%rax, %r9	# len, i_399
 228 037e 731E     		jnb	.L1	#,
 229              	# vector_reduce_double.c:233:     for( size_t i = 0 ; i < l
 230 0380 4180F801 		cmpb	$1, %r8b	#, _403
 231              	# vector_reduce_double.c:234:         initial += *src ;
 232 0384 C5FB5842 		vaddsd	8(%rdx), %xmm0, %xmm0	# MEM[(const double *)src_21 + 8B], <retval>, <retval>
 232      08
 233              	# vector_reduce_double.c:233:     for( size_t i = 0 ; i < l
 234 0389 4D19D2   		sbbq	%r10, %r10	# i_373
 235 038c 4183E204 		andl	$4, %r10d	#, i_373
 236 0390 4983C202 		addq	$2, %r10	#, i_373
 237              	# vector_reduce_double.c:233:     for( size_t i = 0 ; i < l
 238 0394 4939C2   		cmpq	%rax, %r10	# len, i_373
 239 0397 7305     		jnb	.L1	#,
 240              	# vector_reduce_double.c:234:         initial += *src ;
 241 0399 C5FB5842 		vaddsd	16(%rdx), %xmm0, %xmm0	# MEM[(const double *)src_21 + 16B], <retval>, <retval>
 241      10
 242              	.L1:
 243 039e C5F877   		vzeroupper
 244              	# vector_reduce_double.c:438: }
 245 03a1 C3       		ret	
 246              		.p2align 4,,10
 247 03a2 660F1F44 		.p2align 3
 247      0000
 248              	.L11:
 249              	# vector_reduce_double.c:48:     while( len >= 32 * 8 ) {
 250 03a8 4889F0   		movq	%rsi, %rax	# len, len
 251 03ab E9DAFDFF 		jmp	.L2	#
 251      FF
 252              	.L12:
 253              	# vector_reduce_double.c:233:     for( size_t i = 0 ; i < l
 254 03b0 4531C0   		xorl	%r8d, %r8d	# i
 255 03b3 EBAC     		jmp	.L10	#
 256              		.cfi_endproc
 257              	.LFE7302:
 259              		.ident	"GCC: (Ubuntu 16-20260315-1ubuntu1~24~ppa1) 16.0.1 20260315 (experimental) [trunk r16-8100-
 260              		.section	.note.GNU-stack,"",@progbits
 261              		.section	.note.gnu.property,"a"
 262              		.align 8
 263 0000 04000000 		.long	1f - 0f
 264 0004 10000000 		.long	4f - 1f
 265 0008 05000000 		.long	5
 266              	0:
 267 000c 474E5500 		.string	"GNU"
 268              	1:
 269              		.align 8
 270 0010 020000C0 		.long	0xc0000002
 271 0014 04000000 		.long	3f - 2f
 272              	2:
 273 0018 03000000 		.long	0x3
 274              	3:
 275 001c 00000000 		.align 8
 276              	4:
