multiline_comment|/*&n; * arch/alpha/boot/bootpz.c&n; *&n; * Copyright (C) 1997 Jay Estabrook&n; *&n; * This file is used for creating a compressed BOOTP file for the&n; * Linux/AXP kernel&n; *&n; * based significantly on the arch/alpha/boot/main.c of Linus Torvalds&n; * and the decompression code from MILO.&n; */
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
macro_line|#include &quot;kzsize.h&quot;
multiline_comment|/* FIXME FIXME FIXME */
DECL|macro|MALLOC_AREA_SIZE
mdefine_line|#define MALLOC_AREA_SIZE 0x200000 /* 2MB for now */
multiline_comment|/* FIXME FIXME FIXME */
multiline_comment|/*&n;  WARNING NOTE&n;&n;  It is very possible that turning on additional messages may cause&n;  kernel image corruption due to stack usage to do the printing.&n;&n;*/
DECL|macro|DEBUG_CHECK_RANGE
macro_line|#undef DEBUG_CHECK_RANGE
DECL|macro|DEBUG_ADDRESSES
macro_line|#undef DEBUG_ADDRESSES
DECL|macro|DEBUG_LAST_STEPS
macro_line|#undef DEBUG_LAST_STEPS
DECL|macro|DEBUG_SP
mdefine_line|#define DEBUG_SP(x) &bslash;&n;    {register long sp asm(&quot;30&quot;); srm_printk(&quot;%s (sp=%lx)&bslash;n&quot;, x, sp);}
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
r_int
id|decompress_kernel
c_func
(paren
r_void
op_star
id|destination
comma
r_void
op_star
id|source
comma
r_int
id|ksize
comma
r_int
id|kzsize
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
DECL|macro|VPTB
mdefine_line|#define VPTB&t;((unsigned long *) 0x200000000)
r_static
r_inline
r_int
r_int
DECL|function|find_pa
id|find_pa
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_int
r_int
id|result
suffix:semicolon
id|result
op_assign
id|VPTB
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
id|result
suffix:semicolon
)brace
r_int
DECL|function|check_range
id|check_range
c_func
(paren
r_int
r_int
id|vstart
comma
r_int
r_int
id|vend
comma
r_int
r_int
id|kstart
comma
r_int
r_int
id|kend
)paren
(brace
r_int
r_int
id|vaddr
comma
id|kaddr
suffix:semicolon
macro_line|#ifdef DEBUG_CHECK_RANGE
id|srm_printk
c_func
(paren
l_string|&quot;check_range: V[0x%lx:0x%lx] K[0x%lx:0x%lx]&bslash;n&quot;
comma
id|vstart
comma
id|vend
comma
id|kstart
comma
id|kend
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* do some range checking for detecting an overlap... */
r_for
c_loop
(paren
id|vaddr
op_assign
id|vstart
suffix:semicolon
id|vaddr
op_le
id|vend
suffix:semicolon
id|vaddr
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|kaddr
op_assign
(paren
id|find_pa
c_func
(paren
id|vaddr
)paren
op_or
id|PAGE_OFFSET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kaddr
op_ge
id|kstart
op_logical_and
id|kaddr
op_le
id|kend
)paren
(brace
macro_line|#ifdef DEBUG_CHECK_RANGE
id|srm_printk
c_func
(paren
l_string|&quot;OVERLAP: vaddr 0x%lx kaddr 0x%lx&quot;
l_string|&quot; [0x%lx:0x%lx]&bslash;n&quot;
comma
id|vaddr
comma
id|kaddr
comma
id|kstart
comma
id|kend
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This function moves into OSF/1 pal-code, and has a temporary&n; * PCB for that. The kernel proper should replace this PCB with&n; * the real one as soon as possible.&n; *&n; * The page table muckery in here depends on the fact that the boot&n; * code has the L1 page table identity-map itself in the second PTE&n; * in the L1 page table. Thus the L1-page is virtually addressable&n; * itself (through three levels) at virtual address 0x200802000.&n; */
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
(paren
r_struct
id|pcb_struct
op_star
)paren
id|find_pa
c_func
(paren
(paren
r_int
r_int
)paren
id|pcb_va
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * a0 = 2 (OSF)&n;&t; * a1 = return address, but we give the asm the vaddr of the PCB&n;&t; * a2 = physical addr of PCB&n;&t; * a3 = new virtual page table pointer&n;&t; * a4 = KSP (but the asm sets it)&n;&t; */
id|srm_printk
c_func
(paren
l_string|&quot;Switching to OSF PAL-code... &quot;
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
l_string|&quot;OK (rev %lx)&bslash;n&quot;
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
l_string|&quot;bis %1,%1,$30&bslash;n&bslash;t&quot;
l_string|&quot;bis %0,%0,$27&bslash;n&bslash;t&quot;
l_string|&quot;jmp ($27)&quot;
suffix:colon
multiline_comment|/* no outputs: it doesn&squot;t even return */
suffix:colon
l_string|&quot;r&quot;
(paren
id|START_ADDR
)paren
comma
l_string|&quot;r&quot;
(paren
id|PAGE_SIZE
op_plus
id|INIT_STACK
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Must record the SP (it is virtual) on entry, so we can make sure&n;   not to overwrite it during movement or decompression. */
DECL|variable|SP_on_entry
r_int
r_int
id|SP_on_entry
suffix:semicolon
multiline_comment|/* Calculate the kernel image address based on the end of the BOOTP&n;   bootstrapper (ie this program).&n;*/
r_extern
r_char
id|_end
suffix:semicolon
DECL|macro|KERNEL_ORIGIN
mdefine_line|#define KERNEL_ORIGIN &bslash;&n;&t;((((unsigned long)&amp;_end) + 511) &amp; ~511)
multiline_comment|/* Round address to next higher page boundary. */
DECL|macro|NEXT_PAGE
mdefine_line|#define NEXT_PAGE(a)&t;(((a) | (PAGE_SIZE - 1)) + 1)
macro_line|#ifdef INITRD_IMAGE_SIZE
DECL|macro|REAL_INITRD_SIZE
macro_line|# define REAL_INITRD_SIZE INITRD_IMAGE_SIZE
macro_line|#else
DECL|macro|REAL_INITRD_SIZE
macro_line|# define REAL_INITRD_SIZE 0
macro_line|#endif
multiline_comment|/* Defines from include/asm-alpha/system.h&n;&n;&t;BOOT_ADDR&t;Virtual address at which the consoles loads&n;&t;&t;&t;the BOOTP image.&n;&n;&t;KERNEL_START    KSEG address at which the kernel is built to run,&n;&t;&t;&t;which includes some initial data pages before the&n;&t;&t;&t;code.&n;&n;&t;START_ADDR&t;KSEG address of the entry point of kernel code.&n;&n;&t;ZERO_PGE&t;KSEG address of page full of zeroes, but &n;&t;&t;&t;upon entry to kerne cvan be expected&n;&t;&t;&t;to hold the parameter list and possible&n;&t;&t;&t;INTRD information.&n;&n;   These are used in the local defines below.&n;*/
multiline_comment|/* Virtual addresses for the BOOTP image. Note that this includes the&n;   bootstrapper code as well as the compressed kernel image, and&n;   possibly the INITRD image.&n;&n;   Oh, and do NOT forget the STACK, which appears to be placed virtually&n;   beyond the end of the loaded image.&n;*/
DECL|macro|V_BOOT_IMAGE_START
mdefine_line|#define V_BOOT_IMAGE_START&t;BOOT_ADDR
DECL|macro|V_BOOT_IMAGE_END
mdefine_line|#define V_BOOT_IMAGE_END&t;SP_on_entry
multiline_comment|/* Virtual addresses for just the bootstrapper part of the BOOTP image. */
DECL|macro|V_BOOTSTRAPPER_START
mdefine_line|#define V_BOOTSTRAPPER_START&t;BOOT_ADDR
DECL|macro|V_BOOTSTRAPPER_END
mdefine_line|#define V_BOOTSTRAPPER_END&t;KERNEL_ORIGIN
multiline_comment|/* Virtual addresses for just the data part of the BOOTP&n;   image. This may also include the INITRD image, but always&n;   includes the STACK.&n;*/
DECL|macro|V_DATA_START
mdefine_line|#define V_DATA_START&t;&t;KERNEL_ORIGIN
DECL|macro|V_INITRD_START
mdefine_line|#define V_INITRD_START&t;&t;(KERNEL_ORIGIN + KERNEL_Z_SIZE)
DECL|macro|V_INTRD_END
mdefine_line|#define V_INTRD_END&t;&t;(V_INITRD_START + REAL_INITRD_SIZE)
DECL|macro|V_DATA_END
mdefine_line|#define V_DATA_END&t; &t;V_BOOT_IMAGE_END
multiline_comment|/* KSEG addresses for the uncompressed kernel.&n;&n;   Note that the end address includes workspace for the decompression.&n;   Note also that the DATA_START address is ZERO_PGE, to which we write&n;   just before jumping to the kernel image at START_ADDR.&n; */
DECL|macro|K_KERNEL_DATA_START
mdefine_line|#define K_KERNEL_DATA_START&t;ZERO_PGE
DECL|macro|K_KERNEL_IMAGE_START
mdefine_line|#define K_KERNEL_IMAGE_START&t;START_ADDR
DECL|macro|K_KERNEL_IMAGE_END
mdefine_line|#define K_KERNEL_IMAGE_END&t;(START_ADDR + KERNEL_SIZE)
multiline_comment|/* Define to where we may have to decompress the kernel image, before&n;   we move it to the final position, in case of overlap. This will be&n;   above the final position of the kernel.&n;&n;   Regardless of overlap, we move the INITRD image to the end of this&n;   copy area, because there needs to be a buffer area after the kernel&n;   for &quot;bootmem&quot; anyway.&n;*/
DECL|macro|K_COPY_IMAGE_START
mdefine_line|#define K_COPY_IMAGE_START&t;NEXT_PAGE(K_KERNEL_IMAGE_END)
DECL|macro|K_INITRD_START
mdefine_line|#define K_INITRD_START&t;&t;NEXT_PAGE(K_COPY_IMAGE_START + KERNEL_SIZE)
DECL|macro|K_COPY_IMAGE_END
mdefine_line|#define K_COPY_IMAGE_END &bslash;&n;    (K_INITRD_START + REAL_INITRD_SIZE + MALLOC_AREA_SIZE)
DECL|macro|K_COPY_IMAGE_SIZE
mdefine_line|#define K_COPY_IMAGE_SIZE &bslash;&n;    NEXT_PAGE(K_COPY_IMAGE_END - K_COPY_IMAGE_START)
r_void
DECL|function|start_kernel
id|start_kernel
c_func
(paren
r_void
)paren
(brace
r_int
id|must_move
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Initialize these for the decompression-in-place situation,&n;&t;   which is the smallest amount of work and most likely to&n;&t;   occur when using the normal START_ADDR of the kernel&n;&t;   (currently set to 16MB, to clear all console code.&n;&t;*/
r_int
r_int
id|uncompressed_image_start
op_assign
id|K_KERNEL_IMAGE_START
suffix:semicolon
r_int
r_int
id|uncompressed_image_end
op_assign
id|K_KERNEL_IMAGE_END
suffix:semicolon
r_int
r_int
id|initrd_image_start
op_assign
id|K_INITRD_START
suffix:semicolon
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
r_register
r_int
r_int
id|asm_sp
id|asm
c_func
(paren
l_string|&quot;30&quot;
)paren
suffix:semicolon
id|SP_on_entry
op_assign
id|asm_sp
suffix:semicolon
id|srm_printk
c_func
(paren
l_string|&quot;Linux/Alpha BOOTPZ Loader for Linux &quot;
id|UTS_RELEASE
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Validity check the HWRPB. */
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
multiline_comment|/* PALcode (re)initialization. */
id|pal_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Get the parameter list from the console environment variable. */
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
macro_line|#ifdef DEBUG_ADDRESSES
id|srm_printk
c_func
(paren
l_string|&quot;START_ADDR 0x%lx&bslash;n&quot;
comma
id|START_ADDR
)paren
suffix:semicolon
id|srm_printk
c_func
(paren
l_string|&quot;KERNEL_ORIGIN 0x%lx&bslash;n&quot;
comma
id|KERNEL_ORIGIN
)paren
suffix:semicolon
id|srm_printk
c_func
(paren
l_string|&quot;KERNEL_SIZE 0x%x&bslash;n&quot;
comma
id|KERNEL_SIZE
)paren
suffix:semicolon
id|srm_printk
c_func
(paren
l_string|&quot;KERNEL_Z_SIZE 0x%x&bslash;n&quot;
comma
id|KERNEL_Z_SIZE
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Since all the SRM consoles load the BOOTP image at virtual&n;&t; * 0x20000000, we have to ensure that the physical memory&n;&t; * pages occupied by that image do NOT overlap the physical&n;&t; * address range where the kernel wants to be run.  This&n;&t; * causes real problems when attempting to cdecompress the&n;&t; * former into the latter... :-(&n;&t; *&n;&t; * So, we may have to decompress/move the kernel/INITRD image&n;&t; * virtual-to-physical someplace else first before moving&n;&t; * kernel /INITRD to their final resting places... ;-}&n;&t; *&n;&t; * Sigh...&n;&t; */
multiline_comment|/* First, check to see if the range of addresses occupied by&n;&t;   the bootstrapper part of the BOOTP image include any of the&n;&t;   physical pages into which the kernel will be placed for&n;&t;   execution.&n;&n;&t;   We only need check on the final kernel image range, since we&n;&t;   will put the INITRD someplace that we can be sure is not&n;&t;   in conflict.&n;&t; */
r_if
c_cond
(paren
id|check_range
c_func
(paren
id|V_BOOTSTRAPPER_START
comma
id|V_BOOTSTRAPPER_END
comma
id|K_KERNEL_DATA_START
comma
id|K_KERNEL_IMAGE_END
)paren
)paren
(brace
id|srm_printk
c_func
(paren
l_string|&quot;FATAL ERROR: overlap of bootstrapper code&bslash;n&quot;
)paren
suffix:semicolon
id|__halt
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Next, check to see if the range of addresses occupied by&n;&t;   the compressed kernel/INITRD/stack portion of the BOOTP&n;&t;   image include any of the physical pages into which the&n;&t;   decompressed kernel or the INITRD will be placed for&n;&t;   execution.&n;&t; */
r_if
c_cond
(paren
id|check_range
c_func
(paren
id|V_DATA_START
comma
id|V_DATA_END
comma
id|K_KERNEL_IMAGE_START
comma
id|K_COPY_IMAGE_END
)paren
)paren
(brace
macro_line|#ifdef DEBUG_ADDRESSES
id|srm_printk
c_func
(paren
l_string|&quot;OVERLAP: cannot decompress in place&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|uncompressed_image_start
op_assign
id|K_COPY_IMAGE_START
suffix:semicolon
id|uncompressed_image_end
op_assign
id|K_COPY_IMAGE_END
suffix:semicolon
id|must_move
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Finally, check to see if the range of addresses&n;&t;&t;   occupied by the compressed kernel/INITRD part of&n;&t;&t;   the BOOTP image include any of the physical pages&n;&t;&t;   into which that part is to be copied for&n;&t;&t;   decompression.&n;&t;&t;*/
r_while
c_loop
(paren
id|check_range
c_func
(paren
id|V_DATA_START
comma
id|V_DATA_END
comma
id|uncompressed_image_start
comma
id|uncompressed_image_end
)paren
)paren
(brace
macro_line|#if 0
id|uncompressed_image_start
op_add_assign
id|K_COPY_IMAGE_SIZE
suffix:semicolon
id|uncompressed_image_end
op_add_assign
id|K_COPY_IMAGE_SIZE
suffix:semicolon
id|initrd_image_start
op_add_assign
id|K_COPY_IMAGE_SIZE
suffix:semicolon
macro_line|#else
multiline_comment|/* Keep as close as possible to end of BOOTP image. */
id|uncompressed_image_start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|uncompressed_image_end
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|initrd_image_start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
macro_line|#endif
)brace
)brace
id|srm_printk
c_func
(paren
l_string|&quot;Starting to load the kernel with args &squot;%s&squot;&bslash;n&quot;
comma
id|envval
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_ADDRESSES
id|srm_printk
c_func
(paren
l_string|&quot;Decompressing the kernel...&bslash;n&quot;
l_string|&quot;...from 0x%lx to 0x%lx size 0x%x&bslash;n&quot;
comma
id|V_DATA_START
comma
id|uncompressed_image_start
comma
id|KERNEL_SIZE
)paren
suffix:semicolon
macro_line|#endif
id|decompress_kernel
c_func
(paren
(paren
r_void
op_star
)paren
id|uncompressed_image_start
comma
(paren
r_void
op_star
)paren
id|V_DATA_START
comma
id|KERNEL_SIZE
comma
id|KERNEL_Z_SIZE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now, move things to their final positions, if/as required.&n;&t; */
macro_line|#ifdef INITRD_IMAGE_SIZE
multiline_comment|/* First, we always move the INITRD image, if present. */
macro_line|#ifdef DEBUG_ADDRESSES
id|srm_printk
c_func
(paren
l_string|&quot;Moving the INITRD image...&bslash;n&quot;
l_string|&quot; from 0x%lx to 0x%lx size 0x%x&bslash;n&quot;
comma
id|V_INITRD_START
comma
id|initrd_image_start
comma
id|INITRD_IMAGE_SIZE
)paren
suffix:semicolon
macro_line|#endif
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|initrd_image_start
comma
(paren
r_void
op_star
)paren
id|V_INITRD_START
comma
id|INITRD_IMAGE_SIZE
)paren
suffix:semicolon
macro_line|#endif /* INITRD_IMAGE_SIZE */
multiline_comment|/* Next, we may have to move the uncompressed kernel to the&n;&t;   final destination.&n;&t; */
r_if
c_cond
(paren
id|must_move
)paren
(brace
macro_line|#ifdef DEBUG_ADDRESSES
id|srm_printk
c_func
(paren
l_string|&quot;Moving the uncompressed kernel...&bslash;n&quot;
l_string|&quot;...from 0x%lx to 0x%lx size 0x%x&bslash;n&quot;
comma
id|uncompressed_image_start
comma
id|K_KERNEL_IMAGE_START
comma
(paren
r_int
)paren
id|KERNEL_SIZE
)paren
suffix:semicolon
macro_line|#endif
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|K_KERNEL_IMAGE_START
comma
(paren
r_void
op_star
)paren
id|uncompressed_image_start
comma
id|KERNEL_SIZE
)paren
suffix:semicolon
)brace
multiline_comment|/* Clear the zero page, then move the argument list in. */
macro_line|#ifdef DEBUG_LAST_STEPS
id|srm_printk
c_func
(paren
l_string|&quot;Preparing ZERO_PGE...&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#ifdef DEBUG_LAST_STEPS
id|srm_printk
c_func
(paren
l_string|&quot;Preparing INITRD info...&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Finally, set the INITRD paramenters for the kernel. */
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
id|initrd_image_start
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
macro_line|#endif /* INITRD_IMAGE_SIZE */
macro_line|#ifdef DEBUG_LAST_STEPS
id|srm_printk
c_func
(paren
l_string|&quot;Doing &squot;runkernel()&squot;...&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|runkernel
c_func
(paren
)paren
suffix:semicolon
)brace
eof
