multiline_comment|/*&n; * arch/arm/mach-iop3xx/common.c&n; *&n; * Common routines shared across all IOP3xx implementations&n; *&n; * Author: Deepak Saxena &lt;dsaxena@mvista.com&gt;&n; *&n; * Copyright 2003 (c) MontaVista, Software, Inc.&n; *&n; * This file is licensed under  the terms of the GNU General Public&n; * License version 2. This program is licensed &quot;as is&quot; without any&n; * warranty of any kind, whether express or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
multiline_comment|/*&n; * Shared variables&n; */
DECL|variable|iop3xx_pcibios_min_io
r_int
r_int
id|iop3xx_pcibios_min_io
op_assign
l_int|0
suffix:semicolon
DECL|variable|iop3xx_pcibios_min_mem
r_int
r_int
id|iop3xx_pcibios_min_mem
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_ARCH_EP80219
macro_line|#include &lt;linux/kernel.h&gt;
multiline_comment|/*&n; * Default power-off for EP80219&n; */
macro_line|#include &lt;asm/mach-types.h&gt;
DECL|function|ep80219_send_to_pic
r_static
r_inline
r_void
id|ep80219_send_to_pic
c_func
(paren
id|__u8
id|c
)paren
(brace
)brace
DECL|function|ep80219_power_off
r_void
id|ep80219_power_off
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;     * This function will send a SHUTDOWN_COMPLETE message to the PIC controller&n;     * over I2C.  We are not using the i2c subsystem since we are going to power&n;     * off and it may be removed&n;     */
multiline_comment|/* Send the Address byte w/ the start condition */
op_star
id|IOP321_IDBR1
op_assign
l_int|0x60
suffix:semicolon
op_star
id|IOP321_ICR1
op_assign
l_int|0xE9
suffix:semicolon
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Send the START_MSG byte w/ no start or stop condition */
op_star
id|IOP321_IDBR1
op_assign
l_int|0x0F
suffix:semicolon
op_star
id|IOP321_ICR1
op_assign
l_int|0xE8
suffix:semicolon
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Send the SHUTDOWN_COMPLETE Message ID byte w/ no start or stop condition */
op_star
id|IOP321_IDBR1
op_assign
l_int|0x03
suffix:semicolon
op_star
id|IOP321_ICR1
op_assign
l_int|0xE8
suffix:semicolon
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Send an ignored byte w/ stop condition */
op_star
id|IOP321_IDBR1
op_assign
l_int|0x00
suffix:semicolon
op_star
id|IOP321_ICR1
op_assign
l_int|0xEA
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
DECL|function|ep80219_init
r_static
r_int
id|__init
id|ep80219_init
c_func
(paren
r_void
)paren
(brace
id|pm_power_off
op_assign
id|ep80219_power_off
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ep80219_init
id|arch_initcall
c_func
(paren
id|ep80219_init
)paren
suffix:semicolon
macro_line|#endif
eof
