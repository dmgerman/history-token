multiline_comment|/*&n; *  include/asm-s390/gdb-stub.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; */
macro_line|#ifndef __S390_GDB_STUB__
DECL|macro|__S390_GDB_STUB__
mdefine_line|#define __S390_GDB_STUB__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if CONFIG_REMOTE_DEBUG
macro_line|#include &lt;asm/s390-gdbregs.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
r_extern
r_int
id|gdb_stub_initialised
suffix:semicolon
r_extern
r_void
id|gdb_stub_handle_exception
c_func
(paren
id|gdb_pt_regs
op_star
id|regs
comma
r_int
id|sigval
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
