multiline_comment|/*&n; * include/asm-sh/io_bigsur.h&n; *&n; * By Dustin McIntire (dustin@sensoria.com) (c)2001&n; * Derived from io_hd64465.h, which bore the message:&n; * By Greg Banks &lt;gbanks@pocketpenguins.com&gt;&n; * (c) 2000 PocketPenguins Inc. &n; * and from io_hd64461.h, which bore the message:&n; * Copyright 2000 Stuart Menefy (stuart.menefy@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * IO functions for a Hitachi Big Sur Evaluation Board.&n; */
macro_line|#ifndef _ASM_SH_IO_BIGSUR_H
DECL|macro|_ASM_SH_IO_BIGSUR_H
mdefine_line|#define _ASM_SH_IO_BIGSUR_H
macro_line|#include &lt;linux/types.h&gt;
r_extern
r_int
r_int
id|bigsur_isa_port2addr
c_func
(paren
r_int
r_int
id|offset
)paren
suffix:semicolon
r_extern
r_int
id|bigsur_irq_demux
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/* Provision for generic secondary demux step -- used by PCMCIA code */
r_extern
r_void
id|bigsur_register_irq_demux
c_func
(paren
r_int
id|irq
comma
r_int
(paren
op_star
id|demux
)paren
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
)paren
comma
r_void
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|bigsur_unregister_irq_demux
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/* Set this variable to 1 to see port traffic */
r_extern
r_int
id|bigsur_io_debug
suffix:semicolon
multiline_comment|/* Map a range of ports to a range of kernel virtual memory. */
r_extern
r_void
id|bigsur_port_map
c_func
(paren
id|u32
id|baseport
comma
id|u32
id|nports
comma
id|u32
id|addr
comma
id|u8
id|shift
)paren
suffix:semicolon
r_extern
r_void
id|bigsur_port_unmap
c_func
(paren
id|u32
id|baseport
comma
id|u32
id|nports
)paren
suffix:semicolon
macro_line|#endif /* _ASM_SH_IO_BIGSUR_H */
eof
