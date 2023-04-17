#include "TestTexture2D.h"

#include "Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace test {
	TestTexture2D::TestTexture2D()
        : m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), 
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), 
        m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0)
	{
        /*
        // use index buffer
        float positions[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f
        };
        */
        /*
        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f
        };
        */
        /*
       顶点位置浮点型数组
       the center point is (0,0)
       x,y -50,-50
       */
        float positions[] = {
           -50.0f, -50.0f, 0.0f, 0.0f, // 0
            50.0f, -50.0f, 1.0f, 0.0f, // 1
            50.0f,  50.0f, 1.0f, 1.0f, // 2
           -50.0f,  50.0f, 0.0f, 1.0f  // 3
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_VAO = std::make_unique<VertexArray>();

        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

        // create projection matrix
        // orthographic matrix
        // 4:3
        // specifying the 4 kind of boundaries f our window
        //glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
        /* 这里应该是 960x720 而不是 960x540 的分辨率 */
        //glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);

        m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
        m_Shader->Bind();
        //shader.SetUniform4f("u_Color", 0.6f, 0.3f, 0.8f, 1.0f);
        m_Shader->SetUniform1i("u_Texture", 0);

        m_Texture = std::make_unique<Texture>("res/textures/ChernoLogo.png");
	}
	TestTexture2D::~TestTexture2D()
	{}


	void TestTexture2D::OnUpdate(float deltaTime)
	{}
	void TestTexture2D::OnRender()
	{
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;
        m_Texture->Bind();
        // Here bind that's a bit redundant, that's a bit slow, a bit of a waste of performance
        // usually in more complicated setups, such as a natural game engine or a graphics engine
        // you would have a some kind of cache system, that would be like hang on a minute
        // you're trying to bind the shader that's already bound
        // A
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
        // B
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
	}
	void TestTexture2D::OnImGuiRender()
	{
        ImGui::Begin("Hello, world!");
        ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
	}
}