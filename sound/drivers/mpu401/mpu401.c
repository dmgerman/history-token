multiline_comment|/*&n; *  Driver for generic MPU-401 boards (UART mode only)&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Copyright (c) 2004 by Castet Matthieu &lt;castet.matthieu@free.fr&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pnp.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/mpu401.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
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
DECL|variable|index
r_static
r_int
id|index
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
op_minus
l_int|2
)brace
suffix:semicolon
multiline_comment|/* exclude the first card */
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
macro_line|#ifdef CONFIG_PNP
DECL|variable|pnp
r_static
r_int
id|pnp
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
id|module_param_array
c_func
(paren
id|index
comma
r_int
comma
l_int|NULL
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
id|module_param_array
c_func
(paren
id|id
comma
id|charp
comma
l_int|NULL
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
id|module_param_array
c_func
(paren
id|enable
comma
r_bool
comma
l_int|NULL
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
macro_line|#ifdef CONFIG_PNP
id|module_param_array
c_func
(paren
id|pnp
comma
r_bool
comma
l_int|NULL
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|pnp
comma
l_string|&quot;PnP detection for MPU-401 device.&quot;
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
l_int|NULL
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
id|module_param_array
c_func
(paren
id|irq
comma
r_int
comma
l_int|NULL
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
DECL|variable|pnp_registered
r_static
r_int
id|pnp_registered
op_assign
l_int|0
suffix:semicolon
DECL|function|snd_mpu401_create
r_static
r_int
id|snd_mpu401_create
c_func
(paren
r_int
id|dev
comma
id|snd_card_t
op_star
op_star
id|rcard
)paren
(brace
id|snd_card_t
op_star
id|card
suffix:semicolon
r_int
id|err
suffix:semicolon
op_star
id|rcard
op_assign
l_int|NULL
suffix:semicolon
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
l_string|&quot;%s at %#lx, &quot;
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
l_string|&quot;irq %d&quot;
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
op_star
id|rcard
op_assign
id|card
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_mpu401_probe
r_static
r_int
id|__devinit
id|snd_mpu401_probe
c_func
(paren
r_int
id|dev
)paren
(brace
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
l_string|&quot;specify or disable IRQ&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|snd_mpu401_create
c_func
(paren
id|dev
comma
op_amp
id|snd_mpu401_legacy_cards
(braket
id|dev
)braket
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PNP
DECL|macro|IO_EXTENT
mdefine_line|#define IO_EXTENT 2
DECL|variable|snd_mpu401_pnpids
r_static
r_struct
id|pnp_device_id
id|snd_mpu401_pnpids
(braket
)braket
op_assign
(brace
(brace
dot
id|id
op_assign
l_string|&quot;PNPb006&quot;
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;&quot;
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pnp
comma
id|snd_mpu401_pnpids
)paren
suffix:semicolon
DECL|function|snd_mpu401_pnp
r_static
r_int
id|__init
id|snd_mpu401_pnp
c_func
(paren
r_int
id|dev
comma
r_struct
id|pnp_dev
op_star
id|device
comma
r_const
r_struct
id|pnp_device_id
op_star
id|id
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pnp_port_valid
c_func
(paren
id|device
comma
l_int|0
)paren
op_logical_or
id|pnp_port_flags
c_func
(paren
id|device
comma
l_int|0
)paren
op_amp
id|IORESOURCE_DISABLED
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;no PnP port&bslash;n&quot;
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
id|pnp_port_len
c_func
(paren
id|device
comma
l_int|0
)paren
OL
id|IO_EXTENT
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnP port length is %ld, expected %d&bslash;n&quot;
comma
id|pnp_port_len
c_func
(paren
id|device
comma
l_int|0
)paren
comma
id|IO_EXTENT
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
id|pnp_port_start
c_func
(paren
id|device
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_irq_valid
c_func
(paren
id|device
comma
l_int|0
)paren
op_logical_or
id|pnp_irq_flags
c_func
(paren
id|device
comma
l_int|0
)paren
op_amp
id|IORESOURCE_DISABLED
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;no PnP irq, using polling&bslash;n&quot;
)paren
suffix:semicolon
id|irq
(braket
id|dev
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|irq
(braket
id|dev
)braket
op_assign
id|pnp_irq
c_func
(paren
id|device
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_mpu401_pnp_probe
r_static
r_int
id|__devinit
id|snd_mpu401_pnp_probe
c_func
(paren
r_struct
id|pnp_dev
op_star
id|pnp_dev
comma
r_const
r_struct
id|pnp_device_id
op_star
id|id
)paren
(brace
r_static
r_int
id|dev
suffix:semicolon
id|snd_card_t
op_star
id|card
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
id|pnp
(braket
id|dev
)braket
)paren
r_continue
suffix:semicolon
id|err
op_assign
id|snd_mpu401_pnp
c_func
(paren
id|dev
comma
id|pnp_dev
comma
id|id
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
id|err
op_assign
id|snd_mpu401_create
c_func
(paren
id|dev
comma
op_amp
id|card
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
id|snd_card_set_dev
c_func
(paren
id|card
comma
op_amp
id|pnp_dev-&gt;dev
)paren
suffix:semicolon
id|pnp_set_drvdata
c_func
(paren
id|pnp_dev
comma
id|card
)paren
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
DECL|function|snd_mpu401_pnp_remove
r_static
r_void
id|__devexit
id|snd_mpu401_pnp_remove
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
id|snd_card_t
op_star
id|card
op_assign
(paren
id|snd_card_t
op_star
)paren
id|pnp_get_drvdata
c_func
(paren
id|dev
)paren
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
)brace
DECL|variable|snd_mpu401_pnp_driver
r_static
r_struct
id|pnp_driver
id|snd_mpu401_pnp_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mpu401&quot;
comma
dot
id|id_table
op_assign
id|snd_mpu401_pnpids
comma
dot
id|probe
op_assign
id|snd_mpu401_pnp_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|snd_mpu401_pnp_remove
)paren
comma
)brace
suffix:semicolon
macro_line|#else
DECL|variable|snd_mpu401_pnp_driver
r_static
r_struct
id|pnp_driver
id|snd_mpu401_pnp_driver
suffix:semicolon
macro_line|#endif
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
comma
id|devices
op_assign
l_int|0
suffix:semicolon
r_int
id|err
suffix:semicolon
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
macro_line|#ifdef CONFIG_PNP
r_if
c_cond
(paren
id|pnp
(braket
id|dev
)braket
)paren
r_continue
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|snd_mpu401_probe
c_func
(paren
id|dev
)paren
op_ge
l_int|0
)paren
id|devices
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|pnp_register_driver
c_func
(paren
op_amp
id|snd_mpu401_pnp_driver
)paren
)paren
op_ge
l_int|0
)paren
(brace
id|pnp_registered
op_assign
l_int|1
suffix:semicolon
id|devices
op_add_assign
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|devices
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
r_if
c_cond
(paren
id|pnp_registered
)paren
id|pnp_unregister_driver
c_func
(paren
op_amp
id|snd_mpu401_pnp_driver
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|pnp_registered
)paren
id|pnp_unregister_driver
c_func
(paren
op_amp
id|snd_mpu401_pnp_driver
)paren
suffix:semicolon
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
