DECL|macro|_FP_W_TYPE_SIZE
mdefine_line|#define _FP_W_TYPE_SIZE&t;&t;32
DECL|macro|_FP_W_TYPE
mdefine_line|#define _FP_W_TYPE&t;&t;unsigned long
DECL|macro|_FP_WS_TYPE
mdefine_line|#define _FP_WS_TYPE&t;&t;signed long
DECL|macro|_FP_I_TYPE
mdefine_line|#define _FP_I_TYPE&t;&t;long
DECL|macro|_FP_MUL_MEAT_S
mdefine_line|#define _FP_MUL_MEAT_S(R,X,Y)&t;&t;&t;&t;&bslash;&n;  _FP_MUL_MEAT_1_wide(_FP_WFRACBITS_S,R,X,Y,umul_ppmm)
DECL|macro|_FP_MUL_MEAT_D
mdefine_line|#define _FP_MUL_MEAT_D(R,X,Y)&t;&t;&t;&t;&bslash;&n;  _FP_MUL_MEAT_2_wide(_FP_WFRACBITS_D,R,X,Y,umul_ppmm)
DECL|macro|_FP_MUL_MEAT_Q
mdefine_line|#define _FP_MUL_MEAT_Q(R,X,Y)&t;&t;&t;&t;&bslash;&n;  _FP_MUL_MEAT_4_wide(_FP_WFRACBITS_Q,R,X,Y,umul_ppmm)
DECL|macro|_FP_DIV_MEAT_S
mdefine_line|#define _FP_DIV_MEAT_S(R,X,Y)&t;_FP_DIV_MEAT_1_udiv_norm(S,R,X,Y)
DECL|macro|_FP_DIV_MEAT_D
mdefine_line|#define _FP_DIV_MEAT_D(R,X,Y)&t;_FP_DIV_MEAT_2_udiv(D,R,X,Y)
DECL|macro|_FP_DIV_MEAT_Q
mdefine_line|#define _FP_DIV_MEAT_Q(R,X,Y)&t;_FP_DIV_MEAT_4_udiv(Q,R,X,Y)
DECL|macro|_FP_NANFRAC_S
mdefine_line|#define _FP_NANFRAC_S&t;&t;((_FP_QNANBIT_S &lt;&lt; 1) - 1)
DECL|macro|_FP_NANFRAC_D
mdefine_line|#define _FP_NANFRAC_D&t;&t;((_FP_QNANBIT_D &lt;&lt; 1) - 1), -1
DECL|macro|_FP_NANFRAC_Q
mdefine_line|#define _FP_NANFRAC_Q&t;&t;((_FP_QNANBIT_Q &lt;&lt; 1) - 1), -1, -1, -1
DECL|macro|_FP_NANSIGN_S
mdefine_line|#define _FP_NANSIGN_S&t;&t;0
DECL|macro|_FP_NANSIGN_D
mdefine_line|#define _FP_NANSIGN_D&t;&t;0
DECL|macro|_FP_NANSIGN_Q
mdefine_line|#define _FP_NANSIGN_Q&t;&t;0
DECL|macro|_FP_KEEPNANFRACP
mdefine_line|#define _FP_KEEPNANFRACP 1
multiline_comment|/* From my experiments it seems X is chosen unless one of the&n;   NaNs is sNaN,  in which case the result is NANSIGN/NANFRAC.  */
DECL|macro|_FP_CHOOSENAN
mdefine_line|#define _FP_CHOOSENAN(fs, wc, R, X, Y, OP)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if ((_FP_FRAC_HIGH_RAW_##fs(X) |&t;&t;&t;&t;&bslash;&n;&t; _FP_FRAC_HIGH_RAW_##fs(Y)) &amp; _FP_QNANBIT_##fs)&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;R##_s = _FP_NANSIGN_##fs;&t;&t;&t;&t;&bslash;&n;        _FP_FRAC_SET_##wc(R,_FP_NANFRAC_##fs);&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;R##_s = X##_s;&t;&t;&t;&t;&t;&t;&bslash;&n;        _FP_FRAC_COPY_##wc(R,X);&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    R##_c = FP_CLS_NAN;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_EX_INVALID
mdefine_line|#define FP_EX_INVALID           (1 &lt;&lt; 4)
DECL|macro|FP_EX_DIVZERO
mdefine_line|#define FP_EX_DIVZERO           (1 &lt;&lt; 3)
DECL|macro|FP_EX_OVERFLOW
mdefine_line|#define FP_EX_OVERFLOW          (1 &lt;&lt; 2)
DECL|macro|FP_EX_UNDERFLOW
mdefine_line|#define FP_EX_UNDERFLOW         (1 &lt;&lt; 1)
DECL|macro|FP_EX_INEXACT
mdefine_line|#define FP_EX_INEXACT           (1 &lt;&lt; 0)
eof
