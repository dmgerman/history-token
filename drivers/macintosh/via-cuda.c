multiline_comment|/*&n; * Device driver for the via-cuda on Apple Powermacs.&n; *&n; * The VIA (versatile interface adapter) interfaces to the CUDA,&n; * a 6805 microprocessor core which controls the ADB (Apple Desktop&n; * Bus) which connects to the keyboard and mouse.  The CUDA also&n; * controls system power and the RTC (real time clock) chip.&n; *&n; * Copyright (C) 1996 Paul Mackerras.&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/adb.h&gt;
macro_line|#include &lt;linux/cuda.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#ifdef CONFIG_PPC
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#else
macro_line|#include &lt;asm/macintosh.h&gt;
macro_line|#include &lt;asm/macints.h&gt;
macro_line|#include &lt;asm/machw.h&gt;
macro_line|#include &lt;asm/mac_via.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|variable|via
r_static
r_volatile
r_int
r_char
op_star
id|via
suffix:semicolon
DECL|variable|cuda_lock
r_static
id|spinlock_t
id|cuda_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
macro_line|#ifdef CONFIG_MAC
DECL|macro|CUDA_IRQ
mdefine_line|#define CUDA_IRQ IRQ_MAC_ADB
DECL|macro|__openfirmware
mdefine_line|#define __openfirmware
DECL|macro|eieio
mdefine_line|#define eieio()
macro_line|#else
DECL|macro|CUDA_IRQ
mdefine_line|#define CUDA_IRQ vias-&gt;intrs[0].line
macro_line|#endif
multiline_comment|/* VIA registers - spaced 0x200 bytes apart */
DECL|macro|RS
mdefine_line|#define RS&t;&t;0x200&t;&t;/* skip between registers */
DECL|macro|B
mdefine_line|#define B&t;&t;0&t;&t;/* B-side data */
DECL|macro|A
mdefine_line|#define A&t;&t;RS&t;&t;/* A-side data */
DECL|macro|DIRB
mdefine_line|#define DIRB&t;&t;(2*RS)&t;&t;/* B-side direction (1=output) */
DECL|macro|DIRA
mdefine_line|#define DIRA&t;&t;(3*RS)&t;&t;/* A-side direction (1=output) */
DECL|macro|T1CL
mdefine_line|#define T1CL&t;&t;(4*RS)&t;&t;/* Timer 1 ctr/latch (low 8 bits) */
DECL|macro|T1CH
mdefine_line|#define T1CH&t;&t;(5*RS)&t;&t;/* Timer 1 counter (high 8 bits) */
DECL|macro|T1LL
mdefine_line|#define T1LL&t;&t;(6*RS)&t;&t;/* Timer 1 latch (low 8 bits) */
DECL|macro|T1LH
mdefine_line|#define T1LH&t;&t;(7*RS)&t;&t;/* Timer 1 latch (high 8 bits) */
DECL|macro|T2CL
mdefine_line|#define T2CL&t;&t;(8*RS)&t;&t;/* Timer 2 ctr/latch (low 8 bits) */
DECL|macro|T2CH
mdefine_line|#define T2CH&t;&t;(9*RS)&t;&t;/* Timer 2 counter (high 8 bits) */
DECL|macro|SR
mdefine_line|#define SR&t;&t;(10*RS)&t;&t;/* Shift register */
DECL|macro|ACR
mdefine_line|#define ACR&t;&t;(11*RS)&t;&t;/* Auxiliary control register */
DECL|macro|PCR
mdefine_line|#define PCR&t;&t;(12*RS)&t;&t;/* Peripheral control register */
DECL|macro|IFR
mdefine_line|#define IFR&t;&t;(13*RS)&t;&t;/* Interrupt flag register */
DECL|macro|IER
mdefine_line|#define IER&t;&t;(14*RS)&t;&t;/* Interrupt enable register */
DECL|macro|ANH
mdefine_line|#define ANH&t;&t;(15*RS)&t;&t;/* A-side data, no handshake */
multiline_comment|/* Bits in B data register: all active low */
DECL|macro|TREQ
mdefine_line|#define TREQ&t;&t;0x08&t;&t;/* Transfer request (input) */
DECL|macro|TACK
mdefine_line|#define TACK&t;&t;0x10&t;&t;/* Transfer acknowledge (output) */
DECL|macro|TIP
mdefine_line|#define TIP&t;&t;0x20&t;&t;/* Transfer in progress (output) */
multiline_comment|/* Bits in ACR */
DECL|macro|SR_CTRL
mdefine_line|#define SR_CTRL&t;&t;0x1c&t;&t;/* Shift register control bits */
DECL|macro|SR_EXT
mdefine_line|#define SR_EXT&t;&t;0x0c&t;&t;/* Shift on external clock */
DECL|macro|SR_OUT
mdefine_line|#define SR_OUT&t;&t;0x10&t;&t;/* Shift out if 1 */
multiline_comment|/* Bits in IFR and IER */
DECL|macro|IER_SET
mdefine_line|#define IER_SET&t;&t;0x80&t;&t;/* set bits in IER */
DECL|macro|IER_CLR
mdefine_line|#define IER_CLR&t;&t;0&t;&t;/* clear bits in IER */
DECL|macro|SR_INT
mdefine_line|#define SR_INT&t;&t;0x04&t;&t;/* Shift register full/empty */
DECL|enum|cuda_state
r_static
r_enum
id|cuda_state
(brace
DECL|enumerator|idle
id|idle
comma
DECL|enumerator|sent_first_byte
id|sent_first_byte
comma
DECL|enumerator|sending
id|sending
comma
DECL|enumerator|reading
id|reading
comma
DECL|enumerator|read_done
id|read_done
comma
DECL|enumerator|awaiting_reply
id|awaiting_reply
DECL|variable|cuda_state
)brace
id|cuda_state
suffix:semicolon
DECL|variable|current_req
r_static
r_struct
id|adb_request
op_star
id|current_req
suffix:semicolon
DECL|variable|last_req
r_static
r_struct
id|adb_request
op_star
id|last_req
suffix:semicolon
DECL|variable|cuda_rbuf
r_static
r_int
r_char
id|cuda_rbuf
(braket
l_int|16
)braket
suffix:semicolon
DECL|variable|reply_ptr
r_static
r_int
r_char
op_star
id|reply_ptr
suffix:semicolon
DECL|variable|reading_reply
r_static
r_int
id|reading_reply
suffix:semicolon
DECL|variable|data_index
r_static
r_int
id|data_index
suffix:semicolon
macro_line|#ifdef CONFIG_PPC
DECL|variable|vias
r_static
r_struct
id|device_node
op_star
id|vias
suffix:semicolon
macro_line|#endif
DECL|variable|cuda_fully_inited
r_static
r_int
id|cuda_fully_inited
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_ADB
r_static
r_int
id|cuda_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|cuda_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|cuda_send_request
c_func
(paren
r_struct
id|adb_request
op_star
id|req
comma
r_int
id|sync
)paren
suffix:semicolon
r_static
r_int
id|cuda_adb_autopoll
c_func
(paren
r_int
id|devs
)paren
suffix:semicolon
r_static
r_int
id|cuda_reset_adb_bus
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ADB */
r_static
r_int
id|cuda_init_via
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|cuda_start
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|cuda_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|arg
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_void
id|cuda_input
c_func
(paren
r_int
r_char
op_star
id|buf
comma
r_int
id|nb
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_void
id|cuda_poll
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|cuda_write
c_func
(paren
r_struct
id|adb_request
op_star
id|req
)paren
suffix:semicolon
r_int
id|cuda_request
c_func
(paren
r_struct
id|adb_request
op_star
id|req
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|adb_request
op_star
)paren
comma
r_int
id|nbytes
comma
dot
dot
dot
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ADB
DECL|variable|via_cuda_driver
r_struct
id|adb_driver
id|via_cuda_driver
op_assign
(brace
l_string|&quot;CUDA&quot;
comma
id|cuda_probe
comma
id|cuda_init
comma
id|cuda_send_request
comma
id|cuda_adb_autopoll
comma
id|cuda_poll
comma
id|cuda_reset_adb_bus
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_ADB */
macro_line|#ifdef CONFIG_PPC
r_int
id|__init
DECL|function|find_via_cuda
id|find_via_cuda
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|adb_request
id|req
suffix:semicolon
r_if
c_cond
(paren
id|vias
op_ne
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|vias
op_assign
id|find_devices
c_func
(paren
l_string|&quot;via-cuda&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vias
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vias-&gt;next
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Warning: only using 1st via-cuda&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#if 0
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;find_via_cuda: node = %p, addrs =&quot;
comma
id|vias-&gt;node
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
id|vias-&gt;n_addrs
suffix:semicolon
op_increment
id|i
)paren
id|printk
c_func
(paren
l_string|&quot; %x(%x)&quot;
comma
id|vias-&gt;addrs
(braket
id|i
)braket
dot
id|address
comma
id|vias-&gt;addrs
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;, intrs =&quot;
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
id|vias-&gt;n_intrs
suffix:semicolon
op_increment
id|i
)paren
id|printk
c_func
(paren
l_string|&quot; %x&quot;
comma
id|vias-&gt;intrs
(braket
id|i
)braket
dot
id|line
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|vias-&gt;n_addrs
op_ne
l_int|1
op_logical_or
id|vias-&gt;n_intrs
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;via-cuda: expecting 1 address (%d) and 1 interrupt (%d)&bslash;n&quot;
comma
id|vias-&gt;n_addrs
comma
id|vias-&gt;n_intrs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vias-&gt;n_addrs
OL
l_int|1
op_logical_or
id|vias-&gt;n_intrs
OL
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
)brace
id|via
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
id|ioremap
c_func
(paren
id|vias-&gt;addrs-&gt;address
comma
l_int|0x2000
)paren
suffix:semicolon
id|cuda_state
op_assign
id|idle
suffix:semicolon
id|sys_ctrler
op_assign
id|SYS_CTRLER_CUDA
suffix:semicolon
id|err
op_assign
id|cuda_init_via
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cuda_init_via() failed&bslash;n&quot;
)paren
suffix:semicolon
id|via
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Clear and enable interrupts, but only on PPC. On 68K it&squot;s done  */
multiline_comment|/* for us by the main VIA driver in arch/m68k/mac/via.c        */
macro_line|#ifndef CONFIG_MAC
id|via
(braket
id|IFR
)braket
op_assign
l_int|0x7f
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* clear interrupts by writing 1s */
id|via
(braket
id|IER
)braket
op_assign
id|IER_SET
op_or
id|SR_INT
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* enable interrupt from SR */
macro_line|#endif
multiline_comment|/* enable autopoll */
id|cuda_request
c_func
(paren
op_amp
id|req
comma
l_int|NULL
comma
l_int|3
comma
id|CUDA_PACKET
comma
id|CUDA_AUTOPOLL
comma
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|req.complete
)paren
id|cuda_poll
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PPC */
DECL|function|via_cuda_start
r_static
r_int
id|__init
id|via_cuda_start
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|via
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
macro_line|#ifdef CONFIG_PPC
id|request_OF_resource
c_func
(paren
id|vias
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|CUDA_IRQ
comma
id|cuda_interrupt
comma
l_int|0
comma
l_string|&quot;ADB&quot;
comma
id|cuda_interrupt
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cuda_init: can&squot;t get irq %d&bslash;n&quot;
comma
id|CUDA_IRQ
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Macintosh CUDA driver v0.5 for Unified ADB.&bslash;n&quot;
)paren
suffix:semicolon
id|cuda_fully_inited
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|via_cuda_start
id|device_initcall
c_func
(paren
id|via_cuda_start
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ADB
r_static
r_int
DECL|function|cuda_probe
id|cuda_probe
c_func
(paren
)paren
(brace
macro_line|#ifdef CONFIG_PPC
r_if
c_cond
(paren
id|sys_ctrler
op_ne
id|SYS_CTRLER_CUDA
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|macintosh_config-&gt;adb_type
op_ne
id|MAC_ADB_CUDA
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|via
op_assign
id|via1
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|cuda_init
id|cuda_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PPC
r_if
c_cond
(paren
id|via
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
l_int|0
suffix:semicolon
macro_line|#else 
r_int
id|err
op_assign
id|cuda_init_via
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cuda_init_via() failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
id|via_cuda_start
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif /* CONFIG_ADB */
DECL|macro|WAIT_FOR
mdefine_line|#define WAIT_FOR(cond, what)&t;&t;&t;&t;&t;&bslash;&n;    do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (x = 1000; !(cond); --x) {&t;&t;&t;&t;&bslash;&n;&t;    if (x == 0) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;printk(&quot;Timeout waiting for &quot; what &quot;&bslash;n&quot;);&t;&bslash;&n;&t;&t;return -ENXIO;&t;&t;&t;&t;&t;&bslash;&n;&t;    }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    udelay(100);&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    } while (0)
r_static
r_int
DECL|function|cuda_init_via
id|cuda_init_via
c_func
(paren
)paren
(brace
r_int
id|x
suffix:semicolon
id|via
(braket
id|DIRB
)braket
op_assign
(paren
id|via
(braket
id|DIRB
)braket
op_or
id|TACK
op_or
id|TIP
)paren
op_amp
op_complement
id|TREQ
suffix:semicolon
multiline_comment|/* TACK &amp; TIP out */
id|via
(braket
id|B
)braket
op_or_assign
id|TACK
op_or
id|TIP
suffix:semicolon
multiline_comment|/* negate them */
id|via
(braket
id|ACR
)braket
op_assign
(paren
id|via
(braket
id|ACR
)braket
op_amp
op_complement
id|SR_CTRL
)paren
op_or
id|SR_EXT
suffix:semicolon
multiline_comment|/* SR data in */
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|x
op_assign
id|via
(braket
id|SR
)braket
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* clear any left-over data */
macro_line|#ifndef CONFIG_MAC
id|via
(braket
id|IER
)braket
op_assign
l_int|0x7f
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* disable interrupts from VIA */
macro_line|#endif
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* delay 4ms and then clear any pending interrupt */
id|mdelay
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|x
op_assign
id|via
(braket
id|SR
)braket
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* sync with the CUDA - assert TACK without TIP */
id|via
(braket
id|B
)braket
op_and_assign
op_complement
id|TACK
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* wait for the CUDA to assert TREQ in response */
id|WAIT_FOR
c_func
(paren
(paren
id|via
(braket
id|B
)braket
op_amp
id|TREQ
)paren
op_eq
l_int|0
comma
l_string|&quot;CUDA response to sync&quot;
)paren
suffix:semicolon
multiline_comment|/* wait for the interrupt and then clear it */
id|WAIT_FOR
c_func
(paren
id|via
(braket
id|IFR
)braket
op_amp
id|SR_INT
comma
l_string|&quot;CUDA response to sync (2)&quot;
)paren
suffix:semicolon
id|x
op_assign
id|via
(braket
id|SR
)braket
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* finish the sync by negating TACK */
id|via
(braket
id|B
)braket
op_or_assign
id|TACK
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* wait for the CUDA to negate TREQ and the corresponding interrupt */
id|WAIT_FOR
c_func
(paren
id|via
(braket
id|B
)braket
op_amp
id|TREQ
comma
l_string|&quot;CUDA response to sync (3)&quot;
)paren
suffix:semicolon
id|WAIT_FOR
c_func
(paren
id|via
(braket
id|IFR
)braket
op_amp
id|SR_INT
comma
l_string|&quot;CUDA response to sync (4)&quot;
)paren
suffix:semicolon
id|x
op_assign
id|via
(braket
id|SR
)braket
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|via
(braket
id|B
)braket
op_or_assign
id|TIP
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* should be unnecessary */
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ADB
multiline_comment|/* Send an ADB command */
r_static
r_int
DECL|function|cuda_send_request
id|cuda_send_request
c_func
(paren
r_struct
id|adb_request
op_star
id|req
comma
r_int
id|sync
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|via
op_eq
l_int|NULL
)paren
op_logical_or
op_logical_neg
id|cuda_fully_inited
)paren
(brace
id|req-&gt;complete
op_assign
l_int|1
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|req-&gt;reply_expected
op_assign
l_int|1
suffix:semicolon
id|i
op_assign
id|cuda_write
c_func
(paren
id|req
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
r_if
c_cond
(paren
id|sync
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|req-&gt;complete
)paren
id|cuda_poll
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Enable/disable autopolling */
r_static
r_int
DECL|function|cuda_adb_autopoll
id|cuda_adb_autopoll
c_func
(paren
r_int
id|devs
)paren
(brace
r_struct
id|adb_request
id|req
suffix:semicolon
r_if
c_cond
(paren
(paren
id|via
op_eq
l_int|NULL
)paren
op_logical_or
op_logical_neg
id|cuda_fully_inited
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|cuda_request
c_func
(paren
op_amp
id|req
comma
l_int|NULL
comma
l_int|3
comma
id|CUDA_PACKET
comma
id|CUDA_AUTOPOLL
comma
(paren
id|devs
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|req.complete
)paren
id|cuda_poll
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Reset adb bus - how do we do this?? */
r_static
r_int
DECL|function|cuda_reset_adb_bus
id|cuda_reset_adb_bus
c_func
(paren
r_void
)paren
(brace
r_struct
id|adb_request
id|req
suffix:semicolon
r_if
c_cond
(paren
(paren
id|via
op_eq
l_int|NULL
)paren
op_logical_or
op_logical_neg
id|cuda_fully_inited
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|cuda_request
c_func
(paren
op_amp
id|req
comma
l_int|NULL
comma
l_int|2
comma
id|ADB_PACKET
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* maybe? */
r_while
c_loop
(paren
op_logical_neg
id|req.complete
)paren
id|cuda_poll
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_ADB */
multiline_comment|/* Construct and send a cuda request */
r_int
DECL|function|cuda_request
id|cuda_request
c_func
(paren
r_struct
id|adb_request
op_star
id|req
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|adb_request
op_star
)paren
comma
r_int
id|nbytes
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
r_if
c_cond
(paren
id|via
op_eq
l_int|NULL
)paren
(brace
id|req-&gt;complete
op_assign
l_int|1
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|req-&gt;nbytes
op_assign
id|nbytes
suffix:semicolon
id|req-&gt;done
op_assign
id|done
suffix:semicolon
id|va_start
c_func
(paren
id|list
comma
id|nbytes
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
id|nbytes
suffix:semicolon
op_increment
id|i
)paren
id|req-&gt;data
(braket
id|i
)braket
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|list
)paren
suffix:semicolon
id|req-&gt;reply_expected
op_assign
l_int|1
suffix:semicolon
r_return
id|cuda_write
c_func
(paren
id|req
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|cuda_write
id|cuda_write
c_func
(paren
r_struct
id|adb_request
op_star
id|req
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;nbytes
template_param
id|CUDA_PACKET
)paren
(brace
id|req-&gt;complete
op_assign
l_int|1
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|req-&gt;next
op_assign
l_int|0
suffix:semicolon
id|req-&gt;sent
op_assign
l_int|0
suffix:semicolon
id|req-&gt;complete
op_assign
l_int|0
suffix:semicolon
id|req-&gt;reply_len
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|cuda_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current_req
op_ne
l_int|0
)paren
(brace
id|last_req-&gt;next
op_assign
id|req
suffix:semicolon
id|last_req
op_assign
id|req
suffix:semicolon
)brace
r_else
(brace
id|current_req
op_assign
id|req
suffix:semicolon
id|last_req
op_assign
id|req
suffix:semicolon
r_if
c_cond
(paren
id|cuda_state
op_eq
id|idle
)paren
id|cuda_start
c_func
(paren
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|cuda_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|cuda_start
id|cuda_start
c_func
(paren
)paren
(brace
r_struct
id|adb_request
op_star
id|req
suffix:semicolon
multiline_comment|/* assert cuda_state == idle */
multiline_comment|/* get the packet to send */
id|req
op_assign
id|current_req
suffix:semicolon
r_if
c_cond
(paren
id|req
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|via
(braket
id|B
)braket
op_amp
id|TREQ
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/* a byte is coming in from the CUDA */
multiline_comment|/* set the shift register to shift out and send a byte */
id|via
(braket
id|ACR
)braket
op_or_assign
id|SR_OUT
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|via
(braket
id|SR
)braket
op_assign
id|req-&gt;data
(braket
l_int|0
)braket
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|via
(braket
id|B
)braket
op_and_assign
op_complement
id|TIP
suffix:semicolon
id|cuda_state
op_assign
id|sent_first_byte
suffix:semicolon
)brace
r_void
DECL|function|cuda_poll
id|cuda_poll
c_func
(paren
)paren
(brace
r_if
c_cond
(paren
id|via
(braket
id|IFR
)braket
op_amp
id|SR_INT
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* cuda_interrupt only takes a normal lock, we disable&n;&t; * interrupts here to avoid re-entering and thus deadlocking.&n;&t; * An option would be to disable only the IRQ source with&n;&t; * disable_irq(), would that work on m68k ? --BenH&n;&t; */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cuda_interrupt
c_func
(paren
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|cuda_interrupt
id|cuda_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|arg
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|x
comma
id|status
suffix:semicolon
r_struct
id|adb_request
op_star
id|req
op_assign
l_int|NULL
suffix:semicolon
r_int
r_char
id|ibuf
(braket
l_int|16
)braket
suffix:semicolon
r_int
id|ibuf_len
op_assign
l_int|0
suffix:semicolon
r_int
id|complete
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|via
(braket
id|IFR
)braket
op_amp
id|SR_INT
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cuda_lock
)paren
suffix:semicolon
id|status
op_assign
(paren
op_complement
id|via
(braket
id|B
)braket
op_amp
(paren
id|TIP
op_or
id|TREQ
)paren
)paren
op_or
(paren
id|via
(braket
id|ACR
)braket
op_amp
id|SR_OUT
)paren
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* printk(&quot;cuda_interrupt: state=%d status=%x&bslash;n&quot;, cuda_state, status); */
r_switch
c_cond
(paren
id|cuda_state
)paren
(brace
r_case
id|idle
suffix:colon
multiline_comment|/* CUDA has sent us the first byte of data - unsolicited */
r_if
c_cond
(paren
id|status
op_ne
id|TREQ
)paren
id|printk
c_func
(paren
l_string|&quot;cuda: state=idle, status=%x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|x
op_assign
id|via
(braket
id|SR
)braket
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|via
(braket
id|B
)braket
op_and_assign
op_complement
id|TIP
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|cuda_state
op_assign
id|reading
suffix:semicolon
id|reply_ptr
op_assign
id|cuda_rbuf
suffix:semicolon
id|reading_reply
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|awaiting_reply
suffix:colon
multiline_comment|/* CUDA has sent us the first byte of data of a reply */
r_if
c_cond
(paren
id|status
op_ne
id|TREQ
)paren
id|printk
c_func
(paren
l_string|&quot;cuda: state=awaiting_reply, status=%x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|x
op_assign
id|via
(braket
id|SR
)braket
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|via
(braket
id|B
)braket
op_and_assign
op_complement
id|TIP
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|cuda_state
op_assign
id|reading
suffix:semicolon
id|reply_ptr
op_assign
id|current_req-&gt;reply
suffix:semicolon
id|reading_reply
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sent_first_byte
suffix:colon
r_if
c_cond
(paren
id|status
op_eq
id|TREQ
op_plus
id|TIP
op_plus
id|SR_OUT
)paren
(brace
multiline_comment|/* collision */
id|via
(braket
id|ACR
)braket
op_and_assign
op_complement
id|SR_OUT
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|x
op_assign
id|via
(braket
id|SR
)braket
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|via
(braket
id|B
)braket
op_or_assign
id|TIP
op_or
id|TACK
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|cuda_state
op_assign
id|idle
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* assert status == TIP + SR_OUT */
r_if
c_cond
(paren
id|status
op_ne
id|TIP
op_plus
id|SR_OUT
)paren
id|printk
c_func
(paren
l_string|&quot;cuda: state=sent_first_byte status=%x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|via
(braket
id|SR
)braket
op_assign
id|current_req-&gt;data
(braket
l_int|1
)braket
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|via
(braket
id|B
)braket
op_xor_assign
id|TACK
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|data_index
op_assign
l_int|2
suffix:semicolon
id|cuda_state
op_assign
id|sending
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|sending
suffix:colon
id|req
op_assign
id|current_req
suffix:semicolon
r_if
c_cond
(paren
id|data_index
op_ge
id|req-&gt;nbytes
)paren
(brace
id|via
(braket
id|ACR
)braket
op_and_assign
op_complement
id|SR_OUT
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|x
op_assign
id|via
(braket
id|SR
)braket
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|via
(braket
id|B
)braket
op_or_assign
id|TACK
op_or
id|TIP
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|req-&gt;sent
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;reply_expected
)paren
(brace
id|cuda_state
op_assign
id|awaiting_reply
suffix:semicolon
)brace
r_else
(brace
id|current_req
op_assign
id|req-&gt;next
suffix:semicolon
id|complete
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* not sure about this */
id|cuda_state
op_assign
id|idle
suffix:semicolon
id|cuda_start
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|via
(braket
id|SR
)braket
op_assign
id|req-&gt;data
(braket
id|data_index
op_increment
)braket
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|via
(braket
id|B
)braket
op_xor_assign
id|TACK
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|reading
suffix:colon
op_star
id|reply_ptr
op_increment
op_assign
id|via
(braket
id|SR
)braket
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|TIP
)paren
(brace
multiline_comment|/* that&squot;s all folks */
id|via
(braket
id|B
)braket
op_or_assign
id|TACK
op_or
id|TIP
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|cuda_state
op_assign
id|read_done
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* assert status == TIP | TREQ */
r_if
c_cond
(paren
id|status
op_ne
id|TIP
op_plus
id|TREQ
)paren
id|printk
c_func
(paren
l_string|&quot;cuda: state=reading status=%x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|via
(braket
id|B
)braket
op_xor_assign
id|TACK
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|read_done
suffix:colon
id|x
op_assign
id|via
(braket
id|SR
)braket
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reading_reply
)paren
(brace
id|req
op_assign
id|current_req
suffix:semicolon
id|req-&gt;reply_len
op_assign
id|reply_ptr
op_minus
id|req-&gt;reply
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;data
(braket
l_int|0
)braket
op_eq
id|ADB_PACKET
)paren
(brace
multiline_comment|/* Have to adjust the reply from ADB commands */
r_if
c_cond
(paren
id|req-&gt;reply_len
op_le
l_int|2
op_logical_or
(paren
id|req-&gt;reply
(braket
l_int|1
)braket
op_amp
l_int|2
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* the 0x2 bit indicates no response */
id|req-&gt;reply_len
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* leave just the command and result bytes in the reply */
id|req-&gt;reply_len
op_sub_assign
l_int|2
suffix:semicolon
id|memmove
c_func
(paren
id|req-&gt;reply
comma
id|req-&gt;reply
op_plus
l_int|2
comma
id|req-&gt;reply_len
)paren
suffix:semicolon
)brace
)brace
id|current_req
op_assign
id|req-&gt;next
suffix:semicolon
id|complete
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* This is tricky. We must break the spinlock to call&n;&t;     * cuda_input. However, doing so means we might get&n;&t;     * re-entered from another CPU getting an interrupt&n;&t;     * or calling cuda_poll(). I ended up using the stack&n;&t;     * (it&squot;s only for 16 bytes) and moving the actual&n;&t;     * call to cuda_input to outside of the lock.&n;&t;     */
id|ibuf_len
op_assign
id|reply_ptr
op_minus
id|cuda_rbuf
suffix:semicolon
id|memcpy
c_func
(paren
id|ibuf
comma
id|cuda_rbuf
comma
id|ibuf_len
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_eq
id|TREQ
)paren
(brace
id|via
(braket
id|B
)braket
op_and_assign
op_complement
id|TIP
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|cuda_state
op_assign
id|reading
suffix:semicolon
id|reply_ptr
op_assign
id|cuda_rbuf
suffix:semicolon
id|reading_reply
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|cuda_state
op_assign
id|idle
suffix:semicolon
id|cuda_start
c_func
(paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;cuda_interrupt: unknown cuda_state %d?&bslash;n&quot;
comma
id|cuda_state
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|cuda_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|complete
op_logical_and
id|req
)paren
(brace
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|adb_request
op_star
)paren
op_assign
id|req-&gt;done
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|req-&gt;complete
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Here, we assume that if the request has a done member, the&n;    &t; * struct request will survive to setting req-&gt;complete to 1&n;    &t; */
r_if
c_cond
(paren
id|done
)paren
(paren
op_star
id|done
)paren
(paren
id|req
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ibuf_len
)paren
id|cuda_input
c_func
(paren
id|ibuf
comma
id|ibuf_len
comma
id|regs
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|cuda_input
id|cuda_input
c_func
(paren
r_int
r_char
op_star
id|buf
comma
r_int
id|nb
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|i
suffix:semicolon
r_switch
c_cond
(paren
id|buf
(braket
l_int|0
)braket
)paren
(brace
r_case
id|ADB_PACKET
suffix:colon
macro_line|#ifdef CONFIG_XMON
r_if
c_cond
(paren
id|nb
op_eq
l_int|5
op_logical_and
id|buf
(braket
l_int|2
)braket
op_eq
l_int|0x2c
)paren
(brace
r_extern
r_int
id|xmon_wants_key
comma
id|xmon_adb_keycode
suffix:semicolon
r_if
c_cond
(paren
id|xmon_wants_key
)paren
(brace
id|xmon_adb_keycode
op_assign
id|buf
(braket
l_int|3
)braket
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_XMON */
macro_line|#ifdef CONFIG_ADB
id|adb_input
c_func
(paren
id|buf
op_plus
l_int|2
comma
id|nb
op_minus
l_int|2
comma
id|regs
comma
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x40
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ADB */
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;data from cuda (%d bytes):&quot;
comma
id|nb
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
id|nb
suffix:semicolon
op_increment
id|i
)paren
id|printk
c_func
(paren
l_string|&quot; %.2x&quot;
comma
id|buf
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
eof
