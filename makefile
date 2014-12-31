all: full

run:
	@./build/ParticlePlay

demo:
	@rm build/ParticlePlay
	@./target/BuildDemo.sh

full:
	@rm -rf build/ParticlePlay
	@./target/BuildFull.sh

clean:
	@rm -rf build/*
