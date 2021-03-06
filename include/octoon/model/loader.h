#ifndef OCTOON_LOADER_H_
#define OCTOON_LOADER_H_

#include <octoon/io/iostream.h>
#include <octoon/model/moddef.h>

#include <string>

namespace octoon
{
	namespace model
	{
		class Model;

		class ModelLoader
		{
		public:
			ModelLoader() = default;
			virtual ~ModelLoader() noexcept = default;

			virtual bool doCanLoad(io::istream& stream) noexcept = 0;
			virtual bool doCanLoad(const std::string& type) noexcept = 0;
			virtual bool doCanLoad(const char* type) noexcept = 0;
			virtual bool doLoad(io::istream& stream, Model& model) noexcept = 0;
			virtual bool doSave(io::ostream& stream, const Model& model) noexcept = 0;

		private:
			ModelLoader(const ModelLoader&) = delete;
			ModelLoader& operator=(const ModelLoader&) = delete;
		};
	}
}
#endif // !OCTOON_LOADER_H_

