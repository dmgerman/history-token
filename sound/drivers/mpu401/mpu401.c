multiline_comment|/*&n; *  Driver for generic MPU-401 boards (UART mode only)&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *  ACPI PnP Copyright (c) 2004 by Clemens Ladisch &lt;clemens@ladisch.de&gt;&n; *  based on 8250_acpi.c&n; *  Copyright (c) 2002-2003 Matthew Wilcox for Hewlett-Packard&n; *  Copyright (C) 2004 Hewlett-Packard Co&n; *       Bjorn Helgaas &lt;bjorn.helgaas@hp.com&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifdef CONFIG_ACPI_BUS
macro_line|#include &lt;acpi/acpi_bus.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/mpu401.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
macro_line|#ifdef CONFIG_ACPI_BUS
DECL|macro|USE_ACPI_PNP
mdefine_line|#define USE_ACPI_PNP
macro_line|#endif
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MPU-401 UART&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_CLASSES
c_func
(paren
l_string|&quot;{sound}&quot;
)paren
suffix:semicolon
DECL|variable|index
r_static
r_int
id|index
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_IDX
suffix:semicolon
multiline_comment|/* Index 0-MAX */
DECL|variable|id
r_static
r_char
op_star
id|id
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_STR
suffix:semicolon
multiline_comment|/* ID for this card */
DECL|variable|enable
r_static
r_int
id|enable
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_ENABLE
suffix:semicolon
multiline_comment|/* Enable this card */
macro_line|#ifdef USE_ACPI_PNP
DECL|variable|acpipnp
r_static
r_int
id|acpipnp
(braket
id|SNDRV_CARDS
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
(paren
id|SNDRV_CARDS
op_minus
l_int|1
)paren
)braket
op_assign
l_int|1
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|port
r_static
r_int
id|port
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_PORT
suffix:semicolon
multiline_comment|/* MPU-401 port number */
DECL|variable|irq
r_static
r_int
id|irq
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_IRQ
suffix:semicolon
multiline_comment|/* MPU-401 IRQ */
DECL|variable|boot_devs
r_static
r_int
id|boot_devs
suffix:semicolon
id|module_param_array
c_func
(paren
id|index
comma
r_int
comma
id|boot_devs
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|index
comma
l_string|&quot;Index value for MPU-401 device.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|index
comma
id|SNDRV_INDEX_DESC
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|id
comma
id|charp
comma
id|boot_devs
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|id
comma
l_string|&quot;ID string for MPU-401 device.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|id
comma
id|SNDRV_ID_DESC
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|enable
comma
r_bool
comma
id|boot_devs
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|enable
comma
l_string|&quot;Enable MPU-401 device.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|enable
comma
id|SNDRV_ENABLE_DESC
)paren
suffix:semicolon
macro_line|#ifdef USE_ACPI_PNP
id|module_param_array
c_func
(paren
id|acpipnp
comma
r_bool
comma
id|boot_devs
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|acpipnp
comma
l_string|&quot;ACPI PnP detection for MPU-401 device.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|acpipnp
comma
id|SNDRV_ENABLED
l_string|&quot;,&quot;
id|SNDRV_BOOLEAN_TRUE_DESC
)paren
suffix:semicolon
macro_line|#endif
id|module_param_array
c_func
(paren
id|port
comma
r_int
comma
id|boot_devs
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|port
comma
l_string|&quot;Port # for MPU-401 device.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|port
comma
id|SNDRV_PORT12_DESC
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|irq
comma
r_int
comma
id|boot_devs
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|irq
comma
l_string|&quot;IRQ # for MPU-401 device.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|irq
comma
id|SNDRV_IRQ_DESC
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_ACPI_BUS
r_struct
id|acpi_device
suffix:semicolon
macro_line|#endif
DECL|variable|snd_mpu401_legacy_cards
r_static
id|snd_card_t
op_star
id|snd_mpu401_legacy_cards
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_PTR
suffix:semicolon
DECL|variable|cards
r_static
r_int
id|cards
suffix:semicolon
macro_line|#ifdef USE_ACPI_PNP
DECL|variable|acpi_driver_registered
r_static
r_int
id|acpi_driver_registered
suffix:semicolon
DECL|struct|mpu401_resources
r_struct
id|mpu401_resources
(brace
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
)brace
suffix:semicolon
DECL|function|snd_mpu401_acpi_resource
r_static
id|acpi_status
id|__devinit
id|snd_mpu401_acpi_resource
c_func
(paren
r_struct
id|acpi_resource
op_star
id|res
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|mpu401_resources
op_star
id|resources
op_assign
(paren
r_struct
id|mpu401_resources
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;id
op_eq
id|ACPI_RSTYPE_IRQ
)paren
(brace
r_if
c_cond
(paren
id|res-&gt;data.irq.number_of_interrupts
OG
l_int|0
)paren
(brace
macro_line|#ifdef CONFIG_IA64
id|resources-&gt;irq
op_assign
id|acpi_register_irq
c_func
(paren
id|res-&gt;data.irq.interrupts
(braket
l_int|0
)braket
comma
id|res-&gt;data.irq.active_high_low
comma
id|res-&gt;data.irq.edge_level
)paren
suffix:semicolon
macro_line|#else
id|resources-&gt;irq
op_assign
id|res-&gt;data.irq.interrupts
(braket
l_int|0
)braket
suffix:semicolon
macro_line|#endif
)brace
)brace
r_else
r_if
c_cond
(paren
id|res-&gt;id
op_eq
id|ACPI_RSTYPE_IO
)paren
(brace
r_if
c_cond
(paren
id|res-&gt;data.io.range_length
op_ge
l_int|2
)paren
(brace
id|resources-&gt;port
op_assign
id|res-&gt;data.io.min_base_address
suffix:semicolon
)brace
)brace
r_return
id|AE_OK
suffix:semicolon
)brace
DECL|function|snd_mpu401_acpi_pnp
r_static
r_int
id|__devinit
id|snd_mpu401_acpi_pnp
c_func
(paren
r_int
id|dev
comma
r_struct
id|acpi_device
op_star
id|device
)paren
(brace
r_struct
id|mpu401_resources
id|res
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|res.port
op_assign
id|SNDRV_AUTO_PORT
suffix:semicolon
id|res.irq
op_assign
id|SNDRV_AUTO_IRQ
suffix:semicolon
id|status
op_assign
id|acpi_walk_resources
c_func
(paren
id|device-&gt;handle
comma
id|METHOD_NAME__CRS
comma
id|snd_mpu401_acpi_resource
comma
op_amp
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|res.port
op_eq
id|SNDRV_AUTO_PORT
op_logical_or
id|res.irq
op_eq
id|SNDRV_AUTO_IRQ
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;no port or irq in %s _CRS&bslash;n&quot;
comma
id|acpi_device_bid
c_func
(paren
id|device
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|port
(braket
id|dev
)braket
op_assign
id|res.port
suffix:semicolon
id|irq
(braket
id|dev
)braket
op_assign
id|res.irq
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* USE_ACPI_PNP */
DECL|function|snd_card_mpu401_probe
r_static
r_int
id|__devinit
id|snd_card_mpu401_probe
c_func
(paren
r_int
id|dev
comma
r_struct
id|acpi_device
op_star
id|device
)paren
(brace
id|snd_card_t
op_star
id|card
suffix:semicolon
r_int
id|err
suffix:semicolon
macro_line|#ifdef USE_ACPI_PNP
r_if
c_cond
(paren
op_logical_neg
id|device
)paren
(brace
macro_line|#endif
r_if
c_cond
(paren
id|port
(braket
id|dev
)braket
op_eq
id|SNDRV_AUTO_PORT
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;specify port&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
(braket
id|dev
)braket
op_eq
id|SNDRV_AUTO_IRQ
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;specify or disable IRQ port&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#ifdef USE_ACPI_PNP
)brace
macro_line|#endif
macro_line|#ifdef USE_ACPI_PNP
r_if
c_cond
(paren
id|device
op_logical_and
(paren
id|err
op_assign
id|snd_mpu401_acpi_pnp
c_func
(paren
id|dev
comma
id|device
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
macro_line|#endif
id|card
op_assign
id|snd_card_new
c_func
(paren
id|index
(braket
id|dev
)braket
comma
id|id
(braket
id|dev
)braket
comma
id|THIS_MODULE
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;driver
comma
l_string|&quot;MPU-401 UART&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;shortname
comma
id|card-&gt;driver
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;%s at 0x%lx, &quot;
comma
id|card-&gt;shortname
comma
id|port
(braket
id|dev
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
(braket
id|dev
)braket
op_ge
l_int|0
)paren
(brace
id|sprintf
c_func
(paren
id|card-&gt;longname
op_plus
id|strlen
c_func
(paren
id|card-&gt;longname
)paren
comma
l_string|&quot;IRQ %d&quot;
comma
id|irq
(braket
id|dev
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|strcat
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;polled&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef USE_ACPI_PNP
r_if
c_cond
(paren
id|device
)paren
(brace
id|strcat
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;, bus id &quot;
)paren
suffix:semicolon
id|strlcat
c_func
(paren
id|card-&gt;longname
comma
id|acpi_device_bid
c_func
(paren
id|device
)paren
comma
r_sizeof
(paren
id|card-&gt;longname
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|snd_mpu401_uart_new
c_func
(paren
id|card
comma
l_int|0
comma
id|MPU401_HW_MPU401
comma
id|port
(braket
id|dev
)braket
comma
l_int|0
comma
id|irq
(braket
id|dev
)braket
comma
id|irq
(braket
id|dev
)braket
op_ge
l_int|0
ques
c_cond
id|SA_INTERRUPT
suffix:colon
l_int|0
comma
l_int|NULL
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;MPU401 not detected at 0x%lx&bslash;n&quot;
comma
id|port
(braket
id|dev
)braket
)paren
suffix:semicolon
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_card_register
c_func
(paren
id|card
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#ifdef USE_ACPI_PNP
r_if
c_cond
(paren
id|device
)paren
id|acpi_driver_data
c_func
(paren
id|device
)paren
op_assign
id|card
suffix:semicolon
r_else
macro_line|#endif
id|snd_mpu401_legacy_cards
(braket
id|dev
)braket
op_assign
id|card
suffix:semicolon
op_increment
id|cards
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef USE_ACPI_PNP
DECL|function|snd_mpu401_acpi_add
r_static
r_int
id|__devinit
id|snd_mpu401_acpi_add
c_func
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
(brace
r_static
r_int
id|dev
suffix:semicolon
r_int
id|err
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|dev
OL
id|SNDRV_CARDS
suffix:semicolon
op_increment
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|enable
(braket
id|dev
)braket
op_logical_or
op_logical_neg
id|acpipnp
(braket
id|dev
)braket
)paren
r_continue
suffix:semicolon
id|err
op_assign
id|snd_card_mpu401_probe
c_func
(paren
id|dev
comma
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
op_increment
id|dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|snd_mpu401_acpi_remove
r_static
r_int
id|__devexit
id|snd_mpu401_acpi_remove
c_func
(paren
r_struct
id|acpi_device
op_star
id|device
comma
r_int
id|type
)paren
(brace
id|snd_card_t
op_star
id|card
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|card
op_assign
(paren
id|snd_card_t
op_star
)paren
id|acpi_driver_data
c_func
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|snd_card_disconnect
c_func
(paren
id|card
)paren
suffix:semicolon
id|snd_card_free_in_thread
c_func
(paren
id|card
)paren
suffix:semicolon
id|acpi_driver_data
c_func
(paren
id|device
)paren
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|snd_mpu401_acpi_driver
r_static
r_struct
id|acpi_driver
id|snd_mpu401_acpi_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;MPU-401 Driver&quot;
comma
dot
r_class
op_assign
l_string|&quot;mpu401&quot;
comma
dot
id|ids
op_assign
l_string|&quot;PNPB006&quot;
comma
dot
id|ops
op_assign
(brace
dot
id|add
op_assign
id|snd_mpu401_acpi_add
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|snd_mpu401_acpi_remove
)paren
comma
)brace
comma
)brace
suffix:semicolon
macro_line|#endif /* USE_ACPI_PNP */
DECL|function|alsa_card_mpu401_init
r_static
r_int
id|__init
id|alsa_card_mpu401_init
c_func
(paren
r_void
)paren
(brace
r_int
id|dev
suffix:semicolon
macro_line|#ifdef USE_ACPI_PNP
r_if
c_cond
(paren
id|acpi_bus_register_driver
c_func
(paren
op_amp
id|snd_mpu401_acpi_driver
)paren
op_ge
l_int|0
)paren
id|acpi_driver_registered
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|dev
op_assign
l_int|0
suffix:semicolon
id|dev
OL
id|SNDRV_CARDS
suffix:semicolon
id|dev
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|enable
(braket
id|dev
)braket
)paren
r_continue
suffix:semicolon
macro_line|#ifdef USE_ACPI_PNP
r_if
c_cond
(paren
id|acpipnp
(braket
id|dev
)braket
op_logical_and
id|acpi_driver_registered
)paren
r_continue
suffix:semicolon
macro_line|#endif
id|snd_card_mpu401_probe
c_func
(paren
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cards
)paren
(brace
macro_line|#ifdef MODULE
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;MPU-401 device not found or device busy&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef USE_ACPI_PNP
r_if
c_cond
(paren
id|acpi_driver_registered
)paren
id|acpi_bus_unregister_driver
c_func
(paren
op_amp
id|snd_mpu401_acpi_driver
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_card_mpu401_exit
r_static
r_void
id|__exit
id|alsa_card_mpu401_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|idx
suffix:semicolon
macro_line|#ifdef USE_ACPI_PNP
r_if
c_cond
(paren
id|acpi_driver_registered
)paren
id|acpi_bus_unregister_driver
c_func
(paren
op_amp
id|snd_mpu401_acpi_driver
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|SNDRV_CARDS
suffix:semicolon
id|idx
op_increment
)paren
id|snd_card_free
c_func
(paren
id|snd_mpu401_legacy_cards
(braket
id|idx
)braket
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_card_mpu401_init
)paren
id|module_exit
c_func
(paren
id|alsa_card_mpu401_exit
)paren
eof
