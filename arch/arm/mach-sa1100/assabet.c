multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/assabet.c&n; *&n; * Author: Nicolas Pitre&n; *&n; * This file contains all Assabet-specific tweaks.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &lt;asm/arch/assabet.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|macro|ASSABET_BCR_DB1110
mdefine_line|#define ASSABET_BCR_DB1110 &bslash;&n;&t;(ASSABET_BCR_SPK_OFF    | ASSABET_BCR_QMUTE     | &bslash;&n;&t; ASSABET_BCR_LED_GREEN  | ASSABET_BCR_LED_RED   | &bslash;&n;&t; ASSABET_BCR_RS232EN    | ASSABET_BCR_LCD_12RGB | &bslash;&n;&t; ASSABET_BCR_IRDA_MD0)
DECL|macro|ASSABET_BCR_DB1111
mdefine_line|#define ASSABET_BCR_DB1111 &bslash;&n;&t;(ASSABET_BCR_SPK_OFF    | ASSABET_BCR_QMUTE     | &bslash;&n;&t; ASSABET_BCR_LED_GREEN  | ASSABET_BCR_LED_RED   | &bslash;&n;&t; ASSABET_BCR_RS232EN    | ASSABET_BCR_LCD_12RGB | &bslash;&n;&t; ASSABET_BCR_CF_BUS_OFF | ASSABET_BCR_STEREO_LB | &bslash;&n;&t; ASSABET_BCR_IRDA_MD0   | ASSABET_BCR_CF_RST)
DECL|variable|SCR_value
r_int
r_int
id|SCR_value
op_assign
id|ASSABET_SCR_INIT
suffix:semicolon
DECL|variable|SCR_value
id|EXPORT_SYMBOL
c_func
(paren
id|SCR_value
)paren
suffix:semicolon
DECL|variable|BCR_value
r_static
r_int
r_int
id|BCR_value
op_assign
id|ASSABET_BCR_DB1110
suffix:semicolon
DECL|function|ASSABET_BCR_frob
r_void
id|ASSABET_BCR_frob
c_func
(paren
r_int
r_int
id|mask
comma
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|BCR_value
op_assign
(paren
id|BCR_value
op_amp
op_complement
id|mask
)paren
op_or
id|val
suffix:semicolon
id|ASSABET_BCR
op_assign
id|BCR_value
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|ASSABET_BCR_frob
id|EXPORT_SYMBOL
c_func
(paren
id|ASSABET_BCR_frob
)paren
suffix:semicolon
DECL|function|assabet_backlight_power
r_static
r_void
id|assabet_backlight_power
c_func
(paren
r_int
id|on
)paren
(brace
macro_line|#ifndef ASSABET_PAL_VIDEO
r_if
c_cond
(paren
id|on
)paren
id|ASSABET_BCR_set
c_func
(paren
id|ASSABET_BCR_LIGHT_ON
)paren
suffix:semicolon
r_else
macro_line|#endif
id|ASSABET_BCR_clear
c_func
(paren
id|ASSABET_BCR_LIGHT_ON
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Turn on/off the backlight.  When turning the backlight on,&n; * we wait 500us after turning it on so we don&squot;t cause the&n; * supplies to droop when we enable the LCD controller (and&n; * cause a hard reset.)&n; */
DECL|function|assabet_lcd_power
r_static
r_void
id|assabet_lcd_power
c_func
(paren
r_int
id|on
)paren
(brace
macro_line|#ifndef ASSABET_PAL_VIDEO
r_if
c_cond
(paren
id|on
)paren
(brace
id|ASSABET_BCR_set
c_func
(paren
id|ASSABET_BCR_LCD_ON
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|500
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
id|ASSABET_BCR_clear
c_func
(paren
id|ASSABET_BCR_LCD_ON
)paren
suffix:semicolon
)brace
DECL|function|assabet_init
r_static
r_int
id|__init
id|assabet_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|machine_is_assabet
c_func
(paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t; * Ensure that the power supply is in &quot;high power&quot; mode.&n;&t; */
id|GPDR
op_or_assign
id|GPIO_GPIO16
suffix:semicolon
id|GPSR
op_assign
id|GPIO_GPIO16
suffix:semicolon
multiline_comment|/*&n;&t; * Ensure that these pins are set as outputs and are driving&n;&t; * logic 0.  This ensures that we won&squot;t inadvertently toggle&n;&t; * the WS latch in the CPLD, and we don&squot;t float causing&n;&t; * excessive power drain.  --rmk&n;&t; */
id|GPDR
op_or_assign
id|GPIO_SSP_TXD
op_or
id|GPIO_SSP_SCLK
op_or
id|GPIO_SSP_SFRM
suffix:semicolon
id|GPCR
op_assign
id|GPIO_SSP_TXD
op_or
id|GPIO_SSP_SCLK
op_or
id|GPIO_SSP_SFRM
suffix:semicolon
multiline_comment|/*&n;&t; * Set up registers for sleep mode.&n;&t; */
id|PWER
op_assign
id|PWER_GPIO0
suffix:semicolon
id|PGSR
op_assign
l_int|0
suffix:semicolon
id|PCFR
op_assign
l_int|0
suffix:semicolon
id|PSDR
op_assign
l_int|0
suffix:semicolon
id|PPDR
op_or_assign
id|PPC_TXD3
op_or
id|PPC_TXD1
suffix:semicolon
id|PPSR
op_or_assign
id|PPC_TXD3
op_or
id|PPC_TXD1
suffix:semicolon
id|sa1100fb_lcd_power
op_assign
id|assabet_lcd_power
suffix:semicolon
id|sa1100fb_backlight_power
op_assign
id|assabet_backlight_power
suffix:semicolon
r_if
c_cond
(paren
id|machine_has_neponset
c_func
(paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Angel sets this, but other bootloaders may not.&n;&t;&t; *&n;&t;&t; * This must precede any driver calls to BCR_set()&n;&t;&t; * or BCR_clear().&n;&t;&t; */
id|ASSABET_BCR
op_assign
id|BCR_value
op_assign
id|ASSABET_BCR_DB1111
suffix:semicolon
macro_line|#ifndef CONFIG_ASSABET_NEPONSET
id|printk
c_func
(paren
l_string|&quot;Warning: Neponset detected but full support &quot;
l_string|&quot;hasn&squot;t been configured in the kernel&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|assabet_init
id|arch_initcall
c_func
(paren
id|assabet_init
)paren
suffix:semicolon
multiline_comment|/*&n; * On Assabet, we must probe for the Neponset board _before_&n; * paging_init() has occurred to actually determine the amount&n; * of RAM available.  To do so, we map the appropriate IO section&n; * in the page table here in order to access GPIO registers.&n; */
DECL|function|map_sa1100_gpio_regs
r_static
r_void
id|__init
id|map_sa1100_gpio_regs
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|phys
op_assign
id|__PREG
c_func
(paren
id|GPLR
)paren
op_amp
id|PMD_MASK
suffix:semicolon
r_int
r_int
id|virt
op_assign
id|io_p2v
c_func
(paren
id|phys
)paren
suffix:semicolon
r_int
id|prot
op_assign
id|PMD_TYPE_SECT
op_or
id|PMD_SECT_AP_WRITE
op_or
id|PMD_DOMAIN
c_func
(paren
id|DOMAIN_IO
)paren
suffix:semicolon
id|pmd_t
id|pmd
suffix:semicolon
id|pmd_val
c_func
(paren
id|pmd
)paren
op_assign
id|phys
op_or
id|prot
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd_offset
c_func
(paren
id|pgd_offset_k
c_func
(paren
id|virt
)paren
comma
id|virt
)paren
comma
id|pmd
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read System Configuration &quot;Register&quot;&n; * (taken from &quot;Intel StrongARM SA-1110 Microprocessor Development Board&n; * User&squot;s Guide&quot;, section 4.4.1)&n; *&n; * This same scan is performed in arch/arm/boot/compressed/head-sa1100.S&n; * to set up the serial port for decompression status messages. We&n; * repeat it here because the kernel may not be loaded as a zImage, and&n; * also because it&squot;s a hassle to communicate the SCR value to the kernel&n; * from the decompressor.&n; *&n; * Note that IRQs are guaranteed to be disabled.&n; */
DECL|function|get_assabet_scr
r_static
r_void
id|__init
id|get_assabet_scr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|scr
comma
id|i
suffix:semicolon
id|GPDR
op_or_assign
l_int|0x3fc
suffix:semicolon
multiline_comment|/* Configure GPIO 9:2 as outputs */
id|GPSR
op_assign
l_int|0x3fc
suffix:semicolon
multiline_comment|/* Write 0xFF to GPIO 9:2 */
id|GPDR
op_and_assign
op_complement
(paren
l_int|0x3fc
)paren
suffix:semicolon
multiline_comment|/* Configure GPIO 9:2 as inputs */
r_for
c_loop
(paren
id|i
op_assign
l_int|100
suffix:semicolon
id|i
op_decrement
suffix:semicolon
id|scr
op_assign
id|GPLR
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Read GPIO 9:2 */
id|GPDR
op_or_assign
l_int|0x3fc
suffix:semicolon
multiline_comment|/*  restore correct pin direction */
id|scr
op_and_assign
l_int|0x3fc
suffix:semicolon
multiline_comment|/* save as system configuration byte. */
id|SCR_value
op_assign
id|scr
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|fixup_assabet
id|fixup_assabet
c_func
(paren
r_struct
id|machine_desc
op_star
id|desc
comma
r_struct
id|tag
op_star
id|tags
comma
r_char
op_star
op_star
id|cmdline
comma
r_struct
id|meminfo
op_star
id|mi
)paren
(brace
multiline_comment|/* This must be done before any call to machine_has_neponset() */
id|map_sa1100_gpio_regs
c_func
(paren
)paren
suffix:semicolon
id|get_assabet_scr
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine_has_neponset
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Neponset expansion board detected&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|assabet_uart_pm
r_static
r_void
id|assabet_uart_pm
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
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|_Ser1UTCR0
)paren
(brace
r_if
c_cond
(paren
id|state
)paren
id|ASSABET_BCR_clear
c_func
(paren
id|ASSABET_BCR_RS232EN
op_or
id|ASSABET_BCR_COM_RTS
op_or
id|ASSABET_BCR_COM_DTR
)paren
suffix:semicolon
r_else
id|ASSABET_BCR_set
c_func
(paren
id|ASSABET_BCR_RS232EN
op_or
id|ASSABET_BCR_COM_RTS
op_or
id|ASSABET_BCR_COM_DTR
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Assabet uses COM_RTS and COM_DTR for both UART1 (com port)&n; * and UART3 (radio module).  We only handle them for UART1 here.&n; */
DECL|function|assabet_set_mctrl
r_static
r_void
id|assabet_set_mctrl
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
id|clear
op_or_assign
id|ASSABET_BCR_COM_RTS
suffix:semicolon
r_else
id|set
op_or_assign
id|ASSABET_BCR_COM_RTS
suffix:semicolon
r_if
c_cond
(paren
id|mctrl
op_amp
id|TIOCM_DTR
)paren
id|clear
op_or_assign
id|ASSABET_BCR_COM_DTR
suffix:semicolon
r_else
id|set
op_or_assign
id|ASSABET_BCR_COM_DTR
suffix:semicolon
id|ASSABET_BCR_clear
c_func
(paren
id|clear
)paren
suffix:semicolon
id|ASSABET_BCR_set
c_func
(paren
id|set
)paren
suffix:semicolon
)brace
)brace
DECL|function|assabet_get_mctrl
r_static
id|u_int
id|assabet_get_mctrl
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
id|bsr
op_assign
id|ASSABET_BSR
suffix:semicolon
multiline_comment|/* need 2 reads to read current value */
id|bsr
op_assign
id|ASSABET_BSR
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|_Ser1UTCR0
)paren
(brace
r_if
c_cond
(paren
id|bsr
op_amp
id|ASSABET_BSR_COM_DCD
)paren
id|ret
op_or_assign
id|TIOCM_CD
suffix:semicolon
r_if
c_cond
(paren
id|bsr
op_amp
id|ASSABET_BSR_COM_CTS
)paren
id|ret
op_or_assign
id|TIOCM_CTS
suffix:semicolon
r_if
c_cond
(paren
id|bsr
op_amp
id|ASSABET_BSR_COM_DSR
)paren
id|ret
op_or_assign
id|TIOCM_DSR
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|_Ser3UTCR0
)paren
(brace
r_if
c_cond
(paren
id|bsr
op_amp
id|ASSABET_BSR_RAD_DCD
)paren
id|ret
op_or_assign
id|TIOCM_CD
suffix:semicolon
r_if
c_cond
(paren
id|bsr
op_amp
id|ASSABET_BSR_RAD_CTS
)paren
id|ret
op_or_assign
id|TIOCM_CTS
suffix:semicolon
r_if
c_cond
(paren
id|bsr
op_amp
id|ASSABET_BSR_RAD_DSR
)paren
id|ret
op_or_assign
id|TIOCM_DSR
suffix:semicolon
r_if
c_cond
(paren
id|bsr
op_amp
id|ASSABET_BSR_RAD_RI
)paren
id|ret
op_or_assign
id|TIOCM_RI
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
id|TIOCM_CD
op_or
id|TIOCM_CTS
op_or
id|TIOCM_DSR
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|sa1100_port_fns
id|assabet_port_fns
id|__initdata
op_assign
(brace
dot
id|set_mctrl
op_assign
id|assabet_set_mctrl
comma
dot
id|get_mctrl
op_assign
id|assabet_get_mctrl
comma
dot
id|pm
op_assign
id|assabet_uart_pm
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|assabet_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      type */
(brace
l_int|0xf1000000
comma
l_int|0x12000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* Board Control Register */
(brace
l_int|0xf2800000
comma
l_int|0x4b800000
comma
l_int|0x00800000
comma
id|MT_DEVICE
)brace
multiline_comment|/* MQ200 */
)brace
suffix:semicolon
DECL|function|assabet_map_io
r_static
r_void
id|__init
id|assabet_map_io
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
id|assabet_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|assabet_io_desc
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set SUS bit in SDCR0 so serial port 1 functions.&n;&t; * Its called GPCLKR0 in my SA1110 manual.&n;&t; */
id|Ser1SDCR0
op_or_assign
id|SDCR0_SUS
suffix:semicolon
r_if
c_cond
(paren
id|machine_has_neponset
c_func
(paren
)paren
)paren
(brace
macro_line|#ifdef CONFIG_ASSABET_NEPONSET
r_extern
r_void
id|neponset_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We map Neponset registers even if it isn&squot;t present since&n;&t;&t; * many drivers will try to probe their stuff (and fail).&n;&t;&t; * This is still more friendly than a kernel paging request&n;&t;&t; * crash.&n;&t;&t; */
id|neponset_map_io
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
id|sa1100_register_uart_fns
c_func
(paren
op_amp
id|assabet_port_fns
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * When Neponset is attached, the first UART should be&n;&t; * UART3.  That&squot;s what Angel is doing and many documents&n;&t; * are stating this.&n;&t; *&n;&t; * We do the Neponset mapping even if Neponset support&n;&t; * isn&squot;t compiled in so the user will still get something on&n;&t; * the expected physical serial port.&n;&t; *&n;&t; * We no longer do this; not all boot loaders support it,&n;&t; * and UART3 appears to be somewhat unreliable with blob.&n;&t; */
id|sa1100_register_uart
c_func
(paren
l_int|0
comma
l_int|1
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
)brace
id|MACHINE_START
c_func
(paren
id|ASSABET
comma
l_string|&quot;Intel-Assabet&quot;
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
id|FIXUP
c_func
(paren
id|fixup_assabet
)paren
id|MAPIO
c_func
(paren
id|assabet_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
eof
