#ifndef DEFS_H
#define DEFS_H
/**
 * @file
 * @brief This file provides a set of defines and macros
 */

#define MUSIC_FILENAME "data/beginning.mp3"


#define AUDIO_RATE 22050
#define AUDIO_FORMAT AUDIO_S16
#define AUDIO_CHANNELS 2
#define AUDIO_BUFFER 131072

#define DEFAULT_SUBARENA_LENGTH 5
#define DEFAULT_SUBARENA_HEIGHT 12

#define LOSING_TEXT "You sad excuse for a T3D player. YOU LOST!!"
#define WINNING_TEXT "The force is strong with you.\n\nYour T3D powers have won you\na great VICTORY!"

typedef enum {
	RUNNING,
		LOST,
		WON,
		NUMBER_GAME_STATES
} GameState;

#endif
