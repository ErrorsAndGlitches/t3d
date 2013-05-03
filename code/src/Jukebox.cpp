#include "Jukebox.h"
#include "Defs.h"

Jukebox* Jukebox::jukeboxInstance = NULL;

static void musicFinishedHook() 
{
	Jukebox *jb = Jukebox::getJukeboxInstance();
	jb->playNextTrack();
}

void Jukebox::cleanupMusic()
{
	Mix_HaltMusic();
	Mix_FreeMusic(music);
	music = NULL;
}

Jukebox::Jukebox(): music(NULL), playlist(new std::vector<std::string>()), 
	trackNumber(0), jbMode(JukeboxMode::LOOP_ALL), 
	randEng(RandomEngine::getRandomEngineInstance())
{
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(AUDIO_RATE, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFER);
	Mix_HookMusicFinished(musicFinishedHook);
}

Jukebox::~Jukebox()
{
	SDL_Quit();
	delete(playlist);
	playlist = NULL;
}

void Jukebox::nextTrack()
{
	++trackNumber;
	if (playlist->size() == trackNumber) { trackNumber = 0; }
}

void Jukebox::loadCurrentTrack()
{
	music = Mix_LoadMUS((*playlist)[trackNumber].c_str());
}

void Jukebox::playCurrentTrack()
{
	Mix_PlayMusic(music, 0); // play once
}

Jukebox* Jukebox::getJukeboxInstance()
{
	if (!jukeboxInstance) { jukeboxInstance = new Jukebox(); }
	return Jukebox::jukeboxInstance;
}

void Jukebox::addToPlaylist(const char *filename)
{
	playlist->push_back(filename);
}

void Jukebox::clearPlaylist()
{
	playlist->clear();
	trackNumber = 0;
}

std::vector<std::string> Jukebox::getPlaylist()
{
	return *playlist;
}

void Jukebox::setJukeboxMode(JukeboxMode mode)
{
	jbMode = mode;
}

Jukebox::JukeboxMode Jukebox::getJukeboxMode()
{
	return jbMode;
}

void Jukebox::playNextTrack()
{
	// do the cleaning up if we need to
	if (music) {
		cleanupMusic();
	}

	// update the current track and play next song if necessary
	switch (jbMode) {
		case SINGLE:
			nextTrack();
			break;
		case NO_LOOP:
			// check if we have not finished the playlist
			if (trackNumber + 1 < playlist->size()) {
				nextTrack();
				loadCurrentTrack();
				playCurrentTrack();
			}
			break;
		case LOOP_ONE:
			if (trackNumber < playlist->size()) {
				loadCurrentTrack();
				playCurrentTrack();
			}
			break;
		case LOOP_ALL:
			nextTrack();
			loadCurrentTrack();
			playCurrentTrack();
			break;
		case SHUFFLE:
			setCurrentTrack(randEng->getRandomInt(0, playlist->size() - 1));
			break;
	}
}

void Jukebox::playMusic() 
{
	// check if a track is already loaded
	if (music) {
		playCurrentTrack();
	}
	else {
		// check to make sure the track number is valid
		if (trackNumber >= playlist->size()) { return; }

		// make a check for shuffle
		if (JukeboxMode::SHUFFLE == jbMode) { 
			setCurrentTrack(randEng->getRandomInt(0, playlist->size() - 1));
		}

		loadCurrentTrack();
		playCurrentTrack();
	}
}

void Jukebox::setCurrentTrack(int trackNumber)
{
	if (playlist->size() <= trackNumber) { return; }
	if (music) { cleanupMusic(); }

	this->trackNumber = trackNumber;

	loadCurrentTrack();
	playCurrentTrack();
}

void Jukebox::toggleMusic()
{
	if (music) {
		if (Mix_PausedMusic()) { Mix_ResumeMusic(); }
		else { Mix_PauseMusic(); }
	}
}

void Jukebox::pauseMusic() 
{
	if (music && !Mix_PausedMusic()) {
		Mix_PauseMusic();
	}
}

void Jukebox::resumeMusic()
{
	if (music && Mix_PlayingMusic() && Mix_PausedMusic()) {
		Mix_ResumeMusic();
	}
}
