multiline_comment|/* 2001/10/02&n; *&n; * gerdes_amd7930.h     Header-file included by&n; *                      gerdes_amd7930.c&n; *&n; * Author               Christoph Ersfeld &lt;info@formula-n.de&gt;&n; *                      Formula-n Europe AG (www.formula-n.com)&n; *                      previously Gerdes AG&n; *&n; *&n; *                      This file is (c) under GNU PUBLIC LICENSE&n; */
DECL|macro|BYTE
mdefine_line|#define BYTE&t;&t;&t;&t;&t;&t;&t;unsigned char
DECL|macro|WORD
mdefine_line|#define WORD&t;&t;&t;&t;&t;&t;&t;unsigned int
DECL|macro|rByteAMD
mdefine_line|#define rByteAMD(cs, reg)&t;&t;&t;&t;&t;cs-&gt;readisac(cs, reg)
DECL|macro|wByteAMD
mdefine_line|#define wByteAMD(cs, reg, val)&t;&t;&t;&t;&t;cs-&gt;writeisac(cs, reg, val)
DECL|macro|rWordAMD
mdefine_line|#define rWordAMD(cs, reg)&t;&t;&t;&t;&t;ReadWordAmd7930(cs, reg)
DECL|macro|wWordAMD
mdefine_line|#define wWordAMD(cs, reg, val)&t;&t;&t;&t;&t;WriteWordAmd7930(cs, reg, val)
DECL|macro|HIBYTE
mdefine_line|#define HIBYTE(w)&t;&t;&t;&t;&t;&t;((unsigned char)((w &amp; 0xff00) / 256))
DECL|macro|LOBYTE
mdefine_line|#define LOBYTE(w)&t;&t;&t;&t;&t;&t;((unsigned char)(w &amp; 0x00ff))
DECL|macro|AmdIrqOff
mdefine_line|#define AmdIrqOff(cs)&t;&t;&t;&t;&t;&t;cs-&gt;dc.amd7930.setIrqMask(cs, 0)
DECL|macro|AmdIrqOn
mdefine_line|#define AmdIrqOn(cs)&t;&t;&t;&t;&t;&t;cs-&gt;dc.amd7930.setIrqMask(cs, 1)
DECL|macro|AMD_CR
mdefine_line|#define AMD_CR&t;&t;0x00
DECL|macro|AMD_DR
mdefine_line|#define AMD_DR&t;&t;0x01
DECL|macro|DBUSY_TIMER_VALUE
mdefine_line|#define DBUSY_TIMER_VALUE 80
DECL|variable|initAMD
r_static
id|WORD
id|initAMD
(braket
)braket
op_assign
(brace
l_int|0x0100
comma
l_int|0x00A5
comma
l_int|3
comma
l_int|0x01
comma
l_int|0x40
comma
l_int|0x58
comma
singleline_comment|// LPR, LMR1, LMR2
l_int|0x0086
comma
l_int|1
comma
l_int|0x0B
comma
singleline_comment|// DMR1 (D-Buffer TH-Interrupts on)
l_int|0x0087
comma
l_int|1
comma
l_int|0xFF
comma
singleline_comment|// DMR2
l_int|0x0092
comma
l_int|1
comma
l_int|0x03
comma
singleline_comment|// EFCR (extended mode d-channel-fifo on)
l_int|0x0090
comma
l_int|4
comma
l_int|0xFE
comma
l_int|0xFF
comma
l_int|0x02
comma
l_int|0x0F
comma
singleline_comment|// FRAR4, SRAR4, DMR3, DMR4 (address recognition )
l_int|0x0084
comma
l_int|2
comma
l_int|0x80
comma
l_int|0x00
comma
singleline_comment|// DRLR
l_int|0x00C0
comma
l_int|1
comma
l_int|0x47
comma
singleline_comment|// PPCR1
l_int|0x00C8
comma
l_int|1
comma
l_int|0x01
comma
singleline_comment|// PPCR2
l_int|0x0102
comma
l_int|0x0107
comma
l_int|0x01A1
comma
l_int|1
comma
l_int|0x0121
comma
l_int|1
comma
l_int|0x0189
comma
l_int|2
comma
l_int|0x0045
comma
l_int|4
comma
l_int|0x61
comma
l_int|0x72
comma
l_int|0x00
comma
l_int|0x00
comma
singleline_comment|// MCR1, MCR2, MCR3, MCR4
l_int|0x0063
comma
l_int|2
comma
l_int|0x08
comma
l_int|0x08
comma
singleline_comment|// GX
l_int|0x0064
comma
l_int|2
comma
l_int|0x08
comma
l_int|0x08
comma
singleline_comment|// GR
l_int|0x0065
comma
l_int|2
comma
l_int|0x99
comma
l_int|0x00
comma
singleline_comment|// GER
l_int|0x0066
comma
l_int|2
comma
l_int|0x7C
comma
l_int|0x8B
comma
singleline_comment|// STG
l_int|0x0067
comma
l_int|2
comma
l_int|0x00
comma
l_int|0x00
comma
singleline_comment|// FTGR1, FTGR2
l_int|0x0068
comma
l_int|2
comma
l_int|0x20
comma
l_int|0x20
comma
singleline_comment|// ATGR1, ATGR2
l_int|0x0069
comma
l_int|1
comma
l_int|0x4F
comma
singleline_comment|// MMR1
l_int|0x006A
comma
l_int|1
comma
l_int|0x00
comma
singleline_comment|// MMR2
l_int|0x006C
comma
l_int|1
comma
l_int|0x40
comma
singleline_comment|// MMR3
l_int|0x0021
comma
l_int|1
comma
l_int|0x02
comma
singleline_comment|// INIT
l_int|0x00A3
comma
l_int|1
comma
l_int|0x40
comma
singleline_comment|// LMR1
l_int|0xFFFF
)brace
suffix:semicolon
r_extern
r_void
id|Amd7930_interrupt
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
r_char
id|irflags
)paren
suffix:semicolon
r_extern
r_void
id|Amd7930_init
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
eof
