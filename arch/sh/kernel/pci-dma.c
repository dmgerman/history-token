multiline_comment|/* &n; * Copyright (C) 2001 David J. Mckay (david.mckay@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.                            &n; *&n; * Dynamic DMA mapping support.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
DECL|function|pci_alloc_consistent
r_void
op_star
id|pci_alloc_consistent
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_handle
)paren
(brace
r_void
op_star
id|ret
suffix:semicolon
r_int
id|gfp
op_assign
id|GFP_ATOMIC
suffix:semicolon
id|ret
op_assign
(paren
r_void
op_star
)paren
id|__get_free_pages
c_func
(paren
id|gfp
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Is it necessary to do the memset? */
id|memset
c_func
(paren
id|ret
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
op_star
id|dma_handle
op_assign
id|virt_to_bus
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/* We must flush the cache before we pass it on to the device */
id|dma_cache_wback_inv
c_func
(paren
id|ret
comma
id|size
)paren
suffix:semicolon
r_return
id|P2SEGADDR
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
DECL|function|pci_free_consistent
r_void
id|pci_free_consistent
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_int
id|size
comma
r_void
op_star
id|vaddr
comma
id|dma_addr_t
id|dma_handle
)paren
(brace
r_int
r_int
id|p1addr
op_assign
id|P1SEGADDR
c_func
(paren
(paren
r_int
r_int
)paren
id|vaddr
)paren
suffix:semicolon
id|free_pages
c_func
(paren
id|p1addr
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
)brace
eof
