multiline_comment|/*&n; *  Copyright (c) 2000-2001 LSI Logic Corporation.&n; *&n; *&n; *           Name:  MPI_INIT.H&n; *          Title:  MPI initiator mode messages and structures&n; *  Creation Date:  June 8, 2000&n; *&n; *    MPI Version:  01.02.04&n; *&n; *  Version History&n; *  ---------------&n; *&n; *  Date      Version   Description&n; *  --------  --------  ------------------------------------------------------&n; *  05-08-00  00.10.01  Original release for 0.10 spec dated 4/26/2000.&n; *  05-24-00  00.10.02  Added SenseBufferLength to _MSG_SCSI_IO_REPLY.&n; *  06-06-00  01.00.01  Update version number for 1.0 release.&n; *  06-08-00  01.00.02  Added MPI_SCSI_RSP_INFO_ definitions.&n; *  11-02-00  01.01.01  Original release for post 1.0 work.&n; *  12-04-00  01.01.02  Added MPI_SCSIIO_CONTROL_NO_DISCONNECT.&n; *  02-20-01  01.01.03  Started using MPI_POINTER.&n; *  03-27-01  01.01.04  Added structure offset comments.&n; *  04-10-01  01.01.05  Added new MsgFlag for MSG_SCSI_TASK_MGMT.&n; *  08-08-01  01.02.01  Original release for v1.2 work.&n; *  08-29-01  01.02.02  Added MPI_SCSITASKMGMT_TASKTYPE_LOGICAL_UNIT_RESET.&n; *                      Added MPI_SCSI_STATE_QUEUE_TAG_REJECTED for&n; *                      MSG_SCSI_IO_REPLY.&n; *  09-28-01  01.02.03  Added structures and defines for SCSI Enclosure&n; *                      Processor messages.&n; *  10-04-01  01.02.04  Added defines for SEP request Action field.&n; *  --------------------------------------------------------------------------&n; */
macro_line|#ifndef MPI_INIT_H
DECL|macro|MPI_INIT_H
mdefine_line|#define MPI_INIT_H
multiline_comment|/*****************************************************************************&n;*&n;*               S C S I    I n i t i a t o r    M e s s a g e s&n;*&n;*****************************************************************************/
multiline_comment|/****************************************************************************/
multiline_comment|/*  SCSI IO messages and assocaited structures                              */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_SCSI_IO_REQUEST
r_typedef
r_struct
id|_MSG_SCSI_IO_REQUEST
(brace
DECL|member|TargetID
id|U8
id|TargetID
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Bus
id|U8
id|Bus
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|ChainOffset
id|U8
id|ChainOffset
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|Function
id|U8
id|Function
suffix:semicolon
multiline_comment|/* 03h */
DECL|member|CDBLength
id|U8
id|CDBLength
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|SenseBufferLength
id|U8
id|SenseBufferLength
suffix:semicolon
multiline_comment|/* 05h */
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
multiline_comment|/* 06h */
DECL|member|MsgFlags
id|U8
id|MsgFlags
suffix:semicolon
multiline_comment|/* 07h */
DECL|member|MsgContext
id|U32
id|MsgContext
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|LUN
id|U8
id|LUN
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|Control
id|U32
id|Control
suffix:semicolon
multiline_comment|/* 14h */
DECL|member|CDB
id|U8
id|CDB
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 18h */
DECL|member|DataLength
id|U32
id|DataLength
suffix:semicolon
multiline_comment|/* 28h */
DECL|member|SenseBufferLowAddr
id|U32
id|SenseBufferLowAddr
suffix:semicolon
multiline_comment|/* 2Ch */
DECL|member|SGL
id|SGE_IO_UNION
id|SGL
suffix:semicolon
multiline_comment|/* 30h */
DECL|typedef|MSG_SCSI_IO_REQUEST
DECL|typedef|PTR_MSG_SCSI_IO_REQUEST
)brace
id|MSG_SCSI_IO_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_SCSI_IO_REQUEST
comma
DECL|typedef|SCSIIORequest_t
DECL|typedef|pSCSIIORequest_t
id|SCSIIORequest_t
comma
id|MPI_POINTER
id|pSCSIIORequest_t
suffix:semicolon
multiline_comment|/* SCSIO MsgFlags bits */
DECL|macro|MPI_SCSIIO_MSGFLGS_SENSE_WIDTH
mdefine_line|#define MPI_SCSIIO_MSGFLGS_SENSE_WIDTH          (0x01)
DECL|macro|MPI_SCSIIO_MSGFLGS_SENSE_WIDTH_32
mdefine_line|#define MPI_SCSIIO_MSGFLGS_SENSE_WIDTH_32       (0x00)
DECL|macro|MPI_SCSIIO_MSGFLGS_SENSE_WIDTH_64
mdefine_line|#define MPI_SCSIIO_MSGFLGS_SENSE_WIDTH_64       (0x01)
DECL|macro|MPI_SCSIIO_MSGFLGS_SENSE_LOCATION
mdefine_line|#define MPI_SCSIIO_MSGFLGS_SENSE_LOCATION       (0x02)
DECL|macro|MPI_SCSIIO_MSGFLGS_SENSE_LOC_HOST
mdefine_line|#define MPI_SCSIIO_MSGFLGS_SENSE_LOC_HOST       (0x00)
DECL|macro|MPI_SCSIIO_MSGFLGS_SENSE_LOC_IOC
mdefine_line|#define MPI_SCSIIO_MSGFLGS_SENSE_LOC_IOC        (0x02)
multiline_comment|/* SCSIIO LUN fields */
DECL|macro|MPI_SCSIIO_LUN_FIRST_LEVEL_ADDRESSING
mdefine_line|#define MPI_SCSIIO_LUN_FIRST_LEVEL_ADDRESSING   (0x0000FFFF)
DECL|macro|MPI_SCSIIO_LUN_SECOND_LEVEL_ADDRESSING
mdefine_line|#define MPI_SCSIIO_LUN_SECOND_LEVEL_ADDRESSING  (0xFFFF0000)
DECL|macro|MPI_SCSIIO_LUN_THIRD_LEVEL_ADDRESSING
mdefine_line|#define MPI_SCSIIO_LUN_THIRD_LEVEL_ADDRESSING   (0x0000FFFF)
DECL|macro|MPI_SCSIIO_LUN_FOURTH_LEVEL_ADDRESSING
mdefine_line|#define MPI_SCSIIO_LUN_FOURTH_LEVEL_ADDRESSING  (0xFFFF0000)
DECL|macro|MPI_SCSIIO_LUN_LEVEL_1_WORD
mdefine_line|#define MPI_SCSIIO_LUN_LEVEL_1_WORD             (0xFF00)
DECL|macro|MPI_SCSIIO_LUN_LEVEL_1_DWORD
mdefine_line|#define MPI_SCSIIO_LUN_LEVEL_1_DWORD            (0x0000FF00)
multiline_comment|/* SCSIO Control bits */
DECL|macro|MPI_SCSIIO_CONTROL_DATADIRECTION_MASK
mdefine_line|#define MPI_SCSIIO_CONTROL_DATADIRECTION_MASK   (0x03000000)
DECL|macro|MPI_SCSIIO_CONTROL_NODATATRANSFER
mdefine_line|#define MPI_SCSIIO_CONTROL_NODATATRANSFER       (0x00000000)
DECL|macro|MPI_SCSIIO_CONTROL_WRITE
mdefine_line|#define MPI_SCSIIO_CONTROL_WRITE                (0x01000000)
DECL|macro|MPI_SCSIIO_CONTROL_READ
mdefine_line|#define MPI_SCSIIO_CONTROL_READ                 (0x02000000)
DECL|macro|MPI_SCSIIO_CONTROL_ADDCDBLEN_MASK
mdefine_line|#define MPI_SCSIIO_CONTROL_ADDCDBLEN_MASK       (0x3C000000)
DECL|macro|MPI_SCSIIO_CONTROL_ADDCDBLEN_SHIFT
mdefine_line|#define MPI_SCSIIO_CONTROL_ADDCDBLEN_SHIFT      (26)
DECL|macro|MPI_SCSIIO_CONTROL_TASKATTRIBUTE_MASK
mdefine_line|#define MPI_SCSIIO_CONTROL_TASKATTRIBUTE_MASK   (0x00000700)
DECL|macro|MPI_SCSIIO_CONTROL_SIMPLEQ
mdefine_line|#define MPI_SCSIIO_CONTROL_SIMPLEQ              (0x00000000)
DECL|macro|MPI_SCSIIO_CONTROL_HEADOFQ
mdefine_line|#define MPI_SCSIIO_CONTROL_HEADOFQ              (0x00000100)
DECL|macro|MPI_SCSIIO_CONTROL_ORDEREDQ
mdefine_line|#define MPI_SCSIIO_CONTROL_ORDEREDQ             (0x00000200)
DECL|macro|MPI_SCSIIO_CONTROL_ACAQ
mdefine_line|#define MPI_SCSIIO_CONTROL_ACAQ                 (0x00000400)
DECL|macro|MPI_SCSIIO_CONTROL_UNTAGGED
mdefine_line|#define MPI_SCSIIO_CONTROL_UNTAGGED             (0x00000500)
DECL|macro|MPI_SCSIIO_CONTROL_NO_DISCONNECT
mdefine_line|#define MPI_SCSIIO_CONTROL_NO_DISCONNECT        (0x00000700)
DECL|macro|MPI_SCSIIO_CONTROL_TASKMANAGE_MASK
mdefine_line|#define MPI_SCSIIO_CONTROL_TASKMANAGE_MASK      (0x00FF0000)
DECL|macro|MPI_SCSIIO_CONTROL_OBSOLETE
mdefine_line|#define MPI_SCSIIO_CONTROL_OBSOLETE             (0x00800000)
DECL|macro|MPI_SCSIIO_CONTROL_CLEAR_ACA_RSV
mdefine_line|#define MPI_SCSIIO_CONTROL_CLEAR_ACA_RSV        (0x00400000)
DECL|macro|MPI_SCSIIO_CONTROL_TARGET_RESET
mdefine_line|#define MPI_SCSIIO_CONTROL_TARGET_RESET         (0x00200000)
DECL|macro|MPI_SCSIIO_CONTROL_LUN_RESET_RSV
mdefine_line|#define MPI_SCSIIO_CONTROL_LUN_RESET_RSV        (0x00100000)
DECL|macro|MPI_SCSIIO_CONTROL_RESERVED
mdefine_line|#define MPI_SCSIIO_CONTROL_RESERVED             (0x00080000)
DECL|macro|MPI_SCSIIO_CONTROL_CLR_TASK_SET_RSV
mdefine_line|#define MPI_SCSIIO_CONTROL_CLR_TASK_SET_RSV     (0x00040000)
DECL|macro|MPI_SCSIIO_CONTROL_ABORT_TASK_SET
mdefine_line|#define MPI_SCSIIO_CONTROL_ABORT_TASK_SET       (0x00020000)
DECL|macro|MPI_SCSIIO_CONTROL_RESERVED2
mdefine_line|#define MPI_SCSIIO_CONTROL_RESERVED2            (0x00010000)
multiline_comment|/* SCSIIO reply structure */
DECL|struct|_MSG_SCSI_IO_REPLY
r_typedef
r_struct
id|_MSG_SCSI_IO_REPLY
(brace
DECL|member|TargetID
id|U8
id|TargetID
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Bus
id|U8
id|Bus
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|MsgLength
id|U8
id|MsgLength
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|Function
id|U8
id|Function
suffix:semicolon
multiline_comment|/* 03h */
DECL|member|CDBLength
id|U8
id|CDBLength
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|SenseBufferLength
id|U8
id|SenseBufferLength
suffix:semicolon
multiline_comment|/* 05h */
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
multiline_comment|/* 06h */
DECL|member|MsgFlags
id|U8
id|MsgFlags
suffix:semicolon
multiline_comment|/* 07h */
DECL|member|MsgContext
id|U32
id|MsgContext
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|SCSIStatus
id|U8
id|SCSIStatus
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|SCSIState
id|U8
id|SCSIState
suffix:semicolon
multiline_comment|/* 0Dh */
DECL|member|IOCStatus
id|U16
id|IOCStatus
suffix:semicolon
multiline_comment|/* 0Eh */
DECL|member|IOCLogInfo
id|U32
id|IOCLogInfo
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|TransferCount
id|U32
id|TransferCount
suffix:semicolon
multiline_comment|/* 14h */
DECL|member|SenseCount
id|U32
id|SenseCount
suffix:semicolon
multiline_comment|/* 18h */
DECL|member|ResponseInfo
id|U32
id|ResponseInfo
suffix:semicolon
multiline_comment|/* 1Ch */
DECL|typedef|MSG_SCSI_IO_REPLY
DECL|typedef|PTR_MSG_SCSI_IO_REPLY
)brace
id|MSG_SCSI_IO_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_SCSI_IO_REPLY
comma
DECL|typedef|SCSIIOReply_t
DECL|typedef|pSCSIIOReply_t
id|SCSIIOReply_t
comma
id|MPI_POINTER
id|pSCSIIOReply_t
suffix:semicolon
multiline_comment|/* SCSIIO Reply SCSIStatus values (SAM-2 status codes) */
DECL|macro|MPI_SCSI_STATUS_SUCCESS
mdefine_line|#define MPI_SCSI_STATUS_SUCCESS                 (0x00)
DECL|macro|MPI_SCSI_STATUS_CHECK_CONDITION
mdefine_line|#define MPI_SCSI_STATUS_CHECK_CONDITION         (0x02)
DECL|macro|MPI_SCSI_STATUS_CONDITION_MET
mdefine_line|#define MPI_SCSI_STATUS_CONDITION_MET           (0x04)
DECL|macro|MPI_SCSI_STATUS_BUSY
mdefine_line|#define MPI_SCSI_STATUS_BUSY                    (0x08)
DECL|macro|MPI_SCSI_STATUS_INTERMEDIATE
mdefine_line|#define MPI_SCSI_STATUS_INTERMEDIATE            (0x10)
DECL|macro|MPI_SCSI_STATUS_INTERMEDIATE_CONDMET
mdefine_line|#define MPI_SCSI_STATUS_INTERMEDIATE_CONDMET    (0x14)
DECL|macro|MPI_SCSI_STATUS_RESERVATION_CONFLICT
mdefine_line|#define MPI_SCSI_STATUS_RESERVATION_CONFLICT    (0x18)
DECL|macro|MPI_SCSI_STATUS_COMMAND_TERMINATED
mdefine_line|#define MPI_SCSI_STATUS_COMMAND_TERMINATED      (0x22)
DECL|macro|MPI_SCSI_STATUS_TASK_SET_FULL
mdefine_line|#define MPI_SCSI_STATUS_TASK_SET_FULL           (0x28)
DECL|macro|MPI_SCSI_STATUS_ACA_ACTIVE
mdefine_line|#define MPI_SCSI_STATUS_ACA_ACTIVE              (0x30)
multiline_comment|/* SCSIIO Reply SCSIState values */
DECL|macro|MPI_SCSI_STATE_AUTOSENSE_VALID
mdefine_line|#define MPI_SCSI_STATE_AUTOSENSE_VALID          (0x01)
DECL|macro|MPI_SCSI_STATE_AUTOSENSE_FAILED
mdefine_line|#define MPI_SCSI_STATE_AUTOSENSE_FAILED         (0x02)
DECL|macro|MPI_SCSI_STATE_NO_SCSI_STATUS
mdefine_line|#define MPI_SCSI_STATE_NO_SCSI_STATUS           (0x04)
DECL|macro|MPI_SCSI_STATE_TERMINATED
mdefine_line|#define MPI_SCSI_STATE_TERMINATED               (0x08)
DECL|macro|MPI_SCSI_STATE_RESPONSE_INFO_VALID
mdefine_line|#define MPI_SCSI_STATE_RESPONSE_INFO_VALID      (0x10)
DECL|macro|MPI_SCSI_STATE_QUEUE_TAG_REJECTED
mdefine_line|#define MPI_SCSI_STATE_QUEUE_TAG_REJECTED       (0x20)
multiline_comment|/* SCSIIO Reply ResponseInfo values */
multiline_comment|/* (FCP-1 RSP_CODE values and SPI-3 Packetized Failure codes) */
DECL|macro|MPI_SCSI_RSP_INFO_FUNCTION_COMPLETE
mdefine_line|#define MPI_SCSI_RSP_INFO_FUNCTION_COMPLETE     (0x00000000)
DECL|macro|MPI_SCSI_RSP_INFO_FCP_BURST_LEN_ERROR
mdefine_line|#define MPI_SCSI_RSP_INFO_FCP_BURST_LEN_ERROR   (0x01000000)
DECL|macro|MPI_SCSI_RSP_INFO_CMND_FIELDS_INVALID
mdefine_line|#define MPI_SCSI_RSP_INFO_CMND_FIELDS_INVALID   (0x02000000)
DECL|macro|MPI_SCSI_RSP_INFO_FCP_DATA_RO_ERROR
mdefine_line|#define MPI_SCSI_RSP_INFO_FCP_DATA_RO_ERROR     (0x03000000)
DECL|macro|MPI_SCSI_RSP_INFO_TASK_MGMT_UNSUPPORTED
mdefine_line|#define MPI_SCSI_RSP_INFO_TASK_MGMT_UNSUPPORTED (0x04000000)
DECL|macro|MPI_SCSI_RSP_INFO_TASK_MGMT_FAILED
mdefine_line|#define MPI_SCSI_RSP_INFO_TASK_MGMT_FAILED      (0x05000000)
DECL|macro|MPI_SCSI_RSP_INFO_SPI_LQ_INVALID_TYPE
mdefine_line|#define MPI_SCSI_RSP_INFO_SPI_LQ_INVALID_TYPE   (0x06000000)
multiline_comment|/****************************************************************************/
multiline_comment|/*  SCSI Task Management messages                                           */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_SCSI_TASK_MGMT
r_typedef
r_struct
id|_MSG_SCSI_TASK_MGMT
(brace
DECL|member|TargetID
id|U8
id|TargetID
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Bus
id|U8
id|Bus
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|ChainOffset
id|U8
id|ChainOffset
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|Function
id|U8
id|Function
suffix:semicolon
multiline_comment|/* 03h */
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|TaskType
id|U8
id|TaskType
suffix:semicolon
multiline_comment|/* 05h */
DECL|member|Reserved1
id|U8
id|Reserved1
suffix:semicolon
multiline_comment|/* 06h */
DECL|member|MsgFlags
id|U8
id|MsgFlags
suffix:semicolon
multiline_comment|/* 07h */
DECL|member|MsgContext
id|U32
id|MsgContext
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|LUN
id|U8
id|LUN
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|Reserved2
id|U32
id|Reserved2
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* 14h */
DECL|member|TaskMsgContext
id|U32
id|TaskMsgContext
suffix:semicolon
multiline_comment|/* 30h */
DECL|typedef|MSG_SCSI_TASK_MGMT
DECL|typedef|PTR_SCSI_TASK_MGMT
)brace
id|MSG_SCSI_TASK_MGMT
comma
id|MPI_POINTER
id|PTR_SCSI_TASK_MGMT
comma
DECL|typedef|SCSITaskMgmt_t
DECL|typedef|pSCSITaskMgmt_t
id|SCSITaskMgmt_t
comma
id|MPI_POINTER
id|pSCSITaskMgmt_t
suffix:semicolon
multiline_comment|/* TaskType values */
DECL|macro|MPI_SCSITASKMGMT_TASKTYPE_ABORT_TASK
mdefine_line|#define MPI_SCSITASKMGMT_TASKTYPE_ABORT_TASK            (0x01)
DECL|macro|MPI_SCSITASKMGMT_TASKTYPE_ABRT_TASK_SET
mdefine_line|#define MPI_SCSITASKMGMT_TASKTYPE_ABRT_TASK_SET         (0x02)
DECL|macro|MPI_SCSITASKMGMT_TASKTYPE_TARGET_RESET
mdefine_line|#define MPI_SCSITASKMGMT_TASKTYPE_TARGET_RESET          (0x03)
DECL|macro|MPI_SCSITASKMGMT_TASKTYPE_RESET_BUS
mdefine_line|#define MPI_SCSITASKMGMT_TASKTYPE_RESET_BUS             (0x04)
DECL|macro|MPI_SCSITASKMGMT_TASKTYPE_LOGICAL_UNIT_RESET
mdefine_line|#define MPI_SCSITASKMGMT_TASKTYPE_LOGICAL_UNIT_RESET    (0x05)
multiline_comment|/* MsgFlags bits */
DECL|macro|MPI_SCSITASKMGMT_MSGFLAGS_TARGET_RESET_OPTION
mdefine_line|#define MPI_SCSITASKMGMT_MSGFLAGS_TARGET_RESET_OPTION   (0x00)
DECL|macro|MPI_SCSITASKMGMT_MSGFLAGS_LIP_RESET_OPTION
mdefine_line|#define MPI_SCSITASKMGMT_MSGFLAGS_LIP_RESET_OPTION      (0x02)
DECL|macro|MPI_SCSITASKMGMT_MSGFLAGS_LIPRESET_RESET_OPTION
mdefine_line|#define MPI_SCSITASKMGMT_MSGFLAGS_LIPRESET_RESET_OPTION (0x04)
multiline_comment|/* SCSI Task Management Reply */
DECL|struct|_MSG_SCSI_TASK_MGMT_REPLY
r_typedef
r_struct
id|_MSG_SCSI_TASK_MGMT_REPLY
(brace
DECL|member|TargetID
id|U8
id|TargetID
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Bus
id|U8
id|Bus
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|MsgLength
id|U8
id|MsgLength
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|Function
id|U8
id|Function
suffix:semicolon
multiline_comment|/* 03h */
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|TaskType
id|U8
id|TaskType
suffix:semicolon
multiline_comment|/* 05h */
DECL|member|Reserved1
id|U8
id|Reserved1
suffix:semicolon
multiline_comment|/* 06h */
DECL|member|MsgFlags
id|U8
id|MsgFlags
suffix:semicolon
multiline_comment|/* 07h */
DECL|member|MsgContext
id|U32
id|MsgContext
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|Reserved2
id|U8
id|Reserved2
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|IOCStatus
id|U16
id|IOCStatus
suffix:semicolon
multiline_comment|/* 0Eh */
DECL|member|IOCLogInfo
id|U32
id|IOCLogInfo
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|TerminationCount
id|U32
id|TerminationCount
suffix:semicolon
multiline_comment|/* 14h */
DECL|typedef|MSG_SCSI_TASK_MGMT_REPLY
DECL|typedef|PTR_MSG_SCSI_TASK_MGMT_REPLY
)brace
id|MSG_SCSI_TASK_MGMT_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_SCSI_TASK_MGMT_REPLY
comma
DECL|typedef|SCSITaskMgmtReply_t
DECL|typedef|pSCSITaskMgmtReply_t
id|SCSITaskMgmtReply_t
comma
id|MPI_POINTER
id|pSCSITaskMgmtReply_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/*  SCSI Enclosure Processor messages                                       */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_SEP_REQUEST
r_typedef
r_struct
id|_MSG_SEP_REQUEST
(brace
DECL|member|TargetID
id|U8
id|TargetID
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Bus
id|U8
id|Bus
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|ChainOffset
id|U8
id|ChainOffset
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|Function
id|U8
id|Function
suffix:semicolon
multiline_comment|/* 03h */
DECL|member|Action
id|U8
id|Action
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Reserved1
id|U8
id|Reserved1
suffix:semicolon
multiline_comment|/* 05h */
DECL|member|Reserved2
id|U8
id|Reserved2
suffix:semicolon
multiline_comment|/* 06h */
DECL|member|MsgFlags
id|U8
id|MsgFlags
suffix:semicolon
multiline_comment|/* 07h */
DECL|member|MsgContext
id|U32
id|MsgContext
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|SlotStatus
id|U32
id|SlotStatus
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|typedef|MSG_SEP_REQUEST
DECL|typedef|PTR_MSG_SEP_REQUEST
)brace
id|MSG_SEP_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_SEP_REQUEST
comma
DECL|typedef|SEPRequest_t
DECL|typedef|pSEPRequest_t
id|SEPRequest_t
comma
id|MPI_POINTER
id|pSEPRequest_t
suffix:semicolon
multiline_comment|/* Action defines */
DECL|macro|MPI_SEP_REQ_ACTION_WRITE_STATUS
mdefine_line|#define MPI_SEP_REQ_ACTION_WRITE_STATUS                 (0x00)
DECL|macro|MPI_SEP_REQ_ACTION_READ_STATUS
mdefine_line|#define MPI_SEP_REQ_ACTION_READ_STATUS                  (0x01)
multiline_comment|/* SlotStatus bits for MSG_SEP_REQUEST */
DECL|macro|MPI_SEP_REQ_SLOTSTATUS_NO_ERROR
mdefine_line|#define MPI_SEP_REQ_SLOTSTATUS_NO_ERROR                 (0x00000001)
DECL|macro|MPI_SEP_REQ_SLOTSTATUS_DEV_FAULTY
mdefine_line|#define MPI_SEP_REQ_SLOTSTATUS_DEV_FAULTY               (0x00000002)
DECL|macro|MPI_SEP_REQ_SLOTSTATUS_DEV_REBUILDING
mdefine_line|#define MPI_SEP_REQ_SLOTSTATUS_DEV_REBUILDING           (0x00000004)
DECL|macro|MPI_SEP_REQ_SLOTSTATUS_IN_FAILED_ARRAY
mdefine_line|#define MPI_SEP_REQ_SLOTSTATUS_IN_FAILED_ARRAY          (0x00000008)
DECL|macro|MPI_SEP_REQ_SLOTSTATUS_IN_CRITICAL_ARRAY
mdefine_line|#define MPI_SEP_REQ_SLOTSTATUS_IN_CRITICAL_ARRAY        (0x00000010)
DECL|macro|MPI_SEP_REQ_SLOTSTATUS_PARITY_CHECK
mdefine_line|#define MPI_SEP_REQ_SLOTSTATUS_PARITY_CHECK             (0x00000020)
DECL|macro|MPI_SEP_REQ_SLOTSTATUS_PREDICTED_FAULT
mdefine_line|#define MPI_SEP_REQ_SLOTSTATUS_PREDICTED_FAULT          (0x00000040)
DECL|macro|MPI_SEP_REQ_SLOTSTATUS_UNCONFIGURED
mdefine_line|#define MPI_SEP_REQ_SLOTSTATUS_UNCONFIGURED             (0x00000080)
DECL|macro|MPI_SEP_REQ_SLOTSTATUS_HOT_SPARE
mdefine_line|#define MPI_SEP_REQ_SLOTSTATUS_HOT_SPARE                (0x00000100)
DECL|macro|MPI_SEP_REQ_SLOTSTATUS_REBUILD_STOPPED
mdefine_line|#define MPI_SEP_REQ_SLOTSTATUS_REBUILD_STOPPED          (0x00000200)
DECL|macro|MPI_SEP_REQ_SLOTSTATUS_IDENTIFY_REQUEST
mdefine_line|#define MPI_SEP_REQ_SLOTSTATUS_IDENTIFY_REQUEST         (0x00020000)
DECL|macro|MPI_SEP_REQ_SLOTSTATUS_REQUEST_REMOVE
mdefine_line|#define MPI_SEP_REQ_SLOTSTATUS_REQUEST_REMOVE           (0x00040000)
DECL|macro|MPI_SEP_REQ_SLOTSTATUS_REQUEST_INSERT
mdefine_line|#define MPI_SEP_REQ_SLOTSTATUS_REQUEST_INSERT           (0x00080000)
DECL|macro|MPI_SEP_REQ_SLOTSTATUS_DO_NOT_MOVE
mdefine_line|#define MPI_SEP_REQ_SLOTSTATUS_DO_NOT_MOVE              (0x00400000)
DECL|macro|MPI_SEP_REQ_SLOTSTATUS_B_ENABLE_BYPASS
mdefine_line|#define MPI_SEP_REQ_SLOTSTATUS_B_ENABLE_BYPASS          (0x04000000)
DECL|macro|MPI_SEP_REQ_SLOTSTATUS_A_ENABLE_BYPASS
mdefine_line|#define MPI_SEP_REQ_SLOTSTATUS_A_ENABLE_BYPASS          (0x08000000)
DECL|macro|MPI_SEP_REQ_SLOTSTATUS_DEV_OFF
mdefine_line|#define MPI_SEP_REQ_SLOTSTATUS_DEV_OFF                  (0x10000000)
DECL|macro|MPI_SEP_REQ_SLOTSTATUS_SWAP_RESET
mdefine_line|#define MPI_SEP_REQ_SLOTSTATUS_SWAP_RESET               (0x80000000)
DECL|struct|_MSG_SEP_REPLY
r_typedef
r_struct
id|_MSG_SEP_REPLY
(brace
DECL|member|TargetID
id|U8
id|TargetID
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Bus
id|U8
id|Bus
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|MsgLength
id|U8
id|MsgLength
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|Function
id|U8
id|Function
suffix:semicolon
multiline_comment|/* 03h */
DECL|member|Action
id|U8
id|Action
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Reserved1
id|U8
id|Reserved1
suffix:semicolon
multiline_comment|/* 05h */
DECL|member|Reserved2
id|U8
id|Reserved2
suffix:semicolon
multiline_comment|/* 06h */
DECL|member|MsgFlags
id|U8
id|MsgFlags
suffix:semicolon
multiline_comment|/* 07h */
DECL|member|MsgContext
id|U32
id|MsgContext
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|Reserved3
id|U16
id|Reserved3
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|IOCStatus
id|U16
id|IOCStatus
suffix:semicolon
multiline_comment|/* 0Eh */
DECL|member|IOCLogInfo
id|U32
id|IOCLogInfo
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|SlotStatus
id|U32
id|SlotStatus
suffix:semicolon
multiline_comment|/* 14h */
DECL|typedef|MSG_SEP_REPLY
DECL|typedef|PTR_MSG_SEP_REPLY
)brace
id|MSG_SEP_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_SEP_REPLY
comma
DECL|typedef|SEPReply_t
DECL|typedef|pSEPReply_t
id|SEPReply_t
comma
id|MPI_POINTER
id|pSEPReply_t
suffix:semicolon
multiline_comment|/* SlotStatus bits for MSG_SEP_REPLY */
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_NO_ERROR
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_NO_ERROR               (0x00000001)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_DEV_FAULTY
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_DEV_FAULTY             (0x00000002)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_DEV_REBUILDING
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_DEV_REBUILDING         (0x00000004)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_IN_FAILED_ARRAY
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_IN_FAILED_ARRAY        (0x00000008)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_IN_CRITICAL_ARRAY
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_IN_CRITICAL_ARRAY      (0x00000010)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_PARITY_CHECK
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_PARITY_CHECK           (0x00000020)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_PREDICTED_FAULT
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_PREDICTED_FAULT        (0x00000040)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_UNCONFIGURED
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_UNCONFIGURED           (0x00000080)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_HOT_SPARE
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_HOT_SPARE              (0x00000100)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_REBUILD_STOPPED
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_REBUILD_STOPPED        (0x00000200)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_REPORT
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_REPORT                 (0x00010000)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_IDENTIFY_REQUEST
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_IDENTIFY_REQUEST       (0x00020000)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_REMOVE_READY
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_REMOVE_READY           (0x00040000)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_INSERT_READY
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_INSERT_READY           (0x00080000)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_DO_NOT_REMOVE
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_DO_NOT_REMOVE          (0x00400000)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_B_BYPASS_ENABLED
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_B_BYPASS_ENABLED       (0x01000000)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_A_BYPASS_ENABLED
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_A_BYPASS_ENABLED       (0x02000000)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_B_ENABLE_BYPASS
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_B_ENABLE_BYPASS        (0x04000000)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_A_ENABLE_BYPASS
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_A_ENABLE_BYPASS        (0x08000000)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_DEV_OFF
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_DEV_OFF                (0x10000000)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_FAULT_SENSED
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_FAULT_SENSED           (0x40000000)
DECL|macro|MPI_SEP_REPLY_SLOTSTATUS_SWAPPED
mdefine_line|#define MPI_SEP_REPLY_SLOTSTATUS_SWAPPED                (0x80000000)
macro_line|#endif
eof
