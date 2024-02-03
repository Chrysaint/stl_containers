

BUILD_DIR=build/
MKDIR_EXISTING=mkdir -p
BIN_CONTAINERS=bin/containers/
BIN=bin/
TAR_FILE=s21_containers_headers.tar
COMPILE_COMMANDS_JSON_FILE=compile_commands.json
COVERAGE_REPORT_BUILD_DIR=coverage_report_build/
IGNORE_BUILDING_DIRS=-path ./build -o -path ./cmake-build-debug -o -path ./coverage_report_build

all : clean format_google_style test install_headers create_tar_headers

format_google_style : clean
	@echo "┏=========================================┓"
	@echo "┃                                         ┃"
	@echo "┃            CODE FORMATTING              ┃"
	@echo "┃                                         ┃"
	@echo "┗=========================================┛"
	find . \( $(IGNORE_BUILDING_DIRS) \) -prune -o \( -name "*.cpp" -o -name "*.h" \) -print | xargs clang-format -i -style="{BasedOnStyle: Google}"

test : format_style test_units test_mem_check test_static test_coverage
	@echo "┏=========================================┓"
	@echo "┃                                         ┃"
	@echo "┃      RUNNING ALL TESTING TARGETS        ┃"
	@echo "┃                                         ┃"
	@echo "┗=========================================┛"

test_static : test_cppcheck

test_units : format_style
	@echo "┏=========================================┓"
	@echo "┃                                         ┃"
	@echo "┃              UNIT TESTS                 ┃"
	@echo "┃                                         ┃"
	@echo "┗=========================================┛"
	$(MKDIR_EXISTING) $(BUILD_DIR)
	cmake -B $(BUILD_DIR) -S .
	cmake --build $(BUILD_DIR)
	make -C ./$(BUILD_DIR) test_units

test_coverage : clean_coverage format_style
	@echo "┏=========================================┓"
	@echo "┃                                         ┃"
	@echo "┃           COVERAGE REPORT               ┃"
	@echo "┃                                         ┃"
	@echo "┗=========================================┛"
	$(MKDIR_EXISTING) $(COVERAGE_REPORT_BUILD_DIR)
	cmake -B $(COVERAGE_REPORT_BUILD_DIR) -S . -DCMAKE_BUILD_TYPE=Coverage
	cmake --build $(COVERAGE_REPORT_BUILD_DIR)
	make -C ./$(COVERAGE_REPORT_BUILD_DIR) test_coverage

clean_coverage :
	rm -rf $(COVERAGE_REPORT_BUILD_DIR)

test_mem_check :  test_valgrind test_sanitizer

test_sanitizer : clean format_style
	@echo "┏=========================================┓"
	@echo "┃                                         ┃"
	@echo "┃            SANITIZER TEST               ┃"
	@echo "┃                                         ┃"
	@echo "┗=========================================┛"
	$(MKDIR_EXISTING) $(BUILD_DIR)
	cmake -B $(BUILD_DIR) -S . -DCMAKE_BUILD_TYPE=Sanitizer
	cmake --build $(BUILD_DIR)
	make -C ./$(BUILD_DIR) test_sanitizer

test_valgrind : clean format_style
	@echo "┏=========================================┓"
	@echo "┃                                         ┃"
	@echo "┃             VALGRIND TEST               ┃"
	@echo "┃                                         ┃"
	@echo "┗=========================================┛"
	$(MKDIR_EXISTING) $(BUILD_DIR)
	cmake -B $(BUILD_DIR) -S .
	cmake --build $(BUILD_DIR)
	make -C ./$(BUILD_DIR) test_valgrind


format_style : ___check_clang_format___
	@echo "┏=========================================┓"
	@echo "┃                                         ┃"
	@echo "┃            CODE FORMATTING              ┃"
	@echo "┃                                         ┃"
	@echo "┗=========================================┛"
	find . \( $(IGNORE_BUILDING_DIRS) \) -prune -o \( -name "*.cpp" -o -name "*.h" \) -print | xargs clang-format -i -style=file:linters/.clang-format

check_format_style : ___check_clang_format___
	@echo "┏=========================================┓"
	@echo "┃                                         ┃"
	@echo "┃        CHECKING CODE FORMATTING         ┃"
	@echo "┃                                         ┃"
	@echo "┗=========================================┛"
	@find . \( $(IGNORE_BUILDING_DIRS) \) -prune -o \( -name "*.cpp" -o -name "*.h" \) -print | xargs clang-format -n -style=file:linters/.clang-format

.PHONY: ___check_clang_format___

clean :
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN)
	rm -rf $(COMPILE_COMMANDS_JSON_FILE)
	rm -rf $(TAR_FILE)

___check_clang_format___ : ___check_pipx_installed___
	echo "Checking clang-format..."; \
	if command -v clang-format >/dev/null 2>&1; then \
		VERSION=$$(clang-format --version | grep -oE '[0-9]+(\.[0-9]+)*' | head -1 | cut -d. -f1); \
		echo "Found clang-format version $$VERSION"; \
		if [ "$$VERSION" -lt 20 ]; then \
			echo "clang-format version is less than 20. Installing latest via pipx..."; \
			pipx install --force clang-format; \
		else \
			echo "clang-format version is 20 or higher. No action needed."; \
		fi; \
	else \
		echo "clang-format not found. Installing via pipx..."; \
		pipx install clang-format; \
	fi

