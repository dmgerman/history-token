multiline_comment|/*&n; * pSeries_lpar.c&n; * Copyright (C) 2001 Todd Inglett, IBM Corporation&n; *&n; * pSeries LPAR support.&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/abs_addr.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/pci_dma.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/hvcall.h&gt;
DECL|function|plpar_pte_enter
r_int
id|plpar_pte_enter
c_func
(paren
r_int
r_int
id|flags
comma
r_int
r_int
id|ptex
comma
r_int
r_int
id|new_pteh
comma
r_int
r_int
id|new_ptel
comma
r_int
r_int
op_star
id|old_pteh_ret
comma
r_int
r_int
op_star
id|old_ptel_ret
)paren
(brace
r_int
r_int
id|dummy
comma
id|ret
suffix:semicolon
id|ret
op_assign
id|plpar_hcall
c_func
(paren
id|H_ENTER
comma
id|flags
comma
id|ptex
comma
id|new_pteh
comma
id|new_ptel
comma
id|old_pteh_ret
comma
id|old_ptel_ret
comma
op_amp
id|dummy
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|plpar_pte_remove
r_int
id|plpar_pte_remove
c_func
(paren
r_int
r_int
id|flags
comma
r_int
r_int
id|ptex
comma
r_int
r_int
id|avpn
comma
r_int
r_int
op_star
id|old_pteh_ret
comma
r_int
r_int
op_star
id|old_ptel_ret
)paren
(brace
r_int
r_int
id|dummy
suffix:semicolon
r_return
id|plpar_hcall
c_func
(paren
id|H_REMOVE
comma
id|flags
comma
id|ptex
comma
id|avpn
comma
l_int|0
comma
id|old_pteh_ret
comma
id|old_ptel_ret
comma
op_amp
id|dummy
)paren
suffix:semicolon
)brace
DECL|function|plpar_pte_read
r_int
id|plpar_pte_read
c_func
(paren
r_int
r_int
id|flags
comma
r_int
r_int
id|ptex
comma
r_int
r_int
op_star
id|old_pteh_ret
comma
r_int
r_int
op_star
id|old_ptel_ret
)paren
(brace
r_int
r_int
id|dummy
suffix:semicolon
r_return
id|plpar_hcall
c_func
(paren
id|H_READ
comma
id|flags
comma
id|ptex
comma
l_int|0
comma
l_int|0
comma
id|old_pteh_ret
comma
id|old_ptel_ret
comma
op_amp
id|dummy
)paren
suffix:semicolon
)brace
DECL|function|plpar_pte_protect
r_int
id|plpar_pte_protect
c_func
(paren
r_int
r_int
id|flags
comma
r_int
r_int
id|ptex
comma
r_int
r_int
id|avpn
)paren
(brace
r_return
id|plpar_hcall_norets
c_func
(paren
id|H_PROTECT
comma
id|flags
comma
id|ptex
comma
id|avpn
)paren
suffix:semicolon
)brace
DECL|function|plpar_tce_get
r_int
id|plpar_tce_get
c_func
(paren
r_int
r_int
id|liobn
comma
r_int
r_int
id|ioba
comma
r_int
r_int
op_star
id|tce_ret
)paren
(brace
r_int
r_int
id|dummy
suffix:semicolon
r_return
id|plpar_hcall
c_func
(paren
id|H_GET_TCE
comma
id|liobn
comma
id|ioba
comma
l_int|0
comma
l_int|0
comma
id|tce_ret
comma
op_amp
id|dummy
comma
op_amp
id|dummy
)paren
suffix:semicolon
)brace
DECL|function|plpar_tce_put
r_int
id|plpar_tce_put
c_func
(paren
r_int
r_int
id|liobn
comma
r_int
r_int
id|ioba
comma
r_int
r_int
id|tceval
)paren
(brace
r_return
id|plpar_hcall_norets
c_func
(paren
id|H_PUT_TCE
comma
id|liobn
comma
id|ioba
comma
id|tceval
)paren
suffix:semicolon
)brace
DECL|function|plpar_get_term_char
r_int
id|plpar_get_term_char
c_func
(paren
r_int
r_int
id|termno
comma
r_int
r_int
op_star
id|len_ret
comma
r_char
op_star
id|buf_ret
)paren
(brace
r_int
r_int
op_star
id|lbuf
op_assign
(paren
r_int
r_int
op_star
)paren
id|buf_ret
suffix:semicolon
multiline_comment|/* ToDo: alignment? */
r_return
id|plpar_hcall
c_func
(paren
id|H_GET_TERM_CHAR
comma
id|termno
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|len_ret
comma
id|lbuf
op_plus
l_int|0
comma
id|lbuf
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|plpar_put_term_char
r_int
id|plpar_put_term_char
c_func
(paren
r_int
r_int
id|termno
comma
r_int
r_int
id|len
comma
r_const
r_char
op_star
id|buffer
)paren
(brace
r_int
r_int
id|dummy
suffix:semicolon
r_int
r_int
op_star
id|lbuf
op_assign
(paren
r_int
r_int
op_star
)paren
id|buffer
suffix:semicolon
multiline_comment|/* ToDo: alignment? */
r_return
id|plpar_hcall
c_func
(paren
id|H_PUT_TERM_CHAR
comma
id|termno
comma
id|len
comma
id|lbuf
(braket
l_int|0
)braket
comma
id|lbuf
(braket
l_int|1
)braket
comma
op_amp
id|dummy
comma
op_amp
id|dummy
comma
op_amp
id|dummy
)paren
suffix:semicolon
)brace
DECL|function|plpar_eoi
r_int
id|plpar_eoi
c_func
(paren
r_int
r_int
id|xirr
)paren
(brace
r_return
id|plpar_hcall_norets
c_func
(paren
id|H_EOI
comma
id|xirr
)paren
suffix:semicolon
)brace
DECL|function|plpar_cppr
r_int
id|plpar_cppr
c_func
(paren
r_int
r_int
id|cppr
)paren
(brace
r_return
id|plpar_hcall_norets
c_func
(paren
id|H_CPPR
comma
id|cppr
)paren
suffix:semicolon
)brace
DECL|function|plpar_ipi
r_int
id|plpar_ipi
c_func
(paren
r_int
r_int
id|servernum
comma
r_int
r_int
id|mfrr
)paren
(brace
r_return
id|plpar_hcall_norets
c_func
(paren
id|H_IPI
comma
id|servernum
comma
id|mfrr
)paren
suffix:semicolon
)brace
DECL|function|plpar_xirr
r_int
id|plpar_xirr
c_func
(paren
r_int
r_int
op_star
id|xirr_ret
)paren
(brace
r_int
r_int
id|dummy
suffix:semicolon
r_return
id|plpar_hcall
c_func
(paren
id|H_XIRR
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|xirr_ret
comma
op_amp
id|dummy
comma
op_amp
id|dummy
)paren
suffix:semicolon
)brace
DECL|function|tce_build_pSeriesLP
r_static
r_void
id|tce_build_pSeriesLP
c_func
(paren
r_struct
id|TceTable
op_star
id|tbl
comma
r_int
id|tcenum
comma
r_int
r_int
id|uaddr
comma
r_int
id|direction
)paren
(brace
id|u64
id|set_tce_rc
suffix:semicolon
r_union
id|Tce
id|tce
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_TCE
comma
l_string|&quot;build_tce: uaddr = 0x%lx&bslash;n&quot;
comma
id|uaddr
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_TCE
comma
l_string|&quot;&bslash;ttcenum = 0x%lx, tbl = 0x%lx, index=%lx&bslash;n&quot;
comma
id|tcenum
comma
id|tbl
comma
id|tbl-&gt;index
)paren
suffix:semicolon
id|tce.wholeTce
op_assign
l_int|0
suffix:semicolon
id|tce.tceBits.rpn
op_assign
(paren
id|virt_to_absolute
c_func
(paren
id|uaddr
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|tce.tceBits.readWrite
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_ne
id|PCI_DMA_TODEVICE
)paren
id|tce.tceBits.pciWrite
op_assign
l_int|1
suffix:semicolon
id|set_tce_rc
op_assign
id|plpar_tce_put
c_func
(paren
(paren
id|u64
)paren
id|tbl-&gt;index
comma
(paren
id|u64
)paren
id|tcenum
op_lshift
l_int|12
comma
id|tce.wholeTce
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set_tce_rc
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tce_build_pSeriesLP: plpar_tce_put failed. rc=%ld&bslash;n&quot;
comma
id|set_tce_rc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;tindex   = 0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|tbl-&gt;index
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;ttcenum  = 0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|tcenum
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;ttce val = 0x%lx&bslash;n&quot;
comma
id|tce.wholeTce
)paren
suffix:semicolon
)brace
)brace
DECL|function|tce_free_one_pSeriesLP
r_static
r_void
id|tce_free_one_pSeriesLP
c_func
(paren
r_struct
id|TceTable
op_star
id|tbl
comma
r_int
id|tcenum
)paren
(brace
id|u64
id|set_tce_rc
suffix:semicolon
r_union
id|Tce
id|tce
suffix:semicolon
id|tce.wholeTce
op_assign
l_int|0
suffix:semicolon
id|set_tce_rc
op_assign
id|plpar_tce_put
c_func
(paren
(paren
id|u64
)paren
id|tbl-&gt;index
comma
(paren
id|u64
)paren
id|tcenum
op_lshift
l_int|12
comma
id|tce.wholeTce
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set_tce_rc
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tce_free_one_pSeriesLP: plpar_tce_put failed&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;trc      = %ld&bslash;n&quot;
comma
id|set_tce_rc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;tindex   = 0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|tbl-&gt;index
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;ttcenum  = 0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|tcenum
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;ttce val = 0x%lx&bslash;n&quot;
comma
id|tce.wholeTce
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* PowerPC Interrupts for lpar. */
multiline_comment|/* NOTE: this typedef is duplicated (for now) from xics.c! */
r_typedef
r_struct
(brace
DECL|member|xirr_info_get
r_int
(paren
op_star
id|xirr_info_get
)paren
(paren
r_int
id|cpu
)paren
suffix:semicolon
DECL|member|xirr_info_set
r_void
(paren
op_star
id|xirr_info_set
)paren
(paren
r_int
id|cpu
comma
r_int
id|val
)paren
suffix:semicolon
DECL|member|cppr_info
r_void
(paren
op_star
id|cppr_info
)paren
(paren
r_int
id|cpu
comma
id|u8
id|val
)paren
suffix:semicolon
DECL|member|qirr_info
r_void
(paren
op_star
id|qirr_info
)paren
(paren
r_int
id|cpu
comma
id|u8
id|val
)paren
suffix:semicolon
DECL|typedef|xics_ops
)brace
id|xics_ops
suffix:semicolon
DECL|function|pSeriesLP_xirr_info_get
r_static
r_int
id|pSeriesLP_xirr_info_get
c_func
(paren
r_int
id|n_cpu
)paren
(brace
r_int
r_int
id|lpar_rc
suffix:semicolon
r_int
r_int
id|return_value
suffix:semicolon
id|lpar_rc
op_assign
id|plpar_xirr
c_func
(paren
op_amp
id|return_value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lpar_rc
op_ne
id|H_Success
)paren
(brace
id|panic
c_func
(paren
l_string|&quot; bad return code xirr - rc = %lx &bslash;n&quot;
comma
id|lpar_rc
)paren
suffix:semicolon
)brace
r_return
(paren
(paren
r_int
)paren
(paren
id|return_value
)paren
)paren
suffix:semicolon
)brace
DECL|function|pSeriesLP_xirr_info_set
r_static
r_void
id|pSeriesLP_xirr_info_set
c_func
(paren
r_int
id|n_cpu
comma
r_int
id|value
)paren
(brace
r_int
r_int
id|lpar_rc
suffix:semicolon
r_int
r_int
id|val64
op_assign
id|value
op_amp
l_int|0xffffffff
suffix:semicolon
id|lpar_rc
op_assign
id|plpar_eoi
c_func
(paren
id|val64
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lpar_rc
op_ne
id|H_Success
)paren
(brace
id|panic
c_func
(paren
l_string|&quot; bad return code EOI - rc = %ld, value=%lx &bslash;n&quot;
comma
id|lpar_rc
comma
id|val64
)paren
suffix:semicolon
)brace
)brace
DECL|function|pSeriesLP_cppr_info
r_static
r_void
id|pSeriesLP_cppr_info
c_func
(paren
r_int
id|n_cpu
comma
id|u8
id|value
)paren
(brace
r_int
r_int
id|lpar_rc
suffix:semicolon
id|lpar_rc
op_assign
id|plpar_cppr
c_func
(paren
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lpar_rc
op_ne
id|H_Success
)paren
(brace
id|panic
c_func
(paren
l_string|&quot; bad return code cppr - rc = %lx &bslash;n&quot;
comma
id|lpar_rc
)paren
suffix:semicolon
)brace
)brace
DECL|function|pSeriesLP_qirr_info
r_static
r_void
id|pSeriesLP_qirr_info
c_func
(paren
r_int
id|n_cpu
comma
id|u8
id|value
)paren
(brace
r_int
r_int
id|lpar_rc
suffix:semicolon
id|lpar_rc
op_assign
id|plpar_ipi
c_func
(paren
id|n_cpu
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lpar_rc
op_ne
id|H_Success
)paren
(brace
id|panic
c_func
(paren
l_string|&quot; bad return code qirr -ipi  - rc = %lx &bslash;n&quot;
comma
id|lpar_rc
)paren
suffix:semicolon
)brace
)brace
DECL|variable|pSeriesLP_ops
id|xics_ops
id|pSeriesLP_ops
op_assign
(brace
id|pSeriesLP_xirr_info_get
comma
id|pSeriesLP_xirr_info_set
comma
id|pSeriesLP_cppr_info
comma
id|pSeriesLP_qirr_info
)brace
suffix:semicolon
multiline_comment|/* end TAI-LPAR */
DECL|variable|vtermno
r_int
id|vtermno
suffix:semicolon
multiline_comment|/* virtual terminal# for udbg  */
DECL|function|udbg_putcLP
r_static
r_void
id|udbg_putcLP
c_func
(paren
r_int
r_char
id|c
)paren
(brace
r_char
id|buf
(braket
l_int|16
)braket
suffix:semicolon
r_int
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|udbg_putcLP
c_func
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
id|c
suffix:semicolon
r_do
(brace
id|rc
op_assign
id|plpar_put_term_char
c_func
(paren
id|vtermno
comma
l_int|1
comma
id|buf
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|rc
op_eq
id|H_Busy
)paren
(brace
suffix:semicolon
)brace
)brace
multiline_comment|/* Buffered chars getc */
DECL|variable|inbuflen
r_static
r_int
id|inbuflen
suffix:semicolon
DECL|variable|inbuf
r_static
r_int
id|inbuf
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* must be 2 longs */
DECL|function|udbg_getc_pollLP
r_static
r_int
id|udbg_getc_pollLP
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* The interface is tricky because it may return up to 16 chars.&n;&t; * We save them statically for future calls to udbg_getc().&n;&t; */
r_char
id|ch
comma
op_star
id|buf
op_assign
(paren
r_char
op_star
)paren
id|inbuf
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|inbuflen
op_eq
l_int|0
)paren
(brace
multiline_comment|/* get some more chars. */
id|inbuflen
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
id|plpar_get_term_char
c_func
(paren
id|vtermno
comma
op_amp
id|inbuflen
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|H_Success
)paren
id|inbuflen
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* otherwise inbuflen is garbage */
)brace
r_if
c_cond
(paren
id|inbuflen
op_le
l_int|0
op_logical_or
id|inbuflen
OG
l_int|16
)paren
(brace
multiline_comment|/* Catch error case as well as other oddities (corruption) */
id|inbuflen
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|ch
op_assign
id|buf
(braket
l_int|0
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|inbuflen
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* shuffle them down. */
id|buf
(braket
id|i
op_minus
l_int|1
)braket
op_assign
id|buf
(braket
id|i
)braket
suffix:semicolon
id|inbuflen
op_decrement
suffix:semicolon
r_return
id|ch
suffix:semicolon
)brace
DECL|function|udbg_getcLP
r_static
r_int
r_char
id|udbg_getcLP
c_func
(paren
r_void
)paren
(brace
r_int
id|ch
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|ch
op_assign
id|udbg_getc_pollLP
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
op_minus
l_int|1
)paren
(brace
multiline_comment|/* This shouldn&squot;t be needed...but... */
r_volatile
r_int
r_int
id|delay
suffix:semicolon
r_for
c_loop
(paren
id|delay
op_assign
l_int|0
suffix:semicolon
id|delay
OL
l_int|2000000
suffix:semicolon
id|delay
op_increment
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|ch
suffix:semicolon
)brace
)brace
)brace
r_void
id|pSeries_lpar_mm_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* This is called early in setup.c.&n; * Use it to setup page table ppc_md stuff as well as udbg.&n; */
DECL|function|pSeriesLP_init_early
r_void
id|pSeriesLP_init_early
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|np
suffix:semicolon
id|pSeries_lpar_mm_init
c_func
(paren
)paren
suffix:semicolon
id|ppc_md.tce_build
op_assign
id|tce_build_pSeriesLP
suffix:semicolon
id|ppc_md.tce_free_one
op_assign
id|tce_free_one_pSeriesLP
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|smp_init_pSeries
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|pSeries_pcibios_init_early
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* The keyboard is not useful in the LPAR environment.&n;&t; * Leave all the interfaces NULL.&n;&t; */
multiline_comment|/* lookup the first virtual terminal number in case we don&squot;t have a&n;&t; * com port. Zero is probably correct in case someone calls udbg&n;&t; * before the init. The property is a pair of numbers.  The first&n;&t; * is the starting termno (the one we use) and the second is the&n;&t; * number of terminals.&n;&t; */
id|np
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/rtas&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
)paren
(brace
id|u32
op_star
id|termno
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;ibm,termno&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|termno
)paren
id|vtermno
op_assign
id|termno
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|ppc_md.udbg_putc
op_assign
id|udbg_putcLP
suffix:semicolon
id|ppc_md.udbg_getc
op_assign
id|udbg_getcLP
suffix:semicolon
id|ppc_md.udbg_getc_poll
op_assign
id|udbg_getc_pollLP
suffix:semicolon
)brace
DECL|function|hvc_get_chars
r_int
id|hvc_get_chars
c_func
(paren
r_int
id|index
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|got
suffix:semicolon
r_if
c_cond
(paren
id|plpar_hcall
c_func
(paren
id|H_GET_TERM_CHAR
comma
id|index
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|got
comma
(paren
r_int
r_int
op_star
)paren
id|buf
comma
(paren
r_int
r_int
op_star
)paren
id|buf
op_plus
l_int|1
)paren
op_eq
id|H_Success
)paren
(brace
multiline_comment|/*&n;&t;&t; * Work around a HV bug where it gives us a null&n;&t;&t; * after every &bslash;r.  -- paulus&n;&t;&t; */
r_if
c_cond
(paren
id|got
OG
l_int|0
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|got
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|buf
(braket
id|i
)braket
op_eq
l_int|0
op_logical_and
id|buf
(braket
id|i
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;r&squot;
)paren
(brace
op_decrement
id|got
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|got
)paren
id|memmove
c_func
(paren
op_amp
id|buf
(braket
id|i
)braket
comma
op_amp
id|buf
(braket
id|i
op_plus
l_int|1
)braket
comma
id|got
op_minus
id|i
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
id|got
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hvc_put_chars
r_int
id|hvc_put_chars
c_func
(paren
r_int
id|index
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|dummy
suffix:semicolon
r_int
r_int
op_star
id|lbuf
op_assign
(paren
r_int
r_int
op_star
)paren
id|buf
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|plpar_hcall
c_func
(paren
id|H_PUT_TERM_CHAR
comma
id|index
comma
id|count
comma
id|lbuf
(braket
l_int|0
)braket
comma
id|lbuf
(braket
l_int|1
)braket
comma
op_amp
id|dummy
comma
op_amp
id|dummy
comma
op_amp
id|dummy
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|H_Success
)paren
r_return
id|count
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|H_Busy
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|hvc_count
r_int
id|hvc_count
c_func
(paren
r_int
op_star
id|start_termno
)paren
(brace
id|u32
op_star
id|termno
suffix:semicolon
r_struct
id|device_node
op_star
id|dn
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dn
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/rtas&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
id|termno
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|dn
comma
l_string|&quot;ibm,termno&quot;
comma
l_int|0
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|start_termno
)paren
op_star
id|start_termno
op_assign
id|termno
(braket
l_int|0
)braket
suffix:semicolon
r_return
id|termno
(braket
l_int|1
)braket
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pSeries_lpar_hpte_insert
r_int
id|pSeries_lpar_hpte_insert
c_func
(paren
r_int
r_int
id|hpte_group
comma
r_int
r_int
id|va
comma
r_int
r_int
id|prpn
comma
r_int
id|secondary
comma
r_int
r_int
id|hpteflags
comma
r_int
id|bolted
comma
r_int
id|large
)paren
(brace
r_int
r_int
id|arpn
op_assign
id|physRpn_to_absRpn
c_func
(paren
id|prpn
)paren
suffix:semicolon
r_int
r_int
id|lpar_rc
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|slot
suffix:semicolon
id|HPTE
id|lhpte
suffix:semicolon
multiline_comment|/* Fill in the local HPTE with absolute rpn, avpn and flags */
id|lhpte.dw1.dword1
op_assign
l_int|0
suffix:semicolon
id|lhpte.dw1.dw1.rpn
op_assign
id|arpn
suffix:semicolon
id|lhpte.dw1.flags.flags
op_assign
id|hpteflags
suffix:semicolon
id|lhpte.dw0.dword0
op_assign
l_int|0
suffix:semicolon
id|lhpte.dw0.dw0.avpn
op_assign
id|va
op_rshift
l_int|23
suffix:semicolon
id|lhpte.dw0.dw0.h
op_assign
id|secondary
suffix:semicolon
id|lhpte.dw0.dw0.bolted
op_assign
id|bolted
suffix:semicolon
id|lhpte.dw0.dw0.v
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|large
)paren
(brace
id|lhpte.dw0.dw0.l
op_assign
l_int|1
suffix:semicolon
id|lhpte.dw0.dw0.avpn
op_and_assign
op_complement
l_int|0x1UL
suffix:semicolon
)brace
multiline_comment|/* Now fill in the actual HPTE */
multiline_comment|/* Set CEC cookie to 0         */
multiline_comment|/* Large page = 0              */
multiline_comment|/* Zero page = 0               */
multiline_comment|/* I-cache Invalidate = 0      */
multiline_comment|/* I-cache synchronize = 0     */
multiline_comment|/* Exact = 0                   */
id|flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* XXX why is this here? - Anton */
r_if
c_cond
(paren
id|hpteflags
op_amp
(paren
id|_PAGE_GUARDED
op_or
id|_PAGE_NO_CACHE
)paren
)paren
id|lhpte.dw1.flags.flags
op_and_assign
op_complement
id|_PAGE_COHERENT
suffix:semicolon
id|__asm__
id|__volatile__
(paren
id|H_ENTER_r3
l_string|&quot;mr    4, %2&bslash;n&quot;
l_string|&quot;mr    5, %3&bslash;n&quot;
l_string|&quot;mr    6, %4&bslash;n&quot;
l_string|&quot;mr    7, %5&bslash;n&quot;
id|HSC
l_string|&quot;mr    %0, 3&bslash;n&quot;
l_string|&quot;mr    %1, 4&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|lpar_rc
)paren
comma
l_string|&quot;=r&quot;
(paren
id|slot
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|flags
)paren
comma
l_string|&quot;r&quot;
(paren
id|hpte_group
)paren
comma
l_string|&quot;r&quot;
(paren
id|lhpte.dw0.dword0
)paren
comma
l_string|&quot;r&quot;
(paren
id|lhpte.dw1.dword1
)paren
suffix:colon
l_string|&quot;r3&quot;
comma
l_string|&quot;r4&quot;
comma
l_string|&quot;r5&quot;
comma
l_string|&quot;r6&quot;
comma
l_string|&quot;r7&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lpar_rc
op_eq
id|H_PTEG_Full
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Since we try and ioremap PHBs we don&squot;t own, the pte insert&n;&t; * will fail. However we must catch the failure in hash_page&n;&t; * or we will loop forever, so return -2 in this case.&n;&t; */
r_if
c_cond
(paren
id|lpar_rc
op_ne
id|H_Success
)paren
r_return
op_minus
l_int|2
suffix:semicolon
r_return
id|slot
suffix:semicolon
)brace
DECL|variable|pSeries_lpar_tlbie_lock
r_static
id|spinlock_t
id|pSeries_lpar_tlbie_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|pSeries_lpar_hpte_remove
r_static
r_int
id|pSeries_lpar_hpte_remove
c_func
(paren
r_int
r_int
id|hpte_group
)paren
(brace
r_int
r_int
id|slot_offset
suffix:semicolon
r_int
r_int
id|lpar_rc
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|dummy1
comma
id|dummy2
suffix:semicolon
multiline_comment|/* pick a random slot to start at */
id|slot_offset
op_assign
id|mftb
c_func
(paren
)paren
op_amp
l_int|0x7
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|HPTES_PER_GROUP
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* don&squot;t remove a bolted entry */
id|lpar_rc
op_assign
id|plpar_pte_remove
c_func
(paren
id|H_ANDCOND
comma
id|hpte_group
op_plus
id|slot_offset
comma
(paren
l_int|0x1UL
op_lshift
l_int|4
)paren
comma
op_amp
id|dummy1
comma
op_amp
id|dummy2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lpar_rc
op_eq
id|H_Success
)paren
r_return
id|i
suffix:semicolon
r_if
c_cond
(paren
id|lpar_rc
op_ne
id|H_Not_Found
)paren
id|panic
c_func
(paren
l_string|&quot;Bad return code from pte remove rc = %lx&bslash;n&quot;
comma
id|lpar_rc
)paren
suffix:semicolon
id|slot_offset
op_increment
suffix:semicolon
id|slot_offset
op_and_assign
l_int|0x7
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * NOTE: for updatepp ops we are fortunate that the linux &quot;newpp&quot; bits and&n; * the low 3 bits of flags happen to line up.  So no transform is needed.&n; * We can probably optimize here and assume the high bits of newpp are&n; * already zero.  For now I am paranoid.&n; */
DECL|function|pSeries_lpar_hpte_updatepp
r_static
r_int
id|pSeries_lpar_hpte_updatepp
c_func
(paren
r_int
r_int
id|slot
comma
r_int
r_int
id|newpp
comma
r_int
r_int
id|va
comma
r_int
id|large
comma
r_int
id|local
)paren
(brace
r_int
r_int
id|lpar_rc
suffix:semicolon
r_int
r_int
id|flags
op_assign
(paren
id|newpp
op_amp
l_int|7
)paren
op_or
id|H_AVPN
suffix:semicolon
r_int
r_int
id|avpn
op_assign
id|va
op_rshift
l_int|23
suffix:semicolon
r_if
c_cond
(paren
id|large
)paren
id|avpn
op_and_assign
op_complement
l_int|0x1UL
suffix:semicolon
id|lpar_rc
op_assign
id|plpar_pte_protect
c_func
(paren
id|flags
comma
id|slot
comma
(paren
id|avpn
op_lshift
l_int|7
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lpar_rc
op_eq
id|H_Not_Found
)paren
(brace
id|udbg_printf
c_func
(paren
l_string|&quot;updatepp missed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lpar_rc
op_ne
id|H_Success
)paren
id|panic
c_func
(paren
l_string|&quot;bad return code from pte protect rc = %lx&bslash;n&quot;
comma
id|lpar_rc
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pSeries_lpar_hpte_getword0
r_static
r_int
r_int
id|pSeries_lpar_hpte_getword0
c_func
(paren
r_int
r_int
id|slot
)paren
(brace
r_int
r_int
id|dword0
suffix:semicolon
r_int
r_int
id|lpar_rc
suffix:semicolon
r_int
r_int
id|dummy_word1
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Read 1 pte at a time                        */
multiline_comment|/* Do not need RPN to logical page translation */
multiline_comment|/* No cross CEC PFT access                     */
id|flags
op_assign
l_int|0
suffix:semicolon
id|lpar_rc
op_assign
id|plpar_pte_read
c_func
(paren
id|flags
comma
id|slot
comma
op_amp
id|dword0
comma
op_amp
id|dummy_word1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lpar_rc
op_ne
id|H_Success
)paren
id|panic
c_func
(paren
l_string|&quot;Error on pte read in get_hpte0 rc = %lx&bslash;n&quot;
comma
id|lpar_rc
)paren
suffix:semicolon
r_return
id|dword0
suffix:semicolon
)brace
DECL|function|pSeries_lpar_hpte_find
r_static
r_int
id|pSeries_lpar_hpte_find
c_func
(paren
r_int
r_int
id|vpn
)paren
(brace
r_int
r_int
id|hash
suffix:semicolon
r_int
r_int
id|i
comma
id|j
suffix:semicolon
r_int
id|slot
suffix:semicolon
r_union
(brace
r_int
r_int
id|dword0
suffix:semicolon
id|Hpte_dword0
id|dw0
suffix:semicolon
)brace
id|hpte_dw0
suffix:semicolon
id|Hpte_dword0
id|dw0
suffix:semicolon
id|hash
op_assign
id|hpt_hash
c_func
(paren
id|vpn
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|2
suffix:semicolon
id|j
op_increment
)paren
(brace
id|slot
op_assign
(paren
id|hash
op_amp
id|htab_data.htab_hash_mask
)paren
op_star
id|HPTES_PER_GROUP
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|HPTES_PER_GROUP
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hpte_dw0.dword0
op_assign
id|pSeries_lpar_hpte_getword0
c_func
(paren
id|slot
)paren
suffix:semicolon
id|dw0
op_assign
id|hpte_dw0.dw0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dw0.avpn
op_eq
(paren
id|vpn
op_rshift
l_int|11
)paren
)paren
op_logical_and
id|dw0.v
op_logical_and
(paren
id|dw0.h
op_eq
id|j
)paren
)paren
(brace
multiline_comment|/* HPTE matches */
r_if
c_cond
(paren
id|j
)paren
id|slot
op_assign
op_minus
id|slot
suffix:semicolon
r_return
id|slot
suffix:semicolon
)brace
op_increment
id|slot
suffix:semicolon
)brace
id|hash
op_assign
op_complement
id|hash
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|pSeries_lpar_hpte_updateboltedpp
r_static
r_void
id|pSeries_lpar_hpte_updateboltedpp
c_func
(paren
r_int
r_int
id|newpp
comma
r_int
r_int
id|ea
)paren
(brace
r_int
r_int
id|lpar_rc
suffix:semicolon
r_int
r_int
id|vsid
comma
id|va
comma
id|vpn
comma
id|flags
suffix:semicolon
r_int
id|slot
suffix:semicolon
id|vsid
op_assign
id|get_kernel_vsid
c_func
(paren
id|ea
)paren
suffix:semicolon
id|va
op_assign
(paren
id|vsid
op_lshift
l_int|28
)paren
op_or
(paren
id|ea
op_amp
l_int|0x0fffffff
)paren
suffix:semicolon
id|vpn
op_assign
id|va
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|slot
op_assign
id|pSeries_lpar_hpte_find
c_func
(paren
id|vpn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
op_minus
l_int|1
)paren
id|panic
c_func
(paren
l_string|&quot;updateboltedpp: Could not find page to bolt&bslash;n&quot;
)paren
suffix:semicolon
id|flags
op_assign
id|newpp
op_amp
l_int|3
suffix:semicolon
id|lpar_rc
op_assign
id|plpar_pte_protect
c_func
(paren
id|flags
comma
id|slot
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lpar_rc
op_ne
id|H_Success
)paren
id|panic
c_func
(paren
l_string|&quot;Bad return code from pte bolted protect rc = %lx&bslash;n&quot;
comma
id|lpar_rc
)paren
suffix:semicolon
)brace
DECL|function|pSeries_lpar_hpte_invalidate
r_static
r_void
id|pSeries_lpar_hpte_invalidate
c_func
(paren
r_int
r_int
id|slot
comma
r_int
r_int
id|va
comma
r_int
id|large
comma
r_int
id|local
)paren
(brace
r_int
r_int
id|avpn
op_assign
id|va
op_rshift
l_int|23
suffix:semicolon
r_int
r_int
id|lpar_rc
suffix:semicolon
r_int
r_int
id|dummy1
comma
id|dummy2
suffix:semicolon
r_if
c_cond
(paren
id|large
)paren
id|avpn
op_and_assign
op_complement
l_int|0x1UL
suffix:semicolon
id|lpar_rc
op_assign
id|plpar_pte_remove
c_func
(paren
id|H_AVPN
comma
id|slot
comma
(paren
id|avpn
op_lshift
l_int|7
)paren
comma
op_amp
id|dummy1
comma
op_amp
id|dummy2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lpar_rc
op_eq
id|H_Not_Found
)paren
(brace
id|udbg_printf
c_func
(paren
l_string|&quot;invalidate missed&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lpar_rc
op_ne
id|H_Success
)paren
id|panic
c_func
(paren
l_string|&quot;Bad return code from invalidate rc = %lx&bslash;n&quot;
comma
id|lpar_rc
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Take a spinlock around flushes to avoid bouncing the hypervisor tlbie&n; * lock.&n; */
DECL|function|pSeries_lpar_flush_hash_range
r_void
id|pSeries_lpar_flush_hash_range
c_func
(paren
r_int
r_int
id|context
comma
r_int
r_int
id|number
comma
r_int
id|local
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|ppc64_tlb_batch
op_star
id|batch
op_assign
op_amp
id|ppc64_tlb_batch
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pSeries_lpar_tlbie_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|number
suffix:semicolon
id|i
op_increment
)paren
id|flush_hash_page
c_func
(paren
id|context
comma
id|batch-&gt;addr
(braket
id|i
)braket
comma
id|batch-&gt;pte
(braket
id|i
)braket
comma
id|local
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pSeries_lpar_tlbie_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|pSeries_lpar_mm_init
r_void
id|pSeries_lpar_mm_init
c_func
(paren
r_void
)paren
(brace
id|ppc_md.hpte_invalidate
op_assign
id|pSeries_lpar_hpte_invalidate
suffix:semicolon
id|ppc_md.hpte_updatepp
op_assign
id|pSeries_lpar_hpte_updatepp
suffix:semicolon
id|ppc_md.hpte_updateboltedpp
op_assign
id|pSeries_lpar_hpte_updateboltedpp
suffix:semicolon
id|ppc_md.hpte_insert
op_assign
id|pSeries_lpar_hpte_insert
suffix:semicolon
id|ppc_md.hpte_remove
op_assign
id|pSeries_lpar_hpte_remove
suffix:semicolon
id|ppc_md.flush_hash_range
op_assign
id|pSeries_lpar_flush_hash_range
suffix:semicolon
)brace
eof
