
#include "camera.h"
#include "interaction.h"
#include "scene.h"
#include "render_loop.h"

#include "imgui/third_party/imgui_impl_glfw.h"
#include "imgui/third_party/imgui_impl_opengl3.h"

#include "imgui/scene_control.h"

int main()
{
    // glfw init
    glfwInit();
    // GL 3.0 + GLSL 330
    const char *glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // // 指定 MSAA 超采样个数 （使用offline方法的时候请注释掉以下的语句）
    // glfwWindowHint(GLFW_SAMPLES, 4);

    // create window instance
    GLFWwindow *window = glfwCreateWindow(primary_cam.frame_width, primary_cam.frame_height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // glad init
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // 注册键盘交互回调函数
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // （游戏模式下，不显示鼠标的效果）
    glfwSetCursorPosCallback(window, primary_mouse_moving_call_back);  // 注册鼠标移动交互回调函数
    glfwSetScrollCallback(window, primary_mouse_scroll_callback);      // 注册鼠标滚轮交互回调
    glfwSetMouseButtonCallback(window, primary_mouse_button_callback); // 注册鼠标点击交互回调函数

    // // demo 场景生成
    // Scene cube_scene = gen_multi_rotating_cube_scene();
    // Scene light_scene = gen_lighting_scene();
    // Scene model_scene = gen_load_model_scene();
    // Scene framebuffer_scene = gen_framebuffer_scene();
    // Scene skybox_scene = gen_skybox_scene();
    // Scene geom_scene = gen_geometry_shader_scene();
    // Scene explode_scene = gen_explode_model_scene();
    // Scene visual_norm_scene = gen_visualize_model_normal_scene();
    // Scene multi_instance_scene = gen_render_instance_scene();
    // Scene multi_instance_scene_opt = gen_render_instance_scene_opt();
    // Scene planet_scene = gen_mars_simu_scene();
    // Scene MSAA_scene = gen_default_MSAA_scene();
    // Scene offscreen_MSAA_scene = gen_offscreen_MSAA_scene();
    // Scene offscreen_MSAA_scene = gen_offscreen_MSAA_scene_ano();
    // Scene blinn_phong_scene = gen_test_Blinn_Phong_scene();
    // Scene shadow_scene = gen_shadow_mapping_scene();
    // Scene real_shadow_scene = switch_gen_shadow_mapping_scene();
    // Scene real_shadow_scene_p2 = switch_gen_shadow_mapping_scene_phase2();
    // Scene point_light_shadow_scene = gen_point_light_shadow_mapping_scene();
    // Scene normal_mapping_scene = gen_simple_normal_mapping_scene();
    // Scene height_mapping_scene = gen_simple_height_mapping_scene();

    // Scene deferred_shading_scene = gen_deferred_shading_scene();

    Scene SSAO_scene = gen_simple_SSAO_scene();


    // Scene pbr_light_scene = gen_PBR_light_base_scene();
    // Scene pbr_textured_scene = gen_PBR_light_textured_scene();

    // Scene pbr_ibl_diffuse_scene = gen_PBR_IBL_diffuse_scene();
    // Scene pbr_ibl_diffuse_scene = gen_PBR_IBL_diffuse_scene_p2();
    // Scene pbr_ibl_diffuse_scene = gen_PBR_IBL_diffuse_scene_ano();

    // Scene pbr_ibl_specular_scene = gen_PBR_IBL_specular_scene();

    // Scene pbr_ibl_textured_scene = gen_PBR_IBL_textured_scene();

    // Scene pbr_ibl_model_scene = gen_PBR_IBL_model_scene();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    bool show_demo_window = false; // 这个先不用
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // main render loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(400, 300)); // 宽400 高300

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            render_control();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        // glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        // glClear(GL_COLOR_BUFFER_BIT);

        // demo 场景绘制
        // multi_rotating_cube_demo_loop(cube_scene);
        // scene_light_demo_loop(light_scene);
        // scene_load_model_demo_loop(model_scene);
        // framebuffer_test_loop(framebuffer_scene);
        // scene_skybox_demo_loop(skybox_scene);
        // scene_geometry_shader_demo_loop(geom_scene);
        // scene_explode_model_demo_loop(explode_scene);
        // scene_visualize_model_normal_loop(visual_norm_scene);
        // rendering_instance_demo_loop(multi_instance_scene);
        // rendering_instance_demo_loop_opt(multi_instance_scene_opt);
        // planet_demo_loop(planet_scene);
        // MSAA_demo_loop(MSAA_scene);
        // offscreen_MSAA_loop(offscreen_MSAA_scene);
        // offscreen_MSAA_loop_ano(offscreen_MSAA_scene);
        // blinn_phong_demo_loop(blinn_phong_scene);
        // shadow_mapping_demo_loop(shadow_scene);
        // switch_shadow_mapping_demo_loop(real_shadow_scene);
        // switch_shadow_mapping_demo_loop_p2(real_shadow_scene_p2);
        // point_light_source_shadow_mapping_demo_loop(point_light_shadow_scene);
        // simple_normal_mapping_demo_loop(normal_mapping_scene);
        // simple_height_mapping_demo_loop(height_mapping_scene);

        // deferred_shading_demo_loop(deferred_shading_scene);

        simple_SSAO_demo_loop(SSAO_scene);
        
        // point_light_source_shadow_mapping_demo_loop(point_light_shadow_scene);
        // PBR_light_base_demo_loop(pbr_light_scene);
        // PBR_light_textured_demo_loop(pbr_textured_scene);

        // PBR_IBL_diffuse_demo_loop(pbr_ibl_diffuse_scene);
        // PBR_IBL_diffuse_demo_loop_p2(pbr_ibl_diffuse_scene);
        // PBR_IBL_diffuse_demo_loop_ano(pbr_ibl_diffuse_scene); // 想将金属球应用到 PBR-IBL 上，但失败了，再看一下原理再改

        // PBR_IBL_specular_demo_loop(pbr_ibl_specular_scene);

        // PBR_IBL_textured_demo_loop(pbr_ibl_textured_scene);

        // PBR_IBL_model_demo_loop(pbr_ibl_model_scene);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // 按键交互
        primary_keyboard_callback(window, primary_cam);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
