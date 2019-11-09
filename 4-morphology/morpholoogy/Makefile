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
	labeling-color\
	binarization\
	add-boundary

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
	composite -compose difference $(DATA)/gear_extracted.png $(DATA)/gear.png $(DATA)/gear_res.png
	$(VIEWER) $(DATA)/gear_res.png;
	./binarization 128 255 $(DATA)/gear_res.png $(DATA)/gear_res_bin.png;
	$(VIEWER) $(DATA)/gear_res_bin.png;
	./labeling-color $(DATA)/gear_res_bin.png $(DATA)/gear_res_r.png $(DATA)/gear_res_color.png;
	$(VIEWER) $(DATA)/gear_res_color.png;

.PHONY: extract-cell
extract-cell:
	./make-se 2 4 disk-4.png;
	./make-se 2 19 disk-19.png;
	./make-se 2 2 disk-2.png;
	$(VIEWER) $(DATA)/cell.png
	./binarization 122 255 $(DATA)/cell.png $(DATA)/cell_bin.png;
	# ./binarization 128 255 $(DATA)/cell.png $(DATA)/cell_bin.png;
	$(VIEWER) $(DATA)/cell_bin.png
	./opening disk-19.png $(DATA)/cell_bin.png $(DATA)/cell-res.png
	$(VIEWER) $(DATA)/cell-res.png
	# ./erosion disk-4.png $(DATA)/cell-res.png $(DATA)/cell-eroded.png
	./erosion disk-2.png $(DATA)/cell-res.png $(DATA)/cell-res-eroded.png
	./dilation disk-4.png $(DATA)/cell-res.png $(DATA)/cell-res-opened.png
	# composite -compose difference $(DATA)/cell-res.png $(DATA)/cell-eroded.png $(DATA)/cell-res-boundary.png
	composite -compose difference $(DATA)/cell-res-opened.png $(DATA)/cell-res-eroded.png $(DATA)/cell-res-boundary.png
	$(VIEWER) $(DATA)/cell-res-boundary.png
	./add-boundary $(DATA)/cell-res-boundary.png $(DATA)/cell.png $(DATA)/cell-final.png
	$(VIEWER) $(DATA)/cell-final.png
	./labeling-color $(DATA)/cell-res.png $(DATA)/cell-res-r.png $(DATA)/cell-res-color.png
	$(VIEWER) $(DATA)/cell-res-color.png

.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
