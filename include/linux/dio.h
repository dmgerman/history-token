multiline_comment|/* header file for DIO boards for the HP300 architecture.&n; * Maybe this should handle DIO-II later?&n; * The general structure of this is vaguely based on how&n; * the Amiga port handles Zorro boards.&n; * Copyright (C) Peter Maydell 05/1998 &lt;pmaydell@chiark.greenend.org.uk&gt;&n; * Converted to driver model Jochen Friedrich &lt;jochen@scram.de&gt;&n; *&n; * The board IDs are from the NetBSD kernel, which for once provided&n; * helpful comments...&n; *&n; * This goes with drivers/dio/dio.c&n; */
macro_line|#ifndef _LINUX_DIO_H
DECL|macro|_LINUX_DIO_H
mdefine_line|#define _LINUX_DIO_H
multiline_comment|/* The DIO boards in a system are distinguished by &squot;select codes&squot; which &n; * range from 0-63 (DIO) and 132-255 (DIO-II). &n; * The DIO board with select code sc is located at physical address &n; *     0x600000 + sc * 0x10000&n; * So DIO cards cover [0x600000-0x800000); the areas [0x200000-0x400000) and&n; * [0x800000-0x1000000) are for additional space required by things&n; * like framebuffers. [0x400000-0x600000) is for miscellaneous internal I/O.&n; * On Linux, this is currently all mapped into the virtual address space&n; * at 0xf0000000 on bootup.&n; * DIO-II boards are at 0x1000000 + (sc - 132) * 0x400000&n; * which is address range [0x1000000-0x20000000) -- too big to map completely,&n; * so currently we just don&squot;t handle DIO-II boards.  It wouldn&squot;t be hard to &n; * do with ioremap() though.&n; */
macro_line|#include &lt;linux/device.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/hp300hw.h&gt;
DECL|typedef|dio_id
r_typedef
id|__u16
id|dio_id
suffix:semicolon
multiline_comment|/*&n;     *  DIO devices&n;     */
DECL|struct|dio_dev
r_struct
id|dio_dev
(brace
DECL|member|bus
r_struct
id|dio_bus
op_star
id|bus
suffix:semicolon
DECL|member|id
id|dio_id
id|id
suffix:semicolon
DECL|member|scode
r_int
id|scode
suffix:semicolon
DECL|member|driver
r_struct
id|dio_driver
op_star
id|driver
suffix:semicolon
multiline_comment|/* which driver has allocated this device */
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* Generic device interface */
DECL|member|ipl
id|u8
id|ipl
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|resource
r_struct
id|resource
id|resource
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_dio_dev
mdefine_line|#define to_dio_dev(n) container_of(n, struct dio_dev, dev)
multiline_comment|/*&n;     *  DIO bus&n;     */
DECL|struct|dio_bus
r_struct
id|dio_bus
(brace
DECL|member|devices
r_struct
id|list_head
id|devices
suffix:semicolon
multiline_comment|/* list of devices on this bus */
DECL|member|num_resources
r_int
r_int
id|num_resources
suffix:semicolon
multiline_comment|/* number of resources */
DECL|member|resources
r_struct
id|resource
id|resources
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* address space routed to this bus */
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|10
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|dio_bus
id|dio_bus
suffix:semicolon
multiline_comment|/* Single DIO bus */
r_extern
r_struct
id|bus_type
id|dio_bus_type
suffix:semicolon
multiline_comment|/*&n;     *  DIO device IDs&n;     */
DECL|struct|dio_device_id
r_struct
id|dio_device_id
(brace
DECL|member|id
id|dio_id
id|id
suffix:semicolon
multiline_comment|/* Device ID or DIO_WILDCARD */
DECL|member|driver_data
r_int
r_int
id|driver_data
suffix:semicolon
multiline_comment|/* Data private to the driver */
)brace
suffix:semicolon
multiline_comment|/*&n;     *  DIO device drivers&n;     */
DECL|struct|dio_driver
r_struct
id|dio_driver
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id_table
r_const
r_struct
id|dio_device_id
op_star
id|id_table
suffix:semicolon
multiline_comment|/* NULL if wants all devices */
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_struct
id|dio_dev
op_star
id|z
comma
r_const
r_struct
id|dio_device_id
op_star
id|id
)paren
suffix:semicolon
multiline_comment|/* New device inserted */
DECL|member|remove
r_void
(paren
op_star
id|remove
)paren
(paren
r_struct
id|dio_dev
op_star
id|z
)paren
suffix:semicolon
multiline_comment|/* Device removed (NULL if not a hot-plug capable driver) */
DECL|member|driver
r_struct
id|device_driver
id|driver
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_dio_driver
mdefine_line|#define to_dio_driver(drv)    container_of(drv, struct dio_driver, driver)
multiline_comment|/* DIO/DIO-II boards all have the following 8bit registers.&n; * These are offsets from the base of the device.&n; */
DECL|macro|DIO_IDOFF
mdefine_line|#define DIO_IDOFF     0x01             /* primary device ID */
DECL|macro|DIO_IPLOFF
mdefine_line|#define DIO_IPLOFF    0x03             /* interrupt priority level */
DECL|macro|DIO_SECIDOFF
mdefine_line|#define DIO_SECIDOFF  0x15             /* secondary device ID */
DECL|macro|DIOII_SIZEOFF
mdefine_line|#define DIOII_SIZEOFF 0x101            /* device size, DIO-II only */
DECL|macro|DIO_VIRADDRBASE
mdefine_line|#define DIO_VIRADDRBASE 0xf0000000UL   /* vir addr where IOspace is mapped */
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
DECL|macro|DIO_WILDCARD
mdefine_line|#define DIO_WILDCARD 0xff
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
r_void
id|dio_create_sysfs_dev_files
c_func
(paren
r_struct
id|dio_dev
op_star
)paren
suffix:semicolon
multiline_comment|/* New-style probing */
r_extern
r_int
id|dio_register_driver
c_func
(paren
r_struct
id|dio_driver
op_star
)paren
suffix:semicolon
r_extern
r_void
id|dio_unregister_driver
c_func
(paren
r_struct
id|dio_driver
op_star
)paren
suffix:semicolon
r_extern
r_const
r_struct
id|dio_device_id
op_star
id|dio_match_device
c_func
(paren
r_const
r_struct
id|dio_device_id
op_star
id|ids
comma
r_const
r_struct
id|dio_dev
op_star
id|z
)paren
suffix:semicolon
DECL|function|dio_dev_driver
r_static
r_inline
r_struct
id|dio_driver
op_star
id|dio_dev_driver
c_func
(paren
r_const
r_struct
id|dio_dev
op_star
id|d
)paren
(brace
r_return
id|d-&gt;driver
suffix:semicolon
)brace
DECL|macro|dio_resource_start
mdefine_line|#define dio_resource_start(d) ((d)-&gt;resource.start)
DECL|macro|dio_resource_end
mdefine_line|#define dio_resource_end(d)   ((d)-&gt;resource.end)
DECL|macro|dio_resource_len
mdefine_line|#define dio_resource_len(d)   ((d)-&gt;resource.end-(z)-&gt;resource.start+1)
DECL|macro|dio_resource_flags
mdefine_line|#define dio_resource_flags(d) ((d)-&gt;resource.flags)
DECL|macro|dio_request_device
mdefine_line|#define dio_request_device(d, name) &bslash;&n;    request_mem_region(dio_resource_start(d), dio_resource_len(d), name)
DECL|macro|dio_release_device
mdefine_line|#define dio_release_device(d) &bslash;&n;    release_mem_region(dio_resource_start(d), dio_resource_len(d))
multiline_comment|/* Similar to the helpers above, these manipulate per-dio_dev&n; * driver-specific data.  They are really just a wrapper around&n; * the generic device structure functions of these calls.&n; */
DECL|function|dio_get_drvdata
r_static
r_inline
r_void
op_star
id|dio_get_drvdata
(paren
r_struct
id|dio_dev
op_star
id|d
)paren
(brace
r_return
id|dev_get_drvdata
c_func
(paren
op_amp
id|d-&gt;dev
)paren
suffix:semicolon
)brace
DECL|function|dio_set_drvdata
r_static
r_inline
r_void
id|dio_set_drvdata
(paren
r_struct
id|dio_dev
op_star
id|d
comma
r_void
op_star
id|data
)paren
(brace
id|dev_set_drvdata
c_func
(paren
op_amp
id|d-&gt;dev
comma
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * A helper function which helps ensure correct dio_driver&n; * setup and cleanup for commonly-encountered hotplug/modular cases&n; *&n; * This MUST stay in a header, as it checks for -DMODULE&n; */
DECL|function|dio_module_init
r_static
r_inline
r_int
id|dio_module_init
c_func
(paren
r_struct
id|dio_driver
op_star
id|drv
)paren
(brace
r_int
id|rc
op_assign
id|dio_register_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OG
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* iff CONFIG_HOTPLUG and built into kernel, we should&n;&t; * leave the driver around for future hotplug events.&n;&t; * For the module case, a hotplug daemon of some sort&n;&t; * should load a module in response to an insert event. */
macro_line|#if defined(CONFIG_HOTPLUG) &amp;&amp; !defined(MODULE)
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
macro_line|#endif
multiline_comment|/* if we get here, we need to clean up DIO driver instance&n;&t; * and return some sort of error */
id|dio_unregister_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* ndef _LINUX_DIO_H */
eof
