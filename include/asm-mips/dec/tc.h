multiline_comment|/*&n; * Interface to the TURBOchannel related routines&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1998 Harald Koerfgen&n; */
macro_line|#ifndef ASM_TC_H
DECL|macro|ASM_TC_H
mdefine_line|#define ASM_TC_H
r_extern
r_int
r_int
id|system_base
suffix:semicolon
multiline_comment|/*&n; * Search for a TURBOchannel Option Module&n; * with a certain name. Returns slot number&n; * of the first card not in use or -ENODEV&n; * if none found.&n; */
r_extern
r_int
id|search_tc_card
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Marks the card in slot as used&n; */
r_extern
r_void
id|claim_tc_card
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Marks the card in slot as free&n; */
r_extern
r_void
id|release_tc_card
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Return base address of card in slot &n; */
r_extern
r_int
r_int
id|get_tc_base_addr
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Return interrupt number of slot&n; */
r_extern
r_int
r_int
id|get_tc_irq_nr
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Return TURBOchannel clock frequency in hz&n; */
r_extern
r_int
r_int
id|get_tc_speed
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
