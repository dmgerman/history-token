multiline_comment|/*&n; * arch/alpha/boot/bootp.c&n; *&n; * Copyright (C) 1997 Jay Estabrook&n; *&n; * This file is used for creating a bootp file for the Linux/AXP kernel&n; *&n; * based significantly on the arch/alpha/boot/main.c of Linus Torvalds&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/console.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &quot;ksize.h&quot;
r_extern
r_int
r_int
id|switch_to_osf_pal
c_func
(paren
r_int
r_int
id|nr
comma
r_struct
id|pcb_struct
op_star
id|pcb_va
comma
r_struct
id|pcb_struct
op_star
id|pcb_pa
comma
r_int
r_int
op_star
id|vptb
)paren
suffix:semicolon
r_extern
r_void
id|move_stack
c_func
(paren
r_int
r_int
id|new_stack
)paren
suffix:semicolon
DECL|variable|hwrpb
r_struct
id|hwrpb_struct
op_star
id|hwrpb
op_assign
id|INIT_HWRPB
suffix:semicolon
DECL|variable|pcb_va
r_static
r_struct
id|pcb_struct
id|pcb_va
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/*&n; * Find a physical address of a virtual object..&n; *&n; * This is easy using the virtual page table address.&n; */
r_static
r_inline
r_void
op_star
DECL|function|find_pa
id|find_pa
c_func
(paren
r_int
r_int
op_star
id|vptb
comma
r_void
op_star
id|ptr
)paren
(brace
r_int
r_int
id|address
op_assign
(paren
r_int
r_int
)paren
id|ptr
suffix:semicolon
r_int
r_int
id|result
suffix:semicolon
id|result
op_assign
id|vptb
(braket
id|address
op_rshift
l_int|13
)braket
suffix:semicolon
id|result
op_rshift_assign
l_int|32
suffix:semicolon
id|result
op_lshift_assign
l_int|13
suffix:semicolon
id|result
op_or_assign
id|address
op_amp
l_int|0x1fff
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * This function moves into OSF/1 pal-code, and has a temporary&n; * PCB for that. The kernel proper should replace this PCB with&n; * the real one as soon as possible.&n; *&n; * The page table muckery in here depends on the fact that the boot&n; * code has the L1 page table identity-map itself in the second PTE&n; * in the L1 page table. Thus the L1-page is virtually addressable&n; * itself (through three levels) at virtual address 0x200802000.&n; */
DECL|macro|VPTB
mdefine_line|#define VPTB&t;((unsigned long *) 0x200000000)
DECL|macro|L1
mdefine_line|#define L1&t;((unsigned long *) 0x200802000)
r_void
DECL|function|pal_init
id|pal_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
comma
id|rev
suffix:semicolon
r_struct
id|percpu_struct
op_star
id|percpu
suffix:semicolon
r_struct
id|pcb_struct
op_star
id|pcb_pa
suffix:semicolon
multiline_comment|/* Create the dummy PCB.  */
id|pcb_va-&gt;ksp
op_assign
l_int|0
suffix:semicolon
id|pcb_va-&gt;usp
op_assign
l_int|0
suffix:semicolon
id|pcb_va-&gt;ptbr
op_assign
id|L1
(braket
l_int|1
)braket
op_rshift
l_int|32
suffix:semicolon
id|pcb_va-&gt;asn
op_assign
l_int|0
suffix:semicolon
id|pcb_va-&gt;pcc
op_assign
l_int|0
suffix:semicolon
id|pcb_va-&gt;unique
op_assign
l_int|0
suffix:semicolon
id|pcb_va-&gt;flags
op_assign
l_int|1
suffix:semicolon
id|pcb_va-&gt;res1
op_assign
l_int|0
suffix:semicolon
id|pcb_va-&gt;res2
op_assign
l_int|0
suffix:semicolon
id|pcb_pa
op_assign
id|find_pa
c_func
(paren
id|VPTB
comma
id|pcb_va
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * a0 = 2 (OSF)&n;&t; * a1 = return address, but we give the asm the vaddr of the PCB&n;&t; * a2 = physical addr of PCB&n;&t; * a3 = new virtual page table pointer&n;&t; * a4 = KSP (but the asm sets it)&n;&t; */
id|srm_printk
c_func
(paren
l_string|&quot;Switching to OSF PAL-code .. &quot;
)paren
suffix:semicolon
id|i
op_assign
id|switch_to_osf_pal
c_func
(paren
l_int|2
comma
id|pcb_va
comma
id|pcb_pa
comma
id|VPTB
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
(brace
id|srm_printk
c_func
(paren
l_string|&quot;failed, code %ld&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|__halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|percpu
op_assign
(paren
r_struct
id|percpu_struct
op_star
)paren
(paren
id|INIT_HWRPB-&gt;processor_offset
op_plus
(paren
r_int
r_int
)paren
id|INIT_HWRPB
)paren
suffix:semicolon
id|rev
op_assign
id|percpu-&gt;pal_revision
op_assign
id|percpu-&gt;palcode_avail
(braket
l_int|2
)braket
suffix:semicolon
id|srm_printk
c_func
(paren
l_string|&quot;Ok (rev %lx)&bslash;n&quot;
comma
id|rev
)paren
suffix:semicolon
id|tbia
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* do it directly in case we are SMP */
)brace
r_static
r_inline
r_void
DECL|function|load
id|load
c_func
(paren
r_int
r_int
id|dst
comma
r_int
r_int
id|src
comma
r_int
r_int
id|count
)paren
(brace
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|dst
comma
(paren
r_void
op_star
)paren
id|src
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Start the kernel.&n; */
r_static
r_inline
r_void
DECL|function|runkernel
id|runkernel
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;bis %0,%0,$27&bslash;n&bslash;t&quot;
l_string|&quot;jmp ($27)&quot;
suffix:colon
multiline_comment|/* no outputs: it doesn&squot;t even return */
suffix:colon
l_string|&quot;r&quot;
(paren
id|START_ADDR
)paren
)paren
suffix:semicolon
)brace
r_extern
r_char
id|_end
suffix:semicolon
DECL|macro|KERNEL_ORIGIN
mdefine_line|#define KERNEL_ORIGIN &bslash;&n;&t;((((unsigned long)&amp;_end) + 511) &amp; ~511)
r_void
DECL|function|start_kernel
id|start_kernel
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Note that this crufty stuff with static and envval&n;&t; * and envbuf is because:&n;&t; *&n;&t; * 1. Frequently, the stack is short, and we don&squot;t want to overrun;&n;&t; * 2. Frequently the stack is where we are going to copy the kernel to;&n;&t; * 3. A certain SRM console required the GET_ENV output to stack.&n;&t; *    ??? A comment in the aboot sources indicates that the GET_ENV&n;&t; *    destination must be quadword aligned.  Might this explain the&n;&t; *    behaviour, rather than requiring output to the stack, which&n;&t; *    seems rather far-fetched.&n;&t; */
r_static
r_int
id|nbytes
suffix:semicolon
r_static
r_char
id|envval
(braket
l_int|256
)braket
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
r_static
r_int
r_int
id|initrd_start
suffix:semicolon
id|srm_printk
c_func
(paren
l_string|&quot;Linux/AXP bootp loader for Linux &quot;
id|UTS_RELEASE
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|INIT_HWRPB-&gt;pagesize
op_ne
l_int|8192
)paren
(brace
id|srm_printk
c_func
(paren
l_string|&quot;Expected 8kB pages, got %ldkB&bslash;n&quot;
comma
id|INIT_HWRPB-&gt;pagesize
op_rshift
l_int|10
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|INIT_HWRPB-&gt;vptb
op_ne
(paren
r_int
r_int
)paren
id|VPTB
)paren
(brace
id|srm_printk
c_func
(paren
l_string|&quot;Expected vptb at %p, got %p&bslash;n&quot;
comma
id|VPTB
comma
(paren
r_void
op_star
)paren
id|INIT_HWRPB-&gt;vptb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pal_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* The initrd must be page-aligned.  See below for the &n;&t;   cause of the magic number 5.  */
id|initrd_start
op_assign
(paren
(paren
id|START_ADDR
op_plus
l_int|5
op_star
id|KERNEL_SIZE
op_plus
id|PAGE_SIZE
)paren
op_or
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_plus
l_int|1
suffix:semicolon
macro_line|#ifdef INITRD_IMAGE_SIZE
id|srm_printk
c_func
(paren
l_string|&quot;Initrd positioned at %#lx&bslash;n&quot;
comma
id|initrd_start
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Move the stack to a safe place to ensure it won&squot;t be&n;&t; * overwritten by kernel image.&n;&t; */
id|move_stack
c_func
(paren
id|initrd_start
op_minus
id|PAGE_SIZE
)paren
suffix:semicolon
id|nbytes
op_assign
id|callback_getenv
c_func
(paren
id|ENV_BOOTED_OSFLAGS
comma
id|envval
comma
r_sizeof
(paren
id|envval
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
OL
l_int|0
op_logical_or
id|nbytes
op_ge
r_sizeof
(paren
id|envval
)paren
)paren
(brace
id|nbytes
op_assign
l_int|0
suffix:semicolon
)brace
id|envval
(braket
id|nbytes
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|srm_printk
c_func
(paren
l_string|&quot;Loading the kernel...&squot;%s&squot;&bslash;n&quot;
comma
id|envval
)paren
suffix:semicolon
multiline_comment|/* NOTE: *no* callbacks or printouts from here on out!!! */
multiline_comment|/* This is a hack, as some consoles seem to get virtual 20000000 (ie&n;&t; * where the SRM console puts the kernel bootp image) memory&n;&t; * overlapping physical memory where the kernel wants to be put,&n;&t; * which causes real problems when attempting to copy the former to&n;&t; * the latter... :-(&n;&t; *&n;&t; * So, we first move the kernel virtual-to-physical way above where&n;&t; * we physically want the kernel to end up, then copy it from there&n;&t; * to its final resting place... ;-}&n;&t; *&n;&t; * Sigh...  */
macro_line|#ifdef INITRD_IMAGE_SIZE
id|load
c_func
(paren
id|initrd_start
comma
id|KERNEL_ORIGIN
op_plus
id|KERNEL_SIZE
comma
id|INITRD_IMAGE_SIZE
)paren
suffix:semicolon
macro_line|#endif
id|load
c_func
(paren
id|START_ADDR
op_plus
(paren
l_int|4
op_star
id|KERNEL_SIZE
)paren
comma
id|KERNEL_ORIGIN
comma
id|KERNEL_SIZE
)paren
suffix:semicolon
id|load
c_func
(paren
id|START_ADDR
comma
id|START_ADDR
op_plus
(paren
l_int|4
op_star
id|KERNEL_SIZE
)paren
comma
id|KERNEL_SIZE
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
id|ZERO_PGE
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|strcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|ZERO_PGE
comma
id|envval
)paren
suffix:semicolon
macro_line|#ifdef INITRD_IMAGE_SIZE
(paren
(paren
r_int
op_star
)paren
(paren
id|ZERO_PGE
op_plus
l_int|256
)paren
)paren
(braket
l_int|0
)braket
op_assign
id|initrd_start
suffix:semicolon
(paren
(paren
r_int
op_star
)paren
(paren
id|ZERO_PGE
op_plus
l_int|256
)paren
)paren
(braket
l_int|1
)braket
op_assign
id|INITRD_IMAGE_SIZE
suffix:semicolon
macro_line|#endif
id|runkernel
c_func
(paren
)paren
suffix:semicolon
)brace
eof
