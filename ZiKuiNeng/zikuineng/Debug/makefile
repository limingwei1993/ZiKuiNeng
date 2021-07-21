################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/limingwei/app/ccs/tools/compiler/ti-cgt-c2000_20.2.4.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./SOURCE/DSP2833x_ADC_cal.obj" \
"./SOURCE/DSP2833x_Adc.obj" \
"./SOURCE/DSP2833x_CSMPasswords.obj" \
"./SOURCE/DSP2833x_CodeStartBranch.obj" \
"./SOURCE/DSP2833x_CpuTimers.obj" \
"./SOURCE/DSP2833x_DBGIER.obj" \
"./SOURCE/DSP2833x_DMA.obj" \
"./SOURCE/DSP2833x_DefaultIsr.obj" \
"./SOURCE/DSP2833x_DisInt.obj" \
"./SOURCE/DSP2833x_ECan.obj" \
"./SOURCE/DSP2833x_ECap.obj" \
"./SOURCE/DSP2833x_EPwm.obj" \
"./SOURCE/DSP2833x_EQep.obj" \
"./SOURCE/DSP2833x_GlobalVariableDefs.obj" \
"./SOURCE/DSP2833x_Gpio.obj" \
"./SOURCE/DSP2833x_I2C.obj" \
"./SOURCE/DSP2833x_Mcbsp.obj" \
"./SOURCE/DSP2833x_MemCopy.obj" \
"./SOURCE/DSP2833x_PieCtrl.obj" \
"./SOURCE/DSP2833x_PieVect.obj" \
"./SOURCE/DSP2833x_Sci.obj" \
"./SOURCE/DSP2833x_Spi.obj" \
"./SOURCE/DSP2833x_SysCtrl.obj" \
"./SOURCE/DSP2833x_Xintf.obj" \
"./SOURCE/DSP2833x_usDelay.obj" \
"./comm/EEPROM.obj" \
"./comm/RS422.obj" \
"./comm/SPI_SDCard.obj" \
"./comm/diskio.obj" \
"./comm/ff.obj" \
"./comm/ffsystem.obj" \
"./comm/ffunicode.obj" \
"./comm/initialization.obj" \
"./comm/main.obj" \
"./comm/pwm.obj" \
"./comm/sdcard.obj" \
"./comm/spi_ADS1258.obj" \
"./comm/time.obj" \
"../CMD/DSP2833x_Headers_nonBIOS.cmd" \
"../CMD/F28335.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include CMD/subdir_vars.mk
-include SOURCE/subdir_vars.mk
-include comm/subdir_vars.mk
-include CMD/subdir_rules.mk
-include SOURCE/subdir_rules.mk
-include comm/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
zikuineng.out \

EXE_OUTPUTS__QUOTED += \
"zikuineng.out" \

BIN_OUTPUTS += \
zikuineng.hex \

BIN_OUTPUTS__QUOTED += \
"zikuineng.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "zikuineng.out"

# Tool invocations
zikuineng.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/limingwei/app/ccs/tools/compiler/ti-cgt-c2000_20.2.4.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi -z -m"zikuineng.map" --stack_size=0x300 --warn_sections -i"C:/limingwei/app/ccs/tools/compiler/ti-cgt-c2000_20.2.4.LTS/lib" -i"C:/limingwei/app/ccs/tools/compiler/ti-cgt-c2000_20.2.4.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="zikuineng_linkInfo.xml" --rom_model -o "zikuineng.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

zikuineng.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: C2000 Hex Utility'
	"C:/limingwei/app/ccs/tools/compiler/ti-cgt-c2000_20.2.4.LTS/bin/hex2000" --diag_wrap=off -o "zikuineng.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "SOURCE\DSP2833x_ADC_cal.obj" "SOURCE\DSP2833x_Adc.obj" "SOURCE\DSP2833x_CSMPasswords.obj" "SOURCE\DSP2833x_CodeStartBranch.obj" "SOURCE\DSP2833x_CpuTimers.obj" "SOURCE\DSP2833x_DBGIER.obj" "SOURCE\DSP2833x_DMA.obj" "SOURCE\DSP2833x_DefaultIsr.obj" "SOURCE\DSP2833x_DisInt.obj" "SOURCE\DSP2833x_ECan.obj" "SOURCE\DSP2833x_ECap.obj" "SOURCE\DSP2833x_EPwm.obj" "SOURCE\DSP2833x_EQep.obj" "SOURCE\DSP2833x_GlobalVariableDefs.obj" "SOURCE\DSP2833x_Gpio.obj" "SOURCE\DSP2833x_I2C.obj" "SOURCE\DSP2833x_Mcbsp.obj" "SOURCE\DSP2833x_MemCopy.obj" "SOURCE\DSP2833x_PieCtrl.obj" "SOURCE\DSP2833x_PieVect.obj" "SOURCE\DSP2833x_Sci.obj" "SOURCE\DSP2833x_Spi.obj" "SOURCE\DSP2833x_SysCtrl.obj" "SOURCE\DSP2833x_Xintf.obj" "SOURCE\DSP2833x_usDelay.obj" "comm\EEPROM.obj" "comm\RS422.obj" "comm\SPI_SDCard.obj" "comm\diskio.obj" "comm\ff.obj" "comm\ffsystem.obj" "comm\ffunicode.obj" "comm\initialization.obj" "comm\main.obj" "comm\pwm.obj" "comm\sdcard.obj" "comm\spi_ADS1258.obj" "comm\time.obj" 
	-$(RM) "SOURCE\DSP2833x_Adc.d" "SOURCE\DSP2833x_CpuTimers.d" "SOURCE\DSP2833x_DMA.d" "SOURCE\DSP2833x_DefaultIsr.d" "SOURCE\DSP2833x_ECan.d" "SOURCE\DSP2833x_ECap.d" "SOURCE\DSP2833x_EPwm.d" "SOURCE\DSP2833x_EQep.d" "SOURCE\DSP2833x_GlobalVariableDefs.d" "SOURCE\DSP2833x_Gpio.d" "SOURCE\DSP2833x_I2C.d" "SOURCE\DSP2833x_Mcbsp.d" "SOURCE\DSP2833x_MemCopy.d" "SOURCE\DSP2833x_PieCtrl.d" "SOURCE\DSP2833x_PieVect.d" "SOURCE\DSP2833x_Sci.d" "SOURCE\DSP2833x_Spi.d" "SOURCE\DSP2833x_SysCtrl.d" "SOURCE\DSP2833x_Xintf.d" "comm\EEPROM.d" "comm\RS422.d" "comm\SPI_SDCard.d" "comm\diskio.d" "comm\ff.d" "comm\ffsystem.d" "comm\ffunicode.d" "comm\initialization.d" "comm\main.d" "comm\pwm.d" "comm\sdcard.d" "comm\spi_ADS1258.d" "comm\time.d" 
	-$(RM) "SOURCE\DSP2833x_ADC_cal.d" "SOURCE\DSP2833x_CSMPasswords.d" "SOURCE\DSP2833x_CodeStartBranch.d" "SOURCE\DSP2833x_DBGIER.d" "SOURCE\DSP2833x_DisInt.d" "SOURCE\DSP2833x_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

