macro_line|#ifndef _LINUX_EISA_H
DECL|macro|_LINUX_EISA_H
mdefine_line|#define _LINUX_EISA_H
DECL|macro|EISA_SIG_LEN
mdefine_line|#define EISA_SIG_LEN   8
DECL|macro|EISA_MAX_SLOTS
mdefine_line|#define EISA_MAX_SLOTS 8
DECL|macro|EISA_MAX_RESOURCES
mdefine_line|#define EISA_MAX_RESOURCES 4
multiline_comment|/* A few EISA constants/offsets... */
DECL|macro|EISA_DMA1_STATUS
mdefine_line|#define EISA_DMA1_STATUS            8
DECL|macro|EISA_INT1_CTRL
mdefine_line|#define EISA_INT1_CTRL           0x20
DECL|macro|EISA_INT1_MASK
mdefine_line|#define EISA_INT1_MASK           0x21
DECL|macro|EISA_INT2_CTRL
mdefine_line|#define EISA_INT2_CTRL           0xA0
DECL|macro|EISA_INT2_MASK
mdefine_line|#define EISA_INT2_MASK           0xA1
DECL|macro|EISA_DMA2_STATUS
mdefine_line|#define EISA_DMA2_STATUS         0xD0
DECL|macro|EISA_DMA2_WRITE_SINGLE
mdefine_line|#define EISA_DMA2_WRITE_SINGLE   0xD4
DECL|macro|EISA_EXT_NMI_RESET_CTRL
mdefine_line|#define EISA_EXT_NMI_RESET_CTRL 0x461
DECL|macro|EISA_INT1_EDGE_LEVEL
mdefine_line|#define EISA_INT1_EDGE_LEVEL    0x4D0
DECL|macro|EISA_INT2_EDGE_LEVEL
mdefine_line|#define EISA_INT2_EDGE_LEVEL    0x4D1
DECL|macro|EISA_VENDOR_ID_OFFSET
mdefine_line|#define EISA_VENDOR_ID_OFFSET   0xC80
DECL|macro|EISA_CONFIG_OFFSET
mdefine_line|#define EISA_CONFIG_OFFSET      0xC84
DECL|macro|EISA_CONFIG_ENABLED
mdefine_line|#define EISA_CONFIG_ENABLED         1
DECL|macro|EISA_CONFIG_FORCED
mdefine_line|#define EISA_CONFIG_FORCED          2
multiline_comment|/* The EISA signature, in ASCII form, null terminated */
DECL|struct|eisa_device_id
r_struct
id|eisa_device_id
(brace
DECL|member|sig
r_char
id|sig
(braket
id|EISA_SIG_LEN
)braket
suffix:semicolon
DECL|member|driver_data
r_int
r_int
id|driver_data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* There is not much we can say about an EISA device, apart from&n; * signature, slot number, and base address. dma_mask is set by&n; * default to parent device mask..*/
DECL|struct|eisa_device
r_struct
id|eisa_device
(brace
DECL|member|id
r_struct
id|eisa_device_id
id|id
suffix:semicolon
DECL|member|slot
r_int
id|slot
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|base_addr
r_int
r_int
id|base_addr
suffix:semicolon
DECL|member|res
r_struct
id|resource
id|res
(braket
id|EISA_MAX_RESOURCES
)braket
suffix:semicolon
DECL|member|dma_mask
id|u64
id|dma_mask
suffix:semicolon
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* generic device */
macro_line|#ifdef CONFIG_EISA_NAMES
DECL|member|pretty_name
r_char
id|pretty_name
(braket
id|DEVICE_NAME_SIZE
)braket
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|to_eisa_device
mdefine_line|#define to_eisa_device(n) container_of(n, struct eisa_device, dev)
DECL|function|eisa_get_region_index
r_static
r_inline
r_int
id|eisa_get_region_index
(paren
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|x
op_assign
(paren
r_int
r_int
)paren
id|addr
suffix:semicolon
id|x
op_and_assign
l_int|0xc00
suffix:semicolon
r_return
(paren
id|x
op_rshift
l_int|12
)paren
suffix:semicolon
)brace
DECL|struct|eisa_driver
r_struct
id|eisa_driver
(brace
DECL|member|id_table
r_const
r_struct
id|eisa_device_id
op_star
id|id_table
suffix:semicolon
DECL|member|driver
r_struct
id|device_driver
id|driver
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_eisa_driver
mdefine_line|#define to_eisa_driver(drv) container_of(drv,struct eisa_driver, driver)
r_extern
r_struct
id|bus_type
id|eisa_bus_type
suffix:semicolon
r_int
id|eisa_driver_register
(paren
r_struct
id|eisa_driver
op_star
id|edrv
)paren
suffix:semicolon
r_void
id|eisa_driver_unregister
(paren
r_struct
id|eisa_driver
op_star
id|edrv
)paren
suffix:semicolon
multiline_comment|/* Mimics pci.h... */
DECL|function|eisa_get_drvdata
r_static
r_inline
r_void
op_star
id|eisa_get_drvdata
(paren
r_struct
id|eisa_device
op_star
id|edev
)paren
(brace
r_return
id|edev-&gt;dev.driver_data
suffix:semicolon
)brace
DECL|function|eisa_set_drvdata
r_static
r_inline
r_void
id|eisa_set_drvdata
(paren
r_struct
id|eisa_device
op_star
id|edev
comma
r_void
op_star
id|data
)paren
(brace
id|edev-&gt;dev.driver_data
op_assign
id|data
suffix:semicolon
)brace
multiline_comment|/* The EISA root device. There&squot;s rumours about machines with multiple&n; * busses (PA-RISC ?), so we try to handle that. */
DECL|struct|eisa_root_device
r_struct
id|eisa_root_device
(brace
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Pointer to bridge device */
DECL|member|res
r_struct
id|resource
op_star
id|res
suffix:semicolon
DECL|member|bus_base_addr
r_int
r_int
id|bus_base_addr
suffix:semicolon
DECL|member|slots
r_int
id|slots
suffix:semicolon
multiline_comment|/* Max slot number */
DECL|member|force_probe
r_int
id|force_probe
suffix:semicolon
multiline_comment|/* Probe even when no slot 0 */
DECL|member|dma_mask
id|u64
id|dma_mask
suffix:semicolon
multiline_comment|/* from bridge device */
DECL|member|bus_nr
r_int
id|bus_nr
suffix:semicolon
multiline_comment|/* Set by eisa_root_register */
DECL|member|eisa_root_res
r_struct
id|resource
id|eisa_root_res
suffix:semicolon
multiline_comment|/* ditto */
)brace
suffix:semicolon
r_int
id|eisa_root_register
(paren
r_struct
id|eisa_root_device
op_star
id|root
)paren
suffix:semicolon
macro_line|#endif
eof
