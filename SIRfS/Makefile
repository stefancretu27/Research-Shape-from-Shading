CC := g++
CFLAGS := -std=c++11 -g -Wall
LIBS := -lm -lz -lpng -lmatio -lpthread

BLOCKA2_SRCS := $(wildcard block_A2/*.cpp)
MATLAB_SRCS := $(wildcard matlab/*.cpp)
REFLECTANCE_SRCS := $(wildcard reflectance/*.cpp)
HELPERS_SRCS := $(wildcard helpers/*.cpp)
TEMPLATES_SRCS := $(wildcard templates/*.cpp)

all: linkall

#execute:linkall
#	./sirfs.o

#link all object files
linkall: blockA2
	cd Obj; $(CC) $(CFLAGS) -o ../sirfs.o *.o $(LIBS); cd .
	
blockA2: blockA1 	
	$(CC) $(CFLAGS) -c main.cpp $(BLOCKA2_SRCS); mv *.o Obj 
	
blockA1: matlab
	cd block_A1/prior ; $(CC) $(CFLAGS) -c height/MKZ/GSM/lut.cpp height/MKZ/GSM.cpp height/MKZ.cpp height/normal.cpp height.cpp ; mv *.o ../../Obj
	cd block_A1/prior/lights ; $(CC) $(CFLAGS) -c color/color_gaussian.cpp color/color_whitenParams.cpp gray/gray_gaussian.cpp gray/gray_whitenParams.cpp; mv *.o ../../../Obj  
	cd block_A1/prior/reflectance/color ; $(CC) $(CFLAGS) -c  ColorMA/GSM_mvn/ReflectanceColorLut.cpp ColorMA/GSM_mvn.cpp ../color.cpp ; mv *.o ../../../../Obj 
	cd block_A1/prior/reflectance/gray ; $(CC) $(CFLAGS) -c grayMA/ReflectanceGSM.cpp grayMA.cpp ../gray.cpp; mv *.o ../../../../Obj  
	cd block_A1 ; $(CC) $(CFLAGS) -c params.cpp read_input_image_libpng.cpp;  mv *.o ../Obj
matlab: helpers
	$(CC) $(CFLAGS) -c $(MATLAB_SRCS); mv *.o Obj 
	
helpers: templts
	$(CC) $(CFLAGS) -c $(HELPERS_SRCS); mv *.o Obj 

templts:
	$(CC) $(CFLAGS) -c $(TEMPLATES_SRCS); mv *.o Obj 

#cudalink:cudacompile
#	nvcc -arch=sm_20 -dlink cudaCode.o -o link.o

#cudacompile:
#	nvcc -arch=sm_20 -dc cudaCode.cu

clean:
	cd Obj;	rm -rf *.o; cd . ; 
	rm -rf *.o; 
