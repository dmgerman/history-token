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
multiline_comment|/* 32-bit word grabing functions */
DECL|macro|Sgl_firstword
mdefine_line|#define Sgl_firstword(value) Sall(value)
DECL|macro|Sgl_secondword
mdefine_line|#define Sgl_secondword(value) dummy_location
DECL|macro|Sgl_thirdword
mdefine_line|#define Sgl_thirdword(value) dummy_location
DECL|macro|Sgl_fourthword
mdefine_line|#define Sgl_fourthword(value) dummy_location
DECL|macro|Sgl_sign
mdefine_line|#define Sgl_sign(object) Ssign(object)
DECL|macro|Sgl_exponent
mdefine_line|#define Sgl_exponent(object) Sexponent(object)
DECL|macro|Sgl_signexponent
mdefine_line|#define Sgl_signexponent(object) Ssignexponent(object)
DECL|macro|Sgl_mantissa
mdefine_line|#define Sgl_mantissa(object) Smantissa(object)
DECL|macro|Sgl_exponentmantissa
mdefine_line|#define Sgl_exponentmantissa(object) Sexponentmantissa(object)
DECL|macro|Sgl_all
mdefine_line|#define Sgl_all(object) Sall(object)
multiline_comment|/* sgl_and_signs ands the sign bits of each argument and puts the result&n; * into the first argument. sgl_or_signs ors those same sign bits */
DECL|macro|Sgl_and_signs
mdefine_line|#define Sgl_and_signs( src1dst, src2)&t;&t;&bslash;&n;    Sall(src1dst) = (Sall(src2)|~((unsigned int)1&lt;&lt;31)) &amp; Sall(src1dst)
DECL|macro|Sgl_or_signs
mdefine_line|#define Sgl_or_signs( src1dst, src2)&t;&t;&bslash;&n;    Sall(src1dst) = (Sall(src2)&amp;((unsigned int)1&lt;&lt;31)) | Sall(src1dst)
multiline_comment|/* The hidden bit is always the low bit of the exponent */
DECL|macro|Sgl_clear_exponent_set_hidden
mdefine_line|#define Sgl_clear_exponent_set_hidden(srcdst) Deposit_sexponent(srcdst,1)
DECL|macro|Sgl_clear_signexponent_set_hidden
mdefine_line|#define Sgl_clear_signexponent_set_hidden(srcdst) &bslash;&n;    Deposit_ssignexponent(srcdst,1)
DECL|macro|Sgl_clear_sign
mdefine_line|#define Sgl_clear_sign(srcdst) Sall(srcdst) &amp;= ~((unsigned int)1&lt;&lt;31)
DECL|macro|Sgl_clear_signexponent
mdefine_line|#define Sgl_clear_signexponent(srcdst) Sall(srcdst) &amp;= 0x007fffff
multiline_comment|/* varamount must be less than 32 for the next three functions */
DECL|macro|Sgl_rightshift
mdefine_line|#define Sgl_rightshift(srcdst, varamount)&t;&bslash;&n;    Sall(srcdst) &gt;&gt;= varamount
DECL|macro|Sgl_leftshift
mdefine_line|#define Sgl_leftshift(srcdst, varamount)&t;&bslash;&n;    Sall(srcdst) &lt;&lt;= varamount
DECL|macro|Sgl_rightshift_exponentmantissa
mdefine_line|#define Sgl_rightshift_exponentmantissa(srcdst, varamount) &bslash;&n;    Sall(srcdst) = &bslash;&n;&t;(Sexponentmantissa(srcdst) &gt;&gt; varamount) | &bslash;&n;&t;(Sall(srcdst) &amp; ((unsigned int)1&lt;&lt;31))
DECL|macro|Sgl_leftshiftby1_withextent
mdefine_line|#define Sgl_leftshiftby1_withextent(left,right,result) &bslash;&n;    Shiftdouble(Sall(left),Extall(right),31,Sall(result))
DECL|macro|Sgl_rightshiftby1_withextent
mdefine_line|#define Sgl_rightshiftby1_withextent(left,right,dst)&t;&t;&bslash;&n;    Shiftdouble(Sall(left),Extall(right),1,Extall(right))
DECL|macro|Sgl_arithrightshiftby1
mdefine_line|#define Sgl_arithrightshiftby1(srcdst)&t;&bslash;&n;    Sall(srcdst) = (int)Sall(srcdst) &gt;&gt; 1
multiline_comment|/* Sign extend the sign bit with an integer destination */
DECL|macro|Sgl_signextendedsign
mdefine_line|#define Sgl_signextendedsign(value) Ssignedsign(value)
DECL|macro|Sgl_isone_hidden
mdefine_line|#define Sgl_isone_hidden(sgl_value) (Shidden(sgl_value))
DECL|macro|Sgl_increment
mdefine_line|#define Sgl_increment(sgl_value) Sall(sgl_value) += 1
DECL|macro|Sgl_increment_mantissa
mdefine_line|#define Sgl_increment_mantissa(sgl_value) &bslash;&n;    Deposit_smantissa(sgl_value,sgl_value+1)
DECL|macro|Sgl_decrement
mdefine_line|#define Sgl_decrement(sgl_value) Sall(sgl_value) -= 1
DECL|macro|Sgl_isone_sign
mdefine_line|#define Sgl_isone_sign(sgl_value) (Is_ssign(sgl_value)!=0)
DECL|macro|Sgl_isone_hiddenoverflow
mdefine_line|#define Sgl_isone_hiddenoverflow(sgl_value) &bslash;&n;    (Is_shiddenoverflow(sgl_value)!=0)
DECL|macro|Sgl_isone_lowmantissa
mdefine_line|#define Sgl_isone_lowmantissa(sgl_value) (Is_slow(sgl_value)!=0)
DECL|macro|Sgl_isone_signaling
mdefine_line|#define Sgl_isone_signaling(sgl_value) (Is_ssignaling(sgl_value)!=0)
DECL|macro|Sgl_is_signalingnan
mdefine_line|#define Sgl_is_signalingnan(sgl_value) (Ssignalingnan(sgl_value)==0x1ff)
DECL|macro|Sgl_isnotzero
mdefine_line|#define Sgl_isnotzero(sgl_value) (Sall(sgl_value)!=0)
DECL|macro|Sgl_isnotzero_hiddenhigh7mantissa
mdefine_line|#define Sgl_isnotzero_hiddenhigh7mantissa(sgl_value) &bslash;&n;    (Shiddenhigh7mantissa(sgl_value)!=0)
DECL|macro|Sgl_isnotzero_low4
mdefine_line|#define Sgl_isnotzero_low4(sgl_value) (Slow4(sgl_value)!=0)
DECL|macro|Sgl_isnotzero_exponent
mdefine_line|#define Sgl_isnotzero_exponent(sgl_value) (Sexponent(sgl_value)!=0)
DECL|macro|Sgl_isnotzero_mantissa
mdefine_line|#define Sgl_isnotzero_mantissa(sgl_value) (Smantissa(sgl_value)!=0)
DECL|macro|Sgl_isnotzero_exponentmantissa
mdefine_line|#define Sgl_isnotzero_exponentmantissa(sgl_value) &bslash;&n;    (Sexponentmantissa(sgl_value)!=0)
DECL|macro|Sgl_iszero
mdefine_line|#define Sgl_iszero(sgl_value) (Sall(sgl_value)==0)
DECL|macro|Sgl_iszero_signaling
mdefine_line|#define Sgl_iszero_signaling(sgl_value) (Is_ssignaling(sgl_value)==0)
DECL|macro|Sgl_iszero_hidden
mdefine_line|#define Sgl_iszero_hidden(sgl_value) (Is_shidden(sgl_value)==0)
DECL|macro|Sgl_iszero_hiddenoverflow
mdefine_line|#define Sgl_iszero_hiddenoverflow(sgl_value) &bslash;&n;    (Is_shiddenoverflow(sgl_value)==0)
DECL|macro|Sgl_iszero_hiddenhigh3mantissa
mdefine_line|#define Sgl_iszero_hiddenhigh3mantissa(sgl_value) &bslash;&n;    (Shiddenhigh3mantissa(sgl_value)==0)
DECL|macro|Sgl_iszero_hiddenhigh7mantissa
mdefine_line|#define Sgl_iszero_hiddenhigh7mantissa(sgl_value) &bslash;&n;    (Shiddenhigh7mantissa(sgl_value)==0)
DECL|macro|Sgl_iszero_sign
mdefine_line|#define Sgl_iszero_sign(sgl_value) (Is_ssign(sgl_value)==0)
DECL|macro|Sgl_iszero_exponent
mdefine_line|#define Sgl_iszero_exponent(sgl_value) (Sexponent(sgl_value)==0)
DECL|macro|Sgl_iszero_mantissa
mdefine_line|#define Sgl_iszero_mantissa(sgl_value) (Smantissa(sgl_value)==0)
DECL|macro|Sgl_iszero_exponentmantissa
mdefine_line|#define Sgl_iszero_exponentmantissa(sgl_value) &bslash;&n;    (Sexponentmantissa(sgl_value)==0)
DECL|macro|Sgl_isinfinity_exponent
mdefine_line|#define Sgl_isinfinity_exponent(sgl_value) &t;&t;&bslash;&n;    (Sgl_exponent(sgl_value)==SGL_INFINITY_EXPONENT)
DECL|macro|Sgl_isnotinfinity_exponent
mdefine_line|#define Sgl_isnotinfinity_exponent(sgl_value) &t;&t;&bslash;&n;    (Sgl_exponent(sgl_value)!=SGL_INFINITY_EXPONENT)
DECL|macro|Sgl_isinfinity
mdefine_line|#define Sgl_isinfinity(sgl_value)&t;&t;&t;&bslash;&n;    (Sgl_exponent(sgl_value)==SGL_INFINITY_EXPONENT &amp;&amp;&t;&bslash;&n;    Sgl_mantissa(sgl_value)==0)
DECL|macro|Sgl_isnan
mdefine_line|#define Sgl_isnan(sgl_value)&t;&t;&t;&t;&bslash;&n;    (Sgl_exponent(sgl_value)==SGL_INFINITY_EXPONENT &amp;&amp;&t;&bslash;&n;    Sgl_mantissa(sgl_value)!=0)
DECL|macro|Sgl_isnotnan
mdefine_line|#define Sgl_isnotnan(sgl_value)&t;&t;&t;&t;&bslash;&n;    (Sgl_exponent(sgl_value)!=SGL_INFINITY_EXPONENT ||&t;&bslash;&n;    Sgl_mantissa(sgl_value)==0)
DECL|macro|Sgl_islessthan
mdefine_line|#define Sgl_islessthan(sgl_op1,sgl_op2)&t;&t;&t;&bslash;&n;    (Sall(sgl_op1) &lt; Sall(sgl_op2))
DECL|macro|Sgl_isgreaterthan
mdefine_line|#define Sgl_isgreaterthan(sgl_op1,sgl_op2)&t;&t;&bslash;&n;    (Sall(sgl_op1) &gt; Sall(sgl_op2))
DECL|macro|Sgl_isnotlessthan
mdefine_line|#define Sgl_isnotlessthan(sgl_op1,sgl_op2)&t;&t;&bslash;&n;    (Sall(sgl_op1) &gt;= Sall(sgl_op2))
DECL|macro|Sgl_isequal
mdefine_line|#define Sgl_isequal(sgl_op1,sgl_op2)&t;&t;&t;&bslash;&n;    (Sall(sgl_op1) == Sall(sgl_op2))
DECL|macro|Sgl_leftshiftby8
mdefine_line|#define Sgl_leftshiftby8(sgl_value) &bslash;&n;    Sall(sgl_value) &lt;&lt;= 8
DECL|macro|Sgl_leftshiftby4
mdefine_line|#define Sgl_leftshiftby4(sgl_value) &bslash;&n;    Sall(sgl_value) &lt;&lt;= 4
DECL|macro|Sgl_leftshiftby3
mdefine_line|#define Sgl_leftshiftby3(sgl_value) &bslash;&n;    Sall(sgl_value) &lt;&lt;= 3
DECL|macro|Sgl_leftshiftby2
mdefine_line|#define Sgl_leftshiftby2(sgl_value) &bslash;&n;    Sall(sgl_value) &lt;&lt;= 2
DECL|macro|Sgl_leftshiftby1
mdefine_line|#define Sgl_leftshiftby1(sgl_value) &bslash;&n;    Sall(sgl_value) &lt;&lt;= 1
DECL|macro|Sgl_rightshiftby1
mdefine_line|#define Sgl_rightshiftby1(sgl_value) &bslash;&n;    Sall(sgl_value) &gt;&gt;= 1
DECL|macro|Sgl_rightshiftby4
mdefine_line|#define Sgl_rightshiftby4(sgl_value) &bslash;&n;    Sall(sgl_value) &gt;&gt;= 4
DECL|macro|Sgl_rightshiftby8
mdefine_line|#define Sgl_rightshiftby8(sgl_value) &bslash;&n;    Sall(sgl_value) &gt;&gt;= 8
DECL|macro|Sgl_ismagnitudeless
mdefine_line|#define Sgl_ismagnitudeless(signlessleft,signlessright)&t;&t;&t;&bslash;&n;/*  unsigned int signlessleft, signlessright; */&t;&t;&t;&bslash;&n;      (signlessleft &lt; signlessright)  
DECL|macro|Sgl_copytoint_exponentmantissa
mdefine_line|#define Sgl_copytoint_exponentmantissa(source,dest)     &bslash;&n;    dest = Sexponentmantissa(source)
multiline_comment|/* A quiet NaN has the high mantissa bit clear and at least on other (in this&n; * case the adjacent bit) bit set. */
DECL|macro|Sgl_set_quiet
mdefine_line|#define Sgl_set_quiet(sgl_value) Deposit_shigh2mantissa(sgl_value,1)
DECL|macro|Sgl_set_exponent
mdefine_line|#define Sgl_set_exponent(sgl_value,exp) Deposit_sexponent(sgl_value,exp)
DECL|macro|Sgl_set_mantissa
mdefine_line|#define Sgl_set_mantissa(dest,value) Deposit_smantissa(dest,value)
DECL|macro|Sgl_set_exponentmantissa
mdefine_line|#define Sgl_set_exponentmantissa(dest,value) &bslash;&n;    Deposit_sexponentmantissa(dest,value)
multiline_comment|/*  An infinity is represented with the max exponent and a zero mantissa */
DECL|macro|Sgl_setinfinity_exponent
mdefine_line|#define Sgl_setinfinity_exponent(sgl_value) &bslash;&n;    Deposit_sexponent(sgl_value,SGL_INFINITY_EXPONENT)
DECL|macro|Sgl_setinfinity_exponentmantissa
mdefine_line|#define Sgl_setinfinity_exponentmantissa(sgl_value)&t;&bslash;&n;    Deposit_sexponentmantissa(sgl_value, &bslash;&n;&t;(SGL_INFINITY_EXPONENT &lt;&lt; (32-(1+SGL_EXP_LENGTH))))
DECL|macro|Sgl_setinfinitypositive
mdefine_line|#define Sgl_setinfinitypositive(sgl_value)&t;&t;&bslash;&n;    Sall(sgl_value) = (SGL_INFINITY_EXPONENT &lt;&lt; (32-(1+SGL_EXP_LENGTH)))
DECL|macro|Sgl_setinfinitynegative
mdefine_line|#define Sgl_setinfinitynegative(sgl_value)&t;&t;&bslash;&n;    Sall(sgl_value) = (SGL_INFINITY_EXPONENT &lt;&lt; (32-(1+SGL_EXP_LENGTH))) &bslash;&n;    | ((unsigned int)1&lt;&lt;31)
DECL|macro|Sgl_setinfinity
mdefine_line|#define Sgl_setinfinity(sgl_value,sign)&t;&t;&t;&t;&t;&bslash;&n;    Sall(sgl_value) = (SGL_INFINITY_EXPONENT &lt;&lt; (32-(1+SGL_EXP_LENGTH))) | &bslash;&n;     ((unsigned int)sign &lt;&lt; 31)
DECL|macro|Sgl_sethigh4bits
mdefine_line|#define Sgl_sethigh4bits(sgl_value, extsign)  &bslash;&n;    Deposit_shigh4(sgl_value,extsign)
DECL|macro|Sgl_set_sign
mdefine_line|#define Sgl_set_sign(sgl_value,sign) Deposit_ssign(sgl_value,sign)
DECL|macro|Sgl_invert_sign
mdefine_line|#define Sgl_invert_sign(sgl_value)  &bslash;&n;    Deposit_ssign(sgl_value,~Ssign(sgl_value))
DECL|macro|Sgl_setone_sign
mdefine_line|#define Sgl_setone_sign(sgl_value) Deposit_ssign(sgl_value,1)
DECL|macro|Sgl_setone_lowmantissa
mdefine_line|#define Sgl_setone_lowmantissa(sgl_value) Deposit_slow(sgl_value,1)
DECL|macro|Sgl_setzero_sign
mdefine_line|#define Sgl_setzero_sign(sgl_value)  Sall(sgl_value) &amp;= 0x7fffffff
DECL|macro|Sgl_setzero_exponent
mdefine_line|#define Sgl_setzero_exponent(sgl_value) Sall(sgl_value) &amp;= 0x807fffff
DECL|macro|Sgl_setzero_mantissa
mdefine_line|#define Sgl_setzero_mantissa(sgl_value) Sall(sgl_value) &amp;= 0xff800000
DECL|macro|Sgl_setzero_exponentmantissa
mdefine_line|#define Sgl_setzero_exponentmantissa(sgl_value)  Sall(sgl_value) &amp;= 0x80000000
DECL|macro|Sgl_setzero
mdefine_line|#define Sgl_setzero(sgl_value) Sall(sgl_value) = 0
DECL|macro|Sgl_setnegativezero
mdefine_line|#define Sgl_setnegativezero(sgl_value) Sall(sgl_value) = (unsigned int)1 &lt;&lt; 31
multiline_comment|/* Use following macro for both overflow &amp; underflow conditions */
DECL|macro|ovfl
mdefine_line|#define ovfl -
DECL|macro|unfl
mdefine_line|#define unfl +
DECL|macro|Sgl_setwrapped_exponent
mdefine_line|#define Sgl_setwrapped_exponent(sgl_value,exponent,op) &bslash;&n;    Deposit_sexponent(sgl_value,(exponent op SGL_WRAP))
DECL|macro|Sgl_setlargestpositive
mdefine_line|#define Sgl_setlargestpositive(sgl_value) &t;&t;&t;&t;&bslash;&n;    Sall(sgl_value) = ((SGL_EMAX+SGL_BIAS) &lt;&lt; (32-(1+SGL_EXP_LENGTH)))&t;&bslash;&n;                      | ((1&lt;&lt;(32-(1+SGL_EXP_LENGTH))) - 1 )
DECL|macro|Sgl_setlargestnegative
mdefine_line|#define Sgl_setlargestnegative(sgl_value)&t;&t;&t;&t;&bslash;&n;    Sall(sgl_value) = ((SGL_EMAX+SGL_BIAS) &lt;&lt; (32-(1+SGL_EXP_LENGTH)))&t;&bslash;&n;                      | ((1&lt;&lt;(32-(1+SGL_EXP_LENGTH))) - 1 )&t;&t;&bslash;&n;&t;&t;      | ((unsigned int)1&lt;&lt;31)
DECL|macro|Sgl_setnegativeinfinity
mdefine_line|#define Sgl_setnegativeinfinity(sgl_value)&t;&bslash;&n;    Sall(sgl_value) = &t;&t;&t;&t;&bslash;&n;    ((1&lt;&lt;SGL_EXP_LENGTH) | SGL_INFINITY_EXPONENT) &lt;&lt; (32-(1+SGL_EXP_LENGTH))
DECL|macro|Sgl_setlargest
mdefine_line|#define Sgl_setlargest(sgl_value,sign) &t;&t;&t;&t;&t;&bslash;&n;    Sall(sgl_value) = (unsigned int)sign &lt;&lt; 31 |&t;&t;&t;&bslash;&n;        (((SGL_EMAX+SGL_BIAS) &lt;&lt; (32-(1+SGL_EXP_LENGTH)))&t;&t;&bslash;&n;&t;  | ((1 &lt;&lt; (32-(1+SGL_EXP_LENGTH))) - 1 ))
DECL|macro|Sgl_setlargest_exponentmantissa
mdefine_line|#define Sgl_setlargest_exponentmantissa(sgl_value)&t;&t;&t;&bslash;&n;    Sall(sgl_value) = Sall(sgl_value) &amp; ((unsigned int)1&lt;&lt;31) |&t;&t;&bslash;&n;        (((SGL_EMAX+SGL_BIAS) &lt;&lt; (32-(1+SGL_EXP_LENGTH)))&t;&t;&bslash;&n;&t;  | ((1 &lt;&lt; (32-(1+SGL_EXP_LENGTH))) - 1 ))
multiline_comment|/* The high bit is always zero so arithmetic or logical shifts will work. */
DECL|macro|Sgl_right_align
mdefine_line|#define Sgl_right_align(srcdst,shift,extent)&t;&t;&t;&t;&bslash;&n;    /* sgl_floating_point srcdst; int shift; extension extent */&t;&bslash;&n;    if (shift &lt; 32) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;Extall(extent) = Sall(srcdst) &lt;&lt; (32-(shift));&t;&t;&t;&bslash;&n;    &t;Sall(srcdst) &gt;&gt;= shift;&t;&t;&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;Extall(extent) = Sall(srcdst);&t;&t;&t;&t;&t;&bslash;&n;&t;Sall(srcdst) = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;    }
DECL|macro|Sgl_hiddenhigh3mantissa
mdefine_line|#define Sgl_hiddenhigh3mantissa(sgl_value) Shiddenhigh3mantissa(sgl_value)
DECL|macro|Sgl_hidden
mdefine_line|#define Sgl_hidden(sgl_value) Shidden(sgl_value)
DECL|macro|Sgl_lowmantissa
mdefine_line|#define Sgl_lowmantissa(sgl_value) Slow(sgl_value)
multiline_comment|/* The left argument is never smaller than the right argument */
DECL|macro|Sgl_subtract
mdefine_line|#define Sgl_subtract(sgl_left,sgl_right,sgl_result) &bslash;&n;    Sall(sgl_result) = Sall(sgl_left) - Sall(sgl_right)
multiline_comment|/* Subtract right augmented with extension from left augmented with zeros and&n; * store into result and extension. */
DECL|macro|Sgl_subtract_withextension
mdefine_line|#define Sgl_subtract_withextension(left,right,extent,result)&t;&t;&bslash;&n;    /* sgl_floating_point left,right,result; extension extent */&t;&bslash;&n;  Sgl_subtract(left,right,result);&t;&t;&t;&t;&t;&bslash;&n;  if((Extall(extent) = 0-Extall(extent)))&t;&t;&t;&t;&bslash;&n;      Sall(result) = Sall(result)-1
DECL|macro|Sgl_addition
mdefine_line|#define Sgl_addition(sgl_left,sgl_right,sgl_result) &bslash;&n;    Sall(sgl_result) = Sall(sgl_left) + Sall(sgl_right)
DECL|macro|Sgl_xortointp1
mdefine_line|#define Sgl_xortointp1(left,right,result)&t;&t;&t;&bslash;&n;    result = Sall(left) XOR Sall(right);
DECL|macro|Sgl_xorfromintp1
mdefine_line|#define Sgl_xorfromintp1(left,right,result)&t;&t;&t;&bslash;&n;    Sall(result) = left XOR Sall(right)
multiline_comment|/* Need to Initialize */
DECL|macro|Sgl_makequietnan
mdefine_line|#define Sgl_makequietnan(dest)&t;&t;&t;&t;&t;&t;&bslash;&n;    Sall(dest) = ((SGL_EMAX+SGL_BIAS)+1)&lt;&lt; (32-(1+SGL_EXP_LENGTH))&t;&bslash;&n;                 | (1&lt;&lt;(32-(1+SGL_EXP_LENGTH+2)))
DECL|macro|Sgl_makesignalingnan
mdefine_line|#define Sgl_makesignalingnan(dest)&t;&t;&t;&t;&t;&bslash;&n;    Sall(dest) = ((SGL_EMAX+SGL_BIAS)+1)&lt;&lt; (32-(1+SGL_EXP_LENGTH))&t;&bslash;&n;                 | (1&lt;&lt;(32-(1+SGL_EXP_LENGTH+1)))
DECL|macro|Sgl_normalize
mdefine_line|#define Sgl_normalize(sgl_opnd,exponent)&t;&t;&t;&bslash;&n;&t;while(Sgl_iszero_hiddenhigh7mantissa(sgl_opnd)) {&t;&bslash;&n;&t;&t;Sgl_leftshiftby8(sgl_opnd);&t;&t;&t;&bslash;&n;&t;&t;exponent -= 8;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if(Sgl_iszero_hiddenhigh3mantissa(sgl_opnd)) {&t;&t;&bslash;&n;&t;&t;Sgl_leftshiftby4(sgl_opnd);&t;&t;&t;&bslash;&n;&t;&t;exponent -= 4;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;while(Sgl_iszero_hidden(sgl_opnd)) {&t;&t;&t;&bslash;&n;&t;&t;Sgl_leftshiftby1(sgl_opnd);&t;&t;&t;&bslash;&n;&t;&t;exponent -= 1;&t;&t;&t;&t;&t;&bslash;&n;&t;}
DECL|macro|Sgl_setoverflow
mdefine_line|#define Sgl_setoverflow(sgl_opnd)&t;&t;&t;&t;&bslash;&n;&t;/* set result to infinity or largest number */&t;&t;&bslash;&n;&t;switch (Rounding_mode()) {&t;&t;&t;&t;&bslash;&n;&t;&t;case ROUNDPLUS:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (Sgl_isone_sign(sgl_opnd)) {&t;&t;&bslash;&n;&t;&t;&t;&t;Sgl_setlargestnegative(sgl_opnd); &bslash;&n;&t;&t;&t;}&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;else {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;Sgl_setinfinitypositive(sgl_opnd); &bslash;&n;&t;&t;&t;}&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case ROUNDMINUS:&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (Sgl_iszero_sign(sgl_opnd)) {&t;&bslash;&n;&t;&t;&t;&t;Sgl_setlargestpositive(sgl_opnd); &bslash;&n;&t;&t;&t;}&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;else {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;Sgl_setinfinitynegative(sgl_opnd); &bslash;&n;&t;&t;&t;}&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case ROUNDNEAREST:&t;&t;&t;&t;&bslash;&n;&t;&t;&t;Sgl_setinfinity_exponentmantissa(sgl_opnd); &bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case ROUNDZERO:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;Sgl_setlargest_exponentmantissa(sgl_opnd); &bslash;&n;&t;}
DECL|macro|Sgl_denormalize
mdefine_line|#define Sgl_denormalize(opnd,exponent,guard,sticky,inexact)&t;&t;&bslash;&n;&t;Sgl_clear_signexponent_set_hidden(opnd);&t;&t;&t;&bslash;&n;&t;if (exponent &gt;= (1 - SGL_P)) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;guard = (Sall(opnd) &gt;&gt; -exponent) &amp; 1;&t;&t;&t;&bslash;&n;&t;&t;if (exponent &lt; 0) sticky |= Sall(opnd) &lt;&lt; (32+exponent); &bslash;&n;&t;&t;inexact = guard | sticky;&t;&t;&t;&t;&bslash;&n;&t;&t;Sall(opnd) &gt;&gt;= (1-exponent);&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;guard = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;sticky |= Sall(opnd);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;inexact = sticky;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;Sgl_setzero(opnd);&t;&t;&t;&t;&t;&bslash;&n;&t;}
multiline_comment|/* &n; * The fused multiply add instructions requires a single extended format,&n; * with 48 bits of mantissa.&n; */
DECL|macro|SGLEXT_THRESHOLD
mdefine_line|#define SGLEXT_THRESHOLD 48
DECL|macro|Sglext_setzero
mdefine_line|#define Sglext_setzero(valA,valB)&t;&bslash;&n;    Sextallp1(valA) = 0; Sextallp2(valB) = 0
DECL|macro|Sglext_isnotzero_mantissap2
mdefine_line|#define Sglext_isnotzero_mantissap2(valB) (Sextallp2(valB)!=0)
DECL|macro|Sglext_isone_lowp1
mdefine_line|#define Sglext_isone_lowp1(val) (Sextlowp1(val)!=0)
DECL|macro|Sglext_isone_highp2
mdefine_line|#define Sglext_isone_highp2(val) (Sexthighp2(val)!=0)
DECL|macro|Sglext_isnotzero_low31p2
mdefine_line|#define Sglext_isnotzero_low31p2(val) (Sextlow31p2(val)!=0)
DECL|macro|Sglext_iszero
mdefine_line|#define Sglext_iszero(valA,valB) (Sextallp1(valA)==0 &amp;&amp; Sextallp2(valB)==0)
DECL|macro|Sgl_copytoptr
mdefine_line|#define Sgl_copytoptr(src,destptr) *destptr = src
DECL|macro|Sgl_copyfromptr
mdefine_line|#define Sgl_copyfromptr(srcptr,dest) dest = *srcptr
DECL|macro|Sglext_copy
mdefine_line|#define Sglext_copy(srca,srcb,desta,destb) &bslash;&n;    Sextallp1(desta) = Sextallp1(srca);&t;&bslash;&n;    Sextallp2(destb) = Sextallp2(srcb)
DECL|macro|Sgl_copyto_sglext
mdefine_line|#define Sgl_copyto_sglext(src1,dest1,dest2) &bslash;&n;&t;Sextallp1(dest1) = Sall(src1); Sextallp2(dest2) = 0
DECL|macro|Sglext_swap_lower
mdefine_line|#define Sglext_swap_lower(leftp2,rightp2)  &bslash;&n;    Sextallp2(leftp2)  = Sextallp2(leftp2) XOR Sextallp2(rightp2);  &bslash;&n;    Sextallp2(rightp2) = Sextallp2(leftp2) XOR Sextallp2(rightp2);  &bslash;&n;    Sextallp2(leftp2)  = Sextallp2(leftp2) XOR Sextallp2(rightp2)
DECL|macro|Sglext_setone_lowmantissap2
mdefine_line|#define Sglext_setone_lowmantissap2(value) Deposit_dlowp2(value,1)
multiline_comment|/* The high bit is always zero so arithmetic or logical shifts will work. */
DECL|macro|Sglext_right_align
mdefine_line|#define Sglext_right_align(srcdstA,srcdstB,shift) &bslash;&n;  {int shiftamt, sticky;&t;&t;&t;&t;&t;&t;&bslash;&n;    shiftamt = shift % 32;&t;&t;&t;&t;&t;&t;&bslash;&n;    sticky = 0;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    switch (shift/32) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;     case 0: if (shiftamt &gt; 0) {&t;&t;&t;&t;&t;&bslash;&n;&t;        sticky = Sextallp2(srcdstB) &lt;&lt; 32 - (shiftamt);&t;&t;&bslash;&n;                Variable_shift_double(Sextallp1(srcdstA),&t;&t;&bslash;&n;&t;&t; Sextallp2(srcdstB),shiftamt,Sextallp2(srcdstB));&t;&bslash;&n;&t;        Sextallp1(srcdstA) &gt;&gt;= shiftamt;&t;&t;&t;&bslash;&n;&t;     }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;     break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;     case 1: if (shiftamt &gt; 0) {&t;&t;&t;&t;&t;&bslash;&n;&t;        sticky = (Sextallp1(srcdstA) &lt;&lt; 32 - (shiftamt)) |&t;&bslash;&n;&t;&t;&t; Sextallp2(srcdstB);&t;&t;&t;&t;&bslash;&n;&t;     }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;     else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;sticky = Sextallp2(srcdstB);&t;&t;&t;&t;&bslash;&n;&t;     }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;     Sextallp2(srcdstB) = Sextallp1(srcdstA) &gt;&gt; shiftamt;&t;&bslash;&n;&t;     Sextallp1(srcdstA) = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;     break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (sticky) Sglext_setone_lowmantissap2(srcdstB);&t;&t;&t;&bslash;&n;  }
multiline_comment|/* The left argument is never smaller than the right argument */
DECL|macro|Sglext_subtract
mdefine_line|#define Sglext_subtract(lefta,leftb,righta,rightb,resulta,resultb) &bslash;&n;    if( Sextallp2(rightb) &gt; Sextallp2(leftb) ) Sextallp1(lefta)--; &bslash;&n;    Sextallp2(resultb) = Sextallp2(leftb) - Sextallp2(rightb);&t;&bslash;&n;    Sextallp1(resulta) = Sextallp1(lefta) - Sextallp1(righta)
DECL|macro|Sglext_addition
mdefine_line|#define Sglext_addition(lefta,leftb,righta,rightb,resulta,resultb) &bslash;&n;    /* If the sum of the low words is less than either source, then &bslash;&n;     * an overflow into the next word occurred. */ &bslash;&n;    if ((Sextallp2(resultb) = Sextallp2(leftb)+Sextallp2(rightb)) &lt; &bslash;&n;        Sextallp2(rightb)) &bslash;&n;&t;    Sextallp1(resulta) = Sextallp1(lefta)+Sextallp1(righta)+1; &bslash;&n;    else Sextallp1(resulta) = Sextallp1(lefta)+Sextallp1(righta)
DECL|macro|Sglext_arithrightshiftby1
mdefine_line|#define Sglext_arithrightshiftby1(srcdstA,srcdstB)&t;&bslash;&n;    Shiftdouble(Sextallp1(srcdstA),Sextallp2(srcdstB),1,Sextallp2(srcdstB)); &bslash;&n;    Sextallp1(srcdstA) = (int)Sextallp1(srcdstA) &gt;&gt; 1
DECL|macro|Sglext_leftshiftby8
mdefine_line|#define Sglext_leftshiftby8(valA,valB) &bslash;&n;    Shiftdouble(Sextallp1(valA),Sextallp2(valB),24,Sextallp1(valA)); &bslash;&n;    Sextallp2(valB) &lt;&lt;= 8
DECL|macro|Sglext_leftshiftby4
mdefine_line|#define Sglext_leftshiftby4(valA,valB) &bslash;&n;    Shiftdouble(Sextallp1(valA),Sextallp2(valB),28,Sextallp1(valA)); &bslash;&n;    Sextallp2(valB) &lt;&lt;= 4
DECL|macro|Sglext_leftshiftby3
mdefine_line|#define Sglext_leftshiftby3(valA,valB) &bslash;&n;    Shiftdouble(Sextallp1(valA),Sextallp2(valB),29,Sextallp1(valA)); &bslash;&n;    Sextallp2(valB) &lt;&lt;= 3
DECL|macro|Sglext_leftshiftby2
mdefine_line|#define Sglext_leftshiftby2(valA,valB) &bslash;&n;    Shiftdouble(Sextallp1(valA),Sextallp2(valB),30,Sextallp1(valA)); &bslash;&n;    Sextallp2(valB) &lt;&lt;= 2
DECL|macro|Sglext_leftshiftby1
mdefine_line|#define Sglext_leftshiftby1(valA,valB) &bslash;&n;    Shiftdouble(Sextallp1(valA),Sextallp2(valB),31,Sextallp1(valA)); &bslash;&n;    Sextallp2(valB) &lt;&lt;= 1
DECL|macro|Sglext_rightshiftby4
mdefine_line|#define Sglext_rightshiftby4(valueA,valueB) &bslash;&n;    Shiftdouble(Sextallp1(valueA),Sextallp2(valueB),4,Sextallp2(valueB)); &bslash;&n;    Sextallp1(valueA) &gt;&gt;= 4
DECL|macro|Sglext_rightshiftby3
mdefine_line|#define Sglext_rightshiftby3(valueA,valueB) &bslash;&n;    Shiftdouble(Sextallp1(valueA),Sextallp2(valueB),3,Sextallp2(valueB)); &bslash;&n;    Sextallp1(valueA) &gt;&gt;= 3
DECL|macro|Sglext_rightshiftby1
mdefine_line|#define Sglext_rightshiftby1(valueA,valueB) &bslash;&n;    Shiftdouble(Sextallp1(valueA),Sextallp2(valueB),1,Sextallp2(valueB)); &bslash;&n;    Sextallp1(valueA) &gt;&gt;= 1
DECL|macro|Sglext_xortointp1
mdefine_line|#define Sglext_xortointp1(left,right,result) Sgl_xortointp1(left,right,result)
DECL|macro|Sglext_xorfromintp1
mdefine_line|#define Sglext_xorfromintp1(left,right,result) &bslash;&n;&t;Sgl_xorfromintp1(left,right,result)
DECL|macro|Sglext_copytoint_exponentmantissa
mdefine_line|#define Sglext_copytoint_exponentmantissa(src,dest) &bslash;&n;&t;Sgl_copytoint_exponentmantissa(src,dest)
DECL|macro|Sglext_ismagnitudeless
mdefine_line|#define Sglext_ismagnitudeless(signlessleft,signlessright) &bslash;&n;&t;Sgl_ismagnitudeless(signlessleft,signlessright)
DECL|macro|Sglext_set_sign
mdefine_line|#define Sglext_set_sign(dbl_value,sign)  Sgl_set_sign(dbl_value,sign)  
DECL|macro|Sglext_clear_signexponent_set_hidden
mdefine_line|#define Sglext_clear_signexponent_set_hidden(srcdst) &bslash;&n;&t;Sgl_clear_signexponent_set_hidden(srcdst) 
DECL|macro|Sglext_clear_signexponent
mdefine_line|#define Sglext_clear_signexponent(srcdst) Sgl_clear_signexponent(srcdst) 
DECL|macro|Sglext_clear_sign
mdefine_line|#define Sglext_clear_sign(srcdst) Sgl_clear_sign(srcdst) 
DECL|macro|Sglext_isone_hidden
mdefine_line|#define Sglext_isone_hidden(dbl_value) Sgl_isone_hidden(dbl_value) 
DECL|macro|Sglext_denormalize
mdefine_line|#define Sglext_denormalize(opndp1,opndp2,exponent,is_tiny)&t;&t;&bslash;&n;  {int sticky;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    is_tiny = TRUE;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (exponent == 0 &amp;&amp; Sextallp2(opndp2)) {&t;&t;&t;&t;&bslash;&n;&t;switch (Rounding_mode()) {&t;&t;&t;&t;&t;&bslash;&n;&t;case ROUNDPLUS:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (Sgl_iszero_sign(opndp1))&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (Sgl_isone_hiddenoverflow(opndp1 + 1))&t;&bslash;&n;&t;&t;&t;&t;is_tiny = FALSE;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case ROUNDMINUS:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (Sgl_isone_sign(opndp1)) {&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (Sgl_isone_hiddenoverflow(opndp1 + 1))&t;&bslash;&n;&t;&t;&t;&t;is_tiny = FALSE;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case ROUNDNEAREST:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (Sglext_isone_highp2(opndp2) &amp;&amp;&t;&t;&t;&bslash;&n;&t;&t;    (Sglext_isone_lowp1(opndp1) || &t;&t;&t;&bslash;&n;&t;&t;     Sglext_isnotzero_low31p2(opndp2)))&t;&t;&t;&bslash;&n;&t;&t;&t;if (Sgl_isone_hiddenoverflow(opndp1 + 1))&t;&bslash;&n;&t;&t;&t;&t;is_tiny = FALSE;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    Sglext_clear_signexponent_set_hidden(opndp1);&t;&t;&t;&bslash;&n;    if (exponent &gt;= (1-DBL_P)) {&t;&t;&t;&t;&t;&bslash;&n;&t;if (exponent &gt;= -31) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    if (exponent &gt; -31) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;sticky = Sextallp2(opndp2) &lt;&lt; 31+exponent;&t;&t;&bslash;&n;&t;&t;Variable_shift_double(opndp1,opndp2,1-exponent,opndp2);&t;&bslash;&n;&t;&t;Sextallp1(opndp1) &gt;&gt;= 1-exponent;&t;&t;&t;&bslash;&n;&t;    }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;sticky = Sextallp2(opndp2);&t;&t;&t;&t;&bslash;&n;&t;&t;Sextallp2(opndp2) = Sextallp1(opndp1);&t;&t;&t;&bslash;&n;&t;&t;Sextallp1(opndp1) = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;    }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    sticky = (Sextallp1(opndp1) &lt;&lt; 31+exponent) | &t;&t;&bslash;&n;&t;&t;     Sextallp2(opndp2);&t;&t;&t;&t;&t;&bslash;&n;&t;    Sextallp2(opndp2) = Sextallp1(opndp1) &gt;&gt; -31-exponent;&t;&bslash;&n;&t;    Sextallp1(opndp1) = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;sticky = Sextallp1(opndp1) | Sextallp2(opndp2);&t;&t;&t;&bslash;&n;&t;Sglext_setzero(opndp1,opndp2);&t;&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (sticky) Sglext_setone_lowmantissap2(opndp2);&t;&t;&t;&bslash;&n;    exponent = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  }
eof
