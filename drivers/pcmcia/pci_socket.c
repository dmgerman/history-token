multiline_comment|/*&n; * Generic PCI pccard driver interface.&n; *&n; * (C) Copyright 1999 Linus Torvalds&n; *&n; * This implements the common parts of PCI pccard drivers,&n; * notably detection and infrastructure conversion (ie change&n; * from socket index to &quot;struct pci_dev&quot; etc)&n; *&n; * This does NOT implement the actual low-level driver details,&n; * and this has on purpose been left generic enough that it can&n; * be used to set up a PCI PCMCIA controller (ie non-cardbus),&n; * or to set up a controller.&n; *&n; * See for example the &quot;yenta&quot; driver for PCI cardbus controllers&n; * conforming to the yenta cardbus specifications.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;pcmcia/ss.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;pci_socket.h&quot;
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
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|init
op_assign
id|pci_init_socket
comma
dot
id|suspend
op_assign
id|pci_suspend_socket
comma
dot
id|register_callback
op_assign
id|pci_register_callback
comma
dot
id|inquire_socket
op_assign
id|pci_inquire_socket
comma
dot
id|get_status
op_assign
id|pci_get_status
comma
dot
id|get_socket
op_assign
id|pci_get_socket
comma
dot
id|set_socket
op_assign
id|pci_set_socket
comma
dot
id|set_io_map
op_assign
id|pci_set_io_map
comma
dot
id|set_mem_map
op_assign
id|pci_set_mem_map
comma
dot
id|proc_setup
op_assign
id|pci_proc_setup
comma
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
multiline_comment|/* prepare class_data */
id|socket-&gt;cls_d.sock_offset
op_assign
id|nr
suffix:semicolon
id|socket-&gt;cls_d.nsock
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* yenta is 1, no other low-level driver uses&n;&t;&t;&t;     this yet */
id|socket-&gt;cls_d.ops
op_assign
op_amp
id|pci_socket_operations
suffix:semicolon
id|socket-&gt;cls_d.class_dev
dot
r_class
op_assign
op_amp
id|pcmcia_socket_class
suffix:semicolon
id|socket-&gt;cls_d.class_dev.dev
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|strlcpy
c_func
(paren
id|socket-&gt;cls_d.class_dev.class_id
comma
id|dev-&gt;dev.bus_id
comma
id|BUS_ID_SIZE
)paren
suffix:semicolon
id|class_set_devdata
c_func
(paren
op_amp
id|socket-&gt;cls_d.class_dev
comma
op_amp
id|socket-&gt;cls_d
)paren
suffix:semicolon
multiline_comment|/* prepare pci_socket_t */
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
r_else
(brace
id|class_device_register
c_func
(paren
op_amp
id|socket-&gt;cls_d.class_dev
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|cardbus_register
r_int
id|cardbus_register
c_func
(paren
r_struct
id|pci_dev
op_star
id|p_dev
)paren
(brace
r_return
l_int|0
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
multiline_comment|/* note: we are already unregistered from the cs core */
id|class_device_unregister
c_func
(paren
op_amp
id|socket-&gt;cls_d.class_dev
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
r_return
id|pcmcia_socket_dev_suspend
c_func
(paren
op_amp
id|socket-&gt;cls_d
comma
id|state
comma
l_int|0
)paren
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
r_return
id|pcmcia_socket_dev_resume
c_func
(paren
op_amp
id|socket-&gt;cls_d
comma
id|RESUME_RESTORE_STATE
)paren
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
dot
r_class
op_assign
id|PCI_CLASS_BRIDGE_CARDBUS
op_lshift
l_int|8
comma
dot
id|class_mask
op_assign
op_complement
l_int|0
comma
dot
id|vendor
op_assign
id|PCI_ANY_ID
comma
dot
id|device
op_assign
id|PCI_ANY_ID
comma
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
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
dot
id|name
op_assign
l_string|&quot;cardbus&quot;
comma
dot
id|id_table
op_assign
id|cardbus_table
comma
dot
id|probe
op_assign
id|cardbus_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|cardbus_remove
)paren
comma
dot
id|suspend
op_assign
id|cardbus_suspend
comma
dot
id|resume
op_assign
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
id|pci_register_driver
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
