multiline_comment|/*&n; * I/O routine for SH-2000&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
DECL|macro|IDE_OFFSET
mdefine_line|#define IDE_OFFSET    0xb6200000
DECL|macro|NIC_OFFSET
mdefine_line|#define NIC_OFFSET    0xb6000000
DECL|macro|EXTBUS_OFFSET
mdefine_line|#define EXTBUS_OFFSET 0xba000000
DECL|function|sh2000_isa_port2addr
r_int
r_int
id|sh2000_isa_port2addr
c_func
(paren
r_int
r_int
id|offset
)paren
(brace
r_if
c_cond
(paren
(paren
id|offset
op_amp
op_complement
l_int|7
)paren
op_eq
l_int|0x1f0
op_logical_or
id|offset
op_eq
l_int|0x3f6
)paren
(brace
r_return
id|IDE_OFFSET
op_plus
id|offset
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|offset
op_amp
op_complement
l_int|0x1f
)paren
op_eq
l_int|0x300
)paren
(brace
r_return
id|NIC_OFFSET
op_plus
id|offset
suffix:semicolon
)brace
r_return
id|EXTBUS_OFFSET
op_plus
id|offset
suffix:semicolon
)brace
eof
