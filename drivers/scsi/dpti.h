multiline_comment|/***************************************************************************&n;                          dpti.h  -  description&n;                             -------------------&n;    begin                : Thu Sep 7 2000&n;    copyright            : (C) 2001 by Adaptec&n;    email                : deanna_bonds@adaptec.com&n;&n;    See README.dpti for history, notes, license info, and credits&n; ***************************************************************************/
multiline_comment|/***************************************************************************&n; *                                                                         *&n; *   This program is free software; you can redistribute it and/or modify  *&n; *   it under the terms of the GNU General Public License as published by  *&n; *   the Free Software Foundation; either version 2 of the License, or     *&n; *   (at your option) any later version.                                   *&n; *                                                                         *&n; ***************************************************************************/
macro_line|#ifndef _DPT_H
DECL|macro|_DPT_H
mdefine_line|#define _DPT_H
macro_line|#ifndef LINUX_VERSION_CODE
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,4,00)
DECL|macro|MAX_TO_IOP_MESSAGES
mdefine_line|#define MAX_TO_IOP_MESSAGES   (210)
macro_line|#else
DECL|macro|MAX_TO_IOP_MESSAGES
mdefine_line|#define MAX_TO_IOP_MESSAGES   (255)
macro_line|#endif
DECL|macro|MAX_FROM_IOP_MESSAGES
mdefine_line|#define MAX_FROM_IOP_MESSAGES (255)
multiline_comment|/*&n; * SCSI interface function Prototypes&n; */
r_static
r_int
id|adpt_proc_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|inode
comma
r_int
id|inout
)paren
suffix:semicolon
r_static
r_int
id|adpt_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|sht
)paren
suffix:semicolon
r_static
r_int
id|adpt_queue
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
comma
r_void
(paren
op_star
id|cmdcomplete
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_static
r_int
id|adpt_abort
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_static
r_int
id|adpt_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_static
r_int
id|adpt_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
suffix:semicolon
r_static
r_const
r_char
op_star
id|adpt_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|pSHost
)paren
suffix:semicolon
r_static
r_int
id|adpt_bios_param
c_func
(paren
id|Disk
op_star
id|disk
comma
id|kdev_t
id|dev
comma
r_int
id|geom
(braket
)braket
)paren
suffix:semicolon
r_static
r_int
id|adpt_bus_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_static
r_int
id|adpt_device_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
)paren
suffix:semicolon
multiline_comment|/*&n; * Scsi_Host_Template (see hosts.h) &n; */
DECL|macro|DPT_DRIVER_NAME
mdefine_line|#define DPT_DRIVER_NAME&t;&quot;Adaptec I2O RAID&quot;
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,00)
DECL|macro|DPT_I2O
mdefine_line|#define DPT_I2O { &bslash;&n;&t;proc_info: adpt_proc_info,&t;&t;&t;&t;&t;&bslash;&n;&t;detect: adpt_detect,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;release: adpt_release,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;info: adpt_info,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;queuecommand: adpt_queue,&t;&t;&t;&t;&t;&bslash;&n;&t;eh_abort_handler: adpt_abort,&t;&t;&t;&t;&t;&bslash;&n;&t;eh_device_reset_handler: adpt_device_reset,&t;&t;&t;&bslash;&n;&t;eh_bus_reset_handler: adpt_bus_reset,&t;&t;&t;&t;&bslash;&n;&t;eh_host_reset_handler: adpt_reset,&t;&t;&t;&t;&bslash;&n;&t;bios_param: adpt_bios_param,&t;&t;&t;&t;&t;&bslash;&n;&t;can_queue: MAX_TO_IOP_MESSAGES ,/* max simultaneous cmds      */&bslash;&n;&t;this_id: 7,&t;&t;&t;/* scsi id of host adapter    */&bslash;&n;&t;sg_tablesize: 0,&t;&t;/* max scatter-gather cmds    */&bslash;&n;&t;cmd_per_lun: 256,&t;&t;/* cmds per lun (linked cmds) */&bslash;&n;&t;use_clustering: ENABLE_CLUSTERING,&t;&t;&t;&t;&bslash;&n;&t;use_new_eh_code: 1&t;&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#else&t;&t;&t;&t;/* KERNEL_VERSION &gt; 2.2.16 */
DECL|macro|DPT_I2O
mdefine_line|#define DPT_I2O { &bslash;&n;&t;proc_info: adpt_proc_info,&t;&t;&t;&t;&t;&bslash;&n;&t;detect: adpt_detect,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;release: adpt_release,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;info: adpt_info,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;queuecommand: adpt_queue,&t;&t;&t;&t;&t;&bslash;&n;&t;eh_abort_handler: adpt_abort,&t;&t;&t;&t;&t;&bslash;&n;&t;eh_device_reset_handler: adpt_device_reset,&t;&t;&t;&bslash;&n;&t;eh_bus_reset_handler: adpt_bus_reset,&t;&t;&t;&t;&bslash;&n;&t;eh_host_reset_handler: adpt_reset,&t;&t;&t;&t;&bslash;&n;&t;bios_param: adpt_bios_param,&t;&t;&t;&t;&t;&bslash;&n;&t;can_queue: MAX_TO_IOP_MESSAGES,&t;/* max simultaneous cmds      */&bslash;&n;&t;this_id: 7,&t;&t;&t;/* scsi id of host adapter    */&bslash;&n;&t;sg_tablesize: 0,&t;&t;/* max scatter-gather cmds    */&bslash;&n;&t;cmd_per_lun: 256,&t;&t;/* cmds per lun (linked cmds) */&bslash;&n;&t;use_clustering: ENABLE_CLUSTERING,&t;&t;&t;&t;&bslash;&n;&t;use_new_eh_code: 1,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;proc_name: &quot;dpt_i2o&quot;&t;/* this is the name of our proc node*/&t;&bslash;&n;}
macro_line|#endif
macro_line|#ifndef HOSTS_C
macro_line|#include &quot;dpt/sys_info.h&quot;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &quot;dpt/dpti_i2o.h&quot;
macro_line|#include &quot;dpt/dpti_ioctl.h&quot;
DECL|macro|DPT_I2O_VERSION
mdefine_line|#define DPT_I2O_VERSION &quot;2.4 Build 5&quot;
DECL|macro|DPT_VERSION
mdefine_line|#define DPT_VERSION     2
DECL|macro|DPT_REVISION
mdefine_line|#define DPT_REVISION    &squot;4&squot;
DECL|macro|DPT_SUBREVISION
mdefine_line|#define DPT_SUBREVISION &squot;5&squot;
DECL|macro|DPT_BETA
mdefine_line|#define DPT_BETA&t;&quot;&quot;
DECL|macro|DPT_MONTH
mdefine_line|#define DPT_MONTH      8 
DECL|macro|DPT_DAY
mdefine_line|#define DPT_DAY        7
DECL|macro|DPT_YEAR
mdefine_line|#define DPT_YEAR        (2001-1980)
DECL|macro|DPT_DRIVER
mdefine_line|#define DPT_DRIVER&t;&quot;dpt_i2o&quot;
DECL|macro|DPTI_I2O_MAJOR
mdefine_line|#define DPTI_I2O_MAJOR&t;(151)
DECL|macro|DPT_ORGANIZATION_ID
mdefine_line|#define DPT_ORGANIZATION_ID (0x1B)        /* For Private Messages */
DECL|macro|DPTI_MAX_HBA
mdefine_line|#define DPTI_MAX_HBA&t;(16)
DECL|macro|MAX_CHANNEL
mdefine_line|#define MAX_CHANNEL     (5)&t;
singleline_comment|// Maximum Channel # Supported
DECL|macro|MAX_ID
mdefine_line|#define MAX_ID        &t;(128)&t;
singleline_comment|// Maximum Target ID Supported
multiline_comment|/* Sizes in 4 byte words */
DECL|macro|REPLY_FRAME_SIZE
mdefine_line|#define REPLY_FRAME_SIZE  (17)
DECL|macro|MAX_MESSAGE_SIZE
mdefine_line|#define MAX_MESSAGE_SIZE  (128)
DECL|macro|SG_LIST_ELEMENTS
mdefine_line|#define SG_LIST_ELEMENTS  (56)
DECL|macro|EMPTY_QUEUE
mdefine_line|#define EMPTY_QUEUE           0xffffffff
DECL|macro|I2O_INTERRUPT_PENDING_B
mdefine_line|#define I2O_INTERRUPT_PENDING_B   (0x08)
DECL|macro|PCI_DPT_VENDOR_ID
mdefine_line|#define PCI_DPT_VENDOR_ID         (0x1044)&t;
singleline_comment|// DPT PCI Vendor ID
DECL|macro|PCI_DPT_DEVICE_ID
mdefine_line|#define PCI_DPT_DEVICE_ID         (0xA501)&t;
singleline_comment|// DPT PCI I2O Device ID
DECL|macro|PCI_DPT_RAPTOR_DEVICE_ID
mdefine_line|#define PCI_DPT_RAPTOR_DEVICE_ID  (0xA511)&t;
singleline_comment|//#define REBOOT_NOTIFIER 1
multiline_comment|/* Debugging macro from Linux Device Drivers - Rubini */
DECL|macro|PDEBUG
macro_line|#undef PDEBUG
macro_line|#ifdef DEBUG
singleline_comment|//TODO add debug level switch
DECL|macro|PDEBUG
macro_line|#  define PDEBUG(fmt, args...)  printk(KERN_DEBUG &quot;dpti: &quot; fmt, ##args)
DECL|macro|PDEBUGV
macro_line|#  define PDEBUGV(fmt, args...) printk(KERN_DEBUG &quot;dpti: &quot; fmt, ##args)
macro_line|#else
DECL|macro|PDEBUG
macro_line|# define PDEBUG(fmt, args...) /* not debugging: nothing */
DECL|macro|PDEBUGV
macro_line|# define PDEBUGV(fmt, args...) /* not debugging: nothing */
macro_line|#endif
DECL|macro|PERROR
mdefine_line|#define PERROR(fmt, args...) printk(KERN_ERR fmt, ##args)
DECL|macro|PWARN
mdefine_line|#define PWARN(fmt, args...) printk(KERN_WARNING fmt, ##args)
DECL|macro|PINFO
mdefine_line|#define PINFO(fmt, args...) printk(KERN_INFO fmt, ##args)
DECL|macro|PCRIT
mdefine_line|#define PCRIT(fmt, args...) printk(KERN_CRIT fmt, ##args)
DECL|macro|SHUTDOWN_SIGS
mdefine_line|#define SHUTDOWN_SIGS&t;(sigmask(SIGKILL)|sigmask(SIGINT)|sigmask(SIGTERM))
singleline_comment|// Command timeouts
DECL|macro|FOREVER
mdefine_line|#define FOREVER&t;&t;&t;(0)
DECL|macro|TMOUT_INQUIRY
mdefine_line|#define TMOUT_INQUIRY &t;&t;(20)
DECL|macro|TMOUT_FLUSH
mdefine_line|#define TMOUT_FLUSH&t;&t;(360/45)
DECL|macro|TMOUT_ABORT
mdefine_line|#define TMOUT_ABORT&t;&t;(30)
DECL|macro|TMOUT_SCSI
mdefine_line|#define TMOUT_SCSI&t;&t;(300)
DECL|macro|TMOUT_IOPRESET
mdefine_line|#define TMOUT_IOPRESET&t;&t;(360)
DECL|macro|TMOUT_GETSTATUS
mdefine_line|#define TMOUT_GETSTATUS&t;&t;(15)
DECL|macro|TMOUT_INITOUTBOUND
mdefine_line|#define TMOUT_INITOUTBOUND&t;(15)
DECL|macro|TMOUT_LCT
mdefine_line|#define TMOUT_LCT&t;&t;(360)
DECL|macro|I2O_SCSI_DEVICE_DSC_MASK
mdefine_line|#define I2O_SCSI_DEVICE_DSC_MASK                0x00FF
DECL|macro|I2O_DETAIL_STATUS_UNSUPPORTED_FUNCTION
mdefine_line|#define I2O_DETAIL_STATUS_UNSUPPORTED_FUNCTION  0x000A
DECL|macro|I2O_SCSI_DSC_MASK
mdefine_line|#define I2O_SCSI_DSC_MASK                   0xFF00
DECL|macro|I2O_SCSI_DSC_SUCCESS
mdefine_line|#define I2O_SCSI_DSC_SUCCESS                0x0000
DECL|macro|I2O_SCSI_DSC_REQUEST_ABORTED
mdefine_line|#define I2O_SCSI_DSC_REQUEST_ABORTED        0x0200
DECL|macro|I2O_SCSI_DSC_UNABLE_TO_ABORT
mdefine_line|#define I2O_SCSI_DSC_UNABLE_TO_ABORT        0x0300
DECL|macro|I2O_SCSI_DSC_COMPLETE_WITH_ERROR
mdefine_line|#define I2O_SCSI_DSC_COMPLETE_WITH_ERROR    0x0400
DECL|macro|I2O_SCSI_DSC_ADAPTER_BUSY
mdefine_line|#define I2O_SCSI_DSC_ADAPTER_BUSY           0x0500
DECL|macro|I2O_SCSI_DSC_REQUEST_INVALID
mdefine_line|#define I2O_SCSI_DSC_REQUEST_INVALID        0x0600
DECL|macro|I2O_SCSI_DSC_PATH_INVALID
mdefine_line|#define I2O_SCSI_DSC_PATH_INVALID           0x0700
DECL|macro|I2O_SCSI_DSC_DEVICE_NOT_PRESENT
mdefine_line|#define I2O_SCSI_DSC_DEVICE_NOT_PRESENT     0x0800
DECL|macro|I2O_SCSI_DSC_UNABLE_TO_TERMINATE
mdefine_line|#define I2O_SCSI_DSC_UNABLE_TO_TERMINATE    0x0900
DECL|macro|I2O_SCSI_DSC_SELECTION_TIMEOUT
mdefine_line|#define I2O_SCSI_DSC_SELECTION_TIMEOUT      0x0A00
DECL|macro|I2O_SCSI_DSC_COMMAND_TIMEOUT
mdefine_line|#define I2O_SCSI_DSC_COMMAND_TIMEOUT        0x0B00
DECL|macro|I2O_SCSI_DSC_MR_MESSAGE_RECEIVED
mdefine_line|#define I2O_SCSI_DSC_MR_MESSAGE_RECEIVED    0x0D00
DECL|macro|I2O_SCSI_DSC_SCSI_BUS_RESET
mdefine_line|#define I2O_SCSI_DSC_SCSI_BUS_RESET         0x0E00
DECL|macro|I2O_SCSI_DSC_PARITY_ERROR_FAILURE
mdefine_line|#define I2O_SCSI_DSC_PARITY_ERROR_FAILURE   0x0F00
DECL|macro|I2O_SCSI_DSC_AUTOSENSE_FAILED
mdefine_line|#define I2O_SCSI_DSC_AUTOSENSE_FAILED       0x1000
DECL|macro|I2O_SCSI_DSC_NO_ADAPTER
mdefine_line|#define I2O_SCSI_DSC_NO_ADAPTER             0x1100
DECL|macro|I2O_SCSI_DSC_DATA_OVERRUN
mdefine_line|#define I2O_SCSI_DSC_DATA_OVERRUN           0x1200
DECL|macro|I2O_SCSI_DSC_UNEXPECTED_BUS_FREE
mdefine_line|#define I2O_SCSI_DSC_UNEXPECTED_BUS_FREE    0x1300
DECL|macro|I2O_SCSI_DSC_SEQUENCE_FAILURE
mdefine_line|#define I2O_SCSI_DSC_SEQUENCE_FAILURE       0x1400
DECL|macro|I2O_SCSI_DSC_REQUEST_LENGTH_ERROR
mdefine_line|#define I2O_SCSI_DSC_REQUEST_LENGTH_ERROR   0x1500
DECL|macro|I2O_SCSI_DSC_PROVIDE_FAILURE
mdefine_line|#define I2O_SCSI_DSC_PROVIDE_FAILURE        0x1600
DECL|macro|I2O_SCSI_DSC_BDR_MESSAGE_SENT
mdefine_line|#define I2O_SCSI_DSC_BDR_MESSAGE_SENT       0x1700
DECL|macro|I2O_SCSI_DSC_REQUEST_TERMINATED
mdefine_line|#define I2O_SCSI_DSC_REQUEST_TERMINATED     0x1800
DECL|macro|I2O_SCSI_DSC_IDE_MESSAGE_SENT
mdefine_line|#define I2O_SCSI_DSC_IDE_MESSAGE_SENT       0x3300
DECL|macro|I2O_SCSI_DSC_RESOURCE_UNAVAILABLE
mdefine_line|#define I2O_SCSI_DSC_RESOURCE_UNAVAILABLE   0x3400
DECL|macro|I2O_SCSI_DSC_UNACKNOWLEDGED_EVENT
mdefine_line|#define I2O_SCSI_DSC_UNACKNOWLEDGED_EVENT   0x3500
DECL|macro|I2O_SCSI_DSC_MESSAGE_RECEIVED
mdefine_line|#define I2O_SCSI_DSC_MESSAGE_RECEIVED       0x3600
DECL|macro|I2O_SCSI_DSC_INVALID_CDB
mdefine_line|#define I2O_SCSI_DSC_INVALID_CDB            0x3700
DECL|macro|I2O_SCSI_DSC_LUN_INVALID
mdefine_line|#define I2O_SCSI_DSC_LUN_INVALID            0x3800
DECL|macro|I2O_SCSI_DSC_SCSI_TID_INVALID
mdefine_line|#define I2O_SCSI_DSC_SCSI_TID_INVALID       0x3900
DECL|macro|I2O_SCSI_DSC_FUNCTION_UNAVAILABLE
mdefine_line|#define I2O_SCSI_DSC_FUNCTION_UNAVAILABLE   0x3A00
DECL|macro|I2O_SCSI_DSC_NO_NEXUS
mdefine_line|#define I2O_SCSI_DSC_NO_NEXUS               0x3B00
DECL|macro|I2O_SCSI_DSC_SCSI_IID_INVALID
mdefine_line|#define I2O_SCSI_DSC_SCSI_IID_INVALID       0x3C00
DECL|macro|I2O_SCSI_DSC_CDB_RECEIVED
mdefine_line|#define I2O_SCSI_DSC_CDB_RECEIVED           0x3D00
DECL|macro|I2O_SCSI_DSC_LUN_ALREADY_ENABLED
mdefine_line|#define I2O_SCSI_DSC_LUN_ALREADY_ENABLED    0x3E00
DECL|macro|I2O_SCSI_DSC_BUS_BUSY
mdefine_line|#define I2O_SCSI_DSC_BUS_BUSY               0x3F00
DECL|macro|I2O_SCSI_DSC_QUEUE_FROZEN
mdefine_line|#define I2O_SCSI_DSC_QUEUE_FROZEN           0x4000
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE                  1
DECL|macro|FALSE
mdefine_line|#define FALSE                 0
macro_line|#endif
DECL|macro|HBA_FLAGS_INSTALLED_B
mdefine_line|#define HBA_FLAGS_INSTALLED_B       0x00000001&t;
singleline_comment|// Adapter Was Installed
DECL|macro|HBA_FLAGS_BLINKLED_B
mdefine_line|#define HBA_FLAGS_BLINKLED_B        0x00000002&t;
singleline_comment|// Adapter In Blink LED State
DECL|macro|HBA_FLAGS_IN_RESET
mdefine_line|#define HBA_FLAGS_IN_RESET&t;0x00000040&t;/* in reset */
DECL|macro|HBA_HOSTRESET_FAILED
mdefine_line|#define HBA_HOSTRESET_FAILED&t;0x00000080&t;/* adpt_resethost failed */
singleline_comment|// Device state flags
DECL|macro|DPTI_DEV_ONLINE
mdefine_line|#define DPTI_DEV_ONLINE    0x00
DECL|macro|DPTI_DEV_UNSCANNED
mdefine_line|#define DPTI_DEV_UNSCANNED 0x01
DECL|macro|DPTI_DEV_RESET
mdefine_line|#define DPTI_DEV_RESET&t;   0x02
DECL|macro|DPTI_DEV_OFFLINE
mdefine_line|#define DPTI_DEV_OFFLINE   0x04
DECL|struct|adpt_device
r_struct
id|adpt_device
(brace
DECL|member|next_lun
r_struct
id|adpt_device
op_star
id|next_lun
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|type
id|u32
id|type
suffix:semicolon
DECL|member|capacity
id|u32
id|capacity
suffix:semicolon
DECL|member|block_size
id|u32
id|block_size
suffix:semicolon
DECL|member|scsi_channel
id|u8
id|scsi_channel
suffix:semicolon
DECL|member|scsi_id
id|u8
id|scsi_id
suffix:semicolon
DECL|member|scsi_lun
id|u8
id|scsi_lun
suffix:semicolon
DECL|member|state
id|u8
id|state
suffix:semicolon
DECL|member|tid
id|u16
id|tid
suffix:semicolon
DECL|member|pI2o_dev
r_struct
id|i2o_device
op_star
id|pI2o_dev
suffix:semicolon
DECL|member|pScsi_dev
id|Scsi_Device
op_star
id|pScsi_dev
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|adpt_channel
r_struct
id|adpt_channel
(brace
DECL|member|device
r_struct
id|adpt_device
op_star
id|device
(braket
id|MAX_ID
)braket
suffix:semicolon
multiline_comment|/* used as an array of 128 scsi ids */
DECL|member|scsi_id
id|u8
id|scsi_id
suffix:semicolon
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|tid
id|u16
id|tid
suffix:semicolon
DECL|member|state
id|u32
id|state
suffix:semicolon
DECL|member|pI2o_dev
r_struct
id|i2o_device
op_star
id|pI2o_dev
suffix:semicolon
)brace
suffix:semicolon
singleline_comment|// HBA state flags
DECL|macro|DPTI_STATE_RESET
mdefine_line|#define DPTI_STATE_RESET&t;(0x01)
DECL|macro|DPTI_STATE_IOCTL
mdefine_line|#define DPTI_STATE_IOCTL&t;(0x02)
DECL|struct|_adpt_hba
r_typedef
r_struct
id|_adpt_hba
(brace
DECL|member|next
r_struct
id|_adpt_hba
op_star
id|next
suffix:semicolon
DECL|member|pDev
r_struct
id|pci_dev
op_star
id|pDev
suffix:semicolon
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
DECL|member|state
id|u32
id|state
suffix:semicolon
DECL|member|state_lock
id|spinlock_t
id|state_lock
suffix:semicolon
DECL|member|unit
r_int
id|unit
suffix:semicolon
DECL|member|host_no
r_int
id|host_no
suffix:semicolon
multiline_comment|/* SCSI host number */
DECL|member|initialized
id|u8
id|initialized
suffix:semicolon
DECL|member|in_use
id|u8
id|in_use
suffix:semicolon
multiline_comment|/* is the management node open*/
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|detail
r_char
id|detail
(braket
l_int|55
)braket
suffix:semicolon
DECL|member|base_addr_virt
id|ulong
id|base_addr_virt
suffix:semicolon
DECL|member|msg_addr_virt
id|ulong
id|msg_addr_virt
suffix:semicolon
DECL|member|base_addr_phys
id|ulong
id|base_addr_phys
suffix:semicolon
DECL|member|post_port
id|ulong
id|post_port
suffix:semicolon
DECL|member|reply_port
id|ulong
id|reply_port
suffix:semicolon
DECL|member|irq_mask
id|ulong
id|irq_mask
suffix:semicolon
DECL|member|post_count
id|u16
id|post_count
suffix:semicolon
DECL|member|post_fifo_size
id|u32
id|post_fifo_size
suffix:semicolon
DECL|member|reply_fifo_size
id|u32
id|reply_fifo_size
suffix:semicolon
DECL|member|reply_pool
id|u32
op_star
id|reply_pool
suffix:semicolon
DECL|member|sg_tablesize
id|u32
id|sg_tablesize
suffix:semicolon
singleline_comment|// Scatter/Gather List Size.       
DECL|member|top_scsi_channel
id|u8
id|top_scsi_channel
suffix:semicolon
DECL|member|top_scsi_id
id|u8
id|top_scsi_id
suffix:semicolon
DECL|member|top_scsi_lun
id|u8
id|top_scsi_lun
suffix:semicolon
DECL|member|status_block
id|i2o_status_block
op_star
id|status_block
suffix:semicolon
DECL|member|hrt
id|i2o_hrt
op_star
id|hrt
suffix:semicolon
DECL|member|lct
id|i2o_lct
op_star
id|lct
suffix:semicolon
DECL|member|lct_size
id|uint
id|lct_size
suffix:semicolon
DECL|member|devices
r_struct
id|i2o_device
op_star
id|devices
suffix:semicolon
DECL|member|channel
r_struct
id|adpt_channel
id|channel
(braket
id|MAX_CHANNEL
)braket
suffix:semicolon
DECL|member|proc_entry
r_struct
id|proc_dir_entry
op_star
id|proc_entry
suffix:semicolon
multiline_comment|/* /proc dir */
DECL|member|FwDebugBuffer_P
id|ulong
id|FwDebugBuffer_P
suffix:semicolon
singleline_comment|// Virtual Address Of FW Debug Buffer
DECL|member|FwDebugBufferSize
id|u32
id|FwDebugBufferSize
suffix:semicolon
singleline_comment|// FW Debug Buffer Size In Bytes
DECL|member|FwDebugStrLength_P
id|ulong
id|FwDebugStrLength_P
suffix:semicolon
singleline_comment|// Virtual Addr Of FW Debug String Len
DECL|member|FwDebugFlags_P
id|ulong
id|FwDebugFlags_P
suffix:semicolon
singleline_comment|// Virtual Address Of FW Debug Flags 
DECL|member|FwDebugBLEDflag_P
id|ulong
id|FwDebugBLEDflag_P
suffix:semicolon
singleline_comment|// Virtual Addr Of FW Debug BLED
DECL|member|FwDebugBLEDvalue_P
id|ulong
id|FwDebugBLEDvalue_P
suffix:semicolon
singleline_comment|// Virtual Addr Of FW Debug BLED
DECL|member|FwDebugFlags
id|u32
id|FwDebugFlags
suffix:semicolon
DECL|typedef|adpt_hba
)brace
id|adpt_hba
suffix:semicolon
DECL|struct|sg_simple_element
r_struct
id|sg_simple_element
(brace
DECL|member|flag_count
id|u32
id|flag_count
suffix:semicolon
DECL|member|addr_bus
id|u32
id|addr_bus
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Function Prototypes&n; */
r_static
r_void
id|adpt_i2o_sys_shutdown
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|adpt_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|adpt_i2o_build_sys_table
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|adpt_isr
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#ifdef REBOOT_NOTIFIER
r_static
r_int
id|adpt_reboot_event
c_func
(paren
r_struct
id|notifier_block
op_star
id|n
comma
id|ulong
id|code
comma
r_void
op_star
id|p
)paren
suffix:semicolon
macro_line|#endif
r_static
r_void
id|adpt_i2o_report_hba_unit
c_func
(paren
id|adpt_hba
op_star
id|pHba
comma
r_struct
id|i2o_device
op_star
id|d
)paren
suffix:semicolon
r_static
r_int
id|adpt_i2o_query_scalar
c_func
(paren
id|adpt_hba
op_star
id|pHba
comma
r_int
id|tid
comma
r_int
id|group
comma
r_int
id|field
comma
r_void
op_star
id|buf
comma
r_int
id|buflen
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
r_static
r_const
r_char
op_star
id|adpt_i2o_get_class_name
c_func
(paren
r_int
r_class
)paren
suffix:semicolon
macro_line|#endif
r_static
r_int
id|adpt_i2o_issue_params
c_func
(paren
r_int
id|cmd
comma
id|adpt_hba
op_star
id|pHba
comma
r_int
id|tid
comma
r_void
op_star
id|opblk
comma
r_int
id|oplen
comma
r_void
op_star
id|resblk
comma
r_int
id|reslen
)paren
suffix:semicolon
r_static
r_int
id|adpt_i2o_post_wait
c_func
(paren
id|adpt_hba
op_star
id|pHba
comma
id|u32
op_star
id|msg
comma
r_int
id|len
comma
r_int
id|timeout
)paren
suffix:semicolon
r_static
r_int
id|adpt_i2o_lct_get
c_func
(paren
id|adpt_hba
op_star
id|pHba
)paren
suffix:semicolon
r_static
r_int
id|adpt_i2o_parse_lct
c_func
(paren
id|adpt_hba
op_star
id|pHba
)paren
suffix:semicolon
r_static
r_int
id|adpt_i2o_activate_hba
c_func
(paren
id|adpt_hba
op_star
id|pHba
)paren
suffix:semicolon
r_static
r_int
id|adpt_i2o_enable_hba
c_func
(paren
id|adpt_hba
op_star
id|pHba
)paren
suffix:semicolon
r_static
r_int
id|adpt_i2o_install_device
c_func
(paren
id|adpt_hba
op_star
id|pHba
comma
r_struct
id|i2o_device
op_star
id|d
)paren
suffix:semicolon
r_static
id|s32
id|adpt_i2o_post_this
c_func
(paren
id|adpt_hba
op_star
id|pHba
comma
id|u32
op_star
id|data
comma
r_int
id|len
)paren
suffix:semicolon
r_static
id|s32
id|adpt_i2o_quiesce_hba
c_func
(paren
id|adpt_hba
op_star
id|pHba
)paren
suffix:semicolon
r_static
id|s32
id|adpt_i2o_status_get
c_func
(paren
id|adpt_hba
op_star
id|pHba
)paren
suffix:semicolon
r_static
id|s32
id|adpt_i2o_init_outbound_q
c_func
(paren
id|adpt_hba
op_star
id|pHba
)paren
suffix:semicolon
r_static
id|s32
id|adpt_i2o_hrt_get
c_func
(paren
id|adpt_hba
op_star
id|pHba
)paren
suffix:semicolon
r_static
id|s32
id|adpt_scsi_to_i2o
c_func
(paren
id|adpt_hba
op_star
id|pHba
comma
id|Scsi_Cmnd
op_star
id|cmd
comma
r_struct
id|adpt_device
op_star
id|dptdevice
)paren
suffix:semicolon
r_static
id|s32
id|adpt_i2o_to_scsi
c_func
(paren
id|ulong
id|reply
comma
id|Scsi_Cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_static
id|s32
id|adpt_scsi_register
c_func
(paren
id|adpt_hba
op_star
id|pHba
comma
id|Scsi_Host_Template
op_star
id|sht
)paren
suffix:semicolon
r_static
id|s32
id|adpt_hba_reset
c_func
(paren
id|adpt_hba
op_star
id|pHba
)paren
suffix:semicolon
r_static
id|s32
id|adpt_i2o_reset_hba
c_func
(paren
id|adpt_hba
op_star
id|pHba
)paren
suffix:semicolon
r_static
id|s32
id|adpt_rescan
c_func
(paren
id|adpt_hba
op_star
id|pHba
)paren
suffix:semicolon
r_static
id|s32
id|adpt_i2o_reparse_lct
c_func
(paren
id|adpt_hba
op_star
id|pHba
)paren
suffix:semicolon
r_static
id|s32
id|adpt_send_nop
c_func
(paren
id|adpt_hba
op_star
id|pHba
comma
id|u32
id|m
)paren
suffix:semicolon
r_static
r_void
id|adpt_i2o_delete_hba
c_func
(paren
id|adpt_hba
op_star
id|pHba
)paren
suffix:semicolon
r_static
r_void
id|adpt_select_queue_depths
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
comma
id|Scsi_Device
op_star
id|devicelist
)paren
suffix:semicolon
r_static
r_void
id|adpt_inquiry
c_func
(paren
id|adpt_hba
op_star
id|pHba
)paren
suffix:semicolon
r_static
r_void
id|adpt_fail_posted_scbs
c_func
(paren
id|adpt_hba
op_star
id|pHba
)paren
suffix:semicolon
r_static
r_struct
id|adpt_device
op_star
id|adpt_find_device
c_func
(paren
id|adpt_hba
op_star
id|pHba
comma
id|u32
id|chan
comma
id|u32
id|id
comma
id|u32
id|lun
)paren
suffix:semicolon
r_static
r_int
id|adpt_install_hba
c_func
(paren
id|Scsi_Host_Template
op_star
id|sht
comma
r_struct
id|pci_dev
op_star
id|pDev
)paren
suffix:semicolon
r_static
r_int
id|adpt_i2o_online_hba
c_func
(paren
id|adpt_hba
op_star
id|pHba
)paren
suffix:semicolon
r_static
r_void
id|adpt_i2o_post_wait_complete
c_func
(paren
id|u32
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|adpt_i2o_systab_send
c_func
(paren
id|adpt_hba
op_star
id|pHba
)paren
suffix:semicolon
r_static
r_int
id|adpt_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
id|uint
id|cmd
comma
id|ulong
id|arg
)paren
suffix:semicolon
r_static
r_int
id|adpt_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_static
r_int
id|adpt_close
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
macro_line|#ifdef UARTDELAY
r_static
r_void
id|adpt_delay
c_func
(paren
r_int
id|millisec
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,4,0)
r_static
r_struct
id|pci_dev
op_star
id|adpt_pci_find_device
c_func
(paren
id|uint
id|vendor
comma
r_struct
id|pci_dev
op_star
id|from
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined __ia64__ 
r_static
r_void
id|adpt_ia64_info
c_func
(paren
id|sysInfo_S
op_star
id|si
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined __sparc__ 
r_static
r_void
id|adpt_sparc_info
c_func
(paren
id|sysInfo_S
op_star
id|si
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined __alpha__ 
r_static
r_void
id|adpt_sparc_info
c_func
(paren
id|sysInfo_S
op_star
id|si
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined __i386__
r_static
r_void
id|adpt_i386_info
c_func
(paren
id|sysInfo_S
op_star
id|si
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|PRINT_BUFFER_SIZE
mdefine_line|#define PRINT_BUFFER_SIZE     512
DECL|macro|HBA_FLAGS_DBG_FLAGS_MASK
mdefine_line|#define HBA_FLAGS_DBG_FLAGS_MASK         0xffff0000&t;
singleline_comment|// Mask for debug flags
DECL|macro|HBA_FLAGS_DBG_KERNEL_PRINT_B
mdefine_line|#define HBA_FLAGS_DBG_KERNEL_PRINT_B     0x00010000&t;
singleline_comment|// Kernel Debugger Print
DECL|macro|HBA_FLAGS_DBG_FW_PRINT_B
mdefine_line|#define HBA_FLAGS_DBG_FW_PRINT_B         0x00020000&t;
singleline_comment|// Firmware Debugger Print
DECL|macro|HBA_FLAGS_DBG_FUNCTION_ENTRY_B
mdefine_line|#define HBA_FLAGS_DBG_FUNCTION_ENTRY_B   0x00040000&t;
singleline_comment|// Function Entry Point
DECL|macro|HBA_FLAGS_DBG_FUNCTION_EXIT_B
mdefine_line|#define HBA_FLAGS_DBG_FUNCTION_EXIT_B    0x00080000&t;
singleline_comment|// Function Exit
DECL|macro|HBA_FLAGS_DBG_ERROR_B
mdefine_line|#define HBA_FLAGS_DBG_ERROR_B            0x00100000&t;
singleline_comment|// Error Conditions
DECL|macro|HBA_FLAGS_DBG_INIT_B
mdefine_line|#define HBA_FLAGS_DBG_INIT_B             0x00200000&t;
singleline_comment|// Init Prints
DECL|macro|HBA_FLAGS_DBG_OS_COMMANDS_B
mdefine_line|#define HBA_FLAGS_DBG_OS_COMMANDS_B      0x00400000&t;
singleline_comment|// OS Command Info
DECL|macro|HBA_FLAGS_DBG_SCAN_B
mdefine_line|#define HBA_FLAGS_DBG_SCAN_B             0x00800000&t;
singleline_comment|// Device Scan
DECL|macro|FW_DEBUG_STR_LENGTH_OFFSET
mdefine_line|#define FW_DEBUG_STR_LENGTH_OFFSET 0
DECL|macro|FW_DEBUG_FLAGS_OFFSET
mdefine_line|#define FW_DEBUG_FLAGS_OFFSET      4
DECL|macro|FW_DEBUG_BLED_OFFSET
mdefine_line|#define FW_DEBUG_BLED_OFFSET       8
DECL|macro|FW_DEBUG_FLAGS_NO_HEADERS_B
mdefine_line|#define FW_DEBUG_FLAGS_NO_HEADERS_B    0x01
macro_line|#endif&t;&t;&t;&t;/* !HOSTS_C */
macro_line|#endif&t;&t;&t;&t;/* _DPT_H */
eof
