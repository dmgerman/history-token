multiline_comment|/*&n; *   32bit -&gt; 64bit ioctl wrapper for PCM API&n; *   Copyright (c) by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
macro_line|#include &quot;ioctl32.h&quot;
multiline_comment|/* wrapper for sndrv_pcm_[us]frames */
DECL|struct|sndrv_pcm_sframes_str
r_struct
id|sndrv_pcm_sframes_str
(brace
DECL|member|val
id|sndrv_pcm_sframes_t
id|val
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sndrv_pcm_sframes_str32
r_struct
id|sndrv_pcm_sframes_str32
(brace
DECL|member|val
id|s32
id|val
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sndrv_pcm_uframes_str
r_struct
id|sndrv_pcm_uframes_str
(brace
DECL|member|val
id|sndrv_pcm_uframes_t
id|val
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sndrv_pcm_uframes_str32
r_struct
id|sndrv_pcm_uframes_str32
(brace
DECL|member|val
id|u32
id|val
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CVT_sndrv_pcm_sframes_str
mdefine_line|#define CVT_sndrv_pcm_sframes_str() { COPY(val); }
DECL|macro|CVT_sndrv_pcm_uframes_str
mdefine_line|#define CVT_sndrv_pcm_uframes_str() { COPY(val); }
DECL|struct|sndrv_interval32
r_struct
id|sndrv_interval32
(brace
DECL|member|min
DECL|member|max
id|u32
id|min
comma
id|max
suffix:semicolon
DECL|member|openmin
r_int
r_int
id|openmin
suffix:colon
l_int|1
comma
DECL|member|openmax
id|openmax
suffix:colon
l_int|1
comma
DECL|member|integer
id|integer
suffix:colon
l_int|1
comma
DECL|member|empty
id|empty
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sndrv_pcm_hw_params32
r_struct
id|sndrv_pcm_hw_params32
(brace
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|masks
r_struct
id|sndrv_mask
id|masks
(braket
id|SNDRV_PCM_HW_PARAM_LAST_MASK
op_minus
id|SNDRV_PCM_HW_PARAM_FIRST_MASK
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* this must be identical */
DECL|member|mres
r_struct
id|sndrv_mask
id|mres
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* reserved masks */
DECL|member|intervals
r_struct
id|sndrv_interval32
id|intervals
(braket
id|SNDRV_PCM_HW_PARAM_LAST_INTERVAL
op_minus
id|SNDRV_PCM_HW_PARAM_FIRST_INTERVAL
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|ires
r_struct
id|sndrv_interval
id|ires
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* reserved intervals */
DECL|member|rmask
id|u32
id|rmask
suffix:semicolon
DECL|member|cmask
id|u32
id|cmask
suffix:semicolon
DECL|member|info
id|u32
id|info
suffix:semicolon
DECL|member|msbits
id|u32
id|msbits
suffix:semicolon
DECL|member|rate_num
id|u32
id|rate_num
suffix:semicolon
DECL|member|rate_den
id|u32
id|rate_den
suffix:semicolon
DECL|member|fifo_size
id|u32
id|fifo_size
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|numberof
mdefine_line|#define numberof(array)  (sizeof(array)/sizeof(array[0]))
DECL|macro|CVT_sndrv_pcm_hw_params
mdefine_line|#define CVT_sndrv_pcm_hw_params()&bslash;&n;{&bslash;&n;&t;unsigned int i;&bslash;&n;&t;COPY(flags);&bslash;&n;&t;for (i = 0; i &lt; numberof(dst-&gt;masks); i++)&bslash;&n;&t;&t;COPY(masks[i]);&bslash;&n;&t;for (i = 0; i &lt; numberof(dst-&gt;intervals); i++) {&bslash;&n;&t;&t;COPY(intervals[i].min);&bslash;&n;&t;&t;COPY(intervals[i].max);&bslash;&n;&t;&t;COPY(intervals[i].openmin);&bslash;&n;&t;&t;COPY(intervals[i].openmax);&bslash;&n;&t;&t;COPY(intervals[i].integer);&bslash;&n;&t;&t;COPY(intervals[i].empty);&bslash;&n;&t;}&bslash;&n;&t;COPY(rmask);&bslash;&n;&t;COPY(cmask);&bslash;&n;&t;COPY(info);&bslash;&n;&t;COPY(msbits);&bslash;&n;&t;COPY(rate_num);&bslash;&n;&t;COPY(rate_den);&bslash;&n;&t;COPY(fifo_size);&bslash;&n;}
DECL|struct|sndrv_pcm_sw_params32
r_struct
id|sndrv_pcm_sw_params32
(brace
DECL|member|tstamp_mode
id|s32
id|tstamp_mode
suffix:semicolon
DECL|member|period_step
id|u32
id|period_step
suffix:semicolon
DECL|member|sleep_min
id|u32
id|sleep_min
suffix:semicolon
DECL|member|avail_min
id|u32
id|avail_min
suffix:semicolon
DECL|member|xfer_align
id|u32
id|xfer_align
suffix:semicolon
DECL|member|start_threshold
id|u32
id|start_threshold
suffix:semicolon
DECL|member|stop_threshold
id|u32
id|stop_threshold
suffix:semicolon
DECL|member|silence_threshold
id|u32
id|silence_threshold
suffix:semicolon
DECL|member|silence_size
id|u32
id|silence_size
suffix:semicolon
DECL|member|boundary
id|u32
id|boundary
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|CVT_sndrv_pcm_sw_params
mdefine_line|#define CVT_sndrv_pcm_sw_params()&bslash;&n;{&bslash;&n;&t;COPY(tstamp_mode);&bslash;&n;&t;COPY(period_step);&bslash;&n;&t;COPY(sleep_min);&bslash;&n;&t;COPY(avail_min);&bslash;&n;&t;COPY(xfer_align);&bslash;&n;&t;COPY(start_threshold);&bslash;&n;&t;COPY(stop_threshold);&bslash;&n;&t;COPY(silence_threshold);&bslash;&n;&t;COPY(silence_size);&bslash;&n;&t;COPY(boundary);&bslash;&n;}
DECL|struct|sndrv_pcm_channel_info32
r_struct
id|sndrv_pcm_channel_info32
(brace
DECL|member|channel
id|u32
id|channel
suffix:semicolon
DECL|member|offset
id|u32
id|offset
suffix:semicolon
DECL|member|first
id|u32
id|first
suffix:semicolon
DECL|member|step
id|u32
id|step
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|CVT_sndrv_pcm_channel_info
mdefine_line|#define CVT_sndrv_pcm_channel_info()&bslash;&n;{&bslash;&n;&t;COPY(channel);&bslash;&n;&t;COPY(offset);&bslash;&n;&t;COPY(first);&bslash;&n;&t;COPY(step);&bslash;&n;}
DECL|struct|timeval32
r_struct
id|timeval32
(brace
DECL|member|tv_sec
id|s32
id|tv_sec
suffix:semicolon
DECL|member|tv_usec
id|s32
id|tv_usec
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|sndrv_pcm_status32
r_struct
id|sndrv_pcm_status32
(brace
DECL|member|state
id|s32
id|state
suffix:semicolon
DECL|member|trigger_tstamp
r_struct
id|timeval32
id|trigger_tstamp
suffix:semicolon
DECL|member|tstamp
r_struct
id|timeval32
id|tstamp
suffix:semicolon
DECL|member|appl_ptr
id|u32
id|appl_ptr
suffix:semicolon
DECL|member|hw_ptr
id|u32
id|hw_ptr
suffix:semicolon
DECL|member|delay
id|s32
id|delay
suffix:semicolon
DECL|member|avail
id|u32
id|avail
suffix:semicolon
DECL|member|avail_max
id|u32
id|avail_max
suffix:semicolon
DECL|member|overrange
id|u32
id|overrange
suffix:semicolon
DECL|member|suspended_state
id|s32
id|suspended_state
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|60
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|CVT_sndrv_pcm_status
mdefine_line|#define CVT_sndrv_pcm_status()&bslash;&n;{&bslash;&n;&t;COPY(state);&bslash;&n;&t;COPY(trigger_tstamp.tv_sec);&bslash;&n;&t;COPY(trigger_tstamp.tv_usec);&bslash;&n;&t;COPY(tstamp.tv_sec);&bslash;&n;&t;COPY(tstamp.tv_usec);&bslash;&n;&t;COPY(appl_ptr);&bslash;&n;&t;COPY(hw_ptr);&bslash;&n;&t;COPY(delay);&bslash;&n;&t;COPY(avail);&bslash;&n;&t;COPY(avail_max);&bslash;&n;&t;COPY(overrange);&bslash;&n;&t;COPY(suspended_state);&bslash;&n;}
DECL|variable|pcm_uframes_str
id|DEFINE_ALSA_IOCTL
c_func
(paren
id|pcm_uframes_str
)paren
suffix:semicolon
DECL|variable|pcm_sframes_str
id|DEFINE_ALSA_IOCTL
c_func
(paren
id|pcm_sframes_str
)paren
suffix:semicolon
DECL|variable|pcm_hw_params
id|DEFINE_ALSA_IOCTL_BIG
c_func
(paren
id|pcm_hw_params
)paren
suffix:semicolon
DECL|variable|pcm_sw_params
id|DEFINE_ALSA_IOCTL
c_func
(paren
id|pcm_sw_params
)paren
suffix:semicolon
DECL|variable|pcm_channel_info
id|DEFINE_ALSA_IOCTL
c_func
(paren
id|pcm_channel_info
)paren
suffix:semicolon
DECL|variable|pcm_status
id|DEFINE_ALSA_IOCTL
c_func
(paren
id|pcm_status
)paren
suffix:semicolon
multiline_comment|/*&n; */
DECL|struct|sndrv_xferi32
r_struct
id|sndrv_xferi32
(brace
DECL|member|result
id|s32
id|result
suffix:semicolon
DECL|member|buf
id|u32
id|buf
suffix:semicolon
DECL|member|frames
id|u32
id|frames
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|function|_snd_ioctl32_xferi
r_static
r_int
id|_snd_ioctl32_xferi
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|native_ctl
)paren
(brace
r_struct
id|sndrv_xferi32
id|data32
suffix:semicolon
r_struct
id|sndrv_xferi
id|data
suffix:semicolon
id|mm_segment_t
id|oldseg
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|data32
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|data32
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|data
comma
l_int|0
comma
r_sizeof
(paren
id|data
)paren
)paren
suffix:semicolon
id|data.result
op_assign
id|data32.result
suffix:semicolon
id|data.buf
op_assign
id|A
c_func
(paren
id|data32.buf
)paren
suffix:semicolon
id|data.frames
op_assign
id|data32.frames
suffix:semicolon
id|oldseg
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|err
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
comma
id|file
comma
id|native_ctl
comma
(paren
r_int
r_int
)paren
op_amp
id|data
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|oldseg
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
multiline_comment|/* copy the result */
id|data32.result
op_assign
id|data.result
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|data32
comma
r_sizeof
(paren
id|data32
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* snd_xfern needs remapping of bufs */
DECL|struct|sndrv_xfern32
r_struct
id|sndrv_xfern32
(brace
DECL|member|result
id|s32
id|result
suffix:semicolon
DECL|member|bufs
id|u32
id|bufs
suffix:semicolon
multiline_comment|/* this is void **; */
DECL|member|frames
id|u32
id|frames
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * xfern ioctl nees to copy (up to) 128 pointers on stack.&n; * although we may pass the copied pointers through f_op-&gt;ioctl, but the ioctl&n; * handler there expands again the same 128 pointers on stack, so it is better&n; * to handle the function (calling pcm_readv/writev) directly in this handler.&n; */
DECL|function|_snd_ioctl32_xfern
r_static
r_int
id|_snd_ioctl32_xfern
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|native_ctl
)paren
(brace
id|snd_pcm_file_t
op_star
id|pcm_file
suffix:semicolon
id|snd_pcm_substream_t
op_star
id|substream
suffix:semicolon
r_struct
id|sndrv_xfern32
id|data32
comma
op_star
id|srcptr
op_assign
(paren
r_struct
id|sndrv_xfern32
op_star
)paren
id|arg
suffix:semicolon
r_void
op_star
op_star
id|bufs
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
op_assign
l_int|0
comma
id|ch
comma
id|i
suffix:semicolon
id|u32
op_star
id|bufptr
suffix:semicolon
id|mm_segment_t
id|oldseg
suffix:semicolon
multiline_comment|/* FIXME: need to check whether fop-&gt;ioctl is sane */
id|pcm_file
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_pcm_file_t
comma
id|file-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|substream
op_assign
id|pcm_file-&gt;substream
suffix:semicolon
id|snd_assert
c_func
(paren
id|substream
op_ne
l_int|NULL
op_logical_and
id|substream-&gt;runtime
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
multiline_comment|/* check validty of the command */
r_switch
c_cond
(paren
id|native_ctl
)paren
(brace
r_case
id|SNDRV_PCM_IOCTL_WRITEN_FRAMES
suffix:colon
r_if
c_cond
(paren
id|substream-&gt;stream
op_ne
id|SNDRV_PCM_STREAM_PLAYBACK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|substream-&gt;runtime-&gt;status-&gt;state
op_eq
id|SNDRV_PCM_STATE_OPEN
)paren
r_return
op_minus
id|EBADFD
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_PCM_IOCTL_READN_FRAMES
suffix:colon
r_if
c_cond
(paren
id|substream-&gt;stream
op_ne
id|SNDRV_PCM_STREAM_CAPTURE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ch
op_assign
id|substream-&gt;runtime-&gt;channels
)paren
OG
l_int|128
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|data32.frames
comma
op_amp
id|srcptr-&gt;frames
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|__get_user
c_func
(paren
id|data32.bufs
comma
op_amp
id|srcptr-&gt;bufs
)paren
suffix:semicolon
id|bufptr
op_assign
(paren
id|u32
op_star
)paren
id|TO_PTR
c_func
(paren
id|data32.bufs
)paren
suffix:semicolon
id|bufs
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_void
op_star
)paren
op_star
l_int|128
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bufs
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
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
id|ch
suffix:semicolon
id|i
op_increment
)paren
(brace
id|u32
id|ptr
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|ptr
comma
id|bufptr
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|bufs
(braket
id|ch
)braket
op_assign
(paren
r_void
op_star
)paren
id|TO_PTR
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|bufptr
op_increment
suffix:semicolon
)brace
id|oldseg
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|native_ctl
)paren
(brace
r_case
id|SNDRV_PCM_IOCTL_WRITEN_FRAMES
suffix:colon
id|err
op_assign
id|snd_pcm_lib_writev
c_func
(paren
id|substream
comma
id|bufs
comma
id|data32.frames
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_PCM_IOCTL_READN_FRAMES
suffix:colon
id|err
op_assign
id|snd_pcm_lib_readv
c_func
(paren
id|substream
comma
id|bufs
comma
id|data32.frames
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|set_fs
c_func
(paren
id|oldseg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|err
comma
op_amp
id|srcptr-&gt;result
)paren
)paren
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|bufs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|sndrv_pcm_hw_params_old32
r_struct
id|sndrv_pcm_hw_params_old32
(brace
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|masks
id|u32
id|masks
(braket
id|SNDRV_PCM_HW_PARAM_SUBFORMAT
op_minus
id|SNDRV_PCM_HW_PARAM_ACCESS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|intervals
r_struct
id|sndrv_interval32
id|intervals
(braket
id|SNDRV_PCM_HW_PARAM_TICK_TIME
op_minus
id|SNDRV_PCM_HW_PARAM_SAMPLE_BITS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|rmask
id|u32
id|rmask
suffix:semicolon
DECL|member|cmask
id|u32
id|cmask
suffix:semicolon
DECL|member|info
id|u32
id|info
suffix:semicolon
DECL|member|msbits
id|u32
id|msbits
suffix:semicolon
DECL|member|rate_num
id|u32
id|rate_num
suffix:semicolon
DECL|member|rate_den
id|u32
id|rate_den
suffix:semicolon
DECL|member|fifo_size
id|u32
id|fifo_size
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|__OLD_TO_NEW_MASK
mdefine_line|#define __OLD_TO_NEW_MASK(x) ((x&amp;7)|((x&amp;0x07fffff8)&lt;&lt;5))
DECL|macro|__NEW_TO_OLD_MASK
mdefine_line|#define __NEW_TO_OLD_MASK(x) ((x&amp;7)|((x&amp;0xffffff00)&gt;&gt;5))
DECL|function|snd_pcm_hw_convert_from_old_params
r_static
r_void
id|snd_pcm_hw_convert_from_old_params
c_func
(paren
id|snd_pcm_hw_params_t
op_star
id|params
comma
r_struct
id|sndrv_pcm_hw_params_old32
op_star
id|oparams
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
id|memset
c_func
(paren
id|params
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|params
)paren
)paren
suffix:semicolon
id|params-&gt;flags
op_assign
id|oparams-&gt;flags
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
r_sizeof
(paren
id|oparams-&gt;masks
)paren
op_div
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|i
op_increment
)paren
id|params-&gt;masks
(braket
id|i
)braket
dot
id|bits
(braket
l_int|0
)braket
op_assign
id|oparams-&gt;masks
(braket
id|i
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|params-&gt;intervals
comma
id|oparams-&gt;intervals
comma
r_sizeof
(paren
id|oparams-&gt;intervals
)paren
)paren
suffix:semicolon
id|params-&gt;rmask
op_assign
id|__OLD_TO_NEW_MASK
c_func
(paren
id|oparams-&gt;rmask
)paren
suffix:semicolon
id|params-&gt;cmask
op_assign
id|__OLD_TO_NEW_MASK
c_func
(paren
id|oparams-&gt;cmask
)paren
suffix:semicolon
id|params-&gt;info
op_assign
id|oparams-&gt;info
suffix:semicolon
id|params-&gt;msbits
op_assign
id|oparams-&gt;msbits
suffix:semicolon
id|params-&gt;rate_num
op_assign
id|oparams-&gt;rate_num
suffix:semicolon
id|params-&gt;rate_den
op_assign
id|oparams-&gt;rate_den
suffix:semicolon
id|params-&gt;fifo_size
op_assign
id|oparams-&gt;fifo_size
suffix:semicolon
)brace
DECL|function|snd_pcm_hw_convert_to_old_params
r_static
r_void
id|snd_pcm_hw_convert_to_old_params
c_func
(paren
r_struct
id|sndrv_pcm_hw_params_old32
op_star
id|oparams
comma
id|snd_pcm_hw_params_t
op_star
id|params
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
id|memset
c_func
(paren
id|oparams
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|oparams
)paren
)paren
suffix:semicolon
id|oparams-&gt;flags
op_assign
id|params-&gt;flags
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
r_sizeof
(paren
id|oparams-&gt;masks
)paren
op_div
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|i
op_increment
)paren
id|oparams-&gt;masks
(braket
id|i
)braket
op_assign
id|params-&gt;masks
(braket
id|i
)braket
dot
id|bits
(braket
l_int|0
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|oparams-&gt;intervals
comma
id|params-&gt;intervals
comma
r_sizeof
(paren
id|oparams-&gt;intervals
)paren
)paren
suffix:semicolon
id|oparams-&gt;rmask
op_assign
id|__NEW_TO_OLD_MASK
c_func
(paren
id|params-&gt;rmask
)paren
suffix:semicolon
id|oparams-&gt;cmask
op_assign
id|__NEW_TO_OLD_MASK
c_func
(paren
id|params-&gt;cmask
)paren
suffix:semicolon
id|oparams-&gt;info
op_assign
id|params-&gt;info
suffix:semicolon
id|oparams-&gt;msbits
op_assign
id|params-&gt;msbits
suffix:semicolon
id|oparams-&gt;rate_num
op_assign
id|params-&gt;rate_num
suffix:semicolon
id|oparams-&gt;rate_den
op_assign
id|params-&gt;rate_den
suffix:semicolon
id|oparams-&gt;fifo_size
op_assign
id|params-&gt;fifo_size
suffix:semicolon
)brace
DECL|function|_snd_ioctl32_pcm_hw_params_old
r_static
r_int
id|_snd_ioctl32_pcm_hw_params_old
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|native_ctl
)paren
(brace
r_struct
id|sndrv_pcm_hw_params_old32
op_star
id|data32
suffix:semicolon
r_struct
id|sndrv_pcm_hw_params
op_star
id|data
suffix:semicolon
id|mm_segment_t
id|oldseg
suffix:semicolon
r_int
id|err
suffix:semicolon
id|data32
op_assign
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
op_star
id|data32
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|data
op_assign
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
op_star
id|data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data32
op_eq
l_int|NULL
op_logical_or
id|data
op_eq
l_int|NULL
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|__end
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|data32
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
op_star
id|data32
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|__end
suffix:semicolon
)brace
id|snd_pcm_hw_convert_from_old_params
c_func
(paren
id|data
comma
id|data32
)paren
suffix:semicolon
id|oldseg
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|err
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
comma
id|file
comma
id|native_ctl
comma
(paren
r_int
r_int
)paren
id|data
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|oldseg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|__end
suffix:semicolon
id|snd_pcm_hw_convert_to_old_params
c_func
(paren
id|data32
comma
id|data
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
id|data32
comma
r_sizeof
(paren
op_star
id|data32
)paren
)paren
)paren
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|__end
suffix:colon
r_if
c_cond
(paren
id|data
)paren
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data32
)paren
id|kfree
c_func
(paren
id|data32
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; */
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|pcm_hw_refine
comma
id|pcm_hw_params
comma
id|SNDRV_PCM_IOCTL_HW_REFINE
)paren
suffix:semicolon
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|pcm_hw_params
comma
id|pcm_hw_params
comma
id|SNDRV_PCM_IOCTL_HW_PARAMS
)paren
suffix:semicolon
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|pcm_sw_params
comma
id|pcm_sw_params
comma
id|SNDRV_PCM_IOCTL_SW_PARAMS
)paren
suffix:semicolon
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|pcm_hw_refine_old
comma
id|pcm_hw_params_old
comma
id|SNDRV_PCM_IOCTL_HW_REFINE
)paren
suffix:semicolon
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|pcm_hw_params_old
comma
id|pcm_hw_params_old
comma
id|SNDRV_PCM_IOCTL_HW_PARAMS
)paren
suffix:semicolon
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|pcm_status
comma
id|pcm_status
comma
id|SNDRV_PCM_IOCTL_STATUS
)paren
suffix:semicolon
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|pcm_delay
comma
id|pcm_sframes_str
comma
id|SNDRV_PCM_IOCTL_DELAY
)paren
suffix:semicolon
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|pcm_channel_info
comma
id|pcm_channel_info
comma
id|SNDRV_PCM_IOCTL_CHANNEL_INFO
)paren
suffix:semicolon
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|pcm_rewind
comma
id|pcm_uframes_str
comma
id|SNDRV_PCM_IOCTL_REWIND
)paren
suffix:semicolon
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|pcm_readi
comma
id|xferi
comma
id|SNDRV_PCM_IOCTL_READI_FRAMES
)paren
suffix:semicolon
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|pcm_writei
comma
id|xferi
comma
id|SNDRV_PCM_IOCTL_WRITEI_FRAMES
)paren
suffix:semicolon
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|pcm_readn
comma
id|xfern
comma
id|SNDRV_PCM_IOCTL_READN_FRAMES
)paren
suffix:semicolon
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|pcm_writen
comma
id|xfern
comma
id|SNDRV_PCM_IOCTL_WRITEN_FRAMES
)paren
suffix:semicolon
multiline_comment|/*&n; */
DECL|macro|AP
mdefine_line|#define AP(x) snd_ioctl32_##x
r_enum
(brace
DECL|enumerator|SNDRV_PCM_IOCTL_HW_REFINE32
id|SNDRV_PCM_IOCTL_HW_REFINE32
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x10
comma
r_struct
id|sndrv_pcm_hw_params32
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_HW_PARAMS32
id|SNDRV_PCM_IOCTL_HW_PARAMS32
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x11
comma
r_struct
id|sndrv_pcm_hw_params32
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_SW_PARAMS32
id|SNDRV_PCM_IOCTL_SW_PARAMS32
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x13
comma
r_struct
id|sndrv_pcm_sw_params32
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_STATUS32
id|SNDRV_PCM_IOCTL_STATUS32
op_assign
id|_IOR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x20
comma
r_struct
id|sndrv_pcm_status32
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_DELAY32
id|SNDRV_PCM_IOCTL_DELAY32
op_assign
id|_IOR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x21
comma
id|s32
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_CHANNEL_INFO32
id|SNDRV_PCM_IOCTL_CHANNEL_INFO32
op_assign
id|_IOR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x32
comma
r_struct
id|sndrv_pcm_channel_info32
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_REWIND32
id|SNDRV_PCM_IOCTL_REWIND32
op_assign
id|_IOW
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x46
comma
id|u32
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_WRITEI_FRAMES32
id|SNDRV_PCM_IOCTL_WRITEI_FRAMES32
op_assign
id|_IOW
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x50
comma
r_struct
id|sndrv_xferi32
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_READI_FRAMES32
id|SNDRV_PCM_IOCTL_READI_FRAMES32
op_assign
id|_IOR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x51
comma
r_struct
id|sndrv_xferi32
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_WRITEN_FRAMES32
id|SNDRV_PCM_IOCTL_WRITEN_FRAMES32
op_assign
id|_IOW
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x52
comma
r_struct
id|sndrv_xfern32
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_READN_FRAMES32
id|SNDRV_PCM_IOCTL_READN_FRAMES32
op_assign
id|_IOR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x53
comma
r_struct
id|sndrv_xfern32
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_HW_REFINE_OLD32
id|SNDRV_PCM_IOCTL_HW_REFINE_OLD32
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x10
comma
r_struct
id|sndrv_pcm_hw_params_old32
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_HW_PARAMS_OLD32
id|SNDRV_PCM_IOCTL_HW_PARAMS_OLD32
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x11
comma
r_struct
id|sndrv_pcm_hw_params_old32
)paren
comma
)brace
suffix:semicolon
DECL|variable|pcm_mappers
r_struct
id|ioctl32_mapper
id|pcm_mappers
(braket
)braket
op_assign
(brace
id|MAP_COMPAT
c_func
(paren
id|SNDRV_PCM_IOCTL_PVERSION
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_PCM_IOCTL_INFO
)paren
comma
(brace
id|SNDRV_PCM_IOCTL_HW_REFINE32
comma
id|AP
c_func
(paren
id|pcm_hw_refine
)paren
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_HW_PARAMS32
comma
id|AP
c_func
(paren
id|pcm_hw_params
)paren
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_HW_REFINE_OLD32
comma
id|AP
c_func
(paren
id|pcm_hw_refine_old
)paren
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_HW_PARAMS_OLD32
comma
id|AP
c_func
(paren
id|pcm_hw_params_old
)paren
)brace
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_PCM_IOCTL_HW_FREE
)paren
comma
(brace
id|SNDRV_PCM_IOCTL_SW_PARAMS32
comma
id|AP
c_func
(paren
id|pcm_sw_params
)paren
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_STATUS32
comma
id|AP
c_func
(paren
id|pcm_status
)paren
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_DELAY32
comma
id|AP
c_func
(paren
id|pcm_delay
)paren
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_CHANNEL_INFO32
comma
id|AP
c_func
(paren
id|pcm_channel_info
)paren
)brace
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_PCM_IOCTL_PREPARE
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_PCM_IOCTL_RESET
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_PCM_IOCTL_START
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_PCM_IOCTL_DROP
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_PCM_IOCTL_DRAIN
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_PCM_IOCTL_PAUSE
)paren
comma
(brace
id|SNDRV_PCM_IOCTL_REWIND32
comma
id|AP
c_func
(paren
id|pcm_rewind
)paren
)brace
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_PCM_IOCTL_RESUME
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_PCM_IOCTL_XRUN
)paren
comma
(brace
id|SNDRV_PCM_IOCTL_WRITEI_FRAMES32
comma
id|AP
c_func
(paren
id|pcm_writei
)paren
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_READI_FRAMES32
comma
id|AP
c_func
(paren
id|pcm_readi
)paren
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_WRITEN_FRAMES32
comma
id|AP
c_func
(paren
id|pcm_writen
)paren
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_READN_FRAMES32
comma
id|AP
c_func
(paren
id|pcm_readn
)paren
)brace
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_PCM_IOCTL_LINK
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_PCM_IOCTL_UNLINK
)paren
comma
(brace
l_int|0
)brace
comma
)brace
suffix:semicolon
eof
