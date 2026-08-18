CC=cc 
CPPFLAGS := -Iinclude -Iextern_lib 
CFLAGS := -std=c17 -Wall -Wextra -Wshadow -g
LDLIBS := -lglfw -ljson-c -lm -lX11 -lpthread -lXrandr -ldl
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

CORE=$(SRC)Core/
PLATFORM=$(SRC)Platform/
RENDERER=$(SRC)Renderer/
GAME=$(SRC)Game/

CONTEXT_MODEL=$(SRC_CONTEXT)Model/
CONTEXT_CONTROLLER=$(SRC_CONTEXT)Controller/
CONTEXT_VIEW=$(SRC_CONTEXT)View/

#Lien vers les outils
INCLUDE_TOOL=$(SRC)Shared_tools/
TRANSFORM_TOOL=$(INCLUDE_TOOL)Transform_openGL_values/
CONTEXT_TOOL=$(INCLUDE_TOOL)Context_tool/
LOAD_TOOLS=$(INCLUDE_TOOL)Load_tools/

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
	\
	$(LOAD_TOOLS)load_shader.o\
	$(LOAD_TOOLS)load_obj_format.o\
	$(LOAD_TOOLS)load_image.o\
	$(LOAD_TOOLS)load_map.o\
	\
	$(CORE)application.o\
	$(CORE)clock.o\
	$(CORE)context_stack.o\
	$(CORE)context_group.o\
	$(CORE)context_content.o\
	$(CORE)context_request.o\
	$(CORE)context_camera.o\
	$(CORE)result.o\
	\
	$(PLATFORM)glfw_input.o\
	$(PLATFORM)glfw_window.o\
	$(PLATFORM)glfw_mouse.o\
	$(PLATFORM)glfw_time.o\
	\
	$(GAME)country.o\
	\
	$(RENDERER)opengl_renderer.o\
	$(RENDERER)render_group.o\
	$(RENDERER)render_scene.o\
	$(RENDERER)renderer.o\
	\
	$(CONTEXT_CONTROLLER)controller_main_menu_context.o\
	$(CONTEXT_MODEL)model_main_menu_context.o\
	$(CONTEXT_VIEW)view_main_menu_context.o\
	\
	$(CONTEXT_CONTROLLER)controller_game_context.o\
	$(CONTEXT_MODEL)model_game_context.o\
	$(CONTEXT_VIEW)view_game_context.o\
	\
	$(CONTEXT_CONTROLLER)controller_pause_menu_context.o\
	$(CONTEXT_MODEL)model_pause_menu_context.o\
	$(CONTEXT_VIEW)view_pause_menu_context.o
	$(CC) -o $@ $^ $(CPPFLAGS) $(CFLAGS) $(LDLIBS)



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
	rm -rf $(UNSIGNED_INT_LIST)*.o
	rm -rf $(INT_LIST)*.o
	rm -rf $(FLOAT_LIST)*.o
	rm -rf $(LOAD_TOOLS)*.o
	rm -rf $(EXTERN_INCLUDE)glad/*.o
	rm -rf $(CORE)*.o 
	rm -rf $(PLATFORM)*.o 
	rm -rf $(RENDERER)*.o
	rm -rf *.o
	rm -rf out/DACH
