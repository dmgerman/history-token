multiline_comment|/*&n; * sound/oss/sb_card.h&n; *&n; * This file is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this&n; * software for more info.&n; *&n; * 02-05-2002 Original Release, Paul Laufer &lt;paul@laufernet.com&gt;&n; */
DECL|struct|sb_card_config
r_struct
id|sb_card_config
(brace
DECL|member|conf
r_struct
id|address_info
id|conf
suffix:semicolon
DECL|member|mpucnf
r_struct
id|address_info
id|mpucnf
suffix:semicolon
DECL|member|card_id
r_const
r_char
op_star
id|card_id
suffix:semicolon
DECL|member|dev_id
r_const
r_char
op_star
id|dev_id
suffix:semicolon
DECL|member|mpu
r_int
id|mpu
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_PNP
multiline_comment|/*&n; * SoundBlaster PnP tables and structures.&n; */
multiline_comment|/* Card PnP ID Table */
DECL|variable|sb_pnp_card_table
r_static
r_struct
id|pnp_card_device_id
id|sb_pnp_card_table
(braket
)braket
op_assign
(brace
multiline_comment|/* Sound Blaster 16 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0024&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0031&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster 16 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0025&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0031&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster 16 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0026&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0031&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster 16 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0027&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0031&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster 16 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0028&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0031&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster 16 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0029&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0031&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster 16 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL002a&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0031&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster 16 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL002b&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0031&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster 16 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL002c&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0031&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster 16 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL00ed&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0041&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster 16 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0086&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0041&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster Vibra16S */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0051&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0001&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster Vibra16C */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0070&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0001&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster Vibra16CL */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0080&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0041&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster Vibra16CL */
(brace
dot
id|id
op_assign
l_string|&quot;CTL00F0&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0043&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 32 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0039&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0031&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 32 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0042&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0031&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 32 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0043&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0031&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 32 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0044&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0031&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 32 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0045&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0031&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 32 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0046&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0031&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 32 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0047&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0031&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 32 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0048&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0031&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 32 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL0054&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0031&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 32 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL009C&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0041&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Createive SB32 PnP */
(brace
dot
id|id
op_assign
l_string|&quot;CTL009F&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0041&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 64 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL009D&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0042&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 64 Gold */
(brace
dot
id|id
op_assign
l_string|&quot;CTL009E&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0044&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 64 Gold */
(brace
dot
id|id
op_assign
l_string|&quot;CTL00B2&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0044&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 64 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL00C1&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0042&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 64 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL00C3&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0045&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 64 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL00C5&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0045&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 64 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL00C7&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0045&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 64 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL00E4&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0045&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Sound Blaster AWE 64 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL00E9&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CTL0045&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* ESS 1868 */
(brace
dot
id|id
op_assign
l_string|&quot;ESS0968&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;ESS0968&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* ESS 1868 */
(brace
dot
id|id
op_assign
l_string|&quot;ESS1868&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;ESS1868&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* ESS 1868 */
(brace
dot
id|id
op_assign
l_string|&quot;ESS1868&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;ESS8611&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* ESS 1869 PnP AudioDrive */
(brace
dot
id|id
op_assign
l_string|&quot;ESS0003&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;ESS1869&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* ESS 1869 */
(brace
dot
id|id
op_assign
l_string|&quot;ESS1869&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;ESS1869&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* ESS 1878 */
(brace
dot
id|id
op_assign
l_string|&quot;ESS1878&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;ESS1878&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* ESS 1879 */
(brace
dot
id|id
op_assign
l_string|&quot;ESS1879&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;ESS1879&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* CMI 8330 SoundPRO */
(brace
dot
id|id
op_assign
l_string|&quot;CMI0001&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;@X@0001&quot;
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;@H@0001&quot;
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;@@@0001&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Diamond DT0197H */
(brace
dot
id|id
op_assign
l_string|&quot;RWR1688&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;@@@0001&quot;
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;@X@0001&quot;
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;@H@0001&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* ALS007 */
(brace
dot
id|id
op_assign
l_string|&quot;ALS0007&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;@@@0001&quot;
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;@X@0001&quot;
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;@H@0001&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* ALS100 */
(brace
dot
id|id
op_assign
l_string|&quot;ALS0001&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;@@@0001&quot;
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;@X@0001&quot;
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;@H@0001&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* ALS110 */
(brace
dot
id|id
op_assign
l_string|&quot;ALS0110&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;@@@1001&quot;
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;@X@1001&quot;
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;@H@0001&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* ALS120 */
(brace
dot
id|id
op_assign
l_string|&quot;ALS0120&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;@@@2001&quot;
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;@X@2001&quot;
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;@H@0001&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* ALS200 */
(brace
dot
id|id
op_assign
l_string|&quot;ALS0200&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;@@@0020&quot;
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;@X@0030&quot;
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;@H@0001&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* ALS200 */
(brace
dot
id|id
op_assign
l_string|&quot;RTL3000&quot;
comma
dot
id|driver_data
op_assign
l_int|0
comma
id|devs
suffix:colon
(brace
(brace
dot
id|id
op_assign
l_string|&quot;@@@2001&quot;
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;@X@2001&quot;
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;@H@0001&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* -end- */
(brace
dot
id|id
op_assign
l_string|&quot;&quot;
comma
)brace
)brace
suffix:semicolon
macro_line|#endif
eof
