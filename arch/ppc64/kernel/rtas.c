multiline_comment|/*&n; *&n; * Procedures for interfacing to the RTAS on CHRP machines.&n; *&n; * Peter Bergner, IBM&t;March 2001.&n; * Copyright (C) 2001 IBM.&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/paca.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/abs_addr.h&gt;
macro_line|#include &lt;asm/udbg.h&gt;
DECL|variable|rtas_proc_dir
r_struct
id|proc_dir_entry
op_star
id|rtas_proc_dir
suffix:semicolon
multiline_comment|/* /proc/ppc64/rtas dir */
DECL|variable|rtas_firmware_flash_list
r_struct
id|flash_block_list_header
id|rtas_firmware_flash_list
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/*&n; * prom_init() is called very early on, before the kernel text&n; * and data have been mapped to KERNELBASE.  At this point the code&n; * is running at whatever address it has been loaded at, so&n; * references to extern and static variables must be relocated&n; * explicitly.  The procedure reloc_offset() returns the address&n; * we&squot;re currently running at minus the address we were linked at.&n; * (Note that strings count as static variables.)&n; *&n; * Because OF may have mapped I/O devices into the area starting at&n; * KERNELBASE, particularly on CHRP machines, we can&squot;t safely call&n; * OF once the kernel has been mapped to KERNELBASE.  Therefore all&n; * OF calls should be done within prom_init(), and prom_init()&n; * and all routines called within it must be careful to relocate&n; * references as necessary.&n; *&n; * Note that the bss is cleared *after* prom_init runs, so we have&n; * to make sure that any static or extern variables it accesses&n; * are put in the data segment.&n; */
DECL|variable|rtas
r_struct
id|rtas_t
id|rtas
op_assign
(brace
dot
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
)brace
suffix:semicolon
r_extern
r_int
r_int
id|reloc_offset
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|rtas_data_buf_lock
id|spinlock_t
id|rtas_data_buf_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|rtas_data_buf
r_char
id|rtas_data_buf
(braket
id|RTAS_DATA_BUF_SIZE
)braket
suffix:semicolon
r_void
DECL|function|phys_call_rtas
id|phys_call_rtas
c_func
(paren
r_int
id|token
comma
r_int
id|nargs
comma
r_int
id|nret
comma
dot
dot
dot
)paren
(brace
id|va_list
id|list
suffix:semicolon
r_int
r_int
id|offset
op_assign
id|reloc_offset
c_func
(paren
)paren
suffix:semicolon
r_struct
id|rtas_args
op_star
id|rtas
op_assign
id|PTRRELOC
c_func
(paren
op_amp
(paren
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|xRtas
)paren
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
id|rtas-&gt;token
op_assign
id|token
suffix:semicolon
id|rtas-&gt;nargs
op_assign
id|nargs
suffix:semicolon
id|rtas-&gt;nret
op_assign
id|nret
suffix:semicolon
id|rtas-&gt;rets
op_assign
(paren
id|rtas_arg_t
op_star
)paren
id|PTRRELOC
c_func
(paren
op_amp
(paren
id|rtas-&gt;args
(braket
id|nargs
)braket
)paren
)paren
suffix:semicolon
id|va_start
c_func
(paren
id|list
comma
id|nret
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nargs
suffix:semicolon
id|i
op_increment
)paren
id|rtas-&gt;args
(braket
id|i
)braket
op_assign
(paren
id|rtas_arg_t
)paren
id|LONG_LSW
c_func
(paren
id|va_arg
c_func
(paren
id|list
comma
id|ulong
)paren
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|list
)paren
suffix:semicolon
id|enter_rtas
c_func
(paren
id|rtas
)paren
suffix:semicolon
)brace
r_void
DECL|function|phys_call_rtas_display_status
id|phys_call_rtas_display_status
c_func
(paren
r_char
id|c
)paren
(brace
r_int
r_int
id|offset
op_assign
id|reloc_offset
c_func
(paren
)paren
suffix:semicolon
r_struct
id|rtas_args
op_star
id|rtas
op_assign
id|PTRRELOC
c_func
(paren
op_amp
(paren
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|xRtas
)paren
)paren
suffix:semicolon
id|rtas-&gt;token
op_assign
l_int|10
suffix:semicolon
id|rtas-&gt;nargs
op_assign
l_int|1
suffix:semicolon
id|rtas-&gt;nret
op_assign
l_int|1
suffix:semicolon
id|rtas-&gt;rets
op_assign
(paren
id|rtas_arg_t
op_star
)paren
id|PTRRELOC
c_func
(paren
op_amp
(paren
id|rtas-&gt;args
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
id|rtas-&gt;args
(braket
l_int|0
)braket
op_assign
(paren
r_int
)paren
id|c
suffix:semicolon
id|enter_rtas
c_func
(paren
id|rtas
)paren
suffix:semicolon
)brace
r_void
DECL|function|call_rtas_display_status
id|call_rtas_display_status
c_func
(paren
r_char
id|c
)paren
(brace
r_struct
id|rtas_args
op_star
id|rtas
op_assign
op_amp
(paren
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|xRtas
)paren
suffix:semicolon
id|rtas-&gt;token
op_assign
l_int|10
suffix:semicolon
id|rtas-&gt;nargs
op_assign
l_int|1
suffix:semicolon
id|rtas-&gt;nret
op_assign
l_int|1
suffix:semicolon
id|rtas-&gt;rets
op_assign
(paren
id|rtas_arg_t
op_star
)paren
op_amp
(paren
id|rtas-&gt;args
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|rtas-&gt;args
(braket
l_int|0
)braket
op_assign
(paren
r_int
)paren
id|c
suffix:semicolon
id|enter_rtas
c_func
(paren
(paren
r_void
op_star
)paren
id|__pa
c_func
(paren
(paren
r_int
r_int
)paren
id|rtas
)paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|rtas_token
id|rtas_token
c_func
(paren
r_const
r_char
op_star
id|service
)paren
(brace
r_int
op_star
id|tokp
suffix:semicolon
r_if
c_cond
(paren
id|rtas.dev
op_eq
l_int|NULL
)paren
(brace
id|PPCDBG
c_func
(paren
id|PPCDBG_RTAS
comma
l_string|&quot;&bslash;tNo rtas device in device-tree...&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|RTAS_UNKNOWN_SERVICE
suffix:semicolon
)brace
id|tokp
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|rtas.dev
comma
id|service
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|tokp
ques
c_cond
op_star
id|tokp
suffix:colon
id|RTAS_UNKNOWN_SERVICE
suffix:semicolon
)brace
r_int
DECL|function|rtas_call
id|rtas_call
c_func
(paren
r_int
id|token
comma
r_int
id|nargs
comma
r_int
id|nret
comma
r_int
r_int
op_star
id|outputs
comma
dot
dot
dot
)paren
(brace
id|va_list
id|list
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|s
suffix:semicolon
r_struct
id|rtas_args
op_star
id|rtas_args
op_assign
op_amp
(paren
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|xRtas
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_RTAS
comma
l_string|&quot;Entering rtas_call&bslash;n&quot;
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_RTAS
comma
l_string|&quot;&bslash;ttoken    = 0x%x&bslash;n&quot;
comma
id|token
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_RTAS
comma
l_string|&quot;&bslash;tnargs    = %d&bslash;n&quot;
comma
id|nargs
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_RTAS
comma
l_string|&quot;&bslash;tnret     = %d&bslash;n&quot;
comma
id|nret
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_RTAS
comma
l_string|&quot;&bslash;t&amp;outputs = 0x%lx&bslash;n&quot;
comma
id|outputs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|token
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|rtas_args-&gt;token
op_assign
id|token
suffix:semicolon
id|rtas_args-&gt;nargs
op_assign
id|nargs
suffix:semicolon
id|rtas_args-&gt;nret
op_assign
id|nret
suffix:semicolon
id|rtas_args-&gt;rets
op_assign
(paren
id|rtas_arg_t
op_star
)paren
op_amp
(paren
id|rtas_args-&gt;args
(braket
id|nargs
)braket
)paren
suffix:semicolon
id|va_start
c_func
(paren
id|list
comma
id|outputs
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nargs
suffix:semicolon
op_increment
id|i
)paren
(brace
id|rtas_args-&gt;args
(braket
id|i
)braket
op_assign
(paren
id|rtas_arg_t
)paren
id|LONG_LSW
c_func
(paren
id|va_arg
c_func
(paren
id|list
comma
id|ulong
)paren
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_RTAS
comma
l_string|&quot;&bslash;tnarg[%d] = 0x%lx&bslash;n&quot;
comma
id|i
comma
id|rtas_args-&gt;args
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|va_end
c_func
(paren
id|list
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nret
suffix:semicolon
op_increment
id|i
)paren
id|rtas_args-&gt;rets
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
macro_line|#if 0   /* Gotta do something different here, use global lock for now... */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rtas_args-&gt;lock
comma
id|s
)paren
suffix:semicolon
macro_line|#else
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rtas.lock
comma
id|s
)paren
suffix:semicolon
macro_line|#endif
id|PPCDBG
c_func
(paren
id|PPCDBG_RTAS
comma
l_string|&quot;&bslash;tentering rtas with 0x%lx&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|__pa
c_func
(paren
(paren
r_int
r_int
)paren
id|rtas_args
)paren
)paren
suffix:semicolon
id|enter_rtas
c_func
(paren
(paren
r_void
op_star
)paren
id|__pa
c_func
(paren
(paren
r_int
r_int
)paren
id|rtas_args
)paren
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_RTAS
comma
l_string|&quot;&bslash;treturned from rtas ...&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#if 0   /* Gotta do something different here, use global lock for now... */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rtas_args-&gt;lock
comma
id|s
)paren
suffix:semicolon
macro_line|#else
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rtas.lock
comma
id|s
)paren
suffix:semicolon
macro_line|#endif
id|ifppcdebug
c_func
(paren
id|PPCDBG_RTAS
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nret
suffix:semicolon
id|i
op_increment
)paren
(brace
id|udbg_printf
c_func
(paren
l_string|&quot;&bslash;tnret[%d] = 0x%lx&bslash;n&quot;
comma
id|i
comma
(paren
id|ulong
)paren
id|rtas_args-&gt;rets
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|nret
OG
l_int|1
op_logical_and
id|outputs
op_ne
l_int|NULL
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nret
op_minus
l_int|1
suffix:semicolon
op_increment
id|i
)paren
id|outputs
(braket
id|i
)braket
op_assign
id|rtas_args-&gt;rets
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
r_return
(paren
id|ulong
)paren
(paren
(paren
id|nret
OG
l_int|0
)paren
ques
c_cond
id|rtas_args-&gt;rets
(braket
l_int|0
)braket
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
DECL|macro|FLASH_BLOCK_LIST_VERSION
mdefine_line|#define FLASH_BLOCK_LIST_VERSION (1UL)
r_static
r_void
DECL|function|rtas_flash_firmware
id|rtas_flash_firmware
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|image_size
suffix:semicolon
r_struct
id|flash_block_list
op_star
id|f
comma
op_star
id|next
comma
op_star
id|flist
suffix:semicolon
r_int
r_int
id|rtas_block_list
suffix:semicolon
r_int
id|i
comma
id|status
comma
id|update_token
suffix:semicolon
id|update_token
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;ibm,update-flash-64-and-reboot&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|update_token
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: ibm,update-flash-64-and-reboot is not available -- not a service partition?&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: firmware will not be flashed&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* NOTE: the &quot;first&quot; block list is a global var with no data&n;&t; * blocks in the kernel data segment.  We do this because&n;&t; * we want to ensure this block_list addr is under 4GB.&n;&t; */
id|rtas_firmware_flash_list.num_blocks
op_assign
l_int|0
suffix:semicolon
id|flist
op_assign
(paren
r_struct
id|flash_block_list
op_star
)paren
op_amp
id|rtas_firmware_flash_list
suffix:semicolon
id|rtas_block_list
op_assign
id|virt_to_absolute
c_func
(paren
(paren
r_int
r_int
)paren
id|flist
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtas_block_list
op_ge
(paren
l_int|4UL
op_lshift
l_int|20
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: kernel bug...flash list header addr above 4GB&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: preparing saved firmware image for flash&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Update the block_list in place. */
id|image_size
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|f
op_assign
id|flist
suffix:semicolon
id|f
suffix:semicolon
id|f
op_assign
id|next
)paren
(brace
multiline_comment|/* Translate data addrs to absolute */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|f-&gt;num_blocks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|f-&gt;blocks
(braket
id|i
)braket
dot
id|data
op_assign
(paren
r_char
op_star
)paren
id|virt_to_absolute
c_func
(paren
(paren
r_int
r_int
)paren
id|f-&gt;blocks
(braket
id|i
)braket
dot
id|data
)paren
suffix:semicolon
id|image_size
op_add_assign
id|f-&gt;blocks
(braket
id|i
)braket
dot
id|length
suffix:semicolon
)brace
id|next
op_assign
id|f-&gt;next
suffix:semicolon
id|f-&gt;next
op_assign
(paren
r_struct
id|flash_block_list
op_star
)paren
id|virt_to_absolute
c_func
(paren
(paren
r_int
r_int
)paren
id|f-&gt;next
)paren
suffix:semicolon
multiline_comment|/* make num_blocks into the version/length field */
id|f-&gt;num_blocks
op_assign
(paren
id|FLASH_BLOCK_LIST_VERSION
op_lshift
l_int|56
)paren
op_or
(paren
(paren
id|f-&gt;num_blocks
op_plus
l_int|1
)paren
op_star
l_int|16
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: flash image is %ld bytes&bslash;n&quot;
comma
id|image_size
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: performing flash and reboot&bslash;n&quot;
)paren
suffix:semicolon
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;Flashing        &bslash;n&quot;
comma
l_int|0x0
)paren
suffix:semicolon
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;Please Wait...  &quot;
comma
l_int|0x0
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: this will take several minutes.  Do not power off!&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
id|rtas_call
c_func
(paren
id|update_token
comma
l_int|1
comma
l_int|1
comma
l_int|NULL
comma
id|rtas_block_list
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
multiline_comment|/* should only get &quot;bad&quot; status */
r_case
l_int|0
suffix:colon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: success&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|1
suffix:colon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: hardware error.  Firmware may not be not flashed&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|3
suffix:colon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: image is corrupt or not correct for this platform.  Firmware not flashed&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|4
suffix:colon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: flash failed when partially complete.  System may not reboot&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: unknown flash return code %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|rtas_flash_bypass_warning
r_void
id|rtas_flash_bypass_warning
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: firmware flash requires a reboot&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: the firmware image will NOT be flashed&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_void
DECL|function|rtas_restart
id|rtas_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
r_if
c_cond
(paren
id|rtas_firmware_flash_list.next
)paren
id|rtas_flash_firmware
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;RTAS system-reboot returned %ld&bslash;n&quot;
comma
id|rtas_call
c_func
(paren
id|rtas_token
c_func
(paren
l_string|&quot;system-reboot&quot;
)paren
comma
l_int|0
comma
l_int|1
comma
l_int|NULL
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
r_void
DECL|function|rtas_power_off
id|rtas_power_off
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|rtas_firmware_flash_list.next
)paren
id|rtas_flash_bypass_warning
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* allow power on only with power button press */
id|printk
c_func
(paren
l_string|&quot;RTAS power-off returned %ld&bslash;n&quot;
comma
id|rtas_call
c_func
(paren
id|rtas_token
c_func
(paren
l_string|&quot;power-off&quot;
)paren
comma
l_int|2
comma
l_int|1
comma
l_int|NULL
comma
l_int|0xffffffff
comma
l_int|0xffffffff
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
r_void
DECL|function|rtas_halt
id|rtas_halt
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|rtas_firmware_flash_list.next
)paren
id|rtas_flash_bypass_warning
c_func
(paren
)paren
suffix:semicolon
id|rtas_power_off
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|rtas_proc_dir
id|EXPORT_SYMBOL
c_func
(paren
id|rtas_proc_dir
)paren
suffix:semicolon
DECL|variable|rtas_firmware_flash_list
id|EXPORT_SYMBOL
c_func
(paren
id|rtas_firmware_flash_list
)paren
suffix:semicolon
DECL|variable|rtas_token
id|EXPORT_SYMBOL
c_func
(paren
id|rtas_token
)paren
suffix:semicolon
DECL|variable|rtas_call
id|EXPORT_SYMBOL
c_func
(paren
id|rtas_call
)paren
suffix:semicolon
DECL|variable|rtas_data_buf
id|EXPORT_SYMBOL
c_func
(paren
id|rtas_data_buf
)paren
suffix:semicolon
DECL|variable|rtas_data_buf_lock
id|EXPORT_SYMBOL
c_func
(paren
id|rtas_data_buf_lock
)paren
suffix:semicolon
eof
