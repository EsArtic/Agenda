Objects=Date.o\
       Meeting.o\
       User.o\
       Storage.o\
       AgendaService.o\
       AgendaUI.o\
       log.o\
       Reload.o
EXCE=main.out
CC=g++
$(EXCE):Agenda.cpp Date.o Meeting.o User.o Storage.o Reload.o log.o AgendaService.o AgendaUI.o
	$(CC) -std=c++0x -o $(EXCE) Agenda.cpp Date.o Meeting.o User.o Storage.o Reload.o log.o AgendaService.o AgendaUI.o

Reload.o:Reload.cpp
	$(CC) -std=c++0x -c Reload.cpp
log.o:log.cpp
	$(CC) -std=c++0x -c log.cpp
AgendaService.o:AgendaService.cpp
	$(CC) -std=c++0x -c AgendaService.cpp
AgendaUI.o:AgendaUI.cpp
	$(CC) -std=c++0x -c AgendaUI.cpp
Storage.o:Storage.cpp
	$(CC) -std=c++0x -c Storage.cpp
Date.o:Date.cpp
	$(CC) -std=c++0x -c Date.cpp
Meeting.o:Meeting.cpp
	$(CC) -std=c++0x -c Meeting.cpp
User.o:User.cpp
	$(CC) -std=c++0x -c User.cpp
clean:
	rm $(Objects) main.out *~
