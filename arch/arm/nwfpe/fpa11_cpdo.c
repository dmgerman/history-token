multiline_comment|/*&n;    NetWinder Floating Point Emulator&n;    (c) Rebel.COM, 1998,1999&n;    (c) Philip Blundell, 2001&n;&n;    Direct questions, comments to Scott Bambrough &lt;scottb@netwinder.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;fpa11.h&quot;
macro_line|#include &quot;fpopcode.h&quot;
r_int
r_int
id|SingleCPDO
c_func
(paren
r_const
r_int
r_int
id|opcode
comma
id|FPREG
op_star
id|rFd
)paren
suffix:semicolon
r_int
r_int
id|DoubleCPDO
c_func
(paren
r_const
r_int
r_int
id|opcode
comma
id|FPREG
op_star
id|rFd
)paren
suffix:semicolon
r_int
r_int
id|ExtendedCPDO
c_func
(paren
r_const
r_int
r_int
id|opcode
comma
id|FPREG
op_star
id|rFd
)paren
suffix:semicolon
DECL|function|EmulateCPDO
r_int
r_int
id|EmulateCPDO
c_func
(paren
r_const
r_int
r_int
id|opcode
)paren
(brace
id|FPA11
op_star
id|fpa11
op_assign
id|GET_FPA11
c_func
(paren
)paren
suffix:semicolon
id|FPREG
op_star
id|rFd
suffix:semicolon
r_int
r_int
id|nType
comma
id|nDest
comma
id|nRc
suffix:semicolon
multiline_comment|/* Get the destination size.  If not valid let Linux perform&n;&t;   an invalid instruction trap. */
id|nDest
op_assign
id|getDestinationSize
c_func
(paren
id|opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|typeNone
op_eq
id|nDest
)paren
r_return
l_int|0
suffix:semicolon
id|SetRoundingMode
c_func
(paren
id|opcode
)paren
suffix:semicolon
multiline_comment|/* Compare the size of the operands in Fn and Fm.&n;&t;   Choose the largest size and perform operations in that size,&n;&t;   in order to make use of all the precision of the operands.&n;&t;   If Fm is a constant, we just grab a constant of a size&n;&t;   matching the size of the operand in Fn. */
r_if
c_cond
(paren
id|MONADIC_INSTRUCTION
c_func
(paren
id|opcode
)paren
)paren
id|nType
op_assign
id|nDest
suffix:semicolon
r_else
id|nType
op_assign
id|fpa11-&gt;fType
(braket
id|getFn
c_func
(paren
id|opcode
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|CONSTANT_FM
c_func
(paren
id|opcode
)paren
)paren
(brace
r_register
r_int
r_int
id|Fm
op_assign
id|getFm
c_func
(paren
id|opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nType
OL
id|fpa11-&gt;fType
(braket
id|Fm
)braket
)paren
(brace
id|nType
op_assign
id|fpa11-&gt;fType
(braket
id|Fm
)braket
suffix:semicolon
)brace
)brace
id|rFd
op_assign
op_amp
id|fpa11-&gt;fpreg
(braket
id|getFd
c_func
(paren
id|opcode
)paren
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|nType
)paren
(brace
r_case
id|typeSingle
suffix:colon
id|nRc
op_assign
id|SingleCPDO
c_func
(paren
id|opcode
comma
id|rFd
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|typeDouble
suffix:colon
id|nRc
op_assign
id|DoubleCPDO
c_func
(paren
id|opcode
comma
id|rFd
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_FPE_NWFPE_XP
r_case
id|typeExtended
suffix:colon
id|nRc
op_assign
id|ExtendedCPDO
c_func
(paren
id|opcode
comma
id|rFd
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|nRc
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* The CPDO functions used to always set the destination type&n;&t;   to be the same as their working size. */
r_if
c_cond
(paren
id|nRc
op_ne
l_int|0
)paren
(brace
multiline_comment|/* If the operation succeeded, check to see if the result in the&n;&t;&t;   destination register is the correct size.  If not force it&n;&t;&t;   to be. */
id|fpa11-&gt;fType
(braket
id|getFd
c_func
(paren
id|opcode
)paren
)braket
op_assign
id|nDest
suffix:semicolon
macro_line|#ifdef CONFIG_FPE_NWFPE_XP
r_if
c_cond
(paren
id|nDest
op_ne
id|nType
)paren
(brace
r_switch
c_cond
(paren
id|nDest
)paren
(brace
r_case
id|typeSingle
suffix:colon
(brace
r_if
c_cond
(paren
id|typeDouble
op_eq
id|nType
)paren
id|rFd-&gt;fSingle
op_assign
id|float64_to_float32
c_func
(paren
id|rFd-&gt;fDouble
)paren
suffix:semicolon
r_else
id|rFd-&gt;fSingle
op_assign
id|floatx80_to_float32
c_func
(paren
id|rFd-&gt;fExtended
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|typeDouble
suffix:colon
(brace
r_if
c_cond
(paren
id|typeSingle
op_eq
id|nType
)paren
id|rFd-&gt;fDouble
op_assign
id|float32_to_float64
c_func
(paren
id|rFd-&gt;fSingle
)paren
suffix:semicolon
r_else
id|rFd-&gt;fDouble
op_assign
id|floatx80_to_float64
c_func
(paren
id|rFd-&gt;fExtended
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|typeExtended
suffix:colon
(brace
r_if
c_cond
(paren
id|typeSingle
op_eq
id|nType
)paren
id|rFd-&gt;fExtended
op_assign
id|float32_to_floatx80
c_func
(paren
id|rFd-&gt;fSingle
)paren
suffix:semicolon
r_else
id|rFd-&gt;fExtended
op_assign
id|float64_to_floatx80
c_func
(paren
id|rFd-&gt;fDouble
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
macro_line|#else
r_if
c_cond
(paren
id|nDest
op_ne
id|nType
)paren
(brace
r_if
c_cond
(paren
id|nDest
op_eq
id|typeSingle
)paren
id|rFd-&gt;fSingle
op_assign
id|float64_to_float32
c_func
(paren
id|rFd-&gt;fDouble
)paren
suffix:semicolon
r_else
id|rFd-&gt;fDouble
op_assign
id|float32_to_float64
c_func
(paren
id|rFd-&gt;fSingle
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_return
id|nRc
suffix:semicolon
)brace
eof
