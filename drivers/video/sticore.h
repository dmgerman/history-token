macro_line|#ifndef STICORE_H
DECL|macro|STICORE_H
mdefine_line|#define STICORE_H
multiline_comment|/* generic STI structures &amp; functions */
macro_line|#if 0
mdefine_line|#define DPRINTK(x)&t;printk x
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(x) 
macro_line|#endif
DECL|macro|MAX_STI_ROMS
mdefine_line|#define MAX_STI_ROMS 4&t;&t;/* max no. of ROMs which this driver handles */
DECL|macro|STI_REGION_MAX
mdefine_line|#define STI_REGION_MAX 8&t;/* hardcoded STI constants */
DECL|macro|STI_DEV_NAME_LENGTH
mdefine_line|#define STI_DEV_NAME_LENGTH 32
DECL|macro|STI_MONITOR_MAX
mdefine_line|#define STI_MONITOR_MAX 256
DECL|macro|STI_FONT_HPROMAN8
mdefine_line|#define STI_FONT_HPROMAN8 1
DECL|macro|STI_FONT_KANA8
mdefine_line|#define STI_FONT_KANA8 2
multiline_comment|/* The latency of the STI functions cannot really be reduced by setting&n; * this to 0;  STI doesn&squot;t seem to be designed to allow calling a different&n; * function (or the same function with different arguments) after a&n; * function exited with 1 as return value.&n; *&n; * As all of the functions below could be called from interrupt context,&n; * we have to spin_lock_irqsave around the do { ret = bla(); } while(ret==1)&n; * block.  Really bad latency there.&n; *&n; * Probably the best solution to all this is have the generic code manage&n; * the screen buffer and a kernel thread to call STI occasionally.&n; * &n; * Luckily, the frame buffer guys have the same problem so we can just wait&n; * for them to fix it and steal their solution.   prumpf&n; */
DECL|macro|STI_WAIT
mdefine_line|#define STI_WAIT 1
macro_line|#include &lt;asm/io.h&gt; /* for USE_HPPA_IOREMAP */
macro_line|#if USE_HPPA_IOREMAP
DECL|macro|STI_PTR
mdefine_line|#define STI_PTR(p)&t;(p)
DECL|macro|PTR_STI
mdefine_line|#define PTR_STI(p)&t;(p)
DECL|function|STI_CALL
r_static
r_inline
r_int
id|STI_CALL
c_func
(paren
r_int
r_int
id|func
comma
r_void
op_star
id|flags
comma
r_void
op_star
id|inptr
comma
r_void
op_star
id|outptr
comma
r_void
op_star
id|glob_cfg
)paren
(brace
r_int
(paren
op_star
id|f
)paren
(paren
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
)paren
suffix:semicolon
id|f
op_assign
(paren
r_void
op_star
)paren
id|func
suffix:semicolon
r_return
id|f
c_func
(paren
id|flags
comma
id|inptr
comma
id|outptr
comma
id|glob_cfg
)paren
suffix:semicolon
)brace
macro_line|#else /* !USE_HPPA_IOREMAP */
DECL|macro|STI_PTR
mdefine_line|#define STI_PTR(p)&t;( virt_to_phys(p) )
DECL|macro|PTR_STI
mdefine_line|#define PTR_STI(p)&t;( phys_to_virt((long)p) )
DECL|macro|STI_CALL
mdefine_line|#define STI_CALL(func, flags, inptr, outptr, glob_cfg) &bslash;&n;       ({                                                      &bslash;&n;               pdc_sti_call( func, (unsigned long)STI_PTR(flags), &bslash;&n;                                   (unsigned long)STI_PTR(inptr), &bslash;&n;                                   (unsigned long)STI_PTR(outptr), &bslash;&n;                                   (unsigned long)STI_PTR(glob_cfg)); &bslash;&n;       })
macro_line|#endif /* USE_HPPA_IOREMAP */
DECL|macro|sti_onscreen_x
mdefine_line|#define sti_onscreen_x(sti) (sti-&gt;glob_cfg-&gt;onscreen_x)
DECL|macro|sti_onscreen_y
mdefine_line|#define sti_onscreen_y(sti) (sti-&gt;glob_cfg-&gt;onscreen_y)
multiline_comment|/* sti_font_xy() use the native font ROM ! */
DECL|macro|sti_font_x
mdefine_line|#define sti_font_x(sti) (PTR_STI(sti-&gt;font)-&gt;width)
DECL|macro|sti_font_y
mdefine_line|#define sti_font_y(sti) (PTR_STI(sti-&gt;font)-&gt;height)
macro_line|#ifndef offsetof
DECL|macro|offsetof
mdefine_line|#define offsetof(TYPE, MEMBER) ((unsigned long) &amp;((TYPE *)0)-&gt;MEMBER)
macro_line|#endif
r_extern
r_struct
id|sti_struct
op_star
id|sti_init_roms
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* XXX: this probably should not be here, but we rely on STI being&n;   initialized early and independently of stifb at the moment, so&n;   there&squot;s no other way for stifb to find it. */
r_extern
r_struct
id|sti_struct
op_star
id|default_sti
suffix:semicolon
r_int
id|sti_init_graph
c_func
(paren
r_struct
id|sti_struct
op_star
id|sti
)paren
suffix:semicolon
r_void
id|sti_inq_conf
c_func
(paren
r_struct
id|sti_struct
op_star
id|sti
)paren
suffix:semicolon
r_void
id|sti_putc
c_func
(paren
r_struct
id|sti_struct
op_star
id|sti
comma
r_int
id|c
comma
r_int
id|y
comma
r_int
id|x
)paren
suffix:semicolon
r_void
id|sti_set
c_func
(paren
r_struct
id|sti_struct
op_star
id|sti
comma
r_int
id|src_y
comma
r_int
id|src_x
comma
r_int
id|height
comma
r_int
id|width
comma
id|u8
id|color
)paren
suffix:semicolon
r_void
id|sti_clear
c_func
(paren
r_struct
id|sti_struct
op_star
id|sti
comma
r_int
id|src_y
comma
r_int
id|src_x
comma
r_int
id|height
comma
r_int
id|width
comma
r_int
id|c
)paren
suffix:semicolon
r_void
id|sti_bmove
c_func
(paren
r_struct
id|sti_struct
op_star
id|sti
comma
r_int
id|src_y
comma
r_int
id|src_x
comma
r_int
id|dst_y
comma
r_int
id|dst_x
comma
r_int
id|height
comma
r_int
id|width
)paren
suffix:semicolon
multiline_comment|/* STI function configuration structs */
DECL|union|region
r_typedef
r_union
id|region
(brace
r_struct
(brace
DECL|member|offset
id|u32
id|offset
suffix:colon
l_int|14
suffix:semicolon
multiline_comment|/* offset in 4kbyte page */
DECL|member|sys_only
id|u32
id|sys_only
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* don&squot;t map to user space */
DECL|member|cache
id|u32
id|cache
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* map to data cache */
DECL|member|btlb
id|u32
id|btlb
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* map to block tlb */
DECL|member|last
id|u32
id|last
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* last region in list */
DECL|member|length
id|u32
id|length
suffix:colon
l_int|14
suffix:semicolon
multiline_comment|/* length in 4kbyte page */
DECL|member|region_desc
)brace
id|region_desc
suffix:semicolon
DECL|member|region
id|u32
id|region
suffix:semicolon
multiline_comment|/* complete region value */
DECL|typedef|region_t
)brace
id|region_t
suffix:semicolon
DECL|macro|REGION_OFFSET_TO_PHYS
mdefine_line|#define REGION_OFFSET_TO_PHYS( rt, hpa ) &bslash;&n;&t;(((rt).region_desc.offset &lt;&lt; 12) + (hpa))
DECL|struct|sti_glob_cfg_ext
r_struct
id|sti_glob_cfg_ext
(brace
DECL|member|curr_mon
id|u8
id|curr_mon
suffix:semicolon
multiline_comment|/* current monitor configured */
DECL|member|friendly_boot
id|u8
id|friendly_boot
suffix:semicolon
multiline_comment|/* in friendly boot mode */
DECL|member|power
id|s16
id|power
suffix:semicolon
multiline_comment|/* power calculation (in Watts) */
DECL|member|freq_ref
id|s32
id|freq_ref
suffix:semicolon
multiline_comment|/* frequency refrence */
DECL|member|sti_mem_addr
id|u32
id|sti_mem_addr
suffix:semicolon
multiline_comment|/* pointer to global sti memory (size=sti_mem_request) */
DECL|member|future_ptr
id|u32
id|future_ptr
suffix:semicolon
multiline_comment|/* pointer to future data */
)brace
suffix:semicolon
DECL|struct|sti_glob_cfg
r_struct
id|sti_glob_cfg
(brace
DECL|member|text_planes
id|s32
id|text_planes
suffix:semicolon
multiline_comment|/* number of planes used for text */
DECL|member|onscreen_x
id|s16
id|onscreen_x
suffix:semicolon
multiline_comment|/* screen width in pixels */
DECL|member|onscreen_y
id|s16
id|onscreen_y
suffix:semicolon
multiline_comment|/* screen height in pixels */
DECL|member|offscreen_x
id|s16
id|offscreen_x
suffix:semicolon
multiline_comment|/* offset width in pixels */
DECL|member|offscreen_y
id|s16
id|offscreen_y
suffix:semicolon
multiline_comment|/* offset height in pixels */
DECL|member|total_x
id|s16
id|total_x
suffix:semicolon
multiline_comment|/* frame buffer width in pixels */
DECL|member|total_y
id|s16
id|total_y
suffix:semicolon
multiline_comment|/* frame buffer height in pixels */
DECL|member|region_ptrs
id|u32
id|region_ptrs
(braket
id|STI_REGION_MAX
)braket
suffix:semicolon
multiline_comment|/* region pointers */
DECL|member|reent_lvl
id|s32
id|reent_lvl
suffix:semicolon
multiline_comment|/* storage for reentry level value */
DECL|member|save_addr
id|u32
id|save_addr
suffix:semicolon
multiline_comment|/* where to save or restore reentrant state */
DECL|member|ext_ptr
id|u32
id|ext_ptr
suffix:semicolon
multiline_comment|/* pointer to extended glob_cfg data structure */
)brace
suffix:semicolon
multiline_comment|/* STI init function structs */
DECL|struct|sti_init_flags
r_struct
id|sti_init_flags
(brace
DECL|member|wait
id|u32
id|wait
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* should routine idle wait or not */
DECL|member|reset
id|u32
id|reset
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* hard reset the device? */
DECL|member|text
id|u32
id|text
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* turn on text display planes? */
DECL|member|nontext
id|u32
id|nontext
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* turn on non-text display planes? */
DECL|member|clear
id|u32
id|clear
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* clear text display planes? */
DECL|member|cmap_blk
id|u32
id|cmap_blk
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* non-text planes cmap black? */
DECL|member|enable_be_timer
id|u32
id|enable_be_timer
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* enable bus error timer */
DECL|member|enable_be_int
id|u32
id|enable_be_int
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* enable bus error timer interrupt */
DECL|member|no_chg_tx
id|u32
id|no_chg_tx
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* don&squot;t change text settings */
DECL|member|no_chg_ntx
id|u32
id|no_chg_ntx
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* don&squot;t change non-text settings */
DECL|member|no_chg_bet
id|u32
id|no_chg_bet
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* don&squot;t change berr timer settings */
DECL|member|no_chg_bei
id|u32
id|no_chg_bei
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* don&squot;t change berr int settings */
DECL|member|init_cmap_tx
id|u32
id|init_cmap_tx
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* initialize cmap for text planes */
DECL|member|cmt_chg
id|u32
id|cmt_chg
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* change current monitor type */
DECL|member|retain_ie
id|u32
id|retain_ie
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* don&squot;t allow reset to clear int enables */
DECL|member|caller_bootrom
id|u32
id|caller_bootrom
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set only by bootrom for each call */
DECL|member|caller_kernel
id|u32
id|caller_kernel
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set only by kernel for each call */
DECL|member|caller_other
id|u32
id|caller_other
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set only by non-[BR/K] caller */
DECL|member|pad
id|u32
id|pad
suffix:colon
l_int|14
suffix:semicolon
multiline_comment|/* pad to word boundary */
DECL|member|future_ptr
id|u32
id|future_ptr
suffix:semicolon
multiline_comment|/* pointer to future data */
)brace
suffix:semicolon
DECL|struct|sti_init_inptr_ext
r_struct
id|sti_init_inptr_ext
(brace
DECL|member|config_mon_type
id|u8
id|config_mon_type
suffix:semicolon
multiline_comment|/* configure to monitor type */
DECL|member|pad
id|u8
id|pad
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* pad to word boundary */
DECL|member|inflight_data
id|u16
id|inflight_data
suffix:semicolon
multiline_comment|/* inflight data possible on PCI */
DECL|member|future_ptr
id|u32
id|future_ptr
suffix:semicolon
multiline_comment|/* pointer to future data */
)brace
suffix:semicolon
DECL|struct|sti_init_inptr
r_struct
id|sti_init_inptr
(brace
DECL|member|text_planes
id|s32
id|text_planes
suffix:semicolon
multiline_comment|/* number of planes to use for text */
DECL|member|ext_ptr
id|u32
id|ext_ptr
suffix:semicolon
multiline_comment|/* pointer to extended init_graph inptr data structure*/
)brace
suffix:semicolon
DECL|struct|sti_init_outptr
r_struct
id|sti_init_outptr
(brace
DECL|member|errno
id|s32
id|errno
suffix:semicolon
multiline_comment|/* error number on failure */
DECL|member|text_planes
id|s32
id|text_planes
suffix:semicolon
multiline_comment|/* number of planes used for text */
DECL|member|future_ptr
id|u32
id|future_ptr
suffix:semicolon
multiline_comment|/* pointer to future data */
)brace
suffix:semicolon
multiline_comment|/* STI configuration function structs */
DECL|struct|sti_conf_flags
r_struct
id|sti_conf_flags
(brace
DECL|member|wait
id|u32
id|wait
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* should routine idle wait or not */
DECL|member|pad
id|u32
id|pad
suffix:colon
l_int|31
suffix:semicolon
multiline_comment|/* pad to word boundary */
DECL|member|future_ptr
id|u32
id|future_ptr
suffix:semicolon
multiline_comment|/* pointer to future data */
)brace
suffix:semicolon
DECL|struct|sti_conf_inptr
r_struct
id|sti_conf_inptr
(brace
DECL|member|future_ptr
id|u32
id|future_ptr
suffix:semicolon
multiline_comment|/* pointer to future data */
)brace
suffix:semicolon
DECL|struct|sti_conf_outptr_ext
r_struct
id|sti_conf_outptr_ext
(brace
DECL|member|crt_config
id|u32
id|crt_config
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* hardware specific X11/OGL information */
DECL|member|crt_hdw
id|u32
id|crt_hdw
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|future_ptr
id|u32
id|future_ptr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sti_conf_outptr
r_struct
id|sti_conf_outptr
(brace
DECL|member|errno
id|s32
id|errno
suffix:semicolon
multiline_comment|/* error number on failure */
DECL|member|onscreen_x
id|s16
id|onscreen_x
suffix:semicolon
multiline_comment|/* screen width in pixels */
DECL|member|onscreen_y
id|s16
id|onscreen_y
suffix:semicolon
multiline_comment|/* screen height in pixels */
DECL|member|offscreen_x
id|s16
id|offscreen_x
suffix:semicolon
multiline_comment|/* offscreen width in pixels */
DECL|member|offscreen_y
id|s16
id|offscreen_y
suffix:semicolon
multiline_comment|/* offscreen height in pixels */
DECL|member|total_x
id|s16
id|total_x
suffix:semicolon
multiline_comment|/* frame buffer width in pixels */
DECL|member|total_y
id|s16
id|total_y
suffix:semicolon
multiline_comment|/* frame buffer height in pixels */
DECL|member|bits_per_pixel
id|s32
id|bits_per_pixel
suffix:semicolon
multiline_comment|/* bits/pixel device has configured */
DECL|member|bits_used
id|s32
id|bits_used
suffix:semicolon
multiline_comment|/* bits which can be accessed */
DECL|member|planes
id|s32
id|planes
suffix:semicolon
multiline_comment|/* number of fb planes in system */
DECL|member|dev_name
id|u8
id|dev_name
(braket
id|STI_DEV_NAME_LENGTH
)braket
suffix:semicolon
multiline_comment|/* null terminated product name */
DECL|member|attributes
id|u32
id|attributes
suffix:semicolon
multiline_comment|/* flags denoting attributes */
DECL|member|ext_ptr
id|u32
id|ext_ptr
suffix:semicolon
multiline_comment|/* pointer to future data */
)brace
suffix:semicolon
DECL|struct|sti_rom
r_struct
id|sti_rom
(brace
DECL|member|type
id|u8
id|type
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|res004
id|u8
id|res004
suffix:semicolon
DECL|member|num_mons
id|u8
id|num_mons
suffix:semicolon
DECL|member|revno
id|u8
id|revno
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|graphics_id
id|u32
id|graphics_id
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|font_start
id|u32
id|font_start
suffix:semicolon
DECL|member|statesize
id|u32
id|statesize
suffix:semicolon
DECL|member|last_addr
id|u32
id|last_addr
suffix:semicolon
DECL|member|region_list
id|u32
id|region_list
suffix:semicolon
DECL|member|reentsize
id|u16
id|reentsize
suffix:semicolon
DECL|member|maxtime
id|u16
id|maxtime
suffix:semicolon
DECL|member|mon_tbl_addr
id|u32
id|mon_tbl_addr
suffix:semicolon
DECL|member|user_data_addr
id|u32
id|user_data_addr
suffix:semicolon
DECL|member|sti_mem_req
id|u32
id|sti_mem_req
suffix:semicolon
DECL|member|user_data_size
id|u32
id|user_data_size
suffix:semicolon
DECL|member|power
id|u16
id|power
suffix:semicolon
DECL|member|bus_support
id|u8
id|bus_support
suffix:semicolon
DECL|member|ext_bus_support
id|u8
id|ext_bus_support
suffix:semicolon
DECL|member|alt_code_type
id|u8
id|alt_code_type
suffix:semicolon
DECL|member|ext_dd_struct
id|u8
id|ext_dd_struct
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cfb_addr
id|u32
id|cfb_addr
suffix:semicolon
DECL|member|init_graph
id|u32
id|init_graph
suffix:semicolon
DECL|member|state_mgmt
id|u32
id|state_mgmt
suffix:semicolon
DECL|member|font_unpmv
id|u32
id|font_unpmv
suffix:semicolon
DECL|member|block_move
id|u32
id|block_move
suffix:semicolon
DECL|member|self_test
id|u32
id|self_test
suffix:semicolon
DECL|member|excep_hdlr
id|u32
id|excep_hdlr
suffix:semicolon
DECL|member|inq_conf
id|u32
id|inq_conf
suffix:semicolon
DECL|member|set_cm_entry
id|u32
id|set_cm_entry
suffix:semicolon
DECL|member|dma_ctrl
id|u32
id|dma_ctrl
suffix:semicolon
DECL|member|res040
id|u8
id|res040
(braket
l_int|7
op_star
l_int|4
)braket
suffix:semicolon
DECL|member|init_graph_addr
id|u32
id|init_graph_addr
suffix:semicolon
DECL|member|state_mgmt_addr
id|u32
id|state_mgmt_addr
suffix:semicolon
DECL|member|font_unp_addr
id|u32
id|font_unp_addr
suffix:semicolon
DECL|member|block_move_addr
id|u32
id|block_move_addr
suffix:semicolon
DECL|member|self_test_addr
id|u32
id|self_test_addr
suffix:semicolon
DECL|member|excep_hdlr_addr
id|u32
id|excep_hdlr_addr
suffix:semicolon
DECL|member|inq_conf_addr
id|u32
id|inq_conf_addr
suffix:semicolon
DECL|member|set_cm_entry_addr
id|u32
id|set_cm_entry_addr
suffix:semicolon
DECL|member|image_unpack_addr
id|u32
id|image_unpack_addr
suffix:semicolon
DECL|member|pa_risx_addrs
id|u32
id|pa_risx_addrs
(braket
l_int|7
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sti_rom_font
r_struct
id|sti_rom_font
(brace
DECL|member|first_char
id|u16
id|first_char
suffix:semicolon
DECL|member|last_char
id|u16
id|last_char
suffix:semicolon
DECL|member|width
id|u8
id|width
suffix:semicolon
DECL|member|height
id|u8
id|height
suffix:semicolon
DECL|member|font_type
id|u8
id|font_type
suffix:semicolon
multiline_comment|/* language type */
DECL|member|bytes_per_char
id|u8
id|bytes_per_char
suffix:semicolon
DECL|member|next_font
id|u32
id|next_font
suffix:semicolon
DECL|member|underline_height
id|u8
id|underline_height
suffix:semicolon
DECL|member|underline_pos
id|u8
id|underline_pos
suffix:semicolon
DECL|member|res008
id|u8
id|res008
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* sticore internal font handling */
DECL|struct|sti_cooked_font
r_struct
id|sti_cooked_font
(brace
DECL|member|raw
r_struct
id|sti_rom_font
op_star
id|raw
suffix:semicolon
DECL|member|next_font
r_struct
id|sti_cooked_font
op_star
id|next_font
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sti_cooked_rom
r_struct
id|sti_cooked_rom
(brace
DECL|member|raw
r_struct
id|sti_rom
op_star
id|raw
suffix:semicolon
DECL|member|font_start
r_struct
id|sti_cooked_font
op_star
id|font_start
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* STI font printing function structs */
DECL|struct|sti_font_inptr
r_struct
id|sti_font_inptr
(brace
DECL|member|font_start_addr
id|u32
id|font_start_addr
suffix:semicolon
multiline_comment|/* address of font start */
DECL|member|index
id|s16
id|index
suffix:semicolon
multiline_comment|/* index into font table of character */
DECL|member|fg_color
id|u8
id|fg_color
suffix:semicolon
multiline_comment|/* foreground color of character */
DECL|member|bg_color
id|u8
id|bg_color
suffix:semicolon
multiline_comment|/* background color of character */
DECL|member|dest_x
id|s16
id|dest_x
suffix:semicolon
multiline_comment|/* X location of character upper left */
DECL|member|dest_y
id|s16
id|dest_y
suffix:semicolon
multiline_comment|/* Y location of character upper left */
DECL|member|future_ptr
id|u32
id|future_ptr
suffix:semicolon
multiline_comment|/* pointer to future data */
)brace
suffix:semicolon
DECL|struct|sti_font_flags
r_struct
id|sti_font_flags
(brace
DECL|member|wait
id|u32
id|wait
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* should routine idle wait or not */
DECL|member|non_text
id|u32
id|non_text
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* font unpack/move in non_text planes =1, text =0 */
DECL|member|pad
id|u32
id|pad
suffix:colon
l_int|30
suffix:semicolon
multiline_comment|/* pad to word boundary */
DECL|member|future_ptr
id|u32
id|future_ptr
suffix:semicolon
multiline_comment|/* pointer to future data */
)brace
suffix:semicolon
DECL|struct|sti_font_outptr
r_struct
id|sti_font_outptr
(brace
DECL|member|errno
id|s32
id|errno
suffix:semicolon
multiline_comment|/* error number on failure */
DECL|member|future_ptr
id|u32
id|future_ptr
suffix:semicolon
multiline_comment|/* pointer to future data */
)brace
suffix:semicolon
multiline_comment|/* STI blockmove structs */
DECL|struct|sti_blkmv_flags
r_struct
id|sti_blkmv_flags
(brace
DECL|member|wait
id|u32
id|wait
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* should routine idle wait or not */
DECL|member|color
id|u32
id|color
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* change color during move? */
DECL|member|clear
id|u32
id|clear
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* clear during move? */
DECL|member|non_text
id|u32
id|non_text
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* block move in non_text planes =1, text =0 */
DECL|member|pad
id|u32
id|pad
suffix:colon
l_int|28
suffix:semicolon
multiline_comment|/* pad to word boundary */
DECL|member|future_ptr
id|u32
id|future_ptr
suffix:semicolon
multiline_comment|/* pointer to future data */
)brace
suffix:semicolon
DECL|struct|sti_blkmv_inptr
r_struct
id|sti_blkmv_inptr
(brace
DECL|member|fg_color
id|u8
id|fg_color
suffix:semicolon
multiline_comment|/* foreground color after move */
DECL|member|bg_color
id|u8
id|bg_color
suffix:semicolon
multiline_comment|/* background color after move */
DECL|member|src_x
id|s16
id|src_x
suffix:semicolon
multiline_comment|/* source upper left pixel x location */
DECL|member|src_y
id|s16
id|src_y
suffix:semicolon
multiline_comment|/* source upper left pixel y location */
DECL|member|dest_x
id|s16
id|dest_x
suffix:semicolon
multiline_comment|/* dest upper left pixel x location */
DECL|member|dest_y
id|s16
id|dest_y
suffix:semicolon
multiline_comment|/* dest upper left pixel y location */
DECL|member|width
id|s16
id|width
suffix:semicolon
multiline_comment|/* block width in pixels */
DECL|member|height
id|s16
id|height
suffix:semicolon
multiline_comment|/* block height in pixels */
DECL|member|future_ptr
id|u32
id|future_ptr
suffix:semicolon
multiline_comment|/* pointer to future data */
)brace
suffix:semicolon
DECL|struct|sti_blkmv_outptr
r_struct
id|sti_blkmv_outptr
(brace
DECL|member|errno
id|s32
id|errno
suffix:semicolon
multiline_comment|/* error number on failure */
DECL|member|future_ptr
id|u32
id|future_ptr
suffix:semicolon
multiline_comment|/* pointer to future data */
)brace
suffix:semicolon
multiline_comment|/* internal generic STI struct */
DECL|struct|sti_struct
r_struct
id|sti_struct
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* the following fields needs to be filled in by the word/byte routines */
DECL|member|font_width
r_int
id|font_width
suffix:semicolon
DECL|member|font_height
r_int
id|font_height
suffix:semicolon
multiline_comment|/* char **mon_strings; */
DECL|member|sti_mem_request
r_int
id|sti_mem_request
suffix:semicolon
DECL|member|graphics_id
id|u32
id|graphics_id
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|rom
r_struct
id|sti_cooked_rom
op_star
id|rom
suffix:semicolon
DECL|member|font_unpmv
r_int
r_int
id|font_unpmv
suffix:semicolon
DECL|member|block_move
r_int
r_int
id|block_move
suffix:semicolon
DECL|member|init_graph
r_int
r_int
id|init_graph
suffix:semicolon
DECL|member|inq_conf
r_int
r_int
id|inq_conf
suffix:semicolon
multiline_comment|/* all following fields are initialized by the generic routines */
DECL|member|text_planes
r_int
id|text_planes
suffix:semicolon
DECL|member|regions
id|region_t
id|regions
(braket
id|STI_REGION_MAX
)braket
suffix:semicolon
DECL|member|regions_phys
r_int
r_int
id|regions_phys
(braket
id|STI_REGION_MAX
)braket
suffix:semicolon
DECL|member|glob_cfg
r_struct
id|sti_glob_cfg
op_star
id|glob_cfg
suffix:semicolon
DECL|member|font
r_struct
id|sti_cooked_font
op_star
id|font
suffix:semicolon
multiline_comment|/* ptr to selected font (cooked) */
DECL|member|outptr
r_struct
id|sti_conf_outptr
id|outptr
suffix:semicolon
multiline_comment|/* configuration */
DECL|member|outptr_ext
r_struct
id|sti_conf_outptr_ext
id|outptr_ext
suffix:semicolon
multiline_comment|/* PCI data structures (pg. 17ff from sti.pdf) */
DECL|member|pd
r_struct
id|pci_dev
op_star
id|pd
suffix:semicolon
DECL|member|rm_entry
id|u8
id|rm_entry
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* pci region mapper array == pci config space offset */
multiline_comment|/* pointer to the fb_info where this STI device is used */
DECL|member|info
r_struct
id|fb_info
op_star
id|info
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* helper functions */
r_struct
id|sti_struct
op_star
id|sti_init_roms
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|sti_struct
op_star
id|sti_get_rom
c_func
(paren
r_int
)paren
suffix:semicolon
r_void
id|sti_rom_copy
c_func
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|count
comma
r_void
op_star
id|dest
)paren
suffix:semicolon
r_struct
id|sti_cooked_font
op_star
id|sti_select_font
c_func
(paren
r_struct
id|sti_cooked_rom
op_star
id|rom
comma
r_int
(paren
op_star
id|search_font_fnc
)paren
(paren
r_struct
id|sti_cooked_rom
op_star
comma
r_int
comma
r_int
)paren
)paren
suffix:semicolon
r_int
id|sti_read_rom
c_func
(paren
r_int
id|wordmode
comma
r_struct
id|sti_struct
op_star
id|sti
comma
r_int
r_int
id|address
)paren
suffix:semicolon
multiline_comment|/* FIXME: Do we have another solution for this ? */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
DECL|function|sti_flush
r_static
r_inline
r_void
id|sti_flush
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|len
)paren
(brace
id|flush_data_cache
c_func
(paren
)paren
suffix:semicolon
id|flush_kernel_dcache_range
c_func
(paren
id|from
comma
id|len
)paren
suffix:semicolon
id|flush_icache_range
c_func
(paren
id|from
comma
id|from
op_plus
id|len
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* STICORE_H */
eof
