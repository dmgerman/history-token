multiline_comment|/*&n; *  linux/drivers/message/fusion/scsi3.h&n; *      SCSI-3 definitions and macros.&n; *      (Ultimately) SCSI-3 definitions; for now, inheriting&n; *      SCSI-2 definitions.&n; *&n; *  Copyright (c) 1996-2002 Steven J. Ralston&n; *  Written By: Steven J. Ralston (19960517)&n; *  (mailto:sjralston1@netscape.net)&n; *  (mailto:Pam.Delaney@lsil.com)&n; *&n; *  $Id: scsi3.h,v 1.9 2002/02/27 18:45:02 sralston Exp $&n; */
macro_line|#ifndef SCSI3_H_INCLUDED
DECL|macro|SCSI3_H_INCLUDED
mdefine_line|#define SCSI3_H_INCLUDED
multiline_comment|/***************************************************************************/
multiline_comment|/****************************************************************************&n; *&n; *  Includes&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#else
macro_line|#ifndef U_STUFF_DEFINED
DECL|macro|U_STUFF_DEFINED
mdefine_line|#define U_STUFF_DEFINED
DECL|typedef|u8
r_typedef
r_int
r_char
id|u8
suffix:semicolon
DECL|typedef|u16
r_typedef
r_int
r_int
id|u16
suffix:semicolon
DECL|typedef|u32
r_typedef
r_int
r_int
id|u32
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/****************************************************************************&n; *&n; *  Defines&n; */
multiline_comment|/*&n; *    SCSI Commands&n; */
DECL|macro|CMD_TestUnitReady
mdefine_line|#define CMD_TestUnitReady      0x00
DECL|macro|CMD_RezeroUnit
mdefine_line|#define CMD_RezeroUnit         0x01  /* direct-access devices */
DECL|macro|CMD_Rewind
mdefine_line|#define CMD_Rewind             0x01  /* sequential-access devices */
DECL|macro|CMD_RequestSense
mdefine_line|#define CMD_RequestSense       0x03
DECL|macro|CMD_FormatUnit
mdefine_line|#define CMD_FormatUnit         0x04
DECL|macro|CMD_ReassignBlock
mdefine_line|#define CMD_ReassignBlock      0x07
DECL|macro|CMD_Read6
mdefine_line|#define CMD_Read6              0x08
DECL|macro|CMD_Write6
mdefine_line|#define CMD_Write6             0x0A
DECL|macro|CMD_WriteFilemark
mdefine_line|#define CMD_WriteFilemark      0x10
DECL|macro|CMD_Space
mdefine_line|#define CMD_Space              0x11
DECL|macro|CMD_Inquiry
mdefine_line|#define CMD_Inquiry            0x12
DECL|macro|CMD_ModeSelect6
mdefine_line|#define CMD_ModeSelect6        0x15
DECL|macro|CMD_ModeSense6
mdefine_line|#define CMD_ModeSense6         0x1A
DECL|macro|CMD_Reserve6
mdefine_line|#define CMD_Reserve6           0x16
DECL|macro|CMD_Release6
mdefine_line|#define CMD_Release6           0x17
DECL|macro|CMD_Erase
mdefine_line|#define CMD_Erase              0x19
DECL|macro|CMD_StartStopUnit
mdefine_line|#define CMD_StartStopUnit      0x1b  /* direct-access devices */
DECL|macro|CMD_LoadUnload
mdefine_line|#define CMD_LoadUnload         0x1b  /* sequential-access devices */
DECL|macro|CMD_ReceiveDiagnostic
mdefine_line|#define CMD_ReceiveDiagnostic  0x1C
DECL|macro|CMD_SendDiagnostic
mdefine_line|#define CMD_SendDiagnostic     0x1D
DECL|macro|CMD_ReadCapacity
mdefine_line|#define CMD_ReadCapacity       0x25
DECL|macro|CMD_Read10
mdefine_line|#define CMD_Read10             0x28
DECL|macro|CMD_Write10
mdefine_line|#define CMD_Write10            0x2A
DECL|macro|CMD_WriteVerify
mdefine_line|#define CMD_WriteVerify        0x2E
DECL|macro|CMD_Verify
mdefine_line|#define CMD_Verify             0x2F
DECL|macro|CMD_SynchronizeCache
mdefine_line|#define CMD_SynchronizeCache   0x35
DECL|macro|CMD_ReadDefectData
mdefine_line|#define CMD_ReadDefectData     0x37
DECL|macro|CMD_WriteBuffer
mdefine_line|#define CMD_WriteBuffer        0x3B
DECL|macro|CMD_ReadBuffer
mdefine_line|#define CMD_ReadBuffer         0x3C
DECL|macro|CMD_ReadLong
mdefine_line|#define CMD_ReadLong           0x3E
DECL|macro|CMD_LogSelect
mdefine_line|#define CMD_LogSelect          0x4C
DECL|macro|CMD_LogSense
mdefine_line|#define CMD_LogSense           0x4D
DECL|macro|CMD_ModeSelect10
mdefine_line|#define CMD_ModeSelect10       0x55
DECL|macro|CMD_Reserve10
mdefine_line|#define CMD_Reserve10          0x56
DECL|macro|CMD_Release10
mdefine_line|#define CMD_Release10          0x57
DECL|macro|CMD_ModeSense10
mdefine_line|#define CMD_ModeSense10        0x5A
DECL|macro|CMD_PersistReserveIn
mdefine_line|#define CMD_PersistReserveIn   0x5E
DECL|macro|CMD_PersistReserveOut
mdefine_line|#define CMD_PersistReserveOut  0x5F
DECL|macro|CMD_ReportLuns
mdefine_line|#define CMD_ReportLuns         0xA0
multiline_comment|/*&n; *    Control byte field&n; */
DECL|macro|CONTROL_BYTE_NACA_BIT
mdefine_line|#define CONTROL_BYTE_NACA_BIT  0x04
DECL|macro|CONTROL_BYTE_Flag_BIT
mdefine_line|#define CONTROL_BYTE_Flag_BIT  0x02
DECL|macro|CONTROL_BYTE_Link_BIT
mdefine_line|#define CONTROL_BYTE_Link_BIT  0x01
multiline_comment|/*&n; *    SCSI Messages&n; */
DECL|macro|MSG_COMPLETE
mdefine_line|#define MSG_COMPLETE             0x00
DECL|macro|MSG_EXTENDED
mdefine_line|#define MSG_EXTENDED             0x01
DECL|macro|MSG_SAVE_POINTERS
mdefine_line|#define MSG_SAVE_POINTERS        0x02
DECL|macro|MSG_RESTORE_POINTERS
mdefine_line|#define MSG_RESTORE_POINTERS     0x03
DECL|macro|MSG_DISCONNECT
mdefine_line|#define MSG_DISCONNECT           0x04
DECL|macro|MSG_IDERROR
mdefine_line|#define MSG_IDERROR              0x05
DECL|macro|MSG_ABORT
mdefine_line|#define MSG_ABORT                0x06
DECL|macro|MSG_REJECT
mdefine_line|#define MSG_REJECT               0x07
DECL|macro|MSG_NOP
mdefine_line|#define MSG_NOP                  0x08
DECL|macro|MSG_PARITY_ERROR
mdefine_line|#define MSG_PARITY_ERROR         0x09
DECL|macro|MSG_LINKED_CMD_COMPLETE
mdefine_line|#define MSG_LINKED_CMD_COMPLETE  0x0a
DECL|macro|MSG_LCMD_COMPLETE_W_FLG
mdefine_line|#define MSG_LCMD_COMPLETE_W_FLG  0x0b
DECL|macro|MSG_BUS_DEVICE_RESET
mdefine_line|#define MSG_BUS_DEVICE_RESET     0x0c
DECL|macro|MSG_ABORT_TAG
mdefine_line|#define MSG_ABORT_TAG            0x0d
DECL|macro|MSG_CLEAR_QUEUE
mdefine_line|#define MSG_CLEAR_QUEUE          0x0e
DECL|macro|MSG_INITIATE_RECOVERY
mdefine_line|#define MSG_INITIATE_RECOVERY    0x0f
DECL|macro|MSG_RELEASE_RECOVRY
mdefine_line|#define MSG_RELEASE_RECOVRY      0x10
DECL|macro|MSG_TERMINATE_IO
mdefine_line|#define MSG_TERMINATE_IO         0x11
DECL|macro|MSG_SIMPLE_QUEUE
mdefine_line|#define MSG_SIMPLE_QUEUE         0x20
DECL|macro|MSG_HEAD_OF_QUEUE
mdefine_line|#define MSG_HEAD_OF_QUEUE        0x21
DECL|macro|MSG_ORDERED_QUEUE
mdefine_line|#define MSG_ORDERED_QUEUE        0x22
DECL|macro|MSG_IGNORE_WIDE_RESIDUE
mdefine_line|#define MSG_IGNORE_WIDE_RESIDUE  0x23
DECL|macro|MSG_IDENTIFY
mdefine_line|#define MSG_IDENTIFY             0x80
DECL|macro|MSG_IDENTIFY_W_DISC
mdefine_line|#define MSG_IDENTIFY_W_DISC      0xc0
multiline_comment|/*&n; *    SCSI Phases&n; */
DECL|macro|PHS_DATA_OUT
mdefine_line|#define PHS_DATA_OUT  0x00
DECL|macro|PHS_DATA_IN
mdefine_line|#define PHS_DATA_IN   0x01
DECL|macro|PHS_COMMAND
mdefine_line|#define PHS_COMMAND   0x02
DECL|macro|PHS_STATUS
mdefine_line|#define PHS_STATUS    0x03
DECL|macro|PHS_MSG_OUT
mdefine_line|#define PHS_MSG_OUT   0x06
DECL|macro|PHS_MSG_IN
mdefine_line|#define PHS_MSG_IN    0x07
multiline_comment|/*&n; *    Statuses&n; */
DECL|macro|STS_GOOD
mdefine_line|#define STS_GOOD                        0x00
DECL|macro|STS_CHECK_CONDITION
mdefine_line|#define STS_CHECK_CONDITION             0x02
DECL|macro|STS_CONDITION_MET
mdefine_line|#define STS_CONDITION_MET               0x04
DECL|macro|STS_BUSY
mdefine_line|#define STS_BUSY                        0x08
DECL|macro|STS_INTERMEDIATE
mdefine_line|#define STS_INTERMEDIATE                0x10
DECL|macro|STS_INTERMEDIATE_CONDITION_MET
mdefine_line|#define STS_INTERMEDIATE_CONDITION_MET  0x14
DECL|macro|STS_RESERVATION_CONFLICT
mdefine_line|#define STS_RESERVATION_CONFLICT        0x18
DECL|macro|STS_COMMAND_TERMINATED
mdefine_line|#define STS_COMMAND_TERMINATED          0x22
DECL|macro|STS_TASK_SET_FULL
mdefine_line|#define STS_TASK_SET_FULL               0x28
DECL|macro|STS_QUEUE_FULL
mdefine_line|#define    STS_QUEUE_FULL               0x28
DECL|macro|STS_ACA_ACTIVE
mdefine_line|#define STS_ACA_ACTIVE                  0x30
DECL|macro|STS_VALID_MASK
mdefine_line|#define STS_VALID_MASK                  0x3e
DECL|macro|SCSI_STATUS
mdefine_line|#define SCSI_STATUS(x)  ((x) &amp; STS_VALID_MASK)
multiline_comment|/*&n; *    SCSI QTag Types&n; */
DECL|macro|QTAG_SIMPLE
mdefine_line|#define QTAG_SIMPLE     0x20
DECL|macro|QTAG_HEAD_OF_Q
mdefine_line|#define QTAG_HEAD_OF_Q  0x21
DECL|macro|QTAG_ORDERED
mdefine_line|#define QTAG_ORDERED    0x22
multiline_comment|/*&n; *    SCSI Sense Key Definitons&n; */
DECL|macro|SK_NO_SENSE
mdefine_line|#define SK_NO_SENSE         0x00
DECL|macro|SK_RECOVERED_ERROR
mdefine_line|#define SK_RECOVERED_ERROR  0x01
DECL|macro|SK_NOT_READY
mdefine_line|#define SK_NOT_READY        0x02
DECL|macro|SK_MEDIUM_ERROR
mdefine_line|#define SK_MEDIUM_ERROR     0x03
DECL|macro|SK_HARDWARE_ERROR
mdefine_line|#define SK_HARDWARE_ERROR   0x04
DECL|macro|SK_ILLEGAL_REQUEST
mdefine_line|#define SK_ILLEGAL_REQUEST  0x05
DECL|macro|SK_UNIT_ATTENTION
mdefine_line|#define SK_UNIT_ATTENTION   0x06
DECL|macro|SK_DATA_PROTECT
mdefine_line|#define SK_DATA_PROTECT     0x07
DECL|macro|SK_BLANK_CHECK
mdefine_line|#define SK_BLANK_CHECK      0x08
DECL|macro|SK_VENDOR_SPECIFIC
mdefine_line|#define SK_VENDOR_SPECIFIC  0x09
DECL|macro|SK_COPY_ABORTED
mdefine_line|#define SK_COPY_ABORTED     0x0a
DECL|macro|SK_ABORTED_COMMAND
mdefine_line|#define SK_ABORTED_COMMAND  0x0b
DECL|macro|SK_EQUAL
mdefine_line|#define SK_EQUAL            0x0c
DECL|macro|SK_VOLUME_OVERFLOW
mdefine_line|#define SK_VOLUME_OVERFLOW  0x0d
DECL|macro|SK_MISCOMPARE
mdefine_line|#define SK_MISCOMPARE       0x0e
DECL|macro|SK_RESERVED
mdefine_line|#define SK_RESERVED         0x0f
DECL|macro|SCSI_MAX_INQUIRY_BYTES
mdefine_line|#define SCSI_MAX_INQUIRY_BYTES  96
DECL|macro|SCSI_STD_INQUIRY_BYTES
mdefine_line|#define SCSI_STD_INQUIRY_BYTES  36
DECL|macro|USE_SCSI_COMPLETE_INQDATA
macro_line|#undef USE_SCSI_COMPLETE_INQDATA
multiline_comment|/*&n; *      Structure definition for SCSI Inquiry Data&n; *&n; *  NOTE: The following structure is 96 bytes in size&n; *      iff USE_SCSI_COMPLETE_INQDATA IS defined above (i.e. w/ &quot;#define&quot;).&n; *      If USE_SCSI_COMPLETE_INQDATA is NOT defined above (i.e. w/ &quot;#undef&quot;)&n; *      then the following structure is only 36 bytes in size.&n; *  THE CHOICE IS YOURS!&n; */
DECL|struct|SCSI_Inquiry_Data
r_typedef
r_struct
id|SCSI_Inquiry_Data
(brace
macro_line|#ifdef USE_SCSI_COMPLETE_INQDATA
DECL|member|InqByte
id|u8
id|InqByte
(braket
id|SCSI_MAX_INQUIRY_BYTES
)braket
suffix:semicolon
macro_line|#else
id|u8
id|InqByte
(braket
id|SCSI_STD_INQUIRY_BYTES
)braket
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * the following structure works only for little-endian (Intel,&n; * LSB first (1234) byte order) systems with 4-byte ints.&n; *&n;        u32    Periph_Device_Type    : 5,&n;               Periph_Qualifier      : 3,&n;               Device_Type_Modifier  : 7,&n;               Removable_Media       : 1,&n;               ANSI_Version          : 3,&n;               ECMA_Version          : 3,&n;               ISO_Version           : 2,&n;               Response_Data_Format  : 4,&n;               reserved_0            : 3,&n;               AERC                  : 1  ;&n;        u32    Additional_Length     : 8,&n;               reserved_1            :16,&n;               SftReset              : 1,&n;               CmdQue                : 1,&n;               reserved_2            : 1,&n;               Linked                : 1,&n;               Sync                  : 1,&n;               WBus16                : 1,&n;               WBus32                : 1,&n;               RelAdr                : 1  ;&n;        u8     Vendor_ID[8];&n;        u8     Product_ID[16];&n;        u8     Revision_Level [4];&n;#ifdef USE_SCSI_COMPLETE_INQDATA&n;        u8     Vendor_Specific[20];&n;        u8     reserved_3[40];&n;#endif&n; *&n; */
DECL|typedef|SCSI_Inquiry_Data_t
)brace
id|SCSI_Inquiry_Data_t
suffix:semicolon
DECL|macro|INQ_PERIPHINFO_BYTE
mdefine_line|#define INQ_PERIPHINFO_BYTE            0
DECL|macro|INQ_Periph_Qualifier_MASK
mdefine_line|#define   INQ_Periph_Qualifier_MASK      0xe0
DECL|macro|INQ_Periph_Device_Type_MASK
mdefine_line|#define   INQ_Periph_Device_Type_MASK    0x1f
DECL|macro|INQ_Peripheral_Qualifier
mdefine_line|#define INQ_Peripheral_Qualifier(inqp) &bslash;&n;    (int)((*((u8*)(inqp)+INQ_PERIPHINFO_BYTE) &amp; INQ_Periph_Qualifier_MASK) &gt;&gt; 5)
DECL|macro|INQ_Peripheral_Device_Type
mdefine_line|#define INQ_Peripheral_Device_Type(inqp) &bslash;&n;    (int)(*((u8*)(inqp)+INQ_PERIPHINFO_BYTE) &amp; INQ_Periph_Device_Type_MASK)
DECL|macro|INQ_DEVTYPEMOD_BYTE
mdefine_line|#define INQ_DEVTYPEMOD_BYTE            1
DECL|macro|INQ_RMB_BIT
mdefine_line|#define   INQ_RMB_BIT                    0x80
DECL|macro|INQ_Device_Type_Modifier_MASK
mdefine_line|#define   INQ_Device_Type_Modifier_MASK  0x7f
DECL|macro|INQ_Removable_Medium
mdefine_line|#define INQ_Removable_Medium(inqp) &bslash;&n;    (int)(*((u8*)(inqp)+INQ_DEVTYPEMOD_BYTE) &amp; INQ_RMB_BIT)
DECL|macro|INQ_Device_Type_Modifier
mdefine_line|#define INQ_Device_Type_Modifier(inqp) &bslash;&n;    (int)(*((u8*)(inqp)+INQ_DEVTYPEMOD_BYTE) &amp; INQ_Device_Type_Modifier_MASK)
DECL|macro|INQ_VERSIONINFO_BYTE
mdefine_line|#define INQ_VERSIONINFO_BYTE           2
DECL|macro|INQ_ISO_Version_MASK
mdefine_line|#define   INQ_ISO_Version_MASK           0xc0
DECL|macro|INQ_ECMA_Version_MASK
mdefine_line|#define   INQ_ECMA_Version_MASK          0x38
DECL|macro|INQ_ANSI_Version_MASK
mdefine_line|#define   INQ_ANSI_Version_MASK          0x07
DECL|macro|INQ_ISO_Version
mdefine_line|#define INQ_ISO_Version(inqp) &bslash;&n;    (int)(*((u8*)(inqp)+INQ_VERSIONINFO_BYTE) &amp; INQ_ISO_Version_MASK)
DECL|macro|INQ_ECMA_Version
mdefine_line|#define INQ_ECMA_Version(inqp) &bslash;&n;    (int)(*((u8*)(inqp)+INQ_VERSIONINFO_BYTE) &amp; INQ_ECMA_Version_MASK)
DECL|macro|INQ_ANSI_Version
mdefine_line|#define INQ_ANSI_Version(inqp) &bslash;&n;    (int)(*((u8*)(inqp)+INQ_VERSIONINFO_BYTE) &amp; INQ_ANSI_Version_MASK)
DECL|macro|INQ_BYTE3
mdefine_line|#define INQ_BYTE3                      3
DECL|macro|INQ_AERC_BIT
mdefine_line|#define   INQ_AERC_BIT                   0x80
DECL|macro|INQ_TrmTsk_BIT
mdefine_line|#define   INQ_TrmTsk_BIT                 0x40
DECL|macro|INQ_NormACA_BIT
mdefine_line|#define   INQ_NormACA_BIT                0x20
DECL|macro|INQ_RDF_MASK
mdefine_line|#define   INQ_RDF_MASK                   0x0F
DECL|macro|INQ_AER_Capable
mdefine_line|#define INQ_AER_Capable(inqp) &bslash;&n;    (int)(*((u8*)(inqp)+INQ_BYTE3) &amp; INQ_AERC_BIT)
DECL|macro|INQ_TrmTsk
mdefine_line|#define INQ_TrmTsk(inqp) &bslash;&n;    (int)(*((u8*)(inqp)+INQ_BYTE3) &amp; INQ_TrmTsk_BIT)
DECL|macro|INQ_NormACA
mdefine_line|#define INQ_NormACA(inqp) &bslash;&n;    (int)(*((u8*)(inqp)+INQ_BYTE3) &amp; INQ_NormACA_BIT)
DECL|macro|INQ_Response_Data_Format
mdefine_line|#define INQ_Response_Data_Format(inqp) &bslash;&n;    (int)(*((u8*)(inqp)+INQ_BYTE3) &amp; INQ_RDF_MASK)
DECL|macro|INQ_CAPABILITY_BYTE
mdefine_line|#define INQ_CAPABILITY_BYTE            7
DECL|macro|INQ_RelAdr_BIT
mdefine_line|#define   INQ_RelAdr_BIT                 0x80
DECL|macro|INQ_WBus32_BIT
mdefine_line|#define   INQ_WBus32_BIT                 0x40
DECL|macro|INQ_WBus16_BIT
mdefine_line|#define   INQ_WBus16_BIT                 0x20
DECL|macro|INQ_Sync_BIT
mdefine_line|#define   INQ_Sync_BIT                   0x10
DECL|macro|INQ_Linked_BIT
mdefine_line|#define   INQ_Linked_BIT                 0x08
multiline_comment|/*      INQ_Reserved BIT               0x40 */
DECL|macro|INQ_CmdQue_BIT
mdefine_line|#define   INQ_CmdQue_BIT                 0x02
DECL|macro|INQ_SftRe_BIT
mdefine_line|#define   INQ_SftRe_BIT                  0x01
DECL|macro|IS_RelAdr_DEV
mdefine_line|#define IS_RelAdr_DEV(inqp) &bslash;&n;    (int)(*((u8*)(inqp)+INQ_CAPABILITY_BYTE) &amp; INQ_RelAdr_BIT)
DECL|macro|IS_WBus32_DEV
mdefine_line|#define IS_WBus32_DEV(inqp) &bslash;&n;    (int)(*((u8*)(inqp)+INQ_CAPABILITY_BYTE) &amp; INQ_WBus32_BIT)
DECL|macro|IS_WBus16_DEV
mdefine_line|#define IS_WBus16_DEV(inqp) &bslash;&n;    (int)(*((u8*)(inqp)+INQ_CAPABILITY_BYTE) &amp; INQ_WBus16_BIT)
DECL|macro|IS_Sync_DEV
mdefine_line|#define IS_Sync_DEV(inqp) &bslash;&n;    (int)(*((u8*)(inqp)+INQ_CAPABILITY_BYTE) &amp; INQ_Sync_BIT)
DECL|macro|IS_Linked_DEV
mdefine_line|#define IS_Linked_DEV(inqp) &bslash;&n;    (int)(*((u8*)(inqp)+INQ_CAPABILITY_BYTE) &amp; INQ_Linked_BIT)
DECL|macro|IS_CmdQue_DEV
mdefine_line|#define IS_CmdQue_DEV(inqp) &bslash;&n;    (int)(*((u8*)(inqp)+INQ_CAPABILITY_BYTE) &amp; INQ_CmdQue_BIT)
DECL|macro|IS_SftRe_DEV
mdefine_line|#define IS_SftRe_DEV(inqp) &bslash;&n;    (int)(*((u8*)(inqp)+INQ_CAPABILITY_BYTE) &amp; INQ_SftRe_BIT)
DECL|macro|INQ_Width_BITS
mdefine_line|#define INQ_Width_BITS &bslash;&n;    (INQ_WBus32_BIT | INQ_WBus16_BIT)
DECL|macro|IS_Wide_DEV
mdefine_line|#define IS_Wide_DEV(inqp) &bslash;&n;    (int)(*((u8*)(inqp)+INQ_CAPABILITY_BYTE) &amp; INQ_Width_BITS)
multiline_comment|/*&n; *      SCSI peripheral device types&n; */
DECL|macro|SCSI_TYPE_DAD
mdefine_line|#define SCSI_TYPE_DAD               0x00  /* Direct Access Device */
DECL|macro|SCSI_TYPE_SAD
mdefine_line|#define SCSI_TYPE_SAD               0x01  /* Sequential Access Device */
DECL|macro|SCSI_TYPE_TAPE
mdefine_line|#define SCSI_TYPE_TAPE  SCSI_TYPE_SAD
DECL|macro|SCSI_TYPE_PRT
mdefine_line|#define SCSI_TYPE_PRT               0x02  /* Printer */
DECL|macro|SCSI_TYPE_PROC
mdefine_line|#define SCSI_TYPE_PROC              0x03  /* Processor */
DECL|macro|SCSI_TYPE_WORM
mdefine_line|#define SCSI_TYPE_WORM              0x04
DECL|macro|SCSI_TYPE_CDROM
mdefine_line|#define SCSI_TYPE_CDROM             0x05
DECL|macro|SCSI_TYPE_SCAN
mdefine_line|#define SCSI_TYPE_SCAN              0x06  /* Scanner */
DECL|macro|SCSI_TYPE_OPTICAL
mdefine_line|#define SCSI_TYPE_OPTICAL           0x07  /* Magneto/Optical */
DECL|macro|SCSI_TYPE_CHANGER
mdefine_line|#define SCSI_TYPE_CHANGER           0x08
DECL|macro|SCSI_TYPE_COMM
mdefine_line|#define SCSI_TYPE_COMM              0x09  /* Communications device */
DECL|macro|SCSI_TYPE_UNKNOWN
mdefine_line|#define SCSI_TYPE_UNKNOWN           0x1f
DECL|macro|SCSI_TYPE_UNCONFIGURED_LUN
mdefine_line|#define SCSI_TYPE_UNCONFIGURED_LUN  0x7f
DECL|macro|SCSI_TYPE_MAX_KNOWN
mdefine_line|#define SCSI_TYPE_MAX_KNOWN         SCSI_TYPE_COMM
multiline_comment|/*&n; *      Peripheral Qualifiers&n; */
DECL|macro|DEVICE_PRESENT
mdefine_line|#define DEVICE_PRESENT     0x00
DECL|macro|LUN_NOT_PRESENT
mdefine_line|#define LUN_NOT_PRESENT    0x01
DECL|macro|LUN_NOT_SUPPORTED
mdefine_line|#define LUN_NOT_SUPPORTED  0x03
multiline_comment|/*&n; *      ANSI Versions&n; */
macro_line|#ifndef SCSI_1
DECL|macro|SCSI_1
mdefine_line|#define SCSI_1  0x01
macro_line|#endif
macro_line|#ifndef SCSI_2
DECL|macro|SCSI_2
mdefine_line|#define SCSI_2  0x02
macro_line|#endif
macro_line|#ifndef SCSI_3
DECL|macro|SCSI_3
mdefine_line|#define SCSI_3  0x03
macro_line|#endif
DECL|macro|SCSI_MAX_SENSE_BYTES
mdefine_line|#define SCSI_MAX_SENSE_BYTES  255
DECL|macro|SCSI_STD_SENSE_BYTES
mdefine_line|#define SCSI_STD_SENSE_BYTES   18
DECL|macro|SCSI_PAD_SENSE_BYTES
mdefine_line|#define SCSI_PAD_SENSE_BYTES      (SCSI_MAX_SENSE_BYTES - SCSI_STD_SENSE_BYTES)
DECL|macro|USE_SCSI_COMPLETE_SENSE
macro_line|#undef USE_SCSI_COMPLETE_SENSE
multiline_comment|/*&n; *      Structure definition for SCSI Sense Data&n; *&n; *  NOTE: The following structure is 255 bytes in size&n; *      iiff USE_SCSI_COMPLETE_SENSE IS defined above (i.e. w/ &quot;#define&quot;).&n; *      If USE_SCSI_COMPLETE_SENSE is NOT defined above (i.e. w/ &quot;#undef&quot;)&n; *      then the following structure is only 19 bytes in size.&n; *  THE CHOICE IS YOURS!&n; *&n; */
DECL|struct|SCSI_Sense_Data
r_typedef
r_struct
id|SCSI_Sense_Data
(brace
macro_line|#ifdef USE_SCSI_COMPLETE_SENSE
DECL|member|SenseByte
id|u8
id|SenseByte
(braket
id|SCSI_MAX_SENSE_BYTES
)braket
suffix:semicolon
macro_line|#else
id|u8
id|SenseByte
(braket
id|SCSI_STD_SENSE_BYTES
)braket
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * the following structure works only for little-endian (Intel,&n; * LSB first (1234) byte order) systems with 4-byte ints.&n; *&n;    u8     Error_Code                :4,            // 0x00&n;           Error_Class               :3,&n;           Valid                     :1&n;     ;&n;    u8     Segment_Number                           // 0x01&n;     ;&n;    u8     Sense_Key                 :4,            // 0x02&n;           Reserved                  :1,&n;           Incorrect_Length_Indicator:1,&n;           End_Of_Media              :1,&n;           Filemark                  :1&n;     ;&n;    u8     Information_MSB;                         // 0x03&n;    u8     Information_Byte2;                       // 0x04&n;    u8     Information_Byte1;                       // 0x05&n;    u8     Information_LSB;                         // 0x06&n;    u8     Additional_Length;                       // 0x07&n;&n;    u32    Command_Specific_Information;            // 0x08 - 0x0b&n;&n;    u8     Additional_Sense_Code;                   // 0x0c&n;    u8     Additional_Sense_Code_Qualifier;         // 0x0d&n;    u8     Field_Replaceable_Unit_Code;             // 0x0e&n;    u8     Illegal_Req_Bit_Pointer   :3,            // 0x0f&n;           Illegal_Req_Bit_Valid     :1,&n;           Illegal_Req_Reserved      :2,&n;           Illegal_Req_Cmd_Data      :1,&n;           Sense_Key_Specific_Valid  :1&n;     ;&n;    u16    Sense_Key_Specific_Data;                 // 0x10 - 0x11&n;&n;#ifdef USE_SCSI_COMPLETE_SENSE&n;    u8     Additional_Sense_Data[SCSI_PAD_SENSE_BYTES];&n;#else&n;    u8     Additional_Sense_Data[1];&n;#endif&n; *&n; */
DECL|typedef|SCSI_Sense_Data_t
)brace
id|SCSI_Sense_Data_t
suffix:semicolon
DECL|macro|SD_ERRCODE_BYTE
mdefine_line|#define SD_ERRCODE_BYTE                0
DECL|macro|SD_Valid_BIT
mdefine_line|#define   SD_Valid_BIT                   0x80
DECL|macro|SD_Error_Code_MASK
mdefine_line|#define   SD_Error_Code_MASK             0x7f
DECL|macro|SD_Valid
mdefine_line|#define SD_Valid(sdp) &bslash;&n;    (int)(*((u8*)(sdp)+SD_ERRCODE_BYTE) &amp; SD_Valid_BIT)
DECL|macro|SD_Error_Code
mdefine_line|#define SD_Error_Code(sdp) &bslash;&n;    (int)(*((u8*)(sdp)+SD_ERRCODE_BYTE) &amp; SD_Error_Code_MASK)
DECL|macro|SD_SEGNUM_BYTE
mdefine_line|#define SD_SEGNUM_BYTE                 1
DECL|macro|SD_Segment_Number
mdefine_line|#define SD_Segment_Number(sdp)  (int)(*((u8*)(sdp)+SD_SEGNUM_BYTE))
DECL|macro|SD_SENSEKEY_BYTE
mdefine_line|#define SD_SENSEKEY_BYTE               2
DECL|macro|SD_Filemark_BIT
mdefine_line|#define   SD_Filemark_BIT                0x80
DECL|macro|SD_EOM_BIT
mdefine_line|#define   SD_EOM_BIT                     0x40
DECL|macro|SD_ILI_BIT
mdefine_line|#define   SD_ILI_BIT                     0x20
DECL|macro|SD_Sense_Key_MASK
mdefine_line|#define   SD_Sense_Key_MASK              0x0f
DECL|macro|SD_Filemark
mdefine_line|#define SD_Filemark(sdp) &bslash;&n;    (int)(*((u8*)(sdp)+SD_SENSEKEY_BYTE) &amp; SD_Filemark_BIT)
DECL|macro|SD_EOM
mdefine_line|#define SD_EOM(sdp) &bslash;&n;    (int)(*((u8*)(sdp)+SD_SENSEKEY_BYTE) &amp; SD_EOM_BIT)
DECL|macro|SD_ILI
mdefine_line|#define SD_ILI(sdp) &bslash;&n;    (int)(*((u8*)(sdp)+SD_SENSEKEY_BYTE) &amp; SD_ILI_BIT)
DECL|macro|SD_Sense_Key
mdefine_line|#define SD_Sense_Key(sdp) &bslash;&n;    (int)(*((u8*)(sdp)+SD_SENSEKEY_BYTE) &amp; SD_Sense_Key_MASK)
DECL|macro|SD_INFO3_BYTE
mdefine_line|#define SD_INFO3_BYTE                  3
DECL|macro|SD_INFO2_BYTE
mdefine_line|#define SD_INFO2_BYTE                  4
DECL|macro|SD_INFO1_BYTE
mdefine_line|#define SD_INFO1_BYTE                  5
DECL|macro|SD_INFO0_BYTE
mdefine_line|#define SD_INFO0_BYTE                  6
DECL|macro|SD_Information3
mdefine_line|#define SD_Information3(sdp)  (int)(*((u8*)(sdp)+SD_INFO3_BYTE))
DECL|macro|SD_Information2
mdefine_line|#define SD_Information2(sdp)  (int)(*((u8*)(sdp)+SD_INFO2_BYTE))
DECL|macro|SD_Information1
mdefine_line|#define SD_Information1(sdp)  (int)(*((u8*)(sdp)+SD_INFO1_BYTE))
DECL|macro|SD_Information0
mdefine_line|#define SD_Information0(sdp)  (int)(*((u8*)(sdp)+SD_INFO0_BYTE))
DECL|macro|SD_ADDL_LEN_BYTE
mdefine_line|#define SD_ADDL_LEN_BYTE               7
DECL|macro|SD_Additional_Sense_Length
mdefine_line|#define SD_Additional_Sense_Length(sdp) &bslash;&n;    (int)(*((u8*)(sdp)+SD_ADDL_LEN_BYTE))
DECL|macro|SD_Addl_Sense_Len
mdefine_line|#define SD_Addl_Sense_Len  SD_Additional_Sense_Length
DECL|macro|SD_CMD_SPECIFIC3_BYTE
mdefine_line|#define SD_CMD_SPECIFIC3_BYTE          8
DECL|macro|SD_CMD_SPECIFIC2_BYTE
mdefine_line|#define SD_CMD_SPECIFIC2_BYTE          9
DECL|macro|SD_CMD_SPECIFIC1_BYTE
mdefine_line|#define SD_CMD_SPECIFIC1_BYTE         10
DECL|macro|SD_CMD_SPECIFIC0_BYTE
mdefine_line|#define SD_CMD_SPECIFIC0_BYTE         11
DECL|macro|SD_Cmd_Specific_Info3
mdefine_line|#define SD_Cmd_Specific_Info3(sdp)  (int)(*((u8*)(sdp)+SD_CMD_SPECIFIC3_BYTE))
DECL|macro|SD_Cmd_Specific_Info2
mdefine_line|#define SD_Cmd_Specific_Info2(sdp)  (int)(*((u8*)(sdp)+SD_CMD_SPECIFIC2_BYTE))
DECL|macro|SD_Cmd_Specific_Info1
mdefine_line|#define SD_Cmd_Specific_Info1(sdp)  (int)(*((u8*)(sdp)+SD_CMD_SPECIFIC1_BYTE))
DECL|macro|SD_Cmd_Specific_Info0
mdefine_line|#define SD_Cmd_Specific_Info0(sdp)  (int)(*((u8*)(sdp)+SD_CMD_SPECIFIC0_BYTE))
DECL|macro|SD_ADDL_SENSE_CODE_BYTE
mdefine_line|#define SD_ADDL_SENSE_CODE_BYTE       12
DECL|macro|SD_Additional_Sense_Code
mdefine_line|#define SD_Additional_Sense_Code(sdp) &bslash;&n;    (int)(*((u8*)(sdp)+SD_ADDL_SENSE_CODE_BYTE))
DECL|macro|SD_Addl_Sense_Code
mdefine_line|#define SD_Addl_Sense_Code  SD_Additional_Sense_Code
DECL|macro|SD_ASC
mdefine_line|#define SD_ASC  SD_Additional_Sense_Code
DECL|macro|SD_ADDL_SENSE_CODE_QUAL_BYTE
mdefine_line|#define SD_ADDL_SENSE_CODE_QUAL_BYTE  13
DECL|macro|SD_Additional_Sense_Code_Qualifier
mdefine_line|#define SD_Additional_Sense_Code_Qualifier(sdp) &bslash;&n;    (int)(*((u8*)(sdp)+SD_ADDL_SENSE_CODE_QUAL_BYTE))
DECL|macro|SD_Addl_Sense_Code_Qual
mdefine_line|#define SD_Addl_Sense_Code_Qual  SD_Additional_Sense_Code_Qualifier
DECL|macro|SD_ASCQ
mdefine_line|#define SD_ASCQ  SD_Additional_Sense_Code_Qualifier
DECL|macro|SD_FIELD_REPL_UNIT_CODE_BYTE
mdefine_line|#define SD_FIELD_REPL_UNIT_CODE_BYTE  14
DECL|macro|SD_Field_Replaceable_Unit_Code
mdefine_line|#define SD_Field_Replaceable_Unit_Code(sdp) &bslash;&n;    (int)(*((u8*)(sdp)+SD_FIELD_REPL_UNIT_CODE_BYTE))
DECL|macro|SD_Field_Repl_Unit_Code
mdefine_line|#define SD_Field_Repl_Unit_Code  SD_Field_Replaceable_Unit_Code
DECL|macro|SD_FRUC
mdefine_line|#define SD_FRUC  SD_Field_Replaceable_Unit_Code
DECL|macro|SD_FRU
mdefine_line|#define SD_FRU  SD_Field_Replaceable_Unit_Code
multiline_comment|/*&n; *  Sense-Key Specific offsets and macros.&n; */
DECL|macro|SD_SKS2_BYTE
mdefine_line|#define SD_SKS2_BYTE                  15
DECL|macro|SD_SKS_Valid_BIT
mdefine_line|#define   SD_SKS_Valid_BIT               0x80
DECL|macro|SD_SKS_Cmd_Data_BIT
mdefine_line|#define   SD_SKS_Cmd_Data_BIT            0x40
DECL|macro|SD_SKS_Bit_Ptr_Valid_BIT
mdefine_line|#define   SD_SKS_Bit_Ptr_Valid_BIT       0x08
DECL|macro|SD_SKS_Bit_Ptr_MASK
mdefine_line|#define   SD_SKS_Bit_Ptr_MASK            0x07
DECL|macro|SD_SKS1_BYTE
mdefine_line|#define SD_SKS1_BYTE                  16
DECL|macro|SD_SKS0_BYTE
mdefine_line|#define SD_SKS0_BYTE                  17
DECL|macro|SD_Sense_Key_Specific_Valid
mdefine_line|#define SD_Sense_Key_Specific_Valid(sdp) &bslash;&n;    (int)(*((u8*)(sdp)+SD_SKS2_BYTE) &amp; SD_SKS_Valid_BIT)
DECL|macro|SD_SKS_Valid
mdefine_line|#define SD_SKS_Valid  SD_Sense_Key_Specific_Valid
DECL|macro|SD_SKS_CDB_Error
mdefine_line|#define SD_SKS_CDB_Error(sdp)  &bslash;&n;    (int)(*((u8*)(sdp)+SD_SKS2_BYTE) &amp; SD_SKS_Cmd_Data_BIT)
DECL|macro|SD_Was_Illegal_Request
mdefine_line|#define SD_Was_Illegal_Request  SD_SKS_CDB_Error
DECL|macro|SD_SKS_Bit_Pointer_Valid
mdefine_line|#define SD_SKS_Bit_Pointer_Valid(sdp)  &bslash;&n;    (int)(*((u8*)(sdp)+SD_SKS2_BYTE) &amp; SD_SKS_Bit_Ptr_Valid_BIT)
DECL|macro|SD_SKS_Bit_Pointer
mdefine_line|#define SD_SKS_Bit_Pointer(sdp)  &bslash;&n;    (int)(*((u8*)(sdp)+SD_SKS2_BYTE) &amp; SD_SKS_Bit_Ptr_MASK)
DECL|macro|SD_Field_Pointer
mdefine_line|#define SD_Field_Pointer(sdp)  &bslash;&n;    (int)( ((u16)(*((u8*)(sdp)+SD_SKS1_BYTE)) &lt;&lt; 8) &bslash;&n;      + *((u8*)(sdp)+SD_SKS0_BYTE) )
DECL|macro|SD_Bad_Byte
mdefine_line|#define SD_Bad_Byte  SD_Field_Pointer
DECL|macro|SD_Actual_Retry_Count
mdefine_line|#define SD_Actual_Retry_Count  SD_Field_Pointer
DECL|macro|SD_Progress_Indication
mdefine_line|#define SD_Progress_Indication  SD_Field_Pointer
multiline_comment|/*&n; *  Mode Sense Write Protect Mask&n; */
DECL|macro|WRITE_PROTECT_MASK
mdefine_line|#define WRITE_PROTECT_MASK      0X80
multiline_comment|/*&n; *  Medium Type Codes&n; */
DECL|macro|OPTICAL_DEFAULT
mdefine_line|#define OPTICAL_DEFAULT                 0x00
DECL|macro|OPTICAL_READ_ONLY_MEDIUM
mdefine_line|#define OPTICAL_READ_ONLY_MEDIUM        0x01
DECL|macro|OPTICAL_WRITE_ONCE_MEDIUM
mdefine_line|#define OPTICAL_WRITE_ONCE_MEDIUM       0x02
DECL|macro|OPTICAL_READ_WRITABLE_MEDIUM
mdefine_line|#define OPTICAL_READ_WRITABLE_MEDIUM    0x03
DECL|macro|OPTICAL_RO_OR_WO_MEDIUM
mdefine_line|#define OPTICAL_RO_OR_WO_MEDIUM         0x04
DECL|macro|OPTICAL_RO_OR_RW_MEDIUM
mdefine_line|#define OPTICAL_RO_OR_RW_MEDIUM         0x05
DECL|macro|OPTICAL_WO_OR_RW_MEDIUM
mdefine_line|#define OPTICAL_WO_OR_RW_MEDIUM         0x06
multiline_comment|/*&n; *    Structure definition for READ6, WRITE6 (6-byte CDB)&n; */
DECL|struct|SCSI_RW6_CDB
r_typedef
r_struct
id|SCSI_RW6_CDB
(brace
DECL|member|OpCode
id|u32
id|OpCode
suffix:colon
l_int|8
comma
DECL|member|LBA_HI
id|LBA_HI
suffix:colon
l_int|5
comma
multiline_comment|/* 5 MSBit&squot;s of the LBA */
DECL|member|Lun
id|Lun
suffix:colon
l_int|3
comma
DECL|member|LBA_MID
id|LBA_MID
suffix:colon
l_int|8
comma
multiline_comment|/* NOTE: total of 21 bits in LBA */
DECL|member|LBA_LO
id|LBA_LO
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Max LBA = 0x001fffff          */
DECL|member|BlockCount
id|u8
id|BlockCount
suffix:semicolon
DECL|member|Control
id|u8
id|Control
suffix:semicolon
DECL|typedef|SCSI_RW6_t
)brace
id|SCSI_RW6_t
suffix:semicolon
DECL|macro|MAX_RW6_LBA
mdefine_line|#define MAX_RW6_LBA  ((u32)0x001fffff)
multiline_comment|/*&n; *  Structure definition for READ10, WRITE10 (10-byte CDB)&n; *&n; *    NOTE: ParityCheck bit is applicable only for VERIFY and WRITE VERIFY for&n; *    the ADP-92 DAC only.  In the SCSI2 spec. this same bit is defined as a&n; *    FUA (forced unit access) bit for READs and WRITEs.  Since this driver&n; *    does not use the FUA, this bit is defined as it is used by the ADP-92.&n; *    Also, for READ CAPACITY, only the OpCode field is used.&n; */
DECL|struct|SCSI_RW10_CDB
r_typedef
r_struct
id|SCSI_RW10_CDB
(brace
DECL|member|OpCode
id|u8
id|OpCode
suffix:semicolon
DECL|member|Reserved1
id|u8
id|Reserved1
suffix:semicolon
DECL|member|LBA
id|u32
id|LBA
suffix:semicolon
DECL|member|Reserved2
id|u8
id|Reserved2
suffix:semicolon
DECL|member|BlockCount
id|u16
id|BlockCount
suffix:semicolon
DECL|member|Control
id|u8
id|Control
suffix:semicolon
DECL|typedef|SCSI_RW10_t
)brace
id|SCSI_RW10_t
suffix:semicolon
DECL|macro|PARITY_CHECK
mdefine_line|#define PARITY_CHECK  0x08    /* parity check bit - byte[1], bit 3 */
multiline_comment|/*&n;     *  Structure definition for data returned by READ CAPACITY cmd;&n;     *  READ CAPACITY data&n;     */
DECL|struct|READ_CAP_DATA
r_typedef
r_struct
id|READ_CAP_DATA
(brace
DECL|member|MaxLBA
id|u32
id|MaxLBA
suffix:semicolon
DECL|member|BlockBytes
id|u32
id|BlockBytes
suffix:semicolon
DECL|typedef|SCSI_READ_CAP_DATA_t
DECL|typedef|pSCSI_READ_CAP_DATA_t
)brace
id|SCSI_READ_CAP_DATA_t
comma
op_star
id|pSCSI_READ_CAP_DATA_t
suffix:semicolon
multiline_comment|/*&n; *  Structure definition for FORMAT UNIT CDB (6-byte CDB)&n; */
DECL|struct|_SCSI_FORMAT_UNIT
r_typedef
r_struct
id|_SCSI_FORMAT_UNIT
(brace
DECL|member|OpCode
id|u8
id|OpCode
suffix:semicolon
DECL|member|Reserved1
id|u8
id|Reserved1
suffix:semicolon
DECL|member|VendorSpecific
id|u8
id|VendorSpecific
suffix:semicolon
DECL|member|Interleave
id|u16
id|Interleave
suffix:semicolon
DECL|member|Control
id|u8
id|Control
suffix:semicolon
DECL|typedef|SCSI_FORMAT_UNIT_t
)brace
id|SCSI_FORMAT_UNIT_t
suffix:semicolon
multiline_comment|/*&n; *    Structure definition for REQUEST SENSE (6-byte CDB)&n; */
DECL|struct|_SCSI_REQUEST_SENSE
r_typedef
r_struct
id|_SCSI_REQUEST_SENSE
(brace
DECL|member|OpCode
id|u8
id|OpCode
suffix:semicolon
DECL|member|Reserved1
id|u8
id|Reserved1
suffix:semicolon
DECL|member|Reserved2
id|u8
id|Reserved2
suffix:semicolon
DECL|member|Reserved3
id|u8
id|Reserved3
suffix:semicolon
DECL|member|AllocLength
id|u8
id|AllocLength
suffix:semicolon
DECL|member|Control
id|u8
id|Control
suffix:semicolon
DECL|typedef|SCSI_REQ_SENSE_t
)brace
id|SCSI_REQ_SENSE_t
suffix:semicolon
multiline_comment|/*&n; *  Structure definition for REPORT LUNS (12-byte CDB)&n; */
DECL|struct|_SCSI_REPORT_LUNS
r_typedef
r_struct
id|_SCSI_REPORT_LUNS
(brace
DECL|member|OpCode
id|u8
id|OpCode
suffix:semicolon
DECL|member|Reserved1
id|u8
id|Reserved1
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|AllocationLength
id|u32
id|AllocationLength
suffix:semicolon
DECL|member|Reserved2
id|u8
id|Reserved2
suffix:semicolon
DECL|member|Control
id|u8
id|Control
suffix:semicolon
DECL|typedef|SCSI_REPORT_LUNS_t
DECL|typedef|pSCSI_REPORT_LUNS_t
)brace
id|SCSI_REPORT_LUNS_t
comma
op_star
id|pSCSI_REPORT_LUNS_t
suffix:semicolon
multiline_comment|/*&n;     *  (per-level) LUN information bytes&n;     */
multiline_comment|/*&n; *  Following doesn&squot;t work on ARMCC compiler&n; *  [apparently] because it pads every struct&n; *  to be multiple of 4 bytes!&n; *  So SCSI_LUN_LEVELS_t winds up being 16&n; *  bytes instead of 8!&n; *&n;    typedef struct LUN_INFO&n;    {&n;        u8     AddrMethod_plus_LunOrBusNumber;&n;        u8     LunOrTarget;&n;    } SCSI_LUN_INFO_t, *pSCSI_LUN_INFO_t;&n;&n;    typedef struct LUN_LEVELS&n;    {&n;        SCSI_LUN_INFO_t  LUN_0;&n;        SCSI_LUN_INFO_t  LUN_1;&n;        SCSI_LUN_INFO_t  LUN_2;&n;        SCSI_LUN_INFO_t  LUN_3;&n;    } SCSI_LUN_LEVELS_t, *pSCSI_LUN_LEVELS_t;&n;*/
multiline_comment|/*&n;     *  All 4 levels (8 bytes) of LUN information&n;     */
DECL|struct|LUN_LEVELS
r_typedef
r_struct
id|LUN_LEVELS
(brace
DECL|member|LVL1_AddrMethod_plus_LunOrBusNumber
id|u8
id|LVL1_AddrMethod_plus_LunOrBusNumber
suffix:semicolon
DECL|member|LVL1_LunOrTarget
id|u8
id|LVL1_LunOrTarget
suffix:semicolon
DECL|member|LVL2_AddrMethod_plus_LunOrBusNumber
id|u8
id|LVL2_AddrMethod_plus_LunOrBusNumber
suffix:semicolon
DECL|member|LVL2_LunOrTarget
id|u8
id|LVL2_LunOrTarget
suffix:semicolon
DECL|member|LVL3_AddrMethod_plus_LunOrBusNumber
id|u8
id|LVL3_AddrMethod_plus_LunOrBusNumber
suffix:semicolon
DECL|member|LVL3_LunOrTarget
id|u8
id|LVL3_LunOrTarget
suffix:semicolon
DECL|member|LVL4_AddrMethod_plus_LunOrBusNumber
id|u8
id|LVL4_AddrMethod_plus_LunOrBusNumber
suffix:semicolon
DECL|member|LVL4_LunOrTarget
id|u8
id|LVL4_LunOrTarget
suffix:semicolon
DECL|typedef|SCSI_LUN_LEVELS_t
DECL|typedef|pSCSI_LUN_LEVELS_t
)brace
id|SCSI_LUN_LEVELS_t
comma
op_star
id|pSCSI_LUN_LEVELS_t
suffix:semicolon
multiline_comment|/*&n;     *  Structure definition for data returned by REPORT LUNS cmd;&n;     *  LUN reporting parameter list format&n;     */
DECL|struct|LUN_REPORT
r_typedef
r_struct
id|LUN_REPORT
(brace
DECL|member|LunListLength
id|u32
id|LunListLength
suffix:semicolon
DECL|member|Reserved
id|u32
id|Reserved
suffix:semicolon
DECL|member|LunInfo
id|SCSI_LUN_LEVELS_t
id|LunInfo
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|SCSI_LUN_REPORT_t
DECL|typedef|pSCSI_LUN_REPORT_t
)brace
id|SCSI_LUN_REPORT_t
comma
op_star
id|pSCSI_LUN_REPORT_t
suffix:semicolon
multiline_comment|/****************************************************************************&n; *&n; *  Externals&n; */
multiline_comment|/****************************************************************************&n; *&n; *  Public Typedefs &amp; Related Defines&n; */
multiline_comment|/****************************************************************************&n; *&n; *  Macros (embedded, above)&n; */
multiline_comment|/****************************************************************************&n; *&n; *  Public Variables&n; */
multiline_comment|/****************************************************************************&n; *&n; *  Public Prototypes (module entry points)&n; */
multiline_comment|/***************************************************************************/
macro_line|#endif
eof
