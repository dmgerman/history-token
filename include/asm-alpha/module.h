macro_line|#ifndef _ASM_ALPHA_MODULE_H
DECL|macro|_ASM_ALPHA_MODULE_H
mdefine_line|#define _ASM_ALPHA_MODULE_H
multiline_comment|/*&n; * This file contains the alpha architecture specific module code.&n; */
DECL|macro|module_map
mdefine_line|#define module_map(x)&t;&t;vmalloc(x)
DECL|macro|module_unmap
mdefine_line|#define module_unmap(x)&t;&t;vfree(x)
DECL|macro|module_arch_init
mdefine_line|#define module_arch_init(x)&t;alpha_module_init(x)
DECL|macro|arch_init_modules
mdefine_line|#define arch_init_modules(x)&t;alpha_init_modules(x)
r_static
r_inline
r_int
DECL|function|alpha_module_init
id|alpha_module_init
c_func
(paren
r_struct
id|module
op_star
id|mod
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mod_bound
c_func
(paren
id|mod-&gt;gp
op_minus
l_int|0x8000
comma
l_int|0
comma
id|mod
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;module_arch_init: mod-&gt;gp out of bounds.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|alpha_init_modules
id|alpha_init_modules
c_func
(paren
r_struct
id|module
op_star
id|mod
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;stq $29,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|mod-&gt;gp
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* _ASM_ALPHA_MODULE_H */
eof
