multiline_comment|/*&n; * include/asm-sh/io_cat68701.h&n; *&n; * Copyright 2000 Stuart Menefy (stuart.menefy@st.com)&n; *           2001 Yutarou Ebihar (ebihara@si-linux.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * IO functions for an AONE Corp. CAT-68701 SH7708 Borad&n; */
macro_line|#ifndef _ASM_SH_IO_CAT68701_H
DECL|macro|_ASM_SH_IO_CAT68701_H
mdefine_line|#define _ASM_SH_IO_CAT68701_H
r_extern
r_int
r_int
id|cat68701_isa_port2addr
c_func
(paren
r_int
r_int
id|offset
)paren
suffix:semicolon
r_extern
r_int
id|cat68701_irq_demux
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|init_cat68701_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|heartbeat_cat68701
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _ASM_SH_IO_CAT68701_H */
eof
