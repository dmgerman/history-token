macro_line|#include &quot;dib3000-common.h&quot;
macro_line|#ifdef CONFIG_DVB_DIBCOM_DEBUG
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
id|module_param
c_func
(paren
id|debug
comma
r_int
comma
l_int|0x644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;set debugging level (1=info,2=i2c,4=srch (|-able)).&quot;
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|deb_info
mdefine_line|#define deb_info(args...) dprintk(0x01,args)
DECL|macro|deb_i2c
mdefine_line|#define deb_i2c(args...) dprintk(0x02,args)
DECL|macro|deb_srch
mdefine_line|#define deb_srch(args...) dprintk(0x04,args)
DECL|function|dib3000_read_reg
r_int
id|dib3000_read_reg
c_func
(paren
r_struct
id|dib3000_state
op_star
id|state
comma
id|u16
id|reg
)paren
(brace
id|u8
id|wb
(braket
)braket
op_assign
(brace
(paren
(paren
id|reg
op_rshift
l_int|8
)paren
op_or
l_int|0x80
)paren
op_amp
l_int|0xff
comma
id|reg
op_amp
l_int|0xff
)brace
suffix:semicolon
id|u8
id|rb
(braket
l_int|2
)braket
suffix:semicolon
r_struct
id|i2c_msg
id|msg
(braket
)braket
op_assign
(brace
(brace
dot
id|addr
op_assign
id|state-&gt;config.demod_address
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|buf
op_assign
id|wb
comma
dot
id|len
op_assign
l_int|2
)brace
comma
(brace
dot
id|addr
op_assign
id|state-&gt;config.demod_address
comma
dot
id|flags
op_assign
id|I2C_M_RD
comma
dot
id|buf
op_assign
id|rb
comma
dot
id|len
op_assign
l_int|2
)brace
comma
)brace
suffix:semicolon
r_if
c_cond
(paren
id|i2c_transfer
c_func
(paren
id|state-&gt;i2c
comma
id|msg
comma
l_int|2
)paren
op_ne
l_int|2
)paren
id|deb_i2c
c_func
(paren
l_string|&quot;i2c read error&bslash;n&quot;
)paren
suffix:semicolon
id|deb_i2c
c_func
(paren
l_string|&quot;reading i2c bus (reg: %5d 0x%04x, val: %5d 0x%04x)&bslash;n&quot;
comma
id|reg
comma
id|reg
comma
(paren
id|rb
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_or
id|rb
(braket
l_int|1
)braket
comma
(paren
id|rb
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_or
id|rb
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
(paren
id|rb
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_or
id|rb
(braket
l_int|1
)braket
suffix:semicolon
)brace
DECL|function|dib3000_write_reg
r_int
id|dib3000_write_reg
c_func
(paren
r_struct
id|dib3000_state
op_star
id|state
comma
id|u16
id|reg
comma
id|u16
id|val
)paren
(brace
id|u8
id|b
(braket
)braket
op_assign
(brace
(paren
id|reg
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
id|reg
op_amp
l_int|0xff
comma
(paren
id|val
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
id|val
op_amp
l_int|0xff
comma
)brace
suffix:semicolon
r_struct
id|i2c_msg
id|msg
(braket
)braket
op_assign
(brace
(brace
dot
id|addr
op_assign
id|state-&gt;config.demod_address
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|buf
op_assign
id|b
comma
dot
id|len
op_assign
l_int|4
)brace
)brace
suffix:semicolon
id|deb_i2c
c_func
(paren
l_string|&quot;writing i2c bus (reg: %5d 0x%04x, val: %5d 0x%04x)&bslash;n&quot;
comma
id|reg
comma
id|reg
comma
id|val
comma
id|val
)paren
suffix:semicolon
r_return
id|i2c_transfer
c_func
(paren
id|state-&gt;i2c
comma
id|msg
comma
l_int|1
)paren
op_ne
l_int|1
ques
c_cond
op_minus
id|EREMOTEIO
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|dib3000_init_pid_list
r_int
id|dib3000_init_pid_list
c_func
(paren
r_struct
id|dib3000_state
op_star
id|state
comma
r_int
id|num
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|state
op_ne
l_int|NULL
)paren
(brace
id|state-&gt;pid_list
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dib3000_pid
)paren
op_star
id|num
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;pid_list
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|deb_info
c_func
(paren
l_string|&quot;initializing %d pids for the pid_list.&bslash;n&quot;
comma
id|num
)paren
suffix:semicolon
id|state-&gt;pid_list_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|memset
c_func
(paren
id|state-&gt;pid_list
comma
l_int|0
comma
id|num
op_star
(paren
r_sizeof
(paren
r_struct
id|dib3000_pid
)paren
)paren
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
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
id|state-&gt;pid_list
(braket
id|i
)braket
dot
id|pid
op_assign
l_int|0
suffix:semicolon
id|state-&gt;pid_list
(braket
id|i
)braket
dot
id|active
op_assign
l_int|0
suffix:semicolon
)brace
id|state-&gt;feedcount
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dib3000_dealloc_pid_list
r_void
id|dib3000_dealloc_pid_list
c_func
(paren
r_struct
id|dib3000_state
op_star
id|state
)paren
(brace
r_if
c_cond
(paren
id|state
op_ne
l_int|NULL
op_logical_and
id|state-&gt;pid_list
op_ne
l_int|NULL
)paren
id|kfree
c_func
(paren
id|state-&gt;pid_list
)paren
suffix:semicolon
)brace
multiline_comment|/* fetch a pid from pid_list */
DECL|function|dib3000_get_pid_index
r_int
id|dib3000_get_pid_index
c_func
(paren
r_struct
id|dib3000_pid
id|pid_list
(braket
)braket
comma
r_int
id|num_pids
comma
r_int
id|pid
comma
id|spinlock_t
op_star
id|pid_list_lock
comma
r_int
id|onoff
)paren
(brace
r_int
id|i
comma
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
id|pid_list_lock
comma
id|flags
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
id|num_pids
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|onoff
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pid_list
(braket
id|i
)braket
dot
id|active
)paren
(brace
id|pid_list
(braket
id|i
)braket
dot
id|pid
op_assign
id|pid
suffix:semicolon
id|pid_list
(braket
id|i
)braket
dot
id|active
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|pid_list
(braket
id|i
)braket
dot
id|active
op_logical_and
id|pid_list
(braket
id|i
)braket
dot
id|pid
op_eq
id|pid
)paren
(brace
id|pid_list
(braket
id|i
)braket
dot
id|pid
op_assign
l_int|0
suffix:semicolon
id|pid_list
(braket
id|i
)braket
dot
id|active
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|deb_info
c_func
(paren
l_string|&quot;setting pid: %5d %04x at index %d &squot;%s&squot;&bslash;n&quot;
comma
id|pid
comma
id|pid
comma
id|ret
comma
id|onoff
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|pid_list_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|dib3000_search_status
r_int
id|dib3000_search_status
c_func
(paren
id|u16
id|irq
comma
id|u16
id|lock
)paren
(brace
r_if
c_cond
(paren
id|irq
op_amp
l_int|0x02
)paren
(brace
r_if
c_cond
(paren
id|lock
op_amp
l_int|0x01
)paren
(brace
id|deb_srch
c_func
(paren
l_string|&quot;auto search succeeded&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
singleline_comment|// auto search succeeded
)brace
r_else
(brace
id|deb_srch
c_func
(paren
l_string|&quot;auto search not successful&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
singleline_comment|// auto search failed
)brace
)brace
r_else
r_if
c_cond
(paren
id|irq
op_amp
l_int|0x01
)paren
(brace
id|deb_srch
c_func
(paren
l_string|&quot;auto search failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
singleline_comment|// auto search failed
)brace
r_return
op_minus
l_int|1
suffix:semicolon
singleline_comment|// try again
)brace
multiline_comment|/* for auto search */
DECL|variable|dib3000_seq
id|u16
id|dib3000_seq
(braket
l_int|2
)braket
(braket
l_int|2
)braket
(braket
l_int|2
)braket
op_assign
multiline_comment|/* fft,gua,   inv   */
(brace
multiline_comment|/* fft */
(brace
multiline_comment|/* gua */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/*  0   0   { 0,1 } */
(brace
l_int|3
comma
l_int|9
)brace
comma
multiline_comment|/*  0   1   { 0,1 } */
)brace
comma
(brace
(brace
l_int|2
comma
l_int|5
)brace
comma
multiline_comment|/*  1   0   { 0,1 } */
(brace
l_int|6
comma
l_int|11
)brace
comma
multiline_comment|/*  1   1   { 0,1 } */
)brace
)brace
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Patrick Boettcher &lt;patrick.boettcher@desy.de&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Common functions for the dib3000mb/dib3000mc dvb frontend drivers&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|dib3000_seq
id|EXPORT_SYMBOL
c_func
(paren
id|dib3000_seq
)paren
suffix:semicolon
DECL|variable|dib3000_read_reg
id|EXPORT_SYMBOL
c_func
(paren
id|dib3000_read_reg
)paren
suffix:semicolon
DECL|variable|dib3000_write_reg
id|EXPORT_SYMBOL
c_func
(paren
id|dib3000_write_reg
)paren
suffix:semicolon
DECL|variable|dib3000_init_pid_list
id|EXPORT_SYMBOL
c_func
(paren
id|dib3000_init_pid_list
)paren
suffix:semicolon
DECL|variable|dib3000_dealloc_pid_list
id|EXPORT_SYMBOL
c_func
(paren
id|dib3000_dealloc_pid_list
)paren
suffix:semicolon
DECL|variable|dib3000_get_pid_index
id|EXPORT_SYMBOL
c_func
(paren
id|dib3000_get_pid_index
)paren
suffix:semicolon
DECL|variable|dib3000_search_status
id|EXPORT_SYMBOL
c_func
(paren
id|dib3000_search_status
)paren
suffix:semicolon
eof
