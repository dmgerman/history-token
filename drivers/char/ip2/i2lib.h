multiline_comment|/*******************************************************************************&n;*&n;*   (c) 1998 by Computone Corporation&n;*&n;********************************************************************************&n;*&n;*&n;*   PACKAGE:     Linux tty Device Driver for IntelliPort II family of multiport&n;*                serial I/O controllers.&n;*&n;*   DESCRIPTION: Header file for high level library functions&n;*&n;*******************************************************************************/
macro_line|#ifndef I2LIB_H
DECL|macro|I2LIB_H
mdefine_line|#define I2LIB_H   1
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// I2LIB.H
singleline_comment|//
singleline_comment|// IntelliPort-II and IntelliPort-IIEX
singleline_comment|//
singleline_comment|// Defines, structure definitions, and external declarations for i2lib.c
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|//--------------------------------------
singleline_comment|// Mandatory Includes:
singleline_comment|//--------------------------------------
macro_line|#include &quot;ip2types.h&quot;
macro_line|#include &quot;i2ellis.h&quot;
macro_line|#include &quot;i2pack.h&quot;
macro_line|#include &quot;i2cmd.h&quot;
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// i2ChanStr -- Channel Structure:
singleline_comment|// Used to track per-channel information for the library routines using standard
singleline_comment|// loadware. Note also, a pointer to an array of these structures is patched
singleline_comment|// into the i2eBordStr (see i2ellis.h)
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|//
singleline_comment|// If we make some limits on the maximum block sizes, we can avoid dealing with
singleline_comment|// buffer wrap. The wrapping of the buffer is based on where the start of the
singleline_comment|// packet is. Then there is always room for the packet contiguously.
singleline_comment|//
singleline_comment|// Maximum total length of an outgoing data or in-line command block. The limit
singleline_comment|// of 36 on data is quite arbitrary and based more on DOS memory limitations
singleline_comment|// than the board interface. However, for commands, the maximum packet length is
singleline_comment|// MAX_CMD_PACK_SIZE, because the field size for the count is only a few bits
singleline_comment|// (see I2PACK.H) in such packets. For data packets, the count field size is not
singleline_comment|// the limiting factor. As of this writing, MAX_OBUF_BLOCK &lt; MAX_CMD_PACK_SIZE,
singleline_comment|// but be careful if wanting to modify either.
singleline_comment|//
DECL|macro|MAX_OBUF_BLOCK
mdefine_line|#define MAX_OBUF_BLOCK  36
singleline_comment|// Another note on maximum block sizes: we are buffering packets here. Data is
singleline_comment|// put into the buffer (if there is room) regardless of the credits from the
singleline_comment|// board. The board sends new credits whenever it has removed from his buffers a
singleline_comment|// number of characters equal to 80% of total buffer size. (Of course, the total
singleline_comment|// buffer size is what is reported when the very first set of flow control
singleline_comment|// status packets are received from the board. Therefore, to be robust, you must
singleline_comment|// always fill the board to at least 80% of the current credit limit, else you
singleline_comment|// might not give it enough to trigger a new report. These conditions are
singleline_comment|// obtained here so long as the maximum output block size is less than 20% the
singleline_comment|// size of the board&squot;s output buffers. This is true at present by &quot;coincidence&quot;
singleline_comment|// or &quot;infernal knowledge&quot;: the board&squot;s output buffers are at least 700 bytes
singleline_comment|// long (20% = 140 bytes, at least). The 80% figure is &quot;official&quot;, so the safest
singleline_comment|// strategy might be to trap the first flow control report and guarantee that
singleline_comment|// the effective maxObufBlock is the minimum of MAX_OBUF_BLOCK and 20% of first
singleline_comment|// reported buffer credit.
singleline_comment|//
DECL|macro|MAX_CBUF_BLOCK
mdefine_line|#define MAX_CBUF_BLOCK  6&t;
singleline_comment|// Maximum total length of a bypass command block
DECL|macro|IBUF_SIZE
mdefine_line|#define IBUF_SIZE       512&t;
singleline_comment|// character capacity of input buffer per channel
DECL|macro|OBUF_SIZE
mdefine_line|#define OBUF_SIZE       1024
singleline_comment|// character capacity of output buffer per channel
DECL|macro|CBUF_SIZE
mdefine_line|#define CBUF_SIZE       10&t;
singleline_comment|// character capacity of output bypass buffer
DECL|struct|_i2ChanStr
r_typedef
r_struct
id|_i2ChanStr
(brace
singleline_comment|// First, back-pointers so that given a pointer to this structure, you can
singleline_comment|// determine the correct board and channel number to reference, (say, when
singleline_comment|// issuing commands, etc. (Note, channel number is in infl.hd.i2sChannel.)
DECL|member|port_index
r_int
id|port_index
suffix:semicolon
singleline_comment|// Index of port in channel structure array attached
singleline_comment|// to board structure.
DECL|member|pTTY
id|PTTY
id|pTTY
suffix:semicolon
singleline_comment|// Pointer to tty structure for port (OS specific)
DECL|member|validity
id|USHORT
id|validity
suffix:semicolon
singleline_comment|// Indicates whether the given channel has been
singleline_comment|// initialized, really exists (or is a missing
singleline_comment|// channel, e.g. channel 9 on an 8-port box.)
DECL|member|pMyBord
id|i2eBordStrPtr
id|pMyBord
suffix:semicolon
singleline_comment|// Back-pointer to this channel&squot;s board structure 
DECL|member|wopen
r_int
id|wopen
suffix:semicolon
singleline_comment|// waiting fer carrier
DECL|member|throttled
r_int
id|throttled
suffix:semicolon
singleline_comment|// Set if upper layer can take no data
DECL|member|flags
r_int
id|flags
suffix:semicolon
singleline_comment|// Defined in tty.h
DECL|member|session
r_int
id|session
suffix:semicolon
singleline_comment|// Defined in tty.h
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
singleline_comment|// Defined in tty.h
DECL|member|open_wait
id|PWAITQ
id|open_wait
suffix:semicolon
singleline_comment|// Pointer for OS sleep function.
DECL|member|close_wait
id|PWAITQ
id|close_wait
suffix:semicolon
singleline_comment|// Pointer for OS sleep function.
DECL|member|delta_msr_wait
id|PWAITQ
id|delta_msr_wait
suffix:semicolon
singleline_comment|// Pointer for OS sleep function.
DECL|member|dss_now_wait
id|PWAITQ
id|dss_now_wait
suffix:semicolon
singleline_comment|// Pointer for OS sleep function.
DECL|member|BookmarkTimer
r_struct
id|timer_list
id|BookmarkTimer
suffix:semicolon
singleline_comment|// Used by i2DrainOutput
DECL|member|pBookmarkWait
id|wait_queue_head_t
id|pBookmarkWait
suffix:semicolon
singleline_comment|// Used by i2DrainOutput
DECL|member|NormalTermios
r_struct
id|termios
id|NormalTermios
suffix:semicolon
DECL|member|CalloutTermios
r_struct
id|termios
id|CalloutTermios
suffix:semicolon
DECL|member|BaudBase
r_int
id|BaudBase
suffix:semicolon
DECL|member|BaudDivisor
r_int
id|BaudDivisor
suffix:semicolon
DECL|member|ClosingDelay
id|USHORT
id|ClosingDelay
suffix:semicolon
DECL|member|ClosingWaitTime
id|USHORT
id|ClosingWaitTime
suffix:semicolon
r_volatile
DECL|member|infl
id|flowIn
id|infl
suffix:semicolon
singleline_comment|// This structure is initialized as a completely
singleline_comment|// formed flow-control command packet, and as such
singleline_comment|// has the channel number, also the capacity and
singleline_comment|// &quot;as-of&quot; data needed continuously.
DECL|member|sinceLastFlow
id|USHORT
id|sinceLastFlow
suffix:semicolon
singleline_comment|// Counts the number of characters read from input
singleline_comment|// buffers, since the last time flow control info
singleline_comment|// was sent.
DECL|member|whenSendFlow
id|USHORT
id|whenSendFlow
suffix:semicolon
singleline_comment|// Determines when new flow control is to be sent to
singleline_comment|// the board. Note unlike earlier manifestations of
singleline_comment|// the driver, these packets can be sent from
singleline_comment|// in-place.
DECL|member|channelNeeds
id|USHORT
id|channelNeeds
suffix:semicolon
singleline_comment|// Bit map of important things which must be done
singleline_comment|// for this channel. (See bits below )
r_volatile
DECL|member|outfl
id|flowStat
id|outfl
suffix:semicolon
singleline_comment|// Same type of structure is used to hold current
singleline_comment|// flow control information used to control our
singleline_comment|// output. &quot;asof&quot; is kept updated as data is sent,
singleline_comment|// and &quot;room&quot; never goes to zero.
singleline_comment|// The incoming ring buffer
singleline_comment|// Unlike the outgoing buffers, this holds raw data, not packets. The two
singleline_comment|// extra bytes are used to hold the byte-padding when there is room for an
singleline_comment|// odd number of bytes before we must wrap.
singleline_comment|//
DECL|member|Ibuf
id|UCHAR
id|Ibuf
(braket
id|IBUF_SIZE
op_plus
l_int|2
)braket
suffix:semicolon
r_volatile
DECL|member|Ibuf_stuff
id|USHORT
id|Ibuf_stuff
suffix:semicolon
singleline_comment|// Stuffing index
r_volatile
DECL|member|Ibuf_strip
id|USHORT
id|Ibuf_strip
suffix:semicolon
singleline_comment|// Stripping index
singleline_comment|// The outgoing ring-buffer: Holds Data and command packets. N.B., even
singleline_comment|// though these are in the channel structure, the channel is also written
singleline_comment|// here, the easier to send it to the fifo when ready. HOWEVER, individual
singleline_comment|// packets here are NOT padded to even length: the routines for writing
singleline_comment|// blocks to the the fifo will pad to even byte counts.
singleline_comment|//
DECL|member|Obuf
id|UCHAR
id|Obuf
(braket
id|OBUF_SIZE
op_plus
id|MAX_OBUF_BLOCK
op_plus
l_int|4
)braket
suffix:semicolon
r_volatile
DECL|member|Obuf_stuff
id|USHORT
id|Obuf_stuff
suffix:semicolon
singleline_comment|// Stuffing index
r_volatile
DECL|member|Obuf_strip
id|USHORT
id|Obuf_strip
suffix:semicolon
singleline_comment|// Stripping index
DECL|member|Obuf_char_count
r_int
id|Obuf_char_count
suffix:semicolon
singleline_comment|// The outgoing bypass-command buffer. Unlike earlier manifestations, the
singleline_comment|// flow control packets are sent directly from the structures. As above, the
singleline_comment|// channel number is included in the packet, but they are NOT padded to even
singleline_comment|// size.
singleline_comment|//
DECL|member|Cbuf
id|UCHAR
id|Cbuf
(braket
id|CBUF_SIZE
op_plus
id|MAX_CBUF_BLOCK
op_plus
l_int|2
)braket
suffix:semicolon
r_volatile
DECL|member|Cbuf_stuff
id|USHORT
id|Cbuf_stuff
suffix:semicolon
singleline_comment|// Stuffing index
r_volatile
DECL|member|Cbuf_strip
id|USHORT
id|Cbuf_strip
suffix:semicolon
singleline_comment|// Stripping index
singleline_comment|// The temporary buffer for the Linux tty driver PutChar entry.
singleline_comment|//
DECL|member|Pbuf
id|UCHAR
id|Pbuf
(braket
id|MAX_OBUF_BLOCK
op_minus
r_sizeof
(paren
id|i2DataHeader
)paren
)braket
suffix:semicolon
r_volatile
DECL|member|Pbuf_stuff
id|USHORT
id|Pbuf_stuff
suffix:semicolon
singleline_comment|// Stuffing index
singleline_comment|// The state of incoming data-set signals
singleline_comment|//
DECL|member|dataSetIn
id|USHORT
id|dataSetIn
suffix:semicolon
singleline_comment|// Bit-mapped according to below. Also indicates
singleline_comment|// whether a break has been detected since last
singleline_comment|// inquiry.
singleline_comment|// The state of outcoming data-set signals (as far as we can tell!)
singleline_comment|//
DECL|member|dataSetOut
id|USHORT
id|dataSetOut
suffix:semicolon
singleline_comment|// Bit-mapped according to below. 
singleline_comment|// Most recent hot-key identifier detected
singleline_comment|//
DECL|member|hotKeyIn
id|USHORT
id|hotKeyIn
suffix:semicolon
singleline_comment|// Hot key as sent by the board, HOT_CLEAR indicates
singleline_comment|// no hot key detected since last examined.
singleline_comment|// Counter of outstanding requests for bookmarks
singleline_comment|//
DECL|member|bookMarks
r_int
id|bookMarks
suffix:semicolon
singleline_comment|// Number of outstanding bookmark requests, (+ive
singleline_comment|// whenever a bookmark request if queued up, -ive
singleline_comment|// whenever a bookmark is received).
singleline_comment|// Misc options
singleline_comment|//
DECL|member|channelOptions
id|USHORT
id|channelOptions
suffix:semicolon
singleline_comment|// See below
singleline_comment|// To store various incoming special packets
singleline_comment|//
DECL|member|channelStatus
id|debugStat
id|channelStatus
suffix:semicolon
DECL|member|channelRcount
id|cntStat
id|channelRcount
suffix:semicolon
DECL|member|channelTcount
id|cntStat
id|channelTcount
suffix:semicolon
DECL|member|channelFail
id|failStat
id|channelFail
suffix:semicolon
singleline_comment|// To store the last values for line characteristics we sent to the board.
singleline_comment|//
DECL|member|speed
r_int
id|speed
suffix:semicolon
DECL|member|flush_flags
r_int
id|flush_flags
suffix:semicolon
DECL|member|trace
r_void
(paren
op_star
id|trace
)paren
(paren
r_int
r_int
comma
r_int
r_char
comma
r_int
r_char
comma
r_int
r_int
comma
dot
dot
dot
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Kernel counters for the 4 input interrupts &n;&t; */
DECL|member|icount
r_struct
id|async_icount
id|icount
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Task queues for processing input packets from the board.&n;&t; */
DECL|member|tqueue_input
r_struct
id|tq_struct
id|tqueue_input
suffix:semicolon
DECL|member|tqueue_status
r_struct
id|tq_struct
id|tqueue_status
suffix:semicolon
DECL|member|tqueue_hangup
r_struct
id|tq_struct
id|tqueue_hangup
suffix:semicolon
DECL|member|Ibuf_spinlock
id|rwlock_t
id|Ibuf_spinlock
suffix:semicolon
DECL|member|Obuf_spinlock
id|rwlock_t
id|Obuf_spinlock
suffix:semicolon
DECL|member|Cbuf_spinlock
id|rwlock_t
id|Cbuf_spinlock
suffix:semicolon
DECL|member|Pbuf_spinlock
id|rwlock_t
id|Pbuf_spinlock
suffix:semicolon
DECL|typedef|i2ChanStr
DECL|typedef|i2ChanStrPtr
)brace
id|i2ChanStr
comma
op_star
id|i2ChanStrPtr
suffix:semicolon
singleline_comment|//---------------------------------------------------
singleline_comment|// Manifests and bit-maps for elements in i2ChanStr
singleline_comment|//---------------------------------------------------
singleline_comment|//
singleline_comment|// flush flags
singleline_comment|//
DECL|macro|STARTFL_FLAG
mdefine_line|#define STARTFL_FLAG 1
DECL|macro|STOPFL_FLAG
mdefine_line|#define STOPFL_FLAG  2
singleline_comment|// validity
singleline_comment|//
DECL|macro|CHANNEL_MAGIC_BITS
mdefine_line|#define CHANNEL_MAGIC_BITS 0xff00
DECL|macro|CHANNEL_MAGIC
mdefine_line|#define CHANNEL_MAGIC      0x5300   
singleline_comment|// (validity &amp; CHANNEL_MAGIC_BITS) ==
singleline_comment|// CHANNEL_MAGIC --&gt; structure good
DECL|macro|CHANNEL_SUPPORT
mdefine_line|#define CHANNEL_SUPPORT    0x0001   
singleline_comment|// Indicates channel is supported, exists,
singleline_comment|// and passed P.O.S.T.
singleline_comment|// channelNeeds
singleline_comment|//
DECL|macro|NEED_FLOW
mdefine_line|#define NEED_FLOW    1  
singleline_comment|// Indicates flow control has been queued
DECL|macro|NEED_INLINE
mdefine_line|#define NEED_INLINE  2  
singleline_comment|// Indicates inline commands or data queued
DECL|macro|NEED_BYPASS
mdefine_line|#define NEED_BYPASS  4  
singleline_comment|// Indicates bypass commands queued
DECL|macro|NEED_CREDIT
mdefine_line|#define NEED_CREDIT  8  
singleline_comment|// Indicates would be sending except has not sufficient
singleline_comment|// credit. The data is still in the channel structure,
singleline_comment|// but the channel is not enqueued in the board
singleline_comment|// structure again until there is a credit received from
singleline_comment|// the board.
singleline_comment|// dataSetIn (Also the bits for i2GetStatus return value)
singleline_comment|//
DECL|macro|I2_DCD
mdefine_line|#define I2_DCD 1
DECL|macro|I2_CTS
mdefine_line|#define I2_CTS 2
DECL|macro|I2_DSR
mdefine_line|#define I2_DSR 4
DECL|macro|I2_RI
mdefine_line|#define I2_RI  8
singleline_comment|// dataSetOut (Also the bits for i2GetStatus return value)
singleline_comment|//
DECL|macro|I2_DTR
mdefine_line|#define I2_DTR 1
DECL|macro|I2_RTS
mdefine_line|#define I2_RTS 2
singleline_comment|// i2GetStatus() can optionally clear these bits
singleline_comment|//
DECL|macro|I2_BRK
mdefine_line|#define I2_BRK    0x10  
singleline_comment|// A break was detected
DECL|macro|I2_PAR
mdefine_line|#define I2_PAR    0x20  
singleline_comment|// A parity error was received 
DECL|macro|I2_FRA
mdefine_line|#define I2_FRA    0x40  
singleline_comment|// A framing error was received
DECL|macro|I2_OVR
mdefine_line|#define I2_OVR    0x80  
singleline_comment|// An overrun error was received 
singleline_comment|// i2GetStatus() automatically clears these bits */
singleline_comment|//
DECL|macro|I2_DDCD
mdefine_line|#define I2_DDCD   0x100 
singleline_comment|// DCD changed from its  former value
DECL|macro|I2_DCTS
mdefine_line|#define I2_DCTS   0x200 
singleline_comment|// CTS changed from its former value 
DECL|macro|I2_DDSR
mdefine_line|#define I2_DDSR   0x400 
singleline_comment|// DSR changed from its former value 
DECL|macro|I2_DRI
mdefine_line|#define I2_DRI    0x800 
singleline_comment|// RI changed from its former value 
singleline_comment|// hotKeyIn
singleline_comment|//
DECL|macro|HOT_CLEAR
mdefine_line|#define HOT_CLEAR 0x1322   
singleline_comment|// Indicates that no hot-key has been detected
singleline_comment|// channelOptions
singleline_comment|//
DECL|macro|CO_NBLOCK_WRITE
mdefine_line|#define CO_NBLOCK_WRITE 1  &t;
singleline_comment|// Writes don&squot;t block waiting for buffer. (Default
singleline_comment|// is, they do wait.)
singleline_comment|// fcmodes
singleline_comment|//
DECL|macro|I2_OUTFLOW_CTS
mdefine_line|#define I2_OUTFLOW_CTS  0x0001
DECL|macro|I2_INFLOW_RTS
mdefine_line|#define I2_INFLOW_RTS   0x0002
DECL|macro|I2_INFLOW_DSR
mdefine_line|#define I2_INFLOW_DSR   0x0004
DECL|macro|I2_INFLOW_DTR
mdefine_line|#define I2_INFLOW_DTR   0x0008
DECL|macro|I2_OUTFLOW_DSR
mdefine_line|#define I2_OUTFLOW_DSR  0x0010
DECL|macro|I2_OUTFLOW_DTR
mdefine_line|#define I2_OUTFLOW_DTR  0x0020
DECL|macro|I2_OUTFLOW_XON
mdefine_line|#define I2_OUTFLOW_XON  0x0040
DECL|macro|I2_OUTFLOW_XANY
mdefine_line|#define I2_OUTFLOW_XANY 0x0080
DECL|macro|I2_INFLOW_XON
mdefine_line|#define I2_INFLOW_XON   0x0100
DECL|macro|I2_CRTSCTS
mdefine_line|#define I2_CRTSCTS      (I2_OUTFLOW_CTS|I2_INFLOW_RTS)
DECL|macro|I2_IXANY_MODE
mdefine_line|#define I2_IXANY_MODE   (I2_OUTFLOW_XON|I2_OUTFLOW_XANY)
singleline_comment|//-------------------------------------------
singleline_comment|// Macros used from user level like functions
singleline_comment|//-------------------------------------------
singleline_comment|// Macros to set and clear channel options
singleline_comment|//
DECL|macro|i2SetOption
mdefine_line|#define i2SetOption(pCh, option) pCh-&gt;channelOptions |= option
DECL|macro|i2ClrOption
mdefine_line|#define i2ClrOption(pCh, option) pCh-&gt;channelOptions &amp;= ~option
singleline_comment|// Macro to set fatal-error trap
singleline_comment|//
DECL|macro|i2SetFatalTrap
mdefine_line|#define i2SetFatalTrap(pB, routine) pB-&gt;i2eFatalTrap = routine
singleline_comment|//--------------------------------------------
singleline_comment|// Declarations and prototypes for i2lib.c
singleline_comment|//--------------------------------------------
singleline_comment|//
r_static
r_int
id|i2InitChannels
c_func
(paren
id|i2eBordStrPtr
comma
r_int
comma
id|i2ChanStrPtr
)paren
suffix:semicolon
r_static
r_int
id|i2QueueCommands
c_func
(paren
r_int
comma
id|i2ChanStrPtr
comma
r_int
comma
r_int
comma
id|cmdSyntaxPtr
comma
dot
dot
dot
)paren
suffix:semicolon
r_static
r_int
id|i2GetStatus
c_func
(paren
id|i2ChanStrPtr
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|i2Input
c_func
(paren
id|i2ChanStrPtr
)paren
suffix:semicolon
r_static
r_int
id|i2InputFlush
c_func
(paren
id|i2ChanStrPtr
)paren
suffix:semicolon
r_static
r_int
id|i2Output
c_func
(paren
id|i2ChanStrPtr
comma
r_const
r_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|i2OutputFree
c_func
(paren
id|i2ChanStrPtr
)paren
suffix:semicolon
r_static
r_int
id|i2ServiceBoard
c_func
(paren
id|i2eBordStrPtr
)paren
suffix:semicolon
r_static
r_void
id|i2DrainOutput
c_func
(paren
id|i2ChanStrPtr
comma
r_int
)paren
suffix:semicolon
singleline_comment|// Argument to i2QueueCommands
singleline_comment|//
DECL|macro|C_IN_LINE
mdefine_line|#define C_IN_LINE 1
DECL|macro|C_BYPASS
mdefine_line|#define C_BYPASS  0
macro_line|#endif   
singleline_comment|// I2LIB_H
eof
