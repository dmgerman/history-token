multiline_comment|/* $Id: iommu_common.h,v 1.5 2001/12/11 09:41:01 davem Exp $&n; * iommu_common.h: UltraSparc SBUS/PCI common iommu declarations.&n; *&n; * Copyright (C) 1999 David S. Miller (davem@redhat.com)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/iommu.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
multiline_comment|/*&n; * These give mapping size of each iommu pte/tlb.&n; */
DECL|macro|IO_PAGE_SHIFT
mdefine_line|#define IO_PAGE_SHIFT&t;&t;&t;13
DECL|macro|IO_PAGE_SIZE
mdefine_line|#define IO_PAGE_SIZE&t;&t;&t;(1UL &lt;&lt; IO_PAGE_SHIFT)
DECL|macro|IO_PAGE_MASK
mdefine_line|#define IO_PAGE_MASK&t;&t;&t;(~(IO_PAGE_SIZE-1))
DECL|macro|IO_PAGE_ALIGN
mdefine_line|#define IO_PAGE_ALIGN(addr)&t;&t;(((addr)+IO_PAGE_SIZE-1)&amp;IO_PAGE_MASK)
DECL|macro|IO_TSB_ENTRIES
mdefine_line|#define IO_TSB_ENTRIES&t;&t;&t;(128*1024)
DECL|macro|IO_TSB_SIZE
mdefine_line|#define IO_TSB_SIZE&t;&t;&t;(IO_TSB_ENTRIES * 8)
multiline_comment|/*&n; * This is the hardwired shift in the iotlb tag/data parts.&n; */
DECL|macro|IOMMU_PAGE_SHIFT
mdefine_line|#define IOMMU_PAGE_SHIFT&t;&t;13
multiline_comment|/* You are _strongly_ advised to enable the following debugging code&n; * any time you make changes to the sg code below, run it for a while&n; * with filesystems mounted read-only before buying the farm... -DaveM&n; */
DECL|macro|VERIFY_SG
macro_line|#undef VERIFY_SG
macro_line|#ifdef VERIFY_SG
r_extern
r_void
id|verify_sglist
c_func
(paren
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nents
comma
id|iopte_t
op_star
id|iopte
comma
r_int
id|npages
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Two addresses are &quot;virtually contiguous&quot; if and only if:&n; * 1) They are equal, or...&n; * 2) They are both on a page boundry&n; */
DECL|macro|VCONTIG
mdefine_line|#define VCONTIG(__X, __Y)&t;(((__X) == (__Y)) || &bslash;&n;&t;&t;&t;&t; (((__X) | (__Y)) &lt;&lt; (64UL - PAGE_SHIFT)) == 0UL)
r_extern
r_int
r_int
id|prepare_sg
c_func
(paren
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nents
)paren
suffix:semicolon
eof
