multiline_comment|/*&n; * Hardware definitions for Compaq iPAQ H3xxx Handheld Computers&n; *&n; * Copyright 2000,1 Compaq Computer Corporation.&n; *&n; * Use consistent with the GNU GPL is permitted,&n; * provided that this copyright notice is&n; * preserved in its entirety in all copies and derived works.&n; *&n; * COMPAQ COMPUTER CORPORATION MAKES NO WARRANTIES, EXPRESSED OR IMPLIED,&n; * AS TO THE USEFULNESS OR CORRECTNESS OF THIS CODE OR ITS&n; * FITNESS FOR ANY PARTICULAR PURPOSE.&n; *&n; * Author: Jamey Hicks.&n; *&n; * History:&n; *&n; * 2001-10-??&t;Andrew Christian   Added support for iPAQ H3800&n; *&t;&t;&t;&t;   and abstracted EGPIO interface.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &lt;asm/arch/h3600.h&gt;
macro_line|#if defined (CONFIG_SA1100_H3600) || defined (CONFIG_SA1100_H3100)
macro_line|#include &lt;asm/arch/h3600_gpio.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_H3800
macro_line|#include &lt;asm/arch/h3600_asic.h&gt;
macro_line|#endif
macro_line|#include &quot;generic.h&quot;
DECL|variable|ipaq_model_ops
r_struct
id|ipaq_model_ops
id|ipaq_model_ops
suffix:semicolon
DECL|variable|ipaq_model_ops
id|EXPORT_SYMBOL
c_func
(paren
id|ipaq_model_ops
)paren
suffix:semicolon
multiline_comment|/*&n; * low-level UART features&n; */
DECL|function|h3600_uart_set_mctrl
r_static
r_void
id|h3600_uart_set_mctrl
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
id|_Ser3UTCR0
)paren
(brace
r_if
c_cond
(paren
id|mctrl
op_amp
id|TIOCM_RTS
)paren
id|GPCR
op_assign
id|GPIO_H3600_COM_RTS
suffix:semicolon
r_else
id|GPSR
op_assign
id|GPIO_H3600_COM_RTS
suffix:semicolon
)brace
)brace
DECL|function|h3600_uart_get_mctrl
r_static
id|u_int
id|h3600_uart_get_mctrl
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
id|TIOCM_CD
op_or
id|TIOCM_CTS
op_or
id|TIOCM_DSR
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|_Ser3UTCR0
)paren
(brace
r_int
id|gplr
op_assign
id|GPLR
suffix:semicolon
multiline_comment|/* DCD and CTS bits are inverted in GPLR by RS232 transceiver */
r_if
c_cond
(paren
id|gplr
op_amp
id|GPIO_H3600_COM_DCD
)paren
id|ret
op_and_assign
op_complement
id|TIOCM_CD
suffix:semicolon
r_if
c_cond
(paren
id|gplr
op_amp
id|GPIO_H3600_COM_CTS
)paren
id|ret
op_and_assign
op_complement
id|TIOCM_CTS
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|h3600_uart_pm
r_static
r_void
id|h3600_uart_pm
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
id|_Ser2UTCR0
)paren
(brace
multiline_comment|/* TODO: REMOVE THIS */
id|assign_h3600_egpio
c_func
(paren
id|IPAQ_EGPIO_IR_ON
comma
op_logical_neg
id|state
)paren
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
id|assign_h3600_egpio
c_func
(paren
id|IPAQ_EGPIO_RS232_ON
comma
op_logical_neg
id|state
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Enable/Disable wake up events for this serial port.&n; * Obviously, we only support this on the normal COM port.&n; */
DECL|function|h3600_uart_set_wake
r_static
r_int
id|h3600_uart_set_wake
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
id|u_int
id|enable
)paren
(brace
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
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
id|enable
)paren
id|PWER
op_or_assign
id|PWER_GPIO23
op_or
id|PWER_GPIO25
suffix:semicolon
multiline_comment|/* DCD and CTS */
r_else
id|PWER
op_and_assign
op_complement
(paren
id|PWER_GPIO23
op_or
id|PWER_GPIO25
)paren
suffix:semicolon
multiline_comment|/* DCD and CTS */
id|err
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|sa1100_port_fns
id|h3600_port_fns
id|__initdata
op_assign
(brace
dot
id|set_mctrl
op_assign
id|h3600_uart_set_mctrl
comma
dot
id|get_mctrl
op_assign
id|h3600_uart_get_mctrl
comma
dot
id|pm
op_assign
id|h3600_uart_pm
comma
dot
id|set_wake
op_assign
id|h3600_uart_set_wake
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * helper for sa1100fb&n; */
DECL|function|h3xxx_lcd_power
r_static
r_void
id|h3xxx_lcd_power
c_func
(paren
r_int
id|enable
)paren
(brace
id|assign_h3600_egpio
c_func
(paren
id|IPAQ_EGPIO_LCD_POWER
comma
id|enable
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|h3600_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual&t;       physical &t;  length      type */
(brace
id|H3600_BANK_2_VIRT
comma
id|SA1100_CS2_PHYS
comma
l_int|0x02800000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* static memory bank 2  CS#2 */
(brace
id|H3600_BANK_4_VIRT
comma
id|SA1100_CS4_PHYS
comma
l_int|0x00800000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* static memory bank 4  CS#4 */
(brace
id|H3600_EGPIO_VIRT
comma
id|H3600_EGPIO_PHYS
comma
l_int|0x01000000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* EGPIO 0&t;&t;CS#5 */
)brace
suffix:semicolon
multiline_comment|/*&n; * Common map_io initialization&n; */
DECL|function|h3xxx_map_io
r_static
r_void
id|__init
id|h3xxx_map_io
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
id|h3600_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|h3600_io_desc
)paren
)paren
suffix:semicolon
id|sa1100_register_uart_fns
c_func
(paren
op_amp
id|h3600_port_fns
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|0
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* Common serial port */
singleline_comment|//&t;sa1100_register_uart(1, 1); /* Microcontroller on 3100/3600 */
multiline_comment|/* Ensure those pins are outputs and driving low  */
id|PPDR
op_or_assign
id|PPC_TXD4
op_or
id|PPC_SCLK
op_or
id|PPC_SFRM
suffix:semicolon
id|PPSR
op_and_assign
op_complement
(paren
id|PPC_TXD4
op_or
id|PPC_SCLK
op_or
id|PPC_SFRM
)paren
suffix:semicolon
multiline_comment|/* Configure suspend conditions */
id|PGSR
op_assign
l_int|0
suffix:semicolon
id|PWER
op_assign
id|PWER_GPIO0
op_or
id|PWER_RTC
suffix:semicolon
id|PCFR
op_assign
id|PCFR_OPDE
suffix:semicolon
id|PSDR
op_assign
l_int|0
suffix:semicolon
id|sa1100fb_lcd_power
op_assign
id|h3xxx_lcd_power
suffix:semicolon
)brace
DECL|function|do_blank
r_static
id|__inline__
r_void
id|do_blank
c_func
(paren
r_int
id|setp
)paren
(brace
r_if
c_cond
(paren
id|ipaq_model_ops.blank_callback
)paren
id|ipaq_model_ops
dot
id|blank_callback
c_func
(paren
l_int|1
op_minus
id|setp
)paren
suffix:semicolon
)brace
multiline_comment|/************************* H3100 *************************/
macro_line|#ifdef CONFIG_SA1100_H3100
DECL|macro|H3100_EGPIO
mdefine_line|#define H3100_EGPIO&t;(*(volatile unsigned int *)H3600_EGPIO_VIRT)
DECL|variable|h3100_egpio
r_static
r_int
r_int
id|h3100_egpio
op_assign
l_int|0
suffix:semicolon
DECL|function|h3100_control_egpio
r_static
r_void
id|h3100_control_egpio
c_func
(paren
r_enum
id|ipaq_egpio_type
id|x
comma
r_int
id|setp
)paren
(brace
r_int
r_int
id|egpio
op_assign
l_int|0
suffix:semicolon
r_int
id|gpio
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_switch
c_cond
(paren
id|x
)paren
(brace
r_case
id|IPAQ_EGPIO_LCD_POWER
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_LCD_ON
suffix:semicolon
id|gpio
op_or_assign
id|GPIO_H3100_LCD_3V_ON
suffix:semicolon
id|do_blank
c_func
(paren
id|setp
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_LCD_ENABLE
suffix:colon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_CODEC_NRESET
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_CODEC_NRESET
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_AUDIO_ON
suffix:colon
id|gpio
op_or_assign
id|GPIO_H3100_AUD_PWR_ON
op_or
id|GPIO_H3100_AUD_ON
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_QMUTE
suffix:colon
id|gpio
op_or_assign
id|GPIO_H3100_QMUTE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_OPT_NVRAM_ON
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_OPT_NVRAM_ON
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_OPT_ON
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_OPT_ON
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_CARD_RESET
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_CARD_RESET
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_OPT_RESET
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_OPT_RESET
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_IR_ON
suffix:colon
id|gpio
op_or_assign
id|GPIO_H3100_IR_ON
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_IR_FSEL
suffix:colon
id|gpio
op_or_assign
id|GPIO_H3100_IR_FSEL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_RS232_ON
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_RS232_ON
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_VPP_ON
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_VPP_ON
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|egpio
op_logical_or
id|gpio
)paren
(brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|setp
)paren
(brace
id|h3100_egpio
op_or_assign
id|egpio
suffix:semicolon
id|GPSR
op_assign
id|gpio
suffix:semicolon
)brace
r_else
(brace
id|h3100_egpio
op_and_assign
op_complement
id|egpio
suffix:semicolon
id|GPCR
op_assign
id|gpio
suffix:semicolon
)brace
id|H3100_EGPIO
op_assign
id|h3100_egpio
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
DECL|function|h3100_read_egpio
r_static
r_int
r_int
id|h3100_read_egpio
c_func
(paren
r_void
)paren
(brace
r_return
id|h3100_egpio
suffix:semicolon
)brace
DECL|function|h3100_pm_callback
r_static
r_int
id|h3100_pm_callback
c_func
(paren
r_int
id|req
)paren
(brace
r_if
c_cond
(paren
id|ipaq_model_ops.pm_callback_aux
)paren
r_return
id|ipaq_model_ops
dot
id|pm_callback_aux
c_func
(paren
id|req
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|ipaq_model_ops
id|h3100_model_ops
id|__initdata
op_assign
(brace
dot
id|generic_name
op_assign
l_string|&quot;3100&quot;
comma
dot
id|control
op_assign
id|h3100_control_egpio
comma
dot
id|read
op_assign
id|h3100_read_egpio
comma
dot
id|pm_callback
op_assign
id|h3100_pm_callback
)brace
suffix:semicolon
DECL|macro|H3100_DIRECT_EGPIO
mdefine_line|#define H3100_DIRECT_EGPIO (GPIO_H3100_BT_ON&t;  &bslash;&n;&t;&t;&t;  | GPIO_H3100_GPIO3&t;  &bslash;&n;&t;&t;&t;  | GPIO_H3100_QMUTE&t;  &bslash;&n;&t;&t;&t;  | GPIO_H3100_LCD_3V_ON  &bslash;&n;&t;&t;&t;  | GPIO_H3100_AUD_ON&t;  &bslash;&n;&t;&t;&t;  | GPIO_H3100_AUD_PWR_ON &bslash;&n;&t;&t;&t;  | GPIO_H3100_IR_ON&t;  &bslash;&n;&t;&t;&t;  | GPIO_H3100_IR_FSEL)
DECL|function|h3100_map_io
r_static
r_void
id|__init
id|h3100_map_io
c_func
(paren
r_void
)paren
(brace
id|h3xxx_map_io
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Initialize h3100-specific values here */
id|GPCR
op_assign
l_int|0x0fffffff
suffix:semicolon
multiline_comment|/* All outputs are set low by default */
id|GPDR
op_assign
id|GPIO_H3600_COM_RTS
op_or
id|GPIO_H3600_L3_CLOCK
op_or
id|GPIO_H3600_L3_MODE
op_or
id|GPIO_H3600_L3_DATA
op_or
id|GPIO_H3600_CLK_SET1
op_or
id|GPIO_H3600_CLK_SET0
op_or
id|H3100_DIRECT_EGPIO
suffix:semicolon
multiline_comment|/* Older bootldrs put GPIO2-9 in alternate mode on the&n;&t;   assumption that they are used for video */
id|GAFR
op_and_assign
op_complement
id|H3100_DIRECT_EGPIO
suffix:semicolon
id|H3100_EGPIO
op_assign
id|h3100_egpio
suffix:semicolon
id|ipaq_model_ops
op_assign
id|h3100_model_ops
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|H3100
comma
l_string|&quot;Compaq iPAQ H3100&quot;
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
id|h3100_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
macro_line|#endif /* CONFIG_SA1100_H3100 */
multiline_comment|/************************* H3600 *************************/
macro_line|#ifdef CONFIG_SA1100_H3600
DECL|macro|H3600_EGPIO
mdefine_line|#define H3600_EGPIO&t;(*(volatile unsigned int *)H3600_EGPIO_VIRT)
DECL|variable|h3600_egpio
r_static
r_int
r_int
id|h3600_egpio
op_assign
id|EGPIO_H3600_RS232_ON
suffix:semicolon
DECL|function|h3600_control_egpio
r_static
r_void
id|h3600_control_egpio
c_func
(paren
r_enum
id|ipaq_egpio_type
id|x
comma
r_int
id|setp
)paren
(brace
r_int
r_int
id|egpio
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_switch
c_cond
(paren
id|x
)paren
(brace
r_case
id|IPAQ_EGPIO_LCD_POWER
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_LCD_ON
op_or
id|EGPIO_H3600_LCD_PCI
op_or
id|EGPIO_H3600_LCD_5V_ON
op_or
id|EGPIO_H3600_LVDD_ON
suffix:semicolon
id|do_blank
c_func
(paren
id|setp
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_LCD_ENABLE
suffix:colon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_CODEC_NRESET
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_CODEC_NRESET
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_AUDIO_ON
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_AUD_AMP_ON
op_or
id|EGPIO_H3600_AUD_PWR_ON
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_QMUTE
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_QMUTE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_OPT_NVRAM_ON
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_OPT_NVRAM_ON
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_OPT_ON
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_OPT_ON
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_CARD_RESET
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_CARD_RESET
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_OPT_RESET
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_OPT_RESET
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_IR_ON
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_IR_ON
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_IR_FSEL
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_IR_FSEL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_RS232_ON
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_RS232_ON
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_VPP_ON
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_VPP_ON
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|egpio
)paren
(brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|setp
)paren
id|h3600_egpio
op_or_assign
id|egpio
suffix:semicolon
r_else
id|h3600_egpio
op_and_assign
op_complement
id|egpio
suffix:semicolon
id|H3600_EGPIO
op_assign
id|h3600_egpio
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
DECL|function|h3600_read_egpio
r_static
r_int
r_int
id|h3600_read_egpio
c_func
(paren
r_void
)paren
(brace
r_return
id|h3600_egpio
suffix:semicolon
)brace
DECL|function|h3600_pm_callback
r_static
r_int
id|h3600_pm_callback
c_func
(paren
r_int
id|req
)paren
(brace
r_if
c_cond
(paren
id|ipaq_model_ops.pm_callback_aux
)paren
r_return
id|ipaq_model_ops
dot
id|pm_callback_aux
c_func
(paren
id|req
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|ipaq_model_ops
id|h3600_model_ops
id|__initdata
op_assign
(brace
dot
id|generic_name
op_assign
l_string|&quot;3600&quot;
comma
dot
id|control
op_assign
id|h3600_control_egpio
comma
dot
id|read
op_assign
id|h3600_read_egpio
comma
dot
id|pm_callback
op_assign
id|h3600_pm_callback
)brace
suffix:semicolon
DECL|function|h3600_map_io
r_static
r_void
id|__init
id|h3600_map_io
c_func
(paren
r_void
)paren
(brace
id|h3xxx_map_io
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Initialize h3600-specific values here */
id|GPCR
op_assign
l_int|0x0fffffff
suffix:semicolon
multiline_comment|/* All outputs are set low by default */
id|GPDR
op_assign
id|GPIO_H3600_COM_RTS
op_or
id|GPIO_H3600_L3_CLOCK
op_or
id|GPIO_H3600_L3_MODE
op_or
id|GPIO_H3600_L3_DATA
op_or
id|GPIO_H3600_CLK_SET1
op_or
id|GPIO_H3600_CLK_SET0
op_or
id|GPIO_LDD15
op_or
id|GPIO_LDD14
op_or
id|GPIO_LDD13
op_or
id|GPIO_LDD12
op_or
id|GPIO_LDD11
op_or
id|GPIO_LDD10
op_or
id|GPIO_LDD9
op_or
id|GPIO_LDD8
suffix:semicolon
id|H3600_EGPIO
op_assign
id|h3600_egpio
suffix:semicolon
multiline_comment|/* Maintains across sleep? */
id|ipaq_model_ops
op_assign
id|h3600_model_ops
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|H3600
comma
l_string|&quot;Compaq iPAQ H3600&quot;
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
id|h3600_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
macro_line|#endif /* CONFIG_SA1100_H3600 */
macro_line|#ifdef CONFIG_SA1100_H3800
DECL|macro|SET_ASIC1
mdefine_line|#define SET_ASIC1(x) &bslash;&n;   do {if (setp) { H3800_ASIC1_GPIO_OUT |= (x); } else { H3800_ASIC1_GPIO_OUT &amp;= ~(x); }} while(0)
DECL|macro|SET_ASIC2
mdefine_line|#define SET_ASIC2(x) &bslash;&n;   do {if (setp) { H3800_ASIC2_GPIOPIOD |= (x); } else { H3800_ASIC2_GPIOPIOD &amp;= ~(x); }} while(0)
DECL|macro|CLEAR_ASIC1
mdefine_line|#define CLEAR_ASIC1(x) &bslash;&n;   do {if (setp) { H3800_ASIC1_GPIO_OUT &amp;= ~(x); } else { H3800_ASIC1_GPIO_OUT |= (x); }} while(0)
DECL|macro|CLEAR_ASIC2
mdefine_line|#define CLEAR_ASIC2(x) &bslash;&n;   do {if (setp) { H3800_ASIC2_GPIOPIOD &amp;= ~(x); } else { H3800_ASIC2_GPIOPIOD |= (x); }} while(0)
multiline_comment|/*&n;  On screen enable, we get&n;&n;     h3800_video_power_on(1)&n;     LCD controller starts&n;     h3800_video_lcd_enable(1)&n;&n;  On screen disable, we get&n;&n;     h3800_video_lcd_enable(0)&n;     LCD controller stops&n;     h3800_video_power_on(0)&n;*/
DECL|function|h3800_video_power_on
r_static
r_void
id|h3800_video_power_on
c_func
(paren
r_int
id|setp
)paren
(brace
r_if
c_cond
(paren
id|setp
)paren
(brace
id|H3800_ASIC1_GPIO_OUT
op_or_assign
id|GPIO1_LCD_ON
suffix:semicolon
id|msleep
c_func
(paren
l_int|30
)paren
suffix:semicolon
id|H3800_ASIC1_GPIO_OUT
op_or_assign
id|GPIO1_VGL_ON
suffix:semicolon
id|msleep
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|H3800_ASIC1_GPIO_OUT
op_or_assign
id|GPIO1_VGH_ON
suffix:semicolon
id|msleep
c_func
(paren
l_int|50
)paren
suffix:semicolon
id|H3800_ASIC1_GPIO_OUT
op_or_assign
id|GPIO1_LCD_5V_ON
suffix:semicolon
id|msleep
c_func
(paren
l_int|5
)paren
suffix:semicolon
)brace
r_else
(brace
id|msleep
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|H3800_ASIC1_GPIO_OUT
op_and_assign
op_complement
id|GPIO1_LCD_5V_ON
suffix:semicolon
id|msleep
c_func
(paren
l_int|50
)paren
suffix:semicolon
id|H3800_ASIC1_GPIO_OUT
op_and_assign
op_complement
id|GPIO1_VGL_ON
suffix:semicolon
id|msleep
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|H3800_ASIC1_GPIO_OUT
op_and_assign
op_complement
id|GPIO1_VGH_ON
suffix:semicolon
id|msleep
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|H3800_ASIC1_GPIO_OUT
op_and_assign
op_complement
id|GPIO1_LCD_ON
suffix:semicolon
)brace
)brace
DECL|function|h3800_video_lcd_enable
r_static
r_void
id|h3800_video_lcd_enable
c_func
(paren
r_int
id|setp
)paren
(brace
r_if
c_cond
(paren
id|setp
)paren
(brace
id|msleep
c_func
(paren
l_int|17
)paren
suffix:semicolon
singleline_comment|// Wait one from before turning on
id|H3800_ASIC1_GPIO_OUT
op_or_assign
id|GPIO1_LCD_PCI
suffix:semicolon
)brace
r_else
(brace
id|H3800_ASIC1_GPIO_OUT
op_and_assign
op_complement
id|GPIO1_LCD_PCI
suffix:semicolon
id|msleep
c_func
(paren
l_int|30
)paren
suffix:semicolon
singleline_comment|// Wait before turning off
)brace
)brace
DECL|function|h3800_control_egpio
r_static
r_void
id|h3800_control_egpio
c_func
(paren
r_enum
id|ipaq_egpio_type
id|x
comma
r_int
id|setp
)paren
(brace
r_switch
c_cond
(paren
id|x
)paren
(brace
r_case
id|IPAQ_EGPIO_LCD_POWER
suffix:colon
id|h3800_video_power_on
c_func
(paren
id|setp
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_LCD_ENABLE
suffix:colon
id|h3800_video_lcd_enable
c_func
(paren
id|setp
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_CODEC_NRESET
suffix:colon
r_case
id|IPAQ_EGPIO_AUDIO_ON
suffix:colon
r_case
id|IPAQ_EGPIO_QMUTE
suffix:colon
id|printk
c_func
(paren
id|__FUNCTION__
l_string|&quot;: error - should not be called&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_OPT_NVRAM_ON
suffix:colon
id|SET_ASIC2
c_func
(paren
id|GPIO2_OPT_ON_NVRAM
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_OPT_ON
suffix:colon
id|SET_ASIC2
c_func
(paren
id|GPIO2_OPT_ON
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_CARD_RESET
suffix:colon
id|SET_ASIC2
c_func
(paren
id|GPIO2_OPT_PCM_RESET
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_OPT_RESET
suffix:colon
id|SET_ASIC2
c_func
(paren
id|GPIO2_OPT_RESET
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_IR_ON
suffix:colon
id|CLEAR_ASIC1
c_func
(paren
id|GPIO1_IR_ON_N
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_IR_FSEL
suffix:colon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_RS232_ON
suffix:colon
id|SET_ASIC1
c_func
(paren
id|GPIO1_RS232_ON
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_VPP_ON
suffix:colon
id|H3800_ASIC2_FlashWP_VPP_ON
op_assign
id|setp
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|h3800_read_egpio
r_static
r_int
r_int
id|h3800_read_egpio
c_func
(paren
r_void
)paren
(brace
r_return
id|H3800_ASIC1_GPIO_OUT
op_or
(paren
id|H3800_ASIC2_GPIOPIOD
op_lshift
l_int|16
)paren
suffix:semicolon
)brace
multiline_comment|/* We need to fix ASIC2 GPIO over suspend/resume.  At the moment,&n;   it doesn&squot;t appear that ASIC1 GPIO has the same problem */
DECL|function|h3800_pm_callback
r_static
r_int
id|h3800_pm_callback
c_func
(paren
r_int
id|req
)paren
(brace
r_static
id|u16
id|asic1_data
suffix:semicolon
r_static
id|u16
id|asic2_data
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|__FUNCTION__
l_string|&quot; %d&bslash;n&quot;
comma
id|req
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|req
)paren
(brace
r_case
id|PM_RESUME
suffix:colon
id|MSC2
op_assign
(paren
id|MSC2
op_amp
l_int|0x0000ffff
)paren
op_or
l_int|0xE4510000
suffix:semicolon
multiline_comment|/* Set MSC2 correctly */
id|H3800_ASIC2_GPIOPIOD
op_assign
id|asic2_data
suffix:semicolon
id|H3800_ASIC2_GPIODIR
op_assign
id|GPIO2_PEN_IRQ
op_or
id|GPIO2_SD_DETECT
op_or
id|GPIO2_EAR_IN_N
op_or
id|GPIO2_USB_DETECT_N
op_or
id|GPIO2_SD_CON_SLT
suffix:semicolon
id|H3800_ASIC1_GPIO_OUT
op_assign
id|asic1_data
suffix:semicolon
r_if
c_cond
(paren
id|ipaq_model_ops.pm_callback_aux
)paren
id|result
op_assign
id|ipaq_model_ops
dot
id|pm_callback_aux
c_func
(paren
id|req
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PM_SUSPEND
suffix:colon
r_if
c_cond
(paren
id|ipaq_model_ops.pm_callback_aux
op_logical_and
(paren
(paren
id|result
op_assign
id|ipaq_model_ops
dot
id|pm_callback_aux
c_func
(paren
id|req
)paren
)paren
op_ne
l_int|0
)paren
)paren
r_return
id|result
suffix:semicolon
id|asic1_data
op_assign
id|H3800_ASIC1_GPIO_OUT
suffix:semicolon
id|asic2_data
op_assign
id|H3800_ASIC2_GPIOPIOD
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|__FUNCTION__
l_string|&quot;: unrecognized PM callback&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|ipaq_model_ops
id|h3800_model_ops
id|__initdata
op_assign
(brace
dot
id|generic_name
op_assign
l_string|&quot;3800&quot;
comma
dot
id|control
op_assign
id|h3800_control_egpio
comma
dot
id|read
op_assign
id|h3800_read_egpio
comma
dot
id|pm_callback
op_assign
id|h3800_pm_callback
)brace
suffix:semicolon
DECL|macro|MAX_ASIC_ISR_LOOPS
mdefine_line|#define MAX_ASIC_ISR_LOOPS    20
multiline_comment|/* The order of these is important - see #include &lt;asm/arch/irqs.h&gt; */
DECL|variable|kpio_irq_mask
r_static
id|u32
id|kpio_irq_mask
(braket
)braket
op_assign
(brace
id|KPIO_KEY_ALL
comma
id|KPIO_SPI_INT
comma
id|KPIO_OWM_INT
comma
id|KPIO_ADC_INT
comma
id|KPIO_UART_0_INT
comma
id|KPIO_UART_1_INT
comma
id|KPIO_TIMER_0_INT
comma
id|KPIO_TIMER_1_INT
comma
id|KPIO_TIMER_2_INT
)brace
suffix:semicolon
DECL|variable|gpio_irq_mask
r_static
id|u32
id|gpio_irq_mask
(braket
)braket
op_assign
(brace
id|GPIO2_PEN_IRQ
comma
id|GPIO2_SD_DETECT
comma
id|GPIO2_EAR_IN_N
comma
id|GPIO2_USB_DETECT_N
comma
id|GPIO2_SD_CON_SLT
comma
)brace
suffix:semicolon
DECL|function|h3800_IRQ_demux
r_static
r_void
id|h3800_IRQ_demux
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
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
l_int|0
)paren
id|printk
c_func
(paren
id|__FUNCTION__
l_string|&quot;: interrupt received&bslash;n&quot;
)paren
suffix:semicolon
id|desc-&gt;chip
op_member_access_from_pointer
id|ack
c_func
(paren
id|irq
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_ASIC_ISR_LOOPS
op_logical_and
(paren
id|GPLR
op_amp
id|GPIO_H3800_ASIC
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|u32
id|irq
suffix:semicolon
r_int
id|j
suffix:semicolon
multiline_comment|/* KPIO */
id|irq
op_assign
id|H3800_ASIC2_KPIINTFLAG
suffix:semicolon
r_if
c_cond
(paren
l_int|0
)paren
id|printk
c_func
(paren
id|__FUNCTION__
l_string|&quot; KPIO 0x%08X&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|H3800_KPIO_IRQ_COUNT
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|irq
op_amp
id|kpio_irq_mask
(braket
id|j
)braket
)paren
id|do_edge_IRQ
c_func
(paren
id|H3800_KPIO_IRQ_COUNT
op_plus
id|j
comma
id|irq_desc
op_plus
id|H3800_KPIO_IRQ_COUNT
op_plus
id|j
comma
id|regs
)paren
suffix:semicolon
multiline_comment|/* GPIO2 */
id|irq
op_assign
id|H3800_ASIC2_GPIINTFLAG
suffix:semicolon
r_if
c_cond
(paren
l_int|0
)paren
id|printk
c_func
(paren
id|__FUNCTION__
l_string|&quot; GPIO 0x%08X&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|H3800_GPIO_IRQ_COUNT
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|irq
op_amp
id|gpio_irq_mask
(braket
id|j
)braket
)paren
id|do_edge_IRQ
c_func
(paren
id|H3800_GPIO_IRQ_COUNT
op_plus
id|j
comma
id|irq_desc
op_plus
id|H3800_GPIO_IRQ_COUNT
op_plus
id|j
comma
id|regs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_ge
id|MAX_ASIC_ISR_LOOPS
)paren
id|printk
c_func
(paren
id|__FUNCTION__
l_string|&quot;: interrupt processing overrun&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* For level-based interrupts */
id|desc-&gt;chip
op_member_access_from_pointer
id|unmask
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|h3800_irq
r_static
r_struct
id|irqaction
id|h3800_irq
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;h3800_asic&quot;
comma
dot
id|handler
op_assign
id|h3800_IRQ_demux
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
)brace
suffix:semicolon
DECL|variable|kpio_int_shadow
id|u32
id|kpio_int_shadow
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* mask_ack &lt;- IRQ is first serviced.&n;       mask &lt;- IRQ is disabled.&n;     unmask &lt;- IRQ is enabled&n;&n;     The INTCLR registers are poorly documented.  I believe that writing&n;     a &quot;1&quot; to the register clears the specific interrupt, but the documentation&n;     indicates writing a &quot;0&quot; clears the interrupt.  In any case, they shouldn&squot;t&n;     be read (that&squot;s the INTFLAG register)&n; */
DECL|function|h3800_mask_ack_kpio_irq
r_static
r_void
id|h3800_mask_ack_kpio_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u32
id|mask
op_assign
id|kpio_irq_mask
(braket
id|irq
op_minus
id|H3800_KPIO_IRQ_START
)braket
suffix:semicolon
id|kpio_int_shadow
op_and_assign
op_complement
id|mask
suffix:semicolon
id|H3800_ASIC2_KPIINTSTAT
op_assign
id|kpio_int_shadow
suffix:semicolon
id|H3800_ASIC2_KPIINTCLR
op_assign
id|mask
suffix:semicolon
)brace
DECL|function|h3800_mask_kpio_irq
r_static
r_void
id|h3800_mask_kpio_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u32
id|mask
op_assign
id|kpio_irq_mask
(braket
id|irq
op_minus
id|H3800_KPIO_IRQ_START
)braket
suffix:semicolon
id|kpio_int_shadow
op_and_assign
op_complement
id|mask
suffix:semicolon
id|H3800_ASIC2_KPIINTSTAT
op_assign
id|kpio_int_shadow
suffix:semicolon
)brace
DECL|function|h3800_unmask_kpio_irq
r_static
r_void
id|h3800_unmask_kpio_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u32
id|mask
op_assign
id|kpio_irq_mask
(braket
id|irq
op_minus
id|H3800_KPIO_IRQ_START
)braket
suffix:semicolon
id|kpio_int_shadow
op_or_assign
id|mask
suffix:semicolon
id|H3800_ASIC2_KPIINTSTAT
op_assign
id|kpio_int_shadow
suffix:semicolon
)brace
DECL|function|h3800_mask_ack_gpio_irq
r_static
r_void
id|h3800_mask_ack_gpio_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u32
id|mask
op_assign
id|gpio_irq_mask
(braket
id|irq
op_minus
id|H3800_GPIO_IRQ_START
)braket
suffix:semicolon
id|H3800_ASIC2_GPIINTSTAT
op_and_assign
op_complement
id|mask
suffix:semicolon
id|H3800_ASIC2_GPIINTCLR
op_assign
id|mask
suffix:semicolon
)brace
DECL|function|h3800_mask_gpio_irq
r_static
r_void
id|h3800_mask_gpio_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u32
id|mask
op_assign
id|gpio_irq_mask
(braket
id|irq
op_minus
id|H3800_GPIO_IRQ_START
)braket
suffix:semicolon
id|H3800_ASIC2_GPIINTSTAT
op_and_assign
op_complement
id|mask
suffix:semicolon
)brace
DECL|function|h3800_unmask_gpio_irq
r_static
r_void
id|h3800_unmask_gpio_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u32
id|mask
op_assign
id|gpio_irq_mask
(braket
id|irq
op_minus
id|H3800_GPIO_IRQ_START
)braket
suffix:semicolon
id|H3800_ASIC2_GPIINTSTAT
op_or_assign
id|mask
suffix:semicolon
)brace
DECL|function|h3800_init_irq
r_static
r_void
id|__init
id|h3800_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Initialize standard IRQs */
id|sa1100_init_irq
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Disable all IRQs and set up clock */
id|H3800_ASIC2_KPIINTSTAT
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Disable all interrupts */
id|H3800_ASIC2_GPIINTSTAT
op_assign
l_int|0
suffix:semicolon
id|H3800_ASIC2_KPIINTCLR
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Clear all KPIO interrupts */
id|H3800_ASIC2_GPIINTCLR
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Clear all GPIO interrupts */
singleline_comment|//&t;H3800_ASIC2_KPIINTCLR&t;   =  0xffff;&t;  /* Clear all KPIO interrupts */
singleline_comment|//&t;H3800_ASIC2_GPIINTCLR&t;   =  0xffff;&t;  /* Clear all GPIO interrupts */
id|H3800_ASIC2_CLOCK_Enable
op_or_assign
id|ASIC2_CLOCK_EX0
suffix:semicolon
multiline_comment|/* 32 kHZ crystal on */
id|H3800_ASIC2_INTR_ClockPrescale
op_or_assign
id|ASIC2_INTCPS_SET
suffix:semicolon
id|H3800_ASIC2_INTR_ClockPrescale
op_assign
id|ASIC2_INTCPS_CPS
c_func
(paren
l_int|0x0e
)paren
op_or
id|ASIC2_INTCPS_SET
suffix:semicolon
id|H3800_ASIC2_INTR_TimerSet
op_assign
l_int|1
suffix:semicolon
macro_line|#if 0
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|H3800_KPIO_IRQ_COUNT
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|irq
op_assign
id|i
op_plus
id|H3800_KPIO_IRQ_START
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|valid
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|probe_ok
op_assign
l_int|1
suffix:semicolon
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|h3800_kpio_irqchip
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|H3800_GPIO_IRQ_COUNT
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|irq
op_assign
id|i
op_plus
id|H3800_GPIO_IRQ_START
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|valid
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|probe_ok
op_assign
l_int|1
suffix:semicolon
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|h3800_gpio_irqchip
)paren
suffix:semicolon
)brace
macro_line|#endif
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_H3800_ASIC
comma
id|IRQT_RISING
)paren
suffix:semicolon
id|set_irq_chained_handler
c_func
(paren
id|IRQ_GPIO_H3800_ASIC
comma
op_amp
id|h3800_IRQ_demux
)paren
suffix:semicolon
)brace
DECL|macro|ASIC1_OUTPUTS
mdefine_line|#define ASIC1_OUTPUTS&t; 0x7fff   /* First 15 bits are used */
DECL|function|h3800_map_io
r_static
r_void
id|__init
id|h3800_map_io
c_func
(paren
r_void
)paren
(brace
id|h3xxx_map_io
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Add wakeup on AC plug/unplug */
id|PWER
op_or_assign
id|PWER_GPIO12
suffix:semicolon
multiline_comment|/* Initialize h3800-specific values here */
id|GPCR
op_assign
l_int|0x0fffffff
suffix:semicolon
multiline_comment|/* All outputs are set low by default */
id|GAFR
op_assign
id|GPIO_H3800_CLK_OUT
op_or
id|GPIO_LDD15
op_or
id|GPIO_LDD14
op_or
id|GPIO_LDD13
op_or
id|GPIO_LDD12
op_or
id|GPIO_LDD11
op_or
id|GPIO_LDD10
op_or
id|GPIO_LDD9
op_or
id|GPIO_LDD8
suffix:semicolon
id|GPDR
op_assign
id|GPIO_H3800_CLK_OUT
op_or
id|GPIO_H3600_COM_RTS
op_or
id|GPIO_H3600_L3_CLOCK
op_or
id|GPIO_H3600_L3_MODE
op_or
id|GPIO_H3600_L3_DATA
op_or
id|GPIO_LDD15
op_or
id|GPIO_LDD14
op_or
id|GPIO_LDD13
op_or
id|GPIO_LDD12
op_or
id|GPIO_LDD11
op_or
id|GPIO_LDD10
op_or
id|GPIO_LDD9
op_or
id|GPIO_LDD8
suffix:semicolon
id|TUCR
op_assign
id|TUCR_3_6864MHz
suffix:semicolon
multiline_comment|/* Seems to be used only for the Bluetooth UART */
multiline_comment|/* Fix the memory bus */
id|MSC2
op_assign
(paren
id|MSC2
op_amp
l_int|0x0000ffff
)paren
op_or
l_int|0xE4510000
suffix:semicolon
multiline_comment|/* Set up ASIC #1 */
id|H3800_ASIC1_GPIO_DIR
op_assign
id|ASIC1_OUTPUTS
suffix:semicolon
multiline_comment|/* All outputs */
id|H3800_ASIC1_GPIO_MASK
op_assign
id|ASIC1_OUTPUTS
suffix:semicolon
multiline_comment|/* No interrupts */
id|H3800_ASIC1_GPIO_SLEEP_MASK
op_assign
id|ASIC1_OUTPUTS
suffix:semicolon
id|H3800_ASIC1_GPIO_SLEEP_DIR
op_assign
id|ASIC1_OUTPUTS
suffix:semicolon
id|H3800_ASIC1_GPIO_SLEEP_OUT
op_assign
id|GPIO1_EAR_ON_N
suffix:semicolon
id|H3800_ASIC1_GPIO_BATT_FAULT_DIR
op_assign
id|ASIC1_OUTPUTS
suffix:semicolon
id|H3800_ASIC1_GPIO_BATT_FAULT_OUT
op_assign
id|GPIO1_EAR_ON_N
suffix:semicolon
id|H3800_ASIC1_GPIO_OUT
op_assign
id|GPIO1_IR_ON_N
op_or
id|GPIO1_RS232_ON
op_or
id|GPIO1_EAR_ON_N
suffix:semicolon
multiline_comment|/* Set up ASIC #2 */
id|H3800_ASIC2_GPIOPIOD
op_assign
id|GPIO2_IN_Y1_N
op_or
id|GPIO2_IN_X1_N
suffix:semicolon
id|H3800_ASIC2_GPOBFSTAT
op_assign
id|GPIO2_IN_Y1_N
op_or
id|GPIO2_IN_X1_N
suffix:semicolon
id|H3800_ASIC2_GPIODIR
op_assign
id|GPIO2_PEN_IRQ
op_or
id|GPIO2_SD_DETECT
op_or
id|GPIO2_EAR_IN_N
op_or
id|GPIO2_USB_DETECT_N
op_or
id|GPIO2_SD_CON_SLT
suffix:semicolon
multiline_comment|/* TODO : Set sleep states &amp; battery fault states */
multiline_comment|/* Clear VPP Enable */
id|H3800_ASIC2_FlashWP_VPP_ON
op_assign
l_int|0
suffix:semicolon
id|ipaq_model_ops
op_assign
id|h3800_model_ops
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|H3800
comma
l_string|&quot;Compaq iPAQ H3800&quot;
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
id|h3800_map_io
)paren
id|INITIRQ
c_func
(paren
id|h3800_init_irq
)paren
id|MACHINE_END
macro_line|#endif /* CONFIG_SA1100_H3800 */
eof
