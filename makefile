CC=cc 
CFLAG=-lglfw -ljson-c  -lm -lX11 -lpthread -lXrandr -ldl -Wall
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


#Lien vers les outils
INCLUDE_TOOL=$(SRC)Shared_tools/
MODEL_TOOL=Model/
CONTROLLER_TOOL=Controller/
VIEW_TOOL=View/


#Lien vers certain .c externe comme GLAD
EXTERN_INCLUDE=extern_lib/

all: $(SAVE_EXEC)$(EXEC)

#Création de l'executable
$(SAVE_EXEC)$(EXEC):\
	$(SRC)main.o\
	\
	$(EXTERN_INCLUDE)glad/glad.o\
	\
	$(CONTROLLER)controller_init.o\
	$(MODEL)model_init.o\
	$(VIEW)view_init.o\
	\
	$(CONTROLLER)controller_mainloop.o\
	$(CONTROLLER)controller_input.o\
	$(CONTROLLER)callback_controller.o\
	\
	$(MODEL)model_mainloop.o\
	\
	$(MODEL)model_main_menu.o\
	$(VIEW)view_main_menu.o\
	\
	$(VIEW)view_render_loop.o
	$(CC) -o $@ $^ $(CFLAG)



#Netoyer les .o
clean:
	rm -rf $(SRC)*.o
	rm -rf $(MODEL)*.o
	rm -rf $(CONTROLLER)*.o
	rm -rf $(VIEW)*.o
	rm -rf *.o
