macro_line|#ifndef __MEGARAID_H__
DECL|macro|__MEGARAID_H__
mdefine_line|#define __MEGARAID_H__
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
DECL|macro|MEGARAID_VERSION
mdefine_line|#define MEGARAID_VERSION&t;&bslash;&n;&t;&quot;v2.00.3 (Release Date: Wed Feb 19 08:51:30 EST 2003)&bslash;n&quot;
multiline_comment|/*&n; * Driver features - change the values to enable or disable features in the&n; * driver.&n; */
multiline_comment|/*&n; * Comand coalescing - This feature allows the driver to be able to combine&n; * two or more commands and issue as one command in order to boost I/O&n; * performance. Useful if the nature of the I/O is sequential. It is not very&n; * useful for random natured I/Os.&n; */
DECL|macro|MEGA_HAVE_COALESCING
mdefine_line|#define MEGA_HAVE_COALESCING&t;0
multiline_comment|/*&n; * Clustering support - Set this flag if you are planning to use the&n; * clustering services provided by the megaraid controllers and planning to&n; * setup a cluster&n; */
DECL|macro|MEGA_HAVE_CLUSTERING
mdefine_line|#define MEGA_HAVE_CLUSTERING&t;1
multiline_comment|/*&n; * Driver statistics - Set this flag if you are interested in statics about&n; * number of I/O completed on each logical drive and how many interrupts&n; * generated. If enabled, this information is available through /proc&n; * interface and through the private ioctl. Setting this flag has a&n; * performance penalty.&n; */
DECL|macro|MEGA_HAVE_STATS
mdefine_line|#define MEGA_HAVE_STATS&t;&t;0
multiline_comment|/*&n; * Enhanced /proc interface - This feature will allow you to have a more&n; * detailed /proc interface for megaraid driver. E.g., a real time update of&n; * the status of the logical drives, battery status, physical drives etc.&n; */
DECL|macro|MEGA_HAVE_ENH_PROC
mdefine_line|#define MEGA_HAVE_ENH_PROC&t;1
DECL|macro|MAX_DEV_TYPE
mdefine_line|#define MAX_DEV_TYPE&t;32
macro_line|#ifndef PCI_VENDOR_ID_LSI_LOGIC
DECL|macro|PCI_VENDOR_ID_LSI_LOGIC
mdefine_line|#define PCI_VENDOR_ID_LSI_LOGIC&t;&t;0x1000
macro_line|#endif
macro_line|#ifndef PCI_VENDOR_ID_AMI
DECL|macro|PCI_VENDOR_ID_AMI
mdefine_line|#define PCI_VENDOR_ID_AMI&t;&t;0x101E
macro_line|#endif
macro_line|#ifndef PCI_VENDOR_ID_DELL
DECL|macro|PCI_VENDOR_ID_DELL
mdefine_line|#define PCI_VENDOR_ID_DELL&t;&t;0x1028
macro_line|#endif
macro_line|#ifndef PCI_VENDOR_ID_INTEL
DECL|macro|PCI_VENDOR_ID_INTEL
mdefine_line|#define PCI_VENDOR_ID_INTEL&t;&t;0x8086
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
DECL|macro|PCI_DEVICE_ID_DISCOVERY
mdefine_line|#define PCI_DEVICE_ID_DISCOVERY&t;&t;0x000E
DECL|macro|PCI_DEVICE_ID_PERC4_DI
mdefine_line|#define PCI_DEVICE_ID_PERC4_DI&t;&t;0x000F
DECL|macro|PCI_DEVICE_ID_PERC4_QC_VERDE
mdefine_line|#define PCI_DEVICE_ID_PERC4_QC_VERDE&t;0x0407
multiline_comment|/* Sub-System Vendor IDs */
DECL|macro|AMI_SUBSYS_VID
mdefine_line|#define&t;AMI_SUBSYS_VID&t;&t;&t;0x101E
DECL|macro|DELL_SUBSYS_VID
mdefine_line|#define DELL_SUBSYS_VID&t;&t;&t;0x1028
DECL|macro|HP_SUBSYS_VID
mdefine_line|#define&t;HP_SUBSYS_VID&t;&t;&t;0x103C
DECL|macro|LSI_SUBSYS_VID
mdefine_line|#define LSI_SUBSYS_VID&t;&t;&t;0x1000
DECL|macro|HBA_SIGNATURE
mdefine_line|#define HBA_SIGNATURE&t;      &t;&t;0x3344
DECL|macro|HBA_SIGNATURE_471
mdefine_line|#define HBA_SIGNATURE_471&t;  &t;0xCCCC
DECL|macro|HBA_SIGNATURE_64BIT
mdefine_line|#define HBA_SIGNATURE_64BIT&t;&t;0x0299
DECL|macro|MBOX_BUSY_WAIT
mdefine_line|#define MBOX_BUSY_WAIT&t;&t;&t;10&t;/* wait for up to 10 usec for&n;&t;&t;&t;&t;&t;&t;   mailbox to be free */
DECL|macro|DEFAULT_INITIATOR_ID
mdefine_line|#define DEFAULT_INITIATOR_ID&t;7
DECL|macro|MAX_SGLIST
mdefine_line|#define MAX_SGLIST&t;&t;64&t;/* max supported in f/w */
DECL|macro|MIN_SGLIST
mdefine_line|#define MIN_SGLIST&t;&t;26&t;/* guaranteed to support these many */
DECL|macro|MAX_COMMANDS
mdefine_line|#define MAX_COMMANDS&t;&t;126
DECL|macro|CMDID_INT_CMDS
mdefine_line|#define CMDID_INT_CMDS&t;&t;MAX_COMMANDS+1&t;/* make sure CMDID_INT_CMDS&n;&t;&t;&t;&t;&t; &t;is less than max commands&n;&t;&t;&t;&t;&t;&t;supported by any f/w */
DECL|macro|MAX_CDB_LEN
mdefine_line|#define MAX_CDB_LEN&t;     &t;10
DECL|macro|MAX_EXT_CDB_LEN
mdefine_line|#define MAX_EXT_CDB_LEN&t;&t;16&t;/* we support cdb length up to 16 */
DECL|macro|DEF_CMD_PER_LUN
mdefine_line|#define DEF_CMD_PER_LUN&t;&t;63
DECL|macro|MAX_CMD_PER_LUN
mdefine_line|#define MAX_CMD_PER_LUN&t;&t;MAX_COMMANDS
DECL|macro|MAX_FIRMWARE_STATUS
mdefine_line|#define MAX_FIRMWARE_STATUS&t;46
DECL|macro|MAX_XFER_PER_CMD
mdefine_line|#define MAX_XFER_PER_CMD&t;(64*1024)
DECL|macro|MAX_SECTORS_PER_IO
mdefine_line|#define MAX_SECTORS_PER_IO&t;128
DECL|macro|MAX_LOGICAL_DRIVES_40LD
mdefine_line|#define MAX_LOGICAL_DRIVES_40LD&t;&t;40
DECL|macro|FC_MAX_PHYSICAL_DEVICES
mdefine_line|#define FC_MAX_PHYSICAL_DEVICES&t;&t;256
DECL|macro|MAX_LOGICAL_DRIVES_8LD
mdefine_line|#define MAX_LOGICAL_DRIVES_8LD&t;&t;8
DECL|macro|MAX_CHANNELS
mdefine_line|#define MAX_CHANNELS&t;&t;&t;5
DECL|macro|MAX_TARGET
mdefine_line|#define MAX_TARGET&t;&t;&t;15
DECL|macro|MAX_PHYSICAL_DRIVES
mdefine_line|#define MAX_PHYSICAL_DRIVES&t;&t;MAX_CHANNELS*MAX_TARGET
DECL|macro|MAX_ROW_SIZE_40LD
mdefine_line|#define MAX_ROW_SIZE_40LD&t;&t;32
DECL|macro|MAX_ROW_SIZE_8LD
mdefine_line|#define MAX_ROW_SIZE_8LD&t;&t;8
DECL|macro|MAX_SPAN_DEPTH
mdefine_line|#define MAX_SPAN_DEPTH&t;&t;&t;8
DECL|macro|NVIRT_CHAN
mdefine_line|#define NVIRT_CHAN&t;&t;4&t;/* # of virtual channels to represent&n;&t;&t;&t;&t;&t;   up to 60 logical drives */
r_typedef
r_struct
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
r_volatile
id|u8
id|busy
suffix:semicolon
DECL|member|numstatus
multiline_comment|/* 0x10 */
r_volatile
id|u8
id|numstatus
suffix:semicolon
DECL|member|status
multiline_comment|/* 0x11 */
r_volatile
id|u8
id|status
suffix:semicolon
DECL|member|completed
multiline_comment|/* 0x12 */
r_volatile
id|u8
id|completed
(braket
id|MAX_FIRMWARE_STATUS
)braket
suffix:semicolon
DECL|member|poll
r_volatile
id|u8
id|poll
suffix:semicolon
DECL|member|ack
r_volatile
id|u8
id|ack
suffix:semicolon
DECL|typedef|mbox_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|mbox_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|xfer_segment_lo
id|u32
id|xfer_segment_lo
suffix:semicolon
DECL|member|xfer_segment_hi
id|u32
id|xfer_segment_hi
suffix:semicolon
DECL|member|mbox
id|mbox_t
id|mbox
suffix:semicolon
DECL|typedef|mbox64_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|mbox64_t
suffix:semicolon
multiline_comment|/*&n; * Passthru definitions&n; */
DECL|macro|MAX_REQ_SENSE_LEN
mdefine_line|#define MAX_REQ_SENSE_LEN       0x20
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
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
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
id|MAX_EXT_CDB_LEN
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
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|mega_ext_passthru
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|address
id|u64
id|address
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|typedef|mega_sgl64
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|mega_sgl64
suffix:semicolon
r_typedef
r_struct
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
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|mega_sglist
suffix:semicolon
multiline_comment|/* Queued command data */
r_typedef
r_struct
(brace
DECL|member|idx
r_int
id|idx
suffix:semicolon
DECL|member|state
id|u32
id|state
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|raw_mbox
id|u8
id|raw_mbox
(braket
l_int|66
)braket
suffix:semicolon
DECL|member|dma_type
id|u32
id|dma_type
suffix:semicolon
DECL|member|dma_direction
id|u32
id|dma_direction
suffix:semicolon
DECL|member|cmd
id|Scsi_Cmnd
op_star
id|cmd
suffix:semicolon
DECL|member|dma_h_bulkdata
id|dma_addr_t
id|dma_h_bulkdata
suffix:semicolon
DECL|member|dma_h_sgdata
id|dma_addr_t
id|dma_h_sgdata
suffix:semicolon
DECL|member|sgl
id|mega_sglist
op_star
id|sgl
suffix:semicolon
DECL|member|sgl64
id|mega_sgl64
op_star
id|sgl64
suffix:semicolon
DECL|member|sgl_dma_addr
id|dma_addr_t
id|sgl_dma_addr
suffix:semicolon
DECL|member|pthru
id|mega_passthru
op_star
id|pthru
suffix:semicolon
DECL|member|pthru_dma_addr
id|dma_addr_t
id|pthru_dma_addr
suffix:semicolon
DECL|member|epthru
id|mega_ext_passthru
op_star
id|epthru
suffix:semicolon
DECL|member|epthru_dma_addr
id|dma_addr_t
id|epthru_dma_addr
suffix:semicolon
DECL|typedef|scb_t
)brace
id|scb_t
suffix:semicolon
multiline_comment|/*&n; * Flags to follow the scb as it transitions between various stages&n; */
DECL|macro|SCB_FREE
mdefine_line|#define SCB_FREE&t;0x0000&t;/* on the free list */
DECL|macro|SCB_ACTIVE
mdefine_line|#define SCB_ACTIVE&t;0x0001&t;/* off the free list */
DECL|macro|SCB_PENDQ
mdefine_line|#define SCB_PENDQ&t;0x0002&t;/* on the pending queue */
DECL|macro|SCB_ISSUED
mdefine_line|#define SCB_ISSUED&t;0x0004&t;/* issued - owner f/w */
DECL|macro|SCB_ABORT
mdefine_line|#define SCB_ABORT&t;0x0008&t;/* Got an abort for this one */
DECL|macro|SCB_RESET
mdefine_line|#define SCB_RESET&t;0x0010&t;/* Got a reset for this one */
multiline_comment|/*&n; * Utilities declare this strcture size as 1024 bytes. So more fields can&n; * be added in future.&n; */
r_typedef
r_struct
(brace
DECL|member|data_size
id|u32
id|data_size
suffix:semicolon
multiline_comment|/* current size in bytes (not including resvd) */
DECL|member|config_signature
id|u32
id|config_signature
suffix:semicolon
multiline_comment|/* Current value is 0x00282008&n;&t;&t; * 0x28=MAX_LOGICAL_DRIVES,&n;&t;&t; * 0x20=Number of stripes and&n;&t;&t; * 0x08=Number of spans */
DECL|member|fw_version
id|u8
id|fw_version
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* printable ASCI string */
DECL|member|bios_version
id|u8
id|bios_version
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* printable ASCI string */
DECL|member|product_name
id|u8
id|product_name
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* printable ASCI string */
DECL|member|max_commands
id|u8
id|max_commands
suffix:semicolon
multiline_comment|/* Max. concurrent commands supported */
DECL|member|nchannels
id|u8
id|nchannels
suffix:semicolon
multiline_comment|/* Number of SCSI Channels detected */
DECL|member|fc_loop_present
id|u8
id|fc_loop_present
suffix:semicolon
multiline_comment|/* Number of Fibre Loops detected */
DECL|member|mem_type
id|u8
id|mem_type
suffix:semicolon
multiline_comment|/* EDO, FPM, SDRAM etc */
DECL|member|signature
id|u32
id|signature
suffix:semicolon
DECL|member|dram_size
id|u16
id|dram_size
suffix:semicolon
multiline_comment|/* In terms of MB */
DECL|member|subsysid
id|u16
id|subsysid
suffix:semicolon
DECL|member|subsysvid
id|u16
id|subsysvid
suffix:semicolon
DECL|member|notify_counters
id|u8
id|notify_counters
suffix:semicolon
DECL|member|pad1k
id|u8
id|pad1k
(braket
l_int|889
)braket
suffix:semicolon
multiline_comment|/* 135 + 889 resvd = 1024 total size */
DECL|typedef|mega_product_info
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|mega_product_info
suffix:semicolon
DECL|struct|notify
r_struct
id|notify
(brace
DECL|member|global_counter
id|u32
id|global_counter
suffix:semicolon
multiline_comment|/* Any change increments this counter */
DECL|member|param_counter
id|u8
id|param_counter
suffix:semicolon
multiline_comment|/* Indicates any params changed  */
DECL|member|param_id
id|u8
id|param_id
suffix:semicolon
multiline_comment|/* Param modified - defined below */
DECL|member|param_val
id|u16
id|param_val
suffix:semicolon
multiline_comment|/* New val of last param modified */
DECL|member|write_config_counter
id|u8
id|write_config_counter
suffix:semicolon
multiline_comment|/* write config occurred */
DECL|member|write_config_rsvd
id|u8
id|write_config_rsvd
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ldrv_op_counter
id|u8
id|ldrv_op_counter
suffix:semicolon
multiline_comment|/* Indicates ldrv op started/completed */
DECL|member|ldrv_opid
id|u8
id|ldrv_opid
suffix:semicolon
multiline_comment|/* ldrv num */
DECL|member|ldrv_opcmd
id|u8
id|ldrv_opcmd
suffix:semicolon
multiline_comment|/* ldrv operation - defined below */
DECL|member|ldrv_opstatus
id|u8
id|ldrv_opstatus
suffix:semicolon
multiline_comment|/* status of the operation */
DECL|member|ldrv_state_counter
id|u8
id|ldrv_state_counter
suffix:semicolon
multiline_comment|/* Indicates change of ldrv state */
DECL|member|ldrv_state_id
id|u8
id|ldrv_state_id
suffix:semicolon
multiline_comment|/* ldrv num */
DECL|member|ldrv_state_new
id|u8
id|ldrv_state_new
suffix:semicolon
multiline_comment|/* New state */
DECL|member|ldrv_state_old
id|u8
id|ldrv_state_old
suffix:semicolon
multiline_comment|/* old state */
DECL|member|pdrv_state_counter
id|u8
id|pdrv_state_counter
suffix:semicolon
multiline_comment|/* Indicates change of ldrv state */
DECL|member|pdrv_state_id
id|u8
id|pdrv_state_id
suffix:semicolon
multiline_comment|/* pdrv id */
DECL|member|pdrv_state_new
id|u8
id|pdrv_state_new
suffix:semicolon
multiline_comment|/* New state */
DECL|member|pdrv_state_old
id|u8
id|pdrv_state_old
suffix:semicolon
multiline_comment|/* old state */
DECL|member|pdrv_fmt_counter
id|u8
id|pdrv_fmt_counter
suffix:semicolon
multiline_comment|/* Indicates pdrv format started/over */
DECL|member|pdrv_fmt_id
id|u8
id|pdrv_fmt_id
suffix:semicolon
multiline_comment|/* pdrv id */
DECL|member|pdrv_fmt_val
id|u8
id|pdrv_fmt_val
suffix:semicolon
multiline_comment|/* format started/over */
DECL|member|pdrv_fmt_rsvd
id|u8
id|pdrv_fmt_rsvd
suffix:semicolon
DECL|member|targ_xfer_counter
id|u8
id|targ_xfer_counter
suffix:semicolon
multiline_comment|/* Indicates SCSI-2 Xfer rate change */
DECL|member|targ_xfer_id
id|u8
id|targ_xfer_id
suffix:semicolon
multiline_comment|/* pdrv Id  */
DECL|member|targ_xfer_val
id|u8
id|targ_xfer_val
suffix:semicolon
multiline_comment|/* new Xfer params of last pdrv */
DECL|member|targ_xfer_rsvd
id|u8
id|targ_xfer_rsvd
suffix:semicolon
DECL|member|fcloop_id_chg_counter
id|u8
id|fcloop_id_chg_counter
suffix:semicolon
multiline_comment|/* Indicates loopid changed */
DECL|member|fcloopid_pdrvid
id|u8
id|fcloopid_pdrvid
suffix:semicolon
multiline_comment|/* pdrv id */
DECL|member|fcloop_id0
id|u8
id|fcloop_id0
suffix:semicolon
multiline_comment|/* loopid on fc loop 0 */
DECL|member|fcloop_id1
id|u8
id|fcloop_id1
suffix:semicolon
multiline_comment|/* loopid on fc loop 1 */
DECL|member|fcloop_state_counter
id|u8
id|fcloop_state_counter
suffix:semicolon
multiline_comment|/* Indicates loop state changed */
DECL|member|fcloop_state0
id|u8
id|fcloop_state0
suffix:semicolon
multiline_comment|/* state of fc loop 0 */
DECL|member|fcloop_state1
id|u8
id|fcloop_state1
suffix:semicolon
multiline_comment|/* state of fc loop 1 */
DECL|member|fcloop_state_rsvd
id|u8
id|fcloop_state_rsvd
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|MAX_NOTIFY_SIZE
mdefine_line|#define MAX_NOTIFY_SIZE     0x80
DECL|macro|CUR_NOTIFY_SIZE
mdefine_line|#define CUR_NOTIFY_SIZE     sizeof(struct notify)
r_typedef
r_struct
(brace
DECL|member|data_size
id|u32
id|data_size
suffix:semicolon
multiline_comment|/* current size in bytes (not including resvd) */
DECL|member|notify
r_struct
id|notify
id|notify
suffix:semicolon
DECL|member|notify_rsvd
id|u8
id|notify_rsvd
(braket
id|MAX_NOTIFY_SIZE
op_minus
id|CUR_NOTIFY_SIZE
)braket
suffix:semicolon
DECL|member|rebuild_rate
id|u8
id|rebuild_rate
suffix:semicolon
multiline_comment|/* Rebuild rate (0% - 100%) */
DECL|member|cache_flush_interval
id|u8
id|cache_flush_interval
suffix:semicolon
multiline_comment|/* In terms of Seconds */
DECL|member|sense_alert
id|u8
id|sense_alert
suffix:semicolon
DECL|member|drive_insert_count
id|u8
id|drive_insert_count
suffix:semicolon
multiline_comment|/* drive insertion count */
DECL|member|battery_status
id|u8
id|battery_status
suffix:semicolon
DECL|member|num_ldrv
id|u8
id|num_ldrv
suffix:semicolon
multiline_comment|/* No. of Log Drives configured */
DECL|member|recon_state
id|u8
id|recon_state
(braket
id|MAX_LOGICAL_DRIVES_40LD
op_div
l_int|8
)braket
suffix:semicolon
multiline_comment|/* State of&n;&t;&t;&t;&t;&t;&t;&t;   reconstruct */
DECL|member|ldrv_op_status
id|u16
id|ldrv_op_status
(braket
id|MAX_LOGICAL_DRIVES_40LD
op_div
l_int|8
)braket
suffix:semicolon
multiline_comment|/* logdrv&n;&t;&t;&t;&t;&t;&t;&t;&t; Status */
DECL|member|ldrv_size
id|u32
id|ldrv_size
(braket
id|MAX_LOGICAL_DRIVES_40LD
)braket
suffix:semicolon
multiline_comment|/* Size of each log drv */
DECL|member|ldrv_prop
id|u8
id|ldrv_prop
(braket
id|MAX_LOGICAL_DRIVES_40LD
)braket
suffix:semicolon
DECL|member|ldrv_state
id|u8
id|ldrv_state
(braket
id|MAX_LOGICAL_DRIVES_40LD
)braket
suffix:semicolon
multiline_comment|/* State of log drives */
DECL|member|pdrv_state
id|u8
id|pdrv_state
(braket
id|FC_MAX_PHYSICAL_DEVICES
)braket
suffix:semicolon
multiline_comment|/* State of phys drvs. */
DECL|member|pdrv_format
id|u16
id|pdrv_format
(braket
id|FC_MAX_PHYSICAL_DEVICES
op_div
l_int|16
)braket
suffix:semicolon
DECL|member|targ_xfer
id|u8
id|targ_xfer
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
DECL|typedef|mega_inquiry3
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|mega_inquiry3
suffix:semicolon
multiline_comment|/* Structures */
r_typedef
r_struct
(brace
DECL|member|max_commands
id|u8
id|max_commands
suffix:semicolon
multiline_comment|/* Max concurrent commands supported */
DECL|member|rebuild_rate
id|u8
id|rebuild_rate
suffix:semicolon
multiline_comment|/* Rebuild rate - 0% thru 100% */
DECL|member|max_targ_per_chan
id|u8
id|max_targ_per_chan
suffix:semicolon
multiline_comment|/* Max targ per channel */
DECL|member|nchannels
id|u8
id|nchannels
suffix:semicolon
multiline_comment|/* Number of channels on HBA */
DECL|member|fw_version
id|u8
id|fw_version
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Firmware version */
DECL|member|age_of_flash
id|u16
id|age_of_flash
suffix:semicolon
multiline_comment|/* Number of times FW has been flashed */
DECL|member|chip_set_value
id|u8
id|chip_set_value
suffix:semicolon
multiline_comment|/* Contents of 0xC0000832 */
DECL|member|dram_size
id|u8
id|dram_size
suffix:semicolon
multiline_comment|/* In MB */
DECL|member|cache_flush_interval
id|u8
id|cache_flush_interval
suffix:semicolon
multiline_comment|/* in seconds */
DECL|member|bios_version
id|u8
id|bios_version
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|board_type
id|u8
id|board_type
suffix:semicolon
DECL|member|sense_alert
id|u8
id|sense_alert
suffix:semicolon
DECL|member|write_config_count
id|u8
id|write_config_count
suffix:semicolon
multiline_comment|/* Increase with every configuration&n;&t;&t;&t;&t;&t;   change */
DECL|member|drive_inserted_count
id|u8
id|drive_inserted_count
suffix:semicolon
multiline_comment|/* Increase with every drive inserted&n;&t;&t;&t;&t;&t; */
DECL|member|inserted_drive
id|u8
id|inserted_drive
suffix:semicolon
multiline_comment|/* Channel:Id of inserted drive */
DECL|member|battery_status
id|u8
id|battery_status
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * BIT 0: battery module missing&n;&t;&t;&t;&t; * BIT 1: VBAD&n;&t;&t;&t;&t; * BIT 2: temprature high&n;&t;&t;&t;&t; * BIT 3: battery pack missing&n;&t;&t;&t;&t; * BIT 4,5:&n;&t;&t;&t;&t; *   00 - charge complete&n;&t;&t;&t;&t; *   01 - fast charge in progress&n;&t;&t;&t;&t; *   10 - fast charge fail&n;&t;&t;&t;&t; *   11 - undefined&n;&t;&t;&t;&t; * Bit 6: counter &gt; 1000&n;&t;&t;&t;&t; * Bit 7: Undefined&n;&t;&t;&t;&t; */
DECL|member|dec_fault_bus_info
id|u8
id|dec_fault_bus_info
suffix:semicolon
DECL|typedef|mega_adp_info
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|mega_adp_info
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|num_ldrv
id|u8
id|num_ldrv
suffix:semicolon
multiline_comment|/* Number of logical drives configured */
DECL|member|rsvd
id|u8
id|rsvd
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ldrv_size
id|u32
id|ldrv_size
(braket
id|MAX_LOGICAL_DRIVES_8LD
)braket
suffix:semicolon
DECL|member|ldrv_prop
id|u8
id|ldrv_prop
(braket
id|MAX_LOGICAL_DRIVES_8LD
)braket
suffix:semicolon
DECL|member|ldrv_state
id|u8
id|ldrv_state
(braket
id|MAX_LOGICAL_DRIVES_8LD
)braket
suffix:semicolon
DECL|typedef|mega_ldrv_info
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|mega_ldrv_info
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|pdrv_state
id|u8
id|pdrv_state
(braket
id|MAX_PHYSICAL_DRIVES
)braket
suffix:semicolon
DECL|member|rsvd
id|u8
id|rsvd
suffix:semicolon
DECL|typedef|mega_pdrv_info
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|mega_pdrv_info
suffix:semicolon
multiline_comment|/* RAID inquiry: Mailbox command 0x05*/
r_typedef
r_struct
(brace
DECL|member|adapter_info
id|mega_adp_info
id|adapter_info
suffix:semicolon
DECL|member|logdrv_info
id|mega_ldrv_info
id|logdrv_info
suffix:semicolon
DECL|member|pdrv_info
id|mega_pdrv_info
id|pdrv_info
suffix:semicolon
DECL|typedef|mraid_inquiry
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|mraid_inquiry
suffix:semicolon
multiline_comment|/* RAID extended inquiry: Mailbox command 0x04*/
r_typedef
r_struct
(brace
DECL|member|raid_inq
id|mraid_inquiry
id|raid_inq
suffix:semicolon
DECL|member|phys_drv_format
id|u16
id|phys_drv_format
(braket
id|MAX_CHANNELS
)braket
suffix:semicolon
DECL|member|stack_attn
id|u8
id|stack_attn
suffix:semicolon
DECL|member|modem_status
id|u8
id|modem_status
suffix:semicolon
DECL|member|rsvd
id|u8
id|rsvd
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|mraid_ext_inquiry
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|mraid_ext_inquiry
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|channel
id|u8
id|channel
suffix:semicolon
DECL|member|target
id|u8
id|target
suffix:semicolon
DECL|typedef|adp_device
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|adp_device
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|start_blk
id|u32
id|start_blk
suffix:semicolon
multiline_comment|/* starting block */
DECL|member|num_blks
id|u32
id|num_blks
suffix:semicolon
multiline_comment|/* # of blocks */
DECL|member|device
id|adp_device
id|device
(braket
id|MAX_ROW_SIZE_40LD
)braket
suffix:semicolon
DECL|typedef|adp_span_40ld
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|adp_span_40ld
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|start_blk
id|u32
id|start_blk
suffix:semicolon
multiline_comment|/* starting block */
DECL|member|num_blks
id|u32
id|num_blks
suffix:semicolon
multiline_comment|/* # of blocks */
DECL|member|device
id|adp_device
id|device
(braket
id|MAX_ROW_SIZE_8LD
)braket
suffix:semicolon
DECL|typedef|adp_span_8ld
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|adp_span_8ld
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|span_depth
id|u8
id|span_depth
suffix:semicolon
multiline_comment|/* Total # of spans */
DECL|member|level
id|u8
id|level
suffix:semicolon
multiline_comment|/* RAID level */
DECL|member|read_ahead
id|u8
id|read_ahead
suffix:semicolon
multiline_comment|/* read ahead, no read ahead, adaptive read&n;&t;&t;&t;&t;   ahead */
DECL|member|stripe_sz
id|u8
id|stripe_sz
suffix:semicolon
multiline_comment|/* Encoded stripe size */
DECL|member|status
id|u8
id|status
suffix:semicolon
multiline_comment|/* Status of the logical drive */
DECL|member|write_mode
id|u8
id|write_mode
suffix:semicolon
multiline_comment|/* write mode, write_through/write_back */
DECL|member|direct_io
id|u8
id|direct_io
suffix:semicolon
multiline_comment|/* direct io or through cache */
DECL|member|row_size
id|u8
id|row_size
suffix:semicolon
multiline_comment|/* Number of stripes in a row */
DECL|typedef|logdrv_param
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|logdrv_param
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|lparam
id|logdrv_param
id|lparam
suffix:semicolon
DECL|member|span
id|adp_span_40ld
id|span
(braket
id|MAX_SPAN_DEPTH
)braket
suffix:semicolon
DECL|typedef|logdrv_40ld
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|logdrv_40ld
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|lparam
id|logdrv_param
id|lparam
suffix:semicolon
DECL|member|span
id|adp_span_8ld
id|span
(braket
id|MAX_SPAN_DEPTH
)braket
suffix:semicolon
DECL|typedef|logdrv_8ld
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|logdrv_8ld
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
multiline_comment|/* Type of the device */
DECL|member|cur_status
id|u8
id|cur_status
suffix:semicolon
multiline_comment|/* current status of the device */
DECL|member|tag_depth
id|u8
id|tag_depth
suffix:semicolon
multiline_comment|/* Level of tagging */
DECL|member|sync_neg
id|u8
id|sync_neg
suffix:semicolon
multiline_comment|/* sync negotiation - ENABLE or DISBALE */
DECL|member|size
id|u32
id|size
suffix:semicolon
multiline_comment|/* configurable size in terms of 512 byte&n;&t;&t;&t;&t;   blocks */
DECL|typedef|phys_drv
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|phys_drv
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|nlog_drives
id|u8
id|nlog_drives
suffix:semicolon
multiline_comment|/* number of logical drives */
DECL|member|resvd
id|u8
id|resvd
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ldrv
id|logdrv_40ld
id|ldrv
(braket
id|MAX_LOGICAL_DRIVES_40LD
)braket
suffix:semicolon
DECL|member|pdrv
id|phys_drv
id|pdrv
(braket
id|MAX_PHYSICAL_DRIVES
)braket
suffix:semicolon
DECL|typedef|disk_array_40ld
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|disk_array_40ld
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|nlog_drives
id|u8
id|nlog_drives
suffix:semicolon
multiline_comment|/* number of logical drives */
DECL|member|resvd
id|u8
id|resvd
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ldrv
id|logdrv_8ld
id|ldrv
(braket
id|MAX_LOGICAL_DRIVES_8LD
)braket
suffix:semicolon
DECL|member|pdrv
id|phys_drv
id|pdrv
(braket
id|MAX_PHYSICAL_DRIVES
)braket
suffix:semicolon
DECL|typedef|disk_array_8ld
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|disk_array_8ld
suffix:semicolon
multiline_comment|/*&n; * User ioctl structure.&n; * This structure will be used for Traditional Method ioctl interface&n; * commands (0x80),Alternate Buffer Method (0x81) ioctl commands and the&n; * Driver ioctls.&n; * The Driver ioctl interface handles the commands at the driver level,&n; * without being sent to the card.&n; */
multiline_comment|/* system call imposed limit. Change accordingly */
DECL|macro|IOCTL_MAX_DATALEN
mdefine_line|#define IOCTL_MAX_DATALEN       4096
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
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|fcs
suffix:semicolon
DECL|member|ui
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
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
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
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
multiline_comment|/*&n; * mailbox structure used for internal commands&n; */
r_typedef
r_struct
(brace
DECL|member|cmd
id|u8
id|cmd
suffix:semicolon
DECL|member|cmdid
id|u8
id|cmdid
suffix:semicolon
DECL|member|opcode
id|u8
id|opcode
suffix:semicolon
DECL|member|subopcode
id|u8
id|subopcode
suffix:semicolon
DECL|member|lba
id|u32
id|lba
suffix:semicolon
DECL|member|xferaddr
id|u32
id|xferaddr
suffix:semicolon
DECL|member|logdrv
id|u8
id|logdrv
suffix:semicolon
DECL|member|rsvd
id|u8
id|rsvd
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|numstatus
id|u8
id|numstatus
suffix:semicolon
DECL|member|status
id|u8
id|status
suffix:semicolon
DECL|typedef|megacmd_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|megacmd_t
suffix:semicolon
multiline_comment|/*&n; * Defines for Driver IOCTL interface&n; */
DECL|macro|MEGAIOC_MAGIC
mdefine_line|#define MEGAIOC_MAGIC  &t;&squot;m&squot;
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
multiline_comment|/*&n; * Definition for the new ioctl interface (NIT)&n; */
multiline_comment|/*&n; * Vendor specific Group-7 commands&n; */
DECL|macro|VENDOR_SPECIFIC_COMMANDS
mdefine_line|#define VENDOR_SPECIFIC_COMMANDS&t;0xE0
DECL|macro|MEGA_INTERNAL_CMD
mdefine_line|#define MEGA_INTERNAL_CMD&t;&t;VENDOR_SPECIFIC_COMMANDS + 0x01
multiline_comment|/*&n; * The ioctl command. No other command shall be used for this interface&n; */
DECL|macro|USCSICMD
mdefine_line|#define USCSICMD&t;VENDOR_SPECIFIC_COMMANDS
multiline_comment|/*&n; * Data direction flags&n; */
DECL|macro|UIOC_RD
mdefine_line|#define UIOC_RD&t;&t;0x00001
DECL|macro|UIOC_WR
mdefine_line|#define UIOC_WR&t;&t;0x00002
multiline_comment|/*&n; * ioctl opcodes&n; */
DECL|macro|MBOX_CMD
mdefine_line|#define MBOX_CMD&t;0x00000&t;/* DCMD or passthru command */
DECL|macro|GET_DRIVER_VER
mdefine_line|#define GET_DRIVER_VER&t;0x10000&t;/* Get driver version */
DECL|macro|GET_N_ADAP
mdefine_line|#define GET_N_ADAP&t;0x20000&t;/* Get number of adapters */
DECL|macro|GET_ADAP_INFO
mdefine_line|#define GET_ADAP_INFO&t;0x30000&t;/* Get information about a adapter */
DECL|macro|GET_CAP
mdefine_line|#define GET_CAP&t;&t;0x40000&t;/* Get ioctl capabilities */
DECL|macro|GET_STATS
mdefine_line|#define GET_STATS&t;0x50000&t;/* Get statistics, including error info */
multiline_comment|/*&n; * The ioctl structure.&n; * MBOX macro converts a nitioctl_t structure to megacmd_t pointer and&n; * MBOX_P macro converts a nitioctl_t pointer to megacmd_t pointer.&n; */
r_typedef
r_struct
(brace
DECL|member|signature
r_char
id|signature
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Must contain &quot;MEGANIT&quot; */
DECL|member|opcode
id|u32
id|opcode
suffix:semicolon
multiline_comment|/* opcode for the command */
DECL|member|adapno
id|u32
id|adapno
suffix:semicolon
multiline_comment|/* adapter number */
r_union
(brace
DECL|member|__raw_mbox
id|u8
id|__raw_mbox
(braket
l_int|18
)braket
suffix:semicolon
DECL|member|__uaddr
id|caddr_t
id|__uaddr
suffix:semicolon
multiline_comment|/* xferaddr for non-mbox cmds */
DECL|member|__ua
)brace
id|__ua
suffix:semicolon
DECL|macro|uioc_rmbox
mdefine_line|#define uioc_rmbox&t;__ua.__raw_mbox
DECL|macro|MBOX
mdefine_line|#define MBOX(uioc)&t;((megacmd_t *)&amp;((uioc).__ua.__raw_mbox[0]))
DECL|macro|MBOX_P
mdefine_line|#define MBOX_P(uioc)&t;((megacmd_t *)&amp;((uioc)-&gt;__ua.__raw_mbox[0]))
DECL|macro|uioc_uaddr
mdefine_line|#define uioc_uaddr&t;__ua.__uaddr
DECL|member|xferlen
id|u32
id|xferlen
suffix:semicolon
multiline_comment|/* xferlen for DCMD and non-mbox&n;&t;&t;&t;&t;&t;   commands */
DECL|member|flags
id|u32
id|flags
suffix:semicolon
multiline_comment|/* data direction flags */
DECL|typedef|nitioctl_t
)brace
id|nitioctl_t
suffix:semicolon
multiline_comment|/*&n; * I/O statistics for some applications like SNMP agent. The caller must&n; * provide the number of logical drives for which status should be reported.&n; */
r_typedef
r_struct
(brace
DECL|member|num_ldrv
r_int
id|num_ldrv
suffix:semicolon
multiline_comment|/* Number for logical drives for which the&n;&t;&t;&t;&t;   status should be reported. */
DECL|member|nreads
id|u32
id|nreads
(braket
id|MAX_LOGICAL_DRIVES_40LD
)braket
suffix:semicolon
multiline_comment|/* number of reads for&n;&t;&t;&t;&t;&t;&t;&t;each logical drive */
DECL|member|nreadblocks
id|u32
id|nreadblocks
(braket
id|MAX_LOGICAL_DRIVES_40LD
)braket
suffix:semicolon
multiline_comment|/* number of blocks&n;&t;&t;&t;&t;&t;&t;&t;read for each logical&n;&t;&t;&t;&t;&t;&t;&t;drive */
DECL|member|nwrites
id|u32
id|nwrites
(braket
id|MAX_LOGICAL_DRIVES_40LD
)braket
suffix:semicolon
multiline_comment|/* number of writes&n;&t;&t;&t;&t;&t;&t;&t;for each logical&n;&t;&t;&t;&t;&t;&t;&t;drive */
DECL|member|nwriteblocks
id|u32
id|nwriteblocks
(braket
id|MAX_LOGICAL_DRIVES_40LD
)braket
suffix:semicolon
multiline_comment|/* number of blocks&n;&t;&t;&t;&t;&t;&t;&t;writes for each&n;&t;&t;&t;&t;&t;&t;&t;logical drive */
DECL|member|rd_errors
id|u32
id|rd_errors
(braket
id|MAX_LOGICAL_DRIVES_40LD
)braket
suffix:semicolon
multiline_comment|/* number of read&n;&t;&t;&t;&t;&t;&t;&t;   errors for each&n;&t;&t;&t;&t;&t;&t;&t;   logical drive */
DECL|member|wr_errors
id|u32
id|wr_errors
(braket
id|MAX_LOGICAL_DRIVES_40LD
)braket
suffix:semicolon
multiline_comment|/* number of write&n;&t;&t;&t;&t;&t;&t;&t;   errors for each&n;&t;&t;&t;&t;&t;&t;&t;   logical drive */
DECL|typedef|megastat_t
)brace
id|megastat_t
suffix:semicolon
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
multiline_comment|/*&n;&t;&t;&t;&t; * bits 0-3 - BIOS geometry&n;&t;&t;&t;&t; * 0x0001 - 1GB&n;&t;&t;&t;&t; * 0x0010 - 2GB&n;&t;&t;&t;&t; * 0x1000 - 8GB&n;&t;&t;&t;&t; * Others values are invalid&n;&t;&t;&t;&t;&t;&t;&t; */
DECL|member|unused
id|u8
id|unused
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* bits 4-7 are unused */
DECL|member|boot_drv
id|u8
id|boot_drv
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * logical drive set as boot drive&n;&t;&t;&t;&t; * 0..7 - for 8LD cards&n;&t;&t;&t;&t; * 0..39 - for 40LD cards&n;&t;&t;&t;&t; */
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
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Mailbox and firmware commands and subopcodes used in this driver.&n; */
DECL|macro|MEGA_MBOXCMD_LREAD
mdefine_line|#define MEGA_MBOXCMD_LREAD&t;0x01
DECL|macro|MEGA_MBOXCMD_LWRITE
mdefine_line|#define MEGA_MBOXCMD_LWRITE&t;0x02
DECL|macro|MEGA_MBOXCMD_PASSTHRU
mdefine_line|#define MEGA_MBOXCMD_PASSTHRU&t;0x03
DECL|macro|MEGA_MBOXCMD_ADPEXTINQ
mdefine_line|#define MEGA_MBOXCMD_ADPEXTINQ&t;0x04
DECL|macro|MEGA_MBOXCMD_ADAPTERINQ
mdefine_line|#define MEGA_MBOXCMD_ADAPTERINQ&t;0x05
DECL|macro|MEGA_MBOXCMD_LREAD64
mdefine_line|#define MEGA_MBOXCMD_LREAD64&t;0xA7
DECL|macro|MEGA_MBOXCMD_LWRITE64
mdefine_line|#define MEGA_MBOXCMD_LWRITE64&t;0xA8
DECL|macro|MEGA_MBOXCMD_PASSTHRU64
mdefine_line|#define MEGA_MBOXCMD_PASSTHRU64&t;0xC3
DECL|macro|MEGA_MBOXCMD_EXTPTHRU
mdefine_line|#define MEGA_MBOXCMD_EXTPTHRU&t;0xE3
DECL|macro|MAIN_MISC_OPCODE
mdefine_line|#define MAIN_MISC_OPCODE&t;0xA4&t;/* f/w misc opcode */
DECL|macro|GET_MAX_SG_SUPPORT
mdefine_line|#define GET_MAX_SG_SUPPORT&t;0x01&t;/* get max sg len supported by f/w */
DECL|macro|FC_NEW_CONFIG
mdefine_line|#define FC_NEW_CONFIG&t;&t;0xA1
DECL|macro|NC_SUBOP_PRODUCT_INFO
mdefine_line|#define NC_SUBOP_PRODUCT_INFO&t;0x0E
DECL|macro|NC_SUBOP_ENQUIRY3
mdefine_line|#define NC_SUBOP_ENQUIRY3&t;0x0F
DECL|macro|ENQ3_GET_SOLICITED_FULL
mdefine_line|#define ENQ3_GET_SOLICITED_FULL&t;0x02
DECL|macro|OP_DCMD_READ_CONFIG
mdefine_line|#define OP_DCMD_READ_CONFIG&t;0x04
DECL|macro|NEW_READ_CONFIG_8LD
mdefine_line|#define NEW_READ_CONFIG_8LD&t;0x67
DECL|macro|READ_CONFIG_8LD
mdefine_line|#define READ_CONFIG_8LD&t;&t;0x07
DECL|macro|FLUSH_ADAPTER
mdefine_line|#define FLUSH_ADAPTER&t;&t;0x0A
DECL|macro|FLUSH_SYSTEM
mdefine_line|#define FLUSH_SYSTEM&t;&t;0xFE
multiline_comment|/*&n; * Command for random deletion of logical drives&n; */
DECL|macro|FC_DEL_LOGDRV
mdefine_line|#define&t;FC_DEL_LOGDRV&t;&t;0xA4&t;/* f/w command */
DECL|macro|OP_SUP_DEL_LOGDRV
mdefine_line|#define&t;OP_SUP_DEL_LOGDRV&t;0x2A&t;/* is feature supported */
DECL|macro|OP_GET_LDID_MAP
mdefine_line|#define OP_GET_LDID_MAP&t;&t;0x18&t;/* get ldid and logdrv number map */
DECL|macro|OP_DEL_LOGDRV
mdefine_line|#define OP_DEL_LOGDRV&t;&t;0x1C&t;/* delete logical drive */
multiline_comment|/*&n; * BIOS commands&n; */
DECL|macro|IS_BIOS_ENABLED
mdefine_line|#define IS_BIOS_ENABLED&t;&t;0x62
DECL|macro|GET_BIOS
mdefine_line|#define GET_BIOS&t;&t;0x01
DECL|macro|CHNL_CLASS
mdefine_line|#define CHNL_CLASS&t;&t;0xA9
DECL|macro|GET_CHNL_CLASS
mdefine_line|#define GET_CHNL_CLASS&t;&t;0x00
DECL|macro|SET_CHNL_CLASS
mdefine_line|#define SET_CHNL_CLASS&t;&t;0x01
DECL|macro|CH_RAID
mdefine_line|#define CH_RAID&t;&t;&t;0x01
DECL|macro|CH_SCSI
mdefine_line|#define CH_SCSI&t;&t;&t;0x00
DECL|macro|BIOS_PVT_DATA
mdefine_line|#define BIOS_PVT_DATA&t;&t;0x40
DECL|macro|GET_BIOS_PVT_DATA
mdefine_line|#define GET_BIOS_PVT_DATA&t;0x00
multiline_comment|/*&n; * Commands to support clustering&n; */
DECL|macro|MEGA_GET_TARGET_ID
mdefine_line|#define MEGA_GET_TARGET_ID&t;0x7D
DECL|macro|MEGA_CLUSTER_OP
mdefine_line|#define MEGA_CLUSTER_OP&t;&t;0x70
DECL|macro|MEGA_GET_CLUSTER_MODE
mdefine_line|#define MEGA_GET_CLUSTER_MODE&t;0x02
DECL|macro|MEGA_CLUSTER_CMD
mdefine_line|#define MEGA_CLUSTER_CMD&t;0x6E
DECL|macro|MEGA_RESERVE_LD
mdefine_line|#define MEGA_RESERVE_LD&t;&t;0x01
DECL|macro|MEGA_RELEASE_LD
mdefine_line|#define MEGA_RELEASE_LD&t;&t;0x02
DECL|macro|MEGA_RESET_RESERVATIONS
mdefine_line|#define MEGA_RESET_RESERVATIONS&t;0x03
DECL|macro|MEGA_RESERVATION_STATUS
mdefine_line|#define MEGA_RESERVATION_STATUS&t;0x04
DECL|macro|MEGA_RESERVE_PD
mdefine_line|#define MEGA_RESERVE_PD&t;&t;0x05
DECL|macro|MEGA_RELEASE_PD
mdefine_line|#define MEGA_RELEASE_PD&t;&t;0x06
multiline_comment|/*&n; * Module battery status&n; */
DECL|macro|MEGA_BATT_MODULE_MISSING
mdefine_line|#define MEGA_BATT_MODULE_MISSING&t;0x01
DECL|macro|MEGA_BATT_LOW_VOLTAGE
mdefine_line|#define MEGA_BATT_LOW_VOLTAGE&t;&t;0x02
DECL|macro|MEGA_BATT_TEMP_HIGH
mdefine_line|#define MEGA_BATT_TEMP_HIGH&t;&t;0x04
DECL|macro|MEGA_BATT_PACK_MISSING
mdefine_line|#define MEGA_BATT_PACK_MISSING&t;&t;0x08
DECL|macro|MEGA_BATT_CHARGE_MASK
mdefine_line|#define MEGA_BATT_CHARGE_MASK&t;&t;0x30
DECL|macro|MEGA_BATT_CHARGE_DONE
mdefine_line|#define MEGA_BATT_CHARGE_DONE&t;&t;0x00
DECL|macro|MEGA_BATT_CHARGE_INPROG
mdefine_line|#define MEGA_BATT_CHARGE_INPROG&t;&t;0x10
DECL|macro|MEGA_BATT_CHARGE_FAIL
mdefine_line|#define MEGA_BATT_CHARGE_FAIL&t;&t;0x20
DECL|macro|MEGA_BATT_CYCLES_EXCEEDED
mdefine_line|#define MEGA_BATT_CYCLES_EXCEEDED&t;0x40
multiline_comment|/*&n; * Physical drive states.&n; */
DECL|macro|PDRV_UNCNF
mdefine_line|#define PDRV_UNCNF&t;0
DECL|macro|PDRV_ONLINE
mdefine_line|#define PDRV_ONLINE&t;3
DECL|macro|PDRV_FAILED
mdefine_line|#define PDRV_FAILED&t;4
DECL|macro|PDRV_RBLD
mdefine_line|#define PDRV_RBLD&t;5
DECL|macro|PDRV_HOTSPARE
mdefine_line|#define PDRV_HOTSPARE&t;6
multiline_comment|/*&n; * Raid logical drive states.&n; */
DECL|macro|RDRV_OFFLINE
mdefine_line|#define RDRV_OFFLINE&t;0
DECL|macro|RDRV_DEGRADED
mdefine_line|#define RDRV_DEGRADED&t;1
DECL|macro|RDRV_OPTIMAL
mdefine_line|#define RDRV_OPTIMAL&t;2
DECL|macro|RDRV_DELETED
mdefine_line|#define RDRV_DELETED&t;3
multiline_comment|/*&n; * Read, write and cache policies&n; */
DECL|macro|NO_READ_AHEAD
mdefine_line|#define NO_READ_AHEAD&t;&t;0
DECL|macro|READ_AHEAD
mdefine_line|#define READ_AHEAD&t;&t;1
DECL|macro|ADAP_READ_AHEAD
mdefine_line|#define ADAP_READ_AHEAD&t;&t;2
DECL|macro|WRMODE_WRITE_THRU
mdefine_line|#define WRMODE_WRITE_THRU&t;0
DECL|macro|WRMODE_WRITE_BACK
mdefine_line|#define WRMODE_WRITE_BACK&t;1
DECL|macro|CACHED_IO
mdefine_line|#define CACHED_IO&t;&t;0
DECL|macro|DIRECT_IO
mdefine_line|#define DIRECT_IO&t;&t;1
DECL|macro|SCSI_LIST
mdefine_line|#define SCSI_LIST(scp) ((struct list_head *)(&amp;(scp)-&gt;SCp))
multiline_comment|/*&n; * Each controller&squot;s soft state&n; */
r_typedef
r_struct
(brace
DECL|member|this_id
r_int
id|this_id
suffix:semicolon
multiline_comment|/* our id, may set to different than 7 if&n;&t;&t;&t;&t;   clustering is available */
DECL|member|flag
id|u32
id|flag
suffix:semicolon
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
multiline_comment|/* mbox64 with mbox not aligned on 16-byte boundry */
DECL|member|una_mbox64
id|mbox64_t
op_star
id|una_mbox64
suffix:semicolon
DECL|member|una_mbox64_dma
id|dma_addr_t
id|una_mbox64_dma
suffix:semicolon
DECL|member|mbox64
r_volatile
id|mbox64_t
op_star
id|mbox64
suffix:semicolon
multiline_comment|/* ptr to 64-bit mailbox */
DECL|member|mbox
r_volatile
id|mbox_t
op_star
id|mbox
suffix:semicolon
multiline_comment|/* ptr to standard mailbox */
DECL|member|mbox_dma
id|dma_addr_t
id|mbox_dma
suffix:semicolon
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
DECL|member|free_list
r_struct
id|list_head
id|free_list
suffix:semicolon
DECL|member|pending_list
r_struct
id|list_head
id|pending_list
suffix:semicolon
DECL|member|completed_list
r_struct
id|list_head
id|completed_list
suffix:semicolon
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
DECL|macro|MEGA_BUFFER_SIZE
mdefine_line|#define MEGA_BUFFER_SIZE (2*1024)
DECL|member|mega_buffer
id|u8
op_star
id|mega_buffer
suffix:semicolon
DECL|member|buf_dma_handle
id|dma_addr_t
id|buf_dma_handle
suffix:semicolon
DECL|member|product_info
id|mega_product_info
id|product_info
suffix:semicolon
DECL|member|max_cmds
id|u8
id|max_cmds
suffix:semicolon
DECL|member|scb_list
id|scb_t
op_star
id|scb_list
suffix:semicolon
DECL|member|pend_cmds
id|atomic_t
id|pend_cmds
suffix:semicolon
multiline_comment|/* maintain a counter for pending&n;&t;&t;&t;&t;&t;   commands in firmware */
macro_line|#if MEGA_HAVE_STATS
DECL|member|nreads
id|u32
id|nreads
(braket
id|MAX_LOGICAL_DRIVES_40LD
)braket
suffix:semicolon
DECL|member|nreadblocks
id|u32
id|nreadblocks
(braket
id|MAX_LOGICAL_DRIVES_40LD
)braket
suffix:semicolon
DECL|member|nwrites
id|u32
id|nwrites
(braket
id|MAX_LOGICAL_DRIVES_40LD
)braket
suffix:semicolon
DECL|member|nwriteblocks
id|u32
id|nwriteblocks
(braket
id|MAX_LOGICAL_DRIVES_40LD
)braket
suffix:semicolon
DECL|member|rd_errors
id|u32
id|rd_errors
(braket
id|MAX_LOGICAL_DRIVES_40LD
)braket
suffix:semicolon
DECL|member|wr_errors
id|u32
id|wr_errors
(braket
id|MAX_LOGICAL_DRIVES_40LD
)braket
suffix:semicolon
macro_line|#endif
multiline_comment|/* Host adapter parameters */
DECL|member|numldrv
id|u8
id|numldrv
suffix:semicolon
DECL|member|fw_version
id|u8
id|fw_version
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|bios_version
id|u8
id|bios_version
(braket
l_int|7
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
DECL|member|controller_proc_dir_entry
r_struct
id|proc_dir_entry
op_star
id|controller_proc_dir_entry
suffix:semicolon
DECL|member|proc_read
r_struct
id|proc_dir_entry
op_star
id|proc_read
suffix:semicolon
DECL|member|proc_stat
r_struct
id|proc_dir_entry
op_star
id|proc_stat
suffix:semicolon
DECL|member|proc_mbox
r_struct
id|proc_dir_entry
op_star
id|proc_mbox
suffix:semicolon
macro_line|#if MEGA_HAVE_ENH_PROC
DECL|member|proc_rr
r_struct
id|proc_dir_entry
op_star
id|proc_rr
suffix:semicolon
DECL|member|proc_battery
r_struct
id|proc_dir_entry
op_star
id|proc_battery
suffix:semicolon
DECL|macro|MAX_PROC_CHANNELS
mdefine_line|#define MAX_PROC_CHANNELS&t;4
DECL|member|proc_pdrvstat
r_struct
id|proc_dir_entry
op_star
id|proc_pdrvstat
(braket
id|MAX_PROC_CHANNELS
)braket
suffix:semicolon
DECL|member|proc_rdrvstat
r_struct
id|proc_dir_entry
op_star
id|proc_rdrvstat
(braket
id|MAX_PROC_CHANNELS
)braket
suffix:semicolon
macro_line|#endif
macro_line|#endif
DECL|member|has_64bit_addr
r_int
id|has_64bit_addr
suffix:semicolon
multiline_comment|/* are we using 64-bit addressing */
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
DECL|member|boot_pdrv_enabled
r_int
id|boot_pdrv_enabled
suffix:semicolon
multiline_comment|/* boot from physical drive */
DECL|member|boot_pdrv_ch
r_int
id|boot_pdrv_ch
suffix:semicolon
multiline_comment|/* boot physical drive channel */
DECL|member|boot_pdrv_tgt
r_int
id|boot_pdrv_tgt
suffix:semicolon
multiline_comment|/* boot physical drive target */
DECL|member|support_random_del
r_int
id|support_random_del
suffix:semicolon
multiline_comment|/* Do we support random deletion of&n;&t;&t;&t;&t;&t;   logdrvs */
DECL|member|read_ldidmap
r_int
id|read_ldidmap
suffix:semicolon
multiline_comment|/* set after logical drive deltion. The&n;&t;&t;&t;&t;   logical drive number must be read from the&n;&t;&t;&t;&t;   map */
DECL|member|quiescent
id|atomic_t
id|quiescent
suffix:semicolon
multiline_comment|/* a stage reached when delete logical&n;&t;&t;&t;&t;&t;   drive needs to be done. Stop&n;&t;&t;&t;&t;&t;   sending requests to the hba till&n;&t;&t;&t;&t;&t;   delete operation is completed */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|logdrv_chan
id|u8
id|logdrv_chan
(braket
id|MAX_CHANNELS
op_plus
id|NVIRT_CHAN
)braket
suffix:semicolon
multiline_comment|/* logical drive are on&n;&t;&t;&t;&t;&t;&t;&t;what channels. */
DECL|member|mega_ch_class
r_int
id|mega_ch_class
suffix:semicolon
DECL|member|sglen
id|u8
id|sglen
suffix:semicolon
multiline_comment|/* f/w supported scatter-gather list length */
DECL|member|int_scb
id|scb_t
id|int_scb
suffix:semicolon
DECL|member|int_scmd
id|Scsi_Cmnd
id|int_scmd
suffix:semicolon
DECL|member|int_mtx
r_struct
id|semaphore
id|int_mtx
suffix:semicolon
multiline_comment|/* To synchronize the internal&n;&t;&t;&t;&t;&t;&t;commands */
DECL|member|int_waitq
id|wait_queue_head_t
id|int_waitq
suffix:semicolon
multiline_comment|/* wait queue for internal&n;&t;&t;&t;&t;&t;&t; cmds */
DECL|member|has_cluster
r_int
id|has_cluster
suffix:semicolon
multiline_comment|/* cluster support on this HBA */
DECL|typedef|adapter_t
)brace
id|adapter_t
suffix:semicolon
DECL|struct|mega_hbas
r_struct
id|mega_hbas
(brace
DECL|member|is_bios_enabled
r_int
id|is_bios_enabled
suffix:semicolon
DECL|member|hostdata_addr
id|adapter_t
op_star
id|hostdata_addr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * For state flag. Do not use LSB(8 bits) which are&n; * reserved for storing info about channels.&n; */
DECL|macro|IN_ABORT
mdefine_line|#define IN_ABORT&t;0x80000000L
DECL|macro|IN_RESET
mdefine_line|#define IN_RESET&t;0x40000000L
DECL|macro|BOARD_MEMMAP
mdefine_line|#define BOARD_MEMMAP&t;0x20000000L
DECL|macro|BOARD_IOMAP
mdefine_line|#define BOARD_IOMAP&t;0x10000000L
DECL|macro|BOARD_40LD
mdefine_line|#define BOARD_40LD   &t;0x08000000L
DECL|macro|BOARD_64BIT
mdefine_line|#define BOARD_64BIT&t;0x04000000L
DECL|macro|INTR_VALID
mdefine_line|#define INTR_VALID&t;&t;&t;0x40
DECL|macro|PCI_CONF_AMISIG
mdefine_line|#define PCI_CONF_AMISIG&t;&t;&t;0xa0
DECL|macro|PCI_CONF_AMISIG64
mdefine_line|#define PCI_CONF_AMISIG64&t;&t;0xa4
DECL|macro|MEGA_DMA_TYPE_NONE
mdefine_line|#define MEGA_DMA_TYPE_NONE&t;&t;0xFFFF
DECL|macro|MEGA_BULK_DATA
mdefine_line|#define MEGA_BULK_DATA&t;&t;&t;0x0001
DECL|macro|MEGA_SGLIST
mdefine_line|#define MEGA_SGLIST&t;&t;&t;0x0002
multiline_comment|/*&n; * lockscope definitions, callers can specify the lock scope with this data&n; * type. LOCK_INT would mean the caller has not acquired the lock before&n; * making the call and LOCK_EXT would mean otherwise.&n; */
DECL|enumerator|LOCK_INT
DECL|enumerator|LOCK_EXT
DECL|typedef|lockscope_t
r_typedef
r_enum
(brace
id|LOCK_INT
comma
id|LOCK_EXT
)brace
id|lockscope_t
suffix:semicolon
multiline_comment|/*&n; * Parameters for the io-mapped controllers&n; */
multiline_comment|/* I/O Port offsets */
DECL|macro|CMD_PORT
mdefine_line|#define CMD_PORT&t; &t;0x00
DECL|macro|ACK_PORT
mdefine_line|#define ACK_PORT&t; &t;0x00
DECL|macro|TOGGLE_PORT
mdefine_line|#define TOGGLE_PORT&t;&t;0x01
DECL|macro|INTR_PORT
mdefine_line|#define INTR_PORT&t;  &t;0x0a
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
DECL|macro|issue_command
mdefine_line|#define issue_command(adapter)&t;&bslash;&n;&t;&t;outb_p(ISSUE_BYTE, (adapter)-&gt;base + CMD_PORT)
DECL|macro|irq_state
mdefine_line|#define irq_state(adapter)&t;inb_p((adapter)-&gt;base + INTR_PORT)
DECL|macro|set_irq_state
mdefine_line|#define set_irq_state(adapter, value)&t;&bslash;&n;&t;&t;outb_p((value), (adapter)-&gt;base + INTR_PORT)
DECL|macro|irq_ack
mdefine_line|#define irq_ack(adapter)&t;&bslash;&n;&t;&t;outb_p(ACK_BYTE, (adapter)-&gt;base + ACK_PORT)
DECL|macro|irq_enable
mdefine_line|#define irq_enable(adapter)&t;&bslash;&n;&t;outb_p(ENABLE_INTR_BYTE, (adapter)-&gt;base + TOGGLE_PORT)
DECL|macro|irq_disable
mdefine_line|#define irq_disable(adapter)&t;&bslash;&n;&t;outb_p(DISABLE_INTR_BYTE, (adapter)-&gt;base + TOGGLE_PORT)
multiline_comment|/*&n; * This is our SYSDEP area. All kernel specific detail should be placed here -&n; * as much as possible&n; */
multiline_comment|/*&n; * End of SYSDEP area&n; */
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
r_static
r_int
id|megaraid_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_static
r_void
id|mega_find_card
c_func
(paren
id|Scsi_Host_Template
op_star
comma
id|u16
comma
id|u16
)paren
suffix:semicolon
r_static
r_int
id|mega_query_adapter
c_func
(paren
id|adapter_t
op_star
)paren
suffix:semicolon
r_static
r_inline
r_int
id|issue_scb
c_func
(paren
id|adapter_t
op_star
comma
id|scb_t
op_star
)paren
suffix:semicolon
r_static
r_int
id|mega_setup_mailbox
c_func
(paren
id|adapter_t
op_star
)paren
suffix:semicolon
r_static
r_int
id|megaraid_queue
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_static
id|scb_t
op_star
id|mega_build_cmd
c_func
(paren
id|adapter_t
op_star
comma
id|Scsi_Cmnd
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_static
r_inline
id|scb_t
op_star
id|mega_allocate_scb
c_func
(paren
id|adapter_t
op_star
comma
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_void
id|__mega_runpendq
c_func
(paren
id|adapter_t
op_star
)paren
suffix:semicolon
r_static
r_inline
r_void
id|mega_runpendq
c_func
(paren
id|adapter_t
op_star
)paren
suffix:semicolon
r_static
r_int
id|issue_scb_block
c_func
(paren
id|adapter_t
op_star
comma
id|u_char
op_star
)paren
suffix:semicolon
r_static
id|irqreturn_t
id|megaraid_isr_memmapped
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_static
id|irqreturn_t
id|megaraid_isr_iomapped
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_static
r_void
id|mega_free_scb
c_func
(paren
id|adapter_t
op_star
comma
id|scb_t
op_star
)paren
suffix:semicolon
r_static
r_int
id|megaraid_release
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_static
r_int
id|megaraid_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|megaraid_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|megaraid_abort_and_reset
c_func
(paren
id|adapter_t
op_star
comma
id|Scsi_Cmnd
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|megaraid_biosparam
c_func
(paren
r_struct
id|scsi_device
op_star
comma
r_struct
id|block_device
op_star
comma
id|sector_t
comma
r_int
(braket
)braket
)paren
suffix:semicolon
r_static
r_int
id|mega_print_inquiry
c_func
(paren
r_char
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_static
r_int
id|mega_build_sglist
(paren
id|adapter_t
op_star
id|adapter
comma
id|scb_t
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
r_inline
r_int
id|mega_busywait_mbox
(paren
id|adapter_t
op_star
)paren
suffix:semicolon
r_static
r_int
id|__mega_busywait_mbox
(paren
id|adapter_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|mega_rundoneq
(paren
id|adapter_t
op_star
)paren
suffix:semicolon
r_static
r_inline
r_void
id|mega_cmd_done
c_func
(paren
id|adapter_t
op_star
comma
id|u8
(braket
)braket
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_static
r_inline
r_void
id|mega_free_sgl
(paren
id|adapter_t
op_star
id|adapter
)paren
suffix:semicolon
r_static
r_void
id|mega_8_to_40ld
(paren
id|mraid_inquiry
op_star
id|inquiry
comma
id|mega_inquiry3
op_star
id|enquiry3
comma
id|mega_product_info
op_star
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
r_int
id|mega_m_to_n
c_func
(paren
r_void
op_star
comma
id|nitioctl_t
op_star
)paren
suffix:semicolon
r_static
r_int
id|mega_n_to_m
c_func
(paren
r_void
op_star
comma
id|megacmd_t
op_star
)paren
suffix:semicolon
r_static
r_int
id|mega_init_scb
(paren
id|adapter_t
op_star
)paren
suffix:semicolon
r_static
r_int
id|mega_is_bios_enabled
(paren
id|adapter_t
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
r_static
r_void
id|mega_create_proc_entry
c_func
(paren
r_int
comma
r_struct
id|proc_dir_entry
op_star
)paren
suffix:semicolon
r_static
r_int
id|proc_read_config
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_static
r_int
id|proc_read_stat
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_static
r_int
id|proc_read_mbox
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_static
r_int
id|proc_rebuild_rate
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_static
r_int
id|proc_battery
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_static
r_int
id|proc_pdrv_ch0
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_static
r_int
id|proc_pdrv_ch1
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_static
r_int
id|proc_pdrv_ch2
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_static
r_int
id|proc_pdrv_ch3
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_static
r_int
id|proc_pdrv
c_func
(paren
id|adapter_t
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|proc_rdrv_10
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_static
r_int
id|proc_rdrv_20
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_static
r_int
id|proc_rdrv_30
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_static
r_int
id|proc_rdrv_40
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_static
r_int
id|proc_rdrv
c_func
(paren
id|adapter_t
op_star
comma
r_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
r_static
r_int
id|mega_adapinq
c_func
(paren
id|adapter_t
op_star
comma
id|dma_addr_t
)paren
suffix:semicolon
r_static
r_int
id|mega_internal_dev_inquiry
c_func
(paren
id|adapter_t
op_star
comma
id|u8
comma
id|u8
comma
id|dma_addr_t
)paren
suffix:semicolon
r_static
r_inline
id|caddr_t
id|mega_allocate_inquiry
c_func
(paren
id|dma_addr_t
op_star
comma
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
r_static
r_inline
r_void
id|mega_free_inquiry
c_func
(paren
id|caddr_t
comma
id|dma_addr_t
comma
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
r_static
r_inline
r_int
id|make_local_pdev
c_func
(paren
id|adapter_t
op_star
comma
r_struct
id|pci_dev
op_star
op_star
)paren
suffix:semicolon
r_static
r_inline
r_void
id|free_local_pdev
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
r_static
r_int
id|mega_support_ext_cdb
c_func
(paren
id|adapter_t
op_star
)paren
suffix:semicolon
r_static
id|mega_passthru
op_star
id|mega_prepare_passthru
c_func
(paren
id|adapter_t
op_star
comma
id|scb_t
op_star
comma
id|Scsi_Cmnd
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_static
id|mega_ext_passthru
op_star
id|mega_prepare_extpassthru
c_func
(paren
id|adapter_t
op_star
comma
id|scb_t
op_star
comma
id|Scsi_Cmnd
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_static
r_void
id|mega_enum_raid_scsi
c_func
(paren
id|adapter_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|mega_get_boot_drv
c_func
(paren
id|adapter_t
op_star
)paren
suffix:semicolon
r_static
r_inline
r_int
id|mega_get_ldrv_num
c_func
(paren
id|adapter_t
op_star
comma
id|Scsi_Cmnd
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|mega_support_random_del
c_func
(paren
id|adapter_t
op_star
)paren
suffix:semicolon
r_static
r_int
id|mega_del_logdrv
c_func
(paren
id|adapter_t
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
id|adapter_t
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_void
id|mega_get_max_sgl
c_func
(paren
id|adapter_t
op_star
)paren
suffix:semicolon
r_static
r_int
id|mega_internal_command
c_func
(paren
id|adapter_t
op_star
comma
id|lockscope_t
comma
id|megacmd_t
op_star
comma
id|mega_passthru
op_star
)paren
suffix:semicolon
r_static
r_void
id|mega_internal_done
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|mega_support_cluster
c_func
(paren
id|adapter_t
op_star
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* vi: set ts=8 sw=8 tw=78: */
eof
