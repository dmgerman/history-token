multiline_comment|/*********************************************************************&n; *                &n; * Filename:      crc.h&n; * Version:       &n; * Description:   CRC routines&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Mon Aug  4 20:40:53 1997&n; * Modified at:   Sun May  2 20:25:23 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; ********************************************************************/
macro_line|#ifndef IRDA_CRC_H
DECL|macro|IRDA_CRC_H
mdefine_line|#define IRDA_CRC_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/crc-ccitt.h&gt;
DECL|macro|INIT_FCS
mdefine_line|#define INIT_FCS  0xffff   /* Initial FCS value */
DECL|macro|GOOD_FCS
mdefine_line|#define GOOD_FCS  0xf0b8   /* Good final FCS value */
multiline_comment|/* Recompute the FCS with one more character appended. */
DECL|macro|irda_fcs
mdefine_line|#define irda_fcs(fcs, c) crc_ccitt_byte(fcs, c)
multiline_comment|/* Recompute the FCS with len bytes appended. */
DECL|macro|irda_calc_crc16
mdefine_line|#define irda_calc_crc16(fcs, buf, len) crc_ccitt(fcs, buf, len)
macro_line|#endif
eof
