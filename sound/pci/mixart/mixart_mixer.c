multiline_comment|/*&n; * Driver for Digigram miXart soundcards&n; *&n; * mixer callbacks&n; *&n; * Copyright (c) 2003 by Digigram &lt;alsa@digigram.com&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;mixart.h&quot;
macro_line|#include &quot;mixart_core.h&quot;
macro_line|#include &quot;mixart_hwdep.h&quot;
macro_line|#include &lt;sound/control.h&gt;
macro_line|#include &quot;mixart_mixer.h&quot;
DECL|variable|mixart_analog_level
r_static
id|u32
id|mixart_analog_level
(braket
l_int|256
)braket
op_assign
(brace
l_int|0xc2c00000
comma
multiline_comment|/* [000] -96.0 dB */
l_int|0xc2bf0000
comma
multiline_comment|/* [001] -95.5 dB */
l_int|0xc2be0000
comma
multiline_comment|/* [002] -95.0 dB */
l_int|0xc2bd0000
comma
multiline_comment|/* [003] -94.5 dB */
l_int|0xc2bc0000
comma
multiline_comment|/* [004] -94.0 dB */
l_int|0xc2bb0000
comma
multiline_comment|/* [005] -93.5 dB */
l_int|0xc2ba0000
comma
multiline_comment|/* [006] -93.0 dB */
l_int|0xc2b90000
comma
multiline_comment|/* [007] -92.5 dB */
l_int|0xc2b80000
comma
multiline_comment|/* [008] -92.0 dB */
l_int|0xc2b70000
comma
multiline_comment|/* [009] -91.5 dB */
l_int|0xc2b60000
comma
multiline_comment|/* [010] -91.0 dB */
l_int|0xc2b50000
comma
multiline_comment|/* [011] -90.5 dB */
l_int|0xc2b40000
comma
multiline_comment|/* [012] -90.0 dB */
l_int|0xc2b30000
comma
multiline_comment|/* [013] -89.5 dB */
l_int|0xc2b20000
comma
multiline_comment|/* [014] -89.0 dB */
l_int|0xc2b10000
comma
multiline_comment|/* [015] -88.5 dB */
l_int|0xc2b00000
comma
multiline_comment|/* [016] -88.0 dB */
l_int|0xc2af0000
comma
multiline_comment|/* [017] -87.5 dB */
l_int|0xc2ae0000
comma
multiline_comment|/* [018] -87.0 dB */
l_int|0xc2ad0000
comma
multiline_comment|/* [019] -86.5 dB */
l_int|0xc2ac0000
comma
multiline_comment|/* [020] -86.0 dB */
l_int|0xc2ab0000
comma
multiline_comment|/* [021] -85.5 dB */
l_int|0xc2aa0000
comma
multiline_comment|/* [022] -85.0 dB */
l_int|0xc2a90000
comma
multiline_comment|/* [023] -84.5 dB */
l_int|0xc2a80000
comma
multiline_comment|/* [024] -84.0 dB */
l_int|0xc2a70000
comma
multiline_comment|/* [025] -83.5 dB */
l_int|0xc2a60000
comma
multiline_comment|/* [026] -83.0 dB */
l_int|0xc2a50000
comma
multiline_comment|/* [027] -82.5 dB */
l_int|0xc2a40000
comma
multiline_comment|/* [028] -82.0 dB */
l_int|0xc2a30000
comma
multiline_comment|/* [029] -81.5 dB */
l_int|0xc2a20000
comma
multiline_comment|/* [030] -81.0 dB */
l_int|0xc2a10000
comma
multiline_comment|/* [031] -80.5 dB */
l_int|0xc2a00000
comma
multiline_comment|/* [032] -80.0 dB */
l_int|0xc29f0000
comma
multiline_comment|/* [033] -79.5 dB */
l_int|0xc29e0000
comma
multiline_comment|/* [034] -79.0 dB */
l_int|0xc29d0000
comma
multiline_comment|/* [035] -78.5 dB */
l_int|0xc29c0000
comma
multiline_comment|/* [036] -78.0 dB */
l_int|0xc29b0000
comma
multiline_comment|/* [037] -77.5 dB */
l_int|0xc29a0000
comma
multiline_comment|/* [038] -77.0 dB */
l_int|0xc2990000
comma
multiline_comment|/* [039] -76.5 dB */
l_int|0xc2980000
comma
multiline_comment|/* [040] -76.0 dB */
l_int|0xc2970000
comma
multiline_comment|/* [041] -75.5 dB */
l_int|0xc2960000
comma
multiline_comment|/* [042] -75.0 dB */
l_int|0xc2950000
comma
multiline_comment|/* [043] -74.5 dB */
l_int|0xc2940000
comma
multiline_comment|/* [044] -74.0 dB */
l_int|0xc2930000
comma
multiline_comment|/* [045] -73.5 dB */
l_int|0xc2920000
comma
multiline_comment|/* [046] -73.0 dB */
l_int|0xc2910000
comma
multiline_comment|/* [047] -72.5 dB */
l_int|0xc2900000
comma
multiline_comment|/* [048] -72.0 dB */
l_int|0xc28f0000
comma
multiline_comment|/* [049] -71.5 dB */
l_int|0xc28e0000
comma
multiline_comment|/* [050] -71.0 dB */
l_int|0xc28d0000
comma
multiline_comment|/* [051] -70.5 dB */
l_int|0xc28c0000
comma
multiline_comment|/* [052] -70.0 dB */
l_int|0xc28b0000
comma
multiline_comment|/* [053] -69.5 dB */
l_int|0xc28a0000
comma
multiline_comment|/* [054] -69.0 dB */
l_int|0xc2890000
comma
multiline_comment|/* [055] -68.5 dB */
l_int|0xc2880000
comma
multiline_comment|/* [056] -68.0 dB */
l_int|0xc2870000
comma
multiline_comment|/* [057] -67.5 dB */
l_int|0xc2860000
comma
multiline_comment|/* [058] -67.0 dB */
l_int|0xc2850000
comma
multiline_comment|/* [059] -66.5 dB */
l_int|0xc2840000
comma
multiline_comment|/* [060] -66.0 dB */
l_int|0xc2830000
comma
multiline_comment|/* [061] -65.5 dB */
l_int|0xc2820000
comma
multiline_comment|/* [062] -65.0 dB */
l_int|0xc2810000
comma
multiline_comment|/* [063] -64.5 dB */
l_int|0xc2800000
comma
multiline_comment|/* [064] -64.0 dB */
l_int|0xc27e0000
comma
multiline_comment|/* [065] -63.5 dB */
l_int|0xc27c0000
comma
multiline_comment|/* [066] -63.0 dB */
l_int|0xc27a0000
comma
multiline_comment|/* [067] -62.5 dB */
l_int|0xc2780000
comma
multiline_comment|/* [068] -62.0 dB */
l_int|0xc2760000
comma
multiline_comment|/* [069] -61.5 dB */
l_int|0xc2740000
comma
multiline_comment|/* [070] -61.0 dB */
l_int|0xc2720000
comma
multiline_comment|/* [071] -60.5 dB */
l_int|0xc2700000
comma
multiline_comment|/* [072] -60.0 dB */
l_int|0xc26e0000
comma
multiline_comment|/* [073] -59.5 dB */
l_int|0xc26c0000
comma
multiline_comment|/* [074] -59.0 dB */
l_int|0xc26a0000
comma
multiline_comment|/* [075] -58.5 dB */
l_int|0xc2680000
comma
multiline_comment|/* [076] -58.0 dB */
l_int|0xc2660000
comma
multiline_comment|/* [077] -57.5 dB */
l_int|0xc2640000
comma
multiline_comment|/* [078] -57.0 dB */
l_int|0xc2620000
comma
multiline_comment|/* [079] -56.5 dB */
l_int|0xc2600000
comma
multiline_comment|/* [080] -56.0 dB */
l_int|0xc25e0000
comma
multiline_comment|/* [081] -55.5 dB */
l_int|0xc25c0000
comma
multiline_comment|/* [082] -55.0 dB */
l_int|0xc25a0000
comma
multiline_comment|/* [083] -54.5 dB */
l_int|0xc2580000
comma
multiline_comment|/* [084] -54.0 dB */
l_int|0xc2560000
comma
multiline_comment|/* [085] -53.5 dB */
l_int|0xc2540000
comma
multiline_comment|/* [086] -53.0 dB */
l_int|0xc2520000
comma
multiline_comment|/* [087] -52.5 dB */
l_int|0xc2500000
comma
multiline_comment|/* [088] -52.0 dB */
l_int|0xc24e0000
comma
multiline_comment|/* [089] -51.5 dB */
l_int|0xc24c0000
comma
multiline_comment|/* [090] -51.0 dB */
l_int|0xc24a0000
comma
multiline_comment|/* [091] -50.5 dB */
l_int|0xc2480000
comma
multiline_comment|/* [092] -50.0 dB */
l_int|0xc2460000
comma
multiline_comment|/* [093] -49.5 dB */
l_int|0xc2440000
comma
multiline_comment|/* [094] -49.0 dB */
l_int|0xc2420000
comma
multiline_comment|/* [095] -48.5 dB */
l_int|0xc2400000
comma
multiline_comment|/* [096] -48.0 dB */
l_int|0xc23e0000
comma
multiline_comment|/* [097] -47.5 dB */
l_int|0xc23c0000
comma
multiline_comment|/* [098] -47.0 dB */
l_int|0xc23a0000
comma
multiline_comment|/* [099] -46.5 dB */
l_int|0xc2380000
comma
multiline_comment|/* [100] -46.0 dB */
l_int|0xc2360000
comma
multiline_comment|/* [101] -45.5 dB */
l_int|0xc2340000
comma
multiline_comment|/* [102] -45.0 dB */
l_int|0xc2320000
comma
multiline_comment|/* [103] -44.5 dB */
l_int|0xc2300000
comma
multiline_comment|/* [104] -44.0 dB */
l_int|0xc22e0000
comma
multiline_comment|/* [105] -43.5 dB */
l_int|0xc22c0000
comma
multiline_comment|/* [106] -43.0 dB */
l_int|0xc22a0000
comma
multiline_comment|/* [107] -42.5 dB */
l_int|0xc2280000
comma
multiline_comment|/* [108] -42.0 dB */
l_int|0xc2260000
comma
multiline_comment|/* [109] -41.5 dB */
l_int|0xc2240000
comma
multiline_comment|/* [110] -41.0 dB */
l_int|0xc2220000
comma
multiline_comment|/* [111] -40.5 dB */
l_int|0xc2200000
comma
multiline_comment|/* [112] -40.0 dB */
l_int|0xc21e0000
comma
multiline_comment|/* [113] -39.5 dB */
l_int|0xc21c0000
comma
multiline_comment|/* [114] -39.0 dB */
l_int|0xc21a0000
comma
multiline_comment|/* [115] -38.5 dB */
l_int|0xc2180000
comma
multiline_comment|/* [116] -38.0 dB */
l_int|0xc2160000
comma
multiline_comment|/* [117] -37.5 dB */
l_int|0xc2140000
comma
multiline_comment|/* [118] -37.0 dB */
l_int|0xc2120000
comma
multiline_comment|/* [119] -36.5 dB */
l_int|0xc2100000
comma
multiline_comment|/* [120] -36.0 dB */
l_int|0xc20e0000
comma
multiline_comment|/* [121] -35.5 dB */
l_int|0xc20c0000
comma
multiline_comment|/* [122] -35.0 dB */
l_int|0xc20a0000
comma
multiline_comment|/* [123] -34.5 dB */
l_int|0xc2080000
comma
multiline_comment|/* [124] -34.0 dB */
l_int|0xc2060000
comma
multiline_comment|/* [125] -33.5 dB */
l_int|0xc2040000
comma
multiline_comment|/* [126] -33.0 dB */
l_int|0xc2020000
comma
multiline_comment|/* [127] -32.5 dB */
l_int|0xc2000000
comma
multiline_comment|/* [128] -32.0 dB */
l_int|0xc1fc0000
comma
multiline_comment|/* [129] -31.5 dB */
l_int|0xc1f80000
comma
multiline_comment|/* [130] -31.0 dB */
l_int|0xc1f40000
comma
multiline_comment|/* [131] -30.5 dB */
l_int|0xc1f00000
comma
multiline_comment|/* [132] -30.0 dB */
l_int|0xc1ec0000
comma
multiline_comment|/* [133] -29.5 dB */
l_int|0xc1e80000
comma
multiline_comment|/* [134] -29.0 dB */
l_int|0xc1e40000
comma
multiline_comment|/* [135] -28.5 dB */
l_int|0xc1e00000
comma
multiline_comment|/* [136] -28.0 dB */
l_int|0xc1dc0000
comma
multiline_comment|/* [137] -27.5 dB */
l_int|0xc1d80000
comma
multiline_comment|/* [138] -27.0 dB */
l_int|0xc1d40000
comma
multiline_comment|/* [139] -26.5 dB */
l_int|0xc1d00000
comma
multiline_comment|/* [140] -26.0 dB */
l_int|0xc1cc0000
comma
multiline_comment|/* [141] -25.5 dB */
l_int|0xc1c80000
comma
multiline_comment|/* [142] -25.0 dB */
l_int|0xc1c40000
comma
multiline_comment|/* [143] -24.5 dB */
l_int|0xc1c00000
comma
multiline_comment|/* [144] -24.0 dB */
l_int|0xc1bc0000
comma
multiline_comment|/* [145] -23.5 dB */
l_int|0xc1b80000
comma
multiline_comment|/* [146] -23.0 dB */
l_int|0xc1b40000
comma
multiline_comment|/* [147] -22.5 dB */
l_int|0xc1b00000
comma
multiline_comment|/* [148] -22.0 dB */
l_int|0xc1ac0000
comma
multiline_comment|/* [149] -21.5 dB */
l_int|0xc1a80000
comma
multiline_comment|/* [150] -21.0 dB */
l_int|0xc1a40000
comma
multiline_comment|/* [151] -20.5 dB */
l_int|0xc1a00000
comma
multiline_comment|/* [152] -20.0 dB */
l_int|0xc19c0000
comma
multiline_comment|/* [153] -19.5 dB */
l_int|0xc1980000
comma
multiline_comment|/* [154] -19.0 dB */
l_int|0xc1940000
comma
multiline_comment|/* [155] -18.5 dB */
l_int|0xc1900000
comma
multiline_comment|/* [156] -18.0 dB */
l_int|0xc18c0000
comma
multiline_comment|/* [157] -17.5 dB */
l_int|0xc1880000
comma
multiline_comment|/* [158] -17.0 dB */
l_int|0xc1840000
comma
multiline_comment|/* [159] -16.5 dB */
l_int|0xc1800000
comma
multiline_comment|/* [160] -16.0 dB */
l_int|0xc1780000
comma
multiline_comment|/* [161] -15.5 dB */
l_int|0xc1700000
comma
multiline_comment|/* [162] -15.0 dB */
l_int|0xc1680000
comma
multiline_comment|/* [163] -14.5 dB */
l_int|0xc1600000
comma
multiline_comment|/* [164] -14.0 dB */
l_int|0xc1580000
comma
multiline_comment|/* [165] -13.5 dB */
l_int|0xc1500000
comma
multiline_comment|/* [166] -13.0 dB */
l_int|0xc1480000
comma
multiline_comment|/* [167] -12.5 dB */
l_int|0xc1400000
comma
multiline_comment|/* [168] -12.0 dB */
l_int|0xc1380000
comma
multiline_comment|/* [169] -11.5 dB */
l_int|0xc1300000
comma
multiline_comment|/* [170] -11.0 dB */
l_int|0xc1280000
comma
multiline_comment|/* [171] -10.5 dB */
l_int|0xc1200000
comma
multiline_comment|/* [172] -10.0 dB */
l_int|0xc1180000
comma
multiline_comment|/* [173] -9.5 dB */
l_int|0xc1100000
comma
multiline_comment|/* [174] -9.0 dB */
l_int|0xc1080000
comma
multiline_comment|/* [175] -8.5 dB */
l_int|0xc1000000
comma
multiline_comment|/* [176] -8.0 dB */
l_int|0xc0f00000
comma
multiline_comment|/* [177] -7.5 dB */
l_int|0xc0e00000
comma
multiline_comment|/* [178] -7.0 dB */
l_int|0xc0d00000
comma
multiline_comment|/* [179] -6.5 dB */
l_int|0xc0c00000
comma
multiline_comment|/* [180] -6.0 dB */
l_int|0xc0b00000
comma
multiline_comment|/* [181] -5.5 dB */
l_int|0xc0a00000
comma
multiline_comment|/* [182] -5.0 dB */
l_int|0xc0900000
comma
multiline_comment|/* [183] -4.5 dB */
l_int|0xc0800000
comma
multiline_comment|/* [184] -4.0 dB */
l_int|0xc0600000
comma
multiline_comment|/* [185] -3.5 dB */
l_int|0xc0400000
comma
multiline_comment|/* [186] -3.0 dB */
l_int|0xc0200000
comma
multiline_comment|/* [187] -2.5 dB */
l_int|0xc0000000
comma
multiline_comment|/* [188] -2.0 dB */
l_int|0xbfc00000
comma
multiline_comment|/* [189] -1.5 dB */
l_int|0xbf800000
comma
multiline_comment|/* [190] -1.0 dB */
l_int|0xbf000000
comma
multiline_comment|/* [191] -0.5 dB */
l_int|0x00000000
comma
multiline_comment|/* [192] 0.0 dB */
l_int|0x3f000000
comma
multiline_comment|/* [193] 0.5 dB */
l_int|0x3f800000
comma
multiline_comment|/* [194] 1.0 dB */
l_int|0x3fc00000
comma
multiline_comment|/* [195] 1.5 dB */
l_int|0x40000000
comma
multiline_comment|/* [196] 2.0 dB */
l_int|0x40200000
comma
multiline_comment|/* [197] 2.5 dB */
l_int|0x40400000
comma
multiline_comment|/* [198] 3.0 dB */
l_int|0x40600000
comma
multiline_comment|/* [199] 3.5 dB */
l_int|0x40800000
comma
multiline_comment|/* [200] 4.0 dB */
l_int|0x40900000
comma
multiline_comment|/* [201] 4.5 dB */
l_int|0x40a00000
comma
multiline_comment|/* [202] 5.0 dB */
l_int|0x40b00000
comma
multiline_comment|/* [203] 5.5 dB */
l_int|0x40c00000
comma
multiline_comment|/* [204] 6.0 dB */
l_int|0x40d00000
comma
multiline_comment|/* [205] 6.5 dB */
l_int|0x40e00000
comma
multiline_comment|/* [206] 7.0 dB */
l_int|0x40f00000
comma
multiline_comment|/* [207] 7.5 dB */
l_int|0x41000000
comma
multiline_comment|/* [208] 8.0 dB */
l_int|0x41080000
comma
multiline_comment|/* [209] 8.5 dB */
l_int|0x41100000
comma
multiline_comment|/* [210] 9.0 dB */
l_int|0x41180000
comma
multiline_comment|/* [211] 9.5 dB */
l_int|0x41200000
comma
multiline_comment|/* [212] 10.0 dB */
l_int|0x41280000
comma
multiline_comment|/* [213] 10.5 dB */
l_int|0x41300000
comma
multiline_comment|/* [214] 11.0 dB */
l_int|0x41380000
comma
multiline_comment|/* [215] 11.5 dB */
l_int|0x41400000
comma
multiline_comment|/* [216] 12.0 dB */
l_int|0x41480000
comma
multiline_comment|/* [217] 12.5 dB */
l_int|0x41500000
comma
multiline_comment|/* [218] 13.0 dB */
l_int|0x41580000
comma
multiline_comment|/* [219] 13.5 dB */
l_int|0x41600000
comma
multiline_comment|/* [220] 14.0 dB */
l_int|0x41680000
comma
multiline_comment|/* [221] 14.5 dB */
l_int|0x41700000
comma
multiline_comment|/* [222] 15.0 dB */
l_int|0x41780000
comma
multiline_comment|/* [223] 15.5 dB */
l_int|0x41800000
comma
multiline_comment|/* [224] 16.0 dB */
l_int|0x41840000
comma
multiline_comment|/* [225] 16.5 dB */
l_int|0x41880000
comma
multiline_comment|/* [226] 17.0 dB */
l_int|0x418c0000
comma
multiline_comment|/* [227] 17.5 dB */
l_int|0x41900000
comma
multiline_comment|/* [228] 18.0 dB */
l_int|0x41940000
comma
multiline_comment|/* [229] 18.5 dB */
l_int|0x41980000
comma
multiline_comment|/* [230] 19.0 dB */
l_int|0x419c0000
comma
multiline_comment|/* [231] 19.5 dB */
l_int|0x41a00000
comma
multiline_comment|/* [232] 20.0 dB */
l_int|0x41a40000
comma
multiline_comment|/* [233] 20.5 dB */
l_int|0x41a80000
comma
multiline_comment|/* [234] 21.0 dB */
l_int|0x41ac0000
comma
multiline_comment|/* [235] 21.5 dB */
l_int|0x41b00000
comma
multiline_comment|/* [236] 22.0 dB */
l_int|0x41b40000
comma
multiline_comment|/* [237] 22.5 dB */
l_int|0x41b80000
comma
multiline_comment|/* [238] 23.0 dB */
l_int|0x41bc0000
comma
multiline_comment|/* [239] 23.5 dB */
l_int|0x41c00000
comma
multiline_comment|/* [240] 24.0 dB */
l_int|0x41c40000
comma
multiline_comment|/* [241] 24.5 dB */
l_int|0x41c80000
comma
multiline_comment|/* [242] 25.0 dB */
l_int|0x41cc0000
comma
multiline_comment|/* [243] 25.5 dB */
l_int|0x41d00000
comma
multiline_comment|/* [244] 26.0 dB */
l_int|0x41d40000
comma
multiline_comment|/* [245] 26.5 dB */
l_int|0x41d80000
comma
multiline_comment|/* [246] 27.0 dB */
l_int|0x41dc0000
comma
multiline_comment|/* [247] 27.5 dB */
l_int|0x41e00000
comma
multiline_comment|/* [248] 28.0 dB */
l_int|0x41e40000
comma
multiline_comment|/* [249] 28.5 dB */
l_int|0x41e80000
comma
multiline_comment|/* [250] 29.0 dB */
l_int|0x41ec0000
comma
multiline_comment|/* [251] 29.5 dB */
l_int|0x41f00000
comma
multiline_comment|/* [252] 30.0 dB */
l_int|0x41f40000
comma
multiline_comment|/* [253] 30.5 dB */
l_int|0x41f80000
comma
multiline_comment|/* [254] 31.0 dB */
l_int|0x41fc0000
comma
multiline_comment|/* [255] 31.5 dB */
)brace
suffix:semicolon
DECL|macro|MIXART_ANALOG_CAPTURE_LEVEL_MIN
mdefine_line|#define MIXART_ANALOG_CAPTURE_LEVEL_MIN   0      /* -96.0 dB + 8.0 dB = -88.0 dB */
DECL|macro|MIXART_ANALOG_CAPTURE_LEVEL_MAX
mdefine_line|#define MIXART_ANALOG_CAPTURE_LEVEL_MAX   255    /*  31.5 dB + 8.0 dB =  39.5 dB */
DECL|macro|MIXART_ANALOG_CAPTURE_ZERO_LEVEL
mdefine_line|#define MIXART_ANALOG_CAPTURE_ZERO_LEVEL  176    /*  -8.0 dB + 8.0 dB =  0.0 dB */
DECL|macro|MIXART_ANALOG_PLAYBACK_LEVEL_MIN
mdefine_line|#define MIXART_ANALOG_PLAYBACK_LEVEL_MIN  0      /* -96.0 dB + 1.5 dB = -94.5 dB (possible is down to (-114.0+1.5)dB) */
DECL|macro|MIXART_ANALOG_PLAYBACK_LEVEL_MAX
mdefine_line|#define MIXART_ANALOG_PLAYBACK_LEVEL_MAX  192    /*   0.0 dB + 1.5 dB =  1.5 dB */
DECL|macro|MIXART_ANALOG_PLAYBACK_ZERO_LEVEL
mdefine_line|#define MIXART_ANALOG_PLAYBACK_ZERO_LEVEL 189    /*  -1.5 dB + 1.5 dB =  0.0 dB */
DECL|function|mixart_update_analog_audio_level
r_static
r_int
id|mixart_update_analog_audio_level
c_func
(paren
id|mixart_t
op_star
id|chip
comma
r_int
id|is_capture
)paren
(brace
r_int
id|i
comma
id|err
suffix:semicolon
id|mixart_msg_t
id|request
suffix:semicolon
id|mixart_io_level_t
id|io_level
suffix:semicolon
id|mixart_return_uid_t
id|resp
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|io_level
comma
l_int|0
comma
r_sizeof
(paren
id|io_level
)paren
)paren
suffix:semicolon
id|io_level.channel
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* left and right */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|is_capture
)paren
(brace
id|io_level.level
(braket
id|i
)braket
dot
id|analog_level
op_assign
id|mixart_analog_level
(braket
id|chip-&gt;analog_capture_volume
(braket
id|i
)braket
)braket
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|chip-&gt;analog_playback_active
(braket
id|i
)braket
)paren
(brace
id|io_level.level
(braket
id|i
)braket
dot
id|analog_level
op_assign
id|mixart_analog_level
(braket
id|chip-&gt;analog_playback_volume
(braket
id|i
)braket
)braket
suffix:semicolon
)brace
r_else
id|io_level.level
(braket
id|i
)braket
dot
id|analog_level
op_assign
id|mixart_analog_level
(braket
id|MIXART_ANALOG_PLAYBACK_LEVEL_MIN
)braket
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|is_capture
)paren
(brace
id|request.uid
op_assign
id|chip-&gt;uid_in_analog_physio
suffix:semicolon
)brace
r_else
id|request.uid
op_assign
id|chip-&gt;uid_out_analog_physio
suffix:semicolon
id|request.message_id
op_assign
id|MSG_PHYSICALIO_SET_LEVEL
suffix:semicolon
id|request.data
op_assign
op_amp
id|io_level
suffix:semicolon
id|request.size
op_assign
r_sizeof
(paren
id|io_level
)paren
suffix:semicolon
id|err
op_assign
id|snd_mixart_send_msg
c_func
(paren
id|chip-&gt;mgr
comma
op_amp
id|request
comma
r_sizeof
(paren
id|resp
)paren
comma
op_amp
id|resp
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
OL
l_int|0
)paren
op_logical_or
(paren
id|resp.error_code
)paren
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;error MSG_PHYSICALIO_SET_LEVEL card(%d) is_capture(%d) error_code(%x)&bslash;n&quot;
comma
id|chip-&gt;chip_idx
comma
id|is_capture
comma
id|resp.error_code
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * analog level control&n; */
DECL|function|mixart_analog_vol_info
r_static
r_int
id|mixart_analog_vol_info
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
(brace
id|uinfo-&gt;type
op_assign
id|SNDRV_CTL_ELEM_TYPE_INTEGER
suffix:semicolon
id|uinfo-&gt;count
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|kcontrol-&gt;private_value
op_eq
l_int|0
)paren
(brace
multiline_comment|/* playback */
id|uinfo-&gt;value.integer.min
op_assign
id|MIXART_ANALOG_PLAYBACK_LEVEL_MIN
suffix:semicolon
multiline_comment|/* -96 dB */
id|uinfo-&gt;value.integer.max
op_assign
id|MIXART_ANALOG_PLAYBACK_LEVEL_MAX
suffix:semicolon
multiline_comment|/* 0 dB */
)brace
r_else
(brace
multiline_comment|/* capture */
id|uinfo-&gt;value.integer.min
op_assign
id|MIXART_ANALOG_CAPTURE_LEVEL_MIN
suffix:semicolon
multiline_comment|/* -96 dB */
id|uinfo-&gt;value.integer.max
op_assign
id|MIXART_ANALOG_CAPTURE_LEVEL_MAX
suffix:semicolon
multiline_comment|/* 31.5 dB */
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mixart_analog_vol_get
r_static
r_int
id|mixart_analog_vol_get
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|mixart_t
op_star
id|chip
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kcontrol-&gt;private_value
op_eq
l_int|0
)paren
(brace
multiline_comment|/* playback */
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
id|chip-&gt;analog_playback_volume
(braket
l_int|0
)braket
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|1
)braket
op_assign
id|chip-&gt;analog_playback_volume
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* capture */
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
id|chip-&gt;analog_capture_volume
(braket
l_int|0
)braket
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|1
)braket
op_assign
id|chip-&gt;analog_capture_volume
(braket
l_int|1
)braket
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mixart_analog_vol_put
r_static
r_int
id|mixart_analog_vol_put
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|mixart_t
op_star
id|chip
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
id|changed
op_assign
l_int|0
suffix:semicolon
r_int
id|is_capture
comma
id|i
suffix:semicolon
id|down
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
id|is_capture
op_assign
(paren
id|kcontrol-&gt;private_value
op_ne
l_int|0
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|new_volume
op_assign
id|ucontrol-&gt;value.integer.value
(braket
id|i
)braket
suffix:semicolon
r_int
op_star
id|stored_volume
op_assign
id|is_capture
ques
c_cond
op_amp
id|chip-&gt;analog_capture_volume
(braket
id|i
)braket
suffix:colon
op_amp
id|chip-&gt;analog_playback_volume
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_star
id|stored_volume
op_ne
id|new_volume
)paren
(brace
op_star
id|stored_volume
op_assign
id|new_volume
suffix:semicolon
id|changed
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|changed
)paren
(brace
id|mixart_update_analog_audio_level
c_func
(paren
id|chip
comma
id|is_capture
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
r_return
id|changed
suffix:semicolon
)brace
DECL|variable|mixart_control_analog_level
r_static
id|snd_kcontrol_new_t
id|mixart_control_analog_level
op_assign
(brace
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
multiline_comment|/* name will be filled later */
dot
id|info
op_assign
id|mixart_analog_vol_info
comma
dot
id|get
op_assign
id|mixart_analog_vol_get
comma
dot
id|put
op_assign
id|mixart_analog_vol_put
comma
)brace
suffix:semicolon
multiline_comment|/* shared */
DECL|function|mixart_sw_info
r_static
r_int
id|mixart_sw_info
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
(brace
id|uinfo-&gt;type
op_assign
id|SNDRV_CTL_ELEM_TYPE_BOOLEAN
suffix:semicolon
id|uinfo-&gt;count
op_assign
l_int|2
suffix:semicolon
id|uinfo-&gt;value.integer.min
op_assign
l_int|0
suffix:semicolon
id|uinfo-&gt;value.integer.max
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mixart_audio_sw_get
r_static
r_int
id|mixart_audio_sw_get
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|mixart_t
op_star
id|chip
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
id|chip-&gt;analog_playback_active
(braket
l_int|0
)braket
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|1
)braket
op_assign
id|chip-&gt;analog_playback_active
(braket
l_int|1
)braket
suffix:semicolon
id|up
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mixart_audio_sw_put
r_static
r_int
id|mixart_audio_sw_put
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|mixart_t
op_star
id|chip
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
id|i
comma
id|changed
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|chip-&gt;analog_playback_active
(braket
id|i
)braket
op_ne
id|ucontrol-&gt;value.integer.value
(braket
id|i
)braket
)paren
(brace
id|chip-&gt;analog_playback_active
(braket
id|i
)braket
op_assign
id|ucontrol-&gt;value.integer.value
(braket
id|i
)braket
suffix:semicolon
id|changed
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|changed
)paren
(brace
id|mixart_update_analog_audio_level
c_func
(paren
id|chip
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* update playback levels */
id|up
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
r_return
id|changed
suffix:semicolon
)brace
DECL|variable|mixart_control_output_switch
r_static
id|snd_kcontrol_new_t
id|mixart_control_output_switch
op_assign
(brace
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
dot
id|name
op_assign
l_string|&quot;Master Playback Switch&quot;
comma
dot
id|info
op_assign
id|mixart_sw_info
comma
multiline_comment|/* shared */
dot
id|get
op_assign
id|mixart_audio_sw_get
comma
dot
id|put
op_assign
id|mixart_audio_sw_put
)brace
suffix:semicolon
DECL|variable|mixart_digital_level
r_static
id|u32
id|mixart_digital_level
(braket
l_int|256
)braket
op_assign
(brace
l_int|0x00000000
comma
multiline_comment|/* [000] = 0.00e+000 = mute if &lt;= -109.5dB */
l_int|0x366e1c7a
comma
multiline_comment|/* [001] = 3.55e-006 = pow(10.0, 0.05 * -109.0dB) */
l_int|0x367c3860
comma
multiline_comment|/* [002] = 3.76e-006 = pow(10.0, 0.05 * -108.5dB) */
l_int|0x36859525
comma
multiline_comment|/* [003] = 3.98e-006 = pow(10.0, 0.05 * -108.0dB) */
l_int|0x368d7f74
comma
multiline_comment|/* [004] = 4.22e-006 = pow(10.0, 0.05 * -107.5dB) */
l_int|0x3695e1d4
comma
multiline_comment|/* [005] = 4.47e-006 = pow(10.0, 0.05 * -107.0dB) */
l_int|0x369ec362
comma
multiline_comment|/* [006] = 4.73e-006 = pow(10.0, 0.05 * -106.5dB) */
l_int|0x36a82ba8
comma
multiline_comment|/* [007] = 5.01e-006 = pow(10.0, 0.05 * -106.0dB) */
l_int|0x36b222a0
comma
multiline_comment|/* [008] = 5.31e-006 = pow(10.0, 0.05 * -105.5dB) */
l_int|0x36bcb0c1
comma
multiline_comment|/* [009] = 5.62e-006 = pow(10.0, 0.05 * -105.0dB) */
l_int|0x36c7defd
comma
multiline_comment|/* [010] = 5.96e-006 = pow(10.0, 0.05 * -104.5dB) */
l_int|0x36d3b6d3
comma
multiline_comment|/* [011] = 6.31e-006 = pow(10.0, 0.05 * -104.0dB) */
l_int|0x36e0424e
comma
multiline_comment|/* [012] = 6.68e-006 = pow(10.0, 0.05 * -103.5dB) */
l_int|0x36ed8c14
comma
multiline_comment|/* [013] = 7.08e-006 = pow(10.0, 0.05 * -103.0dB) */
l_int|0x36fb9f6c
comma
multiline_comment|/* [014] = 7.50e-006 = pow(10.0, 0.05 * -102.5dB) */
l_int|0x37054423
comma
multiline_comment|/* [015] = 7.94e-006 = pow(10.0, 0.05 * -102.0dB) */
l_int|0x370d29a5
comma
multiline_comment|/* [016] = 8.41e-006 = pow(10.0, 0.05 * -101.5dB) */
l_int|0x371586f0
comma
multiline_comment|/* [017] = 8.91e-006 = pow(10.0, 0.05 * -101.0dB) */
l_int|0x371e631b
comma
multiline_comment|/* [018] = 9.44e-006 = pow(10.0, 0.05 * -100.5dB) */
l_int|0x3727c5ac
comma
multiline_comment|/* [019] = 1.00e-005 = pow(10.0, 0.05 * -100.0dB) */
l_int|0x3731b69a
comma
multiline_comment|/* [020] = 1.06e-005 = pow(10.0, 0.05 * -99.5dB) */
l_int|0x373c3e53
comma
multiline_comment|/* [021] = 1.12e-005 = pow(10.0, 0.05 * -99.0dB) */
l_int|0x374765c8
comma
multiline_comment|/* [022] = 1.19e-005 = pow(10.0, 0.05 * -98.5dB) */
l_int|0x3753366f
comma
multiline_comment|/* [023] = 1.26e-005 = pow(10.0, 0.05 * -98.0dB) */
l_int|0x375fba4f
comma
multiline_comment|/* [024] = 1.33e-005 = pow(10.0, 0.05 * -97.5dB) */
l_int|0x376cfc07
comma
multiline_comment|/* [025] = 1.41e-005 = pow(10.0, 0.05 * -97.0dB) */
l_int|0x377b06d5
comma
multiline_comment|/* [026] = 1.50e-005 = pow(10.0, 0.05 * -96.5dB) */
l_int|0x3784f352
comma
multiline_comment|/* [027] = 1.58e-005 = pow(10.0, 0.05 * -96.0dB) */
l_int|0x378cd40b
comma
multiline_comment|/* [028] = 1.68e-005 = pow(10.0, 0.05 * -95.5dB) */
l_int|0x37952c42
comma
multiline_comment|/* [029] = 1.78e-005 = pow(10.0, 0.05 * -95.0dB) */
l_int|0x379e030e
comma
multiline_comment|/* [030] = 1.88e-005 = pow(10.0, 0.05 * -94.5dB) */
l_int|0x37a75fef
comma
multiline_comment|/* [031] = 2.00e-005 = pow(10.0, 0.05 * -94.0dB) */
l_int|0x37b14ad5
comma
multiline_comment|/* [032] = 2.11e-005 = pow(10.0, 0.05 * -93.5dB) */
l_int|0x37bbcc2c
comma
multiline_comment|/* [033] = 2.24e-005 = pow(10.0, 0.05 * -93.0dB) */
l_int|0x37c6ecdd
comma
multiline_comment|/* [034] = 2.37e-005 = pow(10.0, 0.05 * -92.5dB) */
l_int|0x37d2b65a
comma
multiline_comment|/* [035] = 2.51e-005 = pow(10.0, 0.05 * -92.0dB) */
l_int|0x37df32a3
comma
multiline_comment|/* [036] = 2.66e-005 = pow(10.0, 0.05 * -91.5dB) */
l_int|0x37ec6c50
comma
multiline_comment|/* [037] = 2.82e-005 = pow(10.0, 0.05 * -91.0dB) */
l_int|0x37fa6e9b
comma
multiline_comment|/* [038] = 2.99e-005 = pow(10.0, 0.05 * -90.5dB) */
l_int|0x3804a2b3
comma
multiline_comment|/* [039] = 3.16e-005 = pow(10.0, 0.05 * -90.0dB) */
l_int|0x380c7ea4
comma
multiline_comment|/* [040] = 3.35e-005 = pow(10.0, 0.05 * -89.5dB) */
l_int|0x3814d1cc
comma
multiline_comment|/* [041] = 3.55e-005 = pow(10.0, 0.05 * -89.0dB) */
l_int|0x381da33c
comma
multiline_comment|/* [042] = 3.76e-005 = pow(10.0, 0.05 * -88.5dB) */
l_int|0x3826fa6f
comma
multiline_comment|/* [043] = 3.98e-005 = pow(10.0, 0.05 * -88.0dB) */
l_int|0x3830df51
comma
multiline_comment|/* [044] = 4.22e-005 = pow(10.0, 0.05 * -87.5dB) */
l_int|0x383b5a49
comma
multiline_comment|/* [045] = 4.47e-005 = pow(10.0, 0.05 * -87.0dB) */
l_int|0x3846743b
comma
multiline_comment|/* [046] = 4.73e-005 = pow(10.0, 0.05 * -86.5dB) */
l_int|0x38523692
comma
multiline_comment|/* [047] = 5.01e-005 = pow(10.0, 0.05 * -86.0dB) */
l_int|0x385eab48
comma
multiline_comment|/* [048] = 5.31e-005 = pow(10.0, 0.05 * -85.5dB) */
l_int|0x386bdcf1
comma
multiline_comment|/* [049] = 5.62e-005 = pow(10.0, 0.05 * -85.0dB) */
l_int|0x3879d6bc
comma
multiline_comment|/* [050] = 5.96e-005 = pow(10.0, 0.05 * -84.5dB) */
l_int|0x38845244
comma
multiline_comment|/* [051] = 6.31e-005 = pow(10.0, 0.05 * -84.0dB) */
l_int|0x388c2971
comma
multiline_comment|/* [052] = 6.68e-005 = pow(10.0, 0.05 * -83.5dB) */
l_int|0x3894778d
comma
multiline_comment|/* [053] = 7.08e-005 = pow(10.0, 0.05 * -83.0dB) */
l_int|0x389d43a4
comma
multiline_comment|/* [054] = 7.50e-005 = pow(10.0, 0.05 * -82.5dB) */
l_int|0x38a6952c
comma
multiline_comment|/* [055] = 7.94e-005 = pow(10.0, 0.05 * -82.0dB) */
l_int|0x38b0740f
comma
multiline_comment|/* [056] = 8.41e-005 = pow(10.0, 0.05 * -81.5dB) */
l_int|0x38bae8ac
comma
multiline_comment|/* [057] = 8.91e-005 = pow(10.0, 0.05 * -81.0dB) */
l_int|0x38c5fbe2
comma
multiline_comment|/* [058] = 9.44e-005 = pow(10.0, 0.05 * -80.5dB) */
l_int|0x38d1b717
comma
multiline_comment|/* [059] = 1.00e-004 = pow(10.0, 0.05 * -80.0dB) */
l_int|0x38de2440
comma
multiline_comment|/* [060] = 1.06e-004 = pow(10.0, 0.05 * -79.5dB) */
l_int|0x38eb4de8
comma
multiline_comment|/* [061] = 1.12e-004 = pow(10.0, 0.05 * -79.0dB) */
l_int|0x38f93f3a
comma
multiline_comment|/* [062] = 1.19e-004 = pow(10.0, 0.05 * -78.5dB) */
l_int|0x39040206
comma
multiline_comment|/* [063] = 1.26e-004 = pow(10.0, 0.05 * -78.0dB) */
l_int|0x390bd472
comma
multiline_comment|/* [064] = 1.33e-004 = pow(10.0, 0.05 * -77.5dB) */
l_int|0x39141d84
comma
multiline_comment|/* [065] = 1.41e-004 = pow(10.0, 0.05 * -77.0dB) */
l_int|0x391ce445
comma
multiline_comment|/* [066] = 1.50e-004 = pow(10.0, 0.05 * -76.5dB) */
l_int|0x39263027
comma
multiline_comment|/* [067] = 1.58e-004 = pow(10.0, 0.05 * -76.0dB) */
l_int|0x3930090d
comma
multiline_comment|/* [068] = 1.68e-004 = pow(10.0, 0.05 * -75.5dB) */
l_int|0x393a7753
comma
multiline_comment|/* [069] = 1.78e-004 = pow(10.0, 0.05 * -75.0dB) */
l_int|0x394583d2
comma
multiline_comment|/* [070] = 1.88e-004 = pow(10.0, 0.05 * -74.5dB) */
l_int|0x395137ea
comma
multiline_comment|/* [071] = 2.00e-004 = pow(10.0, 0.05 * -74.0dB) */
l_int|0x395d9d8a
comma
multiline_comment|/* [072] = 2.11e-004 = pow(10.0, 0.05 * -73.5dB) */
l_int|0x396abf37
comma
multiline_comment|/* [073] = 2.24e-004 = pow(10.0, 0.05 * -73.0dB) */
l_int|0x3978a814
comma
multiline_comment|/* [074] = 2.37e-004 = pow(10.0, 0.05 * -72.5dB) */
l_int|0x3983b1f8
comma
multiline_comment|/* [075] = 2.51e-004 = pow(10.0, 0.05 * -72.0dB) */
l_int|0x398b7fa6
comma
multiline_comment|/* [076] = 2.66e-004 = pow(10.0, 0.05 * -71.5dB) */
l_int|0x3993c3b2
comma
multiline_comment|/* [077] = 2.82e-004 = pow(10.0, 0.05 * -71.0dB) */
l_int|0x399c8521
comma
multiline_comment|/* [078] = 2.99e-004 = pow(10.0, 0.05 * -70.5dB) */
l_int|0x39a5cb5f
comma
multiline_comment|/* [079] = 3.16e-004 = pow(10.0, 0.05 * -70.0dB) */
l_int|0x39af9e4d
comma
multiline_comment|/* [080] = 3.35e-004 = pow(10.0, 0.05 * -69.5dB) */
l_int|0x39ba063f
comma
multiline_comment|/* [081] = 3.55e-004 = pow(10.0, 0.05 * -69.0dB) */
l_int|0x39c50c0b
comma
multiline_comment|/* [082] = 3.76e-004 = pow(10.0, 0.05 * -68.5dB) */
l_int|0x39d0b90a
comma
multiline_comment|/* [083] = 3.98e-004 = pow(10.0, 0.05 * -68.0dB) */
l_int|0x39dd1726
comma
multiline_comment|/* [084] = 4.22e-004 = pow(10.0, 0.05 * -67.5dB) */
l_int|0x39ea30db
comma
multiline_comment|/* [085] = 4.47e-004 = pow(10.0, 0.05 * -67.0dB) */
l_int|0x39f81149
comma
multiline_comment|/* [086] = 4.73e-004 = pow(10.0, 0.05 * -66.5dB) */
l_int|0x3a03621b
comma
multiline_comment|/* [087] = 5.01e-004 = pow(10.0, 0.05 * -66.0dB) */
l_int|0x3a0b2b0d
comma
multiline_comment|/* [088] = 5.31e-004 = pow(10.0, 0.05 * -65.5dB) */
l_int|0x3a136a16
comma
multiline_comment|/* [089] = 5.62e-004 = pow(10.0, 0.05 * -65.0dB) */
l_int|0x3a1c2636
comma
multiline_comment|/* [090] = 5.96e-004 = pow(10.0, 0.05 * -64.5dB) */
l_int|0x3a2566d5
comma
multiline_comment|/* [091] = 6.31e-004 = pow(10.0, 0.05 * -64.0dB) */
l_int|0x3a2f33cd
comma
multiline_comment|/* [092] = 6.68e-004 = pow(10.0, 0.05 * -63.5dB) */
l_int|0x3a399570
comma
multiline_comment|/* [093] = 7.08e-004 = pow(10.0, 0.05 * -63.0dB) */
l_int|0x3a44948c
comma
multiline_comment|/* [094] = 7.50e-004 = pow(10.0, 0.05 * -62.5dB) */
l_int|0x3a503a77
comma
multiline_comment|/* [095] = 7.94e-004 = pow(10.0, 0.05 * -62.0dB) */
l_int|0x3a5c9112
comma
multiline_comment|/* [096] = 8.41e-004 = pow(10.0, 0.05 * -61.5dB) */
l_int|0x3a69a2d7
comma
multiline_comment|/* [097] = 8.91e-004 = pow(10.0, 0.05 * -61.0dB) */
l_int|0x3a777ada
comma
multiline_comment|/* [098] = 9.44e-004 = pow(10.0, 0.05 * -60.5dB) */
l_int|0x3a83126f
comma
multiline_comment|/* [099] = 1.00e-003 = pow(10.0, 0.05 * -60.0dB) */
l_int|0x3a8ad6a8
comma
multiline_comment|/* [100] = 1.06e-003 = pow(10.0, 0.05 * -59.5dB) */
l_int|0x3a9310b1
comma
multiline_comment|/* [101] = 1.12e-003 = pow(10.0, 0.05 * -59.0dB) */
l_int|0x3a9bc784
comma
multiline_comment|/* [102] = 1.19e-003 = pow(10.0, 0.05 * -58.5dB) */
l_int|0x3aa50287
comma
multiline_comment|/* [103] = 1.26e-003 = pow(10.0, 0.05 * -58.0dB) */
l_int|0x3aaec98e
comma
multiline_comment|/* [104] = 1.33e-003 = pow(10.0, 0.05 * -57.5dB) */
l_int|0x3ab924e5
comma
multiline_comment|/* [105] = 1.41e-003 = pow(10.0, 0.05 * -57.0dB) */
l_int|0x3ac41d56
comma
multiline_comment|/* [106] = 1.50e-003 = pow(10.0, 0.05 * -56.5dB) */
l_int|0x3acfbc31
comma
multiline_comment|/* [107] = 1.58e-003 = pow(10.0, 0.05 * -56.0dB) */
l_int|0x3adc0b51
comma
multiline_comment|/* [108] = 1.68e-003 = pow(10.0, 0.05 * -55.5dB) */
l_int|0x3ae91528
comma
multiline_comment|/* [109] = 1.78e-003 = pow(10.0, 0.05 * -55.0dB) */
l_int|0x3af6e4c6
comma
multiline_comment|/* [110] = 1.88e-003 = pow(10.0, 0.05 * -54.5dB) */
l_int|0x3b02c2f2
comma
multiline_comment|/* [111] = 2.00e-003 = pow(10.0, 0.05 * -54.0dB) */
l_int|0x3b0a8276
comma
multiline_comment|/* [112] = 2.11e-003 = pow(10.0, 0.05 * -53.5dB) */
l_int|0x3b12b782
comma
multiline_comment|/* [113] = 2.24e-003 = pow(10.0, 0.05 * -53.0dB) */
l_int|0x3b1b690d
comma
multiline_comment|/* [114] = 2.37e-003 = pow(10.0, 0.05 * -52.5dB) */
l_int|0x3b249e76
comma
multiline_comment|/* [115] = 2.51e-003 = pow(10.0, 0.05 * -52.0dB) */
l_int|0x3b2e5f8f
comma
multiline_comment|/* [116] = 2.66e-003 = pow(10.0, 0.05 * -51.5dB) */
l_int|0x3b38b49f
comma
multiline_comment|/* [117] = 2.82e-003 = pow(10.0, 0.05 * -51.0dB) */
l_int|0x3b43a669
comma
multiline_comment|/* [118] = 2.99e-003 = pow(10.0, 0.05 * -50.5dB) */
l_int|0x3b4f3e37
comma
multiline_comment|/* [119] = 3.16e-003 = pow(10.0, 0.05 * -50.0dB) */
l_int|0x3b5b85e0
comma
multiline_comment|/* [120] = 3.35e-003 = pow(10.0, 0.05 * -49.5dB) */
l_int|0x3b6887cf
comma
multiline_comment|/* [121] = 3.55e-003 = pow(10.0, 0.05 * -49.0dB) */
l_int|0x3b764f0e
comma
multiline_comment|/* [122] = 3.76e-003 = pow(10.0, 0.05 * -48.5dB) */
l_int|0x3b8273a6
comma
multiline_comment|/* [123] = 3.98e-003 = pow(10.0, 0.05 * -48.0dB) */
l_int|0x3b8a2e77
comma
multiline_comment|/* [124] = 4.22e-003 = pow(10.0, 0.05 * -47.5dB) */
l_int|0x3b925e89
comma
multiline_comment|/* [125] = 4.47e-003 = pow(10.0, 0.05 * -47.0dB) */
l_int|0x3b9b0ace
comma
multiline_comment|/* [126] = 4.73e-003 = pow(10.0, 0.05 * -46.5dB) */
l_int|0x3ba43aa2
comma
multiline_comment|/* [127] = 5.01e-003 = pow(10.0, 0.05 * -46.0dB) */
l_int|0x3badf5d1
comma
multiline_comment|/* [128] = 5.31e-003 = pow(10.0, 0.05 * -45.5dB) */
l_int|0x3bb8449c
comma
multiline_comment|/* [129] = 5.62e-003 = pow(10.0, 0.05 * -45.0dB) */
l_int|0x3bc32fc3
comma
multiline_comment|/* [130] = 5.96e-003 = pow(10.0, 0.05 * -44.5dB) */
l_int|0x3bcec08a
comma
multiline_comment|/* [131] = 6.31e-003 = pow(10.0, 0.05 * -44.0dB) */
l_int|0x3bdb00c0
comma
multiline_comment|/* [132] = 6.68e-003 = pow(10.0, 0.05 * -43.5dB) */
l_int|0x3be7facc
comma
multiline_comment|/* [133] = 7.08e-003 = pow(10.0, 0.05 * -43.0dB) */
l_int|0x3bf5b9b0
comma
multiline_comment|/* [134] = 7.50e-003 = pow(10.0, 0.05 * -42.5dB) */
l_int|0x3c02248a
comma
multiline_comment|/* [135] = 7.94e-003 = pow(10.0, 0.05 * -42.0dB) */
l_int|0x3c09daac
comma
multiline_comment|/* [136] = 8.41e-003 = pow(10.0, 0.05 * -41.5dB) */
l_int|0x3c1205c6
comma
multiline_comment|/* [137] = 8.91e-003 = pow(10.0, 0.05 * -41.0dB) */
l_int|0x3c1aacc8
comma
multiline_comment|/* [138] = 9.44e-003 = pow(10.0, 0.05 * -40.5dB) */
l_int|0x3c23d70a
comma
multiline_comment|/* [139] = 1.00e-002 = pow(10.0, 0.05 * -40.0dB) */
l_int|0x3c2d8c52
comma
multiline_comment|/* [140] = 1.06e-002 = pow(10.0, 0.05 * -39.5dB) */
l_int|0x3c37d4dd
comma
multiline_comment|/* [141] = 1.12e-002 = pow(10.0, 0.05 * -39.0dB) */
l_int|0x3c42b965
comma
multiline_comment|/* [142] = 1.19e-002 = pow(10.0, 0.05 * -38.5dB) */
l_int|0x3c4e4329
comma
multiline_comment|/* [143] = 1.26e-002 = pow(10.0, 0.05 * -38.0dB) */
l_int|0x3c5a7bf1
comma
multiline_comment|/* [144] = 1.33e-002 = pow(10.0, 0.05 * -37.5dB) */
l_int|0x3c676e1e
comma
multiline_comment|/* [145] = 1.41e-002 = pow(10.0, 0.05 * -37.0dB) */
l_int|0x3c7524ac
comma
multiline_comment|/* [146] = 1.50e-002 = pow(10.0, 0.05 * -36.5dB) */
l_int|0x3c81d59f
comma
multiline_comment|/* [147] = 1.58e-002 = pow(10.0, 0.05 * -36.0dB) */
l_int|0x3c898712
comma
multiline_comment|/* [148] = 1.68e-002 = pow(10.0, 0.05 * -35.5dB) */
l_int|0x3c91ad39
comma
multiline_comment|/* [149] = 1.78e-002 = pow(10.0, 0.05 * -35.0dB) */
l_int|0x3c9a4efc
comma
multiline_comment|/* [150] = 1.88e-002 = pow(10.0, 0.05 * -34.5dB) */
l_int|0x3ca373af
comma
multiline_comment|/* [151] = 2.00e-002 = pow(10.0, 0.05 * -34.0dB) */
l_int|0x3cad2314
comma
multiline_comment|/* [152] = 2.11e-002 = pow(10.0, 0.05 * -33.5dB) */
l_int|0x3cb76563
comma
multiline_comment|/* [153] = 2.24e-002 = pow(10.0, 0.05 * -33.0dB) */
l_int|0x3cc24350
comma
multiline_comment|/* [154] = 2.37e-002 = pow(10.0, 0.05 * -32.5dB) */
l_int|0x3ccdc614
comma
multiline_comment|/* [155] = 2.51e-002 = pow(10.0, 0.05 * -32.0dB) */
l_int|0x3cd9f773
comma
multiline_comment|/* [156] = 2.66e-002 = pow(10.0, 0.05 * -31.5dB) */
l_int|0x3ce6e1c6
comma
multiline_comment|/* [157] = 2.82e-002 = pow(10.0, 0.05 * -31.0dB) */
l_int|0x3cf49003
comma
multiline_comment|/* [158] = 2.99e-002 = pow(10.0, 0.05 * -30.5dB) */
l_int|0x3d0186e2
comma
multiline_comment|/* [159] = 3.16e-002 = pow(10.0, 0.05 * -30.0dB) */
l_int|0x3d0933ac
comma
multiline_comment|/* [160] = 3.35e-002 = pow(10.0, 0.05 * -29.5dB) */
l_int|0x3d1154e1
comma
multiline_comment|/* [161] = 3.55e-002 = pow(10.0, 0.05 * -29.0dB) */
l_int|0x3d19f169
comma
multiline_comment|/* [162] = 3.76e-002 = pow(10.0, 0.05 * -28.5dB) */
l_int|0x3d231090
comma
multiline_comment|/* [163] = 3.98e-002 = pow(10.0, 0.05 * -28.0dB) */
l_int|0x3d2cba15
comma
multiline_comment|/* [164] = 4.22e-002 = pow(10.0, 0.05 * -27.5dB) */
l_int|0x3d36f62b
comma
multiline_comment|/* [165] = 4.47e-002 = pow(10.0, 0.05 * -27.0dB) */
l_int|0x3d41cd81
comma
multiline_comment|/* [166] = 4.73e-002 = pow(10.0, 0.05 * -26.5dB) */
l_int|0x3d4d494a
comma
multiline_comment|/* [167] = 5.01e-002 = pow(10.0, 0.05 * -26.0dB) */
l_int|0x3d597345
comma
multiline_comment|/* [168] = 5.31e-002 = pow(10.0, 0.05 * -25.5dB) */
l_int|0x3d6655c3
comma
multiline_comment|/* [169] = 5.62e-002 = pow(10.0, 0.05 * -25.0dB) */
l_int|0x3d73fbb4
comma
multiline_comment|/* [170] = 5.96e-002 = pow(10.0, 0.05 * -24.5dB) */
l_int|0x3d813856
comma
multiline_comment|/* [171] = 6.31e-002 = pow(10.0, 0.05 * -24.0dB) */
l_int|0x3d88e078
comma
multiline_comment|/* [172] = 6.68e-002 = pow(10.0, 0.05 * -23.5dB) */
l_int|0x3d90fcbf
comma
multiline_comment|/* [173] = 7.08e-002 = pow(10.0, 0.05 * -23.0dB) */
l_int|0x3d99940e
comma
multiline_comment|/* [174] = 7.50e-002 = pow(10.0, 0.05 * -22.5dB) */
l_int|0x3da2adad
comma
multiline_comment|/* [175] = 7.94e-002 = pow(10.0, 0.05 * -22.0dB) */
l_int|0x3dac5156
comma
multiline_comment|/* [176] = 8.41e-002 = pow(10.0, 0.05 * -21.5dB) */
l_int|0x3db68738
comma
multiline_comment|/* [177] = 8.91e-002 = pow(10.0, 0.05 * -21.0dB) */
l_int|0x3dc157fb
comma
multiline_comment|/* [178] = 9.44e-002 = pow(10.0, 0.05 * -20.5dB) */
l_int|0x3dcccccd
comma
multiline_comment|/* [179] = 1.00e-001 = pow(10.0, 0.05 * -20.0dB) */
l_int|0x3dd8ef67
comma
multiline_comment|/* [180] = 1.06e-001 = pow(10.0, 0.05 * -19.5dB) */
l_int|0x3de5ca15
comma
multiline_comment|/* [181] = 1.12e-001 = pow(10.0, 0.05 * -19.0dB) */
l_int|0x3df367bf
comma
multiline_comment|/* [182] = 1.19e-001 = pow(10.0, 0.05 * -18.5dB) */
l_int|0x3e00e9f9
comma
multiline_comment|/* [183] = 1.26e-001 = pow(10.0, 0.05 * -18.0dB) */
l_int|0x3e088d77
comma
multiline_comment|/* [184] = 1.33e-001 = pow(10.0, 0.05 * -17.5dB) */
l_int|0x3e10a4d3
comma
multiline_comment|/* [185] = 1.41e-001 = pow(10.0, 0.05 * -17.0dB) */
l_int|0x3e1936ec
comma
multiline_comment|/* [186] = 1.50e-001 = pow(10.0, 0.05 * -16.5dB) */
l_int|0x3e224b06
comma
multiline_comment|/* [187] = 1.58e-001 = pow(10.0, 0.05 * -16.0dB) */
l_int|0x3e2be8d7
comma
multiline_comment|/* [188] = 1.68e-001 = pow(10.0, 0.05 * -15.5dB) */
l_int|0x3e361887
comma
multiline_comment|/* [189] = 1.78e-001 = pow(10.0, 0.05 * -15.0dB) */
l_int|0x3e40e2bb
comma
multiline_comment|/* [190] = 1.88e-001 = pow(10.0, 0.05 * -14.5dB) */
l_int|0x3e4c509b
comma
multiline_comment|/* [191] = 2.00e-001 = pow(10.0, 0.05 * -14.0dB) */
l_int|0x3e586bd9
comma
multiline_comment|/* [192] = 2.11e-001 = pow(10.0, 0.05 * -13.5dB) */
l_int|0x3e653ebb
comma
multiline_comment|/* [193] = 2.24e-001 = pow(10.0, 0.05 * -13.0dB) */
l_int|0x3e72d424
comma
multiline_comment|/* [194] = 2.37e-001 = pow(10.0, 0.05 * -12.5dB) */
l_int|0x3e809bcc
comma
multiline_comment|/* [195] = 2.51e-001 = pow(10.0, 0.05 * -12.0dB) */
l_int|0x3e883aa8
comma
multiline_comment|/* [196] = 2.66e-001 = pow(10.0, 0.05 * -11.5dB) */
l_int|0x3e904d1c
comma
multiline_comment|/* [197] = 2.82e-001 = pow(10.0, 0.05 * -11.0dB) */
l_int|0x3e98da02
comma
multiline_comment|/* [198] = 2.99e-001 = pow(10.0, 0.05 * -10.5dB) */
l_int|0x3ea1e89b
comma
multiline_comment|/* [199] = 3.16e-001 = pow(10.0, 0.05 * -10.0dB) */
l_int|0x3eab8097
comma
multiline_comment|/* [200] = 3.35e-001 = pow(10.0, 0.05 * -9.5dB) */
l_int|0x3eb5aa1a
comma
multiline_comment|/* [201] = 3.55e-001 = pow(10.0, 0.05 * -9.0dB) */
l_int|0x3ec06dc3
comma
multiline_comment|/* [202] = 3.76e-001 = pow(10.0, 0.05 * -8.5dB) */
l_int|0x3ecbd4b4
comma
multiline_comment|/* [203] = 3.98e-001 = pow(10.0, 0.05 * -8.0dB) */
l_int|0x3ed7e89b
comma
multiline_comment|/* [204] = 4.22e-001 = pow(10.0, 0.05 * -7.5dB) */
l_int|0x3ee4b3b6
comma
multiline_comment|/* [205] = 4.47e-001 = pow(10.0, 0.05 * -7.0dB) */
l_int|0x3ef240e2
comma
multiline_comment|/* [206] = 4.73e-001 = pow(10.0, 0.05 * -6.5dB) */
l_int|0x3f004dce
comma
multiline_comment|/* [207] = 5.01e-001 = pow(10.0, 0.05 * -6.0dB) */
l_int|0x3f07e80b
comma
multiline_comment|/* [208] = 5.31e-001 = pow(10.0, 0.05 * -5.5dB) */
l_int|0x3f0ff59a
comma
multiline_comment|/* [209] = 5.62e-001 = pow(10.0, 0.05 * -5.0dB) */
l_int|0x3f187d50
comma
multiline_comment|/* [210] = 5.96e-001 = pow(10.0, 0.05 * -4.5dB) */
l_int|0x3f21866c
comma
multiline_comment|/* [211] = 6.31e-001 = pow(10.0, 0.05 * -4.0dB) */
l_int|0x3f2b1896
comma
multiline_comment|/* [212] = 6.68e-001 = pow(10.0, 0.05 * -3.5dB) */
l_int|0x3f353bef
comma
multiline_comment|/* [213] = 7.08e-001 = pow(10.0, 0.05 * -3.0dB) */
l_int|0x3f3ff911
comma
multiline_comment|/* [214] = 7.50e-001 = pow(10.0, 0.05 * -2.5dB) */
l_int|0x3f4b5918
comma
multiline_comment|/* [215] = 7.94e-001 = pow(10.0, 0.05 * -2.0dB) */
l_int|0x3f5765ac
comma
multiline_comment|/* [216] = 8.41e-001 = pow(10.0, 0.05 * -1.5dB) */
l_int|0x3f642905
comma
multiline_comment|/* [217] = 8.91e-001 = pow(10.0, 0.05 * -1.0dB) */
l_int|0x3f71adf9
comma
multiline_comment|/* [218] = 9.44e-001 = pow(10.0, 0.05 * -0.5dB) */
l_int|0x3f800000
comma
multiline_comment|/* [219] = 1.00e+000 = pow(10.0, 0.05 * 0.0dB) */
l_int|0x3f8795a0
comma
multiline_comment|/* [220] = 1.06e+000 = pow(10.0, 0.05 * 0.5dB) */
l_int|0x3f8f9e4d
comma
multiline_comment|/* [221] = 1.12e+000 = pow(10.0, 0.05 * 1.0dB) */
l_int|0x3f9820d7
comma
multiline_comment|/* [222] = 1.19e+000 = pow(10.0, 0.05 * 1.5dB) */
l_int|0x3fa12478
comma
multiline_comment|/* [223] = 1.26e+000 = pow(10.0, 0.05 * 2.0dB) */
l_int|0x3faab0d5
comma
multiline_comment|/* [224] = 1.33e+000 = pow(10.0, 0.05 * 2.5dB) */
l_int|0x3fb4ce08
comma
multiline_comment|/* [225] = 1.41e+000 = pow(10.0, 0.05 * 3.0dB) */
l_int|0x3fbf84a6
comma
multiline_comment|/* [226] = 1.50e+000 = pow(10.0, 0.05 * 3.5dB) */
l_int|0x3fcaddc8
comma
multiline_comment|/* [227] = 1.58e+000 = pow(10.0, 0.05 * 4.0dB) */
l_int|0x3fd6e30d
comma
multiline_comment|/* [228] = 1.68e+000 = pow(10.0, 0.05 * 4.5dB) */
l_int|0x3fe39ea9
comma
multiline_comment|/* [229] = 1.78e+000 = pow(10.0, 0.05 * 5.0dB) */
l_int|0x3ff11b6a
comma
multiline_comment|/* [230] = 1.88e+000 = pow(10.0, 0.05 * 5.5dB) */
l_int|0x3fff64c1
comma
multiline_comment|/* [231] = 2.00e+000 = pow(10.0, 0.05 * 6.0dB) */
l_int|0x40074368
comma
multiline_comment|/* [232] = 2.11e+000 = pow(10.0, 0.05 * 6.5dB) */
l_int|0x400f4735
comma
multiline_comment|/* [233] = 2.24e+000 = pow(10.0, 0.05 * 7.0dB) */
l_int|0x4017c496
comma
multiline_comment|/* [234] = 2.37e+000 = pow(10.0, 0.05 * 7.5dB) */
l_int|0x4020c2bf
comma
multiline_comment|/* [235] = 2.51e+000 = pow(10.0, 0.05 * 8.0dB) */
l_int|0x402a4952
comma
multiline_comment|/* [236] = 2.66e+000 = pow(10.0, 0.05 * 8.5dB) */
l_int|0x40346063
comma
multiline_comment|/* [237] = 2.82e+000 = pow(10.0, 0.05 * 9.0dB) */
l_int|0x403f1082
comma
multiline_comment|/* [238] = 2.99e+000 = pow(10.0, 0.05 * 9.5dB) */
l_int|0x404a62c2
comma
multiline_comment|/* [239] = 3.16e+000 = pow(10.0, 0.05 * 10.0dB) */
l_int|0x405660bd
comma
multiline_comment|/* [240] = 3.35e+000 = pow(10.0, 0.05 * 10.5dB) */
l_int|0x406314a0
comma
multiline_comment|/* [241] = 3.55e+000 = pow(10.0, 0.05 * 11.0dB) */
l_int|0x40708933
comma
multiline_comment|/* [242] = 3.76e+000 = pow(10.0, 0.05 * 11.5dB) */
l_int|0x407ec9e1
comma
multiline_comment|/* [243] = 3.98e+000 = pow(10.0, 0.05 * 12.0dB) */
l_int|0x4086f161
comma
multiline_comment|/* [244] = 4.22e+000 = pow(10.0, 0.05 * 12.5dB) */
l_int|0x408ef052
comma
multiline_comment|/* [245] = 4.47e+000 = pow(10.0, 0.05 * 13.0dB) */
l_int|0x4097688d
comma
multiline_comment|/* [246] = 4.73e+000 = pow(10.0, 0.05 * 13.5dB) */
l_int|0x40a06142
comma
multiline_comment|/* [247] = 5.01e+000 = pow(10.0, 0.05 * 14.0dB) */
l_int|0x40a9e20e
comma
multiline_comment|/* [248] = 5.31e+000 = pow(10.0, 0.05 * 14.5dB) */
l_int|0x40b3f300
comma
multiline_comment|/* [249] = 5.62e+000 = pow(10.0, 0.05 * 15.0dB) */
l_int|0x40be9ca5
comma
multiline_comment|/* [250] = 5.96e+000 = pow(10.0, 0.05 * 15.5dB) */
l_int|0x40c9e807
comma
multiline_comment|/* [251] = 6.31e+000 = pow(10.0, 0.05 * 16.0dB) */
l_int|0x40d5debc
comma
multiline_comment|/* [252] = 6.68e+000 = pow(10.0, 0.05 * 16.5dB) */
l_int|0x40e28aeb
comma
multiline_comment|/* [253] = 7.08e+000 = pow(10.0, 0.05 * 17.0dB) */
l_int|0x40eff755
comma
multiline_comment|/* [254] = 7.50e+000 = pow(10.0, 0.05 * 17.5dB) */
l_int|0x40fe2f5e
comma
multiline_comment|/* [255] = 7.94e+000 = pow(10.0, 0.05 * 18.0dB) */
)brace
suffix:semicolon
DECL|macro|MIXART_DIGITAL_LEVEL_MIN
mdefine_line|#define MIXART_DIGITAL_LEVEL_MIN   0      /* -109.5 dB */
DECL|macro|MIXART_DIGITAL_LEVEL_MAX
mdefine_line|#define MIXART_DIGITAL_LEVEL_MAX   255    /*  18.0 dB */
DECL|macro|MIXART_DIGITAL_ZERO_LEVEL
mdefine_line|#define MIXART_DIGITAL_ZERO_LEVEL  219    /*  0.0 dB */
DECL|function|mixart_update_playback_stream_level
r_int
id|mixart_update_playback_stream_level
c_func
(paren
id|mixart_t
op_star
id|chip
comma
r_int
id|is_aes
comma
r_int
id|idx
)paren
(brace
r_int
id|err
comma
id|i
suffix:semicolon
r_int
id|volume
(braket
l_int|2
)braket
suffix:semicolon
id|mixart_msg_t
id|request
suffix:semicolon
id|mixart_set_out_stream_level_req_t
id|set_level
suffix:semicolon
id|u32
id|status
suffix:semicolon
id|mixart_pipe_t
op_star
id|pipe
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|set_level
comma
l_int|0
comma
r_sizeof
(paren
id|set_level
)paren
)paren
suffix:semicolon
id|set_level.nb_of_stream
op_assign
l_int|1
suffix:semicolon
id|set_level.stream_level.desc.stream_idx
op_assign
id|idx
suffix:semicolon
r_if
c_cond
(paren
id|is_aes
)paren
(brace
id|pipe
op_assign
op_amp
id|chip-&gt;pipe_out_dig
suffix:semicolon
multiline_comment|/* AES playback */
id|idx
op_add_assign
id|MIXART_PLAYBACK_STREAMS
suffix:semicolon
)brace
r_else
(brace
id|pipe
op_assign
op_amp
id|chip-&gt;pipe_out_ana
suffix:semicolon
multiline_comment|/* analog playback */
)brace
multiline_comment|/* only when pipe exists ! */
r_if
c_cond
(paren
id|pipe-&gt;status
op_eq
id|PIPE_UNDEFINED
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|set_level.stream_level.desc.uid_pipe
op_assign
id|pipe-&gt;group_uid
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|chip-&gt;digital_playback_active
(braket
id|idx
)braket
(braket
id|i
)braket
)paren
(brace
id|volume
(braket
id|i
)braket
op_assign
id|chip-&gt;digital_playback_volume
(braket
id|idx
)braket
(braket
id|i
)braket
suffix:semicolon
)brace
r_else
id|volume
(braket
id|i
)braket
op_assign
id|MIXART_DIGITAL_LEVEL_MIN
suffix:semicolon
)brace
id|set_level.stream_level.out_level.valid_mask1
op_assign
id|MIXART_OUT_STREAM_SET_LEVEL_LEFT_AUDIO1
op_or
id|MIXART_OUT_STREAM_SET_LEVEL_RIGHT_AUDIO2
suffix:semicolon
id|set_level.stream_level.out_level.left_to_out1_level
op_assign
id|mixart_digital_level
(braket
id|volume
(braket
l_int|0
)braket
)braket
suffix:semicolon
id|set_level.stream_level.out_level.right_to_out2_level
op_assign
id|mixart_digital_level
(braket
id|volume
(braket
l_int|1
)braket
)braket
suffix:semicolon
id|request.message_id
op_assign
id|MSG_STREAM_SET_OUT_STREAM_LEVEL
suffix:semicolon
id|request.uid
op_assign
(paren
id|mixart_uid_t
)paren
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
id|request.data
op_assign
op_amp
id|set_level
suffix:semicolon
id|request.size
op_assign
r_sizeof
(paren
id|set_level
)paren
suffix:semicolon
id|err
op_assign
id|snd_mixart_send_msg
c_func
(paren
id|chip-&gt;mgr
comma
op_amp
id|request
comma
r_sizeof
(paren
id|status
)paren
comma
op_amp
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
OL
l_int|0
)paren
op_logical_or
id|status
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;error MSG_STREAM_SET_OUT_STREAM_LEVEL card(%d) status(%x)&bslash;n&quot;
comma
id|chip-&gt;chip_idx
comma
id|status
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mixart_update_capture_stream_level
r_int
id|mixart_update_capture_stream_level
c_func
(paren
id|mixart_t
op_star
id|chip
comma
r_int
id|is_aes
)paren
(brace
r_int
id|err
comma
id|i
comma
id|idx
suffix:semicolon
id|mixart_pipe_t
op_star
id|pipe
suffix:semicolon
id|mixart_msg_t
id|request
suffix:semicolon
id|mixart_set_in_audio_level_req_t
id|set_level
suffix:semicolon
id|u32
id|status
suffix:semicolon
r_if
c_cond
(paren
id|is_aes
)paren
(brace
id|idx
op_assign
l_int|1
suffix:semicolon
id|pipe
op_assign
op_amp
id|chip-&gt;pipe_in_dig
suffix:semicolon
)brace
r_else
(brace
id|idx
op_assign
l_int|0
suffix:semicolon
id|pipe
op_assign
op_amp
id|chip-&gt;pipe_in_ana
suffix:semicolon
)brace
multiline_comment|/* only when pipe exists ! */
r_if
c_cond
(paren
id|pipe-&gt;status
op_eq
id|PIPE_UNDEFINED
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|set_level
comma
l_int|0
comma
r_sizeof
(paren
id|set_level
)paren
)paren
suffix:semicolon
id|set_level.audio_count
op_assign
l_int|2
suffix:semicolon
id|set_level.level
(braket
l_int|0
)braket
dot
id|connector
op_assign
id|pipe-&gt;uid_left_connector
suffix:semicolon
id|set_level.level
(braket
l_int|1
)braket
dot
id|connector
op_assign
id|pipe-&gt;uid_right_connector
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|set_level.level
(braket
id|i
)braket
dot
id|valid_mask1
op_assign
id|MIXART_AUDIO_LEVEL_DIGITAL_MASK
suffix:semicolon
id|set_level.level
(braket
id|i
)braket
dot
id|digital_level
op_assign
id|mixart_digital_level
(braket
id|chip-&gt;digital_capture_volume
(braket
id|idx
)braket
(braket
id|i
)braket
)braket
suffix:semicolon
)brace
id|request.message_id
op_assign
id|MSG_STREAM_SET_IN_AUDIO_LEVEL
suffix:semicolon
id|request.uid
op_assign
(paren
id|mixart_uid_t
)paren
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
id|request.data
op_assign
op_amp
id|set_level
suffix:semicolon
id|request.size
op_assign
r_sizeof
(paren
id|set_level
)paren
suffix:semicolon
id|err
op_assign
id|snd_mixart_send_msg
c_func
(paren
id|chip-&gt;mgr
comma
op_amp
id|request
comma
r_sizeof
(paren
id|status
)paren
comma
op_amp
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
OL
l_int|0
)paren
op_logical_or
id|status
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;error MSG_STREAM_SET_IN_AUDIO_LEVEL card(%d) status(%x)&bslash;n&quot;
comma
id|chip-&gt;chip_idx
comma
id|status
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* shared */
DECL|function|mixart_digital_vol_info
r_static
r_int
id|mixart_digital_vol_info
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
(brace
id|uinfo-&gt;type
op_assign
id|SNDRV_CTL_ELEM_TYPE_INTEGER
suffix:semicolon
id|uinfo-&gt;count
op_assign
l_int|2
suffix:semicolon
id|uinfo-&gt;value.integer.min
op_assign
id|MIXART_DIGITAL_LEVEL_MIN
suffix:semicolon
multiline_comment|/* -109.5 dB */
id|uinfo-&gt;value.integer.max
op_assign
id|MIXART_DIGITAL_LEVEL_MAX
suffix:semicolon
multiline_comment|/*   18.0 dB */
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|MIXART_VOL_REC_MASK
mdefine_line|#define MIXART_VOL_REC_MASK&t;1
DECL|macro|MIXART_VOL_AES_MASK
mdefine_line|#define MIXART_VOL_AES_MASK&t;2
DECL|function|mixart_pcm_vol_get
r_static
r_int
id|mixart_pcm_vol_get
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|mixart_t
op_star
id|chip
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
id|idx
op_assign
id|snd_ctl_get_ioffidx
c_func
(paren
id|kcontrol
comma
op_amp
id|ucontrol-&gt;id
)paren
suffix:semicolon
multiline_comment|/* index */
r_int
op_star
id|stored_volume
suffix:semicolon
r_int
id|is_capture
op_assign
id|kcontrol-&gt;private_value
op_amp
id|MIXART_VOL_REC_MASK
suffix:semicolon
r_int
id|is_aes
op_assign
id|kcontrol-&gt;private_value
op_amp
id|MIXART_VOL_AES_MASK
suffix:semicolon
id|down
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_capture
)paren
(brace
r_if
c_cond
(paren
id|is_aes
)paren
(brace
id|stored_volume
op_assign
id|chip-&gt;digital_capture_volume
(braket
l_int|1
)braket
suffix:semicolon
)brace
multiline_comment|/* AES capture */
r_else
id|stored_volume
op_assign
id|chip-&gt;digital_capture_volume
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* analog capture */
)brace
r_else
(brace
id|snd_assert
(paren
id|idx
OL
id|MIXART_PLAYBACK_STREAMS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_aes
)paren
(brace
id|stored_volume
op_assign
id|chip-&gt;digital_playback_volume
(braket
id|MIXART_PLAYBACK_STREAMS
op_plus
id|idx
)braket
suffix:semicolon
)brace
multiline_comment|/* AES playback */
r_else
id|stored_volume
op_assign
id|chip-&gt;digital_playback_volume
(braket
id|idx
)braket
suffix:semicolon
multiline_comment|/* analog playback */
)brace
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
id|stored_volume
(braket
l_int|0
)braket
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|1
)braket
op_assign
id|stored_volume
(braket
l_int|1
)braket
suffix:semicolon
id|up
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mixart_pcm_vol_put
r_static
r_int
id|mixart_pcm_vol_put
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|mixart_t
op_star
id|chip
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
id|idx
op_assign
id|snd_ctl_get_ioffidx
c_func
(paren
id|kcontrol
comma
op_amp
id|ucontrol-&gt;id
)paren
suffix:semicolon
multiline_comment|/* index */
r_int
id|changed
op_assign
l_int|0
suffix:semicolon
r_int
id|is_capture
op_assign
id|kcontrol-&gt;private_value
op_amp
id|MIXART_VOL_REC_MASK
suffix:semicolon
r_int
id|is_aes
op_assign
id|kcontrol-&gt;private_value
op_amp
id|MIXART_VOL_AES_MASK
suffix:semicolon
r_int
op_star
id|stored_volume
suffix:semicolon
r_int
id|i
suffix:semicolon
id|down
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_capture
)paren
(brace
r_if
c_cond
(paren
id|is_aes
)paren
(brace
id|stored_volume
op_assign
id|chip-&gt;digital_capture_volume
(braket
l_int|1
)braket
suffix:semicolon
)brace
multiline_comment|/* AES capture */
r_else
id|stored_volume
op_assign
id|chip-&gt;digital_capture_volume
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* analog capture */
)brace
r_else
(brace
id|snd_assert
(paren
id|idx
OL
id|MIXART_PLAYBACK_STREAMS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_aes
)paren
(brace
id|stored_volume
op_assign
id|chip-&gt;digital_playback_volume
(braket
id|MIXART_PLAYBACK_STREAMS
op_plus
id|idx
)braket
suffix:semicolon
)brace
multiline_comment|/* AES playback */
r_else
id|stored_volume
op_assign
id|chip-&gt;digital_playback_volume
(braket
id|idx
)braket
suffix:semicolon
multiline_comment|/* analog playback */
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|stored_volume
(braket
id|i
)braket
op_ne
id|ucontrol-&gt;value.integer.value
(braket
id|i
)braket
)paren
(brace
id|stored_volume
(braket
id|i
)braket
op_assign
id|ucontrol-&gt;value.integer.value
(braket
id|i
)braket
suffix:semicolon
id|changed
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|changed
)paren
(brace
r_if
c_cond
(paren
id|is_capture
)paren
(brace
id|mixart_update_capture_stream_level
c_func
(paren
id|chip
comma
id|is_aes
)paren
suffix:semicolon
)brace
r_else
id|mixart_update_playback_stream_level
c_func
(paren
id|chip
comma
id|is_aes
comma
id|idx
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
r_return
id|changed
suffix:semicolon
)brace
DECL|variable|snd_mixart_pcm_vol
r_static
id|snd_kcontrol_new_t
id|snd_mixart_pcm_vol
op_assign
(brace
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
multiline_comment|/* name will be filled later */
multiline_comment|/* count will be filled later */
dot
id|info
op_assign
id|mixart_digital_vol_info
comma
multiline_comment|/* shared */
dot
id|get
op_assign
id|mixart_pcm_vol_get
comma
dot
id|put
op_assign
id|mixart_pcm_vol_put
comma
)brace
suffix:semicolon
DECL|function|mixart_pcm_sw_get
r_static
r_int
id|mixart_pcm_sw_get
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|mixart_t
op_star
id|chip
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
id|idx
op_assign
id|snd_ctl_get_ioffidx
c_func
(paren
id|kcontrol
comma
op_amp
id|ucontrol-&gt;id
)paren
suffix:semicolon
multiline_comment|/* index */
id|snd_assert
(paren
id|idx
OL
id|MIXART_PLAYBACK_STREAMS
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kcontrol-&gt;private_value
op_amp
id|MIXART_VOL_AES_MASK
)paren
(brace
multiline_comment|/* AES playback */
id|idx
op_add_assign
id|MIXART_PLAYBACK_STREAMS
suffix:semicolon
)brace
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
id|chip-&gt;digital_playback_active
(braket
id|idx
)braket
(braket
l_int|0
)braket
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|1
)braket
op_assign
id|chip-&gt;digital_playback_active
(braket
id|idx
)braket
(braket
l_int|1
)braket
suffix:semicolon
id|up
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mixart_pcm_sw_put
r_static
r_int
id|mixart_pcm_sw_put
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|mixart_t
op_star
id|chip
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
id|changed
op_assign
l_int|0
suffix:semicolon
r_int
id|is_aes
op_assign
id|kcontrol-&gt;private_value
op_amp
id|MIXART_VOL_AES_MASK
suffix:semicolon
r_int
id|idx
op_assign
id|snd_ctl_get_ioffidx
c_func
(paren
id|kcontrol
comma
op_amp
id|ucontrol-&gt;id
)paren
suffix:semicolon
multiline_comment|/* index */
r_int
id|i
comma
id|j
suffix:semicolon
id|snd_assert
(paren
id|idx
OL
id|MIXART_PLAYBACK_STREAMS
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
id|j
op_assign
id|idx
suffix:semicolon
r_if
c_cond
(paren
id|is_aes
)paren
(brace
id|j
op_add_assign
id|MIXART_PLAYBACK_STREAMS
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|chip-&gt;digital_playback_active
(braket
id|j
)braket
(braket
id|i
)braket
op_ne
id|ucontrol-&gt;value.integer.value
(braket
id|i
)braket
)paren
(brace
id|chip-&gt;digital_playback_active
(braket
id|j
)braket
(braket
id|i
)braket
op_assign
id|ucontrol-&gt;value.integer.value
(braket
id|i
)braket
suffix:semicolon
id|changed
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|changed
)paren
(brace
id|mixart_update_playback_stream_level
c_func
(paren
id|chip
comma
id|is_aes
comma
id|idx
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
r_return
id|changed
suffix:semicolon
)brace
DECL|variable|mixart_control_pcm_switch
r_static
id|snd_kcontrol_new_t
id|mixart_control_pcm_switch
op_assign
(brace
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
multiline_comment|/* name will be filled later */
dot
id|count
op_assign
id|MIXART_PLAYBACK_STREAMS
comma
dot
id|info
op_assign
id|mixart_sw_info
comma
multiline_comment|/* shared */
dot
id|get
op_assign
id|mixart_pcm_sw_get
comma
dot
id|put
op_assign
id|mixart_pcm_sw_put
)brace
suffix:semicolon
DECL|function|mixart_update_monitoring
r_static
r_int
id|mixart_update_monitoring
c_func
(paren
id|mixart_t
op_star
id|chip
comma
r_int
id|channel
)paren
(brace
r_int
id|err
suffix:semicolon
id|mixart_msg_t
id|request
suffix:semicolon
id|mixart_set_out_audio_level_t
id|audio_level
suffix:semicolon
id|u32
id|resp
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;pipe_out_ana.status
op_eq
id|PIPE_UNDEFINED
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* no pipe defined */
r_if
c_cond
(paren
op_logical_neg
id|channel
)paren
(brace
id|request.uid
op_assign
id|chip-&gt;pipe_out_ana.uid_left_connector
suffix:semicolon
)brace
r_else
id|request.uid
op_assign
id|chip-&gt;pipe_out_ana.uid_right_connector
suffix:semicolon
id|request.message_id
op_assign
id|MSG_CONNECTOR_SET_OUT_AUDIO_LEVEL
suffix:semicolon
id|request.data
op_assign
op_amp
id|audio_level
suffix:semicolon
id|request.size
op_assign
r_sizeof
(paren
id|audio_level
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|audio_level
comma
l_int|0
comma
r_sizeof
(paren
id|audio_level
)paren
)paren
suffix:semicolon
id|audio_level.valid_mask1
op_assign
id|MIXART_AUDIO_LEVEL_MONITOR_MASK
op_or
id|MIXART_AUDIO_LEVEL_MUTE_M1_MASK
suffix:semicolon
id|audio_level.monitor_level
op_assign
id|mixart_digital_level
(braket
id|chip-&gt;monitoring_volume
(braket
id|channel
op_ne
l_int|0
)braket
)braket
suffix:semicolon
id|audio_level.monitor_mute1
op_assign
op_logical_neg
id|chip-&gt;monitoring_active
(braket
id|channel
op_ne
l_int|0
)braket
suffix:semicolon
id|err
op_assign
id|snd_mixart_send_msg
c_func
(paren
id|chip-&gt;mgr
comma
op_amp
id|request
comma
r_sizeof
(paren
id|resp
)paren
comma
op_amp
id|resp
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
OL
l_int|0
)paren
op_logical_or
id|resp
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;error MSG_CONNECTOR_SET_OUT_AUDIO_LEVEL card(%d) resp(%x)&bslash;n&quot;
comma
id|chip-&gt;chip_idx
comma
id|resp
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * monitoring level control&n; */
DECL|function|mixart_monitor_vol_get
r_static
r_int
id|mixart_monitor_vol_get
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|mixart_t
op_star
id|chip
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
id|chip-&gt;monitoring_volume
(braket
l_int|0
)braket
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|1
)braket
op_assign
id|chip-&gt;monitoring_volume
(braket
l_int|1
)braket
suffix:semicolon
id|up
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mixart_monitor_vol_put
r_static
r_int
id|mixart_monitor_vol_put
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|mixart_t
op_star
id|chip
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
id|changed
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|down
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|chip-&gt;monitoring_volume
(braket
id|i
)braket
op_ne
id|ucontrol-&gt;value.integer.value
(braket
id|i
)braket
)paren
(brace
id|chip-&gt;monitoring_volume
(braket
id|i
)braket
op_assign
id|ucontrol-&gt;value.integer.value
(braket
id|i
)braket
suffix:semicolon
id|mixart_update_monitoring
c_func
(paren
id|chip
comma
id|i
)paren
suffix:semicolon
id|changed
op_assign
l_int|1
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
r_return
id|changed
suffix:semicolon
)brace
DECL|variable|mixart_control_monitor_vol
r_static
id|snd_kcontrol_new_t
id|mixart_control_monitor_vol
op_assign
(brace
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
dot
id|name
op_assign
l_string|&quot;Monitoring Volume&quot;
comma
dot
id|info
op_assign
id|mixart_digital_vol_info
comma
multiline_comment|/* shared */
dot
id|get
op_assign
id|mixart_monitor_vol_get
comma
dot
id|put
op_assign
id|mixart_monitor_vol_put
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * monitoring switch control&n; */
DECL|function|mixart_monitor_sw_get
r_static
r_int
id|mixart_monitor_sw_get
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|mixart_t
op_star
id|chip
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
id|chip-&gt;monitoring_active
(braket
l_int|0
)braket
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|1
)braket
op_assign
id|chip-&gt;monitoring_active
(braket
l_int|1
)braket
suffix:semicolon
id|up
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mixart_monitor_sw_put
r_static
r_int
id|mixart_monitor_sw_put
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|mixart_t
op_star
id|chip
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
id|changed
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|down
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|chip-&gt;monitoring_active
(braket
id|i
)braket
op_ne
id|ucontrol-&gt;value.integer.value
(braket
id|i
)braket
)paren
(brace
id|chip-&gt;monitoring_active
(braket
id|i
)braket
op_assign
id|ucontrol-&gt;value.integer.value
(braket
id|i
)braket
suffix:semicolon
id|changed
op_or_assign
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
multiline_comment|/* mask 0x01 ans 0x02 */
)brace
)brace
r_if
c_cond
(paren
id|changed
)paren
(brace
multiline_comment|/* allocate or release resources for monitoring */
r_int
id|allocate
op_assign
id|chip-&gt;monitoring_active
(braket
l_int|0
)braket
op_logical_or
id|chip-&gt;monitoring_active
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|allocate
)paren
(brace
id|snd_mixart_add_ref_pipe
c_func
(paren
id|chip
comma
id|MIXART_PCM_ANALOG
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* allocate the playback pipe for monitoring */
id|snd_mixart_add_ref_pipe
c_func
(paren
id|chip
comma
id|MIXART_PCM_ANALOG
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* allocate the capture pipe for monitoring */
)brace
r_if
c_cond
(paren
id|changed
op_amp
l_int|0x01
)paren
(brace
id|mixart_update_monitoring
c_func
(paren
id|chip
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|changed
op_amp
l_int|0x02
)paren
(brace
id|mixart_update_monitoring
c_func
(paren
id|chip
comma
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|allocate
)paren
(brace
id|snd_mixart_kill_ref_pipe
c_func
(paren
id|chip-&gt;mgr
comma
op_amp
id|chip-&gt;pipe_in_ana
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* release the capture pipe for monitoring */
id|snd_mixart_kill_ref_pipe
c_func
(paren
id|chip-&gt;mgr
comma
op_amp
id|chip-&gt;pipe_out_ana
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* release the playback pipe for monitoring */
)brace
)brace
id|up
c_func
(paren
op_amp
id|chip-&gt;mgr-&gt;mixer_mutex
)paren
suffix:semicolon
r_return
(paren
id|changed
op_ne
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|mixart_control_monitor_sw
r_static
id|snd_kcontrol_new_t
id|mixart_control_monitor_sw
op_assign
(brace
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
dot
id|name
op_assign
l_string|&quot;Monitoring Switch&quot;
comma
dot
id|info
op_assign
id|mixart_sw_info
comma
multiline_comment|/* shared */
dot
id|get
op_assign
id|mixart_monitor_sw_get
comma
dot
id|put
op_assign
id|mixart_monitor_sw_put
)brace
suffix:semicolon
DECL|function|mixart_reset_audio_levels
r_static
r_void
id|mixart_reset_audio_levels
c_func
(paren
id|mixart_t
op_star
id|chip
)paren
(brace
multiline_comment|/* analog volumes can be set even if there is no pipe */
id|mixart_update_analog_audio_level
c_func
(paren
id|chip
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* analog levels for capture only on the first two chips */
r_if
c_cond
(paren
id|chip-&gt;chip_idx
OL
l_int|2
)paren
(brace
id|mixart_update_analog_audio_level
c_func
(paren
id|chip
comma
l_int|1
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|snd_mixart_create_mixer
r_int
id|snd_mixart_create_mixer
c_func
(paren
id|mixart_mgr_t
op_star
id|mgr
)paren
(brace
id|mixart_t
op_star
id|chip
suffix:semicolon
r_int
id|err
comma
id|i
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|mgr-&gt;mixer_mutex
)paren
suffix:semicolon
multiline_comment|/* can be in another place */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|mgr-&gt;num_cards
suffix:semicolon
id|i
op_increment
)paren
(brace
id|snd_kcontrol_new_t
id|temp
suffix:semicolon
id|chip
op_assign
id|mgr-&gt;chip
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/* analog output level control */
id|temp
op_assign
id|mixart_control_analog_level
suffix:semicolon
id|temp.name
op_assign
l_string|&quot;Master Playback Volume&quot;
suffix:semicolon
id|temp.private_value
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* playback */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|chip-&gt;card
comma
id|snd_ctl_new1
c_func
(paren
op_amp
id|temp
comma
id|chip
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* output mute controls */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|chip-&gt;card
comma
id|snd_ctl_new1
c_func
(paren
op_amp
id|mixart_control_output_switch
comma
id|chip
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* analog input level control only on first two chips !*/
r_if
c_cond
(paren
id|i
OL
l_int|2
)paren
(brace
id|temp
op_assign
id|mixart_control_analog_level
suffix:semicolon
id|temp.name
op_assign
l_string|&quot;Master Capture Volume&quot;
suffix:semicolon
id|temp.private_value
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* capture */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|chip-&gt;card
comma
id|snd_ctl_new1
c_func
(paren
op_amp
id|temp
comma
id|chip
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
)brace
id|temp
op_assign
id|snd_mixart_pcm_vol
suffix:semicolon
id|temp.name
op_assign
l_string|&quot;PCM Playback Volume&quot;
suffix:semicolon
id|temp.count
op_assign
id|MIXART_PLAYBACK_STREAMS
suffix:semicolon
id|temp.private_value
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* playback analog */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|chip-&gt;card
comma
id|snd_ctl_new1
c_func
(paren
op_amp
id|temp
comma
id|chip
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|temp.name
op_assign
l_string|&quot;PCM Capture Volume&quot;
suffix:semicolon
id|temp.count
op_assign
l_int|1
suffix:semicolon
id|temp.private_value
op_assign
id|MIXART_VOL_REC_MASK
suffix:semicolon
multiline_comment|/* capture analog */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|chip-&gt;card
comma
id|snd_ctl_new1
c_func
(paren
op_amp
id|temp
comma
id|chip
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|mgr-&gt;board_type
op_eq
id|MIXART_DAUGHTER_TYPE_AES
)paren
(brace
id|temp.name
op_assign
l_string|&quot;AES Playback Volume&quot;
suffix:semicolon
id|temp.count
op_assign
id|MIXART_PLAYBACK_STREAMS
suffix:semicolon
id|temp.private_value
op_assign
id|MIXART_VOL_AES_MASK
suffix:semicolon
multiline_comment|/* playback AES/EBU */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|chip-&gt;card
comma
id|snd_ctl_new1
c_func
(paren
op_amp
id|temp
comma
id|chip
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|temp.name
op_assign
l_string|&quot;AES Capture Volume&quot;
suffix:semicolon
id|temp.count
op_assign
l_int|0
suffix:semicolon
id|temp.private_value
op_assign
id|MIXART_VOL_REC_MASK
op_or
id|MIXART_VOL_AES_MASK
suffix:semicolon
multiline_comment|/* capture AES/EBU */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|chip-&gt;card
comma
id|snd_ctl_new1
c_func
(paren
op_amp
id|temp
comma
id|chip
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
)brace
id|temp
op_assign
id|mixart_control_pcm_switch
suffix:semicolon
id|temp.name
op_assign
l_string|&quot;PCM Playback Switch&quot;
suffix:semicolon
id|temp.private_value
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* playback analog */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|chip-&gt;card
comma
id|snd_ctl_new1
c_func
(paren
op_amp
id|temp
comma
id|chip
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|mgr-&gt;board_type
op_eq
id|MIXART_DAUGHTER_TYPE_AES
)paren
(brace
id|temp.name
op_assign
l_string|&quot;AES Playback Switch&quot;
suffix:semicolon
id|temp.private_value
op_assign
id|MIXART_VOL_AES_MASK
suffix:semicolon
multiline_comment|/* playback AES/EBU */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|chip-&gt;card
comma
id|snd_ctl_new1
c_func
(paren
op_amp
id|temp
comma
id|chip
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* monitoring */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|chip-&gt;card
comma
id|snd_ctl_new1
c_func
(paren
op_amp
id|mixart_control_monitor_vol
comma
id|chip
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|chip-&gt;card
comma
id|snd_ctl_new1
c_func
(paren
op_amp
id|mixart_control_monitor_sw
comma
id|chip
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* init all mixer data and program the master volumes/switches */
id|mixart_reset_audio_levels
c_func
(paren
id|chip
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
