.PHONY: all clean mrproper tags

ifndef Out
  error "No target specified"
endif

ifeq "$(strip $(C++0x))" ""
  GenericName := CPP
else
  GenericName := CPP0x
endif

Flags   +=-Ihdr -x c++ -c
ifneq "$(strip $(C++0x))" ""
  Flags +=-std=c++0x 
endif
  Flags +=$(foreach lib,$(Libs),$(shell pkg-config --cflags $(lib)))

Sources:=$(shell find src \( -name '.*' -prune -o -true \) -name '*.cc')
Headers:=$(shell find hdr \( -name '.*' -prune -o -true \) -name '*.hh')

all: bin/$(Out)

run: all
	@echo Running $(Out) :
	@mkdir -p exec && cd exec > /dev/null 2>&1 && ../bin/$(Out) $(Out_Args)

clean:
	@rm -rf obj depends.mk

mrproper:clean
	@rm -f bin/$(Out) TAGS

Linker_Flags+=$(foreach lib,$(Libs),$(shell pkg-config --libs $(lib)))
Objs:=$(Sources:src/%.cc=obj/%.o)

bin/$(Out):$(Objs)
	@-mkdir -p bin
	@echo "  LD\t" $@
	@g++ $(Linker_Flags) -o $@ $^ 

obj/%.o:
	@echo "  $(GenericName)\t" $@
	@mkdir -p `dirname $@`
	@g++ $(Flags) -o $@ $<

tags:
	@echo "  TAGS"
	@etags -l c++ $(Sources) $(Headers)

depends.mk:
	@g++ $(Flags) -MM $(Sources) \
	  | sed -r 's%^(.*\.o): src(.*)/(.*\.cc)%obj\2/\1: src\2/\3%' > $@
-include depends.mk


