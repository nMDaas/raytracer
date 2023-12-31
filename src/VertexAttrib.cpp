#include "VertexAttrib.h"

VertexAttrib::VertexAttrib()
{
    position = glm::vec4(0,0,0,1);
    normal = glm::vec4(0,0,0,0);
    texcoord = glm::vec4(0,0,0,1);
}

VertexAttrib::~VertexAttrib(){}

bool VertexAttrib::hasData(string attribName)
{

    if ((attribName == "position")
            || (attribName == "normal")
            || (attribName == "texcoord"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

vector<float> VertexAttrib::getData(string attribName)
    {
        vector<float> result;
        stringstream message;


        if (attribName == "position")
        {
            result.push_back(position.x);
            result.push_back(position.y);
            result.push_back(position.z);
            result.push_back(position.w);
        }
        else if (attribName == "normal")
        {
            result.push_back(normal.x);
            result.push_back(normal.y);
            result.push_back(normal.z);
            result.push_back(normal.w);
        }
        else if (attribName == "texcoord")
        {
            result.push_back(texcoord.x);
            result.push_back(texcoord.y);
            result.push_back(texcoord.z);
            result.push_back(texcoord.w);
        }
        else
        {
            message << "No attribute: " << attribName << " found!";
            throw runtime_error(message.str());
        }

        return result;
    }

void VertexAttrib::setData(string attribName, const vector<float>& data)
    {
        stringstream message;

        if (attribName == "position")
        {
            position = glm::vec4(0,0,0,1);
            switch (data.size()) {
            case 4: position.w = data[3];
            case 3: position.z = data[2];
            case 2: position.y = data[1];
            case 1: position.x = data[0];
                break;
            default:
                message << "Too much data for attribute: " << attribName;
                throw runtime_error(message.str());
            }
        }
        else if (attribName == "normal")
        {
            normal = glm::vec4(0,0,0,0);
            switch (data.size()) {
            case 4: normal.w = data[3];
            case 3: normal.z = data[2];
            case 2: normal.y = data[1];
            case 1: normal.x = data[0];
                break;
            default:
                message << "Too much data for attribute: " << attribName;
                throw runtime_error(message.str());
            }
        }
        else if (attribName == "texcoord")
        {
            texcoord = glm::vec4(0,0,0,1);
            switch (data.size()) {
            case 4: texcoord.w = data[3];
            case 3: texcoord.z = data[2];
            case 2: texcoord.y = data[1];
            case 1: texcoord.x = data[0];
                break;
            default:
                message << "Too much data for attribute: " << attribName;
                throw runtime_error(message.str());
            }
        }
        else
        {
            message << "Attribute: " << attribName << " unsupported!";
            throw runtime_error(message.str());
        }
    }

    vector<string> VertexAttrib::getAllAttributes()
    {
        vector<string> attributes;

        attributes.push_back("position");
        attributes.push_back("normal");
        attributes.push_back("texcoord");
        return attributes;
    }