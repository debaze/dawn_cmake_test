#include <fstream>
#include <iostream>

#include <GLFW/glfw3.h>
#include <webgpu/webgpu_cpp.h>
#ifdef EMSCRIPTEN
	#include <emscripten/emscripten.h>
#else
	#include <webgpu/webgpu_glfw.h>
#endif

#include "utils.cpp"
#include "Renderer.cpp"

const uint32_t WINDOW_WIDTH	= 512;
const uint32_t WINDOW_HEIGHT = 512;
const char* WINDOW_TITLE = "WebGPU";

Renderer renderer;

auto adapterAndDeviceCallback = [](Renderer& renderer) {
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);

	renderer.setWindow(window);
	renderer.createSurface();
	renderer.createSwapChain();

	char* shaderSource = readFile("shaders/vertex.wgsl");
	wgpu::ShaderModule vertexShaderModule = renderer.createShaderModule(shaderSource);
	shaderSource = readFile("shaders/fragment.wgsl");
	wgpu::ShaderModule fragmentShaderModule = renderer.createShaderModule(shaderSource);

	renderer.createRenderPipeline(vertexShaderModule, fragmentShaderModule);

	auto render = [](void* userData) {
		Renderer& renderer = *reinterpret_cast<Renderer*>(userData);

		wgpu::RenderPassColorAttachment colorAttachment {
			.view = renderer.getSwapChain().GetCurrentTextureView(),
			.loadOp = wgpu::LoadOp::Clear,
			.storeOp = wgpu::StoreOp::Store,
		};

		wgpu::RenderPassDescriptor renderPassDescriptor {
			.colorAttachmentCount = 1,
			.colorAttachments = &colorAttachment,
		};

		wgpu::CommandEncoder commandEncoder = renderer.getDevice().CreateCommandEncoder();
		wgpu::RenderPassEncoder renderPass = commandEncoder.BeginRenderPass(&renderPassDescriptor);

		renderPass.SetPipeline(renderer.getRenderPipeline());
		renderPass.Draw(3);
		renderPass.End();

		wgpu::CommandBuffer commandBuffer = commandEncoder.Finish();
		renderer.getDevice().GetQueue().Submit(1, &commandBuffer);
	};

	#ifdef EMSCRIPTEN
		emscripten_set_main_loop_arg(render, (void*) &renderer, 0, false);
	#else
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();

			render((void*) &renderer);

			renderer.getSwapChain().Present();
		}

		glfwTerminate();
	#endif
};

int main() {
	if (!glfwInit()) return -1;

	renderer.setAdapterAndDeviceCallback(adapterAndDeviceCallback);
	renderer.createInstance();
	renderer.requestAdapterAndDevice();
}