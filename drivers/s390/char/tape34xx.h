multiline_comment|/***************************************************************************&n; *&n; *  drivers/s390/char/tape34xx.h&n; *    common tape device discipline for 34xx tapes.&n; *&n; *  S390 and zSeries version&n; *    Copyright (C) 2001 IBM Corporation&n; *    Author(s): Carsten Otte &lt;cotte@de.ibm.com&gt;&n; *               Tuan Ngo-Anh &lt;ngoanh@de.ibm.com&gt;&n; *&n; ****************************************************************************&n; */
macro_line|#ifndef _TAPE34XX_H
DECL|macro|_TAPE34XX_H
mdefine_line|#define _TAPE34XX_H
multiline_comment|/*&n; * The CCW commands for the Tape type of command.&n; */
DECL|macro|INVALID_00
mdefine_line|#define         INVALID_00              0x00    /* Invalid cmd      */
DECL|macro|BACKSPACEBLOCK
mdefine_line|#define         BACKSPACEBLOCK          0x27    /* Back Space block */
DECL|macro|BACKSPACEFILE
mdefine_line|#define         BACKSPACEFILE           0x2f    /* Back Space file */
DECL|macro|DATA_SEC_ERASE
mdefine_line|#define         DATA_SEC_ERASE          0x97    /* Data security erase */
DECL|macro|ERASE_GAP
mdefine_line|#define         ERASE_GAP               0x17    /* Erase Gap */
DECL|macro|FORSPACEBLOCK
mdefine_line|#define         FORSPACEBLOCK           0x37    /* Forward space block */
DECL|macro|FORSPACEFILE
mdefine_line|#define         FORSPACEFILE            0x3F    /* Forward Space file */
DECL|macro|FORCE_STREAM_CNT
mdefine_line|#define         FORCE_STREAM_CNT        0xEB    /* Forced streaming count #   */
DECL|macro|NOP
mdefine_line|#define         NOP                     0x03    /* No operation  */
DECL|macro|READ_FORWARD
mdefine_line|#define         READ_FORWARD            0x02    /* Read forward */
DECL|macro|REWIND
mdefine_line|#define         REWIND                  0x07    /* Rewind */
DECL|macro|REWIND_UNLOAD
mdefine_line|#define         REWIND_UNLOAD           0x0F    /* Rewind and Unload */
DECL|macro|SENSE
mdefine_line|#define         SENSE                   0x04    /* Sense */
DECL|macro|NEW_MODE_SET
mdefine_line|#define         NEW_MODE_SET            0xEB    /* Guess it is Mode set */
DECL|macro|WRITE_CMD
mdefine_line|#define         WRITE_CMD               0x01    /* Write */
DECL|macro|WRITETAPEMARK
mdefine_line|#define         WRITETAPEMARK           0x1F    /* Write Tape Mark */
DECL|macro|ASSIGN
mdefine_line|#define         ASSIGN                  0xB7    /* 3420 REJECT,3480 OK  */
DECL|macro|CONTROL_ACCESS
mdefine_line|#define         CONTROL_ACCESS          0xE3    /* Set high speed */
DECL|macro|DIAG_MODE_SET
mdefine_line|#define         DIAG_MODE_SET           0x0B    /* 3420 NOP, 3480 REJECT*/
DECL|macro|LOAD_DISPLAY
mdefine_line|#define         LOAD_DISPLAY            0x9F    /* 3420 REJECT,3480 OK  */
DECL|macro|LOCATE
mdefine_line|#define         LOCATE                  0x4F    /* 3420 REJ, 3480 NOP   */
DECL|macro|LOOP_WRITE_TO_READ
mdefine_line|#define         LOOP_WRITE_TO_READ      0x8B    /* 3480 REJECT        */
DECL|macro|MODE_SET_DB
mdefine_line|#define         MODE_SET_DB             0xDB    /* 3420 REJECT,3480 OK  */
DECL|macro|MODE_SET_C3
mdefine_line|#define         MODE_SET_C3             0xC3    /* for 3420                */
DECL|macro|MODE_SET_CB
mdefine_line|#define         MODE_SET_CB             0xCB    /* for 3420                */
DECL|macro|MODE_SET_D3
mdefine_line|#define         MODE_SET_D3             0xD3    /* for 3420                */
DECL|macro|READ_BACKWARD
mdefine_line|#define         READ_BACKWARD           0x0C    /*                      */
DECL|macro|READ_BLOCK_ID
mdefine_line|#define         READ_BLOCK_ID           0x22    /* 3420 REJECT,3480 OK  */
DECL|macro|READ_BUFFER
mdefine_line|#define         READ_BUFFER             0x12    /* 3420 REJECT,3480 OK  */
DECL|macro|READ_BUFF_LOG
mdefine_line|#define         READ_BUFF_LOG           0x24    /* 3420 REJECT,3480 OK  */
DECL|macro|RELEASE
mdefine_line|#define         RELEASE                 0xD4    /* 3420 NOP, 3480 REJECT*/
DECL|macro|REQ_TRK_IN_ERROR
mdefine_line|#define         REQ_TRK_IN_ERROR        0x1B    /* 3420 NOP, 3480 REJECT*/
DECL|macro|RESERVE
mdefine_line|#define         RESERVE                 0xF4    /* 3420 NOP, 3480 REJECT*/
DECL|macro|SENSE_GROUP_ID
mdefine_line|#define         SENSE_GROUP_ID          0x34    /* 3420 REJECT,3480 OK  */
DECL|macro|SENSE_ID
mdefine_line|#define         SENSE_ID                0xE4    /* 3420 REJECT,3480 OK */
DECL|macro|READ_DEV_CHAR
mdefine_line|#define         READ_DEV_CHAR           0x64    /* Read device characteristics */
DECL|macro|SET_DIAGNOSE
mdefine_line|#define         SET_DIAGNOSE            0x4B    /* 3420 NOP, 3480 REJECT*/
DECL|macro|SET_GROUP_ID
mdefine_line|#define         SET_GROUP_ID            0xAF    /* 3420 REJECT,3480 OK  */
DECL|macro|SET_TAPE_WRITE_IMMED
mdefine_line|#define         SET_TAPE_WRITE_IMMED    0xC3    /* for 3480                */
DECL|macro|SUSPEND
mdefine_line|#define         SUSPEND                 0x5B    /* 3420 REJ, 3480 NOP   */
DECL|macro|SYNC
mdefine_line|#define         SYNC                    0x43    /* Synchronize (flush buffer) */
DECL|macro|UNASSIGN
mdefine_line|#define         UNASSIGN                0xC7    /* 3420 REJECT,3480 OK  */
DECL|macro|PERF_SUBSYS_FUNC
mdefine_line|#define         PERF_SUBSYS_FUNC        0x77    /* 3490 CMD */
DECL|macro|READ_CONFIG_DATA
mdefine_line|#define         READ_CONFIG_DATA        0xFA    /* 3490 CMD */
DECL|macro|READ_MESSAGE_ID
mdefine_line|#define         READ_MESSAGE_ID         0x4E    /* 3490 CMD */
DECL|macro|READ_SUBSYS_DATA
mdefine_line|#define         READ_SUBSYS_DATA        0x3E    /* 3490 CMD */
DECL|macro|SET_INTERFACE_ID
mdefine_line|#define         SET_INTERFACE_ID        0x73    /* 3490 CMD */
DECL|macro|COMMAND_CHAIN
mdefine_line|#define COMMAND_CHAIN    CCW_FLAG_CC      /* redefine from irq.h */
DECL|macro|CHANNEL_END
mdefine_line|#define CHANNEL_END      DEV_STAT_CHN_END /* redefine from irq.h */
DECL|macro|DEVICE_END
mdefine_line|#define DEVICE_END       DEV_STAT_DEV_END /* redefine from irq.h */
DECL|macro|UNIT_CHECK
mdefine_line|#define UNIT_CHECK       DEV_STAT_UNIT_CHECK  /* redefine from irq.h */
DECL|macro|UNIT_EXCEPTION
mdefine_line|#define UNIT_EXCEPTION   DEV_STAT_UNIT_EXCEP  /* redefine from irq.h */
DECL|macro|CONTROL_UNIT_END
mdefine_line|#define CONTROL_UNIT_END DEV_STAT_CU_END      /* redefine from irq.h */
DECL|macro|INCORR_LEN
mdefine_line|#define INCORR_LEN       SCHN_STAT_INCORR_LEN /* redefine from irq.h */
DECL|macro|SENSE_COMMAND_REJECT
mdefine_line|#define SENSE_COMMAND_REJECT        0x80
DECL|macro|SENSE_INTERVENTION_REQUIRED
mdefine_line|#define SENSE_INTERVENTION_REQUIRED 0x40
DECL|macro|SENSE_BUS_OUT_CHECK
mdefine_line|#define SENSE_BUS_OUT_CHECK         0x20
DECL|macro|SENSE_EQUIPMENT_CHECK
mdefine_line|#define SENSE_EQUIPMENT_CHECK       0x10
DECL|macro|SENSE_DATA_CHECK
mdefine_line|#define SENSE_DATA_CHECK            0x08
DECL|macro|SENSE_OVERRUN
mdefine_line|#define SENSE_OVERRUN               0x04
DECL|macro|SENSE_DEFERRED_UNIT_CHECK
mdefine_line|#define SENSE_DEFERRED_UNIT_CHECK   0x02
DECL|macro|SENSE_ASSIGNED_ELSEWHERE
mdefine_line|#define SENSE_ASSIGNED_ELSEWHERE    0x01
DECL|macro|SENSE_LOCATE_FAILURE
mdefine_line|#define SENSE_LOCATE_FAILURE        0x80
DECL|macro|SENSE_DRIVE_ONLINE
mdefine_line|#define SENSE_DRIVE_ONLINE          0x40
DECL|macro|SENSE_RESERVED
mdefine_line|#define SENSE_RESERVED              0x20
DECL|macro|SENSE_RECORD_SEQUENCE_ERR
mdefine_line|#define SENSE_RECORD_SEQUENCE_ERR   0x10
DECL|macro|SENSE_BEGINNING_OF_TAPE
mdefine_line|#define SENSE_BEGINNING_OF_TAPE     0x08
DECL|macro|SENSE_WRITE_MODE
mdefine_line|#define SENSE_WRITE_MODE            0x04
DECL|macro|SENSE_WRITE_PROTECT
mdefine_line|#define SENSE_WRITE_PROTECT         0x02
DECL|macro|SENSE_NOT_CAPABLE
mdefine_line|#define SENSE_NOT_CAPABLE           0x01
DECL|macro|SENSE_CHANNEL_ADAPTER_CODE
mdefine_line|#define SENSE_CHANNEL_ADAPTER_CODE  0xE0
DECL|macro|SENSE_CHANNEL_ADAPTER_LOC
mdefine_line|#define SENSE_CHANNEL_ADAPTER_LOC   0x10
DECL|macro|SENSE_REPORTING_CU
mdefine_line|#define SENSE_REPORTING_CU          0x08
DECL|macro|SENSE_AUTOMATIC_LOADER
mdefine_line|#define SENSE_AUTOMATIC_LOADER      0x04
DECL|macro|SENSE_TAPE_SYNC_MODE
mdefine_line|#define SENSE_TAPE_SYNC_MODE        0x02
DECL|macro|SENSE_TAPE_POSITIONING
mdefine_line|#define SENSE_TAPE_POSITIONING      0x01
DECL|struct|_tape34xx_disc_data_t
r_typedef
r_struct
id|_tape34xx_disc_data_t
(brace
DECL|member|modeset_byte
id|__u8
id|modeset_byte
suffix:semicolon
DECL|typedef|tape34xx_disc_data_t
)brace
id|tape34xx_disc_data_t
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
DECL|macro|MOD_BYTE
mdefine_line|#define MOD_BYTE ((tape34xx_disc_data_t *)td-&gt;discdata)-&gt;modeset_byte
multiline_comment|/* discipline functions */
r_int
id|tape34xx_ioctl_overload
(paren
id|tape_dev_t
op_star
id|td
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
id|tape_ccw_req_t
op_star
id|tape34xx_write_block
(paren
r_const
r_char
op_star
id|data
comma
r_int
id|count
comma
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
id|tape_ccw_req_t
op_star
id|tape34xx_read_block
(paren
r_const
r_char
op_star
id|data
comma
r_int
id|count
comma
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
id|tape_ccw_req_t
op_star
id|tape34xx_ioctl
c_func
(paren
id|tape_dev_t
op_star
id|td
comma
r_int
id|op
comma
r_int
id|count
comma
r_int
op_star
id|rc
)paren
suffix:semicolon
id|tape_ccw_req_t
op_star
id|tape34xx_bread
(paren
r_struct
id|request
op_star
id|req
comma
id|tape_dev_t
op_star
id|td
comma
r_int
id|tapeblock_major
)paren
suffix:semicolon
r_void
id|tape34xx_free_bread
(paren
id|tape_ccw_req_t
op_star
id|treq
)paren
suffix:semicolon
r_void
id|tape34xx_bread_enable_locate
(paren
id|tape_ccw_req_t
op_star
id|treq
)paren
suffix:semicolon
id|tape_ccw_req_t
op_star
id|tape34xx_bwrite
(paren
r_struct
id|request
op_star
id|req
comma
id|tape_dev_t
op_star
id|td
comma
r_int
id|tapeblock_major
)paren
suffix:semicolon
multiline_comment|/* Event handlers */
r_void
id|tape34xx_default_handler
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
r_void
id|tape34xx_unexpect_uchk_handler
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
r_void
id|tape34xx_irq
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
r_void
id|tape34xx_process_eov
c_func
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
singleline_comment|// the error recovery stuff:
r_void
id|tape34xx_error_recovery
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
r_void
id|tape34xx_error_recovery_has_failed
(paren
id|tape_dev_t
op_star
id|td
comma
r_int
id|error_id
)paren
suffix:semicolon
r_void
id|tape34xx_error_recovery_succeded
c_func
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
r_void
id|tape34xx_error_recovery_do_retry
c_func
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
r_void
id|tape34xx_error_recovery_read_opposite
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
r_void
id|tape34xx_error_recovery_HWBUG
(paren
id|tape_dev_t
op_star
id|td
comma
r_int
id|condno
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// _TAPE34XX_H
eof
