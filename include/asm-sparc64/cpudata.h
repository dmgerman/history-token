multiline_comment|/* cpudata.h: Per-cpu parameters.&n; *&n; * Copyright (C) 2003 David S. Miller (davem@redhat.com)&n; */
macro_line|#ifndef _SPARC64_CPUDATA_H
DECL|macro|_SPARC64_CPUDATA_H
mdefine_line|#define _SPARC64_CPUDATA_H
macro_line|#include &lt;linux/percpu.h&gt;
r_typedef
r_struct
(brace
multiline_comment|/* Dcache line 1 */
DECL|member|__pad0
r_int
r_int
id|__pad0
suffix:semicolon
multiline_comment|/* bh_count moved to irq_stat for consistency. KAO */
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
DECL|member|idle_volume
r_int
r_int
id|idle_volume
suffix:semicolon
DECL|member|clock_tick
r_int
r_int
id|clock_tick
suffix:semicolon
multiline_comment|/* %tick&squot;s per second */
DECL|member|udelay_val
r_int
r_int
id|udelay_val
suffix:semicolon
multiline_comment|/* Dcache line 2 */
DECL|member|pgcache_size
r_int
r_int
id|pgcache_size
suffix:semicolon
DECL|member|pgdcache_size
r_int
r_int
id|pgdcache_size
suffix:semicolon
DECL|member|pte_cache
r_int
r_int
op_star
id|pte_cache
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|pgd_cache
r_int
r_int
op_star
id|pgd_cache
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
mdefine_line|#define cpu_data(__cpu)&t;per_cpu(__cpu_data, (__cpu))
macro_line|#endif /* _SPARC64_CPUDATA_H */
eof
