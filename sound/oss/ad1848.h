DECL|macro|AD_F_CS4231
mdefine_line|#define AD_F_CS4231     0x0001  /* Returned if a CS4232 (or compatible) detected */
DECL|macro|AD_F_CS4248
mdefine_line|#define AD_F_CS4248     0x0001  /* Returned if a CS4248 (or compatible) detected */
DECL|macro|AD1848_SET_XTAL
mdefine_line|#define         AD1848_SET_XTAL         1
DECL|macro|AD1848_MIXER_REROUTE
mdefine_line|#define         AD1848_MIXER_REROUTE    2
DECL|macro|AD1848_REROUTE
mdefine_line|#define AD1848_REROUTE(oldctl, newctl) &bslash;&n;                ad1848_control(AD1848_MIXER_REROUTE, ((oldctl)&lt;&lt;8)|(newctl))
r_int
id|ad1848_init
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|io_base
comma
r_int
id|irq
comma
r_int
id|dma_playback
comma
r_int
id|dma_capture
comma
r_int
id|share_dma
comma
r_int
op_star
id|osp
comma
r_struct
id|module
op_star
id|owner
)paren
suffix:semicolon
r_void
id|ad1848_unload
(paren
r_int
id|io_base
comma
r_int
id|irq
comma
r_int
id|dma_playback
comma
r_int
id|dma_capture
comma
r_int
id|share_dma
)paren
suffix:semicolon
r_int
id|ad1848_detect
(paren
r_int
id|io_base
comma
r_int
op_star
id|flags
comma
r_int
op_star
id|osp
)paren
suffix:semicolon
r_int
id|ad1848_control
c_func
(paren
r_int
id|cmd
comma
r_int
id|arg
)paren
suffix:semicolon
r_void
id|adintr
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
r_void
id|attach_ms_sound
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
comma
r_struct
id|module
op_star
id|owner
)paren
suffix:semicolon
r_int
id|probe_ms_sound
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_void
id|unload_ms_sound
c_func
(paren
r_struct
id|address_info
op_star
id|hw_info
)paren
suffix:semicolon
eof
