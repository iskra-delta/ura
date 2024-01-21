        ;;  g06.s
        ;;  
        ;;  g06
        ;; 
        ;;  notes: see libgpx documentation for format details
        ;;  
        ;;  MIT License (see: LICENSE)
        ;;  copyright(c) 2021 tomaz stih
        ;;  
        ;;  21.01.2024   tstih
        .module g06

        .globl _g06

        .area _CODE
_g06::
        ;; glyph header
        .db 160                         ; glyph magic 101xxxxx
        .db 20                          ; width
        .db 30                          ; height
        .db 255                         ; reserved
        ;; glyph data
        .db 0x01, 0x12, 0x01, 0xFF, 0x14, 0xFF, 0x04, 0x06
        .db 0x0A, 0xFF, 0x03, 0x08, 0x09, 0xFF, 0x03, 0x08
        .db 0x09, 0xFF, 0x03, 0x08, 0x09, 0xFF, 0x03, 0x08
        .db 0x09, 0xFF, 0x03, 0x08, 0x09, 0xFF, 0x03, 0x08
        .db 0x09, 0xFF, 0x03, 0x08, 0x09, 0xFF, 0x03, 0x11
        .db 0xFF, 0x03, 0x11, 0xFF, 0x04, 0x10, 0xFF, 0x14
        .db 0xFF, 0x14, 0xFF, 0x14, 0xFF, 0x04, 0x06, 0x0A
        .db 0xFF, 0x03, 0x08, 0x09, 0xFF, 0x03, 0x08, 0x09
        .db 0xFF, 0x03, 0x08, 0x09, 0xFF, 0x03, 0x08, 0x09
        .db 0xFF, 0x03, 0x08, 0x09, 0xFF, 0x03, 0x08, 0x09
        .db 0xFF, 0x03, 0x08, 0x09, 0xFF, 0x03, 0x08, 0x09
        .db 0xFF, 0x03, 0x08, 0x09, 0xFF, 0x03, 0x08, 0x09
        .db 0xFF, 0x04, 0x06, 0x0A, 0xFF, 0x14, 0x01, 0x12
        .db 0x01
