multiline_comment|/*&n; *&n; * Definitions for H3600 Handheld Computer&n; *&n; * Copyright 2000 Compaq Computer Corporation.&n; *&n; * Use consistent with the GNU GPL is permitted,&n; * provided that this copyright notice is&n; * preserved in its entirety in all copies and derived works.&n; *&n; * COMPAQ COMPUTER CORPORATION MAKES NO WARRANTIES, EXPRESSED OR IMPLIED,&n; * AS TO THE USEFULNESS OR CORRECTNESS OF THIS CODE OR ITS&n; * FITNESS FOR ANY PARTICULAR PURPOSE.&n; *&n; * Author: Jamey Hicks.&n; *&n; * History:&n; *&n; * 2001-10-??&t;Andrew Christian   Added support for iPAQ H3800&n; *&n; */
macro_line|#ifndef _INCLUDE_H3600_H_
DECL|macro|_INCLUDE_H3600_H_
mdefine_line|#define _INCLUDE_H3600_H_
multiline_comment|/* generalized support for H3xxx series Compaq Pocket PC&squot;s */
DECL|macro|machine_is_h3xxx
mdefine_line|#define machine_is_h3xxx() (machine_is_h3100() || machine_is_h3600() || machine_is_h3800())
multiline_comment|/* Physical memory regions corresponding to chip selects */
DECL|macro|H3600_EGPIO_PHYS
mdefine_line|#define H3600_EGPIO_PHYS     (SA1100_CS5_PHYS + 0x01000000)
DECL|macro|H3600_BANK_2_PHYS
mdefine_line|#define H3600_BANK_2_PHYS    SA1100_CS2_PHYS
DECL|macro|H3600_BANK_4_PHYS
mdefine_line|#define H3600_BANK_4_PHYS    SA1100_CS4_PHYS
multiline_comment|/* Virtual memory regions corresponding to chip selects 2 &amp; 4 (used on sleeves) */
DECL|macro|H3600_EGPIO_VIRT
mdefine_line|#define H3600_EGPIO_VIRT     0xf0000000
DECL|macro|H3600_BANK_2_VIRT
mdefine_line|#define H3600_BANK_2_VIRT    0xf1000000
DECL|macro|H3600_BANK_4_VIRT
mdefine_line|#define H3600_BANK_4_VIRT    0xf3800000
multiline_comment|/*&n;   Machine-independent GPIO definitions&n;   --- these are common across all current iPAQ platforms&n;*/
DECL|macro|GPIO_H3600_NPOWER_BUTTON
mdefine_line|#define GPIO_H3600_NPOWER_BUTTON&t;GPIO_GPIO (0)&t;/* Also known as the &quot;off button&quot;  */
DECL|macro|GPIO_H3600_PCMCIA_CD1
mdefine_line|#define GPIO_H3600_PCMCIA_CD1&t;&t;GPIO_GPIO (10)
DECL|macro|GPIO_H3600_PCMCIA_IRQ1
mdefine_line|#define GPIO_H3600_PCMCIA_IRQ1&t;&t;GPIO_GPIO (11)
multiline_comment|/* UDA1341 L3 Interface */
DECL|macro|GPIO_H3600_L3_DATA
mdefine_line|#define GPIO_H3600_L3_DATA&t;&t;GPIO_GPIO (14)
DECL|macro|GPIO_H3600_L3_MODE
mdefine_line|#define GPIO_H3600_L3_MODE&t;&t;GPIO_GPIO (15)
DECL|macro|GPIO_H3600_L3_CLOCK
mdefine_line|#define GPIO_H3600_L3_CLOCK&t;&t;GPIO_GPIO (16)
DECL|macro|GPIO_H3600_PCMCIA_CD0
mdefine_line|#define GPIO_H3600_PCMCIA_CD0&t;&t;GPIO_GPIO (17)
DECL|macro|GPIO_H3600_SYS_CLK
mdefine_line|#define GPIO_H3600_SYS_CLK&t;&t;GPIO_GPIO (19)
DECL|macro|GPIO_H3600_PCMCIA_IRQ0
mdefine_line|#define GPIO_H3600_PCMCIA_IRQ0&t;&t;GPIO_GPIO (21)
DECL|macro|GPIO_H3600_COM_DCD
mdefine_line|#define GPIO_H3600_COM_DCD&t;&t;GPIO_GPIO (23)
DECL|macro|GPIO_H3600_OPT_IRQ
mdefine_line|#define GPIO_H3600_OPT_IRQ&t;&t;GPIO_GPIO (24)
DECL|macro|GPIO_H3600_COM_CTS
mdefine_line|#define GPIO_H3600_COM_CTS&t;&t;GPIO_GPIO (25)
DECL|macro|GPIO_H3600_COM_RTS
mdefine_line|#define GPIO_H3600_COM_RTS&t;&t;GPIO_GPIO (26)
DECL|macro|IRQ_GPIO_H3600_NPOWER_BUTTON
mdefine_line|#define IRQ_GPIO_H3600_NPOWER_BUTTON&t;IRQ_GPIO0
DECL|macro|IRQ_GPIO_H3600_PCMCIA_CD1
mdefine_line|#define IRQ_GPIO_H3600_PCMCIA_CD1&t;IRQ_GPIO10
DECL|macro|IRQ_GPIO_H3600_PCMCIA_IRQ1
mdefine_line|#define IRQ_GPIO_H3600_PCMCIA_IRQ1&t;IRQ_GPIO11
DECL|macro|IRQ_GPIO_H3600_PCMCIA_CD0
mdefine_line|#define IRQ_GPIO_H3600_PCMCIA_CD0&t;IRQ_GPIO17
DECL|macro|IRQ_GPIO_H3600_PCMCIA_IRQ0
mdefine_line|#define IRQ_GPIO_H3600_PCMCIA_IRQ0&t;IRQ_GPIO21
DECL|macro|IRQ_GPIO_H3600_COM_DCD
mdefine_line|#define IRQ_GPIO_H3600_COM_DCD&t;&t;IRQ_GPIO23
DECL|macro|IRQ_GPIO_H3600_OPT_IRQ
mdefine_line|#define IRQ_GPIO_H3600_OPT_IRQ&t;&t;IRQ_GPIO24
DECL|macro|IRQ_GPIO_H3600_COM_CTS
mdefine_line|#define IRQ_GPIO_H3600_COM_CTS&t;&t;IRQ_GPIO25
macro_line|#ifndef __ASSEMBLY__
DECL|enum|ipaq_egpio_type
r_enum
id|ipaq_egpio_type
(brace
DECL|enumerator|IPAQ_EGPIO_LCD_POWER
id|IPAQ_EGPIO_LCD_POWER
comma
multiline_comment|/* Power to the LCD panel */
DECL|enumerator|IPAQ_EGPIO_CODEC_NRESET
id|IPAQ_EGPIO_CODEC_NRESET
comma
multiline_comment|/* Clear to reset the audio codec (remember to return high) */
DECL|enumerator|IPAQ_EGPIO_AUDIO_ON
id|IPAQ_EGPIO_AUDIO_ON
comma
multiline_comment|/* Audio power */
DECL|enumerator|IPAQ_EGPIO_QMUTE
id|IPAQ_EGPIO_QMUTE
comma
multiline_comment|/* Audio muting */
DECL|enumerator|IPAQ_EGPIO_OPT_NVRAM_ON
id|IPAQ_EGPIO_OPT_NVRAM_ON
comma
multiline_comment|/* Non-volatile RAM on extension sleeves (SPI interface) */
DECL|enumerator|IPAQ_EGPIO_OPT_ON
id|IPAQ_EGPIO_OPT_ON
comma
multiline_comment|/* Power to extension sleeves */
DECL|enumerator|IPAQ_EGPIO_CARD_RESET
id|IPAQ_EGPIO_CARD_RESET
comma
multiline_comment|/* Reset PCMCIA cards on extension sleeve (???) */
DECL|enumerator|IPAQ_EGPIO_OPT_RESET
id|IPAQ_EGPIO_OPT_RESET
comma
multiline_comment|/* Reset option pack (???) */
DECL|enumerator|IPAQ_EGPIO_IR_ON
id|IPAQ_EGPIO_IR_ON
comma
multiline_comment|/* IR sensor/emitter power */
DECL|enumerator|IPAQ_EGPIO_IR_FSEL
id|IPAQ_EGPIO_IR_FSEL
comma
multiline_comment|/* IR speed selection 1-&gt;fast, 0-&gt;slow */
DECL|enumerator|IPAQ_EGPIO_RS232_ON
id|IPAQ_EGPIO_RS232_ON
comma
multiline_comment|/* Maxim RS232 chip power */
DECL|enumerator|IPAQ_EGPIO_VPP_ON
id|IPAQ_EGPIO_VPP_ON
comma
multiline_comment|/* Turn on power to flash programming */
DECL|enumerator|IPAQ_EGPIO_LCD_ENABLE
id|IPAQ_EGPIO_LCD_ENABLE
comma
multiline_comment|/* Enable/disable LCD controller */
)brace
suffix:semicolon
DECL|struct|ipaq_model_ops
r_struct
id|ipaq_model_ops
(brace
DECL|member|generic_name
r_const
r_char
op_star
id|generic_name
suffix:semicolon
DECL|member|control
r_void
(paren
op_star
id|control
)paren
(paren
r_enum
id|ipaq_egpio_type
comma
r_int
)paren
suffix:semicolon
DECL|member|read
r_int
r_int
(paren
op_star
id|read
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|blank_callback
r_void
(paren
op_star
id|blank_callback
)paren
(paren
r_int
id|blank
)paren
suffix:semicolon
DECL|member|pm_callback
r_int
(paren
op_star
id|pm_callback
)paren
(paren
r_int
id|req
)paren
suffix:semicolon
multiline_comment|/* Primary model callback */
DECL|member|pm_callback_aux
r_int
(paren
op_star
id|pm_callback_aux
)paren
(paren
r_int
id|req
)paren
suffix:semicolon
multiline_comment|/* Secondary callback (used by HAL modules) */
)brace
suffix:semicolon
r_extern
r_struct
id|ipaq_model_ops
id|ipaq_model_ops
suffix:semicolon
DECL|function|h3600_generic_name
r_static
id|__inline__
r_const
r_char
op_star
id|h3600_generic_name
c_func
(paren
r_void
)paren
(brace
r_return
id|ipaq_model_ops.generic_name
suffix:semicolon
)brace
DECL|function|assign_h3600_egpio
r_static
id|__inline__
r_void
id|assign_h3600_egpio
c_func
(paren
r_enum
id|ipaq_egpio_type
id|x
comma
r_int
id|level
)paren
(brace
r_if
c_cond
(paren
id|ipaq_model_ops.control
)paren
id|ipaq_model_ops
dot
id|control
c_func
(paren
id|x
comma
id|level
)paren
suffix:semicolon
)brace
DECL|function|clr_h3600_egpio
r_static
id|__inline__
r_void
id|clr_h3600_egpio
c_func
(paren
r_enum
id|ipaq_egpio_type
id|x
)paren
(brace
r_if
c_cond
(paren
id|ipaq_model_ops.control
)paren
id|ipaq_model_ops
dot
id|control
c_func
(paren
id|x
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|set_h3600_egpio
r_static
id|__inline__
r_void
id|set_h3600_egpio
c_func
(paren
r_enum
id|ipaq_egpio_type
id|x
)paren
(brace
r_if
c_cond
(paren
id|ipaq_model_ops.control
)paren
id|ipaq_model_ops
dot
id|control
c_func
(paren
id|x
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|read_h3600_egpio
r_static
id|__inline__
r_int
r_int
id|read_h3600_egpio
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ipaq_model_ops.read
)paren
r_return
id|ipaq_model_ops
dot
id|read
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|h3600_register_blank_callback
r_static
id|__inline__
r_int
id|h3600_register_blank_callback
c_func
(paren
r_void
(paren
op_star
id|f
)paren
(paren
r_int
)paren
)paren
(brace
id|ipaq_model_ops.blank_callback
op_assign
id|f
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|h3600_unregister_blank_callback
r_static
id|__inline__
r_void
id|h3600_unregister_blank_callback
c_func
(paren
r_void
(paren
op_star
id|f
)paren
(paren
r_int
)paren
)paren
(brace
id|ipaq_model_ops.blank_callback
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|h3600_register_pm_callback
r_static
id|__inline__
r_int
id|h3600_register_pm_callback
c_func
(paren
r_int
(paren
op_star
id|f
)paren
(paren
r_int
)paren
)paren
(brace
id|ipaq_model_ops.pm_callback_aux
op_assign
id|f
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|h3600_unregister_pm_callback
r_static
id|__inline__
r_void
id|h3600_unregister_pm_callback
c_func
(paren
r_int
(paren
op_star
id|f
)paren
(paren
r_int
)paren
)paren
(brace
id|ipaq_model_ops.pm_callback_aux
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|h3600_power_management
r_static
id|__inline__
r_int
id|h3600_power_management
c_func
(paren
r_int
id|req
)paren
(brace
r_if
c_cond
(paren
id|ipaq_model_ops.pm_callback
)paren
r_return
id|ipaq_model_ops
dot
id|pm_callback
c_func
(paren
id|req
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* ASSEMBLY */
macro_line|#endif /* _INCLUDE_H3600_H_ */
eof
