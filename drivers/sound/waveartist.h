multiline_comment|/*&n; * linux/drivers/sound/waveartist.h&n; *&n; * def file for Rockwell RWA010 chip set, as installed in Rebel.com NetWinder&n; */
singleline_comment|//registers
DECL|macro|CMDR
mdefine_line|#define CMDR&t;0
DECL|macro|DATR
mdefine_line|#define DATR&t;2
DECL|macro|CTLR
mdefine_line|#define CTLR&t;4
DECL|macro|STATR
mdefine_line|#define&t;STATR&t;5
DECL|macro|IRQSTAT
mdefine_line|#define&t;IRQSTAT&t;12
singleline_comment|//bit defs
singleline_comment|//reg STATR
DECL|macro|CMD_WE
mdefine_line|#define&t;CMD_WE&t;0x80
DECL|macro|CMD_RF
mdefine_line|#define&t;CMD_RF&t;0x40
DECL|macro|DAT_WE
mdefine_line|#define&t;DAT_WE&t;0x20
DECL|macro|DAT_RF
mdefine_line|#define&t;DAT_RF&t;0x10
DECL|macro|IRQ_REQ
mdefine_line|#define&t;IRQ_REQ&t;0x08
DECL|macro|DMA1
mdefine_line|#define&t;DMA1&t;0x04
DECL|macro|DMA0
mdefine_line|#define&t;DMA0&t;0x02
singleline_comment|//bit defs
singleline_comment|//reg CTLR
DECL|macro|CMD_WEIE
mdefine_line|#define&t;CMD_WEIE&t;0x80
DECL|macro|CMD_RFIE
mdefine_line|#define&t;CMD_RFIE&t;0x40
DECL|macro|DAT_WEIE
mdefine_line|#define&t;DAT_WEIE&t;0x20
DECL|macro|DAT_RFIE
mdefine_line|#define&t;DAT_RFIE&t;0x10
DECL|macro|RESET
mdefine_line|#define&t;RESET&t;0x08
DECL|macro|DMA1_IE
mdefine_line|#define&t;DMA1_IE&t;0x04
DECL|macro|DMA0_IE
mdefine_line|#define&t;DMA0_IE&t;0x02
DECL|macro|IRQ_ACK
mdefine_line|#define&t;IRQ_ACK&t;0x01
singleline_comment|//commands
DECL|macro|WACMD_SYSTEMID
mdefine_line|#define&t;WACMD_SYSTEMID&t;&t;0x00
DECL|macro|WACMD_GETREV
mdefine_line|#define WACMD_GETREV&t;&t;0x00
DECL|macro|WACMD_INPUTFORMAT
mdefine_line|#define&t;WACMD_INPUTFORMAT&t;0x10&t;
singleline_comment|//0-8S, 1-16S, 2-8U
DECL|macro|WACMD_INPUTCHANNELS
mdefine_line|#define&t;WACMD_INPUTCHANNELS&t;0x11&t;
singleline_comment|//1-Mono, 2-Stereo
DECL|macro|WACMD_INPUTSPEED
mdefine_line|#define&t;WACMD_INPUTSPEED&t;0x12&t;
singleline_comment|//sampling rate
DECL|macro|WACMD_INPUTDMA
mdefine_line|#define&t;WACMD_INPUTDMA&t;&t;0x13&t;
singleline_comment|//0-8bit, 1-16bit, 2-PIO
DECL|macro|WACMD_INPUTSIZE
mdefine_line|#define&t;WACMD_INPUTSIZE&t;&t;0x14&t;
singleline_comment|//samples to interrupt
DECL|macro|WACMD_INPUTSTART
mdefine_line|#define&t;WACMD_INPUTSTART&t;0x15&t;
singleline_comment|//start ADC
DECL|macro|WACMD_INPUTPAUSE
mdefine_line|#define&t;WACMD_INPUTPAUSE&t;0x16&t;
singleline_comment|//pause ADC
DECL|macro|WACMD_INPUTSTOP
mdefine_line|#define&t;WACMD_INPUTSTOP&t;&t;0x17&t;
singleline_comment|//stop ADC
DECL|macro|WACMD_INPUTRESUME
mdefine_line|#define&t;WACMD_INPUTRESUME&t;0x18&t;
singleline_comment|//resume ADC
DECL|macro|WACMD_INPUTPIO
mdefine_line|#define&t;WACMD_INPUTPIO&t;&t;0x19&t;
singleline_comment|//PIO ADC
DECL|macro|WACMD_OUTPUTFORMAT
mdefine_line|#define&t;WACMD_OUTPUTFORMAT&t;0x20&t;
singleline_comment|//0-8S, 1-16S, 2-8U
DECL|macro|WACMD_OUTPUTCHANNELS
mdefine_line|#define&t;WACMD_OUTPUTCHANNELS&t;0x21&t;
singleline_comment|//1-Mono, 2-Stereo
DECL|macro|WACMD_OUTPUTSPEED
mdefine_line|#define&t;WACMD_OUTPUTSPEED&t;0x22&t;
singleline_comment|//sampling rate
DECL|macro|WACMD_OUTPUTDMA
mdefine_line|#define&t;WACMD_OUTPUTDMA&t;&t;0x23&t;
singleline_comment|//0-8bit, 1-16bit, 2-PIO
DECL|macro|WACMD_OUTPUTSIZE
mdefine_line|#define&t;WACMD_OUTPUTSIZE&t;0x24&t;
singleline_comment|//samples to interrupt
DECL|macro|WACMD_OUTPUTSTART
mdefine_line|#define&t;WACMD_OUTPUTSTART&t;0x25&t;
singleline_comment|//start ADC
DECL|macro|WACMD_OUTPUTPAUSE
mdefine_line|#define&t;WACMD_OUTPUTPAUSE&t;0x26&t;
singleline_comment|//pause ADC
DECL|macro|WACMD_OUTPUTSTOP
mdefine_line|#define&t;WACMD_OUTPUTSTOP&t;0x27&t;
singleline_comment|//stop ADC
DECL|macro|WACMD_OUTPUTRESUME
mdefine_line|#define&t;WACMD_OUTPUTRESUME&t;0x28&t;
singleline_comment|//resume ADC
DECL|macro|WACMD_OUTPUTPIO
mdefine_line|#define&t;WACMD_OUTPUTPIO&t;&t;0x29&t;
singleline_comment|//PIO ADC
DECL|macro|WACMD_GET_LEVEL
mdefine_line|#define&t;WACMD_GET_LEVEL&t;&t;0x30
DECL|macro|WACMD_SET_LEVEL
mdefine_line|#define&t;WACMD_SET_LEVEL&t;&t;0x31
DECL|macro|WACMD_SET_MIXER
mdefine_line|#define&t;WACMD_SET_MIXER&t;&t;0x32
DECL|macro|WACMD_RST_MIXER
mdefine_line|#define&t;WACMD_RST_MIXER&t;&t;0x33
DECL|macro|WACMD_SET_MONO
mdefine_line|#define&t;WACMD_SET_MONO&t;&t;0x34
r_int
id|wa_sendcmd
c_func
(paren
r_int
r_int
id|cmd
)paren
suffix:semicolon
r_int
id|wa_writecmd
c_func
(paren
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
eof
