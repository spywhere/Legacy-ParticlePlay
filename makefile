CC=g++

CPPFLAGS=\
-DPPDEBUG\
-DAL_ALEXT_PROTOTYPES\
-I/Library/Frameworks/SDL2.framework/Headers\
-I/Library/Frameworks/SDL2_image.framework/Headers\
-I/Library/Frameworks/SDL2_net.framework/Headers
# -I/Library/Frameworks/SDL2_mixer.framework/Headers\

# Library
LIBS=\
-framework SDL2\
-framework SDL2_image\
-framework SDL2_net\
-lOpenAL\
-framework OpenGL\
-lBox2D
# -framework SDL2_mixer\
# -framework Box2D
# -openal32

# Source goes here
SOURCEDIR=src
# Engine
CUSTOM_SOURCES=\
ParticlePlay/GUI/Control.cpp\
ParticlePlay/GUI/GUI.cpp\
ParticlePlay/GUI/Label.cpp\
ParticlePlay/IMS/filters/BandPassFilter.cpp\
ParticlePlay/IMS/filters/HighPassFilter.cpp\
ParticlePlay/IMS/filters/LowPassFilter.cpp\
ParticlePlay/IMS/Filter.cpp\
ParticlePlay/IMS/IMS.cpp\
ParticlePlay/IMS/Sound.cpp\
ParticlePlay/IMS/Utils.cpp\
ParticlePlay/BitmapFont.cpp\
ParticlePlay/Color.cpp\
ParticlePlay/Game.cpp\
ParticlePlay/Input.cpp\
ParticlePlay/Physics.cpp\
ParticlePlay/TestBed.cpp\
ParticlePlay/State.cpp\

# Game
SOURCES=\
TestGame.cpp\
TestScene.cpp\
TestIMS.cpp\
TestTestBed.cpp

# Demo/Full version flags
DEMO_FLAGS=\
-DDEMO

FULL_FLAGS=\
-DFULL

# Info
OBJDIR=objs
OBJDIR_CUSTOM=$(OBJDIR)/custom
OBJDIR_DEMO=$(OBJDIR)/demo
OBJDIR_FULL=$(OBJDIR)/full

CUSTOM_OBJS=$(CUSTOM_SOURCES:%.cpp=$(OBJDIR_CUSTOM)/%.o)
ALL_OBJS=$(SOURCES:%.cpp=%.o)
DEMO_OBJS=$(ALL_OBJS:%.o=$(OBJDIR_DEMO)/%.o)
FULL_OBJS=$(ALL_OBJS:%.o=$(OBJDIR_FULL)/%.o)

RESDIR=res
OUTDIR=bin
FULLEXE=TestGame
DEMOEXE=TestGameDemo

all: preclean full-link demo-link
demo: preclean demo-link
full: preclean full-link

$(OBJDIR_CUSTOM)/%.o: $(SOURCEDIR)/%.cpp
	@echo "[Custom] Compiling $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(DEMO_FLAGS) $(FULL_FLAGS) -c $< -o $@

$(OBJDIR_DEMO)/%.o: $(SOURCEDIR)/%.cpp
	@echo "[Demo] Compiling $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(DEMO_FLAGS) -c $< -o $@

$(OBJDIR_FULL)/%.o: $(SOURCEDIR)/%.cpp
	@echo "[Full] Compiling $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(FULL_FLAGS) -c $< -o $@

demo-link: $(CUSTOM_OBJS) $(DEMO_OBJS)
	@echo "[Demo] Linking..."
	@mkdir -p $(OUTDIR)
	@$(CC) -o $(OUTDIR)/$(DEMOEXE) $+ $(LIBS)

full-link: $(CUSTOM_OBJS) $(FULL_OBJS)
	@echo "[Full] Linking..."
	@mkdir -p $(OUTDIR)
	@$(CC) -o $(OUTDIR)/$(FULLEXE) $+ $(LIBS)

run-demo:
	@echo "[Demo] Running..."
	@$(OUTDIR)/$(DEMOEXE)

run-full:
	@echo "[Full] Running..."
	@$(OUTDIR)/$(FULLEXE)

resources:
	@echo "Copying resources..."
	@cp -R $(RESDIR)/* $(OUTDIR)/

preclean:
	@echo "Pre Cleaning..."
	@rm -rf $(OUTDIR)/$(FULLEXE) $(OUTDIR)/$(DEMOEXE)

clean:
	@echo "Cleaning..."
	@rm -rf $(OBJDIR) $(OUTDIR)