macro_line|#if !defined(_LINUX_UDF_UDF_H)
DECL|macro|_LINUX_UDF_UDF_H
mdefine_line|#define _LINUX_UDF_UDF_H
multiline_comment|/*&n; * udf_udf.h&n; *&n; * PURPOSE&n; *&t;OSTA-UDF(tm) format specification [based on ECMA 167 standard].&n; *&t;http://www.osta.org/&n; *&n; * CONTACTS&n; *&t;E-mail regarding any portion of the Linux UDF file system should be&n; *&t;directed to the development team mailing list (run by majordomo):&n; *&t;&t;linux_udf@hootie.lvld.hp.com&n; *&n; * COPYRIGHT&n; *&t;This file is distributed under the terms of the GNU General Public&n; *&t;License (GPL). Copies of the GPL can be obtained from:&n; *&t;&t;ftp://prep.ai.mit.edu/pub/gnu/GPL&n; *&t;Each contributing author retains all rights to their own work.&n; *&n; * HISTORY&n; *&t;July 1, 1997 - Andrew E. Mileski&n; *&t;Written, tested, and released.&n; *&n; * 10/2/98 dgb&t;changed UDF_ID_DEVELOPER&n; * 11/26/98 bf  changed UDF_ID_DEVELOPER, &n; * 12/5/98 dgb  updated include file hierarchy, more UDF definitions&n; */
multiline_comment|/* based on ECMA 167 structure definitions */
macro_line|#include &lt;linux/udf_167.h&gt;
macro_line|#pragma pack(1)
multiline_comment|/* -------- Basic types and constants ----------- */
multiline_comment|/* UDF character set (UDF 1.50 2.1.2) */
DECL|macro|UDF_CHAR_SET_TYPE
mdefine_line|#define UDF_CHAR_SET_TYPE&t;0
DECL|macro|UDF_CHAR_SET_INFO
mdefine_line|#define UDF_CHAR_SET_INFO&t;&quot;OSTA Compressed Unicode&quot;
DECL|macro|UDF_ID_DEVELOPER
mdefine_line|#define UDF_ID_DEVELOPER&t;&quot;*Linux UDFFS&quot;
multiline_comment|/* UDF 1.02 2.2.6.4 */
DECL|struct|LogicalVolIntegrityDescImpUse
r_struct
id|LogicalVolIntegrityDescImpUse
(brace
DECL|member|impIdent
id|EntityID
id|impIdent
suffix:semicolon
DECL|member|numFiles
id|Uint32
id|numFiles
suffix:semicolon
DECL|member|numDirs
id|Uint32
id|numDirs
suffix:semicolon
DECL|member|minUDFReadRev
id|Uint16
id|minUDFReadRev
suffix:semicolon
DECL|member|minUDFWriteRev
id|Uint16
id|minUDFWriteRev
suffix:semicolon
DECL|member|maxUDFWriteRev
id|Uint16
id|maxUDFWriteRev
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* UDF 1.02 2.2.7.2 */
multiline_comment|/* LVInformation may be present in ImpUseVolDesc.impUse */
DECL|struct|ImpUseVolDescImpUse
r_struct
id|ImpUseVolDescImpUse
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
id|EntityID
id|impIdent
suffix:semicolon
DECL|member|impUse
id|Uint8
id|impUse
(braket
l_int|128
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|UdfPartitionMap2
r_struct
id|UdfPartitionMap2
(brace
DECL|member|partitionMapType
id|Uint8
id|partitionMapType
suffix:semicolon
DECL|member|partitionMapLength
id|Uint8
id|partitionMapLength
suffix:semicolon
DECL|member|reserved1
id|Uint8
id|reserved1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|partIdent
id|EntityID
id|partIdent
suffix:semicolon
DECL|member|volSeqNum
id|Uint16
id|volSeqNum
suffix:semicolon
DECL|member|partitionNum
id|Uint16
id|partitionNum
suffix:semicolon
DECL|member|reserved2
id|Uint8
id|reserved2
(braket
l_int|24
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* UDF 1.5 2.2.8 */
DECL|struct|VirtualPartitionMap
r_struct
id|VirtualPartitionMap
(brace
DECL|member|partitionMapType
id|Uint8
id|partitionMapType
suffix:semicolon
multiline_comment|/* 2 */
DECL|member|partitionMapLength
id|Uint8
id|partitionMapLength
suffix:semicolon
multiline_comment|/* 64 */
DECL|member|reserved1
id|Uint8
id|reserved1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* #00 */
DECL|member|partIdent
id|EntityID
id|partIdent
suffix:semicolon
DECL|member|volSeqNum
id|Uint16
id|volSeqNum
suffix:semicolon
DECL|member|partitionNum
id|Uint16
id|partitionNum
suffix:semicolon
DECL|member|reserved2
id|Uint8
id|reserved2
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* #00 */
)brace
suffix:semicolon
multiline_comment|/* UDF 1.5 2.2.9 */
DECL|struct|SparablePartitionMap
r_struct
id|SparablePartitionMap
(brace
DECL|member|partitionMapType
id|Uint8
id|partitionMapType
suffix:semicolon
multiline_comment|/* 2 */
DECL|member|partitionMapLength
id|Uint8
id|partitionMapLength
suffix:semicolon
multiline_comment|/* 64 */
DECL|member|reserved1
id|Uint8
id|reserved1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* #00 */
DECL|member|partIdent
id|EntityID
id|partIdent
suffix:semicolon
multiline_comment|/* Flags = 0 */
multiline_comment|/* Id = UDF_ID_SPARABLE */
multiline_comment|/* IdSuf = 2.1.5.3 */
DECL|member|volSeqNum
id|Uint16
id|volSeqNum
suffix:semicolon
DECL|member|partitionNum
id|Uint16
id|partitionNum
suffix:semicolon
DECL|member|packetLength
id|Uint16
id|packetLength
suffix:semicolon
multiline_comment|/* 32 */
DECL|member|numSparingTables
id|Uint8
id|numSparingTables
suffix:semicolon
DECL|member|reserved2
id|Uint8
id|reserved2
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* #00 */
DECL|member|sizeSparingTable
id|Uint32
id|sizeSparingTable
suffix:semicolon
DECL|member|locSparingTable
id|Uint32
id|locSparingTable
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* DVD Copyright Management Info, see UDF 1.02 3.3.4.5.1.2 */
multiline_comment|/* when ImpUseExtendedAttr.impIdent= &quot;*UDF DVD CGMS Info&quot; */
DECL|struct|DVDCopyrightImpUse
r_struct
id|DVDCopyrightImpUse
(brace
DECL|member|headerChecksum
id|Uint16
id|headerChecksum
suffix:semicolon
DECL|member|CGMSInfo
id|Uint8
id|CGMSInfo
suffix:semicolon
DECL|member|dataType
id|Uint8
id|dataType
suffix:semicolon
DECL|member|protectionSystemInfo
id|Uint8
id|protectionSystemInfo
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* the impUse of long_ad used in AllocDescs  - UDF 1.02 2.3.10.1 */
DECL|struct|ADImpUse
r_struct
id|ADImpUse
(brace
DECL|member|flags
id|Uint16
id|flags
suffix:semicolon
DECL|member|impUse
id|Uint8
id|impUse
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* UDF 1.02 2.3.10.1 */
DECL|macro|UDF_EXTENT_LENGTH_MASK
mdefine_line|#define UDF_EXTENT_LENGTH_MASK&t;&t;0x3FFFFFFF
DECL|macro|UDF_EXTENT_FLAG_MASK
mdefine_line|#define UDF_EXTENT_FLAG_MASK&t;&t;0xc0000000
DECL|macro|UDF_EXTENT_FLAG_ERASED
mdefine_line|#define UDF_EXTENT_FLAG_ERASED&t;&t;0x40000000
multiline_comment|/* &n; * Important!  VirtualAllocationTables are &n; * very different between 1.5 and 2.0!&n; */
multiline_comment|/* ----------- 1.5 ------------- */
multiline_comment|/* UDF 1.5 2.2.10 */
DECL|macro|FILE_TYPE_VAT15
mdefine_line|#define FILE_TYPE_VAT15&t;&t;0x0U
multiline_comment|/* UDF 1.5 2.2.10 - VAT layout: */
DECL|struct|VirutalAllocationTable15
r_struct
id|VirutalAllocationTable15
(brace
DECL|member|VirtualSector
id|Uint32
id|VirtualSector
(braket
l_int|0
)braket
suffix:semicolon
DECL|member|ident
id|EntityID
id|ident
suffix:semicolon
DECL|member|previousVATICB
id|Uint32
id|previousVATICB
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* where number of VirtualSector&squot;s is (VATSize-36)/4 */
multiline_comment|/* ----------- 2.0 ------------- */
multiline_comment|/* UDF 2.0 2.2.10 */
DECL|macro|FILE_TYPE_VAT20
mdefine_line|#define FILE_TYPE_VAT20&t;&t;0xf8U
multiline_comment|/* UDF 2.0 2.2.10 (different from 1.5!) */
DECL|struct|VirtualAllocationTable20
r_struct
id|VirtualAllocationTable20
(brace
DECL|member|lengthHeader
id|Uint16
id|lengthHeader
suffix:semicolon
DECL|member|lengthImpUse
id|Uint16
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
id|Uint32
id|previousVatICBLoc
suffix:semicolon
DECL|member|numFIDSFiles
id|Uint32
id|numFIDSFiles
suffix:semicolon
DECL|member|numFIDSDirectories
id|Uint32
id|numFIDSDirectories
suffix:semicolon
multiline_comment|/* non-parent */
DECL|member|minReadRevision
id|Uint16
id|minReadRevision
suffix:semicolon
DECL|member|minWriteRevision
id|Uint16
id|minWriteRevision
suffix:semicolon
DECL|member|maxWriteRevision
id|Uint16
id|maxWriteRevision
suffix:semicolon
DECL|member|reserved
id|Uint16
id|reserved
suffix:semicolon
DECL|member|impUse
id|Uint8
id|impUse
(braket
l_int|0
)braket
suffix:semicolon
DECL|member|vatEntry
id|Uint32
id|vatEntry
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Sparing maps, see UDF 1.5 2.2.11 */
r_typedef
r_struct
(brace
DECL|member|origLocation
id|Uint32
id|origLocation
suffix:semicolon
DECL|member|mappedLocation
id|Uint32
id|mappedLocation
suffix:semicolon
DECL|typedef|SparingEntry
)brace
id|SparingEntry
suffix:semicolon
multiline_comment|/* sparing maps, see UDF 2.0 2.2.11 */
DECL|struct|SparingTable
r_struct
id|SparingTable
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|sparingIdent
id|EntityID
id|sparingIdent
suffix:semicolon
multiline_comment|/* *UDF Sparing Table */
DECL|member|reallocationTableLen
id|Uint16
id|reallocationTableLen
suffix:semicolon
DECL|member|reserved
id|Uint16
id|reserved
suffix:semicolon
multiline_comment|/* #00 */
DECL|member|sequenceNum
id|Uint32
id|sequenceNum
suffix:semicolon
DECL|member|mapEntry
id|SparingEntry
id|mapEntry
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Entity Identifiers (UDF 1.50 6.1) */
DECL|macro|UDF_ID_COMPLIANT
mdefine_line|#define&t;UDF_ID_COMPLIANT&t;&quot;*OSTA UDF Compliant&quot;
DECL|macro|UDF_ID_LV_INFO
mdefine_line|#define UDF_ID_LV_INFO&t;&t;&quot;*UDF LV Info&quot;
DECL|macro|UDF_ID_FREE_EA
mdefine_line|#define UDF_ID_FREE_EA&t;&t;&quot;*UDF FreeEASpace&quot;
DECL|macro|UDF_ID_FREE_APP_EA
mdefine_line|#define UDF_ID_FREE_APP_EA&t;&quot;*UDF FreeAppEASpace&quot;
DECL|macro|UDF_ID_DVD_CGMS
mdefine_line|#define UDF_ID_DVD_CGMS&t;&t;&quot;*UDF DVD CGMS Info&quot;
DECL|macro|UDF_ID_OS2_EA
mdefine_line|#define UDF_ID_OS2_EA&t;&t;&quot;*UDF OS/2 EA&quot;
DECL|macro|UDF_ID_OS2_EA_LENGTH
mdefine_line|#define UDF_ID_OS2_EA_LENGTH&t;&quot;*UDF OS/2 EALength&quot;
DECL|macro|UDF_ID_MAC_VOLUME
mdefine_line|#define UDF_ID_MAC_VOLUME&t;&quot;*UDF Mac VolumeInfo&quot;
DECL|macro|UDF_ID_MAC_FINDER
mdefine_line|#define UDF_ID_MAC_FINDER&t;&quot;*UDF Mac FinderInfo&quot;
DECL|macro|UDF_ID_MAC_UNIQUE
mdefine_line|#define UDF_ID_MAC_UNIQUE&t;&quot;*UDF Mac UniqueIDTable&quot;
DECL|macro|UDF_ID_MAC_RESOURCE
mdefine_line|#define UDF_ID_MAC_RESOURCE&t;&quot;*UDF Mac ResourceFork&quot;
DECL|macro|UDF_ID_VIRTUAL
mdefine_line|#define UDF_ID_VIRTUAL&t;&t;&quot;*UDF Virtual Partition&quot;
DECL|macro|UDF_ID_SPARABLE
mdefine_line|#define UDF_ID_SPARABLE&t;&t;&quot;*UDF Sparable Partition&quot;
DECL|macro|UDF_ID_ALLOC
mdefine_line|#define UDF_ID_ALLOC&t;&t;&quot;*UDF Virtual Alloc Tbl&quot;
DECL|macro|UDF_ID_SPARING
mdefine_line|#define UDF_ID_SPARING&t;&t;&quot;*UDF Sparing Table&quot;
multiline_comment|/* Operating System Identifiers (UDF 1.50 6.3) */
DECL|macro|UDF_OS_CLASS_UNDEF
mdefine_line|#define UDF_OS_CLASS_UNDEF&t;0x00U
DECL|macro|UDF_OS_CLASS_DOS
mdefine_line|#define UDF_OS_CLASS_DOS&t;0x01U
DECL|macro|UDF_OS_CLASS_OS2
mdefine_line|#define UDF_OS_CLASS_OS2&t;0x02U
DECL|macro|UDF_OS_CLASS_MAC
mdefine_line|#define UDF_OS_CLASS_MAC&t;0x03U
DECL|macro|UDF_OS_CLASS_UNIX
mdefine_line|#define UDF_OS_CLASS_UNIX&t;0x04U
DECL|macro|UDF_OS_CLASS_WIN95
mdefine_line|#define UDF_OS_CLASS_WIN95&t;0x05U
DECL|macro|UDF_OS_CLASS_WINNT
mdefine_line|#define UDF_OS_CLASS_WINNT&t;0x06U
DECL|macro|UDF_OS_ID_UNDEF
mdefine_line|#define UDF_OS_ID_UNDEF&t;&t;0x00U
DECL|macro|UDF_OS_ID_DOS
mdefine_line|#define UDF_OS_ID_DOS&t;&t;0x00U
DECL|macro|UDF_OS_ID_OS2
mdefine_line|#define UDF_OS_ID_OS2&t;&t;0x00U
DECL|macro|UDF_OS_ID_MAC
mdefine_line|#define UDF_OS_ID_MAC&t;&t;0x00U
DECL|macro|UDF_OS_ID_UNIX
mdefine_line|#define UDF_OS_ID_UNIX&t;&t;0x00U
DECL|macro|UDF_OS_ID_WIN95
mdefine_line|#define UDF_OS_ID_WIN95&t;&t;0x00U
DECL|macro|UDF_OS_ID_WINNT
mdefine_line|#define UDF_OS_ID_WINNT&t;&t;0x00U
DECL|macro|UDF_OS_ID_AIX
mdefine_line|#define UDF_OS_ID_AIX&t;&t;0x01U
DECL|macro|UDF_OS_ID_SOLARIS
mdefine_line|#define UDF_OS_ID_SOLARIS&t;0x02U
DECL|macro|UDF_OS_ID_HPUX
mdefine_line|#define UDF_OS_ID_HPUX&t;&t;0x03U
DECL|macro|UDF_OS_ID_IRIX
mdefine_line|#define UDF_OS_ID_IRIX&t;&t;0x04U
DECL|macro|UDF_OS_ID_LINUX
mdefine_line|#define UDF_OS_ID_LINUX&t;&t;0x05U
DECL|macro|UDF_OS_ID_MKLINUX
mdefine_line|#define UDF_OS_ID_MKLINUX&t;0x06U
DECL|macro|UDF_OS_ID_FREEBSD
mdefine_line|#define UDF_OS_ID_FREEBSD&t;0x07U
DECL|macro|UDF_NAME_PAD
mdefine_line|#define UDF_NAME_PAD&t;4
DECL|macro|UDF_NAME_LEN
mdefine_line|#define UDF_NAME_LEN&t;255
DECL|macro|UDF_PATH_LEN
mdefine_line|#define UDF_PATH_LEN&t;1023
macro_line|#pragma pack()
macro_line|#endif /* !defined(_LINUX_UDF_FMT_H) */
eof
