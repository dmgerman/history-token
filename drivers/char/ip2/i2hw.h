multiline_comment|/*******************************************************************************&n;*&n;*   (c) 1999 by Computone Corporation&n;*&n;********************************************************************************&n;*&n;*&n;*   PACKAGE:     Linux tty Device Driver for IntelliPort II family of multiport&n;*                serial I/O controllers.&n;*&n;*   DESCRIPTION: Definitions limited to properties of the hardware or the&n;*                bootstrap firmware. As such, they are applicable regardless of&n;*                operating system or loadware (standard or diagnostic).&n;*&n;*******************************************************************************/
macro_line|#ifndef I2HW_H
DECL|macro|I2HW_H
mdefine_line|#define I2HW_H 1
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// Revision History:
singleline_comment|//
singleline_comment|// 23 September 1991 MAG   First Draft Started...through...
singleline_comment|// 11 October 1991   ...   Continuing development...
singleline_comment|//  6 August 1993          Added support for ISA-4 (asic) which is architected
singleline_comment|//                         as an ISA-CEX with a single 4-port box.
singleline_comment|//
singleline_comment|// 20 December 1996  AKM   Version for Linux
singleline_comment|//
singleline_comment|//------------------------------------------------------------------------------
multiline_comment|/*------------------------------------------------------------------------------&n;&n;HARDWARE DESCRIPTION:&n;&n;Introduction:&n;&n;The IntelliPort-II and IntelliPort-IIEX products occupy a block of eight (8)&n;addresses in the host&squot;s I/O space.&n;&n;Some addresses are used to transfer data to/from the board, some to transfer&n;so-called &quot;mailbox&quot; messages, and some to read bit-mapped status information.&n;While all the products in the line are functionally similar, some use a 16-bit&n;data path to transfer data while others use an 8-bit path. Also, the use of&n;command /status/mailbox registers differs slightly between the II and IIEX&n;branches of the family.&n;&n;The host determines what type of board it is dealing with by reading a string of&n;sixteen characters from the board. These characters are always placed in the&n;fifo by the board&squot;s local processor whenever the board is reset (either from&n;power-on or under software control) and are known as the &quot;Power-on Reset&n;Message.&quot; In order that this message can be read from either type of board, the&n;hardware registers used in reading this message are the same. Once this message&n;has been read by the host, then it has the information required to operate.&n;&n;General Differences between boards:&n;&n;The greatest structural difference is between the -II and -IIEX families of&n;product. The -II boards use the Am4701 dual 512x8 bidirectional fifo to support&n;the data path, mailbox registers, and status registers. This chip contains some&n;features which are not used in the IntelliPort-II products; a description of&n;these is omitted here. Because of these many features, it contains many&n;registers, too many to access directly within a small address space. They are&n;accessed by first writing a value to a &quot;pointer&quot; register. This value selects&n;the register to be accessed.  The next read or write to that address accesses&n;the selected register rather than the pointer register.&n;&n;The -IIEX boards use a proprietary design similar to the Am4701 in function. But&n;because of a simpler, more streamlined design it doesn&squot;t require so many&n;registers. This means they can be accessed directly in single operations rather&n;than through a pointer register.&n;&n;Besides these differences, there are differences in whether 8-bit or 16-bit&n;transfers are used to move data to the board.&n;&n;The -II boards are capable only of 8-bit data transfers, while the -IIEX boards&n;may be configured for either 8-bit or 16-bit data transfers. If the on-board DIP&n;switch #8 is ON, and the card has been installed in a 16-bit slot, 16-bit&n;transfers are supported (and will be expected by the standard loadware). The&n;on-board firmware can determine the position of the switch, and whether the&n;board is installed in a 16-bit slot; it supplies this information to the host as&n;part of the power-up reset message.&n;&n;The configuration switch (#8) and slot selection do not directly configure the&n;hardware. It is up to the on-board loadware and host-based drivers to act&n;according to the selected options. That is, loadware and drivers could be&n;written to perform 8-bit transfers regardless of the state of the DIP switch or&n;slot (and in a diagnostic environment might well do so). Likewise, 16-bit&n;transfers could be performed as long as the card is in a 16-bit slot.&n;&n;Note the slot selection and DIP switch selection are provided separately: a&n;board running in 8-bit mode in a 16-bit slot has a greater range of possible&n;interrupts to choose from; information of potential use to the host.&n;&n;All 8-bit data transfers are done in the same way, regardless of whether on a&n;-II board or a -IIEX board.&n;&n;The host must consider two things then: 1) whether a -II or -IIEX product is&n;being used, and 2) whether an 8-bit or 16-bit data path is used.&n;&n;A further difference is that -II boards always have a 512-byte fifo operating in&n;each direction. -IIEX boards may use fifos of varying size; this size is&n;reported as part of the power-up message.&n;&n;I/O Map Of IntelliPort-II and IntelliPort-IIEX boards:&n;(Relative to the chosen base address)&n;&n;Addr  R/W      IntelliPort-II    IntelliPort-IIEX&n;----  ---      --------------    ----------------&n;0     R/W      Data Port (byte)  Data Port (byte or word)&n;1     R/W      (Not used)        (MSB of word-wide data written to Data Port)&n;2     R        Status Register   Status Register&n;2     W        Pointer Register  Interrupt Mask Register&n;3     R/W      (Not used)        Mailbox Registers (6 bits: 11111100)&n;4,5   --       Reserved for future products&n;6     --       Reserved for future products&n;7     R        Guaranteed to have no effect&n;7     W        Hardware reset of board.&n;&n;&n;Rules:&n;All data transfers are performed using the even i/o address. If byte-wide data&n;transfers are being used, do INB/OUTB operations on the data port. If word-wide&n;transfers are used, do INW/OUTW operations. In some circumstances (such as&n;reading the power-up message) you will do INB from the data port, but in this&n;case the MSB of each word read is lost. When accessing all other unreserved&n;registers, use byte operations only.&n;------------------------------------------------------------------------------*/
singleline_comment|//------------------------------------------------
singleline_comment|// Mandatory Includes:
singleline_comment|//------------------------------------------------
singleline_comment|//
macro_line|#include &quot;ip2types.h&quot;
macro_line|#include &quot;i2os.h&quot;    /* For any o.s., compiler, or host-related issues */
singleline_comment|//-------------------------------------------------------------------------
singleline_comment|// Manifests for the I/O map:
singleline_comment|//-------------------------------------------------------------------------
singleline_comment|// R/W: Data port (byte) for IntelliPort-II,
singleline_comment|// R/W: Data port (byte or word) for IntelliPort-IIEX
singleline_comment|// Incoming or outgoing data passes through a FIFO, the status of which is
singleline_comment|// available in some of the bits in FIFO_STATUS. This (bidirectional) FIFO is
singleline_comment|// the primary means of transferring data, commands, flow-control, and status
singleline_comment|// information between the host and board.
singleline_comment|//
DECL|macro|FIFO_DATA
mdefine_line|#define FIFO_DATA 0
singleline_comment|// Another way of passing information between the board and the host is
singleline_comment|// through &quot;mailboxes&quot;. Unlike a FIFO, a mailbox holds only a single byte of
singleline_comment|// data.  Writing data to the mailbox causes a status bit to be set, and
singleline_comment|// potentially interrupting the intended receiver. The sender has some way to
singleline_comment|// determine whether the data has been read yet; as soon as it has, it may send
singleline_comment|// more. The mailboxes are handled differently on -II and -IIEX products, as
singleline_comment|// suggested below.
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// Read: Status Register for IntelliPort-II or -IIEX
singleline_comment|// The presence of any bit set here will cause an interrupt to the host,
singleline_comment|// provided the corresponding bit has been unmasked in the interrupt mask
singleline_comment|// register. Furthermore, interrupts to the host are disabled globally until the
singleline_comment|// loadware selects the irq line to use. With the exception of STN_MR, the bits
singleline_comment|// remain set so long as the associated condition is true.
singleline_comment|//
DECL|macro|FIFO_STATUS
mdefine_line|#define FIFO_STATUS 2
singleline_comment|// Bit map of status bits which are identical for -II and -IIEX
singleline_comment|//
DECL|macro|ST_OUT_FULL
mdefine_line|#define ST_OUT_FULL  0x40  
singleline_comment|// Outbound FIFO full
DECL|macro|ST_IN_EMPTY
mdefine_line|#define ST_IN_EMPTY  0x20  
singleline_comment|// Inbound FIFO empty
DECL|macro|ST_IN_MAIL
mdefine_line|#define ST_IN_MAIL   0x04  
singleline_comment|// Inbound Mailbox full
singleline_comment|// The following exists only on the Intelliport-IIEX, and indicates that the
singleline_comment|// board has not read the last outgoing mailbox data yet. In the IntelliPort-II,
singleline_comment|// the outgoing mailbox may be read back: a zero indicates the board has read
singleline_comment|// the data.
singleline_comment|//
DECL|macro|STE_OUT_MAIL
mdefine_line|#define STE_OUT_MAIL 0x80  
singleline_comment|// Outbound mailbox full (!)
singleline_comment|// The following bits are defined differently for -II and -IIEX boards. Code
singleline_comment|// which relies on these bits will need to be functionally different for the two
singleline_comment|// types of boards and should be generally avoided because of the additional
singleline_comment|// complexity this creates:
singleline_comment|// Bit map of status bits only on -II
singleline_comment|// Fifo has been RESET (cleared when the status register is read). Note that
singleline_comment|// this condition cannot be masked and would always interrupt the host, except
singleline_comment|// that the hardware reset also disables interrupts globally from the board
singleline_comment|// until re-enabled by loadware. This could also arise from the
singleline_comment|// Am4701-supported command to reset the chip, but this command is generally not
singleline_comment|// used here.
singleline_comment|//
DECL|macro|STN_MR
mdefine_line|#define STN_MR       0x80
singleline_comment|// See the AMD Am4701 data sheet for details on the following four bits. They
singleline_comment|// are not presently used by Computone drivers.
singleline_comment|//
DECL|macro|STN_OUT_AF
mdefine_line|#define STN_OUT_AF  0x10  
singleline_comment|// Outbound FIFO almost full (programmable)
DECL|macro|STN_IN_AE
mdefine_line|#define STN_IN_AE   0x08  
singleline_comment|// Inbound FIFO almost empty (programmable)
DECL|macro|STN_BD
mdefine_line|#define STN_BD      0x02  
singleline_comment|// Inbound byte detected
DECL|macro|STN_PE
mdefine_line|#define STN_PE      0x01  
singleline_comment|// Parity/Framing condition detected
singleline_comment|// Bit-map of status bits only on -IIEX
singleline_comment|//
DECL|macro|STE_OUT_HF
mdefine_line|#define STE_OUT_HF  0x10  
singleline_comment|// Outbound FIFO half full
DECL|macro|STE_IN_HF
mdefine_line|#define STE_IN_HF   0x08  
singleline_comment|// Inbound FIFO half full
DECL|macro|STE_IN_FULL
mdefine_line|#define STE_IN_FULL 0x02  
singleline_comment|// Inbound FIFO full
DECL|macro|STE_OUT_MT
mdefine_line|#define STE_OUT_MT  0x01  
singleline_comment|// Outbound FIFO empty
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// Intelliport-II -- Write Only: the pointer register.
singleline_comment|// Values are written to this register to select the Am4701 internal register to
singleline_comment|// be accessed on the next operation.
singleline_comment|//
DECL|macro|FIFO_PTR
mdefine_line|#define FIFO_PTR    0x02
singleline_comment|// Values for the pointer register
singleline_comment|//
DECL|macro|SEL_COMMAND
mdefine_line|#define SEL_COMMAND 0x1    
singleline_comment|// Selects the Am4701 command register
singleline_comment|// Some possible commands:
singleline_comment|//
DECL|macro|SEL_CMD_MR
mdefine_line|#define SEL_CMD_MR  0x80&t;
singleline_comment|// Am4701 command to reset the chip
DECL|macro|SEL_CMD_SH
mdefine_line|#define SEL_CMD_SH  0x40&t;
singleline_comment|// Am4701 command to map the &quot;other&quot; port into the
singleline_comment|// status register.
DECL|macro|SEL_CMD_UNSH
mdefine_line|#define SEL_CMD_UNSH   0&t;
singleline_comment|// Am4701 command to &quot;unshift&quot;: port maps into its
singleline_comment|// own status register.
DECL|macro|SEL_MASK
mdefine_line|#define SEL_MASK     0x2&t;
singleline_comment|// Selects the Am4701 interrupt mask register. The
singleline_comment|// interrupt mask register is bit-mapped to match 
singleline_comment|// the status register (FIFO_STATUS) except for
singleline_comment|// STN_MR. (See above.)
DECL|macro|SEL_BYTE_DET
mdefine_line|#define SEL_BYTE_DET 0x3&t;
singleline_comment|// Selects the Am4701 byte-detect register. (Not
singleline_comment|// normally used except in diagnostics.)
DECL|macro|SEL_OUTMAIL
mdefine_line|#define SEL_OUTMAIL  0x4&t;
singleline_comment|// Selects the outbound mailbox (R/W). Reading back
singleline_comment|// a value of zero indicates that the mailbox has
singleline_comment|// been read by the board and is available for more
singleline_comment|// data./ Writing to the mailbox optionally
singleline_comment|// interrupts the board, depending on the loadware&squot;s
singleline_comment|// setting of its interrupt mask register.
DECL|macro|SEL_AEAF
mdefine_line|#define SEL_AEAF     0x5&t;
singleline_comment|// Selects AE/AF threshold register.
DECL|macro|SEL_INMAIL
mdefine_line|#define SEL_INMAIL   0x6&t;
singleline_comment|// Selects the inbound mailbox (Read)
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// IntelliPort-IIEX --  Write Only: interrupt mask (and misc flags) register:
singleline_comment|// Unlike IntelliPort-II, bit assignments do NOT match those of the status
singleline_comment|// register.
singleline_comment|//
DECL|macro|FIFO_MASK
mdefine_line|#define FIFO_MASK    0x2
singleline_comment|// Mailbox readback select:
singleline_comment|// If set, reads to FIFO_MAIL will read the OUTBOUND mailbox (host to board). If
singleline_comment|// clear (default on reset) reads to FIFO_MAIL will read the INBOUND mailbox.
singleline_comment|// This is the normal situation. The clearing of a mailbox is determined on
singleline_comment|// -IIEX boards by waiting for the STE_OUT_MAIL bit to clear. Readback
singleline_comment|// capability is provided for diagnostic purposes only.
singleline_comment|//
DECL|macro|MX_OUTMAIL_RSEL
mdefine_line|#define  MX_OUTMAIL_RSEL   0x80
DECL|macro|MX_IN_MAIL
mdefine_line|#define  MX_IN_MAIL  0x40&t;
singleline_comment|// Enables interrupts when incoming mailbox goes
singleline_comment|// full (ST_IN_MAIL set).
DECL|macro|MX_IN_FULL
mdefine_line|#define  MX_IN_FULL  0x20&t;
singleline_comment|// Enables interrupts when incoming FIFO goes full
singleline_comment|// (STE_IN_FULL).
DECL|macro|MX_IN_MT
mdefine_line|#define  MX_IN_MT    0x08&t;
singleline_comment|// Enables interrupts when incoming FIFO goes empty
singleline_comment|// (ST_IN_MT).
DECL|macro|MX_OUT_FULL
mdefine_line|#define  MX_OUT_FULL 0x04&t;
singleline_comment|// Enables interrupts when outgoing FIFO goes full
singleline_comment|// (ST_OUT_FULL).
DECL|macro|MX_OUT_MT
mdefine_line|#define  MX_OUT_MT   0x01&t;
singleline_comment|// Enables interrupts when outgoing FIFO goes empty
singleline_comment|// (STE_OUT_MT).
singleline_comment|// Any remaining bits are reserved, and should be written to ZERO for
singleline_comment|// compatibility with future Computone products.
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// IntelliPort-IIEX: -- These are only 6-bit mailboxes !!! -- 11111100 (low two
singleline_comment|// bits always read back 0).
singleline_comment|// Read:  One of the mailboxes, usually Inbound.
singleline_comment|//        Inbound Mailbox (MX_OUTMAIL_RSEL = 0)
singleline_comment|//        Outbound Mailbox (MX_OUTMAIL_RSEL = 1)
singleline_comment|// Write: Outbound Mailbox
singleline_comment|// For the IntelliPort-II boards, the outbound mailbox is read back to determine
singleline_comment|// whether the board has read the data (0 --&gt; data has been read). For the
singleline_comment|// IntelliPort-IIEX, this is done by reading a status register. To determine
singleline_comment|// whether mailbox is available for more outbound data, use the STE_OUT_MAIL bit
singleline_comment|// in FIFO_STATUS. Moreover, although the Outbound Mailbox can be read back by
singleline_comment|// setting MX_OUTMAIL_RSEL, it is NOT cleared when the board reads it, as is the
singleline_comment|// case with the -II boards. For this reason, FIFO_MAIL is normally used to read
singleline_comment|// the inbound FIFO, and MX_OUTMAIL_RSEL kept clear. (See above for
singleline_comment|// MX_OUTMAIL_RSEL description.)
singleline_comment|//
DECL|macro|FIFO_MAIL
mdefine_line|#define  FIFO_MAIL   0x3
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// WRITE ONLY:  Resets the board. (Data doesn&squot;t matter).
singleline_comment|//
DECL|macro|FIFO_RESET
mdefine_line|#define  FIFO_RESET  0x7
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// READ ONLY:  Will have no effect. (Data is undefined.)
singleline_comment|// Actually, there will be an effect, in that the operation is sure to generate
singleline_comment|// a bus cycle: viz., an I/O byte Read. This fact can be used to enforce short
singleline_comment|// delays when no comparable time constant is available.
singleline_comment|//
DECL|macro|FIFO_NOP
mdefine_line|#define  FIFO_NOP    0x7
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// RESET &amp; POWER-ON RESET MESSAGE
multiline_comment|/*------------------------------------------------------------------------------&n;RESET:&n;&n;The IntelliPort-II and -IIEX boards are reset in three ways: Power-up, channel&n;reset, and via a write to the reset register described above. For products using&n;the ISA bus, these three sources of reset are equvalent. For MCA and EISA buses,&n;the Power-up and channel reset sources cause additional hardware initialization&n;which should only occur at system startup time.&n;&n;The third type of reset, called a &quot;command reset&quot;, is done by writing any data&n;to the FIFO_RESET address described above. This resets the on-board processor,&n;FIFO, UARTS, and associated hardware.&n;&n;This passes control of the board to the bootstrap firmware, which performs a&n;Power-On Self Test and which detects its current configuration. For example,&n;-IIEX products determine the size of FIFO which has been installed, and the&n;number and type of expansion boxes attached.&n;&n;This and other information is then written to the FIFO in a 16-byte data block&n;to be read by the host. This block is guaranteed to be present within two (2)&n;seconds of having received the command reset. The firmware is now ready to&n;receive loadware from the host.&n;&n;It is good practice to perform a command reset to the board explicitly as part&n;of your software initialization.  This allows your code to properly restart from&n;a soft boot. (Many systems do not issue channel reset on soft boot).&n;&n;Because of a hardware reset problem on some of the Cirrus Logic 1400&squot;s which are&n;used on the product, it is recommended that you reset the board twice, separated&n;by an approximately 50 milliseconds delay. (VERY approximately: probably ok to&n;be off by a factor of five. The important point is that the first command reset&n;in fact generates a reset pulse on the board. This pulse is guaranteed to last&n;less than 10 milliseconds. The additional delay ensures the 1400 has had the&n;chance to respond sufficiently to the first reset. Why not a longer delay? Much&n;more than 50 milliseconds gets to be noticable, but the board would still work.&n;&n;Once all 16 bytes of the Power-on Reset Message have been read, the bootstrap&n;firmware is ready to receive loadware.&n;&n;Note on Power-on Reset Message format:&n;The various fields have been designed with future expansion in view.&n;Combinations of bitfields and values have been defined which define products&n;which may not currently exist. This has been done to allow drivers to anticipate&n;the possible introduction of products in a systematic fashion. This is not&n;intended to suggest that each potential product is actually under consideration.&n;------------------------------------------------------------------------------*/
singleline_comment|//----------------------------------------
singleline_comment|// Format of Power-on Reset Message
singleline_comment|//----------------------------------------
DECL|union|_porStr
r_typedef
r_union
id|_porStr
singleline_comment|// &quot;por&quot; stands for Power On Reset
(brace
DECL|member|c
r_int
r_char
id|c
(braket
l_int|16
)braket
suffix:semicolon
singleline_comment|// array used when considering the message as a
singleline_comment|// string of undifferentiated characters
r_struct
singleline_comment|// Elements used when considering values
(brace
singleline_comment|// The first two bytes out of the FIFO are two magic numbers. These are
singleline_comment|// intended to establish that there is indeed a member of the
singleline_comment|// IntelliPort-II(EX) family present. The remaining bytes may be 
singleline_comment|// expected // to be valid. When reading the Power-on Reset message, 
singleline_comment|// if the magic numbers do not match it is probably best to stop
singleline_comment|// reading immediately. You are certainly not reading our board (unless
singleline_comment|// hardware is faulty), and may in fact be reading some other piece of
singleline_comment|// hardware.
DECL|member|porMagic1
r_int
r_char
id|porMagic1
suffix:semicolon
singleline_comment|// magic number: first byte == POR_MAGIC_1 
DECL|member|porMagic2
r_int
r_char
id|porMagic2
suffix:semicolon
singleline_comment|// magic number: second byte == POR_MAGIC_2 
singleline_comment|// The Version, Revision, and Subrevision are stored as absolute numbers
singleline_comment|// and would normally be displayed in the format V.R.S (e.g. 1.0.2)
DECL|member|porVersion
r_int
r_char
id|porVersion
suffix:semicolon
singleline_comment|// Bootstrap firmware version number
DECL|member|porRevision
r_int
r_char
id|porRevision
suffix:semicolon
singleline_comment|// Bootstrap firmware revision number
DECL|member|porSubRev
r_int
r_char
id|porSubRev
suffix:semicolon
singleline_comment|// Bootstrap firmware sub-revision number
DECL|member|porID
r_int
r_char
id|porID
suffix:semicolon
singleline_comment|// Product ID:  Bit-mapped according to
singleline_comment|// conventions described below. Among other
singleline_comment|// things, this allows us to distinguish
singleline_comment|// IntelliPort-II boards from IntelliPort-IIEX
singleline_comment|// boards.
DECL|member|porBus
r_int
r_char
id|porBus
suffix:semicolon
singleline_comment|// IntelliPort-II: Unused
singleline_comment|// IntelliPort-IIEX: Bus Information:
singleline_comment|// Bit-mapped below
DECL|member|porMemory
r_int
r_char
id|porMemory
suffix:semicolon
singleline_comment|// On-board DRAM size: in 32k blocks
singleline_comment|// porPorts1 (and porPorts2) are used to determine the ports which are
singleline_comment|// available to the board. For non-expandable product, a single number 
singleline_comment|// is sufficient. For expandable product, the board may be connected
singleline_comment|// to as many as four boxes. Each box may be (so far) either a 16-port
singleline_comment|// or an 8-port size. Whenever an 8-port box is used, the remaining 8
singleline_comment|// ports leave gaps between existing channels. For that reason,
singleline_comment|// expandable products must report a MAP of available channels. Since 
singleline_comment|// each UART supports four ports, we represent each UART found by a
singleline_comment|// single bit. Using two bytes to supply the mapping information we
singleline_comment|// report the presense or absense of up to 16 UARTS, or 64 ports in
singleline_comment|// steps of 4 ports. For -IIEX products, the ports are numbered
singleline_comment|// starting at the box closest to the controller in the &quot;chain&quot;.
singleline_comment|// Interpreted Differently for IntelliPort-II and -IIEX.
singleline_comment|// -II:   Number of ports (Derived actually from product ID). See
singleline_comment|// Diag1&amp;2 to indicate if uart was actually detected.
singleline_comment|// -IIEX: Bit-map of UARTS found, LSB (see below for MSB of this). This
singleline_comment|//        bitmap is based on detecting the uarts themselves; 
singleline_comment|//        see porFlags for information from the box i.d&squot;s.
DECL|member|porPorts1
r_int
r_char
id|porPorts1
suffix:semicolon
DECL|member|porDiag1
r_int
r_char
id|porDiag1
suffix:semicolon
singleline_comment|// Results of on-board P.O.S.T, 1st byte
DECL|member|porDiag2
r_int
r_char
id|porDiag2
suffix:semicolon
singleline_comment|// Results of on-board P.O.S.T, 2nd byte
DECL|member|porSpeed
r_int
r_char
id|porSpeed
suffix:semicolon
singleline_comment|// Speed of local CPU: given as MHz x10
singleline_comment|// e.g., 16.0 MHz CPU is reported as 160
DECL|member|porFlags
r_int
r_char
id|porFlags
suffix:semicolon
singleline_comment|// Misc information (see manifests below)
singleline_comment|// Bit-mapped: CPU type, UART&squot;s present
DECL|member|porPorts2
r_int
r_char
id|porPorts2
suffix:semicolon
singleline_comment|// -II:  Undefined
singleline_comment|// -IIEX: Bit-map of UARTS found, MSB (see
singleline_comment|//        above for LSB)
singleline_comment|// IntelliPort-II: undefined
singleline_comment|// IntelliPort-IIEX: 1 &lt;&lt; porFifoSize gives the size, in bytes, of the
singleline_comment|// host interface FIFO, in each direction. When running the -IIEX in
singleline_comment|// 8-bit mode, fifo capacity is halved. The bootstrap firmware will
singleline_comment|// have already accounted for this fact in generating this number.
DECL|member|porFifoSize
r_int
r_char
id|porFifoSize
suffix:semicolon
singleline_comment|// IntelliPort-II: undefined
singleline_comment|// IntelliPort-IIEX: The number of boxes connected. (Presently 1-4)
DECL|member|porNumBoxes
r_int
r_char
id|porNumBoxes
suffix:semicolon
DECL|member|e
)brace
id|e
suffix:semicolon
DECL|typedef|porStr
DECL|typedef|porStrPtr
)brace
id|porStr
comma
op_star
id|porStrPtr
suffix:semicolon
singleline_comment|//--------------------------
singleline_comment|// Values for porStr fields
singleline_comment|//--------------------------
singleline_comment|//---------------------
singleline_comment|// porMagic1, porMagic2
singleline_comment|//----------------------
singleline_comment|//
DECL|macro|POR_MAGIC_1
mdefine_line|#define  POR_MAGIC_1    0x96  
singleline_comment|// The only valid value for porMagic1
DECL|macro|POR_MAGIC_2
mdefine_line|#define  POR_MAGIC_2    0x35  
singleline_comment|// The only valid value for porMagic2
DECL|macro|POR_1_INDEX
mdefine_line|#define  POR_1_INDEX    0     
singleline_comment|// Byte position of POR_MAGIC_1
DECL|macro|POR_2_INDEX
mdefine_line|#define  POR_2_INDEX    1     
singleline_comment|// Ditto for POR_MAGIC_2
singleline_comment|//----------------------
singleline_comment|// porID
singleline_comment|//----------------------
singleline_comment|//
DECL|macro|POR_ID_FAMILY
mdefine_line|#define  POR_ID_FAMILY  0xc0&t;
singleline_comment|// These bits indicate the general family of
singleline_comment|// product.
DECL|macro|POR_ID_FII
mdefine_line|#define  POR_ID_FII     0x00&t;
singleline_comment|// Family is &quot;IntelliPort-II&quot;
DECL|macro|POR_ID_FIIEX
mdefine_line|#define  POR_ID_FIIEX   0x40&t;
singleline_comment|// Family is &quot;IntelliPort-IIEX&quot;
singleline_comment|// These bits are reserved, presently zero. May be used at a later date to
singleline_comment|// convey other product information.
singleline_comment|//
DECL|macro|POR_ID_RESERVED
mdefine_line|#define POR_ID_RESERVED 0x3c
DECL|macro|POR_ID_SIZE
mdefine_line|#define POR_ID_SIZE     0x03&t;
singleline_comment|// Remaining bits indicate number of ports &amp;
singleline_comment|// Connector information.
DECL|macro|POR_ID_II_8
mdefine_line|#define POR_ID_II_8     0x00&t;
singleline_comment|// For IntelliPort-II, indicates 8-port using
singleline_comment|// standard brick.
DECL|macro|POR_ID_II_8R
mdefine_line|#define POR_ID_II_8R    0x01&t;
singleline_comment|// For IntelliPort-II, indicates 8-port using
singleline_comment|// RJ11&squot;s (no CTS)
DECL|macro|POR_ID_II_6
mdefine_line|#define POR_ID_II_6     0x02&t;
singleline_comment|// For IntelliPort-II, indicates 6-port using
singleline_comment|// RJ45&squot;s
DECL|macro|POR_ID_II_4
mdefine_line|#define POR_ID_II_4     0x03&t;
singleline_comment|// For IntelliPort-II, indicates 4-port using
singleline_comment|// 4xRJ45 connectors
DECL|macro|POR_ID_EX
mdefine_line|#define POR_ID_EX       0x00&t;
singleline_comment|// For IntelliPort-IIEX, indicates standard
singleline_comment|// expandable controller (other values reserved)
singleline_comment|//----------------------
singleline_comment|// porBus
singleline_comment|//----------------------
singleline_comment|// IntelliPort-IIEX only: Board is installed in a 16-bit slot
singleline_comment|//
DECL|macro|POR_BUS_SLOT16
mdefine_line|#define POR_BUS_SLOT16  0x20
singleline_comment|// IntelliPort-IIEX only: DIP switch #8 is on, selecting 16-bit host interface
singleline_comment|// operation.
singleline_comment|// 
DECL|macro|POR_BUS_DIP16
mdefine_line|#define POR_BUS_DIP16   0x10
singleline_comment|// Bits 0-2 indicate type of bus: This information is stored in the bootstrap
singleline_comment|// loadware, different loadware being used on different products for different
singleline_comment|// buses. For most situations, the drivers do not need this information; but it
singleline_comment|// is handy in a diagnostic environment. For example, on microchannel boards,
singleline_comment|// you would not want to try to test several interrupts, only the one for which
singleline_comment|// you were configured.
singleline_comment|//
DECL|macro|POR_BUS_TYPE
mdefine_line|#define  POR_BUS_TYPE   0x07
singleline_comment|// Unknown:  this product doesn&squot;t know what bus it is running in. (e.g. if same
singleline_comment|// bootstrap firmware were wanted for two different buses.)
singleline_comment|//
DECL|macro|POR_BUS_T_UNK
mdefine_line|#define  POR_BUS_T_UNK  0
singleline_comment|// Note: existing firmware for ISA-8 and MC-8 currently report the POR_BUS_T_UNK
singleline_comment|// state, since the same bootstrap firmware is used for each.
DECL|macro|POR_BUS_T_MCA
mdefine_line|#define  POR_BUS_T_MCA  1  
singleline_comment|// MCA BUS */
DECL|macro|POR_BUS_T_EISA
mdefine_line|#define  POR_BUS_T_EISA 2  
singleline_comment|// EISA BUS */
DECL|macro|POR_BUS_T_ISA
mdefine_line|#define  POR_BUS_T_ISA  3  
singleline_comment|// ISA BUS */
singleline_comment|// Values 4-7 Reserved
singleline_comment|// Remaining bits are reserved
singleline_comment|//----------------------
singleline_comment|// porDiag1
singleline_comment|//----------------------
DECL|macro|POR_BAD_MAPPER
mdefine_line|#define  POR_BAD_MAPPER 0x80&t;
singleline_comment|// HW failure on P.O.S.T: Chip mapper failed
singleline_comment|// These two bits valid only for the IntelliPort-II
singleline_comment|//
DECL|macro|POR_BAD_UART1
mdefine_line|#define  POR_BAD_UART1  0x01&t;
singleline_comment|// First  1400 bad
DECL|macro|POR_BAD_UART2
mdefine_line|#define  POR_BAD_UART2  0x02&t;
singleline_comment|// Second 1400 bad
singleline_comment|//----------------------
singleline_comment|// porDiag2
singleline_comment|//----------------------
DECL|macro|POR_DEBUG_PORT
mdefine_line|#define  POR_DEBUG_PORT 0x80&t;
singleline_comment|// debug port was detected by the P.O.S.T
DECL|macro|POR_DIAG_OK
mdefine_line|#define  POR_DIAG_OK    0x00&t;
singleline_comment|// Indicates passage: Failure codes not yet
singleline_comment|// available.
singleline_comment|// Other bits undefined.
singleline_comment|//----------------------
singleline_comment|// porFlags
singleline_comment|//----------------------
DECL|macro|POR_CPU
mdefine_line|#define  POR_CPU     0x03&t;
singleline_comment|// These bits indicate supposed CPU type
DECL|macro|POR_CPU_8
mdefine_line|#define  POR_CPU_8   0x01&t;
singleline_comment|// Board uses an 80188 (no such thing yet)
DECL|macro|POR_CPU_6
mdefine_line|#define  POR_CPU_6   0x02&t;
singleline_comment|// Board uses an 80186 (all existing products)
DECL|macro|POR_CEX4
mdefine_line|#define  POR_CEX4    0x04&t;
singleline_comment|// If set, this is an ISA-CEX/4: An ISA-4 (asic)
singleline_comment|// which is architected like an ISA-CEX connected
singleline_comment|// to a (hitherto impossible) 4-port box.
DECL|macro|POR_BOXES
mdefine_line|#define POR_BOXES    0xf0&t;
singleline_comment|// Valid for IntelliPort-IIEX only: Map of Box
singleline_comment|// sizes based on box I.D.
DECL|macro|POR_BOX_16
mdefine_line|#define POR_BOX_16   0x10&t;
singleline_comment|// Set indicates 16-port, clear 8-port
singleline_comment|//-------------------------------------
singleline_comment|// LOADWARE and DOWNLOADING CODE
singleline_comment|//-------------------------------------
multiline_comment|/*&n;Loadware may be sent to the board in two ways:&n;1) It may be read from a (binary image) data file block by block as each block&n;&t;is sent to the board. This is only possible when the initialization is&n;&t;performed by code which can access your file system. This is most suitable&n;&t;for diagnostics and appications which use the interface library directly.&n;&n;2) It may be hard-coded into your source by including a .h file (typically&n;&t;supplied by Computone), which declares a data array and initializes every&n;&t;element. This acheives the same result as if an entire loadware file had &n;&t;been read into the array.&n;&n;&t;This requires more data space in your program, but access to the file system&n;&t;is not required. This method is more suited to driver code, which typically&n;&t;is running at a level too low to access the file system directly.&n;&n;At present, loadware can only be generated at Computone.&n;&n;All Loadware begins with a header area which has a particular format. This&n;includes a magic number which identifies the file as being (purportedly)&n;loadware, CRC (for the loader), and version information.&n;*/
singleline_comment|//-----------------------------------------------------------------------------
singleline_comment|// Format of loadware block
singleline_comment|//
singleline_comment|// This is defined as a union so we can pass a pointer to one of these items
singleline_comment|// and (if it is the first block) pick out the version information, etc.
singleline_comment|//
singleline_comment|// Otherwise, to deal with this as a simple character array
singleline_comment|//------------------------------------------------------------------------------
DECL|macro|LOADWARE_BLOCK_SIZE
mdefine_line|#define LOADWARE_BLOCK_SIZE   512   
singleline_comment|// Number of bytes in each block of loadware
DECL|union|_loadHdrStr
r_typedef
r_union
id|_loadHdrStr
(brace
DECL|member|c
r_int
r_char
id|c
(braket
id|LOADWARE_BLOCK_SIZE
)braket
suffix:semicolon
singleline_comment|// Valid for every block
r_struct
singleline_comment|// These fields are valid for only the first block of loadware.
(brace
DECL|member|loadMagic
r_int
r_char
id|loadMagic
suffix:semicolon
singleline_comment|// Magic number: see below
DECL|member|loadBlocksMore
r_int
r_char
id|loadBlocksMore
suffix:semicolon
singleline_comment|// How many more blocks?
DECL|member|loadCRC
r_int
r_char
id|loadCRC
(braket
l_int|2
)braket
suffix:semicolon
singleline_comment|// Two CRC bytes: used by loader
DECL|member|loadVersion
r_int
r_char
id|loadVersion
suffix:semicolon
singleline_comment|// Version number
DECL|member|loadRevision
r_int
r_char
id|loadRevision
suffix:semicolon
singleline_comment|// Revision number
DECL|member|loadSubRevision
r_int
r_char
id|loadSubRevision
suffix:semicolon
singleline_comment|// Sub-revision number
DECL|member|loadSpares
r_int
r_char
id|loadSpares
(braket
l_int|9
)braket
suffix:semicolon
singleline_comment|// Presently unused
DECL|member|loadDates
r_int
r_char
id|loadDates
(braket
l_int|32
)braket
suffix:semicolon
singleline_comment|// Null-terminated string which can give
singleline_comment|// date and time of compilation
DECL|member|e
)brace
id|e
suffix:semicolon
DECL|typedef|loadHdrStr
DECL|typedef|loadHdrStrPtr
)brace
id|loadHdrStr
comma
op_star
id|loadHdrStrPtr
suffix:semicolon
singleline_comment|//------------------------------------
singleline_comment|// Defines for downloading code:
singleline_comment|//------------------------------------
singleline_comment|// The loadMagic field in the first block of the loadfile must be this, else the
singleline_comment|// file is not valid.
singleline_comment|//
DECL|macro|MAGIC_LOADFILE
mdefine_line|#define  MAGIC_LOADFILE 0x3c
singleline_comment|// How do we know the load was successful? On completion of the load, the
singleline_comment|// bootstrap firmware returns a code to indicate whether it thought the download
singleline_comment|// was valid and intends to execute it. These are the only possible valid codes:
singleline_comment|//
DECL|macro|LOADWARE_OK
mdefine_line|#define  LOADWARE_OK    0xc3        
singleline_comment|// Download was ok
DECL|macro|LOADWARE_BAD
mdefine_line|#define  LOADWARE_BAD   0x5a        
singleline_comment|// Download was bad (CRC error)
singleline_comment|// Constants applicable to writing blocks of loadware:
singleline_comment|// The first block of loadware might take 600 mS to load, in extreme cases.
singleline_comment|// (Expandable board: worst case for sending startup messages to the LCD&squot;s).
singleline_comment|// The 600mS figure is not really a calculation, but a conservative
singleline_comment|// guess/guarantee. Usually this will be within 100 mS, like subsequent blocks.
singleline_comment|//
DECL|macro|MAX_DLOAD_START_TIME
mdefine_line|#define  MAX_DLOAD_START_TIME 1000  
singleline_comment|// 1000 mS
DECL|macro|MAX_DLOAD_READ_TIME
mdefine_line|#define  MAX_DLOAD_READ_TIME  100   
singleline_comment|// 100 mS
singleline_comment|// Firmware should respond with status (see above) within this long of host
singleline_comment|// having sent the final block.
singleline_comment|//
DECL|macro|MAX_DLOAD_ACK_TIME
mdefine_line|#define  MAX_DLOAD_ACK_TIME   100   
singleline_comment|// 100 mS, again!
singleline_comment|//------------------------------------------------------
singleline_comment|// MAXIMUM NUMBER OF PORTS PER BOARD:
singleline_comment|// This is fixed for now (with the expandable), but may
singleline_comment|// be expanding according to even newer products.
singleline_comment|//------------------------------------------------------
singleline_comment|//
DECL|macro|ABS_MAX_BOXES
mdefine_line|#define ABS_MAX_BOXES   4     
singleline_comment|// Absolute most boxes per board
DECL|macro|ABS_BIGGEST_BOX
mdefine_line|#define ABS_BIGGEST_BOX 16    
singleline_comment|// Absolute the most ports per box
DECL|macro|ABS_MOST_PORTS
mdefine_line|#define ABS_MOST_PORTS  (ABS_MAX_BOXES * ABS_BIGGEST_BOX)
macro_line|#endif   
singleline_comment|// I2HW_H
eof
