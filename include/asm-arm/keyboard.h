multiline_comment|/*&n; *  linux/include/asm-arm/keyboard.h&n; *&n; *  Copyright (C) 1998 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Keyboard driver definitions for ARM&n; */
macro_line|#ifndef __ASM_ARM_KEYBOARD_H
DECL|macro|__ASM_ARM_KEYBOARD_H
mdefine_line|#define __ASM_ARM_KEYBOARD_H
multiline_comment|/*&n; * We provide a unified keyboard interface when in VC_MEDIUMRAW&n; * mode.  This means that all keycodes must be common between&n; * all supported keyboards.  This unfortunately puts us at odds&n; * with the PC keyboard interface chip... but we can&squot;t do anything&n; * about that now.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/arch/keyboard.h&gt;
macro_line|#ifndef kbd_rate
r_struct
id|kbd_repeat
suffix:semicolon
r_extern
r_int
id|kbd_rate
c_func
(paren
r_struct
id|kbd_repeat
op_star
id|rate
)paren
id|__attribute__
c_func
(paren
(paren
id|weak
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_ARM_KEYBOARD_H */
eof
