multiline_comment|/*&n; * Linux/PA-RISC Project (http://www.parisc-linux.org/)&n; *&n; * Floating-point emulation code&n; *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) &lt;bame@debian.org&gt;&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*&n; *  linux/arch/math-emu/driver.c.c&n; *&n; *&t;decodes and dispatches unimplemented FPU instructions&n; *&n; *  Copyright (C) 1999, 2000  Philipp Rumpf &lt;prumpf@tux.org&gt;&n; *  Copyright (C) 2001&t;      Hewlett-Packard &lt;bame@debian.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &quot;float.h&quot;
macro_line|#include &quot;math-emu.h&quot;
DECL|macro|fptpos
mdefine_line|#define fptpos 31
DECL|macro|fpr1pos
mdefine_line|#define fpr1pos 10
DECL|macro|extru
mdefine_line|#define extru(r,pos,len) (((r) &gt;&gt; (31-(pos))) &amp; (( 1 &lt;&lt; (len)) - 1))
DECL|macro|FPUDEBUG
mdefine_line|#define FPUDEBUG 0
multiline_comment|/* Format of the floating-point exception registers. */
DECL|struct|exc_reg
r_struct
id|exc_reg
(brace
DECL|member|exception
r_int
r_int
id|exception
suffix:colon
l_int|6
suffix:semicolon
DECL|member|ei
r_int
r_int
id|ei
suffix:colon
l_int|26
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Macros for grabbing bits of the instruction format from the &squot;ei&squot;&n;   field above. */
multiline_comment|/* Major opcode 0c and 0e */
DECL|macro|FP0CE_UID
mdefine_line|#define FP0CE_UID(i) (((i) &gt;&gt; 6) &amp; 3)
DECL|macro|FP0CE_CLASS
mdefine_line|#define FP0CE_CLASS(i) (((i) &gt;&gt; 9) &amp; 3)
DECL|macro|FP0CE_SUBOP
mdefine_line|#define FP0CE_SUBOP(i) (((i) &gt;&gt; 13) &amp; 7)
DECL|macro|FP0CE_SUBOP1
mdefine_line|#define FP0CE_SUBOP1(i) (((i) &gt;&gt; 15) &amp; 7) /* Class 1 subopcode */
DECL|macro|FP0C_FORMAT
mdefine_line|#define FP0C_FORMAT(i) (((i) &gt;&gt; 11) &amp; 3)
DECL|macro|FP0E_FORMAT
mdefine_line|#define FP0E_FORMAT(i) (((i) &gt;&gt; 11) &amp; 1)
multiline_comment|/* Major opcode 0c, uid 2 (performance monitoring) */
DECL|macro|FPPM_SUBOP
mdefine_line|#define FPPM_SUBOP(i) (((i) &gt;&gt; 9) &amp; 0x1f)
multiline_comment|/* Major opcode 2e (fused operations).   */
DECL|macro|FP2E_SUBOP
mdefine_line|#define FP2E_SUBOP(i)  (((i) &gt;&gt; 5) &amp; 1)
DECL|macro|FP2E_FORMAT
mdefine_line|#define FP2E_FORMAT(i) (((i) &gt;&gt; 11) &amp; 1)
multiline_comment|/* Major opcode 26 (FMPYSUB) */
multiline_comment|/* Major opcode 06 (FMPYADD) */
DECL|macro|FPx6_FORMAT
mdefine_line|#define FPx6_FORMAT(i) ((i) &amp; 0x1f)
multiline_comment|/* Flags and enable bits of the status word. */
DECL|macro|FPSW_FLAGS
mdefine_line|#define FPSW_FLAGS(w) ((w) &gt;&gt; 27)
DECL|macro|FPSW_ENABLE
mdefine_line|#define FPSW_ENABLE(w) ((w) &amp; 0x1f)
DECL|macro|FPSW_V
mdefine_line|#define FPSW_V (1&lt;&lt;4)
DECL|macro|FPSW_Z
mdefine_line|#define FPSW_Z (1&lt;&lt;3)
DECL|macro|FPSW_O
mdefine_line|#define FPSW_O (1&lt;&lt;2)
DECL|macro|FPSW_U
mdefine_line|#define FPSW_U (1&lt;&lt;1)
DECL|macro|FPSW_I
mdefine_line|#define FPSW_I (1&lt;&lt;0)
multiline_comment|/* Handle a floating point exception.  Return zero if the faulting&n;   instruction can be completed successfully. */
r_int
DECL|function|handle_fpe
id|handle_fpe
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_extern
r_void
id|printbinary
c_func
(paren
r_int
r_int
id|x
comma
r_int
id|nbits
)paren
suffix:semicolon
r_struct
id|siginfo
id|si
suffix:semicolon
r_int
r_int
id|orig_sw
comma
id|sw
suffix:semicolon
r_int
id|signalcode
suffix:semicolon
multiline_comment|/* need an intermediate copy of float regs because FPU emulation&n;&t; * code expects an artificial last entry which contains zero&n;&t; *&n;&t; * also, the passed in fr registers contain one word that defines&n;&t; * the fpu type. the fpu type information is constructed &n;&t; * inside the emulation code&n;&t; */
id|__u64
id|frcopy
(braket
l_int|36
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|frcopy
comma
id|regs-&gt;fr
comma
r_sizeof
id|regs-&gt;fr
)paren
suffix:semicolon
id|frcopy
(braket
l_int|32
)braket
op_assign
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|orig_sw
comma
id|frcopy
comma
r_sizeof
(paren
id|orig_sw
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FPUDEBUG
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;FP VZOUICxxxxCQCQCQCQCQCRMxxTDVZOUI -&gt;&bslash;n   &quot;
)paren
suffix:semicolon
id|printbinary
c_func
(paren
id|orig_sw
comma
l_int|32
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|signalcode
op_assign
id|decode_fpu
c_func
(paren
id|frcopy
comma
l_int|0x666
)paren
suffix:semicolon
multiline_comment|/* Status word = FR0L. */
id|memcpy
c_func
(paren
op_amp
id|sw
comma
id|frcopy
comma
r_sizeof
(paren
id|sw
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FPUDEBUG
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;VZOUICxxxxCQCQCQCQCQCRMxxTDVZOUI decode_fpu returns %d|0x%x&bslash;n&quot;
comma
id|signalcode
op_rshift
l_int|24
comma
id|signalcode
op_amp
l_int|0xffffff
)paren
suffix:semicolon
id|printbinary
c_func
(paren
id|sw
comma
l_int|32
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|regs-&gt;fr
comma
id|frcopy
comma
r_sizeof
id|regs-&gt;fr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signalcode
op_ne
l_int|0
)paren
(brace
id|si.si_signo
op_assign
id|signalcode
op_rshift
l_int|24
suffix:semicolon
id|si.si_errno
op_assign
l_int|0
suffix:semicolon
id|si.si_code
op_assign
id|signalcode
op_amp
l_int|0xffffff
suffix:semicolon
id|si.si_addr
op_assign
(paren
r_void
op_star
)paren
id|regs-&gt;iaoq
(braket
l_int|0
)braket
suffix:semicolon
id|force_sig_info
c_func
(paren
id|si.si_signo
comma
op_amp
id|si
comma
id|current
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|signalcode
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
eof
