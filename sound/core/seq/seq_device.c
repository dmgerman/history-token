multiline_comment|/*&n; *  ALSA sequencer device management&n; *  Copyright (c) 1999 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; *&n; *----------------------------------------------------------------&n; *&n; * This device handler seperates the card driver module from sequencer&n; * stuff (sequencer core, synth drivers, etc), so that user can avoid&n; * to spend unnecessary resources e.g. if he needs only listening to&n; * MP3s.&n; *&n; * The card (or lowlevel) driver creates a sequencer device entry&n; * via snd_seq_device_new().  This is an entry pointer to communicate&n; * with the sequencer device &quot;driver&quot;, which is involved with the&n; * actual part to communicate with the sequencer core.&n; * Each sequencer device entry has an id string and the corresponding&n; * driver with the same id is loaded when required.  For example,&n; * lowlevel codes to access emu8000 chip on sbawe card are included in&n; * emu8000-synth module.  To activate this module, the hardware&n; * resources like i/o port are passed via snd_seq_device argument.&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/info.h&gt;
macro_line|#include &lt;sound/seq_device.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Takashi Iwai &lt;tiwai@suse.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ALSA sequencer device management&quot;
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
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;sound&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * driver list&n; */
DECL|typedef|ops_list_t
r_typedef
r_struct
id|ops_list
id|ops_list_t
suffix:semicolon
multiline_comment|/* driver state */
DECL|macro|DRIVER_EMPTY
mdefine_line|#define DRIVER_EMPTY&t;&t;0
DECL|macro|DRIVER_LOADED
mdefine_line|#define DRIVER_LOADED&t;&t;(1&lt;&lt;0)
DECL|macro|DRIVER_REQUESTED
mdefine_line|#define DRIVER_REQUESTED&t;(1&lt;&lt;1)
DECL|macro|DRIVER_LOCKED
mdefine_line|#define DRIVER_LOCKED&t;&t;(1&lt;&lt;2)
DECL|struct|ops_list
r_struct
id|ops_list
(brace
DECL|member|id
r_char
id|id
(braket
id|ID_LEN
)braket
suffix:semicolon
multiline_comment|/* driver id */
DECL|member|driver
r_int
id|driver
suffix:semicolon
multiline_comment|/* driver state */
DECL|member|used
r_int
id|used
suffix:semicolon
multiline_comment|/* reference counter */
DECL|member|argsize
r_int
id|argsize
suffix:semicolon
multiline_comment|/* argument size */
multiline_comment|/* operators */
DECL|member|ops
id|snd_seq_dev_ops_t
id|ops
suffix:semicolon
multiline_comment|/* registred devices */
DECL|member|dev_list
r_struct
id|list_head
id|dev_list
suffix:semicolon
multiline_comment|/* list of devices */
DECL|member|num_devices
r_int
id|num_devices
suffix:semicolon
multiline_comment|/* number of associated devices */
DECL|member|num_init_devices
r_int
id|num_init_devices
suffix:semicolon
multiline_comment|/* number of initialized devices */
DECL|member|reg_mutex
r_struct
id|semaphore
id|reg_mutex
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* next driver */
)brace
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|opslist
)paren
suffix:semicolon
DECL|variable|num_ops
r_static
r_int
id|num_ops
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|ops_mutex
)paren
suffix:semicolon
DECL|variable|info_entry
r_static
id|snd_info_entry_t
op_star
id|info_entry
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * prototypes&n; */
r_static
r_int
id|snd_seq_device_free
c_func
(paren
id|snd_seq_device_t
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|snd_seq_device_dev_free
c_func
(paren
id|snd_device_t
op_star
id|device
)paren
suffix:semicolon
r_static
r_int
id|snd_seq_device_dev_register
c_func
(paren
id|snd_device_t
op_star
id|device
)paren
suffix:semicolon
r_static
r_int
id|snd_seq_device_dev_unregister
c_func
(paren
id|snd_device_t
op_star
id|device
)paren
suffix:semicolon
r_static
r_int
id|init_device
c_func
(paren
id|snd_seq_device_t
op_star
id|dev
comma
id|ops_list_t
op_star
id|ops
)paren
suffix:semicolon
r_static
r_int
id|free_device
c_func
(paren
id|snd_seq_device_t
op_star
id|dev
comma
id|ops_list_t
op_star
id|ops
)paren
suffix:semicolon
r_static
id|ops_list_t
op_star
id|find_driver
c_func
(paren
r_char
op_star
id|id
comma
r_int
id|create_if_empty
)paren
suffix:semicolon
r_static
id|ops_list_t
op_star
id|create_driver
c_func
(paren
r_char
op_star
id|id
)paren
suffix:semicolon
r_static
r_void
id|unlock_driver
c_func
(paren
id|ops_list_t
op_star
id|ops
)paren
suffix:semicolon
r_static
r_void
id|remove_drivers
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * show all drivers and their status&n; */
DECL|function|snd_seq_device_info
r_static
r_void
id|snd_seq_device_info
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
comma
id|snd_info_buffer_t
op_star
id|buffer
)paren
(brace
r_struct
id|list_head
op_star
id|head
suffix:semicolon
id|down
c_func
(paren
op_amp
id|ops_mutex
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|head
comma
op_amp
id|opslist
)paren
(brace
id|ops_list_t
op_star
id|ops
op_assign
id|list_entry
c_func
(paren
id|head
comma
id|ops_list_t
comma
id|list
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;snd-%s%s%s%s,%d&bslash;n&quot;
comma
id|ops-&gt;id
comma
id|ops-&gt;driver
op_amp
id|DRIVER_LOADED
ques
c_cond
l_string|&quot;,loaded&quot;
suffix:colon
(paren
id|ops-&gt;driver
op_eq
id|DRIVER_EMPTY
ques
c_cond
l_string|&quot;,empty&quot;
suffix:colon
l_string|&quot;&quot;
)paren
comma
id|ops-&gt;driver
op_amp
id|DRIVER_REQUESTED
ques
c_cond
l_string|&quot;,requested&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|ops-&gt;driver
op_amp
id|DRIVER_LOCKED
ques
c_cond
l_string|&quot;,locked&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|ops-&gt;num_devices
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|ops_mutex
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * load all registered drivers (called from seq_clientmgr.c)&n; */
DECL|function|snd_seq_device_load_drivers
r_void
id|snd_seq_device_load_drivers
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_KMOD
r_struct
id|list_head
op_star
id|head
suffix:semicolon
r_char
id|modname
(braket
l_int|64
)braket
suffix:semicolon
id|down
c_func
(paren
op_amp
id|ops_mutex
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|head
comma
op_amp
id|opslist
)paren
(brace
id|ops_list_t
op_star
id|ops
op_assign
id|list_entry
c_func
(paren
id|head
comma
id|ops_list_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ops-&gt;driver
op_amp
id|DRIVER_LOADED
)paren
op_logical_and
op_logical_neg
(paren
id|ops-&gt;driver
op_amp
id|DRIVER_REQUESTED
)paren
)paren
(brace
id|ops-&gt;used
op_increment
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ops_mutex
)paren
suffix:semicolon
id|ops-&gt;driver
op_or_assign
id|DRIVER_REQUESTED
suffix:semicolon
id|sprintf
c_func
(paren
id|modname
comma
l_string|&quot;snd-%s&quot;
comma
id|ops-&gt;id
)paren
suffix:semicolon
id|request_module
c_func
(paren
id|modname
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|ops_mutex
)paren
suffix:semicolon
id|ops-&gt;used
op_decrement
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|ops_mutex
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * register a sequencer device&n; * card = card info (NULL allowed)&n; * device = device number (if any)&n; * id = id of driver&n; * result = return pointer (NULL allowed if unnecessary)&n; */
DECL|function|snd_seq_device_new
r_int
id|snd_seq_device_new
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_int
id|device
comma
r_char
op_star
id|id
comma
r_int
id|argsize
comma
id|snd_seq_device_t
op_star
op_star
id|result
)paren
(brace
id|snd_seq_device_t
op_star
id|dev
suffix:semicolon
id|ops_list_t
op_star
id|ops
suffix:semicolon
r_int
id|err
suffix:semicolon
r_static
id|snd_device_ops_t
id|dops
op_assign
(brace
id|dev_free
suffix:colon
id|snd_seq_device_dev_free
comma
id|dev_register
suffix:colon
id|snd_seq_device_dev_register
comma
id|dev_unregister
suffix:colon
id|snd_seq_device_dev_unregister
)brace
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
id|snd_assert
c_func
(paren
id|id
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|ops
op_assign
id|find_driver
c_func
(paren
id|id
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ops
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|dev
op_assign
id|snd_magic_kcalloc
c_func
(paren
id|snd_seq_device_t
comma
r_sizeof
(paren
op_star
id|dev
)paren
op_plus
id|argsize
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|unlock_driver
c_func
(paren
id|ops
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* set up device info */
id|dev-&gt;card
op_assign
id|card
suffix:semicolon
id|dev-&gt;device
op_assign
id|device
suffix:semicolon
id|strncpy
c_func
(paren
id|dev-&gt;id
comma
id|id
comma
r_sizeof
(paren
id|dev-&gt;id
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|dev-&gt;id
(braket
r_sizeof
(paren
id|dev-&gt;id
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;argsize
op_assign
id|argsize
suffix:semicolon
id|dev-&gt;status
op_assign
id|SNDRV_SEQ_DEVICE_FREE
suffix:semicolon
multiline_comment|/* add this device to the list */
id|down
c_func
(paren
op_amp
id|ops-&gt;reg_mutex
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|dev-&gt;list
comma
op_amp
id|ops-&gt;dev_list
)paren
suffix:semicolon
id|ops-&gt;num_devices
op_increment
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ops-&gt;reg_mutex
)paren
suffix:semicolon
id|unlock_driver
c_func
(paren
id|ops
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_device_new
c_func
(paren
id|card
comma
id|SNDRV_DEV_SEQUENCER
comma
id|dev
comma
op_amp
id|dops
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_seq_device_free
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
)paren
op_star
id|result
op_assign
id|dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * free the existing device&n; */
DECL|function|snd_seq_device_free
r_static
r_int
id|snd_seq_device_free
c_func
(paren
id|snd_seq_device_t
op_star
id|dev
)paren
(brace
id|ops_list_t
op_star
id|ops
suffix:semicolon
id|snd_assert
c_func
(paren
id|dev
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|ops
op_assign
id|find_driver
c_func
(paren
id|dev-&gt;id
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ops
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* remove the device from the list */
id|down
c_func
(paren
op_amp
id|ops-&gt;reg_mutex
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|dev-&gt;list
)paren
suffix:semicolon
id|ops-&gt;num_devices
op_decrement
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ops-&gt;reg_mutex
)paren
suffix:semicolon
id|free_device
c_func
(paren
id|dev
comma
id|ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;private_free
)paren
id|dev
op_member_access_from_pointer
id|private_free
c_func
(paren
id|dev
)paren
suffix:semicolon
id|snd_magic_kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
id|unlock_driver
c_func
(paren
id|ops
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_seq_device_dev_free
r_static
r_int
id|snd_seq_device_dev_free
c_func
(paren
id|snd_device_t
op_star
id|device
)paren
(brace
id|snd_seq_device_t
op_star
id|dev
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_seq_device_t
comma
id|device-&gt;device_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_return
id|snd_seq_device_free
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * register the device&n; */
DECL|function|snd_seq_device_dev_register
r_static
r_int
id|snd_seq_device_dev_register
c_func
(paren
id|snd_device_t
op_star
id|device
)paren
(brace
id|snd_seq_device_t
op_star
id|dev
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_seq_device_t
comma
id|device-&gt;device_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|ops_list_t
op_star
id|ops
suffix:semicolon
id|ops
op_assign
id|find_driver
c_func
(paren
id|dev-&gt;id
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ops
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
multiline_comment|/* initialize this device if the corresponding driver was&n;&t; * already loaded&n;&t; */
r_if
c_cond
(paren
id|ops-&gt;driver
op_amp
id|DRIVER_LOADED
)paren
id|init_device
c_func
(paren
id|dev
comma
id|ops
)paren
suffix:semicolon
id|unlock_driver
c_func
(paren
id|ops
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * unregister the existing device&n; */
DECL|function|snd_seq_device_dev_unregister
r_static
r_int
id|snd_seq_device_dev_unregister
c_func
(paren
id|snd_device_t
op_star
id|device
)paren
(brace
id|snd_seq_device_t
op_star
id|dev
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_seq_device_t
comma
id|device-&gt;device_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_return
id|snd_seq_device_free
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * register device driver&n; * id = driver id&n; * entry = driver operators - duplicated to each instance&n; */
DECL|function|snd_seq_device_register_driver
r_int
id|snd_seq_device_register_driver
c_func
(paren
r_char
op_star
id|id
comma
id|snd_seq_dev_ops_t
op_star
id|entry
comma
r_int
id|argsize
)paren
(brace
r_struct
id|list_head
op_star
id|head
suffix:semicolon
id|ops_list_t
op_star
id|ops
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
l_int|NULL
op_logical_or
id|entry
op_eq
l_int|NULL
op_logical_or
id|entry-&gt;init_device
op_eq
l_int|NULL
op_logical_or
id|entry-&gt;free_device
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ops
op_assign
id|find_driver
c_func
(paren
id|id
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ops
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|ops-&gt;driver
op_amp
id|DRIVER_LOADED
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;driver_register: driver &squot;%s&squot; already exists&bslash;n&quot;
comma
id|id
)paren
suffix:semicolon
id|unlock_driver
c_func
(paren
id|ops
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|ops-&gt;reg_mutex
)paren
suffix:semicolon
multiline_comment|/* copy driver operators */
id|ops-&gt;ops
op_assign
op_star
id|entry
suffix:semicolon
id|ops-&gt;driver
op_or_assign
id|DRIVER_LOADED
suffix:semicolon
id|ops-&gt;argsize
op_assign
id|argsize
suffix:semicolon
multiline_comment|/* initialize existing devices if necessary */
id|list_for_each
c_func
(paren
id|head
comma
op_amp
id|ops-&gt;dev_list
)paren
(brace
id|snd_seq_device_t
op_star
id|dev
op_assign
id|list_entry
c_func
(paren
id|head
comma
id|snd_seq_device_t
comma
id|list
)paren
suffix:semicolon
id|init_device
c_func
(paren
id|dev
comma
id|ops
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|ops-&gt;reg_mutex
)paren
suffix:semicolon
id|unlock_driver
c_func
(paren
id|ops
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * create driver record&n; */
DECL|function|create_driver
r_static
id|ops_list_t
op_star
id|create_driver
c_func
(paren
r_char
op_star
id|id
)paren
(brace
id|ops_list_t
op_star
id|ops
suffix:semicolon
id|ops
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ops
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ops
op_eq
l_int|NULL
)paren
r_return
id|ops
suffix:semicolon
id|memset
c_func
(paren
id|ops
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ops
)paren
)paren
suffix:semicolon
multiline_comment|/* set up driver entry */
id|strncpy
c_func
(paren
id|ops-&gt;id
comma
id|id
comma
r_sizeof
(paren
id|ops-&gt;id
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|ops-&gt;id
(braket
r_sizeof
(paren
id|ops-&gt;id
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|ops-&gt;reg_mutex
)paren
suffix:semicolon
id|ops-&gt;driver
op_assign
id|DRIVER_EMPTY
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|ops-&gt;dev_list
)paren
suffix:semicolon
multiline_comment|/* lock this instance */
id|ops-&gt;used
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* register driver entry */
id|down
c_func
(paren
op_amp
id|ops_mutex
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|ops-&gt;list
comma
op_amp
id|opslist
)paren
suffix:semicolon
id|num_ops
op_increment
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ops_mutex
)paren
suffix:semicolon
r_return
id|ops
suffix:semicolon
)brace
multiline_comment|/*&n; * unregister the specified driver&n; */
DECL|function|snd_seq_device_unregister_driver
r_int
id|snd_seq_device_unregister_driver
c_func
(paren
r_char
op_star
id|id
)paren
(brace
r_struct
id|list_head
op_star
id|head
suffix:semicolon
id|ops_list_t
op_star
id|ops
suffix:semicolon
id|ops
op_assign
id|find_driver
c_func
(paren
id|id
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ops
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ops-&gt;driver
op_amp
id|DRIVER_LOADED
)paren
op_logical_or
(paren
id|ops-&gt;driver
op_amp
id|DRIVER_LOCKED
)paren
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;driver_unregister: cannot unload driver &squot;%s&squot;: status=%x&bslash;n&quot;
comma
id|id
comma
id|ops-&gt;driver
)paren
suffix:semicolon
id|unlock_driver
c_func
(paren
id|ops
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/* close and release all devices associated with this driver */
id|down
c_func
(paren
op_amp
id|ops-&gt;reg_mutex
)paren
suffix:semicolon
id|ops-&gt;driver
op_or_assign
id|DRIVER_LOCKED
suffix:semicolon
multiline_comment|/* do not remove this driver recursively */
id|list_for_each
c_func
(paren
id|head
comma
op_amp
id|ops-&gt;dev_list
)paren
(brace
id|snd_seq_device_t
op_star
id|dev
op_assign
id|list_entry
c_func
(paren
id|head
comma
id|snd_seq_device_t
comma
id|list
)paren
suffix:semicolon
id|free_device
c_func
(paren
id|dev
comma
id|ops
)paren
suffix:semicolon
)brace
id|ops-&gt;driver
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ops-&gt;num_init_devices
OG
l_int|0
)paren
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;free_driver: init_devices &gt; 0!! (%d)&bslash;n&quot;
comma
id|ops-&gt;num_init_devices
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ops-&gt;reg_mutex
)paren
suffix:semicolon
id|unlock_driver
c_func
(paren
id|ops
)paren
suffix:semicolon
multiline_comment|/* remove empty driver entries */
id|remove_drivers
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * remove empty driver entries&n; */
DECL|function|remove_drivers
r_static
r_void
id|remove_drivers
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|head
suffix:semicolon
id|down
c_func
(paren
op_amp
id|ops_mutex
)paren
suffix:semicolon
id|head
op_assign
id|opslist.next
suffix:semicolon
r_while
c_loop
(paren
id|head
op_ne
op_amp
id|opslist
)paren
(brace
id|ops_list_t
op_star
id|ops
op_assign
id|list_entry
c_func
(paren
id|head
comma
id|ops_list_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ops-&gt;driver
op_amp
id|DRIVER_LOADED
)paren
op_logical_and
id|ops-&gt;used
op_eq
l_int|0
op_logical_and
id|ops-&gt;num_devices
op_eq
l_int|0
)paren
(brace
id|head
op_assign
id|head-&gt;next
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|ops-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ops
)paren
suffix:semicolon
id|num_ops
op_decrement
suffix:semicolon
)brace
r_else
id|head
op_assign
id|head-&gt;next
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|ops_mutex
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * initialize the device - call init_device operator&n; */
DECL|function|init_device
r_static
r_int
id|init_device
c_func
(paren
id|snd_seq_device_t
op_star
id|dev
comma
id|ops_list_t
op_star
id|ops
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ops-&gt;driver
op_amp
id|DRIVER_LOADED
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* driver is not loaded yet */
r_if
c_cond
(paren
id|dev-&gt;status
op_ne
id|SNDRV_SEQ_DEVICE_FREE
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* already initialized */
r_if
c_cond
(paren
id|ops-&gt;argsize
op_ne
id|dev-&gt;argsize
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;incompatible device &squot;%s&squot; for plug-in &squot;%s&squot; (%d %d)&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ops-&gt;id
comma
id|ops-&gt;argsize
comma
id|dev-&gt;argsize
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
id|ops-&gt;ops
dot
id|init_device
c_func
(paren
id|dev
)paren
op_ge
l_int|0
)paren
(brace
id|dev-&gt;status
op_assign
id|SNDRV_SEQ_DEVICE_REGISTERED
suffix:semicolon
id|ops-&gt;num_init_devices
op_increment
suffix:semicolon
)brace
r_else
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;init_device failed: %s: %s&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;id
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * release the device - call free_device operator&n; */
DECL|function|free_device
r_static
r_int
id|free_device
c_func
(paren
id|snd_seq_device_t
op_star
id|dev
comma
id|ops_list_t
op_star
id|ops
)paren
(brace
r_int
id|result
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ops-&gt;driver
op_amp
id|DRIVER_LOADED
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* driver is not loaded yet */
r_if
c_cond
(paren
id|dev-&gt;status
op_ne
id|SNDRV_SEQ_DEVICE_REGISTERED
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* not registered */
r_if
c_cond
(paren
id|ops-&gt;argsize
op_ne
id|dev-&gt;argsize
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;incompatible device &squot;%s&squot; for plug-in &squot;%s&squot; (%d %d)&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ops-&gt;id
comma
id|ops-&gt;argsize
comma
id|dev-&gt;argsize
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
(paren
id|result
op_assign
id|ops-&gt;ops
dot
id|free_device
c_func
(paren
id|dev
)paren
)paren
op_ge
l_int|0
op_logical_or
id|result
op_eq
op_minus
id|ENXIO
)paren
(brace
id|dev-&gt;status
op_assign
id|SNDRV_SEQ_DEVICE_FREE
suffix:semicolon
id|dev-&gt;driver_data
op_assign
l_int|NULL
suffix:semicolon
id|ops-&gt;num_init_devices
op_decrement
suffix:semicolon
)brace
r_else
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;free_device failed: %s: %s&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;id
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * find the matching driver with given id&n; */
DECL|function|find_driver
r_static
id|ops_list_t
op_star
id|find_driver
c_func
(paren
r_char
op_star
id|id
comma
r_int
id|create_if_empty
)paren
(brace
r_struct
id|list_head
op_star
id|head
suffix:semicolon
id|down
c_func
(paren
op_amp
id|ops_mutex
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|head
comma
op_amp
id|opslist
)paren
(brace
id|ops_list_t
op_star
id|ops
op_assign
id|list_entry
c_func
(paren
id|head
comma
id|ops_list_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|ops-&gt;id
comma
id|id
)paren
op_eq
l_int|0
)paren
(brace
id|ops-&gt;used
op_increment
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ops_mutex
)paren
suffix:semicolon
r_return
id|ops
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|ops_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|create_if_empty
)paren
r_return
id|create_driver
c_func
(paren
id|id
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|unlock_driver
r_static
r_void
id|unlock_driver
c_func
(paren
id|ops_list_t
op_star
id|ops
)paren
(brace
id|down
c_func
(paren
op_amp
id|ops_mutex
)paren
suffix:semicolon
id|ops-&gt;used
op_decrement
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ops_mutex
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * module part&n; */
DECL|function|alsa_seq_device_init
r_static
r_int
id|__init
id|alsa_seq_device_init
c_func
(paren
r_void
)paren
(brace
id|info_entry
op_assign
id|snd_info_create_module_entry
c_func
(paren
id|THIS_MODULE
comma
l_string|&quot;drivers&quot;
comma
id|snd_seq_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info_entry
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|info_entry-&gt;content
op_assign
id|SNDRV_INFO_CONTENT_TEXT
suffix:semicolon
id|info_entry-&gt;c.text.read_size
op_assign
l_int|2048
suffix:semicolon
id|info_entry-&gt;c.text.read
op_assign
id|snd_seq_device_info
suffix:semicolon
r_if
c_cond
(paren
id|snd_info_register
c_func
(paren
id|info_entry
)paren
OL
l_int|0
)paren
(brace
id|snd_info_free_entry
c_func
(paren
id|info_entry
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_seq_device_exit
r_static
r_void
id|__exit
id|alsa_seq_device_exit
c_func
(paren
r_void
)paren
(brace
id|remove_drivers
c_func
(paren
)paren
suffix:semicolon
id|snd_info_unregister
c_func
(paren
id|info_entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num_ops
)paren
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;drivers not released (%d)&bslash;n&quot;
comma
id|num_ops
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_seq_device_init
)paren
id|module_exit
c_func
(paren
id|alsa_seq_device_exit
)paren
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_device_load_drivers
)paren
suffix:semicolon
DECL|variable|EXPORT_SYMBOL
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_device_new
)paren
suffix:semicolon
DECL|variable|snd_seq_device_register_driver
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_device_register_driver
)paren
suffix:semicolon
DECL|variable|snd_seq_device_unregister_driver
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_device_unregister_driver
)paren
suffix:semicolon
eof
