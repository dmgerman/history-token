multiline_comment|/*&n; * linux/include/asm-arm/arch-cl7500/keyboard.h&n; *  from linux/include/asm-arm/arch-rpc/keyboard.h&n; *&n; * Keyboard driver definitions for CL7500 architecture&n; *&n; * (C) 1998 Russell King&n; */
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|NR_SCANCODES
mdefine_line|#define NR_SCANCODES 128
r_extern
r_void
id|ps2kbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
suffix:semicolon
r_extern
r_void
id|ps2kbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|ps2kbd_sysrq_xlate
(braket
id|NR_SCANCODES
)braket
suffix:semicolon
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode(sc,kc)&t;&t;(-EINVAL)
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode(sc)&t;&t;(-EINVAL)
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate(sc, kcp, rm)&t;({ *(kcp) = (sc); 1; })
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up(kc)&t;&t;(0200)
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds(leds)&t;&t;&t;ps2kbd_leds(leds)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw()&t;&t;&t;ps2kbd_init_hw()
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate&t;&t;&t;ps2kbd_sysrq_xlate
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq()&t;&t;disable_irq(IRQ_KEYBOARDRX)
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq()&t;&t;enable_irq(IRQ_KEYBOARDRX)
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY&t;13
eof
