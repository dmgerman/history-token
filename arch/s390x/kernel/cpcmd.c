multiline_comment|/*&n; *  arch/s390/kernel/cpcmd.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/cpcmd.h&gt;
macro_line|#include &lt;asm/ebcdic.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|variable|cpcmd_lock
r_static
id|spinlock_t
id|cpcmd_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|cpcmd_buf
r_static
r_char
id|cpcmd_buf
(braket
l_int|128
)braket
suffix:semicolon
DECL|function|cpcmd
r_void
id|cpcmd
c_func
(paren
r_char
op_star
id|cmd
comma
r_char
op_star
id|response
comma
r_int
id|rlen
)paren
(brace
r_const
r_int
id|mask
op_assign
l_int|0x40000000L
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|cmdlen
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|cpcmd_lock
comma
id|flags
)paren
suffix:semicolon
id|cmdlen
op_assign
id|strlen
c_func
(paren
id|cmd
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|cpcmd_buf
comma
id|cmd
)paren
suffix:semicolon
id|ASCEBC
c_func
(paren
id|cpcmd_buf
comma
id|cmdlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|response
op_ne
l_int|NULL
op_logical_and
id|rlen
OG
l_int|0
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;   lrag  2,0(%0)&bslash;n&quot;
l_string|&quot;   lgr   4,%1&bslash;n&quot;
l_string|&quot;   o     4,%4&bslash;n&quot;
l_string|&quot;   lrag  3,0(%2)&bslash;n&quot;
l_string|&quot;   lgr   5,%3&bslash;n&quot;
l_string|&quot;   sam31&bslash;n&quot;
l_string|&quot;   .long 0x83240008 # Diagnose 83&bslash;n&quot;
l_string|&quot;   sam64&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;a&quot;
(paren
id|cpcmd_buf
)paren
comma
l_string|&quot;d&quot;
(paren
id|cmdlen
)paren
comma
l_string|&quot;a&quot;
(paren
id|response
)paren
comma
l_string|&quot;d&quot;
(paren
id|rlen
)paren
comma
l_string|&quot;m&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
comma
l_string|&quot;4&quot;
comma
l_string|&quot;5&quot;
)paren
suffix:semicolon
id|EBCASC
c_func
(paren
id|response
comma
id|rlen
)paren
suffix:semicolon
)brace
r_else
(brace
id|asm
r_volatile
(paren
l_string|&quot;   lrag  2,0(%0)&bslash;n&quot;
l_string|&quot;   lgr   3,%1&bslash;n&quot;
l_string|&quot;   sam31&bslash;n&quot;
l_string|&quot;   .long 0x83230008 # Diagnose 83&bslash;n&quot;
l_string|&quot;   sam64&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;a&quot;
(paren
id|cpcmd_buf
)paren
comma
l_string|&quot;d&quot;
(paren
id|cmdlen
)paren
suffix:colon
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|cpcmd_lock
comma
id|flags
)paren
suffix:semicolon
)brace
eof
