macro_line|#ifndef _ASM_I386_MODULE_H
DECL|macro|_ASM_I386_MODULE_H
mdefine_line|#define _ASM_I386_MODULE_H
multiline_comment|/* x86 is simple */
DECL|struct|mod_arch_specific
r_struct
id|mod_arch_specific
(brace
)brace
suffix:semicolon
DECL|macro|Elf_Shdr
mdefine_line|#define Elf_Shdr Elf32_Shdr
DECL|macro|Elf_Sym
mdefine_line|#define Elf_Sym Elf32_Sym
DECL|macro|Elf_Ehdr
mdefine_line|#define Elf_Ehdr Elf32_Ehdr
macro_line|#ifdef CONFIG_M386
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;386 &quot;
macro_line|#elif defined CONFIG_M486
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;486 &quot;
macro_line|#elif defined CONFIG_M586
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;586 &quot;
macro_line|#elif defined CONFIG_M586TSC
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;586TSC &quot;
macro_line|#elif defined CONFIG_M586MMX
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;586MMX &quot;
macro_line|#elif defined CONFIG_M686
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;686 &quot;
macro_line|#elif defined CONFIG_MPENTIUMII
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;PENTIUMII &quot;
macro_line|#elif defined CONFIG_MPENTIUMIII
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;PENTIUMIII &quot;
macro_line|#elif defined CONFIG_MPENTIUMM
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;PENTIUMM &quot;
macro_line|#elif defined CONFIG_MPENTIUM4
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;PENTIUM4 &quot;
macro_line|#elif defined CONFIG_MK6
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;K6 &quot;
macro_line|#elif defined CONFIG_MK7
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;K7 &quot;
macro_line|#elif defined CONFIG_MK8
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;K8 &quot;
macro_line|#elif defined CONFIG_X86_ELAN
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;ELAN &quot;
macro_line|#elif defined CONFIG_MCRUSOE
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;CRUSOE &quot;
macro_line|#elif defined CONFIG_MEFFICEON
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;EFFICEON &quot;
macro_line|#elif defined CONFIG_MWINCHIPC6
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;WINCHIPC6 &quot;
macro_line|#elif defined CONFIG_MWINCHIP2
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;WINCHIP2 &quot;
macro_line|#elif defined CONFIG_MWINCHIP3D
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;WINCHIP3D &quot;
macro_line|#elif defined CONFIG_MCYRIXIII
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;CYRIXIII &quot;
macro_line|#elif defined CONFIG_MVIAC3_2
DECL|macro|MODULE_PROC_FAMILY
mdefine_line|#define MODULE_PROC_FAMILY &quot;VIAC3-2 &quot;
macro_line|#else
macro_line|#error unknown processor family
macro_line|#endif
macro_line|#ifdef CONFIG_REGPARM
DECL|macro|MODULE_REGPARM
mdefine_line|#define MODULE_REGPARM &quot;REGPARM &quot;
macro_line|#else
DECL|macro|MODULE_REGPARM
mdefine_line|#define MODULE_REGPARM &quot;&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_4KSTACKS
DECL|macro|MODULE_STACKSIZE
mdefine_line|#define MODULE_STACKSIZE &quot;4KSTACKS &quot;
macro_line|#else
DECL|macro|MODULE_STACKSIZE
mdefine_line|#define MODULE_STACKSIZE &quot;&quot;
macro_line|#endif
DECL|macro|MODULE_ARCH_VERMAGIC
mdefine_line|#define MODULE_ARCH_VERMAGIC MODULE_PROC_FAMILY MODULE_REGPARM MODULE_STACKSIZE
macro_line|#endif /* _ASM_I386_MODULE_H */
eof
