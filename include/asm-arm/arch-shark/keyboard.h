multiline_comment|/*&n; * linux/include/asm-arm/arch-shark/keyboard.h&n; * by Alexander Schulz &lt;aschulz@netwinder.org&gt;&n; * &n; * Derived from linux/include/asm-arm/arch-ebsa285/keyboard.h&n; * (C) 1998 Russell King&n; * (C) 1998 Phil Blundell&n; */
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
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
DECL|macro|KEYBOARD_IRQ
mdefine_line|#define KEYBOARD_IRQ&t;&t;&t;IRQ_ISA_KEYBOARD
DECL|macro|NR_SCANCODES
mdefine_line|#define NR_SCANCODES 128
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode(sc,kc)&t;&t;pckbd_setkeycode(sc,kc)
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode(sc)&t;&t;pckbd_getkeycode(sc)
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate(sc, kcp, rm)&t;pckbd_translate(sc, kcp, rm)
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up&t;&t;pckbd_unexpected_up
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds(leds)&t;&t;&t;pckbd_leds(leds)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw()&t;&t;&t;pckbd_init_hw()
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate&t;&t;&t;pckbd_sysrq_xlate
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq()
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq()
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY&t;0x54
multiline_comment|/* resource allocation */
DECL|macro|kbd_request_region
mdefine_line|#define kbd_request_region() request_region(0x60, 16, &quot;keyboard&quot;)
DECL|macro|kbd_request_irq
mdefine_line|#define kbd_request_irq(handler) request_irq(KEYBOARD_IRQ, handler, 0, &bslash;&n;                                             &quot;keyboard&quot;, NULL)
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
multiline_comment|/*&n; * Machine specific bits for the PS/2 driver&n; */
DECL|macro|aux_request_irq
mdefine_line|#define aux_request_irq(hand, dev_id)&t;&t;&t;&t;&t;&bslash;&n;&t;request_irq(AUX_IRQ, hand, SA_SHIRQ, &quot;PS/2 Mouse&quot;, dev_id)
DECL|macro|aux_free_irq
mdefine_line|#define aux_free_irq(dev_id) free_irq(AUX_IRQ, dev_id)
eof
