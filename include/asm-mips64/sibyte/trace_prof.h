multiline_comment|/*&n; * Copyright (C) 2001 Broadcom Corporation&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#ifndef __ASM_SIBYTE_TRACE_PROF_H
DECL|macro|__ASM_SIBYTE_TRACE_PROF_H
mdefine_line|#define __ASM_SIBYTE_TRACE_PROF_H
macro_line|#if SBPROF_TB_DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(a) a
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(a)
macro_line|#endif
DECL|macro|SBPROF_TB_MAJOR
mdefine_line|#define SBPROF_TB_MAJOR 240
DECL|macro|DEVNAME
mdefine_line|#define DEVNAME &quot;bcm1250_tbprof&quot;
DECL|typedef|tb_sample_t
r_typedef
id|u_int64_t
id|tb_sample_t
(braket
l_int|6
op_star
l_int|256
)braket
suffix:semicolon
DECL|struct|sbprof_tb
r_struct
id|sbprof_tb
(brace
DECL|member|open
r_int
id|open
suffix:semicolon
DECL|member|sbprof_tbbuf
id|tb_sample_t
op_star
id|sbprof_tbbuf
suffix:semicolon
DECL|member|next_tb_sample
r_int
id|next_tb_sample
suffix:semicolon
DECL|member|tb_enable
r_volatile
r_int
id|tb_enable
suffix:semicolon
DECL|member|tb_armed
r_volatile
r_int
id|tb_armed
suffix:semicolon
DECL|member|tb_sync
id|wait_queue_head_t
id|tb_sync
suffix:semicolon
DECL|member|tb_read
id|wait_queue_head_t
id|tb_read
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MAX_SAMPLE_BYTES
mdefine_line|#define MAX_SAMPLE_BYTES (24*1024*1024)
DECL|macro|MAX_TBSAMPLE_BYTES
mdefine_line|#define MAX_TBSAMPLE_BYTES (12*1024*1024)
DECL|macro|MAX_SAMPLES
mdefine_line|#define MAX_SAMPLES (MAX_SAMPLE_BYTES/sizeof(u_int32_t))
DECL|macro|TB_SAMPLE_SIZE
mdefine_line|#define TB_SAMPLE_SIZE (sizeof(tb_sample_t))
DECL|macro|MAX_TB_SAMPLES
mdefine_line|#define MAX_TB_SAMPLES (MAX_TBSAMPLE_BYTES/TB_SAMPLE_SIZE)
multiline_comment|/* IOCTLs */
DECL|macro|SBPROF_ZBSTART
mdefine_line|#define SBPROF_ZBSTART&t;&t;_IOW(&squot;s&squot;, 0, int)
DECL|macro|SBPROF_ZBSTOP
mdefine_line|#define SBPROF_ZBSTOP&t;&t;_IOW(&squot;s&squot;, 1, int)
DECL|macro|SBPROF_ZBWAITFULL
mdefine_line|#define SBPROF_ZBWAITFULL&t;_IOW(&squot;s&squot;, 2, int)
multiline_comment|/***************************************************************************&n; * Routines for gathering ZBbus profiles using trace buffer&n; ***************************************************************************/
multiline_comment|/* Requires: Already called zclk_timer_init with a value that won&squot;t&n;&t;     saturate 40 bits.  No subsequent use of SCD performance counters&n;&t;     or trace buffer.&n;   Effect:   Starts gathering random ZBbus profiles using trace buffer. */
r_static
r_int
id|sbprof_zbprof_start
c_func
(paren
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
multiline_comment|/* Effect: Stops collection of ZBbus profiles */
r_static
r_int
id|sbprof_zbprof_stop
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/***************************************************************************&n; * Routines for using 40-bit SCD cycle counter&n; *&n; * Client responsible for either handling interrupts or making sure&n; * the cycles counter never saturates, e.g., by doing&n; * zclk_timer_init(0) at least every 2^40 - 1 ZCLKs.&n; ***************************************************************************/
multiline_comment|/* Configures SCD counter 0 to count ZCLKs starting from val;&n;   Configures SCD counters1,2,3 to count nothing.&n;   Must not be called while gathering ZBbus profiles.&n;&n;unsigned long long val; */
DECL|macro|zclk_timer_init
mdefine_line|#define zclk_timer_init(val) &bslash;&n;  __asm__ __volatile__ (&quot;.set push;&quot; &bslash;&n;&t;&t;&t;&quot;.set mips64;&quot; &bslash;&n;&t;&t;&t;&quot;la   $8, 0xb00204c0;&quot; /* SCD perf_cnt_cfg */ &bslash;&n;&t;&t;&t;&quot;sd   %0, 0x10($8);&quot;   /* write val to counter0 */ &bslash;&n;&t;&t;&t;&quot;sd   %1, 0($8);&quot;      /* config counter0 for zclks*/ &bslash;&n;&t;&t;&t;&quot;.set pop&quot; &bslash;&n;&t;&t;&t;: /* no outputs */ &bslash;&n;&t;&t;&t;&t;&t;&t;     /* enable, counter0 */ &bslash;&n;&t;&t;&t;: /* inputs */ &quot;r&quot;(val), &quot;r&quot; ((1ULL &lt;&lt; 33) | 1ULL) &bslash;&n;&t;&t;&t;: /* modifies */ &quot;$8&quot; )
multiline_comment|/* Reads SCD counter 0 and puts result in value&n;   unsigned long long val; */
DECL|macro|zclk_get
mdefine_line|#define zclk_get(val) &bslash;&n;  __asm__ __volatile__ (&quot;.set push;&quot; &bslash;&n;&t;&t;&t;&quot;.set mips64;&quot; &bslash;&n;&t;&t;&t;&quot;la   $8, 0xb00204c0;&quot; /* SCD perf_cnt_cfg */ &bslash;&n;&t;&t;&t;&quot;ld   %0, 0x10($8);&quot;   /* write val to counter0 */ &bslash;&n;&t;&t;&t;&quot;.set pop&quot; &bslash;&n;&t;&t;&t;: /* outputs */ &quot;=r&quot;(val) &bslash;&n;&t;&t;&t;: /* inputs */ &bslash;&n;&t;&t;&t;: /* modifies */ &quot;$8&quot; )
macro_line|#endif /* __ASM_SIBYTE_TRACE_PROF_H */
eof
