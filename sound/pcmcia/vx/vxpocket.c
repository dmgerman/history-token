multiline_comment|/*&n; * Driver for Digigram VXpocket V2/440 soundcards&n; *&n; * Copyright (c) 2002 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
multiline_comment|/*&n; please add the following as /etc/pcmcia/vxpocket.conf:&n; &n;  device &quot;snd-vxpocket&quot;&n;     class &quot;audio&quot; module &quot;snd-vxpocket&quot;&n;&n;  card &quot;Digigram VX-POCKET&quot;&n;    manfid 0x01f1, 0x0100&n;    bind &quot;snd-vxpocket&quot;&n;&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &quot;vxpocket.h&quot;
macro_line|#include &lt;sound/initval.h&gt;
multiline_comment|/*&n; */
macro_line|#ifdef COMPILE_VXP440
DECL|macro|CARD_NAME
mdefine_line|#define CARD_NAME&t;&quot;VXPocket440&quot;
macro_line|#else
DECL|macro|CARD_NAME
mdefine_line|#define CARD_NAME&t;&quot;VXPocket&quot;
macro_line|#endif
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Takashi Iwai &lt;tiwai@suse.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Digigram &quot;
id|CARD_NAME
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;{{Digigram,&quot;
id|CARD_NAME
l_string|&quot;}}&quot;
)paren
suffix:semicolon
DECL|variable|index
r_static
r_int
id|index
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_IDX
suffix:semicolon
multiline_comment|/* Index 0-MAX */
DECL|variable|id
r_static
r_char
op_star
id|id
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_STR
suffix:semicolon
multiline_comment|/* ID for this card */
DECL|variable|enable
r_static
r_int
id|enable
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_ENABLE_PNP
suffix:semicolon
multiline_comment|/* Enable switches */
DECL|variable|ibl
r_static
r_int
id|ibl
(braket
id|SNDRV_CARDS
)braket
suffix:semicolon
id|module_param_array
c_func
(paren
id|index
comma
r_int
comma
l_int|NULL
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|index
comma
l_string|&quot;Index value for &quot;
id|CARD_NAME
l_string|&quot; soundcard.&quot;
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|id
comma
id|charp
comma
l_int|NULL
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|id
comma
l_string|&quot;ID string for &quot;
id|CARD_NAME
l_string|&quot; soundcard.&quot;
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|enable
comma
r_bool
comma
l_int|NULL
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|enable
comma
l_string|&quot;Enable &quot;
id|CARD_NAME
l_string|&quot; soundcard.&quot;
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|ibl
comma
r_int
comma
l_int|NULL
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|ibl
comma
l_string|&quot;Capture IBL size for &quot;
id|CARD_NAME
l_string|&quot; soundcard.&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; */
macro_line|#ifdef COMPILE_VXP440
multiline_comment|/* 1 DSP, 1 sync UER, 1 sync World Clock (NIY) */
multiline_comment|/* SMPTE (NIY) */
multiline_comment|/* 2 stereo analog input (line/micro) */
multiline_comment|/* 2 stereo analog output */
multiline_comment|/* Only output levels can be modified */
multiline_comment|/* UER, but only for the first two inputs and outputs. */
DECL|macro|NUM_CODECS
mdefine_line|#define NUM_CODECS&t;2
DECL|macro|CARD_TYPE
mdefine_line|#define CARD_TYPE&t;VX_TYPE_VXP440
DECL|macro|DEV_INFO
mdefine_line|#define DEV_INFO&t;&quot;snd-vxp440&quot;
macro_line|#else
multiline_comment|/* 1 DSP, 1 sync UER */
multiline_comment|/* 1 programmable clock (NIY) */
multiline_comment|/* 1 stereo analog input (line/micro) */
multiline_comment|/* 1 stereo analog output */
multiline_comment|/* Only output levels can be modified */
DECL|macro|NUM_CODECS
mdefine_line|#define NUM_CODECS&t;1
DECL|macro|CARD_TYPE
mdefine_line|#define CARD_TYPE&t;VX_TYPE_VXPOCKET
DECL|macro|DEV_INFO
mdefine_line|#define DEV_INFO&t;&quot;snd-vxpocket&quot;
macro_line|#endif
DECL|variable|dev_info
r_static
id|dev_info_t
id|dev_info
op_assign
id|DEV_INFO
suffix:semicolon
DECL|variable|vxp_hw
r_static
r_struct
id|snd_vx_hardware
id|vxp_hw
op_assign
(brace
dot
id|name
op_assign
id|CARD_NAME
comma
dot
id|type
op_assign
id|CARD_TYPE
comma
multiline_comment|/* hardware specs */
dot
id|num_codecs
op_assign
id|NUM_CODECS
comma
dot
id|num_ins
op_assign
id|NUM_CODECS
comma
dot
id|num_outs
op_assign
id|NUM_CODECS
comma
dot
id|output_level_max
op_assign
id|VX_ANALOG_OUT_LEVEL_MAX
comma
)brace
suffix:semicolon
DECL|variable|hw_entry
r_static
r_struct
id|snd_vxp_entry
id|hw_entry
op_assign
(brace
dot
id|dev_info
op_assign
op_amp
id|dev_info
comma
multiline_comment|/* module parameters */
dot
id|index_table
op_assign
id|index
comma
dot
id|id_table
op_assign
id|id
comma
dot
id|enable_table
op_assign
id|enable
comma
dot
id|ibl
op_assign
id|ibl
comma
multiline_comment|/* h/w config */
dot
id|hardware
op_assign
op_amp
id|vxp_hw
comma
dot
id|ops
op_assign
op_amp
id|snd_vxpocket_ops
comma
)brace
suffix:semicolon
multiline_comment|/*&n; */
DECL|function|vxp_attach
r_static
id|dev_link_t
op_star
id|vxp_attach
c_func
(paren
r_void
)paren
(brace
r_return
id|snd_vxpocket_attach
c_func
(paren
op_amp
id|hw_entry
)paren
suffix:semicolon
)brace
DECL|function|vxp_detach
r_static
r_void
id|vxp_detach
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
id|snd_vxpocket_detach
c_func
(paren
op_amp
id|hw_entry
comma
id|link
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Module entry points&n; */
DECL|variable|vxp_cs_driver
r_static
r_struct
id|pcmcia_driver
id|vxp_cs_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|drv
op_assign
(brace
dot
id|name
op_assign
id|DEV_INFO
comma
)brace
comma
dot
id|attach
op_assign
id|vxp_attach
comma
dot
id|detach
op_assign
id|vxp_detach
)brace
suffix:semicolon
DECL|function|init_vxpocket
r_static
r_int
id|__init
id|init_vxpocket
c_func
(paren
r_void
)paren
(brace
r_return
id|pcmcia_register_driver
c_func
(paren
op_amp
id|vxp_cs_driver
)paren
suffix:semicolon
)brace
DECL|function|exit_vxpocket
r_static
r_void
id|__exit
id|exit_vxpocket
c_func
(paren
r_void
)paren
(brace
id|pcmcia_unregister_driver
c_func
(paren
op_amp
id|vxp_cs_driver
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|hw_entry.dev_list
op_ne
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|init_vxpocket
id|module_init
c_func
(paren
id|init_vxpocket
)paren
suffix:semicolon
DECL|variable|exit_vxpocket
id|module_exit
c_func
(paren
id|exit_vxpocket
)paren
suffix:semicolon
eof
