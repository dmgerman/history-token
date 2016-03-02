macro_line|#ifndef _ASM_IA64_SN_SN1_SYNERGY_H
DECL|macro|_ASM_IA64_SN_SN1_SYNERGY_H
mdefine_line|#define _ASM_IA64_SN_SN1_SYNERGY_H
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/intr_public.h&gt;
multiline_comment|/*&n; * Definitions for the synergy asic driver&n; * &n; * These are for SGI platforms only.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All rights reserved.&n; */
DECL|macro|SYNERGY_L4_BYTES
mdefine_line|#define SYNERGY_L4_BYTES&t;&t;(64UL*1024*1024)
DECL|macro|SYNERGY_L4_WAYS
mdefine_line|#define SYNERGY_L4_WAYS&t;&t;&t;8
DECL|macro|SYNERGY_L4_BYTES_PER_WAY
mdefine_line|#define SYNERGY_L4_BYTES_PER_WAY&t;(SYNERGY_L4_BYTES/SYNERGY_L4_WAYS)
DECL|macro|SYNERGY_BLOCK_SIZE
mdefine_line|#define SYNERGY_BLOCK_SIZE&t;&t;512UL
DECL|macro|SSPEC_BASE
mdefine_line|#define SSPEC_BASE&t;(0xe0000000000UL)
DECL|macro|LB_REG_BASE
mdefine_line|#define LB_REG_BASE&t;(SSPEC_BASE + 0x0)
DECL|macro|VEC_MASK3A_ADDR
mdefine_line|#define VEC_MASK3A_ADDR&t;(0x2a0 + LB_REG_BASE + __IA64_UNCACHED_OFFSET)
DECL|macro|VEC_MASK3B_ADDR
mdefine_line|#define VEC_MASK3B_ADDR&t;(0x2a8 + LB_REG_BASE + __IA64_UNCACHED_OFFSET)
DECL|macro|VEC_MASK3A
mdefine_line|#define VEC_MASK3A&t;(0x2a0)
DECL|macro|VEC_MASK3B
mdefine_line|#define VEC_MASK3B&t;(0x2a8)
DECL|macro|VEC_MASK2A_ADDR
mdefine_line|#define VEC_MASK2A_ADDR&t;(0x2b0 + LB_REG_BASE + __IA64_UNCACHED_OFFSET)
DECL|macro|VEC_MASK2B_ADDR
mdefine_line|#define VEC_MASK2B_ADDR&t;(0x2b8 + LB_REG_BASE + __IA64_UNCACHED_OFFSET)
DECL|macro|VEC_MASK2A
mdefine_line|#define VEC_MASK2A&t;(0x2b0)
DECL|macro|VEC_MASK2B
mdefine_line|#define VEC_MASK2B&t;(0x2b8)
DECL|macro|VEC_MASK1A_ADDR
mdefine_line|#define VEC_MASK1A_ADDR&t;(0x2c0 + LB_REG_BASE + __IA64_UNCACHED_OFFSET)
DECL|macro|VEC_MASK1B_ADDR
mdefine_line|#define VEC_MASK1B_ADDR&t;(0x2c8 + LB_REG_BASE + __IA64_UNCACHED_OFFSET)
DECL|macro|VEC_MASK1A
mdefine_line|#define VEC_MASK1A&t;(0x2c0)
DECL|macro|VEC_MASK1B
mdefine_line|#define VEC_MASK1B&t;(0x2c8)
DECL|macro|VEC_MASK0A_ADDR
mdefine_line|#define VEC_MASK0A_ADDR&t;(0x2d0 + LB_REG_BASE + __IA64_UNCACHED_OFFSET)
DECL|macro|VEC_MASK0B_ADDR
mdefine_line|#define VEC_MASK0B_ADDR&t;(0x2d8 + LB_REG_BASE + __IA64_UNCACHED_OFFSET)
DECL|macro|VEC_MASK0A
mdefine_line|#define VEC_MASK0A&t;(0x2d0)
DECL|macro|VEC_MASK0B
mdefine_line|#define VEC_MASK0B&t;(0x2d8)
DECL|macro|GBL_PERF_A_ADDR
mdefine_line|#define GBL_PERF_A_ADDR (0x330 + LB_REG_BASE + __IA64_UNCACHED_OFFSET)
DECL|macro|GBL_PERF_B_ADDR
mdefine_line|#define GBL_PERF_B_ADDR (0x338 + LB_REG_BASE + __IA64_UNCACHED_OFFSET)
DECL|macro|WRITE_LOCAL_SYNERGY_REG
mdefine_line|#define WRITE_LOCAL_SYNERGY_REG(addr, value)&t;__synergy_out(addr, value)
DECL|macro|HSPEC_SYNERGY0_0
mdefine_line|#define HSPEC_SYNERGY0_0        0x04000000    /* Synergy0 Registers     */
DECL|macro|HSPEC_SYNERGY1_0
mdefine_line|#define HSPEC_SYNERGY1_0        0x05000000    /* Synergy1 Registers     */
DECL|macro|HS_SYNERGY_STRIDE
mdefine_line|#define HS_SYNERGY_STRIDE       (HSPEC_SYNERGY1_0 - HSPEC_SYNERGY0_0)
DECL|macro|REMOTE_HSPEC
mdefine_line|#define REMOTE_HSPEC(_n, _x)    (HUBREG_CAST (RREG_BASE(_n) + (_x)))
DECL|macro|RREG_BASE
mdefine_line|#define RREG_BASE(_n)           (NODE_LREG_BASE(_n))
DECL|macro|NODE_LREG_BASE
mdefine_line|#define NODE_LREG_BASE(_n)      (NODE_HSPEC_BASE(_n) + 0x30000000)
DECL|macro|NODE_HSPEC_BASE
mdefine_line|#define NODE_HSPEC_BASE(_n)     (HSPEC_BASE + NODE_OFFSET(_n))
macro_line|#ifndef HSPEC_BASE
DECL|macro|HSPEC_BASE
mdefine_line|#define HSPEC_BASE              (SYN_UNCACHED_SPACE | HSPEC_BASE_SYN)
macro_line|#endif
DECL|macro|SYN_UNCACHED_SPACE
mdefine_line|#define SYN_UNCACHED_SPACE      0xc000000000000000
DECL|macro|HSPEC_BASE_SYN
mdefine_line|#define HSPEC_BASE_SYN          0x00000b0000000000
DECL|macro|NODE_OFFSET
mdefine_line|#define NODE_OFFSET(_n)         (UINT64_CAST (_n) &lt;&lt; NODE_SIZE_BITS)
DECL|macro|NODE_SIZE_BITS
mdefine_line|#define NODE_SIZE_BITS&t;&t;33
DECL|macro|SYN_TAG_DISABLE_WAY
mdefine_line|#define SYN_TAG_DISABLE_WAY&t;(SSPEC_BASE+0xae0)
DECL|macro|RSYN_REG_OFFSET
mdefine_line|#define RSYN_REG_OFFSET(fsb, reg) (((fsb) ? HSPEC_SYNERGY1_0 : HSPEC_SYNERGY0_0) | (reg))
DECL|macro|REMOTE_SYNERGY_LOAD
mdefine_line|#define REMOTE_SYNERGY_LOAD(nasid, fsb, reg)  __remote_synergy_in(nasid, fsb, reg)
DECL|macro|REMOTE_SYNERGY_STORE
mdefine_line|#define REMOTE_SYNERGY_STORE(nasid, fsb, reg, val) __remote_synergy_out(nasid, fsb, reg, val)
r_static
r_inline
r_uint64
DECL|function|__remote_synergy_in
id|__remote_synergy_in
c_func
(paren
r_int
id|nasid
comma
r_int
id|fsb
comma
r_uint64
id|reg
)paren
(brace
r_volatile
r_uint64
op_star
id|addr
suffix:semicolon
id|addr
op_assign
(paren
r_uint64
op_star
)paren
(paren
id|RREG_BASE
c_func
(paren
id|nasid
)paren
op_plus
id|RSYN_REG_OFFSET
c_func
(paren
id|fsb
comma
id|reg
)paren
)paren
suffix:semicolon
r_return
(paren
op_star
id|addr
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__remote_synergy_out
id|__remote_synergy_out
c_func
(paren
r_int
id|nasid
comma
r_int
id|fsb
comma
r_uint64
id|reg
comma
r_uint64
id|value
)paren
(brace
r_volatile
r_uint64
op_star
id|addr
suffix:semicolon
id|addr
op_assign
(paren
r_uint64
op_star
)paren
(paren
id|RREG_BASE
c_func
(paren
id|nasid
)paren
op_plus
id|RSYN_REG_OFFSET
c_func
(paren
id|fsb
comma
(paren
id|reg
op_lshift
l_int|2
)paren
)paren
)paren
suffix:semicolon
op_star
(paren
id|addr
op_plus
l_int|0
)paren
op_assign
id|value
op_rshift
l_int|48
suffix:semicolon
op_star
(paren
id|addr
op_plus
l_int|1
)paren
op_assign
id|value
op_rshift
l_int|32
suffix:semicolon
op_star
(paren
id|addr
op_plus
l_int|2
)paren
op_assign
id|value
op_rshift
l_int|16
suffix:semicolon
op_star
(paren
id|addr
op_plus
l_int|3
)paren
op_assign
id|value
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* XX this doesn&squot;t make a lot of sense. Which fsb?  */
r_static
r_inline
r_void
DECL|function|__synergy_out
id|__synergy_out
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|value
)paren
(brace
r_volatile
r_int
r_int
op_star
id|adr
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|addr
op_or
id|__IA64_UNCACHED_OFFSET
)paren
suffix:semicolon
op_star
id|adr
op_assign
id|value
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|macro|READ_LOCAL_SYNERGY_REG
mdefine_line|#define READ_LOCAL_SYNERGY_REG(addr)&t;__synergy_in(addr)
multiline_comment|/* XX this doesn&squot;t make a lot of sense. Which fsb? */
r_static
r_inline
r_int
r_int
DECL|function|__synergy_in
id|__synergy_in
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|ret
comma
op_star
id|adr
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|addr
op_or
id|__IA64_UNCACHED_OFFSET
)paren
suffix:semicolon
id|ret
op_assign
op_star
id|adr
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|struct|sn1_intr_action
r_struct
id|sn1_intr_action
(brace
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|member|intr_arg
r_void
op_star
id|intr_arg
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|next
r_struct
id|sn1_intr_action
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|synergy_da_s
r_typedef
r_struct
id|synergy_da_s
(brace
DECL|member|s_intmasks
id|hub_intmasks_t
id|s_intmasks
suffix:semicolon
DECL|typedef|synergy_da_t
)brace
id|synergy_da_t
suffix:semicolon
DECL|struct|sn1_cnode_action_list
r_struct
id|sn1_cnode_action_list
(brace
DECL|member|action_list_lock
id|spinlock_t
id|action_list_lock
suffix:semicolon
DECL|member|action_list
r_struct
id|sn1_intr_action
op_star
id|action_list
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ioctl cmds for node/hub/synergy/[01]/mon for synergy&n; * perf monitoring are defined in sndrv.h&n; */
multiline_comment|/* multiplex the counters every 10 timer interrupts */
DECL|macro|SYNERGY_PERF_FREQ_DEFAULT
mdefine_line|#define SYNERGY_PERF_FREQ_DEFAULT 10
multiline_comment|/* macros for synergy &quot;mon&quot; device ioctl handler */
DECL|macro|SYNERGY_PERF_INFO
mdefine_line|#define SYNERGY_PERF_INFO(_s, _f)&t;(arbitrary_info_t)(((_s) &lt;&lt; 16)|(_f))
DECL|macro|SYNERGY_PERF_INFO_CNODE
mdefine_line|#define SYNERGY_PERF_INFO_CNODE(_x)&t;(cnodeid_t)(((uint64_t)_x) &gt;&gt; 16)
DECL|macro|SYNERGY_PERF_INFO_FSB
mdefine_line|#define SYNERGY_PERF_INFO_FSB(_x)&t;(((uint64_t)_x) &amp; 1)
multiline_comment|/* synergy perf control registers */
DECL|macro|PERF_CNTL0_A
mdefine_line|#define PERF_CNTL0_A            0xab0UL /* control A on FSB0 */
DECL|macro|PERF_CNTL0_B
mdefine_line|#define PERF_CNTL0_B            0xab8UL /* control B on FSB0 */
DECL|macro|PERF_CNTL1_A
mdefine_line|#define PERF_CNTL1_A            0xac0UL /* control A on FSB1 */
DECL|macro|PERF_CNTL1_B
mdefine_line|#define PERF_CNTL1_B            0xac8UL /* control B on FSB1 */
multiline_comment|/* synergy perf counters */
DECL|macro|PERF_CNTR0_A
mdefine_line|#define PERF_CNTR0_A            0xad0UL /* counter A on FSB0 */
DECL|macro|PERF_CNTR0_B
mdefine_line|#define PERF_CNTR0_B            0xad8UL /* counter B on FSB0 */
DECL|macro|PERF_CNTR1_A
mdefine_line|#define PERF_CNTR1_A            0xaf0UL /* counter A on FSB1 */
DECL|macro|PERF_CNTR1_B
mdefine_line|#define PERF_CNTR1_B            0xaf8UL /* counter B on FSB1 */
multiline_comment|/* Synergy perf data. Each nodepda keeps a list of these */
DECL|struct|synergy_perf_s
r_struct
id|synergy_perf_s
(brace
DECL|member|intervals
r_uint64
id|intervals
suffix:semicolon
multiline_comment|/* count of active intervals for this event */
DECL|member|total_intervals
r_uint64
id|total_intervals
suffix:semicolon
multiline_comment|/* snapshot of total intervals */
DECL|member|modesel
r_uint64
id|modesel
suffix:semicolon
multiline_comment|/* mode and sel bits, both A and B registers */
DECL|member|next
r_struct
id|synergy_perf_s
op_star
id|next
suffix:semicolon
multiline_comment|/* next in circular linked list */
DECL|member|counts
r_uint64
id|counts
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* [0] is synergy-A counter, [1] synergy-B counter */
)brace
suffix:semicolon
DECL|typedef|synergy_perf_t
r_typedef
r_struct
id|synergy_perf_s
id|synergy_perf_t
suffix:semicolon
DECL|typedef|synergy_info_t
r_typedef
r_struct
id|synergy_info_s
id|synergy_info_t
suffix:semicolon
r_extern
r_void
id|synergy_perf_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|synergy_perf_update
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|file_operations
id|synergy_mon_fops
suffix:semicolon
macro_line|#endif /* _ASM_IA64_SN_SN1_SYNERGY_H */
eof
