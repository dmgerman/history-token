multiline_comment|/*&n; * Hardware definitions for Compaq iPAQ H3xxx Handheld Computers&n; *&n; * Copyright 2000,1 Compaq Computer Corporation.&n; *&n; * Use consistent with the GNU GPL is permitted,&n; * provided that this copyright notice is&n; * preserved in its entirety in all copies and derived works.&n; *&n; * COMPAQ COMPUTER CORPORATION MAKES NO WARRANTIES, EXPRESSED OR IMPLIED,&n; * AS TO THE USEFULNESS OR CORRECTNESS OF THIS CODE OR ITS&n; * FITNESS FOR ANY PARTICULAR PURPOSE.&n; *&n; * Author: Jamey Hicks.&n; *&n; * History:&n; *&n; * 2001-10-??&t;Andrew Christian   Added support for iPAQ H3800&n; *&t;&t;&t;&t;   and abstracted EGPIO interface.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/arch/h3600_gpio.h&gt;
macro_line|#include &quot;generic.h&quot;
multiline_comment|/*&n; * H3600 has extended, write-only memory-mapped GPIO&squot;s&n; * H3100 has 1/2 extended, write-only GPIO and 1/2 on&n; *&t; regular GPIO lines.&n; * H3800 has memory-mapped GPIO through ASIC1 &amp; 2&n; */
DECL|macro|H3600_EGPIO
mdefine_line|#define H3600_EGPIO&t;(*(volatile unsigned int *)H3600_EGPIO_VIRT)
DECL|variable|h3600_egpio
r_static
r_int
r_int
id|h3600_egpio
suffix:semicolon
multiline_comment|/************************* H3100 *************************/
DECL|macro|H3100_DIRECT_EGPIO
mdefine_line|#define H3100_DIRECT_EGPIO (GPIO_H3100_BT_ON&t;  &bslash;&n;&t;&t;&t;  | GPIO_H3100_GPIO3&t;  &bslash;&n;&t;&t;&t;  | GPIO_H3100_QMUTE&t;  &bslash;&n;&t;&t;&t;  | GPIO_H3100_LCD_3V_ON  &bslash;&n;&t;&t;&t;  | GPIO_H3100_AUD_ON&t;  &bslash;&n;&t;&t;&t;  | GPIO_H3100_AUD_PWR_ON &bslash;&n;&t;&t;&t;  | GPIO_H3100_IR_ON&t;  &bslash;&n;&t;&t;&t;  | GPIO_H3100_IR_FSEL)
DECL|function|h3100_init_egpio
r_static
r_void
id|h3100_init_egpio
c_func
(paren
r_void
)paren
(brace
id|GPDR
op_or_assign
id|H3100_DIRECT_EGPIO
suffix:semicolon
id|GPCR
op_assign
id|H3100_DIRECT_EGPIO
suffix:semicolon
multiline_comment|/* Initially all off */
multiline_comment|/* Older bootldrs put GPIO2-9 in alternate mode on the&n;&t;   assumption that they are used for video */
id|GAFR
op_and_assign
op_complement
id|H3100_DIRECT_EGPIO
suffix:semicolon
id|h3600_egpio
op_assign
id|EGPIO_H3600_RS232_ON
suffix:semicolon
id|H3600_EGPIO
op_assign
id|h3600_egpio
suffix:semicolon
)brace
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
id|IPAQ_EGPIO_LCD_ON
suffix:colon
id|egpio
op_or_assign
id|EGPIO_H3600_LCD_ON
suffix:semicolon
id|gpio
op_or_assign
id|GPIO_H3100_LCD_3V_ON
suffix:semicolon
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
id|h3600_egpio
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
id|h3600_egpio
op_and_assign
op_complement
id|egpio
suffix:semicolon
id|GPCR
op_assign
id|gpio
suffix:semicolon
)brace
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
multiline_comment|/*&n;&t;if ( x != IPAQ_EGPIO_VPP_ON ) {&n;&t;&t;printk(&quot;%s: type=%d (%s) gpio=0x%x (0x%x) egpio=0x%x (0x%x) setp=%d&bslash;n&quot;,&n;&t;&t;       __FUNCTION__,&n;&t;&t;       x, egpio_names[x], GPLR, gpio, h3600_egpio, egpio, setp );&n;&t;}&n;&t;*/
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
id|h3600_egpio
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
id|model
suffix:colon
id|IPAQ_H3100
comma
id|generic_name
suffix:colon
l_string|&quot;3100&quot;
comma
id|initialize
suffix:colon
id|h3100_init_egpio
comma
id|control
suffix:colon
id|h3100_control_egpio
comma
id|read
suffix:colon
id|h3100_read_egpio
)brace
suffix:semicolon
multiline_comment|/************************* H3600 *************************/
DECL|function|h3600_init_egpio
r_static
r_void
id|h3600_init_egpio
c_func
(paren
r_void
)paren
(brace
id|h3600_egpio
op_assign
id|EGPIO_H3600_RS232_ON
suffix:semicolon
id|H3600_EGPIO
op_assign
id|h3600_egpio
suffix:semicolon
)brace
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
id|IPAQ_EGPIO_LCD_ON
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
DECL|variable|__initdata
r_static
r_struct
id|ipaq_model_ops
id|h3600_model_ops
id|__initdata
op_assign
(brace
id|model
suffix:colon
id|IPAQ_H3600
comma
id|generic_name
suffix:colon
l_string|&quot;3600&quot;
comma
id|initialize
suffix:colon
id|h3600_init_egpio
comma
id|control
suffix:colon
id|h3600_control_egpio
comma
id|read
suffix:colon
id|h3600_read_egpio
)brace
suffix:semicolon
multiline_comment|/************************* H3800 *************************/
DECL|macro|ASIC1_OUTPUTS
mdefine_line|#define ASIC1_OUTPUTS&t; 0x7fff   /* First 15 bits are used */
DECL|variable|h3800_asic1_gpio
r_static
r_int
r_int
id|h3800_asic1_gpio
suffix:semicolon
DECL|variable|h3800_asic2_gpio
r_static
r_int
r_int
id|h3800_asic2_gpio
suffix:semicolon
DECL|function|h3800_init_egpio
r_static
r_void
id|h3800_init_egpio
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Set up ASIC #1 */
id|H3800_ASIC1_GPIO_Direction
op_assign
id|ASIC1_OUTPUTS
suffix:semicolon
multiline_comment|/* All outputs */
id|H3800_ASIC1_GPIO_Mask
op_assign
id|ASIC1_OUTPUTS
suffix:semicolon
multiline_comment|/* No interrupts */
id|H3800_ASIC1_GPIO_SleepMask
op_assign
id|ASIC1_OUTPUTS
suffix:semicolon
id|H3800_ASIC1_GPIO_SleepDir
op_assign
id|ASIC1_OUTPUTS
suffix:semicolon
id|H3800_ASIC1_GPIO_SleepOut
op_assign
id|GPIO_H3800_ASIC1_EAR_ON_N
suffix:semicolon
id|H3800_ASIC1_GPIO_BattFaultDir
op_assign
id|ASIC1_OUTPUTS
suffix:semicolon
id|H3800_ASIC1_GPIO_BattFaultOut
op_assign
id|GPIO_H3800_ASIC1_EAR_ON_N
suffix:semicolon
id|h3800_asic1_gpio
op_assign
id|GPIO_H3800_ASIC1_IR_ON_N
multiline_comment|/* TODO: Check IR level */
op_or
id|GPIO_H3800_ASIC1_RS232_ON
op_or
id|GPIO_H3800_ASIC1_EAR_ON_N
suffix:semicolon
id|H3800_ASIC1_GPIO_Out
op_assign
id|h3800_asic1_gpio
suffix:semicolon
multiline_comment|/* Set up ASIC #2 */
id|H3800_ASIC2_GPIO_Direction
op_assign
id|GPIO_H3800_ASIC2_PEN_IRQ
op_or
id|GPIO_H3800_ASIC2_SD_DETECT
op_or
id|GPIO_H3800_ASIC2_EAR_IN_N
op_or
id|GPIO_H3800_ASIC2_USB_DETECT_N
op_or
id|GPIO_H3800_ASIC2_SD_CON_SLT
suffix:semicolon
id|h3800_asic2_gpio
op_assign
id|GPIO_H3800_ASIC2_IN_Y1_N
op_or
id|GPIO_H3800_ASIC2_IN_X1_N
suffix:semicolon
id|H3800_ASIC2_GPIO_Data
op_assign
id|h3800_asic2_gpio
suffix:semicolon
id|H3800_ASIC2_GPIO_BattFaultOut
op_assign
id|h3800_asic2_gpio
suffix:semicolon
multiline_comment|/* TODO : Set sleep states &amp; battery fault states */
multiline_comment|/* Clear VPP Enable */
id|H3800_ASIC1_FlashWP_VPP_ON
op_assign
l_int|0
suffix:semicolon
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
r_int
r_int
id|set_asic1_egpio
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|clear_asic1_egpio
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
id|IPAQ_EGPIO_LCD_ON
suffix:colon
id|set_asic1_egpio
op_or_assign
id|GPIO_H3800_ASIC1_LCD_5V_ON
op_or
id|GPIO_H3800_ASIC1_LCD_ON
op_or
id|GPIO_H3800_ASIC1_LCD_PCI
op_or
id|GPIO_H3800_ASIC1_VGH_ON
op_or
id|GPIO_H3800_ASIC1_VGL_ON
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_CODEC_NRESET
suffix:colon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_AUDIO_ON
suffix:colon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_QMUTE
suffix:colon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_OPT_NVRAM_ON
suffix:colon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_OPT_ON
suffix:colon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_CARD_RESET
suffix:colon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_OPT_RESET
suffix:colon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_IR_ON
suffix:colon
id|clear_asic1_egpio
op_or_assign
id|GPIO_H3800_ASIC1_IR_ON_N
suffix:semicolon
multiline_comment|/* TODO : This is backwards? */
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
id|set_asic1_egpio
op_or_assign
id|GPIO_H3800_ASIC1_RS232_ON
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPAQ_EGPIO_VPP_ON
suffix:colon
id|H3800_ASIC1_FlashWP_VPP_ON
op_assign
id|setp
suffix:semicolon
r_break
suffix:semicolon
)brace
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
id|h3800_asic1_gpio
op_or_assign
id|set_asic1_egpio
suffix:semicolon
id|h3800_asic1_gpio
op_and_assign
op_complement
id|clear_asic1_egpio
suffix:semicolon
)brace
r_else
(brace
id|h3800_asic1_gpio
op_and_assign
op_complement
id|set_asic1_egpio
suffix:semicolon
id|h3800_asic1_gpio
op_or_assign
id|clear_asic1_egpio
suffix:semicolon
)brace
id|H3800_ASIC1_GPIO_Out
op_assign
id|h3800_asic1_gpio
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
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
id|h3800_asic1_gpio
op_or
(paren
id|h3800_asic2_gpio
op_lshift
l_int|16
)paren
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
id|model
suffix:colon
id|IPAQ_H3800
comma
id|generic_name
suffix:colon
l_string|&quot;3800&quot;
comma
id|initialize
suffix:colon
id|h3800_init_egpio
comma
id|control
suffix:colon
id|h3800_control_egpio
comma
id|read
suffix:colon
id|h3800_read_egpio
)brace
suffix:semicolon
DECL|function|h3600_lcd_power
r_static
r_void
id|h3600_lcd_power
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
id|set_h3600_egpio
c_func
(paren
id|IPAQ_EGPIO_LCD_ON
)paren
suffix:semicolon
r_else
id|clr_h3600_egpio
c_func
(paren
id|IPAQ_EGPIO_LCD_ON
)paren
suffix:semicolon
)brace
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
DECL|function|h3600_init_model_ops
r_static
r_int
id|__init
id|h3600_init_model_ops
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_h3xxx
c_func
(paren
)paren
)paren
(brace
id|sa1100fb_lcd_power
op_assign
id|h3600_lcd_power
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_h3100
c_func
(paren
)paren
)paren
(brace
id|ipaq_model_ops
op_assign
id|h3100_model_ops
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|machine_is_h3600
c_func
(paren
)paren
)paren
(brace
id|ipaq_model_ops
op_assign
id|h3600_model_ops
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|machine_is_h3800
c_func
(paren
)paren
)paren
(brace
id|ipaq_model_ops
op_assign
id|h3800_model_ops
suffix:semicolon
)brace
id|init_h3600_egpio
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|h3600_init_model_ops
id|__initcall
c_func
(paren
id|h3600_init_model_ops
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
multiline_comment|/* virtual&t;       physical    length      type */
(brace
id|H3600_EGPIO_VIRT
comma
l_int|0x49000000
comma
l_int|0x01000000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* EGPIO 0&t;&t; CS#5 */
(brace
id|H3600_BANK_2_VIRT
comma
l_int|0x10000000
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
l_int|0x40000000
comma
l_int|0x00800000
comma
id|MT_DEVICE
)brace
multiline_comment|/* static memory bank 4  CS#4 */
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
id|sa1100_register_uart
c_func
(paren
l_int|1
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* isn&squot;t this one driven elsewhere? */
multiline_comment|/*&n;&t; * Default GPIO settings.  Should be set by machine&n;&t; */
id|GPCR
op_assign
l_int|0x0fffffff
suffix:semicolon
singleline_comment|//&t;GPDR = 0x0401f3fc;
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
id|init_h3600_egpio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Ensure those pins are outputs and driving low.&n;&t; */
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
id|h3600_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
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
id|h3600_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
eof
