multiline_comment|/* Rubin encoder/decoder header       */
multiline_comment|/* work started at   : aug   3, 1994  */
multiline_comment|/* last modification : aug  15, 1994  */
multiline_comment|/* $Id: compr_rubin.h,v 1.6 2002/01/25 01:49:26 dwmw2 Exp $ */
macro_line|#include &quot;pushpull.h&quot;
DECL|macro|RUBIN_REG_SIZE
mdefine_line|#define RUBIN_REG_SIZE   16
DECL|macro|UPPER_BIT_RUBIN
mdefine_line|#define UPPER_BIT_RUBIN    (((long) 1)&lt;&lt;(RUBIN_REG_SIZE-1))
DECL|macro|LOWER_BITS_RUBIN
mdefine_line|#define LOWER_BITS_RUBIN   ((((long) 1)&lt;&lt;(RUBIN_REG_SIZE-1))-1)
DECL|struct|rubin_state
r_struct
id|rubin_state
(brace
DECL|member|p
r_int
r_int
id|p
suffix:semicolon
DECL|member|q
r_int
r_int
id|q
suffix:semicolon
DECL|member|rec_q
r_int
r_int
id|rec_q
suffix:semicolon
DECL|member|bit_number
r_int
id|bit_number
suffix:semicolon
DECL|member|pp
r_struct
id|pushpull
id|pp
suffix:semicolon
DECL|member|bit_divider
r_int
id|bit_divider
suffix:semicolon
DECL|member|bits
r_int
id|bits
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
eof
