multiline_comment|/* linux/arch/i386/kernel/scx200.c &n;&n;   Copyright (c) 2001,2002 Christer Weinigel &lt;wingel@nano-system.com&gt;&n;&n;   National Semiconductor SCx200 support. */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/scx200.h&gt;
macro_line|#include &lt;linux/scx200.h&gt;
DECL|macro|NAME
mdefine_line|#define NAME &quot;scx200&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Christer Weinigel &lt;wingel@nano-system.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;NatSemi SCx200 Driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|scx200_gpio_base
r_int
id|scx200_gpio_base
op_assign
l_int|0
suffix:semicolon
DECL|variable|scx200_gpio_shadow
r_int
id|scx200_gpio_shadow
(braket
l_int|2
)braket
suffix:semicolon
DECL|variable|scx200_gpio_lock
id|spinlock_t
id|scx200_gpio_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|scx200_gpio_config_lock
r_static
id|spinlock_t
id|scx200_gpio_config_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|scx200_gpio_configure
id|u32
id|scx200_gpio_configure
c_func
(paren
r_int
id|index
comma
id|u32
id|mask
comma
id|u32
id|bits
)paren
(brace
id|u32
id|config
comma
id|new_config
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|scx200_gpio_config_lock
comma
id|flags
)paren
suffix:semicolon
id|outl
c_func
(paren
id|index
comma
id|scx200_gpio_base
op_plus
l_int|0x20
)paren
suffix:semicolon
id|config
op_assign
id|inl
c_func
(paren
id|scx200_gpio_base
op_plus
l_int|0x24
)paren
suffix:semicolon
id|new_config
op_assign
(paren
id|config
op_amp
id|mask
)paren
op_or
id|bits
suffix:semicolon
id|outl
c_func
(paren
id|new_config
comma
id|scx200_gpio_base
op_plus
l_int|0x24
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|scx200_gpio_config_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|config
suffix:semicolon
)brace
DECL|function|scx200_gpio_dump
r_void
id|scx200_gpio_dump
c_func
(paren
r_int
id|index
)paren
(brace
id|u32
id|config
op_assign
id|scx200_gpio_configure
c_func
(paren
id|index
comma
op_complement
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;GPIO%02u: 0x%08lx&quot;
comma
id|index
comma
(paren
r_int
r_int
)paren
id|config
)paren
suffix:semicolon
r_if
c_cond
(paren
id|config
op_amp
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot; OE&quot;
)paren
suffix:semicolon
multiline_comment|/* output enabled */
r_else
id|printk
c_func
(paren
l_string|&quot; TS&quot;
)paren
suffix:semicolon
multiline_comment|/* tristate */
r_if
c_cond
(paren
id|config
op_amp
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot; PP&quot;
)paren
suffix:semicolon
multiline_comment|/* push pull */
r_else
id|printk
c_func
(paren
l_string|&quot; OD&quot;
)paren
suffix:semicolon
multiline_comment|/* open drain */
r_if
c_cond
(paren
id|config
op_amp
l_int|4
)paren
id|printk
c_func
(paren
l_string|&quot; PUE&quot;
)paren
suffix:semicolon
multiline_comment|/* pull up enabled */
r_else
id|printk
c_func
(paren
l_string|&quot; PUD&quot;
)paren
suffix:semicolon
multiline_comment|/* pull up disabled */
r_if
c_cond
(paren
id|config
op_amp
l_int|8
)paren
id|printk
c_func
(paren
l_string|&quot; LOCKED&quot;
)paren
suffix:semicolon
multiline_comment|/* locked */
r_if
c_cond
(paren
id|config
op_amp
l_int|16
)paren
id|printk
c_func
(paren
l_string|&quot; LEVEL&quot;
)paren
suffix:semicolon
multiline_comment|/* level input */
r_else
id|printk
c_func
(paren
l_string|&quot; EDGE&quot;
)paren
suffix:semicolon
multiline_comment|/* edge input */
r_if
c_cond
(paren
id|config
op_amp
l_int|32
)paren
id|printk
c_func
(paren
l_string|&quot; HI&quot;
)paren
suffix:semicolon
multiline_comment|/* trigger on rising edge */
r_else
id|printk
c_func
(paren
l_string|&quot; LO&quot;
)paren
suffix:semicolon
multiline_comment|/* trigger on falling edge */
r_if
c_cond
(paren
id|config
op_amp
l_int|64
)paren
id|printk
c_func
(paren
l_string|&quot; DEBOUNCE&quot;
)paren
suffix:semicolon
multiline_comment|/* debounce */
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|scx200_init
r_int
id|__init
id|scx200_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|bridge
suffix:semicolon
r_int
id|bank
suffix:semicolon
r_int
id|base
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|NAME
l_string|&quot;: NatSemi SCx200 Driver&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bridge
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_NS
comma
id|PCI_DEVICE_ID_NS_SCx200_BRIDGE
comma
l_int|NULL
)paren
)paren
op_eq
l_int|NULL
op_logical_and
(paren
id|bridge
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_NS
comma
id|PCI_DEVICE_ID_NS_SC1100_BRIDGE
comma
l_int|NULL
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|base
op_assign
id|pci_resource_start
c_func
(paren
id|bridge
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|NAME
l_string|&quot;: GPIO base 0x%x&bslash;n&quot;
comma
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_region
c_func
(paren
id|base
comma
id|SCx200_GPIO_SIZE
comma
l_string|&quot;NatSemi SCx200 GPIO&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|NAME
l_string|&quot;: can&squot;t allocate I/O for GPIOs&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|scx200_gpio_base
op_assign
id|base
suffix:semicolon
multiline_comment|/* read the current values driven on the GPIO signals */
r_for
c_loop
(paren
id|bank
op_assign
l_int|0
suffix:semicolon
id|bank
OL
l_int|2
suffix:semicolon
op_increment
id|bank
)paren
id|scx200_gpio_shadow
(braket
id|bank
)braket
op_assign
id|inl
c_func
(paren
id|scx200_gpio_base
op_plus
l_int|0x10
op_star
id|bank
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scx200_cleanup
r_void
id|__exit
id|scx200_cleanup
c_func
(paren
r_void
)paren
(brace
id|release_region
c_func
(paren
id|scx200_gpio_base
comma
id|SCx200_GPIO_SIZE
)paren
suffix:semicolon
)brace
DECL|variable|scx200_init
id|module_init
c_func
(paren
id|scx200_init
)paren
suffix:semicolon
DECL|variable|scx200_cleanup
id|module_exit
c_func
(paren
id|scx200_cleanup
)paren
suffix:semicolon
DECL|variable|scx200_gpio_base
id|EXPORT_SYMBOL
c_func
(paren
id|scx200_gpio_base
)paren
suffix:semicolon
DECL|variable|scx200_gpio_shadow
id|EXPORT_SYMBOL
c_func
(paren
id|scx200_gpio_shadow
)paren
suffix:semicolon
DECL|variable|scx200_gpio_lock
id|EXPORT_SYMBOL
c_func
(paren
id|scx200_gpio_lock
)paren
suffix:semicolon
DECL|variable|scx200_gpio_configure
id|EXPORT_SYMBOL
c_func
(paren
id|scx200_gpio_configure
)paren
suffix:semicolon
DECL|variable|scx200_gpio_dump
id|EXPORT_SYMBOL
c_func
(paren
id|scx200_gpio_dump
)paren
suffix:semicolon
multiline_comment|/*&n;    Local variables:&n;        compile-command: &quot;make -k -C ../../.. SUBDIRS=arch/i386/kernel modules&quot;&n;        c-basic-offset: 8&n;    End:&n;*/
eof
