multiline_comment|/*&n; *&t;OSS&n; *&n; *&t;This is used in place of VIA2 on the IIfx.&n; */
DECL|macro|OSS_BASE
mdefine_line|#define OSS_BASE&t;(0x50f1a000)
multiline_comment|/*&n; * Interrupt level offsets for mac_oss-&gt;irq_level&n; */
DECL|macro|OSS_NUBUS0
mdefine_line|#define OSS_NUBUS0&t;0
DECL|macro|OSS_NUBUS1
mdefine_line|#define OSS_NUBUS1&t;1
DECL|macro|OSS_NUBUS2
mdefine_line|#define OSS_NUBUS2&t;2
DECL|macro|OSS_NUBUS3
mdefine_line|#define OSS_NUBUS3&t;3
DECL|macro|OSS_NUBUS4
mdefine_line|#define OSS_NUBUS4&t;4
DECL|macro|OSS_NUBUS5
mdefine_line|#define OSS_NUBUS5&t;5
DECL|macro|OSS_IOPISM
mdefine_line|#define OSS_IOPISM&t;6
DECL|macro|OSS_IOPSCC
mdefine_line|#define OSS_IOPSCC&t;7
DECL|macro|OSS_SOUND
mdefine_line|#define OSS_SOUND&t;8
DECL|macro|OSS_SCSI
mdefine_line|#define OSS_SCSI&t;9
DECL|macro|OSS_60HZ
mdefine_line|#define OSS_60HZ&t;10
DECL|macro|OSS_VIA1
mdefine_line|#define OSS_VIA1&t;11
DECL|macro|OSS_UNUSED1
mdefine_line|#define OSS_UNUSED1&t;12
DECL|macro|OSS_UNUSED2
mdefine_line|#define OSS_UNUSED2&t;13
DECL|macro|OSS_PARITY
mdefine_line|#define OSS_PARITY&t;14
DECL|macro|OSS_UNUSED3
mdefine_line|#define OSS_UNUSED3&t;15
DECL|macro|OSS_NUM_SOURCES
mdefine_line|#define OSS_NUM_SOURCES&t;16
multiline_comment|/*&n; * Pending interrupt bits in mac_oss-&gt;irq_pending&n; */
DECL|macro|OSS_IP_NUBUS0
mdefine_line|#define OSS_IP_NUBUS0&t;0x0001
DECL|macro|OSS_IP_NUBUS1
mdefine_line|#define OSS_IP_NUBUS1&t;0x0002
DECL|macro|OSS_IP_NUBUS2
mdefine_line|#define OSS_IP_NUBUS2&t;0x0004
DECL|macro|OSS_IP_NUBUS3
mdefine_line|#define OSS_IP_NUBUS3&t;0x0008
DECL|macro|OSS_IP_NUBUS4
mdefine_line|#define OSS_IP_NUBUS4&t;0x0010
DECL|macro|OSS_IP_NUBUS5
mdefine_line|#define OSS_IP_NUBUS5&t;0x0020
DECL|macro|OSS_IP_IOPISM
mdefine_line|#define OSS_IP_IOPISM&t;0x0040
DECL|macro|OSS_IP_IOPSCC
mdefine_line|#define OSS_IP_IOPSCC&t;0x0080
DECL|macro|OSS_IP_SOUND
mdefine_line|#define OSS_IP_SOUND&t;0x0100
DECL|macro|OSS_IP_SCSI
mdefine_line|#define OSS_IP_SCSI&t;0x0200
DECL|macro|OSS_IP_60HZ
mdefine_line|#define OSS_IP_60HZ&t;0x0400
DECL|macro|OSS_IP_VIA1
mdefine_line|#define OSS_IP_VIA1&t;0x0800
DECL|macro|OSS_IP_UNUSED1
mdefine_line|#define OSS_IP_UNUSED1&t;0x1000
DECL|macro|OSS_IP_UNUSED2
mdefine_line|#define OSS_IP_UNUSED2&t;0x2000
DECL|macro|OSS_IP_PARITY
mdefine_line|#define OSS_IP_PARITY&t;0x4000
DECL|macro|OSS_IP_UNUSED3
mdefine_line|#define OSS_IP_UNUSED3&t;0x8000
DECL|macro|OSS_IP_NUBUS
mdefine_line|#define OSS_IP_NUBUS (OSS_IP_NUBUS0|OSS_IP_NUBUS1|OSS_IP_NUBUS2|OSS_IP_NUBUS3|OSS_IP_NUBUS4|OSS_IP_NUBUS5)
multiline_comment|/*&n; * Rom Control Register&n; */
DECL|macro|OSS_POWEROFF
mdefine_line|#define OSS_POWEROFF&t;0x80
multiline_comment|/*&n; * OSS Interrupt levels for various sub-systems&n; *&n; * This mapping is layed out with two things in mind: first, we try to keep&n; * things on their own levels to avoid having to do double-dispatches. Second,&n; * the levels match as closely as possible the alternate IRQ mapping mode (aka&n; * &quot;A/UX mode&quot;) available on some VIA machines.&n; */
DECL|macro|OSS_IRQLEV_DISABLED
mdefine_line|#define OSS_IRQLEV_DISABLED&t;0
DECL|macro|OSS_IRQLEV_IOPISM
mdefine_line|#define OSS_IRQLEV_IOPISM&t;1&t;/* ADB? */
DECL|macro|OSS_IRQLEV_SCSI
mdefine_line|#define OSS_IRQLEV_SCSI&t;&t;2
DECL|macro|OSS_IRQLEV_NUBUS
mdefine_line|#define OSS_IRQLEV_NUBUS&t;3&t;/* keep this on its own level */
DECL|macro|OSS_IRQLEV_IOPSCC
mdefine_line|#define OSS_IRQLEV_IOPSCC&t;4&t;/* matches VIA alternate mapping */
DECL|macro|OSS_IRQLEV_SOUND
mdefine_line|#define OSS_IRQLEV_SOUND&t;5&t;/* matches VIA alternate mapping */
DECL|macro|OSS_IRQLEV_60HZ
mdefine_line|#define OSS_IRQLEV_60HZ&t;&t;6&t;/* matches VIA alternate mapping */
DECL|macro|OSS_IRQLEV_VIA1
mdefine_line|#define OSS_IRQLEV_VIA1&t;&t;6&t;/* matches VIA alternate mapping */
DECL|macro|OSS_IRQLEV_PARITY
mdefine_line|#define OSS_IRQLEV_PARITY&t;7&t;/* matches VIA alternate mapping */
macro_line|#ifndef __ASSEMBLY__
DECL|struct|mac_oss
r_struct
id|mac_oss
(brace
DECL|member|irq_level
id|__u8
id|irq_level
(braket
l_int|0x10
)braket
suffix:semicolon
multiline_comment|/* [0x000-0x00f] Interrupt levels */
DECL|member|padding0
id|__u8
id|padding0
(braket
l_int|0x1F2
)braket
suffix:semicolon
multiline_comment|/* [0x010-0x201] IO space filler */
DECL|member|irq_pending
id|__u16
id|irq_pending
suffix:semicolon
multiline_comment|/* [0x202-0x203] pending interrupts bits */
DECL|member|rom_ctrl
id|__u8
id|rom_ctrl
suffix:semicolon
multiline_comment|/* [0x204-0x204] ROM cntl reg (for poweroff) */
DECL|member|padding1
id|__u8
id|padding1
(braket
l_int|0x2
)braket
suffix:semicolon
multiline_comment|/* [0x205-0x206] currently unused by A/UX */
DECL|member|ack_60hz
id|__u8
id|ack_60hz
suffix:semicolon
multiline_comment|/* [0x207-0x207] 60 Hz ack. */
)brace
suffix:semicolon
r_extern
r_volatile
r_struct
id|mac_oss
op_star
id|oss
suffix:semicolon
r_extern
r_int
id|oss_present
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
eof
