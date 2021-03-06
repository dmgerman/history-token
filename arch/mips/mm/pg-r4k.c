multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003, 04, 05 Ralf Baechle (ralf@linux-mips.org)&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/cacheops.h&gt;
macro_line|#include &lt;asm/inst.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/prefetch.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/war.h&gt;
DECL|macro|half_scache_line_size
mdefine_line|#define half_scache_line_size()&t;&t;(cpu_scache_line_size() &gt;&gt; 1)
multiline_comment|/*&n; * Maximum sizes:&n; *&n; * R4000 128 bytes S-cache:&t;&t;0x58 bytes&n; * R4600 v1.7:&t;&t;&t;&t;0x5c bytes&n; * R4600 v2.0:&t;&t;&t;&t;0x60 bytes&n; * With prefetching, 16 byte strides&t;0xa0 bytes&n; */
DECL|variable|clear_page_array
r_static
r_int
r_int
id|clear_page_array
(braket
l_int|0x130
op_div
l_int|4
)braket
suffix:semicolon
r_void
id|clear_page
c_func
(paren
r_void
op_star
id|page
)paren
id|__attribute__
c_func
(paren
(paren
id|alias
c_func
(paren
l_string|&quot;clear_page_array&quot;
)paren
)paren
)paren
suffix:semicolon
DECL|variable|clear_page
id|EXPORT_SYMBOL
c_func
(paren
id|clear_page
)paren
suffix:semicolon
multiline_comment|/*&n; * Maximum sizes:&n; *&n; * R4000 128 bytes S-cache:&t;&t;0x11c bytes&n; * R4600 v1.7:&t;&t;&t;&t;0x080 bytes&n; * R4600 v2.0:&t;&t;&t;&t;0x07c bytes&n; * With prefetching, 16 byte strides&t;0x0b8 bytes&n; */
DECL|variable|copy_page_array
r_static
r_int
r_int
id|copy_page_array
(braket
l_int|0x148
op_div
l_int|4
)braket
suffix:semicolon
r_void
id|copy_page
c_func
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
)paren
id|__attribute__
c_func
(paren
(paren
id|alias
c_func
(paren
l_string|&quot;copy_page_array&quot;
)paren
)paren
)paren
suffix:semicolon
DECL|variable|copy_page
id|EXPORT_SYMBOL
c_func
(paren
id|copy_page
)paren
suffix:semicolon
multiline_comment|/*&n; * This is suboptimal for 32-bit kernels; we assume that R10000 is only used&n; * with 64-bit kernels.  The prefetch offsets have been experimentally tuned&n; * an Origin 200.&n; */
DECL|variable|__initdata
r_static
r_int
id|pref_offset_clear
id|__initdata
op_assign
l_int|512
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|pref_offset_copy
id|__initdata
op_assign
l_int|256
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
r_int
id|pref_src_mode
id|__initdata
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
r_int
id|pref_dst_mode
id|__initdata
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|load_offset
id|__initdata
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|store_offset
id|__initdata
suffix:semicolon
DECL|variable|dest
DECL|variable|epc
r_static
r_int
r_int
id|__initdata
op_star
id|dest
comma
op_star
id|epc
suffix:semicolon
DECL|variable|instruction_pending
r_static
r_int
r_int
id|instruction_pending
suffix:semicolon
DECL|variable|delayed_mi
r_static
r_union
id|mips_instruction
id|delayed_mi
suffix:semicolon
DECL|function|emit_instruction
r_static
r_void
id|__init
id|emit_instruction
c_func
(paren
r_union
id|mips_instruction
id|mi
)paren
(brace
r_if
c_cond
(paren
id|instruction_pending
)paren
op_star
id|epc
op_increment
op_assign
id|delayed_mi.word
suffix:semicolon
id|instruction_pending
op_assign
l_int|1
suffix:semicolon
id|delayed_mi
op_assign
id|mi
suffix:semicolon
)brace
DECL|function|flush_delay_slot_or_nop
r_static
r_inline
r_void
id|flush_delay_slot_or_nop
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|instruction_pending
)paren
(brace
op_star
id|epc
op_increment
op_assign
id|delayed_mi.word
suffix:semicolon
id|instruction_pending
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
op_star
id|epc
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|label
r_static
r_inline
r_int
r_int
op_star
id|label
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|instruction_pending
)paren
(brace
op_star
id|epc
op_increment
op_assign
id|delayed_mi.word
suffix:semicolon
id|instruction_pending
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|epc
suffix:semicolon
)brace
DECL|function|build_insn_word
r_static
r_inline
r_void
id|build_insn_word
c_func
(paren
r_int
r_int
id|word
)paren
(brace
r_union
id|mips_instruction
id|mi
suffix:semicolon
id|mi.word
op_assign
id|word
suffix:semicolon
id|emit_instruction
c_func
(paren
id|mi
)paren
suffix:semicolon
)brace
DECL|function|build_nop
r_static
r_inline
r_void
id|build_nop
c_func
(paren
r_void
)paren
(brace
id|build_insn_word
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* nop */
)brace
DECL|function|build_src_pref
r_static
r_inline
r_void
id|build_src_pref
c_func
(paren
r_int
id|advance
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|load_offset
op_amp
(paren
id|cpu_dcache_line_size
c_func
(paren
)paren
op_minus
l_int|1
)paren
)paren
)paren
(brace
r_union
id|mips_instruction
id|mi
suffix:semicolon
id|mi.i_format.opcode
op_assign
id|pref_op
suffix:semicolon
id|mi.i_format.rs
op_assign
l_int|5
suffix:semicolon
multiline_comment|/* $a1 */
id|mi.i_format.rt
op_assign
id|pref_src_mode
suffix:semicolon
id|mi.i_format.simmediate
op_assign
id|load_offset
op_plus
id|advance
suffix:semicolon
id|emit_instruction
c_func
(paren
id|mi
)paren
suffix:semicolon
)brace
)brace
DECL|function|__build_load_reg
r_static
r_inline
r_void
id|__build_load_reg
c_func
(paren
r_int
id|reg
)paren
(brace
r_union
id|mips_instruction
id|mi
suffix:semicolon
r_int
r_int
id|width
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_64bit_gp_regs
)paren
(brace
id|mi.i_format.opcode
op_assign
id|ld_op
suffix:semicolon
id|width
op_assign
l_int|8
suffix:semicolon
)brace
r_else
(brace
id|mi.i_format.opcode
op_assign
id|lw_op
suffix:semicolon
id|width
op_assign
l_int|4
suffix:semicolon
)brace
id|mi.i_format.rs
op_assign
l_int|5
suffix:semicolon
multiline_comment|/* $a1 */
id|mi.i_format.rt
op_assign
id|reg
suffix:semicolon
multiline_comment|/* $reg */
id|mi.i_format.simmediate
op_assign
id|load_offset
suffix:semicolon
id|load_offset
op_add_assign
id|width
suffix:semicolon
id|emit_instruction
c_func
(paren
id|mi
)paren
suffix:semicolon
)brace
DECL|function|build_load_reg
r_static
r_inline
r_void
id|build_load_reg
c_func
(paren
r_int
id|reg
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_prefetch
)paren
id|build_src_pref
c_func
(paren
id|pref_offset_copy
)paren
suffix:semicolon
id|__build_load_reg
c_func
(paren
id|reg
)paren
suffix:semicolon
)brace
DECL|function|build_dst_pref
r_static
r_inline
r_void
id|build_dst_pref
c_func
(paren
r_int
id|advance
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|store_offset
op_amp
(paren
id|cpu_dcache_line_size
c_func
(paren
)paren
op_minus
l_int|1
)paren
)paren
)paren
(brace
r_union
id|mips_instruction
id|mi
suffix:semicolon
id|mi.i_format.opcode
op_assign
id|pref_op
suffix:semicolon
id|mi.i_format.rs
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* $a0 */
id|mi.i_format.rt
op_assign
id|pref_dst_mode
suffix:semicolon
id|mi.i_format.simmediate
op_assign
id|store_offset
op_plus
id|advance
suffix:semicolon
id|emit_instruction
c_func
(paren
id|mi
)paren
suffix:semicolon
)brace
)brace
DECL|function|build_cdex_s
r_static
r_inline
r_void
id|build_cdex_s
c_func
(paren
r_void
)paren
(brace
r_union
id|mips_instruction
id|mi
suffix:semicolon
r_if
c_cond
(paren
(paren
id|store_offset
op_amp
(paren
id|cpu_scache_line_size
c_func
(paren
)paren
op_minus
l_int|1
)paren
)paren
)paren
r_return
suffix:semicolon
id|mi.c_format.opcode
op_assign
id|cache_op
suffix:semicolon
id|mi.c_format.rs
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* $a0 */
id|mi.c_format.c_op
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* Create Dirty Exclusive */
id|mi.c_format.cache
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* Secondary Data Cache */
id|mi.c_format.simmediate
op_assign
id|store_offset
suffix:semicolon
id|emit_instruction
c_func
(paren
id|mi
)paren
suffix:semicolon
)brace
DECL|function|build_cdex_p
r_static
r_inline
r_void
id|build_cdex_p
c_func
(paren
r_void
)paren
(brace
r_union
id|mips_instruction
id|mi
suffix:semicolon
r_if
c_cond
(paren
id|store_offset
op_amp
(paren
id|cpu_dcache_line_size
c_func
(paren
)paren
op_minus
l_int|1
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|R4600_V1_HIT_CACHEOP_WAR
op_logical_and
(paren
(paren
id|read_c0_prid
c_func
(paren
)paren
op_amp
l_int|0xfff0
)paren
op_eq
l_int|0x2010
)paren
)paren
(brace
id|build_nop
c_func
(paren
)paren
suffix:semicolon
id|build_nop
c_func
(paren
)paren
suffix:semicolon
id|build_nop
c_func
(paren
)paren
suffix:semicolon
id|build_nop
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|R4600_V2_HIT_CACHEOP_WAR
op_logical_and
(paren
(paren
id|read_c0_prid
c_func
(paren
)paren
op_amp
l_int|0xfff0
)paren
op_eq
l_int|0x2020
)paren
)paren
id|build_insn_word
c_func
(paren
l_int|0x8c200000
)paren
suffix:semicolon
multiline_comment|/* lw      $zero, ($at) */
id|mi.c_format.opcode
op_assign
id|cache_op
suffix:semicolon
id|mi.c_format.rs
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* $a0 */
id|mi.c_format.c_op
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* Create Dirty Exclusive */
id|mi.c_format.cache
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Data Cache */
id|mi.c_format.simmediate
op_assign
id|store_offset
suffix:semicolon
id|emit_instruction
c_func
(paren
id|mi
)paren
suffix:semicolon
)brace
DECL|function|__build_store_reg
r_static
r_void
id|__init
id|__build_store_reg
c_func
(paren
r_int
id|reg
)paren
(brace
r_union
id|mips_instruction
id|mi
suffix:semicolon
r_int
r_int
id|width
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_64bit_gp_regs
op_logical_or
(paren
id|cpu_has_64bit_zero_reg
op_logical_and
id|reg
op_eq
l_int|0
)paren
)paren
(brace
id|mi.i_format.opcode
op_assign
id|sd_op
suffix:semicolon
id|width
op_assign
l_int|8
suffix:semicolon
)brace
r_else
(brace
id|mi.i_format.opcode
op_assign
id|sw_op
suffix:semicolon
id|width
op_assign
l_int|4
suffix:semicolon
)brace
id|mi.i_format.rs
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* $a0 */
id|mi.i_format.rt
op_assign
id|reg
suffix:semicolon
multiline_comment|/* $reg */
id|mi.i_format.simmediate
op_assign
id|store_offset
suffix:semicolon
id|store_offset
op_add_assign
id|width
suffix:semicolon
id|emit_instruction
c_func
(paren
id|mi
)paren
suffix:semicolon
)brace
DECL|function|build_store_reg
r_static
r_inline
r_void
id|build_store_reg
c_func
(paren
r_int
id|reg
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_prefetch
)paren
r_if
c_cond
(paren
id|reg
)paren
id|build_dst_pref
c_func
(paren
id|pref_offset_copy
)paren
suffix:semicolon
r_else
id|build_dst_pref
c_func
(paren
id|pref_offset_clear
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cpu_has_cache_cdex_s
)paren
id|build_cdex_s
c_func
(paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cpu_has_cache_cdex_p
)paren
id|build_cdex_p
c_func
(paren
)paren
suffix:semicolon
id|__build_store_reg
c_func
(paren
id|reg
)paren
suffix:semicolon
)brace
DECL|function|build_addiu_a2_a0
r_static
r_inline
r_void
id|build_addiu_a2_a0
c_func
(paren
r_int
r_int
id|offset
)paren
(brace
r_union
id|mips_instruction
id|mi
suffix:semicolon
id|BUG_ON
c_func
(paren
id|offset
OG
l_int|0x7fff
)paren
suffix:semicolon
id|mi.i_format.opcode
op_assign
id|cpu_has_64bit_gp_regs
ques
c_cond
id|daddiu_op
suffix:colon
id|addiu_op
suffix:semicolon
id|mi.i_format.rs
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* $a0 */
id|mi.i_format.rt
op_assign
l_int|6
suffix:semicolon
multiline_comment|/* $a2 */
id|mi.i_format.simmediate
op_assign
id|offset
suffix:semicolon
id|emit_instruction
c_func
(paren
id|mi
)paren
suffix:semicolon
)brace
DECL|function|build_addiu_a1
r_static
r_inline
r_void
id|build_addiu_a1
c_func
(paren
r_int
r_int
id|offset
)paren
(brace
r_union
id|mips_instruction
id|mi
suffix:semicolon
id|BUG_ON
c_func
(paren
id|offset
OG
l_int|0x7fff
)paren
suffix:semicolon
id|mi.i_format.opcode
op_assign
id|cpu_has_64bit_gp_regs
ques
c_cond
id|daddiu_op
suffix:colon
id|addiu_op
suffix:semicolon
id|mi.i_format.rs
op_assign
l_int|5
suffix:semicolon
multiline_comment|/* $a1 */
id|mi.i_format.rt
op_assign
l_int|5
suffix:semicolon
multiline_comment|/* $a1 */
id|mi.i_format.simmediate
op_assign
id|offset
suffix:semicolon
id|load_offset
op_sub_assign
id|offset
suffix:semicolon
id|emit_instruction
c_func
(paren
id|mi
)paren
suffix:semicolon
)brace
DECL|function|build_addiu_a0
r_static
r_inline
r_void
id|build_addiu_a0
c_func
(paren
r_int
r_int
id|offset
)paren
(brace
r_union
id|mips_instruction
id|mi
suffix:semicolon
id|BUG_ON
c_func
(paren
id|offset
OG
l_int|0x7fff
)paren
suffix:semicolon
id|mi.i_format.opcode
op_assign
id|cpu_has_64bit_gp_regs
ques
c_cond
id|daddiu_op
suffix:colon
id|addiu_op
suffix:semicolon
id|mi.i_format.rs
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* $a0 */
id|mi.i_format.rt
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* $a0 */
id|mi.i_format.simmediate
op_assign
id|offset
suffix:semicolon
id|store_offset
op_sub_assign
id|offset
suffix:semicolon
id|emit_instruction
c_func
(paren
id|mi
)paren
suffix:semicolon
)brace
DECL|function|build_bne
r_static
r_inline
r_void
id|build_bne
c_func
(paren
r_int
r_int
op_star
id|dest
)paren
(brace
r_union
id|mips_instruction
id|mi
suffix:semicolon
id|mi.i_format.opcode
op_assign
id|bne_op
suffix:semicolon
id|mi.i_format.rs
op_assign
l_int|6
suffix:semicolon
multiline_comment|/* $a2 */
id|mi.i_format.rt
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* $a0 */
id|mi.i_format.simmediate
op_assign
id|dest
op_minus
id|epc
op_minus
l_int|1
suffix:semicolon
op_star
id|epc
op_increment
op_assign
id|mi.word
suffix:semicolon
id|flush_delay_slot_or_nop
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|build_jr_ra
r_static
r_inline
r_void
id|build_jr_ra
c_func
(paren
r_void
)paren
(brace
r_union
id|mips_instruction
id|mi
suffix:semicolon
id|mi.r_format.opcode
op_assign
id|spec_op
suffix:semicolon
id|mi.r_format.rs
op_assign
l_int|31
suffix:semicolon
id|mi.r_format.rt
op_assign
l_int|0
suffix:semicolon
id|mi.r_format.rd
op_assign
l_int|0
suffix:semicolon
id|mi.r_format.re
op_assign
l_int|0
suffix:semicolon
id|mi.r_format.func
op_assign
id|jr_op
suffix:semicolon
op_star
id|epc
op_increment
op_assign
id|mi.word
suffix:semicolon
id|flush_delay_slot_or_nop
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|build_clear_page
r_void
id|__init
id|build_clear_page
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|loop_start
suffix:semicolon
id|epc
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|clear_page_array
suffix:semicolon
id|instruction_pending
op_assign
l_int|0
suffix:semicolon
id|store_offset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_prefetch
)paren
(brace
r_switch
c_cond
(paren
id|current_cpu_data.cputype
)paren
(brace
r_case
id|CPU_RM9000
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * As a workaround for erratum G105 which make the&n;&t;&t;&t; * PrepareForStore hint unusable we fall back to&n;&t;&t;&t; * StoreRetained on the RM9000.  Once it is known which&n;&t;&t;&t; * versions of the RM9000 we&squot;ll be able to condition-&n;&t;&t;&t; * alize this.&n;&t;&t;&t; */
r_case
id|CPU_R10000
suffix:colon
r_case
id|CPU_R12000
suffix:colon
id|pref_src_mode
op_assign
id|Pref_LoadStreamed
suffix:semicolon
id|pref_dst_mode
op_assign
id|Pref_StoreStreamed
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|pref_src_mode
op_assign
id|Pref_LoadStreamed
suffix:semicolon
id|pref_dst_mode
op_assign
id|Pref_PrepareForStore
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|build_addiu_a2_a0
c_func
(paren
id|PAGE_SIZE
op_minus
(paren
id|cpu_has_prefetch
ques
c_cond
id|pref_offset_clear
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|R4600_V2_HIT_CACHEOP_WAR
op_logical_and
(paren
(paren
id|read_c0_prid
c_func
(paren
)paren
op_amp
l_int|0xfff0
)paren
op_eq
l_int|0x2020
)paren
)paren
id|build_insn_word
c_func
(paren
l_int|0x3c01a000
)paren
suffix:semicolon
multiline_comment|/* lui     $at, 0xa000  */
id|dest
op_assign
id|label
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
id|build_store_reg
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|build_store_reg
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|build_store_reg
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|build_store_reg
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|store_offset
OL
id|half_scache_line_size
c_func
(paren
)paren
)paren
suffix:semicolon
id|build_addiu_a0
c_func
(paren
l_int|2
op_star
id|store_offset
)paren
suffix:semicolon
id|loop_start
op_assign
id|store_offset
suffix:semicolon
r_do
(brace
id|build_store_reg
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|build_store_reg
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|build_store_reg
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|build_store_reg
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|store_offset
op_minus
id|loop_start
)paren
OL
id|half_scache_line_size
c_func
(paren
)paren
)paren
suffix:semicolon
id|build_bne
c_func
(paren
id|dest
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_prefetch
op_logical_and
id|pref_offset_clear
)paren
(brace
id|build_addiu_a2_a0
c_func
(paren
id|pref_offset_clear
)paren
suffix:semicolon
id|dest
op_assign
id|label
c_func
(paren
)paren
suffix:semicolon
id|loop_start
op_assign
id|store_offset
suffix:semicolon
r_do
(brace
id|__build_store_reg
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|__build_store_reg
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|__build_store_reg
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|__build_store_reg
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|store_offset
op_minus
id|loop_start
)paren
OL
id|half_scache_line_size
c_func
(paren
)paren
)paren
suffix:semicolon
id|build_addiu_a0
c_func
(paren
l_int|2
op_star
id|store_offset
)paren
suffix:semicolon
id|loop_start
op_assign
id|store_offset
suffix:semicolon
r_do
(brace
id|__build_store_reg
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|__build_store_reg
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|__build_store_reg
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|__build_store_reg
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|store_offset
op_minus
id|loop_start
)paren
OL
id|half_scache_line_size
c_func
(paren
)paren
)paren
suffix:semicolon
id|build_bne
c_func
(paren
id|dest
)paren
suffix:semicolon
)brace
id|build_jr_ra
c_func
(paren
)paren
suffix:semicolon
id|flush_icache_range
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|clear_page_array
comma
(paren
r_int
r_int
)paren
id|epc
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|epc
OG
id|clear_page_array
op_plus
id|ARRAY_SIZE
c_func
(paren
id|clear_page_array
)paren
)paren
suffix:semicolon
)brace
DECL|function|build_copy_page
r_void
id|__init
id|build_copy_page
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|loop_start
suffix:semicolon
id|epc
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|copy_page_array
suffix:semicolon
id|store_offset
op_assign
id|load_offset
op_assign
l_int|0
suffix:semicolon
id|instruction_pending
op_assign
l_int|0
suffix:semicolon
id|build_addiu_a2_a0
c_func
(paren
id|PAGE_SIZE
op_minus
(paren
id|cpu_has_prefetch
ques
c_cond
id|pref_offset_copy
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|R4600_V2_HIT_CACHEOP_WAR
op_logical_and
(paren
(paren
id|read_c0_prid
c_func
(paren
)paren
op_amp
l_int|0xfff0
)paren
op_eq
l_int|0x2020
)paren
)paren
id|build_insn_word
c_func
(paren
l_int|0x3c01a000
)paren
suffix:semicolon
multiline_comment|/* lui     $at, 0xa000  */
id|dest
op_assign
id|label
c_func
(paren
)paren
suffix:semicolon
id|loop_start
op_assign
id|store_offset
suffix:semicolon
r_do
(brace
id|build_load_reg
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|build_load_reg
c_func
(paren
l_int|9
)paren
suffix:semicolon
id|build_load_reg
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|build_load_reg
c_func
(paren
l_int|11
)paren
suffix:semicolon
id|build_store_reg
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|build_store_reg
c_func
(paren
l_int|9
)paren
suffix:semicolon
id|build_store_reg
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|build_store_reg
c_func
(paren
l_int|11
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|store_offset
op_minus
id|loop_start
)paren
OL
id|half_scache_line_size
c_func
(paren
)paren
)paren
suffix:semicolon
id|build_addiu_a0
c_func
(paren
l_int|2
op_star
id|store_offset
)paren
suffix:semicolon
id|build_addiu_a1
c_func
(paren
l_int|2
op_star
id|load_offset
)paren
suffix:semicolon
id|loop_start
op_assign
id|store_offset
suffix:semicolon
r_do
(brace
id|build_load_reg
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|build_load_reg
c_func
(paren
l_int|9
)paren
suffix:semicolon
id|build_load_reg
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|build_load_reg
c_func
(paren
l_int|11
)paren
suffix:semicolon
id|build_store_reg
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|build_store_reg
c_func
(paren
l_int|9
)paren
suffix:semicolon
id|build_store_reg
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|build_store_reg
c_func
(paren
l_int|11
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|store_offset
op_minus
id|loop_start
)paren
OL
id|half_scache_line_size
c_func
(paren
)paren
)paren
suffix:semicolon
id|build_bne
c_func
(paren
id|dest
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_prefetch
op_logical_and
id|pref_offset_copy
)paren
(brace
id|build_addiu_a2_a0
c_func
(paren
id|pref_offset_copy
)paren
suffix:semicolon
id|dest
op_assign
id|label
c_func
(paren
)paren
suffix:semicolon
id|loop_start
op_assign
id|store_offset
suffix:semicolon
r_do
(brace
id|__build_load_reg
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|__build_load_reg
c_func
(paren
l_int|9
)paren
suffix:semicolon
id|__build_load_reg
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|__build_load_reg
c_func
(paren
l_int|11
)paren
suffix:semicolon
id|__build_store_reg
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|__build_store_reg
c_func
(paren
l_int|9
)paren
suffix:semicolon
id|__build_store_reg
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|__build_store_reg
c_func
(paren
l_int|11
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|store_offset
op_minus
id|loop_start
)paren
OL
id|half_scache_line_size
c_func
(paren
)paren
)paren
suffix:semicolon
id|build_addiu_a0
c_func
(paren
l_int|2
op_star
id|store_offset
)paren
suffix:semicolon
id|build_addiu_a1
c_func
(paren
l_int|2
op_star
id|load_offset
)paren
suffix:semicolon
id|loop_start
op_assign
id|store_offset
suffix:semicolon
r_do
(brace
id|__build_load_reg
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|__build_load_reg
c_func
(paren
l_int|9
)paren
suffix:semicolon
id|__build_load_reg
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|__build_load_reg
c_func
(paren
l_int|11
)paren
suffix:semicolon
id|__build_store_reg
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|__build_store_reg
c_func
(paren
l_int|9
)paren
suffix:semicolon
id|__build_store_reg
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|__build_store_reg
c_func
(paren
l_int|11
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|store_offset
op_minus
id|loop_start
)paren
OL
id|half_scache_line_size
c_func
(paren
)paren
)paren
suffix:semicolon
id|build_bne
c_func
(paren
id|dest
)paren
suffix:semicolon
)brace
id|build_jr_ra
c_func
(paren
)paren
suffix:semicolon
id|flush_icache_range
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|copy_page_array
comma
(paren
r_int
r_int
)paren
id|epc
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|epc
OG
id|copy_page_array
op_plus
id|ARRAY_SIZE
c_func
(paren
id|copy_page_array
)paren
)paren
suffix:semicolon
)brace
eof
