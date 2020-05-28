#pragma once

#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <iostream>
#include <initializer_list>
#include <type_traits>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/types.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/transform.hpp"

#include "common/common.h"
#include "debug.h"

namespace				engine
{
	using				std::vector;
	using				std::list;
	using				std::optional;
	using				std::pair;
	using				std::string;
	using				std::move;
	using				std::filesystem::path;
	using				std::unique_ptr;
	using				std::make_unique;
	using				std::shared_ptr;
	using				std::make_shared;
	using				std::initializer_list;

	using				glm::ivec2;
	using				glm::vec2;
	using				glm::vec3;
	using				glm::vec4;
	using				glm::mat3;
	using				glm::mat4;
	using				glm::quat;

	namespace			converter
	{}

	class 				core;

	namespace			interface
	{
		class			function;
		class			timer;
		class			event;
		class			callback;
		enum class		key;
	}

	namespace			abstract
	{
		template		<typename enum_type, typename underlying_type>
		class			enum_wrap;
		class			holder;
	}

	namespace			program
	{
		template		<typename type>
		class			uniform;
		class 			shader;
		class 			program;
	}

	namespace			model
	{
		class			bone;
		class			skeleton;
		class			animation;
		class			texture;
		class			material;
		class			mesh;
		class			manager;
		class			model;
		class			instance;
	}

	namespace			scene
	{
		class			camera;
		class			light;
		class			scene;
	}

	class 				renderer;
}