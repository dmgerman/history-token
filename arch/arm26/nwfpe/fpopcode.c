multiline_comment|/*&n;    NetWinder Floating Point Emulator&n;    (c) Rebel.COM, 1998,1999&n;&n;    Direct questions, comments to Scott Bambrough &lt;scottb@netwinder.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &quot;fpa11.h&quot;
macro_line|#include &quot;softfloat.h&quot;
macro_line|#include &quot;fpopcode.h&quot;
macro_line|#include &quot;fpsr.h&quot;
macro_line|#include &quot;fpmodule.h&quot;
macro_line|#include &quot;fpmodule.inl&quot;
DECL|variable|floatx80Constant
r_const
id|floatx80
id|floatx80Constant
(braket
)braket
op_assign
(brace
(brace
l_int|0x0000
comma
l_int|0x0000000000000000ULL
)brace
comma
multiline_comment|/* extended 0.0 */
(brace
l_int|0x3fff
comma
l_int|0x8000000000000000ULL
)brace
comma
multiline_comment|/* extended 1.0 */
(brace
l_int|0x4000
comma
l_int|0x8000000000000000ULL
)brace
comma
multiline_comment|/* extended 2.0 */
(brace
l_int|0x4000
comma
l_int|0xc000000000000000ULL
)brace
comma
multiline_comment|/* extended 3.0 */
(brace
l_int|0x4001
comma
l_int|0x8000000000000000ULL
)brace
comma
multiline_comment|/* extended 4.0 */
(brace
l_int|0x4001
comma
l_int|0xa000000000000000ULL
)brace
comma
multiline_comment|/* extended 5.0 */
(brace
l_int|0x3ffe
comma
l_int|0x8000000000000000ULL
)brace
comma
multiline_comment|/* extended 0.5 */
(brace
l_int|0x4002
comma
l_int|0xa000000000000000ULL
)brace
multiline_comment|/* extended 10.0 */
)brace
suffix:semicolon
DECL|variable|float64Constant
r_const
id|float64
id|float64Constant
(braket
)braket
op_assign
(brace
l_int|0x0000000000000000ULL
comma
multiline_comment|/* double 0.0 */
l_int|0x3ff0000000000000ULL
comma
multiline_comment|/* double 1.0 */
l_int|0x4000000000000000ULL
comma
multiline_comment|/* double 2.0 */
l_int|0x4008000000000000ULL
comma
multiline_comment|/* double 3.0 */
l_int|0x4010000000000000ULL
comma
multiline_comment|/* double 4.0 */
l_int|0x4014000000000000ULL
comma
multiline_comment|/* double 5.0 */
l_int|0x3fe0000000000000ULL
comma
multiline_comment|/* double 0.5 */
l_int|0x4024000000000000ULL
multiline_comment|/* double 10.0 */
)brace
suffix:semicolon
DECL|variable|float32Constant
r_const
id|float32
id|float32Constant
(braket
)braket
op_assign
(brace
l_int|0x00000000
comma
multiline_comment|/* single 0.0 */
l_int|0x3f800000
comma
multiline_comment|/* single 1.0 */
l_int|0x40000000
comma
multiline_comment|/* single 2.0 */
l_int|0x40400000
comma
multiline_comment|/* single 3.0 */
l_int|0x40800000
comma
multiline_comment|/* single 4.0 */
l_int|0x40a00000
comma
multiline_comment|/* single 5.0 */
l_int|0x3f000000
comma
multiline_comment|/* single 0.5 */
l_int|0x41200000
multiline_comment|/* single 10.0 */
)brace
suffix:semicolon
DECL|function|getTransferLength
r_int
r_int
id|getTransferLength
c_func
(paren
r_const
r_int
r_int
id|opcode
)paren
(brace
r_int
r_int
id|nRc
suffix:semicolon
r_switch
c_cond
(paren
id|opcode
op_amp
id|MASK_TRANSFER_LENGTH
)paren
(brace
r_case
l_int|0x00000000
suffix:colon
id|nRc
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* single precision */
r_case
l_int|0x00008000
suffix:colon
id|nRc
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* double precision */
r_case
l_int|0x00400000
suffix:colon
id|nRc
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* extended precision */
r_default
suffix:colon
id|nRc
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|nRc
suffix:semicolon
)brace
DECL|function|getRegisterCount
r_int
r_int
id|getRegisterCount
c_func
(paren
r_const
r_int
r_int
id|opcode
)paren
(brace
r_int
r_int
id|nRc
suffix:semicolon
r_switch
c_cond
(paren
id|opcode
op_amp
id|MASK_REGISTER_COUNT
)paren
(brace
r_case
l_int|0x00000000
suffix:colon
id|nRc
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x00008000
suffix:colon
id|nRc
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x00400000
suffix:colon
id|nRc
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x00408000
suffix:colon
id|nRc
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|nRc
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|nRc
suffix:semicolon
)brace
DECL|function|getRoundingPrecision
r_int
r_int
id|getRoundingPrecision
c_func
(paren
r_const
r_int
r_int
id|opcode
)paren
(brace
r_int
r_int
id|nRc
suffix:semicolon
r_switch
c_cond
(paren
id|opcode
op_amp
id|MASK_ROUNDING_PRECISION
)paren
(brace
r_case
l_int|0x00000000
suffix:colon
id|nRc
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x00000080
suffix:colon
id|nRc
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x00080000
suffix:colon
id|nRc
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|nRc
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|nRc
suffix:semicolon
)brace
DECL|function|getDestinationSize
r_int
r_int
id|getDestinationSize
c_func
(paren
r_const
r_int
r_int
id|opcode
)paren
(brace
r_int
r_int
id|nRc
suffix:semicolon
r_switch
c_cond
(paren
id|opcode
op_amp
id|MASK_DESTINATION_SIZE
)paren
(brace
r_case
l_int|0x00000000
suffix:colon
id|nRc
op_assign
id|typeSingle
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x00000080
suffix:colon
id|nRc
op_assign
id|typeDouble
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x00080000
suffix:colon
id|nRc
op_assign
id|typeExtended
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|nRc
op_assign
id|typeNone
suffix:semicolon
)brace
r_return
id|nRc
suffix:semicolon
)brace
multiline_comment|/* condition code lookup table&n; index into the table is test code: EQ, NE, ... LT, GT, AL, NV&n; bit position in short is condition code: NZCV */
DECL|variable|aCC
r_static
r_const
r_int
r_int
id|aCC
(braket
l_int|16
)braket
op_assign
(brace
l_int|0xF0F0
comma
singleline_comment|// EQ == Z set
l_int|0x0F0F
comma
singleline_comment|// NE
l_int|0xCCCC
comma
singleline_comment|// CS == C set
l_int|0x3333
comma
singleline_comment|// CC
l_int|0xFF00
comma
singleline_comment|// MI == N set
l_int|0x00FF
comma
singleline_comment|// PL
l_int|0xAAAA
comma
singleline_comment|// VS == V set
l_int|0x5555
comma
singleline_comment|// VC
l_int|0x0C0C
comma
singleline_comment|// HI == C set &amp;&amp; Z clear
l_int|0xF3F3
comma
singleline_comment|// LS == C clear || Z set
l_int|0xAA55
comma
singleline_comment|// GE == (N==V)
l_int|0x55AA
comma
singleline_comment|// LT == (N!=V)
l_int|0x0A05
comma
singleline_comment|// GT == (!Z &amp;&amp; (N==V))
l_int|0xF5FA
comma
singleline_comment|// LE == (Z || (N!=V))
l_int|0xFFFF
comma
singleline_comment|// AL always
l_int|0
singleline_comment|// NV
)brace
suffix:semicolon
DECL|function|checkCondition
r_int
r_int
id|checkCondition
c_func
(paren
r_const
r_int
r_int
id|opcode
comma
r_const
r_int
r_int
id|ccodes
)paren
(brace
r_return
(paren
id|aCC
(braket
id|opcode
op_rshift
l_int|28
)braket
op_rshift
(paren
id|ccodes
op_rshift
l_int|28
)paren
)paren
op_amp
l_int|1
suffix:semicolon
)brace
eof
