macro_line|#ifndef __MEGARAID_H__
DECL|macro|__MEGARAID_H__
mdefine_line|#define __MEGARAID_H__
macro_line|#ifndef LINUX_VERSION_CODE
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif
multiline_comment|/*&n; * For state flag. Do not use LSB(8 bits) which are&n; * reserved for storing info about channels.&n; */
DECL|macro|IN_ISR
mdefine_line|#define IN_ISR&t;&t;  &t;0x80000000L
DECL|macro|IN_ABORT
mdefine_line|#define IN_ABORT&t;&t;0x40000000L
DECL|macro|IN_RESET
mdefine_line|#define IN_RESET&t;&t;0x20000000L
DECL|macro|IN_QUEUE
mdefine_line|#define IN_QUEUE&t;&t;0x10000000L
DECL|macro|BOARD_QUARTZ
mdefine_line|#define BOARD_QUARTZ&t;0x08000000L
DECL|macro|BOARD_40LD
mdefine_line|#define BOARD_40LD&t;   &t;0x04000000L
DECL|macro|BOARD_64BIT
mdefine_line|#define BOARD_64BIT&t;&t;0x02000000L
DECL|macro|SCB_FREE
mdefine_line|#define SCB_FREE     0x0
DECL|macro|SCB_ACTIVE
mdefine_line|#define SCB_ACTIVE   0x1
DECL|macro|SCB_WAITQ
mdefine_line|#define SCB_WAITQ    0x2
DECL|macro|SCB_ISSUED
mdefine_line|#define SCB_ISSUED   0x3
DECL|macro|SCB_COMPLETE
mdefine_line|#define SCB_COMPLETE 0x4
DECL|macro|SCB_ABORTED
mdefine_line|#define SCB_ABORTED  0x5
DECL|macro|SCB_RESET
mdefine_line|#define SCB_RESET    0x6
DECL|macro|M_RD_CRLFSTR
mdefine_line|#define M_RD_CRLFSTR &t;&t;&t;&quot;&bslash;n&quot;
DECL|macro|M_RD_IOCTL_CMD
mdefine_line|#define M_RD_IOCTL_CMD&t;&t;&t;0x80
DECL|macro|M_RD_IOCTL_CMD_NEW
mdefine_line|#define M_RD_IOCTL_CMD_NEW&t;&t;0x81
DECL|macro|M_RD_DRIVER_IOCTL_INTERFACE
mdefine_line|#define M_RD_DRIVER_IOCTL_INTERFACE&t;0x82
DECL|macro|MEGARAID_VERSION
mdefine_line|#define MEGARAID_VERSION &quot;v1.18 (Release Date: Thu Oct 11 15:02:53 EDT 2001&bslash;n)&quot;
DECL|macro|MEGARAID_IOCTL_VERSION
mdefine_line|#define MEGARAID_IOCTL_VERSION &t;114
multiline_comment|/* Methods */
DECL|macro|GET_DRIVER_INFO
mdefine_line|#define GET_DRIVER_INFO &t;&t;0x1
DECL|macro|MEGA_CMD_TIMEOUT
mdefine_line|#define MEGA_CMD_TIMEOUT&t;&t;10
multiline_comment|/* Feel free to fiddle with these.. max values are:&n;   SGLIST     0..26&n;   COMMANDS   0..253&n;   CMDPERLUN  0..63&n;*/
DECL|macro|MAX_SGLIST
mdefine_line|#define MAX_SGLIST&t;      &t;0x1A
DECL|macro|MAX_COMMANDS
mdefine_line|#define MAX_COMMANDS&t;    &t;127
DECL|macro|MAX_CMD_PER_LUN
mdefine_line|#define MAX_CMD_PER_LUN&t; &t;63
DECL|macro|MAX_FIRMWARE_STATUS
mdefine_line|#define MAX_FIRMWARE_STATUS     46
DECL|macro|MAX_LOGICAL_DRIVES
mdefine_line|#define MAX_LOGICAL_DRIVES      8
DECL|macro|MAX_CHANNEL
mdefine_line|#define MAX_CHANNEL&t;     &t;5
DECL|macro|MAX_TARGET
mdefine_line|#define MAX_TARGET&t;      &t;15
DECL|macro|MAX_PHYSICAL_DRIVES
mdefine_line|#define MAX_PHYSICAL_DRIVES     MAX_CHANNEL*MAX_TARGET
DECL|macro|INQUIRY_DATA_SIZE
mdefine_line|#define INQUIRY_DATA_SIZE       0x24
DECL|macro|MAX_CDB_LEN
mdefine_line|#define MAX_CDB_LEN&t;     &t;&t;0x0A
DECL|macro|MAX_REQ_SENSE_LEN
mdefine_line|#define MAX_REQ_SENSE_LEN       0x20
DECL|macro|INTR_VALID
mdefine_line|#define INTR_VALID&t;      &t;0x40
multiline_comment|/* Direction Macros for MBOX Data direction */
DECL|macro|TO_DEVICE
mdefine_line|#define TO_DEVICE&t;&t;0x0
DECL|macro|FROM_DEVICE
mdefine_line|#define FROM_DEVICE&t;&t;0x1
DECL|macro|FROMTO_DEVICE
mdefine_line|#define FROMTO_DEVICE&t;&t;0x2
multiline_comment|/* Mailbox commands */
DECL|macro|MEGA_MBOXCMD_LREAD
mdefine_line|#define MEGA_MBOXCMD_LREAD&t;&t;0x01
DECL|macro|MEGA_MBOXCMD_LWRITE
mdefine_line|#define MEGA_MBOXCMD_LWRITE&t;&t;0x02
DECL|macro|MEGA_MBOXCMD_LREAD64
mdefine_line|#define MEGA_MBOXCMD_LREAD64&t;&t;0xA7
DECL|macro|MEGA_MBOXCMD_LWRITE64
mdefine_line|#define MEGA_MBOXCMD_LWRITE64&t;&t;0xA8
DECL|macro|MEGA_MBOXCMD_PASSTHRU
mdefine_line|#define MEGA_MBOXCMD_PASSTHRU&t;&t;0x03
DECL|macro|MEGA_MBOXCMD_EXTPASSTHRU
mdefine_line|#define MEGA_MBOXCMD_EXTPASSTHRU&t;0xE3
DECL|macro|MEGA_MBOXCMD_ADAPTERINQ
mdefine_line|#define MEGA_MBOXCMD_ADAPTERINQ&t;&t;0x05
multiline_comment|/* Offsets into Mailbox */
DECL|macro|COMMAND_PORT
mdefine_line|#define COMMAND_PORT       &t;0x00
DECL|macro|COMMAND_ID_PORT
mdefine_line|#define COMMAND_ID_PORT    &t;0x01
DECL|macro|SG_LIST_PORT0
mdefine_line|#define SG_LIST_PORT0      &t;0x08
DECL|macro|SG_LIST_PORT1
mdefine_line|#define SG_LIST_PORT1      &t;0x09
DECL|macro|SG_LIST_PORT2
mdefine_line|#define SG_LIST_PORT2      &t;0x0a
DECL|macro|SG_LIST_PORT3
mdefine_line|#define SG_LIST_PORT3      &t;0x0b
DECL|macro|SG_ELEMENT_PORT
mdefine_line|#define SG_ELEMENT_PORT    &t;0x0d
DECL|macro|NO_FIRED_PORT
mdefine_line|#define NO_FIRED_PORT      &t;0x0f
multiline_comment|/* I/O Port offsets */
DECL|macro|I_CMD_PORT
mdefine_line|#define I_CMD_PORT&t; &t;0x00
DECL|macro|I_ACK_PORT
mdefine_line|#define I_ACK_PORT&t; &t;0x00
DECL|macro|I_TOGGLE_PORT
mdefine_line|#define I_TOGGLE_PORT      &t;0x01
DECL|macro|INTR_PORT
mdefine_line|#define INTR_PORT&t;  &t;0x0a
DECL|macro|MAILBOX_SIZE
mdefine_line|#define MAILBOX_SIZE       &t;(sizeof(mega_mailbox)-16)
DECL|macro|MBOX_BUSY_PORT
mdefine_line|#define MBOX_BUSY_PORT     &t;0x00
DECL|macro|MBOX_PORT0
mdefine_line|#define MBOX_PORT0&t; &t;0x04
DECL|macro|MBOX_PORT1
mdefine_line|#define MBOX_PORT1&t; &t;0x05
DECL|macro|MBOX_PORT2
mdefine_line|#define MBOX_PORT2&t; &t;0x06
DECL|macro|MBOX_PORT3
mdefine_line|#define MBOX_PORT3&t; &t;0x07
DECL|macro|ENABLE_MBOX_REGION
mdefine_line|#define ENABLE_MBOX_REGION &t;0x0B
multiline_comment|/* I/O Port Values */
DECL|macro|ISSUE_BYTE
mdefine_line|#define ISSUE_BYTE&t; &t;0x10
DECL|macro|ACK_BYTE
mdefine_line|#define ACK_BYTE&t;   &t;0x08
DECL|macro|ENABLE_INTR_BYTE
mdefine_line|#define ENABLE_INTR_BYTE   &t;0xc0
DECL|macro|DISABLE_INTR_BYTE
mdefine_line|#define DISABLE_INTR_BYTE  &t;0x00
DECL|macro|VALID_INTR_BYTE
mdefine_line|#define VALID_INTR_BYTE    &t;0x40
DECL|macro|MBOX_BUSY_BYTE
mdefine_line|#define MBOX_BUSY_BYTE     &t;0x10
DECL|macro|ENABLE_MBOX_BYTE
mdefine_line|#define ENABLE_MBOX_BYTE   &t;0x00
multiline_comment|/* Setup some port macros here */
DECL|macro|WRITE_MAILBOX
mdefine_line|#define WRITE_MAILBOX(base,offset,value)   &t;*(base+offset)=value
DECL|macro|READ_MAILBOX
mdefine_line|#define READ_MAILBOX(base,offset)&t;&t;*(base+offset)
DECL|macro|WRITE_PORT
mdefine_line|#define WRITE_PORT(base,offset,value)      &t;outb_p(value,base+offset)
DECL|macro|READ_PORT
mdefine_line|#define READ_PORT(base,offset)&t;     &t;&t;inb_p(base+offset)
DECL|macro|ISSUE_COMMAND
mdefine_line|#define ISSUE_COMMAND(base)&t;WRITE_PORT(base,I_CMD_PORT,ISSUE_BYTE)
DECL|macro|CLEAR_INTR
mdefine_line|#define CLEAR_INTR(base)&t;WRITE_PORT(base,I_ACK_PORT,ACK_BYTE)
DECL|macro|ENABLE_INTR
mdefine_line|#define ENABLE_INTR(base)&t;WRITE_PORT(base,I_TOGGLE_PORT,ENABLE_INTR_BYTE)
DECL|macro|DISABLE_INTR
mdefine_line|#define DISABLE_INTR(base)&t;WRITE_PORT(base,I_TOGGLE_PORT,DISABLE_INTR_BYTE)
multiline_comment|/* Define AMI&squot;s PCI codes */
macro_line|#ifndef PCI_VENDOR_ID_AMI
DECL|macro|PCI_VENDOR_ID_AMI
mdefine_line|#define PCI_VENDOR_ID_AMI&t;&t;0x101E
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_AMI_MEGARAID
DECL|macro|PCI_DEVICE_ID_AMI_MEGARAID
mdefine_line|#define PCI_DEVICE_ID_AMI_MEGARAID&t;0x9010
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_AMI_MEGARAID2
DECL|macro|PCI_DEVICE_ID_AMI_MEGARAID2
mdefine_line|#define PCI_DEVICE_ID_AMI_MEGARAID2&t;0x9060
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_AMI_MEGARAID3
DECL|macro|PCI_DEVICE_ID_AMI_MEGARAID3
mdefine_line|#define PCI_DEVICE_ID_AMI_MEGARAID3&t;0x1960
macro_line|#endif
multiline_comment|/* Special Adapter Commands */
DECL|macro|FW_FIRE_WRITE
mdefine_line|#define FW_FIRE_WRITE   &t;0x2C
DECL|macro|FW_FIRE_FLASH
mdefine_line|#define FW_FIRE_FLASH   &t;0x2D
DECL|macro|FC_NEW_CONFIG
mdefine_line|#define FC_NEW_CONFIG&t;   &t;&t;0xA1
DECL|macro|DCMD_FC_CMD
mdefine_line|#define DCMD_FC_CMD&t;&t;&t;0xA1
DECL|macro|DCMD_FC_PROCEED
mdefine_line|#define DCMD_FC_PROCEED&t;     &t;&t;0x02
DECL|macro|DCMD_DELETE_LOGDRV
mdefine_line|#define DCMD_DELETE_LOGDRV&t;  &t;0x03
DECL|macro|DCMD_FC_READ_NVRAM_CONFIG
mdefine_line|#define DCMD_FC_READ_NVRAM_CONFIG   &t;0x04
DECL|macro|DCMD_FC_READ_NVRAM_CONFIG_64
mdefine_line|#define DCMD_FC_READ_NVRAM_CONFIG_64   &t;0xC0
DECL|macro|DCMD_FC_READ_FINAL_CONFIG
mdefine_line|#define DCMD_FC_READ_FINAL_CONFIG   &t;0x05
DECL|macro|DCMD_GET_DISK_CONFIG
mdefine_line|#define DCMD_GET_DISK_CONFIG&t;&t;0x06
DECL|macro|DCMD_GET_DISK_CONFIG_64
mdefine_line|#define DCMD_GET_DISK_CONFIG_64&t;&t;0xC2
DECL|macro|DCMD_CHANGE_LDNO
mdefine_line|#define DCMD_CHANGE_LDNO&t;    &t;0x07
DECL|macro|DCMD_COMPACT_CONFIG
mdefine_line|#define DCMD_COMPACT_CONFIG&t; &t;0x08
DECL|macro|DCMD_DELETE_DRIVEGROUP
mdefine_line|#define DCMD_DELETE_DRIVEGROUP      &t;0x09
DECL|macro|DCMD_GET_LOOPID_INFO
mdefine_line|#define DCMD_GET_LOOPID_INFO&t;&t;0x0A
DECL|macro|DCMD_CHANGE_LOOPID
mdefine_line|#define DCMD_CHANGE_LOOPID&t;  &t;0x0B
DECL|macro|DCMD_GET_NUM_SCSI_CHANS
mdefine_line|#define DCMD_GET_NUM_SCSI_CHANS     &t;0x0C
DECL|macro|DCMD_WRITE_CONFIG
mdefine_line|#define DCMD_WRITE_CONFIG&t;   &t;0x0D
DECL|macro|DCMD_WRITE_CONFIG_64
mdefine_line|#define DCMD_WRITE_CONFIG_64   &t;&t;0xC1
DECL|macro|NC_SUBOP_PRODUCT_INFO
mdefine_line|#define NC_SUBOP_PRODUCT_INFO       &t;0x0E
DECL|macro|NC_SUBOP_ENQUIRY3
mdefine_line|#define NC_SUBOP_ENQUIRY3&t;   &t;0x0F
DECL|macro|ENQ3_GET_SOLICITED_NOTIFY_ONLY
mdefine_line|#define ENQ3_GET_SOLICITED_NOTIFY_ONLY  0x01
DECL|macro|ENQ3_GET_SOLICITED_FULL
mdefine_line|#define ENQ3_GET_SOLICITED_FULL&t; &t;0x02
DECL|macro|ENQ3_GET_UNSOLICITED
mdefine_line|#define ENQ3_GET_UNSOLICITED&t;    &t;0x03
DECL|macro|PCI_CONF_BASE_ADDR_OFFSET
mdefine_line|#define PCI_CONF_BASE_ADDR_OFFSET  &t;0x10
DECL|macro|PCI_CONF_IRQ_OFFSET
mdefine_line|#define PCI_CONF_IRQ_OFFSET&t;&t;0x3c
DECL|macro|PCI_CONF_AMISIG
mdefine_line|#define PCI_CONF_AMISIG&t;    &t;&t;0xa0
DECL|macro|PCI_CONF_AMISIG64
mdefine_line|#define PCI_CONF_AMISIG64&t;&t;0xa4
multiline_comment|/* Sub-System Vendor ID sorted on alphabetical order*/
DECL|macro|AMI_SUBSYS_ID
mdefine_line|#define&t;AMI_SUBSYS_ID&t;&t;&t;0x101E
DECL|macro|DELL_SUBSYS_ID
mdefine_line|#define DELL_SUBSYS_ID&t;&t;&t;0x1028
DECL|macro|HP_SUBSYS_ID
mdefine_line|#define&t;HP_SUBSYS_ID&t;&t;&t;0x103C
DECL|macro|AMI_SIGNATURE
mdefine_line|#define AMI_SIGNATURE&t;      &t;&t;0x3344
DECL|macro|AMI_SIGNATURE_471
mdefine_line|#define AMI_SIGNATURE_471&t;  &t;0xCCCC
DECL|macro|AMI_64BIT_SIGNATURE
mdefine_line|#define AMI_64BIT_SIGNATURE&t;&t;0x0299
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,1,0)&t;/*0x20100 */
DECL|macro|MEGARAID
mdefine_line|#define MEGARAID &bslash;&n;  { NULL,&t;&t;&t;      &t;/* Next&t;&t;&t;&t;*/&bslash;&n;    NULL,&t;&t;&t;        /* Usage Count Pointer&t;&t;*/&bslash;&n;    NULL,&t;&t;&t;       &t;/* proc Directory Entry&t;&t;*/&bslash;&n;    megaraid_proc_info,&t;&t; &t;/* proc Info Function&t;&t;*/&bslash;&n;    &quot;MegaRAID&quot;,&t;&t;&t; &t;/* Driver Name&t;&t;&t;*/&bslash;&n;    megaraid_detect,&t;&t;    &t;/* Detect Host Adapter&t;&t;*/&bslash;&n;    megaraid_release,&t;&t;   &t;/* Release Host Adapter&t;&t;*/&bslash;&n;    megaraid_info,&t;&t;      &t;/* Driver Info Function&t;&t;*/&bslash;&n;    megaraid_command,&t;&t;   &t;/* Command Function&t;&t;*/&bslash;&n;    megaraid_queue,&t;&t;     &t;/* Queue Command Function&t;*/&bslash;&n;    megaraid_abort,&t;&t;     &t;/* Abort Command Function&t;*/&bslash;&n;    megaraid_reset,&t;&t;     &t;/* Reset Command Function&t;*/&bslash;&n;    NULL,&t;&t;&t;       &t;/* Slave Attach Function&t;*/&bslash;&n;    megaraid_biosparam,&t;&t; &t;/* Disk BIOS Parameters&t;&t;*/&bslash;&n;    MAX_COMMANDS,&t;&t;       &t;/* # of cmds that can be&bslash;&n;&t;&t;&t;&t;&t;outstanding at any time&t;&t;*/&bslash;&n;    7,&t;&t;&t;&t;  &t;/* HBA Target ID&t;&t;*/&bslash;&n;    MAX_SGLIST,&t;&t;&t; &t;/* Scatter/Gather Table Size&t;*/&bslash;&n;    MAX_CMD_PER_LUN,&t;&t;    &t;/* SCSI Commands per LUN&t;*/&bslash;&n;    0,&t;&t;&t;&t;  &t;/* Present&t;&t;&t;*/&bslash;&n;    0,&t;&t;&t;&t;  &t;/* Default Unchecked ISA DMA&t;*/&bslash;&n;    ENABLE_CLUSTERING }&t;&t;&t;/* Enable Clustering&t;&t;*/
macro_line|#else
DECL|macro|MEGARAID
mdefine_line|#define MEGARAID &bslash;&n;  {&bslash;&n;    name:&t;    &t;&quot;MegaRAID&quot;,&t;&t;/* Driver Name&t;&t;&t;*/&bslash;&n;    proc_info:&t;&t;megaraid_proc_info,     /* /proc driver info&t;&t;*/&bslash;&n;    detect:&t;&t;megaraid_detect,&t;/* Detect Host Adapter&t;&t;*/&bslash;&n;    release:&t;  &t;megaraid_release,&t;/* Release Host Adapter&t;&t;*/&bslash;&n;    info:&t;     &t;megaraid_info,&t;   &t;/* Driver Info Function&t;&t;*/&bslash;&n;    command:&t;  &t;megaraid_command,&t;/* Command Function&t;&t;*/&bslash;&n;    queuecommand:  &t;megaraid_queue,&t;&t;/* Queue Command Function&t;*/&bslash;&n;    abort:&t;    &t;megaraid_abort,&t;  &t;/* Abort Command Function&t;*/&bslash;&n;    reset:&t;    &t;megaraid_reset,&t;  &t;/* Reset Command Function&t;*/&bslash;&n;    bios_param:     &t;megaraid_biosparam, &t;/* Disk BIOS Parameters&t;&t;*/&bslash;&n;    can_queue:&t;&t;MAX_COMMANDS,&t;    &t;/* Can Queue&t;&t;&t;*/&bslash;&n;    this_id:&t;  &t;7,&t;&t;       &t;/* HBA Target ID&t;&t;*/&bslash;&n;    sg_tablesize:   &t;MAX_SGLIST,&t;  &t;/* Scatter/Gather Table Size&t;*/&bslash;&n;    cmd_per_lun:    &t;MAX_CMD_PER_LUN,&t;/* SCSI Commands per LUN&t;*/&bslash;&n;    present:&t;  &t;0,&t;&t;       &t;/* Present&t;&t;&t;*/&bslash;&n;    unchecked_isa_dma:&t;0,&t;&t;       &t;/* Default Unchecked ISA DMA&t;*/&bslash;&n;    use_clustering:   &t;ENABLE_CLUSTERING,  &t;/* Enable Clustering&t;&t;*/&bslash;&n;&t;highmem_io:&t;&t;1,&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  }
macro_line|#endif
multiline_comment|/***********************************************************************&n; * Structure Declarations for the Firmware supporting 40 Logical Drives&n; * and 256 Physical Drives.&n; ***********************************************************************/
DECL|macro|FC_MAX_LOGICAL_DRIVES
mdefine_line|#define FC_MAX_LOGICAL_DRIVES       &t;40
DECL|macro|FC_MAX_LOG_DEVICES
mdefine_line|#define FC_MAX_LOG_DEVICES&t;  &t;FC_MAX_LOGICAL_DRIVES
DECL|macro|FC_MAX_SPAN_DEPTH
mdefine_line|#define FC_MAX_SPAN_DEPTH&t;   &t;8
DECL|macro|FC_MAX_ROW_SIZE
mdefine_line|#define FC_MAX_ROW_SIZE&t;     &t;&t;32
DECL|macro|FC_MAX_CHANNELS
mdefine_line|#define FC_MAX_CHANNELS&t;     &t;&t;16
DECL|macro|FC_MAX_TARGETS_PER_CHANNEL
mdefine_line|#define FC_MAX_TARGETS_PER_CHANNEL  &t;16
DECL|macro|FC_MAX_PHYSICAL_DEVICES
mdefine_line|#define FC_MAX_PHYSICAL_DEVICES     &t;256
multiline_comment|/********************************************&n; * PRODUCT_INFO&n; ********************************************/
DECL|macro|SIG_40LOG_32STR_8SPN
mdefine_line|#define SIG_40LOG_32STR_8SPN  0x00282008
multiline_comment|/*&n; * Utilities declare this strcture size as 1024 bytes. So more fields can&n; * be added in future.&n; */
DECL|struct|MRaidProductInfo
r_struct
id|MRaidProductInfo
(brace
DECL|member|DataSize
id|u32
id|DataSize
suffix:semicolon
multiline_comment|/* current size in bytes (not including resvd) */
DECL|member|ConfigSignature
id|u32
id|ConfigSignature
suffix:semicolon
multiline_comment|/* Current value is 0x00282008&n;&t; * 0x28=MAX_LOGICAL_DRIVES,&n;&t; * 0x20=Number of stripes and&n;&t; * 0x08=Number of spans */
DECL|member|FwVer
id|u8
id|FwVer
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* printable ASCI string */
DECL|member|BiosVer
id|u8
id|BiosVer
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* printable ASCI string */
DECL|member|ProductName
id|u8
id|ProductName
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* printable ASCI string */
DECL|member|MaxConcCmds
id|u8
id|MaxConcCmds
suffix:semicolon
multiline_comment|/* Max. concurrent commands supported */
DECL|member|SCSIChanPresent
id|u8
id|SCSIChanPresent
suffix:semicolon
multiline_comment|/* Number of SCSI Channels detected */
DECL|member|FCLoopPresent
id|u8
id|FCLoopPresent
suffix:semicolon
multiline_comment|/* Number of Fibre Loops detected */
DECL|member|memType
id|u8
id|memType
suffix:semicolon
multiline_comment|/* EDO, FPM, SDRAM etc */
DECL|member|signature
id|u32
id|signature
suffix:semicolon
DECL|member|DramSize
id|u16
id|DramSize
suffix:semicolon
multiline_comment|/* In terms of MB */
DECL|member|subSystemID
id|u16
id|subSystemID
suffix:semicolon
DECL|member|subSystemVendorID
id|u16
id|subSystemVendorID
suffix:semicolon
DECL|member|numNotifyCounters
id|u8
id|numNotifyCounters
suffix:semicolon
DECL|member|pad1k
id|u8
id|pad1k
(braket
l_int|889
)braket
suffix:semicolon
multiline_comment|/* 135 + 889 resvd = 1024 total size */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|megaRaidProductInfo
r_typedef
r_struct
id|MRaidProductInfo
id|megaRaidProductInfo
suffix:semicolon
multiline_comment|/********************************************&n; * Standard ENQUIRY&n; ********************************************/
DECL|struct|FC_ADP_INFO
r_struct
id|FC_ADP_INFO
(brace
DECL|member|MaxConcCmds
id|u8
id|MaxConcCmds
suffix:semicolon
multiline_comment|/* Max. concurrent commands supported. */
DECL|member|RbldRate
id|u8
id|RbldRate
suffix:semicolon
multiline_comment|/* Rebuild Rate. Varies from 0%-100% */
DECL|member|MaxTargPerChan
id|u8
id|MaxTargPerChan
suffix:semicolon
multiline_comment|/* Max. Targets supported per chan. */
DECL|member|ChanPresent
id|u8
id|ChanPresent
suffix:semicolon
multiline_comment|/* No. of Chans present on this adapter. */
DECL|member|FwVer
id|u8
id|FwVer
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Firmware version. */
DECL|member|AgeOfFlash
id|u16
id|AgeOfFlash
suffix:semicolon
multiline_comment|/* No. of times FW has been downloaded. */
DECL|member|ChipSetValue
id|u8
id|ChipSetValue
suffix:semicolon
multiline_comment|/* Contents of 0xC0000832 */
DECL|member|DramSize
id|u8
id|DramSize
suffix:semicolon
multiline_comment|/* In terms of MB */
DECL|member|CacheFlushInterval
id|u8
id|CacheFlushInterval
suffix:semicolon
multiline_comment|/* In terms of Seconds */
DECL|member|BiosVersion
id|u8
id|BiosVersion
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|BoardType
id|u8
id|BoardType
suffix:semicolon
DECL|member|sense_alert
id|u8
id|sense_alert
suffix:semicolon
DECL|member|write_config_count
id|u8
id|write_config_count
suffix:semicolon
multiline_comment|/* Increase with evry configuration change */
DECL|member|drive_inserted_count
id|u8
id|drive_inserted_count
suffix:semicolon
multiline_comment|/* Increase with every drive inserted */
DECL|member|inserted_drive
id|u8
id|inserted_drive
suffix:semicolon
multiline_comment|/* Channel: Id of inserted drive */
DECL|member|battery_status
id|u8
id|battery_status
suffix:semicolon
multiline_comment|/*&n;&t;   BIT 0 : battery module missing&n;&t;   BIT 1 : VBAD&n;&t;   BIT 2 : temp high&n;&t;   BIT 3 : battery pack missing&n;&t;   BIT 4,5 : 00 - charge complete&n;&t;   01 - fast charge in prog&n;&t;   10 - fast charge fail&n;&t;   11 - undefined&n;&t;   BIt 6 : counter &gt; 1000&n;&t;   Bit 7 : undefined&n;&t; */
DECL|member|dec_fault_bus_info
id|u8
id|dec_fault_bus_info
suffix:semicolon
multiline_comment|/* was resvd */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|FC_LDRV_INFO
r_struct
id|FC_LDRV_INFO
(brace
DECL|member|NumLDrv
id|u8
id|NumLDrv
suffix:semicolon
multiline_comment|/* No. of Log. Drvs configured. */
DECL|member|recon_state
id|u8
id|recon_state
(braket
id|FC_MAX_LOGICAL_DRIVES
op_div
l_int|8
)braket
suffix:semicolon
multiline_comment|/* bit field for State of reconstruct */
DECL|member|LDrvOpStatus
id|u16
id|LDrvOpStatus
(braket
id|FC_MAX_LOGICAL_DRIVES
op_div
l_int|8
)braket
suffix:semicolon
multiline_comment|/* bit field Status of Long Operations. */
DECL|member|LDrvSize
id|u32
id|LDrvSize
(braket
id|FC_MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
multiline_comment|/* Size of each log. Drv. */
DECL|member|LDrvProp
id|u8
id|LDrvProp
(braket
id|FC_MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
DECL|member|LDrvState
id|u8
id|LDrvState
(braket
id|FC_MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
multiline_comment|/* State of Logical Drives. */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|PREVSTAT_MASK
mdefine_line|#define PREVSTAT_MASK   0xf0
DECL|macro|CURRSTAT_MASK
mdefine_line|#define CURRSTAT_MASK   0x0f
DECL|struct|FC_PDRV_INFO
r_struct
id|FC_PDRV_INFO
(brace
DECL|member|PDrvState
id|u8
id|PDrvState
(braket
id|FC_MAX_PHYSICAL_DEVICES
)braket
suffix:semicolon
multiline_comment|/* State of Phys Drvs. */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|FC_AdapterInq
r_struct
id|FC_AdapterInq
(brace
DECL|member|AdpInfo
r_struct
id|FC_ADP_INFO
id|AdpInfo
suffix:semicolon
DECL|member|LogdrvInfo
r_struct
id|FC_LDRV_INFO
id|LogdrvInfo
suffix:semicolon
DECL|member|PhysdrvInfo
r_struct
id|FC_PDRV_INFO
id|PhysdrvInfo
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|mega_RAIDINQ_FC
r_typedef
r_struct
id|FC_AdapterInq
id|mega_RAIDINQ_FC
suffix:semicolon
multiline_comment|/********************************************&n; * NOTIFICATION&n; ********************************************/
DECL|macro|MAX_NOTIFY_SIZE
mdefine_line|#define MAX_NOTIFY_SIZE     0x80
DECL|macro|CUR_NOTIFY_SIZE
mdefine_line|#define CUR_NOTIFY_SIZE     sizeof(struct MegaRAID_Notify)
multiline_comment|/*&n; * Utilities declare this strcture size as ?? bytes. So more fields can&n; * be added in future.&n; */
DECL|struct|MegaRAID_Notify
r_struct
id|MegaRAID_Notify
(brace
DECL|member|globalCounter
id|u32
id|globalCounter
suffix:semicolon
multiline_comment|/* Any change increments this counter */
DECL|member|paramCounter
id|u8
id|paramCounter
suffix:semicolon
multiline_comment|/* Indicates any params changed  */
DECL|member|paramId
id|u8
id|paramId
suffix:semicolon
multiline_comment|/* Param modified - defined below */
DECL|member|paramVal
id|u16
id|paramVal
suffix:semicolon
multiline_comment|/* New val of last param modified */
DECL|member|writeConfigCounter
id|u8
id|writeConfigCounter
suffix:semicolon
multiline_comment|/* write config occurred */
DECL|member|writeConfigRsvd
id|u8
id|writeConfigRsvd
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ldrvOpCounter
id|u8
id|ldrvOpCounter
suffix:semicolon
multiline_comment|/* Indicates ldrv op started/completed */
DECL|member|ldrvOpId
id|u8
id|ldrvOpId
suffix:semicolon
multiline_comment|/* ldrv num */
DECL|member|ldrvOpCmd
id|u8
id|ldrvOpCmd
suffix:semicolon
multiline_comment|/* ldrv operation - defined below */
DECL|member|ldrvOpStatus
id|u8
id|ldrvOpStatus
suffix:semicolon
multiline_comment|/* status of the operation */
DECL|member|ldrvStateCounter
id|u8
id|ldrvStateCounter
suffix:semicolon
multiline_comment|/* Indicates change of ldrv state */
DECL|member|ldrvStateId
id|u8
id|ldrvStateId
suffix:semicolon
multiline_comment|/* ldrv num */
DECL|member|ldrvStateNew
id|u8
id|ldrvStateNew
suffix:semicolon
multiline_comment|/* New state */
DECL|member|ldrvStateOld
id|u8
id|ldrvStateOld
suffix:semicolon
multiline_comment|/* old state */
DECL|member|pdrvStateCounter
id|u8
id|pdrvStateCounter
suffix:semicolon
multiline_comment|/* Indicates change of ldrv state */
DECL|member|pdrvStateId
id|u8
id|pdrvStateId
suffix:semicolon
multiline_comment|/* pdrv id */
DECL|member|pdrvStateNew
id|u8
id|pdrvStateNew
suffix:semicolon
multiline_comment|/* New state */
DECL|member|pdrvStateOld
id|u8
id|pdrvStateOld
suffix:semicolon
multiline_comment|/* old state */
DECL|member|pdrvFmtCounter
id|u8
id|pdrvFmtCounter
suffix:semicolon
multiline_comment|/* Indicates pdrv format started/over */
DECL|member|pdrvFmtId
id|u8
id|pdrvFmtId
suffix:semicolon
multiline_comment|/* pdrv id */
DECL|member|pdrvFmtVal
id|u8
id|pdrvFmtVal
suffix:semicolon
multiline_comment|/* format started/over */
DECL|member|pdrvFmtRsvd
id|u8
id|pdrvFmtRsvd
suffix:semicolon
DECL|member|targXferCounter
id|u8
id|targXferCounter
suffix:semicolon
multiline_comment|/* Indicates SCSI-2 Xfer rate change */
DECL|member|targXferId
id|u8
id|targXferId
suffix:semicolon
multiline_comment|/* pdrv Id  */
DECL|member|targXferVal
id|u8
id|targXferVal
suffix:semicolon
multiline_comment|/* new Xfer params of last pdrv */
DECL|member|targXferRsvd
id|u8
id|targXferRsvd
suffix:semicolon
DECL|member|fcLoopIdChgCounter
id|u8
id|fcLoopIdChgCounter
suffix:semicolon
multiline_comment|/* Indicates loopid changed */
DECL|member|fcLoopIdPdrvId
id|u8
id|fcLoopIdPdrvId
suffix:semicolon
multiline_comment|/* pdrv id */
DECL|member|fcLoopId0
id|u8
id|fcLoopId0
suffix:semicolon
multiline_comment|/* loopid on fc loop 0 */
DECL|member|fcLoopId1
id|u8
id|fcLoopId1
suffix:semicolon
multiline_comment|/* loopid on fc loop 1 */
DECL|member|fcLoopStateCounter
id|u8
id|fcLoopStateCounter
suffix:semicolon
multiline_comment|/* Indicates loop state changed */
DECL|member|fcLoopState0
id|u8
id|fcLoopState0
suffix:semicolon
multiline_comment|/* state of fc loop 0 */
DECL|member|fcLoopState1
id|u8
id|fcLoopState1
suffix:semicolon
multiline_comment|/* state of fc loop 1 */
DECL|member|fcLoopStateRsvd
id|u8
id|fcLoopStateRsvd
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/********************************************&n; * PARAM IDs in Notify struct&n; ********************************************/
DECL|macro|PARAM_RBLD_RATE
mdefine_line|#define PARAM_RBLD_RATE&t;&t; 0x01
multiline_comment|/*--------------------------------------&n;     * Param val =&n;     *      byte 0: new rbld rate&n;     *--------------------------------------*/
DECL|macro|PARAM_CACHE_FLUSH_INTERVAL
mdefine_line|#define PARAM_CACHE_FLUSH_INTERVAL      0x02
multiline_comment|/*--------------------------------------&n;     * Param val =&n;     *      byte 0: new cache flush interval&n;     *--------------------------------------*/
DECL|macro|PARAM_SENSE_ALERT
mdefine_line|#define PARAM_SENSE_ALERT&t;       0x03
multiline_comment|/*--------------------------------------&n;     * Param val =&n;     *      byte 0: last pdrv id causing chkcond&n;     *--------------------------------------*/
DECL|macro|PARAM_DRIVE_INSERTED
mdefine_line|#define PARAM_DRIVE_INSERTED&t;    0x04
multiline_comment|/*--------------------------------------&n;     * Param val =&n;     *      byte 0: last pdrv id inserted&n;     *--------------------------------------*/
DECL|macro|PARAM_BATTERY_STATUS
mdefine_line|#define PARAM_BATTERY_STATUS&t;    0x05
multiline_comment|/*--------------------------------------&n;     * Param val =&n;     *      byte 0: battery status&n;     *--------------------------------------*/
multiline_comment|/********************************************&n; * Ldrv operation cmd in Notify struct&n; ********************************************/
DECL|macro|LDRV_CMD_CHKCONSISTANCY
mdefine_line|#define LDRV_CMD_CHKCONSISTANCY&t; 0x01
DECL|macro|LDRV_CMD_INITIALIZE
mdefine_line|#define LDRV_CMD_INITIALIZE&t; 0x02
DECL|macro|LDRV_CMD_RECONSTRUCTION
mdefine_line|#define LDRV_CMD_RECONSTRUCTION&t; 0x03
multiline_comment|/********************************************&n; * Ldrv operation status in Notify struct&n; ********************************************/
DECL|macro|LDRV_OP_SUCCESS
mdefine_line|#define LDRV_OP_SUCCESS&t;&t; 0x00
DECL|macro|LDRV_OP_FAILED
mdefine_line|#define LDRV_OP_FAILED&t;&t; 0x01
DECL|macro|LDRV_OP_ABORTED
mdefine_line|#define LDRV_OP_ABORTED&t;&t; 0x02
DECL|macro|LDRV_OP_CORRECTED
mdefine_line|#define LDRV_OP_CORRECTED&t; 0x03
DECL|macro|LDRV_OP_STARTED
mdefine_line|#define LDRV_OP_STARTED&t;&t; 0x04
multiline_comment|/********************************************&n; * Raid Logical drive states.&n; ********************************************/
DECL|macro|RDRV_OFFLINE
mdefine_line|#define     RDRV_OFFLINE&t;0
DECL|macro|RDRV_DEGRADED
mdefine_line|#define     RDRV_DEGRADED&t;1
DECL|macro|RDRV_OPTIMAL
mdefine_line|#define     RDRV_OPTIMAL&t;2
DECL|macro|RDRV_DELETED
mdefine_line|#define     RDRV_DELETED&t;3
multiline_comment|/*******************************************&n; * Physical drive states.&n; *******************************************/
DECL|macro|PDRV_UNCNF
mdefine_line|#define     PDRV_UNCNF&t;&t;0
DECL|macro|PDRV_ONLINE
mdefine_line|#define     PDRV_ONLINE&t;&t;3
DECL|macro|PDRV_FAILED
mdefine_line|#define     PDRV_FAILED&t;&t;4
DECL|macro|PDRV_RBLD
mdefine_line|#define     PDRV_RBLD&t;&t;5
multiline_comment|/*******************************************&n; * Formal val in Notify struct&n; *******************************************/
DECL|macro|PDRV_FMT_START
mdefine_line|#define PDRV_FMT_START&t;&t;0x01
DECL|macro|PDRV_FMT_OVER
mdefine_line|#define PDRV_FMT_OVER&t;&t;0x02
multiline_comment|/********************************************&n; * FC Loop State in Notify Struct&n; ********************************************/
DECL|macro|ENQ_FCLOOP_FAILED
mdefine_line|#define ENQ_FCLOOP_FAILED&t;0
DECL|macro|ENQ_FCLOOP_ACTIVE
mdefine_line|#define ENQ_FCLOOP_ACTIVE&t;1
DECL|macro|ENQ_FCLOOP_TRANSIENT
mdefine_line|#define ENQ_FCLOOP_TRANSIENT&t;2
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
DECL|macro|M_RD_DMA_TYPE_NONE
mdefine_line|#define M_RD_DMA_TYPE_NONE&t;      &t;0xFFFF
DECL|macro|M_RD_PTHRU_WITH_BULK_DATA
mdefine_line|#define M_RD_PTHRU_WITH_BULK_DATA   &t;0x0001
DECL|macro|M_RD_PTHRU_WITH_SGLIST
mdefine_line|#define M_RD_PTHRU_WITH_SGLIST&t;  &t;0x0002
DECL|macro|M_RD_BULK_DATA_ONLY
mdefine_line|#define M_RD_BULK_DATA_ONLY&t;     &t;0x0004
DECL|macro|M_RD_SGLIST_ONLY
mdefine_line|#define M_RD_SGLIST_ONLY&t;&t;0x0008
DECL|macro|M_RD_EPTHRU_WITH_BULK_DATA
mdefine_line|#define M_RD_EPTHRU_WITH_BULK_DATA   &t;0x0010
macro_line|#endif
multiline_comment|/********************************************&n; * ENQUIRY3&n; ********************************************/
multiline_comment|/*&n; * Utilities declare this strcture size as 1024 bytes. So more fields can&n; * be added in future.&n; */
DECL|struct|MegaRAID_Enquiry3
r_struct
id|MegaRAID_Enquiry3
(brace
DECL|member|dataSize
id|u32
id|dataSize
suffix:semicolon
multiline_comment|/* current size in bytes (not including resvd) */
DECL|member|notify
r_struct
id|MegaRAID_Notify
id|notify
suffix:semicolon
DECL|member|notifyRsvd
id|u8
id|notifyRsvd
(braket
id|MAX_NOTIFY_SIZE
op_minus
id|CUR_NOTIFY_SIZE
)braket
suffix:semicolon
DECL|member|rbldRate
id|u8
id|rbldRate
suffix:semicolon
multiline_comment|/* Rebuild rate (0% - 100%) */
DECL|member|cacheFlushInterval
id|u8
id|cacheFlushInterval
suffix:semicolon
multiline_comment|/* In terms of Seconds */
DECL|member|senseAlert
id|u8
id|senseAlert
suffix:semicolon
DECL|member|driveInsertedCount
id|u8
id|driveInsertedCount
suffix:semicolon
multiline_comment|/* drive insertion count */
DECL|member|batteryStatus
id|u8
id|batteryStatus
suffix:semicolon
DECL|member|numLDrv
id|u8
id|numLDrv
suffix:semicolon
multiline_comment|/* No. of Log Drives configured */
DECL|member|reconState
id|u8
id|reconState
(braket
id|FC_MAX_LOGICAL_DRIVES
op_div
l_int|8
)braket
suffix:semicolon
multiline_comment|/* State of reconstruct */
DECL|member|lDrvOpStatus
id|u16
id|lDrvOpStatus
(braket
id|FC_MAX_LOGICAL_DRIVES
op_div
l_int|8
)braket
suffix:semicolon
multiline_comment|/* log. Drv Status */
DECL|member|lDrvSize
id|u32
id|lDrvSize
(braket
id|FC_MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
multiline_comment|/* Size of each log. Drv */
DECL|member|lDrvProp
id|u8
id|lDrvProp
(braket
id|FC_MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
DECL|member|lDrvState
id|u8
id|lDrvState
(braket
id|FC_MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
multiline_comment|/* State of Logical Drives */
DECL|member|pDrvState
id|u8
id|pDrvState
(braket
id|FC_MAX_PHYSICAL_DEVICES
)braket
suffix:semicolon
multiline_comment|/* State of Phys. Drvs. */
DECL|member|physDrvFormat
id|u16
id|physDrvFormat
(braket
id|FC_MAX_PHYSICAL_DEVICES
op_div
l_int|16
)braket
suffix:semicolon
DECL|member|targXfer
id|u8
id|targXfer
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* phys device transfer rate */
DECL|member|pad1k
id|u8
id|pad1k
(braket
l_int|263
)braket
suffix:semicolon
multiline_comment|/* 761 + 263reserved = 1024 bytes total size */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|mega_Enquiry3
r_typedef
r_struct
id|MegaRAID_Enquiry3
id|mega_Enquiry3
suffix:semicolon
multiline_comment|/* Structures */
DECL|struct|_mega_ADP_INFO
r_typedef
r_struct
id|_mega_ADP_INFO
(brace
DECL|member|MaxConcCmds
id|u8
id|MaxConcCmds
suffix:semicolon
DECL|member|RbldRate
id|u8
id|RbldRate
suffix:semicolon
DECL|member|MaxTargPerChan
id|u8
id|MaxTargPerChan
suffix:semicolon
DECL|member|ChanPresent
id|u8
id|ChanPresent
suffix:semicolon
DECL|member|FwVer
id|u8
id|FwVer
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|AgeOfFlash
id|u16
id|AgeOfFlash
suffix:semicolon
DECL|member|ChipSetValue
id|u8
id|ChipSetValue
suffix:semicolon
DECL|member|DramSize
id|u8
id|DramSize
suffix:semicolon
DECL|member|CacheFlushInterval
id|u8
id|CacheFlushInterval
suffix:semicolon
DECL|member|BiosVer
id|u8
id|BiosVer
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|resvd
id|u8
id|resvd
(braket
l_int|7
)braket
suffix:semicolon
DECL|typedef|mega_ADP_INFO
)brace
id|mega_ADP_INFO
suffix:semicolon
DECL|struct|_mega_LDRV_INFO
r_typedef
r_struct
id|_mega_LDRV_INFO
(brace
DECL|member|NumLDrv
id|u8
id|NumLDrv
suffix:semicolon
DECL|member|resvd
id|u8
id|resvd
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|LDrvSize
id|u32
id|LDrvSize
(braket
id|MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
DECL|member|LDrvProp
id|u8
id|LDrvProp
(braket
id|MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
DECL|member|LDrvState
id|u8
id|LDrvState
(braket
id|MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
DECL|typedef|mega_LDRV_INFO
)brace
id|mega_LDRV_INFO
suffix:semicolon
DECL|struct|_mega_PDRV_INFO
r_typedef
r_struct
id|_mega_PDRV_INFO
(brace
DECL|member|PDrvState
id|u8
id|PDrvState
(braket
id|MAX_PHYSICAL_DRIVES
)braket
suffix:semicolon
DECL|member|resvd
id|u8
id|resvd
suffix:semicolon
DECL|typedef|mega_PDRV_INFO
)brace
id|mega_PDRV_INFO
suffix:semicolon
multiline_comment|/* RAID inquiry: Mailbox command 0x5*/
DECL|struct|_mega_RAIDINQ
r_typedef
r_struct
id|_mega_RAIDINQ
(brace
DECL|member|AdpInfo
id|mega_ADP_INFO
id|AdpInfo
suffix:semicolon
DECL|member|LogdrvInfo
id|mega_LDRV_INFO
id|LogdrvInfo
suffix:semicolon
DECL|member|PhysdrvInfo
id|mega_PDRV_INFO
id|PhysdrvInfo
suffix:semicolon
DECL|typedef|mega_RAIDINQ
)brace
id|mega_RAIDINQ
suffix:semicolon
multiline_comment|/* Passthrough command: Mailbox command 0x3*/
DECL|struct|mega_passthru
r_typedef
r_struct
id|mega_passthru
(brace
DECL|member|timeout
id|u8
id|timeout
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 0=6sec/1=60sec/2=10min/3=3hrs */
DECL|member|ars
id|u8
id|ars
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:colon
l_int|3
suffix:semicolon
DECL|member|islogical
id|u8
id|islogical
suffix:colon
l_int|1
suffix:semicolon
DECL|member|logdrv
id|u8
id|logdrv
suffix:semicolon
multiline_comment|/* if islogical == 1 */
DECL|member|channel
id|u8
id|channel
suffix:semicolon
multiline_comment|/* if islogical == 0 */
DECL|member|target
id|u8
id|target
suffix:semicolon
multiline_comment|/* if islogical == 0 */
DECL|member|queuetag
id|u8
id|queuetag
suffix:semicolon
multiline_comment|/* unused */
DECL|member|queueaction
id|u8
id|queueaction
suffix:semicolon
multiline_comment|/* unused */
DECL|member|cdb
id|u8
id|cdb
(braket
id|MAX_CDB_LEN
)braket
suffix:semicolon
DECL|member|cdblen
id|u8
id|cdblen
suffix:semicolon
DECL|member|reqsenselen
id|u8
id|reqsenselen
suffix:semicolon
DECL|member|reqsensearea
id|u8
id|reqsensearea
(braket
id|MAX_REQ_SENSE_LEN
)braket
suffix:semicolon
DECL|member|numsgelements
id|u8
id|numsgelements
suffix:semicolon
DECL|member|scsistatus
id|u8
id|scsistatus
suffix:semicolon
DECL|member|dataxferaddr
id|u32
id|dataxferaddr
suffix:semicolon
DECL|member|dataxferlen
id|u32
id|dataxferlen
suffix:semicolon
DECL|typedef|mega_passthru
)brace
id|mega_passthru
suffix:semicolon
multiline_comment|/*&n; * Extended passthru: support CDB &gt; 10 bytes&n; */
r_typedef
r_struct
(brace
DECL|member|timeout
id|u8
id|timeout
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 0=6sec/1=60sec/2=10min/3=3hrs */
DECL|member|ars
id|u8
id|ars
suffix:colon
l_int|1
suffix:semicolon
DECL|member|rsvd1
id|u8
id|rsvd1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cd_rom
id|u8
id|cd_rom
suffix:colon
l_int|1
suffix:semicolon
DECL|member|rsvd2
id|u8
id|rsvd2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|islogical
id|u8
id|islogical
suffix:colon
l_int|1
suffix:semicolon
DECL|member|logdrv
id|u8
id|logdrv
suffix:semicolon
multiline_comment|/* if islogical == 1 */
DECL|member|channel
id|u8
id|channel
suffix:semicolon
multiline_comment|/* if islogical == 0 */
DECL|member|target
id|u8
id|target
suffix:semicolon
multiline_comment|/* if islogical == 0 */
DECL|member|queuetag
id|u8
id|queuetag
suffix:semicolon
multiline_comment|/* unused */
DECL|member|queueaction
id|u8
id|queueaction
suffix:semicolon
multiline_comment|/* unused */
DECL|member|cdblen
id|u8
id|cdblen
suffix:semicolon
DECL|member|rsvd3
id|u8
id|rsvd3
suffix:semicolon
DECL|member|cdb
id|u8
id|cdb
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|numsgelements
id|u8
id|numsgelements
suffix:semicolon
DECL|member|status
id|u8
id|status
suffix:semicolon
DECL|member|reqsenselen
id|u8
id|reqsenselen
suffix:semicolon
DECL|member|reqsensearea
id|u8
id|reqsensearea
(braket
id|MAX_REQ_SENSE_LEN
)braket
suffix:semicolon
DECL|member|rsvd4
id|u8
id|rsvd4
suffix:semicolon
DECL|member|dataxferaddr
id|u32
id|dataxferaddr
suffix:semicolon
DECL|member|dataxferlen
id|u32
id|dataxferlen
suffix:semicolon
DECL|typedef|mega_ext_passthru
)brace
id|mega_ext_passthru
suffix:semicolon
DECL|struct|_mega_mailbox
r_struct
id|_mega_mailbox
(brace
DECL|member|cmd
multiline_comment|/* 0x0 */
id|u8
id|cmd
suffix:semicolon
DECL|member|cmdid
multiline_comment|/* 0x1 */
id|u8
id|cmdid
suffix:semicolon
DECL|member|numsectors
multiline_comment|/* 0x2 */
id|u16
id|numsectors
suffix:semicolon
DECL|member|lba
multiline_comment|/* 0x4 */
id|u32
id|lba
suffix:semicolon
DECL|member|xferaddr
multiline_comment|/* 0x8 */
id|u32
id|xferaddr
suffix:semicolon
DECL|member|logdrv
multiline_comment|/* 0xC */
id|u8
id|logdrv
suffix:semicolon
DECL|member|numsgelements
multiline_comment|/* 0xD */
id|u8
id|numsgelements
suffix:semicolon
DECL|member|resvd
multiline_comment|/* 0xE */
id|u8
id|resvd
suffix:semicolon
DECL|member|busy
multiline_comment|/* 0xF */
id|u8
id|busy
suffix:semicolon
DECL|member|numstatus
multiline_comment|/* 0x10 */
id|u8
id|numstatus
suffix:semicolon
DECL|member|status
multiline_comment|/* 0x11 */
id|u8
id|status
suffix:semicolon
DECL|member|completed
multiline_comment|/* 0x12 */
id|u8
id|completed
(braket
l_int|46
)braket
suffix:semicolon
DECL|member|mraid_poll
r_volatile
id|u8
id|mraid_poll
suffix:semicolon
DECL|member|mraid_ack
r_volatile
id|u8
id|mraid_ack
suffix:semicolon
DECL|member|pad
id|u8
id|pad
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* for alignment purposes */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|mega_mailbox
r_typedef
r_struct
id|_mega_mailbox
id|mega_mailbox
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|xferSegment_lo
id|u32
id|xferSegment_lo
suffix:semicolon
DECL|member|xferSegment_hi
id|u32
id|xferSegment_hi
suffix:semicolon
DECL|member|mailbox
id|mega_mailbox
id|mailbox
suffix:semicolon
DECL|typedef|mega_mailbox64
)brace
id|mega_mailbox64
suffix:semicolon
DECL|struct|_mega_ioctl_mbox
r_typedef
r_struct
id|_mega_ioctl_mbox
(brace
DECL|member|cmd
multiline_comment|/* 0x0 */
id|u8
id|cmd
suffix:semicolon
DECL|member|cmdid
multiline_comment|/* 0x1 */
id|u8
id|cmdid
suffix:semicolon
DECL|member|channel
multiline_comment|/* 0x2 */
id|u8
id|channel
suffix:semicolon
DECL|member|param
multiline_comment|/* 0x3 */
id|u8
id|param
suffix:semicolon
DECL|member|pad
multiline_comment|/* 0x4 */
id|u8
id|pad
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|xferaddr
multiline_comment|/* 0x8 */
id|u32
id|xferaddr
suffix:semicolon
DECL|member|logdrv
multiline_comment|/* 0xC */
id|u8
id|logdrv
suffix:semicolon
DECL|member|numsgelements
multiline_comment|/* 0xD */
id|u8
id|numsgelements
suffix:semicolon
DECL|member|resvd
multiline_comment|/* 0xE */
id|u8
id|resvd
suffix:semicolon
DECL|member|busy
multiline_comment|/* 0xF */
id|u8
id|busy
suffix:semicolon
DECL|member|numstatus
multiline_comment|/* 0x10 */
id|u8
id|numstatus
suffix:semicolon
DECL|member|status
multiline_comment|/* 0x11 */
id|u8
id|status
suffix:semicolon
DECL|member|completed
multiline_comment|/* 0x12 */
id|u8
id|completed
(braket
l_int|46
)braket
suffix:semicolon
DECL|member|mraid_poll
id|u8
id|mraid_poll
suffix:semicolon
DECL|member|mraid_ack
id|u8
id|mraid_ack
suffix:semicolon
DECL|member|malign
id|u8
id|malign
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|mega_ioctl_mbox
)brace
id|mega_ioctl_mbox
suffix:semicolon
DECL|struct|_mega_64sglist32
r_typedef
r_struct
id|_mega_64sglist32
(brace
DECL|member|address
id|u64
id|address
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|typedef|mega_64sglist
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|mega_64sglist
suffix:semicolon
DECL|struct|_mega_sglist
r_typedef
r_struct
id|_mega_sglist
(brace
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|typedef|mega_sglist
)brace
id|mega_sglist
suffix:semicolon
multiline_comment|/* Queued command data */
DECL|typedef|mega_scb
r_typedef
r_struct
id|_mega_scb
id|mega_scb
suffix:semicolon
DECL|struct|_mega_scb
r_struct
id|_mega_scb
(brace
DECL|member|idx
r_int
id|idx
suffix:semicolon
DECL|member|state
id|u32
id|state
suffix:semicolon
DECL|member|isrcount
id|u32
id|isrcount
suffix:semicolon
DECL|member|mboxData
id|u8
id|mboxData
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
DECL|member|dma_type
id|u32
id|dma_type
suffix:semicolon
DECL|member|dma_h_bulkdata
id|dma_addr_t
id|dma_h_bulkdata
suffix:semicolon
multiline_comment|/*Dma handle for bulk data transfter */
DECL|member|dma_direction
id|u32
id|dma_direction
suffix:semicolon
multiline_comment|/*Dma direction */
DECL|member|dma_h_sgdata
id|dma_addr_t
id|dma_h_sgdata
suffix:semicolon
multiline_comment|/*Dma handle for the sglist structure */
DECL|member|dma_h_sglist
id|dma_addr_t
id|dma_h_sglist
(braket
id|MAX_SGLIST
)braket
suffix:semicolon
multiline_comment|/*Dma handle for all SGL elements */
DECL|member|sglist_count
id|u8
id|sglist_count
suffix:semicolon
DECL|member|dma_sghandle64
id|dma_addr_t
id|dma_sghandle64
suffix:semicolon
DECL|member|dma_passthruhandle64
id|dma_addr_t
id|dma_passthruhandle64
suffix:semicolon
DECL|member|dma_ext_passthruhandle64
id|dma_addr_t
id|dma_ext_passthruhandle64
suffix:semicolon
DECL|member|dma_bounce_buffer
id|dma_addr_t
id|dma_bounce_buffer
suffix:semicolon
DECL|member|bounce_buffer
id|u8
op_star
id|bounce_buffer
suffix:semicolon
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
DECL|member|pthru
id|mega_passthru
op_star
id|pthru
suffix:semicolon
DECL|member|epthru
id|mega_ext_passthru
op_star
id|epthru
suffix:semicolon
macro_line|#else
DECL|member|pthru
id|mega_passthru
id|pthru
suffix:semicolon
DECL|member|epthru
id|mega_ext_passthru
id|epthru
suffix:semicolon
macro_line|#endif
DECL|member|SCpnt
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
DECL|member|sgList
id|mega_sglist
op_star
id|sgList
suffix:semicolon
DECL|member|sg64List
id|mega_64sglist
op_star
id|sg64List
suffix:semicolon
DECL|member|ioctl_sem
r_struct
id|semaphore
id|ioctl_sem
suffix:semicolon
DECL|member|buff_ptr
r_void
op_star
id|buff_ptr
suffix:semicolon
DECL|member|iDataSize
id|u32
id|iDataSize
suffix:semicolon
DECL|member|next
id|mega_scb
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* internal locking by the queue manipulting routines */
DECL|macro|INTERNAL_LOCK
mdefine_line|#define INTERNAL_LOCK   0
multiline_comment|/* external locking by the queue manipulting routines */
DECL|macro|EXTERNAL_LOCK
mdefine_line|#define EXTERNAL_LOCK   1
DECL|macro|NO_LOCK
mdefine_line|#define NO_LOCK&t;&t;2
DECL|macro|INTR_ENB
mdefine_line|#define INTR_ENB&t;0&t;/* do not disable interrupt while manipulating */
DECL|macro|INTR_DIS
mdefine_line|#define INTR_DIS&t;1&t;/* disable interrupt while manipulating */
multiline_comment|/* Per-controller data */
DECL|struct|_mega_host_config
r_typedef
r_struct
id|_mega_host_config
(brace
DECL|member|numldrv
id|u8
id|numldrv
suffix:semicolon
DECL|member|flag
id|u32
id|flag
suffix:semicolon
macro_line|#ifdef __LP64__
DECL|member|base
id|u64
id|base
suffix:semicolon
macro_line|#else
DECL|member|base
id|u32
id|base
suffix:semicolon
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
DECL|member|dma_handle64
DECL|member|adjdmahandle64
id|dma_addr_t
id|dma_handle64
comma
id|adjdmahandle64
suffix:semicolon
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
macro_line|#endif
DECL|member|qFreeH
id|mega_scb
op_star
id|qFreeH
suffix:semicolon
DECL|member|qFreeT
id|mega_scb
op_star
id|qFreeT
suffix:semicolon
DECL|member|lock_free
id|spinlock_t
id|lock_free
suffix:semicolon
DECL|member|qPendingH
id|mega_scb
op_star
id|qPendingH
suffix:semicolon
DECL|member|qPendingT
id|mega_scb
op_star
id|qPendingT
suffix:semicolon
DECL|member|lock_pend
id|spinlock_t
id|lock_pend
suffix:semicolon
DECL|member|qCompletedH
id|Scsi_Cmnd
op_star
id|qCompletedH
suffix:semicolon
DECL|member|qCompletedT
id|Scsi_Cmnd
op_star
id|qCompletedT
suffix:semicolon
DECL|member|lock_scsicmd
id|spinlock_t
id|lock_scsicmd
suffix:semicolon
DECL|member|qFcnt
id|u32
id|qFcnt
suffix:semicolon
DECL|member|qPcnt
id|u32
id|qPcnt
suffix:semicolon
DECL|member|qCcnt
id|u32
id|qCcnt
suffix:semicolon
DECL|member|nReads
r_int
r_int
id|nReads
(braket
id|FC_MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
DECL|member|nReadBlocks
r_int
r_int
id|nReadBlocks
(braket
id|FC_MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
DECL|member|nWrites
r_int
r_int
id|nWrites
(braket
id|FC_MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
DECL|member|nWriteBlocks
r_int
r_int
id|nWriteBlocks
(braket
id|FC_MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
DECL|member|nInterrupts
r_int
r_int
id|nInterrupts
suffix:semicolon
multiline_comment|/* Host adapter parameters */
DECL|member|fwVer
id|u8
id|fwVer
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|biosVer
id|u8
id|biosVer
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
DECL|member|mbox64
r_volatile
id|mega_mailbox64
op_star
id|mbox64
suffix:semicolon
multiline_comment|/* ptr to beginning of 64-bit mailbox */
DECL|member|mbox
r_volatile
id|mega_mailbox
op_star
id|mbox
suffix:semicolon
multiline_comment|/* ptr to beginning of standard mailbox */
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
multiline_comment|/* ptr to beginning of standard mailbox */
DECL|member|mailbox64ptr
r_volatile
id|mega_mailbox64
op_star
id|mailbox64ptr
suffix:semicolon
macro_line|#else
DECL|member|mailbox64
r_volatile
id|mega_mailbox64
id|mailbox64
suffix:semicolon
macro_line|#endif
DECL|member|mega_buffer
r_volatile
id|u8
id|mega_buffer
(braket
l_int|2
op_star
l_int|1024L
)braket
suffix:semicolon
DECL|member|productInfo
r_volatile
id|megaRaidProductInfo
id|productInfo
suffix:semicolon
DECL|member|max_cmds
id|u8
id|max_cmds
suffix:semicolon
DECL|member|scbList
id|mega_scb
id|scbList
(braket
id|MAX_COMMANDS
)braket
suffix:semicolon
DECL|macro|PROCBUFSIZE
mdefine_line|#define PROCBUFSIZE 4096
DECL|member|procbuf
r_char
id|procbuf
(braket
id|PROCBUFSIZE
)braket
suffix:semicolon
DECL|member|procidx
r_int
id|procidx
suffix:semicolon
DECL|member|controller_proc_dir_entry
r_struct
id|proc_dir_entry
op_star
id|controller_proc_dir_entry
suffix:semicolon
DECL|member|proc_read
DECL|member|proc_stat
DECL|member|proc_status
DECL|member|proc_mbox
r_struct
id|proc_dir_entry
op_star
id|proc_read
comma
op_star
id|proc_stat
comma
op_star
id|proc_status
comma
op_star
id|proc_mbox
suffix:semicolon
DECL|member|support_ext_cdb
r_int
id|support_ext_cdb
suffix:semicolon
DECL|member|boot_ldrv_enabled
r_int
id|boot_ldrv_enabled
suffix:semicolon
DECL|member|boot_ldrv
r_int
id|boot_ldrv
suffix:semicolon
DECL|member|support_random_del
r_int
id|support_random_del
suffix:semicolon
multiline_comment|/* Do we support random deletion of logdrvs */
DECL|member|read_ldidmap
r_int
id|read_ldidmap
suffix:semicolon
multiline_comment|/* set after logical drive deltion. The logical&n;&t;&t;&t;&t;&t;&t;&t;&t;drive number must be read from the map */
DECL|member|quiescent
r_int
id|quiescent
suffix:semicolon
multiline_comment|/* a stage reached when delete logical drive needs to&n;&t;&t;&t;&t;&t;&t;   be done. Stop sending requests to the hba till&n;&t;&t;&t;&t;&t;&t;   delete operation is completed */
DECL|member|int_qh
id|mega_scb
op_star
id|int_qh
suffix:semicolon
multiline_comment|/* commands are queued in the internal queue */
DECL|member|int_qt
id|mega_scb
op_star
id|int_qt
suffix:semicolon
multiline_comment|/* while the hba is quiescent */
DECL|member|int_qlen
r_int
id|int_qlen
suffix:semicolon
DECL|typedef|mega_host_config
)brace
id|mega_host_config
suffix:semicolon
DECL|struct|_driver_info
r_typedef
r_struct
id|_driver_info
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|version
id|ulong
id|version
suffix:semicolon
DECL|typedef|mega_driver_info
)brace
id|mega_driver_info
suffix:semicolon
multiline_comment|/*&n; * User ioctl structure.&n; * This structure will be used for Traditional Method ioctl interface&n; * commands (M_RD_IOCTL_CMD),Alternate Buffer Method (M_RD_IOCTL_CMD_NEW) &n; * ioctl commands and the Driver ioctls(M_RD_DRIVER_IOCTL_INTERFACE).&n; * The Driver ioctl interface handles the commands at&n; * the driver level, without being sent to the card.&n; */
DECL|macro|MEGADEVIOC
mdefine_line|#define MEGADEVIOC      0x84
multiline_comment|/* system call imposed limit. Change accordingly */
DECL|macro|IOCTL_MAX_DATALEN
mdefine_line|#define IOCTL_MAX_DATALEN       4096
macro_line|#pragma pack(1)
DECL|struct|uioctl_t
r_struct
id|uioctl_t
(brace
DECL|member|inlen
id|u32
id|inlen
suffix:semicolon
DECL|member|outlen
id|u32
id|outlen
suffix:semicolon
r_union
(brace
DECL|member|fca
id|u8
id|fca
(braket
l_int|16
)braket
suffix:semicolon
r_struct
(brace
DECL|member|opcode
id|u8
id|opcode
suffix:semicolon
DECL|member|subopcode
id|u8
id|subopcode
suffix:semicolon
DECL|member|adapno
id|u16
id|adapno
suffix:semicolon
macro_line|#if BITS_PER_LONG == 32
DECL|member|buffer
id|u8
op_star
id|buffer
suffix:semicolon
DECL|member|pad
id|u8
id|pad
(braket
l_int|4
)braket
suffix:semicolon
macro_line|#endif
macro_line|#if BITS_PER_LONG == 64
DECL|member|buffer
id|u8
op_star
id|buffer
suffix:semicolon
macro_line|#endif
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|fcs
)brace
id|fcs
suffix:semicolon
DECL|member|ui
)brace
id|ui
suffix:semicolon
DECL|member|mbox
id|u8
id|mbox
(braket
l_int|18
)braket
suffix:semicolon
multiline_comment|/* 16 bytes + 2 status bytes */
DECL|member|pthru
id|mega_passthru
id|pthru
suffix:semicolon
macro_line|#if BITS_PER_LONG == 32
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* buffer &lt;= 4096 for 0x80 commands */
DECL|member|pad
r_char
id|pad
(braket
l_int|4
)braket
suffix:semicolon
macro_line|#endif
macro_line|#if BITS_PER_LONG == 64
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#pragma pack()
multiline_comment|/*&n; * struct mcontroller is used to pass information about the controllers in the&n; * system. Its upto the application how to use the information. We are passing&n; * as much info about the cards as possible and useful. Before issuing the&n; * call to find information about the cards, the applicaiton needs to issue a&n; * ioctl first to find out the number of controllers in the system.&n; */
DECL|macro|MAX_CONTROLLERS
mdefine_line|#define MAX_CONTROLLERS 32
DECL|struct|mcontroller
r_struct
id|mcontroller
(brace
DECL|member|base
id|u64
id|base
suffix:semicolon
DECL|member|irq
id|u8
id|irq
suffix:semicolon
DECL|member|numldrv
id|u8
id|numldrv
suffix:semicolon
DECL|member|pcibus
id|u8
id|pcibus
suffix:semicolon
DECL|member|pcidev
id|u16
id|pcidev
suffix:semicolon
DECL|member|pcifun
id|u8
id|pcifun
suffix:semicolon
DECL|member|pciid
id|u16
id|pciid
suffix:semicolon
DECL|member|pcivendor
id|u16
id|pcivendor
suffix:semicolon
DECL|member|pcislot
id|u8
id|pcislot
suffix:semicolon
DECL|member|uid
id|u32
id|uid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mbox_passthru
r_struct
id|mbox_passthru
(brace
DECL|member|cmd
id|u8
id|cmd
suffix:semicolon
DECL|member|cmdid
id|u8
id|cmdid
suffix:semicolon
DECL|member|pad1
id|u16
id|pad1
suffix:semicolon
DECL|member|pad2
id|u32
id|pad2
suffix:semicolon
DECL|member|dataxferaddr
id|u32
id|dataxferaddr
suffix:semicolon
DECL|member|pad3
id|u8
id|pad3
suffix:semicolon
DECL|member|pad4
id|u8
id|pad4
suffix:semicolon
DECL|member|rsvd
id|u8
id|rsvd
suffix:semicolon
DECL|member|mboxbusy
id|u8
id|mboxbusy
suffix:semicolon
DECL|member|nstatus
id|u8
id|nstatus
suffix:semicolon
DECL|member|status
id|u8
id|status
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Defines for Driver IOCTL interface, Op-code:M_RD_DRIVER_IOCTL_INTERFACE&n; */
DECL|macro|MEGAIOC_MAGIC
mdefine_line|#define MEGAIOC_MAGIC  &t;&squot;m&squot;
DECL|macro|MEGAIOCCMD
mdefine_line|#define MEGAIOCCMD     &t;_IOWR(MEGAIOC_MAGIC, 0)&t;/* Mega IOCTL command */
DECL|macro|MEGAIOC_QNADAP
mdefine_line|#define MEGAIOC_QNADAP&t;&t;&squot;m&squot;&t;/* Query # of adapters */
DECL|macro|MEGAIOC_QDRVRVER
mdefine_line|#define MEGAIOC_QDRVRVER&t;&squot;e&squot;&t;/* Query driver version */
DECL|macro|MEGAIOC_QADAPINFO
mdefine_line|#define MEGAIOC_QADAPINFO   &t;&squot;g&squot;&t;/* Query adapter information */
DECL|macro|MKADAP
mdefine_line|#define MKADAP(adapno)&t;  &t;(MEGAIOC_MAGIC &lt;&lt; 8 | (adapno) )
DECL|macro|GETADAP
mdefine_line|#define GETADAP(mkadap)&t; &t;( (mkadap) ^ MEGAIOC_MAGIC &lt;&lt; 8 )
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0)&t;/*0x20300 */
r_extern
r_struct
id|proc_dir_entry
id|proc_scsi_megaraid
suffix:semicolon
macro_line|#endif
multiline_comment|/* For Host Re-Ordering */
DECL|macro|MAX_CONTROLLERS
mdefine_line|#define MAX_CONTROLLERS&t;32
DECL|struct|mega_hbas
r_struct
id|mega_hbas
(brace
DECL|member|is_bios_enabled
r_int
id|is_bios_enabled
suffix:semicolon
DECL|member|hostdata_addr
id|mega_host_config
op_star
id|hostdata_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IS_BIOS_ENABLED
mdefine_line|#define&t;&t;IS_BIOS_ENABLED&t;&t;0x62
DECL|macro|GET_BIOS
mdefine_line|#define&t;&t;GET_BIOS&t;&t;0x01
DECL|macro|CHNL_CLASS
mdefine_line|#define&t;&t;CHNL_CLASS&t;&t;0xA9
DECL|macro|GET_CHNL_CLASS
mdefine_line|#define&t;&t;GET_CHNL_CLASS&t;0x00
DECL|macro|SET_CHNL_CLASS
mdefine_line|#define&t;&t;SET_CHNL_CLASS&t;0x01
DECL|macro|CH_RAID
mdefine_line|#define&t;&t;CH_RAID&t;&t;&t;0x01
DECL|macro|CH_SCSI
mdefine_line|#define&t;&t;CH_SCSI&t;&t;&t;0x00
DECL|macro|BIOS_PVT_DATA
mdefine_line|#define BIOS_PVT_DATA&t;&t;0x40
DECL|macro|GET_BIOS_PVT_DATA
mdefine_line|#define GET_BIOS_PVT_DATA&t;0x00
macro_line|#pragma pack(1)
DECL|struct|private_bios_data
r_struct
id|private_bios_data
(brace
DECL|member|geometry
id|u8
id|geometry
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t;&t; * bits 0-3 - BIOS geometry&n;&t;&t;&t;&t;&t;&t;&t; * 0x0001 - 1GB&n;&t;&t;&t;&t;&t;&t;&t; * 0x0010 - 2GB&n;&t;&t;&t;&t;&t;&t;&t; * 0x1000 - 8GB&n;&t;&t;&t;&t;&t;&t;&t; * Others values are invalid&n;&t;&t;&t;&t;&t;&t;&t; */
DECL|member|unused
id|u8
id|unused
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* bits 4-7 are unused */
DECL|member|boot_ldrv
id|u8
id|boot_ldrv
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t;&t; * logical drive set as boot drive&n;&t;&t;&t;&t;&t;&t;&t; * 0..7 - for 8LD cards&n;&t;&t;&t;&t;&t;&t;&t; * 0..39 - for 40LD cards&n;&t;&t;&t;&t;&t;&t;&t; */
DECL|member|rsvd
id|u8
id|rsvd
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|cksum
id|u16
id|cksum
suffix:semicolon
multiline_comment|/* 0-(sum of first 13 bytes of this structure) */
)brace
suffix:semicolon
macro_line|#pragma pack()
DECL|macro|NVIRT_CHAN
mdefine_line|#define NVIRT_CHAN&t;&t;4&t;/* # of virtual channels to represent 60 logical&n;&t;&t;&t;&t;&t;&t;&t;drives */
multiline_comment|/*&n; * Command for random deletion of logical drives&n; */
DECL|macro|FC_DEL_LOGDRV
mdefine_line|#define&t;FC_DEL_LOGDRV&t;&t;0xA4&t;/* f/w command */
DECL|macro|OP_SUP_DEL_LOGDRV
mdefine_line|#define&t;OP_SUP_DEL_LOGDRV&t;0x2A&t;/* is feature supported */
DECL|macro|OP_GET_LDID_MAP
mdefine_line|#define OP_GET_LDID_MAP&t;&t;0x18&t;/* get logdrv id and logdrv number map */
DECL|macro|OP_DEL_LOGDRV
mdefine_line|#define OP_DEL_LOGDRV&t;&t;0x1C&t;/* delete logical drive */
multiline_comment|/*================================================================&n; *&n; *                    Function prototypes&n; *&n; *================================================================&n; */
r_const
r_char
op_star
id|megaraid_info
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|megaraid_detect
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|megaraid_release
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|megaraid_command
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|megaraid_abort
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|megaraid_reset
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|megaraid_queue
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_int
id|megaraid_biosparam
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|megaraid_proc_info
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
id|hostno
comma
r_int
id|inout
)paren
suffix:semicolon
r_static
r_int
id|megaIssueCmd
(paren
id|mega_host_config
op_star
id|megaCfg
comma
id|u_char
op_star
id|mboxData
comma
id|mega_scb
op_star
id|scb
comma
r_int
id|intr
)paren
suffix:semicolon
r_static
r_int
id|mega_build_sglist
(paren
id|mega_host_config
op_star
id|megaCfg
comma
id|mega_scb
op_star
id|scb
comma
id|u32
op_star
id|buffer
comma
id|u32
op_star
id|length
)paren
suffix:semicolon
r_static
r_int
id|mega_busyWaitMbox
(paren
id|mega_host_config
op_star
)paren
suffix:semicolon
r_static
r_int
id|mega_runpendq
(paren
id|mega_host_config
op_star
)paren
suffix:semicolon
r_static
r_void
id|mega_rundoneq
(paren
id|mega_host_config
op_star
)paren
suffix:semicolon
r_static
r_void
id|mega_cmd_done
(paren
id|mega_host_config
op_star
comma
id|mega_scb
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_inline
r_void
id|mega_freeSgList
(paren
id|mega_host_config
op_star
id|megaCfg
)paren
suffix:semicolon
r_static
r_void
id|mega_Convert8ldTo40ld
(paren
id|mega_RAIDINQ
op_star
id|inquiry
comma
id|mega_Enquiry3
op_star
id|enquiry3
comma
id|megaRaidProductInfo
op_star
id|productInfo
)paren
suffix:semicolon
r_static
r_int
id|megaraid_reboot_notify
(paren
r_struct
id|notifier_block
op_star
comma
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0)  
r_static
id|mega_scb
op_star
id|mega_ioctl
(paren
id|mega_host_config
op_star
id|megaCfg
comma
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_void
id|mega_build_kernel_sg
(paren
r_char
op_star
id|barea
comma
id|ulong
id|xfersize
comma
id|mega_scb
op_star
id|pScb
comma
id|mega_ioctl_mbox
op_star
id|mbox
)paren
suffix:semicolon
macro_line|#endif
r_static
r_int
id|megadev_open
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_static
r_int
id|megadev_ioctl_entry
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_int
id|megadev_ioctl
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_static
id|mega_scb
op_star
id|megadev_doioctl
(paren
id|mega_host_config
op_star
comma
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|megadev_close
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_static
r_void
id|megadev_ioctl_done
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|mega_init_scb
(paren
id|mega_host_config
op_star
)paren
suffix:semicolon
r_static
r_void
id|enq_scb_freelist
(paren
id|mega_host_config
op_star
comma
id|mega_scb
op_star
comma
r_int
id|lock
comma
r_int
id|intr
)paren
suffix:semicolon
r_static
r_int
id|mega_is_bios_enabled
(paren
id|mega_host_config
op_star
)paren
suffix:semicolon
r_static
r_void
id|mega_reorder_hosts
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|mega_swap_hosts
(paren
r_struct
id|Scsi_Host
op_star
comma
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_static
r_void
id|mega_create_proc_entry
(paren
r_int
id|index
comma
r_struct
id|proc_dir_entry
op_star
)paren
suffix:semicolon
r_static
r_int
id|mega_support_ext_cdb
c_func
(paren
id|mega_host_config
op_star
)paren
suffix:semicolon
r_static
id|mega_passthru
op_star
id|mega_prepare_passthru
c_func
(paren
id|mega_host_config
op_star
comma
id|mega_scb
op_star
comma
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
id|mega_ext_passthru
op_star
id|mega_prepare_extpassthru
c_func
(paren
id|mega_host_config
op_star
comma
id|mega_scb
op_star
comma
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_void
id|mega_enum_raid_scsi
c_func
(paren
id|mega_host_config
op_star
)paren
suffix:semicolon
r_static
r_int
id|mega_partsize
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
r_static
r_void
id|mega_get_boot_ldrv
c_func
(paren
id|mega_host_config
op_star
)paren
suffix:semicolon
r_static
r_int
id|mega_get_lun
c_func
(paren
id|mega_host_config
op_star
comma
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|mega_support_random_del
c_func
(paren
id|mega_host_config
op_star
)paren
suffix:semicolon
r_static
r_int
id|mega_del_logdrv
c_func
(paren
id|mega_host_config
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|mega_do_del_logdrv
c_func
(paren
id|mega_host_config
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* vi: set ts=4: */
eof
