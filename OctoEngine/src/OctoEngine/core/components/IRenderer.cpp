#include "IRenderer.h"

namespace octo {
	namespace core
	{

		IRenderer::IRenderer():
			Component()
		{
		}


		IRenderer::~IRenderer()
		{
		}

		//void IRenderer::setAmbientLight(const octo::graphics::AmbientLight& ambientLight)
		//{
		//	m_AmbientLight = ambientLight;
		//}

		//const octo::graphics::AmbientLight& IRenderer::getAmbientLight() const
		//{
		//	return m_AmbientLight;
		//}
	}
}