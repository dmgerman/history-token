multiline_comment|/*&n; *  Kevin D. Kissell, kevink@mips and Carsten Langgaard, carstenl@mips.com&n; *  Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Routines corresponding to Linux kernel FP context&n; * manipulation primitives for the Algorithmics MIPS&n; * FPU Emulator&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/signal.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/fpu_emulator.h&gt;
r_extern
r_struct
id|mips_fpu_emulator_private
id|fpuemuprivate
suffix:semicolon
DECL|macro|SIGNALLING_NAN
mdefine_line|#define SIGNALLING_NAN 0x7ff800007ff80000LL
DECL|function|fpu_emulator_init_fpu
r_void
id|fpu_emulator_init_fpu
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|first
op_assign
l_int|1
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|first
)paren
(brace
id|first
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Algorithmics/MIPS FPU Emulator v1.5&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|current-&gt;thread.fpu.soft.fcr31
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32
suffix:semicolon
id|i
op_increment
)paren
(brace
id|current-&gt;thread.fpu.soft.fpr
(braket
id|i
)braket
op_assign
id|SIGNALLING_NAN
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Emulator context save/restore to/from a signal context&n; * presumed to be on the user stack, and therefore accessed&n; * with appropriate macros from uaccess.h&n; */
DECL|function|fpu_emulator_save_context
r_int
id|fpu_emulator_save_context
c_func
(paren
r_struct
id|sigcontext
op_star
id|sc
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32
suffix:semicolon
id|i
op_increment
)paren
(brace
id|err
op_or_assign
id|__put_user
c_func
(paren
id|current-&gt;thread.fpu.soft.fpr
(braket
id|i
)braket
comma
op_amp
id|sc-&gt;sc_fpregs
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|err
op_or_assign
id|__put_user
c_func
(paren
id|current-&gt;thread.fpu.soft.fcr31
comma
op_amp
id|sc-&gt;sc_fpc_csr
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|fpuemuprivate.eir
comma
op_amp
id|sc-&gt;sc_fpc_eir
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|fpu_emulator_restore_context
r_int
id|fpu_emulator_restore_context
c_func
(paren
r_struct
id|sigcontext
op_star
id|sc
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32
suffix:semicolon
id|i
op_increment
)paren
(brace
id|err
op_or_assign
id|__get_user
c_func
(paren
id|current-&gt;thread.fpu.soft.fpr
(braket
id|i
)braket
comma
op_amp
id|sc-&gt;sc_fpregs
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|err
op_or_assign
id|__get_user
c_func
(paren
id|current-&gt;thread.fpu.soft.fcr31
comma
op_amp
id|sc-&gt;sc_fpc_csr
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|fpuemuprivate.eir
comma
op_amp
id|sc-&gt;sc_fpc_eir
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MIPS64
multiline_comment|/*&n; * This is the o32 version&n; */
DECL|function|fpu_emulator_save_context32
r_int
id|fpu_emulator_save_context32
c_func
(paren
r_struct
id|sigcontext32
op_star
id|sc
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
(brace
id|err
op_or_assign
id|__put_user
c_func
(paren
id|current-&gt;thread.fpu.soft.fpr
(braket
id|i
)braket
comma
op_amp
id|sc-&gt;sc_fpregs
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|err
op_or_assign
id|__put_user
c_func
(paren
id|current-&gt;thread.fpu.soft.fcr31
comma
op_amp
id|sc-&gt;sc_fpc_csr
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|fpuemuprivate.eir
comma
op_amp
id|sc-&gt;sc_fpc_eir
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|fpu_emulator_restore_context32
r_int
id|fpu_emulator_restore_context32
c_func
(paren
r_struct
id|sigcontext32
op_star
id|sc
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
(brace
id|err
op_or_assign
id|__get_user
c_func
(paren
id|current-&gt;thread.fpu.soft.fpr
(braket
id|i
)braket
comma
op_amp
id|sc-&gt;sc_fpregs
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|err
op_or_assign
id|__get_user
c_func
(paren
id|current-&gt;thread.fpu.soft.fcr31
comma
op_amp
id|sc-&gt;sc_fpc_csr
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|fpuemuprivate.eir
comma
op_amp
id|sc-&gt;sc_fpc_eir
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#endif
eof
