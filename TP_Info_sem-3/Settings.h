#ifndef SETTINGS_H
	#define SETTINGS_H

	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include <math.h>
	#include <time.h>
	#include <string.h>
	#include <assert.h>

	#define BASIC_RUN
	//#define BONUS
	//#define FOR_MOODLE

	#ifdef BASIC_RUN
		#define SPLIT_INITIAL
		#define ENSACHAGE_INITIAL

	#else
		
		#ifdef BONUS
			#define DATASET_MAISON
			#define SAVE
			#define SPLIT_INITIAL
			//#define ENSACHAGE_INITIAL

		#else	
			#define SPLIT_INITIAL
			//#define ENSACHAGE_INITIAL
		
		#endif		

	#endif

#endif
