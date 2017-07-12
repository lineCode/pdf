#ifndef _PDF_COMPILERCOMPAT_H
#define _PDF_COMPILERCOMPAT_H

//
// *** THIS HEADER IS INCLUDED BY PdfDefines.h ***
// *** DO NOT INCLUDE DIRECTLY ***
#ifndef _PDF_DEFINES_H_
#error Please include PdfDefines.h instead
#endif

#include "podofo_config.h"

#ifndef PODOFO_COMPILE_RC

// Silence some annoying warnings from Visual Studio
#ifdef _MSC_VER
#if _MSC_VER <= 1200 // Visual Studio 6
#pragma warning(disable: 4786)
#pragma warning(disable: 4251)
#elif _MSC_VER <= 1400 // Visual Studio 2005
#pragma warning(disable: 4251)
#pragma warning(disable: 4275)
#endif // _MSC_VER
#endif // _MSC_VER

// Make sure that DEBUG is defined
// for debug builds on Windows
// as Visual Studio defines only _DEBUG
#ifdef _DEBUG
#ifndef DEBUG
#define DEBUG 1
#endif // DEBUG
#endif // _DEBUG


#if defined(__BORLANDC__) || defined( __TURBOC__)
#  include <stddef.h>
#else
#  include <cstddef>
#endif

#if defined(TEST_BIG)
#  define PODOFO_IS_BIG_ENDIAN
#else
#  define PODOFO_IS_LITTLE_ENDIAN
#endif

#if PODOFO_HAVE_STDINT_H
#include <stdint.h>
#endif

#if PODOFO_HAVE_BASETSD_H
#include <BaseTsd.h>
#endif

#if PODOFO_HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#if PODOFO_HAVE_MEM_H
#include <mem.h>
#endif

#if PODOFO_HAVE_CTYPE_H
#include <ctype.h>
#endif

#if PODOFO_HAVE_STRINGS_H
#include <strings.h>
#endif

// alloca() is defined only in <cstdlib> on Mac OS X,
// only in <malloc.h> on win32, and in both on Linux.
#if defined(_WIN32)
#include <malloc.h>
#endif

// Disable usage of min() and max() macros
#if defined(_WIN32) && !defined(__MINGW32__) && !defined(NOMINMAX)
#define NOMINMAX
#endif

// Integer types - fixed size types guaranteed to work anywhere
// because we detect the right underlying type name to use with
// CMake. Use typedefs rather than macros for saner error messages
// etc.
#include <cstdint>

namespace PoDoFo {
    typedef std::int8_t pdf_int8;
    typedef std::int16_t pdf_int16;
    typedef std::int32_t pdf_int32;
    typedef std::int64_t pdf_int64;
    typedef std::uint8_t pdf_uint8;
    typedef std::uint16_t pdf_uint16;
    typedef std::uint32_t pdf_uint32;
    typedef std::uint64_t pdf_uint64;
};


/*
 * Some elderly compilers, notably VC6, don't support LL literals.
 * In those cases we can use the oversized literal without any suffix.
 */
#if defined(_MSC_VER)  &&  _MSC_VER <= 1200 // Visual Studio 6
#  define PODOFO_LL_LITERAL(x) x
#  define PODOFO_ULL_LITERAL(x) x
#else
#if defined(PODOFO_COMPILER_LACKS_LL_LITERALS)
#  define PODOFO_LL_LITERAL(x) x
#  define PODOFO_ULL_LITERAL(x) x
#else
#  define PODOFO_LL_LITERAL(x) x##LL
#  define PODOFO_ULL_LITERAL(x) x##ULL
#endif
#endif

#if defined(_MSC_VER)  &&  _MSC_VER <= 1200 // Visual Studio 6
#   define PODOFO_MIN(_a, _b) ((_a) < (_b) ? (_a) : (_b))
#else
#   define PODOFO_MIN(_a, _b) (std::min((_a), (_b)))
#endif