test_cppcheck :
	@echo "┏=========================================┓"
	@echo "┃                                         ┃"
	@echo "┃         RUNNING CPPCHECK                ┃"
	@echo "┃                                         ┃"
	@echo "┗=========================================┛"
	cppcheck --enable=all --inconclusive --std=c++20 --force --inline-suppr --max-configs=100 --quiet --language=c++\
		--suppress=missingIncludeSystem \
		--error-exitcode=0 \
		src/**/*.h

___create_bin_headers___ : clean format_google_style
	@echo "┏=========================================┓"
	@echo "┃                                         ┃"
	@echo "┃           CREATE BIN HEADERS            ┃"
	@echo "┃                                         ┃"
	@echo "┗=========================================┛"
	@$(MKDIR_EXISTING) $(BIN_CONTAINERS)
	@cp src/lib/s21_containers.h bin/
	@for d in src/lib/containers/*; do \
		if [ -d "$$d" ]; then \
			mkdir -p $(BIN_CONTAINERS)$$(basename $$d); \
			find "$$d" -maxdepth 1 -type f -name '*.h' -exec cp {} $(BIN_CONTAINERS)$$(basename $$d)/ \; ; \
		fi \
	done


PREFIX ?= /usr/local
INCLUDE_DIR := $(PREFIX)/include/s21_containers

PREFIX ?= /usr/local
INCLUDE_DIR := $(PREFIX)/include/s21_containers

install_headers : format_google_style ___create_bin_headers___
	@echo "┏=========================================┓"
	@echo "┃                                         ┃"
	@echo "┃      INSTALLING HEADERS SYSTEM-WIDE     ┃"
	@echo "┃                                         ┃"
	@echo "┗=========================================┛"
	sudo mkdir -p $(INCLUDE_DIR)
	sudo cp bin/s21_containers.h $(INCLUDE_DIR)/
	@for d in bin/containers/*; do \
		if [ -d "$$d" ]; then \
			sudo mkdir -p $(INCLUDE_DIR)/containers/$$(basename $$d); \
			sudo cp $$d/*.h $(INCLUDE_DIR)/containers/$$(basename $$d)/; \
		fi \
	done
	sudo chmod -R a+rX $(INCLUDE_DIR)

uninstall_headers :
	@echo "┏=========================================┓"
	@echo "┃                                         ┃"
	@echo "┃       REMOVING SYSTEM-WIDE HEADERS      ┃"
	@echo "┃                                         ┃"
	@echo "┗=========================================┛"
	sudo rm -rf $(INCLUDE_DIR)

test_clang_tidy : ___check_install_clang_tidy___ ___generate_compdb___
	@echo "┏=========================================┓"
	@echo "┃                                         ┃"
	@echo "┃            RUNNING CLANG-TIDY           ┃"
	@echo "┃                                         ┃"
	@echo "┗=========================================┛"
	find src/lib -type f \( -name "*.h" \) -print0 | xargs -0 clang-tidy \
		--extra-arg=-std=c++20 \
		--extra-arg=-I/usr/include/c++/11 \
		--extra-arg=-I/usr/include/x86_64-linux-gnu/c++/11 \
		--checks=-llvmlibc-restrict-system-libc-headers \
		--checks='*,\
        -abseil-*,\
        -altera-*,\
        -cppcoreguidelines-*,\
        -clang-analyzer-*,\
        -concurrency-*,\
        -diagnostic-*,\
        -google-*,\
        -hicpp-*,\
        -llvm-*,\
        -modernize-*,\
        -performance-*,\
        -portability-*,\
        -readability-*,\
        -bugprone-*'

___generate_compdb___ : clean
	@echo "┏=========================================┓"
	@echo "┃                                         ┃"
	@echo "┃           GENERATING COMPDB             ┃"
	@echo "┃                                         ┃"
	@echo "┗=========================================┛"
	@if [ ! -f "build/compile_commands.json" ]; then \
		echo "Generating compile_commands.json..."; \
		cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON; \
		ln -sf build/compile_commands.json .; \
	fi

___check_install_clang_tidy___ : ___check_pipx_installed___
	echo "Checking clang-tidy..."; \
	if command -v clang-tidy >/dev/null 2>&1; then \
	    VERSION=$$(clang-tidy --version | grep -oE '[0-9]+(\.[0-9]+)*' | head -1 | cut -d. -f1); \
	    echo "Found clang-tidy version $$VERSION"; \
	    if [ "$$VERSION" -lt 20 ]; then \
	        echo "clang-tidy version is less than 20. Installing latest via pipx..."; \
	        pipx install --force clang-tidy; \
	    else \
	        echo "clang-tidy version is 20 or higher. No action needed."; \
	    fi; \
	else \
	    echo "clang-tidy not found. Installing via pipx..."; \
	    pipx install clang-tidy; \
	fi

___check_pipx_installed___ :
	@if ! command -v pipx >/dev/null 2>&1; then \
		echo "pipx not found. Installing pipx..."; \
		sudo apt update && sudo apt install -y pipx; \
		pipx ensurepath; \
		. ~/.bashrc || true; \
		echo "pipx installation completed."; \
	else \
		echo "pipx is already installed."; \
	fi

create_tar_headers : ___create_bin_headers___
	@echo "┏=========================================┓"
	@echo "┃                                         ┃"
	@echo "┃        CREATING bin HEADERS TARBALL     ┃"
	@echo "┃                                         ┃"
	@echo "┗=========================================┛"
	tar -cvf $(TAR_FILE) bin