multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_HWCNTRS_H
DECL|macro|_ASM_SN_HWCNTRS_H
mdefine_line|#define _ASM_SN_HWCNTRS_H
DECL|typedef|refcnt_t
r_typedef
r_uint64
id|refcnt_t
suffix:semicolon
DECL|macro|SN0_REFCNT_MAX_COUNTERS
mdefine_line|#define SN0_REFCNT_MAX_COUNTERS 64
DECL|struct|sn0_refcnt_set
r_typedef
r_struct
id|sn0_refcnt_set
(brace
DECL|member|refcnt
id|refcnt_t
id|refcnt
(braket
id|SN0_REFCNT_MAX_COUNTERS
)braket
suffix:semicolon
DECL|member|flags
r_uint64
id|flags
suffix:semicolon
DECL|member|reserved
r_uint64
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|sn0_refcnt_set_t
)brace
id|sn0_refcnt_set_t
suffix:semicolon
DECL|struct|sn0_refcnt_buf
r_typedef
r_struct
id|sn0_refcnt_buf
(brace
DECL|member|refcnt_set
id|sn0_refcnt_set_t
id|refcnt_set
suffix:semicolon
DECL|member|paddr
r_uint64
id|paddr
suffix:semicolon
DECL|member|page_size
r_uint64
id|page_size
suffix:semicolon
DECL|member|cnodeid
id|cnodeid_t
id|cnodeid
suffix:semicolon
multiline_comment|/* cnodeid + pad[3] use 64 bits */
DECL|member|pad
r_uint16
id|pad
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|reserved
r_uint64
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|sn0_refcnt_buf_t
)brace
id|sn0_refcnt_buf_t
suffix:semicolon
DECL|struct|sn0_refcnt_args
r_typedef
r_struct
id|sn0_refcnt_args
(brace
DECL|member|vaddr
r_uint64
id|vaddr
suffix:semicolon
DECL|member|len
r_uint64
id|len
suffix:semicolon
DECL|member|buf
id|sn0_refcnt_buf_t
op_star
id|buf
suffix:semicolon
DECL|member|reserved
r_uint64
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|sn0_refcnt_args_t
)brace
id|sn0_refcnt_args_t
suffix:semicolon
multiline_comment|/*&n; * Info needed by the user level program&n; * to mmap the refcnt buffer&n; */
DECL|macro|RCB_INFO_GET
mdefine_line|#define RCB_INFO_GET  1
DECL|macro|RCB_SLOT_GET
mdefine_line|#define RCB_SLOT_GET  2
DECL|struct|rcb_info
r_typedef
r_struct
id|rcb_info
(brace
DECL|member|rcb_len
r_uint64
id|rcb_len
suffix:semicolon
multiline_comment|/* total refcnt buffer len in bytes */
DECL|member|rcb_sw_sets
r_int
id|rcb_sw_sets
suffix:semicolon
multiline_comment|/* number of sw counter sets in buffer */
DECL|member|rcb_sw_counters_per_set
r_int
id|rcb_sw_counters_per_set
suffix:semicolon
multiline_comment|/* sw counters per set -- numnodes */
DECL|member|rcb_sw_counter_size
r_int
id|rcb_sw_counter_size
suffix:semicolon
multiline_comment|/* sizeof(refcnt_t) -- size of sw cntr */
DECL|member|rcb_base_pages
r_int
id|rcb_base_pages
suffix:semicolon
multiline_comment|/* number of base pages in node */
DECL|member|rcb_base_page_size
r_int
id|rcb_base_page_size
suffix:semicolon
multiline_comment|/* sw base page size */
DECL|member|rcb_base_paddr
r_uint64
id|rcb_base_paddr
suffix:semicolon
multiline_comment|/* base physical address for this node */
DECL|member|rcb_cnodeid
r_int
id|rcb_cnodeid
suffix:semicolon
multiline_comment|/* cnodeid for this node */
DECL|member|rcb_granularity
r_int
id|rcb_granularity
suffix:semicolon
multiline_comment|/* hw page size used for counter sets */
DECL|member|rcb_hw_counter_max
id|uint
id|rcb_hw_counter_max
suffix:semicolon
multiline_comment|/* max hwcounter count (width mask) */
DECL|member|rcb_diff_threshold
r_int
id|rcb_diff_threshold
suffix:semicolon
multiline_comment|/* current node differential threshold */
DECL|member|rcb_abs_threshold
r_int
id|rcb_abs_threshold
suffix:semicolon
multiline_comment|/* current node absolute threshold */
DECL|member|rcb_num_slots
r_int
id|rcb_num_slots
suffix:semicolon
multiline_comment|/* physmem slots */
DECL|member|rcb_reserved
r_int
id|rcb_reserved
(braket
l_int|512
)braket
suffix:semicolon
DECL|typedef|rcb_info_t
)brace
id|rcb_info_t
suffix:semicolon
DECL|struct|rcb_slot
r_typedef
r_struct
id|rcb_slot
(brace
DECL|member|base
r_uint64
id|base
suffix:semicolon
DECL|member|size
r_uint64
id|size
suffix:semicolon
DECL|typedef|rcb_slot_t
)brace
id|rcb_slot_t
suffix:semicolon
macro_line|#if defined(__KERNEL__)
singleline_comment|// #include &lt;sys/immu.h&gt;
DECL|struct|sn0_refcnt_args_32
r_typedef
r_struct
id|sn0_refcnt_args_32
(brace
DECL|member|vaddr
r_uint64
id|vaddr
suffix:semicolon
DECL|member|len
r_uint64
id|len
suffix:semicolon
DECL|member|buf
id|app32_ptr_t
id|buf
suffix:semicolon
DECL|member|reserved
r_uint64
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|sn0_refcnt_args_32_t
)brace
id|sn0_refcnt_args_32_t
suffix:semicolon
multiline_comment|/* Defines and Macros  */
multiline_comment|/* A set of reference counts are for 4k bytes of physical memory */
DECL|macro|NBPREFCNTP
mdefine_line|#define&t;NBPREFCNTP&t;0x1000&t;
DECL|macro|BPREFCNTPSHIFT
mdefine_line|#define&t;BPREFCNTPSHIFT&t;12
DECL|macro|bytes_to_refcntpages
mdefine_line|#define bytes_to_refcntpages(x)&t;(((__psunsigned_t)(x)+(NBPREFCNTP-1))&gt;&gt;BPREFCNTPSHIFT)
DECL|macro|refcntpage_offset
mdefine_line|#define refcntpage_offset(x)&t;((__psunsigned_t)(x)&amp;((NBPP-1)&amp;~(NBPREFCNTP-1)))
DECL|macro|align_to_refcntpage
mdefine_line|#define align_to_refcntpage(x)&t;((__psunsigned_t)(x)&amp;(~(NBPREFCNTP-1)))
r_extern
r_void
id|migr_refcnt_read
c_func
(paren
id|sn0_refcnt_buf_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|migr_refcnt_read_extended
c_func
(paren
id|sn0_refcnt_buf_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|migr_refcnt_enabled
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_SN_HWCNTRS_H */
eof
