multiline_comment|/* $Id: iommu_common.h,v 1.1 1999/12/17 12:31:54 jj Exp $&n; * iommu_common.h: UltraSparc SBUS/PCI common iommu declarations.&n; *&n; * Copyright (C) 1999 David S. Miller (davem@redhat.com)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/iommu.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
multiline_comment|/* You are _strongly_ advised to enable the following debugging code&n; * any time you make changes to the sg code below, run it for a while&n; * with filesystems mounted read-only before buying the farm... -DaveM&n; */
DECL|macro|VERIFY_SG
macro_line|#undef VERIFY_SG
macro_line|#ifdef VERIFY_SG
r_int
id|verify_lengths
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
r_int
id|npages
)paren
suffix:semicolon
r_int
id|verify_one_map
c_func
(paren
r_struct
id|scatterlist
op_star
id|dma_sg
comma
r_struct
id|scatterlist
op_star
op_star
id|__sg
comma
r_int
id|nents
comma
id|iopte_t
op_star
op_star
id|__iopte
)paren
suffix:semicolon
r_int
id|verify_maps
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
)paren
suffix:semicolon
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
