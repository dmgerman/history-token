multiline_comment|/*&n; * Suspend support specific for i386.&n; *&n; * Distribute under GPLv2&n; *&n; * Copyright (c) 2002 Pavel Machek &lt;pavel@suse.cz&gt;&n; * Copyright (c) 2001 Patrick Mochel &lt;mochel@osdl.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/acpi.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|variable|saved_context
r_static
r_struct
id|saved_context
id|saved_context
suffix:semicolon
r_static
r_void
id|fix_processor_context
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|saved_context_eax
DECL|variable|saved_context_ebx
r_int
r_int
id|saved_context_eax
comma
id|saved_context_ebx
suffix:semicolon
DECL|variable|saved_context_ecx
DECL|variable|saved_context_edx
r_int
r_int
id|saved_context_ecx
comma
id|saved_context_edx
suffix:semicolon
DECL|variable|saved_context_esp
DECL|variable|saved_context_ebp
r_int
r_int
id|saved_context_esp
comma
id|saved_context_ebp
suffix:semicolon
DECL|variable|saved_context_esi
DECL|variable|saved_context_edi
r_int
r_int
id|saved_context_esi
comma
id|saved_context_edi
suffix:semicolon
DECL|variable|saved_context_eflags
r_int
r_int
id|saved_context_eflags
suffix:semicolon
r_extern
r_void
id|enable_sep_cpu
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|function|save_processor_state
r_void
id|save_processor_state
c_func
(paren
r_void
)paren
(brace
id|kernel_fpu_begin
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * descriptor tables&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;sgdt %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_context.gdt_limit
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;sidt %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_context.idt_limit
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;sldt %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_context.ldt
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;str %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_context.tr
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * segment registers&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;movw %%es, %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_context.es
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movw %%fs, %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_context.fs
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movw %%gs, %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_context.gs
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movw %%ss, %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_context.ss
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * control registers &n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;movl %%cr0, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|saved_context.cr0
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%cr2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|saved_context.cr2
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%cr3, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|saved_context.cr3
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%cr4, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|saved_context.cr4
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|do_fpu_end
id|do_fpu_end
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* restore FPU regs if necessary */
multiline_comment|/* Do it out of line so that gcc does not move cr0 load to some stupid place */
id|kernel_fpu_end
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|restore_processor_state
r_void
id|restore_processor_state
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * control registers&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;movl %0, %%cr4&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|saved_context.cr4
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %0, %%cr3&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|saved_context.cr3
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %0, %%cr2&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|saved_context.cr2
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %0, %%cr0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|saved_context.cr0
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * segment registers&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;movw %0, %%es&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|saved_context.es
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movw %0, %%fs&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|saved_context.fs
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movw %0, %%gs&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|saved_context.gs
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movw %0, %%ss&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|saved_context.ss
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * now restore the descriptor tables to their proper values&n;&t; * ltr is done i fix_processor_context().&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;lgdt %0&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|saved_context.gdt_limit
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;lidt %0&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|saved_context.idt_limit
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;lldt %0&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|saved_context.ldt
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * sysenter MSRs&n;&t; */
r_if
c_cond
(paren
id|boot_cpu_has
c_func
(paren
id|X86_FEATURE_SEP
)paren
)paren
id|enable_sep_cpu
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|fix_processor_context
c_func
(paren
)paren
suffix:semicolon
id|do_fpu_end
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|fix_processor_context
r_static
r_void
id|fix_processor_context
c_func
(paren
r_void
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_struct
id|tss_struct
op_star
id|t
op_assign
id|init_tss
op_plus
id|cpu
suffix:semicolon
id|set_tss_desc
c_func
(paren
id|cpu
comma
id|t
)paren
suffix:semicolon
multiline_comment|/* This just modifies memory; should not be necessary. But... This is necessary, because 386 hardware has concept of busy TSS or some similar stupidity. */
id|cpu_gdt_table
(braket
id|cpu
)braket
(braket
id|GDT_ENTRY_TSS
)braket
dot
id|b
op_and_assign
l_int|0xfffffdff
suffix:semicolon
id|load_TR_desc
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* This does ltr */
id|load_LDT
c_func
(paren
op_amp
id|current-&gt;active_mm-&gt;context
)paren
suffix:semicolon
multiline_comment|/* This does lldt */
multiline_comment|/*&n;&t; * Now maybe reload the debug registers&n;&t; */
r_if
c_cond
(paren
id|current-&gt;thread.debugreg
(braket
l_int|7
)braket
)paren
(brace
id|loaddebug
c_func
(paren
op_amp
id|current-&gt;thread
comma
l_int|0
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
op_amp
id|current-&gt;thread
comma
l_int|1
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
op_amp
id|current-&gt;thread
comma
l_int|2
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
op_amp
id|current-&gt;thread
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* no 4 and 5 */
id|loaddebug
c_func
(paren
op_amp
id|current-&gt;thread
comma
l_int|6
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
op_amp
id|current-&gt;thread
comma
l_int|7
)paren
suffix:semicolon
)brace
)brace
DECL|variable|save_processor_state
id|EXPORT_SYMBOL
c_func
(paren
id|save_processor_state
)paren
suffix:semicolon
DECL|variable|restore_processor_state
id|EXPORT_SYMBOL
c_func
(paren
id|restore_processor_state
)paren
suffix:semicolon
eof
