#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <src/public/public.h>

#include <fstream>
#include <sstream>
#include <inicpp/inicpp.h>

using namespace std;

using namespace inicpp;
using namespace std::literals;

#define IGNORE_EXCEPTIONS try {
#define IGNORE_EXCEPTIONS_END } catch (...) {}

#define safeSaveParameter(code) try \
{ \
    code; \
} \
catch (inicpp::not_found_exception &e) \
{ \
    logger_error(e.what(), ""); \
} \
catch (inicpp::bad_cast_exception &e) \
{ \
    logger_error(e.what(), ""); \
    exit (1); \
} \



config parseFile(string fname);


void parseInitConfig(string fname)
{
    config conf = parseFile(fname);

    safeSaveParameter(pathSettings.basePath = conf["path"]["base"].get<string>());
    safeSaveParameter(pathSettings.configPath = conf["path"]["config"].get<string>());
    safeSaveParameter(pathSettings.meshPath = conf["path"]["mesh"].get<string>());
    safeSaveParameter(pathSettings.shaderPath = conf["path"]["shader"].get<string>());
    safeSaveParameter(pathSettings.texturePath = conf["path"]["texture"].get<string>());
}

void parseGraphicsConfig(string fname)
{
    config conf = parseFile(fname);

    safeSaveParameter(graphicSettings.doubleBufferization = conf["graphics"]["doubleBufferization"].get<bool>());
    safeSaveParameter(graphicSettings.fov = conf["graphics"]["fov"].get<double>());
    safeSaveParameter(graphicSettings.renderDistance = conf["graphics"]["renderDistance"].get<double>());

    safeSaveParameter(graphicSettings.isFullScreen = conf["graphics"]["fullscreen"].get<bool>());

    safeSaveParameter(graphicSettings.startWindowResolution.x = conf["graphics"]["windowW"].get<int64_t>());
    safeSaveParameter(graphicSettings.startWindowResolution.y = conf["graphics"]["windowH"].get<int64_t>());

    safeSaveParameter(graphicSettings.startWindowPosition.x = conf["graphics"]["windowX"].get<int64_t>());
    safeSaveParameter(graphicSettings.startWindowPosition.y = conf["graphics"]["windowY"].get<int64_t>());
}

void parsePlayerConfig(string fname)
{
    config conf = parseFile(fname);

    safeSaveParameter(playerSettings.speed = conf["player"]["speed"].get<double>());
    safeSaveParameter(playerSettings.speed = conf["player"]["speedBoost"].get<double>());
}

void parseOtherConfig(string fname)
{
    config conf = parseFile(fname);

    safeSaveParameter(usersSettings.cursorSensivity = conf["cursor"]["sensivity"].get<double>());
}

config parseFile(string fname)
{
        ifstream stream;
    stream.open(pathSettings.basePath + pathSettings.configPath + fname);

    if (!stream.is_open())
        throw std::runtime_error("fail for open file '" + fname + '\'');

    stringstream ss;
    ss << stream.rdbuf();

    return parser::load(ss.str());
}
