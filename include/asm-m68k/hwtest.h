multiline_comment|/* Routines to test for presence/absence of hardware registers:&n; * see arch/m68k/mm/hwtest.c.&n; *  -- PMM &lt;pmaydell@chiark.greenend.org.uk&gt; 05/1998&n; *&n; * Removed __init from decls.  We might want them in modules, and &n; * the code is tiny anyway.  16/5/98 pb&n; */
macro_line|#ifndef __ASM_HWTEST_H
DECL|macro|__ASM_HWTEST_H
mdefine_line|#define __ASM_HWTEST_H 
r_extern
r_int
id|hwreg_present
c_func
(paren
r_volatile
r_void
op_star
id|regp
)paren
suffix:semicolon
r_extern
r_int
id|hwreg_write
c_func
(paren
r_volatile
r_void
op_star
id|regp
comma
r_int
r_int
id|val
)paren
suffix:semicolon
macro_line|#endif
eof
