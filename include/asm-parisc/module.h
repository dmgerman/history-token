macro_line|#ifndef _ASM_PARISC_MODULE_H
DECL|macro|_ASM_PARISC_MODULE_H
mdefine_line|#define _ASM_PARISC_MODULE_H
multiline_comment|/*&n; * This file contains the parisc architecture specific module code.&n; */
macro_line|#ifdef __LP64__
DECL|macro|Elf_Shdr
mdefine_line|#define Elf_Shdr Elf64_Shdr
DECL|macro|Elf_Sym
mdefine_line|#define Elf_Sym Elf64_Sym
DECL|macro|Elf_Ehdr
mdefine_line|#define Elf_Ehdr Elf64_Ehdr
DECL|macro|Elf_Addr
mdefine_line|#define Elf_Addr Elf64_Addr
DECL|macro|Elf_Rela
mdefine_line|#define Elf_Rela Elf64_Rela
macro_line|#else
DECL|macro|Elf_Shdr
mdefine_line|#define Elf_Shdr Elf32_Shdr
DECL|macro|Elf_Sym
mdefine_line|#define Elf_Sym Elf32_Sym
DECL|macro|Elf_Ehdr
mdefine_line|#define Elf_Ehdr Elf32_Ehdr
DECL|macro|Elf_Addr
mdefine_line|#define Elf_Addr Elf32_Addr
DECL|macro|Elf_Rela
mdefine_line|#define Elf_Rela Elf32_Rela
macro_line|#endif
DECL|macro|module_map
mdefine_line|#define module_map(x)&t;&t;vmalloc(x)
DECL|macro|module_unmap
mdefine_line|#define module_unmap(x)&t;&t;vfree(x)
DECL|macro|module_arch_init
mdefine_line|#define module_arch_init(x)&t;(0)
DECL|macro|arch_init_modules
mdefine_line|#define arch_init_modules(x)&t;do { } while (0)
DECL|struct|mod_arch_specific
r_struct
id|mod_arch_specific
(brace
DECL|member|got_offset
r_int
r_int
id|got_offset
suffix:semicolon
DECL|member|fdesc_offset
DECL|member|fdesc_count
r_int
r_int
id|fdesc_offset
comma
id|fdesc_count
suffix:semicolon
DECL|member|stub_offset
r_int
r_int
id|stub_offset
suffix:semicolon
DECL|member|stub_count
r_int
r_int
id|stub_count
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _ASM_PARISC_MODULE_H */
eof
