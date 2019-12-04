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

#-- EXERCICE 1: MAKE-SE
	./make-se 0 21 $(DATA)/square.png;
	$(VIEWER) $(DATA)/square.png;
	./make-se 1 21 $(DATA)/diamond.png;
	$(VIEWER) $(DATA)/diamond.png;
	./make-se 2 21 $(DATA)/disk.png;
	$(VIEWER) $(DATA)/disk.png;
	./make-se 3 21 $(DATA)/line_v.png;
	$(VIEWER) $(DATA)/line_v.png;
	./make-se 4 21 $(DATA)/diag_r.png;
	$(VIEWER) $(DATA)/diag_r.png;
	./make-se 5 21 $(DATA)/line_h.png;
	$(VIEWER) $(DATA)/line_h.png;
	./make-se 6 21 $(DATA)/diag_l.png;
	$(VIEWER) $(DATA)/diag_l.png;
	./make-se 7 21 $(DATA)/cross.png;
	$(VIEWER) $(DATA)/cross.png;
	./make-se 8 21 $(DATA)/plus.png;
	$(VIEWER) $(DATA)/plus.png;

#-- EXERCICE 3: DILATION/EROSION
	$(VIEWER) $(DATA)/lena_gray.png;
	./make-se 2 10 $(DATA)/disk-10.png;
	./make-se 7 10 $(DATA)/cross-10.png;
	./dilation $(DATA)/disk-10.png $(DATA)/lena_gray.png $(DATA)/a.png
	$(VIEWER) $(DATA)/a.png;
	./dilation $(DATA)/cross-10.png $(DATA)/lena_gray.png $(DATA)/a.png
	$(VIEWER) $(DATA)/a.png;
	./erosion $(DATA)/disk-10.png $(DATA)/lena_gray.png $(DATA)/a.png
	$(VIEWER) $(DATA)/a.png;
	./erosion $(DATA)/cross-10.png $(DATA)/lena_gray.png $(DATA)/a.png
	$(VIEWER) $(DATA)/a.png;

#-- EXERCICE 4: OPENING/CLOSING
	$(VIEWER) $(DATA)/lena_gray.png;
	./make-se 2 10 $(DATA)/disk-10.png;
	./make-se 7 10 $(DATA)/cross-10.png;
	./opening $(DATA)/disk-10.png $(DATA)/lena_gray.png $(DATA)/a.png
	$(VIEWER) $(DATA)/a.png;
	./opening $(DATA)/cross-10.png $(DATA)/lena_gray.png $(DATA)/a.png
	$(VIEWER) $(DATA)/a.png;
	./closing $(DATA)/disk-10.png $(DATA)/lena_gray.png $(DATA)/a.png
	$(VIEWER) $(DATA)/a.png;
	./closing $(DATA)/cross-10.png $(DATA)/lena_gray.png $(DATA)/a.png
	$(VIEWER) $(DATA)/a.png;

#-- EXERCICE 5: LABELING-COLOR
	$(VIEWER) $(DATA)/cell_bin.png;
	./labeling-color $(DATA)/cell-bin.png $(DATA)/cell-r.png $(DATA)/cell-c.png;
	$(VIEWER) $(DATA)/cell-r.png;
	$(VIEWER) $(DATA)/cell-c.png;

.PHONY: extract-gear
extract-gear:
	./make-se 2 10 $(DATA)/disk-10.png;
	$(VIEWER) $(DATA)/gear.png;
	./opening $(DATA)/disk-10.png $(DATA)/gear.png $(DATA)/gear-extracted.png
	composite -compose difference $(DATA)/gear-extracted.png $(DATA)/gear.png $(DATA)/gear-res.png
	$(VIEWER) $(DATA)/gear-res.png;
	./binarization 128 255 $(DATA)/gear-res.png $(DATA)/gear-res-bin.png;
	$(VIEWER) $(DATA)/gear-res-bin.png;
	./labeling-color $(DATA)/gear-res-bin.png $(DATA)/gear-res-r.png $(DATA)/gear-res-color.png;
	$(VIEWER) $(DATA)/gear-res-color.png;

.PHONY: extract-cell
extract-cell:
	./make-se 2 4 $(DATA)/disk-4.png;
	./make-se 2 19 $(DATA)/disk-19.png;
	./make-se 2 2 $(DATA)/disk-2.png;
	$(VIEWER) $(DATA)/cell.png
	./binarization 122 255 $(DATA)/cell.png $(DATA)/cell_bin.png;
	$(VIEWER) $(DATA)/cell_bin.png
	./opening $(DATA)/disk-19.png $(DATA)/cell_bin.png $(DATA)/cell-res.png
	$(VIEWER) $(DATA)/cell-res.png
	./erosion $(DATA)/disk-2.png $(DATA)/cell-res.png $(DATA)/cell-res-eroded.png
	./dilation $(DATA)/disk-4.png $(DATA)/cell-res.png $(DATA)/cell-res-opened.png
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
