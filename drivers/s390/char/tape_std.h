multiline_comment|/*&n; *  drivers/s390/char/tape_34xx.h&n; *    standard tape device functions for ibm tapes.&n; *&n; *  S390 and zSeries version&n; *    Copyright (C) 2001,2002 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Carsten Otte &lt;cotte@de.ibm.com&gt;&n; *&t;&t; Tuan Ngo-Anh &lt;ngoanh@de.ibm.com&gt;&n; *&t;&t; Martin Schwidefsky &lt;schwidefsky@de.ibm.com&gt;&n; */
macro_line|#ifndef _TAPE_STD_H
DECL|macro|_TAPE_STD_H
mdefine_line|#define _TAPE_STD_H
macro_line|#include &lt;asm/tape390.h&gt;
multiline_comment|/*&n; * Biggest block size to handle. Currently 64K because we only build&n; * channel programs without data chaining.&n; */
DECL|macro|MAX_BLOCKSIZE
mdefine_line|#define MAX_BLOCKSIZE   65535
multiline_comment|/*&n; * The CCW commands for the Tape type of command.&n; */
DECL|macro|INVALID_00
mdefine_line|#define INVALID_00&t;&t;0x00&t;/* Invalid cmd */
DECL|macro|BACKSPACEBLOCK
mdefine_line|#define BACKSPACEBLOCK&t;&t;0x27&t;/* Back Space block */
DECL|macro|BACKSPACEFILE
mdefine_line|#define BACKSPACEFILE&t;&t;0x2f&t;/* Back Space file */
DECL|macro|DATA_SEC_ERASE
mdefine_line|#define DATA_SEC_ERASE&t;&t;0x97&t;/* Data security erase */
DECL|macro|ERASE_GAP
mdefine_line|#define ERASE_GAP&t;&t;0x17&t;/* Erase Gap */
DECL|macro|FORSPACEBLOCK
mdefine_line|#define FORSPACEBLOCK&t;&t;0x37&t;/* Forward space block */
DECL|macro|FORSPACEFILE
mdefine_line|#define FORSPACEFILE&t;&t;0x3F&t;/* Forward Space file */
DECL|macro|FORCE_STREAM_CNT
mdefine_line|#define FORCE_STREAM_CNT&t;0xEB&t;/* Forced streaming count # */
DECL|macro|NOP
mdefine_line|#define NOP&t;&t;&t;0x03&t;/* No operation&t;*/
DECL|macro|READ_FORWARD
mdefine_line|#define READ_FORWARD&t;&t;0x02&t;/* Read forward */
DECL|macro|REWIND
mdefine_line|#define REWIND&t;&t;&t;0x07&t;/* Rewind */
DECL|macro|REWIND_UNLOAD
mdefine_line|#define REWIND_UNLOAD&t;&t;0x0F&t;/* Rewind and Unload */
DECL|macro|SENSE
mdefine_line|#define SENSE&t;&t;&t;0x04&t;/* Sense */
DECL|macro|NEW_MODE_SET
mdefine_line|#define NEW_MODE_SET&t;&t;0xEB&t;/* Guess it is Mode set */
DECL|macro|WRITE_CMD
mdefine_line|#define WRITE_CMD&t;&t;0x01&t;/* Write */
DECL|macro|WRITETAPEMARK
mdefine_line|#define WRITETAPEMARK&t;&t;0x1F&t;/* Write Tape Mark */
DECL|macro|ASSIGN
mdefine_line|#define ASSIGN&t;&t;&t;0xB7&t;/* 3420 REJECT,3480 OK&t;*/
DECL|macro|CONTROL_ACCESS
mdefine_line|#define CONTROL_ACCESS&t;&t;0xE3&t;/* Set high speed */
DECL|macro|DIAG_MODE_SET
mdefine_line|#define DIAG_MODE_SET&t;&t;0x0B&t;/* 3420 NOP, 3480 REJECT */
DECL|macro|LOAD_DISPLAY
mdefine_line|#define LOAD_DISPLAY&t;&t;0x9F&t;/* 3420 REJECT,3480 OK */
DECL|macro|LOCATE
mdefine_line|#define LOCATE&t;&t;&t;0x4F&t;/* 3420 REJ, 3480 NOP */
DECL|macro|LOOP_WRITE_TO_READ
mdefine_line|#define LOOP_WRITE_TO_READ&t;0x8B&t;/* 3480 REJECT */
DECL|macro|MODE_SET_DB
mdefine_line|#define MODE_SET_DB&t;&t;0xDB&t;/* 3420 REJECT,3480 OK */
DECL|macro|MODE_SET_C3
mdefine_line|#define MODE_SET_C3&t;&t;0xC3&t;/* for 3420 */
DECL|macro|MODE_SET_CB
mdefine_line|#define MODE_SET_CB&t;&t;0xCB&t;/* for 3420 */
DECL|macro|MODE_SET_D3
mdefine_line|#define MODE_SET_D3&t;&t;0xD3&t;/* for 3420 */
DECL|macro|READ_BACKWARD
mdefine_line|#define READ_BACKWARD&t;&t;0x0C&t;/* */
DECL|macro|READ_BLOCK_ID
mdefine_line|#define READ_BLOCK_ID&t;&t;0x22&t;/* 3420 REJECT,3480 OK */
DECL|macro|READ_BUFFER
mdefine_line|#define READ_BUFFER&t;&t;0x12&t;/* 3420 REJECT,3480 OK */
DECL|macro|READ_BUFF_LOG
mdefine_line|#define READ_BUFF_LOG&t;&t;0x24&t;/* 3420 REJECT,3480 OK */
DECL|macro|RELEASE
mdefine_line|#define RELEASE&t;&t;&t;0xD4&t;/* 3420 NOP, 3480 REJECT */
DECL|macro|REQ_TRK_IN_ERROR
mdefine_line|#define REQ_TRK_IN_ERROR&t;0x1B&t;/* 3420 NOP, 3480 REJECT */
DECL|macro|RESERVE
mdefine_line|#define RESERVE&t;&t;&t;0xF4&t;/* 3420 NOP, 3480 REJECT */
DECL|macro|SENSE_GROUP_ID
mdefine_line|#define SENSE_GROUP_ID&t;&t;0x34&t;/* 3420 REJECT,3480 OK */
DECL|macro|SENSE_ID
mdefine_line|#define SENSE_ID&t;&t;0xE4&t;/* 3420 REJECT,3480 OK */
DECL|macro|READ_DEV_CHAR
mdefine_line|#define READ_DEV_CHAR&t;&t;0x64&t;/* Read device characteristics */
DECL|macro|SET_DIAGNOSE
mdefine_line|#define SET_DIAGNOSE&t;&t;0x4B&t;/* 3420 NOP, 3480 REJECT */
DECL|macro|SET_GROUP_ID
mdefine_line|#define SET_GROUP_ID&t;&t;0xAF&t;/* 3420 REJECT,3480 OK */
DECL|macro|SET_TAPE_WRITE_IMMED
mdefine_line|#define SET_TAPE_WRITE_IMMED&t;0xC3&t;/* for 3480 */
DECL|macro|SUSPEND
mdefine_line|#define SUSPEND&t;&t;&t;0x5B&t;/* 3420 REJ, 3480 NOP */
DECL|macro|SYNC
mdefine_line|#define SYNC&t;&t;&t;0x43&t;/* Synchronize (flush buffer) */
DECL|macro|UNASSIGN
mdefine_line|#define UNASSIGN&t;&t;0xC7&t;/* 3420 REJECT,3480 OK */
DECL|macro|PERF_SUBSYS_FUNC
mdefine_line|#define PERF_SUBSYS_FUNC&t;0x77&t;/* 3490 CMD */
DECL|macro|READ_CONFIG_DATA
mdefine_line|#define READ_CONFIG_DATA&t;0xFA&t;/* 3490 CMD */
DECL|macro|READ_MESSAGE_ID
mdefine_line|#define READ_MESSAGE_ID&t;&t;0x4E&t;/* 3490 CMD */
DECL|macro|READ_SUBSYS_DATA
mdefine_line|#define READ_SUBSYS_DATA&t;0x3E&t;/* 3490 CMD */
DECL|macro|SET_INTERFACE_ID
mdefine_line|#define SET_INTERFACE_ID&t;0x73&t;/* 3490 CMD */
DECL|macro|SENSE_COMMAND_REJECT
mdefine_line|#define SENSE_COMMAND_REJECT&t;&t;0x80
DECL|macro|SENSE_INTERVENTION_REQUIRED
mdefine_line|#define SENSE_INTERVENTION_REQUIRED&t;0x40
DECL|macro|SENSE_BUS_OUT_CHECK
mdefine_line|#define SENSE_BUS_OUT_CHECK&t;&t;0x20
DECL|macro|SENSE_EQUIPMENT_CHECK
mdefine_line|#define SENSE_EQUIPMENT_CHECK&t;&t;0x10
DECL|macro|SENSE_DATA_CHECK
mdefine_line|#define SENSE_DATA_CHECK&t;&t;0x08
DECL|macro|SENSE_OVERRUN
mdefine_line|#define SENSE_OVERRUN&t;&t;&t;0x04
DECL|macro|SENSE_DEFERRED_UNIT_CHECK
mdefine_line|#define SENSE_DEFERRED_UNIT_CHECK&t;0x02
DECL|macro|SENSE_ASSIGNED_ELSEWHERE
mdefine_line|#define SENSE_ASSIGNED_ELSEWHERE&t;0x01
DECL|macro|SENSE_LOCATE_FAILURE
mdefine_line|#define SENSE_LOCATE_FAILURE&t;&t;0x80
DECL|macro|SENSE_DRIVE_ONLINE
mdefine_line|#define SENSE_DRIVE_ONLINE&t;&t;0x40
DECL|macro|SENSE_RESERVED
mdefine_line|#define SENSE_RESERVED&t;&t;&t;0x20
DECL|macro|SENSE_RECORD_SEQUENCE_ERR
mdefine_line|#define SENSE_RECORD_SEQUENCE_ERR&t;0x10
DECL|macro|SENSE_BEGINNING_OF_TAPE
mdefine_line|#define SENSE_BEGINNING_OF_TAPE&t;&t;0x08
DECL|macro|SENSE_WRITE_MODE
mdefine_line|#define SENSE_WRITE_MODE&t;&t;0x04
DECL|macro|SENSE_WRITE_PROTECT
mdefine_line|#define SENSE_WRITE_PROTECT&t;&t;0x02
DECL|macro|SENSE_NOT_CAPABLE
mdefine_line|#define SENSE_NOT_CAPABLE&t;&t;0x01
DECL|macro|SENSE_CHANNEL_ADAPTER_CODE
mdefine_line|#define SENSE_CHANNEL_ADAPTER_CODE&t;0xE0
DECL|macro|SENSE_CHANNEL_ADAPTER_LOC
mdefine_line|#define SENSE_CHANNEL_ADAPTER_LOC&t;0x10
DECL|macro|SENSE_REPORTING_CU
mdefine_line|#define SENSE_REPORTING_CU&t;&t;0x08
DECL|macro|SENSE_AUTOMATIC_LOADER
mdefine_line|#define SENSE_AUTOMATIC_LOADER&t;&t;0x04
DECL|macro|SENSE_TAPE_SYNC_MODE
mdefine_line|#define SENSE_TAPE_SYNC_MODE&t;&t;0x02
DECL|macro|SENSE_TAPE_POSITIONING
mdefine_line|#define SENSE_TAPE_POSITIONING&t;&t;0x01
multiline_comment|/* discipline functions */
r_struct
id|tape_request
op_star
id|tape_std_read_block
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|tape_std_read_backward
c_func
(paren
r_struct
id|tape_device
op_star
id|device
comma
r_struct
id|tape_request
op_star
id|request
)paren
suffix:semicolon
r_struct
id|tape_request
op_star
id|tape_std_write_block
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_struct
id|tape_request
op_star
id|tape_std_bread
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
r_void
id|tape_std_free_bread
c_func
(paren
r_struct
id|tape_request
op_star
)paren
suffix:semicolon
r_void
id|tape_std_check_locate
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_struct
id|tape_request
op_star
)paren
suffix:semicolon
r_struct
id|tape_request
op_star
id|tape_std_bwrite
c_func
(paren
r_struct
id|request
op_star
comma
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Some non-mtop commands. */
r_int
id|tape_std_assign
c_func
(paren
r_struct
id|tape_device
op_star
)paren
suffix:semicolon
r_int
id|tape_std_unassign
c_func
(paren
r_struct
id|tape_device
op_star
)paren
suffix:semicolon
r_int
id|tape_std_read_block_id
c_func
(paren
r_struct
id|tape_device
op_star
id|device
comma
id|__u64
op_star
id|id
)paren
suffix:semicolon
r_int
id|tape_std_display
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_struct
id|display_struct
op_star
id|disp
)paren
suffix:semicolon
r_int
id|tape_std_terminate_write
c_func
(paren
r_struct
id|tape_device
op_star
)paren
suffix:semicolon
multiline_comment|/* Standard magnetic tape commands. */
r_int
id|tape_std_mtbsf
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|tape_std_mtbsfm
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|tape_std_mtbsr
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|tape_std_mtcompression
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|tape_std_mteom
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|tape_std_mterase
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|tape_std_mtfsf
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|tape_std_mtfsfm
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|tape_std_mtfsr
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|tape_std_mtload
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|tape_std_mtnop
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|tape_std_mtoffl
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|tape_std_mtreset
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|tape_std_mtreten
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|tape_std_mtrew
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|tape_std_mtsetblk
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|tape_std_mtunload
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|tape_std_mtweof
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Event handlers */
r_void
id|tape_std_default_handler
c_func
(paren
r_struct
id|tape_device
op_star
)paren
suffix:semicolon
r_void
id|tape_std_unexpect_uchk_handler
c_func
(paren
r_struct
id|tape_device
op_star
)paren
suffix:semicolon
r_void
id|tape_std_irq
c_func
(paren
r_struct
id|tape_device
op_star
)paren
suffix:semicolon
r_void
id|tape_std_process_eov
c_func
(paren
r_struct
id|tape_device
op_star
)paren
suffix:semicolon
singleline_comment|// the error recovery stuff:
r_void
id|tape_std_error_recovery
c_func
(paren
r_struct
id|tape_device
op_star
)paren
suffix:semicolon
r_void
id|tape_std_error_recovery_has_failed
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
id|error_id
)paren
suffix:semicolon
r_void
id|tape_std_error_recovery_succeded
c_func
(paren
r_struct
id|tape_device
op_star
)paren
suffix:semicolon
r_void
id|tape_std_error_recovery_do_retry
c_func
(paren
r_struct
id|tape_device
op_star
)paren
suffix:semicolon
r_void
id|tape_std_error_recovery_read_opposite
c_func
(paren
r_struct
id|tape_device
op_star
)paren
suffix:semicolon
r_void
id|tape_std_error_recovery_HWBUG
c_func
(paren
r_struct
id|tape_device
op_star
comma
r_int
id|condno
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// _TAPE_STD_H
eof
