macro_line|#ifndef __I2C_KEYWEST_H__
DECL|macro|__I2C_KEYWEST_H__
mdefine_line|#define __I2C_KEYWEST_H__
multiline_comment|/* The Tumbler audio equalizer can be really slow sometimes */
DECL|macro|POLL_TIMEOUT
mdefine_line|#define POLL_TIMEOUT&t;&t;(2*HZ)
multiline_comment|/* Register indices */
r_typedef
r_enum
(brace
DECL|enumerator|reg_mode
id|reg_mode
op_assign
l_int|0
comma
DECL|enumerator|reg_control
id|reg_control
comma
DECL|enumerator|reg_status
id|reg_status
comma
DECL|enumerator|reg_isr
id|reg_isr
comma
DECL|enumerator|reg_ier
id|reg_ier
comma
DECL|enumerator|reg_addr
id|reg_addr
comma
DECL|enumerator|reg_subaddr
id|reg_subaddr
comma
DECL|enumerator|reg_data
id|reg_data
DECL|typedef|reg_t
)brace
id|reg_t
suffix:semicolon
multiline_comment|/* Mode register */
DECL|macro|KW_I2C_MODE_100KHZ
mdefine_line|#define KW_I2C_MODE_100KHZ&t;0x00
DECL|macro|KW_I2C_MODE_50KHZ
mdefine_line|#define KW_I2C_MODE_50KHZ&t;0x01
DECL|macro|KW_I2C_MODE_25KHZ
mdefine_line|#define KW_I2C_MODE_25KHZ&t;0x02
DECL|macro|KW_I2C_MODE_DUMB
mdefine_line|#define KW_I2C_MODE_DUMB&t;0x00
DECL|macro|KW_I2C_MODE_STANDARD
mdefine_line|#define KW_I2C_MODE_STANDARD&t;0x04
DECL|macro|KW_I2C_MODE_STANDARDSUB
mdefine_line|#define KW_I2C_MODE_STANDARDSUB&t;0x08
DECL|macro|KW_I2C_MODE_COMBINED
mdefine_line|#define KW_I2C_MODE_COMBINED&t;0x0C
DECL|macro|KW_I2C_MODE_MODE_MASK
mdefine_line|#define KW_I2C_MODE_MODE_MASK&t;0x0C
DECL|macro|KW_I2C_MODE_CHAN_MASK
mdefine_line|#define KW_I2C_MODE_CHAN_MASK&t;0xF0
multiline_comment|/* Control register */
DECL|macro|KW_I2C_CTL_AAK
mdefine_line|#define KW_I2C_CTL_AAK&t;&t;0x01
DECL|macro|KW_I2C_CTL_XADDR
mdefine_line|#define KW_I2C_CTL_XADDR&t;0x02
DECL|macro|KW_I2C_CTL_STOP
mdefine_line|#define KW_I2C_CTL_STOP&t;&t;0x04
DECL|macro|KW_I2C_CTL_START
mdefine_line|#define KW_I2C_CTL_START&t;0x08
multiline_comment|/* Status register */
DECL|macro|KW_I2C_STAT_BUSY
mdefine_line|#define KW_I2C_STAT_BUSY&t;0x01
DECL|macro|KW_I2C_STAT_LAST_AAK
mdefine_line|#define KW_I2C_STAT_LAST_AAK&t;0x02
DECL|macro|KW_I2C_STAT_LAST_RW
mdefine_line|#define KW_I2C_STAT_LAST_RW&t;0x04
DECL|macro|KW_I2C_STAT_SDA
mdefine_line|#define KW_I2C_STAT_SDA&t;&t;0x08
DECL|macro|KW_I2C_STAT_SCL
mdefine_line|#define KW_I2C_STAT_SCL&t;&t;0x10
multiline_comment|/* IER &amp; ISR registers */
DECL|macro|KW_I2C_IRQ_DATA
mdefine_line|#define KW_I2C_IRQ_DATA&t;&t;0x01
DECL|macro|KW_I2C_IRQ_ADDR
mdefine_line|#define KW_I2C_IRQ_ADDR&t;&t;0x02
DECL|macro|KW_I2C_IRQ_STOP
mdefine_line|#define KW_I2C_IRQ_STOP&t;&t;0x04
DECL|macro|KW_I2C_IRQ_START
mdefine_line|#define KW_I2C_IRQ_START&t;0x08
DECL|macro|KW_I2C_IRQ_MASK
mdefine_line|#define KW_I2C_IRQ_MASK&t;&t;0x0F
multiline_comment|/* Physical interface */
DECL|struct|keywest_iface
r_struct
id|keywest_iface
(brace
DECL|member|node
r_struct
id|device_node
op_star
id|node
suffix:semicolon
DECL|member|base
r_void
id|__iomem
op_star
id|base
suffix:semicolon
DECL|member|bsteps
r_int
id|bsteps
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|channels
r_struct
id|keywest_chan
op_star
id|channels
suffix:semicolon
DECL|member|chan_count
r_int
id|chan_count
suffix:semicolon
DECL|member|cur_mode
id|u8
id|cur_mode
suffix:semicolon
DECL|member|read_write
r_char
id|read_write
suffix:semicolon
DECL|member|data
id|u8
op_star
id|data
suffix:semicolon
DECL|member|datalen
r_int
id|datalen
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|result
r_int
id|result
suffix:semicolon
DECL|member|timeout_timer
r_struct
id|timer_list
id|timeout_timer
suffix:semicolon
DECL|member|complete
r_struct
id|completion
id|complete
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|state_idle
id|state_idle
comma
DECL|enumerator|state_addr
id|state_addr
comma
DECL|enumerator|state_read
id|state_read
comma
DECL|enumerator|state_write
id|state_write
comma
DECL|enumerator|state_stop
id|state_stop
comma
DECL|enumerator|state_dead
id|state_dead
)brace
suffix:semicolon
multiline_comment|/* Channel on an interface */
DECL|struct|keywest_chan
r_struct
id|keywest_chan
(brace
DECL|member|adapter
r_struct
id|i2c_adapter
id|adapter
suffix:semicolon
DECL|member|iface
r_struct
id|keywest_iface
op_star
id|iface
suffix:semicolon
DECL|member|chan_no
r_int
id|chan_no
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Register access */
DECL|function|__read_reg
r_static
r_inline
id|u8
id|__read_reg
c_func
(paren
r_struct
id|keywest_iface
op_star
id|iface
comma
id|reg_t
id|reg
)paren
(brace
r_return
id|in_8
c_func
(paren
id|iface-&gt;base
op_plus
(paren
(paren
(paren
r_int
)paren
id|reg
)paren
op_lshift
id|iface-&gt;bsteps
)paren
)paren
suffix:semicolon
)brace
DECL|function|__write_reg
r_static
r_inline
r_void
id|__write_reg
c_func
(paren
r_struct
id|keywest_iface
op_star
id|iface
comma
id|reg_t
id|reg
comma
id|u8
id|val
)paren
(brace
id|out_8
c_func
(paren
id|iface-&gt;base
op_plus
(paren
(paren
(paren
r_int
)paren
id|reg
)paren
op_lshift
id|iface-&gt;bsteps
)paren
comma
id|val
)paren
suffix:semicolon
(paren
r_void
)paren
id|__read_reg
c_func
(paren
id|iface
comma
id|reg_subaddr
)paren
suffix:semicolon
)brace
DECL|macro|write_reg
mdefine_line|#define write_reg(reg, val)&t;__write_reg(iface, reg, val) 
DECL|macro|read_reg
mdefine_line|#define read_reg(reg)&t;&t;__read_reg(iface, reg) 
macro_line|#endif /* __I2C_KEYWEST_H__ */
eof
