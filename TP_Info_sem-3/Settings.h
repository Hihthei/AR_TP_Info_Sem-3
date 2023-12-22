#ifndef SETTINGS_H
	#define SETTINGS_H

	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include <math.h>
	#include <time.h>
	#include <string.h>
	#include <assert.h>

	//#define BASIC_RUN
	#define BONUS


	// PERMET DE REALISER UNE RUN POUR MOODLE (SORTIES SONT CELLES ATTENDUES PAR MOODLE)
	//#define FOR_MOODLE

	#ifdef BASIC_RUN
		#define SPLIT_INITIAL
		#define ENSACHAGE_INITIAL

	#else
		#ifdef MOODLE
			#define SPLIT_INITIAL
			//#define ENSACHAGE_INITIAL

		#else
		
			#ifdef BONUS
				// PERMET DE POUVOIR CREER SA PROPRE BASE DE DONNEE (image paint en .bmp), S'UTILISE UNIQUEMENT AVEC MNIST
				//#define DATASET_MAISON

				// PERMET DE POUVOIR SAUVEGARDER DES FORETS ET DE LES CHARGER AU LANCEMENT DU PROGRAMME
				//#define SAVE_LOAD

			#endif

				// ON PEUT PRENDRE LES DEUX, L'UN DES DEUX OU AUCUN
				
				// PAR DEFAUT (quand c'est commenter) : SPLIT AMELIORER - PLUS LENT MAIS MOINS DE NOEUDS
				//#define SPLIT_INITIAL
				
				// PAR DEFAUT (quand c'est commenter) : ENSACHAGE AMELIORER - ARBRE "PLUS COMPETENTS"
				//#define ENSACHAGE_INITIAL
		
		#endif		

	#endif



	// IL NE FAUT PAS DECOMMENTER :

	#define CHEMIN_IMAGE_BMP "../Dataset/WrittingTest6.bmp"
	#define NOMBRE_ARBRES 5
	#define PRUNNING_THRESHOLD 1.0f
	#define MAX_DEPTH 25

	#ifdef ENSACHAGE_INITIAL
		// ON PEUT CHANGER LA VALEUR DE LA BAGGING_PROPORTION
		#define BAGGING_PROPORTION 0.5f

	#else
		// IL NE FAUT PAS CHANGER LA VALEUR DE CELLE-CI
		#define BAGGING_PROPORTION 1.0f

	#endif

#endif
