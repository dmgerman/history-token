multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; *  linux/include/asm-ppc/keyboard.h&n; *&n; *  Created 3 Nov 1996 by Geert Uytterhoeven&n; *  Modified for Power Macintosh by Paul Mackerras&n; */
multiline_comment|/*&n; * This file contains the ppc architecture specific keyboard definitions -&n; * like the intel pc for prep systems, different for power macs.&n; */
macro_line|#ifndef __ASM_KEYBOARD_H__
DECL|macro|__ASM_KEYBOARD_H__
mdefine_line|#define __ASM_KEYBOARD_H__
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/adb.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* IBM Spruce platform is different. */
macro_line|#ifdef CONFIG_SPRUCE
macro_line|#include &lt;platforms/spruce.h&gt;
macro_line|#endif
macro_line|#ifndef KEYBOARD_IRQ
DECL|macro|KEYBOARD_IRQ
mdefine_line|#define KEYBOARD_IRQ&t;&t;&t;1
macro_line|#endif
DECL|macro|DISABLE_KBD_DURING_INTERRUPTS
mdefine_line|#define DISABLE_KBD_DURING_INTERRUPTS&t;0
DECL|macro|INIT_KBD
mdefine_line|#define INIT_KBD
DECL|function|kbd_setkeycode
r_static
r_inline
r_int
id|kbd_setkeycode
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
(brace
r_if
c_cond
(paren
id|ppc_md.kbd_setkeycode
)paren
r_return
id|ppc_md
dot
id|kbd_setkeycode
c_func
(paren
id|scancode
comma
id|keycode
)paren
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|kbd_getkeycode
r_static
r_inline
r_int
id|kbd_getkeycode
c_func
(paren
r_int
r_int
id|scancode
)paren
(brace
r_if
c_cond
(paren
id|ppc_md.kbd_getkeycode
)paren
r_return
id|ppc_md
dot
id|kbd_getkeycode
c_func
(paren
id|scancode
)paren
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|kbd_translate
r_static
r_inline
r_int
id|kbd_translate
c_func
(paren
r_int
r_char
id|keycode
comma
r_int
r_char
op_star
id|keycodep
comma
r_char
id|raw_mode
)paren
(brace
r_if
c_cond
(paren
id|ppc_md.kbd_translate
)paren
r_return
id|ppc_md
dot
id|kbd_translate
c_func
(paren
id|keycode
comma
id|keycodep
comma
id|raw_mode
)paren
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|kbd_unexpected_up
r_static
r_inline
r_int
id|kbd_unexpected_up
c_func
(paren
r_int
r_char
id|keycode
)paren
(brace
r_if
c_cond
(paren
id|ppc_md.kbd_unexpected_up
)paren
r_return
id|ppc_md
dot
id|kbd_unexpected_up
c_func
(paren
id|keycode
)paren
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|kbd_leds
r_static
r_inline
r_void
id|kbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
(brace
r_if
c_cond
(paren
id|ppc_md.kbd_leds
)paren
id|ppc_md
dot
id|kbd_leds
c_func
(paren
id|leds
)paren
suffix:semicolon
)brace
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
id|ppc_md.kbd_init_hw
)paren
id|ppc_md
dot
id|kbd_init_hw
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate&t;(ppc_md.ppc_kbd_sysrq_xlate)
r_extern
r_int
r_int
id|SYSRQ_KEY
suffix:semicolon
multiline_comment|/* resource allocation */
DECL|macro|kbd_request_region
mdefine_line|#define kbd_request_region()
DECL|macro|kbd_request_irq
mdefine_line|#define kbd_request_irq(handler) request_irq(KEYBOARD_IRQ, handler, 0, &bslash;&n;                                             &quot;keyboard&quot;, NULL)
multiline_comment|/* How to access the keyboard macros on this platform.  */
macro_line|#ifndef kbd_read_input
DECL|macro|kbd_read_input
mdefine_line|#define kbd_read_input() inb(KBD_DATA_REG)
DECL|macro|kbd_read_status
mdefine_line|#define kbd_read_status() inb(KBD_STATUS_REG)
DECL|macro|kbd_write_output
mdefine_line|#define kbd_write_output(val) outb(val, KBD_DATA_REG)
DECL|macro|kbd_write_command
mdefine_line|#define kbd_write_command(val) outb(val, KBD_CNTL_REG)
macro_line|#endif
multiline_comment|/* Some stoneage hardware needs delays after some operations.  */
DECL|macro|kbd_pause
mdefine_line|#define kbd_pause() do { } while(0)
multiline_comment|/*&n; * Machine specific bits for the PS/2 driver&n; */
macro_line|#ifndef AUX_IRQ&t;
DECL|macro|AUX_IRQ
mdefine_line|#define AUX_IRQ 12
macro_line|#endif
DECL|macro|aux_request_irq
mdefine_line|#define aux_request_irq(hand, dev_id)&t;&t;&t;&t;&t;&bslash;&n;&t;request_irq(AUX_IRQ, hand, SA_SHIRQ, &quot;PS/2 Mouse&quot;, dev_id)
DECL|macro|aux_free_irq
mdefine_line|#define aux_free_irq(dev_id) free_irq(AUX_IRQ, dev_id)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_KEYBOARD_H__ */
eof
