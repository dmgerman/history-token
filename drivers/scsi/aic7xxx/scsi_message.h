multiline_comment|/*&n; * This file is in the public domain.&n; * $FreeBSD: src/sys/cam/scsi/scsi_message.h,v 1.2 2000/05/01 20:21:29 peter Exp $&n; */
multiline_comment|/* Messages (1 byte) */
multiline_comment|/* I/T (M)andatory or (O)ptional */
DECL|macro|MSG_CMDCOMPLETE
mdefine_line|#define MSG_CMDCOMPLETE&t;&t;0x00 /* M/M */
DECL|macro|MSG_TASK_COMPLETE
mdefine_line|#define MSG_TASK_COMPLETE&t;0x00 /* M/M */ /* SPI3 Terminology */
DECL|macro|MSG_EXTENDED
mdefine_line|#define MSG_EXTENDED&t;&t;0x01 /* O/O */
DECL|macro|MSG_SAVEDATAPOINTER
mdefine_line|#define MSG_SAVEDATAPOINTER&t;0x02 /* O/O */
DECL|macro|MSG_RESTOREPOINTERS
mdefine_line|#define MSG_RESTOREPOINTERS&t;0x03 /* O/O */
DECL|macro|MSG_DISCONNECT
mdefine_line|#define MSG_DISCONNECT&t;&t;0x04 /* O/O */
DECL|macro|MSG_INITIATOR_DET_ERR
mdefine_line|#define MSG_INITIATOR_DET_ERR&t;0x05 /* M/M */
DECL|macro|MSG_ABORT
mdefine_line|#define MSG_ABORT&t;&t;0x06 /* O/M */
DECL|macro|MSG_ABORT_TASK_SET
mdefine_line|#define MSG_ABORT_TASK_SET&t;0x06 /* O/M */ /* SPI3 Terminology */
DECL|macro|MSG_MESSAGE_REJECT
mdefine_line|#define MSG_MESSAGE_REJECT&t;0x07 /* M/M */
DECL|macro|MSG_NOOP
mdefine_line|#define MSG_NOOP&t;&t;0x08 /* M/M */
DECL|macro|MSG_PARITY_ERROR
mdefine_line|#define MSG_PARITY_ERROR&t;0x09 /* M/M */
DECL|macro|MSG_LINK_CMD_COMPLETE
mdefine_line|#define MSG_LINK_CMD_COMPLETE&t;0x0a /* O/O */
DECL|macro|MSG_LINK_CMD_COMPLETEF
mdefine_line|#define MSG_LINK_CMD_COMPLETEF&t;0x0b /* O/O */
DECL|macro|MSG_BUS_DEV_RESET
mdefine_line|#define MSG_BUS_DEV_RESET&t;0x0c /* O/M */
DECL|macro|MSG_TARGET_RESET
mdefine_line|#define MSG_TARGET_RESET&t;0x0c /* O/M */ /* SPI3 Terminology */
DECL|macro|MSG_ABORT_TAG
mdefine_line|#define MSG_ABORT_TAG&t;&t;0x0d /* O/O */
DECL|macro|MSG_ABORT_TASK
mdefine_line|#define MSG_ABORT_TASK&t;&t;0x0d /* O/O */ /* SPI3 Terminology */
DECL|macro|MSG_CLEAR_QUEUE
mdefine_line|#define MSG_CLEAR_QUEUE&t;&t;0x0e /* O/O */
DECL|macro|MSG_CLEAR_TASK_SET
mdefine_line|#define MSG_CLEAR_TASK_SET&t;0x0e /* O/O */ /* SPI3 Terminology */
DECL|macro|MSG_INIT_RECOVERY
mdefine_line|#define MSG_INIT_RECOVERY&t;0x0f /* O/O */ /* Deprecated in SPI3 */
DECL|macro|MSG_REL_RECOVERY
mdefine_line|#define MSG_REL_RECOVERY&t;0x10 /* O/O */ /* Deprecated in SPI3 */
DECL|macro|MSG_TERM_IO_PROC
mdefine_line|#define MSG_TERM_IO_PROC&t;0x11 /* O/O */ /* Deprecated in SPI3 */
DECL|macro|MSG_CLEAR_ACA
mdefine_line|#define MSG_CLEAR_ACA&t;&t;0x16 /* O/O */ /* SPI3 */
DECL|macro|MSG_LOGICAL_UNIT_RESET
mdefine_line|#define MSG_LOGICAL_UNIT_RESET&t;0x17 /* O/O */ /* SPI3 */
DECL|macro|MSG_QAS_REQUEST
mdefine_line|#define MSG_QAS_REQUEST&t;&t;0x55 /* O/O */ /* SPI3 */
multiline_comment|/* Messages (2 byte) */
DECL|macro|MSG_SIMPLE_Q_TAG
mdefine_line|#define MSG_SIMPLE_Q_TAG&t;0x20 /* O/O */
DECL|macro|MSG_SIMPLE_TASK
mdefine_line|#define MSG_SIMPLE_TASK&t;&t;0x20 /* O/O */ /* SPI3 Terminology */
DECL|macro|MSG_HEAD_OF_Q_TAG
mdefine_line|#define MSG_HEAD_OF_Q_TAG&t;0x21 /* O/O */
DECL|macro|MSG_HEAD_OF_QUEUE_TASK
mdefine_line|#define MSG_HEAD_OF_QUEUE_TASK&t;0x21 /* O/O */ /* SPI3 Terminology */
DECL|macro|MSG_ORDERED_Q_TAG
mdefine_line|#define MSG_ORDERED_Q_TAG&t;0x22 /* O/O */
DECL|macro|MSG_ORDERED_TASK
mdefine_line|#define MSG_ORDERED_TASK&t;0x22 /* O/O */ /* SPI3 Terminology */
DECL|macro|MSG_IGN_WIDE_RESIDUE
mdefine_line|#define MSG_IGN_WIDE_RESIDUE&t;0x23 /* O/O */
DECL|macro|MSG_ACA_TASK
mdefine_line|#define MSG_ACA_TASK&t;&t;0x24 /* 0/0 */ /* SPI3 */
multiline_comment|/* Identify message */
multiline_comment|/* M/M */
DECL|macro|MSG_IDENTIFYFLAG
mdefine_line|#define MSG_IDENTIFYFLAG&t;0x80 
DECL|macro|MSG_IDENTIFY_DISCFLAG
mdefine_line|#define MSG_IDENTIFY_DISCFLAG&t;0x40 
DECL|macro|MSG_IDENTIFY
mdefine_line|#define MSG_IDENTIFY(lun, disc)&t;(((disc) ? 0xc0 : MSG_IDENTIFYFLAG) | (lun))
DECL|macro|MSG_ISIDENTIFY
mdefine_line|#define MSG_ISIDENTIFY(m)&t;((m) &amp; MSG_IDENTIFYFLAG)
DECL|macro|MSG_IDENTIFY_LUNMASK
mdefine_line|#define MSG_IDENTIFY_LUNMASK&t;0x03F 
multiline_comment|/* Extended messages (opcode and length) */
DECL|macro|MSG_EXT_SDTR
mdefine_line|#define MSG_EXT_SDTR&t;&t;0x01
DECL|macro|MSG_EXT_SDTR_LEN
mdefine_line|#define MSG_EXT_SDTR_LEN&t;0x03
DECL|macro|MSG_EXT_WDTR
mdefine_line|#define MSG_EXT_WDTR&t;&t;0x03
DECL|macro|MSG_EXT_WDTR_LEN
mdefine_line|#define MSG_EXT_WDTR_LEN&t;0x02
DECL|macro|MSG_EXT_WDTR_BUS_8_BIT
mdefine_line|#define MSG_EXT_WDTR_BUS_8_BIT&t;0x00
DECL|macro|MSG_EXT_WDTR_BUS_16_BIT
mdefine_line|#define MSG_EXT_WDTR_BUS_16_BIT&t;0x01
DECL|macro|MSG_EXT_WDTR_BUS_32_BIT
mdefine_line|#define MSG_EXT_WDTR_BUS_32_BIT&t;0x02 /* Deprecated in SPI3 */
DECL|macro|MSG_EXT_PPR
mdefine_line|#define MSG_EXT_PPR&t;&t;0x04 /* SPI3 */
DECL|macro|MSG_EXT_PPR_LEN
mdefine_line|#define MSG_EXT_PPR_LEN&t;&t;0x06
DECL|macro|MSG_EXT_PPR_QAS_REQ
mdefine_line|#define MSG_EXT_PPR_QAS_REQ&t;0x04
DECL|macro|MSG_EXT_PPR_DT_REQ
mdefine_line|#define MSG_EXT_PPR_DT_REQ&t;0x02
DECL|macro|MSG_EXT_PPR_IU_REQ
mdefine_line|#define MSG_EXT_PPR_IU_REQ&t;0x01
eof
