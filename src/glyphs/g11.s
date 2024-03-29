        ;;  g11.s
        ;;  
        ;;  g11
        ;; 
        ;;  notes: see libgpx documentation for format details
        ;;  
        ;;  MIT License (see: LICENSE)
        ;;  copyright(c) 2021 tomaz stih
        ;;  
        ;;  21.01.2024   tstih
        .module g11

        .globl _g11

        .area _CODE
_g11::
        ;; glyph header
        .db 160                         ; glyph magic 101xxxxx
        .db 29                          ; width
        .db 30                          ; height
        .db 255                         ; reserved
        ;; glyph data
        .db 0xFF, 0x0C, 0x04, 0x0C, 0x01, 0xFF, 0x0D, 0x03
        .db 0x0D, 0x04, 0x09, 0x07, 0x09, 0x04, 0x09, 0x07
        .db 0x09, 0x04, 0x09, 0x07, 0x09, 0x04, 0x09, 0x07
        .db 0x09, 0x04, 0x09, 0x07, 0x09, 0x04, 0x09, 0x07
        .db 0x09, 0x04, 0x09, 0x07, 0x09, 0x04, 0x09, 0x07
        .db 0x09, 0x04, 0x09, 0x07, 0x09, 0x04, 0x09, 0x07
        .db 0x09, 0x04, 0x09, 0x07, 0x09, 0x04, 0x09, 0x07
        .db 0x09, 0x04, 0x09, 0x07, 0x09, 0x04, 0x09, 0x07
        .db 0x09, 0x04, 0x09, 0x07, 0x09, 0x04, 0x09, 0x07
        .db 0x09, 0x04, 0x09, 0x07, 0x09, 0x04, 0x09, 0x07
        .db 0x09, 0x04, 0x09, 0x07, 0x09, 0x04, 0x09, 0x07
        .db 0x09, 0x04, 0x09, 0x07, 0x09, 0x04, 0x09, 0x07
        .db 0x09, 0x04, 0x09, 0x07, 0x09, 0x04, 0x09, 0x07
        .db 0x09, 0x04, 0x09, 0x07, 0x09, 0x04, 0x09, 0x07
        .db 0x09, 0x04, 0x09, 0x07, 0x09, 0x05, 0x07, 0x09
        .db 0x07, 0x01
