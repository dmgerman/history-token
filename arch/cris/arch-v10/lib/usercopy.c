multiline_comment|/*&n; * User address space access functions.&n; * The non-inlined parts of asm-cris/uaccess.h are here.&n; *&n; * Copyright (C) 2000, Axis Communications AB.&n; *&n; * Written by Hans-Peter Nilsson.&n; * Pieces used from memcpy, originally by Kenny Ranerup long time ago.&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* Asm:s have been tweaked (within the domain of correctness) to give&n;   satisfactory results for &quot;gcc version 2.96 20000427 (experimental)&quot;.&n;&n;   Check regularly...&n;&n;   Note that the PC saved at a bus-fault is the address *after* the&n;   faulting instruction, which means the branch-target for instructions in&n;   delay-slots for taken branches.  Note also that the postincrement in&n;   the instruction is performed regardless of bus-fault; the register is&n;   seen updated in fault handlers.&n;&n;   Oh, and on the code formatting issue, to whomever feels like &quot;fixing&n;   it&quot; to Conformity: I&squot;m too &quot;lazy&quot;, but why don&squot;t you go ahead and &quot;fix&quot;&n;   string.c too.  I just don&squot;t think too many people will hack this file&n;   for the code format to be an issue.  */
multiline_comment|/* Copy to userspace.  This is based on the memcpy used for&n;   kernel-to-kernel copying; see &quot;string.c&quot;.  */
r_int
r_int
DECL|function|__copy_user
id|__copy_user
(paren
r_void
id|__user
op_star
id|pdst
comma
r_const
r_void
op_star
id|psrc
comma
r_int
r_int
id|pn
)paren
(brace
multiline_comment|/* We want the parameters put in special registers.&n;     Make sure the compiler is able to make something useful of this.&n;     As it is now: r10 -&gt; r13; r11 -&gt; r11 (nop); r12 -&gt; r12 (nop).&n;&n;     FIXME: Comment for old gcc version.  Check.&n;     If gcc was allright, it really would need no temporaries, and no&n;     stack space to save stuff on. */
r_register
r_char
op_star
id|dst
id|__asm__
(paren
l_string|&quot;r13&quot;
)paren
op_assign
id|pdst
suffix:semicolon
r_register
r_const
r_char
op_star
id|src
id|__asm__
(paren
l_string|&quot;r11&quot;
)paren
op_assign
id|psrc
suffix:semicolon
r_register
r_int
id|n
id|__asm__
(paren
l_string|&quot;r12&quot;
)paren
op_assign
id|pn
suffix:semicolon
r_register
r_int
id|retn
id|__asm__
(paren
l_string|&quot;r10&quot;
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* When src is aligned but not dst, this makes a few extra needless&n;     cycles.  I believe it would take as many to check that the&n;     re-alignment was unnecessary.  */
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|dst
op_amp
l_int|3
)paren
op_ne
l_int|0
multiline_comment|/* Don&squot;t align if we wouldn&squot;t copy more than a few bytes; so we&n;&t; don&squot;t have to check further for overflows.  */
op_logical_and
id|n
op_ge
l_int|3
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|dst
op_amp
l_int|1
)paren
(brace
id|__asm_copy_to_user_1
(paren
id|dst
comma
id|src
comma
id|retn
)paren
suffix:semicolon
id|n
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|dst
op_amp
l_int|2
)paren
(brace
id|__asm_copy_to_user_2
(paren
id|dst
comma
id|src
comma
id|retn
)paren
suffix:semicolon
id|n
op_sub_assign
l_int|2
suffix:semicolon
)brace
)brace
multiline_comment|/* Decide which copying method to use. */
r_if
c_cond
(paren
id|n
op_ge
l_int|44
op_star
l_int|2
)paren
multiline_comment|/* Break even between movem and&n;&t;&t;&t;&t;   move16 is at 38.7*2, but modulo 44. */
(brace
multiline_comment|/* For large copies we use &squot;movem&squot;.  */
multiline_comment|/* It is not optimal to tell the compiler about clobbering any&n;       registers; that will move the saving/restoring of those registers&n;       to the function prologue/epilogue, and make non-movem sizes&n;       suboptimal.&n;&n;       This method is not foolproof; it assumes that the &quot;asm reg&quot;&n;       declarations at the beginning of the function really are used&n;       here (beware: they may be moved to temporary registers).&n;       This way, we do not have to save/move the registers around into&n;       temporaries; we can safely use them straight away.&n;&n;       If you want to check that the allocation was right; then&n;       check the equalities in the first comment.  It should say&n;       &quot;r13=r13, r11=r11, r12=r12&quot;.  */
id|__asm__
r_volatile
(paren
"&quot;&bslash;"
dot
id|ifnc
op_mod
l_int|0
op_mod
l_int|1
op_mod
l_int|2
op_mod
l_int|3
comma
"$"
id|r13
"$"
id|r11
"$"
id|r12
"$"
id|r10
"&bslash;"
id|n
"&bslash;"
dot
id|err
"&bslash;"
id|n
"&bslash;"
dot
id|endif
"&bslash;"
id|n
"&bslash;"
suffix:semicolon
suffix:semicolon
id|Save
id|the
id|registers
id|we
"&squot;"
id|ll
id|use
id|in
id|the
id|movem
id|process
suffix:semicolon
suffix:semicolon
id|on
id|the
id|stack
dot
id|subq
l_int|11
op_star
l_int|4
comma
"$"
id|sp
id|movem
"$"
id|r10
comma
(braket
"$"
id|sp
)braket
suffix:semicolon
suffix:semicolon
id|Now
id|we
"&squot;"
id|ve
id|got
id|this
suffix:colon
suffix:semicolon
suffix:semicolon
id|r11
op_minus
id|src
suffix:semicolon
suffix:semicolon
id|r13
op_minus
id|dst
suffix:semicolon
suffix:semicolon
id|r12
op_minus
id|n
suffix:semicolon
suffix:semicolon
id|Update
id|n
r_for
id|the
id|first
id|loop
id|subq
l_int|44
comma
"$"
id|r12
suffix:semicolon
id|Since
id|the
id|noted
id|PC
id|of
id|a
id|faulting
id|instruction
id|in
id|a
id|delay
op_minus
id|slot
id|of
id|a
id|taken
suffix:semicolon
id|branch
comma
id|is
id|that
id|of
id|the
id|branch
id|target
comma
id|we
id|actually
id|point
id|at
id|the
id|from
op_minus
id|movem
suffix:semicolon
r_for
id|this
r_case
dot
id|There
id|is
id|no
id|ambiguity
id|here
suffix:semicolon
r_if
id|there
id|was
id|a
id|fault
id|in
id|that
suffix:semicolon
id|instruction
(paren
id|meaning
id|a
id|kernel
id|oops
)paren
comma
id|the
id|faulted
id|PC
id|would
id|be
id|the
id|address
suffix:semicolon
id|after
op_star
id|that
op_star
id|movem
dot
l_int|0
suffix:colon
id|movem
(braket
"$"
id|r11
op_plus
)braket
comma
"$"
id|r10
id|subq
l_int|44
comma
"$"
id|r12
id|bge
l_int|0
id|b
id|movem
"$"
id|r10
comma
(braket
"$"
id|r13
op_plus
)braket
l_int|1
suffix:colon
id|addq
l_int|44
comma
"$"
id|r12
suffix:semicolon
suffix:semicolon
id|compensate
r_for
id|last
id|loop
id|underflowing
id|n
suffix:semicolon
suffix:semicolon
id|Restore
id|registers
id|from
id|stack
id|movem
(braket
"$"
id|sp
op_plus
)braket
comma
"$"
id|r10
l_int|2
suffix:colon
dot
id|section
dot
id|fixup
comma
"&bslash;&quot;"
id|ax
"&bslash;&quot;"
suffix:semicolon
id|To
id|provide
id|a
id|correct
id|count
id|in
id|r10
id|of
id|bytes
id|that
id|failed
id|to
id|be
id|copied
comma
suffix:semicolon
id|we
id|jump
id|back
id|into
id|the
id|loop
r_if
id|the
id|loop
op_minus
id|branch
id|was
id|taken
dot
id|There
id|is
id|no
suffix:semicolon
id|performance
id|penalty
r_for
id|sany
id|use
suffix:semicolon
id|the
id|program
id|will
id|segfault
id|soon
id|enough
dot
l_int|3
suffix:colon
id|move.d
(braket
"$"
id|sp
)braket
comma
"$"
id|r10
id|addq
l_int|44
comma
"$"
id|r10
id|move.d
"$"
id|r10
comma
(braket
"$"
id|sp
)braket
id|jump
l_int|0
id|b
l_int|4
suffix:colon
id|movem
(braket
"$"
id|sp
op_plus
)braket
comma
"$"
id|r10
id|addq
l_int|44
comma
"$"
id|r10
id|addq
l_int|44
comma
"$"
id|r12
id|jump
l_int|2
id|b
dot
id|previous
dot
id|section
id|__ex_table
comma
"&bslash;&quot;"
id|a
"&bslash;&quot;"
dot
id|dword
l_int|0
id|b
comma
l_int|3
id|b
dot
id|dword
l_int|1
id|b
comma
l_int|4
id|b
dot
id|previous
"&quot;"
multiline_comment|/* Outputs */
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dst
)paren
comma
l_string|&quot;=r&quot;
(paren
id|src
)paren
comma
l_string|&quot;=r&quot;
(paren
id|n
)paren
comma
l_string|&quot;=r&quot;
(paren
id|retn
)paren
multiline_comment|/* Inputs */
suffix:colon
l_string|&quot;0&quot;
(paren
id|dst
)paren
comma
l_string|&quot;1&quot;
(paren
id|src
)paren
comma
l_string|&quot;2&quot;
(paren
id|n
)paren
comma
l_string|&quot;3&quot;
(paren
id|retn
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Either we directly start copying, using dword copying in a loop, or&n;     we copy as much as possible with &squot;movem&squot; and then the last block (&lt;44&n;     bytes) is copied here.  This will work since &squot;movem&squot; will have&n;     updated SRC, DST and N.  */
r_while
c_loop
(paren
id|n
op_ge
l_int|16
)paren
(brace
id|__asm_copy_to_user_16
(paren
id|dst
comma
id|src
comma
id|retn
)paren
suffix:semicolon
id|n
op_sub_assign
l_int|16
suffix:semicolon
)brace
multiline_comment|/* Having a separate by-four loops cuts down on cache footprint.&n;     FIXME:  Test with and without; increasing switch to be 0..15.  */
r_while
c_loop
(paren
id|n
op_ge
l_int|4
)paren
(brace
id|__asm_copy_to_user_4
(paren
id|dst
comma
id|src
comma
id|retn
)paren
suffix:semicolon
id|n
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|n
)paren
(brace
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|__asm_copy_to_user_1
(paren
id|dst
comma
id|src
comma
id|retn
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm_copy_to_user_2
(paren
id|dst
comma
id|src
comma
id|retn
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|__asm_copy_to_user_3
(paren
id|dst
comma
id|src
comma
id|retn
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|retn
suffix:semicolon
)brace
multiline_comment|/* Copy from user to kernel, zeroing the bytes that were inaccessible in&n;   userland.  The return-value is the number of bytes that were&n;   inaccessible.  */
r_int
r_int
DECL|function|__copy_user_zeroing
id|__copy_user_zeroing
(paren
r_void
id|__user
op_star
id|pdst
comma
r_const
r_void
op_star
id|psrc
comma
r_int
r_int
id|pn
)paren
(brace
multiline_comment|/* We want the parameters put in special registers.&n;     Make sure the compiler is able to make something useful of this.&n;     As it is now: r10 -&gt; r13; r11 -&gt; r11 (nop); r12 -&gt; r12 (nop).&n;&n;     FIXME: Comment for old gcc version.  Check.&n;     If gcc was allright, it really would need no temporaries, and no&n;     stack space to save stuff on.  */
r_register
r_char
op_star
id|dst
id|__asm__
(paren
l_string|&quot;r13&quot;
)paren
op_assign
id|pdst
suffix:semicolon
r_register
r_const
r_char
op_star
id|src
id|__asm__
(paren
l_string|&quot;r11&quot;
)paren
op_assign
id|psrc
suffix:semicolon
r_register
r_int
id|n
id|__asm__
(paren
l_string|&quot;r12&quot;
)paren
op_assign
id|pn
suffix:semicolon
r_register
r_int
id|retn
id|__asm__
(paren
l_string|&quot;r10&quot;
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* The best reason to align src is that we then know that a read-fault&n;     was for aligned bytes; there&squot;s no 1..3 remaining good bytes to&n;     pickle.  */
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|src
op_amp
l_int|3
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|src
op_amp
l_int|1
)paren
op_logical_and
id|n
op_ne
l_int|0
)paren
(brace
id|__asm_copy_from_user_1
(paren
id|dst
comma
id|src
comma
id|retn
)paren
suffix:semicolon
id|n
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|src
op_amp
l_int|2
)paren
op_logical_and
id|n
op_ge
l_int|2
)paren
(brace
id|__asm_copy_from_user_2
(paren
id|dst
comma
id|src
comma
id|retn
)paren
suffix:semicolon
id|n
op_sub_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/* We only need one check after the unalignment-adjustments, because&n;       if both adjustments were done, either both or neither reference&n;       had an exception.  */
r_if
c_cond
(paren
id|retn
op_ne
l_int|0
)paren
r_goto
id|copy_exception_bytes
suffix:semicolon
)brace
multiline_comment|/* Decide which copying method to use. */
r_if
c_cond
(paren
id|n
op_ge
l_int|44
op_star
l_int|2
)paren
multiline_comment|/* Break even between movem and&n;&t;&t;&t;&t;   move16 is at 38.7*2, but modulo 44.&n;&t;&t;&t;&t;   FIXME: We use move4 now.  */
(brace
multiline_comment|/* For large copies we use &squot;movem&squot; */
multiline_comment|/* It is not optimal to tell the compiler about clobbering any&n;       registers; that will move the saving/restoring of those registers&n;       to the function prologue/epilogue, and make non-movem sizes&n;       suboptimal.&n;&n;       This method is not foolproof; it assumes that the &quot;asm reg&quot;&n;       declarations at the beginning of the function really are used&n;       here (beware: they may be moved to temporary registers).&n;       This way, we do not have to save/move the registers around into&n;       temporaries; we can safely use them straight away.&n;&n;       If you want to check that the allocation was right; then&n;       check the equalities in the first comment.  It should say&n;       &quot;r13=r13, r11=r11, r12=r12&quot; */
id|__asm__
r_volatile
(paren
"&quot;"
dot
id|ifnc
op_mod
l_int|0
op_mod
l_int|1
op_mod
l_int|2
op_mod
l_int|3
comma
"$"
id|r13
"$"
id|r11
"$"
id|r12
"$"
id|r10
"&bslash;"
id|n
"&bslash;"
dot
id|err
"&bslash;"
id|n
"&bslash;"
dot
id|endif
"&bslash;"
id|n
"&bslash;"
suffix:semicolon
suffix:semicolon
id|Save
id|the
id|registers
id|we
"&squot;"
id|ll
id|use
id|in
id|the
id|movem
id|process
suffix:semicolon
suffix:semicolon
id|on
id|the
id|stack
dot
id|subq
l_int|11
op_star
l_int|4
comma
"$"
id|sp
id|movem
"$"
id|r10
comma
(braket
"$"
id|sp
)braket
suffix:semicolon
suffix:semicolon
id|Now
id|we
"&squot;"
id|ve
id|got
id|this
suffix:colon
suffix:semicolon
suffix:semicolon
id|r11
op_minus
id|src
suffix:semicolon
suffix:semicolon
id|r13
op_minus
id|dst
suffix:semicolon
suffix:semicolon
id|r12
op_minus
id|n
suffix:semicolon
suffix:semicolon
id|Update
id|n
r_for
id|the
id|first
id|loop
id|subq
l_int|44
comma
"$"
id|r12
l_int|0
suffix:colon
id|movem
(braket
"$"
id|r11
op_plus
)braket
comma
"$"
id|r10
l_int|1
suffix:colon
id|subq
l_int|44
comma
"$"
id|r12
id|bge
l_int|0
id|b
id|movem
"$"
id|r10
comma
(braket
"$"
id|r13
op_plus
)braket
id|addq
l_int|44
comma
"$"
id|r12
suffix:semicolon
suffix:semicolon
id|compensate
r_for
id|last
id|loop
id|underflowing
id|n
suffix:semicolon
suffix:semicolon
id|Restore
id|registers
id|from
id|stack
id|movem
(braket
"$"
id|sp
op_plus
)braket
comma
"$"
id|r10
l_int|4
suffix:colon
dot
id|section
dot
id|fixup
comma
"&bslash;&quot;"
id|ax
"&bslash;&quot;"
suffix:semicolon
suffix:semicolon
id|Do
op_logical_neg
id|jump
id|back
id|into
id|the
id|loop
r_if
id|we
id|fail
dot
id|For
id|some
id|uses
comma
id|we
id|get
id|a
suffix:semicolon
suffix:semicolon
id|page
id|fault
id|somewhere
id|on
id|the
id|line
dot
id|Without
id|checking
r_for
id|page
id|limits
comma
suffix:semicolon
suffix:semicolon
id|we
id|don
"&squot;"
id|t
id|know
id|where
comma
id|but
id|we
id|need
id|to
id|copy
id|accurately
op_logical_and
id|keep
id|an
suffix:semicolon
suffix:semicolon
id|accurate
id|count
suffix:semicolon
op_logical_neg
id|just
id|clear
id|the
id|whole
id|line
dot
id|To
r_do
id|that
comma
id|we
id|fall
suffix:semicolon
suffix:semicolon
id|down
id|in
id|the
id|code
id|below
comma
id|proceeding
id|with
id|smaller
id|amounts
dot
id|It
id|should
suffix:semicolon
suffix:semicolon
id|be
id|kept
id|in
id|mind
id|that
id|we
id|have
id|to
id|cater
id|to
id|code
id|like
id|what
id|at
id|one
id|time
suffix:semicolon
suffix:semicolon
id|was
id|in
id|fs
op_div
id|super.c
suffix:colon
suffix:semicolon
suffix:semicolon
id|i
op_assign
id|size
op_minus
id|copy_from_user
c_func
(paren
(paren
r_void
op_star
)paren
id|page
comma
id|data
comma
id|size
)paren
suffix:semicolon
suffix:semicolon
suffix:semicolon
id|which
id|would
id|cause
id|repeated
id|faults
r_while
id|clearing
id|the
id|remainder
id|of
suffix:semicolon
suffix:semicolon
id|the
id|SIZE
id|bytes
id|at
id|PAGE
id|after
id|the
id|first
id|fault
dot
suffix:semicolon
suffix:semicolon
id|A
id|caveat
id|here
id|is
id|that
id|we
id|must
op_logical_neg
id|fall
id|through
id|from
id|a
id|failing
id|page
suffix:semicolon
suffix:semicolon
id|to
id|a
id|valid
id|page
dot
l_int|3
suffix:colon
id|movem
(braket
"$"
id|sp
op_plus
)braket
comma
"$"
id|r10
id|addq
l_int|44
comma
"$"
id|r12
suffix:semicolon
suffix:semicolon
id|Get
id|back
id|count
id|before
id|faulting
id|point
dot
id|subq
l_int|44
comma
"$"
id|r11
suffix:semicolon
suffix:semicolon
id|Get
id|back
id|pointer
id|to
id|faulting
id|movem
op_minus
id|line
dot
id|jump
l_int|4
id|b
suffix:semicolon
suffix:semicolon
id|Fall
id|through
comma
id|pretending
id|the
id|fault
id|didn
"&squot;"
id|t
id|happen
dot
dot
id|previous
dot
id|section
id|__ex_table
comma
"&bslash;&quot;"
id|a
"&bslash;&quot;"
dot
id|dword
l_int|1
id|b
comma
l_int|3
id|b
dot
id|previous
"&quot;"
multiline_comment|/* Outputs */
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dst
)paren
comma
l_string|&quot;=r&quot;
(paren
id|src
)paren
comma
l_string|&quot;=r&quot;
(paren
id|n
)paren
comma
l_string|&quot;=r&quot;
(paren
id|retn
)paren
multiline_comment|/* Inputs */
suffix:colon
l_string|&quot;0&quot;
(paren
id|dst
)paren
comma
l_string|&quot;1&quot;
(paren
id|src
)paren
comma
l_string|&quot;2&quot;
(paren
id|n
)paren
comma
l_string|&quot;3&quot;
(paren
id|retn
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Either we directly start copying here, using dword copying in a loop,&n;     or we copy as much as possible with &squot;movem&squot; and then the last block&n;     (&lt;44 bytes) is copied here.  This will work since &squot;movem&squot; will have&n;     updated src, dst and n.  (Except with failing src.)&n;&n;     Since we want to keep src accurate, we can&squot;t use&n;     __asm_copy_from_user_N with N != (1, 2, 4); it updates dst and&n;     retn, but not src (by design; it&squot;s value is ignored elsewhere).  */
r_while
c_loop
(paren
id|n
op_ge
l_int|4
)paren
(brace
id|__asm_copy_from_user_4
(paren
id|dst
comma
id|src
comma
id|retn
)paren
suffix:semicolon
id|n
op_sub_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|retn
)paren
r_goto
id|copy_exception_bytes
suffix:semicolon
)brace
multiline_comment|/* If we get here, there were no memory read faults.  */
r_switch
c_cond
(paren
id|n
)paren
(brace
multiline_comment|/* These copies are at least &quot;naturally aligned&quot; (so we don&squot;t have&n;       to check each byte), due to the src alignment code before the&n;       movem loop.  The *_3 case *will* get the correct count for retn.  */
r_case
l_int|0
suffix:colon
multiline_comment|/* This case deliberately left in (if you have doubts check the&n;&t; generated assembly code).  */
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|__asm_copy_from_user_1
(paren
id|dst
comma
id|src
comma
id|retn
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm_copy_from_user_2
(paren
id|dst
comma
id|src
comma
id|retn
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|__asm_copy_from_user_3
(paren
id|dst
comma
id|src
comma
id|retn
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* If we get here, retn correctly reflects the number of failing&n;     bytes.  */
r_return
id|retn
suffix:semicolon
id|copy_exception_bytes
suffix:colon
multiline_comment|/* We already have &quot;retn&quot; bytes cleared, and need to clear the&n;     remaining &quot;n&quot; bytes.  A non-optimized simple byte-for-byte in-line&n;     memset is preferred here, since this isn&squot;t speed-critical code and&n;     we&squot;d rather have this a leaf-function than calling memset.  */
(brace
r_char
op_star
id|endp
suffix:semicolon
r_for
c_loop
(paren
id|endp
op_assign
id|dst
op_plus
id|n
suffix:semicolon
id|dst
OL
id|endp
suffix:semicolon
id|dst
op_increment
)paren
op_star
id|dst
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|retn
op_plus
id|n
suffix:semicolon
)brace
multiline_comment|/* Zero userspace.  */
r_int
r_int
DECL|function|__do_clear_user
id|__do_clear_user
(paren
r_void
id|__user
op_star
id|pto
comma
r_int
r_int
id|pn
)paren
(brace
multiline_comment|/* We want the parameters put in special registers.&n;     Make sure the compiler is able to make something useful of this.&n;      As it is now: r10 -&gt; r13; r11 -&gt; r11 (nop); r12 -&gt; r12 (nop).&n;&n;     FIXME: Comment for old gcc version.  Check.&n;     If gcc was allright, it really would need no temporaries, and no&n;     stack space to save stuff on. */
r_register
r_char
op_star
id|dst
id|__asm__
(paren
l_string|&quot;r13&quot;
)paren
op_assign
id|pto
suffix:semicolon
r_register
r_int
id|n
id|__asm__
(paren
l_string|&quot;r12&quot;
)paren
op_assign
id|pn
suffix:semicolon
r_register
r_int
id|retn
id|__asm__
(paren
l_string|&quot;r10&quot;
)paren
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|dst
op_amp
l_int|3
)paren
op_ne
l_int|0
multiline_comment|/* Don&squot;t align if we wouldn&squot;t copy more than a few bytes.  */
op_logical_and
id|n
op_ge
l_int|3
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|dst
op_amp
l_int|1
)paren
(brace
id|__asm_clear_1
(paren
id|dst
comma
id|retn
)paren
suffix:semicolon
id|n
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|dst
op_amp
l_int|2
)paren
(brace
id|__asm_clear_2
(paren
id|dst
comma
id|retn
)paren
suffix:semicolon
id|n
op_sub_assign
l_int|2
suffix:semicolon
)brace
)brace
multiline_comment|/* Decide which copying method to use.&n;     FIXME: This number is from the &quot;ordinary&quot; kernel memset.  */
r_if
c_cond
(paren
id|n
op_ge
(paren
l_int|1
op_star
l_int|48
)paren
)paren
(brace
multiline_comment|/* For large clears we use &squot;movem&squot; */
multiline_comment|/* It is not optimal to tell the compiler about clobbering any&n;       call-saved registers; that will move the saving/restoring of&n;       those registers to the function prologue/epilogue, and make&n;       non-movem sizes suboptimal.&n;&n;       This method is not foolproof; it assumes that the &quot;asm reg&quot;&n;       declarations at the beginning of the function really are used&n;       here (beware: they may be moved to temporary registers).&n;       This way, we do not have to save/move the registers around into&n;       temporaries; we can safely use them straight away.&n;&n;      If you want to check that the allocation was right; then&n;      check the equalities in the first comment.  It should say&n;      something like &quot;r13=r13, r11=r11, r12=r12&quot;. */
id|__asm__
r_volatile
(paren
"&quot;"
dot
id|ifnc
op_mod
l_int|0
op_mod
l_int|1
op_mod
l_int|2
comma
"$"
id|r13
"$"
id|r12
"$"
id|r10
"&bslash;"
id|n
"&bslash;"
dot
id|err
"&bslash;"
id|n
"&bslash;"
dot
id|endif
"&bslash;"
id|n
"&bslash;"
suffix:semicolon
suffix:semicolon
id|Save
id|the
id|registers
id|we
"&squot;"
id|ll
id|clobber
id|in
id|the
id|movem
id|process
suffix:semicolon
suffix:semicolon
id|on
id|the
id|stack
dot
id|Don
"&squot;"
id|t
id|mention
id|them
id|to
id|gcc
comma
id|it
id|will
id|only
id|be
suffix:semicolon
suffix:semicolon
id|upset
dot
id|subq
l_int|11
op_star
l_int|4
comma
"$"
id|sp
id|movem
"$"
id|r10
comma
(braket
"$"
id|sp
)braket
id|clear.d
"$"
id|r0
id|clear.d
"$"
id|r1
id|clear.d
"$"
id|r2
id|clear.d
"$"
id|r3
id|clear.d
"$"
id|r4
id|clear.d
"$"
id|r5
id|clear.d
"$"
id|r6
id|clear.d
"$"
id|r7
id|clear.d
"$"
id|r8
id|clear.d
"$"
id|r9
id|clear.d
"$"
id|r10
id|clear.d
"$"
id|r11
suffix:semicolon
suffix:semicolon
id|Now
id|we
"&squot;"
id|ve
id|got
id|this
suffix:colon
suffix:semicolon
suffix:semicolon
id|r13
op_minus
id|dst
suffix:semicolon
suffix:semicolon
id|r12
op_minus
id|n
suffix:semicolon
suffix:semicolon
id|Update
id|n
r_for
id|the
id|first
id|loop
id|subq
l_int|12
op_star
l_int|4
comma
"$"
id|r12
l_int|0
suffix:colon
id|subq
l_int|12
op_star
l_int|4
comma
"$"
id|r12
id|bge
l_int|0
id|b
id|movem
"$"
id|r11
comma
(braket
"$"
id|r13
op_plus
)braket
l_int|1
suffix:colon
id|addq
l_int|12
op_star
l_int|4
comma
"$"
id|r12
suffix:semicolon
suffix:semicolon
id|compensate
r_for
id|last
id|loop
id|underflowing
id|n
suffix:semicolon
suffix:semicolon
id|Restore
id|registers
id|from
id|stack
id|movem
(braket
"$"
id|sp
op_plus
)braket
comma
"$"
id|r10
l_int|2
suffix:colon
dot
id|section
dot
id|fixup
comma
"&bslash;&quot;"
id|ax
"&bslash;&quot;"
l_int|3
suffix:colon
id|move.d
(braket
"$"
id|sp
)braket
comma
"$"
id|r10
id|addq
l_int|12
op_star
l_int|4
comma
"$"
id|r10
id|move.d
"$"
id|r10
comma
(braket
"$"
id|sp
)braket
id|clear.d
"$"
id|r10
id|jump
l_int|0
id|b
l_int|4
suffix:colon
id|movem
(braket
"$"
id|sp
op_plus
)braket
comma
"$"
id|r10
id|addq
l_int|12
op_star
l_int|4
comma
"$"
id|r10
id|addq
l_int|12
op_star
l_int|4
comma
"$"
id|r12
id|jump
l_int|2
id|b
dot
id|previous
dot
id|section
id|__ex_table
comma
"&bslash;&quot;"
id|a
"&bslash;&quot;"
dot
id|dword
l_int|0
id|b
comma
l_int|3
id|b
dot
id|dword
l_int|1
id|b
comma
l_int|4
id|b
dot
id|previous
"&quot;"
multiline_comment|/* Outputs */
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dst
)paren
comma
l_string|&quot;=r&quot;
(paren
id|n
)paren
comma
l_string|&quot;=r&quot;
(paren
id|retn
)paren
multiline_comment|/* Inputs */
suffix:colon
l_string|&quot;0&quot;
(paren
id|dst
)paren
comma
l_string|&quot;1&quot;
(paren
id|n
)paren
comma
l_string|&quot;2&quot;
(paren
id|retn
)paren
multiline_comment|/* Clobber */
suffix:colon
l_string|&quot;r11&quot;
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|n
op_ge
l_int|16
)paren
(brace
id|__asm_clear_16
(paren
id|dst
comma
id|retn
)paren
suffix:semicolon
id|n
op_sub_assign
l_int|16
suffix:semicolon
)brace
multiline_comment|/* Having a separate by-four loops cuts down on cache footprint.&n;     FIXME:  Test with and without; increasing switch to be 0..15.  */
r_while
c_loop
(paren
id|n
op_ge
l_int|4
)paren
(brace
id|__asm_clear_4
(paren
id|dst
comma
id|retn
)paren
suffix:semicolon
id|n
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|n
)paren
(brace
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|__asm_clear_1
(paren
id|dst
comma
id|retn
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm_clear_2
(paren
id|dst
comma
id|retn
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|__asm_clear_3
(paren
id|dst
comma
id|retn
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|retn
suffix:semicolon
)brace
eof
