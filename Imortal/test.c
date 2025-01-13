// #include <stdio.h>
// #include <signal.h>
// #include <unistd.h>
// #include <string.h>
// #include <stdlib.h>

// // Gestionnaire de signal
// void handle_signal(int signal) {
// 	if (signal == SIGINT) {
// 		printf("Signal SIGINT reçu\n");
// 		// exit(0); // Utilisation de exit() pour un nettoyage approprié
// 	} else if (signal == SIGTERM) {
// 		printf("Signal SIGTERM reçu\n");
// 		exit(0); // Utilisation de exit() pour un nettoyage approprié
// 	}
// }

// int main()
// {
// 	// Configurer le gestionnaire de signal pour SIGTERM et SIGINT
// 	struct sigaction sa;
// 	sa.sa_handler = handle_signal;
// 	sa.sa_flags = SA_SIGINFO; // Pas d'options supplémentaires
// 	sigemptyset(&sa.sa_mask); // Pas de masquage supplémentaire de signaux
// 	// sigaction(SIGTERM, &sa, NULL);
// 	// sigaction(SIGINT, &sa, NULL); // Ajouter cette ligne pour gérer SIGINT

// 	int i = 0;
// 	while (i < 65)
// 		sigaction(i++, &sa, NULL);
// 	printf("En attente de signaux...\n");

// 	// Boucle infinie pour garder le programme en exécution
// 	while (1) {
// 		pause(); // Attendre un signal
// 	}

// 	return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signo, siginfo_t *info, void *context) {
    if (info != NULL) {
        printf("Signal reçu : %d\n", signo);
        printf("PID de l'émetteur : %d\n", info->si_pid);
		printf("UID de l'émetteur : %d\n", info->si_uid);
		printf("Code de la cause du signal : %d\n", info->si_code);
		printf("Valeur du signal : %d\n", info->si_value.sival_int);
		printf("Adresse de la mémoire qui a causé le signal : %p\n", info->si_addr);
		printf("Numéro de la trappe matérielle qui a causé le signal : %d\n", info->si_errno);
		printf("Numéro de l'erreur (si applicable) : %d\n", info->si_errno);
		printf("Statut de la terminaison de l'enfant : %d\n", info->si_status);
	}
	else 
	{
			printf("Signal reçu : %d\n", signo);
			printf("Impossible d'obtenir des informations supplémentaires.\n");
		}
}

int main() {
    struct sigaction sa;

    // Configure le gestionnaire de signal
    sa.sa_sigaction = signal_handler; // Définit la fonction de gestion
    sa.sa_flags = SA_SIGINFO;         // Permet d'obtenir des informations détaillées sur le signal
	sigaction(SIGINT, &sa, NULL);
    // Intercepter SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Erreur lors de l'installation du gestionnaire de signal");
        exit(EXIT_FAILURE);
    }

    printf("PID du processus actuel : %d\n", getpid());
    printf("En attente d'un signal...\n");

    // Boucle infinie pour garder le programme actif
    while (1) {
        pause(); // Attend un signal
    }

    return 0;
}
