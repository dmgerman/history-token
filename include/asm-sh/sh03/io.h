multiline_comment|/*&n; * include/asm-sh/sh03/io.h&n; *&n; * Copyright 2004 Interface Co.,Ltd. Saito.K&n; *&n; * IO functions for an Interface CTP/PCI-SH03&n; */
macro_line|#ifndef _ASM_SH_IO_SH03_H
DECL|macro|_ASM_SH_IO_SH03_H
mdefine_line|#define _ASM_SH_IO_SH03_H
macro_line|#include &lt;linux/time.h&gt;
DECL|macro|INTC_IPRD
mdefine_line|#define INTC_IPRD&t;0xffd00010UL
DECL|macro|IRL0_IRQ
mdefine_line|#define IRL0_IRQ&t;2
DECL|macro|IRL0_IPR_ADDR
mdefine_line|#define IRL0_IPR_ADDR&t;INTC_IPRD
DECL|macro|IRL0_IPR_POS
mdefine_line|#define IRL0_IPR_POS&t;3
DECL|macro|IRL0_PRIORITY
mdefine_line|#define IRL0_PRIORITY&t;13
DECL|macro|IRL1_IRQ
mdefine_line|#define IRL1_IRQ&t;5
DECL|macro|IRL1_IPR_ADDR
mdefine_line|#define IRL1_IPR_ADDR&t;INTC_IPRD
DECL|macro|IRL1_IPR_POS
mdefine_line|#define IRL1_IPR_POS&t;2
DECL|macro|IRL1_PRIORITY
mdefine_line|#define IRL1_PRIORITY&t;10
DECL|macro|IRL2_IRQ
mdefine_line|#define IRL2_IRQ&t;8
DECL|macro|IRL2_IPR_ADDR
mdefine_line|#define IRL2_IPR_ADDR&t;INTC_IPRD
DECL|macro|IRL2_IPR_POS
mdefine_line|#define IRL2_IPR_POS&t;1
DECL|macro|IRL2_PRIORITY
mdefine_line|#define IRL2_PRIORITY&t;7
DECL|macro|IRL3_IRQ
mdefine_line|#define IRL3_IRQ&t;11
DECL|macro|IRL3_IPR_ADDR
mdefine_line|#define IRL3_IPR_ADDR&t;INTC_IPRD
DECL|macro|IRL3_IPR_POS
mdefine_line|#define IRL3_IPR_POS&t;0
DECL|macro|IRL3_PRIORITY
mdefine_line|#define IRL3_PRIORITY&t;4
r_extern
r_int
r_int
id|sh03_isa_port2addr
c_func
(paren
r_int
r_int
id|offset
)paren
suffix:semicolon
r_extern
r_void
id|setup_sh03
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|init_sh03_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|heartbeat_sh03
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sh03_rtc_gettimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
)paren
suffix:semicolon
r_extern
r_int
id|sh03_rtc_settimeofday
c_func
(paren
r_const
r_struct
id|timeval
op_star
id|tv
)paren
suffix:semicolon
macro_line|#endif /* _ASM_SH_IO_SH03_H */
eof
