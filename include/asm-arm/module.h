macro_line|#ifndef _ASM_ARM_MODULE_H
DECL|macro|_ASM_ARM_MODULE_H
mdefine_line|#define _ASM_ARM_MODULE_H
DECL|struct|mod_arch_specific
r_struct
id|mod_arch_specific
(brace
DECL|member|foo
r_int
id|foo
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|Elf_Shdr
mdefine_line|#define Elf_Shdr&t;Elf32_Shdr
DECL|macro|Elf_Sym
mdefine_line|#define Elf_Sym&t;&t;Elf32_Sym
DECL|macro|Elf_Ehdr
mdefine_line|#define Elf_Ehdr&t;Elf32_Ehdr
multiline_comment|/*&n; * Include the ARM architecture version.&n; */
DECL|macro|MODULE_ARCH_VERMAGIC
mdefine_line|#define MODULE_ARCH_VERMAGIC&t;&quot;ARMv&quot; __stringify(__LINUX_ARM_ARCH__) &quot; &quot;
macro_line|#endif /* _ASM_ARM_MODULE_H */
eof
