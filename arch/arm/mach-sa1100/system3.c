multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/system3.c&n; *&n; * Copyright (C) 2001 Stefan Eletzhofer &lt;stefan.eletzhofer@eletztrick.de&gt;&n; *&n; * $Id: system3.c,v 1.1.6.1 2001/12/04 17:28:06 seletz Exp $&n; *&n; * This file contains all PT Sytsem 3 tweaks. Based on original work from&n; * Nicolas Pitre&squot;s assabet fixes&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * $Log: system3.c,v $&n; * Revision 1.1.6.1  2001/12/04 17:28:06  seletz&n; * - merged from previous branch&n; *&n; * Revision 1.1.4.3  2001/12/04 15:16:31  seletz&n; * - merged from linux_2_4_13_ac5_rmk2&n; *&n; * Revision 1.1.4.2  2001/11/19 17:18:57  seletz&n; * - more code cleanups&n; *&n; * Revision 1.1.4.1  2001/11/16 13:52:05  seletz&n; * - PT Digital Board Support Code&n; *&n; * Revision 1.1.2.2  2001/11/05 16:46:18  seletz&n; * - cleanups&n; *&n; * Revision 1.1.2.1  2001/10/15 16:00:43  seletz&n; * - first revision working with new board&n; *&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &quot;generic.h&quot;
macro_line|#include &lt;asm/hardware/sa1111.h&gt;
DECL|macro|DEBUG
mdefine_line|#define DEBUG 1
macro_line|#ifdef DEBUG
DECL|macro|DPRINTK
macro_line|#&t;define DPRINTK( x, args... )&t;printk( &quot;%s: line %d: &quot;x, __FUNCTION__, __LINE__, ## args  );
macro_line|#else
DECL|macro|DPRINTK
macro_line|#&t;define DPRINTK( x, args... )&t;/* nix */
macro_line|#endif
multiline_comment|/**********************************************************************&n; *  prototypes&n; */
multiline_comment|/* init funcs */
r_static
r_int
id|__init
id|system3_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|__init
id|system3_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|__init
id|system3_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
id|u_int
id|system3_get_mctrl
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
suffix:semicolon
r_static
r_void
id|system3_set_mctrl
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
id|u_int
id|mctrl
)paren
suffix:semicolon
r_static
r_void
id|system3_uart_pm
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
id|u_int
id|state
comma
id|u_int
id|oldstate
)paren
suffix:semicolon
r_static
r_int
id|sdram_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
comma
r_int
r_int
id|event
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_static
r_void
id|system3_lcd_power
c_func
(paren
r_int
id|on
)paren
suffix:semicolon
r_static
r_void
id|system3_backlight_power
c_func
(paren
r_int
id|on
)paren
suffix:semicolon
multiline_comment|/**********************************************************************&n; *  global data&n; */
multiline_comment|/**********************************************************************&n; *  static data&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|system3_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical        length      type */
(brace
l_int|0xf3000000
comma
id|PT_CPLD_BASE
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* System Registers */
(brace
l_int|0xf4000000
comma
id|PT_SA1111_BASE
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
multiline_comment|/* SA-1111 */
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|sa1100_port_fns
id|system3_port_fns
id|__initdata
op_assign
(brace
dot
id|set_mctrl
op_assign
id|system3_set_mctrl
comma
dot
id|get_mctrl
op_assign
id|system3_get_mctrl
comma
dot
id|pm
op_assign
id|system3_uart_pm
comma
)brace
suffix:semicolon
DECL|variable|system3_clkchg_block
r_static
r_struct
id|notifier_block
id|system3_clkchg_block
op_assign
(brace
dot
id|notifier_call
op_assign
id|sdram_notifier
comma
)brace
suffix:semicolon
multiline_comment|/**********************************************************************&n; *  Static functions&n; */
DECL|function|system3_map_io
r_static
r_void
id|__init
id|system3_map_io
c_func
(paren
r_void
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
l_string|&quot;START&quot;
)paren
suffix:semicolon
id|sa1100_map_io
c_func
(paren
)paren
suffix:semicolon
id|iotable_init
c_func
(paren
id|system3_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|system3_io_desc
)paren
)paren
suffix:semicolon
id|sa1100_register_uart_fns
c_func
(paren
op_amp
id|system3_port_fns
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|0
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* com port */
id|sa1100_register_uart
c_func
(paren
l_int|1
comma
l_int|2
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|2
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* radio module */
id|Ser1SDCR0
op_or_assign
id|SDCR0_SUS
suffix:semicolon
)brace
multiline_comment|/*********************************************************************&n; * Install IRQ handler&n; */
r_static
r_void
DECL|function|system3_irq_handler
id|system3_irq_handler
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqdesc
op_star
id|desc
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|u_char
id|irr
suffix:semicolon
singleline_comment|//DPRINTK( &quot;irq=%d, desc=%p, regs=%p&bslash;n&quot;, irq, desc, regs );
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_struct
id|irqdesc
op_star
id|d
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Acknowledge the parent IRQ.&n;&t;&t; */
id|desc-&gt;chip
op_member_access_from_pointer
id|ack
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Read the interrupt reason register.  Let&squot;s have all&n;&t;&t; * active IRQ bits high.  Note: there is a typo in the&n;&t;&t; * Neponset user&squot;s guide for the SA1111 IRR level.&n;&t;&t; */
singleline_comment|//irr = PT_IRQSR &amp; (PT_IRR_LAN | PT_IRR_SA1111);
id|irr
op_assign
id|PT_IRQSR
op_amp
(paren
id|PT_IRR_SA1111
)paren
suffix:semicolon
multiline_comment|/* SMC IRQ is low-active, so &quot;switch&quot; bit over */
singleline_comment|//irr ^= (PT_IRR_LAN);
singleline_comment|//DPRINTK( &quot;irr=0x%02x&bslash;n&quot;, irr );
r_if
c_cond
(paren
(paren
id|irr
op_amp
(paren
id|PT_IRR_LAN
op_or
id|PT_IRR_SA1111
)paren
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Since there is no individual mask, we have to&n;&t;&t; * mask the parent IRQ.  This is safe, since we&squot;ll&n;&t;&t; * recheck the register for any pending IRQs.&n;&t;&t; */
r_if
c_cond
(paren
id|irr
op_amp
(paren
id|PT_IRR_LAN
)paren
)paren
(brace
id|desc-&gt;chip
op_member_access_from_pointer
id|mask
c_func
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irr
op_amp
id|PT_IRR_LAN
)paren
(brace
singleline_comment|//DPRINTK( &quot;SMC9196, irq=%d&bslash;n&quot;, IRQ_SYSTEM3_SMC9196 );
id|d
op_assign
id|irq_desc
op_plus
id|IRQ_SYSTEM3_SMC9196
suffix:semicolon
id|d
op_member_access_from_pointer
id|handle
c_func
(paren
id|IRQ_SYSTEM3_SMC9196
comma
id|d
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#if 0 /* no SSP yet on system 4 */
r_if
c_cond
(paren
id|irr
op_amp
id|IRR_USAR
)paren
(brace
id|d
op_assign
id|irq_desc
op_plus
id|IRQ_NEPONSET_USAR
suffix:semicolon
id|d
op_member_access_from_pointer
id|handle
c_func
(paren
id|IRQ_NEPONSET_USAR
comma
id|d
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif
id|desc-&gt;chip
op_member_access_from_pointer
id|unmask
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irr
op_amp
id|PT_IRR_SA1111
)paren
(brace
singleline_comment|//DPRINTK( &quot;SA1111, irq=%d&bslash;n&quot;, IRQ_SYSTEM3_SA1111 );
id|d
op_assign
id|irq_desc
op_plus
id|IRQ_SYSTEM3_SA1111
suffix:semicolon
id|d
op_member_access_from_pointer
id|handle
c_func
(paren
id|IRQ_SYSTEM3_SA1111
comma
id|d
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|system3_init_irq
r_static
r_void
id|__init
id|system3_init_irq
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Install handler for GPIO25.&n;&t; */
id|set_irq_type
c_func
(paren
id|IRQ_GPIO25
comma
id|IRQT_RISING
)paren
suffix:semicolon
id|set_irq_chained_handler
c_func
(paren
id|IRQ_GPIO25
comma
id|system3_irq_handler
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * install eth irq&n;&t; */
id|set_irq_handler
c_func
(paren
id|IRQ_SYSTEM3_SMC9196
comma
id|do_simple_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|IRQ_SYSTEM3_SMC9196
comma
id|IRQF_VALID
op_or
id|IRQF_PROBE
)paren
suffix:semicolon
)brace
multiline_comment|/**********************************************************************&n; * On system 3 limit cpu frequency to 206 Mhz&n; */
DECL|function|sdram_notifier
r_static
r_int
id|sdram_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
comma
r_int
r_int
id|event
comma
r_void
op_star
id|data
)paren
(brace
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|CPUFREQ_MINMAX
suffix:colon
id|cpufreq_updateminmax
c_func
(paren
id|data
comma
l_int|147500
comma
l_int|206000
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;system3_uart_pm - powermgmt callback function for system 3 UART&n; *&t;@port: uart port structure&n; *&t;@state: pm state&n; *&t;@oldstate: old pm state&n; *&n; */
DECL|function|system3_uart_pm
r_static
r_void
id|system3_uart_pm
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
id|u_int
id|state
comma
id|u_int
id|oldstate
)paren
(brace
multiline_comment|/* TODO: switch on/off uart in powersave mode */
)brace
multiline_comment|/*&n; * Note! this can be called from IRQ context.&n; * FIXME: Handle PT Digital Board CTRL regs irq-safe.&n; *&n; * NB: system3 uses COM_RTS and COM_DTR for both UART1 (com port)&n; * and UART3 (radio module).  We only handle them for UART1 here.&n; */
DECL|function|system3_set_mctrl
r_static
r_void
id|system3_set_mctrl
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
id|u_int
id|mctrl
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|_Ser1UTCR0
)paren
(brace
id|u_int
id|set
op_assign
l_int|0
comma
id|clear
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mctrl
op_amp
id|TIOCM_RTS
)paren
id|set
op_or_assign
id|PT_CTRL2_RS1_RTS
suffix:semicolon
r_else
id|clear
op_or_assign
id|PT_CTRL2_RS1_RTS
suffix:semicolon
r_if
c_cond
(paren
id|mctrl
op_amp
id|TIOCM_DTR
)paren
id|set
op_or_assign
id|PT_CTRL2_RS1_DTR
suffix:semicolon
r_else
id|clear
op_or_assign
id|PT_CTRL2_RS1_DTR
suffix:semicolon
id|PTCTRL2_clear
c_func
(paren
id|clear
)paren
suffix:semicolon
id|PTCTRL2_set
c_func
(paren
id|set
)paren
suffix:semicolon
)brace
)brace
DECL|function|system3_get_mctrl
r_static
id|u_int
id|system3_get_mctrl
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
id|u_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|u_int
id|irqsr
op_assign
id|PT_IRQSR
suffix:semicolon
multiline_comment|/* need 2 reads to read current value */
id|irqsr
op_assign
id|PT_IRQSR
suffix:semicolon
multiline_comment|/* TODO: check IRQ source register for modem/com&n;&t; status lines and set them correctly. */
id|ret
op_assign
id|TIOCM_CD
op_or
id|TIOCM_CTS
op_or
id|TIOCM_DSR
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;system3_lcd_backlight_on - switch system 3 lcd backlight on&n; *&n; */
DECL|function|system3_lcd_backlight_on
r_int
id|system3_lcd_backlight_on
c_func
(paren
r_void
)paren
(brace
id|PTCTRL0_set
c_func
(paren
id|PT_CTRL0_LCD_BL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;system3_lcd_backlight_off - switch system 3 lcd backlight off&n; *&n; */
DECL|function|system3_lcd_backlight_off
r_static
r_void
id|system3_lcd_backlight_off
c_func
(paren
r_void
)paren
(brace
id|PTCTRL0_clear
c_func
(paren
id|PT_CTRL0_LCD_BL
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;system3_lcd_on - switch system 3 lcd on&n; *&n; */
DECL|function|system3_lcd_on
r_static
r_void
id|system3_lcd_on
c_func
(paren
r_void
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
l_string|&quot;START&quot;
)paren
suffix:semicolon
id|PTCTRL0_set
c_func
(paren
id|PT_CTRL0_LCD_EN
)paren
suffix:semicolon
multiline_comment|/* brightness / contrast */
id|sa1111_enable_device
c_func
(paren
id|SKPCR_PWMCLKEN
)paren
suffix:semicolon
id|PB_DDR
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
id|SKPEN0
op_assign
l_int|1
suffix:semicolon
id|SKPEN1
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;system3_lcd_off - switch system 3 lcd off&n; *&n; */
DECL|function|system3_lcd_off
r_static
r_void
id|system3_lcd_off
c_func
(paren
r_void
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
l_string|&quot;START&quot;
)paren
suffix:semicolon
id|PTCTRL0_clear
c_func
(paren
id|PT_CTRL0_LCD_EN
)paren
suffix:semicolon
id|SKPEN0
op_assign
l_int|0
suffix:semicolon
id|SKPEN1
op_assign
l_int|0
suffix:semicolon
id|sa1111_disable_device
c_func
(paren
id|SKPCR_PWMCLKEN
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;system3_lcd_contrast - set system 3 contrast&n; *&t;@value:&t;&t;the new contrast&n; *&n; */
DECL|function|system3_lcd_contrast
r_static
r_void
id|system3_lcd_contrast
c_func
(paren
r_int
r_char
id|value
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;value=0x%02x&bslash;n&quot;
comma
id|value
)paren
suffix:semicolon
id|SYS3LCDCONTR
op_assign
id|value
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;system3_lcd_brightness - set system 3 brightness&n; *&t;@value:&t;&t;the new brightness&n; *&n; */
DECL|function|system3_lcd_brightness
r_static
r_void
id|system3_lcd_brightness
c_func
(paren
r_int
r_char
id|value
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;value=0x%02x&bslash;n&quot;
comma
id|value
)paren
suffix:semicolon
id|SYS3LCDBRIGHT
op_assign
id|value
suffix:semicolon
)brace
DECL|function|system3_lcd_power
r_static
r_void
id|system3_lcd_power
c_func
(paren
r_int
id|on
)paren
(brace
r_if
c_cond
(paren
id|on
)paren
(brace
id|system3_lcd_on
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|system3_lcd_off
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|system3_backlight_power
r_static
r_void
id|system3_backlight_power
c_func
(paren
r_int
id|on
)paren
(brace
r_if
c_cond
(paren
id|on
)paren
(brace
id|system3_lcd_backlight_on
c_func
(paren
)paren
suffix:semicolon
id|system3_lcd_contrast
c_func
(paren
l_int|0x95
)paren
suffix:semicolon
id|system3_lcd_brightness
c_func
(paren
l_int|240
)paren
suffix:semicolon
)brace
r_else
(brace
id|system3_lcd_backlight_off
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|system3_init
r_static
r_int
id|__init
id|system3_init
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
id|DPRINTK
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
l_string|&quot;START&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|machine_is_pt_system3
c_func
(paren
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|DONE
suffix:semicolon
)brace
id|sa1100fb_lcd_power
op_assign
id|system3_lcd_power
suffix:semicolon
id|sa1100fb_backlight_power
op_assign
id|system3_backlight_power
suffix:semicolon
multiline_comment|/* init control register */
id|PT_CTRL0
op_assign
id|PT_CTRL0_INIT
suffix:semicolon
id|PT_CTRL1
op_assign
l_int|0x02
suffix:semicolon
id|PT_CTRL2
op_assign
l_int|0x00
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;CTRL[0]=0x%02x&bslash;n&quot;
comma
id|PT_CTRL0
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;CTRL[1]=0x%02x&bslash;n&quot;
comma
id|PT_CTRL1
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;CTRL[2]=0x%02x&bslash;n&quot;
comma
id|PT_CTRL2
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Ensure that the memory bus request/grant signals are setup,&n;&t; * and the grant is held in its inactive state.&n;&t; */
id|sa1110_mb_disable
c_func
(paren
)paren
suffix:semicolon
id|system3_init_irq
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Probe for a SA1111.&n;&t; */
id|ret
op_assign
id|sa1111_init
c_func
(paren
id|PT_SA1111_BASE
comma
id|IRQ_SYSTEM3_SA1111
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PT Digital Board: no SA1111 found!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|DONE
suffix:semicolon
)brace
macro_line|#if defined( CONFIG_CPU_FREQ )
id|ret
op_assign
id|cpufreq_register_notifier
c_func
(paren
op_amp
id|system3_clkchg_block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PT Digital Board: could not register clock scale callback&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|DONE
suffix:semicolon
)brace
macro_line|#endif
id|ret
op_assign
l_int|0
suffix:semicolon
id|DONE
suffix:colon
id|DPRINTK
c_func
(paren
l_string|&quot;ret=%d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**********************************************************************&n; *  Exported Functions&n; */
multiline_comment|/**********************************************************************&n; *  kernel magic macros&n; */
DECL|variable|system3_init
id|arch_initcall
c_func
(paren
id|system3_init
)paren
suffix:semicolon
id|MACHINE_START
c_func
(paren
id|PT_SYSTEM3
comma
l_string|&quot;PT System 3&quot;
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
id|BOOT_PARAMS
c_func
(paren
l_int|0xc0000100
)paren
id|MAPIO
c_func
(paren
id|system3_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
eof
