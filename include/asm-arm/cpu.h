multiline_comment|/*&n; *  linux/include/asm-arm/cpu.h&n; *&n; *  Copyright (C) 2004-2005 ARM Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARM_CPU_H
DECL|macro|__ASM_ARM_CPU_H
mdefine_line|#define __ASM_ARM_CPU_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
DECL|struct|cpuinfo_arm
r_struct
id|cpuinfo_arm
(brace
DECL|member|cpu
r_struct
id|cpu
id|cpu
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|member|loops_per_jiffy
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
id|DECLARE_PER_CPU
c_func
(paren
r_struct
id|cpuinfo_arm
comma
id|cpu_data
)paren
suffix:semicolon
macro_line|#endif
eof
