multiline_comment|/*&n; * drivers/video/clgenfb.h - Cirrus Logic chipset constants&n; *&n; * Copyright 1999 Jeff Garzik &lt;jgarzik@mandrakesoft.com&gt;&n; *&n; * Original clgenfb author:  Frank Neumann&n; *&n; * Based on retz3fb.c and clgen.c:&n; *      Copyright (C) 1997 Jes Sorensen&n; *      Copyright (C) 1996 Frank Neumann&n; *&n; ***************************************************************&n; *&n; * Format this code with GNU indent &squot;-kr -i8 -pcs&squot; options.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; *&n; */
macro_line|#ifndef __CLGENFB_H__
DECL|macro|__CLGENFB_H__
mdefine_line|#define __CLGENFB_H__
multiline_comment|/* OLD COMMENT: definitions for Piccolo/SD64 VGA controller chip   */
multiline_comment|/* OLD COMMENT: these definitions might most of the time also work */
multiline_comment|/* OLD COMMENT: for other CL-GD542x/543x based boards..            */
multiline_comment|/*** External/General Registers ***/
DECL|macro|CL_POS102
mdefine_line|#define CL_POS102&t;0x102  &t;/* POS102 register */
DECL|macro|CL_VSSM
mdefine_line|#define CL_VSSM&t;&t;0x46e8 &t;/* Adapter Sleep */
DECL|macro|CL_VSSM2
mdefine_line|#define CL_VSSM2&t;0x3c3&t;/* Motherboard Sleep */
multiline_comment|/*** VGA Sequencer Registers ***/
DECL|macro|CL_SEQR0
mdefine_line|#define CL_SEQR0&t;0x0&t;/* Reset */
multiline_comment|/* the following are from the &quot;extension registers&quot; group */
DECL|macro|CL_SEQR6
mdefine_line|#define CL_SEQR6&t;0x6&t;/* Unlock ALL Extensions */
DECL|macro|CL_SEQR7
mdefine_line|#define CL_SEQR7&t;0x7&t;/* Extended Sequencer Mode */
DECL|macro|CL_SEQR8
mdefine_line|#define CL_SEQR8&t;0x8&t;/* EEPROM Control */
DECL|macro|CL_SEQR9
mdefine_line|#define CL_SEQR9&t;0x9&t;/* Scratch Pad 0 (do not access!) */
DECL|macro|CL_SEQRA
mdefine_line|#define CL_SEQRA&t;0xa&t;/* Scratch Pad 1 (do not access!) */
DECL|macro|CL_SEQRB
mdefine_line|#define CL_SEQRB&t;0xb&t;/* VCLK0 Numerator */
DECL|macro|CL_SEQRC
mdefine_line|#define CL_SEQRC&t;0xc&t;/* VCLK1 Numerator */
DECL|macro|CL_SEQRD
mdefine_line|#define CL_SEQRD&t;0xd&t;/* VCLK2 Numerator */
DECL|macro|CL_SEQRE
mdefine_line|#define CL_SEQRE&t;0xe&t;/* VCLK3 Numerator */
DECL|macro|CL_SEQRF
mdefine_line|#define CL_SEQRF&t;0xf&t;/* DRAM Control */
DECL|macro|CL_SEQR10
mdefine_line|#define CL_SEQR10&t;0x10&t;/* Graphics Cursor X Position */
DECL|macro|CL_SEQR11
mdefine_line|#define CL_SEQR11&t;0x11&t;/* Graphics Cursor Y Position */
DECL|macro|CL_SEQR12
mdefine_line|#define CL_SEQR12&t;0x12&t;/* Graphics Cursor Attributes */
DECL|macro|CL_SEQR13
mdefine_line|#define CL_SEQR13&t;0x13&t;/* Graphics Cursor Pattern Address Offset */
DECL|macro|CL_SEQR14
mdefine_line|#define CL_SEQR14&t;0x14&t;/* Scratch Pad 2 (CL-GD5426/&squot;28 Only) (do not access!) */
DECL|macro|CL_SEQR15
mdefine_line|#define CL_SEQR15&t;0x15&t;/* Scratch Pad 3 (CL-GD5426/&squot;28 Only) (do not access!) */
DECL|macro|CL_SEQR16
mdefine_line|#define CL_SEQR16&t;0x16&t;/* Performance Tuning (CL-GD5424/&squot;26/&squot;28 Only) */
DECL|macro|CL_SEQR17
mdefine_line|#define CL_SEQR17&t;0x17&t;/* Configuration ReadBack and Extended Control (CL-GF5428 Only) */
DECL|macro|CL_SEQR18
mdefine_line|#define CL_SEQR18&t;0x18&t;/* Signature Generator Control (Not CL-GD5420) */
DECL|macro|CL_SEQR19
mdefine_line|#define CL_SEQR19&t;0x19&t;/* Signature Generator Result Low Byte (Not CL-GD5420) */
DECL|macro|CL_SEQR1A
mdefine_line|#define CL_SEQR1A&t;0x1a&t;/* Signature Generator Result High Byte (Not CL-GD5420) */
DECL|macro|CL_SEQR1B
mdefine_line|#define CL_SEQR1B&t;0x1b&t;/* VCLK0 Denominator and Post-Scalar Value */
DECL|macro|CL_SEQR1C
mdefine_line|#define CL_SEQR1C&t;0x1c&t;/* VCLK1 Denominator and Post-Scalar Value */
DECL|macro|CL_SEQR1D
mdefine_line|#define CL_SEQR1D&t;0x1d&t;/* VCLK2 Denominator and Post-Scalar Value */
DECL|macro|CL_SEQR1E
mdefine_line|#define CL_SEQR1E&t;0x1e&t;/* VCLK3 Denominator and Post-Scalar Value */
DECL|macro|CL_SEQR1F
mdefine_line|#define CL_SEQR1F&t;0x1f&t;/* BIOS ROM write enable and MCLK Select */
multiline_comment|/*** CRT Controller Registers ***/
DECL|macro|CL_CRT22
mdefine_line|#define CL_CRT22&t;0x22&t;/* Graphics Data Latches ReadBack */
DECL|macro|CL_CRT24
mdefine_line|#define CL_CRT24&t;0x24&t;/* Attribute Controller Toggle ReadBack */
DECL|macro|CL_CRT26
mdefine_line|#define CL_CRT26&t;0x26&t;/* Attribute Controller Index ReadBack */
multiline_comment|/* the following are from the &quot;extension registers&quot; group */
DECL|macro|CL_CRT19
mdefine_line|#define CL_CRT19&t;0x19&t;/* Interlace End */
DECL|macro|CL_CRT1A
mdefine_line|#define CL_CRT1A&t;0x1a&t;/* Interlace Control */
DECL|macro|CL_CRT1B
mdefine_line|#define CL_CRT1B&t;0x1b&t;/* Extended Display Controls */
DECL|macro|CL_CRT1C
mdefine_line|#define CL_CRT1C&t;0x1c&t;/* Sync adjust and genlock register */
DECL|macro|CL_CRT1D
mdefine_line|#define CL_CRT1D&t;0x1d&t;/* Overlay Extended Control register */
DECL|macro|CL_CRT25
mdefine_line|#define CL_CRT25&t;0x25&t;/* Part Status Register */
DECL|macro|CL_CRT27
mdefine_line|#define CL_CRT27&t;0x27&t;/* ID Register */
DECL|macro|CL_CRT51
mdefine_line|#define CL_CRT51&t;0x51&t;/* P4 disable &quot;flicker fixer&quot; */
multiline_comment|/*** Graphics Controller Registers ***/
multiline_comment|/* the following are from the &quot;extension registers&quot; group */
DECL|macro|CL_GR9
mdefine_line|#define CL_GR9&t;&t;0x9&t;/* Offset Register 0 */
DECL|macro|CL_GRA
mdefine_line|#define CL_GRA&t;&t;0xa&t;/* Offset Register 1 */
DECL|macro|CL_GRB
mdefine_line|#define CL_GRB&t;&t;0xb&t;/* Graphics Controller Mode Extensions */
DECL|macro|CL_GRC
mdefine_line|#define CL_GRC&t;&t;0xc&t;/* Color Key (CL-GD5424/&squot;26/&squot;28 Only) */
DECL|macro|CL_GRD
mdefine_line|#define CL_GRD&t;&t;0xd&t;/* Color Key Mask (CL-GD5424/&squot;26/&squot;28 Only) */
DECL|macro|CL_GRE
mdefine_line|#define CL_GRE&t;&t;0xe&t;/* Miscellaneous Control (Cl-GD5428 Only) */
DECL|macro|CL_GRF
mdefine_line|#define CL_GRF&t;&t;0xf&t;/* Display Compression Control register */
DECL|macro|CL_GR10
mdefine_line|#define CL_GR10&t;&t;0x10&t;/* 16-bit Pixel BG Color High Byte (Not CL-GD5420) */
DECL|macro|CL_GR11
mdefine_line|#define CL_GR11&t;&t;0x11&t;/* 16-bit Pixel FG Color High Byte (Not CL-GD5420) */
DECL|macro|CL_GR12
mdefine_line|#define CL_GR12&t;&t;0x12&t;/* Background Color Byte 2 Register */
DECL|macro|CL_GR13
mdefine_line|#define CL_GR13&t;&t;0x13&t;/* Foreground Color Byte 2 Register */
DECL|macro|CL_GR14
mdefine_line|#define CL_GR14&t;&t;0x14&t;/* Background Color Byte 3 Register */
DECL|macro|CL_GR15
mdefine_line|#define CL_GR15&t;&t;0x15&t;/* Foreground Color Byte 3 Register */
multiline_comment|/* the following are CL-GD5426/&squot;28 specific blitter registers */
DECL|macro|CL_GR20
mdefine_line|#define CL_GR20&t;&t;0x20&t;/* BLT Width Low */
DECL|macro|CL_GR21
mdefine_line|#define CL_GR21&t;&t;0x21&t;/* BLT Width High */
DECL|macro|CL_GR22
mdefine_line|#define CL_GR22&t;&t;0x22&t;/* BLT Height Low */
DECL|macro|CL_GR23
mdefine_line|#define CL_GR23&t;&t;0x23&t;/* BLT Height High */
DECL|macro|CL_GR24
mdefine_line|#define CL_GR24&t;&t;0x24&t;/* BLT Destination Pitch Low */
DECL|macro|CL_GR25
mdefine_line|#define CL_GR25&t;&t;0x25&t;/* BLT Destination Pitch High */
DECL|macro|CL_GR26
mdefine_line|#define CL_GR26&t;&t;0x26&t;/* BLT Source Pitch Low */
DECL|macro|CL_GR27
mdefine_line|#define CL_GR27&t;&t;0x27&t;/* BLT Source Pitch High */
DECL|macro|CL_GR28
mdefine_line|#define CL_GR28&t;&t;0x28&t;/* BLT Destination Start Low */
DECL|macro|CL_GR29
mdefine_line|#define CL_GR29&t;&t;0x29&t;/* BLT Destination Start Mid */
DECL|macro|CL_GR2A
mdefine_line|#define CL_GR2A&t;&t;0x2a&t;/* BLT Destination Start High */
DECL|macro|CL_GR2C
mdefine_line|#define CL_GR2C&t;&t;0x2c&t;/* BLT Source Start Low */
DECL|macro|CL_GR2D
mdefine_line|#define CL_GR2D&t;&t;0x2d&t;/* BLT Source Start Mid */
DECL|macro|CL_GR2E
mdefine_line|#define CL_GR2E&t;&t;0x2e&t;/* BLT Source Start High */
DECL|macro|CL_GR2F
mdefine_line|#define CL_GR2F&t;&t;0x2f&t;/* Picasso IV Blitter compat mode..? */
DECL|macro|CL_GR30
mdefine_line|#define CL_GR30&t;&t;0x30&t;/* BLT Mode */
DECL|macro|CL_GR31
mdefine_line|#define CL_GR31&t;&t;0x31&t;/* BLT Start/Status */
DECL|macro|CL_GR32
mdefine_line|#define CL_GR32&t;&t;0x32&t;/* BLT Raster Operation */
DECL|macro|CL_GR33
mdefine_line|#define CL_GR33&t;&t;0x33&t;/* another P4 &quot;compat&quot; register.. */
DECL|macro|CL_GR34
mdefine_line|#define CL_GR34&t;&t;0x34&t;/* Transparent Color Select Low */
DECL|macro|CL_GR35
mdefine_line|#define CL_GR35&t;&t;0x35&t;/* Transparent Color Select High */
DECL|macro|CL_GR38
mdefine_line|#define CL_GR38&t;&t;0x38&t;/* Source Transparent Color Mask Low */
DECL|macro|CL_GR39
mdefine_line|#define CL_GR39&t;&t;0x39&t;/* Source Transparent Color Mask High */
multiline_comment|/*** Attribute Controller Registers ***/
DECL|macro|CL_AR33
mdefine_line|#define CL_AR33&t;&t;0x33&t;/* The &quot;real&quot; Pixel Panning register (?) */
DECL|macro|CL_AR34
mdefine_line|#define CL_AR34&t;&t;0x34&t;/* TEST */
macro_line|#endif /* __CLGENFB_H__ */
eof
