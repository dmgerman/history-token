multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;mcfcache.h -- ColdFire CPU cache support code&n; *&n; *&t;(C) Copyright 2004, Greg Ungerer &lt;gerg@snapgear.com&gt;&n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;__M68KNOMMU_MCFCACHE_H
DECL|macro|__M68KNOMMU_MCFCACHE_H
mdefine_line|#define&t;__M68KNOMMU_MCFCACHE_H
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; *&t;The different ColdFire families have different cache arrangments.&n; *&t;Everything from a small linstruction only cache, to configurable&n; *&t;data and/or instruction cache, to unified instruction/data, to &n; *&t;harvard style separate instruction and data caches.&n; */
macro_line|#if defined(CONFIG_M5206) || defined(CONFIG_M5206e) || defined(CONFIG_M5272)
multiline_comment|/*&n; *&t;Simple verion 2 core cache. These have instruction cache only,&n; *&t;we just need to invalidate it and enable it.&n; */
dot
id|macro
id|CACHE_ENABLE
id|movel
macro_line|#0x01000000,%d0&t;&t;/* invalidate cache cmd */
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|CACR
multiline_comment|/* do invalidate cache */
DECL|variable|x80000100
id|movel
macro_line|#0x80000100,%d0&t;&t;/* setup cache mask */
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|CACR
multiline_comment|/* enable cache */
dot
id|endm
macro_line|#endif /* CONFIG_M5206 || CONFIG_M5206e || CONFIG_M5272 */
macro_line|#if defined(CONFIG_M527x)
multiline_comment|/*&n; *&t;New version 2 cores have a configurable split cache arrangement.&n; *&t;For now I am just enabling instruction cache - but ultimately I&n; *&t;think a split instruction/data cache would be better.&n; */
dot
id|macro
id|CACHE_ENABLE
id|movel
macro_line|#0x01400000,%d0
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|CACR
multiline_comment|/* invalidate cache */
id|nop
DECL|variable|x0000c000
id|movel
macro_line|#0x0000c000,%d0&t;&t;/* set SDRAM cached only */
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|ACR0
DECL|variable|x00000000
id|movel
macro_line|#0x00000000,%d0&t;&t;/* no other regions cached */
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|ACR1
DECL|variable|x80400100
id|movel
macro_line|#0x80400100,%d0&t;&t;/* configure cache */
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|CACR
multiline_comment|/* enable cache */
id|nop
dot
id|endm
macro_line|#endif /* CONFIG_M527x */
macro_line|#if defined(CONFIG_M528x)
multiline_comment|/*&n; *&t;Cache is totally broken on early 5282 silicon. So far now we&n; *&t;disable its cache all together.&n; */
dot
id|macro
id|CACHE_ENABLE
id|movel
macro_line|#0x01000000,%d0
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|CACR
multiline_comment|/* invalidate cache */
id|nop
DECL|variable|x0000c000
id|movel
macro_line|#0x0000c000,%d0&t;&t;/* set SDRAM cached only */
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|ACR0
DECL|variable|x00000000
id|movel
macro_line|#0x00000000,%d0&t;&t;/* no other regions cached */
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|ACR1
DECL|variable|x00000000
id|movel
macro_line|#0x00000000,%d0&t;&t;/* configure cache */
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|CACR
multiline_comment|/* enable cache */
id|nop
dot
id|endm
macro_line|#endif /* CONFIG_M528x */
macro_line|#if defined(CONFIG_M5249) || defined(CONFIG_M5307)
multiline_comment|/*&n; *&t;The version 3 core cache. Oddly enough the version 2 core 5249&n; *&t;has the same SDRAM and cache setup as the version 3 cores.&n; *&t;This is a single unified instruction/data cache.&n; */
dot
id|macro
id|CACHE_ENABLE
id|movel
macro_line|#0x01000000,%d0&t;&t;/* invalidate whole cache */
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|CACR
id|nop
macro_line|#if defined(DEBUGGER_COMPATIBLE_CACHE) || defined(CONFIG_SECUREEDGEMP3)
DECL|variable|x0000c000
id|movel
macro_line|#0x0000c000,%d0&t;&t;/* set SDRAM cached (write-thru) */
macro_line|#else
id|movel
macro_line|#0x0000c020,%d0&t;&t;/* set SDRAM cached (copyback) */
macro_line|#endif
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|ACR0
DECL|variable|x00000000
id|movel
macro_line|#0x00000000,%d0&t;&t;/* no other regions cached */
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|ACR1
DECL|variable|xa0000200
id|movel
macro_line|#0xa0000200,%d0&t;&t;/* enable cache */
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|CACR
id|nop
dot
id|endm
macro_line|#endif /* CONFIG_M5249 || CONFIG_M5307 */
macro_line|#if defined(CONFIG_M5407)
multiline_comment|/*&n; *&t;Version 4 cores have a true hardvard style separate instruction&n; *&t;and data cache. Invalidate and enable cache, also enable write&n; *&t;buffers and branch accelerator.&n; */
dot
id|macro
id|CACHE_ENABLE
id|movel
macro_line|#0x01040100,%d0&t;&t;/* invalidate whole cache */
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|CACR
id|nop
DECL|variable|x000fc000
id|movel
macro_line|#0x000fc000,%d0&t;&t;/* set SDRAM cached only */
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|ACR0
DECL|variable|x00000000
id|movel
macro_line|#0x00000000,%d0&t;&t;/* no other regions cached */
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|ACR1
DECL|variable|x000fc000
id|movel
macro_line|#0x000fc000,%d0&t;&t;/* set SDRAM cached only */
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|ACR2
DECL|variable|x00000000
id|movel
macro_line|#0x00000000,%d0&t;&t;/* no other regions cached */
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|ACR3
DECL|variable|xb6088400
id|movel
macro_line|#0xb6088400,%d0&t;&t;/* enable caches */
DECL|variable|d0
id|movec
op_mod
id|d0
comma
op_mod
id|CACR
id|nop
dot
id|endm
macro_line|#endif /* CONFIG_M5407 */
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* __M68KNOMMU_MCFCACHE_H */
eof
