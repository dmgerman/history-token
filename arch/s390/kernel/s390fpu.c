multiline_comment|/*&n; *  arch/s390/kernel/s390fpu.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; *&n; *  s390fpu.h functions for saving &amp; restoring the fpu state.&n; *&n; *  I couldn&squot;t inline these as linux/sched.h included half the world&n; *  &amp; was required to at the task structure.&n; *  &amp; the functions were too complex to make macros from.&n; *  ( &amp; as usual I didn&squot;t feel like debugging inline code ).&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
DECL|function|save_fp_regs1
r_int
id|save_fp_regs1
c_func
(paren
id|s390_fp_regs
op_star
id|fpregs
)paren
(brace
r_int
id|has_ieee
op_assign
id|MACHINE_HAS_IEEE
suffix:semicolon
multiline_comment|/*&n;  I don&squot;t think we can use STE here as this would load&n;  fp registers 0 &amp; 2 into memory locations 0 &amp; 1 etc. &n; */
id|asm
r_volatile
(paren
l_string|&quot;STD   0,8(%0)&bslash;n&bslash;t&quot;
l_string|&quot;STD   2,24(%0)&bslash;n&bslash;t&quot;
l_string|&quot;STD   4,40(%0)&bslash;n&bslash;t&quot;
l_string|&quot;STD   6,56(%0)&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|fpregs
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_ieee
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;STFPC 0(%0)&bslash;n&bslash;t&quot;
l_string|&quot;STD   1,16(%0)&bslash;n&bslash;t&quot;
l_string|&quot;STD   3,32(%0)&bslash;n&bslash;t&quot;
l_string|&quot;STD   5,48(%0)&bslash;n&bslash;t&quot;
l_string|&quot;STD   7,64(%0)&bslash;n&bslash;t&quot;
l_string|&quot;STD   8,72(%0)&bslash;n&bslash;t&quot;
l_string|&quot;STD   9,80(%0)&bslash;n&bslash;t&quot;
l_string|&quot;STD   10,88(%0)&bslash;n&bslash;t&quot;
l_string|&quot;STD   11,96(%0)&bslash;n&bslash;t&quot;
l_string|&quot;STD   12,104(%0)&bslash;n&bslash;t&quot;
l_string|&quot;STD   13,112(%0)&bslash;n&bslash;t&quot;
l_string|&quot;STD   14,120(%0)&bslash;n&bslash;t&quot;
l_string|&quot;STD   15,128(%0)&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|fpregs
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_return
id|has_ieee
suffix:semicolon
)brace
DECL|function|save_fp_regs
r_void
id|save_fp_regs
c_func
(paren
id|s390_fp_regs
op_star
id|fpregs
)paren
(brace
macro_line|#if CONFIG_IEEEFPU_EMULATION
id|s390_fp_regs
op_star
id|currentfprs
suffix:semicolon
macro_line|#endif
macro_line|#if CONFIG_IEEEFPU_EMULATION
r_if
c_cond
(paren
op_logical_neg
id|save_fp_regs1
c_func
(paren
id|fpregs
)paren
)paren
(brace
id|currentfprs
op_assign
op_amp
id|current-&gt;thread.fp_regs
suffix:semicolon
id|fpregs-&gt;fpc
op_assign
id|currentfprs-&gt;fpc
suffix:semicolon
id|fpregs-&gt;fprs
(braket
l_int|1
)braket
dot
id|d
op_assign
id|currentfprs-&gt;fprs
(braket
l_int|1
)braket
dot
id|d
suffix:semicolon
id|fpregs-&gt;fprs
(braket
l_int|3
)braket
dot
id|d
op_assign
id|currentfprs-&gt;fprs
(braket
l_int|3
)braket
dot
id|d
suffix:semicolon
id|fpregs-&gt;fprs
(braket
l_int|5
)braket
dot
id|d
op_assign
id|currentfprs-&gt;fprs
(braket
l_int|5
)braket
dot
id|d
suffix:semicolon
id|fpregs-&gt;fprs
(braket
l_int|7
)braket
dot
id|d
op_assign
id|currentfprs-&gt;fprs
(braket
l_int|7
)braket
dot
id|d
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|fpregs-&gt;fprs
(braket
l_int|8
)braket
dot
id|d
comma
op_amp
id|currentfprs-&gt;fprs
(braket
l_int|8
)braket
dot
id|d
comma
r_sizeof
(paren
id|freg_t
)paren
op_star
l_int|8
)paren
suffix:semicolon
)brace
macro_line|#else
id|save_fp_regs1
c_func
(paren
id|fpregs
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|restore_fp_regs1
r_int
id|restore_fp_regs1
c_func
(paren
id|s390_fp_regs
op_star
id|fpregs
)paren
(brace
r_int
id|has_ieee
op_assign
id|MACHINE_HAS_IEEE
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;LD   0,8(%0)&bslash;n&bslash;t&quot;
l_string|&quot;LD   2,24(%0)&bslash;n&bslash;t&quot;
l_string|&quot;LD   4,40(%0)&bslash;n&bslash;t&quot;
l_string|&quot;LD   6,56(%0)&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|fpregs
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_ieee
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;LFPC 0(%0)&bslash;n&bslash;t&quot;
l_string|&quot;LD   1,16(%0)&bslash;n&bslash;t&quot;
l_string|&quot;LD   3,32(%0)&bslash;n&bslash;t&quot;
l_string|&quot;LD   5,48(%0)&bslash;n&bslash;t&quot;
l_string|&quot;LD   7,64(%0)&bslash;n&bslash;t&quot;
l_string|&quot;LD   8,72(%0)&bslash;n&bslash;t&quot;
l_string|&quot;LD   9,80(%0)&bslash;n&bslash;t&quot;
l_string|&quot;LD   10,88(%0)&bslash;n&bslash;t&quot;
l_string|&quot;LD   11,96(%0)&bslash;n&bslash;t&quot;
l_string|&quot;LD   12,104(%0)&bslash;n&bslash;t&quot;
l_string|&quot;LD   13,112(%0)&bslash;n&bslash;t&quot;
l_string|&quot;LD   14,120(%0)&bslash;n&bslash;t&quot;
l_string|&quot;LD   15,128(%0)&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|fpregs
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_return
id|has_ieee
suffix:semicolon
)brace
DECL|function|restore_fp_regs
r_void
id|restore_fp_regs
c_func
(paren
id|s390_fp_regs
op_star
id|fpregs
)paren
(brace
macro_line|#if CONFIG_IEEEFPU_EMULATION
id|s390_fp_regs
op_star
id|currentfprs
suffix:semicolon
macro_line|#endif
macro_line|#if CONFIG_IEEEFPU_EMULATION
r_if
c_cond
(paren
op_logical_neg
id|restore_fp_regs1
c_func
(paren
id|fpregs
)paren
)paren
(brace
id|currentfprs
op_assign
op_amp
id|current-&gt;thread.fp_regs
suffix:semicolon
id|currentfprs-&gt;fpc
op_assign
id|fpregs-&gt;fpc
suffix:semicolon
id|currentfprs-&gt;fprs
(braket
l_int|1
)braket
dot
id|d
op_assign
id|fpregs-&gt;fprs
(braket
l_int|1
)braket
dot
id|d
suffix:semicolon
id|currentfprs-&gt;fprs
(braket
l_int|3
)braket
dot
id|d
op_assign
id|fpregs-&gt;fprs
(braket
l_int|3
)braket
dot
id|d
suffix:semicolon
id|currentfprs-&gt;fprs
(braket
l_int|5
)braket
dot
id|d
op_assign
id|fpregs-&gt;fprs
(braket
l_int|5
)braket
dot
id|d
suffix:semicolon
id|currentfprs-&gt;fprs
(braket
l_int|7
)braket
dot
id|d
op_assign
id|fpregs-&gt;fprs
(braket
l_int|7
)braket
dot
id|d
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|currentfprs-&gt;fprs
(braket
l_int|8
)braket
dot
id|d
comma
op_amp
id|fpregs-&gt;fprs
(braket
l_int|8
)braket
dot
id|d
comma
r_sizeof
(paren
id|freg_t
)paren
op_star
l_int|8
)paren
suffix:semicolon
)brace
macro_line|#else
id|restore_fp_regs1
c_func
(paren
id|fpregs
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
