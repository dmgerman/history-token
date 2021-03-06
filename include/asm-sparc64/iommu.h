multiline_comment|/* $Id: iommu.h,v 1.10 2001/03/08 09:55:56 davem Exp $&n; * iommu.h: Definitions for the sun5 IOMMU.&n; *&n; * Copyright (C) 1996, 1999 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_IOMMU_H
DECL|macro|_SPARC64_IOMMU_H
mdefine_line|#define _SPARC64_IOMMU_H
multiline_comment|/* The format of an iopte in the page tables. */
DECL|macro|IOPTE_VALID
mdefine_line|#define IOPTE_VALID   0x8000000000000000UL /* IOPTE is valid                  */
DECL|macro|IOPTE_64K
mdefine_line|#define IOPTE_64K     0x2000000000000000UL /* IOPTE is for 64k page           */
DECL|macro|IOPTE_STBUF
mdefine_line|#define IOPTE_STBUF   0x1000000000000000UL /* DVMA can use streaming buffer   */
DECL|macro|IOPTE_INTRA
mdefine_line|#define IOPTE_INTRA   0x0800000000000000UL /* SBUS slot--&gt;slot direct transfer*/
DECL|macro|IOPTE_CONTEXT
mdefine_line|#define IOPTE_CONTEXT 0x07ff800000000000UL /* Context number&t;&t;      */
DECL|macro|IOPTE_PAGE
mdefine_line|#define IOPTE_PAGE    0x00007fffffffe000UL /* Physical page number (PA[42:13])*/
DECL|macro|IOPTE_CACHE
mdefine_line|#define IOPTE_CACHE   0x0000000000000010UL /* Cached (in UPA E-cache)         */
DECL|macro|IOPTE_WRITE
mdefine_line|#define IOPTE_WRITE   0x0000000000000002UL /* Writeable                       */
macro_line|#endif /* !(_SPARC_IOMMU_H) */
eof
