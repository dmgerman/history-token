multiline_comment|/*+M*************************************************************************&n; * Perceptive Solutions, Inc. PSI-240I device driver proc support for Linux.&n; *&n; * Copyright (c) 1997 Perceptive Solutions, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *&n; *&t;File Name:&t;&t;psi240i.h&n; *&n; *&t;Description:&t;Header file for the SCSI driver for the PSI240I&n; *&t;&t;&t;&t;&t;EIDE interface card.&n; *&n; *-M*************************************************************************/
macro_line|#ifndef _PSI240I_H
DECL|macro|_PSI240I_H
mdefine_line|#define _PSI240I_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#ifndef&t;PSI_EIDE_SCSIOP
DECL|macro|PSI_EIDE_SCSIOP
mdefine_line|#define&t;PSI_EIDE_SCSIOP&t;1
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Some defines that we like &t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|CHAR
mdefine_line|#define&t;CHAR&t;&t;char
DECL|macro|UCHAR
mdefine_line|#define&t;UCHAR&t;&t;unsigned char
DECL|macro|SHORT
mdefine_line|#define&t;SHORT&t;&t;short
DECL|macro|USHORT
mdefine_line|#define&t;USHORT&t;&t;unsigned short
DECL|macro|BOOL
mdefine_line|#define&t;BOOL&t;&t;unsigned short
DECL|macro|LONG
mdefine_line|#define&t;LONG&t;&t;long
DECL|macro|ULONG
mdefine_line|#define&t;ULONG&t;&t;unsigned long
DECL|macro|VOID
mdefine_line|#define&t;VOID&t;&t;void
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Timeout konstants&t;&t; &t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|TIMEOUT_READY
mdefine_line|#define&t;TIMEOUT_READY&t;&t;&t;&t;10&t;&t;
singleline_comment|// 100 mSec
DECL|macro|TIMEOUT_DRQ
mdefine_line|#define&t;TIMEOUT_DRQ&t;&t;&t;&t;&t;40&t;&t;
singleline_comment|// 400 mSec
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
singleline_comment|// IDE command definitions
DECL|macro|IDE_COMMAND_ATAPI_RESET
mdefine_line|#define IDE_COMMAND_ATAPI_RESET&t;&t;0x08
DECL|macro|IDE_COMMAND_READ
mdefine_line|#define IDE_COMMAND_READ&t;&t;&t;0x20
DECL|macro|IDE_COMMAND_WRITE
mdefine_line|#define IDE_COMMAND_WRITE&t;&t;&t;0x30
DECL|macro|IDE_COMMAND_RECALIBRATE
mdefine_line|#define IDE_COMMAND_RECALIBRATE&t;&t;0x10
DECL|macro|IDE_COMMAND_SEEK
mdefine_line|#define IDE_COMMAND_SEEK&t;&t;&t;0x70
DECL|macro|IDE_COMMAND_SET_PARAMETERS
mdefine_line|#define IDE_COMMAND_SET_PARAMETERS&t;0x91
DECL|macro|IDE_COMMAND_VERIFY
mdefine_line|#define IDE_COMMAND_VERIFY&t;&t;&t;0x40
DECL|macro|IDE_COMMAND_ATAPI_PACKET
mdefine_line|#define IDE_COMMAND_ATAPI_PACKET&t;0xA0
DECL|macro|IDE_COMMAND_ATAPI_IDENTIFY
mdefine_line|#define IDE_COMMAND_ATAPI_IDENTIFY&t;0xA1
DECL|macro|IDE_CMD_READ_MULTIPLE
mdefine_line|#define&t;IDE_CMD_READ_MULTIPLE&t;&t;0xC4
DECL|macro|IDE_CMD_WRITE_MULTIPLE
mdefine_line|#define&t;IDE_CMD_WRITE_MULTIPLE&t;&t;0xC5
DECL|macro|IDE_CMD_SET_MULTIPLE
mdefine_line|#define&t;IDE_CMD_SET_MULTIPLE&t;&t;0xC6
DECL|macro|IDE_COMMAND_WRITE_DMA
mdefine_line|#define IDE_COMMAND_WRITE_DMA&t;&t;0xCA
DECL|macro|IDE_COMMAND_READ_DMA
mdefine_line|#define IDE_COMMAND_READ_DMA&t;&t;0xC8
DECL|macro|IDE_COMMAND_IDENTIFY
mdefine_line|#define IDE_COMMAND_IDENTIFY&t;&t;0xEC
singleline_comment|// IDE status definitions
DECL|macro|IDE_STATUS_ERROR
mdefine_line|#define IDE_STATUS_ERROR&t;&t;&t;0x01
DECL|macro|IDE_STATUS_INDEX
mdefine_line|#define IDE_STATUS_INDEX&t;&t;&t;0x02
DECL|macro|IDE_STATUS_CORRECTED_ERROR
mdefine_line|#define IDE_STATUS_CORRECTED_ERROR&t;0x04
DECL|macro|IDE_STATUS_DRQ
mdefine_line|#define IDE_STATUS_DRQ&t;&t;&t;&t;0x08
DECL|macro|IDE_STATUS_DSC
mdefine_line|#define IDE_STATUS_DSC&t;&t;&t;&t;0x10
DECL|macro|IDE_STATUS_WRITE_FAULT
mdefine_line|#define&t;IDE_STATUS_WRITE_FAULT&t;&t;0x20
DECL|macro|IDE_STATUS_DRDY
mdefine_line|#define IDE_STATUS_DRDY&t;&t;&t;&t;0x40
DECL|macro|IDE_STATUS_BUSY
mdefine_line|#define IDE_STATUS_BUSY&t;&t;&t;&t;0x80
singleline_comment|// IDE error definitions
DECL|macro|IDE_ERROR_AMNF
mdefine_line|#define&t;IDE_ERROR_AMNF&t;&t;&t;&t;0x01
DECL|macro|IDE_ERROR_TKONF
mdefine_line|#define&t;IDE_ERROR_TKONF&t;&t;&t;&t;0x02
DECL|macro|IDE_ERROR_ABRT
mdefine_line|#define&t;IDE_ERROR_ABRT&t;&t;&t;&t;0x04
DECL|macro|IDE_ERROR_MCR
mdefine_line|#define&t;IDE_ERROR_MCR&t;&t;&t;&t;0x08
DECL|macro|IDE_ERROR_IDFN
mdefine_line|#define&t;IDE_ERROR_IDFN&t;&t;&t;&t;0x10
DECL|macro|IDE_ERROR_MC
mdefine_line|#define&t;IDE_ERROR_MC&t;&t;&t;&t;0x20
DECL|macro|IDE_ERROR_UNC
mdefine_line|#define&t;IDE_ERROR_UNC&t;&t;&t;&t;0x40
DECL|macro|IDE_ERROR_BBK
mdefine_line|#define&t;IDE_ERROR_BBK&t;&t;&t;&t;0x80
singleline_comment|//&t;IDE interface structure
DECL|struct|_IDE_STRUCT
r_typedef
r_struct
id|_IDE_STRUCT
(brace
r_union
(brace
DECL|member|ide
id|UCHAR
id|ide
(braket
l_int|9
)braket
suffix:semicolon
r_struct
(brace
DECL|member|data
id|USHORT
id|data
suffix:semicolon
DECL|member|sectors
id|UCHAR
id|sectors
suffix:semicolon
DECL|member|lba
id|UCHAR
id|lba
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|cmd
id|UCHAR
id|cmd
suffix:semicolon
DECL|member|spigot
id|UCHAR
id|spigot
suffix:semicolon
DECL|member|ides
)brace
id|ides
suffix:semicolon
DECL|member|ide
)brace
id|ide
suffix:semicolon
DECL|typedef|IDE_STRUCT
)brace
id|IDE_STRUCT
suffix:semicolon
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
macro_line|#ifndef HOSTS_C
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
singleline_comment|// IDE IDENTIFY data
DECL|struct|_IDENTIFY_DATA
r_typedef
r_struct
id|_IDENTIFY_DATA
(brace
DECL|member|GeneralConfiguration
id|USHORT
id|GeneralConfiguration
suffix:semicolon
singleline_comment|// 00
DECL|member|NumberOfCylinders
id|USHORT
id|NumberOfCylinders
suffix:semicolon
singleline_comment|// 02
DECL|member|Reserved1
id|USHORT
id|Reserved1
suffix:semicolon
singleline_comment|// 04
DECL|member|NumberOfHeads
id|USHORT
id|NumberOfHeads
suffix:semicolon
singleline_comment|// 06
DECL|member|UnformattedBytesPerTrack
id|USHORT
id|UnformattedBytesPerTrack
suffix:semicolon
singleline_comment|// 08
DECL|member|UnformattedBytesPerSector
id|USHORT
id|UnformattedBytesPerSector
suffix:semicolon
singleline_comment|// 0A
DECL|member|SectorsPerTrack
id|USHORT
id|SectorsPerTrack
suffix:semicolon
singleline_comment|// 0C
DECL|member|VendorUnique1
id|USHORT
id|VendorUnique1
(braket
l_int|3
)braket
suffix:semicolon
singleline_comment|// 0E
DECL|member|SerialNumber
id|USHORT
id|SerialNumber
(braket
l_int|10
)braket
suffix:semicolon
singleline_comment|// 14
DECL|member|BufferType
id|USHORT
id|BufferType
suffix:semicolon
singleline_comment|// 28
DECL|member|BufferSectorSize
id|USHORT
id|BufferSectorSize
suffix:semicolon
singleline_comment|// 2A
DECL|member|NumberOfEccBytes
id|USHORT
id|NumberOfEccBytes
suffix:semicolon
singleline_comment|// 2C
DECL|member|FirmwareRevision
id|USHORT
id|FirmwareRevision
(braket
l_int|4
)braket
suffix:semicolon
singleline_comment|// 2E
DECL|member|ModelNumber
id|USHORT
id|ModelNumber
(braket
l_int|20
)braket
suffix:semicolon
singleline_comment|// 36
DECL|member|MaximumBlockTransfer
id|UCHAR
id|MaximumBlockTransfer
suffix:semicolon
singleline_comment|// 5E
DECL|member|VendorUnique2
id|UCHAR
id|VendorUnique2
suffix:semicolon
singleline_comment|// 5F
DECL|member|DoubleWordIo
id|USHORT
id|DoubleWordIo
suffix:semicolon
singleline_comment|// 60
DECL|member|Capabilities
id|USHORT
id|Capabilities
suffix:semicolon
singleline_comment|// 62
DECL|member|Reserved2
id|USHORT
id|Reserved2
suffix:semicolon
singleline_comment|// 64
DECL|member|VendorUnique3
id|UCHAR
id|VendorUnique3
suffix:semicolon
singleline_comment|// 66
DECL|member|PioCycleTimingMode
id|UCHAR
id|PioCycleTimingMode
suffix:semicolon
singleline_comment|// 67
DECL|member|VendorUnique4
id|UCHAR
id|VendorUnique4
suffix:semicolon
singleline_comment|// 68
DECL|member|DmaCycleTimingMode
id|UCHAR
id|DmaCycleTimingMode
suffix:semicolon
singleline_comment|// 69
DECL|member|TranslationFieldsValid
id|USHORT
id|TranslationFieldsValid
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 6A
DECL|member|Reserved3
id|USHORT
id|Reserved3
suffix:colon
l_int|15
suffix:semicolon
DECL|member|NumberOfCurrentCylinders
id|USHORT
id|NumberOfCurrentCylinders
suffix:semicolon
singleline_comment|// 6C
DECL|member|NumberOfCurrentHeads
id|USHORT
id|NumberOfCurrentHeads
suffix:semicolon
singleline_comment|// 6E
DECL|member|CurrentSectorsPerTrack
id|USHORT
id|CurrentSectorsPerTrack
suffix:semicolon
singleline_comment|// 70
DECL|member|CurrentSectorCapacity
id|ULONG
id|CurrentSectorCapacity
suffix:semicolon
singleline_comment|// 72
DECL|member|Reserved4
id|USHORT
id|Reserved4
(braket
l_int|197
)braket
suffix:semicolon
singleline_comment|// 76
DECL|typedef|IDENTIFY_DATA
DECL|typedef|PIDENTIFY_DATA
)brace
id|IDENTIFY_DATA
comma
op_star
id|PIDENTIFY_DATA
suffix:semicolon
singleline_comment|// Identify data without the Reserved4.
DECL|struct|_IDENTIFY_DATA2
r_typedef
r_struct
id|_IDENTIFY_DATA2
(brace
DECL|member|GeneralConfiguration
id|USHORT
id|GeneralConfiguration
suffix:semicolon
singleline_comment|// 00
DECL|member|NumberOfCylinders
id|USHORT
id|NumberOfCylinders
suffix:semicolon
singleline_comment|// 02
DECL|member|Reserved1
id|USHORT
id|Reserved1
suffix:semicolon
singleline_comment|// 04
DECL|member|NumberOfHeads
id|USHORT
id|NumberOfHeads
suffix:semicolon
singleline_comment|// 06
DECL|member|UnformattedBytesPerTrack
id|USHORT
id|UnformattedBytesPerTrack
suffix:semicolon
singleline_comment|// 08
DECL|member|UnformattedBytesPerSector
id|USHORT
id|UnformattedBytesPerSector
suffix:semicolon
singleline_comment|// 0A
DECL|member|SectorsPerTrack
id|USHORT
id|SectorsPerTrack
suffix:semicolon
singleline_comment|// 0C
DECL|member|VendorUnique1
id|USHORT
id|VendorUnique1
(braket
l_int|3
)braket
suffix:semicolon
singleline_comment|// 0E
DECL|member|SerialNumber
id|USHORT
id|SerialNumber
(braket
l_int|10
)braket
suffix:semicolon
singleline_comment|// 14
DECL|member|BufferType
id|USHORT
id|BufferType
suffix:semicolon
singleline_comment|// 28
DECL|member|BufferSectorSize
id|USHORT
id|BufferSectorSize
suffix:semicolon
singleline_comment|// 2A
DECL|member|NumberOfEccBytes
id|USHORT
id|NumberOfEccBytes
suffix:semicolon
singleline_comment|// 2C
DECL|member|FirmwareRevision
id|USHORT
id|FirmwareRevision
(braket
l_int|4
)braket
suffix:semicolon
singleline_comment|// 2E
DECL|member|ModelNumber
id|USHORT
id|ModelNumber
(braket
l_int|20
)braket
suffix:semicolon
singleline_comment|// 36
DECL|member|MaximumBlockTransfer
id|UCHAR
id|MaximumBlockTransfer
suffix:semicolon
singleline_comment|// 5E
DECL|member|VendorUnique2
id|UCHAR
id|VendorUnique2
suffix:semicolon
singleline_comment|// 5F
DECL|member|DoubleWordIo
id|USHORT
id|DoubleWordIo
suffix:semicolon
singleline_comment|// 60
DECL|member|Capabilities
id|USHORT
id|Capabilities
suffix:semicolon
singleline_comment|// 62
DECL|member|Reserved2
id|USHORT
id|Reserved2
suffix:semicolon
singleline_comment|// 64
DECL|member|VendorUnique3
id|UCHAR
id|VendorUnique3
suffix:semicolon
singleline_comment|// 66
DECL|member|PioCycleTimingMode
id|UCHAR
id|PioCycleTimingMode
suffix:semicolon
singleline_comment|// 67
DECL|member|VendorUnique4
id|UCHAR
id|VendorUnique4
suffix:semicolon
singleline_comment|// 68
DECL|member|DmaCycleTimingMode
id|UCHAR
id|DmaCycleTimingMode
suffix:semicolon
singleline_comment|// 69
DECL|member|TranslationFieldsValid
id|USHORT
id|TranslationFieldsValid
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 6A
DECL|member|Reserved3
id|USHORT
id|Reserved3
suffix:colon
l_int|15
suffix:semicolon
DECL|member|NumberOfCurrentCylinders
id|USHORT
id|NumberOfCurrentCylinders
suffix:semicolon
singleline_comment|// 6C
DECL|member|NumberOfCurrentHeads
id|USHORT
id|NumberOfCurrentHeads
suffix:semicolon
singleline_comment|// 6E
DECL|member|CurrentSectorsPerTrack
id|USHORT
id|CurrentSectorsPerTrack
suffix:semicolon
singleline_comment|// 70
DECL|member|CurrentSectorCapacity
id|ULONG
id|CurrentSectorCapacity
suffix:semicolon
singleline_comment|// 72
DECL|typedef|IDENTIFY_DATA2
DECL|typedef|PIDENTIFY_DATA2
)brace
id|IDENTIFY_DATA2
comma
op_star
id|PIDENTIFY_DATA2
suffix:semicolon
macro_line|#endif&t;
singleline_comment|// PSI_EIDE_SCSIOP
singleline_comment|// function prototypes
r_int
id|Psi240i_Detect
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
suffix:semicolon
r_int
id|Psi240i_Command
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_int
id|Psi240i_QueueCommand
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
id|Psi240i_Abort
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_int
id|Psi240i_Reset
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
id|Psi240i_BiosParam
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
DECL|macro|PSI240I
mdefine_line|#define PSI240I { proc_name:      &quot;psi240i&quot;, &bslash;&n;&t;&t;  name:           &quot;PSI-240I EIDE Disk Controller&quot;,&bslash;&n;&t;&t;  detect:         Psi240i_Detect,&t;&t;&t;&bslash;&n;&t;&t;  command:&t;  Psi240i_Command,&t;&t;&t;&bslash;&n;&t;&t;  queuecommand:&t;  Psi240i_QueueCommand,&t;&t;&bslash;&n;&t;&t;  abort:&t;  Psi240i_Abort,&t;&t;&t;&bslash;&n;&t;&t;  reset:&t;  Psi240i_Reset,&t;&t;&t;&bslash;&n;&t;&t;  bios_param:&t;  Psi240i_BiosParam,                 &t;&bslash;&n;&t;&t;  can_queue:&t;  1, &t;&t;&t;&t;&t;&bslash;&n;&t;&t;  this_id:&t;  -1, &t;&t;&t;&t;&t;&bslash;&n;&t;&t;  sg_tablesize:&t;  SG_NONE,&t;&t; &t;&t;&bslash;&n;&t;&t;  cmd_per_lun:&t;  1, &t;&t;&t;&t;&t;&bslash;&n;&t;&t;  use_clustering: DISABLE_CLUSTERING }
macro_line|#endif
eof
