multiline_comment|/* $Id: tsunami.h,v 1.5 1996/08/29 09:49:03 davem Exp $&n; * tsunami.h:  Module specific definitions for Tsunami V8 Sparcs&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_TSUNAMI_H
DECL|macro|_SPARC_TSUNAMI_H
mdefine_line|#define _SPARC_TSUNAMI_H
macro_line|#include &lt;asm/asi.h&gt;
multiline_comment|/* The MMU control register on the Tsunami:&n; *&n; * -----------------------------------------------------------------------&n; * | implvers |SW|AV|DV|MV| RSV |PC|ITD|ALC| RSV |PE| RC |IE|DE|RSV|NF|ME|&n; * -----------------------------------------------------------------------&n; *  31      24 23 22 21 20 19-18 17  16 14  13-12 11 10-9  8  7 6-2  1  0&n; *&n; * SW: Enable Software Table Walks  0=off 1=on&n; * AV: Address View bit&n; * DV: Data View bit&n; * MV: Memory View bit&n; * PC: Parity Control&n; * ITD: ITBR disable&n; * ALC: Alternate Cacheable&n; * PE: Parity Enable   0=off 1=on&n; * RC: Refresh Control&n; * IE: Instruction cache Enable  0=off 1=on&n; * DE: Data cache Enable  0=off 1=on&n; * NF: No Fault, same as all other SRMMUs&n; * ME: MMU Enable, same as all other SRMMUs&n; */
DECL|macro|TSUNAMI_SW
mdefine_line|#define TSUNAMI_SW        0x00800000
DECL|macro|TSUNAMI_AV
mdefine_line|#define TSUNAMI_AV        0x00400000
DECL|macro|TSUNAMI_DV
mdefine_line|#define TSUNAMI_DV        0x00200000
DECL|macro|TSUNAMI_MV
mdefine_line|#define TSUNAMI_MV        0x00100000
DECL|macro|TSUNAMI_PC
mdefine_line|#define TSUNAMI_PC        0x00020000
DECL|macro|TSUNAMI_ITD
mdefine_line|#define TSUNAMI_ITD       0x00010000
DECL|macro|TSUNAMI_ALC
mdefine_line|#define TSUNAMI_ALC       0x00008000
DECL|macro|TSUNAMI_PE
mdefine_line|#define TSUNAMI_PE        0x00001000
DECL|macro|TSUNAMI_RCMASK
mdefine_line|#define TSUNAMI_RCMASK    0x00000C00
DECL|macro|TSUNAMI_IENAB
mdefine_line|#define TSUNAMI_IENAB     0x00000200
DECL|macro|TSUNAMI_DENAB
mdefine_line|#define TSUNAMI_DENAB     0x00000100
DECL|macro|TSUNAMI_NF
mdefine_line|#define TSUNAMI_NF        0x00000002
DECL|macro|TSUNAMI_ME
mdefine_line|#define TSUNAMI_ME        0x00000001
DECL|function|tsunami_flush_icache
r_extern
id|__inline__
r_void
id|tsunami_flush_icache
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%%g0] %0&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;i&quot;
(paren
id|ASI_M_IC_FLCLEAR
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|tsunami_flush_dcache
r_extern
id|__inline__
r_void
id|tsunami_flush_dcache
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%%g0] %0&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;i&quot;
(paren
id|ASI_M_DC_FLCLEAR
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* !(_SPARC_TSUNAMI_H) */
eof
