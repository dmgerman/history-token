macro_line|#ifndef _ASM_IA64_SYSTEM_H
DECL|macro|_ASM_IA64_SYSTEM_H
mdefine_line|#define _ASM_IA64_SYSTEM_H
multiline_comment|/*&n; * System defines. Note that this is included both from .c and .S&n; * files, so it does only defines, not any C code.  This is based&n; * on information published in the Processor Abstraction Layer&n; * and the System Abstraction Layer manual.&n; *&n; * Copyright (C) 1998-2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 Asit Mallick &lt;asit.k.mallick@intel.com&gt;&n; * Copyright (C) 1999 Don Dugger &lt;don.dugger@intel.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/page.h&gt;
DECL|macro|KERNEL_START
mdefine_line|#define KERNEL_START&t;&t;(PAGE_OFFSET + 68*1024*1024)
DECL|macro|GATE_ADDR
mdefine_line|#define GATE_ADDR&t;&t;(0xa000000000000000 + PAGE_SIZE)
DECL|macro|PERCPU_ADDR
mdefine_line|#define PERCPU_ADDR&t;&t;(0xa000000000000000 + 2*PAGE_SIZE)
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
DECL|struct|pci_vector_struct
r_struct
id|pci_vector_struct
(brace
DECL|member|bus
id|__u16
id|bus
suffix:semicolon
multiline_comment|/* PCI Bus number */
DECL|member|pci_id
id|__u32
id|pci_id
suffix:semicolon
multiline_comment|/* ACPI split 16 bits device, 16 bits function (see section 6.1.1) */
DECL|member|pin
id|__u8
id|pin
suffix:semicolon
multiline_comment|/* PCI PIN (0 = A, 1 = B, 2 = C, 3 = D) */
DECL|member|irq
id|__u8
id|irq
suffix:semicolon
multiline_comment|/* IRQ assigned */
)brace
suffix:semicolon
DECL|struct|ia64_boot_param
r_extern
r_struct
id|ia64_boot_param
(brace
DECL|member|command_line
id|__u64
id|command_line
suffix:semicolon
multiline_comment|/* physical address of command line arguments */
DECL|member|efi_systab
id|__u64
id|efi_systab
suffix:semicolon
multiline_comment|/* physical address of EFI system table */
DECL|member|efi_memmap
id|__u64
id|efi_memmap
suffix:semicolon
multiline_comment|/* physical address of EFI memory map */
DECL|member|efi_memmap_size
id|__u64
id|efi_memmap_size
suffix:semicolon
multiline_comment|/* size of EFI memory map */
DECL|member|efi_memdesc_size
id|__u64
id|efi_memdesc_size
suffix:semicolon
multiline_comment|/* size of an EFI memory map descriptor */
DECL|member|efi_memdesc_version
id|__u32
id|efi_memdesc_version
suffix:semicolon
multiline_comment|/* memory descriptor version */
r_struct
(brace
DECL|member|num_cols
id|__u16
id|num_cols
suffix:semicolon
multiline_comment|/* number of columns on console output device */
DECL|member|num_rows
id|__u16
id|num_rows
suffix:semicolon
multiline_comment|/* number of rows on console output device */
DECL|member|orig_x
id|__u16
id|orig_x
suffix:semicolon
multiline_comment|/* cursor&squot;s x position */
DECL|member|orig_y
id|__u16
id|orig_y
suffix:semicolon
multiline_comment|/* cursor&squot;s y position */
DECL|member|console_info
)brace
id|console_info
suffix:semicolon
DECL|member|fpswa
id|__u64
id|fpswa
suffix:semicolon
multiline_comment|/* physical address of the fpswa interface */
DECL|member|initrd_start
id|__u64
id|initrd_start
suffix:semicolon
DECL|member|initrd_size
id|__u64
id|initrd_size
suffix:semicolon
)brace
op_star
id|ia64_boot_param
suffix:semicolon
r_static
r_inline
r_void
DECL|function|ia64_insn_group_barrier
id|ia64_insn_group_barrier
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;;;&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Macros to force memory ordering.  In these descriptions, &quot;previous&quot;&n; * and &quot;subsequent&quot; refer to program order; &quot;visible&quot; means that all&n; * architecturally visible effects of a memory access have occurred&n; * (at a minimum, this means the memory has been read or written).&n; *&n; *   wmb():&t;Guarantees that all preceding stores to memory-&n; *&t;&t;like regions are visible before any subsequent&n; *&t;&t;stores and that all following stores will be&n; *&t;&t;visible only after all previous stores.&n; *   rmb():&t;Like wmb(), but for reads.&n; *   mb():&t;wmb()/rmb() combo, i.e., all previous memory&n; *&t;&t;accesses are visible before all subsequent&n; *&t;&t;accesses and vice versa.  This is also known as&n; *&t;&t;a &quot;fence.&quot;&n; *&n; * Note: &quot;mb()&quot; and its variants cannot be used as a fence to order&n; * accesses to memory mapped I/O registers.  For that, mf.a needs to&n; * be used.  However, we don&squot;t want to always use mf.a because (a)&n; * it&squot;s (presumably) much slower than mf and (b) mf.a is supported for&n; * sequential memory pages only.&n; */
DECL|macro|mb
mdefine_line|#define mb()&t;__asm__ __volatile__ (&quot;mf&quot; ::: &quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb()&t;mb()
DECL|macro|wmb
mdefine_line|#define wmb()&t;mb()
macro_line|#ifdef CONFIG_SMP
DECL|macro|smp_mb
macro_line|# define smp_mb()&t;mb()
DECL|macro|smp_rmb
macro_line|# define smp_rmb()&t;rmb()
DECL|macro|smp_wmb
macro_line|# define smp_wmb()&t;wmb()
macro_line|#else
DECL|macro|smp_mb
macro_line|# define smp_mb()&t;barrier()
DECL|macro|smp_rmb
macro_line|# define smp_rmb()&t;barrier()
DECL|macro|smp_wmb
macro_line|# define smp_wmb()&t;barrier()
macro_line|#endif
multiline_comment|/*&n; * XXX check on these---I suspect what Linus really wants here is&n; * acquire vs release semantics but we can&squot;t discuss this stuff with&n; * Linus just yet.  Grrr...&n; */
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value)&t;do { (var) = (value); mb(); } while (0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value)&t;do { (var) = (value); mb(); } while (0)
multiline_comment|/*&n; * The group barrier in front of the rsm &amp; ssm are necessary to ensure&n; * that none of the previous instructions in the same group are&n; * affected by the rsm/ssm.&n; */
multiline_comment|/* For spinlocks etc */
macro_line|#ifdef CONFIG_IA64_DEBUG_IRQ
r_extern
r_int
r_int
id|last_cli_ip
suffix:semicolon
DECL|macro|local_irq_save
macro_line|# define local_irq_save(x)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long ip, psr;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&quot;mov %0=psr;; rsm psr.i;;&quot; : &quot;=r&quot; (psr) :: &quot;memory&quot;);&t;&bslash;&n;&t;if (psr &amp; (1UL &lt;&lt; 14)) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ (&quot;mov %0=ip&quot; : &quot;=r&quot;(ip));&t;&t;&t;&t;&t;&bslash;&n;&t;&t;last_cli_ip = ip;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(x) = psr;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|local_irq_disable
macro_line|# define local_irq_disable()&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long ip, psr;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&quot;mov %0=psr;; rsm psr.i;;&quot; : &quot;=r&quot; (psr) :: &quot;memory&quot;);&t;&bslash;&n;&t;if (psr &amp; (1UL &lt;&lt; 14)) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ (&quot;mov %0=ip&quot; : &quot;=r&quot;(ip));&t;&t;&t;&t;&t;&bslash;&n;&t;&t;last_cli_ip = ip;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|local_irq_restore
macro_line|# define local_irq_restore(x)&t;&t;&t;&t;&t;&t; &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;unsigned long ip, old_psr, psr = (x);&t;&t;&t;&t; &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;__asm__ __volatile__ (&quot;;;mov %0=psr; mov psr.l=%1;; srlz.d&quot;&t; &bslash;&n;&t;&t;&t;      : &quot;=&amp;r&quot; (old_psr) : &quot;r&quot; (psr) : &quot;memory&quot;); &bslash;&n;&t;if ((old_psr &amp; (1UL &lt;&lt; 14)) &amp;&amp; !(psr &amp; (1UL &lt;&lt; 14))) {&t;&t; &bslash;&n;&t;&t;__asm__ (&quot;mov %0=ip&quot; : &quot;=r&quot;(ip));&t;&t;&t; &bslash;&n;&t;&t;last_cli_ip = ip;&t;&t;&t;&t;&t; &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;} while (0)
macro_line|#else /* !CONFIG_IA64_DEBUG_IRQ */
multiline_comment|/* clearing of psr.i is implicitly serialized (visible by next insn) */
DECL|macro|local_irq_save
macro_line|# define local_irq_save(x)&t;__asm__ __volatile__ (&quot;mov %0=psr;; rsm psr.i;;&quot;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;      : &quot;=r&quot; (x) :: &quot;memory&quot;)
DECL|macro|local_irq_disable
macro_line|# define local_irq_disable()&t;__asm__ __volatile__ (&quot;;; rsm psr.i;;&quot; ::: &quot;memory&quot;)
multiline_comment|/* (potentially) setting psr.i requires data serialization: */
DECL|macro|local_irq_restore
macro_line|# define local_irq_restore(x)&t;__asm__ __volatile__ (&quot;;; mov psr.l=%0;; srlz.d&quot;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;      :: &quot;r&quot; (x) : &quot;memory&quot;)
macro_line|#endif /* !CONFIG_IA64_DEBUG_IRQ */
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()&t;__asm__ __volatile__ (&quot;;; ssm psr.i;; srlz.d&quot; ::: &quot;memory&quot;)
DECL|macro|__cli
mdefine_line|#define __cli()&t;&t;&t;local_irq_disable ()
DECL|macro|__save_flags
mdefine_line|#define __save_flags(flags)&t;__asm__ __volatile__ (&quot;mov %0=psr&quot; : &quot;=r&quot; (flags) :: &quot;memory&quot;)
DECL|macro|__save_and_cli
mdefine_line|#define __save_and_cli(flags)&t;local_irq_save(flags)
DECL|macro|save_and_cli
mdefine_line|#define save_and_cli(flags)&t;__save_and_cli(flags)
DECL|macro|__sti
mdefine_line|#define __sti()&t;&t;&t;local_irq_enable ()
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(flags)&t;local_irq_restore(flags)
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|__global_cli
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__global_sti
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__global_save_flags
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__global_restore_flags
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|cli
macro_line|# define cli()&t;&t;&t;__global_cli()
DECL|macro|sti
macro_line|# define sti()&t;&t;&t;__global_sti()
DECL|macro|save_flags
macro_line|# define save_flags(flags)&t;((flags) = __global_save_flags())
DECL|macro|restore_flags
macro_line|# define restore_flags(flags)&t;__global_restore_flags(flags)
macro_line|#else /* !CONFIG_SMP */
DECL|macro|cli
macro_line|# define cli()&t;&t;&t;__cli()
DECL|macro|sti
macro_line|# define sti()&t;&t;&t;__sti()
DECL|macro|save_flags
macro_line|# define save_flags(flags)&t;__save_flags(flags)
DECL|macro|restore_flags
macro_line|# define restore_flags(flags)&t;__restore_flags(flags)
macro_line|#endif /* !CONFIG_SMP */
multiline_comment|/*&n; * Force an unresolved reference if someone tries to use&n; * ia64_fetch_and_add() with a bad value.&n; */
r_extern
r_int
r_int
id|__bad_size_for_ia64_fetch_and_add
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__bad_increment_for_ia64_fetch_and_add
(paren
r_void
)paren
suffix:semicolon
DECL|macro|IA64_FETCHADD
mdefine_line|#define IA64_FETCHADD(tmp,v,n,sz)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (sz) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 4:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__ (&quot;fetchadd4.rel %0=[%1],%2&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;      : &quot;=r&quot;(tmp) : &quot;r&quot;(v), &quot;i&quot;(n) : &quot;memory&quot;);&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 8:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__ (&quot;fetchadd8.rel %0=[%1],%2&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;      : &quot;=r&quot;(tmp) : &quot;r&quot;(v), &quot;i&quot;(n) : &quot;memory&quot;);&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      default:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__bad_size_for_ia64_fetch_and_add();&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_fetch_and_add
mdefine_line|#define ia64_fetch_and_add(i,v)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 _tmp;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;volatile __typeof__(*(v)) *_v = (v);&t;&t;&t;&t;&t;&bslash;&n;&t;switch (i) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case -16:&t;IA64_FETCHADD(_tmp, _v, -16, sizeof(*(v))); break;&t;&bslash;&n;&t;      case  -8:&t;IA64_FETCHADD(_tmp, _v,  -8, sizeof(*(v))); break;&t;&bslash;&n;&t;      case  -4:&t;IA64_FETCHADD(_tmp, _v,  -4, sizeof(*(v))); break;&t;&bslash;&n;&t;      case  -1:&t;IA64_FETCHADD(_tmp, _v,  -1, sizeof(*(v))); break;&t;&bslash;&n;&t;      case   1:&t;IA64_FETCHADD(_tmp, _v,   1, sizeof(*(v))); break;&t;&bslash;&n;&t;      case   4:&t;IA64_FETCHADD(_tmp, _v,   4, sizeof(*(v))); break;&t;&bslash;&n;&t;      case   8:&t;IA64_FETCHADD(_tmp, _v,   8, sizeof(*(v))); break;&t;&bslash;&n;&t;      case  16:&t;IA64_FETCHADD(_tmp, _v,  16, sizeof(*(v))); break;&t;&bslash;&n;&t;      default:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_tmp = __bad_increment_for_ia64_fetch_and_add();&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(__typeof__(*(v))) (_tmp + (i));&t;/* return new value */&t;&t;&bslash;&n;})
multiline_comment|/*&n; * This function doesn&squot;t exist, so you&squot;ll get a linker error if&n; * something tries to do an invalid xchg().&n; */
r_extern
r_void
id|__xchg_called_with_bad_pointer
(paren
r_void
)paren
suffix:semicolon
r_static
id|__inline__
r_int
r_int
DECL|function|__xchg
id|__xchg
(paren
r_int
r_int
id|x
comma
r_volatile
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|result
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|__asm__
id|__volatile
(paren
l_string|&quot;xchg1 %0=[%1],%2&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm__
id|__volatile
(paren
l_string|&quot;xchg2 %0=[%1],%2&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__asm__
id|__volatile
(paren
l_string|&quot;xchg4 %0=[%1],%2&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
r_case
l_int|8
suffix:colon
id|__asm__
id|__volatile
(paren
l_string|&quot;xchg8 %0=[%1],%2&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|__xchg_called_with_bad_pointer
c_func
(paren
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x)&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;  ((__typeof__(*(ptr))) __xchg ((unsigned long) (x), (ptr), sizeof(*(ptr))))
multiline_comment|/*&n; * Atomic compare and exchange.  Compare OLD with MEM, if identical,&n; * store NEW in MEM.  Return the initial value in MEM.  Success is&n; * indicated by comparing RETURN with OLD.&n; */
DECL|macro|__HAVE_ARCH_CMPXCHG
mdefine_line|#define __HAVE_ARCH_CMPXCHG 1
multiline_comment|/*&n; * This function doesn&squot;t exist, so you&squot;ll get a linker error&n; * if something tries to do an invalid cmpxchg().&n; */
r_extern
r_int
id|__cmpxchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|ia64_cmpxchg
mdefine_line|#define ia64_cmpxchg(sem,ptr,old,new,size)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof__(ptr) _p_ = (ptr);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof__(new) _n_ = (new);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 _o_, _r_;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 1: _o_ = (__u8 ) (long) (old); break;&t;&t;&t;&t;&bslash;&n;&t;      case 2: _o_ = (__u16) (long) (old); break;&t;&t;&t;&t;&bslash;&n;&t;      case 4: _o_ = (__u32) (long) (old); break;&t;&t;&t;&t;&bslash;&n;&t;      case 8: _o_ = (__u64) (long) (old); break;&t;&t;&t;&t;&bslash;&n;&t;      default: break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; __asm__ __volatile__ (&quot;mov ar.ccv=%0;;&quot; :: &quot;rO&quot;(_o_));&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 1:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__ (&quot;cmpxchg1.&quot;sem&quot; %0=[%1],%2,ar.ccv&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;      : &quot;=r&quot;(_r_) : &quot;r&quot;(_p_), &quot;r&quot;(_n_) : &quot;memory&quot;);&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 2:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__ (&quot;cmpxchg2.&quot;sem&quot; %0=[%1],%2,ar.ccv&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;      : &quot;=r&quot;(_r_) : &quot;r&quot;(_p_), &quot;r&quot;(_n_) : &quot;memory&quot;);&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 4:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__ (&quot;cmpxchg4.&quot;sem&quot; %0=[%1],%2,ar.ccv&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;      : &quot;=r&quot;(_r_) : &quot;r&quot;(_p_), &quot;r&quot;(_n_) : &quot;memory&quot;);&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 8:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__ (&quot;cmpxchg8.&quot;sem&quot; %0=[%1],%2,ar.ccv&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;      : &quot;=r&quot;(_r_) : &quot;r&quot;(_p_), &quot;r&quot;(_n_) : &quot;memory&quot;);&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      default:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_r_ = __cmpxchg_called_with_bad_pointer();&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(__typeof__(old)) _r_;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|cmpxchg_acq
mdefine_line|#define cmpxchg_acq(ptr,o,n)&t;ia64_cmpxchg(&quot;acq&quot;, (ptr), (o), (n), sizeof(*(ptr)))
DECL|macro|cmpxchg_rel
mdefine_line|#define cmpxchg_rel(ptr,o,n)&t;ia64_cmpxchg(&quot;rel&quot;, (ptr), (o), (n), sizeof(*(ptr)))
multiline_comment|/* for compatibility with other platforms: */
DECL|macro|cmpxchg
mdefine_line|#define cmpxchg(ptr,o,n)&t;cmpxchg_acq(ptr,o,n)
macro_line|#ifdef CONFIG_IA64_DEBUG_CMPXCHG
DECL|macro|CMPXCHG_BUGCHECK_DECL
macro_line|# define CMPXCHG_BUGCHECK_DECL&t;int _cmpxchg_bugcheck_count = 128;
DECL|macro|CMPXCHG_BUGCHECK
macro_line|# define CMPXCHG_BUGCHECK(v)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (_cmpxchg_bugcheck_count-- &lt;= 0) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;void *ip;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;extern int printk(const char *fmt, ...);&t;&t;&t;&bslash;&n;&t;&t;asm (&quot;mov %0=ip&quot; : &quot;=r&quot;(ip));&t;&t;&t;&t;&t;&bslash;&n;&t;&t;printk(&quot;CMPXCHG_BUGCHECK: stuck at %p on word %p&bslash;n&quot;, ip, (v));&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
macro_line|#else /* !CONFIG_IA64_DEBUG_CMPXCHG */
DECL|macro|CMPXCHG_BUGCHECK_DECL
macro_line|# define CMPXCHG_BUGCHECK_DECL
DECL|macro|CMPXCHG_BUGCHECK
macro_line|# define CMPXCHG_BUGCHECK(v)
macro_line|#endif /* !CONFIG_IA64_DEBUG_CMPXCHG */
macro_line|#ifdef __KERNEL__
DECL|macro|prepare_to_switch
mdefine_line|#define prepare_to_switch()    do { } while(0)
macro_line|#ifdef CONFIG_IA32_SUPPORT
DECL|macro|IS_IA32_PROCESS
macro_line|# define IS_IA32_PROCESS(regs)&t;(ia64_psr(regs)-&gt;is != 0)
macro_line|#else
DECL|macro|IS_IA32_PROCESS
macro_line|# define IS_IA32_PROCESS(regs)&t;&t;0
macro_line|#endif
multiline_comment|/*&n; * Context switch from one thread to another.  If the two threads have&n; * different address spaces, schedule() has already taken care of&n; * switching to the new address space by calling switch_mm().&n; *&n; * Disabling access to the fph partition and the debug-register&n; * context switch MUST be done before calling ia64_switch_to() since a&n; * newly created thread returns directly to&n; * ia64_ret_from_syscall_clear_r8.&n; */
r_extern
r_void
id|ia64_switch_to
(paren
r_void
op_star
id|next_task
)paren
suffix:semicolon
r_struct
id|task_struct
suffix:semicolon
r_extern
r_void
id|ia64_save_extra
(paren
r_struct
id|task_struct
op_star
id|task
)paren
suffix:semicolon
r_extern
r_void
id|ia64_load_extra
(paren
r_struct
id|task_struct
op_star
id|task
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SMP) &amp;&amp; defined(CONFIG_PERFMON)
DECL|macro|PERFMON_IS_SYSWIDE
macro_line|# define PERFMON_IS_SYSWIDE() (local_cpu_data-&gt;pfm_syst_wide != 0)
macro_line|#else
DECL|macro|PERFMON_IS_SYSWIDE
macro_line|# define PERFMON_IS_SYSWIDE() (0)
macro_line|#endif
DECL|macro|__switch_to
mdefine_line|#define __switch_to(prev,next) do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (((prev)-&gt;thread.flags &amp; (IA64_THREAD_DBG_VALID|IA64_THREAD_PM_VALID))&t;&bslash;&n;&t;    || IS_IA32_PROCESS(ia64_task_regs(prev)) || PERFMON_IS_SYSWIDE())&t;&t;&bslash;&n;&t;&t;ia64_save_extra(prev);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (((next)-&gt;thread.flags &amp; (IA64_THREAD_DBG_VALID|IA64_THREAD_PM_VALID))&t;&bslash;&n;&t;    || IS_IA32_PROCESS(ia64_task_regs(next)) || PERFMON_IS_SYSWIDE())&t;&t;&bslash;&n;&t;&t;ia64_load_extra(next);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_switch_to((next));&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* Return true if this CPU can call the console drivers in printk() */
DECL|macro|arch_consoles_callable
mdefine_line|#define arch_consoles_callable() (cpu_online_map &amp; (1UL &lt;&lt; smp_processor_id()))
multiline_comment|/*&n; * In the SMP case, we save the fph state when context-switching&n; * away from a thread that modified fph.  This way, when the thread&n; * gets scheduled on another CPU, the CPU can pick up the state from&n; * task-&gt;thread.fph, avoiding the complication of having to fetch&n; * the latest fph state from another CPU.&n; */
DECL|macro|switch_to
macro_line|# define switch_to(prev,next) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (ia64_psr(ia64_task_regs(prev))-&gt;mfh) {&t;&t;&t;&t;&bslash;&n;&t;&t;ia64_psr(ia64_task_regs(prev))-&gt;mfh = 0;&t;&t;&t;&bslash;&n;&t;&t;(prev)-&gt;thread.flags |= IA64_THREAD_FPH_VALID;&t;&t;&t;&bslash;&n;&t;&t;__ia64_save_fpu((prev)-&gt;thread.fph);&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_psr(ia64_task_regs(prev))-&gt;dfh = 1;&t;&t;&t;&t;&bslash;&n;&t;__switch_to(prev,next);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
macro_line|#else
DECL|macro|switch_to
macro_line|# define switch_to(prev,next) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_psr(ia64_task_regs(next))-&gt;dfh = (ia64_get_fpu_owner() != (next));&t;&bslash;&n;&t;__switch_to(prev,next);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_SYSTEM_H */
eof
