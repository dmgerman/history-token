macro_line|#ifndef __MEGARAID_H__
DECL|macro|__MEGARAID_H__
mdefine_line|#define __MEGARAID_H__
macro_line|#ifndef LINUX_VERSION_CODE
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif
DECL|macro|IN_ISR
mdefine_line|#define IN_ISR                  0x80000000L
DECL|macro|IN_ABORT
mdefine_line|#define IN_ABORT                0x40000000L
DECL|macro|IN_RESET
mdefine_line|#define IN_RESET                0x20000000L
DECL|macro|IN_QUEUE
mdefine_line|#define IN_QUEUE                0x10000000L
DECL|macro|BOARD_QUARTZ
mdefine_line|#define BOARD_QUARTZ            0x08000000L
DECL|macro|BOARD_40LD
mdefine_line|#define BOARD_40LD              0x04000000L
macro_line|#ifndef HOSTS_C
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
macro_line|#endif
DECL|macro|MEGA_CMD_TIMEOUT
mdefine_line|#define MEGA_CMD_TIMEOUT        10
multiline_comment|/* Feel free to fiddle with these.. max values are:&n;   SGLIST     0..26&n;   COMMANDS   0..253&n;   CMDPERLUN  0..63&n;*/
DECL|macro|MAX_SGLIST
mdefine_line|#define MAX_SGLIST              0x1A
DECL|macro|MAX_COMMANDS
mdefine_line|#define MAX_COMMANDS            127
DECL|macro|MAX_CMD_PER_LUN
mdefine_line|#define MAX_CMD_PER_LUN         63
DECL|macro|MAX_FIRMWARE_STATUS
mdefine_line|#define MAX_FIRMWARE_STATUS     46
DECL|macro|MAX_LOGICAL_DRIVES
mdefine_line|#define MAX_LOGICAL_DRIVES      8
DECL|macro|MAX_CHANNEL
mdefine_line|#define MAX_CHANNEL             5
DECL|macro|MAX_TARGET
mdefine_line|#define MAX_TARGET              15
DECL|macro|MAX_PHYSICAL_DRIVES
mdefine_line|#define MAX_PHYSICAL_DRIVES     MAX_CHANNEL*MAX_TARGET
DECL|macro|INQUIRY_DATA_SIZE
mdefine_line|#define INQUIRY_DATA_SIZE       0x24
DECL|macro|MAX_CDB_LEN
mdefine_line|#define MAX_CDB_LEN             0x0A
DECL|macro|MAX_REQ_SENSE_LEN
mdefine_line|#define MAX_REQ_SENSE_LEN       0x20
DECL|macro|INTR_VALID
mdefine_line|#define INTR_VALID              0x40
multiline_comment|/* Mailbox commands */
DECL|macro|MEGA_MBOXCMD_LREAD
mdefine_line|#define MEGA_MBOXCMD_LREAD      0x01
DECL|macro|MEGA_MBOXCMD_LWRITE
mdefine_line|#define MEGA_MBOXCMD_LWRITE     0x02
DECL|macro|MEGA_MBOXCMD_PASSTHRU
mdefine_line|#define MEGA_MBOXCMD_PASSTHRU   0x03
DECL|macro|MEGA_MBOXCMD_ADAPTERINQ
mdefine_line|#define MEGA_MBOXCMD_ADAPTERINQ 0x05
multiline_comment|/* Offsets into Mailbox */
DECL|macro|COMMAND_PORT
mdefine_line|#define COMMAND_PORT       0x00
DECL|macro|COMMAND_ID_PORT
mdefine_line|#define COMMAND_ID_PORT    0x01
DECL|macro|SG_LIST_PORT0
mdefine_line|#define SG_LIST_PORT0      0x08
DECL|macro|SG_LIST_PORT1
mdefine_line|#define SG_LIST_PORT1      0x09
DECL|macro|SG_LIST_PORT2
mdefine_line|#define SG_LIST_PORT2      0x0a
DECL|macro|SG_LIST_PORT3
mdefine_line|#define SG_LIST_PORT3      0x0b
DECL|macro|SG_ELEMENT_PORT
mdefine_line|#define SG_ELEMENT_PORT    0x0d
DECL|macro|NO_FIRED_PORT
mdefine_line|#define NO_FIRED_PORT      0x0f
multiline_comment|/* I/O Port offsets */
DECL|macro|I_CMD_PORT
mdefine_line|#define I_CMD_PORT         0x00
DECL|macro|I_ACK_PORT
mdefine_line|#define I_ACK_PORT         0x00
DECL|macro|I_TOGGLE_PORT
mdefine_line|#define I_TOGGLE_PORT      0x01
DECL|macro|INTR_PORT
mdefine_line|#define INTR_PORT          0x0a
DECL|macro|MAILBOX_SIZE
mdefine_line|#define MAILBOX_SIZE       (sizeof(mega_mailbox)-16)
DECL|macro|MBOX_BUSY_PORT
mdefine_line|#define MBOX_BUSY_PORT     0x00
DECL|macro|MBOX_PORT0
mdefine_line|#define MBOX_PORT0         0x04
DECL|macro|MBOX_PORT1
mdefine_line|#define MBOX_PORT1         0x05
DECL|macro|MBOX_PORT2
mdefine_line|#define MBOX_PORT2         0x06
DECL|macro|MBOX_PORT3
mdefine_line|#define MBOX_PORT3         0x07
DECL|macro|ENABLE_MBOX_REGION
mdefine_line|#define ENABLE_MBOX_REGION 0x0B
multiline_comment|/* I/O Port Values */
DECL|macro|ISSUE_BYTE
mdefine_line|#define ISSUE_BYTE         0x10
DECL|macro|ACK_BYTE
mdefine_line|#define ACK_BYTE           0x08
DECL|macro|ENABLE_INTR_BYTE
mdefine_line|#define ENABLE_INTR_BYTE   0xc0
DECL|macro|DISABLE_INTR_BYTE
mdefine_line|#define DISABLE_INTR_BYTE  0x00
DECL|macro|VALID_INTR_BYTE
mdefine_line|#define VALID_INTR_BYTE    0x40
DECL|macro|MBOX_BUSY_BYTE
mdefine_line|#define MBOX_BUSY_BYTE     0x10
DECL|macro|ENABLE_MBOX_BYTE
mdefine_line|#define ENABLE_MBOX_BYTE   0x00
multiline_comment|/* Setup some port macros here */
DECL|macro|WRITE_MAILBOX
mdefine_line|#define WRITE_MAILBOX(base,offset,value)   *(base+offset)=value
DECL|macro|READ_MAILBOX
mdefine_line|#define READ_MAILBOX(base,offset)          *(base+offset)
DECL|macro|WRITE_PORT
mdefine_line|#define WRITE_PORT(base,offset,value)      outb_p(value,base+offset)
DECL|macro|READ_PORT
mdefine_line|#define READ_PORT(base,offset)             inb_p(base+offset)
DECL|macro|ISSUE_COMMAND
mdefine_line|#define ISSUE_COMMAND(base)   WRITE_PORT(base,I_CMD_PORT,ISSUE_BYTE)
DECL|macro|CLEAR_INTR
mdefine_line|#define CLEAR_INTR(base)      WRITE_PORT(base,I_ACK_PORT,ACK_BYTE)
DECL|macro|ENABLE_INTR
mdefine_line|#define ENABLE_INTR(base)     WRITE_PORT(base,I_TOGGLE_PORT,ENABLE_INTR_BYTE)
DECL|macro|DISABLE_INTR
mdefine_line|#define DISABLE_INTR(base)    WRITE_PORT(base,I_TOGGLE_PORT,DISABLE_INTR_BYTE)
multiline_comment|/* Define AMI&squot;s PCI codes */
DECL|macro|PCI_VENDOR_ID_AMI
macro_line|#undef PCI_VENDOR_ID_AMI
DECL|macro|PCI_DEVICE_ID_AMI_MEGARAID
macro_line|#undef PCI_DEVICE_ID_AMI_MEGARAID
macro_line|#ifndef PCI_VENDOR_ID_AMI
DECL|macro|PCI_VENDOR_ID_AMI
mdefine_line|#define PCI_VENDOR_ID_AMI          0x101E
DECL|macro|PCI_DEVICE_ID_AMI_MEGARAID
mdefine_line|#define PCI_DEVICE_ID_AMI_MEGARAID 0x9010
macro_line|#endif
DECL|macro|PCI_CONF_BASE_ADDR_OFFSET
mdefine_line|#define PCI_CONF_BASE_ADDR_OFFSET  0x10
DECL|macro|PCI_CONF_IRQ_OFFSET
mdefine_line|#define PCI_CONF_IRQ_OFFSET        0x3c
DECL|macro|PCI_CONF_AMISIG
mdefine_line|#define PCI_CONF_AMISIG            0xa0
DECL|macro|AMI_SIGNATURE
mdefine_line|#define AMI_SIGNATURE              0x3344
DECL|macro|AMI_SIGNATURE_471
mdefine_line|#define AMI_SIGNATURE_471          0xCCCC
macro_line|#if LINUX_VERSION_CODE &lt; 0x20100
DECL|macro|MEGARAID
mdefine_line|#define MEGARAID &bslash;&n;  { NULL,                               /* Next                      */&bslash;&n;    NULL,                               /* Usage Count Pointer       */&bslash;&n;    NULL,                               /* /proc Directory Entry     */&bslash;&n;    megaraid_proc_info,                 /* /proc Info Function       */&bslash;&n;    &quot;MegaRAID&quot;,                         /* Driver Name               */&bslash;&n;    megaraid_detect,                    /* Detect Host Adapter       */&bslash;&n;    megaraid_release,                   /* Release Host Adapter      */&bslash;&n;    megaraid_info,                      /* Driver Info Function      */&bslash;&n;    megaraid_command,                   /* Command Function          */&bslash;&n;    megaraid_queue,                     /* Queue Command Function    */&bslash;&n;    megaraid_abort,                     /* Abort Command Function    */&bslash;&n;    megaraid_reset,                     /* Reset Command Function    */&bslash;&n;    NULL,                               /* Slave Attach Function     */&bslash;&n;    megaraid_biosparam,                 /* Disk BIOS Parameters      */&bslash;&n;    MAX_COMMANDS,                       /* # of cmds that can be&bslash;&n;                                           outstanding at any time */&bslash;&n;    7,                                  /* HBA Target ID             */&bslash;&n;    MAX_SGLIST,                         /* Scatter/Gather Table Size */&bslash;&n;    MAX_CMD_PER_LUN,                    /* SCSI Commands per LUN     */&bslash;&n;    0,                                  /* Present                   */&bslash;&n;    0,                                  /* Default Unchecked ISA DMA */&bslash;&n;    ENABLE_CLUSTERING }&t;&t;/* Enable Clustering         */
macro_line|#else
DECL|macro|MEGARAID
mdefine_line|#define MEGARAID &bslash;&n;  {&bslash;&n;    name:            &quot;MegaRAID&quot;,               /* Driver Name               */&bslash;&n;    proc_info:        megaraid_proc_info,      /* /proc driver info         */&bslash;&n;    detect:           megaraid_detect,         /* Detect Host Adapter       */&bslash;&n;    release:          megaraid_release,        /* Release Host Adapter      */&bslash;&n;    info:             megaraid_info,           /* Driver Info Function      */&bslash;&n;    command:          megaraid_command,        /* Command Function          */&bslash;&n;    queuecommand:     megaraid_queue,          /* Queue Command Function    */&bslash;&n;    abort:            megaraid_abort,          /* Abort Command Function    */&bslash;&n;    reset:            megaraid_reset,          /* Reset Command Function    */&bslash;&n;    bios_param:       megaraid_biosparam,      /* Disk BIOS Parameters      */&bslash;&n;    can_queue:        MAX_COMMANDS,            /* Can Queue                 */&bslash;&n;    this_id:          7,                       /* HBA Target ID             */&bslash;&n;    sg_tablesize:     MAX_SGLIST,              /* Scatter/Gather Table Size */&bslash;&n;    cmd_per_lun:      MAX_CMD_PER_LUN,         /* SCSI Commands per LUN     */&bslash;&n;    present:          0,                       /* Present                   */&bslash;&n;    unchecked_isa_dma:0,                       /* Default Unchecked ISA DMA */&bslash;&n;    use_clustering:   ENABLE_CLUSTERING        /* Enable Clustering         */&bslash;&n;  }
macro_line|#endif
multiline_comment|/***********************************************************************&n; * Structure Declarations for the Firmware supporting 40 Logical Drives&n; * and 256 Physical Drives.&n; ***********************************************************************/
DECL|macro|FC_MAX_LOGICAL_DRIVES
mdefine_line|#define FC_MAX_LOGICAL_DRIVES       40
DECL|macro|FC_MAX_LOG_DEVICES
mdefine_line|#define FC_MAX_LOG_DEVICES          FC_MAX_LOGICAL_DRIVES
DECL|macro|FC_MAX_SPAN_DEPTH
mdefine_line|#define FC_MAX_SPAN_DEPTH           8
DECL|macro|FC_MAX_ROW_SIZE
mdefine_line|#define FC_MAX_ROW_SIZE             32
DECL|macro|FC_MAX_CHANNELS
mdefine_line|#define FC_MAX_CHANNELS             16
DECL|macro|FC_MAX_TARGETS_PER_CHANNEL
mdefine_line|#define FC_MAX_TARGETS_PER_CHANNEL  16
DECL|macro|FC_MAX_PHYSICAL_DEVICES
mdefine_line|#define FC_MAX_PHYSICAL_DEVICES     256
DECL|macro|FC_NEW_CONFIG
mdefine_line|#define FC_NEW_CONFIG               0xA1
DECL|macro|DCMD_FC_CMD
mdefine_line|#define DCMD_FC_CMD                 0xA1
DECL|macro|NC_SUBOP_PRODUCT_INFO
mdefine_line|#define NC_SUBOP_PRODUCT_INFO       0x0E
DECL|macro|NC_SUBOP_ENQUIRY3
mdefine_line|#define NC_SUBOP_ENQUIRY3           0x0F
DECL|macro|ENQ3_GET_SOLICITED_NOTIFY_ONLY
mdefine_line|#define ENQ3_GET_SOLICITED_NOTIFY_ONLY  0x01
DECL|macro|ENQ3_GET_SOLICITED_FULL
mdefine_line|#define ENQ3_GET_SOLICITED_FULL         0x02
DECL|macro|ENQ3_GET_UNSOLICITED
mdefine_line|#define ENQ3_GET_UNSOLICITED            0x03
multiline_comment|/********************************************&n; * PRODUCT_INFO Strucure&n; ********************************************/
DECL|macro|SIG_40LOG_32STR_8SPN
mdefine_line|#define SIG_40LOG_32STR_8SPN  0x00282008
multiline_comment|/* &n; * Utilities declare this strcture size as 1024 bytes. So more fields can&n; * be added in future.&n; */
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
multiline_comment|/* Current value is 0x00282008&n;                          * 0x28=MAX_LOGICAL_DRIVES, &n;                          * 0x20=Number of stripes and &n;                          * 0x08=Number of spans */
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
c_func
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
multiline_comment|/********************************************&n; * Standard ENQUIRY Strucure&n; ********************************************/
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
multiline_comment|/*&n;                              BIT 0 : battery module missing&n;                              BIT 1 : VBAD&n;                              BIT 2 : temp high&n;                              BIT 3 : battery pack missing&n;                              BIT 4,5 : 00 - charge complete&n;                                        01 - fast charge in prog&n;                                        10 - fast charge fail&n;                                        11 - undefined&n;                              BIt 6 : counter &gt; 1000&n;                              Bit 7 : undefined&n;                           */
DECL|member|dec_fault_bus_info
id|u8
id|dec_fault_bus_info
suffix:semicolon
multiline_comment|/* was resvd */
)brace
id|__attribute__
c_func
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
c_func
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
c_func
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
c_func
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
multiline_comment|/********************************************&n; * NOTIFICATION Strucure&n; ********************************************/
DECL|macro|MAX_NOTIFY_SIZE
mdefine_line|#define MAX_NOTIFY_SIZE     0x80
DECL|macro|CUR_NOTIFY_SIZE
mdefine_line|#define CUR_NOTIFY_SIZE     sizeof(struct MegaRAID_Notify)
multiline_comment|/* &n; * Utilities declare this strcture size as ?? bytes. So more fields can&n; * be added in future.&n; */
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
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/********************************************&n; * PARAM IDs in Notify struct&n; ********************************************/
DECL|macro|PARAM_RBLD_RATE
mdefine_line|#define PARAM_RBLD_RATE                 0x01
multiline_comment|/*--------------------------------------&n;     * Param val = &n;     *      byte 0: new rbld rate &n;     *--------------------------------------*/
DECL|macro|PARAM_CACHE_FLUSH_INTERVAL
mdefine_line|#define PARAM_CACHE_FLUSH_INTERVAL      0x02
multiline_comment|/*--------------------------------------&n;     * Param val = &n;     *      byte 0: new cache flush interval&n;     *--------------------------------------*/
DECL|macro|PARAM_SENSE_ALERT
mdefine_line|#define PARAM_SENSE_ALERT               0x03
multiline_comment|/*--------------------------------------&n;     * Param val = &n;     *      byte 0: last pdrv id causing chkcond&n;     *--------------------------------------*/
DECL|macro|PARAM_DRIVE_INSERTED
mdefine_line|#define PARAM_DRIVE_INSERTED            0x04
multiline_comment|/*--------------------------------------&n;     * Param val = &n;     *      byte 0: last pdrv id inserted&n;     *--------------------------------------*/
DECL|macro|PARAM_BATTERY_STATUS
mdefine_line|#define PARAM_BATTERY_STATUS            0x05
multiline_comment|/*--------------------------------------&n;     * Param val = &n;     *      byte 0: battery status&n;     *--------------------------------------*/
multiline_comment|/********************************************&n; * Ldrv operation cmd in Notify struct&n; ********************************************/
DECL|macro|LDRV_CMD_CHKCONSISTANCY
mdefine_line|#define LDRV_CMD_CHKCONSISTANCY         0x01
DECL|macro|LDRV_CMD_INITIALIZE
mdefine_line|#define LDRV_CMD_INITIALIZE             0x02
DECL|macro|LDRV_CMD_RECONSTRUCTION
mdefine_line|#define LDRV_CMD_RECONSTRUCTION         0x03
multiline_comment|/********************************************&n; * Ldrv operation status in Notify struct&n; ********************************************/
DECL|macro|LDRV_OP_SUCCESS
mdefine_line|#define&t;LDRV_OP_SUCCESS                 0x00
DECL|macro|LDRV_OP_FAILED
mdefine_line|#define&t;LDRV_OP_FAILED                  0x01
DECL|macro|LDRV_OP_ABORTED
mdefine_line|#define&t;LDRV_OP_ABORTED                 0x02
DECL|macro|LDRV_OP_CORRECTED
mdefine_line|#define&t;LDRV_OP_CORRECTED               0x03
DECL|macro|LDRV_OP_STARTED
mdefine_line|#define&t;LDRV_OP_STARTED                 0x04
multiline_comment|/********************************************&n; * Raid Logical drive states.&n; ********************************************/
DECL|macro|RDRV_OFFLINE
mdefine_line|#define     RDRV_OFFLINE                0
DECL|macro|RDRV_DEGRADED
mdefine_line|#define     RDRV_DEGRADED               1
DECL|macro|RDRV_OPTIMAL
mdefine_line|#define     RDRV_OPTIMAL                2
DECL|macro|RDRV_DELETED
mdefine_line|#define     RDRV_DELETED                3
multiline_comment|/*******************************************&n; * Physical drive states.&n; *******************************************/
DECL|macro|PDRV_UNCNF
mdefine_line|#define     PDRV_UNCNF                  0
DECL|macro|PDRV_ONLINE
mdefine_line|#define     PDRV_ONLINE                 3
DECL|macro|PDRV_FAILED
mdefine_line|#define     PDRV_FAILED                 4
DECL|macro|PDRV_RBLD
mdefine_line|#define     PDRV_RBLD                   5
multiline_comment|/* #define     PDRV_HOTSPARE               6 */
multiline_comment|/*******************************************&n; * Formal val in Notify struct&n; *******************************************/
DECL|macro|PDRV_FMT_START
mdefine_line|#define PDRV_FMT_START                  0x01
DECL|macro|PDRV_FMT_OVER
mdefine_line|#define PDRV_FMT_OVER                   0x02
multiline_comment|/********************************************&n; * FC Loop State in Notify Struct&n; ********************************************/
DECL|macro|ENQ_FCLOOP_FAILED
mdefine_line|#define ENQ_FCLOOP_FAILED               0
DECL|macro|ENQ_FCLOOP_ACTIVE
mdefine_line|#define ENQ_FCLOOP_ACTIVE               1
DECL|macro|ENQ_FCLOOP_TRANSIENT
mdefine_line|#define ENQ_FCLOOP_TRANSIENT            2
multiline_comment|/********************************************&n; * ENQUIRY3 Strucure&n; ********************************************/
multiline_comment|/* &n; * Utilities declare this strcture size as 1024 bytes. So more fields can&n; * be added in future.&n; */
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
c_func
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
singleline_comment|// RAID inquiry: Mailbox command 0x5
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
singleline_comment|// Passthrough command: Mailbox command 0x3
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
id|u8
id|mraid_poll
suffix:semicolon
DECL|member|mraid_ack
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
c_func
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
DECL|member|xferSegment
id|u32
id|xferSegment
suffix:semicolon
multiline_comment|/* for 64-bit controllers */
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
DECL|member|pthru
id|mega_passthru
id|pthru
suffix:semicolon
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
DECL|member|kern_area
r_char
op_star
id|kern_area
suffix:semicolon
multiline_comment|/* Only used for large ioctl xfers */
DECL|member|ioctl_wait
r_struct
id|wait_queue
op_star
id|ioctl_wait
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|next
id|mega_scb
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
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
DECL|member|base
id|u32
id|base
suffix:semicolon
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
id|u32
id|nReads
(braket
id|FC_MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
DECL|member|nWrites
id|u32
id|nWrites
(braket
id|FC_MAX_LOGICAL_DRIVES
)braket
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
DECL|member|mailbox64
r_volatile
id|mega_mailbox64
id|mailbox64
suffix:semicolon
macro_line|#if 0
r_volatile
r_union
(brace
id|u8
id|generic_buffer
(braket
l_int|2
op_star
l_int|1024L
)braket
suffix:semicolon
id|mega_RAIDINQ
id|adapterInfoData
suffix:semicolon
id|mega_Enquiry3
id|enquiry3Data
suffix:semicolon
)brace
id|mega_buffer
suffix:semicolon
macro_line|#else
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
macro_line|#endif
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
DECL|typedef|mega_host_config
)brace
id|mega_host_config
suffix:semicolon
r_const
r_char
op_star
id|megaraid_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|megaraid_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|megaraid_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|megaraid_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|megaraid_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|megaraid_reset
c_func
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
c_func
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
r_int
id|megaraid_proc_info
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
id|hostno
comma
r_int
id|inout
)paren
suffix:semicolon
macro_line|#endif
eof
