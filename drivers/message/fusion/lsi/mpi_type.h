multiline_comment|/*&n; *  Copyright (c) 2000-2002 LSI Logic Corporation.&n; *&n; *&n; *           Name:  MPI_TYPE.H&n; *          Title:  MPI Basic type definitions&n; *  Creation Date:  June 6, 2000&n; *&n; *    MPI Version:  01.02.01&n; *&n; *  Version History&n; *  ---------------&n; *&n; *  Date      Version   Description&n; *  --------  --------  ------------------------------------------------------&n; *  05-08-00  00.10.01  Original release for 0.10 spec dated 4/26/2000.&n; *  06-06-00  01.00.01  Update version number for 1.0 release.&n; *  11-02-00  01.01.01  Original release for post 1.0 work&n; *  02-20-01  01.01.02  Added define and ifdef for MPI_POINTER.&n; *  08-08-01  01.02.01  Original release for v1.2 work.&n; *  --------------------------------------------------------------------------&n; */
macro_line|#ifndef MPI_TYPE_H
DECL|macro|MPI_TYPE_H
mdefine_line|#define MPI_TYPE_H
multiline_comment|/*******************************************************************************&n; * Define MPI_POINTER if it hasn&squot;t already been defined. By default MPI_POINTER&n; * is defined to be a near pointer. MPI_POINTER can be defined as a far pointer&n; * by defining MPI_POINTER as &quot;far *&quot; before this header file is included.&n; */
macro_line|#ifndef MPI_POINTER
DECL|macro|MPI_POINTER
mdefine_line|#define MPI_POINTER     *
macro_line|#endif
multiline_comment|/*****************************************************************************&n;*&n;*               B a s i c    T y p e s&n;*&n;*****************************************************************************/
DECL|typedef|S8
r_typedef
r_int
r_char
id|S8
suffix:semicolon
DECL|typedef|U8
r_typedef
r_int
r_char
id|U8
suffix:semicolon
DECL|typedef|S16
r_typedef
r_int
r_int
id|S16
suffix:semicolon
DECL|typedef|U16
r_typedef
r_int
r_int
id|U16
suffix:semicolon
macro_line|#if defined(unix) || defined(__arm) || defined(ALPHA)
DECL|typedef|S32
r_typedef
r_int
r_int
id|S32
suffix:semicolon
DECL|typedef|U32
r_typedef
r_int
r_int
id|U32
suffix:semicolon
macro_line|#else
DECL|typedef|S32
r_typedef
r_int
r_int
id|S32
suffix:semicolon
DECL|typedef|U32
r_typedef
r_int
r_int
id|U32
suffix:semicolon
macro_line|#endif
DECL|struct|_S64
r_typedef
r_struct
id|_S64
(brace
DECL|member|Low
id|U32
id|Low
suffix:semicolon
DECL|member|High
id|S32
id|High
suffix:semicolon
DECL|typedef|S64
)brace
id|S64
suffix:semicolon
DECL|struct|_U64
r_typedef
r_struct
id|_U64
(brace
DECL|member|Low
id|U32
id|Low
suffix:semicolon
DECL|member|High
id|U32
id|High
suffix:semicolon
DECL|typedef|U64
)brace
id|U64
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/*  Pointers                                                                */
multiline_comment|/****************************************************************************/
DECL|typedef|PS8
r_typedef
id|S8
op_star
id|PS8
suffix:semicolon
DECL|typedef|PU8
r_typedef
id|U8
op_star
id|PU8
suffix:semicolon
DECL|typedef|PS16
r_typedef
id|S16
op_star
id|PS16
suffix:semicolon
DECL|typedef|PU16
r_typedef
id|U16
op_star
id|PU16
suffix:semicolon
DECL|typedef|PS32
r_typedef
id|S32
op_star
id|PS32
suffix:semicolon
DECL|typedef|PU32
r_typedef
id|U32
op_star
id|PU32
suffix:semicolon
DECL|typedef|PS64
r_typedef
id|S64
op_star
id|PS64
suffix:semicolon
DECL|typedef|PU64
r_typedef
id|U64
op_star
id|PU64
suffix:semicolon
macro_line|#endif
eof
