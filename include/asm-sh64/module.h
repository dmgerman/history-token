macro_line|#ifndef __ASM_SH64_MODULE_H
DECL|macro|__ASM_SH64_MODULE_H
mdefine_line|#define __ASM_SH64_MODULE_H
multiline_comment|/*&n; * This file contains the SH architecture specific module code.&n; */
DECL|struct|mod_arch_specific
r_struct
id|mod_arch_specific
(brace
multiline_comment|/* empty */
)brace
suffix:semicolon
DECL|macro|Elf_Shdr
mdefine_line|#define Elf_Shdr&t;&t;Elf32_Shdr
DECL|macro|Elf_Sym
mdefine_line|#define Elf_Sym&t;&t;&t;Elf32_Sym
DECL|macro|Elf_Ehdr
mdefine_line|#define Elf_Ehdr&t;&t;Elf32_Ehdr
DECL|macro|module_map
mdefine_line|#define module_map(x)&t;&t;vmalloc(x)
DECL|macro|module_unmap
mdefine_line|#define module_unmap(x)&t;&t;vfree(x)
DECL|macro|module_arch_init
mdefine_line|#define module_arch_init(x)&t;(0)
DECL|macro|arch_init_modules
mdefine_line|#define arch_init_modules(x)&t;do { } while (0)
macro_line|#endif /* __ASM_SH64_MODULE_H */
eof
