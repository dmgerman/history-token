multiline_comment|/*&n; * Copyright 2001-2002 Pavel Machek &lt;pavel@suse.cz&gt;&n; * Based on code&n; * Copyright 2001 Patrick Mochel &lt;mochel@osdl.org&gt;&n; */
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
r_static
r_inline
r_void
DECL|function|arch_prepare_suspend
id|arch_prepare_suspend
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/* Image of the saved processor state. If you touch this, fix acpi_wakeup.S. */
DECL|struct|saved_context
r_struct
id|saved_context
(brace
DECL|member|ds
DECL|member|es
DECL|member|fs
DECL|member|gs
DECL|member|ss
id|u16
id|ds
comma
id|es
comma
id|fs
comma
id|gs
comma
id|ss
suffix:semicolon
DECL|member|gs_base
DECL|member|gs_kernel_base
DECL|member|fs_base
r_int
r_int
id|gs_base
comma
id|gs_kernel_base
comma
id|fs_base
suffix:semicolon
DECL|member|cr0
DECL|member|cr2
DECL|member|cr3
DECL|member|cr4
r_int
r_int
id|cr0
comma
id|cr2
comma
id|cr3
comma
id|cr4
suffix:semicolon
DECL|member|gdt_pad
id|u16
id|gdt_pad
suffix:semicolon
DECL|member|gdt_limit
id|u16
id|gdt_limit
suffix:semicolon
DECL|member|gdt_base
r_int
r_int
id|gdt_base
suffix:semicolon
DECL|member|idt_pad
id|u16
id|idt_pad
suffix:semicolon
DECL|member|idt_limit
id|u16
id|idt_limit
suffix:semicolon
DECL|member|idt_base
r_int
r_int
id|idt_base
suffix:semicolon
DECL|member|ldt
id|u16
id|ldt
suffix:semicolon
DECL|member|tss
id|u16
id|tss
suffix:semicolon
DECL|member|tr
r_int
r_int
id|tr
suffix:semicolon
DECL|member|safety
r_int
r_int
id|safety
suffix:semicolon
DECL|member|return_address
r_int
r_int
id|return_address
suffix:semicolon
DECL|member|eflags
r_int
r_int
id|eflags
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* We&squot;ll access these from assembly, so we&squot;d better have them outside struct */
r_extern
r_int
r_int
id|saved_context_eax
comma
id|saved_context_ebx
comma
id|saved_context_ecx
comma
id|saved_context_edx
suffix:semicolon
r_extern
r_int
r_int
id|saved_context_esp
comma
id|saved_context_ebp
comma
id|saved_context_esi
comma
id|saved_context_edi
suffix:semicolon
r_extern
r_int
r_int
id|saved_context_r08
comma
id|saved_context_r09
comma
id|saved_context_r10
comma
id|saved_context_r11
suffix:semicolon
r_extern
r_int
r_int
id|saved_context_r12
comma
id|saved_context_r13
comma
id|saved_context_r14
comma
id|saved_context_r15
suffix:semicolon
r_extern
r_int
r_int
id|saved_context_eflags
suffix:semicolon
DECL|macro|loaddebug
mdefine_line|#define loaddebug(thread,register) &bslash;&n;               __asm__(&quot;movq %0,%%db&quot; #register  &bslash;&n;                       : /* no output */ &bslash;&n;                       :&quot;r&quot; ((thread)-&gt;debugreg##register))
r_extern
r_void
id|fix_processor_context
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ACPI_SLEEP
r_extern
r_int
r_int
id|saved_eip
suffix:semicolon
r_extern
r_int
r_int
id|saved_esp
suffix:semicolon
r_extern
r_int
r_int
id|saved_ebp
suffix:semicolon
r_extern
r_int
r_int
id|saved_ebx
suffix:semicolon
r_extern
r_int
r_int
id|saved_esi
suffix:semicolon
r_extern
r_int
r_int
id|saved_edi
suffix:semicolon
multiline_comment|/* routines for saving/restoring kernel state */
r_extern
r_int
id|acpi_save_state_mem
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|acpi_save_state_disk
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
