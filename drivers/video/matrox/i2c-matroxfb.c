multiline_comment|/*&n; *&n; * Hardware accelerated Matrox Millennium I, II, Mystique, G100, G200, G400 and G450.&n; *&n; * (c) 1998-2002 Petr Vandrovec &lt;vandrove@vc.cvut.cz&gt;&n; *&n; * Version: 1.64 2002/06/10&n; *&n; * See matroxfb_base.c for contributors.&n; *&n; */
macro_line|#include &quot;matroxfb_base.h&quot;
macro_line|#include &quot;matroxfb_maven.h&quot;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
multiline_comment|/* MGA-TVO I2C for G200, G400 */
DECL|macro|MAT_CLK
mdefine_line|#define MAT_CLK&t;&t;0x20
DECL|macro|MAT_DATA
mdefine_line|#define MAT_DATA&t;0x10
multiline_comment|/* primary head DDC for Mystique(?), G100, G200, G400 */
DECL|macro|DDC1_CLK
mdefine_line|#define DDC1_CLK&t;0x08
DECL|macro|DDC1_DATA
mdefine_line|#define DDC1_DATA&t;0x02
multiline_comment|/* primary head DDC for Millennium, Millennium II */
DECL|macro|DDC1B_CLK
mdefine_line|#define DDC1B_CLK&t;0x10
DECL|macro|DDC1B_DATA
mdefine_line|#define DDC1B_DATA&t;0x04
multiline_comment|/* secondary head DDC for G400 */
DECL|macro|DDC2_CLK
mdefine_line|#define DDC2_CLK&t;0x04
DECL|macro|DDC2_DATA
mdefine_line|#define DDC2_DATA&t;0x01
multiline_comment|/******************************************************/
DECL|struct|matroxfb_dh_maven_info
r_struct
id|matroxfb_dh_maven_info
(brace
DECL|member|maven
r_struct
id|i2c_bit_adapter
id|maven
suffix:semicolon
DECL|member|ddc1
r_struct
id|i2c_bit_adapter
id|ddc1
suffix:semicolon
DECL|member|ddc2
r_struct
id|i2c_bit_adapter
id|ddc2
suffix:semicolon
)brace
suffix:semicolon
DECL|function|matroxfb_read_gpio
r_static
r_int
id|matroxfb_read_gpio
c_func
(paren
r_struct
id|matrox_fb_info
op_star
id|minfo
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|v
suffix:semicolon
id|matroxfb_DAC_lock_irqsave
c_func
(paren
id|flags
)paren
suffix:semicolon
id|v
op_assign
id|matroxfb_DAC_in
c_func
(paren
id|PMINFO
id|DAC_XGENIODATA
)paren
suffix:semicolon
id|matroxfb_DAC_unlock_irqrestore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|v
suffix:semicolon
)brace
DECL|function|matroxfb_set_gpio
r_static
r_void
id|matroxfb_set_gpio
c_func
(paren
r_struct
id|matrox_fb_info
op_star
id|minfo
comma
r_int
id|mask
comma
r_int
id|val
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|v
suffix:semicolon
id|matroxfb_DAC_lock_irqsave
c_func
(paren
id|flags
)paren
suffix:semicolon
id|v
op_assign
(paren
id|matroxfb_DAC_in
c_func
(paren
id|PMINFO
id|DAC_XGENIOCTRL
)paren
op_amp
id|mask
)paren
op_or
id|val
suffix:semicolon
id|matroxfb_DAC_out
c_func
(paren
id|PMINFO
id|DAC_XGENIOCTRL
comma
id|v
)paren
suffix:semicolon
multiline_comment|/* We must reset GENIODATA very often... XFree plays with this register */
id|matroxfb_DAC_out
c_func
(paren
id|PMINFO
id|DAC_XGENIODATA
comma
l_int|0x00
)paren
suffix:semicolon
id|matroxfb_DAC_unlock_irqrestore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* software I2C functions */
DECL|function|matroxfb_i2c_set
r_static
r_inline
r_void
id|matroxfb_i2c_set
c_func
(paren
r_struct
id|matrox_fb_info
op_star
id|minfo
comma
r_int
id|mask
comma
r_int
id|state
)paren
(brace
r_if
c_cond
(paren
id|state
)paren
id|state
op_assign
l_int|0
suffix:semicolon
r_else
id|state
op_assign
id|mask
suffix:semicolon
id|matroxfb_set_gpio
c_func
(paren
id|minfo
comma
op_complement
id|mask
comma
id|state
)paren
suffix:semicolon
)brace
DECL|function|matroxfb_gpio_setsda
r_static
r_void
id|matroxfb_gpio_setsda
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|state
)paren
(brace
r_struct
id|i2c_bit_adapter
op_star
id|b
op_assign
id|data
suffix:semicolon
id|matroxfb_i2c_set
c_func
(paren
id|b-&gt;minfo
comma
id|b-&gt;mask.data
comma
id|state
)paren
suffix:semicolon
)brace
DECL|function|matroxfb_gpio_setscl
r_static
r_void
id|matroxfb_gpio_setscl
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|state
)paren
(brace
r_struct
id|i2c_bit_adapter
op_star
id|b
op_assign
id|data
suffix:semicolon
id|matroxfb_i2c_set
c_func
(paren
id|b-&gt;minfo
comma
id|b-&gt;mask.clock
comma
id|state
)paren
suffix:semicolon
)brace
DECL|function|matroxfb_gpio_getsda
r_static
r_int
id|matroxfb_gpio_getsda
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|i2c_bit_adapter
op_star
id|b
op_assign
id|data
suffix:semicolon
r_return
(paren
id|matroxfb_read_gpio
c_func
(paren
id|b-&gt;minfo
)paren
op_amp
id|b-&gt;mask.data
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|matroxfb_gpio_getscl
r_static
r_int
id|matroxfb_gpio_getscl
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|i2c_bit_adapter
op_star
id|b
op_assign
id|data
suffix:semicolon
r_return
(paren
id|matroxfb_read_gpio
c_func
(paren
id|b-&gt;minfo
)paren
op_amp
id|b-&gt;mask.clock
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|matroxfb_dh_inc_use
r_static
r_void
id|matroxfb_dh_inc_use
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|dummy
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
DECL|function|matroxfb_dh_dec_use
r_static
r_void
id|matroxfb_dh_dec_use
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|dummy
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|variable|matrox_i2c_adapter_template
r_static
r_struct
id|i2c_adapter
id|matrox_i2c_adapter_template
op_assign
(brace
dot
id|id
op_assign
id|I2C_HW_B_G400
comma
dot
id|inc_use
op_assign
id|matroxfb_dh_inc_use
comma
dot
id|dec_use
op_assign
id|matroxfb_dh_dec_use
comma
)brace
suffix:semicolon
DECL|variable|matrox_i2c_algo_template
r_static
r_struct
id|i2c_algo_bit_data
id|matrox_i2c_algo_template
op_assign
(brace
l_int|NULL
comma
id|matroxfb_gpio_setsda
comma
id|matroxfb_gpio_setscl
comma
id|matroxfb_gpio_getsda
comma
id|matroxfb_gpio_getscl
comma
l_int|10
comma
l_int|10
comma
l_int|100
comma
)brace
suffix:semicolon
DECL|function|i2c_bus_reg
r_static
r_int
id|i2c_bus_reg
c_func
(paren
r_struct
id|i2c_bit_adapter
op_star
id|b
comma
r_struct
id|matrox_fb_info
op_star
id|minfo
comma
r_int
r_int
id|data
comma
r_int
r_int
id|clock
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_int
id|err
suffix:semicolon
id|b-&gt;minfo
op_assign
id|minfo
suffix:semicolon
id|b-&gt;mask.data
op_assign
id|data
suffix:semicolon
id|b-&gt;mask.clock
op_assign
id|clock
suffix:semicolon
id|b-&gt;adapter
op_assign
id|matrox_i2c_adapter_template
suffix:semicolon
id|sprintf
c_func
(paren
id|b-&gt;adapter.name
comma
id|name
comma
id|GET_FB_IDX
c_func
(paren
id|minfo-&gt;fbcon.node
)paren
)paren
suffix:semicolon
id|b-&gt;adapter.data
op_assign
id|b
suffix:semicolon
id|b-&gt;adapter.algo_data
op_assign
op_amp
id|b-&gt;bac
suffix:semicolon
id|b-&gt;bac
op_assign
id|matrox_i2c_algo_template
suffix:semicolon
id|b-&gt;bac.data
op_assign
id|b
suffix:semicolon
id|err
op_assign
id|i2c_bit_add_bus
c_func
(paren
op_amp
id|b-&gt;adapter
)paren
suffix:semicolon
id|b-&gt;initialized
op_assign
op_logical_neg
id|err
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|i2c_bit_bus_del
r_static
r_void
id|i2c_bit_bus_del
c_func
(paren
r_struct
id|i2c_bit_adapter
op_star
id|b
)paren
(brace
r_if
c_cond
(paren
id|b-&gt;initialized
)paren
(brace
id|i2c_bit_del_bus
c_func
(paren
op_amp
id|b-&gt;adapter
)paren
suffix:semicolon
id|b-&gt;initialized
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|i2c_maven_done
r_static
r_inline
r_void
id|i2c_maven_done
c_func
(paren
r_struct
id|matroxfb_dh_maven_info
op_star
id|minfo2
)paren
(brace
id|i2c_bit_bus_del
c_func
(paren
op_amp
id|minfo2-&gt;maven
)paren
suffix:semicolon
)brace
DECL|function|i2c_ddc1_done
r_static
r_inline
r_void
id|i2c_ddc1_done
c_func
(paren
r_struct
id|matroxfb_dh_maven_info
op_star
id|minfo2
)paren
(brace
id|i2c_bit_bus_del
c_func
(paren
op_amp
id|minfo2-&gt;ddc1
)paren
suffix:semicolon
)brace
DECL|function|i2c_ddc2_done
r_static
r_inline
r_void
id|i2c_ddc2_done
c_func
(paren
r_struct
id|matroxfb_dh_maven_info
op_star
id|minfo2
)paren
(brace
id|i2c_bit_bus_del
c_func
(paren
op_amp
id|minfo2-&gt;ddc2
)paren
suffix:semicolon
)brace
DECL|function|i2c_matroxfb_probe
r_static
r_void
op_star
id|i2c_matroxfb_probe
c_func
(paren
r_struct
id|matrox_fb_info
op_star
id|minfo
)paren
(brace
r_int
id|err
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|matroxfb_dh_maven_info
op_star
id|m2info
suffix:semicolon
id|m2info
op_assign
(paren
r_struct
id|matroxfb_dh_maven_info
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|m2info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|m2info
)paren
r_return
l_int|NULL
suffix:semicolon
id|matroxfb_DAC_lock_irqsave
c_func
(paren
id|flags
)paren
suffix:semicolon
id|matroxfb_DAC_out
c_func
(paren
id|PMINFO
id|DAC_XGENIODATA
comma
l_int|0xFF
)paren
suffix:semicolon
id|matroxfb_DAC_out
c_func
(paren
id|PMINFO
id|DAC_XGENIOCTRL
comma
l_int|0x00
)paren
suffix:semicolon
id|matroxfb_DAC_unlock_irqrestore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|memset
c_func
(paren
id|m2info
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|m2info
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ACCESS_FBINFO
c_func
(paren
id|chip
)paren
)paren
(brace
r_case
id|MGA_2064
suffix:colon
r_case
id|MGA_2164
suffix:colon
id|err
op_assign
id|i2c_bus_reg
c_func
(paren
op_amp
id|m2info-&gt;ddc1
comma
id|minfo
comma
id|DDC1B_DATA
comma
id|DDC1B_CLK
comma
l_string|&quot;DDC:fb%u #0 on i2c-matroxfb&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
id|i2c_bus_reg
c_func
(paren
op_amp
id|m2info-&gt;ddc1
comma
id|minfo
comma
id|DDC1_DATA
comma
id|DDC1_CLK
comma
l_string|&quot;DDC:fb%u #0 on i2c-matroxfb&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
r_goto
id|fail_ddc1
suffix:semicolon
r_if
c_cond
(paren
id|ACCESS_FBINFO
c_func
(paren
id|devflags.dualhead
)paren
)paren
(brace
id|err
op_assign
id|i2c_bus_reg
c_func
(paren
op_amp
id|m2info-&gt;ddc2
comma
id|minfo
comma
id|DDC2_DATA
comma
id|DDC2_CLK
comma
l_string|&quot;DDC:fb%u #1 on i2c-matroxfb&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
op_minus
id|ENODEV
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2c-matroxfb: VGA-&gt;TV plug detected, DDC unavailable.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|err
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2c-matroxfb: Could not register secondary output i2c bus. Continuing anyway.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Register maven bus even on G450/G550 */
id|err
op_assign
id|i2c_bus_reg
c_func
(paren
op_amp
id|m2info-&gt;maven
comma
id|minfo
comma
id|MAT_DATA
comma
id|MAT_CLK
comma
l_string|&quot;MAVEN:fb%u on i2c-matroxfb&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2c-matroxfb: Could not register Maven i2c bus. Continuing anyway.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|m2info
suffix:semicolon
id|fail_ddc1
suffix:colon
suffix:semicolon
id|kfree
c_func
(paren
id|m2info
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-matroxfb: Could not register primary adapter DDC bus.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|i2c_matroxfb_remove
r_static
r_void
id|i2c_matroxfb_remove
c_func
(paren
r_struct
id|matrox_fb_info
op_star
id|minfo
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|matroxfb_dh_maven_info
op_star
id|m2info
op_assign
id|data
suffix:semicolon
id|i2c_maven_done
c_func
(paren
id|m2info
)paren
suffix:semicolon
id|i2c_ddc2_done
c_func
(paren
id|m2info
)paren
suffix:semicolon
id|i2c_ddc1_done
c_func
(paren
id|m2info
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|m2info
)paren
suffix:semicolon
)brace
DECL|variable|i2c_matroxfb
r_static
r_struct
id|matroxfb_driver
id|i2c_matroxfb
op_assign
(brace
dot
id|node
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|i2c_matroxfb.node
)paren
comma
dot
id|name
op_assign
l_string|&quot;i2c-matroxfb&quot;
comma
dot
id|probe
op_assign
id|i2c_matroxfb_probe
comma
dot
id|remove
op_assign
id|i2c_matroxfb_remove
comma
)brace
suffix:semicolon
DECL|function|i2c_matroxfb_init
r_static
r_int
id|__init
id|i2c_matroxfb_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|matroxfb_register_driver
c_func
(paren
op_amp
id|i2c_matroxfb
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-matroxfb: failed to register driver&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2c_matroxfb_exit
r_static
r_void
id|__exit
id|i2c_matroxfb_exit
c_func
(paren
r_void
)paren
(brace
id|matroxfb_unregister_driver
c_func
(paren
op_amp
id|i2c_matroxfb
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;(c) 1999-2002 Petr Vandrovec &lt;vandrove@vc.cvut.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Support module providing I2C buses present on Matrox videocards&quot;
)paren
suffix:semicolon
DECL|variable|i2c_matroxfb_init
id|module_init
c_func
(paren
id|i2c_matroxfb_init
)paren
suffix:semicolon
DECL|variable|i2c_matroxfb_exit
id|module_exit
c_func
(paren
id|i2c_matroxfb_exit
)paren
suffix:semicolon
multiline_comment|/* no __setup required */
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
