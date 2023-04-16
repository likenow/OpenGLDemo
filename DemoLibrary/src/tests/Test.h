#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <string>

namespace test {

	class Test
	{
	public:
		Test() {}
		~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPtr);
		// we don't need a destructor actually
		// because everything's stacked
		//~TestMenu() {}

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test = " << name << std::endl;
			m_Tests.push_back(std::make_pair(name, [](){ return new T(); }));
		}

	private:
		Test*& m_CurrentTest;
		// collect a list right a vector of strings and the actual test classses which those strings kind of create
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
	};
}