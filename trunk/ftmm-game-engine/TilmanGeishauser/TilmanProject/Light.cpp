#include "Light.h"

Light::~Light()
{
}

void Light::setType(LightTypes type)
    {
        m_light_type = type;
    }

Light::LightTypes Light::getType(void) const
    {
        return m_light_type;
    }

void Light::setPosition(float x, float y, float z)
    {
        m_position.x = x;
        m_position.y = y;
        m_position.z = z;
//        mDerivedTransformDirty = true;
//		mDerivedCamRelativeDirty = true;

    }

void Light::setPosition(const Vector3& vec)
    {
        m_position = vec;
//        mDerivedTransformDirty = true;
//		mDerivedCamRelativeDirty = true;
    }

const Vector3& Light::getPosition(void) const
    {
        return m_position;
    }

void Light::setDirection(float x, float y, float z)
    {
        m_direction.x = x;
        m_direction.y = y;
        m_direction.z = z;
//        mDerivedTransformDirty = true;
    }

void Light::setDirection(const Vector3& vec)
    {
        m_direction = vec;
//        mDerivedTransformDirty = true;
    }

const Vector3& Light::getDirection(void) const
    {
        return m_direction;
    }

void Light::setDiffuseColour(float red, float green, float blue)
    {
        m_diffuse.x = red;
        m_diffuse.y = blue;
        m_diffuse.z = green;
    }

