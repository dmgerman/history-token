multiline_comment|/*&n; *  ALSA sequencer main module&n; *  Copyright (c) 1998-1999 by Frank van de Pol &lt;fvdpol@coil.demon.nl&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
macro_line|#include &lt;sound/seq_kernel.h&gt;
macro_line|#include &quot;seq_clientmgr.h&quot;
macro_line|#include &quot;seq_memory.h&quot;
macro_line|#include &quot;seq_queue.h&quot;
macro_line|#include &quot;seq_lock.h&quot;
macro_line|#include &quot;seq_timer.h&quot;
macro_line|#include &quot;seq_system.h&quot;
macro_line|#include &quot;seq_info.h&quot;
macro_line|#include &lt;sound/seq_device.h&gt;
DECL|variable|seq_client_load
r_int
id|seq_client_load
(braket
l_int|64
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
l_int|63
)braket
op_assign
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|seq_default_timer_class
r_int
id|seq_default_timer_class
op_assign
id|SNDRV_TIMER_CLASS_GLOBAL
suffix:semicolon
DECL|variable|seq_default_timer_sclass
r_int
id|seq_default_timer_sclass
op_assign
id|SNDRV_TIMER_SCLASS_NONE
suffix:semicolon
DECL|variable|seq_default_timer_card
r_int
id|seq_default_timer_card
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|seq_default_timer_device
r_int
id|seq_default_timer_device
op_assign
id|SNDRV_TIMER_GLOBAL_SYSTEM
suffix:semicolon
DECL|variable|seq_default_timer_subdevice
r_int
id|seq_default_timer_subdevice
op_assign
l_int|0
suffix:semicolon
DECL|variable|seq_default_timer_resolution
r_int
id|seq_default_timer_resolution
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Hz */
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Frank van de Pol &lt;fvdpol@coil.demon.nl&gt;, Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Advanced Linux Sound Architecture sequencer.&quot;
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
DECL|variable|boot_devs
r_static
r_int
id|boot_devs
suffix:semicolon
id|module_param_array
c_func
(paren
id|seq_client_load
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
id|seq_client_load
comma
l_string|&quot;The numbers of global (system) clients to load through kmod.&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|seq_default_timer_class
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|seq_default_timer_class
comma
l_string|&quot;The default timer class.&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|seq_default_timer_sclass
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|seq_default_timer_sclass
comma
l_string|&quot;The default timer slave class.&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|seq_default_timer_card
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|seq_default_timer_card
comma
l_string|&quot;The default timer card number.&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|seq_default_timer_device
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|seq_default_timer_device
comma
l_string|&quot;The default timer device number.&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|seq_default_timer_subdevice
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|seq_default_timer_subdevice
comma
l_string|&quot;The default timer subdevice number.&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|seq_default_timer_resolution
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|seq_default_timer_resolution
comma
l_string|&quot;The default timer resolution in Hz.&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; *  INIT PART&n; */
DECL|function|alsa_seq_init
r_static
r_int
id|__init
id|alsa_seq_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|client_init_data
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* init memory, room for selected events */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_sequencer_memory_init
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* init event queues */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_seq_queues_init
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* register sequencer device */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_sequencer_device_init
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* register proc interface */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_seq_info_init
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* register our internal client */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_seq_system_client_init
c_func
(paren
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
DECL|function|alsa_seq_exit
r_static
r_void
id|__exit
id|alsa_seq_exit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* unregister our internal client */
id|snd_seq_system_client_done
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* unregister proc interface */
id|snd_seq_info_done
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* delete timing queues */
id|snd_seq_queues_delete
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* unregister sequencer device */
id|snd_sequencer_device_done
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* release event memory */
id|snd_sequencer_memory_done
c_func
(paren
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_seq_init
)paren
id|module_exit
c_func
(paren
id|alsa_seq_exit
)paren
multiline_comment|/* seq_clientmgr.c */
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_create_kernel_client
)paren
suffix:semicolon
DECL|variable|EXPORT_SYMBOL
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_delete_kernel_client
)paren
suffix:semicolon
DECL|variable|snd_seq_kernel_client_enqueue
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_kernel_client_enqueue
)paren
suffix:semicolon
DECL|variable|snd_seq_kernel_client_enqueue_blocking
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_kernel_client_enqueue_blocking
)paren
suffix:semicolon
DECL|variable|snd_seq_kernel_client_dispatch
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_kernel_client_dispatch
)paren
suffix:semicolon
DECL|variable|snd_seq_kernel_client_ctl
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_kernel_client_ctl
)paren
suffix:semicolon
DECL|variable|snd_seq_kernel_client_write_poll
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_kernel_client_write_poll
)paren
suffix:semicolon
multiline_comment|/* seq_memory.c */
DECL|variable|snd_seq_expand_var_event
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_expand_var_event
)paren
suffix:semicolon
DECL|variable|snd_seq_dump_var_event
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_dump_var_event
)paren
suffix:semicolon
multiline_comment|/* seq_ports.c */
DECL|variable|snd_seq_event_port_attach
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_event_port_attach
)paren
suffix:semicolon
DECL|variable|snd_seq_event_port_detach
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_event_port_detach
)paren
suffix:semicolon
multiline_comment|/* seq_lock.c */
macro_line|#if defined(CONFIG_SMP) || defined(CONFIG_SND_DEBUG)
multiline_comment|/*EXPORT_SYMBOL(snd_seq_sleep_in_lock);*/
multiline_comment|/*EXPORT_SYMBOL(snd_seq_sleep_timeout_in_lock);*/
DECL|variable|snd_use_lock_sync_helper
id|EXPORT_SYMBOL
c_func
(paren
id|snd_use_lock_sync_helper
)paren
suffix:semicolon
macro_line|#endif
eof
