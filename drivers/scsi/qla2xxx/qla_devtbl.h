DECL|macro|QLA_MODEL_NAMES
mdefine_line|#define QLA_MODEL_NAMES         0x32
multiline_comment|/*&n; * Adapter model names.&n; */
DECL|variable|qla2x00_model_name
r_static
r_char
op_star
id|qla2x00_model_name
(braket
id|QLA_MODEL_NAMES
)braket
op_assign
(brace
l_string|&quot;QLA2340&quot;
comma
multiline_comment|/* 0x100 */
l_string|&quot;QLA2342&quot;
comma
multiline_comment|/* 0x101 */
l_string|&quot;QLA2344&quot;
comma
multiline_comment|/* 0x102 */
l_string|&quot;QCP2342&quot;
comma
multiline_comment|/* 0x103 */
l_string|&quot;QSB2340&quot;
comma
multiline_comment|/* 0x104 */
l_string|&quot;QSB2342&quot;
comma
multiline_comment|/* 0x105 */
l_string|&quot;QLA2310&quot;
comma
multiline_comment|/* 0x106 */
l_string|&quot;QLA2332&quot;
comma
multiline_comment|/* 0x107 */
l_string|&quot;QCP2332&quot;
comma
multiline_comment|/* 0x108 */
l_string|&quot;QCP2340&quot;
comma
multiline_comment|/* 0x109 */
l_string|&quot;QLA2342&quot;
comma
multiline_comment|/* 0x10a */
l_string|&quot;QCP2342&quot;
comma
multiline_comment|/* 0x10b */
l_string|&quot;QLA2350&quot;
comma
multiline_comment|/* 0x10c */
l_string|&quot;QLA2352&quot;
comma
multiline_comment|/* 0x10d */
l_string|&quot;QLA2352&quot;
comma
multiline_comment|/* 0x10e */
l_string|&quot;HPQ SVS&quot;
comma
multiline_comment|/* 0x10f */
l_string|&quot;HPQ SVS&quot;
comma
multiline_comment|/* 0x110 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x111 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x112 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x113 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x114 */
l_string|&quot;QLA2360&quot;
comma
multiline_comment|/* 0x115 */
l_string|&quot;QLA2362&quot;
comma
multiline_comment|/* 0x116 */
l_string|&quot;QLE2360&quot;
comma
multiline_comment|/* 0x117 */
l_string|&quot;QLE2362&quot;
comma
multiline_comment|/* 0x118 */
l_string|&quot;QLA200&quot;
comma
multiline_comment|/* 0x119 */
l_string|&quot;QLA200C&quot;
comma
multiline_comment|/* 0x11a */
l_string|&quot;QLA200P&quot;
comma
multiline_comment|/* 0x11b */
l_string|&quot;QLA200P&quot;
comma
multiline_comment|/* 0x11c */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x11d */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x11e */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x11f */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x120 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x121 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x122 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x123 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x124 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x125 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x126 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x127 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x128 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x129 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x12a */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x12b */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x12c */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x12d */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x12e */
l_string|&quot;QLA210&quot;
comma
multiline_comment|/* 0x12f */
l_string|&quot;EMC 250&quot;
comma
multiline_comment|/* 0x130 */
l_string|&quot;HP A7538A&quot;
multiline_comment|/* 0x131 */
)brace
suffix:semicolon
DECL|variable|qla2x00_model_desc
r_static
r_char
op_star
id|qla2x00_model_desc
(braket
id|QLA_MODEL_NAMES
)braket
op_assign
(brace
l_string|&quot;133MHz PCI-X to 2Gb FC, Single Channel&quot;
comma
multiline_comment|/* 0x100 */
l_string|&quot;133MHz PCI-X to 2Gb FC, Dual Channel&quot;
comma
multiline_comment|/* 0x101 */
l_string|&quot;133MHz PCI-X to 2Gb FC, Quad Channel&quot;
comma
multiline_comment|/* 0x102 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x103 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x104 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x105 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x106 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x107 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x108 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x109 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x10a */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x10b */
l_string|&quot;133MHz PCI-X to 2Gb FC, Single Channel&quot;
comma
multiline_comment|/* 0x10c */
l_string|&quot;133MHz PCI-X to 2Gb FC, Dual Channel&quot;
comma
multiline_comment|/* 0x10d */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x10e */
l_string|&quot;HPQ SVS HBA- Initiator device&quot;
comma
multiline_comment|/* 0x10f */
l_string|&quot;HPQ SVS HBA- Target device&quot;
comma
multiline_comment|/* 0x110 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x111 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x112 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x113 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x114 */
l_string|&quot;133MHz PCI-X to 2Gb FC Single Channel&quot;
comma
multiline_comment|/* 0x115 */
l_string|&quot;133MHz PCI-X to 2Gb FC Dual Channel&quot;
comma
multiline_comment|/* 0x116 */
l_string|&quot;PCI-Express to 2Gb FC, Single Channel&quot;
comma
multiline_comment|/* 0x117 */
l_string|&quot;PCI-Express to 2Gb FC, Dual Channel&quot;
comma
multiline_comment|/* 0x118 */
l_string|&quot;133MHz PCI-X to 2Gb FC Optical&quot;
comma
multiline_comment|/* 0x119 */
l_string|&quot;133MHz PCI-X to 2Gb FC Copper&quot;
comma
multiline_comment|/* 0x11a */
l_string|&quot;133MHz PCI-X to 2Gb FC SFP&quot;
comma
multiline_comment|/* 0x11b */
l_string|&quot;133MHz PCI-X to 2Gb FC SFP&quot;
comma
multiline_comment|/* 0x11c */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x11d */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x11e */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x11f */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x120 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x121 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x122 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x123 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x124 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x125 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x126 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x127 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x128 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x129 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x12a */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x12b */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x12c */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x12d */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x12e */
l_string|&quot;133MHz PCI-X to 2Gb FC SFF&quot;
comma
multiline_comment|/* 0x12f */
l_string|&quot;133MHz PCI-X to 2Gb FC SFF&quot;
comma
multiline_comment|/* 0x130 */
l_string|&quot;HP 1p2g QLA2340&quot;
multiline_comment|/* 0x131 */
)brace
suffix:semicolon
eof
