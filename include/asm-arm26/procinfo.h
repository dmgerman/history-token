multiline_comment|/*&n; *  linux/include/asm-arm/procinfo.h&n; *&n; *  Copyright (C) 1996-1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_PROCINFO_H
DECL|macro|__ASM_PROCINFO_H
mdefine_line|#define __ASM_PROCINFO_H
macro_line|#ifndef __ASSEMBLY__
singleline_comment|//struct processor;
singleline_comment|//struct cpu_user_fns;
DECL|struct|proc_info_item
r_struct
id|proc_info_item
(brace
DECL|member|manufacturer
r_const
r_char
op_star
id|manufacturer
suffix:semicolon
DECL|member|cpu_name
r_const
r_char
op_star
id|cpu_name
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Note!  struct processor is always defined if we&squot;re&n; * using MULTI_CPU, otherwise this entry is unused,&n; * but still exists.&n; *&n; * NOTE! The following structure is defined by assembly&n; * language, NOT C code.  For more information, check:&n; *  arch/arm/mm/proc-*.S and arch/arm/kernel/head-armv.S&n; */
DECL|struct|proc_info_list
r_struct
id|proc_info_list
(brace
DECL|member|cpu_val
r_int
r_int
id|cpu_val
suffix:semicolon
DECL|member|cpu_mask
r_int
r_int
id|cpu_mask
suffix:semicolon
DECL|member|arch_name
r_const
r_char
op_star
id|arch_name
suffix:semicolon
DECL|member|elf_name
r_const
r_char
op_star
id|elf_name
suffix:semicolon
DECL|member|elf_hwcap
r_int
r_int
id|elf_hwcap
suffix:semicolon
DECL|member|info
r_struct
id|proc_info_item
op_star
id|info
suffix:semicolon
DECL|member|proc
r_struct
id|processor
op_star
id|proc
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;/* __ASSEMBLY__ */
DECL|macro|PROC_INFO_SZ
mdefine_line|#define PROC_INFO_SZ&t;48
DECL|macro|HWCAP_SWP
mdefine_line|#define HWCAP_SWP&t;1
DECL|macro|HWCAP_HALF
mdefine_line|#define HWCAP_HALF&t;2
DECL|macro|HWCAP_THUMB
mdefine_line|#define HWCAP_THUMB&t;4
DECL|macro|HWCAP_26BIT
mdefine_line|#define HWCAP_26BIT&t;8&t;/* Play it safe */
DECL|macro|HWCAP_FAST_MULT
mdefine_line|#define HWCAP_FAST_MULT&t;16
DECL|macro|HWCAP_FPA
mdefine_line|#define HWCAP_FPA&t;32
DECL|macro|HWCAP_VFP
mdefine_line|#define HWCAP_VFP&t;64
DECL|macro|HWCAP_EDSP
mdefine_line|#define HWCAP_EDSP&t;128
DECL|macro|HWCAP_JAVA
mdefine_line|#define HWCAP_JAVA&t;256
macro_line|#endif
eof
