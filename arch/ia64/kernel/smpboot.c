multiline_comment|/*&n; * SMP Support&n; *&n; * Application processor startup code, moved from smp.c to better support kernel profile&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/efi.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
multiline_comment|/* &n; * SAL shoves the AP&squot;s here when we start them.  Physical mode, no kernel TR, &n; * no RRs set, better than even chance that psr is bogus.  Fix all that and &n; * call _start.  In effect, pretend to be lilo.&n; *&n; * Stolen from lilo_start.c.  Thanks David! &n; */
r_void
DECL|function|start_ap
id|start_ap
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|_start
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n;&t; * Install a translation register that identity maps the&n;&t; * kernel&squot;s 256MB page(s).&n;&t; */
id|ia64_clear_ic
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ia64_set_rr
c_func
(paren
l_int|0
comma
(paren
l_int|0x1000
op_lshift
l_int|8
)paren
op_or
(paren
id|_PAGE_SIZE_1M
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
id|ia64_set_rr
c_func
(paren
id|PAGE_OFFSET
comma
(paren
id|ia64_rid
c_func
(paren
l_int|0
comma
id|PAGE_OFFSET
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|_PAGE_SIZE_256M
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
id|ia64_itr
c_func
(paren
l_int|0x3
comma
l_int|1
comma
id|PAGE_OFFSET
comma
id|pte_val
c_func
(paren
id|mk_pte_phys
c_func
(paren
l_int|0
comma
id|__pgprot
c_func
(paren
id|__DIRTY_BITS
op_or
id|_PAGE_PL_0
op_or
id|_PAGE_AR_RWX
)paren
)paren
)paren
comma
id|_PAGE_SIZE_256M
)paren
suffix:semicolon
id|ia64_srlz_i
c_func
(paren
)paren
suffix:semicolon
id|flags
op_assign
(paren
id|IA64_PSR_IT
op_or
id|IA64_PSR_IC
op_or
id|IA64_PSR_DT
op_or
id|IA64_PSR_RT
op_or
id|IA64_PSR_DFH
op_or
id|IA64_PSR_BN
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl r8 = 1f&bslash;n&quot;
l_string|&quot;;;&bslash;n&quot;
l_string|&quot;mov cr.ipsr=%0&bslash;n&quot;
l_string|&quot;mov cr.iip=r8&bslash;n&quot;
l_string|&quot;mov cr.ifs=r0&bslash;n&quot;
l_string|&quot;;;&bslash;n&quot;
l_string|&quot;rfi;;&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;movl r1 = __gp&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|flags
)paren
suffix:colon
l_string|&quot;r8&quot;
)paren
suffix:semicolon
id|_start
c_func
(paren
)paren
suffix:semicolon
)brace
eof
