multiline_comment|/* $Id: pstate.h,v 1.6 1997/06/25 07:39:45 jj Exp $ */
macro_line|#ifndef _SPARC64_PSTATE_H
DECL|macro|_SPARC64_PSTATE_H
mdefine_line|#define _SPARC64_PSTATE_H
macro_line|#include &lt;asm/const.h&gt;
multiline_comment|/* The V9 PSTATE Register (with SpitFire extensions).&n; *&n; * -----------------------------------------------------------------------&n; * | Resv | IG | MG | CLE | TLE |  MM  | RED | PEF | AM | PRIV | IE | AG |&n; * -----------------------------------------------------------------------&n; *  63  12  11   10    9     8    7   6   5     4     3     2     1    0&n; */
DECL|macro|PSTATE_IG
mdefine_line|#define PSTATE_IG   _AC(0x0000000000000800,UL) /* Interrupt Globals.&t;*/
DECL|macro|PSTATE_MG
mdefine_line|#define PSTATE_MG   _AC(0x0000000000000400,UL) /* MMU Globals.&t;&t;*/
DECL|macro|PSTATE_CLE
mdefine_line|#define PSTATE_CLE  _AC(0x0000000000000200,UL) /* Current Little Endian.*/
DECL|macro|PSTATE_TLE
mdefine_line|#define PSTATE_TLE  _AC(0x0000000000000100,UL) /* Trap Little Endian.&t;*/
DECL|macro|PSTATE_MM
mdefine_line|#define PSTATE_MM   _AC(0x00000000000000c0,UL) /* Memory Model.&t;&t;*/
DECL|macro|PSTATE_TSO
mdefine_line|#define PSTATE_TSO  _AC(0x0000000000000000,UL) /* MM: TotalStoreOrder&t;*/
DECL|macro|PSTATE_PSO
mdefine_line|#define PSTATE_PSO  _AC(0x0000000000000040,UL) /* MM: PartialStoreOrder&t;*/
DECL|macro|PSTATE_RMO
mdefine_line|#define PSTATE_RMO  _AC(0x0000000000000080,UL) /* MM: RelaxedMemoryOrder*/
DECL|macro|PSTATE_RED
mdefine_line|#define PSTATE_RED  _AC(0x0000000000000020,UL) /* Reset Error Debug.&t;*/
DECL|macro|PSTATE_PEF
mdefine_line|#define PSTATE_PEF  _AC(0x0000000000000010,UL) /* Floating Point Enable.*/
DECL|macro|PSTATE_AM
mdefine_line|#define PSTATE_AM   _AC(0x0000000000000008,UL) /* Address Mask.&t;&t;*/
DECL|macro|PSTATE_PRIV
mdefine_line|#define PSTATE_PRIV _AC(0x0000000000000004,UL) /* Privilege.&t;&t;*/
DECL|macro|PSTATE_IE
mdefine_line|#define PSTATE_IE   _AC(0x0000000000000002,UL) /* Interrupt Enable.&t;*/
DECL|macro|PSTATE_AG
mdefine_line|#define PSTATE_AG   _AC(0x0000000000000001,UL) /* Alternate Globals.&t;*/
multiline_comment|/* The V9 TSTATE Register (with SpitFire and Linux extensions).&n; *&n; * ---------------------------------------------------------------&n; * |  Resv  |  CCR  |  ASI  |  %pil  |  PSTATE  |  Resv  |  CWP  |&n; * ---------------------------------------------------------------&n; *  63    40 39   32 31   24 23    20 19       8 7      5 4     0&n; */
DECL|macro|TSTATE_CCR
mdefine_line|#define TSTATE_CCR&t;_AC(0x000000ff00000000,UL) /* Condition Codes.&t;*/
DECL|macro|TSTATE_XCC
mdefine_line|#define TSTATE_XCC&t;_AC(0x000000f000000000,UL) /* Condition Codes.&t;*/
DECL|macro|TSTATE_XNEG
mdefine_line|#define TSTATE_XNEG&t;_AC(0x0000008000000000,UL) /* %xcc Negative.&t;*/
DECL|macro|TSTATE_XZERO
mdefine_line|#define TSTATE_XZERO&t;_AC(0x0000004000000000,UL) /* %xcc Zero.&t;*/
DECL|macro|TSTATE_XOVFL
mdefine_line|#define TSTATE_XOVFL&t;_AC(0x0000002000000000,UL) /* %xcc Overflow.&t;*/
DECL|macro|TSTATE_XCARRY
mdefine_line|#define TSTATE_XCARRY&t;_AC(0x0000001000000000,UL) /* %xcc Carry.&t;*/
DECL|macro|TSTATE_ICC
mdefine_line|#define TSTATE_ICC&t;_AC(0x0000000f00000000,UL) /* Condition Codes.&t;*/
DECL|macro|TSTATE_INEG
mdefine_line|#define TSTATE_INEG&t;_AC(0x0000000800000000,UL) /* %icc Negative.&t;*/
DECL|macro|TSTATE_IZERO
mdefine_line|#define TSTATE_IZERO&t;_AC(0x0000000400000000,UL) /* %icc Zero.&t;*/
DECL|macro|TSTATE_IOVFL
mdefine_line|#define TSTATE_IOVFL&t;_AC(0x0000000200000000,UL) /* %icc Overflow.&t;*/
DECL|macro|TSTATE_ICARRY
mdefine_line|#define TSTATE_ICARRY&t;_AC(0x0000000100000000,UL) /* %icc Carry.&t;*/
DECL|macro|TSTATE_ASI
mdefine_line|#define TSTATE_ASI&t;_AC(0x00000000ff000000,UL) /* AddrSpace ID.&t;*/
DECL|macro|TSTATE_PIL
mdefine_line|#define TSTATE_PIL&t;_AC(0x0000000000f00000,UL) /* %pil (Linux traps)*/
DECL|macro|TSTATE_PSTATE
mdefine_line|#define TSTATE_PSTATE&t;_AC(0x00000000000fff00,UL) /* PSTATE.&t;&t;*/
DECL|macro|TSTATE_IG
mdefine_line|#define TSTATE_IG&t;_AC(0x0000000000080000,UL) /* Interrupt Globals.*/
DECL|macro|TSTATE_MG
mdefine_line|#define TSTATE_MG&t;_AC(0x0000000000040000,UL) /* MMU Globals.&t;*/
DECL|macro|TSTATE_CLE
mdefine_line|#define TSTATE_CLE&t;_AC(0x0000000000020000,UL) /* CurrLittleEndian.&t;*/
DECL|macro|TSTATE_TLE
mdefine_line|#define TSTATE_TLE&t;_AC(0x0000000000010000,UL) /* TrapLittleEndian.&t;*/
DECL|macro|TSTATE_MM
mdefine_line|#define TSTATE_MM&t;_AC(0x000000000000c000,UL) /* Memory Model.&t;*/
DECL|macro|TSTATE_TSO
mdefine_line|#define TSTATE_TSO&t;_AC(0x0000000000000000,UL) /* MM: TSO&t;&t;*/
DECL|macro|TSTATE_PSO
mdefine_line|#define TSTATE_PSO&t;_AC(0x0000000000004000,UL) /* MM: PSO&t;&t;*/
DECL|macro|TSTATE_RMO
mdefine_line|#define TSTATE_RMO&t;_AC(0x0000000000008000,UL) /* MM: RMO&t;&t;*/
DECL|macro|TSTATE_RED
mdefine_line|#define TSTATE_RED&t;_AC(0x0000000000002000,UL) /* Reset Error Debug.*/
DECL|macro|TSTATE_PEF
mdefine_line|#define TSTATE_PEF&t;_AC(0x0000000000001000,UL) /* FPU Enable.&t;*/
DECL|macro|TSTATE_AM
mdefine_line|#define TSTATE_AM&t;_AC(0x0000000000000800,UL) /* Address Mask.&t;*/
DECL|macro|TSTATE_PRIV
mdefine_line|#define TSTATE_PRIV&t;_AC(0x0000000000000400,UL) /* Privilege.&t;*/
DECL|macro|TSTATE_IE
mdefine_line|#define TSTATE_IE&t;_AC(0x0000000000000200,UL) /* Interrupt Enable.&t;*/
DECL|macro|TSTATE_AG
mdefine_line|#define TSTATE_AG&t;_AC(0x0000000000000100,UL) /* Alternate Globals.*/
DECL|macro|TSTATE_CWP
mdefine_line|#define TSTATE_CWP&t;_AC(0x000000000000001f,UL) /* Curr Win-Pointer.&t;*/
multiline_comment|/* Floating-Point Registers State Register.&n; *&n; * --------------------------------&n; * |  Resv  |  FEF  |  DU  |  DL  |&n; * --------------------------------&n; *  63     3    2       1      0&n; */
DECL|macro|FPRS_FEF
mdefine_line|#define FPRS_FEF&t;_AC(0x0000000000000004,UL) /* FPU Enable.&t;*/
DECL|macro|FPRS_DU
mdefine_line|#define FPRS_DU&t;&t;_AC(0x0000000000000002,UL) /* Dirty Upper.&t;*/
DECL|macro|FPRS_DL
mdefine_line|#define FPRS_DL&t;&t;_AC(0x0000000000000001,UL) /* Dirty Lower.&t;*/
multiline_comment|/* Version Register.&n; *&n; * ------------------------------------------------------&n; * | MANUF | IMPL | MASK | Resv | MAXTL | Resv | MAXWIN |&n; * ------------------------------------------------------&n; *  63   48 47  32 31  24 23  16 15    8 7    5 4      0&n; */
DECL|macro|VERS_MANUF
mdefine_line|#define VERS_MANUF&t;_AC(0xffff000000000000,UL) /* Manufacturer.&t;*/
DECL|macro|VERS_IMPL
mdefine_line|#define VERS_IMPL&t;_AC(0x0000ffff00000000,UL) /* Implementation.&t;*/
DECL|macro|VERS_MASK
mdefine_line|#define VERS_MASK&t;_AC(0x00000000ff000000,UL) /* Mask Set Revision.*/
DECL|macro|VERS_MAXTL
mdefine_line|#define VERS_MAXTL&t;_AC(0x000000000000ff00,UL) /* Max Trap Level.&t;*/
DECL|macro|VERS_MAXWIN
mdefine_line|#define VERS_MAXWIN&t;_AC(0x000000000000001f,UL) /* Max RegWindow Idx.*/
macro_line|#endif /* !(_SPARC64_PSTATE_H) */
eof
