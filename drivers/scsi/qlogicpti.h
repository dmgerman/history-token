multiline_comment|/* qlogicpti.h: Performance Technologies QlogicISP sbus card defines.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caipfs.rutgers.edu)&n; */
macro_line|#ifndef _QLOGICPTI_H
DECL|macro|_QLOGICPTI_H
mdefine_line|#define _QLOGICPTI_H
multiline_comment|/* Qlogic/SBUS controller registers. */
DECL|macro|SBUS_CFG1
mdefine_line|#define SBUS_CFG1&t;0x006UL
DECL|macro|SBUS_CTRL
mdefine_line|#define SBUS_CTRL&t;0x008UL
DECL|macro|SBUS_STAT
mdefine_line|#define SBUS_STAT&t;0x00aUL
DECL|macro|SBUS_SEMAPHORE
mdefine_line|#define SBUS_SEMAPHORE&t;0x00cUL
DECL|macro|CMD_DMA_CTRL
mdefine_line|#define CMD_DMA_CTRL&t;0x022UL
DECL|macro|DATA_DMA_CTRL
mdefine_line|#define DATA_DMA_CTRL&t;0x042UL
DECL|macro|MBOX0
mdefine_line|#define MBOX0&t;&t;0x080UL
DECL|macro|MBOX1
mdefine_line|#define MBOX1&t;&t;0x082UL
DECL|macro|MBOX2
mdefine_line|#define MBOX2&t;&t;0x084UL
DECL|macro|MBOX3
mdefine_line|#define MBOX3&t;&t;0x086UL
DECL|macro|MBOX4
mdefine_line|#define MBOX4&t;&t;0x088UL
DECL|macro|MBOX5
mdefine_line|#define MBOX5&t;&t;0x08aUL
DECL|macro|CPU_CMD
mdefine_line|#define CPU_CMD&t;&t;0x214UL
DECL|macro|CPU_ORIDE
mdefine_line|#define CPU_ORIDE&t;0x224UL
DECL|macro|CPU_PCTRL
mdefine_line|#define CPU_PCTRL&t;0x272UL
DECL|macro|CPU_PDIFF
mdefine_line|#define CPU_PDIFF&t;0x276UL
DECL|macro|RISC_PSR
mdefine_line|#define RISC_PSR&t;0x420UL
DECL|macro|RISC_MTREG
mdefine_line|#define RISC_MTREG&t;0x42EUL
DECL|macro|HCCTRL
mdefine_line|#define HCCTRL&t;&t;0x440UL
multiline_comment|/* SCSI parameters for this driver. */
DECL|macro|MAX_TARGETS
mdefine_line|#define MAX_TARGETS&t;16
DECL|macro|MAX_LUNS
mdefine_line|#define MAX_LUNS&t;8
multiline_comment|/* With the qlogic interface, every queue slot can hold a SCSI&n; * command with up to 4 scatter/gather entries.  If we need more&n; * than 4 entries, continuation entries can be used that hold&n; * another 7 entries each.  Unlike for other drivers, this means&n; * that the maximum number of scatter/gather entries we can&n; * support at any given time is a function of the number of queue&n; * slots available.  That is, host-&gt;can_queue and host-&gt;sg_tablesize&n; * are dynamic and _not_ independent.  This all works fine because&n; * requests are queued serially and the scatter/gather limit is&n; * determined for each queue request anew.&n; */
DECL|macro|QLOGICPTI_REQ_QUEUE_LEN
mdefine_line|#define QLOGICPTI_REQ_QUEUE_LEN&t;255&t;/* must be power of two - 1 */
DECL|macro|QLOGICPTI_MAX_SG
mdefine_line|#define QLOGICPTI_MAX_SG(ql)&t;(4 + ((ql) &gt; 0) ? 7*((ql) - 1) : 0)
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL (0)
macro_line|#endif
r_int
id|qlogicpti_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|qlogicpti_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|qlogicpti_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|qlogicpti_queuecommand
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
id|qlogicpti_queuecommand_slow
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
id|qlogicpti_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|qlogicpti_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* mailbox command complete status codes */
DECL|macro|MBOX_COMMAND_COMPLETE
mdefine_line|#define MBOX_COMMAND_COMPLETE&t;&t;0x4000
DECL|macro|INVALID_COMMAND
mdefine_line|#define INVALID_COMMAND&t;&t;&t;0x4001
DECL|macro|HOST_INTERFACE_ERROR
mdefine_line|#define HOST_INTERFACE_ERROR&t;&t;0x4002
DECL|macro|TEST_FAILED
mdefine_line|#define TEST_FAILED&t;&t;&t;0x4003
DECL|macro|COMMAND_ERROR
mdefine_line|#define COMMAND_ERROR&t;&t;&t;0x4005
DECL|macro|COMMAND_PARAM_ERROR
mdefine_line|#define COMMAND_PARAM_ERROR&t;&t;0x4006
multiline_comment|/* async event status codes */
DECL|macro|ASYNC_SCSI_BUS_RESET
mdefine_line|#define ASYNC_SCSI_BUS_RESET&t;&t;0x8001
DECL|macro|SYSTEM_ERROR
mdefine_line|#define SYSTEM_ERROR&t;&t;&t;0x8002
DECL|macro|REQUEST_TRANSFER_ERROR
mdefine_line|#define REQUEST_TRANSFER_ERROR&t;&t;0x8003
DECL|macro|RESPONSE_TRANSFER_ERROR
mdefine_line|#define RESPONSE_TRANSFER_ERROR&t;&t;0x8004
DECL|macro|REQUEST_QUEUE_WAKEUP
mdefine_line|#define REQUEST_QUEUE_WAKEUP&t;&t;0x8005
DECL|macro|EXECUTION_TIMEOUT_RESET
mdefine_line|#define EXECUTION_TIMEOUT_RESET&t;&t;0x8006
multiline_comment|/* Am I fucking pedantic or what? */
DECL|struct|Entry_header
r_struct
id|Entry_header
(brace
macro_line|#ifdef __BIG_ENDIAN
DECL|member|entry_cnt
id|u8
id|entry_cnt
suffix:semicolon
DECL|member|entry_type
id|u8
id|entry_type
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|sys_def_1
id|u8
id|sys_def_1
suffix:semicolon
macro_line|#else /* __LITTLE_ENDIAN */
id|u8
id|entry_type
suffix:semicolon
id|u8
id|entry_cnt
suffix:semicolon
id|u8
id|sys_def_1
suffix:semicolon
id|u8
id|flags
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* entry header type commands */
DECL|macro|ENTRY_COMMAND
mdefine_line|#define ENTRY_COMMAND&t;&t;1
DECL|macro|ENTRY_CONTINUATION
mdefine_line|#define ENTRY_CONTINUATION&t;2
DECL|macro|ENTRY_STATUS
mdefine_line|#define ENTRY_STATUS&t;&t;3
DECL|macro|ENTRY_MARKER
mdefine_line|#define ENTRY_MARKER&t;&t;4
DECL|macro|ENTRY_EXTENDED_COMMAND
mdefine_line|#define ENTRY_EXTENDED_COMMAND&t;5
multiline_comment|/* entry header flag definitions */
DECL|macro|EFLAG_CONTINUATION
mdefine_line|#define EFLAG_CONTINUATION&t;1
DECL|macro|EFLAG_BUSY
mdefine_line|#define EFLAG_BUSY&t;&t;2
DECL|macro|EFLAG_BAD_HEADER
mdefine_line|#define EFLAG_BAD_HEADER&t;4
DECL|macro|EFLAG_BAD_PAYLOAD
mdefine_line|#define EFLAG_BAD_PAYLOAD&t;8
DECL|struct|dataseg
r_struct
id|dataseg
(brace
DECL|member|d_base
id|u32
id|d_base
suffix:semicolon
DECL|member|d_count
id|u32
id|d_count
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|Command_Entry
r_struct
id|Command_Entry
(brace
DECL|member|hdr
r_struct
id|Entry_header
id|hdr
suffix:semicolon
DECL|member|handle
id|u32
id|handle
suffix:semicolon
macro_line|#ifdef __BIG_ENDIAN
DECL|member|target_id
id|u8
id|target_id
suffix:semicolon
DECL|member|target_lun
id|u8
id|target_lun
suffix:semicolon
macro_line|#else /* __LITTLE_ENDIAN */
DECL|member|target_lun
id|u8
id|target_lun
suffix:semicolon
DECL|member|target_id
id|u8
id|target_id
suffix:semicolon
macro_line|#endif
DECL|member|cdb_length
id|u16
id|cdb_length
suffix:semicolon
DECL|member|control_flags
id|u16
id|control_flags
suffix:semicolon
DECL|member|rsvd
id|u16
id|rsvd
suffix:semicolon
DECL|member|time_out
id|u16
id|time_out
suffix:semicolon
DECL|member|segment_cnt
id|u16
id|segment_cnt
suffix:semicolon
DECL|member|cdb
id|u8
id|cdb
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|dataseg
r_struct
id|dataseg
id|dataseg
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* command entry control flag definitions */
DECL|macro|CFLAG_NODISC
mdefine_line|#define CFLAG_NODISC&t;&t;0x01
DECL|macro|CFLAG_HEAD_TAG
mdefine_line|#define CFLAG_HEAD_TAG&t;&t;0x02
DECL|macro|CFLAG_ORDERED_TAG
mdefine_line|#define CFLAG_ORDERED_TAG&t;0x04
DECL|macro|CFLAG_SIMPLE_TAG
mdefine_line|#define CFLAG_SIMPLE_TAG&t;0x08
DECL|macro|CFLAG_TAR_RTN
mdefine_line|#define CFLAG_TAR_RTN&t;&t;0x10
DECL|macro|CFLAG_READ
mdefine_line|#define CFLAG_READ&t;&t;0x20
DECL|macro|CFLAG_WRITE
mdefine_line|#define CFLAG_WRITE&t;&t;0x40
DECL|struct|Ext_Command_Entry
r_struct
id|Ext_Command_Entry
(brace
DECL|member|hdr
r_struct
id|Entry_header
id|hdr
suffix:semicolon
DECL|member|handle
id|u32
id|handle
suffix:semicolon
macro_line|#ifdef __BIG_ENDIAN
DECL|member|target_id
id|u8
id|target_id
suffix:semicolon
DECL|member|target_lun
id|u8
id|target_lun
suffix:semicolon
macro_line|#else /* __LITTLE_ENDIAN */
DECL|member|target_lun
id|u8
id|target_lun
suffix:semicolon
DECL|member|target_id
id|u8
id|target_id
suffix:semicolon
macro_line|#endif
DECL|member|cdb_length
id|u16
id|cdb_length
suffix:semicolon
DECL|member|control_flags
id|u16
id|control_flags
suffix:semicolon
DECL|member|rsvd
id|u16
id|rsvd
suffix:semicolon
DECL|member|time_out
id|u16
id|time_out
suffix:semicolon
DECL|member|segment_cnt
id|u16
id|segment_cnt
suffix:semicolon
DECL|member|cdb
id|u8
id|cdb
(braket
l_int|44
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|Continuation_Entry
r_struct
id|Continuation_Entry
(brace
DECL|member|hdr
r_struct
id|Entry_header
id|hdr
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
DECL|member|dataseg
r_struct
id|dataseg
id|dataseg
(braket
l_int|7
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|Marker_Entry
r_struct
id|Marker_Entry
(brace
DECL|member|hdr
r_struct
id|Entry_header
id|hdr
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
macro_line|#ifdef __BIG_ENDIAN
DECL|member|target_id
id|u8
id|target_id
suffix:semicolon
DECL|member|target_lun
id|u8
id|target_lun
suffix:semicolon
macro_line|#else /* __LITTLE_ENDIAN */
DECL|member|target_lun
id|u8
id|target_lun
suffix:semicolon
DECL|member|target_id
id|u8
id|target_id
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __BIG_ENDIAN
DECL|member|rsvd
id|u8
id|rsvd
suffix:semicolon
DECL|member|modifier
id|u8
id|modifier
suffix:semicolon
macro_line|#else /* __LITTLE_ENDIAN */
DECL|member|modifier
id|u8
id|modifier
suffix:semicolon
DECL|member|rsvd
id|u8
id|rsvd
suffix:semicolon
macro_line|#endif
DECL|member|rsvds
id|u8
id|rsvds
(braket
l_int|52
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* marker entry modifier definitions */
DECL|macro|SYNC_DEVICE
mdefine_line|#define SYNC_DEVICE&t;0
DECL|macro|SYNC_TARGET
mdefine_line|#define SYNC_TARGET&t;1
DECL|macro|SYNC_ALL
mdefine_line|#define SYNC_ALL&t;2
DECL|struct|Status_Entry
r_struct
id|Status_Entry
(brace
DECL|member|hdr
r_struct
id|Entry_header
id|hdr
suffix:semicolon
DECL|member|handle
id|u32
id|handle
suffix:semicolon
DECL|member|scsi_status
id|u16
id|scsi_status
suffix:semicolon
DECL|member|completion_status
id|u16
id|completion_status
suffix:semicolon
DECL|member|state_flags
id|u16
id|state_flags
suffix:semicolon
DECL|member|status_flags
id|u16
id|status_flags
suffix:semicolon
DECL|member|time
id|u16
id|time
suffix:semicolon
DECL|member|req_sense_len
id|u16
id|req_sense_len
suffix:semicolon
DECL|member|residual
id|u32
id|residual
suffix:semicolon
DECL|member|rsvd
id|u8
id|rsvd
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|req_sense_data
id|u8
id|req_sense_data
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* status entry completion status definitions */
DECL|macro|CS_COMPLETE
mdefine_line|#define CS_COMPLETE&t;&t;&t;0x0000
DECL|macro|CS_INCOMPLETE
mdefine_line|#define CS_INCOMPLETE&t;&t;&t;0x0001
DECL|macro|CS_DMA_ERROR
mdefine_line|#define CS_DMA_ERROR&t;&t;&t;0x0002
DECL|macro|CS_TRANSPORT_ERROR
mdefine_line|#define CS_TRANSPORT_ERROR&t;&t;0x0003
DECL|macro|CS_RESET_OCCURRED
mdefine_line|#define CS_RESET_OCCURRED&t;&t;0x0004
DECL|macro|CS_ABORTED
mdefine_line|#define CS_ABORTED&t;&t;&t;0x0005
DECL|macro|CS_TIMEOUT
mdefine_line|#define CS_TIMEOUT&t;&t;&t;0x0006
DECL|macro|CS_DATA_OVERRUN
mdefine_line|#define CS_DATA_OVERRUN&t;&t;&t;0x0007
DECL|macro|CS_COMMAND_OVERRUN
mdefine_line|#define CS_COMMAND_OVERRUN&t;&t;0x0008
DECL|macro|CS_STATUS_OVERRUN
mdefine_line|#define CS_STATUS_OVERRUN&t;&t;0x0009
DECL|macro|CS_BAD_MESSAGE
mdefine_line|#define CS_BAD_MESSAGE&t;&t;&t;0x000a
DECL|macro|CS_NO_MESSAGE_OUT
mdefine_line|#define CS_NO_MESSAGE_OUT&t;&t;0x000b
DECL|macro|CS_EXT_ID_FAILED
mdefine_line|#define CS_EXT_ID_FAILED&t;&t;0x000c
DECL|macro|CS_IDE_MSG_FAILED
mdefine_line|#define CS_IDE_MSG_FAILED&t;&t;0x000d
DECL|macro|CS_ABORT_MSG_FAILED
mdefine_line|#define CS_ABORT_MSG_FAILED&t;&t;0x000e
DECL|macro|CS_REJECT_MSG_FAILED
mdefine_line|#define CS_REJECT_MSG_FAILED&t;&t;0x000f
DECL|macro|CS_NOP_MSG_FAILED
mdefine_line|#define CS_NOP_MSG_FAILED&t;&t;0x0010
DECL|macro|CS_PARITY_ERROR_MSG_FAILED
mdefine_line|#define CS_PARITY_ERROR_MSG_FAILED&t;0x0011
DECL|macro|CS_DEVICE_RESET_MSG_FAILED
mdefine_line|#define CS_DEVICE_RESET_MSG_FAILED&t;0x0012
DECL|macro|CS_ID_MSG_FAILED
mdefine_line|#define CS_ID_MSG_FAILED&t;&t;0x0013
DECL|macro|CS_UNEXP_BUS_FREE
mdefine_line|#define CS_UNEXP_BUS_FREE&t;&t;0x0014
DECL|macro|CS_DATA_UNDERRUN
mdefine_line|#define CS_DATA_UNDERRUN&t;&t;0x0015
DECL|macro|CS_BUS_RESET
mdefine_line|#define CS_BUS_RESET&t;&t;&t;0x001c
multiline_comment|/* status entry state flag definitions */
DECL|macro|SF_GOT_BUS
mdefine_line|#define SF_GOT_BUS&t;&t;&t;0x0100
DECL|macro|SF_GOT_TARGET
mdefine_line|#define SF_GOT_TARGET&t;&t;&t;0x0200
DECL|macro|SF_SENT_CDB
mdefine_line|#define SF_SENT_CDB&t;&t;&t;0x0400
DECL|macro|SF_TRANSFERRED_DATA
mdefine_line|#define SF_TRANSFERRED_DATA&t;&t;0x0800
DECL|macro|SF_GOT_STATUS
mdefine_line|#define SF_GOT_STATUS&t;&t;&t;0x1000
DECL|macro|SF_GOT_SENSE
mdefine_line|#define SF_GOT_SENSE&t;&t;&t;0x2000
multiline_comment|/* status entry status flag definitions */
DECL|macro|STF_DISCONNECT
mdefine_line|#define STF_DISCONNECT&t;&t;&t;0x0001
DECL|macro|STF_SYNCHRONOUS
mdefine_line|#define STF_SYNCHRONOUS&t;&t;&t;0x0002
DECL|macro|STF_PARITY_ERROR
mdefine_line|#define STF_PARITY_ERROR&t;&t;0x0004
DECL|macro|STF_BUS_RESET
mdefine_line|#define STF_BUS_RESET&t;&t;&t;0x0008
DECL|macro|STF_DEVICE_RESET
mdefine_line|#define STF_DEVICE_RESET&t;&t;0x0010
DECL|macro|STF_ABORTED
mdefine_line|#define STF_ABORTED&t;&t;&t;0x0020
DECL|macro|STF_TIMEOUT
mdefine_line|#define STF_TIMEOUT&t;&t;&t;0x0040
DECL|macro|STF_NEGOTIATION
mdefine_line|#define STF_NEGOTIATION&t;&t;&t;0x0080
multiline_comment|/* mailbox commands */
DECL|macro|MBOX_NO_OP
mdefine_line|#define MBOX_NO_OP&t;&t;&t;0x0000
DECL|macro|MBOX_LOAD_RAM
mdefine_line|#define MBOX_LOAD_RAM&t;&t;&t;0x0001
DECL|macro|MBOX_EXEC_FIRMWARE
mdefine_line|#define MBOX_EXEC_FIRMWARE&t;&t;0x0002
DECL|macro|MBOX_DUMP_RAM
mdefine_line|#define MBOX_DUMP_RAM&t;&t;&t;0x0003
DECL|macro|MBOX_WRITE_RAM_WORD
mdefine_line|#define MBOX_WRITE_RAM_WORD&t;&t;0x0004
DECL|macro|MBOX_READ_RAM_WORD
mdefine_line|#define MBOX_READ_RAM_WORD&t;&t;0x0005
DECL|macro|MBOX_MAILBOX_REG_TEST
mdefine_line|#define MBOX_MAILBOX_REG_TEST&t;&t;0x0006
DECL|macro|MBOX_VERIFY_CHECKSUM
mdefine_line|#define MBOX_VERIFY_CHECKSUM&t;&t;0x0007
DECL|macro|MBOX_ABOUT_FIRMWARE
mdefine_line|#define MBOX_ABOUT_FIRMWARE&t;&t;0x0008
DECL|macro|MBOX_CHECK_FIRMWARE
mdefine_line|#define MBOX_CHECK_FIRMWARE&t;&t;0x000e
DECL|macro|MBOX_INIT_REQ_QUEUE
mdefine_line|#define MBOX_INIT_REQ_QUEUE&t;&t;0x0010
DECL|macro|MBOX_INIT_RES_QUEUE
mdefine_line|#define MBOX_INIT_RES_QUEUE&t;&t;0x0011
DECL|macro|MBOX_EXECUTE_IOCB
mdefine_line|#define MBOX_EXECUTE_IOCB&t;&t;0x0012
DECL|macro|MBOX_WAKE_UP
mdefine_line|#define MBOX_WAKE_UP&t;&t;&t;0x0013
DECL|macro|MBOX_STOP_FIRMWARE
mdefine_line|#define MBOX_STOP_FIRMWARE&t;&t;0x0014
DECL|macro|MBOX_ABORT
mdefine_line|#define MBOX_ABORT&t;&t;&t;0x0015
DECL|macro|MBOX_ABORT_DEVICE
mdefine_line|#define MBOX_ABORT_DEVICE&t;&t;0x0016
DECL|macro|MBOX_ABORT_TARGET
mdefine_line|#define MBOX_ABORT_TARGET&t;&t;0x0017
DECL|macro|MBOX_BUS_RESET
mdefine_line|#define MBOX_BUS_RESET&t;&t;&t;0x0018
DECL|macro|MBOX_STOP_QUEUE
mdefine_line|#define MBOX_STOP_QUEUE&t;&t;&t;0x0019
DECL|macro|MBOX_START_QUEUE
mdefine_line|#define MBOX_START_QUEUE&t;&t;0x001a
DECL|macro|MBOX_SINGLE_STEP_QUEUE
mdefine_line|#define MBOX_SINGLE_STEP_QUEUE&t;&t;0x001b
DECL|macro|MBOX_ABORT_QUEUE
mdefine_line|#define MBOX_ABORT_QUEUE&t;&t;0x001c
DECL|macro|MBOX_GET_DEV_QUEUE_STATUS
mdefine_line|#define MBOX_GET_DEV_QUEUE_STATUS&t;0x001d
DECL|macro|MBOX_GET_FIRMWARE_STATUS
mdefine_line|#define MBOX_GET_FIRMWARE_STATUS&t;0x001f
DECL|macro|MBOX_GET_INIT_SCSI_ID
mdefine_line|#define MBOX_GET_INIT_SCSI_ID&t;&t;0x0020
DECL|macro|MBOX_GET_SELECT_TIMEOUT
mdefine_line|#define MBOX_GET_SELECT_TIMEOUT&t;&t;0x0021
DECL|macro|MBOX_GET_RETRY_COUNT
mdefine_line|#define MBOX_GET_RETRY_COUNT&t;&t;0x0022
DECL|macro|MBOX_GET_TAG_AGE_LIMIT
mdefine_line|#define MBOX_GET_TAG_AGE_LIMIT&t;&t;0x0023
DECL|macro|MBOX_GET_CLOCK_RATE
mdefine_line|#define MBOX_GET_CLOCK_RATE&t;&t;0x0024
DECL|macro|MBOX_GET_ACT_NEG_STATE
mdefine_line|#define MBOX_GET_ACT_NEG_STATE&t;&t;0x0025
DECL|macro|MBOX_GET_ASYNC_DATA_SETUP_TIME
mdefine_line|#define MBOX_GET_ASYNC_DATA_SETUP_TIME&t;0x0026
DECL|macro|MBOX_GET_SBUS_PARAMS
mdefine_line|#define MBOX_GET_SBUS_PARAMS&t;&t;0x0027
DECL|macro|MBOX_GET_TARGET_PARAMS
mdefine_line|#define MBOX_GET_TARGET_PARAMS&t;&t;0x0028
DECL|macro|MBOX_GET_DEV_QUEUE_PARAMS
mdefine_line|#define MBOX_GET_DEV_QUEUE_PARAMS&t;0x0029
DECL|macro|MBOX_SET_INIT_SCSI_ID
mdefine_line|#define MBOX_SET_INIT_SCSI_ID&t;&t;0x0030
DECL|macro|MBOX_SET_SELECT_TIMEOUT
mdefine_line|#define MBOX_SET_SELECT_TIMEOUT&t;&t;0x0031
DECL|macro|MBOX_SET_RETRY_COUNT
mdefine_line|#define MBOX_SET_RETRY_COUNT&t;&t;0x0032
DECL|macro|MBOX_SET_TAG_AGE_LIMIT
mdefine_line|#define MBOX_SET_TAG_AGE_LIMIT&t;&t;0x0033
DECL|macro|MBOX_SET_CLOCK_RATE
mdefine_line|#define MBOX_SET_CLOCK_RATE&t;&t;0x0034
DECL|macro|MBOX_SET_ACTIVE_NEG_STATE
mdefine_line|#define MBOX_SET_ACTIVE_NEG_STATE&t;0x0035
DECL|macro|MBOX_SET_ASYNC_DATA_SETUP_TIME
mdefine_line|#define MBOX_SET_ASYNC_DATA_SETUP_TIME&t;0x0036
DECL|macro|MBOX_SET_SBUS_CONTROL_PARAMS
mdefine_line|#define MBOX_SET_SBUS_CONTROL_PARAMS&t;0x0037
DECL|macro|MBOX_SET_TARGET_PARAMS
mdefine_line|#define MBOX_SET_TARGET_PARAMS&t;&t;0x0038
DECL|macro|MBOX_SET_DEV_QUEUE_PARAMS
mdefine_line|#define MBOX_SET_DEV_QUEUE_PARAMS&t;0x0039
DECL|struct|host_param
r_struct
id|host_param
(brace
DECL|member|initiator_scsi_id
id|u_short
id|initiator_scsi_id
suffix:semicolon
DECL|member|bus_reset_delay
id|u_short
id|bus_reset_delay
suffix:semicolon
DECL|member|retry_count
id|u_short
id|retry_count
suffix:semicolon
DECL|member|retry_delay
id|u_short
id|retry_delay
suffix:semicolon
DECL|member|async_data_setup_time
id|u_short
id|async_data_setup_time
suffix:semicolon
DECL|member|req_ack_active_negation
id|u_short
id|req_ack_active_negation
suffix:semicolon
DECL|member|data_line_active_negation
id|u_short
id|data_line_active_negation
suffix:semicolon
DECL|member|data_dma_burst_enable
id|u_short
id|data_dma_burst_enable
suffix:semicolon
DECL|member|command_dma_burst_enable
id|u_short
id|command_dma_burst_enable
suffix:semicolon
DECL|member|tag_aging
id|u_short
id|tag_aging
suffix:semicolon
DECL|member|selection_timeout
id|u_short
id|selection_timeout
suffix:semicolon
DECL|member|max_queue_depth
id|u_short
id|max_queue_depth
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Device Flags:&n; *&n; * Bit  Name&n; * ---------&n; *  7   Disconnect Privilege&n; *  6   Parity Checking&n; *  5   Wide Data Transfers&n; *  4   Synchronous Data Transfers&n; *  3   Tagged Queuing&n; *  2   Automatic Request Sense&n; *  1   Stop Queue on Check Condition&n; *  0   Renegotiate on Error&n; */
DECL|struct|dev_param
r_struct
id|dev_param
(brace
DECL|member|device_flags
id|u_short
id|device_flags
suffix:semicolon
DECL|member|execution_throttle
id|u_short
id|execution_throttle
suffix:semicolon
DECL|member|synchronous_period
id|u_short
id|synchronous_period
suffix:semicolon
DECL|member|synchronous_offset
id|u_short
id|synchronous_offset
suffix:semicolon
DECL|member|device_enable
id|u_short
id|device_enable
suffix:semicolon
DECL|member|reserved
id|u_short
id|reserved
suffix:semicolon
multiline_comment|/* pad */
)brace
suffix:semicolon
multiline_comment|/*&n; * The result queue can be quite a bit smaller since continuation entries&n; * do not show up there:&n; */
DECL|macro|RES_QUEUE_LEN
mdefine_line|#define RES_QUEUE_LEN&t;&t;255&t;/* Must be power of two - 1 */
DECL|macro|QUEUE_ENTRY_LEN
mdefine_line|#define QUEUE_ENTRY_LEN&t;&t;64
DECL|macro|NEXT_REQ_PTR
mdefine_line|#define NEXT_REQ_PTR(wheee)   (((wheee) + 1) &amp; QLOGICPTI_REQ_QUEUE_LEN)
DECL|macro|NEXT_RES_PTR
mdefine_line|#define NEXT_RES_PTR(wheee)   (((wheee) + 1) &amp; RES_QUEUE_LEN)
DECL|macro|PREV_REQ_PTR
mdefine_line|#define PREV_REQ_PTR(wheee)   (((wheee) - 1) &amp; QLOGICPTI_REQ_QUEUE_LEN)
DECL|macro|PREV_RES_PTR
mdefine_line|#define PREV_RES_PTR(wheee)   (((wheee) - 1) &amp; RES_QUEUE_LEN)
DECL|struct|pti_queue_entry
r_struct
id|pti_queue_entry
(brace
DECL|member|__opaque
r_char
id|__opaque
(braket
id|QUEUE_ENTRY_LEN
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Software state for the driver. */
DECL|struct|qlogicpti
r_struct
id|qlogicpti
(brace
multiline_comment|/* These are the hot elements in the cache, so they come first. */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* Driver mutex&t;&t;      */
DECL|member|qregs
r_int
r_int
id|qregs
suffix:semicolon
multiline_comment|/* Adapter registers          */
DECL|member|res_cpu
r_struct
id|pti_queue_entry
op_star
id|res_cpu
suffix:semicolon
multiline_comment|/* Ptr to RESPONSE bufs (CPU) */
DECL|member|req_cpu
r_struct
id|pti_queue_entry
op_star
id|req_cpu
suffix:semicolon
multiline_comment|/* Ptr to REQUEST bufs (CPU)  */
DECL|member|req_in_ptr
id|u_int
id|req_in_ptr
suffix:semicolon
multiline_comment|/* index of next request slot */
DECL|member|res_out_ptr
id|u_int
id|res_out_ptr
suffix:semicolon
multiline_comment|/* index of next result slot  */
DECL|member|send_marker
r_int
id|send_marker
suffix:semicolon
multiline_comment|/* must we send a marker?     */
DECL|member|sdev
r_struct
id|sbus_dev
op_star
id|sdev
suffix:semicolon
DECL|member|__pad
r_int
r_int
id|__pad
suffix:semicolon
DECL|member|cmd_count
r_int
id|cmd_count
(braket
id|MAX_TARGETS
)braket
suffix:semicolon
DECL|member|tag_ages
r_int
r_int
id|tag_ages
(braket
id|MAX_TARGETS
)braket
suffix:semicolon
multiline_comment|/* The cmd-&gt;handler is only 32-bits, so that things work even on monster&n;&t; * Ex000 sparc64 machines with &gt;4GB of ram we just keep track of the&n;&t; * scsi command pointers here.  This is essentially what Matt Jacob does. -DaveM&n;&t; */
DECL|member|cmd_slots
id|Scsi_Cmnd
op_star
id|cmd_slots
(braket
id|QLOGICPTI_REQ_QUEUE_LEN
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* The rest of the elements are unimportant for performance. */
DECL|member|next
r_struct
id|qlogicpti
op_star
id|next
suffix:semicolon
DECL|member|res_dvma
id|__u32
id|res_dvma
suffix:semicolon
multiline_comment|/* Ptr to RESPONSE bufs (DVMA)*/
DECL|member|req_dvma
id|__u32
id|req_dvma
suffix:semicolon
multiline_comment|/* Ptr to REQUEST bufs (DVMA) */
DECL|member|fware_majrev
DECL|member|fware_minrev
DECL|member|fware_micrev
id|u_char
id|fware_majrev
comma
id|fware_minrev
comma
id|fware_micrev
suffix:semicolon
DECL|member|qhost
r_struct
id|Scsi_Host
op_star
id|qhost
suffix:semicolon
DECL|member|qpti_id
r_int
id|qpti_id
suffix:semicolon
DECL|member|scsi_id
r_int
id|scsi_id
suffix:semicolon
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|differential
DECL|member|ultra
DECL|member|clock
r_char
id|differential
comma
id|ultra
comma
id|clock
suffix:semicolon
DECL|member|bursts
r_int
r_char
id|bursts
suffix:semicolon
DECL|member|host_param
r_struct
id|host_param
id|host_param
suffix:semicolon
DECL|member|dev_param
r_struct
id|dev_param
id|dev_param
(braket
id|MAX_TARGETS
)braket
suffix:semicolon
DECL|member|sreg
r_int
r_int
id|sreg
suffix:semicolon
DECL|macro|SREG_TPOWER
mdefine_line|#define SREG_TPOWER               0x80   /* State of termpwr           */
DECL|macro|SREG_FUSE
mdefine_line|#define SREG_FUSE                 0x40   /* State of on board fuse     */
DECL|macro|SREG_PDISAB
mdefine_line|#define SREG_PDISAB               0x20   /* Disable state for power on */
DECL|macro|SREG_DSENSE
mdefine_line|#define SREG_DSENSE               0x10   /* Sense for differential     */
DECL|macro|SREG_IMASK
mdefine_line|#define SREG_IMASK                0x0c   /* Interrupt level            */
DECL|macro|SREG_SPMASK
mdefine_line|#define SREG_SPMASK               0x03   /* Mask for switch pack       */
DECL|member|swsreg
r_int
r_char
id|swsreg
suffix:semicolon
r_int
r_int
DECL|member|gotirq
id|gotirq
suffix:colon
l_int|1
comma
multiline_comment|/* this instance got an irq */
DECL|member|is_pti
id|is_pti
suffix:colon
l_int|1
comma
multiline_comment|/* Non-zero if this is a PTI board. */
DECL|member|sbits
id|sbits
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* syncmode known bits */
)brace
suffix:semicolon
multiline_comment|/* How to twiddle them bits... */
multiline_comment|/* SBUS config register one. */
DECL|macro|SBUS_CFG1_EPAR
mdefine_line|#define SBUS_CFG1_EPAR          0x0100      /* Enable parity checking           */
DECL|macro|SBUS_CFG1_FMASK
mdefine_line|#define SBUS_CFG1_FMASK         0x00f0      /* Forth code cycle mask            */
DECL|macro|SBUS_CFG1_BENAB
mdefine_line|#define SBUS_CFG1_BENAB         0x0004      /* Burst dvma enable                */
DECL|macro|SBUS_CFG1_B64
mdefine_line|#define SBUS_CFG1_B64           0x0003      /* Enable 64byte bursts             */
DECL|macro|SBUS_CFG1_B32
mdefine_line|#define SBUS_CFG1_B32           0x0002      /* Enable 32byte bursts             */
DECL|macro|SBUS_CFG1_B16
mdefine_line|#define SBUS_CFG1_B16           0x0001      /* Enable 16byte bursts             */
DECL|macro|SBUS_CFG1_B8
mdefine_line|#define SBUS_CFG1_B8            0x0008      /* Enable 8byte bursts              */
multiline_comment|/* SBUS control register */
DECL|macro|SBUS_CTRL_EDIRQ
mdefine_line|#define SBUS_CTRL_EDIRQ         0x0020      /* Enable Data DVMA Interrupts      */
DECL|macro|SBUS_CTRL_ECIRQ
mdefine_line|#define SBUS_CTRL_ECIRQ         0x0010      /* Enable Command DVMA Interrupts   */
DECL|macro|SBUS_CTRL_ESIRQ
mdefine_line|#define SBUS_CTRL_ESIRQ         0x0008      /* Enable SCSI Processor Interrupts */
DECL|macro|SBUS_CTRL_ERIRQ
mdefine_line|#define SBUS_CTRL_ERIRQ         0x0004      /* Enable RISC Processor Interrupts */
DECL|macro|SBUS_CTRL_GENAB
mdefine_line|#define SBUS_CTRL_GENAB         0x0002      /* Global Interrupt Enable          */
DECL|macro|SBUS_CTRL_RESET
mdefine_line|#define SBUS_CTRL_RESET         0x0001      /* Soft Reset                       */
multiline_comment|/* SBUS status register */
DECL|macro|SBUS_STAT_DINT
mdefine_line|#define SBUS_STAT_DINT          0x0020      /* Data DVMA IRQ pending            */
DECL|macro|SBUS_STAT_CINT
mdefine_line|#define SBUS_STAT_CINT          0x0010      /* Command DVMA IRQ pending         */
DECL|macro|SBUS_STAT_SINT
mdefine_line|#define SBUS_STAT_SINT          0x0008      /* SCSI Processor IRQ pending       */
DECL|macro|SBUS_STAT_RINT
mdefine_line|#define SBUS_STAT_RINT          0x0004      /* RISC Processor IRQ pending       */
DECL|macro|SBUS_STAT_GINT
mdefine_line|#define SBUS_STAT_GINT          0x0002      /* Global IRQ pending               */
multiline_comment|/* SBUS semaphore register */
DECL|macro|SBUS_SEMAPHORE_STAT
mdefine_line|#define SBUS_SEMAPHORE_STAT     0x0002      /* Semaphore status bit             */
DECL|macro|SBUS_SEMAPHORE_LCK
mdefine_line|#define SBUS_SEMAPHORE_LCK      0x0001      /* Semaphore lock bit               */
multiline_comment|/* DVMA control register */
DECL|macro|DMA_CTRL_CSUSPEND
mdefine_line|#define DMA_CTRL_CSUSPEND       0x0010      /* DMA channel suspend              */
DECL|macro|DMA_CTRL_CCLEAR
mdefine_line|#define DMA_CTRL_CCLEAR         0x0008      /* DMA channel clear and reset      */
DECL|macro|DMA_CTRL_FCLEAR
mdefine_line|#define DMA_CTRL_FCLEAR         0x0004      /* DMA fifo clear                   */
DECL|macro|DMA_CTRL_CIRQ
mdefine_line|#define DMA_CTRL_CIRQ           0x0002      /* DMA irq clear                    */
DECL|macro|DMA_CTRL_DMASTART
mdefine_line|#define DMA_CTRL_DMASTART       0x0001      /* DMA transfer start               */
multiline_comment|/* SCSI processor override register */
DECL|macro|CPU_ORIDE_ETRIG
mdefine_line|#define CPU_ORIDE_ETRIG         0x8000      /* External trigger enable          */
DECL|macro|CPU_ORIDE_STEP
mdefine_line|#define CPU_ORIDE_STEP          0x4000      /* Single step mode enable          */
DECL|macro|CPU_ORIDE_BKPT
mdefine_line|#define CPU_ORIDE_BKPT          0x2000      /* Breakpoint reg enable            */
DECL|macro|CPU_ORIDE_PWRITE
mdefine_line|#define CPU_ORIDE_PWRITE        0x1000      /* SCSI pin write enable            */
DECL|macro|CPU_ORIDE_OFORCE
mdefine_line|#define CPU_ORIDE_OFORCE        0x0800      /* Force outputs on                 */
DECL|macro|CPU_ORIDE_LBACK
mdefine_line|#define CPU_ORIDE_LBACK         0x0400      /* SCSI loopback enable             */
DECL|macro|CPU_ORIDE_PTEST
mdefine_line|#define CPU_ORIDE_PTEST         0x0200      /* Parity test enable               */
DECL|macro|CPU_ORIDE_TENAB
mdefine_line|#define CPU_ORIDE_TENAB         0x0100      /* SCSI pins tristate enable        */
DECL|macro|CPU_ORIDE_TPINS
mdefine_line|#define CPU_ORIDE_TPINS         0x0080      /* SCSI pins enable                 */
DECL|macro|CPU_ORIDE_FRESET
mdefine_line|#define CPU_ORIDE_FRESET        0x0008      /* FIFO reset                       */
DECL|macro|CPU_ORIDE_CTERM
mdefine_line|#define CPU_ORIDE_CTERM         0x0004      /* Command terminate                */
DECL|macro|CPU_ORIDE_RREG
mdefine_line|#define CPU_ORIDE_RREG          0x0002      /* Reset SCSI processor regs        */
DECL|macro|CPU_ORIDE_RMOD
mdefine_line|#define CPU_ORIDE_RMOD          0x0001      /* Reset SCSI processor module      */
multiline_comment|/* SCSI processor commands */
DECL|macro|CPU_CMD_BRESET
mdefine_line|#define CPU_CMD_BRESET          0x300b      /* Reset SCSI bus                   */
multiline_comment|/* SCSI processor pin control register */
DECL|macro|CPU_PCTRL_PVALID
mdefine_line|#define CPU_PCTRL_PVALID        0x8000      /* Phase bits are valid             */
DECL|macro|CPU_PCTRL_PHI
mdefine_line|#define CPU_PCTRL_PHI           0x0400      /* Parity bit high                  */
DECL|macro|CPU_PCTRL_PLO
mdefine_line|#define CPU_PCTRL_PLO           0x0200      /* Parity bit low                   */
DECL|macro|CPU_PCTRL_REQ
mdefine_line|#define CPU_PCTRL_REQ           0x0100      /* REQ bus signal                   */
DECL|macro|CPU_PCTRL_ACK
mdefine_line|#define CPU_PCTRL_ACK           0x0080      /* ACK bus signal                   */
DECL|macro|CPU_PCTRL_RST
mdefine_line|#define CPU_PCTRL_RST           0x0040      /* RST bus signal                   */
DECL|macro|CPU_PCTRL_BSY
mdefine_line|#define CPU_PCTRL_BSY           0x0020      /* BSY bus signal                   */
DECL|macro|CPU_PCTRL_SEL
mdefine_line|#define CPU_PCTRL_SEL           0x0010      /* SEL bus signal                   */
DECL|macro|CPU_PCTRL_ATN
mdefine_line|#define CPU_PCTRL_ATN           0x0008      /* ATN bus signal                   */
DECL|macro|CPU_PCTRL_MSG
mdefine_line|#define CPU_PCTRL_MSG           0x0004      /* MSG bus signal                   */
DECL|macro|CPU_PCTRL_CD
mdefine_line|#define CPU_PCTRL_CD            0x0002      /* CD bus signal                    */
DECL|macro|CPU_PCTRL_IO
mdefine_line|#define CPU_PCTRL_IO            0x0001      /* IO bus signal                    */
multiline_comment|/* SCSI processor differential pins register */
DECL|macro|CPU_PDIFF_SENSE
mdefine_line|#define CPU_PDIFF_SENSE         0x0200      /* Differential sense               */
DECL|macro|CPU_PDIFF_MODE
mdefine_line|#define CPU_PDIFF_MODE          0x0100      /* Differential mode                */
DECL|macro|CPU_PDIFF_OENAB
mdefine_line|#define CPU_PDIFF_OENAB         0x0080      /* Outputs enable                   */
DECL|macro|CPU_PDIFF_PMASK
mdefine_line|#define CPU_PDIFF_PMASK         0x007c      /* Differential control pins        */
DECL|macro|CPU_PDIFF_TGT
mdefine_line|#define CPU_PDIFF_TGT           0x0002      /* Target mode enable               */
DECL|macro|CPU_PDIFF_INIT
mdefine_line|#define CPU_PDIFF_INIT          0x0001      /* Initiator mode enable            */
multiline_comment|/* RISC processor status register */
DECL|macro|RISC_PSR_FTRUE
mdefine_line|#define RISC_PSR_FTRUE          0x8000      /* Force true                       */
DECL|macro|RISC_PSR_LCD
mdefine_line|#define RISC_PSR_LCD            0x4000      /* Loop counter shows done status   */
DECL|macro|RISC_PSR_RIRQ
mdefine_line|#define RISC_PSR_RIRQ           0x2000      /* RISC irq status                  */
DECL|macro|RISC_PSR_TOFLOW
mdefine_line|#define RISC_PSR_TOFLOW         0x1000      /* Timer overflow (rollover)        */
DECL|macro|RISC_PSR_AOFLOW
mdefine_line|#define RISC_PSR_AOFLOW         0x0800      /* Arithmetic overflow              */
DECL|macro|RISC_PSR_AMSB
mdefine_line|#define RISC_PSR_AMSB           0x0400      /* Arithmetic big endian            */
DECL|macro|RISC_PSR_ACARRY
mdefine_line|#define RISC_PSR_ACARRY         0x0200      /* Arithmetic carry                 */
DECL|macro|RISC_PSR_AZERO
mdefine_line|#define RISC_PSR_AZERO          0x0100      /* Arithmetic zero                  */
DECL|macro|RISC_PSR_ULTRA
mdefine_line|#define RISC_PSR_ULTRA          0x0020      /* Ultra mode                       */
DECL|macro|RISC_PSR_DIRQ
mdefine_line|#define RISC_PSR_DIRQ           0x0010      /* DVMA interrupt                   */
DECL|macro|RISC_PSR_SIRQ
mdefine_line|#define RISC_PSR_SIRQ           0x0008      /* SCSI processor interrupt         */
DECL|macro|RISC_PSR_HIRQ
mdefine_line|#define RISC_PSR_HIRQ           0x0004      /* Host interrupt                   */
DECL|macro|RISC_PSR_IPEND
mdefine_line|#define RISC_PSR_IPEND          0x0002      /* Interrupt pending                */
DECL|macro|RISC_PSR_FFALSE
mdefine_line|#define RISC_PSR_FFALSE         0x0001      /* Force false                      */
multiline_comment|/* RISC processor memory timing register */
DECL|macro|RISC_MTREG_P1DFLT
mdefine_line|#define RISC_MTREG_P1DFLT       0x1200      /* Default read/write timing, pg1   */
DECL|macro|RISC_MTREG_P0DFLT
mdefine_line|#define RISC_MTREG_P0DFLT       0x0012      /* Default read/write timing, pg0   */
DECL|macro|RISC_MTREG_P1ULTRA
mdefine_line|#define RISC_MTREG_P1ULTRA      0x2300      /* Ultra-mode rw timing, pg1        */
DECL|macro|RISC_MTREG_P0ULTRA
mdefine_line|#define RISC_MTREG_P0ULTRA      0x0023      /* Ultra-mode rw timing, pg0        */
multiline_comment|/* Host command/ctrl register */
DECL|macro|HCCTRL_NOP
mdefine_line|#define HCCTRL_NOP              0x0000      /* CMD: No operation                */
DECL|macro|HCCTRL_RESET
mdefine_line|#define HCCTRL_RESET            0x1000      /* CMD: Reset RISC cpu              */
DECL|macro|HCCTRL_PAUSE
mdefine_line|#define HCCTRL_PAUSE            0x2000      /* CMD: Pause RISC cpu              */
DECL|macro|HCCTRL_REL
mdefine_line|#define HCCTRL_REL              0x3000      /* CMD: Release paused RISC cpu     */
DECL|macro|HCCTRL_STEP
mdefine_line|#define HCCTRL_STEP             0x4000      /* CMD: Single step RISC cpu        */
DECL|macro|HCCTRL_SHIRQ
mdefine_line|#define HCCTRL_SHIRQ            0x5000      /* CMD: Set host irq                */
DECL|macro|HCCTRL_CHIRQ
mdefine_line|#define HCCTRL_CHIRQ            0x6000      /* CMD: Clear host irq              */
DECL|macro|HCCTRL_CRIRQ
mdefine_line|#define HCCTRL_CRIRQ            0x7000      /* CMD: Clear RISC cpu irq          */
DECL|macro|HCCTRL_BKPT
mdefine_line|#define HCCTRL_BKPT             0x8000      /* CMD: Breakpoint enables change   */
DECL|macro|HCCTRL_TMODE
mdefine_line|#define HCCTRL_TMODE            0xf000      /* CMD: Enable test mode            */
DECL|macro|HCCTRL_HIRQ
mdefine_line|#define HCCTRL_HIRQ             0x0080      /* Host IRQ pending                 */
DECL|macro|HCCTRL_RRIP
mdefine_line|#define HCCTRL_RRIP             0x0040      /* RISC cpu reset in happening now  */
DECL|macro|HCCTRL_RPAUSED
mdefine_line|#define HCCTRL_RPAUSED          0x0020      /* RISC cpu is paused now           */
DECL|macro|HCCTRL_EBENAB
mdefine_line|#define HCCTRL_EBENAB           0x0010      /* External breakpoint enable       */
DECL|macro|HCCTRL_B1ENAB
mdefine_line|#define HCCTRL_B1ENAB           0x0008      /* Breakpoint 1 enable              */
DECL|macro|HCCTRL_B0ENAB
mdefine_line|#define HCCTRL_B0ENAB           0x0004      /* Breakpoint 0 enable              */
DECL|macro|QLOGICPTI
mdefine_line|#define QLOGICPTI {&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;detect:&t;&t;qlogicpti_detect,&t;&t;&t;   &bslash;&n;&t;release:&t;qlogicpti_release,&t;&t;&t;   &bslash;&n;&t;info:&t;&t;qlogicpti_info,&t;&t;&t;&t;   &bslash;&n;&t;queuecommand:&t;qlogicpti_queuecommand_slow,&t;&t;   &bslash;&n;&t;abort:&t;&t;qlogicpti_abort,&t;&t;&t;   &bslash;&n;&t;reset:&t;&t;qlogicpti_reset,&t;&t;&t;   &bslash;&n;&t;can_queue:&t;QLOGICPTI_REQ_QUEUE_LEN,&t;&t;   &bslash;&n;&t;this_id:&t;7,&t;&t;&t;&t;&t;   &bslash;&n;&t;sg_tablesize:&t;QLOGICPTI_MAX_SG(QLOGICPTI_REQ_QUEUE_LEN), &bslash;&n;&t;cmd_per_lun:&t;1,&t;&t;&t;&t;&t;   &bslash;&n;&t;use_clustering:&t;ENABLE_CLUSTERING,&t;&t;&t;   &bslash;&n;&t;highmem_io:&t;1,&t;&t;&t;   &t;&t;   &bslash;&n;}
multiline_comment|/* For our interrupt engine. */
DECL|macro|for_each_qlogicpti
mdefine_line|#define for_each_qlogicpti(qp) &bslash;&n;        for((qp) = qptichain; (qp); (qp) = (qp)-&gt;next)
macro_line|#endif /* !(_QLOGICPTI_H) */
eof
