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
r_extern
r_void
id|Amd7930_interrupt
c_func
(paren
r_struct
id|IsdnCardState
op_star
comma
r_int
r_char
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
)paren
suffix:semicolon
r_extern
r_void
id|setup_Amd7930
c_func
(paren
r_struct
id|IsdnCardState
op_star
)paren
suffix:semicolon
eof
