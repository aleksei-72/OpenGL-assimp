#include <map>
#include <src/gl/texture.h>
#include <src/3d/model/Model.h>
#include <src/3d/gameObject/GameObject.h>

extern std::map<std::string, Texture> textureStorage;
extern std::map<std::string, Model> modelStorage;
extern std::map<std::string, Object> objectStorage;


Texture *getTexture(std::string fname);
Model *getModel(std::string name);
Object *get3dObject(std::string name);
