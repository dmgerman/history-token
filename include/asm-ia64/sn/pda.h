multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_PDA_H
DECL|macro|_ASM_IA64_SN_PDA_H
mdefine_line|#define _ASM_IA64_SN_PDA_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/sn/bte.h&gt;
multiline_comment|/*&n; * CPU-specific data structure.&n; *&n; * One of these structures is allocated for each cpu of a NUMA system.&n; *&n; * This structure provides a convenient way of keeping together &n; * all SN per-cpu data structures. &n; */
DECL|struct|pda_s
r_typedef
r_struct
id|pda_s
(brace
multiline_comment|/* Having a pointer in the begining of PDA tends to increase&n;&t; * the chance of having this pointer in cache. (Yes something&n;&t; * else gets pushed out). Doing this reduces the number of memory&n;&t; * access to all nodepda variables to be one&n;&t; */
DECL|member|p_nodepda
r_struct
id|nodepda_s
op_star
id|p_nodepda
suffix:semicolon
multiline_comment|/* Pointer to Per node PDA */
DECL|member|p_subnodepda
r_struct
id|subnodepda_s
op_star
id|p_subnodepda
suffix:semicolon
multiline_comment|/* Pointer to CPU  subnode PDA */
multiline_comment|/*&n;&t; * Support for blinking SN LEDs&n;&t; */
DECL|member|led_address
r_int
op_star
id|led_address
suffix:semicolon
DECL|member|led_state
id|u8
id|led_state
suffix:semicolon
DECL|member|hb_state
r_char
id|hb_state
suffix:semicolon
multiline_comment|/* supports blinking heartbeat leds */
DECL|member|hb_count
r_int
r_int
id|hb_count
suffix:semicolon
DECL|member|idle_flag
r_int
r_int
id|idle_flag
suffix:semicolon
macro_line|#ifdef CONFIG_IA64_SGI_SN2
DECL|member|p_irqpda
r_struct
id|irqpda_s
op_star
id|p_irqpda
suffix:semicolon
multiline_comment|/* Pointer to CPU irq data */
macro_line|#endif
DECL|member|bedrock_rev_id
r_volatile
r_int
r_int
op_star
id|bedrock_rev_id
suffix:semicolon
DECL|member|pio_write_status_addr
r_volatile
r_int
r_int
op_star
id|pio_write_status_addr
suffix:semicolon
DECL|member|cpubte
id|bteinfo_t
op_star
id|cpubte
(braket
id|BTES_PER_NODE
)braket
suffix:semicolon
DECL|typedef|pda_t
)brace
id|pda_t
suffix:semicolon
DECL|macro|CACHE_ALIGN
mdefine_line|#define CACHE_ALIGN(x)&t;(((x) + SMP_CACHE_BYTES-1) &amp; ~(SMP_CACHE_BYTES-1))
multiline_comment|/*&n; * PDA&n; * Per-cpu private data area for each cpu. The PDA is located immediately after&n; * the IA64 cpu_data area. A full page is allocated for the cp_data area for each&n; * cpu but only a small amout of the page is actually used. We put the SNIA PDA&n; * in the same page as the cpu_data area. Note that there is a check in the setup&n; * code to verify that we dont overflow the page.&n; *&n; * Seems like we should should cache-line align the pda so that any changes in the&n; * size of the cpu_data area dont change cache layout. Should we align to 32, 64, 128&n; * or 512 boundary. Each has merits. For now, pick 128 but should be revisited later.&n; */
DECL|macro|CPU_DATA_END
mdefine_line|#define CPU_DATA_END&t;CACHE_ALIGN((long)&amp;(((struct cpuinfo_ia64*)0)-&gt;platform_specific))
DECL|macro|PDAADDR
mdefine_line|#define PDAADDR&t;&t;(PERCPU_ADDR+CPU_DATA_END)
DECL|macro|pda
mdefine_line|#define pda&t;&t;(*((pda_t *) PDAADDR))
macro_line|#endif /* _ASM_IA64_SN_PDA_H */
eof
