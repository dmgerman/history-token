multiline_comment|/*&n; * bioscalls.c - the lowlevel layer of the PnPBIOS driver&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pnpbios.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/pnp.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &quot;pnpbios.h&quot;
r_static
r_struct
(brace
DECL|member|offset
id|u16
id|offset
suffix:semicolon
DECL|member|segment
id|u16
id|segment
suffix:semicolon
DECL|variable|pnp_bios_callpoint
)brace
id|pnp_bios_callpoint
suffix:semicolon
multiline_comment|/* The PnP BIOS entries in the GDT */
DECL|macro|PNP_GDT
mdefine_line|#define PNP_GDT    (GDT_ENTRY_PNPBIOS_BASE * 8)
DECL|macro|PNP_CS32
mdefine_line|#define PNP_CS32   (PNP_GDT+0x00)&t;/* segment for calling fn */
DECL|macro|PNP_CS16
mdefine_line|#define PNP_CS16   (PNP_GDT+0x08)&t;/* code segment for BIOS */
DECL|macro|PNP_DS
mdefine_line|#define PNP_DS     (PNP_GDT+0x10)&t;/* data segment for BIOS */
DECL|macro|PNP_TS1
mdefine_line|#define PNP_TS1    (PNP_GDT+0x18)&t;/* transfer data segment */
DECL|macro|PNP_TS2
mdefine_line|#define PNP_TS2    (PNP_GDT+0x20)&t;/* another data segment */
multiline_comment|/*&n; * These are some opcodes for a &quot;static asmlinkage&quot;&n; * As this code is *not* executed inside the linux kernel segment, but in a&n; * alias at offset 0, we need a far return that can not be compiled by&n; * default (please, prove me wrong! this is *really* ugly!)&n; * This is the only way to get the bios to return into the kernel code,&n; * because the bios code runs in 16 bit protected mode and therefore can only&n; * return to the caller if the call is within the first 64kB, and the linux&n; * kernel begins at offset 3GB...&n; */
id|asmlinkage
r_void
id|pnp_bios_callfunc
c_func
(paren
r_void
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;.text&t;&t;&t;&bslash;n&quot;
id|__ALIGN_STR
l_string|&quot;&bslash;n&quot;
l_string|&quot;pnp_bios_callfunc:&bslash;n&quot;
l_string|&quot;&t;pushl %edx&t;&bslash;n&quot;
l_string|&quot;&t;pushl %ecx&t;&bslash;n&quot;
l_string|&quot;&t;pushl %ebx&t;&bslash;n&quot;
l_string|&quot;&t;pushl %eax&t;&bslash;n&quot;
l_string|&quot;&t;lcallw *pnp_bios_callpoint&bslash;n&quot;
l_string|&quot;&t;addl $16, %esp&t;&bslash;n&quot;
l_string|&quot;&t;lret&t;&t;&bslash;n&quot;
l_string|&quot;.previous&t;&t;&bslash;n&quot;
)paren
suffix:semicolon
DECL|macro|Q_SET_SEL
mdefine_line|#define Q_SET_SEL(cpu, selname, address, size) &bslash;&n;do { &bslash;&n;set_base(cpu_gdt_table[cpu][(selname) &gt;&gt; 3], __va((u32)(address))); &bslash;&n;set_limit(cpu_gdt_table[cpu][(selname) &gt;&gt; 3], size); &bslash;&n;} while(0)
DECL|macro|Q2_SET_SEL
mdefine_line|#define Q2_SET_SEL(cpu, selname, address, size) &bslash;&n;do { &bslash;&n;set_base(cpu_gdt_table[cpu][(selname) &gt;&gt; 3], (u32)(address)); &bslash;&n;set_limit(cpu_gdt_table[cpu][(selname) &gt;&gt; 3], size); &bslash;&n;} while(0)
DECL|variable|bad_bios_desc
r_static
r_struct
id|desc_struct
id|bad_bios_desc
op_assign
(brace
l_int|0
comma
l_int|0x00409200
)brace
suffix:semicolon
multiline_comment|/*&n; * At some point we want to use this stack frame pointer to unwind&n; * after PnP BIOS oopses.&n; */
DECL|variable|pnp_bios_fault_esp
id|u32
id|pnp_bios_fault_esp
suffix:semicolon
DECL|variable|pnp_bios_fault_eip
id|u32
id|pnp_bios_fault_eip
suffix:semicolon
DECL|variable|pnp_bios_is_utter_crap
id|u32
id|pnp_bios_is_utter_crap
op_assign
l_int|0
suffix:semicolon
DECL|variable|pnp_bios_lock
r_static
id|spinlock_t
id|pnp_bios_lock
suffix:semicolon
multiline_comment|/*&n; * Support Functions&n; */
DECL|function|call_pnp_bios
r_static
r_inline
id|u16
id|call_pnp_bios
c_func
(paren
id|u16
id|func
comma
id|u16
id|arg1
comma
id|u16
id|arg2
comma
id|u16
id|arg3
comma
id|u16
id|arg4
comma
id|u16
id|arg5
comma
id|u16
id|arg6
comma
id|u16
id|arg7
comma
r_void
op_star
id|ts1_base
comma
id|u32
id|ts1_size
comma
r_void
op_star
id|ts2_base
comma
id|u32
id|ts2_size
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u16
id|status
suffix:semicolon
r_struct
id|desc_struct
id|save_desc_40
suffix:semicolon
r_int
id|cpu
suffix:semicolon
multiline_comment|/*&n;&t; * PnP BIOSes are generally not terribly re-entrant.&n;&t; * Also, don&squot;t rely on them to save everything correctly.&n;&t; */
r_if
c_cond
(paren
id|pnp_bios_is_utter_crap
)paren
(brace
r_return
id|PNP_FUNCTION_NOT_SUPPORTED
suffix:semicolon
)brace
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
id|save_desc_40
op_assign
id|cpu_gdt_table
(braket
id|cpu
)braket
(braket
l_int|0x40
op_div
l_int|8
)braket
suffix:semicolon
id|cpu_gdt_table
(braket
id|cpu
)braket
(braket
l_int|0x40
op_div
l_int|8
)braket
op_assign
id|bad_bios_desc
suffix:semicolon
multiline_comment|/* On some boxes IRQ&squot;s during PnP BIOS calls are deadly.  */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pnp_bios_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* The lock prevents us bouncing CPU here */
r_if
c_cond
(paren
id|ts1_size
)paren
id|Q2_SET_SEL
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|PNP_TS1
comma
id|ts1_base
comma
id|ts1_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ts2_size
)paren
id|Q2_SET_SEL
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|PNP_TS2
comma
id|ts2_base
comma
id|ts2_size
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;pushl %%ebp&bslash;n&bslash;t&quot;
l_string|&quot;pushl %%edi&bslash;n&bslash;t&quot;
l_string|&quot;pushl %%esi&bslash;n&bslash;t&quot;
l_string|&quot;pushl %%ds&bslash;n&bslash;t&quot;
l_string|&quot;pushl %%es&bslash;n&bslash;t&quot;
l_string|&quot;pushl %%fs&bslash;n&bslash;t&quot;
l_string|&quot;pushl %%gs&bslash;n&bslash;t&quot;
l_string|&quot;pushfl&bslash;n&bslash;t&quot;
l_string|&quot;movl %%esp, pnp_bios_fault_esp&bslash;n&bslash;t&quot;
l_string|&quot;movl $1f, pnp_bios_fault_eip&bslash;n&bslash;t&quot;
l_string|&quot;lcall %5,%6&bslash;n&bslash;t&quot;
l_string|&quot;1:popfl&bslash;n&bslash;t&quot;
l_string|&quot;popl %%gs&bslash;n&bslash;t&quot;
l_string|&quot;popl %%fs&bslash;n&bslash;t&quot;
l_string|&quot;popl %%es&bslash;n&bslash;t&quot;
l_string|&quot;popl %%ds&bslash;n&bslash;t&quot;
l_string|&quot;popl %%esi&bslash;n&bslash;t&quot;
l_string|&quot;popl %%edi&bslash;n&bslash;t&quot;
l_string|&quot;popl %%ebp&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|status
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
(paren
id|func
)paren
op_or
(paren
(paren
(paren
id|u32
)paren
id|arg1
)paren
op_lshift
l_int|16
)paren
)paren
comma
l_string|&quot;b&quot;
(paren
(paren
id|arg2
)paren
op_or
(paren
(paren
(paren
id|u32
)paren
id|arg3
)paren
op_lshift
l_int|16
)paren
)paren
comma
l_string|&quot;c&quot;
(paren
(paren
id|arg4
)paren
op_or
(paren
(paren
(paren
id|u32
)paren
id|arg5
)paren
op_lshift
l_int|16
)paren
)paren
comma
l_string|&quot;d&quot;
(paren
(paren
id|arg6
)paren
op_or
(paren
(paren
(paren
id|u32
)paren
id|arg7
)paren
op_lshift
l_int|16
)paren
)paren
comma
l_string|&quot;i&quot;
(paren
id|PNP_CS32
)paren
comma
l_string|&quot;i&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pnp_bios_lock
comma
id|flags
)paren
suffix:semicolon
id|cpu_gdt_table
(braket
id|cpu
)braket
(braket
l_int|0x40
op_div
l_int|8
)braket
op_assign
id|save_desc_40
suffix:semicolon
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* If we get here and this is set then the PnP BIOS faulted on us. */
r_if
c_cond
(paren
id|pnp_bios_is_utter_crap
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: Warning! Your PnP BIOS caused a fatal error. Attempting to continue&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: You may need to reboot with the &bslash;&quot;nobiospnp&bslash;&quot; option to operate stably&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: Check with your vendor for an updated BIOS&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
DECL|function|pnpbios_print_status
r_void
id|pnpbios_print_status
c_func
(paren
r_const
r_char
op_star
id|module
comma
id|u16
id|status
)paren
(brace
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|PNP_SUCCESS
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: %s: function successful&bslash;n&quot;
comma
id|module
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_NOT_SET_STATICALLY
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: %s: unable to set static resources&bslash;n&quot;
comma
id|module
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_UNKNOWN_FUNCTION
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: %s: invalid function number passed&bslash;n&quot;
comma
id|module
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_FUNCTION_NOT_SUPPORTED
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: %s: function not supported on this system&bslash;n&quot;
comma
id|module
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_INVALID_HANDLE
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: %s: invalid handle&bslash;n&quot;
comma
id|module
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_BAD_PARAMETER
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: %s: invalid parameters were passed&bslash;n&quot;
comma
id|module
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_SET_FAILED
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: %s: unable to set resources&bslash;n&quot;
comma
id|module
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_EVENTS_NOT_PENDING
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: %s: no events are pending&bslash;n&quot;
comma
id|module
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_SYSTEM_NOT_DOCKED
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: %s: the system is not docked&bslash;n&quot;
comma
id|module
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_NO_ISA_PNP_CARDS
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: %s: no isapnp cards are installed on this system&bslash;n&quot;
comma
id|module
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_UNABLE_TO_DETERMINE_DOCK_CAPABILITIES
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: %s: cannot determine the capabilities of the docking station&bslash;n&quot;
comma
id|module
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_CONFIG_CHANGE_FAILED_NO_BATTERY
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: %s: unable to undock, the system does not have a battery&bslash;n&quot;
comma
id|module
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_CONFIG_CHANGE_FAILED_RESOURCE_CONFLICT
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: %s: could not dock due to resource conflicts&bslash;n&quot;
comma
id|module
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_BUFFER_TOO_SMALL
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: %s: the buffer passed is too small&bslash;n&quot;
comma
id|module
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_USE_ESCD_SUPPORT
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: %s: use ESCD instead&bslash;n&quot;
comma
id|module
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_MESSAGE_NOT_SUPPORTED
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: %s: the message is unsupported&bslash;n&quot;
comma
id|module
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_HARDWARE_ERROR
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: %s: a hardware failure has occured&bslash;n&quot;
comma
id|module
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: %s: unexpected status 0x%x&bslash;n&quot;
comma
id|module
comma
id|status
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * PnP BIOS Low Level Calls&n; */
DECL|macro|PNP_GET_NUM_SYS_DEV_NODES
mdefine_line|#define PNP_GET_NUM_SYS_DEV_NODES&t;&t;0x00
DECL|macro|PNP_GET_SYS_DEV_NODE
mdefine_line|#define PNP_GET_SYS_DEV_NODE&t;&t;&t;0x01
DECL|macro|PNP_SET_SYS_DEV_NODE
mdefine_line|#define PNP_SET_SYS_DEV_NODE&t;&t;&t;0x02
DECL|macro|PNP_GET_EVENT
mdefine_line|#define PNP_GET_EVENT&t;&t;&t;&t;0x03
DECL|macro|PNP_SEND_MESSAGE
mdefine_line|#define PNP_SEND_MESSAGE&t;&t;&t;0x04
DECL|macro|PNP_GET_DOCKING_STATION_INFORMATION
mdefine_line|#define PNP_GET_DOCKING_STATION_INFORMATION&t;0x05
DECL|macro|PNP_SET_STATIC_ALLOCED_RES_INFO
mdefine_line|#define PNP_SET_STATIC_ALLOCED_RES_INFO&t;&t;0x09
DECL|macro|PNP_GET_STATIC_ALLOCED_RES_INFO
mdefine_line|#define PNP_GET_STATIC_ALLOCED_RES_INFO&t;&t;0x0a
DECL|macro|PNP_GET_APM_ID_TABLE
mdefine_line|#define PNP_GET_APM_ID_TABLE&t;&t;&t;0x0b
DECL|macro|PNP_GET_PNP_ISA_CONFIG_STRUC
mdefine_line|#define PNP_GET_PNP_ISA_CONFIG_STRUC&t;&t;0x40
DECL|macro|PNP_GET_ESCD_INFO
mdefine_line|#define PNP_GET_ESCD_INFO&t;&t;&t;0x41
DECL|macro|PNP_READ_ESCD
mdefine_line|#define PNP_READ_ESCD&t;&t;&t;&t;0x42
DECL|macro|PNP_WRITE_ESCD
mdefine_line|#define PNP_WRITE_ESCD&t;&t;&t;&t;0x43
multiline_comment|/*&n; * Call PnP BIOS with function 0x00, &quot;get number of system device nodes&quot;&n; */
DECL|function|__pnp_bios_dev_node_info
r_static
r_int
id|__pnp_bios_dev_node_info
c_func
(paren
r_struct
id|pnp_dev_node_info
op_star
id|data
)paren
(brace
id|u16
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_bios_present
c_func
(paren
)paren
)paren
r_return
id|PNP_FUNCTION_NOT_SUPPORTED
suffix:semicolon
id|status
op_assign
id|call_pnp_bios
c_func
(paren
id|PNP_GET_NUM_SYS_DEV_NODES
comma
l_int|0
comma
id|PNP_TS1
comma
l_int|2
comma
id|PNP_TS1
comma
id|PNP_DS
comma
l_int|0
comma
l_int|0
comma
id|data
comma
r_sizeof
(paren
r_struct
id|pnp_dev_node_info
)paren
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|data-&gt;no_nodes
op_and_assign
l_int|0xff
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|pnp_bios_dev_node_info
r_int
id|pnp_bios_dev_node_info
c_func
(paren
r_struct
id|pnp_dev_node_info
op_star
id|data
)paren
(brace
r_int
id|status
op_assign
id|__pnp_bios_dev_node_info
c_func
(paren
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
id|pnpbios_print_status
c_func
(paren
l_string|&quot;dev_node_info&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * Note that some PnP BIOSes (e.g., on Sony Vaio laptops) die a horrible&n; * death if they are asked to access the &quot;current&quot; configuration.&n; * Therefore, if it&squot;s a matter of indifference, it&squot;s better to call&n; * get_dev_node() and set_dev_node() with boot=1 rather than with boot=0.&n; */
multiline_comment|/* &n; * Call PnP BIOS with function 0x01, &quot;get system device node&quot;&n; * Input: *nodenum = desired node,&n; *        boot = whether to get nonvolatile boot (!=0)&n; *               or volatile current (0) config&n; * Output: *nodenum=next node or 0xff if no more nodes&n; */
DECL|function|__pnp_bios_get_dev_node
r_static
r_int
id|__pnp_bios_get_dev_node
c_func
(paren
id|u8
op_star
id|nodenum
comma
r_char
id|boot
comma
r_struct
id|pnp_bios_node
op_star
id|data
)paren
(brace
id|u16
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_bios_present
c_func
(paren
)paren
)paren
r_return
id|PNP_FUNCTION_NOT_SUPPORTED
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|boot
op_logical_and
id|pnpbios_dont_use_current_config
)paren
r_return
id|PNP_FUNCTION_NOT_SUPPORTED
suffix:semicolon
id|status
op_assign
id|call_pnp_bios
c_func
(paren
id|PNP_GET_SYS_DEV_NODE
comma
l_int|0
comma
id|PNP_TS1
comma
l_int|0
comma
id|PNP_TS2
comma
id|boot
ques
c_cond
l_int|2
suffix:colon
l_int|1
comma
id|PNP_DS
comma
l_int|0
comma
id|nodenum
comma
r_sizeof
(paren
r_char
)paren
comma
id|data
comma
l_int|65536
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|pnp_bios_get_dev_node
r_int
id|pnp_bios_get_dev_node
c_func
(paren
id|u8
op_star
id|nodenum
comma
r_char
id|boot
comma
r_struct
id|pnp_bios_node
op_star
id|data
)paren
(brace
r_int
id|status
suffix:semicolon
id|status
op_assign
id|__pnp_bios_get_dev_node
c_func
(paren
id|nodenum
comma
id|boot
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
id|pnpbios_print_status
c_func
(paren
l_string|&quot;get_dev_node&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * Call PnP BIOS with function 0x02, &quot;set system device node&quot;&n; * Input: *nodenum = desired node, &n; *        boot = whether to set nonvolatile boot (!=0)&n; *               or volatile current (0) config&n; */
DECL|function|__pnp_bios_set_dev_node
r_static
r_int
id|__pnp_bios_set_dev_node
c_func
(paren
id|u8
id|nodenum
comma
r_char
id|boot
comma
r_struct
id|pnp_bios_node
op_star
id|data
)paren
(brace
id|u16
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_bios_present
c_func
(paren
)paren
)paren
r_return
id|PNP_FUNCTION_NOT_SUPPORTED
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|boot
op_logical_and
id|pnpbios_dont_use_current_config
)paren
r_return
id|PNP_FUNCTION_NOT_SUPPORTED
suffix:semicolon
id|status
op_assign
id|call_pnp_bios
c_func
(paren
id|PNP_SET_SYS_DEV_NODE
comma
id|nodenum
comma
l_int|0
comma
id|PNP_TS1
comma
id|boot
ques
c_cond
l_int|2
suffix:colon
l_int|1
comma
id|PNP_DS
comma
l_int|0
comma
l_int|0
comma
id|data
comma
l_int|65536
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|pnp_bios_set_dev_node
r_int
id|pnp_bios_set_dev_node
c_func
(paren
id|u8
id|nodenum
comma
r_char
id|boot
comma
r_struct
id|pnp_bios_node
op_star
id|data
)paren
(brace
r_int
id|status
suffix:semicolon
id|status
op_assign
id|__pnp_bios_set_dev_node
c_func
(paren
id|nodenum
comma
id|boot
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|pnpbios_print_status
c_func
(paren
l_string|&quot;set_dev_node&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|boot
)paren
(brace
multiline_comment|/* Update devlist */
id|status
op_assign
id|pnp_bios_get_dev_node
c_func
(paren
op_amp
id|nodenum
comma
id|boot
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
r_return
id|status
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
macro_line|#if needed
multiline_comment|/*&n; * Call PnP BIOS with function 0x03, &quot;get event&quot;&n; */
DECL|function|pnp_bios_get_event
r_static
r_int
id|pnp_bios_get_event
c_func
(paren
id|u16
op_star
id|event
)paren
(brace
id|u16
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_bios_present
c_func
(paren
)paren
)paren
r_return
id|PNP_FUNCTION_NOT_SUPPORTED
suffix:semicolon
id|status
op_assign
id|call_pnp_bios
c_func
(paren
id|PNP_GET_EVENT
comma
l_int|0
comma
id|PNP_TS1
comma
id|PNP_DS
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|event
comma
r_sizeof
(paren
id|u16
)paren
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if needed
multiline_comment|/*&n; * Call PnP BIOS with function 0x04, &quot;send message&quot;&n; */
DECL|function|pnp_bios_send_message
r_static
r_int
id|pnp_bios_send_message
c_func
(paren
id|u16
id|message
)paren
(brace
id|u16
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_bios_present
c_func
(paren
)paren
)paren
r_return
id|PNP_FUNCTION_NOT_SUPPORTED
suffix:semicolon
id|status
op_assign
id|call_pnp_bios
c_func
(paren
id|PNP_SEND_MESSAGE
comma
id|message
comma
id|PNP_DS
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Call PnP BIOS with function 0x05, &quot;get docking station information&quot;&n; */
DECL|function|pnp_bios_dock_station_info
r_int
id|pnp_bios_dock_station_info
c_func
(paren
r_struct
id|pnp_docking_station_info
op_star
id|data
)paren
(brace
id|u16
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_bios_present
c_func
(paren
)paren
)paren
r_return
id|PNP_FUNCTION_NOT_SUPPORTED
suffix:semicolon
id|status
op_assign
id|call_pnp_bios
c_func
(paren
id|PNP_GET_DOCKING_STATION_INFORMATION
comma
l_int|0
comma
id|PNP_TS1
comma
id|PNP_DS
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|data
comma
r_sizeof
(paren
r_struct
id|pnp_docking_station_info
)paren
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
macro_line|#if needed
multiline_comment|/*&n; * Call PnP BIOS with function 0x09, &quot;set statically allocated resource&n; * information&quot;&n; */
DECL|function|pnp_bios_set_stat_res
r_static
r_int
id|pnp_bios_set_stat_res
c_func
(paren
r_char
op_star
id|info
)paren
(brace
id|u16
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_bios_present
c_func
(paren
)paren
)paren
r_return
id|PNP_FUNCTION_NOT_SUPPORTED
suffix:semicolon
id|status
op_assign
id|call_pnp_bios
c_func
(paren
id|PNP_SET_STATIC_ALLOCED_RES_INFO
comma
l_int|0
comma
id|PNP_TS1
comma
id|PNP_DS
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|info
comma
op_star
(paren
(paren
id|u16
op_star
)paren
id|info
)paren
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Call PnP BIOS with function 0x0a, &quot;get statically allocated resource&n; * information&quot;&n; */
DECL|function|__pnp_bios_get_stat_res
r_static
r_int
id|__pnp_bios_get_stat_res
c_func
(paren
r_char
op_star
id|info
)paren
(brace
id|u16
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_bios_present
c_func
(paren
)paren
)paren
r_return
id|PNP_FUNCTION_NOT_SUPPORTED
suffix:semicolon
id|status
op_assign
id|call_pnp_bios
c_func
(paren
id|PNP_GET_STATIC_ALLOCED_RES_INFO
comma
l_int|0
comma
id|PNP_TS1
comma
id|PNP_DS
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|info
comma
l_int|65536
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|pnp_bios_get_stat_res
r_int
id|pnp_bios_get_stat_res
c_func
(paren
r_char
op_star
id|info
)paren
(brace
r_int
id|status
suffix:semicolon
id|status
op_assign
id|__pnp_bios_get_stat_res
c_func
(paren
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
id|pnpbios_print_status
c_func
(paren
l_string|&quot;get_stat_res&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
macro_line|#if needed
multiline_comment|/*&n; * Call PnP BIOS with function 0x0b, &quot;get APM id table&quot;&n; */
DECL|function|pnp_bios_apm_id_table
r_static
r_int
id|pnp_bios_apm_id_table
c_func
(paren
r_char
op_star
id|table
comma
id|u16
op_star
id|size
)paren
(brace
id|u16
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_bios_present
c_func
(paren
)paren
)paren
r_return
id|PNP_FUNCTION_NOT_SUPPORTED
suffix:semicolon
id|status
op_assign
id|call_pnp_bios
c_func
(paren
id|PNP_GET_APM_ID_TABLE
comma
l_int|0
comma
id|PNP_TS2
comma
l_int|0
comma
id|PNP_TS1
comma
id|PNP_DS
comma
l_int|0
comma
l_int|0
comma
id|table
comma
op_star
id|size
comma
id|size
comma
r_sizeof
(paren
id|u16
)paren
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Call PnP BIOS with function 0x40, &quot;get isa pnp configuration structure&quot;&n; */
DECL|function|__pnp_bios_isapnp_config
r_static
r_int
id|__pnp_bios_isapnp_config
c_func
(paren
r_struct
id|pnp_isa_config_struc
op_star
id|data
)paren
(brace
id|u16
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_bios_present
c_func
(paren
)paren
)paren
r_return
id|PNP_FUNCTION_NOT_SUPPORTED
suffix:semicolon
id|status
op_assign
id|call_pnp_bios
c_func
(paren
id|PNP_GET_PNP_ISA_CONFIG_STRUC
comma
l_int|0
comma
id|PNP_TS1
comma
id|PNP_DS
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|data
comma
r_sizeof
(paren
r_struct
id|pnp_isa_config_struc
)paren
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|pnp_bios_isapnp_config
r_int
id|pnp_bios_isapnp_config
c_func
(paren
r_struct
id|pnp_isa_config_struc
op_star
id|data
)paren
(brace
r_int
id|status
suffix:semicolon
id|status
op_assign
id|__pnp_bios_isapnp_config
c_func
(paren
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
id|pnpbios_print_status
c_func
(paren
l_string|&quot;isapnp_config&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * Call PnP BIOS with function 0x41, &quot;get ESCD info&quot;&n; */
DECL|function|__pnp_bios_escd_info
r_static
r_int
id|__pnp_bios_escd_info
c_func
(paren
r_struct
id|escd_info_struc
op_star
id|data
)paren
(brace
id|u16
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_bios_present
c_func
(paren
)paren
)paren
r_return
id|ESCD_FUNCTION_NOT_SUPPORTED
suffix:semicolon
id|status
op_assign
id|call_pnp_bios
c_func
(paren
id|PNP_GET_ESCD_INFO
comma
l_int|0
comma
id|PNP_TS1
comma
l_int|2
comma
id|PNP_TS1
comma
l_int|4
comma
id|PNP_TS1
comma
id|PNP_DS
comma
id|data
comma
r_sizeof
(paren
r_struct
id|escd_info_struc
)paren
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|pnp_bios_escd_info
r_int
id|pnp_bios_escd_info
c_func
(paren
r_struct
id|escd_info_struc
op_star
id|data
)paren
(brace
r_int
id|status
suffix:semicolon
id|status
op_assign
id|__pnp_bios_escd_info
c_func
(paren
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
id|pnpbios_print_status
c_func
(paren
l_string|&quot;escd_info&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * Call PnP BIOS function 0x42, &quot;read ESCD&quot;&n; * nvram_base is determined by calling escd_info&n; */
DECL|function|__pnp_bios_read_escd
r_static
r_int
id|__pnp_bios_read_escd
c_func
(paren
r_char
op_star
id|data
comma
id|u32
id|nvram_base
)paren
(brace
id|u16
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_bios_present
c_func
(paren
)paren
)paren
r_return
id|ESCD_FUNCTION_NOT_SUPPORTED
suffix:semicolon
id|status
op_assign
id|call_pnp_bios
c_func
(paren
id|PNP_READ_ESCD
comma
l_int|0
comma
id|PNP_TS1
comma
id|PNP_TS2
comma
id|PNP_DS
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|data
comma
l_int|65536
comma
id|__va
c_func
(paren
id|nvram_base
)paren
comma
l_int|65536
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|pnp_bios_read_escd
r_int
id|pnp_bios_read_escd
c_func
(paren
r_char
op_star
id|data
comma
id|u32
id|nvram_base
)paren
(brace
r_int
id|status
suffix:semicolon
id|status
op_assign
id|__pnp_bios_read_escd
c_func
(paren
id|data
comma
id|nvram_base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
id|pnpbios_print_status
c_func
(paren
l_string|&quot;read_escd&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
macro_line|#if needed
multiline_comment|/*&n; * Call PnP BIOS function 0x43, &quot;write ESCD&quot;&n; */
DECL|function|pnp_bios_write_escd
r_static
r_int
id|pnp_bios_write_escd
c_func
(paren
r_char
op_star
id|data
comma
id|u32
id|nvram_base
)paren
(brace
id|u16
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_bios_present
c_func
(paren
)paren
)paren
r_return
id|ESCD_FUNCTION_NOT_SUPPORTED
suffix:semicolon
id|status
op_assign
id|call_pnp_bios
c_func
(paren
id|PNP_WRITE_ESCD
comma
l_int|0
comma
id|PNP_TS1
comma
id|PNP_TS2
comma
id|PNP_DS
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|data
comma
l_int|65536
comma
id|__va
c_func
(paren
id|nvram_base
)paren
comma
l_int|65536
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Initialization&n; */
DECL|function|pnpbios_calls_init
r_void
id|pnpbios_calls_init
c_func
(paren
r_union
id|pnp_bios_install_struct
op_star
id|header
)paren
(brace
r_int
id|i
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|pnp_bios_lock
)paren
suffix:semicolon
id|pnp_bios_callpoint.offset
op_assign
id|header-&gt;fields.pm16offset
suffix:semicolon
id|pnp_bios_callpoint.segment
op_assign
id|PNP_CS16
suffix:semicolon
id|set_base
c_func
(paren
id|bad_bios_desc
comma
id|__va
c_func
(paren
(paren
r_int
r_int
)paren
l_int|0x40
op_lshift
l_int|4
)paren
)paren
suffix:semicolon
id|_set_limit
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|bad_bios_desc
comma
l_int|4095
op_minus
(paren
l_int|0x40
op_lshift
l_int|4
)paren
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
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|Q2_SET_SEL
c_func
(paren
id|i
comma
id|PNP_CS32
comma
op_amp
id|pnp_bios_callfunc
comma
l_int|64
op_star
l_int|1024
)paren
suffix:semicolon
id|Q_SET_SEL
c_func
(paren
id|i
comma
id|PNP_CS16
comma
id|header-&gt;fields.pm16cseg
comma
l_int|64
op_star
l_int|1024
)paren
suffix:semicolon
id|Q_SET_SEL
c_func
(paren
id|i
comma
id|PNP_DS
comma
id|header-&gt;fields.pm16dseg
comma
l_int|64
op_star
l_int|1024
)paren
suffix:semicolon
)brace
)brace
eof
