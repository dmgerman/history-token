multiline_comment|/*&n; *&t;FILE    &t;SA-1100.h&n; *&n; *&t;Version &t;1.2&n; *&t;Author  &t;Copyright (c) Marc A. Viredaz, 1998&n; *&t;        &t;DEC Western Research Laboratory, Palo Alto, CA&n; *&t;Date    &t;January 1998 (April 1997)&n; *&t;System  &t;StrongARM SA-1100&n; *&t;Language&t;C or ARM Assembly&n; *&t;Purpose &t;Definition of constants related to the StrongARM&n; *&t;        &t;SA-1100 microprocessor (Advanced RISC Machine (ARM)&n; *&t;        &t;architecture version 4). This file is based on the&n; *&t;        &t;StrongARM SA-1100 data sheet version 2.2.&n; *&n; *&t;        &t;Language-specific definitions are selected by the&n; *&t;        &t;macro &quot;LANGUAGE&quot;, which should be defined as either&n; *&t;        &t;&quot;C&quot; (default) or &quot;Assembly&quot;.&n; */
multiline_comment|/* Be sure that virtual mapping is defined right */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
macro_line|#error You must include hardware.h not SA-1100.h
macro_line|#endif
macro_line|#ifndef LANGUAGE
macro_line|# ifdef __ASSEMBLY__
DECL|macro|LANGUAGE
macro_line|#  define LANGUAGE Assembly
macro_line|# else
DECL|macro|LANGUAGE
macro_line|#  define LANGUAGE C
macro_line|# endif
macro_line|#endif
macro_line|#ifndef io_p2v
DECL|macro|io_p2v
mdefine_line|#define io_p2v(PhAdd)&t;(PhAdd)
macro_line|#endif
macro_line|#include &lt;asm/arch/bitfield.h&gt;
DECL|macro|C
mdefine_line|#define C       &t;0
DECL|macro|Assembly
mdefine_line|#define Assembly&t;1
macro_line|#if LANGUAGE == C
DECL|typedef|Word16
r_typedef
r_int
r_int
id|Word16
suffix:semicolon
DECL|typedef|Word32
r_typedef
r_int
r_int
id|Word32
suffix:semicolon
DECL|typedef|Word
r_typedef
id|Word32
id|Word
suffix:semicolon
DECL|typedef|Quad
r_typedef
id|Word
id|Quad
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|Address
r_typedef
r_void
op_star
id|Address
suffix:semicolon
DECL|typedef|ExcpHndlr
r_typedef
r_void
(paren
op_star
id|ExcpHndlr
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* LANGUAGE == C */
multiline_comment|/*&n; * Memory&n; */
DECL|macro|MemBnkSp
mdefine_line|#define MemBnkSp&t;0x08000000&t;/* Memory Bank Space [byte]        */
DECL|macro|StMemBnkSp
mdefine_line|#define StMemBnkSp&t;MemBnkSp&t;/* Static Memory Bank Space [byte] */
DECL|macro|StMemBnk0Sp
mdefine_line|#define StMemBnk0Sp&t;StMemBnkSp&t;/* Static Memory Bank 0 Space      */
multiline_comment|/* [byte]                          */
DECL|macro|StMemBnk1Sp
mdefine_line|#define StMemBnk1Sp&t;StMemBnkSp&t;/* Static Memory Bank 1 Space      */
multiline_comment|/* [byte]                          */
DECL|macro|StMemBnk2Sp
mdefine_line|#define StMemBnk2Sp&t;StMemBnkSp&t;/* Static Memory Bank 2 Space      */
multiline_comment|/* [byte]                          */
DECL|macro|StMemBnk3Sp
mdefine_line|#define StMemBnk3Sp&t;StMemBnkSp&t;/* Static Memory Bank 3 Space      */
multiline_comment|/* [byte]                          */
DECL|macro|DRAMBnkSp
mdefine_line|#define DRAMBnkSp&t;MemBnkSp&t;/* DRAM Bank Space [byte]          */
DECL|macro|DRAMBnk0Sp
mdefine_line|#define DRAMBnk0Sp&t;DRAMBnkSp&t;/* DRAM Bank 0 Space [byte]        */
DECL|macro|DRAMBnk1Sp
mdefine_line|#define DRAMBnk1Sp&t;DRAMBnkSp&t;/* DRAM Bank 1 Space [byte]        */
DECL|macro|DRAMBnk2Sp
mdefine_line|#define DRAMBnk2Sp&t;DRAMBnkSp&t;/* DRAM Bank 2 Space [byte]        */
DECL|macro|DRAMBnk3Sp
mdefine_line|#define DRAMBnk3Sp&t;DRAMBnkSp&t;/* DRAM Bank 3 Space [byte]        */
DECL|macro|ZeroMemSp
mdefine_line|#define ZeroMemSp&t;MemBnkSp&t;/* Zero Memory bank Space [byte]   */
DECL|macro|_StMemBnk
mdefine_line|#define _StMemBnk(Nb)&t;        &t;/* Static Memory Bank [0..3]       */ &bslash;&n;                &t;(0x00000000 + (Nb)*StMemBnkSp)
DECL|macro|_StMemBnk0
mdefine_line|#define _StMemBnk0&t;_StMemBnk (0)&t;/* Static Memory Bank 0            */
DECL|macro|_StMemBnk1
mdefine_line|#define _StMemBnk1&t;_StMemBnk (1)&t;/* Static Memory Bank 1            */
DECL|macro|_StMemBnk2
mdefine_line|#define _StMemBnk2&t;_StMemBnk (2)&t;/* Static Memory Bank 2            */
DECL|macro|_StMemBnk3
mdefine_line|#define _StMemBnk3&t;_StMemBnk (3)&t;/* Static Memory Bank 3            */
macro_line|#if LANGUAGE == C
DECL|typedef|StMemBnkType
r_typedef
id|Quad
id|StMemBnkType
(braket
id|StMemBnkSp
op_div
r_sizeof
(paren
id|Quad
)paren
)braket
suffix:semicolon
DECL|macro|StMemBnk
mdefine_line|#define StMemBnk&t;        &t;/* Static Memory Bank [0..3]       */ &bslash;&n;                &t;((StMemBnkType *) io_p2v (_StMemBnk (0)))
DECL|macro|StMemBnk0
mdefine_line|#define StMemBnk0&t;(StMemBnk [0])&t;/* Static Memory Bank 0            */
DECL|macro|StMemBnk1
mdefine_line|#define StMemBnk1&t;(StMemBnk [1])&t;/* Static Memory Bank 1            */
DECL|macro|StMemBnk2
mdefine_line|#define StMemBnk2&t;(StMemBnk [2])&t;/* Static Memory Bank 2            */
DECL|macro|StMemBnk3
mdefine_line|#define StMemBnk3&t;(StMemBnk [3])&t;/* Static Memory Bank 3            */
macro_line|#endif /* LANGUAGE == C */
DECL|macro|_DRAMBnk
mdefine_line|#define _DRAMBnk(Nb)&t;        &t;/* DRAM Bank [0..3]                */ &bslash;&n;                &t;(0xC0000000 + (Nb)*DRAMBnkSp)
DECL|macro|_DRAMBnk0
mdefine_line|#define _DRAMBnk0&t;_DRAMBnk (0)&t;/* DRAM Bank 0                     */
DECL|macro|_DRAMBnk1
mdefine_line|#define _DRAMBnk1&t;_DRAMBnk (1)&t;/* DRAM Bank 1                     */
DECL|macro|_DRAMBnk2
mdefine_line|#define _DRAMBnk2&t;_DRAMBnk (2)&t;/* DRAM Bank 2                     */
DECL|macro|_DRAMBnk3
mdefine_line|#define _DRAMBnk3&t;_DRAMBnk (3)&t;/* DRAM Bank 3                     */
macro_line|#if LANGUAGE == C
DECL|typedef|DRAMBnkType
r_typedef
id|Quad
id|DRAMBnkType
(braket
id|DRAMBnkSp
op_div
r_sizeof
(paren
id|Quad
)paren
)braket
suffix:semicolon
DECL|macro|DRAMBnk
mdefine_line|#define DRAMBnk &t;        &t;/* DRAM Bank [0..3]                */ &bslash;&n;                &t;((DRAMBnkType *) io_p2v (_DRAMBnk (0)))
DECL|macro|DRAMBnk0
mdefine_line|#define DRAMBnk0&t;(DRAMBnk [0])&t;/* DRAM Bank 0                     */
DECL|macro|DRAMBnk1
mdefine_line|#define DRAMBnk1&t;(DRAMBnk [1])&t;/* DRAM Bank 1                     */
DECL|macro|DRAMBnk2
mdefine_line|#define DRAMBnk2&t;(DRAMBnk [2])&t;/* DRAM Bank 2                     */
DECL|macro|DRAMBnk3
mdefine_line|#define DRAMBnk3&t;(DRAMBnk [3])&t;/* DRAM Bank 3                     */
macro_line|#endif /* LANGUAGE == C */
DECL|macro|_ZeroMem
mdefine_line|#define _ZeroMem&t;0xE0000000&t;/* Zero Memory bank                */
macro_line|#if LANGUAGE == C
DECL|typedef|ZeroMemType
r_typedef
id|Quad
id|ZeroMemType
(braket
id|ZeroMemSp
op_div
r_sizeof
(paren
id|Quad
)paren
)braket
suffix:semicolon
DECL|macro|ZeroMem
mdefine_line|#define ZeroMem &t;        &t;/* Zero Memory bank                */ &bslash;&n;                &t;(*((ZeroMemType *) io_p2v (_ZeroMem)))
macro_line|#endif /* LANGUAGE == C */
multiline_comment|/*&n; * Personal Computer Memory Card International Association (PCMCIA) sockets&n; */
DECL|macro|PCMCIAPrtSp
mdefine_line|#define PCMCIAPrtSp&t;0x04000000&t;/* PCMCIA Partition Space [byte]   */
DECL|macro|PCMCIASp
mdefine_line|#define PCMCIASp&t;(4*PCMCIAPrtSp)&t;/* PCMCIA Space [byte]             */
DECL|macro|PCMCIAIOSp
mdefine_line|#define PCMCIAIOSp&t;PCMCIAPrtSp&t;/* PCMCIA I/O Space [byte]         */
DECL|macro|PCMCIAAttrSp
mdefine_line|#define PCMCIAAttrSp&t;PCMCIAPrtSp&t;/* PCMCIA Attribute Space [byte]   */
DECL|macro|PCMCIAMemSp
mdefine_line|#define PCMCIAMemSp&t;PCMCIAPrtSp&t;/* PCMCIA Memory Space [byte]      */
DECL|macro|PCMCIA0Sp
mdefine_line|#define PCMCIA0Sp&t;PCMCIASp&t;/* PCMCIA 0 Space [byte]           */
DECL|macro|PCMCIA0IOSp
mdefine_line|#define PCMCIA0IOSp&t;PCMCIAIOSp&t;/* PCMCIA 0 I/O Space [byte]       */
DECL|macro|PCMCIA0AttrSp
mdefine_line|#define PCMCIA0AttrSp&t;PCMCIAAttrSp&t;/* PCMCIA 0 Attribute Space [byte] */
DECL|macro|PCMCIA0MemSp
mdefine_line|#define PCMCIA0MemSp&t;PCMCIAMemSp&t;/* PCMCIA 0 Memory Space [byte]    */
DECL|macro|PCMCIA1Sp
mdefine_line|#define PCMCIA1Sp&t;PCMCIASp&t;/* PCMCIA 1 Space [byte]           */
DECL|macro|PCMCIA1IOSp
mdefine_line|#define PCMCIA1IOSp&t;PCMCIAIOSp&t;/* PCMCIA 1 I/O Space [byte]       */
DECL|macro|PCMCIA1AttrSp
mdefine_line|#define PCMCIA1AttrSp&t;PCMCIAAttrSp&t;/* PCMCIA 1 Attribute Space [byte] */
DECL|macro|PCMCIA1MemSp
mdefine_line|#define PCMCIA1MemSp&t;PCMCIAMemSp&t;/* PCMCIA 1 Memory Space [byte]    */
DECL|macro|_PCMCIA
mdefine_line|#define _PCMCIA(Nb)&t;        &t;/* PCMCIA [0..1]                   */ &bslash;&n;                &t;(0x20000000 + (Nb)*PCMCIASp)
DECL|macro|_PCMCIAIO
mdefine_line|#define _PCMCIAIO(Nb)&t;_PCMCIA (Nb)&t;/* PCMCIA I/O [0..1]               */
DECL|macro|_PCMCIAAttr
mdefine_line|#define _PCMCIAAttr(Nb)&t;        &t;/* PCMCIA Attribute [0..1]         */ &bslash;&n;                &t;(_PCMCIA (Nb) + 2*PCMCIAPrtSp)
DECL|macro|_PCMCIAMem
mdefine_line|#define _PCMCIAMem(Nb)&t;        &t;/* PCMCIA Memory [0..1]            */ &bslash;&n;                &t;(_PCMCIA (Nb) + 3*PCMCIAPrtSp)
DECL|macro|_PCMCIA0
mdefine_line|#define _PCMCIA0&t;_PCMCIA (0)&t;/* PCMCIA 0                        */
DECL|macro|_PCMCIA0IO
mdefine_line|#define _PCMCIA0IO&t;_PCMCIAIO (0)&t;/* PCMCIA 0 I/O                    */
DECL|macro|_PCMCIA0Attr
mdefine_line|#define _PCMCIA0Attr&t;_PCMCIAAttr (0)&t;/* PCMCIA 0 Attribute              */
DECL|macro|_PCMCIA0Mem
mdefine_line|#define _PCMCIA0Mem&t;_PCMCIAMem (0)&t;/* PCMCIA 0 Memory                 */
DECL|macro|_PCMCIA1
mdefine_line|#define _PCMCIA1&t;_PCMCIA (1)&t;/* PCMCIA 1                        */
DECL|macro|_PCMCIA1IO
mdefine_line|#define _PCMCIA1IO&t;_PCMCIAIO (1)&t;/* PCMCIA 1 I/O                    */
DECL|macro|_PCMCIA1Attr
mdefine_line|#define _PCMCIA1Attr&t;_PCMCIAAttr (1)&t;/* PCMCIA 1 Attribute              */
DECL|macro|_PCMCIA1Mem
mdefine_line|#define _PCMCIA1Mem&t;_PCMCIAMem (1)&t;/* PCMCIA 1 Memory                 */
macro_line|#if LANGUAGE == C
DECL|typedef|PCMCIAPrtType
r_typedef
id|Quad
id|PCMCIAPrtType
(braket
id|PCMCIAPrtSp
op_div
r_sizeof
(paren
id|Quad
)paren
)braket
suffix:semicolon
DECL|typedef|PCMCIAType
r_typedef
id|PCMCIAPrtType
id|PCMCIAType
(braket
id|PCMCIASp
op_div
id|PCMCIAPrtSp
)braket
suffix:semicolon
DECL|macro|PCMCIA0
mdefine_line|#define PCMCIA0 &t;        &t;/* PCMCIA 0                        */ &bslash;&n;                &t;(*((PCMCIAType *) io_p2v (_PCMCIA0)))
DECL|macro|PCMCIA0IO
mdefine_line|#define PCMCIA0IO&t;        &t;/* PCMCIA 0 I/O                    */ &bslash;&n;                &t;(*((PCMCIAPrtType *) io_p2v (_PCMCIA0IO)))
DECL|macro|PCMCIA0Attr
mdefine_line|#define PCMCIA0Attr&t;        &t;/* PCMCIA 0 Attribute              */ &bslash;&n;                &t;(*((PCMCIAPrtType *) io_p2v (_PCMCIA0Attr)))
DECL|macro|PCMCIA0Mem
mdefine_line|#define PCMCIA0Mem&t;        &t;/* PCMCIA 0 Memory                 */ &bslash;&n;                &t;(*((PCMCIAPrtType *) io_p2v (_PCMCIA0Mem)))
DECL|macro|PCMCIA1
mdefine_line|#define PCMCIA1 &t;        &t;/* PCMCIA 1                        */ &bslash;&n;                &t;(*((PCMCIAType *) io_p2v (_PCMCIA1)))
DECL|macro|PCMCIA1IO
mdefine_line|#define PCMCIA1IO&t;        &t;/* PCMCIA 1 I/O                    */ &bslash;&n;                &t;(*((PCMCIAPrtType *) io_p2v (_PCMCIA1IO)))
DECL|macro|PCMCIA1Attr
mdefine_line|#define PCMCIA1Attr&t;        &t;/* PCMCIA 1 Attribute              */ &bslash;&n;                &t;(*((PCMCIAPrtType *) io_p2v (_PCMCIA1Attr)))
DECL|macro|PCMCIA1Mem
mdefine_line|#define PCMCIA1Mem&t;        &t;/* PCMCIA 1 Memory                 */ &bslash;&n;                &t;(*((PCMCIAPrtType *) io_p2v (_PCMCIA1Mem)))
macro_line|#endif /* LANGUAGE == C */
multiline_comment|/*&n; * Universal Serial Bus (USB) Device Controller (UDC) control registers&n; *&n; * Registers&n; *    Ser0UDCCR &t;Serial port 0 Universal Serial Bus (USB) Device&n; *              &t;Controller (UDC) Control Register (read/write).&n; *    Ser0UDCAR &t;Serial port 0 Universal Serial Bus (USB) Device&n; *              &t;Controller (UDC) Address Register (read/write).&n; *    Ser0UDCOMP&t;Serial port 0 Universal Serial Bus (USB) Device&n; *              &t;Controller (UDC) Output Maximum Packet size register&n; *              &t;(read/write).&n; *    Ser0UDCIMP&t;Serial port 0 Universal Serial Bus (USB) Device&n; *              &t;Controller (UDC) Input Maximum Packet size register&n; *              &t;(read/write).&n; *    Ser0UDCCS0&t;Serial port 0 Universal Serial Bus (USB) Device&n; *              &t;Controller (UDC) Control/Status register end-point 0&n; *              &t;(read/write).&n; *    Ser0UDCCS1&t;Serial port 0 Universal Serial Bus (USB) Device&n; *              &t;Controller (UDC) Control/Status register end-point 1&n; *              &t;(output, read/write).&n; *    Ser0UDCCS2&t;Serial port 0 Universal Serial Bus (USB) Device&n; *              &t;Controller (UDC) Control/Status register end-point 2&n; *              &t;(input, read/write).&n; *    Ser0UDCD0 &t;Serial port 0 Universal Serial Bus (USB) Device&n; *              &t;Controller (UDC) Data register end-point 0&n; *              &t;(read/write).&n; *    Ser0UDCWC &t;Serial port 0 Universal Serial Bus (USB) Device&n; *              &t;Controller (UDC) Write Count register end-point 0&n; *              &t;(read).&n; *    Ser0UDCDR &t;Serial port 0 Universal Serial Bus (USB) Device&n; *              &t;Controller (UDC) Data Register (read/write).&n; *    Ser0UDCSR &t;Serial port 0 Universal Serial Bus (USB) Device&n; *              &t;Controller (UDC) Status Register (read/write).&n; */
DECL|macro|_Ser0UDCCR
mdefine_line|#define _Ser0UDCCR&t;0x80000000&t;/* Ser. port 0 UDC Control Reg.    */
DECL|macro|_Ser0UDCAR
mdefine_line|#define _Ser0UDCAR&t;0x80000004&t;/* Ser. port 0 UDC Address Reg.    */
DECL|macro|_Ser0UDCOMP
mdefine_line|#define _Ser0UDCOMP&t;0x80000008&t;/* Ser. port 0 UDC Output Maximum  */
multiline_comment|/* Packet size reg.                */
DECL|macro|_Ser0UDCIMP
mdefine_line|#define _Ser0UDCIMP&t;0x8000000C&t;/* Ser. port 0 UDC Input Maximum   */
multiline_comment|/* Packet size reg.                */
DECL|macro|_Ser0UDCCS0
mdefine_line|#define _Ser0UDCCS0&t;0x80000010&t;/* Ser. port 0 UDC Control/Status  */
multiline_comment|/* reg. end-point 0                */
DECL|macro|_Ser0UDCCS1
mdefine_line|#define _Ser0UDCCS1&t;0x80000014&t;/* Ser. port 0 UDC Control/Status  */
multiline_comment|/* reg. end-point 1 (output)       */
DECL|macro|_Ser0UDCCS2
mdefine_line|#define _Ser0UDCCS2&t;0x80000018&t;/* Ser. port 0 UDC Control/Status  */
multiline_comment|/* reg. end-point 2 (input)        */
DECL|macro|_Ser0UDCD0
mdefine_line|#define _Ser0UDCD0&t;0x8000001C&t;/* Ser. port 0 UDC Data reg.       */
multiline_comment|/* end-point 0                     */
DECL|macro|_Ser0UDCWC
mdefine_line|#define _Ser0UDCWC&t;0x80000020&t;/* Ser. port 0 UDC Write Count     */
multiline_comment|/* reg. end-point 0                */
DECL|macro|_Ser0UDCDR
mdefine_line|#define _Ser0UDCDR&t;0x80000028&t;/* Ser. port 0 UDC Data Reg.       */
DECL|macro|_Ser0UDCSR
mdefine_line|#define _Ser0UDCSR&t;0x80000030&t;/* Ser. port 0 UDC Status Reg.     */
macro_line|#if LANGUAGE == C
DECL|macro|Ser0UDCCR
mdefine_line|#define Ser0UDCCR&t;        &t;/* Ser. port 0 UDC Control Reg.    */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser0UDCCR)))
DECL|macro|Ser0UDCAR
mdefine_line|#define Ser0UDCAR&t;        &t;/* Ser. port 0 UDC Address Reg.    */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser0UDCAR)))
DECL|macro|Ser0UDCOMP
mdefine_line|#define Ser0UDCOMP&t;        &t;/* Ser. port 0 UDC Output Maximum  */ &bslash;&n;                &t;        &t;/* Packet size reg.                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser0UDCOMP)))
DECL|macro|Ser0UDCIMP
mdefine_line|#define Ser0UDCIMP&t;        &t;/* Ser. port 0 UDC Input Maximum   */ &bslash;&n;                &t;        &t;/* Packet size reg.                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser0UDCIMP)))
DECL|macro|Ser0UDCCS0
mdefine_line|#define Ser0UDCCS0&t;        &t;/* Ser. port 0 UDC Control/Status  */ &bslash;&n;                &t;        &t;/* reg. end-point 0                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser0UDCCS0)))
DECL|macro|Ser0UDCCS1
mdefine_line|#define Ser0UDCCS1&t;        &t;/* Ser. port 0 UDC Control/Status  */ &bslash;&n;                &t;        &t;/* reg. end-point 1 (output)       */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser0UDCCS1)))
DECL|macro|Ser0UDCCS2
mdefine_line|#define Ser0UDCCS2&t;        &t;/* Ser. port 0 UDC Control/Status  */ &bslash;&n;                &t;        &t;/* reg. end-point 2 (input)        */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser0UDCCS2)))
DECL|macro|Ser0UDCD0
mdefine_line|#define Ser0UDCD0&t;        &t;/* Ser. port 0 UDC Data reg.       */ &bslash;&n;                &t;        &t;/* end-point 0                     */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser0UDCD0)))
DECL|macro|Ser0UDCWC
mdefine_line|#define Ser0UDCWC&t;        &t;/* Ser. port 0 UDC Write Count     */ &bslash;&n;                &t;        &t;/* reg. end-point 0                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser0UDCWC)))
DECL|macro|Ser0UDCDR
mdefine_line|#define Ser0UDCDR&t;        &t;/* Ser. port 0 UDC Data Reg.       */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser0UDCDR)))
DECL|macro|Ser0UDCSR
mdefine_line|#define Ser0UDCSR&t;        &t;/* Ser. port 0 UDC Status Reg.     */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser0UDCSR)))
macro_line|#endif /* LANGUAGE == C */
DECL|macro|UDCCR_UDD
mdefine_line|#define UDCCR_UDD&t;0x00000001&t;/* UDC Disable                     */
DECL|macro|UDCCR_UDA
mdefine_line|#define UDCCR_UDA&t;0x00000002&t;/* UDC Active (read)               */
DECL|macro|UDCCR_RESIM
mdefine_line|#define UDCCR_RESIM&t;0x00000004&t;/* Resume Interrupt Mask, per errata */
DECL|macro|UDCCR_EIM
mdefine_line|#define UDCCR_EIM&t;0x00000008&t;/* End-point 0 Interrupt Mask      */
multiline_comment|/* (disable)                       */
DECL|macro|UDCCR_RIM
mdefine_line|#define UDCCR_RIM&t;0x00000010&t;/* Receive Interrupt Mask          */
multiline_comment|/* (disable)                       */
DECL|macro|UDCCR_TIM
mdefine_line|#define UDCCR_TIM&t;0x00000020&t;/* Transmit Interrupt Mask         */
multiline_comment|/* (disable)                       */
DECL|macro|UDCCR_SRM
mdefine_line|#define UDCCR_SRM&t;0x00000040&t;/* Suspend/Resume interrupt Mask   */
multiline_comment|/* (disable)                       */
DECL|macro|UDCCR_SUSIM
mdefine_line|#define UDCCR_SUSIM&t;UDCCR_SRM&t;/* Per errata, SRM just masks suspend */
DECL|macro|UDCCR_REM
mdefine_line|#define UDCCR_REM&t;0x00000080&t;/* REset interrupt Mask (disable)  */
DECL|macro|UDCAR_ADD
mdefine_line|#define UDCAR_ADD&t;Fld (7, 0)&t;/* function ADDress                */
DECL|macro|UDCOMP_OUTMAXP
mdefine_line|#define UDCOMP_OUTMAXP&t;Fld (8, 0)&t;/* OUTput MAXimum Packet size - 1  */
multiline_comment|/* [byte]                          */
DECL|macro|UDCOMP_OutMaxPkt
mdefine_line|#define UDCOMP_OutMaxPkt(Size)  &t;/* Output Maximum Packet size      */ &bslash;&n;                &t;        &t;/* [1..256 byte]                   */ &bslash;&n;                &t;(((Size) - 1) &lt;&lt; FShft (UDCOMP_OUTMAXP))
DECL|macro|UDCIMP_INMAXP
mdefine_line|#define UDCIMP_INMAXP&t;Fld (8, 0)&t;/* INput MAXimum Packet size - 1   */
multiline_comment|/* [byte]                          */
DECL|macro|UDCIMP_InMaxPkt
mdefine_line|#define UDCIMP_InMaxPkt(Size)   &t;/* Input Maximum Packet size       */ &bslash;&n;                &t;        &t;/* [1..256 byte]                   */ &bslash;&n;                &t;(((Size) - 1) &lt;&lt; FShft (UDCIMP_INMAXP))
DECL|macro|UDCCS0_OPR
mdefine_line|#define UDCCS0_OPR&t;0x00000001&t;/* Output Packet Ready (read)      */
DECL|macro|UDCCS0_IPR
mdefine_line|#define UDCCS0_IPR&t;0x00000002&t;/* Input Packet Ready              */
DECL|macro|UDCCS0_SST
mdefine_line|#define UDCCS0_SST&t;0x00000004&t;/* Sent STall                      */
DECL|macro|UDCCS0_FST
mdefine_line|#define UDCCS0_FST&t;0x00000008&t;/* Force STall                     */
DECL|macro|UDCCS0_DE
mdefine_line|#define UDCCS0_DE&t;0x00000010&t;/* Data End                        */
DECL|macro|UDCCS0_SE
mdefine_line|#define UDCCS0_SE&t;0x00000020&t;/* Setup End (read)                */
DECL|macro|UDCCS0_SO
mdefine_line|#define UDCCS0_SO&t;0x00000040&t;/* Serviced Output packet ready    */
multiline_comment|/* (write)                         */
DECL|macro|UDCCS0_SSE
mdefine_line|#define UDCCS0_SSE&t;0x00000080&t;/* Serviced Setup End (write)      */
DECL|macro|UDCCS1_RFS
mdefine_line|#define UDCCS1_RFS&t;0x00000001&t;/* Receive FIFO 12-bytes or more   */
multiline_comment|/* Service request (read)          */
DECL|macro|UDCCS1_RPC
mdefine_line|#define UDCCS1_RPC&t;0x00000002&t;/* Receive Packet Complete         */
DECL|macro|UDCCS1_RPE
mdefine_line|#define UDCCS1_RPE&t;0x00000004&t;/* Receive Packet Error (read)     */
DECL|macro|UDCCS1_SST
mdefine_line|#define UDCCS1_SST&t;0x00000008&t;/* Sent STall                      */
DECL|macro|UDCCS1_FST
mdefine_line|#define UDCCS1_FST&t;0x00000010&t;/* Force STall                     */
DECL|macro|UDCCS1_RNE
mdefine_line|#define UDCCS1_RNE&t;0x00000020&t;/* Receive FIFO Not Empty (read)   */
DECL|macro|UDCCS2_TFS
mdefine_line|#define UDCCS2_TFS&t;0x00000001&t;/* Transmit FIFO 8-bytes or less   */
multiline_comment|/* Service request (read)          */
DECL|macro|UDCCS2_TPC
mdefine_line|#define UDCCS2_TPC&t;0x00000002&t;/* Transmit Packet Complete        */
DECL|macro|UDCCS2_TPE
mdefine_line|#define UDCCS2_TPE&t;0x00000004&t;/* Transmit Packet Error (read)    */
DECL|macro|UDCCS2_TUR
mdefine_line|#define UDCCS2_TUR&t;0x00000008&t;/* Transmit FIFO Under-Run         */
DECL|macro|UDCCS2_SST
mdefine_line|#define UDCCS2_SST&t;0x00000010&t;/* Sent STall                      */
DECL|macro|UDCCS2_FST
mdefine_line|#define UDCCS2_FST&t;0x00000020&t;/* Force STall                     */
DECL|macro|UDCD0_DATA
mdefine_line|#define UDCD0_DATA&t;Fld (8, 0)&t;/* receive/transmit DATA FIFOs     */
DECL|macro|UDCWC_WC
mdefine_line|#define UDCWC_WC&t;Fld (4, 0)&t;/* Write Count                     */
DECL|macro|UDCDR_DATA
mdefine_line|#define UDCDR_DATA&t;Fld (8, 0)&t;/* receive/transmit DATA FIFOs     */
DECL|macro|UDCSR_EIR
mdefine_line|#define UDCSR_EIR&t;0x00000001&t;/* End-point 0 Interrupt Request   */
DECL|macro|UDCSR_RIR
mdefine_line|#define UDCSR_RIR&t;0x00000002&t;/* Receive Interrupt Request       */
DECL|macro|UDCSR_TIR
mdefine_line|#define UDCSR_TIR&t;0x00000004&t;/* Transmit Interrupt Request      */
DECL|macro|UDCSR_SUSIR
mdefine_line|#define UDCSR_SUSIR&t;0x00000008&t;/* SUSpend Interrupt Request       */
DECL|macro|UDCSR_RESIR
mdefine_line|#define UDCSR_RESIR&t;0x00000010&t;/* RESume Interrupt Request        */
DECL|macro|UDCSR_RSTIR
mdefine_line|#define UDCSR_RSTIR&t;0x00000020&t;/* ReSeT Interrupt Request         */
multiline_comment|/*&n; * Universal Asynchronous Receiver/Transmitter (UART) control registers&n; *&n; * Registers&n; *    Ser1UTCR0 &t;Serial port 1 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Control Register 0&n; *              &t;(read/write).&n; *    Ser1UTCR1 &t;Serial port 1 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Control Register 1&n; *              &t;(read/write).&n; *    Ser1UTCR2 &t;Serial port 1 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Control Register 2&n; *              &t;(read/write).&n; *    Ser1UTCR3 &t;Serial port 1 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Control Register 3&n; *              &t;(read/write).&n; *    Ser1UTDR  &t;Serial port 1 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Data Register&n; *              &t;(read/write).&n; *    Ser1UTSR0 &t;Serial port 1 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Status Register 0&n; *              &t;(read/write).&n; *    Ser1UTSR1 &t;Serial port 1 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Status Register 1 (read).&n; *&n; *    Ser2UTCR0 &t;Serial port 2 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Control Register 0&n; *              &t;(read/write).&n; *    Ser2UTCR1 &t;Serial port 2 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Control Register 1&n; *              &t;(read/write).&n; *    Ser2UTCR2 &t;Serial port 2 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Control Register 2&n; *              &t;(read/write).&n; *    Ser2UTCR3 &t;Serial port 2 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Control Register 3&n; *              &t;(read/write).&n; *    Ser2UTCR4 &t;Serial port 2 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Control Register 4&n; *              &t;(read/write).&n; *    Ser2UTDR  &t;Serial port 2 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Data Register&n; *              &t;(read/write).&n; *    Ser2UTSR0 &t;Serial port 2 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Status Register 0&n; *              &t;(read/write).&n; *    Ser2UTSR1 &t;Serial port 2 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Status Register 1 (read).&n; *&n; *    Ser3UTCR0 &t;Serial port 3 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Control Register 0&n; *              &t;(read/write).&n; *    Ser3UTCR1 &t;Serial port 3 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Control Register 1&n; *              &t;(read/write).&n; *    Ser3UTCR2 &t;Serial port 3 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Control Register 2&n; *              &t;(read/write).&n; *    Ser3UTCR3 &t;Serial port 3 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Control Register 3&n; *              &t;(read/write).&n; *    Ser3UTDR  &t;Serial port 3 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Data Register&n; *              &t;(read/write).&n; *    Ser3UTSR0 &t;Serial port 3 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Status Register 0&n; *              &t;(read/write).&n; *    Ser3UTSR1 &t;Serial port 3 Universal Asynchronous&n; *              &t;Receiver/Transmitter (UART) Status Register 1 (read).&n; *&n; * Clocks&n; *    fxtl, Txtl&t;Frequency, period of the system crystal (3.6864 MHz&n; *              &t;or 3.5795 MHz).&n; *    fua, Tua  &t;Frequency, period of the UART communication.&n; */
DECL|macro|_UTCR0
mdefine_line|#define _UTCR0(Nb)&t;        &t;/* UART Control Reg. 0 [1..3]      */ &bslash;&n;                &t;(0x80010000 + ((Nb) - 1)*0x00020000)
DECL|macro|_UTCR1
mdefine_line|#define _UTCR1(Nb)&t;        &t;/* UART Control Reg. 1 [1..3]      */ &bslash;&n;                &t;(0x80010004 + ((Nb) - 1)*0x00020000)
DECL|macro|_UTCR2
mdefine_line|#define _UTCR2(Nb)&t;        &t;/* UART Control Reg. 2 [1..3]      */ &bslash;&n;                &t;(0x80010008 + ((Nb) - 1)*0x00020000)
DECL|macro|_UTCR3
mdefine_line|#define _UTCR3(Nb)&t;        &t;/* UART Control Reg. 3 [1..3]      */ &bslash;&n;                &t;(0x8001000C + ((Nb) - 1)*0x00020000)
DECL|macro|_UTCR4
mdefine_line|#define _UTCR4(Nb)&t;        &t;/* UART Control Reg. 4 [2]         */ &bslash;&n;                &t;(0x80010010 + ((Nb) - 1)*0x00020000)
DECL|macro|_UTDR
mdefine_line|#define _UTDR(Nb)&t;        &t;/* UART Data Reg. [1..3]           */ &bslash;&n;                &t;(0x80010014 + ((Nb) - 1)*0x00020000)
DECL|macro|_UTSR0
mdefine_line|#define _UTSR0(Nb)&t;        &t;/* UART Status Reg. 0 [1..3]       */ &bslash;&n;                &t;(0x8001001C + ((Nb) - 1)*0x00020000)
DECL|macro|_UTSR1
mdefine_line|#define _UTSR1(Nb)&t;        &t;/* UART Status Reg. 1 [1..3]       */ &bslash;&n;                &t;(0x80010020 + ((Nb) - 1)*0x00020000)
DECL|macro|_Ser1UTCR0
mdefine_line|#define _Ser1UTCR0&t;_UTCR0 (1)&t;/* Ser. port 1 UART Control Reg. 0 */
DECL|macro|_Ser1UTCR1
mdefine_line|#define _Ser1UTCR1&t;_UTCR1 (1)&t;/* Ser. port 1 UART Control Reg. 1 */
DECL|macro|_Ser1UTCR2
mdefine_line|#define _Ser1UTCR2&t;_UTCR2 (1)&t;/* Ser. port 1 UART Control Reg. 2 */
DECL|macro|_Ser1UTCR3
mdefine_line|#define _Ser1UTCR3&t;_UTCR3 (1)&t;/* Ser. port 1 UART Control Reg. 3 */
DECL|macro|_Ser1UTDR
mdefine_line|#define _Ser1UTDR&t;_UTDR (1)&t;/* Ser. port 1 UART Data Reg.      */
DECL|macro|_Ser1UTSR0
mdefine_line|#define _Ser1UTSR0&t;_UTSR0 (1)&t;/* Ser. port 1 UART Status Reg. 0  */
DECL|macro|_Ser1UTSR1
mdefine_line|#define _Ser1UTSR1&t;_UTSR1 (1)&t;/* Ser. port 1 UART Status Reg. 1  */
DECL|macro|_Ser2UTCR0
mdefine_line|#define _Ser2UTCR0&t;_UTCR0 (2)&t;/* Ser. port 2 UART Control Reg. 0 */
DECL|macro|_Ser2UTCR1
mdefine_line|#define _Ser2UTCR1&t;_UTCR1 (2)&t;/* Ser. port 2 UART Control Reg. 1 */
DECL|macro|_Ser2UTCR2
mdefine_line|#define _Ser2UTCR2&t;_UTCR2 (2)&t;/* Ser. port 2 UART Control Reg. 2 */
DECL|macro|_Ser2UTCR3
mdefine_line|#define _Ser2UTCR3&t;_UTCR3 (2)&t;/* Ser. port 2 UART Control Reg. 3 */
DECL|macro|_Ser2UTCR4
mdefine_line|#define _Ser2UTCR4&t;_UTCR4 (2)&t;/* Ser. port 2 UART Control Reg. 4 */
DECL|macro|_Ser2UTDR
mdefine_line|#define _Ser2UTDR&t;_UTDR (2)&t;/* Ser. port 2 UART Data Reg.      */
DECL|macro|_Ser2UTSR0
mdefine_line|#define _Ser2UTSR0&t;_UTSR0 (2)&t;/* Ser. port 2 UART Status Reg. 0  */
DECL|macro|_Ser2UTSR1
mdefine_line|#define _Ser2UTSR1&t;_UTSR1 (2)&t;/* Ser. port 2 UART Status Reg. 1  */
DECL|macro|_Ser3UTCR0
mdefine_line|#define _Ser3UTCR0&t;_UTCR0 (3)&t;/* Ser. port 3 UART Control Reg. 0 */
DECL|macro|_Ser3UTCR1
mdefine_line|#define _Ser3UTCR1&t;_UTCR1 (3)&t;/* Ser. port 3 UART Control Reg. 1 */
DECL|macro|_Ser3UTCR2
mdefine_line|#define _Ser3UTCR2&t;_UTCR2 (3)&t;/* Ser. port 3 UART Control Reg. 2 */
DECL|macro|_Ser3UTCR3
mdefine_line|#define _Ser3UTCR3&t;_UTCR3 (3)&t;/* Ser. port 3 UART Control Reg. 3 */
DECL|macro|_Ser3UTDR
mdefine_line|#define _Ser3UTDR&t;_UTDR (3)&t;/* Ser. port 3 UART Data Reg.      */
DECL|macro|_Ser3UTSR0
mdefine_line|#define _Ser3UTSR0&t;_UTSR0 (3)&t;/* Ser. port 3 UART Status Reg. 0  */
DECL|macro|_Ser3UTSR1
mdefine_line|#define _Ser3UTSR1&t;_UTSR1 (3)&t;/* Ser. port 3 UART Status Reg. 1  */
multiline_comment|/*&n; * Register offsets&n; */
DECL|macro|UTCR0
mdefine_line|#define UTCR0&t;&t;0x00
DECL|macro|UTCR1
mdefine_line|#define UTCR1&t;&t;0x04
DECL|macro|UTCR2
mdefine_line|#define UTCR2&t;&t;0x08
DECL|macro|UTCR3
mdefine_line|#define UTCR3&t;&t;0x0c
DECL|macro|UTDR
mdefine_line|#define UTDR&t;&t;0x14
DECL|macro|UTSR0
mdefine_line|#define UTSR0&t;&t;0x1c
DECL|macro|UTSR1
mdefine_line|#define UTSR1&t;&t;0x20
macro_line|#if LANGUAGE == C
DECL|macro|Ser1UTCR0
mdefine_line|#define Ser1UTCR0&t;        &t;/* Ser. port 1 UART Control Reg. 0 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser1UTCR0)))
DECL|macro|Ser1UTCR1
mdefine_line|#define Ser1UTCR1&t;        &t;/* Ser. port 1 UART Control Reg. 1 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser1UTCR1)))
DECL|macro|Ser1UTCR2
mdefine_line|#define Ser1UTCR2&t;        &t;/* Ser. port 1 UART Control Reg. 2 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser1UTCR2)))
DECL|macro|Ser1UTCR3
mdefine_line|#define Ser1UTCR3&t;        &t;/* Ser. port 1 UART Control Reg. 3 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser1UTCR3)))
DECL|macro|Ser1UTDR
mdefine_line|#define Ser1UTDR&t;        &t;/* Ser. port 1 UART Data Reg.      */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser1UTDR)))
DECL|macro|Ser1UTSR0
mdefine_line|#define Ser1UTSR0&t;        &t;/* Ser. port 1 UART Status Reg. 0  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser1UTSR0)))
DECL|macro|Ser1UTSR1
mdefine_line|#define Ser1UTSR1&t;        &t;/* Ser. port 1 UART Status Reg. 1  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser1UTSR1)))
DECL|macro|Ser2UTCR0
mdefine_line|#define Ser2UTCR0&t;        &t;/* Ser. port 2 UART Control Reg. 0 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser2UTCR0)))
DECL|macro|Ser2UTCR1
mdefine_line|#define Ser2UTCR1&t;        &t;/* Ser. port 2 UART Control Reg. 1 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser2UTCR1)))
DECL|macro|Ser2UTCR2
mdefine_line|#define Ser2UTCR2&t;        &t;/* Ser. port 2 UART Control Reg. 2 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser2UTCR2)))
DECL|macro|Ser2UTCR3
mdefine_line|#define Ser2UTCR3&t;        &t;/* Ser. port 2 UART Control Reg. 3 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser2UTCR3)))
DECL|macro|Ser2UTCR4
mdefine_line|#define Ser2UTCR4&t;        &t;/* Ser. port 2 UART Control Reg. 4 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser2UTCR4)))
DECL|macro|Ser2UTDR
mdefine_line|#define Ser2UTDR&t;        &t;/* Ser. port 2 UART Data Reg.      */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser2UTDR)))
DECL|macro|Ser2UTSR0
mdefine_line|#define Ser2UTSR0&t;        &t;/* Ser. port 2 UART Status Reg. 0  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser2UTSR0)))
DECL|macro|Ser2UTSR1
mdefine_line|#define Ser2UTSR1&t;        &t;/* Ser. port 2 UART Status Reg. 1  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser2UTSR1)))
DECL|macro|Ser3UTCR0
mdefine_line|#define Ser3UTCR0&t;        &t;/* Ser. port 3 UART Control Reg. 0 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser3UTCR0)))
DECL|macro|Ser3UTCR1
mdefine_line|#define Ser3UTCR1&t;        &t;/* Ser. port 3 UART Control Reg. 1 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser3UTCR1)))
DECL|macro|Ser3UTCR2
mdefine_line|#define Ser3UTCR2&t;        &t;/* Ser. port 3 UART Control Reg. 2 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser3UTCR2)))
DECL|macro|Ser3UTCR3
mdefine_line|#define Ser3UTCR3&t;        &t;/* Ser. port 3 UART Control Reg. 3 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser3UTCR3)))
DECL|macro|Ser3UTDR
mdefine_line|#define Ser3UTDR&t;        &t;/* Ser. port 3 UART Data Reg.      */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser3UTDR)))
DECL|macro|Ser3UTSR0
mdefine_line|#define Ser3UTSR0&t;        &t;/* Ser. port 3 UART Status Reg. 0  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser3UTSR0)))
DECL|macro|Ser3UTSR1
mdefine_line|#define Ser3UTSR1&t;        &t;/* Ser. port 3 UART Status Reg. 1  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser3UTSR1)))
macro_line|#elif LANGUAGE == Assembly
DECL|macro|Ser1UTCR0
mdefine_line|#define Ser1UTCR0&t;( io_p2v (_Ser1UTCR0))
DECL|macro|Ser1UTCR1
mdefine_line|#define Ser1UTCR1&t;( io_p2v (_Ser1UTCR1))
DECL|macro|Ser1UTCR2
mdefine_line|#define Ser1UTCR2&t;( io_p2v (_Ser1UTCR2))
DECL|macro|Ser1UTCR3
mdefine_line|#define Ser1UTCR3&t;( io_p2v (_Ser1UTCR3))
DECL|macro|Ser1UTDR
mdefine_line|#define Ser1UTDR&t;( io_p2v (_Ser1UTDR))
DECL|macro|Ser1UTSR0
mdefine_line|#define Ser1UTSR0&t;( io_p2v (_Ser1UTSR0))
DECL|macro|Ser1UTSR1
mdefine_line|#define Ser1UTSR1&t;( io_p2v (_Ser1UTSR1))
DECL|macro|Ser2UTCR0
mdefine_line|#define Ser2UTCR0&t;( io_p2v (_Ser2UTCR0))
DECL|macro|Ser2UTCR1
mdefine_line|#define Ser2UTCR1&t;( io_p2v (_Ser2UTCR1))
DECL|macro|Ser2UTCR2
mdefine_line|#define Ser2UTCR2&t;( io_p2v (_Ser2UTCR2))
DECL|macro|Ser2UTCR3
mdefine_line|#define Ser2UTCR3&t;( io_p2v (_Ser2UTCR3))
DECL|macro|Ser2UTCR4
mdefine_line|#define Ser2UTCR4&t;( io_p2v (_Ser2UTCR4))
DECL|macro|Ser2UTDR
mdefine_line|#define Ser2UTDR&t;( io_p2v (_Ser2UTDR))
DECL|macro|Ser2UTSR0
mdefine_line|#define Ser2UTSR0&t;( io_p2v (_Ser2UTSR0))
DECL|macro|Ser2UTSR1
mdefine_line|#define Ser2UTSR1&t;( io_p2v (_Ser2UTSR1))
DECL|macro|Ser3UTCR0
mdefine_line|#define Ser3UTCR0&t;( io_p2v (_Ser3UTCR0))
DECL|macro|Ser3UTCR1
mdefine_line|#define Ser3UTCR1&t;( io_p2v (_Ser3UTCR1))
DECL|macro|Ser3UTCR2
mdefine_line|#define Ser3UTCR2&t;( io_p2v (_Ser3UTCR2))
DECL|macro|Ser3UTCR3
mdefine_line|#define Ser3UTCR3&t;( io_p2v (_Ser3UTCR3))
DECL|macro|Ser3UTDR
mdefine_line|#define Ser3UTDR&t;( io_p2v (_Ser3UTDR))
DECL|macro|Ser3UTSR0
mdefine_line|#define Ser3UTSR0&t;( io_p2v (_Ser3UTSR0))
DECL|macro|Ser3UTSR1
mdefine_line|#define Ser3UTSR1&t;( io_p2v (_Ser3UTSR1))
macro_line|#endif /* LANGUAGE == C */
DECL|macro|UTCR0_PE
mdefine_line|#define UTCR0_PE&t;0x00000001&t;/* Parity Enable                   */
DECL|macro|UTCR0_OES
mdefine_line|#define UTCR0_OES&t;0x00000002&t;/* Odd/Even parity Select          */
DECL|macro|UTCR0_OddPar
mdefine_line|#define UTCR0_OddPar&t;(UTCR0_OES*0)&t;/*  Odd Parity                     */
DECL|macro|UTCR0_EvenPar
mdefine_line|#define UTCR0_EvenPar&t;(UTCR0_OES*1)&t;/*  Even Parity                    */
DECL|macro|UTCR0_SBS
mdefine_line|#define UTCR0_SBS&t;0x00000004&t;/* Stop Bit Select                 */
DECL|macro|UTCR0_1StpBit
mdefine_line|#define UTCR0_1StpBit&t;(UTCR0_SBS*0)&t;/*  1 Stop Bit per frame           */
DECL|macro|UTCR0_2StpBit
mdefine_line|#define UTCR0_2StpBit&t;(UTCR0_SBS*1)&t;/*  2 Stop Bits per frame          */
DECL|macro|UTCR0_DSS
mdefine_line|#define UTCR0_DSS&t;0x00000008&t;/* Data Size Select                */
DECL|macro|UTCR0_7BitData
mdefine_line|#define UTCR0_7BitData&t;(UTCR0_DSS*0)&t;/*  7-Bit Data                     */
DECL|macro|UTCR0_8BitData
mdefine_line|#define UTCR0_8BitData&t;(UTCR0_DSS*1)&t;/*  8-Bit Data                     */
DECL|macro|UTCR0_SCE
mdefine_line|#define UTCR0_SCE&t;0x00000010&t;/* Sample Clock Enable             */
multiline_comment|/* (ser. port 1: GPIO [18],        */
multiline_comment|/* ser. port 3: GPIO [20])         */
DECL|macro|UTCR0_RCE
mdefine_line|#define UTCR0_RCE&t;0x00000020&t;/* Receive Clock Edge select       */
DECL|macro|UTCR0_RcRsEdg
mdefine_line|#define UTCR0_RcRsEdg&t;(UTCR0_RCE*0)&t;/*  Receive clock Rising-Edge      */
DECL|macro|UTCR0_RcFlEdg
mdefine_line|#define UTCR0_RcFlEdg&t;(UTCR0_RCE*1)&t;/*  Receive clock Falling-Edge     */
DECL|macro|UTCR0_TCE
mdefine_line|#define UTCR0_TCE&t;0x00000040&t;/* Transmit Clock Edge select      */
DECL|macro|UTCR0_TrRsEdg
mdefine_line|#define UTCR0_TrRsEdg&t;(UTCR0_TCE*0)&t;/*  Transmit clock Rising-Edge     */
DECL|macro|UTCR0_TrFlEdg
mdefine_line|#define UTCR0_TrFlEdg&t;(UTCR0_TCE*1)&t;/*  Transmit clock Falling-Edge    */
DECL|macro|UTCR0_Ser2IrDA
mdefine_line|#define UTCR0_Ser2IrDA&t;        &t;/* Ser. port 2 IrDA settings       */ &bslash;&n;                &t;(UTCR0_1StpBit + UTCR0_8BitData)
DECL|macro|UTCR1_BRD
mdefine_line|#define UTCR1_BRD&t;Fld (4, 0)&t;/* Baud Rate Divisor/16 - 1 [11:8] */
DECL|macro|UTCR2_BRD
mdefine_line|#define UTCR2_BRD&t;Fld (8, 0)&t;/* Baud Rate Divisor/16 - 1  [7:0] */
multiline_comment|/* fua = fxtl/(16*(BRD[11:0] + 1)) */
multiline_comment|/* Tua = 16*(BRD [11:0] + 1)*Txtl  */
DECL|macro|UTCR1_BdRtDiv
mdefine_line|#define UTCR1_BdRtDiv(Div)      &t;/*  Baud Rate Divisor [16..65536]  */ &bslash;&n;                &t;(((Div) - 16)/16 &gt;&gt; FSize (UTCR2_BRD) &lt;&lt; &bslash;&n;                &t; FShft (UTCR1_BRD))
DECL|macro|UTCR2_BdRtDiv
mdefine_line|#define UTCR2_BdRtDiv(Div)      &t;/*  Baud Rate Divisor [16..65536]  */ &bslash;&n;                &t;(((Div) - 16)/16 &amp; FAlnMsk (UTCR2_BRD) &lt;&lt; &bslash;&n;                &t; FShft (UTCR2_BRD))
multiline_comment|/*  fua = fxtl/(16*Floor (Div/16)) */
multiline_comment|/*  Tua = 16*Floor (Div/16)*Txtl   */
DECL|macro|UTCR1_CeilBdRtDiv
mdefine_line|#define UTCR1_CeilBdRtDiv(Div)  &t;/*  Ceil. of BdRtDiv [16..65536]   */ &bslash;&n;                &t;(((Div) - 1)/16 &gt;&gt; FSize (UTCR2_BRD) &lt;&lt; &bslash;&n;                &t; FShft (UTCR1_BRD))
DECL|macro|UTCR2_CeilBdRtDiv
mdefine_line|#define UTCR2_CeilBdRtDiv(Div)  &t;/*  Ceil. of BdRtDiv [16..65536]   */ &bslash;&n;                &t;(((Div) - 1)/16 &amp; FAlnMsk (UTCR2_BRD) &lt;&lt; &bslash;&n;                &t; FShft (UTCR2_BRD))
multiline_comment|/*  fua = fxtl/(16*Ceil (Div/16))  */
multiline_comment|/*  Tua = 16*Ceil (Div/16)*Txtl    */
DECL|macro|UTCR3_RXE
mdefine_line|#define UTCR3_RXE&t;0x00000001&t;/* Receive Enable                  */
DECL|macro|UTCR3_TXE
mdefine_line|#define UTCR3_TXE&t;0x00000002&t;/* Transmit Enable                 */
DECL|macro|UTCR3_BRK
mdefine_line|#define UTCR3_BRK&t;0x00000004&t;/* BReaK mode                      */
DECL|macro|UTCR3_RIE
mdefine_line|#define UTCR3_RIE&t;0x00000008&t;/* Receive FIFO 1/3-to-2/3-full or */
multiline_comment|/* more Interrupt Enable           */
DECL|macro|UTCR3_TIE
mdefine_line|#define UTCR3_TIE&t;0x00000010&t;/* Transmit FIFO 1/2-full or less  */
multiline_comment|/* Interrupt Enable                */
DECL|macro|UTCR3_LBM
mdefine_line|#define UTCR3_LBM&t;0x00000020&t;/* Look-Back Mode                  */
DECL|macro|UTCR3_Ser2IrDA
mdefine_line|#define UTCR3_Ser2IrDA&t;        &t;/* Ser. port 2 IrDA settings (RIE, */ &bslash;&n;                &t;        &t;/* TIE, LBM can be set or cleared) */ &bslash;&n;                &t;(UTCR3_RXE + UTCR3_TXE)
DECL|macro|UTCR4_HSE
mdefine_line|#define UTCR4_HSE&t;0x00000001&t;/* Hewlett-Packard Serial InfraRed */
multiline_comment|/* (HP-SIR) modulation Enable      */
DECL|macro|UTCR4_NRZ
mdefine_line|#define UTCR4_NRZ&t;(UTCR4_HSE*0)&t;/*  Non-Return to Zero modulation  */
DECL|macro|UTCR4_HPSIR
mdefine_line|#define UTCR4_HPSIR&t;(UTCR4_HSE*1)&t;/*  HP-SIR modulation              */
DECL|macro|UTCR4_LPM
mdefine_line|#define UTCR4_LPM&t;0x00000002&t;/* Low-Power Mode                  */
DECL|macro|UTCR4_Z3_16Bit
mdefine_line|#define UTCR4_Z3_16Bit&t;(UTCR4_LPM*0)&t;/*  Zero pulse = 3/16 Bit time     */
DECL|macro|UTCR4_Z1_6us
mdefine_line|#define UTCR4_Z1_6us&t;(UTCR4_LPM*1)&t;/*  Zero pulse = 1.6 us            */
DECL|macro|UTDR_DATA
mdefine_line|#define UTDR_DATA&t;Fld (8, 0)&t;/* receive/transmit DATA FIFOs     */
macro_line|#if 0           &t;        &t;/* Hidden receive FIFO bits        */
mdefine_line|#define UTDR_PRE&t;0x00000100&t;/*  receive PaRity Error (read)    */
mdefine_line|#define UTDR_FRE&t;0x00000200&t;/*  receive FRaming Error (read)   */
mdefine_line|#define UTDR_ROR&t;0x00000400&t;/*  Receive FIFO Over-Run (read)   */
macro_line|#endif /* 0 */
DECL|macro|UTSR0_TFS
mdefine_line|#define UTSR0_TFS&t;0x00000001&t;/* Transmit FIFO 1/2-full or less  */
multiline_comment|/* Service request (read)          */
DECL|macro|UTSR0_RFS
mdefine_line|#define UTSR0_RFS&t;0x00000002&t;/* Receive FIFO 1/3-to-2/3-full or */
multiline_comment|/* more Service request (read)     */
DECL|macro|UTSR0_RID
mdefine_line|#define UTSR0_RID&t;0x00000004&t;/* Receiver IDle                   */
DECL|macro|UTSR0_RBB
mdefine_line|#define UTSR0_RBB&t;0x00000008&t;/* Receive Beginning of Break      */
DECL|macro|UTSR0_REB
mdefine_line|#define UTSR0_REB&t;0x00000010&t;/* Receive End of Break            */
DECL|macro|UTSR0_EIF
mdefine_line|#define UTSR0_EIF&t;0x00000020&t;/* Error In FIFO (read)            */
DECL|macro|UTSR1_TBY
mdefine_line|#define UTSR1_TBY&t;0x00000001&t;/* Transmitter BusY (read)         */
DECL|macro|UTSR1_RNE
mdefine_line|#define UTSR1_RNE&t;0x00000002&t;/* Receive FIFO Not Empty (read)   */
DECL|macro|UTSR1_TNF
mdefine_line|#define UTSR1_TNF&t;0x00000004&t;/* Transmit FIFO Not Full (read)   */
DECL|macro|UTSR1_PRE
mdefine_line|#define UTSR1_PRE&t;0x00000008&t;/* receive PaRity Error (read)     */
DECL|macro|UTSR1_FRE
mdefine_line|#define UTSR1_FRE&t;0x00000010&t;/* receive FRaming Error (read)    */
DECL|macro|UTSR1_ROR
mdefine_line|#define UTSR1_ROR&t;0x00000020&t;/* Receive FIFO Over-Run (read)    */
multiline_comment|/*&n; * Synchronous Data Link Controller (SDLC) control registers&n; *&n; * Registers&n; *    Ser1SDCR0 &t;Serial port 1 Synchronous Data Link Controller (SDLC)&n; *              &t;Control Register 0 (read/write).&n; *    Ser1SDCR1 &t;Serial port 1 Synchronous Data Link Controller (SDLC)&n; *              &t;Control Register 1 (read/write).&n; *    Ser1SDCR2 &t;Serial port 1 Synchronous Data Link Controller (SDLC)&n; *              &t;Control Register 2 (read/write).&n; *    Ser1SDCR3 &t;Serial port 1 Synchronous Data Link Controller (SDLC)&n; *              &t;Control Register 3 (read/write).&n; *    Ser1SDCR4 &t;Serial port 1 Synchronous Data Link Controller (SDLC)&n; *              &t;Control Register 4 (read/write).&n; *    Ser1SDDR  &t;Serial port 1 Synchronous Data Link Controller (SDLC)&n; *              &t;Data Register (read/write).&n; *    Ser1SDSR0 &t;Serial port 1 Synchronous Data Link Controller (SDLC)&n; *              &t;Status Register 0 (read/write).&n; *    Ser1SDSR1 &t;Serial port 1 Synchronous Data Link Controller (SDLC)&n; *              &t;Status Register 1 (read/write).&n; *&n; * Clocks&n; *    fxtl, Txtl&t;Frequency, period of the system crystal (3.6864 MHz&n; *              &t;or 3.5795 MHz).&n; *    fsd, Tsd  &t;Frequency, period of the SDLC communication.&n; */
DECL|macro|_Ser1SDCR0
mdefine_line|#define _Ser1SDCR0&t;0x80020060&t;/* Ser. port 1 SDLC Control Reg. 0 */
DECL|macro|_Ser1SDCR1
mdefine_line|#define _Ser1SDCR1&t;0x80020064&t;/* Ser. port 1 SDLC Control Reg. 1 */
DECL|macro|_Ser1SDCR2
mdefine_line|#define _Ser1SDCR2&t;0x80020068&t;/* Ser. port 1 SDLC Control Reg. 2 */
DECL|macro|_Ser1SDCR3
mdefine_line|#define _Ser1SDCR3&t;0x8002006C&t;/* Ser. port 1 SDLC Control Reg. 3 */
DECL|macro|_Ser1SDCR4
mdefine_line|#define _Ser1SDCR4&t;0x80020070&t;/* Ser. port 1 SDLC Control Reg. 4 */
DECL|macro|_Ser1SDDR
mdefine_line|#define _Ser1SDDR&t;0x80020078&t;/* Ser. port 1 SDLC Data Reg.      */
DECL|macro|_Ser1SDSR0
mdefine_line|#define _Ser1SDSR0&t;0x80020080&t;/* Ser. port 1 SDLC Status Reg. 0  */
DECL|macro|_Ser1SDSR1
mdefine_line|#define _Ser1SDSR1&t;0x80020084&t;/* Ser. port 1 SDLC Status Reg. 1  */
macro_line|#if LANGUAGE == C
DECL|macro|Ser1SDCR0
mdefine_line|#define Ser1SDCR0&t;        &t;/* Ser. port 1 SDLC Control Reg. 0 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser1SDCR0)))
DECL|macro|Ser1SDCR1
mdefine_line|#define Ser1SDCR1&t;        &t;/* Ser. port 1 SDLC Control Reg. 1 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser1SDCR1)))
DECL|macro|Ser1SDCR2
mdefine_line|#define Ser1SDCR2&t;        &t;/* Ser. port 1 SDLC Control Reg. 2 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser1SDCR2)))
DECL|macro|Ser1SDCR3
mdefine_line|#define Ser1SDCR3&t;        &t;/* Ser. port 1 SDLC Control Reg. 3 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser1SDCR3)))
DECL|macro|Ser1SDCR4
mdefine_line|#define Ser1SDCR4&t;        &t;/* Ser. port 1 SDLC Control Reg. 4 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser1SDCR4)))
DECL|macro|Ser1SDDR
mdefine_line|#define Ser1SDDR&t;        &t;/* Ser. port 1 SDLC Data Reg.      */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser1SDDR)))
DECL|macro|Ser1SDSR0
mdefine_line|#define Ser1SDSR0&t;        &t;/* Ser. port 1 SDLC Status Reg. 0  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser1SDSR0)))
DECL|macro|Ser1SDSR1
mdefine_line|#define Ser1SDSR1&t;        &t;/* Ser. port 1 SDLC Status Reg. 1  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser1SDSR1)))
macro_line|#endif /* LANGUAGE == C */
DECL|macro|SDCR0_SUS
mdefine_line|#define SDCR0_SUS&t;0x00000001&t;/* SDLC/UART Select                */
DECL|macro|SDCR0_SDLC
mdefine_line|#define SDCR0_SDLC&t;(SDCR0_SUS*0)&t;/*  SDLC mode (TXD1 &amp; RXD1)        */
DECL|macro|SDCR0_UART
mdefine_line|#define SDCR0_UART&t;(SDCR0_SUS*1)&t;/*  UART mode (TXD1 &amp; RXD1)        */
DECL|macro|SDCR0_SDF
mdefine_line|#define SDCR0_SDF&t;0x00000002&t;/* Single/Double start Flag select */
DECL|macro|SDCR0_SglFlg
mdefine_line|#define SDCR0_SglFlg&t;(SDCR0_SDF*0)&t;/*  Single start Flag              */
DECL|macro|SDCR0_DblFlg
mdefine_line|#define SDCR0_DblFlg&t;(SDCR0_SDF*1)&t;/*  Double start Flag              */
DECL|macro|SDCR0_LBM
mdefine_line|#define SDCR0_LBM&t;0x00000004&t;/* Look-Back Mode                  */
DECL|macro|SDCR0_BMS
mdefine_line|#define SDCR0_BMS&t;0x00000008&t;/* Bit Modulation Select           */
DECL|macro|SDCR0_FM0
mdefine_line|#define SDCR0_FM0&t;(SDCR0_BMS*0)&t;/*  Freq. Modulation zero (0)      */
DECL|macro|SDCR0_NRZ
mdefine_line|#define SDCR0_NRZ&t;(SDCR0_BMS*1)&t;/*  Non-Return to Zero modulation  */
DECL|macro|SDCR0_SCE
mdefine_line|#define SDCR0_SCE&t;0x00000010&t;/* Sample Clock Enable (GPIO [16]) */
DECL|macro|SDCR0_SCD
mdefine_line|#define SDCR0_SCD&t;0x00000020&t;/* Sample Clock Direction select   */
multiline_comment|/* (GPIO [16])                     */
DECL|macro|SDCR0_SClkIn
mdefine_line|#define SDCR0_SClkIn&t;(SDCR0_SCD*0)&t;/*  Sample Clock Input             */
DECL|macro|SDCR0_SClkOut
mdefine_line|#define SDCR0_SClkOut&t;(SDCR0_SCD*1)&t;/*  Sample Clock Output            */
DECL|macro|SDCR0_RCE
mdefine_line|#define SDCR0_RCE&t;0x00000040&t;/* Receive Clock Edge select       */
DECL|macro|SDCR0_RcRsEdg
mdefine_line|#define SDCR0_RcRsEdg&t;(SDCR0_RCE*0)&t;/*  Receive clock Rising-Edge      */
DECL|macro|SDCR0_RcFlEdg
mdefine_line|#define SDCR0_RcFlEdg&t;(SDCR0_RCE*1)&t;/*  Receive clock Falling-Edge     */
DECL|macro|SDCR0_TCE
mdefine_line|#define SDCR0_TCE&t;0x00000080&t;/* Transmit Clock Edge select      */
DECL|macro|SDCR0_TrRsEdg
mdefine_line|#define SDCR0_TrRsEdg&t;(SDCR0_TCE*0)&t;/*  Transmit clock Rising-Edge     */
DECL|macro|SDCR0_TrFlEdg
mdefine_line|#define SDCR0_TrFlEdg&t;(SDCR0_TCE*1)&t;/*  Transmit clock Falling-Edge    */
DECL|macro|SDCR1_AAF
mdefine_line|#define SDCR1_AAF&t;0x00000001&t;/* Abort After Frame enable        */
multiline_comment|/* (GPIO [17])                     */
DECL|macro|SDCR1_TXE
mdefine_line|#define SDCR1_TXE&t;0x00000002&t;/* Transmit Enable                 */
DECL|macro|SDCR1_RXE
mdefine_line|#define SDCR1_RXE&t;0x00000004&t;/* Receive Enable                  */
DECL|macro|SDCR1_RIE
mdefine_line|#define SDCR1_RIE&t;0x00000008&t;/* Receive FIFO 1/3-to-2/3-full or */
multiline_comment|/* more Interrupt Enable           */
DECL|macro|SDCR1_TIE
mdefine_line|#define SDCR1_TIE&t;0x00000010&t;/* Transmit FIFO 1/2-full or less  */
multiline_comment|/* Interrupt Enable                */
DECL|macro|SDCR1_AME
mdefine_line|#define SDCR1_AME&t;0x00000020&t;/* Address Match Enable            */
DECL|macro|SDCR1_TUS
mdefine_line|#define SDCR1_TUS&t;0x00000040&t;/* Transmit FIFO Under-run Select  */
DECL|macro|SDCR1_EFrmURn
mdefine_line|#define SDCR1_EFrmURn&t;(SDCR1_TUS*0)&t;/*  End Frame on Under-Run         */
DECL|macro|SDCR1_AbortURn
mdefine_line|#define SDCR1_AbortURn&t;(SDCR1_TUS*1)&t;/*  Abort on Under-Run             */
DECL|macro|SDCR1_RAE
mdefine_line|#define SDCR1_RAE&t;0x00000080&t;/* Receive Abort interrupt Enable  */
DECL|macro|SDCR2_AMV
mdefine_line|#define SDCR2_AMV&t;Fld (8, 0)&t;/* Address Match Value             */
DECL|macro|SDCR3_BRD
mdefine_line|#define SDCR3_BRD&t;Fld (4, 0)&t;/* Baud Rate Divisor/16 - 1 [11:8] */
DECL|macro|SDCR4_BRD
mdefine_line|#define SDCR4_BRD&t;Fld (8, 0)&t;/* Baud Rate Divisor/16 - 1  [7:0] */
multiline_comment|/* fsd = fxtl/(16*(BRD[11:0] + 1)) */
multiline_comment|/* Tsd = 16*(BRD[11:0] + 1)*Txtl   */
DECL|macro|SDCR3_BdRtDiv
mdefine_line|#define SDCR3_BdRtDiv(Div)      &t;/*  Baud Rate Divisor [16..65536]  */ &bslash;&n;                &t;(((Div) - 16)/16 &gt;&gt; FSize (SDCR4_BRD) &lt;&lt; &bslash;&n;                &t; FShft (SDCR3_BRD))
DECL|macro|SDCR4_BdRtDiv
mdefine_line|#define SDCR4_BdRtDiv(Div)      &t;/*  Baud Rate Divisor [16..65536]  */ &bslash;&n;                &t;(((Div) - 16)/16 &amp; FAlnMsk (SDCR4_BRD) &lt;&lt; &bslash;&n;                &t; FShft (SDCR4_BRD))
multiline_comment|/*  fsd = fxtl/(16*Floor (Div/16)) */
multiline_comment|/*  Tsd = 16*Floor (Div/16)*Txtl   */
DECL|macro|SDCR3_CeilBdRtDiv
mdefine_line|#define SDCR3_CeilBdRtDiv(Div)  &t;/*  Ceil. of BdRtDiv [16..65536]   */ &bslash;&n;                &t;(((Div) - 1)/16 &gt;&gt; FSize (SDCR4_BRD) &lt;&lt; &bslash;&n;                &t; FShft (SDCR3_BRD))
DECL|macro|SDCR4_CeilBdRtDiv
mdefine_line|#define SDCR4_CeilBdRtDiv(Div)  &t;/*  Ceil. of BdRtDiv [16..65536]   */ &bslash;&n;                &t;(((Div) - 1)/16 &amp; FAlnMsk (SDCR4_BRD) &lt;&lt; &bslash;&n;                &t; FShft (SDCR4_BRD))
multiline_comment|/*  fsd = fxtl/(16*Ceil (Div/16))  */
multiline_comment|/*  Tsd = 16*Ceil (Div/16)*Txtl    */
DECL|macro|SDDR_DATA
mdefine_line|#define SDDR_DATA&t;Fld (8, 0)&t;/* receive/transmit DATA FIFOs     */
macro_line|#if 0           &t;        &t;/* Hidden receive FIFO bits        */
mdefine_line|#define SDDR_EOF&t;0x00000100&t;/*  receive End-Of-Frame (read)    */
mdefine_line|#define SDDR_CRE&t;0x00000200&t;/*  receive CRC Error (read)       */
mdefine_line|#define SDDR_ROR&t;0x00000400&t;/*  Receive FIFO Over-Run (read)   */
macro_line|#endif /* 0 */
DECL|macro|SDSR0_EIF
mdefine_line|#define SDSR0_EIF&t;0x00000001&t;/* Error In FIFO (read)            */
DECL|macro|SDSR0_TUR
mdefine_line|#define SDSR0_TUR&t;0x00000002&t;/* Transmit FIFO Under-Run         */
DECL|macro|SDSR0_RAB
mdefine_line|#define SDSR0_RAB&t;0x00000004&t;/* Receive ABort                   */
DECL|macro|SDSR0_TFS
mdefine_line|#define SDSR0_TFS&t;0x00000008&t;/* Transmit FIFO 1/2-full or less  */
multiline_comment|/* Service request (read)          */
DECL|macro|SDSR0_RFS
mdefine_line|#define SDSR0_RFS&t;0x00000010&t;/* Receive FIFO 1/3-to-2/3-full or */
multiline_comment|/* more Service request (read)     */
DECL|macro|SDSR1_RSY
mdefine_line|#define SDSR1_RSY&t;0x00000001&t;/* Receiver SYnchronized (read)    */
DECL|macro|SDSR1_TBY
mdefine_line|#define SDSR1_TBY&t;0x00000002&t;/* Transmitter BusY (read)         */
DECL|macro|SDSR1_RNE
mdefine_line|#define SDSR1_RNE&t;0x00000004&t;/* Receive FIFO Not Empty (read)   */
DECL|macro|SDSR1_TNF
mdefine_line|#define SDSR1_TNF&t;0x00000008&t;/* Transmit FIFO Not Full (read)   */
DECL|macro|SDSR1_RTD
mdefine_line|#define SDSR1_RTD&t;0x00000010&t;/* Receive Transition Detected     */
DECL|macro|SDSR1_EOF
mdefine_line|#define SDSR1_EOF&t;0x00000020&t;/* receive End-Of-Frame (read)     */
DECL|macro|SDSR1_CRE
mdefine_line|#define SDSR1_CRE&t;0x00000040&t;/* receive CRC Error (read)        */
DECL|macro|SDSR1_ROR
mdefine_line|#define SDSR1_ROR&t;0x00000080&t;/* Receive FIFO Over-Run (read)    */
multiline_comment|/*&n; * High-Speed Serial to Parallel controller (HSSP) control registers&n; *&n; * Registers&n; *    Ser2HSCR0 &t;Serial port 2 High-Speed Serial to Parallel&n; *              &t;controller (HSSP) Control Register 0 (read/write).&n; *    Ser2HSCR1 &t;Serial port 2 High-Speed Serial to Parallel&n; *              &t;controller (HSSP) Control Register 1 (read/write).&n; *    Ser2HSDR  &t;Serial port 2 High-Speed Serial to Parallel&n; *              &t;controller (HSSP) Data Register (read/write).&n; *    Ser2HSSR0 &t;Serial port 2 High-Speed Serial to Parallel&n; *              &t;controller (HSSP) Status Register 0 (read/write).&n; *    Ser2HSSR1 &t;Serial port 2 High-Speed Serial to Parallel&n; *              &t;controller (HSSP) Status Register 1 (read).&n; *    Ser2HSCR2 &t;Serial port 2 High-Speed Serial to Parallel&n; *              &t;controller (HSSP) Control Register 2 (read/write).&n; *              &t;[The HSCR2 register is only implemented in&n; *              &t;versions 2.0 (rev. = 8) and higher of the StrongARM&n; *              &t;SA-1100.]&n; */
DECL|macro|_Ser2HSCR0
mdefine_line|#define _Ser2HSCR0&t;0x80040060&t;/* Ser. port 2 HSSP Control Reg. 0 */
DECL|macro|_Ser2HSCR1
mdefine_line|#define _Ser2HSCR1&t;0x80040064&t;/* Ser. port 2 HSSP Control Reg. 1 */
DECL|macro|_Ser2HSDR
mdefine_line|#define _Ser2HSDR&t;0x8004006C&t;/* Ser. port 2 HSSP Data Reg.      */
DECL|macro|_Ser2HSSR0
mdefine_line|#define _Ser2HSSR0&t;0x80040074&t;/* Ser. port 2 HSSP Status Reg. 0  */
DECL|macro|_Ser2HSSR1
mdefine_line|#define _Ser2HSSR1&t;0x80040078&t;/* Ser. port 2 HSSP Status Reg. 1  */
DECL|macro|_Ser2HSCR2
mdefine_line|#define _Ser2HSCR2&t;0x90060028&t;/* Ser. port 2 HSSP Control Reg. 2 */
macro_line|#if LANGUAGE == C
DECL|macro|Ser2HSCR0
mdefine_line|#define Ser2HSCR0&t;        &t;/* Ser. port 2 HSSP Control Reg. 0 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser2HSCR0)))
DECL|macro|Ser2HSCR1
mdefine_line|#define Ser2HSCR1&t;        &t;/* Ser. port 2 HSSP Control Reg. 1 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser2HSCR1)))
DECL|macro|Ser2HSDR
mdefine_line|#define Ser2HSDR&t;        &t;/* Ser. port 2 HSSP Data Reg.      */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser2HSDR)))
DECL|macro|Ser2HSSR0
mdefine_line|#define Ser2HSSR0&t;        &t;/* Ser. port 2 HSSP Status Reg. 0  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser2HSSR0)))
DECL|macro|Ser2HSSR1
mdefine_line|#define Ser2HSSR1&t;        &t;/* Ser. port 2 HSSP Status Reg. 1  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser2HSSR1)))
DECL|macro|Ser2HSCR2
mdefine_line|#define Ser2HSCR2&t;        &t;/* Ser. port 2 HSSP Control Reg. 2 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser2HSCR2)))
macro_line|#endif /* LANGUAGE == C */
DECL|macro|HSCR0_ITR
mdefine_line|#define HSCR0_ITR&t;0x00000001&t;/* IrDA Transmission Rate          */
DECL|macro|HSCR0_UART
mdefine_line|#define HSCR0_UART&t;(HSCR0_ITR*0)&t;/*  UART mode (115.2 kb/s if IrDA) */
DECL|macro|HSCR0_HSSP
mdefine_line|#define HSCR0_HSSP&t;(HSCR0_ITR*1)&t;/*  HSSP mode (4 Mb/s)             */
DECL|macro|HSCR0_LBM
mdefine_line|#define HSCR0_LBM&t;0x00000002&t;/* Look-Back Mode                  */
DECL|macro|HSCR0_TUS
mdefine_line|#define HSCR0_TUS&t;0x00000004&t;/* Transmit FIFO Under-run Select  */
DECL|macro|HSCR0_EFrmURn
mdefine_line|#define HSCR0_EFrmURn&t;(HSCR0_TUS*0)&t;/*  End Frame on Under-Run         */
DECL|macro|HSCR0_AbortURn
mdefine_line|#define HSCR0_AbortURn&t;(HSCR0_TUS*1)&t;/*  Abort on Under-Run             */
DECL|macro|HSCR0_TXE
mdefine_line|#define HSCR0_TXE&t;0x00000008&t;/* Transmit Enable                 */
DECL|macro|HSCR0_RXE
mdefine_line|#define HSCR0_RXE&t;0x00000010&t;/* Receive Enable                  */
DECL|macro|HSCR0_RIE
mdefine_line|#define HSCR0_RIE&t;0x00000020&t;/* Receive FIFO 2/5-to-3/5-full or */
multiline_comment|/* more Interrupt Enable           */
DECL|macro|HSCR0_TIE
mdefine_line|#define HSCR0_TIE&t;0x00000040&t;/* Transmit FIFO 1/2-full or less  */
multiline_comment|/* Interrupt Enable                */
DECL|macro|HSCR0_AME
mdefine_line|#define HSCR0_AME&t;0x00000080&t;/* Address Match Enable            */
DECL|macro|HSCR1_AMV
mdefine_line|#define HSCR1_AMV&t;Fld (8, 0)&t;/* Address Match Value             */
DECL|macro|HSDR_DATA
mdefine_line|#define HSDR_DATA&t;Fld (8, 0)&t;/* receive/transmit DATA FIFOs     */
macro_line|#if 0           &t;        &t;/* Hidden receive FIFO bits        */
mdefine_line|#define HSDR_EOF&t;0x00000100&t;/*  receive End-Of-Frame (read)    */
mdefine_line|#define HSDR_CRE&t;0x00000200&t;/*  receive CRC Error (read)       */
mdefine_line|#define HSDR_ROR&t;0x00000400&t;/*  Receive FIFO Over-Run (read)   */
macro_line|#endif /* 0 */
DECL|macro|HSSR0_EIF
mdefine_line|#define HSSR0_EIF&t;0x00000001&t;/* Error In FIFO (read)            */
DECL|macro|HSSR0_TUR
mdefine_line|#define HSSR0_TUR&t;0x00000002&t;/* Transmit FIFO Under-Run         */
DECL|macro|HSSR0_RAB
mdefine_line|#define HSSR0_RAB&t;0x00000004&t;/* Receive ABort                   */
DECL|macro|HSSR0_TFS
mdefine_line|#define HSSR0_TFS&t;0x00000008&t;/* Transmit FIFO 1/2-full or less  */
multiline_comment|/* Service request (read)          */
DECL|macro|HSSR0_RFS
mdefine_line|#define HSSR0_RFS&t;0x00000010&t;/* Receive FIFO 2/5-to-3/5-full or */
multiline_comment|/* more Service request (read)     */
DECL|macro|HSSR0_FRE
mdefine_line|#define HSSR0_FRE&t;0x00000020&t;/* receive FRaming Error           */
DECL|macro|HSSR1_RSY
mdefine_line|#define HSSR1_RSY&t;0x00000001&t;/* Receiver SYnchronized (read)    */
DECL|macro|HSSR1_TBY
mdefine_line|#define HSSR1_TBY&t;0x00000002&t;/* Transmitter BusY (read)         */
DECL|macro|HSSR1_RNE
mdefine_line|#define HSSR1_RNE&t;0x00000004&t;/* Receive FIFO Not Empty (read)   */
DECL|macro|HSSR1_TNF
mdefine_line|#define HSSR1_TNF&t;0x00000008&t;/* Transmit FIFO Not Full (read)   */
DECL|macro|HSSR1_EOF
mdefine_line|#define HSSR1_EOF&t;0x00000010&t;/* receive End-Of-Frame (read)     */
DECL|macro|HSSR1_CRE
mdefine_line|#define HSSR1_CRE&t;0x00000020&t;/* receive CRC Error (read)        */
DECL|macro|HSSR1_ROR
mdefine_line|#define HSSR1_ROR&t;0x00000040&t;/* Receive FIFO Over-Run (read)    */
DECL|macro|HSCR2_TXP
mdefine_line|#define HSCR2_TXP&t;0x00040000&t;/* Transmit data Polarity (TXD_2)  */
DECL|macro|HSCR2_TrDataL
mdefine_line|#define HSCR2_TrDataL&t;(HSCR2_TXP*0)&t;/*  Transmit Data active Low       */
multiline_comment|/*  (inverted)                     */
DECL|macro|HSCR2_TrDataH
mdefine_line|#define HSCR2_TrDataH&t;(HSCR2_TXP*1)&t;/*  Transmit Data active High      */
multiline_comment|/*  (non-inverted)                 */
DECL|macro|HSCR2_RXP
mdefine_line|#define HSCR2_RXP&t;0x00080000&t;/* Receive data Polarity (RXD_2)   */
DECL|macro|HSCR2_RcDataL
mdefine_line|#define HSCR2_RcDataL&t;(HSCR2_RXP*0)&t;/*  Receive Data active Low        */
multiline_comment|/*  (inverted)                     */
DECL|macro|HSCR2_RcDataH
mdefine_line|#define HSCR2_RcDataH&t;(HSCR2_RXP*1)&t;/*  Receive Data active High       */
multiline_comment|/*  (non-inverted)                 */
multiline_comment|/*&n; * Multi-media Communications Port (MCP) control registers&n; *&n; * Registers&n; *    Ser4MCCR0 &t;Serial port 4 Multi-media Communications Port (MCP)&n; *              &t;Control Register 0 (read/write).&n; *    Ser4MCDR0 &t;Serial port 4 Multi-media Communications Port (MCP)&n; *              &t;Data Register 0 (audio, read/write).&n; *    Ser4MCDR1 &t;Serial port 4 Multi-media Communications Port (MCP)&n; *              &t;Data Register 1 (telecom, read/write).&n; *    Ser4MCDR2 &t;Serial port 4 Multi-media Communications Port (MCP)&n; *              &t;Data Register 2 (CODEC registers, read/write).&n; *    Ser4MCSR  &t;Serial port 4 Multi-media Communications Port (MCP)&n; *              &t;Status Register (read/write).&n; *    Ser4MCCR1 &t;Serial port 4 Multi-media Communications Port (MCP)&n; *              &t;Control Register 1 (read/write).&n; *              &t;[The MCCR1 register is only implemented in&n; *              &t;versions 2.0 (rev. = 8) and higher of the StrongARM&n; *              &t;SA-1100.]&n; *&n; * Clocks&n; *    fmc, Tmc  &t;Frequency, period of the MCP communication (10 MHz,&n; *              &t;12 MHz, or GPIO [21]).&n; *    faud, Taud&t;Frequency, period of the audio sampling.&n; *    ftcm, Ttcm&t;Frequency, period of the telecom sampling.&n; */
DECL|macro|_Ser4MCCR0
mdefine_line|#define _Ser4MCCR0&t;0x80060000&t;/* Ser. port 4 MCP Control Reg. 0  */
DECL|macro|_Ser4MCDR0
mdefine_line|#define _Ser4MCDR0&t;0x80060008&t;/* Ser. port 4 MCP Data Reg. 0     */
multiline_comment|/* (audio)                         */
DECL|macro|_Ser4MCDR1
mdefine_line|#define _Ser4MCDR1&t;0x8006000C&t;/* Ser. port 4 MCP Data Reg. 1     */
multiline_comment|/* (telecom)                       */
DECL|macro|_Ser4MCDR2
mdefine_line|#define _Ser4MCDR2&t;0x80060010&t;/* Ser. port 4 MCP Data Reg. 2     */
multiline_comment|/* (CODEC reg.)                    */
DECL|macro|_Ser4MCSR
mdefine_line|#define _Ser4MCSR&t;0x80060018&t;/* Ser. port 4 MCP Status Reg.     */
DECL|macro|_Ser4MCCR1
mdefine_line|#define _Ser4MCCR1&t;0x90060030&t;/* Ser. port 4 MCP Control Reg. 1  */
macro_line|#if LANGUAGE == C
DECL|macro|Ser4MCCR0
mdefine_line|#define Ser4MCCR0&t;        &t;/* Ser. port 4 MCP Control Reg. 0  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser4MCCR0)))
DECL|macro|Ser4MCDR0
mdefine_line|#define Ser4MCDR0&t;        &t;/* Ser. port 4 MCP Data Reg. 0     */ &bslash;&n;                &t;        &t;/* (audio)                         */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser4MCDR0)))
DECL|macro|Ser4MCDR1
mdefine_line|#define Ser4MCDR1&t;        &t;/* Ser. port 4 MCP Data Reg. 1     */ &bslash;&n;                &t;        &t;/* (telecom)                       */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser4MCDR1)))
DECL|macro|Ser4MCDR2
mdefine_line|#define Ser4MCDR2&t;        &t;/* Ser. port 4 MCP Data Reg. 2     */ &bslash;&n;                &t;        &t;/* (CODEC reg.)                    */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser4MCDR2)))
DECL|macro|Ser4MCSR
mdefine_line|#define Ser4MCSR&t;        &t;/* Ser. port 4 MCP Status Reg.     */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser4MCSR)))
DECL|macro|Ser4MCCR1
mdefine_line|#define Ser4MCCR1&t;        &t;/* Ser. port 4 MCP Control Reg. 1  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser4MCCR1)))
macro_line|#endif /* LANGUAGE == C */
DECL|macro|MCCR0_ASD
mdefine_line|#define MCCR0_ASD&t;Fld (7, 0)&t;/* Audio Sampling rate Divisor/32  */
multiline_comment|/* [6..127]                        */
multiline_comment|/* faud = fmc/(32*ASD)             */
multiline_comment|/* Taud = 32*ASD*Tmc               */
DECL|macro|MCCR0_AudSmpDiv
mdefine_line|#define MCCR0_AudSmpDiv(Div)    &t;/*  Audio Sampling rate Divisor    */ &bslash;&n;                &t;        &t;/*  [192..4064]                    */ &bslash;&n;                &t;((Div)/32 &lt;&lt; FShft (MCCR0_ASD))
multiline_comment|/*  faud = fmc/(32*Floor (Div/32)) */
multiline_comment|/*  Taud = 32*Floor (Div/32)*Tmc   */
DECL|macro|MCCR0_CeilAudSmpDiv
mdefine_line|#define MCCR0_CeilAudSmpDiv(Div)&t;/*  Ceil. of AudSmpDiv [192..4064] */ &bslash;&n;                &t;(((Div) + 31)/32 &lt;&lt; FShft (MCCR0_ASD))
multiline_comment|/*  faud = fmc/(32*Ceil (Div/32))  */
multiline_comment|/*  Taud = 32*Ceil (Div/32)*Tmc    */
DECL|macro|MCCR0_TSD
mdefine_line|#define MCCR0_TSD&t;Fld (7, 8)&t;/* Telecom Sampling rate           */
multiline_comment|/* Divisor/32 [16..127]            */
multiline_comment|/* ftcm = fmc/(32*TSD)             */
multiline_comment|/* Ttcm = 32*TSD*Tmc               */
DECL|macro|MCCR0_TcmSmpDiv
mdefine_line|#define MCCR0_TcmSmpDiv(Div)    &t;/*  Telecom Sampling rate Divisor  */ &bslash;&n;                &t;        &t;/*  [512..4064]                    */ &bslash;&n;                &t;((Div)/32 &lt;&lt; FShft (MCCR0_TSD))
multiline_comment|/*  ftcm = fmc/(32*Floor (Div/32)) */
multiline_comment|/*  Ttcm = 32*Floor (Div/32)*Tmc   */
DECL|macro|MCCR0_CeilTcmSmpDiv
mdefine_line|#define MCCR0_CeilTcmSmpDiv(Div)&t;/*  Ceil. of TcmSmpDiv [512..4064] */ &bslash;&n;                &t;(((Div) + 31)/32 &lt;&lt; FShft (MCCR0_TSD))
multiline_comment|/*  ftcm = fmc/(32*Ceil (Div/32))  */
multiline_comment|/*  Ttcm = 32*Ceil (Div/32)*Tmc    */
DECL|macro|MCCR0_MCE
mdefine_line|#define MCCR0_MCE&t;0x00010000&t;/* MCP Enable                      */
DECL|macro|MCCR0_ECS
mdefine_line|#define MCCR0_ECS&t;0x00020000&t;/* External Clock Select           */
DECL|macro|MCCR0_IntClk
mdefine_line|#define MCCR0_IntClk&t;(MCCR0_ECS*0)&t;/*  Internal Clock (10 or 12 MHz)  */
DECL|macro|MCCR0_ExtClk
mdefine_line|#define MCCR0_ExtClk&t;(MCCR0_ECS*1)&t;/*  External Clock (GPIO [21])     */
DECL|macro|MCCR0_ADM
mdefine_line|#define MCCR0_ADM&t;0x00040000&t;/* A/D (audio/telecom) data        */
multiline_comment|/* sampling/storing Mode           */
DECL|macro|MCCR0_VldBit
mdefine_line|#define MCCR0_VldBit&t;(MCCR0_ADM*0)&t;/*  Valid Bit storing mode         */
DECL|macro|MCCR0_SmpCnt
mdefine_line|#define MCCR0_SmpCnt&t;(MCCR0_ADM*1)&t;/*  Sampling Counter storing mode  */
DECL|macro|MCCR0_TTE
mdefine_line|#define MCCR0_TTE&t;0x00080000&t;/* Telecom Transmit FIFO 1/2-full  */
multiline_comment|/* or less interrupt Enable        */
DECL|macro|MCCR0_TRE
mdefine_line|#define MCCR0_TRE&t;0x00100000&t;/* Telecom Receive FIFO 1/2-full   */
multiline_comment|/* or more interrupt Enable        */
DECL|macro|MCCR0_ATE
mdefine_line|#define MCCR0_ATE&t;0x00200000&t;/* Audio Transmit FIFO 1/2-full    */
multiline_comment|/* or less interrupt Enable        */
DECL|macro|MCCR0_ARE
mdefine_line|#define MCCR0_ARE&t;0x00400000&t;/* Audio Receive FIFO 1/2-full or  */
multiline_comment|/* more interrupt Enable           */
DECL|macro|MCCR0_LBM
mdefine_line|#define MCCR0_LBM&t;0x00800000&t;/* Look-Back Mode                  */
DECL|macro|MCCR0_ECP
mdefine_line|#define MCCR0_ECP&t;Fld (2, 24)&t;/* External Clock Prescaler - 1    */
DECL|macro|MCCR0_ExtClkDiv
mdefine_line|#define MCCR0_ExtClkDiv(Div)    &t;/*  External Clock Divisor [1..4]  */ &bslash;&n;                &t;(((Div) - 1) &lt;&lt; FShft (MCCR0_ECP))
DECL|macro|MCDR0_DATA
mdefine_line|#define MCDR0_DATA&t;Fld (12, 4)&t;/* receive/transmit audio DATA     */
multiline_comment|/* FIFOs                           */
DECL|macro|MCDR1_DATA
mdefine_line|#define MCDR1_DATA&t;Fld (14, 2)&t;/* receive/transmit telecom DATA   */
multiline_comment|/* FIFOs                           */
multiline_comment|/* receive/transmit CODEC reg.     */
multiline_comment|/* FIFOs:                          */
DECL|macro|MCDR2_DATA
mdefine_line|#define MCDR2_DATA&t;Fld (16, 0)&t;/*  reg. DATA                      */
DECL|macro|MCDR2_RW
mdefine_line|#define MCDR2_RW&t;0x00010000&t;/*  reg. Read/Write (transmit)     */
DECL|macro|MCDR2_Rd
mdefine_line|#define MCDR2_Rd&t;(MCDR2_RW*0)&t;/*   reg. Read                     */
DECL|macro|MCDR2_Wr
mdefine_line|#define MCDR2_Wr&t;(MCDR2_RW*1)&t;/*   reg. Write                    */
DECL|macro|MCDR2_ADD
mdefine_line|#define MCDR2_ADD&t;Fld (4, 17)&t;/*  reg. ADDress                   */
DECL|macro|MCSR_ATS
mdefine_line|#define MCSR_ATS&t;0x00000001&t;/* Audio Transmit FIFO 1/2-full    */
multiline_comment|/* or less Service request (read)  */
DECL|macro|MCSR_ARS
mdefine_line|#define MCSR_ARS&t;0x00000002&t;/* Audio Receive FIFO 1/2-full or  */
multiline_comment|/* more Service request (read)     */
DECL|macro|MCSR_TTS
mdefine_line|#define MCSR_TTS&t;0x00000004&t;/* Telecom Transmit FIFO 1/2-full  */
multiline_comment|/* or less Service request (read)  */
DECL|macro|MCSR_TRS
mdefine_line|#define MCSR_TRS&t;0x00000008&t;/* Telecom Receive FIFO 1/2-full   */
multiline_comment|/* or more Service request (read)  */
DECL|macro|MCSR_ATU
mdefine_line|#define MCSR_ATU&t;0x00000010&t;/* Audio Transmit FIFO Under-run   */
DECL|macro|MCSR_ARO
mdefine_line|#define MCSR_ARO&t;0x00000020&t;/* Audio Receive FIFO Over-run     */
DECL|macro|MCSR_TTU
mdefine_line|#define MCSR_TTU&t;0x00000040&t;/* Telecom Transmit FIFO Under-run */
DECL|macro|MCSR_TRO
mdefine_line|#define MCSR_TRO&t;0x00000080&t;/* Telecom Receive FIFO Over-run   */
DECL|macro|MCSR_ANF
mdefine_line|#define MCSR_ANF&t;0x00000100&t;/* Audio transmit FIFO Not Full    */
multiline_comment|/* (read)                          */
DECL|macro|MCSR_ANE
mdefine_line|#define MCSR_ANE&t;0x00000200&t;/* Audio receive FIFO Not Empty    */
multiline_comment|/* (read)                          */
DECL|macro|MCSR_TNF
mdefine_line|#define MCSR_TNF&t;0x00000400&t;/* Telecom transmit FIFO Not Full  */
multiline_comment|/* (read)                          */
DECL|macro|MCSR_TNE
mdefine_line|#define MCSR_TNE&t;0x00000800&t;/* Telecom receive FIFO Not Empty  */
multiline_comment|/* (read)                          */
DECL|macro|MCSR_CWC
mdefine_line|#define MCSR_CWC&t;0x00001000&t;/* CODEC register Write Completed  */
multiline_comment|/* (read)                          */
DECL|macro|MCSR_CRC
mdefine_line|#define MCSR_CRC&t;0x00002000&t;/* CODEC register Read Completed   */
multiline_comment|/* (read)                          */
DECL|macro|MCSR_ACE
mdefine_line|#define MCSR_ACE&t;0x00004000&t;/* Audio CODEC Enabled (read)      */
DECL|macro|MCSR_TCE
mdefine_line|#define MCSR_TCE&t;0x00008000&t;/* Telecom CODEC Enabled (read)    */
DECL|macro|MCCR1_CFS
mdefine_line|#define MCCR1_CFS&t;0x00100000&t;/* Clock Freq. Select              */
DECL|macro|MCCR1_F12MHz
mdefine_line|#define MCCR1_F12MHz&t;(MCCR1_CFS*0)&t;/*  Freq. (fmc) = ~ 12 MHz         */
multiline_comment|/*  (11.981 MHz)                   */
DECL|macro|MCCR1_F10MHz
mdefine_line|#define MCCR1_F10MHz&t;(MCCR1_CFS*1)&t;/*  Freq. (fmc) = ~ 10 MHz         */
multiline_comment|/*  (9.585 MHz)                    */
multiline_comment|/*&n; * Synchronous Serial Port (SSP) control registers&n; *&n; * Registers&n; *    Ser4SSCR0 &t;Serial port 4 Synchronous Serial Port (SSP) Control&n; *              &t;Register 0 (read/write).&n; *    Ser4SSCR1 &t;Serial port 4 Synchronous Serial Port (SSP) Control&n; *              &t;Register 1 (read/write).&n; *              &t;[Bits SPO and SP are only implemented in versions 2.0&n; *              &t;(rev. = 8) and higher of the StrongARM SA-1100.]&n; *    Ser4SSDR  &t;Serial port 4 Synchronous Serial Port (SSP) Data&n; *              &t;Register (read/write).&n; *    Ser4SSSR  &t;Serial port 4 Synchronous Serial Port (SSP) Status&n; *              &t;Register (read/write).&n; *&n; * Clocks&n; *    fxtl, Txtl&t;Frequency, period of the system crystal (3.6864 MHz&n; *              &t;or 3.5795 MHz).&n; *    fss, Tss  &t;Frequency, period of the SSP communication.&n; */
DECL|macro|_Ser4SSCR0
mdefine_line|#define _Ser4SSCR0&t;0x80070060&t;/* Ser. port 4 SSP Control Reg. 0  */
DECL|macro|_Ser4SSCR1
mdefine_line|#define _Ser4SSCR1&t;0x80070064&t;/* Ser. port 4 SSP Control Reg. 1  */
DECL|macro|_Ser4SSDR
mdefine_line|#define _Ser4SSDR&t;0x8007006C&t;/* Ser. port 4 SSP Data Reg.       */
DECL|macro|_Ser4SSSR
mdefine_line|#define _Ser4SSSR&t;0x80070074&t;/* Ser. port 4 SSP Status Reg.     */
macro_line|#if LANGUAGE == C
DECL|macro|Ser4SSCR0
mdefine_line|#define Ser4SSCR0&t;        &t;/* Ser. port 4 SSP Control Reg. 0  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser4SSCR0)))
DECL|macro|Ser4SSCR1
mdefine_line|#define Ser4SSCR1&t;        &t;/* Ser. port 4 SSP Control Reg. 1  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser4SSCR1)))
DECL|macro|Ser4SSDR
mdefine_line|#define Ser4SSDR&t;        &t;/* Ser. port 4 SSP Data Reg.       */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser4SSDR)))
DECL|macro|Ser4SSSR
mdefine_line|#define Ser4SSSR&t;        &t;/* Ser. port 4 SSP Status Reg.     */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_Ser4SSSR)))
macro_line|#endif /* LANGUAGE == C */
DECL|macro|SSCR0_DSS
mdefine_line|#define SSCR0_DSS&t;Fld (4, 0)&t;/* Data Size - 1 Select [3..15]    */
DECL|macro|SSCR0_DataSize
mdefine_line|#define SSCR0_DataSize(Size)    &t;/*  Data Size Select [4..16]       */ &bslash;&n;                &t;(((Size) - 1) &lt;&lt; FShft (SSCR0_DSS))
DECL|macro|SSCR0_FRF
mdefine_line|#define SSCR0_FRF&t;Fld (2, 4)&t;/* FRame Format                    */
DECL|macro|SSCR0_Motorola
mdefine_line|#define SSCR0_Motorola&t;        &t;/*  Motorola Serial Peripheral     */ &bslash;&n;                &t;        &t;/*  Interface (SPI) format         */ &bslash;&n;                &t;(0 &lt;&lt; FShft (SSCR0_FRF))
DECL|macro|SSCR0_TI
mdefine_line|#define SSCR0_TI&t;        &t;/*  Texas Instruments Synchronous  */ &bslash;&n;                &t;        &t;/*  Serial format                  */ &bslash;&n;                &t;(1 &lt;&lt; FShft (SSCR0_FRF))
DECL|macro|SSCR0_National
mdefine_line|#define SSCR0_National&t;        &t;/*  National Microwire format      */ &bslash;&n;                &t;(2 &lt;&lt; FShft (SSCR0_FRF))
DECL|macro|SSCR0_SSE
mdefine_line|#define SSCR0_SSE&t;0x00000080&t;/* SSP Enable                      */
DECL|macro|SSCR0_SCR
mdefine_line|#define SSCR0_SCR&t;Fld (8, 8)&t;/* Serial Clock Rate divisor/2 - 1 */
multiline_comment|/* fss = fxtl/(2*(SCR + 1))        */
multiline_comment|/* Tss = 2*(SCR + 1)*Txtl          */
DECL|macro|SSCR0_SerClkDiv
mdefine_line|#define SSCR0_SerClkDiv(Div)    &t;/*  Serial Clock Divisor [2..512]  */ &bslash;&n;                &t;(((Div) - 2)/2 &lt;&lt; FShft (SSCR0_SCR))
multiline_comment|/*  fss = fxtl/(2*Floor (Div/2))   */
multiline_comment|/*  Tss = 2*Floor (Div/2)*Txtl     */
DECL|macro|SSCR0_CeilSerClkDiv
mdefine_line|#define SSCR0_CeilSerClkDiv(Div)&t;/*  Ceil. of SerClkDiv [2..512]    */ &bslash;&n;                &t;(((Div) - 1)/2 &lt;&lt; FShft (SSCR0_SCR))
multiline_comment|/*  fss = fxtl/(2*Ceil (Div/2))    */
multiline_comment|/*  Tss = 2*Ceil (Div/2)*Txtl      */
DECL|macro|SSCR1_RIE
mdefine_line|#define SSCR1_RIE&t;0x00000001&t;/* Receive FIFO 1/2-full or more   */
multiline_comment|/* Interrupt Enable                */
DECL|macro|SSCR1_TIE
mdefine_line|#define SSCR1_TIE&t;0x00000002&t;/* Transmit FIFO 1/2-full or less  */
multiline_comment|/* Interrupt Enable                */
DECL|macro|SSCR1_LBM
mdefine_line|#define SSCR1_LBM&t;0x00000004&t;/* Look-Back Mode                  */
DECL|macro|SSCR1_SPO
mdefine_line|#define SSCR1_SPO&t;0x00000008&t;/* Sample clock (SCLK) POlarity    */
DECL|macro|SSCR1_SClkIactL
mdefine_line|#define SSCR1_SClkIactL&t;(SSCR1_SPO*0)&t;/*  Sample Clock Inactive Low      */
DECL|macro|SSCR1_SClkIactH
mdefine_line|#define SSCR1_SClkIactH&t;(SSCR1_SPO*1)&t;/*  Sample Clock Inactive High     */
DECL|macro|SSCR1_SP
mdefine_line|#define SSCR1_SP&t;0x00000010&t;/* Sample clock (SCLK) Phase       */
DECL|macro|SSCR1_SClk1P
mdefine_line|#define SSCR1_SClk1P&t;(SSCR1_SP*0)&t;/*  Sample Clock active 1 Period   */
multiline_comment|/*  after frame (SFRM, 1st edge)   */
DECL|macro|SSCR1_SClk1_2P
mdefine_line|#define SSCR1_SClk1_2P&t;(SSCR1_SP*1)&t;/*  Sample Clock active 1/2 Period */
multiline_comment|/*  after frame (SFRM, 1st edge)   */
DECL|macro|SSCR1_ECS
mdefine_line|#define SSCR1_ECS&t;0x00000020&t;/* External Clock Select           */
DECL|macro|SSCR1_IntClk
mdefine_line|#define SSCR1_IntClk&t;(SSCR1_ECS*0)&t;/*  Internal Clock                 */
DECL|macro|SSCR1_ExtClk
mdefine_line|#define SSCR1_ExtClk&t;(SSCR1_ECS*1)&t;/*  External Clock (GPIO [19])     */
DECL|macro|SSDR_DATA
mdefine_line|#define SSDR_DATA&t;Fld (16, 0)&t;/* receive/transmit DATA FIFOs     */
DECL|macro|SSSR_TNF
mdefine_line|#define SSSR_TNF&t;0x00000002&t;/* Transmit FIFO Not Full (read)   */
DECL|macro|SSSR_RNE
mdefine_line|#define SSSR_RNE&t;0x00000004&t;/* Receive FIFO Not Empty (read)   */
DECL|macro|SSSR_BSY
mdefine_line|#define SSSR_BSY&t;0x00000008&t;/* SSP BuSY (read)                 */
DECL|macro|SSSR_TFS
mdefine_line|#define SSSR_TFS&t;0x00000010&t;/* Transmit FIFO 1/2-full or less  */
multiline_comment|/* Service request (read)          */
DECL|macro|SSSR_RFS
mdefine_line|#define SSSR_RFS&t;0x00000020&t;/* Receive FIFO 1/2-full or more   */
multiline_comment|/* Service request (read)          */
DECL|macro|SSSR_ROR
mdefine_line|#define SSSR_ROR&t;0x00000040&t;/* Receive FIFO Over-Run           */
multiline_comment|/*&n; * Operating System (OS) timer control registers&n; *&n; * Registers&n; *    OSMR0     &t;Operating System (OS) timer Match Register 0&n; *              &t;(read/write).&n; *    OSMR1     &t;Operating System (OS) timer Match Register 1&n; *              &t;(read/write).&n; *    OSMR2     &t;Operating System (OS) timer Match Register 2&n; *              &t;(read/write).&n; *    OSMR3     &t;Operating System (OS) timer Match Register 3&n; *              &t;(read/write).&n; *    OSCR      &t;Operating System (OS) timer Counter Register&n; *              &t;(read/write).&n; *    OSSR      &t;Operating System (OS) timer Status Register&n; *              &t;(read/write).&n; *    OWER      &t;Operating System (OS) timer Watch-dog Enable Register&n; *              &t;(read/write).&n; *    OIER      &t;Operating System (OS) timer Interrupt Enable Register&n; *              &t;(read/write).&n; */
DECL|macro|_OSMR
mdefine_line|#define _OSMR(Nb)&t;        &t;/* OS timer Match Reg. [0..3]      */ &bslash;&n;                &t;(0x90000000 + (Nb)*4)
DECL|macro|_OSMR0
mdefine_line|#define _OSMR0  &t;_OSMR (0)&t;/* OS timer Match Reg. 0           */
DECL|macro|_OSMR1
mdefine_line|#define _OSMR1  &t;_OSMR (1)&t;/* OS timer Match Reg. 1           */
DECL|macro|_OSMR2
mdefine_line|#define _OSMR2  &t;_OSMR (2)&t;/* OS timer Match Reg. 2           */
DECL|macro|_OSMR3
mdefine_line|#define _OSMR3  &t;_OSMR (3)&t;/* OS timer Match Reg. 3           */
DECL|macro|_OSCR
mdefine_line|#define _OSCR   &t;0x90000010&t;/* OS timer Counter Reg.           */
DECL|macro|_OSSR
mdefine_line|#define _OSSR   &t;0x90000014&t;/* OS timer Status Reg.            */
DECL|macro|_OWER
mdefine_line|#define _OWER   &t;0x90000018&t;/* OS timer Watch-dog Enable Reg.  */
DECL|macro|_OIER
mdefine_line|#define _OIER   &t;0x9000001C&t;/* OS timer Interrupt Enable Reg.  */
macro_line|#if LANGUAGE == C
DECL|macro|OSMR
mdefine_line|#define OSMR    &t;        &t;/* OS timer Match Reg. [0..3]      */ &bslash;&n;                &t;((volatile Word *) io_p2v (_OSMR (0)))
DECL|macro|OSMR0
mdefine_line|#define OSMR0   &t;(OSMR [0])&t;/* OS timer Match Reg. 0           */
DECL|macro|OSMR1
mdefine_line|#define OSMR1   &t;(OSMR [1])&t;/* OS timer Match Reg. 1           */
DECL|macro|OSMR2
mdefine_line|#define OSMR2   &t;(OSMR [2])&t;/* OS timer Match Reg. 2           */
DECL|macro|OSMR3
mdefine_line|#define OSMR3   &t;(OSMR [3])&t;/* OS timer Match Reg. 3           */
DECL|macro|OSCR
mdefine_line|#define OSCR    &t;        &t;/* OS timer Counter Reg.           */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_OSCR)))
DECL|macro|OSSR
mdefine_line|#define OSSR    &t;        &t;/* OS timer Status Reg.            */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_OSSR)))
DECL|macro|OWER
mdefine_line|#define OWER    &t;        &t;/* OS timer Watch-dog Enable Reg.  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_OWER)))
DECL|macro|OIER
mdefine_line|#define OIER    &t;        &t;/* OS timer Interrupt Enable Reg.  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_OIER)))
macro_line|#endif /* LANGUAGE == C */
DECL|macro|OSSR_M
mdefine_line|#define OSSR_M(Nb)&t;        &t;/* Match detected [0..3]           */ &bslash;&n;                &t;(0x00000001 &lt;&lt; (Nb))
DECL|macro|OSSR_M0
mdefine_line|#define OSSR_M0 &t;OSSR_M (0)&t;/* Match detected 0                */
DECL|macro|OSSR_M1
mdefine_line|#define OSSR_M1 &t;OSSR_M (1)&t;/* Match detected 1                */
DECL|macro|OSSR_M2
mdefine_line|#define OSSR_M2 &t;OSSR_M (2)&t;/* Match detected 2                */
DECL|macro|OSSR_M3
mdefine_line|#define OSSR_M3 &t;OSSR_M (3)&t;/* Match detected 3                */
DECL|macro|OWER_WME
mdefine_line|#define OWER_WME&t;0x00000001&t;/* Watch-dog Match Enable          */
multiline_comment|/* (set only)                      */
DECL|macro|OIER_E
mdefine_line|#define OIER_E(Nb)&t;        &t;/* match interrupt Enable [0..3]   */ &bslash;&n;                &t;(0x00000001 &lt;&lt; (Nb))
DECL|macro|OIER_E0
mdefine_line|#define OIER_E0 &t;OIER_E (0)&t;/* match interrupt Enable 0        */
DECL|macro|OIER_E1
mdefine_line|#define OIER_E1 &t;OIER_E (1)&t;/* match interrupt Enable 1        */
DECL|macro|OIER_E2
mdefine_line|#define OIER_E2 &t;OIER_E (2)&t;/* match interrupt Enable 2        */
DECL|macro|OIER_E3
mdefine_line|#define OIER_E3 &t;OIER_E (3)&t;/* match interrupt Enable 3        */
multiline_comment|/*&n; * Real-Time Clock (RTC) control registers&n; *&n; * Registers&n; *    RTAR      &t;Real-Time Clock (RTC) Alarm Register (read/write).&n; *    RCNR      &t;Real-Time Clock (RTC) CouNt Register (read/write).&n; *    RTTR      &t;Real-Time Clock (RTC) Trim Register (read/write).&n; *    RTSR      &t;Real-Time Clock (RTC) Status Register (read/write).&n; *&n; * Clocks&n; *    frtx, Trtx&t;Frequency, period of the real-time clock crystal&n; *              &t;(32.768 kHz nominal).&n; *    frtc, Trtc&t;Frequency, period of the real-time clock counter&n; *              &t;(1 Hz nominal).&n; */
DECL|macro|_RTAR
mdefine_line|#define _RTAR   &t;0x90010000&t;/* RTC Alarm Reg.                  */
DECL|macro|_RCNR
mdefine_line|#define _RCNR   &t;0x90010004&t;/* RTC CouNt Reg.                  */
DECL|macro|_RTTR
mdefine_line|#define _RTTR   &t;0x90010008&t;/* RTC Trim Reg.                   */
DECL|macro|_RTSR
mdefine_line|#define _RTSR   &t;0x90010010&t;/* RTC Status Reg.                 */
macro_line|#if LANGUAGE == C
DECL|macro|RTAR
mdefine_line|#define RTAR    &t;        &t;/* RTC Alarm Reg.                  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_RTAR)))
DECL|macro|RCNR
mdefine_line|#define RCNR    &t;        &t;/* RTC CouNt Reg.                  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_RCNR)))
DECL|macro|RTTR
mdefine_line|#define RTTR    &t;        &t;/* RTC Trim Reg.                   */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_RTTR)))
DECL|macro|RTSR
mdefine_line|#define RTSR    &t;        &t;/* RTC Status Reg.                 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_RTSR)))
macro_line|#endif /* LANGUAGE == C */
DECL|macro|RTTR_C
mdefine_line|#define RTTR_C  &t;Fld (16, 0)&t;/* clock divider Count - 1         */
DECL|macro|RTTR_D
mdefine_line|#define RTTR_D  &t;Fld (10, 16)&t;/* trim Delete count               */
multiline_comment|/* frtc = (1023*(C + 1) - D)*frtx/ */
multiline_comment|/*        (1023*(C + 1)^2)         */
multiline_comment|/* Trtc = (1023*(C + 1)^2)*Trtx/   */
multiline_comment|/*        (1023*(C + 1) - D)       */
DECL|macro|RTSR_AL
mdefine_line|#define RTSR_AL &t;0x00000001&t;/* ALarm detected                  */
DECL|macro|RTSR_HZ
mdefine_line|#define RTSR_HZ &t;0x00000002&t;/* 1 Hz clock detected             */
DECL|macro|RTSR_ALE
mdefine_line|#define RTSR_ALE&t;0x00000004&t;/* ALarm interrupt Enable          */
DECL|macro|RTSR_HZE
mdefine_line|#define RTSR_HZE&t;0x00000008&t;/* 1 Hz clock interrupt Enable     */
multiline_comment|/*&n; * Power Manager (PM) control registers&n; *&n; * Registers&n; *    PMCR      &t;Power Manager (PM) Control Register (read/write).&n; *    PSSR      &t;Power Manager (PM) Sleep Status Register (read/write).&n; *    PSPR      &t;Power Manager (PM) Scratch-Pad Register (read/write).&n; *    PWER      &t;Power Manager (PM) Wake-up Enable Register&n; *              &t;(read/write).&n; *    PCFR      &t;Power Manager (PM) general ConFiguration Register&n; *              &t;(read/write).&n; *    PPCR      &t;Power Manager (PM) Phase-Locked Loop (PLL)&n; *              &t;Configuration Register (read/write).&n; *    PGSR      &t;Power Manager (PM) General-Purpose Input/Output (GPIO)&n; *              &t;Sleep state Register (read/write, see GPIO pins).&n; *    POSR      &t;Power Manager (PM) Oscillator Status Register (read).&n; *&n; * Clocks&n; *    fxtl, Txtl&t;Frequency, period of the system crystal (3.6864 MHz&n; *              &t;or 3.5795 MHz).&n; *    fcpu, Tcpu&t;Frequency, period of the CPU core clock (CCLK).&n; */
DECL|macro|_PMCR
mdefine_line|#define _PMCR   &t;0x90020000&t;/* PM Control Reg.                 */
DECL|macro|_PSSR
mdefine_line|#define _PSSR   &t;0x90020004&t;/* PM Sleep Status Reg.            */
DECL|macro|_PSPR
mdefine_line|#define _PSPR   &t;0x90020008&t;/* PM Scratch-Pad Reg.             */
DECL|macro|_PWER
mdefine_line|#define _PWER   &t;0x9002000C&t;/* PM Wake-up Enable Reg.          */
DECL|macro|_PCFR
mdefine_line|#define _PCFR   &t;0x90020010&t;/* PM general ConFiguration Reg.   */
DECL|macro|_PPCR
mdefine_line|#define _PPCR   &t;0x90020014&t;/* PM PLL Configuration Reg.       */
DECL|macro|_PGSR
mdefine_line|#define _PGSR   &t;0x90020018&t;/* PM GPIO Sleep state Reg.        */
DECL|macro|_POSR
mdefine_line|#define _POSR   &t;0x9002001C&t;/* PM Oscillator Status Reg.       */
macro_line|#if LANGUAGE == C
DECL|macro|PMCR
mdefine_line|#define PMCR    &t;        &t;/* PM Control Reg.                 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_PMCR)))
DECL|macro|PSSR
mdefine_line|#define PSSR    &t;        &t;/* PM Sleep Status Reg.            */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_PSSR)))
DECL|macro|PSPR
mdefine_line|#define PSPR    &t;        &t;/* PM Scratch-Pad Reg.             */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_PSPR)))
DECL|macro|PWER
mdefine_line|#define PWER    &t;        &t;/* PM Wake-up Enable Reg.          */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_PWER)))
DECL|macro|PCFR
mdefine_line|#define PCFR    &t;        &t;/* PM general ConFiguration Reg.   */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_PCFR)))
DECL|macro|PPCR
mdefine_line|#define PPCR    &t;        &t;/* PM PLL Configuration Reg.       */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_PPCR)))
DECL|macro|PGSR
mdefine_line|#define PGSR    &t;        &t;/* PM GPIO Sleep state Reg.        */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_PGSR)))
DECL|macro|POSR
mdefine_line|#define POSR    &t;        &t;/* PM Oscillator Status Reg.       */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_POSR)))
macro_line|#elif LANGUAGE == Assembly
DECL|macro|PMCR
mdefine_line|#define PMCR          &t;(io_p2v (_PMCR))
DECL|macro|PSSR
mdefine_line|#define PSSR          &t;(io_p2v (_PSSR))
DECL|macro|PSPR
mdefine_line|#define PSPR          &t;(io_p2v (_PSPR))
DECL|macro|PWER
mdefine_line|#define PWER          &t;(io_p2v (_PWER))
DECL|macro|PCFR
mdefine_line|#define PCFR          &t;(io_p2v (_PCFR))
DECL|macro|PPCR
mdefine_line|#define PPCR          &t;(io_p2v (_PPCR))
DECL|macro|PGSR
mdefine_line|#define PGSR          &t;(io_p2v (_PGSR))
DECL|macro|POSR
mdefine_line|#define POSR          &t;(io_p2v (_POSR))
macro_line|#endif /* LANGUAGE == C */
DECL|macro|PMCR_SF
mdefine_line|#define PMCR_SF &t;0x00000001&t;/* Sleep Force (set only)          */
DECL|macro|PSSR_SS
mdefine_line|#define PSSR_SS &t;0x00000001&t;/* Software Sleep                  */
DECL|macro|PSSR_BFS
mdefine_line|#define PSSR_BFS&t;0x00000002&t;/* Battery Fault Status            */
multiline_comment|/* (BATT_FAULT)                    */
DECL|macro|PSSR_VFS
mdefine_line|#define PSSR_VFS&t;0x00000004&t;/* Vdd Fault Status (VDD_FAULT)    */
DECL|macro|PSSR_DH
mdefine_line|#define PSSR_DH &t;0x00000008&t;/* DRAM control Hold               */
DECL|macro|PSSR_PH
mdefine_line|#define PSSR_PH &t;0x00000010&t;/* Peripheral control Hold         */
DECL|macro|PWER_GPIO
mdefine_line|#define PWER_GPIO(Nb)&t;GPIO_GPIO (Nb)&t;/* GPIO [0..27] wake-up enable     */
DECL|macro|PWER_GPIO0
mdefine_line|#define PWER_GPIO0&t;PWER_GPIO (0)&t;/* GPIO  [0] wake-up enable        */
DECL|macro|PWER_GPIO1
mdefine_line|#define PWER_GPIO1&t;PWER_GPIO (1)&t;/* GPIO  [1] wake-up enable        */
DECL|macro|PWER_GPIO2
mdefine_line|#define PWER_GPIO2&t;PWER_GPIO (2)&t;/* GPIO  [2] wake-up enable        */
DECL|macro|PWER_GPIO3
mdefine_line|#define PWER_GPIO3&t;PWER_GPIO (3)&t;/* GPIO  [3] wake-up enable        */
DECL|macro|PWER_GPIO4
mdefine_line|#define PWER_GPIO4&t;PWER_GPIO (4)&t;/* GPIO  [4] wake-up enable        */
DECL|macro|PWER_GPIO5
mdefine_line|#define PWER_GPIO5&t;PWER_GPIO (5)&t;/* GPIO  [5] wake-up enable        */
DECL|macro|PWER_GPIO6
mdefine_line|#define PWER_GPIO6&t;PWER_GPIO (6)&t;/* GPIO  [6] wake-up enable        */
DECL|macro|PWER_GPIO7
mdefine_line|#define PWER_GPIO7&t;PWER_GPIO (7)&t;/* GPIO  [7] wake-up enable        */
DECL|macro|PWER_GPIO8
mdefine_line|#define PWER_GPIO8&t;PWER_GPIO (8)&t;/* GPIO  [8] wake-up enable        */
DECL|macro|PWER_GPIO9
mdefine_line|#define PWER_GPIO9&t;PWER_GPIO (9)&t;/* GPIO  [9] wake-up enable        */
DECL|macro|PWER_GPIO10
mdefine_line|#define PWER_GPIO10&t;PWER_GPIO (10)&t;/* GPIO [10] wake-up enable        */
DECL|macro|PWER_GPIO11
mdefine_line|#define PWER_GPIO11&t;PWER_GPIO (11)&t;/* GPIO [11] wake-up enable        */
DECL|macro|PWER_GPIO12
mdefine_line|#define PWER_GPIO12&t;PWER_GPIO (12)&t;/* GPIO [12] wake-up enable        */
DECL|macro|PWER_GPIO13
mdefine_line|#define PWER_GPIO13&t;PWER_GPIO (13)&t;/* GPIO [13] wake-up enable        */
DECL|macro|PWER_GPIO14
mdefine_line|#define PWER_GPIO14&t;PWER_GPIO (14)&t;/* GPIO [14] wake-up enable        */
DECL|macro|PWER_GPIO15
mdefine_line|#define PWER_GPIO15&t;PWER_GPIO (15)&t;/* GPIO [15] wake-up enable        */
DECL|macro|PWER_GPIO16
mdefine_line|#define PWER_GPIO16&t;PWER_GPIO (16)&t;/* GPIO [16] wake-up enable        */
DECL|macro|PWER_GPIO17
mdefine_line|#define PWER_GPIO17&t;PWER_GPIO (17)&t;/* GPIO [17] wake-up enable        */
DECL|macro|PWER_GPIO18
mdefine_line|#define PWER_GPIO18&t;PWER_GPIO (18)&t;/* GPIO [18] wake-up enable        */
DECL|macro|PWER_GPIO19
mdefine_line|#define PWER_GPIO19&t;PWER_GPIO (19)&t;/* GPIO [19] wake-up enable        */
DECL|macro|PWER_GPIO20
mdefine_line|#define PWER_GPIO20&t;PWER_GPIO (20)&t;/* GPIO [20] wake-up enable        */
DECL|macro|PWER_GPIO21
mdefine_line|#define PWER_GPIO21&t;PWER_GPIO (21)&t;/* GPIO [21] wake-up enable        */
DECL|macro|PWER_GPIO22
mdefine_line|#define PWER_GPIO22&t;PWER_GPIO (22)&t;/* GPIO [22] wake-up enable        */
DECL|macro|PWER_GPIO23
mdefine_line|#define PWER_GPIO23&t;PWER_GPIO (23)&t;/* GPIO [23] wake-up enable        */
DECL|macro|PWER_GPIO24
mdefine_line|#define PWER_GPIO24&t;PWER_GPIO (24)&t;/* GPIO [24] wake-up enable        */
DECL|macro|PWER_GPIO25
mdefine_line|#define PWER_GPIO25&t;PWER_GPIO (25)&t;/* GPIO [25] wake-up enable        */
DECL|macro|PWER_GPIO26
mdefine_line|#define PWER_GPIO26&t;PWER_GPIO (26)&t;/* GPIO [26] wake-up enable        */
DECL|macro|PWER_GPIO27
mdefine_line|#define PWER_GPIO27&t;PWER_GPIO (27)&t;/* GPIO [27] wake-up enable        */
DECL|macro|PWER_RTC
mdefine_line|#define PWER_RTC&t;0x80000000&t;/* RTC alarm wake-up enable        */
DECL|macro|PCFR_OPDE
mdefine_line|#define PCFR_OPDE&t;0x00000001&t;/* Oscillator Power-Down Enable    */
DECL|macro|PCFR_ClkRun
mdefine_line|#define PCFR_ClkRun&t;(PCFR_OPDE*0)&t;/*  Clock Running in sleep mode    */
DECL|macro|PCFR_ClkStp
mdefine_line|#define PCFR_ClkStp&t;(PCFR_OPDE*1)&t;/*  Clock Stopped in sleep mode    */
DECL|macro|PCFR_FP
mdefine_line|#define PCFR_FP &t;0x00000002&t;/* Float PCMCIA pins               */
DECL|macro|PCFR_PCMCIANeg
mdefine_line|#define PCFR_PCMCIANeg&t;(PCFR_FP*0)&t;/*  PCMCIA pins Negated (1)        */
DECL|macro|PCFR_PCMCIAFlt
mdefine_line|#define PCFR_PCMCIAFlt&t;(PCFR_FP*1)&t;/*  PCMCIA pins Floating           */
DECL|macro|PCFR_FS
mdefine_line|#define PCFR_FS &t;0x00000004&t;/* Float Static memory pins        */
DECL|macro|PCFR_StMemNeg
mdefine_line|#define PCFR_StMemNeg&t;(PCFR_FS*0)&t;/*  Static Memory pins Negated (1) */
DECL|macro|PCFR_StMemFlt
mdefine_line|#define PCFR_StMemFlt&t;(PCFR_FS*1)&t;/*  Static Memory pins Floating    */
DECL|macro|PCFR_FO
mdefine_line|#define PCFR_FO &t;0x00000008&t;/* Force RTC oscillator            */
multiline_comment|/* (32.768 kHz) enable On          */
DECL|macro|PPCR_CCF
mdefine_line|#define PPCR_CCF&t;Fld (5, 0)&t;/* CPU core Clock (CCLK) Freq.     */
DECL|macro|PPCR_Fx16
mdefine_line|#define PPCR_Fx16&t;        &t;/*  Freq. x 16 (fcpu = 16*fxtl)    */ &bslash;&n;                &t;(0x00 &lt;&lt; FShft (PPCR_CCF))
DECL|macro|PPCR_Fx20
mdefine_line|#define PPCR_Fx20&t;        &t;/*  Freq. x 20 (fcpu = 20*fxtl)    */ &bslash;&n;                &t;(0x01 &lt;&lt; FShft (PPCR_CCF))
DECL|macro|PPCR_Fx24
mdefine_line|#define PPCR_Fx24&t;        &t;/*  Freq. x 24 (fcpu = 24*fxtl)    */ &bslash;&n;                &t;(0x02 &lt;&lt; FShft (PPCR_CCF))
DECL|macro|PPCR_Fx28
mdefine_line|#define PPCR_Fx28&t;        &t;/*  Freq. x 28 (fcpu = 28*fxtl)    */ &bslash;&n;                &t;(0x03 &lt;&lt; FShft (PPCR_CCF))
DECL|macro|PPCR_Fx32
mdefine_line|#define PPCR_Fx32&t;        &t;/*  Freq. x 32 (fcpu = 32*fxtl)    */ &bslash;&n;                &t;(0x04 &lt;&lt; FShft (PPCR_CCF))
DECL|macro|PPCR_Fx36
mdefine_line|#define PPCR_Fx36&t;        &t;/*  Freq. x 36 (fcpu = 36*fxtl)    */ &bslash;&n;                &t;(0x05 &lt;&lt; FShft (PPCR_CCF))
DECL|macro|PPCR_Fx40
mdefine_line|#define PPCR_Fx40&t;        &t;/*  Freq. x 40 (fcpu = 40*fxtl)    */ &bslash;&n;                &t;(0x06 &lt;&lt; FShft (PPCR_CCF))
DECL|macro|PPCR_Fx44
mdefine_line|#define PPCR_Fx44&t;        &t;/*  Freq. x 44 (fcpu = 44*fxtl)    */ &bslash;&n;                &t;(0x07 &lt;&lt; FShft (PPCR_CCF))
DECL|macro|PPCR_Fx48
mdefine_line|#define PPCR_Fx48&t;        &t;/*  Freq. x 48 (fcpu = 48*fxtl)    */ &bslash;&n;                &t;(0x08 &lt;&lt; FShft (PPCR_CCF))
DECL|macro|PPCR_Fx52
mdefine_line|#define PPCR_Fx52&t;        &t;/*  Freq. x 52 (fcpu = 52*fxtl)    */ &bslash;&n;                &t;(0x09 &lt;&lt; FShft (PPCR_CCF))
DECL|macro|PPCR_Fx56
mdefine_line|#define PPCR_Fx56&t;        &t;/*  Freq. x 56 (fcpu = 56*fxtl)    */ &bslash;&n;                &t;(0x0A &lt;&lt; FShft (PPCR_CCF))
DECL|macro|PPCR_Fx60
mdefine_line|#define PPCR_Fx60&t;        &t;/*  Freq. x 60 (fcpu = 60*fxtl)    */ &bslash;&n;                &t;(0x0B &lt;&lt; FShft (PPCR_CCF))
DECL|macro|PPCR_Fx64
mdefine_line|#define PPCR_Fx64&t;        &t;/*  Freq. x 64 (fcpu = 64*fxtl)    */ &bslash;&n;                &t;(0x0C &lt;&lt; FShft (PPCR_CCF))
DECL|macro|PPCR_Fx68
mdefine_line|#define PPCR_Fx68&t;        &t;/*  Freq. x 68 (fcpu = 68*fxtl)    */ &bslash;&n;                &t;(0x0D &lt;&lt; FShft (PPCR_CCF))
DECL|macro|PPCR_Fx72
mdefine_line|#define PPCR_Fx72&t;        &t;/*  Freq. x 72 (fcpu = 72*fxtl)    */ &bslash;&n;                &t;(0x0E &lt;&lt; FShft (PPCR_CCF))
DECL|macro|PPCR_Fx76
mdefine_line|#define PPCR_Fx76&t;        &t;/*  Freq. x 76 (fcpu = 76*fxtl)    */ &bslash;&n;                &t;(0x0F &lt;&lt; FShft (PPCR_CCF))
multiline_comment|/*  3.6864 MHz crystal (fxtl):     */
DECL|macro|PPCR_F59_0MHz
mdefine_line|#define PPCR_F59_0MHz&t;PPCR_Fx16&t;/*   Freq. (fcpu) =  59.0 MHz      */
DECL|macro|PPCR_F73_7MHz
mdefine_line|#define PPCR_F73_7MHz&t;PPCR_Fx20&t;/*   Freq. (fcpu) =  73.7 MHz      */
DECL|macro|PPCR_F88_5MHz
mdefine_line|#define PPCR_F88_5MHz&t;PPCR_Fx24&t;/*   Freq. (fcpu) =  88.5 MHz      */
DECL|macro|PPCR_F103_2MHz
mdefine_line|#define PPCR_F103_2MHz&t;PPCR_Fx28&t;/*   Freq. (fcpu) = 103.2 MHz      */
DECL|macro|PPCR_F118_0MHz
mdefine_line|#define PPCR_F118_0MHz&t;PPCR_Fx32&t;/*   Freq. (fcpu) = 118.0 MHz      */
DECL|macro|PPCR_F132_7MHz
mdefine_line|#define PPCR_F132_7MHz&t;PPCR_Fx36&t;/*   Freq. (fcpu) = 132.7 MHz      */
DECL|macro|PPCR_F147_5MHz
mdefine_line|#define PPCR_F147_5MHz&t;PPCR_Fx40&t;/*   Freq. (fcpu) = 147.5 MHz      */
DECL|macro|PPCR_F162_2MHz
mdefine_line|#define PPCR_F162_2MHz&t;PPCR_Fx44&t;/*   Freq. (fcpu) = 162.2 MHz      */
DECL|macro|PPCR_F176_9MHz
mdefine_line|#define PPCR_F176_9MHz&t;PPCR_Fx48&t;/*   Freq. (fcpu) = 176.9 MHz      */
DECL|macro|PPCR_F191_7MHz
mdefine_line|#define PPCR_F191_7MHz&t;PPCR_Fx52&t;/*   Freq. (fcpu) = 191.7 MHz      */
DECL|macro|PPCR_F206_4MHz
mdefine_line|#define PPCR_F206_4MHz&t;PPCR_Fx56&t;/*   Freq. (fcpu) = 206.4 MHz      */
DECL|macro|PPCR_F221_2MHz
mdefine_line|#define PPCR_F221_2MHz&t;PPCR_Fx60&t;/*   Freq. (fcpu) = 221.2 MHz      */
DECL|macro|PPCR_F239_6MHz
mdefine_line|#define PPCR_F239_6MHz&t;PPCR_Fx64&t;/*   Freq. (fcpu) = 239.6 MHz      */
DECL|macro|PPCR_F250_7MHz
mdefine_line|#define PPCR_F250_7MHz&t;PPCR_Fx68&t;/*   Freq. (fcpu) = 250.7 MHz      */
DECL|macro|PPCR_F265_4MHz
mdefine_line|#define PPCR_F265_4MHz&t;PPCR_Fx72&t;/*   Freq. (fcpu) = 265.4 MHz      */
DECL|macro|PPCR_F280_2MHz
mdefine_line|#define PPCR_F280_2MHz&t;PPCR_Fx76&t;/*   Freq. (fcpu) = 280.2 MHz      */
multiline_comment|/*  3.5795 MHz crystal (fxtl):     */
DECL|macro|PPCR_F57_3MHz
mdefine_line|#define PPCR_F57_3MHz&t;PPCR_Fx16&t;/*   Freq. (fcpu) =  57.3 MHz      */
DECL|macro|PPCR_F71_6MHz
mdefine_line|#define PPCR_F71_6MHz&t;PPCR_Fx20&t;/*   Freq. (fcpu) =  71.6 MHz      */
DECL|macro|PPCR_F85_9MHz
mdefine_line|#define PPCR_F85_9MHz&t;PPCR_Fx24&t;/*   Freq. (fcpu) =  85.9 MHz      */
DECL|macro|PPCR_F100_2MHz
mdefine_line|#define PPCR_F100_2MHz&t;PPCR_Fx28&t;/*   Freq. (fcpu) = 100.2 MHz      */
DECL|macro|PPCR_F114_5MHz
mdefine_line|#define PPCR_F114_5MHz&t;PPCR_Fx32&t;/*   Freq. (fcpu) = 114.5 MHz      */
DECL|macro|PPCR_F128_9MHz
mdefine_line|#define PPCR_F128_9MHz&t;PPCR_Fx36&t;/*   Freq. (fcpu) = 128.9 MHz      */
DECL|macro|PPCR_F143_2MHz
mdefine_line|#define PPCR_F143_2MHz&t;PPCR_Fx40&t;/*   Freq. (fcpu) = 143.2 MHz      */
DECL|macro|PPCR_F157_5MHz
mdefine_line|#define PPCR_F157_5MHz&t;PPCR_Fx44&t;/*   Freq. (fcpu) = 157.5 MHz      */
DECL|macro|PPCR_F171_8MHz
mdefine_line|#define PPCR_F171_8MHz&t;PPCR_Fx48&t;/*   Freq. (fcpu) = 171.8 MHz      */
DECL|macro|PPCR_F186_1MHz
mdefine_line|#define PPCR_F186_1MHz&t;PPCR_Fx52&t;/*   Freq. (fcpu) = 186.1 MHz      */
DECL|macro|PPCR_F200_5MHz
mdefine_line|#define PPCR_F200_5MHz&t;PPCR_Fx56&t;/*   Freq. (fcpu) = 200.5 MHz      */
DECL|macro|PPCR_F214_8MHz
mdefine_line|#define PPCR_F214_8MHz&t;PPCR_Fx60&t;/*   Freq. (fcpu) = 214.8 MHz      */
DECL|macro|PPCR_F229_1MHz
mdefine_line|#define PPCR_F229_1MHz&t;PPCR_Fx64&t;/*   Freq. (fcpu) = 229.1 MHz      */
DECL|macro|PPCR_F243_4MHz
mdefine_line|#define PPCR_F243_4MHz&t;PPCR_Fx68&t;/*   Freq. (fcpu) = 243.4 MHz      */
DECL|macro|PPCR_F257_7MHz
mdefine_line|#define PPCR_F257_7MHz&t;PPCR_Fx72&t;/*   Freq. (fcpu) = 257.7 MHz      */
DECL|macro|PPCR_F272_0MHz
mdefine_line|#define PPCR_F272_0MHz&t;PPCR_Fx76&t;/*   Freq. (fcpu) = 272.0 MHz      */
DECL|macro|POSR_OOK
mdefine_line|#define POSR_OOK&t;0x00000001&t;/* RTC Oscillator (32.768 kHz) OK  */
multiline_comment|/*&n; * Reset Controller (RC) control registers&n; *&n; * Registers&n; *    RSRR      &t;Reset Controller (RC) Software Reset Register&n; *              &t;(read/write).&n; *    RCSR      &t;Reset Controller (RC) Status Register (read/write).&n; */
DECL|macro|_RSRR
mdefine_line|#define _RSRR   &t;0x90030000&t;/* RC Software Reset Reg.          */
DECL|macro|_RCSR
mdefine_line|#define _RCSR   &t;0x90030004&t;/* RC Status Reg.                  */
macro_line|#if LANGUAGE == C
DECL|macro|RSRR
mdefine_line|#define RSRR    &t;        &t;/* RC Software Reset Reg.          */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_RSRR)))
DECL|macro|RCSR
mdefine_line|#define RCSR    &t;        &t;/* RC Status Reg.                  */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_RCSR)))
macro_line|#endif /* LANGUAGE == C */
DECL|macro|RSRR_SWR
mdefine_line|#define RSRR_SWR&t;0x00000001&t;/* SoftWare Reset (set only)       */
DECL|macro|RCSR_HWR
mdefine_line|#define RCSR_HWR&t;0x00000001&t;/* HardWare Reset                  */
DECL|macro|RCSR_SWR
mdefine_line|#define RCSR_SWR&t;0x00000002&t;/* SoftWare Reset                  */
DECL|macro|RCSR_WDR
mdefine_line|#define RCSR_WDR&t;0x00000004&t;/* Watch-Dog Reset                 */
DECL|macro|RCSR_SMR
mdefine_line|#define RCSR_SMR&t;0x00000008&t;/* Sleep-Mode Reset                */
multiline_comment|/*&n; * Test unit control registers&n; *&n; * Registers&n; *    TUCR      &t;Test Unit Control Register (read/write).&n; */
DECL|macro|_TUCR
mdefine_line|#define _TUCR   &t;0x90030008&t;/* Test Unit Control Reg.          */
macro_line|#if LANGUAGE == C
DECL|macro|TUCR
mdefine_line|#define TUCR    &t;        &t;/* Test Unit Control Reg.          */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_TUCR)))
macro_line|#endif /* LANGUAGE == C */
DECL|macro|TUCR_TIC
mdefine_line|#define TUCR_TIC&t;0x00000040&t;/* TIC mode                        */
DECL|macro|TUCR_TTST
mdefine_line|#define TUCR_TTST&t;0x00000080&t;/* Trim TeST mode                  */
DECL|macro|TUCR_RCRC
mdefine_line|#define TUCR_RCRC&t;0x00000100&t;/* Richard&squot;s Cyclic Redundancy     */
multiline_comment|/* Check                           */
DECL|macro|TUCR_PMD
mdefine_line|#define TUCR_PMD&t;0x00000200&t;/* Power Management Disable        */
DECL|macro|TUCR_MR
mdefine_line|#define TUCR_MR &t;0x00000400&t;/* Memory Request mode             */
DECL|macro|TUCR_NoMB
mdefine_line|#define TUCR_NoMB&t;(TUCR_MR*0)&t;/*  No Memory Bus request &amp; grant  */
DECL|macro|TUCR_MBGPIO
mdefine_line|#define TUCR_MBGPIO&t;(TUCR_MR*1)&t;/*  Memory Bus request (MBREQ) &amp;   */
multiline_comment|/*  grant (MBGNT) on GPIO [22:21]  */
DECL|macro|TUCR_CTB
mdefine_line|#define TUCR_CTB&t;Fld (3, 20)&t;/* Clock Test Bits                 */
DECL|macro|TUCR_FDC
mdefine_line|#define TUCR_FDC&t;0x00800000&t;/* RTC Force Delete Count          */
DECL|macro|TUCR_FMC
mdefine_line|#define TUCR_FMC&t;0x01000000&t;/* Force Michelle&squot;s Control mode   */
DECL|macro|TUCR_TMC
mdefine_line|#define TUCR_TMC&t;0x02000000&t;/* RTC Trimmer Multiplexer Control */
DECL|macro|TUCR_DPS
mdefine_line|#define TUCR_DPS&t;0x04000000&t;/* Disallow Pad Sleep              */
DECL|macro|TUCR_TSEL
mdefine_line|#define TUCR_TSEL&t;Fld (3, 29)&t;/* clock Test SELect on GPIO [27]  */
DECL|macro|TUCR_32_768kHz
mdefine_line|#define TUCR_32_768kHz&t;        &t;/*  32.768 kHz osc. on GPIO [27]   */ &bslash;&n;                &t;(0 &lt;&lt; FShft (TUCR_TSEL))
DECL|macro|TUCR_3_6864MHz
mdefine_line|#define TUCR_3_6864MHz&t;        &t;/*  3.6864 MHz osc. on GPIO [27]   */ &bslash;&n;                &t;(1 &lt;&lt; FShft (TUCR_TSEL))
DECL|macro|TUCR_VDD
mdefine_line|#define TUCR_VDD&t;        &t;/*  VDD ring osc./16 on GPIO [27]  */ &bslash;&n;                &t;(2 &lt;&lt; FShft (TUCR_TSEL))
DECL|macro|TUCR_96MHzPLL
mdefine_line|#define TUCR_96MHzPLL&t;        &t;/*  96 MHz PLL/4 on GPIO [27]      */ &bslash;&n;                &t;(3 &lt;&lt; FShft (TUCR_TSEL))
DECL|macro|TUCR_Clock
mdefine_line|#define TUCR_Clock&t;        &t;/*  internal (fcpu/2) &amp; 32.768 kHz */ &bslash;&n;                &t;        &t;/*  Clocks on GPIO [26:27]         */ &bslash;&n;                &t;(4 &lt;&lt; FShft (TUCR_TSEL))
DECL|macro|TUCR_3_6864MHzA
mdefine_line|#define TUCR_3_6864MHzA&t;        &t;/*  3.6864 MHz osc. on GPIO [27]   */ &bslash;&n;                &t;        &t;/*  (Alternative)                  */ &bslash;&n;                &t;(5 &lt;&lt; FShft (TUCR_TSEL))
DECL|macro|TUCR_MainPLL
mdefine_line|#define TUCR_MainPLL&t;        &t;/*  Main PLL/16 on GPIO [27]       */ &bslash;&n;                &t;(6 &lt;&lt; FShft (TUCR_TSEL))
DECL|macro|TUCR_VDDL
mdefine_line|#define TUCR_VDDL&t;        &t;/*  VDDL ring osc./4 on GPIO [27]  */ &bslash;&n;                &t;(7 &lt;&lt; FShft (TUCR_TSEL))
multiline_comment|/*&n; * General-Purpose Input/Output (GPIO) control registers&n; *&n; * Registers&n; *    GPLR      &t;General-Purpose Input/Output (GPIO) Pin Level&n; *              &t;Register (read).&n; *    GPDR      &t;General-Purpose Input/Output (GPIO) Pin Direction&n; *              &t;Register (read/write).&n; *    GPSR      &t;General-Purpose Input/Output (GPIO) Pin output Set&n; *              &t;Register (write).&n; *    GPCR      &t;General-Purpose Input/Output (GPIO) Pin output Clear&n; *              &t;Register (write).&n; *    GRER      &t;General-Purpose Input/Output (GPIO) Rising-Edge&n; *              &t;detect Register (read/write).&n; *    GFER      &t;General-Purpose Input/Output (GPIO) Falling-Edge&n; *              &t;detect Register (read/write).&n; *    GEDR      &t;General-Purpose Input/Output (GPIO) Edge Detect&n; *              &t;status Register (read/write).&n; *    GAFR      &t;General-Purpose Input/Output (GPIO) Alternate&n; *              &t;Function Register (read/write).&n; *&n; * Clock&n; *    fcpu, Tcpu&t;Frequency, period of the CPU core clock (CCLK).&n; */
DECL|macro|_GPLR
mdefine_line|#define _GPLR   &t;0x90040000&t;/* GPIO Pin Level Reg.             */
DECL|macro|_GPDR
mdefine_line|#define _GPDR   &t;0x90040004&t;/* GPIO Pin Direction Reg.         */
DECL|macro|_GPSR
mdefine_line|#define _GPSR   &t;0x90040008&t;/* GPIO Pin output Set Reg.        */
DECL|macro|_GPCR
mdefine_line|#define _GPCR   &t;0x9004000C&t;/* GPIO Pin output Clear Reg.      */
DECL|macro|_GRER
mdefine_line|#define _GRER   &t;0x90040010&t;/* GPIO Rising-Edge detect Reg.    */
DECL|macro|_GFER
mdefine_line|#define _GFER   &t;0x90040014&t;/* GPIO Falling-Edge detect Reg.   */
DECL|macro|_GEDR
mdefine_line|#define _GEDR   &t;0x90040018&t;/* GPIO Edge Detect status Reg.    */
DECL|macro|_GAFR
mdefine_line|#define _GAFR   &t;0x9004001C&t;/* GPIO Alternate Function Reg.    */
macro_line|#if LANGUAGE == C
DECL|macro|GPLR
mdefine_line|#define GPLR    &t;        &t;/* GPIO Pin Level Reg.             */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_GPLR)))
DECL|macro|GPDR
mdefine_line|#define GPDR    &t;        &t;/* GPIO Pin Direction Reg.         */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_GPDR)))
DECL|macro|GPSR
mdefine_line|#define GPSR    &t;        &t;/* GPIO Pin output Set Reg.        */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_GPSR)))
DECL|macro|GPCR
mdefine_line|#define GPCR    &t;        &t;/* GPIO Pin output Clear Reg.      */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_GPCR)))
DECL|macro|GRER
mdefine_line|#define GRER    &t;        &t;/* GPIO Rising-Edge detect Reg.    */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_GRER)))
DECL|macro|GFER
mdefine_line|#define GFER    &t;        &t;/* GPIO Falling-Edge detect Reg.   */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_GFER)))
DECL|macro|GEDR
mdefine_line|#define GEDR    &t;        &t;/* GPIO Edge Detect status Reg.    */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_GEDR)))
DECL|macro|GAFR
mdefine_line|#define GAFR    &t;        &t;/* GPIO Alternate Function Reg.    */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_GAFR)))
macro_line|#elif LANGUAGE == Assembly
DECL|macro|GPLR
mdefine_line|#define GPLR  (io_p2v (_GPLR))
DECL|macro|GPDR
mdefine_line|#define GPDR  (io_p2v (_GPDR))
DECL|macro|GPSR
mdefine_line|#define GPSR  (io_p2v (_GPSR))
DECL|macro|GPCR
mdefine_line|#define GPCR  (io_p2v (_GPCR))
DECL|macro|GRER
mdefine_line|#define GRER  (io_p2v (_GRER))
DECL|macro|GFER
mdefine_line|#define GFER  (io_p2v (_GFER))
DECL|macro|GEDR
mdefine_line|#define GEDR  (io_p2v (_GEDR))
DECL|macro|GAFR
mdefine_line|#define GAFR  (io_p2v (_GAFR))
macro_line|#endif /* LANGUAGE == C */
DECL|macro|GPIO_MIN
mdefine_line|#define GPIO_MIN&t;(0)
DECL|macro|GPIO_MAX
mdefine_line|#define GPIO_MAX&t;(27)
DECL|macro|GPIO_GPIO
mdefine_line|#define GPIO_GPIO(Nb)&t;        &t;/* GPIO [0..27]                    */ &bslash;&n;                &t;(0x00000001 &lt;&lt; (Nb))
DECL|macro|GPIO_GPIO0
mdefine_line|#define GPIO_GPIO0&t;GPIO_GPIO (0)&t;/* GPIO  [0]                       */
DECL|macro|GPIO_GPIO1
mdefine_line|#define GPIO_GPIO1&t;GPIO_GPIO (1)&t;/* GPIO  [1]                       */
DECL|macro|GPIO_GPIO2
mdefine_line|#define GPIO_GPIO2&t;GPIO_GPIO (2)&t;/* GPIO  [2]                       */
DECL|macro|GPIO_GPIO3
mdefine_line|#define GPIO_GPIO3&t;GPIO_GPIO (3)&t;/* GPIO  [3]                       */
DECL|macro|GPIO_GPIO4
mdefine_line|#define GPIO_GPIO4&t;GPIO_GPIO (4)&t;/* GPIO  [4]                       */
DECL|macro|GPIO_GPIO5
mdefine_line|#define GPIO_GPIO5&t;GPIO_GPIO (5)&t;/* GPIO  [5]                       */
DECL|macro|GPIO_GPIO6
mdefine_line|#define GPIO_GPIO6&t;GPIO_GPIO (6)&t;/* GPIO  [6]                       */
DECL|macro|GPIO_GPIO7
mdefine_line|#define GPIO_GPIO7&t;GPIO_GPIO (7)&t;/* GPIO  [7]                       */
DECL|macro|GPIO_GPIO8
mdefine_line|#define GPIO_GPIO8&t;GPIO_GPIO (8)&t;/* GPIO  [8]                       */
DECL|macro|GPIO_GPIO9
mdefine_line|#define GPIO_GPIO9&t;GPIO_GPIO (9)&t;/* GPIO  [9]                       */
DECL|macro|GPIO_GPIO10
mdefine_line|#define GPIO_GPIO10&t;GPIO_GPIO (10)&t;/* GPIO [10]                       */
DECL|macro|GPIO_GPIO11
mdefine_line|#define GPIO_GPIO11&t;GPIO_GPIO (11)&t;/* GPIO [11]                       */
DECL|macro|GPIO_GPIO12
mdefine_line|#define GPIO_GPIO12&t;GPIO_GPIO (12)&t;/* GPIO [12]                       */
DECL|macro|GPIO_GPIO13
mdefine_line|#define GPIO_GPIO13&t;GPIO_GPIO (13)&t;/* GPIO [13]                       */
DECL|macro|GPIO_GPIO14
mdefine_line|#define GPIO_GPIO14&t;GPIO_GPIO (14)&t;/* GPIO [14]                       */
DECL|macro|GPIO_GPIO15
mdefine_line|#define GPIO_GPIO15&t;GPIO_GPIO (15)&t;/* GPIO [15]                       */
DECL|macro|GPIO_GPIO16
mdefine_line|#define GPIO_GPIO16&t;GPIO_GPIO (16)&t;/* GPIO [16]                       */
DECL|macro|GPIO_GPIO17
mdefine_line|#define GPIO_GPIO17&t;GPIO_GPIO (17)&t;/* GPIO [17]                       */
DECL|macro|GPIO_GPIO18
mdefine_line|#define GPIO_GPIO18&t;GPIO_GPIO (18)&t;/* GPIO [18]                       */
DECL|macro|GPIO_GPIO19
mdefine_line|#define GPIO_GPIO19&t;GPIO_GPIO (19)&t;/* GPIO [19]                       */
DECL|macro|GPIO_GPIO20
mdefine_line|#define GPIO_GPIO20&t;GPIO_GPIO (20)&t;/* GPIO [20]                       */
DECL|macro|GPIO_GPIO21
mdefine_line|#define GPIO_GPIO21&t;GPIO_GPIO (21)&t;/* GPIO [21]                       */
DECL|macro|GPIO_GPIO22
mdefine_line|#define GPIO_GPIO22&t;GPIO_GPIO (22)&t;/* GPIO [22]                       */
DECL|macro|GPIO_GPIO23
mdefine_line|#define GPIO_GPIO23&t;GPIO_GPIO (23)&t;/* GPIO [23]                       */
DECL|macro|GPIO_GPIO24
mdefine_line|#define GPIO_GPIO24&t;GPIO_GPIO (24)&t;/* GPIO [24]                       */
DECL|macro|GPIO_GPIO25
mdefine_line|#define GPIO_GPIO25&t;GPIO_GPIO (25)&t;/* GPIO [25]                       */
DECL|macro|GPIO_GPIO26
mdefine_line|#define GPIO_GPIO26&t;GPIO_GPIO (26)&t;/* GPIO [26]                       */
DECL|macro|GPIO_GPIO27
mdefine_line|#define GPIO_GPIO27&t;GPIO_GPIO (27)&t;/* GPIO [27]                       */
DECL|macro|GPIO_LDD
mdefine_line|#define GPIO_LDD(Nb)&t;        &t;/* LCD Data [8..15] (O)            */ &bslash;&n;                &t;GPIO_GPIO ((Nb) - 6)
DECL|macro|GPIO_LDD8
mdefine_line|#define GPIO_LDD8&t;GPIO_LDD (8)&t;/* LCD Data  [8] (O)               */
DECL|macro|GPIO_LDD9
mdefine_line|#define GPIO_LDD9&t;GPIO_LDD (9)&t;/* LCD Data  [9] (O)               */
DECL|macro|GPIO_LDD10
mdefine_line|#define GPIO_LDD10&t;GPIO_LDD (10)&t;/* LCD Data [10] (O)               */
DECL|macro|GPIO_LDD11
mdefine_line|#define GPIO_LDD11&t;GPIO_LDD (11)&t;/* LCD Data [11] (O)               */
DECL|macro|GPIO_LDD12
mdefine_line|#define GPIO_LDD12&t;GPIO_LDD (12)&t;/* LCD Data [12] (O)               */
DECL|macro|GPIO_LDD13
mdefine_line|#define GPIO_LDD13&t;GPIO_LDD (13)&t;/* LCD Data [13] (O)               */
DECL|macro|GPIO_LDD14
mdefine_line|#define GPIO_LDD14&t;GPIO_LDD (14)&t;/* LCD Data [14] (O)               */
DECL|macro|GPIO_LDD15
mdefine_line|#define GPIO_LDD15&t;GPIO_LDD (15)&t;/* LCD Data [15] (O)               */
multiline_comment|/* ser. port 4:                    */
DECL|macro|GPIO_SSP_TXD
mdefine_line|#define GPIO_SSP_TXD&t;GPIO_GPIO (10)&t;/*  SSP Transmit Data (O)          */
DECL|macro|GPIO_SSP_RXD
mdefine_line|#define GPIO_SSP_RXD&t;GPIO_GPIO (11)&t;/*  SSP Receive Data (I)           */
DECL|macro|GPIO_SSP_SCLK
mdefine_line|#define GPIO_SSP_SCLK&t;GPIO_GPIO (12)&t;/*  SSP Sample CLocK (O)           */
DECL|macro|GPIO_SSP_SFRM
mdefine_line|#define GPIO_SSP_SFRM&t;GPIO_GPIO (13)&t;/*  SSP Sample FRaMe (O)           */
multiline_comment|/* ser. port 1:                    */
DECL|macro|GPIO_UART_TXD
mdefine_line|#define GPIO_UART_TXD&t;GPIO_GPIO (14)&t;/*  UART Transmit Data (O)         */
DECL|macro|GPIO_UART_RXD
mdefine_line|#define GPIO_UART_RXD&t;GPIO_GPIO (15)&t;/*  UART Receive Data (I)          */
DECL|macro|GPIO_SDLC_SCLK
mdefine_line|#define GPIO_SDLC_SCLK&t;GPIO_GPIO (16)&t;/*  SDLC Sample CLocK (I/O)        */
DECL|macro|GPIO_SDLC_AAF
mdefine_line|#define GPIO_SDLC_AAF&t;GPIO_GPIO (17)&t;/*  SDLC Abort After Frame (O)     */
DECL|macro|GPIO_UART_SCLK1
mdefine_line|#define GPIO_UART_SCLK1&t;GPIO_GPIO (18)&t;/*  UART Sample CLocK 1 (I)        */
multiline_comment|/* ser. port 4:                    */
DECL|macro|GPIO_SSP_CLK
mdefine_line|#define GPIO_SSP_CLK&t;GPIO_GPIO (19)&t;/*  SSP external CLocK (I)         */
multiline_comment|/* ser. port 3:                    */
DECL|macro|GPIO_UART_SCLK3
mdefine_line|#define GPIO_UART_SCLK3&t;GPIO_GPIO (20)&t;/*  UART Sample CLocK 3 (I)        */
multiline_comment|/* ser. port 4:                    */
DECL|macro|GPIO_MCP_CLK
mdefine_line|#define GPIO_MCP_CLK&t;GPIO_GPIO (21)&t;/*  MCP CLocK (I)                  */
multiline_comment|/* test controller:                */
DECL|macro|GPIO_TIC_ACK
mdefine_line|#define GPIO_TIC_ACK&t;GPIO_GPIO (21)&t;/*  TIC ACKnowledge (O)            */
DECL|macro|GPIO_MBGNT
mdefine_line|#define GPIO_MBGNT&t;GPIO_GPIO (21)&t;/*  Memory Bus GraNT (O)           */
DECL|macro|GPIO_TREQA
mdefine_line|#define GPIO_TREQA&t;GPIO_GPIO (22)&t;/*  TIC REQuest A (I)              */
DECL|macro|GPIO_MBREQ
mdefine_line|#define GPIO_MBREQ&t;GPIO_GPIO (22)&t;/*  Memory Bus REQuest (I)         */
DECL|macro|GPIO_TREQB
mdefine_line|#define GPIO_TREQB&t;GPIO_GPIO (23)&t;/*  TIC REQuest B (I)              */
DECL|macro|GPIO_1Hz
mdefine_line|#define GPIO_1Hz&t;GPIO_GPIO (25)&t;/* 1 Hz clock (O)                  */
DECL|macro|GPIO_RCLK
mdefine_line|#define GPIO_RCLK&t;GPIO_GPIO (26)&t;/* internal (R) CLocK (O, fcpu/2)  */
DECL|macro|GPIO_32_768kHz
mdefine_line|#define GPIO_32_768kHz&t;GPIO_GPIO (27)&t;/* 32.768 kHz clock (O, RTC)       */
DECL|macro|GPDR_In
mdefine_line|#define GPDR_In &t;0       &t;/* Input                           */
DECL|macro|GPDR_Out
mdefine_line|#define GPDR_Out&t;1       &t;/* Output                          */
multiline_comment|/*&n; * Interrupt Controller (IC) control registers&n; *&n; * Registers&n; *    ICIP      &t;Interrupt Controller (IC) Interrupt ReQuest (IRQ)&n; *              &t;Pending register (read).&n; *    ICMR      &t;Interrupt Controller (IC) Mask Register (read/write).&n; *    ICLR      &t;Interrupt Controller (IC) Level Register (read/write).&n; *    ICCR      &t;Interrupt Controller (IC) Control Register&n; *              &t;(read/write).&n; *              &t;[The ICCR register is only implemented in versions 2.0&n; *              &t;(rev. = 8) and higher of the StrongARM SA-1100.]&n; *    ICFP      &t;Interrupt Controller (IC) Fast Interrupt reQuest&n; *              &t;(FIQ) Pending register (read).&n; *    ICPR      &t;Interrupt Controller (IC) Pending Register (read).&n; *              &t;[The ICPR register is active low (inverted) in&n; *              &t;versions 1.0 (rev. = 1) and 1.1 (rev. = 2) of the&n; *              &t;StrongARM SA-1100, it is active high (non-inverted) in&n; *              &t;versions 2.0 (rev. = 8) and higher.]&n; */
DECL|macro|_ICIP
mdefine_line|#define _ICIP   &t;0x90050000&t;/* IC IRQ Pending reg.             */
DECL|macro|_ICMR
mdefine_line|#define _ICMR   &t;0x90050004&t;/* IC Mask Reg.                    */
DECL|macro|_ICLR
mdefine_line|#define _ICLR   &t;0x90050008&t;/* IC Level Reg.                   */
DECL|macro|_ICCR
mdefine_line|#define _ICCR   &t;0x9005000C&t;/* IC Control Reg.                 */
DECL|macro|_ICFP
mdefine_line|#define _ICFP   &t;0x90050010&t;/* IC FIQ Pending reg.             */
DECL|macro|_ICPR
mdefine_line|#define _ICPR   &t;0x90050020&t;/* IC Pending Reg.                 */
macro_line|#if LANGUAGE == C
DECL|macro|ICIP
mdefine_line|#define ICIP    &t;        &t;/* IC IRQ Pending reg.             */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_ICIP)))
DECL|macro|ICMR
mdefine_line|#define ICMR    &t;        &t;/* IC Mask Reg.                    */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_ICMR)))
DECL|macro|ICLR
mdefine_line|#define ICLR    &t;        &t;/* IC Level Reg.                   */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_ICLR)))
DECL|macro|ICCR
mdefine_line|#define ICCR    &t;        &t;/* IC Control Reg.                 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_ICCR)))
DECL|macro|ICFP
mdefine_line|#define ICFP    &t;        &t;/* IC FIQ Pending reg.             */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_ICFP)))
DECL|macro|ICPR
mdefine_line|#define ICPR    &t;        &t;/* IC Pending Reg.                 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_ICPR)))
macro_line|#endif /* LANGUAGE == C */
DECL|macro|IC_GPIO
mdefine_line|#define IC_GPIO(Nb)&t;        &t;/* GPIO [0..10]                    */ &bslash;&n;                &t;(0x00000001 &lt;&lt; (Nb))
DECL|macro|IC_GPIO0
mdefine_line|#define IC_GPIO0&t;IC_GPIO (0)&t;/* GPIO  [0]                       */
DECL|macro|IC_GPIO1
mdefine_line|#define IC_GPIO1&t;IC_GPIO (1)&t;/* GPIO  [1]                       */
DECL|macro|IC_GPIO2
mdefine_line|#define IC_GPIO2&t;IC_GPIO (2)&t;/* GPIO  [2]                       */
DECL|macro|IC_GPIO3
mdefine_line|#define IC_GPIO3&t;IC_GPIO (3)&t;/* GPIO  [3]                       */
DECL|macro|IC_GPIO4
mdefine_line|#define IC_GPIO4&t;IC_GPIO (4)&t;/* GPIO  [4]                       */
DECL|macro|IC_GPIO5
mdefine_line|#define IC_GPIO5&t;IC_GPIO (5)&t;/* GPIO  [5]                       */
DECL|macro|IC_GPIO6
mdefine_line|#define IC_GPIO6&t;IC_GPIO (6)&t;/* GPIO  [6]                       */
DECL|macro|IC_GPIO7
mdefine_line|#define IC_GPIO7&t;IC_GPIO (7)&t;/* GPIO  [7]                       */
DECL|macro|IC_GPIO8
mdefine_line|#define IC_GPIO8&t;IC_GPIO (8)&t;/* GPIO  [8]                       */
DECL|macro|IC_GPIO9
mdefine_line|#define IC_GPIO9&t;IC_GPIO (9)&t;/* GPIO  [9]                       */
DECL|macro|IC_GPIO10
mdefine_line|#define IC_GPIO10&t;IC_GPIO (10)&t;/* GPIO [10]                       */
DECL|macro|IC_GPIO11_27
mdefine_line|#define IC_GPIO11_27&t;0x00000800&t;/* GPIO [11:27] (ORed)             */
DECL|macro|IC_LCD
mdefine_line|#define IC_LCD  &t;0x00001000&t;/* LCD controller                  */
DECL|macro|IC_Ser0UDC
mdefine_line|#define IC_Ser0UDC&t;0x00002000&t;/* Ser. port 0 UDC                 */
DECL|macro|IC_Ser1SDLC
mdefine_line|#define IC_Ser1SDLC&t;0x00004000&t;/* Ser. port 1 SDLC                */
DECL|macro|IC_Ser1UART
mdefine_line|#define IC_Ser1UART&t;0x00008000&t;/* Ser. port 1 UART                */
DECL|macro|IC_Ser2ICP
mdefine_line|#define IC_Ser2ICP&t;0x00010000&t;/* Ser. port 2 ICP                 */
DECL|macro|IC_Ser3UART
mdefine_line|#define IC_Ser3UART&t;0x00020000&t;/* Ser. port 3 UART                */
DECL|macro|IC_Ser4MCP
mdefine_line|#define IC_Ser4MCP&t;0x00040000&t;/* Ser. port 4 MCP                 */
DECL|macro|IC_Ser4SSP
mdefine_line|#define IC_Ser4SSP&t;0x00080000&t;/* Ser. port 4 SSP                 */
DECL|macro|IC_DMA
mdefine_line|#define IC_DMA(Nb)&t;        &t;/* DMA controller channel [0..5]   */ &bslash;&n;                &t;(0x00100000 &lt;&lt; (Nb))
DECL|macro|IC_DMA0
mdefine_line|#define IC_DMA0 &t;IC_DMA (0)&t;/* DMA controller channel 0        */
DECL|macro|IC_DMA1
mdefine_line|#define IC_DMA1 &t;IC_DMA (1)&t;/* DMA controller channel 1        */
DECL|macro|IC_DMA2
mdefine_line|#define IC_DMA2 &t;IC_DMA (2)&t;/* DMA controller channel 2        */
DECL|macro|IC_DMA3
mdefine_line|#define IC_DMA3 &t;IC_DMA (3)&t;/* DMA controller channel 3        */
DECL|macro|IC_DMA4
mdefine_line|#define IC_DMA4 &t;IC_DMA (4)&t;/* DMA controller channel 4        */
DECL|macro|IC_DMA5
mdefine_line|#define IC_DMA5 &t;IC_DMA (5)&t;/* DMA controller channel 5        */
DECL|macro|IC_OST
mdefine_line|#define IC_OST(Nb)&t;        &t;/* OS Timer match [0..3]           */ &bslash;&n;                &t;(0x04000000 &lt;&lt; (Nb))
DECL|macro|IC_OST0
mdefine_line|#define IC_OST0 &t;IC_OST (0)&t;/* OS Timer match 0                */
DECL|macro|IC_OST1
mdefine_line|#define IC_OST1 &t;IC_OST (1)&t;/* OS Timer match 1                */
DECL|macro|IC_OST2
mdefine_line|#define IC_OST2 &t;IC_OST (2)&t;/* OS Timer match 2                */
DECL|macro|IC_OST3
mdefine_line|#define IC_OST3 &t;IC_OST (3)&t;/* OS Timer match 3                */
DECL|macro|IC_RTC1Hz
mdefine_line|#define IC_RTC1Hz&t;0x40000000&t;/* RTC 1 Hz clock                  */
DECL|macro|IC_RTCAlrm
mdefine_line|#define IC_RTCAlrm&t;0x80000000&t;/* RTC Alarm                       */
DECL|macro|ICLR_IRQ
mdefine_line|#define ICLR_IRQ&t;0       &t;/* Interrupt ReQuest               */
DECL|macro|ICLR_FIQ
mdefine_line|#define ICLR_FIQ&t;1       &t;/* Fast Interrupt reQuest          */
DECL|macro|ICCR_DIM
mdefine_line|#define ICCR_DIM&t;0x00000001&t;/* Disable Idle-mode interrupt     */
multiline_comment|/* Mask                            */
DECL|macro|ICCR_IdleAllInt
mdefine_line|#define ICCR_IdleAllInt&t;(ICCR_DIM*0)&t;/*  Idle-mode All Interrupt enable */
multiline_comment|/*  (ICMR ignored)                 */
DECL|macro|ICCR_IdleMskInt
mdefine_line|#define ICCR_IdleMskInt&t;(ICCR_DIM*1)&t;/*  Idle-mode non-Masked Interrupt */
multiline_comment|/*  enable (ICMR used)             */
multiline_comment|/*&n; * Peripheral Pin Controller (PPC) control registers&n; *&n; * Registers&n; *    PPDR      &t;Peripheral Pin Controller (PPC) Pin Direction&n; *              &t;Register (read/write).&n; *    PPSR      &t;Peripheral Pin Controller (PPC) Pin State Register&n; *              &t;(read/write).&n; *    PPAR      &t;Peripheral Pin Controller (PPC) Pin Assignment&n; *              &t;Register (read/write).&n; *    PSDR      &t;Peripheral Pin Controller (PPC) Sleep-mode pin&n; *              &t;Direction Register (read/write).&n; *    PPFR      &t;Peripheral Pin Controller (PPC) Pin Flag Register&n; *              &t;(read).&n; */
DECL|macro|_PPDR
mdefine_line|#define _PPDR   &t;0x90060000&t;/* PPC Pin Direction Reg.          */
DECL|macro|_PPSR
mdefine_line|#define _PPSR   &t;0x90060004&t;/* PPC Pin State Reg.              */
DECL|macro|_PPAR
mdefine_line|#define _PPAR   &t;0x90060008&t;/* PPC Pin Assignment Reg.         */
DECL|macro|_PSDR
mdefine_line|#define _PSDR   &t;0x9006000C&t;/* PPC Sleep-mode pin Direction    */
multiline_comment|/* Reg.                            */
DECL|macro|_PPFR
mdefine_line|#define _PPFR   &t;0x90060010&t;/* PPC Pin Flag Reg.               */
macro_line|#if LANGUAGE == C
DECL|macro|PPDR
mdefine_line|#define PPDR    &t;        &t;/* PPC Pin Direction Reg.          */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_PPDR)))
DECL|macro|PPSR
mdefine_line|#define PPSR    &t;        &t;/* PPC Pin State Reg.              */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_PPSR)))
DECL|macro|PPAR
mdefine_line|#define PPAR    &t;        &t;/* PPC Pin Assignment Reg.         */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_PPAR)))
DECL|macro|PSDR
mdefine_line|#define PSDR    &t;        &t;/* PPC Sleep-mode pin Direction    */ &bslash;&n;                &t;        &t;/* Reg.                            */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_PSDR)))
DECL|macro|PPFR
mdefine_line|#define PPFR    &t;        &t;/* PPC Pin Flag Reg.               */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_PPFR)))
macro_line|#endif /* LANGUAGE == C */
DECL|macro|PPC_LDD
mdefine_line|#define PPC_LDD(Nb)&t;        &t;/* LCD Data [0..7]                 */ &bslash;&n;                &t;(0x00000001 &lt;&lt; (Nb))
DECL|macro|PPC_LDD0
mdefine_line|#define PPC_LDD0&t;PPC_LDD (0)&t;/* LCD Data [0]                    */
DECL|macro|PPC_LDD1
mdefine_line|#define PPC_LDD1&t;PPC_LDD (1)&t;/* LCD Data [1]                    */
DECL|macro|PPC_LDD2
mdefine_line|#define PPC_LDD2&t;PPC_LDD (2)&t;/* LCD Data [2]                    */
DECL|macro|PPC_LDD3
mdefine_line|#define PPC_LDD3&t;PPC_LDD (3)&t;/* LCD Data [3]                    */
DECL|macro|PPC_LDD4
mdefine_line|#define PPC_LDD4&t;PPC_LDD (4)&t;/* LCD Data [4]                    */
DECL|macro|PPC_LDD5
mdefine_line|#define PPC_LDD5&t;PPC_LDD (5)&t;/* LCD Data [5]                    */
DECL|macro|PPC_LDD6
mdefine_line|#define PPC_LDD6&t;PPC_LDD (6)&t;/* LCD Data [6]                    */
DECL|macro|PPC_LDD7
mdefine_line|#define PPC_LDD7&t;PPC_LDD (7)&t;/* LCD Data [7]                    */
DECL|macro|PPC_L_PCLK
mdefine_line|#define PPC_L_PCLK&t;0x00000100&t;/* LCD Pixel CLocK                 */
DECL|macro|PPC_L_LCLK
mdefine_line|#define PPC_L_LCLK&t;0x00000200&t;/* LCD Line CLocK                  */
DECL|macro|PPC_L_FCLK
mdefine_line|#define PPC_L_FCLK&t;0x00000400&t;/* LCD Frame CLocK                 */
DECL|macro|PPC_L_BIAS
mdefine_line|#define PPC_L_BIAS&t;0x00000800&t;/* LCD AC BIAS                     */
multiline_comment|/* ser. port 1:                    */
DECL|macro|PPC_TXD1
mdefine_line|#define PPC_TXD1&t;0x00001000&t;/*  SDLC/UART Transmit Data 1      */
DECL|macro|PPC_RXD1
mdefine_line|#define PPC_RXD1&t;0x00002000&t;/*  SDLC/UART Receive Data 1       */
multiline_comment|/* ser. port 2:                    */
DECL|macro|PPC_TXD2
mdefine_line|#define PPC_TXD2&t;0x00004000&t;/*  IPC Transmit Data 2            */
DECL|macro|PPC_RXD2
mdefine_line|#define PPC_RXD2&t;0x00008000&t;/*  IPC Receive Data 2             */
multiline_comment|/* ser. port 3:                    */
DECL|macro|PPC_TXD3
mdefine_line|#define PPC_TXD3&t;0x00010000&t;/*  UART Transmit Data 3           */
DECL|macro|PPC_RXD3
mdefine_line|#define PPC_RXD3&t;0x00020000&t;/*  UART Receive Data 3            */
multiline_comment|/* ser. port 4:                    */
DECL|macro|PPC_TXD4
mdefine_line|#define PPC_TXD4&t;0x00040000&t;/*  MCP/SSP Transmit Data 4        */
DECL|macro|PPC_RXD4
mdefine_line|#define PPC_RXD4&t;0x00080000&t;/*  MCP/SSP Receive Data 4         */
DECL|macro|PPC_SCLK
mdefine_line|#define PPC_SCLK&t;0x00100000&t;/*  MCP/SSP Sample CLocK           */
DECL|macro|PPC_SFRM
mdefine_line|#define PPC_SFRM&t;0x00200000&t;/*  MCP/SSP Sample FRaMe           */
DECL|macro|PPDR_In
mdefine_line|#define PPDR_In &t;0       &t;/* Input                           */
DECL|macro|PPDR_Out
mdefine_line|#define PPDR_Out&t;1       &t;/* Output                          */
multiline_comment|/* ser. port 1:                    */
DECL|macro|PPAR_UPR
mdefine_line|#define PPAR_UPR&t;0x00001000&t;/*  UART Pin Reassignment          */
DECL|macro|PPAR_UARTTR
mdefine_line|#define PPAR_UARTTR&t;(PPAR_UPR*0)&t;/*   UART on TXD_1 &amp; RXD_1         */
DECL|macro|PPAR_UARTGPIO
mdefine_line|#define PPAR_UARTGPIO&t;(PPAR_UPR*1)&t;/*   UART on GPIO [14:15]          */
multiline_comment|/* ser. port 4:                    */
DECL|macro|PPAR_SPR
mdefine_line|#define PPAR_SPR&t;0x00040000&t;/*  SSP Pin Reassignment           */
DECL|macro|PPAR_SSPTRSS
mdefine_line|#define PPAR_SSPTRSS&t;(PPAR_SPR*0)&t;/*   SSP on TXD_C, RXD_C, SCLK_C,  */
multiline_comment|/*   &amp; SFRM_C                      */
DECL|macro|PPAR_SSPGPIO
mdefine_line|#define PPAR_SSPGPIO&t;(PPAR_SPR*1)&t;/*   SSP on GPIO [10:13]           */
DECL|macro|PSDR_OutL
mdefine_line|#define PSDR_OutL&t;0       &t;/* Output Low in sleep mode        */
DECL|macro|PSDR_Flt
mdefine_line|#define PSDR_Flt&t;1       &t;/* Floating (input) in sleep mode  */
DECL|macro|PPFR_LCD
mdefine_line|#define PPFR_LCD&t;0x00000001&t;/* LCD controller                  */
DECL|macro|PPFR_SP1TX
mdefine_line|#define PPFR_SP1TX&t;0x00001000&t;/* Ser. Port 1 SDLC/UART Transmit  */
DECL|macro|PPFR_SP1RX
mdefine_line|#define PPFR_SP1RX&t;0x00002000&t;/* Ser. Port 1 SDLC/UART Receive   */
DECL|macro|PPFR_SP2TX
mdefine_line|#define PPFR_SP2TX&t;0x00004000&t;/* Ser. Port 2 ICP Transmit        */
DECL|macro|PPFR_SP2RX
mdefine_line|#define PPFR_SP2RX&t;0x00008000&t;/* Ser. Port 2 ICP Receive         */
DECL|macro|PPFR_SP3TX
mdefine_line|#define PPFR_SP3TX&t;0x00010000&t;/* Ser. Port 3 UART Transmit       */
DECL|macro|PPFR_SP3RX
mdefine_line|#define PPFR_SP3RX&t;0x00020000&t;/* Ser. Port 3 UART Receive        */
DECL|macro|PPFR_SP4
mdefine_line|#define PPFR_SP4&t;0x00040000&t;/* Ser. Port 4 MCP/SSP             */
DECL|macro|PPFR_PerEn
mdefine_line|#define PPFR_PerEn&t;0       &t;/* Peripheral Enabled              */
DECL|macro|PPFR_PPCEn
mdefine_line|#define PPFR_PPCEn&t;1       &t;/* PPC Enabled                     */
multiline_comment|/*&n; * Dynamic Random-Access Memory (DRAM) control registers&n; *&n; * Registers&n; *    MDCNFG    &t;Memory system: Dynamic Random-Access Memory (DRAM)&n; *              &t;CoNFiGuration register (read/write).&n; *    MDCAS0    &t;Memory system: Dynamic Random-Access Memory (DRAM)&n; *              &t;Column Address Strobe (CAS) shift register 0&n; *              &t;(read/write).&n; *    MDCAS1    &t;Memory system: Dynamic Random-Access Memory (DRAM)&n; *              &t;Column Address Strobe (CAS) shift register 1&n; *              &t;(read/write).&n; *    MDCAS2    &t;Memory system: Dynamic Random-Access Memory (DRAM)&n; *              &t;Column Address Strobe (CAS) shift register 2&n; *              &t;(read/write).&n; *&n; * Clocks&n; *    fcpu, Tcpu&t;Frequency, period of the CPU core clock (CCLK).&n; *    fmem, Tmem&t;Frequency, period of the memory clock (fmem = fcpu/2).&n; *    fcas, Tcas&t;Frequency, period of the DRAM CAS shift registers.&n; */
multiline_comment|/* Memory system:                  */
DECL|macro|_MDCNFG
mdefine_line|#define _MDCNFG &t;0xA0000000&t;/*  DRAM CoNFiGuration reg.        */
DECL|macro|_MDCAS
mdefine_line|#define _MDCAS(Nb)&t;        &t;/*  DRAM CAS shift reg. [0..3]     */ &bslash;&n;                &t;(0xA0000004 + (Nb)*4)
DECL|macro|_MDCAS0
mdefine_line|#define _MDCAS0 &t;_MDCAS (0)&t;/*  DRAM CAS shift reg. 0          */
DECL|macro|_MDCAS1
mdefine_line|#define _MDCAS1 &t;_MDCAS (1)&t;/*  DRAM CAS shift reg. 1          */
DECL|macro|_MDCAS2
mdefine_line|#define _MDCAS2 &t;_MDCAS (2)&t;/*  DRAM CAS shift reg. 2          */
macro_line|#if LANGUAGE == C
multiline_comment|/* Memory system:                  */
DECL|macro|MDCNFG
mdefine_line|#define MDCNFG  &t;        &t;/*  DRAM CoNFiGuration reg.        */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_MDCNFG)))
DECL|macro|MDCAS
mdefine_line|#define MDCAS   &t;        &t;/*  DRAM CAS shift reg. [0..3]     */ &bslash;&n;                &t;((volatile Word *) io_p2v (_MDCAS (0)))
DECL|macro|MDCAS0
mdefine_line|#define MDCAS0  &t;(MDCAS [0])&t;/*  DRAM CAS shift reg. 0          */
DECL|macro|MDCAS1
mdefine_line|#define MDCAS1  &t;(MDCAS [1])&t;/*  DRAM CAS shift reg. 1          */
DECL|macro|MDCAS2
mdefine_line|#define MDCAS2  &t;(MDCAS [2])&t;/*  DRAM CAS shift reg. 2          */
macro_line|#elif LANGUAGE == Assembly
DECL|macro|MDCNFG
mdefine_line|#define MDCNFG&t;&t;(io_p2v(_MDCNFG))
macro_line|#endif /* LANGUAGE == C */
multiline_comment|/* SA1100 MDCNFG values */
DECL|macro|MDCNFG_DE
mdefine_line|#define MDCNFG_DE(Nb)&t;        &t;/* DRAM Enable bank [0..3]         */ &bslash;&n;                &t;(0x00000001 &lt;&lt; (Nb))
DECL|macro|MDCNFG_DE0
mdefine_line|#define MDCNFG_DE0&t;MDCNFG_DE (0)&t;/* DRAM Enable bank 0              */
DECL|macro|MDCNFG_DE1
mdefine_line|#define MDCNFG_DE1&t;MDCNFG_DE (1)&t;/* DRAM Enable bank 1              */
DECL|macro|MDCNFG_DE2
mdefine_line|#define MDCNFG_DE2&t;MDCNFG_DE (2)&t;/* DRAM Enable bank 2              */
DECL|macro|MDCNFG_DE3
mdefine_line|#define MDCNFG_DE3&t;MDCNFG_DE (3)&t;/* DRAM Enable bank 3              */
DECL|macro|MDCNFG_DRAC
mdefine_line|#define MDCNFG_DRAC&t;Fld (2, 4)&t;/* DRAM Row Address Count - 9      */
DECL|macro|MDCNFG_RowAdd
mdefine_line|#define MDCNFG_RowAdd(Add)      &t;/*  Row Address count [9..12]      */ &bslash;&n;                &t;(((Add) - 9) &lt;&lt; FShft (MDCNFG_DRAC))
DECL|macro|MDCNFG_CDB2
mdefine_line|#define MDCNFG_CDB2&t;0x00000040&t;/* shift reg. Clock Divide By 2    */
multiline_comment|/* (fcas = fcpu/2)                 */
DECL|macro|MDCNFG_TRP
mdefine_line|#define MDCNFG_TRP&t;Fld (4, 7)&t;/* Time RAS Pre-charge - 1 [Tmem]  */
DECL|macro|MDCNFG_PrChrg
mdefine_line|#define MDCNFG_PrChrg(Tcpu)     &t;/*  Pre-Charge time [2..32 Tcpu]   */ &bslash;&n;                &t;(((Tcpu) - 2)/2 &lt;&lt; FShft (MDCNFG_TRP))
DECL|macro|MDCNFG_CeilPrChrg
mdefine_line|#define MDCNFG_CeilPrChrg(Tcpu) &t;/*  Ceil. of PrChrg [2..32 Tcpu]   */ &bslash;&n;                &t;(((Tcpu) - 1)/2 &lt;&lt; FShft (MDCNFG_TRP))
DECL|macro|MDCNFG_TRASR
mdefine_line|#define MDCNFG_TRASR&t;Fld (4, 11)&t;/* Time RAS Refresh - 1 [Tmem]     */
DECL|macro|MDCNFG_Ref
mdefine_line|#define MDCNFG_Ref(Tcpu)        &t;/*  Refresh time [2..32 Tcpu]      */ &bslash;&n;                &t;(((Tcpu) - 2)/2 &lt;&lt; FShft (MDCNFG_TRASR))
DECL|macro|MDCNFG_CeilRef
mdefine_line|#define MDCNFG_CeilRef(Tcpu)    &t;/*  Ceil. of Ref [2..32 Tcpu]      */ &bslash;&n;                &t;(((Tcpu) - 1)/2 &lt;&lt; FShft (MDCNFG_TRASR))
DECL|macro|MDCNFG_TDL
mdefine_line|#define MDCNFG_TDL&t;Fld (2, 15)&t;/* Time Data Latch [Tcpu]          */
DECL|macro|MDCNFG_DataLtch
mdefine_line|#define MDCNFG_DataLtch(Tcpu)   &t;/*  Data Latch delay [0..3 Tcpu]   */ &bslash;&n;                &t;((Tcpu) &lt;&lt; FShft (MDCNFG_TDL))
DECL|macro|MDCNFG_DRI
mdefine_line|#define MDCNFG_DRI&t;Fld (15, 17)&t;/* min. DRAM Refresh Interval/4    */
multiline_comment|/* [Tmem]                          */
DECL|macro|MDCNFG_RefInt
mdefine_line|#define MDCNFG_RefInt(Tcpu)     &t;/*  min. Refresh Interval          */ &bslash;&n;                &t;        &t;/*  [0..262136 Tcpu]               */ &bslash;&n;                &t;((Tcpu)/8 &lt;&lt; FShft (MDCNFG_DRI))
multiline_comment|/* SA1110 MDCNFG values */
DECL|macro|MDCNFG_SA1110_DE0
mdefine_line|#define MDCNFG_SA1110_DE0&t;0x00000001&t;/* DRAM Enable bank 0        */
DECL|macro|MDCNFG_SA1110_DE1
mdefine_line|#define MDCNFG_SA1110_DE1&t;0x00000002 &t;/* DRAM Enable bank 1        */
DECL|macro|MDCNFG_SA1110_DTIM0
mdefine_line|#define MDCNFG_SA1110_DTIM0&t;0x00000004&t;/* DRAM timing type 0/1      */
DECL|macro|MDCNFG_SA1110_DWID0
mdefine_line|#define MDCNFG_SA1110_DWID0&t;0x00000008&t;/* DRAM bus width 0/1        */
DECL|macro|MDCNFG_SA1110_DRAC0
mdefine_line|#define MDCNFG_SA1110_DRAC0&t;Fld(3, 4)&t;/* DRAM row addr bit count   */
multiline_comment|/* bank 0/1                  */
DECL|macro|MDCNFG_SA1110_CDB20
mdefine_line|#define MDCNFG_SA1110_CDB20&t;0x00000080&t;/* Mem Clock divide by 2 0/1 */
DECL|macro|MDCNFG_SA1110_TRP0
mdefine_line|#define MDCNFG_SA1110_TRP0&t;Fld(3, 8)&t;/* RAS precharge 0/1         */
DECL|macro|MDCNFG_SA1110_TDL0
mdefine_line|#define MDCNFG_SA1110_TDL0&t;Fld(2, 12)&t;/* Data input latch after CAS*/
multiline_comment|/* deassertion 0/1           */
DECL|macro|MDCNFG_SA1110_TWR0
mdefine_line|#define MDCNFG_SA1110_TWR0&t;Fld(2, 14)&t;/* SDRAM write recovery 0/1  */
DECL|macro|MDCNFG_SA1110_DE2
mdefine_line|#define MDCNFG_SA1110_DE2&t;0x00010000&t;/* DRAM Enable bank 0        */
DECL|macro|MDCNFG_SA1110_DE3
mdefine_line|#define MDCNFG_SA1110_DE3&t;0x00020000 &t;/* DRAM Enable bank 1        */
DECL|macro|MDCNFG_SA1110_DTIM2
mdefine_line|#define MDCNFG_SA1110_DTIM2&t;0x00040000&t;/* DRAM timing type 0/1      */
DECL|macro|MDCNFG_SA1110_DWID2
mdefine_line|#define MDCNFG_SA1110_DWID2&t;0x00080000&t;/* DRAM bus width 0/1        */
DECL|macro|MDCNFG_SA1110_DRAC2
mdefine_line|#define MDCNFG_SA1110_DRAC2&t;Fld(3, 20)&t;/* DRAM row addr bit count   */
multiline_comment|/* bank 0/1                  */
DECL|macro|MDCNFG_SA1110_CDB22
mdefine_line|#define MDCNFG_SA1110_CDB22&t;0x00800000&t;/* Mem Clock divide by 2 0/1 */
DECL|macro|MDCNFG_SA1110_TRP2
mdefine_line|#define MDCNFG_SA1110_TRP2&t;Fld(3, 24)&t;/* RAS precharge 0/1         */
DECL|macro|MDCNFG_SA1110_TDL2
mdefine_line|#define MDCNFG_SA1110_TDL2&t;Fld(2, 28)&t;/* Data input latch after CAS*/
multiline_comment|/* deassertion 0/1           */
DECL|macro|MDCNFG_SA1110_TWR2
mdefine_line|#define MDCNFG_SA1110_TWR2&t;Fld(2, 30)&t;/* SDRAM write recovery 0/1  */
multiline_comment|/*&n; * Static memory control registers&n; *&n; * Registers&n; *    MSC0      &t;Memory system: Static memory Control register 0&n; *              &t;(read/write).&n; *    MSC1      &t;Memory system: Static memory Control register 1&n; *              &t;(read/write).&n; *&n; * Clocks&n; *    fcpu, Tcpu&t;Frequency, period of the CPU core clock (CCLK).&n; *    fmem, Tmem&t;Frequency, period of the memory clock (fmem = fcpu/2).&n; */
multiline_comment|/* Memory system:                  */
DECL|macro|_MSC
mdefine_line|#define _MSC(Nb)&t;        &t;/*  Static memory Control reg.     */ &bslash;&n;                &t;        &t;/*  [0..1]                         */ &bslash;&n;                &t;(0xA0000010 + (Nb)*4)
DECL|macro|_MSC0
mdefine_line|#define _MSC0   &t;_MSC (0)&t;/*  Static memory Control reg. 0   */
DECL|macro|_MSC1
mdefine_line|#define _MSC1   &t;_MSC (1)&t;/*  Static memory Control reg. 1   */
DECL|macro|_MSC2
mdefine_line|#define _MSC2&t;&t;0xA000002C&t;/*  Static memory Control reg. 2, not contiguous   */
macro_line|#if LANGUAGE == C
multiline_comment|/* Memory system:                  */
DECL|macro|MSC
mdefine_line|#define MSC     &t;        &t;/*  Static memory Control reg.     */ &bslash;&n;                &t;        &t;/*  [0..1]                         */ &bslash;&n;                &t;((volatile Word *) io_p2v (_MSC (0)))
DECL|macro|MSC0
mdefine_line|#define MSC0    &t;(MSC [0])&t;/*  Static memory Control reg. 0   */
DECL|macro|MSC1
mdefine_line|#define MSC1    &t;(MSC [1])&t;/*  Static memory Control reg. 1   */
DECL|macro|MSC2
mdefine_line|#define MSC2    &t;(*(volatile Word *) io_p2v (_MSC2))&t;/*  Static memory Control reg. 2   */
macro_line|#elif LANGUAGE == Assembly
DECL|macro|MSC0
mdefine_line|#define MSC0&t;&t;io_p2v(0xa0000010)
DECL|macro|MSC1
mdefine_line|#define MSC1&t;&t;io_p2v(0xa0000014)
DECL|macro|MSC2
mdefine_line|#define MSC2&t;&t;io_p2v(0xa000002c)
macro_line|#endif /* LANGUAGE == C */
DECL|macro|MSC_Bnk
mdefine_line|#define MSC_Bnk(Nb)&t;        &t;/* static memory Bank [0..3]       */ &bslash;&n;                &t;Fld (16, ((Nb) Modulo 2)*16)
DECL|macro|MSC0_Bnk0
mdefine_line|#define MSC0_Bnk0&t;MSC_Bnk (0)&t;/* static memory Bank 0            */
DECL|macro|MSC0_Bnk1
mdefine_line|#define MSC0_Bnk1&t;MSC_Bnk (1)&t;/* static memory Bank 1            */
DECL|macro|MSC1_Bnk2
mdefine_line|#define MSC1_Bnk2&t;MSC_Bnk (2)&t;/* static memory Bank 2            */
DECL|macro|MSC1_Bnk3
mdefine_line|#define MSC1_Bnk3&t;MSC_Bnk (3)&t;/* static memory Bank 3            */
DECL|macro|MSC_RT
mdefine_line|#define MSC_RT  &t;Fld (2, 0)&t;/* ROM/static memory Type          */
DECL|macro|MSC_NonBrst
mdefine_line|#define MSC_NonBrst&t;        &t;/*  Non-Burst static memory        */ &bslash;&n;                &t;(0 &lt;&lt; FShft (MSC_RT))
DECL|macro|MSC_SRAM
mdefine_line|#define MSC_SRAM&t;        &t;/*  32-bit byte-writable SRAM      */ &bslash;&n;                &t;(1 &lt;&lt; FShft (MSC_RT))
DECL|macro|MSC_Brst4
mdefine_line|#define MSC_Brst4&t;        &t;/*  Burst-of-4 static memory       */ &bslash;&n;                &t;(2 &lt;&lt; FShft (MSC_RT))
DECL|macro|MSC_Brst8
mdefine_line|#define MSC_Brst8&t;        &t;/*  Burst-of-8 static memory       */ &bslash;&n;                &t;(3 &lt;&lt; FShft (MSC_RT))
DECL|macro|MSC_RBW
mdefine_line|#define MSC_RBW &t;0x0004  &t;/* ROM/static memory Bus Width     */
DECL|macro|MSC_32BitStMem
mdefine_line|#define MSC_32BitStMem&t;(MSC_RBW*0)&t;/*  32-Bit Static Memory           */
DECL|macro|MSC_16BitStMem
mdefine_line|#define MSC_16BitStMem&t;(MSC_RBW*1)&t;/*  16-Bit Static Memory           */
DECL|macro|MSC_RDF
mdefine_line|#define MSC_RDF &t;Fld (5, 3)&t;/* ROM/static memory read Delay    */
multiline_comment|/* First access - 1(.5) [Tmem]     */
DECL|macro|MSC_1stRdAcc
mdefine_line|#define MSC_1stRdAcc(Tcpu)      &t;/*  1st Read Access time (burst    */ &bslash;&n;                &t;        &t;/*  static memory) [3..65 Tcpu]    */ &bslash;&n;                &t;((((Tcpu) - 3)/2) &lt;&lt; FShft (MSC_RDF))
DECL|macro|MSC_Ceil1stRdAcc
mdefine_line|#define MSC_Ceil1stRdAcc(Tcpu)  &t;/*  Ceil. of 1stRdAcc [3..65 Tcpu] */ &bslash;&n;                &t;((((Tcpu) - 2)/2) &lt;&lt; FShft (MSC_RDF))
DECL|macro|MSC_RdAcc
mdefine_line|#define MSC_RdAcc(Tcpu)&t;        &t;/*  Read Access time (non-burst    */ &bslash;&n;                &t;        &t;/*  static memory) [2..64 Tcpu]    */ &bslash;&n;                &t;((((Tcpu) - 2)/2) &lt;&lt; FShft (MSC_RDF))
DECL|macro|MSC_CeilRdAcc
mdefine_line|#define MSC_CeilRdAcc(Tcpu)     &t;/*  Ceil. of RdAcc [2..64 Tcpu]    */ &bslash;&n;                &t;((((Tcpu) - 1)/2) &lt;&lt; FShft (MSC_RDF))
DECL|macro|MSC_RDN
mdefine_line|#define MSC_RDN &t;Fld (5, 8)&t;/* ROM/static memory read Delay    */
multiline_comment|/* Next access - 1 [Tmem]          */
DECL|macro|MSC_NxtRdAcc
mdefine_line|#define MSC_NxtRdAcc(Tcpu)      &t;/*  Next Read Access time (burst   */ &bslash;&n;                &t;        &t;/*  static memory) [2..64 Tcpu]    */ &bslash;&n;                &t;((((Tcpu) - 2)/2) &lt;&lt; FShft (MSC_RDN))
DECL|macro|MSC_CeilNxtRdAcc
mdefine_line|#define MSC_CeilNxtRdAcc(Tcpu)  &t;/*  Ceil. of NxtRdAcc [2..64 Tcpu] */ &bslash;&n;                &t;((((Tcpu) - 1)/2) &lt;&lt; FShft (MSC_RDN))
DECL|macro|MSC_WrAcc
mdefine_line|#define MSC_WrAcc(Tcpu)&t;        &t;/*  Write Access time (non-burst   */ &bslash;&n;                &t;        &t;/*  static memory) [2..64 Tcpu]    */ &bslash;&n;                &t;((((Tcpu) - 2)/2) &lt;&lt; FShft (MSC_RDN))
DECL|macro|MSC_CeilWrAcc
mdefine_line|#define MSC_CeilWrAcc(Tcpu)     &t;/*  Ceil. of WrAcc [2..64 Tcpu]    */ &bslash;&n;                &t;((((Tcpu) - 1)/2) &lt;&lt; FShft (MSC_RDN))
DECL|macro|MSC_RRR
mdefine_line|#define MSC_RRR &t;Fld (3, 13)&t;/* ROM/static memory RecoveRy      */
multiline_comment|/* time/2 [Tmem]                   */
DECL|macro|MSC_Rec
mdefine_line|#define MSC_Rec(Tcpu)&t;        &t;/*  Recovery time [0..28 Tcpu]     */ &bslash;&n;                &t;(((Tcpu)/4) &lt;&lt; FShft (MSC_RRR))
DECL|macro|MSC_CeilRec
mdefine_line|#define MSC_CeilRec(Tcpu)       &t;/*  Ceil. of Rec [0..28 Tcpu]      */ &bslash;&n;                &t;((((Tcpu) + 3)/4) &lt;&lt; FShft (MSC_RRR))
multiline_comment|/*&n; * Personal Computer Memory Card International Association (PCMCIA) control&n; * register&n; *&n; * Register&n; *    MECR      &t;Memory system: Expansion memory bus (PCMCIA)&n; *              &t;Configuration Register (read/write).&n; *&n; * Clocks&n; *    fcpu, Tcpu&t;Frequency, period of the CPU core clock (CCLK).&n; *    fmem, Tmem&t;Frequency, period of the memory clock (fmem = fcpu/2).&n; *    fbclk, Tbclk&t;Frequency, period of the PCMCIA clock (BCLK).&n; */
multiline_comment|/* Memory system:                  */
DECL|macro|_MECR
mdefine_line|#define _MECR   &t;0xA0000018&t;/*  Expansion memory bus (PCMCIA)  */
multiline_comment|/*  Configuration Reg.             */
macro_line|#if LANGUAGE == C
multiline_comment|/* Memory system:                  */
DECL|macro|MECR
mdefine_line|#define MECR    &t;        &t;/*  Expansion memory bus (PCMCIA)  */ &bslash;&n;                &t;        &t;/*  Configuration Reg.             */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_MECR)))
macro_line|#endif /* LANGUAGE == C */
DECL|macro|MECR_PCMCIA
mdefine_line|#define MECR_PCMCIA(Nb)&t;        &t;/* PCMCIA [0..1]                   */ &bslash;&n;                &t;Fld (15, (Nb)*16)
DECL|macro|MECR_PCMCIA0
mdefine_line|#define MECR_PCMCIA0&t;MECR_PCMCIA (0)&t;/* PCMCIA 0                        */
DECL|macro|MECR_PCMCIA1
mdefine_line|#define MECR_PCMCIA1&t;MECR_PCMCIA (1)&t;/* PCMCIA 1                        */
DECL|macro|MECR_BSIO
mdefine_line|#define MECR_BSIO&t;Fld (5, 0)&t;/* BCLK Select I/O - 1 [Tmem]      */
DECL|macro|MECR_IOClk
mdefine_line|#define MECR_IOClk(Tcpu)        &t;/*  I/O Clock [2..64 Tcpu]         */ &bslash;&n;                &t;((((Tcpu) - 2)/2) &lt;&lt; FShft (MECR_BSIO))
DECL|macro|MECR_CeilIOClk
mdefine_line|#define MECR_CeilIOClk(Tcpu)    &t;/*  Ceil. of IOClk [2..64 Tcpu]    */ &bslash;&n;                &t;((((Tcpu) - 1)/2) &lt;&lt; FShft (MECR_BSIO))
DECL|macro|MECR_BSA
mdefine_line|#define MECR_BSA&t;Fld (5, 5)&t;/* BCLK Select Attribute - 1       */
multiline_comment|/* [Tmem]                          */
DECL|macro|MECR_AttrClk
mdefine_line|#define MECR_AttrClk(Tcpu)      &t;/*  Attribute Clock [2..64 Tcpu]   */ &bslash;&n;                &t;((((Tcpu) - 2)/2) &lt;&lt; FShft (MECR_BSA))
DECL|macro|MECR_CeilAttrClk
mdefine_line|#define MECR_CeilAttrClk(Tcpu)  &t;/*  Ceil. of AttrClk [2..64 Tcpu]  */ &bslash;&n;                &t;((((Tcpu) - 1)/2) &lt;&lt; FShft (MECR_BSA))
DECL|macro|MECR_BSM
mdefine_line|#define MECR_BSM&t;Fld (5, 10)&t;/* BCLK Select Memory - 1 [Tmem]   */
DECL|macro|MECR_MemClk
mdefine_line|#define MECR_MemClk(Tcpu)       &t;/*  Memory Clock [2..64 Tcpu]      */ &bslash;&n;                &t;((((Tcpu) - 2)/2) &lt;&lt; FShft (MECR_BSM))
DECL|macro|MECR_CeilMemClk
mdefine_line|#define MECR_CeilMemClk(Tcpu)   &t;/*  Ceil. of MemClk [2..64 Tcpu]   */ &bslash;&n;                &t;((((Tcpu) - 1)/2) &lt;&lt; FShft (MECR_BSM))
multiline_comment|/*&n; * On SA1110 only&n; */
DECL|macro|_MDREFR
mdefine_line|#define _MDREFR&t;&t;0xA000001C
macro_line|#if LANGUAGE == C
multiline_comment|/* Memory system:                  */
DECL|macro|MDREFR
mdefine_line|#define MDREFR &bslash;&n;                &t;(*((volatile Word *) io_p2v (_MDREFR)))
macro_line|#elif LANGUAGE == Assembly
DECL|macro|MDREFR
mdefine_line|#define MDREFR&t;&t;(io_p2v(_MDREFR))
macro_line|#endif /* LANGUAGE == C */
DECL|macro|MDREFR_TRASR
mdefine_line|#define MDREFR_TRASR&t;&t;Fld (4, 0)
DECL|macro|MDREFR_DRI
mdefine_line|#define MDREFR_DRI&t;&t;Fld (12, 4)
DECL|macro|MDREFR_E0PIN
mdefine_line|#define MDREFR_E0PIN&t;&t;(1 &lt;&lt; 16)
DECL|macro|MDREFR_K0RUN
mdefine_line|#define MDREFR_K0RUN&t;&t;(1 &lt;&lt; 17)
DECL|macro|MDREFR_K0DB2
mdefine_line|#define MDREFR_K0DB2&t;&t;(1 &lt;&lt; 18)
DECL|macro|MDREFR_E1PIN
mdefine_line|#define MDREFR_E1PIN&t;&t;(1 &lt;&lt; 20)
DECL|macro|MDREFR_K1RUN
mdefine_line|#define MDREFR_K1RUN&t;&t;(1 &lt;&lt; 21)
DECL|macro|MDREFR_K1DB2
mdefine_line|#define MDREFR_K1DB2&t;&t;(1 &lt;&lt; 22)
DECL|macro|MDREFR_K2RUN
mdefine_line|#define MDREFR_K2RUN&t;&t;(1 &lt;&lt; 25)
DECL|macro|MDREFR_K2DB2
mdefine_line|#define MDREFR_K2DB2&t;&t;(1 &lt;&lt; 26)
DECL|macro|MDREFR_EAPD
mdefine_line|#define MDREFR_EAPD&t;&t;(1 &lt;&lt; 28)
DECL|macro|MDREFR_KAPD
mdefine_line|#define MDREFR_KAPD&t;&t;(1 &lt;&lt; 29)
DECL|macro|MDREFR_SLFRSH
mdefine_line|#define MDREFR_SLFRSH&t;&t;(1 &lt;&lt; 31)
multiline_comment|/*&n; * Direct Memory Access (DMA) control registers&n; *&n; * Registers&n; *    DDAR0     &t;Direct Memory Access (DMA) Device Address Register&n; *              &t;channel 0 (read/write).&n; *    DCSR0     &t;Direct Memory Access (DMA) Control and Status&n; *              &t;Register channel 0 (read/write).&n; *    DBSA0     &t;Direct Memory Access (DMA) Buffer Start address&n; *              &t;register A channel 0 (read/write).&n; *    DBTA0     &t;Direct Memory Access (DMA) Buffer Transfer count&n; *              &t;register A channel 0 (read/write).&n; *    DBSB0     &t;Direct Memory Access (DMA) Buffer Start address&n; *              &t;register B channel 0 (read/write).&n; *    DBTB0     &t;Direct Memory Access (DMA) Buffer Transfer count&n; *              &t;register B channel 0 (read/write).&n; *&n; *    DDAR1     &t;Direct Memory Access (DMA) Device Address Register&n; *              &t;channel 1 (read/write).&n; *    DCSR1     &t;Direct Memory Access (DMA) Control and Status&n; *              &t;Register channel 1 (read/write).&n; *    DBSA1     &t;Direct Memory Access (DMA) Buffer Start address&n; *              &t;register A channel 1 (read/write).&n; *    DBTA1     &t;Direct Memory Access (DMA) Buffer Transfer count&n; *              &t;register A channel 1 (read/write).&n; *    DBSB1     &t;Direct Memory Access (DMA) Buffer Start address&n; *              &t;register B channel 1 (read/write).&n; *    DBTB1     &t;Direct Memory Access (DMA) Buffer Transfer count&n; *              &t;register B channel 1 (read/write).&n; *&n; *    DDAR2     &t;Direct Memory Access (DMA) Device Address Register&n; *              &t;channel 2 (read/write).&n; *    DCSR2     &t;Direct Memory Access (DMA) Control and Status&n; *              &t;Register channel 2 (read/write).&n; *    DBSA2     &t;Direct Memory Access (DMA) Buffer Start address&n; *              &t;register A channel 2 (read/write).&n; *    DBTA2     &t;Direct Memory Access (DMA) Buffer Transfer count&n; *              &t;register A channel 2 (read/write).&n; *    DBSB2     &t;Direct Memory Access (DMA) Buffer Start address&n; *              &t;register B channel 2 (read/write).&n; *    DBTB2     &t;Direct Memory Access (DMA) Buffer Transfer count&n; *              &t;register B channel 2 (read/write).&n; *&n; *    DDAR3     &t;Direct Memory Access (DMA) Device Address Register&n; *              &t;channel 3 (read/write).&n; *    DCSR3     &t;Direct Memory Access (DMA) Control and Status&n; *              &t;Register channel 3 (read/write).&n; *    DBSA3     &t;Direct Memory Access (DMA) Buffer Start address&n; *              &t;register A channel 3 (read/write).&n; *    DBTA3     &t;Direct Memory Access (DMA) Buffer Transfer count&n; *              &t;register A channel 3 (read/write).&n; *    DBSB3     &t;Direct Memory Access (DMA) Buffer Start address&n; *              &t;register B channel 3 (read/write).&n; *    DBTB3     &t;Direct Memory Access (DMA) Buffer Transfer count&n; *              &t;register B channel 3 (read/write).&n; *&n; *    DDAR4     &t;Direct Memory Access (DMA) Device Address Register&n; *              &t;channel 4 (read/write).&n; *    DCSR4     &t;Direct Memory Access (DMA) Control and Status&n; *              &t;Register channel 4 (read/write).&n; *    DBSA4     &t;Direct Memory Access (DMA) Buffer Start address&n; *              &t;register A channel 4 (read/write).&n; *    DBTA4     &t;Direct Memory Access (DMA) Buffer Transfer count&n; *              &t;register A channel 4 (read/write).&n; *    DBSB4     &t;Direct Memory Access (DMA) Buffer Start address&n; *              &t;register B channel 4 (read/write).&n; *    DBTB4     &t;Direct Memory Access (DMA) Buffer Transfer count&n; *              &t;register B channel 4 (read/write).&n; *&n; *    DDAR5     &t;Direct Memory Access (DMA) Device Address Register&n; *              &t;channel 5 (read/write).&n; *    DCSR5     &t;Direct Memory Access (DMA) Control and Status&n; *              &t;Register channel 5 (read/write).&n; *    DBSA5     &t;Direct Memory Access (DMA) Buffer Start address&n; *              &t;register A channel 5 (read/write).&n; *    DBTA5     &t;Direct Memory Access (DMA) Buffer Transfer count&n; *              &t;register A channel 5 (read/write).&n; *    DBSB5     &t;Direct Memory Access (DMA) Buffer Start address&n; *              &t;register B channel 5 (read/write).&n; *    DBTB5     &t;Direct Memory Access (DMA) Buffer Transfer count&n; *              &t;register B channel 5 (read/write).&n; */
DECL|macro|DMASp
mdefine_line|#define DMASp   &t;0x00000020&t;/* DMA control reg. Space [byte]   */
DECL|macro|_DDAR
mdefine_line|#define _DDAR(Nb)&t;        &t;/* DMA Device Address Reg.         */ &bslash;&n;                &t;        &t;/* channel [0..5]                  */ &bslash;&n;                &t;(0xB0000000 + (Nb)*DMASp)
DECL|macro|_SetDCSR
mdefine_line|#define _SetDCSR(Nb)&t;        &t;/* Set DMA Control &amp; Status Reg.   */ &bslash;&n;                &t;        &t;/* channel [0..5] (write)          */ &bslash;&n;                &t;(0xB0000004 + (Nb)*DMASp)
DECL|macro|_ClrDCSR
mdefine_line|#define _ClrDCSR(Nb)&t;        &t;/* Clear DMA Control &amp; Status Reg. */ &bslash;&n;                &t;        &t;/* channel [0..5] (write)          */ &bslash;&n;                &t;(0xB0000008 + (Nb)*DMASp)
DECL|macro|_RdDCSR
mdefine_line|#define _RdDCSR(Nb)&t;        &t;/* Read DMA Control &amp; Status Reg.  */ &bslash;&n;                &t;        &t;/* channel [0..5] (read)           */ &bslash;&n;                &t;(0xB000000C + (Nb)*DMASp)
DECL|macro|_DBSA
mdefine_line|#define _DBSA(Nb)&t;        &t;/* DMA Buffer Start address reg. A */ &bslash;&n;                &t;        &t;/* channel [0..5]                  */ &bslash;&n;                &t;(0xB0000010 + (Nb)*DMASp)
DECL|macro|_DBTA
mdefine_line|#define _DBTA(Nb)&t;        &t;/* DMA Buffer Transfer count       */ &bslash;&n;                &t;        &t;/* reg. A channel [0..5]           */ &bslash;&n;                &t;(0xB0000014 + (Nb)*DMASp)
DECL|macro|_DBSB
mdefine_line|#define _DBSB(Nb)&t;        &t;/* DMA Buffer Start address reg. B */ &bslash;&n;                &t;        &t;/* channel [0..5]                  */ &bslash;&n;                &t;(0xB0000018 + (Nb)*DMASp)
DECL|macro|_DBTB
mdefine_line|#define _DBTB(Nb)&t;        &t;/* DMA Buffer Transfer count       */ &bslash;&n;                &t;        &t;/* reg. B channel [0..5]           */ &bslash;&n;                &t;(0xB000001C + (Nb)*DMASp)
DECL|macro|_DDAR0
mdefine_line|#define _DDAR0  &t;_DDAR (0)&t;/* DMA Device Address Reg.         */
multiline_comment|/* channel 0                       */
DECL|macro|_SetDCSR0
mdefine_line|#define _SetDCSR0&t;_SetDCSR (0)&t;/* Set DMA Control &amp; Status Reg.   */
multiline_comment|/* channel 0 (write)               */
DECL|macro|_ClrDCSR0
mdefine_line|#define _ClrDCSR0&t;_ClrDCSR (0)&t;/* Clear DMA Control &amp; Status Reg. */
multiline_comment|/* channel 0 (write)               */
DECL|macro|_RdDCSR0
mdefine_line|#define _RdDCSR0&t;_RdDCSR (0)&t;/* Read DMA Control &amp; Status Reg.  */
multiline_comment|/* channel 0 (read)                */
DECL|macro|_DBSA0
mdefine_line|#define _DBSA0  &t;_DBSA (0)&t;/* DMA Buffer Start address reg. A */
multiline_comment|/* channel 0                       */
DECL|macro|_DBTA0
mdefine_line|#define _DBTA0  &t;_DBTA (0)&t;/* DMA Buffer Transfer count       */
multiline_comment|/* reg. A channel 0                */
DECL|macro|_DBSB0
mdefine_line|#define _DBSB0  &t;_DBSB (0)&t;/* DMA Buffer Start address reg. B */
multiline_comment|/* channel 0                       */
DECL|macro|_DBTB0
mdefine_line|#define _DBTB0  &t;_DBTB (0)&t;/* DMA Buffer Transfer count       */
multiline_comment|/* reg. B channel 0                */
DECL|macro|_DDAR1
mdefine_line|#define _DDAR1  &t;_DDAR (1)&t;/* DMA Device Address Reg.         */
multiline_comment|/* channel 1                       */
DECL|macro|_SetDCSR1
mdefine_line|#define _SetDCSR1&t;_SetDCSR (1)&t;/* Set DMA Control &amp; Status Reg.   */
multiline_comment|/* channel 1 (write)               */
DECL|macro|_ClrDCSR1
mdefine_line|#define _ClrDCSR1&t;_ClrDCSR (1)&t;/* Clear DMA Control &amp; Status Reg. */
multiline_comment|/* channel 1 (write)               */
DECL|macro|_RdDCSR1
mdefine_line|#define _RdDCSR1&t;_RdDCSR (1)&t;/* Read DMA Control &amp; Status Reg.  */
multiline_comment|/* channel 1 (read)                */
DECL|macro|_DBSA1
mdefine_line|#define _DBSA1  &t;_DBSA (1)&t;/* DMA Buffer Start address reg. A */
multiline_comment|/* channel 1                       */
DECL|macro|_DBTA1
mdefine_line|#define _DBTA1  &t;_DBTA (1)&t;/* DMA Buffer Transfer count       */
multiline_comment|/* reg. A channel 1                */
DECL|macro|_DBSB1
mdefine_line|#define _DBSB1  &t;_DBSB (1)&t;/* DMA Buffer Start address reg. B */
multiline_comment|/* channel 1                       */
DECL|macro|_DBTB1
mdefine_line|#define _DBTB1  &t;_DBTB (1)&t;/* DMA Buffer Transfer count       */
multiline_comment|/* reg. B channel 1                */
DECL|macro|_DDAR2
mdefine_line|#define _DDAR2  &t;_DDAR (2)&t;/* DMA Device Address Reg.         */
multiline_comment|/* channel 2                       */
DECL|macro|_SetDCSR2
mdefine_line|#define _SetDCSR2&t;_SetDCSR (2)&t;/* Set DMA Control &amp; Status Reg.   */
multiline_comment|/* channel 2 (write)               */
DECL|macro|_ClrDCSR2
mdefine_line|#define _ClrDCSR2&t;_ClrDCSR (2)&t;/* Clear DMA Control &amp; Status Reg. */
multiline_comment|/* channel 2 (write)               */
DECL|macro|_RdDCSR2
mdefine_line|#define _RdDCSR2&t;_RdDCSR (2)&t;/* Read DMA Control &amp; Status Reg.  */
multiline_comment|/* channel 2 (read)                */
DECL|macro|_DBSA2
mdefine_line|#define _DBSA2  &t;_DBSA (2)&t;/* DMA Buffer Start address reg. A */
multiline_comment|/* channel 2                       */
DECL|macro|_DBTA2
mdefine_line|#define _DBTA2  &t;_DBTA (2)&t;/* DMA Buffer Transfer count       */
multiline_comment|/* reg. A channel 2                */
DECL|macro|_DBSB2
mdefine_line|#define _DBSB2  &t;_DBSB (2)&t;/* DMA Buffer Start address reg. B */
multiline_comment|/* channel 2                       */
DECL|macro|_DBTB2
mdefine_line|#define _DBTB2  &t;_DBTB (2)&t;/* DMA Buffer Transfer count       */
multiline_comment|/* reg. B channel 2                */
DECL|macro|_DDAR3
mdefine_line|#define _DDAR3  &t;_DDAR (3)&t;/* DMA Device Address Reg.         */
multiline_comment|/* channel 3                       */
DECL|macro|_SetDCSR3
mdefine_line|#define _SetDCSR3&t;_SetDCSR (3)&t;/* Set DMA Control &amp; Status Reg.   */
multiline_comment|/* channel 3 (write)               */
DECL|macro|_ClrDCSR3
mdefine_line|#define _ClrDCSR3&t;_ClrDCSR (3)&t;/* Clear DMA Control &amp; Status Reg. */
multiline_comment|/* channel 3 (write)               */
DECL|macro|_RdDCSR3
mdefine_line|#define _RdDCSR3&t;_RdDCSR (3)&t;/* Read DMA Control &amp; Status Reg.  */
multiline_comment|/* channel 3 (read)                */
DECL|macro|_DBSA3
mdefine_line|#define _DBSA3  &t;_DBSA (3)&t;/* DMA Buffer Start address reg. A */
multiline_comment|/* channel 3                       */
DECL|macro|_DBTA3
mdefine_line|#define _DBTA3  &t;_DBTA (3)&t;/* DMA Buffer Transfer count       */
multiline_comment|/* reg. A channel 3                */
DECL|macro|_DBSB3
mdefine_line|#define _DBSB3  &t;_DBSB (3)&t;/* DMA Buffer Start address reg. B */
multiline_comment|/* channel 3                       */
DECL|macro|_DBTB3
mdefine_line|#define _DBTB3  &t;_DBTB (3)&t;/* DMA Buffer Transfer count       */
multiline_comment|/* reg. B channel 3                */
DECL|macro|_DDAR4
mdefine_line|#define _DDAR4  &t;_DDAR (4)&t;/* DMA Device Address Reg.         */
multiline_comment|/* channel 4                       */
DECL|macro|_SetDCSR4
mdefine_line|#define _SetDCSR4&t;_SetDCSR (4)&t;/* Set DMA Control &amp; Status Reg.   */
multiline_comment|/* channel 4 (write)               */
DECL|macro|_ClrDCSR4
mdefine_line|#define _ClrDCSR4&t;_ClrDCSR (4)&t;/* Clear DMA Control &amp; Status Reg. */
multiline_comment|/* channel 4 (write)               */
DECL|macro|_RdDCSR4
mdefine_line|#define _RdDCSR4&t;_RdDCSR (4)&t;/* Read DMA Control &amp; Status Reg.  */
multiline_comment|/* channel 4 (read)                */
DECL|macro|_DBSA4
mdefine_line|#define _DBSA4  &t;_DBSA (4)&t;/* DMA Buffer Start address reg. A */
multiline_comment|/* channel 4                       */
DECL|macro|_DBTA4
mdefine_line|#define _DBTA4  &t;_DBTA (4)&t;/* DMA Buffer Transfer count       */
multiline_comment|/* reg. A channel 4                */
DECL|macro|_DBSB4
mdefine_line|#define _DBSB4  &t;_DBSB (4)&t;/* DMA Buffer Start address reg. B */
multiline_comment|/* channel 4                       */
DECL|macro|_DBTB4
mdefine_line|#define _DBTB4  &t;_DBTB (4)&t;/* DMA Buffer Transfer count       */
multiline_comment|/* reg. B channel 4                */
DECL|macro|_DDAR5
mdefine_line|#define _DDAR5  &t;_DDAR (5)&t;/* DMA Device Address Reg.         */
multiline_comment|/* channel 5                       */
DECL|macro|_SetDCSR5
mdefine_line|#define _SetDCSR5&t;_SetDCSR (5)&t;/* Set DMA Control &amp; Status Reg.   */
multiline_comment|/* channel 5 (write)               */
DECL|macro|_ClrDCSR5
mdefine_line|#define _ClrDCSR5&t;_ClrDCSR (5)&t;/* Clear DMA Control &amp; Status Reg. */
multiline_comment|/* channel 5 (write)               */
DECL|macro|_RdDCSR5
mdefine_line|#define _RdDCSR5&t;_RdDCSR (5)&t;/* Read DMA Control &amp; Status Reg.  */
multiline_comment|/* channel 5 (read)                */
DECL|macro|_DBSA5
mdefine_line|#define _DBSA5  &t;_DBSA (5)&t;/* DMA Buffer Start address reg. A */
multiline_comment|/* channel 5                       */
DECL|macro|_DBTA5
mdefine_line|#define _DBTA5  &t;_DBTA (5)&t;/* DMA Buffer Transfer count       */
multiline_comment|/* reg. A channel 5                */
DECL|macro|_DBSB5
mdefine_line|#define _DBSB5  &t;_DBSB (5)&t;/* DMA Buffer Start address reg. B */
multiline_comment|/* channel 5                       */
DECL|macro|_DBTB5
mdefine_line|#define _DBTB5  &t;_DBTB (5)&t;/* DMA Buffer Transfer count       */
multiline_comment|/* reg. B channel 5                */
macro_line|#if LANGUAGE == C
DECL|macro|DDAR0
mdefine_line|#define DDAR0   &t;        &t;/* DMA Device Address Reg.         */ &bslash;&n;                &t;        &t;/* channel 0                       */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_DDAR0)))
DECL|macro|SetDCSR0
mdefine_line|#define SetDCSR0&t;        &t;/* Set DMA Control &amp; Status Reg.   */ &bslash;&n;                &t;        &t;/* channel 0 (write)               */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_SetDCSR0)))
DECL|macro|ClrDCSR0
mdefine_line|#define ClrDCSR0&t;        &t;/* Clear DMA Control &amp; Status Reg. */ &bslash;&n;                &t;        &t;/* channel 0 (write)               */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_ClrDCSR0)))
DECL|macro|RdDCSR0
mdefine_line|#define RdDCSR0 &t;        &t;/* Read DMA Control &amp; Status Reg.  */ &bslash;&n;                &t;        &t;/* channel 0 (read)                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_RdDCSR0)))
DECL|macro|DBSA0
mdefine_line|#define DBSA0   &t;        &t;/* DMA Buffer Start address reg. A */ &bslash;&n;                &t;        &t;/* channel 0                       */ &bslash;&n;                &t;(*((volatile Address *) io_p2v (_DBSA0)))
DECL|macro|DBTA0
mdefine_line|#define DBTA0   &t;        &t;/* DMA Buffer Transfer count       */ &bslash;&n;                &t;        &t;/* reg. A channel 0                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_DBTA0)))
DECL|macro|DBSB0
mdefine_line|#define DBSB0   &t;        &t;/* DMA Buffer Start address reg. B */ &bslash;&n;                &t;        &t;/* channel 0                       */ &bslash;&n;                &t;(*((volatile Address *) io_p2v (_DBSB0)))
DECL|macro|DBTB0
mdefine_line|#define DBTB0   &t;        &t;/* DMA Buffer Transfer count       */ &bslash;&n;                &t;        &t;/* reg. B channel 0                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_DBTB0)))
DECL|macro|DDAR1
mdefine_line|#define DDAR1   &t;        &t;/* DMA Device Address Reg.         */ &bslash;&n;                &t;        &t;/* channel 1                       */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_DDAR1)))
DECL|macro|SetDCSR1
mdefine_line|#define SetDCSR1&t;        &t;/* Set DMA Control &amp; Status Reg.   */ &bslash;&n;                &t;        &t;/* channel 1 (write)               */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_SetDCSR1)))
DECL|macro|ClrDCSR1
mdefine_line|#define ClrDCSR1&t;        &t;/* Clear DMA Control &amp; Status Reg. */ &bslash;&n;                &t;        &t;/* channel 1 (write)               */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_ClrDCSR1)))
DECL|macro|RdDCSR1
mdefine_line|#define RdDCSR1 &t;        &t;/* Read DMA Control &amp; Status Reg.  */ &bslash;&n;                &t;        &t;/* channel 1 (read)                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_RdDCSR1)))
DECL|macro|DBSA1
mdefine_line|#define DBSA1   &t;        &t;/* DMA Buffer Start address reg. A */ &bslash;&n;                &t;        &t;/* channel 1                       */ &bslash;&n;                &t;(*((volatile Address *) io_p2v (_DBSA1)))
DECL|macro|DBTA1
mdefine_line|#define DBTA1   &t;        &t;/* DMA Buffer Transfer count       */ &bslash;&n;                &t;        &t;/* reg. A channel 1                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_DBTA1)))
DECL|macro|DBSB1
mdefine_line|#define DBSB1   &t;        &t;/* DMA Buffer Start address reg. B */ &bslash;&n;                &t;        &t;/* channel 1                       */ &bslash;&n;                &t;(*((volatile Address *) io_p2v (_DBSB1)))
DECL|macro|DBTB1
mdefine_line|#define DBTB1   &t;        &t;/* DMA Buffer Transfer count       */ &bslash;&n;                &t;        &t;/* reg. B channel 1                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_DBTB1)))
DECL|macro|DDAR2
mdefine_line|#define DDAR2   &t;        &t;/* DMA Device Address Reg.         */ &bslash;&n;                &t;        &t;/* channel 2                       */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_DDAR2)))
DECL|macro|SetDCSR2
mdefine_line|#define SetDCSR2&t;        &t;/* Set DMA Control &amp; Status Reg.   */ &bslash;&n;                &t;        &t;/* channel 2 (write)               */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_SetDCSR2)))
DECL|macro|ClrDCSR2
mdefine_line|#define ClrDCSR2&t;        &t;/* Clear DMA Control &amp; Status Reg. */ &bslash;&n;                &t;        &t;/* channel 2 (write)               */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_ClrDCSR2)))
DECL|macro|RdDCSR2
mdefine_line|#define RdDCSR2 &t;        &t;/* Read DMA Control &amp; Status Reg.  */ &bslash;&n;                &t;        &t;/* channel 2 (read)                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_RdDCSR2)))
DECL|macro|DBSA2
mdefine_line|#define DBSA2   &t;        &t;/* DMA Buffer Start address reg. A */ &bslash;&n;                &t;        &t;/* channel 2                       */ &bslash;&n;                &t;(*((volatile Address *) io_p2v (_DBSA2)))
DECL|macro|DBTA2
mdefine_line|#define DBTA2   &t;        &t;/* DMA Buffer Transfer count       */ &bslash;&n;                &t;        &t;/* reg. A channel 2                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_DBTA2)))
DECL|macro|DBSB2
mdefine_line|#define DBSB2   &t;        &t;/* DMA Buffer Start address reg. B */ &bslash;&n;                &t;        &t;/* channel 2                       */ &bslash;&n;                &t;(*((volatile Address *) io_p2v (_DBSB2)))
DECL|macro|DBTB2
mdefine_line|#define DBTB2   &t;        &t;/* DMA Buffer Transfer count       */ &bslash;&n;                &t;        &t;/* reg. B channel 2                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_DBTB2)))
DECL|macro|DDAR3
mdefine_line|#define DDAR3   &t;        &t;/* DMA Device Address Reg.         */ &bslash;&n;                &t;        &t;/* channel 3                       */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_DDAR3)))
DECL|macro|SetDCSR3
mdefine_line|#define SetDCSR3&t;        &t;/* Set DMA Control &amp; Status Reg.   */ &bslash;&n;                &t;        &t;/* channel 3 (write)               */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_SetDCSR3)))
DECL|macro|ClrDCSR3
mdefine_line|#define ClrDCSR3&t;        &t;/* Clear DMA Control &amp; Status Reg. */ &bslash;&n;                &t;        &t;/* channel 3 (write)               */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_ClrDCSR3)))
DECL|macro|RdDCSR3
mdefine_line|#define RdDCSR3 &t;        &t;/* Read DMA Control &amp; Status Reg.  */ &bslash;&n;                &t;        &t;/* channel 3 (read)                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_RdDCSR3)))
DECL|macro|DBSA3
mdefine_line|#define DBSA3   &t;        &t;/* DMA Buffer Start address reg. A */ &bslash;&n;                &t;        &t;/* channel 3                       */ &bslash;&n;                &t;(*((volatile Address *) io_p2v (_DBSA3)))
DECL|macro|DBTA3
mdefine_line|#define DBTA3   &t;        &t;/* DMA Buffer Transfer count       */ &bslash;&n;                &t;        &t;/* reg. A channel 3                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_DBTA3)))
DECL|macro|DBSB3
mdefine_line|#define DBSB3   &t;        &t;/* DMA Buffer Start address reg. B */ &bslash;&n;                &t;        &t;/* channel 3                       */ &bslash;&n;                &t;(*((volatile Address *) io_p2v (_DBSB3)))
DECL|macro|DBTB3
mdefine_line|#define DBTB3   &t;        &t;/* DMA Buffer Transfer count       */ &bslash;&n;                &t;        &t;/* reg. B channel 3                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_DBTB3)))
DECL|macro|DDAR4
mdefine_line|#define DDAR4   &t;        &t;/* DMA Device Address Reg.         */ &bslash;&n;                &t;        &t;/* channel 4                       */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_DDAR4)))
DECL|macro|SetDCSR4
mdefine_line|#define SetDCSR4&t;        &t;/* Set DMA Control &amp; Status Reg.   */ &bslash;&n;                &t;        &t;/* channel 4 (write)               */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_SetDCSR4)))
DECL|macro|ClrDCSR4
mdefine_line|#define ClrDCSR4&t;        &t;/* Clear DMA Control &amp; Status Reg. */ &bslash;&n;                &t;        &t;/* channel 4 (write)               */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_ClrDCSR4)))
DECL|macro|RdDCSR4
mdefine_line|#define RdDCSR4 &t;        &t;/* Read DMA Control &amp; Status Reg.  */ &bslash;&n;                &t;        &t;/* channel 4 (read)                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_RdDCSR4)))
DECL|macro|DBSA4
mdefine_line|#define DBSA4   &t;        &t;/* DMA Buffer Start address reg. A */ &bslash;&n;                &t;        &t;/* channel 4                       */ &bslash;&n;                &t;(*((volatile Address *) io_p2v (_DBSA4)))
DECL|macro|DBTA4
mdefine_line|#define DBTA4   &t;        &t;/* DMA Buffer Transfer count       */ &bslash;&n;                &t;        &t;/* reg. A channel 4                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_DBTA4)))
DECL|macro|DBSB4
mdefine_line|#define DBSB4   &t;        &t;/* DMA Buffer Start address reg. B */ &bslash;&n;                &t;        &t;/* channel 4                       */ &bslash;&n;                &t;(*((volatile Address *) io_p2v (_DBSB4)))
DECL|macro|DBTB4
mdefine_line|#define DBTB4   &t;        &t;/* DMA Buffer Transfer count       */ &bslash;&n;                &t;        &t;/* reg. B channel 4                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_DBTB4)))
DECL|macro|DDAR5
mdefine_line|#define DDAR5   &t;        &t;/* DMA Device Address Reg.         */ &bslash;&n;                &t;        &t;/* channel 5                       */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_DDAR5)))
DECL|macro|SetDCSR5
mdefine_line|#define SetDCSR5&t;        &t;/* Set DMA Control &amp; Status Reg.   */ &bslash;&n;                &t;        &t;/* channel 5 (write)               */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_SetDCSR5)))
DECL|macro|ClrDCSR5
mdefine_line|#define ClrDCSR5&t;        &t;/* Clear DMA Control &amp; Status Reg. */ &bslash;&n;                &t;        &t;/* channel 5 (write)               */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_ClrDCSR5)))
DECL|macro|RdDCSR5
mdefine_line|#define RdDCSR5 &t;        &t;/* Read DMA Control &amp; Status Reg.  */ &bslash;&n;                &t;        &t;/* channel 5 (read)                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_RdDCSR5)))
DECL|macro|DBSA5
mdefine_line|#define DBSA5   &t;        &t;/* DMA Buffer Start address reg. A */ &bslash;&n;                &t;        &t;/* channel 5                       */ &bslash;&n;                &t;(*((volatile Address *) io_p2v (_DBSA5)))
DECL|macro|DBTA5
mdefine_line|#define DBTA5   &t;        &t;/* DMA Buffer Transfer count       */ &bslash;&n;                &t;        &t;/* reg. A channel 5                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_DBTA5)))
DECL|macro|DBSB5
mdefine_line|#define DBSB5   &t;        &t;/* DMA Buffer Start address reg. B */ &bslash;&n;                &t;        &t;/* channel 5                       */ &bslash;&n;                &t;(*((volatile Address *) io_p2v (_DBSB5)))
DECL|macro|DBTB5
mdefine_line|#define DBTB5   &t;        &t;/* DMA Buffer Transfer count       */ &bslash;&n;                &t;        &t;/* reg. B channel 5                */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_DBTB5)))
macro_line|#endif /* LANGUAGE == C */
DECL|macro|DDAR_RW
mdefine_line|#define DDAR_RW &t;0x00000001&t;/* device data Read/Write          */
DECL|macro|DDAR_DevWr
mdefine_line|#define DDAR_DevWr&t;(DDAR_RW*0)&t;/*  Device data Write              */
multiline_comment|/*  (memory -&gt; device)             */
DECL|macro|DDAR_DevRd
mdefine_line|#define DDAR_DevRd&t;(DDAR_RW*1)&t;/*  Device data Read               */
multiline_comment|/*  (device -&gt; memory)             */
DECL|macro|DDAR_E
mdefine_line|#define DDAR_E  &t;0x00000002&t;/* big/little Endian device        */
DECL|macro|DDAR_LtlEnd
mdefine_line|#define DDAR_LtlEnd&t;(DDAR_E*0)&t;/*  Little Endian device           */
DECL|macro|DDAR_BigEnd
mdefine_line|#define DDAR_BigEnd&t;(DDAR_E*1)&t;/*  Big Endian device              */
DECL|macro|DDAR_BS
mdefine_line|#define DDAR_BS &t;0x00000004&t;/* device Burst Size               */
DECL|macro|DDAR_Brst4
mdefine_line|#define DDAR_Brst4&t;(DDAR_BS*0)&t;/*  Burst-of-4 device              */
DECL|macro|DDAR_Brst8
mdefine_line|#define DDAR_Brst8&t;(DDAR_BS*1)&t;/*  Burst-of-8 device              */
DECL|macro|DDAR_DW
mdefine_line|#define DDAR_DW &t;0x00000008&t;/* device Data Width               */
DECL|macro|DDAR_8BitDev
mdefine_line|#define DDAR_8BitDev&t;(DDAR_DW*0)&t;/*  8-Bit Device                   */
DECL|macro|DDAR_16BitDev
mdefine_line|#define DDAR_16BitDev&t;(DDAR_DW*1)&t;/*  16-Bit Device                  */
DECL|macro|DDAR_DS
mdefine_line|#define DDAR_DS &t;Fld (4, 4)&t;/* Device Select                   */
DECL|macro|DDAR_Ser0UDCTr
mdefine_line|#define DDAR_Ser0UDCTr&t;        &t;/*  Ser. port 0 UDC Transmit       */ &bslash;&n;                &t;(0x0 &lt;&lt; FShft (DDAR_DS))
DECL|macro|DDAR_Ser0UDCRc
mdefine_line|#define DDAR_Ser0UDCRc&t;        &t;/*  Ser. port 0 UDC Receive        */ &bslash;&n;                &t;(0x1 &lt;&lt; FShft (DDAR_DS))
DECL|macro|DDAR_Ser1SDLCTr
mdefine_line|#define DDAR_Ser1SDLCTr&t;        &t;/*  Ser. port 1 SDLC Transmit      */ &bslash;&n;                &t;(0x2 &lt;&lt; FShft (DDAR_DS))
DECL|macro|DDAR_Ser1SDLCRc
mdefine_line|#define DDAR_Ser1SDLCRc&t;        &t;/*  Ser. port 1 SDLC Receive       */ &bslash;&n;                &t;(0x3 &lt;&lt; FShft (DDAR_DS))
DECL|macro|DDAR_Ser1UARTTr
mdefine_line|#define DDAR_Ser1UARTTr&t;        &t;/*  Ser. port 1 UART Transmit      */ &bslash;&n;                &t;(0x4 &lt;&lt; FShft (DDAR_DS))
DECL|macro|DDAR_Ser1UARTRc
mdefine_line|#define DDAR_Ser1UARTRc&t;        &t;/*  Ser. port 1 UART Receive       */ &bslash;&n;                &t;(0x5 &lt;&lt; FShft (DDAR_DS))
DECL|macro|DDAR_Ser2ICPTr
mdefine_line|#define DDAR_Ser2ICPTr&t;        &t;/*  Ser. port 2 ICP Transmit       */ &bslash;&n;                &t;(0x6 &lt;&lt; FShft (DDAR_DS))
DECL|macro|DDAR_Ser2ICPRc
mdefine_line|#define DDAR_Ser2ICPRc&t;        &t;/*  Ser. port 2 ICP Receive        */ &bslash;&n;                &t;(0x7 &lt;&lt; FShft (DDAR_DS))
DECL|macro|DDAR_Ser3UARTTr
mdefine_line|#define DDAR_Ser3UARTTr&t;        &t;/*  Ser. port 3 UART Transmit      */ &bslash;&n;                &t;(0x8 &lt;&lt; FShft (DDAR_DS))
DECL|macro|DDAR_Ser3UARTRc
mdefine_line|#define DDAR_Ser3UARTRc&t;        &t;/*  Ser. port 3 UART Receive       */ &bslash;&n;                &t;(0x9 &lt;&lt; FShft (DDAR_DS))
DECL|macro|DDAR_Ser4MCP0Tr
mdefine_line|#define DDAR_Ser4MCP0Tr&t;        &t;/*  Ser. port 4 MCP 0 Transmit     */ &bslash;&n;                &t;        &t;/*  (audio)                        */ &bslash;&n;                &t;(0xA &lt;&lt; FShft (DDAR_DS))
DECL|macro|DDAR_Ser4MCP0Rc
mdefine_line|#define DDAR_Ser4MCP0Rc&t;        &t;/*  Ser. port 4 MCP 0 Receive      */ &bslash;&n;                &t;        &t;/*  (audio)                        */ &bslash;&n;                &t;(0xB &lt;&lt; FShft (DDAR_DS))
DECL|macro|DDAR_Ser4MCP1Tr
mdefine_line|#define DDAR_Ser4MCP1Tr&t;        &t;/*  Ser. port 4 MCP 1 Transmit     */ &bslash;&n;                &t;        &t;/*  (telecom)                      */ &bslash;&n;                &t;(0xC &lt;&lt; FShft (DDAR_DS))
DECL|macro|DDAR_Ser4MCP1Rc
mdefine_line|#define DDAR_Ser4MCP1Rc&t;        &t;/*  Ser. port 4 MCP 1 Receive      */ &bslash;&n;                &t;        &t;/*  (telecom)                      */ &bslash;&n;                &t;(0xD &lt;&lt; FShft (DDAR_DS))
DECL|macro|DDAR_Ser4SSPTr
mdefine_line|#define DDAR_Ser4SSPTr&t;        &t;/*  Ser. port 4 SSP Transmit       */ &bslash;&n;                &t;(0xE &lt;&lt; FShft (DDAR_DS))
DECL|macro|DDAR_Ser4SSPRc
mdefine_line|#define DDAR_Ser4SSPRc&t;        &t;/*  Ser. port 4 SSP Receive        */ &bslash;&n;                &t;(0xF &lt;&lt; FShft (DDAR_DS))
DECL|macro|DDAR_DA
mdefine_line|#define DDAR_DA &t;Fld (24, 8)&t;/* Device Address                  */
DECL|macro|DDAR_DevAdd
mdefine_line|#define DDAR_DevAdd(Add)        &t;/*  Device Address                 */ &bslash;&n;                &t;(((Add) &amp; 0xF0000000) | &bslash;&n;                &t; (((Add) &amp; 0X003FFFFC) &lt;&lt; (FShft (DDAR_DA) - 2)))
DECL|macro|DDAR_Ser0UDCWr
mdefine_line|#define DDAR_Ser0UDCWr&t;        &t;/* Ser. port 0 UDC Write           */ &bslash;&n;                &t;(DDAR_DevWr + DDAR_Brst8 + DDAR_8BitDev + &bslash;&n;                &t; DDAR_Ser0UDCTr + DDAR_DevAdd (_Ser0UDCDR))
DECL|macro|DDAR_Ser0UDCRd
mdefine_line|#define DDAR_Ser0UDCRd&t;        &t;/* Ser. port 0 UDC Read            */ &bslash;&n;                &t;(DDAR_DevRd + DDAR_Brst8 + DDAR_8BitDev + &bslash;&n;                &t; DDAR_Ser0UDCRc + DDAR_DevAdd (_Ser0UDCDR))
DECL|macro|DDAR_Ser1UARTWr
mdefine_line|#define DDAR_Ser1UARTWr&t;        &t;/* Ser. port 1 UART Write          */ &bslash;&n;                &t;(DDAR_DevWr + DDAR_Brst4 + DDAR_8BitDev + &bslash;&n;                &t; DDAR_Ser1UARTTr + DDAR_DevAdd (_Ser1UTDR))
DECL|macro|DDAR_Ser1UARTRd
mdefine_line|#define DDAR_Ser1UARTRd&t;        &t;/* Ser. port 1 UART Read           */ &bslash;&n;                &t;(DDAR_DevRd + DDAR_Brst4 + DDAR_8BitDev + &bslash;&n;                &t; DDAR_Ser1UARTRc + DDAR_DevAdd (_Ser1UTDR))
DECL|macro|DDAR_Ser1SDLCWr
mdefine_line|#define DDAR_Ser1SDLCWr&t;        &t;/* Ser. port 1 SDLC Write          */ &bslash;&n;                &t;(DDAR_DevWr + DDAR_Brst4 + DDAR_8BitDev + &bslash;&n;                &t; DDAR_Ser1SDLCTr + DDAR_DevAdd (_Ser1SDDR))
DECL|macro|DDAR_Ser1SDLCRd
mdefine_line|#define DDAR_Ser1SDLCRd&t;        &t;/* Ser. port 1 SDLC Read           */ &bslash;&n;                &t;(DDAR_DevRd + DDAR_Brst4 + DDAR_8BitDev + &bslash;&n;                &t; DDAR_Ser1SDLCRc + DDAR_DevAdd (_Ser1SDDR))
DECL|macro|DDAR_Ser2UARTWr
mdefine_line|#define DDAR_Ser2UARTWr&t;        &t;/* Ser. port 2 UART Write          */ &bslash;&n;                &t;(DDAR_DevWr + DDAR_Brst4 + DDAR_8BitDev + &bslash;&n;                &t; DDAR_Ser2ICPTr + DDAR_DevAdd (_Ser2UTDR))
DECL|macro|DDAR_Ser2UARTRd
mdefine_line|#define DDAR_Ser2UARTRd&t;        &t;/* Ser. port 2 UART Read           */ &bslash;&n;                &t;(DDAR_DevRd + DDAR_Brst4 + DDAR_8BitDev + &bslash;&n;                &t; DDAR_Ser2ICPRc + DDAR_DevAdd (_Ser2UTDR))
DECL|macro|DDAR_Ser2HSSPWr
mdefine_line|#define DDAR_Ser2HSSPWr&t;        &t;/* Ser. port 2 HSSP Write          */ &bslash;&n;                &t;(DDAR_DevWr + DDAR_Brst8 + DDAR_8BitDev + &bslash;&n;                &t; DDAR_Ser2ICPTr + DDAR_DevAdd (_Ser2HSDR))
DECL|macro|DDAR_Ser2HSSPRd
mdefine_line|#define DDAR_Ser2HSSPRd&t;        &t;/* Ser. port 2 HSSP Read           */ &bslash;&n;                &t;(DDAR_DevRd + DDAR_Brst8 + DDAR_8BitDev + &bslash;&n;                &t; DDAR_Ser2ICPRc + DDAR_DevAdd (_Ser2HSDR))
DECL|macro|DDAR_Ser3UARTWr
mdefine_line|#define DDAR_Ser3UARTWr&t;        &t;/* Ser. port 3 UART Write          */ &bslash;&n;                &t;(DDAR_DevWr + DDAR_Brst4 + DDAR_8BitDev + &bslash;&n;                &t; DDAR_Ser3UARTTr + DDAR_DevAdd (_Ser3UTDR))
DECL|macro|DDAR_Ser3UARTRd
mdefine_line|#define DDAR_Ser3UARTRd&t;        &t;/* Ser. port 3 UART Read           */ &bslash;&n;                &t;(DDAR_DevRd + DDAR_Brst4 + DDAR_8BitDev + &bslash;&n;                &t; DDAR_Ser3UARTRc + DDAR_DevAdd (_Ser3UTDR))
DECL|macro|DDAR_Ser4MCP0Wr
mdefine_line|#define DDAR_Ser4MCP0Wr&t;        &t;/* Ser. port 4 MCP 0 Write (audio) */ &bslash;&n;                &t;(DDAR_DevWr + DDAR_Brst4 + DDAR_16BitDev + &bslash;&n;                &t; DDAR_Ser4MCP0Tr + DDAR_DevAdd (_Ser4MCDR0))
DECL|macro|DDAR_Ser4MCP0Rd
mdefine_line|#define DDAR_Ser4MCP0Rd&t;        &t;/* Ser. port 4 MCP 0 Read (audio)  */ &bslash;&n;                &t;(DDAR_DevRd + DDAR_Brst4 + DDAR_16BitDev + &bslash;&n;                &t; DDAR_Ser4MCP0Rc + DDAR_DevAdd (_Ser4MCDR0))
DECL|macro|DDAR_Ser4MCP1Wr
mdefine_line|#define DDAR_Ser4MCP1Wr&t;        &t;/* Ser. port 4 MCP 1 Write         */ &bslash;&n;                &t;        &t;/* (telecom)                       */ &bslash;&n;                &t;(DDAR_DevWr + DDAR_Brst4 + DDAR_16BitDev + &bslash;&n;                &t; DDAR_Ser4MCP1Tr + DDAR_DevAdd (_Ser4MCDR1))
DECL|macro|DDAR_Ser4MCP1Rd
mdefine_line|#define DDAR_Ser4MCP1Rd&t;        &t;/* Ser. port 4 MCP 1 Read          */ &bslash;&n;                &t;        &t;/* (telecom)                       */ &bslash;&n;                &t;(DDAR_DevRd + DDAR_Brst4 + DDAR_16BitDev + &bslash;&n;                &t; DDAR_Ser4MCP1Rc + DDAR_DevAdd (_Ser4MCDR1))
DECL|macro|DDAR_Ser4SSPWr
mdefine_line|#define DDAR_Ser4SSPWr&t;        &t;/* Ser. port 4 SSP Write (16 bits) */ &bslash;&n;                &t;(DDAR_DevWr + DDAR_Brst4 + DDAR_16BitDev + &bslash;&n;                &t; DDAR_Ser4SSPTr + DDAR_DevAdd (_Ser4SSDR))
DECL|macro|DDAR_Ser4SSPRd
mdefine_line|#define DDAR_Ser4SSPRd&t;        &t;/* Ser. port 4 SSP Read (16 bits)  */ &bslash;&n;                &t;(DDAR_DevRd + DDAR_Brst4 + DDAR_16BitDev + &bslash;&n;                &t; DDAR_Ser4SSPRc + DDAR_DevAdd (_Ser4SSDR))
DECL|macro|DCSR_RUN
mdefine_line|#define DCSR_RUN&t;0x00000001&t;/* DMA RUNing                      */
DECL|macro|DCSR_IE
mdefine_line|#define DCSR_IE &t;0x00000002&t;/* DMA Interrupt Enable            */
DECL|macro|DCSR_ERROR
mdefine_line|#define DCSR_ERROR&t;0x00000004&t;/* DMA ERROR                       */
DECL|macro|DCSR_DONEA
mdefine_line|#define DCSR_DONEA&t;0x00000008&t;/* DONE DMA transfer buffer A      */
DECL|macro|DCSR_STRTA
mdefine_line|#define DCSR_STRTA&t;0x00000010&t;/* STaRTed DMA transfer buffer A   */
DECL|macro|DCSR_DONEB
mdefine_line|#define DCSR_DONEB&t;0x00000020&t;/* DONE DMA transfer buffer B      */
DECL|macro|DCSR_STRTB
mdefine_line|#define DCSR_STRTB&t;0x00000040&t;/* STaRTed DMA transfer buffer B   */
DECL|macro|DCSR_BIU
mdefine_line|#define DCSR_BIU&t;0x00000080&t;/* DMA Buffer In Use               */
DECL|macro|DCSR_BufA
mdefine_line|#define DCSR_BufA&t;(DCSR_BIU*0)&t;/*  DMA Buffer A in use            */
DECL|macro|DCSR_BufB
mdefine_line|#define DCSR_BufB&t;(DCSR_BIU*1)&t;/*  DMA Buffer B in use            */
DECL|macro|DBT_TC
mdefine_line|#define DBT_TC  &t;Fld (13, 0)&t;/* Transfer Count                  */
DECL|macro|DBTA_TCA
mdefine_line|#define DBTA_TCA&t;DBT_TC  &t;/* Transfer Count buffer A         */
DECL|macro|DBTB_TCB
mdefine_line|#define DBTB_TCB&t;DBT_TC  &t;/* Transfer Count buffer B         */
multiline_comment|/*&n; * Liquid Crystal Display (LCD) control registers&n; *&n; * Registers&n; *    LCCR0     &t;Liquid Crystal Display (LCD) Control Register 0&n; *              &t;(read/write).&n; *              &t;[Bits LDM, BAM, and ERM are only implemented in&n; *              &t;versions 2.0 (rev. = 8) and higher of the StrongARM&n; *              &t;SA-1100.]&n; *    LCSR      &t;Liquid Crystal Display (LCD) Status Register&n; *              &t;(read/write).&n; *              &t;[Bit LDD can be only read in versions 1.0 (rev. = 1)&n; *              &t;and 1.1 (rev. = 2) of the StrongARM SA-1100, it can be&n; *              &t;read and written (cleared) in versions 2.0 (rev. = 8)&n; *              &t;and higher.]&n; *    DBAR1     &t;Liquid Crystal Display (LCD) Direct Memory Access&n; *              &t;(DMA) Base Address Register channel 1 (read/write).&n; *    DCAR1     &t;Liquid Crystal Display (LCD) Direct Memory Access&n; *              &t;(DMA) Current Address Register channel 1 (read).&n; *    DBAR2     &t;Liquid Crystal Display (LCD) Direct Memory Access&n; *              &t;(DMA) Base Address Register channel 2 (read/write).&n; *    DCAR2     &t;Liquid Crystal Display (LCD) Direct Memory Access&n; *              &t;(DMA) Current Address Register channel 2 (read).&n; *    LCCR1     &t;Liquid Crystal Display (LCD) Control Register 1&n; *              &t;(read/write).&n; *              &t;[The LCCR1 register can be only written in&n; *              &t;versions 1.0 (rev. = 1) and 1.1 (rev. = 2) of the&n; *              &t;StrongARM SA-1100, it can be written and read in&n; *              &t;versions 2.0 (rev. = 8) and higher.]&n; *    LCCR2     &t;Liquid Crystal Display (LCD) Control Register 2&n; *              &t;(read/write).&n; *              &t;[The LCCR1 register can be only written in&n; *              &t;versions 1.0 (rev. = 1) and 1.1 (rev. = 2) of the&n; *              &t;StrongARM SA-1100, it can be written and read in&n; *              &t;versions 2.0 (rev. = 8) and higher.]&n; *    LCCR3     &t;Liquid Crystal Display (LCD) Control Register 3&n; *              &t;(read/write).&n; *              &t;[The LCCR1 register can be only written in&n; *              &t;versions 1.0 (rev. = 1) and 1.1 (rev. = 2) of the&n; *              &t;StrongARM SA-1100, it can be written and read in&n; *              &t;versions 2.0 (rev. = 8) and higher. Bit PCP is only&n; *              &t;implemented in versions 2.0 (rev. = 8) and higher of&n; *              &t;the StrongARM SA-1100.]&n; *&n; * Clocks&n; *    fcpu, Tcpu&t;Frequency, period of the CPU core clock (CCLK).&n; *    fmem, Tmem&t;Frequency, period of the memory clock (fmem = fcpu/2).&n; *    fpix, Tpix&t;Frequency, period of the pixel clock.&n; *    fln, Tln  &t;Frequency, period of the line clock.&n; *    fac, Tac  &t;Frequency, period of the AC bias clock.&n; */
DECL|macro|LCD_PEntrySp
mdefine_line|#define LCD_PEntrySp&t;2       &t;/* LCD Palette Entry Space [byte]  */
DECL|macro|LCD_4BitPSp
mdefine_line|#define LCD_4BitPSp&t;        &t;/* LCD 4-Bit pixel Palette Space   */ &bslash;&n;                &t;        &t;/* [byte]                          */ &bslash;&n;                &t;(16*LCD_PEntrySp)
DECL|macro|LCD_8BitPSp
mdefine_line|#define LCD_8BitPSp&t;        &t;/* LCD 8-Bit pixel Palette Space   */ &bslash;&n;                &t;        &t;/* [byte]                          */ &bslash;&n;                &t;(256*LCD_PEntrySp)
DECL|macro|LCD_12_16BitPSp
mdefine_line|#define LCD_12_16BitPSp&t;        &t;/* LCD 12/16-Bit pixel             */ &bslash;&n;                &t;        &t;/* dummy-Palette Space [byte]      */ &bslash;&n;                &t;(16*LCD_PEntrySp)
DECL|macro|LCD_PGrey
mdefine_line|#define LCD_PGrey&t;Fld (4, 0)&t;/* LCD Palette entry Grey value    */
DECL|macro|LCD_PBlue
mdefine_line|#define LCD_PBlue&t;Fld (4, 0)&t;/* LCD Palette entry Blue value    */
DECL|macro|LCD_PGreen
mdefine_line|#define LCD_PGreen&t;Fld (4, 4)&t;/* LCD Palette entry Green value   */
DECL|macro|LCD_PRed
mdefine_line|#define LCD_PRed&t;Fld (4, 8)&t;/* LCD Palette entry Red value     */
DECL|macro|LCD_PBS
mdefine_line|#define LCD_PBS &t;Fld (2, 12)&t;/* LCD Pixel Bit Size              */
DECL|macro|LCD_4Bit
mdefine_line|#define LCD_4Bit&t;        &t;/*  LCD 4-Bit pixel mode           */ &bslash;&n;                &t;(0 &lt;&lt; FShft (LCD_PBS))
DECL|macro|LCD_8Bit
mdefine_line|#define LCD_8Bit&t;        &t;/*  LCD 8-Bit pixel mode           */ &bslash;&n;                &t;(1 &lt;&lt; FShft (LCD_PBS))
DECL|macro|LCD_12_16Bit
mdefine_line|#define LCD_12_16Bit&t;        &t;/*  LCD 12/16-Bit pixel mode       */ &bslash;&n;                &t;(2 &lt;&lt; FShft (LCD_PBS))
DECL|macro|LCD_Int0_0
mdefine_line|#define LCD_Int0_0&t;0x0     &t;/* LCD Intensity =   0.0% =  0     */
DECL|macro|LCD_Int11_1
mdefine_line|#define LCD_Int11_1&t;0x1     &t;/* LCD Intensity =  11.1% =  1/9   */
DECL|macro|LCD_Int20_0
mdefine_line|#define LCD_Int20_0&t;0x2     &t;/* LCD Intensity =  20.0% =  1/5   */
DECL|macro|LCD_Int26_7
mdefine_line|#define LCD_Int26_7&t;0x3     &t;/* LCD Intensity =  26.7% =  4/15  */
DECL|macro|LCD_Int33_3
mdefine_line|#define LCD_Int33_3&t;0x4     &t;/* LCD Intensity =  33.3% =  3/9   */
DECL|macro|LCD_Int40_0
mdefine_line|#define LCD_Int40_0&t;0x5     &t;/* LCD Intensity =  40.0% =  2/5   */
DECL|macro|LCD_Int44_4
mdefine_line|#define LCD_Int44_4&t;0x6     &t;/* LCD Intensity =  44.4% =  4/9   */
DECL|macro|LCD_Int50_0
mdefine_line|#define LCD_Int50_0&t;0x7     &t;/* LCD Intensity =  50.0% =  1/2   */
DECL|macro|LCD_Int55_6
mdefine_line|#define LCD_Int55_6&t;0x8     &t;/* LCD Intensity =  55.6% =  5/9   */
DECL|macro|LCD_Int60_0
mdefine_line|#define LCD_Int60_0&t;0x9     &t;/* LCD Intensity =  60.0% =  3/5   */
DECL|macro|LCD_Int66_7
mdefine_line|#define LCD_Int66_7&t;0xA     &t;/* LCD Intensity =  66.7% =  6/9   */
DECL|macro|LCD_Int73_3
mdefine_line|#define LCD_Int73_3&t;0xB     &t;/* LCD Intensity =  73.3% = 11/15  */
DECL|macro|LCD_Int80_0
mdefine_line|#define LCD_Int80_0&t;0xC     &t;/* LCD Intensity =  80.0% =  4/5   */
DECL|macro|LCD_Int88_9
mdefine_line|#define LCD_Int88_9&t;0xD     &t;/* LCD Intensity =  88.9% =  8/9   */
DECL|macro|LCD_Int100_0
mdefine_line|#define LCD_Int100_0&t;0xE     &t;/* LCD Intensity = 100.0% =  1     */
DECL|macro|LCD_Int100_0A
mdefine_line|#define LCD_Int100_0A&t;0xF     &t;/* LCD Intensity = 100.0% =  1     */
multiline_comment|/* (Alternative)                   */
DECL|macro|_LCCR0
mdefine_line|#define _LCCR0  &t;0xB0100000&t;/* LCD Control Reg. 0              */
DECL|macro|_LCSR
mdefine_line|#define _LCSR   &t;0xB0100004&t;/* LCD Status Reg.                 */
DECL|macro|_DBAR1
mdefine_line|#define _DBAR1  &t;0xB0100010&t;/* LCD DMA Base Address Reg.       */
multiline_comment|/* channel 1                       */
DECL|macro|_DCAR1
mdefine_line|#define _DCAR1  &t;0xB0100014&t;/* LCD DMA Current Address Reg.    */
multiline_comment|/* channel 1                       */
DECL|macro|_DBAR2
mdefine_line|#define _DBAR2  &t;0xB0100018&t;/* LCD DMA Base Address Reg.       */
multiline_comment|/* channel 2                       */
DECL|macro|_DCAR2
mdefine_line|#define _DCAR2  &t;0xB010001C&t;/* LCD DMA Current Address Reg.    */
multiline_comment|/* channel 2                       */
DECL|macro|_LCCR1
mdefine_line|#define _LCCR1  &t;0xB0100020&t;/* LCD Control Reg. 1              */
DECL|macro|_LCCR2
mdefine_line|#define _LCCR2  &t;0xB0100024&t;/* LCD Control Reg. 2              */
DECL|macro|_LCCR3
mdefine_line|#define _LCCR3  &t;0xB0100028&t;/* LCD Control Reg. 3              */
macro_line|#if LANGUAGE == C
DECL|macro|LCCR0
mdefine_line|#define LCCR0   &t;        &t;/* LCD Control Reg. 0              */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_LCCR0)))
DECL|macro|LCSR
mdefine_line|#define LCSR    &t;        &t;/* LCD Status Reg.                 */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_LCSR)))
DECL|macro|DBAR1
mdefine_line|#define DBAR1   &t;        &t;/* LCD DMA Base Address Reg.       */ &bslash;&n;                &t;        &t;/* channel 1                       */ &bslash;&n;                &t;(*((volatile Address *) io_p2v (_DBAR1)))
DECL|macro|DCAR1
mdefine_line|#define DCAR1   &t;        &t;/* LCD DMA Current Address Reg.    */ &bslash;&n;                &t;        &t;/* channel 1                       */ &bslash;&n;                &t;(*((volatile Address *) io_p2v (_DCAR1)))
DECL|macro|DBAR2
mdefine_line|#define DBAR2   &t;        &t;/* LCD DMA Base Address Reg.       */ &bslash;&n;                &t;        &t;/* channel 2                       */ &bslash;&n;                &t;(*((volatile Address *) io_p2v (_DBAR2)))
DECL|macro|DCAR2
mdefine_line|#define DCAR2   &t;        &t;/* LCD DMA Current Address Reg.    */ &bslash;&n;                &t;        &t;/* channel 2                       */ &bslash;&n;                &t;(*((volatile Address *) io_p2v (_DCAR2)))
DECL|macro|LCCR1
mdefine_line|#define LCCR1   &t;        &t;/* LCD Control Reg. 1              */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_LCCR1)))
DECL|macro|LCCR2
mdefine_line|#define LCCR2   &t;        &t;/* LCD Control Reg. 2              */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_LCCR2)))
DECL|macro|LCCR3
mdefine_line|#define LCCR3   &t;        &t;/* LCD Control Reg. 3              */ &bslash;&n;                &t;(*((volatile Word *) io_p2v (_LCCR3)))
macro_line|#endif /* LANGUAGE == C */
DECL|macro|LCCR0_LEN
mdefine_line|#define LCCR0_LEN&t;0x00000001&t;/* LCD ENable                      */
DECL|macro|LCCR0_CMS
mdefine_line|#define LCCR0_CMS&t;0x00000002&t;/* Color/Monochrome display Select */
DECL|macro|LCCR0_Color
mdefine_line|#define LCCR0_Color&t;(LCCR0_CMS*0)&t;/*  Color display                  */
DECL|macro|LCCR0_Mono
mdefine_line|#define LCCR0_Mono&t;(LCCR0_CMS*1)&t;/*  Monochrome display             */
DECL|macro|LCCR0_SDS
mdefine_line|#define LCCR0_SDS&t;0x00000004&t;/* Single/Dual panel display       */
multiline_comment|/* Select                          */
DECL|macro|LCCR0_Sngl
mdefine_line|#define LCCR0_Sngl&t;(LCCR0_SDS*0)&t;/*  Single panel display           */
DECL|macro|LCCR0_Dual
mdefine_line|#define LCCR0_Dual&t;(LCCR0_SDS*1)&t;/*  Dual panel display             */
DECL|macro|LCCR0_LDM
mdefine_line|#define LCCR0_LDM&t;0x00000008&t;/* LCD Disable done (LDD)          */
multiline_comment|/* interrupt Mask (disable)        */
DECL|macro|LCCR0_BAM
mdefine_line|#define LCCR0_BAM&t;0x00000010&t;/* Base Address update (BAU)       */
multiline_comment|/* interrupt Mask (disable)        */
DECL|macro|LCCR0_ERM
mdefine_line|#define LCCR0_ERM&t;0x00000020&t;/* LCD ERror (BER, IOL, IUL, IOU,  */
multiline_comment|/* IUU, OOL, OUL, OOU, and OUU)    */
multiline_comment|/* interrupt Mask (disable)        */
DECL|macro|LCCR0_PAS
mdefine_line|#define LCCR0_PAS&t;0x00000080&t;/* Passive/Active display Select   */
DECL|macro|LCCR0_Pas
mdefine_line|#define LCCR0_Pas&t;(LCCR0_PAS*0)&t;/*  Passive display (STN)          */
DECL|macro|LCCR0_Act
mdefine_line|#define LCCR0_Act&t;(LCCR0_PAS*1)&t;/*  Active display (TFT)           */
DECL|macro|LCCR0_BLE
mdefine_line|#define LCCR0_BLE&t;0x00000100&t;/* Big/Little Endian select        */
DECL|macro|LCCR0_LtlEnd
mdefine_line|#define LCCR0_LtlEnd&t;(LCCR0_BLE*0)&t;/*  Little Endian frame buffer     */
DECL|macro|LCCR0_BigEnd
mdefine_line|#define LCCR0_BigEnd&t;(LCCR0_BLE*1)&t;/*  Big Endian frame buffer        */
DECL|macro|LCCR0_DPD
mdefine_line|#define LCCR0_DPD&t;0x00000200&t;/* Double Pixel Data (monochrome   */
multiline_comment|/* display mode)                   */
DECL|macro|LCCR0_4PixMono
mdefine_line|#define LCCR0_4PixMono&t;(LCCR0_DPD*0)&t;/*  4-Pixel/clock Monochrome       */
multiline_comment|/*  display                        */
DECL|macro|LCCR0_8PixMono
mdefine_line|#define LCCR0_8PixMono&t;(LCCR0_DPD*1)&t;/*  8-Pixel/clock Monochrome       */
multiline_comment|/*  display                        */
DECL|macro|LCCR0_PDD
mdefine_line|#define LCCR0_PDD&t;Fld (8, 12)&t;/* Palette DMA request Delay       */
multiline_comment|/* [Tmem]                          */
DECL|macro|LCCR0_DMADel
mdefine_line|#define LCCR0_DMADel(Tcpu)      &t;/*  palette DMA request Delay      */ &bslash;&n;                &t;        &t;/*  [0..510 Tcpu]                  */ &bslash;&n;                &t;((Tcpu)/2 &lt;&lt; FShft (LCCR0_PDD))
DECL|macro|LCSR_LDD
mdefine_line|#define LCSR_LDD&t;0x00000001&t;/* LCD Disable Done                */
DECL|macro|LCSR_BAU
mdefine_line|#define LCSR_BAU&t;0x00000002&t;/* Base Address Update (read)      */
DECL|macro|LCSR_BER
mdefine_line|#define LCSR_BER&t;0x00000004&t;/* Bus ERror                       */
DECL|macro|LCSR_ABC
mdefine_line|#define LCSR_ABC&t;0x00000008&t;/* AC Bias clock Count             */
DECL|macro|LCSR_IOL
mdefine_line|#define LCSR_IOL&t;0x00000010&t;/* Input FIFO Over-run Lower       */
multiline_comment|/* panel                           */
DECL|macro|LCSR_IUL
mdefine_line|#define LCSR_IUL&t;0x00000020&t;/* Input FIFO Under-run Lower      */
multiline_comment|/* panel                           */
DECL|macro|LCSR_IOU
mdefine_line|#define LCSR_IOU&t;0x00000040&t;/* Input FIFO Over-run Upper       */
multiline_comment|/* panel                           */
DECL|macro|LCSR_IUU
mdefine_line|#define LCSR_IUU&t;0x00000080&t;/* Input FIFO Under-run Upper      */
multiline_comment|/* panel                           */
DECL|macro|LCSR_OOL
mdefine_line|#define LCSR_OOL&t;0x00000100&t;/* Output FIFO Over-run Lower      */
multiline_comment|/* panel                           */
DECL|macro|LCSR_OUL
mdefine_line|#define LCSR_OUL&t;0x00000200&t;/* Output FIFO Under-run Lower     */
multiline_comment|/* panel                           */
DECL|macro|LCSR_OOU
mdefine_line|#define LCSR_OOU&t;0x00000400&t;/* Output FIFO Over-run Upper      */
multiline_comment|/* panel                           */
DECL|macro|LCSR_OUU
mdefine_line|#define LCSR_OUU&t;0x00000800&t;/* Output FIFO Under-run Upper     */
multiline_comment|/* panel                           */
DECL|macro|LCCR1_PPL
mdefine_line|#define LCCR1_PPL&t;Fld (6, 4)&t;/* Pixels Per Line/16 - 1          */
DECL|macro|LCCR1_DisWdth
mdefine_line|#define LCCR1_DisWdth(Pixel)    &t;/*  Display Width [16..1024 pix.]  */ &bslash;&n;                &t;(((Pixel) - 16)/16 &lt;&lt; FShft (LCCR1_PPL))
DECL|macro|LCCR1_HSW
mdefine_line|#define LCCR1_HSW&t;Fld (6, 10)&t;/* Horizontal Synchronization      */
multiline_comment|/* pulse Width - 1 [Tpix] (L_LCLK) */
DECL|macro|LCCR1_HorSnchWdth
mdefine_line|#define LCCR1_HorSnchWdth(Tpix) &t;/*  Horizontal Synchronization     */ &bslash;&n;                &t;        &t;/*  pulse Width [1..64 Tpix]       */ &bslash;&n;                &t;(((Tpix) - 1) &lt;&lt; FShft (LCCR1_HSW))
DECL|macro|LCCR1_ELW
mdefine_line|#define LCCR1_ELW&t;Fld (8, 16)&t;/* End-of-Line pixel clock Wait    */
multiline_comment|/* count - 1 [Tpix]                */
DECL|macro|LCCR1_EndLnDel
mdefine_line|#define LCCR1_EndLnDel(Tpix)    &t;/*  End-of-Line Delay              */ &bslash;&n;                &t;        &t;/*  [1..256 Tpix]                  */ &bslash;&n;                &t;(((Tpix) - 1) &lt;&lt; FShft (LCCR1_ELW))
DECL|macro|LCCR1_BLW
mdefine_line|#define LCCR1_BLW&t;Fld (8, 24)&t;/* Beginning-of-Line pixel clock   */
multiline_comment|/* Wait count - 1 [Tpix]           */
DECL|macro|LCCR1_BegLnDel
mdefine_line|#define LCCR1_BegLnDel(Tpix)    &t;/*  Beginning-of-Line Delay        */ &bslash;&n;                &t;        &t;/*  [1..256 Tpix]                  */ &bslash;&n;                &t;(((Tpix) - 1) &lt;&lt; FShft (LCCR1_BLW))
DECL|macro|LCCR2_LPP
mdefine_line|#define LCCR2_LPP&t;Fld (10, 0)&t;/* Line Per Panel - 1              */
DECL|macro|LCCR2_DisHght
mdefine_line|#define LCCR2_DisHght(Line)     &t;/*  Display Height [1..1024 lines] */ &bslash;&n;                &t;(((Line) - 1) &lt;&lt; FShft (LCCR2_LPP))
DECL|macro|LCCR2_VSW
mdefine_line|#define LCCR2_VSW&t;Fld (6, 10)&t;/* Vertical Synchronization pulse  */
multiline_comment|/* Width - 1 [Tln] (L_FCLK)        */
DECL|macro|LCCR2_VrtSnchWdth
mdefine_line|#define LCCR2_VrtSnchWdth(Tln)  &t;/*  Vertical Synchronization pulse */ &bslash;&n;                &t;        &t;/*  Width [1..64 Tln]              */ &bslash;&n;                &t;(((Tln) - 1) &lt;&lt; FShft (LCCR2_VSW))
DECL|macro|LCCR2_EFW
mdefine_line|#define LCCR2_EFW&t;Fld (8, 16)&t;/* End-of-Frame line clock Wait    */
multiline_comment|/* count [Tln]                     */
DECL|macro|LCCR2_EndFrmDel
mdefine_line|#define LCCR2_EndFrmDel(Tln)    &t;/*  End-of-Frame Delay             */ &bslash;&n;                &t;        &t;/*  [0..255 Tln]                   */ &bslash;&n;                &t;((Tln) &lt;&lt; FShft (LCCR2_EFW))
DECL|macro|LCCR2_BFW
mdefine_line|#define LCCR2_BFW&t;Fld (8, 24)&t;/* Beginning-of-Frame line clock   */
multiline_comment|/* Wait count [Tln]                */
DECL|macro|LCCR2_BegFrmDel
mdefine_line|#define LCCR2_BegFrmDel(Tln)    &t;/*  Beginning-of-Frame Delay       */ &bslash;&n;                &t;        &t;/*  [0..255 Tln]                   */ &bslash;&n;                &t;((Tln) &lt;&lt; FShft (LCCR2_BFW))
DECL|macro|LCCR3_PCD
mdefine_line|#define LCCR3_PCD&t;Fld (8, 0)&t;/* Pixel Clock Divisor/2 - 2       */
multiline_comment|/* [1..255] (L_PCLK)               */
multiline_comment|/* fpix = fcpu/(2*(PCD + 2))       */
multiline_comment|/* Tpix = 2*(PCD + 2)*Tcpu         */
DECL|macro|LCCR3_PixClkDiv
mdefine_line|#define LCCR3_PixClkDiv(Div)    &t;/*  Pixel Clock Divisor [6..514]   */ &bslash;&n;                &t;(((Div) - 4)/2 &lt;&lt; FShft (LCCR3_PCD))
multiline_comment|/*  fpix = fcpu/(2*Floor (Div/2))  */
multiline_comment|/*  Tpix = 2*Floor (Div/2)*Tcpu    */
DECL|macro|LCCR3_CeilPixClkDiv
mdefine_line|#define LCCR3_CeilPixClkDiv(Div)&t;/*  Ceil. of PixClkDiv [6..514]    */ &bslash;&n;                &t;(((Div) - 3)/2 &lt;&lt; FShft (LCCR3_PCD))
multiline_comment|/*  fpix = fcpu/(2*Ceil (Div/2))   */
multiline_comment|/*  Tpix = 2*Ceil (Div/2)*Tcpu     */
DECL|macro|LCCR3_ACB
mdefine_line|#define LCCR3_ACB&t;Fld (8, 8)&t;/* AC Bias clock half period - 1   */
multiline_comment|/* [Tln] (L_BIAS)                  */
DECL|macro|LCCR3_ACBsDiv
mdefine_line|#define LCCR3_ACBsDiv(Div)      &t;/*  AC Bias clock Divisor [2..512] */ &bslash;&n;                &t;(((Div) - 2)/2 &lt;&lt; FShft (LCCR3_ACB))
multiline_comment|/*  fac = fln/(2*Floor (Div/2))    */
multiline_comment|/*  Tac = 2*Floor (Div/2)*Tln      */
DECL|macro|LCCR3_CeilACBsDiv
mdefine_line|#define LCCR3_CeilACBsDiv(Div)  &t;/*  Ceil. of ACBsDiv [2..512]      */ &bslash;&n;                &t;(((Div) - 1)/2 &lt;&lt; FShft (LCCR3_ACB))
multiline_comment|/*  fac = fln/(2*Ceil (Div/2))     */
multiline_comment|/*  Tac = 2*Ceil (Div/2)*Tln       */
DECL|macro|LCCR3_API
mdefine_line|#define LCCR3_API&t;Fld (4, 16)&t;/* AC bias Pin transitions per     */
multiline_comment|/* Interrupt                       */
DECL|macro|LCCR3_ACBsCntOff
mdefine_line|#define LCCR3_ACBsCntOff        &t;/*  AC Bias clock transition Count */ &bslash;&n;                &t;        &t;/*  Off                            */ &bslash;&n;                &t;(0 &lt;&lt; FShft (LCCR3_API))
DECL|macro|LCCR3_ACBsCnt
mdefine_line|#define LCCR3_ACBsCnt(Trans)    &t;/*  AC Bias clock transition Count */ &bslash;&n;                &t;        &t;/*  [1..15]                        */ &bslash;&n;                &t;((Trans) &lt;&lt; FShft (LCCR3_API))
DECL|macro|LCCR3_VSP
mdefine_line|#define LCCR3_VSP&t;0x00100000&t;/* Vertical Synchronization pulse  */
multiline_comment|/* Polarity (L_FCLK)               */
DECL|macro|LCCR3_VrtSnchH
mdefine_line|#define LCCR3_VrtSnchH&t;(LCCR3_VSP*0)&t;/*  Vertical Synchronization pulse */
multiline_comment|/*  active High                    */
DECL|macro|LCCR3_VrtSnchL
mdefine_line|#define LCCR3_VrtSnchL&t;(LCCR3_VSP*1)&t;/*  Vertical Synchronization pulse */
multiline_comment|/*  active Low                     */
DECL|macro|LCCR3_HSP
mdefine_line|#define LCCR3_HSP&t;0x00200000&t;/* Horizontal Synchronization      */
multiline_comment|/* pulse Polarity (L_LCLK)         */
DECL|macro|LCCR3_HorSnchH
mdefine_line|#define LCCR3_HorSnchH&t;(LCCR3_HSP*0)&t;/*  Horizontal Synchronization     */
multiline_comment|/*  pulse active High              */
DECL|macro|LCCR3_HorSnchL
mdefine_line|#define LCCR3_HorSnchL&t;(LCCR3_HSP*1)&t;/*  Horizontal Synchronization     */
multiline_comment|/*  pulse active Low               */
DECL|macro|LCCR3_PCP
mdefine_line|#define LCCR3_PCP&t;0x00400000&t;/* Pixel Clock Polarity (L_PCLK)   */
DECL|macro|LCCR3_PixRsEdg
mdefine_line|#define LCCR3_PixRsEdg&t;(LCCR3_PCP*0)&t;/*  Pixel clock Rising-Edge        */
DECL|macro|LCCR3_PixFlEdg
mdefine_line|#define LCCR3_PixFlEdg&t;(LCCR3_PCP*1)&t;/*  Pixel clock Falling-Edge       */
DECL|macro|LCCR3_OEP
mdefine_line|#define LCCR3_OEP&t;0x00800000&t;/* Output Enable Polarity (L_BIAS, */
multiline_comment|/* active display mode)            */
DECL|macro|LCCR3_OutEnH
mdefine_line|#define LCCR3_OutEnH&t;(LCCR3_OEP*0)&t;/*  Output Enable active High      */
DECL|macro|LCCR3_OutEnL
mdefine_line|#define LCCR3_OutEnL&t;(LCCR3_OEP*1)&t;/*  Output Enable active Low       */
DECL|macro|C
macro_line|#undef C
DECL|macro|Assembly
macro_line|#undef Assembly
eof
