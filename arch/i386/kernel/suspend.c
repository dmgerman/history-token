multiline_comment|/*&n; * Suspend support specific for i386.&n; *&n; * Distribute under GPLv2&n; *&n; * Copyright (c) 2002 Pavel Machek &lt;pavel@suse.cz&gt;&n; */
DECL|macro|ACPI_C
mdefine_line|#define ACPI_C
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;linux/compatmac.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/acpi.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|variable|saved_context
r_static
r_struct
id|saved_context
id|saved_context
suffix:semicolon
multiline_comment|/*&n; * save_processor_context&n; * &n; * Save the state of the processor before we go to sleep.&n; *&n; * return_stack is the value of the stack pointer (%esp) as the caller sees it.&n; * A good way could not be found to obtain it from here (don&squot;t want to make _too_&n; * many assumptions about the layout of the stack this far down.) Also, the &n; * handy little __builtin_frame_pointer(level) where level &gt; 0, is blatantly &n; * buggy - it returns the value of the stack at the proper location, not the &n; * location, like it should (as of gcc 2.91.66)&n; * &n; * Note that the context and timing of this function is pretty critical.&n; * With a minimal amount of things going on in the caller and in here, gcc&n; * does a good job of being just a dumb compiler.  Watch the assembly output&n; * if anything changes, though, and make sure everything is going in the right&n; * place. &n; */
DECL|function|save_processor_context
r_static
r_inline
r_void
id|save_processor_context
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
l_string|&quot;sgdt (%0)&quot;
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
l_string|&quot;sidt (%0)&quot;
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
l_string|&quot;sldt (%0)&quot;
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
l_string|&quot;str (%0)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_context.tr
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * save the general registers.&n;&t; * note that gcc has constructs to specify output of certain registers,&n;&t; * but they&squot;re not used here, because it assumes that you want to modify&n;&t; * those registers, so it tries to be smart and save them beforehand.&n;&t; * It&squot;s really not necessary, and kinda fishy (check the assembly output),&n;&t; * so it&squot;s avoided. &n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;movl %%esp, (%0)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_context.esp
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%eax, (%0)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_context.eax
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%ebx, (%0)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_context.ebx
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%ecx, (%0)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_context.ecx
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%edx, (%0)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_context.edx
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%ebp, (%0)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_context.ebp
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%esi, (%0)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_context.esi
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%edi, (%0)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_context.edi
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * segment registers&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;movw %%es, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
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
l_string|&quot;=r&quot;
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
l_string|&quot;=r&quot;
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
l_string|&quot;=r&quot;
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
multiline_comment|/*&n;&t; * eflags&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;pushfl ; popl (%0)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_context.eflags
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * restore_processor_context&n; * &n; * Restore the processor context as it was before we went to sleep&n; * - descriptor tables&n; * - control registers&n; * - segment registers&n; * - flags&n; * &n; * Note that it is critical that this function is declared inline.  &n; * It was separated out from restore_state to make that function&n; * a little clearer, but it needs to be inlined because we won&squot;t have a&n; * stack when we get here (so we can&squot;t push a return address).&n; */
DECL|function|restore_processor_context
r_static
r_inline
r_void
id|restore_processor_context
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * first restore %ds, so we can access our data properly&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;.align 4&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movw %0, %%ds&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
(paren
id|u16
)paren
id|__KERNEL_DS
)paren
)paren
suffix:semicolon
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
multiline_comment|/*&n;&t; * the other general registers&n;&t; *&n;&t; * note that even though gcc has constructs to specify memory &n;&t; * input into certain registers, it will try to be too smart&n;&t; * and save them at the beginning of the function.  This is esp.&n;&t; * bad since we don&squot;t have a stack set up when we enter, and we &n;&t; * want to preserve the values on exit. So, we set them manually.&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;movl %0, %%esp&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|saved_context.esp
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %0, %%ebp&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|saved_context.ebp
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %0, %%eax&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|saved_context.eax
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %0, %%ebx&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|saved_context.ebx
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %0, %%ecx&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|saved_context.ecx
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %0, %%edx&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|saved_context.edx
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %0, %%esi&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|saved_context.esi
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %0, %%edi&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|saved_context.edi
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * now restore the descriptor tables to their proper values&n;&t; * ltr is done i fix_processor_context().&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;lgdt (%0)&quot;
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
l_string|&quot;lidt (%0)&quot;
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
l_string|&quot;lldt (%0)&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|saved_context.ldt
)paren
)paren
suffix:semicolon
id|fix_processor_context
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * the flags&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;pushl %0 ; popfl&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|saved_context.eflags
)paren
)paren
suffix:semicolon
id|do_fpu_end
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ACPI_SLEEP
DECL|function|do_suspend_lowlevel
r_void
id|do_suspend_lowlevel
c_func
(paren
r_int
id|resume
)paren
(brace
multiline_comment|/*&n; * FIXME: This function should really be written in assembly. Actually&n; * requirement is that it does not touch stack, because %esp will be&n; * wrong during resume before restore_processor_context(). Check&n; * assembly if you modify this.&n; */
r_if
c_cond
(paren
op_logical_neg
id|resume
)paren
(brace
id|save_processor_context
c_func
(paren
)paren
suffix:semicolon
id|acpi_save_register_state
c_func
(paren
(paren
r_int
r_int
)paren
op_logical_and
id|acpi_sleep_done
)paren
suffix:semicolon
id|acpi_enter_sleep_state
c_func
(paren
l_int|3
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|acpi_sleep_done
suffix:colon
id|acpi_restore_register_state
c_func
(paren
)paren
suffix:semicolon
id|restore_processor_context
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|fix_processor_context
r_void
id|fix_processor_context
c_func
(paren
r_void
)paren
(brace
r_int
id|nr
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
op_amp
id|init_tss
(braket
id|nr
)braket
suffix:semicolon
id|set_tss_desc
c_func
(paren
id|nr
comma
id|t
)paren
suffix:semicolon
multiline_comment|/* This just modifies memory; should not be neccessary. But... This is neccessary, because 386 hardware has concept of busy tsc or some similar stupidity. */
id|gdt_table
(braket
id|__TSS
c_func
(paren
id|nr
)paren
)braket
dot
id|b
op_and_assign
l_int|0xfffffdff
suffix:semicolon
id|load_TR
c_func
(paren
id|nr
)paren
suffix:semicolon
multiline_comment|/* This does ltr */
id|load_LDT
c_func
(paren
op_amp
id|current-&gt;mm-&gt;context
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
multiline_comment|/* Local variables for do_magic */
DECL|variable|__nosavedata
r_static
r_int
id|loop
id|__nosavedata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__nosavedata
r_static
r_int
id|loop2
id|__nosavedata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * (KG): Since we affect stack here, we make this function as flat and easy&n; * as possible in order to not provoke gcc to use local variables on the stack.&n; * Note that on resume, all (expect nosave) variables will have the state from&n; * the time of writing (suspend_save_image) and the registers (including the&n; * stack pointer, but excluding the instruction pointer) will be loaded with &n; * the values saved at save_processor_context() time.&n; */
DECL|function|do_magic
r_void
id|do_magic
c_func
(paren
r_int
id|resume
)paren
(brace
multiline_comment|/* DANGER WILL ROBINSON!&n;&t; *&n;&t; * If this function is too difficult for gcc to optimize, it will crash and burn!&n;&t; * see above.&n;&t; *&n;&t; * DO NOT TOUCH.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|resume
)paren
(brace
id|do_magic_suspend_1
c_func
(paren
)paren
suffix:semicolon
id|save_processor_context
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* We need to capture registers and memory at &quot;same time&quot; */
id|do_magic_suspend_2
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* If everything goes okay, this function does not return */
r_return
suffix:semicolon
)brace
multiline_comment|/* We want to run from swapper_pg_dir, since swapper_pg_dir is stored in constant&n;&t; * place in memory &n;&t; */
id|__asm__
c_func
(paren
l_string|&quot;movl %%ecx,%%cr3&bslash;n&quot;
op_scope_resolution
l_string|&quot;c&quot;
(paren
id|__pa
c_func
(paren
id|swapper_pg_dir
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Final function for resuming: after copying the pages to their original&n; * position, it restores the register state.&n; *&n; * What about page tables? Writing data pages may toggle&n; * accessed/dirty bits in our page tables. That should be no problems&n; * with 4MB page tables. That&squot;s why we require have_pse.  &n; *&n; * This loops destroys stack from under itself, so it better should&n; * not use any stack space, itself. When this function is entered at&n; * resume time, we move stack to _old_ place.  This is means that this&n; * function must use no stack and no local variables in registers,&n; * until calling restore_processor_context();&n; *&n; * Critical section here: noone should touch saved memory after&n; * do_magic_resume_1; copying works, because nr_copy_pages,&n; * pagedir_nosave, loop and loop2 are nosavedata.&n; */
id|do_magic_resume_1
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
id|nr_copy_pages
suffix:semicolon
id|loop
op_increment
)paren
(brace
multiline_comment|/* You may not call something (like copy_page) here: see above */
r_for
c_loop
(paren
id|loop2
op_assign
l_int|0
suffix:semicolon
id|loop2
OL
id|PAGE_SIZE
suffix:semicolon
id|loop2
op_increment
)paren
(brace
op_star
(paren
(paren
(paren
r_char
op_star
)paren
(paren
(paren
id|pagedir_nosave
op_plus
id|loop
)paren
op_member_access_from_pointer
id|orig_address
)paren
)paren
op_plus
id|loop2
)paren
op_assign
op_star
(paren
(paren
(paren
r_char
op_star
)paren
(paren
(paren
id|pagedir_nosave
op_plus
id|loop
)paren
op_member_access_from_pointer
id|address
)paren
)paren
op_plus
id|loop2
)paren
suffix:semicolon
id|__flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|restore_processor_context
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Ahah, we now run with our old stack, and with registers copied from&n;   suspend time */
id|do_magic_resume_2
c_func
(paren
)paren
suffix:semicolon
)brace
eof
