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
	//#define BONUS
	//#define FOR_MOODLE
	#define CHEMIN_IMAGE_BMP "../Dataset/WrittingTest6.bmp"
	#define NOMBRE_ARBRES 20
	#define PRUNNING_THRESHOLD 1.0f
	#define MAX_DEPTH 30

	#ifdef BASIC_RUN
		#define SPLIT_INITIAL
		#define ENSACHAGE_INITIAL

	#else
		
		#ifdef BONUS
			#define DATASET_MAISON
			//#define SAVE
			#define SPLIT_INITIAL
			//#define ENSACHAGE_INITIAL

		#else	
			#define SPLIT_INITIAL
			//#define ENSACHAGE_INITIAL
		
		#endif		

	#endif

	#ifdef ENSACHAGE_INITIAL
		#define BAGGING_PROPORTION 0.5f

	#else
		#define BAGGING_PROPORTION 1.0f

	#endif

#endif
