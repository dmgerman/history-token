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
r_if
c_cond
(paren
op_logical_neg
id|cpu_has_pse
)paren
id|panic
c_func
(paren
l_string|&quot;pse required&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* image of the saved processor state */
DECL|struct|saved_context
r_struct
id|saved_context
(brace
DECL|member|es
DECL|member|fs
DECL|member|gs
DECL|member|ss
id|u16
id|es
comma
id|fs
comma
id|gs
comma
id|ss
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
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|loaddebug
mdefine_line|#define loaddebug(thread,register) &bslash;&n;               __asm__(&quot;movl %0,%%db&quot; #register  &bslash;&n;                       : /* no output */ &bslash;&n;                       :&quot;r&quot; ((thread)-&gt;debugreg[register]))
r_extern
r_void
id|save_processor_state
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|restore_processor_state
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|do_magic
c_func
(paren
r_int
id|resume
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
DECL|function|acpi_save_register_state
r_static
r_inline
r_void
id|acpi_save_register_state
c_func
(paren
r_int
r_int
id|return_point
)paren
(brace
id|saved_eip
op_assign
id|return_point
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%esp,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_esp
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%ebp,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_ebp
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%ebx,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_ebx
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%edi,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_edi
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%esi,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_esi
)paren
)paren
suffix:semicolon
)brace
DECL|macro|acpi_restore_register_state
mdefine_line|#define acpi_restore_register_state()  do {} while (0)
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
