multiline_comment|/*&n; * OHCI HCD (Host Controller Driver) for USB.&n; * &n; * (C) Copyright 1999 Roman Weissgaerber &lt;weissg@vienna.at&gt;&n; * (C) Copyright 2000-2002 David Brownell &lt;dbrownell@users.sourceforge.net&gt;&n; * &n; * This file is licenced under the GPL.&n; */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * There&squot;s basically three types of memory:&n; *&t;- data used only by the HCD ... kmalloc is fine&n; *&t;- async and periodic schedules, shared by HC and HCD ... these&n; *&t;  need to use dma_pool or dma_alloc_coherent&n; *&t;- driver buffers, read/written by HC ... the hcd glue or the&n; *&t;  device driver provides us with dma addresses&n; *&n; * There&squot;s also PCI &quot;register&quot; data, which is memory mapped.&n; * No memory seen by this driver is pagable.&n; */
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|ohci_hcd_init
r_static
r_void
id|ohci_hcd_init
(paren
r_struct
id|ohci_hcd
op_star
id|ohci
)paren
(brace
id|ohci-&gt;next_statechange
op_assign
id|jiffies
suffix:semicolon
id|spin_lock_init
(paren
op_amp
id|ohci-&gt;lock
)paren
suffix:semicolon
id|INIT_LIST_HEAD
(paren
op_amp
id|ohci-&gt;pending
)paren
suffix:semicolon
id|INIT_WORK
(paren
op_amp
id|ohci-&gt;rh_resume
comma
id|ohci_rh_resume
comma
id|ohci_to_hcd
c_func
(paren
id|ohci
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|ohci_mem_init
r_static
r_int
id|ohci_mem_init
(paren
r_struct
id|ohci_hcd
op_star
id|ohci
)paren
(brace
id|ohci-&gt;td_cache
op_assign
id|dma_pool_create
(paren
l_string|&quot;ohci_td&quot;
comma
id|ohci_to_hcd
c_func
(paren
id|ohci
)paren
op_member_access_from_pointer
id|self.controller
comma
r_sizeof
(paren
r_struct
id|td
)paren
comma
l_int|32
multiline_comment|/* byte alignment */
comma
l_int|0
multiline_comment|/* no page-crossing issues */
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ohci-&gt;td_cache
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ohci-&gt;ed_cache
op_assign
id|dma_pool_create
(paren
l_string|&quot;ohci_ed&quot;
comma
id|ohci_to_hcd
c_func
(paren
id|ohci
)paren
op_member_access_from_pointer
id|self.controller
comma
r_sizeof
(paren
r_struct
id|ed
)paren
comma
l_int|16
multiline_comment|/* byte alignment */
comma
l_int|0
multiline_comment|/* no page-crossing issues */
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ohci-&gt;ed_cache
)paren
(brace
id|dma_pool_destroy
(paren
id|ohci-&gt;td_cache
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ohci_mem_cleanup
r_static
r_void
id|ohci_mem_cleanup
(paren
r_struct
id|ohci_hcd
op_star
id|ohci
)paren
(brace
r_if
c_cond
(paren
id|ohci-&gt;td_cache
)paren
(brace
id|dma_pool_destroy
(paren
id|ohci-&gt;td_cache
)paren
suffix:semicolon
id|ohci-&gt;td_cache
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ohci-&gt;ed_cache
)paren
(brace
id|dma_pool_destroy
(paren
id|ohci-&gt;ed_cache
)paren
suffix:semicolon
id|ohci-&gt;ed_cache
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* ohci &quot;done list&quot; processing needs this mapping */
r_static
r_inline
r_struct
id|td
op_star
DECL|function|dma_to_td
id|dma_to_td
(paren
r_struct
id|ohci_hcd
op_star
id|hc
comma
id|dma_addr_t
id|td_dma
)paren
(brace
r_struct
id|td
op_star
id|td
suffix:semicolon
id|td_dma
op_and_assign
id|TD_MASK
suffix:semicolon
id|td
op_assign
id|hc-&gt;td_hash
(braket
id|TD_HASH_FUNC
c_func
(paren
id|td_dma
)paren
)braket
suffix:semicolon
r_while
c_loop
(paren
id|td
op_logical_and
id|td-&gt;td_dma
op_ne
id|td_dma
)paren
id|td
op_assign
id|td-&gt;td_hash
suffix:semicolon
r_return
id|td
suffix:semicolon
)brace
multiline_comment|/* TDs ... */
r_static
r_struct
id|td
op_star
DECL|function|td_alloc
id|td_alloc
(paren
r_struct
id|ohci_hcd
op_star
id|hc
comma
r_int
id|mem_flags
)paren
(brace
id|dma_addr_t
id|dma
suffix:semicolon
r_struct
id|td
op_star
id|td
suffix:semicolon
id|td
op_assign
id|dma_pool_alloc
(paren
id|hc-&gt;td_cache
comma
id|mem_flags
comma
op_amp
id|dma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|td
)paren
(brace
multiline_comment|/* in case hc fetches it, make it look dead */
id|memset
(paren
id|td
comma
l_int|0
comma
r_sizeof
op_star
id|td
)paren
suffix:semicolon
id|td-&gt;hwNextTD
op_assign
id|cpu_to_hc32
(paren
id|hc
comma
id|dma
)paren
suffix:semicolon
id|td-&gt;td_dma
op_assign
id|dma
suffix:semicolon
multiline_comment|/* hashed in td_fill */
)brace
r_return
id|td
suffix:semicolon
)brace
r_static
r_void
DECL|function|td_free
id|td_free
(paren
r_struct
id|ohci_hcd
op_star
id|hc
comma
r_struct
id|td
op_star
id|td
)paren
(brace
r_struct
id|td
op_star
op_star
id|prev
op_assign
op_amp
id|hc-&gt;td_hash
(braket
id|TD_HASH_FUNC
(paren
id|td-&gt;td_dma
)paren
)braket
suffix:semicolon
r_while
c_loop
(paren
op_star
id|prev
op_logical_and
op_star
id|prev
op_ne
id|td
)paren
id|prev
op_assign
op_amp
(paren
op_star
id|prev
)paren
op_member_access_from_pointer
id|td_hash
suffix:semicolon
r_if
c_cond
(paren
op_star
id|prev
)paren
op_star
id|prev
op_assign
id|td-&gt;td_hash
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|td-&gt;hwINFO
op_amp
id|cpu_to_hc32
c_func
(paren
id|hc
comma
id|TD_DONE
)paren
)paren
op_ne
l_int|0
)paren
id|ohci_dbg
(paren
id|hc
comma
l_string|&quot;no hash for td %p&bslash;n&quot;
comma
id|td
)paren
suffix:semicolon
id|dma_pool_free
(paren
id|hc-&gt;td_cache
comma
id|td
comma
id|td-&gt;td_dma
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* EDs ... */
r_static
r_struct
id|ed
op_star
DECL|function|ed_alloc
id|ed_alloc
(paren
r_struct
id|ohci_hcd
op_star
id|hc
comma
r_int
id|mem_flags
)paren
(brace
id|dma_addr_t
id|dma
suffix:semicolon
r_struct
id|ed
op_star
id|ed
suffix:semicolon
id|ed
op_assign
id|dma_pool_alloc
(paren
id|hc-&gt;ed_cache
comma
id|mem_flags
comma
op_amp
id|dma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ed
)paren
(brace
id|memset
(paren
id|ed
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ed
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
(paren
op_amp
id|ed-&gt;td_list
)paren
suffix:semicolon
id|ed-&gt;dma
op_assign
id|dma
suffix:semicolon
)brace
r_return
id|ed
suffix:semicolon
)brace
r_static
r_void
DECL|function|ed_free
id|ed_free
(paren
r_struct
id|ohci_hcd
op_star
id|hc
comma
r_struct
id|ed
op_star
id|ed
)paren
(brace
id|dma_pool_free
(paren
id|hc-&gt;ed_cache
comma
id|ed
comma
id|ed-&gt;dma
)paren
suffix:semicolon
)brace
eof
