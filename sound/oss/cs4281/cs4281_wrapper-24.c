multiline_comment|/*******************************************************************************&n;*&n;*      &quot;cs4281_wrapper.c&quot; --  Cirrus Logic-Crystal CS4281 linux audio driver.&n;*&n;*      Copyright (C) 2000,2001  Cirrus Logic Corp.  &n;*            -- tom woller (twoller@crystal.cirrus.com) or&n;*               (audio@crystal.cirrus.com).&n;*&n;*      This program is free software; you can redistribute it and/or modify&n;*      it under the terms of the GNU General Public License as published by&n;*      the Free Software Foundation; either version 2 of the License, or&n;*      (at your option) any later version.&n;*&n;*      This program is distributed in the hope that it will be useful,&n;*      but WITHOUT ANY WARRANTY; without even the implied warranty of&n;*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;*      GNU General Public License for more details.&n;*&n;*      You should have received a copy of the GNU General Public License&n;*      along with this program; if not, write to the Free Software&n;*      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*&n;* 12/20/00 trw - new file. &n;*&n;*******************************************************************************/
macro_line|#include &lt;linux/spinlock.h&gt;
DECL|function|cs4281_null
r_void
id|cs4281_null
c_func
(paren
r_struct
id|pci_dev
op_star
id|pcidev
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|macro|cs4x_mem_map_reserve
mdefine_line|#define cs4x_mem_map_reserve(page) mem_map_reserve(page)
DECL|macro|cs4x_mem_map_unreserve
mdefine_line|#define cs4x_mem_map_unreserve(page) mem_map_unreserve(page)
DECL|macro|free_dmabuf
mdefine_line|#define free_dmabuf(state, dmabuf) &bslash;&n;&t;pci_free_consistent(state-&gt;pcidev, &bslash;&n;&t;&t;&t;    PAGE_SIZE &lt;&lt; (dmabuf)-&gt;buforder, &bslash;&n;&t;&t;&t;    (dmabuf)-&gt;rawbuf, (dmabuf)-&gt;dmaaddr);
DECL|macro|free_dmabuf2
mdefine_line|#define free_dmabuf2(state, dmabuf) &bslash;&n;&t;pci_free_consistent((state)-&gt;pcidev, &bslash;&n;&t;&t;&t;&t;    PAGE_SIZE &lt;&lt; (state)-&gt;buforder_tmpbuff, &bslash;&n;&t;&t;&t;&t;    (state)-&gt;tmpbuff, (state)-&gt;dmaaddr_tmpbuff);
DECL|macro|cs4x_pgoff
mdefine_line|#define cs4x_pgoff(vma) ((vma)-&gt;vm_pgoff)
eof
