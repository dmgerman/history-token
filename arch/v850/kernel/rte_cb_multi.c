multiline_comment|/*&n; * include/asm-v850/rte_multi.c -- Support for Multi debugger monitor ROM&n; * &t;on Midas lab RTE-CB series of evaluation boards&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
multiline_comment|/* A table of which interrupt vectors to install, since blindly&n;   installing all of them makes the debugger stop working.  This is a&n;   list of offsets in the interrupt vector area; each entry means to&n;   copy that particular 16-byte vector.  An entry less than zero ends&n;   the table.  */
DECL|variable|multi_intv_install_table
r_static
r_int
id|multi_intv_install_table
(braket
)braket
op_assign
(brace
l_int|0x40
comma
l_int|0x50
comma
multiline_comment|/* trap vectors */
multiline_comment|/* Note -- illegal insn trap is used by the debugger.  */
l_int|0xD0
comma
l_int|0xE0
comma
l_int|0xF0
comma
multiline_comment|/* GINT1 - GINT3 */
l_int|0x240
comma
l_int|0x250
comma
l_int|0x260
comma
l_int|0x270
comma
multiline_comment|/* timer D interrupts */
l_int|0x2D0
comma
l_int|0x2E0
comma
l_int|0x2F0
comma
multiline_comment|/* UART channel 0 */
l_int|0x310
comma
l_int|0x320
comma
l_int|0x330
comma
multiline_comment|/* UART channel 1 */
l_int|0x350
comma
l_int|0x360
comma
l_int|0x370
comma
multiline_comment|/* UART channel 2 */
op_minus
l_int|1
)brace
suffix:semicolon
multiline_comment|/* Early initialization for kernel using Multi debugger ROM monitor.  */
DECL|function|multi_init
r_void
id|__init
id|multi_init
(paren
r_void
)paren
(brace
multiline_comment|/* We&squot;re using the Multi debugger monitor, so we have to install&n;&t;   the interrupt vectors.  The monitor doesn&squot;t allow them to be&n;&t;   initially downloaded into their final destination because&n;&t;   it&squot;s in the monitor&squot;s scratch-RAM area.  Unfortunately, Multi&n;&t;   also doesn&squot;t deal correctly with ELF sections where the LMA&n;&t;   and VMA differ -- it just ignores the LMA -- so we can&squot;t use&n;&t;   that feature to work around the problem.  What we do instead&n;&t;   is just put the interrupt vectors into a normal section, and&n;&t;   do the necessary copying and relocation here.  Since the&n;&t;   interrupt vector basically only contains `jr&squot; instructions&n;&t;   and no-ops, it&squot;s not that hard.  */
r_extern
r_int
r_int
id|_intv_load_start
comma
id|_intv_start
suffix:semicolon
r_register
r_int
r_int
op_star
id|src
op_assign
op_amp
id|_intv_load_start
suffix:semicolon
r_register
r_int
r_int
op_star
id|dst
op_assign
(paren
r_int
r_int
op_star
)paren
id|INTV_BASE
suffix:semicolon
r_register
r_int
r_int
id|jr_fixup
op_assign
(paren
r_char
op_star
)paren
op_amp
id|_intv_start
op_minus
(paren
r_char
op_star
)paren
id|dst
suffix:semicolon
r_register
r_int
op_star
id|ii
suffix:semicolon
multiline_comment|/* Copy interupt vectors as instructed by multi_intv_install_table. */
r_for
c_loop
(paren
id|ii
op_assign
id|multi_intv_install_table
suffix:semicolon
op_star
id|ii
op_ge
l_int|0
suffix:semicolon
id|ii
op_increment
)paren
(brace
multiline_comment|/* Copy 16-byte interrupt vector at offset *ii.  */
r_int
id|boffs
suffix:semicolon
r_for
c_loop
(paren
id|boffs
op_assign
l_int|0
suffix:semicolon
id|boffs
OL
l_int|0x10
suffix:semicolon
id|boffs
op_add_assign
r_sizeof
op_star
id|src
)paren
(brace
multiline_comment|/* Copy a single word, fixing up the jump offs&n;&t;&t;&t;   if it&squot;s a `jr&squot; instruction.  */
r_int
id|woffs
op_assign
(paren
op_star
id|ii
op_plus
id|boffs
)paren
op_div
r_sizeof
op_star
id|src
suffix:semicolon
r_int
r_int
id|word
op_assign
id|src
(braket
id|woffs
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|word
op_amp
l_int|0xFC0
)paren
op_eq
l_int|0x780
)paren
(brace
multiline_comment|/* A `jr&squot; insn, fix up its offset (and yes, the&n;&t;&t;&t;&t;   wierd half-word swapping is intentional). */
r_int
r_int
id|hi
op_assign
id|word
op_amp
l_int|0xFFFF
suffix:semicolon
r_int
r_int
id|lo
op_assign
id|word
op_rshift
l_int|16
suffix:semicolon
r_int
r_int
id|udisp22
op_assign
id|lo
op_plus
(paren
(paren
id|hi
op_amp
l_int|0x3F
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
r_int
id|disp22
op_assign
(paren
r_int
)paren
(paren
id|udisp22
op_lshift
l_int|10
)paren
op_rshift
l_int|10
suffix:semicolon
id|disp22
op_add_assign
id|jr_fixup
suffix:semicolon
id|hi
op_assign
(paren
(paren
id|disp22
op_rshift
l_int|16
)paren
op_amp
l_int|0x3F
)paren
op_or
l_int|0x780
suffix:semicolon
id|lo
op_assign
id|disp22
op_amp
l_int|0xFFFF
suffix:semicolon
id|word
op_assign
id|hi
op_plus
(paren
id|lo
op_lshift
l_int|16
)paren
suffix:semicolon
)brace
id|dst
(braket
id|woffs
)braket
op_assign
id|word
suffix:semicolon
)brace
)brace
)brace
eof
