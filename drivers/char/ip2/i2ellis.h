multiline_comment|/*******************************************************************************&n;*&n;*   (c) 1999 by Computone Corporation&n;*&n;********************************************************************************&n;*&n;*&n;*   PACKAGE:     Linux tty Device Driver for IntelliPort II family of multiport&n;*                serial I/O controllers.&n;*&n;*   DESCRIPTION: Mainline code for the device driver&n;*&n;*******************************************************************************/
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// i2ellis.h
singleline_comment|//
singleline_comment|// IntelliPort-II and IntelliPort-IIEX
singleline_comment|//
singleline_comment|// Extremely
singleline_comment|// Low
singleline_comment|// Level
singleline_comment|// Interface
singleline_comment|// Services
singleline_comment|//
singleline_comment|// Structure Definitions and declarations for &quot;ELLIS&quot; service routines found in
singleline_comment|// i2ellis.c
singleline_comment|//
singleline_comment|// These routines are based on properties of the IntelliPort-II and -IIEX
singleline_comment|// hardware and bootstrap firmware, and are not sensitive to particular
singleline_comment|// conventions of any particular loadware.
singleline_comment|//
singleline_comment|// Unlike i2hw.h, which provides IRONCLAD hardware definitions, the material
singleline_comment|// here and in i2ellis.c is intended to provice a useful, but not required,
singleline_comment|// layer of insulation from the hardware specifics.
singleline_comment|//------------------------------------------------------------------------------
macro_line|#ifndef  I2ELLIS_H   /* To prevent multiple includes */
DECL|macro|I2ELLIS_H
mdefine_line|#define  I2ELLIS_H   1
singleline_comment|//------------------------------------------------
singleline_comment|// Revision History:
singleline_comment|//
singleline_comment|// 30 September 1991 MAG First Draft Started
singleline_comment|// 12 October   1991 ...continued...
singleline_comment|//
singleline_comment|// 20 December  1996 AKM Linux version
singleline_comment|//-------------------------------------------------
singleline_comment|//----------------------
singleline_comment|// Mandatory Includes:
singleline_comment|//----------------------
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;ip2types.h&quot;
macro_line|#include &quot;i2hw.h&quot;       
singleline_comment|// The hardware definitions
singleline_comment|//------------------------------------------
singleline_comment|// STAT_BOXIDS packets
singleline_comment|//------------------------------------------
DECL|macro|MAX_BOX
mdefine_line|#define MAX_BOX&t;&t;4
DECL|struct|_bidStat
r_typedef
r_struct
id|_bidStat
(brace
DECL|member|bid_value
r_int
r_char
id|bid_value
(braket
id|MAX_BOX
)braket
suffix:semicolon
DECL|typedef|bidStat
DECL|typedef|bidStatPtr
)brace
id|bidStat
comma
op_star
id|bidStatPtr
suffix:semicolon
singleline_comment|// This packet is sent in response to a CMD_GET_BOXIDS bypass command. For -IIEX
singleline_comment|// boards, reports the hardware-specific &quot;asynchronous resource register&quot; on
singleline_comment|// each expansion box. Boxes not present report 0xff. For -II boards, the first
singleline_comment|// element contains 0x80 for 8-port, 0x40 for 4-port boards.
singleline_comment|// Box IDs aka ARR or Async Resource Register (more than you want to know)
singleline_comment|//   7   6   5   4   3   2   1   0
singleline_comment|//   F   F   N   N   L   S   S   S
singleline_comment|//   =============================
singleline_comment|//   F   F   -  Product Family Designator
singleline_comment|//   =====+++++++++++++++++++++++++++++++
singleline_comment|//   0   0   -  Intelliport II EX / ISA-8
singleline_comment|//   1   0   -  IntelliServer
singleline_comment|//   0   1   -  SAC - Port Device (Intelliport III ??? )
singleline_comment|//           =====+++++++++++++++++++++++++++++++++++++++
singleline_comment|//           N   N   -  Number of Ports
singleline_comment|//           0   0   -  8  (eight)
singleline_comment|//           0   1   -  4  (four)
singleline_comment|//           1   0   -  12 (twelve)
singleline_comment|//           1   1   -  16 (sixteen)
singleline_comment|//                   =++++++++++++++++++++++++++++++++++
singleline_comment|//                   L  -   LCD Display Module Present
singleline_comment|//                   0  -   No
singleline_comment|//                   1  -   LCD module present
singleline_comment|//                   =========+++++++++++++++++++++++++++++++++++++
singleline_comment|//                      S   S   S - Async Signals Supported Designator
singleline_comment|//                      0   0   0 - 8dss, Mod DCE DB25 Female
singleline_comment|//                      0   0   1 - 6dss, RJ-45
singleline_comment|//                      0   1   0 - RS-232/422 dss, DB25 Female
singleline_comment|//                      0   1   1 - RS-232/422 dss, separate 232/422 DB25 Female
singleline_comment|//                      1   0   0 - 6dss, 921.6 I/F with ST654&squot;s
singleline_comment|//                      1   0   1 - RS-423/232 8dss, RJ-45 10Pin
singleline_comment|//                      1   1   0 - 6dss, Mod DCE DB25 Female
singleline_comment|//                      1   1   1 - NO BOX PRESENT
DECL|macro|FF
mdefine_line|#define FF(c)&t;((c &amp; 0xC0) &gt;&gt; 6)
DECL|macro|NN
mdefine_line|#define NN(c)&t;((c &amp; 0x30) &gt;&gt; 4)
DECL|macro|L
mdefine_line|#define L(c)&t;((c &amp; 0x08) &gt;&gt; 3)
DECL|macro|SSS
mdefine_line|#define SSS(c)&t; (c &amp; 0x07)
DECL|macro|BID_HAS_654
mdefine_line|#define BID_HAS_654(x)&t;(SSS(x) == 0x04)
DECL|macro|BID_NO_BOX
mdefine_line|#define BID_NO_BOX&t;0xff /* no box */
DECL|macro|BID_8PORT
mdefine_line|#define BID_8PORT  &t;0x80 /* IP2-8 port */
DECL|macro|BID_4PORT
mdefine_line|#define BID_4PORT   &t;0x81 /* IP2-4 port */
DECL|macro|BID_EXP_MASK
mdefine_line|#define BID_EXP_MASK   &t;0x30 /* IP2-EX  */
DECL|macro|BID_EXP_8PORT
mdefine_line|#define BID_EXP_8PORT&t;0x00 /*     8, */
DECL|macro|BID_EXP_4PORT
mdefine_line|#define BID_EXP_4PORT&t;0x10 /*     4, */
DECL|macro|BID_EXP_UNDEF
mdefine_line|#define BID_EXP_UNDEF&t;0x20 /*     UNDEF, */
DECL|macro|BID_EXP_16PORT
mdefine_line|#define BID_EXP_16PORT&t;0x30 /*    16, */
DECL|macro|BID_LCD_CTRL
mdefine_line|#define BID_LCD_CTRL   &t;0x08 /* LCD Controller */
DECL|macro|BID_LCD_NONE
mdefine_line|#define BID_LCD_NONE&t;0x00 /* - no controller present */
DECL|macro|BID_LCD_PRES
mdefine_line|#define BID_LCD_PRES   &t;0x08 /* - controller present */
DECL|macro|BID_CON_MASK
mdefine_line|#define BID_CON_MASK&t;0x07 /* - connector pinouts */
DECL|macro|BID_CON_DB25
mdefine_line|#define BID_CON_DB25&t;0x00 /* - DB-25 F */
DECL|macro|BID_CON_RJ45
mdefine_line|#define BID_CON_RJ45&t;0x01 /* - rj45 */
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// i2eBordStr
singleline_comment|//
singleline_comment|// This structure contains all the information the ELLIS routines require in
singleline_comment|// dealing with a particular board.
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// There are some queues here which are guaranteed to never contain the entry
singleline_comment|// for a single channel twice. So they must be slightly larger to allow
singleline_comment|// unambiguous full/empty management
singleline_comment|//
DECL|macro|CH_QUEUE_SIZE
mdefine_line|#define CH_QUEUE_SIZE ABS_MOST_PORTS+2
DECL|struct|_i2eBordStr
r_typedef
r_struct
id|_i2eBordStr
(brace
DECL|member|i2ePom
id|porStr
id|i2ePom
suffix:semicolon
singleline_comment|// Structure containing the power-on message.
DECL|member|i2ePomSize
r_int
r_int
id|i2ePomSize
suffix:semicolon
singleline_comment|// The number of bytes actually read if
singleline_comment|// different from sizeof i2ePom, indicates
singleline_comment|// there is an error!
DECL|member|i2eStartMail
r_int
r_int
id|i2eStartMail
suffix:semicolon
singleline_comment|// Contains whatever inbound mailbox data
singleline_comment|// present at startup. NO_MAIL_HERE indicates
singleline_comment|// nothing was present. No special
singleline_comment|// significance as of this writing, but may be
singleline_comment|// useful for diagnostic reasons.
DECL|member|i2eValid
r_int
r_int
id|i2eValid
suffix:semicolon
singleline_comment|// Indicates validity of the structure; if
singleline_comment|// i2eValid == I2E_MAGIC, then we can trust
singleline_comment|// the other fields. Some (especially
singleline_comment|// initialization) functions are good about
singleline_comment|// checking for validity.  Many functions do
singleline_comment|// not, it being assumed that the larger
singleline_comment|// context assures we are using a valid
singleline_comment|// i2eBordStrPtr.
DECL|member|i2eError
r_int
r_int
id|i2eError
suffix:semicolon
singleline_comment|// Used for returning an error condition from
singleline_comment|// several functions which use i2eBordStrPtr
singleline_comment|// as an argument.
singleline_comment|// Accelerators to characterize separate features of a board, derived from a
singleline_comment|// number of sources.
DECL|member|i2eFifoSize
r_int
r_int
id|i2eFifoSize
suffix:semicolon
singleline_comment|// Always, the size of the FIFO. For
singleline_comment|// IntelliPort-II, always the same, for -IIEX
singleline_comment|// taken from the Power-On reset message.
r_volatile
DECL|member|i2eFifoRemains
r_int
r_int
id|i2eFifoRemains
suffix:semicolon
singleline_comment|// Used during normal operation to indicate a
singleline_comment|// lower bound on the amount of data which
singleline_comment|// might be in the outbound fifo.
DECL|member|i2eFifoStyle
r_int
r_char
id|i2eFifoStyle
suffix:semicolon
singleline_comment|// Accelerator which tells which style (-II or
singleline_comment|// -IIEX) FIFO we are using.
DECL|member|i2eDataWidth16
r_int
r_char
id|i2eDataWidth16
suffix:semicolon
singleline_comment|// Accelerator which tells whether we should
singleline_comment|// do 8 or 16-bit data transfers.
DECL|member|i2eMaxIrq
r_int
r_char
id|i2eMaxIrq
suffix:semicolon
singleline_comment|// The highest allowable IRQ, based on the
singleline_comment|// slot size.
DECL|member|i2eChangeIrq
r_int
r_char
id|i2eChangeIrq
suffix:semicolon
singleline_comment|// Whether tis valid to change IRQ&squot;s
singleline_comment|// ISA = ok, EISA, MicroChannel, no
singleline_comment|// Accelerators for various addresses on the board
DECL|member|i2eBase
r_int
id|i2eBase
suffix:semicolon
singleline_comment|// I/O Address of the Board
DECL|member|i2eData
r_int
id|i2eData
suffix:semicolon
singleline_comment|// From here data transfers happen
DECL|member|i2eStatus
r_int
id|i2eStatus
suffix:semicolon
singleline_comment|// From here status reads happen
DECL|member|i2ePointer
r_int
id|i2ePointer
suffix:semicolon
singleline_comment|// (IntelliPort-II: pointer/commands)
DECL|member|i2eXMail
r_int
id|i2eXMail
suffix:semicolon
singleline_comment|// (IntelliPOrt-IIEX: mailboxes
DECL|member|i2eXMask
r_int
id|i2eXMask
suffix:semicolon
singleline_comment|// (IntelliPort-IIEX: mask write
singleline_comment|//-------------------------------------------------------
singleline_comment|// Information presented in a common format across boards
singleline_comment|// For each box, bit map of the channels present.  Box closest to 
singleline_comment|// the host is box 0. LSB is channel 0. IntelliPort-II (non-expandable)
singleline_comment|// is taken to be box 0. These are derived from product i.d. registers.
DECL|member|i2eChannelMap
r_int
r_int
id|i2eChannelMap
(braket
id|ABS_MAX_BOXES
)braket
suffix:semicolon
singleline_comment|// Same as above, except each is derived from firmware attempting to detect
singleline_comment|// the uart presence (by reading a valid GFRCR register). If bits are set in
singleline_comment|// i2eChannelMap and not in i2eGoodMap, there is a potential problem.
DECL|member|i2eGoodMap
r_int
r_int
id|i2eGoodMap
(braket
id|ABS_MAX_BOXES
)braket
suffix:semicolon
singleline_comment|// ---------------------------
singleline_comment|// For indirect function calls
singleline_comment|// Routine to cause an N-millisecond delay: Patched by the ii2Initialize
singleline_comment|// function.
DECL|member|i2eDelay
r_void
(paren
op_star
id|i2eDelay
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
singleline_comment|// Routine to write N bytes to the board through the FIFO. Returns true if
singleline_comment|// all copacetic, otherwise returns false and error is in i2eError field.
singleline_comment|// IF COUNT IS ODD, ROUNDS UP TO THE NEXT EVEN NUMBER.
DECL|member|i2eWriteBuf
r_int
(paren
op_star
id|i2eWriteBuf
)paren
(paren
r_struct
id|_i2eBordStr
op_star
comma
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
singleline_comment|// Routine to read N bytes from the board through the FIFO. Returns true if
singleline_comment|// copacetic, otherwise returns false and error in i2eError.
singleline_comment|// IF COUNT IS ODD, ROUNDS UP TO THE NEXT EVEN NUMBER.
DECL|member|i2eReadBuf
r_int
(paren
op_star
id|i2eReadBuf
)paren
(paren
r_struct
id|_i2eBordStr
op_star
comma
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
singleline_comment|// Returns a word from FIFO. Will use 2 byte operations if needed.
DECL|member|i2eReadWord
r_int
r_int
(paren
op_star
id|i2eReadWord
)paren
(paren
r_struct
id|_i2eBordStr
op_star
)paren
suffix:semicolon
singleline_comment|// Writes a word to FIFO. Will use 2 byte operations if needed.
DECL|member|i2eWriteWord
r_void
(paren
op_star
id|i2eWriteWord
)paren
(paren
r_struct
id|_i2eBordStr
op_star
comma
r_int
r_int
)paren
suffix:semicolon
singleline_comment|// Waits specified time for the Transmit FIFO to go empty. Returns true if
singleline_comment|//  ok, otherwise returns false and error in i2eError.
DECL|member|i2eWaitForTxEmpty
r_int
(paren
op_star
id|i2eWaitForTxEmpty
)paren
(paren
r_struct
id|_i2eBordStr
op_star
comma
r_int
)paren
suffix:semicolon
singleline_comment|// Returns true or false according to whether the outgoing mailbox is empty.
DECL|member|i2eTxMailEmpty
r_int
(paren
op_star
id|i2eTxMailEmpty
)paren
(paren
r_struct
id|_i2eBordStr
op_star
)paren
suffix:semicolon
singleline_comment|// Checks whether outgoing mailbox is empty.  If so, sends mail and returns
singleline_comment|// true.  Otherwise returns false.
DECL|member|i2eTrySendMail
r_int
(paren
op_star
id|i2eTrySendMail
)paren
(paren
r_struct
id|_i2eBordStr
op_star
comma
r_int
r_char
)paren
suffix:semicolon
singleline_comment|// If no mail available, returns NO_MAIL_HERE, else returns the value in the
singleline_comment|// mailbox (guaranteed can&squot;t be NO_MAIL_HERE).
DECL|member|i2eGetMail
r_int
r_int
(paren
op_star
id|i2eGetMail
)paren
(paren
r_struct
id|_i2eBordStr
op_star
)paren
suffix:semicolon
singleline_comment|// Enables the board to interrupt the host when it writes to the mailbox.
singleline_comment|// Irqs will not occur, however, until the loadware separately enables
singleline_comment|// interrupt generation to the host.  The standard loadware does this in
singleline_comment|// response to a command packet sent by the host. (Also, disables
singleline_comment|// any other potential interrupt sources from the board -- other than the
singleline_comment|// inbound mailbox).
DECL|member|i2eEnableMailIrq
r_void
(paren
op_star
id|i2eEnableMailIrq
)paren
(paren
r_struct
id|_i2eBordStr
op_star
)paren
suffix:semicolon
singleline_comment|// Writes an arbitrary value to the mask register.
DECL|member|i2eWriteMask
r_void
(paren
op_star
id|i2eWriteMask
)paren
(paren
r_struct
id|_i2eBordStr
op_star
comma
r_int
r_char
)paren
suffix:semicolon
singleline_comment|// State information
singleline_comment|// During downloading, indicates the number of blocks remaining to download
singleline_comment|// to the board.
DECL|member|i2eToLoad
r_int
id|i2eToLoad
suffix:semicolon
singleline_comment|// State of board (see manifests below) (e.g., whether in reset condition,
singleline_comment|// whether standard loadware is installed, etc.
DECL|member|i2eState
r_int
r_char
id|i2eState
suffix:semicolon
singleline_comment|// These three fields are only valid when there is loadware running on the
singleline_comment|// board. (i2eState == II_STATE_LOADED or i2eState == II_STATE_STDLOADED )
DECL|member|i2eLVersion
r_int
r_char
id|i2eLVersion
suffix:semicolon
singleline_comment|// Loadware version
DECL|member|i2eLRevision
r_int
r_char
id|i2eLRevision
suffix:semicolon
singleline_comment|// Loadware revision
DECL|member|i2eLSub
r_int
r_char
id|i2eLSub
suffix:semicolon
singleline_comment|// Loadware subrevision
singleline_comment|// Flags which only have meaning in the context of the standard loadware.
singleline_comment|// Somewhat violates the layering concept, but there is so little additional
singleline_comment|// needed at the board level (while much additional at the channel level),
singleline_comment|// that this beats maintaining two different per-board structures.
singleline_comment|// Indicates which IRQ the board has been initialized (from software) to use
singleline_comment|// For MicroChannel boards, any value different from IRQ_UNDEFINED means
singleline_comment|// that the software command has been sent to enable interrupts (or specify
singleline_comment|// they are disabled). Special value: IRQ_UNDEFINED indicates that the
singleline_comment|// software command to select the interrupt has not yet been sent, therefore
singleline_comment|// (since the standard loadware insists that it be sent before any other
singleline_comment|// packets are sent) no other packets should be sent yet.
DECL|member|i2eUsingIrq
r_int
r_int
id|i2eUsingIrq
suffix:semicolon
singleline_comment|// This is set when we hit the MB_OUT_STUFFED mailbox, which prevents us
singleline_comment|// putting more in the mailbox until an appropriate mailbox message is
singleline_comment|// received.
DECL|member|i2eWaitingForEmptyFifo
r_int
r_char
id|i2eWaitingForEmptyFifo
suffix:semicolon
singleline_comment|// Any mailbox bits waiting to be sent to the board are OR&squot;ed in here.
DECL|member|i2eOutMailWaiting
r_int
r_char
id|i2eOutMailWaiting
suffix:semicolon
singleline_comment|// The head of any incoming packet is read into here, is then examined and 
singleline_comment|// we dispatch accordingly.
DECL|member|i2eLeadoffWord
r_int
r_int
id|i2eLeadoffWord
(braket
l_int|1
)braket
suffix:semicolon
singleline_comment|// Running counter of interrupts where the mailbox indicated incoming data.
DECL|member|i2eFifoInInts
r_int
r_int
id|i2eFifoInInts
suffix:semicolon
singleline_comment|// Running counter of interrupts where the mailbox indicated outgoing data
singleline_comment|// had been stripped.
DECL|member|i2eFifoOutInts
r_int
r_int
id|i2eFifoOutInts
suffix:semicolon
singleline_comment|// If not void, gives the address of a routine to call if fatal board error
singleline_comment|// is found (only applies to standard l/w).
DECL|member|i2eFatalTrap
r_void
(paren
op_star
id|i2eFatalTrap
)paren
(paren
r_struct
id|_i2eBordStr
op_star
)paren
suffix:semicolon
singleline_comment|// Will point to an array of some sort of channel structures (whose format
singleline_comment|// is unknown at this level, being a function of what loadware is
singleline_comment|// installed and the code configuration (max sizes of buffers, etc.)).
DECL|member|i2eChannelPtr
r_void
op_star
id|i2eChannelPtr
suffix:semicolon
singleline_comment|// Set indicates that the board has gone fatal.
DECL|member|i2eFatal
r_int
r_int
id|i2eFatal
suffix:semicolon
singleline_comment|// The number of elements pointed to by i2eChannelPtr.
DECL|member|i2eChannelCnt
r_int
r_int
id|i2eChannelCnt
suffix:semicolon
singleline_comment|// Ring-buffers of channel structures whose channels have particular needs.
DECL|member|Fbuf_spinlock
id|rwlock_t
id|Fbuf_spinlock
suffix:semicolon
r_volatile
DECL|member|i2Fbuf_strip
r_int
r_int
id|i2Fbuf_strip
suffix:semicolon
singleline_comment|// Strip index
r_volatile
DECL|member|i2Fbuf_stuff
r_int
r_int
id|i2Fbuf_stuff
suffix:semicolon
singleline_comment|// Stuff index
DECL|member|i2Fbuf
r_void
op_star
id|i2Fbuf
(braket
id|CH_QUEUE_SIZE
)braket
suffix:semicolon
singleline_comment|// An array of channel pointers
singleline_comment|// of channels who need to send
singleline_comment|// flow control packets.
DECL|member|Dbuf_spinlock
id|rwlock_t
id|Dbuf_spinlock
suffix:semicolon
r_volatile
DECL|member|i2Dbuf_strip
r_int
r_int
id|i2Dbuf_strip
suffix:semicolon
singleline_comment|// Strip index
r_volatile
DECL|member|i2Dbuf_stuff
r_int
r_int
id|i2Dbuf_stuff
suffix:semicolon
singleline_comment|// Stuff index
DECL|member|i2Dbuf
r_void
op_star
id|i2Dbuf
(braket
id|CH_QUEUE_SIZE
)braket
suffix:semicolon
singleline_comment|// An array of channel pointers
singleline_comment|// of channels who need to send
singleline_comment|// data or in-line command packets.
DECL|member|Bbuf_spinlock
id|rwlock_t
id|Bbuf_spinlock
suffix:semicolon
r_volatile
DECL|member|i2Bbuf_strip
r_int
r_int
id|i2Bbuf_strip
suffix:semicolon
singleline_comment|// Strip index
r_volatile
DECL|member|i2Bbuf_stuff
r_int
r_int
id|i2Bbuf_stuff
suffix:semicolon
singleline_comment|// Stuff index
DECL|member|i2Bbuf
r_void
op_star
id|i2Bbuf
(braket
id|CH_QUEUE_SIZE
)braket
suffix:semicolon
singleline_comment|// An array of channel pointers
singleline_comment|// of channels who need to send
singleline_comment|// bypass command packets.
multiline_comment|/*&n;&t; * A set of flags to indicate that certain events have occurred on at least&n;&t; * one of the ports on this board. We use this to decide whether to spin&n;&t; * through the channels looking for breaks, etc.&n;&t; */
DECL|member|got_input
r_int
id|got_input
suffix:semicolon
DECL|member|status_change
r_int
id|status_change
suffix:semicolon
DECL|member|channelBtypes
id|bidStat
id|channelBtypes
suffix:semicolon
multiline_comment|/*&n;&t; * Debugging counters, etc.&n;&t; */
DECL|member|debugFlowQueued
r_int
r_int
id|debugFlowQueued
suffix:semicolon
DECL|member|debugInlineQueued
r_int
r_int
id|debugInlineQueued
suffix:semicolon
DECL|member|debugDataQueued
r_int
r_int
id|debugDataQueued
suffix:semicolon
DECL|member|debugBypassQueued
r_int
r_int
id|debugBypassQueued
suffix:semicolon
DECL|member|debugFlowCount
r_int
r_int
id|debugFlowCount
suffix:semicolon
DECL|member|debugInlineCount
r_int
r_int
id|debugInlineCount
suffix:semicolon
DECL|member|debugBypassCount
r_int
r_int
id|debugBypassCount
suffix:semicolon
DECL|member|read_fifo_spinlock
id|rwlock_t
id|read_fifo_spinlock
suffix:semicolon
DECL|member|write_fifo_spinlock
id|rwlock_t
id|write_fifo_spinlock
suffix:semicolon
singleline_comment|//&t;For queuing interupt bottom half handlers.&t;/&bslash;/&bslash;|=mhw=|&bslash;/&bslash;/
DECL|member|tqueue_interrupt
r_struct
id|tq_struct
id|tqueue_interrupt
suffix:semicolon
DECL|member|SendPendingTimer
r_struct
id|timer_list
id|SendPendingTimer
suffix:semicolon
singleline_comment|// Used by iiSendPending
DECL|member|SendPendingRetry
r_int
r_int
id|SendPendingRetry
suffix:semicolon
macro_line|#ifdef&t;CONFIG_DEVFS_FS
multiline_comment|/* Device handles into devfs */
DECL|member|devfs_ipl_handle
id|devfs_handle_t
id|devfs_ipl_handle
suffix:semicolon
DECL|member|devfs_stat_handle
id|devfs_handle_t
id|devfs_stat_handle
suffix:semicolon
macro_line|#endif
DECL|typedef|i2eBordStr
DECL|typedef|i2eBordStrPtr
)brace
id|i2eBordStr
comma
op_star
id|i2eBordStrPtr
suffix:semicolon
singleline_comment|//-------------------------------------------------------------------
singleline_comment|// Macro Definitions for the indirect calls defined in the i2eBordStr
singleline_comment|//-------------------------------------------------------------------
singleline_comment|//
DECL|macro|iiDelay
mdefine_line|#define iiDelay(a,b)          (*(a)-&gt;i2eDelay)(b)
DECL|macro|iiWriteBuf
mdefine_line|#define iiWriteBuf(a,b,c)     (*(a)-&gt;i2eWriteBuf)(a,b,c)
DECL|macro|iiReadBuf
mdefine_line|#define iiReadBuf(a,b,c)      (*(a)-&gt;i2eReadBuf)(a,b,c)
DECL|macro|iiWriteWord
mdefine_line|#define iiWriteWord(a,b)      (*(a)-&gt;i2eWriteWord)(a,b)
DECL|macro|iiReadWord
mdefine_line|#define iiReadWord(a)         (*(a)-&gt;i2eReadWord)(a)
DECL|macro|iiWaitForTxEmpty
mdefine_line|#define iiWaitForTxEmpty(a,b) (*(a)-&gt;i2eWaitForTxEmpty)(a,b)
DECL|macro|iiTxMailEmpty
mdefine_line|#define iiTxMailEmpty(a)      (*(a)-&gt;i2eTxMailEmpty)(a)
DECL|macro|iiTrySendMail
mdefine_line|#define iiTrySendMail(a,b)    (*(a)-&gt;i2eTrySendMail)(a,b)
DECL|macro|iiGetMail
mdefine_line|#define iiGetMail(a)          (*(a)-&gt;i2eGetMail)(a)
DECL|macro|iiEnableMailIrq
mdefine_line|#define iiEnableMailIrq(a)    (*(a)-&gt;i2eEnableMailIrq)(a)
DECL|macro|iiDisableMailIrq
mdefine_line|#define iiDisableMailIrq(a)   (*(a)-&gt;i2eWriteMask)(a,0)
DECL|macro|iiWriteMask
mdefine_line|#define iiWriteMask(a,b)      (*(a)-&gt;i2eWriteMask)(a,b)
singleline_comment|//-------------------------------------------
singleline_comment|// Manifests for i2eBordStr:
singleline_comment|//-------------------------------------------
DECL|macro|YES
mdefine_line|#define YES 1
DECL|macro|NO
mdefine_line|#define NO  0
DECL|macro|NULLFUNC
mdefine_line|#define NULLFUNC (void (*)(void))0
DECL|macro|NULLPTR
mdefine_line|#define NULLPTR (void *)0
DECL|typedef|delayFunc_t
r_typedef
r_void
(paren
op_star
id|delayFunc_t
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
singleline_comment|// i2eValid
singleline_comment|//
DECL|macro|I2E_MAGIC
mdefine_line|#define I2E_MAGIC       0x4251   
singleline_comment|// Structure is valid.
DECL|macro|I2E_INCOMPLETE
mdefine_line|#define I2E_INCOMPLETE  0x1122   
singleline_comment|// Structure failed during init.
singleline_comment|// i2eError
singleline_comment|//
DECL|macro|I2EE_GOOD
mdefine_line|#define I2EE_GOOD       0&t;
singleline_comment|// Operation successful
DECL|macro|I2EE_BADADDR
mdefine_line|#define I2EE_BADADDR    1&t;
singleline_comment|// Address out of range
DECL|macro|I2EE_BADSTATE
mdefine_line|#define I2EE_BADSTATE   2&t;
singleline_comment|// Attempt to perform a function when the board
singleline_comment|// structure was in the incorrect state
DECL|macro|I2EE_BADMAGIC
mdefine_line|#define I2EE_BADMAGIC   3&t;
singleline_comment|// Bad magic number from Power On test (i2ePomSize
singleline_comment|// reflects what was read
DECL|macro|I2EE_PORM_SHORT
mdefine_line|#define I2EE_PORM_SHORT 4&t;
singleline_comment|// Power On message too short
DECL|macro|I2EE_PORM_LONG
mdefine_line|#define I2EE_PORM_LONG  5&t;
singleline_comment|// Power On message too long
DECL|macro|I2EE_BAD_FAMILY
mdefine_line|#define I2EE_BAD_FAMILY 6&t;
singleline_comment|// Un-supported board family type
DECL|macro|I2EE_INCONSIST
mdefine_line|#define I2EE_INCONSIST  7&t;
singleline_comment|// Firmware reports something impossible,
singleline_comment|// e.g. unexpected number of ports... Almost no
singleline_comment|// excuse other than bad FIFO...
DECL|macro|I2EE_POSTERR
mdefine_line|#define I2EE_POSTERR    8&t;
singleline_comment|// Power-On self test reported a bad error
DECL|macro|I2EE_BADBUS
mdefine_line|#define I2EE_BADBUS     9&t;
singleline_comment|// Unknown Bus type declared in message
DECL|macro|I2EE_TXE_TIME
mdefine_line|#define I2EE_TXE_TIME   10&t;
singleline_comment|// Timed out waiting for TX Fifo to empty
DECL|macro|I2EE_INVALID
mdefine_line|#define I2EE_INVALID    11&t;
singleline_comment|// i2eValid field does not indicate a valid and
singleline_comment|// complete board structure (for functions which
singleline_comment|// require this be so.)
DECL|macro|I2EE_BAD_PORT
mdefine_line|#define I2EE_BAD_PORT   12&t;
singleline_comment|// Discrepancy between channels actually found and
singleline_comment|// what the product is supposed to have. Check
singleline_comment|// i2eGoodMap vs i2eChannelMap for details.
DECL|macro|I2EE_BAD_IRQ
mdefine_line|#define I2EE_BAD_IRQ    13&t;
singleline_comment|// Someone specified an unsupported IRQ
DECL|macro|I2EE_NOCHANNELS
mdefine_line|#define I2EE_NOCHANNELS 14&t;
singleline_comment|// No channel structures have been defined (for
singleline_comment|// functions requiring this).
singleline_comment|// i2eFifoStyle
singleline_comment|//
DECL|macro|FIFO_II
mdefine_line|#define FIFO_II   0  /* IntelliPort-II style: see also i2hw.h */
DECL|macro|FIFO_IIEX
mdefine_line|#define FIFO_IIEX 1  /* IntelliPort-IIEX style */
singleline_comment|// i2eGetMail
singleline_comment|//
DECL|macro|NO_MAIL_HERE
mdefine_line|#define NO_MAIL_HERE    0x1111&t;
singleline_comment|// Since mail is unsigned char, cannot possibly
singleline_comment|// promote to 0x1111.
singleline_comment|// i2eState
singleline_comment|//
DECL|macro|II_STATE_COLD
mdefine_line|#define II_STATE_COLD      0  
singleline_comment|// Addresses have been defined, but board not even
singleline_comment|// reset yet.
DECL|macro|II_STATE_RESET
mdefine_line|#define II_STATE_RESET     1  
singleline_comment|// Board,if it exists, has just been reset
DECL|macro|II_STATE_READY
mdefine_line|#define II_STATE_READY     2  
singleline_comment|// Board ready for its first block
DECL|macro|II_STATE_LOADING
mdefine_line|#define II_STATE_LOADING   3  
singleline_comment|// Board continuing load
DECL|macro|II_STATE_LOADED
mdefine_line|#define II_STATE_LOADED    4  
singleline_comment|// Board has finished load: status ok
DECL|macro|II_STATE_BADLOAD
mdefine_line|#define II_STATE_BADLOAD   5  
singleline_comment|// Board has finished load: failed!
DECL|macro|II_STATE_STDLOADED
mdefine_line|#define II_STATE_STDLOADED 6  
singleline_comment|// Board has finished load: standard firmware
singleline_comment|// i2eUsingIrq
singleline_comment|//
DECL|macro|IRQ_UNDEFINED
mdefine_line|#define IRQ_UNDEFINED   0x1352  
singleline_comment|// No valid irq (or polling = 0) can ever
singleline_comment|// promote to this!
singleline_comment|//------------------------------------------
singleline_comment|// Handy Macros for i2ellis.c and others
singleline_comment|// Note these are common to -II and -IIEX
singleline_comment|//------------------------------------------
singleline_comment|// Given a pointer to the board structure, does the input FIFO have any data or
singleline_comment|// not?
singleline_comment|//
DECL|macro|HAS_INPUT
mdefine_line|#define HAS_INPUT(pB)      !(INB(pB-&gt;i2eStatus) &amp; ST_IN_EMPTY)
DECL|macro|HAS_NO_INPUT
mdefine_line|#define HAS_NO_INPUT(pB)   (INB(pB-&gt;i2eStatus) &amp; ST_IN_EMPTY)
singleline_comment|// Given a pointer to board structure, read a byte or word from the fifo
singleline_comment|//
DECL|macro|BYTE_FROM
mdefine_line|#define BYTE_FROM(pB)      (unsigned char)INB(pB-&gt;i2eData)
DECL|macro|WORD_FROM
mdefine_line|#define WORD_FROM(pB)      (unsigned short)INW(pB-&gt;i2eData)
singleline_comment|// Given a pointer to board structure, is there room for any data to be written
singleline_comment|// to the data fifo?
singleline_comment|//
DECL|macro|HAS_OUTROOM
mdefine_line|#define HAS_OUTROOM(pB)    !(INB(pB-&gt;i2eStatus) &amp; ST_OUT_FULL)
DECL|macro|HAS_NO_OUTROOM
mdefine_line|#define HAS_NO_OUTROOM(pB) (INB(pB-&gt;i2eStatus) &amp; ST_OUT_FULL)
singleline_comment|// Given a pointer to board structure, write a single byte to the fifo
singleline_comment|// structure. Note that for 16-bit interfaces, the high order byte is undefined
singleline_comment|// and unknown.
singleline_comment|//
DECL|macro|BYTE_TO
mdefine_line|#define BYTE_TO(pB, c)     OUTB(pB-&gt;i2eData,(c))
singleline_comment|// Write a word to the fifo structure. For 8-bit interfaces, this may have
singleline_comment|// unknown results.
singleline_comment|//
DECL|macro|WORD_TO
mdefine_line|#define WORD_TO(pB, c)     OUTW(pB-&gt;i2eData,(c))
singleline_comment|// Given a pointer to the board structure, is there anything in the incoming
singleline_comment|// mailbox?
singleline_comment|//
DECL|macro|HAS_MAIL
mdefine_line|#define HAS_MAIL(pB)       (INB(pB-&gt;i2eStatus) &amp; ST_IN_MAIL)
DECL|macro|UPDATE_FIFO_ROOM
mdefine_line|#define UPDATE_FIFO_ROOM(pB)  (pB)-&gt;i2eFifoRemains=(pB)-&gt;i2eFifoSize
singleline_comment|// Handy macro to round up a number (like the buffer write and read routines do)
singleline_comment|// 
DECL|macro|ROUNDUP
mdefine_line|#define ROUNDUP(number)    (((number)+1) &amp; (~1))
singleline_comment|//------------------------------------------
singleline_comment|// Function Declarations for i2ellis.c
singleline_comment|//------------------------------------------
singleline_comment|//
singleline_comment|// Functions called directly
singleline_comment|//
singleline_comment|// Initialization of a board &amp; structure is in four (five!) parts:
singleline_comment|//
singleline_comment|// 0) iiEllisInit()  - Initialize iiEllis subsystem.
singleline_comment|// 1) iiSetAddress() - Define the board address &amp; delay function for a board.
singleline_comment|// 2) iiReset()      - Reset the board   (provided it exists)
singleline_comment|//       -- Note you may do this to several boards --
singleline_comment|// 3) iiResetDelay() - Delay for 2 seconds (once for all boards)
singleline_comment|// 4) iiInitialize() - Attempt to read Power-up message; further initialize
singleline_comment|//                     accelerators
singleline_comment|//
singleline_comment|// Then you may use iiDownloadAll() or iiDownloadFile() (in i2file.c) to write
singleline_comment|// loadware.  To change loadware, you must begin again with step 2, resetting
singleline_comment|// the board again (step 1 not needed).
r_static
r_void
id|iiEllisInit
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|iiSetAddress
c_func
(paren
id|i2eBordStrPtr
comma
r_int
comma
id|delayFunc_t
)paren
suffix:semicolon
r_static
r_int
id|iiReset
c_func
(paren
id|i2eBordStrPtr
)paren
suffix:semicolon
r_static
r_int
id|iiResetDelay
c_func
(paren
id|i2eBordStrPtr
)paren
suffix:semicolon
r_static
r_int
id|iiInitialize
c_func
(paren
id|i2eBordStrPtr
)paren
suffix:semicolon
singleline_comment|// Routine to validate that all channels expected are there.
singleline_comment|//
r_extern
r_int
id|iiValidateChannels
c_func
(paren
id|i2eBordStrPtr
)paren
suffix:semicolon
singleline_comment|// Routine used to download a block of loadware.
singleline_comment|//
r_static
r_int
id|iiDownloadBlock
c_func
(paren
id|i2eBordStrPtr
comma
id|loadHdrStrPtr
comma
r_int
)paren
suffix:semicolon
singleline_comment|// Return values given by iiDownloadBlock, iiDownloadAll, iiDownloadFile:
singleline_comment|//
DECL|macro|II_DOWN_BADVALID
mdefine_line|#define II_DOWN_BADVALID   0&t;
singleline_comment|// board structure is invalid
DECL|macro|II_DOWN_CONTINUING
mdefine_line|#define II_DOWN_CONTINUING 1&t;
singleline_comment|// So far, so good, firmware expects more
DECL|macro|II_DOWN_GOOD
mdefine_line|#define II_DOWN_GOOD       2&t;
singleline_comment|// Download complete, CRC good
DECL|macro|II_DOWN_BAD
mdefine_line|#define II_DOWN_BAD        3&t;
singleline_comment|// Download complete, but CRC bad
DECL|macro|II_DOWN_BADFILE
mdefine_line|#define II_DOWN_BADFILE    4&t;
singleline_comment|// Bad magic number in loadware file
DECL|macro|II_DOWN_BADSTATE
mdefine_line|#define II_DOWN_BADSTATE   5&t;
singleline_comment|// Board is in an inappropriate state for
singleline_comment|// downloading loadware. (see i2eState)
DECL|macro|II_DOWN_TIMEOUT
mdefine_line|#define II_DOWN_TIMEOUT    6&t;
singleline_comment|// Timeout waiting for firmware
DECL|macro|II_DOWN_OVER
mdefine_line|#define II_DOWN_OVER       7&t;
singleline_comment|// Too much data
DECL|macro|II_DOWN_UNDER
mdefine_line|#define II_DOWN_UNDER      8&t;
singleline_comment|// Not enough data
DECL|macro|II_DOWN_NOFILE
mdefine_line|#define II_DOWN_NOFILE     9&t;
singleline_comment|// Loadware file not found
singleline_comment|// Routine to download an entire loadware module: Return values are a subset of
singleline_comment|// iiDownloadBlock&squot;s, excluding, of course, II_DOWN_CONTINUING
singleline_comment|//
r_static
r_int
id|iiDownloadAll
c_func
(paren
id|i2eBordStrPtr
comma
id|loadHdrStrPtr
comma
r_int
comma
r_int
)paren
suffix:semicolon
singleline_comment|// Called indirectly always.  Needed externally so the routine might be
singleline_comment|// SPECIFIED as an argument to iiReset()
singleline_comment|//
singleline_comment|//static void ii2DelayIO(unsigned int);&t;&t;// N-millisecond delay using
singleline_comment|//hardware spin
singleline_comment|//static void ii2DelayTimer(unsigned int);&t;// N-millisecond delay using Linux
singleline_comment|//timer
singleline_comment|// Many functions defined here return True if good, False otherwise, with an
singleline_comment|// error code in i2eError field. Here is a handy macro for setting the error
singleline_comment|// code and returning.
singleline_comment|//
DECL|macro|COMPLETE
mdefine_line|#define COMPLETE(pB,code) &bslash;&n;&t;if(1){ &bslash;&n;&t;&t; pB-&gt;i2eError = code; &bslash;&n;&t;&t; return (code == I2EE_GOOD);&bslash;&n;&t;}
macro_line|#endif   
singleline_comment|// I2ELLIS_H
eof
