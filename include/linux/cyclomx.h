multiline_comment|/*&n;* cyclomx.h&t;Cyclom 2X WAN Link Driver.&n;*&t;&t;User-level API definitions.&n;*&n;* Author:&t;Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n;*&n;* Copyright:&t;(c) 1998-2000 Arnaldo Carvalho de Melo&n;*&n;* Based on wanpipe.h by Gene Kozin &lt;genek@compuserve.com&gt;&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* 2000/07/13    acme&t;&t;remove crap #if KERNEL_VERSION &gt; blah&n;* 2000/01/21    acme            rename cyclomx_open to cyclomx_mod_inc_use_count&n;*                               and cyclomx_close to cyclomx_mod_dec_use_count&n;* 1999/05/19&t;acme&t;&t;wait_queue_head_t wait_stats(support for 2.3.*)&n;* 1999/01/03&t;acme&t;&t;judicious use of data types&n;* 1998/12/27&t;acme&t;&t;cleanup: PACKED not needed&n;* 1998/08/08&t;acme&t;&t;Version 0.0.1&n;*/
macro_line|#ifndef&t;_CYCLOMX_H
DECL|macro|_CYCLOMX_H
mdefine_line|#define&t;_CYCLOMX_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/wanrouter.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#ifdef&t;__KERNEL__
multiline_comment|/* Kernel Interface */
macro_line|#include &lt;linux/cycx_drv.h&gt;&t;/* Cyclom 2X support module API definitions */
macro_line|#include &lt;linux/cycx_cfm.h&gt;&t;/* Cyclom 2X firmware module definitions */
macro_line|#ifdef CONFIG_CYCLOMX_X25
macro_line|#include &lt;linux/cycx_x25.h&gt;
macro_line|#endif
macro_line|#ifndef&t;min
DECL|macro|min
mdefine_line|#define min(a,b) (((a)&lt;(b))?(a):(b))
macro_line|#endif
macro_line|#ifndef&t;max
DECL|macro|max
mdefine_line|#define max(a,b) (((a)&gt;(b))?(a):(b))
macro_line|#endif
DECL|macro|is_digit
mdefine_line|#define&t;is_digit(ch) (((ch)&gt;=(unsigned)&squot;0&squot;&amp;&amp;(ch)&lt;=(unsigned)&squot;9&squot;)?1:0)
multiline_comment|/* Adapter Data Space.&n; * This structure is needed because we handle multiple cards, otherwise&n; * static data would do it.&n; */
DECL|struct|cycx
r_typedef
r_struct
id|cycx
(brace
DECL|member|devname
r_char
id|devname
(braket
id|WAN_DRVNAME_SZ
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* card name */
DECL|member|hw
id|cycxhw_t
id|hw
suffix:semicolon
multiline_comment|/* hardware configuration */
DECL|member|wandev
id|wan_device_t
id|wandev
suffix:semicolon
multiline_comment|/* WAN device data space */
DECL|member|open_cnt
id|u32
id|open_cnt
suffix:semicolon
multiline_comment|/* number of open interfaces */
DECL|member|state_tick
id|u32
id|state_tick
suffix:semicolon
multiline_comment|/* link state timestamp */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|in_isr
r_char
id|in_isr
suffix:semicolon
multiline_comment|/* interrupt-in-service flag */
DECL|member|buff_int_mode_unbusy
r_char
id|buff_int_mode_unbusy
suffix:semicolon
multiline_comment|/* flag for carrying out dev_tint */
DECL|member|wait_stats
id|wait_queue_head_t
id|wait_stats
suffix:semicolon
multiline_comment|/* to wait for the STATS indication */
DECL|member|mbox
id|u32
id|mbox
suffix:semicolon
multiline_comment|/* -&gt; mailbox */
DECL|member|isr
r_void
(paren
op_star
id|isr
)paren
(paren
r_struct
id|cycx
op_star
id|card
)paren
suffix:semicolon
multiline_comment|/* interrupt service routine */
DECL|member|exec
r_int
(paren
op_star
id|exec
)paren
(paren
r_struct
id|cycx
op_star
id|card
comma
r_void
op_star
id|u_cmd
comma
r_void
op_star
id|u_data
)paren
suffix:semicolon
r_union
(brace
macro_line|#ifdef CONFIG_CYCLOMX_X25
r_struct
(brace
multiline_comment|/* X.25 specific data */
DECL|member|lo_pvc
id|u32
id|lo_pvc
suffix:semicolon
DECL|member|hi_pvc
id|u32
id|hi_pvc
suffix:semicolon
DECL|member|lo_svc
id|u32
id|lo_svc
suffix:semicolon
DECL|member|hi_svc
id|u32
id|hi_svc
suffix:semicolon
DECL|member|stats
id|TX25Stats
id|stats
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|connection_keys
id|u32
id|connection_keys
suffix:semicolon
DECL|member|x
)brace
id|x
suffix:semicolon
macro_line|#endif
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|typedef|cycx_t
)brace
id|cycx_t
suffix:semicolon
multiline_comment|/* Public Functions */
r_void
id|cyclomx_mod_inc_use_count
(paren
id|cycx_t
op_star
id|card
)paren
suffix:semicolon
multiline_comment|/* cycx_main.c */
r_void
id|cyclomx_mod_dec_use_count
(paren
id|cycx_t
op_star
id|card
)paren
suffix:semicolon
multiline_comment|/* cycx_main.c */
r_void
id|cyclomx_set_state
(paren
id|cycx_t
op_star
id|card
comma
r_int
id|state
)paren
suffix:semicolon
multiline_comment|/* cycx_main.c */
macro_line|#ifdef CONFIG_CYCLOMX_X25
r_int
id|cyx_init
(paren
id|cycx_t
op_star
id|card
comma
id|wandev_conf_t
op_star
id|conf
)paren
suffix:semicolon
multiline_comment|/* cycx_x25.c */
macro_line|#endif
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _CYCLOMX_H */
eof
