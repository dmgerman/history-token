multiline_comment|/*&n; * include/asm-v850/v850e_utils.h -- Utility functions associated with&n; *&t;V850E CPUs&n; *&n; *  Copyright (C) 2001,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_V850E_UTILS_H__
DECL|macro|__V850_V850E_UTILS_H__
mdefine_line|#define __V850_V850E_UTILS_H__
multiline_comment|/* Calculate counter clock-divider and count values to attain the&n;   desired frequency RATE from the base frequency BASE_FREQ.  The&n;   counter is expected to have a clock-divider, which can divide the&n;   system cpu clock by a power of two value from MIN_DIVLOG2 to&n;   MAX_DIV_LOG2, and a word-size of COUNTER_SIZE bits (the counter&n;   counts up and resets whenever it&squot;s equal to the compare register,&n;   generating an interrupt or whatever when it does so).  The returned&n;   values are: *DIVLOG2 -- log2 of the desired clock divider and *COUNT&n;   -- the counter compare value to use.  Returns true if it was possible&n;   to find a reasonable value, otherwise false (and the other return&n;   values will be set to be as good as possible).  */
r_extern
r_int
id|calc_counter_params
(paren
r_int
r_int
id|base_freq
comma
r_int
r_int
id|rate
comma
r_int
id|min_divlog2
comma
r_int
id|max_divlog2
comma
r_int
id|counter_size
comma
r_int
op_star
id|divlog2
comma
r_int
op_star
id|count
)paren
suffix:semicolon
macro_line|#endif /* __V850_V850E_UTILS_H__ */
eof
