multiline_comment|/*&n; * Header for Microchannel Architecture Bus&n; * Written by Martin Kolinek, February 1996&n; */
macro_line|#ifndef _LINUX_MCA_H
DECL|macro|_LINUX_MCA_H
mdefine_line|#define _LINUX_MCA_H
multiline_comment|/* FIXME: This shouldn&squot;t happen, but we need everything that previously&n; * included mca.h to compile.  Take it out later when the MCA #includes&n; * are sorted out */
macro_line|#include &lt;linux/device.h&gt;
multiline_comment|/* get the platform specific defines */
macro_line|#include &lt;asm/mca.h&gt;
multiline_comment|/* The detection of MCA bus is done in the real mode (using BIOS).&n; * The information is exported to the protected code, where this&n; * variable is set to one in case MCA bus was detected.&n; */
macro_line|#ifndef MCA_bus__is_a_macro
r_extern
r_int
id|MCA_bus
suffix:semicolon
macro_line|#endif
multiline_comment|/* This sets up an information callback for /proc/mca/slot?.  The&n; * function is called with the buffer, slot, and device pointer (or&n; * some equally informative context information, or nothing, if you&n; * prefer), and is expected to put useful information into the&n; * buffer.  The adapter name, id, and POS registers get printed&n; * before this is called though, so don&squot;t do it again.&n; *&n; * This should be called with a NULL procfn when a module&n; * unregisters, thus preventing kernel crashes and other such&n; * nastiness.&n; */
DECL|typedef|MCA_ProcFn
r_typedef
r_int
(paren
op_star
id|MCA_ProcFn
)paren
(paren
r_char
op_star
id|buf
comma
r_int
id|slot
comma
r_void
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Should only be called by the NMI interrupt handler, this will do some&n; * fancy stuff to figure out what might have generated a NMI.&n; */
r_extern
r_void
id|mca_handle_nmi
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|enum|MCA_AdapterStatus
r_enum
id|MCA_AdapterStatus
(brace
DECL|enumerator|MCA_ADAPTER_NORMAL
id|MCA_ADAPTER_NORMAL
op_assign
l_int|0
comma
DECL|enumerator|MCA_ADAPTER_NONE
id|MCA_ADAPTER_NONE
op_assign
l_int|1
comma
DECL|enumerator|MCA_ADAPTER_DISABLED
id|MCA_ADAPTER_DISABLED
op_assign
l_int|2
comma
DECL|enumerator|MCA_ADAPTER_ERROR
id|MCA_ADAPTER_ERROR
op_assign
l_int|3
)brace
suffix:semicolon
DECL|struct|mca_device
r_struct
id|mca_device
(brace
DECL|member|dma_mask
id|u64
id|dma_mask
suffix:semicolon
DECL|member|pos_id
r_int
id|pos_id
suffix:semicolon
DECL|member|slot
r_int
id|slot
suffix:semicolon
multiline_comment|/* index into id_table, set by the bus match routine */
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* is there a driver installed? 0 - No, 1 - Yes */
DECL|member|driver_loaded
r_int
id|driver_loaded
suffix:semicolon
multiline_comment|/* POS registers */
DECL|member|pos
r_int
r_char
id|pos
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* if a pseudo adapter of the motherboard, this is the motherboard&n;&t; * register value to use for setup cycles */
DECL|member|pos_register
r_int
id|pos_register
suffix:semicolon
DECL|member|status
r_enum
id|MCA_AdapterStatus
id|status
suffix:semicolon
macro_line|#ifdef CONFIG_MCA_PROC_FS
multiline_comment|/* name of the proc/mca file */
DECL|member|procname
r_char
id|procname
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* /proc info callback */
DECL|member|procfn
id|MCA_ProcFn
id|procfn
suffix:semicolon
multiline_comment|/* device/context info for proc callback */
DECL|member|proc_dev
r_void
op_star
id|proc_dev
suffix:semicolon
macro_line|#endif
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_mca_device
mdefine_line|#define to_mca_device(mdev) container_of(mdev, struct mca_device, dev)
DECL|struct|mca_bus_accessor_functions
r_struct
id|mca_bus_accessor_functions
(brace
DECL|member|mca_read_pos
r_int
r_char
(paren
op_star
id|mca_read_pos
)paren
(paren
r_struct
id|mca_device
op_star
comma
r_int
id|reg
)paren
suffix:semicolon
DECL|member|mca_write_pos
r_void
(paren
op_star
id|mca_write_pos
)paren
(paren
r_struct
id|mca_device
op_star
comma
r_int
id|reg
comma
r_int
r_char
id|byte
)paren
suffix:semicolon
DECL|member|mca_transform_irq
r_int
(paren
op_star
id|mca_transform_irq
)paren
(paren
r_struct
id|mca_device
op_star
comma
r_int
id|irq
)paren
suffix:semicolon
DECL|member|mca_transform_ioport
r_int
(paren
op_star
id|mca_transform_ioport
)paren
(paren
r_struct
id|mca_device
op_star
comma
r_int
id|region
)paren
suffix:semicolon
DECL|member|mca_transform_memory
r_void
op_star
(paren
op_star
id|mca_transform_memory
)paren
(paren
r_struct
id|mca_device
op_star
comma
r_void
op_star
id|memory
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mca_bus
r_struct
id|mca_bus
(brace
DECL|member|default_dma_mask
id|u64
id|default_dma_mask
suffix:semicolon
DECL|member|number
r_int
id|number
suffix:semicolon
DECL|member|f
r_struct
id|mca_bus_accessor_functions
id|f
suffix:semicolon
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_mca_bus
mdefine_line|#define to_mca_bus(mdev) container_of(mdev, struct mca_bus, dev)
DECL|struct|mca_driver
r_struct
id|mca_driver
(brace
DECL|member|id_table
r_const
r_int
op_star
id|id_table
suffix:semicolon
DECL|member|driver_data
r_void
op_star
id|driver_data
suffix:semicolon
DECL|member|driver
r_struct
id|device_driver
id|driver
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_mca_driver
mdefine_line|#define to_mca_driver(mdriver) container_of(mdriver, struct mca_driver, driver)
multiline_comment|/* Ongoing supported API functions */
r_extern
r_struct
id|mca_device
op_star
id|mca_find_device_by_slot
c_func
(paren
r_int
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|mca_system_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|mca_bus
op_star
id|mca_attach_bus
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
r_char
id|mca_device_read_stored_pos
c_func
(paren
r_struct
id|mca_device
op_star
id|mca_dev
comma
r_int
id|reg
)paren
suffix:semicolon
r_extern
r_int
r_char
id|mca_device_read_pos
c_func
(paren
r_struct
id|mca_device
op_star
id|mca_dev
comma
r_int
id|reg
)paren
suffix:semicolon
r_extern
r_void
id|mca_device_write_pos
c_func
(paren
r_struct
id|mca_device
op_star
id|mca_dev
comma
r_int
id|reg
comma
r_int
r_char
id|byte
)paren
suffix:semicolon
r_extern
r_int
id|mca_device_transform_irq
c_func
(paren
r_struct
id|mca_device
op_star
id|mca_dev
comma
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_int
id|mca_device_transform_ioport
c_func
(paren
r_struct
id|mca_device
op_star
id|mca_dev
comma
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
op_star
id|mca_device_transform_memory
c_func
(paren
r_struct
id|mca_device
op_star
id|mca_dev
comma
r_void
op_star
id|mem
)paren
suffix:semicolon
r_extern
r_int
id|mca_device_claimed
c_func
(paren
r_struct
id|mca_device
op_star
id|mca_dev
)paren
suffix:semicolon
r_extern
r_void
id|mca_device_set_claim
c_func
(paren
r_struct
id|mca_device
op_star
id|mca_dev
comma
r_int
id|val
)paren
suffix:semicolon
r_extern
r_void
id|mca_device_set_name
c_func
(paren
r_struct
id|mca_device
op_star
id|mca_dev
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
DECL|function|mca_device_get_name
r_static
r_inline
r_char
op_star
id|mca_device_get_name
c_func
(paren
r_struct
id|mca_device
op_star
id|mca_dev
)paren
(brace
r_return
id|mca_dev
ques
c_cond
id|mca_dev-&gt;name
suffix:colon
l_int|NULL
suffix:semicolon
)brace
r_extern
r_enum
id|MCA_AdapterStatus
id|mca_device_status
c_func
(paren
r_struct
id|mca_device
op_star
id|mca_dev
)paren
suffix:semicolon
r_extern
r_struct
id|bus_type
id|mca_bus_type
suffix:semicolon
r_extern
r_int
id|mca_register_driver
c_func
(paren
r_struct
id|mca_driver
op_star
id|drv
)paren
suffix:semicolon
r_extern
r_void
id|mca_unregister_driver
c_func
(paren
r_struct
id|mca_driver
op_star
id|drv
)paren
suffix:semicolon
multiline_comment|/* WARNING: only called by the boot time device setup */
r_extern
r_int
id|mca_register_device
c_func
(paren
r_int
id|bus
comma
r_struct
id|mca_device
op_star
id|mca_dev
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MCA_LEGACY
macro_line|#include &lt;linux/mca-legacy.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_MCA_PROC_FS
r_extern
r_void
id|mca_do_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mca_set_adapter_procfn
c_func
(paren
r_int
id|slot
comma
id|MCA_ProcFn
comma
r_void
op_star
id|dev
)paren
suffix:semicolon
macro_line|#else
DECL|function|mca_do_proc_init
r_static
r_inline
r_void
id|mca_do_proc_init
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|mca_set_adapter_procfn
r_static
r_inline
r_void
id|mca_set_adapter_procfn
c_func
(paren
r_int
id|slot
comma
id|MCA_ProcFn
op_star
id|fn
comma
r_void
op_star
id|dev
)paren
(brace
)brace
macro_line|#endif
macro_line|#endif /* _LINUX_MCA_H */
eof
