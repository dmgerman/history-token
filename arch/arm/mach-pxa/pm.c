multiline_comment|/*&n; * PXA250/210 Power Management Routines&n; *&n; * Original code for the SA11x0:&n; * Copyright (c) 2001 Cliff Brake &lt;cbrake@accelent.com&gt;&n; *&n; * Modified for the PXA250 by Nicolas Pitre:&n; * Copyright (c) 2002 Monta Vista Software, Inc.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/arch/pxa-regs.h&gt;
macro_line|#include &lt;asm/arch/lubbock.h&gt;
macro_line|#include &lt;asm/mach/time.h&gt;
multiline_comment|/*&n; * Debug macros&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
r_extern
r_void
id|pxa_cpu_suspend
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pxa_cpu_resume
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|SAVE
mdefine_line|#define SAVE(x)&t;&t;sleep_save[SLEEP_SAVE_##x] = x
DECL|macro|RESTORE
mdefine_line|#define RESTORE(x)&t;x = sleep_save[SLEEP_SAVE_##x]
DECL|macro|RESTORE_GPLEVEL
mdefine_line|#define RESTORE_GPLEVEL(n) do { &bslash;&n;&t;GPSR##n = sleep_save[SLEEP_SAVE_GPLR##n]; &bslash;&n;&t;GPCR##n = ~sleep_save[SLEEP_SAVE_GPLR##n]; &bslash;&n;} while (0)
multiline_comment|/*&n; * List of global PXA peripheral registers to preserve.&n; * More ones like CP and general purpose register values are preserved&n; * with the stack pointer in sleep.S.&n; */
DECL|enumerator|SLEEP_SAVE_START
r_enum
(brace
id|SLEEP_SAVE_START
op_assign
l_int|0
comma
DECL|enumerator|SLEEP_SAVE_OIER
id|SLEEP_SAVE_OIER
comma
DECL|enumerator|SLEEP_SAVE_OSMR0
DECL|enumerator|SLEEP_SAVE_OSMR1
DECL|enumerator|SLEEP_SAVE_OSMR2
DECL|enumerator|SLEEP_SAVE_OSMR3
id|SLEEP_SAVE_OSMR0
comma
id|SLEEP_SAVE_OSMR1
comma
id|SLEEP_SAVE_OSMR2
comma
id|SLEEP_SAVE_OSMR3
comma
DECL|enumerator|SLEEP_SAVE_GPLR0
DECL|enumerator|SLEEP_SAVE_GPLR1
DECL|enumerator|SLEEP_SAVE_GPLR2
id|SLEEP_SAVE_GPLR0
comma
id|SLEEP_SAVE_GPLR1
comma
id|SLEEP_SAVE_GPLR2
comma
DECL|enumerator|SLEEP_SAVE_GPDR0
DECL|enumerator|SLEEP_SAVE_GPDR1
DECL|enumerator|SLEEP_SAVE_GPDR2
id|SLEEP_SAVE_GPDR0
comma
id|SLEEP_SAVE_GPDR1
comma
id|SLEEP_SAVE_GPDR2
comma
DECL|enumerator|SLEEP_SAVE_GRER0
DECL|enumerator|SLEEP_SAVE_GRER1
DECL|enumerator|SLEEP_SAVE_GRER2
id|SLEEP_SAVE_GRER0
comma
id|SLEEP_SAVE_GRER1
comma
id|SLEEP_SAVE_GRER2
comma
DECL|enumerator|SLEEP_SAVE_GFER0
DECL|enumerator|SLEEP_SAVE_GFER1
DECL|enumerator|SLEEP_SAVE_GFER2
id|SLEEP_SAVE_GFER0
comma
id|SLEEP_SAVE_GFER1
comma
id|SLEEP_SAVE_GFER2
comma
DECL|enumerator|SLEEP_SAVE_GAFR0_L
DECL|enumerator|SLEEP_SAVE_GAFR1_L
DECL|enumerator|SLEEP_SAVE_GAFR2_L
id|SLEEP_SAVE_GAFR0_L
comma
id|SLEEP_SAVE_GAFR1_L
comma
id|SLEEP_SAVE_GAFR2_L
comma
DECL|enumerator|SLEEP_SAVE_GAFR0_U
DECL|enumerator|SLEEP_SAVE_GAFR1_U
DECL|enumerator|SLEEP_SAVE_GAFR2_U
id|SLEEP_SAVE_GAFR0_U
comma
id|SLEEP_SAVE_GAFR1_U
comma
id|SLEEP_SAVE_GAFR2_U
comma
DECL|enumerator|SLEEP_SAVE_ICMR
id|SLEEP_SAVE_ICMR
comma
DECL|enumerator|SLEEP_SAVE_CKEN
id|SLEEP_SAVE_CKEN
comma
DECL|enumerator|SLEEP_SAVE_CKSUM
id|SLEEP_SAVE_CKSUM
comma
DECL|enumerator|SLEEP_SAVE_SIZE
id|SLEEP_SAVE_SIZE
)brace
suffix:semicolon
DECL|function|pxa_pm_enter
r_static
r_int
id|pxa_pm_enter
c_func
(paren
id|u32
id|state
)paren
(brace
r_int
r_int
id|sleep_save
(braket
id|SLEEP_SAVE_SIZE
)braket
suffix:semicolon
r_int
r_int
id|checksum
op_assign
l_int|0
suffix:semicolon
r_struct
id|timespec
id|delta
comma
id|rtc
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|state
op_ne
id|PM_SUSPEND_MEM
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* preserve current time */
id|rtc.tv_sec
op_assign
id|RCNR
suffix:semicolon
id|rtc.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|save_time_delta
c_func
(paren
op_amp
id|delta
comma
op_amp
id|rtc
)paren
suffix:semicolon
multiline_comment|/* save vital registers */
id|SAVE
c_func
(paren
id|OSMR0
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|OSMR1
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|OSMR2
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|OSMR3
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|OIER
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GPLR0
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GPLR1
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GPLR2
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GPDR0
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GPDR1
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GPDR2
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GRER0
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GRER1
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GRER2
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GFER0
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GFER1
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GFER2
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GAFR0_L
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GAFR0_U
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GAFR1_L
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GAFR1_U
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GAFR2_L
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GAFR2_U
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|ICMR
)paren
suffix:semicolon
id|ICMR
op_assign
l_int|0
suffix:semicolon
id|SAVE
c_func
(paren
id|CKEN
)paren
suffix:semicolon
id|CKEN
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Note: wake up source are set up in each machine specific files */
multiline_comment|/* clear GPIO transition detect  bits */
id|GEDR0
op_assign
id|GEDR0
suffix:semicolon
id|GEDR1
op_assign
id|GEDR1
suffix:semicolon
id|GEDR2
op_assign
id|GEDR2
suffix:semicolon
multiline_comment|/* Clear sleep reset status */
id|RCSR
op_assign
id|RCSR_SMR
suffix:semicolon
multiline_comment|/* set resume return address */
id|PSPR
op_assign
id|virt_to_phys
c_func
(paren
id|pxa_cpu_resume
)paren
suffix:semicolon
multiline_comment|/* before sleeping, calculate and save a checksum */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|SLEEP_SAVE_SIZE
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
id|checksum
op_add_assign
id|sleep_save
(braket
id|i
)braket
suffix:semicolon
id|sleep_save
(braket
id|SLEEP_SAVE_CKSUM
)braket
op_assign
id|checksum
suffix:semicolon
multiline_comment|/* *** go zzz *** */
id|pxa_cpu_suspend
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* after sleeping, validate the checksum */
id|checksum
op_assign
l_int|0
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
id|SLEEP_SAVE_SIZE
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
id|checksum
op_add_assign
id|sleep_save
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/* if invalid, display message and wait for a hardware reset */
r_if
c_cond
(paren
id|checksum
op_ne
id|sleep_save
(braket
id|SLEEP_SAVE_CKSUM
)braket
)paren
(brace
macro_line|#ifdef CONFIG_ARCH_LUBBOCK
id|LUB_HEXLED
op_assign
l_int|0xbadbadc5
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* ensure not to come back here if it wasn&squot;t intended */
id|PSPR
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* restore registers */
id|RESTORE
c_func
(paren
id|GAFR0_L
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|GAFR0_U
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|GAFR1_L
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|GAFR1_U
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|GAFR2_L
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|GAFR2_U
)paren
suffix:semicolon
id|RESTORE_GPLEVEL
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|RESTORE_GPLEVEL
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|RESTORE_GPLEVEL
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|GPDR0
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|GPDR1
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|GPDR2
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|GRER0
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|GRER1
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|GRER2
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|GFER0
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|GFER1
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|GFER2
)paren
suffix:semicolon
id|PSSR
op_assign
id|PSSR_RDH
op_or
id|PSSR_PH
suffix:semicolon
id|RESTORE
c_func
(paren
id|OSMR0
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|OSMR1
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|OSMR2
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|OSMR3
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|OIER
)paren
suffix:semicolon
multiline_comment|/* OSMR0 is the system timer: make sure OSCR is sufficiently behind */
id|OSCR
op_assign
id|OSMR0
op_minus
id|LATCH
suffix:semicolon
id|RESTORE
c_func
(paren
id|CKEN
)paren
suffix:semicolon
id|ICLR
op_assign
l_int|0
suffix:semicolon
id|ICCR
op_assign
l_int|1
suffix:semicolon
id|RESTORE
c_func
(paren
id|ICMR
)paren
suffix:semicolon
multiline_comment|/* restore current time */
id|rtc.tv_sec
op_assign
id|RCNR
suffix:semicolon
id|restore_time_delta
c_func
(paren
op_amp
id|delta
comma
op_amp
id|rtc
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;*** made it back from resume&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sleep_phys_sp
r_int
r_int
id|sleep_phys_sp
c_func
(paren
r_void
op_star
id|sp
)paren
(brace
r_return
id|virt_to_phys
c_func
(paren
id|sp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Called after processes are frozen, but before we shut down devices.&n; */
DECL|function|pxa_pm_prepare
r_static
r_int
id|pxa_pm_prepare
c_func
(paren
id|u32
id|state
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Called after devices are re-setup, but before processes are thawed.&n; */
DECL|function|pxa_pm_finish
r_static
r_int
id|pxa_pm_finish
c_func
(paren
id|u32
id|state
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set to PM_DISK_FIRMWARE so we can quickly veto suspend-to-disk.&n; */
DECL|variable|pxa_pm_ops
r_static
r_struct
id|pm_ops
id|pxa_pm_ops
op_assign
(brace
dot
id|pm_disk_mode
op_assign
id|PM_DISK_FIRMWARE
comma
dot
id|prepare
op_assign
id|pxa_pm_prepare
comma
dot
id|enter
op_assign
id|pxa_pm_enter
comma
dot
id|finish
op_assign
id|pxa_pm_finish
comma
)brace
suffix:semicolon
DECL|function|pxa_pm_init
r_static
r_int
id|__init
id|pxa_pm_init
c_func
(paren
r_void
)paren
(brace
id|pm_set_ops
c_func
(paren
op_amp
id|pxa_pm_ops
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pxa_pm_init
id|late_initcall
c_func
(paren
id|pxa_pm_init
)paren
suffix:semicolon
eof
