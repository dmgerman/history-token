multiline_comment|/*&n; *  linux/arch/x86_64/kernel/head64.c -- prepare to run common code&n; *&n; *  Copyright (C) 2000 Andrea Arcangeli &lt;andrea@suse.de&gt; SuSE&n; *&n; *  $Id: head64.c,v 1.22 2001/07/06 14:28:20 ak Exp $&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/proto.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/bootsetup.h&gt;
multiline_comment|/* Don&squot;t add a printk in there. printk relies on the PDA which is not initialized &n;   yet. */
DECL|function|clear_bss
r_static
r_void
id|__init
id|clear_bss
c_func
(paren
r_void
)paren
(brace
r_extern
r_char
id|__bss_start
(braket
)braket
comma
id|__bss_end
(braket
)braket
suffix:semicolon
id|memset
c_func
(paren
id|__bss_start
comma
l_int|0
comma
(paren
r_int
r_int
)paren
id|__bss_end
op_minus
(paren
r_int
r_int
)paren
id|__bss_start
)paren
suffix:semicolon
)brace
r_extern
r_char
id|x86_boot_params
(braket
l_int|2048
)braket
suffix:semicolon
DECL|macro|NEW_CL_POINTER
mdefine_line|#define NEW_CL_POINTER&t;&t;0x228&t;/* Relative to real mode data */
DECL|macro|OLD_CL_MAGIC_ADDR
mdefine_line|#define OLD_CL_MAGIC_ADDR&t;0x90020
DECL|macro|OLD_CL_MAGIC
mdefine_line|#define OLD_CL_MAGIC            0xA33F
DECL|macro|OLD_CL_BASE_ADDR
mdefine_line|#define OLD_CL_BASE_ADDR        0x90000
DECL|macro|OLD_CL_OFFSET
mdefine_line|#define OLD_CL_OFFSET           0x90022
r_extern
r_char
id|saved_command_line
(braket
)braket
suffix:semicolon
DECL|function|copy_bootdata
r_static
r_void
id|__init
id|copy_bootdata
c_func
(paren
r_char
op_star
id|real_mode_data
)paren
(brace
r_int
id|new_data
suffix:semicolon
r_char
op_star
id|command_line
suffix:semicolon
id|memcpy
c_func
(paren
id|x86_boot_params
comma
id|real_mode_data
comma
l_int|2048
)paren
suffix:semicolon
id|new_data
op_assign
op_star
(paren
r_int
op_star
)paren
(paren
id|x86_boot_params
op_plus
id|NEW_CL_POINTER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_data
)paren
(brace
r_if
c_cond
(paren
id|OLD_CL_MAGIC
op_ne
op_star
(paren
id|u16
op_star
)paren
id|OLD_CL_MAGIC_ADDR
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;so old bootloader that it does not support commandline?!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|new_data
op_assign
id|OLD_CL_BASE_ADDR
op_plus
op_star
(paren
id|u16
op_star
)paren
id|OLD_CL_OFFSET
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;old bootloader convention, maybe loadlin?&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|command_line
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
id|u64
)paren
(paren
id|new_data
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|saved_command_line
comma
id|command_line
comma
id|COMMAND_LINE_SIZE
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Bootdata ok (command line is %s)&bslash;n&quot;
comma
id|saved_command_line
)paren
suffix:semicolon
)brace
DECL|function|setup_boot_cpu_data
r_static
r_void
id|__init
id|setup_boot_cpu_data
c_func
(paren
r_void
)paren
(brace
r_int
id|dummy
comma
id|eax
suffix:semicolon
multiline_comment|/* get vendor info */
id|cpuid
c_func
(paren
l_int|0
comma
op_amp
id|boot_cpu_data.cpuid_level
comma
(paren
r_int
op_star
)paren
op_amp
id|boot_cpu_data.x86_vendor_id
(braket
l_int|0
)braket
comma
(paren
r_int
op_star
)paren
op_amp
id|boot_cpu_data.x86_vendor_id
(braket
l_int|8
)braket
comma
(paren
r_int
op_star
)paren
op_amp
id|boot_cpu_data.x86_vendor_id
(braket
l_int|4
)braket
)paren
suffix:semicolon
multiline_comment|/* get cpu type */
id|cpuid
c_func
(paren
l_int|1
comma
op_amp
id|eax
comma
op_amp
id|dummy
comma
op_amp
id|dummy
comma
(paren
r_int
op_star
)paren
op_amp
id|boot_cpu_data.x86_capability
)paren
suffix:semicolon
id|boot_cpu_data.x86
op_assign
(paren
id|eax
op_rshift
l_int|8
)paren
op_amp
l_int|0xf
suffix:semicolon
id|boot_cpu_data.x86_model
op_assign
(paren
id|eax
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
suffix:semicolon
id|boot_cpu_data.x86_mask
op_assign
id|eax
op_amp
l_int|0xf
suffix:semicolon
)brace
DECL|function|x86_64_start_kernel
r_void
id|__init
id|x86_64_start_kernel
c_func
(paren
r_char
op_star
id|real_mode_data
)paren
(brace
r_char
op_star
id|s
suffix:semicolon
id|clear_bss
c_func
(paren
)paren
suffix:semicolon
id|pda_init
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|copy_bootdata
c_func
(paren
id|real_mode_data
)paren
suffix:semicolon
multiline_comment|/* default console: */
r_if
c_cond
(paren
op_logical_neg
id|strstr
c_func
(paren
id|saved_command_line
comma
l_string|&quot;console=&quot;
)paren
)paren
id|strcat
c_func
(paren
id|saved_command_line
comma
l_string|&quot; console=tty0&quot;
)paren
suffix:semicolon
id|s
op_assign
id|strstr
c_func
(paren
id|saved_command_line
comma
l_string|&quot;earlyprintk=&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
op_ne
l_int|NULL
)paren
id|setup_early_printk
c_func
(paren
id|s
op_plus
l_int|12
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DISCONTIGMEM
id|s
op_assign
id|strstr
c_func
(paren
id|saved_command_line
comma
l_string|&quot;numa=&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
op_ne
l_int|NULL
)paren
id|numa_setup
c_func
(paren
id|s
op_plus
l_int|5
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_X86_IO_APIC
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|saved_command_line
comma
l_string|&quot;disableapic&quot;
)paren
)paren
id|disable_apic
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
id|setup_boot_cpu_data
c_func
(paren
)paren
suffix:semicolon
id|start_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
eof
