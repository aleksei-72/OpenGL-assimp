#include <src/public/public.h>

#include <tinyxml.h>
#include <tinystr.h>
#include <glm/vec3.hpp>
#include <src/3d/mesh/Mesh.h>
#include <src/3d/mesh/simpleMeshes.h>

#include <iostream>

using namespace std;

void parseObjectTypes(TiXmlElement * head);
void spamnObjectsFromXML(TiXmlElement * head);


bool fileExists(string fname)
{
    ifstream fstr;
    fstr.open(fname);

    if(!fstr)
    {
        fstr.close();
        return false;
    }
    fstr.close();
    return true;
}

void parseLevel(string fname)
{
    string filePath = pathSettings.basePath + pathSettings.xmlPath + fname;
    if (!fileExists(filePath))
    {
        logger_error("Fail for open file '" + filePath + "'", "");
        return;
    }

    TiXmlDocument file(filePath.c_str());
    if(!file.LoadFile())
    {
        logger_error("error for opem file '" + filePath + "'", "");
        return;
    }

    TiXmlElement *objectTypes = file.FirstChildElement("objects_types");
    TiXmlElement *objects = file.FirstChildElement("objects");

    if (!objectTypes)
    {
        logger_error_and_abort("section 'objects_types' not found", "");
    }

    if (!objects)
    {
        logger_error_and_abort("section 'objects' not found", "");
    }

    {
        Mesh mesh(generateCube(1.f));
        mesh.diffuseTextures.push_back(manager.getTexture("default.png"));

        Model m;
        m.meshes.push_back(mesh);
        manager.addModel("cube", m);

        Object o;
        o.model = manager.getModel("cube");
        o.physicsMode = none;

        manager.addObject("cube", o);
    }

    {
        Mesh mesh(generatePlain(1.f));
        mesh.diffuseTextures.push_back(manager.getTexture("default.png"));

        Model m;
        m.meshes.push_back(mesh);
        manager.addModel("plain", m);

        Object o;
        o.model = manager.getModel("plain");
        o.physicsMode = none;

        manager.addObject("plain", o);
    }


    parseObjectTypes(objectTypes);
    spamnObjectsFromXML(objects);
}

void parseObjectTypes(TiXmlElement * head)
{
    TiXmlElement *element = head->FirstChildElement("object");
    while (element)
    {
        const char *attrId = element->Attribute("id"),
            *attrMesh = element->Attribute("mesh"),
            *attrHitbox = element->Attribute("hitbox"),
            *attrScale = element->Attribute("scale"),
            *attrPhysics = element->Attribute("physics");

        if (!attrId)
            logger_error_and_abort("attribute 'id' is requered", "row: " + to_string(element->Row()));

        if (!attrMesh)
            logger_error_and_abort("attribute 'mesh' is requered", "row: " + to_string(element->Row()));

        if (!attrPhysics)
            logger_error_and_abort("attribute 'physics' is requered", "row: " + to_string(element->Row()));

        if (!attrScale)
            attrScale = "1.0";


        physicsMode physics = none;
        float scale = 1.f;

        if (string(attrPhysics) == "solidBoby")
            physics = solidBoby;

        if (physics == solidBoby && !attrHitbox)
            logger_error_and_abort("the 'physics' attribute value is 'solidBoby' and has no 'hitbox' attribute - incompatible", "row: " + to_string(element->Row()))

        try {
            scale = stof(string(attrScale));
        } catch (...) {
            logger_error("fail for convert attr 'scale' to float. Use default 1.0", "row: " + to_string(element->Row()));
        }


        // @TODO: load hitbox
        Model model(string(attrMesh), scale);
        manager.addModel(string(attrMesh), model);

        Object object;
        object.model = manager.getModel(string(attrMesh));
        object.hitbox = nullptr;
        object.physicsMode = physics;

        manager.addObject(string(attrId), object);

        element = element->NextSiblingElement("object");
    }
}

void spamnObjectsFromXML(TiXmlElement * head)
{
    TiXmlElement *element = head->FirstChildElement("object");
    while (element)
    {
        const char *attrType = element->Attribute("type"),
            *attrX = element->Attribute("x"),
            *attrY = element->Attribute("y"),
            *attrZ = element->Attribute("z"),
            *attrRx = element->Attribute("rx"),
            *attrRy = element->Attribute("ry"),
            *attrRz = element->Attribute("rz");

        if (!attrType)
            logger_error_and_abort("attribute 'type' is requered", "row: " + to_string(element->Row()));

        if (!attrX)
            logger_error_and_abort("attribute 'x' is requered", "row: " + to_string(element->Row()));

        if (!attrY)
            logger_error_and_abort("attribute 'y' is requered", "row: " + to_string(element->Row()));

        if (!attrZ)
            logger_error_and_abort("attribute 'z' is requered", "row: " + to_string(element->Row()));


        if (!attrRx)
            attrRx = "0.0";


        if (!attrRy)
            attrRy = "0.0";


        if (!attrRz)
            attrRz = "0.0";

\
        vec3 position = {0, 0, 0},
            turning = {0, 0, 0};

        try
        {
            position = {atof(attrX), atof(attrY), atof(attrZ)};
        } catch (...)
        {
            logger_error_and_abort("invalid value of attribute 'x', 'y' or 'z'", "row: " + to_string(element->Row()));
        }

        try
        {
            turning = {atof(attrRx), atof(attrRy), atof(attrRz)};
        } catch (...)
        {
            logger_error_and_abort("invalid value of attribute 'rx', 'ry' or 'rz'", "row: " + to_string(element->Row()));
        }

        manager.spawn(string(attrType), position, turning);

        element = element->NextSiblingElement("object");
    }
}
