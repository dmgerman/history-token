multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000,2002-2003 Silicon Graphics, Inc. All rights reserved.&n; *&n; * Routines for PCI DMA mapping.  See Documentation/DMA-mapping.txt for&n; * a description of how these routines should be used.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr_private.h&gt;
macro_line|#include &lt;asm/sn/driver.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/alenlist.h&gt;
macro_line|#include &lt;asm/sn/pci/pci_bus_cvlink.h&gt;
multiline_comment|/*&n; * For ATE allocations&n; */
id|pciio_dmamap_t
id|get_free_pciio_dmamap
c_func
(paren
id|vertex_hdl_t
)paren
suffix:semicolon
r_void
id|free_pciio_dmamap
c_func
(paren
id|pcibr_dmamap_t
)paren
suffix:semicolon
r_static
r_struct
id|pcibr_dmamap_s
op_star
id|find_sn_dma_map
c_func
(paren
id|dma_addr_t
comma
r_int
r_char
)paren
suffix:semicolon
r_void
id|sn_pci_unmap_sg
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nents
comma
r_int
id|direction
)paren
suffix:semicolon
multiline_comment|/*&n; * Toplogy stuff&n; */
r_extern
id|vertex_hdl_t
id|busnum_to_pcibr_vhdl
(braket
)braket
suffix:semicolon
r_extern
id|nasid_t
id|busnum_to_nid
(braket
)braket
suffix:semicolon
r_extern
r_void
op_star
id|busnum_to_atedmamaps
(braket
)braket
suffix:semicolon
multiline_comment|/**&n; * get_free_pciio_dmamap - find and allocate an ATE&n; * @pci_bus: PCI bus to get an entry for&n; *&n; * Finds and allocates an ATE on the PCI bus specified&n; * by @pci_bus.&n; */
id|pciio_dmamap_t
DECL|function|get_free_pciio_dmamap
id|get_free_pciio_dmamap
c_func
(paren
id|vertex_hdl_t
id|pci_bus
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|pcibr_dmamap_s
op_star
id|sn_dma_map
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Darn, we need to get the maps allocated for this bus.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_PCI_XWIDGET
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|busnum_to_pcibr_vhdl
(braket
id|i
)braket
op_eq
id|pci_bus
)paren
(brace
id|sn_dma_map
op_assign
id|busnum_to_atedmamaps
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Now get a free dmamap entry from this list.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_ATE_MAPS
suffix:semicolon
id|i
op_increment
comma
id|sn_dma_map
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sn_dma_map-&gt;bd_dma_addr
)paren
(brace
id|sn_dma_map-&gt;bd_dma_addr
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
(paren
id|pciio_dmamap_t
)paren
id|sn_dma_map
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; * free_pciio_dmamap - free an ATE&n; * @dma_map: ATE to free&n; *&n; * Frees the ATE specified by @dma_map.&n; */
r_void
DECL|function|free_pciio_dmamap
id|free_pciio_dmamap
c_func
(paren
id|pcibr_dmamap_t
id|dma_map
)paren
(brace
id|dma_map-&gt;bd_dma_addr
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * find_sn_dma_map - find an ATE associated with @dma_addr and @busnum&n; * @dma_addr: DMA address to look for&n; * @busnum: PCI bus to look on&n; *&n; * Finds the ATE associated with @dma_addr and @busnum.&n; */
r_static
r_struct
id|pcibr_dmamap_s
op_star
DECL|function|find_sn_dma_map
id|find_sn_dma_map
c_func
(paren
id|dma_addr_t
id|dma_addr
comma
r_int
r_char
id|busnum
)paren
(brace
r_struct
id|pcibr_dmamap_s
op_star
id|sn_dma_map
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
suffix:semicolon
id|sn_dma_map
op_assign
id|busnum_to_atedmamaps
(braket
id|busnum
)braket
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
id|MAX_ATE_MAPS
suffix:semicolon
id|i
op_increment
comma
id|sn_dma_map
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sn_dma_map-&gt;bd_dma_addr
op_eq
id|dma_addr
)paren
(brace
r_return
id|sn_dma_map
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; * sn_pci_alloc_consistent - allocate memory for coherent DMA&n; * @hwdev: device to allocate for&n; * @size: size of the region&n; * @dma_handle: DMA (bus) address&n; *&n; * pci_alloc_consistent() returns a pointer to a memory region suitable for&n; * coherent DMA traffic to/from a PCI device.  On SN platforms, this means&n; * that @dma_handle will have the %PCIIO_DMA_CMD flag set.&n; *&n; * This interface is usually used for &quot;command&quot; streams (e.g. the command&n; * queue for a SCSI controller).  See Documentation/DMA-mapping.txt for&n; * more information.  Note that this routine will always put a 32 bit&n; * DMA address into @dma_handle.  This is because most devices&n; * that are capable of 64 bit PCI DMA transactions can&squot;t do 64 bit _coherent_&n; * DMAs, and unfortunately this interface has to cater to the LCD.  Oh well.&n; *&n; * Also known as platform_pci_alloc_consistent() by the IA64 machvec code.&n; */
r_void
op_star
DECL|function|sn_pci_alloc_consistent
id|sn_pci_alloc_consistent
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
id|cpuaddr
suffix:semicolon
id|vertex_hdl_t
id|vhdl
suffix:semicolon
r_struct
id|sn_device_sysdata
op_star
id|device_sysdata
suffix:semicolon
r_int
r_int
id|phys_addr
suffix:semicolon
id|pcibr_dmamap_t
id|dma_map
op_assign
l_int|0
suffix:semicolon
op_star
id|dma_handle
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hwdev-&gt;dma_mask
OL
l_int|0xffffffffUL
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Get hwgraph vertex for the device&n;&t; */
id|device_sysdata
op_assign
(paren
r_struct
id|sn_device_sysdata
op_star
)paren
id|hwdev-&gt;sysdata
suffix:semicolon
id|vhdl
op_assign
id|device_sysdata-&gt;vhdl
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate the memory.  FIXME: if we&squot;re allocating for&n;&t; * two devices on the same bus, we should at least try to&n;&t; * allocate memory in the same 2 GB window to avoid using&n;&t; * ATEs for the translation.  See the comment above about the&n;&t; * 32 bit requirement for this function.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|cpuaddr
op_assign
(paren
r_void
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_ATOMIC
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* physical addr. of the memory we just got */
id|phys_addr
op_assign
id|__pa
c_func
(paren
id|cpuaddr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This will try to use a Direct Map register to do the&n;&t; * 32 bit DMA mapping, but it may not succeed if another&n;&t; * device on the same bus is already mapped with different&n;&t; * attributes or to a different memory region.&n;&t; */
op_star
id|dma_handle
op_assign
id|pcibr_dmatrans_addr
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|phys_addr
comma
id|size
comma
(paren
(paren
id|IS_PIC_DEVICE
c_func
(paren
id|hwdev
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
id|PCIIO_BYTE_STREAM
)paren
op_or
id|PCIIO_DMA_CMD
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If this device is in PCI-X mode, the system would have&n;&t; * automatically allocated a 64Bits DMA Address.  Error out if the &n;&t; * device cannot support DAC.&n;&t; */
r_if
c_cond
(paren
op_star
id|dma_handle
OG
id|hwdev-&gt;consistent_dma_mask
)paren
(brace
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|cpuaddr
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * It is a 32 bit card and we cannot do direct mapping,&n;&t; * so we try to use an ATE.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|dma_handle
)paren
)paren
(brace
id|dma_map
op_assign
id|pcibr_dmamap_alloc
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|size
comma
(paren
(paren
id|IS_PIC_DEVICE
c_func
(paren
id|hwdev
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
id|PCIIO_BYTE_STREAM
)paren
op_or
id|PCIIO_DMA_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma_map
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sn_pci_alloc_consistent: Unable to &quot;
l_string|&quot;allocate anymore 32 bit page map entries.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|dma_handle
op_assign
(paren
id|dma_addr_t
)paren
id|pcibr_dmamap_addr
c_func
(paren
id|dma_map
comma
id|phys_addr
comma
id|size
)paren
suffix:semicolon
id|dma_map-&gt;bd_dma_addr
op_assign
op_star
id|dma_handle
suffix:semicolon
)brace
r_return
id|cpuaddr
suffix:semicolon
)brace
multiline_comment|/**&n; * sn_pci_free_consistent - free memory associated with coherent DMAable region&n; * @hwdev: device to free for&n; * @size: size to free&n; * @vaddr: kernel virtual address to free&n; * @dma_handle: DMA address associated with this region&n; *&n; * Frees the memory allocated by pci_alloc_consistent().  Also known&n; * as platform_pci_free_consistent() by the IA64 machvec code.&n; */
r_void
DECL|function|sn_pci_free_consistent
id|sn_pci_free_consistent
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
r_struct
id|pcibr_dmamap_s
op_star
id|dma_map
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Get the sn_dma_map entry.&n;&t; */
r_if
c_cond
(paren
id|IS_PCI32_MAPPED
c_func
(paren
id|dma_handle
)paren
)paren
id|dma_map
op_assign
id|find_sn_dma_map
c_func
(paren
id|dma_handle
comma
id|hwdev-&gt;bus-&gt;number
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * and free it if necessary...&n;&t; */
r_if
c_cond
(paren
id|dma_map
)paren
(brace
id|pcibr_dmamap_done
c_func
(paren
id|dma_map
)paren
suffix:semicolon
id|pcibr_dmamap_free
c_func
(paren
id|dma_map
)paren
suffix:semicolon
id|dma_map-&gt;bd_dma_addr
op_assign
l_int|0
suffix:semicolon
)brace
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|vaddr
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * sn_pci_map_sg - map a scatter-gather list for DMA&n; * @hwdev: device to map for&n; * @sg: scatterlist to map&n; * @nents: number of entries&n; * @direction: direction of the DMA transaction&n; *&n; * Maps each entry of @sg for DMA.  Also known as platform_pci_map_sg by the&n; * IA64 machvec code.&n; */
r_int
DECL|function|sn_pci_map_sg
id|sn_pci_map_sg
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nents
comma
r_int
id|direction
)paren
(brace
r_int
id|i
suffix:semicolon
id|vertex_hdl_t
id|vhdl
suffix:semicolon
r_int
r_int
id|phys_addr
suffix:semicolon
r_struct
id|sn_device_sysdata
op_star
id|device_sysdata
suffix:semicolon
id|pcibr_dmamap_t
id|dma_map
suffix:semicolon
r_struct
id|scatterlist
op_star
id|saved_sg
op_assign
id|sg
suffix:semicolon
multiline_comment|/* can&squot;t go anywhere w/o a direction in life */
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get the hwgraph vertex for the device&n;&t; */
id|device_sysdata
op_assign
(paren
r_struct
id|sn_device_sysdata
op_star
)paren
id|hwdev-&gt;sysdata
suffix:semicolon
id|vhdl
op_assign
id|device_sysdata-&gt;vhdl
suffix:semicolon
multiline_comment|/*&n;&t; * Setup a DMA address for each entry in the&n;&t; * scatterlist.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nents
suffix:semicolon
id|i
op_increment
comma
id|sg
op_increment
)paren
(brace
id|phys_addr
op_assign
id|__pa
c_func
(paren
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|sg-&gt;page
)paren
op_plus
id|sg-&gt;offset
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Handle the most common case: 64 bit cards.  This&n;&t;&t; * call should always succeed.&n;&t;&t; */
r_if
c_cond
(paren
id|IS_PCIA64
c_func
(paren
id|hwdev
)paren
)paren
(brace
id|sg-&gt;dma_address
op_assign
id|pcibr_dmatrans_addr
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|phys_addr
comma
id|sg-&gt;length
comma
(paren
(paren
id|IS_PIC_DEVICE
c_func
(paren
id|hwdev
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
id|PCIIO_BYTE_STREAM
)paren
op_or
id|PCIIO_DMA_DATA
op_or
id|PCIIO_DMA_A64
)paren
suffix:semicolon
id|sg-&gt;dma_length
op_assign
id|sg-&gt;length
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Handle 32-63 bit cards via direct mapping&n;&t;&t; */
r_if
c_cond
(paren
id|IS_PCI32G
c_func
(paren
id|hwdev
)paren
)paren
(brace
id|sg-&gt;dma_address
op_assign
id|pcibr_dmatrans_addr
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|phys_addr
comma
id|sg-&gt;length
comma
(paren
(paren
id|IS_PIC_DEVICE
c_func
(paren
id|hwdev
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
id|PCIIO_BYTE_STREAM
)paren
op_or
id|PCIIO_DMA_DATA
)paren
suffix:semicolon
id|sg-&gt;dma_length
op_assign
id|sg-&gt;length
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * See if we got a direct map entry&n;&t;&t;&t; */
r_if
c_cond
(paren
id|sg-&gt;dma_address
)paren
(brace
r_continue
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * It is a 32 bit card and we cannot do direct mapping,&n;&t;&t; * so we use an ATE.&n;&t;&t; */
id|dma_map
op_assign
id|pcibr_dmamap_alloc
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|sg-&gt;length
comma
(paren
(paren
id|IS_PIC_DEVICE
c_func
(paren
id|hwdev
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
id|PCIIO_BYTE_STREAM
)paren
op_or
id|PCIIO_DMA_DATA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma_map
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sn_pci_map_sg: Unable to allocate &quot;
l_string|&quot;anymore 32 bit page map entries.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * We will need to free all previously allocated entries.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
(brace
id|sn_pci_unmap_sg
c_func
(paren
id|hwdev
comma
id|saved_sg
comma
id|i
comma
id|direction
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|sg-&gt;dma_address
op_assign
id|pcibr_dmamap_addr
c_func
(paren
id|dma_map
comma
id|phys_addr
comma
id|sg-&gt;length
)paren
suffix:semicolon
id|sg-&gt;dma_length
op_assign
id|sg-&gt;length
suffix:semicolon
id|dma_map-&gt;bd_dma_addr
op_assign
id|sg-&gt;dma_address
suffix:semicolon
)brace
r_return
id|nents
suffix:semicolon
)brace
multiline_comment|/**&n; * sn_pci_unmap_sg - unmap a scatter-gather list&n; * @hwdev: device to unmap&n; * @sg: scatterlist to unmap&n; * @nents: number of scatterlist entries&n; * @direction: DMA direction&n; *&n; * Unmap a set of streaming mode DMA translations.  Again, cpu read rules&n; * concerning calls here are the same as for pci_unmap_single() below.  Also&n; * known as sn_pci_unmap_sg() by the IA64 machvec code.&n; */
r_void
DECL|function|sn_pci_unmap_sg
id|sn_pci_unmap_sg
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nents
comma
r_int
id|direction
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|pcibr_dmamap_s
op_star
id|dma_map
suffix:semicolon
multiline_comment|/* can&squot;t go anywhere w/o a direction in life */
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
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
id|nents
suffix:semicolon
id|i
op_increment
comma
id|sg
op_increment
)paren
(brace
r_if
c_cond
(paren
id|IS_PCI32_MAPPED
c_func
(paren
id|sg-&gt;dma_address
)paren
)paren
(brace
id|dma_map
op_assign
id|find_sn_dma_map
c_func
(paren
id|sg-&gt;dma_address
comma
id|hwdev-&gt;bus-&gt;number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma_map
)paren
(brace
id|pcibr_dmamap_done
c_func
(paren
id|dma_map
)paren
suffix:semicolon
id|pcibr_dmamap_free
c_func
(paren
id|dma_map
)paren
suffix:semicolon
id|dma_map-&gt;bd_dma_addr
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|sg-&gt;dma_address
op_assign
(paren
id|dma_addr_t
)paren
l_int|NULL
suffix:semicolon
id|sg-&gt;dma_length
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * sn_pci_map_single - map a single region for DMA&n; * @hwdev: device to map for&n; * @ptr: kernel virtual address of the region to map&n; * @size: size of the region&n; * @direction: DMA direction&n; *&n; * Map the region pointed to by @ptr for DMA and return the&n; * DMA address.   Also known as platform_pci_map_single() by&n; * the IA64 machvec code.&n; *&n; * We map this to the one step pcibr_dmamap_trans interface rather than&n; * the two step pciio_dmamap_alloc/pciio_dmamap_addr because we have&n; * no way of saving the dmamap handle from the alloc to later free&n; * (which is pretty much unacceptable).&n; *&n; * TODO: simplify our interface;&n; *       get rid of dev_desc and vhdl (seems redundant given a pci_dev);&n; *       figure out how to save dmamap handle so can use two step.&n; */
id|dma_addr_t
DECL|function|sn_pci_map_single
id|sn_pci_map_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_void
op_star
id|ptr
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
id|vertex_hdl_t
id|vhdl
suffix:semicolon
id|dma_addr_t
id|dma_addr
suffix:semicolon
r_int
r_int
id|phys_addr
suffix:semicolon
r_struct
id|sn_device_sysdata
op_star
id|device_sysdata
suffix:semicolon
id|pcibr_dmamap_t
id|dma_map
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* SN cannot support DMA addresses smaller than 32 bits. */
r_if
c_cond
(paren
id|IS_PCI32L
c_func
(paren
id|hwdev
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * find vertex for the device&n;&t; */
id|device_sysdata
op_assign
(paren
r_struct
id|sn_device_sysdata
op_star
)paren
id|hwdev-&gt;sysdata
suffix:semicolon
id|vhdl
op_assign
id|device_sysdata-&gt;vhdl
suffix:semicolon
multiline_comment|/*&n;&t; * Call our dmamap interface&n;&t; */
id|dma_addr
op_assign
l_int|0
suffix:semicolon
id|phys_addr
op_assign
id|__pa
c_func
(paren
id|ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_PCIA64
c_func
(paren
id|hwdev
)paren
)paren
(brace
multiline_comment|/* This device supports 64 bit DMA addresses. */
id|dma_addr
op_assign
id|pcibr_dmatrans_addr
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|phys_addr
comma
id|size
comma
(paren
(paren
id|IS_PIC_DEVICE
c_func
(paren
id|hwdev
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
id|PCIIO_BYTE_STREAM
)paren
op_or
id|PCIIO_DMA_DATA
op_or
id|PCIIO_DMA_A64
)paren
suffix:semicolon
r_return
id|dma_addr
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Devices that support 32 bit to 63 bit DMA addresses get&n;&t; * 32 bit DMA addresses.&n;&t; *&n;&t; * First try to get a 32 bit direct map register.&n;&t; */
r_if
c_cond
(paren
id|IS_PCI32G
c_func
(paren
id|hwdev
)paren
)paren
(brace
id|dma_addr
op_assign
id|pcibr_dmatrans_addr
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|phys_addr
comma
id|size
comma
(paren
(paren
id|IS_PIC_DEVICE
c_func
(paren
id|hwdev
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
id|PCIIO_BYTE_STREAM
)paren
op_or
id|PCIIO_DMA_DATA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma_addr
)paren
r_return
id|dma_addr
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * It&squot;s a 32 bit card and we cannot do direct mapping so&n;&t; * let&squot;s use the PMU instead.&n;&t; */
id|dma_map
op_assign
l_int|NULL
suffix:semicolon
id|dma_map
op_assign
id|pcibr_dmamap_alloc
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|size
comma
(paren
(paren
id|IS_PIC_DEVICE
c_func
(paren
id|hwdev
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
id|PCIIO_BYTE_STREAM
)paren
op_or
id|PCIIO_DMA_DATA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma_map
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pci_map_single: Unable to allocate anymore &quot;
l_string|&quot;32 bit page map entries.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|dma_addr
op_assign
(paren
id|dma_addr_t
)paren
id|pcibr_dmamap_addr
c_func
(paren
id|dma_map
comma
id|phys_addr
comma
id|size
)paren
suffix:semicolon
id|dma_map-&gt;bd_dma_addr
op_assign
id|dma_addr
suffix:semicolon
r_return
(paren
(paren
id|dma_addr_t
)paren
id|dma_addr
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * sn_pci_unmap_single - unmap a region used for DMA&n; * @hwdev: device to unmap&n; * @dma_addr: DMA address to unmap&n; * @size: size of region&n; * @direction: DMA direction&n; *&n; * Unmaps the region pointed to by @dma_addr.  Also known as&n; * platform_pci_unmap_single() by the IA64 machvec code.&n; */
r_void
DECL|function|sn_pci_unmap_single
id|sn_pci_unmap_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
id|dma_addr_t
id|dma_addr
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
r_struct
id|pcibr_dmamap_s
op_star
id|dma_map
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get the sn_dma_map entry.&n;&t; */
r_if
c_cond
(paren
id|IS_PCI32_MAPPED
c_func
(paren
id|dma_addr
)paren
)paren
id|dma_map
op_assign
id|find_sn_dma_map
c_func
(paren
id|dma_addr
comma
id|hwdev-&gt;bus-&gt;number
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * and free it if necessary...&n;&t; */
r_if
c_cond
(paren
id|dma_map
)paren
(brace
id|pcibr_dmamap_done
c_func
(paren
id|dma_map
)paren
suffix:semicolon
id|pcibr_dmamap_free
c_func
(paren
id|dma_map
)paren
suffix:semicolon
id|dma_map-&gt;bd_dma_addr
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * sn_pci_dma_sync_single - make sure all DMAs have completed&n; * @hwdev: device to sync&n; * @dma_handle: DMA address to sync&n; * @size: size of region&n; * @direction: DMA direction&n; *&n; * This routine is supposed to sync the DMA region specified&n; * by @dma_handle into the &squot;coherence domain&squot;.  We do not need to do &n; * anything on our platform.&n; */
r_void
DECL|function|sn_pci_dma_sync_single
id|sn_pci_dma_sync_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
id|dma_addr_t
id|dma_handle
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; * sn_pci_dma_sync_sg - make sure all DMAs have completed&n; * @hwdev: device to sync&n; * @sg: scatterlist to sync&n; * @nents: number of entries in the scatterlist&n; * @direction: DMA direction&n; *&n; * This routine is supposed to sync the DMA regions specified&n; * by @sg into the &squot;coherence domain&squot;.  We do not need to do anything &n; * on our platform.&n; */
r_void
DECL|function|sn_pci_dma_sync_sg
id|sn_pci_dma_sync_sg
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nents
comma
r_int
id|direction
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; * sn_dma_supported - test a DMA mask&n; * @hwdev: device to test&n; * @mask: DMA mask to test&n; *&n; * Return whether the given PCI device DMA address mask can be supported&n; * properly.  For example, if your device can only drive the low 24-bits&n; * during PCI bus mastering, then you would pass 0x00ffffff as the mask to&n; * this function.  Of course, SN only supports devices that have 32 or more&n; * address bits when using the PMU.  We could theoretically support &lt;32 bit&n; * cards using direct mapping, but we&squot;ll worry about that later--on the off&n; * chance that someone actually wants to use such a card.&n; */
r_int
DECL|function|sn_pci_dma_supported
id|sn_pci_dma_supported
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
id|u64
id|mask
)paren
(brace
r_if
c_cond
(paren
id|mask
OL
l_int|0xffffffff
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * New generic DMA routines just wrap sn2 PCI routines until we&n; * support other bus types (if ever).&n; */
r_int
DECL|function|sn_dma_supported
id|sn_dma_supported
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u64
id|mask
)paren
(brace
id|BUG_ON
c_func
(paren
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
r_return
id|sn_pci_dma_supported
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|mask
)paren
suffix:semicolon
)brace
DECL|variable|sn_dma_supported
id|EXPORT_SYMBOL
c_func
(paren
id|sn_dma_supported
)paren
suffix:semicolon
r_int
DECL|function|sn_dma_set_mask
id|sn_dma_set_mask
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u64
id|dma_mask
)paren
(brace
id|BUG_ON
c_func
(paren
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sn_dma_supported
c_func
(paren
id|dev
comma
id|dma_mask
)paren
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|dev-&gt;dma_mask
op_assign
id|dma_mask
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|sn_dma_set_mask
id|EXPORT_SYMBOL
c_func
(paren
id|sn_dma_set_mask
)paren
suffix:semicolon
r_void
op_star
DECL|function|sn_dma_alloc_coherent
id|sn_dma_alloc_coherent
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_handle
comma
r_int
id|flag
)paren
(brace
id|BUG_ON
c_func
(paren
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
r_return
id|sn_pci_alloc_consistent
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|size
comma
id|dma_handle
)paren
suffix:semicolon
)brace
DECL|variable|sn_dma_alloc_coherent
id|EXPORT_SYMBOL
c_func
(paren
id|sn_dma_alloc_coherent
)paren
suffix:semicolon
r_void
DECL|function|sn_dma_free_coherent
id|sn_dma_free_coherent
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|size
comma
r_void
op_star
id|cpu_addr
comma
id|dma_addr_t
id|dma_handle
)paren
(brace
id|BUG_ON
c_func
(paren
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
id|sn_pci_free_consistent
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|size
comma
id|cpu_addr
comma
id|dma_handle
)paren
suffix:semicolon
)brace
DECL|variable|sn_dma_free_coherent
id|EXPORT_SYMBOL
c_func
(paren
id|sn_dma_free_coherent
)paren
suffix:semicolon
id|dma_addr_t
DECL|function|sn_dma_map_single
id|sn_dma_map_single
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|cpu_addr
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
id|BUG_ON
c_func
(paren
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
r_return
id|sn_pci_map_single
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|cpu_addr
comma
id|size
comma
(paren
r_int
)paren
id|direction
)paren
suffix:semicolon
)brace
DECL|variable|sn_dma_map_single
id|EXPORT_SYMBOL
c_func
(paren
id|sn_dma_map_single
)paren
suffix:semicolon
r_void
DECL|function|sn_dma_unmap_single
id|sn_dma_unmap_single
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|dma_addr_t
id|dma_addr
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
id|BUG_ON
c_func
(paren
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
id|sn_pci_unmap_single
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|dma_addr
comma
id|size
comma
(paren
r_int
)paren
id|direction
)paren
suffix:semicolon
)brace
DECL|variable|sn_dma_unmap_single
id|EXPORT_SYMBOL
c_func
(paren
id|sn_dma_unmap_single
)paren
suffix:semicolon
id|dma_addr_t
DECL|function|sn_dma_map_page
id|sn_dma_map_page
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|offset
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
id|BUG_ON
c_func
(paren
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
r_return
id|pci_map_page
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|page
comma
id|offset
comma
id|size
comma
(paren
r_int
)paren
id|direction
)paren
suffix:semicolon
)brace
DECL|variable|sn_dma_map_page
id|EXPORT_SYMBOL
c_func
(paren
id|sn_dma_map_page
)paren
suffix:semicolon
r_void
DECL|function|sn_dma_unmap_page
id|sn_dma_unmap_page
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|dma_addr_t
id|dma_address
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
id|BUG_ON
c_func
(paren
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
id|pci_unmap_page
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|dma_address
comma
id|size
comma
(paren
r_int
)paren
id|direction
)paren
suffix:semicolon
)brace
DECL|variable|sn_dma_unmap_page
id|EXPORT_SYMBOL
c_func
(paren
id|sn_dma_unmap_page
)paren
suffix:semicolon
r_int
DECL|function|sn_dma_map_sg
id|sn_dma_map_sg
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nents
comma
r_int
id|direction
)paren
(brace
id|BUG_ON
c_func
(paren
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
r_return
id|sn_pci_map_sg
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|sg
comma
id|nents
comma
(paren
r_int
)paren
id|direction
)paren
suffix:semicolon
)brace
DECL|variable|sn_dma_map_sg
id|EXPORT_SYMBOL
c_func
(paren
id|sn_dma_map_sg
)paren
suffix:semicolon
r_void
DECL|function|sn_dma_unmap_sg
id|sn_dma_unmap_sg
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nhwentries
comma
r_int
id|direction
)paren
(brace
id|BUG_ON
c_func
(paren
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
id|sn_pci_unmap_sg
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|sg
comma
id|nhwentries
comma
(paren
r_int
)paren
id|direction
)paren
suffix:semicolon
)brace
DECL|variable|sn_dma_unmap_sg
id|EXPORT_SYMBOL
c_func
(paren
id|sn_dma_unmap_sg
)paren
suffix:semicolon
r_void
DECL|function|sn_dma_sync_single
id|sn_dma_sync_single
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|dma_addr_t
id|dma_handle
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
id|BUG_ON
c_func
(paren
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
id|sn_pci_dma_sync_single
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|dma_handle
comma
id|size
comma
(paren
r_int
)paren
id|direction
)paren
suffix:semicolon
)brace
DECL|variable|sn_dma_sync_single
id|EXPORT_SYMBOL
c_func
(paren
id|sn_dma_sync_single
)paren
suffix:semicolon
r_void
DECL|function|sn_dma_sync_sg
id|sn_dma_sync_sg
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nelems
comma
r_int
id|direction
)paren
(brace
id|BUG_ON
c_func
(paren
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
id|sn_pci_dma_sync_sg
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|sg
comma
id|nelems
comma
(paren
r_int
)paren
id|direction
)paren
suffix:semicolon
)brace
DECL|variable|sn_dma_sync_sg
id|EXPORT_SYMBOL
c_func
(paren
id|sn_dma_sync_sg
)paren
suffix:semicolon
DECL|variable|sn_pci_unmap_single
id|EXPORT_SYMBOL
c_func
(paren
id|sn_pci_unmap_single
)paren
suffix:semicolon
DECL|variable|sn_pci_map_single
id|EXPORT_SYMBOL
c_func
(paren
id|sn_pci_map_single
)paren
suffix:semicolon
DECL|variable|sn_pci_dma_sync_single
id|EXPORT_SYMBOL
c_func
(paren
id|sn_pci_dma_sync_single
)paren
suffix:semicolon
DECL|variable|sn_pci_map_sg
id|EXPORT_SYMBOL
c_func
(paren
id|sn_pci_map_sg
)paren
suffix:semicolon
DECL|variable|sn_pci_unmap_sg
id|EXPORT_SYMBOL
c_func
(paren
id|sn_pci_unmap_sg
)paren
suffix:semicolon
DECL|variable|sn_pci_alloc_consistent
id|EXPORT_SYMBOL
c_func
(paren
id|sn_pci_alloc_consistent
)paren
suffix:semicolon
DECL|variable|sn_pci_free_consistent
id|EXPORT_SYMBOL
c_func
(paren
id|sn_pci_free_consistent
)paren
suffix:semicolon
DECL|variable|sn_pci_dma_supported
id|EXPORT_SYMBOL
c_func
(paren
id|sn_pci_dma_supported
)paren
suffix:semicolon
eof
