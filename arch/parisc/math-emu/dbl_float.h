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
DECL|macro|Dbl_firstword
mdefine_line|#define Dbl_firstword(value) Dallp1(value)
DECL|macro|Dbl_secondword
mdefine_line|#define Dbl_secondword(value) Dallp2(value)
DECL|macro|Dbl_thirdword
mdefine_line|#define Dbl_thirdword(value) dummy_location
DECL|macro|Dbl_fourthword
mdefine_line|#define Dbl_fourthword(value) dummy_location
DECL|macro|Dbl_sign
mdefine_line|#define Dbl_sign(object) Dsign(object)
DECL|macro|Dbl_exponent
mdefine_line|#define Dbl_exponent(object) Dexponent(object)
DECL|macro|Dbl_signexponent
mdefine_line|#define Dbl_signexponent(object) Dsignexponent(object)
DECL|macro|Dbl_mantissap1
mdefine_line|#define Dbl_mantissap1(object) Dmantissap1(object)
DECL|macro|Dbl_mantissap2
mdefine_line|#define Dbl_mantissap2(object) Dmantissap2(object)
DECL|macro|Dbl_exponentmantissap1
mdefine_line|#define Dbl_exponentmantissap1(object) Dexponentmantissap1(object)
DECL|macro|Dbl_allp1
mdefine_line|#define Dbl_allp1(object) Dallp1(object)
DECL|macro|Dbl_allp2
mdefine_line|#define Dbl_allp2(object) Dallp2(object)
multiline_comment|/* dbl_and_signs ands the sign bits of each argument and puts the result&n; * into the first argument. dbl_or_signs ors those same sign bits */
DECL|macro|Dbl_and_signs
mdefine_line|#define Dbl_and_signs( src1dst, src2)&t;&t;&bslash;&n;    Dallp1(src1dst) = (Dallp1(src2)|~((unsigned int)1&lt;&lt;31)) &amp; Dallp1(src1dst)
DECL|macro|Dbl_or_signs
mdefine_line|#define Dbl_or_signs( src1dst, src2)&t;&t;&bslash;&n;    Dallp1(src1dst) = (Dallp1(src2)&amp;((unsigned int)1&lt;&lt;31)) | Dallp1(src1dst)
multiline_comment|/* The hidden bit is always the low bit of the exponent */
DECL|macro|Dbl_clear_exponent_set_hidden
mdefine_line|#define Dbl_clear_exponent_set_hidden(srcdst) Deposit_dexponent(srcdst,1)
DECL|macro|Dbl_clear_signexponent_set_hidden
mdefine_line|#define Dbl_clear_signexponent_set_hidden(srcdst) &bslash;&n;    Deposit_dsignexponent(srcdst,1)
DECL|macro|Dbl_clear_sign
mdefine_line|#define Dbl_clear_sign(srcdst) Dallp1(srcdst) &amp;= ~((unsigned int)1&lt;&lt;31)
DECL|macro|Dbl_clear_signexponent
mdefine_line|#define Dbl_clear_signexponent(srcdst) &bslash;&n;    Dallp1(srcdst) &amp;= Dmantissap1((unsigned int)-1)
multiline_comment|/* Exponent field for doubles has already been cleared and may be&n; * included in the shift.  Here we need to generate two double width&n; * variable shifts.  The insignificant bits can be ignored.&n; *      MTSAR f(varamount)&n; *      VSHD&t;srcdst.high,srcdst.low =&gt; srcdst.low&n; *&t;VSHD&t;0,srcdst.high =&gt; srcdst.high &n; * This is very difficult to model with C expressions since the shift amount&n; * could exceed 32.  */
multiline_comment|/* varamount must be less than 64 */
DECL|macro|Dbl_rightshift
mdefine_line|#define Dbl_rightshift(srcdstA, srcdstB, varamount)&t;&t;&t;&bslash;&n;    {if((varamount) &gt;= 32) {&t;&t;&t;&t;&t;&t;&bslash;&n;        Dallp2(srcdstB) = Dallp1(srcdstA) &gt;&gt; (varamount-32);&t;&t;&bslash;&n;        Dallp1(srcdstA)=0;&t;&t;&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else if(varamount &gt; 0) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;Variable_shift_double(Dallp1(srcdstA), Dallp2(srcdstB), &t;&bslash;&n;&t;  (varamount), Dallp2(srcdstB));&t;&t;&t;&t;&bslash;&n;&t;Dallp1(srcdstA) &gt;&gt;= varamount;&t;&t;&t;&t;&t;&bslash;&n;    } }
multiline_comment|/* varamount must be less than 64 */
DECL|macro|Dbl_rightshift_exponentmantissa
mdefine_line|#define Dbl_rightshift_exponentmantissa(srcdstA, srcdstB, varamount)&t;&bslash;&n;    {if((varamount) &gt;= 32) {&t;&t;&t;&t;&t;&t;&bslash;&n;        Dallp2(srcdstB) = Dexponentmantissap1(srcdstA) &gt;&gt; (varamount-32); &bslash;&n;&t;Dallp1(srcdstA) &amp;= ((unsigned int)1&lt;&lt;31);  /* clear expmant field */ &bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else if(varamount &gt; 0) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;Variable_shift_double(Dexponentmantissap1(srcdstA), Dallp2(srcdstB), &bslash;&n;&t;(varamount), Dallp2(srcdstB));&t;&t;&t;&t;&t;&bslash;&n;&t;Deposit_dexponentmantissap1(srcdstA,&t;&t;&t;&t;&bslash;&n;&t;    (Dexponentmantissap1(srcdstA)&gt;&gt;varamount));&t;&t;&t;&bslash;&n;    } }
multiline_comment|/* varamount must be less than 64 */
DECL|macro|Dbl_leftshift
mdefine_line|#define Dbl_leftshift(srcdstA, srcdstB, varamount)&t;&t;&t;&bslash;&n;    {if((varamount) &gt;= 32) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;Dallp1(srcdstA) = Dallp2(srcdstB) &lt;&lt; (varamount-32);&t;&t;&bslash;&n;&t;Dallp2(srcdstB)=0;&t;&t;&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((varamount) &gt; 0) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    Dallp1(srcdstA) = (Dallp1(srcdstA) &lt;&lt; (varamount)) |&t;&bslash;&n;&t;&t;(Dallp2(srcdstB) &gt;&gt; (32-(varamount)));&t;&t;&t;&bslash;&n;&t;    Dallp2(srcdstB) &lt;&lt;= varamount;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    } }
DECL|macro|Dbl_leftshiftby1_withextent
mdefine_line|#define Dbl_leftshiftby1_withextent(lefta,leftb,right,resulta,resultb)&t;&bslash;&n;    Shiftdouble(Dallp1(lefta), Dallp2(leftb), 31, Dallp1(resulta));&t;&bslash;&n;    Shiftdouble(Dallp2(leftb), Extall(right), 31, Dallp2(resultb)) 
DECL|macro|Dbl_rightshiftby1_withextent
mdefine_line|#define Dbl_rightshiftby1_withextent(leftb,right,dst)&t;&t;&bslash;&n;    Extall(dst) = (Dallp2(leftb) &lt;&lt; 31) | ((unsigned int)Extall(right) &gt;&gt; 1) | &bslash;&n;&t;&t;  Extlow(right)
DECL|macro|Dbl_arithrightshiftby1
mdefine_line|#define Dbl_arithrightshiftby1(srcdstA,srcdstB)&t;&t;&t;&bslash;&n;    Shiftdouble(Dallp1(srcdstA),Dallp2(srcdstB),1,Dallp2(srcdstB));&bslash;&n;    Dallp1(srcdstA) = (int)Dallp1(srcdstA) &gt;&gt; 1
multiline_comment|/* Sign extend the sign bit with an integer destination */
DECL|macro|Dbl_signextendedsign
mdefine_line|#define Dbl_signextendedsign(value)  Dsignedsign(value)
DECL|macro|Dbl_isone_hidden
mdefine_line|#define Dbl_isone_hidden(dbl_value) (Is_dhidden(dbl_value)!=0)
multiline_comment|/* Singles and doubles may include the sign and exponent fields.  The&n; * hidden bit and the hidden overflow must be included. */
DECL|macro|Dbl_increment
mdefine_line|#define Dbl_increment(dbl_valueA,dbl_valueB) &bslash;&n;    if( (Dallp2(dbl_valueB) += 1) == 0 )  Dallp1(dbl_valueA) += 1
DECL|macro|Dbl_increment_mantissa
mdefine_line|#define Dbl_increment_mantissa(dbl_valueA,dbl_valueB) &bslash;&n;    if( (Dmantissap2(dbl_valueB) += 1) == 0 )  &bslash;&n;    Deposit_dmantissap1(dbl_valueA,dbl_valueA+1)
DECL|macro|Dbl_decrement
mdefine_line|#define Dbl_decrement(dbl_valueA,dbl_valueB) &bslash;&n;    if( Dallp2(dbl_valueB) == 0 )  Dallp1(dbl_valueA) -= 1; &bslash;&n;    Dallp2(dbl_valueB) -= 1
DECL|macro|Dbl_isone_sign
mdefine_line|#define Dbl_isone_sign(dbl_value) (Is_dsign(dbl_value)!=0)
DECL|macro|Dbl_isone_hiddenoverflow
mdefine_line|#define Dbl_isone_hiddenoverflow(dbl_value) (Is_dhiddenoverflow(dbl_value)!=0)
DECL|macro|Dbl_isone_lowmantissap1
mdefine_line|#define Dbl_isone_lowmantissap1(dbl_valueA) (Is_dlowp1(dbl_valueA)!=0)
DECL|macro|Dbl_isone_lowmantissap2
mdefine_line|#define Dbl_isone_lowmantissap2(dbl_valueB) (Is_dlowp2(dbl_valueB)!=0)
DECL|macro|Dbl_isone_signaling
mdefine_line|#define Dbl_isone_signaling(dbl_value) (Is_dsignaling(dbl_value)!=0)
DECL|macro|Dbl_is_signalingnan
mdefine_line|#define Dbl_is_signalingnan(dbl_value) (Dsignalingnan(dbl_value)==0xfff)
DECL|macro|Dbl_isnotzero
mdefine_line|#define Dbl_isnotzero(dbl_valueA,dbl_valueB) &bslash;&n;    (Dallp1(dbl_valueA) || Dallp2(dbl_valueB))
DECL|macro|Dbl_isnotzero_hiddenhigh7mantissa
mdefine_line|#define Dbl_isnotzero_hiddenhigh7mantissa(dbl_value) &bslash;&n;    (Dhiddenhigh7mantissa(dbl_value)!=0)
DECL|macro|Dbl_isnotzero_exponent
mdefine_line|#define Dbl_isnotzero_exponent(dbl_value) (Dexponent(dbl_value)!=0)
DECL|macro|Dbl_isnotzero_mantissa
mdefine_line|#define Dbl_isnotzero_mantissa(dbl_valueA,dbl_valueB) &bslash;&n;    (Dmantissap1(dbl_valueA) || Dmantissap2(dbl_valueB))
DECL|macro|Dbl_isnotzero_mantissap1
mdefine_line|#define Dbl_isnotzero_mantissap1(dbl_valueA) (Dmantissap1(dbl_valueA)!=0)
DECL|macro|Dbl_isnotzero_mantissap2
mdefine_line|#define Dbl_isnotzero_mantissap2(dbl_valueB) (Dmantissap2(dbl_valueB)!=0)
DECL|macro|Dbl_isnotzero_exponentmantissa
mdefine_line|#define Dbl_isnotzero_exponentmantissa(dbl_valueA,dbl_valueB) &bslash;&n;    (Dexponentmantissap1(dbl_valueA) || Dmantissap2(dbl_valueB))
DECL|macro|Dbl_isnotzero_low4p2
mdefine_line|#define Dbl_isnotzero_low4p2(dbl_value) (Dlow4p2(dbl_value)!=0)
DECL|macro|Dbl_iszero
mdefine_line|#define Dbl_iszero(dbl_valueA,dbl_valueB) (Dallp1(dbl_valueA)==0 &amp;&amp; &bslash;&n;    Dallp2(dbl_valueB)==0)
DECL|macro|Dbl_iszero_allp1
mdefine_line|#define Dbl_iszero_allp1(dbl_value) (Dallp1(dbl_value)==0)
DECL|macro|Dbl_iszero_allp2
mdefine_line|#define Dbl_iszero_allp2(dbl_value) (Dallp2(dbl_value)==0)
DECL|macro|Dbl_iszero_hidden
mdefine_line|#define Dbl_iszero_hidden(dbl_value) (Is_dhidden(dbl_value)==0)
DECL|macro|Dbl_iszero_hiddenoverflow
mdefine_line|#define Dbl_iszero_hiddenoverflow(dbl_value) (Is_dhiddenoverflow(dbl_value)==0)
DECL|macro|Dbl_iszero_hiddenhigh3mantissa
mdefine_line|#define Dbl_iszero_hiddenhigh3mantissa(dbl_value) &bslash;&n;    (Dhiddenhigh3mantissa(dbl_value)==0)
DECL|macro|Dbl_iszero_hiddenhigh7mantissa
mdefine_line|#define Dbl_iszero_hiddenhigh7mantissa(dbl_value) &bslash;&n;    (Dhiddenhigh7mantissa(dbl_value)==0)
DECL|macro|Dbl_iszero_sign
mdefine_line|#define Dbl_iszero_sign(dbl_value) (Is_dsign(dbl_value)==0)
DECL|macro|Dbl_iszero_exponent
mdefine_line|#define Dbl_iszero_exponent(dbl_value) (Dexponent(dbl_value)==0)
DECL|macro|Dbl_iszero_mantissa
mdefine_line|#define Dbl_iszero_mantissa(dbl_valueA,dbl_valueB) &bslash;&n;    (Dmantissap1(dbl_valueA)==0 &amp;&amp; Dmantissap2(dbl_valueB)==0)
DECL|macro|Dbl_iszero_exponentmantissa
mdefine_line|#define Dbl_iszero_exponentmantissa(dbl_valueA,dbl_valueB) &bslash;&n;    (Dexponentmantissap1(dbl_valueA)==0 &amp;&amp; Dmantissap2(dbl_valueB)==0)
DECL|macro|Dbl_isinfinity_exponent
mdefine_line|#define Dbl_isinfinity_exponent(dbl_value)&t;&t;&bslash;&n;    (Dexponent(dbl_value)==DBL_INFINITY_EXPONENT)
DECL|macro|Dbl_isnotinfinity_exponent
mdefine_line|#define Dbl_isnotinfinity_exponent(dbl_value)&t;&t;&bslash;&n;    (Dexponent(dbl_value)!=DBL_INFINITY_EXPONENT)
DECL|macro|Dbl_isinfinity
mdefine_line|#define Dbl_isinfinity(dbl_valueA,dbl_valueB)&t;&t;&t;&bslash;&n;    (Dexponent(dbl_valueA)==DBL_INFINITY_EXPONENT &amp;&amp;&t;&bslash;&n;    Dmantissap1(dbl_valueA)==0 &amp;&amp; Dmantissap2(dbl_valueB)==0)
DECL|macro|Dbl_isnan
mdefine_line|#define Dbl_isnan(dbl_valueA,dbl_valueB)&t;&t;&bslash;&n;    (Dexponent(dbl_valueA)==DBL_INFINITY_EXPONENT &amp;&amp;&t;&bslash;&n;    (Dmantissap1(dbl_valueA)!=0 || Dmantissap2(dbl_valueB)!=0))
DECL|macro|Dbl_isnotnan
mdefine_line|#define Dbl_isnotnan(dbl_valueA,dbl_valueB)&t;&t;&bslash;&n;    (Dexponent(dbl_valueA)!=DBL_INFINITY_EXPONENT ||&t;&bslash;&n;    (Dmantissap1(dbl_valueA)==0 &amp;&amp; Dmantissap2(dbl_valueB)==0))
DECL|macro|Dbl_islessthan
mdefine_line|#define Dbl_islessthan(dbl_op1a,dbl_op1b,dbl_op2a,dbl_op2b)&t;&bslash;&n;    (Dallp1(dbl_op1a) &lt; Dallp1(dbl_op2a) ||&t;&t;&t;&bslash;&n;     (Dallp1(dbl_op1a) == Dallp1(dbl_op2a) &amp;&amp;&t;&t;&t;&bslash;&n;      Dallp2(dbl_op1b) &lt; Dallp2(dbl_op2b)))
DECL|macro|Dbl_isgreaterthan
mdefine_line|#define Dbl_isgreaterthan(dbl_op1a,dbl_op1b,dbl_op2a,dbl_op2b)&t;&bslash;&n;    (Dallp1(dbl_op1a) &gt; Dallp1(dbl_op2a) ||&t;&t;&t;&bslash;&n;     (Dallp1(dbl_op1a) == Dallp1(dbl_op2a) &amp;&amp;&t;&t;&t;&bslash;&n;      Dallp2(dbl_op1b) &gt; Dallp2(dbl_op2b)))
DECL|macro|Dbl_isnotlessthan
mdefine_line|#define Dbl_isnotlessthan(dbl_op1a,dbl_op1b,dbl_op2a,dbl_op2b)&t;&bslash;&n;    (Dallp1(dbl_op1a) &gt; Dallp1(dbl_op2a) ||&t;&t;&t;&bslash;&n;     (Dallp1(dbl_op1a) == Dallp1(dbl_op2a) &amp;&amp;&t;&t;&t;&bslash;&n;      Dallp2(dbl_op1b) &gt;= Dallp2(dbl_op2b)))
DECL|macro|Dbl_isnotgreaterthan
mdefine_line|#define Dbl_isnotgreaterthan(dbl_op1a,dbl_op1b,dbl_op2a,dbl_op2b) &bslash;&n;    (Dallp1(dbl_op1a) &lt; Dallp1(dbl_op2a) ||&t;&t;&t;&bslash;&n;     (Dallp1(dbl_op1a) == Dallp1(dbl_op2a) &amp;&amp;&t;&t;&t;&bslash;&n;      Dallp2(dbl_op1b) &lt;= Dallp2(dbl_op2b)))
DECL|macro|Dbl_isequal
mdefine_line|#define Dbl_isequal(dbl_op1a,dbl_op1b,dbl_op2a,dbl_op2b)&t;&bslash;&n;     ((Dallp1(dbl_op1a) == Dallp1(dbl_op2a)) &amp;&amp;&t;&t;&t;&bslash;&n;      (Dallp2(dbl_op1b) == Dallp2(dbl_op2b)))
DECL|macro|Dbl_leftshiftby8
mdefine_line|#define Dbl_leftshiftby8(dbl_valueA,dbl_valueB) &bslash;&n;    Shiftdouble(Dallp1(dbl_valueA),Dallp2(dbl_valueB),24,Dallp1(dbl_valueA)); &bslash;&n;    Dallp2(dbl_valueB) &lt;&lt;= 8
DECL|macro|Dbl_leftshiftby7
mdefine_line|#define Dbl_leftshiftby7(dbl_valueA,dbl_valueB) &bslash;&n;    Shiftdouble(Dallp1(dbl_valueA),Dallp2(dbl_valueB),25,Dallp1(dbl_valueA)); &bslash;&n;    Dallp2(dbl_valueB) &lt;&lt;= 7
DECL|macro|Dbl_leftshiftby4
mdefine_line|#define Dbl_leftshiftby4(dbl_valueA,dbl_valueB) &bslash;&n;    Shiftdouble(Dallp1(dbl_valueA),Dallp2(dbl_valueB),28,Dallp1(dbl_valueA)); &bslash;&n;    Dallp2(dbl_valueB) &lt;&lt;= 4
DECL|macro|Dbl_leftshiftby3
mdefine_line|#define Dbl_leftshiftby3(dbl_valueA,dbl_valueB) &bslash;&n;    Shiftdouble(Dallp1(dbl_valueA),Dallp2(dbl_valueB),29,Dallp1(dbl_valueA)); &bslash;&n;    Dallp2(dbl_valueB) &lt;&lt;= 3
DECL|macro|Dbl_leftshiftby2
mdefine_line|#define Dbl_leftshiftby2(dbl_valueA,dbl_valueB) &bslash;&n;    Shiftdouble(Dallp1(dbl_valueA),Dallp2(dbl_valueB),30,Dallp1(dbl_valueA)); &bslash;&n;    Dallp2(dbl_valueB) &lt;&lt;= 2
DECL|macro|Dbl_leftshiftby1
mdefine_line|#define Dbl_leftshiftby1(dbl_valueA,dbl_valueB) &bslash;&n;    Shiftdouble(Dallp1(dbl_valueA),Dallp2(dbl_valueB),31,Dallp1(dbl_valueA)); &bslash;&n;    Dallp2(dbl_valueB) &lt;&lt;= 1
DECL|macro|Dbl_rightshiftby8
mdefine_line|#define Dbl_rightshiftby8(dbl_valueA,dbl_valueB) &bslash;&n;    Shiftdouble(Dallp1(dbl_valueA),Dallp2(dbl_valueB),8,Dallp2(dbl_valueB)); &bslash;&n;    Dallp1(dbl_valueA) &gt;&gt;= 8
DECL|macro|Dbl_rightshiftby4
mdefine_line|#define Dbl_rightshiftby4(dbl_valueA,dbl_valueB) &bslash;&n;    Shiftdouble(Dallp1(dbl_valueA),Dallp2(dbl_valueB),4,Dallp2(dbl_valueB)); &bslash;&n;    Dallp1(dbl_valueA) &gt;&gt;= 4
DECL|macro|Dbl_rightshiftby2
mdefine_line|#define Dbl_rightshiftby2(dbl_valueA,dbl_valueB) &bslash;&n;    Shiftdouble(Dallp1(dbl_valueA),Dallp2(dbl_valueB),2,Dallp2(dbl_valueB)); &bslash;&n;    Dallp1(dbl_valueA) &gt;&gt;= 2
DECL|macro|Dbl_rightshiftby1
mdefine_line|#define Dbl_rightshiftby1(dbl_valueA,dbl_valueB) &bslash;&n;    Shiftdouble(Dallp1(dbl_valueA),Dallp2(dbl_valueB),1,Dallp2(dbl_valueB)); &bslash;&n;    Dallp1(dbl_valueA) &gt;&gt;= 1
multiline_comment|/* This magnitude comparison uses the signless first words and&n; * the regular part2 words.  The comparison is graphically:&n; *&n; *       1st greater?  -------------&n; *                                 |&n; *       1st less?-----------------+---------&n; *                                 |        |&n; *       2nd greater or equal-----&gt;|        |&n; *                               False     True&n; */
DECL|macro|Dbl_ismagnitudeless
mdefine_line|#define Dbl_ismagnitudeless(leftB,rightB,signlessleft,signlessright)&t;&bslash;&n;      ((signlessleft &lt;= signlessright) &amp;&amp;&t;&t;&t;&t;&bslash;&n;       ( (signlessleft &lt; signlessright) || (Dallp2(leftB)&lt;Dallp2(rightB)) ))
DECL|macro|Dbl_copytoint_exponentmantissap1
mdefine_line|#define Dbl_copytoint_exponentmantissap1(src,dest) &bslash;&n;    dest = Dexponentmantissap1(src)
multiline_comment|/* A quiet NaN has the high mantissa bit clear and at least on other (in this&n; * case the adjacent bit) bit set. */
DECL|macro|Dbl_set_quiet
mdefine_line|#define Dbl_set_quiet(dbl_value) Deposit_dhigh2mantissa(dbl_value,1)
DECL|macro|Dbl_set_exponent
mdefine_line|#define Dbl_set_exponent(dbl_value, exp) Deposit_dexponent(dbl_value,exp)
DECL|macro|Dbl_set_mantissa
mdefine_line|#define Dbl_set_mantissa(desta,destb,valuea,valueb)&t;&bslash;&n;    Deposit_dmantissap1(desta,valuea);&t;&t;&t;&bslash;&n;    Dmantissap2(destb) = Dmantissap2(valueb)
DECL|macro|Dbl_set_mantissap1
mdefine_line|#define Dbl_set_mantissap1(desta,valuea)&t;&t;&bslash;&n;    Deposit_dmantissap1(desta,valuea)
DECL|macro|Dbl_set_mantissap2
mdefine_line|#define Dbl_set_mantissap2(destb,valueb)&t;&t;&bslash;&n;    Dmantissap2(destb) = Dmantissap2(valueb)
DECL|macro|Dbl_set_exponentmantissa
mdefine_line|#define Dbl_set_exponentmantissa(desta,destb,valuea,valueb)&t;&bslash;&n;    Deposit_dexponentmantissap1(desta,valuea);&t;&t;&t;&bslash;&n;    Dmantissap2(destb) = Dmantissap2(valueb)
DECL|macro|Dbl_set_exponentmantissap1
mdefine_line|#define Dbl_set_exponentmantissap1(dest,value)&t;&t;&t;&bslash;&n;    Deposit_dexponentmantissap1(dest,value)
DECL|macro|Dbl_copyfromptr
mdefine_line|#define Dbl_copyfromptr(src,desta,destb) &bslash;&n;    Dallp1(desta) = src-&gt;wd0;&t;&t;&bslash;&n;    Dallp2(destb) = src-&gt;wd1 
DECL|macro|Dbl_copytoptr
mdefine_line|#define Dbl_copytoptr(srca,srcb,dest)&t;&bslash;&n;    dest-&gt;wd0 = Dallp1(srca);&t;&t;&bslash;&n;    dest-&gt;wd1 = Dallp2(srcb)
multiline_comment|/*  An infinity is represented with the max exponent and a zero mantissa */
DECL|macro|Dbl_setinfinity_exponent
mdefine_line|#define Dbl_setinfinity_exponent(dbl_value) &bslash;&n;    Deposit_dexponent(dbl_value,DBL_INFINITY_EXPONENT)
DECL|macro|Dbl_setinfinity_exponentmantissa
mdefine_line|#define Dbl_setinfinity_exponentmantissa(dbl_valueA,dbl_valueB)&t;&bslash;&n;    Deposit_dexponentmantissap1(dbl_valueA, &t;&t;&t;&bslash;&n;    (DBL_INFINITY_EXPONENT &lt;&lt; (32-(1+DBL_EXP_LENGTH))));&t;&bslash;&n;    Dmantissap2(dbl_valueB) = 0
DECL|macro|Dbl_setinfinitypositive
mdefine_line|#define Dbl_setinfinitypositive(dbl_valueA,dbl_valueB)&t;&t;&bslash;&n;    Dallp1(dbl_valueA) &t;&t;&t;&t;&t;&t;&bslash;&n;        = (DBL_INFINITY_EXPONENT &lt;&lt; (32-(1+DBL_EXP_LENGTH)));&t;&bslash;&n;    Dmantissap2(dbl_valueB) = 0
DECL|macro|Dbl_setinfinitynegative
mdefine_line|#define Dbl_setinfinitynegative(dbl_valueA,dbl_valueB)&t;&t;&bslash;&n;    Dallp1(dbl_valueA) = ((unsigned int)1&lt;&lt;31) |&t;&t;&bslash;&n;         (DBL_INFINITY_EXPONENT &lt;&lt; (32-(1+DBL_EXP_LENGTH)));&t;&bslash;&n;    Dmantissap2(dbl_valueB) = 0
DECL|macro|Dbl_setinfinity
mdefine_line|#define Dbl_setinfinity(dbl_valueA,dbl_valueB,sign)&t;&t;&bslash;&n;    Dallp1(dbl_valueA) = ((unsigned int)sign &lt;&lt; 31) | &t;&t;&bslash;&n;&t;(DBL_INFINITY_EXPONENT &lt;&lt; (32-(1+DBL_EXP_LENGTH)));&t;&bslash;&n;    Dmantissap2(dbl_valueB) = 0
DECL|macro|Dbl_sethigh4bits
mdefine_line|#define Dbl_sethigh4bits(dbl_value, extsign) Deposit_dhigh4p1(dbl_value,extsign)
DECL|macro|Dbl_set_sign
mdefine_line|#define Dbl_set_sign(dbl_value,sign) Deposit_dsign(dbl_value,sign)
DECL|macro|Dbl_invert_sign
mdefine_line|#define Dbl_invert_sign(dbl_value) Deposit_dsign(dbl_value,~Dsign(dbl_value))
DECL|macro|Dbl_setone_sign
mdefine_line|#define Dbl_setone_sign(dbl_value) Deposit_dsign(dbl_value,1)
DECL|macro|Dbl_setone_lowmantissap2
mdefine_line|#define Dbl_setone_lowmantissap2(dbl_value) Deposit_dlowp2(dbl_value,1)
DECL|macro|Dbl_setzero_sign
mdefine_line|#define Dbl_setzero_sign(dbl_value) Dallp1(dbl_value) &amp;= 0x7fffffff
DECL|macro|Dbl_setzero_exponent
mdefine_line|#define Dbl_setzero_exponent(dbl_value) &t;&t;&bslash;&n;    Dallp1(dbl_value) &amp;= 0x800fffff
DECL|macro|Dbl_setzero_mantissa
mdefine_line|#define Dbl_setzero_mantissa(dbl_valueA,dbl_valueB)&t;&bslash;&n;    Dallp1(dbl_valueA) &amp;= 0xfff00000; &t;&t;&t;&bslash;&n;    Dallp2(dbl_valueB) = 0
DECL|macro|Dbl_setzero_mantissap1
mdefine_line|#define Dbl_setzero_mantissap1(dbl_value) Dallp1(dbl_value) &amp;= 0xfff00000
DECL|macro|Dbl_setzero_mantissap2
mdefine_line|#define Dbl_setzero_mantissap2(dbl_value) Dallp2(dbl_value) = 0
DECL|macro|Dbl_setzero_exponentmantissa
mdefine_line|#define Dbl_setzero_exponentmantissa(dbl_valueA,dbl_valueB)&t;&bslash;&n;    Dallp1(dbl_valueA) &amp;= 0x80000000;&t;&t;&bslash;&n;    Dallp2(dbl_valueB) = 0
DECL|macro|Dbl_setzero_exponentmantissap1
mdefine_line|#define Dbl_setzero_exponentmantissap1(dbl_valueA)&t;&bslash;&n;    Dallp1(dbl_valueA) &amp;= 0x80000000
DECL|macro|Dbl_setzero
mdefine_line|#define Dbl_setzero(dbl_valueA,dbl_valueB) &bslash;&n;    Dallp1(dbl_valueA) = 0; Dallp2(dbl_valueB) = 0
DECL|macro|Dbl_setzerop1
mdefine_line|#define Dbl_setzerop1(dbl_value) Dallp1(dbl_value) = 0
DECL|macro|Dbl_setzerop2
mdefine_line|#define Dbl_setzerop2(dbl_value) Dallp2(dbl_value) = 0
DECL|macro|Dbl_setnegativezero
mdefine_line|#define Dbl_setnegativezero(dbl_value) &bslash;&n;    Dallp1(dbl_value) = (unsigned int)1 &lt;&lt; 31; Dallp2(dbl_value) = 0
DECL|macro|Dbl_setnegativezerop1
mdefine_line|#define Dbl_setnegativezerop1(dbl_value) Dallp1(dbl_value) = (unsigned int)1&lt;&lt;31
multiline_comment|/* Use the following macro for both overflow &amp; underflow conditions */
DECL|macro|ovfl
mdefine_line|#define ovfl -
DECL|macro|unfl
mdefine_line|#define unfl +
DECL|macro|Dbl_setwrapped_exponent
mdefine_line|#define Dbl_setwrapped_exponent(dbl_value,exponent,op) &bslash;&n;    Deposit_dexponent(dbl_value,(exponent op DBL_WRAP))
DECL|macro|Dbl_setlargestpositive
mdefine_line|#define Dbl_setlargestpositive(dbl_valueA,dbl_valueB) &t;&t;&t;&bslash;&n;    Dallp1(dbl_valueA) = ((DBL_EMAX+DBL_BIAS) &lt;&lt; (32-(1+DBL_EXP_LENGTH))) &bslash;&n;&t;&t;&t;| ((1&lt;&lt;(32-(1+DBL_EXP_LENGTH))) - 1 );&t;&t;&bslash;&n;    Dallp2(dbl_valueB) = 0xFFFFFFFF
DECL|macro|Dbl_setlargestnegative
mdefine_line|#define Dbl_setlargestnegative(dbl_valueA,dbl_valueB) &t;&t;&t;&bslash;&n;    Dallp1(dbl_valueA) = ((DBL_EMAX+DBL_BIAS) &lt;&lt; (32-(1+DBL_EXP_LENGTH))) &bslash;&n;&t;&t;&t;| ((1&lt;&lt;(32-(1+DBL_EXP_LENGTH))) - 1 )&t;&t;&bslash;&n;&t;&t;&t;| ((unsigned int)1&lt;&lt;31);&t;&t;&t;&bslash;&n;    Dallp2(dbl_valueB) = 0xFFFFFFFF
DECL|macro|Dbl_setlargest_exponentmantissa
mdefine_line|#define Dbl_setlargest_exponentmantissa(dbl_valueA,dbl_valueB)&t;&t;&bslash;&n;    Deposit_dexponentmantissap1(dbl_valueA,&t;&t;&t;&t;&bslash;&n;&t;(((DBL_EMAX+DBL_BIAS) &lt;&lt; (32-(1+DBL_EXP_LENGTH)))&t;&t;&bslash;&n;&t;&t;&t;| ((1&lt;&lt;(32-(1+DBL_EXP_LENGTH))) - 1 )));&t;&bslash;&n;    Dallp2(dbl_valueB) = 0xFFFFFFFF
DECL|macro|Dbl_setnegativeinfinity
mdefine_line|#define Dbl_setnegativeinfinity(dbl_valueA,dbl_valueB) &t;&t;&t;&bslash;&n;    Dallp1(dbl_valueA) = ((1&lt;&lt;DBL_EXP_LENGTH) | DBL_INFINITY_EXPONENT) &t;&bslash;&n;&t;&t;&t; &lt;&lt; (32-(1+DBL_EXP_LENGTH)) ; &t;&t;&t;&bslash;&n;    Dallp2(dbl_valueB) = 0
DECL|macro|Dbl_setlargest
mdefine_line|#define Dbl_setlargest(dbl_valueA,dbl_valueB,sign)&t;&t;&t;&bslash;&n;    Dallp1(dbl_valueA) = ((unsigned int)sign &lt;&lt; 31) |&t;&t;&t;&bslash;&n;         ((DBL_EMAX+DBL_BIAS) &lt;&lt; (32-(1+DBL_EXP_LENGTH))) |&t; &t;&bslash;&n;&t; ((1 &lt;&lt; (32-(1+DBL_EXP_LENGTH))) - 1 );&t;&t;&t;&t;&bslash;&n;    Dallp2(dbl_valueB) = 0xFFFFFFFF
multiline_comment|/* The high bit is always zero so arithmetic or logical shifts will work. */
DECL|macro|Dbl_right_align
mdefine_line|#define Dbl_right_align(srcdstA,srcdstB,shift,extent)&t;&t;&t;&bslash;&n;    if( shift &gt;= 32 ) &t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* Big shift requires examining the portion shift off &t;&t;&bslash;&n;&t;the end to properly set inexact.  */&t;&t;&t;&t;&bslash;&n;&t;if(shift &lt; 64)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    if(shift &gt; 32)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;        Variable_shift_double(Dallp1(srcdstA),Dallp2(srcdstB),&t;&bslash;&n;&t;&t; shift-32, Extall(extent));&t;&t;&t;&t;&bslash;&n;&t;        if(Dallp2(srcdstB) &lt;&lt; 64 - (shift)) Ext_setone_low(extent); &bslash;&n;&t;        }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    else Extall(extent) = Dallp2(srcdstB);&t;&t;&t;&bslash;&n;&t;    Dallp2(srcdstB) = Dallp1(srcdstA) &gt;&gt; (shift - 32);&t;&t;&bslash;&n;&t;    }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    Extall(extent) = Dallp1(srcdstA);&t;&t;&t;&t;&bslash;&n;&t;    if(Dallp2(srcdstB)) Ext_setone_low(extent);&t;&t;&t;&bslash;&n;&t;    Dallp2(srcdstB) = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;    }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;Dallp1(srcdstA) = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* Small alignment is simpler.  Extension is easily set. */&t;&bslash;&n;&t;if (shift &gt; 0)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    Extall(extent) = Dallp2(srcdstB) &lt;&lt; 32 - (shift);&t;&t;&bslash;&n;&t;    Variable_shift_double(Dallp1(srcdstA),Dallp2(srcdstB),shift, &bslash;&n;&t;     Dallp2(srcdstB));&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    Dallp1(srcdstA) &gt;&gt;= shift;&t;&t;&t;&t;&t;&bslash;&n;&t;    }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;else Extall(extent) = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;}
multiline_comment|/* &n; * Here we need to shift the result right to correct for an overshift&n; * (due to the exponent becoming negative) during normalization.&n; */
DECL|macro|Dbl_fix_overshift
mdefine_line|#define Dbl_fix_overshift(srcdstA,srcdstB,shift,extent)&t;&t;&t;&bslash;&n;&t;    Extall(extent) = Dallp2(srcdstB) &lt;&lt; 32 - (shift);&t;&t;&bslash;&n;&t;    Dallp2(srcdstB) = (Dallp1(srcdstA) &lt;&lt; 32 - (shift)) |&t;&bslash;&n;&t;&t;(Dallp2(srcdstB) &gt;&gt; (shift));&t;&t;&t;&t;&bslash;&n;&t;    Dallp1(srcdstA) = Dallp1(srcdstA) &gt;&gt; shift
DECL|macro|Dbl_hiddenhigh3mantissa
mdefine_line|#define Dbl_hiddenhigh3mantissa(dbl_value) Dhiddenhigh3mantissa(dbl_value)
DECL|macro|Dbl_hidden
mdefine_line|#define Dbl_hidden(dbl_value) Dhidden(dbl_value)
DECL|macro|Dbl_lowmantissap2
mdefine_line|#define Dbl_lowmantissap2(dbl_value) Dlowp2(dbl_value)
multiline_comment|/* The left argument is never smaller than the right argument */
DECL|macro|Dbl_subtract
mdefine_line|#define Dbl_subtract(lefta,leftb,righta,rightb,resulta,resultb)&t;&t;&t;&bslash;&n;    if( Dallp2(rightb) &gt; Dallp2(leftb) ) Dallp1(lefta)--;&t;&bslash;&n;    Dallp2(resultb) = Dallp2(leftb) - Dallp2(rightb);&t;&t;&bslash;&n;    Dallp1(resulta) = Dallp1(lefta) - Dallp1(righta)
multiline_comment|/* Subtract right augmented with extension from left augmented with zeros and&n; * store into result and extension. */
DECL|macro|Dbl_subtract_withextension
mdefine_line|#define Dbl_subtract_withextension(lefta,leftb,righta,rightb,extent,resulta,resultb)&t;&bslash;&n;    Dbl_subtract(lefta,leftb,righta,rightb,resulta,resultb);&t;&t;&bslash;&n;    if( (Extall(extent) = 0-Extall(extent)) )&t;&t;&t;&t;&bslash;&n;        {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        if((Dallp2(resultb)--) == 0) Dallp1(resulta)--;&t;&t;&t;&bslash;&n;        }
DECL|macro|Dbl_addition
mdefine_line|#define Dbl_addition(lefta,leftb,righta,rightb,resulta,resultb)&t;&t;&bslash;&n;    /* If the sum of the low words is less than either source, then&t;&bslash;&n;     * an overflow into the next word occurred. */&t;&t;&t;&bslash;&n;    Dallp1(resulta) = Dallp1(lefta) + Dallp1(righta);&t;&t;&t;&bslash;&n;    if((Dallp2(resultb) = Dallp2(leftb) + Dallp2(rightb)) &lt; Dallp2(rightb)) &bslash;&n;&t;Dallp1(resulta)++
DECL|macro|Dbl_xortointp1
mdefine_line|#define Dbl_xortointp1(left,right,result)&t;&t;&t;&bslash;&n;    result = Dallp1(left) XOR Dallp1(right)
DECL|macro|Dbl_xorfromintp1
mdefine_line|#define Dbl_xorfromintp1(left,right,result)&t;&t;&t;&bslash;&n;    Dallp1(result) = left XOR Dallp1(right)
DECL|macro|Dbl_swap_lower
mdefine_line|#define Dbl_swap_lower(left,right)&t;&t;&t;&t;&bslash;&n;    Dallp2(left)  = Dallp2(left) XOR Dallp2(right);&t;&t;&bslash;&n;    Dallp2(right) = Dallp2(left) XOR Dallp2(right);&t;&t;&bslash;&n;    Dallp2(left)  = Dallp2(left) XOR Dallp2(right)
multiline_comment|/* Need to Initialize */
DECL|macro|Dbl_makequietnan
mdefine_line|#define Dbl_makequietnan(desta,destb)&t;&t;&t;&t;&t;&bslash;&n;    Dallp1(desta) = ((DBL_EMAX+DBL_BIAS)+1)&lt;&lt; (32-(1+DBL_EXP_LENGTH))&t;&bslash;&n;                 | (1&lt;&lt;(32-(1+DBL_EXP_LENGTH+2)));&t;&t;&t;&bslash;&n;    Dallp2(destb) = 0
DECL|macro|Dbl_makesignalingnan
mdefine_line|#define Dbl_makesignalingnan(desta,destb)&t;&t;&t;&t;&bslash;&n;    Dallp1(desta) = ((DBL_EMAX+DBL_BIAS)+1)&lt;&lt; (32-(1+DBL_EXP_LENGTH))&t;&bslash;&n;                 | (1&lt;&lt;(32-(1+DBL_EXP_LENGTH+1)));&t;&t;&t;&bslash;&n;    Dallp2(destb) = 0
DECL|macro|Dbl_normalize
mdefine_line|#define Dbl_normalize(dbl_opndA,dbl_opndB,exponent)&t;&t;&t;&bslash;&n;&t;while(Dbl_iszero_hiddenhigh7mantissa(dbl_opndA)) {&t;&t;&bslash;&n;&t;&t;Dbl_leftshiftby8(dbl_opndA,dbl_opndB);&t;&t;&t;&bslash;&n;&t;&t;exponent -= 8;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if(Dbl_iszero_hiddenhigh3mantissa(dbl_opndA)) {&t;&t;&t;&bslash;&n;&t;&t;Dbl_leftshiftby4(dbl_opndA,dbl_opndB);&t;&t;&t;&bslash;&n;&t;&t;exponent -= 4;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;while(Dbl_iszero_hidden(dbl_opndA)) {&t;&t;&t;&t;&bslash;&n;&t;&t;Dbl_leftshiftby1(dbl_opndA,dbl_opndB);&t;&t;&t;&bslash;&n;&t;&t;exponent -= 1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}
DECL|macro|Twoword_add
mdefine_line|#define Twoword_add(src1dstA,src1dstB,src2A,src2B)&t;&t;&bslash;&n;&t;/* &t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; * want this macro to generate:&t;&t;&t;&t;&bslash;&n;&t; *&t;ADD&t;src1dstB,src2B,src1dstB;&t;&t;&bslash;&n;&t; *&t;ADDC&t;src1dstA,src2A,src1dstA;&t;&t;&bslash;&n;&t; */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((src1dstB) + (src2B) &lt; (src1dstB)) Dallp1(src1dstA)++; &bslash;&n;&t;Dallp1(src1dstA) += (src2A);&t;&t;&t;&t;&bslash;&n;&t;Dallp2(src1dstB) += (src2B)
DECL|macro|Twoword_subtract
mdefine_line|#define Twoword_subtract(src1dstA,src1dstB,src2A,src2B)&t;&t;&bslash;&n;&t;/* &t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; * want this macro to generate:&t;&t;&t;&t;&bslash;&n;&t; *&t;SUB&t;src1dstB,src2B,src1dstB;&t;&t;&bslash;&n;&t; *&t;SUBB&t;src1dstA,src2A,src1dstA;&t;&t;&bslash;&n;&t; */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((src1dstB) &lt; (src2B)) Dallp1(src1dstA)--;&t;&t;&bslash;&n;&t;Dallp1(src1dstA) -= (src2A);&t;&t;&t;&t;&bslash;&n;&t;Dallp2(src1dstB) -= (src2B)
DECL|macro|Dbl_setoverflow
mdefine_line|#define Dbl_setoverflow(resultA,resultB)&t;&t;&t;&t;&bslash;&n;&t;/* set result to infinity or largest number */&t;&t;&t;&bslash;&n;&t;switch (Rounding_mode()) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case ROUNDPLUS:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (Dbl_isone_sign(resultA)) {&t;&t;&t;&bslash;&n;&t;&t;&t;&t;Dbl_setlargestnegative(resultA,resultB); &bslash;&n;&t;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;else {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;Dbl_setinfinitypositive(resultA,resultB); &bslash;&n;&t;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case ROUNDMINUS:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (Dbl_iszero_sign(resultA)) {&t;&t;&t;&bslash;&n;&t;&t;&t;&t;Dbl_setlargestpositive(resultA,resultB); &bslash;&n;&t;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;else {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;Dbl_setinfinitynegative(resultA,resultB); &bslash;&n;&t;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case ROUNDNEAREST:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;Dbl_setinfinity_exponentmantissa(resultA,resultB); &bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case ROUNDZERO:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;Dbl_setlargest_exponentmantissa(resultA,resultB); &bslash;&n;&t;}
DECL|macro|Dbl_denormalize
mdefine_line|#define Dbl_denormalize(opndp1,opndp2,exponent,guard,sticky,inexact)&t;&bslash;&n;    Dbl_clear_signexponent_set_hidden(opndp1);&t;&t;&t;&t;&bslash;&n;    if (exponent &gt;= (1-DBL_P)) {&t;&t;&t;&t;&t;&bslash;&n;&t;if (exponent &gt;= -31) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    guard = (Dallp2(opndp2) &gt;&gt; -exponent) &amp; 1;&t;&t;&t;&bslash;&n;&t;    if (exponent &lt; 0) sticky |= Dallp2(opndp2) &lt;&lt; (32+exponent); &bslash;&n;&t;    if (exponent &gt; -31) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;Variable_shift_double(opndp1,opndp2,1-exponent,opndp2);&t;&bslash;&n;&t;&t;Dallp1(opndp1) &gt;&gt;= 1-exponent;&t;&t;&t;&t;&bslash;&n;&t;    }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;Dallp2(opndp2) = Dallp1(opndp1);&t;&t;&t;&bslash;&n;&t;&t;Dbl_setzerop1(opndp1);&t;&t;&t;&t;&t;&bslash;&n;&t;    }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    guard = (Dallp1(opndp1) &gt;&gt; -32-exponent) &amp; 1;&t;&t;&bslash;&n;&t;    if (exponent == -32) sticky |= Dallp2(opndp2);&t;&t;&bslash;&n;&t;    else sticky |= (Dallp2(opndp2) | Dallp1(opndp1) &lt;&lt; 64+exponent); &bslash;&n;&t;    Dallp2(opndp2) = Dallp1(opndp1) &gt;&gt; -31-exponent;&t;&t;&bslash;&n;&t;    Dbl_setzerop1(opndp1);&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;inexact = guard | sticky;&t;&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;guard = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;sticky |= (Dallp1(opndp1) | Dallp2(opndp2));&t;&t;&t;&bslash;&n;&t;Dbl_setzero(opndp1,opndp2);&t;&t;&t;&t;&t;&bslash;&n;&t;inexact = sticky;&t;&t;&t;&t;&t;&t;&bslash;&n;    }
multiline_comment|/* &n; * The fused multiply add instructions requires a double extended format,&n; * with 106 bits of mantissa.&n; */
DECL|macro|DBLEXT_THRESHOLD
mdefine_line|#define DBLEXT_THRESHOLD 106
DECL|macro|Dblext_setzero
mdefine_line|#define Dblext_setzero(valA,valB,valC,valD)&t;&bslash;&n;    Dextallp1(valA) = 0; Dextallp2(valB) = 0;&t;&bslash;&n;    Dextallp3(valC) = 0; Dextallp4(valD) = 0
DECL|macro|Dblext_isnotzero_mantissap3
mdefine_line|#define Dblext_isnotzero_mantissap3(valC) (Dextallp3(valC)!=0)
DECL|macro|Dblext_isnotzero_mantissap4
mdefine_line|#define Dblext_isnotzero_mantissap4(valD) (Dextallp3(valD)!=0)
DECL|macro|Dblext_isone_lowp2
mdefine_line|#define Dblext_isone_lowp2(val) (Dextlowp2(val)!=0)
DECL|macro|Dblext_isone_highp3
mdefine_line|#define Dblext_isone_highp3(val) (Dexthighp3(val)!=0)
DECL|macro|Dblext_isnotzero_low31p3
mdefine_line|#define Dblext_isnotzero_low31p3(val) (Dextlow31p3(val)!=0)
DECL|macro|Dblext_iszero
mdefine_line|#define Dblext_iszero(valA,valB,valC,valD) (Dextallp1(valA)==0 &amp;&amp; &bslash;&n;    Dextallp2(valB)==0 &amp;&amp; Dextallp3(valC)==0 &amp;&amp; Dextallp4(valD)==0)
DECL|macro|Dblext_copy
mdefine_line|#define Dblext_copy(srca,srcb,srcc,srcd,desta,destb,destc,destd) &bslash;&n;    Dextallp1(desta) = Dextallp4(srca);&t;&bslash;&n;    Dextallp2(destb) = Dextallp4(srcb);&t;&bslash;&n;    Dextallp3(destc) = Dextallp4(srcc);&t;&bslash;&n;    Dextallp4(destd) = Dextallp4(srcd)
DECL|macro|Dblext_swap_lower
mdefine_line|#define Dblext_swap_lower(leftp2,leftp3,leftp4,rightp2,rightp3,rightp4)  &bslash;&n;    Dextallp2(leftp2)  = Dextallp2(leftp2) XOR Dextallp2(rightp2);  &bslash;&n;    Dextallp2(rightp2) = Dextallp2(leftp2) XOR Dextallp2(rightp2);  &bslash;&n;    Dextallp2(leftp2)  = Dextallp2(leftp2) XOR Dextallp2(rightp2);  &bslash;&n;    Dextallp3(leftp3)  = Dextallp3(leftp3) XOR Dextallp3(rightp3);  &bslash;&n;    Dextallp3(rightp3) = Dextallp3(leftp3) XOR Dextallp3(rightp3);  &bslash;&n;    Dextallp3(leftp3)  = Dextallp3(leftp3) XOR Dextallp3(rightp3);  &bslash;&n;    Dextallp4(leftp4)  = Dextallp4(leftp4) XOR Dextallp4(rightp4);  &bslash;&n;    Dextallp4(rightp4) = Dextallp4(leftp4) XOR Dextallp4(rightp4);  &bslash;&n;    Dextallp4(leftp4)  = Dextallp4(leftp4) XOR Dextallp4(rightp4)
DECL|macro|Dblext_setone_lowmantissap4
mdefine_line|#define Dblext_setone_lowmantissap4(dbl_value) Deposit_dextlowp4(dbl_value,1)
multiline_comment|/* The high bit is always zero so arithmetic or logical shifts will work. */
DECL|macro|Dblext_right_align
mdefine_line|#define Dblext_right_align(srcdstA,srcdstB,srcdstC,srcdstD,shift) &bslash;&n;  {int shiftamt, sticky;&t;&t;&t;&t;&t;&t;&bslash;&n;    shiftamt = shift % 32;&t;&t;&t;&t;&t;&t;&bslash;&n;    sticky = 0;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    switch (shift/32) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;     case 0: if (shiftamt &gt; 0) {&t;&t;&t;&t;&t;&bslash;&n;&t;        sticky = Dextallp4(srcdstD) &lt;&lt; 32 - (shiftamt); &t;&bslash;&n;                Variable_shift_double(Dextallp3(srcdstC),&t;&t;&bslash;&n;&t;&t; Dextallp4(srcdstD),shiftamt,Dextallp4(srcdstD));&t;&bslash;&n;                Variable_shift_double(Dextallp2(srcdstB),&t;&t;&bslash;&n;&t;&t; Dextallp3(srcdstC),shiftamt,Dextallp3(srcdstC));&t;&bslash;&n;                Variable_shift_double(Dextallp1(srcdstA),&t;&t;&bslash;&n;&t;&t; Dextallp2(srcdstB),shiftamt,Dextallp2(srcdstB));&t;&bslash;&n;&t;        Dextallp1(srcdstA) &gt;&gt;= shiftamt;&t;&t;&t;&bslash;&n;&t;     }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;     break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;     case 1: if (shiftamt &gt; 0) {&t;&t;&t;&t;&t;&bslash;&n;                sticky = (Dextallp3(srcdstC) &lt;&lt; 31 - shiftamt) |&t;&bslash;&n;&t;&t;&t; Dextallp4(srcdstD);&t;&t;&t;&t;&bslash;&n;                Variable_shift_double(Dextallp2(srcdstB),&t;&t;&bslash;&n;&t;&t; Dextallp3(srcdstC),shiftamt,Dextallp4(srcdstD));&t;&bslash;&n;                Variable_shift_double(Dextallp1(srcdstA),&t;&t;&bslash;&n;&t;&t; Dextallp2(srcdstB),shiftamt,Dextallp3(srcdstC));&t;&bslash;&n;&t;     }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;     else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;sticky = Dextallp4(srcdstD);&t;&t;&t;&t;&bslash;&n;&t;&t;Dextallp4(srcdstD) = Dextallp3(srcdstC);&t;&t;&bslash;&n;&t;&t;Dextallp3(srcdstC) = Dextallp2(srcdstB);&t;&t;&bslash;&n;&t;     }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;     Dextallp2(srcdstB) = Dextallp1(srcdstA) &gt;&gt; shiftamt;&t;&bslash;&n;&t;     Dextallp1(srcdstA) = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;     break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;     case 2: if (shiftamt &gt; 0) {&t;&t;&t;&t;&t;&bslash;&n;                sticky = (Dextallp2(srcdstB) &lt;&lt; 31 - shiftamt) |&t;&bslash;&n;&t;&t;&t; Dextallp3(srcdstC) | Dextallp4(srcdstD);&t;&bslash;&n;                Variable_shift_double(Dextallp1(srcdstA),&t;&t;&bslash;&n;&t;&t; Dextallp2(srcdstB),shiftamt,Dextallp4(srcdstD));&t;&bslash;&n;&t;     }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;     else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;sticky = Dextallp3(srcdstC) | Dextallp4(srcdstD);&t;&bslash;&n;&t;&t;Dextallp4(srcdstD) = Dextallp2(srcdstB);&t;&t;&bslash;&n;&t;     }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;     Dextallp3(srcdstC) = Dextallp1(srcdstA) &gt;&gt; shiftamt;&t;&bslash;&n;&t;     Dextallp1(srcdstA) = Dextallp2(srcdstB) = 0;&t;&t;&bslash;&n;&t;     break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;     case 3: if (shiftamt &gt; 0) {&t;&t;&t;&t;&t;&bslash;&n;                sticky = (Dextallp1(srcdstA) &lt;&lt; 31 - shiftamt) |&t;&bslash;&n;&t;&t;&t; Dextallp2(srcdstB) | Dextallp3(srcdstC) |&t;&bslash;&n;&t;&t;&t; Dextallp4(srcdstD);&t;&t;&t;&t;&bslash;&n;&t;     }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;     else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;sticky = Dextallp2(srcdstB) | Dextallp3(srcdstC) |&t;&bslash;&n;&t;&t;    Dextallp4(srcdstD);&t;&t;&t;&t;&t;&bslash;&n;&t;     }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;     Dextallp4(srcdstD) = Dextallp1(srcdstA) &gt;&gt; shiftamt;&t;&bslash;&n;&t;     Dextallp1(srcdstA) = Dextallp2(srcdstB) = 0;&t;&t;&bslash;&n;&t;     Dextallp3(srcdstC) = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;     break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (sticky) Dblext_setone_lowmantissap4(srcdstD);&t;&t;&t;&bslash;&n;  }
multiline_comment|/* The left argument is never smaller than the right argument */
DECL|macro|Dblext_subtract
mdefine_line|#define Dblext_subtract(lefta,leftb,leftc,leftd,righta,rightb,rightc,rightd,resulta,resultb,resultc,resultd) &bslash;&n;    if( Dextallp4(rightd) &gt; Dextallp4(leftd) ) &t;&t;&t;&bslash;&n;&t;if( (Dextallp3(leftc)--) == 0)&t;&t;&t;&t;&bslash;&n;&t;    if( (Dextallp2(leftb)--) == 0) Dextallp1(lefta)--;&t;&bslash;&n;    Dextallp4(resultd) = Dextallp4(leftd) - Dextallp4(rightd);&t;&bslash;&n;    if( Dextallp3(rightc) &gt; Dextallp3(leftc) ) &t;&t;&t;&bslash;&n;        if( (Dextallp2(leftb)--) == 0) Dextallp1(lefta)--;&t;&bslash;&n;    Dextallp3(resultc) = Dextallp3(leftc) - Dextallp3(rightc);&t;&bslash;&n;    if( Dextallp2(rightb) &gt; Dextallp2(leftb) ) Dextallp1(lefta)--; &bslash;&n;    Dextallp2(resultb) = Dextallp2(leftb) - Dextallp2(rightb);&t;&bslash;&n;    Dextallp1(resulta) = Dextallp1(lefta) - Dextallp1(righta)
DECL|macro|Dblext_addition
mdefine_line|#define Dblext_addition(lefta,leftb,leftc,leftd,righta,rightb,rightc,rightd,resulta,resultb,resultc,resultd) &bslash;&n;    /* If the sum of the low words is less than either source, then &bslash;&n;     * an overflow into the next word occurred. */ &bslash;&n;    if ((Dextallp4(resultd) = Dextallp4(leftd)+Dextallp4(rightd)) &lt; &bslash;&n;&t;Dextallp4(rightd)) &bslash;&n;&t;if((Dextallp3(resultc) = Dextallp3(leftc)+Dextallp3(rightc)+1) &lt;= &bslash;&n;&t;    Dextallp3(rightc)) &bslash;&n;&t;    if((Dextallp2(resultb) = Dextallp2(leftb)+Dextallp2(rightb)+1) &bslash;&n;&t;        &lt;= Dextallp2(rightb))  &bslash;&n;&t;&t;    Dextallp1(resulta) = Dextallp1(lefta)+Dextallp1(righta)+1; &bslash;&n;&t;    else Dextallp1(resulta) = Dextallp1(lefta)+Dextallp1(righta); &bslash;&n;&t;else &bslash;&n;&t;    if ((Dextallp2(resultb) = Dextallp2(leftb)+Dextallp2(rightb)) &lt; &bslash;&n;&t;        Dextallp2(rightb)) &bslash;&n;&t;&t;    Dextallp1(resulta) = Dextallp1(lefta)+Dextallp1(righta)+1; &bslash;&n;&t;    else Dextallp1(resulta) = Dextallp1(lefta)+Dextallp1(righta); &bslash;&n;    else &bslash;&n;&t;if ((Dextallp3(resultc) = Dextallp3(leftc)+Dextallp3(rightc)) &lt; &bslash;&n;&t;    Dextallp3(rightc))  &bslash;&n;&t;    if ((Dextallp2(resultb) = Dextallp2(leftb)+Dextallp2(rightb)+1) &bslash;&n;&t;        &lt;= Dextallp2(rightb)) &bslash;&n;&t;&t;    Dextallp1(resulta) = Dextallp1(lefta)+Dextallp1(righta)+1; &bslash;&n;&t;    else Dextallp1(resulta) = Dextallp1(lefta)+Dextallp1(righta); &bslash;&n;&t;else &bslash;&n;&t;    if ((Dextallp2(resultb) = Dextallp2(leftb)+Dextallp2(rightb)) &lt; &bslash;&n;&t;        Dextallp2(rightb)) &bslash;&n;&t;&t;    Dextallp1(resulta) = Dextallp1(lefta)+Dextallp1(righta)+1; &bslash;&n;&t;    else Dextallp1(resulta) = Dextallp1(lefta)+Dextallp1(righta)
DECL|macro|Dblext_arithrightshiftby1
mdefine_line|#define Dblext_arithrightshiftby1(srcdstA,srcdstB,srcdstC,srcdstD)&t;&bslash;&n;    Shiftdouble(Dextallp3(srcdstC),Dextallp4(srcdstD),1,Dextallp4(srcdstD)); &bslash;&n;    Shiftdouble(Dextallp2(srcdstB),Dextallp3(srcdstC),1,Dextallp3(srcdstC)); &bslash;&n;    Shiftdouble(Dextallp1(srcdstA),Dextallp2(srcdstB),1,Dextallp2(srcdstB)); &bslash;&n;    Dextallp1(srcdstA) = (int)Dextallp1(srcdstA) &gt;&gt; 1
DECL|macro|Dblext_leftshiftby8
mdefine_line|#define Dblext_leftshiftby8(valA,valB,valC,valD) &bslash;&n;    Shiftdouble(Dextallp1(valA),Dextallp2(valB),24,Dextallp1(valA)); &bslash;&n;    Shiftdouble(Dextallp2(valB),Dextallp3(valC),24,Dextallp2(valB)); &bslash;&n;    Shiftdouble(Dextallp3(valC),Dextallp4(valD),24,Dextallp3(valC)); &bslash;&n;    Dextallp4(valD) &lt;&lt;= 8
DECL|macro|Dblext_leftshiftby4
mdefine_line|#define Dblext_leftshiftby4(valA,valB,valC,valD) &bslash;&n;    Shiftdouble(Dextallp1(valA),Dextallp2(valB),28,Dextallp1(valA)); &bslash;&n;    Shiftdouble(Dextallp2(valB),Dextallp3(valC),28,Dextallp2(valB)); &bslash;&n;    Shiftdouble(Dextallp3(valC),Dextallp4(valD),28,Dextallp3(valC)); &bslash;&n;    Dextallp4(valD) &lt;&lt;= 4
DECL|macro|Dblext_leftshiftby3
mdefine_line|#define Dblext_leftshiftby3(valA,valB,valC,valD) &bslash;&n;    Shiftdouble(Dextallp1(valA),Dextallp2(valB),29,Dextallp1(valA)); &bslash;&n;    Shiftdouble(Dextallp2(valB),Dextallp3(valC),29,Dextallp2(valB)); &bslash;&n;    Shiftdouble(Dextallp3(valC),Dextallp4(valD),29,Dextallp3(valC)); &bslash;&n;    Dextallp4(valD) &lt;&lt;= 3
DECL|macro|Dblext_leftshiftby2
mdefine_line|#define Dblext_leftshiftby2(valA,valB,valC,valD) &bslash;&n;    Shiftdouble(Dextallp1(valA),Dextallp2(valB),30,Dextallp1(valA)); &bslash;&n;    Shiftdouble(Dextallp2(valB),Dextallp3(valC),30,Dextallp2(valB)); &bslash;&n;    Shiftdouble(Dextallp3(valC),Dextallp4(valD),30,Dextallp3(valC)); &bslash;&n;    Dextallp4(valD) &lt;&lt;= 2
DECL|macro|Dblext_leftshiftby1
mdefine_line|#define Dblext_leftshiftby1(valA,valB,valC,valD) &bslash;&n;    Shiftdouble(Dextallp1(valA),Dextallp2(valB),31,Dextallp1(valA)); &bslash;&n;    Shiftdouble(Dextallp2(valB),Dextallp3(valC),31,Dextallp2(valB)); &bslash;&n;    Shiftdouble(Dextallp3(valC),Dextallp4(valD),31,Dextallp3(valC)); &bslash;&n;    Dextallp4(valD) &lt;&lt;= 1
DECL|macro|Dblext_rightshiftby4
mdefine_line|#define Dblext_rightshiftby4(valueA,valueB,valueC,valueD) &bslash;&n;    Shiftdouble(Dextallp3(valueC),Dextallp4(valueD),4,Dextallp4(valueD)); &bslash;&n;    Shiftdouble(Dextallp2(valueB),Dextallp3(valueC),4,Dextallp3(valueC)); &bslash;&n;    Shiftdouble(Dextallp1(valueA),Dextallp2(valueB),4,Dextallp2(valueB)); &bslash;&n;    Dextallp1(valueA) &gt;&gt;= 4
DECL|macro|Dblext_rightshiftby1
mdefine_line|#define Dblext_rightshiftby1(valueA,valueB,valueC,valueD) &bslash;&n;    Shiftdouble(Dextallp3(valueC),Dextallp4(valueD),1,Dextallp4(valueD)); &bslash;&n;    Shiftdouble(Dextallp2(valueB),Dextallp3(valueC),1,Dextallp3(valueC)); &bslash;&n;    Shiftdouble(Dextallp1(valueA),Dextallp2(valueB),1,Dextallp2(valueB)); &bslash;&n;    Dextallp1(valueA) &gt;&gt;= 1
DECL|macro|Dblext_xortointp1
mdefine_line|#define Dblext_xortointp1(left,right,result) Dbl_xortointp1(left,right,result)
DECL|macro|Dblext_xorfromintp1
mdefine_line|#define Dblext_xorfromintp1(left,right,result) &bslash;&n;&t;Dbl_xorfromintp1(left,right,result)
DECL|macro|Dblext_copytoint_exponentmantissap1
mdefine_line|#define Dblext_copytoint_exponentmantissap1(src,dest) &bslash;&n;&t;Dbl_copytoint_exponentmantissap1(src,dest)
DECL|macro|Dblext_ismagnitudeless
mdefine_line|#define Dblext_ismagnitudeless(leftB,rightB,signlessleft,signlessright) &bslash;&n;&t;Dbl_ismagnitudeless(leftB,rightB,signlessleft,signlessright)
DECL|macro|Dbl_copyto_dblext
mdefine_line|#define Dbl_copyto_dblext(src1,src2,dest1,dest2,dest3,dest4) &bslash;&n;&t;Dextallp1(dest1) = Dallp1(src1); Dextallp2(dest2) = Dallp2(src2); &bslash;&n;&t;Dextallp3(dest3) = 0; Dextallp4(dest4) = 0
DECL|macro|Dblext_set_sign
mdefine_line|#define Dblext_set_sign(dbl_value,sign)  Dbl_set_sign(dbl_value,sign)  
DECL|macro|Dblext_clear_signexponent_set_hidden
mdefine_line|#define Dblext_clear_signexponent_set_hidden(srcdst) &bslash;&n;&t;Dbl_clear_signexponent_set_hidden(srcdst) 
DECL|macro|Dblext_clear_signexponent
mdefine_line|#define Dblext_clear_signexponent(srcdst) Dbl_clear_signexponent(srcdst) 
DECL|macro|Dblext_clear_sign
mdefine_line|#define Dblext_clear_sign(srcdst) Dbl_clear_sign(srcdst) 
DECL|macro|Dblext_isone_hidden
mdefine_line|#define Dblext_isone_hidden(dbl_value) Dbl_isone_hidden(dbl_value) 
multiline_comment|/*&n; * The Fourword_add() macro assumes that integers are 4 bytes in size.&n; * It will break if this is not the case.&n; */
DECL|macro|Fourword_add
mdefine_line|#define Fourword_add(src1dstA,src1dstB,src1dstC,src1dstD,src2A,src2B,src2C,src2D) &bslash;&n;&t;/* &t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; * want this macro to generate:&t;&t;&t;&t;&t;&bslash;&n;&t; *&t;ADD&t;src1dstD,src2D,src1dstD;&t;&t;&t;&bslash;&n;&t; *&t;ADDC&t;src1dstC,src2C,src1dstC;&t;&t;&t;&bslash;&n;&t; *&t;ADDC&t;src1dstB,src2B,src1dstB;&t;&t;&t;&bslash;&n;&t; *&t;ADDC&t;src1dstA,src2A,src1dstA;&t;&t;&t;&bslash;&n;&t; */&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((unsigned int)(src1dstD += (src2D)) &lt; (unsigned int)(src2D)) { &bslash;&n;&t;   if ((unsigned int)(src1dstC += (src2C) + 1) &lt;=&t;&t;&bslash;&n;&t;       (unsigned int)(src2C)) {&t;&t;&t;&t;&t;&bslash;&n;&t;     if ((unsigned int)(src1dstB += (src2B) + 1) &lt;=&t;&t;&bslash;&n;&t;&t; (unsigned int)(src2B)) src1dstA++;&t;&t;&t;&bslash;&n;&t;   }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   else if ((unsigned int)(src1dstB += (src2B)) &lt; &t;&t;&bslash;&n;&t;&t;    (unsigned int)(src2B)) src1dstA++;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   if ((unsigned int)(src1dstC += (src2C)) &lt;&t;&t;&t;&bslash;&n;&t;       (unsigned int)(src2C)) {&t;&t;&t;&t;&t;&bslash;&n;&t;      if ((unsigned int)(src1dstB += (src2B) + 1) &lt;=&t;&t;&bslash;&n;&t;&t;  (unsigned int)(src2B)) src1dstA++;&t;&t;&t;&bslash;&n;&t;   }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   else if ((unsigned int)(src1dstB += (src2B)) &lt;&t;&t;&bslash;&n;&t;&t;    (unsigned int)(src2B)) src1dstA++;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;src1dstA += (src2A)
DECL|macro|Dblext_denormalize
mdefine_line|#define Dblext_denormalize(opndp1,opndp2,opndp3,opndp4,exponent,is_tiny) &bslash;&n;  {int shiftamt, sticky;&t;&t;&t;&t;&t;&t;&bslash;&n;    is_tiny = TRUE;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (exponent == 0 &amp;&amp; (Dextallp3(opndp3) || Dextallp4(opndp4))) {&t;&bslash;&n;&t;switch (Rounding_mode()) {&t;&t;&t;&t;&t;&bslash;&n;&t;case ROUNDPLUS:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (Dbl_iszero_sign(opndp1)) {&t;&t;&t;&t;&bslash;&n;&t;&t;&t;Dbl_increment(opndp1,opndp2);&t;&t;&t;&bslash;&n;&t;&t;&t;if (Dbl_isone_hiddenoverflow(opndp1))&t;&t;&bslash;&n;&t;&t;&t;&t;is_tiny = FALSE;&t;&t;&t;&bslash;&n;&t;&t;&t;Dbl_decrement(opndp1,opndp2);&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case ROUNDMINUS:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (Dbl_isone_sign(opndp1)) {&t;&t;&t;&t;&bslash;&n;&t;&t;&t;Dbl_increment(opndp1,opndp2);&t;&t;&t;&bslash;&n;&t;&t;&t;if (Dbl_isone_hiddenoverflow(opndp1))&t;&t;&bslash;&n;&t;&t;&t;&t;is_tiny = FALSE;&t;&t;&t;&bslash;&n;&t;&t;&t;Dbl_decrement(opndp1,opndp2);&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case ROUNDNEAREST:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (Dblext_isone_highp3(opndp3) &amp;&amp;&t;&t;&t;&bslash;&n;&t;&t;    (Dblext_isone_lowp2(opndp2) || &t;&t;&t;&bslash;&n;&t;&t;     Dblext_isnotzero_low31p3(opndp3)))&t;{&t;&t;&bslash;&n;&t;&t;&t;Dbl_increment(opndp1,opndp2);&t;&t;&t;&bslash;&n;&t;&t;&t;if (Dbl_isone_hiddenoverflow(opndp1))&t;&t;&bslash;&n;&t;&t;&t;&t;is_tiny = FALSE;&t;&t;&t;&bslash;&n;&t;&t;&t;Dbl_decrement(opndp1,opndp2);&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    Dblext_clear_signexponent_set_hidden(opndp1);&t;&t;&t;&bslash;&n;    if (exponent &gt;= (1-QUAD_P)) {&t;&t;&t;&t;&t;&bslash;&n;&t;shiftamt = (1-exponent) % 32;&t;&t;&t;&t;&t;&bslash;&n;&t;switch((1-exponent)/32) {&t;&t;&t;&t;&t;&bslash;&n;&t;  case 0: sticky = Dextallp4(opndp4) &lt;&lt; 32-(shiftamt);&t;&t;&bslash;&n;&t;&t;  Variableshiftdouble(opndp3,opndp4,shiftamt,opndp4);&t;&bslash;&n;&t;&t;  Variableshiftdouble(opndp2,opndp3,shiftamt,opndp3);&t;&bslash;&n;&t;&t;  Variableshiftdouble(opndp1,opndp2,shiftamt,opndp2);&t;&bslash;&n;&t;&t;  Dextallp1(opndp1) &gt;&gt;= shiftamt;&t;&t;&t;&bslash;&n;&t;&t;  break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  case 1: sticky = (Dextallp3(opndp3) &lt;&lt; 32-(shiftamt)) | &t;&bslash;&n;&t;&t;&t;   Dextallp4(opndp4);&t;&t;&t;&t;&bslash;&n;&t;&t;  Variableshiftdouble(opndp2,opndp3,shiftamt,opndp4);&t;&bslash;&n;&t;&t;  Variableshiftdouble(opndp1,opndp2,shiftamt,opndp3);&t;&bslash;&n;&t;&t;  Dextallp2(opndp2) = Dextallp1(opndp1) &gt;&gt; shiftamt;&t;&bslash;&n;&t;&t;  Dextallp1(opndp1) = 0;&t;&t;&t;&t;&bslash;&n;&t;&t;  break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  case 2: sticky = (Dextallp2(opndp2) &lt;&lt; 32-(shiftamt)) |&t;&bslash;&n;&t;&t;&t;    Dextallp3(opndp3) | Dextallp4(opndp4);&t;&bslash;&n;&t;&t;  Variableshiftdouble(opndp1,opndp2,shiftamt,opndp4);&t;&bslash;&n;&t;&t;  Dextallp3(opndp3) = Dextallp1(opndp1) &gt;&gt; shiftamt;&t;&bslash;&n;&t;&t;  Dextallp1(opndp1) = Dextallp2(opndp2) = 0;&t;&t;&bslash;&n;&t;&t;  break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  case 3: sticky = (Dextallp1(opndp1) &lt;&lt; 32-(shiftamt)) |&t;&bslash;&n;&t;&t;  &t;Dextallp2(opndp2) | Dextallp3(opndp3) | &t;&bslash;&n;&t;&t;&t;Dextallp4(opndp4);&t;&t;&t;&t;&bslash;&n;&t;&t;  Dextallp4(opndp4) = Dextallp1(opndp1) &gt;&gt; shiftamt;&t;&bslash;&n;&t;&t;  Dextallp1(opndp1) = Dextallp2(opndp2) = 0;&t;&t;&bslash;&n;&t;&t;  Dextallp3(opndp3) = 0;&t;&t;&t;&t;&bslash;&n;&t;&t;  break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;sticky = Dextallp1(opndp1) | Dextallp2(opndp2) |&t;&t;&bslash;&n;&t;&t; Dextallp3(opndp3) | Dextallp4(opndp4);&t;&t;&t;&bslash;&n;&t;Dblext_setzero(opndp1,opndp2,opndp3,opndp4);&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (sticky) Dblext_setone_lowmantissap4(opndp4);&t;&t;&t;&bslash;&n;    exponent = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  }
eof
