multiline_comment|/*&n; *  Copyright (c) 2000-2001 LSI Logic Corporation.&n; *&n; *&n; *           Name:  MPI.H&n; *          Title:  MPI Message independent structures and definitions&n; *  Creation Date:  July 27, 2000&n; *&n; *    MPI Version:  01.02.03&n; *&n; *  Version History&n; *  ---------------&n; *&n; *  Date      Version   Description&n; *  --------  --------  ------------------------------------------------------&n; *  05-08-00  00.10.01  Original release for 0.10 spec dated 4/26/2000.&n; *  05-24-00  00.10.02  Added MPI_IOCSTATUS_SCSI_RESIDUAL_MISMATCH definition.&n; *  06-06-00  01.00.01  Update MPI_VERSION_MAJOR and MPI_VERSION_MINOR.&n; *  06-22-00  01.00.02  Added MPI_IOCSTATUS_LAN_ definitions.&n; *                      Removed LAN_SUSPEND function definition.&n; *                      Added MPI_MSGFLAGS_CONTINUATION_REPLY definition.&n; *  06-30-00  01.00.03  Added MPI_CONTEXT_REPLY_TYPE_LAN definition.&n; *                      Added MPI_GET/SET_CONTEXT_REPLY_TYPE macros.&n; *  07-27-00  01.00.04  Added MPI_FAULT_ definitions.&n; *                      Removed MPI_IOCSTATUS_MSG/DATA_XFER_ERROR definitions.&n; *                      Added MPI_IOCSTATUS_INTERNAL_ERROR definition.&n; *                      Added MPI_IOCSTATUS_TARGET_XFER_COUNT_MISMATCH.&n; *  11-02-00  01.01.01  Original release for post 1.0 work.&n; *  12-04-00  01.01.02  Added new function codes.&n; *  01-09-01  01.01.03  Added more definitions to the system interface section&n; *                      Added MPI_IOCSTATUS_TARGET_STS_DATA_NOT_SENT.&n; *  01-25-01  01.01.04  Changed MPI_VERSION_MINOR from 0x00 to 0x01.&n; *  02-20-01  01.01.05  Started using MPI_POINTER.&n; *                      Fixed value for MPI_DIAG_RW_ENABLE.&n; *                      Added defines for MPI_DIAG_PREVENT_IOC_BOOT and&n; *                      MPI_DIAG_CLEAR_FLASH_BAD_SIG.&n; *                      Obsoleted MPI_IOCSTATUS_TARGET_FC_ defines.&n; *  02-27-01  01.01.06  Removed MPI_HOST_INDEX_REGISTER define.&n; *                      Added function codes for RAID.&n; *  04-09-01  01.01.07  Added alternate define for MPI_DOORBELL_ACTIVE,&n; *                      MPI_DOORBELL_USED, to better match the spec.&n; *  08-08-01  01.02.01  Original release for v1.2 work.&n; *                      Changed MPI_VERSION_MINOR from 0x01 to 0x02.&n; *                      Added define MPI_FUNCTION_TOOLBOX.&n; *  09-28-01  01.02.02  New function code MPI_SCSI_ENCLOSURE_PROCESSOR.&n; *  11-01-01  01.02.03  Changed name to MPI_FUNCTION_SCSI_ENCLOSURE_PROCESSOR.&n; *  --------------------------------------------------------------------------&n; */
macro_line|#ifndef MPI_H
DECL|macro|MPI_H
mdefine_line|#define MPI_H
multiline_comment|/*****************************************************************************&n;*&n;*        M P I    V e r s i o n    D e f i n i t i o n s&n;*&n;*****************************************************************************/
DECL|macro|MPI_VERSION_MAJOR
mdefine_line|#define MPI_VERSION_MAJOR                   (0x01)
DECL|macro|MPI_VERSION_MINOR
mdefine_line|#define MPI_VERSION_MINOR                   (0x02)
DECL|macro|MPI_VERSION
mdefine_line|#define MPI_VERSION            ((MPI_VERSION_MAJOR &lt;&lt; 8) | MPI_VERSION_MINOR)
multiline_comment|/* Note: The major versions of 0xe0 through 0xff are reserved */
multiline_comment|/*****************************************************************************&n;*&n;*        I O C    S t a t e    D e f i n i t i o n s&n;*&n;*****************************************************************************/
DECL|macro|MPI_IOC_STATE_RESET
mdefine_line|#define MPI_IOC_STATE_RESET                 (0x00000000)
DECL|macro|MPI_IOC_STATE_READY
mdefine_line|#define MPI_IOC_STATE_READY                 (0x10000000)
DECL|macro|MPI_IOC_STATE_OPERATIONAL
mdefine_line|#define MPI_IOC_STATE_OPERATIONAL           (0x20000000)
DECL|macro|MPI_IOC_STATE_FAULT
mdefine_line|#define MPI_IOC_STATE_FAULT                 (0x40000000)
DECL|macro|MPI_IOC_STATE_MASK
mdefine_line|#define MPI_IOC_STATE_MASK                  (0xF0000000)
DECL|macro|MPI_IOC_STATE_SHIFT
mdefine_line|#define MPI_IOC_STATE_SHIFT                 (28)
multiline_comment|/* Fault state codes (product independent range 0x8000-0xFFFF) */
DECL|macro|MPI_FAULT_REQUEST_MESSAGE_PCI_PARITY_ERROR
mdefine_line|#define MPI_FAULT_REQUEST_MESSAGE_PCI_PARITY_ERROR  (0x8111)
DECL|macro|MPI_FAULT_REQUEST_MESSAGE_PCI_BUS_FAULT
mdefine_line|#define MPI_FAULT_REQUEST_MESSAGE_PCI_BUS_FAULT     (0x8112)
DECL|macro|MPI_FAULT_REPLY_MESSAGE_PCI_PARITY_ERROR
mdefine_line|#define MPI_FAULT_REPLY_MESSAGE_PCI_PARITY_ERROR    (0x8113)
DECL|macro|MPI_FAULT_REPLY_MESSAGE_PCI_BUS_FAULT
mdefine_line|#define MPI_FAULT_REPLY_MESSAGE_PCI_BUS_FAULT       (0x8114)
DECL|macro|MPI_FAULT_DATA_SEND_PCI_PARITY_ERROR
mdefine_line|#define MPI_FAULT_DATA_SEND_PCI_PARITY_ERROR        (0x8115)
DECL|macro|MPI_FAULT_DATA_SEND_PCI_BUS_FAULT
mdefine_line|#define MPI_FAULT_DATA_SEND_PCI_BUS_FAULT           (0x8116)
DECL|macro|MPI_FAULT_DATA_RECEIVE_PCI_PARITY_ERROR
mdefine_line|#define MPI_FAULT_DATA_RECEIVE_PCI_PARITY_ERROR     (0x8117)
DECL|macro|MPI_FAULT_DATA_RECEIVE_PCI_BUS_FAULT
mdefine_line|#define MPI_FAULT_DATA_RECEIVE_PCI_BUS_FAULT        (0x8118)
multiline_comment|/*****************************************************************************&n;*&n;*        P C I    S y s t e m    I n t e r f a c e    R e g i s t e r s&n;*&n;*****************************************************************************/
multiline_comment|/* S y s t e m    D o o r b e l l */
DECL|macro|MPI_DOORBELL_OFFSET
mdefine_line|#define MPI_DOORBELL_OFFSET                 (0x00000000)
DECL|macro|MPI_DOORBELL_ACTIVE
mdefine_line|#define MPI_DOORBELL_ACTIVE                 (0x08000000) /* DoorbellUsed */
DECL|macro|MPI_DOORBELL_USED
mdefine_line|#define MPI_DOORBELL_USED                   (MPI_DOORBELL_ACTIVE)
DECL|macro|MPI_DOORBELL_ACTIVE_SHIFT
mdefine_line|#define MPI_DOORBELL_ACTIVE_SHIFT           (27)
DECL|macro|MPI_DOORBELL_WHO_INIT_MASK
mdefine_line|#define MPI_DOORBELL_WHO_INIT_MASK          (0x07000000)
DECL|macro|MPI_DOORBELL_WHO_INIT_SHIFT
mdefine_line|#define MPI_DOORBELL_WHO_INIT_SHIFT         (24)
DECL|macro|MPI_DOORBELL_FUNCTION_MASK
mdefine_line|#define MPI_DOORBELL_FUNCTION_MASK          (0xFF000000)
DECL|macro|MPI_DOORBELL_FUNCTION_SHIFT
mdefine_line|#define MPI_DOORBELL_FUNCTION_SHIFT         (24)
DECL|macro|MPI_DOORBELL_ADD_DWORDS_MASK
mdefine_line|#define MPI_DOORBELL_ADD_DWORDS_MASK        (0x00FF0000)
DECL|macro|MPI_DOORBELL_ADD_DWORDS_SHIFT
mdefine_line|#define MPI_DOORBELL_ADD_DWORDS_SHIFT       (16)
DECL|macro|MPI_DOORBELL_DATA_MASK
mdefine_line|#define MPI_DOORBELL_DATA_MASK              (0x0000FFFF)
DECL|macro|MPI_WRITE_SEQUENCE_OFFSET
mdefine_line|#define MPI_WRITE_SEQUENCE_OFFSET           (0x00000004)
DECL|macro|MPI_WRSEQ_KEY_VALUE_MASK
mdefine_line|#define MPI_WRSEQ_KEY_VALUE_MASK            (0x0000000F)
DECL|macro|MPI_WRSEQ_1ST_KEY_VALUE
mdefine_line|#define MPI_WRSEQ_1ST_KEY_VALUE             (0x04)
DECL|macro|MPI_WRSEQ_2ND_KEY_VALUE
mdefine_line|#define MPI_WRSEQ_2ND_KEY_VALUE             (0x0B)
DECL|macro|MPI_WRSEQ_3RD_KEY_VALUE
mdefine_line|#define MPI_WRSEQ_3RD_KEY_VALUE             (0x02)
DECL|macro|MPI_WRSEQ_4TH_KEY_VALUE
mdefine_line|#define MPI_WRSEQ_4TH_KEY_VALUE             (0x07)
DECL|macro|MPI_WRSEQ_5TH_KEY_VALUE
mdefine_line|#define MPI_WRSEQ_5TH_KEY_VALUE             (0x0D)
DECL|macro|MPI_DIAGNOSTIC_OFFSET
mdefine_line|#define MPI_DIAGNOSTIC_OFFSET               (0x00000008)
DECL|macro|MPI_DIAG_CLEAR_FLASH_BAD_SIG
mdefine_line|#define MPI_DIAG_CLEAR_FLASH_BAD_SIG        (0x00000400)
DECL|macro|MPI_DIAG_PREVENT_IOC_BOOT
mdefine_line|#define MPI_DIAG_PREVENT_IOC_BOOT           (0x00000200)
DECL|macro|MPI_DIAG_DRWE
mdefine_line|#define MPI_DIAG_DRWE                       (0x00000080)
DECL|macro|MPI_DIAG_FLASH_BAD_SIG
mdefine_line|#define MPI_DIAG_FLASH_BAD_SIG              (0x00000040)
DECL|macro|MPI_DIAG_RESET_HISTORY
mdefine_line|#define MPI_DIAG_RESET_HISTORY              (0x00000020)
DECL|macro|MPI_DIAG_RW_ENABLE
mdefine_line|#define MPI_DIAG_RW_ENABLE                  (0x00000010)
DECL|macro|MPI_DIAG_RESET_ADAPTER
mdefine_line|#define MPI_DIAG_RESET_ADAPTER              (0x00000004)
DECL|macro|MPI_DIAG_DISABLE_ARM
mdefine_line|#define MPI_DIAG_DISABLE_ARM                (0x00000002)
DECL|macro|MPI_DIAG_MEM_ENABLE
mdefine_line|#define MPI_DIAG_MEM_ENABLE                 (0x00000001)
DECL|macro|MPI_TEST_BASE_ADDRESS_OFFSET
mdefine_line|#define MPI_TEST_BASE_ADDRESS_OFFSET        (0x0000000C)
DECL|macro|MPI_DIAG_RW_DATA_OFFSET
mdefine_line|#define MPI_DIAG_RW_DATA_OFFSET             (0x00000010)
DECL|macro|MPI_DIAG_RW_ADDRESS_OFFSET
mdefine_line|#define MPI_DIAG_RW_ADDRESS_OFFSET          (0x00000014)
DECL|macro|MPI_HOST_INTERRUPT_STATUS_OFFSET
mdefine_line|#define MPI_HOST_INTERRUPT_STATUS_OFFSET    (0x00000030)
DECL|macro|MPI_HIS_IOP_DOORBELL_STATUS
mdefine_line|#define MPI_HIS_IOP_DOORBELL_STATUS         (0x80000000)
DECL|macro|MPI_HIS_REPLY_MESSAGE_INTERRUPT
mdefine_line|#define MPI_HIS_REPLY_MESSAGE_INTERRUPT     (0x00000008)
DECL|macro|MPI_HIS_DOORBELL_INTERRUPT
mdefine_line|#define MPI_HIS_DOORBELL_INTERRUPT          (0x00000001)
DECL|macro|MPI_HOST_INTERRUPT_MASK_OFFSET
mdefine_line|#define MPI_HOST_INTERRUPT_MASK_OFFSET      (0x00000034)
DECL|macro|MPI_HIM_RIM
mdefine_line|#define MPI_HIM_RIM                         (0x00000008)
DECL|macro|MPI_HIM_DIM
mdefine_line|#define MPI_HIM_DIM                         (0x00000001)
DECL|macro|MPI_REQUEST_QUEUE_OFFSET
mdefine_line|#define MPI_REQUEST_QUEUE_OFFSET            (0x00000040)
DECL|macro|MPI_REQUEST_POST_FIFO_OFFSET
mdefine_line|#define MPI_REQUEST_POST_FIFO_OFFSET        (0x00000040)
DECL|macro|MPI_REPLY_QUEUE_OFFSET
mdefine_line|#define MPI_REPLY_QUEUE_OFFSET              (0x00000044)
DECL|macro|MPI_REPLY_POST_FIFO_OFFSET
mdefine_line|#define MPI_REPLY_POST_FIFO_OFFSET          (0x00000044)
DECL|macro|MPI_REPLY_FREE_FIFO_OFFSET
mdefine_line|#define MPI_REPLY_FREE_FIFO_OFFSET          (0x00000044)
multiline_comment|/*****************************************************************************&n;*&n;*        M e s s a g e    F r a m e    D e s c r i p t o r s&n;*&n;*****************************************************************************/
DECL|macro|MPI_REQ_MF_DESCRIPTOR_NB_MASK
mdefine_line|#define MPI_REQ_MF_DESCRIPTOR_NB_MASK       (0x00000003)
DECL|macro|MPI_REQ_MF_DESCRIPTOR_F_BIT
mdefine_line|#define MPI_REQ_MF_DESCRIPTOR_F_BIT         (0x00000004)
DECL|macro|MPI_REQ_MF_DESCRIPTOR_ADDRESS_MASK
mdefine_line|#define MPI_REQ_MF_DESCRIPTOR_ADDRESS_MASK  (0xFFFFFFF8)
DECL|macro|MPI_ADDRESS_REPLY_A_BIT
mdefine_line|#define MPI_ADDRESS_REPLY_A_BIT             (0x80000000)
DECL|macro|MPI_ADDRESS_REPLY_ADDRESS_MASK
mdefine_line|#define MPI_ADDRESS_REPLY_ADDRESS_MASK      (0x7FFFFFFF)
DECL|macro|MPI_CONTEXT_REPLY_A_BIT
mdefine_line|#define MPI_CONTEXT_REPLY_A_BIT             (0x80000000)
DECL|macro|MPI_CONTEXT_REPLY_TYPE_MASK
mdefine_line|#define MPI_CONTEXT_REPLY_TYPE_MASK         (0x60000000)
DECL|macro|MPI_CONTEXT_REPLY_TYPE_SCSI_INIT
mdefine_line|#define MPI_CONTEXT_REPLY_TYPE_SCSI_INIT    (0x00)
DECL|macro|MPI_CONTEXT_REPLY_TYPE_SCSI_TARGET
mdefine_line|#define MPI_CONTEXT_REPLY_TYPE_SCSI_TARGET  (0x01)
DECL|macro|MPI_CONTEXT_REPLY_TYPE_LAN
mdefine_line|#define MPI_CONTEXT_REPLY_TYPE_LAN          (0x02)
DECL|macro|MPI_CONTEXT_REPLY_TYPE_SHIFT
mdefine_line|#define MPI_CONTEXT_REPLY_TYPE_SHIFT        (29)
DECL|macro|MPI_CONTEXT_REPLY_CONTEXT_MASK
mdefine_line|#define MPI_CONTEXT_REPLY_CONTEXT_MASK      (0x1FFFFFFF)
multiline_comment|/****************************************************************************/
multiline_comment|/* Context Reply macros                                                     */
multiline_comment|/****************************************************************************/
DECL|macro|MPI_GET_CONTEXT_REPLY_TYPE
mdefine_line|#define MPI_GET_CONTEXT_REPLY_TYPE(x)  (((x) &amp; MPI_CONTEXT_REPLY_TYPE_MASK) &bslash;&n;                                          &gt;&gt; MPI_CONTEXT_REPLY_TYPE_SHIFT)
DECL|macro|MPI_SET_CONTEXT_REPLY_TYPE
mdefine_line|#define MPI_SET_CONTEXT_REPLY_TYPE(x, typ)                                  &bslash;&n;            ((x) = ((x) &amp; ~MPI_CONTEXT_REPLY_TYPE_MASK) |                   &bslash;&n;                            (((typ) &lt;&lt; MPI_CONTEXT_REPLY_TYPE_SHIFT) &amp;      &bslash;&n;                                        MPI_CONTEXT_REPLY_TYPE_MASK))
multiline_comment|/*****************************************************************************&n;*&n;*        M e s s a g e    F u n c t i o n s&n;*              0x80 -&gt; 0x8F reserved for private message use per product&n;*&n;*&n;*****************************************************************************/
DECL|macro|MPI_FUNCTION_SCSI_IO_REQUEST
mdefine_line|#define MPI_FUNCTION_SCSI_IO_REQUEST                (0x00)
DECL|macro|MPI_FUNCTION_SCSI_TASK_MGMT
mdefine_line|#define MPI_FUNCTION_SCSI_TASK_MGMT                 (0x01)
DECL|macro|MPI_FUNCTION_IOC_INIT
mdefine_line|#define MPI_FUNCTION_IOC_INIT                       (0x02)
DECL|macro|MPI_FUNCTION_IOC_FACTS
mdefine_line|#define MPI_FUNCTION_IOC_FACTS                      (0x03)
DECL|macro|MPI_FUNCTION_CONFIG
mdefine_line|#define MPI_FUNCTION_CONFIG                         (0x04)
DECL|macro|MPI_FUNCTION_PORT_FACTS
mdefine_line|#define MPI_FUNCTION_PORT_FACTS                     (0x05)
DECL|macro|MPI_FUNCTION_PORT_ENABLE
mdefine_line|#define MPI_FUNCTION_PORT_ENABLE                    (0x06)
DECL|macro|MPI_FUNCTION_EVENT_NOTIFICATION
mdefine_line|#define MPI_FUNCTION_EVENT_NOTIFICATION             (0x07)
DECL|macro|MPI_FUNCTION_EVENT_ACK
mdefine_line|#define MPI_FUNCTION_EVENT_ACK                      (0x08)
DECL|macro|MPI_FUNCTION_FW_DOWNLOAD
mdefine_line|#define MPI_FUNCTION_FW_DOWNLOAD                    (0x09)
DECL|macro|MPI_FUNCTION_TARGET_CMD_BUFFER_POST
mdefine_line|#define MPI_FUNCTION_TARGET_CMD_BUFFER_POST         (0x0A)
DECL|macro|MPI_FUNCTION_TARGET_ASSIST
mdefine_line|#define MPI_FUNCTION_TARGET_ASSIST                  (0x0B)
DECL|macro|MPI_FUNCTION_TARGET_STATUS_SEND
mdefine_line|#define MPI_FUNCTION_TARGET_STATUS_SEND             (0x0C)
DECL|macro|MPI_FUNCTION_TARGET_MODE_ABORT
mdefine_line|#define MPI_FUNCTION_TARGET_MODE_ABORT              (0x0D)
DECL|macro|MPI_FUNCTION_TARGET_FC_BUF_POST_LINK_SRVC
mdefine_line|#define MPI_FUNCTION_TARGET_FC_BUF_POST_LINK_SRVC   (0x0E) /* obsolete name */
DECL|macro|MPI_FUNCTION_TARGET_FC_RSP_LINK_SRVC
mdefine_line|#define MPI_FUNCTION_TARGET_FC_RSP_LINK_SRVC        (0x0F) /* obsolete name */
DECL|macro|MPI_FUNCTION_TARGET_FC_EX_SEND_LINK_SRVC
mdefine_line|#define MPI_FUNCTION_TARGET_FC_EX_SEND_LINK_SRVC    (0x10) /* obsolete name */
DECL|macro|MPI_FUNCTION_TARGET_FC_ABORT
mdefine_line|#define MPI_FUNCTION_TARGET_FC_ABORT                (0x11) /* obsolete name */
DECL|macro|MPI_FUNCTION_FC_LINK_SRVC_BUF_POST
mdefine_line|#define MPI_FUNCTION_FC_LINK_SRVC_BUF_POST          (0x0E)
DECL|macro|MPI_FUNCTION_FC_LINK_SRVC_RSP
mdefine_line|#define MPI_FUNCTION_FC_LINK_SRVC_RSP               (0x0F)
DECL|macro|MPI_FUNCTION_FC_EX_LINK_SRVC_SEND
mdefine_line|#define MPI_FUNCTION_FC_EX_LINK_SRVC_SEND           (0x10)
DECL|macro|MPI_FUNCTION_FC_ABORT
mdefine_line|#define MPI_FUNCTION_FC_ABORT                       (0x11)
DECL|macro|MPI_FUNCTION_FW_UPLOAD
mdefine_line|#define MPI_FUNCTION_FW_UPLOAD                      (0x12)
DECL|macro|MPI_FUNCTION_FC_COMMON_TRANSPORT_SEND
mdefine_line|#define MPI_FUNCTION_FC_COMMON_TRANSPORT_SEND       (0x13)
DECL|macro|MPI_FUNCTION_FC_PRIMITIVE_SEND
mdefine_line|#define MPI_FUNCTION_FC_PRIMITIVE_SEND              (0x14)
DECL|macro|MPI_FUNCTION_RAID_ACTION
mdefine_line|#define MPI_FUNCTION_RAID_ACTION                    (0x15)
DECL|macro|MPI_FUNCTION_RAID_SCSI_IO_PASSTHROUGH
mdefine_line|#define MPI_FUNCTION_RAID_SCSI_IO_PASSTHROUGH       (0x16)
DECL|macro|MPI_FUNCTION_TOOLBOX
mdefine_line|#define MPI_FUNCTION_TOOLBOX                        (0x17)
DECL|macro|MPI_FUNCTION_SCSI_ENCLOSURE_PROCESSOR
mdefine_line|#define MPI_FUNCTION_SCSI_ENCLOSURE_PROCESSOR       (0x18)
DECL|macro|MPI_FUNCTION_LAN_SEND
mdefine_line|#define MPI_FUNCTION_LAN_SEND                       (0x20)
DECL|macro|MPI_FUNCTION_LAN_RECEIVE
mdefine_line|#define MPI_FUNCTION_LAN_RECEIVE                    (0x21)
DECL|macro|MPI_FUNCTION_LAN_RESET
mdefine_line|#define MPI_FUNCTION_LAN_RESET                      (0x22)
DECL|macro|MPI_FUNCTION_IOC_MESSAGE_UNIT_RESET
mdefine_line|#define MPI_FUNCTION_IOC_MESSAGE_UNIT_RESET         (0x40)
DECL|macro|MPI_FUNCTION_IO_UNIT_RESET
mdefine_line|#define MPI_FUNCTION_IO_UNIT_RESET                  (0x41)
DECL|macro|MPI_FUNCTION_HANDSHAKE
mdefine_line|#define MPI_FUNCTION_HANDSHAKE                      (0x42)
DECL|macro|MPI_FUNCTION_REPLY_FRAME_REMOVAL
mdefine_line|#define MPI_FUNCTION_REPLY_FRAME_REMOVAL            (0x43)
multiline_comment|/*****************************************************************************&n;*&n;*        S c a t t e r    G a t h e r    E l e m e n t s&n;*&n;*****************************************************************************/
multiline_comment|/****************************************************************************/
multiline_comment|/*  Simple element structures                                               */
multiline_comment|/****************************************************************************/
DECL|struct|_SGE_SIMPLE32
r_typedef
r_struct
id|_SGE_SIMPLE32
(brace
DECL|member|FlagsLength
id|U32
id|FlagsLength
suffix:semicolon
DECL|member|Address
id|U32
id|Address
suffix:semicolon
DECL|typedef|SGE_SIMPLE32
DECL|typedef|PTR_SGE_SIMPLE32
)brace
id|SGE_SIMPLE32
comma
id|MPI_POINTER
id|PTR_SGE_SIMPLE32
comma
DECL|typedef|SGESimple32_t
DECL|typedef|pSGESimple32_t
id|SGESimple32_t
comma
id|MPI_POINTER
id|pSGESimple32_t
suffix:semicolon
DECL|struct|_SGE_SIMPLE64
r_typedef
r_struct
id|_SGE_SIMPLE64
(brace
DECL|member|FlagsLength
id|U32
id|FlagsLength
suffix:semicolon
DECL|member|Address
id|U64
id|Address
suffix:semicolon
DECL|typedef|SGE_SIMPLE64
DECL|typedef|PTR_SGE_SIMPLE64
)brace
id|SGE_SIMPLE64
comma
id|MPI_POINTER
id|PTR_SGE_SIMPLE64
comma
DECL|typedef|SGESimple64_t
DECL|typedef|pSGESimple64_t
id|SGESimple64_t
comma
id|MPI_POINTER
id|pSGESimple64_t
suffix:semicolon
DECL|struct|_SGE_SIMPLE_UNION
r_typedef
r_struct
id|_SGE_SIMPLE_UNION
(brace
DECL|member|FlagsLength
id|U32
id|FlagsLength
suffix:semicolon
r_union
(brace
DECL|member|Address32
id|U32
id|Address32
suffix:semicolon
DECL|member|Address64
id|U64
id|Address64
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|typedef|SGESimpleUnion_t
DECL|typedef|pSGESimpleUnion_t
)brace
id|SGESimpleUnion_t
comma
id|MPI_POINTER
id|pSGESimpleUnion_t
comma
DECL|typedef|SGE_SIMPLE_UNION
DECL|typedef|PTR_SGE_SIMPLE_UNION
id|SGE_SIMPLE_UNION
comma
id|MPI_POINTER
id|PTR_SGE_SIMPLE_UNION
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/*  Chain element structures                                                */
multiline_comment|/****************************************************************************/
DECL|struct|_SGE_CHAIN32
r_typedef
r_struct
id|_SGE_CHAIN32
(brace
DECL|member|Length
id|U16
id|Length
suffix:semicolon
DECL|member|NextChainOffset
id|U8
id|NextChainOffset
suffix:semicolon
DECL|member|Flags
id|U8
id|Flags
suffix:semicolon
DECL|member|Address
id|U32
id|Address
suffix:semicolon
DECL|typedef|SGE_CHAIN32
DECL|typedef|PTR_SGE_CHAIN32
)brace
id|SGE_CHAIN32
comma
id|MPI_POINTER
id|PTR_SGE_CHAIN32
comma
DECL|typedef|SGEChain32_t
DECL|typedef|pSGEChain32_t
id|SGEChain32_t
comma
id|MPI_POINTER
id|pSGEChain32_t
suffix:semicolon
DECL|struct|_SGE_CHAIN64
r_typedef
r_struct
id|_SGE_CHAIN64
(brace
DECL|member|Length
id|U16
id|Length
suffix:semicolon
DECL|member|NextChainOffset
id|U8
id|NextChainOffset
suffix:semicolon
DECL|member|Flags
id|U8
id|Flags
suffix:semicolon
DECL|member|Address
id|U64
id|Address
suffix:semicolon
DECL|typedef|SGE_CHAIN64
DECL|typedef|PTR_SGE_CHAIN64
)brace
id|SGE_CHAIN64
comma
id|MPI_POINTER
id|PTR_SGE_CHAIN64
comma
DECL|typedef|SGEChain64_t
DECL|typedef|pSGEChain64_t
id|SGEChain64_t
comma
id|MPI_POINTER
id|pSGEChain64_t
suffix:semicolon
DECL|struct|_SGE_CHAIN_UNION
r_typedef
r_struct
id|_SGE_CHAIN_UNION
(brace
DECL|member|Length
id|U16
id|Length
suffix:semicolon
DECL|member|NextChainOffset
id|U8
id|NextChainOffset
suffix:semicolon
DECL|member|Flags
id|U8
id|Flags
suffix:semicolon
r_union
(brace
DECL|member|Address32
id|U32
id|Address32
suffix:semicolon
DECL|member|Address64
id|U64
id|Address64
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|typedef|SGE_CHAIN_UNION
DECL|typedef|PTR_SGE_CHAIN_UNION
)brace
id|SGE_CHAIN_UNION
comma
id|MPI_POINTER
id|PTR_SGE_CHAIN_UNION
comma
DECL|typedef|SGEChainUnion_t
DECL|typedef|pSGEChainUnion_t
id|SGEChainUnion_t
comma
id|MPI_POINTER
id|pSGEChainUnion_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/*  Transaction Context element                                             */
multiline_comment|/****************************************************************************/
DECL|struct|_SGE_TRANSACTION32
r_typedef
r_struct
id|_SGE_TRANSACTION32
(brace
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
DECL|member|ContextSize
id|U8
id|ContextSize
suffix:semicolon
DECL|member|DetailsLength
id|U8
id|DetailsLength
suffix:semicolon
DECL|member|Flags
id|U8
id|Flags
suffix:semicolon
DECL|member|TransactionContext
id|U32
id|TransactionContext
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|TransactionDetails
id|U32
id|TransactionDetails
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|SGE_TRANSACTION32
DECL|typedef|PTR_SGE_TRANSACTION32
)brace
id|SGE_TRANSACTION32
comma
id|MPI_POINTER
id|PTR_SGE_TRANSACTION32
comma
DECL|typedef|SGETransaction32_t
DECL|typedef|pSGETransaction32_t
id|SGETransaction32_t
comma
id|MPI_POINTER
id|pSGETransaction32_t
suffix:semicolon
DECL|struct|_SGE_TRANSACTION64
r_typedef
r_struct
id|_SGE_TRANSACTION64
(brace
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
DECL|member|ContextSize
id|U8
id|ContextSize
suffix:semicolon
DECL|member|DetailsLength
id|U8
id|DetailsLength
suffix:semicolon
DECL|member|Flags
id|U8
id|Flags
suffix:semicolon
DECL|member|TransactionContext
id|U32
id|TransactionContext
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|TransactionDetails
id|U32
id|TransactionDetails
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|SGE_TRANSACTION64
DECL|typedef|PTR_SGE_TRANSACTION64
)brace
id|SGE_TRANSACTION64
comma
id|MPI_POINTER
id|PTR_SGE_TRANSACTION64
comma
DECL|typedef|SGETransaction64_t
DECL|typedef|pSGETransaction64_t
id|SGETransaction64_t
comma
id|MPI_POINTER
id|pSGETransaction64_t
suffix:semicolon
DECL|struct|_SGE_TRANSACTION96
r_typedef
r_struct
id|_SGE_TRANSACTION96
(brace
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
DECL|member|ContextSize
id|U8
id|ContextSize
suffix:semicolon
DECL|member|DetailsLength
id|U8
id|DetailsLength
suffix:semicolon
DECL|member|Flags
id|U8
id|Flags
suffix:semicolon
DECL|member|TransactionContext
id|U32
id|TransactionContext
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|TransactionDetails
id|U32
id|TransactionDetails
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|SGE_TRANSACTION96
DECL|typedef|PTR_SGE_TRANSACTION96
)brace
id|SGE_TRANSACTION96
comma
id|MPI_POINTER
id|PTR_SGE_TRANSACTION96
comma
DECL|typedef|SGETransaction96_t
DECL|typedef|pSGETransaction96_t
id|SGETransaction96_t
comma
id|MPI_POINTER
id|pSGETransaction96_t
suffix:semicolon
DECL|struct|_SGE_TRANSACTION128
r_typedef
r_struct
id|_SGE_TRANSACTION128
(brace
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
DECL|member|ContextSize
id|U8
id|ContextSize
suffix:semicolon
DECL|member|DetailsLength
id|U8
id|DetailsLength
suffix:semicolon
DECL|member|Flags
id|U8
id|Flags
suffix:semicolon
DECL|member|TransactionContext
id|U32
id|TransactionContext
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|TransactionDetails
id|U32
id|TransactionDetails
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|SGE_TRANSACTION128
DECL|typedef|PTR_SGE_TRANSACTION128
)brace
id|SGE_TRANSACTION128
comma
id|MPI_POINTER
id|PTR_SGE_TRANSACTION128
comma
DECL|typedef|SGETransaction_t128
DECL|typedef|pSGETransaction_t128
id|SGETransaction_t128
comma
id|MPI_POINTER
id|pSGETransaction_t128
suffix:semicolon
DECL|struct|_SGE_TRANSACTION_UNION
r_typedef
r_struct
id|_SGE_TRANSACTION_UNION
(brace
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
DECL|member|ContextSize
id|U8
id|ContextSize
suffix:semicolon
DECL|member|DetailsLength
id|U8
id|DetailsLength
suffix:semicolon
DECL|member|Flags
id|U8
id|Flags
suffix:semicolon
r_union
(brace
DECL|member|TransactionContext32
id|U32
id|TransactionContext32
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|TransactionContext64
id|U32
id|TransactionContext64
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|TransactionContext96
id|U32
id|TransactionContext96
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|TransactionContext128
id|U32
id|TransactionContext128
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|TransactionDetails
id|U32
id|TransactionDetails
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|SGE_TRANSACTION_UNION
DECL|typedef|PTR_SGE_TRANSACTION_UNION
)brace
id|SGE_TRANSACTION_UNION
comma
id|MPI_POINTER
id|PTR_SGE_TRANSACTION_UNION
comma
DECL|typedef|SGETransactionUnion_t
DECL|typedef|pSGETransactionUnion_t
id|SGETransactionUnion_t
comma
id|MPI_POINTER
id|pSGETransactionUnion_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/*  SGE IO types union  for IO SGL&squot;s                                        */
multiline_comment|/****************************************************************************/
DECL|struct|_SGE_IO_UNION
r_typedef
r_struct
id|_SGE_IO_UNION
(brace
r_union
(brace
DECL|member|Simple
id|SGE_SIMPLE_UNION
id|Simple
suffix:semicolon
DECL|member|Chain
id|SGE_CHAIN_UNION
id|Chain
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|typedef|SGE_IO_UNION
DECL|typedef|PTR_SGE_IO_UNION
)brace
id|SGE_IO_UNION
comma
id|MPI_POINTER
id|PTR_SGE_IO_UNION
comma
DECL|typedef|SGEIOUnion_t
DECL|typedef|pSGEIOUnion_t
id|SGEIOUnion_t
comma
id|MPI_POINTER
id|pSGEIOUnion_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/*  SGE union for SGL&squot;s with Simple and Transaction elements                */
multiline_comment|/****************************************************************************/
DECL|struct|_SGE_TRANS_SIMPLE_UNION
r_typedef
r_struct
id|_SGE_TRANS_SIMPLE_UNION
(brace
r_union
(brace
DECL|member|Simple
id|SGE_SIMPLE_UNION
id|Simple
suffix:semicolon
DECL|member|Transaction
id|SGE_TRANSACTION_UNION
id|Transaction
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|typedef|SGE_TRANS_SIMPLE_UNION
DECL|typedef|PTR_SGE_TRANS_SIMPLE_UNION
)brace
id|SGE_TRANS_SIMPLE_UNION
comma
id|MPI_POINTER
id|PTR_SGE_TRANS_SIMPLE_UNION
comma
DECL|typedef|SGETransSimpleUnion_t
DECL|typedef|pSGETransSimpleUnion_t
id|SGETransSimpleUnion_t
comma
id|MPI_POINTER
id|pSGETransSimpleUnion_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/*  All SGE types union                                                     */
multiline_comment|/****************************************************************************/
DECL|struct|_SGE_MPI_UNION
r_typedef
r_struct
id|_SGE_MPI_UNION
(brace
r_union
(brace
DECL|member|Simple
id|SGE_SIMPLE_UNION
id|Simple
suffix:semicolon
DECL|member|Chain
id|SGE_CHAIN_UNION
id|Chain
suffix:semicolon
DECL|member|Transaction
id|SGE_TRANSACTION_UNION
id|Transaction
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|typedef|SGE_MPI_UNION
DECL|typedef|PTR_SGE_MPI_UNION
)brace
id|SGE_MPI_UNION
comma
id|MPI_POINTER
id|PTR_SGE_MPI_UNION
comma
DECL|typedef|MPI_SGE_UNION_t
DECL|typedef|pMPI_SGE_UNION_t
id|MPI_SGE_UNION_t
comma
id|MPI_POINTER
id|pMPI_SGE_UNION_t
comma
DECL|typedef|SGEAllUnion_t
DECL|typedef|pSGEAllUnion_t
id|SGEAllUnion_t
comma
id|MPI_POINTER
id|pSGEAllUnion_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/*  SGE field definition and masks                                          */
multiline_comment|/****************************************************************************/
multiline_comment|/* Flags field bit definitions */
DECL|macro|MPI_SGE_FLAGS_LAST_ELEMENT
mdefine_line|#define MPI_SGE_FLAGS_LAST_ELEMENT              (0x80)
DECL|macro|MPI_SGE_FLAGS_END_OF_BUFFER
mdefine_line|#define MPI_SGE_FLAGS_END_OF_BUFFER             (0x40)
DECL|macro|MPI_SGE_FLAGS_ELEMENT_TYPE_MASK
mdefine_line|#define MPI_SGE_FLAGS_ELEMENT_TYPE_MASK         (0x30)
DECL|macro|MPI_SGE_FLAGS_LOCAL_ADDRESS
mdefine_line|#define MPI_SGE_FLAGS_LOCAL_ADDRESS             (0x08)
DECL|macro|MPI_SGE_FLAGS_DIRECTION
mdefine_line|#define MPI_SGE_FLAGS_DIRECTION                 (0x04)
DECL|macro|MPI_SGE_FLAGS_ADDRESS_SIZE
mdefine_line|#define MPI_SGE_FLAGS_ADDRESS_SIZE              (0x02)
DECL|macro|MPI_SGE_FLAGS_END_OF_LIST
mdefine_line|#define MPI_SGE_FLAGS_END_OF_LIST               (0x01)
DECL|macro|MPI_SGE_FLAGS_SHIFT
mdefine_line|#define MPI_SGE_FLAGS_SHIFT                     (24)
DECL|macro|MPI_SGE_LENGTH_MASK
mdefine_line|#define MPI_SGE_LENGTH_MASK                     (0x00FFFFFF)
DECL|macro|MPI_SGE_CHAIN_LENGTH_MASK
mdefine_line|#define MPI_SGE_CHAIN_LENGTH_MASK               (0x0000FFFF)
multiline_comment|/* Element Type */
DECL|macro|MPI_SGE_FLAGS_TRANSACTION_ELEMENT
mdefine_line|#define MPI_SGE_FLAGS_TRANSACTION_ELEMENT       (0x00)
DECL|macro|MPI_SGE_FLAGS_SIMPLE_ELEMENT
mdefine_line|#define MPI_SGE_FLAGS_SIMPLE_ELEMENT            (0x10)
DECL|macro|MPI_SGE_FLAGS_CHAIN_ELEMENT
mdefine_line|#define MPI_SGE_FLAGS_CHAIN_ELEMENT             (0x30)
DECL|macro|MPI_SGE_FLAGS_ELEMENT_MASK
mdefine_line|#define MPI_SGE_FLAGS_ELEMENT_MASK              (0x30)
multiline_comment|/* Address location */
DECL|macro|MPI_SGE_FLAGS_SYSTEM_ADDRESS
mdefine_line|#define MPI_SGE_FLAGS_SYSTEM_ADDRESS            (0x00)
multiline_comment|/* Direction */
DECL|macro|MPI_SGE_FLAGS_IOC_TO_HOST
mdefine_line|#define MPI_SGE_FLAGS_IOC_TO_HOST               (0x00)
DECL|macro|MPI_SGE_FLAGS_HOST_TO_IOC
mdefine_line|#define MPI_SGE_FLAGS_HOST_TO_IOC               (0x04)
multiline_comment|/* Address Size */
DECL|macro|MPI_SGE_FLAGS_32_BIT_ADDRESSING
mdefine_line|#define MPI_SGE_FLAGS_32_BIT_ADDRESSING         (0x00)
DECL|macro|MPI_SGE_FLAGS_64_BIT_ADDRESSING
mdefine_line|#define MPI_SGE_FLAGS_64_BIT_ADDRESSING         (0x02)
multiline_comment|/* Context Size */
DECL|macro|MPI_SGE_FLAGS_32_BIT_CONTEXT
mdefine_line|#define MPI_SGE_FLAGS_32_BIT_CONTEXT            (0x00)
DECL|macro|MPI_SGE_FLAGS_64_BIT_CONTEXT
mdefine_line|#define MPI_SGE_FLAGS_64_BIT_CONTEXT            (0x02)
DECL|macro|MPI_SGE_FLAGS_96_BIT_CONTEXT
mdefine_line|#define MPI_SGE_FLAGS_96_BIT_CONTEXT            (0x04)
DECL|macro|MPI_SGE_FLAGS_128_BIT_CONTEXT
mdefine_line|#define MPI_SGE_FLAGS_128_BIT_CONTEXT           (0x06)
DECL|macro|MPI_SGE_CHAIN_OFFSET_MASK
mdefine_line|#define MPI_SGE_CHAIN_OFFSET_MASK               (0x00FF0000)
DECL|macro|MPI_SGE_CHAIN_OFFSET_SHIFT
mdefine_line|#define MPI_SGE_CHAIN_OFFSET_SHIFT              (16)
multiline_comment|/****************************************************************************/
multiline_comment|/*  SGE operation Macros                                                    */
multiline_comment|/****************************************************************************/
multiline_comment|/* SIMPLE FlagsLength manipulations... */
DECL|macro|MPI_SGE_SET_FLAGS
mdefine_line|#define  MPI_SGE_SET_FLAGS(f)           ((U32)(f) &lt;&lt; MPI_SGE_FLAGS_SHIFT)
DECL|macro|MPI_SGE_GET_FLAGS
mdefine_line|#define  MPI_SGE_GET_FLAGS(fl)          (((fl) &amp; ~MPI_SGE_LENGTH_MASK) &gt;&gt; MPI_SGE_FLAGS_SHIFT)
DECL|macro|MPI_SGE_LENGTH
mdefine_line|#define  MPI_SGE_LENGTH(fl)             ((fl) &amp; MPI_SGE_LENGTH_MASK)
DECL|macro|MPI_SGE_CHAIN_LENGTH
mdefine_line|#define  MPI_SGE_CHAIN_LENGTH(fl)       ((fl) &amp; MPI_SGE_CHAIN_LENGTH_MASK)
DECL|macro|MPI_SGE_SET_FLAGS_LENGTH
mdefine_line|#define  MPI_SGE_SET_FLAGS_LENGTH(f,l)  (MPI_SGE_SET_FLAGS(f) | MPI_SGE_LENGTH(l))
DECL|macro|MPI_pSGE_GET_FLAGS
mdefine_line|#define  MPI_pSGE_GET_FLAGS(psg)        MPI_SGE_GET_FLAGS((psg)-&gt;FlagsLength)
DECL|macro|MPI_pSGE_GET_LENGTH
mdefine_line|#define  MPI_pSGE_GET_LENGTH(psg)       MPI_SGE_LENGTH((psg)-&gt;FlagsLength)
DECL|macro|MPI_pSGE_SET_FLAGS_LENGTH
mdefine_line|#define  MPI_pSGE_SET_FLAGS_LENGTH(psg,f,l)  (psg)-&gt;FlagsLength = MPI_SGE_SET_FLAGS_LENGTH(f,l)
multiline_comment|/* CAUTION - The following are READ-MODIFY-WRITE! */
DECL|macro|MPI_pSGE_SET_FLAGS
mdefine_line|#define  MPI_pSGE_SET_FLAGS(psg,f)      (psg)-&gt;FlagsLength |= MPI_SGE_SET_FLAGS(f)
DECL|macro|MPI_pSGE_SET_LENGTH
mdefine_line|#define  MPI_pSGE_SET_LENGTH(psg,l)     (psg)-&gt;FlagsLength |= MPI_SGE_LENGTH(l)
DECL|macro|MPI_GET_CHAIN_OFFSET
mdefine_line|#define  MPI_GET_CHAIN_OFFSET(x) ((x&amp;MPI_SGE_CHAIN_OFFSET_MASK)&gt;&gt;MPI_SGE_CHAIN_OFFSET_SHIFT)
multiline_comment|/*****************************************************************************&n;*&n;*        S t a n d a r d    M e s s a g e    S t r u c t u r e s&n;*&n;*****************************************************************************/
multiline_comment|/****************************************************************************/
multiline_comment|/* Standard message request header for all request messages                 */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_REQUEST_HEADER
r_typedef
r_struct
id|_MSG_REQUEST_HEADER
(brace
DECL|member|Reserved
id|U8
id|Reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* function specific */
DECL|member|ChainOffset
id|U8
id|ChainOffset
suffix:semicolon
DECL|member|Function
id|U8
id|Function
suffix:semicolon
DECL|member|Reserved1
id|U8
id|Reserved1
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* function specific */
DECL|member|MsgFlags
id|U8
id|MsgFlags
suffix:semicolon
DECL|member|MsgContext
id|U32
id|MsgContext
suffix:semicolon
DECL|typedef|MSG_REQUEST_HEADER
DECL|typedef|PTR_MSG_REQUEST_HEADER
)brace
id|MSG_REQUEST_HEADER
comma
id|MPI_POINTER
id|PTR_MSG_REQUEST_HEADER
comma
DECL|typedef|MPIHeader_t
DECL|typedef|pMPIHeader_t
id|MPIHeader_t
comma
id|MPI_POINTER
id|pMPIHeader_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/*  Default Reply                                                           */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_DEFAULT_REPLY
r_typedef
r_struct
id|_MSG_DEFAULT_REPLY
(brace
DECL|member|Reserved
id|U8
id|Reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* function specific */
DECL|member|MsgLength
id|U8
id|MsgLength
suffix:semicolon
DECL|member|Function
id|U8
id|Function
suffix:semicolon
DECL|member|Reserved1
id|U8
id|Reserved1
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* function specific */
DECL|member|MsgFlags
id|U8
id|MsgFlags
suffix:semicolon
DECL|member|MsgContext
id|U32
id|MsgContext
suffix:semicolon
DECL|member|Reserved2
id|U8
id|Reserved2
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* function specific */
DECL|member|IOCStatus
id|U16
id|IOCStatus
suffix:semicolon
DECL|member|IOCLogInfo
id|U32
id|IOCLogInfo
suffix:semicolon
DECL|typedef|MSG_DEFAULT_REPLY
DECL|typedef|PTR_MSG_DEFAULT_REPLY
)brace
id|MSG_DEFAULT_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_DEFAULT_REPLY
comma
DECL|typedef|MPIDefaultReply_t
DECL|typedef|pMPIDefaultReply_t
id|MPIDefaultReply_t
comma
id|MPI_POINTER
id|pMPIDefaultReply_t
suffix:semicolon
multiline_comment|/* MsgFlags definition for all replies */
DECL|macro|MPI_MSGFLAGS_CONTINUATION_REPLY
mdefine_line|#define MPI_MSGFLAGS_CONTINUATION_REPLY         (0x80)
multiline_comment|/*****************************************************************************&n;*&n;*               I O C    S t a t u s   V a l u e s&n;*&n;*****************************************************************************/
multiline_comment|/****************************************************************************/
multiline_comment|/*  Common IOCStatus values for all replies                                 */
multiline_comment|/****************************************************************************/
DECL|macro|MPI_IOCSTATUS_SUCCESS
mdefine_line|#define MPI_IOCSTATUS_SUCCESS                  (0x0000)
DECL|macro|MPI_IOCSTATUS_INVALID_FUNCTION
mdefine_line|#define MPI_IOCSTATUS_INVALID_FUNCTION         (0x0001)
DECL|macro|MPI_IOCSTATUS_BUSY
mdefine_line|#define MPI_IOCSTATUS_BUSY                     (0x0002)
DECL|macro|MPI_IOCSTATUS_INVALID_SGL
mdefine_line|#define MPI_IOCSTATUS_INVALID_SGL              (0x0003)
DECL|macro|MPI_IOCSTATUS_INTERNAL_ERROR
mdefine_line|#define MPI_IOCSTATUS_INTERNAL_ERROR           (0x0004)
DECL|macro|MPI_IOCSTATUS_RESERVED
mdefine_line|#define MPI_IOCSTATUS_RESERVED                 (0x0005)
DECL|macro|MPI_IOCSTATUS_INSUFFICIENT_RESOURCES
mdefine_line|#define MPI_IOCSTATUS_INSUFFICIENT_RESOURCES   (0x0006)
DECL|macro|MPI_IOCSTATUS_INVALID_FIELD
mdefine_line|#define MPI_IOCSTATUS_INVALID_FIELD            (0x0007)
DECL|macro|MPI_IOCSTATUS_INVALID_STATE
mdefine_line|#define MPI_IOCSTATUS_INVALID_STATE            (0x0008)
multiline_comment|/****************************************************************************/
multiline_comment|/*  Config IOCStatus values                                                 */
multiline_comment|/****************************************************************************/
DECL|macro|MPI_IOCSTATUS_CONFIG_INVALID_ACTION
mdefine_line|#define MPI_IOCSTATUS_CONFIG_INVALID_ACTION    (0x0020)
DECL|macro|MPI_IOCSTATUS_CONFIG_INVALID_TYPE
mdefine_line|#define MPI_IOCSTATUS_CONFIG_INVALID_TYPE      (0x0021)
DECL|macro|MPI_IOCSTATUS_CONFIG_INVALID_PAGE
mdefine_line|#define MPI_IOCSTATUS_CONFIG_INVALID_PAGE      (0x0022)
DECL|macro|MPI_IOCSTATUS_CONFIG_INVALID_DATA
mdefine_line|#define MPI_IOCSTATUS_CONFIG_INVALID_DATA      (0x0023)
DECL|macro|MPI_IOCSTATUS_CONFIG_NO_DEFAULTS
mdefine_line|#define MPI_IOCSTATUS_CONFIG_NO_DEFAULTS       (0x0024)
DECL|macro|MPI_IOCSTATUS_CONFIG_CANT_COMMIT
mdefine_line|#define MPI_IOCSTATUS_CONFIG_CANT_COMMIT       (0x0025)
multiline_comment|/****************************************************************************/
multiline_comment|/*  SCSIIO Reply (SPI &amp; FCP) initiator values                               */
multiline_comment|/****************************************************************************/
DECL|macro|MPI_IOCSTATUS_SCSI_RECOVERED_ERROR
mdefine_line|#define MPI_IOCSTATUS_SCSI_RECOVERED_ERROR     (0x0040)
DECL|macro|MPI_IOCSTATUS_SCSI_INVALID_BUS
mdefine_line|#define MPI_IOCSTATUS_SCSI_INVALID_BUS         (0x0041)
DECL|macro|MPI_IOCSTATUS_SCSI_INVALID_TARGETID
mdefine_line|#define MPI_IOCSTATUS_SCSI_INVALID_TARGETID    (0x0042)
DECL|macro|MPI_IOCSTATUS_SCSI_DEVICE_NOT_THERE
mdefine_line|#define MPI_IOCSTATUS_SCSI_DEVICE_NOT_THERE    (0x0043)
DECL|macro|MPI_IOCSTATUS_SCSI_DATA_OVERRUN
mdefine_line|#define MPI_IOCSTATUS_SCSI_DATA_OVERRUN        (0x0044)
DECL|macro|MPI_IOCSTATUS_SCSI_DATA_UNDERRUN
mdefine_line|#define MPI_IOCSTATUS_SCSI_DATA_UNDERRUN       (0x0045)
DECL|macro|MPI_IOCSTATUS_SCSI_IO_DATA_ERROR
mdefine_line|#define MPI_IOCSTATUS_SCSI_IO_DATA_ERROR       (0x0046)
DECL|macro|MPI_IOCSTATUS_SCSI_PROTOCOL_ERROR
mdefine_line|#define MPI_IOCSTATUS_SCSI_PROTOCOL_ERROR      (0x0047)
DECL|macro|MPI_IOCSTATUS_SCSI_TASK_TERMINATED
mdefine_line|#define MPI_IOCSTATUS_SCSI_TASK_TERMINATED     (0x0048)
DECL|macro|MPI_IOCSTATUS_SCSI_RESIDUAL_MISMATCH
mdefine_line|#define MPI_IOCSTATUS_SCSI_RESIDUAL_MISMATCH   (0x0049)
DECL|macro|MPI_IOCSTATUS_SCSI_TASK_MGMT_FAILED
mdefine_line|#define MPI_IOCSTATUS_SCSI_TASK_MGMT_FAILED    (0x004A)
DECL|macro|MPI_IOCSTATUS_SCSI_IOC_TERMINATED
mdefine_line|#define MPI_IOCSTATUS_SCSI_IOC_TERMINATED      (0x004B)
DECL|macro|MPI_IOCSTATUS_SCSI_EXT_TERMINATED
mdefine_line|#define MPI_IOCSTATUS_SCSI_EXT_TERMINATED      (0x004C)
multiline_comment|/****************************************************************************/
multiline_comment|/*  SCSI (SPI &amp; FCP) target values                                          */
multiline_comment|/****************************************************************************/
DECL|macro|MPI_IOCSTATUS_TARGET_PRIORITY_IO
mdefine_line|#define MPI_IOCSTATUS_TARGET_PRIORITY_IO         (0x0060)
DECL|macro|MPI_IOCSTATUS_TARGET_INVALID_PORT
mdefine_line|#define MPI_IOCSTATUS_TARGET_INVALID_PORT        (0x0061)
DECL|macro|MPI_IOCSTATUS_TARGET_INVALID_IOCINDEX
mdefine_line|#define MPI_IOCSTATUS_TARGET_INVALID_IOCINDEX    (0x0062)
DECL|macro|MPI_IOCSTATUS_TARGET_ABORTED
mdefine_line|#define MPI_IOCSTATUS_TARGET_ABORTED             (0x0063)
DECL|macro|MPI_IOCSTATUS_TARGET_NO_CONN_RETRYABLE
mdefine_line|#define MPI_IOCSTATUS_TARGET_NO_CONN_RETRYABLE   (0x0064)
DECL|macro|MPI_IOCSTATUS_TARGET_NO_CONNECTION
mdefine_line|#define MPI_IOCSTATUS_TARGET_NO_CONNECTION       (0x0065)
DECL|macro|MPI_IOCSTATUS_TARGET_XFER_COUNT_MISMATCH
mdefine_line|#define MPI_IOCSTATUS_TARGET_XFER_COUNT_MISMATCH (0x006A)
DECL|macro|MPI_IOCSTATUS_TARGET_STS_DATA_NOT_SENT
mdefine_line|#define MPI_IOCSTATUS_TARGET_STS_DATA_NOT_SENT   (0x006B)
multiline_comment|/****************************************************************************/
multiline_comment|/*  Additional FCP target values                                            */
multiline_comment|/****************************************************************************/
DECL|macro|MPI_IOCSTATUS_TARGET_FC_ABORTED
mdefine_line|#define MPI_IOCSTATUS_TARGET_FC_ABORTED         (0x0066)    /* obsolete */
DECL|macro|MPI_IOCSTATUS_TARGET_FC_RX_ID_INVALID
mdefine_line|#define MPI_IOCSTATUS_TARGET_FC_RX_ID_INVALID   (0x0067)    /* obsolete */
DECL|macro|MPI_IOCSTATUS_TARGET_FC_DID_INVALID
mdefine_line|#define MPI_IOCSTATUS_TARGET_FC_DID_INVALID     (0x0068)    /* obsolete */
DECL|macro|MPI_IOCSTATUS_TARGET_FC_NODE_LOGGED_OUT
mdefine_line|#define MPI_IOCSTATUS_TARGET_FC_NODE_LOGGED_OUT (0x0069)    /* obsolete */
multiline_comment|/****************************************************************************/
multiline_comment|/*  Fibre Channel Direct Access values                                      */
multiline_comment|/****************************************************************************/
DECL|macro|MPI_IOCSTATUS_FC_ABORTED
mdefine_line|#define MPI_IOCSTATUS_FC_ABORTED                (0x0066)
DECL|macro|MPI_IOCSTATUS_FC_RX_ID_INVALID
mdefine_line|#define MPI_IOCSTATUS_FC_RX_ID_INVALID          (0x0067)
DECL|macro|MPI_IOCSTATUS_FC_DID_INVALID
mdefine_line|#define MPI_IOCSTATUS_FC_DID_INVALID            (0x0068)
DECL|macro|MPI_IOCSTATUS_FC_NODE_LOGGED_OUT
mdefine_line|#define MPI_IOCSTATUS_FC_NODE_LOGGED_OUT        (0x0069)
multiline_comment|/****************************************************************************/
multiline_comment|/*  LAN values                                                              */
multiline_comment|/****************************************************************************/
DECL|macro|MPI_IOCSTATUS_LAN_DEVICE_NOT_FOUND
mdefine_line|#define MPI_IOCSTATUS_LAN_DEVICE_NOT_FOUND      (0x0080)
DECL|macro|MPI_IOCSTATUS_LAN_DEVICE_FAILURE
mdefine_line|#define MPI_IOCSTATUS_LAN_DEVICE_FAILURE        (0x0081)
DECL|macro|MPI_IOCSTATUS_LAN_TRANSMIT_ERROR
mdefine_line|#define MPI_IOCSTATUS_LAN_TRANSMIT_ERROR        (0x0082)
DECL|macro|MPI_IOCSTATUS_LAN_TRANSMIT_ABORTED
mdefine_line|#define MPI_IOCSTATUS_LAN_TRANSMIT_ABORTED      (0x0083)
DECL|macro|MPI_IOCSTATUS_LAN_RECEIVE_ERROR
mdefine_line|#define MPI_IOCSTATUS_LAN_RECEIVE_ERROR         (0x0084)
DECL|macro|MPI_IOCSTATUS_LAN_RECEIVE_ABORTED
mdefine_line|#define MPI_IOCSTATUS_LAN_RECEIVE_ABORTED       (0x0085)
DECL|macro|MPI_IOCSTATUS_LAN_PARTIAL_PACKET
mdefine_line|#define MPI_IOCSTATUS_LAN_PARTIAL_PACKET        (0x0086)
DECL|macro|MPI_IOCSTATUS_LAN_CANCELED
mdefine_line|#define MPI_IOCSTATUS_LAN_CANCELED              (0x0087)
multiline_comment|/****************************************************************************/
multiline_comment|/*  IOCStatus flag to indicate that log info is available                   */
multiline_comment|/****************************************************************************/
DECL|macro|MPI_IOCSTATUS_FLAG_LOG_INFO_AVAILABLE
mdefine_line|#define MPI_IOCSTATUS_FLAG_LOG_INFO_AVAILABLE   (0x8000)
DECL|macro|MPI_IOCSTATUS_MASK
mdefine_line|#define MPI_IOCSTATUS_MASK                      (0x7FFF)
multiline_comment|/****************************************************************************/
multiline_comment|/*  LogInfo Types                                                           */
multiline_comment|/****************************************************************************/
DECL|macro|MPI_IOCLOGINFO_TYPE_MASK
mdefine_line|#define MPI_IOCLOGINFO_TYPE_MASK                (0xF0000000)
DECL|macro|MPI_IOCLOGINFO_TYPE_NONE
mdefine_line|#define MPI_IOCLOGINFO_TYPE_NONE                (0x0)
DECL|macro|MPI_IOCLOGINFO_TYPE_SCSI
mdefine_line|#define MPI_IOCLOGINFO_TYPE_SCSI                (0x1)
DECL|macro|MPI_IOCLOGINFO_TYPE_FC
mdefine_line|#define MPI_IOCLOGINFO_TYPE_FC                  (0x2)
DECL|macro|MPI_IOCLOGINFO_LOG_DATA_MASK
mdefine_line|#define MPI_IOCLOGINFO_LOG_DATA_MASK            (0x0FFFFFFF)
macro_line|#endif
eof
