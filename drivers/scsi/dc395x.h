multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;dc395x.h&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Device Driver for Tekram DC395(U/UW/F), DC315(U)&t;&t;*/
multiline_comment|/*&t;PCI SCSI Bus Master Host Adapter&t;&t;&t;&t;*/
multiline_comment|/*&t;(SCSI chip set used Tekram ASIC TRM-S1040)&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
macro_line|#ifndef DC395x_H
DECL|macro|DC395x_H
mdefine_line|#define DC395x_H
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Name, Banner and Version&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|DC395X_NAME
mdefine_line|#define DC395X_NAME&t;&t;&t;&quot;dc395x&quot;
DECL|macro|DC395X_BANNER
mdefine_line|#define DC395X_BANNER&t;&t;&t;&quot;Tekram DC395(U/UW/F), DC315(U) - ASIC TRM-S1040&quot;
DECL|macro|DC395X_VERSION
mdefine_line|#define DC395X_VERSION&t;&t;&t;&quot;v2.04, 2003/05/19&quot;
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Initial values&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|DC395x_MAX_CMD_QUEUE
mdefine_line|#define DC395x_MAX_CMD_QUEUE&t;&t;32
multiline_comment|/* #define DC395x_MAX_QTAGS&t;&t;32 */
DECL|macro|DC395x_MAX_QTAGS
mdefine_line|#define DC395x_MAX_QTAGS&t;&t;16
DECL|macro|DC395x_MAX_SCSI_ID
mdefine_line|#define DC395x_MAX_SCSI_ID&t;&t;16
DECL|macro|DC395x_MAX_CMD_PER_LUN
mdefine_line|#define DC395x_MAX_CMD_PER_LUN&t;&t;DC395x_MAX_QTAGS
DECL|macro|DC395x_MAX_SG_TABLESIZE
mdefine_line|#define DC395x_MAX_SG_TABLESIZE&t;&t;64&t;/* HW limitation&t;&t;&t;*/
DECL|macro|DC395x_MAX_SG_LISTENTRY
mdefine_line|#define DC395x_MAX_SG_LISTENTRY&t;&t;64&t;/* Must be equal or lower to previous&t;*/
multiline_comment|/* item&t;&t;&t;&t;&t;*/
DECL|macro|DC395x_MAX_SRB_CNT
mdefine_line|#define DC395x_MAX_SRB_CNT&t;&t;63
multiline_comment|/* #define DC395x_MAX_CAN_QUEUE&t;&t;7 * DC395x_MAX_QTAGS */
DECL|macro|DC395x_MAX_CAN_QUEUE
mdefine_line|#define DC395x_MAX_CAN_QUEUE&t;&t;DC395x_MAX_SRB_CNT
DECL|macro|DC395x_END_SCAN
mdefine_line|#define DC395x_END_SCAN&t;&t;&t;2
DECL|macro|DC395x_SEL_TIMEOUT
mdefine_line|#define DC395x_SEL_TIMEOUT&t;&t;153&t;/* 250 ms selection timeout (@ 40 MHz)&t;*/
DECL|macro|DC395x_MAX_RETRIES
mdefine_line|#define DC395x_MAX_RETRIES&t;&t;3
macro_line|#if 0
mdefine_line|#define SYNC_FIRST
macro_line|#endif
DECL|macro|NORM_REC_LVL
mdefine_line|#define NORM_REC_LVL&t;&t;&t;0
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Various definitions&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|BIT31
mdefine_line|#define BIT31&t;&t;&t;&t;0x80000000
DECL|macro|BIT30
mdefine_line|#define BIT30&t;&t;&t;&t;0x40000000
DECL|macro|BIT29
mdefine_line|#define BIT29&t;&t;&t;&t;0x20000000
DECL|macro|BIT28
mdefine_line|#define BIT28&t;&t;&t;&t;0x10000000
DECL|macro|BIT27
mdefine_line|#define BIT27&t;&t;&t;&t;0x08000000
DECL|macro|BIT26
mdefine_line|#define BIT26&t;&t;&t;&t;0x04000000
DECL|macro|BIT25
mdefine_line|#define BIT25&t;&t;&t;&t;0x02000000
DECL|macro|BIT24
mdefine_line|#define BIT24&t;&t;&t;&t;0x01000000
DECL|macro|BIT23
mdefine_line|#define BIT23&t;&t;&t;&t;0x00800000
DECL|macro|BIT22
mdefine_line|#define BIT22&t;&t;&t;&t;0x00400000
DECL|macro|BIT21
mdefine_line|#define BIT21&t;&t;&t;&t;0x00200000
DECL|macro|BIT20
mdefine_line|#define BIT20&t;&t;&t;&t;0x00100000
DECL|macro|BIT19
mdefine_line|#define BIT19&t;&t;&t;&t;0x00080000
DECL|macro|BIT18
mdefine_line|#define BIT18&t;&t;&t;&t;0x00040000
DECL|macro|BIT17
mdefine_line|#define BIT17&t;&t;&t;&t;0x00020000
DECL|macro|BIT16
mdefine_line|#define BIT16&t;&t;&t;&t;0x00010000
DECL|macro|BIT15
mdefine_line|#define BIT15&t;&t;&t;&t;0x00008000
DECL|macro|BIT14
mdefine_line|#define BIT14&t;&t;&t;&t;0x00004000
DECL|macro|BIT13
mdefine_line|#define BIT13&t;&t;&t;&t;0x00002000
DECL|macro|BIT12
mdefine_line|#define BIT12&t;&t;&t;&t;0x00001000
DECL|macro|BIT11
mdefine_line|#define BIT11&t;&t;&t;&t;0x00000800
DECL|macro|BIT10
mdefine_line|#define BIT10&t;&t;&t;&t;0x00000400
DECL|macro|BIT9
mdefine_line|#define BIT9&t;&t;&t;&t;0x00000200
DECL|macro|BIT8
mdefine_line|#define BIT8&t;&t;&t;&t;0x00000100
DECL|macro|BIT7
mdefine_line|#define BIT7&t;&t;&t;&t;0x00000080
DECL|macro|BIT6
mdefine_line|#define BIT6&t;&t;&t;&t;0x00000040
DECL|macro|BIT5
mdefine_line|#define BIT5&t;&t;&t;&t;0x00000020
DECL|macro|BIT4
mdefine_line|#define BIT4&t;&t;&t;&t;0x00000010
DECL|macro|BIT3
mdefine_line|#define BIT3&t;&t;&t;&t;0x00000008
DECL|macro|BIT2
mdefine_line|#define BIT2&t;&t;&t;&t;0x00000004
DECL|macro|BIT1
mdefine_line|#define BIT1&t;&t;&t;&t;0x00000002
DECL|macro|BIT0
mdefine_line|#define BIT0&t;&t;&t;&t;0x00000001
multiline_comment|/* UnitCtrlFlag */
DECL|macro|UNIT_ALLOCATED
mdefine_line|#define UNIT_ALLOCATED&t;&t;&t;BIT0
DECL|macro|UNIT_INFO_CHANGED
mdefine_line|#define UNIT_INFO_CHANGED&t;&t;BIT1
DECL|macro|FORMATING_MEDIA
mdefine_line|#define FORMATING_MEDIA&t;&t;&t;BIT2
DECL|macro|UNIT_RETRY
mdefine_line|#define UNIT_RETRY&t;&t;&t;BIT3
multiline_comment|/* UnitFlags */
DECL|macro|DASD_SUPPORT
mdefine_line|#define DASD_SUPPORT&t;&t;&t;BIT0
DECL|macro|SCSI_SUPPORT
mdefine_line|#define SCSI_SUPPORT&t;&t;&t;BIT1
DECL|macro|ASPI_SUPPORT
mdefine_line|#define ASPI_SUPPORT&t;&t;&t;BIT2
multiline_comment|/* SRBState machine definition */
DECL|macro|SRB_FREE
mdefine_line|#define SRB_FREE&t;&t;&t;0x0000
DECL|macro|SRB_WAIT
mdefine_line|#define SRB_WAIT&t;&t;&t;0x0001
DECL|macro|SRB_READY
mdefine_line|#define SRB_READY&t;&t;&t;0x0002
DECL|macro|SRB_MSGOUT
mdefine_line|#define SRB_MSGOUT&t;&t;&t;0x0004&t;/* arbitration+msg_out 1st byte&t;&t;*/
DECL|macro|SRB_MSGIN
mdefine_line|#define SRB_MSGIN&t;&t;&t;0x0008
DECL|macro|SRB_EXTEND_MSGIN
mdefine_line|#define SRB_EXTEND_MSGIN&t;&t;0x0010
DECL|macro|SRB_COMMAND
mdefine_line|#define SRB_COMMAND&t;&t;&t;0x0020
DECL|macro|SRB_START_
mdefine_line|#define SRB_START_&t;&t;&t;0x0040&t;/* arbitration+msg_out+command_out&t;*/
DECL|macro|SRB_DISCONNECT
mdefine_line|#define SRB_DISCONNECT&t;&t;&t;0x0080
DECL|macro|SRB_DATA_XFER
mdefine_line|#define SRB_DATA_XFER&t;&t;&t;0x0100
DECL|macro|SRB_XFERPAD
mdefine_line|#define SRB_XFERPAD&t;&t;&t;0x0200
DECL|macro|SRB_STATUS
mdefine_line|#define SRB_STATUS&t;&t;&t;0x0400
DECL|macro|SRB_COMPLETED
mdefine_line|#define SRB_COMPLETED&t;&t;&t;0x0800
DECL|macro|SRB_ABORT_SENT
mdefine_line|#define SRB_ABORT_SENT&t;&t;&t;0x1000
DECL|macro|SRB_DO_SYNC_NEGO
mdefine_line|#define SRB_DO_SYNC_NEGO&t;&t;0x2000
DECL|macro|SRB_DO_WIDE_NEGO
mdefine_line|#define SRB_DO_WIDE_NEGO&t;&t;0x4000
DECL|macro|SRB_UNEXPECT_RESEL
mdefine_line|#define SRB_UNEXPECT_RESEL&t;&t;0x8000
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;ACB Config&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|HCC_WIDE_CARD
mdefine_line|#define HCC_WIDE_CARD&t;&t;&t;0x20
DECL|macro|HCC_SCSI_RESET
mdefine_line|#define HCC_SCSI_RESET&t;&t;&t;0x10
DECL|macro|HCC_PARITY
mdefine_line|#define HCC_PARITY&t;&t;&t;0x08
DECL|macro|HCC_AUTOTERM
mdefine_line|#define HCC_AUTOTERM&t;&t;&t;0x04
DECL|macro|HCC_LOW8TERM
mdefine_line|#define HCC_LOW8TERM&t;&t;&t;0x02
DECL|macro|HCC_UP8TERM
mdefine_line|#define HCC_UP8TERM&t;&t;&t;0x01
multiline_comment|/* ACBFlag */
DECL|macro|RESET_DEV
mdefine_line|#define RESET_DEV&t;&t;&t;BIT0
DECL|macro|RESET_DETECT
mdefine_line|#define RESET_DETECT&t;&t;&t;BIT1
DECL|macro|RESET_DONE
mdefine_line|#define RESET_DONE&t;&t;&t;BIT2
multiline_comment|/* DCBFlag */
DECL|macro|ABORT_DEV_
mdefine_line|#define ABORT_DEV_&t;&t;&t;BIT0
multiline_comment|/* SRBstatus */
DECL|macro|SRB_OK
mdefine_line|#define SRB_OK&t;&t;&t;&t;BIT0
DECL|macro|ABORTION
mdefine_line|#define ABORTION&t;&t;&t;BIT1
DECL|macro|OVER_RUN
mdefine_line|#define OVER_RUN&t;&t;&t;BIT2
DECL|macro|UNDER_RUN
mdefine_line|#define UNDER_RUN&t;&t;&t;BIT3
DECL|macro|PARITY_ERROR
mdefine_line|#define PARITY_ERROR&t;&t;&t;BIT4
DECL|macro|SRB_ERROR
mdefine_line|#define SRB_ERROR&t;&t;&t;BIT5
multiline_comment|/* SRBFlag */
DECL|macro|DATAOUT
mdefine_line|#define DATAOUT&t;&t;&t;&t;BIT7
DECL|macro|DATAIN
mdefine_line|#define DATAIN&t;&t;&t;&t;BIT6
DECL|macro|RESIDUAL_VALID
mdefine_line|#define RESIDUAL_VALID&t;&t;&t;BIT5
DECL|macro|ENABLE_TIMER
mdefine_line|#define ENABLE_TIMER&t;&t;&t;BIT4
DECL|macro|RESET_DEV0
mdefine_line|#define RESET_DEV0&t;&t;&t;BIT2
DECL|macro|ABORT_DEV
mdefine_line|#define ABORT_DEV&t;&t;&t;BIT1
DECL|macro|AUTO_REQSENSE
mdefine_line|#define AUTO_REQSENSE&t;&t;&t;BIT0
multiline_comment|/* Adapter status */
DECL|macro|H_STATUS_GOOD
mdefine_line|#define H_STATUS_GOOD&t;&t;&t;0
DECL|macro|H_SEL_TIMEOUT
mdefine_line|#define H_SEL_TIMEOUT&t;&t;&t;0x11
DECL|macro|H_OVER_UNDER_RUN
mdefine_line|#define H_OVER_UNDER_RUN&t;&t;0x12
DECL|macro|H_UNEXP_BUS_FREE
mdefine_line|#define H_UNEXP_BUS_FREE&t;&t;0x13
DECL|macro|H_TARGET_PHASE_F
mdefine_line|#define H_TARGET_PHASE_F&t;&t;0x14
DECL|macro|H_INVALID_CCB_OP
mdefine_line|#define H_INVALID_CCB_OP&t;&t;0x16
DECL|macro|H_LINK_CCB_BAD
mdefine_line|#define H_LINK_CCB_BAD&t;&t;&t;0x17
DECL|macro|H_BAD_TARGET_DIR
mdefine_line|#define H_BAD_TARGET_DIR&t;&t;0x18
DECL|macro|H_DUPLICATE_CCB
mdefine_line|#define H_DUPLICATE_CCB&t;&t;&t;0x19
DECL|macro|H_BAD_CCB_OR_SG
mdefine_line|#define H_BAD_CCB_OR_SG&t;&t;&t;0x1A
DECL|macro|H_ABORT
mdefine_line|#define H_ABORT&t;&t;&t;&t;0x0FF
multiline_comment|/* SCSI BUS Status byte codes */
DECL|macro|SCSI_STAT_GOOD
mdefine_line|#define SCSI_STAT_GOOD&t;&t;&t;0x0&t;/* Good status&t;&t;&t;&t;*/
DECL|macro|SCSI_STAT_CHECKCOND
mdefine_line|#define SCSI_STAT_CHECKCOND&t;&t;0x02&t;/* SCSI Check Condition&t;&t;&t;*/
DECL|macro|SCSI_STAT_CONDMET
mdefine_line|#define SCSI_STAT_CONDMET&t;&t;0x04&t;/* Condition Met&t;&t;&t;*/
DECL|macro|SCSI_STAT_BUSY
mdefine_line|#define SCSI_STAT_BUSY&t;&t;&t;0x08&t;/* Target busy status&t;&t;&t;*/
DECL|macro|SCSI_STAT_INTER
mdefine_line|#define SCSI_STAT_INTER&t;&t;&t;0x10&t;/* Intermediate status&t;&t;&t;*/
DECL|macro|SCSI_STAT_INTERCONDMET
mdefine_line|#define SCSI_STAT_INTERCONDMET&t;&t;0x14&t;/* Intermediate condition met&t;&t;*/
DECL|macro|SCSI_STAT_RESCONFLICT
mdefine_line|#define SCSI_STAT_RESCONFLICT&t;&t;0x18&t;/* Reservation conflict&t;&t;&t;*/
DECL|macro|SCSI_STAT_CMDTERM
mdefine_line|#define SCSI_STAT_CMDTERM&t;&t;0x22&t;/* Command Terminated&t;&t;&t;*/
DECL|macro|SCSI_STAT_QUEUEFULL
mdefine_line|#define SCSI_STAT_QUEUEFULL&t;&t;0x28&t;/* Queue Full&t;&t;&t;&t;*/
DECL|macro|SCSI_STAT_UNEXP_BUS_F
mdefine_line|#define SCSI_STAT_UNEXP_BUS_F&t;&t;0xFD&t;/* Unexpect Bus Free&t;&t;&t;*/
DECL|macro|SCSI_STAT_BUS_RST_DETECT
mdefine_line|#define SCSI_STAT_BUS_RST_DETECT&t;0xFE&t;/* Scsi Bus Reset detected&t;&t;*/
DECL|macro|SCSI_STAT_SEL_TIMEOUT
mdefine_line|#define SCSI_STAT_SEL_TIMEOUT&t;&t;0xFF&t;/* Selection Time out&t;&t;&t;*/
multiline_comment|/* Sync_Mode */
DECL|macro|SYNC_WIDE_TAG_ATNT_DISABLE
mdefine_line|#define SYNC_WIDE_TAG_ATNT_DISABLE&t;0
DECL|macro|SYNC_NEGO_ENABLE
mdefine_line|#define SYNC_NEGO_ENABLE&t;&t;BIT0
DECL|macro|SYNC_NEGO_DONE
mdefine_line|#define SYNC_NEGO_DONE&t;&t;&t;BIT1
DECL|macro|WIDE_NEGO_ENABLE
mdefine_line|#define WIDE_NEGO_ENABLE&t;&t;BIT2
DECL|macro|WIDE_NEGO_DONE
mdefine_line|#define WIDE_NEGO_DONE&t;&t;&t;BIT3
DECL|macro|WIDE_NEGO_STATE
mdefine_line|#define WIDE_NEGO_STATE&t;&t;&t;BIT4
DECL|macro|EN_TAG_QUEUEING
mdefine_line|#define EN_TAG_QUEUEING&t;&t;&t;BIT5
DECL|macro|EN_ATN_STOP
mdefine_line|#define EN_ATN_STOP&t;&t;&t;BIT6
DECL|macro|SYNC_NEGO_OFFSET
mdefine_line|#define SYNC_NEGO_OFFSET&t;&t;15
multiline_comment|/* SCSI MSG BYTE */
DECL|macro|MSG_COMPLETE
mdefine_line|#define MSG_COMPLETE&t;&t;&t;0x00
DECL|macro|MSG_EXTENDED
mdefine_line|#define MSG_EXTENDED&t;&t;&t;0x01
DECL|macro|MSG_SAVE_PTR
mdefine_line|#define MSG_SAVE_PTR&t;&t;&t;0x02
DECL|macro|MSG_RESTORE_PTR
mdefine_line|#define MSG_RESTORE_PTR&t;&t;&t;0x03
DECL|macro|MSG_DISCONNECT
mdefine_line|#define MSG_DISCONNECT&t;&t;&t;0x04
DECL|macro|MSG_INITIATOR_ERROR
mdefine_line|#define MSG_INITIATOR_ERROR&t;&t;0x05
DECL|macro|MSG_ABORT
mdefine_line|#define MSG_ABORT&t;&t;&t;0x06
DECL|macro|MSG_REJECT_
mdefine_line|#define MSG_REJECT_&t;&t;&t;0x07
DECL|macro|MSG_NOP
mdefine_line|#define MSG_NOP&t;&t;&t;&t;0x08
DECL|macro|MSG_PARITY_ERROR
mdefine_line|#define MSG_PARITY_ERROR&t;&t;0x09
DECL|macro|MSG_LINK_CMD_COMPL
mdefine_line|#define MSG_LINK_CMD_COMPL&t;&t;0x0A
DECL|macro|MSG_LINK_CMD_COMPL_FLG
mdefine_line|#define MSG_LINK_CMD_COMPL_FLG&t;&t;0x0B
DECL|macro|MSG_BUS_RESET
mdefine_line|#define MSG_BUS_RESET&t;&t;&t;0x0C
DECL|macro|MSG_ABORT_TAG
mdefine_line|#define MSG_ABORT_TAG&t;&t;&t;0x0D
DECL|macro|MSG_SIMPLE_QTAG
mdefine_line|#define MSG_SIMPLE_QTAG&t;&t;&t;0x20
DECL|macro|MSG_HEAD_QTAG
mdefine_line|#define MSG_HEAD_QTAG&t;&t;&t;0x21
DECL|macro|MSG_ORDER_QTAG
mdefine_line|#define MSG_ORDER_QTAG&t;&t;&t;0x22
DECL|macro|MSG_IGNOREWIDE
mdefine_line|#define MSG_IGNOREWIDE&t;&t;&t;0x23
DECL|macro|MSG_IDENTIFY
mdefine_line|#define MSG_IDENTIFY&t;&t;&t;0x80
DECL|macro|MSG_HOST_ID
mdefine_line|#define MSG_HOST_ID&t;&t;&t;0xC0
multiline_comment|/* SCSI STATUS BYTE */
DECL|macro|STATUS_GOOD
mdefine_line|#define STATUS_GOOD&t;&t;&t;0x00
DECL|macro|CHECK_CONDITION_
mdefine_line|#define CHECK_CONDITION_&t;&t;0x02
DECL|macro|STATUS_BUSY
mdefine_line|#define STATUS_BUSY&t;&t;&t;0x08
DECL|macro|STATUS_INTERMEDIATE
mdefine_line|#define STATUS_INTERMEDIATE&t;&t;0x10
DECL|macro|RESERVE_CONFLICT
mdefine_line|#define RESERVE_CONFLICT&t;&t;0x18
multiline_comment|/* cmd-&gt;result */
DECL|macro|STATUS_MASK_
mdefine_line|#define STATUS_MASK_&t;&t;&t;0xFF
DECL|macro|MSG_MASK
mdefine_line|#define MSG_MASK&t;&t;&t;0xFF00
DECL|macro|RETURN_MASK
mdefine_line|#define RETURN_MASK&t;&t;&t;0xFF0000
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Inquiry Data format&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|struct|ScsiInqData
r_struct
id|ScsiInqData
(brace
multiline_comment|/* INQ&t;&t;&t;&t;&t;*/
DECL|member|DevType
id|u8
id|DevType
suffix:semicolon
multiline_comment|/* Periph Qualifier &amp; Periph Dev Type&t;*/
DECL|member|RMB_TypeMod
id|u8
id|RMB_TypeMod
suffix:semicolon
multiline_comment|/* rem media bit &amp; Dev Type Modifier&t;*/
DECL|member|Vers
id|u8
id|Vers
suffix:semicolon
multiline_comment|/* ISO, ECMA, &amp; ANSI versions&t;&t;*/
DECL|member|RDF
id|u8
id|RDF
suffix:semicolon
multiline_comment|/* AEN, TRMIOP, &amp; response data format&t;*/
DECL|member|AddLen
id|u8
id|AddLen
suffix:semicolon
multiline_comment|/* length of additional data&t;&t;*/
DECL|member|Res1
id|u8
id|Res1
suffix:semicolon
multiline_comment|/* reserved&t;&t;&t;&t;*/
DECL|member|Res2
id|u8
id|Res2
suffix:semicolon
multiline_comment|/* reserved&t;&t;&t;&t;*/
DECL|member|Flags
id|u8
id|Flags
suffix:semicolon
multiline_comment|/* RelADr, Wbus32, Wbus16, Sync, etc.&t;*/
DECL|member|VendorID
id|u8
id|VendorID
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Vendor Identification&t;&t;*/
DECL|member|ProductID
id|u8
id|ProductID
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Product Identification&t;&t;*/
DECL|member|ProductRev
id|u8
id|ProductRev
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Product Revision&t;&t;&t;*/
)brace
suffix:semicolon
multiline_comment|/* Inquiry byte 0 masks&t;&t;&t;*/
DECL|macro|SCSI_DEVTYPE
mdefine_line|#define SCSI_DEVTYPE&t;&t;&t;0x1F&t;/* Peripheral Device Type&t;&t;*/
DECL|macro|SCSI_PERIPHQUAL
mdefine_line|#define SCSI_PERIPHQUAL&t;&t;&t;0xE0&t;/* Peripheral Qualifier&t;&t;&t;*/
multiline_comment|/* Inquiry byte 1 mask&t;&t;&t;*/
DECL|macro|SCSI_REMOVABLE_MEDIA
mdefine_line|#define SCSI_REMOVABLE_MEDIA&t;&t;0x80&t;/* Removable Media bit (1=removable)&t;*/
multiline_comment|/* Peripheral Device Type definitions&t;*/
multiline_comment|/* See include/scsi/scsi.h&t;&t;*/
DECL|macro|TYPE_NODEV
mdefine_line|#define TYPE_NODEV&t;&t;SCSI_DEVTYPE&t;/* Unknown or no device type&t;&t;*/
macro_line|#ifndef TYPE_PRINTER&t;&t;&t;&t;/*&t;&t;&t;&t;&t;*/
DECL|macro|TYPE_PRINTER
macro_line|# define TYPE_PRINTER&t;&t;&t;0x02&t;/* Printer device&t;&t;&t;*/
macro_line|#endif&t;&t;&t;&t;&t;&t;/*&t;&t;&t;&t;&t;*/
macro_line|#ifndef TYPE_COMM&t;&t;&t;&t;/*&t;&t;&t;&t;&t;*/
DECL|macro|TYPE_COMM
macro_line|# define TYPE_COMM&t;&t;&t;0x09&t;/* Communications device&t;&t;*/
macro_line|#endif
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Inquiry flag definitions (Inq data byte 7)&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|SCSI_INQ_RELADR
mdefine_line|#define SCSI_INQ_RELADR&t;&t;&t;0x80&t;/* device supports relative addressing&t;*/
DECL|macro|SCSI_INQ_WBUS32
mdefine_line|#define SCSI_INQ_WBUS32&t;&t;&t;0x40&t;/* device supports 32 bit data xfers&t;*/
DECL|macro|SCSI_INQ_WBUS16
mdefine_line|#define SCSI_INQ_WBUS16&t;&t;&t;0x20&t;/* device supports 16 bit data xfers&t;*/
DECL|macro|SCSI_INQ_SYNC
mdefine_line|#define SCSI_INQ_SYNC&t;&t;&t;0x10&t;/* device supports synchronous xfer&t;*/
DECL|macro|SCSI_INQ_LINKED
mdefine_line|#define SCSI_INQ_LINKED&t;&t;&t;0x08&t;/* device supports linked commands&t;*/
DECL|macro|SCSI_INQ_CMDQUEUE
mdefine_line|#define SCSI_INQ_CMDQUEUE&t;&t;0x02&t;/* device supports command queueing&t;*/
DECL|macro|SCSI_INQ_SFTRE
mdefine_line|#define SCSI_INQ_SFTRE&t;&t;&t;0x01&t;/* device supports soft resets&t;&t;*/
DECL|macro|ENABLE_CE
mdefine_line|#define ENABLE_CE&t;&t;&t;1
DECL|macro|DISABLE_CE
mdefine_line|#define DISABLE_CE&t;&t;&t;0
DECL|macro|EEPROM_READ
mdefine_line|#define EEPROM_READ&t;&t;&t;0x80
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;The PCI configuration register offset for TRM_S1040&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|TRM_S1040_ID
mdefine_line|#define TRM_S1040_ID&t;&t;&t;0x00&t;/* Vendor and Device ID&t;&t;&t;*/
DECL|macro|TRM_S1040_COMMAND
mdefine_line|#define TRM_S1040_COMMAND&t;&t;0x04&t;/* PCI command register&t;&t;&t;*/
DECL|macro|TRM_S1040_IOBASE
mdefine_line|#define TRM_S1040_IOBASE&t;&t;0x10&t;/* I/O Space base address&t;&t;*/
DECL|macro|TRM_S1040_ROMBASE
mdefine_line|#define TRM_S1040_ROMBASE&t;&t;0x30&t;/* Expansion ROM Base Address&t;&t;*/
DECL|macro|TRM_S1040_INTLINE
mdefine_line|#define TRM_S1040_INTLINE&t;&t;0x3C&t;/* Interrupt line&t;&t;&t;*/
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;The SCSI register offset for TRM_S1040&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|TRM_S1040_SCSI_STATUS
mdefine_line|#define TRM_S1040_SCSI_STATUS&t;&t;0x80&t;/* SCSI Status (R)&t;&t;&t;*/
DECL|macro|COMMANDPHASEDONE
mdefine_line|#define COMMANDPHASEDONE&t;&t;0x2000&t;/* SCSI command phase done&t;&t;*/
DECL|macro|SCSIXFERDONE
mdefine_line|#define SCSIXFERDONE&t;&t;&t;0x0800&t;/* SCSI SCSI transfer done&t;&t;*/
DECL|macro|SCSIXFERCNT_2_ZERO
mdefine_line|#define SCSIXFERCNT_2_ZERO&t;&t;0x0100&t;/* SCSI SCSI transfer count to zero&t;*/
DECL|macro|SCSIINTERRUPT
mdefine_line|#define SCSIINTERRUPT&t;&t;&t;0x0080&t;/* SCSI interrupt pending&t;&t;*/
DECL|macro|COMMANDABORT
mdefine_line|#define COMMANDABORT&t;&t;&t;0x0040&t;/* SCSI command abort&t;&t;&t;*/
DECL|macro|SEQUENCERACTIVE
mdefine_line|#define SEQUENCERACTIVE&t;&t;&t;0x0020&t;/* SCSI sequencer active&t;&t;*/
DECL|macro|PHASEMISMATCH
mdefine_line|#define PHASEMISMATCH&t;&t;&t;0x0010&t;/* SCSI phase mismatch&t;&t;&t;*/
DECL|macro|PARITYERROR
mdefine_line|#define PARITYERROR&t;&t;&t;0x0008&t;/* SCSI parity error&t;&t;&t;*/
DECL|macro|PHASEMASK
mdefine_line|#define PHASEMASK&t;&t;&t;0x0007&t;/* Phase MSG/CD/IO&t;&t;&t;*/
DECL|macro|PH_DATA_OUT
mdefine_line|#define PH_DATA_OUT&t;&t;&t;0x00&t;/* Data out phase&t;&t;&t;*/
DECL|macro|PH_DATA_IN
mdefine_line|#define PH_DATA_IN&t;&t;&t;0x01&t;/* Data in phase&t;&t;&t;*/
DECL|macro|PH_COMMAND
mdefine_line|#define PH_COMMAND&t;&t;&t;0x02&t;/* Command phase&t;&t;&t;*/
DECL|macro|PH_STATUS
mdefine_line|#define PH_STATUS&t;&t;&t;0x03&t;/* Status phase&t;&t;&t;&t;*/
DECL|macro|PH_BUS_FREE
mdefine_line|#define PH_BUS_FREE&t;&t;&t;0x05&t;/* Invalid phase used as bus free&t;*/
DECL|macro|PH_MSG_OUT
mdefine_line|#define PH_MSG_OUT&t;&t;&t;0x06&t;/* Message out phase&t;&t;&t;*/
DECL|macro|PH_MSG_IN
mdefine_line|#define PH_MSG_IN&t;&t;&t;0x07&t;/* Message in phase&t;&t;&t;*/
DECL|macro|TRM_S1040_SCSI_CONTROL
mdefine_line|#define TRM_S1040_SCSI_CONTROL&t;&t;0x80&t;/* SCSI Control (W)&t;&t;&t;*/
DECL|macro|DO_CLRATN
mdefine_line|#define DO_CLRATN&t;&t;&t;0x0400&t;/* Clear ATN&t;&t;&t;&t;*/
DECL|macro|DO_SETATN
mdefine_line|#define DO_SETATN&t;&t;&t;0x0200&t;/* Set ATN&t;&t;&t;&t;*/
DECL|macro|DO_CMDABORT
mdefine_line|#define DO_CMDABORT&t;&t;&t;0x0100&t;/* Abort SCSI command&t;&t;&t;*/
DECL|macro|DO_RSTMODULE
mdefine_line|#define DO_RSTMODULE&t;&t;&t;0x0010&t;/* Reset SCSI chip&t;&t;&t;*/
DECL|macro|DO_RSTSCSI
mdefine_line|#define DO_RSTSCSI&t;&t;&t;0x0008&t;/* Reset SCSI bus&t;&t;&t;*/
DECL|macro|DO_CLRFIFO
mdefine_line|#define DO_CLRFIFO&t;&t;&t;0x0004&t;/* Clear SCSI transfer FIFO&t;&t;*/
DECL|macro|DO_DATALATCH
mdefine_line|#define DO_DATALATCH&t;&t;&t;0x0002&t;/* Enable SCSI bus data input (latched)&t;*/
multiline_comment|/* #define DO_DATALATCH&t;&t;&t;0x0000 */
multiline_comment|/* KG: DISable SCSI bus data latch&t;*/
DECL|macro|DO_HWRESELECT
mdefine_line|#define DO_HWRESELECT&t;&t;&t;0x0001&t;/* Enable hardware reselection&t;&t;*/
DECL|macro|TRM_S1040_SCSI_FIFOCNT
mdefine_line|#define TRM_S1040_SCSI_FIFOCNT&t;&t;0x82&t;/* SCSI FIFO Counter 5bits(R)&t;&t;*/
DECL|macro|TRM_S1040_SCSI_SIGNAL
mdefine_line|#define TRM_S1040_SCSI_SIGNAL&t;&t;0x83&t;/* SCSI low level signal (R/W)&t;&t;*/
DECL|macro|TRM_S1040_SCSI_INTSTATUS
mdefine_line|#define TRM_S1040_SCSI_INTSTATUS&t;0x84&t;/* SCSI Interrupt Status (R)&t;&t;*/
DECL|macro|INT_SCAM
mdefine_line|#define INT_SCAM&t;&t;&t;0x80&t;/* SCAM selection interrupt&t;&t;*/
DECL|macro|INT_SELECT
mdefine_line|#define INT_SELECT&t;&t;&t;0x40&t;/* Selection interrupt&t;&t;&t;*/
DECL|macro|INT_SELTIMEOUT
mdefine_line|#define INT_SELTIMEOUT&t;&t;&t;0x20&t;/* Selection timeout interrupt&t;&t;*/
DECL|macro|INT_DISCONNECT
mdefine_line|#define INT_DISCONNECT&t;&t;&t;0x10&t;/* Bus disconnected interrupt&t;&t;*/
DECL|macro|INT_RESELECTED
mdefine_line|#define INT_RESELECTED&t;&t;&t;0x08&t;/* Reselected interrupt&t;&t;&t;*/
DECL|macro|INT_SCSIRESET
mdefine_line|#define INT_SCSIRESET&t;&t;&t;0x04&t;/* SCSI reset detected interrupt&t;*/
DECL|macro|INT_BUSSERVICE
mdefine_line|#define INT_BUSSERVICE&t;&t;&t;0x02&t;/* Bus service interrupt&t;&t;*/
DECL|macro|INT_CMDDONE
mdefine_line|#define INT_CMDDONE&t;&t;&t;0x01&t;/* SCSI command done interrupt&t;&t;*/
DECL|macro|TRM_S1040_SCSI_OFFSET
mdefine_line|#define TRM_S1040_SCSI_OFFSET&t;&t;0x84&t;/* SCSI Offset Count (W)&t;&t;*/
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Bit&t;&t;Name&t;&t;Definition&t;&t;&t;*/
multiline_comment|/*&t;---------&t;-------------&t;----------------------------&t;*/
multiline_comment|/*&t;07-05&t;0&t;RSVD&t;&t;Reversed. Always 0.&t;&t;*/
multiline_comment|/*&t;04&t;0&t;OFFSET4&t;&t;Reversed for LVDS. Always 0.&t;*/
multiline_comment|/*&t;03-00&t;0&t;OFFSET[03:00]&t;Offset number from 0 to 15&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|TRM_S1040_SCSI_SYNC
mdefine_line|#define TRM_S1040_SCSI_SYNC&t;&t;0x85&t;/* SCSI Synchronous Control (R/W)&t;*/
DECL|macro|LVDS_SYNC
mdefine_line|#define LVDS_SYNC&t;&t;&t;0x20&t;/* Enable LVDS synchronous&t;&t;*/
DECL|macro|WIDE_SYNC
mdefine_line|#define WIDE_SYNC&t;&t;&t;0x10&t;/* Enable WIDE synchronous&t;&t;*/
DECL|macro|ALT_SYNC
mdefine_line|#define ALT_SYNC&t;&t;&t;0x08&t;/* Enable Fast-20 alternate synchronous&t;*/
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;SYNCM&t;7    6    5    4    3       2       1       0&t;&t;*/
multiline_comment|/*&t;Name&t;RSVD RSVD LVDS WIDE ALTPERD PERIOD2 PERIOD1 PERIOD0&t;*/
multiline_comment|/*&t;Default&t;0    0    0    0    0       0       0       0&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Bit&t;&t;Name&t;&t;Definition&t;&t;&t;*/
multiline_comment|/*&t;---------&t;-------------&t;---------------------------&t;*/
multiline_comment|/*&t;07-06&t;0&t;RSVD&t;&t;Reversed. Always read 0&t;&t;*/
multiline_comment|/*&t;05&t;0&t;LVDS&t;&t;Reversed. Always read 0&t;&t;*/
multiline_comment|/*&t;04&t;0&t;WIDE/WSCSI&t;Enable wide (16-bits) SCSI&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;transfer.&t;&t;&t;*/
multiline_comment|/*&t;03&t;0&t;ALTPERD/ALTPD&t;Alternate (Sync./Period) mode.&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;@@ When this bit is set,&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;   the synchronous period bits 2:0&t;&t;*/
multiline_comment|/*&t;&t;&t;   in the Synchronous Mode register&t;&t;*/
multiline_comment|/*&t;&t;&t;   are used to transfer data&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;   at the Fast-20 rate.&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;@@ When this bit is unset,&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;   the synchronous period bits 2:0&t;&t;*/
multiline_comment|/*&t;&t;&t;   in the Synchronous Mode Register&t;&t;*/
multiline_comment|/*&t;&t;&t;   are used to transfer data&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;   at the Fast-10 rate (or Fast-40 w/ LVDS).&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;02-00&t;0&t;PERIOD[2:0]/&t;Synchronous SCSI Transfer Rate.&t;*/
multiline_comment|/*&t;&t;&t;SXPD[02:00]&t;These 3 bits specify&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;the Synchronous SCSI Transfer&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;Rate for Fast-20 and Fast-10.&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;These bits are also reset&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;by a SCSI Bus reset.&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;For Fast-10 bit ALTPD = 0 and LVDS = 0&t;&t;&t;&t;*/
multiline_comment|/*&t;and bit2,bit1,bit0 is defined as follows :&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;000&t;100ns, 10.0 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;001&t;150ns,  6.6 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;010&t;200ns,  5.0 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;011&t;250ns,  4.0 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;100&t;300ns,  3.3 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;101&t;350ns,  2.8 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;110&t;400ns,  2.5 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;111&t;450ns,  2.2 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;For Fast-20 bit ALTPD = 1 and LVDS = 0&t;&t;&t;&t;*/
multiline_comment|/*&t;and bit2,bit1,bit0 is defined as follows :&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;000&t; 50ns, 20.0 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;001&t; 75ns, 13.3 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;010&t;100ns, 10.0 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;011&t;125ns,  8.0 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;100&t;150ns,  6.6 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;101&t;175ns,  5.7 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;110&t;200ns,  5.0 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;111&t;250ns,  4.0 MHz   KG: Maybe 225ns, 4.4 MHz&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;For Fast-40 bit ALTPD = 0 and LVDS = 1&t;&t;&t;&t;*/
multiline_comment|/*&t;and bit2,bit1,bit0 is defined as follows :&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;000&t; 25ns, 40.0 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;001&t; 50ns, 20.0 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;010&t; 75ns, 13.3 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;011&t;100ns, 10.0 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;100&t;125ns,  8.0 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;101&t;150ns,  6.6 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;110&t;175ns,  5.7 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;111&t;200ns,  5.0 MHz&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|TRM_S1040_SCSI_TARGETID
mdefine_line|#define TRM_S1040_SCSI_TARGETID&t;&t;0x86&t;/* SCSI Target ID (R/W)&t;&t;&t;*/
DECL|macro|TRM_S1040_SCSI_IDMSG
mdefine_line|#define TRM_S1040_SCSI_IDMSG&t;&t;0x87&t;/* SCSI Identify Message (R)&t;&t;*/
DECL|macro|TRM_S1040_SCSI_HOSTID
mdefine_line|#define TRM_S1040_SCSI_HOSTID&t;&t;0x87&t;/* SCSI Host ID (W)&t;&t;&t;*/
DECL|macro|TRM_S1040_SCSI_COUNTER
mdefine_line|#define TRM_S1040_SCSI_COUNTER&t;&t;0x88&t;/* SCSI Transfer Counter 24bits(R/W)&t;*/
DECL|macro|TRM_S1040_SCSI_INTEN
mdefine_line|#define TRM_S1040_SCSI_INTEN&t;&t;0x8C&t;/* SCSI Interrupt Enable (R/W)&t;&t;*/
DECL|macro|EN_SCAM
mdefine_line|#define EN_SCAM&t;&t;&t;&t;0x80&t;/* Enable SCAM selection interrupt&t;*/
DECL|macro|EN_SELECT
mdefine_line|#define EN_SELECT&t;&t;&t;0x40&t;/* Enable selection interrupt&t;&t;*/
DECL|macro|EN_SELTIMEOUT
mdefine_line|#define EN_SELTIMEOUT&t;&t;&t;0x20&t;/* Enable selection timeout interrupt&t;*/
DECL|macro|EN_DISCONNECT
mdefine_line|#define EN_DISCONNECT&t;&t;&t;0x10&t;/* Enable bus disconnected interrupt&t;*/
DECL|macro|EN_RESELECTED
mdefine_line|#define EN_RESELECTED&t;&t;&t;0x08&t;/* Enable reselected interrupt&t;&t;*/
DECL|macro|EN_SCSIRESET
mdefine_line|#define EN_SCSIRESET&t;&t;&t;0x04&t;/* Enable SCSI reset detected interrupt&t;*/
DECL|macro|EN_BUSSERVICE
mdefine_line|#define EN_BUSSERVICE&t;&t;&t;0x02&t;/* Enable bus service interrupt&t;&t;*/
DECL|macro|EN_CMDDONE
mdefine_line|#define EN_CMDDONE&t;&t;&t;0x01&t;/* Enable SCSI command done interrupt&t;*/
DECL|macro|TRM_S1040_SCSI_CONFIG0
mdefine_line|#define TRM_S1040_SCSI_CONFIG0&t;&t;0x8D&t;/* SCSI Configuration 0 (R/W)&t;&t;*/
DECL|macro|PHASELATCH
mdefine_line|#define PHASELATCH&t;&t;&t;0x40&t;/* Enable phase latch&t;&t;&t;*/
DECL|macro|INITIATOR
mdefine_line|#define INITIATOR&t;&t;&t;0x20&t;/* Enable initiator mode&t;&t;*/
DECL|macro|PARITYCHECK
mdefine_line|#define PARITYCHECK&t;&t;&t;0x10&t;/* Enable parity check&t;&t;&t;*/
DECL|macro|BLOCKRST
mdefine_line|#define BLOCKRST&t;&t;&t;0x01&t;/* Disable SCSI reset1&t;&t;&t;*/
DECL|macro|TRM_S1040_SCSI_CONFIG1
mdefine_line|#define TRM_S1040_SCSI_CONFIG1&t;&t;0x8E&t;/* SCSI Configuration 1 (R/W)&t;&t;*/
DECL|macro|ACTIVE_NEGPLUS
mdefine_line|#define ACTIVE_NEGPLUS&t;&t;&t;0x10&t;/* Enhance active negation&t;&t;*/
DECL|macro|FILTER_DISABLE
mdefine_line|#define FILTER_DISABLE&t;&t;&t;0x08&t;/* Disable SCSI data filter&t;&t;*/
DECL|macro|FAST_FILTER
mdefine_line|#define FAST_FILTER&t;&t;&t;0x04&t;/* ?&t;&t;&t;&t;&t;*/
DECL|macro|ACTIVE_NEG
mdefine_line|#define ACTIVE_NEG&t;&t;&t;0x02&t;/* Enable active negation&t;&t;*/
DECL|macro|TRM_S1040_SCSI_CONFIG2
mdefine_line|#define TRM_S1040_SCSI_CONFIG2&t;&t;0x8F&t;/* SCSI Configuration 2 (R/W)&t;&t;*/
DECL|macro|CFG2_WIDEFIFO
mdefine_line|#define CFG2_WIDEFIFO&t;&t;&t;0x02&t;/*&t;&t;&t;&t;&t;*/
DECL|macro|TRM_S1040_SCSI_COMMAND
mdefine_line|#define TRM_S1040_SCSI_COMMAND&t;&t;0x90&t;/* SCSI Command (R/W)&t;&t;&t;*/
DECL|macro|SCMD_COMP
mdefine_line|#define SCMD_COMP&t;&t;&t;0x12&t;/* Command complete&t;&t;&t;*/
DECL|macro|SCMD_SEL_ATN
mdefine_line|#define SCMD_SEL_ATN&t;&t;&t;0x60&t;/* Selection with ATN&t;&t;&t;*/
DECL|macro|SCMD_SEL_ATN3
mdefine_line|#define SCMD_SEL_ATN3&t;&t;&t;0x64&t;/* Selection with ATN3&t;&t;&t;*/
DECL|macro|SCMD_SEL_ATNSTOP
mdefine_line|#define SCMD_SEL_ATNSTOP&t;&t;0xB8&t;/* Selection with ATN and Stop&t;&t;*/
DECL|macro|SCMD_FIFO_OUT
mdefine_line|#define SCMD_FIFO_OUT&t;&t;&t;0xC0&t;/* SCSI FIFO transfer out&t;&t;*/
DECL|macro|SCMD_DMA_OUT
mdefine_line|#define SCMD_DMA_OUT&t;&t;&t;0xC1&t;/* SCSI DMA transfer out&t;&t;*/
DECL|macro|SCMD_FIFO_IN
mdefine_line|#define SCMD_FIFO_IN&t;&t;&t;0xC2&t;/* SCSI FIFO transfer in&t;&t;*/
DECL|macro|SCMD_DMA_IN
mdefine_line|#define SCMD_DMA_IN&t;&t;&t;0xC3&t;/* SCSI DMA transfer in&t;&t;&t;*/
DECL|macro|SCMD_MSGACCEPT
mdefine_line|#define SCMD_MSGACCEPT&t;&t;&t;0xD8&t;/* Message accept&t;&t;&t;*/
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Code&t;Command Description&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;----&t;----------------------------------------&t;&t;*/
multiline_comment|/*&t;02&t;Enable reselection with FIFO&t;&t;&t;&t;*/
multiline_comment|/*&t;40&t;Select without ATN with FIFO&t;&t;&t;&t;*/
multiline_comment|/*&t;60&t;Select with ATN with FIFO&t;&t;&t;&t;*/
multiline_comment|/*&t;64&t;Select with ATN3 with FIFO&t;&t;&t;&t;*/
multiline_comment|/*&t;A0&t;Select with ATN and stop with FIFO&t;&t;&t;*/
multiline_comment|/*&t;C0&t;Transfer information out with FIFO&t;&t;&t;*/
multiline_comment|/*&t;C1&t;Transfer information out with DMA&t;&t;&t;*/
multiline_comment|/*&t;C2&t;Transfer information in with FIFO&t;&t;&t;*/
multiline_comment|/*&t;C3&t;Transfer information in with DMA&t;&t;&t;*/
multiline_comment|/*&t;12&t;Initiator command complete with FIFO&t;&t;&t;*/
multiline_comment|/*&t;50&t;Initiator transfer information out sequence without ATN&t;*/
multiline_comment|/*&t;&t;with FIFO&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;70&t;Initiator transfer information out sequence with ATN&t;*/
multiline_comment|/*&t;&t;with FIFO&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;74&t;Initiator transfer information out sequence with ATN3&t;*/
multiline_comment|/*&t;&t;with FIFO&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;52&t;Initiator transfer information in sequence without ATN&t;*/
multiline_comment|/*&t;&t;with FIFO&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;72&t;Initiator transfer information in sequence with ATN&t;*/
multiline_comment|/*&t;&t;with FIFO&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;76&t;Initiator transfer information in sequence with ATN3&t;*/
multiline_comment|/*&t;&t;with FIFO&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;90&t;Initiator transfer information out command complete&t;*/
multiline_comment|/*&t;&t;with FIFO&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;92&t;Initiator transfer information in command complete&t;*/
multiline_comment|/*&t;&t;with FIFO&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;D2&t;Enable selection&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;08&t;Reselection&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;48&t;Disconnect command with FIFO&t;&t;&t;&t;*/
multiline_comment|/*&t;88&t;Terminate command with FIFO&t;&t;&t;&t;*/
multiline_comment|/*&t;C8&t;Target command complete with FIFO&t;&t;&t;*/
multiline_comment|/*&t;18&t;SCAM Arbitration/ Selection&t;&t;&t;&t;*/
multiline_comment|/*&t;5A&t;Enable reselection&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;98&t;Select without ATN with FIFO&t;&t;&t;&t;*/
multiline_comment|/*&t;B8&t;Select with ATN with FIFO&t;&t;&t;&t;*/
multiline_comment|/*&t;D8&t;Message Accepted&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;58&t;NOP&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|TRM_S1040_SCSI_TIMEOUT
mdefine_line|#define TRM_S1040_SCSI_TIMEOUT&t;&t;0x91&t;/* SCSI Time Out Value (R/W)&t;&t;*/
DECL|macro|TRM_S1040_SCSI_FIFO
mdefine_line|#define TRM_S1040_SCSI_FIFO&t;&t;0x98&t;/* SCSI FIFO (R/W)&t;&t;&t;*/
DECL|macro|TRM_S1040_SCSI_TCR0
mdefine_line|#define TRM_S1040_SCSI_TCR0&t;&t;0x9C&t;/* SCSI Target Control 0 (R/W)&t;&t;*/
DECL|macro|TCR0_WIDE_NEGO_DONE
mdefine_line|#define TCR0_WIDE_NEGO_DONE&t;&t;0x8000&t;/* Wide nego done&t;&t;&t;*/
DECL|macro|TCR0_SYNC_NEGO_DONE
mdefine_line|#define TCR0_SYNC_NEGO_DONE&t;&t;0x4000&t;/* Synchronous nego done&t;&t;*/
DECL|macro|TCR0_ENABLE_LVDS
mdefine_line|#define TCR0_ENABLE_LVDS&t;&t;0x2000&t;/* Enable LVDS synchronous&t;&t;*/
DECL|macro|TCR0_ENABLE_WIDE
mdefine_line|#define TCR0_ENABLE_WIDE&t;&t;0x1000&t;/* Enable WIDE synchronous&t;&t;*/
DECL|macro|TCR0_ENABLE_ALT
mdefine_line|#define TCR0_ENABLE_ALT&t;&t;&t;0x0800&t;/* Enable alternate synchronous&t;&t;*/
DECL|macro|TCR0_PERIOD_MASK
mdefine_line|#define TCR0_PERIOD_MASK&t;&t;0x0700&t;/* Transfer rate&t;&t;&t;*/
DECL|macro|TCR0_DO_WIDE_NEGO
mdefine_line|#define TCR0_DO_WIDE_NEGO&t;&t;0x0080&t;/* Do wide NEGO&t;&t;&t;&t;*/
DECL|macro|TCR0_DO_SYNC_NEGO
mdefine_line|#define TCR0_DO_SYNC_NEGO&t;&t;0x0040&t;/* Do sync NEGO&t;&t;&t;&t;*/
DECL|macro|TCR0_DISCONNECT_EN
mdefine_line|#define TCR0_DISCONNECT_EN&t;&t;0x0020&t;/* Disconnection enable&t;&t;&t;*/
DECL|macro|TCR0_OFFSET_MASK
mdefine_line|#define TCR0_OFFSET_MASK&t;&t;0x001F&t;/* Offset number&t;&t;&t;*/
DECL|macro|TRM_S1040_SCSI_TCR1
mdefine_line|#define TRM_S1040_SCSI_TCR1&t;&t;0x9E&t;/* SCSI Target Control 1 (R/W)&t;&t;*/
DECL|macro|MAXTAG_MASK
mdefine_line|#define MAXTAG_MASK&t;&t;&t;0x7F00&t;/* Maximum tags (127)&t;&t;&t;*/
DECL|macro|NON_TAG_BUSY
mdefine_line|#define NON_TAG_BUSY&t;&t;&t;0x0080&t;/* Non tag command active&t;&t;*/
DECL|macro|ACTTAG_MASK
mdefine_line|#define ACTTAG_MASK&t;&t;&t;0x007F&t;/* Active tags&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;The DMA register offset for TRM_S1040&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|TRM_S1040_DMA_COMMAND
mdefine_line|#define TRM_S1040_DMA_COMMAND&t;&t;0xA0&t;/* DMA Command (R/W)&t;&t;&t;*/
DECL|macro|DMACMD_SG
mdefine_line|#define DMACMD_SG&t;&t;&t;0x02&t;/* Enable HW S/G support&t;&t;*/
DECL|macro|DMACMD_DIR
mdefine_line|#define DMACMD_DIR&t;&t;&t;0x01&t;/* 1 = read from SCSI write to Host&t;*/
DECL|macro|XFERDATAIN_SG
mdefine_line|#define XFERDATAIN_SG&t;&t;&t;0x0103&t;/* Transfer data in  w/  SG&t;&t;*/
DECL|macro|XFERDATAOUT_SG
mdefine_line|#define XFERDATAOUT_SG&t;&t;&t;0x0102&t;/* Transfer data out w/  SG&t;&t;*/
DECL|macro|XFERDATAIN
mdefine_line|#define XFERDATAIN&t;&t;&t;0x0101&t;/* Transfer data in  w/o SG&t;&t;*/
DECL|macro|XFERDATAOUT
mdefine_line|#define XFERDATAOUT&t;&t;&t;0x0100&t;/* Transfer data out w/o SG&t;&t;*/
DECL|macro|TRM_S1040_DMA_FIFOCNT
mdefine_line|#define TRM_S1040_DMA_FIFOCNT&t;&t;0xA1&t;/* DMA FIFO Counter (R)&t;&t;&t;*/
DECL|macro|TRM_S1040_DMA_CONTROL
mdefine_line|#define TRM_S1040_DMA_CONTROL&t;&t;0xA1&t;/* DMA Control (W)&t;&t;&t;*/
DECL|macro|DMARESETMODULE
mdefine_line|#define DMARESETMODULE&t;&t;&t;0x10&t;/* Reset PCI/DMA module&t;&t;&t;*/
DECL|macro|STOPDMAXFER
mdefine_line|#define STOPDMAXFER&t;&t;&t;0x08&t;/* Stop  DMA transfer&t;&t;&t;*/
DECL|macro|ABORTXFER
mdefine_line|#define ABORTXFER&t;&t;&t;0x04&t;/* Abort DMA transfer&t;&t;&t;*/
DECL|macro|CLRXFIFO
mdefine_line|#define CLRXFIFO&t;&t;&t;0x02&t;/* Clear DMA transfer FIFO&t;&t;*/
DECL|macro|STARTDMAXFER
mdefine_line|#define STARTDMAXFER&t;&t;&t;0x01&t;/* Start DMA transfer&t;&t;&t;*/
DECL|macro|TRM_S1040_DMA_FIFOSTAT
mdefine_line|#define TRM_S1040_DMA_FIFOSTAT&t;&t;0xA2&t;/* DMA FIFO Status (R)&t;&t;&t;*/
DECL|macro|TRM_S1040_DMA_STATUS
mdefine_line|#define TRM_S1040_DMA_STATUS&t;&t;0xA3&t;/* DMA Interrupt Status (R/W)&t;&t;*/
DECL|macro|XFERPENDING
mdefine_line|#define XFERPENDING&t;&t;&t;0x80&t;/* Transfer pending&t;&t;&t;*/
DECL|macro|SCSIBUSY
mdefine_line|#define SCSIBUSY&t;&t;&t;0x40&t;/* SCSI busy&t;&t;&t;&t;*/
DECL|macro|GLOBALINT
mdefine_line|#define GLOBALINT&t;&t;&t;0x20&t;/* DMA_INTEN bit 0-4 set&t;&t;*/
DECL|macro|FORCEDMACOMP
mdefine_line|#define FORCEDMACOMP&t;&t;&t;0x10&t;/* Force DMA transfer complete&t;&t;*/
DECL|macro|DMAXFERERROR
mdefine_line|#define DMAXFERERROR&t;&t;&t;0x08&t;/* DMA transfer error&t;&t;&t;*/
DECL|macro|DMAXFERABORT
mdefine_line|#define DMAXFERABORT&t;&t;&t;0x04&t;/* DMA transfer abort&t;&t;&t;*/
DECL|macro|DMAXFERCOMP
mdefine_line|#define DMAXFERCOMP&t;&t;&t;0x02&t;/* Bus Master XFER Complete status&t;*/
DECL|macro|SCSICOMP
mdefine_line|#define SCSICOMP&t;&t;&t;0x01&t;/* SCSI complete interrupt&t;&t;*/
DECL|macro|TRM_S1040_DMA_INTEN
mdefine_line|#define TRM_S1040_DMA_INTEN&t;&t;0xA4&t;/* DMA Interrupt Enable (R/W)&t;&t;*/
DECL|macro|EN_FORCEDMACOMP
mdefine_line|#define EN_FORCEDMACOMP&t;&t;&t;0x10&t;/* Force DMA transfer complete&t;&t;*/
DECL|macro|EN_DMAXFERERROR
mdefine_line|#define EN_DMAXFERERROR&t;&t;&t;0x08&t;/* DMA transfer error&t;&t;&t;*/
DECL|macro|EN_DMAXFERABORT
mdefine_line|#define EN_DMAXFERABORT&t;&t;&t;0x04&t;/* DMA transfer abort&t;&t;&t;*/
DECL|macro|EN_DMAXFERCOMP
mdefine_line|#define EN_DMAXFERCOMP&t;&t;&t;0x02&t;/* Bus Master XFER Complete status&t;*/
DECL|macro|EN_SCSIINTR
mdefine_line|#define EN_SCSIINTR&t;&t;&t;0x01&t;/* Enable SCSI complete interrupt&t;*/
DECL|macro|TRM_S1040_DMA_CONFIG
mdefine_line|#define TRM_S1040_DMA_CONFIG&t;&t;0xA6&t;/* DMA Configuration (R/W)&t;&t;*/
DECL|macro|DMA_ENHANCE
mdefine_line|#define DMA_ENHANCE&t;&t;&t;0x8000&t;/* Enable DMA enhance feature (SG?)&t;*/
DECL|macro|DMA_PCI_DUAL_ADDR
mdefine_line|#define DMA_PCI_DUAL_ADDR&t;&t;0x4000&t;/*&t;&t;&t;&t;&t;*/
DECL|macro|DMA_CFG_RES
mdefine_line|#define DMA_CFG_RES&t;&t;&t;0x2000&t;/* Always 1&t;&t;&t;&t;*/
DECL|macro|DMA_AUTO_CLR_FIFO
mdefine_line|#define DMA_AUTO_CLR_FIFO&t;&t;0x1000&t;/* DISable DMA auto clear FIFO&t;&t;*/
DECL|macro|DMA_MEM_MULTI_READ
mdefine_line|#define DMA_MEM_MULTI_READ&t;&t;0x0800&t;/*&t;&t;&t;&t;&t;*/
DECL|macro|DMA_MEM_WRITE_INVAL
mdefine_line|#define DMA_MEM_WRITE_INVAL&t;&t;0x0400&t;/* Memory write and invalidate&t;&t;*/
DECL|macro|DMA_FIFO_CTRL
mdefine_line|#define DMA_FIFO_CTRL&t;&t;&t;0x0300&t;/* Control FIFO operation with DMA&t;*/
DECL|macro|DMA_FIFO_HALF_HALF
mdefine_line|#define DMA_FIFO_HALF_HALF&t;&t;0x0200&t;/* Keep half filled on both read/write&t;*/
DECL|macro|TRM_S1040_DMA_XCNT
mdefine_line|#define TRM_S1040_DMA_XCNT&t;&t;0xA8&t;/* DMA Transfer Counter (R/W), 24bits&t;*/
DECL|macro|TRM_S1040_DMA_CXCNT
mdefine_line|#define TRM_S1040_DMA_CXCNT&t;&t;0xAC&t;/* DMA Current Transfer Counter (R)&t;*/
DECL|macro|TRM_S1040_DMA_XLOWADDR
mdefine_line|#define TRM_S1040_DMA_XLOWADDR&t;&t;0xB0&t;/* DMA Transfer Physical Low Address&t;*/
DECL|macro|TRM_S1040_DMA_XHIGHADDR
mdefine_line|#define TRM_S1040_DMA_XHIGHADDR&t;&t;0xB4&t;/* DMA Transfer Physical High Address&t;*/
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;The general register offset for TRM_S1040&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|TRM_S1040_GEN_CONTROL
mdefine_line|#define TRM_S1040_GEN_CONTROL&t;&t;0xD4&t;/* Global Control&t;&t;&t;*/
DECL|macro|CTRL_LED
mdefine_line|#define CTRL_LED&t;&t;&t;0x80&t;/* Control onboard LED&t;&t;&t;*/
DECL|macro|EN_EEPROM
mdefine_line|#define EN_EEPROM&t;&t;&t;0x10&t;/* Enable EEPROM programming&t;&t;*/
DECL|macro|DIS_TERM
mdefine_line|#define DIS_TERM&t;&t;&t;0x08&t;/* Disable onboard termination&t;&t;*/
DECL|macro|AUTOTERM
mdefine_line|#define AUTOTERM&t;&t;&t;0x04&t;/* Enable Auto SCSI terminator&t;&t;*/
DECL|macro|LOW8TERM
mdefine_line|#define LOW8TERM&t;&t;&t;0x02&t;/* Enable Lower 8 bit SCSI terminator&t;*/
DECL|macro|UP8TERM
mdefine_line|#define UP8TERM&t;&t;&t;&t;0x01&t;/* Enable Upper 8 bit SCSI terminator&t;*/
DECL|macro|TRM_S1040_GEN_STATUS
mdefine_line|#define TRM_S1040_GEN_STATUS&t;&t;0xD5&t;/* Global Status&t;&t;&t;*/
DECL|macro|GTIMEOUT
mdefine_line|#define GTIMEOUT&t;&t;&t;0x80&t;/* Global timer reach 0&t;&t;&t;*/
DECL|macro|EXT68HIGH
mdefine_line|#define EXT68HIGH&t;&t;&t;0x40&t;/* Higher 8 bit connected externally&t;*/
DECL|macro|INT68HIGH
mdefine_line|#define INT68HIGH&t;&t;&t;0x20&t;/* Higher 8 bit connected internally&t;*/
DECL|macro|CON5068
mdefine_line|#define CON5068&t;&t;&t;&t;0x10&t;/* External 50/68 pin connected (low)&t;*/
DECL|macro|CON68
mdefine_line|#define CON68&t;&t;&t;&t;0x08&t;/* Internal 68 pin connected (low)&t;*/
DECL|macro|CON50
mdefine_line|#define CON50&t;&t;&t;&t;0x04&t;/* Internal 50 pin connected (low!)&t;*/
DECL|macro|WIDESCSI
mdefine_line|#define WIDESCSI&t;&t;&t;0x02&t;/* Wide SCSI card&t;&t;&t;*/
DECL|macro|STATUS_LOAD_DEFAULT
mdefine_line|#define STATUS_LOAD_DEFAULT&t;&t;0x01&t;/*&t;&t;&t;&t;&t;*/
DECL|macro|TRM_S1040_GEN_NVRAM
mdefine_line|#define TRM_S1040_GEN_NVRAM&t;&t;0xD6&t;/* Serial NON-VOLATILE RAM port&t;&t;*/
DECL|macro|NVR_BITOUT
mdefine_line|#define NVR_BITOUT&t;&t;&t;0x08&t;/* Serial data out&t;&t;&t;*/
DECL|macro|NVR_BITIN
mdefine_line|#define NVR_BITIN&t;&t;&t;0x04&t;/* Serial data in&t;&t;&t;*/
DECL|macro|NVR_CLOCK
mdefine_line|#define NVR_CLOCK&t;&t;&t;0x02&t;/* Serial clock&t;&t;&t;&t;*/
DECL|macro|NVR_SELECT
mdefine_line|#define NVR_SELECT&t;&t;&t;0x01&t;/* Serial select&t;&t;&t;*/
DECL|macro|TRM_S1040_GEN_EDATA
mdefine_line|#define TRM_S1040_GEN_EDATA&t;&t;0xD7&t;/* Parallel EEPROM data port&t;&t;*/
DECL|macro|TRM_S1040_GEN_EADDRESS
mdefine_line|#define TRM_S1040_GEN_EADDRESS&t;&t;0xD8&t;/* Parallel EEPROM address&t;&t;*/
DECL|macro|TRM_S1040_GEN_TIMER
mdefine_line|#define TRM_S1040_GEN_TIMER&t;&t;0xDB&t;/* Global timer&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;NvmTarCfg0: Target configuration byte 0 :..pDCB-&gt;DevMode&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|NTC_DO_WIDE_NEGO
mdefine_line|#define NTC_DO_WIDE_NEGO&t;&t;0x20&t;/* Wide negotiate&t;&t;&t;*/
DECL|macro|NTC_DO_TAG_QUEUEING
mdefine_line|#define NTC_DO_TAG_QUEUEING&t;&t;0x10&t;/* Enable SCSI tag queuing&t;&t;*/
DECL|macro|NTC_DO_SEND_START
mdefine_line|#define NTC_DO_SEND_START&t;&t;0x08&t;/* Send start command SPINUP&t;&t;*/
DECL|macro|NTC_DO_DISCONNECT
mdefine_line|#define NTC_DO_DISCONNECT&t;&t;0x04&t;/* Enable SCSI disconnect&t;&t;*/
DECL|macro|NTC_DO_SYNC_NEGO
mdefine_line|#define NTC_DO_SYNC_NEGO&t;&t;0x02&t;/* Sync negotiation&t;&t;&t;*/
DECL|macro|NTC_DO_PARITY_CHK
mdefine_line|#define NTC_DO_PARITY_CHK&t;&t;0x01&t;/* (it sould define at NAC)&t;&t;*/
multiline_comment|/* Parity check enable&t;&t;&t;*/
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Nvram Initiater bits definition&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
macro_line|#if 0
mdefine_line|#define MORE2_DRV&t;&t;&t;BIT0
mdefine_line|#define GREATER_1G&t;&t;&t;BIT1
mdefine_line|#define RST_SCSI_BUS&t;&t;&t;BIT2
mdefine_line|#define ACTIVE_NEGATION&t;&t;&t;BIT3
mdefine_line|#define NO_SEEK&t;&t;&t;&t;BIT4
mdefine_line|#define LUN_CHECK&t;&t;&t;BIT5
macro_line|#endif
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Nvram Adapter Cfg bits definition&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|NAC_SCANLUN
mdefine_line|#define NAC_SCANLUN&t;&t;&t;0x20&t;/* Include LUN as BIOS device&t;&t;*/
DECL|macro|NAC_POWERON_SCSI_RESET
mdefine_line|#define NAC_POWERON_SCSI_RESET&t;&t;0x04&t;/* Power on reset enable&t;&t;*/
DECL|macro|NAC_GREATER_1G
mdefine_line|#define NAC_GREATER_1G&t;&t;&t;0x02&t;/* &gt; 1G support enable&t;&t;&t;*/
DECL|macro|NAC_GT2DRIVES
mdefine_line|#define NAC_GT2DRIVES&t;&t;&t;0x01&t;/* Support more than 2 drives&t;&t;*/
multiline_comment|/* #define NAC_DO_PARITY_CHK&t;&t;0x08 */
multiline_comment|/* Parity check enable&t;&t;&t;*/
macro_line|#endif
eof
