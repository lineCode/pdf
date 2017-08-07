# PDF
<http://podofo.sourceforge.net/><br/>
Version: 0.9.5

```sh
mv ${archive}/podofo_config.h.in src/
mv ${archive}/src/{base,doc,podofo.h,podofo-base.h} src/podofo/
rm src/podofo/doc/PdfTTFWriter.{h,cpp}
find src/podofo -type f -exec sed -i 's/std::auto_ptr/std::unique_ptr/g' '{}' ';'
```
