macro_line|#if !defined(_LINUX_UDF_167_H)
DECL|macro|_LINUX_UDF_167_H
mdefine_line|#define _LINUX_UDF_167_H
multiline_comment|/*&n; * udf_167.h&n; *&n; * DESCRIPTION&n; *&t;Definitions from the ECMA 167 standard.&n; *&t;http://www.ecma.ch/&n; *&n; *&t;These abbreviations are used to keep the symbols short:&n; *&t;&t;Alloc&t;Allocation&n; *&t;&t;App&t;Application&n; *&t;&t;Attr&t;Attribute&n; *&t;&t;Char&t;Characters&n; *&t;&t;Desc&t;Descriptor&n; *&t;&t;Descs&t;Descriptors&n; *&t;&t;Ext&t;Extent&n; *&t;&t;Ident&t;Identifier&n; *&t;&t;Imp&t;Implementation&n; *&t;&t;Lvl&t;Level&n; *&t;&t;Max&t;Maximum&n; *&t;&t;Num&t;Number&n; *&t;&t;Ptr&t;Pointer&n; *&t;&t;Seq&t;Sequence&n; *&t;&t;Std&t;Standard&n; *&t;&t;Struct&t;Structure&n; *&t;&t;Vol&t;Volume&n; *&t;The symbols are otherwise identical to the standard, and the&n; *&t;sections of the standard to refer to are indicated.&n; *&n; * CONTACTS&n; *&t;E-mail regarding any portion of the Linux UDF file system should be&n; *&t;directed to the development team mailing list (run by majordomo):&n; *&t;&t;linux_udf@hpesjro.fc.hp.com&n; *&n; * COPYRIGHT&n; *&t;This file is distributed under the terms of the GNU General Public&n; *&t;License (GPL). Copies of the GPL can be obtained from:&n; *&t;&t;ftp://prep.ai.mit.edu/pub/gnu/GPL&n; *&t;Each contributing author retains all rights to their own work.&n; *&n; * HISTORY&n; *&t;July 12, 1997 - Andrew E. Mileski&n; *&t;Adapted from the ECMA-167 standard.&n; *&n; * 10/2/98 dgb&t;Adaptation&n; * 10/4/98 &t;Changes by HJA Sandkuyl&n; * 10/7/98&t;Changed FILE_EXISTENCE to FILE_HIDDEN, per UDF 2.0 spec&n; * 11/26/98&t;Modifed some entries for UDF 1.5/2.0&n; * 11/26/98 bf  Fixed typos, non-linux types, more structures&n; * 12/5/98 dgb  Adjusted structure and content of include files.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|Uint8
mdefine_line|#define Uint8&t;__u8
DECL|macro|Sint8
mdefine_line|#define Sint8&t;__s8
DECL|macro|Uint16
mdefine_line|#define Uint16&t;__u16
DECL|macro|Sint16
mdefine_line|#define Sint16&t;__s16
DECL|macro|Uint32
mdefine_line|#define Uint32&t;__u32
DECL|macro|Sint32
mdefine_line|#define Sint32&t;__s32
DECL|macro|Uint64
mdefine_line|#define Uint64&t;__u64
DECL|macro|Sint64
mdefine_line|#define Sint64&t;__s64
DECL|typedef|dstring
r_typedef
id|Uint8
id|dstring
suffix:semicolon
macro_line|#else
DECL|macro|Uint8
mdefine_line|#define Uint8&t;unsigned char
DECL|macro|Sint8
mdefine_line|#define Sint8&t;char
DECL|macro|Uint16
mdefine_line|#define Uint16&t;unsigned short
DECL|macro|Sint16
mdefine_line|#define Sint16&t;short
DECL|macro|Uint32
mdefine_line|#define Uint32&t;unsigned int
DECL|macro|Sint32
mdefine_line|#define Sint32&t;int
DECL|macro|Uint64
mdefine_line|#define Uint64&t;unsigned long long
DECL|macro|Sint64
mdefine_line|#define Sint64&t;long long
DECL|typedef|dstring
r_typedef
id|Uint8
id|dstring
suffix:semicolon
macro_line|#endif
multiline_comment|/* make sure all structures are packed! */
macro_line|#pragma pack(1)
multiline_comment|/* CS0 Charspec (ECMA 167 1/7.2.1) */
r_typedef
r_struct
(brace
DECL|member|charSetType
id|Uint8
id|charSetType
suffix:semicolon
DECL|member|charSetInfo
id|Uint8
id|charSetInfo
(braket
l_int|63
)braket
suffix:semicolon
DECL|typedef|charspec
)brace
id|charspec
suffix:semicolon
multiline_comment|/* Timestamp (ECMA 167 1/7.3) */
r_typedef
r_struct
(brace
DECL|member|typeAndTimezone
id|Uint16
id|typeAndTimezone
suffix:semicolon
DECL|member|year
id|Uint16
id|year
suffix:semicolon
DECL|member|month
id|Uint8
id|month
suffix:semicolon
DECL|member|day
id|Uint8
id|day
suffix:semicolon
DECL|member|hour
id|Uint8
id|hour
suffix:semicolon
DECL|member|minute
id|Uint8
id|minute
suffix:semicolon
DECL|member|second
id|Uint8
id|second
suffix:semicolon
DECL|member|centiseconds
id|Uint8
id|centiseconds
suffix:semicolon
DECL|member|hundredsOfMicroseconds
id|Uint8
id|hundredsOfMicroseconds
suffix:semicolon
DECL|member|microseconds
id|Uint8
id|microseconds
suffix:semicolon
DECL|typedef|timestamp
)brace
id|timestamp
suffix:semicolon
multiline_comment|/* Timestamp types (ECMA 167 1/7.3.1) */
DECL|macro|TIMESTAMP_TYPE_CUT
mdefine_line|#define TIMESTAMP_TYPE_CUT&t;&t;0x0000U
DECL|macro|TIMESTAMP_TYPE_LOCAL
mdefine_line|#define TIMESTAMP_TYPE_LOCAL&t;&t;0x0001U
DECL|macro|TIMESTAMP_TYPE_AGREEMENT
mdefine_line|#define TIMESTAMP_TYPE_AGREEMENT&t;0x0002U
multiline_comment|/* Entity Identifier (ECMA 167 1/7.4) */
r_typedef
r_struct
(brace
DECL|member|flags
id|Uint8
id|flags
suffix:semicolon
DECL|member|ident
id|Uint8
id|ident
(braket
l_int|23
)braket
suffix:semicolon
DECL|member|identSuffix
id|Uint8
id|identSuffix
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|EntityID
)brace
id|EntityID
suffix:semicolon
DECL|macro|regid
mdefine_line|#define regid EntityID
multiline_comment|/* Entity identifier flags (ECMA 167 1/7.4.1) */
DECL|macro|ENTITYID_FLAGS_DIRTY
mdefine_line|#define ENTITYID_FLAGS_DIRTY&t;&t;0x01U
DECL|macro|ENTITYID_FLAGS_PROTECTED
mdefine_line|#define ENTITYID_FLAGS_PROTECTED&t;0x02U
multiline_comment|/* Volume Structure Descriptor (ECMA 167 2/9.1) */
DECL|macro|STD_ID_LEN
mdefine_line|#define STD_ID_LEN&t;5
DECL|struct|VolStructDesc
r_struct
id|VolStructDesc
(brace
DECL|member|structType
id|Uint8
id|structType
suffix:semicolon
DECL|member|stdIdent
id|Uint8
id|stdIdent
(braket
id|STD_ID_LEN
)braket
suffix:semicolon
DECL|member|structVersion
id|Uint8
id|structVersion
suffix:semicolon
DECL|member|structData
id|Uint8
id|structData
(braket
l_int|2041
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Std structure identifiers (ECMA 167 2/9.1.2) */
DECL|macro|STD_ID_BEA01
mdefine_line|#define STD_ID_BEA01&t;&quot;BEA01&quot;
DECL|macro|STD_ID_BOOT2
mdefine_line|#define STD_ID_BOOT2&t;&quot;BOOT2&quot;
DECL|macro|STD_ID_CD001
mdefine_line|#define STD_ID_CD001&t;&quot;CD001&quot;
DECL|macro|STD_ID_CDW02
mdefine_line|#define STD_ID_CDW02&t;&quot;CDW02&quot;
DECL|macro|STD_ID_NSR02
mdefine_line|#define STD_ID_NSR02&t;&quot;NSR02&quot;
DECL|macro|STD_ID_NSR03
mdefine_line|#define STD_ID_NSR03&t;&quot;NSR03&quot;
DECL|macro|STD_ID_TEA01
mdefine_line|#define STD_ID_TEA01&t;&quot;TEA01&quot;
multiline_comment|/* Beginning Extended Area Descriptor (ECMA 167 2/9.2) */
DECL|struct|BeginningExtendedAreaDesc
r_struct
id|BeginningExtendedAreaDesc
(brace
DECL|member|structType
id|Uint8
id|structType
suffix:semicolon
DECL|member|stdIdent
id|Uint8
id|stdIdent
(braket
id|STD_ID_LEN
)braket
suffix:semicolon
DECL|member|structVersion
id|Uint8
id|structVersion
suffix:semicolon
DECL|member|structData
id|Uint8
id|structData
(braket
l_int|2041
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Terminating Extended Area Descriptor (ECMA 167 2/9.3) */
DECL|struct|TerminatingExtendedAreaDesc
r_struct
id|TerminatingExtendedAreaDesc
(brace
DECL|member|structType
id|Uint8
id|structType
suffix:semicolon
DECL|member|stdIdent
id|Uint8
id|stdIdent
(braket
id|STD_ID_LEN
)braket
suffix:semicolon
DECL|member|structVersion
id|Uint8
id|structVersion
suffix:semicolon
DECL|member|structData
id|Uint8
id|structData
(braket
l_int|2041
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Boot Descriptor (ECMA 167 2/9.4) */
DECL|struct|BootDesc
r_struct
id|BootDesc
(brace
DECL|member|structType
id|Uint8
id|structType
suffix:semicolon
DECL|member|stdIdent
id|Uint8
id|stdIdent
(braket
id|STD_ID_LEN
)braket
suffix:semicolon
DECL|member|structVersion
id|Uint8
id|structVersion
suffix:semicolon
DECL|member|reserved1
id|Uint8
id|reserved1
suffix:semicolon
DECL|member|architectureType
id|EntityID
id|architectureType
suffix:semicolon
DECL|member|bootIdent
id|EntityID
id|bootIdent
suffix:semicolon
DECL|member|bootExtLocation
id|Uint32
id|bootExtLocation
suffix:semicolon
DECL|member|bootExtLength
id|Uint32
id|bootExtLength
suffix:semicolon
DECL|member|loadAddress
id|Uint64
id|loadAddress
suffix:semicolon
DECL|member|startAddress
id|Uint64
id|startAddress
suffix:semicolon
DECL|member|descCreationDateAndTime
id|timestamp
id|descCreationDateAndTime
suffix:semicolon
DECL|member|flags
id|Uint16
id|flags
suffix:semicolon
DECL|member|reserved2
id|Uint8
id|reserved2
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|bootUse
id|Uint8
id|bootUse
(braket
l_int|1906
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Boot flags (ECMA 167 2/9.4.12) */
DECL|macro|BOOT_FLAGS_ERASE
mdefine_line|#define BOOT_FLAGS_ERASE&t;1
multiline_comment|/* Extent Descriptor (ECMA 167 3/7.1) */
r_typedef
r_struct
(brace
DECL|member|extLength
id|Uint32
id|extLength
suffix:semicolon
DECL|member|extLocation
id|Uint32
id|extLocation
suffix:semicolon
DECL|typedef|extent_ad
)brace
id|extent_ad
suffix:semicolon
multiline_comment|/* Descriptor Tag (ECMA 167 3/7.2) */
r_typedef
r_struct
(brace
DECL|member|tagIdent
id|Uint16
id|tagIdent
suffix:semicolon
DECL|member|descVersion
id|Uint16
id|descVersion
suffix:semicolon
DECL|member|tagChecksum
id|Uint8
id|tagChecksum
suffix:semicolon
DECL|member|reserved
id|Uint8
id|reserved
suffix:semicolon
DECL|member|tagSerialNum
id|Uint16
id|tagSerialNum
suffix:semicolon
DECL|member|descCRC
id|Uint16
id|descCRC
suffix:semicolon
DECL|member|descCRCLength
id|Uint16
id|descCRCLength
suffix:semicolon
DECL|member|tagLocation
id|Uint32
id|tagLocation
suffix:semicolon
DECL|typedef|tag
)brace
id|tag
suffix:semicolon
multiline_comment|/* Tag Identifiers (ECMA 167 3/7.2.1) */
DECL|macro|TID_UNUSED_DESC
mdefine_line|#define TID_UNUSED_DESC&t;&t;&t;0x0000U
DECL|macro|TID_PRIMARY_VOL_DESC
mdefine_line|#define TID_PRIMARY_VOL_DESC&t;&t;0x0001U
DECL|macro|TID_ANCHOR_VOL_DESC_PTR
mdefine_line|#define TID_ANCHOR_VOL_DESC_PTR&t;&t;0x0002U
DECL|macro|TID_VOL_DESC_PTR
mdefine_line|#define TID_VOL_DESC_PTR&t;&t;0x0003U
DECL|macro|TID_IMP_USE_VOL_DESC
mdefine_line|#define TID_IMP_USE_VOL_DESC&t;&t;0x0004U
DECL|macro|TID_PARTITION_DESC
mdefine_line|#define TID_PARTITION_DESC&t;&t;0x0005U
DECL|macro|TID_LOGICAL_VOL_DESC
mdefine_line|#define TID_LOGICAL_VOL_DESC&t;&t;0x0006U
DECL|macro|TID_UNALLOC_SPACE_DESC
mdefine_line|#define TID_UNALLOC_SPACE_DESC&t;&t;0x0007U
DECL|macro|TID_TERMINATING_DESC
mdefine_line|#define TID_TERMINATING_DESC&t;&t;0x0008U
DECL|macro|TID_LOGICAL_VOL_INTEGRITY_DESC
mdefine_line|#define TID_LOGICAL_VOL_INTEGRITY_DESC&t;0x0009U
multiline_comment|/* Tag Identifiers (ECMA 167 4/7.2.1) */
DECL|macro|TID_FILE_SET_DESC
mdefine_line|#define TID_FILE_SET_DESC&t;&t;0x0100U
DECL|macro|TID_FILE_IDENT_DESC
mdefine_line|#define TID_FILE_IDENT_DESC&t;&t;0x0101U
DECL|macro|TID_ALLOC_EXTENT_DESC
mdefine_line|#define TID_ALLOC_EXTENT_DESC&t;&t;0x0102U
DECL|macro|TID_INDIRECT_ENTRY
mdefine_line|#define TID_INDIRECT_ENTRY&t;&t;0x0103U
DECL|macro|TID_TERMINAL_ENTRY
mdefine_line|#define TID_TERMINAL_ENTRY&t;&t;0x0104U
DECL|macro|TID_FILE_ENTRY
mdefine_line|#define TID_FILE_ENTRY&t;&t;&t;0x0105U
DECL|macro|TID_EXTENDED_ATTRE_HEADER_DESC
mdefine_line|#define TID_EXTENDED_ATTRE_HEADER_DESC&t;0x0106U
DECL|macro|TID_UNALLOCATED_SPACE_ENTRY
mdefine_line|#define TID_UNALLOCATED_SPACE_ENTRY&t;0x0107U
DECL|macro|TID_SPACE_BITMAP_DESC
mdefine_line|#define TID_SPACE_BITMAP_DESC&t;&t;0x0108U
DECL|macro|TID_PARTITION_INTEGRITY_ENTRY
mdefine_line|#define TID_PARTITION_INTEGRITY_ENTRY&t;0x0109U
DECL|macro|TID_EXTENDED_FILE_ENTRY
mdefine_line|#define TID_EXTENDED_FILE_ENTRY&t;&t;0x010AU
multiline_comment|/* NSR Descriptor (ECMA 167 3/9.1) */
DECL|struct|NSRDesc
r_struct
id|NSRDesc
(brace
DECL|member|structType
id|Uint8
id|structType
suffix:semicolon
DECL|member|stdIdent
id|Uint8
id|stdIdent
(braket
id|STD_ID_LEN
)braket
suffix:semicolon
DECL|member|structVersion
id|Uint8
id|structVersion
suffix:semicolon
DECL|member|reserved
id|Uint8
id|reserved
suffix:semicolon
DECL|member|structData
id|Uint8
id|structData
(braket
l_int|2040
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Primary Volume Descriptor (ECMA 167 3/10.1) */
DECL|struct|PrimaryVolDesc
r_struct
id|PrimaryVolDesc
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|volDescSeqNum
id|Uint32
id|volDescSeqNum
suffix:semicolon
DECL|member|primaryVolDescNum
id|Uint32
id|primaryVolDescNum
suffix:semicolon
DECL|member|volIdent
id|dstring
id|volIdent
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|volSeqNum
id|Uint16
id|volSeqNum
suffix:semicolon
DECL|member|maxVolSeqNum
id|Uint16
id|maxVolSeqNum
suffix:semicolon
DECL|member|interchangeLvl
id|Uint16
id|interchangeLvl
suffix:semicolon
DECL|member|maxInterchangeLvl
id|Uint16
id|maxInterchangeLvl
suffix:semicolon
DECL|member|charSetList
id|Uint32
id|charSetList
suffix:semicolon
DECL|member|maxCharSetList
id|Uint32
id|maxCharSetList
suffix:semicolon
DECL|member|volSetIdent
id|dstring
id|volSetIdent
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|descCharSet
id|charspec
id|descCharSet
suffix:semicolon
DECL|member|explanatoryCharSet
id|charspec
id|explanatoryCharSet
suffix:semicolon
DECL|member|volAbstract
id|extent_ad
id|volAbstract
suffix:semicolon
DECL|member|volCopyright
id|extent_ad
id|volCopyright
suffix:semicolon
DECL|member|appIdent
id|EntityID
id|appIdent
suffix:semicolon
DECL|member|recordingDateAndTime
id|timestamp
id|recordingDateAndTime
suffix:semicolon
DECL|member|impIdent
id|EntityID
id|impIdent
suffix:semicolon
DECL|member|impUse
id|Uint8
id|impUse
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|predecessorVolDescSeqLocation
id|Uint32
id|predecessorVolDescSeqLocation
suffix:semicolon
DECL|member|flags
id|Uint16
id|flags
suffix:semicolon
DECL|member|reserved
id|Uint8
id|reserved
(braket
l_int|22
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Primary volume descriptor flags (ECMA 167 3/10.1.21) */
DECL|macro|VOL_SET_IDENT
mdefine_line|#define VOL_SET_IDENT&t;1
multiline_comment|/* Anchor Volume Descriptor Pointer (ECMA 167 3/10.2) */
DECL|struct|AnchorVolDescPtr
r_struct
id|AnchorVolDescPtr
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|mainVolDescSeqExt
id|extent_ad
id|mainVolDescSeqExt
suffix:semicolon
DECL|member|reserveVolDescSeqExt
id|extent_ad
id|reserveVolDescSeqExt
suffix:semicolon
DECL|member|reserved
id|Uint8
id|reserved
(braket
l_int|480
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Volume Descriptor Pointer (ECMA 167 3/10.3) */
DECL|struct|VolDescPtr
r_struct
id|VolDescPtr
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|volDescSeqNum
id|Uint32
id|volDescSeqNum
suffix:semicolon
DECL|member|nextVolDescSeqExt
id|extent_ad
id|nextVolDescSeqExt
suffix:semicolon
DECL|member|reserved
id|Uint8
id|reserved
(braket
l_int|484
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Implementation Use Volume Descriptor (ECMA 167 3/10.4) */
DECL|struct|ImpUseVolDesc
r_struct
id|ImpUseVolDesc
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|volDescSeqNum
id|Uint32
id|volDescSeqNum
suffix:semicolon
DECL|member|impIdent
id|EntityID
id|impIdent
suffix:semicolon
DECL|member|impUse
id|Uint8
id|impUse
(braket
l_int|460
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Partition Descriptor (ECMA 167 3/10.5) */
DECL|struct|PartitionDesc
r_struct
id|PartitionDesc
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|volDescSeqNum
id|Uint32
id|volDescSeqNum
suffix:semicolon
DECL|member|partitionFlags
id|Uint16
id|partitionFlags
suffix:semicolon
DECL|member|partitionNumber
id|Uint16
id|partitionNumber
suffix:semicolon
DECL|member|partitionContents
id|EntityID
id|partitionContents
suffix:semicolon
DECL|member|partitionContentsUse
id|Uint8
id|partitionContentsUse
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|accessType
id|Uint32
id|accessType
suffix:semicolon
DECL|member|partitionStartingLocation
id|Uint32
id|partitionStartingLocation
suffix:semicolon
DECL|member|partitionLength
id|Uint32
id|partitionLength
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
DECL|member|reserved
id|Uint8
id|reserved
(braket
l_int|156
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Partition Flags (ECMA 167 3/10.5.3) */
DECL|macro|PARTITION_FLAGS_ALLOC
mdefine_line|#define PARTITION_FLAGS_ALLOC&t;1
multiline_comment|/* Partition Contents (ECMA 167 3/10.5.5) */
DECL|macro|PARTITION_CONTENTS_FDC01
mdefine_line|#define PARTITION_CONTENTS_FDC01&t;&quot;+FDC01&quot;
DECL|macro|PARTITION_CONTENTS_CD001
mdefine_line|#define PARTITION_CONTENTS_CD001&t;&quot;+CD001&quot;
DECL|macro|PARTITION_CONTENTS_CDW02
mdefine_line|#define PARTITION_CONTENTS_CDW02&t;&quot;+CDW02&quot;
DECL|macro|PARTITION_CONTENTS_NSR02
mdefine_line|#define PARTITION_CONTENTS_NSR02&t;&quot;+NSR02&quot;
DECL|macro|PARTITION_CONTENTS_NSR03
mdefine_line|#define PARTITION_CONTENTS_NSR03&t;&quot;+NSR03&quot;
multiline_comment|/* Partition Access Types (ECMA 167 3/10.5.7) */
DECL|macro|PARTITION_ACCESS_NONE
mdefine_line|#define PARTITION_ACCESS_NONE&t;0
DECL|macro|PARTITION_ACCESS_R
mdefine_line|#define PARTITION_ACCESS_R&t;1
DECL|macro|PARTITION_ACCESS_WO
mdefine_line|#define PARTITION_ACCESS_WO&t;2
DECL|macro|PARTITION_ACCESS_RW
mdefine_line|#define PARTITION_ACCESS_RW&t;3
DECL|macro|PARTITION_ACCESS_OW
mdefine_line|#define PARTITION_ACCESS_OW&t;4
multiline_comment|/* Logical Volume Descriptor (ECMA 167 3/10.6) */
DECL|struct|LogicalVolDesc
r_struct
id|LogicalVolDesc
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|volDescSeqNum
id|Uint32
id|volDescSeqNum
suffix:semicolon
DECL|member|descCharSet
id|charspec
id|descCharSet
suffix:semicolon
DECL|member|logicalVolIdent
id|dstring
id|logicalVolIdent
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|logicalBlockSize
id|Uint32
id|logicalBlockSize
suffix:semicolon
DECL|member|domainIdent
id|EntityID
id|domainIdent
suffix:semicolon
DECL|member|logicalVolContentsUse
id|Uint8
id|logicalVolContentsUse
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* used to find fileset */
DECL|member|mapTableLength
id|Uint32
id|mapTableLength
suffix:semicolon
DECL|member|numPartitionMaps
id|Uint32
id|numPartitionMaps
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
DECL|member|integritySeqExt
id|extent_ad
id|integritySeqExt
suffix:semicolon
DECL|member|partitionMaps
id|Uint8
id|partitionMaps
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Generic Partition Map (ECMA 167 3/10.7.1) */
DECL|struct|GenericPartitionMap
r_struct
id|GenericPartitionMap
(brace
DECL|member|partitionMapType
id|Uint8
id|partitionMapType
suffix:semicolon
DECL|member|partitionMapLength
id|Uint8
id|partitionMapLength
suffix:semicolon
DECL|member|partitionMapping
id|Uint8
id|partitionMapping
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Partition Map Type (ECMA 167 3/10.7.1.1) */
DECL|macro|PARTITION_MAP_TYPE_NONE
mdefine_line|#define PARTITION_MAP_TYPE_NONE&t;&t;0
DECL|macro|PARTITION_MAP_TYPE_1
mdefine_line|#define PARTITION_MAP_TYPE_1&t;&t;1
DECL|macro|PARTITION_MAP_TYPE_2
mdefine_line|#define PARTITION_MAP_TYPE_2&t;&t;2
multiline_comment|/* Type 1 Partition Map (ECMA 167 3/10.7.2) */
DECL|struct|GenericPartitionMap1
r_struct
id|GenericPartitionMap1
(brace
DECL|member|partitionMapType
id|Uint8
id|partitionMapType
suffix:semicolon
DECL|member|partitionMapLength
id|Uint8
id|partitionMapLength
suffix:semicolon
DECL|member|volSeqNum
id|Uint16
id|volSeqNum
suffix:semicolon
DECL|member|partitionNum
id|Uint16
id|partitionNum
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Type 2 Partition Map (ECMA 167 3/10.7.3) */
DECL|struct|GenericPartitionMap2
r_struct
id|GenericPartitionMap2
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
DECL|member|partitionIdent
id|Uint8
id|partitionIdent
(braket
l_int|62
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Unallocated Space Descriptor (ECMA 167 3/10.8) */
DECL|struct|UnallocatedSpaceDesc
r_struct
id|UnallocatedSpaceDesc
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|volDescSeqNum
id|Uint32
id|volDescSeqNum
suffix:semicolon
DECL|member|numAllocDescs
id|Uint32
id|numAllocDescs
suffix:semicolon
DECL|member|allocDescs
id|extent_ad
id|allocDescs
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Terminating Descriptor (ECMA 3/10.9) */
DECL|struct|TerminatingDesc
r_struct
id|TerminatingDesc
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|reserved
id|Uint8
id|reserved
(braket
l_int|496
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|GenericDesc
r_struct
id|GenericDesc
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|volDescSeqNum
id|Uint32
id|volDescSeqNum
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Logical Volume Integrity Descriptor (ECMA 167 3/10.10) */
DECL|struct|LogicalVolIntegrityDesc
r_struct
id|LogicalVolIntegrityDesc
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|recordingDateAndTime
id|timestamp
id|recordingDateAndTime
suffix:semicolon
DECL|member|integrityType
id|Uint32
id|integrityType
suffix:semicolon
DECL|member|nextIntegrityExt
id|extent_ad
id|nextIntegrityExt
suffix:semicolon
DECL|member|logicalVolContentsUse
id|Uint8
id|logicalVolContentsUse
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|numOfPartitions
id|Uint32
id|numOfPartitions
suffix:semicolon
DECL|member|lengthOfImpUse
id|Uint32
id|lengthOfImpUse
suffix:semicolon
DECL|member|freeSpaceTable
id|Uint32
id|freeSpaceTable
(braket
l_int|0
)braket
suffix:semicolon
DECL|member|sizeTable
id|Uint32
id|sizeTable
(braket
l_int|0
)braket
suffix:semicolon
DECL|member|impUse
id|Uint8
id|impUse
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Integrity Types (ECMA 167 3/10.10.3) */
DECL|macro|INTEGRITY_TYPE_OPEN
mdefine_line|#define INTEGRITY_TYPE_OPEN&t;0
DECL|macro|INTEGRITY_TYPE_CLOSE
mdefine_line|#define INTEGRITY_TYPE_CLOSE&t;1
multiline_comment|/* Recorded Address (ECMA 167 4/7.1) */
r_typedef
r_struct
(brace
DECL|member|logicalBlockNum
id|Uint32
id|logicalBlockNum
suffix:semicolon
DECL|member|partitionReferenceNum
id|Uint16
id|partitionReferenceNum
suffix:semicolon
DECL|typedef|lb_addr
)brace
id|lb_addr
suffix:semicolon
multiline_comment|/* Extent interpretation (ECMA 167 4/14.14.1.1) */
DECL|macro|EXTENT_RECORDED_ALLOCATED
mdefine_line|#define EXTENT_RECORDED_ALLOCATED               0x00
DECL|macro|EXTENT_NOT_RECORDED_ALLOCATED
mdefine_line|#define EXTENT_NOT_RECORDED_ALLOCATED           0x01
DECL|macro|EXTENT_NOT_RECORDED_NOT_ALLOCATED
mdefine_line|#define EXTENT_NOT_RECORDED_NOT_ALLOCATED       0x02
DECL|macro|EXTENT_NEXT_EXTENT_ALLOCDECS
mdefine_line|#define EXTENT_NEXT_EXTENT_ALLOCDECS            0x03
multiline_comment|/* Long Allocation Descriptor (ECMA 167 4/14.14.2) */
r_typedef
r_struct
(brace
DECL|member|extLength
id|Uint32
id|extLength
suffix:semicolon
DECL|member|extLocation
id|lb_addr
id|extLocation
suffix:semicolon
DECL|member|impUse
id|Uint8
id|impUse
(braket
l_int|6
)braket
suffix:semicolon
DECL|typedef|long_ad
)brace
id|long_ad
suffix:semicolon
multiline_comment|/* upper 2 bits of extLength indicate type */
multiline_comment|/* File Set Descriptor (ECMA 167 4/14.1) */
DECL|struct|FileSetDesc
r_struct
id|FileSetDesc
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|recordingDateAndTime
id|timestamp
id|recordingDateAndTime
suffix:semicolon
DECL|member|interchangeLvl
id|Uint16
id|interchangeLvl
suffix:semicolon
DECL|member|maxInterchangeLvl
id|Uint16
id|maxInterchangeLvl
suffix:semicolon
DECL|member|charSetList
id|Uint32
id|charSetList
suffix:semicolon
DECL|member|maxCharSetList
id|Uint32
id|maxCharSetList
suffix:semicolon
DECL|member|fileSetNum
id|Uint32
id|fileSetNum
suffix:semicolon
DECL|member|fileSetDescNum
id|Uint32
id|fileSetDescNum
suffix:semicolon
DECL|member|logicalVolIdentCharSet
id|charspec
id|logicalVolIdentCharSet
suffix:semicolon
DECL|member|logicalVolIdent
id|dstring
id|logicalVolIdent
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|fileSetCharSet
id|charspec
id|fileSetCharSet
suffix:semicolon
DECL|member|fileSetIdent
id|dstring
id|fileSetIdent
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|copyrightFileIdent
id|dstring
id|copyrightFileIdent
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|abstractFileIdent
id|dstring
id|abstractFileIdent
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|rootDirectoryICB
id|long_ad
id|rootDirectoryICB
suffix:semicolon
DECL|member|domainIdent
id|EntityID
id|domainIdent
suffix:semicolon
DECL|member|nextExt
id|long_ad
id|nextExt
suffix:semicolon
DECL|member|streamDirectoryICB
id|long_ad
id|streamDirectoryICB
suffix:semicolon
DECL|member|reserved
id|Uint8
id|reserved
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Short Allocation Descriptor (ECMA 167 4/14.14.1) */
r_typedef
r_struct
(brace
DECL|member|extLength
id|Uint32
id|extLength
suffix:semicolon
DECL|member|extPosition
id|Uint32
id|extPosition
suffix:semicolon
DECL|typedef|short_ad
)brace
id|short_ad
suffix:semicolon
multiline_comment|/* Partition Header Descriptor (ECMA 167 4/14.3) */
DECL|struct|PartitionHeaderDesc
r_struct
id|PartitionHeaderDesc
(brace
DECL|member|unallocatedSpaceTable
id|short_ad
id|unallocatedSpaceTable
suffix:semicolon
DECL|member|unallocatedSpaceBitmap
id|short_ad
id|unallocatedSpaceBitmap
suffix:semicolon
DECL|member|partitionIntegrityTable
id|short_ad
id|partitionIntegrityTable
suffix:semicolon
DECL|member|freedSpaceTable
id|short_ad
id|freedSpaceTable
suffix:semicolon
DECL|member|freedSpaceBitmap
id|short_ad
id|freedSpaceBitmap
suffix:semicolon
DECL|member|reserved
id|Uint8
id|reserved
(braket
l_int|88
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* File Identifier Descriptor (ECMA 167 4/14.4) */
DECL|struct|FileIdentDesc
r_struct
id|FileIdentDesc
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|fileVersionNum
id|Uint16
id|fileVersionNum
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|fileCharacteristics
id|Uint8
id|fileCharacteristics
suffix:semicolon
DECL|member|lengthFileIdent
id|Uint8
id|lengthFileIdent
suffix:semicolon
DECL|member|icb
id|long_ad
id|icb
suffix:semicolon
DECL|member|lengthOfImpUse
id|Uint16
id|lengthOfImpUse
suffix:semicolon
DECL|member|impUse
id|Uint8
id|impUse
(braket
l_int|0
)braket
suffix:semicolon
DECL|member|fileIdent
id|Uint8
id|fileIdent
(braket
l_int|0
)braket
suffix:semicolon
DECL|member|padding
id|Uint8
id|padding
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* File Characteristics (ECMA 167 4/14.4.3) */
DECL|macro|FILE_HIDDEN
mdefine_line|#define FILE_HIDDEN&t;1
DECL|macro|FILE_DIRECTORY
mdefine_line|#define FILE_DIRECTORY&t;2
DECL|macro|FILE_DELETED
mdefine_line|#define FILE_DELETED&t;4
DECL|macro|FILE_PARENT
mdefine_line|#define FILE_PARENT&t;8
DECL|macro|FILE_METADATA
mdefine_line|#define FILE_METADATA&t;0x10 /* UDF 2.0 */
multiline_comment|/* Allocation Ext Descriptor (ECMA 167 4/14.5) */
DECL|struct|AllocExtDesc
r_struct
id|AllocExtDesc
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|previousAllocExtLocation
id|Uint32
id|previousAllocExtLocation
suffix:semicolon
DECL|member|lengthAllocDescs
id|Uint32
id|lengthAllocDescs
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ICB Tag (ECMA 167 4/14.6) */
r_typedef
r_struct
(brace
DECL|member|priorRecordedNumDirectEntries
id|Uint32
id|priorRecordedNumDirectEntries
suffix:semicolon
DECL|member|strategyType
id|Uint16
id|strategyType
suffix:semicolon
DECL|member|strategyParameter
id|Uint16
id|strategyParameter
suffix:semicolon
DECL|member|numEntries
id|Uint16
id|numEntries
suffix:semicolon
DECL|member|reserved
id|Uint8
id|reserved
suffix:semicolon
DECL|member|fileType
id|Uint8
id|fileType
suffix:semicolon
DECL|member|parentICBLocation
id|lb_addr
id|parentICBLocation
suffix:semicolon
DECL|member|flags
id|Uint16
id|flags
suffix:semicolon
DECL|typedef|icbtag
)brace
id|icbtag
suffix:semicolon
multiline_comment|/* ICB File Type (ECMA 167 4/14.6.6) */
DECL|macro|FILE_TYPE_NONE
mdefine_line|#define FILE_TYPE_NONE&t;&t;0x00U
DECL|macro|FILE_TYPE_UNALLOC
mdefine_line|#define FILE_TYPE_UNALLOC&t;0x01U
DECL|macro|FILE_TYPE_INTEGRITY
mdefine_line|#define FILE_TYPE_INTEGRITY&t;0x02U
DECL|macro|FILE_TYPE_INDIRECT
mdefine_line|#define FILE_TYPE_INDIRECT&t;0x03U
DECL|macro|FILE_TYPE_DIRECTORY
mdefine_line|#define FILE_TYPE_DIRECTORY&t;0x04U
DECL|macro|FILE_TYPE_REGULAR
mdefine_line|#define FILE_TYPE_REGULAR&t;0x05U
DECL|macro|FILE_TYPE_BLOCK
mdefine_line|#define FILE_TYPE_BLOCK&t;&t;0x06U
DECL|macro|FILE_TYPE_CHAR
mdefine_line|#define FILE_TYPE_CHAR&t;&t;0x07U
DECL|macro|FILE_TYPE_EXTENDED
mdefine_line|#define FILE_TYPE_EXTENDED&t;0x08U
DECL|macro|FILE_TYPE_FIFO
mdefine_line|#define FILE_TYPE_FIFO&t;&t;0x09U
DECL|macro|FILE_TYPE_SOCKET
mdefine_line|#define FILE_TYPE_SOCKET&t;0x0aU
DECL|macro|FILE_TYPE_TERMINAL
mdefine_line|#define FILE_TYPE_TERMINAL&t;0x0bU
DECL|macro|FILE_TYPE_SYMLINK
mdefine_line|#define FILE_TYPE_SYMLINK&t;0x0cU
DECL|macro|FILE_TYPE_STREAMDIR
mdefine_line|#define FILE_TYPE_STREAMDIR&t;0x0dU /* ECMA 167 4/13 */
multiline_comment|/* ICB Flags (ECMA 167 4/14.6.8) */
DECL|macro|ICB_FLAG_ALLOC_MASK
mdefine_line|#define ICB_FLAG_ALLOC_MASK&t;0x0007U
DECL|macro|ICB_FLAG_SORTED
mdefine_line|#define ICB_FLAG_SORTED&t;&t;0x0008U
DECL|macro|ICB_FLAG_NONRELOCATABLE
mdefine_line|#define ICB_FLAG_NONRELOCATABLE&t;0x0010U
DECL|macro|ICB_FLAG_ARCHIVE
mdefine_line|#define ICB_FLAG_ARCHIVE&t;0x0020U
DECL|macro|ICB_FLAG_SETUID
mdefine_line|#define ICB_FLAG_SETUID&t;&t;0x0040U
DECL|macro|ICB_FLAG_SETGID
mdefine_line|#define ICB_FLAG_SETGID&t;&t;0x0080U
DECL|macro|ICB_FLAG_STICKY
mdefine_line|#define ICB_FLAG_STICKY&t;&t;0x0100U
DECL|macro|ICB_FLAG_CONTIGUOUS
mdefine_line|#define ICB_FLAG_CONTIGUOUS&t;0x0200U
DECL|macro|ICB_FLAG_SYSTEM
mdefine_line|#define ICB_FLAG_SYSTEM&t;&t;0x0400U
DECL|macro|ICB_FLAG_TRANSFORMED
mdefine_line|#define ICB_FLAG_TRANSFORMED&t;0x0800U
DECL|macro|ICB_FLAG_MULTIVERSIONS
mdefine_line|#define ICB_FLAG_MULTIVERSIONS&t;0x1000U
multiline_comment|/* ICB Flags Allocation type(ECMA 167 4/14.6.8) */
DECL|macro|ICB_FLAG_AD_SHORT
mdefine_line|#define ICB_FLAG_AD_SHORT&t;0
DECL|macro|ICB_FLAG_AD_LONG
mdefine_line|#define ICB_FLAG_AD_LONG&t;1
DECL|macro|ICB_FLAG_AD_EXTENDED
mdefine_line|#define ICB_FLAG_AD_EXTENDED&t;2
DECL|macro|ICB_FLAG_AD_IN_ICB
mdefine_line|#define ICB_FLAG_AD_IN_ICB&t;3
multiline_comment|/* Indirect Entry (ECMA 167 4/14.7) */
DECL|struct|IndirectEntry
r_struct
id|IndirectEntry
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|icbTag
id|icbtag
id|icbTag
suffix:semicolon
DECL|member|indirectICB
id|long_ad
id|indirectICB
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Terminal Entry (ECMA 167 4/14.8) */
DECL|struct|TerminalEntry
r_struct
id|TerminalEntry
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|icbTag
id|icbtag
id|icbTag
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* File Entry (ECMA 167 4/14.9) */
DECL|struct|FileEntry
r_struct
id|FileEntry
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|icbTag
id|icbtag
id|icbTag
suffix:semicolon
DECL|member|uid
id|Uint32
id|uid
suffix:semicolon
DECL|member|gid
id|Uint32
id|gid
suffix:semicolon
DECL|member|permissions
id|Uint32
id|permissions
suffix:semicolon
DECL|member|fileLinkCount
id|Uint16
id|fileLinkCount
suffix:semicolon
DECL|member|recordFormat
id|Uint8
id|recordFormat
suffix:semicolon
DECL|member|recordDisplayAttr
id|Uint8
id|recordDisplayAttr
suffix:semicolon
DECL|member|recordLength
id|Uint32
id|recordLength
suffix:semicolon
DECL|member|informationLength
id|Uint64
id|informationLength
suffix:semicolon
DECL|member|logicalBlocksRecorded
id|Uint64
id|logicalBlocksRecorded
suffix:semicolon
DECL|member|accessTime
id|timestamp
id|accessTime
suffix:semicolon
DECL|member|modificationTime
id|timestamp
id|modificationTime
suffix:semicolon
DECL|member|attrTime
id|timestamp
id|attrTime
suffix:semicolon
DECL|member|checkpoint
id|Uint32
id|checkpoint
suffix:semicolon
DECL|member|extendedAttrICB
id|long_ad
id|extendedAttrICB
suffix:semicolon
DECL|member|impIdent
id|EntityID
id|impIdent
suffix:semicolon
DECL|member|uniqueID
id|Uint64
id|uniqueID
suffix:semicolon
multiline_comment|/* 0= root, 16- (2^32-1) */
DECL|member|lengthExtendedAttr
id|Uint32
id|lengthExtendedAttr
suffix:semicolon
DECL|member|lengthAllocDescs
id|Uint32
id|lengthAllocDescs
suffix:semicolon
DECL|member|extendedAttr
id|Uint8
id|extendedAttr
(braket
l_int|0
)braket
suffix:semicolon
DECL|member|allocDescs
id|Uint8
id|allocDescs
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* File Permissions (ECMA 167 4/14.9.5) */
DECL|macro|PERM_O_EXEC
mdefine_line|#define PERM_O_EXEC&t;0x00000001U
DECL|macro|PERM_O_WRITE
mdefine_line|#define PERM_O_WRITE&t;0x00000002U
DECL|macro|PERM_O_READ
mdefine_line|#define PERM_O_READ&t;0x00000004U
DECL|macro|PERM_O_CHATTR
mdefine_line|#define PERM_O_CHATTR&t;0x00000008U
DECL|macro|PERM_O_DELETE
mdefine_line|#define PERM_O_DELETE&t;0x00000010U
DECL|macro|PERM_G_EXEC
mdefine_line|#define PERM_G_EXEC&t;0x00000020U
DECL|macro|PERM_G_WRITE
mdefine_line|#define PERM_G_WRITE&t;0x00000040U
DECL|macro|PERM_G_READ
mdefine_line|#define PERM_G_READ&t;0x00000080U
DECL|macro|PERM_G_CHATTR
mdefine_line|#define PERM_G_CHATTR&t;0x00000100U
DECL|macro|PERM_G_DELETE
mdefine_line|#define PERM_G_DELETE&t;0x00000200U
DECL|macro|PERM_U_EXEC
mdefine_line|#define PERM_U_EXEC&t;0x00000400U
DECL|macro|PERM_U_WRITE
mdefine_line|#define PERM_U_WRITE&t;0x00000800U
DECL|macro|PERM_U_READ
mdefine_line|#define PERM_U_READ&t;0x00001000U
DECL|macro|PERM_U_CHATTR
mdefine_line|#define PERM_U_CHATTR&t;0x00002000U
DECL|macro|PERM_U_DELETE
mdefine_line|#define PERM_U_DELETE&t;0x00004000U
multiline_comment|/* File Record Format (ECMA 167 4/14.9.7) */
DECL|macro|RECORD_FMT_NONE
mdefine_line|#define RECORD_FMT_NONE&t;&t;&t;0
DECL|macro|RECORD_FMT_FIXED_PAD
mdefine_line|#define RECORD_FMT_FIXED_PAD&t;&t;1
DECL|macro|RECORD_FMT_FIXED
mdefine_line|#define RECORD_FMT_FIXED&t;&t;2
DECL|macro|RECORD_FMT_VARIABLE8
mdefine_line|#define RECORD_FMT_VARIABLE8&t;&t;3
DECL|macro|RECORD_FMT_VARIABLE16
mdefine_line|#define RECORD_FMT_VARIABLE16&t;&t;4
DECL|macro|RECORD_FMT_VARIABLE16_MSB
mdefine_line|#define RECORD_FMT_VARIABLE16_MSB&t;5
DECL|macro|RECORD_FMT_VARIABLE32
mdefine_line|#define RECORD_FMT_VARIABLE32&t;&t;6
DECL|macro|RECORD_FMT_PRINT
mdefine_line|#define RECORD_FMT_PRINT&t;&t;7
DECL|macro|RECORD_FMT_LF
mdefine_line|#define RECORD_FMT_LF&t;&t;&t;8
DECL|macro|RECORD_FMT_CR
mdefine_line|#define RECORD_FMT_CR&t;&t;&t;9
DECL|macro|RECORD_FMT_CRLF
mdefine_line|#define RECORD_FMT_CRLF&t;&t;&t;10
DECL|macro|RECORD_FMT_LFCR
mdefine_line|#define RECORD_FMT_LFCR&t;&t;&t;10
multiline_comment|/* Extended Attribute Header Descriptor (ECMA 167 4/14.10.1) */
DECL|struct|ExtendedAttrHeaderDesc
r_struct
id|ExtendedAttrHeaderDesc
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|impAttrLocation
id|Uint32
id|impAttrLocation
suffix:semicolon
DECL|member|appAttrLocation
id|Uint32
id|appAttrLocation
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Generic Attribute Format (ECMA 4/14.10.2) */
DECL|struct|GenericAttrFormat
r_struct
id|GenericAttrFormat
(brace
DECL|member|attrType
id|Uint32
id|attrType
suffix:semicolon
DECL|member|attrSubtype
id|Uint8
id|attrSubtype
suffix:semicolon
DECL|member|reserved
id|Uint8
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|attrLength
id|Uint32
id|attrLength
suffix:semicolon
DECL|member|attrData
id|Uint8
id|attrData
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Character Set Attribute Format (ECMA 4/14.10.3) */
DECL|struct|CharSetAttrFormat
r_struct
id|CharSetAttrFormat
(brace
DECL|member|attrType
id|Uint32
id|attrType
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|attrSubtype
id|Uint8
id|attrSubtype
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|reserved
id|Uint8
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|attrLength
id|Uint32
id|attrLength
suffix:semicolon
DECL|member|escapeSeqLength
id|Uint32
id|escapeSeqLength
suffix:semicolon
DECL|member|charSetType
id|Uint8
id|charSetType
suffix:semicolon
DECL|member|escapeSeq
id|Uint8
id|escapeSeq
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Alternate Permissions (ECMA 167 4/14.10.4) */
DECL|struct|AlternatePermissionsExtendedAttr
r_struct
id|AlternatePermissionsExtendedAttr
(brace
DECL|member|attrType
id|Uint32
id|attrType
suffix:semicolon
multiline_comment|/* 3 */
DECL|member|attrSubtype
id|Uint8
id|attrSubtype
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|reserved
id|Uint8
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|attrLength
id|Uint32
id|attrLength
suffix:semicolon
DECL|member|ownerIdent
id|Uint16
id|ownerIdent
suffix:semicolon
DECL|member|groupIdent
id|Uint16
id|groupIdent
suffix:semicolon
DECL|member|permission
id|Uint16
id|permission
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* File Times Extended Attribute (ECMA 167 4/14.10.5) */
DECL|struct|FileTimesExtendedAttr
r_struct
id|FileTimesExtendedAttr
(brace
DECL|member|attrType
id|Uint32
id|attrType
suffix:semicolon
multiline_comment|/* 5 */
DECL|member|attrSubtype
id|Uint8
id|attrSubtype
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|reserved
id|Uint8
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|attrLength
id|Uint32
id|attrLength
suffix:semicolon
DECL|member|dataLength
id|Uint32
id|dataLength
suffix:semicolon
DECL|member|fileTimeExistence
id|Uint32
id|fileTimeExistence
suffix:semicolon
DECL|member|fileTimes
id|Uint8
id|fileTimes
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* FileTimeExistence (ECMA 167 4/14.10.5.6) */
DECL|macro|FTE_CREATION
mdefine_line|#define FTE_CREATION&t;0
DECL|macro|FTE_DELETION
mdefine_line|#define FTE_DELETION&t;2
DECL|macro|FTE_EFFECTIVE
mdefine_line|#define FTE_EFFECTIVE&t;3
DECL|macro|FTE_BACKUP
mdefine_line|#define FTE_BACKUP&t;5
multiline_comment|/* Information Times Extended Attribute (ECMA 167 4/14.10.6) */
DECL|struct|InfoTimesExtendedAttr
r_struct
id|InfoTimesExtendedAttr
(brace
DECL|member|attrType
id|Uint32
id|attrType
suffix:semicolon
multiline_comment|/* 6 */
DECL|member|attrSubtype
id|Uint8
id|attrSubtype
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|reserved
id|Uint8
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|attrLength
id|Uint32
id|attrLength
suffix:semicolon
DECL|member|dataLength
id|Uint32
id|dataLength
suffix:semicolon
DECL|member|infoTimeExistence
id|Uint32
id|infoTimeExistence
suffix:semicolon
DECL|member|infoTimes
id|Uint8
id|infoTimes
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Device Specification Extended Attribute (ECMA 167 4/14.10.7) */
DECL|struct|DeviceSpecificationExtendedAttr
r_struct
id|DeviceSpecificationExtendedAttr
(brace
DECL|member|attrType
id|Uint32
id|attrType
suffix:semicolon
multiline_comment|/* 12 */
DECL|member|attrSubtype
id|Uint8
id|attrSubtype
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|reserved
id|Uint8
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|attrLength
id|Uint32
id|attrLength
suffix:semicolon
DECL|member|impUseLength
id|Uint32
id|impUseLength
suffix:semicolon
DECL|member|majorDeviceIdent
id|Uint32
id|majorDeviceIdent
suffix:semicolon
DECL|member|minorDeviceIdent
id|Uint32
id|minorDeviceIdent
suffix:semicolon
DECL|member|impUse
id|Uint8
id|impUse
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Implementation Use Extended Attr (ECMA 167 4/14.10.8) */
DECL|struct|ImpUseExtendedAttr
r_struct
id|ImpUseExtendedAttr
(brace
DECL|member|attrType
id|Uint32
id|attrType
suffix:semicolon
multiline_comment|/* 2048 */
DECL|member|attrSubtype
id|Uint8
id|attrSubtype
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|reserved
id|Uint8
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|attrLength
id|Uint32
id|attrLength
suffix:semicolon
DECL|member|impUseLength
id|Uint32
id|impUseLength
suffix:semicolon
DECL|member|impIdent
id|EntityID
id|impIdent
suffix:semicolon
DECL|member|impUse
id|Uint8
id|impUse
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Application Use Extended Attribute (ECMA 167 4/14.10.9) */
DECL|struct|AppUseExtendedAttr
r_struct
id|AppUseExtendedAttr
(brace
DECL|member|attrType
id|Uint32
id|attrType
suffix:semicolon
multiline_comment|/* 65536 */
DECL|member|attrSubtype
id|Uint8
id|attrSubtype
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|reserved
id|Uint8
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|attrLength
id|Uint32
id|attrLength
suffix:semicolon
DECL|member|appUseLength
id|Uint32
id|appUseLength
suffix:semicolon
DECL|member|appIdent
id|EntityID
id|appIdent
suffix:semicolon
DECL|member|appUse
id|Uint8
id|appUse
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EXTATTR_CHAR_SET
mdefine_line|#define EXTATTR_CHAR_SET&t;1
DECL|macro|EXTATTR_ALT_PERMS
mdefine_line|#define EXTATTR_ALT_PERMS&t;3
DECL|macro|EXTATTR_FILE_TIMES
mdefine_line|#define EXTATTR_FILE_TIMES&t;5
DECL|macro|EXTATTR_INFO_TIMES
mdefine_line|#define EXTATTR_INFO_TIMES&t;6
DECL|macro|EXTATTR_DEV_SPEC
mdefine_line|#define EXTATTR_DEV_SPEC&t;12
DECL|macro|EXTATTR_IMP_USE
mdefine_line|#define EXTATTR_IMP_USE&t;&t;2048
DECL|macro|EXTATTR_APP_USE
mdefine_line|#define EXTATTR_APP_USE&t;&t;65536
multiline_comment|/* Unallocated Space Entry (ECMA 167 4/14.11) */
DECL|struct|UnallocatedSpaceEntry
r_struct
id|UnallocatedSpaceEntry
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|icbTag
id|icbtag
id|icbTag
suffix:semicolon
DECL|member|lengthAllocDescs
id|Uint32
id|lengthAllocDescs
suffix:semicolon
DECL|member|allocDescs
id|Uint8
id|allocDescs
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Space Bitmap Descriptor (ECMA 167 4/14.12) */
DECL|struct|SpaceBitmapDesc
r_struct
id|SpaceBitmapDesc
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|numOfBits
id|Uint32
id|numOfBits
suffix:semicolon
DECL|member|numOfBytes
id|Uint32
id|numOfBytes
suffix:semicolon
DECL|member|bitmap
id|Uint8
id|bitmap
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Partition Integrity Entry (ECMA 167 4/14.13) */
DECL|struct|PartitionIntegrityEntry
r_struct
id|PartitionIntegrityEntry
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|icbTag
id|icbtag
id|icbTag
suffix:semicolon
DECL|member|recordingDateAndTime
id|timestamp
id|recordingDateAndTime
suffix:semicolon
DECL|member|integrityType
id|Uint8
id|integrityType
suffix:semicolon
DECL|member|reserved
id|Uint8
id|reserved
(braket
l_int|175
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
l_int|256
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Extended Allocation Descriptor (ECMA 167 4/14.14.3) */
r_typedef
r_struct
(brace
multiline_comment|/* ECMA 167 4/14.14.3 */
DECL|member|extLength
id|Uint32
id|extLength
suffix:semicolon
DECL|member|recordedLength
id|Uint32
id|recordedLength
suffix:semicolon
DECL|member|informationLength
id|Uint32
id|informationLength
suffix:semicolon
DECL|member|extLocation
id|lb_addr
id|extLocation
suffix:semicolon
DECL|typedef|ext_ad
)brace
id|ext_ad
suffix:semicolon
multiline_comment|/* Logical Volume Header Descriptor (ECMA 167 4/14.5) */
DECL|struct|LogicalVolHeaderDesc
r_struct
id|LogicalVolHeaderDesc
(brace
DECL|member|uniqueID
id|Uint64
id|uniqueID
suffix:semicolon
DECL|member|reserved
id|Uint8
id|reserved
(braket
l_int|24
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Path Component (ECMA 167 4/14.16.1) */
DECL|struct|PathComponent
r_struct
id|PathComponent
(brace
DECL|member|componentType
id|Uint8
id|componentType
suffix:semicolon
DECL|member|lengthComponentIdent
id|Uint8
id|lengthComponentIdent
suffix:semicolon
DECL|member|componentFileVersionNum
id|Uint16
id|componentFileVersionNum
suffix:semicolon
DECL|member|componentIdent
id|dstring
id|componentIdent
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* File Entry (ECMA 167 4/14.17) */
DECL|struct|ExtendedFileEntry
r_struct
id|ExtendedFileEntry
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|icbTag
id|icbtag
id|icbTag
suffix:semicolon
DECL|member|uid
id|Uint32
id|uid
suffix:semicolon
DECL|member|gid
id|Uint32
id|gid
suffix:semicolon
DECL|member|permissions
id|Uint32
id|permissions
suffix:semicolon
DECL|member|fileLinkCount
id|Uint16
id|fileLinkCount
suffix:semicolon
DECL|member|recordFormat
id|Uint8
id|recordFormat
suffix:semicolon
DECL|member|recordDisplayAttr
id|Uint8
id|recordDisplayAttr
suffix:semicolon
DECL|member|recordLength
id|Uint32
id|recordLength
suffix:semicolon
DECL|member|informationLength
id|Uint64
id|informationLength
suffix:semicolon
DECL|member|objectSize
id|Uint64
id|objectSize
suffix:semicolon
DECL|member|logicalBlocksRecorded
id|Uint64
id|logicalBlocksRecorded
suffix:semicolon
DECL|member|accessTime
id|timestamp
id|accessTime
suffix:semicolon
DECL|member|modificationTime
id|timestamp
id|modificationTime
suffix:semicolon
DECL|member|createTime
id|timestamp
id|createTime
suffix:semicolon
DECL|member|attrTime
id|timestamp
id|attrTime
suffix:semicolon
DECL|member|checkpoint
id|Uint32
id|checkpoint
suffix:semicolon
DECL|member|reserved
id|Uint32
id|reserved
suffix:semicolon
DECL|member|extendedAttrICB
id|long_ad
id|extendedAttrICB
suffix:semicolon
DECL|member|streamDirectoryICB
id|long_ad
id|streamDirectoryICB
suffix:semicolon
DECL|member|impIdent
id|EntityID
id|impIdent
suffix:semicolon
DECL|member|uniqueID
id|Uint64
id|uniqueID
suffix:semicolon
DECL|member|lengthExtendedAttr
id|Uint32
id|lengthExtendedAttr
suffix:semicolon
DECL|member|lengthAllocDescs
id|Uint32
id|lengthAllocDescs
suffix:semicolon
DECL|member|extendedAttr
id|Uint8
id|extendedAttr
(braket
l_int|0
)braket
suffix:semicolon
DECL|member|allocDescs
id|Uint8
id|allocDescs
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#pragma pack()
macro_line|#endif /* !defined(_LINUX_UDF_167_H) */
eof
