multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2001 Silicon Graphics, Inc. All rights reserved.&n; */
multiline_comment|/* $Id$&n; *&n; * ARCS hardware/memory inventory/configuration and system ID definitions.&n; */
macro_line|#ifndef _ASM_SN_ARC_HINV_H
DECL|macro|_ASM_SN_ARC_HINV_H
mdefine_line|#define _ASM_SN_ARC_HINV_H
macro_line|#include &lt;asm/sn/arc/types.h&gt;
multiline_comment|/* configuration query defines */
DECL|enum|configclass
r_typedef
r_enum
id|configclass
(brace
DECL|enumerator|SystemClass
id|SystemClass
comma
DECL|enumerator|ProcessorClass
id|ProcessorClass
comma
DECL|enumerator|CacheClass
id|CacheClass
comma
macro_line|#ifndef&t;_NT_PROM
DECL|enumerator|MemoryClass
id|MemoryClass
comma
DECL|enumerator|AdapterClass
id|AdapterClass
comma
DECL|enumerator|ControllerClass
id|ControllerClass
comma
DECL|enumerator|PeripheralClass
id|PeripheralClass
macro_line|#else&t;/* _NT_PROM */
id|AdapterClass
comma
id|ControllerClass
comma
id|PeripheralClass
comma
id|MemoryClass
macro_line|#endif&t;/* _NT_PROM */
DECL|typedef|CONFIGCLASS
)brace
id|CONFIGCLASS
suffix:semicolon
DECL|enum|configtype
r_typedef
r_enum
id|configtype
(brace
DECL|enumerator|ARC
id|ARC
comma
DECL|enumerator|CPU
id|CPU
comma
DECL|enumerator|FPU
id|FPU
comma
DECL|enumerator|PrimaryICache
id|PrimaryICache
comma
DECL|enumerator|PrimaryDCache
id|PrimaryDCache
comma
DECL|enumerator|SecondaryICache
id|SecondaryICache
comma
DECL|enumerator|SecondaryDCache
id|SecondaryDCache
comma
DECL|enumerator|SecondaryCache
id|SecondaryCache
comma
macro_line|#ifndef&t;_NT_PROM
DECL|enumerator|Memory
id|Memory
comma
macro_line|#endif
DECL|enumerator|EISAAdapter
id|EISAAdapter
comma
DECL|enumerator|TCAdapter
id|TCAdapter
comma
DECL|enumerator|SCSIAdapter
id|SCSIAdapter
comma
DECL|enumerator|DTIAdapter
id|DTIAdapter
comma
DECL|enumerator|MultiFunctionAdapter
id|MultiFunctionAdapter
comma
DECL|enumerator|DiskController
id|DiskController
comma
DECL|enumerator|TapeController
id|TapeController
comma
DECL|enumerator|CDROMController
id|CDROMController
comma
DECL|enumerator|WORMController
id|WORMController
comma
DECL|enumerator|SerialController
id|SerialController
comma
DECL|enumerator|NetworkController
id|NetworkController
comma
DECL|enumerator|DisplayController
id|DisplayController
comma
DECL|enumerator|ParallelController
id|ParallelController
comma
DECL|enumerator|PointerController
id|PointerController
comma
DECL|enumerator|KeyboardController
id|KeyboardController
comma
DECL|enumerator|AudioController
id|AudioController
comma
DECL|enumerator|OtherController
id|OtherController
comma
DECL|enumerator|DiskPeripheral
id|DiskPeripheral
comma
DECL|enumerator|FloppyDiskPeripheral
id|FloppyDiskPeripheral
comma
DECL|enumerator|TapePeripheral
id|TapePeripheral
comma
DECL|enumerator|ModemPeripheral
id|ModemPeripheral
comma
DECL|enumerator|MonitorPeripheral
id|MonitorPeripheral
comma
DECL|enumerator|PrinterPeripheral
id|PrinterPeripheral
comma
DECL|enumerator|PointerPeripheral
id|PointerPeripheral
comma
DECL|enumerator|KeyboardPeripheral
id|KeyboardPeripheral
comma
DECL|enumerator|TerminalPeripheral
id|TerminalPeripheral
comma
DECL|enumerator|LinePeripheral
id|LinePeripheral
comma
DECL|enumerator|NetworkPeripheral
id|NetworkPeripheral
comma
macro_line|#ifdef&t;_NT_PROM
DECL|enumerator|Memory
id|Memory
comma
macro_line|#endif
DECL|enumerator|OtherPeripheral
id|OtherPeripheral
comma
multiline_comment|/* new stuff for IP30 */
multiline_comment|/* added without moving anything */
multiline_comment|/* except ANONYMOUS. */
DECL|enumerator|XTalkAdapter
id|XTalkAdapter
comma
DECL|enumerator|PCIAdapter
id|PCIAdapter
comma
DECL|enumerator|GIOAdapter
id|GIOAdapter
comma
DECL|enumerator|TPUAdapter
id|TPUAdapter
comma
DECL|enumerator|TernaryCache
id|TernaryCache
comma
DECL|enumerator|Anonymous
id|Anonymous
DECL|typedef|CONFIGTYPE
)brace
id|CONFIGTYPE
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|Failed
id|Failed
op_assign
l_int|1
comma
DECL|enumerator|ReadOnly
id|ReadOnly
op_assign
l_int|2
comma
DECL|enumerator|Removable
id|Removable
op_assign
l_int|4
comma
DECL|enumerator|ConsoleIn
id|ConsoleIn
op_assign
l_int|8
comma
DECL|enumerator|ConsoleOut
id|ConsoleOut
op_assign
l_int|16
comma
DECL|enumerator|Input
id|Input
op_assign
l_int|32
comma
DECL|enumerator|Output
id|Output
op_assign
l_int|64
DECL|typedef|IDENTIFIERFLAG
)brace
id|IDENTIFIERFLAG
suffix:semicolon
macro_line|#ifndef NULL&t;&t;&t;/* for GetChild(NULL); */
DECL|macro|NULL
mdefine_line|#define&t;NULL&t;0
macro_line|#endif
DECL|union|key_u
r_union
id|key_u
(brace
r_struct
(brace
macro_line|#ifdef&t;_MIPSEB
DECL|member|c_bsize
r_int
r_char
id|c_bsize
suffix:semicolon
multiline_comment|/* block size in lines */
DECL|member|c_lsize
r_int
r_char
id|c_lsize
suffix:semicolon
multiline_comment|/* line size in bytes/tag */
DECL|member|c_size
r_int
r_int
id|c_size
suffix:semicolon
multiline_comment|/* cache size in 4K pages */
macro_line|#else&t;/* _MIPSEL */
r_int
r_int
id|c_size
suffix:semicolon
multiline_comment|/* cache size in 4K pages */
r_int
r_char
id|c_lsize
suffix:semicolon
multiline_comment|/* line size in bytes/tag */
r_int
r_char
id|c_bsize
suffix:semicolon
multiline_comment|/* block size in lines */
macro_line|#endif&t;/* _MIPSEL */
DECL|member|cache
)brace
id|cache
suffix:semicolon
DECL|member|FullKey
id|ULONG
id|FullKey
suffix:semicolon
)brace
suffix:semicolon
macro_line|#if _MIPS_SIM == _ABI64
DECL|macro|SGI_ARCS_VERS
mdefine_line|#define SGI_ARCS_VERS&t;64&t;&t;&t;/* sgi 64-bit version */
DECL|macro|SGI_ARCS_REV
mdefine_line|#define SGI_ARCS_REV&t;0&t;&t;&t;/* rev .00 */
macro_line|#else
DECL|macro|SGI_ARCS_VERS
mdefine_line|#define SGI_ARCS_VERS&t;1&t;&t;&t;/* first version */
DECL|macro|SGI_ARCS_REV
mdefine_line|#define SGI_ARCS_REV&t;10&t;&t;&t;/* rev .10, 3/04/92 */
macro_line|#endif
DECL|struct|component
r_typedef
r_struct
id|component
(brace
DECL|member|Class
id|CONFIGCLASS
id|Class
suffix:semicolon
DECL|member|Type
id|CONFIGTYPE
id|Type
suffix:semicolon
DECL|member|Flags
id|IDENTIFIERFLAG
id|Flags
suffix:semicolon
DECL|member|Version
id|USHORT
id|Version
suffix:semicolon
DECL|member|Revision
id|USHORT
id|Revision
suffix:semicolon
DECL|member|Key
id|ULONG
id|Key
suffix:semicolon
DECL|member|AffinityMask
id|ULONG
id|AffinityMask
suffix:semicolon
DECL|member|ConfigurationDataSize
id|ULONG
id|ConfigurationDataSize
suffix:semicolon
DECL|member|IdentifierLength
id|ULONG
id|IdentifierLength
suffix:semicolon
DECL|member|Identifier
r_char
op_star
id|Identifier
suffix:semicolon
DECL|typedef|COMPONENT
)brace
id|COMPONENT
suffix:semicolon
multiline_comment|/* internal structure that holds pathname parsing data */
DECL|struct|cfgdata
r_struct
id|cfgdata
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* full name */
DECL|member|minlen
r_int
id|minlen
suffix:semicolon
multiline_comment|/* minimum length to match */
DECL|member|type
id|CONFIGTYPE
id|type
suffix:semicolon
multiline_comment|/* type of token */
)brace
suffix:semicolon
multiline_comment|/* System ID */
DECL|struct|systemid
r_typedef
r_struct
id|systemid
(brace
DECL|member|VendorId
id|CHAR
id|VendorId
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ProductId
id|CHAR
id|ProductId
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|SYSTEMID
)brace
id|SYSTEMID
suffix:semicolon
multiline_comment|/* memory query functions */
DECL|enum|memorytype
r_typedef
r_enum
id|memorytype
(brace
DECL|enumerator|ExceptionBlock
id|ExceptionBlock
comma
DECL|enumerator|SPBPage
id|SPBPage
comma
multiline_comment|/* ARCS == SystemParameterBlock */
macro_line|#ifndef&t;_NT_PROM
DECL|enumerator|FreeContiguous
id|FreeContiguous
comma
DECL|enumerator|FreeMemory
id|FreeMemory
comma
DECL|enumerator|BadMemory
id|BadMemory
comma
DECL|enumerator|LoadedProgram
id|LoadedProgram
comma
DECL|enumerator|FirmwareTemporary
id|FirmwareTemporary
comma
DECL|enumerator|FirmwarePermanent
id|FirmwarePermanent
macro_line|#else&t;/* _NT_PROM */
id|FreeMemory
comma
id|BadMemory
comma
id|LoadedProgram
comma
id|FirmwareTemporary
comma
id|FirmwarePermanent
comma
id|FreeContiguous
macro_line|#endif&t;/* _NT_PROM */
DECL|typedef|MEMORYTYPE
)brace
id|MEMORYTYPE
suffix:semicolon
DECL|struct|memorydescriptor
r_typedef
r_struct
id|memorydescriptor
(brace
DECL|member|Type
id|MEMORYTYPE
id|Type
suffix:semicolon
DECL|member|BasePage
id|LONG
id|BasePage
suffix:semicolon
DECL|member|PageCount
id|LONG
id|PageCount
suffix:semicolon
DECL|typedef|MEMORYDESCRIPTOR
)brace
id|MEMORYDESCRIPTOR
suffix:semicolon
macro_line|#endif /* _ASM_SN_ARC_HINV_H */
eof
