multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_SN1_HUBPI_NEXT_H
DECL|macro|_ASM_SN_SN1_HUBPI_NEXT_H
mdefine_line|#define _ASM_SN_SN1_HUBPI_NEXT_H
multiline_comment|/* define for remote PI_1 space. It is always half of a node_addressspace&n; * from PI_0. The normal REMOTE_HUB space for PI registers access&n; * the PI_0 space, unless they are qualified by PI_1.&n; */
DECL|macro|PI_0
mdefine_line|#define PI_0(x)&t;&t;&t;(x)
DECL|macro|PI_1
mdefine_line|#define PI_1(x)&t;&t;&t;((x) + 0x200000)
DECL|macro|PIREG
mdefine_line|#define PIREG(x,sn)&t;&t;((sn) ? PI_1(x) : PI_0(x))
DECL|macro|PI_MIN_STACK_SIZE
mdefine_line|#define PI_MIN_STACK_SIZE 4096  /* For figuring out the size to set */
DECL|macro|PI_STACK_SIZE_SHFT
mdefine_line|#define PI_STACK_SIZE_SHFT      12      /* 4k */
DECL|macro|PI_STACKADDR_OFFSET
mdefine_line|#define PI_STACKADDR_OFFSET     (PI_ERR_STACK_ADDR_B - PI_ERR_STACK_ADDR_A)
DECL|macro|PI_ERRSTAT_OFFSET
mdefine_line|#define PI_ERRSTAT_OFFSET       (PI_ERR_STATUS0_B - PI_ERR_STATUS0_A)
DECL|macro|PI_RDCLR_OFFSET
mdefine_line|#define PI_RDCLR_OFFSET         (PI_ERR_STATUS0_A_RCLR - PI_ERR_STATUS0_A)
multiline_comment|/* these macros are correct, but fix their users to understand two PIs&n;   and 4 CPUs (slices) per bedrock */
DECL|macro|PI_INT_MASK_OFFSET
mdefine_line|#define PI_INT_MASK_OFFSET      (PI_INT_MASK0_B - PI_INT_MASK0_A)
DECL|macro|PI_INT_SET_OFFSET
mdefine_line|#define PI_INT_SET_OFFSET       (PI_CC_PEND_CLR_B - PI_CC_PEND_CLR_A)
DECL|macro|PI_NMI_OFFSET
mdefine_line|#define PI_NMI_OFFSET&t;&t;(PI_NMI_B - PI_NMI_A)
DECL|macro|ERR_STACK_SIZE_BYTES
mdefine_line|#define ERR_STACK_SIZE_BYTES(_sz) &bslash;&n;       ((_sz) ? (PI_MIN_STACK_SIZE &lt;&lt; ((_sz) - 1)) : 0)
DECL|macro|PI_CRB_STS_P
mdefine_line|#define PI_CRB_STS_P&t;(1 &lt;&lt; 9) &t;/* &quot;P&quot; (partial word read/write) bit */
DECL|macro|PI_CRB_STS_V
mdefine_line|#define PI_CRB_STS_V&t;(1 &lt;&lt; 8)&t;/* &quot;V&quot; (valid) bit */
DECL|macro|PI_CRB_STS_R
mdefine_line|#define PI_CRB_STS_R&t;(1 &lt;&lt; 7)&t;/* &quot;R&quot; (response data sent to CPU) */
DECL|macro|PI_CRB_STS_A
mdefine_line|#define PI_CRB_STS_A&t;(1 &lt;&lt; 6)&t;/* &quot;A&quot; (data ack. received) bit */
DECL|macro|PI_CRB_STS_W
mdefine_line|#define PI_CRB_STS_W&t;(1 &lt;&lt; 5)&t;/* &quot;W&quot; (waiting for write compl.) */
DECL|macro|PI_CRB_STS_H
mdefine_line|#define PI_CRB_STS_H&t;(1 &lt;&lt; 4)&t;/* &quot;H&quot; (gathering invalidates) bit */
DECL|macro|PI_CRB_STS_I
mdefine_line|#define PI_CRB_STS_I&t;(1 &lt;&lt; 3)&t;/* &quot;I&quot; (targ. inbound invalidate) */
DECL|macro|PI_CRB_STS_T
mdefine_line|#define PI_CRB_STS_T&t;(1 &lt;&lt; 2)&t;/* &quot;T&quot; (targ. inbound intervention) */
DECL|macro|PI_CRB_STS_E
mdefine_line|#define PI_CRB_STS_E&t;(0x3)&t;&t;/* &quot;E&quot; (coherent read type) */
multiline_comment|/* When the &quot;P&quot; bit is set in the sk_crb_sts field of an error stack&n; * entry, the &quot;R,&quot; &quot;A,&quot; &quot;H,&quot; and &quot;I&quot; bits are actually bits 6..3 of&n; * the address.  This macro extracts those address bits and shifts&n; * them to their proper positions, ready to be ORed in to the rest of&n; * the address (which is calculated as sk_addr &lt;&lt; 7).&n; */
DECL|macro|PI_CRB_STS_ADDR_BITS
mdefine_line|#define PI_CRB_STS_ADDR_BITS(sts) &bslash;&n;    ((sts) &amp; (PI_CRB_STS_I | PI_CRB_STS_H) | &bslash;&n;     ((sts) &amp; (PI_CRB_STS_A | PI_CRB_STS_R)) &gt;&gt; 1)
macro_line|#ifdef _LANGUAGE_C
multiline_comment|/*&n; * format of error stack and error status registers.&n; */
macro_line|#ifdef LITTLE_ENDIAN
DECL|struct|err_stack_format
r_struct
id|err_stack_format
(brace
DECL|member|sk_err_type
r_uint64
id|sk_err_type
suffix:colon
l_int|3
comma
multiline_comment|/* error type        */
DECL|member|sk_suppl
id|sk_suppl
suffix:colon
l_int|3
comma
multiline_comment|/* lowest 3 bit of supplemental */
DECL|member|sk_t5_req
id|sk_t5_req
suffix:colon
l_int|3
comma
multiline_comment|/* RRB T5 request number */
DECL|member|sk_crb_num
id|sk_crb_num
suffix:colon
l_int|3
comma
multiline_comment|/* WRB (0 to 7) or RRB (0 to 4) */
DECL|member|sk_rw_rb
id|sk_rw_rb
suffix:colon
l_int|1
comma
multiline_comment|/* RRB == 0, WRB == 1 */
DECL|member|sk_crb_sts
id|sk_crb_sts
suffix:colon
l_int|10
comma
multiline_comment|/* status from RRB or WRB */
DECL|member|sk_cmd
id|sk_cmd
suffix:colon
l_int|8
comma
multiline_comment|/* message command */
DECL|member|sk_addr
id|sk_addr
suffix:colon
l_int|33
suffix:semicolon
multiline_comment|/* address */
)brace
suffix:semicolon
macro_line|#else
DECL|struct|err_stack_format
r_struct
id|err_stack_format
(brace
DECL|member|sk_addr
r_uint64
id|sk_addr
suffix:colon
l_int|33
comma
multiline_comment|/* address */
DECL|member|sk_cmd
id|sk_cmd
suffix:colon
l_int|8
comma
multiline_comment|/* message command */
DECL|member|sk_crb_sts
id|sk_crb_sts
suffix:colon
l_int|10
comma
multiline_comment|/* status from RRB or WRB */
DECL|member|sk_rw_rb
id|sk_rw_rb
suffix:colon
l_int|1
comma
multiline_comment|/* RRB == 0, WRB == 1 */
DECL|member|sk_crb_num
id|sk_crb_num
suffix:colon
l_int|3
comma
multiline_comment|/* WRB (0 to 7) or RRB (0 to 4) */
DECL|member|sk_t5_req
id|sk_t5_req
suffix:colon
l_int|3
comma
multiline_comment|/* RRB T5 request number */
DECL|member|sk_suppl
id|sk_suppl
suffix:colon
l_int|3
comma
multiline_comment|/* lowest 3 bit of supplemental */
DECL|member|sk_err_type
id|sk_err_type
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* error type&t;*/
)brace
suffix:semicolon
macro_line|#endif
DECL|union|pi_err_stack
r_typedef
r_union
id|pi_err_stack
(brace
DECL|member|pi_stk_word
r_uint64
id|pi_stk_word
suffix:semicolon
DECL|member|pi_stk_fmt
r_struct
id|err_stack_format
id|pi_stk_fmt
suffix:semicolon
DECL|typedef|pi_err_stack_t
)brace
id|pi_err_stack_t
suffix:semicolon
multiline_comment|/* Simplified version of pi_err_status0_a_u_t (PI_ERR_STATUS0_A) */
macro_line|#ifdef LITTLE_ENDIAN
DECL|struct|err_status0_format
r_struct
id|err_status0_format
(brace
DECL|member|s0_err_type
r_uint64
id|s0_err_type
suffix:colon
l_int|3
comma
multiline_comment|/* Encoded error cause */
DECL|member|s0_proc_req_num
id|s0_proc_req_num
suffix:colon
l_int|3
comma
multiline_comment|/* Request number for RRB only */
DECL|member|s0_supplemental
id|s0_supplemental
suffix:colon
l_int|11
comma
multiline_comment|/* ncoming message sup field */
DECL|member|s0_cmd
id|s0_cmd
suffix:colon
l_int|8
comma
multiline_comment|/* Incoming message command */
DECL|member|s0_addr
id|s0_addr
suffix:colon
l_int|37
comma
multiline_comment|/* Address */
DECL|member|s0_over_run
id|s0_over_run
suffix:colon
l_int|1
comma
multiline_comment|/* Subsequent errors spooled */
DECL|member|s0_valid
id|s0_valid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* error is valid */
)brace
suffix:semicolon
macro_line|#else
DECL|struct|err_status0_format
r_struct
id|err_status0_format
(brace
DECL|member|s0_valid
r_uint64
id|s0_valid
suffix:colon
l_int|1
comma
multiline_comment|/* error is valid */
DECL|member|s0_over_run
id|s0_over_run
suffix:colon
l_int|1
comma
multiline_comment|/* Subsequent errors spooled */
DECL|member|s0_addr
id|s0_addr
suffix:colon
l_int|37
comma
multiline_comment|/* Address */
DECL|member|s0_cmd
id|s0_cmd
suffix:colon
l_int|8
comma
multiline_comment|/* Incoming message command */
DECL|member|s0_supplemental
id|s0_supplemental
suffix:colon
l_int|11
comma
multiline_comment|/* ncoming message sup field */
DECL|member|s0_proc_req_num
id|s0_proc_req_num
suffix:colon
l_int|3
comma
multiline_comment|/* Request number for RRB only */
DECL|member|s0_err_type
id|s0_err_type
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Encoded error cause */
)brace
suffix:semicolon
macro_line|#endif
DECL|union|pi_err_stat0
r_typedef
r_union
id|pi_err_stat0
(brace
DECL|member|pi_stat0_word
r_uint64
id|pi_stat0_word
suffix:semicolon
DECL|member|pi_stat0_fmt
r_struct
id|err_status0_format
id|pi_stat0_fmt
suffix:semicolon
DECL|typedef|pi_err_stat0_t
)brace
id|pi_err_stat0_t
suffix:semicolon
multiline_comment|/* Simplified version of pi_err_status1_a_u_t (PI_ERR_STATUS1_A) */
macro_line|#ifdef LITTLE_ENDIAN
DECL|struct|err_status1_format
r_struct
id|err_status1_format
(brace
DECL|member|s1_spl_cnt
r_uint64
id|s1_spl_cnt
suffix:colon
l_int|21
comma
multiline_comment|/* number spooled to memory */
DECL|member|s1_to_cnt
id|s1_to_cnt
suffix:colon
l_int|8
comma
multiline_comment|/* crb timeout counter */
DECL|member|s1_inval_cnt
id|s1_inval_cnt
suffix:colon
l_int|10
comma
multiline_comment|/* signed invalidate counter RRB */
DECL|member|s1_crb_num
id|s1_crb_num
suffix:colon
l_int|3
comma
multiline_comment|/* WRB (0 to 7) or RRB (0 to 4) */
DECL|member|s1_rw_rb
id|s1_rw_rb
suffix:colon
l_int|1
comma
multiline_comment|/* RRB == 0, WRB == 1 */
DECL|member|s1_crb_sts
id|s1_crb_sts
suffix:colon
l_int|10
comma
multiline_comment|/* status from RRB or WRB */
DECL|member|s1_src
id|s1_src
suffix:colon
l_int|11
suffix:semicolon
multiline_comment|/* message source */
)brace
suffix:semicolon
macro_line|#else
DECL|struct|err_status1_format
r_struct
id|err_status1_format
(brace
DECL|member|s1_src
r_uint64
id|s1_src
suffix:colon
l_int|11
comma
multiline_comment|/* message source */
DECL|member|s1_crb_sts
id|s1_crb_sts
suffix:colon
l_int|10
comma
multiline_comment|/* status from RRB or WRB */
DECL|member|s1_rw_rb
id|s1_rw_rb
suffix:colon
l_int|1
comma
multiline_comment|/* RRB == 0, WRB == 1 */
DECL|member|s1_crb_num
id|s1_crb_num
suffix:colon
l_int|3
comma
multiline_comment|/* WRB (0 to 7) or RRB (0 to 4) */
DECL|member|s1_inval_cnt
id|s1_inval_cnt
suffix:colon
l_int|10
comma
multiline_comment|/* signed invalidate counter RRB */
DECL|member|s1_to_cnt
id|s1_to_cnt
suffix:colon
l_int|8
comma
multiline_comment|/* crb timeout counter */
DECL|member|s1_spl_cnt
id|s1_spl_cnt
suffix:colon
l_int|21
suffix:semicolon
multiline_comment|/* number spooled to memory */
)brace
suffix:semicolon
macro_line|#endif
DECL|union|pi_err_stat1
r_typedef
r_union
id|pi_err_stat1
(brace
DECL|member|pi_stat1_word
r_uint64
id|pi_stat1_word
suffix:semicolon
DECL|member|pi_stat1_fmt
r_struct
id|err_status1_format
id|pi_stat1_fmt
suffix:semicolon
DECL|typedef|pi_err_stat1_t
)brace
id|pi_err_stat1_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* Error stack types (sk_err_type) for reads:&t;*/
DECL|macro|PI_ERR_RD_AERR
mdefine_line|#define PI_ERR_RD_AERR&t;&t;0&t;/* Read Access Error */
DECL|macro|PI_ERR_RD_PRERR
mdefine_line|#define PI_ERR_RD_PRERR         1&t;/* Uncached Partitial Read */
DECL|macro|PI_ERR_RD_DERR
mdefine_line|#define PI_ERR_RD_DERR          2&t;/* Directory Error */
DECL|macro|PI_ERR_RD_TERR
mdefine_line|#define PI_ERR_RD_TERR          3&t;/* read timeout */
DECL|macro|PI_ERR_RD_PERR
mdefine_line|#define PI_ERR_RD_PERR&t;&t;4&t;/* Poison Access Violation */
DECL|macro|PI_ERR_RD_NACK
mdefine_line|#define PI_ERR_RD_NACK&t;&t;5&t;/* Excessive NACKs&t;*/
DECL|macro|PI_ERR_RD_RDE
mdefine_line|#define PI_ERR_RD_RDE&t;&t;6&t;/* Response Data Error&t;*/
DECL|macro|PI_ERR_RD_PLERR
mdefine_line|#define PI_ERR_RD_PLERR&t;&t;7&t;/* Packet Length Error */
multiline_comment|/* Error stack types (sk_err_type) for writes:&t;*/
DECL|macro|PI_ERR_WR_WERR
mdefine_line|#define PI_ERR_WR_WERR          0&t;/* Write Access Error */
DECL|macro|PI_ERR_WR_PWERR
mdefine_line|#define PI_ERR_WR_PWERR         1&t;/* Uncached Write Error */
DECL|macro|PI_ERR_WR_TERR
mdefine_line|#define PI_ERR_WR_TERR          3&t;/* write timeout */
DECL|macro|PI_ERR_WR_RDE
mdefine_line|#define PI_ERR_WR_RDE&t;&t;6&t;/* Response Data Error */
DECL|macro|PI_ERR_WR_PLERR
mdefine_line|#define PI_ERR_WR_PLERR&t;&t;7&t;/* Packet Length Error */
multiline_comment|/* For backwards compatibility */
DECL|macro|PI_RT_COUNT
mdefine_line|#define PI_RT_COUNT&t;PI_RT_COUNTER    /* Real Time Counter &t;&t;    */
DECL|macro|PI_RT_EN_A
mdefine_line|#define PI_RT_EN_A&t;PI_RT_INT_EN_A   /* RT int for CPU A enable         */
DECL|macro|PI_RT_EN_B
mdefine_line|#define PI_RT_EN_B&t;PI_RT_INT_EN_B   /* RT int for CPU B enable         */
DECL|macro|PI_PROF_EN_A
mdefine_line|#define PI_PROF_EN_A&t;PI_PROF_INT_EN_A /* PROF int for CPU A enable       */
DECL|macro|PI_PROF_EN_B
mdefine_line|#define PI_PROF_EN_B&t;PI_PROF_INT_EN_B /* PROF int for CPU B enable       */
DECL|macro|PI_RT_PEND_A
mdefine_line|#define PI_RT_PEND_A    PI_RT_INT_PEND_A /* RT interrupt pending &t;    */
DECL|macro|PI_RT_PEND_B
mdefine_line|#define PI_RT_PEND_B    PI_RT_INT_PEND_B /* RT interrupt pending &t;    */
DECL|macro|PI_PROF_PEND_A
mdefine_line|#define PI_PROF_PEND_A  PI_PROF_INT_PEND_A /* Profiling interrupt pending   */
DECL|macro|PI_PROF_PEND_B
mdefine_line|#define PI_PROF_PEND_B  PI_PROF_INT_PEND_B /* Profiling interrupt pending   */
multiline_comment|/* Bits in PI_SYSAD_ERRCHK_EN */
DECL|macro|PI_SYSAD_ERRCHK_ECCGEN
mdefine_line|#define PI_SYSAD_ERRCHK_ECCGEN  0x01    /* Enable ECC generation            */
DECL|macro|PI_SYSAD_ERRCHK_QUALGEN
mdefine_line|#define PI_SYSAD_ERRCHK_QUALGEN 0x02    /* Enable data quality signal gen.  */
DECL|macro|PI_SYSAD_ERRCHK_SADP
mdefine_line|#define PI_SYSAD_ERRCHK_SADP    0x04    /* Enable SysAD parity checking     */
DECL|macro|PI_SYSAD_ERRCHK_CMDP
mdefine_line|#define PI_SYSAD_ERRCHK_CMDP    0x08    /* Enable SysCmd parity checking    */
DECL|macro|PI_SYSAD_ERRCHK_STATE
mdefine_line|#define PI_SYSAD_ERRCHK_STATE   0x10    /* Enable SysState parity checking  */
DECL|macro|PI_SYSAD_ERRCHK_QUAL
mdefine_line|#define PI_SYSAD_ERRCHK_QUAL    0x20    /* Enable data quality checking     */
DECL|macro|PI_SYSAD_CHECK_ALL
mdefine_line|#define PI_SYSAD_CHECK_ALL      0x3f    /* Generate and check all signals.  */
multiline_comment|/* CALIAS values */
DECL|macro|PI_CALIAS_SIZE_0
mdefine_line|#define PI_CALIAS_SIZE_0        0
DECL|macro|PI_CALIAS_SIZE_4K
mdefine_line|#define PI_CALIAS_SIZE_4K       1
DECL|macro|PI_CALIAS_SIZE_8K
mdefine_line|#define PI_CALIAS_SIZE_8K       2
DECL|macro|PI_CALIAS_SIZE_16K
mdefine_line|#define PI_CALIAS_SIZE_16K      3
DECL|macro|PI_CALIAS_SIZE_32K
mdefine_line|#define PI_CALIAS_SIZE_32K      4
DECL|macro|PI_CALIAS_SIZE_64K
mdefine_line|#define PI_CALIAS_SIZE_64K      5
DECL|macro|PI_CALIAS_SIZE_128K
mdefine_line|#define PI_CALIAS_SIZE_128K     6
DECL|macro|PI_CALIAS_SIZE_256K
mdefine_line|#define PI_CALIAS_SIZE_256K     7
DECL|macro|PI_CALIAS_SIZE_512K
mdefine_line|#define PI_CALIAS_SIZE_512K     8
DECL|macro|PI_CALIAS_SIZE_1M
mdefine_line|#define PI_CALIAS_SIZE_1M       9
DECL|macro|PI_CALIAS_SIZE_2M
mdefine_line|#define PI_CALIAS_SIZE_2M       10
DECL|macro|PI_CALIAS_SIZE_4M
mdefine_line|#define PI_CALIAS_SIZE_4M       11
DECL|macro|PI_CALIAS_SIZE_8M
mdefine_line|#define PI_CALIAS_SIZE_8M       12
DECL|macro|PI_CALIAS_SIZE_16M
mdefine_line|#define PI_CALIAS_SIZE_16M      13
DECL|macro|PI_CALIAS_SIZE_32M
mdefine_line|#define PI_CALIAS_SIZE_32M      14
DECL|macro|PI_CALIAS_SIZE_64M
mdefine_line|#define PI_CALIAS_SIZE_64M      15
multiline_comment|/* Fields in PI_ERR_STATUS0_[AB] */
DECL|macro|PI_ERR_ST0_VALID_MASK
mdefine_line|#define PI_ERR_ST0_VALID_MASK&t;0x8000000000000000
DECL|macro|PI_ERR_ST0_VALID_SHFT
mdefine_line|#define PI_ERR_ST0_VALID_SHFT&t;63
multiline_comment|/* Fields in PI_SPURIOUS_HDR_0 */
DECL|macro|PI_SPURIOUS_HDR_VALID_MASK
mdefine_line|#define PI_SPURIOUS_HDR_VALID_MASK&t;0x8000000000000000
DECL|macro|PI_SPURIOUS_HDR_VALID_SHFT
mdefine_line|#define PI_SPURIOUS_HDR_VALID_SHFT&t;63
multiline_comment|/* Fields in PI_NACK_CNT_A/B */
DECL|macro|PI_NACK_CNT_EN_SHFT
mdefine_line|#define PI_NACK_CNT_EN_SHFT&t;20
DECL|macro|PI_NACK_CNT_EN_MASK
mdefine_line|#define PI_NACK_CNT_EN_MASK&t;0x100000
DECL|macro|PI_NACK_CNT_MASK
mdefine_line|#define PI_NACK_CNT_MASK&t;0x0fffff
DECL|macro|PI_NACK_CNT_MAX
mdefine_line|#define PI_NACK_CNT_MAX&t;&t;0x0fffff
multiline_comment|/* Bits in PI_ERR_INT_PEND */
DECL|macro|PI_ERR_SPOOL_CMP_B
mdefine_line|#define PI_ERR_SPOOL_CMP_B&t;0x000000001&t;/* Spool end hit high water */
DECL|macro|PI_ERR_SPOOL_CMP_A
mdefine_line|#define PI_ERR_SPOOL_CMP_A&t;0x000000002
DECL|macro|PI_ERR_SPUR_MSG_B
mdefine_line|#define PI_ERR_SPUR_MSG_B&t;0x000000004&t;/* Spurious message intr.   */
DECL|macro|PI_ERR_SPUR_MSG_A
mdefine_line|#define PI_ERR_SPUR_MSG_A&t;0x000000008
DECL|macro|PI_ERR_WRB_TERR_B
mdefine_line|#define PI_ERR_WRB_TERR_B&t;0x000000010&t;/* WRB TERR&t;&t;    */
DECL|macro|PI_ERR_WRB_TERR_A
mdefine_line|#define PI_ERR_WRB_TERR_A&t;0x000000020
DECL|macro|PI_ERR_WRB_WERR_B
mdefine_line|#define PI_ERR_WRB_WERR_B&t;0x000000040&t;/* WRB WERR &t;&t;    */
DECL|macro|PI_ERR_WRB_WERR_A
mdefine_line|#define PI_ERR_WRB_WERR_A&t;0x000000080
DECL|macro|PI_ERR_SYSSTATE_B
mdefine_line|#define PI_ERR_SYSSTATE_B&t;0x000000100&t;/* SysState parity error    */
DECL|macro|PI_ERR_SYSSTATE_A
mdefine_line|#define PI_ERR_SYSSTATE_A&t;0x000000200
DECL|macro|PI_ERR_SYSAD_DATA_B
mdefine_line|#define PI_ERR_SYSAD_DATA_B&t;0x000000400&t;/* SysAD data parity error  */
DECL|macro|PI_ERR_SYSAD_DATA_A
mdefine_line|#define PI_ERR_SYSAD_DATA_A&t;0x000000800
DECL|macro|PI_ERR_SYSAD_ADDR_B
mdefine_line|#define PI_ERR_SYSAD_ADDR_B&t;0x000001000&t;/* SysAD addr parity error  */
DECL|macro|PI_ERR_SYSAD_ADDR_A
mdefine_line|#define PI_ERR_SYSAD_ADDR_A&t;0x000002000
DECL|macro|PI_ERR_SYSCMD_DATA_B
mdefine_line|#define PI_ERR_SYSCMD_DATA_B&t;0x000004000&t;/* SysCmd data parity error */
DECL|macro|PI_ERR_SYSCMD_DATA_A
mdefine_line|#define PI_ERR_SYSCMD_DATA_A&t;0x000008000
DECL|macro|PI_ERR_SYSCMD_ADDR_B
mdefine_line|#define PI_ERR_SYSCMD_ADDR_B&t;0x000010000&t;/* SysCmd addr parity error */
DECL|macro|PI_ERR_SYSCMD_ADDR_A
mdefine_line|#define PI_ERR_SYSCMD_ADDR_A&t;0x000020000
DECL|macro|PI_ERR_BAD_SPOOL_B
mdefine_line|#define PI_ERR_BAD_SPOOL_B&t;0x000040000&t;/* Error spooling to memory */
DECL|macro|PI_ERR_BAD_SPOOL_A
mdefine_line|#define PI_ERR_BAD_SPOOL_A&t;0x000080000
DECL|macro|PI_ERR_UNCAC_UNCORR_B
mdefine_line|#define PI_ERR_UNCAC_UNCORR_B&t;0x000100000&t;/* Uncached uncorrectable   */
DECL|macro|PI_ERR_UNCAC_UNCORR_A
mdefine_line|#define PI_ERR_UNCAC_UNCORR_A&t;0x000200000
DECL|macro|PI_ERR_SYSSTATE_TAG_B
mdefine_line|#define PI_ERR_SYSSTATE_TAG_B&t;0x000400000&t;/* SysState tag parity error */
DECL|macro|PI_ERR_SYSSTATE_TAG_A
mdefine_line|#define PI_ERR_SYSSTATE_TAG_A&t;0x000800000
DECL|macro|PI_ERR_MD_UNCORR
mdefine_line|#define PI_ERR_MD_UNCORR&t;0x001000000&t;/* Must be cleared in MD    */
DECL|macro|PI_ERR_SYSAD_BAD_DATA_B
mdefine_line|#define PI_ERR_SYSAD_BAD_DATA_B&t;0x002000000&t;/* SysAD Data quality bad   */
DECL|macro|PI_ERR_SYSAD_BAD_DATA_A
mdefine_line|#define PI_ERR_SYSAD_BAD_DATA_A&t;0x004000000
DECL|macro|PI_ERR_UE_CACHED_B
mdefine_line|#define PI_ERR_UE_CACHED_B&t;0x008000000&t;/* UE during cached load    */
DECL|macro|PI_ERR_UE_CACHED_A
mdefine_line|#define PI_ERR_UE_CACHED_A&t;0x010000000
DECL|macro|PI_ERR_PKT_LEN_ERR_B
mdefine_line|#define PI_ERR_PKT_LEN_ERR_B&t;0x020000000&t;/* Xbar data too long/short */
DECL|macro|PI_ERR_PKT_LEN_ERR_A
mdefine_line|#define PI_ERR_PKT_LEN_ERR_A&t;0x040000000
DECL|macro|PI_ERR_IRB_ERR_B
mdefine_line|#define PI_ERR_IRB_ERR_B&t;0x080000000&t;/* Protocol error           */
DECL|macro|PI_ERR_IRB_ERR_A
mdefine_line|#define PI_ERR_IRB_ERR_A&t;0x100000000
DECL|macro|PI_ERR_IRB_TIMEOUT_B
mdefine_line|#define PI_ERR_IRB_TIMEOUT_B&t;0x200000000&t;/* IRB_B got a timeout      */
DECL|macro|PI_ERR_IRB_TIMEOUT_A
mdefine_line|#define PI_ERR_IRB_TIMEOUT_A&t;0x400000000
DECL|macro|PI_ERR_CLEAR_ALL_A
mdefine_line|#define PI_ERR_CLEAR_ALL_A&t;0x554aaaaaa
DECL|macro|PI_ERR_CLEAR_ALL_B
mdefine_line|#define PI_ERR_CLEAR_ALL_B&t;0x2aa555555
multiline_comment|/*&n; * The following three macros define all possible error int pends. &n; */
DECL|macro|PI_FATAL_ERR_CPU_A
mdefine_line|#define PI_FATAL_ERR_CPU_A&t;(PI_ERR_IRB_TIMEOUT_A&t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_IRB_ERR_A&t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_PKT_LEN_ERR_A&t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSSTATE_TAG_A &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_BAD_SPOOL_A &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSCMD_ADDR_A &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSCMD_DATA_A &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSAD_ADDR_A &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSAD_DATA_A&t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSSTATE_A)
DECL|macro|PI_MISC_ERR_CPU_A
mdefine_line|#define PI_MISC_ERR_CPU_A&t;(PI_ERR_UE_CACHED_A&t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSAD_BAD_DATA_A| &bslash;&n;&t;&t;&t;&t; PI_ERR_UNCAC_UNCORR_A &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_WRB_WERR_A &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_WRB_TERR_A &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SPUR_MSG_A &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SPOOL_CMP_A)
DECL|macro|PI_FATAL_ERR_CPU_B
mdefine_line|#define PI_FATAL_ERR_CPU_B&t;(PI_ERR_IRB_TIMEOUT_B&t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_IRB_ERR_B&t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_PKT_LEN_ERR_B&t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSSTATE_TAG_B &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_BAD_SPOOL_B &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSCMD_ADDR_B &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSCMD_DATA_B &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSAD_ADDR_B &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSAD_DATA_B&t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSSTATE_B)
DECL|macro|PI_MISC_ERR_CPU_B
mdefine_line|#define PI_MISC_ERR_CPU_B&t;(PI_ERR_UE_CACHED_B&t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSAD_BAD_DATA_B| &bslash;&n;&t;&t;&t;&t; PI_ERR_UNCAC_UNCORR_B &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_WRB_WERR_B &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_WRB_TERR_B &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SPUR_MSG_B &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SPOOL_CMP_B)
DECL|macro|PI_ERR_GENERIC
mdefine_line|#define PI_ERR_GENERIC&t;(PI_ERR_MD_UNCORR)
multiline_comment|/* Values for PI_MAX_CRB_TIMEOUT and PI_CRB_SFACTOR */
DECL|macro|PMCT_MAX
mdefine_line|#define PMCT_MAX&t;0xff
DECL|macro|PCS_MAX
mdefine_line|#define PCS_MAX&t;&t;0xffffff
multiline_comment|/* pi_err_status0_a_u_t address shift */
DECL|macro|ERR_STAT0_ADDR_SHFT
mdefine_line|#define ERR_STAT0_ADDR_SHFT     3
multiline_comment|/* PI error read/write bit (RRB == 0, WRB == 1)&t;*/
multiline_comment|/* pi_err_status1_a_u_t.pi_err_status1_a_fld_s.esa_wrb */
DECL|macro|PI_ERR_RRB
mdefine_line|#define PI_ERR_RRB&t;0
DECL|macro|PI_ERR_WRB
mdefine_line|#define PI_ERR_WRB&t;1
multiline_comment|/* Error stack address shift, for use with pi_stk_fmt.sk_addr */
DECL|macro|ERR_STK_ADDR_SHFT
mdefine_line|#define ERR_STK_ADDR_SHFT&t;3
macro_line|#endif /* _ASM_SN_SN1_HUBPI_NEXT_H */
eof
