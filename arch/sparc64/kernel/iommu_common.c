multiline_comment|/* $Id: iommu_common.c,v 1.5 2001/08/24 17:57:51 kanoj Exp $&n; * iommu_common.c: UltraSparc SBUS/PCI common iommu code.&n; *&n; * Copyright (C) 1999 David S. Miller (davem@redhat.com)&n; */
macro_line|#include &quot;iommu_common.h&quot;
multiline_comment|/* You are _strongly_ advised to enable the following debugging code&n; * any time you make changes to the sg code below, run it for a while&n; * with filesystems mounted read-only before buying the farm... -DaveM&n; */
macro_line|#ifdef VERIFY_SG
DECL|function|verify_lengths
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
(brace
r_int
id|sg_len
comma
id|dma_len
suffix:semicolon
r_int
id|i
comma
id|pgcount
suffix:semicolon
id|sg_len
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nents
suffix:semicolon
id|i
op_increment
)paren
id|sg_len
op_add_assign
id|sg
(braket
id|i
)braket
dot
id|length
suffix:semicolon
id|dma_len
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nents
op_logical_and
id|sg
(braket
id|i
)braket
dot
id|dvma_length
suffix:semicolon
id|i
op_increment
)paren
id|dma_len
op_add_assign
id|sg
(braket
id|i
)braket
dot
id|dvma_length
suffix:semicolon
r_if
c_cond
(paren
id|sg_len
op_ne
id|dma_len
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;verify_lengths: Error, different, sg[%d] dma[%d]&bslash;n&quot;
comma
id|sg_len
comma
id|dma_len
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|pgcount
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nents
op_logical_and
id|sg
(braket
id|i
)braket
dot
id|dvma_length
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|start
comma
id|end
suffix:semicolon
id|start
op_assign
id|sg
(braket
id|i
)braket
dot
id|dvma_address
suffix:semicolon
id|start
op_assign
id|start
op_amp
id|IO_PAGE_MASK
suffix:semicolon
id|end
op_assign
id|sg
(braket
id|i
)braket
dot
id|dvma_address
op_plus
id|sg
(braket
id|i
)braket
dot
id|dvma_length
suffix:semicolon
id|end
op_assign
(paren
id|end
op_plus
(paren
id|IO_PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_amp
id|IO_PAGE_MASK
suffix:semicolon
id|pgcount
op_add_assign
(paren
(paren
id|end
op_minus
id|start
)paren
op_rshift
id|IO_PAGE_SHIFT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pgcount
op_ne
id|npages
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;verify_lengths: Error, page count wrong, &quot;
l_string|&quot;npages[%d] pgcount[%d]&bslash;n&quot;
comma
id|npages
comma
id|pgcount
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* This test passes... */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|verify_one_map
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
(brace
r_struct
id|scatterlist
op_star
id|sg
op_assign
op_star
id|__sg
suffix:semicolon
id|iopte_t
op_star
id|iopte
op_assign
op_star
id|__iopte
suffix:semicolon
id|u32
id|dlen
op_assign
id|dma_sg-&gt;dvma_length
suffix:semicolon
id|u32
id|daddr
op_assign
id|dma_sg-&gt;dvma_address
suffix:semicolon
r_int
r_int
id|sglen
suffix:semicolon
r_int
r_int
id|sgaddr
suffix:semicolon
id|sglen
op_assign
id|sg-&gt;length
suffix:semicolon
id|sgaddr
op_assign
(paren
r_int
r_int
)paren
id|sg-&gt;address
suffix:semicolon
r_while
c_loop
(paren
id|dlen
OG
l_int|0
)paren
(brace
r_int
r_int
id|paddr
suffix:semicolon
multiline_comment|/* SG and DMA_SG must begin at the same sub-page boundary. */
r_if
c_cond
(paren
(paren
id|sgaddr
op_amp
op_complement
id|IO_PAGE_MASK
)paren
op_ne
(paren
id|daddr
op_amp
op_complement
id|IO_PAGE_MASK
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;verify_one_map: Wrong start offset &quot;
l_string|&quot;sg[%08lx] dma[%08x]&bslash;n&quot;
comma
id|sgaddr
comma
id|daddr
)paren
suffix:semicolon
id|nents
op_assign
op_minus
l_int|1
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Verify the IOPTE points to the right page. */
id|paddr
op_assign
id|iopte_val
c_func
(paren
op_star
id|iopte
)paren
op_amp
id|IOPTE_PAGE
suffix:semicolon
r_if
c_cond
(paren
(paren
id|paddr
op_plus
id|PAGE_OFFSET
)paren
op_ne
(paren
id|sgaddr
op_amp
id|IO_PAGE_MASK
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;verify_one_map: IOPTE[%08lx] maps the &quot;
l_string|&quot;wrong page, should be [%08lx]&bslash;n&quot;
comma
id|iopte_val
c_func
(paren
op_star
id|iopte
)paren
comma
(paren
id|sgaddr
op_amp
id|IO_PAGE_MASK
)paren
op_minus
id|PAGE_OFFSET
)paren
suffix:semicolon
id|nents
op_assign
op_minus
l_int|1
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* If this SG crosses a page, adjust to that next page&n;&t;&t; * boundary and loop.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|sgaddr
op_amp
id|IO_PAGE_MASK
)paren
op_xor
(paren
(paren
id|sgaddr
op_plus
id|sglen
op_minus
l_int|1
)paren
op_amp
id|IO_PAGE_MASK
)paren
)paren
(brace
r_int
r_int
id|next_page
comma
id|diff
suffix:semicolon
id|next_page
op_assign
(paren
id|sgaddr
op_plus
id|IO_PAGE_SIZE
)paren
op_amp
id|IO_PAGE_MASK
suffix:semicolon
id|diff
op_assign
id|next_page
op_minus
id|sgaddr
suffix:semicolon
id|sgaddr
op_add_assign
id|diff
suffix:semicolon
id|daddr
op_add_assign
id|diff
suffix:semicolon
id|sglen
op_sub_assign
id|diff
suffix:semicolon
id|dlen
op_sub_assign
id|diff
suffix:semicolon
r_if
c_cond
(paren
id|dlen
OG
l_int|0
)paren
id|iopte
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* SG wholly consumed within this page. */
id|daddr
op_add_assign
id|sglen
suffix:semicolon
id|dlen
op_sub_assign
id|sglen
suffix:semicolon
r_if
c_cond
(paren
id|dlen
OG
l_int|0
op_logical_and
(paren
(paren
id|daddr
op_amp
op_complement
id|IO_PAGE_MASK
)paren
op_eq
l_int|0
)paren
)paren
id|iopte
op_increment
suffix:semicolon
id|sg
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|nents
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|sgaddr
op_assign
(paren
r_int
r_int
)paren
id|sg-&gt;address
suffix:semicolon
id|sglen
op_assign
id|sg-&gt;length
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dlen
OL
l_int|0
)paren
(brace
multiline_comment|/* Transfer overrun, big problems. */
id|printk
c_func
(paren
l_string|&quot;verify_one_map: Transfer overrun by %d bytes.&bslash;n&quot;
comma
op_minus
id|dlen
)paren
suffix:semicolon
id|nents
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Advance to next dma_sg implies that the next iopte will&n;&t;&t; * begin it.&n;&t;&t; */
id|iopte
op_increment
suffix:semicolon
)brace
id|out
suffix:colon
op_star
id|__sg
op_assign
id|sg
suffix:semicolon
op_star
id|__iopte
op_assign
id|iopte
suffix:semicolon
r_return
id|nents
suffix:semicolon
)brace
DECL|function|verify_maps
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
(brace
r_struct
id|scatterlist
op_star
id|dma_sg
op_assign
id|sg
suffix:semicolon
r_struct
id|scatterlist
op_star
id|orig_dma_sg
op_assign
id|dma_sg
suffix:semicolon
r_int
id|orig_nents
op_assign
id|nents
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|nents
op_assign
id|verify_one_map
c_func
(paren
id|dma_sg
comma
op_amp
id|sg
comma
id|nents
comma
op_amp
id|iopte
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nents
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|dma_sg
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|dma_sg-&gt;dvma_length
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nents
OG
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;verify_maps: dma maps consumed by some sgs remain (%d)&bslash;n&quot;
comma
id|nents
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nents
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;verify_maps: Error, messed up mappings, &quot;
l_string|&quot;at sg %d dma_sg %d&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
id|orig_nents
op_plus
id|nents
)paren
comma
(paren
r_int
)paren
(paren
id|dma_sg
op_minus
id|orig_dma_sg
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* This test passes... */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|verify_sglist
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
(brace
r_if
c_cond
(paren
id|verify_lengths
c_func
(paren
id|sg
comma
id|nents
comma
id|npages
)paren
OL
l_int|0
op_logical_or
id|verify_maps
c_func
(paren
id|sg
comma
id|nents
comma
id|iopte
)paren
OL
l_int|0
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;verify_sglist: Crap, messed up mappings, dumping, iodma at %08x.&bslash;n&quot;
comma
(paren
id|u32
)paren
(paren
id|sg-&gt;dvma_address
op_amp
id|IO_PAGE_MASK
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nents
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sg(%d): address(%p) length(%x) &quot;
l_string|&quot;dma_address[%08x] dma_length[%08x]&bslash;n&quot;
comma
id|i
comma
id|sg
(braket
id|i
)braket
dot
id|address
comma
id|sg
(braket
id|i
)braket
dot
id|length
comma
id|sg
(braket
id|i
)braket
dot
id|dvma_address
comma
id|sg
(braket
id|i
)braket
dot
id|dvma_length
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Seems to be ok */
)brace
macro_line|#endif
DECL|function|prepare_sg
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
(brace
r_struct
id|scatterlist
op_star
id|dma_sg
op_assign
id|sg
suffix:semicolon
r_int
r_int
id|prev
suffix:semicolon
id|u32
id|dent_addr
comma
id|dent_len
suffix:semicolon
id|prev
op_assign
(paren
r_int
r_int
)paren
id|sg-&gt;address
suffix:semicolon
id|prev
op_add_assign
(paren
r_int
r_int
)paren
(paren
id|dent_len
op_assign
id|sg-&gt;length
)paren
suffix:semicolon
id|dent_addr
op_assign
(paren
id|u32
)paren
(paren
(paren
r_int
r_int
)paren
id|sg-&gt;address
op_amp
(paren
id|IO_PAGE_SIZE
op_minus
l_int|1UL
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|nents
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|sg
op_increment
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|sg-&gt;address
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|VCONTIG
c_func
(paren
id|prev
comma
id|addr
)paren
)paren
(brace
id|dma_sg-&gt;dvma_address
op_assign
id|dent_addr
suffix:semicolon
id|dma_sg-&gt;dvma_length
op_assign
id|dent_len
suffix:semicolon
id|dma_sg
op_increment
suffix:semicolon
id|dent_addr
op_assign
(paren
(paren
id|dent_addr
op_plus
id|dent_len
op_plus
(paren
id|IO_PAGE_SIZE
op_minus
l_int|1UL
)paren
)paren
op_rshift
id|IO_PAGE_SHIFT
)paren
suffix:semicolon
id|dent_addr
op_lshift_assign
id|IO_PAGE_SHIFT
suffix:semicolon
id|dent_addr
op_add_assign
id|addr
op_amp
(paren
id|IO_PAGE_SIZE
op_minus
l_int|1UL
)paren
suffix:semicolon
id|dent_len
op_assign
l_int|0
suffix:semicolon
)brace
id|dent_len
op_add_assign
id|sg-&gt;length
suffix:semicolon
id|prev
op_assign
id|addr
op_plus
id|sg-&gt;length
suffix:semicolon
)brace
id|dma_sg-&gt;dvma_address
op_assign
id|dent_addr
suffix:semicolon
id|dma_sg-&gt;dvma_length
op_assign
id|dent_len
suffix:semicolon
r_return
(paren
(paren
r_int
r_int
)paren
id|dent_addr
op_plus
(paren
r_int
r_int
)paren
id|dent_len
op_plus
(paren
id|IO_PAGE_SIZE
op_minus
l_int|1UL
)paren
)paren
op_rshift
id|IO_PAGE_SHIFT
suffix:semicolon
)brace
eof
