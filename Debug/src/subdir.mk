################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ftest.cpp \
../src/testMemMgr.cpp 

C_SRCS += \
../src/baseCode.c 

OBJS += \
./src/baseCode.o \
./src/ftest.o \
./src/testMemMgr.o 

C_DEPS += \
./src/baseCode.d 

CPP_DEPS += \
./src/ftest.d \
./src/testMemMgr.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include -I/usr/lib/gcc/i586-linux-gnu/4.9/include -I/usr/include/i386-linux-gnu -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/include/c++/4.9 -I/usr/include/i386-linux-gnu/c++/4.9 -I/usr/include/cppunit -I/usr/lib/gcc/i586-linux-gnu/4.9/include -I/usr/include/i386-linux-gnu -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


