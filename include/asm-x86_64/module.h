macro_line|#ifndef _ASM_X8664_MODULE_H
DECL|macro|_ASM_X8664_MODULE_H
mdefine_line|#define _ASM_X8664_MODULE_H
multiline_comment|/*&n; * This file contains the x8664 architecture specific module code.&n; * Modules need to be mapped near the kernel code to allow 32bit relocations.&n; */
r_extern
r_void
op_star
id|module_map
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|module_unmap
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|macro|module_arch_init
mdefine_line|#define module_arch_init(x)&t;(0)
DECL|macro|arch_init_modules
mdefine_line|#define arch_init_modules(x)&t;do { } while (0)
macro_line|#endif 
eof
