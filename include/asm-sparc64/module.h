macro_line|#ifndef _ASM_SPARC64_MODULE_H
DECL|macro|_ASM_SPARC64_MODULE_H
mdefine_line|#define _ASM_SPARC64_MODULE_H
multiline_comment|/*&n; * This file contains the sparc64 architecture specific module code.&n; */
r_extern
r_void
op_star
id|module_map
(paren
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|module_unmap
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
DECL|macro|module_arch_init
mdefine_line|#define module_arch_init(x)&t;(0)
DECL|macro|arch_init_modules
mdefine_line|#define arch_init_modules(x)&t;do { } while (0)
macro_line|#endif /* _ASM_SPARC64_MODULE_H */
eof
