multiline_comment|/*******************************************************************************&n;*&n;*   (c) 1998 by Computone Corporation&n;*&n;********************************************************************************&n;*&n;*&n;*   PACKAGE:     Linux tty Device Driver for IntelliPort family of multiport&n;*                serial I/O controllers.&n;*&n;*   DESCRIPTION: Status display utility&n;*&n;*******************************************************************************/
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;ctype.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &quot;i2ellis.h&quot;
macro_line|#include &quot;i2lib.h&quot;
DECL|variable|Board
id|i2eBordStr
id|Board
(braket
l_int|2
)braket
suffix:semicolon
DECL|variable|Port
id|i2ChanStr
id|Port
(braket
l_int|2
)braket
suffix:semicolon
DECL|struct|driver_stats
r_struct
id|driver_stats
(brace
DECL|member|ref_count
id|ULONG
id|ref_count
suffix:semicolon
DECL|member|irq_counter
id|ULONG
id|irq_counter
suffix:semicolon
DECL|member|bh_counter
id|ULONG
id|bh_counter
suffix:semicolon
DECL|variable|Driver
)brace
id|Driver
suffix:semicolon
DECL|variable|devname
r_char
id|devname
(braket
l_int|20
)braket
suffix:semicolon
DECL|function|main
r_int
id|main
(paren
r_int
id|argc
comma
r_char
op_star
id|argv
(braket
)braket
)paren
(brace
r_int
id|fd
suffix:semicolon
r_int
id|dev
comma
id|i
suffix:semicolon
id|i2eBordStrPtr
id|pB
op_assign
id|Board
suffix:semicolon
id|i2ChanStrPtr
id|pCh
op_assign
id|Port
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|2
)paren
(brace
id|printf
(paren
l_string|&quot;Usage: %s &lt;port&gt;&bslash;n&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|i
op_assign
id|sscanf
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;/dev/ttyF%d&quot;
comma
op_amp
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
l_int|1
)paren
m_exit
(paren
l_int|1
)paren
suffix:semicolon
singleline_comment|//printf(&quot;%s: board %d, port %d&bslash;n&quot;, argv[1], dev / 64, dev % 64 );
id|sprintf
(paren
id|devname
comma
l_string|&quot;/dev/ip2stat%d&quot;
comma
id|dev
op_div
l_int|64
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
OG
(paren
id|fd
op_assign
id|open
(paren
id|devname
comma
id|O_RDONLY
)paren
)paren
)paren
(brace
singleline_comment|// Conventional name failed - try devfs name
id|sprintf
(paren
id|devname
comma
l_string|&quot;/dev/ip2/stat%d&quot;
comma
id|dev
op_div
l_int|64
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
OG
(paren
id|fd
op_assign
id|open
(paren
id|devname
comma
id|O_RDONLY
)paren
)paren
)paren
(brace
singleline_comment|// Where is our board???
id|printf
c_func
(paren
l_string|&quot;Unable to open board %d to retrieve stats&bslash;n&quot;
comma
id|dev
op_div
l_int|64
)paren
suffix:semicolon
m_exit
(paren
l_int|255
)paren
suffix:semicolon
)brace
)brace
id|ioctl
(paren
id|fd
comma
l_int|64
comma
op_amp
id|Driver
)paren
suffix:semicolon
id|ioctl
(paren
id|fd
comma
l_int|65
comma
id|Board
)paren
suffix:semicolon
id|ioctl
(paren
id|fd
comma
id|dev
op_mod
l_int|64
comma
id|Port
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;Driver statistics:-&bslash;n&quot;
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot; Reference Count:  %d&bslash;n&quot;
comma
id|Driver.ref_count
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot; Interrupts to date:   %ld&bslash;n&quot;
comma
id|Driver.irq_counter
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot; Bottom half to date:  %ld&bslash;n&quot;
comma
id|Driver.bh_counter
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;Board statistics(%d):-&bslash;n&quot;
comma
id|dev
op_div
l_int|64
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;FIFO: remains = %d%s&bslash;n&quot;
comma
id|pB-&gt;i2eFifoRemains
comma
id|pB-&gt;i2eWaitingForEmptyFifo
ques
c_cond
l_string|&quot;, busy&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;Mail: out mail = %02x&bslash;n&quot;
comma
id|pB-&gt;i2eOutMailWaiting
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;  Input interrupts : %d&bslash;n&quot;
comma
id|pB-&gt;i2eFifoInInts
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;  Output interrupts: %d&bslash;n&quot;
comma
id|pB-&gt;i2eFifoOutInts
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;  Flow queued      : %ld&bslash;n&quot;
comma
id|pB-&gt;debugFlowQueued
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;  Bypass queued    : %ld&bslash;n&quot;
comma
id|pB-&gt;debugBypassQueued
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;  Inline queued    : %ld&bslash;n&quot;
comma
id|pB-&gt;debugInlineQueued
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;  Data queued      : %ld&bslash;n&quot;
comma
id|pB-&gt;debugDataQueued
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;  Flow packets     : %ld&bslash;n&quot;
comma
id|pB-&gt;debugFlowCount
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;  Bypass packets   : %ld&bslash;n&quot;
comma
id|pB-&gt;debugBypassCount
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;  Inline packets   : %ld&bslash;n&quot;
comma
id|pB-&gt;debugInlineCount
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;  Mail status      : %x&bslash;n&quot;
comma
id|pB-&gt;i2eStatus
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;  Output mail      : %x&bslash;n&quot;
comma
id|pB-&gt;i2eOutMailWaiting
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;  Fatal flag       : %d&bslash;n&quot;
comma
id|pB-&gt;i2eFatal
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;Channel statistics(%s:%d):-&bslash;n&quot;
comma
id|argv
(braket
l_int|1
)braket
comma
id|dev
op_mod
l_int|64
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;ibuf: stuff = %d strip = %d&bslash;n&quot;
comma
id|pCh-&gt;Ibuf_stuff
comma
id|pCh-&gt;Ibuf_strip
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;obuf: stuff = %d strip = %d&bslash;n&quot;
comma
id|pCh-&gt;Obuf_stuff
comma
id|pCh-&gt;Obuf_strip
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;pbuf: stuff = %d&bslash;n&quot;
comma
id|pCh-&gt;Pbuf_stuff
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;cbuf: stuff = %d strip = %d&bslash;n&quot;
comma
id|pCh-&gt;Cbuf_stuff
comma
id|pCh-&gt;Cbuf_strip
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;infl: count = %d room = %d&bslash;n&quot;
comma
id|pCh-&gt;infl.asof
comma
id|pCh-&gt;infl.room
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;outfl: count = %d room = %d&bslash;n&quot;
comma
id|pCh-&gt;outfl.asof
comma
id|pCh-&gt;outfl.room
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;throttled = %d &quot;
comma
id|pCh-&gt;throttled
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;bookmarks = %d &quot;
comma
id|pCh-&gt;bookMarks
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;flush_flags = %x&bslash;n&quot;
comma
id|pCh-&gt;flush_flags
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;needs: &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pCh-&gt;channelNeeds
op_amp
id|NEED_FLOW
)paren
id|printf
c_func
(paren
l_string|&quot;FLOW &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pCh-&gt;channelNeeds
op_amp
id|NEED_INLINE
)paren
id|printf
c_func
(paren
l_string|&quot;INLINE &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pCh-&gt;channelNeeds
op_amp
id|NEED_BYPASS
)paren
id|printf
c_func
(paren
l_string|&quot;BYPASS &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pCh-&gt;channelNeeds
op_amp
id|NEED_CREDIT
)paren
id|printf
c_func
(paren
l_string|&quot;CREDIT &quot;
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;dss: in = %x, out = %x&bslash;n&quot;
comma
id|pCh-&gt;dataSetIn
comma
id|pCh-&gt;dataSetOut
)paren
suffix:semicolon
)brace
eof
