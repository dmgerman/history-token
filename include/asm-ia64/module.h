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
DECL|member|core_plt
r_struct
id|elf64_shdr
op_star
id|core_plt
suffix:semicolon
multiline_comment|/* core PLT section */
DECL|member|init_plt
r_struct
id|elf64_shdr
op_star
id|init_plt
suffix:semicolon
multiline_comment|/* init PLT section */
DECL|member|got
r_struct
id|elf64_shdr
op_star
id|got
suffix:semicolon
multiline_comment|/* global offset table */
DECL|member|opd
r_struct
id|elf64_shdr
op_star
id|opd
suffix:semicolon
multiline_comment|/* official procedure descriptors */
DECL|member|unwind
r_struct
id|elf64_shdr
op_star
id|unwind
suffix:semicolon
multiline_comment|/* unwind-table section */
DECL|member|gp
r_int
r_int
id|gp
suffix:semicolon
multiline_comment|/* global-pointer for module */
DECL|member|core_unw_table
r_void
op_star
id|core_unw_table
suffix:semicolon
multiline_comment|/* core unwind-table cookie returned by unwinder */
DECL|member|init_unw_table
r_void
op_star
id|init_unw_table
suffix:semicolon
multiline_comment|/* init unwind-table cookie returned by unwinder */
DECL|member|next_got_entry
r_int
r_int
id|next_got_entry
suffix:semicolon
multiline_comment|/* index of next available got entry */
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
DECL|macro|ARCH_SHF_SMALL
mdefine_line|#define ARCH_SHF_SMALL&t;SHF_IA_64_SHORT
macro_line|#endif /* _ASM_IA64_MODULE_H */
eof
