CC=g++

CPPFLAGS=\
-std=c++11\
-DPPDEBUG\
-DAL_ALEXT_PROTOTYPES\
-I/Library/Frameworks/SDL2.framework/Headers\
-I/Library/Frameworks/SDL2_image.framework/Headers\
-I/Library/Frameworks/SDL2_net.framework/Headers

# Library
LIBS=\
-framework SDL2\
-framework SDL2_image\
-framework SDL2_net\
-lOpenAL\
-framework OpenGL\
-lBox2D
# -lopenal32

# Source goes here
SOURCEDIR=src
# Engine
ENGINE_SOURCES=\
ParticlePlay/Easings/BackEasing.cpp\
ParticlePlay/Easings/BackInEasing.cpp\
ParticlePlay/Easings/BackOutEasing.cpp\
ParticlePlay/Easings/BounceEasing.cpp\
ParticlePlay/Easings/BounceInEasing.cpp\
ParticlePlay/Easings/BounceOutEasing.cpp\
ParticlePlay/Easings/CircEasing.cpp\
ParticlePlay/Easings/CircInEasing.cpp\
ParticlePlay/Easings/CircOutEasing.cpp\
ParticlePlay/Easings/CubicEasing.cpp\
ParticlePlay/Easings/CubicInEasing.cpp\
ParticlePlay/Easings/CubicOutEasing.cpp\
ParticlePlay/Easings/ElasticEasing.cpp\
ParticlePlay/Easings/ElasticInEasing.cpp\
ParticlePlay/Easings/ElasticOutEasing.cpp\
ParticlePlay/Easings/ExpoEasing.cpp\
ParticlePlay/Easings/ExpoInEasing.cpp\
ParticlePlay/Easings/ExpoOutEasing.cpp\
ParticlePlay/Easings/LinearEasing.cpp\
ParticlePlay/Easings/QuadEasing.cpp\
ParticlePlay/Easings/QuadInEasing.cpp\
ParticlePlay/Easings/QuadOutEasing.cpp\
ParticlePlay/Easings/QuartEasing.cpp\
ParticlePlay/Easings/QuartInEasing.cpp\
ParticlePlay/Easings/QuartOutEasing.cpp\
ParticlePlay/Easings/QuintEasing.cpp\
ParticlePlay/Easings/QuintInEasing.cpp\
ParticlePlay/Easings/QuintOutEasing.cpp\
ParticlePlay/Easings/SineEasing.cpp\
ParticlePlay/Easings/SineInEasing.cpp\
ParticlePlay/Easings/SineOutEasing.cpp\
ParticlePlay/Graphics/BitmapFont.cpp\
ParticlePlay/Graphics/Graphics.cpp\
ParticlePlay/Graphics/Image.cpp\
ParticlePlay/GUI/Control/Label.cpp\
ParticlePlay/GUI/Control.cpp\
ParticlePlay/GUI/GUI.cpp\
ParticlePlay/IMS/Format/EmptyFormat.cpp\
ParticlePlay/IMS/Format/Format.cpp\
ParticlePlay/IMS/Format/WaveFormat.cpp\
ParticlePlay/IMS/Interfaces.cpp\
ParticlePlay/IMS/IMS.cpp\
ParticlePlay/IMS/Playlist.cpp\
ParticlePlay/IMS/Segment.cpp\
ParticlePlay/IMS/Sound.cpp\
ParticlePlay/IMS/Utils.cpp\
ParticlePlay/Color.cpp\
ParticlePlay/Game.cpp\
ParticlePlay/Input.cpp\
ParticlePlay/IO.cpp\
ParticlePlay/Physics.cpp\
ParticlePlay/Randomizer.cpp\
ParticlePlay/State.cpp\
ParticlePlay/TestBed.cpp\

# Game
SOURCES=\
FarmGame/AnimateTile.cpp\
FarmGame/Chicken.cpp\
FarmGame/Entity.cpp\
FarmGame/FarmState.cpp\
FarmGame/Player.cpp\
FarmGame/Spritesheet.cpp\
FarmGame/Tile.cpp\
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
OBJDIR_ENGINE=$(OBJDIR)/custom
OBJDIR_DEMO=$(OBJDIR)/demo
OBJDIR_FULL=$(OBJDIR)/full

ENGINE_OBJS=$(ENGINE_SOURCES:%.cpp=$(OBJDIR_ENGINE)/%.o)
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

$(OBJDIR_ENGINE)/%.o: $(SOURCEDIR)/%.cpp
	@echo "[Engine] Compiling $<"
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

demo-link: $(ENGINE_OBJS) $(DEMO_OBJS)
	@echo "[Demo] Linking..."
	@mkdir -p $(OUTDIR)
	@$(CC) -o $(OUTDIR)/$(DEMOEXE) $+ $(LIBS)

full-link: $(ENGINE_OBJS) $(FULL_OBJS)
	@echo "[Full] Linking..."
	@mkdir -p $(OUTDIR)
	@$(CC) -o $(OUTDIR)/$(FULLEXE) $+ $(LIBS)

run-demo: demo
	@echo "[Demo] Running..."
	@$(OUTDIR)/$(DEMOEXE)

run-full: full
	@echo "[Full] Running..."
	@$(OUTDIR)/$(FULLEXE)

resources:
	@echo "Copying resources..."
	@mkdir -p $(OUTDIR)
	@cp -R $(RESDIR)/* $(OUTDIR)/

preclean:
	@echo "Pre Cleaning..."
	@rm -rf $(OUTDIR)/$(FULLEXE) $(OUTDIR)/$(DEMOEXE)

clean:
	@echo "Cleaning..."
	@rm -rf $(OBJDIR) $(OUTDIR)
