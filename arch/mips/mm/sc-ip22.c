multiline_comment|/*&n; * sc-ip22.c: Indy cache management functions.&n; *&n; * Copyright (C) 1997, 2001 Ralf Baechle (ralf@gnu.org),&n; * derived from r4xx0.c by David S. Miller (dm@engr.sgi.com).&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/bcache.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/sgi/ip22.h&gt;
macro_line|#include &lt;asm/sgi/mc.h&gt;
multiline_comment|/* Secondary cache size in bytes, if present.  */
DECL|variable|scache_size
r_static
r_int
r_int
id|scache_size
suffix:semicolon
DECL|macro|DEBUG_CACHE
macro_line|#undef DEBUG_CACHE
DECL|macro|SC_SIZE
mdefine_line|#define SC_SIZE 0x00080000
DECL|macro|SC_LINE
mdefine_line|#define SC_LINE 32
DECL|macro|CI_MASK
mdefine_line|#define CI_MASK (SC_SIZE - SC_LINE)
DECL|macro|SC_INDEX
mdefine_line|#define SC_INDEX(n) ((n) &amp; CI_MASK)
DECL|function|indy_sc_wipe
r_static
r_inline
r_void
id|indy_sc_wipe
c_func
(paren
r_int
r_int
id|first
comma
r_int
r_int
id|last
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tpush&bslash;t&bslash;t&bslash;t# indy_sc_wipe&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips3&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;mfc0&bslash;t%2, $12&bslash;n&bslash;t&quot;
l_string|&quot;li&bslash;t$1, 0x80&bslash;t&bslash;t&bslash;t# Go 64 bit&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t$1, $12&bslash;n&bslash;t&quot;
l_string|&quot;dli&bslash;t$1, 0x9000000080000000&bslash;n&bslash;t&quot;
l_string|&quot;or&bslash;t%0, $1&bslash;t&bslash;t&bslash;t# first line to flush&bslash;n&bslash;t&quot;
l_string|&quot;or&bslash;t%1, $1&bslash;t&bslash;t&bslash;t# last line to flush&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;tsw&bslash;t$0, 0(%0)&bslash;n&bslash;t&quot;
l_string|&quot;bne&bslash;t%0, %1, 1b&bslash;n&bslash;t&quot;
l_string|&quot; daddu&bslash;t%0, 32&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t%2, $12&bslash;t&bslash;t&bslash;t# Back to 32 bit&bslash;n&bslash;t&quot;
l_string|&quot;nop; nop; nop; nop;&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|first
)paren
comma
l_string|&quot;=r&quot;
(paren
id|last
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|first
)paren
comma
l_string|&quot;1&quot;
(paren
id|last
)paren
)paren
suffix:semicolon
)brace
DECL|function|indy_sc_wback_invalidate
r_static
r_void
id|indy_sc_wback_invalidate
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|first_line
comma
id|last_line
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
macro_line|#ifdef DEBUG_CACHE
id|printk
c_func
(paren
l_string|&quot;indy_sc_wback_invalidate[%08lx,%08lx]&quot;
comma
id|addr
comma
id|size
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
suffix:semicolon
multiline_comment|/* Which lines to flush?  */
id|first_line
op_assign
id|SC_INDEX
c_func
(paren
id|addr
)paren
suffix:semicolon
id|last_line
op_assign
id|SC_INDEX
c_func
(paren
id|addr
op_plus
id|size
op_minus
l_int|1
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|first_line
op_le
id|last_line
)paren
(brace
id|indy_sc_wipe
c_func
(paren
id|first_line
comma
id|last_line
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|indy_sc_wipe
c_func
(paren
id|first_line
comma
id|SC_SIZE
op_minus
id|SC_LINE
)paren
suffix:semicolon
id|indy_sc_wipe
c_func
(paren
l_int|0
comma
id|last_line
)paren
suffix:semicolon
id|out
suffix:colon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|indy_sc_enable
r_static
r_void
id|indy_sc_enable
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|addr
comma
id|tmp1
comma
id|tmp2
suffix:semicolon
multiline_comment|/* This is really cool... */
macro_line|#ifdef DEBUG_CACHE
id|printk
c_func
(paren
l_string|&quot;Enabling R4600 SCACHE&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tpush&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips3&bslash;n&bslash;t&quot;
l_string|&quot;mfc0&bslash;t%2, $12&bslash;n&bslash;t&quot;
l_string|&quot;nop; nop; nop; nop;&bslash;n&bslash;t&quot;
l_string|&quot;li&bslash;t%1, 0x80&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t%1, $12&bslash;n&bslash;t&quot;
l_string|&quot;nop; nop; nop; nop;&bslash;n&bslash;t&quot;
l_string|&quot;li&bslash;t%0, 0x1&bslash;n&bslash;t&quot;
l_string|&quot;dsll&bslash;t%0, 31&bslash;n&bslash;t&quot;
l_string|&quot;lui&bslash;t%1, 0x9000&bslash;n&bslash;t&quot;
l_string|&quot;dsll32&bslash;t%1, 0&bslash;n&bslash;t&quot;
l_string|&quot;or&bslash;t%0, %1, %0&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0(%0)&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t$0, $12&bslash;n&bslash;t&quot;
l_string|&quot;nop; nop; nop; nop;&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t%2, $12&bslash;n&bslash;t&quot;
l_string|&quot;nop; nop; nop; nop;&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp2
)paren
comma
l_string|&quot;=r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|indy_sc_disable
r_static
r_void
id|indy_sc_disable
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tmp1
comma
id|tmp2
comma
id|tmp3
suffix:semicolon
macro_line|#ifdef DEBUG_CACHE
id|printk
c_func
(paren
l_string|&quot;Disabling R4600 SCACHE&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tpush&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips3&bslash;n&bslash;t&quot;
l_string|&quot;li&bslash;t%0, 0x1&bslash;n&bslash;t&quot;
l_string|&quot;dsll&bslash;t%0, 31&bslash;n&bslash;t&quot;
l_string|&quot;lui&bslash;t%1, 0x9000&bslash;n&bslash;t&quot;
l_string|&quot;dsll32&bslash;t%1, 0&bslash;n&bslash;t&quot;
l_string|&quot;or&bslash;t%0, %1, %0&bslash;n&bslash;t&quot;
l_string|&quot;mfc0&bslash;t%2, $12&bslash;n&bslash;t&quot;
l_string|&quot;nop; nop; nop; nop&bslash;n&bslash;t&quot;
l_string|&quot;li&bslash;t%1, 0x80&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t%1, $12&bslash;n&bslash;t&quot;
l_string|&quot;nop; nop; nop; nop&bslash;n&bslash;t&quot;
l_string|&quot;sh&bslash;t$0, 0(%0)&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t$0, $12&bslash;n&bslash;t&quot;
l_string|&quot;nop; nop; nop; nop&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t%2, $12&bslash;n&bslash;t&quot;
l_string|&quot;nop; nop; nop; nop&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp2
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp3
)paren
)paren
suffix:semicolon
)brace
DECL|function|indy_sc_probe
r_static
r_inline
r_int
id|__init
id|indy_sc_probe
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|size
op_assign
id|ip22_eeprom_read
c_func
(paren
op_amp
id|sgimc-&gt;eeprom
comma
l_int|17
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|size
op_lshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;R4600/R5000 SCACHE size %dK, linesize 32 bytes.&bslash;n&quot;
comma
id|size
op_rshift
l_int|10
)paren
suffix:semicolon
id|scache_size
op_assign
id|size
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* XXX Check with wje if the Indy caches can differenciate between&n;   writeback + invalidate and just invalidate.  */
DECL|variable|indy_sc_ops
r_struct
id|bcache_ops
id|indy_sc_ops
op_assign
(brace
dot
id|bc_enable
op_assign
id|indy_sc_enable
comma
dot
id|bc_disable
op_assign
id|indy_sc_disable
comma
dot
id|bc_wback_inv
op_assign
id|indy_sc_wback_invalidate
comma
dot
id|bc_inv
op_assign
id|indy_sc_wback_invalidate
)brace
suffix:semicolon
DECL|function|indy_sc_init
r_void
id|__init
id|indy_sc_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|indy_sc_probe
c_func
(paren
)paren
)paren
(brace
id|indy_sc_enable
c_func
(paren
)paren
suffix:semicolon
id|bcops
op_assign
op_amp
id|indy_sc_ops
suffix:semicolon
)brace
)brace
eof
