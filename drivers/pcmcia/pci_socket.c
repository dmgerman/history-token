multiline_comment|/*&n; * Generic PCI pccard driver interface.&n; *&n; * (C) Copyright 1999 Linus Torvalds&n; *&n; * This implements the common parts of PCI pccard drivers,&n; * notably detection and infrastructure conversion (ie change&n; * from socket index to &quot;struct pci_dev&quot; etc)&n; *&n; * This does NOT implement the actual low-level driver details,&n; * and this has on purpose been left generic enough that it can&n; * be used to set up a PCI PCMCIA controller (ie non-cardbus),&n; * or to set up a controller.&n; *&n; * See for example the &quot;yenta&quot; driver for PCI cardbus controllers&n; * conforming to the yenta cardbus specifications.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;pcmcia/ss.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;pci_socket.h&quot;
r_extern
r_struct
id|socket_info_t
op_star
id|pcmcia_register_socket
(paren
r_int
id|slot
comma
r_struct
id|pccard_operations
op_star
id|vtable
comma
r_int
id|use_bus_pm
)paren
suffix:semicolon
r_extern
r_void
id|pcmcia_unregister_socket
(paren
r_struct
id|socket_info_t
op_star
id|socket
)paren
suffix:semicolon
r_extern
r_void
id|pcmcia_suspend_socket
(paren
r_struct
id|socket_info_t
op_star
id|socket
)paren
suffix:semicolon
r_extern
r_void
id|pcmcia_resume_socket
(paren
r_struct
id|socket_info_t
op_star
id|socket
)paren
suffix:semicolon
multiline_comment|/*&n; * Arbitrary define. This is the array of active cardbus&n; * entries.&n; */
DECL|macro|MAX_SOCKETS
mdefine_line|#define MAX_SOCKETS (8)
DECL|variable|pci_socket_array
r_static
id|pci_socket_t
id|pci_socket_array
(braket
id|MAX_SOCKETS
)braket
suffix:semicolon
DECL|function|pci_init_socket
r_static
r_int
id|pci_init_socket
c_func
(paren
r_int
r_int
id|sock
)paren
(brace
id|pci_socket_t
op_star
id|socket
op_assign
id|pci_socket_array
op_plus
id|sock
suffix:semicolon
r_if
c_cond
(paren
id|socket-&gt;op
op_logical_and
id|socket-&gt;op-&gt;init
)paren
r_return
id|socket-&gt;op
op_member_access_from_pointer
id|init
c_func
(paren
id|socket
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|pci_suspend_socket
r_static
r_int
id|pci_suspend_socket
c_func
(paren
r_int
r_int
id|sock
)paren
(brace
id|pci_socket_t
op_star
id|socket
op_assign
id|pci_socket_array
op_plus
id|sock
suffix:semicolon
r_if
c_cond
(paren
id|socket-&gt;op
op_logical_and
id|socket-&gt;op-&gt;suspend
)paren
r_return
id|socket-&gt;op
op_member_access_from_pointer
id|suspend
c_func
(paren
id|socket
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|pci_register_callback
r_static
r_int
id|pci_register_callback
c_func
(paren
r_int
r_int
id|sock
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_void
op_star
comma
r_int
r_int
)paren
comma
r_void
op_star
id|info
)paren
(brace
id|pci_socket_t
op_star
id|socket
op_assign
id|pci_socket_array
op_plus
id|sock
suffix:semicolon
id|socket-&gt;handler
op_assign
id|handler
suffix:semicolon
id|socket-&gt;info
op_assign
id|info
suffix:semicolon
r_if
c_cond
(paren
id|handler
)paren
id|MOD_INC_USE_COUNT
suffix:semicolon
r_else
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_inquire_socket
r_static
r_int
id|pci_inquire_socket
c_func
(paren
r_int
r_int
id|sock
comma
id|socket_cap_t
op_star
id|cap
)paren
(brace
id|pci_socket_t
op_star
id|socket
op_assign
id|pci_socket_array
op_plus
id|sock
suffix:semicolon
op_star
id|cap
op_assign
id|socket-&gt;cap
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_get_status
r_static
r_int
id|pci_get_status
c_func
(paren
r_int
r_int
id|sock
comma
r_int
r_int
op_star
id|value
)paren
(brace
id|pci_socket_t
op_star
id|socket
op_assign
id|pci_socket_array
op_plus
id|sock
suffix:semicolon
r_if
c_cond
(paren
id|socket-&gt;op
op_logical_and
id|socket-&gt;op-&gt;get_status
)paren
r_return
id|socket-&gt;op
op_member_access_from_pointer
id|get_status
c_func
(paren
id|socket
comma
id|value
)paren
suffix:semicolon
op_star
id|value
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|pci_get_socket
r_static
r_int
id|pci_get_socket
c_func
(paren
r_int
r_int
id|sock
comma
id|socket_state_t
op_star
id|state
)paren
(brace
id|pci_socket_t
op_star
id|socket
op_assign
id|pci_socket_array
op_plus
id|sock
suffix:semicolon
r_if
c_cond
(paren
id|socket-&gt;op
op_logical_and
id|socket-&gt;op-&gt;get_socket
)paren
r_return
id|socket-&gt;op
op_member_access_from_pointer
id|get_socket
c_func
(paren
id|socket
comma
id|state
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|pci_set_socket
r_static
r_int
id|pci_set_socket
c_func
(paren
r_int
r_int
id|sock
comma
id|socket_state_t
op_star
id|state
)paren
(brace
id|pci_socket_t
op_star
id|socket
op_assign
id|pci_socket_array
op_plus
id|sock
suffix:semicolon
r_if
c_cond
(paren
id|socket-&gt;op
op_logical_and
id|socket-&gt;op-&gt;set_socket
)paren
r_return
id|socket-&gt;op
op_member_access_from_pointer
id|set_socket
c_func
(paren
id|socket
comma
id|state
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|pci_get_io_map
r_static
r_int
id|pci_get_io_map
c_func
(paren
r_int
r_int
id|sock
comma
r_struct
id|pccard_io_map
op_star
id|io
)paren
(brace
id|pci_socket_t
op_star
id|socket
op_assign
id|pci_socket_array
op_plus
id|sock
suffix:semicolon
r_if
c_cond
(paren
id|socket-&gt;op
op_logical_and
id|socket-&gt;op-&gt;get_io_map
)paren
r_return
id|socket-&gt;op
op_member_access_from_pointer
id|get_io_map
c_func
(paren
id|socket
comma
id|io
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|pci_set_io_map
r_static
r_int
id|pci_set_io_map
c_func
(paren
r_int
r_int
id|sock
comma
r_struct
id|pccard_io_map
op_star
id|io
)paren
(brace
id|pci_socket_t
op_star
id|socket
op_assign
id|pci_socket_array
op_plus
id|sock
suffix:semicolon
r_if
c_cond
(paren
id|socket-&gt;op
op_logical_and
id|socket-&gt;op-&gt;set_io_map
)paren
r_return
id|socket-&gt;op
op_member_access_from_pointer
id|set_io_map
c_func
(paren
id|socket
comma
id|io
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|pci_get_mem_map
r_static
r_int
id|pci_get_mem_map
c_func
(paren
r_int
r_int
id|sock
comma
r_struct
id|pccard_mem_map
op_star
id|mem
)paren
(brace
id|pci_socket_t
op_star
id|socket
op_assign
id|pci_socket_array
op_plus
id|sock
suffix:semicolon
r_if
c_cond
(paren
id|socket-&gt;op
op_logical_and
id|socket-&gt;op-&gt;get_mem_map
)paren
r_return
id|socket-&gt;op
op_member_access_from_pointer
id|get_mem_map
c_func
(paren
id|socket
comma
id|mem
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|pci_set_mem_map
r_static
r_int
id|pci_set_mem_map
c_func
(paren
r_int
r_int
id|sock
comma
r_struct
id|pccard_mem_map
op_star
id|mem
)paren
(brace
id|pci_socket_t
op_star
id|socket
op_assign
id|pci_socket_array
op_plus
id|sock
suffix:semicolon
r_if
c_cond
(paren
id|socket-&gt;op
op_logical_and
id|socket-&gt;op-&gt;set_mem_map
)paren
r_return
id|socket-&gt;op
op_member_access_from_pointer
id|set_mem_map
c_func
(paren
id|socket
comma
id|mem
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|pci_proc_setup
r_static
r_void
id|pci_proc_setup
c_func
(paren
r_int
r_int
id|sock
comma
r_struct
id|proc_dir_entry
op_star
id|base
)paren
(brace
id|pci_socket_t
op_star
id|socket
op_assign
id|pci_socket_array
op_plus
id|sock
suffix:semicolon
r_if
c_cond
(paren
id|socket-&gt;op
op_logical_and
id|socket-&gt;op-&gt;proc_setup
)paren
id|socket-&gt;op
op_member_access_from_pointer
id|proc_setup
c_func
(paren
id|socket
comma
id|base
)paren
suffix:semicolon
)brace
DECL|variable|pci_socket_operations
r_static
r_struct
id|pccard_operations
id|pci_socket_operations
op_assign
(brace
id|pci_init_socket
comma
id|pci_suspend_socket
comma
id|pci_register_callback
comma
id|pci_inquire_socket
comma
id|pci_get_status
comma
id|pci_get_socket
comma
id|pci_set_socket
comma
id|pci_get_io_map
comma
id|pci_set_io_map
comma
id|pci_get_mem_map
comma
id|pci_set_mem_map
comma
id|pci_proc_setup
)brace
suffix:semicolon
DECL|function|add_pci_socket
r_static
r_int
id|__devinit
id|add_pci_socket
c_func
(paren
r_int
id|nr
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|pci_socket_ops
op_star
id|ops
)paren
(brace
id|pci_socket_t
op_star
id|socket
op_assign
id|nr
op_plus
id|pci_socket_array
suffix:semicolon
r_int
id|err
suffix:semicolon
id|memset
c_func
(paren
id|socket
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|socket
)paren
)paren
suffix:semicolon
id|socket-&gt;dev
op_assign
id|dev
suffix:semicolon
id|socket-&gt;op
op_assign
id|ops
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|dev
comma
id|socket
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|socket-&gt;event_lock
)paren
suffix:semicolon
id|err
op_assign
id|socket-&gt;op
op_member_access_from_pointer
id|open
c_func
(paren
id|socket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|socket-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|cardbus_register
r_void
id|cardbus_register
c_func
(paren
id|pci_socket_t
op_star
id|socket
)paren
(brace
r_int
id|nr
op_assign
id|socket
op_minus
id|pci_socket_array
suffix:semicolon
id|socket-&gt;pcmcia_socket
op_assign
id|pcmcia_register_socket
c_func
(paren
id|nr
comma
op_amp
id|pci_socket_operations
comma
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_int
id|__devinit
DECL|function|cardbus_probe
id|cardbus_probe
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|id
)paren
(brace
r_int
id|s
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
l_int|0
suffix:semicolon
id|s
OL
id|MAX_SOCKETS
suffix:semicolon
id|s
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pci_socket_array
(braket
id|s
)braket
dot
id|dev
op_eq
l_int|0
)paren
(brace
r_return
id|add_pci_socket
(paren
id|s
comma
id|dev
comma
op_amp
id|yenta_operations
)paren
suffix:semicolon
)brace
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|cardbus_remove
r_static
r_void
id|__devexit
id|cardbus_remove
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|pci_socket_t
op_star
id|socket
op_assign
id|pci_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pcmcia_unregister_socket
(paren
id|socket-&gt;pcmcia_socket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|socket-&gt;op
op_logical_and
id|socket-&gt;op-&gt;close
)paren
id|socket-&gt;op
op_member_access_from_pointer
id|close
c_func
(paren
id|socket
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|cardbus_suspend
r_static
r_int
id|cardbus_suspend
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u32
id|state
)paren
(brace
id|pci_socket_t
op_star
id|socket
op_assign
id|pci_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pcmcia_suspend_socket
(paren
id|socket-&gt;pcmcia_socket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cardbus_resume
r_static
r_int
id|cardbus_resume
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|pci_socket_t
op_star
id|socket
op_assign
id|pci_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pcmcia_resume_socket
(paren
id|socket-&gt;pcmcia_socket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|cardbus_table
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
r_class
suffix:colon
id|PCI_CLASS_BRIDGE_CARDBUS
op_lshift
l_int|8
comma
id|class_mask
suffix:colon
op_complement
l_int|0
comma
id|vendor
suffix:colon
id|PCI_ANY_ID
comma
id|device
suffix:colon
id|PCI_ANY_ID
comma
id|subvendor
suffix:colon
id|PCI_ANY_ID
comma
id|subdevice
suffix:colon
id|PCI_ANY_ID
comma
)brace
comma
(brace
multiline_comment|/* all zeroes */
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|cardbus_table
)paren
suffix:semicolon
DECL|variable|pci_cardbus_driver
r_static
r_struct
id|pci_driver
id|pci_cardbus_driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;cardbus&quot;
comma
id|id_table
suffix:colon
id|cardbus_table
comma
id|probe
suffix:colon
id|cardbus_probe
comma
id|remove
suffix:colon
id|cardbus_remove
comma
id|suspend
suffix:colon
id|cardbus_suspend
comma
id|resume
suffix:colon
id|cardbus_resume
comma
)brace
suffix:semicolon
DECL|function|pci_socket_init
r_static
r_int
id|__init
id|pci_socket_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pci_module_init
(paren
op_amp
id|pci_cardbus_driver
)paren
suffix:semicolon
)brace
DECL|function|pci_socket_exit
r_static
r_void
id|__exit
id|pci_socket_exit
(paren
r_void
)paren
(brace
id|pci_unregister_driver
(paren
op_amp
id|pci_cardbus_driver
)paren
suffix:semicolon
)brace
DECL|variable|pci_socket_init
id|module_init
c_func
(paren
id|pci_socket_init
)paren
suffix:semicolon
DECL|variable|pci_socket_exit
id|module_exit
c_func
(paren
id|pci_socket_exit
)paren
suffix:semicolon
eof
