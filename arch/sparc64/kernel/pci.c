multiline_comment|/* $Id: pci.c,v 1.39 2002/01/05 01:13:43 davem Exp $&n; * pci.c: UltraSparc PCI controller support.&n; *&n; * Copyright (C) 1997, 1998, 1999 David S. Miller (davem@redhat.com)&n; * Copyright (C) 1998, 1999 Eddie C. Dost   (ecd@skynet.be)&n; * Copyright (C) 1999 Jakub Jelinek   (jj@ultra.linux.cz)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/capability.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pbm.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/ebus.h&gt;
macro_line|#include &lt;asm/isa.h&gt;
DECL|variable|pci_memspace_mask
r_int
r_int
id|pci_memspace_mask
op_assign
l_int|0xffffffffUL
suffix:semicolon
macro_line|#ifndef CONFIG_PCI
multiline_comment|/* A &quot;nop&quot; PCI implementation. */
DECL|function|sys_pciconfig_read
id|asmlinkage
r_int
id|sys_pciconfig_read
c_func
(paren
r_int
r_int
id|bus
comma
r_int
r_int
id|dfn
comma
r_int
r_int
id|off
comma
r_int
r_int
id|len
comma
r_int
r_char
op_star
id|buf
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_pciconfig_write
id|asmlinkage
r_int
id|sys_pciconfig_write
c_func
(paren
r_int
r_int
id|bus
comma
r_int
r_int
id|dfn
comma
r_int
r_int
id|off
comma
r_int
r_int
id|len
comma
r_int
r_char
op_star
id|buf
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/* List of all PCI controllers found in the system. */
DECL|variable|pci_controller_lock
id|spinlock_t
id|pci_controller_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|pci_controller_root
r_struct
id|pci_controller_info
op_star
id|pci_controller_root
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Each PCI controller found gets a unique index. */
DECL|variable|pci_num_controllers
r_int
id|pci_num_controllers
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Given an 8-bit PCI bus number, this yields the&n; * controlling PBM module info.&n; *&n; * Some explanation is in order here.  The Linux APIs for&n; * the PCI subsystem require that the configuration space&n; * types are enough to signify PCI configuration space&n; * accesses correctly.  This gives us 8-bits for the bus&n; * number, however we have multiple PCI controllers on&n; * UltraSparc systems.&n; *&n; * So what we do is give the PCI busses under each controller&n; * a unique portion of the 8-bit PCI bus number space.&n; * Therefore one can obtain the controller from the bus&n; * number.  For example, say PSYCHO PBM-A a subordinate bus&n; * space of 0 to 4, and PBM-B has a space of 0 to 2.  PBM-A&n; * will use 0 to 4, and PBM-B will use 5 to 7.&n; */
DECL|variable|pci_bus2pbm
r_struct
id|pci_pbm_info
op_star
id|pci_bus2pbm
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|pci_highest_busnum
r_int
r_char
id|pci_highest_busnum
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* At boot time the user can give the kernel a command&n; * line option which controls if and how PCI devices&n; * are reordered at PCI bus probing time.&n; */
DECL|variable|pci_device_reorder
r_int
id|pci_device_reorder
op_assign
l_int|0
suffix:semicolon
DECL|variable|pci_poke_in_progress
r_volatile
r_int
id|pci_poke_in_progress
suffix:semicolon
DECL|variable|pci_poke_cpu
r_volatile
r_int
id|pci_poke_cpu
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|pci_poke_faulted
r_volatile
r_int
id|pci_poke_faulted
suffix:semicolon
DECL|variable|pci_poke_lock
r_static
id|spinlock_t
id|pci_poke_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|pci_config_read8
r_void
id|pci_config_read8
c_func
(paren
id|u8
op_star
id|addr
comma
id|u8
op_star
id|ret
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u8
id|byte
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pci_poke_lock
comma
id|flags
)paren
suffix:semicolon
id|pci_poke_cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|pci_poke_in_progress
op_assign
l_int|1
suffix:semicolon
id|pci_poke_faulted
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;membar #Sync&bslash;n&bslash;t&quot;
l_string|&quot;lduba [%1] %2, %0&bslash;n&bslash;t&quot;
l_string|&quot;membar #Sync&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|byte
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|pci_poke_in_progress
op_assign
l_int|0
suffix:semicolon
id|pci_poke_cpu
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_poke_faulted
)paren
op_star
id|ret
op_assign
id|byte
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pci_poke_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|pci_config_read16
r_void
id|pci_config_read16
c_func
(paren
id|u16
op_star
id|addr
comma
id|u16
op_star
id|ret
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u16
id|word
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pci_poke_lock
comma
id|flags
)paren
suffix:semicolon
id|pci_poke_cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|pci_poke_in_progress
op_assign
l_int|1
suffix:semicolon
id|pci_poke_faulted
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;membar #Sync&bslash;n&bslash;t&quot;
l_string|&quot;lduha [%1] %2, %0&bslash;n&bslash;t&quot;
l_string|&quot;membar #Sync&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|word
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|pci_poke_in_progress
op_assign
l_int|0
suffix:semicolon
id|pci_poke_cpu
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_poke_faulted
)paren
op_star
id|ret
op_assign
id|word
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pci_poke_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|pci_config_read32
r_void
id|pci_config_read32
c_func
(paren
id|u32
op_star
id|addr
comma
id|u32
op_star
id|ret
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u32
id|dword
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pci_poke_lock
comma
id|flags
)paren
suffix:semicolon
id|pci_poke_cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|pci_poke_in_progress
op_assign
l_int|1
suffix:semicolon
id|pci_poke_faulted
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;membar #Sync&bslash;n&bslash;t&quot;
l_string|&quot;lduwa [%1] %2, %0&bslash;n&bslash;t&quot;
l_string|&quot;membar #Sync&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dword
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|pci_poke_in_progress
op_assign
l_int|0
suffix:semicolon
id|pci_poke_cpu
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_poke_faulted
)paren
op_star
id|ret
op_assign
id|dword
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pci_poke_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|pci_config_write8
r_void
id|pci_config_write8
c_func
(paren
id|u8
op_star
id|addr
comma
id|u8
id|val
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pci_poke_lock
comma
id|flags
)paren
suffix:semicolon
id|pci_poke_cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|pci_poke_in_progress
op_assign
l_int|1
suffix:semicolon
id|pci_poke_faulted
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;membar #Sync&bslash;n&bslash;t&quot;
l_string|&quot;stba %0, [%1] %2&bslash;n&bslash;t&quot;
l_string|&quot;membar #Sync&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|pci_poke_in_progress
op_assign
l_int|0
suffix:semicolon
id|pci_poke_cpu
op_assign
op_minus
l_int|1
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pci_poke_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|pci_config_write16
r_void
id|pci_config_write16
c_func
(paren
id|u16
op_star
id|addr
comma
id|u16
id|val
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pci_poke_lock
comma
id|flags
)paren
suffix:semicolon
id|pci_poke_cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|pci_poke_in_progress
op_assign
l_int|1
suffix:semicolon
id|pci_poke_faulted
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;membar #Sync&bslash;n&bslash;t&quot;
l_string|&quot;stha %0, [%1] %2&bslash;n&bslash;t&quot;
l_string|&quot;membar #Sync&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|pci_poke_in_progress
op_assign
l_int|0
suffix:semicolon
id|pci_poke_cpu
op_assign
op_minus
l_int|1
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pci_poke_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|pci_config_write32
r_void
id|pci_config_write32
c_func
(paren
id|u32
op_star
id|addr
comma
id|u32
id|val
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pci_poke_lock
comma
id|flags
)paren
suffix:semicolon
id|pci_poke_cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|pci_poke_in_progress
op_assign
l_int|1
suffix:semicolon
id|pci_poke_faulted
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;membar #Sync&bslash;n&bslash;t&quot;
l_string|&quot;stwa %0, [%1] %2&bslash;n&bslash;t&quot;
l_string|&quot;membar #Sync&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|pci_poke_in_progress
op_assign
l_int|0
suffix:semicolon
id|pci_poke_cpu
op_assign
op_minus
l_int|1
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pci_poke_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Probe for all PCI controllers in the system. */
r_extern
r_void
id|sabre_init
c_func
(paren
r_int
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|psycho_init
c_func
(paren
r_int
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|schizo_init
c_func
(paren
r_int
comma
r_char
op_star
)paren
suffix:semicolon
r_static
r_struct
(brace
DECL|member|model_name
r_char
op_star
id|model_name
suffix:semicolon
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_int
comma
r_char
op_star
)paren
suffix:semicolon
DECL|variable|pci_controller_table
)brace
id|pci_controller_table
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;SUNW,sabre&quot;
comma
id|sabre_init
)brace
comma
(brace
l_string|&quot;pci108e,a000&quot;
comma
id|sabre_init
)brace
comma
(brace
l_string|&quot;pci108e,a001&quot;
comma
id|sabre_init
)brace
comma
(brace
l_string|&quot;SUNW,psycho&quot;
comma
id|psycho_init
)brace
comma
(brace
l_string|&quot;pci108e,8000&quot;
comma
id|psycho_init
)brace
comma
(brace
l_string|&quot;SUNW,schizo&quot;
comma
id|schizo_init
)brace
comma
(brace
l_string|&quot;pci108e,8001&quot;
comma
id|schizo_init
)brace
)brace
suffix:semicolon
DECL|macro|PCI_NUM_CONTROLLER_TYPES
mdefine_line|#define PCI_NUM_CONTROLLER_TYPES (sizeof(pci_controller_table) / &bslash;&n;&t;&t;&t;&t;  sizeof(pci_controller_table[0]))
DECL|function|pci_controller_init
r_static
r_void
id|pci_controller_init
c_func
(paren
r_char
op_star
id|model_name
comma
r_int
id|namelen
comma
r_int
id|node
)paren
(brace
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
id|PCI_NUM_CONTROLLER_TYPES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|model_name
comma
id|pci_controller_table
(braket
id|i
)braket
dot
id|model_name
comma
id|namelen
)paren
)paren
(brace
id|pci_controller_table
(braket
id|i
)braket
dot
id|init
c_func
(paren
id|node
comma
id|model_name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;PCI: Warning unknown controller, model name [%s]&bslash;n&quot;
comma
id|model_name
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI: Ignoring controller...&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|pci_is_controller
r_static
r_int
id|pci_is_controller
c_func
(paren
r_char
op_star
id|model_name
comma
r_int
id|namelen
comma
r_int
id|node
)paren
(brace
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
id|PCI_NUM_CONTROLLER_TYPES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|model_name
comma
id|pci_controller_table
(braket
id|i
)braket
dot
id|model_name
comma
id|namelen
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Is there some PCI controller in the system?  */
DECL|function|pcic_present
r_int
id|pcic_present
c_func
(paren
r_void
)paren
(brace
r_char
id|namebuf
(braket
l_int|16
)braket
suffix:semicolon
r_int
id|node
suffix:semicolon
id|node
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|node
op_assign
id|prom_searchsiblings
c_func
(paren
id|node
comma
l_string|&quot;pci&quot;
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_int
id|len
comma
id|ret
suffix:semicolon
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;model&quot;
comma
id|namebuf
comma
r_sizeof
(paren
id|namebuf
)paren
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
(brace
id|ret
op_assign
id|pci_is_controller
c_func
(paren
id|namebuf
comma
id|len
comma
id|node
)paren
suffix:semicolon
)brace
r_else
(brace
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;compatible&quot;
comma
id|namebuf
comma
r_sizeof
(paren
id|namebuf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
id|ret
op_assign
id|pci_is_controller
c_func
(paren
id|namebuf
comma
id|len
comma
id|node
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|node
op_assign
id|prom_getsibling
c_func
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Find each controller in the system, attach and initialize&n; * software state structure for each and link into the&n; * pci_controller_root.  Setup the controller enough such&n; * that bus scanning can be done.&n; */
DECL|function|pci_controller_probe
r_static
r_void
id|pci_controller_probe
c_func
(paren
r_void
)paren
(brace
r_char
id|namebuf
(braket
l_int|16
)braket
suffix:semicolon
r_int
id|node
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI: Probing for controllers.&bslash;n&quot;
)paren
suffix:semicolon
id|node
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|node
op_assign
id|prom_searchsiblings
c_func
(paren
id|node
comma
l_string|&quot;pci&quot;
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_int
id|len
suffix:semicolon
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;model&quot;
comma
id|namebuf
comma
r_sizeof
(paren
id|namebuf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
id|pci_controller_init
c_func
(paren
id|namebuf
comma
id|len
comma
id|node
)paren
suffix:semicolon
r_else
(brace
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;compatible&quot;
comma
id|namebuf
comma
r_sizeof
(paren
id|namebuf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
id|pci_controller_init
c_func
(paren
id|namebuf
comma
id|len
comma
id|node
)paren
suffix:semicolon
)brace
id|node
op_assign
id|prom_getsibling
c_func
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
r_break
suffix:semicolon
)brace
)brace
DECL|function|pci_scan_each_controller_bus
r_static
r_void
id|pci_scan_each_controller_bus
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller_info
op_star
id|p
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pci_controller_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|pci_controller_root
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
id|p
op_member_access_from_pointer
id|scan_bus
c_func
(paren
id|p
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pci_controller_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Reorder the pci_dev chain, so that onboard devices come first&n; * and then come the pluggable cards.&n; */
DECL|function|pci_reorder_devs
r_static
r_void
id|__init
id|pci_reorder_devs
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|pci_onboard
op_assign
op_amp
id|pci_devices
suffix:semicolon
r_struct
id|list_head
op_star
id|walk
op_assign
id|pci_onboard-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|walk
op_ne
id|pci_onboard
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
op_assign
id|pci_dev_g
c_func
(paren
id|walk
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|walk_next
op_assign
id|walk-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|pdev-&gt;irq
op_logical_and
(paren
id|__irq_ino
c_func
(paren
id|pdev-&gt;irq
)paren
op_amp
l_int|0x20
)paren
)paren
(brace
id|list_del
c_func
(paren
id|walk
)paren
suffix:semicolon
id|list_add
c_func
(paren
id|walk
comma
id|pci_onboard
)paren
suffix:semicolon
)brace
id|walk
op_assign
id|walk_next
suffix:semicolon
)brace
)brace
r_extern
r_void
id|clock_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|power_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|pcibios_init
r_static
r_int
id|__init
id|pcibios_init
c_func
(paren
r_void
)paren
(brace
id|pci_controller_probe
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_controller_root
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|pci_scan_each_controller_bus
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_device_reorder
)paren
id|pci_reorder_devs
c_func
(paren
)paren
suffix:semicolon
id|isa_init
c_func
(paren
)paren
suffix:semicolon
id|ebus_init
c_func
(paren
)paren
suffix:semicolon
id|clock_probe
c_func
(paren
)paren
suffix:semicolon
id|power_init
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pcibios_init
id|subsys_initcall
c_func
(paren
id|pcibios_init
)paren
suffix:semicolon
DECL|variable|pcibios_fixups
r_struct
id|pci_fixup
id|pcibios_fixups
(braket
)braket
op_assign
(brace
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|pcibios_fixup_bus
r_void
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|pbus
)paren
(brace
r_struct
id|pci_pbm_info
op_star
id|pbm
op_assign
id|pbus-&gt;sysdata
suffix:semicolon
multiline_comment|/* Generic PCI bus probing sets these to point at&n;&t; * &amp;io{port,mem}_resouce which is wrong for us.&n;&t; */
id|pbus-&gt;resource
(braket
l_int|0
)braket
op_assign
op_amp
id|pbm-&gt;io_space
suffix:semicolon
id|pbus-&gt;resource
(braket
l_int|1
)braket
op_assign
op_amp
id|pbm-&gt;mem_space
suffix:semicolon
)brace
multiline_comment|/* NOTE: This can get called before we&squot;ve fixed up pdev-&gt;sysdata. */
DECL|function|pci_claim_resource
r_int
id|pci_claim_resource
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_int
id|resource
)paren
(brace
r_struct
id|pci_pbm_info
op_star
id|pbm
op_assign
id|pci_bus2pbm
(braket
id|pdev-&gt;bus-&gt;number
)braket
suffix:semicolon
r_struct
id|resource
op_star
id|res
op_assign
op_amp
id|pdev-&gt;resource
(braket
id|resource
)braket
suffix:semicolon
r_struct
id|resource
op_star
id|root
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pbm
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
id|root
op_assign
op_amp
id|pbm-&gt;io_space
suffix:semicolon
r_else
id|root
op_assign
op_amp
id|pbm-&gt;mem_space
suffix:semicolon
id|pbm-&gt;parent
op_member_access_from_pointer
id|resource_adjust
c_func
(paren
id|pdev
comma
id|res
comma
id|root
)paren
suffix:semicolon
r_return
id|request_resource
c_func
(paren
id|root
comma
id|res
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Given the PCI bus a device resides on, try to&n; * find an acceptable resource allocation for a&n; * specific device resource..&n; */
DECL|function|pci_assign_bus_resource
r_static
r_int
id|pci_assign_bus_resource
c_func
(paren
r_const
r_struct
id|pci_bus
op_star
id|bus
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|resource
op_star
id|res
comma
r_int
r_int
id|size
comma
r_int
r_int
id|min
comma
r_int
id|resno
)paren
(brace
r_int
r_int
id|type_mask
suffix:semicolon
r_int
id|i
suffix:semicolon
id|type_mask
op_assign
id|IORESOURCE_IO
op_or
id|IORESOURCE_MEM
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|r
op_assign
id|bus-&gt;resource
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r
)paren
r_continue
suffix:semicolon
multiline_comment|/* type_mask must match */
r_if
c_cond
(paren
(paren
id|res-&gt;flags
op_xor
id|r-&gt;flags
)paren
op_amp
id|type_mask
)paren
r_continue
suffix:semicolon
multiline_comment|/* Ok, try it out.. */
r_if
c_cond
(paren
id|allocate_resource
c_func
(paren
id|r
comma
id|res
comma
id|size
comma
id|min
comma
op_minus
l_int|1
comma
id|size
comma
l_int|NULL
comma
l_int|NULL
)paren
OL
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/* PCI config space updated by caller.  */
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
DECL|function|pci_assign_resource
r_int
id|pci_assign_resource
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_int
id|resource
)paren
(brace
r_struct
id|pcidev_cookie
op_star
id|pcp
op_assign
id|pdev-&gt;sysdata
suffix:semicolon
r_struct
id|pci_pbm_info
op_star
id|pbm
op_assign
id|pcp-&gt;pbm
suffix:semicolon
r_struct
id|resource
op_star
id|res
op_assign
op_amp
id|pdev-&gt;resource
(braket
id|resource
)braket
suffix:semicolon
r_int
r_int
id|min
comma
id|size
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
id|min
op_assign
id|pbm-&gt;io_space.start
op_plus
l_int|0x400UL
suffix:semicolon
r_else
id|min
op_assign
id|pbm-&gt;mem_space.start
suffix:semicolon
id|size
op_assign
id|res-&gt;end
op_minus
id|res-&gt;start
op_plus
l_int|1
suffix:semicolon
id|err
op_assign
id|pci_assign_bus_resource
c_func
(paren
id|pdev-&gt;bus
comma
id|pdev
comma
id|res
comma
id|size
comma
id|min
comma
id|resource
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Failed to allocate resource %d for %s&bslash;n&quot;
comma
id|resource
comma
id|pdev-&gt;name
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Update PCI config space. */
id|pbm-&gt;parent
op_member_access_from_pointer
id|base_address_update
c_func
(paren
id|pdev
comma
id|resource
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|pcibios_update_resource
r_void
id|pcibios_update_resource
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_struct
id|resource
op_star
id|res1
comma
r_struct
id|resource
op_star
id|res2
comma
r_int
id|index
)paren
(brace
)brace
DECL|function|pcibios_update_irq
r_void
id|pcibios_update_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_int
id|irq
)paren
(brace
)brace
DECL|function|pcibios_fixup_pbus_ranges
r_void
id|__devinit
id|pcibios_fixup_pbus_ranges
c_func
(paren
r_struct
id|pci_bus
op_star
id|pbus
comma
r_struct
id|pbus_set_ranges_data
op_star
id|pranges
)paren
(brace
)brace
DECL|function|pcibios_align_resource
r_void
id|pcibios_align_resource
c_func
(paren
r_void
op_star
id|data
comma
r_struct
id|resource
op_star
id|res
comma
r_int
r_int
id|size
comma
r_int
r_int
id|align
)paren
(brace
)brace
DECL|function|pcibios_enable_device
r_int
id|pcibios_enable_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_int
id|mask
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pcibios_setup
r_char
op_star
id|__init
id|pcibios_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;onboardfirst&quot;
)paren
)paren
(brace
id|pci_device_reorder
op_assign
l_int|1
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;noreorder&quot;
)paren
)paren
(brace
id|pci_device_reorder
op_assign
l_int|0
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|str
suffix:semicolon
)brace
multiline_comment|/* Platform support for /proc/bus/pci/X/Y mmap()s. */
multiline_comment|/* If the user uses a host-bridge as the PCI device, he may use&n; * this to perform a raw mmap() of the I/O or MEM space behind&n; * that controller.&n; *&n; * This can be useful for execution of x86 PCI bios initialization code&n; * on a PCI card, like the xfree86 int10 stuff does.&n; */
DECL|function|__pci_mmap_make_offset_bus
r_static
r_int
id|__pci_mmap_make_offset_bus
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_enum
id|pci_mmap_state
id|mmap_state
)paren
(brace
r_struct
id|pcidev_cookie
op_star
id|pcp
op_assign
id|pdev-&gt;sysdata
suffix:semicolon
r_struct
id|pci_pbm_info
op_star
id|pbm
suffix:semicolon
r_struct
id|pci_controller_info
op_star
id|p
suffix:semicolon
r_int
r_int
id|space_size
comma
id|user_offset
comma
id|user_size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pcp
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|pbm
op_assign
id|pcp-&gt;pbm
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pbm
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|p
op_assign
id|pbm-&gt;parent
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;pbms_same_domain
)paren
(brace
r_int
r_int
id|lowest
comma
id|highest
suffix:semicolon
id|lowest
op_assign
op_complement
l_int|0UL
suffix:semicolon
id|highest
op_assign
l_int|0UL
suffix:semicolon
r_if
c_cond
(paren
id|mmap_state
op_eq
id|pci_mmap_io
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;pbm_A.io_space.flags
)paren
(brace
id|lowest
op_assign
id|p-&gt;pbm_A.io_space.start
suffix:semicolon
id|highest
op_assign
id|p-&gt;pbm_A.io_space.end
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;pbm_B.io_space.flags
)paren
(brace
r_if
c_cond
(paren
id|lowest
OG
id|p-&gt;pbm_B.io_space.start
)paren
id|lowest
op_assign
id|p-&gt;pbm_B.io_space.start
suffix:semicolon
r_if
c_cond
(paren
id|highest
OL
id|p-&gt;pbm_B.io_space.end
op_plus
l_int|1
)paren
id|highest
op_assign
id|p-&gt;pbm_B.io_space.end
op_plus
l_int|1
suffix:semicolon
)brace
id|space_size
op_assign
id|highest
op_minus
id|lowest
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|p-&gt;pbm_A.mem_space.flags
)paren
(brace
id|lowest
op_assign
id|p-&gt;pbm_A.mem_space.start
suffix:semicolon
id|highest
op_assign
id|p-&gt;pbm_A.mem_space.end
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;pbm_B.mem_space.flags
)paren
(brace
r_if
c_cond
(paren
id|lowest
OG
id|p-&gt;pbm_B.mem_space.start
)paren
id|lowest
op_assign
id|p-&gt;pbm_B.mem_space.start
suffix:semicolon
r_if
c_cond
(paren
id|highest
OL
id|p-&gt;pbm_B.mem_space.end
op_plus
l_int|1
)paren
id|highest
op_assign
id|p-&gt;pbm_B.mem_space.end
op_plus
l_int|1
suffix:semicolon
)brace
id|space_size
op_assign
id|highest
op_minus
id|lowest
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|mmap_state
op_eq
id|pci_mmap_io
)paren
(brace
id|space_size
op_assign
(paren
id|pbm-&gt;io_space.end
op_minus
id|pbm-&gt;io_space.start
)paren
op_plus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|space_size
op_assign
(paren
id|pbm-&gt;mem_space.end
op_minus
id|pbm-&gt;mem_space.start
)paren
op_plus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* Make sure the request is in range. */
id|user_offset
op_assign
id|vma-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|user_size
op_assign
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
suffix:semicolon
r_if
c_cond
(paren
id|user_offset
op_ge
id|space_size
op_logical_or
(paren
id|user_offset
op_plus
id|user_size
)paren
OG
id|space_size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;pbms_same_domain
)paren
(brace
r_int
r_int
id|lowest
op_assign
op_complement
l_int|0UL
suffix:semicolon
r_if
c_cond
(paren
id|mmap_state
op_eq
id|pci_mmap_io
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;pbm_A.io_space.flags
)paren
id|lowest
op_assign
id|p-&gt;pbm_A.io_space.start
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;pbm_B.io_space.flags
op_logical_and
id|lowest
OG
id|p-&gt;pbm_B.io_space.start
)paren
id|lowest
op_assign
id|p-&gt;pbm_B.io_space.start
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|p-&gt;pbm_A.mem_space.flags
)paren
id|lowest
op_assign
id|p-&gt;pbm_A.mem_space.start
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;pbm_B.mem_space.flags
op_logical_and
id|lowest
OG
id|p-&gt;pbm_B.mem_space.start
)paren
id|lowest
op_assign
id|p-&gt;pbm_B.mem_space.start
suffix:semicolon
)brace
id|vma-&gt;vm_pgoff
op_assign
(paren
id|lowest
op_plus
id|user_offset
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|mmap_state
op_eq
id|pci_mmap_io
)paren
(brace
id|vma-&gt;vm_pgoff
op_assign
(paren
id|pbm-&gt;io_space.start
op_plus
id|user_offset
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
)brace
r_else
(brace
id|vma-&gt;vm_pgoff
op_assign
(paren
id|pbm-&gt;mem_space.start
op_plus
id|user_offset
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Adjust vm_pgoff of VMA such that it is the physical page offset corresponding&n; * to the 32-bit pci bus offset for DEV requested by the user.&n; *&n; * Basically, the user finds the base address for his device which he wishes&n; * to mmap.  They read the 32-bit value from the config space base register,&n; * add whatever PAGE_SIZE multiple offset they wish, and feed this into the&n; * offset parameter of mmap on /proc/bus/pci/XXX for that device.&n; *&n; * Returns negative error code on failure, zero on success.&n; */
DECL|function|__pci_mmap_make_offset
r_static
r_int
id|__pci_mmap_make_offset
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_enum
id|pci_mmap_state
id|mmap_state
)paren
(brace
r_int
r_int
id|user_offset
op_assign
id|vma-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
suffix:semicolon
r_int
r_int
id|user32
op_assign
id|user_offset
op_amp
id|pci_memspace_mask
suffix:semicolon
r_int
r_int
id|largest_base
comma
id|this_base
comma
id|addr32
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_eq
id|PCI_CLASS_BRIDGE_HOST
)paren
r_return
id|__pci_mmap_make_offset_bus
c_func
(paren
id|dev
comma
id|vma
comma
id|mmap_state
)paren
suffix:semicolon
multiline_comment|/* Figure out which base address this is for. */
id|largest_base
op_assign
l_int|0UL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|PCI_ROM_RESOURCE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|rp
op_assign
op_amp
id|dev-&gt;resource
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/* Active? */
r_if
c_cond
(paren
op_logical_neg
id|rp-&gt;flags
)paren
r_continue
suffix:semicolon
multiline_comment|/* Same type? */
r_if
c_cond
(paren
id|i
op_eq
id|PCI_ROM_RESOURCE
)paren
(brace
r_if
c_cond
(paren
id|mmap_state
op_ne
id|pci_mmap_mem
)paren
r_continue
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|mmap_state
op_eq
id|pci_mmap_io
op_logical_and
(paren
id|rp-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
op_eq
l_int|0
)paren
op_logical_or
(paren
id|mmap_state
op_eq
id|pci_mmap_mem
op_logical_and
(paren
id|rp-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
op_eq
l_int|0
)paren
)paren
r_continue
suffix:semicolon
)brace
id|this_base
op_assign
id|rp-&gt;start
suffix:semicolon
id|addr32
op_assign
(paren
id|this_base
op_amp
id|PAGE_MASK
)paren
op_amp
id|pci_memspace_mask
suffix:semicolon
r_if
c_cond
(paren
id|mmap_state
op_eq
id|pci_mmap_io
)paren
id|addr32
op_and_assign
l_int|0xffffff
suffix:semicolon
r_if
c_cond
(paren
id|addr32
op_le
id|user32
op_logical_and
id|this_base
OG
id|largest_base
)paren
id|largest_base
op_assign
id|this_base
suffix:semicolon
)brace
r_if
c_cond
(paren
id|largest_base
op_eq
l_int|0UL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Now construct the final physical address. */
r_if
c_cond
(paren
id|mmap_state
op_eq
id|pci_mmap_io
)paren
id|vma-&gt;vm_pgoff
op_assign
(paren
(paren
(paren
id|largest_base
op_amp
op_complement
l_int|0xffffffUL
)paren
op_or
id|user32
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_else
id|vma-&gt;vm_pgoff
op_assign
(paren
(paren
(paren
id|largest_base
op_amp
op_complement
(paren
id|pci_memspace_mask
)paren
)paren
op_or
id|user32
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Set vm_flags of VMA, as appropriate for this architecture, for a pci device&n; * mapping.&n; */
DECL|function|__pci_mmap_set_flags
r_static
r_void
id|__pci_mmap_set_flags
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_enum
id|pci_mmap_state
id|mmap_state
)paren
(brace
id|vma-&gt;vm_flags
op_or_assign
(paren
id|VM_SHM
op_or
id|VM_LOCKED
)paren
suffix:semicolon
)brace
multiline_comment|/* Set vm_page_prot of VMA, as appropriate for this architecture, for a pci&n; * device mapping.&n; */
DECL|function|__pci_mmap_set_pgprot
r_static
r_void
id|__pci_mmap_set_pgprot
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_enum
id|pci_mmap_state
id|mmap_state
)paren
(brace
multiline_comment|/* Our io_remap_page_range takes care of this, do nothing. */
)brace
r_extern
r_int
id|io_remap_page_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|from
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
id|pgprot_t
id|prot
comma
r_int
id|space
)paren
suffix:semicolon
multiline_comment|/* Perform the actual remap of the pages for a PCI device mapping, as appropriate&n; * for this architecture.  The region in the process to map is described by vm_start&n; * and vm_end members of VMA, the base physical address is found in vm_pgoff.&n; * The pci device structure is provided so that architectures may make mapping&n; * decisions on a per-device or per-bus basis.&n; *&n; * Returns a negative error code on failure, zero on success.&n; */
DECL|function|pci_mmap_page_range
r_int
id|pci_mmap_page_range
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_enum
id|pci_mmap_state
id|mmap_state
comma
r_int
id|write_combine
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|__pci_mmap_make_offset
c_func
(paren
id|dev
comma
id|vma
comma
id|mmap_state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|__pci_mmap_set_flags
c_func
(paren
id|dev
comma
id|vma
comma
id|mmap_state
)paren
suffix:semicolon
id|__pci_mmap_set_pgprot
c_func
(paren
id|dev
comma
id|vma
comma
id|mmap_state
)paren
suffix:semicolon
id|ret
op_assign
id|io_remap_page_range
c_func
(paren
id|vma
comma
id|vma-&gt;vm_start
comma
(paren
id|vma-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
op_or
(paren
id|write_combine
ques
c_cond
l_int|0x1UL
suffix:colon
l_int|0x0UL
)paren
)paren
comma
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_page_prot
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|vma-&gt;vm_flags
op_or_assign
id|VM_IO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Return the index of the PCI controller for device PDEV. */
DECL|function|pci_controller_num
r_int
id|pci_controller_num
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_struct
id|pcidev_cookie
op_star
id|cookie
op_assign
id|pdev-&gt;sysdata
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|cookie
op_ne
l_int|NULL
)paren
(brace
r_struct
id|pci_pbm_info
op_star
id|pbm
op_assign
id|cookie-&gt;pbm
suffix:semicolon
r_if
c_cond
(paren
id|pbm
op_eq
l_int|NULL
op_logical_or
id|pbm-&gt;parent
op_eq
l_int|NULL
)paren
(brace
id|ret
op_assign
op_minus
id|ENXIO
suffix:semicolon
)brace
r_else
(brace
r_struct
id|pci_controller_info
op_star
id|p
op_assign
id|pbm-&gt;parent
suffix:semicolon
id|ret
op_assign
id|p-&gt;index
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;pbms_same_domain
op_eq
l_int|0
)paren
id|ret
op_assign
(paren
(paren
id|ret
op_lshift
l_int|1
)paren
op_plus
(paren
(paren
id|pbm
op_eq
op_amp
id|pbm-&gt;parent-&gt;pbm_B
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|ret
op_assign
op_minus
id|ENXIO
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pcibios_prep_mwi
r_int
id|pcibios_prep_mwi
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
multiline_comment|/* We set correct PCI_CACHE_LINE_SIZE register values for every&n;&t; * device probed on this platform.  So there is nothing to check&n;&t; * and this always succeeds.&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* !(CONFIG_PCI) */
eof
