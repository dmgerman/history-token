multiline_comment|/*&n; *  linux/include/asm-arm/arch-sa1100/keyboard.h&n; *  Created 16 Dec 1999 by Nicolas Pitre &lt;nico@cam.org&gt;&n; *  This file contains the SA1100 architecture specific keyboard definitions&n; */
macro_line|#ifndef _SA1100_KEYBOARD_H
DECL|macro|_SA1100_KEYBOARD_H
mdefine_line|#define _SA1100_KEYBOARD_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
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
id|smartio_kbd_init_hw
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
id|machine_is_graphicsclient
c_func
(paren
)paren
)paren
id|gc_kbd_init_hw
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_adsbitsy
c_func
(paren
)paren
)paren
id|smartio_kbd_init_hw
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif  /* _SA1100_KEYBOARD_H */
eof
