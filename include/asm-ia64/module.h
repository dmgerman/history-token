macro_line|#ifndef _ASM_IA64_MODULE_H
DECL|macro|_ASM_IA64_MODULE_H
mdefine_line|#define _ASM_IA64_MODULE_H
multiline_comment|/*&n; * IA-64-specific support for kernel module loader.&n; *&n; * Copyright (C) 2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
r_struct
id|elf64_shdr
suffix:semicolon
multiline_comment|/* forward declration */
DECL|struct|mod_arch_specific
r_struct
id|mod_arch_specific
(brace
multiline_comment|/*&n;&t; * PLTs need to be within 16MB of the call-site.  Since the core and the init&n;&t; * sections are allocated separately, we need to maintain separate PLT areas&n;&t; * for them.  Function descriptors and global-offset-table entries are, in&n;&t; * contrast, always allocated in the core.&n;&t; */
DECL|member|init_text_sec
r_struct
id|elf64_shdr
op_star
id|init_text_sec
suffix:semicolon
multiline_comment|/* .init.text section (or NULL) */
DECL|member|init_plt_offset
r_int
r_int
id|init_plt_offset
suffix:semicolon
DECL|member|core_text_sec
r_struct
id|elf64_shdr
op_star
id|core_text_sec
suffix:semicolon
multiline_comment|/* .text section (or NULL) */
DECL|member|core_plt_offset
r_int
r_int
id|core_plt_offset
suffix:semicolon
DECL|member|fdesc_offset
r_int
r_int
id|fdesc_offset
suffix:semicolon
DECL|member|got_offset
r_int
r_int
id|got_offset
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|Elf_Shdr
mdefine_line|#define Elf_Shdr&t;Elf64_Shdr
DECL|macro|Elf_Sym
mdefine_line|#define Elf_Sym&t;&t;Elf64_Sym
DECL|macro|Elf_Ehdr
mdefine_line|#define Elf_Ehdr&t;Elf64_Ehdr
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY&t;&quot;ia64&quot;
DECL|macro|MODULE_ARCH_VERMAGIC
mdefine_line|#define MODULE_ARCH_VERMAGIC&t;MODULE_PROC_FAMILY
macro_line|#endif /* _ASM_IA64_MODULE_H */
eof
