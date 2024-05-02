#
# Makefile
#
CC 				= arm-linux-gnueabihf-gcc
LVGL_DIR_NAME 	?= lvgl
LVGL_DIR 		?= .

WARNINGS		:= -Wall -Wshadow -Wundef -Wmissing-prototypes -Wno-discarded-qualifiers -Wall -Wextra -Wno-unused-function -Wno-error=strict-prototypes -Wpointer-arith \
					-fno-strict-aliasing -Wno-error=cpp -Wuninitialized -Wmaybe-uninitialized -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess \
					-Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-error=pedantic \
					-Wno-sign-compare -Wno-error=missing-prototypes -Wdouble-promotion -Wclobbered -Wdeprecated -Wempty-body -Wtype-limits -Wstack-usage=2048 \
					-Wno-unused-value -Wno-unused-parameter -Wno-missing-field-initializers -Wuninitialized -Wmaybe-uninitialized -Wall -Wextra -Wno-unused-parameter \
					-Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wpointer-arith -Wno-cast-qual -Wmissing-prototypes \
					-Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wno-discarded-qualifiers -Wformat-security -Wno-ignored-qualifiers -Wno-sign-compare -std=c99
CFLAGS 			?= -O3 -g0 -I$(LVGL_DIR)/ $(WARNINGS)

BR_INCS			= /home/alientek/ssd20x/buildroot-2020.05/output/build/libcurl-7.69.1/include/
MAD_INCS		= /home/alientek/ssd20x/buildroot-2020.05/output/build/libmad-0.15.1b/
BR_LIBS			=/home/alientek/ssd20x/buildroot-2020.05/output/target/usr/lib

INC 			= -I./phy_drivers/audio/include -I./phy_drivers/audio -I./screen -I$(BR_INCS) -I$(MAD_INCS)
LDFLAGS 		?= -L$(BR_LIBS) -L./phy_drivers/audio/lib -lmi_ai -lm -lmi_ao -ldl -lmi_sys -lmi_common -lpthread -lmad
BIN 			= lvgl_demo
BUILD_DIR 		= ./build
BUILD_OBJ_DIR 	= $(BUILD_DIR)/obj
BUILD_BIN_DIR 	= $(BUILD_DIR)/bin

#Collect the files to compile

include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk

OBJEXT 			?= .o

# lvgl file 
AOBJS 			= $(ASRCS:.S=$(OBJEXT))
COBJS 			= $(CSRCS:.c=$(OBJEXT))

# main
MAINSRC = 		./main.c
MAINOBJ 		= $(MAINSRC:.c=$(OBJEXT))

# squareline generate ui file
GEN_SRCS	 	:= $(shell find generate -type f -name '*.c')
GEN_OBJS 		:= $(GEN_SRCS:.c=$(OBJEXT))

# ssd202 phy drivers
PHY_DRIVER_SRCS	:= $(shell find phy_drivers -type f -name '*.c')
PHY_DRIVER_OBJS := $(PHY_DRIVER_SRCS:.c=$(OBJEXT))

# user ui file 
LVGL_EXTRA_SRCS := $(shell find screen -type f -name '*.c')
LVGL_EXTRA_OBJS := $(LVGL_EXTRA_SRCS:.c=.o)


SRCS 			= $(ASRCS) $(CSRCS) $(MAINSRC)
OBJS 			= $(AOBJS) $(COBJS) $(MAINOBJ) $(GEN_OBJS) $(PHY_DRIVER_OBJS) $(LVGL_EXTRA_OBJS)
TARGET 			= $(addprefix $(BUILD_OBJ_DIR)/, $(patsubst ./%, %, $(OBJS)))

$(BUILD_OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC)  $(CFLAGS) $(INC) -c $< -o $@
	@echo "CC $<"
    
default: $(TARGET)
	@mkdir -p $(dir $(BUILD_BIN_DIR)/)
	$(CC) -o $(BUILD_BIN_DIR)/$(BIN) $(TARGET) $(INC) $(LDFLAGS)

clean: 
	rm -rf $(BUILD_DIR)