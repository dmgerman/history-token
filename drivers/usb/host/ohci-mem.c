multiline_comment|/*&n; * OHCI HCD (Host Controller Driver) for USB.&n; * &n; * (C) Copyright 1999 Roman Weissgaerber &lt;weissg@vienna.at&gt;&n; * (C) Copyright 2000-2002 David Brownell &lt;dbrownell@users.sourceforge.net&gt;&n; * &n; * This file is licenced under the GPL.&n; */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * There&squot;s basically three types of memory:&n; *&t;- data used only by the HCD ... kmalloc is fine&n; *&t;- async and periodic schedules, shared by HC and HCD ... these&n; *&t;  need to use pci_pool or pci_alloc_consistent&n; *&t;- driver buffers, read/written by HC ... single shot DMA mapped &n; *&n; * There&squot;s also PCI &quot;register&quot; data, which is memory mapped.&n; * No memory seen by this driver is pagable.&n; */
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|ohci_hcd_alloc
r_static
r_struct
id|usb_hcd
op_star
id|ohci_hcd_alloc
(paren
r_void
)paren
(brace
r_struct
id|ohci_hcd
op_star
id|ohci
suffix:semicolon
id|ohci
op_assign
(paren
r_struct
id|ohci_hcd
op_star
)paren
id|kmalloc
(paren
r_sizeof
op_star
id|ohci
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ohci
op_ne
l_int|0
)paren
(brace
id|memset
(paren
id|ohci
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ohci_hcd
)paren
)paren
suffix:semicolon
r_return
op_amp
id|ohci-&gt;hcd
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ohci_hcd_free
r_static
r_void
id|ohci_hcd_free
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
id|kfree
(paren
id|hcd_to_ohci
(paren
id|hcd
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* Recover a TD/ED using its collision chain */
r_static
r_inline
r_void
op_star
DECL|function|dma_to_ed_td
id|dma_to_ed_td
(paren
r_struct
id|hash_list_t
op_star
id|entry
comma
id|dma_addr_t
id|dma
)paren
(brace
r_struct
id|hash_t
op_star
id|scan
op_assign
id|entry-&gt;head
suffix:semicolon
r_while
c_loop
(paren
id|scan
op_logical_and
id|scan-&gt;dma
op_ne
id|dma
)paren
id|scan
op_assign
id|scan-&gt;next
suffix:semicolon
r_return
id|scan
ques
c_cond
id|scan-&gt;virt
suffix:colon
l_int|0
suffix:semicolon
)brace
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
id|td_dma
op_and_assign
id|TD_MASK
suffix:semicolon
r_return
(paren
r_struct
id|td
op_star
)paren
id|dma_to_ed_td
c_func
(paren
op_amp
(paren
id|hc-&gt;td_hash
(braket
id|TD_HASH_FUNC
c_func
(paren
id|td_dma
)paren
)braket
)paren
comma
id|td_dma
)paren
suffix:semicolon
)brace
singleline_comment|// FIXME:  when updating the hashtables this way, mem_flags is unusable...
multiline_comment|/* Add a hash entry for a TD/ED; return true on success */
r_static
r_inline
r_int
DECL|function|hash_add_ed_td
id|hash_add_ed_td
(paren
r_struct
id|hash_list_t
op_star
id|entry
comma
r_void
op_star
id|virt
comma
id|dma_addr_t
id|dma
comma
r_int
id|mem_flags
)paren
(brace
r_struct
id|hash_t
op_star
id|scan
suffix:semicolon
id|scan
op_assign
(paren
r_struct
id|hash_t
op_star
)paren
id|kmalloc
(paren
r_sizeof
op_star
id|scan
comma
id|mem_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scan
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;tail
)paren
(brace
id|entry-&gt;head
op_assign
id|entry-&gt;tail
op_assign
id|scan
suffix:semicolon
)brace
r_else
(brace
id|entry-&gt;tail-&gt;next
op_assign
id|scan
suffix:semicolon
id|entry-&gt;tail
op_assign
id|scan
suffix:semicolon
)brace
id|scan-&gt;virt
op_assign
id|virt
suffix:semicolon
id|scan-&gt;dma
op_assign
id|dma
suffix:semicolon
id|scan-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|hash_add_td
id|hash_add_td
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
comma
r_int
id|mem_flags
)paren
(brace
r_return
id|hash_add_ed_td
(paren
op_amp
(paren
id|hc-&gt;td_hash
(braket
id|TD_HASH_FUNC
(paren
id|td-&gt;td_dma
)paren
)braket
)paren
comma
id|td
comma
id|td-&gt;td_dma
comma
id|mem_flags
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|hash_free_ed_td
id|hash_free_ed_td
(paren
r_struct
id|hash_list_t
op_star
id|entry
comma
r_void
op_star
id|virt
)paren
(brace
r_struct
id|hash_t
op_star
id|scan
comma
op_star
id|prev
suffix:semicolon
id|scan
op_assign
id|prev
op_assign
id|entry-&gt;head
suffix:semicolon
singleline_comment|// Find and unlink hash entry
r_while
c_loop
(paren
id|scan
op_logical_and
id|scan-&gt;virt
op_ne
id|virt
)paren
(brace
id|prev
op_assign
id|scan
suffix:semicolon
id|scan
op_assign
id|scan-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|scan
)paren
(brace
r_if
c_cond
(paren
id|scan
op_eq
id|entry-&gt;head
)paren
(brace
r_if
c_cond
(paren
id|entry-&gt;head
op_eq
id|entry-&gt;tail
)paren
id|entry-&gt;head
op_assign
id|entry-&gt;tail
op_assign
l_int|NULL
suffix:semicolon
r_else
id|entry-&gt;head
op_assign
id|scan-&gt;next
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|scan
op_eq
id|entry-&gt;tail
)paren
(brace
id|entry-&gt;tail
op_assign
id|prev
suffix:semicolon
id|prev-&gt;next
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
id|prev-&gt;next
op_assign
id|scan-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|scan
)paren
suffix:semicolon
)brace
)brace
r_static
r_inline
r_void
DECL|function|hash_free_td
id|hash_free_td
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
id|hash_free_ed_td
(paren
op_amp
(paren
id|hc-&gt;td_hash
(braket
id|TD_HASH_FUNC
c_func
(paren
id|td-&gt;td_dma
)paren
)braket
)paren
comma
id|td
)paren
suffix:semicolon
)brace
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
id|pci_pool_create
(paren
l_string|&quot;ohci_td&quot;
comma
id|ohci-&gt;hcd.pdev
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
id|pci_pool_create
(paren
l_string|&quot;ohci_ed&quot;
comma
id|ohci-&gt;hcd.pdev
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
id|pci_pool_destroy
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
id|pci_pool_destroy
(paren
id|ohci-&gt;td_cache
)paren
suffix:semicolon
id|ohci-&gt;td_cache
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ohci-&gt;ed_cache
)paren
(brace
id|pci_pool_destroy
(paren
id|ohci-&gt;ed_cache
)paren
suffix:semicolon
id|ohci-&gt;ed_cache
op_assign
l_int|0
suffix:semicolon
)brace
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
id|pci_pool_alloc
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
id|td-&gt;td_dma
op_assign
id|dma
suffix:semicolon
multiline_comment|/* hash it for later reverse mapping */
r_if
c_cond
(paren
op_logical_neg
id|hash_add_td
(paren
id|hc
comma
id|td
comma
id|mem_flags
)paren
)paren
(brace
id|pci_pool_free
(paren
id|hc-&gt;td_cache
comma
id|td
comma
id|dma
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
singleline_comment|// DEBUG ONLY want to see if these tds are really getting
singleline_comment|// allocated.  the last one in a page shouldn&squot;t be getting
singleline_comment|// allocated during these tests!
r_if
c_cond
(paren
(paren
id|dma
op_amp
l_int|0x0fff
)paren
op_eq
l_int|0x0fc0
)paren
(brace
id|dbg
(paren
l_string|&quot;td = %p&quot;
comma
id|td
)paren
suffix:semicolon
id|dump_stack
(paren
)paren
suffix:semicolon
)brace
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
id|hash_free_td
(paren
id|hc
comma
id|td
)paren
suffix:semicolon
id|pci_pool_free
(paren
id|hc-&gt;td_cache
comma
id|td
comma
id|td-&gt;td_dma
)paren
suffix:semicolon
)brace
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
id|pci_pool_alloc
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
id|pci_pool_free
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
