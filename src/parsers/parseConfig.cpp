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

#define setParameter(code) try \
{ \
    code; \
} \
catch (inicpp::not_found_exception &e) \
{ \
    logger.error(e.what()); \
} \
catch (inicpp::bad_cast_exception &e) \
{ \
    logger.error(e.what()); \
    exit (1); \
} \



config parseFile(string fname);


void parseInitConfig(string fname)
{
    config conf = parseFile(fname);

    setParameter(pathSettings.basePath = conf["path"]["base"].get<string>());
    setParameter(pathSettings.configPath = conf["path"]["config"].get<string>());
    setParameter(pathSettings.meshPath = conf["path"]["mesh"].get<string>());
    setParameter(pathSettings.shaderPath = conf["path"]["shader"].get<string>());
    setParameter(pathSettings.texturePath = conf["path"]["texture"].get<string>());
}

void parseGraphicsConfig(string fname)
{
    config conf = parseFile(fname);

    setParameter(graphicSettings.doubleBufferization = conf["graphics"]["doubleBufferization"].get<bool>());
    setParameter(graphicSettings.fov = conf["graphics"]["fov"].get<double>());
    setParameter(graphicSettings.renderDistance = conf["graphics"]["renderDistance"].get<double>());

    setParameter(graphicSettings.isFullScreen = conf["graphics"]["fullscreen"].get<bool>());

    setParameter(graphicSettings.startWindowResolution.x = conf["graphics"]["windowW"].get<int64_t>());
    setParameter(graphicSettings.startWindowResolution.y = conf["graphics"]["windowH"].get<int64_t>());

    setParameter(graphicSettings.startWindowPosition.x = conf["graphics"]["windowX"].get<int64_t>());
    setParameter(graphicSettings.startWindowPosition.y = conf["graphics"]["windowY"].get<int64_t>());
}

void parsePlayerConfig(string fname)
{
    config conf = parseFile(fname);

    setParameter(playerSettings.speed = conf["player"]["speed"].get<double>());
    setParameter(playerSettings.speed = conf["player"]["speedBoost"].get<double>());
}

void parseOtherConfig(string fname)
{
    config conf = parseFile(fname);

    setParameter(usersSettings.cursorSensivity = conf["cursor"]["sensivity"].get<double>());
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
