multiline_comment|/*&n; *&t;$Id: pci.c,v 1.91 1999/01/21 13:34:01 davem Exp $&n; *&n; *&t;PCI Bus Services, see include/linux/pci.h for further explanation.&n; *&n; *&t;Copyright 1993 -- 1997 Drew Eckhardt, Frederic Potter,&n; *&t;David Mosberger-Tang&n; *&n; *&t;Copyright 1997 -- 2000 Martin Mares &lt;mj@ucw.cz&gt;&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/dma.h&gt;&t;/* isa_dma_bridge_buggy */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif
multiline_comment|/**&n; * pci_bus_max_busnr - returns maximum PCI bus number of given bus&squot; children&n; * @bus: pointer to PCI bus structure to search&n; *&n; * Given a PCI bus, returns the highest PCI bus number present in the set&n; * including the given PCI bus and its list of child PCI buses.&n; */
r_int
r_char
id|__devinit
DECL|function|pci_bus_max_busnr
id|pci_bus_max_busnr
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_int
r_char
id|max
comma
id|n
suffix:semicolon
id|max
op_assign
id|bus-&gt;number
suffix:semicolon
id|list_for_each
c_func
(paren
id|tmp
comma
op_amp
id|bus-&gt;children
)paren
(brace
id|n
op_assign
id|pci_bus_max_busnr
c_func
(paren
id|pci_bus_b
c_func
(paren
id|tmp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
id|max
)paren
(brace
id|max
op_assign
id|n
suffix:semicolon
)brace
)brace
r_return
id|max
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_max_busnr - returns maximum PCI bus number&n; *&n; * Returns the highest PCI bus number present in the system global list of&n; * PCI buses.&n; */
r_int
r_char
id|__devinit
DECL|function|pci_max_busnr
id|pci_max_busnr
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_bus
op_star
id|bus
op_assign
l_int|NULL
suffix:semicolon
r_int
r_char
id|max
comma
id|n
suffix:semicolon
id|max
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|bus
op_assign
id|pci_find_next_bus
c_func
(paren
id|bus
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|n
op_assign
id|pci_bus_max_busnr
c_func
(paren
id|bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
id|max
)paren
(brace
id|max
op_assign
id|n
suffix:semicolon
)brace
)brace
r_return
id|max
suffix:semicolon
)brace
DECL|function|__pci_bus_find_cap
r_static
r_int
id|__pci_bus_find_cap
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
id|u8
id|hdr_type
comma
r_int
id|cap
)paren
(brace
id|u16
id|status
suffix:semicolon
id|u8
id|pos
comma
id|id
suffix:semicolon
r_int
id|ttl
op_assign
l_int|48
suffix:semicolon
id|pci_bus_read_config_word
c_func
(paren
id|bus
comma
id|devfn
comma
id|PCI_STATUS
comma
op_amp
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|PCI_STATUS_CAP_LIST
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|hdr_type
)paren
(brace
r_case
id|PCI_HEADER_TYPE_NORMAL
suffix:colon
r_case
id|PCI_HEADER_TYPE_BRIDGE
suffix:colon
id|pci_bus_read_config_byte
c_func
(paren
id|bus
comma
id|devfn
comma
id|PCI_CAPABILITY_LIST
comma
op_amp
id|pos
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_HEADER_TYPE_CARDBUS
suffix:colon
id|pci_bus_read_config_byte
c_func
(paren
id|bus
comma
id|devfn
comma
id|PCI_CB_CAPABILITY_LIST
comma
op_amp
id|pos
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ttl
op_decrement
op_logical_and
id|pos
op_ge
l_int|0x40
)paren
(brace
id|pos
op_and_assign
op_complement
l_int|3
suffix:semicolon
id|pci_bus_read_config_byte
c_func
(paren
id|bus
comma
id|devfn
comma
id|pos
op_plus
id|PCI_CAP_LIST_ID
comma
op_amp
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
l_int|0xff
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
id|cap
)paren
r_return
id|pos
suffix:semicolon
id|pci_bus_read_config_byte
c_func
(paren
id|bus
comma
id|devfn
comma
id|pos
op_plus
id|PCI_CAP_LIST_NEXT
comma
op_amp
id|pos
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_find_capability - query for devices&squot; capabilities &n; * @dev: PCI device to query&n; * @cap: capability code&n; *&n; * Tell if a device supports a given PCI capability.&n; * Returns the address of the requested capability structure within the&n; * device&squot;s PCI configuration space or 0 in case the device does not&n; * support it.  Possible values for @cap:&n; *&n; *  %PCI_CAP_ID_PM           Power Management &n; *  %PCI_CAP_ID_AGP          Accelerated Graphics Port &n; *  %PCI_CAP_ID_VPD          Vital Product Data &n; *  %PCI_CAP_ID_SLOTID       Slot Identification &n; *  %PCI_CAP_ID_MSI          Message Signalled Interrupts&n; *  %PCI_CAP_ID_CHSWP        CompactPCI HotSwap &n; *  %PCI_CAP_ID_PCIX         PCI-X&n; *  %PCI_CAP_ID_EXP          PCI Express&n; */
DECL|function|pci_find_capability
r_int
id|pci_find_capability
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|cap
)paren
(brace
r_return
id|__pci_bus_find_cap
c_func
(paren
id|dev-&gt;bus
comma
id|dev-&gt;devfn
comma
id|dev-&gt;hdr_type
comma
id|cap
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_bus_find_capability - query for devices&squot; capabilities &n; * @bus:   the PCI bus to query&n; * @devfn: PCI device to query&n; * @cap:   capability code&n; *&n; * Like pci_find_capability() but works for pci devices that do not have a&n; * pci_dev structure set up yet. &n; *&n; * Returns the address of the requested capability structure within the&n; * device&squot;s PCI configuration space or 0 in case the device does not&n; * support it.&n; */
DECL|function|pci_bus_find_capability
r_int
id|pci_bus_find_capability
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|cap
)paren
(brace
id|u8
id|hdr_type
suffix:semicolon
id|pci_bus_read_config_byte
c_func
(paren
id|bus
comma
id|devfn
comma
id|PCI_HEADER_TYPE
comma
op_amp
id|hdr_type
)paren
suffix:semicolon
r_return
id|__pci_bus_find_cap
c_func
(paren
id|bus
comma
id|devfn
comma
id|hdr_type
op_amp
l_int|0x7f
comma
id|cap
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_find_ext_capability - Find an extended capability&n; * @dev: PCI device to query&n; * @cap: capability code&n; *&n; * Returns the address of the requested extended capability structure&n; * within the device&squot;s PCI configuration space or 0 if the device does&n; * not support it.  Possible values for @cap:&n; *&n; *  %PCI_EXT_CAP_ID_ERR&t;&t;Advanced Error Reporting&n; *  %PCI_EXT_CAP_ID_VC&t;&t;Virtual Channel&n; *  %PCI_EXT_CAP_ID_DSN&t;&t;Device Serial Number&n; *  %PCI_EXT_CAP_ID_PWR&t;&t;Power Budgeting&n; */
DECL|function|pci_find_ext_capability
r_int
id|pci_find_ext_capability
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|cap
)paren
(brace
id|u32
id|header
suffix:semicolon
r_int
id|ttl
op_assign
l_int|480
suffix:semicolon
multiline_comment|/* 3840 bytes, minimum 8 bytes per capability */
r_int
id|pos
op_assign
l_int|0x100
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;cfg_size
op_le
l_int|256
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|pos
comma
op_amp
id|header
)paren
op_ne
id|PCIBIOS_SUCCESSFUL
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If we have no capabilities, this is indicated by cap ID,&n;&t; * cap version and next pointer all being 0.&n;&t; */
r_if
c_cond
(paren
id|header
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|ttl
op_decrement
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|PCI_EXT_CAP_ID
c_func
(paren
id|header
)paren
op_eq
id|cap
)paren
r_return
id|pos
suffix:semicolon
id|pos
op_assign
id|PCI_EXT_CAP_NEXT
c_func
(paren
id|header
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0x100
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|pos
comma
op_amp
id|header
)paren
op_ne
id|PCIBIOS_SUCCESSFUL
)paren
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_find_parent_resource - return resource region of parent bus of given region&n; * @dev: PCI device structure contains resources to be searched&n; * @res: child resource record for which parent is sought&n; *&n; *  For given resource region of given device, return the resource&n; *  region of parent bus the given region is contained in or where&n; *  it should be allocated from.&n; */
r_struct
id|resource
op_star
DECL|function|pci_find_parent_resource
id|pci_find_parent_resource
c_func
(paren
r_const
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|resource
op_star
id|res
)paren
(brace
r_const
r_struct
id|pci_bus
op_star
id|bus
op_assign
id|dev-&gt;bus
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|resource
op_star
id|best
op_assign
l_int|NULL
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
id|PCI_BUS_NUM_RESOURCES
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
r_if
c_cond
(paren
id|res-&gt;start
op_logical_and
op_logical_neg
(paren
id|res-&gt;start
op_ge
id|r-&gt;start
op_logical_and
id|res-&gt;end
op_le
id|r-&gt;end
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Not contained */
r_if
c_cond
(paren
(paren
id|res-&gt;flags
op_xor
id|r-&gt;flags
)paren
op_amp
(paren
id|IORESOURCE_IO
op_or
id|IORESOURCE_MEM
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Wrong type */
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|res-&gt;flags
op_xor
id|r-&gt;flags
)paren
op_amp
id|IORESOURCE_PREFETCH
)paren
)paren
r_return
id|r
suffix:semicolon
multiline_comment|/* Exact match */
r_if
c_cond
(paren
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_PREFETCH
)paren
op_logical_and
op_logical_neg
(paren
id|r-&gt;flags
op_amp
id|IORESOURCE_PREFETCH
)paren
)paren
id|best
op_assign
id|r
suffix:semicolon
multiline_comment|/* Approximating prefetchable by non-prefetchable */
)brace
r_return
id|best
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_set_power_state - Set the power state of a PCI device&n; * @dev: PCI device to be suspended&n; * @state: Power state we&squot;re entering&n; *&n; * Transition a device to a new power state, using the Power Management &n; * Capabilities in the device&squot;s config space.&n; *&n; * RETURN VALUE: &n; * -EINVAL if trying to enter a lower state than we&squot;re already in.&n; * 0 if we&squot;re already in the requested state.&n; * -EIO if device does not support PCI PM.&n; * 0 if we can successfully change the power state.&n; */
r_int
DECL|function|pci_set_power_state
id|pci_set_power_state
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|state
)paren
(brace
r_int
id|pm
suffix:semicolon
id|u16
id|pmcsr
suffix:semicolon
multiline_comment|/* bound the state we&squot;re entering */
r_if
c_cond
(paren
id|state
OG
l_int|3
)paren
id|state
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* Validate current state:&n;&t; * Can enter D0 from any state, but if we can only go deeper &n;&t; * to sleep if we&squot;re already in a low power state&n;&t; */
r_if
c_cond
(paren
id|state
OG
l_int|0
op_logical_and
id|dev-&gt;current_state
OG
id|state
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dev-&gt;current_state
op_eq
id|state
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* we&squot;re already there */
multiline_comment|/* find PCI PM capability in list */
id|pm
op_assign
id|pci_find_capability
c_func
(paren
id|dev
comma
id|PCI_CAP_ID_PM
)paren
suffix:semicolon
multiline_comment|/* abort if the device doesn&squot;t support PM capabilities */
r_if
c_cond
(paren
op_logical_neg
id|pm
)paren
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* check if this device supports the desired state */
r_if
c_cond
(paren
id|state
op_eq
l_int|1
op_logical_or
id|state
op_eq
l_int|2
)paren
(brace
id|u16
id|pmc
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|pm
op_plus
id|PCI_PM_PMC
comma
op_amp
id|pmc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
op_eq
l_int|1
op_logical_and
op_logical_neg
(paren
id|pmc
op_amp
id|PCI_PM_CAP_D1
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_else
r_if
c_cond
(paren
id|state
op_eq
l_int|2
op_logical_and
op_logical_neg
(paren
id|pmc
op_amp
id|PCI_PM_CAP_D2
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* If we&squot;re in D3, force entire word to 0.&n;&t; * This doesn&squot;t affect PME_Status, disables PME_En, and&n;&t; * sets PowerState to 0.&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;current_state
op_ge
l_int|3
)paren
id|pmcsr
op_assign
l_int|0
suffix:semicolon
r_else
(brace
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|pm
op_plus
id|PCI_PM_CTRL
comma
op_amp
id|pmcsr
)paren
suffix:semicolon
id|pmcsr
op_and_assign
op_complement
id|PCI_PM_CTRL_STATE_MASK
suffix:semicolon
id|pmcsr
op_or_assign
id|state
suffix:semicolon
)brace
multiline_comment|/* enter specified state */
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|pm
op_plus
id|PCI_PM_CTRL
comma
id|pmcsr
)paren
suffix:semicolon
multiline_comment|/* Mandatory power management transition delays */
multiline_comment|/* see PCI PM 1.1 5.6.1 table 18 */
r_if
c_cond
(paren
id|state
op_eq
l_int|3
op_logical_or
id|dev-&gt;current_state
op_eq
l_int|3
)paren
(brace
id|msleep
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|state
op_eq
l_int|2
op_logical_or
id|dev-&gt;current_state
op_eq
l_int|2
)paren
(brace
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
)brace
id|dev-&gt;current_state
op_assign
id|state
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_save_state - save the PCI configuration space of a device before suspending&n; * @dev: - PCI device that we&squot;re dealing with&n; * @buffer: - buffer to hold config space context&n; *&n; * @buffer must be large enough to hold the entire PCI 2.2 config space &n; * (&gt;= 64 bytes).&n; */
r_int
DECL|function|pci_save_state
id|pci_save_state
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* XXX: 100% dword access ok here? */
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
id|i
op_increment
)paren
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|i
op_star
l_int|4
comma
op_amp
id|dev-&gt;saved_config_space
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/** &n; * pci_restore_state - Restore the saved state of a PCI device&n; * @dev: - PCI device that we&squot;re dealing with&n; * @buffer: - saved PCI config space&n; *&n; */
r_int
DECL|function|pci_restore_state
id|pci_restore_state
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|i
op_star
l_int|4
comma
id|dev-&gt;saved_config_space
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_enable_device_bars - Initialize some of a device for use&n; * @dev: PCI device to be initialized&n; * @bars: bitmask of BAR&squot;s that must be configured&n; *&n; *  Initialize device before it&squot;s used by a driver. Ask low-level code&n; *  to enable selected I/O and memory resources. Wake up the device if it &n; *  was suspended. Beware, this function can fail.&n; */
r_int
DECL|function|pci_enable_device_bars
id|pci_enable_device_bars
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|bars
)paren
(brace
r_int
id|err
suffix:semicolon
id|pci_set_power_state
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|pcibios_enable_device
c_func
(paren
id|dev
comma
id|bars
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_enable_device - Initialize device before it&squot;s used by a driver.&n; * @dev: PCI device to be initialized&n; *&n; *  Initialize device before it&squot;s used by a driver. Ask low-level code&n; *  to enable I/O and memory. Wake up the device if it was suspended.&n; *  Beware, this function can fail.&n; */
r_int
DECL|function|pci_enable_device
id|pci_enable_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|err
suffix:semicolon
id|dev-&gt;is_enabled
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|pci_enable_device_bars
c_func
(paren
id|dev
comma
(paren
l_int|1
op_lshift
id|PCI_NUM_RESOURCES
)paren
op_minus
l_int|1
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|pci_fixup_device
c_func
(paren
id|pci_fixup_enable
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * pcibios_disable_device - disable arch specific PCI resources for device dev&n; * @dev: the PCI device to disable&n; *&n; * Disables architecture specific PCI resources for the device. This&n; * is the default implementation. Architecture implementations can&n; * override this.&n; */
DECL|function|pcibios_disable_device
r_void
id|__attribute__
(paren
(paren
id|weak
)paren
)paren
id|pcibios_disable_device
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
)brace
multiline_comment|/**&n; * pci_disable_device - Disable PCI device after use&n; * @dev: PCI device to be disabled&n; *&n; * Signal to the system that the PCI device is not in use by the system&n; * anymore.  This only involves disabling PCI bus-mastering, if active.&n; */
r_void
DECL|function|pci_disable_device
id|pci_disable_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u16
id|pci_command
suffix:semicolon
id|dev-&gt;is_enabled
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;is_busmaster
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|pci_command
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_command
op_amp
id|PCI_COMMAND_MASTER
)paren
(brace
id|pci_command
op_and_assign
op_complement
id|PCI_COMMAND_MASTER
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|pci_command
)paren
suffix:semicolon
)brace
id|pcibios_disable_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_enable_wake - enable device to generate PME# when suspended&n; * @dev: - PCI device to operate on&n; * @state: - Current state of device.&n; * @enable: - Flag to enable or disable generation&n; * &n; * Set the bits in the device&squot;s PM Capabilities to generate PME# when&n; * the system is suspended. &n; *&n; * -EIO is returned if device doesn&squot;t have PM Capabilities. &n; * -EINVAL is returned if device supports it, but can&squot;t generate wake events.&n; * 0 if operation is successful.&n; * &n; */
DECL|function|pci_enable_wake
r_int
id|pci_enable_wake
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u32
id|state
comma
r_int
id|enable
)paren
(brace
r_int
id|pm
suffix:semicolon
id|u16
id|value
suffix:semicolon
multiline_comment|/* find PCI PM capability in list */
id|pm
op_assign
id|pci_find_capability
c_func
(paren
id|dev
comma
id|PCI_CAP_ID_PM
)paren
suffix:semicolon
multiline_comment|/* If device doesn&squot;t support PM Capabilities, but request is to disable&n;&t; * wake events, it&squot;s a nop; otherwise fail */
r_if
c_cond
(paren
op_logical_neg
id|pm
)paren
r_return
id|enable
ques
c_cond
op_minus
id|EIO
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* Check device&squot;s ability to generate PME# */
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|pm
op_plus
id|PCI_PM_PMC
comma
op_amp
id|value
)paren
suffix:semicolon
id|value
op_and_assign
id|PCI_PM_CAP_PME_MASK
suffix:semicolon
id|value
op_rshift_assign
id|ffs
c_func
(paren
id|PCI_PM_CAP_PME_MASK
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* First bit of mask */
multiline_comment|/* Check if it can generate PME# from requested state. */
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
(paren
id|value
op_amp
(paren
l_int|1
op_lshift
id|state
)paren
)paren
)paren
r_return
id|enable
ques
c_cond
op_minus
id|EINVAL
suffix:colon
l_int|0
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|pm
op_plus
id|PCI_PM_CTRL
comma
op_amp
id|value
)paren
suffix:semicolon
multiline_comment|/* Clear PME_Status by writing 1 to it and enable PME# */
id|value
op_or_assign
id|PCI_PM_CTRL_PME_STATUS
op_or
id|PCI_PM_CTRL_PME_ENABLE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|enable
)paren
id|value
op_and_assign
op_complement
id|PCI_PM_CTRL_PME_ENABLE
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|pm
op_plus
id|PCI_PM_CTRL
comma
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|pci_get_interrupt_pin
id|pci_get_interrupt_pin
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|pci_dev
op_star
op_star
id|bridge
)paren
(brace
id|u8
id|pin
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|pin
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pin
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|pin
op_decrement
suffix:semicolon
r_while
c_loop
(paren
id|dev-&gt;bus-&gt;self
)paren
(brace
id|pin
op_assign
(paren
id|pin
op_plus
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
op_mod
l_int|4
suffix:semicolon
id|dev
op_assign
id|dev-&gt;bus-&gt;self
suffix:semicolon
)brace
op_star
id|bridge
op_assign
id|dev
suffix:semicolon
r_return
id|pin
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;pci_release_region - Release a PCI bar&n; *&t;@pdev: PCI device whose resources were previously reserved by pci_request_region&n; *&t;@bar: BAR to release&n; *&n; *&t;Releases the PCI I/O and memory resources previously reserved by a&n; *&t;successful call to pci_request_region.  Call this function only&n; *&t;after all use of the PCI regions has ceased.&n; */
DECL|function|pci_release_region
r_void
id|pci_release_region
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_int
id|bar
)paren
(brace
r_if
c_cond
(paren
id|pci_resource_len
c_func
(paren
id|pdev
comma
id|bar
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|pci_resource_flags
c_func
(paren
id|pdev
comma
id|bar
)paren
op_amp
id|IORESOURCE_IO
)paren
id|release_region
c_func
(paren
id|pci_resource_start
c_func
(paren
id|pdev
comma
id|bar
)paren
comma
id|pci_resource_len
c_func
(paren
id|pdev
comma
id|bar
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|pci_resource_flags
c_func
(paren
id|pdev
comma
id|bar
)paren
op_amp
id|IORESOURCE_MEM
)paren
id|release_mem_region
c_func
(paren
id|pci_resource_start
c_func
(paren
id|pdev
comma
id|bar
)paren
comma
id|pci_resource_len
c_func
(paren
id|pdev
comma
id|bar
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;pci_request_region - Reserved PCI I/O and memory resource&n; *&t;@pdev: PCI device whose resources are to be reserved&n; *&t;@bar: BAR to be reserved&n; *&t;@res_name: Name to be associated with resource.&n; *&n; *&t;Mark the PCI region associated with PCI device @pdev BR @bar as&n; *&t;being reserved by owner @res_name.  Do not access any&n; *&t;address inside the PCI regions unless this call returns&n; *&t;successfully.&n; *&n; *&t;Returns 0 on success, or %EBUSY on error.  A warning&n; *&t;message is also printed on failure.&n; */
DECL|function|pci_request_region
r_int
id|pci_request_region
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_int
id|bar
comma
r_char
op_star
id|res_name
)paren
(brace
r_if
c_cond
(paren
id|pci_resource_len
c_func
(paren
id|pdev
comma
id|bar
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pci_resource_flags
c_func
(paren
id|pdev
comma
id|bar
)paren
op_amp
id|IORESOURCE_IO
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|pci_resource_start
c_func
(paren
id|pdev
comma
id|bar
)paren
comma
id|pci_resource_len
c_func
(paren
id|pdev
comma
id|bar
)paren
comma
id|res_name
)paren
)paren
r_goto
id|err_out
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pci_resource_flags
c_func
(paren
id|pdev
comma
id|bar
)paren
op_amp
id|IORESOURCE_MEM
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|pci_resource_start
c_func
(paren
id|pdev
comma
id|bar
)paren
comma
id|pci_resource_len
c_func
(paren
id|pdev
comma
id|bar
)paren
comma
id|res_name
)paren
)paren
r_goto
id|err_out
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|err_out
suffix:colon
id|printk
(paren
id|KERN_WARNING
l_string|&quot;PCI: Unable to reserve %s region #%d:%lx@%lx for device %s&bslash;n&quot;
comma
id|pci_resource_flags
c_func
(paren
id|pdev
comma
id|bar
)paren
op_amp
id|IORESOURCE_IO
ques
c_cond
l_string|&quot;I/O&quot;
suffix:colon
l_string|&quot;mem&quot;
comma
id|bar
op_plus
l_int|1
comma
multiline_comment|/* PCI BAR # */
id|pci_resource_len
c_func
(paren
id|pdev
comma
id|bar
)paren
comma
id|pci_resource_start
c_func
(paren
id|pdev
comma
id|bar
)paren
comma
id|pci_name
c_func
(paren
id|pdev
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;pci_release_regions - Release reserved PCI I/O and memory resources&n; *&t;@pdev: PCI device whose resources were previously reserved by pci_request_regions&n; *&n; *&t;Releases all PCI I/O and memory resources previously reserved by a&n; *&t;successful call to pci_request_regions.  Call this function only&n; *&t;after all use of the PCI regions has ceased.&n; */
DECL|function|pci_release_regions
r_void
id|pci_release_regions
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
id|pci_release_region
c_func
(paren
id|pdev
comma
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;pci_request_regions - Reserved PCI I/O and memory resources&n; *&t;@pdev: PCI device whose resources are to be reserved&n; *&t;@res_name: Name to be associated with resource.&n; *&n; *&t;Mark all PCI regions associated with PCI device @pdev as&n; *&t;being reserved by owner @res_name.  Do not access any&n; *&t;address inside the PCI regions unless this call returns&n; *&t;successfully.&n; *&n; *&t;Returns 0 on success, or %EBUSY on error.  A warning&n; *&t;message is also printed on failure.&n; */
DECL|function|pci_request_regions
r_int
id|pci_request_regions
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_char
op_star
id|res_name
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|pci_request_region
c_func
(paren
id|pdev
comma
id|i
comma
id|res_name
)paren
)paren
(brace
r_goto
id|err_out
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|err_out
suffix:colon
r_while
c_loop
(paren
op_decrement
id|i
op_ge
l_int|0
)paren
(brace
id|pci_release_region
c_func
(paren
id|pdev
comma
id|i
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_set_master - enables bus-mastering for device dev&n; * @dev: the PCI device to enable&n; *&n; * Enables bus-mastering on the device and calls pcibios_set_master()&n; * to do the needed arch specific settings.&n; */
r_void
DECL|function|pci_set_master
id|pci_set_master
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u16
id|cmd
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cmd
op_amp
id|PCI_COMMAND_MASTER
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;PCI: Enabling bus mastering for device %s&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|cmd
op_or_assign
id|PCI_COMMAND_MASTER
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
)brace
id|dev-&gt;is_busmaster
op_assign
l_int|1
suffix:semicolon
id|pcibios_set_master
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
macro_line|#ifndef HAVE_ARCH_PCI_MWI
multiline_comment|/* This can be overridden by arch code. */
DECL|variable|pci_cache_line_size
id|u8
id|pci_cache_line_size
op_assign
id|L1_CACHE_BYTES
op_rshift
l_int|2
suffix:semicolon
multiline_comment|/**&n; * pci_generic_prep_mwi - helper function for pci_set_mwi&n; * @dev: the PCI device for which MWI is enabled&n; *&n; * Helper function for generic implementation of pcibios_prep_mwi&n; * function.  Originally copied from drivers/net/acenic.c.&n; * Copyright 1998-2001 by Jes Sorensen, &lt;jes@trained-monkey.org&gt;.&n; *&n; * RETURNS: An appropriate -ERRNO error value on error, or zero for success.&n; */
r_static
r_int
DECL|function|pci_generic_prep_mwi
id|pci_generic_prep_mwi
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u8
id|cacheline_size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_cache_line_size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* The system doesn&squot;t support MWI. */
multiline_comment|/* Validate current setting: the PCI_CACHE_LINE_SIZE must be&n;&t;   equal to or multiple of the right value. */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_CACHE_LINE_SIZE
comma
op_amp
id|cacheline_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cacheline_size
op_ge
id|pci_cache_line_size
op_logical_and
(paren
id|cacheline_size
op_mod
id|pci_cache_line_size
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Write the correct value. */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_CACHE_LINE_SIZE
comma
id|pci_cache_line_size
)paren
suffix:semicolon
multiline_comment|/* Read it back. */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_CACHE_LINE_SIZE
comma
op_amp
id|cacheline_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cacheline_size
op_eq
id|pci_cache_line_size
)paren
r_return
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;PCI: cache line size of %d is not supported &quot;
l_string|&quot;by device %s&bslash;n&quot;
comma
id|pci_cache_line_size
op_lshift
l_int|2
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif /* !HAVE_ARCH_PCI_MWI */
multiline_comment|/**&n; * pci_set_mwi - enables memory-write-invalidate PCI transaction&n; * @dev: the PCI device for which MWI is enabled&n; *&n; * Enables the Memory-Write-Invalidate transaction in %PCI_COMMAND,&n; * and then calls @pcibios_set_mwi to do the needed arch specific&n; * operations or a generic mwi-prep function.&n; *&n; * RETURNS: An appropriate -ERRNO error value on error, or zero for success.&n; */
r_int
DECL|function|pci_set_mwi
id|pci_set_mwi
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|rc
suffix:semicolon
id|u16
id|cmd
suffix:semicolon
macro_line|#ifdef HAVE_ARCH_PCI_MWI
id|rc
op_assign
id|pcibios_prep_mwi
c_func
(paren
id|dev
)paren
suffix:semicolon
macro_line|#else
id|rc
op_assign
id|pci_generic_prep_mwi
c_func
(paren
id|dev
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cmd
op_amp
id|PCI_COMMAND_INVALIDATE
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;PCI: Enabling Mem-Wr-Inval for device %s&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|cmd
op_or_assign
id|PCI_COMMAND_INVALIDATE
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_clear_mwi - disables Memory-Write-Invalidate for device dev&n; * @dev: the PCI device to disable&n; *&n; * Disables PCI Memory-Write-Invalidate transaction on the device&n; */
r_void
DECL|function|pci_clear_mwi
id|pci_clear_mwi
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u16
id|cmd
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_amp
id|PCI_COMMAND_INVALIDATE
)paren
(brace
id|cmd
op_and_assign
op_complement
id|PCI_COMMAND_INVALIDATE
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifndef HAVE_ARCH_PCI_SET_DMA_MASK
multiline_comment|/*&n; * These can be overridden by arch-specific implementations&n; */
r_int
DECL|function|pci_set_dma_mask
id|pci_set_dma_mask
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u64
id|mask
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pci_dma_supported
c_func
(paren
id|dev
comma
id|mask
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|dev-&gt;dma_mask
op_assign
id|mask
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|pci_dac_set_dma_mask
id|pci_dac_set_dma_mask
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u64
id|mask
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pci_dac_dma_supported
c_func
(paren
id|dev
comma
id|mask
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|dev-&gt;dma_mask
op_assign
id|mask
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|pci_set_consistent_dma_mask
id|pci_set_consistent_dma_mask
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u64
id|mask
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pci_dma_supported
c_func
(paren
id|dev
comma
id|mask
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|dev-&gt;dev.coherent_dma_mask
op_assign
id|mask
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|pci_init
r_static
r_int
id|__devinit
id|pci_init
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
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|pci_get_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|pci_fixup_device
c_func
(paren
id|pci_fixup_final
comma
id|dev
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_setup
r_static
r_int
id|__devinit
id|pci_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_while
c_loop
(paren
id|str
)paren
(brace
r_char
op_star
id|k
op_assign
id|strchr
c_func
(paren
id|str
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|k
)paren
op_star
id|k
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|str
op_logical_and
(paren
id|str
op_assign
id|pcibios_setup
c_func
(paren
id|str
)paren
)paren
op_logical_and
op_star
id|str
)paren
(brace
multiline_comment|/* PCI layer options should be handled here */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Unknown option `%s&squot;&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
)brace
id|str
op_assign
id|k
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|pci_init
id|device_initcall
c_func
(paren
id|pci_init
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;pci=&quot;
comma
id|pci_setup
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_ISA) || defined(CONFIG_EISA)
multiline_comment|/* FIXME: Some boxes have multiple ISA bridges! */
DECL|variable|isa_bridge
r_struct
id|pci_dev
op_star
id|isa_bridge
suffix:semicolon
DECL|variable|isa_bridge
id|EXPORT_SYMBOL
c_func
(paren
id|isa_bridge
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|pci_enable_device_bars
id|EXPORT_SYMBOL
c_func
(paren
id|pci_enable_device_bars
)paren
suffix:semicolon
DECL|variable|pci_enable_device
id|EXPORT_SYMBOL
c_func
(paren
id|pci_enable_device
)paren
suffix:semicolon
DECL|variable|pci_disable_device
id|EXPORT_SYMBOL
c_func
(paren
id|pci_disable_device
)paren
suffix:semicolon
DECL|variable|pci_max_busnr
id|EXPORT_SYMBOL
c_func
(paren
id|pci_max_busnr
)paren
suffix:semicolon
DECL|variable|pci_bus_max_busnr
id|EXPORT_SYMBOL
c_func
(paren
id|pci_bus_max_busnr
)paren
suffix:semicolon
DECL|variable|pci_find_capability
id|EXPORT_SYMBOL
c_func
(paren
id|pci_find_capability
)paren
suffix:semicolon
DECL|variable|pci_bus_find_capability
id|EXPORT_SYMBOL
c_func
(paren
id|pci_bus_find_capability
)paren
suffix:semicolon
DECL|variable|pci_release_regions
id|EXPORT_SYMBOL
c_func
(paren
id|pci_release_regions
)paren
suffix:semicolon
DECL|variable|pci_request_regions
id|EXPORT_SYMBOL
c_func
(paren
id|pci_request_regions
)paren
suffix:semicolon
DECL|variable|pci_release_region
id|EXPORT_SYMBOL
c_func
(paren
id|pci_release_region
)paren
suffix:semicolon
DECL|variable|pci_request_region
id|EXPORT_SYMBOL
c_func
(paren
id|pci_request_region
)paren
suffix:semicolon
DECL|variable|pci_set_master
id|EXPORT_SYMBOL
c_func
(paren
id|pci_set_master
)paren
suffix:semicolon
DECL|variable|pci_set_mwi
id|EXPORT_SYMBOL
c_func
(paren
id|pci_set_mwi
)paren
suffix:semicolon
DECL|variable|pci_clear_mwi
id|EXPORT_SYMBOL
c_func
(paren
id|pci_clear_mwi
)paren
suffix:semicolon
DECL|variable|pci_set_dma_mask
id|EXPORT_SYMBOL
c_func
(paren
id|pci_set_dma_mask
)paren
suffix:semicolon
DECL|variable|pci_dac_set_dma_mask
id|EXPORT_SYMBOL
c_func
(paren
id|pci_dac_set_dma_mask
)paren
suffix:semicolon
DECL|variable|pci_set_consistent_dma_mask
id|EXPORT_SYMBOL
c_func
(paren
id|pci_set_consistent_dma_mask
)paren
suffix:semicolon
DECL|variable|pci_assign_resource
id|EXPORT_SYMBOL
c_func
(paren
id|pci_assign_resource
)paren
suffix:semicolon
DECL|variable|pci_find_parent_resource
id|EXPORT_SYMBOL
c_func
(paren
id|pci_find_parent_resource
)paren
suffix:semicolon
DECL|variable|pci_set_power_state
id|EXPORT_SYMBOL
c_func
(paren
id|pci_set_power_state
)paren
suffix:semicolon
DECL|variable|pci_save_state
id|EXPORT_SYMBOL
c_func
(paren
id|pci_save_state
)paren
suffix:semicolon
DECL|variable|pci_restore_state
id|EXPORT_SYMBOL
c_func
(paren
id|pci_restore_state
)paren
suffix:semicolon
DECL|variable|pci_enable_wake
id|EXPORT_SYMBOL
c_func
(paren
id|pci_enable_wake
)paren
suffix:semicolon
multiline_comment|/* Quirk info */
DECL|variable|isa_dma_bridge_buggy
id|EXPORT_SYMBOL
c_func
(paren
id|isa_dma_bridge_buggy
)paren
suffix:semicolon
DECL|variable|pci_pci_problems
id|EXPORT_SYMBOL
c_func
(paren
id|pci_pci_problems
)paren
suffix:semicolon
eof
