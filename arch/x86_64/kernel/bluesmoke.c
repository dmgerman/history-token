multiline_comment|/*&n; * Machine check handler.&n; * K8 parts Copyright 2002,2003 Andi Kleen, SuSE Labs.&n; * Rest from unknown author(s). &n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;asm/processor.h&gt; 
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/kdebug.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
DECL|variable|__initdata
r_static
r_int
id|mce_disabled
id|__initdata
suffix:semicolon
DECL|variable|mce_cpus
r_static
r_int
r_int
id|mce_cpus
suffix:semicolon
multiline_comment|/*&n; *&t;Machine Check Handler For PII/PIII/K7&n; */
DECL|variable|banks
r_static
r_int
id|banks
suffix:semicolon
DECL|variable|ignored_banks
DECL|variable|disabled_banks
r_static
r_int
r_int
id|ignored_banks
comma
id|disabled_banks
suffix:semicolon
multiline_comment|/* Machine Check on everything dubious. This is a good setting&n;   for device driver testing. */
DECL|macro|K8_DRIVER_DEBUG
mdefine_line|#define K8_DRIVER_DEBUG ((1&lt;&lt;13)-1)
multiline_comment|/* Report RAM errors and Hyper Transport Problems, but ignore Device&n;   aborts and GART errors. */
DECL|macro|K8_NORMAL_OP
mdefine_line|#define K8_NORMAL_OP    0xff
macro_line|#ifdef CONFIG_MCE_DEBUG
DECL|variable|__initdata
r_static
id|u32
id|k8_nb_flags
id|__initdata
op_assign
id|K8_DRIVER_DEBUG
suffix:semicolon
macro_line|#else
DECL|variable|__initdata
r_static
id|u32
id|k8_nb_flags
id|__initdata
op_assign
id|K8_NORMAL_OP
suffix:semicolon
macro_line|#endif
DECL|function|generic_machine_check
r_static
r_void
id|generic_machine_check
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|error_code
)paren
(brace
r_int
id|recover
op_assign
l_int|1
suffix:semicolon
id|u32
id|alow
comma
id|ahigh
comma
id|high
comma
id|low
suffix:semicolon
id|u32
id|mcgstl
comma
id|mcgsth
suffix:semicolon
r_int
id|i
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_MCG_STATUS
comma
id|mcgstl
comma
id|mcgsth
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mcgstl
op_amp
(paren
l_int|1
op_lshift
l_int|0
)paren
)paren
(brace
multiline_comment|/* Recoverable ? */
id|recover
op_assign
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;CPU %d: Machine Check Exception: %08x%08x&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|mcgsth
comma
id|mcgstl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regs
op_logical_and
(paren
id|mcgstl
op_amp
l_int|2
)paren
)paren
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;RIP &lt;%02lx&gt;:%016lx RSP %016lx&bslash;n&quot;
comma
id|regs-&gt;cs
comma
id|regs-&gt;rip
comma
id|regs-&gt;rsp
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
id|banks
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
l_int|1UL
op_lshift
id|i
)paren
op_amp
id|ignored_banks
)paren
r_continue
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_MC0_STATUS
op_plus
id|i
op_star
l_int|4
comma
id|low
comma
id|high
)paren
suffix:semicolon
r_if
c_cond
(paren
id|high
op_amp
(paren
l_int|1
op_lshift
l_int|31
)paren
)paren
(brace
r_if
c_cond
(paren
id|high
op_amp
(paren
l_int|1
op_lshift
l_int|29
)paren
)paren
(brace
id|recover
op_or_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|high
op_amp
(paren
l_int|1
op_lshift
l_int|25
)paren
)paren
(brace
id|recover
op_or_assign
l_int|2
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Bank %d: %08x%08x&quot;
comma
id|i
comma
id|high
comma
id|low
)paren
suffix:semicolon
id|high
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|31
)paren
suffix:semicolon
r_if
c_cond
(paren
id|high
op_amp
(paren
l_int|1
op_lshift
l_int|27
)paren
)paren
(brace
id|rdmsr
c_func
(paren
id|MSR_IA32_MC0_MISC
op_plus
id|i
op_star
l_int|4
comma
id|alow
comma
id|ahigh
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;[%08x%08x]&quot;
comma
id|alow
comma
id|ahigh
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|high
op_amp
(paren
l_int|1
op_lshift
l_int|26
)paren
)paren
(brace
id|rdmsr
c_func
(paren
id|MSR_IA32_MC0_ADDR
op_plus
id|i
op_star
l_int|4
comma
id|alow
comma
id|ahigh
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; at %08x%08x&quot;
comma
id|ahigh
comma
id|alow
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Clear it */
id|wrmsr
c_func
(paren
id|MSR_IA32_MC0_STATUS
op_plus
id|i
op_star
l_int|4
comma
l_int|0UL
comma
l_int|0UL
)paren
suffix:semicolon
multiline_comment|/* Serialize */
id|wmb
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|recover
op_amp
l_int|2
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;CPU context corrupt&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|recover
op_amp
l_int|1
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Unable to continue&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Attempting to continue.&bslash;n&quot;
)paren
suffix:semicolon
id|mcgstl
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|2
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_IA32_MCG_STATUS
comma
id|mcgstl
comma
id|mcgsth
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|unexpected_machine_check
r_static
r_void
id|unexpected_machine_check
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|error_code
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unexpected machine check %lx&bslash;n&quot;
comma
id|error_code
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Call the installed machine check handler for this CPU setup.&n; */
DECL|variable|machine_check_vector
r_static
r_void
(paren
op_star
id|machine_check_vector
)paren
(paren
r_struct
id|pt_regs
op_star
comma
r_int
id|error_code
)paren
op_assign
id|unexpected_machine_check
suffix:semicolon
DECL|function|do_machine_check
r_void
id|do_machine_check
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|error_code
)paren
(brace
id|notify_die
c_func
(paren
id|DIE_NMI
comma
l_string|&quot;machine check&quot;
comma
id|regs
comma
id|error_code
comma
l_int|255
comma
id|SIGKILL
)paren
suffix:semicolon
id|machine_check_vector
c_func
(paren
id|regs
comma
id|error_code
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;K8 machine check.&n; */
DECL|function|find_k8_nb
r_static
r_struct
id|pci_dev
op_star
id|find_k8_nb
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_AMD
comma
l_int|0x1103
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_eq
l_int|0
op_logical_and
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_eq
(paren
l_int|24U
op_plus
id|cpu
)paren
)paren
r_return
id|dev
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* When we have kallsyms we can afford kmcedecode too. */
DECL|variable|transaction
r_static
r_char
op_star
id|transaction
(braket
)braket
op_assign
(brace
l_string|&quot;instruction&quot;
comma
l_string|&quot;data&quot;
comma
l_string|&quot;generic&quot;
comma
l_string|&quot;reserved&quot;
)brace
suffix:semicolon
DECL|variable|cachelevel
r_static
r_char
op_star
id|cachelevel
(braket
)braket
op_assign
(brace
l_string|&quot;level 0&quot;
comma
l_string|&quot;level 1&quot;
comma
l_string|&quot;level 2&quot;
comma
l_string|&quot;level generic&quot;
)brace
suffix:semicolon
DECL|variable|memtrans
r_static
r_char
op_star
id|memtrans
(braket
)braket
op_assign
(brace
l_string|&quot;generic error&quot;
comma
l_string|&quot;generic read&quot;
comma
l_string|&quot;generic write&quot;
comma
l_string|&quot;data read&quot;
comma
l_string|&quot;data write&quot;
comma
l_string|&quot;instruction fetch&quot;
comma
l_string|&quot;prefetch&quot;
comma
l_string|&quot;snoop&quot;
comma
l_string|&quot;?&quot;
comma
l_string|&quot;?&quot;
comma
l_string|&quot;?&quot;
comma
l_string|&quot;?&quot;
comma
l_string|&quot;?&quot;
comma
l_string|&quot;?&quot;
comma
l_string|&quot;?&quot;
)brace
suffix:semicolon
DECL|variable|partproc
r_static
r_char
op_star
id|partproc
(braket
)braket
op_assign
(brace
l_string|&quot;local node origin&quot;
comma
l_string|&quot;local node response&quot;
comma
l_string|&quot;local node observed&quot;
comma
l_string|&quot;generic&quot;
)brace
suffix:semicolon
DECL|variable|timeout
r_static
r_char
op_star
id|timeout
(braket
)braket
op_assign
(brace
l_string|&quot;request didn&squot;t time out&quot;
comma
l_string|&quot;request timed out&quot;
)brace
suffix:semicolon
DECL|variable|memoryio
r_static
r_char
op_star
id|memoryio
(braket
)braket
op_assign
(brace
l_string|&quot;memory access&quot;
comma
l_string|&quot;res.&quot;
comma
l_string|&quot;i/o access&quot;
comma
l_string|&quot;generic&quot;
)brace
suffix:semicolon
DECL|variable|extendederr
r_static
r_char
op_star
id|extendederr
(braket
)braket
op_assign
(brace
l_string|&quot;ecc error&quot;
comma
l_string|&quot;crc error&quot;
comma
l_string|&quot;sync error&quot;
comma
l_string|&quot;mst abort&quot;
comma
l_string|&quot;tgt abort&quot;
comma
l_string|&quot;gart error&quot;
comma
l_string|&quot;rmw error&quot;
comma
l_string|&quot;wdog error&quot;
comma
l_string|&quot;chipkill ecc error&quot;
comma
l_string|&quot;&lt;9&gt;&quot;
comma
l_string|&quot;&lt;10&gt;&quot;
comma
l_string|&quot;&lt;11&gt;&quot;
comma
l_string|&quot;&lt;12&gt;&quot;
comma
l_string|&quot;&lt;13&gt;&quot;
comma
l_string|&quot;&lt;14&gt;&quot;
comma
l_string|&quot;&lt;15&gt;&quot;
)brace
suffix:semicolon
DECL|variable|highbits
r_static
r_char
op_star
id|highbits
(braket
l_int|32
)braket
op_assign
(brace
(braket
l_int|31
)braket
op_assign
l_string|&quot;previous error lost&quot;
comma
(braket
l_int|30
)braket
op_assign
l_string|&quot;error overflow&quot;
comma
(braket
l_int|29
)braket
op_assign
l_string|&quot;error uncorrected&quot;
comma
(braket
l_int|28
)braket
op_assign
l_string|&quot;error enable&quot;
comma
(braket
l_int|27
)braket
op_assign
l_string|&quot;misc error valid&quot;
comma
(braket
l_int|26
)braket
op_assign
l_string|&quot;error address valid&quot;
comma
(braket
l_int|25
)braket
op_assign
l_string|&quot;processor context corrupt&quot;
comma
(braket
l_int|24
)braket
op_assign
l_string|&quot;res24&quot;
comma
(braket
l_int|23
)braket
op_assign
l_string|&quot;res23&quot;
comma
multiline_comment|/* 22-15 ecc syndrome bits */
(braket
l_int|14
)braket
op_assign
l_string|&quot;corrected ecc error&quot;
comma
(braket
l_int|13
)braket
op_assign
l_string|&quot;uncorrected ecc error&quot;
comma
(braket
l_int|12
)braket
op_assign
l_string|&quot;res12&quot;
comma
(braket
l_int|11
)braket
op_assign
l_string|&quot;res11&quot;
comma
(braket
l_int|10
)braket
op_assign
l_string|&quot;res10&quot;
comma
(braket
l_int|9
)braket
op_assign
l_string|&quot;res9&quot;
comma
(braket
l_int|8
)braket
op_assign
l_string|&quot;dram scrub error&quot;
comma
(braket
l_int|7
)braket
op_assign
l_string|&quot;res7&quot;
comma
multiline_comment|/* 6-4 ht link number of error */
(braket
l_int|3
)braket
op_assign
l_string|&quot;res3&quot;
comma
(braket
l_int|2
)braket
op_assign
l_string|&quot;res2&quot;
comma
(braket
l_int|1
)braket
op_assign
l_string|&quot;err cpu0&quot;
comma
(braket
l_int|0
)braket
op_assign
l_string|&quot;err cpu1&quot;
comma
)brace
suffix:semicolon
DECL|function|check_k8_nb
r_static
r_void
id|check_k8_nb
c_func
(paren
r_int
id|header
)paren
(brace
r_struct
id|pci_dev
op_star
id|nb
suffix:semicolon
id|nb
op_assign
id|find_k8_nb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nb
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|u32
id|statuslow
comma
id|statushigh
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|nb
comma
l_int|0x48
comma
op_amp
id|statuslow
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|nb
comma
l_int|0x4c
comma
op_amp
id|statushigh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|statushigh
op_amp
(paren
l_int|1
op_lshift
l_int|31
)paren
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|header
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;CPU %d: Silent Northbridge MCE&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Northbridge status %08x%08x&bslash;n&quot;
comma
id|statushigh
comma
id|statuslow
)paren
suffix:semicolon
r_int
r_int
id|errcode
op_assign
id|statuslow
op_amp
l_int|0xffff
suffix:semicolon
r_switch
c_cond
(paren
id|errcode
op_rshift
l_int|8
)paren
(brace
r_case
l_int|0
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;    GART TLB error %s %s&bslash;n&quot;
comma
id|transaction
(braket
(paren
id|errcode
op_rshift
l_int|2
)paren
op_amp
l_int|3
)braket
comma
id|cachelevel
(braket
id|errcode
op_amp
l_int|3
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|errcode
op_amp
(paren
l_int|1
op_lshift
l_int|11
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;    bus error %s %s %s %s %s&bslash;n&quot;
comma
id|partproc
(braket
(paren
id|errcode
op_rshift
l_int|10
)paren
op_amp
l_int|0x3
)braket
comma
id|timeout
(braket
(paren
id|errcode
op_rshift
l_int|9
)paren
op_amp
l_int|1
)braket
comma
id|memtrans
(braket
(paren
id|errcode
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
)braket
comma
id|memoryio
(braket
(paren
id|errcode
op_rshift
l_int|2
)paren
op_amp
l_int|0x3
)braket
comma
id|cachelevel
(braket
(paren
id|errcode
op_amp
l_int|0x3
)paren
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|errcode
op_amp
(paren
l_int|1
op_lshift
l_int|8
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;    memory error %s %s %s&bslash;n&quot;
comma
id|memtrans
(braket
(paren
id|errcode
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
)braket
comma
id|transaction
(braket
(paren
id|errcode
op_rshift
l_int|2
)paren
op_amp
l_int|0x3
)braket
comma
id|cachelevel
(braket
(paren
id|errcode
op_amp
l_int|0x3
)paren
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;    unknown error code %x&bslash;n&quot;
comma
id|errcode
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|statushigh
op_amp
(paren
(paren
l_int|1
op_lshift
l_int|14
)paren
op_or
(paren
l_int|1
op_lshift
l_int|13
)paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;    ECC syndrome bits %x&bslash;n&quot;
comma
(paren
(paren
(paren
id|statuslow
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|statushigh
op_rshift
l_int|15
)paren
op_amp
l_int|0x7f
)paren
)paren
suffix:semicolon
id|errcode
op_assign
(paren
id|statuslow
op_rshift
l_int|16
)paren
op_amp
l_int|0xf
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;    extended error %s&bslash;n&quot;
comma
id|extendederr
(braket
(paren
id|statuslow
op_rshift
l_int|16
)paren
op_amp
l_int|0xf
)braket
)paren
suffix:semicolon
multiline_comment|/* should only print when it was a HyperTransport related error. */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;    link number %x&bslash;n&quot;
comma
(paren
id|statushigh
op_rshift
l_int|4
)paren
op_amp
l_int|3
)paren
suffix:semicolon
r_int
id|i
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
l_int|32
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|highbits
(braket
id|i
)braket
op_logical_and
(paren
id|statushigh
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;    %s&bslash;n&quot;
comma
id|highbits
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|statushigh
op_amp
(paren
l_int|1
op_lshift
l_int|26
)paren
)paren
(brace
id|u32
id|addrhigh
comma
id|addrlow
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|nb
comma
l_int|0x54
comma
op_amp
id|addrhigh
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|nb
comma
l_int|0x50
comma
op_amp
id|addrlow
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;    error address %08x%08x&bslash;n&quot;
comma
id|addrhigh
comma
id|addrlow
)paren
suffix:semicolon
)brace
id|statushigh
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|31
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|nb
comma
l_int|0x4c
comma
id|statushigh
)paren
suffix:semicolon
)brace
DECL|function|k8_machine_check
r_static
r_void
id|k8_machine_check
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|error_code
)paren
(brace
id|u64
id|status
comma
id|nbstatus
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|rdmsrl
c_func
(paren
id|MSR_IA32_MCG_STATUS
comma
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
(paren
l_int|1
op_lshift
l_int|2
)paren
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|regs
)paren
id|check_k8_nb
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;CPU %d: Machine Check Exception: %016Lx&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;MCG_STATUS: unrecoverable&bslash;n&quot;
)paren
suffix:semicolon
id|rdmsrl
c_func
(paren
id|MSR_IA32_MC0_STATUS
op_plus
l_int|4
op_star
l_int|4
comma
id|nbstatus
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nbstatus
op_amp
(paren
l_int|1UL
op_lshift
l_int|63
)paren
)paren
op_eq
l_int|0
)paren
r_goto
id|others
suffix:semicolon
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Northbridge Machine Check %s %016lx %lx&bslash;n&quot;
comma
id|regs
ques
c_cond
l_string|&quot;exception&quot;
suffix:colon
l_string|&quot;timer&quot;
comma
(paren
r_int
r_int
)paren
id|nbstatus
comma
id|error_code
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nbstatus
op_amp
(paren
l_int|1UL
op_lshift
l_int|62
)paren
)paren
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Lost at least one NB error condition&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nbstatus
op_amp
(paren
l_int|1UL
op_lshift
l_int|61
)paren
)paren
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Uncorrectable condition&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nbstatus
op_amp
(paren
l_int|1UL
OL
l_int|57
)paren
)paren
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Unrecoverable condition&bslash;n&quot;
)paren
suffix:semicolon
id|check_k8_nb
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nbstatus
op_amp
(paren
l_int|1UL
op_lshift
l_int|58
)paren
)paren
(brace
id|u64
id|adr
suffix:semicolon
id|rdmsrl
c_func
(paren
id|MSR_IA32_MC0_ADDR
op_plus
l_int|4
op_star
l_int|4
comma
id|adr
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Address: %016lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|adr
)paren
suffix:semicolon
)brace
id|wrmsrl
c_func
(paren
id|MSR_IA32_MC0_STATUS
op_plus
l_int|4
op_star
l_int|4
comma
l_int|0
)paren
suffix:semicolon
id|wrmsrl
c_func
(paren
id|MSR_IA32_MCG_STATUS
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regs
op_logical_and
(paren
id|status
op_amp
(paren
l_int|1
op_lshift
l_int|1
)paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;MCE at RIP %lx RSP %lx&bslash;n&quot;
comma
id|regs-&gt;rip
comma
id|regs-&gt;rsp
)paren
suffix:semicolon
id|others
suffix:colon
id|generic_machine_check
c_func
(paren
id|regs
comma
id|error_code
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|mcheck_timer
r_static
r_struct
id|timer_list
id|mcheck_timer
suffix:semicolon
DECL|variable|mcheck_interval
r_int
id|mcheck_interval
op_assign
l_int|30
op_star
id|HZ
suffix:semicolon
macro_line|#ifndef CONFIG_SMP 
DECL|function|mcheck_timer_handler
r_static
r_void
id|mcheck_timer_handler
c_func
(paren
r_int
r_int
id|data
)paren
(brace
id|k8_machine_check
c_func
(paren
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|mcheck_timer.expires
op_assign
id|jiffies
op_plus
id|mcheck_interval
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|mcheck_timer
)paren
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/* SMP needs a process context trampoline because smp_call_function cannot be &n;   called from interrupt context. */
DECL|function|mcheck_timer_other
r_static
r_void
id|mcheck_timer_other
c_func
(paren
r_void
op_star
id|data
)paren
(brace
id|k8_machine_check
c_func
(paren
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|mcheck_timer_dist
r_static
r_void
id|mcheck_timer_dist
c_func
(paren
r_void
op_star
id|data
)paren
(brace
id|smp_call_function
c_func
(paren
id|mcheck_timer_other
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|k8_machine_check
c_func
(paren
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|mcheck_timer.expires
op_assign
id|jiffies
op_plus
id|mcheck_interval
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|mcheck_timer
)paren
suffix:semicolon
)brace
DECL|function|mcheck_timer_handler
r_static
r_void
id|mcheck_timer_handler
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_static
id|DECLARE_WORK
c_func
(paren
id|mcheck_work
comma
id|mcheck_timer_dist
comma
l_int|NULL
)paren
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|mcheck_work
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|__initdata
r_static
r_int
id|nok8
id|__initdata
suffix:semicolon
DECL|function|k8_mcheck_init
r_static
r_void
id|__init
id|k8_mcheck_init
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
id|u64
id|cap
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|X86_FEATURE_MCE
comma
op_amp
id|c-&gt;x86_capability
)paren
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|X86_FEATURE_MCA
comma
op_amp
id|c-&gt;x86_capability
)paren
)paren
r_return
suffix:semicolon
id|rdmsrl
c_func
(paren
id|MSR_IA32_MCG_CAP
comma
id|cap
)paren
suffix:semicolon
id|banks
op_assign
id|cap
op_amp
l_int|0xff
suffix:semicolon
id|machine_check_vector
op_assign
id|k8_machine_check
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
id|banks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|u64
id|val
op_assign
(paren
(paren
l_int|1UL
op_lshift
id|i
)paren
op_amp
id|disabled_banks
)paren
ques
c_cond
l_int|0
suffix:colon
op_complement
l_int|0UL
suffix:semicolon
r_if
c_cond
(paren
id|val
op_logical_and
id|i
op_eq
l_int|4
)paren
id|val
op_assign
id|k8_nb_flags
suffix:semicolon
id|wrmsrl
c_func
(paren
id|MSR_IA32_MC0_CTL
op_plus
l_int|4
op_star
id|i
comma
id|val
)paren
suffix:semicolon
id|wrmsrl
c_func
(paren
id|MSR_IA32_MC0_STATUS
op_plus
l_int|4
op_star
id|i
comma
l_int|0
)paren
suffix:semicolon
)brace
id|set_in_cr4
c_func
(paren
id|X86_CR4_MCE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mcheck_interval
op_logical_and
(paren
id|smp_processor_id
c_func
(paren
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|init_timer
c_func
(paren
op_amp
id|mcheck_timer
)paren
suffix:semicolon
id|mcheck_timer.function
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
r_int
r_int
)paren
)paren
id|mcheck_timer_handler
suffix:semicolon
id|mcheck_timer.expires
op_assign
id|jiffies
op_plus
id|mcheck_interval
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|mcheck_timer
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Machine Check Reporting enabled for CPU#%d&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Set up machine check reporting for Intel processors&n; */
DECL|function|generic_mcheck_init
r_static
r_void
id|__init
id|generic_mcheck_init
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
id|u32
id|l
comma
id|h
suffix:semicolon
r_int
id|i
suffix:semicolon
r_static
r_int
id|done
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Check for MCE support&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|X86_FEATURE_MCE
comma
op_amp
id|c-&gt;x86_capability
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Check for PPro style MCA&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|X86_FEATURE_MCA
comma
op_amp
id|c-&gt;x86_capability
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Ok machine check is available */
id|machine_check_vector
op_assign
id|generic_machine_check
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|done
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Intel machine check architecture supported.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|rdmsr
c_func
(paren
id|MSR_IA32_MCG_CAP
comma
id|l
comma
id|h
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l
op_amp
(paren
l_int|1
op_lshift
l_int|8
)paren
)paren
(brace
id|wrmsr
c_func
(paren
id|MSR_IA32_MCG_CTL
comma
l_int|0xffffffff
comma
l_int|0xffffffff
)paren
suffix:semicolon
)brace
id|banks
op_assign
id|l
op_amp
l_int|0xff
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
id|banks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|u32
id|val
op_assign
(paren
(paren
l_int|1UL
op_lshift
id|i
)paren
op_amp
id|disabled_banks
)paren
ques
c_cond
l_int|0
suffix:colon
op_complement
l_int|0
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_IA32_MC0_CTL
op_plus
l_int|4
op_star
id|i
comma
id|val
comma
id|val
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_IA32_MC0_STATUS
op_plus
l_int|4
op_star
id|i
comma
l_int|0x0
comma
l_int|0x0
)paren
suffix:semicolon
)brace
id|set_in_cr4
c_func
(paren
id|X86_CR4_MCE
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Intel machine check reporting enabled on CPU#%d.&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|done
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This has to be run for each processor&n; */
DECL|function|mcheck_init
r_void
id|__init
id|mcheck_init
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
op_amp
id|mce_cpus
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|mce_disabled
op_eq
l_int|1
)paren
(brace
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|c-&gt;x86_vendor
)paren
(brace
r_case
id|X86_VENDOR_AMD
suffix:colon
r_if
c_cond
(paren
id|c-&gt;x86
op_eq
l_int|15
op_logical_and
op_logical_neg
id|nok8
)paren
(brace
id|k8_mcheck_init
c_func
(paren
id|c
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* FALL THROUGH */
r_default
suffix:colon
r_case
id|X86_VENDOR_INTEL
suffix:colon
id|generic_mcheck_init
c_func
(paren
id|c
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|mcheck_disable
r_static
r_int
id|__init
id|mcheck_disable
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|mce_disabled
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* mce=off disable machine check&n;   mce=nok8 disable k8 specific features&n;   mce=disable&lt;NUMBER&gt; disable bank NUMBER&n;   mce=enable&lt;NUMBER&gt; enable bank number&n;   mce=device&t;Enable device driver test reporting in NB&n;   mce=NUMBER mcheck timer interval number seconds. &n;   Can be also comma separated in a single mce= */
DECL|function|mcheck_enable
r_static
r_int
id|__init
id|mcheck_enable
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_while
c_loop
(paren
(paren
id|p
op_assign
id|strsep
c_func
(paren
op_amp
id|str
comma
l_string|&quot;,&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|isdigit
c_func
(paren
op_star
id|p
)paren
)paren
id|mcheck_interval
op_assign
id|simple_strtol
c_func
(paren
id|p
comma
l_int|NULL
comma
l_int|0
)paren
op_star
id|HZ
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|p
comma
l_string|&quot;off&quot;
)paren
)paren
id|mce_disabled
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|p
comma
l_string|&quot;enable&quot;
comma
l_int|6
)paren
)paren
id|disabled_banks
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|simple_strtol
c_func
(paren
id|p
op_plus
l_int|6
comma
l_int|NULL
comma
l_int|0
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|p
comma
l_string|&quot;disable&quot;
comma
l_int|7
)paren
)paren
id|disabled_banks
op_or_assign
op_complement
(paren
l_int|1
op_lshift
id|simple_strtol
c_func
(paren
id|p
op_plus
l_int|7
comma
l_int|NULL
comma
l_int|0
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|p
comma
l_string|&quot;nok8&quot;
)paren
)paren
id|nok8
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|p
comma
l_string|&quot;device&quot;
)paren
)paren
id|k8_nb_flags
op_assign
id|K8_DRIVER_DEBUG
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;nomce&quot;
comma
id|mcheck_disable
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;mce&quot;
comma
id|mcheck_enable
)paren
suffix:semicolon
eof
