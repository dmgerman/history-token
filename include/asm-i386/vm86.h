macro_line|#ifndef _LINUX_VM86_H
DECL|macro|_LINUX_VM86_H
mdefine_line|#define _LINUX_VM86_H
multiline_comment|/*&n; * I&squot;m guessing at the VIF/VIP flag usage, but hope that this is how&n; * the Pentium uses them. Linux will return from vm86 mode when both&n; * VIF and VIP is set.&n; *&n; * On a Pentium, we could probably optimize the virtual flags directly&n; * in the eflags register instead of doing it &quot;by hand&quot; in vflags...&n; *&n; * Linus&n; */
DECL|macro|TF_MASK
mdefine_line|#define TF_MASK&t;&t;0x00000100
DECL|macro|IF_MASK
mdefine_line|#define IF_MASK&t;&t;0x00000200
DECL|macro|IOPL_MASK
mdefine_line|#define IOPL_MASK&t;0x00003000
DECL|macro|NT_MASK
mdefine_line|#define NT_MASK&t;&t;0x00004000
DECL|macro|VM_MASK
mdefine_line|#define VM_MASK&t;&t;0x00020000
DECL|macro|AC_MASK
mdefine_line|#define AC_MASK&t;&t;0x00040000
DECL|macro|VIF_MASK
mdefine_line|#define VIF_MASK&t;0x00080000&t;/* virtual interrupt flag */
DECL|macro|VIP_MASK
mdefine_line|#define VIP_MASK&t;0x00100000&t;/* virtual interrupt pending */
DECL|macro|ID_MASK
mdefine_line|#define ID_MASK&t;&t;0x00200000
DECL|macro|BIOSSEG
mdefine_line|#define BIOSSEG&t;&t;0x0f000
DECL|macro|CPU_086
mdefine_line|#define CPU_086&t;&t;0
DECL|macro|CPU_186
mdefine_line|#define CPU_186&t;&t;1
DECL|macro|CPU_286
mdefine_line|#define CPU_286&t;&t;2
DECL|macro|CPU_386
mdefine_line|#define CPU_386&t;&t;3
DECL|macro|CPU_486
mdefine_line|#define CPU_486&t;&t;4
DECL|macro|CPU_586
mdefine_line|#define CPU_586&t;&t;5
multiline_comment|/*&n; * Return values for the &squot;vm86()&squot; system call&n; */
DECL|macro|VM86_TYPE
mdefine_line|#define VM86_TYPE(retval)&t;((retval) &amp; 0xff)
DECL|macro|VM86_ARG
mdefine_line|#define VM86_ARG(retval)&t;((retval) &gt;&gt; 8)
DECL|macro|VM86_SIGNAL
mdefine_line|#define VM86_SIGNAL&t;0&t;/* return due to signal */
DECL|macro|VM86_UNKNOWN
mdefine_line|#define VM86_UNKNOWN&t;1&t;/* unhandled GP fault - IO-instruction or similar */
DECL|macro|VM86_INTx
mdefine_line|#define VM86_INTx&t;2&t;/* int3/int x instruction (ARG = x) */
DECL|macro|VM86_STI
mdefine_line|#define VM86_STI&t;3&t;/* sti/popf/iret instruction enabled virtual interrupts */
multiline_comment|/*&n; * Additional return values when invoking new vm86()&n; */
DECL|macro|VM86_PICRETURN
mdefine_line|#define VM86_PICRETURN&t;4&t;/* return due to pending PIC request */
DECL|macro|VM86_TRAP
mdefine_line|#define VM86_TRAP&t;6&t;/* return due to DOS-debugger request */
multiline_comment|/*&n; * function codes when invoking new vm86()&n; */
DECL|macro|VM86_PLUS_INSTALL_CHECK
mdefine_line|#define VM86_PLUS_INSTALL_CHECK&t;0
DECL|macro|VM86_ENTER
mdefine_line|#define VM86_ENTER&t;&t;1
DECL|macro|VM86_ENTER_NO_BYPASS
mdefine_line|#define VM86_ENTER_NO_BYPASS&t;2
DECL|macro|VM86_REQUEST_IRQ
mdefine_line|#define&t;VM86_REQUEST_IRQ&t;3
DECL|macro|VM86_FREE_IRQ
mdefine_line|#define VM86_FREE_IRQ&t;&t;4
DECL|macro|VM86_GET_IRQ_BITS
mdefine_line|#define VM86_GET_IRQ_BITS&t;5
DECL|macro|VM86_GET_AND_RESET_IRQ
mdefine_line|#define VM86_GET_AND_RESET_IRQ&t;6
multiline_comment|/*&n; * This is the stack-layout seen by the user space program when we have&n; * done a translation of &quot;SAVE_ALL&quot; from vm86 mode. The real kernel layout&n; * is &squot;kernel_vm86_regs&squot; (see below).&n; */
DECL|struct|vm86_regs
r_struct
id|vm86_regs
(brace
multiline_comment|/*&n; * normal regs, with special meaning for the segment descriptors..&n; */
DECL|member|ebx
r_int
id|ebx
suffix:semicolon
DECL|member|ecx
r_int
id|ecx
suffix:semicolon
DECL|member|edx
r_int
id|edx
suffix:semicolon
DECL|member|esi
r_int
id|esi
suffix:semicolon
DECL|member|edi
r_int
id|edi
suffix:semicolon
DECL|member|ebp
r_int
id|ebp
suffix:semicolon
DECL|member|eax
r_int
id|eax
suffix:semicolon
DECL|member|__null_ds
r_int
id|__null_ds
suffix:semicolon
DECL|member|__null_es
r_int
id|__null_es
suffix:semicolon
DECL|member|__null_fs
r_int
id|__null_fs
suffix:semicolon
DECL|member|__null_gs
r_int
id|__null_gs
suffix:semicolon
DECL|member|orig_eax
r_int
id|orig_eax
suffix:semicolon
DECL|member|eip
r_int
id|eip
suffix:semicolon
DECL|member|cs
DECL|member|__csh
r_int
r_int
id|cs
comma
id|__csh
suffix:semicolon
DECL|member|eflags
r_int
id|eflags
suffix:semicolon
DECL|member|esp
r_int
id|esp
suffix:semicolon
DECL|member|ss
DECL|member|__ssh
r_int
r_int
id|ss
comma
id|__ssh
suffix:semicolon
multiline_comment|/*&n; * these are specific to v86 mode:&n; */
DECL|member|es
DECL|member|__esh
r_int
r_int
id|es
comma
id|__esh
suffix:semicolon
DECL|member|ds
DECL|member|__dsh
r_int
r_int
id|ds
comma
id|__dsh
suffix:semicolon
DECL|member|fs
DECL|member|__fsh
r_int
r_int
id|fs
comma
id|__fsh
suffix:semicolon
DECL|member|gs
DECL|member|__gsh
r_int
r_int
id|gs
comma
id|__gsh
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|revectored_struct
r_struct
id|revectored_struct
(brace
DECL|member|__map
r_int
r_int
id|__map
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 256 bits */
)brace
suffix:semicolon
DECL|struct|vm86_struct
r_struct
id|vm86_struct
(brace
DECL|member|regs
r_struct
id|vm86_regs
id|regs
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|screen_bitmap
r_int
r_int
id|screen_bitmap
suffix:semicolon
DECL|member|cpu_type
r_int
r_int
id|cpu_type
suffix:semicolon
DECL|member|int_revectored
r_struct
id|revectored_struct
id|int_revectored
suffix:semicolon
DECL|member|int21_revectored
r_struct
id|revectored_struct
id|int21_revectored
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * flags masks&n; */
DECL|macro|VM86_SCREEN_BITMAP
mdefine_line|#define VM86_SCREEN_BITMAP&t;0x0001
DECL|struct|vm86plus_info_struct
r_struct
id|vm86plus_info_struct
(brace
DECL|member|force_return_for_pic
r_int
r_int
id|force_return_for_pic
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vm86dbg_active
r_int
r_int
id|vm86dbg_active
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* for debugger */
DECL|member|vm86dbg_TFpendig
r_int
r_int
id|vm86dbg_TFpendig
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* for debugger */
DECL|member|unused
r_int
r_int
id|unused
suffix:colon
l_int|28
suffix:semicolon
DECL|member|is_vm86pus
r_int
r_int
id|is_vm86pus
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* for vm86 internal use */
DECL|member|vm86dbg_intxxtab
r_int
r_char
id|vm86dbg_intxxtab
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* for debugger */
)brace
suffix:semicolon
DECL|struct|vm86plus_struct
r_struct
id|vm86plus_struct
(brace
DECL|member|regs
r_struct
id|vm86_regs
id|regs
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|screen_bitmap
r_int
r_int
id|screen_bitmap
suffix:semicolon
DECL|member|cpu_type
r_int
r_int
id|cpu_type
suffix:semicolon
DECL|member|int_revectored
r_struct
id|revectored_struct
id|int_revectored
suffix:semicolon
DECL|member|int21_revectored
r_struct
id|revectored_struct
id|int21_revectored
suffix:semicolon
DECL|member|vm86plus
r_struct
id|vm86plus_info_struct
id|vm86plus
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * This is the (kernel) stack-layout when we have done a &quot;SAVE_ALL&quot; from vm86&n; * mode - the main change is that the old segment descriptors aren&squot;t&n; * useful any more and are forced to be zero by the kernel (and the&n; * hardware when a trap occurs), and the real segment descriptors are&n; * at the end of the structure. Look at ptrace.h to see the &quot;normal&quot;&n; * setup. For user space layout see &squot;struct vm86_regs&squot; above.&n; */
DECL|struct|kernel_vm86_regs
r_struct
id|kernel_vm86_regs
(brace
multiline_comment|/*&n; * normal regs, with special meaning for the segment descriptors..&n; */
DECL|member|ebx
r_int
id|ebx
suffix:semicolon
DECL|member|ecx
r_int
id|ecx
suffix:semicolon
DECL|member|edx
r_int
id|edx
suffix:semicolon
DECL|member|esi
r_int
id|esi
suffix:semicolon
DECL|member|edi
r_int
id|edi
suffix:semicolon
DECL|member|ebp
r_int
id|ebp
suffix:semicolon
DECL|member|eax
r_int
id|eax
suffix:semicolon
DECL|member|__null_ds
r_int
id|__null_ds
suffix:semicolon
DECL|member|__null_es
r_int
id|__null_es
suffix:semicolon
DECL|member|orig_eax
r_int
id|orig_eax
suffix:semicolon
DECL|member|eip
r_int
id|eip
suffix:semicolon
DECL|member|cs
DECL|member|__csh
r_int
r_int
id|cs
comma
id|__csh
suffix:semicolon
DECL|member|eflags
r_int
id|eflags
suffix:semicolon
DECL|member|esp
r_int
id|esp
suffix:semicolon
DECL|member|ss
DECL|member|__ssh
r_int
r_int
id|ss
comma
id|__ssh
suffix:semicolon
multiline_comment|/*&n; * these are specific to v86 mode:&n; */
DECL|member|es
DECL|member|__esh
r_int
r_int
id|es
comma
id|__esh
suffix:semicolon
DECL|member|ds
DECL|member|__dsh
r_int
r_int
id|ds
comma
id|__dsh
suffix:semicolon
DECL|member|fs
DECL|member|__fsh
r_int
r_int
id|fs
comma
id|__fsh
suffix:semicolon
DECL|member|gs
DECL|member|__gsh
r_int
r_int
id|gs
comma
id|__gsh
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kernel_vm86_struct
r_struct
id|kernel_vm86_struct
(brace
DECL|member|regs
r_struct
id|kernel_vm86_regs
id|regs
suffix:semicolon
multiline_comment|/*&n; * the below part remains on the kernel stack while we are in VM86 mode.&n; * &squot;tss.esp0&squot; then contains the address of VM86_TSS_ESP0 below, and when we&n; * get forced back from VM86, the CPU and &quot;SAVE_ALL&quot; will restore the above&n; * &squot;struct kernel_vm86_regs&squot; with the then actual values.&n; * Therefore, pt_regs in fact points to a complete &squot;kernel_vm86_struct&squot;&n; * in kernelspace, hence we need not reget the data from userspace.&n; */
DECL|macro|VM86_TSS_ESP0
mdefine_line|#define VM86_TSS_ESP0 flags
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|screen_bitmap
r_int
r_int
id|screen_bitmap
suffix:semicolon
DECL|member|cpu_type
r_int
r_int
id|cpu_type
suffix:semicolon
DECL|member|int_revectored
r_struct
id|revectored_struct
id|int_revectored
suffix:semicolon
DECL|member|int21_revectored
r_struct
id|revectored_struct
id|int21_revectored
suffix:semicolon
DECL|member|vm86plus
r_struct
id|vm86plus_info_struct
id|vm86plus
suffix:semicolon
DECL|member|regs32
r_struct
id|pt_regs
op_star
id|regs32
suffix:semicolon
multiline_comment|/* here we save the pointer to the old regs */
multiline_comment|/*&n; * The below is not part of the structure, but the stack layout continues&n; * this way. In front of &squot;return-eip&squot; may be some data, depending on&n; * compilation, so we don&squot;t rely on this and save the pointer to &squot;oldregs&squot;&n; * in &squot;regs32&squot; above.&n; * However, with GCC-2.7.2 and the current CFLAGS you see exactly this:&n;&n;&t;long return-eip;        from call to vm86()&n;&t;struct pt_regs oldregs;  user space registers as saved by syscall&n; */
)brace
suffix:semicolon
r_void
id|handle_vm86_fault
c_func
(paren
r_struct
id|kernel_vm86_regs
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|handle_vm86_trap
c_func
(paren
r_struct
id|kernel_vm86_regs
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
