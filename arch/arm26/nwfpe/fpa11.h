multiline_comment|/*&n;    NetWinder Floating Point Emulator&n;    (c) Rebel.com, 1998-1999&n;    &n;    Direct questions, comments to Scott Bambrough &lt;scottb@netwinder.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef __FPA11_H__
DECL|macro|__FPA11_H__
mdefine_line|#define __FPA11_H__
DECL|macro|GET_FPA11
mdefine_line|#define GET_FPA11() ((FPA11 *)(&amp;current_thread_info()-&gt;fpstate))
multiline_comment|/*&n; * The processes registers are always at the very top of the 8K&n; * stack+task struct.  Use the same method as &squot;current&squot; uses to&n; * reach them.&n; */
r_register
r_int
r_int
op_star
id|user_registers
id|asm
c_func
(paren
l_string|&quot;sl&quot;
)paren
suffix:semicolon
DECL|macro|GET_USERREG
mdefine_line|#define GET_USERREG() (user_registers)
macro_line|#include &lt;linux/thread_info.h&gt;
multiline_comment|/* includes */
macro_line|#include &quot;fpsr.h&quot;&t;&t;/* FP control and status register definitions */
macro_line|#include &quot;softfloat.h&quot;
DECL|macro|typeNone
mdefine_line|#define&t;&t;typeNone&t;&t;0x00
DECL|macro|typeSingle
mdefine_line|#define&t;&t;typeSingle&t;&t;0x01
DECL|macro|typeDouble
mdefine_line|#define&t;&t;typeDouble&t;&t;0x02
DECL|macro|typeExtended
mdefine_line|#define&t;&t;typeExtended&t;&t;0x03
multiline_comment|/*&n; * This must be no more and no less than 12 bytes.&n; */
DECL|union|tagFPREG
r_typedef
r_union
id|tagFPREG
(brace
DECL|member|fExtended
id|floatx80
id|fExtended
suffix:semicolon
DECL|member|fDouble
id|float64
id|fDouble
suffix:semicolon
DECL|member|fSingle
id|float32
id|fSingle
suffix:semicolon
DECL|typedef|FPREG
)brace
id|FPREG
suffix:semicolon
multiline_comment|/*&n; * FPA11 device model.&n; *&n; * This structure is exported to user space.  Do not re-order.&n; * Only add new stuff to the end, and do not change the size of&n; * any element.  Elements of this structure are used by user&n; * space, and must match struct user_fp in include/asm-arm/user.h.&n; * We include the byte offsets below for documentation purposes.&n; *&n; * The size of this structure and FPREG are checked by fpmodule.c&n; * on initialisation.  If the rules have been broken, NWFPE will&n; * not initialise.&n; */
DECL|struct|tagFPA11
r_typedef
r_struct
id|tagFPA11
(brace
DECL|member|fpreg
multiline_comment|/*   0 */
id|FPREG
id|fpreg
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 8 floating point registers */
DECL|member|fpsr
multiline_comment|/*  96 */
id|FPSR
id|fpsr
suffix:semicolon
multiline_comment|/* floating point status register */
DECL|member|fpcr
multiline_comment|/* 100 */
id|FPCR
id|fpcr
suffix:semicolon
multiline_comment|/* floating point control register */
DECL|member|fType
multiline_comment|/* 104 */
r_int
r_char
id|fType
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* type of floating point value held in&n;&t;&t;&t;&t;&t;   floating point registers.  One of none&n;&t;&t;&t;&t;&t;   single, double or extended. */
DECL|member|initflag
multiline_comment|/* 112 */
r_int
id|initflag
suffix:semicolon
multiline_comment|/* this is special.  The kernel guarantees&n;&t;&t;&t;&t;&t;   to set it to 0 when a thread is launched,&n;&t;&t;&t;&t;&t;   so we can use it to detect whether this&n;&t;&t;&t;&t;&t;   instance of the emulator needs to be&n;&t;&t;&t;&t;&t;   initialised. */
DECL|typedef|FPA11
)brace
id|FPA11
suffix:semicolon
r_extern
r_void
id|resetFPA11
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|SetRoundingMode
c_func
(paren
r_const
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|SetRoundingPrecision
c_func
(paren
r_const
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
eof
