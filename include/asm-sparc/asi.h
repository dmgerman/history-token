multiline_comment|/* $Id: asi.h,v 1.18 1998/03/09 14:04:46 jj Exp $ */
macro_line|#ifndef _SPARC_ASI_H
DECL|macro|_SPARC_ASI_H
mdefine_line|#define _SPARC_ASI_H
multiline_comment|/* asi.h:  Address Space Identifier values for the sparc.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; *&n; * Pioneer work for sun4m: Paul Hatchman (paul@sfe.com.au)&n; * Joint edition for sun4c+sun4m: Pete A. Zaitcev &lt;zaitcev@ipmce.su&gt;&n; */
multiline_comment|/* The first batch are for the sun4c. */
DECL|macro|ASI_NULL1
mdefine_line|#define ASI_NULL1           0x00
DECL|macro|ASI_NULL2
mdefine_line|#define ASI_NULL2           0x01
multiline_comment|/* sun4c and sun4 control registers and mmu/vac ops */
DECL|macro|ASI_CONTROL
mdefine_line|#define ASI_CONTROL         0x02
DECL|macro|ASI_SEGMAP
mdefine_line|#define ASI_SEGMAP          0x03
DECL|macro|ASI_PTE
mdefine_line|#define ASI_PTE             0x04
DECL|macro|ASI_HWFLUSHSEG
mdefine_line|#define ASI_HWFLUSHSEG      0x05
DECL|macro|ASI_HWFLUSHPAGE
mdefine_line|#define ASI_HWFLUSHPAGE     0x06
DECL|macro|ASI_REGMAP
mdefine_line|#define ASI_REGMAP          0x06
DECL|macro|ASI_HWFLUSHCONTEXT
mdefine_line|#define ASI_HWFLUSHCONTEXT  0x07
DECL|macro|ASI_USERTXT
mdefine_line|#define ASI_USERTXT         0x08
DECL|macro|ASI_KERNELTXT
mdefine_line|#define ASI_KERNELTXT       0x09
DECL|macro|ASI_USERDATA
mdefine_line|#define ASI_USERDATA        0x0a
DECL|macro|ASI_KERNELDATA
mdefine_line|#define ASI_KERNELDATA      0x0b
multiline_comment|/* VAC Cache flushing on sun4c and sun4 */
DECL|macro|ASI_FLUSHSEG
mdefine_line|#define ASI_FLUSHSEG        0x0c
DECL|macro|ASI_FLUSHPG
mdefine_line|#define ASI_FLUSHPG         0x0d
DECL|macro|ASI_FLUSHCTX
mdefine_line|#define ASI_FLUSHCTX        0x0e
multiline_comment|/* SPARCstation-5: only 6 bits are decoded. */
multiline_comment|/* wo = Write Only, rw = Read Write;        */
multiline_comment|/* ss = Single Size, as = All Sizes;        */
DECL|macro|ASI_M_RES00
mdefine_line|#define ASI_M_RES00         0x00   /* Don&squot;t touch... */
DECL|macro|ASI_M_UNA01
mdefine_line|#define ASI_M_UNA01         0x01   /* Same here... */
DECL|macro|ASI_M_MXCC
mdefine_line|#define ASI_M_MXCC          0x02   /* Access to TI VIKING MXCC registers */
DECL|macro|ASI_M_FLUSH_PROBE
mdefine_line|#define ASI_M_FLUSH_PROBE   0x03   /* Reference MMU Flush/Probe; rw, ss */
DECL|macro|ASI_M_MMUREGS
mdefine_line|#define ASI_M_MMUREGS       0x04   /* MMU Registers; rw, ss */
DECL|macro|ASI_M_TLBDIAG
mdefine_line|#define ASI_M_TLBDIAG       0x05   /* MMU TLB only Diagnostics */
DECL|macro|ASI_M_DIAGS
mdefine_line|#define ASI_M_DIAGS         0x06   /* Reference MMU Diagnostics */
DECL|macro|ASI_M_IODIAG
mdefine_line|#define ASI_M_IODIAG        0x07   /* MMU I/O TLB only Diagnostics */
DECL|macro|ASI_M_USERTXT
mdefine_line|#define ASI_M_USERTXT       0x08   /* Same as ASI_USERTXT; rw, as */
DECL|macro|ASI_M_KERNELTXT
mdefine_line|#define ASI_M_KERNELTXT     0x09   /* Same as ASI_KERNELTXT; rw, as */
DECL|macro|ASI_M_USERDATA
mdefine_line|#define ASI_M_USERDATA      0x0A   /* Same as ASI_USERDATA; rw, as */
DECL|macro|ASI_M_KERNELDATA
mdefine_line|#define ASI_M_KERNELDATA    0x0B   /* Same as ASI_KERNELDATA; rw, as */
DECL|macro|ASI_M_TXTC_TAG
mdefine_line|#define ASI_M_TXTC_TAG      0x0C   /* Instruction Cache Tag; rw, ss */
DECL|macro|ASI_M_TXTC_DATA
mdefine_line|#define ASI_M_TXTC_DATA     0x0D   /* Instruction Cache Data; rw, ss */
DECL|macro|ASI_M_DATAC_TAG
mdefine_line|#define ASI_M_DATAC_TAG     0x0E   /* Data Cache Tag; rw, ss */
DECL|macro|ASI_M_DATAC_DATA
mdefine_line|#define ASI_M_DATAC_DATA    0x0F   /* Data Cache Data; rw, ss */
multiline_comment|/* The following cache flushing ASIs work only with the &squot;sta&squot;&n; * instruction. Results are unpredictable for &squot;swap&squot; and &squot;ldstuba&squot;,&n; * so don&squot;t do it.&n; */
multiline_comment|/* These ASI flushes affect external caches too. */
DECL|macro|ASI_M_FLUSH_PAGE
mdefine_line|#define ASI_M_FLUSH_PAGE    0x10   /* Flush I&amp;D Cache Line (page); wo, ss */
DECL|macro|ASI_M_FLUSH_SEG
mdefine_line|#define ASI_M_FLUSH_SEG     0x11   /* Flush I&amp;D Cache Line (seg); wo, ss */
DECL|macro|ASI_M_FLUSH_REGION
mdefine_line|#define ASI_M_FLUSH_REGION  0x12   /* Flush I&amp;D Cache Line (region); wo, ss */
DECL|macro|ASI_M_FLUSH_CTX
mdefine_line|#define ASI_M_FLUSH_CTX     0x13   /* Flush I&amp;D Cache Line (context); wo, ss */
DECL|macro|ASI_M_FLUSH_USER
mdefine_line|#define ASI_M_FLUSH_USER    0x14   /* Flush I&amp;D Cache Line (user); wo, ss */
multiline_comment|/* Block-copy operations are available only on certain V8 cpus. */
DECL|macro|ASI_M_BCOPY
mdefine_line|#define ASI_M_BCOPY         0x17   /* Block copy */
multiline_comment|/* These affect only the ICACHE and are Ross HyperSparc and TurboSparc specific. */
DECL|macro|ASI_M_IFLUSH_PAGE
mdefine_line|#define ASI_M_IFLUSH_PAGE   0x18   /* Flush I Cache Line (page); wo, ss */
DECL|macro|ASI_M_IFLUSH_SEG
mdefine_line|#define ASI_M_IFLUSH_SEG    0x19   /* Flush I Cache Line (seg); wo, ss */
DECL|macro|ASI_M_IFLUSH_REGION
mdefine_line|#define ASI_M_IFLUSH_REGION 0x1A   /* Flush I Cache Line (region); wo, ss */
DECL|macro|ASI_M_IFLUSH_CTX
mdefine_line|#define ASI_M_IFLUSH_CTX    0x1B   /* Flush I Cache Line (context); wo, ss */
DECL|macro|ASI_M_IFLUSH_USER
mdefine_line|#define ASI_M_IFLUSH_USER   0x1C   /* Flush I Cache Line (user); wo, ss */
multiline_comment|/* Block-fill operations are available on certain V8 cpus */
DECL|macro|ASI_M_BFILL
mdefine_line|#define ASI_M_BFILL         0x1F
multiline_comment|/* This allows direct access to main memory, actually 0x20 to 0x2f are&n; * the available ASI&squot;s for physical ram pass-through, but I don&squot;t have&n; * any idea what the other ones do....&n; */
DECL|macro|ASI_M_BYPASS
mdefine_line|#define ASI_M_BYPASS       0x20   /* Reference MMU bypass; rw, as */
DECL|macro|ASI_M_FBMEM
mdefine_line|#define ASI_M_FBMEM        0x29   /* Graphics card frame buffer access */
DECL|macro|ASI_M_VMEUS
mdefine_line|#define ASI_M_VMEUS        0x2A   /* VME user 16-bit access */
DECL|macro|ASI_M_VMEPS
mdefine_line|#define ASI_M_VMEPS        0x2B   /* VME priv 16-bit access */
DECL|macro|ASI_M_VMEUT
mdefine_line|#define ASI_M_VMEUT        0x2C   /* VME user 32-bit access */
DECL|macro|ASI_M_VMEPT
mdefine_line|#define ASI_M_VMEPT        0x2D   /* VME priv 32-bit access */
DECL|macro|ASI_M_SBUS
mdefine_line|#define ASI_M_SBUS         0x2E   /* Direct SBus access */
DECL|macro|ASI_M_CTL
mdefine_line|#define ASI_M_CTL          0x2F   /* Control Space (ECC and MXCC are here) */
multiline_comment|/* This is ROSS HyperSparc only. */
DECL|macro|ASI_M_FLUSH_IWHOLE
mdefine_line|#define ASI_M_FLUSH_IWHOLE 0x31   /* Flush entire ICACHE; wo, ss */
multiline_comment|/* Tsunami/Viking/TurboSparc i/d cache flash clear. */
DECL|macro|ASI_M_IC_FLCLEAR
mdefine_line|#define ASI_M_IC_FLCLEAR   0x36
DECL|macro|ASI_M_DC_FLCLEAR
mdefine_line|#define ASI_M_DC_FLCLEAR   0x37
DECL|macro|ASI_M_DCDR
mdefine_line|#define ASI_M_DCDR         0x39   /* Data Cache Diagnostics Register rw, ss */
DECL|macro|ASI_M_VIKING_TMP1
mdefine_line|#define ASI_M_VIKING_TMP1  0x40&t;  /* Emulation temporary 1 on Viking */
DECL|macro|ASI_M_VIKING_TMP2
mdefine_line|#define ASI_M_VIKING_TMP2  0x41&t;  /* Emulation temporary 2 on Viking */
DECL|macro|ASI_M_ACTION
mdefine_line|#define ASI_M_ACTION       0x4c   /* Breakpoint Action Register (GNU/Viking) */
macro_line|#endif /* _SPARC_ASI_H */
eof
