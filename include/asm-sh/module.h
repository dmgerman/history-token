macro_line|#ifndef _ASM_SH_MODULE_H
DECL|macro|_ASM_SH_MODULE_H
mdefine_line|#define _ASM_SH_MODULE_H
multiline_comment|/*&n; * This file contains the SH architecture specific module code.&n; */
DECL|struct|mod_arch_specific
r_struct
id|mod_arch_specific
(brace
multiline_comment|/* Nothing to see here .. */
)brace
suffix:semicolon
DECL|macro|Elf_Shdr
mdefine_line|#define Elf_Shdr&t;&t;Elf32_Shdr
DECL|macro|Elf_Sym
mdefine_line|#define Elf_Sym&t;&t;&t;Elf32_Sym
DECL|macro|Elf_Ehdr
mdefine_line|#define Elf_Ehdr&t;&t;Elf32_Ehdr
macro_line|#ifdef CONFIG_CPU_LITTLE_ENDIAN
macro_line|# ifdef CONFIG_CPU_SH3
DECL|macro|MODULE_PROC_FAMILY
macro_line|#  define MODULE_PROC_FAMILY &quot;SH3LE &quot;
macro_line|# elif defined  CONFIG_CPU_SH4
DECL|macro|MODULE_PROC_FAMILY
macro_line|#  define MODULE_PROC_FAMILY &quot;SH4LE &quot;
macro_line|# else
macro_line|#  error unknown processor family
macro_line|# endif
macro_line|#else
macro_line|# ifdef CONFIG_CPU_SH3
DECL|macro|MODULE_PROC_FAMILY
macro_line|#  define MODULE_PROC_FAMILY &quot;SH3BE &quot;
macro_line|# elif defined  CONFIG_CPU_SH4
DECL|macro|MODULE_PROC_FAMILY
macro_line|#  define MODULE_PROC_FAMILY &quot;SH4BE &quot;
macro_line|# else
macro_line|#  error unknown processor family
macro_line|# endif
macro_line|#endif
DECL|macro|MODULE_ARCH_VERMAGIC
mdefine_line|#define MODULE_ARCH_VERMAGIC MODULE_PROC_FAMILY
macro_line|#endif /* _ASM_SH_MODULE_H */
eof
