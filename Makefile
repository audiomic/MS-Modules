
SOURCES = $(wildcard src/*.cpp)

include ../../plugin.mk


dist: all
	mkdir -p dist/MS_modules
	cp LICENSE* dist/MS_modules/
	cp plugin.* dist/MS_modules/
	cp -R res dist/MS_modules/
