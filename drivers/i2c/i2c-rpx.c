multiline_comment|/*&n; * Embedded Planet RPX Lite MPC8xx CPM I2C interface.&n; * Copyright (c) 1999 Dan Malek (dmalek@jlc.net).&n; *&n; * moved into proper i2c interface;&n; * Brad Parker (brad@heeltoe.com)&n; *&n; * RPX lite specific parts of the i2c interface&n; * Update:  There actually isn&squot;t anything RPXLite-specific about this module.&n; * This should work for most any 8xx board.  The console messages have been &n; * changed to eliminate RPXLite references.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;asm/mpc8xx.h&gt;
macro_line|#include &lt;asm/commproc.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-8xx.h&gt;
r_static
r_void
DECL|function|rpx_iic_init
id|rpx_iic_init
c_func
(paren
r_struct
id|i2c_algo_8xx_data
op_star
id|data
)paren
(brace
r_volatile
id|cpm8xx_t
op_star
id|cp
suffix:semicolon
r_volatile
id|immap_t
op_star
id|immap
suffix:semicolon
id|cp
op_assign
id|cpmp
suffix:semicolon
multiline_comment|/* Get pointer to Communication Processor */
id|immap
op_assign
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
suffix:semicolon
multiline_comment|/* and to internal registers */
id|data-&gt;iip
op_assign
(paren
id|iic_t
op_star
)paren
op_amp
id|cp-&gt;cp_dparam
(braket
id|PROFF_IIC
)braket
suffix:semicolon
multiline_comment|/* Check for and use a microcode relocation patch.&n;&t;*/
r_if
c_cond
(paren
(paren
id|data-&gt;reloc
op_assign
id|data-&gt;iip-&gt;iic_rpbase
)paren
)paren
id|data-&gt;iip
op_assign
(paren
id|iic_t
op_star
)paren
op_amp
id|cp-&gt;cp_dpmem
(braket
id|data-&gt;iip-&gt;iic_rpbase
)braket
suffix:semicolon
id|data-&gt;i2c
op_assign
(paren
id|i2c8xx_t
op_star
)paren
op_amp
(paren
id|immap-&gt;im_i2c
)paren
suffix:semicolon
id|data-&gt;cp
op_assign
id|cp
suffix:semicolon
multiline_comment|/* Initialize Port B IIC pins.&n;&t;*/
id|cp-&gt;cp_pbpar
op_or_assign
l_int|0x00000030
suffix:semicolon
id|cp-&gt;cp_pbdir
op_or_assign
l_int|0x00000030
suffix:semicolon
id|cp-&gt;cp_pbodr
op_or_assign
l_int|0x00000030
suffix:semicolon
multiline_comment|/* Allocate space for two transmit and two receive buffer&n;&t; * descriptors in the DP ram.&n;&t; */
id|data-&gt;dp_addr
op_assign
id|m8xx_cpm_dpalloc
c_func
(paren
r_sizeof
(paren
id|cbd_t
)paren
op_star
l_int|4
)paren
suffix:semicolon
multiline_comment|/* ptr to i2c area */
id|data-&gt;i2c
op_assign
(paren
id|i2c8xx_t
op_star
)paren
op_amp
(paren
(paren
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_i2c
)paren
suffix:semicolon
)brace
DECL|function|rpx_install_isr
r_static
r_int
id|rpx_install_isr
c_func
(paren
r_int
id|irq
comma
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
comma
r_void
op_star
)paren
comma
r_void
op_star
id|data
)paren
(brace
multiline_comment|/* install interrupt handler */
id|cpm_install_handler
c_func
(paren
id|irq
comma
(paren
r_void
(paren
op_star
)paren
(paren
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
id|func
comma
id|data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rpx_reg
r_static
r_int
id|rpx_reg
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rpx_unreg
r_static
r_int
id|rpx_unreg
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rpx_inc_use
r_static
r_void
id|rpx_inc_use
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
macro_line|#ifdef MODULE
id|MOD_INC_USE_COUNT
suffix:semicolon
macro_line|#endif
)brace
DECL|function|rpx_dec_use
r_static
r_void
id|rpx_dec_use
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
macro_line|#ifdef MODULE
id|MOD_DEC_USE_COUNT
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|rpx_data
r_static
r_struct
id|i2c_algo_8xx_data
id|rpx_data
op_assign
(brace
id|setisr
suffix:colon
id|rpx_install_isr
)brace
suffix:semicolon
DECL|variable|rpx_ops
r_static
r_struct
id|i2c_adapter
id|rpx_ops
op_assign
(brace
l_string|&quot;m8xx&quot;
comma
id|I2C_HW_MPC8XX_EPON
comma
l_int|NULL
comma
op_amp
id|rpx_data
comma
id|rpx_inc_use
comma
id|rpx_dec_use
comma
id|rpx_reg
comma
id|rpx_unreg
comma
)brace
suffix:semicolon
DECL|function|i2c_rpx_init
r_int
id|__init
id|i2c_rpx_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;i2c-rpx.o: i2c MPC8xx module version %s (%s)&bslash;n&quot;
comma
id|I2C_VERSION
comma
id|I2C_DATE
)paren
suffix:semicolon
multiline_comment|/* reset hardware to sane state */
id|rpx_iic_init
c_func
(paren
op_amp
id|rpx_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_8xx_add_bus
c_func
(paren
op_amp
id|rpx_ops
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;i2c-rpx: Unable to register with I2C&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2c_rpx_exit
r_void
id|__exit
id|i2c_rpx_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_8xx_del_bus
c_func
(paren
op_amp
id|rpx_ops
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Dan Malek &lt;dmalek@jlc.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;I2C-Bus adapter routines for MPC8xx boards&quot;
)paren
suffix:semicolon
DECL|variable|i2c_rpx_init
id|module_init
c_func
(paren
id|i2c_rpx_init
)paren
suffix:semicolon
DECL|variable|i2c_rpx_exit
id|module_exit
c_func
(paren
id|i2c_rpx_exit
)paren
suffix:semicolon
macro_line|#endif
eof
