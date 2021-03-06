
# compiler
CXX :=g++ -Wall -w -O3 -msse2 -fPIC -ggdb -pthread
CC :=gcc -Wall -w -O3 -msse2 -fPIC -ggdb -pthread

#CXX :=g++ -fPIC 
#CC :=gcc -fPIC 

#shared library
SFLAG := -fPIC -shared

###### target and sources
# sources

COMMEN_DIR = ../../src/API_commen
COMMEN_INC = -I$(COMMEN_DIR)
COMMEN_SRC = $(COMMEN_DIR)/API_commen.cpp

LINEARSVM_DIR = ../../src/API_linearsvm
LINEARSVM_INC = -I$(LINEARSVM_DIR)
LINEARSVM_SRC = $(LINEARSVM_DIR)/tron.cpp $(LINEARSVM_DIR)/linear.cpp $(LINEARSVM_DIR)/API_linearsvm.cpp

ADSTEXTDETECT2_DIR = ../../src/API_adstextdetect2
ADSTEXTDETECT2_INC = -I$(ADSTEXTDETECT2_DIR)
ADSTEXTDETECT2_SRC = 	$(ADSTEXTDETECT2_DIR)/region.cpp \
			$(ADSTEXTDETECT2_DIR)/region_classifier.cpp \
			$(ADSTEXTDETECT2_DIR)/max_meaningful_clustering.cpp \
			$(ADSTEXTDETECT2_DIR)/min_bounding_box.cpp \
			$(ADSTEXTDETECT2_DIR)/mser.cpp \
			$(ADSTEXTDETECT2_DIR)/group_classifier.cpp
			

# include && lib
INCLUDE = -I../../include -I../../input/include -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include -I/usr/local/cuda-6.5/include
LIBARAY = -L../../lib -L../../input/lib -L/usr/local/lib -L/usr/local/cuda/lib64 -L/usr/lib

# flags
CFLAGS =  -fopenmp  -DHAVE_JPEG -DHAVE_PNG
CXXFLAGS = -fopenmp  -DHAVE_JPEG -DHAVE_PNG \
	$(COMMEN_INC) $(LINEARSVM_INC) $(ADSTEXTDETECT2_INC) $(INCLUDE)

LDFLAGS  = -lm -lpthread -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_ml -lopencv_contrib -lopencv_features2d -lopencv_legacy -lopencv_nonfree -lopencv_objdetect
LDFLAGS  += -lcublas_device -lcublas -lcudadevrt -lcudart  -lcufft -lcufftw -lculibos -lcurand -lcusparse -lnppc -lnppi -lnpps -lcaffe
#LDFLAGS  += -DCPU_ONLY
LDFLAGS  += -ldl -lrt -ljpeg -lpng  -lz -lcurl -lstdc++ -lglog -lopenblas

SRCS =  $(COMMEN_SRC) $(LINEARSVM_SRC) $(ADSTEXTDETECT2_SRC) 
OBJS = $(SRCS:%.cpp=%.o)
OBJECTS := $(OBJS)

# BIN && LIB
BIN = ../../bin
LIB = ../../lib

###### generation rules
#.SUFFIXES: .cpp .c .o .so .a .d
.c.o:
	@echo ----------------------------------------------
	$(CC) $(CFLAGS) -c $< -o $@
	@echo ----------------------------------------------

.cpp.o:
	@echo ----------------------------------------------
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo ----------------------------------------------


###### main
#.PHONY : all 
all: lib Demo_adstextdetect2

#deps: $(addprefix $(OBJSPATH),$(DEPS))
Demo_adstextdetect2:$(BIN) $(LIB) $(OBJECTS) Demo_adstextdetect2.cpp
	@echo ----------------------------------------------
	$(CXX) $(CXXFLAGS) Demo_adstextdetect2.cpp  -o $(BIN)/Demo_adstextdetect2 -ladstextdetect2_1.0.0 $(LIBARAY) $(LDFLAGS) 
	@echo ----------------------------------------------

lib: $(LIB) $(OBJECTS)
	@echo ----------------------------------------------
	$(CXX) $(CXXFLAGS) -shared -o -fPIC -o $(LIB)/libadstextdetect2_1.0.0.so $(OBJECTS) $(LIBARAY) $(LDFLAGS)
	@echo ----------------------------------------------

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)
	rm $(LIB)/libadstextdetect2_1.0.0.so
	rm -f *.o 
	rm $(BIN)/Demo_adstextdetect2

rebuild: clean all
install:
	install -T $(TARGET) $(INSTALL_PATH)/bin/$(TARGET)
