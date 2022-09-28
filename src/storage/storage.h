#include <map>
#include <src/gl/texture.h>
#include <src/3d/model/Model.h>

extern std::map<std::string, Texture> textureStorage;
extern std::map<std::string, Model> modelStorage;

Texture *getTexture(std::string fname);
Model *getModel(std::string fname, std::string texture);
