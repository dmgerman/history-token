multiline_comment|/* Low-level parallel port routines for the Atari builtin port&n; *&n; * Author: Andreas Schwab &lt;schwab@issan.informatik.uni-dortmund.de&gt;&n; *&n; * Based on parport_amiga.c.&n; *&n; * The built-in Atari parallel port provides one port at a fixed address&n; * with 8 output data lines (D0 - D7), 1 output control line (STROBE)&n; * and 1 input status line (BUSY) able to cause an interrupt.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/atarihw.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/atariints.h&gt;
DECL|variable|this_port
r_static
r_struct
id|parport
op_star
id|this_port
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
r_char
DECL|function|parport_atari_read_data
id|parport_atari_read_data
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_char
id|data
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|sound_ym.rd_data_reg_sel
op_assign
l_int|15
suffix:semicolon
id|data
op_assign
id|sound_ym.rd_data_reg_sel
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
r_static
r_void
DECL|function|parport_atari_write_data
id|parport_atari_write_data
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_int
r_char
id|data
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|sound_ym.rd_data_reg_sel
op_assign
l_int|15
suffix:semicolon
id|sound_ym.wd_data
op_assign
id|data
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_int
r_char
DECL|function|parport_atari_read_control
id|parport_atari_read_control
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_char
id|control
op_assign
l_int|0
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|sound_ym.rd_data_reg_sel
op_assign
l_int|14
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sound_ym.rd_data_reg_sel
op_amp
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
)paren
id|control
op_assign
id|PARPORT_CONTROL_STROBE
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|control
suffix:semicolon
)brace
r_static
r_void
DECL|function|parport_atari_write_control
id|parport_atari_write_control
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_int
r_char
id|control
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|sound_ym.rd_data_reg_sel
op_assign
l_int|14
suffix:semicolon
r_if
c_cond
(paren
id|control
op_amp
id|PARPORT_CONTROL_STROBE
)paren
id|sound_ym.wd_data
op_assign
id|sound_ym.rd_data_reg_sel
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|5
)paren
suffix:semicolon
r_else
id|sound_ym.wd_data
op_assign
id|sound_ym.rd_data_reg_sel
op_or
(paren
l_int|1
op_lshift
l_int|5
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_int
r_char
DECL|function|parport_atari_frob_control
id|parport_atari_frob_control
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_int
r_char
id|mask
comma
r_int
r_char
id|val
)paren
(brace
r_int
r_char
id|old
op_assign
id|parport_atari_read_control
c_func
(paren
id|p
)paren
suffix:semicolon
id|parport_atari_write_control
c_func
(paren
id|p
comma
(paren
id|old
op_amp
op_complement
id|mask
)paren
op_xor
id|val
)paren
suffix:semicolon
r_return
id|old
suffix:semicolon
)brace
r_static
r_int
r_char
DECL|function|parport_atari_read_status
id|parport_atari_read_status
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_return
(paren
(paren
id|mfp.par_dt_reg
op_amp
l_int|1
ques
c_cond
l_int|0
suffix:colon
id|PARPORT_STATUS_BUSY
)paren
op_or
id|PARPORT_STATUS_SELECT
op_or
id|PARPORT_STATUS_ERROR
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|parport_atari_init_state
id|parport_atari_init_state
c_func
(paren
r_struct
id|pardevice
op_star
id|d
comma
r_struct
id|parport_state
op_star
id|s
)paren
(brace
)brace
r_static
r_void
DECL|function|parport_atari_save_state
id|parport_atari_save_state
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_struct
id|parport_state
op_star
id|s
)paren
(brace
)brace
r_static
r_void
DECL|function|parport_atari_restore_state
id|parport_atari_restore_state
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_struct
id|parport_state
op_star
id|s
)paren
(brace
)brace
r_static
r_void
DECL|function|parport_atari_interrupt
id|parport_atari_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|parport_generic_irq
c_func
(paren
id|irq
comma
(paren
r_struct
id|parport
op_star
)paren
id|dev_id
comma
id|regs
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|parport_atari_enable_irq
id|parport_atari_enable_irq
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
id|enable_irq
c_func
(paren
id|IRQ_MFP_BUSY
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|parport_atari_disable_irq
id|parport_atari_disable_irq
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
id|disable_irq
c_func
(paren
id|IRQ_MFP_BUSY
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|parport_atari_data_forward
id|parport_atari_data_forward
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Soundchip port B as output. */
id|sound_ym.rd_data_reg_sel
op_assign
l_int|7
suffix:semicolon
id|sound_ym.wd_data
op_assign
id|sound_ym.rd_data_reg_sel
op_or
l_int|0x40
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|parport_atari_data_reverse
id|parport_atari_data_reverse
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
macro_line|#if 0 /* too dangerous, can kill sound chip */
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Soundchip port B as input. */
id|sound_ym.rd_data_reg_sel
op_assign
l_int|7
suffix:semicolon
id|sound_ym.wd_data
op_assign
id|sound_ym.rd_data_reg_sel
op_amp
op_complement
l_int|0x40
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
macro_line|#endif
)brace
r_static
r_void
DECL|function|parport_atari_inc_use_count
id|parport_atari_inc_use_count
c_func
(paren
r_void
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
r_static
r_void
DECL|function|parport_atari_dec_use_count
id|parport_atari_dec_use_count
c_func
(paren
r_void
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|variable|parport_atari_ops
r_static
r_struct
id|parport_operations
id|parport_atari_ops
op_assign
(brace
id|parport_atari_write_data
comma
id|parport_atari_read_data
comma
id|parport_atari_write_control
comma
id|parport_atari_read_control
comma
id|parport_atari_frob_control
comma
id|parport_atari_read_status
comma
id|parport_atari_enable_irq
comma
id|parport_atari_disable_irq
comma
id|parport_atari_data_forward
comma
id|parport_atari_data_reverse
comma
id|parport_atari_init_state
comma
id|parport_atari_save_state
comma
id|parport_atari_restore_state
comma
id|parport_atari_inc_use_count
comma
id|parport_atari_dec_use_count
comma
id|parport_ieee1284_epp_write_data
comma
id|parport_ieee1284_epp_read_data
comma
id|parport_ieee1284_epp_write_addr
comma
id|parport_ieee1284_epp_read_addr
comma
id|parport_ieee1284_ecp_write_data
comma
id|parport_ieee1284_ecp_read_data
comma
id|parport_ieee1284_ecp_write_addr
comma
id|parport_ieee1284_write_compat
comma
id|parport_ieee1284_read_nibble
comma
id|parport_ieee1284_read_byte
comma
)brace
suffix:semicolon
r_int
id|__init
DECL|function|parport_atari_init
id|parport_atari_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|parport
op_star
id|p
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|MACH_IS_ATARI
)paren
(brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Soundchip port A/B as output. */
id|sound_ym.rd_data_reg_sel
op_assign
l_int|7
suffix:semicolon
id|sound_ym.wd_data
op_assign
(paren
id|sound_ym.rd_data_reg_sel
op_amp
l_int|0x3f
)paren
op_or
l_int|0xc0
suffix:semicolon
multiline_comment|/* STROBE high. */
id|sound_ym.rd_data_reg_sel
op_assign
l_int|14
suffix:semicolon
id|sound_ym.wd_data
op_assign
id|sound_ym.rd_data_reg_sel
op_or
(paren
l_int|1
op_lshift
l_int|5
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* MFP port I0 as input. */
id|mfp.data_dir
op_and_assign
op_complement
l_int|1
suffix:semicolon
multiline_comment|/* MFP port I0 interrupt on high-&gt;low edge. */
id|mfp.active_edge
op_and_assign
op_complement
l_int|1
suffix:semicolon
id|p
op_assign
id|parport_register_port
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|sound_ym.wd_data
comma
id|IRQ_MFP_BUSY
comma
id|PARPORT_DMA_NONE
comma
op_amp
id|parport_atari_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|IRQ_MFP_BUSY
comma
id|parport_atari_interrupt
comma
id|IRQ_TYPE_SLOW
comma
id|p-&gt;name
comma
id|p
)paren
)paren
(brace
id|parport_unregister_port
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|this_port
op_assign
id|p
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Atari built-in port using irq&bslash;n&quot;
comma
id|p-&gt;name
)paren
suffix:semicolon
id|parport_proc_register
c_func
(paren
id|p
)paren
suffix:semicolon
id|parport_announce_port
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Andreas Schwab&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Parport Driver for Atari builtin Port&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;Atari builtin Parallel Port&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
r_int
DECL|function|init_module
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|parport_atari_init
c_func
(paren
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENODEV
suffix:semicolon
)brace
r_void
DECL|function|cleanup_module
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|this_port-&gt;irq
op_ne
id|PARPORT_IRQ_NONE
)paren
id|free_irq
c_func
(paren
id|IRQ_MFP_BUSY
comma
id|this_port
)paren
suffix:semicolon
id|parport_proc_unregister
c_func
(paren
id|this_port
)paren
suffix:semicolon
id|parport_unregister_port
c_func
(paren
id|this_port
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
