multiline_comment|/* cpudata.h: Per-cpu parameters.&n; *&n; * Copyright (C) 2004 Keith M Wesolowski (wesolows@foobazco.org)&n; *&n; * Based on include/asm-sparc64/cpudata.h and Linux 2.4 smp.h&n; * both (C) David S. Miller.&n; */
macro_line|#ifndef _SPARC_CPUDATA_H
DECL|macro|_SPARC_CPUDATA_H
mdefine_line|#define _SPARC_CPUDATA_H
macro_line|#include &lt;linux/percpu.h&gt;
r_typedef
r_struct
(brace
DECL|member|udelay_val
r_int
r_int
id|udelay_val
suffix:semicolon
DECL|member|clock_tick
r_int
r_int
id|clock_tick
suffix:semicolon
DECL|member|multiplier
r_int
r_int
id|multiplier
suffix:semicolon
DECL|member|counter
r_int
r_int
id|counter
suffix:semicolon
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|mid
r_int
id|mid
suffix:semicolon
DECL|typedef|cpuinfo_sparc
)brace
id|cpuinfo_sparc
suffix:semicolon
id|DECLARE_PER_CPU
c_func
(paren
id|cpuinfo_sparc
comma
id|__cpu_data
)paren
suffix:semicolon
DECL|macro|cpu_data
mdefine_line|#define cpu_data(__cpu) per_cpu(__cpu_data, (__cpu))
macro_line|#endif /* _SPARC_CPUDATA_H */
eof
