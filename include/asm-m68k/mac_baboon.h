multiline_comment|/*&n; * Definitions for the &quot;Baboon&quot; custom IC on the PowerBook 190.&n; */
DECL|macro|BABOON_BASE
mdefine_line|#define BABOON_BASE (0x50F1A000)&t;/* same as IDE controller base */
macro_line|#ifndef __ASSEMBLY__
DECL|struct|baboon
r_struct
id|baboon
(brace
DECL|member|pad1
r_char
id|pad1
(braket
l_int|208
)braket
suffix:semicolon
multiline_comment|/* generic IDE registers, not used here */
DECL|member|mb_control
r_int
id|mb_control
suffix:semicolon
multiline_comment|/* Control register:&n;&t;&t;&t;&t; * bit 5 : slot 2 power control&n;&t;&t;&t;&t; * bit 6 : slot 1 power control&n;&t;&t;&t;&t; */
DECL|member|pad2
r_char
id|pad2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|mb_status
r_int
id|mb_status
suffix:semicolon
multiline_comment|/* (0xD4) media bay status register:&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; * bit 0: ????&n;&t;&t;&t;&t; * bit 1: IDE interrupt active?&n;&t;&t;&t;&t; * bit 2: bay status, 0 = full, 1 = empty&n;&t;&t;&t;&t; * bit 3: ????&n;&t;&t;&t;&t; */
DECL|member|pad3
r_char
id|pad3
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* (0xD6) not used */
DECL|member|mb_ifr
r_int
id|mb_ifr
suffix:semicolon
multiline_comment|/* (0xD8) media bay interrupt flags register:&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; * bit 0: ????&n;&t;&t;&t;&t; * bit 1: IDE controller interrupt&n;&t;&t;&t;&t; * bit 2: media bay status change interrupt&n;&t;&t;&t;&t; */
)brace
suffix:semicolon
r_extern
r_volatile
r_struct
id|baboon
op_star
id|baboon
suffix:semicolon
macro_line|#endif /* __ASSEMBLY **/
eof
