multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/collie.c&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * This file contains all Collie-specific tweaks.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * ChangeLog:&n; *  03-06-2004 John Lenz &lt;jelenz@wisc.edu&gt;&n; *  06-04-2002 Chris Larson &lt;kergoth@digitalnemesis.net&gt;&n; *  04-16-2001 Lineo Japan,Inc. ...&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/arch/collie.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &lt;asm/hardware/locomo.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|function|scoop_init
r_static
r_void
id|__init
id|scoop_init
c_func
(paren
r_void
)paren
(brace
DECL|macro|COLLIE_SCP_INIT_DATA
mdefine_line|#define&t;COLLIE_SCP_INIT_DATA(adr,dat)&t;(((adr)&lt;&lt;16)|(dat))
DECL|macro|COLLIE_SCP_INIT_DATA_END
mdefine_line|#define&t;COLLIE_SCP_INIT_DATA_END&t;((unsigned long)-1)
r_static
r_const
r_int
r_int
id|scp_init
(braket
)braket
op_assign
(brace
id|COLLIE_SCP_INIT_DATA
c_func
(paren
id|COLLIE_SCP_MCR
comma
l_int|0x0140
)paren
comma
singleline_comment|// 00
id|COLLIE_SCP_INIT_DATA
c_func
(paren
id|COLLIE_SCP_MCR
comma
l_int|0x0100
)paren
comma
id|COLLIE_SCP_INIT_DATA
c_func
(paren
id|COLLIE_SCP_CDR
comma
l_int|0x0000
)paren
comma
singleline_comment|// 04
id|COLLIE_SCP_INIT_DATA
c_func
(paren
id|COLLIE_SCP_CPR
comma
l_int|0x0000
)paren
comma
singleline_comment|// 0C
id|COLLIE_SCP_INIT_DATA
c_func
(paren
id|COLLIE_SCP_CCR
comma
l_int|0x0000
)paren
comma
singleline_comment|// 10
id|COLLIE_SCP_INIT_DATA
c_func
(paren
id|COLLIE_SCP_IMR
comma
l_int|0x0000
)paren
comma
singleline_comment|// 18
id|COLLIE_SCP_INIT_DATA
c_func
(paren
id|COLLIE_SCP_IRM
comma
l_int|0x00FF
)paren
comma
singleline_comment|// 14
id|COLLIE_SCP_INIT_DATA
c_func
(paren
id|COLLIE_SCP_ISR
comma
l_int|0x0000
)paren
comma
singleline_comment|// 1C
id|COLLIE_SCP_INIT_DATA
c_func
(paren
id|COLLIE_SCP_IRM
comma
l_int|0x0000
)paren
comma
id|COLLIE_SCP_INIT_DATA
c_func
(paren
id|COLLIE_SCP_GPCR
comma
id|COLLIE_SCP_IO_DIR
)paren
comma
singleline_comment|// 20
id|COLLIE_SCP_INIT_DATA
c_func
(paren
id|COLLIE_SCP_GPWR
comma
id|COLLIE_SCP_IO_OUT
)paren
comma
singleline_comment|// 24
id|COLLIE_SCP_INIT_DATA_END
)brace
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|scp_init
(braket
id|i
)braket
op_ne
id|COLLIE_SCP_INIT_DATA_END
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|adr
op_assign
id|scp_init
(braket
id|i
)braket
op_rshift
l_int|16
suffix:semicolon
id|COLLIE_SCP_REG
c_func
(paren
id|adr
)paren
op_assign
id|scp_init
(braket
id|i
)braket
op_amp
l_int|0xFFFF
suffix:semicolon
)brace
)brace
DECL|variable|locomo_resources
r_static
r_struct
id|resource
id|locomo_resources
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
(brace
dot
id|start
op_assign
l_int|0x40000000
comma
dot
id|end
op_assign
l_int|0x40001fff
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(braket
l_int|1
)braket
op_assign
(brace
dot
id|start
op_assign
id|IRQ_GPIO25
comma
dot
id|end
op_assign
id|IRQ_GPIO25
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|locomo_device
r_static
r_struct
id|platform_device
id|locomo_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;locomo&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|locomo_resources
)paren
comma
dot
id|resource
op_assign
id|locomo_resources
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|devices
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|locomo_device
comma
)brace
suffix:semicolon
DECL|function|collie_init
r_static
r_int
id|__init
id|collie_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* cpu initialize */
id|GAFR
op_assign
(paren
id|GPIO_SSP_TXD
op_or
"&bslash;"
id|GPIO_SSP_SCLK
op_or
id|GPIO_SSP_SFRM
op_or
id|GPIO_SSP_CLK
op_or
id|GPIO_TIC_ACK
op_or
"&bslash;"
id|GPIO_32_768kHz
)paren
suffix:semicolon
id|GPDR
op_assign
(paren
id|GPIO_LDD8
op_or
id|GPIO_LDD9
op_or
id|GPIO_LDD10
op_or
id|GPIO_LDD11
op_or
id|GPIO_LDD12
op_or
"&bslash;"
id|GPIO_LDD13
op_or
id|GPIO_LDD14
op_or
id|GPIO_LDD15
op_or
id|GPIO_SSP_TXD
op_or
"&bslash;"
id|GPIO_SSP_SCLK
op_or
id|GPIO_SSP_SFRM
op_or
id|GPIO_SDLC_SCLK
op_or
"&bslash;"
id|GPIO_SDLC_AAF
op_or
id|GPIO_UART_SCLK1
op_or
id|GPIO_32_768kHz
)paren
suffix:semicolon
id|GPLR
op_assign
id|GPIO_GPIO18
suffix:semicolon
singleline_comment|// PPC pin setting
id|PPDR
op_assign
(paren
id|PPC_LDD0
op_or
id|PPC_LDD1
op_or
id|PPC_LDD2
op_or
id|PPC_LDD3
op_or
id|PPC_LDD4
op_or
id|PPC_LDD5
op_or
"&bslash;"
id|PPC_LDD6
op_or
id|PPC_LDD7
op_or
id|PPC_L_PCLK
op_or
id|PPC_L_LCLK
op_or
id|PPC_L_FCLK
op_or
id|PPC_L_BIAS
op_or
"&bslash;"
id|PPC_TXD1
op_or
id|PPC_TXD2
op_or
id|PPC_RXD2
op_or
id|PPC_TXD3
op_or
id|PPC_TXD4
op_or
id|PPC_SCLK
op_or
id|PPC_SFRM
)paren
suffix:semicolon
id|PSDR
op_assign
(paren
id|PPC_RXD1
op_or
id|PPC_RXD2
op_or
id|PPC_RXD3
op_or
id|PPC_RXD4
)paren
suffix:semicolon
id|GAFR
op_or_assign
id|GPIO_32_768kHz
suffix:semicolon
id|GPDR
op_or_assign
id|GPIO_32_768kHz
suffix:semicolon
id|TUCR
op_assign
id|TUCR_32_768kHz
suffix:semicolon
id|scoop_init
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|platform_add_devices
c_func
(paren
id|devices
comma
id|ARRAY_SIZE
c_func
(paren
id|devices
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;collie: Unable to register LoCoMo device&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|collie_init
id|arch_initcall
c_func
(paren
id|collie_init
)paren
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|collie_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      type */
(brace
l_int|0xe8000000
comma
l_int|0x00000000
comma
l_int|0x02000000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* 32M main flash (cs0) */
(brace
l_int|0xea000000
comma
l_int|0x08000000
comma
l_int|0x02000000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* 32M boot flash (cs1) */
(brace
l_int|0xf0000000
comma
l_int|0x40000000
comma
l_int|0x01000000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* 16M LOCOMO  &amp; SCOOP (cs4) */
)brace
suffix:semicolon
DECL|function|collie_map_io
r_static
r_void
id|__init
id|collie_map_io
c_func
(paren
r_void
)paren
(brace
id|sa1100_map_io
c_func
(paren
)paren
suffix:semicolon
id|iotable_init
c_func
(paren
id|collie_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|collie_io_desc
)paren
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|COLLIE
comma
l_string|&quot;Sharp-Collie&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0xc0000000
comma
l_int|0x80000000
comma
l_int|0xf8000000
)paren
id|MAPIO
c_func
(paren
id|collie_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
eof
