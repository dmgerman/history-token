multiline_comment|/*&n; *   Additional mixer mapping&n; *&n; *   Copyright (c) 2002 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|struct|usbmix_name_map
r_struct
id|usbmix_name_map
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|control
r_int
id|control
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|usbmix_ctl_map
r_struct
id|usbmix_ctl_map
(brace
DECL|member|vendor
r_int
id|vendor
suffix:semicolon
DECL|member|product
r_int
id|product
suffix:semicolon
DECL|member|map
r_const
r_struct
id|usbmix_name_map
op_star
id|map
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * USB control mappers for SB Exitigy&n; */
multiline_comment|/*&n; * Topology of SB Extigy (see on the wide screen :)&n;&n;USB_IN[1] ---&gt;FU[2]------------------------------+-&gt;MU[16]--&gt;PU[17]-+-&gt;FU[18]--+-&gt;EU[27]--+-&gt;EU[21]--&gt;FU[22]--+-&gt;FU[23] &gt; Dig_OUT[24]&n;                                                 ^                  |          |          |                   |&n;USB_IN[3] -+-&gt;SU[5]--&gt;FU[6]--+-&gt;MU[14] -&gt;PU[15]-&gt;+                  |          |          |                   +-&gt;FU[25] &gt; Dig_OUT[26]&n;           ^                 ^                   |                  |          |          |&n;Dig_IN[4] -+                 |                   |                  |          |          +-&gt;FU[28]---------------------&gt; Spk_OUT[19]&n;                             |                   |                  |          |&n;Lin-IN[7] -+--&gt;FU[8]---------+                   |                  |          +----------------------------------------&gt; Hph_OUT[20]&n;           |                                     |                  |&n;Mic-IN[9] --+-&gt;FU[10]----------------------------+                  |&n;           ||                                                       |&n;           ||  +----------------------------------------------------+&n;           VV  V&n;           ++--+-&gt;SU[11]--&gt;FU[12] --------------------------------------------------------------------------------------&gt; USB_OUT[13]&n;*/
DECL|variable|extigy_map
r_static
r_struct
id|usbmix_name_map
id|extigy_map
(braket
)braket
op_assign
(brace
multiline_comment|/* 1: IT pcm */
(brace
l_int|2
comma
l_string|&quot;PCM Playback&quot;
)brace
comma
multiline_comment|/* FU */
multiline_comment|/* 3: IT pcm */
multiline_comment|/* 4: IT digital in */
(brace
l_int|5
comma
l_string|&quot;Digital In Playback Source&quot;
)brace
comma
multiline_comment|/* SU */
(brace
l_int|6
comma
l_string|&quot;Digital In&quot;
)brace
comma
multiline_comment|/* FU */
multiline_comment|/* 7: IT line */
(brace
l_int|8
comma
l_string|&quot;Line Playback&quot;
)brace
comma
multiline_comment|/* FU */
multiline_comment|/* 9: IT mic */
(brace
l_int|10
comma
l_string|&quot;Mic Playback&quot;
)brace
comma
multiline_comment|/* FU */
(brace
l_int|11
comma
l_string|&quot;Capture Source&quot;
)brace
comma
multiline_comment|/* SU */
(brace
l_int|12
comma
l_string|&quot;Capture&quot;
)brace
comma
multiline_comment|/* FU */
multiline_comment|/* 13: OT pcm capture */
multiline_comment|/* 14: MU (w/o controls) */
multiline_comment|/* 15: PU (3D enh) */
multiline_comment|/* 16: MU (w/o controls) */
multiline_comment|/* 17: PU (updown) */
multiline_comment|/* FIXME: what control? */
(brace
l_int|18
comma
l_string|&quot;Tone Control - Bass&quot;
comma
id|USB_FEATURE_BASS
)brace
comma
multiline_comment|/* FU */
(brace
l_int|18
comma
l_string|&quot;Tone Control - Treble&quot;
comma
id|USB_FEATURE_TREBLE
)brace
comma
multiline_comment|/* FU */
(brace
l_int|18
comma
l_string|&quot;Master Playback&quot;
)brace
comma
multiline_comment|/* FU; others */
multiline_comment|/* 19: OT speaker */
multiline_comment|/* 20: OT headphone */
(brace
l_int|21
comma
l_string|&quot;Digital Out Extension&quot;
)brace
comma
multiline_comment|/* EU */
multiline_comment|/* FIXME: what? */
(brace
l_int|22
comma
l_string|&quot;Digital Out Playback&quot;
)brace
comma
multiline_comment|/* FU */
(brace
l_int|23
comma
l_string|&quot;Digital Out1 Playback&quot;
)brace
comma
multiline_comment|/* FU */
multiline_comment|/* FIXME: corresponds to 24 */
multiline_comment|/* 24: OT digital out */
(brace
l_int|25
comma
l_string|&quot;Digital Out2 Playback&quot;
)brace
comma
multiline_comment|/* FU */
multiline_comment|/* FIXME: corresponds to 26 */
multiline_comment|/* 26: OT digital out */
(brace
l_int|27
comma
l_string|&quot;Output Extension&quot;
)brace
comma
multiline_comment|/* EU */
multiline_comment|/* FIXME: what? */
multiline_comment|/* 28: FU (mute) */
(brace
l_int|0
)brace
multiline_comment|/* terminator */
)brace
suffix:semicolon
multiline_comment|/*&n; * Control map entries&n; */
DECL|variable|usbmix_ctl_maps
r_static
r_struct
id|usbmix_ctl_map
id|usbmix_ctl_maps
(braket
)braket
op_assign
(brace
(brace
l_int|0x41e
comma
l_int|0x3000
comma
id|extigy_map
)brace
comma
(brace
l_int|0
)brace
multiline_comment|/* terminator */
)brace
suffix:semicolon
eof
