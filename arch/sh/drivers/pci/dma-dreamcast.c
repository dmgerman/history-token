multiline_comment|/*&n; * arch/sh/pci/dma-dreamcast.c&n; *&n; * PCI DMA support for the Sega Dreamcast&n; *&n; * Copyright (C) 2001, 2002  M. R. Brown&n; * Copyright (C) 2002, 2003  Paul Mundt&n; *&n; * This file originally bore the message (with enclosed-$):&n; *&t;Id: pci.c,v 1.3 2003/05/04 19:29:46 lethal Exp&n; *&t;Dreamcast PCI: Supports SEGA Broadband Adaptor only.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/pci.h&gt;
DECL|variable|gapspci_dma_used
r_static
r_int
id|gapspci_dma_used
op_assign
l_int|0
suffix:semicolon
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
r_int
r_int
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|gapspci_dma_used
op_plus
id|size
OG
id|GAPSPCI_DMA_SIZE
)paren
r_return
l_int|NULL
suffix:semicolon
id|buf
op_assign
id|GAPSPCI_DMA_BASE
op_plus
id|gapspci_dma_used
suffix:semicolon
id|gapspci_dma_used
op_assign
id|PAGE_ALIGN
c_func
(paren
id|gapspci_dma_used
op_plus
id|size
)paren
suffix:semicolon
op_star
id|dma_handle
op_assign
(paren
id|dma_addr_t
)paren
id|buf
suffix:semicolon
id|buf
op_assign
id|P2SEGADDR
c_func
(paren
id|buf
)paren
suffix:semicolon
multiline_comment|/* Flush the dcache before we hand off the buffer */
id|dma_cache_wback_inv
c_func
(paren
(paren
r_void
op_star
)paren
id|buf
comma
id|size
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|buf
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
multiline_comment|/* XXX */
id|gapspci_dma_used
op_assign
l_int|0
suffix:semicolon
)brace
eof
