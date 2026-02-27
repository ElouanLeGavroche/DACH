CC=cc 
CFLAG=-lglfw -ljson-c -lGL -lm -lX11 -lpthread -lXrandr -ldl -Wall
INC=-I

#Nom de l'executable
EXEC=DACH
SAVE_EXEC=out/

#Lien des dossier
SRC=src/
INCLUDE=include/
INCLUDE_SRC=include/src_include/
MODEL=$(SRC)Model/
CONTROLLER=$(SRC)Controller/
VIEW=$(SRC)View/

all: $(SAVE_EXEC)$(EXEC)

#Création de l'executable
$(SAVE_EXEC)$(EXEC):\
	$(SRC)main.o\
	\
	$(CONTROLLER)controller_init.o\
	$(MODEL)model_init.o\
	$(VIEW)view_init.o
	$(CC) -o $@ $^ $(CFLAG)



#Netoyer les .o
clean:
	rm -rf $(SRC)*.o
	rm -rf $(MODEL)*.o
	rm -rf $(CONTROLLER)*.o
	rm -rf $(VIEW)*.o
	rm -rf *.o
