        ;;  g12.s
        ;;  
        ;;  g12
        ;; 
        ;;  notes: see libgpx documentation for format details
        ;;  
        ;;  MIT License (see: LICENSE)
        ;;  copyright(c) 2021 tomaz stih
        ;;  
        ;;  21.01.2024   tstih
        .module g12

        .globl _g12

        .area _CODE
_g12::
        ;; glyph header
        .db 160                         ; glyph magic 101xxxxx
        .db 37                          ; width
        .db 30                          ; height
        .db 255                         ; reserved
        ;; glyph data
        .db 0xFF, 0x0C, 0x06, 0x12, 0x01, 0xFF, 0x0D, 0x04
        .db 0x14, 0x04, 0x09, 0x04, 0x04, 0x06, 0x0A, 0x04
        .db 0x09, 0x04, 0x03, 0x08, 0x09, 0x04, 0x09, 0x04
        .db 0x03, 0x08, 0x09, 0x04, 0x09, 0x04, 0x03, 0x08
        .db 0x09, 0x04, 0x09, 0x04, 0x03, 0x08, 0x09, 0x04
        .db 0x09, 0x04, 0x03, 0x08, 0x09, 0x04, 0x09, 0x04
        .db 0x03, 0x08, 0x09, 0x04, 0x09, 0x04, 0x03, 0x08
        .db 0x09, 0x04, 0x09, 0x0F, 0x09, 0x04, 0x09, 0x0F
        .db 0x09, 0x04, 0x09, 0x0F, 0x09, 0x04, 0x09, 0x0F
        .db 0x09, 0x04, 0x09, 0x0E, 0x0A, 0x04, 0x09, 0x04
        .db 0x14, 0x04, 0x09, 0x04, 0x14, 0x04, 0x09, 0x04
        .db 0x04, 0x10, 0x04, 0x09, 0x04, 0x03, 0x11, 0x04
        .db 0x09, 0x04, 0x03, 0x11, 0x04, 0x09, 0x04, 0x03
        .db 0x08, 0x09, 0x04, 0x09, 0x04, 0x03, 0x08, 0x09
        .db 0x04, 0x09, 0x04, 0x03, 0x08, 0x09, 0x04, 0x09
        .db 0x04, 0x03, 0x08, 0x09, 0x04, 0x09, 0x04, 0x03
        .db 0x08, 0x09, 0x04, 0x09, 0x04, 0x03, 0x08, 0x09
        .db 0x04, 0x09, 0x04, 0x03, 0x08, 0x09, 0x04, 0x09
        .db 0x04, 0x04, 0x06, 0x0A, 0x04, 0x09, 0x04, 0x14
        .db 0x05, 0x07, 0x06, 0x12, 0x01
