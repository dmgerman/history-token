multiline_comment|/* $Id: pstate.h,v 1.6 1997/06/25 07:39:45 jj Exp $ */
macro_line|#ifndef _SPARC64_PSTATE_H
DECL|macro|_SPARC64_PSTATE_H
mdefine_line|#define _SPARC64_PSTATE_H
multiline_comment|/* The V9 PSTATE Register (with SpitFire extensions).&n; *&n; * -----------------------------------------------------------------------&n; * | Resv | IG | MG | CLE | TLE |  MM  | RED | PEF | AM | PRIV | IE | AG |&n; * -----------------------------------------------------------------------&n; *  63  12  11   10    9     8    7   6   5     4     3     2     1    0&n; */
DECL|macro|PSTATE_IG
mdefine_line|#define PSTATE_IG&t;0x0000000000000800&t;/* Interrupt Globals.&t;&t;*/
DECL|macro|PSTATE_MG
mdefine_line|#define PSTATE_MG&t;0x0000000000000400&t;/* MMU Globals.&t;&t;&t;*/
DECL|macro|PSTATE_CLE
mdefine_line|#define PSTATE_CLE&t;0x0000000000000200&t;/* Current Little Endian.&t;*/
DECL|macro|PSTATE_TLE
mdefine_line|#define PSTATE_TLE&t;0x0000000000000100&t;/* Trap Little Endian.&t;&t;*/
DECL|macro|PSTATE_MM
mdefine_line|#define PSTATE_MM&t;0x00000000000000c0&t;/* Memory Model.&t;&t;*/
DECL|macro|PSTATE_TSO
mdefine_line|#define PSTATE_TSO&t;0x0000000000000000&t;/* MM: Total Store Order&t;*/
DECL|macro|PSTATE_PSO
mdefine_line|#define PSTATE_PSO&t;0x0000000000000040&t;/* MM: Partial Store Order&t;*/
DECL|macro|PSTATE_RMO
mdefine_line|#define PSTATE_RMO&t;0x0000000000000080&t;/* MM: Relaxed Memory Order&t;*/
DECL|macro|PSTATE_RED
mdefine_line|#define PSTATE_RED&t;0x0000000000000020&t;/* Reset Error Debug State.&t;*/
DECL|macro|PSTATE_PEF
mdefine_line|#define PSTATE_PEF&t;0x0000000000000010&t;/* Floating Point Enable.&t;*/
DECL|macro|PSTATE_AM
mdefine_line|#define PSTATE_AM&t;0x0000000000000008&t;/* Address Mask.&t;&t;*/
DECL|macro|PSTATE_PRIV
mdefine_line|#define PSTATE_PRIV&t;0x0000000000000004&t;/* Privilege.&t;&t;&t;*/
DECL|macro|PSTATE_IE
mdefine_line|#define PSTATE_IE&t;0x0000000000000002&t;/* Interrupt Enable.&t;&t;*/
DECL|macro|PSTATE_AG
mdefine_line|#define PSTATE_AG&t;0x0000000000000001&t;/* Alternate Globals.&t;&t;*/
multiline_comment|/* The V9 TSTATE Register (with SpitFire and Linux extensions).&n; *&n; * ---------------------------------------------------------------&n; * |  Resv  |  CCR  |  ASI  |  %pil  |  PSTATE  |  Resv  |  CWP  |&n; * ---------------------------------------------------------------&n; *  63    40 39   32 31   24 23    20 19       8 7      5 4     0&n; */
DECL|macro|TSTATE_CCR
mdefine_line|#define TSTATE_CCR&t;0x000000ff00000000&t;/* Condition Codes.&t;&t;*/
DECL|macro|TSTATE_XCC
mdefine_line|#define TSTATE_XCC&t;0x000000f000000000&t;/* Condition Codes.&t;&t;*/
DECL|macro|TSTATE_XNEG
mdefine_line|#define TSTATE_XNEG&t;0x0000008000000000&t;/* %xcc Negative.&t;&t;*/
DECL|macro|TSTATE_XZERO
mdefine_line|#define TSTATE_XZERO&t;0x0000004000000000&t;/* %xcc Zero.&t;&t;&t;*/
DECL|macro|TSTATE_XOVFL
mdefine_line|#define TSTATE_XOVFL&t;0x0000002000000000&t;/* %xcc Overflow.&t;&t;*/
DECL|macro|TSTATE_XCARRY
mdefine_line|#define TSTATE_XCARRY&t;0x0000001000000000&t;/* %xcc Carry.&t;&t;&t;*/
DECL|macro|TSTATE_ICC
mdefine_line|#define TSTATE_ICC&t;0x0000000f00000000&t;/* Condition Codes.&t;&t;*/
DECL|macro|TSTATE_INEG
mdefine_line|#define TSTATE_INEG&t;0x0000000800000000&t;/* %icc Negative.&t;&t;*/
DECL|macro|TSTATE_IZERO
mdefine_line|#define TSTATE_IZERO&t;0x0000000400000000&t;/* %icc Zero.&t;&t;&t;*/
DECL|macro|TSTATE_IOVFL
mdefine_line|#define TSTATE_IOVFL&t;0x0000000200000000&t;/* %icc Overflow.&t;&t;*/
DECL|macro|TSTATE_ICARRY
mdefine_line|#define TSTATE_ICARRY&t;0x0000000100000000&t;/* %icc Carry.&t;&t;&t;*/
DECL|macro|TSTATE_ASI
mdefine_line|#define TSTATE_ASI&t;0x00000000ff000000&t;/* Address Space Identifier.&t;*/
DECL|macro|TSTATE_PIL
mdefine_line|#define TSTATE_PIL&t;0x0000000000f00000&t;/* %pil (Linux traps set this)  */
DECL|macro|TSTATE_PSTATE
mdefine_line|#define TSTATE_PSTATE&t;0x00000000000fff00&t;/* PSTATE.&t;&t;&t;*/
DECL|macro|TSTATE_IG
mdefine_line|#define TSTATE_IG&t;0x0000000000080000&t;/* Interrupt Globals.&t;&t;*/
DECL|macro|TSTATE_MG
mdefine_line|#define TSTATE_MG&t;0x0000000000040000&t;/* MMU Globals.&t;&t;&t;*/
DECL|macro|TSTATE_CLE
mdefine_line|#define TSTATE_CLE&t;0x0000000000020000&t;/* Current Little Endian.&t;*/
DECL|macro|TSTATE_TLE
mdefine_line|#define TSTATE_TLE&t;0x0000000000010000&t;/* Trap Little Endian.&t;&t;*/
DECL|macro|TSTATE_MM
mdefine_line|#define TSTATE_MM&t;0x000000000000c000&t;/* Memory Model.&t;&t;*/
DECL|macro|TSTATE_TSO
mdefine_line|#define TSTATE_TSO&t;0x0000000000000000&t;/* MM: Total Store Order&t;*/
DECL|macro|TSTATE_PSO
mdefine_line|#define TSTATE_PSO&t;0x0000000000004000&t;/* MM: Partial Store Order&t;*/
DECL|macro|TSTATE_RMO
mdefine_line|#define TSTATE_RMO&t;0x0000000000008000&t;/* MM: Relaxed Memory Order&t;*/
DECL|macro|TSTATE_RED
mdefine_line|#define TSTATE_RED&t;0x0000000000002000&t;/* Reset Error Debug State.&t;*/
DECL|macro|TSTATE_PEF
mdefine_line|#define TSTATE_PEF&t;0x0000000000001000&t;/* Floating Point Enable.&t;*/
DECL|macro|TSTATE_AM
mdefine_line|#define TSTATE_AM&t;0x0000000000000800&t;/* Address Mask.&t;&t;*/
DECL|macro|TSTATE_PRIV
mdefine_line|#define TSTATE_PRIV&t;0x0000000000000400&t;/* Privilege.&t;&t;&t;*/
DECL|macro|TSTATE_IE
mdefine_line|#define TSTATE_IE&t;0x0000000000000200&t;/* Interrupt Enable.&t;&t;*/
DECL|macro|TSTATE_AG
mdefine_line|#define TSTATE_AG&t;0x0000000000000100&t;/* Alternate Globals.&t;&t;*/
DECL|macro|TSTATE_CWP
mdefine_line|#define TSTATE_CWP&t;0x000000000000001f&t;/* Current Window Pointer.&t;*/
multiline_comment|/* Floating-Point Registers State Register.&n; *&n; * --------------------------------&n; * |  Resv  |  FEF  |  DU  |  DL  |&n; * --------------------------------&n; *  63     3    2       1      0&n; */
DECL|macro|FPRS_FEF
mdefine_line|#define FPRS_FEF&t;0x0000000000000004&t;/* Enable Floating Point.&t;*/
DECL|macro|FPRS_DU
mdefine_line|#define FPRS_DU&t;&t;0x0000000000000002&t;/* Dirty Upper.&t;&t;&t;*/
DECL|macro|FPRS_DL
mdefine_line|#define FPRS_DL&t;&t;0x0000000000000001&t;/* Dirty Lower.&t;&t;&t;*/
multiline_comment|/* Version Register.&n; *&n; * ------------------------------------------------------&n; * | MANUF | IMPL | MASK | Resv | MAXTL | Resv | MAXWIN |&n; * ------------------------------------------------------&n; *  63   48 47  32 31  24 23  16 15    8 7    5 4      0&n; */
DECL|macro|VERS_MANUF
mdefine_line|#define VERS_MANUF&t;0xffff000000000000&t;/* Manufacturer.&t;&t;*/
DECL|macro|VERS_IMPL
mdefine_line|#define VERS_IMPL&t;0x0000ffff00000000&t;/* Implementation.&t;&t;*/
DECL|macro|VERS_MASK
mdefine_line|#define VERS_MASK&t;0x00000000ff000000&t;/* Mask Set Revision.&t;&t;*/
DECL|macro|VERS_MAXTL
mdefine_line|#define VERS_MAXTL&t;0x000000000000ff00&t;/* Maximum Trap Level.&t;&t;*/
DECL|macro|VERS_MAXWIN
mdefine_line|#define VERS_MAXWIN&t;0x000000000000001f&t;/* Maximum Reg Window Index.&t;*/
macro_line|#if defined(__KERNEL__) &amp;&amp; !defined(__ASSEMBLY__)
DECL|macro|set_pstate
mdefine_line|#define set_pstate(bits)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;rdpr      %%pstate, %%g1&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;or        %%g1, %0, %%g1&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;wrpr      %%g1, 0x0, %%pstate&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;: /* no outputs */&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;i&quot; (bits)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;g1&quot;)
DECL|macro|clear_pstate
mdefine_line|#define clear_pstate(bits)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;rdpr      %%pstate, %%g1&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;andn        %%g1, %0, %%g1&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;wrpr      %%g1, 0x0, %%pstate&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;: /* no outputs */&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;i&quot; (bits)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;g1&quot;)
DECL|macro|change_pstate
mdefine_line|#define change_pstate(bits)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;rdpr      %%pstate, %%g1&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;wrpr      %%g1, %0, %%pstate&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;: /* no outputs */&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;i&quot; (bits)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;g1&quot;)
macro_line|#endif
macro_line|#endif /* !(_SPARC64_PSTATE_H) */
eof
