multiline_comment|/*&t;BSDI dptsig.h,v 1.7 1998/06/03 19:15:00 karels Exp&t;*/
multiline_comment|/*&n; * Copyright (c) 1996-1999 Distributed Processing Technology Corporation&n; * All rights reserved.&n; *&n; * Redistribution and use in source form, with or without modification, are&n; * permitted provided that redistributions of source code must retain the&n; * above copyright notice, this list of conditions and the following disclaimer.&n; *&n; * This software is provided `as is&squot; by Distributed Processing Technology and&n; * any express or implied warranties, including, but not limited to, the&n; * implied warranties of merchantability and fitness for a particular purpose,&n; * are disclaimed. In no event shall Distributed Processing Technology be&n; * liable for any direct, indirect, incidental, special, exemplary or&n; * consequential damages (including, but not limited to, procurement of&n; * substitute goods or services; loss of use, data, or profits; or business&n; * interruptions) however caused and on any theory of liability, whether in&n; * contract, strict liability, or tort (including negligence or otherwise)&n; * arising in any way out of the use of this driver software, even if advised&n; * of the possibility of such damage.&n; *&n; */
macro_line|#ifndef __DPTSIG_H_
DECL|macro|__DPTSIG_H_
mdefine_line|#define __DPTSIG_H_
macro_line|#ifdef _SINIX_ADDON
macro_line|#include &quot;dpt.h&quot;
macro_line|#endif
multiline_comment|/* DPT SIGNATURE SPEC AND HEADER FILE                           */
multiline_comment|/* Signature Version 1 (sorry no &squot;A&squot;)                           */
multiline_comment|/* to make sure we are talking the same size under all OS&squot;s     */
DECL|typedef|sigBYTE
r_typedef
r_int
r_char
id|sigBYTE
suffix:semicolon
DECL|typedef|sigWORD
r_typedef
r_int
r_int
id|sigWORD
suffix:semicolon
macro_line|#if (defined(_MULTI_DATAMODEL) &amp;&amp; defined(sun) &amp;&amp; !defined(_ILP32))
DECL|typedef|sigLONG
r_typedef
r_uint32
id|sigLONG
suffix:semicolon
macro_line|#else
DECL|typedef|sigLONG
r_typedef
r_int
r_int
id|sigLONG
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * use sigWORDLittleEndian for:&n; *  dsCapabilities&n; *  dsDeviceSupp&n; *  dsAdapterSupp&n; *  dsApplication&n; * use sigLONGLittleEndian for:&n; *      dsOS&n; * so that the sig can be standardised to Little Endian&n; */
macro_line|#if (defined(_DPT_BIG_ENDIAN))
DECL|macro|sigWORDLittleEndian
macro_line|# define sigWORDLittleEndian(x) ((((x)&amp;0xFF)&lt;&lt;8)|(((x)&gt;&gt;8)&amp;0xFF))
DECL|macro|sigLONGLittleEndian
macro_line|# define sigLONGLittleEndian(x) &bslash;&n;        ((((x)&amp;0xFF)&lt;&lt;24) |             &bslash;&n;         (((x)&amp;0xFF00)&lt;&lt;8) |    &bslash;&n;         (((x)&amp;0xFF0000L)&gt;&gt;8) | &bslash;&n;         (((x)&amp;0xFF000000L)&gt;&gt;24))
macro_line|#else
DECL|macro|sigWORDLittleEndian
macro_line|# define sigWORDLittleEndian(x) (x)
DECL|macro|sigLONGLittleEndian
macro_line|# define sigLONGLittleEndian(x) (x)
macro_line|#endif
multiline_comment|/* must make sure the structure is not word or double-word aligned      */
multiline_comment|/* ---------------------------------------------------------------      */
multiline_comment|/* Borland will ignore the following pragma:                            */
multiline_comment|/* Word alignment is OFF by default.  If in the, IDE make               */
multiline_comment|/* sure that Options | Compiler | Code Generation | Word Alignment      */
multiline_comment|/* is not checked.  If using BCC, do not use the -a option.             */
macro_line|#ifndef NO_PACK
macro_line|#if defined (_DPT_AIX)
macro_line|#pragma options align=packed
macro_line|#else
macro_line|#pragma pack(1)
macro_line|#endif  /* aix */
macro_line|#endif
multiline_comment|/* For the Macintosh */
macro_line|#if STRUCTALIGNMENTSUPPORTED
macro_line|#pragma options align=mac68k
macro_line|#endif
multiline_comment|/* Current Signature Version - sigBYTE dsSigVersion; */
multiline_comment|/* ------------------------------------------------------------------ */
DECL|macro|SIG_VERSION
mdefine_line|#define SIG_VERSION 1
multiline_comment|/* Processor Family - sigBYTE dsProcessorFamily;  DISTINCT VALUES */
multiline_comment|/* ------------------------------------------------------------------ */
multiline_comment|/* What type of processor the file is meant to run on. */
multiline_comment|/* This will let us know whether to read sigWORDs as high/low or low/high. */
DECL|macro|PROC_INTEL
mdefine_line|#define PROC_INTEL      0x00    /* Intel 80x86 */
DECL|macro|PROC_MOTOROLA
mdefine_line|#define PROC_MOTOROLA   0x01    /* Motorola 68K */
DECL|macro|PROC_MIPS4000
mdefine_line|#define PROC_MIPS4000   0x02    /* MIPS RISC 4000 */
DECL|macro|PROC_ALPHA
mdefine_line|#define PROC_ALPHA      0x03    /* DEC Alpha */
DECL|macro|PROC_POWERPC
mdefine_line|#define PROC_POWERPC    0x04    /* IBM Power PC */
DECL|macro|PROC_i960
mdefine_line|#define PROC_i960       0x05    /* Intel i960 */
DECL|macro|PROC_ULTRASPARC
mdefine_line|#define PROC_ULTRASPARC 0x06    /* SPARC processor */
multiline_comment|/* Specific Minimim Processor - sigBYTE dsProcessor;    FLAG BITS */
multiline_comment|/* ------------------------------------------------------------------ */
multiline_comment|/* Different bit definitions dependent on processor_family */
multiline_comment|/* PROC_INTEL: */
DECL|macro|PROC_8086
mdefine_line|#define PROC_8086       0x01    /* Intel 8086 */
DECL|macro|PROC_286
mdefine_line|#define PROC_286        0x02    /* Intel 80286 */
DECL|macro|PROC_386
mdefine_line|#define PROC_386        0x04    /* Intel 80386 */
DECL|macro|PROC_486
mdefine_line|#define PROC_486        0x08    /* Intel 80486 */
DECL|macro|PROC_PENTIUM
mdefine_line|#define PROC_PENTIUM    0x10    /* Intel 586 aka P5 aka Pentium */
DECL|macro|PROC_SEXIUM
mdefine_line|#define PROC_SEXIUM&t;0x20&t;/* Intel 686 aka P6 aka Pentium Pro or MMX */
multiline_comment|/* PROC_i960: */
DECL|macro|PROC_960RX
mdefine_line|#define PROC_960RX      0x01    /* Intel 80960RC/RD */
DECL|macro|PROC_960HX
mdefine_line|#define PROC_960HX      0x02    /* Intel 80960HA/HD/HT */
multiline_comment|/* PROC_MOTOROLA: */
DECL|macro|PROC_68000
mdefine_line|#define PROC_68000      0x01    /* Motorola 68000 */
DECL|macro|PROC_68010
mdefine_line|#define PROC_68010&t;0x02&t;/* Motorola 68010 */
DECL|macro|PROC_68020
mdefine_line|#define PROC_68020      0x04    /* Motorola 68020 */
DECL|macro|PROC_68030
mdefine_line|#define PROC_68030      0x08    /* Motorola 68030 */
DECL|macro|PROC_68040
mdefine_line|#define PROC_68040      0x10    /* Motorola 68040 */
multiline_comment|/* PROC_POWERPC */
DECL|macro|PROC_PPC601
mdefine_line|#define PROC_PPC601&t;&t;0x01&t;/* PowerPC 601 */
DECL|macro|PROC_PPC603
mdefine_line|#define PROC_PPC603&t;&t;0x02&t;/* PowerPC 603 */
DECL|macro|PROC_PPC604
mdefine_line|#define PROC_PPC604&t;&t;0x04&t;/* PowerPC 604 */
multiline_comment|/* PROC_MIPS4000: */
DECL|macro|PROC_R4000
mdefine_line|#define PROC_R4000      0x01    /* MIPS R4000 */
multiline_comment|/* Filetype - sigBYTE dsFiletype;       DISTINCT VALUES */
multiline_comment|/* ------------------------------------------------------------------ */
DECL|macro|FT_EXECUTABLE
mdefine_line|#define FT_EXECUTABLE   0       /* Executable Program */
DECL|macro|FT_SCRIPT
mdefine_line|#define FT_SCRIPT       1       /* Script/Batch File??? */
DECL|macro|FT_HBADRVR
mdefine_line|#define FT_HBADRVR      2       /* HBA Driver */
DECL|macro|FT_OTHERDRVR
mdefine_line|#define FT_OTHERDRVR    3       /* Other Driver */
DECL|macro|FT_IFS
mdefine_line|#define FT_IFS          4       /* Installable Filesystem Driver */
DECL|macro|FT_ENGINE
mdefine_line|#define FT_ENGINE       5       /* DPT Engine */
DECL|macro|FT_COMPDRVR
mdefine_line|#define FT_COMPDRVR     6       /* Compressed Driver Disk */
DECL|macro|FT_LANGUAGE
mdefine_line|#define FT_LANGUAGE     7       /* Foreign Language file */
DECL|macro|FT_FIRMWARE
mdefine_line|#define FT_FIRMWARE     8       /* Downloadable or actual Firmware */
DECL|macro|FT_COMMMODL
mdefine_line|#define FT_COMMMODL     9       /* Communications Module */
DECL|macro|FT_INT13
mdefine_line|#define FT_INT13        10      /* INT 13 style HBA Driver */
DECL|macro|FT_HELPFILE
mdefine_line|#define FT_HELPFILE     11      /* Help file */
DECL|macro|FT_LOGGER
mdefine_line|#define FT_LOGGER       12      /* Event Logger */
DECL|macro|FT_INSTALL
mdefine_line|#define FT_INSTALL      13      /* An Install Program */
DECL|macro|FT_LIBRARY
mdefine_line|#define FT_LIBRARY      14      /* Storage Manager Real-Mode Calls */
DECL|macro|FT_RESOURCE
mdefine_line|#define FT_RESOURCE &t;15 &t;/* Storage Manager Resource File */
DECL|macro|FT_MODEM_DB
mdefine_line|#define FT_MODEM_DB  &t;16  &t;/* Storage Manager Modem Database */
multiline_comment|/* Filetype flags - sigBYTE dsFiletypeFlags;    FLAG BITS */
multiline_comment|/* ------------------------------------------------------------------ */
DECL|macro|FTF_DLL
mdefine_line|#define FTF_DLL         0x01    /* Dynamic Link Library */
DECL|macro|FTF_NLM
mdefine_line|#define FTF_NLM         0x02    /* Netware Loadable Module */
DECL|macro|FTF_OVERLAYS
mdefine_line|#define FTF_OVERLAYS    0x04    /* Uses overlays */
DECL|macro|FTF_DEBUG
mdefine_line|#define FTF_DEBUG       0x08    /* Debug version */
DECL|macro|FTF_TSR
mdefine_line|#define FTF_TSR         0x10    /* TSR */
DECL|macro|FTF_SYS
mdefine_line|#define FTF_SYS         0x20    /* DOS Loadable driver */
DECL|macro|FTF_PROTECTED
mdefine_line|#define FTF_PROTECTED   0x40    /* Runs in protected mode */
DECL|macro|FTF_APP_SPEC
mdefine_line|#define FTF_APP_SPEC    0x80    /* Application Specific */
DECL|macro|FTF_ROM
mdefine_line|#define FTF_ROM&t;&t;(FTF_SYS|FTF_TSR)&t;/* Special Case */
multiline_comment|/* OEM - sigBYTE dsOEM;         DISTINCT VALUES */
multiline_comment|/* ------------------------------------------------------------------ */
DECL|macro|OEM_DPT
mdefine_line|#define OEM_DPT         0       /* DPT */
DECL|macro|OEM_ATT
mdefine_line|#define OEM_ATT         1       /* ATT */
DECL|macro|OEM_NEC
mdefine_line|#define OEM_NEC         2       /* NEC */
DECL|macro|OEM_ALPHA
mdefine_line|#define OEM_ALPHA       3       /* Alphatronix */
DECL|macro|OEM_AST
mdefine_line|#define OEM_AST         4       /* AST */
DECL|macro|OEM_OLIVETTI
mdefine_line|#define OEM_OLIVETTI    5       /* Olivetti */
DECL|macro|OEM_SNI
mdefine_line|#define OEM_SNI         6       /* Siemens/Nixdorf */
DECL|macro|OEM_SUN
mdefine_line|#define OEM_SUN         7       /* SUN Microsystems */
multiline_comment|/* Operating System  - sigLONG dsOS;    FLAG BITS */
multiline_comment|/* ------------------------------------------------------------------ */
DECL|macro|OS_DOS
mdefine_line|#define OS_DOS          0x00000001 /* PC/MS-DOS&t;&t;&t;&t;*/
DECL|macro|OS_WINDOWS
mdefine_line|#define OS_WINDOWS      0x00000002 /* Microsoft Windows 3.x&t;&t;*/
DECL|macro|OS_WINDOWS_NT
mdefine_line|#define OS_WINDOWS_NT   0x00000004 /* Microsoft Windows NT&t;&t;*/
DECL|macro|OS_OS2M
mdefine_line|#define OS_OS2M         0x00000008 /* OS/2 1.2.x,MS 1.3.0,IBM 1.3.x - Monolithic */
DECL|macro|OS_OS2L
mdefine_line|#define OS_OS2L         0x00000010 /* Microsoft OS/2 1.301 - LADDR&t;*/
DECL|macro|OS_OS22x
mdefine_line|#define OS_OS22x        0x00000020 /* IBM OS/2 2.x&t;&t;&t;*/
DECL|macro|OS_NW286
mdefine_line|#define OS_NW286        0x00000040 /* Novell NetWare 286&t;&t;*/
DECL|macro|OS_NW386
mdefine_line|#define OS_NW386        0x00000080 /* Novell NetWare 386&t;&t;*/
DECL|macro|OS_GEN_UNIX
mdefine_line|#define OS_GEN_UNIX     0x00000100 /* Generic Unix&t;&t;&t;*/
DECL|macro|OS_SCO_UNIX
mdefine_line|#define OS_SCO_UNIX     0x00000200 /* SCO Unix&t;&t;&t;&t;*/
DECL|macro|OS_ATT_UNIX
mdefine_line|#define OS_ATT_UNIX     0x00000400 /* ATT Unix&t;&t;&t;&t;*/
DECL|macro|OS_UNIXWARE
mdefine_line|#define OS_UNIXWARE     0x00000800 /* USL Unix&t;&t;&t;&t;*/
DECL|macro|OS_INT_UNIX
mdefine_line|#define OS_INT_UNIX     0x00001000 /* Interactive Unix&t;&t;&t;*/
DECL|macro|OS_SOLARIS
mdefine_line|#define OS_SOLARIS      0x00002000 /* SunSoft Solaris&t;&t;&t;*/
DECL|macro|OS_QNX
mdefine_line|#define OS_QNX          0x00004000 /* QNX for Tom Moch&t;&t;&t;*/
DECL|macro|OS_NEXTSTEP
mdefine_line|#define OS_NEXTSTEP     0x00008000 /* NeXTSTEP/OPENSTEP/MACH&t;&t;*/
DECL|macro|OS_BANYAN
mdefine_line|#define OS_BANYAN       0x00010000 /* Banyan Vines&t;&t;&t;*/
DECL|macro|OS_OLIVETTI_UNIX
mdefine_line|#define OS_OLIVETTI_UNIX 0x00020000/* Olivetti Unix&t;&t;&t;*/
DECL|macro|OS_MAC_OS
mdefine_line|#define OS_MAC_OS&t;0x00040000 /* Mac OS&t;&t;&t;&t;*/
DECL|macro|OS_WINDOWS_95
mdefine_line|#define OS_WINDOWS_95&t;0x00080000 /* Microsoft Windows &squot;95&t;&t;*/
DECL|macro|OS_NW4x
mdefine_line|#define OS_NW4x&t;&t;0x00100000 /* Novell Netware 4.x&t;&t;*/
DECL|macro|OS_BSDI_UNIX
mdefine_line|#define OS_BSDI_UNIX&t;0x00200000 /* BSDi Unix BSD/OS 2.0 and up&t;*/
DECL|macro|OS_AIX_UNIX
mdefine_line|#define OS_AIX_UNIX     0x00400000 /* AIX Unix&t;&t;&t;&t;*/
DECL|macro|OS_FREE_BSD
mdefine_line|#define OS_FREE_BSD&t;0x00800000 /* FreeBSD Unix&t;&t;&t;*/
DECL|macro|OS_LINUX
mdefine_line|#define OS_LINUX&t;0x01000000 /* Linux&t;&t;&t;&t;*/
DECL|macro|OS_DGUX_UNIX
mdefine_line|#define OS_DGUX_UNIX&t;0x02000000 /* Data General Unix&t;&t;&t;*/
DECL|macro|OS_SINIX_N
mdefine_line|#define OS_SINIX_N      0x04000000 /* SNI SINIX-N&t;&t;&t;*/
DECL|macro|OS_PLAN9
mdefine_line|#define OS_PLAN9&t;0x08000000 /* ATT Plan 9&t;&t;&t;*/
DECL|macro|OS_TSX
mdefine_line|#define OS_TSX&t;&t;0x10000000 /* SNH TSX-32&t;&t;&t;*/
DECL|macro|OS_OTHER
mdefine_line|#define OS_OTHER        0x80000000 /* Other&t;&t;&t;&t;*/
multiline_comment|/* Capabilities - sigWORD dsCapabilities;        FLAG BITS */
multiline_comment|/* ------------------------------------------------------------------ */
DECL|macro|CAP_RAID0
mdefine_line|#define CAP_RAID0       0x0001  /* RAID-0 */
DECL|macro|CAP_RAID1
mdefine_line|#define CAP_RAID1       0x0002  /* RAID-1 */
DECL|macro|CAP_RAID3
mdefine_line|#define CAP_RAID3       0x0004  /* RAID-3 */
DECL|macro|CAP_RAID5
mdefine_line|#define CAP_RAID5       0x0008  /* RAID-5 */
DECL|macro|CAP_SPAN
mdefine_line|#define CAP_SPAN        0x0010  /* Spanning */
DECL|macro|CAP_PASS
mdefine_line|#define CAP_PASS        0x0020  /* Provides passthrough */
DECL|macro|CAP_OVERLAP
mdefine_line|#define CAP_OVERLAP     0x0040  /* Passthrough supports overlapped commands */
DECL|macro|CAP_ASPI
mdefine_line|#define CAP_ASPI        0x0080  /* Supports ASPI Command Requests */
DECL|macro|CAP_ABOVE16MB
mdefine_line|#define CAP_ABOVE16MB   0x0100  /* ISA Driver supports greater than 16MB */
DECL|macro|CAP_EXTEND
mdefine_line|#define CAP_EXTEND      0x8000  /* Extended info appears after description */
macro_line|#ifdef SNI_MIPS
DECL|macro|CAP_CACHEMODE
mdefine_line|#define CAP_CACHEMODE   0x1000  /* dpt_force_cache is set in driver */
macro_line|#endif
multiline_comment|/* Devices Supported - sigWORD dsDeviceSupp;    FLAG BITS */
multiline_comment|/* ------------------------------------------------------------------ */
DECL|macro|DEV_DASD
mdefine_line|#define DEV_DASD        0x0001  /* DASD (hard drives) */
DECL|macro|DEV_TAPE
mdefine_line|#define DEV_TAPE        0x0002  /* Tape drives */
DECL|macro|DEV_PRINTER
mdefine_line|#define DEV_PRINTER     0x0004  /* Printers */
DECL|macro|DEV_PROC
mdefine_line|#define DEV_PROC        0x0008  /* Processors */
DECL|macro|DEV_WORM
mdefine_line|#define DEV_WORM        0x0010  /* WORM drives */
DECL|macro|DEV_CDROM
mdefine_line|#define DEV_CDROM       0x0020  /* CD-ROM drives */
DECL|macro|DEV_SCANNER
mdefine_line|#define DEV_SCANNER     0x0040  /* Scanners */
DECL|macro|DEV_OPTICAL
mdefine_line|#define DEV_OPTICAL     0x0080  /* Optical Drives */
DECL|macro|DEV_JUKEBOX
mdefine_line|#define DEV_JUKEBOX     0x0100  /* Jukebox */
DECL|macro|DEV_COMM
mdefine_line|#define DEV_COMM        0x0200  /* Communications Devices */
DECL|macro|DEV_OTHER
mdefine_line|#define DEV_OTHER       0x0400  /* Other Devices */
DECL|macro|DEV_ALL
mdefine_line|#define DEV_ALL         0xFFFF  /* All SCSI Devices */
multiline_comment|/* Adapters Families Supported - sigWORD dsAdapterSupp; FLAG BITS */
multiline_comment|/* ------------------------------------------------------------------ */
DECL|macro|ADF_2001
mdefine_line|#define ADF_2001        0x0001  /* PM2001           */
DECL|macro|ADF_2012A
mdefine_line|#define ADF_2012A       0x0002  /* PM2012A          */
DECL|macro|ADF_PLUS_ISA
mdefine_line|#define ADF_PLUS_ISA    0x0004  /* PM2011,PM2021    */
DECL|macro|ADF_PLUS_EISA
mdefine_line|#define ADF_PLUS_EISA   0x0008  /* PM2012B,PM2022   */
DECL|macro|ADF_SC3_ISA
mdefine_line|#define ADF_SC3_ISA&t;0x0010  /* PM2021           */
DECL|macro|ADF_SC3_EISA
mdefine_line|#define ADF_SC3_EISA&t;0x0020  /* PM2022,PM2122, etc */
DECL|macro|ADF_SC3_PCI
mdefine_line|#define ADF_SC3_PCI&t;0x0040  /* SmartCache III PCI */
DECL|macro|ADF_SC4_ISA
mdefine_line|#define ADF_SC4_ISA&t;0x0080  /* SmartCache IV ISA */
DECL|macro|ADF_SC4_EISA
mdefine_line|#define ADF_SC4_EISA&t;0x0100  /* SmartCache IV EISA */
DECL|macro|ADF_SC4_PCI
mdefine_line|#define ADF_SC4_PCI&t;0x0200&t;/* SmartCache IV PCI */
DECL|macro|ADF_SC5_PCI
mdefine_line|#define ADF_SC5_PCI&t;0x0400&t;/* Fifth Generation I2O products */
multiline_comment|/*&n; *&t;Combinations of products&n; */
DECL|macro|ADF_ALL_2000
mdefine_line|#define ADF_ALL_2000&t;(ADF_2001|ADF_2012A)
DECL|macro|ADF_ALL_PLUS
mdefine_line|#define ADF_ALL_PLUS&t;(ADF_PLUS_ISA|ADF_PLUS_EISA)
DECL|macro|ADF_ALL_SC3
mdefine_line|#define ADF_ALL_SC3&t;(ADF_SC3_ISA|ADF_SC3_EISA|ADF_SC3_PCI)
DECL|macro|ADF_ALL_SC4
mdefine_line|#define ADF_ALL_SC4&t;(ADF_SC4_ISA|ADF_SC4_EISA|ADF_SC4_PCI)
DECL|macro|ADF_ALL_SC5
mdefine_line|#define ADF_ALL_SC5&t;(ADF_SC5_PCI)
multiline_comment|/* All EATA Cacheing Products */
DECL|macro|ADF_ALL_CACHE
mdefine_line|#define ADF_ALL_CACHE&t;(ADF_ALL_PLUS|ADF_ALL_SC3|ADF_ALL_SC4)
multiline_comment|/* All EATA Bus Mastering Products */
DECL|macro|ADF_ALL_MASTER
mdefine_line|#define ADF_ALL_MASTER&t;(ADF_2012A|ADF_ALL_CACHE)
multiline_comment|/* All EATA Adapter Products */
DECL|macro|ADF_ALL_EATA
mdefine_line|#define ADF_ALL_EATA&t;(ADF_2001|ADF_ALL_MASTER)
DECL|macro|ADF_ALL
mdefine_line|#define ADF_ALL&t;&t;ADF_ALL_EATA
multiline_comment|/* Application - sigWORD dsApplication;         FLAG BITS */
multiline_comment|/* ------------------------------------------------------------------ */
DECL|macro|APP_DPTMGR
mdefine_line|#define APP_DPTMGR      0x0001  /* DPT Storage Manager */
DECL|macro|APP_ENGINE
mdefine_line|#define APP_ENGINE      0x0002  /* DPT Engine */
DECL|macro|APP_SYTOS
mdefine_line|#define APP_SYTOS       0x0004  /* Sytron Sytos Plus */
DECL|macro|APP_CHEYENNE
mdefine_line|#define APP_CHEYENNE    0x0008  /* Cheyenne ARCServe + ARCSolo */
DECL|macro|APP_MSCDEX
mdefine_line|#define APP_MSCDEX      0x0010  /* Microsoft CD-ROM extensions */
DECL|macro|APP_NOVABACK
mdefine_line|#define APP_NOVABACK    0x0020  /* NovaStor Novaback */
DECL|macro|APP_AIM
mdefine_line|#define APP_AIM         0x0040  /* Archive Information Manager */
multiline_comment|/* Requirements - sigBYTE dsRequirements;         FLAG BITS             */
multiline_comment|/* ------------------------------------------------------------------   */
DECL|macro|REQ_SMARTROM
mdefine_line|#define REQ_SMARTROM    0x01    /* Requires SmartROM to be present      */
DECL|macro|REQ_DPTDDL
mdefine_line|#define REQ_DPTDDL      0x02    /* Requires DPTDDL.SYS to be loaded     */
DECL|macro|REQ_HBA_DRIVER
mdefine_line|#define REQ_HBA_DRIVER  0x04    /* Requires an HBA driver to be loaded  */
DECL|macro|REQ_ASPI_TRAN
mdefine_line|#define REQ_ASPI_TRAN   0x08    /* Requires an ASPI Transport Modules   */
DECL|macro|REQ_ENGINE
mdefine_line|#define REQ_ENGINE      0x10    /* Requires a DPT Engine to be loaded   */
DECL|macro|REQ_COMM_ENG
mdefine_line|#define REQ_COMM_ENG    0x20    /* Requires a DPT Communications Engine */
multiline_comment|/*&n; * You may adjust dsDescription_size with an override to a value less than&n; * 50 so that the structure allocates less real space.&n; */
macro_line|#if (!defined(dsDescription_size))
DECL|macro|dsDescription_size
macro_line|# define dsDescription_size 50
macro_line|#endif
DECL|struct|dpt_sig
r_typedef
r_struct
id|dpt_sig
(brace
DECL|member|dsSignature
r_char
id|dsSignature
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* ALWAYS &quot;dPtSiG&quot; */
DECL|member|dsSigVersion
id|sigBYTE
id|dsSigVersion
suffix:semicolon
multiline_comment|/* signature version (currently 1) */
DECL|member|dsProcessorFamily
id|sigBYTE
id|dsProcessorFamily
suffix:semicolon
multiline_comment|/* what type of processor */
DECL|member|dsProcessor
id|sigBYTE
id|dsProcessor
suffix:semicolon
multiline_comment|/* precise processor */
DECL|member|dsFiletype
id|sigBYTE
id|dsFiletype
suffix:semicolon
multiline_comment|/* type of file */
DECL|member|dsFiletypeFlags
id|sigBYTE
id|dsFiletypeFlags
suffix:semicolon
multiline_comment|/* flags to specify load type, etc. */
DECL|member|dsOEM
id|sigBYTE
id|dsOEM
suffix:semicolon
multiline_comment|/* OEM file was created for */
DECL|member|dsOS
id|sigLONG
id|dsOS
suffix:semicolon
multiline_comment|/* which Operating systems */
DECL|member|dsCapabilities
id|sigWORD
id|dsCapabilities
suffix:semicolon
multiline_comment|/* RAID levels, etc. */
DECL|member|dsDeviceSupp
id|sigWORD
id|dsDeviceSupp
suffix:semicolon
multiline_comment|/* Types of SCSI devices supported */
DECL|member|dsAdapterSupp
id|sigWORD
id|dsAdapterSupp
suffix:semicolon
multiline_comment|/* DPT adapter families supported */
DECL|member|dsApplication
id|sigWORD
id|dsApplication
suffix:semicolon
multiline_comment|/* applications file is for */
DECL|member|dsRequirements
id|sigBYTE
id|dsRequirements
suffix:semicolon
multiline_comment|/* Other driver dependencies */
DECL|member|dsVersion
id|sigBYTE
id|dsVersion
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|dsRevision
id|sigBYTE
id|dsRevision
suffix:semicolon
multiline_comment|/* &squot;J&squot; */
DECL|member|dsSubRevision
id|sigBYTE
id|dsSubRevision
suffix:semicolon
multiline_comment|/* &squot;9&squot;   &squot; &squot; if N/A */
DECL|member|dsMonth
id|sigBYTE
id|dsMonth
suffix:semicolon
multiline_comment|/* creation month */
DECL|member|dsDay
id|sigBYTE
id|dsDay
suffix:semicolon
multiline_comment|/* creation day */
DECL|member|dsYear
id|sigBYTE
id|dsYear
suffix:semicolon
multiline_comment|/* creation year since 1980 (1993=13) */
multiline_comment|/* description (NULL terminated) */
DECL|member|dsDescription
r_char
id|dsDescription
(braket
id|dsDescription_size
)braket
suffix:semicolon
DECL|typedef|dpt_sig_S
)brace
id|dpt_sig_S
suffix:semicolon
multiline_comment|/* 32 bytes minimum - with no description.  Put NULL at description[0] */
multiline_comment|/* 81 bytes maximum - with 49 character description plus NULL. */
multiline_comment|/* This line added at Roycroft&squot;s request */
multiline_comment|/* Microsoft&squot;s NT compiler gets confused if you do a pack and don&squot;t */
multiline_comment|/* restore it. */
macro_line|#ifndef NO_UNPACK
macro_line|#if defined (_DPT_AIX)
macro_line|#pragma options align=reset
macro_line|#elif defined (UNPACK_FOUR)
macro_line|#pragma pack(4)
macro_line|#else
macro_line|#pragma pack()
macro_line|#endif  /* aix */
macro_line|#endif
multiline_comment|/* For the Macintosh */
macro_line|#if STRUCTALIGNMENTSUPPORTED
macro_line|#pragma options align=reset
macro_line|#endif
macro_line|#endif
eof
