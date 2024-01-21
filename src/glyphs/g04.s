        ;;  g04.s
        ;;  
        ;;  g04
        ;; 
        ;;  notes: see libgpx documentation for format details
        ;;  
        ;;  MIT License (see: LICENSE)
        ;;  copyright(c) 2021 tomaz stih
        ;;  
        ;;  21.01.2024   tstih
        .module g04

        .globl _g04

        .area _CODE
_g04::
        ;; glyph header
        .db 160                         ; glyph magic 101xxxxx
        .db 23                          ; width
        .db 30                          ; height
        .db 255                         ; reserved
        ;; glyph data
        .db 0x01, 0x12, 0x04, 0xFF, 0x14, 0x03, 0xFF, 0x04
        .db 0x06, 0x0A, 0x03, 0xFF, 0x03, 0x08, 0x09, 0x03
        .db 0xFF, 0x03, 0x08, 0x09, 0x03, 0xFF, 0x03, 0x08
        .db 0x09, 0x03, 0xFF, 0x03, 0x08, 0x09, 0x03, 0xFF
        .db 0x03, 0x08, 0x09, 0x03, 0xFF, 0x03, 0x08, 0x09
        .db 0x03, 0xFF, 0x03, 0x08, 0x09, 0x03, 0xFF, 0x03
        .db 0x08, 0x09, 0x03, 0xFF, 0x03, 0x08, 0x09, 0x03
        .db 0xFF, 0x03, 0x08, 0x09, 0x03, 0xFF, 0x03, 0x08
        .db 0x09, 0x03, 0xFF, 0x04, 0x06, 0x0A, 0x03, 0xFF
        .db 0x17, 0xFF, 0x17, 0x01, 0x16, 0x0B, 0x09, 0x03
        .db 0x0B, 0x09, 0x03, 0x0B, 0x09, 0x03, 0x0B, 0x09
        .db 0x03, 0x0B, 0x09, 0x03, 0x0B, 0x09, 0x03, 0x0B
        .db 0x09, 0x03, 0x0B, 0x09, 0x03, 0x0B, 0x09, 0x03
        .db 0x0B, 0x09, 0x03, 0x0B, 0x09, 0x03, 0x0C, 0x07
        .db 0x04