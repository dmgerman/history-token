multiline_comment|/*&n; *  arch/s390/kernel/irqextras390.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com),&n; *&n; *  Some channel code by D.J. Barrow&n; */
multiline_comment|/*&n;&t;&n;*/
macro_line|#include&lt;asm/irqextras390.h&gt;
macro_line|#include&lt;asm/lowcore.h&gt;
macro_line|#if 0
singleline_comment|// fixchannelprogram is now obselete
r_void
id|fixchannelprogram
c_func
(paren
id|orb_bits_t
op_star
id|orbptr
)paren
(brace
id|__u32
id|newAddress
op_assign
id|orbptr-&gt;ccw_program_address
suffix:semicolon
id|fixccws
c_func
(paren
id|orbptr-&gt;ccw_program_address
)paren
suffix:semicolon
id|orbptr-&gt;ccw_program_address
op_assign
id|newAddress
suffix:semicolon
id|orbptr-&gt;ccw_program_address
op_assign
(paren
id|ccw1_t
op_star
)paren
(paren
(paren
(paren
id|__u32
)paren
id|orbptr-&gt;ccw_program_address
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|fixccws
r_void
id|fixccws
c_func
(paren
id|ccw1_bits_t
op_star
id|ccwptr
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
id|ccwptr
op_increment
)paren
(brace
singleline_comment|// Just hope nobody starts doing prefixing
r_if
c_cond
(paren
op_logical_neg
id|ccwptr-&gt;cc
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
)brace
eof
