multiline_comment|/*&n; * ip22-berr.c: Bus error handling.&n; *&n; * Copyright (C) 2002 Ladislav Michl&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/branch.h&gt;
macro_line|#include &lt;asm/sgi/mc.h&gt;
macro_line|#include &lt;asm/sgi/hpc3.h&gt;
DECL|variable|cpu_err_stat
r_static
r_int
r_int
id|cpu_err_stat
suffix:semicolon
multiline_comment|/* Status reg for CPU */
DECL|variable|gio_err_stat
r_static
r_int
r_int
id|gio_err_stat
suffix:semicolon
multiline_comment|/* Status reg for GIO */
DECL|variable|cpu_err_addr
r_static
r_int
r_int
id|cpu_err_addr
suffix:semicolon
multiline_comment|/* Error address reg for CPU */
DECL|variable|gio_err_addr
r_static
r_int
r_int
id|gio_err_addr
suffix:semicolon
multiline_comment|/* Error address reg for GIO */
DECL|function|save_and_clear_buserr
r_static
r_void
id|save_and_clear_buserr
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* save memory controler&squot;s error status registers */
id|cpu_err_addr
op_assign
id|sgimc-&gt;cerr
suffix:semicolon
id|cpu_err_stat
op_assign
id|sgimc-&gt;cstat
suffix:semicolon
id|gio_err_addr
op_assign
id|sgimc-&gt;gerr
suffix:semicolon
id|gio_err_stat
op_assign
id|sgimc-&gt;gstat
suffix:semicolon
id|sgimc-&gt;cstat
op_assign
id|sgimc-&gt;gstat
op_assign
l_int|0
suffix:semicolon
)brace
DECL|macro|GIO_ERRMASK
mdefine_line|#define GIO_ERRMASK&t;0xff00
DECL|macro|CPU_ERRMASK
mdefine_line|#define CPU_ERRMASK&t;0x3f00
DECL|function|print_buserr
r_static
r_void
id|print_buserr
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|cpu_err_stat
op_amp
id|CPU_ERRMASK
)paren
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;CPU error 0x%x&lt;%s%s%s%s%s%s&gt; @ 0x%08x&bslash;n&quot;
comma
id|cpu_err_stat
comma
id|cpu_err_stat
op_amp
id|SGIMC_CSTAT_RD
ques
c_cond
l_string|&quot;RD &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|cpu_err_stat
op_amp
id|SGIMC_CSTAT_PAR
ques
c_cond
l_string|&quot;PAR &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|cpu_err_stat
op_amp
id|SGIMC_CSTAT_ADDR
ques
c_cond
l_string|&quot;ADDR &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|cpu_err_stat
op_amp
id|SGIMC_CSTAT_SYSAD_PAR
ques
c_cond
l_string|&quot;SYSAD &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|cpu_err_stat
op_amp
id|SGIMC_CSTAT_SYSCMD_PAR
ques
c_cond
l_string|&quot;SYSCMD &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|cpu_err_stat
op_amp
id|SGIMC_CSTAT_BAD_DATA
ques
c_cond
l_string|&quot;BAD_DATA &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|cpu_err_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gio_err_stat
op_amp
id|GIO_ERRMASK
)paren
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;GIO error 0x%x:&lt;%s%s%s%s%s%s%s%s&gt; @ 0x08%x&bslash;n&quot;
comma
id|gio_err_stat
comma
id|gio_err_stat
op_amp
id|SGIMC_GSTAT_RD
ques
c_cond
l_string|&quot;RD &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|gio_err_stat
op_amp
id|SGIMC_GSTAT_WR
ques
c_cond
l_string|&quot;WR &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|gio_err_stat
op_amp
id|SGIMC_GSTAT_TIME
ques
c_cond
l_string|&quot;TIME &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|gio_err_stat
op_amp
id|SGIMC_GSTAT_PROM
ques
c_cond
l_string|&quot;PROM &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|gio_err_stat
op_amp
id|SGIMC_GSTAT_ADDR
ques
c_cond
l_string|&quot;ADDR &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|gio_err_stat
op_amp
id|SGIMC_GSTAT_BC
ques
c_cond
l_string|&quot;BC &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|gio_err_stat
op_amp
id|SGIMC_GSTAT_PIO_RD
ques
c_cond
l_string|&quot;PIO_RD &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|gio_err_stat
op_amp
id|SGIMC_GSTAT_PIO_WR
ques
c_cond
l_string|&quot;PIO_WR &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|gio_err_addr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * MC sends an interrupt whenever bus or parity errors occur. In addition,&n; * if the error happened during a CPU read, it also asserts the bus error&n; * pin on the R4K. Code in bus error handler save the MC bus error registers&n; * and then clear the interrupt when this happens.&n; */
DECL|function|ip22_be_interrupt
r_void
id|ip22_be_interrupt
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|save_and_clear_buserr
c_func
(paren
)paren
suffix:semicolon
id|print_buserr
c_func
(paren
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Bus error, epc == %08lx, ra == %08lx&quot;
comma
id|regs-&gt;cp0_epc
comma
id|regs-&gt;regs
(braket
l_int|31
)braket
)paren
suffix:semicolon
)brace
DECL|function|ip22_be_handler
r_int
id|ip22_be_handler
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|is_fixup
)paren
(brace
id|save_and_clear_buserr
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_fixup
)paren
r_return
id|MIPS_BE_FIXUP
suffix:semicolon
id|print_buserr
c_func
(paren
)paren
suffix:semicolon
r_return
id|MIPS_BE_FATAL
suffix:semicolon
)brace
DECL|function|ip22_be_init
r_void
id|__init
id|ip22_be_init
c_func
(paren
r_void
)paren
(brace
id|board_be_handler
op_assign
id|ip22_be_handler
suffix:semicolon
)brace
eof
