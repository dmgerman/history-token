multiline_comment|/*&n; * Copyright (c) 2001 by David Brownell&n; * &n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY&n; * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; * for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/* this file is part of ehci-hcd.c */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * There&squot;s basically three types of memory:&n; *&t;- data used only by the HCD ... kmalloc is fine&n; *&t;- async and periodic schedules, shared by HC and HCD ... these&n; *&t;  need to use dma_pool or dma_alloc_coherent&n; *&t;- driver buffers, read/written by HC ... single shot DMA mapped &n; *&n; * There&squot;s also PCI &quot;register&quot; data, which is memory mapped.&n; * No memory seen by this driver is pageable.&n; */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* &n; * Allocator / cleanup for the per device structure&n; * Called by hcd init / removal code&n; */
DECL|function|ehci_hcd_alloc
r_static
r_struct
id|usb_hcd
op_star
id|ehci_hcd_alloc
(paren
r_void
)paren
(brace
r_struct
id|ehci_hcd
op_star
id|ehci
suffix:semicolon
id|ehci
op_assign
(paren
r_struct
id|ehci_hcd
op_star
)paren
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|ehci_hcd
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ehci
op_ne
l_int|0
)paren
(brace
id|memset
(paren
id|ehci
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ehci_hcd
)paren
)paren
suffix:semicolon
id|ehci-&gt;hcd.product_desc
op_assign
l_string|&quot;EHCI Host Controller&quot;
suffix:semicolon
r_return
op_amp
id|ehci-&gt;hcd
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|ehci_hcd_free
r_static
r_void
id|ehci_hcd_free
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
id|kfree
(paren
id|hcd_to_ehci
(paren
id|hcd
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* Allocate the key transfer structures from the previously allocated pool */
DECL|function|ehci_qtd_init
r_static
r_inline
r_void
id|ehci_qtd_init
(paren
r_struct
id|ehci_qtd
op_star
id|qtd
comma
id|dma_addr_t
id|dma
)paren
(brace
id|memset
(paren
id|qtd
comma
l_int|0
comma
r_sizeof
op_star
id|qtd
)paren
suffix:semicolon
id|qtd-&gt;qtd_dma
op_assign
id|dma
suffix:semicolon
id|qtd-&gt;hw_token
op_assign
id|cpu_to_le32
(paren
id|QTD_STS_HALT
)paren
suffix:semicolon
id|qtd-&gt;hw_next
op_assign
id|EHCI_LIST_END
suffix:semicolon
id|qtd-&gt;hw_alt_next
op_assign
id|EHCI_LIST_END
suffix:semicolon
id|INIT_LIST_HEAD
(paren
op_amp
id|qtd-&gt;qtd_list
)paren
suffix:semicolon
)brace
DECL|function|ehci_qtd_alloc
r_static
r_struct
id|ehci_qtd
op_star
id|ehci_qtd_alloc
(paren
r_struct
id|ehci_hcd
op_star
id|ehci
comma
r_int
id|flags
)paren
(brace
r_struct
id|ehci_qtd
op_star
id|qtd
suffix:semicolon
id|dma_addr_t
id|dma
suffix:semicolon
id|qtd
op_assign
id|dma_pool_alloc
(paren
id|ehci-&gt;qtd_pool
comma
id|flags
comma
op_amp
id|dma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qtd
op_ne
l_int|0
)paren
(brace
id|ehci_qtd_init
(paren
id|qtd
comma
id|dma
)paren
suffix:semicolon
)brace
r_return
id|qtd
suffix:semicolon
)brace
DECL|function|ehci_qtd_free
r_static
r_inline
r_void
id|ehci_qtd_free
(paren
r_struct
id|ehci_hcd
op_star
id|ehci
comma
r_struct
id|ehci_qtd
op_star
id|qtd
)paren
(brace
id|dma_pool_free
(paren
id|ehci-&gt;qtd_pool
comma
id|qtd
comma
id|qtd-&gt;qtd_dma
)paren
suffix:semicolon
)brace
DECL|function|qh_destroy
r_static
r_void
id|qh_destroy
(paren
r_struct
id|kref
op_star
id|kref
)paren
(brace
r_struct
id|ehci_qh
op_star
id|qh
op_assign
id|container_of
c_func
(paren
id|kref
comma
r_struct
id|ehci_qh
comma
id|kref
)paren
suffix:semicolon
r_struct
id|ehci_hcd
op_star
id|ehci
op_assign
id|qh-&gt;ehci
suffix:semicolon
multiline_comment|/* clean qtds first, and know this is not linked */
r_if
c_cond
(paren
op_logical_neg
id|list_empty
(paren
op_amp
id|qh-&gt;qtd_list
)paren
op_logical_or
id|qh-&gt;qh_next.ptr
)paren
(brace
id|ehci_dbg
(paren
id|ehci
comma
l_string|&quot;unused qh not empty!&bslash;n&quot;
)paren
suffix:semicolon
id|BUG
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|qh-&gt;dummy
)paren
id|ehci_qtd_free
(paren
id|ehci
comma
id|qh-&gt;dummy
)paren
suffix:semicolon
id|usb_put_dev
(paren
id|qh-&gt;dev
)paren
suffix:semicolon
id|dma_pool_free
(paren
id|ehci-&gt;qh_pool
comma
id|qh
comma
id|qh-&gt;qh_dma
)paren
suffix:semicolon
)brace
DECL|function|ehci_qh_alloc
r_static
r_struct
id|ehci_qh
op_star
id|ehci_qh_alloc
(paren
r_struct
id|ehci_hcd
op_star
id|ehci
comma
r_int
id|flags
)paren
(brace
r_struct
id|ehci_qh
op_star
id|qh
suffix:semicolon
id|dma_addr_t
id|dma
suffix:semicolon
id|qh
op_assign
(paren
r_struct
id|ehci_qh
op_star
)paren
id|dma_pool_alloc
(paren
id|ehci-&gt;qh_pool
comma
id|flags
comma
op_amp
id|dma
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|qh
)paren
r_return
id|qh
suffix:semicolon
id|memset
(paren
id|qh
comma
l_int|0
comma
r_sizeof
op_star
id|qh
)paren
suffix:semicolon
id|kref_init
c_func
(paren
op_amp
id|qh-&gt;kref
comma
id|qh_destroy
)paren
suffix:semicolon
id|qh-&gt;ehci
op_assign
id|ehci
suffix:semicolon
id|qh-&gt;qh_dma
op_assign
id|dma
suffix:semicolon
singleline_comment|// INIT_LIST_HEAD (&amp;qh-&gt;qh_list);
id|INIT_LIST_HEAD
(paren
op_amp
id|qh-&gt;qtd_list
)paren
suffix:semicolon
multiline_comment|/* dummy td enables safe urb queuing */
id|qh-&gt;dummy
op_assign
id|ehci_qtd_alloc
(paren
id|ehci
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qh-&gt;dummy
op_eq
l_int|0
)paren
(brace
id|ehci_dbg
(paren
id|ehci
comma
l_string|&quot;no dummy td&bslash;n&quot;
)paren
suffix:semicolon
id|dma_pool_free
(paren
id|ehci-&gt;qh_pool
comma
id|qh
comma
id|qh-&gt;qh_dma
)paren
suffix:semicolon
id|qh
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|qh
suffix:semicolon
)brace
multiline_comment|/* to share a qh (cpu threads, or hc) */
DECL|function|qh_get
r_static
r_inline
r_struct
id|ehci_qh
op_star
id|qh_get
(paren
r_struct
id|ehci_qh
op_star
id|qh
)paren
(brace
id|kref_get
c_func
(paren
op_amp
id|qh-&gt;kref
)paren
suffix:semicolon
r_return
id|qh
suffix:semicolon
)brace
DECL|function|qh_put
r_static
r_inline
r_void
id|qh_put
(paren
r_struct
id|ehci_qh
op_star
id|qh
)paren
(brace
id|kref_put
c_func
(paren
op_amp
id|qh-&gt;kref
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* The queue heads and transfer descriptors are managed from pools tied &n; * to each of the &quot;per device&quot; structures.&n; * This is the initialisation and cleanup code.&n; */
DECL|function|ehci_mem_cleanup
r_static
r_void
id|ehci_mem_cleanup
(paren
r_struct
id|ehci_hcd
op_star
id|ehci
)paren
(brace
r_if
c_cond
(paren
id|ehci-&gt;async
)paren
id|qh_put
(paren
id|ehci-&gt;async
)paren
suffix:semicolon
id|ehci-&gt;async
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* DMA consistent memory and pools */
r_if
c_cond
(paren
id|ehci-&gt;qtd_pool
)paren
id|dma_pool_destroy
(paren
id|ehci-&gt;qtd_pool
)paren
suffix:semicolon
id|ehci-&gt;qtd_pool
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ehci-&gt;qh_pool
)paren
(brace
id|dma_pool_destroy
(paren
id|ehci-&gt;qh_pool
)paren
suffix:semicolon
id|ehci-&gt;qh_pool
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ehci-&gt;itd_pool
)paren
id|dma_pool_destroy
(paren
id|ehci-&gt;itd_pool
)paren
suffix:semicolon
id|ehci-&gt;itd_pool
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ehci-&gt;sitd_pool
)paren
id|dma_pool_destroy
(paren
id|ehci-&gt;sitd_pool
)paren
suffix:semicolon
id|ehci-&gt;sitd_pool
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ehci-&gt;periodic
)paren
id|dma_free_coherent
(paren
id|ehci-&gt;hcd.self.controller
comma
id|ehci-&gt;periodic_size
op_star
r_sizeof
(paren
id|u32
)paren
comma
id|ehci-&gt;periodic
comma
id|ehci-&gt;periodic_dma
)paren
suffix:semicolon
id|ehci-&gt;periodic
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* shadow periodic table */
r_if
c_cond
(paren
id|ehci-&gt;pshadow
)paren
id|kfree
(paren
id|ehci-&gt;pshadow
)paren
suffix:semicolon
id|ehci-&gt;pshadow
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* remember to add cleanup code (above) if you add anything here */
DECL|function|ehci_mem_init
r_static
r_int
id|ehci_mem_init
(paren
r_struct
id|ehci_hcd
op_star
id|ehci
comma
r_int
id|flags
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* QTDs for control/bulk/intr transfers */
id|ehci-&gt;qtd_pool
op_assign
id|dma_pool_create
(paren
l_string|&quot;ehci_qtd&quot;
comma
id|ehci-&gt;hcd.self.controller
comma
r_sizeof
(paren
r_struct
id|ehci_qtd
)paren
comma
l_int|32
multiline_comment|/* byte alignment (for hw parts) */
comma
l_int|4096
multiline_comment|/* can&squot;t cross 4K */
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ehci-&gt;qtd_pool
)paren
(brace
r_goto
id|fail
suffix:semicolon
)brace
multiline_comment|/* QHs for control/bulk/intr transfers */
id|ehci-&gt;qh_pool
op_assign
id|dma_pool_create
(paren
l_string|&quot;ehci_qh&quot;
comma
id|ehci-&gt;hcd.self.controller
comma
r_sizeof
(paren
r_struct
id|ehci_qh
)paren
comma
l_int|32
multiline_comment|/* byte alignment (for hw parts) */
comma
l_int|4096
multiline_comment|/* can&squot;t cross 4K */
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ehci-&gt;qh_pool
)paren
(brace
r_goto
id|fail
suffix:semicolon
)brace
id|ehci-&gt;async
op_assign
id|ehci_qh_alloc
(paren
id|ehci
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ehci-&gt;async
)paren
(brace
r_goto
id|fail
suffix:semicolon
)brace
multiline_comment|/* ITD for high speed ISO transfers */
id|ehci-&gt;itd_pool
op_assign
id|dma_pool_create
(paren
l_string|&quot;ehci_itd&quot;
comma
id|ehci-&gt;hcd.self.controller
comma
r_sizeof
(paren
r_struct
id|ehci_itd
)paren
comma
l_int|32
multiline_comment|/* byte alignment (for hw parts) */
comma
l_int|4096
multiline_comment|/* can&squot;t cross 4K */
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ehci-&gt;itd_pool
)paren
(brace
r_goto
id|fail
suffix:semicolon
)brace
multiline_comment|/* SITD for full/low speed split ISO transfers */
id|ehci-&gt;sitd_pool
op_assign
id|dma_pool_create
(paren
l_string|&quot;ehci_sitd&quot;
comma
id|ehci-&gt;hcd.self.controller
comma
r_sizeof
(paren
r_struct
id|ehci_sitd
)paren
comma
l_int|32
multiline_comment|/* byte alignment (for hw parts) */
comma
l_int|4096
multiline_comment|/* can&squot;t cross 4K */
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ehci-&gt;sitd_pool
)paren
(brace
r_goto
id|fail
suffix:semicolon
)brace
multiline_comment|/* Hardware periodic table */
id|ehci-&gt;periodic
op_assign
(paren
id|u32
op_star
)paren
id|dma_alloc_coherent
(paren
id|ehci-&gt;hcd.self.controller
comma
id|ehci-&gt;periodic_size
op_star
r_sizeof
(paren
id|u32
)paren
comma
op_amp
id|ehci-&gt;periodic_dma
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ehci-&gt;periodic
op_eq
l_int|0
)paren
(brace
r_goto
id|fail
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ehci-&gt;periodic_size
suffix:semicolon
id|i
op_increment
)paren
id|ehci-&gt;periodic
(braket
id|i
)braket
op_assign
id|EHCI_LIST_END
suffix:semicolon
multiline_comment|/* software shadow of hardware table */
id|ehci-&gt;pshadow
op_assign
id|kmalloc
(paren
id|ehci-&gt;periodic_size
op_star
r_sizeof
(paren
r_void
op_star
)paren
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ehci-&gt;pshadow
op_eq
l_int|0
)paren
(brace
r_goto
id|fail
suffix:semicolon
)brace
id|memset
(paren
id|ehci-&gt;pshadow
comma
l_int|0
comma
id|ehci-&gt;periodic_size
op_star
r_sizeof
(paren
r_void
op_star
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|ehci_dbg
(paren
id|ehci
comma
l_string|&quot;couldn&squot;t init memory&bslash;n&quot;
)paren
suffix:semicolon
id|ehci_mem_cleanup
(paren
id|ehci
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
eof
