multiline_comment|/*&n; *  linux/include/asm-arm/arch-l7200/keyboard.h&n; *&n; *  Keyboard driver definitions for LinkUp Systems L7200 architecture&n; *&n; *  Copyright (C) 2000 Scott A McConnell (samcconn@cotw.com)&n; *                     Steve Hill (sjhill@cotw.com)&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; *&n; * Changelog:&n; *   07-18-2000&t;SAM&t;Created file&n; *   07-28-2000&t;SJH&t;Complete rewrite&n; */
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/*&n; * Layout of L7200 keyboard registers&n; */
DECL|struct|KBD_Port
r_struct
id|KBD_Port
(brace
DECL|member|KBDR
r_int
r_int
id|KBDR
suffix:semicolon
DECL|member|KBDMR
r_int
r_int
id|KBDMR
suffix:semicolon
DECL|member|KBSBSR
r_int
r_int
id|KBSBSR
suffix:semicolon
DECL|member|Reserved
r_int
r_int
id|Reserved
suffix:semicolon
DECL|member|KBKSR
r_int
r_int
id|KBKSR
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|KBD_BASE
mdefine_line|#define KBD_BASE        IO_BASE_2 + 0x4000
DECL|macro|l7200kbd_hwregs
mdefine_line|#define l7200kbd_hwregs ((volatile struct KBD_Port *) (KBD_BASE))
r_extern
r_void
id|l7200kbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|l7200kbd_translate
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
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode(sc,kc)&t;&t;(-EINVAL)
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode(sc)&t;&t;(-EINVAL)
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate(sc, kcp, rm)      ({ *(kcp) = (sc); 1; })
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up(kc)           (0200)
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds(leds)                  do {} while (0)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw()                   l7200kbd_init_hw()
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate                 ((unsigned char *)NULL)
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq()               disable_irq(IRQ_GCTC2)
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq()                enable_irq(IRQ_GCTC2)
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY&t;13
eof
