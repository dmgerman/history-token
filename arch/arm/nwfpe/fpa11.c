multiline_comment|/*&n;    NetWinder Floating Point Emulator&n;    (c) Rebel.COM, 1998,1999&n;&n;    Direct questions, comments to Scott Bambrough &lt;scottb@netwinder.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &quot;fpa11.h&quot;
macro_line|#include &quot;fpopcode.h&quot;
macro_line|#include &quot;fpmodule.h&quot;
macro_line|#include &quot;fpmodule.inl&quot;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/* forward declarations */
r_int
r_int
id|EmulateCPDO
c_func
(paren
r_const
r_int
r_int
)paren
suffix:semicolon
r_int
r_int
id|EmulateCPDT
c_func
(paren
r_const
r_int
r_int
)paren
suffix:semicolon
r_int
r_int
id|EmulateCPRT
c_func
(paren
r_const
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* Reset the FPA11 chip.  Called to initialize and reset the emulator. */
DECL|function|resetFPA11
r_static
r_void
id|resetFPA11
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|FPA11
op_star
id|fpa11
op_assign
id|GET_FPA11
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* initialize the register type array */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
l_int|7
suffix:semicolon
id|i
op_increment
)paren
(brace
id|fpa11-&gt;fType
(braket
id|i
)braket
op_assign
id|typeNone
suffix:semicolon
)brace
multiline_comment|/* FPSR: set system id to FP_EMULATOR, set AC, clear all other bits */
id|fpa11-&gt;fpsr
op_assign
id|FP_EMULATOR
op_or
id|BIT_AC
suffix:semicolon
)brace
DECL|function|SetRoundingMode
r_void
id|SetRoundingMode
c_func
(paren
r_const
r_int
r_int
id|opcode
)paren
(brace
r_switch
c_cond
(paren
id|opcode
op_amp
id|MASK_ROUNDING_MODE
)paren
(brace
r_default
suffix:colon
r_case
id|ROUND_TO_NEAREST
suffix:colon
id|float_rounding_mode
op_assign
id|float_round_nearest_even
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUND_TO_PLUS_INFINITY
suffix:colon
id|float_rounding_mode
op_assign
id|float_round_up
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUND_TO_MINUS_INFINITY
suffix:colon
id|float_rounding_mode
op_assign
id|float_round_down
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUND_TO_ZERO
suffix:colon
id|float_rounding_mode
op_assign
id|float_round_to_zero
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|SetRoundingPrecision
r_void
id|SetRoundingPrecision
c_func
(paren
r_const
r_int
r_int
id|opcode
)paren
(brace
r_switch
c_cond
(paren
id|opcode
op_amp
id|MASK_ROUNDING_PRECISION
)paren
(brace
r_case
id|ROUND_SINGLE
suffix:colon
id|floatx80_rounding_precision
op_assign
l_int|32
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUND_DOUBLE
suffix:colon
id|floatx80_rounding_precision
op_assign
l_int|64
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUND_EXTENDED
suffix:colon
id|floatx80_rounding_precision
op_assign
l_int|80
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|floatx80_rounding_precision
op_assign
l_int|80
suffix:semicolon
)brace
)brace
DECL|function|nwfpe_init
r_void
id|nwfpe_init
c_func
(paren
r_union
id|fp_state
op_star
id|fp
)paren
(brace
id|FPA11
op_star
id|fpa11
op_assign
(paren
id|FPA11
op_star
)paren
id|fp
suffix:semicolon
id|memset
c_func
(paren
id|fpa11
comma
l_int|0
comma
r_sizeof
(paren
id|FPA11
)paren
)paren
suffix:semicolon
id|resetFPA11
c_func
(paren
)paren
suffix:semicolon
id|SetRoundingMode
c_func
(paren
id|ROUND_TO_NEAREST
)paren
suffix:semicolon
id|SetRoundingPrecision
c_func
(paren
id|ROUND_EXTENDED
)paren
suffix:semicolon
id|fpa11-&gt;initflag
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Emulate the instruction in the opcode. */
DECL|function|EmulateAll
r_int
r_int
id|EmulateAll
c_func
(paren
r_int
r_int
id|opcode
)paren
(brace
r_int
r_int
id|nRc
op_assign
l_int|1
comma
id|code
suffix:semicolon
id|code
op_assign
id|opcode
op_amp
l_int|0x00000f00
suffix:semicolon
r_if
c_cond
(paren
id|code
op_eq
l_int|0x00000100
op_logical_or
id|code
op_eq
l_int|0x00000200
)paren
(brace
multiline_comment|/* For coprocessor 1 or 2 (FPA11) */
id|code
op_assign
id|opcode
op_amp
l_int|0x0e000000
suffix:semicolon
r_if
c_cond
(paren
id|code
op_eq
l_int|0x0e000000
)paren
(brace
r_if
c_cond
(paren
id|opcode
op_amp
l_int|0x00000010
)paren
(brace
multiline_comment|/* Emulate conversion opcodes. */
multiline_comment|/* Emulate register transfer opcodes. */
multiline_comment|/* Emulate comparison opcodes. */
id|nRc
op_assign
id|EmulateCPRT
c_func
(paren
id|opcode
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Emulate monadic arithmetic opcodes. */
multiline_comment|/* Emulate dyadic arithmetic opcodes. */
id|nRc
op_assign
id|EmulateCPDO
c_func
(paren
id|opcode
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|code
op_eq
l_int|0x0c000000
)paren
(brace
multiline_comment|/* Emulate load/store opcodes. */
multiline_comment|/* Emulate load/store multiple opcodes. */
id|nRc
op_assign
id|EmulateCPDT
c_func
(paren
id|opcode
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Invalid instruction detected.  Return FALSE. */
id|nRc
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_return
(paren
id|nRc
)paren
suffix:semicolon
)brace
eof
