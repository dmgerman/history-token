multiline_comment|/*&n;    NetWinder Floating Point Emulator&n;    (c) Rebel.com, 1998-1999&n;    (c) Philip Blundell, 1998&n;&n;    Direct questions, comments to Scott Bambrough &lt;scottb@netwinder.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &quot;fpa11.h&quot;
macro_line|#include &quot;softfloat.h&quot;
macro_line|#include &quot;fpopcode.h&quot;
macro_line|#include &quot;fpmodule.h&quot;
macro_line|#include &quot;fpmodule.inl&quot;
macro_line|#include &lt;asm/uaccess.h&gt;
r_static
r_inline
DECL|function|loadSingle
r_void
id|loadSingle
c_func
(paren
r_const
r_int
r_int
id|Fn
comma
r_const
r_int
r_int
op_star
id|pMem
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
id|fpa11-&gt;fType
(braket
id|Fn
)braket
op_assign
id|typeSingle
suffix:semicolon
id|get_user
c_func
(paren
id|fpa11-&gt;fpreg
(braket
id|Fn
)braket
dot
id|fSingle
comma
id|pMem
)paren
suffix:semicolon
)brace
r_static
r_inline
DECL|function|loadDouble
r_void
id|loadDouble
c_func
(paren
r_const
r_int
r_int
id|Fn
comma
r_const
r_int
r_int
op_star
id|pMem
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
r_int
r_int
op_star
id|p
suffix:semicolon
id|p
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|fpa11-&gt;fpreg
(braket
id|Fn
)braket
dot
id|fDouble
suffix:semicolon
id|fpa11-&gt;fType
(braket
id|Fn
)braket
op_assign
id|typeDouble
suffix:semicolon
id|get_user
c_func
(paren
id|p
(braket
l_int|0
)braket
comma
op_amp
id|pMem
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|get_user
c_func
(paren
id|p
(braket
l_int|1
)braket
comma
op_amp
id|pMem
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* sign &amp; exponent */
)brace
r_static
r_inline
DECL|function|loadExtended
r_void
id|loadExtended
c_func
(paren
r_const
r_int
r_int
id|Fn
comma
r_const
r_int
r_int
op_star
id|pMem
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
r_int
r_int
op_star
id|p
suffix:semicolon
id|p
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|fpa11-&gt;fpreg
(braket
id|Fn
)braket
dot
id|fExtended
suffix:semicolon
id|fpa11-&gt;fType
(braket
id|Fn
)braket
op_assign
id|typeExtended
suffix:semicolon
id|get_user
c_func
(paren
id|p
(braket
l_int|0
)braket
comma
op_amp
id|pMem
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* sign &amp; exponent */
id|get_user
c_func
(paren
id|p
(braket
l_int|1
)braket
comma
op_amp
id|pMem
(braket
l_int|2
)braket
)paren
suffix:semicolon
multiline_comment|/* ls bits */
id|get_user
c_func
(paren
id|p
(braket
l_int|2
)braket
comma
op_amp
id|pMem
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* ms bits */
)brace
r_static
r_inline
DECL|function|loadMultiple
r_void
id|loadMultiple
c_func
(paren
r_const
r_int
r_int
id|Fn
comma
r_const
r_int
r_int
op_star
id|pMem
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
r_register
r_int
r_int
op_star
id|p
suffix:semicolon
r_int
r_int
id|x
suffix:semicolon
id|p
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
(paren
id|fpa11-&gt;fpreg
(braket
id|Fn
)braket
)paren
suffix:semicolon
id|get_user
c_func
(paren
id|x
comma
op_amp
id|pMem
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|fpa11-&gt;fType
(braket
id|Fn
)braket
op_assign
(paren
id|x
op_rshift
l_int|14
)paren
op_amp
l_int|0x00000003
suffix:semicolon
r_switch
c_cond
(paren
id|fpa11-&gt;fType
(braket
id|Fn
)braket
)paren
(brace
r_case
id|typeSingle
suffix:colon
r_case
id|typeDouble
suffix:colon
(brace
id|get_user
c_func
(paren
id|p
(braket
l_int|0
)braket
comma
op_amp
id|pMem
(braket
l_int|2
)braket
)paren
suffix:semicolon
multiline_comment|/* Single */
id|get_user
c_func
(paren
id|p
(braket
l_int|1
)braket
comma
op_amp
id|pMem
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* double msw */
id|p
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* empty */
)brace
r_break
suffix:semicolon
r_case
id|typeExtended
suffix:colon
(brace
id|get_user
c_func
(paren
id|p
(braket
l_int|1
)braket
comma
op_amp
id|pMem
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|get_user
c_func
(paren
id|p
(braket
l_int|2
)braket
comma
op_amp
id|pMem
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* msw */
id|p
(braket
l_int|0
)braket
op_assign
(paren
id|x
op_amp
l_int|0x80003fff
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
r_static
r_inline
DECL|function|storeSingle
r_void
id|storeSingle
c_func
(paren
r_const
r_int
r_int
id|Fn
comma
r_int
r_int
op_star
id|pMem
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
r_union
(brace
id|float32
id|f
suffix:semicolon
r_int
r_int
id|i
(braket
l_int|1
)braket
suffix:semicolon
)brace
id|val
suffix:semicolon
r_switch
c_cond
(paren
id|fpa11-&gt;fType
(braket
id|Fn
)braket
)paren
(brace
r_case
id|typeDouble
suffix:colon
id|val.f
op_assign
id|float64_to_float32
c_func
(paren
id|fpa11-&gt;fpreg
(braket
id|Fn
)braket
dot
id|fDouble
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|typeExtended
suffix:colon
id|val.f
op_assign
id|floatx80_to_float32
c_func
(paren
id|fpa11-&gt;fpreg
(braket
id|Fn
)braket
dot
id|fExtended
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|val.f
op_assign
id|fpa11-&gt;fpreg
(braket
id|Fn
)braket
dot
id|fSingle
suffix:semicolon
)brace
id|put_user
c_func
(paren
id|val.i
(braket
l_int|0
)braket
comma
id|pMem
)paren
suffix:semicolon
)brace
r_static
r_inline
DECL|function|storeDouble
r_void
id|storeDouble
c_func
(paren
r_const
r_int
r_int
id|Fn
comma
r_int
r_int
op_star
id|pMem
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
r_union
(brace
id|float64
id|f
suffix:semicolon
r_int
r_int
id|i
(braket
l_int|2
)braket
suffix:semicolon
)brace
id|val
suffix:semicolon
r_switch
c_cond
(paren
id|fpa11-&gt;fType
(braket
id|Fn
)braket
)paren
(brace
r_case
id|typeSingle
suffix:colon
id|val.f
op_assign
id|float32_to_float64
c_func
(paren
id|fpa11-&gt;fpreg
(braket
id|Fn
)braket
dot
id|fSingle
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|typeExtended
suffix:colon
id|val.f
op_assign
id|floatx80_to_float64
c_func
(paren
id|fpa11-&gt;fpreg
(braket
id|Fn
)braket
dot
id|fExtended
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|val.f
op_assign
id|fpa11-&gt;fpreg
(braket
id|Fn
)braket
dot
id|fDouble
suffix:semicolon
)brace
id|put_user
c_func
(paren
id|val.i
(braket
l_int|1
)braket
comma
op_amp
id|pMem
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* msw */
id|put_user
c_func
(paren
id|val.i
(braket
l_int|0
)braket
comma
op_amp
id|pMem
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* lsw */
)brace
r_static
r_inline
DECL|function|storeExtended
r_void
id|storeExtended
c_func
(paren
r_const
r_int
r_int
id|Fn
comma
r_int
r_int
op_star
id|pMem
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
r_union
(brace
id|floatx80
id|f
suffix:semicolon
r_int
r_int
id|i
(braket
l_int|3
)braket
suffix:semicolon
)brace
id|val
suffix:semicolon
r_switch
c_cond
(paren
id|fpa11-&gt;fType
(braket
id|Fn
)braket
)paren
(brace
r_case
id|typeSingle
suffix:colon
id|val.f
op_assign
id|float32_to_floatx80
c_func
(paren
id|fpa11-&gt;fpreg
(braket
id|Fn
)braket
dot
id|fSingle
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|typeDouble
suffix:colon
id|val.f
op_assign
id|float64_to_floatx80
c_func
(paren
id|fpa11-&gt;fpreg
(braket
id|Fn
)braket
dot
id|fDouble
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|val.f
op_assign
id|fpa11-&gt;fpreg
(braket
id|Fn
)braket
dot
id|fExtended
suffix:semicolon
)brace
id|put_user
c_func
(paren
id|val.i
(braket
l_int|0
)braket
comma
op_amp
id|pMem
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* sign &amp; exp */
id|put_user
c_func
(paren
id|val.i
(braket
l_int|1
)braket
comma
op_amp
id|pMem
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|val.i
(braket
l_int|2
)braket
comma
op_amp
id|pMem
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* msw */
)brace
r_static
r_inline
DECL|function|storeMultiple
r_void
id|storeMultiple
c_func
(paren
r_const
r_int
r_int
id|Fn
comma
r_int
r_int
op_star
id|pMem
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
r_register
r_int
r_int
id|nType
comma
op_star
id|p
suffix:semicolon
id|p
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
(paren
id|fpa11-&gt;fpreg
(braket
id|Fn
)braket
)paren
suffix:semicolon
id|nType
op_assign
id|fpa11-&gt;fType
(braket
id|Fn
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
r_case
id|typeDouble
suffix:colon
(brace
id|put_user
c_func
(paren
id|p
(braket
l_int|0
)braket
comma
op_amp
id|pMem
(braket
l_int|2
)braket
)paren
suffix:semicolon
multiline_comment|/* single */
id|put_user
c_func
(paren
id|p
(braket
l_int|1
)braket
comma
op_amp
id|pMem
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* double msw */
id|put_user
c_func
(paren
id|nType
op_lshift
l_int|14
comma
op_amp
id|pMem
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|typeExtended
suffix:colon
(brace
id|put_user
c_func
(paren
id|p
(braket
l_int|2
)braket
comma
op_amp
id|pMem
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* msw */
id|put_user
c_func
(paren
id|p
(braket
l_int|1
)braket
comma
op_amp
id|pMem
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|put_user
c_func
(paren
(paren
id|p
(braket
l_int|0
)braket
op_amp
l_int|0x80003fff
)paren
op_or
(paren
id|nType
op_lshift
l_int|14
)paren
comma
op_amp
id|pMem
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
DECL|function|PerformLDF
r_int
r_int
id|PerformLDF
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
op_star
id|pBase
comma
op_star
id|pAddress
comma
op_star
id|pFinal
comma
id|nRc
op_assign
l_int|1
comma
id|write_back
op_assign
id|WRITE_BACK
c_func
(paren
id|opcode
)paren
suffix:semicolon
singleline_comment|//printk(&quot;PerformLDF(0x%08x), Fd = 0x%08x&bslash;n&quot;,opcode,getFd(opcode));
id|pBase
op_assign
(paren
r_int
r_int
op_star
)paren
id|readRegister
c_func
(paren
id|getRn
c_func
(paren
id|opcode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|REG_PC
op_eq
id|getRn
c_func
(paren
id|opcode
)paren
)paren
(brace
id|pBase
op_add_assign
l_int|2
suffix:semicolon
id|write_back
op_assign
l_int|0
suffix:semicolon
)brace
id|pFinal
op_assign
id|pBase
suffix:semicolon
r_if
c_cond
(paren
id|BIT_UP_SET
c_func
(paren
id|opcode
)paren
)paren
id|pFinal
op_add_assign
id|getOffset
c_func
(paren
id|opcode
)paren
suffix:semicolon
r_else
id|pFinal
op_sub_assign
id|getOffset
c_func
(paren
id|opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PREINDEXED
c_func
(paren
id|opcode
)paren
)paren
id|pAddress
op_assign
id|pFinal
suffix:semicolon
r_else
id|pAddress
op_assign
id|pBase
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
id|TRANSFER_SINGLE
suffix:colon
id|loadSingle
c_func
(paren
id|getFd
c_func
(paren
id|opcode
)paren
comma
id|pAddress
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TRANSFER_DOUBLE
suffix:colon
id|loadDouble
c_func
(paren
id|getFd
c_func
(paren
id|opcode
)paren
comma
id|pAddress
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TRANSFER_EXTENDED
suffix:colon
id|loadExtended
c_func
(paren
id|getFd
c_func
(paren
id|opcode
)paren
comma
id|pAddress
)paren
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
r_if
c_cond
(paren
id|write_back
)paren
id|writeRegister
c_func
(paren
id|getRn
c_func
(paren
id|opcode
)paren
comma
(paren
r_int
r_int
)paren
id|pFinal
)paren
suffix:semicolon
r_return
id|nRc
suffix:semicolon
)brace
DECL|function|PerformSTF
r_int
r_int
id|PerformSTF
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
op_star
id|pBase
comma
op_star
id|pAddress
comma
op_star
id|pFinal
comma
id|nRc
op_assign
l_int|1
comma
id|write_back
op_assign
id|WRITE_BACK
c_func
(paren
id|opcode
)paren
suffix:semicolon
singleline_comment|//printk(&quot;PerformSTF(0x%08x), Fd = 0x%08x&bslash;n&quot;,opcode,getFd(opcode));
id|SetRoundingMode
c_func
(paren
id|ROUND_TO_NEAREST
)paren
suffix:semicolon
id|pBase
op_assign
(paren
r_int
r_int
op_star
)paren
id|readRegister
c_func
(paren
id|getRn
c_func
(paren
id|opcode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|REG_PC
op_eq
id|getRn
c_func
(paren
id|opcode
)paren
)paren
(brace
id|pBase
op_add_assign
l_int|2
suffix:semicolon
id|write_back
op_assign
l_int|0
suffix:semicolon
)brace
id|pFinal
op_assign
id|pBase
suffix:semicolon
r_if
c_cond
(paren
id|BIT_UP_SET
c_func
(paren
id|opcode
)paren
)paren
id|pFinal
op_add_assign
id|getOffset
c_func
(paren
id|opcode
)paren
suffix:semicolon
r_else
id|pFinal
op_sub_assign
id|getOffset
c_func
(paren
id|opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PREINDEXED
c_func
(paren
id|opcode
)paren
)paren
id|pAddress
op_assign
id|pFinal
suffix:semicolon
r_else
id|pAddress
op_assign
id|pBase
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
id|TRANSFER_SINGLE
suffix:colon
id|storeSingle
c_func
(paren
id|getFd
c_func
(paren
id|opcode
)paren
comma
id|pAddress
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TRANSFER_DOUBLE
suffix:colon
id|storeDouble
c_func
(paren
id|getFd
c_func
(paren
id|opcode
)paren
comma
id|pAddress
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TRANSFER_EXTENDED
suffix:colon
id|storeExtended
c_func
(paren
id|getFd
c_func
(paren
id|opcode
)paren
comma
id|pAddress
)paren
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
r_if
c_cond
(paren
id|write_back
)paren
id|writeRegister
c_func
(paren
id|getRn
c_func
(paren
id|opcode
)paren
comma
(paren
r_int
r_int
)paren
id|pFinal
)paren
suffix:semicolon
r_return
id|nRc
suffix:semicolon
)brace
DECL|function|PerformLFM
r_int
r_int
id|PerformLFM
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
id|i
comma
id|Fd
comma
op_star
id|pBase
comma
op_star
id|pAddress
comma
op_star
id|pFinal
comma
id|write_back
op_assign
id|WRITE_BACK
c_func
(paren
id|opcode
)paren
suffix:semicolon
id|pBase
op_assign
(paren
r_int
r_int
op_star
)paren
id|readRegister
c_func
(paren
id|getRn
c_func
(paren
id|opcode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|REG_PC
op_eq
id|getRn
c_func
(paren
id|opcode
)paren
)paren
(brace
id|pBase
op_add_assign
l_int|2
suffix:semicolon
id|write_back
op_assign
l_int|0
suffix:semicolon
)brace
id|pFinal
op_assign
id|pBase
suffix:semicolon
r_if
c_cond
(paren
id|BIT_UP_SET
c_func
(paren
id|opcode
)paren
)paren
id|pFinal
op_add_assign
id|getOffset
c_func
(paren
id|opcode
)paren
suffix:semicolon
r_else
id|pFinal
op_sub_assign
id|getOffset
c_func
(paren
id|opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PREINDEXED
c_func
(paren
id|opcode
)paren
)paren
id|pAddress
op_assign
id|pFinal
suffix:semicolon
r_else
id|pAddress
op_assign
id|pBase
suffix:semicolon
id|Fd
op_assign
id|getFd
c_func
(paren
id|opcode
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|getRegisterCount
c_func
(paren
id|opcode
)paren
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|loadMultiple
c_func
(paren
id|Fd
comma
id|pAddress
)paren
suffix:semicolon
id|pAddress
op_add_assign
l_int|3
suffix:semicolon
id|Fd
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|Fd
op_eq
l_int|8
)paren
id|Fd
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write_back
)paren
id|writeRegister
c_func
(paren
id|getRn
c_func
(paren
id|opcode
)paren
comma
(paren
r_int
r_int
)paren
id|pFinal
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|PerformSFM
r_int
r_int
id|PerformSFM
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
id|i
comma
id|Fd
comma
op_star
id|pBase
comma
op_star
id|pAddress
comma
op_star
id|pFinal
comma
id|write_back
op_assign
id|WRITE_BACK
c_func
(paren
id|opcode
)paren
suffix:semicolon
id|pBase
op_assign
(paren
r_int
r_int
op_star
)paren
id|readRegister
c_func
(paren
id|getRn
c_func
(paren
id|opcode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|REG_PC
op_eq
id|getRn
c_func
(paren
id|opcode
)paren
)paren
(brace
id|pBase
op_add_assign
l_int|2
suffix:semicolon
id|write_back
op_assign
l_int|0
suffix:semicolon
)brace
id|pFinal
op_assign
id|pBase
suffix:semicolon
r_if
c_cond
(paren
id|BIT_UP_SET
c_func
(paren
id|opcode
)paren
)paren
id|pFinal
op_add_assign
id|getOffset
c_func
(paren
id|opcode
)paren
suffix:semicolon
r_else
id|pFinal
op_sub_assign
id|getOffset
c_func
(paren
id|opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PREINDEXED
c_func
(paren
id|opcode
)paren
)paren
id|pAddress
op_assign
id|pFinal
suffix:semicolon
r_else
id|pAddress
op_assign
id|pBase
suffix:semicolon
id|Fd
op_assign
id|getFd
c_func
(paren
id|opcode
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|getRegisterCount
c_func
(paren
id|opcode
)paren
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|storeMultiple
c_func
(paren
id|Fd
comma
id|pAddress
)paren
suffix:semicolon
id|pAddress
op_add_assign
l_int|3
suffix:semicolon
id|Fd
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|Fd
op_eq
l_int|8
)paren
id|Fd
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write_back
)paren
id|writeRegister
c_func
(paren
id|getRn
c_func
(paren
id|opcode
)paren
comma
(paren
r_int
r_int
)paren
id|pFinal
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#if 1
DECL|function|EmulateCPDT
r_int
r_int
id|EmulateCPDT
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
op_assign
l_int|0
suffix:semicolon
singleline_comment|//printk(&quot;EmulateCPDT(0x%08x)&bslash;n&quot;,opcode);
r_if
c_cond
(paren
id|LDF_OP
c_func
(paren
id|opcode
)paren
)paren
(brace
id|nRc
op_assign
id|PerformLDF
c_func
(paren
id|opcode
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|LFM_OP
c_func
(paren
id|opcode
)paren
)paren
(brace
id|nRc
op_assign
id|PerformLFM
c_func
(paren
id|opcode
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|STF_OP
c_func
(paren
id|opcode
)paren
)paren
(brace
id|nRc
op_assign
id|PerformSTF
c_func
(paren
id|opcode
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|SFM_OP
c_func
(paren
id|opcode
)paren
)paren
(brace
id|nRc
op_assign
id|PerformSFM
c_func
(paren
id|opcode
)paren
suffix:semicolon
)brace
r_else
(brace
id|nRc
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|nRc
suffix:semicolon
)brace
macro_line|#endif
eof
