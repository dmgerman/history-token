macro_line|#ifndef __ASM_TRAPS_H
DECL|macro|__ASM_TRAPS_H
mdefine_line|#define __ASM_TRAPS_H
macro_line|#ifdef __KERNEL__
r_struct
id|pt_regs
suffix:semicolon
multiline_comment|/* traps.c */
r_void
id|parisc_terminate
c_func
(paren
r_char
op_star
id|msg
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|code
comma
r_int
r_int
id|offset
)paren
suffix:semicolon
multiline_comment|/* mm/fault.c */
r_void
id|do_page_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|code
comma
r_int
r_int
id|address
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
