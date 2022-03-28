CLIENT = client
SERVEUR = serveur


all:$(CLIENT) $(SERVEUR) 

$(CLIENT): $(CLIENT).c calcul.h
	gcc -o $(CLIENT) $(CLIENT).c

$(SERVEUR): $(SERVEUR).c calcul.h
	gcc -o $(SERVEUR) $(SERVEUR).c

clean:
	rm *.o
