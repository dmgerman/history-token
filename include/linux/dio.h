multiline_comment|/* header file for DIO boards for the HP300 architecture.&n; * Maybe this should handle DIO-II later?&n; * The general structure of this is vaguely based on how&n; * the Amiga port handles Zorro boards.&n; * Copyright (C) Peter Maydell 05/1998 &lt;pmaydell@chiark.greenend.org.uk&gt;&n; *&n; * The board IDs are from the NetBSD kernel, which for once provided&n; * helpful comments...&n; *&n; * This goes with arch/m68k/hp300/dio.c&n; */
macro_line|#ifndef _LINUX_DIO_H
DECL|macro|_LINUX_DIO_H
mdefine_line|#define _LINUX_DIO_H
multiline_comment|/* The DIO boards in a system are distinguished by &squot;select codes&squot; which &n; * range from 0-63 (DIO) and 132-255 (DIO-II). &n; * The DIO board with select code sc is located at physical address &n; *     0x600000 + sc * 0x10000&n; * So DIO cards cover [0x600000-0x800000); the areas [0x200000-0x400000) and&n; * [0x800000-0x1000000) are for additional space required by things&n; * like framebuffers. [0x400000-0x600000) is for miscellaneous internal I/O.&n; * On Linux, this is currently all mapped into the virtual address space&n; * at 0xf0000000 on bootup.&n; * DIO-II boards are at 0x1000000 + (sc - 132) * 0x400000&n; * which is address range [0x1000000-0x20000000) -- too big to map completely,&n; * so currently we just don&squot;t handle DIO-II boards.  It wouldn&squot;t be hard to &n; * do with ioremap() though.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/hp300hw.h&gt;
multiline_comment|/* DIO/DIO-II boards all have the following 8bit registers.&n; * These are offsets from the base of the device.&n; */
DECL|macro|DIO_IDOFF
mdefine_line|#define DIO_IDOFF     0x01                        /* primary device ID */
DECL|macro|DIO_IPLOFF
mdefine_line|#define DIO_IPLOFF    0x03                        /* interrupt priority level */
DECL|macro|DIO_SECIDOFF
mdefine_line|#define DIO_SECIDOFF  0x15                        /* secondary device ID */
DECL|macro|DIOII_SIZEOFF
mdefine_line|#define DIOII_SIZEOFF 0x101                       /* device size, DIO-II only */
DECL|macro|DIO_VIRADDRBASE
mdefine_line|#define DIO_VIRADDRBASE 0xf0000000UL              /* vir addr where IOspace is mapped */
DECL|macro|DIO_BASE
mdefine_line|#define DIO_BASE                0x600000        /* start of DIO space */
DECL|macro|DIO_END
mdefine_line|#define DIO_END                 0x1000000       /* end of DIO space */
DECL|macro|DIO_DEVSIZE
mdefine_line|#define DIO_DEVSIZE             0x10000         /* size of a DIO device */
DECL|macro|DIOII_BASE
mdefine_line|#define DIOII_BASE              0x01000000      /* start of DIO-II space */
DECL|macro|DIOII_END
mdefine_line|#define DIOII_END               0x20000000      /* end of DIO-II space */
DECL|macro|DIOII_DEVSIZE
mdefine_line|#define DIOII_DEVSIZE           0x00400000      /* size of a DIO-II device */
multiline_comment|/* Highest valid select code. If we add DIO-II support this should become&n; * 256 for everything except HP320, which only has DIO.&n; */
DECL|macro|DIO_SCMAX
mdefine_line|#define DIO_SCMAX (hp300_model == HP_320 ? 32 : 256)
DECL|macro|DIOII_SCBASE
mdefine_line|#define DIOII_SCBASE 132 /* lowest DIO-II select code */
DECL|macro|DIO_SCINHOLE
mdefine_line|#define DIO_SCINHOLE(scode) (((scode) &gt;= 32) &amp;&amp; ((scode) &lt; DIOII_SCBASE))
DECL|macro|DIO_ISDIOII
mdefine_line|#define DIO_ISDIOII(scode) ((scode) &gt;= 132 &amp;&amp; (scode) &lt; 256)
multiline_comment|/* macros to read device IDs, given base address */
DECL|macro|DIO_ID
mdefine_line|#define DIO_ID(baseaddr) in_8((baseaddr) + DIO_IDOFF)
DECL|macro|DIO_SECID
mdefine_line|#define DIO_SECID(baseaddr) in_8((baseaddr) + DIO_SECIDOFF)
multiline_comment|/* extract the interrupt level */
DECL|macro|DIO_IPL
mdefine_line|#define DIO_IPL(baseaddr) (((in_8((baseaddr) + DIO_IPLOFF) &gt;&gt; 4) &amp; 0x03) + 3)
multiline_comment|/* find the size of a DIO-II board&squot;s address space.&n; * DIO boards are all fixed length.&n; */
DECL|macro|DIOII_SIZE
mdefine_line|#define DIOII_SIZE(baseaddr) ((in_8((baseaddr) + DIOII_SIZEOFF) + 1) * 0x100000)
multiline_comment|/* general purpose macro for both DIO and DIO-II */
DECL|macro|DIO_SIZE
mdefine_line|#define DIO_SIZE(scode, base) (DIO_ISDIOII((scode)) ? DIOII_SIZE((base)) : DIO_DEVSIZE)
multiline_comment|/* The hardware has primary and secondary IDs; we encode these in a single&n; * int as PRIMARY ID &amp; (SECONDARY ID &lt;&lt; 8).&n; * In practice this is only important for framebuffers,&n; * and everybody else just sets ID fields equal to the DIO_ID_FOO value.&n; */
DECL|macro|DIO_ENCODE_ID
mdefine_line|#define DIO_ENCODE_ID(pr,sec) ((((int)sec &amp; 0xff) &lt;&lt; 8) | ((int)pr &amp; 0xff))
multiline_comment|/* macro to determine whether a given primary ID requires a secondary ID byte */
DECL|macro|DIO_NEEDSSECID
mdefine_line|#define DIO_NEEDSSECID(id) ((id) == DIO_ID_FBUFFER)
multiline_comment|/* Now a whole slew of macros giving device IDs and descriptive strings: */
DECL|macro|DIO_ID_DCA0
mdefine_line|#define DIO_ID_DCA0     0x02 /* 98644A serial */
DECL|macro|DIO_DESC_DCA0
mdefine_line|#define DIO_DESC_DCA0 &quot;98644A DCA0 serial&quot;
DECL|macro|DIO_ID_DCA0REM
mdefine_line|#define DIO_ID_DCA0REM  0x82 /* 98644A serial */
DECL|macro|DIO_DESC_DCA0REM
mdefine_line|#define DIO_DESC_DCA0REM &quot;98644A DCA0REM serial&quot;
DECL|macro|DIO_ID_DCA1
mdefine_line|#define DIO_ID_DCA1     0x42 /* 98644A serial */
DECL|macro|DIO_DESC_DCA1
mdefine_line|#define DIO_DESC_DCA1 &quot;98644A DCA1 serial&quot;
DECL|macro|DIO_ID_DCA1REM
mdefine_line|#define DIO_ID_DCA1REM  0xc2 /* 98644A serial */
DECL|macro|DIO_DESC_DCA1REM
mdefine_line|#define DIO_DESC_DCA1REM &quot;98644A DCA1REM serial&quot;
DECL|macro|DIO_ID_DCM
mdefine_line|#define DIO_ID_DCM      0x05 /* 98642A serial MUX */
DECL|macro|DIO_DESC_DCM
mdefine_line|#define DIO_DESC_DCM &quot;98642A DCM serial MUX&quot;
DECL|macro|DIO_ID_DCMREM
mdefine_line|#define DIO_ID_DCMREM   0x85 /* 98642A serial MUX */
DECL|macro|DIO_DESC_DCMREM
mdefine_line|#define DIO_DESC_DCMREM &quot;98642A DCMREM serial MUX&quot;
DECL|macro|DIO_ID_LAN
mdefine_line|#define DIO_ID_LAN      0x15 /* 98643A LAN */
DECL|macro|DIO_DESC_LAN
mdefine_line|#define DIO_DESC_LAN &quot;98643A LANCE ethernet&quot;
DECL|macro|DIO_ID_FHPIB
mdefine_line|#define DIO_ID_FHPIB    0x08 /* 98625A/98625B fast HP-IB */
DECL|macro|DIO_DESC_FHPIB
mdefine_line|#define DIO_DESC_FHPIB &quot;98625A/98625B fast HPIB&quot;
DECL|macro|DIO_ID_NHPIB
mdefine_line|#define DIO_ID_NHPIB    0x01 /* 98624A HP-IB (normal ie slow) */
DECL|macro|DIO_DESC_NHPIB
mdefine_line|#define DIO_DESC_NHPIB &quot;98624A HPIB&quot;
DECL|macro|DIO_ID_SCSI0
mdefine_line|#define DIO_ID_SCSI0    0x07 /* 98265A SCSI */
DECL|macro|DIO_DESC_SCSI0
mdefine_line|#define DIO_DESC_SCSI0 &quot;98265A SCSI0&quot;
DECL|macro|DIO_ID_SCSI1
mdefine_line|#define DIO_ID_SCSI1    0x27 /* ditto */
DECL|macro|DIO_DESC_SCSI1
mdefine_line|#define DIO_DESC_SCSI1 &quot;98265A SCSI1&quot;
DECL|macro|DIO_ID_SCSI2
mdefine_line|#define DIO_ID_SCSI2    0x47 /* ditto */
DECL|macro|DIO_DESC_SCSI2
mdefine_line|#define DIO_DESC_SCSI2 &quot;98265A SCSI2&quot;
DECL|macro|DIO_ID_SCSI3
mdefine_line|#define DIO_ID_SCSI3    0x67 /* ditto */
DECL|macro|DIO_DESC_SCSI3
mdefine_line|#define DIO_DESC_SCSI3 &quot;98265A SCSI3&quot;
DECL|macro|DIO_ID_FBUFFER
mdefine_line|#define DIO_ID_FBUFFER  0x39 /* framebuffer: flavour is distinguished by secondary ID */
DECL|macro|DIO_DESC_FBUFFER
mdefine_line|#define DIO_DESC_FBUFFER &quot;bitmapped display&quot;
multiline_comment|/* the NetBSD kernel source is a bit unsure as to what these next IDs actually do :-&gt; */
DECL|macro|DIO_ID_MISC0
mdefine_line|#define DIO_ID_MISC0    0x03 /* 98622A */
DECL|macro|DIO_DESC_MISC0
mdefine_line|#define DIO_DESC_MISC0 &quot;98622A&quot;
DECL|macro|DIO_ID_MISC1
mdefine_line|#define DIO_ID_MISC1    0x04 /* 98623A */
DECL|macro|DIO_DESC_MISC1
mdefine_line|#define DIO_DESC_MISC1 &quot;98623A&quot;
DECL|macro|DIO_ID_PARALLEL
mdefine_line|#define DIO_ID_PARALLEL 0x06 /* internal parallel */
DECL|macro|DIO_DESC_PARALLEL
mdefine_line|#define DIO_DESC_PARALLEL &quot;internal parallel&quot;
DECL|macro|DIO_ID_MISC2
mdefine_line|#define DIO_ID_MISC2    0x09 /* 98287A keyboard */
DECL|macro|DIO_DESC_MISC2
mdefine_line|#define DIO_DESC_MISC2 &quot;98287A keyboard&quot;
DECL|macro|DIO_ID_MISC3
mdefine_line|#define DIO_ID_MISC3    0x0a /* HP98635A FP accelerator */
DECL|macro|DIO_DESC_MISC3
mdefine_line|#define DIO_DESC_MISC3 &quot;HP98635A FP accelerator&quot;
DECL|macro|DIO_ID_MISC4
mdefine_line|#define DIO_ID_MISC4    0x0b /* timer */
DECL|macro|DIO_DESC_MISC4
mdefine_line|#define DIO_DESC_MISC4 &quot;timer&quot;
DECL|macro|DIO_ID_MISC5
mdefine_line|#define DIO_ID_MISC5    0x12 /* 98640A */
DECL|macro|DIO_DESC_MISC5
mdefine_line|#define DIO_DESC_MISC5 &quot;98640A&quot;
DECL|macro|DIO_ID_MISC6
mdefine_line|#define DIO_ID_MISC6    0x16 /* 98659A */
DECL|macro|DIO_DESC_MISC6
mdefine_line|#define DIO_DESC_MISC6 &quot;98659A&quot;
DECL|macro|DIO_ID_MISC7
mdefine_line|#define DIO_ID_MISC7    0x19 /* 237 display */
DECL|macro|DIO_DESC_MISC7
mdefine_line|#define DIO_DESC_MISC7 &quot;237 display&quot;
DECL|macro|DIO_ID_MISC8
mdefine_line|#define DIO_ID_MISC8    0x1a /* quad-wide card */
DECL|macro|DIO_DESC_MISC8
mdefine_line|#define DIO_DESC_MISC8 &quot;quad-wide card&quot;
DECL|macro|DIO_ID_MISC9
mdefine_line|#define DIO_ID_MISC9    0x1b /* 98253A */
DECL|macro|DIO_DESC_MISC9
mdefine_line|#define DIO_DESC_MISC9 &quot;98253A&quot;
DECL|macro|DIO_ID_MISC10
mdefine_line|#define DIO_ID_MISC10   0x1c /* 98627A */
DECL|macro|DIO_DESC_MISC10
mdefine_line|#define DIO_DESC_MISC10 &quot;98253A&quot;
DECL|macro|DIO_ID_MISC11
mdefine_line|#define DIO_ID_MISC11   0x1d /* 98633A */
DECL|macro|DIO_DESC_MISC11
mdefine_line|#define DIO_DESC_MISC11 &quot;98633A&quot;
DECL|macro|DIO_ID_MISC12
mdefine_line|#define DIO_ID_MISC12   0x1e /* 98259A */
DECL|macro|DIO_DESC_MISC12
mdefine_line|#define DIO_DESC_MISC12 &quot;98259A&quot;
DECL|macro|DIO_ID_MISC13
mdefine_line|#define DIO_ID_MISC13   0x1f /* 8741 */
DECL|macro|DIO_DESC_MISC13
mdefine_line|#define DIO_DESC_MISC13 &quot;8741&quot;
DECL|macro|DIO_ID_VME
mdefine_line|#define DIO_ID_VME      0x31 /* 98577A VME adapter */
DECL|macro|DIO_DESC_VME
mdefine_line|#define DIO_DESC_VME &quot;98577A VME adapter&quot;
DECL|macro|DIO_ID_DCL
mdefine_line|#define DIO_ID_DCL      0x34 /* 98628A serial */
DECL|macro|DIO_DESC_DCL
mdefine_line|#define DIO_DESC_DCL &quot;98628A DCL serial&quot;
DECL|macro|DIO_ID_DCLREM
mdefine_line|#define DIO_ID_DCLREM   0xb4 /* 98628A serial */
DECL|macro|DIO_DESC_DCLREM
mdefine_line|#define DIO_DESC_DCLREM &quot;98628A DCLREM serial&quot;
multiline_comment|/* These are the secondary IDs for the framebuffers */
DECL|macro|DIO_ID2_GATORBOX
mdefine_line|#define DIO_ID2_GATORBOX    0x01 /* 98700/98710 &quot;gatorbox&quot; */
DECL|macro|DIO_DESC2_GATORBOX
mdefine_line|#define DIO_DESC2_GATORBOX       &quot;98700/98710 &bslash;&quot;gatorbox&bslash;&quot; display&quot;
DECL|macro|DIO_ID2_TOPCAT
mdefine_line|#define DIO_ID2_TOPCAT      0x02 /* 98544/98545/98547 &quot;topcat&quot; */
DECL|macro|DIO_DESC2_TOPCAT
mdefine_line|#define DIO_DESC2_TOPCAT         &quot;98544/98545/98547 &bslash;&quot;topcat&bslash;&quot; display&quot;
DECL|macro|DIO_ID2_RENAISSANCE
mdefine_line|#define DIO_ID2_RENAISSANCE 0x04 /* 98720/98721 &quot;renaissance&quot; */
DECL|macro|DIO_DESC2_RENAISSANCE
mdefine_line|#define DIO_DESC2_RENAISSANCE    &quot;98720/98721 &bslash;&quot;renaissance&bslash;&quot; display&quot;
DECL|macro|DIO_ID2_LRCATSEYE
mdefine_line|#define DIO_ID2_LRCATSEYE   0x05 /* lowres &quot;catseye&quot; */
DECL|macro|DIO_DESC2_LRCATSEYE
mdefine_line|#define DIO_DESC2_LRCATSEYE      &quot;low-res catseye display&quot;
DECL|macro|DIO_ID2_HRCCATSEYE
mdefine_line|#define DIO_ID2_HRCCATSEYE  0x06 /* highres colour &quot;catseye&quot; */
DECL|macro|DIO_DESC2_HRCCATSEYE
mdefine_line|#define DIO_DESC2_HRCCATSEYE     &quot;high-res color catseye display&quot;
DECL|macro|DIO_ID2_HRMCATSEYE
mdefine_line|#define DIO_ID2_HRMCATSEYE  0x07 /* highres mono &quot;catseye&quot; */
DECL|macro|DIO_DESC2_HRMCATSEYE
mdefine_line|#define DIO_DESC2_HRMCATSEYE     &quot;high-res mono catseye display&quot;
DECL|macro|DIO_ID2_DAVINCI
mdefine_line|#define DIO_ID2_DAVINCI     0x08 /* 98730/98731 &quot;davinci&quot; */
DECL|macro|DIO_DESC2_DAVINCI
mdefine_line|#define DIO_DESC2_DAVINCI        &quot;98730/98731 &bslash;&quot;davinci&bslash;&quot; display&quot;
DECL|macro|DIO_ID2_XXXCATSEYE
mdefine_line|#define DIO_ID2_XXXCATSEYE  0x09 /* &quot;catseye&quot; */
DECL|macro|DIO_DESC2_XXXCATSEYE
mdefine_line|#define DIO_DESC2_XXXCATSEYE     &quot;catseye display&quot;
DECL|macro|DIO_ID2_HYPERION
mdefine_line|#define DIO_ID2_HYPERION    0x0e /* A1096A &quot;hyperion&quot; */
DECL|macro|DIO_DESC2_HYPERION
mdefine_line|#define DIO_DESC2_HYPERION       &quot;A1096A &bslash;&quot;hyperion&bslash;&quot; display&quot;
DECL|macro|DIO_ID2_XGENESIS
mdefine_line|#define DIO_ID2_XGENESIS    0x0b /* &quot;x-genesis&quot;; no NetBSD support */
DECL|macro|DIO_DESC2_XGENESIS
mdefine_line|#define DIO_DESC2_XGENESIS       &quot;&bslash;&quot;x-genesis&bslash;&quot; display&quot;
DECL|macro|DIO_ID2_TIGER
mdefine_line|#define DIO_ID2_TIGER       0x0c /* &quot;tiger&quot;; no NetBSD support */
DECL|macro|DIO_DESC2_TIGER
mdefine_line|#define DIO_DESC2_TIGER          &quot;&bslash;&quot;tiger&bslash;&quot; display&quot;
DECL|macro|DIO_ID2_YGENESIS
mdefine_line|#define DIO_ID2_YGENESIS    0x0d /* &quot;y-genesis&quot;; no NetBSD support */
DECL|macro|DIO_DESC2_YGENESIS
mdefine_line|#define DIO_DESC2_YGENESIS       &quot;&bslash;&quot;y-genesis&bslash;&quot; display&quot;
multiline_comment|/* if you add new IDs then you should tell dio.c about them so it can&n; * identify them...&n; */
r_extern
r_int
id|dio_find
c_func
(paren
r_int
id|deviceid
)paren
suffix:semicolon
r_extern
r_int
r_int
id|dio_scodetophysaddr
c_func
(paren
r_int
id|scode
)paren
suffix:semicolon
r_extern
r_int
id|dio_scodetoipl
c_func
(paren
r_int
id|scode
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|dio_scodetoname
c_func
(paren
r_int
id|scode
)paren
suffix:semicolon
r_extern
r_void
id|dio_config_board
c_func
(paren
r_int
id|scode
)paren
suffix:semicolon
r_extern
r_void
id|dio_unconfig_board
c_func
(paren
r_int
id|scode
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* ndef _LINUX_DIO_H */
eof
