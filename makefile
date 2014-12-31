all: full

run:
	@./build/ParticlePlay

demo: preclean
	@./UnixBuild.sh debug demo

full: preclean
	@./UnixBuild.sh debug full

preclean:
	@rm -rf build/ParticlePlay

clean:
	@rm -rf build/*
