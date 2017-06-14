#include <stddef.h>
#include "WakeEngine.h"
#include "Key.hpp"

WakeEngine* WakeEngine::m_pInstance = NULL;

WakeEngine* WakeEngine::Instance() {
	if(!m_pInstance)
		m_pInstance = new WakeEngine;
	return m_pInstance;
}

void WakeEngine::init(std::string settingsFile) {


	srand (time(NULL));

	log = Logger::Instance();
	settings = Settings::Instance();

	log->writeLine("Initializing WakeEngine");
	settings->loadFile(settingsFile);
	settings->loadFile("keys.conf");
	bindKeyConversions(engineKeyConversion);

	log->writeLine("Starting up SDL");
	SDL_Init(SDL_INIT_EVERYTHING);

	// Display size stuff
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);
	//std::cout << "width:" << current.w << "\theight:" << current.h << std::endl;
	settings->setI("resX",current.w);
	settings->setI("resY",current.h);

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
			   SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALLOW_HIGHDPI
			   );
	SDL_ShowCursor(SDL_DISABLE);

	if(settings->s("fullscreen") == "yes")
	 	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	if(window == NULL) {
		log->writeLine("ERROR: Could not create window");
		log->writeLine("Settings file is corrupt or drivers need to be updated");
		log->closeLogFile();
		exit(-1);
	}
	SDL_Joystick* gGameController = NULL;
	//Check for joysticks
	if( SDL_NumJoysticks() < 1 ) {
		printf( "Warning: No joysticks connected!\n" );
	} else { //Load joystick
		gGameController = SDL_JoystickOpen( 0 );
		if( gGameController == NULL ) {
			printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
		}
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

std::string WakeEngine::getKeyCommand(SDL_Keycode key) {
	//std::cout << engineKeyConversion[SDLK_0] << std::endl;
	return settings->s( engineKeyConversion[key] );
}
