multiline_comment|/*&n; *  arch/s390/kernel/cpcmd.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *               Christian Borntraeger (cborntra@de.ibm.com),&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/ebcdic.h&gt;
macro_line|#include &lt;asm/cpcmd.h&gt;
macro_line|#include &lt;asm/system.h&gt;
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|cpcmd_lock
)paren
suffix:semicolon
DECL|variable|cpcmd_buf
r_static
r_char
id|cpcmd_buf
(braket
l_int|240
)braket
suffix:semicolon
multiline_comment|/*&n; * the caller of __cpcmd has to ensure that the response buffer is below 2 GB&n; */
DECL|function|__cpcmd
r_void
id|__cpcmd
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
id|BUG_ON
c_func
(paren
id|cmdlen
OG
l_int|240
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
id|memset
c_func
(paren
id|response
comma
l_int|0
comma
id|rlen
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_ARCH_S390X
id|asm
r_volatile
(paren
l_string|&quot;LRA   2,0(%0)&bslash;n&bslash;t&quot;
l_string|&quot;LR    4,%1&bslash;n&bslash;t&quot;
l_string|&quot;O     4,%4&bslash;n&bslash;t&quot;
l_string|&quot;LRA   3,0(%2)&bslash;n&bslash;t&quot;
l_string|&quot;LR    5,%3&bslash;n&bslash;t&quot;
l_string|&quot;.long 0x83240008 # Diagnose X&squot;08&squot;&bslash;n&bslash;t&quot;
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
l_string|&quot;cc&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
comma
l_string|&quot;4&quot;
comma
l_string|&quot;5&quot;
)paren
suffix:semicolon
macro_line|#else /* CONFIG_ARCH_S390X */
id|asm
r_volatile
(paren
l_string|&quot;   lrag  2,0(%0)&bslash;n&quot;
l_string|&quot;   lgr   4,%1&bslash;n&quot;
l_string|&quot;   o     4,%4&bslash;n&quot;
l_string|&quot;   lrag  3,0(%2)&bslash;n&quot;
l_string|&quot;   lgr   5,%3&bslash;n&quot;
l_string|&quot;   sam31&bslash;n&quot;
l_string|&quot;   .long 0x83240008 # Diagnose X&squot;08&squot;&bslash;n&quot;
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
l_string|&quot;cc&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
comma
l_string|&quot;4&quot;
comma
l_string|&quot;5&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ARCH_S390X */
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
macro_line|#ifndef CONFIG_ARCH_S390X
id|asm
r_volatile
(paren
l_string|&quot;LRA   2,0(%0)&bslash;n&bslash;t&quot;
l_string|&quot;LR    3,%1&bslash;n&bslash;t&quot;
l_string|&quot;.long 0x83230008 # Diagnose X&squot;08&squot;&bslash;n&bslash;t&quot;
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
macro_line|#else /* CONFIG_ARCH_S390X */
id|asm
r_volatile
(paren
l_string|&quot;   lrag  2,0(%0)&bslash;n&quot;
l_string|&quot;   lgr   3,%1&bslash;n&quot;
l_string|&quot;   sam31&bslash;n&quot;
l_string|&quot;   .long 0x83230008 # Diagnose X&squot;08&squot;&bslash;n&quot;
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
macro_line|#endif /* CONFIG_ARCH_S390X */
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
DECL|variable|__cpcmd
id|EXPORT_SYMBOL
c_func
(paren
id|__cpcmd
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ARCH_S390X
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
r_char
op_star
id|lowbuf
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rlen
op_eq
l_int|0
)paren
op_logical_or
(paren
id|response
op_eq
l_int|NULL
)paren
op_logical_or
op_logical_neg
(paren
(paren
r_int
r_int
)paren
id|response
op_rshift
l_int|31
)paren
)paren
id|__cpcmd
c_func
(paren
id|cmd
comma
id|response
comma
id|rlen
)paren
suffix:semicolon
r_else
(brace
id|lowbuf
op_assign
id|kmalloc
c_func
(paren
id|rlen
comma
id|GFP_KERNEL
op_or
id|GFP_DMA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lowbuf
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;cpcmd: could not allocate response buffer&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|__cpcmd
c_func
(paren
id|cmd
comma
id|lowbuf
comma
id|rlen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|response
comma
id|lowbuf
comma
id|rlen
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|lowbuf
)paren
suffix:semicolon
)brace
)brace
DECL|variable|cpcmd
id|EXPORT_SYMBOL
c_func
(paren
id|cpcmd
)paren
suffix:semicolon
macro_line|#endif&t;&t;/* CONFIG_ARCH_S390X */
eof
