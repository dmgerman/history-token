multiline_comment|/****************************************************************************&n; * Perceptive Solutions, Inc. PCI-2000 device driver for Linux.&n; *&n; * pci2000.h - Linux Host Driver for PCI-2000 IntelliCache SCSI Adapters&n; *&n; * Copyright (c) 1997-1999 Perceptive Solutions, Inc.&n; * All Rights Reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that redistributions of source&n; * code retain the above copyright notice and this comment without&n; * modification.&n; *&n; * Technical updates and product information at:&n; *  http://www.psidisk.com&n; *&n; * Please send questions, comments, bug reports to:&n; *  tech@psidisk.com Technical Support&n; *&n; ****************************************************************************/
macro_line|#ifndef _PCI2000_H
DECL|macro|_PCI2000_H
mdefine_line|#define _PCI2000_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#ifndef&t;PSI_EIDE_SCSIOP
DECL|macro|PSI_EIDE_SCSIOP
mdefine_line|#define&t;PSI_EIDE_SCSIOP&t;1
macro_line|#ifndef LINUX_VERSION_CODE
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif 
DECL|macro|LINUXVERSION
mdefine_line|#define&t;LINUXVERSION(v,p,s)    (((v)&lt;&lt;16) + ((p)&lt;&lt;8) + (s))
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;definition of standard data types&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|CHAR
mdefine_line|#define&t;CHAR&t;char
DECL|macro|UCHAR
mdefine_line|#define&t;UCHAR&t;unsigned char
DECL|macro|SHORT
mdefine_line|#define&t;SHORT&t;short
DECL|macro|USHORT
mdefine_line|#define&t;USHORT&t;unsigned short
DECL|macro|BOOL
mdefine_line|#define&t;BOOL&t;long
DECL|macro|LONG
mdefine_line|#define&t;LONG&t;long
DECL|macro|ULONG
mdefine_line|#define&t;ULONG&t;unsigned long
DECL|macro|VOID
mdefine_line|#define&t;VOID&t;void
DECL|typedef|PCHAR
r_typedef
id|CHAR
op_star
id|PCHAR
suffix:semicolon
DECL|typedef|PUCHAR
r_typedef
id|UCHAR
op_star
id|PUCHAR
suffix:semicolon
DECL|typedef|PSHORT
r_typedef
id|SHORT
op_star
id|PSHORT
suffix:semicolon
DECL|typedef|PUSHORT
r_typedef
id|USHORT
op_star
id|PUSHORT
suffix:semicolon
DECL|typedef|PBOOL
r_typedef
id|BOOL
op_star
id|PBOOL
suffix:semicolon
DECL|typedef|PLONG
r_typedef
id|LONG
op_star
id|PLONG
suffix:semicolon
DECL|typedef|PULONG
r_typedef
id|ULONG
op_star
id|PULONG
suffix:semicolon
DECL|typedef|PVOID
r_typedef
id|VOID
op_star
id|PVOID
suffix:semicolon
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Misc. macros&t;&t;&t; &t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|ANY2SCSI
mdefine_line|#define ANY2SCSI(up, p)&t;&t;&t;&t;&t;&bslash;&n;((UCHAR *)up)[0] = (((ULONG)(p)) &gt;&gt; 8);&t;&bslash;&n;((UCHAR *)up)[1] = ((ULONG)(p));
DECL|macro|SCSI2LONG
mdefine_line|#define SCSI2LONG(up)&t;&t;&t;&t;&t;&bslash;&n;( (((long)*(((UCHAR *)up))) &lt;&lt; 16)&t;&t;&bslash;&n;+ (((long)(((UCHAR *)up)[1])) &lt;&lt; 8)&t;&t;&bslash;&n;+ ((long)(((UCHAR *)up)[2])) )
DECL|macro|XANY2SCSI
mdefine_line|#define XANY2SCSI(up, p)&t;&t;&t;&t;&bslash;&n;((UCHAR *)up)[0] = ((long)(p)) &gt;&gt; 24;&t;&bslash;&n;((UCHAR *)up)[1] = ((long)(p)) &gt;&gt; 16;&t;&bslash;&n;((UCHAR *)up)[2] = ((long)(p)) &gt;&gt; 8;&t;&bslash;&n;((UCHAR *)up)[3] = ((long)(p));
DECL|macro|XSCSI2LONG
mdefine_line|#define XSCSI2LONG(up)&t;&t;&t;&t;&t;&bslash;&n;( (((long)(((UCHAR *)up)[0])) &lt;&lt; 24)&t;&bslash;&n;+ (((long)(((UCHAR *)up)[1])) &lt;&lt; 16)&t;&bslash;&n;+ (((long)(((UCHAR *)up)[2])) &lt;&lt;  8)&t;&bslash;&n;+ ((long)(((UCHAR *)up)[3])) )
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;SCSI CDB operation codes &t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|SCSIOP_TEST_UNIT_READY
mdefine_line|#define SCSIOP_TEST_UNIT_READY&t;&t;0x00
DECL|macro|SCSIOP_REZERO_UNIT
mdefine_line|#define SCSIOP_REZERO_UNIT&t;&t;&t;0x01
DECL|macro|SCSIOP_REWIND
mdefine_line|#define SCSIOP_REWIND&t;&t;&t;&t;0x01
DECL|macro|SCSIOP_REQUEST_BLOCK_ADDR
mdefine_line|#define SCSIOP_REQUEST_BLOCK_ADDR&t;0x02
DECL|macro|SCSIOP_REQUEST_SENSE
mdefine_line|#define SCSIOP_REQUEST_SENSE&t;&t;0x03
DECL|macro|SCSIOP_FORMAT_UNIT
mdefine_line|#define SCSIOP_FORMAT_UNIT&t;&t;&t;0x04
DECL|macro|SCSIOP_READ_BLOCK_LIMITS
mdefine_line|#define SCSIOP_READ_BLOCK_LIMITS&t;0x05
DECL|macro|SCSIOP_REASSIGN_BLOCKS
mdefine_line|#define SCSIOP_REASSIGN_BLOCKS&t;&t;0x07
DECL|macro|SCSIOP_READ6
mdefine_line|#define SCSIOP_READ6&t;&t;&t;&t;0x08
DECL|macro|SCSIOP_RECEIVE
mdefine_line|#define SCSIOP_RECEIVE&t;&t;&t;&t;0x08
DECL|macro|SCSIOP_WRITE6
mdefine_line|#define SCSIOP_WRITE6&t;&t;&t;&t;0x0A
DECL|macro|SCSIOP_PRINT
mdefine_line|#define SCSIOP_PRINT&t;&t;&t;&t;0x0A
DECL|macro|SCSIOP_SEND
mdefine_line|#define SCSIOP_SEND&t;&t;&t;&t;&t;0x0A
DECL|macro|SCSIOP_SEEK6
mdefine_line|#define SCSIOP_SEEK6&t;&t;&t;&t;0x0B
DECL|macro|SCSIOP_TRACK_SELECT
mdefine_line|#define SCSIOP_TRACK_SELECT&t;&t;&t;0x0B
DECL|macro|SCSIOP_SLEW_PRINT
mdefine_line|#define SCSIOP_SLEW_PRINT&t;&t;&t;0x0B
DECL|macro|SCSIOP_SEEK_BLOCK
mdefine_line|#define SCSIOP_SEEK_BLOCK&t;&t;&t;0x0C
DECL|macro|SCSIOP_PARTITION
mdefine_line|#define SCSIOP_PARTITION&t;&t;&t;0x0D
DECL|macro|SCSIOP_READ_REVERSE
mdefine_line|#define SCSIOP_READ_REVERSE&t;&t;&t;0x0F
DECL|macro|SCSIOP_WRITE_FILEMARKS
mdefine_line|#define SCSIOP_WRITE_FILEMARKS&t;&t;0x10
DECL|macro|SCSIOP_FLUSH_BUFFER
mdefine_line|#define SCSIOP_FLUSH_BUFFER&t;&t;&t;0x10
DECL|macro|SCSIOP_SPACE
mdefine_line|#define SCSIOP_SPACE&t;&t;&t;&t;0x11
DECL|macro|SCSIOP_INQUIRY
mdefine_line|#define SCSIOP_INQUIRY&t;&t;&t;&t;0x12
DECL|macro|SCSIOP_VERIFY6
mdefine_line|#define SCSIOP_VERIFY6&t;&t;&t;&t;0x13
DECL|macro|SCSIOP_RECOVER_BUF_DATA
mdefine_line|#define SCSIOP_RECOVER_BUF_DATA&t;&t;0x14
DECL|macro|SCSIOP_MODE_SELECT
mdefine_line|#define SCSIOP_MODE_SELECT&t;&t;&t;0x15
DECL|macro|SCSIOP_RESERVE_UNIT
mdefine_line|#define SCSIOP_RESERVE_UNIT&t;&t;&t;0x16
DECL|macro|SCSIOP_RELEASE_UNIT
mdefine_line|#define SCSIOP_RELEASE_UNIT&t;&t;&t;0x17
DECL|macro|SCSIOP_COPY
mdefine_line|#define SCSIOP_COPY&t;&t;&t;&t;&t;0x18
DECL|macro|SCSIOP_ERASE
mdefine_line|#define SCSIOP_ERASE&t;&t;&t;&t;0x19
DECL|macro|SCSIOP_MODE_SENSE
mdefine_line|#define SCSIOP_MODE_SENSE&t;&t;&t;0x1A
DECL|macro|SCSIOP_START_STOP_UNIT
mdefine_line|#define SCSIOP_START_STOP_UNIT&t;&t;0x1B
DECL|macro|SCSIOP_STOP_PRINT
mdefine_line|#define SCSIOP_STOP_PRINT&t;&t;&t;0x1B
DECL|macro|SCSIOP_LOAD_UNLOAD
mdefine_line|#define SCSIOP_LOAD_UNLOAD&t;&t;&t;0x1B
DECL|macro|SCSIOP_RECEIVE_DIAGNOSTIC
mdefine_line|#define SCSIOP_RECEIVE_DIAGNOSTIC&t;0x1C
DECL|macro|SCSIOP_SEND_DIAGNOSTIC
mdefine_line|#define SCSIOP_SEND_DIAGNOSTIC&t;&t;0x1D
DECL|macro|SCSIOP_MEDIUM_REMOVAL
mdefine_line|#define SCSIOP_MEDIUM_REMOVAL&t;&t;0x1E
DECL|macro|SCSIOP_READ_CAPACITY
mdefine_line|#define SCSIOP_READ_CAPACITY&t;&t;0x25
DECL|macro|SCSIOP_READ
mdefine_line|#define SCSIOP_READ&t;&t;&t;&t;&t;0x28
DECL|macro|SCSIOP_WRITE
mdefine_line|#define SCSIOP_WRITE&t;&t;&t;&t;0x2A
DECL|macro|SCSIOP_SEEK
mdefine_line|#define SCSIOP_SEEK&t;&t;&t;&t;&t;0x2B
DECL|macro|SCSIOP_LOCATE
mdefine_line|#define SCSIOP_LOCATE&t;&t;&t;&t;0x2B
DECL|macro|SCSIOP_WRITE_VERIFY
mdefine_line|#define SCSIOP_WRITE_VERIFY&t;&t;&t;0x2E
DECL|macro|SCSIOP_VERIFY
mdefine_line|#define SCSIOP_VERIFY&t;&t;&t;&t;0x2F
DECL|macro|SCSIOP_SEARCH_DATA_HIGH
mdefine_line|#define SCSIOP_SEARCH_DATA_HIGH&t;&t;0x30
DECL|macro|SCSIOP_SEARCH_DATA_EQUAL
mdefine_line|#define SCSIOP_SEARCH_DATA_EQUAL&t;0x31
DECL|macro|SCSIOP_SEARCH_DATA_LOW
mdefine_line|#define SCSIOP_SEARCH_DATA_LOW&t;&t;0x32
DECL|macro|SCSIOP_SET_LIMITS
mdefine_line|#define SCSIOP_SET_LIMITS&t;&t;&t;0x33
DECL|macro|SCSIOP_READ_POSITION
mdefine_line|#define SCSIOP_READ_POSITION&t;&t;0x34
DECL|macro|SCSIOP_SYNCHRONIZE_CACHE
mdefine_line|#define SCSIOP_SYNCHRONIZE_CACHE&t;0x35
DECL|macro|SCSIOP_COMPARE
mdefine_line|#define SCSIOP_COMPARE&t;&t;&t;&t;0x39
DECL|macro|SCSIOP_COPY_COMPARE
mdefine_line|#define SCSIOP_COPY_COMPARE&t;&t;&t;0x3A
DECL|macro|SCSIOP_WRITE_DATA_BUFF
mdefine_line|#define SCSIOP_WRITE_DATA_BUFF&t;&t;0x3B
DECL|macro|SCSIOP_READ_DATA_BUFF
mdefine_line|#define SCSIOP_READ_DATA_BUFF&t;&t;0x3C
DECL|macro|SCSIOP_CHANGE_DEFINITION
mdefine_line|#define SCSIOP_CHANGE_DEFINITION&t;0x40
DECL|macro|SCSIOP_READ_SUB_CHANNEL
mdefine_line|#define SCSIOP_READ_SUB_CHANNEL&t;&t;0x42
DECL|macro|SCSIOP_READ_TOC
mdefine_line|#define SCSIOP_READ_TOC&t;&t;&t;&t;0x43
DECL|macro|SCSIOP_READ_HEADER
mdefine_line|#define SCSIOP_READ_HEADER&t;&t;&t;0x44
DECL|macro|SCSIOP_PLAY_AUDIO
mdefine_line|#define SCSIOP_PLAY_AUDIO&t;&t;&t;0x45
DECL|macro|SCSIOP_PLAY_AUDIO_MSF
mdefine_line|#define SCSIOP_PLAY_AUDIO_MSF&t;&t;0x47
DECL|macro|SCSIOP_PLAY_TRACK_INDEX
mdefine_line|#define SCSIOP_PLAY_TRACK_INDEX&t;&t;0x48
DECL|macro|SCSIOP_PLAY_TRACK_RELATIVE
mdefine_line|#define SCSIOP_PLAY_TRACK_RELATIVE&t;0x49
DECL|macro|SCSIOP_PAUSE_RESUME
mdefine_line|#define SCSIOP_PAUSE_RESUME&t;&t;&t;0x4B
DECL|macro|SCSIOP_LOG_SELECT
mdefine_line|#define SCSIOP_LOG_SELECT&t;&t;&t;0x4C
DECL|macro|SCSIOP_LOG_SENSE
mdefine_line|#define SCSIOP_LOG_SENSE&t;&t;&t;0x4D
DECL|macro|SCSIOP_MODE_SELECT10
mdefine_line|#define SCSIOP_MODE_SELECT10&t;&t;0x55
DECL|macro|SCSIOP_MODE_SENSE10
mdefine_line|#define SCSIOP_MODE_SENSE10&t;&t;&t;0x5A
DECL|macro|SCSIOP_LOAD_UNLOAD_SLOT
mdefine_line|#define SCSIOP_LOAD_UNLOAD_SLOT&t;&t;0xA6
DECL|macro|SCSIOP_MECHANISM_STATUS
mdefine_line|#define SCSIOP_MECHANISM_STATUS&t;&t;0xBD
DECL|macro|SCSIOP_READ_CD
mdefine_line|#define SCSIOP_READ_CD&t;&t;&t;&t;0xBE
singleline_comment|// SCSI read capacity structure
DECL|struct|_READ_CAPACITY_DATA
r_typedef
r_struct
id|_READ_CAPACITY_DATA
(brace
DECL|member|blks
id|ULONG
id|blks
suffix:semicolon
multiline_comment|/* total blocks (converted to little endian) */
DECL|member|blksiz
id|ULONG
id|blksiz
suffix:semicolon
multiline_comment|/* size of each (converted to little endian) */
DECL|typedef|READ_CAPACITY_DATA
DECL|typedef|PREAD_CAPACITY_DATA
)brace
id|READ_CAPACITY_DATA
comma
op_star
id|PREAD_CAPACITY_DATA
suffix:semicolon
singleline_comment|// SCSI inquiry data
DECL|struct|_INQUIRYDATA
r_typedef
r_struct
id|_INQUIRYDATA
(brace
DECL|member|DeviceType
id|UCHAR
id|DeviceType
suffix:colon
l_int|5
suffix:semicolon
DECL|member|DeviceTypeQualifier
id|UCHAR
id|DeviceTypeQualifier
suffix:colon
l_int|3
suffix:semicolon
DECL|member|DeviceTypeModifier
id|UCHAR
id|DeviceTypeModifier
suffix:colon
l_int|7
suffix:semicolon
DECL|member|RemovableMedia
id|UCHAR
id|RemovableMedia
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Versions
id|UCHAR
id|Versions
suffix:semicolon
DECL|member|ResponseDataFormat
id|UCHAR
id|ResponseDataFormat
suffix:semicolon
DECL|member|AdditionalLength
id|UCHAR
id|AdditionalLength
suffix:semicolon
DECL|member|Reserved
id|UCHAR
id|Reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|SoftReset
id|UCHAR
id|SoftReset
suffix:colon
l_int|1
suffix:semicolon
DECL|member|CommandQueue
id|UCHAR
id|CommandQueue
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Reserved2
id|UCHAR
id|Reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|LinkedCommands
id|UCHAR
id|LinkedCommands
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Synchronous
id|UCHAR
id|Synchronous
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Wide16Bit
id|UCHAR
id|Wide16Bit
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Wide32Bit
id|UCHAR
id|Wide32Bit
suffix:colon
l_int|1
suffix:semicolon
DECL|member|RelativeAddressing
id|UCHAR
id|RelativeAddressing
suffix:colon
l_int|1
suffix:semicolon
DECL|member|VendorId
id|UCHAR
id|VendorId
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ProductId
id|UCHAR
id|ProductId
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|ProductRevisionLevel
id|UCHAR
id|ProductRevisionLevel
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|VendorSpecific
id|UCHAR
id|VendorSpecific
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|Reserved3
id|UCHAR
id|Reserved3
(braket
l_int|40
)braket
suffix:semicolon
DECL|typedef|INQUIRYDATA
DECL|typedef|PINQUIRYDATA
)brace
id|INQUIRYDATA
comma
op_star
id|PINQUIRYDATA
suffix:semicolon
macro_line|#endif
singleline_comment|// function prototypes
r_int
id|Pci2000_Detect
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
suffix:semicolon
r_int
id|Pci2000_Command
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_int
id|Pci2000_QueueCommand
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_int
id|Pci2000_Abort
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_int
id|Pci2000_Reset
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
r_int
id|Pci2000_Release
(paren
r_struct
id|Scsi_Host
op_star
id|pshost
)paren
suffix:semicolon
r_int
id|Pci2000_BiosParam
(paren
id|Disk
op_star
id|disk
comma
id|kdev_t
id|dev
comma
r_int
id|geom
(braket
)braket
)paren
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
multiline_comment|/* screen is 80 columns wide, damnit! */
DECL|macro|PCI2000
mdefine_line|#define PCI2000 {&t;&t;&t;&t;&bslash;&n;&t;proc_name:&t;&quot;pci2000&quot;,&t;&t;&t;&t;&t;&bslash;&n;&t;name:&t;&t;&quot;PCI-2000 SCSI Intelligent Disk Controller&quot;,&t;&bslash;&n;&t;detect:&t;&t;Pci2000_Detect,&t;&t;&t;&t;&t;&bslash;&n;&t;release:&t;Pci2000_Release,&t;&t;&t;&t;&bslash;&n;&t;command:&t;Pci2000_Command,&t;&t;&t;&t;&bslash;&n;&t;queuecommand:&t;Pci2000_QueueCommand,&t;&t;&t;&t;&bslash;&n;&t;abort:&t;&t;Pci2000_Abort,&t;&t;&t;&t;&t;&bslash;&n;&t;reset:&t;&t;Pci2000_Reset,&t;&t;&t;&t;&t;&bslash;&n;&t;bios_param:&t;Pci2000_BiosParam,&t;&t;&t;&t;&bslash;&n;&t;can_queue:&t;16,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;this_id:&t;-1,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;sg_tablesize:&t;16,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;cmd_per_lun:&t;1,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;present:&t;0,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unchecked_isa_dma:0,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;use_clustering:&t;DISABLE_CLUSTERING,&t;&t;&t;&t;&bslash;&n;}
macro_line|#endif
eof
