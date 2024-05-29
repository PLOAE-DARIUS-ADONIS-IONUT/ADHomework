.PHONY: all clean

# Define the Python interpreter
PYTHON := python

# Define the source files
SRCS := main.py lobster.py

# Define the input and output files
INPUT := input.txt
OUTPUT := output.txt

# Define the default target
all: $(OUTPUT)

# Rule to generate the output file
$(OUTPUT): $(SRCS) $(INPUT)
	$(PYTHON) main.py $(INPUT)

# Rule to clean up generated files
clean:
	rm -f $(OUTPUT)
