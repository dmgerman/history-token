multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* i2c-algo-sibyte.c i2c driver algorithms for bit-shift adapters&t;&t;     */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*   Copyright (C) 2001,2002,2003 Broadcom Corporation&n;     Copyright (C) 1995-2000 Simon G. Vogl&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&t;&t;     */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* With some changes from Ky&#xfffd;sti M&#xfffd;lkki &lt;kmalkki@cc.hut.fi&gt; and even&n;   Frodo Looijaard &lt;frodol@dds.nl&gt;.  */
multiline_comment|/* Ported for SiByte SOCs by Broadcom Corporation.  */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_regs.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_smbus.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-sibyte.h&gt;
multiline_comment|/* ----- global defines ----------------------------------------------- */
DECL|macro|SMB_CSR
mdefine_line|#define SMB_CSR(a,r) ((long)(a-&gt;reg_base + r))
multiline_comment|/* ----- global variables ---------------------------------------------&t;*/
multiline_comment|/* module parameters:&n; */
DECL|variable|bit_scan
r_static
r_int
id|bit_scan
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* have a look at what&squot;s hanging &squot;round&t;&t;*/
DECL|function|smbus_xfer
r_static
r_int
id|smbus_xfer
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|i2c_adap
comma
id|u16
id|addr
comma
r_int
r_int
id|flags
comma
r_char
id|read_write
comma
id|u8
id|command
comma
r_int
id|size
comma
r_union
id|i2c_smbus_data
op_star
id|data
)paren
(brace
r_struct
id|i2c_algo_sibyte_data
op_star
id|adap
op_assign
id|i2c_adap-&gt;algo_data
suffix:semicolon
r_int
id|data_bytes
op_assign
l_int|0
suffix:semicolon
r_int
id|error
suffix:semicolon
r_while
c_loop
(paren
id|csr_in32
c_func
(paren
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_STATUS
)paren
)paren
op_amp
id|M_SMB_BUSY
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
id|I2C_SMBUS_QUICK
suffix:colon
id|csr_out32
c_func
(paren
(paren
id|V_SMB_ADDR
c_func
(paren
id|addr
)paren
op_or
(paren
id|read_write
op_eq
id|I2C_SMBUS_READ
ques
c_cond
id|M_SMB_QDATA
suffix:colon
l_int|0
)paren
op_or
id|V_SMB_TT_QUICKCMD
)paren
comma
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_START
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE
suffix:colon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_READ
)paren
(brace
id|csr_out32
c_func
(paren
(paren
id|V_SMB_ADDR
c_func
(paren
id|addr
)paren
op_or
id|V_SMB_TT_RD1BYTE
)paren
comma
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_START
)paren
)paren
suffix:semicolon
id|data_bytes
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|csr_out32
c_func
(paren
id|V_SMB_CMD
c_func
(paren
id|command
)paren
comma
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_CMD
)paren
)paren
suffix:semicolon
id|csr_out32
c_func
(paren
(paren
id|V_SMB_ADDR
c_func
(paren
id|addr
)paren
op_or
id|V_SMB_TT_WR1BYTE
)paren
comma
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_START
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE_DATA
suffix:colon
id|csr_out32
c_func
(paren
id|V_SMB_CMD
c_func
(paren
id|command
)paren
comma
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_CMD
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_READ
)paren
(brace
id|csr_out32
c_func
(paren
(paren
id|V_SMB_ADDR
c_func
(paren
id|addr
)paren
op_or
id|V_SMB_TT_CMD_RD1BYTE
)paren
comma
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_START
)paren
)paren
suffix:semicolon
id|data_bytes
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|csr_out32
c_func
(paren
id|V_SMB_LB
c_func
(paren
id|data-&gt;byte
)paren
comma
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_DATA
)paren
)paren
suffix:semicolon
id|csr_out32
c_func
(paren
(paren
id|V_SMB_ADDR
c_func
(paren
id|addr
)paren
op_or
id|V_SMB_TT_WR2BYTE
)paren
comma
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_START
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_WORD_DATA
suffix:colon
id|csr_out32
c_func
(paren
id|V_SMB_CMD
c_func
(paren
id|command
)paren
comma
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_CMD
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_READ
)paren
(brace
id|csr_out32
c_func
(paren
(paren
id|V_SMB_ADDR
c_func
(paren
id|addr
)paren
op_or
id|V_SMB_TT_CMD_RD2BYTE
)paren
comma
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_START
)paren
)paren
suffix:semicolon
id|data_bytes
op_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
id|csr_out32
c_func
(paren
id|V_SMB_LB
c_func
(paren
id|data-&gt;word
op_amp
l_int|0xff
)paren
comma
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_DATA
)paren
)paren
suffix:semicolon
id|csr_out32
c_func
(paren
id|V_SMB_MB
c_func
(paren
id|data-&gt;word
op_rshift
l_int|8
)paren
comma
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_DATA
)paren
)paren
suffix:semicolon
id|csr_out32
c_func
(paren
(paren
id|V_SMB_ADDR
c_func
(paren
id|addr
)paren
op_or
id|V_SMB_TT_WR2BYTE
)paren
comma
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_START
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* XXXKW better error code? */
)brace
r_while
c_loop
(paren
id|csr_in32
c_func
(paren
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_STATUS
)paren
)paren
op_amp
id|M_SMB_BUSY
)paren
suffix:semicolon
id|error
op_assign
id|csr_in32
c_func
(paren
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_STATUS
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_amp
id|M_SMB_ERROR
)paren
(brace
multiline_comment|/* Clear error bit by writing a 1 */
id|csr_out32
c_func
(paren
id|M_SMB_ERROR
comma
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_STATUS
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* XXXKW better error code? */
)brace
r_if
c_cond
(paren
id|data_bytes
op_eq
l_int|1
)paren
id|data-&gt;byte
op_assign
id|csr_in32
c_func
(paren
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_DATA
)paren
)paren
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|data_bytes
op_eq
l_int|2
)paren
id|data-&gt;word
op_assign
id|csr_in32
c_func
(paren
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_DATA
)paren
)paren
op_amp
l_int|0xffff
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|algo_control
r_static
r_int
id|algo_control
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bit_func
r_static
id|u32
id|bit_func
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_return
(paren
id|I2C_FUNC_SMBUS_QUICK
op_or
id|I2C_FUNC_SMBUS_BYTE
op_or
id|I2C_FUNC_SMBUS_BYTE_DATA
op_or
id|I2C_FUNC_SMBUS_WORD_DATA
)paren
suffix:semicolon
)brace
multiline_comment|/* -----exported algorithm data: -------------------------------------&t;*/
DECL|variable|i2c_sibyte_algo
r_static
r_struct
id|i2c_algorithm
id|i2c_sibyte_algo
op_assign
(brace
l_string|&quot;SiByte algorithm&quot;
comma
id|I2C_ALGO_SIBYTE
comma
l_int|NULL
comma
multiline_comment|/* master_xfer          */
id|smbus_xfer
comma
multiline_comment|/* smbus_xfer           */
l_int|NULL
comma
multiline_comment|/* slave_xmit&t;&t;*/
l_int|NULL
comma
multiline_comment|/* slave_recv&t;&t;*/
id|algo_control
comma
multiline_comment|/* ioctl&t;&t;*/
id|bit_func
comma
multiline_comment|/* functionality&t;*/
)brace
suffix:semicolon
multiline_comment|/* &n; * registering functions to load algorithms at runtime &n; */
DECL|function|i2c_sibyte_add_bus
r_int
id|i2c_sibyte_add_bus
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|i2c_adap
comma
r_int
id|speed
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|i2c_algo_sibyte_data
op_star
id|adap
op_assign
id|i2c_adap-&gt;algo_data
suffix:semicolon
multiline_comment|/* register new adapter to i2c module... */
id|i2c_adap-&gt;id
op_or_assign
id|i2c_sibyte_algo.id
suffix:semicolon
id|i2c_adap-&gt;algo
op_assign
op_amp
id|i2c_sibyte_algo
suffix:semicolon
multiline_comment|/* Set the frequency to 100 kHz */
id|csr_out32
c_func
(paren
id|speed
comma
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_FREQ
)paren
)paren
suffix:semicolon
id|csr_out32
c_func
(paren
l_int|0
comma
id|SMB_CSR
c_func
(paren
id|adap
comma
id|R_SMB_CONTROL
)paren
)paren
suffix:semicolon
multiline_comment|/* scan bus */
r_if
c_cond
(paren
id|bit_scan
)paren
(brace
r_union
id|i2c_smbus_data
id|data
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; i2c-algo-sibyte.o: scanning bus %s.&bslash;n&quot;
comma
id|i2c_adap-&gt;name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0x00
suffix:semicolon
id|i
OL
l_int|0x7f
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* XXXKW is this a realistic probe? */
id|rc
op_assign
id|smbus_xfer
c_func
(paren
id|i2c_adap
comma
id|i
comma
l_int|0
comma
id|I2C_SMBUS_READ
comma
l_int|0
comma
id|I2C_SMBUS_BYTE_DATA
comma
op_amp
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;(%02x)&quot;
comma
id|i
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|i2c_add_adapter
c_func
(paren
id|i2c_adap
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2c_sibyte_del_bus
r_int
id|i2c_sibyte_del_bus
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
id|i2c_del_adapter
c_func
(paren
id|adap
)paren
)paren
OL
l_int|0
)paren
r_return
id|res
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2c_algo_sibyte_init
r_int
id|__init
id|i2c_algo_sibyte_init
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;i2c-algo-sibyte.o: i2c SiByte algorithm module&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|i2c_sibyte_add_bus
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_sibyte_add_bus
)paren
suffix:semicolon
DECL|variable|i2c_sibyte_del_bus
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_sibyte_del_bus
)paren
suffix:semicolon
macro_line|#ifdef MODULE
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Kip Walker, Broadcom Corp.&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SiByte I2C-Bus algorithm&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|bit_scan
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|bit_scan
comma
l_string|&quot;Scan for active chips on the bus&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|i2c_algo_sibyte_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
eof
