multiline_comment|/*&n; *  Copyright (c) 2000-2001 LSI Logic Corporation.&n; *&n; *&n; *           Name:  MPI_IOC.H&n; *          Title:  MPI IOC, Port, Event, FW Download, and FW Upload messages&n; *  Creation Date:  August 11, 2000&n; *&n; *    MPI Version:  01.02.04&n; *&n; *  Version History&n; *  ---------------&n; *&n; *  Date      Version   Description&n; *  --------  --------  ------------------------------------------------------&n; *  05-08-00  00.10.01  Original release for 0.10 spec dated 4/26/2000.&n; *  05-24-00  00.10.02  Added _MSG_IOC_INIT_REPLY structure.&n; *  06-06-00  01.00.01  Added CurReplyFrameSize field to _MSG_IOC_FACTS_REPLY.&n; *  06-12-00  01.00.02  Added _MSG_PORT_ENABLE_REPLY structure.&n; *                      Added _MSG_EVENT_ACK_REPLY structure.&n; *                      Added _MSG_FW_DOWNLOAD_REPLY structure.&n; *                      Added _MSG_TOOLBOX_REPLY structure.&n; *  06-30-00  01.00.03  Added MaxLanBuckets to _PORT_FACT_REPLY structure.&n; *  07-27-00  01.00.04  Added _EVENT_DATA structure definitions for _SCSI,&n; *                      _LINK_STATUS, _LOOP_STATE and _LOGOUT.&n; *  08-11-00  01.00.05  Switched positions of MsgLength and Function fields in&n; *                      _MSG_EVENT_ACK_REPLY structure to match specification.&n; *  11-02-00  01.01.01  Original release for post 1.0 work.&n; *                      Added a value for Manufacturer to WhoInit.&n; *  12-04-00  01.01.02  Modified IOCFacts reply, added FWUpload messages, and&n; *                      removed toolbox message.&n; *  01-09-01  01.01.03  Added event enabled and disabled defines.&n; *                      Added structures for FwHeader and DataHeader.&n; *                      Added ImageType to FwUpload reply.&n; *  02-20-01  01.01.04  Started using MPI_POINTER.&n; *  02-27-01  01.01.05  Added event for RAID status change and its event data.&n; *                      Added IocNumber field to MSG_IOC_FACTS_REPLY.&n; *  03-27-01  01.01.06  Added defines for ProductId field of MPI_FW_HEADER.&n; *                      Added structure offset comments.&n; *  04-09-01  01.01.07  Added structure EVENT_DATA_EVENT_CHANGE.&n; *  08-08-01  01.02.01  Original release for v1.2 work.&n; *                      New format for FWVersion and ProductId in&n; *                      MSG_IOC_FACTS_REPLY and MPI_FW_HEADER.&n; *  08-31-01  01.02.02  Addded event MPI_EVENT_SCSI_DEVICE_STATUS_CHANGE and&n; *                      related structure and defines.&n; *                      Added event MPI_EVENT_ON_BUS_TIMER_EXPIRED.&n; *                      Added MPI_IOCINIT_FLAGS_DISCARD_FW_IMAGE.&n; *                      Replaced a reserved field in MSG_IOC_FACTS_REPLY with&n; *                      IOCExceptions and changed DataImageSize to reserved.&n; *                      Added MPI_FW_DOWNLOAD_ITYPE_NVSTORE_DATA and&n; *                      MPI_FW_UPLOAD_ITYPE_NVDATA.&n; *  09-28-01  01.02.03  Modified Event Data for Integrated RAID.&n; *  11-01-01  01.02.04  Added defines for MPI_EXT_IMAGE_HEADER ImageType field.&n; *  --------------------------------------------------------------------------&n; */
macro_line|#ifndef MPI_IOC_H
DECL|macro|MPI_IOC_H
mdefine_line|#define MPI_IOC_H
multiline_comment|/*****************************************************************************&n;*&n;*               I O C    M e s s a g e s&n;*&n;*****************************************************************************/
multiline_comment|/****************************************************************************/
multiline_comment|/*  IOCInit message                                                         */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_IOC_INIT
r_typedef
r_struct
id|_MSG_IOC_INIT
(brace
DECL|member|WhoInit
id|U8
id|WhoInit
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
DECL|member|Flags
id|U8
id|Flags
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|MaxDevices
id|U8
id|MaxDevices
suffix:semicolon
multiline_comment|/* 05h */
DECL|member|MaxBuses
id|U8
id|MaxBuses
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
DECL|member|ReplyFrameSize
id|U16
id|ReplyFrameSize
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|Reserved1
id|U8
id|Reserved1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0Eh */
DECL|member|HostMfaHighAddr
id|U32
id|HostMfaHighAddr
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|SenseBufferHighAddr
id|U32
id|SenseBufferHighAddr
suffix:semicolon
multiline_comment|/* 14h */
DECL|typedef|MSG_IOC_INIT
DECL|typedef|PTR_MSG_IOC_INIT
)brace
id|MSG_IOC_INIT
comma
id|MPI_POINTER
id|PTR_MSG_IOC_INIT
comma
DECL|typedef|IOCInit_t
DECL|typedef|pIOCInit_t
id|IOCInit_t
comma
id|MPI_POINTER
id|pIOCInit_t
suffix:semicolon
multiline_comment|/* WhoInit values */
DECL|macro|MPI_WHOINIT_NO_ONE
mdefine_line|#define MPI_WHOINIT_NO_ONE                      (0x00)
DECL|macro|MPI_WHOINIT_SYSTEM_BIOS
mdefine_line|#define MPI_WHOINIT_SYSTEM_BIOS                 (0x01)
DECL|macro|MPI_WHOINIT_ROM_BIOS
mdefine_line|#define MPI_WHOINIT_ROM_BIOS                    (0x02)
DECL|macro|MPI_WHOINIT_PCI_PEER
mdefine_line|#define MPI_WHOINIT_PCI_PEER                    (0x03)
DECL|macro|MPI_WHOINIT_HOST_DRIVER
mdefine_line|#define MPI_WHOINIT_HOST_DRIVER                 (0x04)
DECL|macro|MPI_WHOINIT_MANUFACTURER
mdefine_line|#define MPI_WHOINIT_MANUFACTURER                (0x05)
multiline_comment|/* Flags values */
DECL|macro|MPI_IOCINIT_FLAGS_DISCARD_FW_IMAGE
mdefine_line|#define MPI_IOCINIT_FLAGS_DISCARD_FW_IMAGE      (0x01)
DECL|struct|_MSG_IOC_INIT_REPLY
r_typedef
r_struct
id|_MSG_IOC_INIT_REPLY
(brace
DECL|member|WhoInit
id|U8
id|WhoInit
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
DECL|member|Flags
id|U8
id|Flags
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|MaxDevices
id|U8
id|MaxDevices
suffix:semicolon
multiline_comment|/* 05h */
DECL|member|MaxBuses
id|U8
id|MaxBuses
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
id|U16
id|Reserved2
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
DECL|typedef|MSG_IOC_INIT_REPLY
DECL|typedef|PTR_MSG_IOC_INIT_REPLY
)brace
id|MSG_IOC_INIT_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_IOC_INIT_REPLY
comma
DECL|typedef|IOCInitReply_t
DECL|typedef|pIOCInitReply_t
id|IOCInitReply_t
comma
id|MPI_POINTER
id|pIOCInitReply_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/*  IOC Facts message                                                       */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_IOC_FACTS
r_typedef
r_struct
id|_MSG_IOC_FACTS
(brace
DECL|member|Reserved
id|U8
id|Reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|ChainOffset
id|U8
id|ChainOffset
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|Function
id|U8
id|Function
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|Reserved1
id|U8
id|Reserved1
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 03h */
DECL|member|MsgFlags
id|U8
id|MsgFlags
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|MsgContext
id|U32
id|MsgContext
suffix:semicolon
multiline_comment|/* 08h */
DECL|typedef|MSG_IOC_FACTS
DECL|typedef|PTR_IOC_FACTS
)brace
id|MSG_IOC_FACTS
comma
id|MPI_POINTER
id|PTR_IOC_FACTS
comma
DECL|typedef|IOCFacts_t
DECL|typedef|pIOCFacts_t
id|IOCFacts_t
comma
id|MPI_POINTER
id|pIOCFacts_t
suffix:semicolon
DECL|struct|_MPI_FW_VERSION_STRUCT
r_typedef
r_struct
id|_MPI_FW_VERSION_STRUCT
(brace
DECL|member|Dev
id|U8
id|Dev
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Unit
id|U8
id|Unit
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|Minor
id|U8
id|Minor
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|Major
id|U8
id|Major
suffix:semicolon
multiline_comment|/* 03h */
DECL|typedef|MPI_FW_VERSION_STRUCT
)brace
id|MPI_FW_VERSION_STRUCT
suffix:semicolon
DECL|union|_MPI_FW_VERSION
r_typedef
r_union
id|_MPI_FW_VERSION
(brace
DECL|member|Struct
id|MPI_FW_VERSION_STRUCT
id|Struct
suffix:semicolon
DECL|member|Word
id|U32
id|Word
suffix:semicolon
DECL|typedef|MPI_FW_VERSION
)brace
id|MPI_FW_VERSION
suffix:semicolon
multiline_comment|/* IOC Facts Reply */
DECL|struct|_MSG_IOC_FACTS_REPLY
r_typedef
r_struct
id|_MSG_IOC_FACTS_REPLY
(brace
DECL|member|MsgVersion
id|U16
id|MsgVersion
suffix:semicolon
multiline_comment|/* 00h */
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
id|U16
id|Reserved
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|IOCNumber
id|U8
id|IOCNumber
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
DECL|member|IOCExceptions
id|U16
id|IOCExceptions
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
DECL|member|MaxChainDepth
id|U8
id|MaxChainDepth
suffix:semicolon
multiline_comment|/* 14h */
DECL|member|WhoInit
id|U8
id|WhoInit
suffix:semicolon
multiline_comment|/* 15h */
DECL|member|BlockSize
id|U8
id|BlockSize
suffix:semicolon
multiline_comment|/* 16h */
DECL|member|Flags
id|U8
id|Flags
suffix:semicolon
multiline_comment|/* 17h */
DECL|member|ReplyQueueDepth
id|U16
id|ReplyQueueDepth
suffix:semicolon
multiline_comment|/* 18h */
DECL|member|RequestFrameSize
id|U16
id|RequestFrameSize
suffix:semicolon
multiline_comment|/* 1Ah */
DECL|member|Reserved_0101_FWVersion
id|U16
id|Reserved_0101_FWVersion
suffix:semicolon
multiline_comment|/* 1Ch */
multiline_comment|/* obsolete 16-bit FWVersion */
DECL|member|ProductID
id|U16
id|ProductID
suffix:semicolon
multiline_comment|/* 1Eh */
DECL|member|CurrentHostMfaHighAddr
id|U32
id|CurrentHostMfaHighAddr
suffix:semicolon
multiline_comment|/* 20h */
DECL|member|GlobalCredits
id|U16
id|GlobalCredits
suffix:semicolon
multiline_comment|/* 24h */
DECL|member|NumberOfPorts
id|U8
id|NumberOfPorts
suffix:semicolon
multiline_comment|/* 26h */
DECL|member|EventState
id|U8
id|EventState
suffix:semicolon
multiline_comment|/* 27h */
DECL|member|CurrentSenseBufferHighAddr
id|U32
id|CurrentSenseBufferHighAddr
suffix:semicolon
multiline_comment|/* 28h */
DECL|member|CurReplyFrameSize
id|U16
id|CurReplyFrameSize
suffix:semicolon
multiline_comment|/* 2Ch */
DECL|member|MaxDevices
id|U8
id|MaxDevices
suffix:semicolon
multiline_comment|/* 2Eh */
DECL|member|MaxBuses
id|U8
id|MaxBuses
suffix:semicolon
multiline_comment|/* 2Fh */
DECL|member|FWImageSize
id|U32
id|FWImageSize
suffix:semicolon
multiline_comment|/* 30h */
DECL|member|Reserved4
id|U32
id|Reserved4
suffix:semicolon
multiline_comment|/* 34h */
DECL|member|FWVersion
id|MPI_FW_VERSION
id|FWVersion
suffix:semicolon
multiline_comment|/* 38h */
DECL|typedef|MSG_IOC_FACTS_REPLY
DECL|typedef|PTR_MSG_IOC_FACTS_REPLY
)brace
id|MSG_IOC_FACTS_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_IOC_FACTS_REPLY
comma
DECL|typedef|IOCFactsReply_t
DECL|typedef|pIOCFactsReply_t
id|IOCFactsReply_t
comma
id|MPI_POINTER
id|pIOCFactsReply_t
suffix:semicolon
DECL|macro|MPI_IOCFACTS_MSGVERSION_MAJOR_MASK
mdefine_line|#define MPI_IOCFACTS_MSGVERSION_MAJOR_MASK          (0xFF00)
DECL|macro|MPI_IOCFACTS_MSGVERSION_MINOR_MASK
mdefine_line|#define MPI_IOCFACTS_MSGVERSION_MINOR_MASK          (0x00FF)
DECL|macro|MPI_IOCFACTS_EXCEPT_CONFIG_CHECKSUM_FAIL
mdefine_line|#define MPI_IOCFACTS_EXCEPT_CONFIG_CHECKSUM_FAIL    (0x0001)
DECL|macro|MPI_IOCFACTS_FLAGS_FW_DOWNLOAD_BOOT
mdefine_line|#define MPI_IOCFACTS_FLAGS_FW_DOWNLOAD_BOOT         (0x01)
DECL|macro|MPI_IOCFACTS_EVENTSTATE_DISABLED
mdefine_line|#define MPI_IOCFACTS_EVENTSTATE_DISABLED            (0x00)
DECL|macro|MPI_IOCFACTS_EVENTSTATE_ENABLED
mdefine_line|#define MPI_IOCFACTS_EVENTSTATE_ENABLED             (0x01)
multiline_comment|/*****************************************************************************&n;*&n;*               P o r t    M e s s a g e s&n;*&n;*****************************************************************************/
multiline_comment|/****************************************************************************/
multiline_comment|/*  Port Facts message and Reply                                            */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_PORT_FACTS
r_typedef
r_struct
id|_MSG_PORT_FACTS
(brace
DECL|member|Reserved
id|U8
id|Reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 00h */
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
id|U8
id|Reserved1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|PortNumber
id|U8
id|PortNumber
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
DECL|typedef|MSG_PORT_FACTS
DECL|typedef|PTR_MSG_PORT_FACTS
)brace
id|MSG_PORT_FACTS
comma
id|MPI_POINTER
id|PTR_MSG_PORT_FACTS
comma
DECL|typedef|PortFacts_t
DECL|typedef|pPortFacts_t
id|PortFacts_t
comma
id|MPI_POINTER
id|pPortFacts_t
suffix:semicolon
DECL|struct|_MSG_PORT_FACTS_REPLY
r_typedef
r_struct
id|_MSG_PORT_FACTS_REPLY
(brace
DECL|member|Reserved
id|U16
id|Reserved
suffix:semicolon
multiline_comment|/* 00h */
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
DECL|member|PortNumber
id|U8
id|PortNumber
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
id|U16
id|Reserved2
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
DECL|member|Reserved3
id|U8
id|Reserved3
suffix:semicolon
multiline_comment|/* 14h */
DECL|member|PortType
id|U8
id|PortType
suffix:semicolon
multiline_comment|/* 15h */
DECL|member|MaxDevices
id|U16
id|MaxDevices
suffix:semicolon
multiline_comment|/* 16h */
DECL|member|PortSCSIID
id|U16
id|PortSCSIID
suffix:semicolon
multiline_comment|/* 18h */
DECL|member|ProtocolFlags
id|U16
id|ProtocolFlags
suffix:semicolon
multiline_comment|/* 1Ah */
DECL|member|MaxPostedCmdBuffers
id|U16
id|MaxPostedCmdBuffers
suffix:semicolon
multiline_comment|/* 1Ch */
DECL|member|MaxPersistentIDs
id|U16
id|MaxPersistentIDs
suffix:semicolon
multiline_comment|/* 1Eh */
DECL|member|MaxLanBuckets
id|U16
id|MaxLanBuckets
suffix:semicolon
multiline_comment|/* 20h */
DECL|member|Reserved4
id|U16
id|Reserved4
suffix:semicolon
multiline_comment|/* 22h */
DECL|member|Reserved5
id|U32
id|Reserved5
suffix:semicolon
multiline_comment|/* 24h */
DECL|typedef|MSG_PORT_FACTS_REPLY
DECL|typedef|PTR_MSG_PORT_FACTS_REPLY
)brace
id|MSG_PORT_FACTS_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_PORT_FACTS_REPLY
comma
DECL|typedef|PortFactsReply_t
DECL|typedef|pPortFactsReply_t
id|PortFactsReply_t
comma
id|MPI_POINTER
id|pPortFactsReply_t
suffix:semicolon
multiline_comment|/* PortTypes values */
DECL|macro|MPI_PORTFACTS_PORTTYPE_INACTIVE
mdefine_line|#define MPI_PORTFACTS_PORTTYPE_INACTIVE         (0x00)
DECL|macro|MPI_PORTFACTS_PORTTYPE_SCSI
mdefine_line|#define MPI_PORTFACTS_PORTTYPE_SCSI             (0x01)
DECL|macro|MPI_PORTFACTS_PORTTYPE_FC
mdefine_line|#define MPI_PORTFACTS_PORTTYPE_FC               (0x10)
multiline_comment|/* ProtocolFlags values */
DECL|macro|MPI_PORTFACTS_PROTOCOL_LOGBUSADDR
mdefine_line|#define MPI_PORTFACTS_PROTOCOL_LOGBUSADDR       (0x01)
DECL|macro|MPI_PORTFACTS_PROTOCOL_LAN
mdefine_line|#define MPI_PORTFACTS_PROTOCOL_LAN              (0x02)
DECL|macro|MPI_PORTFACTS_PROTOCOL_TARGET
mdefine_line|#define MPI_PORTFACTS_PROTOCOL_TARGET           (0x04)
DECL|macro|MPI_PORTFACTS_PROTOCOL_INITIATOR
mdefine_line|#define MPI_PORTFACTS_PROTOCOL_INITIATOR        (0x08)
multiline_comment|/****************************************************************************/
multiline_comment|/*  Port Enable Message                                                     */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_PORT_ENABLE
r_typedef
r_struct
id|_MSG_PORT_ENABLE
(brace
DECL|member|Reserved
id|U8
id|Reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 00h */
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
id|U8
id|Reserved1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|PortNumber
id|U8
id|PortNumber
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
DECL|typedef|MSG_PORT_ENABLE
DECL|typedef|PTR_MSG_PORT_ENABLE
)brace
id|MSG_PORT_ENABLE
comma
id|MPI_POINTER
id|PTR_MSG_PORT_ENABLE
comma
DECL|typedef|PortEnable_t
DECL|typedef|pPortEnable_t
id|PortEnable_t
comma
id|MPI_POINTER
id|pPortEnable_t
suffix:semicolon
DECL|struct|_MSG_PORT_ENABLE_REPLY
r_typedef
r_struct
id|_MSG_PORT_ENABLE_REPLY
(brace
DECL|member|Reserved
id|U8
id|Reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 00h */
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
id|U8
id|Reserved1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|PortNumber
id|U8
id|PortNumber
suffix:semicolon
multiline_comment|/* 05h */
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
id|U16
id|Reserved2
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
DECL|typedef|MSG_PORT_ENABLE_REPLY
DECL|typedef|PTR_MSG_PORT_ENABLE_REPLY
)brace
id|MSG_PORT_ENABLE_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_PORT_ENABLE_REPLY
comma
DECL|typedef|PortEnableReply_t
DECL|typedef|pPortEnableReply_t
id|PortEnableReply_t
comma
id|MPI_POINTER
id|pPortEnableReply_t
suffix:semicolon
multiline_comment|/*****************************************************************************&n;*&n;*               E v e n t    M e s s a g e s&n;*&n;*****************************************************************************/
multiline_comment|/****************************************************************************/
multiline_comment|/*  Event Notification messages                                             */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_EVENT_NOTIFY
r_typedef
r_struct
id|_MSG_EVENT_NOTIFY
(brace
DECL|member|Switch
id|U8
id|Switch
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
id|U8
id|Reserved1
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 04h */
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
DECL|typedef|MSG_EVENT_NOTIFY
DECL|typedef|PTR_MSG_EVENT_NOTIFY
)brace
id|MSG_EVENT_NOTIFY
comma
id|MPI_POINTER
id|PTR_MSG_EVENT_NOTIFY
comma
DECL|typedef|EventNotification_t
DECL|typedef|pEventNotification_t
id|EventNotification_t
comma
id|MPI_POINTER
id|pEventNotification_t
suffix:semicolon
multiline_comment|/* Event Notification Reply */
DECL|struct|_MSG_EVENT_NOTIFY_REPLY
r_typedef
r_struct
id|_MSG_EVENT_NOTIFY_REPLY
(brace
DECL|member|EventDataLength
id|U16
id|EventDataLength
suffix:semicolon
multiline_comment|/* 00h */
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
id|U8
id|Reserved1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|AckRequired
id|U8
id|AckRequired
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
DECL|member|Event
id|U32
id|Event
suffix:semicolon
multiline_comment|/* 14h */
DECL|member|EventContext
id|U32
id|EventContext
suffix:semicolon
multiline_comment|/* 18h */
DECL|member|Data
id|U32
id|Data
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* 1Ch */
DECL|typedef|MSG_EVENT_NOTIFY_REPLY
DECL|typedef|PTR_MSG_EVENT_NOTIFY_REPLY
)brace
id|MSG_EVENT_NOTIFY_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_EVENT_NOTIFY_REPLY
comma
DECL|typedef|EventNotificationReply_t
DECL|typedef|pEventNotificationReply_t
id|EventNotificationReply_t
comma
id|MPI_POINTER
id|pEventNotificationReply_t
suffix:semicolon
multiline_comment|/* Event Acknowledge */
DECL|struct|_MSG_EVENT_ACK
r_typedef
r_struct
id|_MSG_EVENT_ACK
(brace
DECL|member|Reserved
id|U8
id|Reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 00h */
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
id|U8
id|Reserved1
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 04h */
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
DECL|member|Event
id|U32
id|Event
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|EventContext
id|U32
id|EventContext
suffix:semicolon
multiline_comment|/* 10h */
DECL|typedef|MSG_EVENT_ACK
DECL|typedef|PTR_MSG_EVENT_ACK
)brace
id|MSG_EVENT_ACK
comma
id|MPI_POINTER
id|PTR_MSG_EVENT_ACK
comma
DECL|typedef|EventAck_t
DECL|typedef|pEventAck_t
id|EventAck_t
comma
id|MPI_POINTER
id|pEventAck_t
suffix:semicolon
DECL|struct|_MSG_EVENT_ACK_REPLY
r_typedef
r_struct
id|_MSG_EVENT_ACK_REPLY
(brace
DECL|member|Reserved
id|U8
id|Reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 00h */
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
id|U8
id|Reserved1
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 04h */
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
id|U16
id|Reserved2
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
DECL|typedef|MSG_EVENT_ACK_REPLY
DECL|typedef|PTR_MSG_EVENT_ACK_REPLY
)brace
id|MSG_EVENT_ACK_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_EVENT_ACK_REPLY
comma
DECL|typedef|EventAckReply_t
DECL|typedef|pEventAckReply_t
id|EventAckReply_t
comma
id|MPI_POINTER
id|pEventAckReply_t
suffix:semicolon
multiline_comment|/* Switch */
DECL|macro|MPI_EVENT_NOTIFICATION_SWITCH_OFF
mdefine_line|#define MPI_EVENT_NOTIFICATION_SWITCH_OFF   (0x00)
DECL|macro|MPI_EVENT_NOTIFICATION_SWITCH_ON
mdefine_line|#define MPI_EVENT_NOTIFICATION_SWITCH_ON    (0x01)
multiline_comment|/* Event */
DECL|macro|MPI_EVENT_NONE
mdefine_line|#define MPI_EVENT_NONE                      (0x00000000)
DECL|macro|MPI_EVENT_LOG_DATA
mdefine_line|#define MPI_EVENT_LOG_DATA                  (0x00000001)
DECL|macro|MPI_EVENT_STATE_CHANGE
mdefine_line|#define MPI_EVENT_STATE_CHANGE              (0x00000002)
DECL|macro|MPI_EVENT_UNIT_ATTENTION
mdefine_line|#define MPI_EVENT_UNIT_ATTENTION            (0x00000003)
DECL|macro|MPI_EVENT_IOC_BUS_RESET
mdefine_line|#define MPI_EVENT_IOC_BUS_RESET             (0x00000004)
DECL|macro|MPI_EVENT_EXT_BUS_RESET
mdefine_line|#define MPI_EVENT_EXT_BUS_RESET             (0x00000005)
DECL|macro|MPI_EVENT_RESCAN
mdefine_line|#define MPI_EVENT_RESCAN                    (0x00000006)
DECL|macro|MPI_EVENT_LINK_STATUS_CHANGE
mdefine_line|#define MPI_EVENT_LINK_STATUS_CHANGE        (0x00000007)
DECL|macro|MPI_EVENT_LOOP_STATE_CHANGE
mdefine_line|#define MPI_EVENT_LOOP_STATE_CHANGE         (0x00000008)
DECL|macro|MPI_EVENT_LOGOUT
mdefine_line|#define MPI_EVENT_LOGOUT                    (0x00000009)
DECL|macro|MPI_EVENT_EVENT_CHANGE
mdefine_line|#define MPI_EVENT_EVENT_CHANGE              (0x0000000A)
DECL|macro|MPI_EVENT_INTEGRATED_RAID
mdefine_line|#define MPI_EVENT_INTEGRATED_RAID           (0x0000000B)
DECL|macro|MPI_EVENT_SCSI_DEVICE_STATUS_CHANGE
mdefine_line|#define MPI_EVENT_SCSI_DEVICE_STATUS_CHANGE (0x0000000C)
DECL|macro|MPI_EVENT_ON_BUS_TIMER_EXPIRED
mdefine_line|#define MPI_EVENT_ON_BUS_TIMER_EXPIRED      (0x0000000D)
multiline_comment|/* AckRequired field values */
DECL|macro|MPI_EVENT_NOTIFICATION_ACK_NOT_REQUIRED
mdefine_line|#define MPI_EVENT_NOTIFICATION_ACK_NOT_REQUIRED (0x00)
DECL|macro|MPI_EVENT_NOTIFICATION_ACK_REQUIRED
mdefine_line|#define MPI_EVENT_NOTIFICATION_ACK_REQUIRED     (0x01)
multiline_comment|/* EventChange Event data */
DECL|struct|_EVENT_DATA_EVENT_CHANGE
r_typedef
r_struct
id|_EVENT_DATA_EVENT_CHANGE
(brace
DECL|member|EventState
id|U8
id|EventState
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 02h */
DECL|typedef|EVENT_DATA_EVENT_CHANGE
DECL|typedef|PTR_EVENT_DATA_EVENT_CHANGE
)brace
id|EVENT_DATA_EVENT_CHANGE
comma
id|MPI_POINTER
id|PTR_EVENT_DATA_EVENT_CHANGE
comma
DECL|typedef|EventDataEventChange_t
DECL|typedef|pEventDataEventChange_t
id|EventDataEventChange_t
comma
id|MPI_POINTER
id|pEventDataEventChange_t
suffix:semicolon
multiline_comment|/* SCSI Event data for Port, Bus and Device forms */
DECL|struct|_EVENT_DATA_SCSI
r_typedef
r_struct
id|_EVENT_DATA_SCSI
(brace
DECL|member|TargetID
id|U8
id|TargetID
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|BusPort
id|U8
id|BusPort
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|Reserved
id|U16
id|Reserved
suffix:semicolon
multiline_comment|/* 02h */
DECL|typedef|EVENT_DATA_SCSI
DECL|typedef|PTR_EVENT_DATA_SCSI
)brace
id|EVENT_DATA_SCSI
comma
id|MPI_POINTER
id|PTR_EVENT_DATA_SCSI
comma
DECL|typedef|EventDataScsi_t
DECL|typedef|pEventDataScsi_t
id|EventDataScsi_t
comma
id|MPI_POINTER
id|pEventDataScsi_t
suffix:semicolon
multiline_comment|/* SCSI Device Status Change Event data */
DECL|struct|_EVENT_DATA_SCSI_DEVICE_STATUS_CHANGE
r_typedef
r_struct
id|_EVENT_DATA_SCSI_DEVICE_STATUS_CHANGE
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
DECL|member|ReasonCode
id|U8
id|ReasonCode
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|LUN
id|U8
id|LUN
suffix:semicolon
multiline_comment|/* 03h */
DECL|member|ASC
id|U8
id|ASC
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|ASCQ
id|U8
id|ASCQ
suffix:semicolon
multiline_comment|/* 05h */
DECL|member|Reserved
id|U16
id|Reserved
suffix:semicolon
multiline_comment|/* 06h */
DECL|typedef|EVENT_DATA_SCSI_DEVICE_STATUS_CHANGE
)brace
id|EVENT_DATA_SCSI_DEVICE_STATUS_CHANGE
comma
DECL|typedef|PTR_EVENT_DATA_SCSI_DEVICE_STATUS_CHANGE
id|MPI_POINTER
id|PTR_EVENT_DATA_SCSI_DEVICE_STATUS_CHANGE
comma
DECL|typedef|MpiEventDataScsiDeviceStatusChange_t
id|MpiEventDataScsiDeviceStatusChange_t
comma
DECL|typedef|pMpiEventDataScsiDeviceStatusChange_t
id|MPI_POINTER
id|pMpiEventDataScsiDeviceStatusChange_t
suffix:semicolon
multiline_comment|/* MPI SCSI Device Status Change Event data ReasonCode values */
DECL|macro|MPI_EVENT_SCSI_DEV_STAT_RC_ADDED
mdefine_line|#define MPI_EVENT_SCSI_DEV_STAT_RC_ADDED                (0x03)
DECL|macro|MPI_EVENT_SCSI_DEV_STAT_RC_NOT_RESPONDING
mdefine_line|#define MPI_EVENT_SCSI_DEV_STAT_RC_NOT_RESPONDING       (0x04)
DECL|macro|MPI_EVENT_SCSI_DEV_STAT_RC_SMART_DATA
mdefine_line|#define MPI_EVENT_SCSI_DEV_STAT_RC_SMART_DATA           (0x05)
multiline_comment|/* MPI Link Status Change Event data */
DECL|struct|_EVENT_DATA_LINK_STATUS
r_typedef
r_struct
id|_EVENT_DATA_LINK_STATUS
(brace
DECL|member|State
id|U8
id|State
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|Reserved2
id|U8
id|Reserved2
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Port
id|U8
id|Port
suffix:semicolon
multiline_comment|/* 05h */
DECL|member|Reserved3
id|U16
id|Reserved3
suffix:semicolon
multiline_comment|/* 06h */
DECL|typedef|EVENT_DATA_LINK_STATUS
DECL|typedef|PTR_EVENT_DATA_LINK_STATUS
)brace
id|EVENT_DATA_LINK_STATUS
comma
id|MPI_POINTER
id|PTR_EVENT_DATA_LINK_STATUS
comma
DECL|typedef|EventDataLinkStatus_t
DECL|typedef|pEventDataLinkStatus_t
id|EventDataLinkStatus_t
comma
id|MPI_POINTER
id|pEventDataLinkStatus_t
suffix:semicolon
DECL|macro|MPI_EVENT_LINK_STATUS_FAILURE
mdefine_line|#define MPI_EVENT_LINK_STATUS_FAILURE       (0x00000000)
DECL|macro|MPI_EVENT_LINK_STATUS_ACTIVE
mdefine_line|#define MPI_EVENT_LINK_STATUS_ACTIVE        (0x00000001)
multiline_comment|/* MPI Loop State Change Event data */
DECL|struct|_EVENT_DATA_LOOP_STATE
r_typedef
r_struct
id|_EVENT_DATA_LOOP_STATE
(brace
DECL|member|Character4
id|U8
id|Character4
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Character3
id|U8
id|Character3
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|Type
id|U8
id|Type
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
multiline_comment|/* 03h */
DECL|member|Reserved1
id|U8
id|Reserved1
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Port
id|U8
id|Port
suffix:semicolon
multiline_comment|/* 05h */
DECL|member|Reserved2
id|U16
id|Reserved2
suffix:semicolon
multiline_comment|/* 06h */
DECL|typedef|EVENT_DATA_LOOP_STATE
DECL|typedef|PTR_EVENT_DATA_LOOP_STATE
)brace
id|EVENT_DATA_LOOP_STATE
comma
id|MPI_POINTER
id|PTR_EVENT_DATA_LOOP_STATE
comma
DECL|typedef|EventDataLoopState_t
DECL|typedef|pEventDataLoopState_t
id|EventDataLoopState_t
comma
id|MPI_POINTER
id|pEventDataLoopState_t
suffix:semicolon
DECL|macro|MPI_EVENT_LOOP_STATE_CHANGE_LIP
mdefine_line|#define MPI_EVENT_LOOP_STATE_CHANGE_LIP     (0x0001)
DECL|macro|MPI_EVENT_LOOP_STATE_CHANGE_LPE
mdefine_line|#define MPI_EVENT_LOOP_STATE_CHANGE_LPE     (0x0002)
DECL|macro|MPI_EVENT_LOOP_STATE_CHANGE_LPB
mdefine_line|#define MPI_EVENT_LOOP_STATE_CHANGE_LPB     (0x0003)
multiline_comment|/* MPI LOGOUT Event data */
DECL|struct|_EVENT_DATA_LOGOUT
r_typedef
r_struct
id|_EVENT_DATA_LOGOUT
(brace
DECL|member|NPortID
id|U32
id|NPortID
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Port
id|U8
id|Port
suffix:semicolon
multiline_comment|/* 05h */
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 06h */
DECL|typedef|EVENT_DATA_LOGOUT
DECL|typedef|PTR_EVENT_DATA_LOGOUT
)brace
id|EVENT_DATA_LOGOUT
comma
id|MPI_POINTER
id|PTR_EVENT_DATA_LOGOUT
comma
DECL|typedef|EventDataLogout_t
DECL|typedef|pEventDataLogout_t
id|EventDataLogout_t
comma
id|MPI_POINTER
id|pEventDataLogout_t
suffix:semicolon
multiline_comment|/* MPI Integrated RAID Event data */
DECL|struct|_EVENT_DATA_RAID
r_typedef
r_struct
id|_EVENT_DATA_RAID
(brace
DECL|member|VolumeID
id|U8
id|VolumeID
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|VolumeBus
id|U8
id|VolumeBus
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|ReasonCode
id|U8
id|ReasonCode
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|PhysDiskNum
id|U8
id|PhysDiskNum
suffix:semicolon
multiline_comment|/* 03h */
DECL|member|ASC
id|U8
id|ASC
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|ASCQ
id|U8
id|ASCQ
suffix:semicolon
multiline_comment|/* 05h */
DECL|member|Reserved
id|U16
id|Reserved
suffix:semicolon
multiline_comment|/* 06h */
DECL|member|SettingsStatus
id|U32
id|SettingsStatus
suffix:semicolon
multiline_comment|/* 08h */
DECL|typedef|EVENT_DATA_RAID
DECL|typedef|PTR_EVENT_DATA_RAID
)brace
id|EVENT_DATA_RAID
comma
id|MPI_POINTER
id|PTR_EVENT_DATA_RAID
comma
DECL|typedef|MpiEventDataRaid_t
DECL|typedef|pMpiEventDataRaid_t
id|MpiEventDataRaid_t
comma
id|MPI_POINTER
id|pMpiEventDataRaid_t
suffix:semicolon
multiline_comment|/* MPI Integrated RAID Event data ReasonCode values */
DECL|macro|MPI_EVENT_RAID_RC_VOLUME_CREATED
mdefine_line|#define MPI_EVENT_RAID_RC_VOLUME_CREATED                (0x00)
DECL|macro|MPI_EVENT_RAID_RC_VOLUME_DELETED
mdefine_line|#define MPI_EVENT_RAID_RC_VOLUME_DELETED                (0x01)
DECL|macro|MPI_EVENT_RAID_RC_VOLUME_SETTINGS_CHANGED
mdefine_line|#define MPI_EVENT_RAID_RC_VOLUME_SETTINGS_CHANGED       (0x02)
DECL|macro|MPI_EVENT_RAID_RC_VOLUME_STATUS_CHANGED
mdefine_line|#define MPI_EVENT_RAID_RC_VOLUME_STATUS_CHANGED         (0x03)
DECL|macro|MPI_EVENT_RAID_RC_VOLUME_PHYSDISK_CHANGED
mdefine_line|#define MPI_EVENT_RAID_RC_VOLUME_PHYSDISK_CHANGED       (0x04)
DECL|macro|MPI_EVENT_RAID_RC_PHYSDISK_CREATED
mdefine_line|#define MPI_EVENT_RAID_RC_PHYSDISK_CREATED              (0x05)
DECL|macro|MPI_EVENT_RAID_RC_PHYSDISK_DELETED
mdefine_line|#define MPI_EVENT_RAID_RC_PHYSDISK_DELETED              (0x06)
DECL|macro|MPI_EVENT_RAID_RC_PHYSDISK_SETTINGS_CHANGED
mdefine_line|#define MPI_EVENT_RAID_RC_PHYSDISK_SETTINGS_CHANGED     (0x07)
DECL|macro|MPI_EVENT_RAID_RC_PHYSDISK_STATUS_CHANGED
mdefine_line|#define MPI_EVENT_RAID_RC_PHYSDISK_STATUS_CHANGED       (0x08)
DECL|macro|MPI_EVENT_RAID_RC_DOMAIN_VAL_NEEDED
mdefine_line|#define MPI_EVENT_RAID_RC_DOMAIN_VAL_NEEDED             (0x09)
DECL|macro|MPI_EVENT_RAID_RC_SMART_DATA
mdefine_line|#define MPI_EVENT_RAID_RC_SMART_DATA                    (0x0A)
DECL|macro|MPI_EVENT_RAID_RC_REPLACE_ACTION_STARTED
mdefine_line|#define MPI_EVENT_RAID_RC_REPLACE_ACTION_STARTED        (0x0B)
multiline_comment|/*****************************************************************************&n;*&n;*               F i r m w a r e    L o a d    M e s s a g e s&n;*&n;*****************************************************************************/
multiline_comment|/****************************************************************************/
multiline_comment|/*  Firmware Download message and associated structures                     */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_FW_DOWNLOAD
r_typedef
r_struct
id|_MSG_FW_DOWNLOAD
(brace
DECL|member|ImageType
id|U8
id|ImageType
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
id|U8
id|Reserved1
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 04h */
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
id|SGE_MPI_UNION
id|SGL
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|typedef|MSG_FW_DOWNLOAD
DECL|typedef|PTR_MSG_FW_DOWNLOAD
)brace
id|MSG_FW_DOWNLOAD
comma
id|MPI_POINTER
id|PTR_MSG_FW_DOWNLOAD
comma
DECL|typedef|FWDownload_t
DECL|typedef|pFWDownload_t
id|FWDownload_t
comma
id|MPI_POINTER
id|pFWDownload_t
suffix:semicolon
DECL|macro|MPI_FW_DOWNLOAD_ITYPE_RESERVED
mdefine_line|#define MPI_FW_DOWNLOAD_ITYPE_RESERVED      (0x00)
DECL|macro|MPI_FW_DOWNLOAD_ITYPE_FW
mdefine_line|#define MPI_FW_DOWNLOAD_ITYPE_FW            (0x01)
DECL|macro|MPI_FW_DOWNLOAD_ITYPE_BIOS
mdefine_line|#define MPI_FW_DOWNLOAD_ITYPE_BIOS          (0x02)
DECL|macro|MPI_FW_DOWNLOAD_ITYPE_NVDATA
mdefine_line|#define MPI_FW_DOWNLOAD_ITYPE_NVDATA        (0x03)
DECL|struct|_FWDownloadTCSGE
r_typedef
r_struct
id|_FWDownloadTCSGE
(brace
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|ContextSize
id|U8
id|ContextSize
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|DetailsLength
id|U8
id|DetailsLength
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|Flags
id|U8
id|Flags
suffix:semicolon
multiline_comment|/* 03h */
DECL|member|Reserved_0100_Checksum
id|U32
id|Reserved_0100_Checksum
suffix:semicolon
multiline_comment|/* 04h */
multiline_comment|/* obsolete Checksum */
DECL|member|ImageOffset
id|U32
id|ImageOffset
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|ImageSize
id|U32
id|ImageSize
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|typedef|FW_DOWNLOAD_TCSGE
DECL|typedef|PTR_FW_DOWNLOAD_TCSGE
)brace
id|FW_DOWNLOAD_TCSGE
comma
id|MPI_POINTER
id|PTR_FW_DOWNLOAD_TCSGE
comma
DECL|typedef|FWDownloadTCSGE_t
DECL|typedef|pFWDownloadTCSGE_t
id|FWDownloadTCSGE_t
comma
id|MPI_POINTER
id|pFWDownloadTCSGE_t
suffix:semicolon
multiline_comment|/* Firmware Download reply */
DECL|struct|_MSG_FW_DOWNLOAD_REPLY
r_typedef
r_struct
id|_MSG_FW_DOWNLOAD_REPLY
(brace
DECL|member|ImageType
id|U8
id|ImageType
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
id|U8
id|Reserved1
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 04h */
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
id|U16
id|Reserved2
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
DECL|typedef|MSG_FW_DOWNLOAD_REPLY
DECL|typedef|PTR_MSG_FW_DOWNLOAD_REPLY
)brace
id|MSG_FW_DOWNLOAD_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_FW_DOWNLOAD_REPLY
comma
DECL|typedef|FWDownloadReply_t
DECL|typedef|pFWDownloadReply_t
id|FWDownloadReply_t
comma
id|MPI_POINTER
id|pFWDownloadReply_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/*  Firmware Upload message and associated structures                       */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_FW_UPLOAD
r_typedef
r_struct
id|_MSG_FW_UPLOAD
(brace
DECL|member|ImageType
id|U8
id|ImageType
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
id|U8
id|Reserved1
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 04h */
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
id|SGE_MPI_UNION
id|SGL
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|typedef|MSG_FW_UPLOAD
DECL|typedef|PTR_MSG_FW_UPLOAD
)brace
id|MSG_FW_UPLOAD
comma
id|MPI_POINTER
id|PTR_MSG_FW_UPLOAD
comma
DECL|typedef|FWUpload_t
DECL|typedef|pFWUpload_t
id|FWUpload_t
comma
id|MPI_POINTER
id|pFWUpload_t
suffix:semicolon
DECL|macro|MPI_FW_UPLOAD_ITYPE_FW_IOC_MEM
mdefine_line|#define MPI_FW_UPLOAD_ITYPE_FW_IOC_MEM      (0x00)
DECL|macro|MPI_FW_UPLOAD_ITYPE_FW_FLASH
mdefine_line|#define MPI_FW_UPLOAD_ITYPE_FW_FLASH        (0x01)
DECL|macro|MPI_FW_UPLOAD_ITYPE_BIOS_FLASH
mdefine_line|#define MPI_FW_UPLOAD_ITYPE_BIOS_FLASH      (0x02)
DECL|macro|MPI_FW_UPLOAD_ITYPE_NVDATA
mdefine_line|#define MPI_FW_UPLOAD_ITYPE_NVDATA          (0x03)
DECL|struct|_FWUploadTCSGE
r_typedef
r_struct
id|_FWUploadTCSGE
(brace
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|ContextSize
id|U8
id|ContextSize
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|DetailsLength
id|U8
id|DetailsLength
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|Flags
id|U8
id|Flags
suffix:semicolon
multiline_comment|/* 03h */
DECL|member|Reserved1
id|U32
id|Reserved1
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|ImageOffset
id|U32
id|ImageOffset
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|ImageSize
id|U32
id|ImageSize
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|typedef|FW_UPLOAD_TCSGE
DECL|typedef|PTR_FW_UPLOAD_TCSGE
)brace
id|FW_UPLOAD_TCSGE
comma
id|MPI_POINTER
id|PTR_FW_UPLOAD_TCSGE
comma
DECL|typedef|FWUploadTCSGE_t
DECL|typedef|pFWUploadTCSGE_t
id|FWUploadTCSGE_t
comma
id|MPI_POINTER
id|pFWUploadTCSGE_t
suffix:semicolon
multiline_comment|/* Firmware Upload reply */
DECL|struct|_MSG_FW_UPLOAD_REPLY
r_typedef
r_struct
id|_MSG_FW_UPLOAD_REPLY
(brace
DECL|member|ImageType
id|U8
id|ImageType
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
id|U8
id|Reserved1
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 04h */
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
id|U16
id|Reserved2
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
DECL|member|ActualImageSize
id|U32
id|ActualImageSize
suffix:semicolon
multiline_comment|/* 14h */
DECL|typedef|MSG_FW_UPLOAD_REPLY
DECL|typedef|PTR_MSG_FW_UPLOAD_REPLY
)brace
id|MSG_FW_UPLOAD_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_FW_UPLOAD_REPLY
comma
DECL|typedef|FWUploadReply_t
DECL|typedef|pFWUploadReply_t
id|FWUploadReply_t
comma
id|MPI_POINTER
id|pFWUploadReply_t
suffix:semicolon
DECL|struct|_MPI_FW_HEADER
r_typedef
r_struct
id|_MPI_FW_HEADER
(brace
DECL|member|ArmBranchInstruction0
id|U32
id|ArmBranchInstruction0
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Signature0
id|U32
id|Signature0
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Signature1
id|U32
id|Signature1
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|Signature2
id|U32
id|Signature2
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|ArmBranchInstruction1
id|U32
id|ArmBranchInstruction1
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|ArmBranchInstruction2
id|U32
id|ArmBranchInstruction2
suffix:semicolon
multiline_comment|/* 14h */
DECL|member|Reserved
id|U32
id|Reserved
suffix:semicolon
multiline_comment|/* 18h */
DECL|member|Checksum
id|U32
id|Checksum
suffix:semicolon
multiline_comment|/* 1Ch */
DECL|member|VendorId
id|U16
id|VendorId
suffix:semicolon
multiline_comment|/* 20h */
DECL|member|ProductId
id|U16
id|ProductId
suffix:semicolon
multiline_comment|/* 22h */
DECL|member|FWVersion
id|MPI_FW_VERSION
id|FWVersion
suffix:semicolon
multiline_comment|/* 24h */
DECL|member|SeqCodeVersion
id|U32
id|SeqCodeVersion
suffix:semicolon
multiline_comment|/* 28h */
DECL|member|ImageSize
id|U32
id|ImageSize
suffix:semicolon
multiline_comment|/* 2Ch */
DECL|member|NextImageHeaderOffset
id|U32
id|NextImageHeaderOffset
suffix:semicolon
multiline_comment|/* 30h */
DECL|member|LoadStartAddress
id|U32
id|LoadStartAddress
suffix:semicolon
multiline_comment|/* 34h */
DECL|member|IopResetVectorValue
id|U32
id|IopResetVectorValue
suffix:semicolon
multiline_comment|/* 38h */
DECL|member|IopResetRegAddr
id|U32
id|IopResetRegAddr
suffix:semicolon
multiline_comment|/* 3Ch */
DECL|member|VersionNameWhat
id|U32
id|VersionNameWhat
suffix:semicolon
multiline_comment|/* 40h */
DECL|member|VersionName
id|U8
id|VersionName
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* 44h */
DECL|member|VendorNameWhat
id|U32
id|VendorNameWhat
suffix:semicolon
multiline_comment|/* 64h */
DECL|member|VendorName
id|U8
id|VendorName
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* 68h */
DECL|typedef|MPI_FW_HEADER
DECL|typedef|PTR_MPI_FW_HEADER
)brace
id|MPI_FW_HEADER
comma
id|MPI_POINTER
id|PTR_MPI_FW_HEADER
comma
DECL|typedef|MpiFwHeader_t
DECL|typedef|pMpiFwHeader_t
id|MpiFwHeader_t
comma
id|MPI_POINTER
id|pMpiFwHeader_t
suffix:semicolon
DECL|macro|MPI_FW_HEADER_WHAT_SIGNATURE
mdefine_line|#define MPI_FW_HEADER_WHAT_SIGNATURE        (0x29232840)
multiline_comment|/* defines for using the ProductId field */
DECL|macro|MPI_FW_HEADER_PID_TYPE_MASK
mdefine_line|#define MPI_FW_HEADER_PID_TYPE_MASK             (0xF000)
DECL|macro|MPI_FW_HEADER_PID_TYPE_SCSI
mdefine_line|#define MPI_FW_HEADER_PID_TYPE_SCSI             (0x0000)
DECL|macro|MPI_FW_HEADER_PID_TYPE_FC
mdefine_line|#define MPI_FW_HEADER_PID_TYPE_FC               (0x1000)
DECL|macro|MPI_FW_HEADER_PID_PROD_MASK
mdefine_line|#define MPI_FW_HEADER_PID_PROD_MASK                     (0x0F00)
DECL|macro|MPI_FW_HEADER_PID_PROD_INITIATOR_SCSI
mdefine_line|#define MPI_FW_HEADER_PID_PROD_INITIATOR_SCSI           (0x0100)
DECL|macro|MPI_FW_HEADER_PID_PROD_TARGET_INITIATOR_SCSI
mdefine_line|#define MPI_FW_HEADER_PID_PROD_TARGET_INITIATOR_SCSI    (0x0200)
DECL|macro|MPI_FW_HEADER_PID_PROD_TARGET_SCSI
mdefine_line|#define MPI_FW_HEADER_PID_PROD_TARGET_SCSI              (0x0300)
DECL|macro|MPI_FW_HEADER_PID_PROD_IM_SCSI
mdefine_line|#define MPI_FW_HEADER_PID_PROD_IM_SCSI                  (0x0400)
DECL|macro|MPI_FW_HEADER_PID_PROD_IS_SCSI
mdefine_line|#define MPI_FW_HEADER_PID_PROD_IS_SCSI                  (0x0500)
DECL|macro|MPI_FW_HEADER_PID_PROD_CTX_SCSI
mdefine_line|#define MPI_FW_HEADER_PID_PROD_CTX_SCSI                 (0x0600)
DECL|macro|MPI_FW_HEADER_PID_FAMILY_MASK
mdefine_line|#define MPI_FW_HEADER_PID_FAMILY_MASK           (0x00FF)
DECL|macro|MPI_FW_HEADER_PID_FAMILY_1030A0_SCSI
mdefine_line|#define MPI_FW_HEADER_PID_FAMILY_1030A0_SCSI    (0x0001)
DECL|macro|MPI_FW_HEADER_PID_FAMILY_1030B0_SCSI
mdefine_line|#define MPI_FW_HEADER_PID_FAMILY_1030B0_SCSI    (0x0002)
DECL|macro|MPI_FW_HEADER_PID_FAMILY_1030B1_SCSI
mdefine_line|#define MPI_FW_HEADER_PID_FAMILY_1030B1_SCSI    (0x0003)
DECL|macro|MPI_FW_HEADER_PID_FAMILY_1030C0_SCSI
mdefine_line|#define MPI_FW_HEADER_PID_FAMILY_1030C0_SCSI    (0x0004)
DECL|macro|MPI_FW_HEADER_PID_FAMILY_1020A0_SCSI
mdefine_line|#define MPI_FW_HEADER_PID_FAMILY_1020A0_SCSI    (0x0005)
DECL|macro|MPI_FW_HEADER_PID_FAMILY_1020B0_SCSI
mdefine_line|#define MPI_FW_HEADER_PID_FAMILY_1020B0_SCSI    (0x0006)
DECL|macro|MPI_FW_HEADER_PID_FAMILY_1020B1_SCSI
mdefine_line|#define MPI_FW_HEADER_PID_FAMILY_1020B1_SCSI    (0x0007)
DECL|macro|MPI_FW_HEADER_PID_FAMILY_1020C0_SCSI
mdefine_line|#define MPI_FW_HEADER_PID_FAMILY_1020C0_SCSI    (0x0008)
DECL|macro|MPI_FW_HEADER_PID_FAMILY_1035A0_SCSI
mdefine_line|#define MPI_FW_HEADER_PID_FAMILY_1035A0_SCSI    (0x0009)
DECL|macro|MPI_FW_HEADER_PID_FAMILY_1035B0_SCSI
mdefine_line|#define MPI_FW_HEADER_PID_FAMILY_1035B0_SCSI    (0x000A)
DECL|macro|MPI_FW_HEADER_PID_FAMILY_909_FC
mdefine_line|#define MPI_FW_HEADER_PID_FAMILY_909_FC         (0x0000)
DECL|macro|MPI_FW_HEADER_PID_FAMILY_919_FC
mdefine_line|#define MPI_FW_HEADER_PID_FAMILY_919_FC         (0x0001)
DECL|macro|MPI_FW_HEADER_PID_FAMILY_919X_FC
mdefine_line|#define MPI_FW_HEADER_PID_FAMILY_919X_FC        (0x0002)
DECL|struct|_MPI_EXT_IMAGE_HEADER
r_typedef
r_struct
id|_MPI_EXT_IMAGE_HEADER
(brace
DECL|member|ImageType
id|U8
id|ImageType
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|Checksum
id|U32
id|Checksum
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|ImageSize
id|U32
id|ImageSize
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|NextImageHeaderOffset
id|U32
id|NextImageHeaderOffset
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|LoadStartAddress
id|U32
id|LoadStartAddress
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|Reserved2
id|U32
id|Reserved2
suffix:semicolon
multiline_comment|/* 14h */
DECL|typedef|MPI_EXT_IMAGE_HEADER
DECL|typedef|PTR_MPI_EXT_IMAGE_HEADER
)brace
id|MPI_EXT_IMAGE_HEADER
comma
id|MPI_POINTER
id|PTR_MPI_EXT_IMAGE_HEADER
comma
DECL|typedef|MpiExtImageHeader_t
DECL|typedef|pMpiExtImageHeader_t
id|MpiExtImageHeader_t
comma
id|MPI_POINTER
id|pMpiExtImageHeader_t
suffix:semicolon
multiline_comment|/* defines for the ImageType field */
DECL|macro|MPI_EXT_IMAGE_TYPE_UNSPECIFIED
mdefine_line|#define MPI_EXT_IMAGE_TYPE_UNSPECIFIED          (0x00)
DECL|macro|MPI_EXT_IMAGE_TYPE_FW
mdefine_line|#define MPI_EXT_IMAGE_TYPE_FW                   (0x01)
DECL|macro|MPI_EXT_IMAGE_TYPE_NVDATA
mdefine_line|#define MPI_EXT_IMAGE_TYPE_NVDATA               (0x03)
macro_line|#endif
eof
