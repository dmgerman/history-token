macro_line|#ifndef S390_CIO_H
DECL|macro|S390_CIO_H
mdefine_line|#define S390_CIO_H
multiline_comment|/*&n; * where we put the ssd info&n; */
DECL|struct|ssd_info
r_struct
id|ssd_info
(brace
DECL|member|valid
id|__u8
id|valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|type
id|__u8
id|type
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* subchannel type */
DECL|member|chpid
id|__u8
id|chpid
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* chpids */
DECL|member|fla
id|__u16
id|fla
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* full link addresses */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * path management control word&n; */
DECL|struct|pmcw
r_struct
id|pmcw
(brace
DECL|member|intparm
id|__u32
id|intparm
suffix:semicolon
multiline_comment|/* interruption parameter */
DECL|member|qf
id|__u32
id|qf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* qdio facility */
DECL|member|res0
id|__u32
id|res0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved zeros */
DECL|member|isc
id|__u32
id|isc
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* interruption sublass */
DECL|member|res5
id|__u32
id|res5
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* reserved zeros */
DECL|member|ena
id|__u32
id|ena
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* enabled */
DECL|member|lm
id|__u32
id|lm
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* limit mode */
DECL|member|mme
id|__u32
id|mme
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* measurement-mode enable */
DECL|member|mp
id|__u32
id|mp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* multipath mode */
DECL|member|tf
id|__u32
id|tf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* timing facility */
DECL|member|dnv
id|__u32
id|dnv
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* device number valid */
DECL|member|dev
id|__u32
id|dev
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* device number */
DECL|member|lpm
id|__u8
id|lpm
suffix:semicolon
multiline_comment|/* logical path mask */
DECL|member|pnom
id|__u8
id|pnom
suffix:semicolon
multiline_comment|/* path not operational mask */
DECL|member|lpum
id|__u8
id|lpum
suffix:semicolon
multiline_comment|/* last path used mask */
DECL|member|pim
id|__u8
id|pim
suffix:semicolon
multiline_comment|/* path installed mask */
DECL|member|mbi
id|__u16
id|mbi
suffix:semicolon
multiline_comment|/* measurement-block index */
DECL|member|pom
id|__u8
id|pom
suffix:semicolon
multiline_comment|/* path operational mask */
DECL|member|pam
id|__u8
id|pam
suffix:semicolon
multiline_comment|/* path available mask */
DECL|member|chpid
id|__u8
id|chpid
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* CHPID 0-7 (if available) */
DECL|member|unused1
id|__u32
id|unused1
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* reserved zeros */
DECL|member|st
id|__u32
id|st
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* subchannel type */
DECL|member|unused2
id|__u32
id|unused2
suffix:colon
l_int|18
suffix:semicolon
multiline_comment|/* reserved zeros */
DECL|member|mbfc
id|__u32
id|mbfc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* measurement block format control */
DECL|member|xmwme
id|__u32
id|xmwme
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* extended measurement word mode enable */
DECL|member|csense
id|__u32
id|csense
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* concurrent sense; can be enabled ...*/
multiline_comment|/*  ... per MSCH, however, if facility */
multiline_comment|/*  ... is not installed, this results */
multiline_comment|/*  ... in an operand exception.       */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * subchannel information block&n; */
DECL|struct|schib
r_struct
id|schib
(brace
DECL|member|pmcw
r_struct
id|pmcw
id|pmcw
suffix:semicolon
multiline_comment|/* path management control word */
DECL|member|scsw
r_struct
id|scsw
id|scsw
suffix:semicolon
multiline_comment|/* subchannel status word */
DECL|member|mba
id|__u64
id|mba
suffix:semicolon
multiline_comment|/* measurement block address */
DECL|member|mda
id|__u8
id|mda
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* model dependent area */
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|4
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * operation request block&n; */
DECL|struct|orb
r_struct
id|orb
(brace
DECL|member|intparm
id|__u32
id|intparm
suffix:semicolon
multiline_comment|/* interruption parameter */
DECL|member|key
id|__u32
id|key
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* flags, like key, suspend control, etc. */
DECL|member|spnd
id|__u32
id|spnd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* suspend control */
DECL|member|res1
id|__u32
id|res1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|mod
id|__u32
id|mod
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* modification control */
DECL|member|sync
id|__u32
id|sync
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* synchronize control */
DECL|member|fmt
id|__u32
id|fmt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* format control */
DECL|member|pfch
id|__u32
id|pfch
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* prefetch control */
DECL|member|isic
id|__u32
id|isic
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* initial-status-interruption control */
DECL|member|alcc
id|__u32
id|alcc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* address-limit-checking control */
DECL|member|ssic
id|__u32
id|ssic
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* suppress-suspended-interr. control */
DECL|member|res2
id|__u32
id|res2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|c64
id|__u32
id|c64
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* IDAW/QDIO 64 bit control  */
DECL|member|i2k
id|__u32
id|i2k
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* IDAW 2/4kB block size control */
DECL|member|lpm
id|__u32
id|lpm
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* logical path mask */
DECL|member|ils
id|__u32
id|ils
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* incorrect length */
DECL|member|zero
id|__u32
id|zero
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* reserved zeros */
DECL|member|orbx
id|__u32
id|orbx
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ORB extension control */
DECL|member|cpa
id|__u32
id|cpa
suffix:semicolon
multiline_comment|/* channel program address */
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|4
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* subchannel data structure used by I/O subroutines */
DECL|struct|subchannel
r_struct
id|subchannel
(brace
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* aka. subchannel number */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* subchannel lock */
r_enum
(brace
DECL|enumerator|SUBCHANNEL_TYPE_IO
id|SUBCHANNEL_TYPE_IO
op_assign
l_int|0
comma
DECL|enumerator|SUBCHANNEL_TYPE_CHSC
id|SUBCHANNEL_TYPE_CHSC
op_assign
l_int|1
comma
DECL|enumerator|SUBCHANNEL_TYPE_MESSAGE
id|SUBCHANNEL_TYPE_MESSAGE
op_assign
l_int|2
comma
DECL|enumerator|SUBCHANNEL_TYPE_ADM
id|SUBCHANNEL_TYPE_ADM
op_assign
l_int|3
comma
DECL|member|st
)brace
id|st
suffix:semicolon
multiline_comment|/* subchannel type */
r_struct
(brace
DECL|member|suspend
r_int
r_int
id|suspend
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* allow suspend */
DECL|member|prefetch
r_int
r_int
id|prefetch
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* deny prefetch */
DECL|member|inter
r_int
r_int
id|inter
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* suppress intermediate interrupts */
DECL|member|options
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|options
suffix:semicolon
DECL|member|vpm
id|__u8
id|vpm
suffix:semicolon
multiline_comment|/* verified path mask */
DECL|member|lpm
id|__u8
id|lpm
suffix:semicolon
multiline_comment|/* logical path mask */
DECL|member|opm
id|__u8
id|opm
suffix:semicolon
multiline_comment|/* operational path mask */
DECL|member|schib
r_struct
id|schib
id|schib
suffix:semicolon
multiline_comment|/* subchannel information block */
DECL|member|orb
r_struct
id|orb
id|orb
suffix:semicolon
multiline_comment|/* operation request block */
DECL|member|sense_ccw
r_struct
id|ccw1
id|sense_ccw
suffix:semicolon
multiline_comment|/* static ccw for sense command */
DECL|member|ssd_info
r_struct
id|ssd_info
id|ssd_info
suffix:semicolon
multiline_comment|/* subchannel description */
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* entry in device tree */
DECL|member|driver
r_struct
id|css_driver
op_star
id|driver
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
DECL|macro|IO_INTERRUPT_TYPE
mdefine_line|#define IO_INTERRUPT_TYPE&t;   0 /* I/O interrupt type */
DECL|macro|to_subchannel
mdefine_line|#define to_subchannel(n) container_of(n, struct subchannel, dev)
r_extern
r_int
id|cio_validate_subchannel
(paren
r_struct
id|subchannel
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|cio_enable_subchannel
(paren
r_struct
id|subchannel
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|cio_disable_subchannel
(paren
r_struct
id|subchannel
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cio_cancel
(paren
r_struct
id|subchannel
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cio_clear
(paren
r_struct
id|subchannel
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cio_resume
(paren
r_struct
id|subchannel
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cio_halt
(paren
r_struct
id|subchannel
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cio_start
(paren
r_struct
id|subchannel
op_star
comma
r_struct
id|ccw1
op_star
comma
id|__u8
)paren
suffix:semicolon
r_extern
r_int
id|cio_start_key
(paren
r_struct
id|subchannel
op_star
comma
r_struct
id|ccw1
op_star
comma
id|__u8
comma
id|__u8
)paren
suffix:semicolon
r_extern
r_int
id|cio_cancel
(paren
r_struct
id|subchannel
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cio_set_options
(paren
r_struct
id|subchannel
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|cio_get_options
(paren
r_struct
id|subchannel
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cio_modify
(paren
r_struct
id|subchannel
op_star
)paren
suffix:semicolon
multiline_comment|/* Use with care. */
macro_line|#ifdef CONFIG_CCW_CONSOLE
r_extern
r_struct
id|subchannel
op_star
id|cio_probe_console
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cio_release_console
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|cio_is_console
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_struct
id|subchannel
op_star
id|cio_get_console_subchannel
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|macro|cio_is_console
mdefine_line|#define cio_is_console(irq) 0
DECL|macro|cio_get_console_subchannel
mdefine_line|#define cio_get_console_subchannel() NULL
macro_line|#endif
r_extern
r_int
id|cio_show_msg
suffix:semicolon
macro_line|#endif
eof
