multiline_comment|/* $Id: cache.c,v 1.4 2000/01/25 00:11:38 prumpf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999 Helge Deller (07-13-1999)&n; * Copyright (C) 1999 SuSE GmbH Nuernberg&n; * Copyright (C) 2000 Philipp Rumpf (prumpf@tux.org)&n; *&n; * Cache and TLB management&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/pdc.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
DECL|variable|split_tlb
r_int
id|split_tlb
suffix:semicolon
DECL|variable|dcache_stride
r_int
id|dcache_stride
suffix:semicolon
DECL|variable|icache_stride
r_int
id|icache_stride
suffix:semicolon
DECL|variable|cache_info
r_struct
id|pdc_cache_info
id|cache_info
suffix:semicolon
macro_line|#ifndef CONFIG_PA20
DECL|variable|btlb_info
r_static
r_struct
id|pdc_btlb_info
id|btlb_info
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
r_void
DECL|function|flush_data_cache
id|flush_data_cache
c_func
(paren
r_void
)paren
(brace
id|on_each_cpu
c_func
(paren
(paren
r_void
(paren
op_star
)paren
(paren
r_void
op_star
)paren
)paren
id|flush_data_cache_local
comma
l_int|NULL
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
r_void
DECL|function|flush_cache_all_local
id|flush_cache_all_local
c_func
(paren
r_void
)paren
(brace
id|flush_instruction_cache_local
c_func
(paren
)paren
suffix:semicolon
id|flush_data_cache_local
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* flushes EVERYTHING (tlb &amp; cache) */
r_void
DECL|function|flush_all_caches
id|flush_all_caches
c_func
(paren
r_void
)paren
(brace
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|update_mmu_cache
id|update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
id|pte_t
id|pte
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|pte_page
c_func
(paren
id|pte
)paren
suffix:semicolon
r_if
c_cond
(paren
id|VALID_PAGE
c_func
(paren
id|page
)paren
op_logical_and
id|page-&gt;mapping
op_logical_and
id|test_bit
c_func
(paren
id|PG_dcache_dirty
comma
op_amp
id|page-&gt;flags
)paren
)paren
(brace
id|flush_kernel_dcache_page
c_func
(paren
id|page_address
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|PG_dcache_dirty
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|show_cache_info
id|show_cache_info
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;I-cache&bslash;t&bslash;t: %ld KB&bslash;n&quot;
comma
id|cache_info.ic_size
op_div
l_int|1024
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;D-cache&bslash;t&bslash;t: %ld KB (%s)%s&bslash;n&quot;
comma
id|cache_info.dc_size
op_div
l_int|1024
comma
(paren
id|cache_info.dc_conf.cc_wt
ques
c_cond
l_string|&quot;WT&quot;
suffix:colon
l_string|&quot;WB&quot;
)paren
comma
(paren
id|cache_info.dc_conf.cc_sh
ques
c_cond
l_string|&quot; - shared I/D&quot;
suffix:colon
l_string|&quot;&quot;
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;ITLB entries&bslash;t: %ld&bslash;n&quot;
l_string|&quot;DTLB entries&bslash;t: %ld%s&bslash;n&quot;
comma
id|cache_info.it_size
comma
id|cache_info.dt_size
comma
id|cache_info.dt_conf.tc_sh
ques
c_cond
l_string|&quot; - shared with ITLB&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_PA20
multiline_comment|/* BTLB - Block TLB */
r_if
c_cond
(paren
id|btlb_info.max_size
op_eq
l_int|0
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;BTLB&bslash;t&bslash;t: not supported&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;BTLB fixed&bslash;t: max. %d pages, pagesize=%d (%dMB)&bslash;n&quot;
l_string|&quot;BTLB fix-entr.&bslash;t: %d instruction, %d data (%d combined)&bslash;n&quot;
l_string|&quot;BTLB var-entr.&bslash;t: %d instruction, %d data (%d combined)&bslash;n&quot;
comma
id|btlb_info.max_size
comma
(paren
r_int
)paren
l_int|4096
comma
id|btlb_info.max_size
op_rshift
l_int|8
comma
id|btlb_info.fixed_range_info.num_i
comma
id|btlb_info.fixed_range_info.num_d
comma
id|btlb_info.fixed_range_info.num_comb
comma
id|btlb_info.variable_range_info.num_i
comma
id|btlb_info.variable_range_info.num_d
comma
id|btlb_info.variable_range_info.num_comb
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_void
id|__init
DECL|function|parisc_cache_init
id|parisc_cache_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|pdc_cache_info
c_func
(paren
op_amp
id|cache_info
)paren
OL
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;parisc_cache_init: pdc_cache_info failed&quot;
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ic_size %lx dc_size %lx it_size %lx pdc_cache_info %d*long pdc_cache_cf %d&bslash;n&quot;
comma
id|cache_info.ic_size
comma
id|cache_info.dc_size
comma
id|cache_info.it_size
comma
r_sizeof
(paren
r_struct
id|pdc_cache_info
)paren
op_div
r_sizeof
(paren
r_int
)paren
comma
r_sizeof
(paren
r_struct
id|pdc_cache_cf
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;dc base %x dc stride %x dc count %x dc loop %d&bslash;n&quot;
comma
id|cache_info.dc_base
comma
id|cache_info.dc_stride
comma
id|cache_info.dc_count
comma
id|cache_info.dc_loop
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;dc conf: alias %d block %d line %d wt %d sh %d cst %d assoc %d&bslash;n&quot;
comma
id|cache_info.dc_conf.cc_alias
comma
id|cache_info.dc_conf.cc_block
comma
id|cache_info.dc_conf.cc_line
comma
id|cache_info.dc_conf.cc_wt
comma
id|cache_info.dc_conf.cc_sh
comma
id|cache_info.dc_conf.cc_cst
comma
id|cache_info.dc_conf.cc_assoc
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ic conf: alias %d block %d line %d wt %d sh %d cst %d assoc %d&bslash;n&quot;
comma
id|cache_info.ic_conf.cc_alias
comma
id|cache_info.ic_conf.cc_block
comma
id|cache_info.ic_conf.cc_line
comma
id|cache_info.ic_conf.cc_wt
comma
id|cache_info.ic_conf.cc_sh
comma
id|cache_info.ic_conf.cc_cst
comma
id|cache_info.ic_conf.cc_assoc
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;dt conf: sh %d page %d cst %d aid %d pad1 %d &bslash;n&quot;
comma
id|cache_info.dt_conf.tc_sh
comma
id|cache_info.dt_conf.tc_page
comma
id|cache_info.dt_conf.tc_cst
comma
id|cache_info.dt_conf.tc_aid
comma
id|cache_info.dt_conf.tc_pad1
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;it conf: sh %d page %d cst %d aid %d pad1 %d &bslash;n&quot;
comma
id|cache_info.it_conf.tc_sh
comma
id|cache_info.it_conf.tc_page
comma
id|cache_info.it_conf.tc_cst
comma
id|cache_info.it_conf.tc_aid
comma
id|cache_info.it_conf.tc_pad1
)paren
suffix:semicolon
macro_line|#endif
id|split_tlb
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cache_info.dt_conf.tc_sh
op_eq
l_int|0
op_logical_or
id|cache_info.dt_conf.tc_sh
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|cache_info.dt_conf.tc_sh
op_eq
l_int|2
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Unexpected TLB configuration. &quot;
l_string|&quot;Will flush I/D separately (could be optimized).&bslash;n&quot;
)paren
suffix:semicolon
id|split_tlb
op_assign
l_int|1
suffix:semicolon
)brace
id|dcache_stride
op_assign
(paren
l_int|1
op_lshift
(paren
id|cache_info.dc_conf.cc_block
op_plus
l_int|3
)paren
)paren
op_star
id|cache_info.dc_conf.cc_line
suffix:semicolon
id|icache_stride
op_assign
(paren
l_int|1
op_lshift
(paren
id|cache_info.ic_conf.cc_block
op_plus
l_int|3
)paren
)paren
op_star
id|cache_info.ic_conf.cc_line
suffix:semicolon
macro_line|#ifndef CONFIG_PA20
r_if
c_cond
(paren
id|pdc_btlb_info
c_func
(paren
op_amp
id|btlb_info
)paren
OL
l_int|0
)paren
(brace
id|memset
c_func
(paren
op_amp
id|btlb_info
comma
l_int|0
comma
r_sizeof
id|btlb_info
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
(paren
id|boot_cpu_data.pdc.capabilities
op_amp
id|PDC_MODEL_NVA_MASK
)paren
op_eq
id|PDC_MODEL_NVA_UNSUPPORTED
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Only equivalent aliasing supported&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
id|panic
c_func
(paren
l_string|&quot;SMP kernel required to avoid non-equivalent aliasing&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
DECL|function|disable_sr_hashing
r_void
id|disable_sr_hashing
c_func
(paren
r_void
)paren
(brace
r_int
id|srhash_type
suffix:semicolon
r_switch
c_cond
(paren
id|boot_cpu_data.cpu_type
)paren
(brace
r_case
id|pcx
suffix:colon
multiline_comment|/* We shouldn&squot;t get this far.  setup.c should prevent it. */
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|pcxs
suffix:colon
r_case
id|pcxt
suffix:colon
r_case
id|pcxt_
suffix:colon
id|srhash_type
op_assign
id|SRHASH_PCXST
suffix:semicolon
r_break
suffix:semicolon
r_case
id|pcxl
suffix:colon
id|srhash_type
op_assign
id|SRHASH_PCXL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|pcxl2
suffix:colon
multiline_comment|/* pcxl2 doesn&squot;t support space register hashing */
r_return
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Currently all PA2.0 machines use the same ins. sequence */
id|srhash_type
op_assign
id|SRHASH_PA20
suffix:semicolon
r_break
suffix:semicolon
)brace
id|disable_sr_hashing_asm
c_func
(paren
id|srhash_type
)paren
suffix:semicolon
)brace
DECL|function|__flush_dcache_page
r_void
id|__flush_dcache_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;active_mm
suffix:semicolon
r_struct
id|list_head
op_star
id|l
suffix:semicolon
id|flush_kernel_dcache_page
c_func
(paren
id|page_address
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page-&gt;mapping
)paren
r_return
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
op_amp
id|page-&gt;mapping-&gt;i_mmap_shared
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|mpnt
suffix:semicolon
r_int
r_int
id|off
suffix:semicolon
id|mpnt
op_assign
id|list_entry
c_func
(paren
id|l
comma
r_struct
id|vm_area_struct
comma
id|shared
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If this VMA is not in our MM, we can ignore it.&n;&t;&t; */
r_if
c_cond
(paren
id|mpnt-&gt;vm_mm
op_ne
id|mm
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;index
OL
id|mpnt-&gt;vm_pgoff
)paren
r_continue
suffix:semicolon
id|off
op_assign
id|page-&gt;index
op_minus
id|mpnt-&gt;vm_pgoff
suffix:semicolon
r_if
c_cond
(paren
id|off
op_ge
(paren
id|mpnt-&gt;vm_end
op_minus
id|mpnt-&gt;vm_start
)paren
op_rshift
id|PAGE_SHIFT
)paren
r_continue
suffix:semicolon
id|flush_cache_page
c_func
(paren
id|mpnt
comma
id|mpnt-&gt;vm_start
op_plus
(paren
id|off
op_lshift
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
multiline_comment|/* All user shared mappings should be equivalently mapped,&n;&t;&t; * so once we&squot;ve flushed one we should be ok&n;&t;&t; */
r_break
suffix:semicolon
)brace
)brace
eof
