multiline_comment|/*&n; * Linux/PA-RISC Project (http://www.parisc-linux.org/)&n; *&n; * Floating-point emulation code&n; *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) &lt;bame@debian.org&gt;&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifdef __NO_PA_HDRS
id|PA
id|header
id|file
op_decrement
r_do
op_logical_neg
id|include
id|this
id|header
id|file
r_for
c_loop
id|non
op_minus
id|PA
id|builds
dot
macro_line|#endif
multiline_comment|/*&n; * Some more constants&n; */
DECL|macro|SGL_FX_MAX_EXP
mdefine_line|#define SGL_FX_MAX_EXP 30
DECL|macro|DBL_FX_MAX_EXP
mdefine_line|#define DBL_FX_MAX_EXP 62
DECL|macro|QUAD_FX_MAX_EXP
mdefine_line|#define QUAD_FX_MAX_EXP 126
DECL|macro|Dintp1
mdefine_line|#define Dintp1(object) (object)
DECL|macro|Dintp2
mdefine_line|#define Dintp2(object) (object)
DECL|macro|Duintp1
mdefine_line|#define Duintp1(object) (object)
DECL|macro|Duintp2
mdefine_line|#define Duintp2(object) (object)
DECL|macro|Qintp0
mdefine_line|#define Qintp0(object) (object)
DECL|macro|Qintp1
mdefine_line|#define Qintp1(object) (object)
DECL|macro|Qintp2
mdefine_line|#define Qintp2(object) (object)
DECL|macro|Qintp3
mdefine_line|#define Qintp3(object) (object)
multiline_comment|/*&n; * These macros will be used specifically by the convert instructions.&n; *&n; *&n; * Single format macros&n; */
DECL|macro|Sgl_to_dbl_exponent
mdefine_line|#define Sgl_to_dbl_exponent(src_exponent,dest)&t;&t;&t;&bslash;&n;    Deposit_dexponent(dest,src_exponent+(DBL_BIAS-SGL_BIAS))
DECL|macro|Sgl_to_dbl_mantissa
mdefine_line|#define Sgl_to_dbl_mantissa(src_mantissa,destA,destB)&t;&bslash;&n;    Deposit_dmantissap1(destA,src_mantissa&gt;&gt;3);&t;&t;&bslash;&n;    Dmantissap2(destB) = src_mantissa &lt;&lt; 29
DECL|macro|Sgl_isinexact_to_fix
mdefine_line|#define Sgl_isinexact_to_fix(sgl_value,exponent)&t;&bslash;&n;    ((exponent &lt; (SGL_P - 1)) ?&t;&t;&t;&t;&bslash;&n;     (Sall(sgl_value) &lt;&lt; (SGL_EXP_LENGTH + 1 + exponent)) : FALSE)
DECL|macro|Int_isinexact_to_sgl
mdefine_line|#define Int_isinexact_to_sgl(int_value)&t;(int_value &lt;&lt; 33 - SGL_EXP_LENGTH)
DECL|macro|Sgl_roundnearest_from_int
mdefine_line|#define Sgl_roundnearest_from_int(int_value,sgl_value)&t;&t;&t;&bslash;&n;    if (int_value &amp; 1&lt;&lt;(SGL_EXP_LENGTH - 2))   /* round bit */&t;&t;&bslash;&n;    &t;if ((int_value &lt;&lt; 34 - SGL_EXP_LENGTH) || Slow(sgl_value))&t;&bslash;&n;&t;&t;Sall(sgl_value)++
DECL|macro|Dint_isinexact_to_sgl
mdefine_line|#define Dint_isinexact_to_sgl(dint_valueA,dint_valueB)&t;&t;&bslash;&n;    ((Dintp1(dint_valueA) &lt;&lt; 33 - SGL_EXP_LENGTH) || Dintp2(dint_valueB))
DECL|macro|Sgl_roundnearest_from_dint
mdefine_line|#define Sgl_roundnearest_from_dint(dint_valueA,dint_valueB,sgl_value)&t;&bslash;&n;    if (Dintp1(dint_valueA) &amp; 1&lt;&lt;(SGL_EXP_LENGTH - 2)) &t;&t;&t;&bslash;&n;    &t;if ((Dintp1(dint_valueA) &lt;&lt; 34 - SGL_EXP_LENGTH) ||&t;&t;&bslash;&n;    &t;Dintp2(dint_valueB) || Slow(sgl_value)) Sall(sgl_value)++
DECL|macro|Dint_isinexact_to_dbl
mdefine_line|#define Dint_isinexact_to_dbl(dint_value) &t;&bslash;&n;    (Dintp2(dint_value) &lt;&lt; 33 - DBL_EXP_LENGTH)
DECL|macro|Dbl_roundnearest_from_dint
mdefine_line|#define Dbl_roundnearest_from_dint(dint_opndB,dbl_opndA,dbl_opndB) &t;&bslash;&n;    if (Dintp2(dint_opndB) &amp; 1&lt;&lt;(DBL_EXP_LENGTH - 2))&t;&t;&t;&bslash;&n;       if ((Dintp2(dint_opndB) &lt;&lt; 34 - DBL_EXP_LENGTH) || Dlowp2(dbl_opndB))  &bslash;&n;          if ((++Dallp2(dbl_opndB))==0) Dallp1(dbl_opndA)++
DECL|macro|Sgl_isone_roundbit
mdefine_line|#define Sgl_isone_roundbit(sgl_value,exponent)&t;&t;&t;&bslash;&n;    ((Sall(sgl_value) &lt;&lt; (SGL_EXP_LENGTH + 1 + exponent)) &gt;&gt; 31)
DECL|macro|Sgl_isone_stickybit
mdefine_line|#define Sgl_isone_stickybit(sgl_value,exponent)&t;&t;&bslash;&n;    (exponent &lt; (SGL_P - 2) ?&t;&t;&t;&t;&bslash;&n;     Sall(sgl_value) &lt;&lt; (SGL_EXP_LENGTH + 2 + exponent) : FALSE)
multiline_comment|/* &n; * Double format macros&n; */
DECL|macro|Dbl_to_sgl_exponent
mdefine_line|#define Dbl_to_sgl_exponent(src_exponent,dest)&t;&t;&t;&bslash;&n;    dest = src_exponent + (SGL_BIAS - DBL_BIAS)
DECL|macro|Dbl_to_sgl_mantissa
mdefine_line|#define Dbl_to_sgl_mantissa(srcA,srcB,dest,inexact,guard,sticky,odd)&t;&bslash;&n;    Shiftdouble(Dmantissap1(srcA),Dmantissap2(srcB),29,dest); &t;&bslash;&n;    guard = Dbit3p2(srcB);&t;&t;&t;&t;&t;&bslash;&n;    sticky = Dallp2(srcB)&lt;&lt;4;&t;&t;&t;&t;&t;&bslash;&n;    inexact = guard | sticky;&t;&t;&t;&t;&t;&bslash;&n;    odd = Dbit2p2(srcB)
DECL|macro|Dbl_to_sgl_denormalized
mdefine_line|#define Dbl_to_sgl_denormalized(srcA,srcB,exp,dest,inexact,guard,sticky,odd,tiny) &bslash;&n;    Deposit_dexponent(srcA,1);&t;&t;&t;&t;&t;&t;&bslash;&n;    tiny = TRUE;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (exp &gt;= -2) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (exp == 0) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    inexact = Dallp2(srcB) &lt;&lt; 3;&t;&t;&t;&t;&bslash;&n;&t;    guard = inexact &gt;&gt; 31;&t;&t;&t;&t;&t;&bslash;&n;&t;    sticky = inexact &lt;&lt; 1;&t;&t;&t;&t;&t;&bslash;&n;&t;    Shiftdouble(Dmantissap1(srcA),Dmantissap2(srcB),29,dest);&t;&bslash;&n;&t;    odd = dest &lt;&lt; 31;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    if (inexact) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;switch(Rounding_mode()) {&t;&t;&t;&t;&bslash;&n;&t;&t;    case ROUNDPLUS:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (Dbl_iszero_sign(srcA)) {&t;&t;&t;&bslash;&n;&t;&t;&t;    dest++;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;    if (Sgl_isone_hidden(dest))&t;&bslash;&n;&t;&t;&t;&t;tiny = FALSE;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;    dest--;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;    case ROUNDMINUS:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (Dbl_isone_sign(srcA)) {&t;&t;&t;&bslash;&n;&t;&t;&t;    dest++;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;    if (Sgl_isone_hidden(dest))&t;&bslash;&n;&t;&t;&t;&t;tiny = FALSE;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;    dest--;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;    case ROUNDNEAREST:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (guard &amp;&amp; (sticky || odd)) {&t;&t;&t;&bslash;&n;&t;&t;&t;    dest++;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;    if (Sgl_isone_hidden(dest))&t;&bslash;&n;&t;&t;&t;&t;tiny = FALSE;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;    dest--;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;/* shift right by one to get correct result */&t;&t;&bslash;&n;&t;&t;guard = odd;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;sticky = inexact;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;inexact |= guard;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;dest &gt;&gt;= 1;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;&t;Deposit_dsign(srcA,0);&t;&t;&t;&t;&t;&bslash;&n;    &t;        Shiftdouble(Dallp1(srcA),Dallp2(srcB),30,dest);&t;&t;&bslash;&n;&t;        odd = dest &lt;&lt; 31;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;    inexact = Dallp2(srcB) &lt;&lt; (2 + exp);&t;&t;&t;&bslash;&n;    &t;    guard = inexact &gt;&gt; 31;&t;&t;&t;&t;&t;&bslash;&n;    &t;    sticky = inexact &lt;&lt; 1; &t;&t;&t;&t;&t;&bslash;&n;    &t;    Deposit_dsign(srcA,0);&t;&t;&t;&t;&t;&bslash;&n;    &t;    if (exp == -2) dest = Dallp1(srcA);&t;&t;&t;&t;&bslash;&n;    &t;    else Variable_shift_double(Dallp1(srcA),Dallp2(srcB),30-exp,dest); &bslash;&n;    &t;    odd = dest &lt;&lt; 31;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;Deposit_dsign(srcA,0);&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;if (exp &gt; (1 - SGL_P)) {&t;&t;&t;&t;&t;&bslash;&n;    &t;    dest = Dallp1(srcA) &gt;&gt; (- 2 - exp);&t;&t;&t;&t;&bslash;&n;    &t;    inexact = Dallp1(srcA) &lt;&lt; (34 + exp);&t;&t;&t;&bslash;&n;    &t;    guard = inexact &gt;&gt; 31;&t;&t;&t;&t;&t;&bslash;&n;    &t;    sticky = (inexact &lt;&lt; 1) | Dallp2(srcB);&t;&t;&t;&bslash;&n;    &t;    inexact |= Dallp2(srcB); &t;&t;&t;&t;&t;&bslash;&n;    &t;    odd = dest &lt;&lt; 31;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;    dest = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;    inexact = Dallp1(srcA) | Dallp2(srcB);&t;&t;&t;&bslash;&n;    &t;    if (exp == (1 - SGL_P)) {&t;&t;&t;&t;&t;&bslash;&n;    &t;    &t;guard = Dhidden(srcA);&t;&t;&t;&t;&t;&bslash;&n;    &t;    &t;sticky = Dmantissap1(srcA) | Dallp2(srcB); &t;&t;&bslash;&n;    &t;    }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;    else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;    &t;guard = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;    &t;sticky = inexact;&t;&t;&t;&t;&t;&bslash;&n;    &t;    }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;    odd = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    exp = 0
DECL|macro|Dbl_isinexact_to_fix
mdefine_line|#define Dbl_isinexact_to_fix(dbl_valueA,dbl_valueB,exponent)&t;&t;&bslash;&n;    (exponent &lt; (DBL_P-33) ? &t;&t;&t;&t;&t;&t;&bslash;&n;     Dallp2(dbl_valueB) || Dallp1(dbl_valueA) &lt;&lt; (DBL_EXP_LENGTH+1+exponent) : &bslash;&n;     (exponent &lt; (DBL_P-1) ? Dallp2(dbl_valueB) &lt;&lt; (exponent + (33-DBL_P)) :   &bslash;&n;      FALSE))
DECL|macro|Dbl_isoverflow_to_int
mdefine_line|#define Dbl_isoverflow_to_int(exponent,dbl_valueA,dbl_valueB)&t;&t;&bslash;&n;    ((exponent &gt; SGL_FX_MAX_EXP + 1) || Dsign(dbl_valueA)==0 ||&t;&t;&bslash;&n;     Dmantissap1(dbl_valueA)!=0 || (Dallp2(dbl_valueB)&gt;&gt;21)!=0 ) 
DECL|macro|Dbl_isone_roundbit
mdefine_line|#define Dbl_isone_roundbit(dbl_valueA,dbl_valueB,exponent)              &bslash;&n;    ((exponent &lt; (DBL_P - 33) ?&t;&t;&t;&t;&t;&t;&bslash;&n;      Dallp1(dbl_valueA) &gt;&gt; ((30 - DBL_EXP_LENGTH) - exponent) :&t;&bslash;&n;      Dallp2(dbl_valueB) &gt;&gt; ((DBL_P - 2) - exponent)) &amp; 1)
DECL|macro|Dbl_isone_stickybit
mdefine_line|#define Dbl_isone_stickybit(dbl_valueA,dbl_valueB,exponent)&t;&t;&bslash;&n;    (exponent &lt; (DBL_P-34) ? &t;&t;&t;&t;&t;&t;&bslash;&n;     (Dallp2(dbl_valueB) || Dallp1(dbl_valueA)&lt;&lt;(DBL_EXP_LENGTH+2+exponent)) : &bslash;&n;     (exponent&lt;(DBL_P-2) ? (Dallp2(dbl_valueB) &lt;&lt; (exponent + (34-DBL_P))) : &bslash;&n;      FALSE))
multiline_comment|/* Int macros */
DECL|macro|Int_from_sgl_mantissa
mdefine_line|#define Int_from_sgl_mantissa(sgl_value,exponent)&t;&bslash;&n;    Sall(sgl_value) = &t;&t;&t;&t;&bslash;&n;    &t;(unsigned)(Sall(sgl_value) &lt;&lt; SGL_EXP_LENGTH)&gt;&gt;(31 - exponent)
DECL|macro|Int_from_dbl_mantissa
mdefine_line|#define Int_from_dbl_mantissa(dbl_valueA,dbl_valueB,exponent)&t;&bslash;&n;    Shiftdouble(Dallp1(dbl_valueA),Dallp2(dbl_valueB),22,Dallp1(dbl_valueA)); &bslash;&n;    if (exponent &lt; 31) Dallp1(dbl_valueA) &gt;&gt;= 30 - exponent;&t;&bslash;&n;    else Dallp1(dbl_valueA) &lt;&lt;= 1
DECL|macro|Int_negate
mdefine_line|#define Int_negate(int_value) int_value = -int_value
multiline_comment|/* Dint macros */
DECL|macro|Dint_from_sgl_mantissa
mdefine_line|#define Dint_from_sgl_mantissa(sgl_value,exponent,dresultA,dresultB)&t;&bslash;&n;    {Sall(sgl_value) &lt;&lt;= SGL_EXP_LENGTH;  /*  left-justify  */&t;&t;&bslash;&n;    if (exponent &lt;= 31) {&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;Dintp1(dresultA) = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;Dintp2(dresultB) = (unsigned)Sall(sgl_value) &gt;&gt; (31 - exponent); &bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;Dintp1(dresultA) = Sall(sgl_value) &gt;&gt; (63 - exponent);&t;&t;&bslash;&n;    &t;Dintp2(dresultB) = Sall(sgl_value) &lt;&lt; (exponent - 31);&t;&t;&bslash;&n;    }}
DECL|macro|Dint_from_dbl_mantissa
mdefine_line|#define Dint_from_dbl_mantissa(dbl_valueA,dbl_valueB,exponent,destA,destB) &bslash;&n;    {if (exponent &lt; 32) {&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;Dintp1(destA) = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;if (exponent &lt;= 20)&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;    Dintp2(destB) = Dallp1(dbl_valueA) &gt;&gt; 20-exponent;&t;&t;&bslash;&n;    &t;else Variable_shift_double(Dallp1(dbl_valueA),Dallp2(dbl_valueB), &bslash;&n;&t;     52-exponent,Dintp2(destB));&t;&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;if (exponent &lt;= 52) {&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;    Dintp1(destA) = Dallp1(dbl_valueA) &gt;&gt; 52-exponent;&t;&t;&bslash;&n;&t;    if (exponent == 52) Dintp2(destB) = Dallp2(dbl_valueB);&t;&bslash;&n;&t;    else Variable_shift_double(Dallp1(dbl_valueA),Dallp2(dbl_valueB), &bslash;&n;&t;    52-exponent,Dintp2(destB));&t;&t;&t;&t;&t;&bslash;&n;        }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;    Variable_shift_double(Dallp1(dbl_valueA),Dallp2(dbl_valueB), &bslash;&n;&t;    84-exponent,Dintp1(destA));&t;&t;&t;&t;&t;&bslash;&n;    &t;    Dintp2(destB) = Dallp2(dbl_valueB) &lt;&lt; exponent-52;&t;&t;&bslash;&n;    &t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    }}
DECL|macro|Dint_setzero
mdefine_line|#define Dint_setzero(dresultA,dresultB) &t;&bslash;&n;    Dintp1(dresultA) = 0; &t;&bslash;&n;    Dintp2(dresultB) = 0
DECL|macro|Dint_setone_sign
mdefine_line|#define Dint_setone_sign(dresultA,dresultB)&t;&t;&bslash;&n;    Dintp1(dresultA) = ~Dintp1(dresultA);&t;&t;&bslash;&n;    if ((Dintp2(dresultB) = -Dintp2(dresultB)) == 0) Dintp1(dresultA)++
DECL|macro|Dint_set_minint
mdefine_line|#define Dint_set_minint(dresultA,dresultB)&t;&t;&bslash;&n;    Dintp1(dresultA) = (unsigned int)1&lt;&lt;31;&t;&t;&bslash;&n;    Dintp2(dresultB) = 0
DECL|macro|Dint_isone_lowp2
mdefine_line|#define Dint_isone_lowp2(dresultB)  (Dintp2(dresultB) &amp; 01)
DECL|macro|Dint_increment
mdefine_line|#define Dint_increment(dresultA,dresultB) &t;&t;&bslash;&n;    if ((++Dintp2(dresultB))==0) Dintp1(dresultA)++
DECL|macro|Dint_decrement
mdefine_line|#define Dint_decrement(dresultA,dresultB) &t;&t;&bslash;&n;    if ((Dintp2(dresultB)--)==0) Dintp1(dresultA)--
DECL|macro|Dint_negate
mdefine_line|#define Dint_negate(dresultA,dresultB)&t;&t;&t;&bslash;&n;    Dintp1(dresultA) = ~Dintp1(dresultA);&t;&t;&bslash;&n;    if ((Dintp2(dresultB) = -Dintp2(dresultB))==0) Dintp1(dresultA)++
DECL|macro|Dint_copyfromptr
mdefine_line|#define Dint_copyfromptr(src,destA,destB) &bslash;&n;     Dintp1(destA) = src-&gt;wd0;&t;&t;&bslash;&n;     Dintp2(destB) = src-&gt;wd1
DECL|macro|Dint_copytoptr
mdefine_line|#define Dint_copytoptr(srcA,srcB,dest)&t;&bslash;&n;    dest-&gt;wd0 = Dintp1(srcA);&t;&t;&bslash;&n;    dest-&gt;wd1 = Dintp2(srcB)
multiline_comment|/* other macros  */
DECL|macro|Find_ms_one_bit
mdefine_line|#define Find_ms_one_bit(value, position)&t;&bslash;&n;    {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int var;&t;&t;&t;&t;&bslash;&n;&t;for (var=8; var &gt;=1; var &gt;&gt;= 1) {&t;&bslash;&n;&t;    if (value &gt;&gt; 32 - position)&t;&t;&bslash;&n;&t;&t;position -= var;&t;&t;&bslash;&n;&t;&t;else position += var;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&bslash;&n;&t;if ((value &gt;&gt; 32 - position) == 0)&t;&bslash;&n;&t;    position--;&t;&t;&t;&t;&bslash;&n;&t;else position -= 2;&t;&t;&t;&bslash;&n;    }
multiline_comment|/*&n; * Unsigned int macros&n; */
DECL|macro|Duint_copyfromptr
mdefine_line|#define Duint_copyfromptr(src,destA,destB) &bslash;&n;    Dint_copyfromptr(src,destA,destB)
DECL|macro|Duint_copytoptr
mdefine_line|#define Duint_copytoptr(srcA,srcB,dest)&t;&bslash;&n;    Dint_copytoptr(srcA,srcB,dest)
DECL|macro|Suint_isinexact_to_sgl
mdefine_line|#define Suint_isinexact_to_sgl(int_value) &bslash;&n;    (int_value &lt;&lt; 32 - SGL_EXP_LENGTH)
DECL|macro|Sgl_roundnearest_from_suint
mdefine_line|#define Sgl_roundnearest_from_suint(suint_value,sgl_value)&t;&t;&bslash;&n;    if (suint_value &amp; 1&lt;&lt;(SGL_EXP_LENGTH - 1))   /* round bit */&t;&bslash;&n;    &t;if ((suint_value &lt;&lt; 33 - SGL_EXP_LENGTH) || Slow(sgl_value))&t;&bslash;&n;&t;&t;Sall(sgl_value)++
DECL|macro|Duint_isinexact_to_sgl
mdefine_line|#define Duint_isinexact_to_sgl(duint_valueA,duint_valueB)&t;&bslash;&n;    ((Duintp1(duint_valueA) &lt;&lt; 32 - SGL_EXP_LENGTH) || Duintp2(duint_valueB))
DECL|macro|Sgl_roundnearest_from_duint
mdefine_line|#define Sgl_roundnearest_from_duint(duint_valueA,duint_valueB,sgl_value) &bslash;&n;    if (Duintp1(duint_valueA) &amp; 1&lt;&lt;(SGL_EXP_LENGTH - 1))&t;&t;&bslash;&n;    &t;if ((Duintp1(duint_valueA) &lt;&lt; 33 - SGL_EXP_LENGTH) ||&t;&t;&bslash;&n;    &t;Duintp2(duint_valueB) || Slow(sgl_value)) Sall(sgl_value)++
DECL|macro|Duint_isinexact_to_dbl
mdefine_line|#define Duint_isinexact_to_dbl(duint_value) &t;&bslash;&n;    (Duintp2(duint_value) &lt;&lt; 32 - DBL_EXP_LENGTH)
DECL|macro|Dbl_roundnearest_from_duint
mdefine_line|#define Dbl_roundnearest_from_duint(duint_opndB,dbl_opndA,dbl_opndB) &t;&bslash;&n;    if (Duintp2(duint_opndB) &amp; 1&lt;&lt;(DBL_EXP_LENGTH - 1))&t;&t;&t;&bslash;&n;       if ((Duintp2(duint_opndB) &lt;&lt; 33 - DBL_EXP_LENGTH) || Dlowp2(dbl_opndB)) &bslash;&n;          if ((++Dallp2(dbl_opndB))==0) Dallp1(dbl_opndA)++
DECL|macro|Suint_from_sgl_mantissa
mdefine_line|#define Suint_from_sgl_mantissa(src,exponent,result)&t;&bslash;&n;    Sall(result) = (unsigned)(Sall(src) &lt;&lt; SGL_EXP_LENGTH)&gt;&gt;(31 - exponent)
DECL|macro|Sgl_isinexact_to_unsigned
mdefine_line|#define Sgl_isinexact_to_unsigned(sgl_value,exponent)&t;&bslash;&n;    Sgl_isinexact_to_fix(sgl_value,exponent)
DECL|macro|Duint_from_sgl_mantissa
mdefine_line|#define Duint_from_sgl_mantissa(sgl_value,exponent,dresultA,dresultB)&t;&bslash;&n;  {Sall(sgl_value) &lt;&lt;= SGL_EXP_LENGTH;  /*  left-justify  */&t;&t;&bslash;&n;    if (exponent &lt;= 31) {&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;Dintp1(dresultA) = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;Dintp2(dresultB) = (unsigned)Sall(sgl_value) &gt;&gt; (31 - exponent); &bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;Dintp1(dresultA) = Sall(sgl_value) &gt;&gt; (63 - exponent);&t;&t;&bslash;&n;    &t;Dintp2(dresultB) = Sall(sgl_value) &lt;&lt; (exponent - 31);&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    Sall(sgl_value) &gt;&gt;= SGL_EXP_LENGTH;  /* return to original */&t;&bslash;&n;  }
DECL|macro|Duint_setzero
mdefine_line|#define Duint_setzero(dresultA,dresultB) &t;&bslash;&n;    Dint_setzero(dresultA,dresultB)
DECL|macro|Duint_increment
mdefine_line|#define Duint_increment(dresultA,dresultB) Dint_increment(dresultA,dresultB) 
DECL|macro|Duint_isone_lowp2
mdefine_line|#define Duint_isone_lowp2(dresultB)  Dint_isone_lowp2(dresultB)
DECL|macro|Suint_from_dbl_mantissa
mdefine_line|#define Suint_from_dbl_mantissa(srcA,srcB,exponent,dest) &bslash;&n;    Shiftdouble(Dallp1(srcA),Dallp2(srcB),21,dest); &bslash;&n;    dest = (unsigned)dest &gt;&gt; 31 - exponent
DECL|macro|Dbl_isinexact_to_unsigned
mdefine_line|#define Dbl_isinexact_to_unsigned(dbl_valueA,dbl_valueB,exponent) &bslash;&n;    Dbl_isinexact_to_fix(dbl_valueA,dbl_valueB,exponent)
DECL|macro|Duint_from_dbl_mantissa
mdefine_line|#define Duint_from_dbl_mantissa(dbl_valueA,dbl_valueB,exponent,destA,destB) &bslash;&n;    Dint_from_dbl_mantissa(dbl_valueA,dbl_valueB,exponent,destA,destB) 
eof
