multiline_comment|/* $Id: tpam_main.c,v 1.1.2.3 2001/09/23 22:25:03 kai Exp $&n; *&n; * Turbo PAM ISDN driver for Linux. (Kernel Driver - main routines)&n; *&n; * Copyright 2001 Stelian Pop &lt;stelian.pop@fr.alcove.com&gt;, Alc&#xfffd;ve&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * For all support questions please contact: &lt;support@auvertech.fr&gt;&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;tpam.h&quot;
multiline_comment|/* Local functions prototypes */
r_static
r_int
id|__devinit
id|tpam_probe
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_const
r_struct
id|pci_device_id
op_star
)paren
suffix:semicolon
r_static
r_void
id|__devexit
id|tpam_unregister_card
c_func
(paren
id|tpam_card
op_star
)paren
suffix:semicolon
r_static
r_void
id|__devexit
id|tpam_remove
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
r_static
r_int
id|__init
id|tpam_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|__exit
id|tpam_exit
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* List of boards */
DECL|variable|cards
r_static
id|tpam_card
op_star
id|cards
suffix:semicolon
multiline_comment|/* = NULL; */
multiline_comment|/* Number of cards */
DECL|variable|cards_num
r_static
r_int
id|cards_num
suffix:semicolon
multiline_comment|/* Configurable id of the driver */
DECL|variable|id
r_static
r_char
op_star
id|id
op_assign
l_string|&quot;tpam&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&quot;
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ISDN4Linux: Driver for TurboPAM ISDN cards&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Stelian Pop&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|id
comma
l_string|&quot;ID-String of the driver&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|id
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Finds a board by its driver ID.&n; *&n; * &t;driverId: driver ID (as referenced by the IDSN link layer)&n; *&n; * Return: the tpam_card structure if found, NULL on error.&n; */
DECL|function|tpam_findcard
id|tpam_card
op_star
id|tpam_findcard
c_func
(paren
r_int
id|driverid
)paren
(brace
id|tpam_card
op_star
id|p
op_assign
id|cards
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;id
op_eq
id|driverid
)paren
r_return
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Finds a channel number by its ncoid.&n; *&n; * &t;card: the board&n; * &t;ncoid: the NCO id&n; *&n; * Return: the channel number if found, TPAM_CHANNEL_INVALID if not.&n; */
DECL|function|tpam_findchannel
id|u32
id|tpam_findchannel
c_func
(paren
id|tpam_card
op_star
id|card
comma
id|u32
id|ncoid
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
id|TPAM_NBCHANNEL
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|card-&gt;channels
(braket
id|i
)braket
dot
id|ncoid
op_eq
id|ncoid
)paren
r_return
id|card-&gt;channels
(braket
id|i
)braket
dot
id|num
suffix:semicolon
r_return
id|TPAM_CHANNEL_INVALID
suffix:semicolon
)brace
multiline_comment|/*&n; * Initializes and registers a new TurboPAM card.&n; *&n; * &t;dev: the PCI device&n; * &t;num: the board number&n; *&n; * Return: 0 if OK, &lt;0 if error&n; */
DECL|function|tpam_probe
r_static
r_int
id|__devinit
id|tpam_probe
c_func
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
id|pci_id
)paren
(brace
id|tpam_card
op_star
id|card
comma
op_star
id|c
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* allocate memory for the board structure */
r_if
c_cond
(paren
op_logical_neg
(paren
id|card
op_assign
(paren
id|tpam_card
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|tpam_card
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM: tpam_register_card: &quot;
l_string|&quot;kmalloc failed!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
id|card
comma
l_int|0
comma
r_sizeof
(paren
id|tpam_card
)paren
)paren
suffix:semicolon
id|card-&gt;irq
op_assign
id|dev-&gt;irq
suffix:semicolon
id|card-&gt;lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;interface.id
comma
l_string|&quot;%s%d&quot;
comma
id|id
comma
id|cards_num
)paren
suffix:semicolon
multiline_comment|/* request interrupt */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|card-&gt;irq
comma
op_amp
id|tpam_irq
comma
id|SA_INTERRUPT
op_or
id|SA_SHIRQ
comma
id|card-&gt;interface.id
comma
id|card
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM: tpam_register_card: &quot;
l_string|&quot;could not request irq %d&bslash;n&quot;
comma
id|card-&gt;irq
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* remap board memory */
r_if
c_cond
(paren
op_logical_neg
(paren
id|card-&gt;bar0
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|0
)paren
comma
l_int|0x800000
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM: tpam_register_card: &quot;
l_string|&quot;unable to remap bar0&bslash;n&quot;
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|card-&gt;irq
comma
id|card
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* reset the board */
id|readl
c_func
(paren
id|card-&gt;bar0
op_plus
id|TPAM_RESETPAM_REGISTER
)paren
suffix:semicolon
multiline_comment|/* initialisation magic :-( */
id|copy_to_pam_dword
c_func
(paren
id|card
comma
(paren
r_void
op_star
)paren
l_int|0x01800008
comma
l_int|0x00000030
)paren
suffix:semicolon
id|copy_to_pam_dword
c_func
(paren
id|card
comma
(paren
r_void
op_star
)paren
l_int|0x01800010
comma
l_int|0x00000030
)paren
suffix:semicolon
id|copy_to_pam_dword
c_func
(paren
id|card
comma
(paren
r_void
op_star
)paren
l_int|0x01800014
comma
l_int|0x42240822
)paren
suffix:semicolon
id|copy_to_pam_dword
c_func
(paren
id|card
comma
(paren
r_void
op_star
)paren
l_int|0x01800018
comma
l_int|0x07114000
)paren
suffix:semicolon
id|copy_to_pam_dword
c_func
(paren
id|card
comma
(paren
r_void
op_star
)paren
l_int|0x0180001c
comma
l_int|0x00000400
)paren
suffix:semicolon
id|copy_to_pam_dword
c_func
(paren
id|card
comma
(paren
r_void
op_star
)paren
l_int|0x01840070
comma
l_int|0x00000010
)paren
suffix:semicolon
multiline_comment|/* fill the ISDN link layer structure */
id|card-&gt;interface.channels
op_assign
id|TPAM_NBCHANNEL
suffix:semicolon
id|card-&gt;interface.maxbufsize
op_assign
id|TPAM_MAXBUFSIZE
suffix:semicolon
id|card-&gt;interface.features
op_assign
id|ISDN_FEATURE_P_EURO
op_or
id|ISDN_FEATURE_L2_HDLC
op_or
id|ISDN_FEATURE_L2_MODEM
op_or
id|ISDN_FEATURE_L3_TRANS
suffix:semicolon
id|card-&gt;interface.hl_hdrlen
op_assign
l_int|0
suffix:semicolon
id|card-&gt;interface.command
op_assign
id|tpam_command
suffix:semicolon
id|card-&gt;interface.writebuf_skb
op_assign
id|tpam_writebuf_skb
suffix:semicolon
id|card-&gt;interface.writecmd
op_assign
l_int|NULL
suffix:semicolon
id|card-&gt;interface.readstat
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* register wrt the ISDN link layer */
r_if
c_cond
(paren
op_logical_neg
id|register_isdn
c_func
(paren
op_amp
id|card-&gt;interface
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM: tpam_register_card: &quot;
l_string|&quot;unable to register %s&bslash;n&quot;
comma
id|card-&gt;interface.id
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|card-&gt;irq
comma
id|card
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|card-&gt;bar0
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|card-&gt;id
op_assign
id|card-&gt;interface.channels
suffix:semicolon
multiline_comment|/* initialize all channels */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|TPAM_NBCHANNEL
suffix:semicolon
op_increment
id|i
)paren
(brace
id|card-&gt;channels
(braket
id|i
)braket
dot
id|num
op_assign
id|i
suffix:semicolon
id|card-&gt;channels
(braket
id|i
)braket
dot
id|card
op_assign
id|card
suffix:semicolon
id|card-&gt;channels
(braket
id|i
)braket
dot
id|ncoid
op_assign
id|TPAM_NCOID_INVALID
suffix:semicolon
id|card-&gt;channels
(braket
id|i
)braket
dot
id|hdlc
op_assign
l_int|0
suffix:semicolon
id|card-&gt;channels
(braket
id|i
)braket
dot
id|realhdlc
op_assign
l_int|0
suffix:semicolon
id|card-&gt;channels
(braket
id|i
)braket
dot
id|hdlcshift
op_assign
l_int|0
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|card-&gt;channels
(braket
id|i
)braket
dot
id|sendq
)paren
suffix:semicolon
)brace
multiline_comment|/* initialize the rest of board structure */
id|card-&gt;channels_used
op_assign
l_int|0
suffix:semicolon
id|card-&gt;channels_tested
op_assign
l_int|0
suffix:semicolon
id|card-&gt;running
op_assign
l_int|0
suffix:semicolon
id|card-&gt;busy
op_assign
l_int|0
suffix:semicolon
id|card-&gt;roundrobin
op_assign
l_int|0
suffix:semicolon
id|card-&gt;loopmode
op_assign
l_int|0
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|card-&gt;sendq
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|card-&gt;recvq
)paren
suffix:semicolon
id|card-&gt;recv_tq.routine
op_assign
(paren
r_void
op_star
)paren
(paren
r_void
op_star
)paren
id|tpam_recv_tq
suffix:semicolon
id|card-&gt;recv_tq.data
op_assign
id|card
suffix:semicolon
id|card-&gt;send_tq.routine
op_assign
(paren
r_void
op_star
)paren
(paren
r_void
op_star
)paren
id|tpam_send_tq
suffix:semicolon
id|card-&gt;send_tq.data
op_assign
id|card
suffix:semicolon
multiline_comment|/* add the board at the end of the list of boards */
id|card-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|cards
)paren
(brace
id|c
op_assign
id|cards
suffix:semicolon
r_while
c_loop
(paren
id|c-&gt;next
)paren
id|c
op_assign
id|c-&gt;next
suffix:semicolon
id|c-&gt;next
op_assign
id|card
suffix:semicolon
)brace
r_else
id|cards
op_assign
id|card
suffix:semicolon
op_increment
id|cards_num
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|dev
comma
id|card
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Unregisters a TurboPAM board by releasing all its ressources (irq, mem etc).&n; *&n; * &t;card: the board.&n; */
DECL|function|tpam_unregister_card
r_static
r_void
id|__devexit
id|tpam_unregister_card
c_func
(paren
id|tpam_card
op_star
id|card
)paren
(brace
id|isdn_ctrl
id|cmd
suffix:semicolon
multiline_comment|/* prevent the ISDN link layer that the driver will be unloaded */
id|cmd.command
op_assign
id|ISDN_STAT_UNLOAD
suffix:semicolon
id|cmd.driver
op_assign
id|card-&gt;id
suffix:semicolon
(paren
op_star
id|card-&gt;interface.statcallb
)paren
(paren
op_amp
id|cmd
)paren
suffix:semicolon
multiline_comment|/* release interrupt */
id|free_irq
c_func
(paren
id|card-&gt;irq
comma
id|card
)paren
suffix:semicolon
multiline_comment|/* release mapped memory */
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|card-&gt;bar0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Stops the driver.&n; */
DECL|function|tpam_remove
r_static
r_void
id|__devexit
id|tpam_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|pcidev
)paren
(brace
id|tpam_card
op_star
id|card
op_assign
id|pci_get_drvdata
c_func
(paren
id|pcidev
)paren
suffix:semicolon
id|tpam_card
op_star
id|c
suffix:semicolon
multiline_comment|/* remove from the list of cards */
r_if
c_cond
(paren
id|card
op_eq
id|cards
)paren
id|cards
op_assign
id|cards-&gt;next
suffix:semicolon
r_else
(brace
id|c
op_assign
id|cards
suffix:semicolon
r_while
c_loop
(paren
id|c-&gt;next
op_ne
id|card
)paren
id|c
op_assign
id|c-&gt;next
suffix:semicolon
id|c-&gt;next
op_assign
id|c-&gt;next-&gt;next
suffix:semicolon
)brace
multiline_comment|/* unregister each board */
id|tpam_unregister_card
c_func
(paren
id|card
)paren
suffix:semicolon
multiline_comment|/* and free the board structure itself */
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
)brace
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|tpam_pci_tbl
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|PCI_VENDOR_ID_XILINX
comma
id|PCI_DEVICE_ID_TURBOPAM
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|tpam_pci_tbl
)paren
suffix:semicolon
DECL|variable|tpam_driver
r_static
r_struct
id|pci_driver
id|tpam_driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;tpam&quot;
comma
id|id_table
suffix:colon
id|tpam_pci_tbl
comma
id|probe
suffix:colon
id|tpam_probe
comma
id|remove
suffix:colon
id|tpam_remove
comma
)brace
suffix:semicolon
DECL|function|tpam_init
r_static
r_int
id|__init
id|tpam_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|pci_module_init
c_func
(paren
op_amp
id|tpam_driver
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
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;TurboPAM: %d card%s found, driver loaded.&bslash;n&quot;
comma
id|cards_num
comma
(paren
id|cards_num
OG
l_int|1
)paren
ques
c_cond
l_string|&quot;s&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tpam_exit
r_static
r_void
id|__exit
id|tpam_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|tpam_driver
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;TurboPAM: driver unloaded&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Module entry points */
DECL|variable|tpam_init
id|module_init
c_func
(paren
id|tpam_init
)paren
suffix:semicolon
DECL|variable|tpam_exit
id|module_exit
c_func
(paren
id|tpam_exit
)paren
suffix:semicolon
eof
