multiline_comment|/*&n; * SA1100 Power Management Routines&n; *&n; * Copyright (c) 2001 Cliff Brake &lt;cbrake@accelent.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License.&n; *&n; * History:&n; *&n; * 2001-02-06:&t;Cliff Brake         Initial code&n; *&n; * 2001-02-25:&t;Sukjae Cho &lt;sjcho@east.isi.edu&gt; &amp;&n; * &t;&t;Chester Kuo &lt;chester@linux.org.tw&gt;&n; * &t;&t;&t;Save more value for the resume function! Support&n; * &t;&t;&t;Bitsy/Assabet/Freebird board&n; *&n; * 2001-08-29:&t;Nicolas Pitre &lt;nico@cam.org&gt;&n; * &t;&t;&t;Cleaned up, pushed platform dependent stuff&n; * &t;&t;&t;in the platform specific files.&n; *&n; * 2002-05-27:&t;Nicolas Pitre&t;Killed sleep.h and the kmalloced save array.&n; * &t;&t;&t;&t;Storage is local on the stack now.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/system.h&gt;
r_extern
r_void
id|sa1100_cpu_suspend
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sa1100_cpu_resume
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|SAVE
mdefine_line|#define SAVE(x)&t;&t;sleep_save[SLEEP_SAVE_##x] = x
DECL|macro|RESTORE
mdefine_line|#define RESTORE(x)&t;x = sleep_save[SLEEP_SAVE_##x]
multiline_comment|/*&n; * List of global SA11x0 peripheral registers to preserve.&n; * More ones like CP and general purpose register values are preserved&n; * on the stack and then the stack pointer is stored last in sleep.S.&n; */
DECL|enumerator|SLEEP_SAVE_SP
r_enum
(brace
id|SLEEP_SAVE_SP
op_assign
l_int|0
comma
DECL|enumerator|SLEEP_SAVE_OSCR
DECL|enumerator|SLEEP_SAVE_OIER
id|SLEEP_SAVE_OSCR
comma
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
DECL|enumerator|SLEEP_SAVE_GPDR
DECL|enumerator|SLEEP_SAVE_GAFR
id|SLEEP_SAVE_GPDR
comma
id|SLEEP_SAVE_GAFR
comma
DECL|enumerator|SLEEP_SAVE_PPDR
DECL|enumerator|SLEEP_SAVE_PPSR
DECL|enumerator|SLEEP_SAVE_PPAR
DECL|enumerator|SLEEP_SAVE_PSDR
id|SLEEP_SAVE_PPDR
comma
id|SLEEP_SAVE_PPSR
comma
id|SLEEP_SAVE_PPAR
comma
id|SLEEP_SAVE_PSDR
comma
DECL|enumerator|SLEEP_SAVE_Ser1SDCR0
id|SLEEP_SAVE_Ser1SDCR0
comma
DECL|enumerator|SLEEP_SAVE_SIZE
id|SLEEP_SAVE_SIZE
)brace
suffix:semicolon
DECL|function|pm_do_suspend
r_int
id|pm_do_suspend
c_func
(paren
r_void
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
id|delta
comma
id|gpio
suffix:semicolon
multiline_comment|/* preserve current time */
id|delta
op_assign
id|xtime.tv_sec
op_minus
id|RCNR
suffix:semicolon
id|gpio
op_assign
id|GPLR
suffix:semicolon
multiline_comment|/* save vital registers */
id|SAVE
c_func
(paren
id|OSCR
)paren
suffix:semicolon
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
id|GPDR
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|GAFR
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|PPDR
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|PPSR
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|PPAR
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|PSDR
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|Ser1SDCR0
)paren
suffix:semicolon
multiline_comment|/* Clear previous reset status */
id|RCSR
op_assign
id|RCSR_HWR
op_or
id|RCSR_SWR
op_or
id|RCSR_WDR
op_or
id|RCSR_SMR
suffix:semicolon
multiline_comment|/* set resume return address */
id|PSPR
op_assign
id|virt_to_phys
c_func
(paren
id|sa1100_cpu_resume
)paren
suffix:semicolon
multiline_comment|/* go zzz */
id|sa1100_cpu_suspend
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Ensure not to come back here if it wasn&squot;t intended&n;&t; */
id|PSPR
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Ensure interrupt sources are disabled; we will re-init&n;&t; * the interrupt subsystem via the device manager.&n;&t; */
id|ICLR
op_assign
l_int|0
suffix:semicolon
id|ICCR
op_assign
l_int|1
suffix:semicolon
id|ICMR
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* restore registers */
id|RESTORE
c_func
(paren
id|GPDR
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|GAFR
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|PPDR
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|PPSR
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|PPAR
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|PSDR
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|Ser1SDCR0
)paren
suffix:semicolon
id|GPSR
op_assign
id|gpio
suffix:semicolon
id|GPCR
op_assign
op_complement
id|gpio
suffix:semicolon
multiline_comment|/*&n;&t; * Clear the peripheral sleep-hold bit.&n;&t; */
id|PSSR
op_assign
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
id|OSCR
)paren
suffix:semicolon
id|RESTORE
c_func
(paren
id|OIER
)paren
suffix:semicolon
multiline_comment|/* restore current time */
id|xtime.tv_sec
op_assign
id|RCNR
op_plus
id|delta
suffix:semicolon
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
eof
