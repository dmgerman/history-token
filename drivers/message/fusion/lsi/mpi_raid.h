multiline_comment|/*&n; *  Copyright (c) 2001 LSI Logic Corporation.&n; *&n; *&n; *           Name:  MPI_RAID.H&n; *          Title:  MPI RAID message and structures&n; *  Creation Date:  February 27, 2001&n; *&n; *    MPI Version:  01.02.04&n; *&n; *  Version History&n; *  ---------------&n; *&n; *  Date      Version   Description&n; *  --------  --------  ------------------------------------------------------&n; *  02-27-01  01.01.01  Original release for this file.&n; *  03-27-01  01.01.02  Added structure offset comments.&n; *  08-08-01  01.02.01  Original release for v1.2 work.&n; *  09-28-01  01.02.02  Major rework for MPI v1.2 Integrated RAID changes.&n; *  10-04-01  01.02.03  Added ActionData defines for&n; *                      MPI_RAID_ACTION_DELETE_VOLUME action.&n; *  11-01-01  01.02.04  Added define for MPI_RAID_ACTION_ADATA_DO_NOT_SYNC.&n; *  --------------------------------------------------------------------------&n; */
macro_line|#ifndef MPI_RAID_H
DECL|macro|MPI_RAID_H
mdefine_line|#define MPI_RAID_H
multiline_comment|/******************************************************************************&n;*&n;*        R A I D    M e s s a g e s&n;*&n;*******************************************************************************/
multiline_comment|/****************************************************************************/
multiline_comment|/* RAID Volume Request                                                      */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_RAID_ACTION
r_typedef
r_struct
id|_MSG_RAID_ACTION
(brace
DECL|member|Action
id|U8
id|Action
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved1
id|U8
id|Reserved1
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
DECL|member|VolumeID
id|U8
id|VolumeID
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|VolumeBus
id|U8
id|VolumeBus
suffix:semicolon
multiline_comment|/* 05h */
DECL|member|PhysDiskNum
id|U8
id|PhysDiskNum
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
id|U32
id|Reserved2
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|ActionDataWord
id|U32
id|ActionDataWord
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|ActionDataSGE
id|SGE_SIMPLE_UNION
id|ActionDataSGE
suffix:semicolon
multiline_comment|/* 14h */
DECL|typedef|MSG_RAID_ACTION_REQUEST
DECL|typedef|PTR_MSG_RAID_ACTION_REQUEST
)brace
id|MSG_RAID_ACTION_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_RAID_ACTION_REQUEST
comma
DECL|typedef|MpiRaidActionRequest_t
DECL|typedef|pMpiRaidActionRequest_t
id|MpiRaidActionRequest_t
comma
id|MPI_POINTER
id|pMpiRaidActionRequest_t
suffix:semicolon
multiline_comment|/* RAID Action request Action values */
DECL|macro|MPI_RAID_ACTION_STATUS
mdefine_line|#define MPI_RAID_ACTION_STATUS                      (0x00)
DECL|macro|MPI_RAID_ACTION_INDICATOR_STRUCT
mdefine_line|#define MPI_RAID_ACTION_INDICATOR_STRUCT            (0x01)
DECL|macro|MPI_RAID_ACTION_CREATE_VOLUME
mdefine_line|#define MPI_RAID_ACTION_CREATE_VOLUME               (0x02)
DECL|macro|MPI_RAID_ACTION_DELETE_VOLUME
mdefine_line|#define MPI_RAID_ACTION_DELETE_VOLUME               (0x03)
DECL|macro|MPI_RAID_ACTION_DISABLE_VOLUME
mdefine_line|#define MPI_RAID_ACTION_DISABLE_VOLUME              (0x04)
DECL|macro|MPI_RAID_ACTION_ENABLE_VOLUME
mdefine_line|#define MPI_RAID_ACTION_ENABLE_VOLUME               (0x05)
DECL|macro|MPI_RAID_ACTION_QUIESCE_PHYS_IO
mdefine_line|#define MPI_RAID_ACTION_QUIESCE_PHYS_IO             (0x06)
DECL|macro|MPI_RAID_ACTION_ENABLE_PHYS_IO
mdefine_line|#define MPI_RAID_ACTION_ENABLE_PHYS_IO              (0x07)
DECL|macro|MPI_RAID_ACTION_CHANGE_VOLUME_SETTINGS
mdefine_line|#define MPI_RAID_ACTION_CHANGE_VOLUME_SETTINGS      (0x08)
DECL|macro|MPI_RAID_ACTION_PHYSDISK_OFFLINE
mdefine_line|#define MPI_RAID_ACTION_PHYSDISK_OFFLINE            (0x0A)
DECL|macro|MPI_RAID_ACTION_PHYSDISK_ONLINE
mdefine_line|#define MPI_RAID_ACTION_PHYSDISK_ONLINE             (0x0B)
DECL|macro|MPI_RAID_ACTION_CHANGE_PHYSDISK_SETTINGS
mdefine_line|#define MPI_RAID_ACTION_CHANGE_PHYSDISK_SETTINGS    (0x0C)
DECL|macro|MPI_RAID_ACTION_CREATE_PHYSDISK
mdefine_line|#define MPI_RAID_ACTION_CREATE_PHYSDISK             (0x0D)
DECL|macro|MPI_RAID_ACTION_DELETE_PHYSDISK
mdefine_line|#define MPI_RAID_ACTION_DELETE_PHYSDISK             (0x0E)
DECL|macro|MPI_RAID_ACTION_FAIL_PHYSDISK
mdefine_line|#define MPI_RAID_ACTION_FAIL_PHYSDISK               (0x0F)
DECL|macro|MPI_RAID_ACTION_REPLACE_PHYSDISK
mdefine_line|#define MPI_RAID_ACTION_REPLACE_PHYSDISK            (0x10)
multiline_comment|/* ActionDataWord defines for use with MPI_RAID_ACTION_CREATE_VOLUME action */
DECL|macro|MPI_RAID_ACTION_ADATA_DO_NOT_SYNC
mdefine_line|#define MPI_RAID_ACTION_ADATA_DO_NOT_SYNC           (0x00000001)
multiline_comment|/* ActionDataWord defines for use with MPI_RAID_ACTION_DELETE_VOLUME action */
DECL|macro|MPI_RAID_ACTION_ADATA_KEEP_PHYS_DISKS
mdefine_line|#define MPI_RAID_ACTION_ADATA_KEEP_PHYS_DISKS       (0x00000000)
DECL|macro|MPI_RAID_ACTION_ADATA_DEL_PHYS_DISKS
mdefine_line|#define MPI_RAID_ACTION_ADATA_DEL_PHYS_DISKS        (0x00000001)
multiline_comment|/* RAID Action reply message */
DECL|struct|_MSG_RAID_ACTION_REPLY
r_typedef
r_struct
id|_MSG_RAID_ACTION_REPLY
(brace
DECL|member|Action
id|U8
id|Action
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
DECL|member|VolumeID
id|U8
id|VolumeID
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|VolumeBus
id|U8
id|VolumeBus
suffix:semicolon
multiline_comment|/* 05h */
DECL|member|PhysDiskNum
id|U8
id|PhysDiskNum
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
DECL|member|ActionStatus
id|U16
id|ActionStatus
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
DECL|member|VolumeStatus
id|U32
id|VolumeStatus
suffix:semicolon
multiline_comment|/* 14h */
DECL|member|ActionData
id|U32
id|ActionData
suffix:semicolon
multiline_comment|/* 18h */
DECL|typedef|MSG_RAID_ACTION_REPLY
DECL|typedef|PTR_MSG_RAID_ACTION_REPLY
)brace
id|MSG_RAID_ACTION_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_RAID_ACTION_REPLY
comma
DECL|typedef|MpiRaidActionReply_t
DECL|typedef|pMpiRaidActionReply_t
id|MpiRaidActionReply_t
comma
id|MPI_POINTER
id|pMpiRaidActionReply_t
suffix:semicolon
multiline_comment|/* RAID Volume reply ActionStatus values */
DECL|macro|MPI_RAID_ACTION_ASTATUS_SUCCESS
mdefine_line|#define MPI_RAID_ACTION_ASTATUS_SUCCESS             (0x0000)
DECL|macro|MPI_RAID_ACTION_ASTATUS_INVALID_ACTION
mdefine_line|#define MPI_RAID_ACTION_ASTATUS_INVALID_ACTION      (0x0001)
DECL|macro|MPI_RAID_ACTION_ASTATUS_FAILURE
mdefine_line|#define MPI_RAID_ACTION_ASTATUS_FAILURE             (0x0002)
DECL|macro|MPI_RAID_ACTION_ASTATUS_IN_PROGRESS
mdefine_line|#define MPI_RAID_ACTION_ASTATUS_IN_PROGRESS         (0x0003)
multiline_comment|/* RAID Volume reply RAID Volume Indicator structure */
DECL|struct|_MPI_RAID_VOL_INDICATOR
r_typedef
r_struct
id|_MPI_RAID_VOL_INDICATOR
(brace
DECL|member|TotalBlocks
id|U64
id|TotalBlocks
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|BlocksRemaining
id|U64
id|BlocksRemaining
suffix:semicolon
multiline_comment|/* 08h */
DECL|typedef|MPI_RAID_VOL_INDICATOR
DECL|typedef|PTR_MPI_RAID_VOL_INDICATOR
)brace
id|MPI_RAID_VOL_INDICATOR
comma
id|MPI_POINTER
id|PTR_MPI_RAID_VOL_INDICATOR
comma
DECL|typedef|MpiRaidVolIndicator_t
DECL|typedef|pMpiRaidVolIndicator_t
id|MpiRaidVolIndicator_t
comma
id|MPI_POINTER
id|pMpiRaidVolIndicator_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/* SCSI IO RAID Passthrough Request                                         */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_SCSI_IO_RAID_PT_REQUEST
r_typedef
r_struct
id|_MSG_SCSI_IO_RAID_PT_REQUEST
(brace
DECL|member|PhysDiskNum
id|U8
id|PhysDiskNum
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved1
id|U8
id|Reserved1
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
DECL|typedef|MSG_SCSI_IO_RAID_PT_REQUEST
DECL|typedef|PTR_MSG_SCSI_IO_RAID_PT_REQUEST
)brace
id|MSG_SCSI_IO_RAID_PT_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_SCSI_IO_RAID_PT_REQUEST
comma
DECL|typedef|SCSIIORaidPassthroughRequest_t
DECL|typedef|pSCSIIORaidPassthroughRequest_t
id|SCSIIORaidPassthroughRequest_t
comma
id|MPI_POINTER
id|pSCSIIORaidPassthroughRequest_t
suffix:semicolon
multiline_comment|/* SCSI IO RAID Passthrough reply structure */
DECL|struct|_MSG_SCSI_IO_RAID_PT_REPLY
r_typedef
r_struct
id|_MSG_SCSI_IO_RAID_PT_REPLY
(brace
DECL|member|PhysDiskNum
id|U8
id|PhysDiskNum
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved1
id|U8
id|Reserved1
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
DECL|typedef|MSG_SCSI_IO_RAID_PT_REPLY
DECL|typedef|PTR_MSG_SCSI_IO_RAID_PT_REPLY
)brace
id|MSG_SCSI_IO_RAID_PT_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_SCSI_IO_RAID_PT_REPLY
comma
DECL|typedef|SCSIIORaidPassthroughReply_t
DECL|typedef|pSCSIIORaidPassthroughReply_t
id|SCSIIORaidPassthroughReply_t
comma
id|MPI_POINTER
id|pSCSIIORaidPassthroughReply_t
suffix:semicolon
macro_line|#endif
eof
