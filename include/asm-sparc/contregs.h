multiline_comment|/* $Id: contregs.h,v 1.8 2000/12/28 22:49:11 davem Exp $ */
macro_line|#ifndef _SPARC_CONTREGS_H
DECL|macro|_SPARC_CONTREGS_H
mdefine_line|#define _SPARC_CONTREGS_H
multiline_comment|/* contregs.h:  Addresses of registers in the ASI_CONTROL alternate address&n; *              space. These are for the mmu&squot;s context register, etc.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
multiline_comment|/* 3=sun3&n;   4=sun4 (as in sun4 sysmaint student book)&n;   c=sun4c (according to davem) */
DECL|macro|AC_IDPROM
mdefine_line|#define AC_IDPROM     0x00000000    /* 34  ID PROM, R/O, byte, 32 bytes      */
DECL|macro|AC_PAGEMAP
mdefine_line|#define AC_PAGEMAP    0x10000000    /* 3   Pagemap R/W, long                 */
DECL|macro|AC_SEGMAP
mdefine_line|#define AC_SEGMAP     0x20000000    /* 3   Segment map, byte                 */
DECL|macro|AC_CONTEXT
mdefine_line|#define AC_CONTEXT    0x30000000    /* 34c current mmu-context               */
DECL|macro|AC_SENABLE
mdefine_line|#define AC_SENABLE    0x40000000    /* 34c system dvma/cache/reset enable reg*/
DECL|macro|AC_UDVMA_ENB
mdefine_line|#define AC_UDVMA_ENB  0x50000000    /* 34  Not used on Sun boards, byte      */
DECL|macro|AC_BUS_ERROR
mdefine_line|#define AC_BUS_ERROR  0x60000000    /* 34  Not cleared on read, byte.        */
DECL|macro|AC_SYNC_ERR
mdefine_line|#define AC_SYNC_ERR   0x60000000    /*  c fault type                         */
DECL|macro|AC_SYNC_VA
mdefine_line|#define AC_SYNC_VA    0x60000004    /*  c fault virtual address              */
DECL|macro|AC_ASYNC_ERR
mdefine_line|#define AC_ASYNC_ERR  0x60000008    /*  c asynchronous fault type            */
DECL|macro|AC_ASYNC_VA
mdefine_line|#define AC_ASYNC_VA   0x6000000c    /*  c async fault virtual address        */
DECL|macro|AC_LEDS
mdefine_line|#define AC_LEDS       0x70000000    /* 34  Zero turns on LEDs, byte          */
DECL|macro|AC_CACHETAGS
mdefine_line|#define AC_CACHETAGS  0x80000000    /* 34c direct access to the VAC tags     */
DECL|macro|AC_CACHEDDATA
mdefine_line|#define AC_CACHEDDATA 0x90000000    /* 3 c direct access to the VAC data     */
DECL|macro|AC_UDVMA_MAP
mdefine_line|#define AC_UDVMA_MAP  0xD0000000    /* 4  Not used on Sun boards, byte       */
DECL|macro|AC_VME_VECTOR
mdefine_line|#define AC_VME_VECTOR 0xE0000000    /* 4  For non-Autovector VME, byte       */
DECL|macro|AC_BOOT_SCC
mdefine_line|#define AC_BOOT_SCC   0xF0000000    /* 34  bypass to access Zilog 8530. byte.*/
multiline_comment|/* s=Swift, h=Ross_HyperSPARC, v=TI_Viking, t=Tsunami, r=Ross_Cypress        */
DECL|macro|AC_M_PCR
mdefine_line|#define AC_M_PCR      0x0000        /* shv Processor Control Reg             */
DECL|macro|AC_M_CTPR
mdefine_line|#define AC_M_CTPR     0x0100        /* shv Context Table Pointer Reg         */
DECL|macro|AC_M_CXR
mdefine_line|#define AC_M_CXR      0x0200        /* shv Context Register                  */
DECL|macro|AC_M_SFSR
mdefine_line|#define AC_M_SFSR     0x0300        /* shv Synchronous Fault Status Reg      */
DECL|macro|AC_M_SFAR
mdefine_line|#define AC_M_SFAR     0x0400        /* shv Synchronous Fault Address Reg     */
DECL|macro|AC_M_AFSR
mdefine_line|#define AC_M_AFSR     0x0500        /*  hv Asynchronous Fault Status Reg     */
DECL|macro|AC_M_AFAR
mdefine_line|#define AC_M_AFAR     0x0600        /*  hv Asynchronous Fault Address Reg    */
DECL|macro|AC_M_RESET
mdefine_line|#define AC_M_RESET    0x0700        /*  hv Reset Reg                         */
DECL|macro|AC_M_RPR
mdefine_line|#define AC_M_RPR      0x1000        /*  hv Root Pointer Reg                  */
DECL|macro|AC_M_TSUTRCR
mdefine_line|#define AC_M_TSUTRCR  0x1000        /* s   TLB Replacement Ctrl Reg          */
DECL|macro|AC_M_IAPTP
mdefine_line|#define AC_M_IAPTP    0x1100        /*  hv Instruction Access PTP            */
DECL|macro|AC_M_DAPTP
mdefine_line|#define AC_M_DAPTP    0x1200        /*  hv Data Access PTP                   */
DECL|macro|AC_M_ITR
mdefine_line|#define AC_M_ITR      0x1300        /*  hv Index Tag Register                */
DECL|macro|AC_M_TRCR
mdefine_line|#define AC_M_TRCR     0x1400        /*  hv TLB Replacement Control Reg       */
DECL|macro|AC_M_SFSRX
mdefine_line|#define AC_M_SFSRX    0x1300        /* s   Synch Fault Status Reg prim       */
DECL|macro|AC_M_SFARX
mdefine_line|#define AC_M_SFARX    0x1400        /* s   Synch Fault Address Reg prim      */
DECL|macro|AC_M_RPR1
mdefine_line|#define AC_M_RPR1     0x1500        /*  h  Root Pointer Reg (entry 2)        */
DECL|macro|AC_M_IAPTP1
mdefine_line|#define AC_M_IAPTP1   0x1600        /*  h  Instruction Access PTP (entry 2)  */
DECL|macro|AC_M_DAPTP1
mdefine_line|#define AC_M_DAPTP1   0x1700        /*  h  Data Access PTP (entry 2)         */
macro_line|#endif /* _SPARC_CONTREGS_H */
eof
