multiline_comment|/*&n; *  PCM I/O Plug-In Interface&n; *  Copyright (c) 1999 by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Library General Public License as&n; *   published by the Free Software Foundation; either version 2 of&n; *   the License, or (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU Library General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Library General Public&n; *   License along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
macro_line|#include &quot;pcm_plugin.h&quot;
DECL|macro|pcm_write
mdefine_line|#define pcm_write(plug,buf,count) snd_pcm_oss_write3(plug,buf,count,1)
DECL|macro|pcm_writev
mdefine_line|#define pcm_writev(plug,vec,count) snd_pcm_oss_writev3(plug,vec,count,1)
DECL|macro|pcm_read
mdefine_line|#define pcm_read(plug,buf,count) snd_pcm_oss_read3(plug,buf,count,1)
DECL|macro|pcm_readv
mdefine_line|#define pcm_readv(plug,vec,count) snd_pcm_oss_readv3(plug,vec,count,1)
multiline_comment|/*&n; *  Basic io plugin&n; */
DECL|function|io_playback_transfer
r_static
id|snd_pcm_sframes_t
id|io_playback_transfer
c_func
(paren
id|snd_pcm_plugin_t
op_star
id|plugin
comma
r_const
id|snd_pcm_plugin_channel_t
op_star
id|src_channels
comma
id|snd_pcm_plugin_channel_t
op_star
id|dst_channels
id|ATTRIBUTE_UNUSED
comma
id|snd_pcm_uframes_t
id|frames
)paren
(brace
id|snd_assert
c_func
(paren
id|plugin
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|src_channels
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|plugin-&gt;access
op_eq
id|SNDRV_PCM_ACCESS_RW_INTERLEAVED
)paren
(brace
r_return
id|pcm_write
c_func
(paren
id|plugin-&gt;plug
comma
id|src_channels-&gt;area.addr
comma
id|frames
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|channel
comma
id|channels
op_assign
id|plugin-&gt;dst_format.channels
suffix:semicolon
r_void
op_star
op_star
id|bufs
op_assign
(paren
r_void
op_star
op_star
)paren
id|plugin-&gt;extra_data
suffix:semicolon
id|snd_assert
c_func
(paren
id|bufs
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_for
c_loop
(paren
id|channel
op_assign
l_int|0
suffix:semicolon
id|channel
OL
id|channels
suffix:semicolon
id|channel
op_increment
)paren
(brace
r_if
c_cond
(paren
id|src_channels
(braket
id|channel
)braket
dot
id|enabled
)paren
id|bufs
(braket
id|channel
)braket
op_assign
id|src_channels
(braket
id|channel
)braket
dot
id|area.addr
suffix:semicolon
r_else
id|bufs
(braket
id|channel
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|pcm_writev
c_func
(paren
id|plugin-&gt;plug
comma
id|bufs
comma
id|frames
)paren
suffix:semicolon
)brace
)brace
DECL|function|io_capture_transfer
r_static
id|snd_pcm_sframes_t
id|io_capture_transfer
c_func
(paren
id|snd_pcm_plugin_t
op_star
id|plugin
comma
r_const
id|snd_pcm_plugin_channel_t
op_star
id|src_channels
id|ATTRIBUTE_UNUSED
comma
id|snd_pcm_plugin_channel_t
op_star
id|dst_channels
comma
id|snd_pcm_uframes_t
id|frames
)paren
(brace
id|snd_assert
c_func
(paren
id|plugin
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|dst_channels
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|plugin-&gt;access
op_eq
id|SNDRV_PCM_ACCESS_RW_INTERLEAVED
)paren
(brace
r_return
id|pcm_read
c_func
(paren
id|plugin-&gt;plug
comma
id|dst_channels-&gt;area.addr
comma
id|frames
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|channel
comma
id|channels
op_assign
id|plugin-&gt;dst_format.channels
suffix:semicolon
r_void
op_star
op_star
id|bufs
op_assign
(paren
r_void
op_star
op_star
)paren
id|plugin-&gt;extra_data
suffix:semicolon
id|snd_assert
c_func
(paren
id|bufs
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_for
c_loop
(paren
id|channel
op_assign
l_int|0
suffix:semicolon
id|channel
OL
id|channels
suffix:semicolon
id|channel
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dst_channels
(braket
id|channel
)braket
dot
id|enabled
)paren
id|bufs
(braket
id|channel
)braket
op_assign
id|dst_channels
(braket
id|channel
)braket
dot
id|area.addr
suffix:semicolon
r_else
id|bufs
(braket
id|channel
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|pcm_readv
c_func
(paren
id|plugin-&gt;plug
comma
id|bufs
comma
id|frames
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|io_src_channels
r_static
id|snd_pcm_sframes_t
id|io_src_channels
c_func
(paren
id|snd_pcm_plugin_t
op_star
id|plugin
comma
id|snd_pcm_uframes_t
id|frames
comma
id|snd_pcm_plugin_channel_t
op_star
op_star
id|channels
)paren
(brace
r_int
id|err
suffix:semicolon
r_int
r_int
id|channel
suffix:semicolon
id|snd_pcm_plugin_channel_t
op_star
id|v
suffix:semicolon
id|err
op_assign
id|snd_pcm_plugin_client_channels
c_func
(paren
id|plugin
comma
id|frames
comma
op_amp
id|v
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
op_star
id|channels
op_assign
id|v
suffix:semicolon
r_if
c_cond
(paren
id|plugin-&gt;access
op_eq
id|SNDRV_PCM_ACCESS_RW_INTERLEAVED
)paren
(brace
r_for
c_loop
(paren
id|channel
op_assign
l_int|0
suffix:semicolon
id|channel
OL
id|plugin-&gt;src_format.channels
suffix:semicolon
op_increment
id|channel
comma
op_increment
id|v
)paren
id|v-&gt;wanted
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|frames
suffix:semicolon
)brace
DECL|function|snd_pcm_plugin_build_io
r_int
id|snd_pcm_plugin_build_io
c_func
(paren
id|snd_pcm_plug_t
op_star
id|plug
comma
id|snd_pcm_hw_params_t
op_star
id|params
comma
id|snd_pcm_plugin_t
op_star
op_star
id|r_plugin
)paren
(brace
r_int
id|err
suffix:semicolon
id|snd_pcm_plugin_format_t
id|format
suffix:semicolon
id|snd_pcm_plugin_t
op_star
id|plugin
suffix:semicolon
id|snd_assert
c_func
(paren
id|r_plugin
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
op_star
id|r_plugin
op_assign
l_int|NULL
suffix:semicolon
id|snd_assert
c_func
(paren
id|plug
op_ne
l_int|NULL
op_logical_and
id|params
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|format.format
op_assign
id|params_format
c_func
(paren
id|params
)paren
suffix:semicolon
id|format.rate
op_assign
id|params_rate
c_func
(paren
id|params
)paren
suffix:semicolon
id|format.channels
op_assign
id|params_channels
c_func
(paren
id|params
)paren
suffix:semicolon
id|err
op_assign
id|snd_pcm_plugin_build
c_func
(paren
id|plug
comma
l_string|&quot;I/O io&quot;
comma
op_amp
id|format
comma
op_amp
id|format
comma
r_sizeof
(paren
r_void
op_star
)paren
op_star
id|format.channels
comma
op_amp
id|plugin
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
id|plugin-&gt;access
op_assign
id|params_access
c_func
(paren
id|params
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_pcm_plug_stream
c_func
(paren
id|plug
)paren
op_eq
id|SNDRV_PCM_STREAM_PLAYBACK
)paren
(brace
id|plugin-&gt;transfer
op_assign
id|io_playback_transfer
suffix:semicolon
r_if
c_cond
(paren
id|plugin-&gt;access
op_eq
id|SNDRV_PCM_ACCESS_RW_INTERLEAVED
)paren
id|plugin-&gt;client_channels
op_assign
id|io_src_channels
suffix:semicolon
)brace
r_else
(brace
id|plugin-&gt;transfer
op_assign
id|io_capture_transfer
suffix:semicolon
)brace
op_star
id|r_plugin
op_assign
id|plugin
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
