multiline_comment|/*&n; **********************************************************************&n; *     midi.c - /dev/midi interface for emu10k1 driver&n; *     Copyright 1999, 2000 Creative Labs, Inc.&n; *&n; **********************************************************************&n; *&n; *     Date                 Author          Summary of changes&n; *     ----                 ------          ------------------&n; *     October 20, 1999     Bertrand Lee    base code release&n; *&n; **********************************************************************&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *     GNU General Public License for more details.&n; *&n; *     You should have received a copy of the GNU General Public&n; *     License along with this program; if not, write to the Free&n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,&n; *     USA.&n; *&n; **********************************************************************&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;hwaccess.h&quot;
macro_line|#include &quot;cardmo.h&quot;
macro_line|#include &quot;cardmi.h&quot;
macro_line|#include &quot;midi.h&quot;
macro_line|#ifdef EMU10K1_SEQUENCER
macro_line|#include &quot;../sound_config.h&quot;
macro_line|#endif
r_static
id|spinlock_t
id|midi_spinlock
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|init_midi_hdr
r_static
r_void
id|init_midi_hdr
c_func
(paren
r_struct
id|midi_hdr
op_star
id|midihdr
)paren
(brace
id|midihdr-&gt;bufferlength
op_assign
id|MIDIIN_BUFLEN
suffix:semicolon
id|midihdr-&gt;bytesrecorded
op_assign
l_int|0
suffix:semicolon
id|midihdr-&gt;flags
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|midiin_add_buffer
r_static
r_int
id|midiin_add_buffer
c_func
(paren
r_struct
id|emu10k1_mididevice
op_star
id|midi_dev
comma
r_struct
id|midi_hdr
op_star
op_star
id|midihdrptr
)paren
(brace
r_struct
id|midi_hdr
op_star
id|midihdr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|midihdr
op_assign
(paren
r_struct
id|midi_hdr
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|midi_hdr
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|ERROR
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|init_midi_hdr
c_func
(paren
id|midihdr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|midihdr-&gt;data
op_assign
(paren
id|u8
op_star
)paren
id|kmalloc
c_func
(paren
id|MIDIIN_BUFLEN
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|ERROR
c_func
(paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midihdr
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|emu10k1_mpuin_add_buffer
c_func
(paren
id|midi_dev-&gt;card-&gt;mpuin
comma
id|midihdr
)paren
OL
l_int|0
)paren
(brace
id|ERROR
c_func
(paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midihdr-&gt;data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midihdr
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
op_star
id|midihdrptr
op_assign
id|midihdr
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|midihdr-&gt;list
comma
op_amp
id|midi_dev-&gt;mid_hdrs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu10k1_midi_open
r_static
r_int
id|emu10k1_midi_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|minor
op_assign
id|iminor
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|emu10k1_card
op_star
id|card
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|emu10k1_mididevice
op_star
id|midi_dev
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_midi_open()&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Check for correct device to open */
id|list_for_each
c_func
(paren
id|entry
comma
op_amp
id|emu10k1_devs
)paren
(brace
id|card
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|emu10k1_card
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;midi_dev
op_eq
id|minor
)paren
r_goto
id|match
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
id|match
suffix:colon
macro_line|#ifdef EMU10K1_SEQUENCER
r_if
c_cond
(paren
id|card-&gt;seq_mididev
)paren
multiline_comment|/* card is opened by sequencer */
r_return
op_minus
id|EBUSY
suffix:semicolon
macro_line|#endif
multiline_comment|/* Wait for device to become free */
id|down
c_func
(paren
op_amp
id|card-&gt;open_sem
)paren
suffix:semicolon
r_while
c_loop
(paren
id|card-&gt;open_mode
op_amp
(paren
id|file-&gt;f_mode
op_lshift
id|FMODE_MIDI_SHIFT
)paren
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
(brace
id|up
c_func
(paren
op_amp
id|card-&gt;open_sem
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|card-&gt;open_sem
)paren
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|card-&gt;open_wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|card-&gt;open_sem
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|midi_dev
op_assign
(paren
r_struct
id|emu10k1_mididevice
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|midi_dev
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|midi_dev-&gt;card
op_assign
id|card
suffix:semicolon
id|midi_dev-&gt;mistate
op_assign
id|MIDIIN_STATE_STOPPED
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|midi_dev-&gt;oWait
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|midi_dev-&gt;iWait
)paren
suffix:semicolon
id|midi_dev-&gt;ird
op_assign
l_int|0
suffix:semicolon
id|midi_dev-&gt;iwr
op_assign
l_int|0
suffix:semicolon
id|midi_dev-&gt;icnt
op_assign
l_int|0
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|midi_dev-&gt;mid_hdrs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
(brace
r_struct
id|midi_openinfo
id|dsCardMidiOpenInfo
suffix:semicolon
r_struct
id|midi_hdr
op_star
id|midihdr1
suffix:semicolon
r_struct
id|midi_hdr
op_star
id|midihdr2
suffix:semicolon
id|dsCardMidiOpenInfo.refdata
op_assign
(paren
r_int
r_int
)paren
id|midi_dev
suffix:semicolon
r_if
c_cond
(paren
id|emu10k1_mpuin_open
c_func
(paren
id|card
comma
op_amp
id|dsCardMidiOpenInfo
)paren
OL
l_int|0
)paren
(brace
id|ERROR
c_func
(paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midi_dev
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Add two buffers to receive sysex buffer */
r_if
c_cond
(paren
id|midiin_add_buffer
c_func
(paren
id|midi_dev
comma
op_amp
id|midihdr1
)paren
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|midi_dev
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
id|midiin_add_buffer
c_func
(paren
id|midi_dev
comma
op_amp
id|midihdr2
)paren
OL
l_int|0
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|midihdr1-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midihdr1-&gt;data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midihdr1
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midi_dev
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
(brace
r_struct
id|midi_openinfo
id|dsCardMidiOpenInfo
suffix:semicolon
id|dsCardMidiOpenInfo.refdata
op_assign
(paren
r_int
r_int
)paren
id|midi_dev
suffix:semicolon
r_if
c_cond
(paren
id|emu10k1_mpuout_open
c_func
(paren
id|card
comma
op_amp
id|dsCardMidiOpenInfo
)paren
OL
l_int|0
)paren
(brace
id|ERROR
c_func
(paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midi_dev
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
id|file-&gt;private_data
op_assign
(paren
r_void
op_star
)paren
id|midi_dev
suffix:semicolon
id|card-&gt;open_mode
op_or_assign
(paren
id|file-&gt;f_mode
op_lshift
id|FMODE_MIDI_SHIFT
)paren
op_amp
(paren
id|FMODE_MIDI_READ
op_or
id|FMODE_MIDI_WRITE
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|card-&gt;open_sem
)paren
suffix:semicolon
r_return
id|nonseekable_open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
)brace
DECL|function|emu10k1_midi_release
r_static
r_int
id|emu10k1_midi_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|emu10k1_mididevice
op_star
id|midi_dev
op_assign
(paren
r_struct
id|emu10k1_mididevice
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_struct
id|emu10k1_card
op_star
id|card
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|card
op_assign
id|midi_dev-&gt;card
suffix:semicolon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_midi_release()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
op_logical_and
(paren
id|card-&gt;mpuout-&gt;firstmidiq
op_ne
l_int|NULL
)paren
)paren
(brace
id|DPF
c_func
(paren
l_int|4
comma
l_string|&quot;Cannot close - buffers not empty&bslash;n&quot;
)paren
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|midi_dev-&gt;oWait
)paren
suffix:semicolon
)brace
)brace
id|emu10k1_mpuout_close
c_func
(paren
id|card
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
(brace
r_struct
id|midi_hdr
op_star
id|midihdr
suffix:semicolon
r_if
c_cond
(paren
id|midi_dev-&gt;mistate
op_eq
id|MIDIIN_STATE_STARTED
)paren
(brace
id|emu10k1_mpuin_stop
c_func
(paren
id|card
)paren
suffix:semicolon
id|midi_dev-&gt;mistate
op_assign
id|MIDIIN_STATE_STOPPED
suffix:semicolon
)brace
id|emu10k1_mpuin_reset
c_func
(paren
id|card
)paren
suffix:semicolon
id|emu10k1_mpuin_close
c_func
(paren
id|card
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|midi_dev-&gt;mid_hdrs
)paren
)paren
(brace
id|midihdr
op_assign
id|list_entry
c_func
(paren
id|midi_dev-&gt;mid_hdrs.next
comma
r_struct
id|midi_hdr
comma
id|list
)paren
suffix:semicolon
id|list_del
c_func
(paren
id|midi_dev-&gt;mid_hdrs.next
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midihdr-&gt;data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midihdr
)paren
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|midi_dev
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|card-&gt;open_sem
)paren
suffix:semicolon
id|card-&gt;open_mode
op_and_assign
op_complement
(paren
(paren
id|file-&gt;f_mode
op_lshift
id|FMODE_MIDI_SHIFT
)paren
op_amp
(paren
id|FMODE_MIDI_READ
op_or
id|FMODE_MIDI_WRITE
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|card-&gt;open_sem
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|card-&gt;open_wait
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu10k1_midi_read
r_static
id|ssize_t
id|emu10k1_midi_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|emu10k1_mididevice
op_star
id|midi_dev
op_assign
(paren
r_struct
id|emu10k1_mididevice
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
id|u16
id|cnt
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|DPD
c_func
(paren
l_int|4
comma
l_string|&quot;emu10k1_midi_read(), count %#x&bslash;n&quot;
comma
(paren
id|u32
)paren
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|buffer
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|midi_dev-&gt;mistate
op_eq
id|MIDIIN_STATE_STOPPED
)paren
(brace
r_if
c_cond
(paren
id|emu10k1_mpuin_start
c_func
(paren
id|midi_dev-&gt;card
)paren
OL
l_int|0
)paren
(brace
id|ERROR
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|midi_dev-&gt;mistate
op_assign
id|MIDIIN_STATE_STARTED
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
id|cnt
op_assign
id|MIDIIN_BUFLEN
op_minus
id|midi_dev-&gt;ird
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|midi_spinlock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|midi_dev-&gt;icnt
OL
id|cnt
)paren
id|cnt
op_assign
id|midi_dev-&gt;icnt
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi_spinlock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cnt
OG
id|count
)paren
id|cnt
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|cnt
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_return
id|ret
ques
c_cond
id|ret
suffix:colon
op_minus
id|EAGAIN
suffix:semicolon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot; Go to sleep...&bslash;n&quot;
)paren
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|midi_dev-&gt;iWait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_return
id|ret
ques
c_cond
id|ret
suffix:colon
op_minus
id|ERESTARTSYS
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
id|midi_dev-&gt;iBuf
op_plus
id|midi_dev-&gt;ird
comma
id|cnt
)paren
)paren
(brace
id|ERROR
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
ques
c_cond
id|ret
suffix:colon
op_minus
id|EFAULT
suffix:semicolon
)brace
id|midi_dev-&gt;ird
op_add_assign
id|cnt
suffix:semicolon
id|midi_dev-&gt;ird
op_mod_assign
id|MIDIIN_BUFLEN
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|midi_spinlock
comma
id|flags
)paren
suffix:semicolon
id|midi_dev-&gt;icnt
op_sub_assign
id|cnt
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi_spinlock
comma
id|flags
)paren
suffix:semicolon
id|count
op_sub_assign
id|cnt
suffix:semicolon
id|buffer
op_add_assign
id|cnt
suffix:semicolon
id|ret
op_add_assign
id|cnt
suffix:semicolon
r_if
c_cond
(paren
id|midi_dev-&gt;icnt
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|emu10k1_midi_write
r_static
id|ssize_t
id|emu10k1_midi_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|emu10k1_mididevice
op_star
id|midi_dev
op_assign
(paren
r_struct
id|emu10k1_mididevice
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_struct
id|midi_hdr
op_star
id|midihdr
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|DPD
c_func
(paren
l_int|4
comma
l_string|&quot;emu10k1_midi_write(), count=%#x&bslash;n&quot;
comma
(paren
id|u32
)paren
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|buffer
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|midihdr
op_assign
(paren
r_struct
id|midi_hdr
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|midi_hdr
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|midihdr-&gt;bufferlength
op_assign
id|count
suffix:semicolon
id|midihdr-&gt;bytesrecorded
op_assign
l_int|0
suffix:semicolon
id|midihdr-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|midihdr-&gt;data
op_assign
(paren
id|u8
op_star
)paren
id|kmalloc
c_func
(paren
id|count
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|ERROR
c_func
(paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midihdr
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
id|copy_from_user
c_func
(paren
id|midihdr-&gt;data
comma
id|buffer
comma
id|count
)paren
)paren
(brace
id|kfree
c_func
(paren
id|midihdr-&gt;data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midihdr
)paren
suffix:semicolon
r_return
id|ret
ques
c_cond
id|ret
suffix:colon
op_minus
id|EFAULT
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|midi_spinlock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|emu10k1_mpuout_add_buffer
c_func
(paren
id|midi_dev-&gt;card
comma
id|midihdr
)paren
OL
l_int|0
)paren
(brace
id|ERROR
c_func
(paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midihdr-&gt;data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midihdr
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi_spinlock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi_spinlock
comma
id|flags
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|emu10k1_midi_poll
r_static
r_int
r_int
id|emu10k1_midi_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|poll_table_struct
op_star
id|wait
)paren
(brace
r_struct
id|emu10k1_mididevice
op_star
id|midi_dev
op_assign
(paren
r_struct
id|emu10k1_mididevice
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|0
suffix:semicolon
id|DPF
c_func
(paren
l_int|4
comma
l_string|&quot;emu10k1_midi_poll() called&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|midi_dev-&gt;oWait
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|midi_dev-&gt;iWait
comma
id|wait
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|midi_spinlock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
id|mask
op_or_assign
id|POLLOUT
op_or
id|POLLWRNORM
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
(brace
r_if
c_cond
(paren
id|midi_dev-&gt;mistate
op_eq
id|MIDIIN_STATE_STARTED
)paren
r_if
c_cond
(paren
id|midi_dev-&gt;icnt
OG
l_int|0
)paren
id|mask
op_or_assign
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi_spinlock
comma
id|flags
)paren
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
DECL|function|emu10k1_midi_callback
r_int
id|emu10k1_midi_callback
c_func
(paren
r_int
r_int
id|msg
comma
r_int
r_int
id|refdata
comma
r_int
r_int
op_star
id|pmsg
)paren
(brace
r_struct
id|emu10k1_mididevice
op_star
id|midi_dev
op_assign
(paren
r_struct
id|emu10k1_mididevice
op_star
)paren
id|refdata
suffix:semicolon
r_struct
id|midi_hdr
op_star
id|midihdr
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DPF
c_func
(paren
l_int|4
comma
l_string|&quot;emu10k1_midi_callback()&bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|midi_spinlock
comma
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|msg
)paren
(brace
r_case
id|ICARDMIDI_OUTLONGDATA
suffix:colon
id|midihdr
op_assign
(paren
r_struct
id|midi_hdr
op_star
)paren
id|pmsg
(braket
l_int|2
)braket
suffix:semicolon
id|kfree
c_func
(paren
id|midihdr-&gt;data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midihdr
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|midi_dev-&gt;oWait
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICARDMIDI_INLONGDATA
suffix:colon
id|midihdr
op_assign
(paren
r_struct
id|midi_hdr
op_star
)paren
id|pmsg
(braket
l_int|2
)braket
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
id|midihdr-&gt;bytesrecorded
suffix:semicolon
id|i
op_increment
)paren
(brace
id|midi_dev-&gt;iBuf
(braket
id|midi_dev-&gt;iwr
op_increment
)braket
op_assign
id|midihdr-&gt;data
(braket
id|i
)braket
suffix:semicolon
id|midi_dev-&gt;iwr
op_mod_assign
id|MIDIIN_BUFLEN
suffix:semicolon
)brace
id|midi_dev-&gt;icnt
op_add_assign
id|midihdr-&gt;bytesrecorded
suffix:semicolon
r_if
c_cond
(paren
id|midi_dev-&gt;mistate
op_eq
id|MIDIIN_STATE_STARTED
)paren
(brace
id|init_midi_hdr
c_func
(paren
id|midihdr
)paren
suffix:semicolon
id|emu10k1_mpuin_add_buffer
c_func
(paren
id|midi_dev-&gt;card-&gt;mpuin
comma
id|midihdr
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|midi_dev-&gt;iWait
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ICARDMIDI_INDATA
suffix:colon
(brace
id|u8
op_star
id|pBuf
op_assign
(paren
id|u8
op_star
)paren
op_amp
id|pmsg
(braket
l_int|1
)braket
suffix:semicolon
id|u16
id|bytesvalid
op_assign
id|pmsg
(braket
l_int|2
)braket
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
id|bytesvalid
suffix:semicolon
id|i
op_increment
)paren
(brace
id|midi_dev-&gt;iBuf
(braket
id|midi_dev-&gt;iwr
op_increment
)braket
op_assign
id|pBuf
(braket
id|i
)braket
suffix:semicolon
id|midi_dev-&gt;iwr
op_mod_assign
id|MIDIIN_BUFLEN
suffix:semicolon
)brace
id|midi_dev-&gt;icnt
op_add_assign
id|bytesvalid
suffix:semicolon
)brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|midi_dev-&gt;iWait
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Unknown message */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi_spinlock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi_spinlock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* MIDI file operations */
DECL|variable|emu10k1_midi_fops
r_struct
id|file_operations
id|emu10k1_midi_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|read
op_assign
id|emu10k1_midi_read
comma
dot
id|write
op_assign
id|emu10k1_midi_write
comma
dot
id|poll
op_assign
id|emu10k1_midi_poll
comma
dot
id|open
op_assign
id|emu10k1_midi_open
comma
dot
id|release
op_assign
id|emu10k1_midi_release
comma
)brace
suffix:semicolon
macro_line|#ifdef EMU10K1_SEQUENCER
multiline_comment|/* functions used for sequencer access */
DECL|function|emu10k1_seq_midi_open
r_int
id|emu10k1_seq_midi_open
c_func
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
r_struct
id|emu10k1_card
op_star
id|card
suffix:semicolon
r_struct
id|midi_openinfo
id|dsCardMidiOpenInfo
suffix:semicolon
r_struct
id|emu10k1_mididevice
op_star
id|midi_dev
suffix:semicolon
r_if
c_cond
(paren
id|midi_devs
(braket
id|dev
)braket
op_eq
l_int|NULL
op_logical_or
id|midi_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|devc
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|card
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
id|card-&gt;open_mode
)paren
multiline_comment|/* card is opened native */
r_return
op_minus
id|EBUSY
suffix:semicolon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_seq_midi_open()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|midi_dev
op_assign
(paren
r_struct
id|emu10k1_mididevice
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|midi_dev
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|midi_dev-&gt;card
op_assign
id|card
suffix:semicolon
id|midi_dev-&gt;mistate
op_assign
id|MIDIIN_STATE_STOPPED
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|midi_dev-&gt;oWait
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|midi_dev-&gt;iWait
)paren
suffix:semicolon
id|midi_dev-&gt;ird
op_assign
l_int|0
suffix:semicolon
id|midi_dev-&gt;iwr
op_assign
l_int|0
suffix:semicolon
id|midi_dev-&gt;icnt
op_assign
l_int|0
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|midi_dev-&gt;mid_hdrs
)paren
suffix:semicolon
id|dsCardMidiOpenInfo.refdata
op_assign
(paren
r_int
r_int
)paren
id|midi_dev
suffix:semicolon
r_if
c_cond
(paren
id|emu10k1_mpuout_open
c_func
(paren
id|card
comma
op_amp
id|dsCardMidiOpenInfo
)paren
OL
l_int|0
)paren
(brace
id|ERROR
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|card-&gt;seq_mididev
op_assign
id|midi_dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu10k1_seq_midi_close
r_void
id|emu10k1_seq_midi_close
c_func
(paren
r_int
id|dev
)paren
(brace
r_struct
id|emu10k1_card
op_star
id|card
suffix:semicolon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_seq_midi_close()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|midi_devs
(braket
id|dev
)braket
op_eq
l_int|NULL
op_logical_or
id|midi_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|devc
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|card
op_assign
id|midi_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|devc
suffix:semicolon
id|emu10k1_mpuout_close
c_func
(paren
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;seq_mididev
)paren
(brace
id|kfree
c_func
(paren
id|card-&gt;seq_mididev
)paren
suffix:semicolon
id|card-&gt;seq_mididev
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|emu10k1_seq_midi_out
r_int
id|emu10k1_seq_midi_out
c_func
(paren
r_int
id|dev
comma
r_int
r_char
id|midi_byte
)paren
(brace
r_struct
id|emu10k1_card
op_star
id|card
suffix:semicolon
r_struct
id|midi_hdr
op_star
id|midihdr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|midi_devs
(braket
id|dev
)braket
op_eq
l_int|NULL
op_logical_or
id|midi_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|devc
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|card
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
(paren
id|midihdr
op_assign
(paren
r_struct
id|midi_hdr
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|midi_hdr
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|midihdr-&gt;bufferlength
op_assign
l_int|1
suffix:semicolon
id|midihdr-&gt;bytesrecorded
op_assign
l_int|0
suffix:semicolon
id|midihdr-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|midihdr-&gt;data
op_assign
(paren
id|u8
op_star
)paren
id|kmalloc
c_func
(paren
l_int|1
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|ERROR
c_func
(paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midihdr
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
op_star
(paren
id|midihdr-&gt;data
)paren
op_assign
id|midi_byte
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|midi_spinlock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|emu10k1_mpuout_add_buffer
c_func
(paren
id|card
comma
id|midihdr
)paren
OL
l_int|0
)paren
(brace
id|ERROR
c_func
(paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midihdr-&gt;data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|midihdr
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi_spinlock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi_spinlock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|emu10k1_seq_midi_start_read
r_int
id|emu10k1_seq_midi_start_read
c_func
(paren
r_int
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu10k1_seq_midi_end_read
r_int
id|emu10k1_seq_midi_end_read
c_func
(paren
r_int
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu10k1_seq_midi_kick
r_void
id|emu10k1_seq_midi_kick
c_func
(paren
r_int
id|dev
)paren
(brace
)brace
DECL|function|emu10k1_seq_midi_buffer_status
r_int
id|emu10k1_seq_midi_buffer_status
c_func
(paren
r_int
id|dev
)paren
(brace
r_int
id|count
suffix:semicolon
r_struct
id|midi_queue
op_star
id|queue
suffix:semicolon
r_struct
id|emu10k1_card
op_star
id|card
suffix:semicolon
r_if
c_cond
(paren
id|midi_devs
(braket
id|dev
)braket
op_eq
l_int|NULL
op_logical_or
id|midi_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|devc
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
id|card
op_assign
id|midi_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|devc
suffix:semicolon
id|queue
op_assign
id|card-&gt;mpuout-&gt;firstmidiq
suffix:semicolon
r_while
c_loop
(paren
id|queue
op_ne
l_int|NULL
)paren
(brace
id|count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|queue
op_eq
id|card-&gt;mpuout-&gt;lastmidiq
)paren
r_break
suffix:semicolon
id|queue
op_assign
id|queue-&gt;next
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
macro_line|#endif
eof
