CC:= gcc
CFLAGS:= -Wall -O3 -std=c99 -pedantic -Wno-unused-result
LIBS:= -lm
MKDIR:= mkdir -p
RMDIR:= rm -rf
RM:= rm -f
BINDIR:= bin
SRCDIR:= src
INCDIR:= include
OBJDIR:= obj
DOCDIR:= doc
BGMDIR:= bgm
BIN:= Rpg
SRC:= $(wildcard $(SRCDIR)/*.c)
OBJ:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
INC:= -I$(INCDIR)
TAR:= $(BIN).tar.gz

.PHONY: dump tar count clean distclean tarclean pull push amend

all: $(BINDIR)/$(BIN)

$(BINDIR)/$(BIN): $(OBJ) | $(BINDIR)
	$(CC) $^ $(LIBS) -o $@
	@echo "Generating C binary \033[1;32m"$@"\033[0m"

$(OBJ): | $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJDIR) $(BINDIR):
	$(MKDIR) $@

dump:
	@echo "src:" $(SRC)
	@echo "obj:" $(OBJ)

tar:
	$(MKDIR) $(BIN)/
	cp -r $(INCDIR)/ $(SRCDIR)/ $(DOCDIR)/ $(BGMDIR)/ Makefile *.md $(BIN)/
	tar -czf $(TAR) $(BIN)/
	$(RMDIR) $(BIN)/
	@echo "Arquivo\033[1;32m" $(TAR) "\033[0mcriado com sucesso"

count:
	wc -l $(SRCDIR)/* $(INCDIR)/*

clean:
	$(RMDIR) $(OBJDIR)/

distclean: clean
	$(RMDIR) $(BINDIR)/

tarclean:
	$(RM) $(TAR)

pull:
	git pull origin master

push:
	git add . && git commit -m "$(M)" && git push

amend:
	git add . && git commit --amend && git push -f
