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
DECL|member|got_count
DECL|member|got_max
r_int
r_int
id|got_offset
comma
id|got_count
comma
id|got_max
suffix:semicolon
DECL|member|fdesc_offset
DECL|member|fdesc_count
DECL|member|fdesc_max
r_int
r_int
id|fdesc_offset
comma
id|fdesc_count
comma
id|fdesc_max
suffix:semicolon
DECL|member|stub_offset
DECL|member|stub_count
DECL|member|stub_max
r_int
r_int
id|stub_offset
comma
id|stub_count
comma
id|stub_max
suffix:semicolon
DECL|member|init_stub_offset
DECL|member|init_stub_count
DECL|member|init_stub_max
r_int
r_int
id|init_stub_offset
comma
id|init_stub_count
comma
id|init_stub_max
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _ASM_PARISC_MODULE_H */
eof
