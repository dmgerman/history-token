multiline_comment|/*&n; * &t;PCI searching functions.&n; *&n; *&t;Copyright (C) 1993 -- 1997 Drew Eckhardt, Frederic Potter,&n; *&t;&t;&t;&t;&t;David Mosberger-Tang&n; *&t;Copyright (C) 1997 -- 2000 Martin Mares &lt;mj@ucw.cz&gt;&n; *&t;Copyright (C) 2003 -- 2004 Greg Kroah-Hartman &lt;greg@kroah.com&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|variable|pci_bus_lock
id|DEFINE_SPINLOCK
c_func
(paren
id|pci_bus_lock
)paren
suffix:semicolon
r_static
r_struct
id|pci_bus
op_star
id|__devinit
DECL|function|pci_do_find_bus
id|pci_do_find_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_char
id|busnr
)paren
(brace
r_struct
id|pci_bus
op_star
id|child
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;number
op_eq
id|busnr
)paren
(brace
r_return
id|bus
suffix:semicolon
)brace
id|list_for_each
c_func
(paren
id|tmp
comma
op_amp
id|bus-&gt;children
)paren
(brace
id|child
op_assign
id|pci_do_find_bus
c_func
(paren
id|pci_bus_b
c_func
(paren
id|tmp
)paren
comma
id|busnr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child
)paren
(brace
r_return
id|child
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_find_bus - locate PCI bus from a given domain and bus number&n; * @domain: number of PCI domain to search&n; * @busnr: number of desired PCI bus&n; *&n; * Given a PCI bus number and domain number, the desired PCI bus is located&n; * in the global list of PCI buses.  If the bus is found, a pointer to its&n; * data structure is returned.  If no bus is found, %NULL is returned.&n; */
DECL|function|pci_find_bus
r_struct
id|pci_bus
op_star
id|__devinit
id|pci_find_bus
c_func
(paren
r_int
id|domain
comma
r_int
id|busnr
)paren
(brace
r_struct
id|pci_bus
op_star
id|bus
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|pci_bus
op_star
id|tmp_bus
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
r_if
c_cond
(paren
id|pci_domain_nr
c_func
(paren
id|bus
)paren
op_ne
id|domain
)paren
r_continue
suffix:semicolon
id|tmp_bus
op_assign
id|pci_do_find_bus
c_func
(paren
id|bus
comma
id|busnr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp_bus
)paren
r_return
id|tmp_bus
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_find_next_bus - begin or continue searching for a PCI bus&n; * @from: Previous PCI bus found, or %NULL for new search.&n; *&n; * Iterates through the list of known PCI busses.  A new search is&n; * initiated by passing %NULL to the @from argument.  Otherwise if&n; * @from is not %NULL, searches continue from next device on the&n; * global list.&n; */
r_struct
id|pci_bus
op_star
DECL|function|pci_find_next_bus
id|pci_find_next_bus
c_func
(paren
r_const
r_struct
id|pci_bus
op_star
id|from
)paren
(brace
r_struct
id|list_head
op_star
id|n
suffix:semicolon
r_struct
id|pci_bus
op_star
id|b
op_assign
l_int|NULL
suffix:semicolon
id|WARN_ON
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pci_bus_lock
)paren
suffix:semicolon
id|n
op_assign
id|from
ques
c_cond
id|from-&gt;node.next
suffix:colon
id|pci_root_buses.next
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ne
op_amp
id|pci_root_buses
)paren
id|b
op_assign
id|pci_bus_b
c_func
(paren
id|n
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pci_bus_lock
)paren
suffix:semicolon
r_return
id|b
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_find_slot - locate PCI device from a given PCI slot&n; * @bus: number of PCI bus on which desired PCI device resides&n; * @devfn: encodes number of PCI slot in which the desired PCI &n; * device resides and the logical device number within that slot &n; * in case of multi-function devices.&n; *&n; * Given a PCI bus and slot/function number, the desired PCI device &n; * is located in system global list of PCI devices.  If the device&n; * is found, a pointer to its data structure is returned.  If no &n; * device is found, %NULL is returned.&n; */
r_struct
id|pci_dev
op_star
DECL|function|pci_find_slot
id|pci_find_slot
c_func
(paren
r_int
r_int
id|bus
comma
r_int
r_int
id|devfn
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
id|pci_find_device
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
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_eq
id|bus
op_logical_and
id|dev-&gt;devfn
op_eq
id|devfn
)paren
r_return
id|dev
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_get_slot - locate PCI device for a given PCI slot&n; * @bus: PCI bus on which desired PCI device resides&n; * @devfn: encodes number of PCI slot in which the desired PCI &n; * device resides and the logical device number within that slot &n; * in case of multi-function devices.&n; *&n; * Given a PCI bus and slot/function number, the desired PCI device &n; * is located in the list of PCI devices.&n; * If the device is found, its reference count is increased and this&n; * function returns a pointer to its data structure.  The caller must&n; * decrement the reference count by calling pci_dev_put().&n; * If no device is found, %NULL is returned.&n; */
DECL|function|pci_get_slot
r_struct
id|pci_dev
op_star
id|pci_get_slot
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
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|WARN_ON
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pci_bus_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|tmp
comma
op_amp
id|bus-&gt;devices
)paren
(brace
id|dev
op_assign
id|pci_dev_b
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;devfn
op_eq
id|devfn
)paren
r_goto
id|out
suffix:semicolon
)brace
id|dev
op_assign
l_int|NULL
suffix:semicolon
id|out
suffix:colon
id|pci_dev_get
c_func
(paren
id|dev
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pci_bus_lock
)paren
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_find_subsys - begin or continue searching for a PCI device by vendor/subvendor/device/subdevice id&n; * @vendor: PCI vendor id to match, or %PCI_ANY_ID to match all vendor ids&n; * @device: PCI device id to match, or %PCI_ANY_ID to match all device ids&n; * @ss_vendor: PCI subsystem vendor id to match, or %PCI_ANY_ID to match all vendor ids&n; * @ss_device: PCI subsystem device id to match, or %PCI_ANY_ID to match all device ids&n; * @from: Previous PCI device found in search, or %NULL for new search.&n; *&n; * Iterates through the list of known PCI devices.  If a PCI device is&n; * found with a matching @vendor, @device, @ss_vendor and @ss_device, a pointer to its&n; * device structure is returned.  Otherwise, %NULL is returned.&n; * A new search is initiated by passing %NULL to the @from argument.&n; * Otherwise if @from is not %NULL, searches continue from next device on the global list.&n; *&n; * NOTE: Do not use this function anymore, use pci_get_subsys() instead, as&n; * the pci device returned by this function can disappear at any moment in&n; * time.&n; */
DECL|function|pci_find_subsys
r_static
r_struct
id|pci_dev
op_star
id|pci_find_subsys
c_func
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
comma
r_int
r_int
id|ss_vendor
comma
r_int
r_int
id|ss_device
comma
r_const
r_struct
id|pci_dev
op_star
id|from
)paren
(brace
r_struct
id|list_head
op_star
id|n
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|WARN_ON
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pci_bus_lock
)paren
suffix:semicolon
id|n
op_assign
id|from
ques
c_cond
id|from-&gt;global_list.next
suffix:colon
id|pci_devices.next
suffix:semicolon
r_while
c_loop
(paren
id|n
op_logical_and
(paren
id|n
op_ne
op_amp
id|pci_devices
)paren
)paren
(brace
id|dev
op_assign
id|pci_dev_g
c_func
(paren
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|vendor
op_eq
id|PCI_ANY_ID
op_logical_or
id|dev-&gt;vendor
op_eq
id|vendor
)paren
op_logical_and
(paren
id|device
op_eq
id|PCI_ANY_ID
op_logical_or
id|dev-&gt;device
op_eq
id|device
)paren
op_logical_and
(paren
id|ss_vendor
op_eq
id|PCI_ANY_ID
op_logical_or
id|dev-&gt;subsystem_vendor
op_eq
id|ss_vendor
)paren
op_logical_and
(paren
id|ss_device
op_eq
id|PCI_ANY_ID
op_logical_or
id|dev-&gt;subsystem_device
op_eq
id|ss_device
)paren
)paren
r_goto
m_exit
suffix:semicolon
id|n
op_assign
id|n-&gt;next
suffix:semicolon
)brace
id|dev
op_assign
l_int|NULL
suffix:semicolon
m_exit
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|pci_bus_lock
)paren
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_find_device - begin or continue searching for a PCI device by vendor/device id&n; * @vendor: PCI vendor id to match, or %PCI_ANY_ID to match all vendor ids&n; * @device: PCI device id to match, or %PCI_ANY_ID to match all device ids&n; * @from: Previous PCI device found in search, or %NULL for new search.&n; *&n; * Iterates through the list of known PCI devices.  If a PCI device is&n; * found with a matching @vendor and @device, a pointer to its device structure is&n; * returned.  Otherwise, %NULL is returned.&n; * A new search is initiated by passing %NULL to the @from argument.&n; * Otherwise if @from is not %NULL, searches continue from next device on the global list.&n; * &n; * NOTE: Do not use this function anymore, use pci_get_device() instead, as&n; * the pci device returned by this function can disappear at any moment in&n; * time.&n; */
r_struct
id|pci_dev
op_star
DECL|function|pci_find_device
id|pci_find_device
c_func
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
comma
r_const
r_struct
id|pci_dev
op_star
id|from
)paren
(brace
r_return
id|pci_find_subsys
c_func
(paren
id|vendor
comma
id|device
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|from
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_get_subsys - begin or continue searching for a PCI device by vendor/subvendor/device/subdevice id&n; * @vendor: PCI vendor id to match, or %PCI_ANY_ID to match all vendor ids&n; * @device: PCI device id to match, or %PCI_ANY_ID to match all device ids&n; * @ss_vendor: PCI subsystem vendor id to match, or %PCI_ANY_ID to match all vendor ids&n; * @ss_device: PCI subsystem device id to match, or %PCI_ANY_ID to match all device ids&n; * @from: Previous PCI device found in search, or %NULL for new search.&n; *&n; * Iterates through the list of known PCI devices.  If a PCI device is&n; * found with a matching @vendor, @device, @ss_vendor and @ss_device, a pointer to its&n; * device structure is returned, and the reference count to the device is&n; * incremented.  Otherwise, %NULL is returned.  A new search is initiated by&n; * passing %NULL to the @from argument.  Otherwise if @from is not %NULL,&n; * searches continue from next device on the global list.&n; * The reference count for @from is always decremented if it is not %NULL.&n; */
r_struct
id|pci_dev
op_star
DECL|function|pci_get_subsys
id|pci_get_subsys
c_func
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
comma
r_int
r_int
id|ss_vendor
comma
r_int
r_int
id|ss_device
comma
r_struct
id|pci_dev
op_star
id|from
)paren
(brace
r_struct
id|list_head
op_star
id|n
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|WARN_ON
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pci_bus_lock
)paren
suffix:semicolon
id|n
op_assign
id|from
ques
c_cond
id|from-&gt;global_list.next
suffix:colon
id|pci_devices.next
suffix:semicolon
r_while
c_loop
(paren
id|n
op_logical_and
(paren
id|n
op_ne
op_amp
id|pci_devices
)paren
)paren
(brace
id|dev
op_assign
id|pci_dev_g
c_func
(paren
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|vendor
op_eq
id|PCI_ANY_ID
op_logical_or
id|dev-&gt;vendor
op_eq
id|vendor
)paren
op_logical_and
(paren
id|device
op_eq
id|PCI_ANY_ID
op_logical_or
id|dev-&gt;device
op_eq
id|device
)paren
op_logical_and
(paren
id|ss_vendor
op_eq
id|PCI_ANY_ID
op_logical_or
id|dev-&gt;subsystem_vendor
op_eq
id|ss_vendor
)paren
op_logical_and
(paren
id|ss_device
op_eq
id|PCI_ANY_ID
op_logical_or
id|dev-&gt;subsystem_device
op_eq
id|ss_device
)paren
)paren
r_goto
m_exit
suffix:semicolon
id|n
op_assign
id|n-&gt;next
suffix:semicolon
)brace
id|dev
op_assign
l_int|NULL
suffix:semicolon
m_exit
suffix:colon
id|pci_dev_put
c_func
(paren
id|from
)paren
suffix:semicolon
id|dev
op_assign
id|pci_dev_get
c_func
(paren
id|dev
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pci_bus_lock
)paren
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_get_device - begin or continue searching for a PCI device by vendor/device id&n; * @vendor: PCI vendor id to match, or %PCI_ANY_ID to match all vendor ids&n; * @device: PCI device id to match, or %PCI_ANY_ID to match all device ids&n; * @from: Previous PCI device found in search, or %NULL for new search.&n; *&n; * Iterates through the list of known PCI devices.  If a PCI device is&n; * found with a matching @vendor and @device, the reference count to the&n; * device is incremented and a pointer to its device structure is returned.&n; * Otherwise, %NULL is returned.  A new search is initiated by passing %NULL&n; * to the @from argument.  Otherwise if @from is not %NULL, searches continue&n; * from next device on the global list.  The reference count for @from is&n; * always decremented if it is not %NULL.&n; */
r_struct
id|pci_dev
op_star
DECL|function|pci_get_device
id|pci_get_device
c_func
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
comma
r_struct
id|pci_dev
op_star
id|from
)paren
(brace
r_return
id|pci_get_subsys
c_func
(paren
id|vendor
comma
id|device
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|from
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_find_device_reverse - begin or continue searching for a PCI device by vendor/device id&n; * @vendor: PCI vendor id to match, or %PCI_ANY_ID to match all vendor ids&n; * @device: PCI device id to match, or %PCI_ANY_ID to match all device ids&n; * @from: Previous PCI device found in search, or %NULL for new search.&n; *&n; * Iterates through the list of known PCI devices in the reverse order of pci_find_device().&n; * If a PCI device is found with a matching @vendor and @device, a pointer to&n; * its device structure is returned.  Otherwise, %NULL is returned.&n; * A new search is initiated by passing %NULL to the @from argument.&n; * Otherwise if @from is not %NULL, searches continue from previous device on the global list.&n; */
r_struct
id|pci_dev
op_star
DECL|function|pci_find_device_reverse
id|pci_find_device_reverse
c_func
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
comma
r_const
r_struct
id|pci_dev
op_star
id|from
)paren
(brace
r_struct
id|list_head
op_star
id|n
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|WARN_ON
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pci_bus_lock
)paren
suffix:semicolon
id|n
op_assign
id|from
ques
c_cond
id|from-&gt;global_list.prev
suffix:colon
id|pci_devices.prev
suffix:semicolon
r_while
c_loop
(paren
id|n
op_logical_and
(paren
id|n
op_ne
op_amp
id|pci_devices
)paren
)paren
(brace
id|dev
op_assign
id|pci_dev_g
c_func
(paren
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|vendor
op_eq
id|PCI_ANY_ID
op_logical_or
id|dev-&gt;vendor
op_eq
id|vendor
)paren
op_logical_and
(paren
id|device
op_eq
id|PCI_ANY_ID
op_logical_or
id|dev-&gt;device
op_eq
id|device
)paren
)paren
r_goto
m_exit
suffix:semicolon
id|n
op_assign
id|n-&gt;prev
suffix:semicolon
)brace
id|dev
op_assign
l_int|NULL
suffix:semicolon
m_exit
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|pci_bus_lock
)paren
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_get_class - begin or continue searching for a PCI device by class&n; * @class: search for a PCI device with this class designation&n; * @from: Previous PCI device found in search, or %NULL for new search.&n; *&n; * Iterates through the list of known PCI devices.  If a PCI device is&n; * found with a matching @class, the reference count to the device is&n; * incremented and a pointer to its device structure is returned.&n; * Otherwise, %NULL is returned.&n; * A new search is initiated by passing %NULL to the @from argument.&n; * Otherwise if @from is not %NULL, searches continue from next device&n; * on the global list.  The reference count for @from is always decremented&n; * if it is not %NULL.&n; */
DECL|function|pci_get_class
r_struct
id|pci_dev
op_star
id|pci_get_class
c_func
(paren
r_int
r_int
r_class
comma
r_struct
id|pci_dev
op_star
id|from
)paren
(brace
r_struct
id|list_head
op_star
id|n
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|WARN_ON
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pci_bus_lock
)paren
suffix:semicolon
id|n
op_assign
id|from
ques
c_cond
id|from-&gt;global_list.next
suffix:colon
id|pci_devices.next
suffix:semicolon
r_while
c_loop
(paren
id|n
op_logical_and
(paren
id|n
op_ne
op_amp
id|pci_devices
)paren
)paren
(brace
id|dev
op_assign
id|pci_dev_g
c_func
(paren
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_member_access_from_pointer
r_class
op_eq
r_class
)paren
r_goto
m_exit
suffix:semicolon
id|n
op_assign
id|n-&gt;next
suffix:semicolon
)brace
id|dev
op_assign
l_int|NULL
suffix:semicolon
m_exit
suffix:colon
id|pci_dev_put
c_func
(paren
id|from
)paren
suffix:semicolon
id|dev
op_assign
id|pci_dev_get
c_func
(paren
id|dev
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pci_bus_lock
)paren
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_dev_present - Returns 1 if device matching the device list is present, 0 if not.&n; * @ids: A pointer to a null terminated list of struct pci_device_id structures&n; * that describe the type of PCI device the caller is trying to find.&n; *&n; * Obvious fact: You do not have a reference to any device that might be found&n; * by this function, so if that device is removed from the system right after&n; * this function is finished, the value will be stale.  Use this function to&n; * find devices that are usually built into a system, or for a general hint as&n; * to if another device happens to be present at this specific moment in time.&n; */
DECL|function|pci_dev_present
r_int
id|pci_dev_present
c_func
(paren
r_const
r_struct
id|pci_device_id
op_star
id|ids
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
id|WARN_ON
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pci_bus_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|ids-&gt;vendor
op_logical_or
id|ids-&gt;subvendor
op_logical_or
id|ids-&gt;class_mask
)paren
(brace
id|list_for_each_entry
c_func
(paren
id|dev
comma
op_amp
id|pci_devices
comma
id|global_list
)paren
(brace
r_if
c_cond
(paren
id|pci_match_one_device
c_func
(paren
id|ids
comma
id|dev
)paren
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
)brace
id|ids
op_increment
suffix:semicolon
)brace
m_exit
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|pci_bus_lock
)paren
suffix:semicolon
r_return
id|found
suffix:semicolon
)brace
DECL|variable|pci_dev_present
id|EXPORT_SYMBOL
c_func
(paren
id|pci_dev_present
)paren
suffix:semicolon
DECL|variable|pci_find_bus
id|EXPORT_SYMBOL
c_func
(paren
id|pci_find_bus
)paren
suffix:semicolon
DECL|variable|pci_find_device
id|EXPORT_SYMBOL
c_func
(paren
id|pci_find_device
)paren
suffix:semicolon
DECL|variable|pci_find_device_reverse
id|EXPORT_SYMBOL
c_func
(paren
id|pci_find_device_reverse
)paren
suffix:semicolon
DECL|variable|pci_find_slot
id|EXPORT_SYMBOL
c_func
(paren
id|pci_find_slot
)paren
suffix:semicolon
DECL|variable|pci_get_device
id|EXPORT_SYMBOL
c_func
(paren
id|pci_get_device
)paren
suffix:semicolon
DECL|variable|pci_get_subsys
id|EXPORT_SYMBOL
c_func
(paren
id|pci_get_subsys
)paren
suffix:semicolon
DECL|variable|pci_get_slot
id|EXPORT_SYMBOL
c_func
(paren
id|pci_get_slot
)paren
suffix:semicolon
DECL|variable|pci_get_class
id|EXPORT_SYMBOL
c_func
(paren
id|pci_get_class
)paren
suffix:semicolon
eof
