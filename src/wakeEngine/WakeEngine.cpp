#include <stddef.h>
#include "WakeEngine.h"

WakeEngine* WakeEngine::m_pInstance = NULL;

WakeEngine* WakeEngine::Instance() {
	if(!m_pInstance)
		m_pInstance = new WakeEngine;
	return m_pInstance;
}

void WakeEngine::init(std::string settingsFile) {

	log = Logger::Instance();
	settings = Settings::Instance();

	log->writeLine("Initializing WakeEngine");
	settings->loadFile(settingsFile);

	log->writeLine("Starting up SDL");
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	log->writeLine("Creating Window");
	window = SDL_CreateWindow(
			   settings->s("program").c_str(),
			   SDL_WINDOWPOS_UNDEFINED,
			   SDL_WINDOWPOS_UNDEFINED,
			   settings->i("resX"),
			   settings->i("resY"),
			   SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE
			   );

	if(settings->s("fullscreen") == "yes")
	 	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	if(window == NULL) {
		log->writeLine("ERROR: Could not create window");
		log->writeLine("Settings file is corrupt or drivers need to be updated");
		log->closeLogFile();
		exit(-1);
	}

	log->writeLine("Creating OpenGL Context");
	gl = SDL_GL_CreateContext(window);


	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glDepthFunc(GL_LESS);



}

void WakeEngine::shutdown() {
	// Get rid of mesh data
	std::map<std::string, Mesh*>::iterator i = this->mesh.begin();
	for(;i!=this->mesh.end(); ++i) {
		//Mix_FreeChunk(this->mesh[i->first]);
		this->mesh[i->first] = NULL;
	}

	Logger::Instance()->closeLogFile();
	audio.close();
	while(Mix_Init(0))
    Mix_Quit();

	SDL_GL_DeleteContext(this->gl);
	SDL_DestroyWindow(this->window);
	SDL_Quit();

}
