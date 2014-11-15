################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../QAP.cpp \
../benchmarking.cpp \
../console.cpp \
../constellation.cpp \
../constellations.cpp \
../distances.cpp \
../main.cpp \
../permutations.cpp \
../randn.cpp \
../statistics.cpp \
../symbol.cpp 

OBJS += \
./QAP.o \
./benchmarking.o \
./console.o \
./constellation.o \
./constellations.o \
./distances.o \
./main.o \
./permutations.o \
./randn.o \
./statistics.o \
./symbol.o 

CPP_DEPS += \
./QAP.d \
./benchmarking.d \
./console.d \
./constellation.d \
./constellations.d \
./distances.d \
./main.d \
./permutations.d \
./randn.d \
./statistics.d \
./symbol.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/boost/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


