macro_line|#ifndef __ASM_MACINTOSH_H
DECL|macro|__ASM_MACINTOSH_H
mdefine_line|#define __ASM_MACINTOSH_H
multiline_comment|/*&n; *&t;Apple Macintoshisms&n; */
r_extern
r_void
id|mac_reset
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mac_poweroff
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mac_init_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|mac_request_irq
(paren
r_int
r_int
comma
r_void
(paren
op_star
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
comma
r_const
r_char
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|mac_free_irq
c_func
(paren
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|mac_enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|mac_disable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|mac_irq_pending
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|mac_get_irq_list
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
macro_line|#if 0
r_extern
r_void
id|mac_default_handler
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|mac_identify
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mac_report_hardware
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mac_debugging_penguin
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|mac_boom
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Floppy driver magic hook - probably shouldnt be here&n; */
r_extern
r_void
id|via1_set_head
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|parse_booter
c_func
(paren
r_char
op_star
id|ptr
)paren
suffix:semicolon
r_extern
r_void
id|print_booter
c_func
(paren
r_char
op_star
id|ptr
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Macintosh Table&n; */
DECL|variable|macintosh_config
r_struct
id|mac_model
op_star
id|macintosh_config
suffix:semicolon
DECL|struct|mac_model
r_struct
id|mac_model
(brace
DECL|member|ident
r_int
id|ident
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|adb_type
r_char
id|adb_type
suffix:semicolon
DECL|member|via_type
r_char
id|via_type
suffix:semicolon
DECL|member|scsi_type
r_char
id|scsi_type
suffix:semicolon
DECL|member|ide_type
r_char
id|ide_type
suffix:semicolon
DECL|member|scc_type
r_char
id|scc_type
suffix:semicolon
DECL|member|ether_type
r_char
id|ether_type
suffix:semicolon
DECL|member|nubus_type
r_char
id|nubus_type
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MAC_ADB_NONE
mdefine_line|#define MAC_ADB_NONE&t;&t;0
DECL|macro|MAC_ADB_II
mdefine_line|#define MAC_ADB_II&t;&t;1
DECL|macro|MAC_ADB_IISI
mdefine_line|#define MAC_ADB_IISI&t;&t;2
DECL|macro|MAC_ADB_CUDA
mdefine_line|#define MAC_ADB_CUDA&t;&t;3
DECL|macro|MAC_ADB_PB1
mdefine_line|#define MAC_ADB_PB1&t;&t;4
DECL|macro|MAC_ADB_PB2
mdefine_line|#define MAC_ADB_PB2&t;&t;5
DECL|macro|MAC_ADB_IOP
mdefine_line|#define MAC_ADB_IOP&t;&t;6
DECL|macro|MAC_VIA_II
mdefine_line|#define MAC_VIA_II&t;&t;1
DECL|macro|MAC_VIA_IIci
mdefine_line|#define MAC_VIA_IIci&t;&t;2
DECL|macro|MAC_VIA_QUADRA
mdefine_line|#define MAC_VIA_QUADRA&t;&t;3
DECL|macro|MAC_SCSI_NONE
mdefine_line|#define MAC_SCSI_NONE&t;&t;0
DECL|macro|MAC_SCSI_OLD
mdefine_line|#define MAC_SCSI_OLD&t;&t;1
DECL|macro|MAC_SCSI_QUADRA
mdefine_line|#define MAC_SCSI_QUADRA&t;&t;2
DECL|macro|MAC_SCSI_QUADRA2
mdefine_line|#define MAC_SCSI_QUADRA2&t;3
DECL|macro|MAC_SCSI_QUADRA3
mdefine_line|#define MAC_SCSI_QUADRA3&t;4
DECL|macro|MAC_IDE_NONE
mdefine_line|#define MAC_IDE_NONE&t;&t;0
DECL|macro|MAC_IDE_QUADRA
mdefine_line|#define MAC_IDE_QUADRA&t;&t;1
DECL|macro|MAC_IDE_PB
mdefine_line|#define MAC_IDE_PB&t;&t;2
DECL|macro|MAC_IDE_BABOON
mdefine_line|#define MAC_IDE_BABOON&t;&t;3
DECL|macro|MAC_SCC_II
mdefine_line|#define MAC_SCC_II&t;&t;1
DECL|macro|MAC_SCC_QUADRA
mdefine_line|#define MAC_SCC_QUADRA&t;&t;2
DECL|macro|MAC_SCC_QUADRA2
mdefine_line|#define MAC_SCC_QUADRA2&t;&t;3
DECL|macro|MAC_SCC_IOP
mdefine_line|#define MAC_SCC_IOP&t;&t;4
DECL|macro|MAC_ETHER_NONE
mdefine_line|#define MAC_ETHER_NONE&t;&t;0&t;
DECL|macro|MAC_ETHER_SONIC
mdefine_line|#define MAC_ETHER_SONIC&t;&t;1
DECL|macro|MAC_ETHER_MACE
mdefine_line|#define MAC_ETHER_MACE&t;&t;2
DECL|macro|MAC_NO_NUBUS
mdefine_line|#define MAC_NO_NUBUS&t;&t;0
DECL|macro|MAC_NUBUS
mdefine_line|#define MAC_NUBUS&t;&t;1
multiline_comment|/*&n; *&t;Gestalt numbers&n; */
DECL|macro|MAC_MODEL_II
mdefine_line|#define MAC_MODEL_II&t;&t;6
DECL|macro|MAC_MODEL_IIX
mdefine_line|#define MAC_MODEL_IIX&t;&t;7
DECL|macro|MAC_MODEL_IICX
mdefine_line|#define MAC_MODEL_IICX&t;&t;8
DECL|macro|MAC_MODEL_SE30
mdefine_line|#define MAC_MODEL_SE30&t;&t;9
DECL|macro|MAC_MODEL_IICI
mdefine_line|#define MAC_MODEL_IICI&t;&t;11
DECL|macro|MAC_MODEL_IIFX
mdefine_line|#define MAC_MODEL_IIFX&t;&t;13&t;/* And well numbered it is too */
DECL|macro|MAC_MODEL_IISI
mdefine_line|#define MAC_MODEL_IISI&t;&t;18
DECL|macro|MAC_MODEL_LC
mdefine_line|#define MAC_MODEL_LC&t;&t;19
DECL|macro|MAC_MODEL_Q900
mdefine_line|#define MAC_MODEL_Q900&t;&t;20
DECL|macro|MAC_MODEL_PB170
mdefine_line|#define MAC_MODEL_PB170&t;&t;21
DECL|macro|MAC_MODEL_Q700
mdefine_line|#define MAC_MODEL_Q700&t;&t;22
DECL|macro|MAC_MODEL_CLII
mdefine_line|#define MAC_MODEL_CLII&t;&t;23&t;/* aka: P200 */
DECL|macro|MAC_MODEL_PB140
mdefine_line|#define MAC_MODEL_PB140&t;&t;25
DECL|macro|MAC_MODEL_Q950
mdefine_line|#define MAC_MODEL_Q950&t;&t;26&t;/* aka: WGS95 */
DECL|macro|MAC_MODEL_LCIII
mdefine_line|#define MAC_MODEL_LCIII&t;&t;27&t;/* aka: P450 */
DECL|macro|MAC_MODEL_PB210
mdefine_line|#define MAC_MODEL_PB210&t;&t;29
DECL|macro|MAC_MODEL_C650
mdefine_line|#define MAC_MODEL_C650&t;&t;30
DECL|macro|MAC_MODEL_PB230
mdefine_line|#define MAC_MODEL_PB230&t;&t;32
DECL|macro|MAC_MODEL_PB180
mdefine_line|#define MAC_MODEL_PB180&t;&t;33
DECL|macro|MAC_MODEL_PB160
mdefine_line|#define MAC_MODEL_PB160&t;&t;34
DECL|macro|MAC_MODEL_Q800
mdefine_line|#define MAC_MODEL_Q800&t;&t;35&t;/* aka: WGS80 */
DECL|macro|MAC_MODEL_Q650
mdefine_line|#define MAC_MODEL_Q650&t;&t;36 
DECL|macro|MAC_MODEL_LCII
mdefine_line|#define MAC_MODEL_LCII&t;&t;37&t;/* aka: P400/405/410/430 */
DECL|macro|MAC_MODEL_PB250
mdefine_line|#define MAC_MODEL_PB250&t;&t;38
DECL|macro|MAC_MODEL_IIVI
mdefine_line|#define MAC_MODEL_IIVI&t;&t;44
DECL|macro|MAC_MODEL_P600
mdefine_line|#define MAC_MODEL_P600&t;&t;45&t;/* aka: P600CD */
DECL|macro|MAC_MODEL_IIVX
mdefine_line|#define MAC_MODEL_IIVX&t;&t;48
DECL|macro|MAC_MODEL_CCL
mdefine_line|#define MAC_MODEL_CCL&t;&t;49&t;/* aka: P250 */
DECL|macro|MAC_MODEL_PB165C
mdefine_line|#define MAC_MODEL_PB165C&t;50
DECL|macro|MAC_MODEL_C610
mdefine_line|#define MAC_MODEL_C610&t;&t;52&t;/* aka: WGS60 */
DECL|macro|MAC_MODEL_Q610
mdefine_line|#define MAC_MODEL_Q610&t;&t;53
DECL|macro|MAC_MODEL_PB145
mdefine_line|#define MAC_MODEL_PB145&t;&t;54&t;/* aka: PB145B */
DECL|macro|MAC_MODEL_P520
mdefine_line|#define MAC_MODEL_P520&t;&t;56&t;/* aka: LC520 */
DECL|macro|MAC_MODEL_C660
mdefine_line|#define MAC_MODEL_C660&t;&t;60
DECL|macro|MAC_MODEL_P460
mdefine_line|#define MAC_MODEL_P460&t;&t;62&t;/* aka: LCIII+, P466/P467 */
DECL|macro|MAC_MODEL_PB180C
mdefine_line|#define MAC_MODEL_PB180C&t;71
DECL|macro|MAC_MODEL_PB520
mdefine_line|#define MAC_MODEL_PB520&t;&t;72&t;/* aka: PB520C, PB540, PB540C, PB550C */
DECL|macro|MAC_MODEL_PB270C
mdefine_line|#define MAC_MODEL_PB270C&t;77
DECL|macro|MAC_MODEL_Q840
mdefine_line|#define MAC_MODEL_Q840&t;&t;78
DECL|macro|MAC_MODEL_P550
mdefine_line|#define MAC_MODEL_P550&t;&t;80&t;/* aka: LC550, P560 */
DECL|macro|MAC_MODEL_CCLII
mdefine_line|#define MAC_MODEL_CCLII&t;&t;83&t;/* aka: P275 */
DECL|macro|MAC_MODEL_PB165
mdefine_line|#define MAC_MODEL_PB165&t;&t;84
DECL|macro|MAC_MODEL_PB190
mdefine_line|#define MAC_MODEL_PB190&t;&t;85&t;/* aka: PB190CS */
DECL|macro|MAC_MODEL_TV
mdefine_line|#define MAC_MODEL_TV&t;&t;88
DECL|macro|MAC_MODEL_P475
mdefine_line|#define MAC_MODEL_P475&t;&t;89&t;/* aka: LC475, P476 */
DECL|macro|MAC_MODEL_P475F
mdefine_line|#define MAC_MODEL_P475F&t;&t;90&t;/* aka: P475 w/ FPU (no LC040) */
DECL|macro|MAC_MODEL_P575
mdefine_line|#define MAC_MODEL_P575&t;&t;92&t;/* aka: LC575, P577/P578 */
DECL|macro|MAC_MODEL_Q605
mdefine_line|#define MAC_MODEL_Q605&t;&t;94
DECL|macro|MAC_MODEL_Q630
mdefine_line|#define MAC_MODEL_Q630&t;&t;98&t;/* aka: LC630, P630/631/635/636/637/638/640 */
DECL|macro|MAC_MODEL_P588
mdefine_line|#define MAC_MODEL_P588&t;&t;99&t;/* aka: LC580, P580 */
DECL|macro|MAC_MODEL_PB280
mdefine_line|#define MAC_MODEL_PB280&t;&t;102
DECL|macro|MAC_MODEL_PB280C
mdefine_line|#define MAC_MODEL_PB280C&t;103
DECL|macro|MAC_MODEL_PB150
mdefine_line|#define MAC_MODEL_PB150&t;&t;115
r_extern
r_struct
id|mac_model
op_star
id|macintosh_config
suffix:semicolon
macro_line|#endif
eof
