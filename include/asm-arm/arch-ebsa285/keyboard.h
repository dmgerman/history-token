multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa285/keyboard.h&n; *&n; * Keyboard driver definitions for EBSA285 architecture&n; *&n; * Copyright (C) 1998-2001 Russell King&n; * (C) 1998 Phil Blundell&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|KEYBOARD_IRQ
mdefine_line|#define KEYBOARD_IRQ&t;&t;IRQ_ISA_KEYBOARD
DECL|macro|NR_SCANCODES
mdefine_line|#define NR_SCANCODES&t;&t;128
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq()&t;do { } while (0)
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq()&t;do { } while (0)
r_extern
r_int
id|pckbd_setkeycode
c_func
(paren
r_int
r_int
id|scancode
comma
r_int
r_int
id|keycode
)paren
suffix:semicolon
r_extern
r_int
id|pckbd_getkeycode
c_func
(paren
r_int
r_int
id|scancode
)paren
suffix:semicolon
r_extern
r_int
id|pckbd_translate
c_func
(paren
r_int
r_char
id|scancode
comma
r_int
r_char
op_star
id|keycode
comma
r_char
id|raw_mode
)paren
suffix:semicolon
r_extern
r_char
id|pckbd_unexpected_up
c_func
(paren
r_int
r_char
id|keycode
)paren
suffix:semicolon
r_extern
r_void
id|pckbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
suffix:semicolon
r_extern
r_void
id|pckbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|pckbd_sysrq_xlate
(braket
l_int|128
)braket
suffix:semicolon
DECL|function|kbd_init_hw
r_static
r_inline
r_void
id|kbd_init_hw
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|have_isa_bridge
)paren
(brace
id|k_setkeycode
op_assign
id|pckbd_setkeycode
suffix:semicolon
id|k_getkeycode
op_assign
id|pckbd_getkeycode
suffix:semicolon
id|k_translate
op_assign
id|pckbd_translate
suffix:semicolon
id|k_unexpected_up
op_assign
id|pckbd_unexpected_up
suffix:semicolon
id|k_leds
op_assign
id|pckbd_leds
suffix:semicolon
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
id|k_sysrq_key
op_assign
l_int|0x54
suffix:semicolon
id|k_sysrq_xlate
op_assign
id|pckbd_sysrq_xlate
suffix:semicolon
macro_line|#endif
id|pckbd_init_hw
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The rest of this file is to do with supporting pc_keyb.c&n; */
multiline_comment|/* resource allocation */
DECL|macro|kbd_request_region
mdefine_line|#define kbd_request_region()&t;request_region(0x60, 16, &quot;keyboard&quot;)
DECL|macro|kbd_request_irq
mdefine_line|#define kbd_request_irq(handler) request_irq(KEYBOARD_IRQ, handler, 0, &bslash;&n;&t;&t;&t;&t;&t;     &quot;keyboard&quot;, NULL)
multiline_comment|/* How to access the keyboard macros on this platform.  */
DECL|macro|kbd_read_input
mdefine_line|#define kbd_read_input() inb(KBD_DATA_REG)
DECL|macro|kbd_read_status
mdefine_line|#define kbd_read_status() inb(KBD_STATUS_REG)
DECL|macro|kbd_write_output
mdefine_line|#define kbd_write_output(val) outb(val, KBD_DATA_REG)
DECL|macro|kbd_write_command
mdefine_line|#define kbd_write_command(val) outb(val, KBD_CNTL_REG)
multiline_comment|/* Some stoneage hardware needs delays after some operations.  */
DECL|macro|kbd_pause
mdefine_line|#define kbd_pause() do { } while(0)
DECL|macro|aux_request_irq
mdefine_line|#define aux_request_irq(hand, dev_id)&t;&t;&t;&t;&t;&bslash;&n;&t;request_irq(AUX_IRQ, hand, SA_SHIRQ, &quot;PS/2 Mouse&quot;, dev_id)
DECL|macro|aux_free_irq
mdefine_line|#define aux_free_irq(dev_id) free_irq(AUX_IRQ, dev_id)
eof
