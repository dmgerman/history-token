multiline_comment|/*&n; *  longhaul.h&n; *  (C) 2003 Dave Jones.&n; *&n; *  Licensed under the terms of the GNU GPL License version 2.&n; *&n; *  VIA-specific information&n; */
DECL|union|msr_bcr2
r_union
id|msr_bcr2
(brace
r_struct
(brace
DECL|member|Reseved
r_int
id|Reseved
suffix:colon
l_int|19
comma
singleline_comment|// 18:0
DECL|member|ESOFTBF
id|ESOFTBF
suffix:colon
l_int|1
comma
singleline_comment|// 19
DECL|member|Reserved2
id|Reserved2
suffix:colon
l_int|3
comma
singleline_comment|// 22:20
DECL|member|CLOCKMUL
id|CLOCKMUL
suffix:colon
l_int|4
comma
singleline_comment|// 26:23
DECL|member|Reserved3
id|Reserved3
suffix:colon
l_int|5
suffix:semicolon
singleline_comment|// 31:27
DECL|member|bits
)brace
id|bits
suffix:semicolon
DECL|member|val
r_int
r_int
id|val
suffix:semicolon
)brace
suffix:semicolon
DECL|union|msr_longhaul
r_union
id|msr_longhaul
(brace
r_struct
(brace
DECL|member|RevisionID
r_int
id|RevisionID
suffix:colon
l_int|4
comma
singleline_comment|// 3:0
DECL|member|RevisionKey
id|RevisionKey
suffix:colon
l_int|4
comma
singleline_comment|// 7:4
DECL|member|EnableSoftBusRatio
id|EnableSoftBusRatio
suffix:colon
l_int|1
comma
singleline_comment|// 8
DECL|member|EnableSoftVID
id|EnableSoftVID
suffix:colon
l_int|1
comma
singleline_comment|// 9
DECL|member|EnableSoftBSEL
id|EnableSoftBSEL
suffix:colon
l_int|1
comma
singleline_comment|// 10
DECL|member|Reserved
id|Reserved
suffix:colon
l_int|3
comma
singleline_comment|// 11:13
DECL|member|SoftBusRatio4
id|SoftBusRatio4
suffix:colon
l_int|1
comma
singleline_comment|// 14
DECL|member|VRMRev
id|VRMRev
suffix:colon
l_int|1
comma
singleline_comment|// 15
DECL|member|SoftBusRatio
id|SoftBusRatio
suffix:colon
l_int|4
comma
singleline_comment|// 19:16
DECL|member|SoftVID
id|SoftVID
suffix:colon
l_int|5
comma
singleline_comment|// 24:20
DECL|member|Reserved2
id|Reserved2
suffix:colon
l_int|3
comma
singleline_comment|// 27:25
DECL|member|SoftBSEL
id|SoftBSEL
suffix:colon
l_int|2
comma
singleline_comment|// 29:28
DECL|member|Reserved3
id|Reserved3
suffix:colon
l_int|2
comma
singleline_comment|// 31:30
DECL|member|MaxMHzBR
id|MaxMHzBR
suffix:colon
l_int|4
comma
singleline_comment|// 35:32
DECL|member|MaximumVID
id|MaximumVID
suffix:colon
l_int|5
comma
singleline_comment|// 40:36
DECL|member|MaxMHzFSB
id|MaxMHzFSB
suffix:colon
l_int|2
comma
singleline_comment|// 42:41
DECL|member|MaxMHzBR4
id|MaxMHzBR4
suffix:colon
l_int|1
comma
singleline_comment|// 43
DECL|member|Reserved4
id|Reserved4
suffix:colon
l_int|4
comma
singleline_comment|// 47:44
DECL|member|MinMHzBR
id|MinMHzBR
suffix:colon
l_int|4
comma
singleline_comment|// 51:48
DECL|member|MinimumVID
id|MinimumVID
suffix:colon
l_int|5
comma
singleline_comment|// 56:52
DECL|member|MinMHzFSB
id|MinMHzFSB
suffix:colon
l_int|2
comma
singleline_comment|// 58:57
DECL|member|MinMHzBR4
id|MinMHzBR4
suffix:colon
l_int|1
comma
singleline_comment|// 59
DECL|member|Reserved5
id|Reserved5
suffix:colon
l_int|4
suffix:semicolon
singleline_comment|// 63:60
DECL|member|bits
)brace
id|bits
suffix:semicolon
DECL|member|val
r_int
r_int
r_int
id|val
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Clock ratio tables. Div/Mod by 10 to get ratio.&n; * The eblcr ones specify the ratio read from the CPU.&n; * The clock_ratio ones specify what to write to the CPU.&n; */
multiline_comment|/*&n; * VIA C3 Samuel 1  &amp; Samuel 2 (stepping 0)&n; */
DECL|variable|samuel1_clock_ratio
r_static
r_int
id|__initdata
id|samuel1_clock_ratio
(braket
l_int|16
)braket
op_assign
(brace
op_minus
l_int|1
comma
multiline_comment|/* 0000 -&gt; RESERVED */
l_int|30
comma
multiline_comment|/* 0001 -&gt;  3.0x */
l_int|40
comma
multiline_comment|/* 0010 -&gt;  4.0x */
op_minus
l_int|1
comma
multiline_comment|/* 0011 -&gt; RESERVED */
op_minus
l_int|1
comma
multiline_comment|/* 0100 -&gt; RESERVED */
l_int|35
comma
multiline_comment|/* 0101 -&gt;  3.5x */
l_int|45
comma
multiline_comment|/* 0110 -&gt;  4.5x */
l_int|55
comma
multiline_comment|/* 0111 -&gt;  5.5x */
l_int|60
comma
multiline_comment|/* 1000 -&gt;  6.0x */
l_int|70
comma
multiline_comment|/* 1001 -&gt;  7.0x */
l_int|80
comma
multiline_comment|/* 1010 -&gt;  8.0x */
l_int|50
comma
multiline_comment|/* 1011 -&gt;  5.0x */
l_int|65
comma
multiline_comment|/* 1100 -&gt;  6.5x */
l_int|75
comma
multiline_comment|/* 1101 -&gt;  7.5x */
op_minus
l_int|1
comma
multiline_comment|/* 1110 -&gt; RESERVED */
op_minus
l_int|1
comma
multiline_comment|/* 1111 -&gt; RESERVED */
)brace
suffix:semicolon
DECL|variable|samuel1_eblcr
r_static
r_int
id|__initdata
id|samuel1_eblcr
(braket
l_int|16
)braket
op_assign
(brace
l_int|50
comma
multiline_comment|/* 0000 -&gt; RESERVED */
l_int|30
comma
multiline_comment|/* 0001 -&gt;  3.0x */
l_int|40
comma
multiline_comment|/* 0010 -&gt;  4.0x */
op_minus
l_int|1
comma
multiline_comment|/* 0011 -&gt; RESERVED */
l_int|55
comma
multiline_comment|/* 0100 -&gt;  5.5x */
l_int|35
comma
multiline_comment|/* 0101 -&gt;  3.5x */
l_int|45
comma
multiline_comment|/* 0110 -&gt;  4.5x */
op_minus
l_int|1
comma
multiline_comment|/* 0111 -&gt; RESERVED */
op_minus
l_int|1
comma
multiline_comment|/* 1000 -&gt; RESERVED */
l_int|70
comma
multiline_comment|/* 1001 -&gt;  7.0x */
l_int|80
comma
multiline_comment|/* 1010 -&gt;  8.0x */
l_int|60
comma
multiline_comment|/* 1011 -&gt;  6.0x */
op_minus
l_int|1
comma
multiline_comment|/* 1100 -&gt; RESERVED */
l_int|75
comma
multiline_comment|/* 1101 -&gt;  7.5x */
op_minus
l_int|1
comma
multiline_comment|/* 1110 -&gt; RESERVED */
l_int|65
comma
multiline_comment|/* 1111 -&gt;  6.5x */
)brace
suffix:semicolon
multiline_comment|/*&n; * VIA C3 Samuel2 Stepping 1-&gt;15 &amp; VIA C3 Ezra&n; */
DECL|variable|ezra_clock_ratio
r_static
r_int
id|__initdata
id|ezra_clock_ratio
(braket
l_int|16
)braket
op_assign
(brace
l_int|100
comma
multiline_comment|/* 0000 -&gt; 10.0x */
l_int|30
comma
multiline_comment|/* 0001 -&gt;  3.0x */
l_int|40
comma
multiline_comment|/* 0010 -&gt;  4.0x */
l_int|90
comma
multiline_comment|/* 0011 -&gt;  9.0x */
l_int|95
comma
multiline_comment|/* 0100 -&gt;  9.5x */
l_int|35
comma
multiline_comment|/* 0101 -&gt;  3.5x */
l_int|45
comma
multiline_comment|/* 0110 -&gt;  4.5x */
l_int|55
comma
multiline_comment|/* 0111 -&gt;  5.5x */
l_int|60
comma
multiline_comment|/* 1000 -&gt;  6.0x */
l_int|70
comma
multiline_comment|/* 1001 -&gt;  7.0x */
l_int|80
comma
multiline_comment|/* 1010 -&gt;  8.0x */
l_int|50
comma
multiline_comment|/* 1011 -&gt;  5.0x */
l_int|65
comma
multiline_comment|/* 1100 -&gt;  6.5x */
l_int|75
comma
multiline_comment|/* 1101 -&gt;  7.5x */
l_int|85
comma
multiline_comment|/* 1110 -&gt;  8.5x */
l_int|120
comma
multiline_comment|/* 1111 -&gt; 12.0x */
)brace
suffix:semicolon
DECL|variable|samuel2_eblcr
r_static
r_int
id|__initdata
id|samuel2_eblcr
(braket
l_int|16
)braket
op_assign
(brace
l_int|50
comma
multiline_comment|/* 0000 -&gt;  5.0x */
l_int|30
comma
multiline_comment|/* 0001 -&gt;  3.0x */
l_int|40
comma
multiline_comment|/* 0010 -&gt;  4.0x */
l_int|100
comma
multiline_comment|/* 0011 -&gt; 10.0x */
l_int|55
comma
multiline_comment|/* 0100 -&gt;  5.5x */
l_int|35
comma
multiline_comment|/* 0101 -&gt;  3.5x */
l_int|45
comma
multiline_comment|/* 0110 -&gt;  4.5x */
l_int|110
comma
multiline_comment|/* 0111 -&gt; 11.0x */
l_int|90
comma
multiline_comment|/* 1000 -&gt;  9.0x */
l_int|70
comma
multiline_comment|/* 1001 -&gt;  7.0x */
l_int|80
comma
multiline_comment|/* 1010 -&gt;  8.0x */
l_int|60
comma
multiline_comment|/* 1011 -&gt;  6.0x */
l_int|120
comma
multiline_comment|/* 1100 -&gt; 12.0x */
l_int|75
comma
multiline_comment|/* 1101 -&gt;  7.5x */
l_int|130
comma
multiline_comment|/* 1110 -&gt; 13.0x */
l_int|65
comma
multiline_comment|/* 1111 -&gt;  6.5x */
)brace
suffix:semicolon
DECL|variable|ezra_eblcr
r_static
r_int
id|__initdata
id|ezra_eblcr
(braket
l_int|16
)braket
op_assign
(brace
l_int|50
comma
multiline_comment|/* 0000 -&gt;  5.0x */
l_int|30
comma
multiline_comment|/* 0001 -&gt;  3.0x */
l_int|40
comma
multiline_comment|/* 0010 -&gt;  4.0x */
l_int|100
comma
multiline_comment|/* 0011 -&gt; 10.0x */
l_int|55
comma
multiline_comment|/* 0100 -&gt;  5.5x */
l_int|35
comma
multiline_comment|/* 0101 -&gt;  3.5x */
l_int|45
comma
multiline_comment|/* 0110 -&gt;  4.5x */
l_int|95
comma
multiline_comment|/* 0111 -&gt;  9.5x */
l_int|90
comma
multiline_comment|/* 1000 -&gt;  9.0x */
l_int|70
comma
multiline_comment|/* 1001 -&gt;  7.0x */
l_int|80
comma
multiline_comment|/* 1010 -&gt;  8.0x */
l_int|60
comma
multiline_comment|/* 1011 -&gt;  6.0x */
l_int|120
comma
multiline_comment|/* 1100 -&gt; 12.0x */
l_int|75
comma
multiline_comment|/* 1101 -&gt;  7.5x */
l_int|85
comma
multiline_comment|/* 1110 -&gt;  8.5x */
l_int|65
comma
multiline_comment|/* 1111 -&gt;  6.5x */
)brace
suffix:semicolon
multiline_comment|/*&n; * VIA C3 (Ezra-T) [C5M].&n; */
DECL|variable|longhaul3_clock_ratio
r_static
r_int
id|__initdata
id|longhaul3_clock_ratio
(braket
l_int|32
)braket
op_assign
(brace
l_int|100
comma
multiline_comment|/* 0000 -&gt; 10.0x */
l_int|30
comma
multiline_comment|/* 0001 -&gt;  3.0x */
l_int|40
comma
multiline_comment|/* 0010 -&gt;  4.0x */
l_int|90
comma
multiline_comment|/* 0011 -&gt;  9.0x */
l_int|95
comma
multiline_comment|/* 0100 -&gt;  9.5x */
l_int|35
comma
multiline_comment|/* 0101 -&gt;  3.5x */
l_int|45
comma
multiline_comment|/* 0110 -&gt;  4.5x */
l_int|55
comma
multiline_comment|/* 0111 -&gt;  5.5x */
l_int|60
comma
multiline_comment|/* 1000 -&gt;  6.0x */
l_int|70
comma
multiline_comment|/* 1001 -&gt;  7.0x */
l_int|80
comma
multiline_comment|/* 1010 -&gt;  8.0x */
l_int|50
comma
multiline_comment|/* 1011 -&gt;  5.0x */
l_int|65
comma
multiline_comment|/* 1100 -&gt;  6.5x */
l_int|75
comma
multiline_comment|/* 1101 -&gt;  7.5x */
l_int|85
comma
multiline_comment|/* 1110 -&gt;  8.5x */
l_int|120
comma
multiline_comment|/* 1111 -&gt;  12.0x */
op_minus
l_int|1
comma
multiline_comment|/* 0000 -&gt; RESERVED (10.0x) */
l_int|110
comma
multiline_comment|/* 0001 -&gt; 11.0x */
l_int|120
comma
multiline_comment|/* 0010 -&gt; 12.0x */
op_minus
l_int|1
comma
multiline_comment|/* 0011 -&gt; RESERVED (9.0x)*/
l_int|105
comma
multiline_comment|/* 0100 -&gt; 10.5x */
l_int|115
comma
multiline_comment|/* 0101 -&gt; 11.5x */
l_int|125
comma
multiline_comment|/* 0110 -&gt; 12.5x */
l_int|135
comma
multiline_comment|/* 0111 -&gt; 13.5x */
l_int|140
comma
multiline_comment|/* 1000 -&gt; 14.0x */
l_int|150
comma
multiline_comment|/* 1001 -&gt; 15.0x */
l_int|160
comma
multiline_comment|/* 1010 -&gt; 16.0x */
l_int|130
comma
multiline_comment|/* 1011 -&gt; 13.0x */
l_int|145
comma
multiline_comment|/* 1100 -&gt; 14.5x */
l_int|155
comma
multiline_comment|/* 1101 -&gt; 15.5x */
op_minus
l_int|1
comma
multiline_comment|/* 1110 -&gt; RESERVED (13.0x) */
op_minus
l_int|1
comma
multiline_comment|/* 1111 -&gt; RESERVED (12.0x) */
)brace
suffix:semicolon
DECL|variable|c5m_eblcr
r_static
r_int
id|__initdata
id|c5m_eblcr
(braket
l_int|32
)braket
op_assign
(brace
l_int|50
comma
multiline_comment|/* 0000 -&gt;  5.0x */
l_int|30
comma
multiline_comment|/* 0001 -&gt;  3.0x */
l_int|40
comma
multiline_comment|/* 0010 -&gt;  4.0x */
l_int|100
comma
multiline_comment|/* 0011 -&gt; 10.0x */
l_int|55
comma
multiline_comment|/* 0100 -&gt;  5.5x */
l_int|35
comma
multiline_comment|/* 0101 -&gt;  3.5x */
l_int|45
comma
multiline_comment|/* 0110 -&gt;  4.5x */
l_int|95
comma
multiline_comment|/* 0111 -&gt;  9.5x */
l_int|90
comma
multiline_comment|/* 1000 -&gt;  9.0x */
l_int|70
comma
multiline_comment|/* 1001 -&gt;  7.0x */
l_int|80
comma
multiline_comment|/* 1010 -&gt;  8.0x */
l_int|60
comma
multiline_comment|/* 1011 -&gt;  6.0x */
l_int|120
comma
multiline_comment|/* 1100 -&gt; 12.0x */
l_int|75
comma
multiline_comment|/* 1101 -&gt;  7.5x */
l_int|85
comma
multiline_comment|/* 1110 -&gt;  8.5x */
l_int|65
comma
multiline_comment|/* 1111 -&gt;  6.5x */
op_minus
l_int|1
comma
multiline_comment|/* 0000 -&gt; RESERVED (9.0x) */
l_int|110
comma
multiline_comment|/* 0001 -&gt; 11.0x */
l_int|120
comma
multiline_comment|/* 0010 -&gt; 12.0x */
op_minus
l_int|1
comma
multiline_comment|/* 0011 -&gt; RESERVED (10.0x)*/
l_int|135
comma
multiline_comment|/* 0100 -&gt; 13.5x */
l_int|115
comma
multiline_comment|/* 0101 -&gt; 11.5x */
l_int|125
comma
multiline_comment|/* 0110 -&gt; 12.5x */
l_int|105
comma
multiline_comment|/* 0111 -&gt; 10.5x */
l_int|130
comma
multiline_comment|/* 1000 -&gt; 13.0x */
l_int|150
comma
multiline_comment|/* 1001 -&gt; 15.0x */
l_int|160
comma
multiline_comment|/* 1010 -&gt; 16.0x */
l_int|140
comma
multiline_comment|/* 1011 -&gt; 14.0x */
op_minus
l_int|1
comma
multiline_comment|/* 1100 -&gt; RESERVED (12.0x) */
l_int|155
comma
multiline_comment|/* 1101 -&gt; 15.5x */
op_minus
l_int|1
comma
multiline_comment|/* 1110 -&gt; RESERVED (13.0x) */
l_int|145
comma
multiline_comment|/* 1111 -&gt; 14.5x */
)brace
suffix:semicolon
multiline_comment|/* &n; * Voltage scales. Div/Mod by 1000 to get actual voltage.&n; * Which scale to use depends on the VRM type in use.&n; */
DECL|variable|vrm85scales
r_static
r_int
id|__initdata
id|vrm85scales
(braket
l_int|32
)braket
op_assign
(brace
l_int|1250
comma
l_int|1200
comma
l_int|1150
comma
l_int|1100
comma
l_int|1050
comma
l_int|1800
comma
l_int|1750
comma
l_int|1700
comma
l_int|1650
comma
l_int|1600
comma
l_int|1550
comma
l_int|1500
comma
l_int|1450
comma
l_int|1400
comma
l_int|1350
comma
l_int|1300
comma
l_int|1275
comma
l_int|1225
comma
l_int|1175
comma
l_int|1125
comma
l_int|1075
comma
l_int|1825
comma
l_int|1775
comma
l_int|1725
comma
l_int|1675
comma
l_int|1625
comma
l_int|1575
comma
l_int|1525
comma
l_int|1475
comma
l_int|1425
comma
l_int|1375
comma
l_int|1325
comma
)brace
suffix:semicolon
DECL|variable|mobilevrmscales
r_static
r_int
id|__initdata
id|mobilevrmscales
(braket
l_int|32
)braket
op_assign
(brace
l_int|2000
comma
l_int|1950
comma
l_int|1900
comma
l_int|1850
comma
l_int|1800
comma
l_int|1750
comma
l_int|1700
comma
l_int|1650
comma
l_int|1600
comma
l_int|1550
comma
l_int|1500
comma
l_int|1450
comma
l_int|1500
comma
l_int|1350
comma
l_int|1300
comma
op_minus
l_int|1
comma
l_int|1275
comma
l_int|1250
comma
l_int|1225
comma
l_int|1200
comma
l_int|1175
comma
l_int|1150
comma
l_int|1125
comma
l_int|1100
comma
l_int|1075
comma
l_int|1050
comma
l_int|1025
comma
l_int|1000
comma
l_int|975
comma
l_int|950
comma
l_int|925
comma
op_minus
l_int|1
comma
)brace
suffix:semicolon
eof
