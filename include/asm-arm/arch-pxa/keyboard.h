multiline_comment|/*&n; *  linux/include/asm-arm/arch-pxa/keyboard.h&n; *&n; *  This file contains the architecture specific keyboard definitions&n; */
macro_line|#ifndef _PXA_KEYBOARD_H
DECL|macro|_PXA_KEYBOARD_H
mdefine_line|#define _PXA_KEYBOARD_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
r_extern
r_struct
id|kbd_ops_struct
op_star
id|kbd_ops
suffix:semicolon
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq()&t;do { } while(0);
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq()&t;do { } while(0);
r_extern
r_int
id|sa1111_kbd_init_hw
c_func
(paren
r_void
)paren
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
id|machine_is_lubbock
c_func
(paren
)paren
)paren
id|sa1111_kbd_init_hw
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif  /* _PXA_KEYBOARD_H */
eof
