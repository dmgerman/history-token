multiline_comment|/*&n; *   linux/arch/parisc/kernel/pa7300lc.c&n; *&t;- PA7300LC-specific functions&t;&n; *&n; *   Copyright (C) 2000 Philipp Rumpf */
macro_line|#include &lt;asm/gsc.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
multiline_comment|/* CPU register indices */
DECL|macro|MIOC_STATUS
mdefine_line|#define MIOC_STATUS&t;0xf040
DECL|macro|MIOC_CONTROL
mdefine_line|#define MIOC_CONTROL&t;0xf080
DECL|macro|MDERRADD
mdefine_line|#define MDERRADD&t;0xf0e0
DECL|macro|DMAERR
mdefine_line|#define DMAERR&t;&t;0xf0e8
DECL|macro|DIOERR
mdefine_line|#define DIOERR&t;&t;0xf0ec
DECL|macro|HIDMAMEM
mdefine_line|#define HIDMAMEM&t;0xf0f4
multiline_comment|/* read CPU Diagnose register index */
DECL|function|diag_read
r_static
id|u32
id|diag_read
c_func
(paren
r_int
id|index
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* this returns the HPA of the CPU it was called on */
DECL|function|cpu_hpa
r_static
id|u32
id|cpu_hpa
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0xfffb0000
suffix:semicolon
)brace
DECL|function|pa7300lc_lpmc
r_static
r_void
id|pa7300lc_lpmc
c_func
(paren
r_int
id|code
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|u32
id|hpa
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;LPMC on CPU %d&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|hpa
op_assign
id|cpu_hpa
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;MIOC_CONTROL %08x&bslash;n&quot;
l_string|&quot;MIOC_STATUS  %08x&bslash;n&quot;
l_string|&quot;MDERRADD     %08x&bslash;n&quot;
l_string|&quot;DMAERR       %08x&bslash;n&quot;
l_string|&quot;DIOERR       %08x&bslash;n&quot;
l_string|&quot;HIDMAMEM     %08x&bslash;n&quot;
comma
id|gsc_readl
c_func
(paren
id|hpa
op_plus
id|MIOC_CONTROL
)paren
comma
id|gsc_readl
c_func
(paren
id|hpa
op_plus
id|MIOC_STATUS
)paren
comma
id|gsc_readl
c_func
(paren
id|hpa
op_plus
id|MDERRADD
)paren
comma
id|gsc_readl
c_func
(paren
id|hpa
op_plus
id|DMAERR
)paren
comma
id|gsc_readl
c_func
(paren
id|hpa
op_plus
id|DIOERR
)paren
comma
id|gsc_readl
c_func
(paren
id|hpa
op_plus
id|HIDMAMEM
)paren
)paren
suffix:semicolon
)brace
DECL|function|pa7300lc_init
r_void
id|pa7300lc_init
c_func
(paren
r_void
)paren
(brace
id|cpu_lpmc
op_assign
id|pa7300lc_lpmc
suffix:semicolon
)brace
eof
