BUILD = build
QUIET_ECHO = @ echo
APP_NAME = aco
CXX = g++ -m64 -std=c++11
CXXFLAGS = -I. -O3 -Wall -fopenmp -Wno-unknown-pragmas


.PHONY: all
all: $(APP_NAME)

# --------------------------------------------------------------------------
# Compile target patterns

$(BUILD)/obj/%.o: src/sequential/%.cpp
	$(QUIET_ECHO) $@: Compiling object
	@ mkdir -p $(dir $(BUILD)/dep/$<)
	@ $(CXX) $(CXXFLAGS) -M -MG -MQ $@ -DCOMPILINGDEPENDENCIES \
        -o $(BUILD)/dep/$(<:%.cpp=%.d) -c $<
	@ mkdir -p $(dir $@)
	@ $(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILD)/obj/%.o: src/paco/%.cpp
	$(QUIET_ECHO) $@: Compiling object
	@ mkdir -p $(dir $(BUILD)/dep/$<)
	@ $(CXX) $(CXXFLAGS) -M -MG -MQ $@ -DCOMPILINGDEPENDENCIES \
        -o $(BUILD)/dep/$(<:%.cpp=%.d) -c $<
	@ mkdir -p $(dir $@)
	@ $(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILD)/obj/main.o: src/main.cpp
	$(QUIET_ECHO) $@: Compiling object
	@ mkdir -p $(dir $(BUILD)/dep/$<)
	@ $(CXX) $(CXXFLAGS) -M -MG -MQ $@ -DCOMPILINGDEPENDENCIES \
        -o $(BUILD)/dep/$(<:%.cpp=%.d) -c $<
	@ mkdir -p $(dir $@)
	@ $(CXX) $(CXXFLAGS) -o $@ -c $<


.PHONY: $(APP_NAME)
$(APP_NAME): $(BUILD)/bin/$(APP_NAME)

OBJS = $(BUILD)/obj/dataloader.o \
	   $(BUILD)/obj/model.o \
	   $(BUILD)/obj/paco.o \
	   $(BUILD)/obj/ant.o \
	   $(BUILD)/obj/path.o \
	   $(BUILD)/obj/random.o \
	   $(BUILD)/obj/tabu.o \
	   $(BUILD)/obj/timer.o \
       $(BUILD)/obj/main.o

$(BUILD)/bin/$(APP_NAME): $(OBJS)
	$(QUIET_ECHO) $@: Building executable
	@ mkdir -p $(dir $@)
	@ $(CXX) $(CXXFLAGS) -o $@ $^


.PHONY: clean
clean:
	$(QUIET_ECHO) $(BUILD): Cleaning
	@ rm -rf $(BUILD)