multiline_comment|/*&n; *  linux/include/asm-arm/arch-sa1100/keyboard.h&n; *  Created 16 Dec 1999 by Nicolas Pitre &lt;nico@cam.org&gt;&n; *  This file contains the SA1100 architecture specific keyboard definitions&n; */
macro_line|#ifndef _SA1100_KEYBOARD_H
DECL|macro|_SA1100_KEYBOARD_H
mdefine_line|#define _SA1100_KEYBOARD_H
macro_line|#include &lt;linux/config.h&gt;
singleline_comment|// #ifdef CONFIG_SA1100_BRUTUS
multiline_comment|/* need fixing... */
macro_line|#if 0
r_extern
r_int
id|Brutus_kbd_translate
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
r_void
id|Brutus_kbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
suffix:semicolon
r_extern
r_void
id|Brutus_kbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|Brutus_kbd_enable_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|Brutus_kbd_disable_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|Brutus_kbd_sysrq_xlate
(braket
l_int|128
)braket
suffix:semicolon
mdefine_line|#define kbd_setkeycode(x...)&t;(-ENOSYS)
mdefine_line|#define kbd_getkeycode(x...)&t;(-ENOSYS)
mdefine_line|#define kbd_translate&t;&t;Brutus_kbd_translate
mdefine_line|#define kbd_unexpected_up(x...)&t;(1)
mdefine_line|#define kbd_leds&t;&t;Brutus_kbd_leds
mdefine_line|#define kbd_init_hw&t;&t;Brutus_kbd_init_hw
mdefine_line|#define kbd_enable_irq&t;&t;Brutus_kbd_enable_irq
mdefine_line|#define kbd_disable_irq&t;&t;Brutus_kbd_disable_irq
mdefine_line|#define kbd_sysrq_xlate&t;&t;Brutus_kbd_sysrq_xlate
mdefine_line|#define SYSRQ_KEY 0x54
macro_line|#elif CONFIG_SA1100_GRAPHICSCLIENT
r_extern
r_int
id|gc_kbd_translate
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
r_void
id|gc_kbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
suffix:semicolon
r_extern
r_void
id|gc_kbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|gc_kbd_enable_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|gc_kbd_disable_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|gc_kbd_sysrq_xlate
(braket
l_int|128
)braket
suffix:semicolon
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode(x...)    (-ENOSYS)
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode(x...)    (-ENOSYS)
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate           gc_kbd_translate
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up(x...) (1)
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds                gc_kbd_leds
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw             gc_kbd_init_hw
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq          gc_kbd_enable_irq
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq         gc_kbd_disable_irq
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate         gc_kbd_sysrq_xlate
macro_line|#elif CONFIG_SA1100_BITSY
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode(x...)    (-ENOSYS)
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode(x...)    (-ENOSYS)
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate(sc_,kc_,rm_)&t;((*(kc_)=(sc_)),1)
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up(x...) (1)
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds(x...)&t;&t;do { } while (0)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw(x...)&t;do { } while (0)
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq(x...)&t;do { } while (0)
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq(x...)&t;do { } while (0)
macro_line|#elif 0 
singleline_comment|//defined(CONFIG_SA1111)   /*@@@@@*/
DECL|macro|KEYBOARD_IRQ
mdefine_line|#define KEYBOARD_IRQ           TPRXINT
DECL|macro|DISABLE_KBD_DURING_INTERRUPTS
mdefine_line|#define DISABLE_KBD_DURING_INTERRUPTS  0
multiline_comment|/* redefine some macros */
macro_line|#ifdef KBD_DATA_REG
DECL|macro|KBD_DATA_REG
macro_line|#undef KBD_DATA_REG
macro_line|#endif
macro_line|#ifdef KBD_STATUS_REG
DECL|macro|KBD_STATUS_REG
macro_line|#undef KBD_STATUS_REG
macro_line|#endif
macro_line|#ifdef KBD_CNTL_REG
DECL|macro|KBD_CNTL_REG
macro_line|#undef KBD_CNTL_REG
macro_line|#endif
DECL|macro|KBD_DATA_REG
mdefine_line|#define KBD_DATA_REG           KBDDATA
DECL|macro|KBD_STATUS_REG
mdefine_line|#define KBD_STATUS_REG         KBDSTAT
DECL|macro|KBD_CNTL_REG
mdefine_line|#define KBD_CNTL_REG           KBDCR
r_extern
r_int
id|sa1111_setkeycode
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
id|sa1111_getkeycode
c_func
(paren
r_int
r_int
id|scancode
)paren
suffix:semicolon
r_extern
r_int
id|sa1111_translate
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
id|sa1111_unexpected_up
c_func
(paren
r_int
r_char
id|keycode
)paren
suffix:semicolon
r_extern
r_void
id|sa1111_leds
c_func
(paren
r_int
r_char
id|leds
)paren
suffix:semicolon
r_extern
r_void
id|sa1111_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|sa1111_sysrq_xlate
(braket
l_int|128
)braket
suffix:semicolon
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode&t;&t;sa1111_setkeycode
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode&t;&t;sa1111_getkeycode
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate&t;&t;sa1111_translate
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up&t;sa1111_unexpected_up
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds&t;&t;sa1111_leds
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw&t;&t;sa1111_init_hw
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate&t;&t;sa1111_sysrq_xlate
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq(x...)&t;do{;}while(0)
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq(x...)&t;do{;}while(0)
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY 0x54
multiline_comment|/* resource allocation */
DECL|macro|kbd_request_region
mdefine_line|#define kbd_request_region()
DECL|macro|kbd_request_irq
mdefine_line|#define kbd_request_irq(handler) request_irq(KEYBOARD_IRQ, handler, 0, &bslash;&n;&t;&t;&t;&t;&t;&quot;keyboard&quot;, NULL)
multiline_comment|/* How to access the keyboard macros on this platform.  */
DECL|macro|kbd_read_input
mdefine_line|#define kbd_read_input()&t;(*KBDDATA &amp; 0x00ff)
DECL|macro|kbd_read_status
mdefine_line|#define kbd_read_status()&t;(*KBDSTAT &amp; 0x01ff)
DECL|macro|kbd_write_output
mdefine_line|#define kbd_write_output(val)&t;(*KBDDATA = (val))
DECL|macro|kbd_write_command
mdefine_line|#define kbd_write_command(val)&t;(*KBDCR = (val))
multiline_comment|/* Some stoneage hardware needs delays after some operations.  */
DECL|macro|kbd_pause
mdefine_line|#define kbd_pause() do {;} while(0)
multiline_comment|/* bit definitions for some registers */
DECL|macro|KBD_CR_ENA
mdefine_line|#define KBD_CR_ENA&t;(1&lt;&lt;3)
DECL|macro|KBD_STAT_RXB
mdefine_line|#define KBD_STAT_RXB&t;(1&lt;&lt;4)
DECL|macro|KBD_STAT_RXF
mdefine_line|#define KBD_STAT_RXF&t;(1&lt;&lt;5)
DECL|macro|KBD_STAT_TXB
mdefine_line|#define KBD_STAT_TXB&t;(1&lt;&lt;6)
DECL|macro|KBD_STAT_TXE
mdefine_line|#define KBD_STAT_TXE&t;(1&lt;&lt;7)
DECL|macro|KBD_STAT_STP
mdefine_line|#define KBD_STAT_STP&t;(1&lt;&lt;8)
multiline_comment|/*&n; * Machine specific bits for the PS/2 driver&n; */
DECL|macro|AUX_IRQ
mdefine_line|#define AUX_IRQ&t;&t;MSRXINT
DECL|macro|aux_request_irq
mdefine_line|#define aux_request_irq(hand, dev_id)  &bslash;&n;&t;&t;request_irq(AUX_IRQ, hand, SA_SHIRQ, &quot;PS/2 Mouse&quot;, dev_id)
DECL|macro|aux_free_irq
mdefine_line|#define aux_free_irq(dev_id) free_irq(AUX_IRQ, dev_id)
multiline_comment|/* How to access the mouse macros on this platform.  */
DECL|macro|mse_read_input
mdefine_line|#define mse_read_input()&t;(*MSEDATA &amp; 0x00ff)
DECL|macro|mse_read_status
mdefine_line|#define mse_read_status()&t;(*MSESTAT &amp; 0x01ff)
DECL|macro|mse_write_output
mdefine_line|#define mse_write_output(val)&t;(*MSEDATA = (val))
DECL|macro|mse_write_command
mdefine_line|#define mse_write_command(val)&t;(*MSECR = (val))
multiline_comment|/* bit definitions for some registers */
DECL|macro|MSE_CR_ENA
mdefine_line|#define MSE_CR_ENA&t;(1&lt;&lt;3)
DECL|macro|MSE_STAT_RXB
mdefine_line|#define MSE_STAT_RXB&t;(1&lt;&lt;4)
DECL|macro|MSE_STAT_RXF
mdefine_line|#define MSE_STAT_RXF&t;(1&lt;&lt;5)
DECL|macro|MSE_STAT_TXB
mdefine_line|#define MSE_STAT_TXB&t;(1&lt;&lt;6)
DECL|macro|MSE_STAT_TXE
mdefine_line|#define MSE_STAT_TXE&t;(1&lt;&lt;7)
DECL|macro|MSE_STAT_STP
mdefine_line|#define MSE_STAT_STP&t;(1&lt;&lt;8)
macro_line|#else
multiline_comment|/* dummy i.e. no real keyboard */
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode(x...)&t;(-ENOSYS)
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode(x...)&t;(-ENOSYS)
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate(x...)&t;(0)
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up(x...)&t;(1)
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds(x...)&t;&t;do {;} while (0)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw(x...)&t;do {;} while (0)
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq(x...)&t;do {;} while (0)
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq(x...)&t;do {;} while (0)
macro_line|#endif
multiline_comment|/* needed if MAGIC_SYSRQ is enabled for serial console */
macro_line|#ifndef SYSRQ_KEY
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY&t;&t;((unsigned char)(-1))
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate         ((unsigned char *)NULL)
macro_line|#endif
macro_line|#endif  /* _SA1100_KEYBOARD_H */
eof
