multiline_comment|/*&n; *   32bit -&gt; 64bit ioctl wrapper for PCM API&n; *   Copyright (c) by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
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
id|u32
id|masks
(braket
id|SNDRV_PCM_HW_PARAM_LAST_MASK
op_minus
id|SNDRV_PCM_HW_PARAM_FIRST_MASK
op_plus
l_int|1
)braket
suffix:semicolon
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
suffix:semicolon
DECL|macro|numberof
mdefine_line|#define numberof(array)  (sizeof(array)/sizeof(array[0]))
DECL|macro|CVT_sndrv_pcm_hw_params
mdefine_line|#define CVT_sndrv_pcm_hw_params()&bslash;&n;{&bslash;&n;&t;int i;&bslash;&n;&t;COPY(flags);&bslash;&n;&t;for (i = 0; i &lt; numberof(dst-&gt;masks); i++)&bslash;&n;&t;&t;COPY(masks[i]);&bslash;&n;&t;for (i = 0; i &lt; numberof(dst-&gt;intervals); i++) {&bslash;&n;&t;&t;COPY(intervals[i].min);&bslash;&n;&t;&t;COPY(intervals[i].max);&bslash;&n;&t;&t;COPY(intervals[i].openmin);&bslash;&n;&t;&t;COPY(intervals[i].openmax);&bslash;&n;&t;&t;COPY(intervals[i].integer);&bslash;&n;&t;&t;COPY(intervals[i].empty);&bslash;&n;&t;}&bslash;&n;&t;COPY(rmask);&bslash;&n;&t;COPY(cmask);&bslash;&n;&t;COPY(info);&bslash;&n;&t;COPY(msbits);&bslash;&n;&t;COPY(rate_num);&bslash;&n;&t;COPY(rate_den);&bslash;&n;&t;COPY(fifo_size);&bslash;&n;}
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
suffix:semicolon
DECL|macro|CVT_sndrv_pcm_status
mdefine_line|#define CVT_sndrv_pcm_status()&bslash;&n;{&bslash;&n;&t;COPY(state);&bslash;&n;&t;COPY(trigger_tstamp.tv_sec);&bslash;&n;&t;COPY(trigger_tstamp.tv_usec);&bslash;&n;&t;COPY(tstamp.tv_sec);&bslash;&n;&t;COPY(tstamp.tv_usec);&bslash;&n;&t;COPY(appl_ptr);&bslash;&n;&t;COPY(hw_ptr);&bslash;&n;&t;COPY(delay);&bslash;&n;&t;COPY(avail);&bslash;&n;&t;COPY(avail_max);&bslash;&n;&t;COPY(overrange);&bslash;&n;&t;COPY(suspended_state);&bslash;&n;}
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
suffix:semicolon
DECL|macro|CVT_sndrv_xferi
mdefine_line|#define CVT_sndrv_xferi()&bslash;&n;{&bslash;&n;&t;COPY(result);&bslash;&n;&t;CPTR(buf);&bslash;&n;&t;COPY(frames);&bslash;&n;}
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
id|DEFINE_ALSA_IOCTL
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
DECL|variable|xferi
id|DEFINE_ALSA_IOCTL
c_func
(paren
id|xferi
)paren
suffix:semicolon
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
suffix:semicolon
multiline_comment|/*&n; * xfern ioctl nees to copy (up to) 128 pointers on stack.&n; * although we may pass the copied pointers through f_op-&gt;ioctl, but the ioctl&n; * handler there expands again the same 128 pointers on stack, so it is better&n; * to handle the function (calling pcm_readv/writev) directly in this handler.&n; */
DECL|function|snd_ioctl32_xfern
r_static
r_int
id|snd_ioctl32_xfern
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
id|bufs
(braket
l_int|128
)braket
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
id|cmd
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
r_switch
c_cond
(paren
id|cmd
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
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|err
OL
l_int|0
ques
c_cond
id|err
suffix:colon
l_int|0
suffix:semicolon
)brace
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
(brace
id|SNDRV_PCM_IOCTL_PVERSION
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_INFO
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_HW_REFINE32
comma
id|AP
c_func
(paren
id|pcm_hw_params
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
id|SNDRV_PCM_IOCTL_HW_FREE
comma
l_int|NULL
)brace
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
id|pcm_sframes_str
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
(brace
id|SNDRV_PCM_IOCTL_PREPARE
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_RESET
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_START
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_DROP
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_DRAIN
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_PAUSE
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_REWIND32
comma
id|AP
c_func
(paren
id|pcm_uframes_str
)paren
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_RESUME
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_XRUN
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_WRITEI_FRAMES32
comma
id|AP
c_func
(paren
id|xferi
)paren
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_READI_FRAMES32
comma
id|AP
c_func
(paren
id|xferi
)paren
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_WRITEN_FRAMES32
comma
id|AP
c_func
(paren
id|xfern
)paren
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_READN_FRAMES32
comma
id|AP
c_func
(paren
id|xfern
)paren
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_LINK
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_PCM_IOCTL_UNLINK
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_CTL_IOCTL_PCM_NEXT_DEVICE
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_CTL_IOCTL_PCM_INFO
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_CTL_IOCTL_PCM_PREFER_SUBDEVICE
comma
l_int|NULL
)brace
comma
(brace
l_int|0
)brace
comma
)brace
suffix:semicolon
eof
