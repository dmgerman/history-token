multiline_comment|/* credit winbond-840.c&n; */
macro_line|#include &lt;asm/io.h&gt;
DECL|struct|eeprom_ops
r_struct
id|eeprom_ops
(brace
DECL|member|set_cs
r_void
(paren
op_star
id|set_cs
)paren
(paren
r_void
op_star
id|ee
)paren
suffix:semicolon
DECL|member|clear_cs
r_void
(paren
op_star
id|clear_cs
)paren
(paren
r_void
op_star
id|ee
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EEPOL_EEDI
mdefine_line|#define EEPOL_EEDI&t;0x01
DECL|macro|EEPOL_EEDO
mdefine_line|#define EEPOL_EEDO&t;0x02
DECL|macro|EEPOL_EECLK
mdefine_line|#define EEPOL_EECLK&t;0x04
DECL|macro|EEPOL_EESEL
mdefine_line|#define EEPOL_EESEL&t;0x08
DECL|struct|eeprom
r_struct
id|eeprom
(brace
DECL|member|dev
r_void
op_star
id|dev
suffix:semicolon
DECL|member|ops
r_struct
id|eeprom_ops
op_star
id|ops
suffix:semicolon
DECL|member|addr
r_void
id|__iomem
op_star
id|addr
suffix:semicolon
DECL|member|ee_addr_bits
r_int
id|ee_addr_bits
suffix:semicolon
DECL|member|eesel
r_int
id|eesel
suffix:semicolon
DECL|member|eeclk
r_int
id|eeclk
suffix:semicolon
DECL|member|eedo
r_int
id|eedo
suffix:semicolon
DECL|member|eedi
r_int
id|eedi
suffix:semicolon
DECL|member|polarity
r_int
id|polarity
suffix:semicolon
DECL|member|ee_state
r_int
id|ee_state
suffix:semicolon
DECL|member|lock
id|spinlock_t
op_star
id|lock
suffix:semicolon
DECL|member|cache
id|u32
op_star
id|cache
suffix:semicolon
)brace
suffix:semicolon
id|u8
id|eeprom_readb
c_func
(paren
r_struct
id|eeprom
op_star
id|ee
comma
r_int
id|address
)paren
suffix:semicolon
r_void
id|eeprom_read
c_func
(paren
r_struct
id|eeprom
op_star
id|ee
comma
r_int
id|address
comma
id|u8
op_star
id|bytes
comma
r_int
id|count
)paren
suffix:semicolon
r_void
id|eeprom_writeb
c_func
(paren
r_struct
id|eeprom
op_star
id|ee
comma
r_int
id|address
comma
id|u8
id|data
)paren
suffix:semicolon
r_void
id|eeprom_write
c_func
(paren
r_struct
id|eeprom
op_star
id|ee
comma
r_int
id|address
comma
id|u8
op_star
id|bytes
comma
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/* The EEPROM commands include the alway-set leading bit. */
DECL|enum|EEPROM_Cmds
r_enum
id|EEPROM_Cmds
(brace
DECL|enumerator|EE_WriteCmd
DECL|enumerator|EE_ReadCmd
DECL|enumerator|EE_EraseCmd
id|EE_WriteCmd
op_assign
(paren
l_int|5
op_lshift
l_int|6
)paren
comma
id|EE_ReadCmd
op_assign
(paren
l_int|6
op_lshift
l_int|6
)paren
comma
id|EE_EraseCmd
op_assign
(paren
l_int|7
op_lshift
l_int|6
)paren
comma
)brace
suffix:semicolon
DECL|function|setup_ee_mem_bitbanger
r_void
id|setup_ee_mem_bitbanger
c_func
(paren
r_struct
id|eeprom
op_star
id|ee
comma
r_void
id|__iomem
op_star
id|memaddr
comma
r_int
id|eesel_bit
comma
r_int
id|eeclk_bit
comma
r_int
id|eedo_bit
comma
r_int
id|eedi_bit
comma
r_int
id|polarity
)paren
(brace
id|ee-&gt;addr
op_assign
id|memaddr
suffix:semicolon
id|ee-&gt;eesel
op_assign
l_int|1
op_lshift
id|eesel_bit
suffix:semicolon
id|ee-&gt;eeclk
op_assign
l_int|1
op_lshift
id|eeclk_bit
suffix:semicolon
id|ee-&gt;eedo
op_assign
l_int|1
op_lshift
id|eedo_bit
suffix:semicolon
id|ee-&gt;eedi
op_assign
l_int|1
op_lshift
id|eedi_bit
suffix:semicolon
id|ee-&gt;polarity
op_assign
id|polarity
suffix:semicolon
op_star
id|ee-&gt;cache
op_assign
id|readl
c_func
(paren
id|ee-&gt;addr
)paren
suffix:semicolon
)brace
multiline_comment|/* foo. put this in a .c file */
DECL|function|eeprom_update
r_static
r_inline
r_void
id|eeprom_update
c_func
(paren
r_struct
id|eeprom
op_star
id|ee
comma
id|u32
id|mask
comma
r_int
id|pol
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u32
id|data
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
id|ee-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|data
op_assign
op_star
id|ee-&gt;cache
suffix:semicolon
id|data
op_and_assign
op_complement
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|pol
)paren
id|data
op_or_assign
id|mask
suffix:semicolon
op_star
id|ee-&gt;cache
op_assign
id|data
suffix:semicolon
singleline_comment|//printk(&quot;update: %08x&bslash;n&quot;, data);
id|writel
c_func
(paren
id|data
comma
id|ee-&gt;addr
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|ee-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|eeprom_clk_lo
r_void
id|eeprom_clk_lo
c_func
(paren
r_struct
id|eeprom
op_star
id|ee
)paren
(brace
r_int
id|pol
op_assign
op_logical_neg
op_logical_neg
(paren
id|ee-&gt;polarity
op_amp
id|EEPOL_EECLK
)paren
suffix:semicolon
id|eeprom_update
c_func
(paren
id|ee
comma
id|ee-&gt;eeclk
comma
id|pol
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|eeprom_clk_hi
r_void
id|eeprom_clk_hi
c_func
(paren
r_struct
id|eeprom
op_star
id|ee
)paren
(brace
r_int
id|pol
op_assign
op_logical_neg
op_logical_neg
(paren
id|ee-&gt;polarity
op_amp
id|EEPOL_EECLK
)paren
suffix:semicolon
id|eeprom_update
c_func
(paren
id|ee
comma
id|ee-&gt;eeclk
comma
op_logical_neg
id|pol
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|eeprom_send_addr
r_void
id|eeprom_send_addr
c_func
(paren
r_struct
id|eeprom
op_star
id|ee
comma
r_int
id|address
)paren
(brace
r_int
id|pol
op_assign
op_logical_neg
op_logical_neg
(paren
id|ee-&gt;polarity
op_amp
id|EEPOL_EEDI
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
id|address
op_or_assign
l_int|6
op_lshift
l_int|6
suffix:semicolon
multiline_comment|/* Shift the read command bits out. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|11
suffix:semicolon
id|i
op_increment
)paren
(brace
id|eeprom_update
c_func
(paren
id|ee
comma
id|ee-&gt;eedi
comma
(paren
(paren
id|address
op_rshift
l_int|10
)paren
op_amp
l_int|1
)paren
op_xor
id|pol
)paren
suffix:semicolon
id|address
op_lshift_assign
l_int|1
suffix:semicolon
id|eeprom_clk_hi
c_func
(paren
id|ee
)paren
suffix:semicolon
id|eeprom_clk_lo
c_func
(paren
id|ee
)paren
suffix:semicolon
)brace
id|eeprom_update
c_func
(paren
id|ee
comma
id|ee-&gt;eedi
comma
id|pol
)paren
suffix:semicolon
)brace
DECL|function|eeprom_readw
id|u16
id|eeprom_readw
c_func
(paren
r_struct
id|eeprom
op_star
id|ee
comma
r_int
id|address
)paren
(brace
r_int
id|i
suffix:semicolon
id|u16
id|res
op_assign
l_int|0
suffix:semicolon
id|eeprom_clk_lo
c_func
(paren
id|ee
)paren
suffix:semicolon
id|eeprom_update
c_func
(paren
id|ee
comma
id|ee-&gt;eesel
comma
l_int|1
op_xor
op_logical_neg
op_logical_neg
(paren
id|ee-&gt;polarity
op_amp
id|EEPOL_EESEL
)paren
)paren
suffix:semicolon
id|eeprom_send_addr
c_func
(paren
id|ee
comma
id|address
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|u32
id|data
suffix:semicolon
id|eeprom_clk_hi
c_func
(paren
id|ee
)paren
suffix:semicolon
id|res
op_lshift_assign
l_int|1
suffix:semicolon
id|data
op_assign
id|readl
c_func
(paren
id|ee-&gt;addr
)paren
suffix:semicolon
singleline_comment|//printk(&quot;eeprom_readw: %08x&bslash;n&quot;, data);
id|res
op_or_assign
op_logical_neg
op_logical_neg
(paren
id|data
op_amp
id|ee-&gt;eedo
)paren
op_xor
op_logical_neg
op_logical_neg
(paren
id|ee-&gt;polarity
op_amp
id|EEPOL_EEDO
)paren
suffix:semicolon
id|eeprom_clk_lo
c_func
(paren
id|ee
)paren
suffix:semicolon
)brace
id|eeprom_update
c_func
(paren
id|ee
comma
id|ee-&gt;eesel
comma
l_int|0
op_xor
op_logical_neg
op_logical_neg
(paren
id|ee-&gt;polarity
op_amp
id|EEPOL_EESEL
)paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|eeprom_writeb
r_void
id|eeprom_writeb
c_func
(paren
r_struct
id|eeprom
op_star
id|ee
comma
r_int
id|address
comma
id|u8
id|data
)paren
(brace
)brace
eof
