macro_line|#ifndef _M68K_MACHDEP_H
DECL|macro|_M68K_MACHDEP_H
mdefine_line|#define _M68K_MACHDEP_H
r_struct
id|pt_regs
suffix:semicolon
r_struct
id|kbd_repeat
suffix:semicolon
r_struct
id|mktime
suffix:semicolon
r_struct
id|hwclk_time
suffix:semicolon
r_struct
id|buffer_head
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mach_sched_init
)paren
(paren
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
suffix:semicolon
multiline_comment|/* machine dependent keyboard functions */
r_extern
r_int
(paren
op_star
id|mach_keyb_init
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|mach_kbdrate
)paren
(paren
r_struct
id|kbd_repeat
op_star
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mach_kbd_leds
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|mach_kbd_translate
)paren
(paren
r_int
r_char
id|scancode
comma
r_int
r_char
op_star
id|keycode
comma
r_char
id|raw_mode
)paren
suffix:semicolon
multiline_comment|/* machine dependent irq functions */
r_extern
r_void
(paren
op_star
id|mach_init_IRQ
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
(paren
op_star
id|mach_default_handler
)paren
(braket
)braket
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|mach_request_irq
)paren
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mach_free_irq
)paren
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mach_get_model
)paren
(paren
r_char
op_star
id|model
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|mach_get_hardware_list
)paren
(paren
r_char
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|mach_get_irq_list
)paren
(paren
r_char
op_star
id|buf
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mach_process_int
)paren
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
suffix:semicolon
multiline_comment|/* machine dependent timer functions */
r_extern
r_int
r_int
(paren
op_star
id|mach_gettimeoffset
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mach_gettod
)paren
(paren
r_int
op_star
id|year
comma
r_int
op_star
id|mon
comma
r_int
op_star
id|day
comma
r_int
op_star
id|hour
comma
r_int
op_star
id|min
comma
r_int
op_star
id|sec
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|mach_hwclk
)paren
(paren
r_int
comma
r_struct
id|hwclk_time
op_star
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|mach_set_clock_mmss
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mach_reset
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mach_halt
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mach_power_off
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
(paren
op_star
id|mach_hd_init
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mach_hd_setup
)paren
(paren
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|mach_max_dma_address
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mach_floppy_setup
)paren
(paren
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mach_floppy_eject
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mach_heartbeat
)paren
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mach_l2_flush
)paren
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|mach_sysrq_key
suffix:semicolon
r_extern
r_int
id|mach_sysrq_shift_state
suffix:semicolon
r_extern
r_int
id|mach_sysrq_shift_mask
suffix:semicolon
r_extern
r_char
op_star
id|mach_sysrq_xlate
suffix:semicolon
macro_line|#endif /* _M68K_MACHDEP_H */
eof
