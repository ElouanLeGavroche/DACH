CC=cc 
CFLAG= -lglfw -ljson-c  -lm -lX11 -lpthread -lXrandr -ldl -Wall
INC=-I

#Nom de l'executable
EXEC=DACH
SAVE_EXEC=out/

#Lien des dossier
SRC=src/
SRC_CONTEXT=$(SRC)Context/
INCLUDE=include/
INCLUDE_SRC=include/src_include/

MODEL=$(SRC)Model/
CONTROLLER=$(SRC)Controller/
VIEW=$(SRC)View/

CONTEXT_MODEL=$(SRC_CONTEXT)Model/
CONTEXT_CONTROLLER=$(SRC_CONTEXT)Controller/
CONTEXT_VIEW=$(SRC_CONTEXT)View/

#Lien vers les outils
INCLUDE_TOOL=$(SRC)Shared_tools/
TRANSFORM_TOOL=$(INCLUDE_TOOL)Transform_openGL_values/
CONTEXT_TOOL=$(INCLUDE_TOOL)Context_tool/
LOAD_TOOLS=$(INCLUDE_TOOL)Load_tools/

#
LIST_TOOLS=$(INCLUDE_TOOL)List/
UNSIGNED_INT=$(LIST_TOOLS)Unsigned_list/




#Lien vers certain .c externe comme GLAD
EXTERN_INCLUDE=extern_lib/

all: $(SAVE_EXEC)$(EXEC)

#Création de l'executable
$(SAVE_EXEC)$(EXEC):\
	$(SRC)main.o\
	\
	$(EXTERN_INCLUDE)glad/glad.o\
	\
	$(TRANSFORM_TOOL)colors.o\
	$(CONTEXT_TOOL)stack.o\
	$(UNSIGNED_INT)unsigned_list.o\
	$(LOAD_TOOLS)load_shader.o\
	$(LOAD_TOOLS)load_obj_format.o\
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
	$(VIEW)view_render_loop.o\
	\
	$(CONTEXT_CONTROLLER)controller_main_menu_context.o\
	$(CONTEXT_MODEL)model_main_menu_context.o\
	$(CONTEXT_VIEW)view_main_menu_context.o\
	\
	$(CONTEXT_CONTROLLER)controller_game_context.o\
	$(CONTEXT_MODEL)model_game_context.o\
	$(CONTEXT_VIEW)view_game_context.o
	$(CC) -o $@ $^ $(CFLAG)



#Netoyer les .o
clean:
	rm -rf $(SRC)*.o
	rm -rf $(MODEL)*.o
	rm -rf $(CONTROLLER)*.o
	rm -rf $(VIEW)*.o
	rm -rf $(TRANSFORM_TOOL)*.o
	rm -rf $(CONTEXT_TOOL)*.o
	rm -rf $(CONTEXT_CONTROLLER)*.o
	rm -rf $(CONTEXT_MODEL)*.o
	rm -rf $(CONTEXT_VIEW)*.o
	rm -rf $(UNSIGNED_INT)*.o
	rm -rf $(LOAD_TOOLS)*.o
	rm -rf *.o
