multiline_comment|/*&n; *  Various wrappers&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifdef ALSA_BUILD
macro_line|#include &quot;config.h&quot;
macro_line|#endif
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef ALSA_BUILD
macro_line|#if defined(CONFIG_MODVERSIONS) &amp;&amp; !defined(__GENKSYMS__) &amp;&amp; !defined(__DEPEND__)
DECL|macro|MODVERSIONS
mdefine_line|#define MODVERSIONS
macro_line|#include &lt;linux/modversions.h&gt;
macro_line|#include &quot;sndversions.h&quot;
macro_line|#endif
macro_line|#endif
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#ifdef CONFIG_SND_DEBUG_MEMORY
DECL|function|snd_wrapper_kmalloc
r_void
op_star
id|snd_wrapper_kmalloc
c_func
(paren
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_wrapper_kfree
r_void
id|snd_wrapper_kfree
c_func
(paren
r_const
r_void
op_star
id|obj
)paren
(brace
id|kfree
c_func
(paren
id|obj
)paren
suffix:semicolon
)brace
DECL|function|snd_wrapper_vmalloc
r_void
op_star
id|snd_wrapper_vmalloc
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_return
id|vmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
)brace
DECL|function|snd_wrapper_vfree
r_void
id|snd_wrapper_vfree
c_func
(paren
r_void
op_star
id|obj
)paren
(brace
id|vfree
c_func
(paren
id|obj
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* check the condition in &lt;sound/core.h&gt; !! */
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2, 4, 0)
macro_line|#if defined(__i386__) || defined(__ppc__) || defined(__x86_64__)
macro_line|#include &lt;linux/pci.h&gt;
multiline_comment|/* to be sure... */
macro_line|#ifdef HACK_PCI_ALLOC_CONSISTENT
macro_line|#error pci_alloc_consistent hack is already defined!!
macro_line|#endif
multiline_comment|/*&n; * A dirty hack... when the kernel code is fixed this should be removed.&n; *&n; * since pci_alloc_consistent always tries GFP_DMA when the requested&n; * pci memory region is below 32bit, it happens quite often that even&n; * 2 order of pages cannot be allocated.&n; *&n; * so in the following, we allocate at first without dma_mask, so that&n; * allocation will be done without GFP_DMA.  if the area doesn&squot;t match&n; * with the requested region, then realloate with the original dma_mask&n; * again.&n; */
DECL|function|snd_pci_hack_alloc_consistent
r_void
op_star
id|snd_pci_hack_alloc_consistent
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
id|u64
id|dma_mask
suffix:semicolon
r_int
r_int
id|rmask
suffix:semicolon
r_if
c_cond
(paren
id|hwdev
op_eq
l_int|NULL
)paren
r_return
id|pci_alloc_consistent
c_func
(paren
id|hwdev
comma
id|size
comma
id|dma_handle
)paren
suffix:semicolon
id|dma_mask
op_assign
id|hwdev-&gt;dma_mask
suffix:semicolon
id|rmask
op_assign
op_complement
(paren
(paren
r_int
r_int
)paren
id|dma_mask
)paren
suffix:semicolon
id|hwdev-&gt;dma_mask
op_assign
l_int|0xffffffff
suffix:semicolon
multiline_comment|/* do without masking */
id|ret
op_assign
id|pci_alloc_consistent
c_func
(paren
id|hwdev
comma
id|size
comma
id|dma_handle
)paren
suffix:semicolon
id|hwdev-&gt;dma_mask
op_assign
id|dma_mask
suffix:semicolon
multiline_comment|/* restore */
r_if
c_cond
(paren
id|ret
)paren
(brace
multiline_comment|/* obtained address is out of range? */
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
op_star
id|dma_handle
op_plus
id|size
op_minus
l_int|1
)paren
op_amp
id|rmask
)paren
(brace
multiline_comment|/* reallocate with the proper mask */
id|pci_free_consistent
c_func
(paren
id|hwdev
comma
id|size
comma
id|ret
comma
op_star
id|dma_handle
)paren
suffix:semicolon
id|ret
op_assign
id|pci_alloc_consistent
c_func
(paren
id|hwdev
comma
id|size
comma
id|dma_handle
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* wish to success now with the proper mask... */
r_if
c_cond
(paren
id|dma_mask
op_ne
l_int|0xffffffff
)paren
id|ret
op_assign
id|pci_alloc_consistent
c_func
(paren
id|hwdev
comma
id|size
comma
id|dma_handle
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
