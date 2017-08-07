# PDF
<http://www.xnetsystems.de/><br/>
Version: 0.9.5

<http://podofo.sourceforge.net/><br/>
Version: 0.9.5

```sh
mv ${archive}/podofo_config.h.in src/
mv ${archive}/src/{base,doc,podofo.h,podofo-base.h} src/podofo/
rm src/podofo/doc/PdfTTFWriter.{h,cpp}
find src/podofo -type f -exec sed -i 's/std::auto_ptr/std::unique_ptr/g' '{}' ';'
```

```diff
diff --git i/src/podofo/base/PdfFiltersPrivate.cpp w/src/podofo/base/PdfFiltersPrivate.cpp
index 56b6880..4ac4404 100644
--- i/src/podofo/base/PdfFiltersPrivate.cpp
+++ w/src/podofo/base/PdfFiltersPrivate.cpp
@@ -852,7 +852,6 @@ void PdfLZWFilter::InitTable()
 /*
  * Handlers for errors inside the JPeg library
  */
-extern "C" {
 void JPegErrorExit(j_common_ptr cinfo)
 {
 #if 1
@@ -869,7 +868,6 @@ void JPegErrorOutput(j_common_ptr, int)
 {
 }

-};

 /*
  * The actual filter implementation
diff --git i/src/podofo/base/PdfFiltersPrivate.h w/src/podofo/base/PdfFiltersPrivate.h
index 9a7c6bd..96f368f 100644
--- i/src/podofo/base/PdfFiltersPrivate.h
+++ w/src/podofo/base/PdfFiltersPrivate.h
@@ -719,11 +719,9 @@ EPdfFilter PdfLZWFilter::GetType() const

 void PODOFO_API jpeg_memory_src (j_decompress_ptr cinfo, const JOCTET * buffer, size_t bufsize);

-extern "C" {
 void JPegErrorExit(j_common_ptr cinfo);

 void JPegErrorOutput(j_common_ptr, int);
-};

 /** The DCT filter can decoded JPEG compressed data.
  *
diff --git i/src/podofo/doc/PdfPainter.cpp w/src/podofo/doc/PdfPainter.cpp
index 0f51b2d..5c79068 100644
--- i/src/podofo/doc/PdfPainter.cpp
+++ w/src/podofo/doc/PdfPainter.cpp
@@ -134,7 +134,7 @@ PdfPainter::PdfPainter()
     currentTextRenderingMode = ePdfTextRenderingMode_Fill;
 }

-PdfPainter::~PdfPainter()
+PdfPainter::~PdfPainter() noexcept(false)
 {
        // Throwing exceptions in C++ destructors is not allowed.
        // Just log the error.
diff --git i/src/podofo/doc/PdfPainter.h w/src/podofo/doc/PdfPainter.h
index 6b99dc1..c33fcb0 100644
--- i/src/podofo/doc/PdfPainter.h
+++ w/src/podofo/doc/PdfPainter.h
@@ -84,7 +84,7 @@ class PODOFO_DOC_API PdfPainter {
      */
     PdfPainter();

-    virtual ~PdfPainter();
+    virtual ~PdfPainter() noexcept(false);

     /** Set the page on which the painter should draw.
      *  The painter will draw of course on the pages
```
