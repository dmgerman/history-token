multiline_comment|/*&n; * OSS compatible sequencer driver&n; *&n; * MIDI device handlers&n; *&n; * Copyright (C) 1998,99 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &quot;seq_oss_midi.h&quot;
macro_line|#include &quot;seq_oss_readq.h&quot;
macro_line|#include &quot;seq_oss_timer.h&quot;
macro_line|#include &quot;seq_oss_event.h&quot;
macro_line|#include &lt;sound/seq_midi_event.h&gt;
macro_line|#include &quot;../seq_lock.h&quot;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n; * constants&n; */
DECL|macro|SNDRV_SEQ_OSS_MAX_MIDI_NAME
mdefine_line|#define SNDRV_SEQ_OSS_MAX_MIDI_NAME&t;30
multiline_comment|/*&n; * definition of midi device record&n; */
DECL|struct|seq_oss_midi_t
r_struct
id|seq_oss_midi_t
(brace
DECL|member|seq_device
r_int
id|seq_device
suffix:semicolon
multiline_comment|/* device number */
DECL|member|client
r_int
id|client
suffix:semicolon
multiline_comment|/* sequencer client number */
DECL|member|port
r_int
id|port
suffix:semicolon
multiline_comment|/* sequencer port number */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* port capability */
DECL|member|opened
r_int
id|opened
suffix:semicolon
multiline_comment|/* flag for opening */
DECL|member|name
r_int
r_char
id|name
(braket
id|SNDRV_SEQ_OSS_MAX_MIDI_NAME
)braket
suffix:semicolon
DECL|member|coder
id|snd_midi_event_t
op_star
id|coder
suffix:semicolon
multiline_comment|/* MIDI event coder */
DECL|member|devinfo
id|seq_oss_devinfo_t
op_star
id|devinfo
suffix:semicolon
multiline_comment|/* assigned OSSseq device */
DECL|member|use_lock
id|snd_use_lock_t
id|use_lock
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * midi device table&n; */
DECL|variable|max_midi_devs
r_static
r_int
id|max_midi_devs
suffix:semicolon
DECL|variable|midi_devs
r_static
id|seq_oss_midi_t
op_star
id|midi_devs
(braket
id|SNDRV_SEQ_OSS_MAX_MIDI_DEVS
)braket
suffix:semicolon
DECL|variable|register_lock
r_static
id|spinlock_t
id|register_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * prototypes&n; */
r_static
id|seq_oss_midi_t
op_star
id|get_mdev
c_func
(paren
r_int
id|dev
)paren
suffix:semicolon
r_static
id|seq_oss_midi_t
op_star
id|get_mididev
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
)paren
suffix:semicolon
r_static
r_int
id|send_synth_event
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|dev
)paren
suffix:semicolon
r_static
r_int
id|send_midi_event
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
id|snd_seq_event_t
op_star
id|ev
comma
id|seq_oss_midi_t
op_star
id|mdev
)paren
suffix:semicolon
multiline_comment|/*&n; * look up the existing ports&n; * this looks a very exhausting job.&n; */
r_int
id|__init
DECL|function|snd_seq_oss_midi_lookup_ports
id|snd_seq_oss_midi_lookup_ports
c_func
(paren
r_int
id|client
)paren
(brace
id|snd_seq_system_info_t
id|sysinfo
suffix:semicolon
id|snd_seq_client_info_t
id|clinfo
suffix:semicolon
id|snd_seq_port_info_t
id|pinfo
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|snd_seq_kernel_client_ctl
c_func
(paren
id|client
comma
id|SNDRV_SEQ_IOCTL_SYSTEM_INFO
comma
op_amp
id|sysinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
r_return
id|rc
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|clinfo
comma
l_int|0
comma
r_sizeof
(paren
id|clinfo
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|pinfo
comma
l_int|0
comma
r_sizeof
(paren
id|pinfo
)paren
)paren
suffix:semicolon
id|clinfo.client
op_assign
op_minus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|snd_seq_kernel_client_ctl
c_func
(paren
id|client
comma
id|SNDRV_SEQ_IOCTL_QUERY_NEXT_CLIENT
comma
op_amp
id|clinfo
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|clinfo.client
op_eq
id|client
)paren
r_continue
suffix:semicolon
multiline_comment|/* ignore myself */
id|pinfo.addr.client
op_assign
id|clinfo.client
suffix:semicolon
id|pinfo.addr.port
op_assign
op_minus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|snd_seq_kernel_client_ctl
c_func
(paren
id|client
comma
id|SNDRV_SEQ_IOCTL_QUERY_NEXT_PORT
comma
op_amp
id|pinfo
)paren
op_eq
l_int|0
)paren
id|snd_seq_oss_midi_check_new_port
c_func
(paren
op_amp
id|pinfo
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; */
r_static
id|seq_oss_midi_t
op_star
DECL|function|get_mdev
id|get_mdev
c_func
(paren
r_int
id|dev
)paren
(brace
id|seq_oss_midi_t
op_star
id|mdev
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
suffix:semicolon
id|mdev
op_assign
id|midi_devs
(braket
id|dev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|mdev
)paren
id|snd_use_lock_use
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|mdev
suffix:semicolon
)brace
multiline_comment|/*&n; * look for the identical slot&n; */
r_static
id|seq_oss_midi_t
op_star
DECL|function|find_slot
id|find_slot
c_func
(paren
r_int
id|client
comma
r_int
id|port
)paren
(brace
r_int
id|i
suffix:semicolon
id|seq_oss_midi_t
op_star
id|mdev
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
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
id|max_midi_devs
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mdev
op_assign
id|midi_devs
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|mdev
op_logical_and
id|mdev-&gt;client
op_eq
id|client
op_logical_and
id|mdev-&gt;port
op_eq
id|port
)paren
(brace
multiline_comment|/* found! */
id|snd_use_lock_use
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|mdev
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|macro|PERM_WRITE
mdefine_line|#define PERM_WRITE (SNDRV_SEQ_PORT_CAP_WRITE|SNDRV_SEQ_PORT_CAP_SUBS_WRITE)
DECL|macro|PERM_READ
mdefine_line|#define PERM_READ (SNDRV_SEQ_PORT_CAP_READ|SNDRV_SEQ_PORT_CAP_SUBS_READ)
multiline_comment|/*&n; * register a new port if it doesn&squot;t exist yet&n; */
r_int
DECL|function|snd_seq_oss_midi_check_new_port
id|snd_seq_oss_midi_check_new_port
c_func
(paren
id|snd_seq_port_info_t
op_star
id|pinfo
)paren
(brace
r_int
id|i
suffix:semicolon
id|seq_oss_midi_t
op_star
id|mdev
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;check for MIDI client %d port %d&bslash;n&quot;
comma
id|pinfo-&gt;addr.client
comma
id|pinfo-&gt;addr.port
)paren
)paren
suffix:semicolon
multiline_comment|/* the port must include generic midi */
r_if
c_cond
(paren
op_logical_neg
(paren
id|pinfo-&gt;type
op_amp
id|SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* either read or write subscribable */
r_if
c_cond
(paren
(paren
id|pinfo-&gt;capability
op_amp
id|PERM_WRITE
)paren
op_ne
id|PERM_WRITE
op_logical_and
(paren
id|pinfo-&gt;capability
op_amp
id|PERM_READ
)paren
op_ne
id|PERM_READ
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * look for the identical slot&n;&t; */
r_if
c_cond
(paren
(paren
id|mdev
op_assign
id|find_slot
c_func
(paren
id|pinfo-&gt;addr.client
comma
id|pinfo-&gt;addr.port
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* already exists */
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * allocate midi info record&n;&t; */
r_if
c_cond
(paren
(paren
id|mdev
op_assign
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
op_star
id|mdev
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;can&squot;t malloc midi info&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* copy the port information */
id|mdev-&gt;client
op_assign
id|pinfo-&gt;addr.client
suffix:semicolon
id|mdev-&gt;port
op_assign
id|pinfo-&gt;addr.port
suffix:semicolon
id|mdev-&gt;flags
op_assign
id|pinfo-&gt;capability
suffix:semicolon
id|mdev-&gt;opened
op_assign
l_int|0
suffix:semicolon
id|snd_use_lock_init
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
multiline_comment|/* copy and truncate the name of synth device */
id|strlcpy
c_func
(paren
id|mdev-&gt;name
comma
id|pinfo-&gt;name
comma
r_sizeof
(paren
id|mdev-&gt;name
)paren
)paren
suffix:semicolon
multiline_comment|/* create MIDI coder */
r_if
c_cond
(paren
id|snd_midi_event_new
c_func
(paren
id|MAX_MIDI_EVENT_BUF
comma
op_amp
id|mdev-&gt;coder
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;can&squot;t malloc midi coder&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mdev
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* OSS sequencer adds running status to all sequences */
id|snd_midi_event_no_status
c_func
(paren
id|mdev-&gt;coder
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * look for en empty slot&n;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
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
id|max_midi_devs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|midi_devs
(braket
id|i
)braket
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_ge
id|max_midi_devs
)paren
(brace
r_if
c_cond
(paren
id|max_midi_devs
op_ge
id|SNDRV_SEQ_OSS_MAX_MIDI_DEVS
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_midi_event_free
c_func
(paren
id|mdev-&gt;coder
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mdev
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|max_midi_devs
op_increment
suffix:semicolon
)brace
id|mdev-&gt;seq_device
op_assign
id|i
suffix:semicolon
id|midi_devs
(braket
id|mdev-&gt;seq_device
)braket
op_assign
id|mdev
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * release the midi device if it was registered&n; */
r_int
DECL|function|snd_seq_oss_midi_check_exit_port
id|snd_seq_oss_midi_check_exit_port
c_func
(paren
r_int
id|client
comma
r_int
id|port
)paren
(brace
id|seq_oss_midi_t
op_star
id|mdev
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|index
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mdev
op_assign
id|find_slot
c_func
(paren
id|client
comma
id|port
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
suffix:semicolon
id|midi_devs
(braket
id|mdev-&gt;seq_device
)braket
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
id|snd_use_lock_sync
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mdev-&gt;coder
)paren
id|snd_midi_event_free
c_func
(paren
id|mdev-&gt;coder
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mdev
)paren
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
id|max_midi_devs
op_minus
l_int|1
suffix:semicolon
id|index
op_ge
l_int|0
suffix:semicolon
id|index
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|midi_devs
(braket
id|index
)braket
)paren
r_break
suffix:semicolon
)brace
id|max_midi_devs
op_assign
id|index
op_plus
l_int|1
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * release the midi device if it was registered&n; */
r_void
DECL|function|snd_seq_oss_midi_clear_all
id|snd_seq_oss_midi_clear_all
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|seq_oss_midi_t
op_star
id|mdev
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
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
id|max_midi_devs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|mdev
op_assign
id|midi_devs
(braket
id|i
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|mdev-&gt;coder
)paren
id|snd_midi_event_free
c_func
(paren
id|mdev-&gt;coder
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mdev
)paren
suffix:semicolon
id|midi_devs
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|max_midi_devs
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * set up midi tables&n; */
r_void
DECL|function|snd_seq_oss_midi_setup
id|snd_seq_oss_midi_setup
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
)paren
(brace
id|dp-&gt;max_mididev
op_assign
id|max_midi_devs
suffix:semicolon
)brace
multiline_comment|/*&n; * clean up midi tables&n; */
r_void
DECL|function|snd_seq_oss_midi_cleanup
id|snd_seq_oss_midi_cleanup
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
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
id|dp-&gt;max_mididev
suffix:semicolon
id|i
op_increment
)paren
id|snd_seq_oss_midi_close
c_func
(paren
id|dp
comma
id|i
)paren
suffix:semicolon
id|dp-&gt;max_mididev
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * open all midi devices.  ignore errors.&n; */
r_void
DECL|function|snd_seq_oss_midi_open_all
id|snd_seq_oss_midi_open_all
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|file_mode
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
id|dp-&gt;max_mididev
suffix:semicolon
id|i
op_increment
)paren
id|snd_seq_oss_midi_open
c_func
(paren
id|dp
comma
id|i
comma
id|file_mode
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * get the midi device information&n; */
r_static
id|seq_oss_midi_t
op_star
DECL|function|get_mididev
id|get_mididev
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev
OL
l_int|0
op_logical_or
id|dev
op_ge
id|dp-&gt;max_mididev
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|get_mdev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * open the midi device if not opened yet&n; */
r_int
DECL|function|snd_seq_oss_midi_open
id|snd_seq_oss_midi_open
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
comma
r_int
id|fmode
)paren
(brace
r_int
id|perm
suffix:semicolon
id|seq_oss_midi_t
op_star
id|mdev
suffix:semicolon
id|snd_seq_port_subscribe_t
id|subs
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mdev
op_assign
id|get_mididev
c_func
(paren
id|dp
comma
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* already used? */
r_if
c_cond
(paren
id|mdev-&gt;opened
op_logical_and
id|mdev-&gt;devinfo
op_ne
id|dp
)paren
(brace
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|perm
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|is_write_mode
c_func
(paren
id|fmode
)paren
)paren
id|perm
op_or_assign
id|PERM_WRITE
suffix:semicolon
r_if
c_cond
(paren
id|is_read_mode
c_func
(paren
id|fmode
)paren
)paren
id|perm
op_or_assign
id|PERM_READ
suffix:semicolon
id|perm
op_and_assign
id|mdev-&gt;flags
suffix:semicolon
r_if
c_cond
(paren
id|perm
op_eq
l_int|0
)paren
(brace
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
multiline_comment|/* already opened? */
r_if
c_cond
(paren
(paren
id|mdev-&gt;opened
op_amp
id|perm
)paren
op_eq
id|perm
)paren
(brace
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|perm
op_and_assign
op_complement
id|mdev-&gt;opened
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|subs
comma
l_int|0
comma
r_sizeof
(paren
id|subs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|perm
op_amp
id|PERM_WRITE
)paren
(brace
id|subs.sender
op_assign
id|dp-&gt;addr
suffix:semicolon
id|subs.dest.client
op_assign
id|mdev-&gt;client
suffix:semicolon
id|subs.dest.port
op_assign
id|mdev-&gt;port
suffix:semicolon
r_if
c_cond
(paren
id|snd_seq_kernel_client_ctl
c_func
(paren
id|dp-&gt;cseq
comma
id|SNDRV_SEQ_IOCTL_SUBSCRIBE_PORT
comma
op_amp
id|subs
)paren
op_ge
l_int|0
)paren
id|mdev-&gt;opened
op_or_assign
id|PERM_WRITE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|perm
op_amp
id|PERM_READ
)paren
(brace
id|subs.sender.client
op_assign
id|mdev-&gt;client
suffix:semicolon
id|subs.sender.port
op_assign
id|mdev-&gt;port
suffix:semicolon
id|subs.dest
op_assign
id|dp-&gt;addr
suffix:semicolon
id|subs.flags
op_assign
id|SNDRV_SEQ_PORT_SUBS_TIMESTAMP
suffix:semicolon
id|subs.queue
op_assign
id|dp-&gt;queue
suffix:semicolon
multiline_comment|/* queue for timestamps */
r_if
c_cond
(paren
id|snd_seq_kernel_client_ctl
c_func
(paren
id|dp-&gt;cseq
comma
id|SNDRV_SEQ_IOCTL_SUBSCRIBE_PORT
comma
op_amp
id|subs
)paren
op_ge
l_int|0
)paren
id|mdev-&gt;opened
op_or_assign
id|PERM_READ
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mdev-&gt;opened
)paren
(brace
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|mdev-&gt;devinfo
op_assign
id|dp
suffix:semicolon
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * close the midi device if already opened&n; */
r_int
DECL|function|snd_seq_oss_midi_close
id|snd_seq_oss_midi_close
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
)paren
(brace
id|seq_oss_midi_t
op_star
id|mdev
suffix:semicolon
id|snd_seq_port_subscribe_t
id|subs
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mdev
op_assign
id|get_mididev
c_func
(paren
id|dp
comma
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mdev-&gt;opened
op_logical_or
id|mdev-&gt;devinfo
op_ne
id|dp
)paren
(brace
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|debug_printk
c_func
(paren
(paren
l_string|&quot;closing client %d port %d mode %d&bslash;n&quot;
comma
id|mdev-&gt;client
comma
id|mdev-&gt;port
comma
id|mdev-&gt;opened
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|subs
comma
l_int|0
comma
r_sizeof
(paren
id|subs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mdev-&gt;opened
op_amp
id|PERM_WRITE
)paren
(brace
id|subs.sender
op_assign
id|dp-&gt;addr
suffix:semicolon
id|subs.dest.client
op_assign
id|mdev-&gt;client
suffix:semicolon
id|subs.dest.port
op_assign
id|mdev-&gt;port
suffix:semicolon
id|snd_seq_kernel_client_ctl
c_func
(paren
id|dp-&gt;cseq
comma
id|SNDRV_SEQ_IOCTL_UNSUBSCRIBE_PORT
comma
op_amp
id|subs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mdev-&gt;opened
op_amp
id|PERM_READ
)paren
(brace
id|subs.sender.client
op_assign
id|mdev-&gt;client
suffix:semicolon
id|subs.sender.port
op_assign
id|mdev-&gt;port
suffix:semicolon
id|subs.dest
op_assign
id|dp-&gt;addr
suffix:semicolon
id|snd_seq_kernel_client_ctl
c_func
(paren
id|dp-&gt;cseq
comma
id|SNDRV_SEQ_IOCTL_UNSUBSCRIBE_PORT
comma
op_amp
id|subs
)paren
suffix:semicolon
)brace
id|mdev-&gt;opened
op_assign
l_int|0
suffix:semicolon
id|mdev-&gt;devinfo
op_assign
l_int|NULL
suffix:semicolon
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * change seq capability flags to file mode flags&n; */
r_int
DECL|function|snd_seq_oss_midi_filemode
id|snd_seq_oss_midi_filemode
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
)paren
(brace
id|seq_oss_midi_t
op_star
id|mdev
suffix:semicolon
r_int
id|mode
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mdev
op_assign
id|get_mididev
c_func
(paren
id|dp
comma
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|mode
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mdev-&gt;opened
op_amp
id|PERM_WRITE
)paren
id|mode
op_or_assign
id|SNDRV_SEQ_OSS_FILE_WRITE
suffix:semicolon
r_if
c_cond
(paren
id|mdev-&gt;opened
op_amp
id|PERM_READ
)paren
id|mode
op_or_assign
id|SNDRV_SEQ_OSS_FILE_READ
suffix:semicolon
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
r_return
id|mode
suffix:semicolon
)brace
multiline_comment|/*&n; * reset the midi device and close it:&n; * so far, only close the device.&n; */
r_void
DECL|function|snd_seq_oss_midi_reset
id|snd_seq_oss_midi_reset
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
)paren
(brace
id|seq_oss_midi_t
op_star
id|mdev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mdev
op_assign
id|get_mididev
c_func
(paren
id|dp
comma
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mdev-&gt;opened
)paren
(brace
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mdev-&gt;opened
op_amp
id|PERM_WRITE
)paren
(brace
id|snd_seq_event_t
id|ev
suffix:semicolon
r_int
id|c
suffix:semicolon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;resetting client %d port %d&bslash;n&quot;
comma
id|mdev-&gt;client
comma
id|mdev-&gt;port
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ev
comma
l_int|0
comma
r_sizeof
(paren
id|ev
)paren
)paren
suffix:semicolon
id|ev.dest.client
op_assign
id|mdev-&gt;client
suffix:semicolon
id|ev.dest.port
op_assign
id|mdev-&gt;port
suffix:semicolon
id|ev.queue
op_assign
id|dp-&gt;queue
suffix:semicolon
id|ev.source.port
op_assign
id|dp-&gt;port
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;seq_mode
op_eq
id|SNDRV_SEQ_OSS_MODE_SYNTH
)paren
(brace
id|ev.type
op_assign
id|SNDRV_SEQ_EVENT_SENSING
suffix:semicolon
id|snd_seq_oss_dispatch
c_func
(paren
id|dp
comma
op_amp
id|ev
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* active sensing */
)brace
r_for
c_loop
(paren
id|c
op_assign
l_int|0
suffix:semicolon
id|c
OL
l_int|16
suffix:semicolon
id|c
op_increment
)paren
(brace
id|ev.type
op_assign
id|SNDRV_SEQ_EVENT_CONTROLLER
suffix:semicolon
id|ev.data.control.channel
op_assign
id|c
suffix:semicolon
id|ev.data.control.param
op_assign
l_int|123
suffix:semicolon
id|snd_seq_oss_dispatch
c_func
(paren
id|dp
comma
op_amp
id|ev
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* all notes off */
r_if
c_cond
(paren
id|dp-&gt;seq_mode
op_eq
id|SNDRV_SEQ_OSS_MODE_MUSIC
)paren
(brace
id|ev.data.control.param
op_assign
l_int|121
suffix:semicolon
id|snd_seq_oss_dispatch
c_func
(paren
id|dp
comma
op_amp
id|ev
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* reset all controllers */
id|ev.type
op_assign
id|SNDRV_SEQ_EVENT_PITCHBEND
suffix:semicolon
id|ev.data.control.value
op_assign
l_int|0
suffix:semicolon
id|snd_seq_oss_dispatch
c_func
(paren
id|dp
comma
op_amp
id|ev
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* bender off */
)brace
)brace
)brace
singleline_comment|// snd_seq_oss_midi_close(dp, dev);
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * get client/port of the specified MIDI device&n; */
r_void
DECL|function|snd_seq_oss_midi_get_addr
id|snd_seq_oss_midi_get_addr
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
comma
id|snd_seq_addr_t
op_star
id|addr
)paren
(brace
id|seq_oss_midi_t
op_star
id|mdev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mdev
op_assign
id|get_mididev
c_func
(paren
id|dp
comma
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|addr-&gt;client
op_assign
id|mdev-&gt;client
suffix:semicolon
id|addr-&gt;port
op_assign
id|mdev-&gt;port
suffix:semicolon
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * input callback - this can be atomic&n; */
r_int
DECL|function|snd_seq_oss_midi_input
id|snd_seq_oss_midi_input
c_func
(paren
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|direct
comma
r_void
op_star
id|private_data
)paren
(brace
id|seq_oss_devinfo_t
op_star
id|dp
op_assign
(paren
id|seq_oss_devinfo_t
op_star
)paren
id|private_data
suffix:semicolon
id|seq_oss_midi_t
op_star
id|mdev
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;readq
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mdev
op_assign
id|find_slot
c_func
(paren
id|ev-&gt;source.client
comma
id|ev-&gt;source.port
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mdev-&gt;opened
op_amp
id|PERM_READ
)paren
)paren
(brace
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dp-&gt;seq_mode
op_eq
id|SNDRV_SEQ_OSS_MODE_MUSIC
)paren
id|rc
op_assign
id|send_synth_event
c_func
(paren
id|dp
comma
id|ev
comma
id|mdev-&gt;seq_device
)paren
suffix:semicolon
r_else
id|rc
op_assign
id|send_midi_event
c_func
(paren
id|dp
comma
id|ev
comma
id|mdev
)paren
suffix:semicolon
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * convert ALSA sequencer event to OSS synth event&n; */
r_static
r_int
DECL|function|send_synth_event
id|send_synth_event
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|dev
)paren
(brace
id|evrec_t
id|ossev
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ossev
comma
l_int|0
comma
r_sizeof
(paren
id|ossev
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ev-&gt;type
)paren
(brace
r_case
id|SNDRV_SEQ_EVENT_NOTEON
suffix:colon
id|ossev.v.cmd
op_assign
id|MIDI_NOTEON
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_SEQ_EVENT_NOTEOFF
suffix:colon
id|ossev.v.cmd
op_assign
id|MIDI_NOTEOFF
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_SEQ_EVENT_KEYPRESS
suffix:colon
id|ossev.v.cmd
op_assign
id|MIDI_KEY_PRESSURE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_SEQ_EVENT_CONTROLLER
suffix:colon
id|ossev.l.cmd
op_assign
id|MIDI_CTL_CHANGE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_SEQ_EVENT_PGMCHANGE
suffix:colon
id|ossev.l.cmd
op_assign
id|MIDI_PGM_CHANGE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_SEQ_EVENT_CHANPRESS
suffix:colon
id|ossev.l.cmd
op_assign
id|MIDI_CHN_PRESSURE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_SEQ_EVENT_PITCHBEND
suffix:colon
id|ossev.l.cmd
op_assign
id|MIDI_PITCH_BEND
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* not supported */
)brace
id|ossev.v.dev
op_assign
id|dev
suffix:semicolon
r_switch
c_cond
(paren
id|ev-&gt;type
)paren
(brace
r_case
id|SNDRV_SEQ_EVENT_NOTEON
suffix:colon
r_case
id|SNDRV_SEQ_EVENT_NOTEOFF
suffix:colon
r_case
id|SNDRV_SEQ_EVENT_KEYPRESS
suffix:colon
id|ossev.v.code
op_assign
id|EV_CHN_VOICE
suffix:semicolon
id|ossev.v.note
op_assign
id|ev-&gt;data.note.note
suffix:semicolon
id|ossev.v.parm
op_assign
id|ev-&gt;data.note.velocity
suffix:semicolon
id|ossev.v.chn
op_assign
id|ev-&gt;data.note.channel
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_SEQ_EVENT_CONTROLLER
suffix:colon
r_case
id|SNDRV_SEQ_EVENT_PGMCHANGE
suffix:colon
r_case
id|SNDRV_SEQ_EVENT_CHANPRESS
suffix:colon
id|ossev.l.code
op_assign
id|EV_CHN_COMMON
suffix:semicolon
id|ossev.l.p1
op_assign
id|ev-&gt;data.control.param
suffix:semicolon
id|ossev.l.val
op_assign
id|ev-&gt;data.control.value
suffix:semicolon
id|ossev.l.chn
op_assign
id|ev-&gt;data.control.channel
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_SEQ_EVENT_PITCHBEND
suffix:colon
id|ossev.l.code
op_assign
id|EV_CHN_COMMON
suffix:semicolon
id|ossev.l.val
op_assign
id|ev-&gt;data.control.value
op_plus
l_int|8192
suffix:semicolon
id|ossev.l.chn
op_assign
id|ev-&gt;data.control.channel
suffix:semicolon
r_break
suffix:semicolon
)brace
id|snd_seq_oss_readq_put_timestamp
c_func
(paren
id|dp-&gt;readq
comma
id|ev-&gt;time.tick
comma
id|dp-&gt;seq_mode
)paren
suffix:semicolon
id|snd_seq_oss_readq_put_event
c_func
(paren
id|dp-&gt;readq
comma
op_amp
id|ossev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * decode event and send MIDI bytes to read queue&n; */
r_static
r_int
DECL|function|send_midi_event
id|send_midi_event
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
id|snd_seq_event_t
op_star
id|ev
comma
id|seq_oss_midi_t
op_star
id|mdev
)paren
(brace
r_char
id|msg
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
id|snd_seq_oss_readq_put_timestamp
c_func
(paren
id|dp-&gt;readq
comma
id|ev-&gt;time.tick
comma
id|dp-&gt;seq_mode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dp-&gt;timer-&gt;running
)paren
id|len
op_assign
id|snd_seq_oss_timer_start
c_func
(paren
id|dp-&gt;timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ev-&gt;type
op_eq
id|SNDRV_SEQ_EVENT_SYSEX
)paren
(brace
r_if
c_cond
(paren
(paren
id|ev-&gt;flags
op_amp
id|SNDRV_SEQ_EVENT_LENGTH_MASK
)paren
op_eq
id|SNDRV_SEQ_EVENT_LENGTH_VARIABLE
)paren
id|snd_seq_oss_readq_puts
c_func
(paren
id|dp-&gt;readq
comma
id|mdev-&gt;seq_device
comma
id|ev-&gt;data.ext.ptr
comma
id|ev-&gt;data.ext.len
)paren
suffix:semicolon
)brace
r_else
(brace
id|len
op_assign
id|snd_midi_event_decode
c_func
(paren
id|mdev-&gt;coder
comma
id|msg
comma
r_sizeof
(paren
id|msg
)paren
comma
id|ev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
id|snd_seq_oss_readq_puts
c_func
(paren
id|dp-&gt;readq
comma
id|mdev-&gt;seq_device
comma
id|msg
comma
id|len
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * dump midi data&n; * return 0 : enqueued&n; *        non-zero : invalid - ignored&n; */
r_int
DECL|function|snd_seq_oss_midi_putc
id|snd_seq_oss_midi_putc
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
comma
r_int
r_char
id|c
comma
id|snd_seq_event_t
op_star
id|ev
)paren
(brace
id|seq_oss_midi_t
op_star
id|mdev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mdev
op_assign
id|get_mididev
c_func
(paren
id|dp
comma
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|snd_midi_event_encode_byte
c_func
(paren
id|mdev-&gt;coder
comma
id|c
comma
id|ev
)paren
OG
l_int|0
)paren
(brace
id|snd_seq_oss_fill_addr
c_func
(paren
id|dp
comma
id|ev
comma
id|mdev-&gt;client
comma
id|mdev-&gt;port
)paren
suffix:semicolon
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; * create OSS compatible midi_info record&n; */
r_int
DECL|function|snd_seq_oss_midi_make_info
id|snd_seq_oss_midi_make_info
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
comma
r_struct
id|midi_info
op_star
id|inf
)paren
(brace
id|seq_oss_midi_t
op_star
id|mdev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mdev
op_assign
id|get_mididev
c_func
(paren
id|dp
comma
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|inf-&gt;device
op_assign
id|dev
suffix:semicolon
id|inf-&gt;dev_type
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* FIXME: ?? */
id|inf-&gt;capabilities
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* FIXME: ?? */
id|strlcpy
c_func
(paren
id|inf-&gt;name
comma
id|mdev-&gt;name
comma
r_sizeof
(paren
id|inf-&gt;name
)paren
)paren
suffix:semicolon
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * proc interface&n; */
r_static
r_char
op_star
DECL|function|capmode_str
id|capmode_str
c_func
(paren
r_int
id|val
)paren
(brace
id|val
op_and_assign
id|PERM_READ
op_or
id|PERM_WRITE
suffix:semicolon
r_if
c_cond
(paren
id|val
op_eq
(paren
id|PERM_READ
op_or
id|PERM_WRITE
)paren
)paren
r_return
l_string|&quot;read/write&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|val
op_eq
id|PERM_READ
)paren
r_return
l_string|&quot;read&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|val
op_eq
id|PERM_WRITE
)paren
r_return
l_string|&quot;write&quot;
suffix:semicolon
r_else
r_return
l_string|&quot;none&quot;
suffix:semicolon
)brace
r_void
DECL|function|snd_seq_oss_midi_info_read
id|snd_seq_oss_midi_info_read
c_func
(paren
id|snd_info_buffer_t
op_star
id|buf
)paren
(brace
r_int
id|i
suffix:semicolon
id|seq_oss_midi_t
op_star
id|mdev
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;nNumber of MIDI devices: %d&bslash;n&quot;
comma
id|max_midi_devs
)paren
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
id|max_midi_devs
suffix:semicolon
id|i
op_increment
)paren
(brace
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;nmidi %d: &quot;
comma
id|i
)paren
suffix:semicolon
id|mdev
op_assign
id|get_mdev
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mdev
op_eq
l_int|NULL
)paren
(brace
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;*empty*&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;[%s] ALSA port %d:%d&bslash;n&quot;
comma
id|mdev-&gt;name
comma
id|mdev-&gt;client
comma
id|mdev-&gt;port
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;  capability %s / opened %s&bslash;n&quot;
comma
id|capmode_str
c_func
(paren
id|mdev-&gt;flags
)paren
comma
id|capmode_str
c_func
(paren
id|mdev-&gt;opened
)paren
)paren
suffix:semicolon
id|snd_use_lock_free
c_func
(paren
op_amp
id|mdev-&gt;use_lock
)paren
suffix:semicolon
)brace
)brace
eof
