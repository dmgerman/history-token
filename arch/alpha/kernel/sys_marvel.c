multiline_comment|/*&n; * linux/arch/alpha/kernel/sys_marvel.c&n; *&n; * Marvel / IO7 support&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/core_marvel.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;err_impl.h&quot;
macro_line|#include &quot;irq_impl.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
macro_line|#include &quot;machvec_impl.h&quot;
"&f;"
multiline_comment|/*&n; * Interrupt handling.&n; */
DECL|macro|IRQ_VEC_PE_SHIFT
mdefine_line|#define IRQ_VEC_PE_SHIFT (10)
DECL|macro|IRQ_VEC_IRQ_MASK
mdefine_line|#define IRQ_VEC_IRQ_MASK ((1 &lt;&lt; IRQ_VEC_PE_SHIFT) - 1)
r_static
r_void
DECL|function|io7_device_interrupt
id|io7_device_interrupt
c_func
(paren
r_int
r_int
id|vector
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|pid
suffix:semicolon
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/*&n;&t; * Vector is 0x800 + (interrupt)&n;&t; *&n;&t; * where (interrupt) is:&n;&t; *&n;&t; *&t;...16|15 14|13     4|3 0&n;&t; *&t;-----+-----+--------+---&n;&t; *&t;  PE |  0  |   irq  | 0&n;&t; *&n;&t; * where (irq) is &n;&t; *&n;&t; *       0x0800 - 0x0ff0&t; - 0x0800 + (LSI id &lt;&lt; 4)&n;&t; *&t; 0x1000 - 0x2ff0&t; - 0x1000 + (MSI_DAT&lt;8:0&gt; &lt;&lt; 4)&n;&t; */
id|pid
op_assign
id|vector
op_rshift
l_int|16
suffix:semicolon
id|irq
op_assign
(paren
(paren
id|vector
op_amp
l_int|0xffff
)paren
op_minus
l_int|0x800
)paren
op_rshift
l_int|4
suffix:semicolon
id|irq
op_add_assign
l_int|16
suffix:semicolon
multiline_comment|/* offset for legacy */
id|irq
op_and_assign
id|IRQ_VEC_IRQ_MASK
suffix:semicolon
multiline_comment|/* not too many bits */
id|irq
op_or_assign
id|pid
op_lshift
id|IRQ_VEC_PE_SHIFT
suffix:semicolon
multiline_comment|/* merge the pid     */
id|handle_irq
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
)brace
r_static
r_volatile
r_int
r_int
op_star
DECL|function|io7_get_irq_ctl
id|io7_get_irq_ctl
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|io7
op_star
op_star
id|pio7
)paren
(brace
r_volatile
r_int
r_int
op_star
id|ctl
suffix:semicolon
r_int
r_int
id|pid
suffix:semicolon
r_struct
id|io7
op_star
id|io7
suffix:semicolon
id|pid
op_assign
id|irq
op_rshift
id|IRQ_VEC_PE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|io7
op_assign
id|marvel_find_io7
c_func
(paren
id|pid
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s for nonexistent io7 -- vec %x, pid %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|pid
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|irq
op_and_assign
id|IRQ_VEC_IRQ_MASK
suffix:semicolon
multiline_comment|/* isolate the vector    */
id|irq
op_sub_assign
l_int|16
suffix:semicolon
multiline_comment|/* subtract legacy bias  */
r_if
c_cond
(paren
id|irq
op_ge
l_int|0x180
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s for invalid irq -- pid %d adjusted irq %x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|pid
comma
id|irq
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|ctl
op_assign
op_amp
id|io7-&gt;csrs-&gt;PO7_LSI_CTL
(braket
id|irq
op_amp
l_int|0xff
)braket
dot
id|csr
suffix:semicolon
multiline_comment|/* assume LSI */
r_if
c_cond
(paren
id|irq
op_ge
l_int|0x80
)paren
multiline_comment|/* MSI */
id|ctl
op_assign
op_amp
id|io7-&gt;csrs-&gt;PO7_MSI_CTL
(braket
(paren
(paren
id|irq
op_minus
l_int|0x80
)paren
op_rshift
l_int|5
)paren
op_amp
l_int|0x0f
)braket
dot
id|csr
suffix:semicolon
r_if
c_cond
(paren
id|pio7
)paren
op_star
id|pio7
op_assign
id|io7
suffix:semicolon
r_return
id|ctl
suffix:semicolon
)brace
r_static
r_void
DECL|function|io7_enable_irq
id|io7_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_volatile
r_int
r_int
op_star
id|ctl
suffix:semicolon
r_struct
id|io7
op_star
id|io7
suffix:semicolon
id|ctl
op_assign
id|io7_get_irq_ctl
c_func
(paren
id|irq
comma
op_amp
id|io7
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ctl
op_logical_or
op_logical_neg
id|io7
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: get_ctl failed for irq %x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|io7-&gt;irq_lock
)paren
suffix:semicolon
op_star
id|ctl
op_or_assign
l_int|1UL
op_lshift
l_int|24
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
id|ctl
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|io7-&gt;irq_lock
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|io7_disable_irq
id|io7_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_volatile
r_int
r_int
op_star
id|ctl
suffix:semicolon
r_struct
id|io7
op_star
id|io7
suffix:semicolon
id|ctl
op_assign
id|io7_get_irq_ctl
c_func
(paren
id|irq
comma
op_amp
id|io7
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ctl
op_logical_or
op_logical_neg
id|io7
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: get_ctl failed for irq %x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|io7-&gt;irq_lock
)paren
suffix:semicolon
op_star
id|ctl
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
l_int|24
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
id|ctl
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|io7-&gt;irq_lock
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|io7_startup_irq
id|io7_startup_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|io7_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* never anything pending */
)brace
r_static
r_void
DECL|function|io7_end_irq
id|io7_end_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_amp
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
)paren
)paren
)paren
id|io7_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|marvel_irq_noop
id|marvel_irq_noop
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_return
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|marvel_irq_noop_return
id|marvel_irq_noop_return
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|marvel_legacy_irq_type
r_static
r_struct
id|hw_interrupt_type
id|marvel_legacy_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;LEGACY&quot;
comma
dot
id|startup
op_assign
id|marvel_irq_noop_return
comma
dot
id|shutdown
op_assign
id|marvel_irq_noop
comma
dot
id|enable
op_assign
id|marvel_irq_noop
comma
dot
id|disable
op_assign
id|marvel_irq_noop
comma
dot
id|ack
op_assign
id|marvel_irq_noop
comma
dot
id|end
op_assign
id|marvel_irq_noop
comma
)brace
suffix:semicolon
DECL|variable|io7_lsi_irq_type
r_static
r_struct
id|hw_interrupt_type
id|io7_lsi_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;LSI&quot;
comma
dot
id|startup
op_assign
id|io7_startup_irq
comma
dot
id|shutdown
op_assign
id|io7_disable_irq
comma
dot
id|enable
op_assign
id|io7_enable_irq
comma
dot
id|disable
op_assign
id|io7_disable_irq
comma
dot
id|ack
op_assign
id|io7_disable_irq
comma
dot
id|end
op_assign
id|io7_end_irq
comma
)brace
suffix:semicolon
DECL|variable|io7_msi_irq_type
r_static
r_struct
id|hw_interrupt_type
id|io7_msi_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;MSI&quot;
comma
dot
id|startup
op_assign
id|io7_startup_irq
comma
dot
id|shutdown
op_assign
id|io7_disable_irq
comma
dot
id|enable
op_assign
id|io7_enable_irq
comma
dot
id|disable
op_assign
id|io7_disable_irq
comma
dot
id|ack
op_assign
id|marvel_irq_noop
comma
dot
id|end
op_assign
id|io7_end_irq
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|io7_redirect_irq
id|io7_redirect_irq
c_func
(paren
r_struct
id|io7
op_star
id|io7
comma
r_volatile
r_int
r_int
op_star
id|csr
comma
r_int
r_int
id|where
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|val
op_assign
op_star
id|csr
suffix:semicolon
id|val
op_and_assign
op_complement
(paren
l_int|0x1ffUL
op_lshift
l_int|24
)paren
suffix:semicolon
multiline_comment|/* clear the target pid   */
id|val
op_or_assign
(paren
(paren
r_int
r_int
)paren
id|where
op_lshift
l_int|24
)paren
suffix:semicolon
multiline_comment|/* set the new target pid */
op_star
id|csr
op_assign
id|val
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
id|csr
suffix:semicolon
)brace
r_static
r_void
DECL|function|io7_redirect_one_lsi
id|io7_redirect_one_lsi
c_func
(paren
r_struct
id|io7
op_star
id|io7
comma
r_int
r_int
id|which
comma
r_int
r_int
id|where
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
multiline_comment|/*&n;&t; * LSI_CTL has target PID @ 14&n;&t; */
id|val
op_assign
id|io7-&gt;csrs-&gt;PO7_LSI_CTL
(braket
id|which
)braket
dot
id|csr
suffix:semicolon
id|val
op_and_assign
op_complement
(paren
l_int|0x1ffUL
op_lshift
l_int|14
)paren
suffix:semicolon
multiline_comment|/* clear the target pid */
id|val
op_or_assign
(paren
(paren
r_int
r_int
)paren
id|where
op_lshift
l_int|14
)paren
suffix:semicolon
multiline_comment|/* set teh new target pid */
id|io7-&gt;csrs-&gt;PO7_LSI_CTL
(braket
id|which
)braket
dot
id|csr
op_assign
id|val
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|io7-&gt;csrs-&gt;PO7_LSI_CTL
(braket
id|which
)braket
dot
id|csr
suffix:semicolon
)brace
r_static
r_void
DECL|function|io7_redirect_one_msi
id|io7_redirect_one_msi
c_func
(paren
r_struct
id|io7
op_star
id|io7
comma
r_int
r_int
id|which
comma
r_int
r_int
id|where
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
multiline_comment|/*&n;&t; * MSI_CTL has target PID @ 14&n;&t; */
id|val
op_assign
id|io7-&gt;csrs-&gt;PO7_MSI_CTL
(braket
id|which
)braket
dot
id|csr
suffix:semicolon
id|val
op_and_assign
op_complement
(paren
l_int|0x1ffUL
op_lshift
l_int|14
)paren
suffix:semicolon
multiline_comment|/* clear the target pid */
id|val
op_or_assign
(paren
(paren
r_int
r_int
)paren
id|where
op_lshift
l_int|14
)paren
suffix:semicolon
multiline_comment|/* set teh new target pid */
id|io7-&gt;csrs-&gt;PO7_MSI_CTL
(braket
id|which
)braket
dot
id|csr
op_assign
id|val
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|io7-&gt;csrs-&gt;PO7_MSI_CTL
(braket
id|which
)braket
dot
id|csr
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|init_one_io7_lsi
id|init_one_io7_lsi
c_func
(paren
r_struct
id|io7
op_star
id|io7
comma
r_int
r_int
id|which
comma
r_int
r_int
id|where
)paren
(brace
multiline_comment|/*&n;&t; * LSI_CTL has target PID @ 14&n;&t; */
id|io7-&gt;csrs-&gt;PO7_LSI_CTL
(braket
id|which
)braket
dot
id|csr
op_assign
(paren
(paren
r_int
r_int
)paren
id|where
op_lshift
l_int|14
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|io7-&gt;csrs-&gt;PO7_LSI_CTL
(braket
id|which
)braket
dot
id|csr
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|init_one_io7_msi
id|init_one_io7_msi
c_func
(paren
r_struct
id|io7
op_star
id|io7
comma
r_int
r_int
id|which
comma
r_int
r_int
id|where
)paren
(brace
multiline_comment|/*&n;&t; * MSI_CTL has target PID @ 14&n;&t; */
id|io7-&gt;csrs-&gt;PO7_MSI_CTL
(braket
id|which
)braket
dot
id|csr
op_assign
(paren
(paren
r_int
r_int
)paren
id|where
op_lshift
l_int|14
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|io7-&gt;csrs-&gt;PO7_MSI_CTL
(braket
id|which
)braket
dot
id|csr
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|init_io7_irqs
id|init_io7_irqs
c_func
(paren
r_struct
id|io7
op_star
id|io7
comma
r_struct
id|hw_interrupt_type
op_star
id|lsi_ops
comma
r_struct
id|hw_interrupt_type
op_star
id|msi_ops
)paren
(brace
r_int
id|base
op_assign
(paren
id|io7-&gt;pe
op_lshift
id|IRQ_VEC_PE_SHIFT
)paren
op_plus
l_int|16
suffix:semicolon
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Initializing interrupts for IO7 at PE %u - base %lx&bslash;n&quot;
comma
id|io7-&gt;pe
comma
id|base
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Where should interrupts from this IO7 go?&n;&t; *&n;&t; * They really should be sent to the local CPU to avoid having to&n;&t; * traverse the mesh, but if it&squot;s not an SMP kernel, they have to&n;&t; * go to the boot CPU. Send them all to the boot CPU for now,&n;&t; * as each secondary starts, it can redirect it&squot;s local device &n;&t; * interrupts.&n;&t; */
id|printk
c_func
(paren
l_string|&quot;  Interrupts reported to CPU at PE %u&bslash;n&quot;
comma
id|boot_cpuid
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|io7-&gt;irq_lock
)paren
suffix:semicolon
multiline_comment|/* set up the error irqs */
id|io7_redirect_irq
c_func
(paren
id|io7
comma
op_amp
id|io7-&gt;csrs-&gt;HLT_CTL.csr
comma
id|boot_cpuid
)paren
suffix:semicolon
id|io7_redirect_irq
c_func
(paren
id|io7
comma
op_amp
id|io7-&gt;csrs-&gt;HPI_CTL.csr
comma
id|boot_cpuid
)paren
suffix:semicolon
id|io7_redirect_irq
c_func
(paren
id|io7
comma
op_amp
id|io7-&gt;csrs-&gt;CRD_CTL.csr
comma
id|boot_cpuid
)paren
suffix:semicolon
id|io7_redirect_irq
c_func
(paren
id|io7
comma
op_amp
id|io7-&gt;csrs-&gt;STV_CTL.csr
comma
id|boot_cpuid
)paren
suffix:semicolon
id|io7_redirect_irq
c_func
(paren
id|io7
comma
op_amp
id|io7-&gt;csrs-&gt;HEI_CTL.csr
comma
id|boot_cpuid
)paren
suffix:semicolon
multiline_comment|/* Set up the lsi irqs.  */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|128
suffix:semicolon
op_increment
id|i
)paren
(brace
id|irq_desc
(braket
id|base
op_plus
id|i
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
op_or
id|IRQ_LEVEL
suffix:semicolon
id|irq_desc
(braket
id|base
op_plus
id|i
)braket
dot
id|handler
op_assign
id|lsi_ops
suffix:semicolon
)brace
multiline_comment|/* Disable the implemented irqs in hardware.  */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|0x60
suffix:semicolon
op_increment
id|i
)paren
id|init_one_io7_lsi
c_func
(paren
id|io7
comma
id|i
comma
id|boot_cpuid
)paren
suffix:semicolon
id|init_one_io7_lsi
c_func
(paren
id|io7
comma
l_int|0x74
comma
id|boot_cpuid
)paren
suffix:semicolon
id|init_one_io7_lsi
c_func
(paren
id|io7
comma
l_int|0x75
comma
id|boot_cpuid
)paren
suffix:semicolon
multiline_comment|/* Set up the msi irqs.  */
r_for
c_loop
(paren
id|i
op_assign
l_int|128
suffix:semicolon
id|i
OL
(paren
l_int|128
op_plus
l_int|512
)paren
suffix:semicolon
op_increment
id|i
)paren
(brace
id|irq_desc
(braket
id|base
op_plus
id|i
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
op_or
id|IRQ_LEVEL
suffix:semicolon
id|irq_desc
(braket
id|base
op_plus
id|i
)braket
dot
id|handler
op_assign
id|msi_ops
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
op_increment
id|i
)paren
id|init_one_io7_msi
c_func
(paren
id|io7
comma
id|i
comma
id|boot_cpuid
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|io7-&gt;irq_lock
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|marvel_init_irq
id|marvel_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|io7
op_star
id|io7
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Reserve the legacy irqs.  */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
op_increment
id|i
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|marvel_legacy_irq_type
suffix:semicolon
)brace
multiline_comment|/* Init the io7 irqs.  */
r_for
c_loop
(paren
id|io7
op_assign
l_int|NULL
suffix:semicolon
(paren
id|io7
op_assign
id|marvel_next_io7
c_func
(paren
id|io7
)paren
)paren
op_ne
l_int|NULL
suffix:semicolon
)paren
id|init_io7_irqs
c_func
(paren
id|io7
comma
op_amp
id|io7_lsi_irq_type
comma
op_amp
id|io7_msi_irq_type
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|marvel_map_irq
id|marvel_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|dev-&gt;sysdata
suffix:semicolon
r_struct
id|io7_port
op_star
id|io7_port
op_assign
id|hose-&gt;sysdata
suffix:semicolon
r_struct
id|io7
op_star
id|io7
op_assign
id|io7_port-&gt;io7
suffix:semicolon
r_int
id|msi_loc
comma
id|msi_data_off
suffix:semicolon
id|u16
id|msg_ctl
suffix:semicolon
id|u16
id|msg_dat
suffix:semicolon
id|u8
id|intline
suffix:semicolon
r_int
id|irq
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
op_amp
id|intline
)paren
suffix:semicolon
id|irq
op_assign
id|intline
suffix:semicolon
id|msi_loc
op_assign
id|pci_find_capability
c_func
(paren
id|dev
comma
id|PCI_CAP_ID_MSI
)paren
suffix:semicolon
id|msg_ctl
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|msi_loc
)paren
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|msi_loc
op_plus
id|PCI_MSI_FLAGS
comma
op_amp
id|msg_ctl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msg_ctl
op_amp
id|PCI_MSI_FLAGS_ENABLE
)paren
(brace
id|msi_data_off
op_assign
id|PCI_MSI_DATA_32
suffix:semicolon
r_if
c_cond
(paren
id|msg_ctl
op_amp
id|PCI_MSI_FLAGS_64BIT
)paren
id|msi_data_off
op_assign
id|PCI_MSI_DATA_64
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|msi_loc
op_plus
id|msi_data_off
comma
op_amp
id|msg_dat
)paren
suffix:semicolon
id|irq
op_assign
id|msg_dat
op_amp
l_int|0x1ff
suffix:semicolon
multiline_comment|/* we use msg_data&lt;8:0&gt; */
id|irq
op_add_assign
l_int|0x80
suffix:semicolon
multiline_comment|/* offset for lsi       */
macro_line|#if 1
id|printk
c_func
(paren
l_string|&quot;PCI:%d:%d:%d (hose %d) [%s] is using MSI&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|hose-&gt;index
comma
id|dev-&gt;dev.name
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  %d message(s) from 0x%04x&bslash;n&quot;
comma
l_int|1
op_lshift
(paren
(paren
id|msg_ctl
op_amp
id|PCI_MSI_FLAGS_QSIZE
)paren
op_rshift
l_int|4
)paren
comma
id|msg_dat
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  reporting on %d IRQ(s) from %d (0x%x)&bslash;n&quot;
comma
l_int|1
op_lshift
(paren
(paren
id|msg_ctl
op_amp
id|PCI_MSI_FLAGS_QSIZE
)paren
op_rshift
l_int|4
)paren
comma
(paren
id|irq
op_plus
l_int|16
)paren
op_or
(paren
id|io7-&gt;pe
op_lshift
id|IRQ_VEC_PE_SHIFT
)paren
comma
(paren
id|irq
op_plus
l_int|16
)paren
op_or
(paren
id|io7-&gt;pe
op_lshift
id|IRQ_VEC_PE_SHIFT
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if 0
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|msi_loc
op_plus
id|PCI_MSI_FLAGS
comma
id|msg_ctl
op_amp
op_complement
id|PCI_MSI_FLAGS_ENABLE
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
op_amp
id|intline
)paren
suffix:semicolon
id|irq
op_assign
id|intline
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  forcing LSI interrupt on irq %d [0x%x]&bslash;n&quot;
comma
id|irq
comma
id|irq
)paren
suffix:semicolon
macro_line|#endif
)brace
id|irq
op_add_assign
l_int|16
suffix:semicolon
multiline_comment|/* offset for legacy */
id|irq
op_or_assign
id|io7-&gt;pe
op_lshift
id|IRQ_VEC_PE_SHIFT
suffix:semicolon
multiline_comment|/* merge the pid     */
r_return
id|irq
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|marvel_init_pci
id|marvel_init_pci
c_func
(paren
r_void
)paren
(brace
r_struct
id|io7
op_star
id|io7
suffix:semicolon
id|marvel_register_error_handlers
c_func
(paren
)paren
suffix:semicolon
id|pci_probe_only
op_assign
l_int|1
suffix:semicolon
id|common_init_pci
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_VGA_HOSE
id|locate_and_init_vga
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Clear any io7 errors.  */
r_for
c_loop
(paren
id|io7
op_assign
l_int|NULL
suffix:semicolon
(paren
id|io7
op_assign
id|marvel_next_io7
c_func
(paren
id|io7
)paren
)paren
op_ne
l_int|NULL
suffix:semicolon
)paren
id|io7_clear_errors
c_func
(paren
id|io7
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|marvel_init_rtc
id|marvel_init_rtc
c_func
(paren
r_void
)paren
(brace
id|init_rtc_irq
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|marvel_smp_callin
id|marvel_smp_callin
c_func
(paren
r_void
)paren
(brace
r_int
id|cpuid
op_assign
id|hard_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_struct
id|io7
op_star
id|io7
op_assign
id|marvel_find_io7
c_func
(paren
id|cpuid
)paren
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|io7
)paren
r_return
suffix:semicolon
multiline_comment|/* &n;&t; * There is a local IO7 - redirect all of it&squot;s interrupts here.&n;&t; */
id|printk
c_func
(paren
l_string|&quot;Redirecting IO7 interrupts to local CPU at PE %u&bslash;n&quot;
comma
id|cpuid
)paren
suffix:semicolon
multiline_comment|/* Redirect the error IRQS here.  */
id|io7_redirect_irq
c_func
(paren
id|io7
comma
op_amp
id|io7-&gt;csrs-&gt;HLT_CTL.csr
comma
id|cpuid
)paren
suffix:semicolon
id|io7_redirect_irq
c_func
(paren
id|io7
comma
op_amp
id|io7-&gt;csrs-&gt;HPI_CTL.csr
comma
id|cpuid
)paren
suffix:semicolon
id|io7_redirect_irq
c_func
(paren
id|io7
comma
op_amp
id|io7-&gt;csrs-&gt;CRD_CTL.csr
comma
id|cpuid
)paren
suffix:semicolon
id|io7_redirect_irq
c_func
(paren
id|io7
comma
op_amp
id|io7-&gt;csrs-&gt;STV_CTL.csr
comma
id|cpuid
)paren
suffix:semicolon
id|io7_redirect_irq
c_func
(paren
id|io7
comma
op_amp
id|io7-&gt;csrs-&gt;HEI_CTL.csr
comma
id|cpuid
)paren
suffix:semicolon
multiline_comment|/* Redirect the implemented LSIs here.  */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|0x60
suffix:semicolon
op_increment
id|i
)paren
id|io7_redirect_one_lsi
c_func
(paren
id|io7
comma
id|i
comma
id|cpuid
)paren
suffix:semicolon
id|io7_redirect_one_lsi
c_func
(paren
id|io7
comma
l_int|0x74
comma
id|cpuid
)paren
suffix:semicolon
id|io7_redirect_one_lsi
c_func
(paren
id|io7
comma
l_int|0x75
comma
id|cpuid
)paren
suffix:semicolon
multiline_comment|/* Redirect the MSIs here.  */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
op_increment
id|i
)paren
id|io7_redirect_one_msi
c_func
(paren
id|io7
comma
id|i
comma
id|cpuid
)paren
suffix:semicolon
)brace
"&f;"
multiline_comment|/*&n; * System Vectors&n; */
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|marvel_ev7_mv
id|__initmv
op_assign
(brace
dot
id|vector_name
op_assign
l_string|&quot;MARVEL/EV7&quot;
comma
id|DO_EV7_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_MARVEL_IO
comma
id|DO_MARVEL_BUS
comma
dot
id|machine_check
op_assign
id|marvel_machine_check
comma
dot
id|max_isa_dma_address
op_assign
id|ALPHA_MAX_ISA_DMA_ADDRESS
comma
dot
id|min_io_address
op_assign
id|DEFAULT_IO_BASE
comma
dot
id|min_mem_address
op_assign
id|DEFAULT_MEM_BASE
comma
dot
id|pci_dac_offset
op_assign
id|IO7_DAC_OFFSET
comma
dot
id|nr_irqs
op_assign
id|MARVEL_NR_IRQS
comma
dot
id|device_interrupt
op_assign
id|io7_device_interrupt
comma
dot
id|agp_info
op_assign
id|marvel_agp_info
comma
dot
id|smp_callin
op_assign
id|marvel_smp_callin
comma
dot
id|init_arch
op_assign
id|marvel_init_arch
comma
dot
id|init_irq
op_assign
id|marvel_init_irq
comma
dot
id|init_rtc
op_assign
id|marvel_init_rtc
comma
dot
id|init_pci
op_assign
id|marvel_init_pci
comma
dot
id|kill_arch
op_assign
id|marvel_kill_arch
comma
dot
id|pci_map_irq
op_assign
id|marvel_map_irq
comma
dot
id|pci_swizzle
op_assign
id|common_swizzle
comma
dot
id|pa_to_nid
op_assign
id|marvel_pa_to_nid
comma
dot
id|cpuid_to_nid
op_assign
id|marvel_cpuid_to_nid
comma
dot
id|node_mem_start
op_assign
id|marvel_node_mem_start
comma
dot
id|node_mem_size
op_assign
id|marvel_node_mem_size
comma
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|marvel_ev7
)paren
eof
