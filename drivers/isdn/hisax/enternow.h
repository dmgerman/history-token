multiline_comment|/* 2001/10/02&n; *&n; * enternow.h   Header-file included by&n; *              enternow_pci.c&n; *&n; * Author       Christoph Ersfeld &lt;info@formula-n.de&gt;&n; *              Formula-n Europe AG (www.formula-n.com)&n; *              previously Gerdes AG&n; *&n; *&n; *              This file is (c) under GNU PUBLIC LICENSE&n; */
multiline_comment|/* ***************************************************************************************** *&n; * ****************************** datatypes and macros ************************************* *&n; * ***************************************************************************************** */
DECL|macro|BYTE
mdefine_line|#define BYTE&t;&t;&t;&t;&t;&t;&t;unsigned char
DECL|macro|WORD
mdefine_line|#define WORD&t;&t;&t;&t;&t;&t;&t;unsigned int
DECL|macro|HIBYTE
mdefine_line|#define HIBYTE(w)&t;&t;&t;&t;&t;&t;((unsigned char)((w &amp; 0xff00) / 256))
DECL|macro|LOBYTE
mdefine_line|#define LOBYTE(w)&t;&t;&t;&t;&t;&t;((unsigned char)(w &amp; 0x00ff))
DECL|macro|InByte
mdefine_line|#define InByte(addr)&t;&t;&t;&t;&t;&t;inb(addr)
DECL|macro|OutByte
mdefine_line|#define OutByte(addr,val)&t;&t;&t;&t;&t;outb(val,addr)
multiline_comment|/* ***************************************************************************************** *&n; * *********************************** card-specific *************************************** *&n; * ***************************************************************************************** */
multiline_comment|/* f&#xfffd;r PowerISDN PCI */
DECL|macro|TJ_AMD_IRQ
mdefine_line|#define TJ_AMD_IRQ &t;&t;&t;&t;&t;&t;0x20
DECL|macro|TJ_LED1
mdefine_line|#define TJ_LED1 &t;&t;&t;&t;&t;&t;0x40
DECL|macro|TJ_LED2
mdefine_line|#define TJ_LED2 &t;&t;&t;&t;&t;&t;0x80
multiline_comment|/* Das Fenster zum AMD...&n; * Ab Adresse hw.njet.base + TJ_AMD_PORT werden vom AMD jeweils 8 Bit in&n; * den TigerJet i/o-Raum gemappt&n; * -&gt; 0x01 des AMD bei hw.njet.base + 0C4 */
DECL|macro|TJ_AMD_PORT
mdefine_line|#define TJ_AMD_PORT&t;&t;&t;&t;&t;&t;0xC0
multiline_comment|/* ***************************************************************************************** *&n; * *************************************** Prototypen ************************************** *&n; * ***************************************************************************************** */
id|BYTE
id|ReadByteAmd7930
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|BYTE
id|offset
)paren
suffix:semicolon
r_void
id|WriteByteAmd7930
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|BYTE
id|offset
comma
id|BYTE
id|value
)paren
suffix:semicolon
eof
