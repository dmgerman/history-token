multiline_comment|/* &n; * Copyright (C) 2001 Chris Emerson (cemerson@chiark.greenend.org.uk)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/kernel.h&quot;
macro_line|#include &quot;linux/smp.h&quot;
macro_line|#include &quot;asm/ptrace.h&quot;
macro_line|#include &quot;sysrq.h&quot;
DECL|function|show_regs
r_void
id|show_regs
c_func
(paren
r_struct
id|pt_regs_subarch
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;show_regs(): insert regs here.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;EIP: %04x:[&lt;%08lx&gt;] CPU: %d&quot;
comma
l_int|0xffff
op_amp
id|regs-&gt;xcs
comma
id|regs-&gt;eip
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;xcs
op_amp
l_int|3
)paren
id|printk
c_func
(paren
l_string|&quot; ESP: %04x:%08lx&quot;
comma
l_int|0xffff
op_amp
id|regs-&gt;xss
comma
id|regs-&gt;esp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; EFLAGS: %08lx&bslash;n&quot;
comma
id|regs-&gt;eflags
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;EAX: %08lx EBX: %08lx ECX: %08lx EDX: %08lx&bslash;n&quot;
comma
id|regs-&gt;eax
comma
id|regs-&gt;ebx
comma
id|regs-&gt;ecx
comma
id|regs-&gt;edx
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ESI: %08lx EDI: %08lx EBP: %08lx&quot;
comma
id|regs-&gt;esi
comma
id|regs-&gt;edi
comma
id|regs-&gt;ebp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; DS: %04x ES: %04x&bslash;n&quot;
comma
l_int|0xffff
op_amp
id|regs-&gt;xds
comma
l_int|0xffff
op_amp
id|regs-&gt;xes
)paren
suffix:semicolon
macro_line|#endif
id|show_trace
c_func
(paren
op_amp
id|regs-&gt;gpr
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
