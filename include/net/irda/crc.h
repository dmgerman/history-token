multiline_comment|/*********************************************************************&n; *                &n; * Filename:      crc.h&n; * Version:       &n; * Description:   CRC routines&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Mon Aug  4 20:40:53 1997&n; * Modified at:   Sun May  2 20:25:23 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; ********************************************************************/
macro_line|#ifndef IRDA_CRC_H
DECL|macro|IRDA_CRC_H
mdefine_line|#define IRDA_CRC_H
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|INIT_FCS
mdefine_line|#define INIT_FCS  0xffff   /* Initial FCS value */
DECL|macro|GOOD_FCS
mdefine_line|#define GOOD_FCS  0xf0b8   /* Good final FCS value */
r_extern
id|__u16
r_const
id|irda_crc16_table
(braket
)braket
suffix:semicolon
multiline_comment|/* Recompute the FCS with one more character appended. */
DECL|function|irda_fcs
r_static
r_inline
id|__u16
id|irda_fcs
c_func
(paren
id|__u16
id|fcs
comma
id|__u8
id|c
)paren
(brace
r_return
(paren
(paren
(paren
id|fcs
)paren
op_rshift
l_int|8
)paren
op_xor
id|irda_crc16_table
(braket
(paren
(paren
id|fcs
)paren
op_xor
(paren
id|c
)paren
)paren
op_amp
l_int|0xff
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Recompute the FCS with len bytes appended. */
r_int
r_int
id|crc_calc
c_func
(paren
id|__u16
id|fcs
comma
id|__u8
r_const
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
macro_line|#endif
eof
