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
macro_line|#include &lt;asm/iommu.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/hvcall.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/abs_addr.h&gt;
multiline_comment|/* in pSeries_hvCall.S */
DECL|variable|plpar_hcall
id|EXPORT_SYMBOL
c_func
(paren
id|plpar_hcall
)paren
suffix:semicolon
DECL|variable|plpar_hcall_4out
id|EXPORT_SYMBOL
c_func
(paren
id|plpar_hcall_4out
)paren
suffix:semicolon
DECL|variable|plpar_hcall_norets
id|EXPORT_SYMBOL
c_func
(paren
id|plpar_hcall_norets
)paren
suffix:semicolon
DECL|variable|plpar_hcall_8arg_2ret
id|EXPORT_SYMBOL
c_func
(paren
id|plpar_hcall_8arg_2ret
)paren
suffix:semicolon
DECL|function|poll_pending
r_int
id|poll_pending
c_func
(paren
r_void
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
id|H_POLL_PENDING
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
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
DECL|function|prod_processor
r_int
id|prod_processor
c_func
(paren
r_void
)paren
(brace
id|plpar_hcall_norets
c_func
(paren
id|H_PROD
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cede_processor
r_int
id|cede_processor
c_func
(paren
r_void
)paren
(brace
id|plpar_hcall_norets
c_func
(paren
id|H_CEDE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|register_vpa
r_int
id|register_vpa
c_func
(paren
r_int
r_int
id|flags
comma
r_int
r_int
id|proc
comma
r_int
r_int
id|vpa
)paren
(brace
id|plpar_hcall_norets
c_func
(paren
id|H_REGISTER_VPA
comma
id|flags
comma
id|proc
comma
id|vpa
)paren
suffix:semicolon
r_return
l_int|0
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
id|plpar_hcall_norets
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
id|iommu_table
op_star
id|tbl
comma
r_int
id|tcenum
comma
r_int
id|npages
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
id|rc
suffix:semicolon
r_union
id|tce_entry
id|tce
suffix:semicolon
id|tce.te_word
op_assign
l_int|0
suffix:semicolon
id|tce.te_rpn
op_assign
(paren
id|virt_to_abs
c_func
(paren
id|uaddr
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|tce.te_rdwr
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
id|tce.te_pciwr
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|npages
op_decrement
)paren
(brace
id|rc
op_assign
id|plpar_tce_put
c_func
(paren
(paren
id|u64
)paren
id|tbl-&gt;it_index
comma
(paren
id|u64
)paren
id|tcenum
op_lshift
l_int|12
comma
id|tce.te_word
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_logical_and
id|printk_ratelimit
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tce_build_pSeriesLP: plpar_tce_put failed. rc=%ld&bslash;n&quot;
comma
id|rc
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
id|tbl-&gt;it_index
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
id|tce.te_word
)paren
suffix:semicolon
id|show_stack
c_func
(paren
id|current
comma
(paren
r_int
r_int
op_star
)paren
id|__get_SP
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
id|tcenum
op_increment
suffix:semicolon
id|tce.te_rpn
op_increment
suffix:semicolon
)brace
)brace
DECL|function|tce_free_pSeriesLP
r_static
r_void
id|tce_free_pSeriesLP
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_int
id|tcenum
comma
r_int
id|npages
)paren
(brace
id|u64
id|rc
suffix:semicolon
r_union
id|tce_entry
id|tce
suffix:semicolon
id|tce.te_word
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|npages
op_decrement
)paren
(brace
id|rc
op_assign
id|plpar_tce_put
c_func
(paren
(paren
id|u64
)paren
id|tbl-&gt;it_index
comma
(paren
id|u64
)paren
id|tcenum
op_lshift
l_int|12
comma
id|tce.te_word
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_logical_and
id|printk_ratelimit
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tce_free_pSeriesLP: plpar_tce_put failed&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;trc      = %ld&bslash;n&quot;
comma
id|rc
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
id|tbl-&gt;it_index
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
id|tce.te_word
)paren
suffix:semicolon
id|show_stack
c_func
(paren
id|current
comma
(paren
r_int
r_int
op_star
)paren
id|__get_SP
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
id|tcenum
op_increment
suffix:semicolon
)brace
)brace
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
multiline_comment|/* returns 0 if couldn&squot;t find or use /chosen/stdout as console */
DECL|function|find_udbg_vterm
r_static
r_int
id|find_udbg_vterm
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|stdout_node
suffix:semicolon
id|u32
op_star
id|termno
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* find the boot console from /chosen/stdout */
r_if
c_cond
(paren
op_logical_neg
id|of_stdout_device
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;couldn&squot;t get path from /chosen/stdout!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|found
suffix:semicolon
)brace
id|stdout_node
op_assign
id|of_find_node_by_path
c_func
(paren
id|of_stdout_device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stdout_node
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;couldn&squot;t find node from /chosen/stdout&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|found
suffix:semicolon
)brace
multiline_comment|/* now we have the stdout node; figure out what type of device it is. */
id|name
op_assign
(paren
r_char
op_star
)paren
id|get_property
c_func
(paren
id|stdout_node
comma
l_string|&quot;name&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;stdout node missing &squot;name&squot; property!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|name
comma
l_string|&quot;vty&quot;
comma
l_int|3
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|device_is_compatible
c_func
(paren
id|stdout_node
comma
l_string|&quot;hvterm1&quot;
)paren
)paren
(brace
id|termno
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|stdout_node
comma
l_string|&quot;reg&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|termno
)paren
(brace
id|vtermno
op_assign
id|termno
(braket
l_int|0
)braket
suffix:semicolon
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
id|found
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* XXX implement udbg_putcLP_vtty for hvterm-protocol1 case */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s doesn&squot;t speak hvterm1; &quot;
l_string|&quot;can&squot;t print udbg messages&bslash;n&quot;
comma
id|of_stdout_device
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|name
comma
l_string|&quot;serial&quot;
comma
l_int|6
)paren
)paren
(brace
multiline_comment|/* XXX fix ISA serial console */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;serial stdout on LPAR (&squot;%s&squot;)! &quot;
l_string|&quot;can&squot;t print udbg messages&bslash;n&quot;
comma
id|of_stdout_device
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;don&squot;t know how to print to stdout &squot;%s&squot;&bslash;n&quot;
comma
id|of_stdout_device
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|of_node_put
c_func
(paren
id|stdout_node
)paren
suffix:semicolon
r_return
id|found
suffix:semicolon
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
id|pSeries_lpar_mm_init
c_func
(paren
)paren
suffix:semicolon
id|tce_init_pSeries
c_func
(paren
)paren
suffix:semicolon
id|ppc_md.tce_build
op_assign
id|tce_build_pSeriesLP
suffix:semicolon
id|ppc_md.tce_free
op_assign
id|tce_free_pSeriesLP
suffix:semicolon
id|pci_iommu_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|smp_init_pSeries
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* The keyboard is not useful in the LPAR environment.&n;&t; * Leave all the ppc_md keyboard interfaces NULL.&n;&t; */
r_if
c_cond
(paren
l_int|0
op_eq
id|find_udbg_vterm
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;can&squot;t use stdout; can&squot;t print early debug messages.&bslash;n&quot;
)paren
suffix:semicolon
)brace
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
r_int
r_int
id|dummy0
comma
id|dummy1
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
id|lpar_rc
op_assign
id|plpar_hcall
c_func
(paren
id|H_ENTER
comma
id|flags
comma
id|hpte_group
comma
id|lhpte.dw0.dword0
comma
id|lhpte.dw1.dword1
comma
op_amp
id|slot
comma
op_amp
id|dummy0
comma
op_amp
id|dummy1
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
multiline_comment|/* Because of iSeries, we have to pass down the secondary&n;&t; * bucket bit here as well&n;&t; */
r_return
(paren
id|slot
op_amp
l_int|7
)paren
op_or
(paren
id|secondary
op_lshift
l_int|3
)paren
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
r_return
op_minus
l_int|1
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
r_return
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
id|__get_cpu_var
c_func
(paren
id|ppc64_tlb_batch
)paren
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
