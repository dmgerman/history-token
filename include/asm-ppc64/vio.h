multiline_comment|/*&n; * IBM PowerPC Virtual I/O Infrastructure Support.&n; *&n; *    Copyright (c) 2003 IBM Corp.&n; *     Dave Engebretsen engebret@us.ibm.com&n; *     Santiago Leon santil@us.ibm.com&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_VIO_H
DECL|macro|_ASM_VIO_H
mdefine_line|#define _ASM_VIO_H
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;asm/hvcall.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
multiline_comment|/* &n; * Architecture-specific constants for drivers to&n; * extract attributes of the device using vio_get_attribute()&n;*/
DECL|macro|VETH_MAC_ADDR
mdefine_line|#define VETH_MAC_ADDR &quot;local-mac-address&quot;
DECL|macro|VETH_MCAST_FILTER_SIZE
mdefine_line|#define VETH_MCAST_FILTER_SIZE &quot;ibm,mac-address-filters&quot;
multiline_comment|/* End architecture-specific constants */
DECL|macro|h_vio_signal
mdefine_line|#define h_vio_signal(ua, mode) &bslash;&n;  plpar_hcall_norets(H_VIO_SIGNAL, ua, mode)
DECL|macro|VIO_IRQ_DISABLE
mdefine_line|#define VIO_IRQ_DISABLE&t;&t;0UL
DECL|macro|VIO_IRQ_ENABLE
mdefine_line|#define VIO_IRQ_ENABLE&t;&t;1UL
r_struct
id|vio_dev
suffix:semicolon
r_struct
id|vio_driver
suffix:semicolon
r_struct
id|vio_device_id
suffix:semicolon
r_struct
id|iommu_table
suffix:semicolon
r_int
id|vio_register_driver
c_func
(paren
r_struct
id|vio_driver
op_star
id|drv
)paren
suffix:semicolon
r_void
id|vio_unregister_driver
c_func
(paren
r_struct
id|vio_driver
op_star
id|drv
)paren
suffix:semicolon
r_const
r_struct
id|vio_device_id
op_star
id|vio_match_device
c_func
(paren
r_const
r_struct
id|vio_device_id
op_star
id|ids
comma
r_const
r_struct
id|vio_dev
op_star
id|dev
)paren
suffix:semicolon
r_struct
id|vio_dev
op_star
id|__devinit
id|vio_register_device
c_func
(paren
r_struct
id|device_node
op_star
id|node_vdev
)paren
suffix:semicolon
r_void
id|__devinit
id|vio_unregister_device
c_func
(paren
r_struct
id|vio_dev
op_star
id|dev
)paren
suffix:semicolon
r_struct
id|vio_dev
op_star
id|vio_find_node
c_func
(paren
r_struct
id|device_node
op_star
id|vnode
)paren
suffix:semicolon
r_const
r_void
op_star
id|vio_get_attribute
c_func
(paren
r_struct
id|vio_dev
op_star
id|vdev
comma
r_void
op_star
id|which
comma
r_int
op_star
id|length
)paren
suffix:semicolon
r_int
id|vio_get_irq
c_func
(paren
r_struct
id|vio_dev
op_star
id|dev
)paren
suffix:semicolon
r_struct
id|iommu_table
op_star
id|vio_build_iommu_table
c_func
(paren
r_struct
id|vio_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|vio_enable_interrupts
c_func
(paren
r_struct
id|vio_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|vio_disable_interrupts
c_func
(paren
r_struct
id|vio_dev
op_star
id|dev
)paren
suffix:semicolon
id|dma_addr_t
id|vio_map_single
c_func
(paren
r_struct
id|vio_dev
op_star
id|dev
comma
r_void
op_star
id|vaddr
comma
r_int
id|size
comma
r_enum
id|dma_data_direction
id|direction
)paren
suffix:semicolon
r_void
id|vio_unmap_single
c_func
(paren
r_struct
id|vio_dev
op_star
id|dev
comma
id|dma_addr_t
id|dma_handle
comma
r_int
id|size
comma
r_enum
id|dma_data_direction
id|direction
)paren
suffix:semicolon
r_int
id|vio_map_sg
c_func
(paren
r_struct
id|vio_dev
op_star
id|vdev
comma
r_struct
id|scatterlist
op_star
id|sglist
comma
r_int
id|nelems
comma
r_enum
id|dma_data_direction
id|direction
)paren
suffix:semicolon
r_void
id|vio_unmap_sg
c_func
(paren
r_struct
id|vio_dev
op_star
id|vdev
comma
r_struct
id|scatterlist
op_star
id|sglist
comma
r_int
id|nelems
comma
r_enum
id|dma_data_direction
id|direction
)paren
suffix:semicolon
r_void
op_star
id|vio_alloc_consistent
c_func
(paren
r_struct
id|vio_dev
op_star
id|dev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_handle
)paren
suffix:semicolon
r_void
id|vio_free_consistent
c_func
(paren
r_struct
id|vio_dev
op_star
id|dev
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
suffix:semicolon
DECL|function|vio_dma_supported
r_static
r_inline
r_int
id|vio_dma_supported
c_func
(paren
r_struct
id|vio_dev
op_star
id|hwdev
comma
id|u64
id|mask
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|macro|vio_map_page
mdefine_line|#define vio_map_page(dev, page, off, size, dir) &bslash;&n;&t;&t;vio_map_single(dev, (page_address(page) + (off)), size, dir)
DECL|macro|vio_unmap_page
mdefine_line|#define vio_unmap_page(dev,addr,sz,dir) vio_unmap_single(dev,addr,sz,dir)
DECL|function|vio_set_dma_mask
r_static
r_inline
r_int
id|vio_set_dma_mask
c_func
(paren
r_struct
id|vio_dev
op_star
id|dev
comma
id|u64
id|mask
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_extern
r_struct
id|bus_type
id|vio_bus_type
suffix:semicolon
DECL|struct|vio_device_id
r_struct
id|vio_device_id
(brace
DECL|member|type
r_char
op_star
id|type
suffix:semicolon
DECL|member|compat
r_char
op_star
id|compat
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vio_driver
r_struct
id|vio_driver
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id_table
r_const
r_struct
id|vio_device_id
op_star
id|id_table
suffix:semicolon
multiline_comment|/* NULL if wants all devices */
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_struct
id|vio_dev
op_star
id|dev
comma
r_const
r_struct
id|vio_device_id
op_star
id|id
)paren
suffix:semicolon
multiline_comment|/* New device inserted */
DECL|member|remove
r_int
(paren
op_star
id|remove
)paren
(paren
r_struct
id|vio_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Device removed (NULL if not a hot-plug capable driver) */
DECL|member|driver_data
r_int
r_int
id|driver_data
suffix:semicolon
DECL|member|driver
r_struct
id|device_driver
id|driver
suffix:semicolon
)brace
suffix:semicolon
DECL|function|to_vio_driver
r_static
r_inline
r_struct
id|vio_driver
op_star
id|to_vio_driver
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_return
id|container_of
c_func
(paren
id|drv
comma
r_struct
id|vio_driver
comma
id|driver
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The vio_dev structure is used to describe virtual I/O devices.&n; */
DECL|struct|vio_dev
r_struct
id|vio_dev
(brace
DECL|member|archdata
r_struct
id|device_node
op_star
id|archdata
suffix:semicolon
multiline_comment|/* Open Firmware node */
DECL|member|driver_data
r_void
op_star
id|driver_data
suffix:semicolon
multiline_comment|/* data private to the driver */
DECL|member|iommu_table
r_struct
id|iommu_table
op_star
id|iommu_table
suffix:semicolon
multiline_comment|/* vio_map_* uses this */
DECL|member|unit_address
r_uint32
id|unit_address
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
)brace
suffix:semicolon
DECL|function|to_vio_dev
r_static
r_inline
r_struct
id|vio_dev
op_star
id|to_vio_dev
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_return
id|container_of
c_func
(paren
id|dev
comma
r_struct
id|vio_dev
comma
id|dev
)paren
suffix:semicolon
)brace
macro_line|#endif /* _ASM_VIO_H */
eof
