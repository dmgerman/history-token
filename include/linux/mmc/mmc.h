multiline_comment|/*&n; *  linux/include/linux/mmc/mmc.h&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef MMC_H
DECL|macro|MMC_H
mdefine_line|#define MMC_H
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/device.h&gt;
r_struct
id|request
suffix:semicolon
r_struct
id|mmc_data
suffix:semicolon
r_struct
id|mmc_request
suffix:semicolon
DECL|struct|mmc_command
r_struct
id|mmc_command
(brace
DECL|member|opcode
id|u32
id|opcode
suffix:semicolon
DECL|member|arg
id|u32
id|arg
suffix:semicolon
DECL|member|resp
id|u32
id|resp
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* expected response type */
DECL|macro|MMC_RSP_NONE
mdefine_line|#define MMC_RSP_NONE&t;(0 &lt;&lt; 0)
DECL|macro|MMC_RSP_SHORT
mdefine_line|#define MMC_RSP_SHORT&t;(1 &lt;&lt; 0)
DECL|macro|MMC_RSP_LONG
mdefine_line|#define MMC_RSP_LONG&t;(2 &lt;&lt; 0)
DECL|macro|MMC_RSP_MASK
mdefine_line|#define MMC_RSP_MASK&t;(3 &lt;&lt; 0)
DECL|macro|MMC_RSP_CRC
mdefine_line|#define MMC_RSP_CRC&t;(1 &lt;&lt; 3)&t;&t;/* expect valid crc */
DECL|macro|MMC_RSP_BUSY
mdefine_line|#define MMC_RSP_BUSY&t;(1 &lt;&lt; 4)&t;&t;/* card may send busy */
multiline_comment|/*&n; * These are the response types, and correspond to valid bit&n; * patterns of the above flags.  One additional valid pattern&n; * is all zeros, which means we don&squot;t expect a response.&n; */
DECL|macro|MMC_RSP_R1
mdefine_line|#define MMC_RSP_R1&t;(MMC_RSP_SHORT|MMC_RSP_CRC)
DECL|macro|MMC_RSP_R1B
mdefine_line|#define MMC_RSP_R1B&t;(MMC_RSP_SHORT|MMC_RSP_CRC|MMC_RSP_BUSY)
DECL|macro|MMC_RSP_R2
mdefine_line|#define MMC_RSP_R2&t;(MMC_RSP_LONG|MMC_RSP_CRC)
DECL|macro|MMC_RSP_R3
mdefine_line|#define MMC_RSP_R3&t;(MMC_RSP_SHORT)
DECL|member|retries
r_int
r_int
id|retries
suffix:semicolon
multiline_comment|/* max number of retries */
DECL|member|error
r_int
r_int
id|error
suffix:semicolon
multiline_comment|/* command error */
DECL|macro|MMC_ERR_NONE
mdefine_line|#define MMC_ERR_NONE&t;0
DECL|macro|MMC_ERR_TIMEOUT
mdefine_line|#define MMC_ERR_TIMEOUT&t;1
DECL|macro|MMC_ERR_BADCRC
mdefine_line|#define MMC_ERR_BADCRC&t;2
DECL|macro|MMC_ERR_FIFO
mdefine_line|#define MMC_ERR_FIFO&t;3
DECL|macro|MMC_ERR_FAILED
mdefine_line|#define MMC_ERR_FAILED&t;4
DECL|macro|MMC_ERR_INVALID
mdefine_line|#define MMC_ERR_INVALID&t;5
DECL|member|data
r_struct
id|mmc_data
op_star
id|data
suffix:semicolon
multiline_comment|/* data segment associated with cmd */
DECL|member|mrq
r_struct
id|mmc_request
op_star
id|mrq
suffix:semicolon
multiline_comment|/* assoicated request */
)brace
suffix:semicolon
DECL|struct|mmc_data
r_struct
id|mmc_data
(brace
DECL|member|timeout_ns
r_int
r_int
id|timeout_ns
suffix:semicolon
multiline_comment|/* data timeout (in ns, max 80ms) */
DECL|member|timeout_clks
r_int
r_int
id|timeout_clks
suffix:semicolon
multiline_comment|/* data timeout (in clocks) */
DECL|member|blksz_bits
r_int
r_int
id|blksz_bits
suffix:semicolon
multiline_comment|/* data block size */
DECL|member|blocks
r_int
r_int
id|blocks
suffix:semicolon
multiline_comment|/* number of blocks */
DECL|member|req
r_struct
id|request
op_star
id|req
id|__attribute__
c_func
(paren
(paren
id|deprecated
)paren
)paren
suffix:semicolon
multiline_comment|/* request structure (use the sg list instead) */
DECL|member|error
r_int
r_int
id|error
suffix:semicolon
multiline_comment|/* data error */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|macro|MMC_DATA_WRITE
mdefine_line|#define MMC_DATA_WRITE&t;(1 &lt;&lt; 8)
DECL|macro|MMC_DATA_READ
mdefine_line|#define MMC_DATA_READ&t;(1 &lt;&lt; 9)
DECL|macro|MMC_DATA_STREAM
mdefine_line|#define MMC_DATA_STREAM&t;(1 &lt;&lt; 10)
DECL|member|bytes_xfered
r_int
r_int
id|bytes_xfered
suffix:semicolon
DECL|member|stop
r_struct
id|mmc_command
op_star
id|stop
suffix:semicolon
multiline_comment|/* stop command */
DECL|member|mrq
r_struct
id|mmc_request
op_star
id|mrq
suffix:semicolon
multiline_comment|/* assoicated request */
DECL|member|sg_len
r_int
r_int
id|sg_len
suffix:semicolon
multiline_comment|/* size of scatter list */
DECL|member|sg
r_struct
id|scatterlist
op_star
id|sg
suffix:semicolon
multiline_comment|/* I/O scatter list */
)brace
suffix:semicolon
DECL|struct|mmc_request
r_struct
id|mmc_request
(brace
DECL|member|cmd
r_struct
id|mmc_command
op_star
id|cmd
suffix:semicolon
DECL|member|data
r_struct
id|mmc_data
op_star
id|data
suffix:semicolon
DECL|member|stop
r_struct
id|mmc_command
op_star
id|stop
suffix:semicolon
DECL|member|done_data
r_void
op_star
id|done_data
suffix:semicolon
multiline_comment|/* completion data */
DECL|member|done
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|mmc_request
op_star
)paren
suffix:semicolon
multiline_comment|/* completion function */
)brace
suffix:semicolon
r_struct
id|mmc_host
suffix:semicolon
r_struct
id|mmc_card
suffix:semicolon
r_extern
r_int
id|mmc_wait_for_req
c_func
(paren
r_struct
id|mmc_host
op_star
comma
r_struct
id|mmc_request
op_star
)paren
suffix:semicolon
r_extern
r_int
id|mmc_wait_for_cmd
c_func
(paren
r_struct
id|mmc_host
op_star
comma
r_struct
id|mmc_command
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__mmc_claim_host
c_func
(paren
r_struct
id|mmc_host
op_star
id|host
comma
r_struct
id|mmc_card
op_star
id|card
)paren
suffix:semicolon
DECL|function|mmc_claim_host
r_static
r_inline
r_void
id|mmc_claim_host
c_func
(paren
r_struct
id|mmc_host
op_star
id|host
)paren
(brace
id|__mmc_claim_host
c_func
(paren
id|host
comma
(paren
r_struct
id|mmc_card
op_star
)paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_extern
r_void
id|mmc_release_host
c_func
(paren
r_struct
id|mmc_host
op_star
id|host
)paren
suffix:semicolon
macro_line|#endif
eof
