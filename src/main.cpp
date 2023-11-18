#include <fstream>
#include <iostream>
// #include <vector>

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

	const char* shaderSource = readFile("../../../src/shaders/vertex.wgsl");
	wgpu::ShaderModule vertexShaderModule = renderer.createShaderModule(shaderSource);
	shaderSource = readFile("../../../src/shaders/fragment.wgsl");
	wgpu::ShaderModule fragmentShaderModule = renderer.createShaderModule(shaderSource);

	/* wgpu::BufferDescriptor bufferDescriptor {
		.usage = wgpu::BufferUsage::Vertex | wgpu::BufferUsage::CopyDst,
		.size = 24,
	};
	wgpu::Buffer vertexBuffer = renderer.createBuffer(bufferDescriptor);

	int8_t data[6] = {
	   -1, -1,
		0,  1,
		1, -1,
	};

	renderer.getDevice().GetQueue().WriteBuffer(vertexBuffer, 0, data, 8);

	wgpu::VertexAttribute vertexAttribute {
		.format = wgpu::VertexFormat::Float32x2,
		.offset = 0,
		.shaderLocation = 0,
	};

	wgpu::VertexBufferLayout vertexBufferLayout {
		.arrayStride = sizeof(float) * 2,
		.stepMode = wgpu::VertexStepMode::Vertex,
		.attributeCount = 1,
		.attributes = &vertexAttribute,
	}; */

	renderer.createRenderPipeline(vertexShaderModule, fragmentShaderModule /*, vertexBufferLayout */);
	// renderer.vertexBuffer = vertexBuffer;

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
		// renderPass.SetVertexBuffer(0, renderer.vertexBuffer, 0, sizeof(float) * 6);
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
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	renderer.setAdapterAndDeviceCallback(adapterAndDeviceCallback);
	renderer.createInstance();
	renderer.requestAdapterAndDevice();
}