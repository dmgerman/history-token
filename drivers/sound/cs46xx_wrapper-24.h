multiline_comment|/*******************************************************************************&n;*&n;*      &quot;cs46xx_wrapper.c&quot; --  Cirrus Logic-Crystal CS46XX linux audio driver.&n;*&n;*      Copyright (C) 2000,2001  Cirrus Logic Corp.  &n;*            -- tom woller (twoller@crystal.cirrus.com) or&n;*               (pcaudio@crystal.cirrus.com).&n;*&n;*      This program is free software; you can redistribute it and/or modify&n;*      it under the terms of the GNU General Public License as published by&n;*      the Free Software Foundation; either version 2 of the License, or&n;*      (at your option) any later version.&n;*&n;*      This program is distributed in the hope that it will be useful,&n;*      but WITHOUT ANY WARRANTY; without even the implied warranty of&n;*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;*      GNU General Public License for more details.&n;*&n;*      You should have received a copy of the GNU General Public License&n;*      along with this program; if not, write to the Free Software&n;*      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*&n;* 01/11/2001 trw - new file from cs4281 wrapper code. &n;*&n;*******************************************************************************/
macro_line|#ifndef __CS46XX_WRAPPER24_H
DECL|macro|__CS46XX_WRAPPER24_H
mdefine_line|#define __CS46XX_WRAPPER24_H
macro_line|#include &lt;linux/spinlock.h&gt;
DECL|macro|CS_OWNER
mdefine_line|#define CS_OWNER owner:
DECL|macro|CS_THIS_MODULE
mdefine_line|#define CS_THIS_MODULE THIS_MODULE,
DECL|function|cs46xx_null
r_void
id|cs46xx_null
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
mdefine_line|#define free_dmabuf(card, dmabuf) &bslash;&n;&t;pci_free_consistent((card)-&gt;pci_dev, &bslash;&n;&t;&t;&t;    PAGE_SIZE &lt;&lt; (dmabuf)-&gt;buforder, &bslash;&n;&t;&t;&t;    (dmabuf)-&gt;rawbuf, (dmabuf)-&gt;dmaaddr);
DECL|macro|free_dmabuf2
mdefine_line|#define free_dmabuf2(card, dmabuf) &bslash;&n;&t;pci_free_consistent((card)-&gt;pci_dev, &bslash;&n;&t;&t;&t;&t;    PAGE_SIZE &lt;&lt; (dmabuf)-&gt;buforder_tmpbuff, &bslash;&n;&t;&t;&t;&t;    (dmabuf)-&gt;tmpbuff, (dmabuf)-&gt;dmaaddr_tmpbuff);
DECL|macro|cs4x_pgoff
mdefine_line|#define cs4x_pgoff(vma) ((vma)-&gt;vm_pgoff)
DECL|macro|RSRCISIOREGION
mdefine_line|#define RSRCISIOREGION(dev,num) ((dev)-&gt;resource[(num)].start != 0 &amp;&amp; &bslash;&n;&t; ((dev)-&gt;resource[(num)].flags &amp; PCI_BASE_ADDRESS_SPACE) == PCI_BASE_ADDRESS_SPACE_IO)
DECL|macro|RSRCISMEMORYREGION
mdefine_line|#define RSRCISMEMORYREGION(dev,num) ((dev)-&gt;resource[(num)].start != 0 &amp;&amp; &bslash;&n;&t; ((dev)-&gt;resource[(num)].flags &amp; PCI_BASE_ADDRESS_SPACE) == PCI_BASE_ADDRESS_SPACE_MEMORY)
DECL|macro|RSRCADDRESS
mdefine_line|#define RSRCADDRESS(dev,num) ((dev)-&gt;resource[(num)].start)
DECL|macro|PCI_GET_DRIVER_DATA
mdefine_line|#define PCI_GET_DRIVER_DATA pci_get_drvdata
DECL|macro|PCI_SET_DRIVER_DATA
mdefine_line|#define PCI_SET_DRIVER_DATA pci_set_drvdata
DECL|macro|PCI_SET_DMA_MASK
mdefine_line|#define PCI_SET_DMA_MASK(pcidev,mask) pcidev-&gt;dma_mask = mask
macro_line|#endif
eof
