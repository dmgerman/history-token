multiline_comment|/* linux/arch/arm/mach-s3c2410/pm.h&n; *&n; * Copyright (c) 2004 Simtec Electronics&n; *&t;Written by Ben Dooks, &lt;ben@simtec.co.uk&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n;*/
multiline_comment|/* s3c2410_pm_init&n; *&n; * called from board at initialisation time to setup the power&n; * management&n;*/
r_extern
id|__init
r_int
id|s3c2410_pm_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* configuration for the IRQ mask over sleep */
r_extern
r_int
r_int
id|s3c_irqwake_intmask
suffix:semicolon
r_extern
r_int
r_int
id|s3c_irqwake_eintmask
suffix:semicolon
multiline_comment|/* IRQ masks for IRQs allowed to go to sleep (see irq.c) */
r_extern
r_int
r_int
id|s3c_irqwake_intallow
suffix:semicolon
r_extern
r_int
r_int
id|s3c_irqwake_eintallow
suffix:semicolon
multiline_comment|/* Flags for PM Control */
r_extern
r_int
r_int
id|s3c_pm_flags
suffix:semicolon
multiline_comment|/* from sleep.S */
r_extern
r_void
id|s3c2410_cpu_suspend
c_func
(paren
r_int
r_int
op_star
id|saveblk
)paren
suffix:semicolon
r_extern
r_void
id|s3c2410_cpu_resume
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|s3c2410_sleep_save_phys
suffix:semicolon
eof
