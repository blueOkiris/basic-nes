# Name of file to build
NAME=     hello

# Get all the source files necessary
INITFILE= src/init.s
CFGFILE=  $(NAME).cfg
SRC=      $(wildcard src/*.c)
SRC+=     $(wildcard src/*/*.c)
HFLDRS=   headers
NMTBLS=   $(wildcard spr/*.chr)

# Generate needed configurations
INC=      $(addprefix -I,$(HFLDRS))
HFILES=   $(foreach folder,$(HFLDRS),$(wildcard $(folder)/*.h))

# Compiler options
CC=       cc65
AS=       ca65
LD=       ld65
CFLAGS=   -Oirs --add-source

# Build rom
# Commands work as follows:
# - Create temp dirs
#   * Name substitution to get c file name w/out dir, and change it to .s and place the new .s file in the tmp/ directory
# - For all source files found in src/ directory, compile with CFLAGS and INC
# - For all generated assembly files (from c files), compile those to object files
#   * Same kind of substitution as before, but now obj/ and .o extension
# - Build the init file
# - Link everything together
$(NAME).nes : $(SRC) $(HFILES) $(NMTBLS)
	mkdir -p obj
	mkdir -p tmp

	$(foreach file,$(SRC),$(CC) $(CFLAGS) $(INC) $(file) -o tmp/$(notdir $(subst .c,.s,$(file)));)
	$(foreach asm_file,$(foreach file,$(SRC),tmp/$(notdir $(subst .c,.s,$(file)))),$(AS) $(ASFLAGS) $(asm_file) -o obj/$(notdir $(subst .s,.o,$(asm_file)));)

	$(AS) $(INITFILE) -o obj/init.o

	$(LD) -C $(CFGFILE) -o $(NAME).nes obj/init.o $(foreach file,$(SRC),obj/$(notdir $(subst .c,.o,$(file)))) nes.lib

# Remove build files
.PHONY : clean
clean :
	rm -rf obj
	rm -rf tmp
	rm -rf $(NAME).nes

.PHONY : run
run : $(NAME).nes
	fceux $(NAME).nes
