#pragma once
#include <functional>
#include <unordered_map>
#include <string>

namespace Alpha
{
	template<typename T>
	class TFactory
	{
	private:
		using BuildFunc = std::function<T* ()>;
		using Builder = std::unordered_map<std::string, BuildFunc>;

		Builder m_builder;

	public:
		TFactory();
		~TFactory();

		void RegisterBuilder(const std::string& name, const BuildFunc& func)
		{
			// “o˜^‚³‚ê‚Ä‚¢‚é‚©‚ÌŠm”F



			m_builder.insert({ name,func });

		}

	};

	/*
	class Test;
	using TestFactory = TFactory<Test>;

	static TestFactory* GetTestFactory()
	{
		static TestFactory factory;

		return &factory;
	}

	class TestO : public Test
	{
	public:
		TestO()
		{
			GetTestFactory()->RegisterBuilder();
		}

	};
	static TestO;
	*/


}