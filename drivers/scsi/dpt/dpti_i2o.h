macro_line|#ifndef _SCSI_I2O_H
DECL|macro|_SCSI_I2O_H
mdefine_line|#define _SCSI_I2O_H
multiline_comment|/* I2O kernel space accessible structures/APIs&n; *&n; * (c) Copyright 1999, 2000 Red Hat Software&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; *************************************************************************&n; *&n; * This header file defined the I2O APIs/structures for use by&n; * the I2O kernel modules.&n; *&n; */
macro_line|#ifdef __KERNEL__       /* This file to be included by kernel only */
macro_line|#include &lt;linux/i2o-dev.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt; /* Needed for MUTEX init macros */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/*&n; *&t;Tunable parameters first&n; */
multiline_comment|/* How many different OSM&squot;s are we allowing */
DECL|macro|MAX_I2O_MODULES
mdefine_line|#define MAX_I2O_MODULES&t;&t;64
DECL|macro|I2O_EVT_CAPABILITY_OTHER
mdefine_line|#define I2O_EVT_CAPABILITY_OTHER&t;&t;0x01
DECL|macro|I2O_EVT_CAPABILITY_CHANGED
mdefine_line|#define I2O_EVT_CAPABILITY_CHANGED&t;&t;0x02
DECL|macro|I2O_EVT_SENSOR_STATE_CHANGED
mdefine_line|#define I2O_EVT_SENSOR_STATE_CHANGED&t;&t;0x01
singleline_comment|//#ifdef __KERNEL__   /* ioctl stuff only thing exported to users */
DECL|macro|I2O_MAX_MANAGERS
mdefine_line|#define I2O_MAX_MANAGERS&t;4
macro_line|#include &lt;asm/semaphore.h&gt; /* Needed for MUTEX init macros */
multiline_comment|/*&n; *&t;I2O Interface Objects&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,4,0)
DECL|macro|DECLARE_MUTEX
mdefine_line|#define DECLARE_MUTEX(name) struct semaphore name=MUTEX
DECL|typedef|adpt_wait_queue_head_t
r_typedef
r_struct
id|wait_queue
op_star
id|adpt_wait_queue_head_t
suffix:semicolon
DECL|macro|ADPT_DECLARE_WAIT_QUEUE_HEAD
mdefine_line|#define ADPT_DECLARE_WAIT_QUEUE_HEAD(wait) adpt_wait_queue_head_t wait = NULL
DECL|typedef|adpt_wait_queue_t
r_typedef
r_struct
id|wait_queue
id|adpt_wait_queue_t
suffix:semicolon
macro_line|#else
macro_line|#include &lt;linux/wait.h&gt;
DECL|typedef|adpt_wait_queue_head_t
r_typedef
id|wait_queue_head_t
id|adpt_wait_queue_head_t
suffix:semicolon
DECL|macro|ADPT_DECLARE_WAIT_QUEUE_HEAD
mdefine_line|#define ADPT_DECLARE_WAIT_QUEUE_HEAD(wait) DECLARE_WAIT_QUEUE_HEAD(wait)
DECL|typedef|adpt_wait_queue_t
r_typedef
id|wait_queue_t
id|adpt_wait_queue_t
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * message structures&n; */
DECL|struct|i2o_message
r_struct
id|i2o_message
(brace
DECL|member|version_offset
id|u8
id|version_offset
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|size
id|u16
id|size
suffix:semicolon
DECL|member|target_tid
id|u32
id|target_tid
suffix:colon
l_int|12
suffix:semicolon
DECL|member|init_tid
id|u32
id|init_tid
suffix:colon
l_int|12
suffix:semicolon
DECL|member|function
id|u32
id|function
suffix:colon
l_int|8
suffix:semicolon
DECL|member|initiator_context
id|u32
id|initiator_context
suffix:semicolon
multiline_comment|/* List follows */
)brace
suffix:semicolon
r_struct
id|adpt_device
suffix:semicolon
r_struct
id|_adpt_hba
suffix:semicolon
DECL|struct|i2o_device
r_struct
id|i2o_device
(brace
DECL|member|next
r_struct
id|i2o_device
op_star
id|next
suffix:semicolon
multiline_comment|/* Chain */
DECL|member|prev
r_struct
id|i2o_device
op_star
id|prev
suffix:semicolon
DECL|member|dev_name
r_char
id|dev_name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* linux /dev name if available */
DECL|member|lct_data
id|i2o_lct_entry
id|lct_data
suffix:semicolon
multiline_comment|/* Device LCT information */
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|proc_entry
r_struct
id|proc_dir_entry
op_star
id|proc_entry
suffix:semicolon
multiline_comment|/* /proc dir */
DECL|member|owner
r_struct
id|adpt_device
op_star
id|owner
suffix:semicolon
DECL|member|controller
r_struct
id|_adpt_hba
op_star
id|controller
suffix:semicolon
multiline_comment|/* Controlling IOP */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Each I2O controller has one of these objects&n; */
DECL|struct|i2o_controller
r_struct
id|i2o_controller
(brace
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|unit
r_int
id|unit
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|enabled
r_int
id|enabled
suffix:semicolon
DECL|member|event_notifer
r_struct
id|notifier_block
op_star
id|event_notifer
suffix:semicolon
multiline_comment|/* Events */
DECL|member|users
id|atomic_t
id|users
suffix:semicolon
DECL|member|devices
r_struct
id|i2o_device
op_star
id|devices
suffix:semicolon
multiline_comment|/* I2O device chain */
DECL|member|next
r_struct
id|i2o_controller
op_star
id|next
suffix:semicolon
multiline_comment|/* Controller chain */
)brace
suffix:semicolon
multiline_comment|/*&n; * I2O System table entry&n; */
DECL|struct|i2o_sys_tbl_entry
r_struct
id|i2o_sys_tbl_entry
(brace
DECL|member|org_id
id|u16
id|org_id
suffix:semicolon
DECL|member|reserved1
id|u16
id|reserved1
suffix:semicolon
DECL|member|iop_id
id|u32
id|iop_id
suffix:colon
l_int|12
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:colon
l_int|20
suffix:semicolon
DECL|member|seg_num
id|u16
id|seg_num
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
DECL|member|frame_size
id|u16
id|frame_size
suffix:semicolon
DECL|member|reserved3
id|u16
id|reserved3
suffix:semicolon
DECL|member|last_changed
id|u32
id|last_changed
suffix:semicolon
DECL|member|iop_capabilities
id|u32
id|iop_capabilities
suffix:semicolon
DECL|member|inbound_low
id|u32
id|inbound_low
suffix:semicolon
DECL|member|inbound_high
id|u32
id|inbound_high
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|i2o_sys_tbl
r_struct
id|i2o_sys_tbl
(brace
DECL|member|num_entries
id|u8
id|num_entries
suffix:semicolon
DECL|member|version
id|u8
id|version
suffix:semicolon
DECL|member|reserved1
id|u16
id|reserved1
suffix:semicolon
DECL|member|change_ind
id|u32
id|change_ind
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|iops
r_struct
id|i2o_sys_tbl_entry
id|iops
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
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
multiline_comment|/*  Rest of 0x092 - 0x09f reserved for peer-to-peer classes&n; */
DECL|macro|I2O_CLASS_MATCH_ANYCLASS
mdefine_line|#define    I2O_CLASS_MATCH_ANYCLASS                    0xffffffff
multiline_comment|/*  Subclasses&n; */
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
multiline_comment|/*&n; *&t;I2O serial number conventions / formats&n; *&t;(circa v1.5)&n; */
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
multiline_comment|/* Plus new in v2.0 (Yellowstone pdf doc)&n; */
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
multiline_comment|/* Transaction Reply Lists (TRL) Control Word structure */
DECL|macro|TRL_SINGLE_FIXED_LENGTH
mdefine_line|#define TRL_SINGLE_FIXED_LENGTH&t;&t;0x00
DECL|macro|TRL_SINGLE_VARIABLE_LENGTH
mdefine_line|#define TRL_SINGLE_VARIABLE_LENGTH&t;0x40
DECL|macro|TRL_MULTIPLE_FIXED_LENGTH
mdefine_line|#define TRL_MULTIPLE_FIXED_LENGTH&t;0x80
multiline_comment|/*&n; *&t;Messaging API values&n; */
DECL|macro|I2O_CMD_ADAPTER_ASSIGN
mdefine_line|#define&t;I2O_CMD_ADAPTER_ASSIGN&t;&t;0xB3
DECL|macro|I2O_CMD_ADAPTER_READ
mdefine_line|#define&t;I2O_CMD_ADAPTER_READ&t;&t;0xB2
DECL|macro|I2O_CMD_ADAPTER_RELEASE
mdefine_line|#define&t;I2O_CMD_ADAPTER_RELEASE&t;&t;0xB5
DECL|macro|I2O_CMD_BIOS_INFO_SET
mdefine_line|#define&t;I2O_CMD_BIOS_INFO_SET&t;&t;0xA5
DECL|macro|I2O_CMD_BOOT_DEVICE_SET
mdefine_line|#define&t;I2O_CMD_BOOT_DEVICE_SET&t;&t;0xA7
DECL|macro|I2O_CMD_CONFIG_VALIDATE
mdefine_line|#define&t;I2O_CMD_CONFIG_VALIDATE&t;&t;0xBB
DECL|macro|I2O_CMD_CONN_SETUP
mdefine_line|#define&t;I2O_CMD_CONN_SETUP&t;&t;0xCA
DECL|macro|I2O_CMD_DDM_DESTROY
mdefine_line|#define&t;I2O_CMD_DDM_DESTROY&t;&t;0xB1
DECL|macro|I2O_CMD_DDM_ENABLE
mdefine_line|#define&t;I2O_CMD_DDM_ENABLE&t;&t;0xD5
DECL|macro|I2O_CMD_DDM_QUIESCE
mdefine_line|#define&t;I2O_CMD_DDM_QUIESCE&t;&t;0xC7
DECL|macro|I2O_CMD_DDM_RESET
mdefine_line|#define&t;I2O_CMD_DDM_RESET&t;&t;0xD9
DECL|macro|I2O_CMD_DDM_SUSPEND
mdefine_line|#define&t;I2O_CMD_DDM_SUSPEND&t;&t;0xAF
DECL|macro|I2O_CMD_DEVICE_ASSIGN
mdefine_line|#define&t;I2O_CMD_DEVICE_ASSIGN&t;&t;0xB7
DECL|macro|I2O_CMD_DEVICE_RELEASE
mdefine_line|#define&t;I2O_CMD_DEVICE_RELEASE&t;&t;0xB9
DECL|macro|I2O_CMD_HRT_GET
mdefine_line|#define&t;I2O_CMD_HRT_GET&t;&t;&t;0xA8
DECL|macro|I2O_CMD_ADAPTER_CLEAR
mdefine_line|#define&t;I2O_CMD_ADAPTER_CLEAR&t;&t;0xBE
DECL|macro|I2O_CMD_ADAPTER_CONNECT
mdefine_line|#define&t;I2O_CMD_ADAPTER_CONNECT&t;&t;0xC9
DECL|macro|I2O_CMD_ADAPTER_RESET
mdefine_line|#define&t;I2O_CMD_ADAPTER_RESET&t;&t;0xBD
DECL|macro|I2O_CMD_LCT_NOTIFY
mdefine_line|#define&t;I2O_CMD_LCT_NOTIFY&t;&t;0xA2
DECL|macro|I2O_CMD_OUTBOUND_INIT
mdefine_line|#define&t;I2O_CMD_OUTBOUND_INIT&t;&t;0xA1
DECL|macro|I2O_CMD_PATH_ENABLE
mdefine_line|#define&t;I2O_CMD_PATH_ENABLE&t;&t;0xD3
DECL|macro|I2O_CMD_PATH_QUIESCE
mdefine_line|#define&t;I2O_CMD_PATH_QUIESCE&t;&t;0xC5
DECL|macro|I2O_CMD_PATH_RESET
mdefine_line|#define&t;I2O_CMD_PATH_RESET&t;&t;0xD7
DECL|macro|I2O_CMD_STATIC_MF_CREATE
mdefine_line|#define&t;I2O_CMD_STATIC_MF_CREATE&t;0xDD
DECL|macro|I2O_CMD_STATIC_MF_RELEASE
mdefine_line|#define&t;I2O_CMD_STATIC_MF_RELEASE&t;0xDF
DECL|macro|I2O_CMD_STATUS_GET
mdefine_line|#define&t;I2O_CMD_STATUS_GET&t;&t;0xA0
DECL|macro|I2O_CMD_SW_DOWNLOAD
mdefine_line|#define&t;I2O_CMD_SW_DOWNLOAD&t;&t;0xA9
DECL|macro|I2O_CMD_SW_UPLOAD
mdefine_line|#define&t;I2O_CMD_SW_UPLOAD&t;&t;0xAB
DECL|macro|I2O_CMD_SW_REMOVE
mdefine_line|#define&t;I2O_CMD_SW_REMOVE&t;&t;0xAD
DECL|macro|I2O_CMD_SYS_ENABLE
mdefine_line|#define&t;I2O_CMD_SYS_ENABLE&t;&t;0xD1
DECL|macro|I2O_CMD_SYS_MODIFY
mdefine_line|#define&t;I2O_CMD_SYS_MODIFY&t;&t;0xC1
DECL|macro|I2O_CMD_SYS_QUIESCE
mdefine_line|#define&t;I2O_CMD_SYS_QUIESCE&t;&t;0xC3
DECL|macro|I2O_CMD_SYS_TAB_SET
mdefine_line|#define&t;I2O_CMD_SYS_TAB_SET&t;&t;0xA3
DECL|macro|I2O_CMD_UTIL_NOP
mdefine_line|#define I2O_CMD_UTIL_NOP&t;&t;0x00
DECL|macro|I2O_CMD_UTIL_ABORT
mdefine_line|#define I2O_CMD_UTIL_ABORT&t;&t;0x01
DECL|macro|I2O_CMD_UTIL_CLAIM
mdefine_line|#define I2O_CMD_UTIL_CLAIM&t;&t;0x09
DECL|macro|I2O_CMD_UTIL_RELEASE
mdefine_line|#define I2O_CMD_UTIL_RELEASE&t;&t;0x0B
DECL|macro|I2O_CMD_UTIL_PARAMS_GET
mdefine_line|#define I2O_CMD_UTIL_PARAMS_GET&t;&t;0x06
DECL|macro|I2O_CMD_UTIL_PARAMS_SET
mdefine_line|#define I2O_CMD_UTIL_PARAMS_SET&t;&t;0x05
DECL|macro|I2O_CMD_UTIL_EVT_REGISTER
mdefine_line|#define I2O_CMD_UTIL_EVT_REGISTER&t;0x13
DECL|macro|I2O_CMD_UTIL_EVT_ACK
mdefine_line|#define I2O_CMD_UTIL_EVT_ACK&t;&t;0x14
DECL|macro|I2O_CMD_UTIL_CONFIG_DIALOG
mdefine_line|#define I2O_CMD_UTIL_CONFIG_DIALOG&t;0x10
DECL|macro|I2O_CMD_UTIL_DEVICE_RESERVE
mdefine_line|#define I2O_CMD_UTIL_DEVICE_RESERVE&t;0x0D
DECL|macro|I2O_CMD_UTIL_DEVICE_RELEASE
mdefine_line|#define I2O_CMD_UTIL_DEVICE_RELEASE&t;0x0F
DECL|macro|I2O_CMD_UTIL_LOCK
mdefine_line|#define I2O_CMD_UTIL_LOCK&t;&t;0x17
DECL|macro|I2O_CMD_UTIL_LOCK_RELEASE
mdefine_line|#define I2O_CMD_UTIL_LOCK_RELEASE&t;0x19
DECL|macro|I2O_CMD_UTIL_REPLY_FAULT_NOTIFY
mdefine_line|#define I2O_CMD_UTIL_REPLY_FAULT_NOTIFY&t;0x15
DECL|macro|I2O_CMD_SCSI_EXEC
mdefine_line|#define I2O_CMD_SCSI_EXEC&t;&t;0x81
DECL|macro|I2O_CMD_SCSI_ABORT
mdefine_line|#define I2O_CMD_SCSI_ABORT&t;&t;0x83
DECL|macro|I2O_CMD_SCSI_BUSRESET
mdefine_line|#define I2O_CMD_SCSI_BUSRESET&t;&t;0x27
DECL|macro|I2O_CMD_BLOCK_READ
mdefine_line|#define I2O_CMD_BLOCK_READ&t;&t;0x30
DECL|macro|I2O_CMD_BLOCK_WRITE
mdefine_line|#define I2O_CMD_BLOCK_WRITE&t;&t;0x31
DECL|macro|I2O_CMD_BLOCK_CFLUSH
mdefine_line|#define I2O_CMD_BLOCK_CFLUSH&t;&t;0x37
DECL|macro|I2O_CMD_BLOCK_MLOCK
mdefine_line|#define I2O_CMD_BLOCK_MLOCK&t;&t;0x49
DECL|macro|I2O_CMD_BLOCK_MUNLOCK
mdefine_line|#define I2O_CMD_BLOCK_MUNLOCK&t;&t;0x4B
DECL|macro|I2O_CMD_BLOCK_MMOUNT
mdefine_line|#define I2O_CMD_BLOCK_MMOUNT&t;&t;0x41
DECL|macro|I2O_CMD_BLOCK_MEJECT
mdefine_line|#define I2O_CMD_BLOCK_MEJECT&t;&t;0x43
DECL|macro|I2O_PRIVATE_MSG
mdefine_line|#define I2O_PRIVATE_MSG&t;&t;&t;0xFF
multiline_comment|/*&n; *&t;Init Outbound Q status &n; */
DECL|macro|I2O_CMD_OUTBOUND_INIT_IN_PROGRESS
mdefine_line|#define I2O_CMD_OUTBOUND_INIT_IN_PROGRESS&t;0x01
DECL|macro|I2O_CMD_OUTBOUND_INIT_REJECTED
mdefine_line|#define I2O_CMD_OUTBOUND_INIT_REJECTED&t;&t;0x02
DECL|macro|I2O_CMD_OUTBOUND_INIT_FAILED
mdefine_line|#define I2O_CMD_OUTBOUND_INIT_FAILED&t;&t;0x03
DECL|macro|I2O_CMD_OUTBOUND_INIT_COMPLETE
mdefine_line|#define I2O_CMD_OUTBOUND_INIT_COMPLETE&t;&t;0x04
multiline_comment|/*&n; *&t;I2O Get Status State values &n; */
DECL|macro|ADAPTER_STATE_INITIALIZING
mdefine_line|#define&t;ADAPTER_STATE_INITIALIZING&t;&t;0x01
DECL|macro|ADAPTER_STATE_RESET
mdefine_line|#define&t;ADAPTER_STATE_RESET&t;&t;&t;0x02
DECL|macro|ADAPTER_STATE_HOLD
mdefine_line|#define&t;ADAPTER_STATE_HOLD&t;&t;&t;0x04
DECL|macro|ADAPTER_STATE_READY
mdefine_line|#define ADAPTER_STATE_READY&t;&t;&t;0x05
DECL|macro|ADAPTER_STATE_OPERATIONAL
mdefine_line|#define&t;ADAPTER_STATE_OPERATIONAL&t;&t;0x08
DECL|macro|ADAPTER_STATE_FAILED
mdefine_line|#define&t;ADAPTER_STATE_FAILED&t;&t;&t;0x10
DECL|macro|ADAPTER_STATE_FAULTED
mdefine_line|#define&t;ADAPTER_STATE_FAULTED&t;&t;&t;0x11
multiline_comment|/* I2O API function return values */
DECL|macro|I2O_RTN_NO_ERROR
mdefine_line|#define I2O_RTN_NO_ERROR&t;&t;&t;0
DECL|macro|I2O_RTN_NOT_INIT
mdefine_line|#define I2O_RTN_NOT_INIT&t;&t;&t;1
DECL|macro|I2O_RTN_FREE_Q_EMPTY
mdefine_line|#define I2O_RTN_FREE_Q_EMPTY&t;&t;&t;2
DECL|macro|I2O_RTN_TCB_ERROR
mdefine_line|#define I2O_RTN_TCB_ERROR&t;&t;&t;3
DECL|macro|I2O_RTN_TRANSACTION_ERROR
mdefine_line|#define I2O_RTN_TRANSACTION_ERROR&t;&t;4
DECL|macro|I2O_RTN_ADAPTER_ALREADY_INIT
mdefine_line|#define I2O_RTN_ADAPTER_ALREADY_INIT&t;&t;5
DECL|macro|I2O_RTN_MALLOC_ERROR
mdefine_line|#define I2O_RTN_MALLOC_ERROR&t;&t;&t;6
DECL|macro|I2O_RTN_ADPTR_NOT_REGISTERED
mdefine_line|#define I2O_RTN_ADPTR_NOT_REGISTERED&t;&t;7
DECL|macro|I2O_RTN_MSG_REPLY_TIMEOUT
mdefine_line|#define I2O_RTN_MSG_REPLY_TIMEOUT&t;&t;8
DECL|macro|I2O_RTN_NO_STATUS
mdefine_line|#define I2O_RTN_NO_STATUS&t;&t;&t;9
DECL|macro|I2O_RTN_NO_FIRM_VER
mdefine_line|#define I2O_RTN_NO_FIRM_VER&t;&t;&t;10
DECL|macro|I2O_RTN_NO_LINK_SPEED
mdefine_line|#define&t;I2O_RTN_NO_LINK_SPEED&t;&t;&t;11
multiline_comment|/* Reply message status defines for all messages */
DECL|macro|I2O_REPLY_STATUS_SUCCESS
mdefine_line|#define I2O_REPLY_STATUS_SUCCESS                    &t;0x00
DECL|macro|I2O_REPLY_STATUS_ABORT_DIRTY
mdefine_line|#define I2O_REPLY_STATUS_ABORT_DIRTY                &t;0x01
DECL|macro|I2O_REPLY_STATUS_ABORT_NO_DATA_TRANSFER
mdefine_line|#define I2O_REPLY_STATUS_ABORT_NO_DATA_TRANSFER     &t;0x02
DECL|macro|I2O_REPLY_STATUS_ABORT_PARTIAL_TRANSFER
mdefine_line|#define&t;I2O_REPLY_STATUS_ABORT_PARTIAL_TRANSFER&t;&t;0x03
DECL|macro|I2O_REPLY_STATUS_ERROR_DIRTY
mdefine_line|#define&t;I2O_REPLY_STATUS_ERROR_DIRTY&t;&t;&t;0x04
DECL|macro|I2O_REPLY_STATUS_ERROR_NO_DATA_TRANSFER
mdefine_line|#define&t;I2O_REPLY_STATUS_ERROR_NO_DATA_TRANSFER&t;&t;0x05
DECL|macro|I2O_REPLY_STATUS_ERROR_PARTIAL_TRANSFER
mdefine_line|#define&t;I2O_REPLY_STATUS_ERROR_PARTIAL_TRANSFER&t;&t;0x06
DECL|macro|I2O_REPLY_STATUS_PROCESS_ABORT_DIRTY
mdefine_line|#define&t;I2O_REPLY_STATUS_PROCESS_ABORT_DIRTY&t;&t;0x08
DECL|macro|I2O_REPLY_STATUS_PROCESS_ABORT_NO_DATA_TRANSFER
mdefine_line|#define&t;I2O_REPLY_STATUS_PROCESS_ABORT_NO_DATA_TRANSFER&t;0x09
DECL|macro|I2O_REPLY_STATUS_PROCESS_ABORT_PARTIAL_TRANSFER
mdefine_line|#define&t;I2O_REPLY_STATUS_PROCESS_ABORT_PARTIAL_TRANSFER&t;0x0A
DECL|macro|I2O_REPLY_STATUS_TRANSACTION_ERROR
mdefine_line|#define&t;I2O_REPLY_STATUS_TRANSACTION_ERROR&t;&t;0x0B
DECL|macro|I2O_REPLY_STATUS_PROGRESS_REPORT
mdefine_line|#define&t;I2O_REPLY_STATUS_PROGRESS_REPORT&t;&t;0x80
multiline_comment|/* Status codes and Error Information for Parameter functions */
DECL|macro|I2O_PARAMS_STATUS_SUCCESS
mdefine_line|#define I2O_PARAMS_STATUS_SUCCESS&t;&t;0x00
DECL|macro|I2O_PARAMS_STATUS_BAD_KEY_ABORT
mdefine_line|#define I2O_PARAMS_STATUS_BAD_KEY_ABORT&t;&t;0x01
DECL|macro|I2O_PARAMS_STATUS_BAD_KEY_CONTINUE
mdefine_line|#define I2O_PARAMS_STATUS_BAD_KEY_CONTINUE   &t;0x02
DECL|macro|I2O_PARAMS_STATUS_BUFFER_FULL
mdefine_line|#define I2O_PARAMS_STATUS_BUFFER_FULL&t;&t;0x03
DECL|macro|I2O_PARAMS_STATUS_BUFFER_TOO_SMALL
mdefine_line|#define I2O_PARAMS_STATUS_BUFFER_TOO_SMALL&t;0x04
DECL|macro|I2O_PARAMS_STATUS_FIELD_UNREADABLE
mdefine_line|#define I2O_PARAMS_STATUS_FIELD_UNREADABLE&t;0x05
DECL|macro|I2O_PARAMS_STATUS_FIELD_UNWRITEABLE
mdefine_line|#define I2O_PARAMS_STATUS_FIELD_UNWRITEABLE&t;0x06
DECL|macro|I2O_PARAMS_STATUS_INSUFFICIENT_FIELDS
mdefine_line|#define I2O_PARAMS_STATUS_INSUFFICIENT_FIELDS&t;0x07
DECL|macro|I2O_PARAMS_STATUS_INVALID_GROUP_ID
mdefine_line|#define I2O_PARAMS_STATUS_INVALID_GROUP_ID&t;0x08
DECL|macro|I2O_PARAMS_STATUS_INVALID_OPERATION
mdefine_line|#define I2O_PARAMS_STATUS_INVALID_OPERATION&t;0x09
DECL|macro|I2O_PARAMS_STATUS_NO_KEY_FIELD
mdefine_line|#define I2O_PARAMS_STATUS_NO_KEY_FIELD&t;&t;0x0A
DECL|macro|I2O_PARAMS_STATUS_NO_SUCH_FIELD
mdefine_line|#define I2O_PARAMS_STATUS_NO_SUCH_FIELD&t;&t;0x0B
DECL|macro|I2O_PARAMS_STATUS_NON_DYNAMIC_GROUP
mdefine_line|#define I2O_PARAMS_STATUS_NON_DYNAMIC_GROUP&t;0x0C
DECL|macro|I2O_PARAMS_STATUS_OPERATION_ERROR
mdefine_line|#define I2O_PARAMS_STATUS_OPERATION_ERROR&t;0x0D
DECL|macro|I2O_PARAMS_STATUS_SCALAR_ERROR
mdefine_line|#define I2O_PARAMS_STATUS_SCALAR_ERROR&t;&t;0x0E
DECL|macro|I2O_PARAMS_STATUS_TABLE_ERROR
mdefine_line|#define I2O_PARAMS_STATUS_TABLE_ERROR&t;&t;0x0F
DECL|macro|I2O_PARAMS_STATUS_WRONG_GROUP_TYPE
mdefine_line|#define I2O_PARAMS_STATUS_WRONG_GROUP_TYPE&t;0x10
multiline_comment|/* DetailedStatusCode defines for Executive, DDM, Util and Transaction error&n; * messages: Table 3-2 Detailed Status Codes.*/
DECL|macro|I2O_DSC_SUCCESS
mdefine_line|#define I2O_DSC_SUCCESS                        0x0000
DECL|macro|I2O_DSC_BAD_KEY
mdefine_line|#define I2O_DSC_BAD_KEY                        0x0002
DECL|macro|I2O_DSC_TCL_ERROR
mdefine_line|#define I2O_DSC_TCL_ERROR                      0x0003
DECL|macro|I2O_DSC_REPLY_BUFFER_FULL
mdefine_line|#define I2O_DSC_REPLY_BUFFER_FULL              0x0004
DECL|macro|I2O_DSC_NO_SUCH_PAGE
mdefine_line|#define I2O_DSC_NO_SUCH_PAGE                   0x0005
DECL|macro|I2O_DSC_INSUFFICIENT_RESOURCE_SOFT
mdefine_line|#define I2O_DSC_INSUFFICIENT_RESOURCE_SOFT     0x0006
DECL|macro|I2O_DSC_INSUFFICIENT_RESOURCE_HARD
mdefine_line|#define I2O_DSC_INSUFFICIENT_RESOURCE_HARD     0x0007
DECL|macro|I2O_DSC_CHAIN_BUFFER_TOO_LARGE
mdefine_line|#define I2O_DSC_CHAIN_BUFFER_TOO_LARGE         0x0009
DECL|macro|I2O_DSC_UNSUPPORTED_FUNCTION
mdefine_line|#define I2O_DSC_UNSUPPORTED_FUNCTION           0x000A
DECL|macro|I2O_DSC_DEVICE_LOCKED
mdefine_line|#define I2O_DSC_DEVICE_LOCKED                  0x000B
DECL|macro|I2O_DSC_DEVICE_RESET
mdefine_line|#define I2O_DSC_DEVICE_RESET                   0x000C
DECL|macro|I2O_DSC_INAPPROPRIATE_FUNCTION
mdefine_line|#define I2O_DSC_INAPPROPRIATE_FUNCTION         0x000D
DECL|macro|I2O_DSC_INVALID_INITIATOR_ADDRESS
mdefine_line|#define I2O_DSC_INVALID_INITIATOR_ADDRESS      0x000E
DECL|macro|I2O_DSC_INVALID_MESSAGE_FLAGS
mdefine_line|#define I2O_DSC_INVALID_MESSAGE_FLAGS          0x000F
DECL|macro|I2O_DSC_INVALID_OFFSET
mdefine_line|#define I2O_DSC_INVALID_OFFSET                 0x0010
DECL|macro|I2O_DSC_INVALID_PARAMETER
mdefine_line|#define I2O_DSC_INVALID_PARAMETER              0x0011
DECL|macro|I2O_DSC_INVALID_REQUEST
mdefine_line|#define I2O_DSC_INVALID_REQUEST                0x0012
DECL|macro|I2O_DSC_INVALID_TARGET_ADDRESS
mdefine_line|#define I2O_DSC_INVALID_TARGET_ADDRESS         0x0013
DECL|macro|I2O_DSC_MESSAGE_TOO_LARGE
mdefine_line|#define I2O_DSC_MESSAGE_TOO_LARGE              0x0014
DECL|macro|I2O_DSC_MESSAGE_TOO_SMALL
mdefine_line|#define I2O_DSC_MESSAGE_TOO_SMALL              0x0015
DECL|macro|I2O_DSC_MISSING_PARAMETER
mdefine_line|#define I2O_DSC_MISSING_PARAMETER              0x0016
DECL|macro|I2O_DSC_TIMEOUT
mdefine_line|#define I2O_DSC_TIMEOUT                        0x0017
DECL|macro|I2O_DSC_UNKNOWN_ERROR
mdefine_line|#define I2O_DSC_UNKNOWN_ERROR                  0x0018
DECL|macro|I2O_DSC_UNKNOWN_FUNCTION
mdefine_line|#define I2O_DSC_UNKNOWN_FUNCTION               0x0019
DECL|macro|I2O_DSC_UNSUPPORTED_VERSION
mdefine_line|#define I2O_DSC_UNSUPPORTED_VERSION            0x001A
DECL|macro|I2O_DSC_DEVICE_BUSY
mdefine_line|#define I2O_DSC_DEVICE_BUSY                    0x001B
DECL|macro|I2O_DSC_DEVICE_NOT_AVAILABLE
mdefine_line|#define I2O_DSC_DEVICE_NOT_AVAILABLE           0x001C
multiline_comment|/* Device Claim Types */
DECL|macro|I2O_CLAIM_PRIMARY
mdefine_line|#define&t;I2O_CLAIM_PRIMARY&t;&t;&t;&t;&t;0x01000000
DECL|macro|I2O_CLAIM_MANAGEMENT
mdefine_line|#define&t;I2O_CLAIM_MANAGEMENT&t;&t;&t;&t;&t;0x02000000
DECL|macro|I2O_CLAIM_AUTHORIZED
mdefine_line|#define&t;I2O_CLAIM_AUTHORIZED&t;&t;&t;&t;&t;0x03000000
DECL|macro|I2O_CLAIM_SECONDARY
mdefine_line|#define&t;I2O_CLAIM_SECONDARY&t;&t;&t;&t;&t;0x04000000
multiline_comment|/* Message header defines for VersionOffset */
DECL|macro|I2OVER15
mdefine_line|#define I2OVER15&t;0x0001
DECL|macro|I2OVER20
mdefine_line|#define I2OVER20&t;0x0002
multiline_comment|/* Default is 1.5, FIXME: Need support for both 1.5 and 2.0 */
DECL|macro|I2OVERSION
mdefine_line|#define I2OVERSION&t;I2OVER15
DECL|macro|SGL_OFFSET_0
mdefine_line|#define SGL_OFFSET_0    I2OVERSION
DECL|macro|SGL_OFFSET_4
mdefine_line|#define SGL_OFFSET_4    (0x0040 | I2OVERSION)
DECL|macro|SGL_OFFSET_5
mdefine_line|#define SGL_OFFSET_5    (0x0050 | I2OVERSION)
DECL|macro|SGL_OFFSET_6
mdefine_line|#define SGL_OFFSET_6    (0x0060 | I2OVERSION)
DECL|macro|SGL_OFFSET_7
mdefine_line|#define SGL_OFFSET_7    (0x0070 | I2OVERSION)
DECL|macro|SGL_OFFSET_8
mdefine_line|#define SGL_OFFSET_8    (0x0080 | I2OVERSION)
DECL|macro|SGL_OFFSET_9
mdefine_line|#define SGL_OFFSET_9    (0x0090 | I2OVERSION)
DECL|macro|SGL_OFFSET_10
mdefine_line|#define SGL_OFFSET_10   (0x00A0 | I2OVERSION)
DECL|macro|SGL_OFFSET_12
mdefine_line|#define SGL_OFFSET_12   (0x00C0 | I2OVERSION)
DECL|macro|TRL_OFFSET_5
mdefine_line|#define TRL_OFFSET_5    (0x0050 | I2OVERSION)
DECL|macro|TRL_OFFSET_6
mdefine_line|#define TRL_OFFSET_6    (0x0060 | I2OVERSION)
multiline_comment|/* msg header defines for MsgFlags */
DECL|macro|MSG_STATIC
mdefine_line|#define MSG_STATIC&t;0x0100
DECL|macro|MSG_64BIT_CNTXT
mdefine_line|#define MSG_64BIT_CNTXT&t;0x0200
DECL|macro|MSG_MULTI_TRANS
mdefine_line|#define MSG_MULTI_TRANS&t;0x1000
DECL|macro|MSG_FAIL
mdefine_line|#define MSG_FAIL&t;0x2000
DECL|macro|MSG_LAST
mdefine_line|#define MSG_LAST&t;0x4000
DECL|macro|MSG_REPLY
mdefine_line|#define MSG_REPLY&t;0x8000
multiline_comment|/* minimum size msg */
DECL|macro|THREE_WORD_MSG_SIZE
mdefine_line|#define THREE_WORD_MSG_SIZE&t;0x00030000
DECL|macro|FOUR_WORD_MSG_SIZE
mdefine_line|#define FOUR_WORD_MSG_SIZE&t;0x00040000
DECL|macro|FIVE_WORD_MSG_SIZE
mdefine_line|#define FIVE_WORD_MSG_SIZE&t;0x00050000
DECL|macro|SIX_WORD_MSG_SIZE
mdefine_line|#define SIX_WORD_MSG_SIZE&t;0x00060000
DECL|macro|SEVEN_WORD_MSG_SIZE
mdefine_line|#define SEVEN_WORD_MSG_SIZE&t;0x00070000
DECL|macro|EIGHT_WORD_MSG_SIZE
mdefine_line|#define EIGHT_WORD_MSG_SIZE&t;0x00080000
DECL|macro|NINE_WORD_MSG_SIZE
mdefine_line|#define NINE_WORD_MSG_SIZE&t;0x00090000
DECL|macro|TEN_WORD_MSG_SIZE
mdefine_line|#define TEN_WORD_MSG_SIZE&t;0x000A0000
DECL|macro|I2O_MESSAGE_SIZE
mdefine_line|#define I2O_MESSAGE_SIZE(x)&t;((x)&lt;&lt;16)
multiline_comment|/* Special TID Assignments */
DECL|macro|ADAPTER_TID
mdefine_line|#define ADAPTER_TID&t;&t;0
DECL|macro|HOST_TID
mdefine_line|#define HOST_TID&t;&t;1
DECL|macro|MSG_FRAME_SIZE
mdefine_line|#define MSG_FRAME_SIZE&t;&t;128
DECL|macro|NMBR_MSG_FRAMES
mdefine_line|#define NMBR_MSG_FRAMES&t;&t;128
DECL|macro|MSG_POOL_SIZE
mdefine_line|#define MSG_POOL_SIZE&t;&t;16384
DECL|macro|I2O_POST_WAIT_OK
mdefine_line|#define I2O_POST_WAIT_OK&t;0
DECL|macro|I2O_POST_WAIT_TIMEOUT
mdefine_line|#define I2O_POST_WAIT_TIMEOUT&t;-ETIMEDOUT
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _SCSI_I2O_H */
eof
