multiline_comment|/*&n; * linux/drivers/ide/qd65xx.h&n; *&n; * Copyright (c) 2000&t;Linus Torvalds &amp; authors&n; */
multiline_comment|/*&n; * Authors:&t;Petr Soucek &lt;petr@ryston.cz&gt;&n; * &t;&t;Samuel Thibault &lt;samuel.thibault@fnac.net&gt;&n; */
multiline_comment|/* truncates a in [b,c] */
DECL|macro|IDE_IN
mdefine_line|#define IDE_IN(a,b,c)   ( ((a)&lt;(b)) ? (b) : ( (a)&gt;(c) ? (c) : (a)) )
DECL|macro|IDE_IMPLY
mdefine_line|#define IDE_IMPLY(a,b)&t;((!(a)) || (b))
DECL|macro|QD_TIM1_PORT
mdefine_line|#define QD_TIM1_PORT&t;&t;(base)
DECL|macro|QD_CONFIG_PORT
mdefine_line|#define QD_CONFIG_PORT&t;&t;(base+0x01)
DECL|macro|QD_TIM2_PORT
mdefine_line|#define QD_TIM2_PORT&t;&t;(base+0x02)
DECL|macro|QD_CONTROL_PORT
mdefine_line|#define QD_CONTROL_PORT&t;&t;(base+0x03)
DECL|macro|QD_CONFIG_IDE_BASEPORT
mdefine_line|#define QD_CONFIG_IDE_BASEPORT&t;0x01
DECL|macro|QD_CONFIG_BASEPORT
mdefine_line|#define QD_CONFIG_BASEPORT&t;0x02
DECL|macro|QD_CONFIG_ID3
mdefine_line|#define QD_CONFIG_ID3&t;&t;0x04
DECL|macro|QD_CONFIG_DISABLED
mdefine_line|#define QD_CONFIG_DISABLED&t;0x08
DECL|macro|QD_CONFIG_QD6500
mdefine_line|#define QD_CONFIG_QD6500&t;0xc0
DECL|macro|QD_CONFIG_QD6580_A
mdefine_line|#define QD_CONFIG_QD6580_A&t;0xa0
DECL|macro|QD_CONFIG_QD6580_B
mdefine_line|#define QD_CONFIG_QD6580_B&t;0x50
DECL|macro|QD_CONTR_SEC_DISABLED
mdefine_line|#define QD_CONTR_SEC_DISABLED&t;0x01
DECL|macro|QD_ID3
mdefine_line|#define QD_ID3&t;&t;&t;(config &amp; QD_CONFIG_ID3)
DECL|macro|QD_CONFIG
mdefine_line|#define QD_CONFIG(hwif)&t;&t;((hwif)-&gt;config_data &amp; 0x00ff)
DECL|macro|QD_CONTROL
mdefine_line|#define QD_CONTROL(hwif)&t;(((hwif)-&gt;config_data &amp; 0xff00) &gt;&gt; 8)
DECL|macro|QD_TIMING
mdefine_line|#define QD_TIMING(drive)&t;(byte)(((drive)-&gt;drive_data) &amp; 0x00ff)
DECL|macro|QD_TIMREG
mdefine_line|#define QD_TIMREG(drive)&t;(byte)((((drive)-&gt;drive_data) &amp; 0xff00) &gt;&gt; 8)
DECL|macro|QD6500_DEF_DATA
mdefine_line|#define QD6500_DEF_DATA&t;&t;((QD_TIM1_PORT&lt;&lt;8) | (QD_ID3 ? 0x0c : 0x08))
DECL|macro|QD6580_DEF_DATA
mdefine_line|#define QD6580_DEF_DATA&t;&t;((QD_TIM1_PORT&lt;&lt;8) | (QD_ID3 ? 0x0a : 0x00))
DECL|macro|QD_DEF_CONTR
mdefine_line|#define QD_DEF_CONTR&t;&t;(0x40 | ((control &amp; 0x02) ? 0x9f : 0x1f))
DECL|macro|QD_TESTVAL
mdefine_line|#define QD_TESTVAL&t;&t;0x19&t;/* safe value */
multiline_comment|/* Drive specific timing taken from DOS driver v3.7 */
DECL|struct|qd65xx_timing_s
r_struct
id|qd65xx_timing_s
(brace
DECL|member|offset
r_char
id|offset
suffix:semicolon
multiline_comment|/* ofset from the beginning of Model Number&quot; */
DECL|member|model
r_char
id|model
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 4 chars from Model number, no conversion */
DECL|member|active
r_int
id|active
suffix:semicolon
multiline_comment|/* active time */
DECL|member|recovery
r_int
id|recovery
suffix:semicolon
multiline_comment|/* recovery time */
DECL|variable|qd65xx_timing
)brace
id|qd65xx_timing
(braket
)braket
op_assign
(brace
(brace
l_int|30
comma
l_string|&quot;2040&quot;
comma
l_int|110
comma
l_int|225
)brace
comma
multiline_comment|/* Conner CP30204&t;&t;&t;*/
(brace
l_int|30
comma
l_string|&quot;2045&quot;
comma
l_int|135
comma
l_int|225
)brace
comma
multiline_comment|/* Conner CP30254&t;&t;&t;*/
(brace
l_int|30
comma
l_string|&quot;1040&quot;
comma
l_int|155
comma
l_int|325
)brace
comma
multiline_comment|/* Conner CP30104&t;&t;&t;*/
(brace
l_int|30
comma
l_string|&quot;1047&quot;
comma
l_int|135
comma
l_int|265
)brace
comma
multiline_comment|/* Conner CP30174&t;&t;&t;*/
(brace
l_int|30
comma
l_string|&quot;5344&quot;
comma
l_int|135
comma
l_int|225
)brace
comma
multiline_comment|/* Conner CP3544&t;&t;&t;*/
(brace
l_int|30
comma
l_string|&quot;01 4&quot;
comma
l_int|175
comma
l_int|405
)brace
comma
multiline_comment|/* Conner CP-3104&t;&t;&t;*/
(brace
l_int|27
comma
l_string|&quot;C030&quot;
comma
l_int|175
comma
l_int|375
)brace
comma
multiline_comment|/* Conner CP3000&t;&t;&t;*/
(brace
l_int|8
comma
l_string|&quot;PL42&quot;
comma
l_int|110
comma
l_int|295
)brace
comma
multiline_comment|/* Quantum LP240&t;&t;&t;*/
(brace
l_int|8
comma
l_string|&quot;PL21&quot;
comma
l_int|110
comma
l_int|315
)brace
comma
multiline_comment|/* Quantum LP120&t;&t;&t;*/
(brace
l_int|8
comma
l_string|&quot;PL25&quot;
comma
l_int|175
comma
l_int|385
)brace
comma
multiline_comment|/* Quantum LP52&t;&t;&t;*/
(brace
l_int|4
comma
l_string|&quot;PA24&quot;
comma
l_int|110
comma
l_int|285
)brace
comma
multiline_comment|/* WD Piranha SP4200&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;2200&quot;
comma
l_int|110
comma
l_int|260
)brace
comma
multiline_comment|/* WD Caviar AC2200&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;3204&quot;
comma
l_int|110
comma
l_int|235
)brace
comma
multiline_comment|/* WD Caviar AC2340&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;1202&quot;
comma
l_int|110
comma
l_int|265
)brace
comma
multiline_comment|/* WD Caviar AC2120&t;&t;&t;*/
(brace
l_int|0
comma
l_string|&quot;DS3-&quot;
comma
l_int|135
comma
l_int|315
)brace
comma
multiline_comment|/* Teac SD340&t;&t;&t;*/
(brace
l_int|8
comma
l_string|&quot;KM32&quot;
comma
l_int|175
comma
l_int|355
)brace
comma
multiline_comment|/* Toshiba MK234&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;53A1&quot;
comma
l_int|175
comma
l_int|355
)brace
comma
multiline_comment|/* Seagate ST351A&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;4108&quot;
comma
l_int|175
comma
l_int|295
)brace
comma
multiline_comment|/* Seagate ST1480A&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;1344&quot;
comma
l_int|175
comma
l_int|335
)brace
comma
multiline_comment|/* Seagate ST3144A&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;7 12&quot;
comma
l_int|110
comma
l_int|225
)brace
comma
multiline_comment|/* Maxtor 7213A&t;&t;&t;*/
(brace
l_int|30
comma
l_string|&quot;02F4&quot;
comma
l_int|145
comma
l_int|295
)brace
comma
multiline_comment|/* Conner 3204F&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;1302&quot;
comma
l_int|175
comma
l_int|335
)brace
comma
multiline_comment|/* Seagate ST3120A&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;2334&quot;
comma
l_int|145
comma
l_int|265
)brace
comma
multiline_comment|/* Seagate ST3243A&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;2338&quot;
comma
l_int|145
comma
l_int|275
)brace
comma
multiline_comment|/* Seagate ST3283A&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;3309&quot;
comma
l_int|145
comma
l_int|275
)brace
comma
multiline_comment|/* Seagate ST3390A&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;5305&quot;
comma
l_int|145
comma
l_int|275
)brace
comma
multiline_comment|/* Seagate ST3550A&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;4100&quot;
comma
l_int|175
comma
l_int|295
)brace
comma
multiline_comment|/* Seagate ST1400A&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;4110&quot;
comma
l_int|175
comma
l_int|295
)brace
comma
multiline_comment|/* Seagate ST1401A&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;6300&quot;
comma
l_int|135
comma
l_int|265
)brace
comma
multiline_comment|/* Seagate ST3600A&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;5300&quot;
comma
l_int|135
comma
l_int|265
)brace
comma
multiline_comment|/* Seagate ST3500A&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;7 31&quot;
comma
l_int|135
comma
l_int|225
)brace
comma
multiline_comment|/* Maxtor 7131 AT&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;7 43&quot;
comma
l_int|115
comma
l_int|265
)brace
comma
multiline_comment|/* Maxtor 7345 AT&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;7 42&quot;
comma
l_int|110
comma
l_int|255
)brace
comma
multiline_comment|/* Maxtor 7245 AT&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;3 04&quot;
comma
l_int|135
comma
l_int|265
)brace
comma
multiline_comment|/* Maxtor 340 AT&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;61 0&quot;
comma
l_int|135
comma
l_int|285
)brace
comma
multiline_comment|/* WD AC160&t;&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;1107&quot;
comma
l_int|135
comma
l_int|235
)brace
comma
multiline_comment|/* WD AC1170&t;&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;2101&quot;
comma
l_int|110
comma
l_int|220
)brace
comma
multiline_comment|/* WD AC1210&t;&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;4202&quot;
comma
l_int|135
comma
l_int|245
)brace
comma
multiline_comment|/* WD AC2420&t;&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;41 0&quot;
comma
l_int|175
comma
l_int|355
)brace
comma
multiline_comment|/* WD Caviar 140&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;82 0&quot;
comma
l_int|175
comma
l_int|355
)brace
comma
multiline_comment|/* WD Caviar 280&t;&t;&t;*/
(brace
l_int|8
comma
l_string|&quot;PL01&quot;
comma
l_int|175
comma
l_int|375
)brace
comma
multiline_comment|/* Quantum LP105&t;&t;&t;*/
(brace
l_int|8
comma
l_string|&quot;PL25&quot;
comma
l_int|110
comma
l_int|295
)brace
comma
multiline_comment|/* Quantum LP525&t;&t;&t;*/
(brace
l_int|10
comma
l_string|&quot;4S 2&quot;
comma
l_int|175
comma
l_int|385
)brace
comma
multiline_comment|/* Quantum ELS42&t;&t;&t;*/
(brace
l_int|10
comma
l_string|&quot;8S 5&quot;
comma
l_int|175
comma
l_int|385
)brace
comma
multiline_comment|/* Quantum ELS85&t;&t;&t;*/
(brace
l_int|10
comma
l_string|&quot;1S72&quot;
comma
l_int|175
comma
l_int|385
)brace
comma
multiline_comment|/* Quantum ELS127&t;&t;&t;*/
(brace
l_int|10
comma
l_string|&quot;1S07&quot;
comma
l_int|175
comma
l_int|385
)brace
comma
multiline_comment|/* Quantum ELS170&t;&t;&t;*/
(brace
l_int|8
comma
l_string|&quot;ZE42&quot;
comma
l_int|135
comma
l_int|295
)brace
comma
multiline_comment|/* Quantum EZ240&t;&t;&t;*/
(brace
l_int|8
comma
l_string|&quot;ZE21&quot;
comma
l_int|175
comma
l_int|385
)brace
comma
multiline_comment|/* Quantum EZ127&t;&t;&t;*/
(brace
l_int|8
comma
l_string|&quot;ZE58&quot;
comma
l_int|175
comma
l_int|385
)brace
comma
multiline_comment|/* Quantum EZ85&t;&t;&t;*/
(brace
l_int|8
comma
l_string|&quot;ZE24&quot;
comma
l_int|175
comma
l_int|385
)brace
comma
multiline_comment|/* Quantum EZ42&t;&t;&t;*/
(brace
l_int|27
comma
l_string|&quot;C036&quot;
comma
l_int|155
comma
l_int|325
)brace
comma
multiline_comment|/* Conner CP30064&t;&t;&t;*/
(brace
l_int|27
comma
l_string|&quot;C038&quot;
comma
l_int|155
comma
l_int|325
)brace
comma
multiline_comment|/* Conner CP30084&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;2205&quot;
comma
l_int|110
comma
l_int|255
)brace
comma
multiline_comment|/* WDC AC2250&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot; CHA&quot;
comma
l_int|140
comma
l_int|415
)brace
comma
multiline_comment|/* WDC AH series; WDC AH260, WDC&t;*/
(brace
l_int|2
comma
l_string|&quot; CLA&quot;
comma
l_int|140
comma
l_int|415
)brace
comma
multiline_comment|/* WDC AL series: WDC AL2120, 2170,&t;*/
(brace
l_int|4
comma
l_string|&quot;UC41&quot;
comma
l_int|140
comma
l_int|415
)brace
comma
multiline_comment|/* WDC CU140&t;&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;1207&quot;
comma
l_int|130
comma
l_int|275
)brace
comma
multiline_comment|/* WDC AC2170&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;2107&quot;
comma
l_int|130
comma
l_int|275
)brace
comma
multiline_comment|/* WDC AC1270&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;5204&quot;
comma
l_int|130
comma
l_int|275
)brace
comma
multiline_comment|/* WDC AC2540&t;&t;&t;*/
(brace
l_int|30
comma
l_string|&quot;3004&quot;
comma
l_int|110
comma
l_int|235
)brace
comma
multiline_comment|/* Conner CP30340&t;&t;&t;*/
(brace
l_int|30
comma
l_string|&quot;0345&quot;
comma
l_int|135
comma
l_int|255
)brace
comma
multiline_comment|/* Conner CP30544&t;&t;&t;*/
(brace
l_int|12
comma
l_string|&quot;12A3&quot;
comma
l_int|175
comma
l_int|320
)brace
comma
multiline_comment|/* MAXTOR LXT-213A&t;&t;&t;*/
(brace
l_int|12
comma
l_string|&quot;43A0&quot;
comma
l_int|145
comma
l_int|240
)brace
comma
multiline_comment|/* MAXTOR LXT-340A&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;7 21&quot;
comma
l_int|180
comma
l_int|290
)brace
comma
multiline_comment|/* Maxtor 7120 AT&t;&t;&t;*/
(brace
l_int|6
comma
l_string|&quot;7 71&quot;
comma
l_int|135
comma
l_int|240
)brace
comma
multiline_comment|/* Maxtor 7170 AT&t;&t;&t;*/
(brace
l_int|12
comma
l_string|&quot;45&bslash;0000&quot;
comma
l_int|110
comma
l_int|205
)brace
comma
multiline_comment|/* MAXTOR MXT-540&t;&t;*/
(brace
l_int|8
comma
l_string|&quot;PL11&quot;
comma
l_int|180
comma
l_int|290
)brace
comma
multiline_comment|/* QUANTUM LP110A&t;&t;&t;*/
(brace
l_int|8
comma
l_string|&quot;OG21&quot;
comma
l_int|150
comma
l_int|275
)brace
comma
multiline_comment|/* QUANTUM GO120&t;&t;&t;*/
(brace
l_int|12
comma
l_string|&quot;42A5&quot;
comma
l_int|175
comma
l_int|320
)brace
comma
multiline_comment|/* MAXTOR LXT-245A&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;2309&quot;
comma
l_int|175
comma
l_int|295
)brace
comma
multiline_comment|/* ST3290A&t;&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;3358&quot;
comma
l_int|180
comma
l_int|310
)brace
comma
multiline_comment|/* ST3385A&t;&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;6355&quot;
comma
l_int|180
comma
l_int|310
)brace
comma
multiline_comment|/* ST3655A&t;&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;1900&quot;
comma
l_int|175
comma
l_int|270
)brace
comma
multiline_comment|/* ST9100A&t;&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;1954&quot;
comma
l_int|175
comma
l_int|270
)brace
comma
multiline_comment|/* ST9145A&t;&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;1909&quot;
comma
l_int|175
comma
l_int|270
)brace
comma
multiline_comment|/* ST9190AG&t;&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;2953&quot;
comma
l_int|175
comma
l_int|270
)brace
comma
multiline_comment|/* ST9235A&t;&t;&t;&t;*/
(brace
l_int|2
comma
l_string|&quot;1359&quot;
comma
l_int|175
comma
l_int|270
)brace
comma
multiline_comment|/* ST3195A&t;&t;&t;&t;*/
(brace
l_int|24
comma
l_string|&quot;3R11&quot;
comma
l_int|175
comma
l_int|290
)brace
comma
multiline_comment|/* ALPS ELECTRIC Co.,LTD, DR311C&t;*/
(brace
l_int|0
comma
l_string|&quot;2M26&quot;
comma
l_int|175
comma
l_int|215
)brace
comma
multiline_comment|/* M262XT-0Ah&t;&t;&t;*/
(brace
l_int|4
comma
l_string|&quot;2253&quot;
comma
l_int|175
comma
l_int|300
)brace
comma
multiline_comment|/* HP C2235A&t;&t;&t;&t;*/
(brace
l_int|4
comma
l_string|&quot;-32A&quot;
comma
l_int|145
comma
l_int|245
)brace
comma
multiline_comment|/* H3133-A2&t;&t;&t;&t;*/
(brace
l_int|30
comma
l_string|&quot;0326&quot;
comma
l_int|150
comma
l_int|270
)brace
comma
multiline_comment|/* Samsung Electronics 120MB&t;&t;*/
(brace
l_int|30
comma
l_string|&quot;3044&quot;
comma
l_int|110
comma
l_int|195
)brace
comma
multiline_comment|/* Conner CFA340A&t;&t;&t;*/
(brace
l_int|30
comma
l_string|&quot;43A0&quot;
comma
l_int|110
comma
l_int|195
)brace
comma
multiline_comment|/* Conner CFA340A&t;&t;&t;*/
(brace
op_minus
l_int|1
comma
l_string|&quot;    &quot;
comma
l_int|175
comma
l_int|415
)brace
multiline_comment|/* unknown disk name&t;&t;&t;*/
)brace
suffix:semicolon
eof
