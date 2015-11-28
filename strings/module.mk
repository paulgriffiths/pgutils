local_dir := src/strings
local_src := $(wildcard $(local_dir)/*.c)
local_objs := $(subst .c,.o,$(local_src))

sources   += $(local_src)
objects   += $(local_objs)


