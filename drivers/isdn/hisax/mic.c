multiline_comment|/* $Id: mic.c,v 1.10.6.2 2001/09/23 22:24:50 kai Exp $&n; *&n; * low level stuff for mic cards&n; *&n; * Author       Stephan von Krawczynski&n; * Copyright    by Stephan von Krawczynski &lt;skraw@ithnet.com&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;hscx.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
r_extern
r_const
r_char
op_star
id|CardType
(braket
)braket
suffix:semicolon
DECL|variable|mic_revision
r_const
r_char
op_star
id|mic_revision
op_assign
l_string|&quot;$Revision: 1.10.6.2 $&quot;
suffix:semicolon
DECL|macro|byteout
mdefine_line|#define byteout(addr,val) outb(val,addr)
DECL|macro|bytein
mdefine_line|#define bytein(addr) inb(addr)
DECL|macro|MIC_ISAC
mdefine_line|#define MIC_ISAC&t;2
DECL|macro|MIC_HSCX
mdefine_line|#define MIC_HSCX&t;1
DECL|macro|MIC_ADR
mdefine_line|#define MIC_ADR&t;&t;7
multiline_comment|/* CARD_ADR (Write) */
DECL|macro|MIC_RESET
mdefine_line|#define MIC_RESET      0x3&t;/* same as DOS driver */
r_static
r_inline
id|u_char
DECL|function|readreg
id|readreg
c_func
(paren
r_int
r_int
id|ale
comma
r_int
r_int
id|adr
comma
id|u_char
id|off
)paren
(brace
r_register
id|u_char
id|ret
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|ale
comma
id|off
)paren
suffix:semicolon
id|ret
op_assign
id|bytein
c_func
(paren
id|adr
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|readfifo
id|readfifo
c_func
(paren
r_int
r_int
id|ale
comma
r_int
r_int
id|adr
comma
id|u_char
id|off
comma
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
multiline_comment|/* fifo read without cli because it&squot;s allready done  */
id|byteout
c_func
(paren
id|ale
comma
id|off
)paren
suffix:semicolon
id|insb
c_func
(paren
id|adr
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|writereg
id|writereg
c_func
(paren
r_int
r_int
id|ale
comma
r_int
r_int
id|adr
comma
id|u_char
id|off
comma
id|u_char
id|data
)paren
(brace
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|ale
comma
id|off
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|adr
comma
id|data
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|writefifo
id|writefifo
c_func
(paren
r_int
r_int
id|ale
comma
r_int
r_int
id|adr
comma
id|u_char
id|off
comma
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
multiline_comment|/* fifo write without cli because it&squot;s allready done  */
id|byteout
c_func
(paren
id|ale
comma
id|off
)paren
suffix:semicolon
id|outsb
c_func
(paren
id|adr
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
multiline_comment|/* Interface functions */
r_static
id|u_char
DECL|function|ReadISAC
id|ReadISAC
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
id|offset
)paren
(brace
r_return
(paren
id|readreg
c_func
(paren
id|cs-&gt;hw.mic.adr
comma
id|cs-&gt;hw.mic.isac
comma
id|offset
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|WriteISAC
id|WriteISAC
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
id|offset
comma
id|u_char
id|value
)paren
(brace
id|writereg
c_func
(paren
id|cs-&gt;hw.mic.adr
comma
id|cs-&gt;hw.mic.isac
comma
id|offset
comma
id|value
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|ReadISACfifo
id|ReadISACfifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|readfifo
c_func
(paren
id|cs-&gt;hw.mic.adr
comma
id|cs-&gt;hw.mic.isac
comma
l_int|0
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|WriteISACfifo
id|WriteISACfifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|writefifo
c_func
(paren
id|cs-&gt;hw.mic.adr
comma
id|cs-&gt;hw.mic.isac
comma
l_int|0
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
r_static
id|u_char
DECL|function|ReadHSCX
id|ReadHSCX
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|hscx
comma
id|u_char
id|offset
)paren
(brace
r_return
(paren
id|readreg
c_func
(paren
id|cs-&gt;hw.mic.adr
comma
id|cs-&gt;hw.mic.hscx
comma
id|offset
op_plus
(paren
id|hscx
ques
c_cond
l_int|0x40
suffix:colon
l_int|0
)paren
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|WriteHSCX
id|WriteHSCX
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|hscx
comma
id|u_char
id|offset
comma
id|u_char
id|value
)paren
(brace
id|writereg
c_func
(paren
id|cs-&gt;hw.mic.adr
comma
id|cs-&gt;hw.mic.hscx
comma
id|offset
op_plus
(paren
id|hscx
ques
c_cond
l_int|0x40
suffix:colon
l_int|0
)paren
comma
id|value
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * fast interrupt HSCX stuff goes here&n; */
DECL|macro|READHSCX
mdefine_line|#define READHSCX(cs, nr, reg) readreg(cs-&gt;hw.mic.adr, &bslash;&n;&t;&t;cs-&gt;hw.mic.hscx, reg + (nr ? 0x40 : 0))
DECL|macro|WRITEHSCX
mdefine_line|#define WRITEHSCX(cs, nr, reg, data) writereg(cs-&gt;hw.mic.adr, &bslash;&n;&t;&t;cs-&gt;hw.mic.hscx, reg + (nr ? 0x40 : 0), data)
DECL|macro|READHSCXFIFO
mdefine_line|#define READHSCXFIFO(cs, nr, ptr, cnt) readfifo(cs-&gt;hw.mic.adr, &bslash;&n;&t;&t;cs-&gt;hw.mic.hscx, (nr ? 0x40 : 0), ptr, cnt)
DECL|macro|WRITEHSCXFIFO
mdefine_line|#define WRITEHSCXFIFO(cs, nr, ptr, cnt) writefifo(cs-&gt;hw.mic.adr, &bslash;&n;&t;&t;cs-&gt;hw.mic.hscx, (nr ? 0x40 : 0), ptr, cnt)
macro_line|#include &quot;hscx_irq.c&quot;
r_static
r_void
DECL|function|mic_interrupt
id|mic_interrupt
c_func
(paren
r_int
id|intno
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|dev_id
suffix:semicolon
id|u_char
id|val
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cs
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mic: Spurious interrupt!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|val
op_assign
id|readreg
c_func
(paren
id|cs-&gt;hw.mic.adr
comma
id|cs-&gt;hw.mic.hscx
comma
id|HSCX_ISTA
op_plus
l_int|0x40
)paren
suffix:semicolon
id|Start_HSCX
suffix:colon
r_if
c_cond
(paren
id|val
)paren
id|hscx_int_main
c_func
(paren
id|cs
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
id|readreg
c_func
(paren
id|cs-&gt;hw.mic.adr
comma
id|cs-&gt;hw.mic.isac
comma
id|ISAC_ISTA
)paren
suffix:semicolon
id|Start_ISAC
suffix:colon
r_if
c_cond
(paren
id|val
)paren
id|isac_interrupt
c_func
(paren
id|cs
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
id|readreg
c_func
(paren
id|cs-&gt;hw.mic.adr
comma
id|cs-&gt;hw.mic.hscx
comma
id|HSCX_ISTA
op_plus
l_int|0x40
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX IntStat after IntRoutine&quot;
)paren
suffix:semicolon
r_goto
id|Start_HSCX
suffix:semicolon
)brace
id|val
op_assign
id|readreg
c_func
(paren
id|cs-&gt;hw.mic.adr
comma
id|cs-&gt;hw.mic.isac
comma
id|ISAC_ISTA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_ISAC
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC IntStat after IntRoutine&quot;
)paren
suffix:semicolon
r_goto
id|Start_ISAC
suffix:semicolon
)brace
id|writereg
c_func
(paren
id|cs-&gt;hw.mic.adr
comma
id|cs-&gt;hw.mic.hscx
comma
id|HSCX_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.mic.adr
comma
id|cs-&gt;hw.mic.hscx
comma
id|HSCX_MASK
op_plus
l_int|0x40
comma
l_int|0xFF
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.mic.adr
comma
id|cs-&gt;hw.mic.isac
comma
id|ISAC_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.mic.adr
comma
id|cs-&gt;hw.mic.isac
comma
id|ISAC_MASK
comma
l_int|0x0
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.mic.adr
comma
id|cs-&gt;hw.mic.hscx
comma
id|HSCX_MASK
comma
l_int|0x0
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.mic.adr
comma
id|cs-&gt;hw.mic.hscx
comma
id|HSCX_MASK
op_plus
l_int|0x40
comma
l_int|0x0
)paren
suffix:semicolon
)brace
r_void
DECL|function|release_io_mic
id|release_io_mic
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_int
id|bytecnt
op_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;hw.mic.cfg_reg
)paren
id|release_region
c_func
(paren
id|cs-&gt;hw.mic.cfg_reg
comma
id|bytecnt
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|mic_card_msg
id|mic_card_msg
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|mt
comma
r_void
op_star
id|arg
)paren
(brace
r_switch
c_cond
(paren
id|mt
)paren
(brace
r_case
id|CARD_RESET
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|CARD_RELEASE
suffix:colon
id|release_io_mic
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|CARD_INIT
suffix:colon
id|inithscx
c_func
(paren
id|cs
)paren
suffix:semicolon
multiline_comment|/* /RTSA := ISAC RST */
id|inithscxisac
c_func
(paren
id|cs
comma
l_int|3
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|CARD_TEST
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
id|__init
DECL|function|setup_mic
id|setup_mic
c_func
(paren
r_struct
id|IsdnCard
op_star
id|card
)paren
(brace
r_int
id|bytecnt
suffix:semicolon
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|card-&gt;cs
suffix:semicolon
r_char
id|tmp
(braket
l_int|64
)braket
suffix:semicolon
id|strcpy
c_func
(paren
id|tmp
comma
id|mic_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: mic driver Rev. %s&bslash;n&quot;
comma
id|HiSax_getrev
c_func
(paren
id|tmp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;typ
op_ne
id|ISDN_CTYPE_MIC
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
id|bytecnt
op_assign
l_int|8
suffix:semicolon
id|cs-&gt;hw.mic.cfg_reg
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
suffix:semicolon
id|cs-&gt;irq
op_assign
id|card-&gt;para
(braket
l_int|0
)braket
suffix:semicolon
id|cs-&gt;hw.mic.adr
op_assign
id|cs-&gt;hw.mic.cfg_reg
op_plus
id|MIC_ADR
suffix:semicolon
id|cs-&gt;hw.mic.isac
op_assign
id|cs-&gt;hw.mic.cfg_reg
op_plus
id|MIC_ISAC
suffix:semicolon
id|cs-&gt;hw.mic.hscx
op_assign
id|cs-&gt;hw.mic.cfg_reg
op_plus
id|MIC_HSCX
suffix:semicolon
r_if
c_cond
(paren
id|check_region
c_func
(paren
(paren
id|cs-&gt;hw.mic.cfg_reg
)paren
comma
id|bytecnt
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s config port %x-%x already in use&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|cs-&gt;hw.mic.cfg_reg
comma
id|cs-&gt;hw.mic.cfg_reg
op_plus
id|bytecnt
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|request_region
c_func
(paren
id|cs-&gt;hw.mic.cfg_reg
comma
id|bytecnt
comma
l_string|&quot;mic isdn&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;mic: defined at 0x%x IRQ %d&bslash;n&quot;
comma
id|cs-&gt;hw.mic.cfg_reg
comma
id|cs-&gt;irq
)paren
suffix:semicolon
id|cs-&gt;readisac
op_assign
op_amp
id|ReadISAC
suffix:semicolon
id|cs-&gt;writeisac
op_assign
op_amp
id|WriteISAC
suffix:semicolon
id|cs-&gt;readisacfifo
op_assign
op_amp
id|ReadISACfifo
suffix:semicolon
id|cs-&gt;writeisacfifo
op_assign
op_amp
id|WriteISACfifo
suffix:semicolon
id|cs-&gt;BC_Read_Reg
op_assign
op_amp
id|ReadHSCX
suffix:semicolon
id|cs-&gt;BC_Write_Reg
op_assign
op_amp
id|WriteHSCX
suffix:semicolon
id|cs-&gt;BC_Send_Data
op_assign
op_amp
id|hscx_fill_fifo
suffix:semicolon
id|cs-&gt;cardmsg
op_assign
op_amp
id|mic_card_msg
suffix:semicolon
id|cs-&gt;irq_func
op_assign
op_amp
id|mic_interrupt
suffix:semicolon
id|ISACVersion
c_func
(paren
id|cs
comma
l_string|&quot;mic:&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|HscxVersion
c_func
(paren
id|cs
comma
l_string|&quot;mic:&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mic: wrong HSCX versions check IO address&bslash;n&quot;
)paren
suffix:semicolon
id|release_io_mic
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
eof
