multiline_comment|/*&n; * Unlike ARM32 this is NOT automatically generated. DONT delete it&n; */
macro_line|#ifndef __ASM_ARM_MACH_TYPE_H
DECL|macro|__ASM_ARM_MACH_TYPE_H
mdefine_line|#define __ASM_ARM_MACH_TYPE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
r_int
id|__machine_arch_type
suffix:semicolon
macro_line|#endif
DECL|macro|MACH_TYPE_ARCHIMEDES
mdefine_line|#define MACH_TYPE_ARCHIMEDES           10
DECL|macro|MACH_TYPE_A5K
mdefine_line|#define MACH_TYPE_A5K                  11
macro_line|#ifdef CONFIG_ARCH_ARC
DECL|macro|machine_arch_type
macro_line|# define machine_arch_type&t;&t;MACH_TYPE_ARCHIMEDES
DECL|macro|machine_is_archimedes
macro_line|# define machine_is_archimedes()&t;(machine_arch_type == MACH_TYPE_ARCHIMEDES)
macro_line|#else
DECL|macro|machine_is_archimedes
macro_line|# define machine_is_archimedes()&t;(0)
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_A5K
DECL|macro|machine_arch_type
macro_line|# define machine_arch_type&t;&t;MACH_TYPE_A5K
DECL|macro|machine_is_a5k
macro_line|# define machine_is_a5k()&t;&t;(machine_arch_type == MACH_TYPE_A5K)
macro_line|#else
DECL|macro|machine_is_a5k
macro_line|# define machine_is_a5k()&t;(0)
macro_line|#endif
macro_line|#ifndef machine_arch_type
macro_line|#error Unknown machine type
DECL|macro|machine_arch_type
mdefine_line|#define machine_arch_type       __machine_arch_type
macro_line|#endif
macro_line|#endif
eof
