multiline_comment|/*&n; * This header file contains public constants and structures used by&n; * the scsi code for linux.&n; *&n; * For documentation on the OPCODES, MESSAGES, and SENSE values,&n; * please consult the SCSI standard.&n; */
macro_line|#ifndef _SCSI_SCSI_H
DECL|macro|_SCSI_SCSI_H
mdefine_line|#define _SCSI_SCSI_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; *&t;The maximum sg list length SCSI can cope with&n; *&t;(currently must be a power of 2 between 32 and 256)&n; */
DECL|macro|SCSI_MAX_PHYS_SEGMENTS
mdefine_line|#define SCSI_MAX_PHYS_SEGMENTS&t;MAX_PHYS_SEGMENTS
multiline_comment|/*&n; *&t;SCSI command lengths&n; */
r_extern
r_const
r_int
r_char
id|scsi_command_size
(braket
l_int|8
)braket
suffix:semicolon
DECL|macro|COMMAND_SIZE
mdefine_line|#define COMMAND_SIZE(opcode) scsi_command_size[((opcode) &gt;&gt; 5) &amp; 7]
multiline_comment|/*&n; *&t;SCSI device types&n; */
DECL|macro|MAX_SCSI_DEVICE_CODE
mdefine_line|#define MAX_SCSI_DEVICE_CODE 14
r_extern
r_const
r_char
op_star
r_const
id|scsi_device_types
(braket
id|MAX_SCSI_DEVICE_CODE
)braket
suffix:semicolon
multiline_comment|/*&n; *      SCSI opcodes&n; */
DECL|macro|TEST_UNIT_READY
mdefine_line|#define TEST_UNIT_READY       0x00
DECL|macro|REZERO_UNIT
mdefine_line|#define REZERO_UNIT           0x01
DECL|macro|REQUEST_SENSE
mdefine_line|#define REQUEST_SENSE         0x03
DECL|macro|FORMAT_UNIT
mdefine_line|#define FORMAT_UNIT           0x04
DECL|macro|READ_BLOCK_LIMITS
mdefine_line|#define READ_BLOCK_LIMITS     0x05
DECL|macro|REASSIGN_BLOCKS
mdefine_line|#define REASSIGN_BLOCKS       0x07
DECL|macro|READ_6
mdefine_line|#define READ_6                0x08
DECL|macro|WRITE_6
mdefine_line|#define WRITE_6               0x0a
DECL|macro|SEEK_6
mdefine_line|#define SEEK_6                0x0b
DECL|macro|READ_REVERSE
mdefine_line|#define READ_REVERSE          0x0f
DECL|macro|WRITE_FILEMARKS
mdefine_line|#define WRITE_FILEMARKS       0x10
DECL|macro|SPACE
mdefine_line|#define SPACE                 0x11
DECL|macro|INQUIRY
mdefine_line|#define INQUIRY               0x12
DECL|macro|RECOVER_BUFFERED_DATA
mdefine_line|#define RECOVER_BUFFERED_DATA 0x14
DECL|macro|MODE_SELECT
mdefine_line|#define MODE_SELECT           0x15
DECL|macro|RESERVE
mdefine_line|#define RESERVE               0x16
DECL|macro|RELEASE
mdefine_line|#define RELEASE               0x17
DECL|macro|COPY
mdefine_line|#define COPY                  0x18
DECL|macro|ERASE
mdefine_line|#define ERASE                 0x19
DECL|macro|MODE_SENSE
mdefine_line|#define MODE_SENSE            0x1a
DECL|macro|START_STOP
mdefine_line|#define START_STOP            0x1b
DECL|macro|RECEIVE_DIAGNOSTIC
mdefine_line|#define RECEIVE_DIAGNOSTIC    0x1c
DECL|macro|SEND_DIAGNOSTIC
mdefine_line|#define SEND_DIAGNOSTIC       0x1d
DECL|macro|ALLOW_MEDIUM_REMOVAL
mdefine_line|#define ALLOW_MEDIUM_REMOVAL  0x1e
DECL|macro|SET_WINDOW
mdefine_line|#define SET_WINDOW            0x24
DECL|macro|READ_CAPACITY
mdefine_line|#define READ_CAPACITY         0x25
DECL|macro|READ_10
mdefine_line|#define READ_10               0x28
DECL|macro|WRITE_10
mdefine_line|#define WRITE_10              0x2a
DECL|macro|SEEK_10
mdefine_line|#define SEEK_10               0x2b
DECL|macro|WRITE_VERIFY
mdefine_line|#define WRITE_VERIFY          0x2e
DECL|macro|VERIFY
mdefine_line|#define VERIFY                0x2f
DECL|macro|SEARCH_HIGH
mdefine_line|#define SEARCH_HIGH           0x30
DECL|macro|SEARCH_EQUAL
mdefine_line|#define SEARCH_EQUAL          0x31
DECL|macro|SEARCH_LOW
mdefine_line|#define SEARCH_LOW            0x32
DECL|macro|SET_LIMITS
mdefine_line|#define SET_LIMITS            0x33
DECL|macro|PRE_FETCH
mdefine_line|#define PRE_FETCH             0x34
DECL|macro|READ_POSITION
mdefine_line|#define READ_POSITION         0x34
DECL|macro|SYNCHRONIZE_CACHE
mdefine_line|#define SYNCHRONIZE_CACHE     0x35
DECL|macro|LOCK_UNLOCK_CACHE
mdefine_line|#define LOCK_UNLOCK_CACHE     0x36
DECL|macro|READ_DEFECT_DATA
mdefine_line|#define READ_DEFECT_DATA      0x37
DECL|macro|MEDIUM_SCAN
mdefine_line|#define MEDIUM_SCAN           0x38
DECL|macro|COMPARE
mdefine_line|#define COMPARE               0x39
DECL|macro|COPY_VERIFY
mdefine_line|#define COPY_VERIFY           0x3a
DECL|macro|WRITE_BUFFER
mdefine_line|#define WRITE_BUFFER          0x3b
DECL|macro|READ_BUFFER
mdefine_line|#define READ_BUFFER           0x3c
DECL|macro|UPDATE_BLOCK
mdefine_line|#define UPDATE_BLOCK          0x3d
DECL|macro|READ_LONG
mdefine_line|#define READ_LONG             0x3e
DECL|macro|WRITE_LONG
mdefine_line|#define WRITE_LONG            0x3f
DECL|macro|CHANGE_DEFINITION
mdefine_line|#define CHANGE_DEFINITION     0x40
DECL|macro|WRITE_SAME
mdefine_line|#define WRITE_SAME            0x41
DECL|macro|READ_TOC
mdefine_line|#define READ_TOC              0x43
DECL|macro|LOG_SELECT
mdefine_line|#define LOG_SELECT            0x4c
DECL|macro|LOG_SENSE
mdefine_line|#define LOG_SENSE             0x4d
DECL|macro|MODE_SELECT_10
mdefine_line|#define MODE_SELECT_10        0x55
DECL|macro|RESERVE_10
mdefine_line|#define RESERVE_10            0x56
DECL|macro|RELEASE_10
mdefine_line|#define RELEASE_10            0x57
DECL|macro|MODE_SENSE_10
mdefine_line|#define MODE_SENSE_10         0x5a
DECL|macro|PERSISTENT_RESERVE_IN
mdefine_line|#define PERSISTENT_RESERVE_IN 0x5e
DECL|macro|PERSISTENT_RESERVE_OUT
mdefine_line|#define PERSISTENT_RESERVE_OUT 0x5f
DECL|macro|REPORT_LUNS
mdefine_line|#define REPORT_LUNS           0xa0
DECL|macro|MOVE_MEDIUM
mdefine_line|#define MOVE_MEDIUM           0xa5
DECL|macro|READ_12
mdefine_line|#define READ_12               0xa8
DECL|macro|WRITE_12
mdefine_line|#define WRITE_12              0xaa
DECL|macro|WRITE_VERIFY_12
mdefine_line|#define WRITE_VERIFY_12       0xae
DECL|macro|SEARCH_HIGH_12
mdefine_line|#define SEARCH_HIGH_12        0xb0
DECL|macro|SEARCH_EQUAL_12
mdefine_line|#define SEARCH_EQUAL_12       0xb1
DECL|macro|SEARCH_LOW_12
mdefine_line|#define SEARCH_LOW_12         0xb2
DECL|macro|READ_ELEMENT_STATUS
mdefine_line|#define READ_ELEMENT_STATUS   0xb8
DECL|macro|SEND_VOLUME_TAG
mdefine_line|#define SEND_VOLUME_TAG       0xb6
DECL|macro|WRITE_LONG_2
mdefine_line|#define WRITE_LONG_2          0xea
DECL|macro|READ_16
mdefine_line|#define READ_16               0x88
DECL|macro|WRITE_16
mdefine_line|#define WRITE_16              0x8a
DECL|macro|VERIFY_16
mdefine_line|#define VERIFY_16&t;      0x8f
DECL|macro|SERVICE_ACTION_IN
mdefine_line|#define SERVICE_ACTION_IN     0x9e
multiline_comment|/* values for service action in */
DECL|macro|SAI_READ_CAPACITY_16
mdefine_line|#define&t;SAI_READ_CAPACITY_16  0x10
multiline_comment|/*&n; *  SCSI Architecture Model (SAM) Status codes. Taken from SAM-3 draft&n; *  T10/1561-D Revision 4 Draft dated 7th November 2002.&n; */
DECL|macro|SAM_STAT_GOOD
mdefine_line|#define SAM_STAT_GOOD            0x00
DECL|macro|SAM_STAT_CHECK_CONDITION
mdefine_line|#define SAM_STAT_CHECK_CONDITION 0x02
DECL|macro|SAM_STAT_CONDITION_MET
mdefine_line|#define SAM_STAT_CONDITION_MET   0x04
DECL|macro|SAM_STAT_BUSY
mdefine_line|#define SAM_STAT_BUSY            0x08
DECL|macro|SAM_STAT_INTERMEDIATE
mdefine_line|#define SAM_STAT_INTERMEDIATE    0x10
DECL|macro|SAM_STAT_INTERMEDIATE_CONDITION_MET
mdefine_line|#define SAM_STAT_INTERMEDIATE_CONDITION_MET 0x14
DECL|macro|SAM_STAT_RESERVATION_CONFLICT
mdefine_line|#define SAM_STAT_RESERVATION_CONFLICT 0x18
DECL|macro|SAM_STAT_COMMAND_TERMINATED
mdefine_line|#define SAM_STAT_COMMAND_TERMINATED 0x22&t;/* obsolete in SAM-3 */
DECL|macro|SAM_STAT_TASK_SET_FULL
mdefine_line|#define SAM_STAT_TASK_SET_FULL   0x28
DECL|macro|SAM_STAT_ACA_ACTIVE
mdefine_line|#define SAM_STAT_ACA_ACTIVE      0x30
DECL|macro|SAM_STAT_TASK_ABORTED
mdefine_line|#define SAM_STAT_TASK_ABORTED    0x40
multiline_comment|/** scsi_status_is_good - check the status return.&n; *&n; * @status: the status passed up from the driver (including host and&n; *          driver components)&n; *&n; * This returns true for known good conditions that may be treated as&n; * command completed normally&n; */
DECL|function|scsi_status_is_good
r_static
r_inline
r_int
id|scsi_status_is_good
c_func
(paren
r_int
id|status
)paren
(brace
multiline_comment|/*&n;&t; * FIXME: bit0 is listed as reserved in SCSI-2, but is&n;&t; * significant in SCSI-3.  For now, we follow the SCSI-2&n;&t; * behaviour and ignore reserved bits.&n;&t; */
id|status
op_and_assign
l_int|0xfe
suffix:semicolon
r_return
(paren
(paren
id|status
op_eq
id|SAM_STAT_GOOD
)paren
op_logical_or
(paren
id|status
op_eq
id|SAM_STAT_INTERMEDIATE
)paren
op_logical_or
(paren
id|status
op_eq
id|SAM_STAT_INTERMEDIATE_CONDITION_MET
)paren
op_logical_or
multiline_comment|/* FIXME: this is obsolete in SAM-3 */
(paren
id|status
op_eq
id|SAM_STAT_COMMAND_TERMINATED
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Status codes. These are deprecated as they are shifted 1 bit right&n; *  from those found in the SCSI standards. This causes confusion for&n; *  applications that are ported to several OSes. Prefer SAM Status codes&n; *  above.&n; */
DECL|macro|GOOD
mdefine_line|#define GOOD                 0x00
DECL|macro|CHECK_CONDITION
mdefine_line|#define CHECK_CONDITION      0x01
DECL|macro|CONDITION_GOOD
mdefine_line|#define CONDITION_GOOD       0x02
DECL|macro|BUSY
mdefine_line|#define BUSY                 0x04
DECL|macro|INTERMEDIATE_GOOD
mdefine_line|#define INTERMEDIATE_GOOD    0x08
DECL|macro|INTERMEDIATE_C_GOOD
mdefine_line|#define INTERMEDIATE_C_GOOD  0x0a
DECL|macro|RESERVATION_CONFLICT
mdefine_line|#define RESERVATION_CONFLICT 0x0c
DECL|macro|COMMAND_TERMINATED
mdefine_line|#define COMMAND_TERMINATED   0x11
DECL|macro|QUEUE_FULL
mdefine_line|#define QUEUE_FULL           0x14
DECL|macro|STATUS_MASK
mdefine_line|#define STATUS_MASK          0x3e
multiline_comment|/*&n; *  SENSE KEYS&n; */
DECL|macro|NO_SENSE
mdefine_line|#define NO_SENSE            0x00
DECL|macro|RECOVERED_ERROR
mdefine_line|#define RECOVERED_ERROR     0x01
DECL|macro|NOT_READY
mdefine_line|#define NOT_READY           0x02
DECL|macro|MEDIUM_ERROR
mdefine_line|#define MEDIUM_ERROR        0x03
DECL|macro|HARDWARE_ERROR
mdefine_line|#define HARDWARE_ERROR      0x04
DECL|macro|ILLEGAL_REQUEST
mdefine_line|#define ILLEGAL_REQUEST     0x05
DECL|macro|UNIT_ATTENTION
mdefine_line|#define UNIT_ATTENTION      0x06
DECL|macro|DATA_PROTECT
mdefine_line|#define DATA_PROTECT        0x07
DECL|macro|BLANK_CHECK
mdefine_line|#define BLANK_CHECK         0x08
DECL|macro|COPY_ABORTED
mdefine_line|#define COPY_ABORTED        0x0a
DECL|macro|ABORTED_COMMAND
mdefine_line|#define ABORTED_COMMAND     0x0b
DECL|macro|VOLUME_OVERFLOW
mdefine_line|#define VOLUME_OVERFLOW     0x0d
DECL|macro|MISCOMPARE
mdefine_line|#define MISCOMPARE          0x0e
multiline_comment|/*&n; *  DEVICE TYPES&n; */
DECL|macro|TYPE_DISK
mdefine_line|#define TYPE_DISK           0x00
DECL|macro|TYPE_TAPE
mdefine_line|#define TYPE_TAPE           0x01
DECL|macro|TYPE_PRINTER
mdefine_line|#define TYPE_PRINTER        0x02
DECL|macro|TYPE_PROCESSOR
mdefine_line|#define TYPE_PROCESSOR      0x03    /* HP scanners use this */
DECL|macro|TYPE_WORM
mdefine_line|#define TYPE_WORM           0x04    /* Treated as ROM by our system */
DECL|macro|TYPE_ROM
mdefine_line|#define TYPE_ROM            0x05
DECL|macro|TYPE_SCANNER
mdefine_line|#define TYPE_SCANNER        0x06
DECL|macro|TYPE_MOD
mdefine_line|#define TYPE_MOD            0x07    /* Magneto-optical disk - &n;&t;&t;&t;&t;     * - treated as TYPE_DISK */
DECL|macro|TYPE_MEDIUM_CHANGER
mdefine_line|#define TYPE_MEDIUM_CHANGER 0x08
DECL|macro|TYPE_COMM
mdefine_line|#define TYPE_COMM           0x09    /* Communications device */
DECL|macro|TYPE_ENCLOSURE
mdefine_line|#define TYPE_ENCLOSURE      0x0d    /* Enclosure Services Device */
DECL|macro|TYPE_RAID
mdefine_line|#define TYPE_RAID           0x0c
DECL|macro|TYPE_NO_LUN
mdefine_line|#define TYPE_NO_LUN         0x7f
multiline_comment|/*&n; * standard mode-select header prepended to all mode-select commands&n; */
DECL|struct|ccs_modesel_head
r_struct
id|ccs_modesel_head
(brace
DECL|member|_r1
id|__u8
id|_r1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|medium
id|__u8
id|medium
suffix:semicolon
multiline_comment|/* device-specific medium type */
DECL|member|_r2
id|__u8
id|_r2
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|block_desc_length
id|__u8
id|block_desc_length
suffix:semicolon
multiline_comment|/* block descriptor length */
DECL|member|density
id|__u8
id|density
suffix:semicolon
multiline_comment|/* device-specific density code */
DECL|member|number_blocks_hi
id|__u8
id|number_blocks_hi
suffix:semicolon
multiline_comment|/* number of blocks in this block desc */
DECL|member|number_blocks_med
id|__u8
id|number_blocks_med
suffix:semicolon
DECL|member|number_blocks_lo
id|__u8
id|number_blocks_lo
suffix:semicolon
DECL|member|_r3
id|__u8
id|_r3
suffix:semicolon
DECL|member|block_length_hi
id|__u8
id|block_length_hi
suffix:semicolon
multiline_comment|/* block length for blocks in this desc */
DECL|member|block_length_med
id|__u8
id|block_length_med
suffix:semicolon
DECL|member|block_length_lo
id|__u8
id|block_length_lo
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ScsiLun: 8 byte LUN.&n; */
DECL|struct|scsi_lun
r_struct
id|scsi_lun
(brace
DECL|member|scsi_lun
id|__u8
id|scsi_lun
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  MESSAGE CODES&n; */
DECL|macro|COMMAND_COMPLETE
mdefine_line|#define COMMAND_COMPLETE    0x00
DECL|macro|EXTENDED_MESSAGE
mdefine_line|#define EXTENDED_MESSAGE    0x01
DECL|macro|EXTENDED_MODIFY_DATA_POINTER
mdefine_line|#define     EXTENDED_MODIFY_DATA_POINTER    0x00
DECL|macro|EXTENDED_SDTR
mdefine_line|#define     EXTENDED_SDTR                   0x01
DECL|macro|EXTENDED_EXTENDED_IDENTIFY
mdefine_line|#define     EXTENDED_EXTENDED_IDENTIFY      0x02    /* SCSI-I only */
DECL|macro|EXTENDED_WDTR
mdefine_line|#define     EXTENDED_WDTR                   0x03
DECL|macro|EXTENDED_PPR
mdefine_line|#define     EXTENDED_PPR                    0x04
DECL|macro|EXTENDED_MODIFY_BIDI_DATA_PTR
mdefine_line|#define     EXTENDED_MODIFY_BIDI_DATA_PTR   0x05
DECL|macro|SAVE_POINTERS
mdefine_line|#define SAVE_POINTERS       0x02
DECL|macro|RESTORE_POINTERS
mdefine_line|#define RESTORE_POINTERS    0x03
DECL|macro|DISCONNECT
mdefine_line|#define DISCONNECT          0x04
DECL|macro|INITIATOR_ERROR
mdefine_line|#define INITIATOR_ERROR     0x05
DECL|macro|ABORT_TASK_SET
mdefine_line|#define ABORT_TASK_SET      0x06
DECL|macro|MESSAGE_REJECT
mdefine_line|#define MESSAGE_REJECT      0x07
DECL|macro|NOP
mdefine_line|#define NOP                 0x08
DECL|macro|MSG_PARITY_ERROR
mdefine_line|#define MSG_PARITY_ERROR    0x09
DECL|macro|LINKED_CMD_COMPLETE
mdefine_line|#define LINKED_CMD_COMPLETE 0x0a
DECL|macro|LINKED_FLG_CMD_COMPLETE
mdefine_line|#define LINKED_FLG_CMD_COMPLETE 0x0b
DECL|macro|TARGET_RESET
mdefine_line|#define TARGET_RESET        0x0c
DECL|macro|ABORT_TASK
mdefine_line|#define ABORT_TASK          0x0d
DECL|macro|CLEAR_TASK_SET
mdefine_line|#define CLEAR_TASK_SET      0x0e
DECL|macro|INITIATE_RECOVERY
mdefine_line|#define INITIATE_RECOVERY   0x0f            /* SCSI-II only */
DECL|macro|RELEASE_RECOVERY
mdefine_line|#define RELEASE_RECOVERY    0x10            /* SCSI-II only */
DECL|macro|CLEAR_ACA
mdefine_line|#define CLEAR_ACA           0x16
DECL|macro|LOGICAL_UNIT_RESET
mdefine_line|#define LOGICAL_UNIT_RESET  0x17
DECL|macro|SIMPLE_QUEUE_TAG
mdefine_line|#define SIMPLE_QUEUE_TAG    0x20
DECL|macro|HEAD_OF_QUEUE_TAG
mdefine_line|#define HEAD_OF_QUEUE_TAG   0x21
DECL|macro|ORDERED_QUEUE_TAG
mdefine_line|#define ORDERED_QUEUE_TAG   0x22
DECL|macro|IGNORE_WIDE_RESIDUE
mdefine_line|#define IGNORE_WIDE_RESIDUE 0x23
DECL|macro|ACA
mdefine_line|#define ACA                 0x24
DECL|macro|QAS_REQUEST
mdefine_line|#define QAS_REQUEST         0x55
DECL|macro|IDENTIFY
mdefine_line|#define IDENTIFY            0x80
multiline_comment|/* Old SCSI2 names, don&squot;t use in new code */
DECL|macro|BUS_DEVICE_RESET
mdefine_line|#define BUS_DEVICE_RESET    TARGET_RESET
DECL|macro|ABORT
mdefine_line|#define ABORT               ABORT_TASK_SET
multiline_comment|/*&n; * Host byte codes&n; */
DECL|macro|DID_OK
mdefine_line|#define DID_OK          0x00&t;/* NO error                                */
DECL|macro|DID_NO_CONNECT
mdefine_line|#define DID_NO_CONNECT  0x01&t;/* Couldn&squot;t connect before timeout period  */
DECL|macro|DID_BUS_BUSY
mdefine_line|#define DID_BUS_BUSY    0x02&t;/* BUS stayed busy through time out period */
DECL|macro|DID_TIME_OUT
mdefine_line|#define DID_TIME_OUT    0x03&t;/* TIMED OUT for other reason              */
DECL|macro|DID_BAD_TARGET
mdefine_line|#define DID_BAD_TARGET  0x04&t;/* BAD target.                             */
DECL|macro|DID_ABORT
mdefine_line|#define DID_ABORT       0x05&t;/* Told to abort for some other reason     */
DECL|macro|DID_PARITY
mdefine_line|#define DID_PARITY      0x06&t;/* Parity error                            */
DECL|macro|DID_ERROR
mdefine_line|#define DID_ERROR       0x07&t;/* Internal error                          */
DECL|macro|DID_RESET
mdefine_line|#define DID_RESET       0x08&t;/* Reset by somebody.                      */
DECL|macro|DID_BAD_INTR
mdefine_line|#define DID_BAD_INTR    0x09&t;/* Got an interrupt we weren&squot;t expecting.  */
DECL|macro|DID_PASSTHROUGH
mdefine_line|#define DID_PASSTHROUGH 0x0a&t;/* Force command past mid-layer            */
DECL|macro|DID_SOFT_ERROR
mdefine_line|#define DID_SOFT_ERROR  0x0b&t;/* The low level driver just wish a retry  */
DECL|macro|DID_IMM_RETRY
mdefine_line|#define DID_IMM_RETRY   0x0c&t;/* Retry without decrementing retry count  */
DECL|macro|DRIVER_OK
mdefine_line|#define DRIVER_OK       0x00&t;/* Driver status                           */
multiline_comment|/*&n; *  These indicate the error that occurred, and what is available.&n; */
DECL|macro|DRIVER_BUSY
mdefine_line|#define DRIVER_BUSY         0x01
DECL|macro|DRIVER_SOFT
mdefine_line|#define DRIVER_SOFT         0x02
DECL|macro|DRIVER_MEDIA
mdefine_line|#define DRIVER_MEDIA        0x03
DECL|macro|DRIVER_ERROR
mdefine_line|#define DRIVER_ERROR        0x04
DECL|macro|DRIVER_INVALID
mdefine_line|#define DRIVER_INVALID      0x05
DECL|macro|DRIVER_TIMEOUT
mdefine_line|#define DRIVER_TIMEOUT      0x06
DECL|macro|DRIVER_HARD
mdefine_line|#define DRIVER_HARD         0x07
DECL|macro|DRIVER_SENSE
mdefine_line|#define DRIVER_SENSE&t;    0x08
DECL|macro|SUGGEST_RETRY
mdefine_line|#define SUGGEST_RETRY       0x10
DECL|macro|SUGGEST_ABORT
mdefine_line|#define SUGGEST_ABORT       0x20
DECL|macro|SUGGEST_REMAP
mdefine_line|#define SUGGEST_REMAP       0x30
DECL|macro|SUGGEST_DIE
mdefine_line|#define SUGGEST_DIE         0x40
DECL|macro|SUGGEST_SENSE
mdefine_line|#define SUGGEST_SENSE       0x80
DECL|macro|SUGGEST_IS_OK
mdefine_line|#define SUGGEST_IS_OK       0xff
DECL|macro|DRIVER_MASK
mdefine_line|#define DRIVER_MASK         0x0f
DECL|macro|SUGGEST_MASK
mdefine_line|#define SUGGEST_MASK        0xf0
multiline_comment|/*&n; * Internal return values.&n; */
DECL|macro|NEEDS_RETRY
mdefine_line|#define NEEDS_RETRY     0x2001
DECL|macro|SUCCESS
mdefine_line|#define SUCCESS         0x2002
DECL|macro|FAILED
mdefine_line|#define FAILED          0x2003
DECL|macro|QUEUED
mdefine_line|#define QUEUED          0x2004
DECL|macro|SOFT_ERROR
mdefine_line|#define SOFT_ERROR      0x2005
DECL|macro|ADD_TO_MLQUEUE
mdefine_line|#define ADD_TO_MLQUEUE  0x2006
DECL|macro|TIMEOUT_ERROR
mdefine_line|#define TIMEOUT_ERROR   0x2007
multiline_comment|/*&n; * Midlevel queue return values.&n; */
DECL|macro|SCSI_MLQUEUE_HOST_BUSY
mdefine_line|#define SCSI_MLQUEUE_HOST_BUSY   0x1055
DECL|macro|SCSI_MLQUEUE_DEVICE_BUSY
mdefine_line|#define SCSI_MLQUEUE_DEVICE_BUSY 0x1056
DECL|macro|SCSI_MLQUEUE_EH_RETRY
mdefine_line|#define SCSI_MLQUEUE_EH_RETRY    0x1057
multiline_comment|/*&n; *  Use these to separate status msg and our bytes&n; *&n; *  These are set by:&n; *&n; *      status byte = set from target device&n; *      msg_byte    = return status from host adapter itself.&n; *      host_byte   = set by low-level driver to indicate status.&n; *      driver_byte = set by mid-level.&n; */
DECL|macro|status_byte
mdefine_line|#define status_byte(result) (((result) &gt;&gt; 1) &amp; 0x1f)
DECL|macro|msg_byte
mdefine_line|#define msg_byte(result)    (((result) &gt;&gt; 8) &amp; 0xff)
DECL|macro|host_byte
mdefine_line|#define host_byte(result)   (((result) &gt;&gt; 16) &amp; 0xff)
DECL|macro|driver_byte
mdefine_line|#define driver_byte(result) (((result) &gt;&gt; 24) &amp; 0xff)
DECL|macro|suggestion
mdefine_line|#define suggestion(result)  (driver_byte(result) &amp; SUGGEST_MASK)
DECL|macro|sense_class
mdefine_line|#define sense_class(sense)  (((sense) &gt;&gt; 4) &amp; 0x7)
DECL|macro|sense_error
mdefine_line|#define sense_error(sense)  ((sense) &amp; 0xf)
DECL|macro|sense_valid
mdefine_line|#define sense_valid(sense)  ((sense) &amp; 0x80);
DECL|macro|IDENTIFY_BASE
mdefine_line|#define IDENTIFY_BASE       0x80
DECL|macro|IDENTIFY
mdefine_line|#define IDENTIFY(can_disconnect, lun)   (IDENTIFY_BASE |&bslash;&n;&t;&t;     ((can_disconnect) ?  0x40 : 0) |&bslash;&n;&t;&t;     ((lun) &amp; 0x07))
multiline_comment|/*&n; *  struct scsi_device::scsi_level values. For SCSI devices other than those&n; *  prior to SCSI-2 (i.e. over 12 years old) this value is (resp[2] + 1)&n; *  where &quot;resp&quot; is a byte array of the response to an INQUIRY. The scsi_level&n; *  variable is visible to the user via sysfs.&n; */
DECL|macro|SCSI_UNKNOWN
mdefine_line|#define SCSI_UNKNOWN    0
DECL|macro|SCSI_1
mdefine_line|#define SCSI_1          1
DECL|macro|SCSI_1_CCS
mdefine_line|#define SCSI_1_CCS      2
DECL|macro|SCSI_2
mdefine_line|#define SCSI_2          3
DECL|macro|SCSI_3
mdefine_line|#define SCSI_3          4        /* SPC */
DECL|macro|SCSI_SPC_2
mdefine_line|#define SCSI_SPC_2      5
DECL|macro|SCSI_SPC_3
mdefine_line|#define SCSI_SPC_3      6
multiline_comment|/*&n; * INQ PERIPHERAL QUALIFIERS&n; */
DECL|macro|SCSI_INQ_PQ_CON
mdefine_line|#define SCSI_INQ_PQ_CON         0x00
DECL|macro|SCSI_INQ_PQ_NOT_CON
mdefine_line|#define SCSI_INQ_PQ_NOT_CON     0x01
DECL|macro|SCSI_INQ_PQ_NOT_CAP
mdefine_line|#define SCSI_INQ_PQ_NOT_CAP     0x03
multiline_comment|/*&n; * Here are some scsi specific ioctl commands which are sometimes useful.&n; *&n; * Note that include/linux/cdrom.h also defines IOCTL 0x5300 - 0x5395&n; */
multiline_comment|/* Used to obtain PUN and LUN info.  Conflicts with CDROMAUDIOBUFSIZ */
DECL|macro|SCSI_IOCTL_GET_IDLUN
mdefine_line|#define SCSI_IOCTL_GET_IDLUN&t;&t;0x5382
multiline_comment|/* 0x5383 and 0x5384 were used for SCSI_IOCTL_TAGGED_{ENABLE,DISABLE} */
multiline_comment|/* Used to obtain the host number of a device. */
DECL|macro|SCSI_IOCTL_PROBE_HOST
mdefine_line|#define SCSI_IOCTL_PROBE_HOST&t;&t;0x5385
multiline_comment|/* Used to obtain the bus number for a device */
DECL|macro|SCSI_IOCTL_GET_BUS_NUMBER
mdefine_line|#define SCSI_IOCTL_GET_BUS_NUMBER&t;0x5386
multiline_comment|/* Used to obtain the PCI location of a device */
DECL|macro|SCSI_IOCTL_GET_PCI
mdefine_line|#define SCSI_IOCTL_GET_PCI&t;&t;0x5387
macro_line|#endif /* _SCSI_SCSI_H */
eof
