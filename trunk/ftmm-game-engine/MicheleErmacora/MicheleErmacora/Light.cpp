#include "Light.h"

Light::Light(const std::string  & name, LightTypes type)
	{
		light_name = name;
		m_light_type = type;
		m_position = Vector3::ZERO;
		m_direction = Vector3::UNIT_Z;
		m_diffuse = Vector3::ZERO;
		m_specular = Vector3::UNIT_SCALE;
		m_range = 100000;
		m_attenuation_const = 1.0;
		m_attenuation_linear = 0.0;
		m_attenuation_quad = 0.0;
		m_spot_inner = 40.0f;
		m_spot_outer = 30.0f;
		m_spot_falloff = 1.0;
		m_power_scale = 0.0;
		m_visible = FALSE;
	}


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
    }

void Light::setPosition(const Vector3& vec)
    {
        m_position = vec;
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
    }

void Light::setDirection(const Vector3& vec)
    {
        m_direction = vec;
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

void Light::setSpecularColour(float red, float green, float blue)
    {
        m_specular.x = red;
        m_specular.y = blue;
        m_specular.z = green;
    }

void Light::setAttenuation(float range, float constant, float linear, float quadratic)
    {
        m_range = range;
        m_attenuation_const = constant;
        m_attenuation_linear = linear;
        m_attenuation_quad = quadratic;
    }
float Light::getAttenuationRange(void) const
    {
        return m_range;
    }

float Light::getAttenuationConstant(void) const
    {
        return m_attenuation_const;
    }

float Light::getAttenuationLinear(void) const
    {
        return m_attenuation_linear;
    }

float Light::getAttenuationQuadric(void) const
    {
        return m_attenuation_quad;
    }

void _calcTempSquareDist(const Vector3& worldPos);

void Light::setSpotlightRange(const Radian& innerAngle, const Radian& outerAngle, float falloff)
    {

        if (m_light_type != LT_SPOTLIGHT)
		{
			m_spot_inner =innerAngle;
			m_spot_outer = outerAngle;
			m_spot_falloff = falloff;
		}
    }

void Light::setSpotlightInnerAngle(const Radian& val)
	{
		m_spot_inner = val;
	}

void Light::setSpotlightOuterAngle(const Radian& val)
	{
		m_spot_outer = val;
	}

void Light::setSpotlightFalloff(float val)
	{
		m_spot_falloff = val;
	}

const Radian& Light::getSpotlightInnerAngle(void) const
    {
        return m_spot_inner;
    }

const Radian& Light::getSpotlightOuterAngle(void) const
    {
        return m_spot_outer;
    }

float Light::getSpotlightFalloff(void) const
    {
        return m_spot_falloff;
    }

void Light::setPowerScale(float power)
	{
		m_power_scale = power;
	}

float Light::getPowerScale(void) const
	{
		return m_power_scale;
	}

void Light::drawLight()
{
	glPushMatrix();
	glBegin(GL_TRIANGLES);

		glColor3f(1.0f,0.0f,0.0f);          // Red
		glVertex3f( 0.0f, 0.05f, 0.0f);          // Top Of Triangle (Front)
		glColor3f(0.0f,1.0f,0.0f);          // Green
		glVertex3f(-0.05f,-0.05f, 0.0f);          // Left Of Triangle (Front)
		glColor3f(0.0f,0.0f,1.0f);          // Blue
		glVertex3f( 0.05f,-0.05f, 0.0f);          // Right Of Triangle (Front)

		
		glColor3f(1.0f,0.0f,0.0f);          // Red
		glVertex3f( 0.0f, 0.05f, 0.0f);          // Top Of Triangle (Right)
		glColor3f(0.0f,0.0f,1.0f);          // Blue
		glVertex3f( 0.05f,-0.05f, 0.05f);          // Left Of Triangle (Right)
		glColor3f(0.0f,1.0f,0.0f);          // Green
		glVertex3f( 0.05f,-0.05f, -0.05f);         // Right Of Triangle (Right)

		glColor3f(1.0f,0.0f,0.0f);          // Red
		glVertex3f( 0.0f, 0.05f, 0.0f);          // Top Of Triangle (Back)
		glColor3f(0.0f,1.0f,0.0f);          // Green
		glVertex3f( 0.05f,-0.05f, -0.05f);         // Left Of Triangle (Back)
		glColor3f(0.0f,0.0f,1.0f);          // Blue
		glVertex3f(-0.05f,-0.05f, -0.05f);         // Right Of Triangle (Back)

		glColor3f(1.0f,0.0f,0.0f);          // Red
		glVertex3f( 0.0f, 0.05f, 0.0f);          // Top Of Triangle (Left)
		glColor3f(0.0f,0.0f,1.0f);          // Blue
		glVertex3f(-0.05f,-0.05f,-0.05f);          // Left Of Triangle (Left)
		glColor3f(0.0f,1.0f,0.0f);          // Green
		glVertex3f(-0.05f,-0.05f, 0.05f);          // Right Of Triangle (Left)
		
	glEnd();
	glPopMatrix();
}

void Light::update(void) const
{

}

void Light::setVisible()
{
	m_visible = TRUE;
}

void Light::translate(const Vector3& translation_value)
{
	m_position.x += translation_value.x;
	m_position.y += translation_value.y;
	m_position.z += translation_value.z;
}

void Light::rotate(const Vector3& axis, const Radian& angle)
{
	Matrix3 mat_rot = Matrix3::IDENTITY;

	mat_rot[0][0] = pow(axis.x,2) + (1 - pow(axis.x,2))* Math::Cos(angle);
	mat_rot[0][1] = (1 - Math::Cos(angle)) * axis.x * axis.y - Math::Sin(angle) * axis.z;
	mat_rot[0][2] = (1 - Math::Cos(angle)) * axis.x * axis.z + Math::Sin(angle) * axis.y;
	mat_rot[1][0] = (1 - Math::Cos(angle)) * axis.y * axis.x + Math::Sin(angle) * axis.z;
	mat_rot[1][1] = pow(axis.y,2) + (1 - pow(axis.y,2))* Math::Cos(angle);
	mat_rot[1][2] = (1 - Math::Cos(angle)) * axis.y * axis.z - Math::Sin(angle) * axis.x;
	mat_rot[2][0] = (1 - Math::Cos(angle)) * axis.z * axis.x - Math::Sin(angle) * axis.y;
	mat_rot[2][1] = (1 - Math::Cos(angle)) * axis.z * axis.y + Math::Sin(angle) * axis.x;
	mat_rot[2][2] = pow(axis.z,2) + (1 - pow(axis.z,2))* Math::Cos(angle);

	m_direction = mat_rot * m_direction;
}

void Light::roll(const Radian& angle)
{
	Matrix3 mat_rot = Matrix3::IDENTITY;

	mat_rot[0][0] = 1;
	mat_rot[0][1] = 0;
	mat_rot[0][2] = 0;
	mat_rot[1][0] = 0;
	mat_rot[1][1] = Math::Cos(angle);
	mat_rot[1][2] = - Math::Sin(angle);
	mat_rot[2][0] = 0;
	mat_rot[2][1] = Math::Sin(angle);
	mat_rot[2][2] = Math::Cos(angle);

	m_direction = mat_rot * m_direction;
}

void Light::pitch(const Radian& angle)
{
	Matrix3 mat_rot = Matrix3::IDENTITY;

	mat_rot[0][0] = Math::Cos(angle);
	mat_rot[0][1] = 0;
	mat_rot[0][2] = Math::Sin(angle);
	mat_rot[1][0] = 0;
	mat_rot[1][1] = 1;
	mat_rot[1][2] = 0;
	mat_rot[2][0] = - Math::Sin(angle);
	mat_rot[2][1] = 0;
	mat_rot[2][2] = Math::Cos(angle);

	m_direction = mat_rot * m_direction;
}

void Light::yaw(const Radian& angle)
{
	Matrix3 mat_rot = Matrix3::IDENTITY;

	mat_rot[0][0] = Math::Cos(angle);
	mat_rot[0][1] = - Math::Sin(angle);
	mat_rot[0][2] = 0;
	mat_rot[1][0] = Math::Sin(angle);
	mat_rot[1][1] = Math::Cos(angle);
	mat_rot[1][2] = 0;
	mat_rot[2][0] = 0;
	mat_rot[2][1] = 1;
	mat_rot[2][2] = 0;

	m_direction = mat_rot * m_direction;
}