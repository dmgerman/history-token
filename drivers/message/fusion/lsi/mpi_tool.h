multiline_comment|/*&n; *  Copyright (c) 2001-2003 LSI Logic Corporation.&n; *&n; *&n; *           Name:  mpi_tool.h&n; *          Title:  MPI Toolbox structures and definitions&n; *  Creation Date:  July 30, 2001&n; *&n; *    mpi_tool.h Version:  01.05.xx&n; *&n; *  Version History&n; *  ---------------&n; *&n; *  Date      Version   Description&n; *  --------  --------  ------------------------------------------------------&n; *  08-08-01  01.02.01  Original release.&n; *  08-29-01  01.02.02  Added DIAG_DATA_UPLOAD_HEADER and related defines.&n; *  --------------------------------------------------------------------------&n; */
macro_line|#ifndef MPI_TOOL_H
DECL|macro|MPI_TOOL_H
mdefine_line|#define MPI_TOOL_H
DECL|macro|MPI_TOOLBOX_CLEAN_TOOL
mdefine_line|#define MPI_TOOLBOX_CLEAN_TOOL                      (0x00)
DECL|macro|MPI_TOOLBOX_MEMORY_MOVE_TOOL
mdefine_line|#define MPI_TOOLBOX_MEMORY_MOVE_TOOL                (0x01)
DECL|macro|MPI_TOOLBOX_DIAG_DATA_UPLOAD_TOOL
mdefine_line|#define MPI_TOOLBOX_DIAG_DATA_UPLOAD_TOOL           (0x02)
DECL|macro|MPI_TOOLBOX_ISTWI_READ_WRITE_TOOL
mdefine_line|#define MPI_TOOLBOX_ISTWI_READ_WRITE_TOOL           (0x03)
DECL|macro|MPI_TOOLBOX_FC_MANAGEMENT_TOOL
mdefine_line|#define MPI_TOOLBOX_FC_MANAGEMENT_TOOL              (0x04)
multiline_comment|/****************************************************************************/
multiline_comment|/* Toolbox reply                                                            */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_TOOLBOX_REPLY
r_typedef
r_struct
id|_MSG_TOOLBOX_REPLY
(brace
DECL|member|Tool
id|U8
id|Tool
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved
id|U8
id|Reserved
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
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 04h */
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
DECL|typedef|MSG_TOOLBOX_REPLY
DECL|typedef|PTR_MSG_TOOLBOX_REPLY
)brace
id|MSG_TOOLBOX_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_TOOLBOX_REPLY
comma
DECL|typedef|ToolboxReply_t
DECL|typedef|pToolboxReply_t
id|ToolboxReply_t
comma
id|MPI_POINTER
id|pToolboxReply_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/* Toolbox Clean Tool request                                               */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_TOOLBOX_CLEAN_REQUEST
r_typedef
r_struct
id|_MSG_TOOLBOX_CLEAN_REQUEST
(brace
DECL|member|Tool
id|U8
id|Tool
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved
id|U8
id|Reserved
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
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 04h */
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
DECL|member|Flags
id|U32
id|Flags
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|typedef|MSG_TOOLBOX_CLEAN_REQUEST
DECL|typedef|PTR_MSG_TOOLBOX_CLEAN_REQUEST
)brace
id|MSG_TOOLBOX_CLEAN_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_TOOLBOX_CLEAN_REQUEST
comma
DECL|typedef|ToolboxCleanRequest_t
DECL|typedef|pToolboxCleanRequest_t
id|ToolboxCleanRequest_t
comma
id|MPI_POINTER
id|pToolboxCleanRequest_t
suffix:semicolon
DECL|macro|MPI_TOOLBOX_CLEAN_NVSRAM
mdefine_line|#define MPI_TOOLBOX_CLEAN_NVSRAM                    (0x00000001)
DECL|macro|MPI_TOOLBOX_CLEAN_SEEPROM
mdefine_line|#define MPI_TOOLBOX_CLEAN_SEEPROM                   (0x00000002)
DECL|macro|MPI_TOOLBOX_CLEAN_FLASH
mdefine_line|#define MPI_TOOLBOX_CLEAN_FLASH                     (0x00000004)
DECL|macro|MPI_TOOLBOX_CLEAN_BOOTLOADER
mdefine_line|#define MPI_TOOLBOX_CLEAN_BOOTLOADER                (0x04000000)
DECL|macro|MPI_TOOLBOX_CLEAN_FW_BACKUP
mdefine_line|#define MPI_TOOLBOX_CLEAN_FW_BACKUP                 (0x08000000)
DECL|macro|MPI_TOOLBOX_CLEAN_FW_CURRENT
mdefine_line|#define MPI_TOOLBOX_CLEAN_FW_CURRENT                (0x10000000)
DECL|macro|MPI_TOOLBOX_CLEAN_OTHER_PERSIST_PAGES
mdefine_line|#define MPI_TOOLBOX_CLEAN_OTHER_PERSIST_PAGES       (0x20000000)
DECL|macro|MPI_TOOLBOX_CLEAN_PERSIST_MANUFACT_PAGES
mdefine_line|#define MPI_TOOLBOX_CLEAN_PERSIST_MANUFACT_PAGES    (0x40000000)
DECL|macro|MPI_TOOLBOX_CLEAN_BOOT_SERVICES
mdefine_line|#define MPI_TOOLBOX_CLEAN_BOOT_SERVICES             (0x80000000)
multiline_comment|/****************************************************************************/
multiline_comment|/* Toolbox Memory Move request                                              */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_TOOLBOX_MEM_MOVE_REQUEST
r_typedef
r_struct
id|_MSG_TOOLBOX_MEM_MOVE_REQUEST
(brace
DECL|member|Tool
id|U8
id|Tool
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved
id|U8
id|Reserved
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
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 04h */
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
DECL|member|SGL
id|SGE_SIMPLE_UNION
id|SGL
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|typedef|MSG_TOOLBOX_MEM_MOVE_REQUEST
DECL|typedef|PTR_MSG_TOOLBOX_MEM_MOVE_REQUEST
)brace
id|MSG_TOOLBOX_MEM_MOVE_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_TOOLBOX_MEM_MOVE_REQUEST
comma
DECL|typedef|ToolboxMemMoveRequest_t
DECL|typedef|pToolboxMemMoveRequest_t
id|ToolboxMemMoveRequest_t
comma
id|MPI_POINTER
id|pToolboxMemMoveRequest_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/* Toolbox Diagnostic Data Upload request                                   */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_TOOLBOX_DIAG_DATA_UPLOAD_REQUEST
r_typedef
r_struct
id|_MSG_TOOLBOX_DIAG_DATA_UPLOAD_REQUEST
(brace
DECL|member|Tool
id|U8
id|Tool
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved
id|U8
id|Reserved
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
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 04h */
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
DECL|member|Flags
id|U32
id|Flags
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|Reserved3
id|U32
id|Reserved3
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|SGL
id|SGE_SIMPLE_UNION
id|SGL
suffix:semicolon
multiline_comment|/* 14h */
DECL|typedef|MSG_TOOLBOX_DIAG_DATA_UPLOAD_REQUEST
DECL|typedef|PTR_MSG_TOOLBOX_DIAG_DATA_UPLOAD_REQUEST
)brace
id|MSG_TOOLBOX_DIAG_DATA_UPLOAD_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_TOOLBOX_DIAG_DATA_UPLOAD_REQUEST
comma
DECL|typedef|ToolboxDiagDataUploadRequest_t
DECL|typedef|pToolboxDiagDataUploadRequest_t
id|ToolboxDiagDataUploadRequest_t
comma
id|MPI_POINTER
id|pToolboxDiagDataUploadRequest_t
suffix:semicolon
DECL|struct|_DIAG_DATA_UPLOAD_HEADER
r_typedef
r_struct
id|_DIAG_DATA_UPLOAD_HEADER
(brace
DECL|member|DiagDataLength
id|U32
id|DiagDataLength
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|FormatCode
id|U8
id|FormatCode
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
multiline_comment|/* 05h */
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 06h */
DECL|typedef|DIAG_DATA_UPLOAD_HEADER
DECL|typedef|PTR_DIAG_DATA_UPLOAD_HEADER
)brace
id|DIAG_DATA_UPLOAD_HEADER
comma
id|MPI_POINTER
id|PTR_DIAG_DATA_UPLOAD_HEADER
comma
DECL|typedef|DiagDataUploadHeader_t
DECL|typedef|pDiagDataUploadHeader_t
id|DiagDataUploadHeader_t
comma
id|MPI_POINTER
id|pDiagDataUploadHeader_t
suffix:semicolon
DECL|macro|MPI_TB_DIAG_FORMAT_SCSI_PRINTF_1
mdefine_line|#define MPI_TB_DIAG_FORMAT_SCSI_PRINTF_1            (0x01)
DECL|macro|MPI_TB_DIAG_FORMAT_SCSI_2
mdefine_line|#define MPI_TB_DIAG_FORMAT_SCSI_2                   (0x02)
DECL|macro|MPI_TB_DIAG_FORMAT_SCSI_3
mdefine_line|#define MPI_TB_DIAG_FORMAT_SCSI_3                   (0x03)
DECL|macro|MPI_TB_DIAG_FORMAT_FC_TRACE_1
mdefine_line|#define MPI_TB_DIAG_FORMAT_FC_TRACE_1               (0x04)
multiline_comment|/****************************************************************************/
multiline_comment|/* Toolbox ISTWI Read Write request                                         */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_TOOLBOX_ISTWI_READ_WRITE_REQUEST
r_typedef
r_struct
id|_MSG_TOOLBOX_ISTWI_READ_WRITE_REQUEST
(brace
DECL|member|Tool
id|U8
id|Tool
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved
id|U8
id|Reserved
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
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 04h */
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
DECL|member|Flags
id|U8
id|Flags
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|BusNum
id|U8
id|BusNum
suffix:semicolon
multiline_comment|/* 0Dh */
DECL|member|Reserved3
id|U16
id|Reserved3
suffix:semicolon
multiline_comment|/* 0Eh */
DECL|member|NumAddressBytes
id|U8
id|NumAddressBytes
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|Reserved4
id|U8
id|Reserved4
suffix:semicolon
multiline_comment|/* 11h */
DECL|member|DataLength
id|U16
id|DataLength
suffix:semicolon
multiline_comment|/* 12h */
DECL|member|DeviceAddr
id|U8
id|DeviceAddr
suffix:semicolon
multiline_comment|/* 14h */
DECL|member|Addr1
id|U8
id|Addr1
suffix:semicolon
multiline_comment|/* 15h */
DECL|member|Addr2
id|U8
id|Addr2
suffix:semicolon
multiline_comment|/* 16h */
DECL|member|Addr3
id|U8
id|Addr3
suffix:semicolon
multiline_comment|/* 17h */
DECL|member|Reserved5
id|U32
id|Reserved5
suffix:semicolon
multiline_comment|/* 18h */
DECL|member|SGL
id|SGE_SIMPLE_UNION
id|SGL
suffix:semicolon
multiline_comment|/* 1Ch */
DECL|typedef|MSG_TOOLBOX_ISTWI_READ_WRITE_REQUEST
DECL|typedef|PTR_MSG_TOOLBOX_ISTWI_READ_WRITE_REQUEST
)brace
id|MSG_TOOLBOX_ISTWI_READ_WRITE_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_TOOLBOX_ISTWI_READ_WRITE_REQUEST
comma
DECL|typedef|ToolboxIstwiReadWriteRequest_t
DECL|typedef|pToolboxIstwiReadWriteRequest_t
id|ToolboxIstwiReadWriteRequest_t
comma
id|MPI_POINTER
id|pToolboxIstwiReadWriteRequest_t
suffix:semicolon
DECL|macro|MPI_TB_ISTWI_FLAGS_WRITE
mdefine_line|#define MPI_TB_ISTWI_FLAGS_WRITE                    (0x00)
DECL|macro|MPI_TB_ISTWI_FLAGS_READ
mdefine_line|#define MPI_TB_ISTWI_FLAGS_READ                     (0x01)
multiline_comment|/****************************************************************************/
multiline_comment|/* Toolbox FC Management request                                            */
multiline_comment|/****************************************************************************/
multiline_comment|/* ActionInfo for Bus and TargetId */
DECL|struct|_MPI_TB_FC_MANAGE_BUS_TID_AI
r_typedef
r_struct
id|_MPI_TB_FC_MANAGE_BUS_TID_AI
(brace
DECL|member|Reserved
id|U16
id|Reserved
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Bus
id|U8
id|Bus
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|TargetId
id|U8
id|TargetId
suffix:semicolon
multiline_comment|/* 03h */
DECL|typedef|MPI_TB_FC_MANAGE_BUS_TID_AI
DECL|typedef|PTR_MPI_TB_FC_MANAGE_BUS_TID_AI
)brace
id|MPI_TB_FC_MANAGE_BUS_TID_AI
comma
id|MPI_POINTER
id|PTR_MPI_TB_FC_MANAGE_BUS_TID_AI
comma
DECL|typedef|MpiTbFcManageBusTidAi_t
DECL|typedef|pMpiTbFcManageBusTidAi_t
id|MpiTbFcManageBusTidAi_t
comma
id|MPI_POINTER
id|pMpiTbFcManageBusTidAi_t
suffix:semicolon
multiline_comment|/* ActionInfo for port identifier */
DECL|struct|_MPI_TB_FC_MANAGE_PID_AI
r_typedef
r_struct
id|_MPI_TB_FC_MANAGE_PID_AI
(brace
DECL|member|PortIdentifier
id|U32
id|PortIdentifier
suffix:semicolon
multiline_comment|/* 00h */
DECL|typedef|MPI_TB_FC_MANAGE_PID_AI
DECL|typedef|PTR_MPI_TB_FC_MANAGE_PID_AI
)brace
id|MPI_TB_FC_MANAGE_PID_AI
comma
id|MPI_POINTER
id|PTR_MPI_TB_FC_MANAGE_PID_AI
comma
DECL|typedef|MpiTbFcManagePidAi_t
DECL|typedef|pMpiTbFcManagePidAi_t
id|MpiTbFcManagePidAi_t
comma
id|MPI_POINTER
id|pMpiTbFcManagePidAi_t
suffix:semicolon
multiline_comment|/* union of ActionInfo */
DECL|union|_MPI_TB_FC_MANAGE_AI_UNION
r_typedef
r_union
id|_MPI_TB_FC_MANAGE_AI_UNION
(brace
DECL|member|BusTid
id|MPI_TB_FC_MANAGE_BUS_TID_AI
id|BusTid
suffix:semicolon
DECL|member|Port
id|MPI_TB_FC_MANAGE_PID_AI
id|Port
suffix:semicolon
DECL|typedef|MPI_TB_FC_MANAGE_AI_UNION
DECL|typedef|PTR_MPI_TB_FC_MANAGE_AI_UNION
)brace
id|MPI_TB_FC_MANAGE_AI_UNION
comma
id|MPI_POINTER
id|PTR_MPI_TB_FC_MANAGE_AI_UNION
comma
DECL|typedef|MpiTbFcManageAiUnion_t
DECL|typedef|pMpiTbFcManageAiUnion_t
id|MpiTbFcManageAiUnion_t
comma
id|MPI_POINTER
id|pMpiTbFcManageAiUnion_t
suffix:semicolon
DECL|struct|_MSG_TOOLBOX_FC_MANAGE_REQUEST
r_typedef
r_struct
id|_MSG_TOOLBOX_FC_MANAGE_REQUEST
(brace
DECL|member|Tool
id|U8
id|Tool
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved
id|U8
id|Reserved
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
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 04h */
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
DECL|member|Action
id|U8
id|Action
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|Reserved3
id|U8
id|Reserved3
suffix:semicolon
multiline_comment|/* 0Dh */
DECL|member|Reserved4
id|U16
id|Reserved4
suffix:semicolon
multiline_comment|/* 0Eh */
DECL|member|ActionInfo
id|MPI_TB_FC_MANAGE_AI_UNION
id|ActionInfo
suffix:semicolon
multiline_comment|/* 10h */
DECL|typedef|MSG_TOOLBOX_FC_MANAGE_REQUEST
DECL|typedef|PTR_MSG_TOOLBOX_FC_MANAGE_REQUEST
)brace
id|MSG_TOOLBOX_FC_MANAGE_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_TOOLBOX_FC_MANAGE_REQUEST
comma
DECL|typedef|ToolboxFcManageRequest_t
DECL|typedef|pToolboxFcManageRequest_t
id|ToolboxFcManageRequest_t
comma
id|MPI_POINTER
id|pToolboxFcManageRequest_t
suffix:semicolon
multiline_comment|/* defines for the Action field */
DECL|macro|MPI_TB_FC_MANAGE_ACTION_DISC_ALL
mdefine_line|#define MPI_TB_FC_MANAGE_ACTION_DISC_ALL            (0x00)
DECL|macro|MPI_TB_FC_MANAGE_ACTION_DISC_PID
mdefine_line|#define MPI_TB_FC_MANAGE_ACTION_DISC_PID            (0x01)
DECL|macro|MPI_TB_FC_MANAGE_ACTION_DISC_BUS_TID
mdefine_line|#define MPI_TB_FC_MANAGE_ACTION_DISC_BUS_TID        (0x02)
multiline_comment|/****************************************************************************/
multiline_comment|/* Diagnostic Buffer Post request                                           */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_DIAG_BUFFER_POST_REQUEST
r_typedef
r_struct
id|_MSG_DIAG_BUFFER_POST_REQUEST
(brace
DECL|member|TraceLevel
id|U8
id|TraceLevel
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|BufferType
id|U8
id|BufferType
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
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 04h */
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
DECL|member|ExtendedType
id|U32
id|ExtendedType
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|BufferLength
id|U32
id|BufferLength
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|ProductSpecific
id|U32
id|ProductSpecific
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 14h */
DECL|member|Reserved3
id|U32
id|Reserved3
suffix:semicolon
multiline_comment|/* 18h */
DECL|member|SGL
id|SGE_SIMPLE_UNION
id|SGL
suffix:semicolon
multiline_comment|/* 28h */
DECL|typedef|MSG_DIAG_BUFFER_POST_REQUEST
DECL|typedef|PTR_MSG_DIAG_BUFFER_POST_REQUEST
)brace
id|MSG_DIAG_BUFFER_POST_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_DIAG_BUFFER_POST_REQUEST
comma
DECL|typedef|DiagBufferPostRequest_t
DECL|typedef|pDiagBufferPostRequest_t
id|DiagBufferPostRequest_t
comma
id|MPI_POINTER
id|pDiagBufferPostRequest_t
suffix:semicolon
DECL|macro|MPI_DIAG_BUF_TYPE_TRACE
mdefine_line|#define MPI_DIAG_BUF_TYPE_TRACE                     (0x00)
DECL|macro|MPI_DIAG_BUF_TYPE_SNAPSHOT
mdefine_line|#define MPI_DIAG_BUF_TYPE_SNAPSHOT                  (0x01)
DECL|macro|MPI_DIAG_BUF_TYPE_EXTENDED
mdefine_line|#define MPI_DIAG_BUF_TYPE_EXTENDED                  (0x02)
DECL|macro|MPI_DIAG_EXTENDED_QTAG
mdefine_line|#define MPI_DIAG_EXTENDED_QTAG                      (0x00000001)
multiline_comment|/* Diagnostic Buffer Post reply */
DECL|struct|_MSG_DIAG_BUFFER_POST_REPLY
r_typedef
r_struct
id|_MSG_DIAG_BUFFER_POST_REPLY
(brace
DECL|member|Reserved1
id|U8
id|Reserved1
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|BufferType
id|U8
id|BufferType
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
DECL|member|Reserved2
id|U16
id|Reserved2
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Reserved3
id|U8
id|Reserved3
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
DECL|member|Reserved4
id|U16
id|Reserved4
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
DECL|member|TransferLength
id|U32
id|TransferLength
suffix:semicolon
multiline_comment|/* 14h */
DECL|typedef|MSG_DIAG_BUFFER_POST_REPLY
DECL|typedef|PTR_MSG_DIAG_BUFFER_POST_REPLY
)brace
id|MSG_DIAG_BUFFER_POST_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_DIAG_BUFFER_POST_REPLY
comma
DECL|typedef|DiagBufferPostReply_t
DECL|typedef|pDiagBufferPostReply_t
id|DiagBufferPostReply_t
comma
id|MPI_POINTER
id|pDiagBufferPostReply_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/* Diagnostic Release request                                               */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_DIAG_RELEASE_REQUEST
r_typedef
r_struct
id|_MSG_DIAG_RELEASE_REQUEST
(brace
DECL|member|Reserved1
id|U8
id|Reserved1
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|BufferType
id|U8
id|BufferType
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
DECL|member|Reserved2
id|U16
id|Reserved2
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Reserved3
id|U8
id|Reserved3
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
DECL|typedef|MSG_DIAG_RELEASE_REQUEST
DECL|typedef|PTR_MSG_DIAG_RELEASE_REQUEST
)brace
id|MSG_DIAG_RELEASE_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_DIAG_RELEASE_REQUEST
comma
DECL|typedef|DiagReleaseRequest_t
DECL|typedef|pDiagReleaseRequest_t
id|DiagReleaseRequest_t
comma
id|MPI_POINTER
id|pDiagReleaseRequest_t
suffix:semicolon
multiline_comment|/* Diagnostic Release reply */
DECL|struct|_MSG_DIAG_RELEASE_REPLY
r_typedef
r_struct
id|_MSG_DIAG_RELEASE_REPLY
(brace
DECL|member|Reserved1
id|U8
id|Reserved1
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|BufferType
id|U8
id|BufferType
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
DECL|member|Reserved2
id|U16
id|Reserved2
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Reserved3
id|U8
id|Reserved3
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
DECL|member|Reserved4
id|U16
id|Reserved4
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
DECL|typedef|MSG_DIAG_RELEASE_REPLY
DECL|typedef|PTR_MSG_DIAG_RELEASE_REPLY
)brace
id|MSG_DIAG_RELEASE_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_DIAG_RELEASE_REPLY
comma
DECL|typedef|DiagReleaseReply_t
DECL|typedef|pDiagReleaseReply_t
id|DiagReleaseReply_t
comma
id|MPI_POINTER
id|pDiagReleaseReply_t
suffix:semicolon
macro_line|#endif
eof
