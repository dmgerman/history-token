multiline_comment|/*&n; * Driver for Tascam US-X2Y USB soundcards&n; *&n; * FPGA Loader + ALSA Startup&n; *&n; * Copyright (c) 2003 by Karsten Wiese &lt;annabellesgarden@yahoo.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/memalloc.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
macro_line|#include &lt;sound/hwdep.h&gt;
macro_line|#include &quot;usx2y.h&quot;
macro_line|#include &quot;usbusx2y.h&quot;
macro_line|#include &quot;usX2Yhwdep.h&quot;
r_int
id|usX2Y_hwdep_pcm_new
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
suffix:semicolon
DECL|function|snd_us428ctls_vm_nopage
r_static
r_struct
id|page
op_star
id|snd_us428ctls_vm_nopage
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|area
comma
r_int
r_int
id|address
comma
r_int
op_star
id|type
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_void
op_star
id|vaddr
suffix:semicolon
id|snd_printdd
c_func
(paren
l_string|&quot;ENTER, start %lXh, ofs %lXh, pgoff %ld, addr %lXh&bslash;n&quot;
comma
id|area-&gt;vm_start
comma
id|address
op_minus
id|area-&gt;vm_start
comma
(paren
id|address
op_minus
id|area-&gt;vm_start
)paren
op_rshift
id|PAGE_SHIFT
comma
id|address
)paren
suffix:semicolon
id|offset
op_assign
id|area-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|offset
op_add_assign
id|address
op_minus
id|area-&gt;vm_start
suffix:semicolon
id|snd_assert
c_func
(paren
(paren
id|offset
op_mod
id|PAGE_SIZE
)paren
op_eq
l_int|0
comma
r_return
id|NOPAGE_OOM
)paren
suffix:semicolon
id|vaddr
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
id|usX2Ydev_t
op_star
)paren
id|area-&gt;vm_private_data
)paren
op_member_access_from_pointer
id|us428ctls_sharedmem
op_plus
id|offset
suffix:semicolon
id|page
op_assign
id|virt_to_page
c_func
(paren
id|vaddr
)paren
suffix:semicolon
id|get_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|snd_printdd
c_func
(paren
l_string|&quot;vaddr=%p made us428ctls_vm_nopage() return %p; offset=%lX&bslash;n&quot;
comma
id|vaddr
comma
id|page
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
)paren
op_star
id|type
op_assign
id|VM_FAULT_MINOR
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
DECL|variable|us428ctls_vm_ops
r_static
r_struct
id|vm_operations_struct
id|us428ctls_vm_ops
op_assign
(brace
dot
id|nopage
op_assign
id|snd_us428ctls_vm_nopage
comma
)brace
suffix:semicolon
DECL|function|snd_us428ctls_mmap
r_static
r_int
id|snd_us428ctls_mmap
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
r_struct
id|file
op_star
id|filp
comma
r_struct
id|vm_area_struct
op_star
id|area
)paren
(brace
r_int
r_int
id|size
op_assign
(paren
r_int
r_int
)paren
(paren
id|area-&gt;vm_end
op_minus
id|area-&gt;vm_start
)paren
suffix:semicolon
id|usX2Ydev_t
op_star
id|us428
op_assign
(paren
id|usX2Ydev_t
op_star
)paren
id|hw-&gt;private_data
suffix:semicolon
singleline_comment|// FIXME this hwdep interface is used twice: fpga download and mmap for controlling Lights etc. Maybe better using 2 hwdep devs?
singleline_comment|// so as long as the device isn&squot;t fully initialised yet we return -EBUSY here.
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
(paren
id|usX2Ydev_t
op_star
)paren
id|hw-&gt;private_data
)paren
op_member_access_from_pointer
id|chip_status
op_amp
id|USX2Y_STAT_CHIP_INIT
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* if userspace tries to mmap beyond end of our buffer, fail */
r_if
c_cond
(paren
id|size
OG
(paren
(paren
id|PAGE_SIZE
op_minus
l_int|1
op_plus
r_sizeof
(paren
id|us428ctls_sharedmem_t
)paren
)paren
op_div
id|PAGE_SIZE
)paren
op_star
id|PAGE_SIZE
)paren
(brace
id|snd_printd
c_func
(paren
l_string|&quot;%lu &gt; %lu&bslash;n&quot;
comma
id|size
comma
(paren
r_int
r_int
)paren
r_sizeof
(paren
id|us428ctls_sharedmem_t
)paren
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
op_logical_neg
id|us428-&gt;us428ctls_sharedmem
)paren
(brace
id|init_waitqueue_head
c_func
(paren
op_amp
id|us428-&gt;us428ctls_wait_queue_head
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|us428-&gt;us428ctls_sharedmem
op_assign
id|snd_malloc_pages
c_func
(paren
r_sizeof
(paren
id|us428ctls_sharedmem_t
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|us428-&gt;us428ctls_sharedmem
comma
op_minus
l_int|1
comma
r_sizeof
(paren
id|us428ctls_sharedmem_t
)paren
)paren
suffix:semicolon
id|us428-&gt;us428ctls_sharedmem-&gt;CtlSnapShotLast
op_assign
op_minus
l_int|2
suffix:semicolon
)brace
id|area-&gt;vm_ops
op_assign
op_amp
id|us428ctls_vm_ops
suffix:semicolon
id|area-&gt;vm_flags
op_or_assign
id|VM_RESERVED
suffix:semicolon
id|area-&gt;vm_private_data
op_assign
id|hw-&gt;private_data
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_us428ctls_poll
r_static
r_int
r_int
id|snd_us428ctls_poll
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_int
r_int
id|mask
op_assign
l_int|0
suffix:semicolon
id|usX2Ydev_t
op_star
id|us428
op_assign
(paren
id|usX2Ydev_t
op_star
)paren
id|hw-&gt;private_data
suffix:semicolon
id|us428ctls_sharedmem_t
op_star
id|shm
op_assign
id|us428-&gt;us428ctls_sharedmem
suffix:semicolon
r_if
c_cond
(paren
id|us428-&gt;chip_status
op_amp
id|USX2Y_STAT_CHIP_HUP
)paren
r_return
id|POLLHUP
suffix:semicolon
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|us428-&gt;us428ctls_wait_queue_head
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shm
op_ne
l_int|NULL
op_logical_and
id|shm-&gt;CtlSnapShotLast
op_ne
id|shm-&gt;CtlSnapShotRed
)paren
id|mask
op_or_assign
id|POLLIN
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
DECL|function|snd_usX2Y_hwdep_open
r_static
r_int
id|snd_usX2Y_hwdep_open
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_usX2Y_hwdep_release
r_static
r_int
id|snd_usX2Y_hwdep_release
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_usX2Y_hwdep_dsp_status
r_static
r_int
id|snd_usX2Y_hwdep_dsp_status
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
id|snd_hwdep_dsp_status_t
op_star
id|info
)paren
(brace
r_static
r_char
op_star
id|type_ids
(braket
id|USX2Y_TYPE_NUMS
)braket
op_assign
(brace
(braket
id|USX2Y_TYPE_122
)braket
op_assign
l_string|&quot;us122&quot;
comma
(braket
id|USX2Y_TYPE_224
)braket
op_assign
l_string|&quot;us224&quot;
comma
(braket
id|USX2Y_TYPE_428
)braket
op_assign
l_string|&quot;us428&quot;
comma
)brace
suffix:semicolon
r_int
id|id
op_assign
op_minus
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|le16_to_cpu
c_func
(paren
(paren
(paren
id|usX2Ydev_t
op_star
)paren
id|hw-&gt;private_data
)paren
op_member_access_from_pointer
id|chip.dev-&gt;descriptor.idProduct
)paren
)paren
(brace
r_case
id|USB_ID_US122
suffix:colon
id|id
op_assign
id|USX2Y_TYPE_122
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_ID_US224
suffix:colon
id|id
op_assign
id|USX2Y_TYPE_224
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_ID_US428
suffix:colon
id|id
op_assign
id|USX2Y_TYPE_428
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
OG
id|id
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|strcpy
c_func
(paren
id|info-&gt;id
comma
id|type_ids
(braket
id|id
)braket
)paren
suffix:semicolon
id|info-&gt;num_dsps
op_assign
l_int|2
suffix:semicolon
singleline_comment|// 0: Prepad Data, 1: FPGA Code
r_if
c_cond
(paren
(paren
(paren
id|usX2Ydev_t
op_star
)paren
id|hw-&gt;private_data
)paren
op_member_access_from_pointer
id|chip_status
op_amp
id|USX2Y_STAT_CHIP_INIT
)paren
id|info-&gt;chip_ready
op_assign
l_int|1
suffix:semicolon
id|info-&gt;version
op_assign
id|USX2Y_DRIVER_VERSION
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usX2Y_create_usbmidi
r_static
r_int
id|usX2Y_create_usbmidi
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
r_static
id|snd_usb_midi_endpoint_info_t
id|quirk_data_1
op_assign
(brace
dot
id|out_ep
op_assign
l_int|0x06
comma
dot
id|in_ep
op_assign
l_int|0x06
comma
dot
id|out_cables
op_assign
l_int|0x001
comma
dot
id|in_cables
op_assign
l_int|0x001
)brace
suffix:semicolon
r_static
id|snd_usb_audio_quirk_t
id|quirk_1
op_assign
(brace
dot
id|vendor_name
op_assign
l_string|&quot;TASCAM&quot;
comma
dot
id|product_name
op_assign
id|NAME_ALLCAPS
comma
dot
id|ifnum
op_assign
l_int|0
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
id|quirk_data_1
)brace
suffix:semicolon
r_static
id|snd_usb_midi_endpoint_info_t
id|quirk_data_2
op_assign
(brace
dot
id|out_ep
op_assign
l_int|0x06
comma
dot
id|in_ep
op_assign
l_int|0x06
comma
dot
id|out_cables
op_assign
l_int|0x003
comma
dot
id|in_cables
op_assign
l_int|0x003
)brace
suffix:semicolon
r_static
id|snd_usb_audio_quirk_t
id|quirk_2
op_assign
(brace
dot
id|vendor_name
op_assign
l_string|&quot;TASCAM&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;US428&quot;
comma
dot
id|ifnum
op_assign
l_int|0
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
id|quirk_data_2
)brace
suffix:semicolon
r_struct
id|usb_device
op_star
id|dev
op_assign
id|usX2Y
c_func
(paren
id|card
)paren
op_member_access_from_pointer
id|chip.dev
suffix:semicolon
r_struct
id|usb_interface
op_star
id|iface
op_assign
id|usb_ifnum_to_if
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|snd_usb_audio_quirk_t
op_star
id|quirk
op_assign
id|le16_to_cpu
c_func
(paren
id|dev-&gt;descriptor.idProduct
)paren
op_eq
id|USB_ID_US428
ques
c_cond
op_amp
id|quirk_2
suffix:colon
op_amp
id|quirk_1
suffix:semicolon
id|snd_printdd
c_func
(paren
l_string|&quot;usX2Y_create_usbmidi &bslash;n&quot;
)paren
suffix:semicolon
r_return
id|snd_usb_create_midi_interface
c_func
(paren
op_amp
id|usX2Y
c_func
(paren
id|card
)paren
op_member_access_from_pointer
id|chip
comma
id|iface
comma
id|quirk
)paren
suffix:semicolon
)brace
DECL|function|usX2Y_create_alsa_devices
r_static
r_int
id|usX2Y_create_alsa_devices
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
r_int
id|err
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|usX2Y_create_usbmidi
c_func
(paren
id|card
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;usX2Y_create_alsa_devices: usX2Y_create_usbmidi error %i &bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|usX2Y_audio_create
c_func
(paren
id|card
)paren
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|usX2Y_hwdep_pcm_new
c_func
(paren
id|card
)paren
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
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
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|0
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|snd_usX2Y_hwdep_dsp_load
r_static
r_int
id|snd_usX2Y_hwdep_dsp_load
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
id|snd_hwdep_dsp_image_t
op_star
id|dsp
)paren
(brace
id|usX2Ydev_t
op_star
id|priv
op_assign
id|hw-&gt;private_data
suffix:semicolon
r_int
id|lret
comma
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|snd_printdd
c_func
(paren
l_string|&quot;dsp_load %s&bslash;n&quot;
comma
id|dsp-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|dsp-&gt;image
comma
id|dsp-&gt;length
)paren
)paren
(brace
r_struct
id|usb_device
op_star
id|dev
op_assign
id|priv-&gt;chip.dev
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|kmalloc
c_func
(paren
id|dsp-&gt;length
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buf
comma
id|dsp-&gt;image
comma
id|dsp-&gt;length
)paren
)paren
(brace
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|err
op_assign
id|usb_set_interface
c_func
(paren
id|dev
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|snd_printk
c_func
(paren
l_string|&quot;usb_set_interface error &bslash;n&quot;
)paren
suffix:semicolon
r_else
id|err
op_assign
id|usb_bulk_msg
c_func
(paren
id|dev
comma
id|usb_sndbulkpipe
c_func
(paren
id|dev
comma
l_int|2
)paren
comma
id|buf
comma
id|dsp-&gt;length
comma
op_amp
id|lret
comma
l_int|6000
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|dsp-&gt;index
op_eq
l_int|1
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
op_div
l_int|4
)paren
suffix:semicolon
singleline_comment|// give the device some time 
id|err
op_assign
id|usX2Y_AsyncSeq04_init
c_func
(paren
id|priv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;usX2Y_AsyncSeq04_init error &bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|err
op_assign
id|usX2Y_In04_init
c_func
(paren
id|priv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;usX2Y_In04_init error &bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|err
op_assign
id|usX2Y_create_alsa_devices
c_func
(paren
id|hw-&gt;card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;usX2Y_create_alsa_devices error %i &bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
id|snd_card_free
c_func
(paren
id|hw-&gt;card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|priv-&gt;chip_status
op_or_assign
id|USX2Y_STAT_CHIP_INIT
suffix:semicolon
id|snd_printdd
c_func
(paren
l_string|&quot;%s: alsa all started&bslash;n&quot;
comma
id|hw-&gt;name
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|usX2Y_hwdep_new
r_int
id|usX2Y_hwdep_new
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_struct
id|usb_device
op_star
id|device
)paren
(brace
r_int
id|err
suffix:semicolon
id|snd_hwdep_t
op_star
id|hw
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_hwdep_new
c_func
(paren
id|card
comma
id|SND_USX2Y_LOADER_ID
comma
l_int|0
comma
op_amp
id|hw
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|hw-&gt;iface
op_assign
id|SNDRV_HWDEP_IFACE_USX2Y
suffix:semicolon
id|hw-&gt;private_data
op_assign
id|usX2Y
c_func
(paren
id|card
)paren
suffix:semicolon
id|hw-&gt;ops.open
op_assign
id|snd_usX2Y_hwdep_open
suffix:semicolon
id|hw-&gt;ops.release
op_assign
id|snd_usX2Y_hwdep_release
suffix:semicolon
id|hw-&gt;ops.dsp_status
op_assign
id|snd_usX2Y_hwdep_dsp_status
suffix:semicolon
id|hw-&gt;ops.dsp_load
op_assign
id|snd_usX2Y_hwdep_dsp_load
suffix:semicolon
id|hw-&gt;ops.mmap
op_assign
id|snd_us428ctls_mmap
suffix:semicolon
id|hw-&gt;ops.poll
op_assign
id|snd_us428ctls_poll
suffix:semicolon
id|hw-&gt;exclusive
op_assign
l_int|1
suffix:semicolon
id|sprintf
c_func
(paren
id|hw-&gt;name
comma
l_string|&quot;/proc/bus/usb/%03d/%03d&quot;
comma
id|device-&gt;bus-&gt;busnum
comma
id|device-&gt;devnum
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
