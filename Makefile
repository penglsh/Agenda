CC := g++
F := -std=c++11 -w
BIN := bin
BUI := build
IN := include
SRC := src
INCLUDE := -I./$(IN)

$(BIN)/main: $(BUI)/main.o $(BUI)/Date.o $(BUI)/User.o $(BUI)/Meeting.o $(BUI)/Storage.o $(BUI)/AgendaService.o $(BUI)/AgendaUI.o
	@mkdir -p $(BIN)
	$(CC) $(F) $(INCLUDE) $^ -o $@

$(BUI)/main.o: $(SRC)/main.cpp
	@mkdir -p $(BUI)
	$(CC) $(F) $(INCLUDE) -c -o $@ $(SRC)/main.cpp

$(BUI)/Date.o: $(SRC)/Date.cpp
	@mkdir -p $(BUI)
	$(CC) $(F) $(INCLUDE) -c -o $@ $(SRC)/Date.cpp

$(BUI)/User.o: $(SRC)/User.cpp
	@mkdir -p $(BUI)
	$(CC) $(F) $(INCLUDE) -c -o $@ $(SRC)/User.cpp

$(BUI)/Meeting.o: $(SRC)/Meeting.cpp
	@mkdir -p $(BUI)
	$(CC) $(F) $(INCLUDE) -c -o $@ $(SRC)/Meeting.cpp

$(BUI)/Storage.o: $(SRC)/Storage.cpp
	@mkdir -p $(BUI)
	$(CC) $(F) $(INCLUDE) -c -o $@ $(SRC)/Storage.cpp

$(BUI)/AgendaUI.o: $(SRC)/AgendaUI.cpp
	@mkdir -p $(BUI)
	$(CC) $(F) $(INCLUDE) -c -o $@ $(SRC)/AgendaUI.cpp

$(BUI)/AgendaService.o: $(SRC)/AgendaService.cpp
	@mkdir -p $(BUI)
	$(CC) $(F) $(INCLUDE) -c -o $@ $(SRC)/AgendaService.cpp

clean :
	@rm -rf $(BIN)
	@rm -rf $(BUI)