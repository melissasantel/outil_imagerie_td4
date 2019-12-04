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


.PHONY: all
all: $(BIN)

$(BIN): morphology.o

.PHONY: test-deploy
test-deploy: all
	@./make-se ; true
	@./dilation ; true


.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
