multiline_comment|/*&n; * Basic two-word fraction declaration and manipulation.&n; */
DECL|macro|_FP_FRAC_DECL_2
mdefine_line|#define _FP_FRAC_DECL_2(X)&t;_FP_W_TYPE X##_f0, X##_f1
DECL|macro|_FP_FRAC_COPY_2
mdefine_line|#define _FP_FRAC_COPY_2(D,S)&t;(D##_f0 = S##_f0, D##_f1 = S##_f1)
DECL|macro|_FP_FRAC_SET_2
mdefine_line|#define _FP_FRAC_SET_2(X,I)&t;__FP_FRAC_SET_2(X, I)
DECL|macro|_FP_FRAC_HIGH_2
mdefine_line|#define _FP_FRAC_HIGH_2(X)&t;(X##_f1)
DECL|macro|_FP_FRAC_LOW_2
mdefine_line|#define _FP_FRAC_LOW_2(X)&t;(X##_f0)
DECL|macro|_FP_FRAC_WORD_2
mdefine_line|#define _FP_FRAC_WORD_2(X,w)&t;(X##_f##w)
DECL|macro|_FP_FRAC_SLL_2
mdefine_line|#define _FP_FRAC_SLL_2(X,N)&t;&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if ((N) &lt; _FP_W_TYPE_SIZE)&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        if (__builtin_constant_p(N) &amp;&amp; (N) == 1) &t;&t;&t;&bslash;&n;          {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;            X##_f1 = X##_f1 + X##_f1 + (((_FP_WS_TYPE)(X##_f0)) &lt; 0);&t;&bslash;&n;            X##_f0 += X##_f0;&t;&t;&t;&t;&t;&t;&bslash;&n;          }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;          {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    X##_f1 = X##_f1 &lt;&lt; (N) | X##_f0 &gt;&gt; (_FP_W_TYPE_SIZE - (N));&t;&bslash;&n;&t;    X##_f0 &lt;&lt;= (N);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;X##_f1 = X##_f0 &lt;&lt; ((N) - _FP_W_TYPE_SIZE);&t;&t;&t;&bslash;&n;&t;X##_f0 = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|_FP_FRAC_SRL_2
mdefine_line|#define _FP_FRAC_SRL_2(X,N)&t;&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if ((N) &lt; _FP_W_TYPE_SIZE)&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;X##_f0 = X##_f0 &gt;&gt; (N) | X##_f1 &lt;&lt; (_FP_W_TYPE_SIZE - (N));&t;&bslash;&n;&t;X##_f1 &gt;&gt;= (N);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;X##_f0 = X##_f1 &gt;&gt; ((N) - _FP_W_TYPE_SIZE);&t;&t;&t;&bslash;&n;&t;X##_f1 = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/* Right shift with sticky-lsb.  */
DECL|macro|_FP_FRAC_SRS_2
mdefine_line|#define _FP_FRAC_SRS_2(X,N,sz)&t;&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if ((N) &lt; _FP_W_TYPE_SIZE)&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;X##_f0 = (X##_f1 &lt;&lt; (_FP_W_TYPE_SIZE - (N)) | X##_f0 &gt;&gt; (N) |&t;&bslash;&n;&t;&t;  (__builtin_constant_p(N) &amp;&amp; (N) == 1&t;&t;&t;&bslash;&n;&t;&t;   ? X##_f0 &amp; 1&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;   : (X##_f0 &lt;&lt; (_FP_W_TYPE_SIZE - (N))) != 0));&t;&bslash;&n;&t;X##_f1 &gt;&gt;= (N);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;X##_f0 = (X##_f1 &gt;&gt; ((N) - _FP_W_TYPE_SIZE) |&t;&t;&t;&bslash;&n;&t;          (((X##_f1 &lt;&lt; (sz - (N))) | X##_f0) != 0));&t;&t;&bslash;&n;&t;X##_f1 = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|_FP_FRAC_ADDI_2
mdefine_line|#define _FP_FRAC_ADDI_2(X,I) &bslash;&n;  __FP_FRAC_ADDI_2(X##_f1, X##_f0, I)
DECL|macro|_FP_FRAC_ADD_2
mdefine_line|#define _FP_FRAC_ADD_2(R,X,Y) &bslash;&n;  __FP_FRAC_ADD_2(R##_f1, R##_f0, X##_f1, X##_f0, Y##_f1, Y##_f0)
DECL|macro|_FP_FRAC_SUB_2
mdefine_line|#define _FP_FRAC_SUB_2(R,X,Y) &bslash;&n;  __FP_FRAC_SUB_2(R##_f1, R##_f0, X##_f1, X##_f0, Y##_f1, Y##_f0)
DECL|macro|_FP_FRAC_CLZ_2
mdefine_line|#define _FP_FRAC_CLZ_2(R,X)&t;&bslash;&n;  do {&t;&t;&t;&t;&bslash;&n;    if (X##_f1)&t;&t;&t;&bslash;&n;      __FP_CLZ(R,X##_f1);&t;&bslash;&n;    else &t;&t;&t;&bslash;&n;    {&t;&t;&t;&t;&bslash;&n;      __FP_CLZ(R,X##_f0);&t;&bslash;&n;      R += _FP_W_TYPE_SIZE;&t;&bslash;&n;    }&t;&t;&t;&t;&bslash;&n;  } while(0)
multiline_comment|/* Predicates */
DECL|macro|_FP_FRAC_NEGP_2
mdefine_line|#define _FP_FRAC_NEGP_2(X)&t;((_FP_WS_TYPE)X##_f1 &lt; 0)
DECL|macro|_FP_FRAC_ZEROP_2
mdefine_line|#define _FP_FRAC_ZEROP_2(X)&t;((X##_f1 | X##_f0) == 0)
DECL|macro|_FP_FRAC_OVERP_2
mdefine_line|#define _FP_FRAC_OVERP_2(fs,X)&t;(X##_f1 &amp; _FP_OVERFLOW_##fs)
DECL|macro|_FP_FRAC_EQ_2
mdefine_line|#define _FP_FRAC_EQ_2(X, Y)&t;(X##_f1 == Y##_f1 &amp;&amp; X##_f0 == Y##_f0)
DECL|macro|_FP_FRAC_GT_2
mdefine_line|#define _FP_FRAC_GT_2(X, Y)&t;&bslash;&n;  ((X##_f1 &gt; Y##_f1) || (X##_f1 == Y##_f1 &amp;&amp; X##_f0 &gt; Y##_f0))
DECL|macro|_FP_FRAC_GE_2
mdefine_line|#define _FP_FRAC_GE_2(X, Y)&t;&bslash;&n;  ((X##_f1 &gt; Y##_f1) || (X##_f1 == Y##_f1 &amp;&amp; X##_f0 &gt;= Y##_f0))
DECL|macro|_FP_ZEROFRAC_2
mdefine_line|#define _FP_ZEROFRAC_2&t;&t;0, 0
DECL|macro|_FP_MINFRAC_2
mdefine_line|#define _FP_MINFRAC_2&t;&t;0, 1
multiline_comment|/*&n; * Internals &n; */
DECL|macro|__FP_FRAC_SET_2
mdefine_line|#define __FP_FRAC_SET_2(X,I1,I0)&t;(X##_f0 = I0, X##_f1 = I1)
DECL|macro|__FP_CLZ_2
mdefine_line|#define __FP_CLZ_2(R, xh, xl)&t;&bslash;&n;  do {&t;&t;&t;&t;&bslash;&n;    if (xh)&t;&t;&t;&bslash;&n;      __FP_CLZ(R,xl);&t;&t;&bslash;&n;    else &t;&t;&t;&bslash;&n;    {&t;&t;&t;&t;&bslash;&n;      __FP_CLZ(R,xl);&t;&t;&bslash;&n;      R += _FP_W_TYPE_SIZE;&t;&bslash;&n;    }&t;&t;&t;&t;&bslash;&n;  } while(0)
macro_line|#if 0
macro_line|#ifndef __FP_FRAC_ADDI_2
mdefine_line|#define __FP_FRAC_ADDI_2(xh, xl, i) &bslash;&n;  (xh += ((xl += i) &lt; i))
macro_line|#endif
macro_line|#ifndef __FP_FRAC_ADD_2
mdefine_line|#define __FP_FRAC_ADD_2(rh, rl, xh, xl, yh, yl) &bslash;&n;  (rh = xh + yh + ((rl = xl + yl) &lt; xl))
macro_line|#endif
macro_line|#ifndef __FP_FRAC_SUB_2
mdefine_line|#define __FP_FRAC_SUB_2(rh, rl, xh, xl, yh, yl) &bslash;&n;  (rh = xh - yh - ((rl = xl - yl) &gt; xl))
macro_line|#endif
macro_line|#else
DECL|macro|__FP_FRAC_ADDI_2
macro_line|#undef __FP_FRAC_ADDI_2
DECL|macro|__FP_FRAC_ADDI_2
mdefine_line|#define __FP_FRAC_ADDI_2(xh, xl, i)&t;add_ssaaaa(xh, xl, xh, xl, 0, i)
DECL|macro|__FP_FRAC_ADD_2
macro_line|#undef __FP_FRAC_ADD_2
DECL|macro|__FP_FRAC_ADD_2
mdefine_line|#define __FP_FRAC_ADD_2&t;&t;&t;add_ssaaaa
DECL|macro|__FP_FRAC_SUB_2
macro_line|#undef __FP_FRAC_SUB_2
DECL|macro|__FP_FRAC_SUB_2
mdefine_line|#define __FP_FRAC_SUB_2&t;&t;&t;sub_ddmmss
macro_line|#endif
multiline_comment|/*&n; * Unpack the raw bits of a native fp value.  Do not classify or&n; * normalize the data.&n; */
DECL|macro|_FP_UNPACK_RAW_2
mdefine_line|#define _FP_UNPACK_RAW_2(fs, X, val)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_##fs _flo; _flo.flt = (val);&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    X##_f0 = _flo.bits.frac0;&t;&t;&t;&t;&bslash;&n;    X##_f1 = _flo.bits.frac1;&t;&t;&t;&t;&bslash;&n;    X##_e  = _flo.bits.exp;&t;&t;&t;&t;&bslash;&n;    X##_s  = _flo.bits.sign;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/*&n; * Repack the raw bits of a native fp value.&n; */
DECL|macro|_FP_PACK_RAW_2
mdefine_line|#define _FP_PACK_RAW_2(fs, val, X)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_##fs _flo;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _flo.bits.frac0 = X##_f0;&t;&t;&t;&t;&bslash;&n;    _flo.bits.frac1 = X##_f1;&t;&t;&t;&t;&bslash;&n;    _flo.bits.exp   = X##_e;&t;&t;&t;&t;&bslash;&n;    _flo.bits.sign  = X##_s;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    (val) = _flo.flt;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/*&n; * Multiplication algorithms:&n; */
multiline_comment|/* Given a 1W * 1W =&gt; 2W primitive, do the extended multiplication.  */
DECL|macro|_FP_MUL_MEAT_2_wide
mdefine_line|#define _FP_MUL_MEAT_2_wide(fs, R, X, Y, doit)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_FRAC_DECL_4(_z); _FP_FRAC_DECL_2(_b); _FP_FRAC_DECL_2(_c);&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    doit(_FP_FRAC_WORD_4(_z,1), _FP_FRAC_WORD_4(_z,0), X##_f0, Y##_f0); &bslash;&n;    doit(_b_f1, _b_f0, X##_f0, Y##_f1);&t;&t;&t;&t;&t;&bslash;&n;    doit(_c_f1, _c_f0, X##_f1, Y##_f0);&t;&t;&t;&t;&t;&bslash;&n;    doit(_FP_FRAC_WORD_4(_z,3), _FP_FRAC_WORD_4(_z,2), X##_f1, Y##_f1); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __FP_FRAC_ADD_4(_FP_FRAC_WORD_4(_z,3),_FP_FRAC_WORD_4(_z,2),&t;&bslash;&n;&t;&t;    _FP_FRAC_WORD_4(_z,1),_FP_FRAC_WORD_4(_z,0),&t;&bslash;&n;&t;&t;    0, _b_f1, _b_f0, 0,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;    _FP_FRAC_WORD_4(_z,3),_FP_FRAC_WORD_4(_z,2),&t;&bslash;&n;&t;&t;    _FP_FRAC_WORD_4(_z,1),_FP_FRAC_WORD_4(_z,0));&t;&bslash;&n;    __FP_FRAC_ADD_4(_FP_FRAC_WORD_4(_z,3),_FP_FRAC_WORD_4(_z,2),&t;&bslash;&n;&t;&t;    _FP_FRAC_WORD_4(_z,1),_FP_FRAC_WORD_4(_z,0),&t;&bslash;&n;&t;&t;    0, _c_f1, _c_f0, 0,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;    _FP_FRAC_WORD_4(_z,3),_FP_FRAC_WORD_4(_z,2),&t;&bslash;&n;&t;&t;    _FP_FRAC_WORD_4(_z,1),_FP_FRAC_WORD_4(_z,0));&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    /* Normalize since we know where the msb of the multiplicands&t;&bslash;&n;       were (bit B), we know that the msb of the of the product is&t;&bslash;&n;       at either 2B or 2B-1.  */&t;&t;&t;&t;&t;&bslash;&n;    _FP_FRAC_SRS_4(_z, _FP_WFRACBITS_##fs-1, 2*_FP_WFRACBITS_##fs);&t;&bslash;&n;    R##_f0 = _FP_FRAC_WORD_4(_z,0);&t;&t;&t;&t;&t;&bslash;&n;    R##_f1 = _FP_FRAC_WORD_4(_z,1);&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/* This next macro appears to be totally broken. Fortunately nowhere&n; * seems to use it :-&gt; The problem is that we define _z[4] but&n; * then use it in _FP_FRAC_SRS_4, which will attempt to access&n; * _z_f[n] which will cause an error. The fix probably involves &n; * declaring it with _FP_FRAC_DECL_4, see previous macro. -- PMM 02/1998 &n; */
DECL|macro|_FP_MUL_MEAT_2_gmp
mdefine_line|#define _FP_MUL_MEAT_2_gmp(fs, R, X, Y)&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_W_TYPE _x[2], _y[2], _z[4];&t;&t;&t;&t;&t;&bslash;&n;    _x[0] = X##_f0; _x[1] = X##_f1;&t;&t;&t;&t;&t;&bslash;&n;    _y[0] = Y##_f0; _y[1] = Y##_f1;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    mpn_mul_n(_z, _x, _y, 2);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    /* Normalize since we know where the msb of the multiplicands&t;&bslash;&n;       were (bit B), we know that the msb of the of the product is&t;&bslash;&n;       at either 2B or 2B-1.  */&t;&t;&t;&t;&t;&bslash;&n;    _FP_FRAC_SRS_4(_z, _FP_WFRACBITS##_fs-1, 2*_FP_WFRACBITS_##fs);&t;&bslash;&n;    R##_f0 = _z[0];&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    R##_f1 = _z[1];&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/*&n; * Division algorithms:&n; * This seems to be giving me difficulties -- PMM &n; * Look, NetBSD seems to be able to comment algorithms. Can&squot;t you?&n; * I&squot;ve thrown printks at the problem.&n; * This now appears to work, but I still don&squot;t really know why.&n; * Also, I don&squot;t think the result is properly normalised...&n; */
DECL|macro|_FP_DIV_MEAT_2_udiv_64
mdefine_line|#define _FP_DIV_MEAT_2_udiv_64(fs, R, X, Y)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    extern void _fp_udivmodti4(_FP_W_TYPE q[2], _FP_W_TYPE r[2],&t;&bslash;&n;&t;&t;&t;       _FP_W_TYPE n1, _FP_W_TYPE n0,&t;&t;&bslash;&n;&t;&t;&t;       _FP_W_TYPE d1, _FP_W_TYPE d0);&t;&t;&bslash;&n;    _FP_W_TYPE _n_f3, _n_f2, _n_f1, _n_f0, _r_f1, _r_f0;&t;&t;&bslash;&n;    _FP_W_TYPE _q_f1, _q_f0, _m_f1, _m_f0;&t;&t;&t;&t;&bslash;&n;    _FP_W_TYPE _rmem[2], _qmem[2];&t;&t;&t;&t;&t;&bslash;&n;    /* I think this check is to ensure that the result is normalised.   &bslash;&n;     * Assuming X,Y normalised (ie in [1.0,2.0)) X/Y will be in         &bslash;&n;     * [0.5,2.0). Furthermore, it will be less than 1.0 iff X &lt; Y.      &bslash;&n;     * In this case we tweak things. (this is based on comments in      &bslash;&n;     * the NetBSD FPU emulation code. )                                 &bslash;&n;     * We know X,Y are normalised because we ensure this as part of     &bslash;&n;     * the unpacking process. -- PMM                                    &bslash;&n;     */&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (_FP_FRAC_GT_2(X, Y))&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;/*&t;R##_e++; */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_n_f3 = X##_f1 &gt;&gt; 1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_n_f2 = X##_f1 &lt;&lt; (_FP_W_TYPE_SIZE - 1) | X##_f0 &gt;&gt; 1;&t;&t;&bslash;&n;&t;_n_f1 = X##_f0 &lt;&lt; (_FP_W_TYPE_SIZE - 1);&t;&t;&t;&bslash;&n;&t;_n_f0 = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;R##_e--;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_n_f3 = X##_f1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_n_f2 = X##_f0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_n_f1 = _n_f0 = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    /* Normalize, i.e. make the most significant bit of the &t;&t;&bslash;&n;       denominator set.  CHANGED: - 1 to nothing -- PMM */&t;&t;&bslash;&n;    _FP_FRAC_SLL_2(Y, _FP_WFRACXBITS_##fs /* -1 */);&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    /* Do the 256/128 bit division given the 128-bit _fp_udivmodtf4 &t;&bslash;&n;       primitive snagged from libgcc2.c.  */&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _fp_udivmodti4(_qmem, _rmem, _n_f3, _n_f2, 0, Y##_f1);&t;&t;&bslash;&n;    _q_f1 = _qmem[0];&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    umul_ppmm(_m_f1, _m_f0, _q_f1, Y##_f0);&t;&t;&t;&t;&bslash;&n;    _r_f1 = _rmem[0];&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _r_f0 = _n_f1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (_FP_FRAC_GT_2(_m, _r))&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_q_f1--;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_FP_FRAC_ADD_2(_r, _r, Y);&t;&t;&t;&t;&t;&bslash;&n;&t;if (_FP_FRAC_GE_2(_r, Y) &amp;&amp; _FP_FRAC_GT_2(_m, _r))&t;&t;&bslash;&n;&t;  {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    _q_f1--;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    _FP_FRAC_ADD_2(_r, _r, Y);&t;&t;&t;&t;&t;&bslash;&n;&t;  }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_FRAC_SUB_2(_r, _r, _m);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _fp_udivmodti4(_qmem, _rmem, _r_f1, _r_f0, 0, Y##_f1);&t;&t;&bslash;&n;    _q_f0 = _qmem[0];&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    umul_ppmm(_m_f1, _m_f0, _q_f0, Y##_f0);&t;&t;&t;&t;&bslash;&n;    _r_f1 = _rmem[0];&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _r_f0 = _n_f0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (_FP_FRAC_GT_2(_m, _r))&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_q_f0--;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_FP_FRAC_ADD_2(_r, _r, Y);&t;&t;&t;&t;&t;&bslash;&n;&t;if (_FP_FRAC_GE_2(_r, Y) &amp;&amp; _FP_FRAC_GT_2(_m, _r))&t;&t;&bslash;&n;&t;  {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    _q_f0--;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    _FP_FRAC_ADD_2(_r, _r, Y);&t;&t;&t;&t;&t;&bslash;&n;&t;  }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_FRAC_SUB_2(_r, _r, _m);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    R##_f1 = _q_f1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    R##_f0 = _q_f0 | ((_r_f1 | _r_f0) != 0);&t;&t;&t;&t;&bslash;&n;    /* adjust so answer is normalized again. I&squot;m not sure what the &t;&bslash;&n;     * final sz param should be. In practice it&squot;s never used since      &bslash;&n;     * N is 1 which is always going to be &lt; _FP_W_TYPE_SIZE...&t;&t;&bslash;&n;     */&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    /* _FP_FRAC_SRS_2(R,1,_FP_WFRACBITS_##fs);&t;*/&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|_FP_DIV_MEAT_2_gmp
mdefine_line|#define _FP_DIV_MEAT_2_gmp(fs, R, X, Y)&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_W_TYPE _x[4], _y[2], _z[4];&t;&t;&t;&t;&t;&bslash;&n;    _y[0] = Y##_f0; _y[1] = Y##_f1;&t;&t;&t;&t;&t;&bslash;&n;    _x[0] = _x[3] = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (_FP_FRAC_GT_2(X, Y))&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;R##_e++;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_x[1] = (X##_f0 &lt;&lt; (_FP_WFRACBITS-1 - _FP_W_TYPE_SIZE) |&t;&bslash;&n;&t;&t; X##_f1 &gt;&gt; (_FP_W_TYPE_SIZE -&t;&t;&t;&t;&bslash;&n;&t;&t;&t;    (_FP_WFRACBITS-1 - _FP_W_TYPE_SIZE)));&t;&bslash;&n;&t;_x[2] = X##_f1 &lt;&lt; (_FP_WFRACBITS-1 - _FP_W_TYPE_SIZE);&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_x[1] = (X##_f0 &lt;&lt; (_FP_WFRACBITS - _FP_W_TYPE_SIZE) |&t;&t;&bslash;&n;&t;&t; X##_f1 &gt;&gt; (_FP_W_TYPE_SIZE -&t;&t;&t;&t;&bslash;&n;&t;&t;&t;    (_FP_WFRACBITS - _FP_W_TYPE_SIZE)));&t;&bslash;&n;&t;_x[2] = X##_f1 &lt;&lt; (_FP_WFRACBITS - _FP_W_TYPE_SIZE);&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    (void) mpn_divrem (_z, 0, _x, 4, _y, 2);&t;&t;&t;&t;&bslash;&n;    R##_f1 = _z[1];&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    R##_f0 = _z[0] | ((_x[0] | _x[1]) != 0);&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/*&n; * Square root algorithms:&n; * We have just one right now, maybe Newton approximation&n; * should be added for those machines where division is fast.&n; */
DECL|macro|_FP_SQRT_MEAT_2
mdefine_line|#define _FP_SQRT_MEAT_2(R, S, T, X, q)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    while (q)&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        T##_f1 = S##_f1 + q;&t;&t;&t;&t;&bslash;&n;        if (T##_f1 &lt;= X##_f1)&t;&t;&t;&t;&bslash;&n;          {&t;&t;&t;&t;&t;&t;&bslash;&n;            S##_f1 = T##_f1 + q;&t;&t;&t;&bslash;&n;            X##_f1 -= T##_f1;&t;&t;&t;&t;&bslash;&n;            R##_f1 += q;&t;&t;&t;&t;&bslash;&n;          }&t;&t;&t;&t;&t;&t;&bslash;&n;        _FP_FRAC_SLL_2(X, 1);&t;&t;&t;&t;&bslash;&n;        q &gt;&gt;= 1;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    q = (_FP_W_TYPE)1 &lt;&lt; (_FP_W_TYPE_SIZE - 1);&t;&t;&bslash;&n;    while (q)&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        T##_f0 = S##_f0 + q;&t;&t;&t;&t;&bslash;&n;        T##_f1 = S##_f1;&t;&t;&t;&t;&bslash;&n;        if (T##_f1 &lt; X##_f1 || &t;&t;&t;&t;&bslash;&n;            (T##_f1 == X##_f1 &amp;&amp; T##_f0 &lt; X##_f0))&t;&bslash;&n;          {&t;&t;&t;&t;&t;&t;&bslash;&n;            S##_f0 = T##_f0 + q;&t;&t;&t;&bslash;&n;            if (((_FP_WS_TYPE)T##_f0) &lt; 0 &amp;&amp;&t;&t;&bslash;&n;                ((_FP_WS_TYPE)S##_f0) &gt;= 0)&t;&t;&bslash;&n;              S##_f1++;&t;&t;&t;&t;&t;&bslash;&n;            _FP_FRAC_SUB_2(X, X, T);&t;&t;&t;&bslash;&n;            R##_f0 += q;&t;&t;&t;&t;&bslash;&n;          }&t;&t;&t;&t;&t;&t;&bslash;&n;        _FP_FRAC_SLL_2(X, 1);&t;&t;&t;&t;&bslash;&n;        q &gt;&gt;= 1;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/*&n; * Assembly/disassembly for converting to/from integral types.  &n; * No shifting or overflow handled here.&n; */
DECL|macro|_FP_FRAC_ASSEMBLE_2
mdefine_line|#define _FP_FRAC_ASSEMBLE_2(r, X, rsize)&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&bslash;&n;    if (rsize &lt;= _FP_W_TYPE_SIZE)&t;&t;&bslash;&n;      r = X##_f0;&t;&t;&t;&t;&bslash;&n;    else&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;r = X##_f1;&t;&t;&t;&t;&bslash;&n;&t;r &lt;&lt;= _FP_W_TYPE_SIZE;&t;&t;&t;&bslash;&n;&t;r += X##_f0;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|_FP_FRAC_DISASSEMBLE_2
mdefine_line|#define _FP_FRAC_DISASSEMBLE_2(X, r, rsize)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    X##_f0 = r;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    X##_f1 = (rsize &lt;= _FP_W_TYPE_SIZE ? 0 : r &gt;&gt; _FP_W_TYPE_SIZE);&t;&bslash;&n;  } while (0)
multiline_comment|/*&n; * Convert FP values between word sizes&n; */
DECL|macro|_FP_FRAC_CONV_1_2
mdefine_line|#define _FP_FRAC_CONV_1_2(dfs, sfs, D, S)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_FRAC_SRS_2(S, (_FP_WFRACBITS_##sfs - _FP_WFRACBITS_##dfs),&t;&bslash;&n;&t;&t;   _FP_WFRACBITS_##sfs);&t;&t;&t;&t;&bslash;&n;    D##_f = S##_f0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|_FP_FRAC_CONV_2_1
mdefine_line|#define _FP_FRAC_CONV_2_1(dfs, sfs, D, S)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    D##_f0 = S##_f;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    D##_f1 = 0;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_FRAC_SLL_2(D, (_FP_WFRACBITS_##dfs - _FP_WFRACBITS_##sfs));&t;&bslash;&n;  } while (0)
eof
