macro_line|#include &quot;ad1848.h&quot;
multiline_comment|/*&t;From gus_card.c */
r_int
id|gus_set_midi_irq
c_func
(paren
r_int
id|num
)paren
suffix:semicolon
id|irqreturn_t
id|gusintr
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
id|dummy
)paren
suffix:semicolon
multiline_comment|/*&t;From gus_wave.c */
r_int
id|gus_wave_detect
c_func
(paren
r_int
id|baseaddr
)paren
suffix:semicolon
r_void
id|gus_wave_init
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_void
id|gus_wave_unload
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_void
id|gus_voice_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|gus_write8
c_func
(paren
r_int
id|reg
comma
r_int
r_int
id|data
)paren
suffix:semicolon
r_void
id|guswave_dma_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|gus_delay
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|gus_default_mixer_ioctl
(paren
r_int
id|dev
comma
r_int
r_int
id|cmd
comma
r_void
id|__user
op_star
id|arg
)paren
suffix:semicolon
r_void
id|gus_timer_command
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|val
)paren
suffix:semicolon
multiline_comment|/*&t;From gus_midi.c */
r_void
id|gus_midi_init
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_void
id|gus_midi_interrupt
c_func
(paren
r_int
id|dummy
)paren
suffix:semicolon
multiline_comment|/*&t;From ics2101.c */
r_int
id|ics2101_mixer_init
c_func
(paren
r_void
)paren
suffix:semicolon
eof
