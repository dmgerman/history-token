multiline_comment|/*&n; * sound/v_midi.c&n; *&n; * The low level driver for the Sound Blaster DS chips.&n; *&n; *&n; * Copyright (C) by Hannu Savolainen 1993-1996&n; *&n; * USS/Lite for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; * ??&n; *&n; * Changes&n; *&t;Alan Cox&t;&t;Modularisation, changed memory allocations&n; *&t;Christoph Hellwig&t;Adapted to module_init/module_exit&n; *&n; * Status&n; *&t;Untested&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &quot;sound_config.h&quot;
macro_line|#include &quot;v_midi.h&quot;
DECL|variable|v_devc
r_static
id|vmidi_devc
op_star
id|v_devc
(braket
l_int|2
)braket
op_assign
(brace
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|midi1
DECL|variable|midi2
r_static
r_int
id|midi1
comma
id|midi2
suffix:semicolon
DECL|variable|midi_mem
r_static
r_void
op_star
id|midi_mem
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * The DSP channel can be used either for input or output. Variable&n; * &squot;sb_irq_mode&squot; will be set when the program calls read or write first time&n; * after open. Current version doesn&squot;t support mode changes without closing&n; * and reopening the device. Support for this feature may be implemented in a&n; * future version of this driver.&n; */
DECL|variable|midi_input_intr
r_void
(paren
op_star
id|midi_input_intr
)paren
(paren
r_int
id|dev
comma
r_int
r_char
id|data
)paren
suffix:semicolon
DECL|function|v_midi_open
r_static
r_int
id|v_midi_open
(paren
r_int
id|dev
comma
r_int
id|mode
comma
r_void
(paren
op_star
id|input
)paren
(paren
r_int
id|dev
comma
r_int
r_char
id|data
)paren
comma
r_void
(paren
op_star
id|output
)paren
(paren
r_int
id|dev
)paren
)paren
(brace
id|vmidi_devc
op_star
id|devc
op_assign
id|midi_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|devc
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|devc
op_eq
l_int|NULL
)paren
r_return
op_minus
(paren
id|ENXIO
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|devc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devc-&gt;opened
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|devc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
(paren
id|EBUSY
)paren
suffix:semicolon
)brace
id|devc-&gt;opened
op_assign
l_int|1
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|devc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|devc-&gt;intr_active
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_amp
id|OPEN_READ
)paren
(brace
id|devc-&gt;input_opened
op_assign
l_int|1
suffix:semicolon
id|devc-&gt;midi_input_intr
op_assign
id|input
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|v_midi_close
r_static
r_void
id|v_midi_close
(paren
r_int
id|dev
)paren
(brace
id|vmidi_devc
op_star
id|devc
op_assign
id|midi_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|devc
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|devc
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|devc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|devc-&gt;intr_active
op_assign
l_int|0
suffix:semicolon
id|devc-&gt;input_opened
op_assign
l_int|0
suffix:semicolon
id|devc-&gt;opened
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|devc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|v_midi_out
r_static
r_int
id|v_midi_out
(paren
r_int
id|dev
comma
r_int
r_char
id|midi_byte
)paren
(brace
id|vmidi_devc
op_star
id|devc
op_assign
id|midi_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|devc
suffix:semicolon
id|vmidi_devc
op_star
id|pdevc
suffix:semicolon
r_if
c_cond
(paren
id|devc
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|pdevc
op_assign
id|midi_devs
(braket
id|devc-&gt;pair_mididev
)braket
op_member_access_from_pointer
id|devc
suffix:semicolon
r_if
c_cond
(paren
id|pdevc-&gt;input_opened
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|MIDIbuf_avail
c_func
(paren
id|pdevc-&gt;my_mididev
)paren
OG
l_int|500
)paren
r_return
l_int|0
suffix:semicolon
id|pdevc-&gt;midi_input_intr
(paren
id|pdevc-&gt;my_mididev
comma
id|midi_byte
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|v_midi_start_read
r_static
r_inline
r_int
id|v_midi_start_read
(paren
r_int
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|v_midi_end_read
r_static
r_int
id|v_midi_end_read
(paren
r_int
id|dev
)paren
(brace
id|vmidi_devc
op_star
id|devc
op_assign
id|midi_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|devc
suffix:semicolon
r_if
c_cond
(paren
id|devc
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|devc-&gt;intr_active
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* why -EPERM and not -EINVAL?? */
DECL|function|v_midi_ioctl
r_static
r_inline
r_int
id|v_midi_ioctl
(paren
r_int
id|dev
comma
r_int
id|cmd
comma
r_void
id|__user
op_star
id|arg
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
DECL|macro|MIDI_SYNTH_NAME
mdefine_line|#define MIDI_SYNTH_NAME&t;&quot;Loopback MIDI&quot;
DECL|macro|MIDI_SYNTH_CAPS
mdefine_line|#define MIDI_SYNTH_CAPS&t;SYNTH_CAP_INPUT
macro_line|#include &quot;midi_synth.h&quot;
DECL|variable|v_midi_operations
r_static
r_struct
id|midi_operations
id|v_midi_operations
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|info
op_assign
(brace
l_string|&quot;Loopback MIDI Port 1&quot;
comma
l_int|0
comma
l_int|0
comma
id|SNDCARD_VMIDI
)brace
comma
dot
id|converter
op_assign
op_amp
id|std_midi_synth
comma
dot
id|in_info
op_assign
(brace
l_int|0
)brace
comma
dot
id|open
op_assign
id|v_midi_open
comma
dot
id|close
op_assign
id|v_midi_close
comma
dot
id|ioctl
op_assign
id|v_midi_ioctl
comma
dot
id|outputc
op_assign
id|v_midi_out
comma
dot
id|start_read
op_assign
id|v_midi_start_read
comma
dot
id|end_read
op_assign
id|v_midi_end_read
comma
)brace
suffix:semicolon
DECL|variable|v_midi_operations2
r_static
r_struct
id|midi_operations
id|v_midi_operations2
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|info
op_assign
(brace
l_string|&quot;Loopback MIDI Port 2&quot;
comma
l_int|0
comma
l_int|0
comma
id|SNDCARD_VMIDI
)brace
comma
dot
id|converter
op_assign
op_amp
id|std_midi_synth
comma
dot
id|in_info
op_assign
(brace
l_int|0
)brace
comma
dot
id|open
op_assign
id|v_midi_open
comma
dot
id|close
op_assign
id|v_midi_close
comma
dot
id|ioctl
op_assign
id|v_midi_ioctl
comma
dot
id|outputc
op_assign
id|v_midi_out
comma
dot
id|start_read
op_assign
id|v_midi_start_read
comma
dot
id|end_read
op_assign
id|v_midi_end_read
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;We kmalloc just one of these - it makes life simpler and the code&n; *&t;cleaner and the memory handling far more efficient&n; */
DECL|struct|vmidi_memory
r_struct
id|vmidi_memory
(brace
multiline_comment|/* Must be first */
DECL|member|m_ops
r_struct
id|midi_operations
id|m_ops
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|s_ops
r_struct
id|synth_operations
id|s_ops
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|v_ops
r_struct
id|vmidi_devc
id|v_ops
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|attach_v_midi
r_static
r_void
id|__init
id|attach_v_midi
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_struct
id|vmidi_memory
op_star
id|m
suffix:semicolon
multiline_comment|/* printk(&quot;Attaching v_midi device.....&bslash;n&quot;); */
id|midi1
op_assign
id|sound_alloc_mididev
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|midi1
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;v_midi: Too many midi devices detected&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|m
op_assign
(paren
r_struct
id|vmidi_memory
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|vmidi_memory
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Loopback MIDI: Failed to allocate memory&bslash;n&quot;
)paren
suffix:semicolon
id|sound_unload_mididev
c_func
(paren
id|midi1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|midi_mem
op_assign
id|m
suffix:semicolon
id|midi_devs
(braket
id|midi1
)braket
op_assign
op_amp
id|m-&gt;m_ops
(braket
l_int|0
)braket
suffix:semicolon
id|midi2
op_assign
id|sound_alloc_mididev
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|midi2
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;v_midi: Too many midi devices detected&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|m
)paren
suffix:semicolon
id|sound_unload_mididev
c_func
(paren
id|midi1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|midi_devs
(braket
id|midi2
)braket
op_assign
op_amp
id|m-&gt;m_ops
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* printk(&quot;VMIDI1: %d   VMIDI2: %d&bslash;n&quot;,midi1,midi2); */
multiline_comment|/* for MIDI-1 */
id|v_devc
(braket
l_int|0
)braket
op_assign
op_amp
id|m-&gt;v_ops
(braket
l_int|0
)braket
suffix:semicolon
id|memcpy
(paren
(paren
r_char
op_star
)paren
id|midi_devs
(braket
id|midi1
)braket
comma
(paren
r_char
op_star
)paren
op_amp
id|v_midi_operations
comma
r_sizeof
(paren
r_struct
id|midi_operations
)paren
)paren
suffix:semicolon
id|v_devc
(braket
l_int|0
)braket
op_member_access_from_pointer
id|my_mididev
op_assign
id|midi1
suffix:semicolon
id|v_devc
(braket
l_int|0
)braket
op_member_access_from_pointer
id|pair_mididev
op_assign
id|midi2
suffix:semicolon
id|v_devc
(braket
l_int|0
)braket
op_member_access_from_pointer
id|opened
op_assign
id|v_devc
(braket
l_int|0
)braket
op_member_access_from_pointer
id|input_opened
op_assign
l_int|0
suffix:semicolon
id|v_devc
(braket
l_int|0
)braket
op_member_access_from_pointer
id|intr_active
op_assign
l_int|0
suffix:semicolon
id|v_devc
(braket
l_int|0
)braket
op_member_access_from_pointer
id|midi_input_intr
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|v_devc
(braket
l_int|0
)braket
op_member_access_from_pointer
id|lock
)paren
suffix:semicolon
id|midi_devs
(braket
id|midi1
)braket
op_member_access_from_pointer
id|devc
op_assign
id|v_devc
(braket
l_int|0
)braket
suffix:semicolon
id|midi_devs
(braket
id|midi1
)braket
op_member_access_from_pointer
id|converter
op_assign
op_amp
id|m-&gt;s_ops
(braket
l_int|0
)braket
suffix:semicolon
id|std_midi_synth.midi_dev
op_assign
id|midi1
suffix:semicolon
id|memcpy
(paren
(paren
r_char
op_star
)paren
id|midi_devs
(braket
id|midi1
)braket
op_member_access_from_pointer
id|converter
comma
(paren
r_char
op_star
)paren
op_amp
id|std_midi_synth
comma
r_sizeof
(paren
r_struct
id|synth_operations
)paren
)paren
suffix:semicolon
id|midi_devs
(braket
id|midi1
)braket
op_member_access_from_pointer
id|converter-&gt;id
op_assign
l_string|&quot;V_MIDI 1&quot;
suffix:semicolon
multiline_comment|/* for MIDI-2 */
id|v_devc
(braket
l_int|1
)braket
op_assign
op_amp
id|m-&gt;v_ops
(braket
l_int|1
)braket
suffix:semicolon
id|memcpy
(paren
(paren
r_char
op_star
)paren
id|midi_devs
(braket
id|midi2
)braket
comma
(paren
r_char
op_star
)paren
op_amp
id|v_midi_operations2
comma
r_sizeof
(paren
r_struct
id|midi_operations
)paren
)paren
suffix:semicolon
id|v_devc
(braket
l_int|1
)braket
op_member_access_from_pointer
id|my_mididev
op_assign
id|midi2
suffix:semicolon
id|v_devc
(braket
l_int|1
)braket
op_member_access_from_pointer
id|pair_mididev
op_assign
id|midi1
suffix:semicolon
id|v_devc
(braket
l_int|1
)braket
op_member_access_from_pointer
id|opened
op_assign
id|v_devc
(braket
l_int|1
)braket
op_member_access_from_pointer
id|input_opened
op_assign
l_int|0
suffix:semicolon
id|v_devc
(braket
l_int|1
)braket
op_member_access_from_pointer
id|intr_active
op_assign
l_int|0
suffix:semicolon
id|v_devc
(braket
l_int|1
)braket
op_member_access_from_pointer
id|midi_input_intr
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|v_devc
(braket
l_int|1
)braket
op_member_access_from_pointer
id|lock
)paren
suffix:semicolon
id|midi_devs
(braket
id|midi2
)braket
op_member_access_from_pointer
id|devc
op_assign
id|v_devc
(braket
l_int|1
)braket
suffix:semicolon
id|midi_devs
(braket
id|midi2
)braket
op_member_access_from_pointer
id|converter
op_assign
op_amp
id|m-&gt;s_ops
(braket
l_int|1
)braket
suffix:semicolon
id|std_midi_synth.midi_dev
op_assign
id|midi2
suffix:semicolon
id|memcpy
(paren
(paren
r_char
op_star
)paren
id|midi_devs
(braket
id|midi2
)braket
op_member_access_from_pointer
id|converter
comma
(paren
r_char
op_star
)paren
op_amp
id|std_midi_synth
comma
r_sizeof
(paren
r_struct
id|synth_operations
)paren
)paren
suffix:semicolon
id|midi_devs
(braket
id|midi2
)braket
op_member_access_from_pointer
id|converter-&gt;id
op_assign
l_string|&quot;V_MIDI 2&quot;
suffix:semicolon
id|sequencer_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* printk(&quot;Attached v_midi device&bslash;n&quot;); */
)brace
DECL|function|probe_v_midi
r_static
r_inline
r_int
id|__init
id|probe_v_midi
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_return
l_int|1
suffix:semicolon
multiline_comment|/* always OK */
)brace
DECL|function|unload_v_midi
r_static
r_void
id|__exit
id|unload_v_midi
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
id|sound_unload_mididev
c_func
(paren
id|midi1
)paren
suffix:semicolon
id|sound_unload_mididev
c_func
(paren
id|midi2
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midi_mem
)paren
suffix:semicolon
)brace
DECL|variable|cfg
r_static
r_struct
id|address_info
id|cfg
suffix:semicolon
multiline_comment|/* dummy */
DECL|function|init_vmidi
r_static
r_int
id|__init
id|init_vmidi
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;MIDI Loopback device driver&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|probe_v_midi
c_func
(paren
op_amp
id|cfg
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|attach_v_midi
c_func
(paren
op_amp
id|cfg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_vmidi
r_static
r_void
id|__exit
id|cleanup_vmidi
c_func
(paren
r_void
)paren
(brace
id|unload_v_midi
c_func
(paren
op_amp
id|cfg
)paren
suffix:semicolon
)brace
DECL|variable|init_vmidi
id|module_init
c_func
(paren
id|init_vmidi
)paren
suffix:semicolon
DECL|variable|cleanup_vmidi
id|module_exit
c_func
(paren
id|cleanup_vmidi
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
