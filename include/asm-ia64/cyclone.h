macro_line|#ifndef ASM_IA64_CYCLONE_H
DECL|macro|ASM_IA64_CYCLONE_H
mdefine_line|#define ASM_IA64_CYCLONE_H
macro_line|#ifdef&t;CONFIG_IA64_CYCLONE
r_extern
r_int
id|use_cyclone
suffix:semicolon
r_extern
r_void
id|__init
id|cyclone_setup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else&t;/* CONFIG_IA64_CYCLONE */
DECL|macro|use_cyclone
mdefine_line|#define use_cyclone 0
DECL|function|cyclone_setup
r_static
r_inline
r_void
id|cyclone_setup
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Cyclone Counter: System not configured&quot;
l_string|&quot; w/ CONFIG_IA64_CYCLONE.&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_IA64_CYCLONE */
macro_line|#endif&t;/* !ASM_IA64_CYCLONE_H */
eof
