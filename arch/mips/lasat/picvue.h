multiline_comment|/* &n; * Picvue PVC160206 display driver&n; *&n; * Brian Murphy &lt;brian.murphy@eicon.com&gt; &n; *&n; */
macro_line|#include &lt;asm/semaphore.h&gt;
DECL|struct|pvc_defs
r_struct
id|pvc_defs
(brace
DECL|member|reg
r_volatile
id|u32
op_star
id|reg
suffix:semicolon
DECL|member|data_shift
id|u32
id|data_shift
suffix:semicolon
DECL|member|data_mask
id|u32
id|data_mask
suffix:semicolon
DECL|member|e
id|u32
id|e
suffix:semicolon
DECL|member|rw
id|u32
id|rw
suffix:semicolon
DECL|member|rs
id|u32
id|rs
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|pvc_defs
op_star
id|picvue
suffix:semicolon
DECL|macro|PVC_NLINES
mdefine_line|#define PVC_NLINES&t;&t;2
DECL|macro|PVC_DISPMEM
mdefine_line|#define PVC_DISPMEM&t;&t;80
DECL|macro|PVC_LINELEN
mdefine_line|#define PVC_LINELEN&t;&t;PVC_DISPMEM / PVC_NLINES
DECL|macro|PVC_VISIBLE_CHARS
mdefine_line|#define PVC_VISIBLE_CHARS&t;16
r_void
id|pvc_write_string
c_func
(paren
r_const
r_int
r_char
op_star
id|str
comma
id|u8
id|addr
comma
r_int
id|line
)paren
suffix:semicolon
r_void
id|pvc_write_string_centered
c_func
(paren
r_const
r_int
r_char
op_star
id|str
comma
r_int
id|line
)paren
suffix:semicolon
r_void
id|pvc_dump_string
c_func
(paren
r_const
r_int
r_char
op_star
id|str
)paren
suffix:semicolon
DECL|macro|BM_SIZE
mdefine_line|#define BM_SIZE&t;&t;&t;8
DECL|macro|MAX_PROGRAMMABLE_CHARS
mdefine_line|#define MAX_PROGRAMMABLE_CHARS&t;8
r_int
id|pvc_program_cg
c_func
(paren
r_int
id|charnum
comma
id|u8
id|bitmap
(braket
id|BM_SIZE
)braket
)paren
suffix:semicolon
r_void
id|pvc_dispcnt
c_func
(paren
id|u8
id|cmd
)paren
suffix:semicolon
DECL|macro|DISP_OFF
mdefine_line|#define  DISP_OFF&t;0
DECL|macro|DISP_ON
mdefine_line|#define  DISP_ON&t;(1 &lt;&lt; 2)
DECL|macro|CUR_ON
mdefine_line|#define  CUR_ON&t;&t;(1 &lt;&lt; 1)
DECL|macro|CUR_BLINK
mdefine_line|#define  CUR_BLINK&t;(1 &lt;&lt; 0)
r_void
id|pvc_move
c_func
(paren
id|u8
id|cmd
)paren
suffix:semicolon
DECL|macro|DISPLAY
mdefine_line|#define  DISPLAY&t;(1 &lt;&lt; 3)
DECL|macro|CURSOR
mdefine_line|#define  CURSOR&t;&t;0
DECL|macro|RIGHT
mdefine_line|#define  RIGHT&t;&t;(1 &lt;&lt; 2)
DECL|macro|LEFT
mdefine_line|#define  LEFT&t;&t;0
r_void
id|pvc_clear
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|pvc_home
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|semaphore
id|pvc_sem
suffix:semicolon
eof
