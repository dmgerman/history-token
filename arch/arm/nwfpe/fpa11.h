multiline_comment|/*&n;    NetWinder Floating Point Emulator&n;    (c) Rebel.com, 1998-1999&n;    &n;    Direct questions, comments to Scott Bambrough &lt;scottb@netwinder.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef __FPA11_H__
DECL|macro|__FPA11_H__
mdefine_line|#define __FPA11_H__
multiline_comment|/* includes */
macro_line|#include &quot;fpsr.h&quot;&t;&t;/* FP control and status register definitions */
macro_line|#include &quot;softfloat.h&quot;
multiline_comment|/* Need task_struct */
macro_line|#include &lt;linux/sched.h&gt;
DECL|macro|typeNone
mdefine_line|#define&t;&t;typeNone&t;&t;0x00
DECL|macro|typeSingle
mdefine_line|#define&t;&t;typeSingle&t;&t;0x01
DECL|macro|typeDouble
mdefine_line|#define&t;&t;typeDouble&t;&t;0x02
DECL|macro|typeExtended
mdefine_line|#define&t;&t;typeExtended&t;&t;0x03
DECL|union|tagFPREG
r_typedef
r_union
id|tagFPREG
(brace
DECL|member|fSingle
id|float32
id|fSingle
suffix:semicolon
DECL|member|fDouble
id|float64
id|fDouble
suffix:semicolon
DECL|member|fExtended
id|floatx80
id|fExtended
suffix:semicolon
DECL|typedef|FPREG
)brace
id|FPREG
suffix:semicolon
multiline_comment|/* FPA11 device model */
DECL|struct|tagFPA11
r_typedef
r_struct
id|tagFPA11
(brace
DECL|member|userRegisters
r_int
r_int
op_star
id|userRegisters
suffix:semicolon
DECL|member|fpreg
id|FPREG
id|fpreg
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 8 floating point registers */
DECL|member|fpsr
id|FPSR
id|fpsr
suffix:semicolon
multiline_comment|/* floating point status register */
DECL|member|fpcr
id|FPCR
id|fpcr
suffix:semicolon
multiline_comment|/* floating point control register */
DECL|member|fType
r_int
r_char
id|fType
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* type of floating point value held in&n;&t;&t;&t;&t;   floating point registers.  One of none&n;&t;&t;&t;&t;   single, double or extended. */
DECL|member|initflag
r_int
id|initflag
suffix:semicolon
multiline_comment|/* this is special.  The kernel guarantees&n;&t;&t;&t;&t;   to set it to 0 when a thread is launched,&n;&t;&t;&t;&t;   so we can use it to detect whether this&n;&t;&t;&t;&t;   instance of the emulator needs to be&n;&t;&t;&t;&t;   initialised. */
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
DECL|macro|GET_FPA11
mdefine_line|#define GET_FPA11() ((FPA11 *)(&amp;current-&gt;thread.fpstate))
DECL|macro|GET_USERREG
mdefine_line|#define GET_USERREG() (GET_FPA11()-&gt;userRegisters)
macro_line|#endif
eof
