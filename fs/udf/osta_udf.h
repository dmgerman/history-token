multiline_comment|/*&n; * osta_udf.h&n; *&n; * This file is based on OSTA UDF(tm) 2.01 (March 15, 2000)&n; * http://www.osta.org&n; *&n; * Copyright (c) 2001-2002  Ben Fennema &lt;bfennema@falcon.csc.calpoly.edu&gt;&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU Public License (&quot;GPL&quot;).&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#include &quot;ecma_167.h&quot;
macro_line|#ifndef _OSTA_UDF_H
DECL|macro|_OSTA_UDF_H
mdefine_line|#define _OSTA_UDF_H 1
multiline_comment|/* OSTA CS0 Charspec (UDF 2.01 2.1.2) */
DECL|macro|UDF_CHAR_SET_TYPE
mdefine_line|#define UDF_CHAR_SET_TYPE&t;&t;0
DECL|macro|UDF_CHAR_SET_INFO
mdefine_line|#define UDF_CHAR_SET_INFO&t;&t;&quot;OSTA Compressed Unicode&quot;
multiline_comment|/* Entity Identifier (UDF 2.01 2.1.5) */
multiline_comment|/* Identifiers (UDF 2.01 2.1.5.2) */
DECL|macro|UDF_ID_DEVELOPER
mdefine_line|#define UDF_ID_DEVELOPER&t;&t;&quot;*Linux UDFFS&quot;
DECL|macro|UDF_ID_COMPLIANT
mdefine_line|#define&t;UDF_ID_COMPLIANT&t;&t;&quot;*OSTA UDF Compliant&quot;
DECL|macro|UDF_ID_LV_INFO
mdefine_line|#define UDF_ID_LV_INFO&t;&t;&t;&quot;*UDF LV Info&quot;
DECL|macro|UDF_ID_FREE_EA
mdefine_line|#define UDF_ID_FREE_EA&t;&t;&t;&quot;*UDF FreeEASpace&quot;
DECL|macro|UDF_ID_FREE_APP_EA
mdefine_line|#define UDF_ID_FREE_APP_EA&t;&t;&quot;*UDF FreeAppEASpace&quot;
DECL|macro|UDF_ID_DVD_CGMS
mdefine_line|#define UDF_ID_DVD_CGMS&t;&t;&t;&quot;*UDF DVD CGMS Info&quot;
DECL|macro|UDF_ID_OS2_EA
mdefine_line|#define UDF_ID_OS2_EA&t;&t;&t;&quot;*UDF OS/2 EA&quot;
DECL|macro|UDF_ID_OS2_EA_LENGTH
mdefine_line|#define UDF_ID_OS2_EA_LENGTH&t;&t;&quot;*UDF OS/2 EALength&quot;
DECL|macro|UDF_ID_MAC_VOLUME
mdefine_line|#define UDF_ID_MAC_VOLUME&t;&t;&quot;*UDF Mac VolumeInfo&quot;
DECL|macro|UDF_ID_MAC_FINDER
mdefine_line|#define UDF_ID_MAC_FINDER&t;&t;&quot;*UDF Mac FinderInfo&quot;
DECL|macro|UDF_ID_MAC_UNIQUE
mdefine_line|#define UDF_ID_MAC_UNIQUE&t;&t;&quot;*UDF Mac UniqueIDTable&quot;
DECL|macro|UDF_ID_MAC_RESOURCE
mdefine_line|#define UDF_ID_MAC_RESOURCE&t;&t;&quot;*UDF Mac ResourceFork&quot;
DECL|macro|UDF_ID_VIRTUAL
mdefine_line|#define UDF_ID_VIRTUAL&t;&t;&t;&quot;*UDF Virtual Partition&quot;
DECL|macro|UDF_ID_SPARABLE
mdefine_line|#define UDF_ID_SPARABLE&t;&t;&t;&quot;*UDF Sparable Partition&quot;
DECL|macro|UDF_ID_ALLOC
mdefine_line|#define UDF_ID_ALLOC&t;&t;&t;&quot;*UDF Virtual Alloc Tbl&quot;
DECL|macro|UDF_ID_SPARING
mdefine_line|#define UDF_ID_SPARING&t;&t;&t;&quot;*UDF Sparing Table&quot;
multiline_comment|/* Identifier Suffix (UDF 2.01 2.1.5.3) */
DECL|macro|IS_DF_HARD_WRITE_PROTECT
mdefine_line|#define IS_DF_HARD_WRITE_PROTECT&t;0x01
DECL|macro|IS_DF_SOFT_WRITE_PROTECT
mdefine_line|#define IS_DF_SOFT_WRITE_PROTECT&t;0x02
DECL|struct|UDFIdentSuffix
r_struct
id|UDFIdentSuffix
(brace
DECL|member|UDFRevision
r_uint16
id|UDFRevision
suffix:semicolon
DECL|member|OSClass
r_uint8
id|OSClass
suffix:semicolon
DECL|member|OSIdentifier
r_uint8
id|OSIdentifier
suffix:semicolon
DECL|member|reserved
r_uint8
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|impIdentSuffix
r_struct
id|impIdentSuffix
(brace
DECL|member|OSClass
r_uint8
id|OSClass
suffix:semicolon
DECL|member|OSIdentifier
r_uint8
id|OSIdentifier
suffix:semicolon
DECL|member|reserved
r_uint8
id|reserved
(braket
l_int|6
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|appIdentSuffix
r_struct
id|appIdentSuffix
(brace
DECL|member|impUse
r_uint8
id|impUse
(braket
l_int|8
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Logical Volume Integrity Descriptor (UDF 2.01 2.2.6) */
multiline_comment|/* Implementation Use (UDF 2.01 2.2.6.4) */
DECL|struct|logicalVolIntegrityDescImpUse
r_struct
id|logicalVolIntegrityDescImpUse
(brace
DECL|member|impIdent
id|regid
id|impIdent
suffix:semicolon
DECL|member|numFiles
r_uint32
id|numFiles
suffix:semicolon
DECL|member|numDirs
r_uint32
id|numDirs
suffix:semicolon
DECL|member|minUDFReadRev
r_uint16
id|minUDFReadRev
suffix:semicolon
DECL|member|minUDFWriteRev
r_uint16
id|minUDFWriteRev
suffix:semicolon
DECL|member|maxUDFWriteRev
r_uint16
id|maxUDFWriteRev
suffix:semicolon
DECL|member|impUse
r_uint8
id|impUse
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Implementation Use Volume Descriptor (UDF 2.01 2.2.7) */
multiline_comment|/* Implementation Use (UDF 2.01 2.2.7.2) */
DECL|struct|impUseVolDescImpUse
r_struct
id|impUseVolDescImpUse
(brace
DECL|member|LVICharset
id|charspec
id|LVICharset
suffix:semicolon
DECL|member|logicalVolIdent
id|dstring
id|logicalVolIdent
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|LVInfo1
id|dstring
id|LVInfo1
(braket
l_int|36
)braket
suffix:semicolon
DECL|member|LVInfo2
id|dstring
id|LVInfo2
(braket
l_int|36
)braket
suffix:semicolon
DECL|member|LVInfo3
id|dstring
id|LVInfo3
(braket
l_int|36
)braket
suffix:semicolon
DECL|member|impIdent
id|regid
id|impIdent
suffix:semicolon
DECL|member|impUse
r_uint8
id|impUse
(braket
l_int|128
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|udfPartitionMap2
r_struct
id|udfPartitionMap2
(brace
DECL|member|partitionMapType
r_uint8
id|partitionMapType
suffix:semicolon
DECL|member|partitionMapLength
r_uint8
id|partitionMapLength
suffix:semicolon
DECL|member|reserved1
r_uint8
id|reserved1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|partIdent
id|regid
id|partIdent
suffix:semicolon
DECL|member|volSeqNum
r_uint16
id|volSeqNum
suffix:semicolon
DECL|member|partitionNum
r_uint16
id|partitionNum
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Virtual Partition Map (UDF 2.01 2.2.8) */
DECL|struct|virtualPartitionMap
r_struct
id|virtualPartitionMap
(brace
DECL|member|partitionMapType
r_uint8
id|partitionMapType
suffix:semicolon
DECL|member|partitionMapLength
r_uint8
id|partitionMapLength
suffix:semicolon
DECL|member|reserved1
r_uint8
id|reserved1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|partIdent
id|regid
id|partIdent
suffix:semicolon
DECL|member|volSeqNum
r_uint16
id|volSeqNum
suffix:semicolon
DECL|member|partitionNum
r_uint16
id|partitionNum
suffix:semicolon
DECL|member|reserved2
r_uint8
id|reserved2
(braket
l_int|24
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Sparable Partition Map (UDF 2.01 2.2.9) */
DECL|struct|sparablePartitionMap
r_struct
id|sparablePartitionMap
(brace
DECL|member|partitionMapType
r_uint8
id|partitionMapType
suffix:semicolon
DECL|member|partitionMapLength
r_uint8
id|partitionMapLength
suffix:semicolon
DECL|member|reserved1
r_uint8
id|reserved1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|partIdent
id|regid
id|partIdent
suffix:semicolon
DECL|member|volSeqNum
r_uint16
id|volSeqNum
suffix:semicolon
DECL|member|partitionNum
r_uint16
id|partitionNum
suffix:semicolon
DECL|member|packetLength
r_uint16
id|packetLength
suffix:semicolon
DECL|member|numSparingTables
r_uint8
id|numSparingTables
suffix:semicolon
DECL|member|reserved2
r_uint8
id|reserved2
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|sizeSparingTable
r_uint32
id|sizeSparingTable
suffix:semicolon
DECL|member|locSparingTable
r_uint32
id|locSparingTable
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Virtual Allocation Table (UDF 1.5 2.2.10) */
DECL|struct|virtualAllocationTable15
r_struct
id|virtualAllocationTable15
(brace
DECL|member|VirtualSector
r_uint32
id|VirtualSector
(braket
l_int|0
)braket
suffix:semicolon
DECL|member|ident
id|regid
id|ident
suffix:semicolon
DECL|member|previousVATICB
r_uint32
id|previousVATICB
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|ICBTAG_FILE_TYPE_VAT15
mdefine_line|#define ICBTAG_FILE_TYPE_VAT15&t;&t;0x00U
multiline_comment|/* Virtual Allocation Table (UDF 2.01 2.2.10) */
DECL|struct|virtualAllocationTable20
r_struct
id|virtualAllocationTable20
(brace
DECL|member|lengthHeader
r_uint16
id|lengthHeader
suffix:semicolon
DECL|member|lengthImpUse
r_uint16
id|lengthImpUse
suffix:semicolon
DECL|member|logicalVolIdent
id|dstring
id|logicalVolIdent
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|previousVatICBLoc
r_uint32
id|previousVatICBLoc
suffix:semicolon
DECL|member|numFIDSFiles
r_uint32
id|numFIDSFiles
suffix:semicolon
DECL|member|numFIDSDirectories
r_uint32
id|numFIDSDirectories
suffix:semicolon
DECL|member|minReadRevision
r_uint16
id|minReadRevision
suffix:semicolon
DECL|member|minWriteRevision
r_uint16
id|minWriteRevision
suffix:semicolon
DECL|member|maxWriteRevision
r_uint16
id|maxWriteRevision
suffix:semicolon
DECL|member|reserved
r_uint16
id|reserved
suffix:semicolon
DECL|member|impUse
r_uint8
id|impUse
(braket
l_int|0
)braket
suffix:semicolon
DECL|member|vatEntry
r_uint32
id|vatEntry
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|ICBTAG_FILE_TYPE_VAT20
mdefine_line|#define ICBTAG_FILE_TYPE_VAT20&t;&t;0xF8U
multiline_comment|/* Sparing Table (UDF 2.01 2.2.11) */
DECL|struct|sparingEntry
r_struct
id|sparingEntry
(brace
DECL|member|origLocation
r_uint32
id|origLocation
suffix:semicolon
DECL|member|mappedLocation
r_uint32
id|mappedLocation
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|sparingTable
r_struct
id|sparingTable
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|sparingIdent
id|regid
id|sparingIdent
suffix:semicolon
DECL|member|reallocationTableLen
r_uint16
id|reallocationTableLen
suffix:semicolon
DECL|member|reserved
r_uint16
id|reserved
suffix:semicolon
DECL|member|sequenceNum
r_uint32
id|sequenceNum
suffix:semicolon
r_struct
id|sparingEntry
DECL|member|mapEntry
id|mapEntry
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* struct long_ad ICB - ADImpUse (UDF 2.01 2.2.4.3) */
DECL|struct|allocDescImpUse
r_struct
id|allocDescImpUse
(brace
DECL|member|flags
r_uint16
id|flags
suffix:semicolon
DECL|member|impUse
r_uint8
id|impUse
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|AD_IU_EXT_ERASED
mdefine_line|#define AD_IU_EXT_ERASED&t;&t;0x0001
multiline_comment|/* Real-Time Files (UDF 2.01 6.11) */
DECL|macro|ICBTAG_FILE_TYPE_REALTIME
mdefine_line|#define ICBTAG_FILE_TYPE_REALTIME&t;0xF9U
multiline_comment|/* Implementation Use Extended Attribute (UDF 2.01 3.3.4.5) */
multiline_comment|/* FreeEASpace (UDF 2.01 3.3.4.5.1.1) */
DECL|struct|freeEaSpace
r_struct
id|freeEaSpace
(brace
DECL|member|headerChecksum
r_uint16
id|headerChecksum
suffix:semicolon
DECL|member|freeEASpace
r_uint8
id|freeEASpace
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* DVD Copyright Management Information (UDF 2.01 3.3.4.5.1.2) */
DECL|struct|DVDCopyrightImpUse
r_struct
id|DVDCopyrightImpUse
(brace
DECL|member|headerChecksum
r_uint16
id|headerChecksum
suffix:semicolon
DECL|member|CGMSInfo
r_uint8
id|CGMSInfo
suffix:semicolon
DECL|member|dataType
r_uint8
id|dataType
suffix:semicolon
DECL|member|protectionSystemInfo
r_uint8
id|protectionSystemInfo
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Application Use Extended Attribute (UDF 2.01 3.3.4.6) */
multiline_comment|/* FreeAppEASpace (UDF 2.01 3.3.4.6.1) */
DECL|struct|freeAppEASpace
r_struct
id|freeAppEASpace
(brace
DECL|member|headerChecksum
r_uint16
id|headerChecksum
suffix:semicolon
DECL|member|freeEASpace
r_uint8
id|freeEASpace
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* UDF Defined System Stream (UDF 2.01 3.3.7) */
DECL|macro|UDF_ID_UNIQUE_ID
mdefine_line|#define UDF_ID_UNIQUE_ID&t;&t;&quot;*UDF Unique ID Mapping Data&quot;
DECL|macro|UDF_ID_NON_ALLOC
mdefine_line|#define UDF_ID_NON_ALLOC&t;&t;&quot;*UDF Non-Allocatable Space&quot;
DECL|macro|UDF_ID_POWER_CAL
mdefine_line|#define UDF_ID_POWER_CAL&t;&t;&quot;*UDF Power Cal Table&quot;
DECL|macro|UDF_ID_BACKUP
mdefine_line|#define UDF_ID_BACKUP&t;&t;&t;&quot;*UDF Backup&quot;
multiline_comment|/* Operating System Identifiers (UDF 2.01 6.3) */
DECL|macro|UDF_OS_CLASS_UNDEF
mdefine_line|#define UDF_OS_CLASS_UNDEF&t;&t;0x00U
DECL|macro|UDF_OS_CLASS_DOS
mdefine_line|#define UDF_OS_CLASS_DOS&t;&t;0x01U
DECL|macro|UDF_OS_CLASS_OS2
mdefine_line|#define UDF_OS_CLASS_OS2&t;&t;0x02U
DECL|macro|UDF_OS_CLASS_MAC
mdefine_line|#define UDF_OS_CLASS_MAC&t;&t;0x03U
DECL|macro|UDF_OS_CLASS_UNIX
mdefine_line|#define UDF_OS_CLASS_UNIX&t;&t;0x04U
DECL|macro|UDF_OS_CLASS_WIN9X
mdefine_line|#define UDF_OS_CLASS_WIN9X&t;&t;0x05U
DECL|macro|UDF_OS_CLASS_WINNT
mdefine_line|#define UDF_OS_CLASS_WINNT&t;&t;0x06U
DECL|macro|UDF_OS_CLASS_OS400
mdefine_line|#define UDF_OS_CLASS_OS400&t;&t;0x07U
DECL|macro|UDF_OS_CLASS_BEOS
mdefine_line|#define UDF_OS_CLASS_BEOS&t;&t;0x08U
DECL|macro|UDF_OS_CLASS_WINCE
mdefine_line|#define UDF_OS_CLASS_WINCE&t;&t;0x09U
DECL|macro|UDF_OS_ID_UNDEF
mdefine_line|#define UDF_OS_ID_UNDEF&t;&t;&t;0x00U
DECL|macro|UDF_OS_ID_DOS
mdefine_line|#define UDF_OS_ID_DOS&t;&t;&t;0x00U
DECL|macro|UDF_OS_ID_OS2
mdefine_line|#define UDF_OS_ID_OS2&t;&t;&t;0x00U
DECL|macro|UDF_OS_ID_MAC
mdefine_line|#define UDF_OS_ID_MAC&t;&t;&t;0x00U
DECL|macro|UDF_OS_ID_UNIX
mdefine_line|#define UDF_OS_ID_UNIX&t;&t;&t;0x00U
DECL|macro|UDF_OS_ID_AIX
mdefine_line|#define UDF_OS_ID_AIX&t;&t;&t;0x01U
DECL|macro|UDF_OS_ID_SOLARIS
mdefine_line|#define UDF_OS_ID_SOLARIS&t;&t;0x02U
DECL|macro|UDF_OS_ID_HPUX
mdefine_line|#define UDF_OS_ID_HPUX&t;&t;&t;0x03U
DECL|macro|UDF_OS_ID_IRIX
mdefine_line|#define UDF_OS_ID_IRIX&t;&t;&t;0x04U
DECL|macro|UDF_OS_ID_LINUX
mdefine_line|#define UDF_OS_ID_LINUX&t;&t;&t;0x05U
DECL|macro|UDF_OS_ID_MKLINUX
mdefine_line|#define UDF_OS_ID_MKLINUX&t;&t;0x06U
DECL|macro|UDF_OS_ID_FREEBSD
mdefine_line|#define UDF_OS_ID_FREEBSD&t;&t;0x07U
DECL|macro|UDF_OS_ID_WIN9X
mdefine_line|#define UDF_OS_ID_WIN9X&t;&t;&t;0x00U
DECL|macro|UDF_OS_ID_WINNT
mdefine_line|#define UDF_OS_ID_WINNT&t;&t;&t;0x00U
DECL|macro|UDF_OS_ID_OS400
mdefine_line|#define UDF_OS_ID_OS400&t;&t;&t;0x00U
DECL|macro|UDF_OS_ID_BEOS
mdefine_line|#define UDF_OS_ID_BEOS&t;&t;&t;0x00U
DECL|macro|UDF_OS_ID_WINCE
mdefine_line|#define UDF_OS_ID_WINCE&t;&t;&t;0x00U
macro_line|#endif /* _OSTA_UDF_H */
eof
