multiline_comment|/*&n; *  Attenuated route Plug-In&n; *  Copyright (c) 2000 by Abramo Bagnara &lt;abramo@alsa-project.org&gt;&n; *&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Library General Public License as&n; *   published by the Free Software Foundation; either version 2 of&n; *   the License, or (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU Library General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Library General Public&n; *   License along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
macro_line|#include &quot;pcm_plugin.h&quot;
multiline_comment|/* The best possible hack to support missing optimization in gcc 2.7.2.3 */
macro_line|#if ROUTE_PLUGIN_RESOLUTION &amp; (ROUTE_PLUGIN_RESOLUTION - 1) != 0
DECL|macro|div
mdefine_line|#define div(a) a /= ROUTE_PLUGIN_RESOLUTION
macro_line|#elif ROUTE_PLUGIN_RESOLUTION == 16
DECL|macro|div
mdefine_line|#define div(a) a &gt;&gt;= 4
macro_line|#else
macro_line|#error &quot;Add some code here&quot;
macro_line|#endif
DECL|typedef|ttable_dst_t
r_typedef
r_struct
id|ttable_dst
id|ttable_dst_t
suffix:semicolon
DECL|typedef|route_t
r_typedef
r_struct
id|route_private_data
id|route_t
suffix:semicolon
DECL|typedef|route_channel_f
r_typedef
r_void
(paren
op_star
id|route_channel_f
)paren
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
id|dst_channel
comma
id|ttable_dst_t
op_star
id|ttable
comma
id|snd_pcm_uframes_t
id|frames
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|as_int
r_int
id|as_int
suffix:semicolon
macro_line|#if ROUTE_PLUGIN_USE_FLOAT
DECL|member|as_float
r_float
id|as_float
suffix:semicolon
macro_line|#endif
DECL|typedef|ttable_src_t
)brace
id|ttable_src_t
suffix:semicolon
DECL|struct|ttable_dst
r_struct
id|ttable_dst
(brace
DECL|member|att
r_int
id|att
suffix:semicolon
multiline_comment|/* Attenuated */
DECL|member|nsrcs
r_int
r_int
id|nsrcs
suffix:semicolon
DECL|member|srcs
id|ttable_src_t
op_star
id|srcs
suffix:semicolon
DECL|member|func
id|route_channel_f
id|func
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|route_private_data
r_struct
id|route_private_data
(brace
DECL|enumerator|UINT32
DECL|enumerator|UINT64
DECL|enumerator|FLOAT
DECL|member|sum_type
r_enum
(brace
id|UINT32
op_assign
l_int|0
comma
id|UINT64
op_assign
l_int|1
comma
id|FLOAT
op_assign
l_int|2
)brace
id|sum_type
suffix:semicolon
DECL|member|get
DECL|member|put
r_int
id|get
comma
id|put
suffix:semicolon
DECL|member|conv
r_int
id|conv
suffix:semicolon
DECL|member|src_sample_size
r_int
id|src_sample_size
suffix:semicolon
DECL|member|ttable
id|ttable_dst_t
id|ttable
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|as_uint32
id|u_int32_t
id|as_uint32
suffix:semicolon
DECL|member|as_uint64
id|u_int64_t
id|as_uint64
suffix:semicolon
macro_line|#if ROUTE_PLUGIN_USE_FLOAT
DECL|member|as_float
r_float
id|as_float
suffix:semicolon
macro_line|#endif
DECL|typedef|sum_t
)brace
id|sum_t
suffix:semicolon
DECL|function|route_to_channel_from_zero
r_static
r_void
id|route_to_channel_from_zero
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
id|dst_channel
comma
id|ttable_dst_t
op_star
id|ttable
id|ATTRIBUTE_UNUSED
comma
id|snd_pcm_uframes_t
id|frames
)paren
(brace
r_if
c_cond
(paren
id|dst_channel-&gt;wanted
)paren
id|snd_pcm_area_silence
c_func
(paren
op_amp
id|dst_channel-&gt;area
comma
l_int|0
comma
id|frames
comma
id|plugin-&gt;dst_format.format
)paren
suffix:semicolon
id|dst_channel-&gt;enabled
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|route_to_channel_from_one
r_static
r_void
id|route_to_channel_from_one
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
id|dst_channel
comma
id|ttable_dst_t
op_star
id|ttable
comma
id|snd_pcm_uframes_t
id|frames
)paren
(brace
DECL|macro|CONV_LABELS
mdefine_line|#define CONV_LABELS
macro_line|#include &quot;plugin_ops.h&quot;
DECL|macro|CONV_LABELS
macro_line|#undef CONV_LABELS
id|route_t
op_star
id|data
op_assign
(paren
id|route_t
op_star
)paren
id|plugin-&gt;extra_data
suffix:semicolon
r_void
op_star
id|conv
suffix:semicolon
r_const
id|snd_pcm_plugin_channel_t
op_star
id|src_channel
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|srcidx
suffix:semicolon
r_char
op_star
id|src
comma
op_star
id|dst
suffix:semicolon
r_int
id|src_step
comma
id|dst_step
suffix:semicolon
r_for
c_loop
(paren
id|srcidx
op_assign
l_int|0
suffix:semicolon
id|srcidx
OL
id|ttable-&gt;nsrcs
suffix:semicolon
op_increment
id|srcidx
)paren
(brace
id|src_channel
op_assign
op_amp
id|src_channels
(braket
id|ttable-&gt;srcs
(braket
id|srcidx
)braket
dot
id|channel
)braket
suffix:semicolon
r_if
c_cond
(paren
id|src_channel-&gt;area.addr
op_ne
l_int|NULL
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srcidx
op_eq
id|ttable-&gt;nsrcs
)paren
(brace
id|route_to_channel_from_zero
c_func
(paren
id|plugin
comma
id|src_channels
comma
id|dst_channel
comma
id|ttable
comma
id|frames
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dst_channel-&gt;enabled
op_assign
l_int|1
suffix:semicolon
id|conv
op_assign
id|conv_labels
(braket
id|data-&gt;conv
)braket
suffix:semicolon
id|src
op_assign
id|src_channel-&gt;area.addr
op_plus
id|src_channel-&gt;area.first
op_div
l_int|8
suffix:semicolon
id|src_step
op_assign
id|src_channel-&gt;area.step
op_div
l_int|8
suffix:semicolon
id|dst
op_assign
id|dst_channel-&gt;area.addr
op_plus
id|dst_channel-&gt;area.first
op_div
l_int|8
suffix:semicolon
id|dst_step
op_assign
id|dst_channel-&gt;area.step
op_div
l_int|8
suffix:semicolon
r_while
c_loop
(paren
id|frames
op_decrement
OG
l_int|0
)paren
(brace
r_goto
op_star
id|conv
suffix:semicolon
DECL|macro|CONV_END
mdefine_line|#define CONV_END after
macro_line|#include &quot;plugin_ops.h&quot;
DECL|macro|CONV_END
macro_line|#undef CONV_END
id|after
suffix:colon
id|src
op_add_assign
id|src_step
suffix:semicolon
id|dst
op_add_assign
id|dst_step
suffix:semicolon
)brace
)brace
DECL|function|route_to_channel
r_static
r_void
id|route_to_channel
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
id|dst_channel
comma
id|ttable_dst_t
op_star
id|ttable
comma
id|snd_pcm_uframes_t
id|frames
)paren
(brace
DECL|macro|GET_U_LABELS
mdefine_line|#define GET_U_LABELS
DECL|macro|PUT_U32_LABELS
mdefine_line|#define PUT_U32_LABELS
macro_line|#include &quot;plugin_ops.h&quot;
DECL|macro|GET_U_LABELS
macro_line|#undef GET_U_LABELS
DECL|macro|PUT_U32_LABELS
macro_line|#undef PUT_U32_LABELS
r_static
r_void
op_star
id|zero_labels
(braket
l_int|3
)braket
op_assign
(brace
op_logical_and
id|zero_int32
comma
op_logical_and
id|zero_int64
comma
macro_line|#if ROUTE_PLUGIN_USE_FLOAT
op_logical_and
id|zero_float
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* sum_type att */
r_static
r_void
op_star
id|add_labels
(braket
l_int|3
op_star
l_int|2
)braket
op_assign
(brace
op_logical_and
id|add_int32_noatt
comma
op_logical_and
id|add_int32_att
comma
op_logical_and
id|add_int64_noatt
comma
op_logical_and
id|add_int64_att
comma
macro_line|#if ROUTE_PLUGIN_USE_FLOAT
op_logical_and
id|add_float_noatt
comma
op_logical_and
id|add_float_att
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* sum_type att shift */
r_static
r_void
op_star
id|norm_labels
(braket
l_int|3
op_star
l_int|2
op_star
l_int|4
)braket
op_assign
(brace
l_int|0
comma
op_logical_and
id|norm_int32_8_noatt
comma
op_logical_and
id|norm_int32_16_noatt
comma
op_logical_and
id|norm_int32_24_noatt
comma
l_int|0
comma
op_logical_and
id|norm_int32_8_att
comma
op_logical_and
id|norm_int32_16_att
comma
op_logical_and
id|norm_int32_24_att
comma
op_logical_and
id|norm_int64_0_noatt
comma
op_logical_and
id|norm_int64_8_noatt
comma
op_logical_and
id|norm_int64_16_noatt
comma
op_logical_and
id|norm_int64_24_noatt
comma
op_logical_and
id|norm_int64_0_att
comma
op_logical_and
id|norm_int64_8_att
comma
op_logical_and
id|norm_int64_16_att
comma
op_logical_and
id|norm_int64_24_att
comma
macro_line|#if ROUTE_PLUGIN_USE_FLOAT
op_logical_and
id|norm_float_0
comma
op_logical_and
id|norm_float_8
comma
op_logical_and
id|norm_float_16
comma
op_logical_and
id|norm_float_24
comma
op_logical_and
id|norm_float_0
comma
op_logical_and
id|norm_float_8
comma
op_logical_and
id|norm_float_16
comma
op_logical_and
id|norm_float_24
comma
macro_line|#endif
)brace
suffix:semicolon
id|route_t
op_star
id|data
op_assign
(paren
id|route_t
op_star
)paren
id|plugin-&gt;extra_data
suffix:semicolon
r_void
op_star
id|zero
comma
op_star
id|get
comma
op_star
id|add
comma
op_star
id|norm
comma
op_star
id|put_u32
suffix:semicolon
r_int
id|nsrcs
op_assign
id|ttable-&gt;nsrcs
suffix:semicolon
r_char
op_star
id|dst
suffix:semicolon
r_int
id|dst_step
suffix:semicolon
r_char
op_star
id|srcs
(braket
id|nsrcs
)braket
suffix:semicolon
r_int
id|src_steps
(braket
id|nsrcs
)braket
suffix:semicolon
id|ttable_src_t
id|src_tt
(braket
id|nsrcs
)braket
suffix:semicolon
id|u_int32_t
id|sample
op_assign
l_int|0
suffix:semicolon
r_int
id|srcidx
comma
id|srcidx1
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|srcidx
op_assign
l_int|0
suffix:semicolon
id|srcidx
OL
id|nsrcs
suffix:semicolon
op_increment
id|srcidx
)paren
(brace
r_const
id|snd_pcm_plugin_channel_t
op_star
id|src_channel
op_assign
op_amp
id|src_channels
(braket
id|ttable-&gt;srcs
(braket
id|srcidx
)braket
dot
id|channel
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|src_channel-&gt;enabled
)paren
r_continue
suffix:semicolon
id|srcs
(braket
id|srcidx1
)braket
op_assign
id|src_channel-&gt;area.addr
op_plus
id|src_channel-&gt;area.first
op_div
l_int|8
suffix:semicolon
id|src_steps
(braket
id|srcidx1
)braket
op_assign
id|src_channel-&gt;area.step
op_div
l_int|8
suffix:semicolon
id|src_tt
(braket
id|srcidx1
)braket
op_assign
id|ttable-&gt;srcs
(braket
id|srcidx
)braket
suffix:semicolon
id|srcidx1
op_increment
suffix:semicolon
)brace
id|nsrcs
op_assign
id|srcidx1
suffix:semicolon
r_if
c_cond
(paren
id|nsrcs
op_eq
l_int|0
)paren
(brace
id|route_to_channel_from_zero
c_func
(paren
id|plugin
comma
id|src_channels
comma
id|dst_channel
comma
id|ttable
comma
id|frames
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nsrcs
op_eq
l_int|1
op_logical_and
id|src_tt
(braket
l_int|0
)braket
dot
id|as_int
op_eq
id|ROUTE_PLUGIN_RESOLUTION
)paren
(brace
id|route_to_channel_from_one
c_func
(paren
id|plugin
comma
id|src_channels
comma
id|dst_channel
comma
id|ttable
comma
id|frames
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dst_channel-&gt;enabled
op_assign
l_int|1
suffix:semicolon
id|zero
op_assign
id|zero_labels
(braket
id|data-&gt;sum_type
)braket
suffix:semicolon
id|get
op_assign
id|get_u_labels
(braket
id|data-&gt;get
)braket
suffix:semicolon
id|add
op_assign
id|add_labels
(braket
id|data-&gt;sum_type
op_star
l_int|2
op_plus
id|ttable-&gt;att
)braket
suffix:semicolon
id|norm
op_assign
id|norm_labels
(braket
id|data-&gt;sum_type
op_star
l_int|8
op_plus
id|ttable-&gt;att
op_star
l_int|4
op_plus
l_int|4
op_minus
id|data-&gt;src_sample_size
)braket
suffix:semicolon
id|put_u32
op_assign
id|put_u32_labels
(braket
id|data-&gt;put
)braket
suffix:semicolon
id|dst
op_assign
id|dst_channel-&gt;area.addr
op_plus
id|dst_channel-&gt;area.first
op_div
l_int|8
suffix:semicolon
id|dst_step
op_assign
id|dst_channel-&gt;area.step
op_div
l_int|8
suffix:semicolon
r_while
c_loop
(paren
id|frames
op_decrement
OG
l_int|0
)paren
(brace
id|ttable_src_t
op_star
id|ttp
op_assign
id|src_tt
suffix:semicolon
id|sum_t
id|sum
suffix:semicolon
multiline_comment|/* Zero sum */
r_goto
op_star
id|zero
suffix:semicolon
id|zero_int32
suffix:colon
id|sum.as_uint32
op_assign
l_int|0
suffix:semicolon
r_goto
id|zero_end
suffix:semicolon
id|zero_int64
suffix:colon
id|sum.as_uint64
op_assign
l_int|0
suffix:semicolon
r_goto
id|zero_end
suffix:semicolon
macro_line|#if ROUTE_PLUGIN_USE_FLOAT
id|zero_float
suffix:colon
id|sum.as_float
op_assign
l_float|0.0
suffix:semicolon
r_goto
id|zero_end
suffix:semicolon
macro_line|#endif
id|zero_end
suffix:colon
r_for
c_loop
(paren
id|srcidx
op_assign
l_int|0
suffix:semicolon
id|srcidx
OL
id|nsrcs
suffix:semicolon
op_increment
id|srcidx
)paren
(brace
r_char
op_star
id|src
op_assign
id|srcs
(braket
id|srcidx
)braket
suffix:semicolon
multiline_comment|/* Get sample */
r_goto
op_star
id|get
suffix:semicolon
DECL|macro|GET_U_END
mdefine_line|#define GET_U_END after_get
macro_line|#include &quot;plugin_ops.h&quot;
DECL|macro|GET_U_END
macro_line|#undef GET_U_END
id|after_get
suffix:colon
multiline_comment|/* Sum */
r_goto
op_star
id|add
suffix:semicolon
id|add_int32_att
suffix:colon
id|sum.as_uint32
op_add_assign
id|sample
op_star
id|ttp-&gt;as_int
suffix:semicolon
r_goto
id|after_sum
suffix:semicolon
id|add_int32_noatt
suffix:colon
r_if
c_cond
(paren
id|ttp-&gt;as_int
)paren
id|sum.as_uint32
op_add_assign
id|sample
suffix:semicolon
r_goto
id|after_sum
suffix:semicolon
id|add_int64_att
suffix:colon
id|sum.as_uint64
op_add_assign
(paren
id|u_int64_t
)paren
id|sample
op_star
id|ttp-&gt;as_int
suffix:semicolon
r_goto
id|after_sum
suffix:semicolon
id|add_int64_noatt
suffix:colon
r_if
c_cond
(paren
id|ttp-&gt;as_int
)paren
id|sum.as_uint64
op_add_assign
id|sample
suffix:semicolon
r_goto
id|after_sum
suffix:semicolon
macro_line|#if ROUTE_PLUGIN_USE_FLOAT
id|add_float_att
suffix:colon
id|sum.as_float
op_add_assign
id|sample
op_star
id|ttp-&gt;as_float
suffix:semicolon
r_goto
id|after_sum
suffix:semicolon
id|add_float_noatt
suffix:colon
r_if
c_cond
(paren
id|ttp-&gt;as_int
)paren
id|sum.as_float
op_add_assign
id|sample
suffix:semicolon
r_goto
id|after_sum
suffix:semicolon
macro_line|#endif
id|after_sum
suffix:colon
id|srcs
(braket
id|srcidx
)braket
op_add_assign
id|src_steps
(braket
id|srcidx
)braket
suffix:semicolon
id|ttp
op_increment
suffix:semicolon
)brace
multiline_comment|/* Normalization */
r_goto
op_star
id|norm
suffix:semicolon
id|norm_int32_8_att
suffix:colon
id|sum.as_uint64
op_assign
id|sum.as_uint32
suffix:semicolon
id|norm_int64_8_att
suffix:colon
id|sum.as_uint64
op_lshift_assign
l_int|8
suffix:semicolon
id|norm_int64_0_att
suffix:colon
id|div
c_func
(paren
id|sum.as_uint64
)paren
suffix:semicolon
r_goto
id|norm_int
suffix:semicolon
id|norm_int32_16_att
suffix:colon
id|sum.as_uint64
op_assign
id|sum.as_uint32
suffix:semicolon
id|norm_int64_16_att
suffix:colon
id|sum.as_uint64
op_lshift_assign
l_int|16
suffix:semicolon
id|div
c_func
(paren
id|sum.as_uint64
)paren
suffix:semicolon
r_goto
id|norm_int
suffix:semicolon
id|norm_int32_24_att
suffix:colon
id|sum.as_uint64
op_assign
id|sum.as_uint32
suffix:semicolon
id|norm_int64_24_att
suffix:colon
id|sum.as_uint64
op_lshift_assign
l_int|24
suffix:semicolon
id|div
c_func
(paren
id|sum.as_uint64
)paren
suffix:semicolon
r_goto
id|norm_int
suffix:semicolon
id|norm_int32_8_noatt
suffix:colon
id|sum.as_uint64
op_assign
id|sum.as_uint32
suffix:semicolon
id|norm_int64_8_noatt
suffix:colon
id|sum.as_uint64
op_lshift_assign
l_int|8
suffix:semicolon
r_goto
id|norm_int
suffix:semicolon
id|norm_int32_16_noatt
suffix:colon
id|sum.as_uint64
op_assign
id|sum.as_uint32
suffix:semicolon
id|norm_int64_16_noatt
suffix:colon
id|sum.as_uint64
op_lshift_assign
l_int|16
suffix:semicolon
r_goto
id|norm_int
suffix:semicolon
id|norm_int32_24_noatt
suffix:colon
id|sum.as_uint64
op_assign
id|sum.as_uint32
suffix:semicolon
id|norm_int64_24_noatt
suffix:colon
id|sum.as_uint64
op_lshift_assign
l_int|24
suffix:semicolon
r_goto
id|norm_int
suffix:semicolon
id|norm_int64_0_noatt
suffix:colon
id|norm_int
suffix:colon
r_if
c_cond
(paren
id|sum.as_uint64
OG
(paren
id|u_int32_t
)paren
l_int|0xffffffff
)paren
id|sample
op_assign
(paren
id|u_int32_t
)paren
l_int|0xffffffff
suffix:semicolon
r_else
id|sample
op_assign
id|sum.as_uint64
suffix:semicolon
r_goto
id|after_norm
suffix:semicolon
macro_line|#if ROUTE_PLUGIN_USE_FLOAT
id|norm_float_8
suffix:colon
id|sum.as_float
op_mul_assign
l_int|1
op_lshift
l_int|8
suffix:semicolon
r_goto
id|norm_float
suffix:semicolon
id|norm_float_16
suffix:colon
id|sum.as_float
op_mul_assign
l_int|1
op_lshift
l_int|16
suffix:semicolon
r_goto
id|norm_float
suffix:semicolon
id|norm_float_24
suffix:colon
id|sum.as_float
op_mul_assign
l_int|1
op_lshift
l_int|24
suffix:semicolon
r_goto
id|norm_float
suffix:semicolon
id|norm_float_0
suffix:colon
id|norm_float
suffix:colon
id|sum.as_float
op_assign
id|floor
c_func
(paren
id|sum.as_float
op_plus
l_float|0.5
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sum.as_float
OG
(paren
id|u_int32_t
)paren
l_int|0xffffffff
)paren
id|sample
op_assign
(paren
id|u_int32_t
)paren
l_int|0xffffffff
suffix:semicolon
r_else
id|sample
op_assign
id|sum.as_float
suffix:semicolon
r_goto
id|after_norm
suffix:semicolon
macro_line|#endif
id|after_norm
suffix:colon
multiline_comment|/* Put sample */
r_goto
op_star
id|put_u32
suffix:semicolon
DECL|macro|PUT_U32_END
mdefine_line|#define PUT_U32_END after_put_u32
macro_line|#include &quot;plugin_ops.h&quot;
DECL|macro|PUT_U32_END
macro_line|#undef PUT_U32_END
id|after_put_u32
suffix:colon
id|dst
op_add_assign
id|dst_step
suffix:semicolon
)brace
)brace
DECL|function|route_src_channels_mask
r_int
id|route_src_channels_mask
c_func
(paren
id|snd_pcm_plugin_t
op_star
id|plugin
comma
id|bitset_t
op_star
id|dst_vmask
comma
id|bitset_t
op_star
op_star
id|src_vmask
)paren
(brace
id|route_t
op_star
id|data
op_assign
(paren
id|route_t
op_star
)paren
id|plugin-&gt;extra_data
suffix:semicolon
r_int
id|schannels
op_assign
id|plugin-&gt;src_format.channels
suffix:semicolon
r_int
id|dchannels
op_assign
id|plugin-&gt;dst_format.channels
suffix:semicolon
id|bitset_t
op_star
id|vmask
op_assign
id|plugin-&gt;src_vmask
suffix:semicolon
r_int
id|channel
suffix:semicolon
id|ttable_dst_t
op_star
id|dp
op_assign
id|data-&gt;ttable
suffix:semicolon
id|bitset_zero
c_func
(paren
id|vmask
comma
id|schannels
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
id|dchannels
suffix:semicolon
id|channel
op_increment
comma
id|dp
op_increment
)paren
(brace
r_int
r_int
id|src
suffix:semicolon
id|ttable_src_t
op_star
id|sp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bitset_get
c_func
(paren
id|dst_vmask
comma
id|channel
)paren
)paren
r_continue
suffix:semicolon
id|sp
op_assign
id|dp-&gt;srcs
suffix:semicolon
r_for
c_loop
(paren
id|src
op_assign
l_int|0
suffix:semicolon
id|src
OL
id|dp-&gt;nsrcs
suffix:semicolon
id|src
op_increment
comma
id|sp
op_increment
)paren
id|bitset_set
c_func
(paren
id|vmask
comma
id|sp-&gt;channel
)paren
suffix:semicolon
)brace
op_star
id|src_vmask
op_assign
id|vmask
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|route_dst_channels_mask
r_int
id|route_dst_channels_mask
c_func
(paren
id|snd_pcm_plugin_t
op_star
id|plugin
comma
id|bitset_t
op_star
id|src_vmask
comma
id|bitset_t
op_star
op_star
id|dst_vmask
)paren
(brace
id|route_t
op_star
id|data
op_assign
(paren
id|route_t
op_star
)paren
id|plugin-&gt;extra_data
suffix:semicolon
r_int
id|dchannels
op_assign
id|plugin-&gt;dst_format.channels
suffix:semicolon
id|bitset_t
op_star
id|vmask
op_assign
id|plugin-&gt;dst_vmask
suffix:semicolon
r_int
id|channel
suffix:semicolon
id|ttable_dst_t
op_star
id|dp
op_assign
id|data-&gt;ttable
suffix:semicolon
id|bitset_zero
c_func
(paren
id|vmask
comma
id|dchannels
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
id|dchannels
suffix:semicolon
id|channel
op_increment
comma
id|dp
op_increment
)paren
(brace
r_int
r_int
id|src
suffix:semicolon
id|ttable_src_t
op_star
id|sp
suffix:semicolon
id|sp
op_assign
id|dp-&gt;srcs
suffix:semicolon
r_for
c_loop
(paren
id|src
op_assign
l_int|0
suffix:semicolon
id|src
OL
id|dp-&gt;nsrcs
suffix:semicolon
id|src
op_increment
comma
id|sp
op_increment
)paren
(brace
r_if
c_cond
(paren
id|bitset_get
c_func
(paren
id|src_vmask
comma
id|sp-&gt;channel
)paren
)paren
(brace
id|bitset_set
c_func
(paren
id|vmask
comma
id|channel
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
op_star
id|dst_vmask
op_assign
id|vmask
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|route_free
r_static
r_void
id|route_free
c_func
(paren
id|snd_pcm_plugin_t
op_star
id|plugin
)paren
(brace
id|route_t
op_star
id|data
op_assign
(paren
id|route_t
op_star
)paren
id|plugin-&gt;extra_data
suffix:semicolon
r_int
r_int
id|dst_channel
suffix:semicolon
r_for
c_loop
(paren
id|dst_channel
op_assign
l_int|0
suffix:semicolon
id|dst_channel
OL
id|plugin-&gt;dst_format.channels
suffix:semicolon
op_increment
id|dst_channel
)paren
(brace
r_if
c_cond
(paren
id|data-&gt;ttable
(braket
id|dst_channel
)braket
dot
id|srcs
op_ne
l_int|NULL
)paren
id|kfree
c_func
(paren
id|data-&gt;ttable
(braket
id|dst_channel
)braket
dot
id|srcs
)paren
suffix:semicolon
)brace
)brace
DECL|function|route_load_ttable
r_static
r_int
id|route_load_ttable
c_func
(paren
id|snd_pcm_plugin_t
op_star
id|plugin
comma
r_const
id|route_ttable_entry_t
op_star
id|src_ttable
)paren
(brace
id|route_t
op_star
id|data
suffix:semicolon
r_int
r_int
id|src_channel
comma
id|dst_channel
suffix:semicolon
r_const
id|route_ttable_entry_t
op_star
id|sptr
suffix:semicolon
id|ttable_dst_t
op_star
id|dptr
suffix:semicolon
r_if
c_cond
(paren
id|src_ttable
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|data
op_assign
(paren
id|route_t
op_star
)paren
id|plugin-&gt;extra_data
suffix:semicolon
id|dptr
op_assign
id|data-&gt;ttable
suffix:semicolon
id|sptr
op_assign
id|src_ttable
suffix:semicolon
id|plugin-&gt;private_free
op_assign
id|route_free
suffix:semicolon
r_for
c_loop
(paren
id|dst_channel
op_assign
l_int|0
suffix:semicolon
id|dst_channel
OL
id|plugin-&gt;dst_format.channels
suffix:semicolon
op_increment
id|dst_channel
)paren
(brace
id|route_ttable_entry_t
id|t
op_assign
l_int|0
suffix:semicolon
r_int
id|att
op_assign
l_int|0
suffix:semicolon
r_int
id|nsrcs
op_assign
l_int|0
suffix:semicolon
id|ttable_src_t
id|srcs
(braket
id|plugin-&gt;src_format.channels
)braket
suffix:semicolon
r_for
c_loop
(paren
id|src_channel
op_assign
l_int|0
suffix:semicolon
id|src_channel
OL
id|plugin-&gt;src_format.channels
suffix:semicolon
op_increment
id|src_channel
)paren
(brace
id|snd_assert
c_func
(paren
op_star
id|sptr
op_ge
l_int|0
op_logical_or
op_star
id|sptr
op_le
id|FULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|sptr
op_ne
l_int|0
)paren
(brace
id|srcs
(braket
id|nsrcs
)braket
dot
id|channel
op_assign
id|src_channel
suffix:semicolon
macro_line|#if ROUTE_PLUGIN_USE_FLOAT
multiline_comment|/* Also in user space for non attenuated */
id|srcs
(braket
id|nsrcs
)braket
dot
id|as_int
op_assign
(paren
op_star
id|sptr
op_eq
id|FULL
ques
c_cond
id|ROUTE_PLUGIN_RESOLUTION
suffix:colon
l_int|0
)paren
suffix:semicolon
id|srcs
(braket
id|nsrcs
)braket
dot
id|as_float
op_assign
op_star
id|sptr
suffix:semicolon
macro_line|#else
id|srcs
(braket
id|nsrcs
)braket
dot
id|as_int
op_assign
op_star
id|sptr
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_star
id|sptr
op_ne
id|FULL
)paren
id|att
op_assign
l_int|1
suffix:semicolon
id|t
op_add_assign
op_star
id|sptr
suffix:semicolon
id|nsrcs
op_increment
suffix:semicolon
)brace
id|sptr
op_increment
suffix:semicolon
)brace
id|dptr-&gt;att
op_assign
id|att
suffix:semicolon
id|dptr-&gt;nsrcs
op_assign
id|nsrcs
suffix:semicolon
r_if
c_cond
(paren
id|nsrcs
op_eq
l_int|0
)paren
id|dptr-&gt;func
op_assign
id|route_to_channel_from_zero
suffix:semicolon
r_else
r_if
c_cond
(paren
id|nsrcs
op_eq
l_int|1
op_logical_and
op_logical_neg
id|att
)paren
id|dptr-&gt;func
op_assign
id|route_to_channel_from_one
suffix:semicolon
r_else
id|dptr-&gt;func
op_assign
id|route_to_channel
suffix:semicolon
r_if
c_cond
(paren
id|nsrcs
OG
l_int|0
)paren
(brace
r_int
id|srcidx
suffix:semicolon
id|dptr-&gt;srcs
op_assign
id|snd_kcalloc
c_func
(paren
id|nsrcs
op_star
r_sizeof
(paren
op_star
id|srcs
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_for
c_loop
(paren
id|srcidx
op_assign
l_int|0
suffix:semicolon
id|srcidx
OL
id|nsrcs
suffix:semicolon
id|srcidx
op_increment
)paren
(brace
id|dptr-&gt;srcs
(braket
id|srcidx
)braket
op_assign
id|srcs
(braket
id|srcidx
)braket
suffix:semicolon
)brace
)brace
r_else
id|dptr-&gt;srcs
op_assign
l_int|0
suffix:semicolon
id|dptr
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|route_transfer
r_static
id|snd_pcm_sframes_t
id|route_transfer
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
comma
id|snd_pcm_uframes_t
id|frames
)paren
(brace
id|route_t
op_star
id|data
suffix:semicolon
r_int
id|src_nchannels
comma
id|dst_nchannels
suffix:semicolon
r_int
id|dst_channel
suffix:semicolon
id|ttable_dst_t
op_star
id|ttp
suffix:semicolon
id|snd_pcm_plugin_channel_t
op_star
id|dvp
suffix:semicolon
id|snd_assert
c_func
(paren
id|plugin
op_ne
l_int|NULL
op_logical_and
id|src_channels
op_ne
l_int|NULL
op_logical_and
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
id|frames
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|data
op_assign
(paren
id|route_t
op_star
)paren
id|plugin-&gt;extra_data
suffix:semicolon
id|src_nchannels
op_assign
id|plugin-&gt;src_format.channels
suffix:semicolon
id|dst_nchannels
op_assign
id|plugin-&gt;dst_format.channels
suffix:semicolon
macro_line|#ifdef CONFIG_SND_DEBUG
(brace
r_int
id|src_channel
suffix:semicolon
r_for
c_loop
(paren
id|src_channel
op_assign
l_int|0
suffix:semicolon
id|src_channel
OL
id|src_nchannels
suffix:semicolon
op_increment
id|src_channel
)paren
(brace
id|snd_assert
c_func
(paren
id|src_channels
(braket
id|src_channel
)braket
dot
id|area.first
op_mod
l_int|8
op_eq
l_int|0
op_logical_or
id|src_channels
(braket
id|src_channel
)braket
dot
id|area.step
op_mod
l_int|8
op_eq
l_int|0
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|dst_channel
op_assign
l_int|0
suffix:semicolon
id|dst_channel
OL
id|dst_nchannels
suffix:semicolon
op_increment
id|dst_channel
)paren
(brace
id|snd_assert
c_func
(paren
id|dst_channels
(braket
id|dst_channel
)braket
dot
id|area.first
op_mod
l_int|8
op_eq
l_int|0
op_logical_or
id|dst_channels
(braket
id|dst_channel
)braket
dot
id|area.step
op_mod
l_int|8
op_eq
l_int|0
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
id|ttp
op_assign
id|data-&gt;ttable
suffix:semicolon
id|dvp
op_assign
id|dst_channels
suffix:semicolon
r_for
c_loop
(paren
id|dst_channel
op_assign
l_int|0
suffix:semicolon
id|dst_channel
OL
id|dst_nchannels
suffix:semicolon
op_increment
id|dst_channel
)paren
(brace
id|ttp
op_member_access_from_pointer
id|func
c_func
(paren
id|plugin
comma
id|src_channels
comma
id|dvp
comma
id|ttp
comma
id|frames
)paren
suffix:semicolon
id|dvp
op_increment
suffix:semicolon
id|ttp
op_increment
suffix:semicolon
)brace
r_return
id|frames
suffix:semicolon
)brace
DECL|function|getput_index
r_int
id|getput_index
c_func
(paren
r_int
id|format
)paren
(brace
r_int
id|sign
comma
id|width
comma
id|endian
suffix:semicolon
id|sign
op_assign
op_logical_neg
id|snd_pcm_format_signed
c_func
(paren
id|format
)paren
suffix:semicolon
id|width
op_assign
id|snd_pcm_format_width
c_func
(paren
id|format
)paren
op_div
l_int|8
op_minus
l_int|1
suffix:semicolon
macro_line|#ifdef SNDRV_LITTLE_ENDIAN
id|endian
op_assign
id|snd_pcm_format_big_endian
c_func
(paren
id|format
)paren
suffix:semicolon
macro_line|#else
id|endian
op_assign
id|snd_pcm_format_little_endian
c_func
(paren
id|format
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|endian
OL
l_int|0
)paren
id|endian
op_assign
l_int|0
suffix:semicolon
r_return
id|width
op_star
l_int|4
op_plus
id|endian
op_star
l_int|2
op_plus
id|sign
suffix:semicolon
)brace
DECL|function|snd_pcm_plugin_build_route
r_int
id|snd_pcm_plugin_build_route
c_func
(paren
id|snd_pcm_plug_t
op_star
id|plug
comma
id|snd_pcm_plugin_format_t
op_star
id|src_format
comma
id|snd_pcm_plugin_format_t
op_star
id|dst_format
comma
id|route_ttable_entry_t
op_star
id|ttable
comma
id|snd_pcm_plugin_t
op_star
op_star
id|r_plugin
)paren
(brace
id|route_t
op_star
id|data
suffix:semicolon
id|snd_pcm_plugin_t
op_star
id|plugin
suffix:semicolon
r_int
id|err
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
id|src_format-&gt;rate
op_eq
id|dst_format-&gt;rate
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|snd_pcm_format_linear
c_func
(paren
id|src_format-&gt;format
)paren
op_ne
l_int|0
op_logical_and
id|snd_pcm_format_linear
c_func
(paren
id|dst_format-&gt;format
)paren
op_ne
l_int|0
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|err
op_assign
id|snd_pcm_plugin_build
c_func
(paren
id|plug
comma
l_string|&quot;attenuated route conversion&quot;
comma
id|src_format
comma
id|dst_format
comma
r_sizeof
(paren
id|route_t
)paren
op_plus
r_sizeof
(paren
id|data-&gt;ttable
(braket
l_int|0
)braket
)paren
op_star
id|dst_format-&gt;channels
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
id|data
op_assign
(paren
id|route_t
op_star
)paren
id|plugin-&gt;extra_data
suffix:semicolon
id|data-&gt;get
op_assign
id|getput_index
c_func
(paren
id|src_format-&gt;format
)paren
suffix:semicolon
id|data-&gt;put
op_assign
id|getput_index
c_func
(paren
id|dst_format-&gt;format
)paren
suffix:semicolon
id|data-&gt;conv
op_assign
id|conv_index
c_func
(paren
id|src_format-&gt;format
comma
id|dst_format-&gt;format
)paren
suffix:semicolon
macro_line|#if ROUTE_PLUGIN_USE_FLOAT
id|data-&gt;sum_type
op_assign
id|FLOAT
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|snd_pcm_format_width
c_func
(paren
id|src_format-&gt;format
)paren
op_eq
l_int|32
)paren
id|data-&gt;sum_type
op_assign
id|UINT64
suffix:semicolon
r_else
id|data-&gt;sum_type
op_assign
id|UINT32
suffix:semicolon
macro_line|#endif
id|data-&gt;src_sample_size
op_assign
id|snd_pcm_format_width
c_func
(paren
id|src_format-&gt;format
)paren
op_div
l_int|8
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|route_load_ttable
c_func
(paren
id|plugin
comma
id|ttable
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_pcm_plugin_free
c_func
(paren
id|plugin
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|plugin-&gt;transfer
op_assign
id|route_transfer
suffix:semicolon
id|plugin-&gt;src_channels_mask
op_assign
id|route_src_channels_mask
suffix:semicolon
id|plugin-&gt;dst_channels_mask
op_assign
id|route_dst_channels_mask
suffix:semicolon
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