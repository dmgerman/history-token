multiline_comment|/*&n; *  linux/arch/arm/kernel/armksyms.c&n; *&n; *  Copyright (C) 2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/proc-fns.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
r_extern
r_void
id|dump_thread
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_struct
id|user
op_star
)paren
suffix:semicolon
r_extern
r_int
id|dump_fpu
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_struct
id|user_fp_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|inswb
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|to
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|outswb
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|to
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|__bad_xchg
c_func
(paren
r_volatile
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/*&n; * syscalls&n; */
r_extern
r_int
id|sys_write
c_func
(paren
r_int
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sys_read
c_func
(paren
r_int
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sys_lseek
c_func
(paren
r_int
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sys_exit
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * libgcc functions - functions that are used internally by the&n; * compiler...  (prototypes are not correct though, but that&n; * doesn&squot;t really matter since they&squot;re not versioned).&n; */
r_extern
r_void
id|__ashldi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__ashrdi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__divsi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__lshrdi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__modsi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__muldi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__ucmpdi2
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__udivdi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__udivmoddi4
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__udivsi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__umodsi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ret_from_exception
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fpundefinstr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fp_enter
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * This has a special calling convention; it doesn&squot;t&n; * modify any of the usual registers, except for LR.&n; */
r_extern
r_void
id|__do_softirq
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|EXPORT_SYMBOL_ALIAS
mdefine_line|#define EXPORT_SYMBOL_ALIAS(sym,orig)&t;&t;&bslash;&n; const char __kstrtab_##sym[]&t;&t;&t;&bslash;&n;  __attribute__((section(&quot;.kstrtab&quot;))) =&t;&bslash;&n;    __MODULE_STRING(sym);&t;&t;&t;&bslash;&n; const struct module_symbol __ksymtab_##sym&t;&bslash;&n;  __attribute__((section(&quot;__ksymtab&quot;))) =&t;&bslash;&n;    { (unsigned long)&amp;##orig, __kstrtab_##sym };
multiline_comment|/*&n; * floating point math emulator support.&n; * These symbols will never change their calling convention...&n; */
id|EXPORT_SYMBOL_ALIAS
c_func
(paren
id|kern_fp_enter
comma
id|fp_enter
)paren
suffix:semicolon
id|EXPORT_SYMBOL_ALIAS
c_func
(paren
id|fp_printk
comma
id|printk
)paren
suffix:semicolon
id|EXPORT_SYMBOL_ALIAS
c_func
(paren
id|fp_send_sig
comma
id|send_sig
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_26
DECL|variable|fpundefinstr
id|EXPORT_SYMBOL
c_func
(paren
id|fpundefinstr
)paren
suffix:semicolon
DECL|variable|ret_from_exception
id|EXPORT_SYMBOL
c_func
(paren
id|ret_from_exception
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VT
DECL|variable|kd_mksound
id|EXPORT_SYMBOL
c_func
(paren
id|kd_mksound
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|__do_softirq
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__do_softirq
)paren
suffix:semicolon
multiline_comment|/* platform dependent support */
DECL|variable|dump_thread
id|EXPORT_SYMBOL
c_func
(paren
id|dump_thread
)paren
suffix:semicolon
DECL|variable|dump_fpu
id|EXPORT_SYMBOL
c_func
(paren
id|dump_fpu
)paren
suffix:semicolon
DECL|variable|udelay
id|EXPORT_SYMBOL
c_func
(paren
id|udelay
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_32
DECL|variable|__ioremap
id|EXPORT_SYMBOL
c_func
(paren
id|__ioremap
)paren
suffix:semicolon
DECL|variable|__iounmap
id|EXPORT_SYMBOL
c_func
(paren
id|__iounmap
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|kernel_thread
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_thread
)paren
suffix:semicolon
DECL|variable|system_rev
id|EXPORT_SYMBOL
c_func
(paren
id|system_rev
)paren
suffix:semicolon
DECL|variable|system_serial_low
id|EXPORT_SYMBOL
c_func
(paren
id|system_serial_low
)paren
suffix:semicolon
DECL|variable|system_serial_high
id|EXPORT_SYMBOL
c_func
(paren
id|system_serial_high
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_BUGVERBOSE
DECL|variable|__bug
id|EXPORT_SYMBOL
c_func
(paren
id|__bug
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|__bad_xchg
id|EXPORT_SYMBOL
c_func
(paren
id|__bad_xchg
)paren
suffix:semicolon
DECL|variable|__readwrite_bug
id|EXPORT_SYMBOL
c_func
(paren
id|__readwrite_bug
)paren
suffix:semicolon
DECL|variable|enable_irq
id|EXPORT_SYMBOL
c_func
(paren
id|enable_irq
)paren
suffix:semicolon
DECL|variable|disable_irq
id|EXPORT_SYMBOL
c_func
(paren
id|disable_irq
)paren
suffix:semicolon
DECL|variable|set_irq_type
id|EXPORT_SYMBOL
c_func
(paren
id|set_irq_type
)paren
suffix:semicolon
DECL|variable|pm_idle
id|EXPORT_SYMBOL
c_func
(paren
id|pm_idle
)paren
suffix:semicolon
DECL|variable|pm_power_off
id|EXPORT_SYMBOL
c_func
(paren
id|pm_power_off
)paren
suffix:semicolon
multiline_comment|/* processor dependencies */
DECL|variable|__machine_arch_type
id|EXPORT_SYMBOL
c_func
(paren
id|__machine_arch_type
)paren
suffix:semicolon
multiline_comment|/* networking */
DECL|variable|csum_partial_copy_nocheck
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy_nocheck
)paren
suffix:semicolon
DECL|variable|__csum_ipv6_magic
id|EXPORT_SYMBOL
c_func
(paren
id|__csum_ipv6_magic
)paren
suffix:semicolon
multiline_comment|/* io */
macro_line|#ifndef __raw_readsb
DECL|variable|__raw_readsb
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__raw_readsb
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __raw_readsw
DECL|variable|__raw_readsw
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__raw_readsw
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __raw_readsl
DECL|variable|__raw_readsl
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__raw_readsl
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __raw_writesb
DECL|variable|__raw_writesb
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__raw_writesb
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __raw_writesw
DECL|variable|__raw_writesw
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__raw_writesw
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __raw_writesl
DECL|variable|__raw_writesl
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__raw_writesl
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* address translation */
macro_line|#ifndef __virt_to_phys__is_a_macro
DECL|variable|__virt_to_phys
id|EXPORT_SYMBOL
c_func
(paren
id|__virt_to_phys
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __phys_to_virt__is_a_macro
DECL|variable|__phys_to_virt
id|EXPORT_SYMBOL
c_func
(paren
id|__phys_to_virt
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __virt_to_bus__is_a_macro
DECL|variable|__virt_to_bus
id|EXPORT_SYMBOL
c_func
(paren
id|__virt_to_bus
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __bus_to_virt__is_a_macro
DECL|variable|__bus_to_virt
id|EXPORT_SYMBOL
c_func
(paren
id|__bus_to_virt
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* string / mem functions */
DECL|variable|strcpy
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strcpy
)paren
suffix:semicolon
DECL|variable|strncpy
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strncpy
)paren
suffix:semicolon
DECL|variable|strcat
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strcat
)paren
suffix:semicolon
DECL|variable|strncat
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strncat
)paren
suffix:semicolon
DECL|variable|strcmp
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strcmp
)paren
suffix:semicolon
DECL|variable|strncmp
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strncmp
)paren
suffix:semicolon
DECL|variable|strchr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strchr
)paren
suffix:semicolon
DECL|variable|strlen
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strlen
)paren
suffix:semicolon
DECL|variable|strnlen
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strnlen
)paren
suffix:semicolon
DECL|variable|strpbrk
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strpbrk
)paren
suffix:semicolon
DECL|variable|strtok
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strtok
)paren
suffix:semicolon
DECL|variable|strrchr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strrchr
)paren
suffix:semicolon
DECL|variable|strstr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strstr
)paren
suffix:semicolon
DECL|variable|memset
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memset
)paren
suffix:semicolon
DECL|variable|memcpy
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memcpy
)paren
suffix:semicolon
DECL|variable|memmove
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|memcmp
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memcmp
)paren
suffix:semicolon
DECL|variable|memscan
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memscan
)paren
suffix:semicolon
DECL|variable|__memzero
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__memzero
)paren
suffix:semicolon
multiline_comment|/* user mem (segment) */
macro_line|#if defined(CONFIG_CPU_32)
DECL|variable|__arch_copy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|__arch_copy_from_user
)paren
suffix:semicolon
DECL|variable|__arch_copy_to_user
id|EXPORT_SYMBOL
c_func
(paren
id|__arch_copy_to_user
)paren
suffix:semicolon
DECL|variable|__arch_clear_user
id|EXPORT_SYMBOL
c_func
(paren
id|__arch_clear_user
)paren
suffix:semicolon
DECL|variable|__arch_strnlen_user
id|EXPORT_SYMBOL
c_func
(paren
id|__arch_strnlen_user
)paren
suffix:semicolon
multiline_comment|/* consistent area handling */
DECL|variable|pci_alloc_consistent
id|EXPORT_SYMBOL
c_func
(paren
id|pci_alloc_consistent
)paren
suffix:semicolon
DECL|variable|consistent_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|consistent_alloc
)paren
suffix:semicolon
DECL|variable|consistent_free
id|EXPORT_SYMBOL
c_func
(paren
id|consistent_free
)paren
suffix:semicolon
DECL|variable|consistent_sync
id|EXPORT_SYMBOL
c_func
(paren
id|consistent_sync
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_CPU_26)
DECL|variable|uaccess_kernel
id|EXPORT_SYMBOL
c_func
(paren
id|uaccess_kernel
)paren
suffix:semicolon
DECL|variable|uaccess_user
id|EXPORT_SYMBOL
c_func
(paren
id|uaccess_user
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|__get_user_1
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__get_user_1
)paren
suffix:semicolon
DECL|variable|__get_user_2
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__get_user_2
)paren
suffix:semicolon
DECL|variable|__get_user_4
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__get_user_4
)paren
suffix:semicolon
DECL|variable|__get_user_8
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__get_user_8
)paren
suffix:semicolon
DECL|variable|__put_user_1
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__put_user_1
)paren
suffix:semicolon
DECL|variable|__put_user_2
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__put_user_2
)paren
suffix:semicolon
DECL|variable|__put_user_4
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__put_user_4
)paren
suffix:semicolon
DECL|variable|__put_user_8
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__put_user_8
)paren
suffix:semicolon
multiline_comment|/* gcc lib functions */
DECL|variable|__ashldi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__ashldi3
)paren
suffix:semicolon
DECL|variable|__ashrdi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__ashrdi3
)paren
suffix:semicolon
DECL|variable|__divsi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__divsi3
)paren
suffix:semicolon
DECL|variable|__lshrdi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__lshrdi3
)paren
suffix:semicolon
DECL|variable|__modsi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__modsi3
)paren
suffix:semicolon
DECL|variable|__muldi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__muldi3
)paren
suffix:semicolon
DECL|variable|__ucmpdi2
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__ucmpdi2
)paren
suffix:semicolon
DECL|variable|__udivdi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__udivdi3
)paren
suffix:semicolon
DECL|variable|__udivmoddi4
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__udivmoddi4
)paren
suffix:semicolon
DECL|variable|__udivsi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__udivsi3
)paren
suffix:semicolon
DECL|variable|__umodsi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__umodsi3
)paren
suffix:semicolon
multiline_comment|/* bitops */
DECL|variable|_set_bit_le
id|EXPORT_SYMBOL
c_func
(paren
id|_set_bit_le
)paren
suffix:semicolon
DECL|variable|_test_and_set_bit_le
id|EXPORT_SYMBOL
c_func
(paren
id|_test_and_set_bit_le
)paren
suffix:semicolon
DECL|variable|_clear_bit_le
id|EXPORT_SYMBOL
c_func
(paren
id|_clear_bit_le
)paren
suffix:semicolon
DECL|variable|_test_and_clear_bit_le
id|EXPORT_SYMBOL
c_func
(paren
id|_test_and_clear_bit_le
)paren
suffix:semicolon
DECL|variable|_change_bit_le
id|EXPORT_SYMBOL
c_func
(paren
id|_change_bit_le
)paren
suffix:semicolon
DECL|variable|_test_and_change_bit_le
id|EXPORT_SYMBOL
c_func
(paren
id|_test_and_change_bit_le
)paren
suffix:semicolon
DECL|variable|_find_first_zero_bit_le
id|EXPORT_SYMBOL
c_func
(paren
id|_find_first_zero_bit_le
)paren
suffix:semicolon
DECL|variable|_find_next_zero_bit_le
id|EXPORT_SYMBOL
c_func
(paren
id|_find_next_zero_bit_le
)paren
suffix:semicolon
macro_line|#ifdef __ARMEB__
DECL|variable|_set_bit_be
id|EXPORT_SYMBOL
c_func
(paren
id|_set_bit_be
)paren
suffix:semicolon
DECL|variable|_test_and_set_bit_be
id|EXPORT_SYMBOL
c_func
(paren
id|_test_and_set_bit_be
)paren
suffix:semicolon
DECL|variable|_clear_bit_be
id|EXPORT_SYMBOL
c_func
(paren
id|_clear_bit_be
)paren
suffix:semicolon
DECL|variable|_test_and_clear_bit_be
id|EXPORT_SYMBOL
c_func
(paren
id|_test_and_clear_bit_be
)paren
suffix:semicolon
DECL|variable|_change_bit_be
id|EXPORT_SYMBOL
c_func
(paren
id|_change_bit_be
)paren
suffix:semicolon
DECL|variable|_test_and_change_bit_be
id|EXPORT_SYMBOL
c_func
(paren
id|_test_and_change_bit_be
)paren
suffix:semicolon
DECL|variable|_find_first_zero_bit_be
id|EXPORT_SYMBOL
c_func
(paren
id|_find_first_zero_bit_be
)paren
suffix:semicolon
DECL|variable|_find_next_zero_bit_be
id|EXPORT_SYMBOL
c_func
(paren
id|_find_next_zero_bit_be
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* elf */
DECL|variable|elf_platform
id|EXPORT_SYMBOL
c_func
(paren
id|elf_platform
)paren
suffix:semicolon
DECL|variable|elf_hwcap
id|EXPORT_SYMBOL
c_func
(paren
id|elf_hwcap
)paren
suffix:semicolon
multiline_comment|/* syscalls */
DECL|variable|sys_write
id|EXPORT_SYMBOL
c_func
(paren
id|sys_write
)paren
suffix:semicolon
DECL|variable|sys_read
id|EXPORT_SYMBOL
c_func
(paren
id|sys_read
)paren
suffix:semicolon
DECL|variable|sys_lseek
id|EXPORT_SYMBOL
c_func
(paren
id|sys_lseek
)paren
suffix:semicolon
DECL|variable|sys_open
id|EXPORT_SYMBOL
c_func
(paren
id|sys_open
)paren
suffix:semicolon
DECL|variable|sys_exit
id|EXPORT_SYMBOL
c_func
(paren
id|sys_exit
)paren
suffix:semicolon
DECL|variable|sys_wait4
id|EXPORT_SYMBOL
c_func
(paren
id|sys_wait4
)paren
suffix:semicolon
multiline_comment|/* semaphores */
DECL|variable|__down_failed
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__down_failed
)paren
suffix:semicolon
DECL|variable|__down_interruptible_failed
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__down_interruptible_failed
)paren
suffix:semicolon
DECL|variable|__down_trylock_failed
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__down_trylock_failed
)paren
suffix:semicolon
DECL|variable|__up_wakeup
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__up_wakeup
)paren
suffix:semicolon
DECL|variable|get_wchan
id|EXPORT_SYMBOL
c_func
(paren
id|get_wchan
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PREEMPT
DECL|variable|kernel_flag
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_flag
)paren
suffix:semicolon
macro_line|#endif
eof
