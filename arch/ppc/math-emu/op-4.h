multiline_comment|/*&n; * Basic four-word fraction declaration and manipulation.&n; *&n; * When adding quadword support for 32 bit machines, we need&n; * to be a little careful as double multiply uses some of these&n; * macros: (in op-2.h)&n; * _FP_MUL_MEAT_2_wide() uses _FP_FRAC_DECL_4, _FP_FRAC_WORD_4,&n; * _FP_FRAC_ADD_4, _FP_FRAC_SRS_4&n; * _FP_MUL_MEAT_2_gmp() uses _FP_FRAC_SRS_4 (and should use&n; * _FP_FRAC_DECL_4: it appears to be broken and is not used&n; * anywhere anyway. )&n; *&n; * I&squot;ve now fixed all the macros that were here from the sparc64 code.&n; * [*none* of the shift macros were correct!] -- PMM 02/1998&n; *&n; * The only quadword stuff that remains to be coded is:&n; * 1) the conversion to/from ints, which requires&n; * that we check (in op-common.h) that the following do the right thing&n; * for quadwords: _FP_TO_INT(Q,4,r,X,rsz,rsg), _FP_FROM_INT(Q,4,X,r,rs,rt)&n; * 2) multiply, divide and sqrt, which require:&n; * _FP_MUL_MEAT_4_*(R,X,Y), _FP_DIV_MEAT_4_*(R,X,Y), _FP_SQRT_MEAT_4(R,S,T,X,q),&n; * This also needs _FP_MUL_MEAT_Q and _FP_DIV_MEAT_Q to be defined to&n; * some suitable _FP_MUL_MEAT_4_* macros in sfp-machine.h.&n; * [we&squot;re free to choose whatever FP_MUL_MEAT_4_* macros we need for&n; * these; they are used nowhere else. ]&n; */
DECL|macro|_FP_FRAC_DECL_4
mdefine_line|#define _FP_FRAC_DECL_4(X)&t;_FP_W_TYPE X##_f[4]
DECL|macro|_FP_FRAC_COPY_4
mdefine_line|#define _FP_FRAC_COPY_4(D,S)&t;&t;&t;&bslash;&n;  (D##_f[0] = S##_f[0], D##_f[1] = S##_f[1],&t;&bslash;&n;   D##_f[2] = S##_f[2], D##_f[3] = S##_f[3])
multiline_comment|/* The _FP_FRAC_SET_n(X,I) macro is intended for use with another&n; * macro such as _FP_ZEROFRAC_n which returns n comma separated values.&n; * The result is that we get an expansion of __FP_FRAC_SET_n(X,I0,I1,I2,I3)&n; * which just assigns the In values to the array X##_f[].&n; * This is why the number of parameters doesn&squot;t appear to match&n; * at first glance...      -- PMM&n; */
DECL|macro|_FP_FRAC_SET_4
mdefine_line|#define _FP_FRAC_SET_4(X,I)&t;__FP_FRAC_SET_4(X, I)
DECL|macro|_FP_FRAC_HIGH_4
mdefine_line|#define _FP_FRAC_HIGH_4(X)&t;(X##_f[3])
DECL|macro|_FP_FRAC_LOW_4
mdefine_line|#define _FP_FRAC_LOW_4(X)&t;(X##_f[0])
DECL|macro|_FP_FRAC_WORD_4
mdefine_line|#define _FP_FRAC_WORD_4(X,w)&t;(X##_f[w])
DECL|macro|_FP_FRAC_SLL_4
mdefine_line|#define _FP_FRAC_SLL_4(X,N)&t;&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_I_TYPE _up, _down, _skip, _i;&t;&t;&t;&t;&t;&bslash;&n;    _skip = (N) / _FP_W_TYPE_SIZE;&t;&t;&t;&t;&t;&bslash;&n;    _up = (N) % _FP_W_TYPE_SIZE;&t;&t;&t;&t;&t;&bslash;&n;    _down = _FP_W_TYPE_SIZE - _up;&t;&t;&t;&t;&t;&bslash;&n;    for (_i = 3; _i &gt; _skip; --_i)&t;&t;&t;&t;&t;&bslash;&n;      X##_f[_i] = X##_f[_i-_skip] &lt;&lt; _up | X##_f[_i-_skip-1] &gt;&gt; _down;&t;&bslash;&n;/* bugfixed: was X##_f[_i] &lt;&lt;= _up;  -- PMM 02/1998 */                  &bslash;&n;    X##_f[_i] = X##_f[0] &lt;&lt; _up; &t;                                &bslash;&n;    for (--_i; _i &gt;= 0; --_i)&t;&t;&t;&t;&t;&t;&bslash;&n;      X##_f[_i] = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/* This one was broken too */
DECL|macro|_FP_FRAC_SRL_4
mdefine_line|#define _FP_FRAC_SRL_4(X,N)&t;&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_I_TYPE _up, _down, _skip, _i;&t;&t;&t;&t;&t;&bslash;&n;    _skip = (N) / _FP_W_TYPE_SIZE;&t;&t;&t;&t;&t;&bslash;&n;    _down = (N) % _FP_W_TYPE_SIZE;&t;&t;&t;&t;&t;&bslash;&n;    _up = _FP_W_TYPE_SIZE - _down;&t;&t;&t;&t;&t;&bslash;&n;    for (_i = 0; _i &lt; 3-_skip; ++_i)&t;&t;&t;&t;&t;&bslash;&n;      X##_f[_i] = X##_f[_i+_skip] &gt;&gt; _down | X##_f[_i+_skip+1] &lt;&lt; _up;&t;&bslash;&n;    X##_f[_i] = X##_f[3] &gt;&gt; _down;&t;&t;&t;         &t;&bslash;&n;    for (++_i; _i &lt; 4; ++_i)&t;&t;&t;&t;&t;&t;&bslash;&n;      X##_f[_i] = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/* Right shift with sticky-lsb.&n; * What this actually means is that we do a standard right-shift,&n; * but that if any of the bits that fall off the right hand side&n; * were one then we always set the LSbit.&n; */
DECL|macro|_FP_FRAC_SRS_4
mdefine_line|#define _FP_FRAC_SRS_4(X,N,size)&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_I_TYPE _up, _down, _skip, _i;&t;&t;&t;&t;&t;&bslash;&n;    _FP_W_TYPE _s;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _skip = (N) / _FP_W_TYPE_SIZE;&t;&t;&t;&t;&t;&bslash;&n;    _down = (N) % _FP_W_TYPE_SIZE;&t;&t;&t;&t;&t;&bslash;&n;    _up = _FP_W_TYPE_SIZE - _down;&t;&t;&t;&t;&t;&bslash;&n;    for (_s = _i = 0; _i &lt; _skip; ++_i)&t;&t;&t;&t;&t;&bslash;&n;      _s |= X##_f[_i];&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _s |= X##_f[_i] &lt;&lt; _up;&t;&t;&t;&t;&t;&t;&bslash;&n;/* s is now != 0 if we want to set the LSbit */                         &bslash;&n;    for (_i = 0; _i &lt; 3-_skip; ++_i)&t;&t;&t;&t;&t;&bslash;&n;      X##_f[_i] = X##_f[_i+_skip] &gt;&gt; _down | X##_f[_i+_skip+1] &lt;&lt; _up;&t;&bslash;&n;    X##_f[_i] = X##_f[3] &gt;&gt; _down;&t;&t;&t;&t;&t;&bslash;&n;    for (++_i; _i &lt; 4; ++_i)&t;&t;&t;&t;&t;&t;&bslash;&n;      X##_f[_i] = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    /* don&squot;t fix the LSB until the very end when we&squot;re sure f[0] is stable */ &bslash;&n;    X##_f[0] |= (_s != 0);                                              &bslash;&n;  } while (0)
DECL|macro|_FP_FRAC_ADD_4
mdefine_line|#define _FP_FRAC_ADD_4(R,X,Y)&t;&t;&t;&t;&t;&t;&bslash;&n;  __FP_FRAC_ADD_4(R##_f[3], R##_f[2], R##_f[1], R##_f[0],&t;&t;&bslash;&n;&t;&t;  X##_f[3], X##_f[2], X##_f[1], X##_f[0],&t;&t;&bslash;&n;&t;&t;  Y##_f[3], Y##_f[2], Y##_f[1], Y##_f[0])
DECL|macro|_FP_FRAC_SUB_4
mdefine_line|#define _FP_FRAC_SUB_4(R,X,Y)                                           &bslash;&n;  __FP_FRAC_SUB_4(R##_f[3], R##_f[2], R##_f[1], R##_f[0],&t;&t;&bslash;&n;&t;&t;  X##_f[3], X##_f[2], X##_f[1], X##_f[0],&t;&t;&bslash;&n;&t;&t;  Y##_f[3], Y##_f[2], Y##_f[1], Y##_f[0])
DECL|macro|_FP_FRAC_ADDI_4
mdefine_line|#define _FP_FRAC_ADDI_4(X,I)                                            &bslash;&n;  __FP_FRAC_ADDI_4(X##_f[3], X##_f[2], X##_f[1], X##_f[0], I)
DECL|macro|_FP_ZEROFRAC_4
mdefine_line|#define _FP_ZEROFRAC_4  0,0,0,0
DECL|macro|_FP_MINFRAC_4
mdefine_line|#define _FP_MINFRAC_4   0,0,0,1
DECL|macro|_FP_FRAC_ZEROP_4
mdefine_line|#define _FP_FRAC_ZEROP_4(X)     ((X##_f[0] | X##_f[1] | X##_f[2] | X##_f[3]) == 0)
DECL|macro|_FP_FRAC_NEGP_4
mdefine_line|#define _FP_FRAC_NEGP_4(X)      ((_FP_WS_TYPE)X##_f[3] &lt; 0)
DECL|macro|_FP_FRAC_OVERP_4
mdefine_line|#define _FP_FRAC_OVERP_4(fs,X)  (X##_f[0] &amp; _FP_OVERFLOW_##fs)
DECL|macro|_FP_FRAC_EQ_4
mdefine_line|#define _FP_FRAC_EQ_4(X,Y)                              &bslash;&n; (X##_f[0] == Y##_f[0] &amp;&amp; X##_f[1] == Y##_f[1]          &bslash;&n;  &amp;&amp; X##_f[2] == Y##_f[2] &amp;&amp; X##_f[3] == Y##_f[3])
DECL|macro|_FP_FRAC_GT_4
mdefine_line|#define _FP_FRAC_GT_4(X,Y)                              &bslash;&n; (X##_f[3] &gt; Y##_f[3] ||                                &bslash;&n;  (X##_f[3] == Y##_f[3] &amp;&amp; (X##_f[2] &gt; Y##_f[2] ||      &bslash;&n;   (X##_f[2] == Y##_f[2] &amp;&amp; (X##_f[1] &gt; Y##_f[1] ||     &bslash;&n;    (X##_f[1] == Y##_f[1] &amp;&amp; X##_f[0] &gt; Y##_f[0])       &bslash;&n;   ))                                                   &bslash;&n;  ))                                                    &bslash;&n; )
DECL|macro|_FP_FRAC_GE_4
mdefine_line|#define _FP_FRAC_GE_4(X,Y)                              &bslash;&n; (X##_f[3] &gt; Y##_f[3] ||                                &bslash;&n;  (X##_f[3] == Y##_f[3] &amp;&amp; (X##_f[2] &gt; Y##_f[2] ||      &bslash;&n;   (X##_f[2] == Y##_f[2] &amp;&amp; (X##_f[1] &gt; Y##_f[1] ||     &bslash;&n;    (X##_f[1] == Y##_f[1] &amp;&amp; X##_f[0] &gt;= Y##_f[0])      &bslash;&n;   ))                                                   &bslash;&n;  ))                                                    &bslash;&n; )
DECL|macro|_FP_FRAC_CLZ_4
mdefine_line|#define _FP_FRAC_CLZ_4(R,X)             &bslash;&n;  do {                                  &bslash;&n;    if (X##_f[3])                       &bslash;&n;    {                                   &bslash;&n;        __FP_CLZ(R,X##_f[3]);           &bslash;&n;    }                                   &bslash;&n;    else if (X##_f[2])                  &bslash;&n;    {                                   &bslash;&n;        __FP_CLZ(R,X##_f[2]);           &bslash;&n;        R += _FP_W_TYPE_SIZE;           &bslash;&n;    }                                   &bslash;&n;    else if (X##_f[1])                  &bslash;&n;    {                                   &bslash;&n;        __FP_CLZ(R,X##_f[2]);           &bslash;&n;        R += _FP_W_TYPE_SIZE*2;         &bslash;&n;    }                                   &bslash;&n;    else                                &bslash;&n;    {                                   &bslash;&n;        __FP_CLZ(R,X##_f[0]);           &bslash;&n;        R += _FP_W_TYPE_SIZE*3;         &bslash;&n;    }                                   &bslash;&n;  } while(0)
DECL|macro|_FP_UNPACK_RAW_4
mdefine_line|#define _FP_UNPACK_RAW_4(fs, X, val)                            &bslash;&n;  do {                                                          &bslash;&n;    union _FP_UNION_##fs _flo; _flo.flt = (val);        &t;&bslash;&n;    X##_f[0] = _flo.bits.frac0;                                 &bslash;&n;    X##_f[1] = _flo.bits.frac1;                                 &bslash;&n;    X##_f[2] = _flo.bits.frac2;                                 &bslash;&n;    X##_f[3] = _flo.bits.frac3;                                 &bslash;&n;    X##_e  = _flo.bits.exp;                                     &bslash;&n;    X##_s  = _flo.bits.sign;                                    &bslash;&n;  } while (0)
DECL|macro|_FP_PACK_RAW_4
mdefine_line|#define _FP_PACK_RAW_4(fs, val, X)                              &bslash;&n;  do {                                                          &bslash;&n;    union _FP_UNION_##fs _flo;&t;&t;&t;&t;&t;&bslash;&n;    _flo.bits.frac0 = X##_f[0];                                 &bslash;&n;    _flo.bits.frac1 = X##_f[1];                                 &bslash;&n;    _flo.bits.frac2 = X##_f[2];                                 &bslash;&n;    _flo.bits.frac3 = X##_f[3];                                 &bslash;&n;    _flo.bits.exp   = X##_e;                                    &bslash;&n;    _flo.bits.sign  = X##_s;                                    &bslash;&n;    (val) = _flo.flt;                                   &t;&bslash;&n;  } while (0)
multiline_comment|/*&n; * Internals&n; */
DECL|macro|__FP_FRAC_SET_4
mdefine_line|#define __FP_FRAC_SET_4(X,I3,I2,I1,I0)&t;&t;&t;&t;&t;&bslash;&n;  (X##_f[3] = I3, X##_f[2] = I2, X##_f[1] = I1, X##_f[0] = I0)
macro_line|#ifndef __FP_FRAC_ADD_4
DECL|macro|__FP_FRAC_ADD_4
mdefine_line|#define __FP_FRAC_ADD_4(r3,r2,r1,r0,x3,x2,x1,x0,y3,y2,y1,y0)&t;&t;&bslash;&n;  (r0 = x0 + y0,&t;&t;&t;&t;&t;&t;&t;&bslash;&n;   r1 = x1 + y1 + (r0 &lt; x0),&t;&t;&t;&t;&t;&t;&bslash;&n;   r2 = x2 + y2 + (r1 &lt; x1),&t;&t;&t;&t;&t;&t;&bslash;&n;   r3 = x3 + y3 + (r2 &lt; x2))
macro_line|#endif
macro_line|#ifndef __FP_FRAC_SUB_4
DECL|macro|__FP_FRAC_SUB_4
mdefine_line|#define __FP_FRAC_SUB_4(r3,r2,r1,r0,x3,x2,x1,x0,y3,y2,y1,y0)&t;&t;&bslash;&n;  (r0 = x0 - y0,                                                        &bslash;&n;   r1 = x1 - y1 - (r0 &gt; x0),                                            &bslash;&n;   r2 = x2 - y2 - (r1 &gt; x1),                                            &bslash;&n;   r3 = x3 - y3 - (r2 &gt; x2))
macro_line|#endif
macro_line|#ifndef __FP_FRAC_ADDI_4
multiline_comment|/* I always wanted to be a lisp programmer :-&gt; */
DECL|macro|__FP_FRAC_ADDI_4
mdefine_line|#define __FP_FRAC_ADDI_4(x3,x2,x1,x0,i)                                 &bslash;&n;  (x3 += ((x2 += ((x1 += ((x0 += i) &lt; x0)) &lt; x1) &lt; x2)))
macro_line|#endif
multiline_comment|/* Convert FP values between word sizes. This appears to be more&n; * complicated than I&squot;d have expected it to be, so these might be&n; * wrong... These macros are in any case somewhat bogus because they&n; * use information about what various FRAC_n variables look like&n; * internally [eg, that 2 word vars are X_f0 and x_f1]. But so do&n; * the ones in op-2.h and op-1.h.&n; */
DECL|macro|_FP_FRAC_CONV_1_4
mdefine_line|#define _FP_FRAC_CONV_1_4(dfs, sfs, D, S)                               &bslash;&n;   do {                                                                 &bslash;&n;     _FP_FRAC_SRS_4(S, (_FP_WFRACBITS_##sfs - _FP_WFRACBITS_##dfs),     &bslash;&n;                        _FP_WFRACBITS_##sfs);                           &bslash;&n;     D##_f = S##_f[0];                                                   &bslash;&n;  } while (0)
DECL|macro|_FP_FRAC_CONV_2_4
mdefine_line|#define _FP_FRAC_CONV_2_4(dfs, sfs, D, S)                               &bslash;&n;   do {                                                                 &bslash;&n;     _FP_FRAC_SRS_4(S, (_FP_WFRACBITS_##sfs - _FP_WFRACBITS_##dfs),     &bslash;&n;                        _FP_WFRACBITS_##sfs);                           &bslash;&n;     D##_f0 = S##_f[0];                                                  &bslash;&n;     D##_f1 = S##_f[1];                                                  &bslash;&n;  } while (0)
multiline_comment|/* Assembly/disassembly for converting to/from integral types.&n; * No shifting or overflow handled here.&n; */
multiline_comment|/* Put the FP value X into r, which is an integer of size rsize. */
DECL|macro|_FP_FRAC_ASSEMBLE_4
mdefine_line|#define _FP_FRAC_ASSEMBLE_4(r, X, rsize)                                &bslash;&n;  do {                                                                  &bslash;&n;    if (rsize &lt;= _FP_W_TYPE_SIZE)                                       &bslash;&n;      r = X##_f[0];                                                     &bslash;&n;    else if (rsize &lt;= 2*_FP_W_TYPE_SIZE)                                &bslash;&n;    {                                                                   &bslash;&n;      r = X##_f[1];                                                     &bslash;&n;      r &lt;&lt;= _FP_W_TYPE_SIZE;                                            &bslash;&n;      r += X##_f[0];                                                    &bslash;&n;    }                                                                   &bslash;&n;    else                                                                &bslash;&n;    {                                                                   &bslash;&n;      /* I&squot;m feeling lazy so we deal with int == 3words (implausible)*/ &bslash;&n;      /* and int == 4words as a single case.                         */ &bslash;&n;      r = X##_f[3];                                                     &bslash;&n;      r &lt;&lt;= _FP_W_TYPE_SIZE;                                            &bslash;&n;      r += X##_f[2];                                                    &bslash;&n;      r &lt;&lt;= _FP_W_TYPE_SIZE;                                            &bslash;&n;      r += X##_f[1];                                                    &bslash;&n;      r &lt;&lt;= _FP_W_TYPE_SIZE;                                            &bslash;&n;      r += X##_f[0];                                                    &bslash;&n;    }                                                                   &bslash;&n;  } while (0)
multiline_comment|/* &quot;No disassemble Number Five!&quot; */
multiline_comment|/* move an integer of size rsize into X&squot;s fractional part. We rely on&n; * the _f[] array consisting of words of size _FP_W_TYPE_SIZE to avoid&n; * having to mask the values we store into it.&n; */
DECL|macro|_FP_FRAC_DISASSEMBLE_4
mdefine_line|#define _FP_FRAC_DISASSEMBLE_4(X, r, rsize)                             &bslash;&n;  do {                                                                  &bslash;&n;    X##_f[0] = r;                                                       &bslash;&n;    X##_f[1] = (rsize &lt;= _FP_W_TYPE_SIZE ? 0 : r &gt;&gt; _FP_W_TYPE_SIZE);   &bslash;&n;    X##_f[2] = (rsize &lt;= 2*_FP_W_TYPE_SIZE ? 0 : r &gt;&gt; 2*_FP_W_TYPE_SIZE); &bslash;&n;    X##_f[3] = (rsize &lt;= 3*_FP_W_TYPE_SIZE ? 0 : r &gt;&gt; 3*_FP_W_TYPE_SIZE); &bslash;&n;  } while (0)
DECL|macro|_FP_FRAC_CONV_4_1
mdefine_line|#define _FP_FRAC_CONV_4_1(dfs, sfs, D, S)                               &bslash;&n;   do {                                                                 &bslash;&n;     D##_f[0] = S##_f;                                                  &bslash;&n;     D##_f[1] = D##_f[2] = D##_f[3] = 0;                                &bslash;&n;     _FP_FRAC_SLL_4(D, (_FP_WFRACBITS_##dfs - _FP_WFRACBITS_##sfs));    &bslash;&n;   } while (0)
DECL|macro|_FP_FRAC_CONV_4_2
mdefine_line|#define _FP_FRAC_CONV_4_2(dfs, sfs, D, S)                               &bslash;&n;   do {                                                                 &bslash;&n;     D##_f[0] = S##_f0;                                                 &bslash;&n;     D##_f[1] = S##_f1;                                                 &bslash;&n;     D##_f[2] = D##_f[3] = 0;                                           &bslash;&n;     _FP_FRAC_SLL_4(D, (_FP_WFRACBITS_##dfs - _FP_WFRACBITS_##sfs));    &bslash;&n;   } while (0)
multiline_comment|/* FIXME! This has to be written */
DECL|macro|_FP_SQRT_MEAT_4
mdefine_line|#define _FP_SQRT_MEAT_4(R, S, T, X, q)
eof
