multiline_comment|/* iommu.h: Definitions for the sun4m IOMMU.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_IOMMU_H
DECL|macro|_SPARC_IOMMU_H
mdefine_line|#define _SPARC_IOMMU_H
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/* The iommu handles all virtual to physical address translations&n; * that occur between the SBUS and physical memory.  Access by&n; * the cpu to IO registers and similar go over the mbus so are&n; * translated by the on chip SRMMU.  The iommu and the srmmu do&n; * not need to have the same translations at all, in fact most&n; * of the time the translations they handle are a disjunct set.&n; * Basically the iommu handles all dvma sbus activity.&n; */
multiline_comment|/* The IOMMU registers occupy three pages in IO space. */
DECL|struct|iommu_regs
r_struct
id|iommu_regs
(brace
multiline_comment|/* First page */
DECL|member|control
r_volatile
r_int
r_int
id|control
suffix:semicolon
multiline_comment|/* IOMMU control */
DECL|member|base
r_volatile
r_int
r_int
id|base
suffix:semicolon
multiline_comment|/* Physical base of iopte page table */
DECL|member|_unused1
r_volatile
r_int
r_int
id|_unused1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tlbflush
r_volatile
r_int
r_int
id|tlbflush
suffix:semicolon
multiline_comment|/* write only */
DECL|member|pageflush
r_volatile
r_int
r_int
id|pageflush
suffix:semicolon
multiline_comment|/* write only */
DECL|member|_unused2
r_volatile
r_int
r_int
id|_unused2
(braket
l_int|1017
)braket
suffix:semicolon
multiline_comment|/* Second page */
DECL|member|afsr
r_volatile
r_int
r_int
id|afsr
suffix:semicolon
multiline_comment|/* Async-fault status register */
DECL|member|afar
r_volatile
r_int
r_int
id|afar
suffix:semicolon
multiline_comment|/* Async-fault physical address */
DECL|member|_unused3
r_volatile
r_int
r_int
id|_unused3
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|sbuscfg0
r_volatile
r_int
r_int
id|sbuscfg0
suffix:semicolon
multiline_comment|/* SBUS configuration registers, per-slot */
DECL|member|sbuscfg1
r_volatile
r_int
r_int
id|sbuscfg1
suffix:semicolon
DECL|member|sbuscfg2
r_volatile
r_int
r_int
id|sbuscfg2
suffix:semicolon
DECL|member|sbuscfg3
r_volatile
r_int
r_int
id|sbuscfg3
suffix:semicolon
DECL|member|mfsr
r_volatile
r_int
r_int
id|mfsr
suffix:semicolon
multiline_comment|/* Memory-fault status register */
DECL|member|mfar
r_volatile
r_int
r_int
id|mfar
suffix:semicolon
multiline_comment|/* Memory-fault physical address */
DECL|member|_unused4
r_volatile
r_int
r_int
id|_unused4
(braket
l_int|1014
)braket
suffix:semicolon
multiline_comment|/* Third page */
DECL|member|mid
r_volatile
r_int
r_int
id|mid
suffix:semicolon
multiline_comment|/* IOMMU module-id */
)brace
suffix:semicolon
DECL|macro|IOMMU_CTRL_IMPL
mdefine_line|#define IOMMU_CTRL_IMPL     0xf0000000 /* Implementation */
DECL|macro|IOMMU_CTRL_VERS
mdefine_line|#define IOMMU_CTRL_VERS     0x0f000000 /* Version */
DECL|macro|IOMMU_CTRL_RNGE
mdefine_line|#define IOMMU_CTRL_RNGE     0x0000001c /* Mapping RANGE */
DECL|macro|IOMMU_RNGE_16MB
mdefine_line|#define IOMMU_RNGE_16MB     0x00000000 /* 0xff000000 -&gt; 0xffffffff */
DECL|macro|IOMMU_RNGE_32MB
mdefine_line|#define IOMMU_RNGE_32MB     0x00000004 /* 0xfe000000 -&gt; 0xffffffff */
DECL|macro|IOMMU_RNGE_64MB
mdefine_line|#define IOMMU_RNGE_64MB     0x00000008 /* 0xfc000000 -&gt; 0xffffffff */
DECL|macro|IOMMU_RNGE_128MB
mdefine_line|#define IOMMU_RNGE_128MB    0x0000000c /* 0xf8000000 -&gt; 0xffffffff */
DECL|macro|IOMMU_RNGE_256MB
mdefine_line|#define IOMMU_RNGE_256MB    0x00000010 /* 0xf0000000 -&gt; 0xffffffff */
DECL|macro|IOMMU_RNGE_512MB
mdefine_line|#define IOMMU_RNGE_512MB    0x00000014 /* 0xe0000000 -&gt; 0xffffffff */
DECL|macro|IOMMU_RNGE_1GB
mdefine_line|#define IOMMU_RNGE_1GB      0x00000018 /* 0xc0000000 -&gt; 0xffffffff */
DECL|macro|IOMMU_RNGE_2GB
mdefine_line|#define IOMMU_RNGE_2GB      0x0000001c /* 0x80000000 -&gt; 0xffffffff */
DECL|macro|IOMMU_CTRL_ENAB
mdefine_line|#define IOMMU_CTRL_ENAB     0x00000001 /* IOMMU Enable */
DECL|macro|IOMMU_AFSR_ERR
mdefine_line|#define IOMMU_AFSR_ERR      0x80000000 /* LE, TO, or BE asserted */
DECL|macro|IOMMU_AFSR_LE
mdefine_line|#define IOMMU_AFSR_LE       0x40000000 /* SBUS reports error after transaction */
DECL|macro|IOMMU_AFSR_TO
mdefine_line|#define IOMMU_AFSR_TO       0x20000000 /* Write access took more than 12.8 us. */
DECL|macro|IOMMU_AFSR_BE
mdefine_line|#define IOMMU_AFSR_BE       0x10000000 /* Write access received error acknowledge */
DECL|macro|IOMMU_AFSR_SIZE
mdefine_line|#define IOMMU_AFSR_SIZE     0x0e000000 /* Size of transaction causing error */
DECL|macro|IOMMU_AFSR_S
mdefine_line|#define IOMMU_AFSR_S        0x01000000 /* Sparc was in supervisor mode */
DECL|macro|IOMMU_AFSR_RESV
mdefine_line|#define IOMMU_AFSR_RESV     0x00f00000 /* Reserver, forced to 0x8 by hardware */
DECL|macro|IOMMU_AFSR_ME
mdefine_line|#define IOMMU_AFSR_ME       0x00080000 /* Multiple errors occurred */
DECL|macro|IOMMU_AFSR_RD
mdefine_line|#define IOMMU_AFSR_RD       0x00040000 /* A read operation was in progress */
DECL|macro|IOMMU_AFSR_FAV
mdefine_line|#define IOMMU_AFSR_FAV      0x00020000 /* IOMMU afar has valid contents */
DECL|macro|IOMMU_SBCFG_SAB30
mdefine_line|#define IOMMU_SBCFG_SAB30   0x00010000 /* Phys-address bit 30 when bypass enabled */
DECL|macro|IOMMU_SBCFG_BA16
mdefine_line|#define IOMMU_SBCFG_BA16    0x00000004 /* Slave supports 16 byte bursts */
DECL|macro|IOMMU_SBCFG_BA8
mdefine_line|#define IOMMU_SBCFG_BA8     0x00000002 /* Slave supports 8 byte bursts */
DECL|macro|IOMMU_SBCFG_BYPASS
mdefine_line|#define IOMMU_SBCFG_BYPASS  0x00000001 /* Bypass IOMMU, treat all addresses&n;&t;&t;&t;&t;&t;  produced by this device as pure&n;&t;&t;&t;&t;&t;  physical. */
DECL|macro|IOMMU_MFSR_ERR
mdefine_line|#define IOMMU_MFSR_ERR      0x80000000 /* One or more of PERR1 or PERR0 */
DECL|macro|IOMMU_MFSR_S
mdefine_line|#define IOMMU_MFSR_S        0x01000000 /* Sparc was in supervisor mode */
DECL|macro|IOMMU_MFSR_CPU
mdefine_line|#define IOMMU_MFSR_CPU      0x00800000 /* CPU transaction caused parity error */
DECL|macro|IOMMU_MFSR_ME
mdefine_line|#define IOMMU_MFSR_ME       0x00080000 /* Multiple parity errors occurred */
DECL|macro|IOMMU_MFSR_PERR
mdefine_line|#define IOMMU_MFSR_PERR     0x00006000 /* high bit indicates parity error occurred&n;&t;&t;&t;&t;&t;  on the even word of the access, low bit&n;&t;&t;&t;&t;&t;  indicated odd word caused the parity error */
DECL|macro|IOMMU_MFSR_BM
mdefine_line|#define IOMMU_MFSR_BM       0x00001000 /* Error occurred while in boot mode */
DECL|macro|IOMMU_MFSR_C
mdefine_line|#define IOMMU_MFSR_C        0x00000800 /* Address causing error was marked cacheable */
DECL|macro|IOMMU_MFSR_RTYP
mdefine_line|#define IOMMU_MFSR_RTYP     0x000000f0 /* Memory request transaction type */
DECL|macro|IOMMU_MID_SBAE
mdefine_line|#define IOMMU_MID_SBAE      0x001f0000 /* SBus arbitration enable */
DECL|macro|IOMMU_MID_SE
mdefine_line|#define IOMMU_MID_SE        0x00100000 /* Enables SCSI/ETHERNET arbitration */
DECL|macro|IOMMU_MID_SB3
mdefine_line|#define IOMMU_MID_SB3       0x00080000 /* Enable SBUS device 3 arbitration */
DECL|macro|IOMMU_MID_SB2
mdefine_line|#define IOMMU_MID_SB2       0x00040000 /* Enable SBUS device 2 arbitration */
DECL|macro|IOMMU_MID_SB1
mdefine_line|#define IOMMU_MID_SB1       0x00020000 /* Enable SBUS device 1 arbitration */
DECL|macro|IOMMU_MID_SB0
mdefine_line|#define IOMMU_MID_SB0       0x00010000 /* Enable SBUS device 0 arbitration */
DECL|macro|IOMMU_MID_MID
mdefine_line|#define IOMMU_MID_MID       0x0000000f /* Module-id, hardcoded to 0x8 */
multiline_comment|/* The format of an iopte in the page tables */
DECL|macro|IOPTE_PAGE
mdefine_line|#define IOPTE_PAGE          0x07ffff00 /* Physical page number (PA[30:12]) */
DECL|macro|IOPTE_CACHE
mdefine_line|#define IOPTE_CACHE         0x00000080 /* Cached (in vme IOCACHE or Viking/MXCC) */
DECL|macro|IOPTE_WRITE
mdefine_line|#define IOPTE_WRITE         0x00000004 /* Writeable */
DECL|macro|IOPTE_VALID
mdefine_line|#define IOPTE_VALID         0x00000002 /* IOPTE is valid */
DECL|macro|IOPTE_WAZ
mdefine_line|#define IOPTE_WAZ           0x00000001 /* Write as zeros */
DECL|struct|iommu_struct
r_struct
id|iommu_struct
(brace
DECL|member|regs
r_struct
id|iommu_regs
op_star
id|regs
suffix:semicolon
DECL|member|page_table
id|iopte_t
op_star
id|page_table
suffix:semicolon
DECL|member|lowest
id|iopte_t
op_star
id|lowest
suffix:semicolon
multiline_comment|/* to speed up searches... */
DECL|member|plow
r_int
r_int
id|plow
suffix:semicolon
multiline_comment|/* For convenience */
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
multiline_comment|/* First managed virtual address */
DECL|member|end
r_int
r_int
id|end
suffix:semicolon
multiline_comment|/* Last managed virtual address */
)brace
suffix:semicolon
DECL|function|iommu_invalidate
r_extern
id|__inline__
r_void
id|iommu_invalidate
c_func
(paren
r_struct
id|iommu_regs
op_star
id|regs
)paren
(brace
id|regs-&gt;tlbflush
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|iommu_invalidate_page
r_extern
id|__inline__
r_void
id|iommu_invalidate_page
c_func
(paren
r_struct
id|iommu_regs
op_star
id|regs
comma
r_int
r_int
id|page
)paren
(brace
id|regs-&gt;pageflush
op_assign
(paren
id|page
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
)brace
macro_line|#endif /* !(_SPARC_IOMMU_H) */
eof
