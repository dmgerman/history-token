multiline_comment|/*&n; *&t;Interface between the low-level keyboard driver and the keymapper&n; */
macro_line|#ifndef _KBD_LL_H
DECL|macro|_KBD_LL_H
mdefine_line|#define _KBD_LL_H
r_extern
r_struct
id|pt_regs
op_star
id|kbd_pt_regs
suffix:semicolon
r_void
id|handle_scancode
c_func
(paren
r_int
r_char
id|scancode
comma
r_int
id|down
)paren
suffix:semicolon
macro_line|#endif&t;/* _KBD_LL_H */
eof
