BUILD = build
QUIET_ECHO = @ echo
APP_NAME = aco
CXX = g++ -m64 -std=c++11
CXXFLAGS = -I. -O3 -Wall


.PHONY: all
all: $(APP_NAME)

# --------------------------------------------------------------------------
# Compile target patterns

$(BUILD)/obj/%.o: src/%.cpp
	$(QUIET_ECHO) $@: Compiling object
	@ mkdir -p $(dir $(BUILD)/dep/$<)
	@ $(CXX) $(CXXFLAGS) -M -MG -MQ $@ -DCOMPILINGDEPENDENCIES \
        -o $(BUILD)/dep/$(<:%.cpp=%.d) -c $<
	@ mkdir -p $(dir $@)
	@ $(CXX) $(CXXFLAGS) -o $@ -c $<



.PHONY: $(APP_NAME)
$(APP_NAME): $(BUILD)/bin/$(APP_NAME)

OBJS = $(BUILD)/obj/dataloader.o \
       $(BUILD)/obj/main.o

$(BUILD)/bin/$(APP_NAME): $(OBJS)
	$(QUIET_ECHO) $@: Building executable
	@ mkdir -p $(dir $@)
	@ $(CXX) $(CXXFLAGS) -o $@ $^