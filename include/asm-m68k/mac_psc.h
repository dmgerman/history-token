multiline_comment|/*&n; * Apple Peripheral System Controller (PSC)&n; *&n; * The PSC is used on the AV Macs to control IO functions not handled&n; * by the VIAs (Ethernet, DSP, SCC, Sound). This includes nine DMA&n; * channels.&n; *&n; * The first seven DMA channels appear to be &quot;one-shot&quot; and are actually&n; * sets of two channels; one member is active while the other is being&n; * configured, and then you flip the active member and start all over again.&n; * The one-shot channels are grouped together and are:&n; *&n; * 1. SCSI&n; * 2. Ethernet Read&n; * 3. Ethernet Write&n; * 4. Floppy Disk Controller&n; * 5. SCC Channel A Receive&n; * 6. SCC Channel B Receive&n; * 7. SCC Channel A Transmit&n; *&n; * The remaining two channels are handled somewhat differently. They appear&n; * to be closely tied and share one set of registers. They also seem to run&n; * continuously, although how you keep the buffer filled in this scenario is&n; * not understood as there seems to be only one input and one output buffer&n; * pointer.&n; * &n; * Much of this was extrapolated from what was known about the Ethernet&n; * registers and subsequently confirmed using MacsBug (ie by pinging the&n; * machine with easy-to-find patterns and looking for them in the DMA&n; * buffers, or by sending a file over the serial ports and finding the&n; * file in the buffers.)&n; *&n; * 1999-05-25 (jmt)&n; */
DECL|macro|PSC_BASE
mdefine_line|#define PSC_BASE&t;(0x50F31000)
multiline_comment|/*&n; * The IER/IFR registers work like the VIA, except that it has 4&n; * of them each on different interrupt levels, and each register&n; * set only seems to handle four interrupts instead of seven.&n; *&n; * To access a particular set of registers, add 0xn0 to the base&n; * where n = 3,4,5 or 6.&n; */
DECL|macro|pIFRbase
mdefine_line|#define pIFRbase&t;0x100
DECL|macro|pIERbase
mdefine_line|#define pIERbase&t;0x104
multiline_comment|/*&n; * One-shot DMA control registers&n; */
DECL|macro|PSC_MYSTERY
mdefine_line|#define PSC_MYSTERY&t;0x804
DECL|macro|PSC_CTL_BASE
mdefine_line|#define PSC_CTL_BASE&t;0xC00
DECL|macro|PSC_SCSI_CTL
mdefine_line|#define PSC_SCSI_CTL&t;0xC00
DECL|macro|PSC_ENETRD_CTL
mdefine_line|#define PSC_ENETRD_CTL  0xC10
DECL|macro|PSC_ENETWR_CTL
mdefine_line|#define PSC_ENETWR_CTL  0xC20
DECL|macro|PSC_FDC_CTL
mdefine_line|#define PSC_FDC_CTL&t;0xC30
DECL|macro|PSC_SCCA_CTL
mdefine_line|#define PSC_SCCA_CTL&t;0xC40
DECL|macro|PSC_SCCB_CTL
mdefine_line|#define PSC_SCCB_CTL&t;0xC50
DECL|macro|PSC_SCCATX_CTL
mdefine_line|#define PSC_SCCATX_CTL&t;0xC60
multiline_comment|/*&n; * DMA channels. Add +0x10 for the second channel in the set.&n; * You&squot;re supposed to use one channel while the other runs and&n; * then flip channels and do the whole thing again.&n; */
DECL|macro|PSC_ADDR_BASE
mdefine_line|#define PSC_ADDR_BASE&t;0x1000
DECL|macro|PSC_LEN_BASE
mdefine_line|#define PSC_LEN_BASE&t;0x1004
DECL|macro|PSC_CMD_BASE
mdefine_line|#define PSC_CMD_BASE&t;0x1008
DECL|macro|PSC_SET0
mdefine_line|#define PSC_SET0&t;0x00
DECL|macro|PSC_SET1
mdefine_line|#define PSC_SET1&t;0x10
DECL|macro|PSC_SCSI_ADDR
mdefine_line|#define PSC_SCSI_ADDR&t;0x1000 &t;/* confirmed */
DECL|macro|PSC_SCSI_LEN
mdefine_line|#define PSC_SCSI_LEN&t;0x1004 &t;/* confirmed */
DECL|macro|PSC_SCSI_CMD
mdefine_line|#define PSC_SCSI_CMD&t;0x1008 &t;/* confirmed */
DECL|macro|PSC_ENETRD_ADDR
mdefine_line|#define PSC_ENETRD_ADDR 0x1020&t;/* confirmed */
DECL|macro|PSC_ENETRD_LEN
mdefine_line|#define PSC_ENETRD_LEN  0x1024&t;/* confirmed */
DECL|macro|PSC_ENETRD_CMD
mdefine_line|#define PSC_ENETRD_CMD  0x1028&t;/* confirmed */
DECL|macro|PSC_ENETWR_ADDR
mdefine_line|#define PSC_ENETWR_ADDR 0x1040&t;/* confirmed */
DECL|macro|PSC_ENETWR_LEN
mdefine_line|#define PSC_ENETWR_LEN  0x1044&t;/* confirmed */
DECL|macro|PSC_ENETWR_CMD
mdefine_line|#define PSC_ENETWR_CMD  0x1048&t;/* confirmed */
DECL|macro|PSC_FDC_ADDR
mdefine_line|#define PSC_FDC_ADDR&t;0x1060&t;/* strongly suspected */
DECL|macro|PSC_FDC_LEN
mdefine_line|#define PSC_FDC_LEN&t;0x1064&t;/* strongly suspected */
DECL|macro|PSC_FDC_CMD
mdefine_line|#define PSC_FDC_CMD&t;0x1068&t;/* strongly suspected */
DECL|macro|PSC_SCCA_ADDR
mdefine_line|#define PSC_SCCA_ADDR&t;0x1080&t;/* confirmed */
DECL|macro|PSC_SCCA_LEN
mdefine_line|#define PSC_SCCA_LEN&t;0x1084&t;/* confirmed */
DECL|macro|PSC_SCCA_CMD
mdefine_line|#define PSC_SCCA_CMD&t;0x1088&t;/* confirmed */
DECL|macro|PSC_SCCB_ADDR
mdefine_line|#define PSC_SCCB_ADDR&t;0x10A0&t;/* confirmed */
DECL|macro|PSC_SCCB_LEN
mdefine_line|#define PSC_SCCB_LEN&t;0x10A4&t;/* confirmed */
DECL|macro|PSC_SCCB_CMD
mdefine_line|#define PSC_SCCB_CMD&t;0x10A8&t;/* confirmed */
DECL|macro|PSC_SCCATX_ADDR
mdefine_line|#define PSC_SCCATX_ADDR&t;0x10C0&t;/* confirmed */
DECL|macro|PSC_SCCATX_LEN
mdefine_line|#define PSC_SCCATX_LEN&t;0x10C4&t;/* confirmed */
DECL|macro|PSC_SCCATX_CMD
mdefine_line|#define PSC_SCCATX_CMD&t;0x10C8&t;/* confirmed */
multiline_comment|/*&n; * Free-running DMA registers. The only part known for sure are the bits in&n; * the control register, the buffer addresses and the buffer length. Everything&n; * else is anybody&squot;s guess.&n; *&n; * These registers seem to be mirrored every thirty-two bytes up until offset&n; * 0x300. It&squot;s safe to assume then that a new set of registers starts there.&n; */
DECL|macro|PSC_SND_CTL
mdefine_line|#define PSC_SND_CTL&t;0x200&t;/*&n;&t;&t;&t;&t; * [ 16-bit ]&n;&t;&t;&t;&t; * Sound (Singer?) control register.&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; * bit 0  : ????&n;&t;&t;&t;&t; * bit 1  : ????&n;&t;&t;&t;&t; * bit 2  : Set to one to enable sound&n;&t;&t;&t;&t; *          output. Possibly a mute flag.&n;&t;&t;&t;&t; * bit 3  : ????&n;&t;&t;&t;&t; * bit 4  : ????&n;&t;&t;&t;&t; * bit 5  : ????&n;&t;&t;&t;&t; * bit 6  : Set to one to enable pass-thru&n;&t;&t;&t;&t; *          audio. In this mode the audio data&n;&t;&t;&t;&t; *          seems to appear in both the input&n;&t;&t;&t;&t; *          buffer and the output buffer.&n;&t;&t;&t;&t; * bit 7  : Set to one to activate the&n;&t;&t;&t;&t; *          sound input DMA or zero to&n;&t;&t;&t;&t; *          disable it.&n;&t;&t;&t;&t; * bit 8  : Set to one to activate the&n;&t;&t;&t;&t; *          sound output DMA or zero to&n;&t;&t;&t;&t; *          disable it.&n;&t;&t;&t;&t; * bit 9  : &bslash;&n;&t;&t;&t;&t; * bit 11 :  |&n;&t;&t;&t;&t; *          These two bits control the sample&n;&t;&t;&t;&t; *          rate. Usually set to binary 10 and&n;&t;&t;&t;&t; *&t;    MacOS 8.0 says I&squot;m at 48 KHz. Using&n;&t;&t;&t;&t; *&t;    a binary value of 01 makes things&n;&t;&t;&t;&t; *&t;    sound about 1/2 speed (24 KHz?) and&n;&t;&t;&t;&t; *          binary 00 is slower still (22 KHz?)&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; * Setting this to 0x0000 is a good way to&n;&t;&t;&t;&t; * kill all DMA at boot time so that the&n;&t;&t;&t;&t; * PSC won&squot;t overwrite the kernel image&n;&t;&t;&t;&t; * with sound data.&n;&t;&t;&t;&t; */
multiline_comment|/*&n; * 0x0202 - 0x0203 is unused. Writing there&n; * seems to clobber the control register.&n; */
DECL|macro|PSC_SND_SOURCE
mdefine_line|#define PSC_SND_SOURCE&t;0x204&t;/*&n;&t;&t;&t;&t; * [ 32-bit ]&n;&t;&t;&t;&t; * Controls input source and volume:&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; * bits 12-15 : input source volume, 0 - F&n;&t;&t;&t;&t; * bits 16-19 : unknown, always 0x5&n;&t;&t;&t;&t; * bits 20-23 : input source selection:&n;&t;&t;&t;&t; *                  0x3 = CD Audio&n;&t;&t;&t;&t; *                  0x4 = External Audio&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; * The volume is definately not the general&n;&t;&t;&t;&t; * output volume as it doesn&squot;t affect the&n;&t;&t;&t;&t; * alert sound volume.&n;&t;&t;&t;&t; */
DECL|macro|PSC_SND_STATUS1
mdefine_line|#define PSC_SND_STATUS1&t;0x208&t;/*&n;&t;&t;&t;&t; * [ 32-bit ]&n;&t;&t;&t;&t; * Appears to be a read-only status register.&n;&t;&t;&t;&t; * The usual value is 0x00400002.&n;&t;&t;&t;&t; */
DECL|macro|PSC_SND_HUH3
mdefine_line|#define PSC_SND_HUH3&t;0x20C&t;/*&n;&t;&t;&t;&t; * [ 16-bit ]&n;&t;&t;&t;&t; * Unknown 16-bit value, always 0x0000.&n;&t;&t;&t;&t; */
DECL|macro|PSC_SND_BITS2GO
mdefine_line|#define PSC_SND_BITS2GO&t;0x20E&t;/*&n;&t;&t;&t;&t; * [ 16-bit ]&n;&t;&t;&t;&t; * Counts down to zero from some constant&n;&t;&t;&t;&t; * value. The value appears to be the&n;&t;&t;&t;&t; * number of _bits_ remaining before the&n;&t;&t;&t;&t; * buffer is full, which would make sense&n;&t;&t;&t;&t; * since Apple&squot;s docs say the sound DMA&n;&t;&t;&t;&t; * channels are 1 bit wide.&n;&t;&t;&t;&t; */
DECL|macro|PSC_SND_INADDR
mdefine_line|#define PSC_SND_INADDR&t;0x210&t;/*&n;&t;&t;&t;&t; * [ 32-bit ]&n;&t;&t;&t;&t; * Address of the sound input DMA buffer&n;&t;&t;&t;&t; */
DECL|macro|PSC_SND_OUTADDR
mdefine_line|#define PSC_SND_OUTADDR&t;0x214&t;/*&n;&t;&t;&t;&t; * [ 32-bit ]&n;&t;&t;&t;&t; * Address of the sound output DMA buffer&n;&t;&t;&t;&t; */
DECL|macro|PSC_SND_LEN
mdefine_line|#define PSC_SND_LEN&t;0x218&t;/*&n;&t;&t;&t;&t; * [ 16-bit ]&n;&t;&t;&t;&t; * Length of both buffers in eight-byte units.&n;&t;&t;&t;&t; */
DECL|macro|PSC_SND_HUH4
mdefine_line|#define PSC_SND_HUH4&t;0x21A&t;/*&n;&t;&t;&t;&t; * [ 16-bit ]&n;&t;&t;&t;&t; * Unknown, always 0x0000.&n;&t;&t;&t;&t; */
DECL|macro|PSC_SND_STATUS2
mdefine_line|#define PSC_SND_STATUS2&t;0x21C&t;/*&n;&t;&t;&t;&t; * [ 16-bit ]&n;&t;&t;&t;&t; * Appears to e a read-only status register.&n;&t;&t;&t;&t; * The usual value is 0x0200.&n;&t;&t;&t;&t; */
DECL|macro|PSC_SND_HUH5
mdefine_line|#define PSC_SND_HUH5&t;0x21E&t;/*&n;&t;&t;&t;&t; * [ 16-bit ]&n;&t;&t;&t;&t; * Unknown, always 0x0000.&n;&t;&t;&t;&t; */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_volatile
id|__u8
op_star
id|psc
suffix:semicolon
r_extern
r_int
id|psc_present
suffix:semicolon
multiline_comment|/*&n; *&t;Access functions&n; */
DECL|function|psc_write_byte
r_extern
r_inline
r_void
id|psc_write_byte
c_func
(paren
r_int
id|offset
comma
id|__u8
id|data
)paren
(brace
op_star
(paren
(paren
r_volatile
id|__u8
op_star
)paren
(paren
id|psc
op_plus
id|offset
)paren
)paren
op_assign
id|data
suffix:semicolon
)brace
DECL|function|psc_write_word
r_extern
r_inline
r_void
id|psc_write_word
c_func
(paren
r_int
id|offset
comma
id|__u16
id|data
)paren
(brace
op_star
(paren
(paren
r_volatile
id|__u16
op_star
)paren
(paren
id|psc
op_plus
id|offset
)paren
)paren
op_assign
id|data
suffix:semicolon
)brace
DECL|function|psc_write_long
r_extern
r_inline
r_void
id|psc_write_long
c_func
(paren
r_int
id|offset
comma
id|__u32
id|data
)paren
(brace
op_star
(paren
(paren
r_volatile
id|__u32
op_star
)paren
(paren
id|psc
op_plus
id|offset
)paren
)paren
op_assign
id|data
suffix:semicolon
)brace
DECL|function|psc_read_byte
r_extern
r_inline
id|u8
id|psc_read_byte
c_func
(paren
r_int
id|offset
)paren
(brace
r_return
op_star
(paren
(paren
r_volatile
id|__u8
op_star
)paren
(paren
id|psc
op_plus
id|offset
)paren
)paren
suffix:semicolon
)brace
DECL|function|psc_read_word
r_extern
r_inline
id|u16
id|psc_read_word
c_func
(paren
r_int
id|offset
)paren
(brace
r_return
op_star
(paren
(paren
r_volatile
id|__u16
op_star
)paren
(paren
id|psc
op_plus
id|offset
)paren
)paren
suffix:semicolon
)brace
DECL|function|psc_read_long
r_extern
r_inline
id|u32
id|psc_read_long
c_func
(paren
r_int
id|offset
)paren
(brace
r_return
op_star
(paren
(paren
r_volatile
id|__u32
op_star
)paren
(paren
id|psc
op_plus
id|offset
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASSEMBLY__ */
eof
