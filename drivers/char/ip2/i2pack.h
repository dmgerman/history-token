multiline_comment|/*******************************************************************************&n;*&n;*   (c) 1998 by Computone Corporation&n;*&n;********************************************************************************&n;*&n;*&n;*   PACKAGE:     Linux tty Device Driver for IntelliPort II family of multiport&n;*                serial I/O controllers.&n;*&n;*   DESCRIPTION: Definitions of the packets used to transfer data and commands&n;*                Host &lt;--&gt; Board. Information provided here is only applicable&n;*                when the standard loadware is active.&n;*&n;*******************************************************************************/
macro_line|#ifndef I2PACK_H
DECL|macro|I2PACK_H
mdefine_line|#define I2PACK_H  1
singleline_comment|//-----------------------------------------------
singleline_comment|// Revision History:
singleline_comment|//
singleline_comment|// 10 October 1991   MAG First draft
singleline_comment|// 24 February 1992  MAG Additions for 1.4.x loadware
singleline_comment|// 11 March 1992     MAG New status packets
singleline_comment|//
singleline_comment|//-----------------------------------------------
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// Packet Formats:
singleline_comment|//
singleline_comment|// Information passes between the host and board through the FIFO in packets.
singleline_comment|// These have headers which indicate the type of packet. Because the fifo data
singleline_comment|// path may be 16-bits wide, the protocol is constrained such that each packet
singleline_comment|// is always padded to an even byte count. (The lower-level interface routines
singleline_comment|// -- i2ellis.c -- are designed to do this).
singleline_comment|//
singleline_comment|// The sender (be it host or board) must place some number of complete packets
singleline_comment|// in the fifo, then place a message in the mailbox that packets are available.
singleline_comment|// Placing such a message interrupts the &quot;receiver&quot; (be it board or host), who
singleline_comment|// reads the mailbox message and determines that there are incoming packets
singleline_comment|// ready. Since there are no partial packets, and the length of a packet is
singleline_comment|// given in the header, the remainder of the packet can be read without checking
singleline_comment|// for FIFO empty condition. The process is repeated, packet by packet, until
singleline_comment|// the incoming FIFO is empty. Then the receiver uses the outbound mailbox to
singleline_comment|// signal the board that it has read the data. Only then can the sender place
singleline_comment|// additional data in the fifo.
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|//
singleline_comment|//------------------------------------------------
singleline_comment|// Definition of Packet Header Area
singleline_comment|//------------------------------------------------
singleline_comment|//
singleline_comment|// Caution: these only define header areas. In actual use the data runs off
singleline_comment|// beyond the end of these structures.
singleline_comment|//
singleline_comment|// Since these structures are based on sequences of bytes which go to the board,
singleline_comment|// there cannot be ANY padding between the elements.
macro_line|#pragma pack(1)
singleline_comment|//----------------------------
singleline_comment|// DATA PACKETS
singleline_comment|//----------------------------
DECL|struct|_i2DataHeader
r_typedef
r_struct
id|_i2DataHeader
(brace
DECL|member|i2sChannel
r_int
r_char
id|i2sChannel
suffix:semicolon
multiline_comment|/* The channel number: 0-255 */
singleline_comment|// -- Bitfields are allocated LSB first --
singleline_comment|// For incoming data, indicates whether this is an ordinary packet or a
singleline_comment|// special one (e.g., hot key hit).
DECL|member|i2sId
r_int
id|i2sId
suffix:colon
l_int|2
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
singleline_comment|// For tagging data packets. There are flush commands which flush only data
singleline_comment|// packets bearing a particular tag. (used in implementing IntelliView and
singleline_comment|// IntelliPrint). THE TAG VALUE 0xf is RESERVED and must not be used (it has
singleline_comment|// meaning internally to the loadware).
DECL|member|i2sTag
r_int
id|i2sTag
suffix:colon
l_int|4
suffix:semicolon
singleline_comment|// These two bits determine the type of packet sent/received.
DECL|member|i2sType
r_int
id|i2sType
suffix:colon
l_int|2
suffix:semicolon
singleline_comment|// The count of data to follow: does not include the possible additional
singleline_comment|// padding byte. MAXIMUM COUNT: 4094. The top four bits must be 0.
DECL|member|i2sCount
r_int
r_int
id|i2sCount
suffix:semicolon
DECL|typedef|i2DataHeader
DECL|typedef|i2DataHeaderPtr
)brace
id|i2DataHeader
comma
op_star
id|i2DataHeaderPtr
suffix:semicolon
singleline_comment|// Structure is immediately followed by the data, proper.
singleline_comment|//----------------------------
singleline_comment|// NON-DATA PACKETS
singleline_comment|//----------------------------
DECL|struct|_i2CmdHeader
r_typedef
r_struct
id|_i2CmdHeader
(brace
DECL|member|i2sChannel
r_int
r_char
id|i2sChannel
suffix:semicolon
singleline_comment|// The channel number: 0-255 (Except where noted
singleline_comment|// - see below
singleline_comment|// Number of bytes of commands, status or whatever to follow
DECL|member|i2sCount
r_int
id|i2sCount
suffix:colon
l_int|6
suffix:semicolon
singleline_comment|// These two bits determine the type of packet sent/received.
DECL|member|i2sType
r_int
id|i2sType
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|i2CmdHeader
DECL|typedef|i2CmdHeaderPtr
)brace
id|i2CmdHeader
comma
op_star
id|i2CmdHeaderPtr
suffix:semicolon
singleline_comment|// Structure is immediately followed by the applicable data.
singleline_comment|//---------------------------------------
singleline_comment|// Flow Control Packets (Outbound)
singleline_comment|//---------------------------------------
singleline_comment|// One type of outbound command packet is so important that the entire structure
singleline_comment|// is explicitly defined here. That is the flow-control packet. This is never
singleline_comment|// sent by user-level code (as would be the commands to raise/lower DTR, for
singleline_comment|// example). These are only sent by the library routines in response to reading
singleline_comment|// incoming data into the buffers.
singleline_comment|//
singleline_comment|// The parameters inside the command block are maintained in place, then the
singleline_comment|// block is sent at the appropriate time.
DECL|struct|_flowIn
r_typedef
r_struct
id|_flowIn
(brace
DECL|member|hd
id|i2CmdHeader
id|hd
suffix:semicolon
singleline_comment|// Channel #, count, type (see above)
DECL|member|fcmd
r_int
r_char
id|fcmd
suffix:semicolon
singleline_comment|// The flow control command (37)
DECL|member|asof
r_int
r_int
id|asof
suffix:semicolon
singleline_comment|// As of byte number &quot;asof&quot; (LSB first!) I have room
singleline_comment|// for &quot;room&quot; bytes
DECL|member|room
r_int
r_int
id|room
suffix:semicolon
DECL|typedef|flowIn
DECL|typedef|flowInPtr
)brace
id|flowIn
comma
op_star
id|flowInPtr
suffix:semicolon
singleline_comment|//----------------------------------------
singleline_comment|// (Incoming) Status Packets
singleline_comment|//----------------------------------------
singleline_comment|// Incoming packets which are non-data packets are status packets. In this case,
singleline_comment|// the channel number in the header is unimportant. What follows are one or more
singleline_comment|// sub-packets, the first word of which consists of the channel (first or low
singleline_comment|// byte) and the status indicator (second or high byte), followed by possibly
singleline_comment|// more data.
DECL|macro|STAT_CTS_UP
mdefine_line|#define STAT_CTS_UP     0  /* CTS raised  (no other bytes) */
DECL|macro|STAT_CTS_DN
mdefine_line|#define STAT_CTS_DN     1  /* CTS dropped (no other bytes) */
DECL|macro|STAT_DCD_UP
mdefine_line|#define STAT_DCD_UP     2  /* DCD raised  (no other bytes) */
DECL|macro|STAT_DCD_DN
mdefine_line|#define STAT_DCD_DN     3  /* DCD dropped (no other bytes) */
DECL|macro|STAT_DSR_UP
mdefine_line|#define STAT_DSR_UP     4  /* DSR raised  (no other bytes) */
DECL|macro|STAT_DSR_DN
mdefine_line|#define STAT_DSR_DN     5  /* DSR dropped (no other bytes) */
DECL|macro|STAT_RI_UP
mdefine_line|#define STAT_RI_UP      6  /* RI  raised  (no other bytes) */
DECL|macro|STAT_RI_DN
mdefine_line|#define STAT_RI_DN      7  /* RI  dropped (no other bytes) */
DECL|macro|STAT_BRK_DET
mdefine_line|#define STAT_BRK_DET    8  /* BRK detect  (no other bytes) */
DECL|macro|STAT_FLOW
mdefine_line|#define STAT_FLOW       9  /* Flow control(-- more: see below */
DECL|macro|STAT_BMARK
mdefine_line|#define STAT_BMARK      10 /* Bookmark    (no other bytes)&n;&t;&t;&t;&t;&t;&t;&t;* Bookmark is sent as a response to&n;&t;&t;&t;&t;&t;&t;&t;* a command 60: request for bookmark&n;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|STAT_STATUS
mdefine_line|#define STAT_STATUS     11 /* Special packet: see below */
DECL|macro|STAT_TXCNT
mdefine_line|#define STAT_TXCNT      12 /* Special packet: see below */
DECL|macro|STAT_RXCNT
mdefine_line|#define STAT_RXCNT      13 /* Special packet: see below */
DECL|macro|STAT_BOXIDS
mdefine_line|#define STAT_BOXIDS     14 /* Special packet: see below */
DECL|macro|STAT_HWFAIL
mdefine_line|#define STAT_HWFAIL     15 /* Special packet: see below */
DECL|macro|STAT_MOD_ERROR
mdefine_line|#define STAT_MOD_ERROR  0xc0
DECL|macro|STAT_MODEM
mdefine_line|#define STAT_MODEM      0xc0/* If status &amp; STAT_MOD_ERROR:&n;&t;&t;&t;&t;&t;&t;&t; * == STAT_MODEM, then this is a modem&n;&t;&t;&t;&t;&t;&t;&t; * status packet, given in response to a&n;&t;&t;&t;&t;&t;&t;&t; * CMD_DSS_NOW command.&n;&t;&t;&t;&t;&t;&t;&t; * The low nibble has each data signal:&n;&t;&t;&t;&t;&t;&t;&t; */
DECL|macro|STAT_MOD_DCD
mdefine_line|#define STAT_MOD_DCD    0x8
DECL|macro|STAT_MOD_RI
mdefine_line|#define STAT_MOD_RI     0x4
DECL|macro|STAT_MOD_DSR
mdefine_line|#define STAT_MOD_DSR    0x2
DECL|macro|STAT_MOD_CTS
mdefine_line|#define STAT_MOD_CTS    0x1
DECL|macro|STAT_ERROR
mdefine_line|#define STAT_ERROR      0x80/* If status &amp; STAT_MOD_ERROR&n;&t;&t;&t;&t;&t;&t;&t; * == STAT_ERROR, then&n;&t;&t;&t;&t;&t;&t;&t; * sort of error on the channel.&n;&t;&t;&t;&t;&t;&t;&t; * The remaining seven bits indicate&n;&t;&t;&t;&t;&t;&t;&t; * what sort of error it is.&n;&t;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* The low three bits indicate parity, framing, or overrun errors */
DECL|macro|STAT_E_PARITY
mdefine_line|#define STAT_E_PARITY   4     /* Parity error */
DECL|macro|STAT_E_FRAMING
mdefine_line|#define STAT_E_FRAMING  2     /* Framing error */
DECL|macro|STAT_E_OVERRUN
mdefine_line|#define STAT_E_OVERRUN  1     /* (uxart) overrun error */
singleline_comment|//---------------------------------------
singleline_comment|// STAT_FLOW packets
singleline_comment|//---------------------------------------
DECL|struct|_flowStat
r_typedef
r_struct
id|_flowStat
(brace
DECL|member|asof
r_int
r_int
id|asof
suffix:semicolon
DECL|member|room
r_int
r_int
id|room
suffix:semicolon
DECL|typedef|flowStat
DECL|typedef|flowStatPtr
)brace
id|flowStat
comma
op_star
id|flowStatPtr
suffix:semicolon
singleline_comment|// flowStat packets are received from the board to regulate the flow of outgoing
singleline_comment|// data. A local copy of this structure is also kept to track the amount of
singleline_comment|// credits used and credits remaining. &quot;room&quot; is the amount of space in the
singleline_comment|// board&squot;s buffers, &quot;as of&quot; having received a certain byte number. When sending
singleline_comment|// data to the fifo, you must calculate how much buffer space your packet will
singleline_comment|// use.  Add this to the current &quot;asof&quot; and subtract it from the current &quot;room&quot;.
singleline_comment|//
singleline_comment|// The calculation for the board&squot;s buffer is given by CREDIT_USAGE, where size
singleline_comment|// is the un-rounded count of either data characters or command characters.
singleline_comment|// (Which is to say, the count rounded up, plus two).
DECL|macro|CREDIT_USAGE
mdefine_line|#define CREDIT_USAGE(size) (((size) + 3) &amp; ~1)
singleline_comment|//---------------------------------------
singleline_comment|// STAT_STATUS packets
singleline_comment|//---------------------------------------
DECL|struct|_debugStat
r_typedef
r_struct
id|_debugStat
(brace
DECL|member|d_ccsr
r_int
r_char
id|d_ccsr
suffix:semicolon
DECL|member|d_txinh
r_int
r_char
id|d_txinh
suffix:semicolon
DECL|member|d_stat1
r_int
r_char
id|d_stat1
suffix:semicolon
DECL|member|d_stat2
r_int
r_char
id|d_stat2
suffix:semicolon
DECL|typedef|debugStat
DECL|typedef|debugStatPtr
)brace
id|debugStat
comma
op_star
id|debugStatPtr
suffix:semicolon
singleline_comment|// debugStat packets are sent to the host in response to a CMD_GET_STATUS
singleline_comment|// command.  Each byte is bit-mapped as described below:
DECL|macro|D_CCSR_XON
mdefine_line|#define D_CCSR_XON      2     /* Has received XON, ready to transmit */
DECL|macro|D_CCSR_XOFF
mdefine_line|#define D_CCSR_XOFF     4     /* Has received XOFF, not transmitting */
DECL|macro|D_CCSR_TXENAB
mdefine_line|#define D_CCSR_TXENAB   8     /* Transmitter is enabled */
DECL|macro|D_CCSR_RXENAB
mdefine_line|#define D_CCSR_RXENAB   0x80  /* Receiver is enabled */
DECL|macro|D_TXINH_BREAK
mdefine_line|#define D_TXINH_BREAK   1     /* We are sending a break */
DECL|macro|D_TXINH_EMPTY
mdefine_line|#define D_TXINH_EMPTY   2     /* No data to send */
DECL|macro|D_TXINH_SUSP
mdefine_line|#define D_TXINH_SUSP    4     /* Output suspended via command 57 */
DECL|macro|D_TXINH_CMD
mdefine_line|#define D_TXINH_CMD     8     /* We are processing an in-line command */
DECL|macro|D_TXINH_LCD
mdefine_line|#define D_TXINH_LCD     0x10  /* LCD diagnostics are running */
DECL|macro|D_TXINH_PAUSE
mdefine_line|#define D_TXINH_PAUSE   0x20  /* We are processing a PAUSE command */
DECL|macro|D_TXINH_DCD
mdefine_line|#define D_TXINH_DCD     0x40  /* DCD is low, preventing transmission */
DECL|macro|D_TXINH_DSR
mdefine_line|#define D_TXINH_DSR     0x80  /* DSR is low, preventing transmission */
DECL|macro|D_STAT1_TXEN
mdefine_line|#define D_STAT1_TXEN    1     /* Transmit INTERRUPTS enabled */
DECL|macro|D_STAT1_RXEN
mdefine_line|#define D_STAT1_RXEN    2     /* Receiver INTERRUPTS enabled */
DECL|macro|D_STAT1_MDEN
mdefine_line|#define D_STAT1_MDEN    4     /* Modem (data set sigs) interrupts enabled */
DECL|macro|D_STAT1_RLM
mdefine_line|#define D_STAT1_RLM     8     /* Remote loopback mode selected */
DECL|macro|D_STAT1_LLM
mdefine_line|#define D_STAT1_LLM     0x10  /* Local internal loopback mode selected */
DECL|macro|D_STAT1_CTS
mdefine_line|#define D_STAT1_CTS     0x20  /* CTS is low, preventing transmission */
DECL|macro|D_STAT1_DTR
mdefine_line|#define D_STAT1_DTR     0x40  /* DTR is low, to stop remote transmission */
DECL|macro|D_STAT1_RTS
mdefine_line|#define D_STAT1_RTS     0x80  /* RTS is low, to stop remote transmission */
DECL|macro|D_STAT2_TXMT
mdefine_line|#define D_STAT2_TXMT    1     /* Transmit buffers are all empty */
DECL|macro|D_STAT2_RXMT
mdefine_line|#define D_STAT2_RXMT    2     /* Receive buffers are all empty */
DECL|macro|D_STAT2_RXINH
mdefine_line|#define D_STAT2_RXINH   4     /* Loadware has tried to inhibit remote&n;&t;&t;&t;&t;&t;&t;&t;   * transmission:  dropped DTR, sent XOFF,&n;&t;&t;&t;&t;&t;&t;&t;   * whatever...&n;&t;&t;&t;&t;&t;&t;&t;   */
DECL|macro|D_STAT2_RXFLO
mdefine_line|#define D_STAT2_RXFLO   8     /* Loadware can send no more data to host&n;&t;&t;&t;&t;&t;&t;&t;   * until it receives a flow-control packet&n;&t;&t;&t;&t;&t;&t;&t;   */
singleline_comment|//-----------------------------------------
singleline_comment|// STAT_TXCNT and STAT_RXCNT packets
singleline_comment|//----------------------------------------
DECL|struct|_cntStat
r_typedef
r_struct
id|_cntStat
(brace
DECL|member|cs_time
r_int
r_int
id|cs_time
suffix:semicolon
singleline_comment|// (Assumes host is little-endian!)
DECL|member|cs_count
r_int
r_int
id|cs_count
suffix:semicolon
DECL|typedef|cntStat
DECL|typedef|cntStatPtr
)brace
id|cntStat
comma
op_star
id|cntStatPtr
suffix:semicolon
singleline_comment|// These packets are sent in response to a CMD_GET_RXCNT or a CMD_GET_TXCNT
singleline_comment|// bypass command. cs_time is a running 1 Millisecond counter which acts as a
singleline_comment|// time stamp. cs_count is a running counter of data sent or received from the
singleline_comment|// uxarts. (Not including data added by the chip itself, as with CRLF
singleline_comment|// processing).
singleline_comment|//------------------------------------------
singleline_comment|// STAT_HWFAIL packets
singleline_comment|//------------------------------------------
DECL|struct|_failStat
r_typedef
r_struct
id|_failStat
(brace
DECL|member|fs_written
r_int
r_char
id|fs_written
suffix:semicolon
DECL|member|fs_read
r_int
r_char
id|fs_read
suffix:semicolon
DECL|member|fs_address
r_int
r_int
id|fs_address
suffix:semicolon
DECL|typedef|failStat
DECL|typedef|failStatPtr
)brace
id|failStat
comma
op_star
id|failStatPtr
suffix:semicolon
singleline_comment|// This packet is sent whenever the on-board diagnostic process detects an
singleline_comment|// error. At startup, this process is dormant. The host can wake it up by
singleline_comment|// issuing the bypass command CMD_HW_TEST. The process runs at low priority and
singleline_comment|// performs continuous hardware verification; writing data to certain on-board
singleline_comment|// registers, reading it back, and comparing. If it detects an error, this
singleline_comment|// packet is sent to the host, and the process goes dormant again until the host
singleline_comment|// sends another CMD_HW_TEST. It then continues with the next register to be
singleline_comment|// tested.
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// Macros to deal with the headers more easily! Note that these are defined so
singleline_comment|// they may be used as &quot;left&quot; as well as &quot;right&quot; expressions.
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// Given a pointer to the packet, reference the channel number
singleline_comment|//
DECL|macro|CHANNEL_OF
mdefine_line|#define CHANNEL_OF(pP)  ((i2DataHeaderPtr)(pP))-&gt;i2sChannel
singleline_comment|// Given a pointer to the packet, reference the Packet type
singleline_comment|//
DECL|macro|PTYPE_OF
mdefine_line|#define PTYPE_OF(pP) ((i2DataHeaderPtr)(pP))-&gt;i2sType
singleline_comment|// The possible types of packets
singleline_comment|//
DECL|macro|PTYPE_DATA
mdefine_line|#define PTYPE_DATA   0  /* Host &lt;--&gt; Board */
DECL|macro|PTYPE_BYPASS
mdefine_line|#define PTYPE_BYPASS 1  /* Host ---&gt; Board */
DECL|macro|PTYPE_INLINE
mdefine_line|#define PTYPE_INLINE 2  /* Host ---&gt; Board */
DECL|macro|PTYPE_STATUS
mdefine_line|#define PTYPE_STATUS 2  /* Host &lt;--- Board */
singleline_comment|// Given a pointer to a Data packet, reference the Tag
singleline_comment|//
DECL|macro|TAG_OF
mdefine_line|#define TAG_OF(pP) ((i2DataHeaderPtr)(pP))-&gt;i2sTag
singleline_comment|// Given a pointer to a Data packet, reference the data i.d.
singleline_comment|//
DECL|macro|ID_OF
mdefine_line|#define ID_OF(pP)  ((i2DataHeaderPtr)(pP))-&gt;i2sId
singleline_comment|// The possible types of ID&squot;s
singleline_comment|//
DECL|macro|ID_ORDINARY_DATA
mdefine_line|#define ID_ORDINARY_DATA   0
DECL|macro|ID_HOT_KEY
mdefine_line|#define ID_HOT_KEY         1
singleline_comment|// Given a pointer to a Data packet, reference the count
singleline_comment|//
DECL|macro|DATA_COUNT_OF
mdefine_line|#define DATA_COUNT_OF(pP) ((i2DataHeaderPtr)(pP))-&gt;i2sCount
singleline_comment|// Given a pointer to a Data packet, reference the beginning of data
singleline_comment|//
DECL|macro|DATA_OF
mdefine_line|#define DATA_OF(pP) &amp;((unsigned char *)(pP))[4] 
singleline_comment|// 4 = size of header
singleline_comment|// Given a pointer to a Non-Data packet, reference the count
singleline_comment|//
DECL|macro|CMD_COUNT_OF
mdefine_line|#define CMD_COUNT_OF(pP) ((i2CmdHeaderPtr)(pP))-&gt;i2sCount
DECL|macro|MAX_CMD_PACK_SIZE
mdefine_line|#define MAX_CMD_PACK_SIZE  62 
singleline_comment|// Maximum size of such a count
singleline_comment|// Given a pointer to a Non-Data packet, reference the beginning of data
singleline_comment|//
DECL|macro|CMD_OF
mdefine_line|#define CMD_OF(pP) &amp;((unsigned char *)(pP))[2]  
singleline_comment|// 2 = size of header
singleline_comment|//--------------------------------
singleline_comment|// MailBox Bits:
singleline_comment|//--------------------------------
singleline_comment|//--------------------------
singleline_comment|// Outgoing (host to board)
singleline_comment|//--------------------------
singleline_comment|//
DECL|macro|MB_OUT_STUFFED
mdefine_line|#define MB_OUT_STUFFED     0x80  
singleline_comment|// Host has placed output in fifo 
DECL|macro|MB_IN_STRIPPED
mdefine_line|#define MB_IN_STRIPPED     0x40  
singleline_comment|// Host has read in all input from fifo 
singleline_comment|//--------------------------
singleline_comment|// Incoming (board to host)
singleline_comment|//--------------------------
singleline_comment|//
DECL|macro|MB_IN_STUFFED
mdefine_line|#define MB_IN_STUFFED      0x80  
singleline_comment|// Board has placed input in fifo 
DECL|macro|MB_OUT_STRIPPED
mdefine_line|#define MB_OUT_STRIPPED    0x40  
singleline_comment|// Board has read all output from fifo 
DECL|macro|MB_FATAL_ERROR
mdefine_line|#define MB_FATAL_ERROR     0x20  
singleline_comment|// Board has encountered a fatal error
macro_line|#pragma pack(4)                  
singleline_comment|// Reset padding to command-line default
macro_line|#endif      
singleline_comment|// I2PACK_H
eof
