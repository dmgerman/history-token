multiline_comment|/*#************************************************************************#*/
multiline_comment|/*#-------------------------------------------------------------------------*/
multiline_comment|/*#                                                                         */
multiline_comment|/*# FUNCTION NAME: memcpy()                                                 */
multiline_comment|/*#                                                                         */
multiline_comment|/*# PARAMETERS:  void* dst;   Destination address.                          */
multiline_comment|/*#              void* src;   Source address.                               */
multiline_comment|/*#              int   len;   Number of bytes to copy.                      */
multiline_comment|/*#                                                                         */
multiline_comment|/*# RETURNS:     dst.                                                       */
multiline_comment|/*#                                                                         */
multiline_comment|/*# DESCRIPTION: Copies len bytes of memory from src to dst.  No guarantees */
multiline_comment|/*#              about copying of overlapping memory areas. This routine is */
multiline_comment|/*#              very sensitive to compiler changes in register allocation. */
multiline_comment|/*#              Should really be rewritten to avoid this problem.          */
multiline_comment|/*#                                                                         */
multiline_comment|/*#-------------------------------------------------------------------------*/
multiline_comment|/*#                                                                         */
multiline_comment|/*# HISTORY                                                                 */
multiline_comment|/*#                                                                         */
multiline_comment|/*# DATE      NAME            CHANGES                                       */
multiline_comment|/*# ----      ----            -------                                       */
multiline_comment|/*# 941007    Kenny R         Creation                                      */
multiline_comment|/*# 941011    Kenny R         Lots of optimizations and inlining.           */
multiline_comment|/*# 941129    Ulf A           Adapted for use in libc.                      */
multiline_comment|/*# 950216    HP              N==0 forgotten if non-aligned src/dst.        */
multiline_comment|/*#                           Added some optimizations.                     */
multiline_comment|/*# 001025    HP              Make src and dst char *.  Align dst to&t;    */
multiline_comment|/*#&t;&t;&t;      dword, not just word-if-both-src-and-dst-&t;    */
multiline_comment|/*#&t;&t;&t;      are-misaligned.&t;&t;&t;&t;    */
multiline_comment|/*#                                                                         */
multiline_comment|/*#-------------------------------------------------------------------------*/
DECL|function|memcpy
r_void
op_star
id|memcpy
c_func
(paren
r_void
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
multiline_comment|/* Ok.  Now we want the parameters put in special registers.&n;     Make sure the compiler is able to make something useful of this.&n;      As it is now: r10 -&gt; r13; r11 -&gt; r11 (nop); r12 -&gt; r12 (nop).&n;&n;     If gcc was allright, it really would need no temporaries, and no&n;     stack space to save stuff on. */
r_register
r_void
op_star
id|return_dst
id|__asm__
(paren
l_string|&quot;r10&quot;
)paren
op_assign
id|pdst
suffix:semicolon
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
id|n
op_decrement
suffix:semicolon
op_star
(paren
r_char
op_star
)paren
id|dst
op_assign
op_star
(paren
r_char
op_star
)paren
id|src
suffix:semicolon
id|src
op_increment
suffix:semicolon
id|dst
op_increment
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
id|n
op_sub_assign
l_int|2
suffix:semicolon
op_star
(paren
r_int
op_star
)paren
id|dst
op_assign
op_star
(paren
r_int
op_star
)paren
id|src
suffix:semicolon
id|src
op_add_assign
l_int|2
suffix:semicolon
id|dst
op_add_assign
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
multiline_comment|/* Break even between movem and&n;                                   move16 is at 38.7*2, but modulo 44. */
(brace
multiline_comment|/* For large copies we use &squot;movem&squot; */
multiline_comment|/* It is not optimal to tell the compiler about clobbering any&n;     registers; that will move the saving/restoring of those registers&n;     to the function prologue/epilogue, and make non-movem sizes&n;     suboptimal.&n;&n;      This method is not foolproof; it assumes that the &quot;asm reg&quot;&n;     declarations at the beginning of the function really are used&n;     here (beware: they may be moved to temporary registers).&n;      This way, we do not have to save/move the registers around into&n;     temporaries; we can safely use them straight away.&n;&n;      If you want to check that the allocation was right; then&n;      check the equalities in the first comment.  It should say&n;      &quot;r13=r13, r11=r11, r12=r12&quot; */
id|__asm__
r_volatile
(paren
"&quot;"
suffix:semicolon
suffix:semicolon
id|Check
id|that
id|the
id|following
id|is
l_bool|true
(paren
id|same
r_register
id|names
id|on
suffix:semicolon
suffix:semicolon
id|both
id|sides
id|of
id|equal
id|sign
comma
id|as
id|in
id|r8
op_assign
id|r8
)paren
suffix:colon
suffix:semicolon
suffix:semicolon
op_mod
l_int|0
op_assign
id|r13
comma
op_mod
l_int|1
op_assign
id|r11
comma
op_mod
l_int|2
op_assign
id|r12
suffix:semicolon
suffix:semicolon
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
id|sp
id|movem
id|r10
comma
(braket
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
id|r12
l_int|0
suffix:colon
id|movem
(braket
id|r11
op_plus
)braket
comma
id|r10
id|subq
l_int|44
comma
id|r12
id|bge
l_int|0
id|b
id|movem
id|r10
comma
(braket
id|r13
op_plus
)braket
id|addq
l_int|44
comma
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
id|sp
op_plus
)braket
comma
id|r10
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
)paren
suffix:semicolon
)brace
multiline_comment|/* Either we directly starts copying, using dword copying&n;     in a loop, or we copy as much as possible with &squot;movem&squot; &n;     and then the last block (&lt;44 bytes) is copied here.&n;     This will work since &squot;movem&squot; will have updated src,dst,n. */
r_while
c_loop
(paren
id|n
op_ge
l_int|16
)paren
(brace
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
id|n
op_sub_assign
l_int|16
suffix:semicolon
)brace
multiline_comment|/* A switch() is definitely the fastest although it takes a LOT of code.&n;   * Particularly if you inline code this.&n;   */
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
op_star
(paren
r_char
op_star
)paren
id|dst
op_assign
op_star
(paren
r_char
op_star
)paren
id|src
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
(paren
r_int
op_star
)paren
id|dst
op_assign
op_star
(paren
r_int
op_star
)paren
id|src
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
r_char
op_star
)paren
id|dst
op_assign
op_star
(paren
r_char
op_star
)paren
id|src
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
r_char
op_star
)paren
id|dst
op_assign
op_star
(paren
r_char
op_star
)paren
id|src
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
r_int
op_star
)paren
id|dst
op_assign
op_star
(paren
r_int
op_star
)paren
id|src
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
r_char
op_star
)paren
id|dst
op_assign
op_star
(paren
r_char
op_star
)paren
id|src
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9
suffix:colon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
r_char
op_star
)paren
id|dst
op_assign
op_star
(paren
r_char
op_star
)paren
id|src
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
r_int
op_star
)paren
id|dst
op_assign
op_star
(paren
r_int
op_star
)paren
id|src
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
r_char
op_star
)paren
id|dst
op_assign
op_star
(paren
r_char
op_star
)paren
id|src
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|12
suffix:colon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|13
suffix:colon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
r_char
op_star
)paren
id|dst
op_assign
op_star
(paren
r_char
op_star
)paren
id|src
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|14
suffix:colon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
r_int
op_star
)paren
id|dst
op_assign
op_star
(paren
r_int
op_star
)paren
id|src
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|15
suffix:colon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|dst
)paren
op_increment
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|src
)paren
op_increment
suffix:semicolon
op_star
(paren
r_char
op_star
)paren
id|dst
op_assign
op_star
(paren
r_char
op_star
)paren
id|src
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|return_dst
suffix:semicolon
multiline_comment|/* destination pointer. */
)brace
multiline_comment|/* memcpy() */
eof
