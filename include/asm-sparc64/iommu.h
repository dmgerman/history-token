multiline_comment|/* $Id: iommu.h,v 1.9 1999/09/21 14:39:39 davem Exp $&n; * iommu.h: Definitions for the sun5 IOMMU.&n; *&n; * Copyright (C) 1996, 1999 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_IOMMU_H
DECL|macro|_SPARC64_IOMMU_H
mdefine_line|#define _SPARC64_IOMMU_H
multiline_comment|/* The format of an iopte in the page tables. */
DECL|macro|IOPTE_VALID
mdefine_line|#define IOPTE_VALID         0x8000000000000000 /* IOPTE is valid                   */
DECL|macro|IOPTE_64K
mdefine_line|#define IOPTE_64K           0x2000000000000000 /* IOPTE is for 64k page            */
DECL|macro|IOPTE_STBUF
mdefine_line|#define IOPTE_STBUF         0x1000000000000000 /* DVMA can use streaming buffer    */
DECL|macro|IOPTE_INTRA
mdefine_line|#define IOPTE_INTRA         0x0800000000000000 /* SBUS slot--&gt;slot direct transfer */
DECL|macro|IOPTE_CONTEXT
mdefine_line|#define IOPTE_CONTEXT&t;    0x07ff800000000000 /* Context number&t;&t;   */
DECL|macro|IOPTE_PAGE
mdefine_line|#define IOPTE_PAGE          0x00007fffffffe000 /* Physical page number (PA[40:13]) */
DECL|macro|IOPTE_CACHE
mdefine_line|#define IOPTE_CACHE         0x0000000000000010 /* Cached (in UPA E-cache)          */
DECL|macro|IOPTE_WRITE
mdefine_line|#define IOPTE_WRITE         0x0000000000000002 /* Writeable                        */
macro_line|#endif /* !(_SPARC_IOMMU_H) */
eof
