macro_line|#include &lt;linux/device.h&gt;
DECL|struct|parisc_device
r_struct
id|parisc_device
(brace
DECL|member|hpa
r_int
r_int
id|hpa
suffix:semicolon
multiline_comment|/* Hard Physical Address */
DECL|member|id
r_struct
id|parisc_device_id
id|id
suffix:semicolon
DECL|member|parent
r_struct
id|parisc_device
op_star
id|parent
suffix:semicolon
DECL|member|sibling
r_struct
id|parisc_device
op_star
id|sibling
suffix:semicolon
DECL|member|child
r_struct
id|parisc_device
op_star
id|child
suffix:semicolon
DECL|member|driver
r_struct
id|parisc_driver
op_star
id|driver
suffix:semicolon
multiline_comment|/* Driver for this device */
DECL|member|sysdata
r_void
op_star
id|sysdata
suffix:semicolon
multiline_comment|/* Driver instance private data */
DECL|member|name
r_char
id|name
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* The hardware description */
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|hw_path
r_char
id|hw_path
suffix:semicolon
multiline_comment|/* The module number on this bus */
DECL|member|num_addrs
r_int
r_int
id|num_addrs
suffix:semicolon
multiline_comment|/* some devices have additional address ranges. */
DECL|member|addr
r_int
r_int
op_star
id|addr
suffix:semicolon
multiline_comment|/* which will be stored here */
macro_line|#ifdef __LP64__
multiline_comment|/* parms for pdc_pat_cell_module() call */
DECL|member|pcell_loc
r_int
r_int
id|pcell_loc
suffix:semicolon
multiline_comment|/* Physical Cell location */
DECL|member|mod_index
r_int
r_int
id|mod_index
suffix:semicolon
multiline_comment|/* PAT specific - Misc Module info */
multiline_comment|/* generic info returned from pdc_pat_cell_module() */
DECL|member|mod_info
r_int
r_int
id|mod_info
suffix:semicolon
multiline_comment|/* PAT specific - Misc Module info */
DECL|member|pmod_loc
r_int
r_int
id|pmod_loc
suffix:semicolon
multiline_comment|/* physical Module location */
macro_line|#endif
DECL|member|dma_mask
id|u64
id|dma_mask
suffix:semicolon
multiline_comment|/* DMA mask for I/O */
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|parisc_driver
r_struct
id|parisc_driver
(brace
DECL|member|next
r_struct
id|parisc_driver
op_star
id|next
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id_table
r_const
r_struct
id|parisc_device_id
op_star
id|id_table
suffix:semicolon
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_struct
id|parisc_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* New device discovered */
DECL|member|drv
r_struct
id|device_driver
id|drv
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_parisc_device
mdefine_line|#define to_parisc_device(d)&t;container_of(d, struct parisc_device, dev)
DECL|macro|to_parisc_driver
mdefine_line|#define to_parisc_driver(d)&t;container_of(d, struct parisc_driver, drv)
r_extern
r_struct
id|bus_type
id|parisc_bus_type
suffix:semicolon
eof
