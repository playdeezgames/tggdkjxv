#include "Visuals.Textures.h"
#include "Common.Utility.h"
#include <SDL_image.h>
#include "Data.JSON.h"
#include <map>
#include <memory>
#include "Data.Stores.h"
#include "Common.Application.Internals.h"
namespace visuals::Textures
{
	static std::map<std::string, std::shared_ptr<SDL_Texture>> table;

	static void Add(const std::string& name, const std::shared_ptr<SDL_Texture>& texture)
	{
		table[name] = texture;
	}

	static bool initialized = false;

	static void HookDestroyTexture(SDL_Texture* texture)
	{
		SDL_DestroyTexture(texture);
	}

	static void Initialize(const std::shared_ptr<common::Application::Renderer>& renderer)
	{
		if (!initialized)
		{
			auto& properties = data::Stores::GetStore(data::Store::TEXTURES);
			for (auto& entry : properties.items())
			{
				std::string imageFileName = entry.value();
				Add(entry.key(), std::shared_ptr<SDL_Texture>(IMG_LoadTexture(renderer.get()->renderer.get(), imageFileName.c_str()), HookDestroyTexture));
			}
			initialized = true;
		}
	}

	const std::shared_ptr<SDL_Texture>& Read(const std::shared_ptr<common::Application::Renderer>& renderer, const std::string& name)
	{
		Initialize(renderer);
		return table.find(name)->second;
	}
}