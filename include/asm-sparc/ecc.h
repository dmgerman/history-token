multiline_comment|/* $Id: ecc.h,v 1.3 1996/04/25 06:12:57 davem Exp $&n; * ecc.h: Definitions and defines for the external cache/memory&n; *        controller on the sun4m.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_ECC_H
DECL|macro|_SPARC_ECC_H
mdefine_line|#define _SPARC_ECC_H
multiline_comment|/* These registers are accessed through the SRMMU passthrough ASI 0x20 */
DECL|macro|ECC_ENABLE
mdefine_line|#define ECC_ENABLE     0x00000000       /* ECC enable register */
DECL|macro|ECC_FSTATUS
mdefine_line|#define ECC_FSTATUS    0x00000008       /* ECC fault status register */
DECL|macro|ECC_FADDR
mdefine_line|#define ECC_FADDR      0x00000010       /* ECC fault address register */
DECL|macro|ECC_DIGNOSTIC
mdefine_line|#define ECC_DIGNOSTIC  0x00000018       /* ECC diagnostics register */
DECL|macro|ECC_MBAENAB
mdefine_line|#define ECC_MBAENAB    0x00000020       /* MBus arbiter enable register */
DECL|macro|ECC_DMESG
mdefine_line|#define ECC_DMESG      0x00001000       /* Diagnostic message passing area */
multiline_comment|/* ECC MBus Arbiter Enable register:&n; *&n; * ----------------------------------------&n; * |              |SBUS|MOD3|MOD2|MOD1|RSV|&n; * ----------------------------------------&n; *  31           5   4   3    2    1    0&n; *&n; * SBUS: Enable MBus Arbiter on the SBus 0=off 1=on&n; * MOD3: Enable MBus Arbiter on MBus module 3  0=off 1=on&n; * MOD2: Enable MBus Arbiter on MBus module 2  0=off 1=on&n; * MOD1: Enable MBus Arbiter on MBus module 1  0=off 1=on&n; */
DECL|macro|ECC_MBAE_SBUS
mdefine_line|#define ECC_MBAE_SBUS     0x00000010
DECL|macro|ECC_MBAE_MOD3
mdefine_line|#define ECC_MBAE_MOD3     0x00000008
DECL|macro|ECC_MBAE_MOD2
mdefine_line|#define ECC_MBAE_MOD2     0x00000004
DECL|macro|ECC_MBAE_MOD1
mdefine_line|#define ECC_MBAE_MOD1     0x00000002 
multiline_comment|/* ECC Fault Control Register layout:&n; *&n; * -----------------------------&n; * |    RESV   | ECHECK | EINT |&n; * -----------------------------&n; *  31        2     1       0&n; *&n; * ECHECK:  Enable ECC checking.  0=off 1=on&n; * EINT:  Enable Interrupts for correctable errors. 0=off 1=on&n; */
DECL|macro|ECC_FCR_CHECK
mdefine_line|#define ECC_FCR_CHECK    0x00000002
DECL|macro|ECC_FCR_INTENAB
mdefine_line|#define ECC_FCR_INTENAB  0x00000001
multiline_comment|/* ECC Fault Address Register Zero layout:&n; *&n; * -----------------------------------------------------&n; * | MID | S | RSV |  VA   | BM |AT| C| SZ |TYP| PADDR |&n; * -----------------------------------------------------&n; *  31-28  27 26-22  21-14   13  12 11 10-8 7-4   3-0&n; *&n; * MID: ModuleID of the faulting processor. ie. who did it?&n; * S: Supervisor/Privileged access? 0=no 1=yes&n; * VA: Bits 19-12 of the virtual faulting address, these are the&n; *     superset bits in the virtual cache and can be used for&n; *     a flush operation if necessary.&n; * BM: Boot mode? 0=no 1=yes  This is just like the SRMMU boot&n; *     mode bit.&n; * AT: Did this fault happen during an atomic instruction? 0=no&n; *     1=yes.  This means either an &squot;ldstub&squot; or &squot;swap&squot; instruction&n; *     was in progress (but not finished) when this fault happened.&n; *     This indicated whether the bus was locked when the fault&n; *     occurred.&n; * C: Did the pte for this access indicate that it was cacheable?&n; *    0=no 1=yes&n; * SZ: The size of the transaction.&n; * TYP: The transaction type.&n; * PADDR: Bits 35-32 of the physical address for the fault.&n; */
DECL|macro|ECC_FADDR0_MIDMASK
mdefine_line|#define ECC_FADDR0_MIDMASK   0xf0000000
DECL|macro|ECC_FADDR0_S
mdefine_line|#define ECC_FADDR0_S         0x08000000
DECL|macro|ECC_FADDR0_VADDR
mdefine_line|#define ECC_FADDR0_VADDR     0x003fc000
DECL|macro|ECC_FADDR0_BMODE
mdefine_line|#define ECC_FADDR0_BMODE     0x00002000
DECL|macro|ECC_FADDR0_ATOMIC
mdefine_line|#define ECC_FADDR0_ATOMIC    0x00001000
DECL|macro|ECC_FADDR0_CACHE
mdefine_line|#define ECC_FADDR0_CACHE     0x00000800
DECL|macro|ECC_FADDR0_SIZE
mdefine_line|#define ECC_FADDR0_SIZE      0x00000700
DECL|macro|ECC_FADDR0_TYPE
mdefine_line|#define ECC_FADDR0_TYPE      0x000000f0
DECL|macro|ECC_FADDR0_PADDR
mdefine_line|#define ECC_FADDR0_PADDR     0x0000000f
multiline_comment|/* ECC Fault Address Register One layout:&n; *&n; * -------------------------------------&n; * |          Physical Address 31-0    |&n; * -------------------------------------&n; *  31                               0&n; *&n; * You get the upper 4 bits of the physical address from the&n; * PADDR field in ECC Fault Address Zero register.&n; */
multiline_comment|/* ECC Fault Status Register layout:&n; *&n; * ----------------------------------------------&n; * | RESV|C2E|MULT|SYNDROME|DWORD|UNC|TIMEO|BS|C|&n; * ----------------------------------------------&n; *  31-18  17  16    15-8    7-4   3    2    1 0&n; *&n; * C2E: A C2 graphics error occurred. 0=no 1=yes (SS10 only)&n; * MULT: Multiple errors occurred ;-O 0=no 1=prom_panic(yes)&n; * SYNDROME: Controller is mentally unstable.&n; * DWORD:&n; * UNC: Uncorrectable error.  0=no 1=yes&n; * TIMEO: Timeout occurred. 0=no 1=yes&n; * BS: C2 graphics bad slot access. 0=no 1=yes (SS10 only)&n; * C: Correctable error? 0=no 1=yes&n; */
DECL|macro|ECC_FSR_C2ERR
mdefine_line|#define ECC_FSR_C2ERR    0x00020000
DECL|macro|ECC_FSR_MULT
mdefine_line|#define ECC_FSR_MULT     0x00010000
DECL|macro|ECC_FSR_SYND
mdefine_line|#define ECC_FSR_SYND     0x0000ff00
DECL|macro|ECC_FSR_DWORD
mdefine_line|#define ECC_FSR_DWORD    0x000000f0
DECL|macro|ECC_FSR_UNC
mdefine_line|#define ECC_FSR_UNC      0x00000008
DECL|macro|ECC_FSR_TIMEO
mdefine_line|#define ECC_FSR_TIMEO    0x00000004
DECL|macro|ECC_FSR_BADSLOT
mdefine_line|#define ECC_FSR_BADSLOT  0x00000002
DECL|macro|ECC_FSR_C
mdefine_line|#define ECC_FSR_C        0x00000001
macro_line|#endif /* !(_SPARC_ECC_H) */
eof
