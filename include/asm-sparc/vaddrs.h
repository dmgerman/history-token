multiline_comment|/* $Id: vaddrs.h,v 1.26 2000/08/01 04:53:58 anton Exp $ */
macro_line|#ifndef _SPARC_VADDRS_H
DECL|macro|_SPARC_VADDRS_H
mdefine_line|#define _SPARC_VADDRS_H
macro_line|#include &lt;asm/head.h&gt;
multiline_comment|/*&n; * asm-sparc/vaddrs.h:  Here we define the virtual addresses at&n; *                      which important things will be mapped.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 2000 Anton Blanchard (anton@samba.org)&n; */
DECL|macro|SRMMU_MAXMEM
mdefine_line|#define SRMMU_MAXMEM&t;&t;0x0c000000
DECL|macro|SRMMU_NOCACHE_VADDR
mdefine_line|#define SRMMU_NOCACHE_VADDR&t;0xfc000000&t;/* KERNBASE + SRMMU_MAXMEM */
multiline_comment|/* XXX Make this dynamic based on ram size - Anton */
DECL|macro|SRMMU_NOCACHE_NPAGES
mdefine_line|#define SRMMU_NOCACHE_NPAGES&t;256
DECL|macro|SRMMU_NOCACHE_SIZE
mdefine_line|#define SRMMU_NOCACHE_SIZE&t;(SRMMU_NOCACHE_NPAGES * PAGE_SIZE)
DECL|macro|SRMMU_NOCACHE_END
mdefine_line|#define SRMMU_NOCACHE_END&t;(SRMMU_NOCACHE_VADDR + SRMMU_NOCACHE_SIZE)
DECL|macro|FIX_KMAP_BEGIN
mdefine_line|#define FIX_KMAP_BEGIN&t;&t;0xfc100000
DECL|macro|FIX_KMAP_END
mdefine_line|#define FIX_KMAP_END (FIX_KMAP_BEGIN + ((KM_TYPE_NR*NR_CPUS)-1)*PAGE_SIZE)
DECL|macro|PKMAP_BASE
mdefine_line|#define PKMAP_BASE&t;&t;0xfc140000
DECL|macro|PKMAP_BASE_END
mdefine_line|#define PKMAP_BASE_END&t;&t;(PKMAP_BASE+LAST_PKMAP*PAGE_SIZE)
DECL|macro|SUN4M_IOBASE_VADDR
mdefine_line|#define SUN4M_IOBASE_VADDR&t;0xfd000000 /* Base for mapping pages */
DECL|macro|IOBASE_VADDR
mdefine_line|#define IOBASE_VADDR&t;&t;0xfe000000
DECL|macro|IOBASE_END
mdefine_line|#define IOBASE_END&t;&t;0xfe300000
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;&t;0xfe300000
multiline_comment|/* XXX Alter this when I get around to fixing sun4c - Anton */
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;&t;0xffc00000
multiline_comment|/*&n; * On the sun4/4c we need a place&n; * to reliably map locked down kernel data.  This includes the&n; * task_struct and kernel stack pages of each process plus the&n; * scsi buffers during dvma IO transfers, also the floppy buffers&n; * during pseudo dma which runs with traps off (no faults allowed).&n; * Some quick calculations yield:&n; *       NR_TASKS &lt;512&gt; * (3 * PAGE_SIZE) == 0x600000&n; * Subtract this from 0xc00000 and you get 0x927C0 of vm left&n; * over to map SCSI dvma + floppy pseudo-dma buffers.  So be&n; * careful if you change NR_TASKS or else there won&squot;t be enough&n; * room for it all.&n; */
DECL|macro|SUN4C_LOCK_VADDR
mdefine_line|#define SUN4C_LOCK_VADDR&t;0xff000000
DECL|macro|SUN4C_LOCK_END
mdefine_line|#define SUN4C_LOCK_END&t;&t;0xffc00000
DECL|macro|KADB_DEBUGGER_BEGVM
mdefine_line|#define KADB_DEBUGGER_BEGVM&t;0xffc00000 /* Where kern debugger is in virt-mem */
DECL|macro|KADB_DEBUGGER_ENDVM
mdefine_line|#define KADB_DEBUGGER_ENDVM&t;0xffd00000
DECL|macro|DEBUG_FIRSTVADDR
mdefine_line|#define DEBUG_FIRSTVADDR&t;KADB_DEBUGGER_BEGVM
DECL|macro|DEBUG_LASTVADDR
mdefine_line|#define DEBUG_LASTVADDR&t;&t;KADB_DEBUGGER_ENDVM
DECL|macro|LINUX_OPPROM_BEGVM
mdefine_line|#define LINUX_OPPROM_BEGVM&t;0xffd00000
DECL|macro|LINUX_OPPROM_ENDVM
mdefine_line|#define LINUX_OPPROM_ENDVM&t;0xfff00000
DECL|macro|DVMA_VADDR
mdefine_line|#define DVMA_VADDR&t;&t;0xfff00000 /* Base area of the DVMA on suns */
DECL|macro|DVMA_END
mdefine_line|#define DVMA_END&t;&t;0xfffc0000
macro_line|#endif /* !(_SPARC_VADDRS_H) */
eof
