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
	# binarization

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
	./opening disk-10.png $(DATA)/gear.png $(DATA)/gear_extracted.png
	$(VIEWER) $(DATA)/gear_extracted.png;
	composite -compose difference $(DATA)/gear_extracted.png $(DATA)/gear.png $(DATA)/gear_res.png
	$(VIEWER) $(DATA)/gear_res.png;
	./binarization 130 255 $(DATA)/gear_res.png $(DATA)/gear_res_int.png;
	./labeling-color $(DATA)/gear_res_int.png $(DATA)/gear_res_r.png $(DATA)/gear_res_color.png;

.PHONY: extract-cell
extract-cell:
	$(VIEWER) $(DATA)/cell.png2
	./labeling $(DATA)/cell-bin.png

.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