// pdf_long is defined as ptrdiff_t . It's a pointer-sized signed quantity
// used throughout the code for a variety of purposes.
//
// pdf_long is DEPRECATED. Please use one of the explicitly sized types
// instead, or define a typedef that meaningfully describes what it's for.
// Good choices in many cases include size_t (string and buffer sizes) and
// ptrdiff_t (offsets and pointer arithmetic).
//
// pdf_long should not be used in new code.
//
namespace PoDoFo {
    typedef ptrdiff_t pdf_long;
};


// Different compilers use different format specifiers for 64-bit integers
// (yay!).  Use these macros with C's automatic string concatenation to handle
// that ghastly quirk.
//
// for example:   printf("Value of signed 64-bit integer: %"PDF_FORMAT_INT64" (more blah)", 128LL)
//
#if defined(_MSC_VER)
#  define PDF_FORMAT_INT64 "I64d"
#  define PDF_FORMAT_UINT64 "I64u"
#elif defined(SZ_INT64) && defined(SZ_LONG) && SZ_INT64 == SZ_LONG
#  define PDF_FORMAT_INT64 "ld"
#  define PDF_FORMAT_UINT64 "lu"
#else
#  define PDF_FORMAT_INT64 "lld"
#  define PDF_FORMAT_UINT64 "llu"
#endif



// Different compilers express __FUNC__ in different ways and with different
// capabilities. Try to find the best option.
//
// Note that __LINE__ and __FILE__ are *NOT* included.
// Further note that you can't use compile-time string concatenation on __FUNC__ and friends
// on many compilers as they're defined to behave as if they were a:
//    static const char* __func__ = 'nameoffunction';
// just after the opening brace of each function.
//
#if (defined(_MSC_VER)  &&  _MSC_VER <= 1200)
#  define PODOFO__FUNCTION__ __FUNCTION__
#elif defined(__BORLANDC__) || defined(__TURBOC__)
#  define PODOFO__FUNCTION__ __FUNC__
#elif defined(__GNUC__)
#  define PODOFO__FUNCTION__ __PRETTY_FUNCTION__
#else
#  define PODOFO__FUNCTION__ __FUNCTION__
#endif

#if defined(_WIN32)

// Undefined stuff which windows does define that breaks the build
// e.g. GetObject is defined to either GetObjectA or GetObjectW
#ifdef GetObject
#undef GetObject
#endif // GetObject

#ifdef CreateFont
#undef CreateFont
#endif // CreateFont

#ifdef DrawText
#undef DrawText
#endif // DrawText

#endif // defined(_WIN32)

// Visual C++ 2015 (_MSC_VER 1900) still uses __cplusplus = 199711 so, we need both tests
// this shrinks enum types from sizeof(int) to sizeof(char) which creates significant
// space savings on PdfObject / PdfVariant
#if (defined(_MSC_VER) && _MSC_VER < 1900) || (!defined(_MSC_VER) &&  __cplusplus < 201103)
#define PODOFO_ENUM_UINT8
#else
#define PODOFO_ENUM_UINT8	: uint8_t
#endif


/**
 * \page PoDoFo PdfCompilerCompat Header
 *
 * <b>PdfCompilerCompat.h</b> gathers up nastyness required for various
 * compiler compatibility into a central place. All compiler-specific defines,
 * wrappers, and the like should be included here and (if necessary) in
 * PdfCompilerCompat.cpp if they must be visible to public users of the library.
 *
 * If the nasty platform and compiler specific hacks can be kept to PoDoFo's
 * build and need not be visible to users of the library, put them in
 * PdfCompilerCompatPrivate.{cpp,h} instead.
 *
 * Please NEVER use symbols from this header or the PoDoFo::compat namespace in
 * a "using" directive. Always explicitly reference names so it's clear that
 * you're pulling them from the compat cruft.
 */

#endif // !PODOFO_COMPILE_RC

#endif
