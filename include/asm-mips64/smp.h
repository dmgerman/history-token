multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file &quot;COPYING&quot; in the main directory of this&n; * archive for more details.&n; *&n; * Copyright (C) 2000 - 2001 by Kanoj Sarcar (kanoj@sgi.com)&n; * Copyright (C) 2000 - 2001 by Silicon Graphics, Inc.&n; */
macro_line|#ifndef __ASM_SMP_H
DECL|macro|__ASM_SMP_H
mdefine_line|#define __ASM_SMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#if 0
r_struct
id|cpuinfo_mips
(brace
multiline_comment|/* XXX  */
r_int
r_int
id|loops_per_sec
suffix:semicolon
r_int
r_int
id|last_asn
suffix:semicolon
r_int
r_int
op_star
id|pgd_cache
suffix:semicolon
r_int
r_int
op_star
id|pte_cache
suffix:semicolon
r_int
r_int
id|pgtable_cache_sz
suffix:semicolon
r_int
r_int
id|ipi_count
suffix:semicolon
r_int
r_int
id|irq_attempt
(braket
id|NR_IRQS
)braket
suffix:semicolon
r_int
r_int
id|smp_local_irq_count
suffix:semicolon
r_int
r_int
id|prof_multiplier
suffix:semicolon
r_int
r_int
id|prof_counter
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|64
)paren
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|cpuinfo_mips
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
macro_line|#endif
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id()&t;(current-&gt;processor)
DECL|macro|PROC_CHANGE_PENALTY
mdefine_line|#define PROC_CHANGE_PENALTY&t;20
multiline_comment|/* Map from cpu id to sequential logical cpu number.  This will only&n;   not be idempotent when cpus failed to come on-line.  */
r_extern
r_int
id|__cpu_number_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|cpu_number_map
mdefine_line|#define cpu_number_map(cpu)  __cpu_number_map[cpu]
multiline_comment|/* The reverse map from sequential logical cpu number to cpu id.  */
r_extern
r_int
id|__cpu_logical_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|cpu_logical_map
mdefine_line|#define cpu_logical_map(cpu)  __cpu_logical_map[cpu]
macro_line|#endif
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;(-1)
macro_line|#if (NR_CPUS &lt;= _MIPS_SZLONG)
DECL|typedef|cpumask_t
r_typedef
r_int
r_int
id|cpumask_t
suffix:semicolon
DECL|macro|CPUMASK_CLRALL
mdefine_line|#define CPUMASK_CLRALL(p)&t;(p) = 0
DECL|macro|CPUMASK_SETB
mdefine_line|#define CPUMASK_SETB(p, bit)&t;(p) |= 1 &lt;&lt; (bit)
DECL|macro|CPUMASK_CLRB
mdefine_line|#define CPUMASK_CLRB(p, bit)&t;(p) &amp;= ~(1ULL &lt;&lt; (bit))
DECL|macro|CPUMASK_TSTB
mdefine_line|#define CPUMASK_TSTB(p, bit)&t;((p) &amp; (1ULL &lt;&lt; (bit)))
macro_line|#elif (NR_CPUS &lt;= 128)
multiline_comment|/*&n; * The foll should work till 128 cpus.&n; */
DECL|macro|CPUMASK_SIZE
mdefine_line|#define CPUMASK_SIZE&t;&t;(NR_CPUS/_MIPS_SZLONG)
DECL|macro|CPUMASK_INDEX
mdefine_line|#define CPUMASK_INDEX(bit)&t;((bit) &gt;&gt; 6)
DECL|macro|CPUMASK_SHFT
mdefine_line|#define CPUMASK_SHFT(bit)&t;((bit) &amp; 0x3f)
r_typedef
r_struct
(brace
DECL|member|_bits
r_int
r_int
id|_bits
(braket
id|CPUMASK_SIZE
)braket
suffix:semicolon
DECL|typedef|cpumask_t
)brace
id|cpumask_t
suffix:semicolon
DECL|macro|CPUMASK_CLRALL
mdefine_line|#define&t;CPUMASK_CLRALL(p)&t;(p)._bits[0] = 0, (p)._bits[1] = 0
DECL|macro|CPUMASK_SETB
mdefine_line|#define CPUMASK_SETB(p, bit)&t;(p)._bits[CPUMASK_INDEX(bit)] |= &bslash;&n;&t;&t;&t;&t;&t;(1ULL &lt;&lt; CPUMASK_SHFT(bit))
DECL|macro|CPUMASK_CLRB
mdefine_line|#define CPUMASK_CLRB(p, bit)&t;(p)._bits[CPUMASK_INDEX(bit)] &amp;= &bslash;&n;&t;&t;&t;&t;&t;~(1ULL &lt;&lt; CPUMASK_SHFT(bit))
DECL|macro|CPUMASK_TSTB
mdefine_line|#define CPUMASK_TSTB(p, bit)&t;((p)._bits[CPUMASK_INDEX(bit)] &amp; &bslash;&n;&t;&t;&t;&t;&t;(1ULL &lt;&lt; CPUMASK_SHFT(bit)))
macro_line|#else
macro_line|#error cpumask macros only defined for 128p kernels
macro_line|#endif
macro_line|#endif /* __ASM_SMP_H */
eof
