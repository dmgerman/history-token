multiline_comment|/*&n; * I2O user space accessible structures/APIs&n; * &n; * (c) Copyright 1999, 2000 Red Hat Software&n; *&n; * This program is free software; you can redistribute it and/or &n; * modify it under the terms of the GNU General Public License &n; * as published by the Free Software Foundation; either version &n; * 2 of the License, or (at your option) any later version.  &n; * &n; *************************************************************************&n; *&n; * This header file defines the I2O APIs that are available to both&n; * the kernel and user level applications.  Kernel specific structures&n; * are defined in i2o_osm. OSMs should include _only_ i2o_osm.h which&n; * automatically includs this file.&n; *&n; */
macro_line|#ifndef _I2O_DEV_H
DECL|macro|_I2O_DEV_H
mdefine_line|#define _I2O_DEV_H
multiline_comment|/* How many controllers are we allowing */
DECL|macro|MAX_I2O_CONTROLLERS
mdefine_line|#define MAX_I2O_CONTROLLERS&t;32
macro_line|#include &lt;linux/ioctl.h&gt;
multiline_comment|/*&n; * I2O Control IOCTLs and structures&n; */
DECL|macro|I2O_MAGIC_NUMBER
mdefine_line|#define I2O_MAGIC_NUMBER&t;&squot;i&squot;
DECL|macro|I2OGETIOPS
mdefine_line|#define I2OGETIOPS&t;&t;_IOR(I2O_MAGIC_NUMBER,0,u8[MAX_I2O_CONTROLLERS])
DECL|macro|I2OHRTGET
mdefine_line|#define I2OHRTGET&t;&t;_IOWR(I2O_MAGIC_NUMBER,1,struct i2o_cmd_hrtlct)
DECL|macro|I2OLCTGET
mdefine_line|#define I2OLCTGET&t;&t;_IOWR(I2O_MAGIC_NUMBER,2,struct i2o_cmd_hrtlct)
DECL|macro|I2OPARMSET
mdefine_line|#define I2OPARMSET&t;&t;_IOWR(I2O_MAGIC_NUMBER,3,struct i2o_cmd_psetget)
DECL|macro|I2OPARMGET
mdefine_line|#define I2OPARMGET&t;&t;_IOWR(I2O_MAGIC_NUMBER,4,struct i2o_cmd_psetget)
DECL|macro|I2OSWDL
mdefine_line|#define I2OSWDL&t;&t;&t;_IOWR(I2O_MAGIC_NUMBER,5,struct i2o_sw_xfer)
DECL|macro|I2OSWUL
mdefine_line|#define I2OSWUL&t;&t;&t;_IOWR(I2O_MAGIC_NUMBER,6,struct i2o_sw_xfer)
DECL|macro|I2OSWDEL
mdefine_line|#define I2OSWDEL&t;&t;_IOWR(I2O_MAGIC_NUMBER,7,struct i2o_sw_xfer)
DECL|macro|I2OVALIDATE
mdefine_line|#define I2OVALIDATE&t;&t;_IOR(I2O_MAGIC_NUMBER,8,u32)
DECL|macro|I2OHTML
mdefine_line|#define I2OHTML&t;&t;&t;_IOWR(I2O_MAGIC_NUMBER,9,struct i2o_html)
DECL|macro|I2OEVTREG
mdefine_line|#define I2OEVTREG&t;&t;_IOW(I2O_MAGIC_NUMBER,10,struct i2o_evt_id)
DECL|macro|I2OEVTGET
mdefine_line|#define I2OEVTGET&t;&t;_IOR(I2O_MAGIC_NUMBER,11,struct i2o_evt_info)
DECL|struct|i2o_cmd_hrtlct
r_struct
id|i2o_cmd_hrtlct
(brace
DECL|member|iop
r_int
r_int
id|iop
suffix:semicolon
multiline_comment|/* IOP unit number */
DECL|member|resbuf
r_void
op_star
id|resbuf
suffix:semicolon
multiline_comment|/* Buffer for result */
DECL|member|reslen
r_int
r_int
op_star
id|reslen
suffix:semicolon
multiline_comment|/* Buffer length in bytes */
)brace
suffix:semicolon
DECL|struct|i2o_cmd_psetget
r_struct
id|i2o_cmd_psetget
(brace
DECL|member|iop
r_int
r_int
id|iop
suffix:semicolon
multiline_comment|/* IOP unit number */
DECL|member|tid
r_int
r_int
id|tid
suffix:semicolon
multiline_comment|/* Target device TID */
DECL|member|opbuf
r_void
op_star
id|opbuf
suffix:semicolon
multiline_comment|/* Operation List buffer */
DECL|member|oplen
r_int
r_int
id|oplen
suffix:semicolon
multiline_comment|/* Operation List buffer length in bytes */
DECL|member|resbuf
r_void
op_star
id|resbuf
suffix:semicolon
multiline_comment|/* Result List buffer */
DECL|member|reslen
r_int
r_int
op_star
id|reslen
suffix:semicolon
multiline_comment|/* Result List buffer length in bytes */
)brace
suffix:semicolon
DECL|struct|i2o_sw_xfer
r_struct
id|i2o_sw_xfer
(brace
DECL|member|iop
r_int
r_int
id|iop
suffix:semicolon
multiline_comment|/* IOP unit number */
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* Flags field */
DECL|member|sw_type
r_int
r_char
id|sw_type
suffix:semicolon
multiline_comment|/* Software type */
DECL|member|sw_id
r_int
r_int
id|sw_id
suffix:semicolon
multiline_comment|/* Software ID */
DECL|member|buf
r_void
op_star
id|buf
suffix:semicolon
multiline_comment|/* Pointer to software buffer */
DECL|member|swlen
r_int
r_int
op_star
id|swlen
suffix:semicolon
multiline_comment|/* Length of software data */
DECL|member|maxfrag
r_int
r_int
op_star
id|maxfrag
suffix:semicolon
multiline_comment|/* Maximum fragment count */
DECL|member|curfrag
r_int
r_int
op_star
id|curfrag
suffix:semicolon
multiline_comment|/* Current fragment count */
)brace
suffix:semicolon
DECL|struct|i2o_html
r_struct
id|i2o_html
(brace
DECL|member|iop
r_int
r_int
id|iop
suffix:semicolon
multiline_comment|/* IOP unit number */
DECL|member|tid
r_int
r_int
id|tid
suffix:semicolon
multiline_comment|/* Target device ID */
DECL|member|page
r_int
r_int
id|page
suffix:semicolon
multiline_comment|/* HTML page */
DECL|member|resbuf
r_void
op_star
id|resbuf
suffix:semicolon
multiline_comment|/* Buffer for reply HTML page */
DECL|member|reslen
r_int
r_int
op_star
id|reslen
suffix:semicolon
multiline_comment|/* Length in bytes of reply buffer */
DECL|member|qbuf
r_void
op_star
id|qbuf
suffix:semicolon
multiline_comment|/* Pointer to HTTP query string */
DECL|member|qlen
r_int
r_int
id|qlen
suffix:semicolon
multiline_comment|/* Length in bytes of query string buffer */
)brace
suffix:semicolon
DECL|macro|I2O_EVT_Q_LEN
mdefine_line|#define I2O_EVT_Q_LEN 32
DECL|struct|i2o_evt_id
r_struct
id|i2o_evt_id
(brace
DECL|member|iop
r_int
r_int
id|iop
suffix:semicolon
DECL|member|tid
r_int
r_int
id|tid
suffix:semicolon
DECL|member|evt_mask
r_int
r_int
id|evt_mask
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Event data size = frame size - message header + evt indicator */
DECL|macro|I2O_EVT_DATA_SIZE
mdefine_line|#define I2O_EVT_DATA_SIZE 88
DECL|struct|i2o_evt_info
r_struct
id|i2o_evt_info
(brace
DECL|member|id
r_struct
id|i2o_evt_id
id|id
suffix:semicolon
DECL|member|evt_data
r_int
r_char
id|evt_data
(braket
id|I2O_EVT_DATA_SIZE
)braket
suffix:semicolon
DECL|member|data_size
r_int
r_int
id|data_size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|i2o_evt_get
r_struct
id|i2o_evt_get
(brace
DECL|member|info
r_struct
id|i2o_evt_info
id|info
suffix:semicolon
DECL|member|pending
r_int
id|pending
suffix:semicolon
DECL|member|lost
r_int
id|lost
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**************************************************************************&n; * HRT related constants and structures&n; **************************************************************************/
DECL|macro|I2O_BUS_LOCAL
mdefine_line|#define I2O_BUS_LOCAL&t;0
DECL|macro|I2O_BUS_ISA
mdefine_line|#define I2O_BUS_ISA&t;1
DECL|macro|I2O_BUS_EISA
mdefine_line|#define I2O_BUS_EISA&t;2
DECL|macro|I2O_BUS_MCA
mdefine_line|#define I2O_BUS_MCA&t;3
DECL|macro|I2O_BUS_PCI
mdefine_line|#define I2O_BUS_PCI&t;4
DECL|macro|I2O_BUS_PCMCIA
mdefine_line|#define I2O_BUS_PCMCIA&t;5
DECL|macro|I2O_BUS_NUBUS
mdefine_line|#define I2O_BUS_NUBUS&t;6
DECL|macro|I2O_BUS_CARDBUS
mdefine_line|#define I2O_BUS_CARDBUS&t;7
DECL|macro|I2O_BUS_UNKNOWN
mdefine_line|#define I2O_BUS_UNKNOWN&t;0x80
macro_line|#ifndef __KERNEL__
DECL|typedef|u8
r_typedef
r_int
r_char
id|u8
suffix:semicolon
DECL|typedef|u16
r_typedef
r_int
r_int
id|u16
suffix:semicolon
DECL|typedef|u32
r_typedef
r_int
r_int
id|u32
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
DECL|struct|_i2o_pci_bus
r_typedef
r_struct
id|_i2o_pci_bus
(brace
DECL|member|PciFunctionNumber
id|u8
id|PciFunctionNumber
suffix:semicolon
DECL|member|PciDeviceNumber
id|u8
id|PciDeviceNumber
suffix:semicolon
DECL|member|PciBusNumber
id|u8
id|PciBusNumber
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|PciVendorID
id|u16
id|PciVendorID
suffix:semicolon
DECL|member|PciDeviceID
id|u16
id|PciDeviceID
suffix:semicolon
DECL|typedef|i2o_pci_bus
)brace
id|i2o_pci_bus
suffix:semicolon
DECL|struct|_i2o_local_bus
r_typedef
r_struct
id|_i2o_local_bus
(brace
DECL|member|LbBaseIOPort
id|u16
id|LbBaseIOPort
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|member|LbBaseMemoryAddress
id|u32
id|LbBaseMemoryAddress
suffix:semicolon
DECL|typedef|i2o_local_bus
)brace
id|i2o_local_bus
suffix:semicolon
DECL|struct|_i2o_isa_bus
r_typedef
r_struct
id|_i2o_isa_bus
(brace
DECL|member|IsaBaseIOPort
id|u16
id|IsaBaseIOPort
suffix:semicolon
DECL|member|CSN
id|u8
id|CSN
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|IsaBaseMemoryAddress
id|u32
id|IsaBaseMemoryAddress
suffix:semicolon
DECL|typedef|i2o_isa_bus
)brace
id|i2o_isa_bus
suffix:semicolon
DECL|struct|_i2o_eisa_bus_info
r_typedef
r_struct
id|_i2o_eisa_bus_info
(brace
DECL|member|EisaBaseIOPort
id|u16
id|EisaBaseIOPort
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|EisaSlotNumber
id|u8
id|EisaSlotNumber
suffix:semicolon
DECL|member|EisaBaseMemoryAddress
id|u32
id|EisaBaseMemoryAddress
suffix:semicolon
DECL|typedef|i2o_eisa_bus
)brace
id|i2o_eisa_bus
suffix:semicolon
DECL|struct|_i2o_mca_bus
r_typedef
r_struct
id|_i2o_mca_bus
(brace
DECL|member|McaBaseIOPort
id|u16
id|McaBaseIOPort
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|McaSlotNumber
id|u8
id|McaSlotNumber
suffix:semicolon
DECL|member|McaBaseMemoryAddress
id|u32
id|McaBaseMemoryAddress
suffix:semicolon
DECL|typedef|i2o_mca_bus
)brace
id|i2o_mca_bus
suffix:semicolon
DECL|struct|_i2o_other_bus
r_typedef
r_struct
id|_i2o_other_bus
(brace
DECL|member|BaseIOPort
id|u16
id|BaseIOPort
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|member|BaseMemoryAddress
id|u32
id|BaseMemoryAddress
suffix:semicolon
DECL|typedef|i2o_other_bus
)brace
id|i2o_other_bus
suffix:semicolon
DECL|struct|_i2o_hrt_entry
r_typedef
r_struct
id|_i2o_hrt_entry
(brace
DECL|member|adapter_id
id|u32
id|adapter_id
suffix:semicolon
DECL|member|parent_tid
id|u32
id|parent_tid
suffix:colon
l_int|12
suffix:semicolon
DECL|member|state
id|u32
id|state
suffix:colon
l_int|4
suffix:semicolon
DECL|member|bus_num
id|u32
id|bus_num
suffix:colon
l_int|8
suffix:semicolon
DECL|member|bus_type
id|u32
id|bus_type
suffix:colon
l_int|8
suffix:semicolon
r_union
(brace
DECL|member|pci_bus
id|i2o_pci_bus
id|pci_bus
suffix:semicolon
DECL|member|local_bus
id|i2o_local_bus
id|local_bus
suffix:semicolon
DECL|member|isa_bus
id|i2o_isa_bus
id|isa_bus
suffix:semicolon
DECL|member|eisa_bus
id|i2o_eisa_bus
id|eisa_bus
suffix:semicolon
DECL|member|mca_bus
id|i2o_mca_bus
id|mca_bus
suffix:semicolon
DECL|member|other_bus
id|i2o_other_bus
id|other_bus
suffix:semicolon
DECL|member|bus
)brace
id|bus
suffix:semicolon
DECL|typedef|i2o_hrt_entry
)brace
id|i2o_hrt_entry
suffix:semicolon
DECL|struct|_i2o_hrt
r_typedef
r_struct
id|_i2o_hrt
(brace
DECL|member|num_entries
id|u16
id|num_entries
suffix:semicolon
DECL|member|entry_len
id|u8
id|entry_len
suffix:semicolon
DECL|member|hrt_version
id|u8
id|hrt_version
suffix:semicolon
DECL|member|change_ind
id|u32
id|change_ind
suffix:semicolon
DECL|member|hrt_entry
id|i2o_hrt_entry
id|hrt_entry
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|i2o_hrt
)brace
id|i2o_hrt
suffix:semicolon
DECL|struct|_i2o_lct_entry
r_typedef
r_struct
id|_i2o_lct_entry
(brace
DECL|member|entry_size
id|u32
id|entry_size
suffix:colon
l_int|16
suffix:semicolon
DECL|member|tid
id|u32
id|tid
suffix:colon
l_int|12
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:colon
l_int|4
suffix:semicolon
DECL|member|change_ind
id|u32
id|change_ind
suffix:semicolon
DECL|member|device_flags
id|u32
id|device_flags
suffix:semicolon
DECL|member|class_id
id|u32
id|class_id
suffix:colon
l_int|12
suffix:semicolon
DECL|member|version
id|u32
id|version
suffix:colon
l_int|4
suffix:semicolon
DECL|member|vendor_id
id|u32
id|vendor_id
suffix:colon
l_int|16
suffix:semicolon
DECL|member|sub_class
id|u32
id|sub_class
suffix:semicolon
DECL|member|user_tid
id|u32
id|user_tid
suffix:colon
l_int|12
suffix:semicolon
DECL|member|parent_tid
id|u32
id|parent_tid
suffix:colon
l_int|12
suffix:semicolon
DECL|member|bios_info
id|u32
id|bios_info
suffix:colon
l_int|8
suffix:semicolon
DECL|member|identity_tag
id|u8
id|identity_tag
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|event_capabilities
id|u32
id|event_capabilities
suffix:semicolon
DECL|typedef|i2o_lct_entry
)brace
id|i2o_lct_entry
suffix:semicolon
DECL|struct|_i2o_lct
r_typedef
r_struct
id|_i2o_lct
(brace
DECL|member|table_size
id|u32
id|table_size
suffix:colon
l_int|16
suffix:semicolon
DECL|member|boot_tid
id|u32
id|boot_tid
suffix:colon
l_int|12
suffix:semicolon
DECL|member|lct_ver
id|u32
id|lct_ver
suffix:colon
l_int|4
suffix:semicolon
DECL|member|iop_flags
id|u32
id|iop_flags
suffix:semicolon
DECL|member|change_ind
id|u32
id|change_ind
suffix:semicolon
DECL|member|lct_entry
id|i2o_lct_entry
id|lct_entry
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|i2o_lct
)brace
id|i2o_lct
suffix:semicolon
DECL|struct|_i2o_status_block
r_typedef
r_struct
id|_i2o_status_block
(brace
DECL|member|org_id
id|u16
id|org_id
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|member|iop_id
id|u16
id|iop_id
suffix:colon
l_int|12
suffix:semicolon
DECL|member|reserved1
id|u16
id|reserved1
suffix:colon
l_int|4
suffix:semicolon
DECL|member|host_unit_id
id|u16
id|host_unit_id
suffix:semicolon
DECL|member|segment_number
id|u16
id|segment_number
suffix:colon
l_int|12
suffix:semicolon
DECL|member|i2o_version
id|u16
id|i2o_version
suffix:colon
l_int|4
suffix:semicolon
DECL|member|iop_state
id|u8
id|iop_state
suffix:semicolon
DECL|member|msg_type
id|u8
id|msg_type
suffix:semicolon
DECL|member|inbound_frame_size
id|u16
id|inbound_frame_size
suffix:semicolon
DECL|member|init_code
id|u8
id|init_code
suffix:semicolon
DECL|member|reserved2
id|u8
id|reserved2
suffix:semicolon
DECL|member|max_inbound_frames
id|u32
id|max_inbound_frames
suffix:semicolon
DECL|member|cur_inbound_frames
id|u32
id|cur_inbound_frames
suffix:semicolon
DECL|member|max_outbound_frames
id|u32
id|max_outbound_frames
suffix:semicolon
DECL|member|product_id
r_char
id|product_id
(braket
l_int|24
)braket
suffix:semicolon
DECL|member|expected_lct_size
id|u32
id|expected_lct_size
suffix:semicolon
DECL|member|iop_capabilities
id|u32
id|iop_capabilities
suffix:semicolon
DECL|member|desired_mem_size
id|u32
id|desired_mem_size
suffix:semicolon
DECL|member|current_mem_size
id|u32
id|current_mem_size
suffix:semicolon
DECL|member|current_mem_base
id|u32
id|current_mem_base
suffix:semicolon
DECL|member|desired_io_size
id|u32
id|desired_io_size
suffix:semicolon
DECL|member|current_io_size
id|u32
id|current_io_size
suffix:semicolon
DECL|member|current_io_base
id|u32
id|current_io_base
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:colon
l_int|24
suffix:semicolon
DECL|member|cmd_status
id|u32
id|cmd_status
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|i2o_status_block
)brace
id|i2o_status_block
suffix:semicolon
multiline_comment|/* Event indicator mask flags */
DECL|macro|I2O_EVT_IND_STATE_CHANGE
mdefine_line|#define I2O_EVT_IND_STATE_CHANGE&t;&t;0x80000000
DECL|macro|I2O_EVT_IND_GENERAL_WARNING
mdefine_line|#define I2O_EVT_IND_GENERAL_WARNING&t;&t;0x40000000
DECL|macro|I2O_EVT_IND_CONFIGURATION_FLAG
mdefine_line|#define I2O_EVT_IND_CONFIGURATION_FLAG&t;&t;0x20000000
DECL|macro|I2O_EVT_IND_LOCK_RELEASE
mdefine_line|#define I2O_EVT_IND_LOCK_RELEASE&t;&t;0x10000000
DECL|macro|I2O_EVT_IND_CAPABILITY_CHANGE
mdefine_line|#define I2O_EVT_IND_CAPABILITY_CHANGE&t;&t;0x08000000
DECL|macro|I2O_EVT_IND_DEVICE_RESET
mdefine_line|#define I2O_EVT_IND_DEVICE_RESET&t;&t;0x04000000
DECL|macro|I2O_EVT_IND_EVT_MASK_MODIFIED
mdefine_line|#define I2O_EVT_IND_EVT_MASK_MODIFIED&t;&t;0x02000000
DECL|macro|I2O_EVT_IND_FIELD_MODIFIED
mdefine_line|#define I2O_EVT_IND_FIELD_MODIFIED&t;&t;0x01000000
DECL|macro|I2O_EVT_IND_VENDOR_EVT
mdefine_line|#define I2O_EVT_IND_VENDOR_EVT&t;&t;&t;0x00800000
DECL|macro|I2O_EVT_IND_DEVICE_STATE
mdefine_line|#define I2O_EVT_IND_DEVICE_STATE&t;&t;0x00400000
multiline_comment|/* Executive event indicitors */
DECL|macro|I2O_EVT_IND_EXEC_RESOURCE_LIMITS
mdefine_line|#define I2O_EVT_IND_EXEC_RESOURCE_LIMITS&t;0x00000001
DECL|macro|I2O_EVT_IND_EXEC_CONNECTION_FAIL
mdefine_line|#define I2O_EVT_IND_EXEC_CONNECTION_FAIL&t;0x00000002
DECL|macro|I2O_EVT_IND_EXEC_ADAPTER_FAULT
mdefine_line|#define I2O_EVT_IND_EXEC_ADAPTER_FAULT&t;&t;0x00000004
DECL|macro|I2O_EVT_IND_EXEC_POWER_FAIL
mdefine_line|#define I2O_EVT_IND_EXEC_POWER_FAIL&t;&t;0x00000008
DECL|macro|I2O_EVT_IND_EXEC_RESET_PENDING
mdefine_line|#define I2O_EVT_IND_EXEC_RESET_PENDING&t;&t;0x00000010
DECL|macro|I2O_EVT_IND_EXEC_RESET_IMMINENT
mdefine_line|#define I2O_EVT_IND_EXEC_RESET_IMMINENT&t;&t;0x00000020
DECL|macro|I2O_EVT_IND_EXEC_HW_FAIL
mdefine_line|#define I2O_EVT_IND_EXEC_HW_FAIL&t;&t;0x00000040
DECL|macro|I2O_EVT_IND_EXEC_XCT_CHANGE
mdefine_line|#define I2O_EVT_IND_EXEC_XCT_CHANGE&t;&t;0x00000080
DECL|macro|I2O_EVT_IND_EXEC_NEW_LCT_ENTRY
mdefine_line|#define I2O_EVT_IND_EXEC_NEW_LCT_ENTRY&t;&t;0x00000100
DECL|macro|I2O_EVT_IND_EXEC_MODIFIED_LCT
mdefine_line|#define I2O_EVT_IND_EXEC_MODIFIED_LCT&t;&t;0x00000200
DECL|macro|I2O_EVT_IND_EXEC_DDM_AVAILABILITY
mdefine_line|#define I2O_EVT_IND_EXEC_DDM_AVAILABILITY&t;0x00000400
multiline_comment|/* Random Block Storage Event Indicators */
DECL|macro|I2O_EVT_IND_BSA_VOLUME_LOAD
mdefine_line|#define I2O_EVT_IND_BSA_VOLUME_LOAD&t;&t;0x00000001
DECL|macro|I2O_EVT_IND_BSA_VOLUME_UNLOAD
mdefine_line|#define I2O_EVT_IND_BSA_VOLUME_UNLOAD&t;&t;0x00000002
DECL|macro|I2O_EVT_IND_BSA_VOLUME_UNLOAD_REQ
mdefine_line|#define I2O_EVT_IND_BSA_VOLUME_UNLOAD_REQ&t;0x00000004
DECL|macro|I2O_EVT_IND_BSA_CAPACITY_CHANGE
mdefine_line|#define I2O_EVT_IND_BSA_CAPACITY_CHANGE&t;&t;0x00000008
DECL|macro|I2O_EVT_IND_BSA_SCSI_SMART
mdefine_line|#define I2O_EVT_IND_BSA_SCSI_SMART&t;&t;0x00000010
multiline_comment|/* Event data for generic events */
DECL|macro|I2O_EVT_STATE_CHANGE_NORMAL
mdefine_line|#define I2O_EVT_STATE_CHANGE_NORMAL&t;&t;0x00
DECL|macro|I2O_EVT_STATE_CHANGE_SUSPENDED
mdefine_line|#define I2O_EVT_STATE_CHANGE_SUSPENDED&t;&t;0x01
DECL|macro|I2O_EVT_STATE_CHANGE_RESTART
mdefine_line|#define I2O_EVT_STATE_CHANGE_RESTART&t;&t;0x02
DECL|macro|I2O_EVT_STATE_CHANGE_NA_RECOVER
mdefine_line|#define I2O_EVT_STATE_CHANGE_NA_RECOVER&t;&t;0x03
DECL|macro|I2O_EVT_STATE_CHANGE_NA_NO_RECOVER
mdefine_line|#define I2O_EVT_STATE_CHANGE_NA_NO_RECOVER&t;0x04
DECL|macro|I2O_EVT_STATE_CHANGE_QUIESCE_REQUEST
mdefine_line|#define I2O_EVT_STATE_CHANGE_QUIESCE_REQUEST&t;0x05
DECL|macro|I2O_EVT_STATE_CHANGE_FAILED
mdefine_line|#define I2O_EVT_STATE_CHANGE_FAILED&t;&t;0x10
DECL|macro|I2O_EVT_STATE_CHANGE_FAULTED
mdefine_line|#define I2O_EVT_STATE_CHANGE_FAULTED&t;&t;0x11
DECL|macro|I2O_EVT_GEN_WARNING_NORMAL
mdefine_line|#define I2O_EVT_GEN_WARNING_NORMAL&t;&t;0x00
DECL|macro|I2O_EVT_GEN_WARNING_ERROR_THRESHOLD
mdefine_line|#define I2O_EVT_GEN_WARNING_ERROR_THRESHOLD&t;0x01
DECL|macro|I2O_EVT_GEN_WARNING_MEDIA_FAULT
mdefine_line|#define I2O_EVT_GEN_WARNING_MEDIA_FAULT&t;&t;0x02
DECL|macro|I2O_EVT_CAPABILITY_OTHER
mdefine_line|#define I2O_EVT_CAPABILITY_OTHER&t;&t;0x01
DECL|macro|I2O_EVT_CAPABILITY_CHANGED
mdefine_line|#define I2O_EVT_CAPABILITY_CHANGED&t;&t;0x02
DECL|macro|I2O_EVT_SENSOR_STATE_CHANGED
mdefine_line|#define I2O_EVT_SENSOR_STATE_CHANGED&t;&t;0x01
multiline_comment|/*&n; *&t;I2O classes / subclasses&n; */
multiline_comment|/*  Class ID and Code Assignments&n; *  (LCT.ClassID.Version field)&n; */
DECL|macro|I2O_CLASS_VERSION_10
mdefine_line|#define    I2O_CLASS_VERSION_10                        0x00
DECL|macro|I2O_CLASS_VERSION_11
mdefine_line|#define    I2O_CLASS_VERSION_11                        0x01
multiline_comment|/*  Class code names&n; *  (from v1.5 Table 6-1 Class Code Assignments.)&n; */
DECL|macro|I2O_CLASS_EXECUTIVE
mdefine_line|#define    I2O_CLASS_EXECUTIVE                         0x000
DECL|macro|I2O_CLASS_DDM
mdefine_line|#define    I2O_CLASS_DDM                               0x001
DECL|macro|I2O_CLASS_RANDOM_BLOCK_STORAGE
mdefine_line|#define    I2O_CLASS_RANDOM_BLOCK_STORAGE              0x010
DECL|macro|I2O_CLASS_SEQUENTIAL_STORAGE
mdefine_line|#define    I2O_CLASS_SEQUENTIAL_STORAGE                0x011
DECL|macro|I2O_CLASS_LAN
mdefine_line|#define    I2O_CLASS_LAN                               0x020
DECL|macro|I2O_CLASS_WAN
mdefine_line|#define    I2O_CLASS_WAN                               0x030
DECL|macro|I2O_CLASS_FIBRE_CHANNEL_PORT
mdefine_line|#define    I2O_CLASS_FIBRE_CHANNEL_PORT                0x040
DECL|macro|I2O_CLASS_FIBRE_CHANNEL_PERIPHERAL
mdefine_line|#define    I2O_CLASS_FIBRE_CHANNEL_PERIPHERAL          0x041
DECL|macro|I2O_CLASS_SCSI_PERIPHERAL
mdefine_line|#define    I2O_CLASS_SCSI_PERIPHERAL                   0x051
DECL|macro|I2O_CLASS_ATE_PORT
mdefine_line|#define    I2O_CLASS_ATE_PORT                          0x060
DECL|macro|I2O_CLASS_ATE_PERIPHERAL
mdefine_line|#define    I2O_CLASS_ATE_PERIPHERAL                    0x061
DECL|macro|I2O_CLASS_FLOPPY_CONTROLLER
mdefine_line|#define    I2O_CLASS_FLOPPY_CONTROLLER                 0x070
DECL|macro|I2O_CLASS_FLOPPY_DEVICE
mdefine_line|#define    I2O_CLASS_FLOPPY_DEVICE                     0x071
DECL|macro|I2O_CLASS_BUS_ADAPTER_PORT
mdefine_line|#define    I2O_CLASS_BUS_ADAPTER_PORT                  0x080
DECL|macro|I2O_CLASS_PEER_TRANSPORT_AGENT
mdefine_line|#define    I2O_CLASS_PEER_TRANSPORT_AGENT              0x090
DECL|macro|I2O_CLASS_PEER_TRANSPORT
mdefine_line|#define    I2O_CLASS_PEER_TRANSPORT                    0x091
multiline_comment|/* &n; *  Rest of 0x092 - 0x09f reserved for peer-to-peer classes&n; */
DECL|macro|I2O_CLASS_MATCH_ANYCLASS
mdefine_line|#define    I2O_CLASS_MATCH_ANYCLASS                    0xffffffff
multiline_comment|/* &n; *  Subclasses&n; */
DECL|macro|I2O_SUBCLASS_i960
mdefine_line|#define    I2O_SUBCLASS_i960                           0x001
DECL|macro|I2O_SUBCLASS_HDM
mdefine_line|#define    I2O_SUBCLASS_HDM                            0x020
DECL|macro|I2O_SUBCLASS_ISM
mdefine_line|#define    I2O_SUBCLASS_ISM                            0x021
multiline_comment|/* Operation functions */
DECL|macro|I2O_PARAMS_FIELD_GET
mdefine_line|#define I2O_PARAMS_FIELD_GET&t;0x0001
DECL|macro|I2O_PARAMS_LIST_GET
mdefine_line|#define I2O_PARAMS_LIST_GET&t;0x0002
DECL|macro|I2O_PARAMS_MORE_GET
mdefine_line|#define I2O_PARAMS_MORE_GET&t;0x0003
DECL|macro|I2O_PARAMS_SIZE_GET
mdefine_line|#define I2O_PARAMS_SIZE_GET&t;0x0004
DECL|macro|I2O_PARAMS_TABLE_GET
mdefine_line|#define I2O_PARAMS_TABLE_GET&t;0x0005
DECL|macro|I2O_PARAMS_FIELD_SET
mdefine_line|#define I2O_PARAMS_FIELD_SET&t;0x0006
DECL|macro|I2O_PARAMS_LIST_SET
mdefine_line|#define I2O_PARAMS_LIST_SET&t;0x0007
DECL|macro|I2O_PARAMS_ROW_ADD
mdefine_line|#define I2O_PARAMS_ROW_ADD&t;0x0008
DECL|macro|I2O_PARAMS_ROW_DELETE
mdefine_line|#define I2O_PARAMS_ROW_DELETE&t;0x0009
DECL|macro|I2O_PARAMS_TABLE_CLEAR
mdefine_line|#define I2O_PARAMS_TABLE_CLEAR&t;0x000A
multiline_comment|/*&n; * I2O serial number conventions / formats &n; * (circa v1.5)&n; */
DECL|macro|I2O_SNFORMAT_UNKNOWN
mdefine_line|#define    I2O_SNFORMAT_UNKNOWN                        0
DECL|macro|I2O_SNFORMAT_BINARY
mdefine_line|#define    I2O_SNFORMAT_BINARY                         1
DECL|macro|I2O_SNFORMAT_ASCII
mdefine_line|#define    I2O_SNFORMAT_ASCII                          2
DECL|macro|I2O_SNFORMAT_UNICODE
mdefine_line|#define    I2O_SNFORMAT_UNICODE                        3
DECL|macro|I2O_SNFORMAT_LAN48_MAC
mdefine_line|#define    I2O_SNFORMAT_LAN48_MAC                      4
DECL|macro|I2O_SNFORMAT_WAN
mdefine_line|#define    I2O_SNFORMAT_WAN                            5
multiline_comment|/* &n; * Plus new in v2.0 (Yellowstone pdf doc)&n; */
DECL|macro|I2O_SNFORMAT_LAN64_MAC
mdefine_line|#define    I2O_SNFORMAT_LAN64_MAC                      6
DECL|macro|I2O_SNFORMAT_DDM
mdefine_line|#define    I2O_SNFORMAT_DDM                            7
DECL|macro|I2O_SNFORMAT_IEEE_REG64
mdefine_line|#define    I2O_SNFORMAT_IEEE_REG64                     8
DECL|macro|I2O_SNFORMAT_IEEE_REG128
mdefine_line|#define    I2O_SNFORMAT_IEEE_REG128                    9
DECL|macro|I2O_SNFORMAT_UNKNOWN2
mdefine_line|#define    I2O_SNFORMAT_UNKNOWN2                       0xff
multiline_comment|/*&n; *&t;I2O Get Status State values &n; */
DECL|macro|ADAPTER_STATE_INITIALIZING
mdefine_line|#define&t;ADAPTER_STATE_INITIALIZING&t;&t;0x01
DECL|macro|ADAPTER_STATE_RESET
mdefine_line|#define&t;ADAPTER_STATE_RESET&t;&t;&t;0x02
DECL|macro|ADAPTER_STATE_HOLD
mdefine_line|#define&t;ADAPTER_STATE_HOLD&t;&t;&t;0x04
DECL|macro|ADAPTER_STATE_READY
mdefine_line|#define &t;ADAPTER_STATE_READY&t;&t;&t;0x05
DECL|macro|ADAPTER_STATE_OPERATIONAL
mdefine_line|#define&t;ADAPTER_STATE_OPERATIONAL&t;&t;0x08
DECL|macro|ADAPTER_STATE_FAILED
mdefine_line|#define&t;ADAPTER_STATE_FAILED&t;&t;&t;0x10
DECL|macro|ADAPTER_STATE_FAULTED
mdefine_line|#define&t;ADAPTER_STATE_FAULTED&t;&t;&t;0x11
macro_line|#endif /* _I2O_DEV_H */
eof
