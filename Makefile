COMPILER := g++
COMPILE_FLAGS := `pkg-config gtkmm-3.0 --cflags --libs` -lgtkmm-3.0 -lgdkmm-3.0 -latkmm-1.6 -lgiomm-2.4 -lglibmm-2.4 -lsigc-2.0 -lhandy-1

.PHONY: clean
clean:
	rm -rf passcoder

.PHONY: build
build: clean
	$(COMPILER) -o build/passcoder src/main.cpp -Iinclude -DUI_FILENAME=\"ui/mainw.glade\" $(COMPILE_FLAGS)

.PHONY: try
try: build
	@cd build && ./passcoder
