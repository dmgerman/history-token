multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000,2002 Silicon Graphics, Inc. All rights reserved.&n; *&n; * Routines for PCI DMA mapping.  See Documentation/DMA-mapping.txt for&n; * a description of how these routines should be used.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/invent.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr_private.h&gt;
macro_line|#include &lt;asm/sn/driver.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/alenlist.h&gt;
macro_line|#include &lt;asm/sn/pci/pci_bus_cvlink.h&gt;
macro_line|#include &lt;asm/sn/nag.h&gt;
id|pciio_dmamap_t
id|get_free_pciio_dmamap
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
r_void
id|free_pciio_dmamap
c_func
(paren
id|pcibr_dmamap_t
)paren
suffix:semicolon
r_struct
id|sn1_dma_maps_s
op_star
id|find_sn1_dma_map
c_func
(paren
id|dma_addr_t
comma
r_int
r_char
)paren
suffix:semicolon
r_extern
id|devfs_handle_t
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
multiline_comment|/*&n; * Get a free pciio_dmamap_t entry.&n; */
id|pciio_dmamap_t
DECL|function|get_free_pciio_dmamap
id|get_free_pciio_dmamap
c_func
(paren
id|devfs_handle_t
id|pci_bus
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|sn1_dma_maps_s
op_star
id|sn1_dma_map
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
id|sn1_dma_map
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
id|sn1_dma_map
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sn1_dma_map-&gt;dma_addr
)paren
(brace
id|sn1_dma_map-&gt;dma_addr
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
(paren
id|pciio_dmamap_t
)paren
id|sn1_dma_map
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Free pciio_dmamap_t entry.&n; */
r_void
DECL|function|free_pciio_dmamap
id|free_pciio_dmamap
c_func
(paren
id|pcibr_dmamap_t
id|dma_map
)paren
(brace
r_struct
id|sn1_dma_maps_s
op_star
id|sn1_dma_map
suffix:semicolon
id|sn1_dma_map
op_assign
(paren
r_struct
id|sn1_dma_maps_s
op_star
)paren
id|dma_map
suffix:semicolon
id|sn1_dma_map-&gt;dma_addr
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * sn_dma_sync: This routine flushes all DMA buffers for the device into the II.&n; *&t;This does not mean that the data is in the &quot;Coherence Domain&quot;.  But it &n; *&t;is very close.&n; */
r_void
DECL|function|sn_dma_sync
id|sn_dma_sync
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
)paren
(brace
r_struct
id|sn1_device_sysdata
op_star
id|device_sysdata
suffix:semicolon
r_volatile
r_int
r_int
id|dummy
suffix:semicolon
multiline_comment|/*&n;&t; * It is expected that on IA64 platform, a DMA sync ensures that all &n;&t; * the DMA (dma_handle) are complete and coherent.&n;&t; *&t;1. Flush Write Buffers from Bridge.&n;&t; *&t;2. Flush Xbow Port.&n;&t; */
id|device_sysdata
op_assign
(paren
r_struct
id|sn1_device_sysdata
op_star
)paren
id|hwdev-&gt;sysdata
suffix:semicolon
id|dummy
op_assign
(paren
r_volatile
r_int
r_int
)paren
op_star
id|device_sysdata-&gt;dma_buf_sync
suffix:semicolon
multiline_comment|/*&n;&t; * For the Xbow Port flush, we maybe denied the request because &n;&t; * someone else may be flushing the Port .. try again.&n;&t; */
r_while
c_loop
(paren
(paren
r_volatile
r_int
r_int
)paren
op_star
id|device_sysdata-&gt;xbow_buf_sync
)paren
(brace
id|udelay
c_func
(paren
l_int|2
)paren
suffix:semicolon
)brace
)brace
r_struct
id|sn1_dma_maps_s
op_star
DECL|function|find_sn1_dma_map
id|find_sn1_dma_map
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
id|sn1_dma_maps_s
op_star
id|sn1_dma_map
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
suffix:semicolon
id|sn1_dma_map
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
id|sn1_dma_map
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sn1_dma_map-&gt;dma_addr
op_eq
id|dma_addr
)paren
(brace
r_return
id|sn1_dma_map
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;find_pciio_dmamap: Unable find the corresponding dma map&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * sn1 platform specific pci_alloc_consistent()&n; *&n; * this interface is meant for &quot;command&quot; streams, i.e. called only&n; * once for initializing a device, so we don&squot;t want prefetching or&n; * write gathering turned on, hence the PCIIO_DMA_CMD flag&n; */
r_void
op_star
DECL|function|sn1_pci_alloc_consistent
id|sn1_pci_alloc_consistent
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
id|devfs_handle_t
id|vhdl
suffix:semicolon
r_struct
id|sn1_device_sysdata
op_star
id|device_sysdata
suffix:semicolon
id|paddr_t
id|temp_ptr
suffix:semicolon
op_star
id|dma_handle
op_assign
(paren
id|dma_addr_t
)paren
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * get vertex for the device&n;&t; */
id|device_sysdata
op_assign
(paren
r_struct
id|sn1_device_sysdata
op_star
)paren
id|hwdev-&gt;sysdata
suffix:semicolon
id|vhdl
op_assign
id|device_sysdata-&gt;vhdl
suffix:semicolon
r_if
c_cond
(paren
(paren
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
)paren
)paren
(brace
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
)brace
r_else
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|temp_ptr
op_assign
(paren
id|paddr_t
)paren
id|__pa
c_func
(paren
id|ret
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
multiline_comment|/*&n;&t;&t; * This device supports 64bits DMA addresses.&n;&t;&t; */
macro_line|#ifdef CONFIG_IA64_SGI_SN1
op_star
id|dma_handle
op_assign
id|pciio_dmatrans_addr
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|temp_ptr
comma
id|size
comma
id|PCIBR_BARRIER
op_or
id|PCIIO_BYTE_STREAM
op_or
id|PCIIO_DMA_CMD
op_or
id|PCIIO_DMA_A64
)paren
suffix:semicolon
macro_line|#else /* SN2 */
op_star
id|dma_handle
op_assign
id|pciio_dmatrans_addr
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|temp_ptr
comma
id|size
comma
id|PCIBR_BARRIER
op_or
id|PCIIO_DMA_CMD
op_or
id|PCIIO_DMA_A64
)paren
suffix:semicolon
macro_line|#endif
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Devices that supports 32 Bits upto 63 Bits DMA Address gets&n;&t; * 32 Bits DMA addresses.&n;&t; *&n;&t; * First try to get 32 Bit Direct Map Support.&n;&t; */
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
macro_line|#ifdef CONFIG_IA64_SGI_SN1
op_star
id|dma_handle
op_assign
id|pciio_dmatrans_addr
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|temp_ptr
comma
id|size
comma
id|PCIBR_BARRIER
op_or
id|PCIIO_BYTE_STREAM
op_or
id|PCIIO_DMA_CMD
)paren
suffix:semicolon
macro_line|#else /* SN2 */
op_star
id|dma_handle
op_assign
id|pciio_dmatrans_addr
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|temp_ptr
comma
id|size
comma
id|PCIBR_BARRIER
op_or
id|PCIIO_DMA_CMD
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|dma_handle
)paren
(brace
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * We need to map this request by using ATEs.&n;&t;&t;&t; */
id|printk
c_func
(paren
l_string|&quot;sn1_pci_alloc_consistent: 32Bits DMA Page Map support not available yet!&quot;
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|IS_PCI32L
c_func
(paren
id|hwdev
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * SNIA64 cannot support DMA Addresses smaller than 32 bits.&n;&t;&t; */
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_void
DECL|function|sn1_pci_free_consistent
id|sn1_pci_free_consistent
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
multiline_comment|/*&n; * On sn1 we use the page entry of the scatterlist to store&n; * the physical address corresponding to the given virtual address&n; */
r_int
DECL|function|sn1_pci_map_sg
id|sn1_pci_map_sg
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
id|devfs_handle_t
id|vhdl
suffix:semicolon
id|dma_addr_t
id|dma_addr
suffix:semicolon
id|paddr_t
id|temp_ptr
suffix:semicolon
r_struct
id|sn1_device_sysdata
op_star
id|device_sysdata
suffix:semicolon
id|pciio_dmamap_t
id|dma_map
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
multiline_comment|/*&n;&t; * Handle 64 bit cards.&n;&t; */
id|device_sysdata
op_assign
(paren
r_struct
id|sn1_device_sysdata
op_star
)paren
id|hwdev-&gt;sysdata
suffix:semicolon
id|vhdl
op_assign
id|device_sysdata-&gt;vhdl
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
multiline_comment|/* this catches incorrectly written drivers that&n;                   attempt to map scatterlists that they have&n;                   previously mapped.  we print a warning and&n;                   continue, but the driver should be fixed */
r_switch
c_cond
(paren
(paren
(paren
id|u64
)paren
id|sg-&gt;address
)paren
op_rshift
l_int|60
)paren
(brace
r_case
l_int|0xa
suffix:colon
r_case
l_int|0xb
suffix:colon
macro_line|#ifdef DEBUG
multiline_comment|/* This needs to be cleaned up at some point. */
id|NAG
c_func
(paren
l_string|&quot;A PCI driver (for device at%8s) has attempted to &quot;
l_string|&quot;map a scatterlist that was previously mapped at &quot;
l_string|&quot;%p - this is currently being worked around.&bslash;n&quot;
comma
id|hwdev-&gt;slot_name
comma
(paren
r_void
op_star
)paren
id|sg-&gt;address
)paren
suffix:semicolon
macro_line|#endif
id|temp_ptr
op_assign
(paren
id|u64
)paren
id|sg-&gt;address
op_amp
id|TO_PHYS_MASK
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xe
suffix:colon
multiline_comment|/* a good address, we now map it. */
id|temp_ptr
op_assign
(paren
id|paddr_t
)paren
id|__pa
c_func
(paren
id|sg-&gt;address
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Very bad address (%p) passed to sn1_pci_map_sg&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|sg-&gt;address
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|sg-&gt;page
op_assign
(paren
r_char
op_star
)paren
l_int|NULL
suffix:semicolon
id|dma_addr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Handle the most common case 64Bit cards.&n;&t;&t; */
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
macro_line|#ifdef CONFIG_IA64_SGI_SN1
id|dma_addr
op_assign
(paren
id|dma_addr_t
)paren
id|pciio_dmatrans_addr
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|temp_ptr
comma
id|sg-&gt;length
comma
id|PCIIO_BYTE_STREAM
op_or
id|PCIIO_DMA_DATA
op_or
id|PCIIO_DMA_A64
)paren
suffix:semicolon
macro_line|#else
id|dma_addr
op_assign
(paren
id|dma_addr_t
)paren
id|pciio_dmatrans_addr
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|temp_ptr
comma
id|sg-&gt;length
comma
id|PCIIO_DMA_DATA
op_or
id|PCIIO_DMA_A64
)paren
suffix:semicolon
macro_line|#endif
id|sg-&gt;address
op_assign
(paren
r_char
op_star
)paren
id|dma_addr
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Handle 32Bits and greater cards.&n;&t;&t; */
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
macro_line|#ifdef CONFIG_IA64_SGI_SN1
id|dma_addr
op_assign
(paren
id|dma_addr_t
)paren
id|pciio_dmatrans_addr
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|temp_ptr
comma
id|sg-&gt;length
comma
id|PCIIO_BYTE_STREAM
op_or
id|PCIIO_DMA_DATA
)paren
suffix:semicolon
macro_line|#else
id|dma_addr
op_assign
(paren
id|dma_addr_t
)paren
id|pciio_dmatrans_addr
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|temp_ptr
comma
id|sg-&gt;length
comma
id|PCIIO_DMA_DATA
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|dma_addr
)paren
(brace
id|sg-&gt;address
op_assign
(paren
r_char
op_star
)paren
id|dma_addr
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * It is a 32 bit card and we cannot do direct mapping,&n;&t;&t; * so we use an ATE.&n;&t;&t; */
id|dma_map
op_assign
l_int|0
suffix:semicolon
id|dma_map
op_assign
id|pciio_dmamap_alloc
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|sg-&gt;length
comma
id|DMA_DATA_FLAGS
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
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|dma_addr
op_assign
id|pciio_dmamap_addr
c_func
(paren
id|dma_map
comma
id|phys_addr
comma
id|sg-&gt;length
)paren
suffix:semicolon
id|sg-&gt;address
op_assign
(paren
r_char
op_star
)paren
id|dma_addr
suffix:semicolon
id|sg-&gt;page
op_assign
(paren
r_char
op_star
)paren
id|dma_map
suffix:semicolon
)brace
r_return
id|nents
suffix:semicolon
)brace
multiline_comment|/*&n; * Unmap a set of streaming mode DMA translations.&n; * Again, cpu read rules concerning calls here are the same as for&n; * pci_unmap_single() above.&n; */
r_void
DECL|function|sn1_pci_unmap_sg
id|sn1_pci_unmap_sg
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
id|nelems
comma
r_int
id|direction
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|sn1_dma_maps_s
op_star
id|sn1_dma_map
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nelems
suffix:semicolon
id|i
op_increment
comma
id|sg
op_increment
)paren
r_if
c_cond
(paren
id|sg-&gt;page
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * We maintain the DMA Map pointer in sg-&gt;page if &n;&t;&t;&t; * it is ever allocated.&n;&t;&t;&t; */
multiline_comment|/* phys_to_virt((dma_addr_t)sg-&gt;address | ~0x80000000); */
multiline_comment|/* sg-&gt;address = sg-&gt;page; */
id|sg-&gt;address
op_assign
(paren
r_char
op_star
)paren
op_minus
l_int|1
suffix:semicolon
id|sn1_dma_map
op_assign
(paren
r_struct
id|sn1_dma_maps_s
op_star
)paren
id|sg-&gt;page
suffix:semicolon
id|pciio_dmamap_done
c_func
(paren
(paren
id|pciio_dmamap_t
)paren
id|sn1_dma_map
)paren
suffix:semicolon
id|pciio_dmamap_free
c_func
(paren
(paren
id|pciio_dmamap_t
)paren
id|sn1_dma_map
)paren
suffix:semicolon
id|sn1_dma_map-&gt;dma_addr
op_assign
l_int|0
suffix:semicolon
id|sg-&gt;page
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * sn_pci_map_single - map a single region for DMA&n; * @hwdev: device to map for&n; * @ptr: kernel virtual address of the region to map&n; * @size: size of the region&n; * @direction: DMA direction&n; *&n; * Map the region pointed to by @ptr for DMA and return the&n; * DMA address.   Also known as platform_pci_map_single() by&n; * the IA64 machvec code.&n; *&n; * We map this to the one step pciio_dmamap_trans interface rather than&n; * the two step pciio_dmamap_alloc/pciio_dmamap_addr because we have&n; * no way of saving the dmamap handle from the alloc to later free&n; * (which is pretty much unacceptable).&n; *&n; * TODO: simplify our interface;&n; *       get rid of dev_desc and vhdl (seems redundant given a pci_dev);&n; *       figure out how to save dmamap handle so can use two step.&n; */
DECL|function|sn1_pci_map_single
id|dma_addr_t
id|sn1_pci_map_single
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
id|devfs_handle_t
id|vhdl
suffix:semicolon
id|dma_addr_t
id|dma_addr
suffix:semicolon
id|paddr_t
id|temp_ptr
suffix:semicolon
r_struct
id|sn1_device_sysdata
op_star
id|device_sysdata
suffix:semicolon
id|pciio_dmamap_t
id|dma_map
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|sn1_dma_maps_s
op_star
id|sn1_dma_map
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
multiline_comment|/*&n;&t; * find vertex for the device&n;&t; */
id|device_sysdata
op_assign
(paren
r_struct
id|sn1_device_sysdata
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
id|temp_ptr
op_assign
(paren
id|paddr_t
)paren
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
multiline_comment|/*&n;&t;&t; * This device supports 64bits DMA addresses.&n;&t;&t; */
macro_line|#ifdef CONFIG_IA64_SGI_SN1
id|dma_addr
op_assign
(paren
id|dma_addr_t
)paren
id|pciio_dmatrans_addr
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|temp_ptr
comma
id|size
comma
id|PCIIO_BYTE_STREAM
op_or
id|PCIIO_DMA_DATA
op_or
id|PCIIO_DMA_A64
)paren
suffix:semicolon
macro_line|#else
id|dma_addr
op_assign
(paren
id|dma_addr_t
)paren
id|pciio_dmatrans_addr
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|temp_ptr
comma
id|size
comma
id|PCIIO_DMA_DATA
op_or
id|PCIIO_DMA_A64
)paren
suffix:semicolon
macro_line|#endif
r_return
(paren
id|dma_addr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Devices that supports 32 Bits upto 63 Bits DMA Address gets&n;&t; * 32 Bits DMA addresses.&n;&t; *&n;&t; * First try to get 32 Bit Direct Map Support.&n;&t; */
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
macro_line|#ifdef CONFIG_IA64_SGI_SN1
id|dma_addr
op_assign
(paren
id|dma_addr_t
)paren
id|pciio_dmatrans_addr
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|temp_ptr
comma
id|size
comma
id|PCIIO_BYTE_STREAM
op_or
id|PCIIO_DMA_DATA
)paren
suffix:semicolon
macro_line|#else
id|dma_addr
op_assign
(paren
id|dma_addr_t
)paren
id|pciio_dmatrans_addr
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|temp_ptr
comma
id|size
comma
id|PCIIO_DMA_DATA
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|dma_addr
)paren
(brace
r_return
(paren
id|dma_addr
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|IS_PCI32L
c_func
(paren
id|hwdev
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * SNIA64 cannot support DMA Addresses smaller than 32 bits.&n;&t;&t; */
r_return
(paren
(paren
id|dma_addr_t
)paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * It is a 32bit card and we cannot do Direct mapping.&n;&t; * Let&squot;s 32Bit Page map the request.&n;&t; */
id|dma_map
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef CONFIG_IA64_SGI_SN1
id|dma_map
op_assign
id|pciio_dmamap_alloc
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|size
comma
id|PCIIO_BYTE_STREAM
op_or
id|PCIIO_DMA_DATA
)paren
suffix:semicolon
macro_line|#else
id|dma_map
op_assign
id|pciio_dmamap_alloc
c_func
(paren
id|vhdl
comma
l_int|NULL
comma
id|size
comma
id|PCIIO_DMA_DATA
)paren
suffix:semicolon
macro_line|#endif
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
l_string|&quot;pci_map_single: Unable to allocate anymore 32Bits Page Map entries.&bslash;n&quot;
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|dma_addr
op_assign
(paren
id|dma_addr_t
)paren
id|pciio_dmamap_addr
c_func
(paren
id|dma_map
comma
id|temp_ptr
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* printk(&quot;pci_map_single: dma_map 0x%p Phys Addr 0x%p dma_addr 0x%p&bslash;n&quot;, dma_map,&n;&t;&t;temp_ptr, dma_addr); */
id|sn1_dma_map
op_assign
(paren
r_struct
id|sn1_dma_maps_s
op_star
)paren
id|dma_map
suffix:semicolon
id|sn1_dma_map-&gt;dma_addr
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
r_void
DECL|function|sn1_pci_unmap_single
id|sn1_pci_unmap_single
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
id|sn1_dma_maps_s
op_star
id|sn1_dma_map
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
multiline_comment|/*&n;&t; * Get the sn1_dma_map entry.&n;&t; */
r_if
c_cond
(paren
id|IS_PCI32_MAPPED
c_func
(paren
id|dma_addr
)paren
)paren
id|sn1_dma_map
op_assign
id|find_sn1_dma_map
c_func
(paren
id|dma_addr
comma
id|hwdev-&gt;bus-&gt;number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sn1_dma_map
)paren
(brace
id|pciio_dmamap_done
c_func
(paren
(paren
id|pciio_dmamap_t
)paren
id|sn1_dma_map
)paren
suffix:semicolon
id|pciio_dmamap_free
c_func
(paren
(paren
id|pciio_dmamap_t
)paren
id|sn1_dma_map
)paren
suffix:semicolon
id|sn1_dma_map-&gt;dma_addr
op_assign
(paren
id|dma_addr_t
)paren
l_int|NULL
suffix:semicolon
)brace
)brace
r_void
DECL|function|sn1_pci_dma_sync_single
id|sn1_pci_dma_sync_single
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
id|sn_dma_sync
c_func
(paren
id|hwdev
)paren
suffix:semicolon
)brace
r_void
DECL|function|sn1_pci_dma_sync_sg
id|sn1_pci_dma_sync_sg
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
id|nelems
comma
r_int
id|direction
)paren
(brace
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
id|sn_dma_sync
c_func
(paren
id|hwdev
)paren
suffix:semicolon
)brace
r_int
r_int
DECL|function|sn1_dma_address
id|sn1_dma_address
(paren
r_struct
id|scatterlist
op_star
id|sg
)paren
(brace
r_return
(paren
(paren
r_int
r_int
)paren
id|sg-&gt;address
)paren
suffix:semicolon
)brace
eof
