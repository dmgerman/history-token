macro_line|#ifndef _LINUX_HDREG_H
DECL|macro|_LINUX_HDREG_H
mdefine_line|#define _LINUX_HDREG_H
multiline_comment|/*&n; * Command Header sizes for IOCTL commands&n; */
DECL|macro|HDIO_DRIVE_CMD_HDR_SIZE
mdefine_line|#define HDIO_DRIVE_CMD_HDR_SIZE&t;&t;(4 * sizeof(u8))
DECL|macro|HDIO_DRIVE_HOB_HDR_SIZE
mdefine_line|#define HDIO_DRIVE_HOB_HDR_SIZE&t;&t;(8 * sizeof(u8))
DECL|struct|hd_geometry
r_struct
id|hd_geometry
(brace
DECL|member|heads
id|__u8
id|heads
suffix:semicolon
DECL|member|sectors
id|__u8
id|sectors
suffix:semicolon
DECL|member|cylinders
id|__u16
id|cylinders
suffix:semicolon
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* hd/ide ctl&squot;s that pass (arg) ptrs to user space are numbered 0x030n/0x031n */
DECL|macro|HDIO_GETGEO
mdefine_line|#define HDIO_GETGEO&t;&t;0x0301&t;/* get device geometry */
DECL|macro|HDIO_GET_UNMASKINTR
mdefine_line|#define HDIO_GET_UNMASKINTR&t;0x0302&t;/* get current unmask setting */
DECL|macro|HDIO_GET_MULTCOUNT
mdefine_line|#define HDIO_GET_MULTCOUNT&t;0x0304&t;/* get current IDE blockmode setting */
DECL|macro|HDIO_GET_QDMA
mdefine_line|#define HDIO_GET_QDMA&t;&t;0x0305&t;/* get use-qdma flag */
DECL|macro|HDIO_GET_32BIT
mdefine_line|#define HDIO_GET_32BIT&t;&t;0x0309&t;/* get current io_32bit setting */
DECL|macro|HDIO_GET_NOWERR
mdefine_line|#define HDIO_GET_NOWERR&t;&t;0x030a&t;/* get ignore-write-error flag */
DECL|macro|HDIO_GET_DMA
mdefine_line|#define HDIO_GET_DMA&t;&t;0x030b&t;/* get use-dma flag */
DECL|macro|HDIO_GET_NICE
mdefine_line|#define HDIO_GET_NICE&t;&t;0x030c&t;/* get nice flags */
DECL|macro|HDIO_GET_IDENTITY
mdefine_line|#define HDIO_GET_IDENTITY&t;0x030d&t;/* get IDE identification info */
DECL|macro|HDIO_GET_WCACHE
mdefine_line|#define HDIO_GET_WCACHE&t;&t;0x030e&t;/* get write cache mode on|off */
DECL|macro|HDIO_GET_ACOUSTIC
mdefine_line|#define HDIO_GET_ACOUSTIC&t;0x030f&t;/* get acoustic value */
DECL|macro|HDIO_GET_ADDRESS
mdefine_line|#define&t;HDIO_GET_ADDRESS&t;0x0310&t;/* */
DECL|macro|HDIO_GET_BUSSTATE
mdefine_line|#define HDIO_GET_BUSSTATE&t;0x031a&t;/* get the bus state of the hwif */
DECL|macro|HDIO_DRIVE_CMD
mdefine_line|#define HDIO_DRIVE_CMD&t;&t;0x031f&t;/* execute a special drive command */
multiline_comment|/* hd/ide ctl&squot;s that pass (arg) non-ptr values are numbered 0x032n/0x033n */
DECL|macro|HDIO_SET_MULTCOUNT
mdefine_line|#define HDIO_SET_MULTCOUNT&t;0x0321&t;/* change IDE blockmode */
DECL|macro|HDIO_SET_UNMASKINTR
mdefine_line|#define HDIO_SET_UNMASKINTR&t;0x0322&t;/* permit other irqs during I/O */
DECL|macro|HDIO_SET_32BIT
mdefine_line|#define HDIO_SET_32BIT&t;&t;0x0324&t;/* change io_32bit flags */
DECL|macro|HDIO_SET_NOWERR
mdefine_line|#define HDIO_SET_NOWERR&t;&t;0x0325&t;/* change ignore-write-error flag */
DECL|macro|HDIO_SET_DMA
mdefine_line|#define HDIO_SET_DMA&t;&t;0x0326&t;/* change use-dma flag */
DECL|macro|HDIO_SET_PIO_MODE
mdefine_line|#define HDIO_SET_PIO_MODE&t;0x0327&t;/* reconfig interface to new speed */
DECL|macro|HDIO_SET_NICE
mdefine_line|#define HDIO_SET_NICE&t;&t;0x0329&t;/* set nice flags */
DECL|macro|HDIO_SET_WCACHE
mdefine_line|#define HDIO_SET_WCACHE&t;&t;0x032b&t;/* change write cache enable-disable */
DECL|macro|HDIO_SET_ACOUSTIC
mdefine_line|#define HDIO_SET_ACOUSTIC&t;0x032c&t;/* change acoustic behavior */
DECL|macro|HDIO_SET_BUSSTATE
mdefine_line|#define HDIO_SET_BUSSTATE&t;0x032d&t;/* set the bus state of the hwif */
DECL|macro|HDIO_SET_QDMA
mdefine_line|#define HDIO_SET_QDMA&t;&t;0x032e&t;/* change use-qdma flag */
DECL|macro|HDIO_SET_ADDRESS
mdefine_line|#define HDIO_SET_ADDRESS&t;0x032f&t;/* change lba addressing modes */
multiline_comment|/* hd/ide ctl&squot;s that pass (arg) ptrs to user space are numbered 0x033n/0x033n */
multiline_comment|/* 0x330 is reserved - used to be HDIO_GETGEO_BIG */
DECL|macro|HDIO_GETGEO_BIG_RAW
mdefine_line|#define HDIO_GETGEO_BIG_RAW&t;0x0331&t;/* */
macro_line|#endif
eof
