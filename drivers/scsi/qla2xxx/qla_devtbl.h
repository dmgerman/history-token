DECL|macro|QLA_MODEL_NAMES
mdefine_line|#define QLA_MODEL_NAMES         0x21
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
l_string|&quot;HPQSVS &quot;
comma
multiline_comment|/* 0x10f */
l_string|&quot;HPQSVS &quot;
comma
multiline_comment|/* 0x110 */
l_string|&quot;QLA4010&quot;
comma
multiline_comment|/* 0x111 */
l_string|&quot;QLA4010&quot;
comma
multiline_comment|/* 0x112 */
l_string|&quot;QLA4010C&quot;
comma
multiline_comment|/* 0x113 */
l_string|&quot;QLA4010C&quot;
comma
multiline_comment|/* 0x114 */
l_string|&quot;QLA2360&quot;
comma
multiline_comment|/* 0x115 */
l_string|&quot;QLA2362&quot;
comma
multiline_comment|/* 0x116 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x117 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x118 */
l_string|&quot;QLA200&quot;
comma
multiline_comment|/* 0x119 */
l_string|&quot;QLA200C&quot;
multiline_comment|/* 0x11A */
l_string|&quot;QLA200P&quot;
multiline_comment|/* 0x11B */
l_string|&quot;QLA200P&quot;
multiline_comment|/* 0x11C */
l_string|&quot;QLA4040&quot;
multiline_comment|/* 0x11D */
l_string|&quot;QLA4040&quot;
multiline_comment|/* 0x11E */
l_string|&quot;QLA4040C&quot;
multiline_comment|/* 0x11F */
l_string|&quot;QLA4040C&quot;
multiline_comment|/* 0x120 */
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
l_string|&quot;Optical- 133MHz to 1Gb iSCSI- networking&quot;
comma
multiline_comment|/* 0x111 */
l_string|&quot;Optical- 133MHz to 1Gb iSCSI- storage&quot;
comma
multiline_comment|/* 0x112 */
l_string|&quot;Copper- 133MHz to 1Gb iSCSI- networking&quot;
comma
multiline_comment|/* 0x113 */
l_string|&quot;Copper- 133MHz to 1Gb iSCSI- storage&quot;
comma
multiline_comment|/* 0x114 */
l_string|&quot;133MHz PCI-X to 2Gb FC Single Channel&quot;
comma
multiline_comment|/* 0x115 */
l_string|&quot;133MHz PCI-X to 2Gb FC Dual Channel&quot;
comma
multiline_comment|/* 0x116 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x117 */
l_string|&quot; &quot;
comma
multiline_comment|/* 0x118 */
l_string|&quot;133MHz PCI-X to 2Gb FC Optical&quot;
comma
multiline_comment|/* 0x119 */
l_string|&quot;133MHz PCI-X to 2Gb FC Copper&quot;
multiline_comment|/* 0x11A */
l_string|&quot;133MHz PCI-X to 2Gb FC SFP&quot;
multiline_comment|/* 0x11B */
l_string|&quot;133MHz PCI-X to 2Gb FC SFP&quot;
multiline_comment|/* 0x11C */
l_string|&quot;Optical- 133MHz to 1Gb NIC with IPSEC&quot;
comma
multiline_comment|/* 0x11D */
l_string|&quot;Optical- 133MHz to 1Gb iSCSI with IPSEC&quot;
comma
multiline_comment|/* 0x11E */
l_string|&quot;Copper- 133MHz to 1Gb NIC with IPSEC&quot;
comma
multiline_comment|/* 0x11F */
l_string|&quot;Copper- 133MHz to 1Gb iSCSI with IPSEC&quot;
comma
multiline_comment|/* 0x120 */
)brace
suffix:semicolon
eof
