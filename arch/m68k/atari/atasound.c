multiline_comment|/*&n; * linux/arch/m68k/atari/atasound.c&n; *&n; * ++Geert: Moved almost all stuff to linux/drivers/sound/&n; *&n; * The author of atari_nosound, atari_mksound and atari_microwire_cmd is&n; * unknown. (++roman: That&squot;s me... :-)&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; *&n; * 1998-05-31 ++andreas: atari_mksound rewritten to always use the envelope,&n; *&t;&t;&t; no timer, atari_nosound removed.&n; *&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/atarihw.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/atariints.h&gt;
multiline_comment|/*&n; * stuff from the old atasound.c&n; */
DECL|function|atari_microwire_cmd
r_void
id|atari_microwire_cmd
(paren
r_int
id|cmd
)paren
(brace
id|tt_microwire.mask
op_assign
l_int|0x7ff
suffix:semicolon
id|tt_microwire.data
op_assign
id|MW_LM1992_ADDR
op_or
id|cmd
suffix:semicolon
multiline_comment|/* Busy wait for data being completely sent :-( */
r_while
c_loop
(paren
id|tt_microwire.mask
op_ne
l_int|0x7ff
)paren
(brace
suffix:semicolon
)brace
)brace
multiline_comment|/* PSG base frequency */
DECL|macro|PSG_FREQ
mdefine_line|#define&t;PSG_FREQ&t;125000
multiline_comment|/* PSG envelope base frequency times 10 */
DECL|macro|PSG_ENV_FREQ_10
mdefine_line|#define PSG_ENV_FREQ_10&t;78125
DECL|function|atari_mksound
r_void
id|atari_mksound
(paren
r_int
r_int
id|hz
comma
r_int
r_int
id|ticks
)paren
(brace
multiline_comment|/* Generates sound of some frequency for some number of clock&n;&t;   ticks.  */
r_int
r_int
id|flags
suffix:semicolon
r_int
r_char
id|tmp
suffix:semicolon
r_int
id|period
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Disable generator A in mixer control.  */
id|sound_ym.rd_data_reg_sel
op_assign
l_int|7
suffix:semicolon
id|tmp
op_assign
id|sound_ym.rd_data_reg_sel
suffix:semicolon
id|tmp
op_or_assign
l_int|011
suffix:semicolon
id|sound_ym.wd_data
op_assign
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|hz
)paren
(brace
multiline_comment|/* Convert from frequency value to PSG period value (base&n;&t;       frequency 125 kHz).  */
id|period
op_assign
id|PSG_FREQ
op_div
id|hz
suffix:semicolon
r_if
c_cond
(paren
id|period
OG
l_int|0xfff
)paren
id|period
op_assign
l_int|0xfff
suffix:semicolon
multiline_comment|/* Set generator A frequency to hz.  */
id|sound_ym.rd_data_reg_sel
op_assign
l_int|0
suffix:semicolon
id|sound_ym.wd_data
op_assign
id|period
op_amp
l_int|0xff
suffix:semicolon
id|sound_ym.rd_data_reg_sel
op_assign
l_int|1
suffix:semicolon
id|sound_ym.wd_data
op_assign
(paren
id|period
op_rshift
l_int|8
)paren
op_amp
l_int|0xf
suffix:semicolon
r_if
c_cond
(paren
id|ticks
)paren
(brace
multiline_comment|/* Set length of envelope (max 8 sec).  */
r_int
id|length
op_assign
(paren
id|ticks
op_star
id|PSG_ENV_FREQ_10
)paren
op_div
id|HZ
op_div
l_int|10
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
l_int|0xffff
)paren
id|length
op_assign
l_int|0xffff
suffix:semicolon
id|sound_ym.rd_data_reg_sel
op_assign
l_int|11
suffix:semicolon
id|sound_ym.wd_data
op_assign
id|length
op_amp
l_int|0xff
suffix:semicolon
id|sound_ym.rd_data_reg_sel
op_assign
l_int|12
suffix:semicolon
id|sound_ym.wd_data
op_assign
id|length
op_rshift
l_int|8
suffix:semicolon
multiline_comment|/* Envelope form: max -&gt; min single.  */
id|sound_ym.rd_data_reg_sel
op_assign
l_int|13
suffix:semicolon
id|sound_ym.wd_data
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Use envelope for generator A.  */
id|sound_ym.rd_data_reg_sel
op_assign
l_int|8
suffix:semicolon
id|sound_ym.wd_data
op_assign
l_int|0x10
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Set generator A level to maximum, no envelope.  */
id|sound_ym.rd_data_reg_sel
op_assign
l_int|8
suffix:semicolon
id|sound_ym.wd_data
op_assign
l_int|15
suffix:semicolon
)brace
multiline_comment|/* Turn on generator A in mixer control.  */
id|sound_ym.rd_data_reg_sel
op_assign
l_int|7
suffix:semicolon
id|tmp
op_and_assign
op_complement
l_int|1
suffix:semicolon
id|sound_ym.wd_data
op_assign
id|tmp
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
eof
