multiline_comment|/* VISWS traps */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/debugreg.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/arch_hooks.h&gt;
macro_line|#ifdef CONFIG_X86_VISWS_APIC
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/cobalt.h&gt;
macro_line|#include &lt;asm/lithium.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_X86_VISWS_APIC
multiline_comment|/*&n; * On Rev 005 motherboards legacy device interrupt lines are wired directly&n; * to Lithium from the 307.  But the PROM leaves the interrupt type of each&n; * 307 logical device set appropriate for the 8259.  Later we&squot;ll actually use&n; * the 8259, but for now we have to flip the interrupt types to&n; * level triggered, active lo as required by Lithium.&n; */
DECL|macro|REG
mdefine_line|#define&t;REG&t;0x2e&t;/* The register to read/write */
DECL|macro|DEV
mdefine_line|#define&t;DEV&t;0x07&t;/* Register: Logical device select */
DECL|macro|VAL
mdefine_line|#define&t;VAL&t;0x2f&t;/* The value to read/write */
r_static
r_void
DECL|function|superio_outb
id|superio_outb
c_func
(paren
r_int
id|dev
comma
r_int
id|reg
comma
r_int
id|val
)paren
(brace
id|outb
c_func
(paren
id|DEV
comma
id|REG
)paren
suffix:semicolon
id|outb
c_func
(paren
id|dev
comma
id|VAL
)paren
suffix:semicolon
id|outb
c_func
(paren
id|reg
comma
id|REG
)paren
suffix:semicolon
id|outb
c_func
(paren
id|val
comma
id|VAL
)paren
suffix:semicolon
)brace
r_static
r_int
id|__attribute__
(paren
(paren
id|unused
)paren
)paren
DECL|function|superio_inb
id|superio_inb
c_func
(paren
r_int
id|dev
comma
r_int
id|reg
)paren
(brace
id|outb
c_func
(paren
id|DEV
comma
id|REG
)paren
suffix:semicolon
id|outb
c_func
(paren
id|dev
comma
id|VAL
)paren
suffix:semicolon
id|outb
c_func
(paren
id|reg
comma
id|REG
)paren
suffix:semicolon
r_return
id|inb
c_func
(paren
id|VAL
)paren
suffix:semicolon
)brace
DECL|macro|FLOP
mdefine_line|#define&t;FLOP&t;3&t;/* floppy logical device */
DECL|macro|PPORT
mdefine_line|#define&t;PPORT&t;4&t;/* parallel logical device */
DECL|macro|UART5
mdefine_line|#define&t;UART5&t;5&t;/* uart2 logical device (not wired up) */
DECL|macro|UART6
mdefine_line|#define&t;UART6&t;6&t;/* uart1 logical device (THIS is the serial port!) */
DECL|macro|IDEST
mdefine_line|#define&t;IDEST&t;0x70&t;/* int. destination (which 307 IRQ line) reg. */
DECL|macro|ITYPE
mdefine_line|#define&t;ITYPE&t;0x71&t;/* interrupt type register */
multiline_comment|/* interrupt type bits */
DECL|macro|LEVEL
mdefine_line|#define&t;LEVEL&t;0x01&t;/* bit 0, 0 == edge triggered */
DECL|macro|ACTHI
mdefine_line|#define&t;ACTHI&t;0x02&t;/* bit 1, 0 == active lo */
r_static
id|__init
r_void
DECL|function|superio_init
id|superio_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|visws_board_type
op_eq
id|VISWS_320
op_logical_and
id|visws_board_rev
op_eq
l_int|5
)paren
(brace
id|superio_outb
c_func
(paren
id|UART6
comma
id|IDEST
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* 0 means no intr propagated */
id|printk
c_func
(paren
l_string|&quot;SGI 320 rev 5: disabling 307 uart1 interrupt&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_static
id|__init
r_void
DECL|function|lithium_init
id|lithium_init
c_func
(paren
r_void
)paren
(brace
id|set_fixmap
c_func
(paren
id|FIX_LI_PCIA
comma
id|LI_PCI_A_PHYS
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Lithium PCI Bridge A, Bus Number: %d&bslash;n&quot;
comma
id|li_pcia_read16
c_func
(paren
id|LI_PCI_BUSNUM
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|set_fixmap
c_func
(paren
id|FIX_LI_PCIB
comma
id|LI_PCI_B_PHYS
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Lithium PCI Bridge B (PIIX4), Bus Number: %d&bslash;n&quot;
comma
id|li_pcib_read16
c_func
(paren
id|LI_PCI_BUSNUM
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* XXX blindly enables all interrupts */
id|li_pcia_write16
c_func
(paren
id|LI_PCI_INTEN
comma
l_int|0xffff
)paren
suffix:semicolon
id|li_pcib_write16
c_func
(paren
id|LI_PCI_INTEN
comma
l_int|0xffff
)paren
suffix:semicolon
)brace
r_static
id|__init
r_void
DECL|function|cobalt_init
id|cobalt_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * On normal SMP PC this is used only with SMP, but we have to&n;&t; * use it and set it up here to start the Cobalt clock&n;&t; */
id|set_fixmap
c_func
(paren
id|FIX_APIC_BASE
comma
id|APIC_DEFAULT_PHYS_BASE
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Local APIC ID %lx&bslash;n&quot;
comma
id|apic_read
c_func
(paren
id|APIC_ID
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Local APIC Version %lx&bslash;n&quot;
comma
id|apic_read
c_func
(paren
id|APIC_LVR
)paren
)paren
suffix:semicolon
id|set_fixmap
c_func
(paren
id|FIX_CO_CPU
comma
id|CO_CPU_PHYS
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Cobalt Revision %lx&bslash;n&quot;
comma
id|co_cpu_read
c_func
(paren
id|CO_CPU_REV
)paren
)paren
suffix:semicolon
id|set_fixmap
c_func
(paren
id|FIX_CO_APIC
comma
id|CO_APIC_PHYS
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Cobalt APIC ID %lx&bslash;n&quot;
comma
id|co_apic_read
c_func
(paren
id|CO_APIC_ID
)paren
)paren
suffix:semicolon
multiline_comment|/* Enable Cobalt APIC being careful to NOT change the ID! */
id|co_apic_write
c_func
(paren
id|CO_APIC_ID
comma
id|co_apic_read
c_func
(paren
id|CO_APIC_ID
)paren
op_or
id|CO_APIC_ENABLE
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Cobalt APIC enabled: ID reg %lx&bslash;n&quot;
comma
id|co_apic_read
c_func
(paren
id|CO_APIC_ID
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|trap_init_hook
r_void
id|__init
id|trap_init_hook
c_func
(paren
)paren
(brace
macro_line|#ifdef CONFIG_X86_VISWS_APIC
id|superio_init
c_func
(paren
)paren
suffix:semicolon
id|lithium_init
c_func
(paren
)paren
suffix:semicolon
id|cobalt_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
