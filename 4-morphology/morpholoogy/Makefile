CPPFLAGS= -I. -I/opt/opencv/include
CXXFLAGS= -Wall -Wextra -Werror
LDFLAGS = -Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui

#modify DATA or VIEWER path command if not applicable
VIEWER= pvisu
DATA= ../data

OBJ= morphology.o
BIN= \
	make-se\
	dilation\
	erosion\
	opening\
	closing\
	labeling\
	labeling-color

.PHONY: all
all: $(BIN)

$(BIN): morphology.o

.PHONY: test-deploy
test-deploy: all
	@./make-se ; true
	@./dilation ; true
	make extract-gear
	make extract-cell

.PHONY: extract-gear
extract-gear:
	$(VIEWER) $(DATA)/gear.png;

.PHONY: extract-cell
extract-cell:
	$(VIEWER) $(DATA)/cell.png;
	./labeling $(DATA)/cell-bin.png

.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
