multiline_comment|/*========================================================================&n;    Debug routines for nsp_cs&n;      By: YOKOTA Hiroshi &lt;yokota@netlab.is.tsukuba.ac.jp&gt;&n;&n;    This software may be used and distributed according to the terms of&n;    the GNU General Public License.&n;=========================================================================*/
multiline_comment|/* $Id: nsp_debug.c,v 1.3 2003/07/26 14:21:09 elca Exp $ */
multiline_comment|/*&n; * Show the command data of a command&n; */
DECL|variable|unknown
r_static
r_const
r_char
id|unknown
(braket
)braket
op_assign
l_string|&quot;UNKNOWN&quot;
suffix:semicolon
DECL|variable|group_0_commands
r_static
r_const
r_char
op_star
id|group_0_commands
(braket
)braket
op_assign
(brace
multiline_comment|/* 00-03 */
l_string|&quot;Test Unit Ready&quot;
comma
l_string|&quot;Rezero Unit&quot;
comma
id|unknown
comma
l_string|&quot;Request Sense&quot;
comma
multiline_comment|/* 04-07 */
l_string|&quot;Format Unit&quot;
comma
l_string|&quot;Read Block Limits&quot;
comma
id|unknown
comma
l_string|&quot;Reasssign Blocks&quot;
comma
multiline_comment|/* 08-0d */
l_string|&quot;Read (6)&quot;
comma
id|unknown
comma
l_string|&quot;Write (6)&quot;
comma
l_string|&quot;Seek (6)&quot;
comma
id|unknown
comma
id|unknown
comma
multiline_comment|/* 0e-12 */
id|unknown
comma
l_string|&quot;Read Reverse&quot;
comma
l_string|&quot;Write Filemarks&quot;
comma
l_string|&quot;Space&quot;
comma
l_string|&quot;Inquiry&quot;
comma
multiline_comment|/* 13-16 */
id|unknown
comma
l_string|&quot;Recover Buffered Data&quot;
comma
l_string|&quot;Mode Select&quot;
comma
l_string|&quot;Reserve&quot;
comma
multiline_comment|/* 17-1b */
l_string|&quot;Release&quot;
comma
l_string|&quot;Copy&quot;
comma
l_string|&quot;Erase&quot;
comma
l_string|&quot;Mode Sense&quot;
comma
l_string|&quot;Start/Stop Unit&quot;
comma
multiline_comment|/* 1c-1d */
l_string|&quot;Receive Diagnostic&quot;
comma
l_string|&quot;Send Diagnostic&quot;
comma
multiline_comment|/* 1e-1f */
l_string|&quot;Prevent/Allow Medium Removal&quot;
comma
id|unknown
comma
)brace
suffix:semicolon
DECL|variable|group_1_commands
r_static
r_const
r_char
op_star
id|group_1_commands
(braket
)braket
op_assign
(brace
multiline_comment|/* 20-22 */
id|unknown
comma
id|unknown
comma
id|unknown
comma
multiline_comment|/* 23-28 */
id|unknown
comma
id|unknown
comma
l_string|&quot;Read Capacity&quot;
comma
id|unknown
comma
id|unknown
comma
l_string|&quot;Read (10)&quot;
comma
multiline_comment|/* 29-2d */
id|unknown
comma
l_string|&quot;Write (10)&quot;
comma
l_string|&quot;Seek (10)&quot;
comma
id|unknown
comma
id|unknown
comma
multiline_comment|/* 2e-31 */
l_string|&quot;Write Verify&quot;
comma
l_string|&quot;Verify&quot;
comma
l_string|&quot;Search High&quot;
comma
l_string|&quot;Search Equal&quot;
comma
multiline_comment|/* 32-34 */
l_string|&quot;Search Low&quot;
comma
l_string|&quot;Set Limits&quot;
comma
l_string|&quot;Prefetch or Read Position&quot;
comma
multiline_comment|/* 35-37 */
l_string|&quot;Synchronize Cache&quot;
comma
l_string|&quot;Lock/Unlock Cache&quot;
comma
l_string|&quot;Read Defect Data&quot;
comma
multiline_comment|/* 38-3c */
l_string|&quot;Medium Scan&quot;
comma
l_string|&quot;Compare&quot;
comma
l_string|&quot;Copy Verify&quot;
comma
l_string|&quot;Write Buffer&quot;
comma
l_string|&quot;Read Buffer&quot;
comma
multiline_comment|/* 3d-3f */
l_string|&quot;Update Block&quot;
comma
l_string|&quot;Read Long&quot;
comma
l_string|&quot;Write Long&quot;
comma
)brace
suffix:semicolon
DECL|variable|group_2_commands
r_static
r_const
r_char
op_star
id|group_2_commands
(braket
)braket
op_assign
(brace
multiline_comment|/* 40-41 */
l_string|&quot;Change Definition&quot;
comma
l_string|&quot;Write Same&quot;
comma
multiline_comment|/* 42-48 */
l_string|&quot;Read Sub-Ch(cd)&quot;
comma
l_string|&quot;Read TOC&quot;
comma
l_string|&quot;Read Header(cd)&quot;
comma
l_string|&quot;Play Audio(cd)&quot;
comma
id|unknown
comma
l_string|&quot;Play Audio MSF(cd)&quot;
comma
l_string|&quot;Play Audio Track/Index(cd)&quot;
comma
multiline_comment|/* 49-4f */
l_string|&quot;Play Track Relative(10)(cd)&quot;
comma
id|unknown
comma
l_string|&quot;Pause/Resume(cd)&quot;
comma
l_string|&quot;Log Select&quot;
comma
l_string|&quot;Log Sense&quot;
comma
id|unknown
comma
id|unknown
comma
multiline_comment|/* 50-55 */
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
l_string|&quot;Mode Select (10)&quot;
comma
multiline_comment|/* 56-5b */
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
l_string|&quot;Mode Sense (10)&quot;
comma
id|unknown
comma
multiline_comment|/* 5c-5f */
id|unknown
comma
id|unknown
comma
id|unknown
comma
)brace
suffix:semicolon
DECL|macro|group
mdefine_line|#define group(opcode) (((opcode) &gt;&gt; 5) &amp; 7)
DECL|macro|RESERVED_GROUP
mdefine_line|#define RESERVED_GROUP  0
DECL|macro|VENDOR_GROUP
mdefine_line|#define VENDOR_GROUP    1
DECL|macro|NOTEXT_GROUP
mdefine_line|#define NOTEXT_GROUP    2
DECL|variable|commands
r_static
r_const
r_char
op_star
op_star
id|commands
(braket
)braket
op_assign
(brace
id|group_0_commands
comma
id|group_1_commands
comma
id|group_2_commands
comma
(paren
r_const
r_char
op_star
op_star
)paren
id|RESERVED_GROUP
comma
(paren
r_const
r_char
op_star
op_star
)paren
id|RESERVED_GROUP
comma
(paren
r_const
r_char
op_star
op_star
)paren
id|NOTEXT_GROUP
comma
(paren
r_const
r_char
op_star
op_star
)paren
id|VENDOR_GROUP
comma
(paren
r_const
r_char
op_star
op_star
)paren
id|VENDOR_GROUP
)brace
suffix:semicolon
DECL|variable|reserved
r_static
r_const
r_char
id|reserved
(braket
)braket
op_assign
l_string|&quot;RESERVED&quot;
suffix:semicolon
DECL|variable|vendor
r_static
r_const
r_char
id|vendor
(braket
)braket
op_assign
l_string|&quot;VENDOR SPECIFIC&quot;
suffix:semicolon
DECL|function|print_opcodek
r_static
r_void
id|print_opcodek
c_func
(paren
r_int
r_char
id|opcode
)paren
(brace
r_const
r_char
op_star
op_star
id|table
op_assign
id|commands
(braket
id|group
c_func
(paren
id|opcode
)paren
)braket
suffix:semicolon
r_switch
c_cond
(paren
(paren
r_int
r_int
)paren
id|table
)paren
(brace
r_case
id|RESERVED_GROUP
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%s[%02x] &quot;
comma
id|reserved
comma
id|opcode
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NOTEXT_GROUP
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%s(notext)[%02x] &quot;
comma
id|unknown
comma
id|opcode
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VENDOR_GROUP
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%s[%02x] &quot;
comma
id|vendor
comma
id|opcode
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|table
(braket
id|opcode
op_amp
l_int|0x1f
)braket
op_ne
id|unknown
)paren
id|printk
c_func
(paren
l_string|&quot;%s[%02x] &quot;
comma
id|table
(braket
id|opcode
op_amp
l_int|0x1f
)braket
comma
id|opcode
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;%s[%02x] &quot;
comma
id|unknown
comma
id|opcode
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|print_commandk
r_static
r_void
id|print_commandk
(paren
r_int
r_char
op_star
id|command
)paren
(brace
r_int
id|i
comma
id|s
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
)paren
suffix:semicolon
id|print_opcodek
c_func
(paren
id|command
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/*printk(KERN_DEBUG __FUNCTION__ &quot; &quot;);*/
r_if
c_cond
(paren
(paren
id|command
(braket
l_int|0
)braket
op_rshift
l_int|5
)paren
op_eq
l_int|6
op_logical_or
(paren
id|command
(braket
l_int|0
)braket
op_rshift
l_int|5
)paren
op_eq
l_int|7
)paren
(brace
id|s
op_assign
l_int|12
suffix:semicolon
multiline_comment|/* vender specific */
)brace
r_else
(brace
id|s
op_assign
id|COMMAND_SIZE
c_func
(paren
id|command
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|s
suffix:semicolon
op_increment
id|i
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|command
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|s
)paren
(brace
r_case
l_int|6
suffix:colon
id|printk
c_func
(paren
l_string|&quot;LBA=%d len=%d&quot;
comma
(paren
(paren
(paren
r_int
r_int
)paren
id|command
(braket
l_int|1
)braket
op_amp
l_int|0x0f
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|command
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|command
(braket
l_int|3
)braket
)paren
comma
(paren
r_int
r_int
)paren
id|command
(braket
l_int|4
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
id|printk
c_func
(paren
l_string|&quot;LBA=%d len=%d&quot;
comma
(paren
(paren
r_int
r_int
)paren
id|command
(braket
l_int|2
)braket
op_lshift
l_int|24
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|command
(braket
l_int|3
)braket
op_lshift
l_int|16
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|command
(braket
l_int|4
)braket
op_lshift
l_int|8
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|command
(braket
l_int|5
)braket
)paren
comma
(paren
(paren
r_int
r_int
)paren
id|command
(braket
l_int|7
)braket
op_lshift
l_int|8
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|command
(braket
l_int|8
)braket
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|12
suffix:colon
id|printk
c_func
(paren
l_string|&quot;LBA=%d len=%d&quot;
comma
(paren
(paren
r_int
r_int
)paren
id|command
(braket
l_int|2
)braket
op_lshift
l_int|24
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|command
(braket
l_int|3
)braket
op_lshift
l_int|16
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|command
(braket
l_int|4
)braket
op_lshift
l_int|8
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|command
(braket
l_int|5
)braket
)paren
comma
(paren
(paren
r_int
r_int
)paren
id|command
(braket
l_int|6
)braket
op_lshift
l_int|24
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|command
(braket
l_int|7
)braket
op_lshift
l_int|16
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|command
(braket
l_int|8
)braket
op_lshift
l_int|8
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|command
(braket
l_int|9
)braket
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|show_command
r_static
r_void
id|show_command
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
id|print_commandk
c_func
(paren
id|SCpnt-&gt;cmnd
)paren
suffix:semicolon
)brace
DECL|function|show_phase
r_static
r_void
id|show_phase
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
r_int
id|i
op_assign
id|SCpnt-&gt;SCp.phase
suffix:semicolon
r_char
op_star
id|ph
(braket
)braket
op_assign
(brace
l_string|&quot;PH_UNDETERMINED&quot;
comma
l_string|&quot;PH_ARBSTART&quot;
comma
l_string|&quot;PH_SELSTART&quot;
comma
l_string|&quot;PH_SELECTED&quot;
comma
l_string|&quot;PH_COMMAND&quot;
comma
l_string|&quot;PH_DATA&quot;
comma
l_string|&quot;PH_STATUS&quot;
comma
l_string|&quot;PH_MSG_IN&quot;
comma
l_string|&quot;PH_MSG_OUT&quot;
comma
l_string|&quot;PH_DISCONNECT&quot;
comma
l_string|&quot;PH_RESELECT&quot;
)brace
suffix:semicolon
r_if
c_cond
(paren
id|i
template_param
id|PH_RESELECT
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;scsi phase: unknown(%d)&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;scsi phase: %s&bslash;n&quot;
comma
id|ph
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|show_busphase
r_static
r_void
id|show_busphase
c_func
(paren
r_int
r_char
id|stat
)paren
(brace
r_switch
c_cond
(paren
id|stat
)paren
(brace
r_case
id|BUSPHASE_COMMAND
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;BUSPHASE_COMMAND&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BUSPHASE_MESSAGE_IN
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;BUSPHASE_MESSAGE_IN&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BUSPHASE_MESSAGE_OUT
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;BUSPHASE_MESSAGE_OUT&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BUSPHASE_DATA_IN
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;BUSPHASE_DATA_IN&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BUSPHASE_DATA_OUT
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;BUSPHASE_DATA_OUT&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BUSPHASE_STATUS
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;BUSPHASE_STATUS&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BUSPHASE_SELECT
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;BUSPHASE_SELECT&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;BUSPHASE_other&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|show_message
r_static
r_void
id|show_message
c_func
(paren
id|nsp_hw_data
op_star
id|data
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;msg:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|data-&gt;MsgLen
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
id|data-&gt;MsgBuffer
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end */
eof
