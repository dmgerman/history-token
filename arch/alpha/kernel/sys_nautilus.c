multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_nautilus.c&n; *&n; *&t;Copyright (C) 1995 David A Rusling&n; *&t;Copyright (C) 1998 Richard Henderson&n; *&t;Copyright (C) 1999 Alpha Processor, Inc.,&n; *&t;&t;(David Daniel, Stig Telfer, Soohoon Lee)&n; *&n; * Code supporting NAUTILUS systems.&n; *&n; *&n; * NAUTILUS has the following I/O features:&n; *&n; * a) Driven by AMD 751 aka IRONGATE (northbridge):&n; *     4 PCI slots&n; *     1 AGP slot&n; *&n; * b) Driven by ALI M1543C (southbridge)&n; *     2 ISA slots&n; *     2 IDE connectors&n; *     1 dual drive capable FDD controller&n; *     2 serial ports&n; *     1 ECP/EPP/SP parallel port&n; *     2 USB ports&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/core_irongate.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;err_impl.h&quot;
macro_line|#include &quot;irq_impl.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
macro_line|#include &quot;machvec_impl.h&quot;
r_static
r_void
id|__init
DECL|function|nautilus_init_irq
id|nautilus_init_irq
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|alpha_using_srm
)paren
(brace
id|alpha_mv.device_interrupt
op_assign
id|srm_device_interrupt
suffix:semicolon
)brace
id|init_i8259a_irqs
c_func
(paren
)paren
suffix:semicolon
id|common_init_isa_dma
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|nautilus_map_irq
id|nautilus_map_irq
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
multiline_comment|/* Preserve the IRQ set up by the console.  */
id|u8
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
id|irq
)paren
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
r_void
DECL|function|nautilus_kill_arch
id|nautilus_kill_arch
c_func
(paren
r_int
id|mode
)paren
(brace
r_struct
id|pci_bus
op_star
id|bus
op_assign
id|pci_isa_hose-&gt;bus
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|LINUX_REBOOT_CMD_RESTART
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|alpha_using_srm
)paren
(brace
id|u8
id|t8
suffix:semicolon
id|pci_bus_read_config_byte
c_func
(paren
id|bus
comma
l_int|0x38
comma
l_int|0x43
comma
op_amp
id|t8
)paren
suffix:semicolon
id|pci_bus_write_config_byte
c_func
(paren
id|bus
comma
l_int|0x38
comma
l_int|0x43
comma
id|t8
op_or
l_int|0x80
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|1
comma
l_int|0x92
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
l_int|0x92
)paren
suffix:semicolon
multiline_comment|/* NOTREACHED */
)brace
r_break
suffix:semicolon
r_case
id|LINUX_REBOOT_CMD_POWER_OFF
suffix:colon
(brace
id|u32
id|pmuport
suffix:semicolon
id|pci_bus_read_config_dword
c_func
(paren
id|bus
comma
l_int|0x88
comma
l_int|0x10
comma
op_amp
id|pmuport
)paren
suffix:semicolon
id|pmuport
op_and_assign
l_int|0xfffe
suffix:semicolon
id|outl
c_func
(paren
l_int|0xffff
comma
id|pmuport
)paren
suffix:semicolon
multiline_comment|/* clear pending events */
id|outw
c_func
(paren
l_int|0x2000
comma
id|pmuport
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* power off */
multiline_comment|/* NOTREACHED */
)brace
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* Perform analysis of a machine check that arrived from the system (NMI) */
r_static
r_void
DECL|function|naut_sys_machine_check
id|naut_sys_machine_check
c_func
(paren
r_int
r_int
id|vector
comma
r_int
r_int
id|la_ptr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PC %lx RA %lx&bslash;n&quot;
comma
id|regs-&gt;pc
comma
id|regs-&gt;r26
)paren
suffix:semicolon
id|irongate_pci_clr_err
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Machine checks can come from two sources - those on the CPU and those&n;   in the system.  They are analysed separately but all starts here.  */
r_void
DECL|function|nautilus_machine_check
id|nautilus_machine_check
c_func
(paren
r_int
r_int
id|vector
comma
r_int
r_int
id|la_ptr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_char
op_star
id|mchk_class
suffix:semicolon
multiline_comment|/* Now for some analysis.  Machine checks fall into two classes --&n;&t;   those picked up by the system, and those picked up by the CPU.&n;&t;   Add to that the two levels of severity - correctable or not.  */
r_if
c_cond
(paren
id|vector
op_eq
id|SCB_Q_SYSMCHK
op_logical_and
(paren
(paren
id|IRONGATE0-&gt;dramms
op_amp
l_int|0x300
)paren
op_eq
l_int|0x300
)paren
)paren
(brace
r_int
r_int
id|nmi_ctl
suffix:semicolon
multiline_comment|/* Clear ALI NMI */
id|nmi_ctl
op_assign
id|inb
c_func
(paren
l_int|0x61
)paren
suffix:semicolon
id|nmi_ctl
op_or_assign
l_int|0x0c
suffix:semicolon
id|outb
c_func
(paren
id|nmi_ctl
comma
l_int|0x61
)paren
suffix:semicolon
id|nmi_ctl
op_and_assign
op_complement
l_int|0x0c
suffix:semicolon
id|outb
c_func
(paren
id|nmi_ctl
comma
l_int|0x61
)paren
suffix:semicolon
multiline_comment|/* Write again clears error bits.  */
id|IRONGATE0-&gt;stat_cmd
op_assign
id|IRONGATE0-&gt;stat_cmd
op_amp
op_complement
l_int|0x100
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|IRONGATE0-&gt;stat_cmd
suffix:semicolon
multiline_comment|/* Write again clears error bits.  */
id|IRONGATE0-&gt;dramms
op_assign
id|IRONGATE0-&gt;dramms
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|IRONGATE0-&gt;dramms
suffix:semicolon
id|draina
c_func
(paren
)paren
suffix:semicolon
id|wrmces
c_func
(paren
l_int|0x7
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vector
op_eq
id|SCB_Q_SYSERR
)paren
id|mchk_class
op_assign
l_string|&quot;Correctable&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|vector
op_eq
id|SCB_Q_SYSMCHK
)paren
id|mchk_class
op_assign
l_string|&quot;Fatal&quot;
suffix:semicolon
r_else
(brace
id|ev6_machine_check
c_func
(paren
id|vector
comma
id|la_ptr
comma
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;NAUTILUS Machine check 0x%lx &quot;
l_string|&quot;[%s  System Machine Check (NMI)]&bslash;n&quot;
comma
id|vector
comma
id|mchk_class
)paren
suffix:semicolon
id|naut_sys_machine_check
c_func
(paren
id|vector
comma
id|la_ptr
comma
id|regs
)paren
suffix:semicolon
multiline_comment|/* Tell the PALcode to clear the machine check */
id|draina
c_func
(paren
)paren
suffix:semicolon
id|wrmces
c_func
(paren
l_int|0x7
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The System Vectors&n; */
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|nautilus_mv
id|__initmv
op_assign
(brace
dot
id|vector_name
op_assign
l_string|&quot;Nautilus&quot;
comma
id|DO_EV6_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_IRONGATE_IO
comma
id|DO_IRONGATE_BUS
comma
dot
id|machine_check
op_assign
id|nautilus_machine_check
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
id|IRONGATE_DEFAULT_MEM_BASE
comma
dot
id|nr_irqs
op_assign
l_int|16
comma
dot
id|device_interrupt
op_assign
id|isa_device_interrupt
comma
dot
id|init_arch
op_assign
id|irongate_init_arch
comma
dot
id|init_irq
op_assign
id|nautilus_init_irq
comma
dot
id|init_rtc
op_assign
id|common_init_rtc
comma
dot
id|init_pci
op_assign
id|common_init_pci
comma
dot
id|kill_arch
op_assign
id|nautilus_kill_arch
comma
dot
id|pci_map_irq
op_assign
id|nautilus_map_irq
comma
dot
id|pci_swizzle
op_assign
id|common_swizzle
comma
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|nautilus
)paren
eof
