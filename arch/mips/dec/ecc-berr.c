multiline_comment|/*&n; *&t;linux/arch/mips/dec/ecc-berr.c&n; *&n; *&t;Bus error event handling code for systems equipped with ECC&n; *&t;handling logic, i.e. DECstation/DECsystem 5000/200 (KN02),&n; *&t;5000/240 (KN03), 5000/260 (KN05) and DECsystem 5900 (KN03),&n; *&t;5900/260 (KN05) systems.&n; *&n; *&t;Copyright (c) 2003  Maciej W. Rozycki&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/dec/ecc.h&gt;
macro_line|#include &lt;asm/dec/kn02.h&gt;
macro_line|#include &lt;asm/dec/kn03.h&gt;
macro_line|#include &lt;asm/dec/kn05.h&gt;
DECL|variable|kn0x_erraddr
r_static
r_volatile
id|u32
op_star
id|kn0x_erraddr
suffix:semicolon
DECL|variable|kn0x_chksyn
r_static
r_volatile
id|u32
op_star
id|kn0x_chksyn
suffix:semicolon
DECL|function|dec_ecc_be_ack
r_static
r_inline
r_void
id|dec_ecc_be_ack
c_func
(paren
r_void
)paren
(brace
op_star
id|kn0x_erraddr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* any write clears the IRQ */
id|iob
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|dec_ecc_be_backend
r_static
r_int
id|dec_ecc_be_backend
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|is_fixup
comma
r_int
id|invoker
)paren
(brace
r_static
r_const
r_char
id|excstr
(braket
)braket
op_assign
l_string|&quot;exception&quot;
suffix:semicolon
r_static
r_const
r_char
id|intstr
(braket
)braket
op_assign
l_string|&quot;interrupt&quot;
suffix:semicolon
r_static
r_const
r_char
id|cpustr
(braket
)braket
op_assign
l_string|&quot;CPU&quot;
suffix:semicolon
r_static
r_const
r_char
id|dmastr
(braket
)braket
op_assign
l_string|&quot;DMA&quot;
suffix:semicolon
r_static
r_const
r_char
id|readstr
(braket
)braket
op_assign
l_string|&quot;read&quot;
suffix:semicolon
r_static
r_const
r_char
id|mreadstr
(braket
)braket
op_assign
l_string|&quot;memory read&quot;
suffix:semicolon
r_static
r_const
r_char
id|writestr
(braket
)braket
op_assign
l_string|&quot;write&quot;
suffix:semicolon
r_static
r_const
r_char
id|mwritstr
(braket
)braket
op_assign
l_string|&quot;partial memory write&quot;
suffix:semicolon
r_static
r_const
r_char
id|timestr
(braket
)braket
op_assign
l_string|&quot;timeout&quot;
suffix:semicolon
r_static
r_const
r_char
id|overstr
(braket
)braket
op_assign
l_string|&quot;overrun&quot;
suffix:semicolon
r_static
r_const
r_char
id|eccstr
(braket
)braket
op_assign
l_string|&quot;ECC error&quot;
suffix:semicolon
r_const
r_char
op_star
id|kind
comma
op_star
id|agent
comma
op_star
id|cycle
comma
op_star
id|event
suffix:semicolon
r_const
r_char
op_star
id|status
op_assign
l_string|&quot;&quot;
comma
op_star
id|xbit
op_assign
l_string|&quot;&quot;
comma
op_star
id|fmt
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|dma_addr_t
id|address
suffix:semicolon
id|u16
id|syn
op_assign
l_int|0
comma
id|sngl
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|u32
id|erraddr
op_assign
op_star
id|kn0x_erraddr
suffix:semicolon
id|u32
id|chksyn
op_assign
op_star
id|kn0x_chksyn
suffix:semicolon
r_int
id|action
op_assign
id|MIPS_BE_FATAL
suffix:semicolon
multiline_comment|/* For non-ECC ack ASAP, so any subsequent errors get caught. */
r_if
c_cond
(paren
(paren
id|erraddr
op_amp
(paren
id|KN0X_EAR_VALID
op_or
id|KN0X_EAR_ECCERR
)paren
)paren
op_eq
id|KN0X_EAR_VALID
)paren
id|dec_ecc_be_ack
c_func
(paren
)paren
suffix:semicolon
id|kind
op_assign
id|invoker
ques
c_cond
id|intstr
suffix:colon
id|excstr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|erraddr
op_amp
id|KN0X_EAR_VALID
)paren
)paren
(brace
multiline_comment|/* No idea what happened. */
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Unidentified bus error %s.&bslash;n&quot;
comma
id|kind
)paren
suffix:semicolon
r_return
id|action
suffix:semicolon
)brace
id|agent
op_assign
(paren
id|erraddr
op_amp
id|KN0X_EAR_CPU
)paren
ques
c_cond
id|cpustr
suffix:colon
id|dmastr
suffix:semicolon
r_if
c_cond
(paren
id|erraddr
op_amp
id|KN0X_EAR_ECCERR
)paren
(brace
multiline_comment|/* An ECC error on a CPU or DMA transaction. */
id|cycle
op_assign
(paren
id|erraddr
op_amp
id|KN0X_EAR_WRITE
)paren
ques
c_cond
id|mwritstr
suffix:colon
id|mreadstr
suffix:semicolon
id|event
op_assign
id|eccstr
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* A CPU timeout or a DMA overrun. */
id|cycle
op_assign
(paren
id|erraddr
op_amp
id|KN0X_EAR_WRITE
)paren
ques
c_cond
id|writestr
suffix:colon
id|readstr
suffix:semicolon
id|event
op_assign
(paren
id|erraddr
op_amp
id|KN0X_EAR_CPU
)paren
ques
c_cond
id|timestr
suffix:colon
id|overstr
suffix:semicolon
)brace
id|address
op_assign
id|erraddr
op_amp
id|KN0X_EAR_ADDRESS
suffix:semicolon
multiline_comment|/* For ECC errors on reads adjust for MT pipelining. */
r_if
c_cond
(paren
(paren
id|erraddr
op_amp
(paren
id|KN0X_EAR_WRITE
op_or
id|KN0X_EAR_ECCERR
)paren
)paren
op_eq
id|KN0X_EAR_ECCERR
)paren
id|address
op_assign
(paren
id|address
op_amp
op_complement
l_int|0xfffLL
)paren
op_or
(paren
(paren
id|address
op_minus
l_int|5
)paren
op_amp
l_int|0xfffLL
)paren
suffix:semicolon
id|address
op_lshift_assign
l_int|2
suffix:semicolon
multiline_comment|/* Only CPU errors are fixable. */
r_if
c_cond
(paren
id|erraddr
op_amp
id|KN0X_EAR_CPU
op_logical_and
id|is_fixup
)paren
id|action
op_assign
id|MIPS_BE_FIXUP
suffix:semicolon
r_if
c_cond
(paren
id|erraddr
op_amp
id|KN0X_EAR_ECCERR
)paren
(brace
r_static
r_const
id|u8
id|data_sbit
(braket
l_int|32
)braket
op_assign
(brace
l_int|0x4f
comma
l_int|0x4a
comma
l_int|0x52
comma
l_int|0x54
comma
l_int|0x57
comma
l_int|0x58
comma
l_int|0x5b
comma
l_int|0x5d
comma
l_int|0x23
comma
l_int|0x25
comma
l_int|0x26
comma
l_int|0x29
comma
l_int|0x2a
comma
l_int|0x2c
comma
l_int|0x31
comma
l_int|0x34
comma
l_int|0x0e
comma
l_int|0x0b
comma
l_int|0x13
comma
l_int|0x15
comma
l_int|0x16
comma
l_int|0x19
comma
l_int|0x1a
comma
l_int|0x1c
comma
l_int|0x62
comma
l_int|0x64
comma
l_int|0x67
comma
l_int|0x68
comma
l_int|0x6b
comma
l_int|0x6d
comma
l_int|0x70
comma
l_int|0x75
comma
)brace
suffix:semicolon
r_static
r_const
id|u8
id|data_mbit
(braket
l_int|25
)braket
op_assign
(brace
l_int|0x07
comma
l_int|0x0d
comma
l_int|0x1f
comma
l_int|0x2f
comma
l_int|0x32
comma
l_int|0x37
comma
l_int|0x38
comma
l_int|0x3b
comma
l_int|0x3d
comma
l_int|0x3e
comma
l_int|0x43
comma
l_int|0x45
comma
l_int|0x46
comma
l_int|0x49
comma
l_int|0x4c
comma
l_int|0x51
comma
l_int|0x5e
comma
l_int|0x61
comma
l_int|0x6e
comma
l_int|0x73
comma
l_int|0x76
comma
l_int|0x79
comma
l_int|0x7a
comma
l_int|0x7c
comma
l_int|0x7f
comma
)brace
suffix:semicolon
r_static
r_const
r_char
id|sbestr
(braket
)braket
op_assign
l_string|&quot;corrected single&quot;
suffix:semicolon
r_static
r_const
r_char
id|dbestr
(braket
)braket
op_assign
l_string|&quot;uncorrectable double&quot;
suffix:semicolon
r_static
r_const
r_char
id|mbestr
(braket
)braket
op_assign
l_string|&quot;uncorrectable multiple&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|address
op_amp
l_int|0x4
)paren
)paren
id|syn
op_assign
id|chksyn
suffix:semicolon
multiline_comment|/* Low bank. */
r_else
id|syn
op_assign
id|chksyn
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* High bank. */
r_if
c_cond
(paren
op_logical_neg
(paren
id|syn
op_amp
id|KN0X_ESR_VLDLO
)paren
)paren
(brace
multiline_comment|/* Ack now, no rewrite will happen. */
id|dec_ecc_be_ack
c_func
(paren
)paren
suffix:semicolon
id|fmt
op_assign
id|KERN_ALERT
l_string|&quot;%s&quot;
l_string|&quot;invalid.&bslash;n&quot;
suffix:semicolon
)brace
r_else
(brace
id|sngl
op_assign
id|syn
op_amp
id|KN0X_ESR_SNGLO
suffix:semicolon
id|syn
op_and_assign
id|KN0X_ESR_SYNLO
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Multibit errors may be tagged incorrectly;&n;&t;&t;&t; * check the syndrome explicitly.&n;&t;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|25
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|syn
op_eq
id|data_mbit
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|25
)paren
(brace
id|status
op_assign
id|mbestr
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|sngl
)paren
(brace
id|status
op_assign
id|dbestr
suffix:semicolon
)brace
r_else
(brace
r_volatile
id|u32
op_star
id|ptr
op_assign
(paren
r_void
op_star
)paren
id|KSEG1ADDR
c_func
(paren
id|address
)paren
suffix:semicolon
op_star
id|ptr
op_assign
op_star
id|ptr
suffix:semicolon
multiline_comment|/* Rewrite. */
id|iob
c_func
(paren
)paren
suffix:semicolon
id|status
op_assign
id|sbestr
suffix:semicolon
id|action
op_assign
id|MIPS_BE_DISCARD
suffix:semicolon
)brace
multiline_comment|/* Ack now, now we&squot;ve rewritten (or not). */
id|dec_ecc_be_ack
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|syn
op_logical_and
id|syn
op_eq
(paren
id|syn
op_amp
op_minus
id|syn
)paren
)paren
(brace
r_if
c_cond
(paren
id|syn
op_eq
l_int|0x01
)paren
(brace
id|fmt
op_assign
id|KERN_ALERT
l_string|&quot;%s&quot;
l_string|&quot;%#04x -- %s bit error &quot;
l_string|&quot;at check bit C%s.&bslash;n&quot;
suffix:semicolon
id|xbit
op_assign
l_string|&quot;X&quot;
suffix:semicolon
)brace
r_else
(brace
id|fmt
op_assign
id|KERN_ALERT
l_string|&quot;%s&quot;
l_string|&quot;%#04x -- %s bit error &quot;
l_string|&quot;at check bit C%s%u.&bslash;n&quot;
suffix:semicolon
)brace
id|i
op_assign
id|syn
op_rshift
l_int|2
suffix:semicolon
)brace
r_else
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
l_int|32
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|syn
op_eq
id|data_sbit
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|32
)paren
id|fmt
op_assign
id|KERN_ALERT
l_string|&quot;%s&quot;
l_string|&quot;%#04x -- %s bit error &quot;
l_string|&quot;at data bit D%s%u.&bslash;n&quot;
suffix:semicolon
r_else
id|fmt
op_assign
id|KERN_ALERT
l_string|&quot;%s&quot;
l_string|&quot;%#04x -- %s bit error.&bslash;n&quot;
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|action
op_ne
id|MIPS_BE_FIXUP
)paren
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Bus error %s: %s %s %s at %#010lx.&bslash;n&quot;
comma
id|kind
comma
id|agent
comma
id|cycle
comma
id|event
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|action
op_ne
id|MIPS_BE_FIXUP
op_logical_and
id|erraddr
op_amp
id|KN0X_EAR_ECCERR
)paren
id|printk
c_func
(paren
id|fmt
comma
l_string|&quot;  ECC syndrome &quot;
comma
id|syn
comma
id|status
comma
id|xbit
comma
id|i
)paren
suffix:semicolon
r_return
id|action
suffix:semicolon
)brace
DECL|function|dec_ecc_be_handler
r_int
id|dec_ecc_be_handler
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
r_return
id|dec_ecc_be_backend
c_func
(paren
id|regs
comma
id|is_fixup
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|dec_ecc_be_interrupt
id|irqreturn_t
id|dec_ecc_be_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|action
op_assign
id|dec_ecc_be_backend
c_func
(paren
id|regs
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|action
op_eq
id|MIPS_BE_DISCARD
)paren
r_return
id|IRQ_NONE
suffix:semicolon
multiline_comment|/*&n;&t; * FIXME: Find affected processes and kill them, otherwise we&n;&t; * must die.&n;&t; *&n;&t; * The interrupt is asynchronously delivered thus EPC and RA&n;&t; * may be irrelevant, but are printed for a reference.&n;&t; */
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Fatal bus interrupt, epc == %08lx, ra == %08lx&bslash;n&quot;
comma
id|regs-&gt;cp0_epc
comma
id|regs-&gt;regs
(braket
l_int|31
)braket
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Unrecoverable bus error&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialization differs a bit between KN02 and KN03/KN05, so we&n; * need two variants.  Once set up, all systems can be handled the&n; * same way.&n; */
DECL|function|dec_kn02_be_init
r_static
r_inline
r_void
id|dec_kn02_be_init
c_func
(paren
r_void
)paren
(brace
r_volatile
id|u32
op_star
id|csr
op_assign
(paren
r_void
op_star
)paren
id|KN02_CSR_BASE
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|kn0x_erraddr
op_assign
(paren
r_void
op_star
)paren
(paren
id|KN02_SLOT_BASE
op_plus
id|KN02_ERRADDR
)paren
suffix:semicolon
id|kn0x_chksyn
op_assign
(paren
r_void
op_star
)paren
(paren
id|KN02_SLOT_BASE
op_plus
id|KN02_CHKSYN
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|kn02_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Preset write-only bits of the Control Register cache. */
id|cached_kn02_csr
op_assign
op_star
id|csr
op_or
id|KN03_CSR_LEDS
suffix:semicolon
multiline_comment|/* Set normal ECC detection and generation. */
id|cached_kn02_csr
op_and_assign
op_complement
(paren
id|KN02_CSR_DIAGCHK
op_or
id|KN02_CSR_DIAGGEN
)paren
suffix:semicolon
multiline_comment|/* Enable ECC correction. */
id|cached_kn02_csr
op_or_assign
id|KN02_CSR_CORRECT
suffix:semicolon
op_star
id|csr
op_assign
id|cached_kn02_csr
suffix:semicolon
id|iob
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|kn02_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|dec_kn03_be_init
r_static
r_inline
r_void
id|dec_kn03_be_init
c_func
(paren
r_void
)paren
(brace
r_volatile
id|u32
op_star
id|mcr
op_assign
(paren
r_void
op_star
)paren
(paren
id|KN03_SLOT_BASE
op_plus
id|IOASIC_MCR
)paren
suffix:semicolon
r_volatile
id|u32
op_star
id|mbcs
op_assign
(paren
r_void
op_star
)paren
(paren
id|KN03_SLOT_BASE
op_plus
id|KN05_MB_CSR
)paren
suffix:semicolon
id|kn0x_erraddr
op_assign
(paren
r_void
op_star
)paren
(paren
id|KN03_SLOT_BASE
op_plus
id|IOASIC_ERRADDR
)paren
suffix:semicolon
id|kn0x_chksyn
op_assign
(paren
r_void
op_star
)paren
(paren
id|KN03_SLOT_BASE
op_plus
id|IOASIC_CHKSYN
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set normal ECC detection and generation, enable ECC correction.&n;&t; * For KN05 we also need to make sure EE (?) is enabled in the MB.&n;&t; * Otherwise DBE/IBE exceptions would be masked but bus error&n;&t; * interrupts would still arrive, resulting in an inevitable crash&n;&t; * if get_dbe() triggers one.&n;&t; */
op_star
id|mcr
op_assign
(paren
op_star
id|mcr
op_amp
op_complement
(paren
id|KN03_MCR_DIAGCHK
op_or
id|KN03_MCR_DIAGGEN
)paren
)paren
op_or
id|KN03_MCR_CORRECT
suffix:semicolon
r_if
c_cond
(paren
id|current_cpu_data.cputype
op_eq
id|CPU_R4400SC
)paren
op_star
id|mbcs
op_or_assign
id|KN05_MB_CSR_EE
suffix:semicolon
id|fast_iob
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|dec_ecc_be_init
r_void
id|__init
id|dec_ecc_be_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|mips_machtype
op_eq
id|MACH_DS5000_200
)paren
id|dec_kn02_be_init
c_func
(paren
)paren
suffix:semicolon
r_else
id|dec_kn03_be_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Clear any leftover errors from the firmware. */
id|dec_ecc_be_ack
c_func
(paren
)paren
suffix:semicolon
)brace
eof
