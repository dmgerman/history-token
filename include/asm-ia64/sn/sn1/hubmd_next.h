multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SN1_HUBMD_NEXT_H
DECL|macro|_ASM_IA64_SN_SN1_HUBMD_NEXT_H
mdefine_line|#define _ASM_IA64_SN_SN1_HUBMD_NEXT_H
multiline_comment|/* XXX moved over from SN/SN0/hubmd.h -- each should be checked for SN1 */
multiline_comment|/* In fact, most of this stuff is wrong. Some is correct, such as&n; * MD_PAGE_SIZE and MD_PAGE_NUM_SHFT.&n; */
DECL|macro|MD_PERF_COUNTERS
mdefine_line|#define MD_PERF_COUNTERS        6
DECL|macro|MD_PERF_SETS
mdefine_line|#define MD_PERF_SETS            6
DECL|macro|MD_SIZE_EMPTY
mdefine_line|#define MD_SIZE_EMPTY           0       
DECL|macro|MD_SIZE_64MB
mdefine_line|#define MD_SIZE_64MB            1       
DECL|macro|MD_SIZE_128MB
mdefine_line|#define MD_SIZE_128MB           2       
DECL|macro|MD_SIZE_256MB
mdefine_line|#define MD_SIZE_256MB           3
DECL|macro|MD_SIZE_512MB
mdefine_line|#define MD_SIZE_512MB           4      
DECL|macro|MD_SIZE_1GB
mdefine_line|#define MD_SIZE_1GB             5      
DECL|macro|MD_SIZE_BYTES
mdefine_line|#define MD_SIZE_BYTES(size)     ((size) == 0 ? 0 : 0x2000000L &lt;&lt; (size))
DECL|macro|MD_SIZE_MBYTES
mdefine_line|#define MD_SIZE_MBYTES(size)    ((size) == 0 ? 0 :   0x20       &lt;&lt; (size))
DECL|macro|MD_NUM_ENABLED
mdefine_line|#define MD_NUM_ENABLED(_x)&t;((_x &amp; 0x1) + ((_x &gt;&gt; 1) &amp; 0x1) + &bslash;&n;&t;&t;&t;&t;((_x &gt;&gt; 2) &amp; 0x1) + ((_x &gt;&gt; 3) &amp; 0x1))
multiline_comment|/* Hardware page size and shift */
DECL|macro|MD_PAGE_SIZE
mdefine_line|#define MD_PAGE_SIZE            16384    /* Page size in bytes              */
DECL|macro|MD_PAGE_NUM_SHFT
mdefine_line|#define MD_PAGE_NUM_SHFT        14       /* Address to page number shift    */
DECL|macro|MMC_IO_PROT
mdefine_line|#define MMC_IO_PROT &t;&t;(UINT64_CAST 1 &lt;&lt; 45)
multiline_comment|/* Register offsets from LOCAL_HUB or REMOTE_HUB */
DECL|macro|MD_PERF_SEL
mdefine_line|#define MD_PERF_SEL             0x210000 /* Select perf monitor events      */
multiline_comment|/* MD_MIG_VALUE_THRESH bit definitions */
DECL|macro|MD_MIG_VALUE_THRES_VALID_MASK
mdefine_line|#define MD_MIG_VALUE_THRES_VALID_MASK (UINT64_CAST 0x1 &lt;&lt; 63)
DECL|macro|MD_MIG_VALUE_THRES_VALUE_MASK
mdefine_line|#define MD_MIG_VALUE_THRES_VALUE_MASK (UINT64_CAST 0xfffff)
multiline_comment|/* MD_MIG_CANDIDATE bit definitions */
DECL|macro|MD_MIG_CANDIDATE_VALID_MASK
mdefine_line|#define MD_MIG_CANDIDATE_VALID_MASK (UINT64_CAST 0x1 &lt;&lt; 63)
DECL|macro|MD_MIG_CANDIDATE_VALID_SHFT
mdefine_line|#define MD_MIG_CANDIDATE_VALID_SHFT 63
DECL|macro|MD_MIG_CANDIDATE_TYPE_MASK
mdefine_line|#define MD_MIG_CANDIDATE_TYPE_MASK (UINT64_CAST 0x1 &lt;&lt; 30)
DECL|macro|MD_MIG_CANDIDATE_TYPE_SHFT
mdefine_line|#define MD_MIG_CANDIDATE_TYPE_SHFT 30
DECL|macro|MD_MIG_CANDIDATE_OVERRUN_MASK
mdefine_line|#define MD_MIG_CANDIDATE_OVERRUN_MASK (UINT64_CAST 0x1 &lt;&lt; 29)
DECL|macro|MD_MIG_CANDIDATE_OVERRUN_SHFT
mdefine_line|#define MD_MIG_CANDIDATE_OVERRUN_SHFT 29
DECL|macro|MD_MIG_CANDIDATE_NODEID_MASK
mdefine_line|#define MD_MIG_CANDIDATE_NODEID_MASK (UINT64_CAST 0x1ff &lt;&lt; 20)
DECL|macro|MD_MIG_CANDIDATE_NODEID_SHFT
mdefine_line|#define MD_MIG_CANDIDATE_NODEID_SHFT 20
DECL|macro|MD_MIG_CANDIDATE_ADDR_MASK
mdefine_line|#define MD_MIG_CANDIDATE_ADDR_MASK (UINT64_CAST 0x3ffff)
multiline_comment|/* XXX protection and migration are completely revised on SN1.  On&n;   SN0, the reference count and protection fields were accessed in the&n;   same word, but on SN1 they reside at different addresses.  The&n;   users of these macros will need to be rewritten.  Also, the MD page&n;   size is 16K on SN1 but 4K on SN0.  */
multiline_comment|/* Premium SIMM protection entry shifts and masks. */
DECL|macro|MD_PPROT_SHFT
mdefine_line|#define MD_PPROT_SHFT           0                       /* Prot. field      */
DECL|macro|MD_PPROT_MASK
mdefine_line|#define MD_PPROT_MASK           0xf
DECL|macro|MD_PPROT_REFCNT_SHFT
mdefine_line|#define MD_PPROT_REFCNT_SHFT    5                       /* Reference count  */
DECL|macro|MD_PPROT_REFCNT_WIDTH
mdefine_line|#define MD_PPROT_REFCNT_WIDTH   0x7ffff
DECL|macro|MD_PPROT_REFCNT_MASK
mdefine_line|#define MD_PPROT_REFCNT_MASK    (MD_PPROT_REFCNT_WIDTH &lt;&lt; 5)
DECL|macro|MD_PPROT_IO_SHFT
mdefine_line|#define MD_PPROT_IO_SHFT        8                       /* I/O Prot field   */
multiline_comment|/* Standard SIMM protection entry shifts and masks. */
DECL|macro|MD_SPROT_SHFT
mdefine_line|#define MD_SPROT_SHFT           0                       /* Prot. field      */
DECL|macro|MD_SPROT_MASK
mdefine_line|#define MD_SPROT_MASK           0xf
DECL|macro|MD_SPROT_IO_SHFT
mdefine_line|#define MD_SPROT_IO_SHFT&t;8
DECL|macro|MD_SPROT_REFCNT_SHFT
mdefine_line|#define MD_SPROT_REFCNT_SHFT    5                       /* Reference count  */
DECL|macro|MD_SPROT_REFCNT_WIDTH
mdefine_line|#define MD_SPROT_REFCNT_WIDTH   0x7ff
DECL|macro|MD_SPROT_REFCNT_MASK
mdefine_line|#define MD_SPROT_REFCNT_MASK    (MD_SPROT_REFCNT_WIDTH &lt;&lt; 5)
multiline_comment|/* Migration modes used in protection entries */
DECL|macro|MD_PROT_MIGMD_IREL
mdefine_line|#define MD_PROT_MIGMD_IREL      (UINT64_CAST 0x3 &lt;&lt; 3)
DECL|macro|MD_PROT_MIGMD_IABS
mdefine_line|#define MD_PROT_MIGMD_IABS      (UINT64_CAST 0x2 &lt;&lt; 3)
DECL|macro|MD_PROT_MIGMD_PREL
mdefine_line|#define MD_PROT_MIGMD_PREL      (UINT64_CAST 0x1 &lt;&lt; 3)
DECL|macro|MD_PROT_MIGMD_OFF
mdefine_line|#define MD_PROT_MIGMD_OFF       (UINT64_CAST 0x0 &lt;&lt; 3)
multiline_comment|/*&n; * Operations on Memory/Directory DIMM control register&n; */
DECL|macro|DIRTYPE_PREMIUM
mdefine_line|#define DIRTYPE_PREMIUM 1
DECL|macro|DIRTYPE_STANDARD
mdefine_line|#define DIRTYPE_STANDARD 0
multiline_comment|/*&n; * Operations on page migration count difference and absolute threshold&n; * registers&n; */
DECL|macro|MD_MIG_VALUE_THRESH_GET
mdefine_line|#define MD_MIG_VALUE_THRESH_GET(region) (                               &bslash;&n;        REMOTE_HUB_L((region), MD_MIG_VALUE_THRESH) &amp;  &bslash;&n;        MD_MIG_VALUE_THRES_VALUE_MASK)
DECL|macro|MD_MIG_VALUE_THRESH_SET
mdefine_line|#define MD_MIG_VALUE_THRESH_SET(region, value) (                        &bslash;&n;        REMOTE_HUB_S((region), MD_MIG_VALUE_THRESH,                     &bslash;&n;                MD_MIG_VALUE_THRES_VALID_MASK | (value)))
DECL|macro|MD_MIG_VALUE_THRESH_ENABLE
mdefine_line|#define MD_MIG_VALUE_THRESH_ENABLE(region) (                    &bslash;&n;        REMOTE_HUB_S((region), MD_MIG_VALUE_THRESH,                     &bslash;&n;                REMOTE_HUB_L((region), MD_MIG_VALUE_THRESH)             &bslash;&n;                             | MD_MIG_VALUE_THRES_VALID_MASK))
multiline_comment|/*&n; * Operations on page migration candidate register&n; */
DECL|macro|MD_MIG_CANDIDATE_GET
mdefine_line|#define MD_MIG_CANDIDATE_GET(my_region_id) ( &bslash;&n;        REMOTE_HUB_L((my_region_id), MD_MIG_CANDIDATE_CLR))
DECL|macro|MD_MIG_CANDIDATE_HWPFN
mdefine_line|#define MD_MIG_CANDIDATE_HWPFN(value) ((value) &amp; MD_MIG_CANDIDATE_ADDR_MASK)
DECL|macro|MD_MIG_CANDIDATE_NODEID
mdefine_line|#define MD_MIG_CANDIDATE_NODEID(value) ( &bslash;&n;        ((value) &amp; MD_MIG_CANDIDATE_NODEID_MASK) &gt;&gt; MD_MIG_CANDIDATE_NODEID_SHFT)
DECL|macro|MD_MIG_CANDIDATE_TYPE
mdefine_line|#define MD_MIG_CANDIDATE_TYPE(value) ( &bslash;&n;        ((value) &amp; MD_MIG_CANDIDATE_TYPE_MASK) &gt;&gt; MD_MIG_CANDIDATE_TYPE_SHFT)
DECL|macro|MD_MIG_CANDIDATE_VALID
mdefine_line|#define MD_MIG_CANDIDATE_VALID(value) ( &bslash;&n;        ((value) &amp; MD_MIG_CANDIDATE_VALID_MASK) &gt;&gt; MD_MIG_CANDIDATE_VALID_SHFT)
multiline_comment|/*&n; * Macros to retrieve fields in the protection entry&n; */
multiline_comment|/* for Premium SIMM */
DECL|macro|MD_PPROT_REFCNT_GET
mdefine_line|#define MD_PPROT_REFCNT_GET(value) ( &bslash;&n;        ((value) &amp; MD_PPROT_REFCNT_MASK) &gt;&gt; MD_PPROT_REFCNT_SHFT)
multiline_comment|/* for Standard SIMM */
DECL|macro|MD_SPROT_REFCNT_GET
mdefine_line|#define MD_SPROT_REFCNT_GET(value) ( &bslash;&n;        ((value) &amp; MD_SPROT_REFCNT_MASK) &gt;&gt; MD_SPROT_REFCNT_SHFT)
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef LITTLE_ENDIAN
DECL|union|md_perf_sel
r_typedef
r_union
id|md_perf_sel
(brace
DECL|member|perf_sel_reg
r_uint64
id|perf_sel_reg
suffix:semicolon
r_struct
(brace
DECL|member|perf_sel
r_uint64
id|perf_sel
suffix:colon
l_int|3
comma
DECL|member|perf_en
id|perf_en
suffix:colon
l_int|1
comma
DECL|member|perf_rsvd
id|perf_rsvd
suffix:colon
l_int|60
suffix:semicolon
DECL|member|perf_sel_bits
)brace
id|perf_sel_bits
suffix:semicolon
DECL|typedef|md_perf_sel_t
)brace
id|md_perf_sel_t
suffix:semicolon
macro_line|#else
DECL|union|md_perf_sel
r_typedef
r_union
id|md_perf_sel
(brace
DECL|member|perf_sel_reg
r_uint64
id|perf_sel_reg
suffix:semicolon
r_struct
(brace
DECL|member|perf_rsvd
r_uint64
id|perf_rsvd
suffix:colon
l_int|60
comma
DECL|member|perf_en
id|perf_en
suffix:colon
l_int|1
comma
DECL|member|perf_sel
id|perf_sel
suffix:colon
l_int|3
suffix:semicolon
DECL|member|perf_sel_bits
)brace
id|perf_sel_bits
suffix:semicolon
DECL|typedef|md_perf_sel_t
)brace
id|md_perf_sel_t
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* Like SN0, SN1 supports a mostly-flat address space with 8&n;   CPU-visible, evenly spaced, contiguous regions, or &quot;software&n;   banks&quot;.  On SN1, software bank n begins at addresses n * 1GB, &n;   0 &lt;= n &lt; 8.&n;&n;   Physically (and very unlike SN0), each SN1 node board contains 8&n;   dimm sockets, arranged as 4 &quot;DIMM banks&quot; of 2 dimms each.  DIMM&n;   size and width (x4/x8) is assigned per dimm bank.  Each DIMM bank&n;   consists of 2 &quot;physical banks&quot;, one on the front sides of the 2&n;   DIMMs and the other on the back sides.  Therefore a node has a&n;   total of 8 ( = 4 * 2) physical banks.  They are collectively&n;   referred to as &quot;locational banks&quot;, since the locational bank number&n;   depends on the physical location of the DIMMs on the board.&n;&n;&t;      Dimm bank 0, Phys bank 0a (locational bank 0a)&n;     Slot D0  ----------------------------------------------&n;&t;      Dimm bank 0, Phys bank 1a (locational bank 1a)&n;&n;&t;      Dimm bank 1, Phys bank 0a (locational bank 2a)&n;     Slot D1  ----------------------------------------------&n;&t;      Dimm bank 1, Phys bank 1a (locational bank 3a)&n;&n;&t;      Dimm bank 2, Phys bank 0a (locational bank 4a)&n;     Slot D2  ----------------------------------------------&n;&t;      Dimm bank 2, Phys bank 1a (locational bank 5a)&n;&n;&t;      Dimm bank 3, Phys bank 0a (locational bank 6a)&n;     Slot D3  ----------------------------------------------&n;&t;      Dimm bank 3, Phys bank 1a (locational bank 7a)&n;&n;&t;      Dimm bank 0, Phys bank 0b (locational bank 0b)&n;     Slot D4  ----------------------------------------------&n;&t;      Dimm bank 0, Phys bank 1b (locational bank 1b)&n;&n;&t;      Dimm bank 1, Phys bank 0b (locational bank 2b)&n;     Slot D5  ----------------------------------------------&n;&t;      Dimm bank 1, Phys bank 1b (locational bank 3b)&n;&n;&t;      Dimm bank 2, Phys bank 0b (locational bank 4b)&n;     Slot D6  ----------------------------------------------&n;&t;      Dimm bank 2, Phys bank 1b (locational bank 5b)&n;&n;&t;      Dimm bank 3, Phys bank 0b (locational bank 6b)&n;     Slot D7  ----------------------------------------------&n;&t;      Dimm bank 3, Phys bank 1b (locational bank 7b)&n;&n;   Since bank size is assigned per DIMM bank, each pair of locational&n;   banks must have the same size.  However, they may be&n;   enabled/disabled individually.&n;&n;   The locational banks map to the software banks via the dimm0_sel&n;   field in MD_MEMORY_CONFIG.  When the field is 0 (the usual case),&n;   the mapping is direct:  eg. locational bank 1 (dimm bank 0,&n;   physical bank 1, which is the back side of the first DIMM pair)&n;   corresponds to software bank 1, at node offset 1GB.  More&n;   generally, locational bank = software bank XOR dimm0_sel.&n;&n;   All the PROM&squot;s data structures (promlog variables, klconfig, etc.)&n;   track memory by the locational bank number.  The kernel usually&n;   tracks memory by the software bank number.&n;   memsupport.c:slot_psize_compute() performs the mapping.&n;&n;   (Note:  the terms &quot;locational bank&quot; and &quot;software bank&quot; are not&n;   offical in any way, but I&squot;ve tried to make the PROM use them&n;   consistently -- bjj.)&n; */
DECL|macro|MD_MEM_BANKS
mdefine_line|#define MD_MEM_BANKS &t;&t;8
DECL|macro|MD_MEM_DIMM_BANKS
mdefine_line|#define MD_MEM_DIMM_BANKS &t;4
DECL|macro|MD_BANK_SHFT
mdefine_line|#define MD_BANK_SHFT            30                     /* log2(1 GB)     */
DECL|macro|MD_BANK_MASK
mdefine_line|#define MD_BANK_MASK            (UINT64_CAST 0x7 &lt;&lt; 30)
DECL|macro|MD_BANK_SIZE
mdefine_line|#define MD_BANK_SIZE            (UINT64_CAST 1 &lt;&lt; MD_BANK_SHFT)   /*  1 GB */
DECL|macro|MD_BANK_OFFSET
mdefine_line|#define MD_BANK_OFFSET(_b)      (UINT64_CAST (_b) &lt;&lt; MD_BANK_SHFT)
DECL|macro|MD_BANK_GET
mdefine_line|#define MD_BANK_GET(addr)&t;(((addr) &amp; MD_BANK_MASK) &gt;&gt; MD_BANK_SHFT)
DECL|macro|MD_BANK_TO_DIMM_BANK
mdefine_line|#define MD_BANK_TO_DIMM_BANK(_b) (( (_b) &gt;&gt; 1) &amp; 0x3)
DECL|macro|MD_BANK_TO_PHYS_BANK
mdefine_line|#define MD_BANK_TO_PHYS_BANK(_b) (( (_b) &gt;&gt; 0) &amp; 0x1)
DECL|macro|MD_DIMM_BANK_GET
mdefine_line|#define MD_DIMM_BANK_GET(addr)   MD_BANK_TO_DIMM_BANK(MD_BANK_GET(addr))
DECL|macro|MD_PHYS_BANK_GET
mdefine_line|#define MD_PHYS_BANK_GET(addr)   MD_BANK_TO_PHYS_BANK(MD_BANK_GET(addr))
multiline_comment|/* Split an MD pointer (or message source &amp; suppl. fields) into node, device */
DECL|macro|MD_PTR_NODE_SHFT
mdefine_line|#define MD_PTR_NODE_SHFT&t;3
DECL|macro|MD_PTR_DEVICE_MASK
mdefine_line|#define MD_PTR_DEVICE_MASK&t;0x7
DECL|macro|MD_PTR_SUBNODE0_MASK
mdefine_line|#define MD_PTR_SUBNODE0_MASK&t;0x1
DECL|macro|MD_PTR_SUBNODE1_MASK
mdefine_line|#define MD_PTR_SUBNODE1_MASK&t;0x4
multiline_comment|/**********************************************************************&n;&n; Backdoor protection and page counter structures&n;&n;**********************************************************************/
multiline_comment|/* Protection entries and page counters are interleaved at 4 separate&n;   addresses, 0x10 apart.  Software must read/write all four. */
DECL|macro|BD_ITLV_COUNT
mdefine_line|#define BD_ITLV_COUNT&t;&t;4
DECL|macro|BD_ITLV_STRIDE
mdefine_line|#define BD_ITLV_STRIDE&t;&t;0x10
multiline_comment|/* Protection entries */
multiline_comment|/* (these macros work for standard (_rgn &lt; 32) or premium DIMMs) */
DECL|macro|MD_PROT_SHFT
mdefine_line|#define MD_PROT_SHFT(_rgn, _io)&t;((((_rgn) &amp; 0x20) &gt;&gt; 2 | &bslash;&n;&t;&t;&t;&t;  ((_rgn) &amp; 0x01) &lt;&lt; 2 | &bslash;&n;&t;&t;&t;&t;  ((_io)  &amp;  0x1) &lt;&lt; 1) * 8)
DECL|macro|MD_PROT_MASK
mdefine_line|#define MD_PROT_MASK(_rgn, _io)&t;(0xff &lt;&lt; MD_PROT_SHFT(_rgn, _io))
DECL|macro|MD_PROT_GET
mdefine_line|#define MD_PROT_GET(_val, _rgn, _io) &bslash;&n;&t;(((_val) &amp; MD_PROT_MASK(_rgn, _io)) &gt;&gt; MD_PROT_SHFT(_rgn, _io))
multiline_comment|/* Protection field values */
DECL|macro|MD_PROT_RW
mdefine_line|#define MD_PROT_RW              (UINT64_CAST 0xff)
DECL|macro|MD_PROT_RO
mdefine_line|#define MD_PROT_RO              (UINT64_CAST 0x0f)
DECL|macro|MD_PROT_NO
mdefine_line|#define MD_PROT_NO              (UINT64_CAST 0x00)
multiline_comment|/**********************************************************************&n;&n; Directory format structures&n;&n;***********************************************************************/
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Standard Directory Entries */
macro_line|#ifdef LITTLE_ENDIAN
DECL|struct|md_sdir_pointer_fmt
r_struct
id|md_sdir_pointer_fmt
(brace
multiline_comment|/* exclusive, busy shared/excl, wait, poisoned */
DECL|member|sdp_format
id|bdrkreg_t
id|sdp_format
suffix:colon
l_int|2
suffix:semicolon
DECL|member|sdp_state
id|bdrkreg_t
id|sdp_state
suffix:colon
l_int|3
suffix:semicolon
DECL|member|sdp_priority
id|bdrkreg_t
id|sdp_priority
suffix:colon
l_int|3
suffix:semicolon
DECL|member|sdp_pointer1
id|bdrkreg_t
id|sdp_pointer1
suffix:colon
l_int|8
suffix:semicolon
DECL|member|sdp_ecc
id|bdrkreg_t
id|sdp_ecc
suffix:colon
l_int|6
suffix:semicolon
DECL|member|sdp_locprot
id|bdrkreg_t
id|sdp_locprot
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sdp_reserved
id|bdrkreg_t
id|sdp_reserved
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sdp_crit_word_off
id|bdrkreg_t
id|sdp_crit_word_off
suffix:colon
l_int|3
suffix:semicolon
DECL|member|sdp_pointer2
id|bdrkreg_t
id|sdp_pointer2
suffix:colon
l_int|5
suffix:semicolon
DECL|member|sdp_fill
id|bdrkreg_t
id|sdp_fill
suffix:colon
l_int|32
suffix:semicolon
)brace
suffix:semicolon
macro_line|#else
DECL|struct|md_sdir_pointer_fmt
r_struct
id|md_sdir_pointer_fmt
(brace
multiline_comment|/* exclusive, busy shared/excl, wait, poisoned */
DECL|member|sdp_fill
id|bdrkreg_t
id|sdp_fill
suffix:colon
l_int|32
suffix:semicolon
DECL|member|sdp_pointer2
id|bdrkreg_t
id|sdp_pointer2
suffix:colon
l_int|5
suffix:semicolon
DECL|member|sdp_crit_word_off
id|bdrkreg_t
id|sdp_crit_word_off
suffix:colon
l_int|3
suffix:semicolon
DECL|member|sdp_reserved
id|bdrkreg_t
id|sdp_reserved
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sdp_locprot
id|bdrkreg_t
id|sdp_locprot
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sdp_ecc
id|bdrkreg_t
id|sdp_ecc
suffix:colon
l_int|6
suffix:semicolon
DECL|member|sdp_pointer1
id|bdrkreg_t
id|sdp_pointer1
suffix:colon
l_int|8
suffix:semicolon
DECL|member|sdp_priority
id|bdrkreg_t
id|sdp_priority
suffix:colon
l_int|3
suffix:semicolon
DECL|member|sdp_state
id|bdrkreg_t
id|sdp_state
suffix:colon
l_int|3
suffix:semicolon
DECL|member|sdp_format
id|bdrkreg_t
id|sdp_format
suffix:colon
l_int|2
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef LITTLE_ENDIAN
DECL|struct|md_sdir_fine_fmt
r_struct
id|md_sdir_fine_fmt
(brace
multiline_comment|/* shared (fine) */
DECL|member|sdf_format
id|bdrkreg_t
id|sdf_format
suffix:colon
l_int|2
suffix:semicolon
DECL|member|sdf_tag1
id|bdrkreg_t
id|sdf_tag1
suffix:colon
l_int|3
suffix:semicolon
DECL|member|sdf_tag2
id|bdrkreg_t
id|sdf_tag2
suffix:colon
l_int|3
suffix:semicolon
DECL|member|sdf_vector1
id|bdrkreg_t
id|sdf_vector1
suffix:colon
l_int|8
suffix:semicolon
DECL|member|sdf_ecc
id|bdrkreg_t
id|sdf_ecc
suffix:colon
l_int|6
suffix:semicolon
DECL|member|sdf_locprot
id|bdrkreg_t
id|sdf_locprot
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sdf_tag2valid
id|bdrkreg_t
id|sdf_tag2valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sdf_vector2
id|bdrkreg_t
id|sdf_vector2
suffix:colon
l_int|8
suffix:semicolon
DECL|member|sdf_fill
id|bdrkreg_t
id|sdf_fill
suffix:colon
l_int|32
suffix:semicolon
)brace
suffix:semicolon
macro_line|#else
DECL|struct|md_sdir_fine_fmt
r_struct
id|md_sdir_fine_fmt
(brace
multiline_comment|/* shared (fine) */
DECL|member|sdf_fill
id|bdrkreg_t
id|sdf_fill
suffix:colon
l_int|32
suffix:semicolon
DECL|member|sdf_vector2
id|bdrkreg_t
id|sdf_vector2
suffix:colon
l_int|8
suffix:semicolon
DECL|member|sdf_tag2valid
id|bdrkreg_t
id|sdf_tag2valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sdf_locprot
id|bdrkreg_t
id|sdf_locprot
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sdf_ecc
id|bdrkreg_t
id|sdf_ecc
suffix:colon
l_int|6
suffix:semicolon
DECL|member|sdf_vector1
id|bdrkreg_t
id|sdf_vector1
suffix:colon
l_int|8
suffix:semicolon
DECL|member|sdf_tag2
id|bdrkreg_t
id|sdf_tag2
suffix:colon
l_int|3
suffix:semicolon
DECL|member|sdf_tag1
id|bdrkreg_t
id|sdf_tag1
suffix:colon
l_int|3
suffix:semicolon
DECL|member|sdf_format
id|bdrkreg_t
id|sdf_format
suffix:colon
l_int|2
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef LITTLE_ENDIAN
DECL|struct|md_sdir_coarse_fmt
r_struct
id|md_sdir_coarse_fmt
(brace
multiline_comment|/* shared (coarse) */
DECL|member|sdc_format
id|bdrkreg_t
id|sdc_format
suffix:colon
l_int|2
suffix:semicolon
DECL|member|sdc_reserved_1
id|bdrkreg_t
id|sdc_reserved_1
suffix:colon
l_int|6
suffix:semicolon
DECL|member|sdc_vector_a
id|bdrkreg_t
id|sdc_vector_a
suffix:colon
l_int|8
suffix:semicolon
DECL|member|sdc_ecc
id|bdrkreg_t
id|sdc_ecc
suffix:colon
l_int|6
suffix:semicolon
DECL|member|sdc_locprot
id|bdrkreg_t
id|sdc_locprot
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sdc_reserved
id|bdrkreg_t
id|sdc_reserved
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sdc_vector_b
id|bdrkreg_t
id|sdc_vector_b
suffix:colon
l_int|8
suffix:semicolon
DECL|member|sdc_fill
id|bdrkreg_t
id|sdc_fill
suffix:colon
l_int|32
suffix:semicolon
)brace
suffix:semicolon
macro_line|#else
DECL|struct|md_sdir_coarse_fmt
r_struct
id|md_sdir_coarse_fmt
(brace
multiline_comment|/* shared (coarse) */
DECL|member|sdc_fill
id|bdrkreg_t
id|sdc_fill
suffix:colon
l_int|32
suffix:semicolon
DECL|member|sdc_vector_b
id|bdrkreg_t
id|sdc_vector_b
suffix:colon
l_int|8
suffix:semicolon
DECL|member|sdc_reserved
id|bdrkreg_t
id|sdc_reserved
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sdc_locprot
id|bdrkreg_t
id|sdc_locprot
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sdc_ecc
id|bdrkreg_t
id|sdc_ecc
suffix:colon
l_int|6
suffix:semicolon
DECL|member|sdc_vector_a
id|bdrkreg_t
id|sdc_vector_a
suffix:colon
l_int|8
suffix:semicolon
DECL|member|sdc_reserved_1
id|bdrkreg_t
id|sdc_reserved_1
suffix:colon
l_int|6
suffix:semicolon
DECL|member|sdc_format
id|bdrkreg_t
id|sdc_format
suffix:colon
l_int|2
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
DECL|union|md_sdir
r_typedef
r_union
id|md_sdir
(brace
multiline_comment|/* The 32 bits of standard directory, in bits 31:0 */
DECL|member|sd_val
r_uint64
id|sd_val
suffix:semicolon
DECL|member|sdp_fmt
r_struct
id|md_sdir_pointer_fmt
id|sdp_fmt
suffix:semicolon
DECL|member|sdf_fmt
r_struct
id|md_sdir_fine_fmt
id|sdf_fmt
suffix:semicolon
DECL|member|sdc_fmt
r_struct
id|md_sdir_coarse_fmt
id|sdc_fmt
suffix:semicolon
DECL|typedef|md_sdir_t
)brace
id|md_sdir_t
suffix:semicolon
multiline_comment|/* Premium Directory Entries */
macro_line|#ifdef LITTLE_ENDIAN
DECL|struct|md_pdir_pointer_fmt
r_struct
id|md_pdir_pointer_fmt
(brace
multiline_comment|/* exclusive, busy shared/excl, wait, poisoned */
DECL|member|pdp_format
id|bdrkreg_t
id|pdp_format
suffix:colon
l_int|2
suffix:semicolon
DECL|member|pdp_state
id|bdrkreg_t
id|pdp_state
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pdp_priority
id|bdrkreg_t
id|pdp_priority
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pdp_pointer1_a
id|bdrkreg_t
id|pdp_pointer1_a
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pdp_reserved_4
id|bdrkreg_t
id|pdp_reserved_4
suffix:colon
l_int|6
suffix:semicolon
DECL|member|pdp_pointer1_b
id|bdrkreg_t
id|pdp_pointer1_b
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pdp_reserved_3
id|bdrkreg_t
id|pdp_reserved_3
suffix:colon
l_int|7
suffix:semicolon
DECL|member|pdp_ecc_a
id|bdrkreg_t
id|pdp_ecc_a
suffix:colon
l_int|6
suffix:semicolon
DECL|member|pdp_locprot
id|bdrkreg_t
id|pdp_locprot
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pdp_reserved_2
id|bdrkreg_t
id|pdp_reserved_2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pdp_crit_word_off
id|bdrkreg_t
id|pdp_crit_word_off
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pdp_pointer2_a
id|bdrkreg_t
id|pdp_pointer2_a
suffix:colon
l_int|5
suffix:semicolon
DECL|member|pdp_ecc_b
id|bdrkreg_t
id|pdp_ecc_b
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pdp_reserved_1
id|bdrkreg_t
id|pdp_reserved_1
suffix:colon
l_int|5
suffix:semicolon
DECL|member|pdp_pointer2_b
id|bdrkreg_t
id|pdp_pointer2_b
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pdp_reserved
id|bdrkreg_t
id|pdp_reserved
suffix:colon
l_int|7
suffix:semicolon
)brace
suffix:semicolon
macro_line|#else
DECL|struct|md_pdir_pointer_fmt
r_struct
id|md_pdir_pointer_fmt
(brace
multiline_comment|/* exclusive, busy shared/excl, wait, poisoned */
DECL|member|pdp_reserved
id|bdrkreg_t
id|pdp_reserved
suffix:colon
l_int|7
suffix:semicolon
DECL|member|pdp_pointer2_b
id|bdrkreg_t
id|pdp_pointer2_b
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pdp_reserved_1
id|bdrkreg_t
id|pdp_reserved_1
suffix:colon
l_int|5
suffix:semicolon
DECL|member|pdp_ecc_b
id|bdrkreg_t
id|pdp_ecc_b
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pdp_pointer2_a
id|bdrkreg_t
id|pdp_pointer2_a
suffix:colon
l_int|5
suffix:semicolon
DECL|member|pdp_crit_word_off
id|bdrkreg_t
id|pdp_crit_word_off
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pdp_reserved_2
id|bdrkreg_t
id|pdp_reserved_2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pdp_locprot
id|bdrkreg_t
id|pdp_locprot
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pdp_ecc_a
id|bdrkreg_t
id|pdp_ecc_a
suffix:colon
l_int|6
suffix:semicolon
DECL|member|pdp_reserved_3
id|bdrkreg_t
id|pdp_reserved_3
suffix:colon
l_int|7
suffix:semicolon
DECL|member|pdp_pointer1_b
id|bdrkreg_t
id|pdp_pointer1_b
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pdp_reserved_4
id|bdrkreg_t
id|pdp_reserved_4
suffix:colon
l_int|6
suffix:semicolon
DECL|member|pdp_pointer1_a
id|bdrkreg_t
id|pdp_pointer1_a
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pdp_priority
id|bdrkreg_t
id|pdp_priority
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pdp_state
id|bdrkreg_t
id|pdp_state
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pdp_format
id|bdrkreg_t
id|pdp_format
suffix:colon
l_int|2
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef LITTLE_ENDIAN
DECL|struct|md_pdir_fine_fmt
r_struct
id|md_pdir_fine_fmt
(brace
multiline_comment|/* shared (fine) */
DECL|member|pdf_format
id|bdrkreg_t
id|pdf_format
suffix:colon
l_int|2
suffix:semicolon
DECL|member|pdf_tag1_a
id|bdrkreg_t
id|pdf_tag1_a
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pdf_tag2_a
id|bdrkreg_t
id|pdf_tag2_a
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pdf_vector1_a
id|bdrkreg_t
id|pdf_vector1_a
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pdf_reserved_1
id|bdrkreg_t
id|pdf_reserved_1
suffix:colon
l_int|6
suffix:semicolon
DECL|member|pdf_tag1_b
id|bdrkreg_t
id|pdf_tag1_b
suffix:colon
l_int|2
suffix:semicolon
DECL|member|pdf_vector1_b
id|bdrkreg_t
id|pdf_vector1_b
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pdf_ecc_a
id|bdrkreg_t
id|pdf_ecc_a
suffix:colon
l_int|6
suffix:semicolon
DECL|member|pdf_locprot
id|bdrkreg_t
id|pdf_locprot
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pdf_tag2valid
id|bdrkreg_t
id|pdf_tag2valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pdf_vector2_a
id|bdrkreg_t
id|pdf_vector2_a
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pdf_ecc_b
id|bdrkreg_t
id|pdf_ecc_b
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pdf_reserved
id|bdrkreg_t
id|pdf_reserved
suffix:colon
l_int|5
suffix:semicolon
DECL|member|pdf_tag2_b
id|bdrkreg_t
id|pdf_tag2_b
suffix:colon
l_int|2
suffix:semicolon
DECL|member|pdf_vector2_b
id|bdrkreg_t
id|pdf_vector2_b
suffix:colon
l_int|8
suffix:semicolon
)brace
suffix:semicolon
macro_line|#else
DECL|struct|md_pdir_fine_fmt
r_struct
id|md_pdir_fine_fmt
(brace
multiline_comment|/* shared (fine) */
DECL|member|pdf_vector2_b
id|bdrkreg_t
id|pdf_vector2_b
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pdf_tag2_b
id|bdrkreg_t
id|pdf_tag2_b
suffix:colon
l_int|2
suffix:semicolon
DECL|member|pdf_reserved
id|bdrkreg_t
id|pdf_reserved
suffix:colon
l_int|5
suffix:semicolon
DECL|member|pdf_ecc_b
id|bdrkreg_t
id|pdf_ecc_b
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pdf_vector2_a
id|bdrkreg_t
id|pdf_vector2_a
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pdf_tag2valid
id|bdrkreg_t
id|pdf_tag2valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pdf_locprot
id|bdrkreg_t
id|pdf_locprot
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pdf_ecc_a
id|bdrkreg_t
id|pdf_ecc_a
suffix:colon
l_int|6
suffix:semicolon
DECL|member|pdf_vector1_b
id|bdrkreg_t
id|pdf_vector1_b
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pdf_tag1_b
id|bdrkreg_t
id|pdf_tag1_b
suffix:colon
l_int|2
suffix:semicolon
DECL|member|pdf_reserved_1
id|bdrkreg_t
id|pdf_reserved_1
suffix:colon
l_int|6
suffix:semicolon
DECL|member|pdf_vector1_a
id|bdrkreg_t
id|pdf_vector1_a
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pdf_tag2_a
id|bdrkreg_t
id|pdf_tag2_a
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pdf_tag1_a
id|bdrkreg_t
id|pdf_tag1_a
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pdf_format
id|bdrkreg_t
id|pdf_format
suffix:colon
l_int|2
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef LITTLE_ENDIAN
DECL|struct|md_pdir_sparse_fmt
r_struct
id|md_pdir_sparse_fmt
(brace
multiline_comment|/* shared (sparse) */
DECL|member|pds_format
id|bdrkreg_t
id|pds_format
suffix:colon
l_int|2
suffix:semicolon
DECL|member|pds_column_a
id|bdrkreg_t
id|pds_column_a
suffix:colon
l_int|6
suffix:semicolon
DECL|member|pds_row_a
id|bdrkreg_t
id|pds_row_a
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pds_column_b
id|bdrkreg_t
id|pds_column_b
suffix:colon
l_int|16
suffix:semicolon
DECL|member|pds_ecc_a
id|bdrkreg_t
id|pds_ecc_a
suffix:colon
l_int|6
suffix:semicolon
DECL|member|pds_locprot
id|bdrkreg_t
id|pds_locprot
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pds_reserved_1
id|bdrkreg_t
id|pds_reserved_1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pds_row_b
id|bdrkreg_t
id|pds_row_b
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pds_ecc_b
id|bdrkreg_t
id|pds_ecc_b
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pds_column_c
id|bdrkreg_t
id|pds_column_c
suffix:colon
l_int|10
suffix:semicolon
DECL|member|pds_reserved
id|bdrkreg_t
id|pds_reserved
suffix:colon
l_int|5
suffix:semicolon
)brace
suffix:semicolon
macro_line|#else
DECL|struct|md_pdir_sparse_fmt
r_struct
id|md_pdir_sparse_fmt
(brace
multiline_comment|/* shared (sparse) */
DECL|member|pds_reserved
id|bdrkreg_t
id|pds_reserved
suffix:colon
l_int|5
suffix:semicolon
DECL|member|pds_column_c
id|bdrkreg_t
id|pds_column_c
suffix:colon
l_int|10
suffix:semicolon
DECL|member|pds_ecc_b
id|bdrkreg_t
id|pds_ecc_b
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pds_row_b
id|bdrkreg_t
id|pds_row_b
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pds_reserved_1
id|bdrkreg_t
id|pds_reserved_1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pds_locprot
id|bdrkreg_t
id|pds_locprot
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pds_ecc_a
id|bdrkreg_t
id|pds_ecc_a
suffix:colon
l_int|6
suffix:semicolon
DECL|member|pds_column_b
id|bdrkreg_t
id|pds_column_b
suffix:colon
l_int|16
suffix:semicolon
DECL|member|pds_row_a
id|bdrkreg_t
id|pds_row_a
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pds_column_a
id|bdrkreg_t
id|pds_column_a
suffix:colon
l_int|6
suffix:semicolon
DECL|member|pds_format
id|bdrkreg_t
id|pds_format
suffix:colon
l_int|2
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
DECL|union|md_pdir
r_typedef
r_union
id|md_pdir
(brace
multiline_comment|/* The 64 bits of premium directory */
DECL|member|pd_val
r_uint64
id|pd_val
suffix:semicolon
DECL|member|pdp_fmt
r_struct
id|md_pdir_pointer_fmt
id|pdp_fmt
suffix:semicolon
DECL|member|pdf_fmt
r_struct
id|md_pdir_fine_fmt
id|pdf_fmt
suffix:semicolon
DECL|member|pds_fmt
r_struct
id|md_pdir_sparse_fmt
id|pds_fmt
suffix:semicolon
DECL|typedef|md_pdir_t
)brace
id|md_pdir_t
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/**********************************************************************&n;&n; The defines for backdoor directory and backdoor ECC.&n;&n;***********************************************************************/
multiline_comment|/* Directory formats, for each format&squot;s &quot;format&quot; field */
DECL|macro|MD_FORMAT_UNOWNED
mdefine_line|#define MD_FORMAT_UNOWNED&t;(UINT64_CAST 0x0)&t;/* 00 */
DECL|macro|MD_FORMAT_POINTER
mdefine_line|#define MD_FORMAT_POINTER&t;(UINT64_CAST 0x1)&t;/* 01 */
DECL|macro|MD_FORMAT_SHFINE
mdefine_line|#define MD_FORMAT_SHFINE&t;(UINT64_CAST 0x2)&t;/* 10 */
DECL|macro|MD_FORMAT_SHCOARSE
mdefine_line|#define MD_FORMAT_SHCOARSE&t;(UINT64_CAST 0x3)&t;/* 11 */
multiline_comment|/* Shared coarse (standard) and shared sparse (premium) both use fmt 0x3 */
multiline_comment|/*&n; * Cacheline state values.&n; *&n; * These are really *software* notions of the &quot;state&quot; of a cacheline; but the&n; * actual values have been carefully chosen to align with some hardware values!&n; * The MD_FMT_ST_TO_STATE macro is used to convert from hardware format/state&n; * pairs in the directory entried into one of these cacheline state values.&n; */
DECL|macro|MD_DIR_EXCLUSIVE
mdefine_line|#define MD_DIR_EXCLUSIVE&t;(UINT64_CAST 0x0)&t;/* ptr format, hw-defined */
DECL|macro|MD_DIR_UNOWNED
mdefine_line|#define MD_DIR_UNOWNED&t;&t;(UINT64_CAST 0x1)&t;/* format=0 */
DECL|macro|MD_DIR_SHARED
mdefine_line|#define MD_DIR_SHARED&t;&t;(UINT64_CAST 0x2)&t;/* format=2,3 */
DECL|macro|MD_DIR_BUSY_SHARED
mdefine_line|#define MD_DIR_BUSY_SHARED&t;(UINT64_CAST 0x4)&t;/* ptr format, hw-defined */
DECL|macro|MD_DIR_BUSY_EXCL
mdefine_line|#define MD_DIR_BUSY_EXCL&t;(UINT64_CAST 0x5)&t;/* ptr format, hw-defined */
DECL|macro|MD_DIR_WAIT
mdefine_line|#define MD_DIR_WAIT&t;&t;(UINT64_CAST 0x6)&t;/* ptr format, hw-defined */
DECL|macro|MD_DIR_POISONED
mdefine_line|#define MD_DIR_POISONED&t;&t;(UINT64_CAST 0x7)&t;/* ptr format, hw-defined */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Convert format and state fields into a single &quot;cacheline state&quot; value, defined above */
DECL|macro|MD_FMT_ST_TO_STATE
mdefine_line|#define MD_FMT_ST_TO_STATE(fmt, state) &bslash;&n;  ((fmt) == MD_FORMAT_POINTER ? (state) : &bslash;&n;   (fmt) == MD_FORMAT_UNOWNED ? MD_DIR_UNOWNED : &bslash;&n;   MD_DIR_SHARED)
DECL|macro|MD_DIR_STATE
mdefine_line|#define MD_DIR_STATE(x) MD_FMT_ST_TO_STATE(MD_DIR_FORMAT(x), MD_DIR_STVAL(x))
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* Directory field shifts and masks */
multiline_comment|/* Standard */
DECL|macro|MD_SDIR_FORMAT_SHFT
mdefine_line|#define MD_SDIR_FORMAT_SHFT&t;0&t;&t;&t;/* All formats */
DECL|macro|MD_SDIR_FORMAT_MASK
mdefine_line|#define MD_SDIR_FORMAT_MASK&t;(0x3 &lt;&lt; 0)
DECL|macro|MD_SDIR_STATE_SHFT
mdefine_line|#define MD_SDIR_STATE_SHFT&t;2&t;&t;&t;/* Pointer fmt. only */
DECL|macro|MD_SDIR_STATE_MASK
mdefine_line|#define MD_SDIR_STATE_MASK&t;(0x7 &lt;&lt; 2)
multiline_comment|/* Premium */
DECL|macro|MD_PDIR_FORMAT_SHFT
mdefine_line|#define MD_PDIR_FORMAT_SHFT&t;0&t;&t;&t;/* All formats */
DECL|macro|MD_PDIR_FORMAT_MASK
mdefine_line|#define MD_PDIR_FORMAT_MASK&t;(0x3 &lt;&lt; 0)
DECL|macro|MD_PDIR_STATE_SHFT
mdefine_line|#define MD_PDIR_STATE_SHFT&t;2&t;&t;&t;/* Pointer fmt. only */
DECL|macro|MD_PDIR_STATE_MASK
mdefine_line|#define MD_PDIR_STATE_MASK&t;(0x7 &lt;&lt; 2)
multiline_comment|/* Generic */
DECL|macro|MD_FORMAT_SHFT
mdefine_line|#define MD_FORMAT_SHFT&t;0&t;&t;&t;&t;/* All formats */
DECL|macro|MD_FORMAT_MASK
mdefine_line|#define MD_FORMAT_MASK&t;(0x3 &lt;&lt; 0)
DECL|macro|MD_STATE_SHFT
mdefine_line|#define MD_STATE_SHFT&t;2&t;&t;&t;&t;/* Pointer fmt. only */
DECL|macro|MD_STATE_MASK
mdefine_line|#define MD_STATE_MASK&t;(0x7 &lt;&lt; 2)
multiline_comment|/* Special shifts to reconstruct fields from the _a and _b parts */
multiline_comment|/* Standard:  only shared coarse has split fields */
DECL|macro|MD_SDC_VECTORB_SHFT
mdefine_line|#define MD_SDC_VECTORB_SHFT&t;8&t;/* eg: sdc_vector_a is 8 bits */
multiline_comment|/* Premium:  pointer, shared fine, shared sparse */
DECL|macro|MD_PDP_POINTER1A_MASK
mdefine_line|#define MD_PDP_POINTER1A_MASK&t;0xFF
DECL|macro|MD_PDP_POINTER1B_SHFT
mdefine_line|#define MD_PDP_POINTER1B_SHFT&t;8
DECL|macro|MD_PDP_POINTER2B_SHFT
mdefine_line|#define MD_PDP_POINTER2B_SHFT&t;5
DECL|macro|MD_PDP_ECCB_SHFT
mdefine_line|#define MD_PDP_ECCB_SHFT&t;6
DECL|macro|MD_PDF_VECTOR1B_SHFT
mdefine_line|#define MD_PDF_VECTOR1B_SHFT&t;8
DECL|macro|MD_PDF_VECTOR2B_SHFT
mdefine_line|#define MD_PDF_VECTOR2B_SHFT&t;8
DECL|macro|MD_PDF_TAG1B_SHFT
mdefine_line|#define MD_PDF_TAG1B_SHFT&t;3
DECL|macro|MD_PDF_TAG2B_SHFT
mdefine_line|#define MD_PDF_TAG2B_SHFT&t;3
DECL|macro|MD_PDF_ECC_SHFT
mdefine_line|#define MD_PDF_ECC_SHFT&t;&t;6
DECL|macro|MD_PDS_ROWB_SHFT
mdefine_line|#define MD_PDS_ROWB_SHFT&t;8
DECL|macro|MD_PDS_COLUMNB_SHFT
mdefine_line|#define MD_PDS_COLUMNB_SHFT&t;6
DECL|macro|MD_PDS_COLUMNC_SHFT
mdefine_line|#define MD_PDS_COLUMNC_SHFT&t;(MD_PDS_COLUMNB_SHFT + 16)
DECL|macro|MD_PDS_ECC_SHFT
mdefine_line|#define MD_PDS_ECC_SHFT&t;&t;6
multiline_comment|/*&n; * Directory/protection/counter initialization values, premium and standard&n; */
DECL|macro|MD_PDIR_INIT
mdefine_line|#define MD_PDIR_INIT&t;&t;0
DECL|macro|MD_PDIR_INIT_CNT
mdefine_line|#define MD_PDIR_INIT_CNT&t;0
DECL|macro|MD_PDIR_INIT_PROT
mdefine_line|#define MD_PDIR_INIT_PROT&t;0
DECL|macro|MD_SDIR_INIT
mdefine_line|#define MD_SDIR_INIT&t;&t;0
DECL|macro|MD_SDIR_INIT_CNT
mdefine_line|#define MD_SDIR_INIT_CNT&t;0
DECL|macro|MD_SDIR_INIT_PROT
mdefine_line|#define MD_SDIR_INIT_PROT&t;0
DECL|macro|MD_PDIR_MASK
mdefine_line|#define MD_PDIR_MASK            0xffffffffffffffff
DECL|macro|MD_SDIR_MASK
mdefine_line|#define MD_SDIR_MASK            0xffffffff
multiline_comment|/* When premium mode is on for probing but standard directory memory&n;   is installed, the valid directory bits depend on the phys. bank */
DECL|macro|MD_PDIR_PROBE_MASK
mdefine_line|#define MD_PDIR_PROBE_MASK(pb)  0xffffffffffffffff
DECL|macro|MD_SDIR_PROBE_MASK
mdefine_line|#define MD_SDIR_PROBE_MASK(pb)  (0xffff0000ffff &lt;&lt; ((pb) ? 16 : 0))
multiline_comment|/*&n; * Misc. field extractions and conversions&n; */
multiline_comment|/* Convert an MD pointer (or message source, supplemental fields) */
DECL|macro|MD_PTR_NODE
mdefine_line|#define MD_PTR_NODE(x)&t;&t;((x) &gt;&gt; MD_PTR_NODE_SHFT)
DECL|macro|MD_PTR_DEVICE
mdefine_line|#define MD_PTR_DEVICE(x)&t;((x) &amp; MD_PTR_DEVICE_MASK)
DECL|macro|MD_PTR_SLICE
mdefine_line|#define MD_PTR_SLICE(x)&t;&t;(((x) &amp; MD_PTR_SUBNODE0_MASK) | &bslash;&n;&t;&t;&t;&t; ((x) &amp; MD_PTR_SUBNODE1_MASK) &gt;&gt; 1)
DECL|macro|MD_PTR_OWNER_CPU
mdefine_line|#define MD_PTR_OWNER_CPU(x)&t;(! ((x) &amp; 2))
DECL|macro|MD_PTR_OWNER_IO
mdefine_line|#define MD_PTR_OWNER_IO(x)&t;((x) &amp; 2)
multiline_comment|/* Extract format and raw state from a directory entry */
DECL|macro|MD_DIR_FORMAT
mdefine_line|#define MD_DIR_FORMAT(x)&t;((x) &gt;&gt; MD_SDIR_FORMAT_SHFT &amp; &bslash;&n;&t;&t;&t;&t; MD_SDIR_FORMAT_MASK &gt;&gt; MD_SDIR_FORMAT_SHFT)
DECL|macro|MD_DIR_STVAL
mdefine_line|#define MD_DIR_STVAL(x)&t;&t;((x) &gt;&gt; MD_SDIR_STATE_SHFT &amp; &bslash;&n;&t;&t;&t;&t; MD_SDIR_STATE_MASK &gt;&gt; MD_SDIR_STATE_SHFT)
multiline_comment|/* Mask &amp; Shift to get HSPEC_ADDR from MD DIR_ERROR register */
DECL|macro|ERROR_ADDR_SHFT
mdefine_line|#define ERROR_ADDR_SHFT         3
DECL|macro|ERROR_HSPEC_SHFT
mdefine_line|#define ERROR_HSPEC_SHFT        3
DECL|macro|DIR_ERR_HSPEC_MASK
mdefine_line|#define DIR_ERR_HSPEC_MASK      0x1fffffff8
multiline_comment|/*&n; *  DIR_ERR* and MEM_ERR* defines are used to avoid ugly&n; *  #ifdefs for SN0 and SN1 in memerror.c code.  See SN0/hubmd.h&n; *  for corresponding SN0 definitions.&n; */
DECL|macro|md_dir_error_t
mdefine_line|#define md_dir_error_t  md_dir_error_u_t
DECL|macro|md_mem_error_t
mdefine_line|#define md_mem_error_t  md_mem_error_u_t
DECL|macro|derr_reg
mdefine_line|#define derr_reg        md_dir_error_regval
DECL|macro|merr_reg
mdefine_line|#define merr_reg        md_mem_error_regval
DECL|macro|DIR_ERR_UCE_VALID
mdefine_line|#define DIR_ERR_UCE_VALID       dir_err.md_dir_error_fld_s.de_uce_valid
DECL|macro|DIR_ERR_AE_VALID
mdefine_line|#define DIR_ERR_AE_VALID        dir_err.md_dir_error_fld_s.de_ae_valid
DECL|macro|DIR_ERR_BAD_SYN
mdefine_line|#define DIR_ERR_BAD_SYN         dir_err.md_dir_error_fld_s.de_bad_syn
DECL|macro|DIR_ERR_CE_OVERRUN
mdefine_line|#define DIR_ERR_CE_OVERRUN      dir_err.md_dir_error_fld_s.de_ce_overrun
DECL|macro|MEM_ERR_ADDRESS
mdefine_line|#define MEM_ERR_ADDRESS         mem_err.md_mem_error_fld_s.me_address
multiline_comment|/* BRINGUP Can the overrun bit be set without the valid bit? */
DECL|macro|MEM_ERR_CE_OVERRUN
mdefine_line|#define MEM_ERR_CE_OVERRUN      (mem_err.md_mem_error_fld_s.me_read_ce &gt;&gt; 1)
DECL|macro|MEM_ERR_BAD_SYN
mdefine_line|#define MEM_ERR_BAD_SYN         mem_err.md_mem_error_fld_s.me_bad_syn
DECL|macro|MEM_ERR_UCE_VALID
mdefine_line|#define MEM_ERR_UCE_VALID       (mem_err.md_mem_error_fld_s.me_read_uce &amp; 1)
multiline_comment|/*********************************************************************&n;&n; We have the shift and masks of various fields defined below.&n;&n; *********************************************************************/
multiline_comment|/* MD_REFRESH_CONTROL fields */
DECL|macro|MRC_ENABLE_SHFT
mdefine_line|#define MRC_ENABLE_SHFT         63
DECL|macro|MRC_ENABLE_MASK
mdefine_line|#define MRC_ENABLE_MASK         (UINT64_CAST 1 &lt;&lt; 63)
DECL|macro|MRC_ENABLE
mdefine_line|#define MRC_ENABLE              (UINT64_CAST 1 &lt;&lt; 63)
DECL|macro|MRC_COUNTER_SHFT
mdefine_line|#define MRC_COUNTER_SHFT        12
DECL|macro|MRC_COUNTER_MASK
mdefine_line|#define MRC_COUNTER_MASK        (UINT64_CAST 0xfff &lt;&lt; 12)
DECL|macro|MRC_CNT_THRESH_MASK
mdefine_line|#define MRC_CNT_THRESH_MASK     0xfff
DECL|macro|MRC_RESET_DEFAULTS
mdefine_line|#define MRC_RESET_DEFAULTS      (UINT64_CAST 0x800)
multiline_comment|/* MD_DIR_CONFIG fields */
DECL|macro|MDC_DIR_PREMIUM
mdefine_line|#define MDC_DIR_PREMIUM&t;&t;(UINT64_CAST 1 &lt;&lt; 0)
DECL|macro|MDC_IGNORE_ECC_SHFT
mdefine_line|#define MDC_IGNORE_ECC_SHFT      1
DECL|macro|MDC_IGNORE_ECC_MASK
mdefine_line|#define MDC_IGNORE_ECC_MASK     (UINT64_CAST 1 &lt;&lt; 1)
multiline_comment|/* MD_MEMORY_CONFIG fields */
DECL|macro|MMC_RP_CONFIG_SHFT
mdefine_line|#define MMC_RP_CONFIG_SHFT&t;61
DECL|macro|MMC_RP_CONFIG_MASK
mdefine_line|#define MMC_RP_CONFIG_MASK&t;(UINT64_CAST 1 &lt;&lt; 61)
DECL|macro|MMC_RCD_CONFIG_SHFT
mdefine_line|#define MMC_RCD_CONFIG_SHFT&t;60
DECL|macro|MMC_RCD_CONFIG_MASK
mdefine_line|#define MMC_RCD_CONFIG_MASK&t;(UINT64_CAST 1 &lt;&lt; 60)
DECL|macro|MMC_MB_NEG_EDGE_SHFT
mdefine_line|#define MMC_MB_NEG_EDGE_SHFT&t;56
DECL|macro|MMC_MB_NEG_EDGE_MASK
mdefine_line|#define MMC_MB_NEG_EDGE_MASK&t;(UINT64_CAST 0x7 &lt;&lt; 56)
DECL|macro|MMC_SAMPLE_TIME_SHFT
mdefine_line|#define MMC_SAMPLE_TIME_SHFT&t;52
DECL|macro|MMC_SAMPLE_TIME_MASK
mdefine_line|#define MMC_SAMPLE_TIME_MASK&t;(UINT64_CAST 0x3 &lt;&lt; 52)
DECL|macro|MMC_DELAY_MUX_SEL_SHFT
mdefine_line|#define MMC_DELAY_MUX_SEL_SHFT&t;50
DECL|macro|MMC_DELAY_MUX_SEL_MASK
mdefine_line|#define MMC_DELAY_MUX_SEL_MASK&t;(UINT64_CAST 0x3 &lt;&lt; 50)
DECL|macro|MMC_PHASE_DELAY_SHFT
mdefine_line|#define MMC_PHASE_DELAY_SHFT&t;49
DECL|macro|MMC_PHASE_DELAY_MASK
mdefine_line|#define MMC_PHASE_DELAY_MASK&t;(UINT64_CAST 1 &lt;&lt; 49)
DECL|macro|MMC_DB_NEG_EDGE_SHFT
mdefine_line|#define MMC_DB_NEG_EDGE_SHFT&t;48
DECL|macro|MMC_DB_NEG_EDGE_MASK
mdefine_line|#define MMC_DB_NEG_EDGE_MASK&t;(UINT64_CAST 1 &lt;&lt; 48)
DECL|macro|MMC_CPU_PROT_IGNORE_SHFT
mdefine_line|#define MMC_CPU_PROT_IGNORE_SHFT&t; 47
DECL|macro|MMC_CPU_PROT_IGNORE_MASK
mdefine_line|#define MMC_CPU_PROT_IGNORE_MASK&t;(UINT64_CAST 1 &lt;&lt; 47)
DECL|macro|MMC_IO_PROT_IGNORE_SHFT
mdefine_line|#define MMC_IO_PROT_IGNORE_SHFT 46
DECL|macro|MMC_IO_PROT_IGNORE_MASK
mdefine_line|#define MMC_IO_PROT_IGNORE_MASK&t;(UINT64_CAST 1 &lt;&lt; 46)
DECL|macro|MMC_IO_PROT_EN_SHFT
mdefine_line|#define MMC_IO_PROT_EN_SHFT&t;45
DECL|macro|MMC_IO_PROT_EN_MASK
mdefine_line|#define MMC_IO_PROT_EN_MASK&t;(UINT64_CAST 1 &lt;&lt; 45)
DECL|macro|MMC_CC_ENABLE_SHFT
mdefine_line|#define MMC_CC_ENABLE_SHFT&t;44
DECL|macro|MMC_CC_ENABLE_MASK
mdefine_line|#define MMC_CC_ENABLE_MASK&t;(UINT64_CAST 1 &lt;&lt; 44)
DECL|macro|MMC_DIMM0_SEL_SHFT
mdefine_line|#define MMC_DIMM0_SEL_SHFT&t;32
DECL|macro|MMC_DIMM0_SEL_MASK
mdefine_line|#define MMC_DIMM0_SEL_MASK     (UINT64_CAST 0x3 &lt;&lt; 32)
DECL|macro|MMC_DIMM_SIZE_SHFT
mdefine_line|#define MMC_DIMM_SIZE_SHFT(_dimm)    ((_dimm &lt;&lt; 3) + 4)
DECL|macro|MMC_DIMM_SIZE_MASK
mdefine_line|#define MMC_DIMM_SIZE_MASK(_dimm)    (UINT64_CAST 0xf &lt;&lt; MMC_DIMM_SIZE_SHFT(_dimm))
DECL|macro|MMC_DIMM_WIDTH_SHFT
mdefine_line|#define MMC_DIMM_WIDTH_SHFT(_dimm)    ((_dimm &lt;&lt; 3) + 3)
DECL|macro|MMC_DIMM_WIDTH_MASK
mdefine_line|#define MMC_DIMM_WIDTH_MASK(_dimm)    (UINT64_CAST 0x1 &lt;&lt; MMC_DIMM_WIDTH_SHFT(_dimm))
DECL|macro|MMC_DIMM_BANKS_SHFT
mdefine_line|#define MMC_DIMM_BANKS_SHFT(_dimm)    (_dimm &lt;&lt; 3)
DECL|macro|MMC_DIMM_BANKS_MASK
mdefine_line|#define MMC_DIMM_BANKS_MASK(_dimm)    (UINT64_CAST 0x3 &lt;&lt; MMC_DIMM_BANKS_SHFT(_dimm))
DECL|macro|MMC_BANK_ALL_MASK
mdefine_line|#define MMC_BANK_ALL_MASK&t;0xffffffffLL
multiline_comment|/* Default values for write-only bits in MD_MEMORY_CONFIG */
DECL|macro|MMC_DEFAULT_BITS
mdefine_line|#define MMC_DEFAULT_BITS&t;(UINT64_CAST 0x7 &lt;&lt; MMC_MB_NEG_EDGE_SHFT)
multiline_comment|/* MD_MB_ECC_CONFIG fields */
DECL|macro|MEC_IGNORE_ECC
mdefine_line|#define MEC_IGNORE_ECC&t;&t;(UINT64_CAST 0x1 &lt;&lt; 0)
multiline_comment|/* MD_BIST_DATA fields */
DECL|macro|MBD_BIST_WRITE
mdefine_line|#define MBD_BIST_WRITE&t;&t;(UINT64_CAST 1 &lt;&lt; 7)
DECL|macro|MBD_BIST_CYCLE
mdefine_line|#define MBD_BIST_CYCLE&t;&t;(UINT64_CAST 1 &lt;&lt; 6)
DECL|macro|MBD_BIST_BYTE
mdefine_line|#define MBD_BIST_BYTE&t;&t;(UINT64_CAST 1 &lt;&lt; 5)
DECL|macro|MBD_BIST_NIBBLE
mdefine_line|#define MBD_BIST_NIBBLE&t;&t;(UINT64_CAST 1 &lt;&lt; 4)
DECL|macro|MBD_BIST_DATA_MASK
mdefine_line|#define MBD_BIST_DATA_MASK&t;0xf
multiline_comment|/* MD_BIST_CTL fields */
DECL|macro|MBC_DIMM_SHFT
mdefine_line|#define MBC_DIMM_SHFT&t;&t;5
DECL|macro|MBC_DIMM_MASK
mdefine_line|#define MBC_DIMM_MASK&t;&t;(UINT64_CAST 0x3 &lt;&lt; 5)
DECL|macro|MBC_BANK_SHFT
mdefine_line|#define MBC_BANK_SHFT&t;&t;4
DECL|macro|MBC_BANK_MASK
mdefine_line|#define MBC_BANK_MASK&t;&t;(UINT64_CAST 0x1 &lt;&lt; 4)
DECL|macro|MBC_BIST_RESET
mdefine_line|#define MBC_BIST_RESET&t;&t;(UINT64_CAST 0x1 &lt;&lt; 2)
DECL|macro|MBC_BIST_STOP
mdefine_line|#define MBC_BIST_STOP&t;&t;(UINT64_CAST 0x1 &lt;&lt; 1)
DECL|macro|MBC_BIST_START
mdefine_line|#define MBC_BIST_START&t;&t;(UINT64_CAST 0x1 &lt;&lt; 0)
DECL|macro|MBC_GO
mdefine_line|#define MBC_GO(dimm, bank) &bslash;&n;    (((dimm) &lt;&lt; MBC_DIMM_SHFT) &amp; MBC_DIMM_MASK | &bslash;&n;     ((bank) &lt;&lt; MBC_BANK_SHFT) &amp; MBC_BANK_MASK | &bslash;&n;     MBC_BIST_START)
multiline_comment|/* MD_BIST_STATUS fields */
DECL|macro|MBS_BIST_DONE
mdefine_line|#define MBS_BIST_DONE&t;&t;(UINT64_CAST 0X1 &lt;&lt; 1)
DECL|macro|MBS_BIST_PASSED
mdefine_line|#define MBS_BIST_PASSED&t;&t;(UINT64_CAST 0X1 &lt;&lt; 0)
multiline_comment|/* MD_JUNK_BUS_TIMING fields */
DECL|macro|MJT_SYNERGY_ENABLE_SHFT
mdefine_line|#define MJT_SYNERGY_ENABLE_SHFT&t;40
DECL|macro|MJT_SYNERGY_ENABLE_MASK
mdefine_line|#define MJT_SYNERGY_ENABLE_MASK&t;(UINT64_CAST 0Xff &lt;&lt; MJT_SYNERGY_ENABLE_SHFT)
DECL|macro|MJT_SYNERGY_SETUP_SHFT
mdefine_line|#define MJT_SYNERGY_SETUP_SHFT&t;32
DECL|macro|MJT_SYNERGY_SETUP_MASK
mdefine_line|#define MJT_SYNERGY_SETUP_MASK&t;(UINT64_CAST 0Xff &lt;&lt; MJT_SYNERGY_SETUP_SHFT)
DECL|macro|MJT_UART_ENABLE_SHFT
mdefine_line|#define MJT_UART_ENABLE_SHFT&t;24
DECL|macro|MJT_UART_ENABLE_MASK
mdefine_line|#define MJT_UART_ENABLE_MASK&t;(UINT64_CAST 0Xff &lt;&lt; MJT_UART_ENABLE_SHFT)
DECL|macro|MJT_UART_SETUP_SHFT
mdefine_line|#define MJT_UART_SETUP_SHFT&t;16
DECL|macro|MJT_UART_SETUP_MASK
mdefine_line|#define MJT_UART_SETUP_MASK&t;(UINT64_CAST 0Xff &lt;&lt; MJT_UART_SETUP_SHFT)
DECL|macro|MJT_FPROM_ENABLE_SHFT
mdefine_line|#define MJT_FPROM_ENABLE_SHFT&t;8
DECL|macro|MJT_FPROM_ENABLE_MASK
mdefine_line|#define MJT_FPROM_ENABLE_MASK&t;(UINT64_CAST 0Xff &lt;&lt; MJT_FPROM_ENABLE_SHFT)
DECL|macro|MJT_FPROM_SETUP_SHFT
mdefine_line|#define MJT_FPROM_SETUP_SHFT&t;0
DECL|macro|MJT_FPROM_SETUP_MASK
mdefine_line|#define MJT_FPROM_SETUP_MASK&t;(UINT64_CAST 0Xff &lt;&lt; MJT_FPROM_SETUP_SHFT)
DECL|macro|MEM_ERROR_VALID_CE
mdefine_line|#define MEM_ERROR_VALID_CE      1
multiline_comment|/* MD_FANDOP_CAC_STAT0, MD_FANDOP_CAC_STAT1 addr field shift */
DECL|macro|MFC_ADDR_SHFT
mdefine_line|#define MFC_ADDR_SHFT&t;&t;6
macro_line|#endif  /* _ASM_IA64_SN_SN1_HUBMD_NEXT_H */
eof
