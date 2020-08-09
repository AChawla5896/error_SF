BLD_DIR_REL =../..
include $(BLD_DIR_REL)/config.mk
include $(SRC_DIR)/mcMd/patterns.mk


SRC_FL := $(wildcard $(USR_DIR)/*.cpp)
user_EXE=$(USR_DIR)./avgSF
OBJ:=$(SRC_FL:./%.c=./%.o)
user=$(USR_DIR)

all: $(user_EXE)

$(user_EXE): $(user_EXE).o $(LIBS)
	$(CXX) -o $(user_EXE) $(user_EXE).o $(LIBS) $(LDFLAGS)

$(user_EXE).o: $(user_EXE).cpp 
	$(CXX) $(INCLUDES) $(MCMD_DEFINES) $(CXXFLAGS) -c -o $@ $(user_EXE).cpp
#ifdef MAKEDEP
#	$(MAKEDEP) $(INCLUDES) $(MCMD_DEFINES) $(CXXFLAGS) $(MCMD_CFGS) -S$(SRC_DIR) -B$(BLD_DIR) $<
#endif

clean:
	rm -f $(user_EXE) $(user_EXE).o

clean-deps:
	rm -f $(mcMd_user_OBJS:.o=.d)

-include $(mcMd_user_OBJS:.o=.d)
