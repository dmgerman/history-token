multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;IT8172 Consumer IR port defines.&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
DECL|macro|NUM_CIR_PORTS
mdefine_line|#define NUM_CIR_PORTS 2
multiline_comment|/* Master Control Register */
DECL|macro|CIR_RESET
mdefine_line|#define CIR_RESET              0x1
DECL|macro|CIR_FIFO_CLEAR
mdefine_line|#define CIR_FIFO_CLEAR         0x2
DECL|macro|CIR_SET_FIFO_TL
mdefine_line|#define CIR_SET_FIFO_TL(x)     (((x)&amp;0x3)&lt;&lt;2)
DECL|macro|CIR_ILE
mdefine_line|#define CIR_ILE                0x10
DECL|macro|CIR_ILSEL
mdefine_line|#define CIR_ILSEL              0x20
multiline_comment|/* Interrupt Enable Register */
DECL|macro|CIR_TLDLIE
mdefine_line|#define CIR_TLDLIE             0x1
DECL|macro|CIR_RDAIE
mdefine_line|#define CIR_RDAIE              0x2
DECL|macro|CIR_RFOIE
mdefine_line|#define CIR_RFOIE              0x4
DECL|macro|CIR_IEC
mdefine_line|#define CIR_IEC                0x80
multiline_comment|/* Interrupt Identification Register */
DECL|macro|CIR_TLDLI
mdefine_line|#define CIR_TLDLI              0x1
DECL|macro|CIR_RDAI
mdefine_line|#define CIR_RDAI               0x2
DECL|macro|CIR_RFOI
mdefine_line|#define CIR_RFOI               0x4
DECL|macro|CIR_NIP
mdefine_line|#define CIR_NIP                0x80
multiline_comment|/* Carrier Frequency Register */
DECL|macro|CIR_SET_CF
mdefine_line|#define CIR_SET_CF(x)          ((x)&amp;0x1f)
DECL|macro|CFQ_38_480
mdefine_line|#define CFQ_38_480           0xB       /* 38 KHz low, 480 KHz high */
DECL|macro|CIR_HCFS
mdefine_line|#define CIR_HCFS               0x20
DECL|macro|CIR_SET_HS
mdefine_line|#define CIR_SET_HS(x)        (((x)&amp;0x1)&lt;&lt;5)
multiline_comment|/* Receiver Control Register */
DECL|macro|CIR_SET_RXDCR
mdefine_line|#define CIR_SET_RXDCR(x)       ((x)&amp;0x7)
DECL|macro|CIR_RXACT
mdefine_line|#define CIR_RXACT              0x8
DECL|macro|CIR_RXEND
mdefine_line|#define CIR_RXEND              0x10
DECL|macro|CIR_RDWOS
mdefine_line|#define CIR_RDWOS              0x20
DECL|macro|CIR_SET_RDWOS
mdefine_line|#define CIR_SET_RDWOS(x)     (((x)&amp;0x1)&lt;&lt;5)
DECL|macro|CIR_RXEN
mdefine_line|#define CIR_RXEN               0x80
multiline_comment|/* Transmitter Control Register */
DECL|macro|CIR_SET_TXMPW
mdefine_line|#define CIR_SET_TXMPW(x)       ((x)&amp;0x7)
DECL|macro|CIR_SET_TXMPM
mdefine_line|#define CIR_SET_TXMPM(x)       (((x)&amp;0x3)&lt;&lt;3)
DECL|macro|CIR_TXENDF
mdefine_line|#define CIR_TXENDF             0x20
DECL|macro|CIR_TXRLE
mdefine_line|#define CIR_TXRLE              0x40
multiline_comment|/* Receiver FIFO Status Register */
DECL|macro|CIR_RXFBC_MASK
mdefine_line|#define CIR_RXFBC_MASK         0x3f
DECL|macro|CIR_RXFTO
mdefine_line|#define CIR_RXFTO              0x80
multiline_comment|/* Wakeup Code Length Register */
DECL|macro|CIR_SET_WCL
mdefine_line|#define CIR_SET_WCL            ((x)&amp;0x3f)
DECL|macro|CIR_WCL_MASK
mdefine_line|#define CIR_WCL_MASK(x)        ((x)&amp;0x3f)
multiline_comment|/* Wakeup Power Control/Status Register */
DECL|macro|CIR_BTMON
mdefine_line|#define CIR_BTMON              0x2
DECL|macro|CIR_CIRON
mdefine_line|#define CIR_CIRON              0x4
DECL|macro|CIR_RCRST
mdefine_line|#define CIR_RCRST              0x10
DECL|macro|CIR_WCRST
mdefine_line|#define CIR_WCRST              0x20
DECL|struct|cir_port
r_struct
id|cir_port
(brace
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|baud_rate
r_int
r_int
id|baud_rate
suffix:semicolon
DECL|member|fifo_tl
r_int
r_char
id|fifo_tl
suffix:semicolon
DECL|member|cfq
r_int
r_char
id|cfq
suffix:semicolon
DECL|member|hcfs
r_int
r_char
id|hcfs
suffix:semicolon
DECL|member|rdwos
r_int
r_char
id|rdwos
suffix:semicolon
DECL|member|rxdcr
r_int
r_char
id|rxdcr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|it8172_cir_regs
r_struct
id|it8172_cir_regs
(brace
DECL|member|dr
r_int
r_char
id|dr
suffix:semicolon
multiline_comment|/* data                        */
DECL|member|pad
r_char
id|pad
suffix:semicolon
DECL|member|mstcr
r_int
r_char
id|mstcr
suffix:semicolon
multiline_comment|/* master control              */
DECL|member|pad1
r_char
id|pad1
suffix:semicolon
DECL|member|ier
r_int
r_char
id|ier
suffix:semicolon
multiline_comment|/* interrupt enable            */
DECL|member|pad2
r_char
id|pad2
suffix:semicolon
DECL|member|iir
r_int
r_char
id|iir
suffix:semicolon
multiline_comment|/* interrupt identification    */
DECL|member|pad3
r_char
id|pad3
suffix:semicolon
DECL|member|cfr
r_int
r_char
id|cfr
suffix:semicolon
multiline_comment|/* carrier frequency           */
DECL|member|pad4
r_char
id|pad4
suffix:semicolon
DECL|member|rcr
r_int
r_char
id|rcr
suffix:semicolon
multiline_comment|/* receiver control            */
DECL|member|pad5
r_char
id|pad5
suffix:semicolon
DECL|member|tcr
r_int
r_char
id|tcr
suffix:semicolon
multiline_comment|/* transmitter control         */
DECL|member|pad6
r_char
id|pad6
suffix:semicolon
DECL|member|pad7
r_char
id|pad7
suffix:semicolon
DECL|member|pad8
r_char
id|pad8
suffix:semicolon
DECL|member|bdlr
r_int
r_char
id|bdlr
suffix:semicolon
multiline_comment|/* baud rate divisor low byte  */
DECL|member|pad9
r_char
id|pad9
suffix:semicolon
DECL|member|bdhr
r_int
r_char
id|bdhr
suffix:semicolon
multiline_comment|/* baud rate divisor high byte */
DECL|member|pad10
r_char
id|pad10
suffix:semicolon
DECL|member|tfsr
r_int
r_char
id|tfsr
suffix:semicolon
multiline_comment|/* tx fifo byte count          */
DECL|member|pad11
r_char
id|pad11
suffix:semicolon
DECL|member|rfsr
r_int
r_char
id|rfsr
suffix:semicolon
multiline_comment|/* rx fifo status              */
DECL|member|pad12
r_char
id|pad12
suffix:semicolon
DECL|member|wcl
r_int
r_char
id|wcl
suffix:semicolon
multiline_comment|/* wakeup code length          */
DECL|member|pad13
r_char
id|pad13
suffix:semicolon
DECL|member|wcr
r_int
r_char
id|wcr
suffix:semicolon
multiline_comment|/* wakeup code read/write      */
DECL|member|pad14
r_char
id|pad14
suffix:semicolon
DECL|member|wps
r_int
r_char
id|wps
suffix:semicolon
multiline_comment|/* wakeup power control/status */
)brace
suffix:semicolon
r_int
id|cir_port_init
c_func
(paren
r_struct
id|cir_port
op_star
id|cir
)paren
suffix:semicolon
r_extern
r_void
id|clear_fifo
c_func
(paren
r_struct
id|cir_port
op_star
id|cir
)paren
suffix:semicolon
r_extern
r_void
id|enable_receiver
c_func
(paren
r_struct
id|cir_port
op_star
id|cir
)paren
suffix:semicolon
r_extern
r_void
id|disable_receiver
c_func
(paren
r_struct
id|cir_port
op_star
id|cir
)paren
suffix:semicolon
r_extern
r_void
id|enable_rx_demodulation
c_func
(paren
r_struct
id|cir_port
op_star
id|cir
)paren
suffix:semicolon
r_extern
r_void
id|disable_rx_demodulation
c_func
(paren
r_struct
id|cir_port
op_star
id|cir
)paren
suffix:semicolon
r_extern
r_void
id|set_rx_active
c_func
(paren
r_struct
id|cir_port
op_star
id|cir
)paren
suffix:semicolon
r_extern
r_void
id|int_enable
c_func
(paren
r_struct
id|cir_port
op_star
id|cir
)paren
suffix:semicolon
r_extern
r_void
id|rx_int_enable
c_func
(paren
r_struct
id|cir_port
op_star
id|cir
)paren
suffix:semicolon
r_extern
r_char
id|get_int_status
c_func
(paren
r_struct
id|cir_port
op_star
id|cir
)paren
suffix:semicolon
r_extern
r_int
id|cir_get_rx_count
c_func
(paren
r_struct
id|cir_port
op_star
id|cir
)paren
suffix:semicolon
r_extern
r_char
id|cir_read_data
c_func
(paren
r_struct
id|cir_port
op_star
id|cir
)paren
suffix:semicolon
eof
