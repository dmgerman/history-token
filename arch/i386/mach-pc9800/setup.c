multiline_comment|/*&n; *&t;Machine specific setup for pc9800&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/apm_bios.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/arch_hooks.h&gt;
DECL|struct|sys_desc_table_struct
r_struct
id|sys_desc_table_struct
(brace
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|member|table
r_int
r_char
id|table
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * pre_intr_init_hook - initialisation prior to setting up interrupt vectors&n; *&n; * Description:&n; *&t;Perform any necessary interrupt initialisation prior to setting up&n; *&t;the &quot;ordinary&quot; interrupt call gates.  For legacy reasons, the ISA&n; *&t;interrupts should be initialised here if the machine emulates a PC&n; *&t;in any way.&n; **/
DECL|function|pre_intr_init_hook
r_void
id|__init
id|pre_intr_init_hook
c_func
(paren
r_void
)paren
(brace
id|init_ISA_irqs
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * IRQ7 is cascade interrupt to second interrupt controller&n; */
DECL|variable|irq7
r_static
r_struct
id|irqaction
id|irq7
op_assign
(brace
id|no_action
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;cascade&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/**&n; * intr_init_hook - post gate setup interrupt initialisation&n; *&n; * Description:&n; *&t;Fill in any interrupts that may have been left out by the general&n; *&t;init_IRQ() routine.  interrupts having to do with the machine rather&n; *&t;than the devices on the I/O bus (like APIC interrupts in intel MP&n; *&t;systems) are started here.&n; **/
DECL|function|intr_init_hook
r_void
id|__init
id|intr_init_hook
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
id|apic_intr_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|setup_irq
c_func
(paren
l_int|7
comma
op_amp
id|irq7
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * pre_setup_arch_hook - hook called prior to any setup_arch() execution&n; *&n; * Description:&n; *&t;generally used to activate any machine specific identification&n; *&t;routines that may be needed before setup_arch() runs.  On VISWS&n; *&t;this is used to get the board revision and type.&n; **/
DECL|function|pre_setup_arch_hook
r_void
id|__init
id|pre_setup_arch_hook
c_func
(paren
r_void
)paren
(brace
id|SYS_DESC_TABLE.length
op_assign
l_int|0
suffix:semicolon
id|MCA_bus
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* In PC-9800, APM BIOS version is written in BCD...?? */
id|APM_BIOS_INFO.version
op_assign
(paren
id|APM_BIOS_INFO.version
op_amp
l_int|0xff00
)paren
op_or
(paren
(paren
id|APM_BIOS_INFO.version
op_amp
l_int|0x00f0
)paren
op_rshift
l_int|4
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * trap_init_hook - initialise system specific traps&n; *&n; * Description:&n; *&t;Called as the final act of trap_init().  Used in VISWS to initialise&n; *&t;the various board specific APIC traps.&n; **/
DECL|function|trap_init_hook
r_void
id|__init
id|trap_init_hook
c_func
(paren
r_void
)paren
(brace
)brace
DECL|variable|irq0
r_static
r_struct
id|irqaction
id|irq0
op_assign
(brace
id|timer_interrupt
comma
id|SA_INTERRUPT
comma
l_int|0
comma
l_string|&quot;timer&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/**&n; * time_init_hook - do any specific initialisations for the system timer.&n; *&n; * Description:&n; *&t;Must plug the system timer interrupt source at HZ into the IRQ listed&n; *&t;in irq_vectors.h:TIMER_IRQ&n; **/
DECL|function|time_init_hook
r_void
id|__init
id|time_init_hook
c_func
(paren
r_void
)paren
(brace
id|setup_irq
c_func
(paren
l_int|0
comma
op_amp
id|irq0
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MCA
multiline_comment|/**&n; * mca_nmi_hook - hook into MCA specific NMI chain&n; *&n; * Description:&n; *&t;The MCA (Microchannel Architecture) has an NMI chain for NMI sources&n; *&t;along the MCA bus.  Use this to hook into that chain if you will need&n; *&t;it.&n; **/
DECL|function|mca_nmi_hook
r_void
id|__init
id|mca_nmi_hook
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* If I recall correctly, there&squot;s a whole bunch of other things that&n;&t; * we can do to check for NMI problems, but that&squot;s all I know about&n;&t; * at the moment.&n;&t; */
id|printk
c_func
(paren
l_string|&quot;NMI generated from unknown source!&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
