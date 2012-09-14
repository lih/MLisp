Out:=MLisp
Out_Args:=utils
C++0x:=true

Mode:=

Flags:=-Wall -Wextra
ifeq "$(filter Tests,$(Mode))" "Tests"
  Flags+=-DMLISP_TEST
endif
ifeq "$(filter Release,$(Mode))" "Release"
  Flags+=-O2
endif
ifeq "$(filter Debug,$(Mode))" "Debug"
  Flags+=-g
endif

include C++.mk

Misc_Find:="unsigned int"
Misc_Replace:='s/unsigned int/int/'

.PHONY:ls-noimpl misc
ls-noimpl:
	-grep -in '\(noimpl\|todo\)\s*[:;]' $(Sources) $(Headers)

find:
	@-egrep -ne $(Misc_Find) $(Sources) $(Headers)

replace:
	@-sed -ri $(Misc_Replace)
try-replace:
	@-sed -rn $(Misc_Replace)p $(Sources) $(Headers)
