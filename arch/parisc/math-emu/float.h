multiline_comment|/*&n; * Linux/PA-RISC Project (http://www.parisc-linux.org/)&n; *&n; * Floating-point emulation code&n; *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) &lt;bame@debian.org&gt;&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*&n; * BEGIN_DESC&n; * &n; *  File: &n; *      @(#)&t;pa/spmath/float.h&t;&t;$Revision: 1.1 $&n; * &n; *  Purpose:&n; *      &lt;&lt;please update with a synopis of the functionality provided by this file&gt;&gt;&n; * &n; *  BE header:  no&n; *&n; *  Shipped:  yes&n; *&t;/usr/conf/pa/spmath/float.h&n; *&n; * END_DESC  &n;*/
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
macro_line|#include &quot;fpbits.h&quot;
macro_line|#include &quot;hppa.h&quot;
multiline_comment|/*&n; * Want to pick up the FPU capability flags, not the PDC structures.&n; * &squot;LOCORE&squot; isn&squot;t really true in this case, but we don&squot;t want the C structures&n; * so it suits our purposes&n; */
DECL|macro|LOCORE
mdefine_line|#define LOCORE
macro_line|#include &quot;fpu.h&quot;
multiline_comment|/*&n; * Declare the basic structures for the 3 different&n; * floating-point precisions.&n; *        &n; * Single number  &n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; * |s|       exp     |               mantissa                      |&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; */
DECL|macro|Sall
mdefine_line|#define&t;Sall(object) (object)
DECL|macro|Ssign
mdefine_line|#define&t;Ssign(object) Bitfield_extract( 0,  1,object)
DECL|macro|Ssignedsign
mdefine_line|#define&t;Ssignedsign(object) Bitfield_signed_extract( 0,  1,object)
DECL|macro|Sexponent
mdefine_line|#define&t;Sexponent(object) Bitfield_extract( 1,  8,object)
DECL|macro|Smantissa
mdefine_line|#define&t;Smantissa(object) Bitfield_mask( 9, 23,object)
DECL|macro|Ssignaling
mdefine_line|#define&t;Ssignaling(object) Bitfield_extract( 9,  1,object)
DECL|macro|Ssignalingnan
mdefine_line|#define&t;Ssignalingnan(object) Bitfield_extract( 1,  9,object)
DECL|macro|Shigh2mantissa
mdefine_line|#define&t;Shigh2mantissa(object) Bitfield_extract( 9,  2,object)
DECL|macro|Sexponentmantissa
mdefine_line|#define&t;Sexponentmantissa(object) Bitfield_mask( 1, 31,object)
DECL|macro|Ssignexponent
mdefine_line|#define&t;Ssignexponent(object) Bitfield_extract( 0,  9,object)
DECL|macro|Shidden
mdefine_line|#define&t;Shidden(object) Bitfield_extract( 8,  1,object)
DECL|macro|Shiddenoverflow
mdefine_line|#define&t;Shiddenoverflow(object) Bitfield_extract( 7,  1,object)
DECL|macro|Shiddenhigh7mantissa
mdefine_line|#define&t;Shiddenhigh7mantissa(object) Bitfield_extract( 8,  8,object)
DECL|macro|Shiddenhigh3mantissa
mdefine_line|#define&t;Shiddenhigh3mantissa(object) Bitfield_extract( 8,  4,object)
DECL|macro|Slow
mdefine_line|#define&t;Slow(object) Bitfield_mask( 31,  1,object)
DECL|macro|Slow4
mdefine_line|#define&t;Slow4(object) Bitfield_mask( 28,  4,object)
DECL|macro|Slow31
mdefine_line|#define&t;Slow31(object) Bitfield_mask( 1, 31,object)
DECL|macro|Shigh31
mdefine_line|#define&t;Shigh31(object) Bitfield_extract( 0, 31,object)
DECL|macro|Ssignedhigh31
mdefine_line|#define&t;Ssignedhigh31(object) Bitfield_signed_extract( 0, 31,object)
DECL|macro|Shigh4
mdefine_line|#define&t;Shigh4(object) Bitfield_extract( 0,  4,object)
DECL|macro|Sbit24
mdefine_line|#define&t;Sbit24(object) Bitfield_extract( 24,  1,object)
DECL|macro|Sbit28
mdefine_line|#define&t;Sbit28(object) Bitfield_extract( 28,  1,object)
DECL|macro|Sbit29
mdefine_line|#define&t;Sbit29(object) Bitfield_extract( 29,  1,object)
DECL|macro|Sbit30
mdefine_line|#define&t;Sbit30(object) Bitfield_extract( 30,  1,object)
DECL|macro|Sbit31
mdefine_line|#define&t;Sbit31(object) Bitfield_mask( 31,  1,object)
DECL|macro|Deposit_ssign
mdefine_line|#define Deposit_ssign(object,value) Bitfield_deposit(value,0,1,object)
DECL|macro|Deposit_sexponent
mdefine_line|#define Deposit_sexponent(object,value) Bitfield_deposit(value,1,8,object)
DECL|macro|Deposit_smantissa
mdefine_line|#define Deposit_smantissa(object,value) Bitfield_deposit(value,9,23,object)
DECL|macro|Deposit_shigh2mantissa
mdefine_line|#define Deposit_shigh2mantissa(object,value) Bitfield_deposit(value,9,2,object)
DECL|macro|Deposit_sexponentmantissa
mdefine_line|#define Deposit_sexponentmantissa(object,value) &bslash;&n;    Bitfield_deposit(value,1,31,object)
DECL|macro|Deposit_ssignexponent
mdefine_line|#define Deposit_ssignexponent(object,value) Bitfield_deposit(value,0,9,object)
DECL|macro|Deposit_slow
mdefine_line|#define Deposit_slow(object,value) Bitfield_deposit(value,31,1,object)
DECL|macro|Deposit_shigh4
mdefine_line|#define Deposit_shigh4(object,value) Bitfield_deposit(value,0,4,object)
DECL|macro|Is_ssign
mdefine_line|#define&t;Is_ssign(object) Bitfield_mask( 0,  1,object)
DECL|macro|Is_ssignaling
mdefine_line|#define&t;Is_ssignaling(object) Bitfield_mask( 9,  1,object)
DECL|macro|Is_shidden
mdefine_line|#define&t;Is_shidden(object) Bitfield_mask( 8,  1,object)
DECL|macro|Is_shiddenoverflow
mdefine_line|#define&t;Is_shiddenoverflow(object) Bitfield_mask( 7,  1,object)
DECL|macro|Is_slow
mdefine_line|#define&t;Is_slow(object) Bitfield_mask( 31,  1,object)
DECL|macro|Is_sbit24
mdefine_line|#define&t;Is_sbit24(object) Bitfield_mask( 24,  1,object)
DECL|macro|Is_sbit28
mdefine_line|#define&t;Is_sbit28(object) Bitfield_mask( 28,  1,object)
DECL|macro|Is_sbit29
mdefine_line|#define&t;Is_sbit29(object) Bitfield_mask( 29,  1,object)
DECL|macro|Is_sbit30
mdefine_line|#define&t;Is_sbit30(object) Bitfield_mask( 30,  1,object)
DECL|macro|Is_sbit31
mdefine_line|#define&t;Is_sbit31(object) Bitfield_mask( 31,  1,object)
multiline_comment|/* &n; * Double number.&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; * |s|       exponent      |          mantissa part 1              |&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; *&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; * |                    mantissa part 2                            |&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; */
DECL|macro|Dallp1
mdefine_line|#define Dallp1(object) (object)
DECL|macro|Dsign
mdefine_line|#define Dsign(object) Bitfield_extract( 0,  1,object)
DECL|macro|Dsignedsign
mdefine_line|#define Dsignedsign(object) Bitfield_signed_extract( 0,  1,object)
DECL|macro|Dexponent
mdefine_line|#define Dexponent(object) Bitfield_extract( 1,  11,object)
DECL|macro|Dmantissap1
mdefine_line|#define Dmantissap1(object) Bitfield_mask( 12, 20,object)
DECL|macro|Dsignaling
mdefine_line|#define Dsignaling(object) Bitfield_extract( 12,  1,object)
DECL|macro|Dsignalingnan
mdefine_line|#define Dsignalingnan(object) Bitfield_extract( 1,  12,object)
DECL|macro|Dhigh2mantissa
mdefine_line|#define Dhigh2mantissa(object) Bitfield_extract( 12,  2,object)
DECL|macro|Dexponentmantissap1
mdefine_line|#define Dexponentmantissap1(object) Bitfield_mask( 1, 31,object)
DECL|macro|Dsignexponent
mdefine_line|#define Dsignexponent(object) Bitfield_extract( 0, 12,object)
DECL|macro|Dhidden
mdefine_line|#define Dhidden(object) Bitfield_extract( 11,  1,object)
DECL|macro|Dhiddenoverflow
mdefine_line|#define Dhiddenoverflow(object) Bitfield_extract( 10,  1,object)
DECL|macro|Dhiddenhigh7mantissa
mdefine_line|#define Dhiddenhigh7mantissa(object) Bitfield_extract( 11,  8,object)
DECL|macro|Dhiddenhigh3mantissa
mdefine_line|#define Dhiddenhigh3mantissa(object) Bitfield_extract( 11,  4,object)
DECL|macro|Dlowp1
mdefine_line|#define Dlowp1(object) Bitfield_mask( 31,  1,object)
DECL|macro|Dlow31p1
mdefine_line|#define Dlow31p1(object) Bitfield_mask( 1, 31,object)
DECL|macro|Dhighp1
mdefine_line|#define Dhighp1(object) Bitfield_extract( 0,  1,object)
DECL|macro|Dhigh4p1
mdefine_line|#define Dhigh4p1(object) Bitfield_extract( 0,  4,object)
DECL|macro|Dhigh31p1
mdefine_line|#define Dhigh31p1(object) Bitfield_extract( 0, 31,object)
DECL|macro|Dsignedhigh31p1
mdefine_line|#define Dsignedhigh31p1(object) Bitfield_signed_extract( 0, 31,object)
DECL|macro|Dbit3p1
mdefine_line|#define Dbit3p1(object) Bitfield_extract( 3,  1,object)
DECL|macro|Deposit_dsign
mdefine_line|#define Deposit_dsign(object,value) Bitfield_deposit(value,0,1,object)
DECL|macro|Deposit_dexponent
mdefine_line|#define Deposit_dexponent(object,value) Bitfield_deposit(value,1,11,object)
DECL|macro|Deposit_dmantissap1
mdefine_line|#define Deposit_dmantissap1(object,value) Bitfield_deposit(value,12,20,object)
DECL|macro|Deposit_dhigh2mantissa
mdefine_line|#define Deposit_dhigh2mantissa(object,value) Bitfield_deposit(value,12,2,object)
DECL|macro|Deposit_dexponentmantissap1
mdefine_line|#define Deposit_dexponentmantissap1(object,value) &bslash;&n;    Bitfield_deposit(value,1,31,object)
DECL|macro|Deposit_dsignexponent
mdefine_line|#define Deposit_dsignexponent(object,value) Bitfield_deposit(value,0,12,object)
DECL|macro|Deposit_dlowp1
mdefine_line|#define Deposit_dlowp1(object,value) Bitfield_deposit(value,31,1,object)
DECL|macro|Deposit_dhigh4p1
mdefine_line|#define Deposit_dhigh4p1(object,value) Bitfield_deposit(value,0,4,object)
DECL|macro|Is_dsign
mdefine_line|#define Is_dsign(object) Bitfield_mask( 0,  1,object)
DECL|macro|Is_dsignaling
mdefine_line|#define Is_dsignaling(object) Bitfield_mask( 12,  1,object)
DECL|macro|Is_dhidden
mdefine_line|#define Is_dhidden(object) Bitfield_mask( 11,  1,object)
DECL|macro|Is_dhiddenoverflow
mdefine_line|#define Is_dhiddenoverflow(object) Bitfield_mask( 10,  1,object)
DECL|macro|Is_dlowp1
mdefine_line|#define Is_dlowp1(object) Bitfield_mask( 31,  1,object)
DECL|macro|Is_dhighp1
mdefine_line|#define Is_dhighp1(object) Bitfield_mask( 0,  1,object)
DECL|macro|Is_dbit3p1
mdefine_line|#define Is_dbit3p1(object) Bitfield_mask( 3,  1,object)
DECL|macro|Dallp2
mdefine_line|#define Dallp2(object) (object)
DECL|macro|Dmantissap2
mdefine_line|#define Dmantissap2(object) (object)
DECL|macro|Dlowp2
mdefine_line|#define Dlowp2(object) Bitfield_mask( 31,  1,object)
DECL|macro|Dlow4p2
mdefine_line|#define Dlow4p2(object) Bitfield_mask( 28,  4,object)
DECL|macro|Dlow31p2
mdefine_line|#define Dlow31p2(object) Bitfield_mask( 1, 31,object)
DECL|macro|Dhighp2
mdefine_line|#define Dhighp2(object) Bitfield_extract( 0,  1,object)
DECL|macro|Dhigh31p2
mdefine_line|#define Dhigh31p2(object) Bitfield_extract( 0, 31,object)
DECL|macro|Dbit2p2
mdefine_line|#define Dbit2p2(object) Bitfield_extract( 2,  1,object)
DECL|macro|Dbit3p2
mdefine_line|#define Dbit3p2(object) Bitfield_extract( 3,  1,object)
DECL|macro|Dbit21p2
mdefine_line|#define Dbit21p2(object) Bitfield_extract( 21,  1,object)
DECL|macro|Dbit28p2
mdefine_line|#define Dbit28p2(object) Bitfield_extract( 28,  1,object)
DECL|macro|Dbit29p2
mdefine_line|#define Dbit29p2(object) Bitfield_extract( 29,  1,object)
DECL|macro|Dbit30p2
mdefine_line|#define Dbit30p2(object) Bitfield_extract( 30,  1,object)
DECL|macro|Dbit31p2
mdefine_line|#define Dbit31p2(object) Bitfield_mask( 31,  1,object)
DECL|macro|Deposit_dlowp2
mdefine_line|#define Deposit_dlowp2(object,value) Bitfield_deposit(value,31,1,object)
DECL|macro|Is_dlowp2
mdefine_line|#define Is_dlowp2(object) Bitfield_mask( 31,  1,object)
DECL|macro|Is_dhighp2
mdefine_line|#define Is_dhighp2(object) Bitfield_mask( 0,  1,object)
DECL|macro|Is_dbit2p2
mdefine_line|#define Is_dbit2p2(object) Bitfield_mask( 2,  1,object)
DECL|macro|Is_dbit3p2
mdefine_line|#define Is_dbit3p2(object) Bitfield_mask( 3,  1,object)
DECL|macro|Is_dbit21p2
mdefine_line|#define Is_dbit21p2(object) Bitfield_mask( 21,  1,object)
DECL|macro|Is_dbit28p2
mdefine_line|#define Is_dbit28p2(object) Bitfield_mask( 28,  1,object)
DECL|macro|Is_dbit29p2
mdefine_line|#define Is_dbit29p2(object) Bitfield_mask( 29,  1,object)
DECL|macro|Is_dbit30p2
mdefine_line|#define Is_dbit30p2(object) Bitfield_mask( 30,  1,object)
DECL|macro|Is_dbit31p2
mdefine_line|#define Is_dbit31p2(object) Bitfield_mask( 31,  1,object)
multiline_comment|/* &n; * Quad number.&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; * |s|          exponent           |      mantissa part 1          |&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; *&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; * |                    mantissa part 2                            |&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; *&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; * |                    mantissa part 3                            |&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; *&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; * |                    mantissa part 4                            |&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; */
r_typedef
r_struct
(brace
r_union
(brace
DECL|member|qallp1
DECL|member|u_qallp1
r_struct
(brace
r_int
id|qallp1
suffix:semicolon
)brace
id|u_qallp1
suffix:semicolon
multiline_comment|/* Not needed for now...&n;&t;Bitfield_extract( 0,  1,u_qsign,qsign)&n;&t;Bitfield_signed_extract( 0,  1,u_qsignedsign,qsignedsign)&n;&t;Bitfield_extract( 1, 15,u_qexponent,qexponent)&n;&t;Bitfield_extract(16, 16,u_qmantissap1,qmantissap1)&n;&t;Bitfield_extract(16,  1,u_qsignaling,qsignaling)&n;&t;Bitfield_extract(1,  16,u_qsignalingnan,qsignalingnan)&n;&t;Bitfield_extract(16,  2,u_qhigh2mantissa,qhigh2mantissa)&n;&t;Bitfield_extract( 1, 31,u_qexponentmantissap1,qexponentmantissap1)&n;&t;Bitfield_extract( 0, 16,u_qsignexponent,qsignexponent)&n;&t;Bitfield_extract(15,  1,u_qhidden,qhidden)&n;&t;Bitfield_extract(14,  1,u_qhiddenoverflow,qhiddenoverflow)&n;&t;Bitfield_extract(15,  8,u_qhiddenhigh7mantissa,qhiddenhigh7mantissa)&n;&t;Bitfield_extract(15,  4,u_qhiddenhigh3mantissa,qhiddenhigh3mantissa)&n;&t;Bitfield_extract(31,  1,u_qlowp1,qlowp1)&n;&t;Bitfield_extract( 1, 31,u_qlow31p1,qlow31p1)&n;&t;Bitfield_extract( 0,  1,u_qhighp1,qhighp1)&n;&t;Bitfield_extract( 0,  4,u_qhigh4p1,qhigh4p1)&n;&t;Bitfield_extract( 0, 31,u_qhigh31p1,qhigh31p1)&n;  */
DECL|member|quad_u1
)brace
id|quad_u1
suffix:semicolon
r_union
(brace
DECL|member|qallp2
DECL|member|u_qallp2
r_struct
(brace
r_int
id|qallp2
suffix:semicolon
)brace
id|u_qallp2
suffix:semicolon
multiline_comment|/* Not needed for now...&n;&t;Bitfield_extract(31,  1,u_qlowp2,qlowp2)&n;&t;Bitfield_extract( 1, 31,u_qlow31p2,qlow31p2)&n;&t;Bitfield_extract( 0,  1,u_qhighp2,qhighp2)&n;&t;Bitfield_extract( 0, 31,u_qhigh31p2,qhigh31p2)&n;   */
DECL|member|quad_u2
)brace
id|quad_u2
suffix:semicolon
r_union
(brace
DECL|member|qallp3
DECL|member|u_qallp3
r_struct
(brace
r_int
id|qallp3
suffix:semicolon
)brace
id|u_qallp3
suffix:semicolon
multiline_comment|/* Not needed for now...&n;&t;Bitfield_extract(31,  1,u_qlowp3,qlowp3)&n;&t;Bitfield_extract( 1, 31,u_qlow31p3,qlow31p3)&n;&t;Bitfield_extract( 0,  1,u_qhighp3,qhighp3)&n;&t;Bitfield_extract( 0, 31,u_qhigh31p3,qhigh31p3)&n;   */
DECL|member|quad_u3
)brace
id|quad_u3
suffix:semicolon
r_union
(brace
DECL|member|qallp4
DECL|member|u_qallp4
r_struct
(brace
r_int
id|qallp4
suffix:semicolon
)brace
id|u_qallp4
suffix:semicolon
multiline_comment|/* Not need for now...&n;&t;Bitfield_extract(31,  1,u_qlowp4,qlowp4)&n;&t;Bitfield_extract( 1, 31,u_qlow31p4,qlow31p4)&n;&t;Bitfield_extract( 0,  1,u_qhighp4,qhighp4)&n;&t;Bitfield_extract( 0, 31,u_qhigh31p4,qhigh31p4)&n;     */
DECL|member|quad_u4
)brace
id|quad_u4
suffix:semicolon
DECL|typedef|quad_floating_point
)brace
id|quad_floating_point
suffix:semicolon
multiline_comment|/* Extension - An additional structure to hold the guard, round and&n; *             sticky bits during computations.&n; */
DECL|macro|Extall
mdefine_line|#define Extall(object) (object)
DECL|macro|Extsign
mdefine_line|#define Extsign(object) Bitfield_extract( 0,  1,object)
DECL|macro|Exthigh31
mdefine_line|#define Exthigh31(object) Bitfield_extract( 0, 31,object)
DECL|macro|Extlow31
mdefine_line|#define Extlow31(object) Bitfield_extract( 1, 31,object)
DECL|macro|Extlow
mdefine_line|#define Extlow(object) Bitfield_extract( 31,  1,object)
multiline_comment|/*&n; * Single extended - The upper word is just like single precision,&n; *                 but one additional word of mantissa is needed.&n; */
DECL|macro|Sextallp1
mdefine_line|#define Sextallp1(object) (object)
DECL|macro|Sextallp2
mdefine_line|#define Sextallp2(object) (object)
DECL|macro|Sextlowp1
mdefine_line|#define Sextlowp1(object) Bitfield_extract( 31,  1,object)
DECL|macro|Sexthighp2
mdefine_line|#define Sexthighp2(object) Bitfield_extract( 0,  1,object)
DECL|macro|Sextlow31p2
mdefine_line|#define Sextlow31p2(object) Bitfield_extract( 1, 31,object)
DECL|macro|Sexthiddenoverflow
mdefine_line|#define Sexthiddenoverflow(object) Bitfield_extract( 4,  1,object)
DECL|macro|Is_sexthiddenoverflow
mdefine_line|#define Is_sexthiddenoverflow(object) Bitfield_mask( 4,  1,object)
multiline_comment|/*&n; * Double extended - The upper two words are just like double precision,&n; *&t;&t;     but two additional words of mantissa are needed.&n; */
DECL|macro|Dextallp1
mdefine_line|#define Dextallp1(object) (object)
DECL|macro|Dextallp2
mdefine_line|#define Dextallp2(object) (object)
DECL|macro|Dextallp3
mdefine_line|#define Dextallp3(object) (object)
DECL|macro|Dextallp4
mdefine_line|#define Dextallp4(object) (object)
DECL|macro|Dextlowp2
mdefine_line|#define Dextlowp2(object) Bitfield_extract( 31,  1,object)
DECL|macro|Dexthighp3
mdefine_line|#define Dexthighp3(object) Bitfield_extract( 0,  1,object)
DECL|macro|Dextlow31p3
mdefine_line|#define Dextlow31p3(object) Bitfield_extract( 1, 31,object)
DECL|macro|Dexthiddenoverflow
mdefine_line|#define Dexthiddenoverflow(object) Bitfield_extract( 10,  1,object)
DECL|macro|Is_dexthiddenoverflow
mdefine_line|#define Is_dexthiddenoverflow(object) Bitfield_mask( 10,  1,object)
DECL|macro|Deposit_dextlowp4
mdefine_line|#define Deposit_dextlowp4(object,value) Bitfield_deposit(value,31,1,object)
multiline_comment|/*&n; * Declare the basic structures for the 3 different&n; * fixed-point precisions.&n; *        &n; * Single number  &n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; * |s|                    integer                                  |&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; */
DECL|typedef|sgl_integer
r_typedef
r_int
id|sgl_integer
suffix:semicolon
multiline_comment|/* &n; * Double number.&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; * |s|                     high integer                            |&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; *&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; * |                       low integer                             |&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; */
DECL|struct|dint
r_struct
id|dint
(brace
DECL|member|wd0
r_int
id|wd0
suffix:semicolon
DECL|member|wd1
r_int
r_int
id|wd1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dblwd
r_struct
id|dblwd
(brace
DECL|member|wd0
r_int
r_int
id|wd0
suffix:semicolon
DECL|member|wd1
r_int
r_int
id|wd1
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * Quad number.&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; * |s|                  integer part1                              |&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; *&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; * |                    integer part 2                             |&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; *&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; * |                    integer part 3                             |&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; *&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; * |                    integer part 4                             |&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; */
DECL|struct|quadwd
r_struct
id|quadwd
(brace
DECL|member|wd0
r_int
id|wd0
suffix:semicolon
DECL|member|wd1
r_int
r_int
id|wd1
suffix:semicolon
DECL|member|wd2
r_int
r_int
id|wd2
suffix:semicolon
DECL|member|wd3
r_int
r_int
id|wd3
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|quad_integer
r_typedef
r_struct
id|quadwd
id|quad_integer
suffix:semicolon
multiline_comment|/* useful typedefs */
DECL|typedef|sgl_floating_point
r_typedef
r_int
r_int
id|sgl_floating_point
suffix:semicolon
DECL|typedef|dbl_floating_point
r_typedef
r_struct
id|dblwd
id|dbl_floating_point
suffix:semicolon
DECL|typedef|dbl_integer
r_typedef
r_struct
id|dint
id|dbl_integer
suffix:semicolon
DECL|typedef|dbl_unsigned
r_typedef
r_struct
id|dblwd
id|dbl_unsigned
suffix:semicolon
multiline_comment|/* &n; * Define the different precisions&squot; parameters.&n; */
DECL|macro|SGL_BITLENGTH
mdefine_line|#define SGL_BITLENGTH 32
DECL|macro|SGL_EMAX
mdefine_line|#define SGL_EMAX 127
DECL|macro|SGL_EMIN
mdefine_line|#define SGL_EMIN (-126)
DECL|macro|SGL_BIAS
mdefine_line|#define SGL_BIAS 127
DECL|macro|SGL_WRAP
mdefine_line|#define SGL_WRAP 192
DECL|macro|SGL_INFINITY_EXPONENT
mdefine_line|#define SGL_INFINITY_EXPONENT (SGL_EMAX+SGL_BIAS+1)
DECL|macro|SGL_THRESHOLD
mdefine_line|#define SGL_THRESHOLD 32
DECL|macro|SGL_EXP_LENGTH
mdefine_line|#define SGL_EXP_LENGTH 8
DECL|macro|SGL_P
mdefine_line|#define SGL_P 24
DECL|macro|DBL_BITLENGTH
mdefine_line|#define DBL_BITLENGTH 64
DECL|macro|DBL_EMAX
mdefine_line|#define DBL_EMAX 1023
DECL|macro|DBL_EMIN
mdefine_line|#define DBL_EMIN (-1022)
DECL|macro|DBL_BIAS
mdefine_line|#define DBL_BIAS 1023
DECL|macro|DBL_WRAP
mdefine_line|#define DBL_WRAP 1536
DECL|macro|DBL_INFINITY_EXPONENT
mdefine_line|#define DBL_INFINITY_EXPONENT (DBL_EMAX+DBL_BIAS+1)
DECL|macro|DBL_THRESHOLD
mdefine_line|#define DBL_THRESHOLD 64
DECL|macro|DBL_EXP_LENGTH
mdefine_line|#define DBL_EXP_LENGTH 11
DECL|macro|DBL_P
mdefine_line|#define DBL_P 53
DECL|macro|QUAD_BITLENGTH
mdefine_line|#define QUAD_BITLENGTH 128
DECL|macro|QUAD_EMAX
mdefine_line|#define QUAD_EMAX 16383
DECL|macro|QUAD_EMIN
mdefine_line|#define QUAD_EMIN (-16382)
DECL|macro|QUAD_BIAS
mdefine_line|#define QUAD_BIAS 16383
DECL|macro|QUAD_WRAP
mdefine_line|#define QUAD_WRAP 24576
DECL|macro|QUAD_INFINITY_EXPONENT
mdefine_line|#define QUAD_INFINITY_EXPONENT (QUAD_EMAX+QUAD_BIAS+1)
DECL|macro|QUAD_P
mdefine_line|#define QUAD_P 113
multiline_comment|/* Boolean Values etc. */
DECL|macro|FALSE
mdefine_line|#define FALSE 0
DECL|macro|TRUE
mdefine_line|#define TRUE (!FALSE)
DECL|macro|NOT
mdefine_line|#define NOT !
DECL|macro|XOR
mdefine_line|#define XOR ^
multiline_comment|/* other constants */
DECL|macro|NULL
macro_line|#undef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
DECL|macro|NIL
mdefine_line|#define NIL 0
DECL|macro|SGL
mdefine_line|#define SGL 0
DECL|macro|DBL
mdefine_line|#define DBL 1
DECL|macro|BADFMT
mdefine_line|#define BADFMT 2
DECL|macro|QUAD
mdefine_line|#define QUAD 3
multiline_comment|/* Types */
DECL|typedef|boolean
r_typedef
r_int
id|boolean
suffix:semicolon
DECL|typedef|FORMAT
r_typedef
r_int
id|FORMAT
suffix:semicolon
DECL|typedef|VOID
r_typedef
r_int
id|VOID
suffix:semicolon
multiline_comment|/* Declare status register equivalent to FPUs architecture.&n; *&n; *  0 1 2 3 4 5 6 7 8 910 1 2 3 4 5 6 7 8 920 1 2 3 4 5 6 7 8 930 1&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; * |V|Z|O|U|I|C|  rsv  |  model    | version |RM |rsv|T|r|V|Z|O|U|I|&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; */
DECL|macro|Cbit
mdefine_line|#define Cbit(object) Bitfield_extract( 5, 1,object)
DECL|macro|Tbit
mdefine_line|#define Tbit(object) Bitfield_extract( 25, 1,object)
DECL|macro|Roundingmode
mdefine_line|#define Roundingmode(object) Bitfield_extract( 21, 2,object)
DECL|macro|Invalidtrap
mdefine_line|#define Invalidtrap(object) Bitfield_extract( 27, 1,object)
DECL|macro|Divisionbyzerotrap
mdefine_line|#define Divisionbyzerotrap(object) Bitfield_extract( 28, 1,object)
DECL|macro|Overflowtrap
mdefine_line|#define Overflowtrap(object) Bitfield_extract( 29, 1,object)
DECL|macro|Underflowtrap
mdefine_line|#define Underflowtrap(object) Bitfield_extract( 30, 1,object)
DECL|macro|Inexacttrap
mdefine_line|#define Inexacttrap(object) Bitfield_extract( 31, 1,object)
DECL|macro|Invalidflag
mdefine_line|#define Invalidflag(object) Bitfield_extract( 0, 1,object)
DECL|macro|Divisionbyzeroflag
mdefine_line|#define Divisionbyzeroflag(object) Bitfield_extract( 1, 1,object)
DECL|macro|Overflowflag
mdefine_line|#define Overflowflag(object) Bitfield_extract( 2, 1,object)
DECL|macro|Underflowflag
mdefine_line|#define Underflowflag(object) Bitfield_extract( 3, 1,object)
DECL|macro|Inexactflag
mdefine_line|#define Inexactflag(object) Bitfield_extract( 4, 1,object)
DECL|macro|Allflags
mdefine_line|#define Allflags(object) Bitfield_extract( 0, 5,object)
multiline_comment|/* Definitions relevant to the status register */
multiline_comment|/* Rounding Modes */
DECL|macro|ROUNDNEAREST
mdefine_line|#define ROUNDNEAREST 0
DECL|macro|ROUNDZERO
mdefine_line|#define ROUNDZERO    1
DECL|macro|ROUNDPLUS
mdefine_line|#define ROUNDPLUS    2
DECL|macro|ROUNDMINUS
mdefine_line|#define ROUNDMINUS   3
multiline_comment|/* Exceptions */
DECL|macro|NOEXCEPTION
mdefine_line|#define NOEXCEPTION&t;&t;0x0
DECL|macro|INVALIDEXCEPTION
mdefine_line|#define INVALIDEXCEPTION&t;0x20
DECL|macro|DIVISIONBYZEROEXCEPTION
mdefine_line|#define DIVISIONBYZEROEXCEPTION&t;0x10
DECL|macro|OVERFLOWEXCEPTION
mdefine_line|#define OVERFLOWEXCEPTION&t;0x08
DECL|macro|UNDERFLOWEXCEPTION
mdefine_line|#define UNDERFLOWEXCEPTION&t;0x04
DECL|macro|INEXACTEXCEPTION
mdefine_line|#define INEXACTEXCEPTION&t;0x02
DECL|macro|UNIMPLEMENTEDEXCEPTION
mdefine_line|#define UNIMPLEMENTEDEXCEPTION&t;0x01
multiline_comment|/* New exceptions for the 2E Opcode */
DECL|macro|OPC_2E_INVALIDEXCEPTION
mdefine_line|#define OPC_2E_INVALIDEXCEPTION     0x30
DECL|macro|OPC_2E_OVERFLOWEXCEPTION
mdefine_line|#define OPC_2E_OVERFLOWEXCEPTION    0x18
DECL|macro|OPC_2E_UNDERFLOWEXCEPTION
mdefine_line|#define OPC_2E_UNDERFLOWEXCEPTION   0x0c
DECL|macro|OPC_2E_INEXACTEXCEPTION
mdefine_line|#define OPC_2E_INEXACTEXCEPTION     0x12
multiline_comment|/* Declare exception registers equivalent to FPUs architecture &n; *&n; *  0 1 2 3 4 5 6 7 8 910 1 2 3 4 5 6 7 8 920 1 2 3 4 5 6 7 8 930 1&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; * |excepttype |  r1     | r2/ext  |  operation  |parm |n| t/cond  |&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; */
DECL|macro|Allexception
mdefine_line|#define Allexception(object) (object)
DECL|macro|Exceptiontype
mdefine_line|#define Exceptiontype(object) Bitfield_extract( 0, 6,object)
DECL|macro|Instructionfield
mdefine_line|#define Instructionfield(object) Bitfield_mask( 6,26,object)
DECL|macro|Parmfield
mdefine_line|#define Parmfield(object) Bitfield_extract( 23, 3,object)
DECL|macro|Rabit
mdefine_line|#define Rabit(object) Bitfield_extract( 24, 1,object)
DECL|macro|Ibit
mdefine_line|#define Ibit(object) Bitfield_extract( 25, 1,object)
DECL|macro|Set_exceptiontype
mdefine_line|#define Set_exceptiontype(object,value) Bitfield_deposit(value, 0, 6,object)
DECL|macro|Set_parmfield
mdefine_line|#define Set_parmfield(object,value) Bitfield_deposit(value, 23, 3,object)
DECL|macro|Set_exceptiontype_and_instr_field
mdefine_line|#define Set_exceptiontype_and_instr_field(exception,instruction,object) &bslash;&n;    object = exception &lt;&lt; 26 | instruction
multiline_comment|/* Declare the condition field&n; *&n; *  0 1 2 3 4 5 6 7 8 910 1 2 3 4 5 6 7 8 920 1 2 3 4 5 6 7 8 930 1&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; * |                                                     |G|L|E|U|X|&n; * +-------+-------+-------+-------+-------+-------+-------+-------+&n; */
DECL|macro|Allexception
mdefine_line|#define Allexception(object) (object)
DECL|macro|Greaterthanbit
mdefine_line|#define Greaterthanbit(object) Bitfield_extract( 27, 1,object)
DECL|macro|Lessthanbit
mdefine_line|#define Lessthanbit(object) Bitfield_extract( 28, 1,object)
DECL|macro|Equalbit
mdefine_line|#define Equalbit(object) Bitfield_extract( 29, 1,object)
DECL|macro|Unorderedbit
mdefine_line|#define Unorderedbit(object) Bitfield_extract( 30, 1,object)
DECL|macro|Exceptionbit
mdefine_line|#define Exceptionbit(object) Bitfield_extract( 31, 1,object)
multiline_comment|/* An alias name for the status register */
DECL|macro|Fpustatus_register
mdefine_line|#define Fpustatus_register (*status)
multiline_comment|/**************************************************&n; * Status register referencing and manipulation.  *&n; **************************************************/
multiline_comment|/* Rounding mode */
DECL|macro|Rounding_mode
mdefine_line|#define Rounding_mode()  Roundingmode(Fpustatus_register)
DECL|macro|Is_rounding_mode
mdefine_line|#define Is_rounding_mode(rmode) &bslash;&n;    (Roundingmode(Fpustatus_register) == rmode)
DECL|macro|Set_rounding_mode
mdefine_line|#define Set_rounding_mode(value) &bslash;&n;    Bitfield_deposit(value,21,2,Fpustatus_register)
multiline_comment|/* Boolean testing of the trap enable bits */
DECL|macro|Is_invalidtrap_enabled
mdefine_line|#define Is_invalidtrap_enabled() Invalidtrap(Fpustatus_register)
DECL|macro|Is_divisionbyzerotrap_enabled
mdefine_line|#define Is_divisionbyzerotrap_enabled() Divisionbyzerotrap(Fpustatus_register)
DECL|macro|Is_overflowtrap_enabled
mdefine_line|#define Is_overflowtrap_enabled() Overflowtrap(Fpustatus_register)
DECL|macro|Is_underflowtrap_enabled
mdefine_line|#define Is_underflowtrap_enabled() Underflowtrap(Fpustatus_register)
DECL|macro|Is_inexacttrap_enabled
mdefine_line|#define Is_inexacttrap_enabled() Inexacttrap(Fpustatus_register)
multiline_comment|/* Set the indicated flags in the status register */
DECL|macro|Set_invalidflag
mdefine_line|#define Set_invalidflag() Bitfield_deposit(1,0,1,Fpustatus_register)
DECL|macro|Set_divisionbyzeroflag
mdefine_line|#define Set_divisionbyzeroflag() Bitfield_deposit(1,1,1,Fpustatus_register)
DECL|macro|Set_overflowflag
mdefine_line|#define Set_overflowflag() Bitfield_deposit(1,2,1,Fpustatus_register)
DECL|macro|Set_underflowflag
mdefine_line|#define Set_underflowflag() Bitfield_deposit(1,3,1,Fpustatus_register)
DECL|macro|Set_inexactflag
mdefine_line|#define Set_inexactflag() Bitfield_deposit(1,4,1,Fpustatus_register)
DECL|macro|Clear_all_flags
mdefine_line|#define Clear_all_flags() Bitfield_deposit(0,0,5,Fpustatus_register)
multiline_comment|/* Manipulate the trap and condition code bits (tbit and cbit) */
DECL|macro|Set_tbit
mdefine_line|#define Set_tbit() Bitfield_deposit(1,25,1,Fpustatus_register)
DECL|macro|Clear_tbit
mdefine_line|#define Clear_tbit() Bitfield_deposit(0,25,1,Fpustatus_register)
DECL|macro|Is_tbit_set
mdefine_line|#define Is_tbit_set() Tbit(Fpustatus_register)
DECL|macro|Is_cbit_set
mdefine_line|#define Is_cbit_set() Cbit(Fpustatus_register)
DECL|macro|Set_status_cbit
mdefine_line|#define Set_status_cbit(value)  &bslash;&n;        Bitfield_deposit(value,5,1,Fpustatus_register)
multiline_comment|/*******************************&n; * Condition field referencing *&n; *******************************/
DECL|macro|Unordered
mdefine_line|#define Unordered(cond) Unorderedbit(cond)
DECL|macro|Equal
mdefine_line|#define Equal(cond) Equalbit(cond)
DECL|macro|Lessthan
mdefine_line|#define Lessthan(cond) Lessthanbit(cond)
DECL|macro|Greaterthan
mdefine_line|#define Greaterthan(cond) Greaterthanbit(cond)
DECL|macro|Exception
mdefine_line|#define Exception(cond) Exceptionbit(cond)
multiline_comment|/* Defines for the extension */
DECL|macro|Ext_isone_sign
mdefine_line|#define Ext_isone_sign(extent) (Extsign(extent))
DECL|macro|Ext_isnotzero
mdefine_line|#define Ext_isnotzero(extent) &bslash;&n;    (Extall(extent))
DECL|macro|Ext_isnotzero_lower
mdefine_line|#define Ext_isnotzero_lower(extent) &bslash;&n;    (Extlow31(extent))
DECL|macro|Ext_leftshiftby1
mdefine_line|#define Ext_leftshiftby1(extent) &bslash;&n;    Extall(extent) &lt;&lt;= 1
DECL|macro|Ext_negate
mdefine_line|#define Ext_negate(extent) &bslash;&n;    (int )Extall(extent) = 0 - (int )Extall(extent)
DECL|macro|Ext_setone_low
mdefine_line|#define Ext_setone_low(extent) Bitfield_deposit(1,31,1,extent)
DECL|macro|Ext_setzero
mdefine_line|#define Ext_setzero(extent) Extall(extent) = 0
DECL|typedef|operation
r_typedef
r_int
id|operation
suffix:semicolon
multiline_comment|/* error messages */
DECL|macro|NONE
mdefine_line|#define&t;&t;NONE&t;&t;0
DECL|macro|UNDEFFPINST
mdefine_line|#define&t;&t;UNDEFFPINST&t;1
multiline_comment|/* Function definitions: opcode, opclass */
DECL|macro|FTEST
mdefine_line|#define FTEST&t;(1&lt;&lt;2) | 0
DECL|macro|FCPY
mdefine_line|#define FCPY&t;(2&lt;&lt;2) | 0
DECL|macro|FABS
mdefine_line|#define FABS&t;(3&lt;&lt;2) | 0
DECL|macro|FSQRT
mdefine_line|#define FSQRT   (4&lt;&lt;2) | 0
DECL|macro|FRND
mdefine_line|#define FRND    (5&lt;&lt;2) | 0
DECL|macro|FCNVFF
mdefine_line|#define FCNVFF&t;(0&lt;&lt;2) | 1
DECL|macro|FCNVXF
mdefine_line|#define FCNVXF&t;(1&lt;&lt;2) | 1
DECL|macro|FCNVFX
mdefine_line|#define FCNVFX&t;(2&lt;&lt;2) | 1
DECL|macro|FCNVFXT
mdefine_line|#define FCNVFXT&t;(3&lt;&lt;2) | 1
DECL|macro|FCMP
mdefine_line|#define FCMP    (0&lt;&lt;2) | 2
DECL|macro|FADD
mdefine_line|#define FADD&t;(0&lt;&lt;2) | 3
DECL|macro|FSUB
mdefine_line|#define FSUB&t;(1&lt;&lt;2) | 3
DECL|macro|FMPY
mdefine_line|#define FMPY&t;(2&lt;&lt;2) | 3
DECL|macro|FDIV
mdefine_line|#define FDIV&t;(3&lt;&lt;2) | 3
DECL|macro|FREM
mdefine_line|#define FREM&t;(4&lt;&lt;2) | 3
eof
