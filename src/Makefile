# Virtual paths are all subfolders!
SDIRS			=	$(wildcard */)
vpath %.c $(SDIRS)
vpath %.s $(SDIRS)
vpath %.h $(SDIRS)

TARGET          =   $(APPNAME)
BUILD_SUBDIR	=	$(BUILD_DIR)/$(TARGET)

# Source files.
C_SRCS			=	$(wildcard */*.c) $(wildcard *.c)
S_SRCS			=	$(filter-out $(CRT0).s, $(wildcard */*.s)$(wildcard *.s))
OBJS			=	$(addprefix $(BUILD_SUBDIR)/, \
						$(notdir \
							$(patsubst %.c,%.rel,$(C_SRCS)) \
							$(patsubst %.s,%.rel,$(S_SRCS)) \
						) \
					)

# Rules.
.PHONY: all
all: $(BUILD_SUBDIR)/$(TARGET).com

$(BUILD_SUBDIR)/$(TARGET).com: $(BUILD_SUBDIR)/$(TARGET).ihx
	$(OBJCOPY) -I ihex -O binary $(basename $@).ihx $(basename $@).com

$(BUILD_SUBDIR)/$(TARGET).ihx: $(BIN_DIR)/$(CRT0).rel $(OBJS)
	$(LD) $(LDFLAGS) -o $(BUILD_SUBDIR)/$(TARGET).ihx \
		$(BIN_DIR)/$(CRT0).rel $(OBJS)
	$(L2FIX) $(BUILD_SUBDIR)/$(TARGET).lk > $(BUILD_SUBDIR)/$(TARGET).link
	$(L2) $(L2FLAGS) $(BUILD_SUBDIR)/$(TARGET).link

$(BUILD_SUBDIR)/$(CRT0).rel: $(LIB_DIR)/ulibc/$(CRT0).s
	$(AS) $(ASFLAGS) $(BUILD_SUBDIR)/$(@F) $<

$(BUILD_SUBDIR)/%.rel: %.c
	$(CC) -c -o $(BUILD_SUBDIR)/$(@F) $< $(CFLAGS) -I.

$(BUILD_SUBDIR)/%.rel: %.s
	$(AS) $(ASFLAGS) $(BUILD_SUBDIR)/$(@F) $<

.PHONY: clean
clean:
